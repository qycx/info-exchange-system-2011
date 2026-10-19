

#include	"stdafx.h"

#include	<stddef.h>
#include	<stdio.h>

#include	<windows.h>
#include	<windef.h>
#include	<lmcons.h>
#ifndef  __WINCE__
	#include	<lmshare.h>
#endif
#include	<tlhelp32.h>
#include	<iphlpapi.h>

#include	"qyMcMainCommon.h"
#include	"qyVDev.h"
#include	"qmcVideoCapture.h"
#include	"qyMcMainRealTimeMediaProc.h"

#include	"qyDynLib.h"
#include	"qyAvRecordPublic.h"

#include	"qyCusResTemp.h"		//  2013/02/17

//  #include	"qwmDynFunc.h"

#include	"qmcCmdProc.h"

#include	"tmpCeLib.h"
#include	"qySqlFunc.h"

#include	"myresource.h"
#include	"myDb.h"
#include	"qyOpenShellCommon.h"
//#include	"DlgObjs_ts.h"
#include	"dlgobjsproc.h"
#include	"dlgtalkproc.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"


BOOL  bMessengerRegInfoSame(  QY_MESSENGER_REGINFO  *  pRegInfo0,  QY_MESSENGER_REGINFO  *  pRegInfo1  );
int  tmpHandler_bGetMessengerRegInfoBySth_myDb(  void  *  p0,  void  *  p1,  void  *  p2  );



 int  mcProcResp_refreshImGrps_end_myDb(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  RETRIEVE_IMGRPLIST_RESP  *  pResp,  void  *  pCtxParam  )
{
	int									iErr													=	-1;
	MT_SUBTHREADINFO				*	pSubThreadInfo											=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	QY_SERVICEGUI_INFO  *  pSci		=	(  QY_SERVICEGUI_INFO  *  )pSciParam;
	MIS_CNT  *  pMisCnt				=	(  MIS_CNT  *  )pMisCntParam;
	CTX_MC_THREAD  *  pCtx			=	(  CTX_MC_THREAD  *  )pCtxParam;
	QY_MC							*	pQyMc													=	QY_GET_GBUF(  );
	MC_VAR_isCli						*	pProcInfo												=	(  MC_VAR_isCli  *  )pSci->pVar;

		//  do nothing

	iErr  =  0;
errLabel:
	return  iErr;
}

 int  tmpHandler_bNeedRetrieveImGrpMems_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
 {
	 int	iErr	=	-1;
	 //  p0
	 //  p1
	 QMEM_qyImObj  *  pMem  =  (  QMEM_qyImObj  *  )p2;

	 if  (  pMem->messengerInfo.uiType  ==  CONST_objType_imGrp  
		 &&  pMem->messengerInfo.iStatus  !=  CONST_qyStatus_del  )
	 {
		 iErr  =  1;  goto  errLabel;
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
 }

  BOOL	bNeedRetrieveImGrpMems_myDb(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName  )
{
	BOOL	bRet	=	FALSE;
	CMyDb	*	pDb	=	(  CMyDb  *  )pDbParam;

#if  0
#ifndef  __NOTSUPPORT_DB__
		 TCHAR								sqlBuf[1024];

		 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(A.idStr) from qyImObjTab as A where A.misServName=%s and A.uiType in (%d) and A.iStatus<>%d"  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CONST_objType_imGrp,  CONST_qyStatus_del  );
		 OutputDebugString(  sqlBuf  );  OutputDebugString(  _T(  "\n"  )  );
		 if  (  bSqlObjExists(  pDb,  sqlBuf  )  )  bRet  =  TRUE;
#else
		 //  暂时在ce里不考虑处理分组成员信息
#endif
#endif

	BOOL	bImGrpExists  =  FALSE;
	if  (  qTraverse(  pDb->m_var.pQ_qyImObjTab,  tmpHandler_bNeedRetrieveImGrpMems_myDb,  0,  0  )  >  0  )  bRet  =  TRUE;
	
	return  bRet;		 
}





 int  deleteOldImObjRule_mcProcResp_refreshImObjRulesReq_myDb(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  MIS_MSG_INPUT  *  pMsgInput,  void  *  pCtxParam  )
 {
	 return  0;
}

 int  tmpHandle_selectImObjRule_mcProcResp_refreshImObjRulesReq_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
 {
	 int								iErr													=	-1;
	 QY_MESSENGER_ID				*	pIdInfo		=  (  QY_MESSENGER_ID  *  )p0;
	 //  p1
	 REFRESH_imObjRule_reqMem		*	pQMem		=  (  REFRESH_imObjRule_reqMem  *  )p2;
	 //
#if  0
	 MIS_MSG_INPUT					*	pMsgInput	=  (  MIS_MSG_INPUT  *  )p1;
	 IM_CONTENTU					*	pContent	=  NULL;
	 int								i =  0, n = 0;
	 pContent  =  MACRO_msgContent(  pMsgInput->ucFlg,  &pMsgInput->data  );
	 n  =  pContent->refreshImObjRulesReq.usCnt;
#endif

	 if  (  pQMem->idInfo_related.ui64Id  >  pIdInfo->ui64Id  ){

		 pIdInfo->ui64Id  =  pQMem->idInfo_related.ui64Id;
		 iErr  =  1;  goto  errLabel;

	 }

	 iErr  =  0;

errLabel:
	 return  iErr;

 }

 int  selectNextImObjRule_mcProcResp_refreshImObjRulesReq_myDb(  void  *  pSubThreadInfoParam,  void  *  pSciParam,  void  *  pMisCntParam,  MIS_MSG_INPUT  *  pMsgInput,  void  *  pCtxParam,  QY_MESSENGER_ID	  *  pIdInfo_related  )
{
	 int								iErr													=	-1;
	 MT_SUBTHREADINFO				*	pSubThreadInfo											=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	 QY_SERVICEGUI_INFO  *  pSci																=	(  QY_SERVICEGUI_INFO  *  )pSciParam;
	 MIS_CNT  *  pMisCnt																		=	(  MIS_CNT  *  )pMisCntParam;
	 CTX_MC_scheduler  *  pCtx																	=	(  CTX_MC_scheduler  *  )pCtxParam;

	 
	 CMyDb							*	pMyDb													=   (  CMyDb  *  )pSubThreadInfo->pDb;

	 if (  qTraverse(  pMyDb->m_var.pQ_qyImObjRuleTab,  tmpHandle_selectImObjRule_mcProcResp_refreshImObjRulesReq_myDb,  pIdInfo_related,  pMsgInput  )  <=  0  )  goto  errLabel;

#if 0
	 TCHAR								sqlBuf[CONST_maxSqlBufLen  +  1]						=	_T(  ""  );
	 char								timeBuf[128]											=	"";
	 char								idStr[CONST_qyMessengerIdStrLen  +  1];

	 TCHAR								tBuf[255  +  1]											=	_T(  ""  );
	 //
	 int								len;
	 //
	 int								tmpiRet;
	 //  
	 CDBVariant							varVals[1];
	 QY_MESSENGER_ID					idInfo_tmp;


			  idInfo2Str(  &idInfo_related,  idStr,  mycountof(  idStr  )  );			
			  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select idStr_related from %s where idStr_related>'%s' order by idStr_related"  ),  CONST_tabName_qyImObjRuleTab,  CString(  idStr  )  );
			  if  (  !bQyGetRcdBySql(  pSubThreadInfo->pDb,  sqlBuf,  mycountof(  varVals  ),  varVals  )  )  goto  errLabel;
			  MACRO_sqlStr(  varVals[0],  tBuf,  mycountof(  tBuf  )  );  myTChar2Utf8(  tBuf,  idStr,  mycountof(  idStr  )  );  idStr2Info(  idStr,  &idInfo_tmp  );
			  if  (  idInfo_tmp.ui64Id  ==  idInfo_related.ui64Id  )  {
				  //  err
				  goto  errLabel;
			  }
			  idInfo_related.ui64Id  =  idInfo_tmp.ui64Id;
#endif

	 iErr  =  0;

errLabel:
	 return  iErr;
}

 int  tmpHandler_fillImObjs_msgr_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;
	QY_MC	*	pQyMc  =  QY_GET_GBUF(  );

	//  p0;
	COMMON_PARAM		*	pCommonParam1	=		(  COMMON_PARAM  *  )p1;
	//
	HWND					hDlg			=		(  HWND  )pCommonParam1->p0;
	DLG_objs_var		&	m_var			=		*(  DLG_objs_var  *  )pCommonParam1->p1;
	CMyDb				*   pMyDb			=		(  CMyDb  *  )pCommonParam1->p2;
	//
	QMEM_qyImObj		*   pQMem			=		(  QMEM_qyImObj  *  )p2;

	QY_MESSENGER_REGINFO		regInfo;
	MY_REG_DESC					desc;
	TCHAR						tBuf[256];
	QY_DMITEM				*	pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );

	memset(  &regInfo,  0,  sizeof(  regInfo  )  );

	QM_dbFuncs  *  pDbFuncs  =  QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	if  (  pQMem->messengerInfo.iStatus  ==  CONST_qyStatus_ok
		&&  pQMem->messengerInfo.uiType  !=  CONST_objType_imGrp  )
	{
	
#if  0
		if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  pMyDb,  CONST_dbType_myDb,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  pQMem->messengerInfo.misServName,  &pQMem->messengerInfo.idInfo,  0,  &pQMem->messengerInfo,  &regInfo,  NULL,  NULL  )  )  {
			memset(  &regInfo,  0,  sizeof(  regInfo  )  );
		}
#endif
		if  (  !g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pMyDb,  CONST_dbType_myDb,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  pQMem->messengerInfo.misServName, &pQMem->messengerInfo.idInfo,  0,  &regInfo  )  )  {
			memset(  &regInfo,  0,  sizeof(  regInfo  ) );
		}
		HWND	hCtl	=	GetDlgItem(  hDlg,  m_var.guiData.iIDC_LIST0  );
		int		tmpiRet;
		TCHAR	talkerDesc[128]  =  _T(  ""  );
		regInfo2Desc(  0,  &regInfo,  &desc,  talkerDesc,  mycountof(  talkerDesc  ),  NULL,  0  ); 

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u %s"  ),  pQMem->messengerInfo.idInfo.ui64Id,  talkerDesc  );
		tmpiRet  =  SendMessage(  hCtl,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "\t%d,  %s, idInfo is %I64u, talkerDesc %s"  ),  m_var.usItemCount,  qyGetDesByType1(  pTable,  pQMem->messengerInfo.uiType  ),  regInfo.addr.idInfo.ui64Id,  talkerDesc  );
		OutputDebugString(  tBuf  );
		OutputDebugString(  _T(  "\n"  )  );

	}


	iRet  =  0;
errLabel:
	return  iRet;

}

 void  fillImObjs_msgr_myDb(  HWND  hDlg,  void  *  pVar,  void  *  pDb  )
{

	CMyDb  *  pMyDb  =  (  CMyDb  *  )pDb;

	COMMON_PARAM				commonParam1;

	MACRO_makeCommonParam3(  hDlg,  pVar,  pDb,  commonParam1  );	

	qTraverse(  pMyDb->m_var.pQ_qyImObjTab,  tmpHandler_fillImObjs_msgr_myDb,  NULL,  &commonParam1  );

#if 0
	TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1];
	CDBVariant		varVals[10];

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select A.idStr,A.uiType,B.col11,B.col12,B.col2,B.col3,B.col4 from (qyImObjTab as A  left join qyImObjRegInfoTab as B on (A.misServName=B.misServName and A.idStr=B.idStr)) "   )  );
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s where A.uiType not in(%d)"  ),  sqlBuf,  CONST_objType_imGrp  );
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s order by A.idStr"  ),  sqlBuf  );

	enumSqlQuery(  pDb,  sqlBuf,  (  PF_commonHandler  )tmpHandler_fillImObjs_messenger,  hDlg,  pVar,  varVals,  mycountof(  varVals  ),  NULL  );	
