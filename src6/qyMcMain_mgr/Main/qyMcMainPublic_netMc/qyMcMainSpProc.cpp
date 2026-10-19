

#include	"stdafx.h"
#include	"qyMcMainCommon.h"

#include	"qyMc.h"

#include	"leftView.h"
#include	"qyMcView.h"
#include	"qyCusResTemp.h"
#include	"myDb.h"

 QY_COLUMNINFO  COSNT_cfgSpOsListColumns[]  =  
{
	{	0,	_T( "²Ù×÷ÏµÍ³" ),					0,	LVCFMT_LEFT, 	120,	1	},
	{	-1,															},
};

 QY_COLUMNINFO  CONST_servicePackListColumns[]  =
{
	{	0,	_T(  "Ãû³Æ"  ),								0,	LVCFMT_LEFT,	200,	1	},
	{	0,	_T(  "ÓïÑÔ"  ),								0,	LVCFMT_LEFT,	80,	1	},
	{	0,	_T(  "url"  ),								0,	LVCFMT_LEFT,	120,	1	},
	{	0,	_T(  "ÃèÊö"  ),								0,	LVCFMT_LEFT,	200,	1	},
	{	-1,	NULL,																},
};

 QY_COLUMNINFO  CONST_spListColumns[]  =
{
	{	0,	_T(  "Ãû³Æ"  ),								0,	LVCFMT_LEFT,	80,	1	},
	{	0,	_T(  "±ðÃû"  ),								0,	LVCFMT_LEFT,	80,	1	},
	{	0,	_T(  "ÓïÑÔ"  ),								0,	LVCFMT_LEFT,	80,	1	},
	{	0,	_T(  "url"  ),								0,	LVCFMT_LEFT,	160,	1	},
	{	0,	_T(  "ÃèÊö"  ),								0,	LVCFMT_LEFT,	200,	1	},
	{	-1,	NULL,																},
};


 int  displayListContent_allTopCols(  QY_OBJ_DB  *  pObjDb,  CQyMcView  *  pMcView,  QY_MC_DISPLAYCFG	*	pCfgParam,  LPCTSTR  tabName_regInfo  );
 int  displayListContent_allCfgSpOses(  QY_OBJ_DB  *  pObjDb,  CQyMcView  *  pMcView,  	 QY_MC_DISPLAYCFG	*	pCfgParam  );
 int  displayListContent_cfgSpOs(  QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_OBJINDEX_RCD  *  pObjIndex  );
 int  displayListContent_cfgSpServicePack(  QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_OBJINDEX_RCD  *  pObjIndex  );


 BOOL  bTvItemExists_cfgSp(  QY_OBJ_DB  *  pObjDb,  CLeftView  *  pLeftView,  HTREEITEM  htItem  )
{
	 BOOL				bRet								=	FALSE;
	 int				iObjId								=	pLeftView->m_TreeCtrl->GetItemData(  htItem  );
	 QY_OBJINDEX_RCD	objIndex;
	 char				sqlBuf[CONST_maxSqlBufLen  +  1]	=	"";


	 QM_dbFuncs  *  pDbFuncs  =  QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  return  FALSE;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	 if  (  g_dbFuncs.pf_getObjIndex(  pObjDb,  iObjId,  &objIndex  )  )  goto  errLabel;  

	 switch  (  objIndex.objType  )  {
			 case  CONST_objType_col2:
		   	 //	   _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "select count(qyPcRegInfoTab.mac0) from qyPcRegInfoTab  where  qyPcRegInfoTab.col2='%s'",  objIndex.objIdStr0  );
			 //	   break;
			 default:
					//  ÕâÀï¼ÙÉè£¬ÐèÒª¼ìÑéµÄ¶¼ÒªÖ¸¶¨
				    bRet  =  TRUE;  goto  errLabel;
	 }
	 if  (  !bSqlObjExists(  pObjDb->pDb,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  goto  errLabel;

	 bRet  =  TRUE;
errLabel:

	 traceLogA(  "½Úµã[%d] %s %s %s %s",  objIndex.objType,  objIndex.objIdStr0,  objIndex.objIdStr1,  objIndex.objIdStr2,  (  bRet  ?  "´æÔÚ"  :  "²»´æÔÚ"  )  );

	 return  bRet;
}


 

#if  0
 int  displayContent_cfgSp(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int					iRet				=				-1;
	 QY_MC				*	pQyMc				=				QY_GET_GBUF(  );
	 CLeftView			*	pLeftView			=				(  CLeftView  *  )p0;
	 CTreeCtrl			*	m_TreeCtrl			=				&pLeftView->GetTreeCtrl(  );
	 CQyMcDoc			*	pDoc				=				pLeftView->GetDocument(  );
	 if  (  pDoc->m_docStruct.iDocType  !=  CONST_qyDocType_mcRootTree  )  return  -1;
	 QY_OBJ_DB			*	pObjDb				=				getProcedObjDb(  0,  pDoc->m_docStruct.u.treeList.tree.iDsnIndex  );
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  -1;
	 //
	 CRecordset				rs(  (  CDatabase  *  )pObjDb->pDb  );
	 CDBVariant				varVals[20];
	 //  int					index, nFields;
	 //  CODBCFieldInfo		tmpFieldInfo;
	 //  char					sqlBuf[QY_SQLBUFLEN  +  1];
	 HTREEITEM				tmphtItem			=				NULL;
	 TCHAR					displayName[512]	=				_T(  ""  );		
	 int					iObjId				=				0;
	 int					nImage,  nSelectedImage;
	 QY_DMITEM			*	pItem				=				NULL;
	 unsigned  char			ucbSorted			=				FALSE;
	 TCHAR					tBuf[1024];

	 if  (  !pLeftView->m_var.bInitialized  ||  !pLeftView->m_var.htMyRootItem  )  goto  errLabel;

	 
	 try  {

		  //  ÏÈ½«²»´æÔÚµÄ½ÚµãÉ¾³ý
		  myTrimTree(  pQyMc->gui.pDb,  pLeftView,  pLeftView->m_var.htMyRootItem,  (  PF_bTvItemExists  )bTvItemExists_cfgSp  );  


		  //  ÏÂÃæÔö¼ÓÐÂÔöµÄ½Úµã
		  //
		  //  ÏÈ½«¸÷²Ù×÷ÏµÍ³¶¼·ÅÈëÊÓÍ¼ÖÐ
		  for  (  pItem  =  CONST_qnmPlatformTable;  pItem->type  !=  -1;  pItem  ++  )  {
					   	 
			   iObjId  =  getObjId(  pObjDb,  0,  NULL,CONST_objType_cfgSpOs,  (  void  *  )pItem->type  );
			   if  (  iObjId  <  0  )  continue;

			   _sntprintf(  displayName,  sizeof(  displayName  )  /  sizeof(  displayName[0]  ),  _T(  "%s"  ),  pItem->des  );
			   nImage  =  pQyMc->cfg.image.nImage_os;  nSelectedImage  =  pQyMc->cfg.image.nImage_os;

			   if  (  !(  tmphtItem  =  pLeftView->FindItemData(  iObjId,  TRUE,  pLeftView->m_var.htMyRootItem  )  )  )  {
				   tmphtItem  =  m_TreeCtrl->InsertItem(  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE  |  TVIF_PARAM,  
														  CString(  displayName  ).GetBuffer(  0  ),  
														  nImage,  
														  nSelectedImage,  
														  TVIS_EXPANDPARTIAL,  
														  TVIS_STATEIMAGEMASK, 
														  iObjId,  
														  pLeftView->m_var.htMyRootItem,  
														  TVI_LAST  );
				   if  (  ucbSorted  )  m_TreeCtrl->SortChildren(  pLeftView->m_var.htMyRootItem  );
				   
				   }
			   else  {				  
				     //  Ö»Ë¢ÐÂÕ¹¿ª½Úµã
					 TVITEM				tvItem;
					 //  char				tmpBuf[512];

					 tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
					 tvItem.hItem  =  tmphtItem;
					 tvItem.pszText  =  tBuf;
					 tvItem.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );
					 m_TreeCtrl->GetItem(  &tvItem  );
					 
					 if  (  lstrcmpi(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
						 _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s"  ),  displayName  );
						 tvItem.iImage  =  nImage;
						 tvItem.iSelectedImage  =  nSelectedImage;
						 m_TreeCtrl->SetItem(  &tvItem  );
					 }

					 //  Ë¢ÐÂÕ¹¿ª½Úµã
					 //  if  (  tvItem.state  &  TVIS_EXPANDED   )  pLeftView->bRefreshItem(  tmphtItem  );				   
					 if  (  pLeftView->m_TreeCtrl->ItemHasChildren(  tmphtItem  )  )  pLeftView->bRefreshItem(  tmphtItem  );				   

			   }

			   /*  ÒÔÏÂÊÇ²úÉú¹ØÁªÍøÂçÓÃµÄ£¬ÔÚ×Ê²ú¹ÜÀíÖÐÔÝÊ±²»ÓÃ
			   if  (  pDoc->m_docStruct.u.treeList.tree.selectedSwitchMac[0]  
				   &&  !strcmpi(  pDoc->m_docStruct.u.treeList.tree.selectedSwitchMac,  pObj->mac  )  )
			   {
				   pLeftView->m_var.htInitialItem  =  tmphtItem;
			   }
			   */

		  }
		  rs.Close(  );
		  
		   
	 	}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "displayContent_cfgSp failed."  )  );
		   goto  errLabel;
	}

	 iRet				=				0;

