
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"qyWmComm.h"

#include	"qyMc.h"
#include	"leftView.h"
#include	"qyMcView.h"
#include	"qyCusResTemp.h"
#include	"qmcVideoCapture.h"
#include	"qmcDynBmp.h"
#include	"qmcVWall.h"

//  #include	"DlgDynBmps.h"
//  #include	"dlgTalk.h"
#include	"qyDynLib.h"

#include	"DlgMessenger.h"

#include	"DlgPropMessenger.h"
#include	"DlgPropImGrp.h"
#include	"DlgPropImMsg.h"

#include	"DlgNum.h"

#include	"DlgCfgIpKnowledge.h"
#include	"DlgPropIpKnowledge.h"

#include	"DlgCfgPhoneMessenger.h"

#include	"DlgCfgGsmModem.h"

#include	"DlgWwwQmContact.h"

#include	"DlgCfgCustomerService.h"

#include	"DlgSelect.h"
#include	"DlgQnmEditPcUsrInfo.h"

#include	"DlgCfgStandardName.h"

#ifndef  __isCli__
  #include	"DlgImGrp.h"
#endif

#include	"myDb.h"

//  int  getSelectedToPath(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  BOOL  bPhoneGuest,  TCHAR  *  toPath,  unsigned  int  size  );
 
BOOL  bItemExists_imObjs(  QY_OBJ_DB  *  pObjDb,  CLeftView  *  pLeftView,  HTREEITEM  htItem  );
 BOOL  bViewImGrpMemList_isMgr(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
int  displayListContent_allTopCols(  QY_OBJ_DB  *  pObjDb,  CQyMcView  *  pMcView,  QY_MC_DISPLAYCFG	*	pCfgParam,  LPCTSTR  tabName_regInfo  ); 
int  displayListContent_bz(  QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  LPCTSTR  tabName_regInfo,  QY_OBJINDEX_RCD  *  pObjIndex  );
int  displayListContent_col3_is(  QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_OBJINDEX_RCD  *  pObjIndex  );
int  displayListContent_unRegGrp_is(  QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_OBJINDEX_RCD  *  pObjIndex  );
int  displayListContent_pc(  QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_OBJINDEX_RCD  *  pObjIndex  );
int  displayListContent_pcUsrInfo(  QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_OBJINDEX_RCD  *  pObjIndex  );
int  displayListContent_pcStatus(  QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_OBJINDEX_RCD  *  pObjIndex  );
int  displayListContent_pcOpNode(  QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_OBJINDEX_RCD  *  pObjIndex  );
int  displayListContent_imGrps(  QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_OBJINDEX_RCD  *  pObjIndex  );
int  displayListContent_imGrp(  QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_OBJINDEX_RCD  *  pObjIndex  );

int  initVar_isGui_mgr(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int						iErr				=	-1;
	 QY_MC					*	pQyMc				=	(  QY_MC  *  )p0;
	 QY_SERVICEGUI_INFO		*	pSci				=	(  QY_SERVICEGUI_INFO  *  )p1;
	 //  p2
	 int						i;
	 MC_VAR_isMgr			*	pProcInfo			=	(  MC_VAR_isMgr  *  )pSci->pVar;

	 //
	 QY_COMM_AUTHINFO_MIS	&	authInfo  =  pProcInfo->authInfo;

	 safeStrnCpy(  qnmVerStr(  pQyMc->iServiceId  ),  authInfo.ver,  mycountof(  authInfo.ver  )  );
	 authInfo.usLangId  =  pQyMc->env.usLangId;		 
	 authInfo.uiDevType  =  CONST_objType_pc;
	 //
	 //  safeStrnCpy(  CONST_qyNullMac,  (  char  *  )authInfo.macsInfo.macs[0],  mycountof(  authInfo.macsInfo.macs[0]  )  );	//  2007/10/10, 这样，就为管理员伪装了一个MAC
	 //  authInfo.macsInfo.nMacs  =  1;
	 //

	 //
	 _sntprintf(  pProcInfo->cfg.mgrQ.name,  mycountof(  pProcInfo->cfg.mgrQ.name  ),  _T(  "mgrQ"  )  );
	 _sntprintf(  pProcInfo->cfg.mgrQ.mutexName_prefix,  mycountof(  pProcInfo->cfg.mgrQ.mutexName_prefix  ),  _T(  "qMgrQ_isMgr"  )  );
	 pProcInfo->cfg.mgrQ.uiMaxCnt_semaTrigger  =  CONST_uiMaxCnt_semaTrigger_mgrQ_isMgr;
	 pProcInfo->cfg.mgrQ.uiMaxQNodes  =  CONST_uiMaxQNodes_mgrQ_isMgr;

	 if  (  initGenericQ(  &pProcInfo->cfg.mgrQ,  mallocMemory,  NULL,  0,  0,  freeMemory,  NULL,  NULL,  &pProcInfo->mgrQ  )  )  goto  errLabel; 


	 iErr  =  0;

errLabel:

	 return  iErr;

}


 int  exitVar_isGui_mgr(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 QY_MC					*	pQyMc				=	(  QY_MC  *  )p0;
	 QY_SERVICEGUI_INFO		*	pSci				=	(  QY_SERVICEGUI_INFO  *  )p1;
	 //  p2
	 MC_VAR_isMgr			*	pProcInfo			=	(  MC_VAR_isMgr  *  )pSci->pVar;

	 //
	 exitGenericQ(  &pProcInfo->mgrQ  );

	 return  0;

}

   int  closeOtherWnds_isMgr(  BOOL  *  pbOtherWndExists  )
{
	QY_MC				*	pQyMc		=		QY_GET_GBUF(  );
	MC_VAR_isMgr		*	pProcInfo	=		QY_GET_procInfo_isMgr(  );
	if  (  !pProcInfo  )  return  -1;
	int  i;

	for  (  i  =  0;  i  <  mycountof(  pProcInfo->hWnds_status_daemon  );  i  ++  )  { 
		  if  (  IsWindow(  pProcInfo->hWnds_status_daemon[i]  )  )  {		//  2011/01/08
			  SendMessage(  pProcInfo->hWnds_status_daemon[i],  WM_CLOSE,  0,  0  );
		  }	
	}

	return  0;
}

 BOOL  bViewImGrpAuthList_isMgr(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL					bRet	=	FALSE;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpImGrpAuthListQueryStruct_isMgr  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_imGrpAuthList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  NULL,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from ((qyImObjAuthTab left join qyImObjTab on (qyImObjTab.misServName=qyImObjAuthTab.misServName and qyImObjTab.idStr=qyImObjAuthTab.idStr)) left join qyImGrpInfoTab on(qyImObjAuthTab.misServName=qyImGrpInfoTab.misServName and qyImObjAuthTab.idStr=qyImGrpInfoTab.idStr ) )"  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "qyImObjAuthTab.uiType in(%d)"  ),  CONST_objType_imGrp  );
	if  (  wherePart  &&  wherePart[0]  ) _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s and %s"  ),  tmpSel.u.query.wherePart,  CString(  wherePart  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "qyImObjAuthTab.idStr"  )  );
	
	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	tmpSel.u.query.pfProcEvent  =  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId  =  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos  =  CONST_resId_popup_viewImGrpList_isMgr;						//  2003/12/17修改
	
	_sntprintf(  tmpSel.u.query.docName,  mycountof(  tmpSel.u.query.docName  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyImGrpAuthList  )  );
	
	bRet  =  pApp->bNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}

#if  10  //  2013/01/16
 BOOL  bViewImMsgListFunc_isMgr(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL					bRet			=	FALSE;
	QY_MC				*	pQyMc			=	QY_GET_GBUF(  );
	CQyMcApp			*	pApp			=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	//  QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  (  pObjDb->cfg.iAppType  ==  CONST_qyAppType_client  )  ?  CONST_resId_gpImMsgListQueryStruct_isClient  :  CONST_resId_gpImMsgListQueryStruct_isMgr  );
	//  TCHAR				*	pTabName		=	CONST_tabName_qyImMsgTab;
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;

#if 0
	tmpSel.u.query.type			=	CONST_qyQueryType_imMsgList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  NULL,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from (%s left join qyImObjRegInfoTab as B on (qyImMsgTab.misServName=B.misServName and qyImMsgTab.idStr_send=B.idStr) )"  ),  pTabName  );
	//
	if  (  wherePart  )  {
		if  (  tmpSel.u.query.wherePart[0]  )  _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s and"  ),  tmpSel.u.query.wherePart  );
		_sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s (%s)"  ),  tmpSel.u.query.wherePart,  CString(  wherePart  )  );
	}
	//
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "qyImMsgTab.firstTime desc"  )  );
#endif
	fillQyMcQuery(  pObjDb,  CONST_qyQueryType_imMsgList,  0,  wherePart,  &tmpSel.u.query  );
	
	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	tmpSel.u.query.pfProcEvent  =  netMc_procEvent;
	tmpSel.u.query.pfProcEvent_new  =  is_procEvent_new;
	tmpSel.u.query.uPopupMenuId  =  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos  =  (  pObjDb->cfg.iAppType  ==  CONST_qyAppType_client  )  ?  CONST_resId_popup_viewImTaskList_isClient  :  CONST_resId_popup_viewImTaskList_isMgr;		//  2003/12/17ÐÞ¸Ä
	tmpSel.u.query.uiDefaultCmd  =  ID_qyProp_imTask;

	if  (  docName  )  _sntprintf(  tmpSel.u.query.docName,  mycountof(  tmpSel.u.query.docName  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_msgList  )  );
	
	bRet  =  pApp->bNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}

BOOL  bViewImMsgListFunc_odbc(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	return   bViewImMsgListFunc_isMgr(  pObjDb,  docName,  wherePart );
}

 int  displayListContent_imObjs(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int								iRet					=	-1;
	 QY_MC							*	pQyMc					=	QY_GET_GBUF( );
	 CQyMcView						*	pMcView					=	(  CQyMcView  *  )p0;
	 QY_MC_DISPLAYCFG				*	pCfgParam				=	(  QY_MC_DISPLAYCFG  *  )p1;
	 QY_MCROOTTREE_SEL				*	pSel					=	(  QY_MCROOTTREE_SEL  *  )p2;
	 CListCtrl						&	ListCtrl				=	pMcView->GetListCtrl();
	 QY_OBJ_DB						*	pObjDb					=	getProcedObjDb(  0,  pSel->iDsnIndex  );
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  -1;
	 
	 	QM_dbFuncs  *  pDbFuncs  =  QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	 if  (  pCfgParam->m_iViewType  !=  QY_VIEWTYPE_MCROOTLIST  )  {
		 traceLogA( "CQyMcView::bDisplayContent(  ) ½öÓÐ¶ÔMcRootListµÄÊµÏÖ£¬ÇëÓÃÅÉÉúÀàÀ´ÖØÔØ´Ëº¯Êý¡£"  );
		 return  -1;
	 }
	 
	 ListCtrl.DeleteAllItems(  );

	 try  {		
	 
		  if  (  pMcView->var.m_superSel.u.rootTree.bRoot  )  {
			  
			  //  ÏÔÊ¾ËùÓÐµÄµ¥Î»
			  if  (  displayListContent_allTopCols(  pObjDb,  pMcView,  pCfgParam,  CONST_tabName_qyImObjRegInfoTab  )  )  goto  errLabel;
			 
			}
		  else  {
			  	 int				iObjId				=	pMcView->var.m_superSel.u.rootTree.iHelpId;
				 QY_OBJINDEX_RCD	objIndex;
				 int				ilastPortIfIndex	=	-1;

	 			 if  (  g_dbFuncs.pf_getObjIndex(  pObjDb,  iObjId,  &objIndex  )  )  goto  errLabel;
				 switch  (  objIndex.objType  )  {					 
						  case  CONST_objType_zb:
						  case  CONST_objType_bb:
						  case  CONST_objType_col2:
							    //  ÏÔÊ¾Ö¸¶¨µ¥Î»µÄËùÓÐ²¿ÃÅ
					 		    if  (  displayListContent_bz(  pObjDb,  pMcView,  pCfgParam,  CONST_tabName_qyImObjRegInfoTab,  &objIndex  )  )  goto  errLabel;
								break;
						  case  CONST_objType_col3:
							    if  (  displayListContent_col3_is(  pObjDb,  pMcView,  pCfgParam,  &objIndex  )  )  goto  errLabel;
								break;								
						  case  CONST_objType_unRegGrp:
							    if  (  displayListContent_unRegGrp_is(  pObjDb,  pMcView,  pCfgParam,  &objIndex  )  )  goto  errLabel;
								break;
								/*
						  case  CONST_objType_othersGrp:
							    if  (  displayListContent_othersGrp(  pObjDb,  pMcView,  pCfgParam,  &objIndex  )  )  goto  errLabel;
								break;
								*/
						  case  CONST_objType_col4:
						  case  CONST_objType_messenger:
							    if  (  displayListContent_pc(  pObjDb,  pMcView,  pCfgParam,  &objIndex  )  )  goto  errLabel;
								break;				
						  case  CONST_objType_pcUsrInfo:
							    if  (  displayListContent_pcUsrInfo(  pObjDb,  pMcView,  pCfgParam,  &objIndex  )  )  goto  errLabel;
								break;
						  case  CONST_objType_pcStatus:
  							    if  (  displayListContent_pcStatus(  pObjDb,  pMcView,  pCfgParam,  &objIndex  )  )  goto  errLabel;
							    break;								
						  case  CONST_objType_pcOpNode:
  							    if  (  displayListContent_pcOpNode(  pObjDb,  pMcView,  pCfgParam,  &objIndex  )  )  goto  errLabel;
							    break;		
						  case  CONST_objType_imGrps:
							    if  (  displayListContent_imGrps(  pObjDb,  pMcView,  pCfgParam,  &objIndex  )  )  goto  errLabel;
							    break;
						  case  CONST_objType_imGrp:
							    if  (  displayListContent_imGrp(  pObjDb,  pMcView,  pCfgParam,  &objIndex  )  )  goto  errLabel;
							    break;
						  default:
								  goto  errLabel;
				 }
				 
		  }
		  
		}
	 catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "displayListContent_imObjs failed."  )  );
		   goto  errLabel;
	 }
		 

	 iRet  =  0;

errLabel:
	
	
	 return  iRet;		

}
 int  displayListContent_allTopCols(  QY_OBJ_DB  *  pObjDb,  CQyMcView  *  pMcView,  QY_MC_DISPLAYCFG	*	pCfgParam,  LPCTSTR  tabName_regInfo  )
{
	 int								iRet					=			-1;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 CQyMcDoc						*	pDoc					=			pMcView->GetDocument(  );
	 CListCtrl						&	ListCtrl				=			pMcView->GetListCtrl();
	 int								index					=			0;
	 //  QY_MCROOTLIST_DISPLAYCFG		*	pCfg					=			&pCfgParam->u.rootList;
	 TCHAR								sqlBuf[1024];
	 CRecordset							rs(  (  CDatabase  *  )pObjDb->pDb  );   int	 nFields;
	 CDBVariant							varVals[20];	 
	 int								cnt						=			0;
	 int								nImage;
	 int								iTopFieldId,  iObjType;
	 int								i;
	 QY_COLUMNINFO						columns[2];
	 TCHAR								tBuf[256];
	 	 
	 
	 try  {		
	 
		  if  (  pMcView->var.m_superSel.u.rootTree.bRoot  )  {

			  if  (  !bGetTopParams(  &iTopFieldId,  &iObjType  )  )  goto  errLabel;
		  	  if  (  (  i  =  getRegIndexByFieldId(  iTopFieldId  )  )  <  0  )  goto  errLabel;
			  mybSetColumns(  iObjType,  columns,  sizeof(  columns  )  /  sizeof(  columns[0]  )  );
			  
			  pMcView->delAllColumns(  );
			  if  (  !pMcView->bAddColumns(  columns  )  )  goto  errLabel;

			  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select distinct %s.col%d from %s %s %s order by %s.col%d"  ),  tabName_regInfo,  i,  tabName_regInfo,  CString(  pDoc->m_docStruct.u.treeList.tree.wherePart[0]  ?  "where"  :  ""  ),  CString(  pDoc->m_docStruct.u.treeList.tree.wherePart  ),  tabName_regInfo,  i  );
			  if  (  !rs.Open( CRecordset::forwardOnly,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  {  debugLog(  "rs open() failed."  );  goto  errLabel;  }
	  			 
			  nFields  =  rs.GetODBCFieldCount(  );
			  //  rs.GetODBCFieldInfo(  index,  tmpFieldInfo  );
			  for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {
						   
				   for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   	   

				   index  =  0;		{  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  }
	 			   index  ++  ;		
				   
				   nImage  =  pQyMc->cfg.image.nImage_col2;	 			  		
			   	   ListCtrl.InsertItem(  cnt,  tBuf,  nImage  );
				   
				   cnt  ++  ;

			  }
			
			  rs.Close(  );

			}
		  
		}
	 catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "displayListContent_allTopCols failed."  )  );
		   goto  errLabel;
	 }

		 
	 iRet  =  TRUE;

errLabel:
	
	 if  (  rs.IsOpen(  )  )  rs.Close(  );
	
	 return  iRet;		

}
 int  displayListContent_bz(  QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  LPCTSTR  tabName_regInfo,  QY_OBJINDEX_RCD  *  pObjIndex  )
{
	 int								iRet					=			-1;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 CListCtrl						&	ListCtrl				=			pMcView->GetListCtrl();
	 //  LV_ITEM							lvi;
	 int								index					=			0;
	 //  QY_MCROOTLIST_DISPLAYCFG		*	pCfg					=			&pCfgParam->u.rootList;
	 TCHAR								sqlBuf[CONST_qyMaxSqlBufLen  +  1];
	 CRecordset							rs(  (  CDatabase  *  )pObjDb->pDb  );   int	 nFields;
	 CDBVariant							varVals[20];
	 int								cnt						=			0;
	 int								nImage;
	 TCHAR								displayName[512];
	 int								indexDisplayed,  indexToDisplay;
	 int								iObjTypeToDisplay;
	 TCHAR								whereClause[1024]		=			_T(  ""  );
	 QY_COLUMNINFO						columns[2];
	 TCHAR								tBuf[256];

	 
	 try  {		

		 //  if  (  pObjIndex->objType  ==  CONST_objType_col2  )  
		 {

			 if  (  getSthForObjs(  pObjDb,  tabName_regInfo,  pObjIndex,  &indexDisplayed,  &indexToDisplay,  &iObjTypeToDisplay,  whereClause,  mycountof(  whereClause  )  )  )  goto  errLabel;
			 mybSetColumns(  iObjTypeToDisplay,  columns,  sizeof(  columns  )  /  sizeof(  columns[0]  )  );
					 
			 //  ÏÔÊ¾Ò»¸ö¶Ë¿ÚµÄ¹ØÁªÐÅÏ¢
			 pMcView->delAllColumns(  );
			 if  (  !pMcView->bAddColumns(  columns  )  )  goto  errLabel;
			 																//  0														
			 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "SELECT distinct %s.col%d from %s where %s order by %s.col%d"  ),  tabName_regInfo,  indexToDisplay,  tabName_regInfo,  whereClause,  tabName_regInfo,  indexToDisplay  );
 			 traceLogA(  "%S",  sqlBuf  );
 			 if  (  !rs.Open( CRecordset::forwardOnly,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  {
				 traceLogA(  "rs open() failed."  );  goto  errLabel;
			 }
			 nFields  =  rs.GetODBCFieldCount(  );					 
					 
			 for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {
				  				   
	  			  for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   				  
	  			  index  =  0;  //  qyPcRegInfoTab.col3
				  MACRO_sqlStr(  varVals[index],  (  TCHAR  *  )tBuf,  mycountof(  tBuf  )  );  
	  			  index  ++  ;	
				  				  
				  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s"  ),  tBuf  );
						  
				  nImage  =  pQyMc->cfg.image.nImage_col3;
				
				  ListCtrl.InsertItem(  cnt,  CString(  displayName  ).GetBuffer(  0  ),  nImage  );
				
				  cnt  ++  ;
							  
			 }

			 rs.Close(  );
						
		 }
						 	
			}
	 catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "displayListContent_bz failed."  )  );
		   goto  errLabel;
	 }

		 
	 iRet  =  0;