#endif

errLabel:

	return;

}

 int  tmpHandler_fillImObjs_grp_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;

	QY_MC	*	pQyMc  =  QY_GET_GBUF(  );

	COMMON_PARAM		*	pCommonParam1	=		(  COMMON_PARAM  *  )p1;
	//
	HWND					hDlg			=		(  HWND  )pCommonParam1->p0;
	DLG_objs_var		&	m_var			=		*(  DLG_objs_var  *  )pCommonParam1->p1;
	CMyDb				*   pMyDb			=		(  CMyDb  *  )pCommonParam1->p2;
	//
	QMEM_qyImObj		*   pQMem			=		(  QMEM_qyImObj  *  )p2;

	//  MY_REG_DESC					desc;
	TCHAR						tBuf[256];
	//  IM_GRP_INFO					grpInfo;

	
	QM_dbFuncs  *  pDbFuncs  =  QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;



	if  (  pQMem->messengerInfo.uiType  ==  CONST_objType_imGrp  )
	{
		IM_GRP_INFO	imGrpInfo;

		if  (  !g_dbFuncs.pf_bGetImGrpInfoBySth(  pMyDb,  CONST_dbType_myDb,  pQMem->messengerInfo.misServName,  &pQMem->messengerInfo.idInfo,  &imGrpInfo  )  )  {
			memset(  &imGrpInfo,  0,  sizeof(  imGrpInfo  )  );
		}
		
		HWND	hCtl	=	GetDlgItem(  hDlg,  m_var.guiData.iIDC_LIST0  );
		//  TCHAR	tBuf[256];
		int		tmpiRet;

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u %s"  ),  pQMem->messengerInfo.idInfo.ui64Id,  imGrpInfo.name  );
		tmpiRet  =  SendMessage(  hCtl,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    

		//  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "\t%d,  %s, idInfo is %I64u, talkerDesc %s"  ),  m_var.usItemCount,  qyGetDesByType1(  pTable,  uiType  ),  grpInfo.idInfo.ui64Id,  grpInfo.name  );
		OutputDebugString(  tBuf  );
		OutputDebugString(  _T(  "\n"  )  );
	}

	iRet  =  0;

errLabel:
	return  iRet;
}

  void  fillImObjs_grp_myDb(  HWND  hDlg,  void  *  pVar,  void  *  pDb  )
{
	CMyDb  *  pMyDb  =  (  CMyDb  *  )pDb;

	COMMON_PARAM				commonParam1;

	MACRO_makeCommonParam3(  hDlg,  pVar,  pDb,  commonParam1  );	

	qTraverse(  pMyDb->m_var.pQ_qyImObjTab,  tmpHandler_fillImObjs_grp_myDb,  NULL,  &commonParam1  );

#if  0
	TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1];
	CDBVariant		varVals[10];

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyImObjTab.idStr,qyImObjTab.uiType,qyImGrpInfoTab.name from (qyImObjTab left join qyImGrpInfoTab on(qyImObjTab.misServName=qyImGrpInfoTab.misServName and qyImObjTab.idStr=qyImGrpInfoTab.idStr ) )"  )  );
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s where qyImObjTab.uiType in(%d)"  ),  sqlBuf,  CONST_objType_imGrp  );
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s order by qyImObjTab.idStr"  ),  sqlBuf  );

	enumSqlQuery(  pDb,  sqlBuf,  (  PF_commonHandler  )tmpHandler_fillImObjs_imGrp,  hDlg,  pVar,  varVals,  mycountof(  varVals  ),  NULL  );	
#endif

errLabel:
	return;
}

int  tmpHandle_selectImTask_dlgTalk_loadTasks_myDb(  void  *  p0,  void  *  P1,  void  *  p2  )
{
	 int				iRet  =  -1;
	 QY_MC			 *	pQyMc									=   QY_GET_GBUF(  );
 	 CQyMalloc			mallocObj;

	 COMMON_PARAM	 *	pCommonParam							=	(  COMMON_PARAM	 *  )p0;
	 //
	 HWND				hDlgTalk								=   (  HWND  )pCommonParam->p0;
	 PARAM_PROC_ROW  *  pParam									=   (  PARAM_PROC_ROW  *  )pCommonParam->p1;
	 //  p1
	 IM_TASK_RCD	 *  pQMem									=   (  IM_TASK_RCD  *  )p2;

	 DLG_TALK_var  &  m_var  =  *(  DLG_TALK_var	*	)getDlgTalkVar(  hDlgTalk  );

	 if  (  (  m_var.addr.uiObjType  ==  CONST_objType_imGrp  &&  (  pQMem->idInfo_send.ui64Id  ==  m_var.addr.idInfo.ui64Id  ||  pQMem->idInfo_recv.ui64Id  ==  m_var.addr.idInfo.ui64Id  )  )
	     || (  m_var.addr.uiObjType  !=  CONST_objType_imGrp  &&  (  
		      (  pQMem->idInfo_send.ui64Id  ==  m_var.addr.idInfo.ui64Id  &&  pQMem->idInfo_recv.ui64Id  ==  m_var.pMisCnt->idInfo.ui64Id  )  ||  
			  (  pQMem->idInfo_send.ui64Id  ==  m_var.pMisCnt->idInfo.ui64Id  &&  pQMem->idInfo_send.ui64Id  ==  m_var.addr.idInfo.ui64Id  )  )  )  )
	 {
		 MIS_MSG_TASK	*	pMsg;
		 if  (  !(  pMsg  =  (  MIS_MSG_TASK  *  )mallocObj.malloc(  sizeof(  MIS_MSG_TASK  )  )  )  )  goto  errLabel;

		 if  (  !taskRcd2Msg(  m_var.pMisCnt,  pQMem,  pMsg  )  )  {
			 traceLogA(  "taskRcd2Msg failed, skipped"  );
			 iRet  =  0;  goto  errLabel;
		 }

	 	if  (  !bTaskAlive(  pQMem->iStatus  )  )  {
			iRet  =  0;  goto  errLabel;
		}

		switch  (  pQMem->uiContentType  )  {
				case  CONST_imCommType_transferAvInfo:  
				case  CONST_imCommType_transferGpsInfo:
					{

					  #ifdef  __DEBUG__
							  traceLogA(  "tmpHandler_displayTasks: skiped, rcd.uiContentType is %d,rcd.uiType %d",  pQMem->uiContentType,  pQMem->uiType  );
					  #endif

					  iRet  =  0;  goto  errLabel;
					  }
					  break;
				default:
						break;
		}
		
		if  (  dlgTalk_qPostMsg(  hDlgTalk,  pMsg,  offsetof(  MIS_MSG_TASK,  data  )  +  pMsg->lenInBytes  )  )  {
			traceLogA(  "tmpHandler_displayTasks failed: qPostMsg failed."  );
			goto  errLabel;
		}

		//
		if  (  pParam->nItem  >=  m_var.usMaxDisplayedTasks  )  {
			iRet  =  1;  goto  errLabel;
		}
	 }
	 
	 iRet =  0;
errLabel:
	 return  iRet;
}

 int  selectImTask_dlgTalk_loadTasks_myDb(  HWND  hDlgTalk,  void  *  pTmpParam,  void  *  pDbParam  )
{
	 int				iRet  =  -1;
	 QY_MC			 *	pQyMc									=   QY_GET_GBUF(  );
	 PARAM_PROC_ROW  *  pParam									=   (  PARAM_PROC_ROW  *  )pTmpParam;
	 char				idStr[CONST_qyMessengerIdStrLen + 1]	=  "";
	 char				idStr_me[CONST_qyMessengerIdStrLen + 1]	=  "";
	 CMyDb			 *	pDb										=	(  CMyDb  *  )pDbParam;
	 COMMON_PARAM		commonParam0;

	 MACRO_makeCommonParam3(  hDlgTalk,  pTmpParam,  NULL,  commonParam0  );

	 qTraverse(  pDb->m_var.pQ_qyImTaskTab,  tmpHandle_selectImTask_dlgTalk_loadTasks_myDb,  &commonParam0,  NULL  );


#if  0
	 TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]		=  _T(  ""  );
	 int				tmpiRet									=  -1;
	 CDBVariant			varVals[15];


	 idInfo2Str(  &m_var.addr.idInfo,  idStr,  mycountof(  idStr  )  );
	 idInfo2Str(  &m_var.pMisCnt->idInfo,  idStr_me, mycountof(  idStr_me  )  );

	//
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select id,uiType,uiMode,subTypeStr,subject,content0,tEndTime,idStr_send,tSendTime,uiTranNo,uiSerialNo,uiContentType,idStr_recv,tRecvTime,iStatus from %s where iStatus<>%d "  ),  CONST_tabName_qyImTaskTab,  CONST_imTaskStatus_null  );	
	if  (  m_var.addr.uiObjType  ==  CONST_objType_imGrp  )  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s and (idStr_send='%s' or idStr_recv='%s')"  ), sqlBuf,  CString(  idStr  ),  CString(  idStr  )  );	    
	else  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s and ((idStr_send='%s' and idStr_recv='%s') or (idStr_send='%s' and idStr_recv='%s'))"  ), sqlBuf,  CString(  idStr  ),  CString(  idStr_me  ),  CString(  idStr_me  ),  CString(  idStr  )  );	    	
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s and uiType not in(%d,%d,%d)"  ),  sqlBuf,  CONST_imTaskType_shareDynBmp,  CONST_imTaskType_viewDynBmp,  CONST_imTaskType_viewGps  );
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s order by tRecvTime "  ),  sqlBuf  );
	tmpiRet  =  enumSqlQuery(  db.m_pDbMem->pDb,  sqlBuf,  tmpHandler_loadTasks,  hDlgTalk,  &pParam,  varVals,  mycountof(  varVals  ),  NULL  );
#endif
	 iRet =  0;
errLabel:
	 return  iRet;
}

 int  tmpHandle_selectImTask_storeTaskInDb_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;

	//  p0
	IM_TASK_RCD			*  pRcd  =  (  IM_TASK_RCD  *  )p1;
	IM_TASK_RCD			*  pQMem =  (  IM_TASK_RCD  *  )p2;

	if  (  pQMem->idInfo_send.ui64Id  ==  pRcd->idInfo_send.ui64Id
		&&  pQMem->idInfo_recv.ui64Id  ==  pRcd->idInfo_recv.ui64Id
		&&  pQMem->tSendTime  ==  pRcd->tSendTime
		&&  pQMem->uiTranNo  ==  pRcd->uiTranNo  )
	{
		pRcd->id  =  pQMem->id;
		pRcd->iStatus  =  pQMem->iStatus;

		iRet  =  1;		goto  errLabel;		
	}

	iRet  =  0;