errLabel:

	if  (  rs.IsOpen(  )  )  rs.Close(  );
	
	return  iRet;		

}
#endif


#if  0
 int  refreshItem_cfgSp(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int					iRet				=				-1;
	 QY_MC				*	pQyMc				=				QY_GET_GBUF(  );
	 CLeftView			*	pLeftView			=				(  CLeftView  *  )p0;
	 HTREEITEM				htItem				=				(  HTREEITEM  )p1;
	 CTreeCtrl			*	m_TreeCtrl			=				&pLeftView->GetTreeCtrl(  );
	 CQyMcDoc			*	pDoc				=				pLeftView->GetDocument(  );
	  if  (  pDoc->m_docStruct.iDocType  !=  CONST_qyDocType_mcRootTree  )  return  -1;
	 QY_OBJ_DB			*	pObjDb				=				getProcedObjDb(  0,  pDoc->m_docStruct.u.treeList.tree.iDsnIndex  );
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  -1;
	 //
	 int					iObjId;
	 QY_OSSP_RCD			osSp;
	 QY_OBJINDEX_RCD		objIndex;
	 CRecordset				rs( ( CDatabase * )pObjDb->pDb );
	 CDBVariant				varVals[10];
	 int					index,  nFields;
	 char					sqlBuf[1024];
	 int					nImage,  nSelectedImage;
	 HTREEITEM				tmphtItem			=				NULL;
	 TCHAR					displayName[512]	=				_T(  ""  );		
	 
	 if  (  htItem  ==  pLeftView->m_var.htMyRootItem  )  {
		 iRet  =  0;  goto  errLabel;
	 }

	 iObjId  =  m_TreeCtrl->GetItemData(  htItem  );
	 if  (  getObjIndex(  pObjDb,  iObjId,  &objIndex  )  )  goto  errLabel;
	 	 
	 if  (  objIndex.objType  ==  CONST_objType_cfgSpOs  )  {
		 																		//  0					1
		 _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "SELECT distinct qyOsSpTab.iPlatformId,qyOsSpTab.servicePack,qyOsSpTab.uiLangId from qyOsSpTab where qyOsSpTab.iPlatformId=%d order by qyOsSpTab.servicePack,  qyOsSpTab.uiLangId",  objIndex.objId0  );
		 traceLogA(  "%s",  sqlBuf  );
		 if  (  !rs.Open( CRecordset::forwardOnly,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  {
			 traceLogA(  "rs open() failed."  );  goto  errLabel;
		 }
	  			 
		 nFields  =  rs.GetODBCFieldCount(  );
		 //  rs.GetODBCFieldInfo(  index,  tmpFieldInfo  );
		 for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {
			  
			  memset(  &osSp,  0,  sizeof(  osSp  )  );
			  
			  for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   				  
			  index  =  0;  
			  MACRO_sqlLong(  varVals[index],  osSp.iPlatformId  );
			  index  ++  ;	//  osSp.servicePack
			  MACRO_sqlStr(  varVals[index],  osSp.servicePack,  sizeof(  osSp.servicePack  )  /  sizeof(  osSp.servicePack[0]  )  );
			  index  ++  ;	//  osSp.uiLangId
			  MACRO_sqlLong(  varVals[index],  osSp.uiLangId  );
			  index  ++  ;	//  

			  iObjId  =  getObjId(  pObjDb,  0,  NULL,CONST_objType_cfgSpServicePack,  &osSp  );
			  if  (  iObjId  <  0  )  continue;

			  _sntprintf(  displayName,  sizeof(  displayName  )  /  sizeof(  displayName[0]  ),  _T(  "%s(%s)"  ),  osSp.servicePack,  CString(  qyGetDesByType1(  CONST_qyLangTable_en,  osSp.uiLangId  )  )  );
			  nImage  =  pQyMc->cfg.image.nImage_os;  nSelectedImage  =  pQyMc->cfg.image.nImage_os;
			  //  getSnmpPortImages(  pQyMc,  &switchPort,  &nImage,  &nSelectedImage  );

			  if  (  myAddOrRefreshTreeItem(  pLeftView,  htItem,  iObjId,  displayName,  nImage,  nSelectedImage  )  )  goto  errLabel;

		 }					 
			}
	 else  if  (  objIndex.objType  ==  CONST_objType_cfgSpServicePack  )  {

			   traceLogA(  "here"  );
	 }
		

	 
	 iRet  =  0;

errLabel:
	 return  iRet;
}
#endif


#if  0
 int  displayListContent_cfgSp(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int								iRet					=	-1;
	 QY_MC							*	pQyMc					=	QY_GET_GBUF( );
	 CQyMcView						*	pMcView					=	(  CQyMcView  *  )p0;
	 QY_MC_DISPLAYCFG				*	pCfgParam				=	(  QY_MC_DISPLAYCFG  *  )p1;
	 QY_MCROOTTREE_SEL				*	pSel					=	(  QY_MCROOTTREE_SEL  *  )p2;
	 CListCtrl						&	ListCtrl				=	pMcView->GetListCtrl();
	 QY_OBJ_DB						*	pObjDb					=	getProcedObjDb(  0,  pSel->iDsnIndex  );
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  -1;

	 
	 if  (  pCfgParam->m_iViewType  !=  QY_VIEWTYPE_MCROOTLIST  )  {
		 traceLogA( "CQyMcView::bDisplayContent(  ) ½öÓÐ¶ÔMcRootListµÄÊµÏÖ£¬ÇëÓÃÅÉÉúÀàÀ´ÖØÔØ´Ëº¯Êý¡£"  );
		 return  -1;
	 }
	 
	 ListCtrl.DeleteAllItems(  );

	 try  {		
	 		  
		  if  (  pMcView->var.m_superSel.u.rootTree.bRoot  )  {
			  
			  //  ÏÔÊ¾ËùÓÐµÄµ¥Î»
			  if  (  displayListContent_allCfgSpOses(  pObjDb,  pMcView,  pCfgParam  )  )  goto  errLabel;
			 
			}
		  else  {
		  
			  	 int				iObjId				=	pMcView->var.m_superSel.u.rootTree.iHelpId;
				 QY_OBJINDEX_RCD	objIndex;
				 int				ilastPortIfIndex	=	-1;

	 			 if  (  getObjIndex(  pObjDb,  iObjId,  &objIndex  )  )  goto  errLabel;
				 switch  (  objIndex.objType  )  {					 
						  case  CONST_objType_cfgSpOs:
							    //  ÏÔÊ¾Ö¸¶¨µ¥Î»µÄËùÓÐ²¿ÃÅ
					 		    if  (  displayListContent_cfgSpOs(  pObjDb,  pMcView,  pCfgParam,  &objIndex  )  )  goto  errLabel;
								break;
						  case  CONST_objType_cfgSpServicePack:
							    if  (  displayListContent_cfgSpServicePack(  pObjDb,  pMcView,  pCfgParam,  &objIndex  )  )  goto  errLabel;
								break;
						  default:
								  goto  errLabel;
				 }
		
		  
		  }
		  
		  
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "displayListContent_cfgSp failed."  )  );
		   goto  errLabel;
	}
		 

	 iRet  =  0;