errLabel:
	
	 if  (  rs.IsOpen(  )  )  rs.Close(  );
	
	 return  iRet;		

}
 int  displayListContent_col3_is(  QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_OBJINDEX_RCD  *  pObjIndex  )
{
	 int								iRet					=			-1;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 CListCtrl						&	ListCtrl				=			pMcView->GetListCtrl();
	 //  LV_ITEM							lvi;
	 int								index					=			0;
	 //  QY_MCROOTLIST_DISPLAYCFG		*	pCfg					=			&pCfgParam->u.rootList;
	 TCHAR								sqlBuf[CONST_qyMaxSqlBufLen  +  1];
	 CRecordset							rs(  (  CDatabase  *  )pObjDb->pDb  );   int	 nFields;
	 CDBVariant							varVals[20];
	 QY_MESSENGER_INFO					messengerInfo;
	 QY_MESSENGER_REGINFO				regInfo;
	 int								cnt						=			0;
	 int								nImage;
	 TCHAR								displayName[512];
	 int								indexDisplayed,  indexToDisplay;
	 int								iObjTypeToDisplay;
	 TCHAR								whereClause[1024]		=			_T(  ""  );
	 TCHAR								tBuf[256];
	 char								buf[256];
	 char								ip12Buf[128]			=			"";
	 
	 try  {		

		 if  (  pObjIndex->objType  ==  CONST_objType_col3  )  {

			 if  (  getSthForObjs(  pObjDb,  _T(  "B"  ),  pObjIndex,  &indexDisplayed,  &indexToDisplay,  &iObjTypeToDisplay,  whereClause,  mycountof(  whereClause  )  )  )  goto  errLabel;
					 
			 //  ÏÔÊ¾Ò»¸ö¶Ë¿ÚµÄ¹ØÁªÐÅÏ¢
			 pMcView->delAllColumns(  );
			 if  (  !pMcView->bAddColumns(  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_COLUMNINFO_col4ListColumns_is  )  )  )  goto  errLabel;
			 																//  0														
			 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "SELECT B.id,B.col%d,B.idStr,A.ip from qyImObjRegInfoTab as B left join qyImObjTab as A on (A.misServName=B.misServName and A.idStr=B.idStr) where %s order by B.col%d"  ),  indexToDisplay,  whereClause,  indexToDisplay  );
			 if  (  !rs.Open( CRecordset::forwardOnly,  sqlBuf  )  )  {  traceLogA(  "rs open() failed."  );  goto  errLabel;  }
			 nFields  =  rs.GetODBCFieldCount(  );					 
					 
			 for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {
				  memset(  &messengerInfo,  0,  sizeof(  messengerInfo  )  );
				  memset(  &regInfo,  0,  sizeof(  regInfo  )  );
				  				   
	  			  for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   				  
	  			  index  =  0;  //  id
				  MACRO_sqlLong(  varVals[index],  regInfo.id  );
				  index  ++  ;	//  qyImObjRegInfoTab.col4
				  MACRO_sqlStr(  varVals[index],  (  TCHAR  *  )regInfo.u.cols[4],  sizeof(  regInfo.u.cols[4]  )  /  sizeof(  TCHAR  )  );  
	  			  index  ++  ;	//  qyImObjRegInfoTab.idStr
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &regInfo.addr.idInfo  );  
				  index  ++  ;  //  qyImObjRegInfoTab.ip
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12Buf,  mycountof(  ip12Buf  )  );  qyIp12ToStd(  ip12Buf,  messengerInfo.ip  );  
				  index  ++  ;  //  
				  				  
				  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s"  ),  regInfo.u.cols[4]  );
						  
				  nImage  =  pQyMc->cfg.image.nImage_col4;
				
				  index  =  0;	ListCtrl.InsertItem(  cnt,  displayName,  nImage  );
				  index  ++  ;	ListCtrl.SetItemText(  cnt, index,  CString(  messengerInfo.ip  ).GetBuffer(  0  )  );
				  index  ++  ;	ListCtrl.SetItemText(  cnt, index,  pObjIndex->servName  );
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  regInfo.addr.idInfo.ui64Id  );
				  index  ++  ;  ListCtrl.SetItemText(  cnt,  index,  tBuf  );
				
				  cnt  ++  ;
							  
			 }

			 rs.Close(  );
						
		 }
						 	
			}
	 catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "displayListContent_col3_is failed."  )  );
		   goto  errLabel;
	 }
	 iRet  =  0;

errLabel:
	
	 if  (  rs.IsOpen(  )  )  rs.Close(  );
	
	 return  iRet;		

}
 int  displayListContent_unRegGrp_is(  QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_OBJINDEX_RCD  *  pObjIndex  )
{
	 int								iRet											=			-1;
	 QY_MC							*	pQyMc											=			QY_GET_GBUF( );
	 CListCtrl						&	ListCtrl										=			pMcView->GetListCtrl();
	 //  LV_ITEM							lvi;
	 int								index											=			0;
	 //  QY_MCROOTLIST_DISPLAYCFG		*	pCfg											=			&pCfgParam->u.rootList;
	 TCHAR								sqlBuf[CONST_qyMaxSqlBufLen  +  1];
	 CRecordset							rs(  (  CDatabase  *  )pObjDb->pDb  );   int	 nFields;
	 CDBVariant							varVals[20];
	 QY_MESSENGER_INFO					messengerInfo;
	 int								cnt												=			0;
	 int								nImage;
	 TCHAR								displayName[512];
	 TCHAR								tBuf[256];
	 char								ip12Buf[128]									=			"";
	 char								buf[255  +  1]									=	"";
	 
	 try  {		

		 if  (  pObjIndex->objType  ==  CONST_objType_unRegGrp  )  {
					 
			 //  ÏÔÊ¾Ò»¸ö¶Ë¿ÚµÄ¹ØÁªÐÅÏ¢
			 pMcView->delAllColumns(  );
			 if  (  !pMcView->bAddColumns(  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_COLUMNINFO_unRegGrpMemListColumns_is  )  )  )  goto  errLabel;
			 																//  0														
			 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "SELECT qyImObjTab.ip,qyImObjTab.idStr from qyImObjTab where qyImObjTab.misServName=%s and qyImObjTab.uiType not in(%d) and qyImObjTab.idStr not in (select qyImObjRegInfoTab.idStr from qyImObjRegInfoTab where qyImObjRegInfoTab.misServName=%s) order by qyImObjTab.ip"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  pObjIndex->servName  ),  CONST_objType_imGrp,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  pObjIndex->servName  )  );
 			 traceLogA(  "%s",  sqlBuf  );
 			 if  (  !rs.Open( CRecordset::forwardOnly,  sqlBuf  )  )  {
				 traceLogA(  "rs open() failed."  );  goto  errLabel;
			 }
			 nFields  =  rs.GetODBCFieldCount(  );					 
					 
			 for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {

				  memset(  &messengerInfo,  0,  sizeof(  messengerInfo  )  );
				  				   
	  			  for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   				  
	  			  index  =  0;  //  ip
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12Buf,  sizeof(  ip12Buf  )  );  qyIp12ToStd(  ip12Buf,  messengerInfo.ip  );  
	  			  index  ++  ;	//  idStr
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &messengerInfo.idInfo  );
				  index  ++  ;
				  				  
						  
				  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%I64u"  ),  messengerInfo.idInfo.ui64Id  );
				  nImage  =  pQyMc->cfg.image.nImage_col4;

				  ListCtrl.InsertItem(  cnt,  displayName,  nImage  );

				  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s"  ),  CString(  messengerInfo.ip  )  );

				  ListCtrl.SetItemText(  cnt,  1,  displayName  );
				
				  cnt  ++  ;
							  
			 }

			 rs.Close(  );
						
		 }
						 	
			}
	 catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "displayListContent_unRegGrp_is failed."  )  );
		   goto  errLabel;
	 }
		 
	 iRet  =  0;

errLabel:
	
	 if  (  rs.IsOpen(  )  )  rs.Close(  );
	
	 return  iRet;		

}
 int  displayListContent_imGrps(  QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_OBJINDEX_RCD  *  pObjIndex  )
{
	 int								iRet					=			-1;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 CListCtrl						&	ListCtrl				=			pMcView->GetListCtrl();
	 //  LV_ITEM							lvi;
	 int								index					=			0;
	 //  QY_MCROOTLIST_DISPLAYCFG		*	pCfg					=			&pCfgParam->u.rootList;
	 TCHAR								sqlBuf[CONST_qyMaxSqlBufLen  +  1];
	 CRecordset							rs(  (  CDatabase  *  )pObjDb->pDb  );   int	 nFields;
	 CDBVariant							varVals[20];
	 IM_GRP_INFO						grpInfo;
	 int								cnt						=			0;
	 int								nImage;
	 TCHAR								displayName[512];
	 TCHAR								tBuf[256];
	 char								buf[128]				=			"";
	 
	 try  {		

		 if  (  pObjIndex->objType  ==  CONST_objType_imGrps  )  {
					 
			 //  ÏÔÊ¾Ò»¸ö¶Ë¿ÚµÄ¹ØÁªÐÅÏ¢
			 pMcView->delAllColumns(  );
			 if  (  !pMcView->bAddColumns(  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_COLUMNINFO_imGrpListColumns  )  )  )  goto  errLabel;
			 																//  0														
			 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "SELECT qyImGrpInfoTab.name,A.idStr,A.id from qyImObjTab as A left join qyImGrpInfoTab on (A.misServName=qyImGrpInfoTab.misServName and A.idStr=qyImGrpInfoTab.idStr) where A.misServName=%s and A.uiType in(%d) order by qyImGrpInfoTab.name"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  pObjIndex->servName  ),  CONST_objType_imGrp  );
 			 traceLogA(  "%s",  sqlBuf  );
 			 if  (  !rs.Open( CRecordset::forwardOnly,  sqlBuf  )  )  {
				 traceLogA(  "rs open() failed."  );  goto  errLabel;
			 }
			 nFields  =  rs.GetODBCFieldCount(  );					 
					 
			 for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {

				  memset(  &grpInfo,  0,  sizeof(  grpInfo  )  );
				  				   
	  			  for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   				  
	  			  index  =  0;  //  name
				  MACRO_sqlStr(  varVals[index],  grpInfo.name,  mycountof(  grpInfo.name  )  );  
	  			  index  ++  ;	//  idStr
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &grpInfo.idInfo  );
				  index  ++  ;	//  id
				  MACRO_sqlLong(  varVals[index],  grpInfo.id  );
				  				  
				  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s"  ),  CString(  grpInfo.name  )  );
						  
				  nImage  =  pQyMc->cfg.image.nImage_imGrp;
				
				  index  =  0;
				  ListCtrl.InsertItem(  cnt,  displayName,  nImage  );
				  index  ++  ;
				  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%I64u"  ),  grpInfo.idInfo.ui64Id  );
				  ListCtrl.SetItemText(  cnt,  index,  displayName  );
				  index  ++  ;
				  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%d"  ),  grpInfo.id  );
				  ListCtrl.SetItemText(  cnt,  index,  displayName  );
				  

				
				  cnt  ++  ;
							  
			 }

			 rs.Close(  );
			
		 }
						 	
			}
	 catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "displayListContent_imGrps failed."  )  );
		   goto  errLabel;
	}

		 
	 iRet  =  0;

errLabel:
	
	 if  (  rs.IsOpen(  )  )  rs.Close(  );
	
	 return  iRet;		

}
 int  displayListContent_imGrp(  QY_OBJ_DB  *  pObjDb,  CQyMcView  * pMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_OBJINDEX_RCD  *  pObjIndex  )
{
	 int								iRet					=			-1;
	 QY_MC							*	pQyMc					=			QY_GET_GBUF( );
	 CListCtrl						&	ListCtrl				=			pMcView->GetListCtrl();
	 //  LV_ITEM							lvi;
	 int								index					=			0;
	 //  QY_MCROOTLIST_DISPLAYCFG		*	pCfg					=			&pCfgParam->u.rootList;
	 TCHAR								sqlBuf[CONST_qyMaxSqlBufLen  +  1];
	 CRecordset							rs(  (  CDatabase  *  )pObjDb->pDb  );   int	 nFields;
	 CDBVariant							varVals[20];
	 int								cnt						=			0;
	 int								nImage;
	 TCHAR								displayName[512];
	 TCHAR								tBuf[256];
	 char								buf[128]				=			"";
	 //
	 QY_MC_QUERY						query;
	 int								i;
	 QY_MESSENGER_REGINFO				regInfo;

	 
	 try  {		

		 if  (  pObjIndex->objType  ==  CONST_objType_imGrp  )  {
					 
			 memset(  &query,  0,  sizeof(  query  )  );
			 setQueryColumns(  0,  (  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpSimpleUsrQueryStruct_is  ),  &query  );

			 //  ÏÔÊ¾Ò»¸ö¶Ë¿ÚµÄ¹ØÁªÐÅÏ¢
			 pMcView->delAllColumns(  );
			 if  (  !pMcView->bAddColumns(  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_COLUMNINFO_imGrpMemListColumns  )  )  )  goto  errLabel;
			 if  (  !pMcView->bAddColumns(  query.columns  )  )  goto  errLabel;
			 																//  0														
			 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "SELECT qyImGrpMemTab.idStr_mem,qyImGrpMemTab.id"  )  );
			 for  (  i  =  0;  query.sqlColumns[i].type  !=  -1;  i  ++  )  {
				  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s,%s"  ),  sqlBuf,  query.sqlColumns[i].label  );
		  	 }		  	 
			 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s from qyImGrpMemTab left join qyImObjRegInfoTab as B on (qyImGrpMemTab.misServName=B.misServName and qyImGrpMemTab.idStr_mem=B.idStr) where qyImGrpMemTab.misServName=%s and qyImGrpMemTab.idStr_grp='%s' order by qyImGrpMemTab.idStr_mem"  ),  sqlBuf,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  pObjIndex->servName  ),  pObjIndex->objIdStr0  );

 			 OutputDebugString(  CString(  sqlBuf  )  +  CString(  "\n"  )  );
 			 if  (  !rs.Open( CRecordset::forwardOnly,  sqlBuf  )  )  {
				 traceLogA(  "rs open() failed."  );  goto  errLabel;
			 }
			 nFields  =  rs.GetODBCFieldCount(  );					 
					 
			 for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {

				  memset(  &regInfo,  0,  sizeof(  regInfo  )  );
				  				   
	  			  for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   				  
	  			  index  =  0;  //  idStr_mem
				  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &regInfo.addr.idInfo  );  
	  			  index  ++  ;	//  id
				  MACRO_sqlLong(  varVals[index],  regInfo.id  );
				  index  ++  ;		//  È¡¸÷ÓÃ»§ÐÅÏ¢
				  for  (  i  =  0;  query.columns[i].type  !=  -1;  i  ++  )  {
					   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  (  TCHAR   *  )regInfo.u.cols[i],  tBuf,  sizeof(  regInfo.u.cols[i]  )  /  sizeof(  TCHAR  )  );  
				   	   index  ++  ;
			   	  }
						  
				  nImage  =  pQyMc->cfg.image.nImage_messenger;

				  index  =  0;
				  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%I64u"  ),  regInfo.addr.idInfo.ui64Id  );
				  ListCtrl.InsertItem(  cnt,  displayName,  nImage  );
				  index  ++  ;
				  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%d"  ),  regInfo.id  );
				  ListCtrl.SetItemText(  cnt,  index,  displayName  );
				  index  ++  ;

				  for  (  i  =  0;  query.columns[i].type  !=  -1;  i  ++  )  {
					   ListCtrl.SetItemText(  cnt,  i  +  index,  (  TCHAR  *  )regInfo.u.cols[i]  );						
				  }

				  cnt  ++  ;
							  
			 }

			 rs.Close(  );
			
		 }
						 	
			}
	 catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "displayListContent_imGrp failed."  )  );
		   goto  errLabel;
	 }

		 
	 iRet  =  0;