errLabel:
	return  iRet;
}

 BOOL  bSelectImTask_storeTaskInDb_myDb(  void  *  pDb,  int  iDbType,  void  *  pMisCntParam,  IM_TASK_RCD  *  pRcd,  BOOL  bInHis  )
{
	BOOL					bRet											=	FALSE;
	CMyDb				*	pMyDb											=  (  CMyDb  *  )pDb;

	if  (  bInHis  )  goto  errLabel;

	if  (  qTraverse(  pMyDb->m_var.pQ_qyImTaskTab,  tmpHandle_selectImTask_storeTaskInDb_myDb,  NULL,  pRcd  )  <=  0  )  goto  errLabel;

#if  0
	QY_MC				*	pQyMc											=	QY_GET_GBUF(  );
	MIS_CNT  *  pMisCnt =	(  MIS_CNT  *  )pMisCntParam;
	//
	TCHAR					sqlBuf[CONST_maxSqlBufLen  +  1];
	char					idStr_send[CONST_qyMessengerIdStrLen  +  1]		=	"";
	char					idStr_recv[CONST_qyMessengerIdStrLen  +  1]		=	"";
	char					sendTime[CONST_qyTimeLen  +  1]					=	"";
#if  0
	char					recvTime[CONST_qyTimeLen  + 1]					=	"";
	char					tStartTime_serv[CONST_qyTimeLen  +  1]			=	"";
	char					endTime[CONST_qyTimeLen  +  1]					=	"";
	char					firstTime[CONST_qyTimeLen  +  1]				=	"";
	char					lastTime[CONST_qyTimeLen  +  1]					=	"";
	char					lastModifiedTime[CONST_qyTimeLen  +  1]			=	"";
	char					lastModifiedTime_req[CONST_qyTimeLen  +  1]		=	"";
	CQySyncObj				syncObj;
#endif
	CDBVariant				varVals[5];
	TCHAR				*	pTabName										=	bInHis  ?  CONST_tabName_qyImTaskHisTab  :  CONST_tabName_qyImTaskTab;
	

	if  (  !idInfo2Str(  &pRcd->idInfo_send,  idStr_send,  mycountof(  idStr_send  )  )  )  goto  errLabel;
	if  (  !idInfo2Str(  &pRcd->idInfo_recv,  idStr_recv,  mycountof(  idStr_recv  )  )  )  goto  errLabel;
	if  (  pRcd->tSendTime  )  getTimeStr(  pRcd->tSendTime,  sendTime,  mycountof(  sendTime  )  );
#if  0
	if  (  pRcd->tRecvTime  )  getTimeStr(  pRcd->tRecvTime,  recvTime,  mycountof(  recvTime  )  );
	if  (  pRcd->tEndTime  )  getTimeStr(  pRcd->tEndTime,  endTime,  mycountof(  endTime  )  );
	if  (  pRcd->tLastModifiedTime  )  getTimeStr(  pRcd->tLastModifiedTime,  lastModifiedTime,  mycountof(  lastModifiedTime  )  );
#endif


	//  +misServName;+idStr_send;+tSendTime;+uiTranNo;+idStr_recv
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select id,iStatus from %s where misServName=%s and idStr_send='%s' and tSendTime='%s' and uiTranNo=%d and uiSerialNo=%d and idStr_recv='%s'"  ),  
													pTabName,
													getDbValStr(  iDbType,  CONST_iDataType_misServName,  pRcd->misServName  ),  
													CString(  idStr_send  ),
													CString(  sendTime  ),
													pRcd->uiTranNo,
													pRcd->uiSerialNo,
													CString(  idStr_recv  )  );
	if  (  bQyGetRcdBySql(  pDb,  sqlBuf,  mycountof(  varVals  ),  varVals  )  )  {
		traceLogA(  "storeTaskInDb: "  );
		MACRO_sqlLong(  varVals[0],  pRcd->id  );		//  
		MACRO_sqlLong(  varVals[1],  pRcd->iStatus  );
		iErr  =  1;  goto  errLabel;
	}

#endif
	bRet  =  TRUE;
errLabel:

	return  bRet;
}

 int  insertImTask_storeTaskInDb_myDb(  void  *  pDb,  int  iDbType,  void  *  pMisCntParam,  IM_TASK_RCD  *  pRcd,  BOOL  bInHis  )
{
	int						iErr											=	-1;
	CMyDb				*	pMyDb											=  (  CMyDb  *  )pDb;

	if  (  bInHis  )  return  0;
	if  (  !pRcd   )  return  -1;

	//  2013/02/05
	pRcd->id  =  getuiNextTranNo(  0,  0,  0  );

	//
	if  (  qPostMsg(  pRcd,  sizeof(  pRcd[0]  ),  pMyDb->m_var.pQ_qyImTaskTab  )  )  goto  errLabel;


#if  0
	QY_MC				*	pQyMc											=	QY_GET_GBUF(  );
	MIS_CNT  *  pMisCnt =	(  MIS_CNT  *  )pMisCntParam;
	//
	TCHAR					sqlBuf[CONST_maxSqlBufLen  +  1];
	char					idStr_send[CONST_qyMessengerIdStrLen  +  1]		=	"";
	char					idStr_recv[CONST_qyMessengerIdStrLen  +  1]		=	"";
	char					sendTime[CONST_qyTimeLen  +  1]					=	"";
	//
	char					recvTime[CONST_qyTimeLen  + 1]					=	"";
	char					tStartTime_serv[CONST_qyTimeLen  +  1]			=	"";
	char					endTime[CONST_qyTimeLen  +  1]					=	"";
	char					firstTime[CONST_qyTimeLen  +  1]				=	"";
	char					lastTime[CONST_qyTimeLen  +  1]					=	"";
	char					lastModifiedTime[CONST_qyTimeLen  +  1]			=	"";
	char					lastModifiedTime_req[CONST_qyTimeLen  +  1]		=	"";

	CDBVariant				varVals[5];
	TCHAR				*	pTabName										=	bInHis  ?  CONST_tabName_qyImTaskHisTab  :  CONST_tabName_qyImTaskTab;
	
	if  (  !idInfo2Str(  &pRcd->idInfo_send,  idStr_send,  mycountof(  idStr_send  )  )  )  goto  errLabel;
	if  (  !idInfo2Str(  &pRcd->idInfo_recv,  idStr_recv,  mycountof(  idStr_recv  )  )  )  goto  errLabel;
	if  (  pRcd->tSendTime  )  getTimeStr(  pRcd->tSendTime,  sendTime,  mycountof(  sendTime  )  );
	if  (  pRcd->tRecvTime  )  getTimeStr(  pRcd->tRecvTime,  recvTime,  mycountof(  recvTime  )  );
	if  (  pRcd->tEndTime  )  getTimeStr(  pRcd->tEndTime,  endTime,  mycountof(  endTime  )  );
	if  (  pRcd->tLastModifiedTime  )  getTimeStr(  pRcd->tLastModifiedTime,  lastModifiedTime,  mycountof(  lastModifiedTime  )  );

	getTimeStr(  pRcd->tStartTime_serv,  tStartTime_serv,  mycountof(  tStartTime_serv  )  );
	getTimeStr(  pRcd->firstTime,  firstTime,  mycountof(  firstTime  )  );
	getTimeStr(  pRcd->lastTime,  lastTime,  mycountof(  lastTime  )  );


	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into %s(misServName,idStr_send,senderDesc,tSendTime,uiTranNo,uiSeqNo,uiContentType,tStartTime_serv,uiSerialNo,idStr_recv,receiverDesc,iRole,tRecvTime,usRespCode,ibReply,uiType,uiMode,subTypeStr,subject,content0,ibNeedReply,tEndTime,firstTime,lastTime,iStatus,tLastModifiedTime,propStr0)"  )
															_T(  " values(%s,        '%s',        %s,     '%s',     %d,        %d,     %d,          '%s',         %d,       '%s',       %s,        %d,     '%s',   %d,        %d,       %d,   %d,     %s,          %s,     %s,    %d,          '%s',   '%s',     '%s',     %d,     '%s',             '%s')"  ),
													pTabName,
													getDbValStr(  iDbType,  CONST_iDataType_misServName,  pRcd->misServName  ),  
													CString(  idStr_send  ),
													getDbValStr(  iDbType,  CONST_iDataType_desc,  pRcd->senderDesc  ),
													CString(  sendTime  ),
													pRcd->uiTranNo,
													(  int  )pRcd->usSeqNo,
													pRcd->uiContentType,
													CString(  tStartTime_serv  ),
													pRcd->uiSerialNo,
													CString(  idStr_recv  ),
													getDbValStr(  iDbType,  CONST_iDataType_desc,  pRcd->receiverDesc  ),
													pRcd->iRole,
													CString(  recvTime  ),
													pRcd->usRespCode,
													pRcd->ibReply,
													pRcd->uiType,
													pRcd->uiMode,
													getDbValStr(  iDbType,  CONST_iDataType_subTypeStr,  pRcd->subTypeStr  ),
													getDbValStr(  iDbType,  CONST_iDataType_subject,  pRcd->subject  ),
													getDbValStr(  iDbType,  CONST_iDataType_content,  pRcd->content  ),
													pRcd->ibNeedReply,
													CString(  endTime  ),
													CString(  firstTime  ),  
													CString(  lastTime  ),
													pRcd->iStatus,
													CString(  lastModifiedTime  ),
													CString(  pRcd->propStrs[0]  )  );
												
													
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;
#endif
	iErr  =  0;
errLabel:
	return  iErr;
}

 int  tmpHandler_updateTaskStatus_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;

	int    iStatus  =  (  int  )p0;
	int    iTaskId  =  (  int  )p1;
	IM_TASK_RCD  *  pQMem  =  (  IM_TASK_RCD  *  )p2;

	if  (  pQMem->id  ==  iTaskId  ){
		pQMem->iStatus  =  iStatus;
		iRet  =  1;  goto  errLabel;
	}

	iRet  =  0;
errLabel:

	return  iRet;
}

 //  2013/02/05
 int  updateTaskStatus_myDb(  void  *  pDb,  int  iStatus,  int  iTaskId  )
{
	int			iErr	=	-1;
	CMyDb  *  pMyDb  =  (  CMyDb  *  )pDb;

	if  (  qTraverse(  pMyDb->m_var.pQ_qyImTaskTab,  tmpHandler_updateTaskStatus_myDb,  (  void  *  )iStatus,  (  void  *  )iTaskId  )  <  0  )  goto  errLabel;

#if  0
#ifdef  __NOTSUPPORT_DB__
		int			iErr	=	-1;
		QY_MC	*	pQyMc  =  QY_GET_GBUF(  );
		QY_SERVICEGUI_INFO		*	pSci								=	NULL;
		pSci			=	getServiceGuiInfo(  pQyMc,  pQyMc->iServiceId  );
		if  (  !pSci  )  goto  errLabel;
		MC_VAR_isCli  *  pProcInfo		=	(  MC_VAR_isCli  *  )pSci->pVar;
		if  (  !pProcInfo  )  goto  errLabel;

		int				tmpiRet		=	-1;

		tmpiRet  =  qTraverse(  &pProcInfo->memTaskQ,  (  PF_commonHandler  )tmpHandler_updateTaskStatus,  (  void  *  )iStatus,  (  void  *  )iTaskId  );
		if  (  tmpiRet  <  0  )  goto  errLabel;
		iErr  =  0;
errLabel:
		return  iErr;
#else
	TCHAR		sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );

	if  (  !pDb  )  return  -1;

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set iStatus=%d where id=%d"  ),  CONST_tabName_qyImTaskTab,  iStatus,  iTaskId  );
	
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  return  -1;
	return  0;
#endif

#endif

	iErr  =  0;