errLabel:
	
	
	 return  iRet;		

}
#endif


 int  displayListContent_allCfgSpOses(  QY_OBJ_DB  *  pObjDb,  CQyMcView  *  pMcView,  	 QY_MC_DISPLAYCFG	*	pCfgParam  )
{
	 int								iRet					=			-1;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 CQyMcDoc						*	pDoc					=			pMcView->GetDocument(  );
	 CListCtrl						&	ListCtrl				=			pMcView->GetListCtrl();
	 int								index					=			0;
	 //  QY_MCROOTLIST_DISPLAYCFG		*	pCfg					=			&pCfgParam->u.rootList;
	 int								cnt						=			0;
	 int								nImage;
	 QY_DMITEM						*	pItem					=			NULL;
	 	 
	 
	 try  {		
	 
		  if  (  pMcView->var.m_superSel.u.rootTree.bRoot  )  {
			  
			  //  ÏÔÊ¾ËùÓÐµÄµ¥Î»

			  pMcView->delAllColumns(  );
			  if  (  !pMcView->bAddColumns(  COSNT_cfgSpOsListColumns  )  )  goto  errLabel;


			  for  (  pItem  =  CONST_qyPlatformTable;  pItem->type  !=  -1;  pItem  ++  )  {
				   
				   nImage  =  pQyMc->cfg.image.nImage_col2;	 			  		

			   	   ListCtrl.InsertItem(  cnt,  CString(  pItem->des  ).GetBuffer(  0  ),  nImage  );
				   
				   cnt  ++  ;

			  }
		  }
			
		  
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "displayListContent_allCfgSpOses failed."  )  );
		   goto  errLabel;
	}
		 
	 iRet  =  TRUE;