errLabel:
	
	 if  (  rs.IsOpen(  )  )  rs.Close(  );
	
	 return  iRet;		

}
#endif
#if  0
  int  getSthForObjs(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  tabName_regInfo,  QY_OBJINDEX_RCD  *  pObjIndex,  int  *  pIndexDisplayed,  int  *  pIndexToDisplay,  int  *  piObjTypeToDisplay,  TCHAR  *  whereClause,  unsigned  int  size  )
{
	 int					iRet					=		-1;
	 QY_OBJINDEX_RCD		objIndex;
	 int					zbIndex,  bbIndex,  dwIndex,  bmIndex,  syrIndex;
	 int					indexDisplayed,  indexToDisplay;
	 int					iObjTypeToDisplay;
	 int					iDataType_displayed		=		SQL_VARCHAR;
	 int					iDbType;

	 if  (  !bObjDbAvail(  pObjDb  )  ||  !tabName_regInfo  )  goto  errLabel;
	 iDbType  =  pObjDb->cfg.iDbType;

	 if  (  (  zbIndex  =  getRegIndexByFieldId(  CONST_fieldId_zb  )  )  <  0  )  goto  errLabel;
	 if  (  (  bbIndex  =  getRegIndexByFieldId(  CONST_fieldId_bb  )  )  <  0  )  goto  errLabel;
	 if  (  (  dwIndex  =  getRegIndexByFieldId(  CONST_fieldId_dw  )  )  <  0  )  goto  errLabel;
	 if  (  (  bmIndex  =  getRegIndexByFieldId(  CONST_fieldId_bm  )  )  <  0  )  goto  errLabel;
	 if  (  (  syrIndex =  getRegIndexByFieldId(  CONST_fieldId_syr  )  )  <  0  )  goto  errLabel;
	 
	 switch  (  pObjIndex->objType  )  {
	 		 case  CONST_objType_bm:
				   indexDisplayed  =  bmIndex;  iDataType_displayed  =  SQL_WVARCHAR;  indexToDisplay  =  syrIndex;  iObjTypeToDisplay  =  CONST_objType_syr;
				   break;
			 case  CONST_objType_dw:
				   indexDisplayed  =  dwIndex;  iDataType_displayed  =  SQL_WVARCHAR;  indexToDisplay  =  bmIndex;  iObjTypeToDisplay  =  CONST_objType_bm;
				   break;	
			 case  CONST_objType_bb:
				   indexDisplayed  =  bbIndex;  iDataType_displayed  =  SQL_WVARCHAR;  indexToDisplay  =  dwIndex;  iObjTypeToDisplay  =  CONST_objType_dw;
				   break;	
			 case  CONST_objType_zb:
				   indexDisplayed  =  zbIndex;  iDataType_displayed  =  SQL_WVARCHAR;  indexToDisplay  =  bbIndex;  iObjTypeToDisplay  =  CONST_objType_bb;
				   break;	
			 default:	goto  errLabel;
	 }
	 if  (  whereClause  &&  size  )  {
		 tTrim(  whereClause  );
	 	 if  (  whereClause[0]  )  _sntprintf(  whereClause,  size,  _T(  "%s and"  ),  whereClause  );
	 	 _sntprintf(  whereClause,  size,  _T(  "%s %s.col%d=%s"  ),  whereClause,  tabName_regInfo,  indexDisplayed,  getDbValStr(  iDbType,  iDataType_displayed,  pObjIndex->objIdStr0  )  );
	 	 if  (  pObjIndex->objId0  )  {
			 if  (  getObjIndex(  pObjDb,  pObjIndex->objId0,  &objIndex  )  )  goto  errLabel;
			 if  (  getSthForObjs(  pObjDb,  tabName_regInfo,  &objIndex,  NULL,  NULL,  NULL,  whereClause,  size  )  )  goto  errLabel;
		 }
	 }
	 iRet  =  0;
errLabel:
	 if  (  !iRet  )  {
		 if  (  pIndexDisplayed  )  *pIndexDisplayed  =  indexDisplayed;
		 if  (  pIndexToDisplay  )  *pIndexToDisplay  =  indexToDisplay;
		 if  (  piObjTypeToDisplay  )  *piObjTypeToDisplay  =  iObjTypeToDisplay;
	 }
	 return  iRet;
}
 BOOL  bItemExists_imObjs(  QY_OBJ_DB  *  pObjDb,  CLeftView  *  pLeftView,  HTREEITEM  htItem  )
{
	 BOOL				bRet								=	FALSE;
	 QY_MC			*	pQyMc								=	QY_GET_GBUF(  );
	 int				iObjId								=	pLeftView->m_TreeCtrl->GetItemData(  htItem  );
	 QY_OBJINDEX_RCD	objIndex;
	 TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	 int				indexDisplayed,  indexToDisplay;
	 TCHAR				whereClause[1024]					=	_T(  ""  );
	 //
	 TCHAR			*	pObjTab								=	CONST_tabName_qyImObjTab;
	 TCHAR			*	pRegInfoTab							=	CONST_tabName_qyImObjRegInfoTab;
	 
	 if  (  getObjIndex(  pObjDb,  iObjId,  &objIndex  )  )  goto  errLabel;  

	 switch  (  objIndex.objType  )  {
			 case  CONST_objType_zb:
			 case  CONST_objType_bb:
			 case  CONST_objType_col2:
			 case  CONST_objType_col3:
				   if  (  getSthForObjs(  pObjDb,  _T(  "B"  ),  &objIndex,  &indexDisplayed,  &indexToDisplay,  NULL,  whereClause,  mycountof(  whereClause  )  )  )  goto  errLabel;
		   		   _sntprintf(  sqlBuf,  sizeof(  sqlBuf  )  /  sizeof(  sqlBuf[0]  ),  _T(  "select count(B.id) from %s as B  where  %s"  ),  pRegInfoTab,  whereClause  );
				   break;
			 case  CONST_objType_col4:
				   _sntprintf(  sqlBuf,  sizeof(  sqlBuf  )  /  sizeof(  sqlBuf[0]  ),  _T(  "select count(B.id) from %s as B where B.idStr='%s'"  ),  pRegInfoTab,  objIndex.objIdStr0  );
				   break;
			 case  CONST_objType_unRegGrp:
				   bRet  =  TRUE;  goto  errLabel;
			 case  CONST_objType_unRegPc:
				   _sntprintf(  sqlBuf,  sizeof(  sqlBuf  )  /  sizeof(  sqlBuf[0]  ),  _T(  "SELECT count(A.id) from %s as A where A.idStr not in( select B.idStr from %s as B) and A.idStr='%s'"  ),  pObjTab,  pRegInfoTab,  objIndex.objIdStr0  );
				   break;
			 case  CONST_objType_messenger:  {
				   MIS_CNT				*	pMisCnt	=  NULL;
				   QY_MESSENGER_ID			idInfo;
				   char						idStr[CONST_qyMessengerIdStrLen  +  1]	=	"";

				   pMisCnt  =  getMisCntByName(  pQyMc,  NULL,  objIndex.objIdStr0  );
				   if  (  !pMisCnt  )  goto  errLabel;
				   if  (  !myTChar2Str(  objIndex.objIdStr1,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
				   if  (  !idStr2Info(  idStr,  &idInfo  )  )  goto  errLabel;
				   if  (  idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  goto  errLabel;	//  Õâ¾ä»°±íÃ÷£¬ÎÒÕâ¸ö×Ö¶ÎÔÚÎ´×¢²áµÄmessengerÀïÊÇ²»´æÔÚµÄ¡£µ«ÊÇ¿ÉÒÔÔÚ×¢²áµÄ×éÀï´æÔÚ£¬ÒòÎªÕâ¿ÉÒÔ²»Ó°ÏìÒ»¸ö×éµÄÍêÕûÐÔ
				   }
				   bRet  =  TRUE;  goto  errLabel;
				   break;
			 default:
					//  ÕâÀï¼ÙÉè£¬ÐèÒª¼ìÑéµÄ¶¼ÒªÖ¸¶¨
				    bRet  =  TRUE;  goto  errLabel;
	 }
	 if  (  !bSqlObjExists(  pObjDb->pDb,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  goto  errLabel;

	 bRet  =  TRUE;
errLabel:

	 traceLogA(  "½Úµã[%d] %S %S %S %s",  objIndex.objType,  objIndex.objIdStr0,  objIndex.objIdStr1,  objIndex.objIdStr2,  (  bRet  ?  "´æÔÚ"  :  "²»´æÔÚ"  )  );

	 return  bRet;
}
 BOOL  bViewUnprocedNewImTaskList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL					bRet										=	FALSE;
	QY_MC				*	pQyMc										=	QY_GET_GBUF(  );
	TCHAR					whereClause[CONST_maxSqlBufLen  +  1]		=	_T(  ""  );

	_sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "(T.iStatus in(%d,%d,%d,%d,%d,%d))"  ), 
															CONST_imTaskStatus_applyToSend,
															CONST_imTaskStatus_waitToSend,
															CONST_imTaskStatus_applyToRecv,
															CONST_imTaskStatus_waitToRecv,
															CONST_imTaskStatus_sending,
															CONST_imTaskStatus_receiving
															);
	if  (  wherePart  &&  wherePart[0]  )  _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "%s and (%s)"  ),  whereClause,  wherePart  );

	bRet  =  bViewImTaskListFunc(  pObjDb,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_unfinished  ),  whereClause,  FALSE  );

	return  bRet;
}
#endif

 //  2013/02/20
 BOOL  bNewMessenger(  )
{
	BOOL					bRet		=		FALSE;
	CDlgMessenger				dlg;
	
	if  (  	dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
	
	bRet  =  TRUE;

errLabel:

	return  bRet;

}


 BOOL  bNewImGrp(  )
{
	BOOL					bRet		=		FALSE;
#ifndef  __isCli__
	CDlgImGrp				dlg;
	
	if  (  	dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
	
	bRet  =  TRUE;
#endif

errLabel:

	return  bRet;

}


 int  modifyImObjId(  void  *  pDb,  int  iDbType,  BOOL  bClient,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo_old,  QY_MESSENGER_ID  *  pIdInfo_new  )
{
	int			iErr		=		-1;
	char		idStr_old[CONST_qyMessengerIdStrLen  +  1]		=	"";
	char		idStr_new[CONST_qyMessengerIdStrLen  +  1]		=	"";
	TCHAR		sqlBuf[CONST_maxSqlBufLen  +  1]				=	_T(  ""  );

	if  (  !misServName  ||  !pIdInfo_old  ||  !pIdInfo_new  )  return  -1;

	idInfo2Str(  pIdInfo_old,  idStr_old,  mycountof(  idStr_old  )  );
	idInfo2Str(  pIdInfo_new,  idStr_new,  mycountof(  idStr_new  )  );

	//  ÏÈÐÞ¸ÄqyImObjAuthTab£¬ÒòÎªÈç¹ûºÅÖØÁË£¬¾Í¿ÉÒÔ±ÜÃâ¸Ä»µÁË
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set idStr='%s' where misServName=%s and idStr='%s'"  ),  CONST_tabName_qyImObjAuthTab,  CString(  idStr_new  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr_old  )  );
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	//  ÐÞ¸ÄqyImGrpMemTab
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set idStr_mem='%s' where misServName=%s and idStr_mem='%s'"  ),  CONST_tabName_qyImGrpMemTab,  CString(  idStr_new  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr_old  )  );
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set idStr_grp='%s' where misServName=%s and idStr_grp='%s'"  ),  CONST_tabName_qyImGrpMemTab,  CString(  idStr_new  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr_old  )  );
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	//  ÐÞ¸ÄqyImGrpInfoTab
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set idStr='%s' where misServName=%s and idStr='%s'"  ),  CONST_tabName_qyImGrpInfoTab,  CString(  idStr_new  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr_old  )  );
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	//  ÐÞ¸ÄqyImObjRegInfoTab
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set idStr='%s' where misServName=%s and idStr='%s'"  ),  CONST_tabName_qyImObjRegInfoTab,  CString(  idStr_new  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr_old  )  );
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;
	//
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set idStr='%s' where misServName=%s and idStr='%s'"  ),  CONST_tabName_qyImObjRegInfoTab1,  CString(  idStr_new  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr_old  )  );
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	if  (  !bClient  )  {
		//  webContactTab
		_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set idStr='%s' where misServName=%s and idStr='%s'"  ),  CONST_tabName_qyWebContactTab,  CString(  idStr_new  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr_old  )  );
		if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

		//  qyDynBmpRuleTab
		_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set idStr='%s' where misServName=%s and idStr='%s'"  ),  CONST_tabName_qyDynBmpRuleTab,  CString(  idStr_new  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr_old  )  );
		if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

		_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set idStr_visitor='%s' where misServName=%s and idStr_visitor='%s'"  ),  CONST_tabName_qyDynBmpRuleTab,  CString(  idStr_new  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr_old  )  );
		if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;
	}

	//  qyDynBmpTab
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set idStr='%s' where misServName=%s and idStr='%s'"  ),  CONST_tabName_qyDynBmpTab,  CString(  idStr_new  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr_old  )  );
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	//  phoneMessengerTab
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set idStr='%s' where misServName=%s and idStr='%s'"  ),  CONST_tabName_qyMessengerPhoneInfoTab,  CString(  idStr_new  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr_old  )  );
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	if  (  !bClient  )  {
		_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set idStr='%s' where misServName=%s and idStr='%s'"  ),  CONST_tabName_qyImAmTab,  CString(  idStr_new  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr_old  )  );
		if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;
	}

	//  qyImObjTab
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set idStr='%s' where misServName=%s and idStr='%s'"  ),  CONST_tabName_qyImObjTab,  CString(  idStr_new  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr_old  )  );
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	iErr  =  0;
errLabel:
	return  iErr;
}

 BOOL  bViewImObjAuthList_isMgr(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL					bRet	=	FALSE;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpMessengerAuthListQueryStruct  );
	
	if  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  return  FALSE;

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_imObjAuthList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  NULL,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from ((((qyImObjAuthTab left join qyImAmTab on(qyImObjAuthTab.misServName=qyImAmTab.misServName and qyImObjAuthTab.idStr=qyImAmTab.idStr)) left join qyMessengerPhoneInfoTab on (qyImObjAuthTab.misServName=qyMessengerPhoneInfoTab.misServName and qyImObjAuthTab.idStr=qyMessengerPhoneInfoTab.idStr)) left join qyImObjTab as A on (qyImObjAuthTab.misServName=A.misServName and qyImObjAuthTab.idStr=A.idstr)) left join qyImObjRegInfoTab as B on(qyImObjAuthTab.misServName=B.misServName and qyImObjAuthTab.idStr=B.idStr ) )"  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "qyImObjAuthTab.uiType not in(%d)"  ),  CONST_objType_imGrp  );
	if  (  wherePart  &&  wherePart[0]  ) _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s and %s"  ),  tmpSel.u.query.wherePart,  CString(  wherePart  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "qyImObjAuthTab.idStr"  )  );
	

	tmpSel.u.query.data2DisplayProc			=  displayQnmElement;
	tmpSel.u.query.pfProcEvent				=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId				=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos				=  CONST_resId_popup_viewMessengerAuthList_isMgr;				//  2003/12/17修改
	tmpSel.u.query.ucbMultiSel				=  TRUE;														//  2007/08/24
	tmpSel.u.query.nSubMenuPos_multiSel		=  CONST_resId_popup_viewMessengerAuthList_multiSel_isMgr;		//  200


	_sntprintf(  tmpSel.u.query.docName,  mycountof(  tmpSel.u.query.docName  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyMessengerAuthList  )  );
	
	bRet  =  pApp->bNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}

 BOOL  bViewGsmModemList_isMgr(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL					bRet	=	FALSE;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpGsmModemListQueryStruct_isMgr  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_gsmModemList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  NULL,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from qyVDevComTab left join qyImObjRegInfoTab on(qyVDevComTab.misServname=qyImObjRegInfoTab.misServName and qyVDevComTab.idStr=qyImObjRegInfoTab.idStr) "  )  );
	if  (  wherePart  &&  wherePart[0]  ) _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s"  ),  CString(  wherePart  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "qyVDevComTab.idStr,qyVDevComTab.wDevIdStr "  )  );
	
	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	tmpSel.u.query.pfProcEvent  =  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId  =  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos  =  CONST_resId_popup_gsmModemList;								//  2003/12/17修改
	//  tmpSel.u.query.nSubMenuPos_notSel  =  CONST_resId_popup_commonList_notSel;
	//  tmpSel.u.query.ucbMultiSel  =  TRUE;
	//  tmpSel.u.query.nSubMenuPos_multiSel  =  CONST_resId_popup_phoneGuestList_multiSel;		//  2003/12/17修改
	//  tmpSel.u.query.uiDefaultCmd  =  ID_qyProp_pcModuleKnowlege;

	_sntprintf(  tmpSel.u.query.docName,  mycountof(  tmpSel.u.query.docName  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyGsmModemList  )  );
	
	bRet  =  pApp->bNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
}

 BOOL  bViewSmContactList_isMgr(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL					bRet	=	FALSE;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpSmContactListQueryStruct_isMgr  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_smContactList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  NULL,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from qySmContactTab left join qyImObjRegInfoTab on(qySmContactTab.misServname=qyImObjRegInfoTab.misServName and qySmContactTab.idStr_contact=qyImObjRegInfoTab.idStr) "  )  );
	if  (  wherePart  &&  wherePart[0]  ) _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s"  ),  CString(  wherePart  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "qySmContactTab.idStr,qySmContactTab.wDevIdStr "  )  );
	
	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	tmpSel.u.query.pfProcEvent  =  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId  =  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos  =  CONST_resId_popup_commonList;								//  2003/12/17修改
	//  tmpSel.u.query.nSubMenuPos_notSel  =  CONST_resId_popup_commonList_notSel;
	//  tmpSel.u.query.ucbMultiSel  =  TRUE;
	//  tmpSel.u.query.nSubMenuPos_multiSel  =  CONST_resId_popup_phoneGuestList_multiSel;		//  2003/12/17修改
	//  tmpSel.u.query.uiDefaultCmd  =  ID_qyProp_pcModuleKnowlege;

	_sntprintf(  tmpSel.u.query.docName,  mycountof(  tmpSel.u.query.docName  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qySmContactList  )  );
	
	bRet  =  pApp->bNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
}

//  2007/08/19
 int  displayContent_imObjs_isMgr(  void  *  p0,  void  *  p1,  void  *  p2  )
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
	 TCHAR						misServName[CONST_maxMisServNameLen  +  1]		=	_T(  ""  );			//  2007/08/19

	 if  (  !pLeftView->m_var.bInitialized  ||  !pLeftView->m_var.htMyRootItem  )  goto  errLabel;
	 
	 try  {

		  //  先将不存在的节点删除
		  myTrimTree(  pObjDb,  pLeftView,  pLeftView->m_var.htMyRootItem,  (  PF_bCommonHandler  )bItemExists_imObjs  );  
	  
		  if  (  !bGetTopParams(  &iTopFieldId,  &iObjType  )  )  goto  errLabel;
		  if  (  (  i  =  getRegIndexByFieldId(  iTopFieldId  )  )  <  0  )  goto  errLabel;
		  
		  //  下面增加新增的节点
		  //
		  //  先将注册用户的单位放入视图
		  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select distinct B.col%d from qyImObjRegInfoTab as B  where B.misServName=%s %s %s order by B.col%d"  ),  i,  getDbValStr(  pSci->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CQyString(  pDoc->m_docStruct.u.treeList.tree.wherePart[0]  ?  "and"  :  ""  ),  pDoc->m_docStruct.u.treeList.tree.wherePart,  i  );
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
			   iObjId  =  getObjId(  pObjDb,  0,  misServName,  iObjType,  &commonParam  );
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


	 	}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "displayContent_imObjs_isMgr failed."  )  );
		   goto  errLabel;
	}
	iRet				=				0;

errLabel:

	if  (  rs.IsOpen(  )  )  rs.Close(  );
	
	return  iRet;		

}

 int  refreshItem_imObjs_isMgr(  void  *  p0,  void  *  p1,  void  *  p2  )
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
	 TCHAR								misServName[CONST_maxMisServNameLen  +  1]		=	_T(  ""  );
	 //
	 CQnmDb								tmpObjDb;
	 if  (  !tmpObjDb.getAvailableDb(  pObjDb->iDsnIndex  )  )  {
		 traceLogA(  "得不到可用的连接数了"  );  goto  errLabel;
	 }
	 
	 if  (  htItem  ==  pLeftView->m_var.htMyRootItem  )  {
		 iRet  =  0;  goto  errLabel;
	 }


	 QM_dbFuncs  *  pDbFuncs  =  QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;



	 curiObjId  =  m_TreeCtrl->GetItemData(  htItem  );
	 if  (  g_dbFuncs.pf_getObjIndex(  pObjDb,  curiObjId,  &objIndex  )  )  goto  errLabel;

	 try  {

		  if  (  objIndex.objType  ==  CONST_objType_zb
			  ||  objIndex.objType  ==  CONST_objType_bb  
				||  objIndex.objType  ==  CONST_objType_dw  )  
		  {
			  if  (  getSthForObjs(  pObjDb,  _T(  "B"  ),  &objIndex,  &indexDisplayed,  &indexToDisplay,  &iObjType,  whereClause,  mycountof(  whereClause  )  )  )  goto  errLabel;
			  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select distinct B.col%d from qyImObjRegInfoTab as B"  ),  indexToDisplay  );
			  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s where misServName=%s %s %s"  ),  sqlBuf,  getDbValStr(  pSci->cfg.iDbType,  CONST_iDataType_misServName,  objIndex.servName  ),  (  whereClause[0]  ?  _T(  "and"  )  :  _T(  ""  )  ),  whereClause  );
			  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s order by B.col%d"  ),  sqlBuf,  indexToDisplay  );

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
						 lstrcpyn(  messengerInfo.misServName,  misServName,  mycountof(  messengerInfo.misServName  )  );
						 messengerInfo.idInfo.ui64Id  =  regInfo.addr.idInfo.ui64Id;

						if  (  regInfo.u.cols[indexToDisplay][0]  )  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s"  ),  regInfo.u.cols[indexToDisplay]  );
						else  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "(%I64u)"  ),  regInfo.addr.idInfo.ui64Id  );

			  			 nImage  =  pQyMc->cfg.image.nImage_col4;  nSelectedImage  =  pQyMc->cfg.image.nImage_selectedCol4;

			  			 if  (  myAddOrRefreshTreeItem(  pLeftView,  htItem,  iObjId,  displayName,  nImage,  nSelectedImage,  NULL  )  )  goto  errLabel;

		 			}					 
		
				  }
	 	  else  if  (  objIndex.objType  ==  CONST_objType_unRegGrp  )  {
	
			        _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "SELECT qyImObjTab.misServName,qyImObjTab.idStr,qyImObjTab.ip from qyImObjTab where qyImObjTab.misServName=%s and qyImObjTab.uiType not in(%d) and qyImObjTab.idStr not in( select qyImObjRegInfoTab.idStr from qyImObjRegInfoTab) order by qyImObjTab.ip"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  objIndex.servName  ),  CONST_objType_imGrp  );
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
						
						iObjId  =  getObjId(  pObjDb,  0,  NULL,CONST_objType_messenger,  &messengerInfo.idInfo  );
						if  (  iObjId  <  0  )  continue;
						
						_sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%I64u"  ),  messengerInfo.idInfo.ui64Id  );
						nImage  =  pQyMc->cfg.image.nImage_selectedMessenger;  nSelectedImage  =  pQyMc->cfg.image.nImage_selectedMessenger;
						//  getSnmpPortImages(  pQyMc,  &switchPort,  &nImage,  &nSelectedImage  );

						if  (  myAddOrRefreshTreeItem(  pLeftView,  htItem,  iObjId,  displayName,  nImage,  nSelectedImage,  NULL  )  )  goto  errLabel;

					}					 

				}
		  else  if  (  objIndex.objType  ==  CONST_objType_syr
					||  objIndex.objType  ==  CONST_objType_messenger  )  
		  {
			        QY_MESSENGER_ID		idInfo;
					COMMON_PARAM		commonParam;
					//
			        myTChar2Str(  objIndex.objIdStr0,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &idInfo  );

					MACRO_makeCommonParam3(  (  void  *  )CONST_objType_messenger,  buf,  0,  commonParam  );
										//  2006/08/14, 加入用户信息
					if  (  1  )  {

						iObjId  =  getObjId(  pObjDb,  0,  NULL,CONST_objType_pcUsrInfo,  &commonParam  );
						if  (  iObjId  <  0  )  goto  errLabel;

						_sntprintf(  displayName,  mycountof(  displayName  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_pcUsrInfo  )  );
						nImage  =  pQyMc->cfg.image.nImage_pcUsrInfo;  nSelectedImage  =  pQyMc->cfg.image.nImage_pcUsrInfo;

						if  (  myAddOrRefreshTreeItem(  pLeftView,  htItem,  iObjId,  displayName,  nImage,  nSelectedImage  )  )  goto  errLabel;

					}

					if  (  1  )  {	//  2006/08/14

						iObjId  =  getObjId(  pObjDb,  0,  NULL,CONST_objType_pcStatus,  &commonParam  );
						if  (  iObjId  <  0  )  goto  errLabel;

						_sntprintf(  displayName,  mycountof(  displayName  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_status  )  );
						nImage  =  pQyMc->cfg.image.nImage_pcStatus;  nSelectedImage  =  pQyMc->cfg.image.nImage_pcStatus;

						if  (  myAddOrRefreshTreeItem(  pLeftView,  htItem,  iObjId,  displayName,  nImage,  nSelectedImage  )  )  goto  errLabel;

					}

					if  (  1  )  {		//  2006/08/15

						iObjId  =  getObjId(  pObjDb,  0,  NULL,CONST_objType_pcOpNode,  &commonParam  );
						if  (  iObjId  <  0  )  goto  errLabel;

						_sntprintf(  displayName,  mycountof(  displayName  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_pcOpNode  )  );
						nImage  =  pQyMc->cfg.image.nImage_pcStatus;  nSelectedImage  =  pQyMc->cfg.image.nImage_selectedPcOpNode;

						if  (  myAddOrRefreshTreeItem(  pLeftView,  htItem,  iObjId,  displayName,  nImage,  nSelectedImage  )  )  goto  errLabel;

					}

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
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "refreshItem_imObjs_isMgr failed."  )  );
		   goto  errLabel;
	}
	 
	
	 iRet  =  0;