errLabel:

	return  iErr;
}

 BOOL  bMoveTask2His_myDb(  void  *  pMisCntParam,  void  *  pDb,  int  iDbType  )
{
	return  FALSE;
}

 BOOL  bClearupDeletedImObjs_isClient_myDb(  void  *  pMisCntParam,  void  *  pDb,  int  iDbType  )
{
		return  FALSE;
}

 int  tmpHandle_bGetImTaskRcdBySth_myDb(   void  *  p0,  void  *  p1,  void  *  p2  )
 {
	 int  iRet  =  -1;

	 COMMON_PARAM	  *  pCommonParam  =  (  COMMON_PARAM  *  )p0;
	 //
	 QY_MESSENGER_ID  *  pIdInfo  =  (  QY_MESSENGER_ID  *  )pCommonParam->p0;
	 unsigned int        uiTranNo  =  (  unsigned int  )pCommonParam->p1;
	 int			     id			=  (  int  )pCommonParam->p2;
	 //
	 IM_TASK_RCD	*  pRcd		=	(  IM_TASK_RCD  *  )p1;
	 IM_TASK_RCD	*  pQMem	=	(  IM_TASK_RCD  *  )p2;

	 if  (  pIdInfo->ui64Id  ){
		 if  (  pQMem->idInfo_send.ui64Id  ==  pIdInfo->ui64Id
			 &&  pQMem->uiTranNo  ==  uiTranNo  )
		 {
			 if  (  pRcd  )memcpy(  pRcd,  pQMem,  sizeof(  pRcd[0]  )  );
			 iRet  =  1;  goto  errLabel;
		 }
	     }
	 else  if  (  pQMem->id  ==  id  )
		 {
			 if  (  pRcd  )memcpy(  pRcd,  pQMem,  sizeof(  pRcd[0]  )  );
			 iRet  =  1;  goto  errLabel;
		 }
	 else  goto  errLabel;

	 iRet  =  0;
errLabel:
	 return  iRet;
 }

  //  2013/02/06
 BOOL  bGetImTaskRcdBySth_myDb(  void  *  pDb,  int  iDbType,  BOOL  bHisTab,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  time_t  tSendTime,  unsigned  int  uiTranNo,  int  id,  IM_TASK_RCD  *  pRcd  )
{
	 BOOL			bRet								=	FALSE;
	 CMyDb		*	pMyDb								=	(  CMyDb  *  )pDb;
	 COMMON_PARAM		commonParam0;

	 if  (  bHisTab  )  goto  errLabel;
	 MACRO_makeCommonParam3(  pIdInfo,  (  void  *  )uiTranNo,  (  void  *  )id,  commonParam0  );


	 if  (  qTraverse(  pMyDb->m_var.pQ_qyImTaskTab,  tmpHandle_bGetImTaskRcdBySth_myDb,  &commonParam0,  pRcd  )  <=  0  )  goto  errLabel;

#if  0
	 TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	 TCHAR			whereClause[256]					=	_T(  ""  );
	 unsigned  int	uiRcdCnt							=	0;


	 if  (  misServName  &&  pIdInfo  )  {
		 char	timeBuf[CONST_qyTimeLen  +  1]	=	"";
		 char	idStr[CONST_qyMessengerIdStrLen  +  1]	=	"";
		 //
		 getTimeStr(  tSendTime,  timeBuf,  mycountof(  timeBuf  )  );
		 idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  );
		 _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "misServName=%s and idStr_send='%s' and tSendTime='%s' and uiTranNo=%d"  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  ),  CString(  timeBuf  ),  uiTranNo  );
		}
	 else  {
		   _sntprintf(  whereClause,  mycountof(  whereClause ),  _T(  "id =%d"  ),  id  );
	 }

	 if  (  enumImTasks(  pDb,  iDbType,  bHisTab,  misServName,  whereClause,  NULL,  0,  0,  &uiRcdCnt,  pRcd  )  )  goto  errLabel;
	 if  (  !uiRcdCnt  )  goto  errLabel;
	
#endif
	 bRet   =  TRUE;

errLabel:

	 return  bRet;
}

int  tmpHandler_bSelectImGrpMem_dlgTalk_OnInitDialog_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int					iRet										=  -1;

	COMMON_PARAM	*	pCommonParam								=	(  COMMON_PARAM  *  )p0;
	//
	HWND				hDlgTalk									=	(  HWND  )pCommonParam->p0;
	PARAM_PROC_ROW	*	pParam										=	(  PARAM_PROC_ROW  *  )pCommonParam->p1;
	CMyDb			*	pDb											=	(  CMyDb  *  )pCommonParam->p2;
	//
	IM_GRP_MEM		*	pQMem										=	(  IM_GRP_MEM  *  )p2;

	QY_MESSENGER_REGINFO		regInfo;
	QY_MESSENGER_REGINFO	*	pRegInfo			=	&regInfo;

	DLG_TALK_var	*	pDlgTalkVar									=	(  DLG_TALK_var	*	)getDlgTalkVar(  hDlgTalk  );
	if  (  !pDlgTalkVar  )  return  -1;
	DLG_TALK_var	&	m_var										=	*pDlgTalkVar;

	if  (  pQMem->idInfo_grp.ui64Id  ==  m_var.addr.idInfo.ui64Id  )
	{
		if  (  pRegInfo  )  {
			if  (  qTraverse(  pDb->m_var.pQ_qyImObjRegInfoTab,  tmpHandler_bGetMessengerRegInfoBySth_myDb,  &pQMem->idInfo_mem,  &regInfo  )  <=  0  )  {
				memset(  &regInfo,  0,  sizeof(  regInfo  )  );
			}
		 
			 QY_MC					*	pQyMc				=  QY_GET_GBUF(  );
			 MC_VAR_isCli			*	pProcInfo			=	(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
			 HWND						hListCtrl			=	GetDlgItem(  hDlgTalk,  m_var.idcList_members  );
			 if  (  !hListCtrl  )  goto  errLabel;
#if  0
			 CListCtrl				*	pListCtrl			=	(  CListCtrl  *  )CWnd::FromHandle(  hListCtrl  );
			 if  (  !pListCtrl  )  goto  errLabel;
#endif
			 MY_REG_DESC				desc;
			 TCHAR						talkerDesc[128  +  1];
			 TCHAR						displayName[64  +  1];
			 int						nImage,  nSelectedImage;
		 
			 if  (  regInfo2Desc(  0,  pRegInfo,  &desc,  talkerDesc,  mycountof(  talkerDesc  ),  displayName,  mycountof(  displayName  )  )  )  goto  errLabel;

			 nImage  =  pQyMc->cfg.image.nImage_messenger;  nSelectedImage  =  pQyMc->cfg.image.nImage_selectedMessenger;

		   {	 //  
			 QM_OBJQ_MEM				mem;
			 QMEM_MESSENGER_CLI		*	pQMem	=	NULL;
			 QY_MESSENGER_INFO			messengerInfo;
			 void					*	pDb		=	NULL;
			 int						i;

			 CQnmDb						tmpObjDb;						
			 pDb				=		tmpObjDb.getAvailableDb(  pQyMc->iDsnIndex_mainSys  );

			 //  ÏÈÓÃregInfoÌî³äÒ»ÏÂmessengerInfo, ÒòÎªÏÂÃæµÄpClientÖ»ÄÜÖ¸ÏòmessengerInfo
			 memset(  &messengerInfo,  0,  sizeof(  messengerInfo  )  );
			 //
			 lstrcpyn(  messengerInfo.misServName,  regInfo.addr.misServName,  mycountof(  messengerInfo.misServName  )  );
			 messengerInfo.idInfo.ui64Id  =  regInfo.addr.idInfo.ui64Id;

			 //               
			 if  (  procQmObjQ(  pProcInfo->pSgiParam,  (  QM_OBJQ  *  )m_var.pMisCnt->pObjQ,  pDb,  pQyMc->cfg.db.iDbType,  CONST_objType_messenger,  &messengerInfo,  &mem  )  )  goto  errLabel;
			 if  (  !mem.pQMemObj  )  goto  errLabel;

			 pQMem  =  (  QMEM_MESSENGER_CLI  *  )mem.pQMemObj;

			 //  ÕâÀïÔÝÊ±ÔÚÕâÀï¸üÐÂÏÔÊ¾Ãû³Æ  
			 lstrcpyn(  pQMem->talkerDesc,  talkerDesc,  mycountof(  pQMem->talkerDesc  )  );
			 lstrcpyn(  pQMem->displayName,  displayName,  mycountof(  pQMem->displayName  )  );		//  2007/09/02

			 //
			 getMessengerImages(  pQyMc,  pQMem->usRunningStatus,  &nImage,  &nSelectedImage  );
#if  0
			 i  =  0;  pListCtrl->InsertItem(  pParam->nItem, displayName,  nImage  );
			 i  ++  ;  pListCtrl->SetItemText(  pParam->nItem,  i,  _ltot(  pRegInfo->id,  displayName,  10  )  );
#endif
			 i  =  0;  myListCtrl_InsertItem(  hListCtrl,  pParam->nItem,  displayName,  nImage  );
			 i  ++  ;  myListCtrl_SetItemText(  hListCtrl,  pParam->nItem,  i,  _ltot(  pRegInfo->id,  displayName,  10  )  );
			 i  ++  ;  //  ²»ÐèÒª×´Ì¬Ïî
			 //
#if  0
			 pListCtrl->SetItemData(  pParam->nItem,  pRegInfo->id  );
#endif
			 myListCtrl_SetItemData(  hListCtrl,  pParam->nItem,  pRegInfo->id  );
			 //
			 pParam->nItem  ++  ;

			 //  2007/06/03 
			 QMOBJQ_PARAM_MISCLIENT		qmObjQParam;
			 //
			 memset(  &qmObjQParam,  0,  sizeof(  qmObjQParam  )  );
			 //  uiType
			 qmObjQParam.pSci  =  (  QY_SERVICEGUI_INFO  *  )pProcInfo->pSgiParam;
			 qmObjQParam.pMisCnt  =  m_var.pMisCnt;
			 qmObjQParam.pDb  =  pDb;
			 qmObjQParam.iDbType  =  pQyMc->cfg.db.iDbType;
			 qmObjQParam.iObjType  =  CONST_objType_messenger;
			 qmObjQParam.pClient  =  &messengerInfo;

			 addToDisplayedObjQ(  &m_var.displayCtx,  &qmObjQParam,  hDlgTalk,  pRegInfo->id  );  
				 
			 if  (  postRecentFriend(  qmObjQParam.pSci,  qmObjQParam.pMisCnt,  &qmObjQParam.pClient->idInfo,  0  )  )  traceLogA(  "postRecentFriend failed"  );  
		   }
		 }

	}

	iRet  =  0;
errLabel:
	return  iRet;
}

BOOL  bSelectImGrpMem_dlgTalk_OnInitDialog_myDb(  HWND  hDlgTalkParam,  void  *  pDbParam,  void  *  pParam  )
{
	BOOL				bRet										=   FALSE;
	CMyDb			*	pDb											=	(  CMyDb  *  )pDbParam;
	COMMON_PARAM		commonParam;
	MACRO_makeCommonParam3(  hDlgTalkParam,  pParam,  pDb,  commonParam  );


	qTraverse(  pDb->m_var.pQ_qyImGrpMemTab,  tmpHandler_bSelectImGrpMem_dlgTalk_OnInitDialog_myDb,  &commonParam,  NULL  );
	
#if  0
	TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]			=	_T(  ""  );
	char				idStr_grp[CONST_qyMessengerIdStrLen  +  1]	=	"";
	CDBVariant			varVals[50];

	DLG_TALK_var	&	m_var										=	*getDlgTalkVar(  pDlgTalk->m_hWnd  );
	void			*	pDb											=   (  void  *  )pDbParam;
	int					tmpiRet										=	-1;

	idInfo2Str(  &m_var.addr.idInfo,  idStr_grp,  mycountof(  idStr_grp  )  );
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyImGrpMemTab.id,qyImGrpMemTab.misServName,qyImGrpMemTab.idStr_mem,qyImObjRegInfoTab.regTime,qyImObjRegInfoTab.auditTime,qyImObjRegInfoTab.tLastModifiedTime,qyImObjRegInfoTab.col0,qyImObjRegInfoTab.col1,qyImObjRegInfoTab.col2,qyImObjRegInfoTab.col3,qyImObjRegInfoTab.col4,qyImObjRegInfoTab.col5,qyImObjRegInfoTab.col6,qyImObjRegInfoTab.col7,qyImObjRegInfoTab.col8,qyImObjRegInfoTab.col9,qyImObjRegInfoTab.col10,qyImObjRegInfoTab.col11,qyImObjRegInfoTab.col12,qyImObjRegInfoTab.col13,qyImObjRegInfoTab.col14,qyImObjRegInfoTab.col15,qyImObjRegInfoTab.col16,qyImObjRegInfoTab.col17,qyImObjRegInfoTab.col18,qyImObjRegInfoTab.col19,qyImObjRegInfoTab.col20,qyImObjRegInfoTab.col21,qyImObjRegInfoTab.col22,qyImObjRegInfoTab.col23,qyImObjRegInfoTab.col24,qyImObjRegInfoTab.col25,qyImObjRegInfoTab.col26,qyImObjRegInfoTab.col27,qyImObjRegInfoTab.col28,qyImObjRegInfoTab.col29"  )
											_T(  " from qyImGrpMemTab left join qyImObjRegInfoTab on( qyImGrpMemTab.misServName=qyImObjRegInfoTab.misServName and qyImGrpMemTab.idStr_mem=qyImObjRegInfoTab.idStr) where qyImGrpMemTab.misServName=%s and qyImGrpMemTab.idStr_grp='%s'"  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_misServName,  m_var.addr.misServName  ),  CString(  idStr_grp  )  );
	//  enumSqlQuery(  pDb->m_pDbMem->pDb,  sqlBuf,  tmpHandler_showImGrpMems,  CWnd::FromHandle(  hDlgTalk  ),  pParam,  varVals,  mycountof(  varVals  ),  NULL  );
	tmpiRet  =  enumSqlQuery(  pDb,  sqlBuf,  tmpHandler_showImGrpMems,  pDlgTalk,  pParam,  varVals,  mycountof(  varVals  ),  NULL  );