errLabel:
	
	
	 return  iRet;		

}


 int  displayListContent_cfgSpOs(  QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_OBJINDEX_RCD  *  pObjIndex  )
{
	 int								iRet					=			-1;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 CListCtrl						&	ListCtrl				=			pMcView->GetListCtrl();
	 //  LV_ITEM							lvi;
	 int								index					=			0;
	 //  QY_MCROOTLIST_DISPLAYCFG		*	pCfg					=			&pCfgParam->u.rootList;
	 char								sqlBuf[CONST_qyMaxSqlBufLen  +  1];
	 CRecordset							rs(  (  CDatabase  *  )pQyMc->gui.pDb  );   int	 nFields;
	 CDBVariant							varVals[20];
	 QY_OSSP_RCD						osSp;
	 int								cnt						=			0;
	 int								nImage;
	 TCHAR								displayName[512];
	 
	 try  {		

		 if  (  pObjIndex->objType  ==  CONST_objType_cfgSpOs  )  {
					 
			 pMcView->delAllColumns(  );
			 if  (  !pMcView->bAddColumns(  CONST_servicePackListColumns  )  )  goto  errLabel;
			 																//  0														
			 _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "SELECT distinct  qyOsSpTab.iPlatformId,qyOsSpTab.uiLangId,qyOsSpTab.servicePack from qyOsSpTab where qyOsSpTab.iPlatformId=%d order by qyOsSpTab.servicePack",  pObjIndex->objId0  );
 			 traceLogA(  "%s",  sqlBuf  );
 			 if  (  !rs.Open( CRecordset::forwardOnly,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  {
				 traceLogA(  "rs open() failed."  );  goto  errLabel;
			 }
			 nFields  =  rs.GetODBCFieldCount(  );					 
					 
			 for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {

				  memset(  &osSp,  0,  sizeof(  osSp  )  );
				  				   
	  			  for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   				  
				  index  =  0;  MACRO_sqlLong(  varVals[index],  osSp.iPlatformId  );
				  index  ++  ;	MACRO_sqlLong(  varVals[index],  osSp.uiLangId  );
				  index  ++  ;  MACRO_sqlStr(  varVals[index],  osSp.servicePack,  sizeof(  osSp.servicePack  )  );

				  bGetOsSpRcdBySth(  pQyMc->gui.pDb,  0,  osSp.iPlatformId,  osSp.uiLangId,  osSp.servicePack,  NULL,  &osSp  );
				  				  
				  _sntprintf(  displayName,  sizeof(  displayName  )  /  sizeof(  displayName[0]  ),  _T(  "%s(%s)"  ),  osSp.servicePack,  qyGetDesByType1(  CONST_qyLangTable_en,  osSp.uiLangId  )  );
						  
				  nImage  =  pQyMc->cfg.image.nImage_os;
				
				  index  =  0;  ListCtrl.InsertItem(  cnt,  displayName,  nImage  );
				  index  ++  ;	ListCtrl.SetItemText(  cnt,  index,  CString(  qyGetDesByType1(  CONST_qyLangTable_en,  osSp.uiLangId  )  ).GetBuffer(  0  )  );  
				  index  ++  ;  ListCtrl.SetItemText(  cnt,  index,  CString(  osSp.url  ).GetBuffer(  0  )  );
				  index  ++  ;	ListCtrl.SetItemText(  cnt,  index,  CString(  osSp.des0  ).GetBuffer(  0  )  );
				  ListCtrl.SetItemData(  cnt,  osSp.id  );
				
				  cnt  ++  ;
							  
			 }

			 rs.Close(  );
						
		 }
						 	
			}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "displayListContent_cfgSpOs failed."  )  );
		   goto  errLabel;
	}
		 
	 iRet  =  0;