errLabel:
	 
	 if  (  rs.IsOpen(  )  )  rs.Close(  );

	 return  iRet;
}

 //  2007/03/07
 BOOL  bViewImObjView_isMgr(  QY_OBJ_DB  *  pObjDb  )
{
	 QY_MC_SEL	sel;
	 QY_MC			*  pQyMc	=  QY_GET_GBUF(  );

	 if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;

	 memset(  &sel,  0,  sizeof(  sel  )  );
	 sel.type								=  CONST_qySelType_mcRootTree;
	 sel.u.rootTree.pfProcTreeSel			=  netMc_procTreeSel;
	 sel.u.rootTree.pfProcEvent				=  netMc_procTreeEvent;
	 sel.u.rootTree.pfDisplayContent		=  displayContent_imObjs_isMgr;
	 sel.u.rootTree.pfRefreshItem			=  refreshItem_imObjs_isMgr;
	 sel.u.rootTree.pfDisplayListContent	=  displayListContent_imObjs;
	 sel.u.rootTree.bRoot					=  TRUE;
	 sel.u.rootTree.type					=  CONST_qyTreeType_imObj;
	 sel.u.rootTree.iDsnIndex				=  pObjDb->iDsnIndex;
	 _sntprintf(  sel.u.rootTree.docName,  mycountof(  sel.u.rootTree.docName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyMessengerView  )  );
	 
	 return  bQyMcNewTreeListView(  &sel  );

}

 BOOL  bViewImObjAuthNeedAuditedList_isMgr(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL					bRet	=	FALSE;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpMessengerAuthNeedAuditedListQueryStruct  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_imObjAuthNeedAuditedList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  NULL,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from qyImObjAuthTmpTab"  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "qyImObjAuthTmpTab.uiType not in(%d)"  ),  CONST_objType_imGrp  );
	if  (  wherePart  &&  wherePart[0]  ) _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s and %s"  ),  tmpSel.u.query.wherePart,  CString(  wherePart  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "qyImObjAuthTmpTab.idStr"  )  );
	
	tmpSel.u.query.data2DisplayProc			=  displayQnmElement;
	tmpSel.u.query.pfProcEvent				=  netMc_procEvent;
	tmpSel.u.query.pfProcEvent_new			=  is_procEvent_new;
	tmpSel.u.query.uPopupMenuId				=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos				=  CONST_resId_popup_viewMessengerNeedAuditedList_isMgr;				//  2003/12/17修改
	//  tmpSel.u.query.ucbMultiSel				=  TRUE;													//  2007/08/24
	//  tmpSel.u.query.nSubMenuPos_multiSel		=  CONST_resId_popup_viewMessengerNeedAuditedList_multiSel_isMgr;		//  200


	_sntprintf(  tmpSel.u.query.docName,  mycountof(  tmpSel.u.query.docName  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyMessengerAuthList_needAudited  )  );
	
	bRet  =  pApp->bNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}


 BOOL  bViewImAmList_isMgr(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	
	BOOL					bRet	=	FALSE;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpImAmListQueryStruct  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_imAmList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  NULL,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from (((qyImAmTab left join qyImObjAuthTab on (qyImAmTab.misServName=qyImObjAuthTab.misServName and qyImAmTab.idStr=qyImObjAuthTab.idStr)) left join qyImObjTab as A on (qyImObjAuthTab.misServName=A.misServName and qyImObjAuthTab.idStr=A.idstr)) left join qyImObjRegInfoTab as B on(qyImObjAuthTab.misServName=B.misServName and qyImObjAuthTab.idStr=B.idStr ) )"  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "1=1"  )  );
	if  (  wherePart  &&  wherePart[0]  ) _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s and %s"  ),  tmpSel.u.query.wherePart,  CString(  wherePart  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "qyImAmTab.idStr"  )  );
	
	tmpSel.u.query.data2DisplayProc			=  displayQnmElement;
	tmpSel.u.query.pfProcEvent				=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId				=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos				=  CONST_resId_popup_imAmList_isMgr;					//  2003/12/17修改
	//  tmpSel.u.query.ucbMultiSel				=  TRUE;															//  2007/08/24
	//  tmpSel.u.query.nSubMenuPos_multiSel		=  CONST_resId_popup_viewPhoneMessengerList_multiSel_isMgr;		//  200
	//  tmpSel.u.query.nSubMenuPos_notSel		=	CONST_resId_popup_viewPhoneMessengerList_notSel_isMgr;			//  2008/01/29	


	_sntprintf(  tmpSel.u.query.docName,  mycountof(  tmpSel.u.query.docName  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  " %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyImAmList  )  );
	
	bRet  =  pApp->bNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}


typedef  struct  __qnmTmpRcd_t  {
				 int			iType;
				 char			queryTime[CONST_qyTimeLen  +  1];
				 char			mac[CONST_qyMacLen  +  1];
				 char			ip[CONST_qyMaxIpLen  +  1];
				 TCHAR			col0[255  +  1];
				 TCHAR			des0[255  +  1];
}		 QNM_TMP_RCD;


 int  getMacInfo(  void  *  pDb,  char  *  mac,  QNM_MAC_INFO  *  pMacInfo  )
{
	 int				iErr			=	-1;
	 CString			sqlStr;
	 CDBVariant			varVals[10];
	 int				index;
	 TCHAR				tBuf[1024];
	 QY_MC			*	pQyMc			=	QY_GET_GBUF(  );

	 if  (  !bMacValid(  mac  )  )  return  -1;

	 	QM_dbFuncs  *  pDbFuncs  =  QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	 memset(  pMacInfo,  0,  sizeof(  pMacInfo[0]  )  );
	 safeStrnCpy(  mac,  pMacInfo->mac,  sizeof(  pMacInfo->mac  )  );

	 if  (  g_dbFuncs.pf_bGetPcInfoByMac(  pDb,  pMacInfo->mac,  FALSE,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  &pMacInfo->u.pcInfo.pcInfo,  &pMacInfo->u.pcInfo.regInfo  )  )  {
		 pMacInfo->ucbPc  =  TRUE;
		 iErr  =  0;  goto  errLabel;
	}	
	
	memset(  &pMacInfo->u,  0,  sizeof(  pMacInfo->u  )  );
	sqlStr  =  CString(  "select qySwitchPortTab.switchMac,qySwitchPortTab.portIfIndex,qySwitchPortTab.portIfDescr,qySwitchPortTab.portIfPhysAddress from qySwitchPortTab,qySnmpObjTab"  )
				+  CString(  " where qySwitchPortTab.portIfPhysAddress='"  )  +  CString(  pMacInfo->mac  )  +  CString(  "'"  )
				+  CString(  " and qySwitchPortTab.switchMac=qySnmpObjTab.mac"  );
	if  (  bQyGetRcdBySql(  pDb,  sqlStr.GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  {
		pMacInfo->ucbSnmpObj  =  TRUE;
		index  =  0;	//  switchMac
		MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pMacInfo->u.switchInfo.portInfo.switchMac,  sizeof(  pMacInfo->u.switchInfo.portInfo.switchMac  )  );
		index  ++  ;	//  portIfIndex
		if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  pMacInfo->u.switchInfo.portInfo.iPortIfIndex  =  varVals[index].m_lVal;
		index  ++  ;	//  portIfDescr
		MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pMacInfo->u.switchInfo.portInfo.portIfDescr,  sizeof(  pMacInfo->u.switchInfo.portInfo.portIfDescr  )  );
		index  ++  ;	//  portIfPhysAddress
		MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pMacInfo->u.switchInfo.portInfo.portIfPhysAddress,  sizeof(  pMacInfo->u.switchInfo.portInfo.portIfPhysAddress  )  );
		index  ++  ;	//  
		
		if  (  !bGetSnmpObjHeadInfoBySth(  pDb,  pMacInfo->u.switchInfo.portInfo.switchMac,  NULL,  &pMacInfo->u.switchInfo.snmpObjHead  )  )  goto  errLabel;
		
		iErr  =  0;  goto  errLabel;
	}		
	
	memset(  &pMacInfo->u,  0,  sizeof(  pMacInfo->u  )  );
	pMacInfo->ucbOtherMacs  =  TRUE;
	if  (  bGetMacDesByMac(  pDb,  pMacInfo->mac,  &pMacInfo->u.otherInfo.macDes  )  )  memset(  &pMacInfo->u,  0,  sizeof(  pMacInfo->u  )  );

	iErr  =  0;

errLabel:
	return  iErr;
	
}
 int  doQnmSearchIp(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  tIp  )
{
	 QY_MC			*	pQyMc								=		QY_GET_GBUF(  );
	 TCHAR				titleBuf[64];
	 char				timeBuf[CONST_qyTimeLen  +  1]		=		"";
	 TCHAR				sqlBuf[CONST_qyMaxSqlBufLen  +  1];
	 CString			macsCStr;
	 char				ip12[12  +  1]						=		"";
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  -1;			//  2007/01/05
	 CRecordset			rs(  (  CDatabase  *  )pObjDb->pDb  );
	 unsigned  int		index;
	 unsigned  int		nFields								=		0;
	 CDBVariant			varVals[10];
	 QNM_PC_INFO		pcInfo;
	 QY_SNMPOBJ_HEAD	snmpObjHead;
	 QNM_TMP_RCD		tmpRcd;
	 char				tmpIp12[12  +  1]					=		"";
	 int				iType_qnmTmpTab						=		pQyMc->cfg.iType_qnmTmpTab;
	 TCHAR			*	pStopString;
	 char				buf[256];
	 TCHAR				tBuf[256];
	 char				ip[256]								=		"";

	 if  (  !tIp  )  return  -1;
	 if  (  !myTChar2Str(  tIp,  ip,  mycountof(  ip  )  )  )  return  -1;	 
	 if  (  !bulIpValid(  inet_addr(  ip  )  )  )  return  -1;

	 getCurTime(  timeBuf  );
	 qyStdToIp12(  ip,  ip12  );
	 macsCStr  =  CString(  ""  );

	 try  {
			 
		     //  ÏÈ²éÕÒpcÐÅÏ¢
		     _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyPcTab.ip,qyPcTab.mac0,qyPcTab.mac1,qyPcTab.mac2,qyPcTab.nMacs from qyPcTab where qyPcTab.ip='%s' or qyPcTab.ip0='%s'  or qyPcTab.ip1='%s'  or qyPcTab.ip2='%s'"  ),  CString(  ip12  ),  CString(  ip12  ),  CString(  ip12  ),  CString(  ip12  )  );

			 if  (  !rs.Open( CRecordset::forwardOnly,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  {
		  		 debugLog(  "rs open() failed."  );  goto  errLabel;
		  	 }
	  		 nFields  =  rs.GetODBCFieldCount(  );
			 if  (  nFields  >  sizeof(  varVals  )  /  sizeof(  varVals[0]  )  )  goto  errLabel;
			 //  rs.GetODBCFieldInfo(  index,  tmpFieldInfo  );
			 for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {
						   
				   for  (  index  =  0;  index  <  (  int  )nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   	   
				   memset(  &pcInfo,  0,  sizeof(  pcInfo  )  );
				   memset(  &tmpRcd,  0,  sizeof(  tmpRcd  )  );
				   
				   index  =  0;		//  ip,
				   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  tmpIp12,  sizeof(  tmpIp12  )  );  qyIp12ToStd(  tmpIp12,  pcInfo.ip  );  
	 			   index  ++  ;		//  mac0,
				   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pcInfo.macs[0],  sizeof(  pcInfo.macs[0]  )  );  
	 			   index  ++  ;		//  mac1,
				   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pcInfo.macs[1],  sizeof(  pcInfo.macs[1]  )  );  
	 			   index  ++  ;		//  mac2,
				   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pcInfo.macs[2],  sizeof(  pcInfo.macs[2]  )  );  
	 			   index  ++  ;		//  nMacs
				   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  pcInfo.nMacs  =  _tcstol(  tBuf,  &pStopString,  10  );  
				   index  ++  ;
				   				   
				   //  ÕâÀïÒÔiType,queryTime,macÎª±êÊ¶
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(queryTime) from qnmTmpTab where iType=%d and queryTime='%s' and mac='%s'"  ),  iType_qnmTmpTab,  CString(  timeBuf  ),  CString(  pcInfo.macs[0]  )  );
				   if  (  !bSqlObjExists(  pObjDb->pDb,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  {
					   qyStdToIp12(  pcInfo.ip,  tmpIp12  );
				   	   _sntprintf(  tmpRcd.col0,  mycountof(  tmpRcd.col0  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_computer  )  );				   
				   	   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qnmTmpTab(iType,queryTime,mac,ip,col0,des0) values(%d,'%s','%s','%s','%s','%s')"  ),  iType_qnmTmpTab,  CString(  timeBuf  ),  CString(  pcInfo.macs[0]  ),  CString(  tmpIp12  ),  CString(  tmpRcd.col0  ),  tmpRcd.des0  );
				   	   bQyExecSql(  pObjDb->pDb,  CString(  sqlBuf  ).GetBuffer(  0  )  );
				   }

				   for  (  index  =  0;  index  <  min(  CONST_qnmMaxMacs,  pcInfo.nMacs  );  index  ++  )  {
					    if  (  bMacValid(  pcInfo.macs[index]  )  )  macsCStr  =  macsCStr  +  CString(  macsCStr.GetLength(  )  ?  ","  :  ""  )  +  CString(  "'"  )  +  CString(  pcInfo.macs[index]  )  +  CString(  "'"  );

				   }
				   traceLogA(  "doQnmSearchIp: ÔÚ´¦Àí¼ÆËã»ú%sºó, macsStr is %s",  pcInfo.ip,  macsCStr.GetBuffer(  0  )  );

			  }
			
			  rs.Close(  );

			  //  ÔÙ²éÕÒ½»»»»ú
			  memset(  &snmpObjHead,  0,  sizeof(  snmpObjHead  )  );
			  memset(  &tmpRcd,  0,  sizeof(  tmpRcd  )  );
			  if  (  bGetSnmpObjHeadInfoBySth(  pObjDb->pDb,  NULL,  ip,  &snmpObjHead  )  )  {

				  //  ÕâÀïÒÔiType,queryTime,macÎª±êÊ¶
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(queryTime) from qnmTmpTab where iType=%d and queryTime='%s' and mac='%s'"  ),  iType_qnmTmpTab,  CString(  timeBuf  ),  CString(  snmpObjHead.mac  )  );
				   if  (  !bSqlObjExists(  pObjDb->pDb,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  {
					   qyStdToIp12(  snmpObjHead.ip,  tmpIp12  );
					   _sntprintf(  tmpRcd.col0,  mycountof(  tmpRcd.col0  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_wangLuoSheBei  )  );
					   _sntprintf(  tmpRcd.des0,  mycountof(  tmpRcd.des0  ),  _T(  "%s( %s )"  ),  CString(  snmpObjHead.productName  ),  CString(  snmpObjHead.ip  )  );				   
					   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qnmTmpTab(iType,queryTime,mac,ip,col0,des0) values(%d,'%s','%s','%s','%s','%s')"  ),  iType_qnmTmpTab,  CString(  timeBuf  ),  CString(  snmpObjHead.mac  ),  CString(  tmpIp12  ),  tmpRcd.col0,  tmpRcd.des0  );
					   bQyExecSql(  pObjDb->pDb,  CString(  sqlBuf  ).GetBuffer(  0  )  );
				   }

				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qySwitchPortTab.portIfPhysAddress from qySwitchPortTab where qySwitchPortTab.switchMac='%s'"  ),  CString(  snmpObjHead.mac  )  );
				   
				   if  (  !rs.Open( CRecordset::forwardOnly,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  {
		  			   debugLog(  "rs open() failed."  );  goto  errLabel;
		  		   }
	  			   nFields  =  rs.GetODBCFieldCount(  );
				   if  (  nFields  >  sizeof(  varVals  )  /  sizeof(  varVals[0]  )  )  goto  errLabel;
				   //  rs.GetODBCFieldInfo(  index,  tmpFieldInfo  );
				   for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {
						   
					    for  (  index  =  0;  index  <  (  int  )nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   	  
						MACRO_sqlStr(  varVals[0],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );
						if  (  bMacValid(  buf  )  )  macsCStr  =  macsCStr  +  CString(  macsCStr.GetLength(  )  ?  ","  :  ""  )  +  CString(  "'"  )  +  CString(  buf  )  +  CString(  "'"  );
						
	
				   }

				   rs.Close(  );

				   traceLogA(  "doQnmSearchIp: ÔÚ´¦ÀíÍøÂçÉè±¸%sºó, macsStr is %s",  snmpObjHead.ip,  macsCStr.GetBuffer(  0  )  );

			  }

			  //  ×îºó²éÕÒÊ£ÓàµÄmac
			  MACRO_CStringTrim(  macsCStr  );
			  traceLogA(  "macsStr is %s",  macsCStr.GetBuffer(  0  )  );
			  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select distinct qySwitchConnectedPcTab.connectedMac,qySwitchConnectedPcTab.connectedIp from qySwitchConnectedPcTab where qySwitchConnectedPcTab.connectedIp='%s'"  ),  CString(  ip12  )  );
			  if  (  macsCStr.GetLength(  )  )  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s and qySwitchConnectedPcTab.connectedMac not in(%s)"  ),  sqlBuf,  macsCStr.GetBuffer(  0  )  );
			  traceLogA(  "sqlBuf is %s",  sqlBuf  );

			  if  (  !rs.Open( CRecordset::forwardOnly,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  {
				  debugLog(  "rs open() failed."  );  goto  errLabel;
			  }
			  nFields  =  rs.GetODBCFieldCount(  );
			  if  (  nFields  >  sizeof(  varVals  )  /  sizeof(  varVals[0]  )  )  goto  errLabel;
			  //  rs.GetODBCFieldInfo(  index,  tmpFieldInfo  );
			  for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {
				
				   for  (  index  =  0;  index  <  (  int  )nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   	  				
				   if  (  varVals[0].m_dwType  !=  DBVT_STRING  )  continue;
				   
				   memset(  &tmpRcd,  0,  sizeof(  tmpRcd  )  );
				   myTChar2Str(  varVals[0].m_pstring->GetBuffer(  0  ),  tmpRcd.mac,  sizeof(  tmpRcd.mac  )  );
				   if  (  varVals[1].m_dwType  ==  DBVT_STRING  )  {
					   myTChar2Str(  varVals[1].m_pstring->GetBuffer(  0  ),  buf,  sizeof(  buf  )  );
					   qyIp12ToStd(  buf,  tmpRcd.ip  );
				   }
				   if  (  getDesOfMac(  pObjDb,  tmpRcd.mac,  tmpRcd.des0,  sizeof(  tmpRcd.des0  ),  NULL  )  )  tmpRcd.des0[0]  =  0;

				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(queryTime) from qnmTmpTab where iType=%d and queryTime='%s' and mac='%s'"  ),  iType_qnmTmpTab,  CString(  timeBuf  ),  varVals[0].m_pstring->GetBuffer(  0  )  );
				   if  (  !bSqlObjExists(  pObjDb->pDb,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  {
					   qyStdToIp12(  tmpRcd.ip,  tmpIp12  );
					   _sntprintf(  tmpRcd.col0,  mycountof(  tmpRcd.col0  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_connection  )  );
					   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qnmTmpTab(iType,queryTime,mac,ip,col0,des0) values(%d,'%s','%s','%s','%s','%s')"  ),  iType_qnmTmpTab,  CString(  timeBuf  ),  varVals[0].m_pstring->GetBuffer(  0  ),  CString(  tmpIp12  ),  tmpRcd.col0,  tmpRcd.des0  );
					   bQyExecSql(  pObjDb->pDb,  CString(  sqlBuf  ).GetBuffer(  0  )  );
				   }
				  
			  }
			  
			  rs.Close(  );

		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doQnmSearchIp failed."  )  );
		   goto  errLabel;
	}
		 
	 //
	 _sntprintf(  titleBuf,  mycountof(  titleBuf  ),  _T(  "IP -- %s %s : "  ),  CString(  ip  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_searchOfResult  )  );
	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "iType=%d and queryTime='%s'"  ),  iType_qnmTmpTab,  CString(  timeBuf  )  );
	 bNetMcViewSearchListFunc(  pObjDb,  CONST_qyQueryType_ip,  titleBuf,  sqlBuf  );
	 
	 //  ²éÑ¯½áÊø

errLabel:
	
	 if  (  rs.IsOpen(  )  )  rs.Close(  );

	 return  0;
}

 int  doQnmSearchMac(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  tMac  )
{
	 QY_MC			*	pQyMc								=		QY_GET_GBUF(  );
	 TCHAR				titleBuf[64];
	 char				timeBuf[CONST_qyTimeLen  +  1]		=		"";
	 CString			macsCStr						;
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  -1;
	 CRecordset			rs(  (  CDatabase  *  )pObjDb->pDb  );
	 unsigned  int		nFields								=		0;
	 CDBVariant			varVals[10];
	 TCHAR				sqlBuf[CONST_qyMaxSqlBufLen  +  1];
	 QNM_TMP_RCD		tmpRcd;
	 char				tmpIp12[12  +  1]					=		"";
	 int				iType_qnmTmpTab						=		pQyMc->cfg.iType_qnmTmpTab;
	 struct								{
		QNM_MAC_INFO					macInfo;
		char							title[256];
		char							whereClause[CONST_qyMaxSqlBufLen  +  1];
	 }									m_var;
	 int				index  =  0;
	 char				buf[256];
	 TCHAR				tBuf[256];
	 char				mac[256]							=		"";

	 if  (  !tMac  )  return  -1;
	 if  (  !myTChar2Str(  tMac,  mac,  mycountof(  mac  )  )  )  return  -1;
	 if  (  !bMacValid(  mac  )  )  return  -1;

	 getCurTime(  timeBuf  );
	 macsCStr  =  CString(  ""  );
	 
	 memset(  &m_var,  0,  sizeof(  m_var  )  );

	 try  {
		
		  if  (  getMacInfo(  pObjDb->pDb,  mac,  &m_var.macInfo  )  )  goto  errLabel;
		  if  (  m_var.macInfo.ucbPc  )  {
			  //  ÕâÀïÒÔiType,queryTime,macÎª±êÊ¶
			  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(queryTime) from qnmTmpTab where iType=%d and queryTime='%s' and mac='%s'"  ),  iType_qnmTmpTab,  CString(  timeBuf  ),  CString(  m_var.macInfo.u.pcInfo.pcInfo.macs[0]  )  );
			  if  (  !bSqlObjExists(  pObjDb->pDb,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  {
				  memset(  &tmpRcd,  0,  sizeof(  tmpRcd  )  );
	 	  		  qyStdToIp12(  m_var.macInfo.u.pcInfo.pcInfo.ip,  tmpIp12  );
				  _sntprintf(  tmpRcd.col0,  mycountof(  tmpRcd.col0  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_computer  )  );				   
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qnmTmpTab(iType,queryTime,mac,ip,col0,des0) values(%d,'%s','%s','%s','%s','%s')"  ),  iType_qnmTmpTab,  CString(  timeBuf  ),  CString(  m_var.macInfo.u.pcInfo.pcInfo.macs[0]  ),  CString(  tmpIp12  ),  tmpRcd.col0,  tmpRcd.des0  );
				   bQyExecSql(  pObjDb->pDb,  CString(  sqlBuf  ).GetBuffer(  0  )  );
			  }
		  }
		  if  (  m_var.macInfo.ucbSnmpObj  )  {			  		  
			  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(queryTime) from qnmTmpTab where iType=%d and queryTime='%s' and mac='%s'"  ),  iType_qnmTmpTab,  CString(  timeBuf  ),  CString(  m_var.macInfo.u.pcInfo.pcInfo.macs[0]  )  );
			  if  (  !bSqlObjExists(  pObjDb->pDb,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  {
				  memset(  &tmpRcd,  0,  sizeof(  tmpRcd  )  );
	 	  		  qyStdToIp12(  m_var.macInfo.u.switchInfo.snmpObjHead.ip,  tmpIp12  );
				  _sntprintf(  tmpRcd.col0,  mycountof(  tmpRcd.col0  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_wangLuoSheBei  )  );				   
				  _sntprintf(  tmpRcd.des0,  mycountof(  tmpRcd.des0  ),  _T(  "%s( %s  ) %s %d"  ),  CString(  m_var.macInfo.u.switchInfo.snmpObjHead.productName  ),  CString(  m_var.macInfo.u.switchInfo.snmpObjHead.ip  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_port  ),  m_var.macInfo.u.switchInfo.portInfo.iPortIfIndex  );
				  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qnmTmpTab(iType,queryTime,mac,ip,col0,des0) values(%d,'%s','%s','%s','%s','%s')"  ),  iType_qnmTmpTab,  CString(  timeBuf  ),  CString(  m_var.macInfo.u.switchInfo.snmpObjHead.mac  ),  CString(  tmpIp12  ),  tmpRcd.col0,  tmpRcd.des0  );
				  bQyExecSql(  pObjDb->pDb,  CString(  sqlBuf  ).GetBuffer(  0  )  );
			  }
		  }
		  if  (  m_var.macInfo.ucbOtherMacs  )  {

			  //  ×îºó²éÕÒÊ£ÓàµÄmac
			  MACRO_CStringTrim(  macsCStr  );
			  traceLogA(  "macsStr is %s",  macsCStr.GetBuffer(  0  )  );
			  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select distinct qySwitchConnectedPcTab.connectedMac,qySwitchConnectedPcTab.connectedIp from qySwitchConnectedPcTab where qySwitchConnectedPcTab.connectedMac='%s'"  ),  CString(  mac  )  );
			  if  (  macsCStr.GetLength(  )  )  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s and qySwitchConnectedPcTab.connectedMac not in(%s)"  ),  sqlBuf,  macsCStr.GetBuffer(  0  )  );
			  traceLogA(  "sqlBuf is %s",  sqlBuf  );

			  if  (  !rs.Open( CRecordset::forwardOnly,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  {
				  debugLog(  "rs open() failed."  );  goto  errLabel;
			  }
			  nFields  =  rs.GetODBCFieldCount(  );
			  if  (  nFields  >  sizeof(  varVals  )  /  sizeof(  varVals[0]  )  )  goto  errLabel;
			  //  rs.GetODBCFieldInfo(  index,  tmpFieldInfo  );
			  for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {
				
				   for  (  index  =  0;  index  <  (  int  )nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   	  				   
				   memset(  &tmpRcd,  0,  sizeof(  tmpRcd  )  );
				   
				   index  =  0;
				   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  tmpRcd.mac,  sizeof(  tmpRcd.mac  )  );
				   index  ++  ;
				   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );  qyIp12ToStd(  buf,  tmpRcd.ip  );
				   
				   if  (  !bMacValid(  tmpRcd.mac  )  )  continue;

				   if  (  getDesOfMac(  pObjDb,  tmpRcd.mac,  tmpRcd.des0,  sizeof(  tmpRcd.des0  ),  NULL  )  )  tmpRcd.des0[0]  =  0;

				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(queryTime) from qnmTmpTab where iType=%d and queryTime='%s' and mac='%s'"  ),  iType_qnmTmpTab,  CString(  timeBuf  ),  CString(  tmpRcd.mac  )  );
				   if  (  !bSqlObjExists(  pObjDb->pDb,  sqlBuf  )  )  {
					   qyStdToIp12(  tmpRcd.ip,  tmpIp12  );
					   _sntprintf(  tmpRcd.col0,  mycountof(  tmpRcd.col0  ),  _T(  "%s"  ),  getResStr(  0, &pQyMc->cusRes,  CONST_resId_connection  )  );
					   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qnmTmpTab(iType,queryTime,mac,ip,col0,des0) values(%d,'%s','%s','%s','%s','%s')"  ),  iType_qnmTmpTab,  CString(  timeBuf  ),  CString(  tmpRcd.mac  ),  CString(  tmpIp12  ),  tmpRcd.col0,  tmpRcd.des0  );
					   bQyExecSql(  pObjDb->pDb,  sqlBuf  );
				   }
				  
			  }
			  
			  rs.Close(  );

		  }
			 
	 		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doQnmSearchMac failed."  )  );
		   goto  errLabel;
	}
		 
	 //
	 _sntprintf(  titleBuf,  mycountof(  titleBuf  ),  _T(  "MAC -- %s %s : "  ),  CString(  mac  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_searchOfResult  )  );
	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "iType=%d and queryTime='%s'"  ),  iType_qnmTmpTab,  CString(  timeBuf  )  );
	 bNetMcViewSearchListFunc(  pObjDb,  CONST_qyQueryType_mac,  titleBuf,  sqlBuf  );

errLabel:

	 return  0;
	 
}

//
int  tmpHandler_procLvEventFunc_is(  QY_EVENTINFO  *  pEventInfo,  void  *  pObjDbParam,  int  iLvType,  int  curnItem,  BOOL  bFirst,  void  *  pParam0  )
{
	int									iErr											=		-1;
	QY_MC							*	pQyMc											=		QY_GET_GBUF(  );
	QY_OBJ_DB						*	pObjDb											=		(  QY_OBJ_DB  *  )pObjDbParam;
	unsigned  char						ucbRefreshed									=		FALSE;
	HWND								hParent											=		pEventInfo->hWnd;
	unsigned  int						uiCmd											=		pEventInfo->uiCmd;  
	unsigned  int						uiType											=		0;
	TCHAR								misServName[CONST_maxMisServNameLen  +  1]		=		_T(  ""  );
	QY_MESSENGER_ID						idInfo;
	char								idStr[CONST_qyMessengerIdStrLen  +  1]			=		"";
	TCHAR								colName[255]									=		_T(  ""  );
	TCHAR								tBuf[255  +  1]									=		_T(  ""  );
	char								buf[255  +  1]									=		"";
	PARAM_procLvEventFunc_is		*	pParam											=		(  PARAM_procLvEventFunc_is  *  )pParam0;
	TCHAR								sqlBuf[CONST_maxSqlBufLen  +  1]				=		_T(  ""  );
	TCHAR								displayName[128]								=		_T(  ""  );
	MSGR_ADDR							addr;
	//


	QM_dbFuncs  *  pDbFuncs  =  QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	if  (  curnItem  <  0  )  {		//  µã»÷¿Õ°×´¦µÄ´¦Àí
		switch  (  iLvType  )  {
				case  CONST_qyQueryType_ipKnowledgeList:
					  //
					  uiType  =  CONST_imCommType_ipKnowledge;
					  ucbRefreshed  =  TRUE;
					  //									
					  switch  (  uiCmd  )  {
							  case  ID_addModuleKnowlege:  {			//  2006/04/16	
									#ifndef  __isCli__
							        CDlgCfgIpKnowledge	dlg;
									if  (  !dlg.bSetDlgInfo(  0,  pObjDb,  0  )  )  goto  errLabel;
									if  (  dlg.DoModal(  )  !=  IDOK  )  ucbRefreshed  =  FALSE;
									#endif
									iErr  =  0;  goto  errLabel;
									//
								    }
								    break;
							  case  ID_importModuleKnowlege:
								    //
									if  (  !bImportKnowledge(  uiType  )  )  ucbRefreshed  =  FALSE;				  
									iErr  =  0;  goto  errLabel;
									break;
							  case  ID_exportModuleKnowlege:
									//
									if  (  !bExportKnowledge(  uiType  )  )  ucbRefreshed  =  FALSE;
									iErr  =  0;  goto  errLabel;
									break;
							  case  ID_clearupModuleKnowlege:
								    //
								    if  (  !bClearupKnowledge(  uiType  )  )  ucbRefreshed  =  FALSE;
									iErr  =  0;  goto  errLabel;
									break;
							  default:
									 break;
					  }
					  //
					  break;	
				case  CONST_qyQueryType_phoneGuestList:
					  //
					  uiType  =  CONST_imCommType_phoneGuest;
					  ucbRefreshed  =  TRUE;
					  //
					  switch  (  uiCmd  )  {
							  case  ID_qyAdd:  {
									#ifndef  __isCli__
								    CDlgCfgPhoneMessenger	dlg;
									if  (  !dlg.bSetDlgInfo(  0,  pObjDb,  NULL,  TRUE,  0,  0  )  )  goto  errLabel;
									if  (  dlg.DoModal(  )  !=  IDOK  )  ucbRefreshed  =  FALSE;
									#endif
									iErr  =  0;  goto  errLabel;
									}
								    break;
							  case  ID_qyImport:
								    if  (  !bImportKnowledge(  uiType  )  )  ucbRefreshed  =  FALSE;
									iErr  =  0;  goto  errLabel;
								    break;
							  case  ID_qyExport:
								    if  (  !bExportKnowledge(  uiType  )  )  ucbRefreshed  =  FALSE;
									iErr  =  0;  goto  errLabel;
								    break;
							  case  ID_qyClearUp:
									if  (  !bClearupKnowledge(  uiType  )  )  ucbRefreshed  =  FALSE;
									iErr  =  0;  goto  errLabel;
								    break;
							  default:
									 break;
					  }
					  //
					  break;
				case  CONST_qyQueryType_phoneMessengerList:
					  //
					  switch  (  uiCmd  )  {
							  case  ID_qyAdd:  {
									#ifndef  __isCli__
								    CDlgCfgPhoneMessenger		dlg;
									if  (  !dlg.bSetDlgInfo(  0,  pObjDb,  NULL,  FALSE,  0,  0  )  )  goto  errLabel;
									if  (  dlg.DoModal(  )  ==  IDOK  )  ucbRefreshed  =  TRUE;
									#endif
									iErr  =  0;  goto  errLabel;
									}
								    break;
							  default:
									 break;
					  }
					  //
					  break;

				case  CONST_qyQueryType_sharedDynBmpList:  
					  //		  
					  switch  (  uiCmd  )  {
						      //  isClient
							  case  ID_retrieveAll:  {
								    MIS_CNT			*	pMisCnt		=	NULL;

									if  (  !(  pMisCnt  =  getMisCntByName(  pQyMc,  NULL,  _T(  ""  )  )  )  )  goto  errLabel;
									sndRetrieveDynBmpsReq_qmc(  pMisCnt,  TRUE  );
									}		
									break;
							  default:
									  break;
					  }
					  //					  
					  break;

				default:
						break;
		}

		iErr  =  0;  goto  errLabel;
	}

	//  ÏÂÃæ±íÃ÷ÊÇÑ¡ÖÐÄ³¼¸ÐÐ½øÐÐ´¦Àí¡£
	//
	if  (  getKeyNameByLvType(  iLvType,  colName,  mycountof(  colName  )  )  )  goto  errLabel;	
	
	HWND	hList	=	pEventInfo->hFrom;
	if  (  getLvColContent(  hParent,  hList,  curnItem,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_servName  ),  misServName,  mycountof(  misServName  )  )  )  misServName[0]  =  0;
	if  (  getLvColContent(  hParent,  hList,  curnItem,  colName,  tBuf,  mycountof(  tBuf  )  )  )  {
		traceLogA(  "netMc_procEventFunc´íÎó: Ã»ÓÐÕÒµ½À¸Ä¿%sÏàÓ¦µÄÄÚÈÝ",  colName  );  goto  errLabel;
	}
	myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );

	switch  (  iLvType  )  {
			case  CONST_qyQueryType_ipKnowledgeList:
				  //
				  switch  (  uiCmd  )  {
						  case  ID_editModuleKnowlege:  {
								#ifndef  __isCli__
							    CDlgCfgIpKnowledge	dlg;
								//
								if  (  !dlg.bSetDlgInfo(  0,  pObjDb,  atol(  buf  )  )  )  goto  errLabel;
								if  (  dlg.DoModal(  )  ==  IDOK  )  ucbRefreshed  =  TRUE;
								#endif
								}
							    break;
						  case  ID_delModuleKnowlege:
								#ifndef  __isCli__
							    if  (  bFirst  )  {
									if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askIfDeleteInfo  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
								}
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where id=%d"  ),  CONST_tabName_qyIpKnowledgeTab,  atol(  buf  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
								ucbRefreshed  =  TRUE;
								#endif
							    break;
						  case  ID_qyProp_pcModuleKnowlege:  {
								#ifndef  __isCli__
							    CDlgPropIpKnowledge		dlg;
								if  (  !dlg.bSetDlgInfo(  0,  pObjDb,  atol(  buf  )  )  )  goto  errLabel;
								dlg.DoModal(  );
								#endif
								}
							    break;
						  default:
								  break;
				  }
				  //
				  iErr  =  0;  goto  errLabel;
				  //
				  break;
			case  CONST_qyQueryType_imObjAuthList:
			case  CONST_qyQueryType_imGrpAuthList:  {
				  #ifndef  __isCli__
				  QY_MESSENGERAUTH_RCD		authInfo;
				  //
				  if  (  !bGetMessengerAuthRcdBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  NULL,  NULL,  NULL,  NULL,  atol(  buf  ),  &authInfo  )  )  goto  errLabel;
				  //
				  uiType  =  authInfo.uiType;
				  lstrcpyn(  misServName,  authInfo.misServName,  mycountof(  misServName  )  );
				  idInfo.ui64Id  =  authInfo.idInfo.ui64Id;
				  #endif
				  }
				  break;
			case  CONST_qyQueryType_imAmList:  {
				  QY_imAm_RCD			imAm;
				  //
				  if  (  !g_dbFuncs.pf_bGetImAmRcdBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  NULL,  NULL,  NULL,  atol(  buf  ),  &imAm  )  )  goto  errLabel;
				  //
				  uiType  =  CONST_objType_messenger;
				  lstrcpyn(  misServName,  imAm.misServName,  mycountof(  misServName  )  );
				  idInfo.ui64Id  =  imAm.idInfo.ui64Id;
				  }
				  break;				  
			case  CONST_qyQueryType_phoneMessengerList:  {
				  QY_MESSENGER_phoneInfo		rcd;
				  //
				  if  (  !g_dbFuncs.pf_bGetMessengerPhoneInfoBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  0,  0,  0,  0,  atol(  buf  ),  &rcd  )  )  goto  errLabel;
				  //
				  uiType  =  CONST_objType_phoneMessenger;
				  lstrcpyn(  misServName,  rcd.misServName,  mycountof(  misServName  )  );
				  idInfo.ui64Id  =  rcd.idInfo.ui64Id;
				  //
				  switch  (  uiCmd  )  {
						  case  ID_qyDel:
							    if  (  bFirst  )  {
									if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askIfDeletePhoneNumber  )/*_T(  "È·ÊµÒªÉ¾³ýÊÖ»úÐÅÏ¢Âð?"  )*/,  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
								}
								_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where id=%d"  ),  CONST_tabName_qyMessengerPhoneInfoTab,  atol(  buf  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
								ucbRefreshed  =  TRUE;
							    iErr  =  0;  goto  errLabel;
							    break;
						  default:
								 break;
				  }
				  }
				  break;
			case  CONST_qyQueryType_imObjList:  
			case  CONST_qyQueryType_clientList_is:  {
				  QY_MESSENGER_REGINFO		regInfo;
				  QY_MESSENGER_phoneInfo	phoneInfo;
				  MY_REG_DESC				desc;

				  uiType  =  CONST_objType_messenger;
				  //  misServName
				  idStr2Info(  buf,  &idInfo  );
				  //
				  memset(  &addr,  0,  sizeof(  addr  )  );
				  lstrcpyn(  addr.misServName,  misServName,  mycountof(  addr.misServName  )  );
				  addr.uiObjType  =  CONST_objType_messenger;
				  addr.idInfo.ui64Id  =  idInfo.ui64Id;
				  //
				  if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  addr.misServName,  &addr.idInfo,  0,  NULL,  &regInfo,  NULL,  &phoneInfo  )  )  {
					  memset(  &regInfo,  0,  sizeof(  regInfo  )  );
					  memset(  &phoneInfo,  0,  sizeof(  phoneInfo  )  );
					  //
				  }				  
				  regInfo2Desc(  0,  &regInfo,  &desc,  NULL,  0,  addr.displayName,  mycountof(  addr.displayName  )  );
				  //				  
				  switch  (  uiCmd  )  {
						  case  ID_qySendSm:
							    //
							    if  (  phoneInfo.wDevIdStr[0]  )  {		//  
									if  (  qPostMsg(  &addr,  sizeof(  addr  ),  &pParam->tmpGrpMemQ  )  )  goto  errLabel;		
								}
								//
								iErr  =  0;  goto  errLabel;
							    break;
						  case  ID_qyRule:  {						//  2010/09/06
								#if  defined  __isCli__  ||  defined  __APP_qyMc_touchscreen__
								CDlgImObjRule					dlg;
								if  (  !dlg.bSetDlgInfo(  addr.misServName,  &addr.idInfo  )  )  goto  errLabel;
								dlg.DoModal(  );
								#endif
							    }
							    //
							    iErr  =  0;  goto  errLabel;
								break;
						  default:
								  break;
				  }
				  //
				  }
				  break;
			case  CONST_qyQueryType_customerServiceList:
				  uiType  =  CONST_objType_messenger;
				  //
				  idStr2Info(  buf,  &idInfo  );
				  //
				  switch  (  uiCmd  )  {
						  case  ID_qyDel:
 							    if  (  !idInfo2Str(  &idInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where misServName=%s and idStr='%s'"  ),  CONST_tabName_qyCustomerServiceObjTab,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
							    ucbRefreshed  =  TRUE;
								iErr  =  0;  goto  errLabel;
							    break;
						  default:
								  break;
				  }
				  break;
			case  CONST_qyQueryType_wwwQmCfgList:  
				  uiType  =  CONST_objType_messenger;
				  //  misServName
				  idStr2Info(  buf,  &idInfo  );
				  //
				  switch  (  uiCmd  )  {
						  case  ID_qyDel:
 							    if  (  !idInfo2Str(  &idInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where misServName=%s and idStr='%s'"  ),  CONST_tabName_qyWebContactTab,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
							    ucbRefreshed  =  TRUE;
								iErr  =  0;  goto  errLabel;
							    break;
						  default:
								  break;
				  }
				  break;
			case  CONST_qyQueryType_phoneGuestList:  {
				  PHONE_GUEST_RCD			guest;
				  QY_MESSENGER_REGINFO		regInfo;
				  MY_REG_DESC				desc;
				  //
				  if  (  !bGetPhoneGuestRcdBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  0,  0,  0,  atol(  buf  ),  &guest  )  )  goto  errLabel;
				  //
				  memset(  &addr,  0,  sizeof(  addr  )  );
				  lstrcpyn(  addr.misServName,  misServName,  mycountof(  addr.misServName  )  );
				  addr.uiObjType  =  CONST_objType_phoneGuest;
				  addr.uiDevType  =  guest.uiDevType;
				  lstrcpyn(  addr.wDevIdStr,  guest.wDevIdStr,  mycountof(  addr.wDevIdStr  )  );
				  //  _sntprintf(  addr.displayName,  mycountof(  addr.displayName  ),  _T(  "%s"  ),  guest.
				  //
				  if  (  !g_dbFuncs.pf_bGetImOtherRegInfoBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImOtherRegInfoTab,  &addr,  0,  &regInfo  )  )  memset(  &regInfo,  0,  sizeof(  regInfo  )  );
				  //
				  if  (  regInfo2Desc(  0,  &regInfo,  &desc,  NULL,  0,  addr.displayName,  mycountof(  addr.displayName  )  )  )  goto  errLabel;
				  //
				  switch  (  uiCmd  )  {
						  case  ID_qySendSm:
							    //  ¼Óµ½¶ÓÁÐÖÐ£¬ÔÚÑ­»·½áÊøºóÔÙµ÷ÓÃtalkTo...
							    if  (  qPostMsg(  &addr,  sizeof(  addr  ),  &pParam->tmpGrpMemQ  )  )  goto  errLabel;							    
							    break;
						  case  ID_qyEdit:  {
								#if  10  //  ndef  __isCli__
							    CDlgQnmEditPcUsrInfo		dlg;
					   			//
					   			if  (  !dlg.bSetDlgInfo(  pObjDb,  &addr,  0,  FALSE  )  )  goto  errLabel;
					   			//
					   			if  (  dlg.DoModal(  )  ==  IDOK  &&  dlg.m_var.ucbChanged  )  ucbRefreshed  =  TRUE;							    
								#endif

							    }
							    break;
						  case  ID_qyDel:
							    if  (  bFirst  )  {
									if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askIfDeleteInfo  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
								}
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where misServName=%s and uiDevType=%d and wDevIdStr=%s"  ),  CONST_tabName_qyImOtherRegInfoTab,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  addr.uiDevType,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_wDevIdStr,  addr.wDevIdStr  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where id=%d"  ),  CONST_tabName_qyPhoneGuestTab,  atol(  buf  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
								ucbRefreshed  =  TRUE;
							    break;
						  case  ID_qyProperties:  {
							    CDlgPropMessenger		dlg;
					   			//
					   			if  (  !dlg.bSetDlgInfo(  pObjDb,  &addr  )  )  goto  errLabel;
					   			dlg.DoModal(  );
								}
							    break;
						  default:
								 break;
				  }
				  //
				  }
				  //
				  iErr  =  0;  goto  errLabel;				  
				  //
				  break;
			case  CONST_qyQueryType_gsmModemList:  {
				  //
				  QY_VDEVCOM_RCD		rcd;

				  if  (  !bGetQyVDevComRcdBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  0,  0,  0,  atol(  buf  ),  &rcd  )  )  goto  errLabel;

				  memset(  &addr,  0,  sizeof(  addr  )  );
				  lstrcpyn(  addr.misServName,  misServName,  mycountof(  addr.misServName  )  );
				  addr.idInfo.ui64Id  =  rcd.idInfo.ui64Id;
				  //
				  idInfo2Str(  &addr.idInfo,  idStr,  mycountof(  idStr  )  );
				  //
				  switch  (  uiCmd  )  {
						  case  ID_qyProperties:  {
							    CDlgPropMessenger		dlg(  CWnd::FromHandle(  pEventInfo->hWnd  )  );
								//
								if  (  !dlg.bSetDlgInfo(  pObjDb,  &addr  )  )  goto  errLabel;
								dlg.DoModal(  );
							    }
							    break;
						  case  ID_qyCfgSmContact:  {
								#ifndef  __isCli__
							    CDlgCfgGsmModem			dlg(  CWnd::FromHandle(  pEventInfo->hWnd  )  );
								//
								if  (  !dlg.bSetDlgInfo(  0,  pObjDb,  addr.misServName,  &addr.idInfo,  rcd.wDevIdStr,  FALSE,  0  )  )  goto  errLabel;
								dlg.DoModal(  );
								#endif
								}
							    break;
						  case  ID_qyCfgDefaultSmContact:  {
								#ifndef  __isCli__
							    CDlgCfgGsmModem			dlg(  CWnd::FromHandle(  pEventInfo->hWnd  )  );
								//
								if  (  !dlg.bSetDlgInfo(  0,  pObjDb,  addr.misServName,  &addr.idInfo,  _T(  ""  ),  FALSE,  0  )  )  goto  errLabel;
								dlg.DoModal(  );
								#endif
								}
							    break;
						  case  ID_qyCfgDefaultSmServer:  {
								#ifndef  __isCli__
							    CDlgCfgGsmModem			dlg(  CWnd::FromHandle(  pEventInfo->hWnd  )  );
								//
								if  (  !dlg.bSetDlgInfo(  0,  pObjDb,  addr.misServName,  &addr.idInfo,  _T(  ""  ),  TRUE,  0  )  )  goto  errLabel;
								dlg.DoModal(  );
								#endif
								}
							    break;
						  case  ID_qyViewSmContacts:
								#ifndef  __isCli__
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qySmContactTab.misServName=%s and qySmContactTab.idStr='%s'"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  )  );
								_sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%I64u"  ),  addr.idInfo.ui64Id  );
								bViewSmContactList_isMgr(   pObjDb,  displayName,  sqlBuf  );
								#endif
							    break;
						  case  ID_qyDel:  
							    if  (  bFirst  )  {
									if  (  AfxMessageBox(  _T(  "Are you sure to delete some information and rules of SM device ?"  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
								}
								_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where misServName=%s and idStr='%s'"  ),  CONST_tabName_qySmContactTab,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
								_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where misServName=%s and idStr='%s'"  ),  CONST_tabName_qyVDevComTab,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
								//
								ucbRefreshed  =  TRUE;
							    break;
						  default:
								 break;
				  }
				  //
				  }
				  iErr  =  0;  goto  errLabel;
				  break;
			case  CONST_qyQueryType_smContactList:  {
				  //
				  QY_SMCONTACT_RCD			rcd;

				  if  (  !bGetQySmContactRcdBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  0,  0,  0,  0,  atol(  buf  ),  &rcd  )  )  goto  errLabel;

				  memset(  &addr,  0,  sizeof(  addr  )  );
				  lstrcpyn(  addr.misServName,  misServName,  mycountof(  addr.misServName  )  );
				  addr.idInfo.ui64Id  =  rcd.idInfo.ui64Id;
				  //
				  switch  (  uiCmd  )  {
						  case  ID_qyProperties:  {
							    CDlgPropMessenger		dlg(  CWnd::FromHandle(  pEventInfo->hWnd  )  );
								//
								if  (  !dlg.bSetDlgInfo(  pObjDb,  &addr  )  )  goto  errLabel;
								dlg.DoModal(  );
							    }
							    break;
						  case  ID_qyEdit:  {
								#ifndef  __isCli__
							    CDlgCfgGsmModem			dlg(  CWnd::FromHandle(  pEventInfo->hWnd  )  );
								//
								if  (  !dlg.bSetDlgInfo(  0,  pObjDb,  addr.misServName,  &addr.idInfo,  rcd.wDevIdStr,  rcd.ucbDefaultSmServer,  0  )  )  goto  errLabel;
								if  (  dlg.DoModal(  )  ==  IDOK  )  ucbRefreshed  =  TRUE;
								#endif
								}
							    break;						  
						  case  ID_qyDel:  {
							    if  (  bFirst  )  {
									if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askIfDeleteInfo  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
								}
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where id=%d"  ),  CONST_tabName_qySmContactTab,  atol(  buf  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
								ucbRefreshed  =  TRUE;							    
								}
							    break;
						  default:
								 break;
				  }
				  

				  }
				  //
				  iErr  =  0;  goto  errLabel;
				  break;
			case  CONST_qyQueryType_tmpGrpMemList:  {
				  //
				  memset(  &addr,  0,  sizeof(  addr  )  );
				  lstrcpyn(  addr.misServName,  misServName,  mycountof(  addr.misServName  )  );
				  addr.uiObjType  =  CONST_objType_phoneGuest;
				  addr.uiDevType  =  CONST_objType_phone;
				  lstrcpyn(  addr.wDevIdStr,  tBuf,  mycountof(  addr.wDevIdStr  )  );
				  //  
				  switch  (  uiCmd  )  {
						  case  ID_qyProperties:  {
							    CDlgPropMessenger		dlg(  CWnd::FromHandle(  pEventInfo->hWnd  )  );
								//
								if  (  !dlg.bSetDlgInfo(  pObjDb,  &addr  )  )  goto  errLabel;
								dlg.DoModal(  );
								//
							    }
							    break;
						  default:
								  break;				  
				  }
				  //
				  }
				  //
				  iErr  =  0;  goto  errLabel;
				  //
				  break;
			case  CONST_qyQueryType_imGrpList:
				  QY_MESSENGER_INFO			messengerInfo;
				  //
				  if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  0,  NULL,  atol(  buf  ),  &messengerInfo,  NULL,  NULL,  NULL  )  )  goto  errLabel;
				  //
				  uiType  =  messengerInfo.uiType;
				  lstrcpyn(  misServName,  messengerInfo.misServName,  mycountof(  misServName  )  );
				  idInfo.ui64Id  =  messengerInfo.idInfo.ui64Id;
				  break;
			case  CONST_qyQueryType_imObjRegInfoList:
			case  CONST_qyQueryType_imObjRegInfoInTab1List:
				  QY_MESSENGER_REGINFO		regInfo;
				  TCHAR					*	pTabName;
				  pTabName  =  (  iLvType  ==  CONST_qyQueryType_imObjRegInfoList  )  ?  CONST_tabName_qyImObjRegInfoTab  :  CONST_tabName_qyImObjRegInfoTab1;
				  //
				  if  (  !g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  pTabName,  0,  NULL,  atol(  buf  ),  &regInfo  )  )  goto  errLabel;
				  //
				  uiType  =  CONST_objType_messenger;
				  lstrcpyn(  misServName,  regInfo.addr.misServName,  mycountof(  misServName  )  );
				  idInfo.ui64Id  =  regInfo.addr.idInfo.ui64Id;
				  break;
			case  CONST_qyQueryType_imGrpMemList:
				  IM_GRP_MEM						grpMem;

				  //
				  if  (  !g_dbFuncs.pf_bGetImGrpMemBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  NULL,  NULL,  NULL,  atol(  buf  ),  &grpMem  )  )  goto  errLabel;
				  //		  
				  switch  (  uiCmd  )  {
						  case  ID_qyDel:
							    if  (  bFirst  )  {
									if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askIfRemoveFromGroup ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
									time(  &pParam->t  );
									pParam->idInfo_grp.ui64Id  =  grpMem.idInfo_grp.ui64Id;
								}
								_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where id=%d"  ),  CONST_tabName_qyImGrpMemTab,  atol(  buf  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
								//
								//  É¾³ý³ÉÔ±ÒªÍ¨Öª·þÎñÆ÷Ë¢ÐÂ
								PARAM_applyForServWork		tmpParam;							
								memset(  &tmpParam,  0,  sizeof(  tmpParam  )  );
								tmpParam.uiType  =  CONST_imCommType_refreshImGrp;
								tmpParam.p0  =  &pParam->idInfo_grp;
								if  (  memcmp(  &tmpParam,  &pParam->param_applyForServWork,  sizeof(  tmpParam  )  )  )  {
									if  (  pParam->param_applyForServWork.uiType  )  {
										if  (  applyForServWork(  pParam->param_applyForServWork.uiType,  pParam->param_applyForServWork.p0,  pParam->param_applyForServWork.p1,  pParam->param_applyForServWork.p2  )  )  goto  errLabel;
									}
									memcpy(  &pParam->param_applyForServWork,  &tmpParam,  sizeof(  pParam->param_applyForServWork  )  );
								}								
								//
								ucbRefreshed  =  TRUE;
								iErr  =  0;  goto  errLabel;
							    break;
						  case  ID_qyImGrpList:
						  case  ID_qyAddTo:
						  case  ID_qyProperties:  
						  case  ID_qyTalk:
						  default:
							    uiType  =  CONST_objType_messenger;
								lstrcpyn(  misServName,  grpMem.misServName,  mycountof(  misServName  )  );
								idInfo.ui64Id  =  grpMem.idInfo_mem.ui64Id;
								break;
				  }	
				  break;
			case  CONST_qyQueryType_imMsgList:
				  IM_MSG_RCD					imMsg;
				  //
				  if  (  !g_dbFuncs.pf_bGetImMsgRcdBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  atol(  buf  ),  &imMsg  )  )  goto  errLabel;
								
				  switch  (  uiCmd  )  {
						  case  ID_qyTalkToTaskPeer:
							    QY_MESSENGER_INFO				messenger_send,  messenger_recv;
							    QY_MESSENGER_ID					idInfo_peer;
							    // 
								if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  imMsg.misServName,  &imMsg.idInfo_send,  0,  &messenger_send,  NULL,  NULL,  NULL  )  )  goto  errLabel;
								if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  imMsg.misServName,  &imMsg.idInfo_recv,  0,  &messenger_recv,  NULL,  NULL,  NULL  )  )  goto  errLabel;
								//
								idInfo_peer.ui64Id  =  0;
								if  (  messenger_recv.uiType  ==  CONST_objType_imGrp  )  idInfo_peer.ui64Id  =  messenger_recv.idInfo.ui64Id;
								else  if  (  messenger_send.uiType  !=  CONST_objType_me  )  idInfo_peer.ui64Id  =  messenger_send.idInfo.ui64Id;
								else  if  (  messenger_recv.uiType  !=  CONST_objType_me  )  idInfo_peer.ui64Id  =  messenger_recv.idInfo.ui64Id;
								else  goto  errLabel;
				  
								memset(  &addr,  0,  sizeof(  addr  )  );
								lstrcpyn(  addr.misServName,  imMsg.misServName,  mycountof(  addr.misServName  )  );
								addr.idInfo.ui64Id  =  idInfo_peer.ui64Id;
								//
								//  if  (  talkToMessenger(  pQyMc,  &addr,  NULL,  FALSE,  TRUE,  NULL  )  )  goto  errLabel;
								if  (  tryToTalkToMessenger(  &addr,  TRUE,  NULL  )  )  goto  errLabel;
								//
                                break;
						  case  ID_qyProp_imTask:  {
							    CDlgPropImMsg			dlg;

								if  (  !dlg.bSetDlgInfo(  pObjDb,  atol(  buf  )  )  )  goto  errLabel;
								dlg.DoModal(  );
								}
							    break;
						  default:
								 break;
				  }
				  break;
			case  CONST_qyQueryType_imTaskList:
			case  CONST_qyQueryType_imTaskHisList:
				  //
				  switch  (  uiCmd  )  {
						  case  ID_qyTalkToTaskPeer:  {
					     	    IM_TASK_RCD			imTask;
								QY_MESSENGER_ID		idInfo_peer;
								BOOL				bHisTab		=	FALSE;
								HWND				hWnd		=	NULL;
								QY_WMBUF_COMM		wmBuf;
								MIS_CNT			*	pMisCnt		=	NULL;
								//
								ucbRefreshed  =  FALSE;
								//						 					     
								bHisTab  =  iLvType  ==  CONST_qyQueryType_imTaskHisList;
								//
								if  (  !g_dbFuncs.pf_bGetImTaskRcdBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  bHisTab,  NULL,  NULL,  0,  0,  atol(  buf  ),  &imTask  )  )  goto  errLabel;
								if  (  !(  pMisCnt  =  getMisCntByName(  pQyMc,  NULL,  imTask.misServName  )  )  )  goto  errLabel;
								if  (  !pMisCnt->idInfo.ui64Id  )  goto  errLabel;
								if  (  pMisCnt->idInfo.ui64Id  ==  imTask.idInfo_send.ui64Id  )  idInfo_peer.ui64Id  =  imTask.idInfo_recv.ui64Id;
								else  idInfo_peer.ui64Id  =  imTask.idInfo_send.ui64Id;

								/*
								switch  (  imTask.uiType  )  {
										case  CONST_imTaskType_sendFile:
										//  case  CONST_imTaskType_req:
											  idInfo_peer.ui64Id  =  imTask.idInfo_recv.ui64Id;		   
									   		  break;
										case  CONST_imTaskType_recvFile:
										case  CONST_imTaskType_resp:
											  idInfo_peer.ui64Id  =  imTask.idInfo_send.ui64Id;
											  break;
										default:
												traceLogA(  "netMc_procLvEventFunc: Î´´¦ÀíµÄimTaskType, %d",  imTask.uiType  );
												goto  errLabel;
												break;
								}
								*/

								memset(  &addr,  0,  sizeof(  addr  )  );
								lstrcpyn(  addr.misServName,  imTask.misServName,  mycountof(  addr.misServName  )  );
								addr.idInfo.ui64Id  =  idInfo_peer.ui64Id;
								//
								//  if  (  talkToMessenger(  pQyMc,  &addr,  NULL,  FALSE,  TRUE,  &hWnd  )  )  goto  errLabel;
								if  (  tryToTalkToMessenger(  &addr,  TRUE,  &hWnd  )  )  goto  errLabel;

								memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
								wmBuf.uiType  =  CONST_qyWmParam_activateImTask;
								wmBuf.u.activateImTask.iTaskId_activated  =  atol(  buf  );
								SendMessage(  hWnd,  CONST_qyWm_comm,  NULL,  (  LPARAM  )&wmBuf  );
							    }
					     	    break;
				   		  case  ID_qyProp_imTask:  {
							    #if  defined  __isCli__  ||  defined  __APP_qyMc_touchscreen__
							    CDlgPropImTask		dlg;
						 		BOOL				bHisTab		=	FALSE;
								//
								ucbRefreshed  =  FALSE;
								//						 					     
								bHisTab  =  iLvType  ==  CONST_qyQueryType_imTaskHisList;
								//
								if  (  !dlg.bSetDlgInfo(  pObjDb,  bHisTab,  atol(  buf  )  )  )  goto  errLabel;
								dlg.DoModal(  );
								#endif
							    }
							    break;
						  default:
								 break;
				  }

				  iErr  =  0;  goto  errLabel;
				  break;
				
			case  CONST_qyQueryType_instantAssistantMemList:  {
				  QY_WMBUF_COMM  wmBuf;
				  memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
				  wmBuf.uiType  =  CONST_qyWmParam_requestToSpeak;
				  wmBuf.u.requestToSpeak.uiCmd  =  uiCmd;
				  wmBuf.u.requestToSpeak.bManager  =  TRUE;
				  wmBuf.u.requestToSpeak.curnItem  =  curnItem;

				  SendMessage(  pEventInfo->hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
				  }
				  iErr  =  0;  goto  errLabel;
				  break;

			case  CONST_qyQueryType_sharedDynBmpList:  {
				  QY_dynBmp_RCD						dynBmp;
				  //
				  if  (  !g_dbFuncs.pf_bGetQyDynBmpRcdBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  NULL,  NULL,  NULL,  0,  atol(  buf  ),  &dynBmp  )  )  goto  errLabel;
				  //		  
				  switch  (  uiCmd  )  {
								//  isClient
						  case  ID_viewDynBmp:
							    //  traceLogA(  "Cmd: viewDynBmp"  );
							    //  viewDynBmp(  pObjDb,  dynBmp.misServName,  &dynBmp.idInfo,  dynBmp.uiObjType,  dynBmp.usIndex,  dynBmp.cusName[0]  ?  dynBmp.cusName  :  dynBmp.name  );
							    break;
						  case  ID_retrieveAll:  {
							    MIS_CNT			*	pMisCnt		=	NULL;

								if  (  !(  pMisCnt  =  getMisCntByName(  pQyMc,  NULL,  dynBmp.misServName  )  )  )  goto  errLabel;
								sndRetrieveDynBmpsReq_qmc(  pMisCnt,  TRUE  );
								}
							    break;

								//  isMgr
						  case  ID_cfgVisitor:  {
							#if  !defined(  __isCli__  )  &&  !defined(  __APP_qyMc_touchscreen__  )
							    if  (  bFirst  )  {
							    	CDlgSelect	dlg;
									if  (  !dlg.bSetDlgInfo(  pObjDb,  CONST_qyQueryType_sharedDynBmpList,  CONST_objType_messenger,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectMessenger  ),  misServName,  0  )  )  goto  errLabel;
									if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
									//
									pParam->idInfo.ui64Id  =  dlg.m_var.u.selectMessenger.idInfo_selected.ui64Id;
									//
									time(  &pParam->t  );
								}
								if  (  dynBmp.idInfo.ui64Id  ==  pParam->idInfo.ui64Id  )  break;

								QY_dynBmpRule_RCD	rule;
								char				idStr_visitor[CONST_qyMessengerIdStrLen  +  1];
								idInfo2Str(  &dynBmp.idInfo,  idStr,  mycountof(  idStr  )  );
								idInfo2Str(  &pParam->idInfo,  idStr_visitor,  mycountof(  idStr_visitor  )  );
								if  (  !bGetQyDynBmpRuleRcdBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  dynBmp.misServName,  &dynBmp.idInfo,  &pParam->idInfo,  0,  &rule  )  )  {
									
									//  2009/11/05
									int			iCnt	=	0;
									CDBVariant	varVals[1];
									//  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(*) from (select distinct idStr from %s where idStr<>'%s')"  ),  CONST_tabName_qyDynBmpRuleTab,  CString(  idStr  )  );
									_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(*) from (select distinct idStr from %s where idStr<>'%s') as A"  ),  CONST_tabName_qyDynBmpRuleTab,  CString(  idStr  )  );
									if  (  bQyGetRcdBySql(  pObjDb->pDb,  sqlBuf,  mycountof(  varVals  ),  varVals  )  
										&&  varVals[0].m_dwType  ==  DBVT_LONG  )  
									{
										iCnt  =  varVals[0].m_lVal;
									}
									//									
									int	iAvUpperLimits  =  qnmAvUpperLimits(  &pQyMc->licenseCtx  );
									int  maxDynBmpMessengers  =  HIWORD(  iAvUpperLimits  );
									//
									traceLogA(  "cnt %d, maxDynBmpMessengers %d",  iCnt,  maxDynBmpMessengers  );
									//
									if  (  maxDynBmpMessengers  -  1  <  iCnt  )  {
										qyShowHint(  _T(  "Maximum of messengers whose dynamic images can be shared is %d."  ),  maxDynBmpMessengers  );
										goto  errLabel;
									}

									//
									_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into %s(misServName,idStr,idStr_visitor,uiRuleCmd) values(%s,'%s','%s',%d)"  ),  CONST_tabName_qyDynBmpRuleTab,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  ),  CString(  idStr_visitor  ),  CONST_ruleCmd_permit  );
									if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
									ucbRefreshed  =  TRUE;
									}
								else  {
									  //  if  (  rule.uiRuleType
								}
							#endif
								}
							    break;
						  default:
								  break;
				  }

				  }
				  iErr  =  0;  goto  errLabel;				  
				  break;

			case  CONST_qyQueryType_sharedDynBmpRuleList:  {
				  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where id=%d"  ),  CONST_tabName_qyDynBmpRuleTab,  atol(  buf  )  );
				  if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;				  
				  ucbRefreshed  =  TRUE;
				  }
				  iErr  =  0;  goto  errLabel;
				  break;

			case  CONST_qyQueryType_imObjRuleList:  {
				  QY_imObjRule_rcd	rcd;

				  if  (  !g_dbFuncs.pf_bGetImObjRuleRcdBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  NULL,  NULL,  NULL,  atol(  buf  ),  &rcd  )  )  goto  errLabel;

				  if  (  isIsMgr(  )  )  {
					  #ifdef  __DEBUG__
							  traceLog(  _T(  "Warning: not supported"  )  );
					  #endif
					  goto  errLabel;
				  }

				  #if  defined  __isCli__  ||  defined  __APP_qyMc_touchscreen__
				  CDlgImObjRule		dlg;
				  if  (  !dlg.bSetDlgInfo(  rcd.misServName,  &rcd.idInfo_related  )  )  goto  errLabel;

				  if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
				  #endif

				  ucbRefreshed  =  TRUE;
				  }
				  iErr  =  0;  goto  errLabel;
				  break;

			default:
				    traceLogA(  "tmpHandler_procLvEventFunc_is failed. iLvType [%d] err",  iLvType  );
					goto  errLabel;
			  
	}


	if  (  !idInfo2Str(  &idInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
	_sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%I64u"  ),  idInfo.ui64Id  );

	//
	switch  (  uiType  )  {
			case  CONST_objType_me:
			case  CONST_objType_admin:
			case  CONST_objType_messenger:
			case  CONST_objType_phoneMessenger:
				  switch  (  uiCmd  )  {
			              case  ID_imTaskList_unproced:
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "T.misServName=%s and (T.idStr_send='%s' or T.idStr_recv='%s')"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  ),  CString(  idStr  )  );
								g_dbFuncs.pf_bViewImTaskList_unproced(  pObjDb,  _T(  ""  ),  sqlBuf  );
								break;
						  case  ID_imTaskList_cur:
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "T.misServName=%s and (T.idStr_send='%s' or T.idStr_recv='%s')"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  ),  CString(  idStr  )  );
								//  bViewImTaskListFunc(  pObjDb,  _T(  ""  ),  sqlBuf,  FALSE  );
								g_dbFuncs.pf_bViewImTaskList_cur(  pObjDb,  _T(  ""  ),  sqlBuf  );
								break;
						  case  ID_imTaskList_his:
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "T.misServName=%s and (T.idStr_send='%s' or T.idStr_recv='%s')"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  ),  CString(  idStr  )  );
								//  bViewImTaskListFunc(  pObjDb,  _T(  ""  ),  sqlBuf,  TRUE  );
								g_dbFuncs.pf_bViewImTaskList_his(  pObjDb,  _T(  ""  ),  sqlBuf  );
								break;
						  case  ID_qyMsgToday:
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyImMsgTab.misServName=%s and (qyImMsgTab.idStr_send='%s' or qyImMsgTab.idStr_recv='%s')"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  ),  CString(  idStr  )  );
								bViewImMsgToday(  pObjDb,  sqlBuf  );
								break;
						  case  ID_qyMsgList:				   
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyImMsgTab.misServName=%s and (qyImMsgTab.idStr_send='%s' or qyImMsgTab.idStr_recv='%s')"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  ),  CString(  idStr  )  );
								bViewImMsgListFunc_isMgr(  pObjDb,  _T(  ""  ),  sqlBuf  );
								break;
								//
				 		  case  ID_qyEdit:  {
								#if  10  //  ndef  __isCli__
							    CDlgQnmEditPcUsrInfo		dlg;
					   			//
					   			if  (  !dlg.bSetDlgInfo(  pObjDb,  misServName,  uiType,  &idInfo,  FALSE  )  )  goto  errLabel;
					   			//
					   			if  (  dlg.DoModal(  )  ==  IDOK  &&  dlg.m_var.ucbChanged  )  ucbRefreshed  =  TRUE;							    
								#endif
								}
								break;
						  case  ID_qyEditPcUsrInTab1:  {
								#if  10  //  ndef  __isCli__
							    CDlgQnmEditPcUsrInfo		dlg;
					   			//
					   			if  (  !dlg.bSetDlgInfo(  pObjDb,  misServName,  uiType,  &idInfo,  TRUE  )  )  goto  errLabel;
					   			// 
				   	   			if  (  dlg.DoModal(  )  ==  IDOK  &&  dlg.m_var.ucbChanged  )  ucbRefreshed  =  TRUE;
								#endif
							    }
							    break;
				 		  case  ID_qyProperties:  {
							    CDlgPropMessenger		dlg(  CWnd::FromHandle(  pEventInfo->hWnd  )  );
					   			//
					   			if  (  !dlg.bSetDlgInfo(  pObjDb,  misServName,  uiType,  &idInfo  )  )  goto  errLabel;
					   			dlg.DoModal(  );
					   		    }
					   		    break;
						  case  ID_qyModifyMessengerId:  {
								#ifndef  __isCli__
							    CDlgNum						dlg;
								QY_MESSENGER_ID				idInfo_new;
								//
								dlg.bSetDlgInfo(  CONST_qyDlgType_get,  NULL,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_hintOfModifyId  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_newId  ),  getResStr(  0,  &pQyMc->cusRes,  IDOK  ),  getResStr(  0,  &pQyMc->cusRes,  IDCANCEL  ),  19  );    
								dlg.bSetMin(  1  );  
								//  dlg.bSetVal(    );
								if  (  dlg.DoModal(  )  !=  IDOK  )  break;

								idInfo_new.ui64Id  =  dlg.m_var.n;

								if  (  idInfo_new.ui64Id  ==  idInfo.ui64Id  )  break;
								idInfo2Str(  &idInfo_new,  buf,  mycountof(  buf  )  );
								_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(id) from %s where misServName=%s and idStr='%s'"  ),  CONST_tabName_qyImObjAuthTab,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  buf  )  );
								if  (  bSqlObjExists(  pObjDb->pDb,  sqlBuf  )  )  {
									qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_hintOfReinput  )  );  break;
								}
								if  (  modifyImObjId(  pObjDb->pDb,  pObjDb->cfg.iDbType,  pQyMc->iAppType  ==  CONST_qyAppType_client,  misServName,  &idInfo,  &idInfo_new  )  )  {
									qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_modifyFailed  )  );  goto  errLabel;
								}
								ucbRefreshed  =  TRUE;
								#endif
								}
							    break;
				 		  case  ID_qyDel:
							    if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askIfDeleteContact  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
								delImObj(  pObjDb->pDb,  pObjDb->cfg.iDbType,  pQyMc->iAppType  ==  CONST_qyAppType_client,  misServName,  &idInfo  );
								ucbRefreshed  =  TRUE;
					   			break;
						  case  ID_qyDelPcUsr:
							    if  (  bFirst  )  {
									if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askIfDeleteRegInfo  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
									time(  &pParam->t  );
								}
								_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where id=%d"  ),  CONST_tabName_qyImObjRegInfoTab,  atol(  buf  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
								//
								ucbRefreshed  =  TRUE;
								iErr  =  0;  goto  errLabel;
							    break;
						  case  ID_qyDelPcUsrInTab1:  
							    if  (  bFirst  )  {
									if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askIfDeleteTmpRegInfo  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
									time(  &pParam->t  );
								}
								_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where id=%d"  ),  CONST_tabName_qyImObjRegInfoTab1,  atol(  buf  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
								//
								ucbRefreshed  =  TRUE;
								iErr  =  0;  goto  errLabel;
							    break;
						  case  ID_qyImGrpList:
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyImObjTab.idStr in (select idStr_grp from qyImGrpMemTab where qyImGrpMemTab.misServName=%s and qyImGrpMemTab.idStr_mem='%s')"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  )  );
								_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  idInfo.ui64Id  );
                                bViewImGrpList(  pObjDb,  CString(  tBuf  ),  sqlBuf  );
								break;
						  case  ID_qyAddTo:  {
                     
							    if  (  bFirst  )  {
							    	CDlgSelect	dlg;
									if  (  !dlg.bSetDlgInfo(  pObjDb,  0,  CONST_objType_imGrp,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectGroup  ),  misServName,  0  )  )  goto  errLabel;
									if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
									//
									if  (  !idInfo2Str(  &dlg.m_var.u.selectImGrp.idInfo_selected,  buf,  mycountof(  buf  )  )  )  goto  errLabel;
									//
									IM_GRP_INFO		grpInfo;
									memset(  &grpInfo,  0,  sizeof(  grpInfo  )  );
									lstrcpyn(  grpInfo.misServName,  pParam->misServName,  mycountof(  grpInfo.misServName  )  );
									grpInfo.idInfo.ui64Id  =  dlg.m_var.u.selectImGrp.idInfo_selected.ui64Id;		
                                    if  (  recoverImGrp(  pObjDb->pDb,  pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_objType_imGrp,  &grpInfo,  0  )  )  goto  errLabel;
                                    //
									pParam->idInfo_grp.ui64Id  =  grpInfo.idInfo.ui64Id;
									//
									time(  &pParam->t  );
								}

								IM_GRP_MEM	imGrpMem;
								memset(  &imGrpMem,  0,  sizeof(  imGrpMem  )  );
								lstrcpyn(  imGrpMem.misServName,  pParam->misServName,  mycountof(  imGrpMem.misServName  )  );
								imGrpMem.idInfo_grp.ui64Id  =  pParam->idInfo_grp.ui64Id;
								imGrpMem.idInfo_mem.ui64Id  =  idInfo.ui64Id;
								//
								recoverImGrpMem(  pObjDb->pDb,  pObjDb->cfg.iDbType,  &imGrpMem,  0  );
								//
								//  Ìí¼Ó³ÉÔ±ÒªÍ¨Öª·þÎñÆ÷Ë¢ÐÂ
								PARAM_applyForServWork		tmpParam;							
								memset(  &tmpParam,  0,  sizeof(  tmpParam  )  );
								tmpParam.uiType  =  CONST_imCommType_refreshImGrp;
								tmpParam.p0  =  &pParam->idInfo_grp;
								if  (  memcmp(  &tmpParam,  &pParam->param_applyForServWork,  sizeof(  tmpParam  )  )  )  {
									if  (  pParam->param_applyForServWork.uiType  )  {
										if  (  applyForServWork(  pParam->param_applyForServWork.uiType,  pParam->param_applyForServWork.p0,  pParam->param_applyForServWork.p1,  pParam->param_applyForServWork.p2  )  )  goto  errLabel;
									}
									memcpy(  &pParam->param_applyForServWork,  &tmpParam,  sizeof(  pParam->param_applyForServWork  )  );
								}						
								//
								}
								ucbRefreshed  =  TRUE;
							    break;