#endif

	bRet  =  TRUE;
errLabel:
	return  bRet;
}


int  tmpHandler_listObjs_dlgMsgList_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;
	QY_MC		  *  pQyMc				=  QY_GET_GBUF(  );
	COMMON_PARAM  *  pCommonParam		=  (  COMMON_PARAM  *  )p0;
	//
	//  QY_MC_QUERY	  *  pQuery				=  (  QY_MC_QUERY  *  )pCommonParam->p0;
	CMyDb		  *  pDb				=  (  CMyDb  *  )pCommonParam->p0;
	//  CListCtrl	  *  pListCtrl			=  (  CListCtrl  *  )pCommonParam->p1;
	HWND			 hListCtrl			=	(  HWND  )pCommonParam->p1;
	if  (  !hListCtrl  )  goto  errLabel;
	int			  *  nItem				=  (  int  *  )pCommonParam->p2;
	//
	QY_MESSENGER_ID  *  pIdInfo			=  (  QY_MESSENGER_ID  *  )p1;
	IM_MSG_RCD	  *  pQMem				=  (  IM_MSG_RCD  *  )p2;

	if  (  pQMem->idInfo_send.ui64Id  ==  pIdInfo->ui64Id  ||  pQMem->idInfo_recv.ui64Id  ==  pIdInfo->ui64Id  ||  (  pIdInfo  &&  !pIdInfo->ui64Id  ?  1  :  0  )  )
	{
		int		iItem  =  nItem[0];
		int		index			 =  0;
		TCHAR	tBuf[255  +  1]  =  _T(  ""  );
		QY_MESSENGER_REGINFO    regInfo;
		MY_REG_DESC				desc;
		char		  timeBuf[CONST_qyTimeLen  +  1]  =  "";


			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pQMem->id  );
			//  index  =  0;  pListCtrl->InsertItem(  iItem,  tBuf  );
			index  =  0;  myListCtrl_InsertItem(  hListCtrl,  iItem,  tBuf  );


			//  QY_DMITEM		*	pTable;
		    // pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_imTaskTypeTable  );
			//   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  CString(  qyGetDesByType1(  pTable,  pQMem->uiType  )  )  );
			//  index  =  1;  pListCtrl->SetItemText(  iItem,  index,  tBuf  );
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pQMem->uiType  );
			//  index  =  1;  pListCtrl->SetItemText(  iItem,  index,  tBuf  );
			index  =  1;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

			if  (  qTraverse(  pDb->m_var.pQ_qyImObjRegInfoTab,  tmpHandler_bGetMessengerRegInfoBySth_myDb,  &pQMem->idInfo_send,  &regInfo  )  >  0  ){
				regInfo2Desc(  0,  &regInfo,  &desc,  NULL,  0,  NULL,  0  );
				if  (  desc.pSyr[0]  )  _sntprintf(  pQMem->senderDesc,  mycountof(  pQMem->senderDesc  ),  _T(  "%s - %s - %s"  ),  desc.pDw,  desc.pBm,  desc.pSyr  );  
			}
			//  index  =  2;  pListCtrl->SetItemText(  iItem,  index,  pQMem->senderDesc  );
			index  =  2;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  pQMem->senderDesc  );

			if  (  qTraverse(  pDb->m_var.pQ_qyImObjRegInfoTab,  tmpHandler_bGetMessengerRegInfoBySth_myDb,  &pQMem->idInfo_recv,  &regInfo  )  >  0  ){
				regInfo2Desc(  0,  &regInfo,  &desc,  NULL,  0,  NULL,  0  );
				if  (  desc.pSyr[0]  )  _sntprintf(  pQMem->receiverDesc,  mycountof(  pQMem->receiverDesc  ),  _T(  "%s - %s - %s"  ),  desc.pDw,  desc.pBm,  desc.pSyr  );  
			}
			//  index  =  3;  pListCtrl->SetItemText(  iItem,  index,  pQMem->receiverDesc  );
			index  =  3;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  pQMem->receiverDesc  );

			getTimeStr(  pQMem->tSendTime,  timeBuf,  mycountof(  timeBuf  )  );
			//  index  =  4;  pListCtrl->SetItemText(  iItem,  index,  CString(  timeBuf  )  );
			index  =  4;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  CQyString(  timeBuf  )  );

			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  pQMem->content  );
			//  index  =  5;  pListCtrl->SetItemText(  iItem,  index,  tBuf  );
			index  =  5;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );
			index  =  6;  //  pListCtrl->SetItemText(  iItem,  index,  pQMem->content1  );
			index  =  7;  //  pListCtrl->SetItemText(  iItem,  index,  pQMem->content2  );
			index  =  8;  //  pListCtrl->SetItemText(  iItem,  index,  pQMem->content3  );
			index  =  9;  //  pListCtrl->SetItemText(  iItem,  index,  pQMem->content4  );

			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pQMem->idInfo_send.ui64Id  );
			//  index  =  10;  pListCtrl->SetItemText(  iItem,  index,  tBuf  );
			index  =  10;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pQMem->idInfo_recv.ui64Id  );
			//  index  =  11;  pListCtrl->SetItemText(  iItem,  index,  tBuf  );
			index  =  11;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

			getTimeStr(  pQMem->firstTime,  timeBuf,  mycountof(  timeBuf  )  );
			//  index  =  12;  pListCtrl->SetItemText(  iItem,  index,  CString(  timeBuf  )  );
			index  =  12;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  CQyString(  timeBuf  )  );


			iItem ++;
			nItem[0]  =  iItem;
	}



	iRet  =  0;
errLabel:
	return  iRet;

}

int  listObjs_dlgMsgList_myDb(  void  *  pDbParam,  void  *  pQueryParam,  HWND  hListCtrlParam,  QY_MESSENGER_ID  *  pIdInfoParam  )
{

	CMyDb					*	pDb			=	(  CMyDb  *  )pDbParam;
	int							nItem[1]	=	{0};
	COMMON_PARAM				commonParam;

	MACRO_makeCommonParam3(  pDb,  hListCtrlParam,  nItem,  commonParam  );

	qTraverse(  pDb->m_var.pQ_qyImMsgTab,  tmpHandler_listObjs_dlgMsgList_myDb,  &commonParam,  pIdInfoParam  );
#if  0
 
	QY_MC_QUERY				*	pQuery		=	(  QY_MC_QUERY  *  )pQueryParam;
	CListCtrl				*	pListCtrl	=	(  CListCtrl  *  )pListCtrlParam;
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	CRecordset					rs(  ( CDatabase * )pDbParam  );
	int							nFields;
	CDBVariant					varVals[30];
	char					*	tmpPtr		=	NULL;
	int							index;
	int							nItem;
	//  TCHAR						tBuf[256];
	int							i;
	CQyString					sqlStr;
		

	sqlStr  =  CQyString(  pQuery->selectPart  );
	sqlStr  =  sqlStr  +  CQyString(  _T(  " "  )  )  +  CQyString(  pQuery->fromPart  );
	if  (  pQuery->wherePart[0]  )  {
		sqlStr  =  sqlStr  +  CQyString(  _T(  " where "  )  )  +  CQyString(  pQuery->wherePart  );
	}
	if  (  pQuery->sortPart[0]  )  {
		sqlStr  =  sqlStr  +  CQyString(  _T(  " order by "  )  )  +  CQyString(  pQuery->sortPart  );
	}
	
	try  {
		 if  (  !rs.Open(  CRecordset::forwardOnly,  sqlStr  )  )  goto  errLabel;
		 nFields  =  rs.GetODBCFieldCount(  );
		 if  (  nFields  >  sizeof(  varVals  )  /  sizeof(  varVals[0]  )  )  {
			 traceLogA(  "%s: varVal is too small.",  __FILE__  );
			 goto  errLabel;
		 }
		 //  MACRO_qyAssert(  nFields  ==  m_var.nFields,  "CDlgQnmCfgPcGrps×Ö¶ÎÊý²»Æ¥Åä"  );

		 int  cnt  =  rs.GetRecordCount(  );


		 for  (  nItem  =  0;  !rs.IsEOF(  );  rs.MoveNext(  ),  nItem  ++  )  {


			 TCHAR	output[256]	=	_T(  ""  );
			 int	size  =  mycountof(  output  );

			 for  (  index  =  0;  index  <  nFields;  index  ++  )  {

			 	  displayQnmElement_ts(  0,  pQuery,  &rs,  index,  output,  size  );

				  if  (  !index  )  pListCtrl->InsertItem(  nItem,  output  );
				  else  pListCtrl->SetItemText(  nItem,  index,  output  );
			 }

		 }
			  //  if  (  m_var.ucbIdSeletedValid  &&  m_var.idSelected  ==  rcd.id  )  m_var.nItemSelected  =  nItem;
			  
		 
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgCfgStandardNames::listCfgStandardNames failed."  )  );
		   goto  errLabel;
	}

errLabel:

	if  (  rs.IsOpen(  )  )  rs.Close(  );
#endif	
	 return  0;
}


#ifdef  __DEBUG__

 int  tmpHandler_printQ_imObj(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	QY_MESSENGER_REGINFO  regInfo;
	TCHAR	tBuf[128]  =  _T(  ""  );

	CMyDb	*  pDb	=  (  CMyDb  *  )p0;
	int  *  cnt  =  (  int  *  )p1;
	//  p1
	QMEM_qyImObj  *  pQMem  =  (  QMEM_qyImObj  *  )p2;


	int  index  =  *cnt;


	QY_DMITEM  *  pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );
					
	int  iType  =  pQMem->messengerInfo.uiType;

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  CQyString(  qyGetDesByType1(  pTable,  iType  )  )  );

	traceLog(  _T(  "\t%d, id %I64u,  uiType %d,  %s"  ),  index,  pQMem->messengerInfo.idInfo.ui64Id,  pQMem->messengerInfo.uiType,  tBuf  );
	
	index  ++;

	*cnt  =  index;

	iRet  =  0;