errLabel:
	
	 if  (  rs.IsOpen(  )  )  rs.Close(  );
	
	 return  iRet;		

}

 int  displayListContent_cfgSpServicePack(  QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_OBJINDEX_RCD  *  pObjIndex  )
{
	 int								iRet					=			-1;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 CListCtrl						&	ListCtrl				=			pMcView->GetListCtrl();
	 //  LV_ITEM							lvi;
	 int								index					=			0;
	 //  QY_MCROOTLIST_DISPLAYCFG		*	pCfg					=			&pCfgParam->u.rootList;
	 TCHAR								sqlBuf[CONST_qyMaxSqlBufLen  +  1];
	 CRecordset							rs(  (  CDatabase  *  )pQyMc->gui.pDb  );   int	 nFields;
	 CDBVariant							varVals[20];
	 QY_OSSP_RCD						osSp;
	 int								cnt						=			0;
	 int								nImage;
	 TCHAR								displayName[512];
	 
	 try  {		

		 if  (  pObjIndex->objType  ==  CONST_objType_cfgSpServicePack  )  {
					 
			 pMcView->delAllColumns(  );
			 if  (  !pMcView->bAddColumns(  CONST_spListColumns  )  )  goto  errLabel;
			 																//     0				1				  						
			 _sntprintf(  sqlBuf,  sizeof(  sqlBuf  )  /  sizeof(  sqlBuf[0]  ),  _T(  "SELECT qyOsSpTab.id,  qyOsSpTab.iPlatformId,qyOsSpTab.uiLangId,qyOsSpTab.spName,qyOsSpTab.cusName,qyOsSpTab.url,qyOsSpTab.des0 from qyOsSpTab where qyOsSpTab.iType=%d and qyOsSpTab.iPlatformId=%d and qyOsSpTab.uiLangId=%d and qyOsSpTab.servicePack='%s' order by qyOsSpTab.spName"  ),  CONST_spType_sp,  pObjIndex->objId0,  pObjIndex->objId1,  pObjIndex->objIdStr0  );
 			 traceLogA(  "%s",  sqlBuf  );
 			 if  (  !rs.Open( CRecordset::forwardOnly,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  {
				 traceLogA(  "rs open() failed."  );  goto  errLabel;
			 }
			 nFields  =  rs.GetODBCFieldCount(  );					 
					 
			 for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {

				  memset(  &osSp,  0,  sizeof(  osSp  )  );
				  				   
	  			  for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   				  
	  			  index  =  0;  MACRO_sqlLong(  varVals[index],  osSp.id  );
				  index  ++  ;	MACRO_sqlLong(  varVals[index],  osSp.iPlatformId  );
				  index  ++  ;	MACRO_sqlLong(  varVals[index],  osSp.uiLangId  );
				  index  ++  ;	MACRO_sqlStr(  varVals[index],  osSp.spName,  sizeof(  osSp.spName  )  /  sizeof(  osSp.spName[0]  )  );
				  index  ++  ;	MACRO_sqlStr(  varVals[index],  osSp.cusName,  sizeof(  osSp.cusName  )  /  sizeof(  osSp.cusName[0]  )  );
				  index  ++  ;	MACRO_sqlStr(  varVals[index],  osSp.url,  sizeof(  osSp.url  )  /  sizeof(  osSp.url[0]  )  );
				  index  ++  ;	MACRO_sqlStr(  varVals[index],  osSp.des0,  sizeof(  osSp.des0  )  /  sizeof(  osSp.des0[0]  )  );
				  				  
				  _sntprintf(  displayName,  sizeof(  displayName  )  /  sizeof(  displayName[0]  ),  _T(  "%s"  ),  osSp.spName,  qyGetDesByType1(  CONST_qyLangTable_en,  osSp.uiLangId  )  );
						  
				  nImage  =  pQyMc->cfg.image.nImage_sp;
				
				  index  =  0;	ListCtrl.InsertItem(  cnt,  CString(  displayName  ).GetBuffer(  0  ),  nImage  );
				  index  ++  ;	ListCtrl.SetItemText(  cnt,  index,  CString(  osSp.cusName  ).GetBuffer(  0  )  );
				  index  ++  ;	ListCtrl.SetItemText(  cnt,  index,  CString(  qyGetDesByType1(  CONST_qyLangTable_en,  osSp.uiLangId  )  ).GetBuffer(  0  )  );
				  index  ++  ;	ListCtrl.SetItemText(  cnt,  index,  CString(  osSp.url  ).GetBuffer(  0  )  );
				  index  ++  ;	ListCtrl.SetItemText(  cnt,  index,  CString(  osSp.des0  ).GetBuffer(  0  )  );
				  ListCtrl.SetItemData(  cnt,  osSp.id  );
				
				  cnt  ++  ;
							  
			 }

			 rs.Close(  );
						
		 }
						 	
			}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "displayListContent_cfgSpServicePack failed."  )  );
		   goto  errLabel;
	}
		 
	 iRet  =  0;