#if  0
						  case  ID_qyTalk:
							    if  (  uiType  ==  CONST_objType_me  ||  uiType  ==  CONST_objType_admin  )  break;	
								//
								memset(  &addr,  0,  sizeof(  addr  )  );
								addr.uiObjType  =  uiType;
								addr.idInfo.ui64Id  =  idInfo.ui64Id;
								//
							    //  if  (  talkToMessenger(  pQyMc,  &addr,  NULL,  FALSE,  TRUE,  NULL  )  )  goto  errLabel;
								if  (  tryToTalkToMessenger(  &addr,  TRUE,  NULL  )  )  goto  errLabel;
							    break;
						  case  ID_qySendSm:
							    memset(  &addr,  0,  sizeof(  addr  )  );
								lstrcpyn(  addr.misServName,  misServName,  mycountof(  addr.misServName  )  );
								addr.uiObjType  =  uiType;
								addr.idInfo.ui64Id  =  idInfo.ui64Id;
								addr.uiDevType  =  CONST_objType_phone;
								//
								if  (  getSelectedToPath(  pObjDb,  _T(  ""  ),  FALSE,  addr.wPath,  mycountof(  addr.wPath  )  )  )  goto  errLabel;
								addr.bInNoticeMode  =  TRUE;
								//
								//  if  (  talkToMessenger(  pQyMc,  &addr,  NULL,  FALSE,  TRUE,  NULL  )  )  goto  errLabel;
								if  (  tryToTalkToMessenger(  &addr,  TRUE,  NULL  )  )  goto  errLabel;
								//
							    break;
