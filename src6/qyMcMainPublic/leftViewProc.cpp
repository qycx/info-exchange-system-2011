

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyMc.h"
#include	"leftView.h"
//  #include	"qyMcView.h"
#include	"qyCusResTemp.h"


 BOOL  bGetTopParams(  int  *piTopFieldId,  int  *piTopObjType  )
{
	 BOOL		bRet	=	FALSE;
	 QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	 int		iTopFieldId,  iObjType;
	 
	 switch  (  pQyMc->cfg.custom.nDwLevels  )  {
			 case  5:  iTopFieldId  =  CONST_fieldId_zb;	iObjType  =  CONST_objType_zb;  break;
			 case  4:  iTopFieldId  =  CONST_fieldId_bb;	iObjType  =  CONST_objType_bb;	break;
			 case  3:  iTopFieldId  =  CONST_fieldId_dw;	iObjType  =  CONST_objType_col2;break;
			 default:	goto  errLabel;
	 }
	 bRet  =  TRUE;
errLabel:
	 if  (  bRet  )  {
		 if  (  piTopFieldId  )  *piTopFieldId  =  iTopFieldId;
		 if  (  piTopObjType  )  *piTopObjType  =  iObjType;
	 }
	 return  bRet;
}



  int  myTrimTree(  void  *  pDb,  void  *  pLeftViewParam,  HANDLE  htItemParam,  PF_bTvItemExists  pfbTvItemExists  )
{
	 CLeftView  *	pLeftView	=	(  CLeftView  *  )pLeftViewParam;
	 HTREEITEM		htItem		=	(  HTREEITEM  )htItemParam;

	 if  (  !pfbTvItemExists  )  {
		 traceLogA(  "myTrimTree:  pfbTvItemExists没有设置"  );  return  -1;
	 }

	 if  (  pLeftView->m_TreeCtrl->ItemHasChildren(  htItem  )  )  {
		 HTREEITEM  tmphtItem	=	pLeftView->m_TreeCtrl->GetChildItem(  htItem  );
		 while  (  tmphtItem  )  {
			    if  (  !pfbTvItemExists(  pDb,  pLeftView,  tmphtItem  )  )  {
					HTREEITEM  tmphtItem1  =  pLeftView->m_TreeCtrl->GetNextSiblingItem(  tmphtItem  );
					pLeftView->m_TreeCtrl->DeleteItem(  tmphtItem  );  
					tmphtItem  =  tmphtItem1;  continue;
				}
				myTrimTree(  pDb,  pLeftView,  tmphtItem,  pfbTvItemExists  );
				tmphtItem  =  pLeftView->m_TreeCtrl->GetNextSiblingItem(  tmphtItem  );
		 }
	 }
	 return  0;
}


 int  myAddOrRefreshTreeItem(  void  *  pLeftViewParam,  HANDLE  htItemParam,  int  iObjId,  TCHAR  *  displayName,  int  nImage,  int  nSelectedImage,  void  *  pQmObjQParam  )
{
	 int					iErr				=		-1;
	 QY_MC		*			pQyMc				=		QY_GET_GBUF(  );
	 CLeftView  *			pLeftView			=		(  CLeftView  *  )pLeftViewParam;
	 HTREEITEM				htItem				=		(  HTREEITEM  )htItemParam;
	 HTREEITEM				tmphtItem			=				NULL;
	 TCHAR					tBuf[1024];
	 QM_OBJQ_MEM			mem;
			   

	 if  (  !(  tmphtItem  =  pLeftView->FindItemData(  iObjId,  TRUE,  htItem  )  )  )  {

		 if  (  pQmObjQParam  )  {		//  µ±ÓÐÄÚ´æ¶ÔÁÐÊ±£¬Ó¦¸ÃÈ±Ê¡Îªoffline
			 QMOBJQ_PARAM_MISCLIENT	*	pParam  =	(  QMOBJQ_PARAM_MISCLIENT  *  )pQmObjQParam;
			 QMEM_MESSENGER_CLI		*	pQMem	=	NULL;

			 //  ÏÈ¼ÓÈëobjQ»ò´ÓÀïÃæÕÒµ½mem             
			 if  (  procQmObjQ(  pParam->pSci,  (  QM_OBJQ  *  )pParam->pMisCnt->pObjQ,  pParam->pDb,  pParam->iDbType,  pParam->iObjType,  pParam->pClient,  &mem  )  )  goto  errLabel;
			 if  (  !mem.pQMemObj  )  goto  errLabel;

			 pQMem  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;

			 getMessengerImages(  pQyMc,  pQMem->usRunningStatus,  &nImage,  &nSelectedImage  );
			 
		 }

		 tmphtItem  =  pLeftView->m_TreeCtrl->InsertItem(  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE  |  TVIF_PARAM,  
										   CString(  displayName  ).GetBuffer(  0  ),  
										   nImage,  
										   nSelectedImage,  
										   TVIS_EXPANDPARTIAL,  
										   TVIS_STATEIMAGEMASK, 
										   iObjId,  
										   htItem,  
										   TVI_LAST  );		


		 if  (  !tmphtItem  )  goto  errLabel;

		 if  (  pQmObjQParam  )  {		//  Í¨¹ýÕâÀïµÄÐÂÔö²ÅÄÜ¼ÓÈë¶ÓÁÐ£¬ÕâÑù¿ÉÒÔÌá¸ßÐ§ÂÊ£¬2007/06/05
			 QMOBJQ_PARAM_MISCLIENT	*	pParam  =  (  QMOBJQ_PARAM_MISCLIENT  *  )pQmObjQParam;
			 
			 //  ÔÙ¼ÓÈë±¾´°¿ÚµÄ¶ÓÁÐÖÐ£¬ÒÔ·½±ãÊµÊ±Ë¢ÐÂ£¬2007/06/09
			 addToDisplayedObjQ(  &pLeftView->m_var.displayCtx,  pParam,  pLeftView->m_hWnd,  tmphtItem  );

		 }


		 }
	 else  {

		   if  (  pQmObjQParam  )  {	//  ÕâÀï£¬Èç¹ûÓÐÄÚ´æÖÐ¶ÓÁÐµÄ»°£¬»¹ÒªÓÃ¶ÓÁÐÖÐÁÙÊ±×´Ì¬À´ÏÔÊ¾
			   QMOBJQ_PARAM_MISCLIENT	*	pParam  =  (  QMOBJQ_PARAM_MISCLIENT  *  )pQmObjQParam;	
			   //
			   if  (  !findQMemByObj(  0,  pParam->pMisCnt->pObjQ,  pParam->pClient,  &mem  )  &&  mem.pQMemObj  )  {
				   QMEM_MESSENGER_CLI  *  pQMem  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;
				   //
				   getMessengerImages(  pQyMc,  pQMem->usRunningStatus,  &nImage,  &nSelectedImage  );
			   }

		   }

				  				  
		   //  Ö»Ë¢ÐÂÕ¹¿ª½Úµã
		   TVITEM				tvItem;
		   			
		   tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
		   tvItem.hItem  =  tmphtItem;
		   tvItem.pszText  =  tBuf;
		   tvItem.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );
		   pLeftView->m_TreeCtrl->GetItem(  &tvItem  );
		   
		   if  (  _tcsicmp(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
			   _sntprintf(  tBuf,  sizeof(  tBuf  ) /  sizeof(  tBuf[0]  ),  _T(  "%s"  ),  displayName  );
			   tvItem.iImage  =  nImage;
			   tvItem.iSelectedImage  =  nSelectedImage;
			   pLeftView->m_TreeCtrl->SetItem(  &tvItem  );
		   }
			   
		
		   //  if  (  tvItem.state  &  TVIS_EXPANDED   )  pLeftView->bRefreshItem(  tmphtItem  );				   
		   if  (  pLeftView->m_TreeCtrl->ItemHasChildren(  tmphtItem  )  )  pLeftView->bRefreshItem(  tmphtItem  );				   
		
	 }

	 //  °ÑÕâÐ©²Ù×öµ½µÄmessenger·Åµ½recentFriendQÀïÈ¥
	 if  (  pQmObjQParam  )  {
		 QMOBJQ_PARAM_MISCLIENT  *  pParam  =  (  QMOBJQ_PARAM_MISCLIENT  *  )pQmObjQParam;

		 if  (  postRecentFriend(  pParam->pSci,  pParam->pMisCnt,  &pParam->pClient->idInfo,  0  )  )  traceLogA(  "postRecentFriend failed"  );  

	 }

	 iErr  =  0;

errLabel:

	 return  iErr;

}


int  myAddOrRefreshTreeItem(  void  *  pLeftViewParam,  HANDLE  htItemParam,  int  iObjId,  TCHAR  *  displayName,  int  nImage,  int  nSelectedImage  )
{
	return  myAddOrRefreshTreeItem(  pLeftViewParam,  htItemParam,  iObjId,  displayName,  nImage,  nSelectedImage,  NULL  );

}