errLabel:
	
	 if  (  rs.IsOpen(  )  )  rs.Close(  );
	
	 return  iRet;		

}

  //  2013/02/21,  2004/05/14添加
 BOOL  bNetMcViewPcSpSpecialListFunc(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  osName,  LPCTSTR  spName  )
{
	BOOL					bRet				=	FALSE;
	QY_MC				*	pQyMc				=	QY_GET_GBUF(  );
	CQyMcApp			*	pApp				=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct		=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpPcSpSpecialListQueryStruct  );
	TCHAR					sqlBuf[CONST_qyMaxSqlBufLen  +  1]	=	_T(  ""  );
	int						iType_qnmTmpTab		=	pQyMc->cfg.iType_qnmTmpTab;
	char					timeBuf[CONST_qyTimeLen  +  1];

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	if  (  !spName  ||  !spName[0]  )  {
		traceLogA(  "spName is needed"  );  goto  errLabel;
	}

	getCurTime(  timeBuf  );
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qnmTmpTab(iType,queryTime,mac,col0,des0,des1) select distinct %d,'%s',qyPcSpTab.mac0,qyPcSpTab.spName,qyPcSpTab.servicePack,qyPcSpTab.lastTime from qyPcSpTab left join qyPcTab on qyPcSpTab.mac0=qyPcTab.mac0 where qyPcSpTab.spName='%s'"    ), iType_qnmTmpTab,  CString(  timeBuf  ),  spName  );
	if  (  osName  &&  osName[0]  )  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s and qyPcTab.osName='%s'"  ),  sqlBuf,  osName  );
	if  (  !bQyExecSql(  pObjDb->pDb,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  goto  errLabel;
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qnmTmpTab(iType,queryTime,mac,des0) select distinct %d,'%s',qyPcTab.mac0,qyPcTab.servicePack from qyPcTab where qyPcTab.mac0 not in (select qnmTmpTab.mac from qnmTmpTab where qnmTmpTab.iType=%d and qnmTmpTab.queryTime='%s')"  ), iType_qnmTmpTab,  CString(  timeBuf  ),  iType_qnmTmpTab,  CString(  timeBuf  )  );
	if  (  osName  &&  osName[0]  )  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s and qyPcTab.osName='%s'"  ),  sqlBuf,  osName  );
	if  (  !bQyExecSql(  pObjDb->pDb,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_netMcPcSpList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;
	/*
	for  (  tmpSel.u.query.nSqlFields  =  0;  pQueryStruct->pSql[tmpSel.u.query.nSqlFields].type  !=  -1;  tmpSel.u.query.nSqlFields  ++  );
	//MACRO_getnItems(  pQueryStruct->pSql,  type,  tmpSel.u.query.nSqlFields  );
	if  (  tmpSel.u.query.nSqlFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nSqlFields is too big"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.sqlColumns,  pQueryStruct->pSql,  (  tmpSel.u.query.nSqlFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	MACRO_getnItems(  pQueryStruct->pDisplay,  type,  tmpSel.u.query.nFields  );
	if  (  tmpSel.u.query.nFields  >  CONST_qyMaxQueryCols  )  {
		MACRO_qyAssert(  0,  "nFields is too big"  );  goto  errLabel;
	}
	memcpy(  tmpSel.u.query.columns,  pQueryStruct->pDisplay,  (  tmpSel.u.query.nFields  +  1  )  *  sizeof(  QY_COLUMNINFO  )  );
	*/
	if  (  setQueryColumns(  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  sizeof(  tmpSel.u.query.fromPart  )  /  sizeof(  TCHAR  ),  _T(  "from ((qyPcTab left join qyPcRegInfoTab on qyPcTab.mac0=qyPcRegInfoTab.mac0) left join qnmTmpTab on (qyPcTab.mac0=qnmTmpTab.mac )) left join qyCusNameTab on (qnmTmpTab.col0=qyCusNameTab.objName0)"  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  sizeof(  tmpSel.u.query.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "qnmTmpTab.iType=%d and qnmTmpTab.queryTime='%s' and (qyCusNameTab.iType=%d or qyCusNameTab.iType is null)"  ),  iType_qnmTmpTab,  CString(  timeBuf  ),  CONST_cusNameType_pcSp  );
	_sntprintf(  tmpSel.u.query.sortPart,  sizeof(  tmpSel.u.query.sortPart  )  / sizeof(  TCHAR  ),  _T(  "qyPcRegInfoTab.col0"  )  );
	
	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	tmpSel.u.query.pfProcEvent  =  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId  =  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos  =  19;				

	_sntprintf(  tmpSel.u.query.docName,  sizeof(  tmpSel.u.query.docName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  sizeof(  tmpSel.u.query.postDocName  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_patchList  )  );
	
	bRet  =  pApp->bNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}