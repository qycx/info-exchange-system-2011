
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"qyWmComm.h"

#include	"qyMc.h"
#include	"qyMcDoc.h"
#include	"leftView.h"
//  #include	"qyMcView.h"
#include	"qyCusResTemp.h"
#include	"qmcVideoCapture.h"
#include	"qmcDynBmp.h"
#include	"qmcVWall.h"
//  #include	"DlgDynBmps.h"
//  #include	"dlgTalk.h"
#include	"qyDynLib.h"
#include	"qmcCmdProc.h"
//
#include	"isCmdConst.h"
//
//  #include	"DlgQnmEditPcUsrInfo.h"
#include	"myDb.h"

//  #include	"DlgImObjRule.h"
//  #include	"DlgPropMessenger.h"
//  #include	"DlgPropImGrp.h"
//  #include	"DlgPropImMsg.h"
//  #include	"DlgPropImTask.h"
//  #include	"DlgSelect_isCli.h"
#include	"myDb.h"


 BOOL  bItemExists_imObjs(  QY_OBJ_DB  *  pObjDb,  CLeftView  *  pLeftView,  HTREEITEM  htItem  );

 //  getObjId(  )?
  int  displayContent_imObjs_isClient(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int							iRet				=				-1;
	 QY_MC						*	pQyMc				=				QY_GET_GBUF(  );
	 CLeftView					*	pLeftView			=				(  CLeftView  *  )p0;
	 CTreeCtrl					*	m_TreeCtrl			=				&pLeftView->GetTreeCtrl(  );
	 CQyMcDoc					*	pDoc				=				pLeftView->GetDocument(  );
	 if  (  pDoc->m_docStruct.iDocType  !=  CONST_qyDocType_mcRootTree  )  return  -1;
	 QY_OBJ_DB					*	pObjDb				=				getProcedObjDb(  0,  pDoc->m_docStruct.u.treeList.tree.iDsnIndex  );
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  -1;
	 CRecordset					rs(  (  CDatabase  *  )pObjDb->pDb  );
	 CDBVariant					varVals[20];
	 int						index, nFields;
	 // CODBCFieldInfo			tmpFieldInfo;
	 TCHAR						sqlBuf[QY_SQLBUFLEN  +  1];
	 QY_MESSENGER_REGINFO		regInfo;
	 HTREEITEM					tmphtItem				=				NULL;
	 TCHAR						displayName[512]		=				_T(  ""  );		
	 int						iObjId					=				0;
	 int						nImage,  nSelectedImage;
	 int						iTopFieldId				=				0;
	 char						topLevelColName[128]	=				"'";
	 char					*	p						=				NULL;
	 int						i;
	 int						iObjType				=				0;
	 COMMON_PARAM				commonParam;
	 TCHAR						tBuf[1024];
	 CString					str;
	 int						iServiceId				=				CONST_qyServiceId_mis;
	 QY_SERVICEGUI_INFO		*	pSci					=				getServiceGuiInfo(  pQyMc,  iServiceId  );
	 if  (  !pSci  )  return  -1;
	 MC_VAR_isCli				*	pProcInfo				=				(  MC_VAR_isCli  *  )pSci->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 MIS_CNT				*	pMisCnt					=				getMisCntByName(  pQyMc,  NULL,  pLeftView->m_var.misServName  );
	 if  (  !pMisCnt  )  return  -1;
		  

	 if  (  !pLeftView->m_var.bInitialized  ||  !pLeftView->m_var.htMyRootItem  )  goto  errLabel;
	 
	 try  {

		  		  
		  //  先将不存在的节点删除
		  myTrimTree(  pObjDb,  pLeftView,  pLeftView->m_var.htMyRootItem,  (  PF_bCommonHandler  )bItemExists_imObjs  );  

		  if  (  !bGetTopParams(  &iTopFieldId,  &iObjType  )  )  goto  errLabel;
		  if  (  (  i  =  getRegIndexByFieldId(  iTopFieldId  )  )  <  0  )  goto  errLabel;
		  
		  //  下面增加新增的节点
		  //
		  //  先将注册用户的单位放入视图
		  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select distinct B.col%d from qyImObjRegInfoTab as B  where B.misServName=%s %s %s order by B.col%d"  ),  i,  getDbValStr(  pSci->cfg.iDbType,  CONST_iDataType_misServName,  pMisCnt->cfg.misServName  ),  (  pDoc->m_docStruct.u.treeList.tree.wherePart[0]  ?  _T(  "and"  )  :  _T(  ""  )  ),  pDoc->m_docStruct.u.treeList.tree.wherePart,  i  );
		  if  (  !rs.Open( CRecordset::forwardOnly,  sqlBuf  )  )  {
		 	  debugLog(  "rs open() failed."  );  goto  errLabel;
		  }
	  	
		  nFields  =  rs.GetODBCFieldCount(  );
		  //  rs.GetODBCFieldInfo(  index,  tmpFieldInfo  );
		  for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {
		
			   for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );

			   memset(  &regInfo,  0,  sizeof(  regInfo  )  );
			   regInfo.uiType  =  CONST_imCommType_messengerRegInfo;
			   MACRO_setFieldIdInRegInfo(  regInfo  );
			   //			   
			   if  (  (  i  =  getRegIndexByFieldId(  iTopFieldId  )  )  <  0  )  goto  errLabel;
					   			
								//  topLevelColName   
			   index  =  0;		MACRO_sqlStr(  varVals[index],  (  TCHAR  *  )regInfo.u.cols[i],  sizeof(  regInfo.u.cols[i]  )  /  sizeof(  TCHAR  )  );	//  注意这里，将regInfo的字段当缓冲用，2005/11/06
	 		   index  ++  ;		
			   			   
			   MACRO_makeCommonParam3(  0,  &regInfo,  0,  commonParam  );  
			   iObjId  =  getObjId(  pObjDb,  0,  pMisCnt->cfg.misServName,  iObjType,  &commonParam  );
			   if  (  iObjId  <  0  )  continue;

			   _sntprintf(  displayName,  sizeof(  displayName  )  /  sizeof(  displayName[0]  ),  _T(  "%s"  ),  regInfo.u.cols[i]  );
			   nImage  =  pQyMc->cfg.image.nImage_col2;  nSelectedImage  =  pQyMc->cfg.image.nImage_col3;
			   //  getSnmpObjImages(  pQyMc,  pObj,  &nImage,  &nSelectedImage  );

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
				   //  m_TreeCtrl->SortChildren(  pLeftView->m_var.htMyRootItem  );
				   
				   }
			   else  {				  
				     //  只刷新展开节点
					 TVITEM				tvItem;
					 
					 tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
					 tvItem.hItem  =  tmphtItem;
					 tvItem.pszText  =  tBuf;
					 tvItem.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );
					 m_TreeCtrl->GetItem(  &tvItem  );
					 
					 if  (  _tcsicmp(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
						 _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s"  ),  displayName  );
						 tvItem.iImage  =  nImage;
						 tvItem.iSelectedImage  =  nSelectedImage;
						 m_TreeCtrl->SetItem(  &tvItem  );
					 }

					 //  刷新展开节点
					 //  if  (  tvItem.state  &  TVIS_EXPANDED   )  pLeftView->bRefreshItem(  tmphtItem  );				   
					 if  (  pLeftView->m_TreeCtrl->ItemHasChildren(  tmphtItem  )  )  pLeftView->bRefreshItem(  tmphtItem  );				   

			   }

			   /*  以下是产生关联网络用的，在资产管理中暂时不用
			   if  (  pDoc->m_docStruct.u.treeList.tree.selectedSwitchMac[0]  
				   &&  !strcmpi(  pDoc->m_docStruct.u.treeList.tree.selectedSwitchMac,  pObj->mac  )  )
			   {
				   pLeftView->m_var.htInitialItem  =  tmphtItem;
			   }
			   */

		  }
		  rs.Close(  );

		  //
		  //
		  //  再为未注册用户增加一个"未注册用户组"并刷新这个组
		  //
		  iObjId  =  getObjId(  pObjDb,  0,  NULL,CONST_objType_unRegGrp,  NULL  );
		  if  (  iObjId  <  0  )  goto  errLabel;;

		  _sntprintf(  displayName,  sizeof(  displayName  )  /  sizeof(  displayName[0]  ),  _T(  "%s"  ),  CString(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_objIdStr_unRegGrp  )  )  );
		  nImage  =  pQyMc->cfg.image.nImage_col2;  nSelectedImage  =  pQyMc->cfg.image.nImage_col3;
				
		  if  (  !(  tmphtItem  =  pLeftView->FindItemData(  iObjId,  TRUE,  pLeftView->m_var.htMyRootItem  )  )  )  {
			  tmphtItem  =  m_TreeCtrl->InsertItem(  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE  |  TVIF_PARAM,  
													  displayName,  
													  nImage,  
													  nSelectedImage,  
													  TVIS_EXPANDPARTIAL,  
													  TVIS_STATEIMAGEMASK, 
													  iObjId,  
													  pLeftView->m_var.htMyRootItem,  
													  TVI_LAST  );
			   //  m_TreeCtrl->SortChildren(  pLeftView->m_var.htMyRootItem  );  //  
				   
			   }
		   else  {				  
			     //  只刷新展开节点
				 TVITEM				tvItem;
				 
				 tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
				 tvItem.hItem  =  tmphtItem;
				 tvItem.pszText  =  tBuf;
				 tvItem.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );
				 m_TreeCtrl->GetItem(  &tvItem  );
				 
				 if  (  _tcsicmp(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
					 _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s"  ),  displayName  );
					 tvItem.iImage  =  nImage;
					 tvItem.iSelectedImage  =  nSelectedImage;
					 m_TreeCtrl->SetItem(  &tvItem  );
				 }

				 //  刷新展开节点
				 //  if  (  tvItem.state  &  TVIS_EXPANDED   )  pLeftView->bRefreshItem(  tmphtItem  );				   
				 if  (  pLeftView->m_TreeCtrl->ItemHasChildren(  tmphtItem  )  )  pLeftView->bRefreshItem(  tmphtItem  );				   

		   }

		   //
		  //  再增加一个"组集合",并刷新这个组
		  //
		  iObjId  =  getObjId(  pObjDb,  0,  NULL,CONST_objType_imGrps,  NULL  );
		  if  (  iObjId  <  0  )  goto  errLabel;;

		  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s"  ),  CString(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_objIdStr_imGrps  )  )  );
		  nImage  =  pQyMc->cfg.image.nImage_imGrps;  nSelectedImage  =  pQyMc->cfg.image.nImage_selectedImGrps;
				
		  if  (  !(  tmphtItem  =  pLeftView->FindItemData(  iObjId,  TRUE,  pLeftView->m_var.htMyRootItem  )  )  )  {
			  tmphtItem  =  m_TreeCtrl->InsertItem(  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE  |  TVIF_PARAM,  
													  displayName,  
													  nImage,  
													  nSelectedImage,  
													  TVIS_EXPANDPARTIAL,  
													  TVIS_STATEIMAGEMASK, 
													  iObjId,  
													  pLeftView->m_var.htMyRootItem,  
													  TVI_LAST  );
			   //  m_TreeCtrl->SortChildren(  pLeftView->m_var.htMyRootItem  );  //  
				   
			   }
		   else  {				  
			     //  只刷新展开节点
				 TVITEM				tvItem;
				 
				 tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
				 tvItem.hItem  =  tmphtItem;
				 tvItem.pszText  =  tBuf;
				 tvItem.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );
				 m_TreeCtrl->GetItem(  &tvItem  );
				 
				 if  (  _tcsicmp(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
					 _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s"  ),  displayName  );
					 tvItem.iImage  =  nImage;
					 tvItem.iSelectedImage  =  nSelectedImage;
					 m_TreeCtrl->SetItem(  &tvItem  );
				 }

				 //  刷新展开节点
				 //  if  (  tvItem.state  &  TVIS_EXPANDED   )  pLeftView->bRefreshItem(  tmphtItem  );				   
				 if  (  pLeftView->m_TreeCtrl->ItemHasChildren(  tmphtItem  )  )  pLeftView->bRefreshItem(  tmphtItem  );				   

		   }



		   //
		   //  下面增加一个我节点
		   //
		   iObjId  =  getObjId(  pObjDb,  0,  NULL,CONST_objType_me,  pMisCnt->cfg.misServName  );
		   if  (  iObjId  <  0  )  goto  errLabel;

		   
		   QM_OBJQ_MEM				mem;
		   unsigned  short			usRunningStatus;
		   //
		   _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s(%I64u)"  ),  pMisCnt->displayName,  pMisCnt->idInfo.ui64Id  );
		   if  (  findQMemByKey(  0,  pMisCnt->pObjQ,  &pMisCnt->idInfo,  &mem  )  )  usRunningStatus  =  CONST_usRunningStatus_offline;
		   else  {
			     QMEM_MESSENGER_CLI	*	pQMem;
			     pQMem  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;
				 usRunningStatus  =  pQMem->usRunningStatus;
		   }
		   //
		   getMessengerImages(  pQyMc,  usRunningStatus,  &nImage,  &nSelectedImage  );
				
		   if  (  !(  tmphtItem  =  pLeftView->FindItemData(  iObjId,  TRUE,  pLeftView->m_var.htMyRootItem  )  )  )  {
			   tmphtItem  =  m_TreeCtrl->InsertItem(  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE  |  TVIF_PARAM,  
													  displayName,  
													  nImage,  
													  nSelectedImage,  
													  TVIS_EXPANDPARTIAL,  
													  TVIS_STATEIMAGEMASK, 
													  iObjId,  
													  pLeftView->m_var.htMyRootItem,  
													  TVI_LAST  );
			   //  m_TreeCtrl->SortChildren(  pLeftView->m_var.htMyRootItem  );  //  
				   
			   QMOBJQ_PARAM_MISCLIENT	qmObjQParam;
			   //
			   memset(  &qmObjQParam,  0,  sizeof(  qmObjQParam  )  );
			   //  uiType
			   qmObjQParam.pSci  =  pSci;
			   qmObjQParam.pMisCnt  =  pMisCnt;
			   qmObjQParam.iObjType  =  CONST_objType_me;
			   
			   if  (  addToDisplayedObjQ(  &pLeftView->m_var.displayCtx,  &qmObjQParam,  pLeftView->m_hWnd,  tmphtItem  )  )  goto  errLabel;

				}
		   else  {				  
			     //  只刷新展开节点
				 TVITEM				tvItem;
				 
				 tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
				 tvItem.hItem  =  tmphtItem;
				 tvItem.pszText  =  tBuf;
				 tvItem.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );
				 m_TreeCtrl->GetItem(  &tvItem  );
				 
				 if  (  _tcsicmp(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
					 _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "%s"  ),  displayName  );
					 tvItem.iImage  =  nImage;
					 tvItem.iSelectedImage  =  nSelectedImage;
					 m_TreeCtrl->SetItem(  &tvItem  );
				 }

				 //  刷新展开节点
				 //  if  (  tvItem.state  &  TVIS_EXPANDED   )  pLeftView->bRefreshItem(  tmphtItem  );				   
				 if  (  pLeftView->m_TreeCtrl->ItemHasChildren(  tmphtItem  )  )  pLeftView->bRefreshItem(  tmphtItem  );				   

		   }


		   

	 	}
	 catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "displayContent_imObjs_isClient failed."  )  );
		   goto  errLabel;
	 }

	 iRet				=				0;