errLabel:
	return  iRet;

}

 
 int  printQ_imObj(  void  *  pDbParam,  int  iDbType,  LPCTSTR  hint  )		//
{
	if  (  !pDbParam  )  return  -1;
	if  (  iDbType  !=  CONST_dbType_myDb  )  return  -1;

	if  (  !hint  )  hint  =  _T(  ""  );
	int  cnt  =  0;

	switch(  iDbType  ){
		
		  case  CONST_dbType_myDb:
		  default:
				CMyDb		*  pDb	=	(  CMyDb  *  )pDbParam;	

				traceLog(  _T(  "%s: printQ_imObj %s starts, %d qNodes"  ),  hint,  pDb->m_var.pQ_qyImObjTab->cfg.name,  pDb->m_var.pQ_qyImObjTab->uiQNodes  );

				qTraverse(  pDb->m_var.pQ_qyImObjTab,  (  PF_commonHandler  )tmpHandler_printQ_imObj,  pDbParam,  (  void  *  )&cnt  );
	
				traceLog(  _T(  "printQ_imObj ends"  )  );

			  break;	
	}

	
	return  0;
}

  int  tmpHandler_printQ_imObjRegInfo(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;
	QY_MESSENGER_REGINFO  regInfo;
	TCHAR	tBuf[128]  =  _T(  ""  );

	CMyDb	*  pDb	=  (  CMyDb  *  )p0;
	int  *  cnt  =  (  int  *  )p1;
	QMEM_qyImObjRegInfo  *  pQMem  =  (  QMEM_qyImObjRegInfo  *  )p2;


	int  index  =  *cnt;

	//  if  (  pQMem->messengerInfo.uiType  ==  CONST_objType_me  ||  pQMem->messengerInfo.uiType  ==  CONST_objType_messenger  )  
	{
		QY_MC	*	pQyMc		=  QY_GET_GBUF(  );
		MY_REG_DESC		desc;
		int  i  =  0;
		//
		memset(  &regInfo,  0,  sizeof(  regInfo  )  );
		regInfo.uiType  =  CONST_imCommType_messengerRegInfo;
		//  id
		regInfo.iCustomId  =  qyGetCustomId(  );

		memcpy(  &regInfo.addr,  &pQMem->myRegInfo.addr,  sizeof(  regInfo.addr  )  );
		
		memcpy(  regInfo.uiFieldIds,  pQMem->myRegInfo.uiFieldIds,  sizeof(  regInfo.uiFieldIds  )  );
		memcpy(  regInfo.u.cols,  pQMem->myRegInfo.u.cols,  sizeof(  regInfo.u.cols  )  );
		
		//
		MACRO_setPtrs(  CONST_fieldIdTable_en,  regInfo,  regInfo.fields  );

		if  (  !regInfo2Desc(  0,  &regInfo,  &desc,  NULL,  0,  NULL,  0  )  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s - %s - %s"  ),  desc.pDw,  desc.pBm,  desc.pSyr  );	
		}	
	}

	traceLog(  _T(  "\t%d, id %I64u,  %s"  ),  index,  pQMem->myRegInfo.addr.idInfo.ui64Id,  tBuf  );
	
	index  ++;

	*cnt  =  index;

	iRet  =  0;
errLabel:
	return  iRet;

}


  int  printQ_imObjRegInfo(  void  *  pDbParam,  int  iDbType,  LPCTSTR  hint  )		//
{
	if  (  !pDbParam  )  return  -1;
	if  (  iDbType  !=  CONST_dbType_myDb  )  return  -1;

	if  (  !hint  )  hint  =  _T(  ""  );
	int  cnt  =  0;

	switch(  iDbType  ){
		
		  case  CONST_dbType_myDb:
		  default:
				CMyDb		*  pDb	=	(  CMyDb  *  )pDbParam;	

				traceLog(  _T(  "%s: printQ_imObjRegInfo %s starts, %d qNodes"  ),  hint,  pDb->m_var.pQ_qyImObjRegInfoTab->cfg.name,  pDb->m_var.pQ_qyImObjRegInfoTab->uiQNodes  );

				qTraverse(  pDb->m_var.pQ_qyImObjRegInfoTab,  (  PF_commonHandler  )tmpHandler_printQ_imObjRegInfo,  pDbParam,  (  void  *  )&cnt  );
	
				traceLog(  _T(  "printQ_imObjRegInfo ends"  )  );

			  break;	
	}

	
	return  0;
}

 int  tmpHandler_printQ_imObjRule(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	TCHAR	tBuf[128]  =  _T(  ""  );

	CMyDb	*  pDb	=  (  CMyDb  *  )p0;
	int  *  cnt  =  (  int  *  )p1;
	//  p1
	QMEM_qyImObjRule  *  pQMem  =  (  QMEM_qyImObjRule  *  )p2;


	int  index  =  *cnt;

	QY_DMITEM  *  pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_ruleCmdTable_autoAnswer  );
					
	int  iRuleType  =  pQMem->ruleRcd.uiRuleType;

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  CQyString(  qyGetDesByType1(  pTable,  iRuleType  )  )  );

	traceLog(  _T(  "\t%d, id %I64u,  id %I64u,  uiType %d,  %s"  ),  index,  (   (  pQMem->ruleRcd.idInfo.ui64Id  )  ?  pQMem->ruleRcd.idInfo.ui64Id  :  0  ),  (  pQMem->ruleRcd.idInfo_related.ui64Id  ?  pQMem->ruleRcd.idInfo_related.ui64Id  :  0  ),  pQMem->ruleRcd.uiRuleType,  tBuf  );
	
	index  ++;

	*cnt  =  index;

	iRet  =  0;
errLabel:
	return  iRet;

}

  int  printQ_imObjRule(  void  *  pDbParam,  int  iDbType,  LPCTSTR  hint  )
{
	if  (  !pDbParam  )  return  -1;
	if  (  iDbType  !=  CONST_dbType_myDb  )  return  -1;

	if  (  !hint  )  hint  =  _T(  ""  );
	int  cnt  =  0;

	CMyDb  *  pDb  =  (  CMyDb  *  )pDbParam;
	 
	traceLog(  _T(  "%s: printQ_imObjRuleInfo %s starts, %d qNodes"  ),  hint,  pDb->m_var.pQ_qyImObjRuleTab->cfg.name,  pDb->m_var.pQ_qyImObjRuleTab->uiQNodes  );

	qTraverse(  pDb->m_var.pQ_qyImObjRuleTab,  (  PF_commonHandler  )tmpHandler_printQ_imObjRule,  pDbParam,  (  void  *  )&cnt  );

	traceLog(  _T(  "printQ_imObjRuleInfo ends"  )  );

		return  0;
}

 int  tmpHandler_printQ_imTask(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	TCHAR	tBuf[128]  =  _T(  ""  );

	CMyDb	*  pDb	=  (  CMyDb  *  )p0;
	int  *  cnt  =  (  int  *  )p1;
	//  p1
	IM_TASK_RCD  *  pQMem  =  (  IM_TASK_RCD  *  )p2;

	int  index  =  *cnt;

#if  10
	QY_DMITEM  *  pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_qyStatusTable  );
					
	int  iStatus  =  pQMem->iStatus;

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  CQyString(  qyGetDesByType1(  pTable,  iStatus  )  )  );
#endif
	traceLog(  _T(  "\t%d, id %I64u,  id %I64u,  iStatus %d,  %s"  ),  index,  pQMem->idInfo_send.ui64Id,  pQMem->idInfo_recv.ui64Id,  pQMem->iStatus,  tBuf  );
	
	index  ++;

	*cnt  =  index;

	iRet  =  0;
errLabel:
	return  iRet;

}
  int  printQ_imTask(  void  *  pDbParam,  int  iDbType,  LPCTSTR  hint  )
{
	if  (  !pDbParam  )  return  -1;
	if  (  iDbType  !=  CONST_dbType_myDb  )  return  -1;

	if  (  !hint  )  hint  =  _T(  ""  );
	int  cnt  =  0;

	CMyDb  *  pDb  =  (  CMyDb  *  )pDbParam;
	 
	traceLog(  _T(  "%s: printQ_imTaskInfo %s starts, %d qNodes"  ),  hint,  pDb->m_var.pQ_qyImTaskTab->cfg.name,  pDb->m_var.pQ_qyImTaskTab->uiQNodes  );

	qTraverse(  pDb->m_var.pQ_qyImTaskTab,  (  PF_commonHandler  )tmpHandler_printQ_imTask,  pDbParam,  (  void  *  )&cnt  );

	traceLog(  _T(  "printQ_imTaskInfo ends"  )  );

		return  0;
}

 __declspec(  dllexport  )  int  test_myDb(  LPCTSTR  hint  )
 {
	 QY_MC  *  pQyMc	=	QY_GET_GBUF(  );

				 CQnmDb	db;
				 void  *  pDb;
				 pDb  =  db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  );
				 if  (  pDb  )  {
#if  0
					 printQ_imObj(  pDb,  pQyMc->cfg.db.iDbType,  hint  );
#endif			 //
#if  0
					 printQ_imObjRegInfo(  pDb,  pQyMc->cfg.db.iDbType,  hint  );
#endif			 //
#if  0
					 printQ_imObjRule(  pDb,  pQyMc->cfg.db.iDbType,  hint  );
#endif
#if  0
					 printQ_imTask(  pDb,  pQyMc->cfg.db.iDbType,  hint  );
#endif
				 }

	 return  0;
 }


#endif


  int  tmpHandler_displayImTask_cur(  void  *  p0,  void  *  p1,  void  *  p2  )
 {
	 int  iRet  =  -1;
	 COMMON_PARAM	*	pCommonParam	=  (  COMMON_PARAM  *  )p0;
	 //
	 CMyDb			*	pDb				=  (  CMyDb  *  )pCommonParam->p0;
	 //  CListCtrl		*	pListCtrl		=  (  CListCtrl  *  )pCommonParam->p1;
	 HWND				hListCtrl		=	(  HWND  )pCommonParam->p1;
	 if  (  !hListCtrl  )  goto  errLabel;
	 int				iItem			=  (  int  )pCommonParam->p2;
	 //
	 BOOL				bUnprocedOnly	=	(  BOOL  )p1;
	 //
	 IM_TASK_RCD	*	pQMem			=  (  IM_TASK_RCD  *  )p2;
	 int				index			=  0;

	 if  (  bUnprocedOnly  )  {
		 if  (  pQMem->iStatus  ==  CONST_imTaskStatus_req
			 ||  pQMem->iStatus  ==  CONST_imTaskStatus_resp
			 ||  pQMem->iStatus  ==  CONST_imTaskStatus_applyToSend
			 ||  pQMem->iStatus  ==  CONST_imTaskStatus_waitToSend
			 ||  pQMem->iStatus  ==  CONST_imTaskStatus_applyToRecv
			 ||  pQMem->iStatus  ==  CONST_imTaskStatus_waitToRecv
			 ||  pQMem->iStatus  ==  CONST_imTaskStatus_sending
			 ||  pQMem->iStatus  ==  CONST_imTaskStatus_receiving  )
		 {
			  }
		 else  {
			   iRet  =  0;  goto  errLabel;
		 }
	 }

	 //
	 {
		TCHAR	tBuf[255  +  1]  =  _T(  ""  );
		QY_MESSENGER_REGINFO    regInfo;
		MY_REG_DESC				desc;
		char		  timeBuf[CONST_qyTimeLen  +  1]  =  "";

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pQMem->id  );
		//  index  =  0;  pListCtrl->InsertItem(  iItem,  tBuf  );
		index  =  0;  myListCtrl_InsertItem(  hListCtrl,  iItem,  tBuf  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pQMem->uiType  );
		//  index  =  1;  pListCtrl->SetItemText(  iItem,  index,  tBuf  );
		index  =  1;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		if  (  qTraverse(  pDb->m_var.pQ_qyImObjRegInfoTab,  tmpHandler_bGetMessengerRegInfoBySth_myDb,  &pQMem->idInfo_send,  &regInfo  )  >  0  ){
			regInfo2Desc(  0,  &regInfo,  &desc,  NULL,  0,  NULL,  0  );
			if  (  desc.pSyr[0]  )  _sntprintf(  pQMem->senderDesc,  mycountof(  pQMem->senderDesc  ),  _T(  "%s - %s - %s"  ),  desc.pDw,  desc.pBm,  desc.pSyr  );  
		}
		//  index  =  2;  pListCtrl->SetItemText(  iItem,  index,  pQMem->senderDesc  );
		index  =  2;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  pQMem->senderDesc  );

		if  (  qTraverse(  pDb->m_var.pQ_qyImObjRegInfoTab,  tmpHandler_bGetMessengerRegInfoBySth_myDb,  &pQMem->idInfo_recv,  &regInfo  )  >  0  ){
			regInfo2Desc(  0,  &regInfo,  &desc,  NULL,  0,  NULL,  0  );
			if  (  desc.pSyr[0]  )  _sntprintf(  pQMem->receiverDesc,  mycountof(  pQMem->receiverDesc  ),  _T(  "%s - %s - %s"  ),  desc.pDw,  desc.pBm,  desc.pSyr  );  
		}
		//  index  =  3;  pListCtrl->SetItemText(  iItem,  index,  pQMem->receiverDesc  );
		index  =  3;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  pQMem->receiverDesc  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pQMem->iStatus  );
		//  index  =  4;  pListCtrl->SetItemText(  iItem,  index,  tBuf  );
		index  =  4;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  pQMem->subject  );
		//  index  =  5;  pListCtrl->SetItemText(  iItem,  index,  tBuf  );
		index  =  5;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		getTimeStr(  pQMem->tSendTime,  timeBuf,  mycountof(  timeBuf  )  );
		//  index  =  6;  pListCtrl->SetItemText(  iItem,  index,  CQyString(  timeBuf  )  );
		index  =  6;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  CQyString(  timeBuf  )  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pQMem->uiTranNo  );
		//  index  =  7;  pListCtrl->SetItemText(  iItem,  index,  tBuf  );
		index  =  7;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		getTimeStr(  pQMem->tRecvTime,  timeBuf,  mycountof(  timeBuf  )  );
		//  index  =  8;  pListCtrl->SetItemText(  iItem,  index,  CQyString(  timeBuf  )  );
		index  =  8;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  CQyString(  timeBuf  )  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  pQMem->content  );
		//  index  =  9;  pListCtrl->SetItemText(  iItem,  index,  tBuf  );
		index  =  9;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pQMem->idInfo_send.ui64Id  );
		//  index  =  10;  pListCtrl->SetItemText(  iItem,  index,  tBuf  );
		index  =  10;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pQMem->idInfo_recv.ui64Id  );
		//  index  =  11;  pListCtrl->SetItemText(  iItem,  index,  tBuf  );
		index  =  11;  myListCtrl_SetItemText(  hListCtrl,  iItem,  index,  tBuf  );

	 }


	 iRet  =  0;