#endif
						  case  ID_qyCfgStandardName:  {
								#ifndef  __isCli__
							    CDlgCfgStandardName		dlg;
								if  (  !dlg.bSetDlgInfo(  0,  pObjDb,  misServName,  &idInfo,  0  )  )  goto  errLabel;
								dlg.DoModal(  );
								#endif
							    }				
				   			    break;
						  case  ID_wwwQmCfg:  {
								#ifndef  __isCli__
							    CDlgWwwQmContact		dlg;
								//
								if  (  uiType  ==  CONST_objType_phoneMessenger  )  {
									qyShowHint(  _T(  "The phone messenger cannot become public messenger"  )  );
									iErr  =  0;  goto  errLabel;
								}

								if  (  !dlg.bSetDlgInfo(  0,  pObjDb,  misServName,  &idInfo,  0  )  )  goto  errLabel;
								if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
								#endif
								//
								ucbRefreshed  =  TRUE;
								}
							    break;
						  case  ID_qyImObjAuthList:
								#ifndef  __isCli__
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyImObjAuthTab.misServName=%s and qyImObjAuthTab.idStr='%s'"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  )  );
							    bViewImObjAuthList_isMgr(  pObjDb,  displayName,  sqlBuf  );  
								#endif
							    break;
						  case  ID_qyPhoneMessengerList:
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyMessengerPhoneInfoTab.misServName=%s and qyMessengerPhoneInfoTab.idStr='%s'"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  )  );
								bViewPhoneMessengerList(  pObjDb,  displayName,  sqlBuf  );
							    break;
						  case  ID_qyAddPhone:  {
								#ifndef  __isCli__
							    CDlgCfgPhoneMessenger		dlg;

								if  (  !dlg.bSetDlgInfo(  0,  pObjDb,  NULL,  FALSE,  &idInfo,  0  )  )  goto  errLabel;
								if  (  dlg.DoModal(  )  ==  IDOK  )  ucbRefreshed  =  TRUE;
								#endif
								iErr  =  0;  goto  errLabel;
								}		    
							    break;
						  case  ID_qyDelPhone:  {
							    if  (  bFirst  )  {
									if  (  AfxMessageBox(  getResStr( 0,  &pQyMc->cusRes,  CONST_resId_askIfDeletePhoneNumber  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
								}
								_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where misServName=%s and idStr='%s'"  ),  CONST_tabName_qyMessengerPhoneInfoTab,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  )  );
								if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
								ucbRefreshed  =  TRUE;
								}
							    break;
						  case  ID_setPasswd:  {
								#ifndef  __isCli__
							    CDlgMessenger	dlg;
								if  (  !dlg.bSetDlgInfo(  CONST_qyDlgType_modify,  pObjDb,  misServName,  &idInfo  )  )  goto  errLabel;
								dlg.DoModal(  );								
								#endif
								}							    
							    break;
						  case  ID_cfgCustomerService:  {
								#ifndef  __isCli__
							    CDlgCfgCustomerService	dlg;

								if  (  uiType  !=  CONST_objType_messenger  )  goto  errLabel;
								if  (  !dlg.bSetDlgInfo(  CONST_qyDlgType_modify,  pObjDb,  misServName,  &idInfo,  0  )  )  goto  errLabel;
								if  (  dlg.DoModal(  )  !=  IDOK  )  break;
								#endif
								//
								ucbRefreshed  =  TRUE;
								}
							    break;
						  case  ID_cfgVisitor:		//  2011/11/18
							    {
							#if  !defined(  __isCli__  )  &&  !defined(  __APP_qyMc_touchscreen__  )
							    if  (  bFirst  )  {
							    	CDlgSelect	dlg;
									if  (  !dlg.bSetDlgInfo(  pObjDb,  CONST_qyQueryType_sharedDynBmpList,  CONST_objType_messenger,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectMessenger  ),  misServName,  0  )  )  goto  errLabel;
									if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
									//
									pParam->idInfo.ui64Id  =  dlg.m_var.u.selectMessenger.idInfo_selected.ui64Id;
									//
									time(  &pParam->t  );
								}
								if  (  idInfo.ui64Id  ==  pParam->idInfo.ui64Id  )  break;

								QY_dynBmpRule_RCD	rule;
								char				idStr_visitor[CONST_qyMessengerIdStrLen  +  1];
								idInfo2Str(  &idInfo,  idStr,  mycountof(  idStr  )  );
								idInfo2Str(  &pParam->idInfo,  idStr_visitor,  mycountof(  idStr_visitor  )  );
								if  (  !bGetQyDynBmpRuleRcdBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  misServName,  &idInfo,  &pParam->idInfo,  0,  &rule  )  )  {
									
									//  2009/11/05
									int			iCnt	=	0;
									CDBVariant	varVals[1];
									//  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(*) from (select distinct idStr from %s where idStr<>'%s')"  ),  CONST_tabName_qyDynBmpRuleTab,  CString(  idStr  )  );
									_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(*) from (select distinct idStr from %s where idStr<>'%s') as A"  ),  CONST_tabName_qyDynBmpRuleTab,  CString(  idStr  )  );
									if  (  bQyGetRcdBySql(  pObjDb->pDb,  sqlBuf,  mycountof(  varVals  ),  varVals  )  
										&&  varVals[0].m_dwType  ==  DBVT_LONG  )  
									{
										iCnt  =  varVals[0].m_lVal;
									}
									//									
									int	iAvUpperLimits  =  qnmAvUpperLimits(  &pQyMc->licenseCtx  );
									int  maxDynBmpMessengers  =  HIWORD(  iAvUpperLimits  );
									//
									traceLogA(  "cnt %d, maxDynBmpMessengers %d",  iCnt,  maxDynBmpMessengers  );
									//
									if  (  maxDynBmpMessengers  -  1  <  iCnt  )  {
										qyShowHint(  _T(  "Maximum of messengers whose dynamic images can be shared is %d."  ),  maxDynBmpMessengers  );
										goto  errLabel;
									}

									//
									_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into %s(misServName,idStr,idStr_visitor,uiRuleCmd) values(%s,'%s','%s',%d)"  ),  CONST_tabName_qyDynBmpRuleTab,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  ),  CString(  idStr_visitor  ),  CONST_ruleCmd_permit  );
									if  (  !bQyExecSql(  pObjDb->pDb,  sqlBuf  )  )  goto  errLabel;
									ucbRefreshed  =  TRUE;
									}
								else  {
									  //  if  (  rule.uiRuleType
								}
							#endif
								}
							    break;
				 		  default:
							     traceLogA(  "messenger: unprocessed cmd: %d",  uiCmd  );
								 goto  errLabel;
								 break;				   
				  }
				  break;
			case  CONST_objType_imGrp:
				  switch  (  uiCmd  )  {
						  case  ID_qyProperties:   {
						   	    CDlgPropImGrp		dlg;

								if  (  !dlg.bSetDlgInfo(  pObjDb,  _T(  ""  ),  &idInfo  )  )  break;
									
								dlg.DoModal(  );

								}
							    break;
						  case  ID_qyDiscuss:												   
							    //  if  (  talkToMessenger(  idInfo.ui64Id,  FALSE,  TRUE,  NULL  )  )  goto  errLabel;
							    if  (  tryToTalkToMessenger(  idInfo.ui64Id,  TRUE,  NULL  )  )  goto  errLabel;
								break;
						  case  ID_qyRule:  {
								#if  defined  __isCli__  ||  defined  __APP_qyMc_touchscreen__
							    CDlgImObjRule	dlg;
								if  (  !dlg.bSetDlgInfo(  _T(  ""  ),  &idInfo  )  )  goto  errLabel;
								if  (  dlg.DoModal(  )  !=  IDOK  )  break;
								//
								ucbRefreshed  =  TRUE;
								#endif
								}							    
							    break;
						  case  ID_qyImGrpMemList:  {
							    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyImGrpMemTab.misServName=%s and qyImGrpMemTab.idStr_grp='%s'"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  )  );
								bViewImGrpMemList_isMgr(  pObjDb,  displayName,  sqlBuf  );
								}
							    break;
						  case  ID_qyModifyMessengerId:  {
								#ifndef  __isCli__
							    CDlgNum						dlg;
								QY_MESSENGER_ID				idInfo_new;
								//
								dlg.bSetDlgInfo(  CONST_qyDlgType_get,  NULL,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_hintOfModifyId  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_newId  ),  getResStr(  0,  &pQyMc->cusRes,  IDOK  ),  getResStr(  0,  &pQyMc->cusRes,  IDCANCEL  ),  0  );    
								dlg.bSetMin(  1  );  
								//  dlg.bSetVal(    );
								if  (  dlg.DoModal(  )  !=  IDOK  )  break;

								idInfo_new.ui64Id  =  dlg.m_var.n;

								if  (  idInfo_new.ui64Id  ==  idInfo.ui64Id  )  break;
								idInfo2Str(  &idInfo_new,  buf,  mycountof(  buf  )  );
								_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(id) from %s where misServName=%s and idStr='%s'"  ),  CONST_tabName_qyImObjAuthTab,  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  buf  )  );
								if  (  bSqlObjExists(  pObjDb->pDb,  sqlBuf  )  )  {
									qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_hintOfReinput  )  );  break;
								}
								if  (  modifyImObjId(  pObjDb->pDb,  pObjDb->cfg.iDbType,  pQyMc->iAppType  ==  CONST_qyAppType_client,  misServName,  &idInfo,  &idInfo_new  )  )  {
									qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_modifyFailed  )  );  goto  errLabel;
								}
								ucbRefreshed  =  TRUE;
								#endif
								}
							    break;
						  case  ID_qyDel:
							    if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_reallyToDelete ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
								delImObj(  pObjDb->pDb,  pObjDb->cfg.iDbType,  pQyMc->iAppType  ==  CONST_qyAppType_client,  misServName,  &idInfo  );
								ucbRefreshed  =  TRUE;
								//
								//  É¾³ý×éÒªÍ¨Öª·þÎñÆ÷Ë¢ÐÂ
								if  (  applyForServWork(  CONST_imCommType_refreshImGrp,  &idInfo,  0,  0  )  )  goto  errLabel;
								//
					   			break;
						  case  ID_qyEdit:  {
								#ifndef  __isCli__
							    CDlgImGrp			dlg;

								if  (  !dlg.bSetDlgInfo(  CONST_qyDlgType_modify,  pObjDb,  misServName,  &idInfo  )  )  goto  errLabel;
								if  (  dlg.DoModal(  )  !=  IDOK  )  break;
								//
								ucbRefreshed  =  TRUE;
								#endif
								}
							    break;
						  default:
								 traceLogA(  "imGrp: unprocessed cmd: %d",  uiCmd  );
								 goto  errLabel;
								 break;
				  }
				  iErr  =  0;  goto  errLabel;							  
				  break;

			default:
				    traceLogA(  "procLvEventFunc_imObj:  Î´´¦ÀíµÄuiType is %d",  uiType  );
					break;
		
	 }

	iErr  =  0;  
		 