errLabel:

	if  (  rs.IsOpen(  )  )  rs.Close(  );
	
	return  iRet;		

}

 int  refreshItem_imObjs_isClient(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int								iRet				=				-1;
	 QY_MC							*	pQyMc				=				QY_GET_GBUF(  );
	 CLeftView						*	pLeftView			=				(  CLeftView  *  )p0;
	 HTREEITEM							htItem				=				(  HTREEITEM  )p1;
	 CTreeCtrl						*	m_TreeCtrl			=				&pLeftView->GetTreeCtrl(  );
	 CQyMcDoc						*	pDoc				=				pLeftView->GetDocument(  );
	 if  (  pDoc->m_docStruct.iDocType  !=  CONST_qyDocType_mcRootTree  )  return  -1;
	 QY_OBJ_DB						*	pObjDb				=				getProcedObjDb(  0,  pDoc->m_docStruct.u.treeList.tree.iDsnIndex  );
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  -1;
	 //
	 int								curiObjId,  iObjId,  iObjType;
	 QY_MESSENGER_REGINFO				regInfo;
	 QY_MESSENGER_INFO					messengerInfo;
	 //
	 QY_OBJINDEX_RCD					objIndex;
	 CRecordset							rs( ( CDatabase * )pObjDb->pDb );
	 CDBVariant							varVals[10];
	 int								index,  nFields;
	 TCHAR								sqlBuf[1024]		=				_T(  ""  );
	 TCHAR								whereClause[1024]	=				_T(  ""  );
	 int								nImage,  nSelectedImage;
	 HTREEITEM							tmphtItem			=				NULL;
	 TCHAR								displayName[512]	=				_T(  ""  );		
	 int								indexDisplayed,  indexToDisplay;
	 COMMON_PARAM						commonParam;
	 TCHAR								tBuf[256];
	 char								buf[256];
	 char								ip12Buf[128]		=				"";
	 //
	 int								iServiceId			=				CONST_qyServiceId_mis;
	 QY_SERVICEGUI_INFO			*	pSci					=				getServiceGuiInfo(  pQyMc,  iServiceId  );
	 if  (  !pSci  )  return  -1;
	 MC_VAR_isCli					*	pProcInfo				=				(  MC_VAR_isCli  *  )pSci->pVar;
	 if  (  !pProcInfo  )  return  -1;
	 MIS_CNT						*	pMisCnt				=				getMisCntByName(  pQyMc,  NULL,  _T(  ""  )  );
	 if  (  !pMisCnt  )  return  -1;
	 CQnmDb								tmpObjDb;

	 QM_dbFuncs		*	pDbFuncs	=	QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	if  (  !tmpObjDb.getAvailableDb(  pObjDb->iDsnIndex  )  )  {
		 traceLogA(  "得不到可用的连接数了"  );  goto  errLabel;
	 }
	 
	 if  (  htItem  ==  pLeftView->m_var.htMyRootItem  )  {
		 iRet  =  0;  goto  errLabel;
	 }


	 curiObjId  =  m_TreeCtrl->GetItemData(  htItem  );
	 if  (  g_dbFuncs.pf_getObjIndex(  pObjDb,  curiObjId,  &objIndex  )  )  goto  errLabel;

	 try  {

		  if  (  objIndex.objType  ==  CONST_objType_zb
			  ||  objIndex.objType  ==  CONST_objType_bb  
				||  objIndex.objType  ==  CONST_objType_dw  )  
		  {
			  if  (  getSthForObjs(  pObjDb,  _T(  "B"  ),  &objIndex,  &indexDisplayed,  &indexToDisplay,  &iObjType,  whereClause,  mycountof(  whereClause  )  )  )  goto  errLabel;
			  _sntprintf(  sqlBuf,  sizeof(  sqlBuf  )  /  sizeof(  sqlBuf[0]  ),  _T(  "select distinct B.col%d from qyImObjRegInfoTab as B"  ),  indexToDisplay  );
			  _sntprintf(  sqlBuf,  sizeof(  sqlBuf  )  /  sizeof(  sqlBuf[0]  ),  _T(  "%s where misServName=%s %s %s"  ),  sqlBuf,  getDbValStr(  pSci->cfg.iDbType,  CONST_iDataType_misServName,  objIndex.servName  ),  (  whereClause[0]  ?  _T(  "and"  )  :  _T(  ""  )  ),  whereClause  );
			  _sntprintf(  sqlBuf,  sizeof(  sqlBuf  )  /  sizeof(  sqlBuf[0]  ),  _T(  "%s order by B.col%d"  ),  sqlBuf,  indexToDisplay  );

			  if  (  !rs.Open( CRecordset::forwardOnly,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  {  traceLogA(  "rs open() failed,  sqlBuf is %s.",  sqlBuf  );  goto  errLabel;  }
			  if  (  (  nFields  =  rs.GetODBCFieldCount(  )  )  >  sizeof(  varVals  )  /  sizeof(  varVals[0]  )  )  goto  errLabel;
			  //  rs.GetODBCFieldInfo(  index,  tmpFieldInfo  );
			  for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {
			  
				  memset(  &regInfo,  0,  sizeof(  regInfo  )  ); 
				  regInfo.uiType  =  CONST_imCommType_messengerRegInfo;
				  MACRO_setFieldIdInRegInfo(  regInfo  );
			  
				  for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   				  
				  index  =  0;  MACRO_sqlStr(  varVals[index],  (  TCHAR  *  )regInfo.u.cols[indexToDisplay],  sizeof(  regInfo.u.cols[indexToDisplay]  )  /  sizeof(  TCHAR  )  );
				  index  ++  ;	//  
				  if  (  index  >  sizeof(  varVals  )  /  sizeof(  varVals[0]  )  )  goto  errLabel;

				 //   _snprintf(  colBuf,  sizeof(  colBuf  ),  "%S",  regInfo.u.cols[indexToDisplay]  );

				  MACRO_makeCommonParam3(  (  void  *  )curiObjId,  &regInfo,  0,  commonParam  );
				  if  (  (  iObjId  =  getObjId(  pObjDb,  0,  objIndex.servName,  iObjType,  &commonParam  )  )  <  0  )  continue;

				  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s"  ),  regInfo.u.cols[indexToDisplay]  );
				  nImage  =  pQyMc->cfg.image.nImage_col3;  nSelectedImage  =  pQyMc->cfg.image.nImage_selectedCol3;

				  if  (  myAddOrRefreshTreeItem(  pLeftView,  htItem,  iObjId,  displayName,  nImage,  nSelectedImage  )  )  goto  errLabel;

			  }		//  end of for  (  ;  ;  )					 

			  }
	 	  else  if  (  objIndex.objType  ==  CONST_objType_bm  )  {
			        if  (  getSthForObjs(  pObjDb,  _T(  "B"  ),  &objIndex,  &indexDisplayed,  &indexToDisplay,  &iObjType,  whereClause,  mycountof(  whereClause  )  )  )  goto  errLabel;
					_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "SELECT distinct B.misServName,B.idStr,B.col%d from qyImObjRegInfoTab as B left join qyImObjTab as A on (A.misServName=B.misServName and A.idStr=B.idStr)"  ),  indexToDisplay  );
					_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s %s %s"  ),  sqlBuf,  (  whereClause[0]  ?  _T(  "where"  )  :  _T(  ""  )  ),  whereClause  );
					_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s order by B.col%d"  ),  sqlBuf,  indexToDisplay  );
					traceLogA(  "%S",  sqlBuf  );
					if  (  !rs.Open( CRecordset::forwardOnly,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  {  traceLogA(  "rs open() failed."  );  goto  errLabel;  }
	  			 	nFields  =  rs.GetODBCFieldCount(  );
		 			//  rs.GetODBCFieldInfo(  index,  tmpFieldInfo  );
		 			for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {
			  		
			  			 memset(  &regInfo,  0,  sizeof(  regInfo  )  ); 
						 regInfo.uiType  =  CONST_imCommType_messengerRegInfo;
						 MACRO_setFieldIdInRegInfo(  regInfo  );
			  
						 for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );

						 index  =  0;  {  MACRO_sqlStr(  varVals[index],  regInfo.addr.misServName,  mycountof(  regInfo.addr.misServName  )  );   }
						 index  ++  ;  {  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &regInfo.addr.idInfo  );  }
						 index  ++  ;  MACRO_sqlStr(  varVals[index],  (  TCHAR  *  )regInfo.u.cols[indexToDisplay],  sizeof(  regInfo.u.cols[indexToDisplay]  )  /  sizeof(  TCHAR  )  );
						 index  ++  ;	
						 		
						 
						 if  (  (  iObjId  =  getObjId(  pObjDb,  0,  NULL,  iObjType,  &regInfo  )  )  <  0  )  continue;

			  
						 //  先用regInfo填充一下messengerInfo, 因为下面的pClient只能指向messengerInfo
						 memset(  &messengerInfo,  0,  sizeof(  messengerInfo  )  );
						 //
						 lstrcpyn(  messengerInfo.misServName,  pMisCnt->cfg.misServName,  mycountof(  messengerInfo.misServName  )  );
						 messengerInfo.idInfo.ui64Id  =  regInfo.addr.idInfo.ui64Id;
                         

						 //  2007/06/03, 这里要加入内存中的管理队列						
						 QMOBJQ_PARAM_MISCLIENT		qmObjQParam;
						//
						memset(  &qmObjQParam,  0,  sizeof(  qmObjQParam  )  );
						//  uiType
						qmObjQParam.pSci  =  pSci;
						qmObjQParam.pMisCnt  =  pMisCnt;
						qmObjQParam.pDb  =  tmpObjDb.getAvailableDb(  pObjDb->iDsnIndex  );
						qmObjQParam.iDbType  =  pObjDb->cfg.iDbType;
						qmObjQParam.iObjType  =  CONST_objType_messenger;
						qmObjQParam.pClient  =  &messengerInfo;

						if  (  regInfo.u.cols[indexToDisplay][0]  )  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s"  ),  regInfo.u.cols[indexToDisplay]  );
						else  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "(%I64u)"  ),  regInfo.addr.idInfo.ui64Id  );

			  			 nImage  =  pQyMc->cfg.image.nImage_col4;  nSelectedImage  =  pQyMc->cfg.image.nImage_selectedCol4;

			  			 if  (  myAddOrRefreshTreeItem(  pLeftView,  htItem,  iObjId,  displayName,  nImage,  nSelectedImage,  &qmObjQParam  )  )  goto  errLabel;

		 			}					 
		
				  }
	 	  else  if  (  objIndex.objType  ==  CONST_objType_unRegGrp  )  {
	
					_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "SELECT qyImObjTab.misServName,qyImObjTab.idStr,qyImObjTab.ip from qyImObjTab where qyImObjTab.misServName=%s and qyImObjTab.uiType not in(%d) and qyImObjTab.idStr not in( select qyImObjRegInfoTab.idStr from qyImObjRegInfoTab) order by qyImObjTab.ip"  ),  getDbValStr(  pSci->cfg.iDbType,  CONST_iDataType_misServName,  objIndex.servName  ),  CONST_objType_imGrp  );
					traceLogA(  "%S",  sqlBuf  );
					if  (  !rs.Open( CRecordset::forwardOnly,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  {
						traceLogA(  "rs open() failed."  );  goto  errLabel;
					}
	  			 
					nFields  =  rs.GetODBCFieldCount(  );
					//  rs.GetODBCFieldInfo(  index,  tmpFieldInfo  );
					for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {

						memset(  &messengerInfo,  0,  sizeof(  messengerInfo  )  );

						for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   				  
						index  =  0;	//  qyImObjTab.misServName
						MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  messengerInfo.misServName,  tBuf,  mycountof(  messengerInfo.misServName  )  );
						index  ++  ;	//  qyImObjTab.idStr
						MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );  if  (  !idStr2Info(  buf,  &messengerInfo.idInfo  )  )  goto  errLabel;
						index  ++  ;	//  qyImObjTab.ip
						MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12Buf,  sizeof(  ip12Buf  )  );  qyIp12ToStd(  ip12Buf,  messengerInfo.ip  );  
						index  ++  ;	//  

						if  (  messengerInfo.idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  continue;
						
						iObjId  =  getObjId(  pObjDb,  0,  NULL,CONST_objType_messenger,  &messengerInfo.idInfo  );
						if  (  iObjId  <  0  )  continue;

						//  2007/06/03, 这里要加入内存中的管理队列
						QMOBJQ_PARAM_MISCLIENT		qmObjQParam;
						//
						memset(  &qmObjQParam,  0,  sizeof(  qmObjQParam  )  );
						//  uiType
						qmObjQParam.pSci  =  pSci;
						qmObjQParam.pMisCnt  =  pMisCnt;
						qmObjQParam.pDb  =  tmpObjDb.getAvailableDb(  pObjDb->iDsnIndex  );
						qmObjQParam.iDbType  =  pObjDb->cfg.iDbType;
						qmObjQParam.iObjType  =  CONST_objType_messenger;
						qmObjQParam.pClient  =  &messengerInfo;
						
						_sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "(%I64u)"  ),  messengerInfo.idInfo.ui64Id  );
						nImage  =  pQyMc->cfg.image.nImage_selectedMessenger;  nSelectedImage  =  pQyMc->cfg.image.nImage_selectedMessenger;
						//  getSnmpPortImages(  pQyMc,  &switchPort,  &nImage,  &nSelectedImage  );

						if  (  myAddOrRefreshTreeItem(  pLeftView,  htItem,  iObjId,  displayName,  nImage,  nSelectedImage,  &qmObjQParam  )  )  goto  errLabel;

					}					 

				}
		  else  if  (  objIndex.objType  ==  CONST_objType_syr  )  {
			        QY_MESSENGER_ID  idInfo;
					//
			        myTChar2Str(  objIndex.objIdStr0,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &idInfo  );
			        if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pObjDb->pDb,  pSci->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  pMisCnt->cfg.misServName,  &idInfo,  0,  &messengerInfo,  &regInfo,  NULL,  NULL  )  )  goto  errLabel;  

					//  2007/06/03, 这里要加入内存中的管理队列						
					QMOBJQ_PARAM_MISCLIENT		qmObjQParam;
					//
					memset(  &qmObjQParam,  0,  sizeof(  qmObjQParam  )  );
					//  uiType
					qmObjQParam.pSci  =  pSci;
					qmObjQParam.pMisCnt  =  pMisCnt;
					qmObjQParam.pDb  =  tmpObjDb.getAvailableDb(  pObjDb->iDsnIndex  );
					qmObjQParam.iDbType  =  pObjDb->cfg.iDbType;
					qmObjQParam.iObjType  =  CONST_objType_messenger;
					qmObjQParam.pClient  =  &messengerInfo;

					if  (  postRecentFriend(  qmObjQParam.pSci,  qmObjQParam.pMisCnt,  &qmObjQParam.pClient->idInfo,  0  )  )  traceLogA(  "postRecentFriend failed"  );  

		 			}
		  else  if  (  objIndex.objType  ==  CONST_objType_messenger  )  {

				  }
 
		  else  if  (  objIndex.objType  ==  CONST_objType_me  )  {

				}
		  else  if  (  objIndex.objType  ==  CONST_objType_imGrps  )  {
	
					IM_GRP_INFO		grpInfo;

					_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "SELECT qyImObjTab.misServName,qyImObjTab.idStr,qyImGrpInfoTab.name from qyImObjTab left join qyImGrpInfoTab on (qyImObjTab.misServName=qyImGrpInfoTab.misServName and qyImObjTab.idStr=qyImGrpInfoTab.idStr) where qyImObjTab.uiType in(%d) order by qyImGrpInfoTab.name"  ),  CONST_objType_imGrp  );
					traceLogA(  "%S",  sqlBuf  );
					if  (  !rs.Open( CRecordset::forwardOnly,  sqlBuf  )  )  {
						traceLogA(  "rs open() failed."  );  goto  errLabel;
					}
	  			 
					nFields  =  rs.GetODBCFieldCount(  );
					//  rs.GetODBCFieldInfo(  index,  tmpFieldInfo  );
					for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {
						
						for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   		
						memset(  &grpInfo,  0,  sizeof(  grpInfo  )  );

						index  =  0;	//  
						MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  grpInfo.misServName,  tBuf,  mycountof(  grpInfo.misServName  )  );
						index  ++  ;	//  
						MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );  if  (  !idStr2Info(  buf,  &grpInfo.idInfo  )  )  goto  errLabel;
						index  ++  ;	//  
						MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  grpInfo.name,  tBuf,  mycountof(  grpInfo.name  )  );
						index  ++  ;	//  
						
						iObjId  =  getObjId(  pObjDb,  0,  grpInfo.misServName,  CONST_objType_imGrp,  &grpInfo.idInfo  );
						if  (  iObjId  <  0  )  continue;
						
						_sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s"  ),  grpInfo.name  );
						nImage  =  pQyMc->cfg.image.nImage_imGrp;  nSelectedImage  =  pQyMc->cfg.image.nImage_selectedImGrp;

						if  (  myAddOrRefreshTreeItem(  pLeftView,  htItem,  iObjId,  displayName,  nImage,  nSelectedImage,  NULL  )  )  goto  errLabel;

					}					 

				}

		 

		}
	 catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "refreshItem_imObjs_isClient failed."  )  );
		   goto  errLabel;
	 }
	
	 iRet  =  0;

errLabel:
	 
	 if  (  rs.IsOpen(  )  )  rs.Close(  );

	 return  iRet;
}






