errLabel:
	 return  iRet;
 }
BOOL  bDisplayMcViewContent_imTaskList_unproced(  HWND  hListCtrl,  void  *  p1,  void  *  p2  )
 {
	 BOOL  bRet  =  FALSE;
	 QY_MC				*	pQyMc		=	QY_GET_GBUF(  );
	 FUNCS_for_isCliHelp	*pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  );
	 if  (  !pFuncs  )  goto  errLabel;
	 QY_SERVICEGUI_INFO	*	pSgi		=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	 if  (  !pSgi  )  goto  errLabel;
	 MC_VAR_isCli		*	pProcInfo	=	(  MC_VAR_isCli  *  )pSgi->pVar;
	 if  (  !pProcInfo  )  goto  errLabel;
	 //  if  (  !pListCtrl  )  goto  errLabel;
	 if  (  !hListCtrl  )  goto  errLabel;
	 int					cnt			=	0;
	 MIS_CNT			*	pMisCnt		=	getMisCntByName(  pQyMc,  pProcInfo,  _T(  ""  )  );
	 CMyDb				*	pDb			=	(  CMyDb  *  )pFuncs->pf_getProcedObjDb(  0,  pQyMc->iDsnIndex_mainSys  )->pDb;

#if  0
	 myListCtrl_delAllColumns(  pListCtrl->m_hWnd  );
	 if  (  !myListCtrl_bAddColumns(  pListCtrl->m_hWnd,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_imTaskListColumns  )  )  )  goto  errLabel;

	 pListCtrl->DeleteAllItems(  );
#endif
	 myListCtrl_delAllColumns(  hListCtrl  );
	 if  (  !myListCtrl_bAddColumns(  hListCtrl,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_imTaskListColumns  )  )  )  goto  errLabel;

	 myListCtrl_DeleteAllItems(  hListCtrl  );


	 COMMON_PARAM	commonParam;
	 MACRO_makeCommonParam3(  pDb,  hListCtrl,  (  void  *  )cnt,  commonParam  );
	 
	 BOOL  bUnprocedOnly  =  TRUE;
	 qTraverse(  pDb->m_var.pQ_qyImTaskTab,  tmpHandler_displayImTask_cur,  &commonParam,  (  void  *  )bUnprocedOnly  );
	  

	 bRet  =  TRUE;
errLabel:
	 return  bRet;
 }

  //  2013/02/17
 BOOL  bViewImTaskList_unproced_myDb(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL					bRet										=	FALSE;
	QY_MC				*	pQyMc										=	QY_GET_GBUF(  );
#if  0
	TCHAR					whereClause[CONST_maxSqlBufLen  +  1]		=	_T(  ""  );

	_sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "(T.iStatus in(%d,%d,%d,%d,%d,%d,%d,%d))"  ), 
															CONST_imTaskStatus_req,
															CONST_imTaskStatus_resp,
															CONST_imTaskStatus_applyToSend,
															CONST_imTaskStatus_waitToSend,
															CONST_imTaskStatus_applyToRecv,
															CONST_imTaskStatus_waitToRecv,
															CONST_imTaskStatus_sending,
															CONST_imTaskStatus_receiving
															);
	if  (  wherePart  &&  wherePart[0]  )  _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "%s and (%s)"  ),  whereClause,  wherePart  );

	bRet  =  bViewImTaskListFunc(  pObjDb,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_unfinished  ),  whereClause,  FALSE  );
#endif

	viewStatusCli(  CONST_qyLvType_unprocedImTaskList,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_unfinished  ),  CONST_resId_imTaskListColumns,	 (  PF_commonHandler  )bDisplayMcViewContent_imTaskList_unproced   );

	bRet  =  0;
errLabel:
	return  bRet;
}

 BOOL  bDisplayMcViewContent_imTaskList_cur(  HWND  hListCtrl,  void  *  p1,  void  *  p2  )
 {
	 BOOL  bRet  =  FALSE;
	 QY_MC				*	pQyMc		=	QY_GET_GBUF(  );
	 FUNCS_for_isCliHelp	*pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  );
	 if  (  !pFuncs  )  goto  errLabel;
	 QY_SERVICEGUI_INFO	*	pSgi		=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	 if  (  !pSgi  )  goto  errLabel;
	 MC_VAR_isCli		*	pProcInfo	=	(  MC_VAR_isCli  *  )pSgi->pVar;
	 if  (  !pProcInfo  )  goto  errLabel;
	 //  if  (  !pListCtrl  )  goto  errLabel;
	 if  (  !hListCtrl  )  goto  errLabel;
	 int					cnt			=	0;
	 MIS_CNT			*	pMisCnt		=	getMisCntByName(  pQyMc,  pProcInfo,  _T(  ""  )  );
	 CMyDb				*	pDb			=	(  CMyDb  *  )pFuncs->pf_getProcedObjDb(  0,  pQyMc->iDsnIndex_mainSys  )->pDb;

#if  0
	 myListCtrl_delAllColumns(  pListCtrl->m_hWnd  );
	 if  (  !myListCtrl_bAddColumns(  pListCtrl->m_hWnd,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_imTaskListColumns  )  )  )  goto  errLabel;

	 pListCtrl->DeleteAllItems(  );
#endif
	 myListCtrl_delAllColumns(  hListCtrl  );
	 if  (  !myListCtrl_bAddColumns(  hListCtrl,  (  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_imTaskListColumns  )  )  )  goto  errLabel;

	 myListCtrl_DeleteAllItems(  hListCtrl  );

	 COMMON_PARAM	commonParam;
	 //  MACRO_makeCommonParam3(  pDb,  pListCtrl,  (  void  *  )cnt,  commonParam  );
	 MACRO_makeCommonParam3(  pDb,  hListCtrl,  (  void  *  )cnt,  commonParam  );
	 
	 BOOL  bUnprocedOnly  =  FALSE;
	 qTraverse(  pDb->m_var.pQ_qyImTaskTab,  tmpHandler_displayImTask_cur,  &commonParam,  (  void  *  )bUnprocedOnly  );
	  

	 bRet  =  TRUE;
errLabel:
	 return  bRet;
 }


//  2013/02/16
 BOOL  bViewImTaskList_cur_myDb(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL					bRet			=	FALSE;
	QY_MC				*	pQyMc			=	QY_GET_GBUF(  );
#if  0
	//  CQyMcApp			*	pApp			=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpImTaskListQueryStruct  );
	TCHAR				*	pTabName		=	bHisTab  ?  CONST_tabName_qyImTaskHisTab  :  CONST_tabName_qyImTaskTab;
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	bHisTab  ?  CONST_qyQueryType_imTaskHisList  :  CONST_qyQueryType_imTaskList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  NULL,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from (%s as T left join qyImObjRegInfoTab as B on (T.misServName=B.misServName and T.idStr_send=B.idStr) )"  ),  pTabName  );
	_sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s"  ),  CString(  wherePart  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "B.idStr"  )  );
	
	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	tmpSel.u.query.pfProcEvent  =  netMc_procEvent;
	tmpSel.u.query.pfProcEvent_new  =  is_procEvent_new;
	tmpSel.u.query.uPopupMenuId  =  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos  =  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  ?  CONST_resId_popup_viewImTaskList_isClient  :  CONST_resId_popup_viewImTaskList_isMgr;		//  2003/12/17ÐÞ¸Ä
	tmpSel.u.query.uiDefaultCmd  =  ID_qyTalkToTaskPeer;

	_sntprintf(  tmpSel.u.query.docName,  mycountof(  tmpSel.u.query.docName  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  "%s"  ),  bHisTab  ?  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyTaskHisList  )  :  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyTaskList  )  );
	
	//  bRet  =  pApp->bNewQueryView(  &tmpSel  );
	if  (  viewDlgListView_db(  pQyMc->gui.hMainWnd,  0,  &tmpSel  )  )  goto  errLabel;
#endif

	viewStatusCli(  CONST_qyLvType_currentImTaskList,  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_current  ),  CONST_resId_imTaskListColumns,	 (  PF_commonHandler  )bDisplayMcViewContent_imTaskList_cur   );

	bRet  =  TRUE;