errLabel:
		 if  (  !iErr  )  {
			 pEventInfo->ucbRefreshed  =  ucbRefreshed;
		 }
		 return  iErr;
		 
}

//
 int  procLvEventFunc_is(  QY_OBJ_DB  *  pObjDb,  QY_EVENTINFO  *  pEventInfo,  int  iLvType  )
{
	int								iErr			=		-1;
	QY_MC						*	pQyMc			=		QY_GET_GBUF(  );
	//
	PARAM_procLvEventFunc_is		param;
				   
	memset(  &param,  0,  sizeof(  param  )  );
	if  (  initGenericQ(  _T(  "procLv_tmpQ"  ),  NULL,  0,  CONST_uiMaxQNodes_tmpGrpMemQ,  malloc,  free,  &param.tmpGrpMemQ  )  )  goto  errLabel;
	param.bTmpQInited  =  TRUE;

	enumLvSelEventFunc(  pEventInfo,  tmpHandler_procLvEventFunc_is,  pObjDb,  iLvType,  (  void  *  )&param  );

	//  ÕâÀïÔÙ¿´Ò»ÏÂ£¬ÒªÊÇÓÐÐèÒª´¦ÀíµÄ¾ÍÔÙ´¦ÀíÒ»ÏÂ
	if  (  pEventInfo->uiCmd  ==  ID_qySendSm  )  {
#if  0
		if  (  !isQEmpty(  &param.tmpGrpMemQ  )  )  {
			MSGR_ADDR	addr;
			BOOL		bPhoneGuest	=	FALSE;

			switch  (  iLvType  )  {
					case  CONST_qyQueryType_phoneGuestList:
						  bPhoneGuest  =  TRUE;
						  break;
					default:
							break;
			}

			//
			MACRO_prepareForTran(  );
			//
			memset(  &addr,  0,  sizeof(  addr  )  );
			addr.uiObjType  =  CONST_objType_tmpGrp;
			if  (  getSelectedToPath(  pObjDb,  _T(  ""  ),  bPhoneGuest,  addr.wPath,  mycountof(  addr.wPath  )  )  )  goto  errLabel;
			addr.bInNoticeMode  =  TRUE;
			addr.tStartTime_notice  =  tStartTran;
			addr.uiTranNo_notice  =  uiTranNo;
			//
			//  if  (  talkToMessenger(  pQyMc,  &addr,  &param.tmpGrpMemQ,  FALSE,  TRUE,  NULL  )  )  goto  errLabel;      
			if  (  tryToTalkToMessenger(  &addr,  TRUE,  NULL  )  )  goto  errLabel;      
		}
#endif
		}
	else  {
		  if  (  param.param_applyForServWork.uiType  )  {
			  if  (  applyForServWork(  param.param_applyForServWork.uiType,  param.param_applyForServWork.p0,  param.param_applyForServWork.p1,  param.param_applyForServWork.p2  )  )  goto  errLabel;
		  }
	}

	iErr  =  0;
errLabel:
	if  (  param.bTmpQInited  )  exitGenericQ(  &param.tmpGrpMemQ  );
	return  iErr;
}