errLabel:

	return  bRet;
	
}

  BOOL  bViewImTaskList_his_myDb(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
  {
#ifdef  __DEBUG__
	    traceLog(  _T(  "Not supported: bViewImTaskList_his_myDb"  )  );
#endif
	  return  FALSE;
  }



BOOL  bInsertPhoneGuest_procMsgTalk_work_myDb(  void  *  pDbParam,  int  iDbType,  void  *  pQyMcParam,  MIS_MSG_TALK  *  pMsg,  void  *  pGuestParam  )
{
#ifdef  __DEBUG__
	    traceLog(  _T(  "Not supported: bInsertPhoneGuest_procMsgTalk_work_myDb"  )  );
#endif
	  return  FALSE;
}

BOOL  bUpdateImTask_bChkQyMcEnv_mis_myDb(  void  *  pDb,  int  iStatus_set,  int  iStatus_0,  int  iStatus_1  )
{
#ifdef  __DEBUG__
	    traceLog(  _T(  "Not supported: bUpdateImTask_bChkQyMcEnv_mis_myDb"  )  );
#endif
	  return  TRUE;
}

int  deleteDynBmp_tmpHandler_delOld_dynBmpQ_myDb(  void  *  pDb,  int  id  )
{
	return  -1;
}

int  iSelectDynBmp_mcProcResp_retrieveDynBmps_myDb(  void  *  pDb,  void  *  pCtxParam  )
{
#ifdef  __DEBUG__
	    traceLog(  _T(  "Not supported: iSelectDynBmp_mcProcResp_retrieveDynBmps_myDb"  )  );
#endif
	return  -1;
}

BOOL  bInsertDynBmp_mcProcResp_retrieveDynBmps_myDb(  void  *  pDb,  void  *  pMisCntParam,  QIS_DYN_BMP  *  pMem,  char  *  pTimeBuf  )
{
#ifdef  __DEBUG__
	    traceLog(  _T(  "Not supported: bInsertDynBmp_mcProcResp_retrieveDynBmps_myDb"  )  );
#endif
	  return  FALSE;
}

BOOL  bUpdateDynBmp_mcProcResp_retrieveDynBmps_myDb(  void  *  pDb,  void  *  pMemParam,  int  rcdId  )
{
#ifdef  __DEBUG__
	    traceLog(  _T(  "Not supported: bUpdateDynBmp_mcProcResp_retrieveDynBmps_myDb"  )  );
#endif
	  return  FALSE;
}

BOOL  bUpdateImObjRegInfo_procMsgInput_scheduler_myDb(  void  *  pDb,  void  *  pSciParam,  void  *  pMisCntParam,  QY_MESSENGER_ID  *  pIdInfo  )
{
#ifdef  __DEBUG__
	    traceLog(  _T(  "Not supported: bUpdateImObjRegInfo_procMsgInput_scheduler_myDb"  )  );
#endif
	  return  FALSE;
}


 BOOL  bStatImTasks_myDb(  void  *  pProcInfoParam,  void  *  pMisCntParam,  void  *  pDb,  int  iDbType  )
{
#ifdef  __DEBUG__
	    traceLog(  _T(  "Not supported: bStatImTasks_myDb"  )  );
#endif
	  return  FALSE;
}

 BOOL  bDeleteFromTabById_myDb(  void  *  pDb,  int  iDbType,  LPCTSTR  pTabName,  int  id  )
{
	  return  FALSE;
}
 BOOL  bDeleteFromTabByIdInfo_myDb(  void  *  pDb,  int  iDbType,  LPCTSTR  pTabName,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  )
{
	  return  FALSE;
}
BOOL  bDeleteImOtherRegInfoByAddr_myDb(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  LPCTSTR  pTabName,  MSGR_ADDR  *  pAddr  )
{
	  return  FALSE;
}

int  iSelectImGrpMem_dlgSelect_isCli_myDb(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  HWND  idc_hWnd  )
{
	return  -1;
}

int  tmpHandler_iSelectImObj_dlgSelect_isCli_myDb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int  iRet  =  -1;

	COMMON_PARAM	*	pCommonParam	=	(  COMMON_PARAM  *  )p0;
	//
	CMyDb			*	pMyDb			=	(  CMyDb  *  )pCommonParam->p0;
	int					iDbType			=	(  int  )pCommonParam->p1;
	LPCTSTR				misServName		=	(  LPCTSTR  )pCommonParam->p2;
	//
	HWND				hCombo			=	(  HWND  )p1;
	//
	QMEM_qyImObj	*	pQMem	=	(  QMEM_qyImObj  *  )p2;

	QY_MC			*	pQyMc	=   QY_GET_GBUF(  );
	TCHAR	talkerDesc[255 + 1] =  _T(  ""  );
	QY_MESSENGER_REGINFO		regInfo;
	MY_REG_DESC					desc;
	

	QM_dbFuncs  *  pDbFuncs  =  QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	if  (  pQMem->messengerInfo.uiType  ==  CONST_objType_messenger  )  {

		memset(  &regInfo,  0,  sizeof(  regInfo  )  );

		if  (  g_dbFuncs.pf_bGetMessengerRegInfoBySth(  pMyDb,  iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_tabName_qyImObjRegInfoTab,  misServName,  &pQMem->messengerInfo.idInfo,  0,  &regInfo  )  )  {
			regInfo2Desc(  0,  &regInfo,  &desc,  talkerDesc,  mycountof(  talkerDesc  ),  NULL,  0  );
		}
		else  {
			memset(  &regInfo,  0,  sizeof(  regInfo  )  );
			memset(  &desc,  0,  sizeof(  desc  )  );
		}

		_sntprintf(  talkerDesc,  mycountof(  talkerDesc  ),  _T(  "%I64u - %s %s %s"  ),  pQMem->messengerInfo.idInfo.ui64Id,  desc.pDw,  desc.pBm,  desc.pSyr  );
		SendMessage(  hCombo,  CB_ADDSTRING,  0,  (  LPARAM  )talkerDesc  );		
		
	}

	iRet  =  0;
errLabel:
	return  iRet;
}

int  iSelectImObj_dlgSelect_isCli_myDb(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  HWND  idc_hWnd  )
{
	int				iRet  =  -1;
	CMyDb		*	pMyDb  =  (  CMyDb  *  )pDb;
	COMMON_PARAM	commonParam;

	MACRO_makeCommonParam3(  pMyDb,  (  void  *  )iDbType,  (  void  *  )misServName,  commonParam  ); 

	iRet  =  qTraverse(  pMyDb->m_var.pQ_qyImObjTab,  tmpHandler_iSelectImObj_dlgSelect_isCli_myDb,  &commonParam,  idc_hWnd  );
#if  0
	TCHAR		sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	TCHAR		tBuf[255  +  1]						=	_T(  ""  );

				  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyImObjTab.idStr,qyImObjRegInfoTab.col2,qyImObjRegInfoTab.col3,qyImObjRegInfoTab.col4 from qyImObjTab left join qyImObjRegInfoTab on (qyImObjTab.misServName=qyImObjRegInfoTab.misServName and qyImObjTab.idStr=qyImObjRegInfoTab.idStr) where qyImObjTab.misServName=%s and qyImObjTab.uiType in (%d) order by qyImObjTab.idStr"  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_misServName,  m_var.u.selectImGrp.misServName  ),  CONST_objType_messenger  );
				  if  (  enumSqlQuery(  m_var.pObjDb->pDb,  sqlBuf,  tmpHandler_displayMessenger,  GetDlgItem(  IDC_COMBO_objList  )->m_hWnd,  0,  varVals,  mycountof(  varVals  ),  NULL  )  <  0  )  goto  errLabel;

#endif				  

errLabel:
	return  iRet;
}

#if  0
int  iSelectImObjAuth2_dlgSelect_isCli_myDb(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  HWND  idc_hWnd  )
{
	return  -1;
}
#endif

int  iSelectDynBmp_dlgSelect_isCli_myDb(  void  *  pDb, int  iDbType,  LPCTSTR  misServName,  HWND  idc_hWnd  )
{
	return  -1;
}


//
int  tmpHandler_enumTalkingFriend_bUsed(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int		iErr	=	-1;
	int		iTaskId	=	(  int  )p0;
	//  BOOL  *  pbUsed  =  (  BOOL  *  )p1;
	MIS_MSG_TALKINGFRIEND_QMC  *  pFriend  =  (  MIS_MSG_TALKINGFRIEND_QMC  *  )p2;

	if  (  !isTalkerShadowMgr(  pFriend->addr  )  )  {
		iErr  =  0;  goto  errLabel;
	}

	QY_WMBUF_COMM  wmBuf;		
	memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );						
	wmBuf.uiType  =  CONST_qyWmParam_chkTask;
	wmBuf.u.chkTask.iTaskId  =  iTaskId;

	SendMessage(  pFriend->hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
	if  (  !wmBuf.u.chkTask.bChked  )  goto  errLabel;
	
	if  (  !wmBuf.u.chkTask.bNotExists  )  {
		iErr  =  1;  goto  errLabel;
	}

	iErr  =  0;
errLabel:


	return  iErr;
}

BOOL  tmpHandler_bNotUsed_imTask(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	BOOL			bRet	=	FALSE;
	MIS_CNT		*	pMisCnt	=	(  MIS_CNT  *  )p0;
	//  p1
	IM_TASK_RCD  *  pRcd  =  (  IM_TASK_RCD  *  )p2;

	MC_VAR_isCli  *	pProcInfo	=	QY_GET_procInfo_isCli(  );
	BOOL			bUsed	=	FALSE;
	

	if  (  qTraverse(  &pMisCnt->talkingFriendQ,  tmpHandler_enumTalkingFriend_bUsed,  (  void  *  )pRcd->id,  0  )  )  {
		//  bUsed  =  TRUE;
		goto  errLabel;
	}

	//
	if  (  IsWindow(  pProcInfo->hWnd_shareDynBmps  )  )  {
		QY_WMBUF_COMM  wmBuf;		

		memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );						
		wmBuf.uiType  =  CONST_qyWmParam_chkTask;
		wmBuf.u.chkTask.iTaskId  =  pRcd->id;
		
		SendMessage(  pProcInfo->hWnd_shareDynBmps,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
		if  (  !wmBuf.u.chkTask.bChked  )  goto  errLabel;
		if  (  wmBuf.u.chkTask.bChked  )  goto  errLabel;
	}

	//
	qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "tmpHandler_bNotUsed_imTask: task %d not used, will be removed"  ),  pRcd->id  );

	bRet  =  TRUE;

errLabel:
	return  bRet;
}

BOOL  tmpHandler_bTooManyImMsg(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	BOOL	bRet	=	FALSE;
	//  p0
	int  *  piCnt		=	(  int  *  )p1;
	IM_MSG_RCD	*	pRcd  =  (  IM_MSG_RCD  *  )p2;

	if  (  (  *piCnt  )  >  0  )  {
		(  *piCnt    )  --  ;
		bRet  =  TRUE;  goto  errLabel;
	}

errLabel:

	return  bRet;
}

 //  2013/03/07
 __declspec(  dllexport  )  int  qisChkDb_gui_myDb(  )			
{
	 int			iErr	=	-1;
	 QY_MC		*	pQyMc	=	QY_GET_GBUF(  );
	 MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	 if  (  !pProcInfo  )  return  -1;

	 void		*	pDbParam		=	NULL;	
	 int			iDbType								=	pQyMc->cfg.db.iDbType;
	 
	 //
	 if  (  iDbType  !=  CONST_dbType_myDb  )  return  -1;

	 //
	 if  (  GetTickCount(  )  -  pProcInfo->status.dwTickCnt_chkDb  <  5  *  60  *  1000  )  return  0;
	 pProcInfo->status.dwTickCnt_chkDb  =  GetTickCount(  );


 	#ifdef  __DEBUG__
			_ASSERT(  pProcInfo->processQ_media.m_var.dwThreadId_gui  ==  GetCurrentThreadId(  )  );
	#endif



	 //
	 CQnmDb							db;
	
	 if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
	 pDbParam  =  db.m_pDbMem->pDb;


	 CMyDb  *  pDb  =  (  CMyDb  *  )pDbParam;
	 GENERIC_Q	*	pQ;
	 MIS_CNT	*	pMisCnt	=	getMisCntByName(  pQyMc,  pProcInfo,  _T(  ""  )  );
	 if  (  !pMisCnt  )  goto  errLabel;
	 
	 pQ  =  pDb->m_var.pQ_qyImTaskTab;
	 if  (  pQ->uiQNodes  >  pQ->cfg.uiMaxQNodes  /  2  ||  pQ->uiQNodes  >  200  )  {
		 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "qisChkDb_gui_myDb, start to chk and clean imTaskTab, qNodes %d"  ),  pQ->uiQNodes  );

		 qRemoveMsg(  pQ,  tmpHandler_bNotUsed_imTask,  pMisCnt,  0  );

		 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "qisChkDb_gui_myDb, chking imTaskTab ends, qNodes %d"  ),  pQ->uiQNodes  );
	 }

	 //
	 pQ  =  pDb->m_var.pQ_qyImMsgTab;
	 int  iInterval  =  min(  pQ->cfg.uiMaxQNodes  /  10,  100  );
	 if  (  isQWarning(  pQ,  iInterval  )  )  {
		 int	cnt  =  iInterval;
		 if  (  cnt  <=  0  )  goto  errLabel;

		 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "qisChkDb_gui_myDb, start to chk and clean imMsgTab, qNodes %d"  ),  pQ->uiQNodes  );

		 qRemoveMsg(  pQ,  tmpHandler_bTooManyImMsg,  0,  &cnt  );

		 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "qisChkDb_gui_myDb, start to chk imMsgTab, qNodes %d"  ),  pQ->uiQNodes  );
	 }
	 
errLabel:

	 return  iErr;
 }