////////////////



  int  procTvEventFunc_is(  void  *  pQyMcParam,  void  *  pDocParamReserved,  void  *  pSelParam,  void  *  pEventInfoParam,  unsigned  int  uiCmd,  LPCTSTR  colName  )
{
	 int						iErr										=	-1;
	 QY_MC					*	pQyMc										=	(  QY_MC  *  )pQyMcParam;
 	 QY_MC_SEL				*	pSel										=	(  QY_MC_SEL  *  )pSelParam;
	 QY_EVENTINFO			*	pEventInfo									=	(  QY_EVENTINFO  *  )pEventInfoParam;
	 HWND						hParent										=	pEventInfo->hWnd;
	 TCHAR						sqlBuf[CONST_maxSqlBufLen  +  1]			=	_T(  ""  );
	 QY_WMBUF_PROCTV			wmBuf;
	 TCHAR						misServName[CONST_maxMisServNameLen  +  1]	=	_T(  ""  );
	 char						idStr[CONST_qyMessengerIdStrLen  +  1]		=	"";
	 QY_OBJ_DB				*	pObjDb										=	NULL;
	 int						iServiceId									=	pQyMc->iServiceId;
	 QY_MESSENGER_INFO			messengerInfo;
	 MSGR_ADDR					addr;

	 	QM_dbFuncs  *  pDbFuncs  =  QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	 if  (  pSel->type  !=  CONST_qySelType_mcRootTree  )  goto  errLabel;
	 
	 pObjDb  =  getProcedObjDb(  0,  pSel->u.rootTree.iDsnIndex  );	//  2007/01/02
	 if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	 memset(  &messengerInfo,  0, sizeof(  messengerInfo  )  );
	 switch  (  pSel->u.rootTree.objIndex.objType  )  {				
		     case  CONST_objType_me:	//  Me½ÚµãµÄÌØÊâµãÊÇÊµ¼ÊËüÊÇ´¦ÀíÈ«¾ÖµÄ¡£ÆäËû½ÚµãÊ«´¦Àí¸ö±ðµÄmessengerµÈ¡£
				   if  (  !g_dbFuncs.pf_bGetMeInfoBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  pSel->u.rootTree.objIndex.servName,  &messengerInfo  )  )  goto  errLabel;
				   //
				   switch  (  uiCmd  )  {
#if  0
						   case  ID_qySendSm:
							     memset(  &addr,  0,  sizeof(  addr  )  );
								 lstrcpyn(  addr.misServName,  messengerInfo.misServName,  mycountof(  addr.misServName  )  );
								 addr.uiObjType  =  messengerInfo.uiType;
								 addr.idInfo.ui64Id  =  messengerInfo.idInfo.ui64Id;
								 addr.uiDevType  =  CONST_objType_phone;
								 //
								 if  (  getSelectedToPath(  pObjDb,  _T(  ""  ),  FALSE,  addr.wPath,  mycountof(  addr.wPath  )  )  )  goto  errLabel;
								 addr.bInNoticeMode  =  TRUE;
								 //
								 //  if  (  talkToMessenger(  pQyMc,  &addr,  NULL,  FALSE,  TRUE,  NULL  )  )  goto  errLabel;
								 if  (  tryToTalkToMessenger(  &addr,  TRUE,  NULL  )  )  goto  errLabel;
							     break;
#endif
			               case  ID_imTaskList_unproced:
				   			     _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "T.misServName=%s"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  pSel->u.rootTree.objIndex.servName  )  );
				   				 g_dbFuncs.pf_bViewImTaskList_unproced(  pObjDb,  _T(  ""  ),  sqlBuf  );
				   				 break;
						   case  ID_qyRealTimeTaskList:
							     traceLogA(  "kk"  );
								 bViewRealTimeImTaskList(  pObjDb,  _T(  ""  ),  _T(  ""  )  );
							     break;
						   case  ID_imTaskList_cur:
							     _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "T.misServName=%s"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  pSel->u.rootTree.objIndex.servName  )  );
							     //  bViewImTaskListFunc(  pObjDb,  _T(  ""  ),  sqlBuf,  FALSE  );
								 g_dbFuncs.pf_bViewImTaskList_cur(  pObjDb,  _T(  ""  ),  sqlBuf  );
				   				 break;
						   case  ID_imTaskList_his:
							     //  bViewImTaskListFunc(  pObjDb,  _T(  ""  ),  _T(  ""  ),  TRUE  );
							     g_dbFuncs.pf_bViewImTaskList_his(  pObjDb,  _T(  ""  ),  _T(  ""  )  );
				   				 break;
						   case  ID_qyMsgToday:
							     _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyImMsgTab.misServName=%s"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  pSel->u.rootTree.objIndex.servName  )  );
							     bViewImMsgToday(  pObjDb,  sqlBuf  );
				   				 break;
						   case  ID_qyMsgList:
							     _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyImMsgTab.misServName=%s"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  pSel->u.rootTree.objIndex.servName  )  );
								 bViewImMsgListFunc_isMgr(  pObjDb,  _T(  ""  ),  sqlBuf  );
								 break;
						   case  ID_qyEdit:  {
								 #if  10  //  ndef  __isCli__
							     CDlgQnmEditPcUsrInfo		dlg(  CWnd::FromHandlePermanent(  pEventInfo->hWnd  )  );
								 QY_MESSENGER_REGINFO		regInfo;
								 BOOL						ucbInTab1	=	FALSE;

								 if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pObjDb->pDb,  pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  messengerInfo.misServName,  &messengerInfo.idInfo,  0,  NULL,  &regInfo,  NULL,  NULL  )  
									 ||  !bQyTimeValid(  regInfo.tLastModifiedTime  )  )
								 {
									 ucbInTab1  =  TRUE;
								 }
								 if  (  !dlg.bSetDlgInfo(  pObjDb,  messengerInfo.misServName,  messengerInfo.uiType,  &messengerInfo.idInfo,  ucbInTab1  )  )  goto  errLabel;
								 dlg.DoModal(  );
								 #endif
								 }
								 break;		
						   case  ID_qyProperties:  {
					     	     CDlgPropMessenger			dlg;
					   	 		 //
					   	 		 if  (  !dlg.bSetDlgInfo(  pObjDb,  messengerInfo.misServName,  messengerInfo.uiType,  &messengerInfo.idInfo  )  )  goto  errLabel;
					   	 		 dlg.DoModal(  );
							     }				   
				   			     break;
						   default:
							       traceLogA(  "Î´´¦ÀíµÄÃüÁî %d",  uiCmd  );
								   goto  errLabel;
				   }
				   
				   iErr  =  0;  goto  errLabel;
				   break;
			 case  CONST_objType_syr:
			 case  CONST_objType_messenger:
				   messengerInfo.uiType  =  CONST_objType_messenger;
				   lstrcpyn(  messengerInfo.misServName,  pSel->u.rootTree.objIndex.servName,  mycountof(  messengerInfo.misServName  )  );
				   myTChar2Str(  pSel->u.rootTree.objIndex.objIdStr0,  idStr,  mycountof(  idStr  )  );
				   if  (  !idStr2Info(  idStr,  &messengerInfo.idInfo  )  )  goto  errLabel;
				   break;
			 case  CONST_objType_imGrp:
				   messengerInfo.uiType  =  CONST_objType_imGrp;
				   lstrcpyn(  messengerInfo.misServName,  pSel->u.rootTree.objIndex.servName,  mycountof(  messengerInfo.misServName  )  );
				   myTChar2Str(  pSel->u.rootTree.objIndex.objIdStr0,  idStr,  mycountof(  idStr  )  );
				   if  (  !idStr2Info(  idStr,  &messengerInfo.idInfo  )  )  goto  errLabel;
				   break;
			 default:
					break;
	 }

	 if  (  !idInfo2Str(  &messengerInfo.idInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;

	 switch  (  uiCmd  )  {
#if  0
			 case  ID_qyTalk:  
			 case  ID_qyDiscuss:	 				//  2007/05/17
				   memset(  &addr,  0,  sizeof(  addr  )  );
				   lstrcpyn(  addr.misServName,  messengerInfo.misServName,  mycountof(  addr.misServName  )  );
				   addr.uiObjType  =  messengerInfo.uiType;
				   addr.idInfo.ui64Id  =  messengerInfo.idInfo.ui64Id;
				   //
				   //  if  (  talkToMessenger(  pQyMc,  &addr,  NULL,  FALSE,  TRUE,  NULL  )  )  goto  errLabel;
				   if  (  tryToTalkToMessenger(  &addr,  TRUE,  NULL  )  )  goto  errLabel;
				   break;
			 case  ID_qySendSm:
				   memset(  &addr,  0,  sizeof(  addr  )  );
				   lstrcpyn(  addr.misServName,  messengerInfo.misServName,  mycountof(  addr.misServName  )  );
				   addr.uiObjType  =  messengerInfo.uiType;
				   addr.idInfo.ui64Id  =  messengerInfo.idInfo.ui64Id;
				   addr.uiDevType  =  CONST_objType_phone;
				   //
				   if  (  getSelectedToPath(  pObjDb,  _T(  ""  ),  FALSE,  addr.wPath,  mycountof(  addr.wPath  )  )  )  goto  errLabel;
				   addr.bInNoticeMode  =  TRUE;
				   //
				   //  if  (  talkToMessenger(  pQyMc,  &addr,  NULL,  FALSE,  TRUE,  NULL  )  )  goto  errLabel;
				   if  (  tryToTalkToMessenger(  &addr,  TRUE,  NULL  )  )  goto  errLabel;
				   break;
#endif
			 case  ID_qyRule:  {    
				   #if  defined  __isCli__  ||  defined  __APP_qyMc_touchscreen__
				   CDlgImObjRule					dlg;
				   if  (  !dlg.bSetDlgInfo(  messengerInfo.misServName,  &messengerInfo.idInfo  )  )  goto  errLabel;
				   dlg.DoModal(  );
				   #endif
				   }
				   break;
			 case  ID_qyProperties:  
				   if  (    messengerInfo.uiType  ==  CONST_objType_imGrp  )  {
					   CDlgPropImGrp				dlg;
					   if  (  !dlg.bSetDlgInfo(  pObjDb,  messengerInfo.misServName,  &messengerInfo.idInfo  )  )  goto  errLabel;
					   dlg.DoModal(  );
					   }
				   else  {
					     CDlgPropMessenger			dlg;
					   	 //
					   	 if  (  !dlg.bSetDlgInfo(  pObjDb,  messengerInfo.misServName,  messengerInfo.uiType,  &messengerInfo.idInfo  )  )  goto  errLabel;
					   	 dlg.DoModal(  );
				   }				   
				   break;
			 case  ID_qyEdit:  {
				   #ifndef  __isCli__
				   CDlgQnmEditPcUsrInfo		dlg;
				   BOOL						ucbInTab1	=	FALSE;	//  MeÔÚÉÏÃæ´¦Àí¡£messenger¶¼Ö»Ð´½øÕýÊ½±í

				   if  (  !dlg.bSetDlgInfo(  pObjDb,  messengerInfo.misServName,  messengerInfo.uiType,  &messengerInfo.idInfo,  ucbInTab1  )  )  goto  errLabel;
				   dlg.DoModal(  );
				   #endif
				   }
				   break;		
			 case  ID_imTaskList_unproced:
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "T.misServName=%s and (T.idStr_send='%s' or T.idStr_recv='%s')"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  pSel->u.rootTree.objIndex.servName  ),  CString(  idStr  ),  CString(  idStr  )  );
				   g_dbFuncs.pf_bViewImTaskList_unproced(  pObjDb,  _T(  ""  ),  sqlBuf  );
				   break;
			 case  ID_imTaskList_cur:
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "T.misServName=%s and (T.idStr_send='%s' or T.idStr_recv='%s')"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  pSel->u.rootTree.objIndex.servName  ),  CString(  idStr  ),  CString(  idStr  )  );
				   //  bViewImTaskListFunc(  pObjDb,  _T(  ""  ),  sqlBuf,  FALSE  );
				   g_dbFuncs.pf_bViewImTaskList_cur(  pObjDb,  _T(  ""  ),  sqlBuf  );
				   break;
			 case  ID_imTaskList_his:
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "T.misServName=%s and (T.idStr_send='%s' or T.idStr_recv='%s')"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  pSel->u.rootTree.objIndex.servName  ),  CString(  idStr  ),  CString(  idStr  )  );
				   //  bViewImTaskListFunc(  pObjDb,  _T(  ""  ),  sqlBuf,  TRUE  );
				   g_dbFuncs.pf_bViewImTaskList_his(  pObjDb,  _T(  ""  ),  sqlBuf  );
				   break;
			 case  ID_qyMsgToday:
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyImMsgTab.misServName=%s and (qyImMsgTab.idStr_send='%s' or qyImMsgTab.idStr_recv='%s')"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  pSel->u.rootTree.objIndex.servName  ),  CString(  idStr  ),  CString(  idStr  )  );
				   bViewImMsgToday(  pObjDb,  sqlBuf  );
				   break;
			 case  ID_qyMsgList:				   
				   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "qyImMsgTab.misServName=%s and (qyImMsgTab.idStr_send='%s' or qyImMsgTab.idStr_recv='%s')"  ),  getDbValStr(  pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  pSel->u.rootTree.objIndex.servName  ),  CString(  idStr  ),  CString(  idStr  )  );
				   bViewImMsgListFunc_isMgr(  pObjDb,  _T(  ""  ),  sqlBuf  );
				   break;
			 case  ID_qyDel:
				   if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_reallyToDelete  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
				   if  (  delImObj(  pObjDb->pDb,  pObjDb->cfg.iDbType,  pQyMc->iAppType  ==  CONST_qyAppType_client,  messengerInfo.misServName,  &messengerInfo.idInfo  )  )  goto  errLabel;
				   //
				   //  Ë¢ÐÂÏÔÊ¾								 
				   memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
				   wmBuf.uiType  =  CONST_qyWmParam_delItem;
				   wmBuf.hItem  =  pSel->u.rootTree.hItem;
				   SendMessage(  pEventInfo->hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
				   break;
			 default:
					//  traceLogA(  "netMc_procTvEventFunc: Î´ÊµÏÖµÄÃüÁî"  );
					break;
	 }
	 

	 iErr  =  0;
errLabel:

	 return  iErr;
}

  //  2013/02/20
 BOOL  bViewImGrpMemList_isMgr(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL					bRet	=	FALSE;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpImGrpMemListQueryStruct_isMgr  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_imGrpMemList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  NULL,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from ((qyImGrpMemTab left join qyImObjAuthTab on (qyImGrpMemTab.misServName=qyImObjAuthTab.misServname and qyImGrpMemTab.idStr_mem=qyImObjAuthTab.idStr)) left join qyImGrpInfoTab on (qyImGrpMemTab.misServName=qyImGrpInfoTab.misServName and qyImGrpMemTab.idStr_grp=qyImGrpInfoTab.idStr)) left join qyImObjRegInfoTab  on (qyImGrpMemTab.misServName=qyImObjRegInfoTab.misServName and qyImGrpMemTab.idStr_mem=qyImObjRegInfoTab.idStr)"  )  );
	if  (  wherePart  &&  wherePart[0]  ) _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s"  ),  CString(  wherePart  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "qyImGrpMemTab.idStr_grp,qyImGrpMemTab.idStr_mem"  )  );
	
	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	tmpSel.u.query.pfProcEvent  =  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId  =  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos  =  CONST_resId_popup_viewImGrpMemList_isMgr;							//  2003/12/17修改
	tmpSel.u.query.ucbMultiSel  =  TRUE;
	tmpSel.u.query.nSubMenuPos_multiSel  =  CONST_resId_popup_viewImGrpMemList_multiSel_isMgr;		//  2003/12/17修改

	_sntprintf(  tmpSel.u.query.docName,  mycountof(  tmpSel.u.query.docName  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  " %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyImGrpMemList  )  );
	
	bRet  =  pApp->bNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}

 BOOL  bViewSharedDynBmpList_isMgr(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause  )
{
	BOOL					bRet	=	FALSE;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpSharedDynBmpListQueryStruct_isMgr  );

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_sharedDynBmpList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
													//				0					1					2		  3			 4					5			6			7				8
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from qyDynBmpTab left join qyImObjRegInfoTab on (qyDynBmpTab.misServName=qyImObjRegInfoTab.misServName and qyDynBmpTab.idStr=qyImObjRegInfoTab.idStr)"  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  ""  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "qyImObjRegInfoTab.col0,qyDynBmpTab.idStr,qyDynBmpTab.usIndex"  )  );
	
	tmpSel.u.query.data2DisplayProc			=  displayQnmElement;
	tmpSel.u.query.pfProcEvent				=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId				=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos				=  CONST_resId_popup_sharedDynBmpList_isMgr;
	tmpSel.u.query.ucbMultiSel				=  TRUE;															//  2007/08/24
	tmpSel.u.query.nSubMenuPos_multiSel		=  CONST_resId_popup_sharedDynBmpList_multiSel_isMgr;			//  200
	//  tmpSel.u.query.nSubMenuPos_notSel		=	CONST_resId_popup_sharedDynBmpList_notSel_isMgr;		//  2008/01/29	



	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_sharedDynBmpList  )  );
	
	bRet  =  pApp->bNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}

