

#include  "stdafx.h"
#include  "qmdCommon.h"

CTime getCTimeByQyTime(  char  *  timeBuf  );


 int  refreshObjQMemPolicy(  void  *  pDb,  QM_OBJQ  *  pQ,  char  *  mac0,  QNM_CMDPARAM_getOpCmd  *  pGetOpCmd,  long  lRefreshedTime,  TCHAR  *  cmdDesc,  unsigned  int  size  )
{
	 int					iErr				=		-1;
	 QNM_CMDPARAM_getOpCmd	cmdParam;
	 BOOL					bGetPolicyFromDb	=		FALSE;

	 if  (  !bMacValid(  mac0  )  )  {
		 if  (  cmdDesc  )  _sntprintf(  cmdDesc,  size,  _T(  "Invalid mac"  )  );
		 goto  errLabel;
	 }

	 if  (  findQMemByKey(  0,  pQ,  mac0,  0  )  )  {
		 if  (  cmdDesc  )  _sntprintf(  cmdDesc,  size,  _T(  "该对象不在管理队列中，策略无法立即生效"  )  );
		 goto  errLabel;
	 }

	 if  (  pGetOpCmd  )  memcpy(  &cmdParam,  pGetOpCmd,  sizeof(  cmdParam  )  );
	 else  {
		   PC_STATUS_INFO	pcStatus;
		   memset(  &pcStatus,  0,  sizeof(  pcStatus  )  );
		   if  (  getPcStatusInfo(  pDb,  mac0,  CONST_fieldIdTable_en,  &pcStatus  )  )  memset(  &pcStatus,  0,  sizeof(  pcStatus  )  );

		   memset(  &cmdParam,  0,  sizeof(  cmdParam  )  );
		   cmdParam.ucbOped  =  pcStatus.ucbOped;				//  2006/03/23
		   cmdParam.ucbViewRemoteDesktop  =  pcStatus.ucbOped  &&  pcStatus.ucbViewRemoteDesktop;	 
		   cmdParam.ucbMonDesktop  =  pcStatus.ucbOped  &&  pcStatus.ucbMonDesktop;				//  2006/03/06  
		   //
		   bGetPolicyFromDb  =  TRUE;
		   //
	 }

	 {
		 QM_OBJQ_MEM		mem;
	
		 if  (  findQMemByKey(  0,  pQ,  mac0,  &mem  )  )  {
			 if  (  cmdDesc  )  _sntprintf(  cmdDesc,  size,  _T(  "该对象不在管理队列中，策略无法立即生效"  )  );
			 goto  errLabel;
		 }

		 //  因为内存中的getOpCmd的ucbMonDesktop一般是从界面上传过来的秒数。所以，将这个参数先取出放入cmdParam中
		 if  (  bGetPolicyFromDb  )  {
             if  (  (  (  QMEM_PC  *  )mem.pQMemObj  )->getOpCmd.ucbMonDesktop  &&  cmdParam.ucbMonDesktop  )  {
				 cmdParam.ucbMonDesktop  =  (  (  QMEM_PC  *  )mem.pQMemObj  )->getOpCmd.ucbMonDesktop;
				 //
			 }
			 if  (  cmdParam.ucbMonDesktop  )  {
                 if  (  cmdParam.ucbMonDesktop  <  CONST_minMonDesktopIntervalIsS  )  cmdParam.ucbMonDesktop  =  CONST_minMonDesktopIntervalIsS;
			 }
		 }

		 if  (  memcmp(  &(  (  QMEM_PC  *  )mem.pQMemObj  )->getOpCmd,  &cmdParam,  sizeof(  cmdParam  )  )  )  memcpy(  &(  (  QMEM_PC  *  )mem.pQMemObj  )->getOpCmd,  &cmdParam,  sizeof(  cmdParam  )  );

		 if  (  cmdDesc  )  _sntprintf(  cmdDesc,  size,  _T(  "bOped is %d, bRD is %d, bMon is %d"  ),  cmdParam.ucbOped,  cmdParam.ucbViewRemoteDesktop,  cmdParam.ucbMonDesktop  );					//  2006/03/06

		 (  (  QMEM_PC  *  )mem.pQMemObj  )->lRefreshedTime  =  lRefreshedTime;

	 }

	 iErr  =  0;

errLabel:
	 return  iErr;
}

#if  0
 static  BOOL  tmpHandler_enumOpedPcs(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 MT_SUBTHREADINFO	*	pThreadInfo		=	(  MT_SUBTHREADINFO  *  )p0;
	 CQyMcDaemon		*	pDaemon			=	(  CQyMcDaemon  *  )pThreadInfo->pParentParam;
	 long					lRefreshedTime	=	(  long  )p1;
	 CDBVariant			*	pVarVals		=	(  CDBVariant  *  )p2;
	 int					index			=	0;
	 TCHAR					tBuf[128];
	 char					mac0[CONST_qyMacLen  +  1]	=	"";
	 //
	 int					iServiceId		=	CONST_qyServiceId_netMc;
	 QY_SERVICE_INFO	*	pServiceInfo	=	(  QY_SERVICE_INFO  *  )pDaemon->getSpecialProperty(  CONST_qyPropertyId_serviceInfo_byServiceId,  (  void  *  )iServiceId,  0  );
	 if  (  !pServiceInfo  ||  !pServiceInfo->pObjQ  ||  !pServiceInfo->ucbVarInited  )  goto  errLabel;
	 QM_OBJQ			*	pObjQ;
	 //
	 pObjQ  =	(  QM_OBJQ  *  )pServiceInfo->pObjQ;

	 index  =  0;	MACRO_sqlStr(  pVarVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  mac0,  mycountof(  mac0  )  );
	 index  ++	;

	 traceLogA(  "mac0 is %s",  mac0  );

	 if  (  refreshObjQMemPolicy(  pThreadInfo->pDb,  pObjQ,  mac0,  0,  lRefreshedTime,  NULL,  0  )  )  goto  errLabel;
	 
errLabel:
	 return  TRUE;
}
#endif


 int  refreshQmObjQInfo_netMc(  MT_SUBTHREADINFO  *  pThreadInfo  )
{
	 int					iErr			=		-1;
	 CQyMcDaemon		*	pDaemon			=		(  CQyMcDaemon  *  )pThreadInfo->pParentParam;
	 //  
	 TCHAR					sqlBuf[CONST_maxSqlBufLen  +  1];
	 CDBVariant				varVals[5];
	 long					lRefreshedTime;
	 //
	 int					iServiceId		=	CONST_qyServiceId_netMc;
	 QY_SERVICE_INFO	*	pServiceInfo	=	(  QY_SERVICE_INFO  *  )pDaemon->getSpecialProperty(  CONST_qyPropertyId_serviceInfo_byServiceId,  (  void  *  )iServiceId,  0  );
	 if  (  !pServiceInfo  ||  !pServiceInfo->pObjQ  ||  !pServiceInfo->ucbVarInited  )  goto  errLabel;
	 QM_OBJQ			*	pObjQ;
	 //
	 pObjQ  =	(  QM_OBJQ  *  )pServiceInfo->pObjQ;


	 time_t  t;
	 time(  &t  );  lRefreshedTime  =  (  long  )t;

#if  0
	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select distinct qyPcTab.mac0 from (qyPcTab left join qyPcStatusTab on qyPcTab.mac0=qyPcStatusTab.mac0) left join qyPcOpQTab on (qyPcTab.mac0=qyPcOpQTab.mac0) where qyPcOpQTab.iStatus=%d or qyPcOpQTab.iStatus=%d "   ),  CONST_cmdStatus_start,  CONST_cmdStatus_restart  );
	 
	 traceLogA(  "sql is [%S]",  sqlBuf  );

	 bEnumSqlQuery(  pThreadInfo->pDb,  sqlBuf,  tmpHandler_enumOpedPcs,  pThreadInfo,  (  void  *  )lRefreshedTime,  varVals,  mycountof(  varVals  )  );  
#else
	 //  2010/11/30

	 char  mac0[CONST_qyMacLen  +  1]	=	"000000000000";
	 char	buf[128];
	 TCHAR	tBuf[128];
	 for  (  ;  ;  )  {
		  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select distinct qyPcTab.mac0 from (qyPcTab left join qyPcStatusTab on qyPcTab.mac0=qyPcStatusTab.mac0) left join qyPcOpQTab on (qyPcTab.mac0=qyPcOpQTab.mac0) where (qyPcOpQTab.iStatus=%d or qyPcOpQTab.iStatus=%d) and qyPcTab.mac0>'%s' order by qyPcTab.mac0  "   ),  CONST_cmdStatus_start,  CONST_cmdStatus_restart,  CString(  mac0  )  );
		  if  (  !bQyGetRcdBySql(  pThreadInfo->pDb,  sqlBuf,  mycountof(  varVals  ),  varVals  )  )  break;
		  MACRO_sqlStr(  varVals[0],  tBuf,  mycountof(  tBuf  )  );	myTChar2Utf8(  tBuf,  buf,  mycountof(  buf  )  );
		  if  (  !strcmpi(  buf,  mac0  )  )  break;

		  safeStrnCpy(  buf,  mac0,  mycountof(  mac0  )  );
#ifdef  __DEBUG__
		  traceLog(  _T(  "refreshQmObjQLastCommTime_netMc: to refresh %s"  ),  CString(  mac0  )  );
#endif

		  QM_OBJQ			*	pObjQ;
		  //
		  pObjQ  =	(  QM_OBJQ  *  )pServiceInfo->pObjQ;

		  if  (  refreshObjQMemPolicy(  pThreadInfo->pDb,  pObjQ,  mac0,  0,  lRefreshedTime,  NULL,  0  )  )  {
			  traceLog(  _T(  "refreshObjQMemPolicy failed"  )  );
		  }

	 }


#endif

	 unsigned  int			uiQCnt;
	 QM_OBJQ_MEM			mem;
	 int					i;
			 
	 uiQCnt  =  pObjQ->cnt;
	 if  (  uiQCnt  >  pObjQ->maxCnt  )  uiQCnt  =  pObjQ->maxCnt;

	 for  (  i  =  0;  i  <  (  int  )uiQCnt;  i  ++  )  {		 
		 {
			 CQyRWLock	syncObj;
#if  0
			 if  (  syncObj.rLock(  pObjQ->mutexName,  pObjQ->uiMilliSeconds_mutex_r,  pObjQ->hSema,  pObjQ->uiMilliSeconds_sema_r  )  )  continue;
#else
			 if  (  syncObj.rLock(  pObjQ->pRw,  pObjQ->uiMilliSeconds_sema_r  )  )  continue;
#endif
			 memcpy(  &mem,  &pObjQ->pMems[i],  sizeof(  mem  )  );
		 }
			
		 if  (  (  (  QMEM_PC  *  )mem.pQMemObj  )->lRefreshedTime  !=  lRefreshedTime  )  {
			 memset(  &(  (  QMEM_PC  *  )mem.pQMemObj  )->getOpCmd,  0,  sizeof(  (  (  QMEM_PC  *  )mem.pQMemObj  )->getOpCmd  )  );
			 (  (  QMEM_PC  *  )mem.pQMemObj  )->lRefreshedTime  =  lRefreshedTime;
		 }
	
	 }
 

	 iErr  =  0;
errLabel:
	 
	 return  iErr;
}


 int  refreshQmObjQLastCommTime_netMc(  MT_SUBTHREADINFO  *  pThreadInfo  )
{
	 int					iErr			=		-1;
	 CQyMcDaemon		*	pDaemon			=		(  CQyMcDaemon  *  )pThreadInfo->pParentParam;
	 int					cnt;
	 int					i;
	 char					timeBuf[128];
	 char				*	p;
	 //	 
	 int					iServiceId		=	CONST_qyServiceId_netMc;
	 QY_SERVICE_INFO	*	pServiceInfo	=	(  QY_SERVICE_INFO  *  )pDaemon->getSpecialProperty(  CONST_qyPropertyId_serviceInfo_byServiceId,  (  void  *  )iServiceId,  0  );
	 if  (  !pServiceInfo  ||  !pServiceInfo->pObjQ  ||  !pServiceInfo->ucbVarInited  )  goto  errLabel;
	 QM_OBJQ			*	pObjQ;
	 QM_OBJQ_MEM		*	pMem;
	 //
	 pObjQ  =	(  QM_OBJQ  *  )pServiceInfo->pObjQ;


	 cnt  =  min(  pObjQ->cnt,  pObjQ->maxCnt  );
	 for  (  i  =  0;  i  <  cnt;  i  ++  )  {
		  pMem  =  &pObjQ->pMems[i];
		  if  (  (  (  QMEM_PC  *  )pMem->pQMemObj  )->lRefreshedLastCommTime  !=  (  (  QMEM_PC  *  )pMem->pQMemObj  )->lLastCommTime  )  {
			  getTimeStr(  (  (  QMEM_PC  *  )pMem->pQMemObj  )->lLastCommTime,  timeBuf,  sizeof(  timeBuf  )  );
			  p  =  inet_ntoa(  *(  in_addr  *  )&(  (  QMEM_PC  *  )pMem->pQMemObj  )->ulIp  );
			  if  (  !p  )  p  =  "";
			  refreshLastCommTime(  pThreadInfo->pDb,  timeBuf,  p,  (  (  QMEM_PC  *  )pMem->pQMemObj  )->mac  );
			  (  (  QMEM_PC  *  )pMem->pQMemObj  )->lRefreshedLastCommTime  =  (  (  QMEM_PC  *  )pMem->pQMemObj  )->lLastCommTime;
		  }
	 }

errLabel:
	 return  0;

 }


 
 int  refreshQmObjQStatusInDb_is(  MT_SUBTHREADINFO  *  pThreadInfo  )
{
	 int					iErr									=		-1;
	 CQyMcDaemon		*	pDaemon									=		(  CQyMcDaemon  *  )pThreadInfo->pParentParam;
	 //	 
	 int					iServiceId								=		pDaemon->var.iServiceId;
	 QY_SERVICE_INFO	*	pServiceInfo							=		(  QY_SERVICE_INFO  *  )pDaemon->getSpecialProperty(  CONST_qyPropertyId_serviceInfo_byServiceId,  (  void  *  )iServiceId,  0  );
	 if  (  !pServiceInfo  ||  !pServiceInfo->pObjQ  ||  !pServiceInfo->ucbVarInited  )  return  -1;
	 QM_OBJQ			*	pObjQ;
	 //
	 pObjQ  =	(  QM_OBJQ  *  )pServiceInfo->pObjQ;

	 unsigned  int			uiQCnt;
	 QM_OBJQ_MEM			mem;
	 int					i;
	 //
	 time_t					t;
	 TCHAR					sqlBuf[CONST_maxSqlBufLen  +  1]		=	_T(  ""  );
	 
	 traceLogA(  "refreshQmObjQStatusInDb_is enters: "  );

	 uiQCnt  =  min(  pObjQ->cnt,  pObjQ->maxCnt  );
	 for  (  i  =  0;  i  <  (  int  )uiQCnt;  i  ++  )  {
		  
		 {
			 CQyRWLock	syncObj;
#if  0
			 if  (  syncObj.rLock(  pObjQ->mutexName,  pObjQ->uiMilliSeconds_mutex_r,  pObjQ->hSema,  pObjQ->uiMilliSeconds_sema_r  )  )  continue;
#else
			 if  (  syncObj.rLock(  pObjQ->pRw,  pObjQ->uiMilliSeconds_sema_r  )  )  continue;
#endif
			 memcpy(  &mem,  &pObjQ->pMems[i],  sizeof(  mem  )  );
		 }


		 if  (  pObjQ->iType  ==  CONST_objQType_mis  )  {
			 QMEM_MESSENGER  *  pQMemMessenger;
			 //
		 	 pQMemMessenger  =  (  QMEM_MESSENGER  *  )mem.pQMemObj;
			 if  (  !pQMemMessenger  )  continue;
		 
			 t  =  pQMemMessenger->tLastRefreshedTime_statusInDb  -  pDaemon->var.cfg.usIntervalAheadInS_refreshTime_forMem;
			 if  (  t  <  pQMemMessenger->tLastRefreshedTime_ulIp
				 ||  t  <  pQMemMessenger->tLastRefreshedTime_ulDetectedIp
					||  t  <  pQMemMessenger->tLastRefreshedTime_usRunningStatus  )
			 {
				 QY_MESSENGER_INFO	*	pMessenger  =  &pQMemMessenger->messenger;
				 char					idStr[CONST_qyMessengerIdStrLen  +  1]	=	"";
				 char					ip12[CONST_qyMaxIpLen  +  1]			=	"";
				 char					detectedIp12[CONST_qyMaxIpLen  +  1]	=	"";
				 char					timeBuf[CONST_qyTimeLen  +  1]			=	"";

				 time(  &t  );
				 //
				 if  (  !idInfo2Str(  &pMessenger->idInfo,  idStr,  mycountof(  idStr  )  )  )  continue;
		 		 qyStdToIp12(  pMessenger->ip,  ip12  );
		 		 qyStdToIp12(  pMessenger->detectedIp,  detectedIp12  );
		 		 getTimeStr(  t,  timeBuf,  mycountof(  timeBuf  )  );
		 		 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set ip='%s',detectedIp='%s',clientVer='%s',usLangId=%d,uiDevType=%d,messengerName=%s,usRunningStatus=%d,iStatus=%d,tLastModifiedTime='%s' where misServName=%s and idStr='%s'"  ),  
										CONST_tabName_qyImObjTab,  CString(  ip12  ),  CString(  detectedIp12  ),  CString(  pMessenger->clientVer  ),  pMessenger->usLangId,  pMessenger->uiDevType,  getDbValStr(  pServiceInfo->cfg.db.iDbType,  CONST_iDataType_messengerName,  pMessenger->messengerName  ),  pMessenger->usRunningStatus,  pMessenger->iStatus,  CString(  timeBuf  ),  getDbValStr(  pServiceInfo->cfg.db.iDbType,  CONST_iDataType_misServName,  pMessenger->misServName  ),  CString(  idStr  )  );
				 OutputDebugString(  CString(  sqlBuf  )  +  _T(  "\n"  )  );
				 if  (  !bQyExecSql(  pThreadInfo->pDb,  sqlBuf  )  )  continue;

				 pQMemMessenger->tLastRefreshedTime_statusInDb  =  t;

			 }
		 }
	 }

	 iErr  =  0;

//  errLabel:

	 traceLogA(  "refreshQmObjQStatusInDb_is leaves"  );

	 return  iErr;

}


 typedef  struct  __ImInternalSchedulerRcd_t		{
				  int								id;
				  TCHAR								misServName[CONST_maxMisServNameLen  +  1];
				  QY_MESSENGER_ID					idInfo;
				  unsigned  int						uiType;
				  time_t							tSchedulerTime;
				  //
				  time_t							firstTime;
				  time_t							lastTime;
				  //
				  int								iStatus;
				  time_t							tLastModifiedTime;
				  
 }		   IM_INTERNAL_schedulerRcd;


 int  processScheduler_is(  MT_SUBTHREADINFO  *  pThreadInfo  )
{
	 int							iErr									=		-1;
	 CQyMcDaemon				*	pDaemon									=		(  CQyMcDaemon  *  )pThreadInfo->pParentParam;
	 //	 
	 int							iServiceId								=		pDaemon->var.iServiceId;
	 QY_SERVICE_INFO			*	pServiceInfo							=		(  QY_SERVICE_INFO  *  )pDaemon->getSpecialProperty(  CONST_qyPropertyId_serviceInfo_byServiceId,  (  void  *  )iServiceId,  0  );
	 if  (  !pServiceInfo  ||  !pServiceInfo->pObjQ  ||  !pServiceInfo->ucbVarInited  )  return  -1;
	 QMD_VAR_MIS			*	pVar			=		(  QMD_VAR_MIS  *  )pServiceInfo->pVar;
	 if  (  !pVar  )  return  -1;
	 MT_SOCK_IOCP				*	pMtSock									=		(  MT_SOCK_IOCP  *  )pServiceInfo->pMtSock;
	 if  (  !pMtSock  )  return  -1;

	 QM_OBJQ					*	pObjQ									=		(  QM_OBJQ  *  )pServiceInfo->pObjQ;

	 TCHAR							sqlBuf[CONST_maxSqlBufLen  +  1]		=		_T(  ""  );
	 char							timeBuf[CONST_qyTimeLen  +  1]			=		"";
	 CDBVariant						varVals[10];
	 int							index;
	 IM_INTERNAL_schedulerRcd		rcd;
	 TCHAR							tBuf[255  +  1];
	 char							buf[255  +  1];
	 TCHAR							sqlBuf1[CONST_maxSqlBufLen  +  1]		=		_T(  ""  );

	 getCurTime(  timeBuf  );

	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select id,misServName,idStr,uiType,tSchedulerTime from %s where tSchedulerTime<='%s'"  ),  CONST_tabName_qyImInternalSchedulerTab,  CString(  timeBuf  )  );
	 for  (  ;  !pDaemon->bQuit(  );  )  {
		  if  (  !bQyGetRcdBySql(  pThreadInfo->pDb,  sqlBuf,  mycountof(  varVals  ),  varVals  )  )  break;

		  memset(  &rcd,  0,  sizeof(  rcd  )  );

		  index  =  0;	MACRO_sqlLong(  varVals[index],  rcd.id  );
		  index  ++  ;	MACRO_sqlStr(  varVals[index],  rcd.misServName,  mycountof(  rcd.misServName  )  );
		  index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &rcd.idInfo  );
		  index  ++  ;	MACRO_sqlLong(  varVals[index],  rcd.uiType  );
		  index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  rcd.tLastModifiedTime  =  gettTimeByBuf(  buf  );

		  qyShowInfo(  CONST_qyShowType_warning,  0,  0,  _T(  "Server"  ),  0,  0,  _T(  ""  ),  _T(  "执行计划 %I64u %s"  ),  rcd.idInfo.ui64Id,  qyGetDesByType1(  CONST_qyCommTypeTable_en,  rcd.uiType  )  );

		  switch  (  rcd.uiType  )  {
				  case  CONST_imCommType_refreshImGrp:  {									 
					    QM_OBJQ_MEM			mem;									 
						QMEM_MESSENGER	*	pQMemGrp;
						GENERIC_Q		*	pOutputQ;
						CQMemHelp			qMemHelp;
									 
						if  (  findQMemByKey(  0,  pServiceInfo->pObjQ,  &rcd.idInfo,  &mem  )  )  {
							qyShowInfo(  CONST_qyShowType_warning,  0,  0,  _T(  "Server"  ),  0,  0,  _T(  ""  ),  _T(  "    %I64u 不在线"  ),  rcd.idInfo.ui64Id  );
							break;
						}
						{										 
							//										 
							if  (  !(  pQMemGrp  =  (  QMEM_MESSENGER  *  )mem.pQMemObj  )  )  goto  errLabel;							
							//										 
							MIS_MSG_applyForWork		msg_applyForWork;										 							
							memset(  &msg_applyForWork,  0,  sizeof(  msg_applyForWork  )  );										 
							msg_applyForWork.uiType  =  CONST_misMsgType_applyForWork;										 
							msg_applyForWork.uiContentType  =  rcd.uiType;							
							//
							//  if  (  !(  pOutputQ  =  getOutputQByChannelType(  pQMemGrp,  0  )  )  )  goto  errLabel;						
							if  (  !(  pOutputQ  =  qMemHelp.getOutputQ_toPostMsg(  pQMemGrp,  0  )  )  )  goto  errLabel;
						
							if  (  qPostMsg(  &msg_applyForWork,  sizeof(  msg_applyForWork  ),  pOutputQ  )  )  goto  errLabel;										 
							//										 
							if  (  postMsg2Mgr(  pMtSock,  CONST_misMsgType_processSelf,  0,  0,  0,  0,  0,  0,  0,  0,  (  char  *  )pQMemGrp,  0  )  )  goto  errLabel;
						}
						//
						}					    
					    break;
				  default:
						  break;
		  }

		  _sntprintf(  sqlBuf1,  mycountof(  sqlBuf1  ),  _T(  "delete from %s where id=%d"  ),  CONST_tabName_qyImInternalSchedulerTab,  rcd.id  );
		  if  (  !bQyExecSql(  pThreadInfo->pDb,  sqlBuf1  )  )  goto  errLabel;

	 }


	 iErr  =  0;
errLabel:
	 return  iErr;
}

  int  qmd_chkChannelTimeout(  QY_ENV  *  pEnv,  MT_SOCK_IOCP  *  pMtSock,  int  uiCliIndex,  MT_SOCK_CLIINFO_IOCP  *  pCliInfo,  PER_SOCKET_CONTEXT  *  p,  QMD_SESSION  *  pSession  )
{
	int					iErr		=	-1;
	CHANNEL_status_io	io;
	DWORD				dwTickCnt  =  GetTickCount(  );
	int					i			=	uiCliIndex;

	if  (  !pCliInfo->bUsed  )  return  0;

	if  (  !pSession->pQMemObj  )  {
		if  (  p->status.accept.dwTickCnt_accepted			 
			&&  dwTickCnt  -  p->status.accept.dwTickCnt_accepted  >  3000  )		 
		{
			p->status.accept.ucCnt_timeout  ++  ;			
			}
		else
			 p->status.accept.ucCnt_timeout  =  0;

		if  (  p->status.accept.ucCnt_timeout  >=  2  )  {
			 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  pSession->comm.clientIp,  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  ""  ),  _T(  "accept timeout, %dms, index %d, %I64u"  ),  dwTickCnt  -  p->status.accept.dwTickCnt_accepted,  i,  pSession->debugInfo.idInfo.ui64Id  ); 
			 postMsg2Iocp(  pMtSock,  CONST_misMsgType_closeChannel,  i,  0,  CONST_commFlg_resp,  0,  0,  0,  0,  0,  0,  0,  NULL  );		
		}

		iErr  =  0;  goto  errLabel;
	}

	getChannelStatus(  p,  NULL,  &io  );
	if  (  io.ucbReceiveing    
		&&  io.dwTickCnt_recv_first  
		&&  dwTickCnt  -  io.dwTickCnt_recv_first  >  3000  )  
	{
		p->status.recv.ucCnt_timeout  ++  ;
		}
	else  
		 p->status.recv.ucCnt_timeout  =  0;

	if  (  io.ucbReceiveing  &&  p->status.recv.ucCnt_timeout  >=  2  )  {
		qyShowInfo(  CONST_qyShowType_qwmComm,  0,  pSession->comm.clientIp,  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  ""  ),  _T(  "recv timeout, %dms, index %d, %I64u"  ),  dwTickCnt  -  io.dwTickCnt_recv_first,  i,  pSession->debugInfo.idInfo.ui64Id  ); 
		postMsg2Iocp(  pMtSock,  CONST_misMsgType_closeChannel,  i,  0,  CONST_commFlg_resp,  0,  0,  0,  0,  0,  0,  0,  NULL  );
		iErr  =  0;  goto  errLabel;
	}

	if  (  io.ucbSending  
		&&  io.dwTickCnt_snd_start
		&&  dwTickCnt  -  io.dwTickCnt_snd_start  >  3000  )
	{
		p->status.snd.ucCnt_timeout  ++  ;
		}
	else
		p->status.snd.ucCnt_timeout  =  0;

	if  (  io.ucbSending  &&  p->status.snd.ucCnt_timeout  >=  2  )  {
		qyShowInfo(  CONST_qyShowType_qwmComm,  0,  pSession->comm.clientIp,  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  ""  ),  _T(  "snd timeout, %dms, index %d, %I64u"  ),  dwTickCnt  -  io.dwTickCnt_snd_start,  i,  pSession->debugInfo.idInfo.ui64Id  ); 
		postMsg2Iocp(  pMtSock,  CONST_misMsgType_closeChannel,  i,  0,  CONST_commFlg_resp,  0,  0,  0,  0,  0,  0,  0,  NULL  );
	}
	iErr  =  0;
errLabel:
	return  iErr;

}


  int  getNetStat_isMgr(  QY_ENV  *	pEnv,  CQyMcDaemon  *  pDaemon,  unsigned  int  nIntervalInMs  )
{
	int				iErr	=	-1;
	int					iServiceId	=  pDaemon->var.iServiceId;
	QY_SERVICE_INFO	*	pServiceInfo							=		(  QY_SERVICE_INFO  *  )pDaemon->getSpecialProperty(  CONST_qyPropertyId_serviceInfo_byServiceId,  (  void  *  )iServiceId,  0  );
	if  (  !pServiceInfo  ||  !pServiceInfo->pObjQ  ||  !pServiceInfo->ucbVarInited  )  return  -1;
	QMD_VAR_MIS			*	pProcInfo			=		(  QMD_VAR_MIS  *  )pServiceInfo->pVar;
	if  (  !pProcInfo  )  return  -1;
	MT_SOCK_IOCP				*	pMtSock									=		(  MT_SOCK_IOCP  *  )pServiceInfo->pMtSock;
	if  (  !pMtSock  )  return  -1;

	NET_STATS_total	t;
	IM_NET_STAT		tmpNetStat;
	int				i;
	__int64			i64InOctets;
	__int64			i64OutOctets;

	if  (  !nIntervalInMs  )  return  -1;

	memset(  &t,  0,  sizeof(  t  )  );

	for  (  i  =  0;  i  <  pMtSock->servWork.usMaxConns;  i  ++  )  {
		 MT_SOCK_CLIINFO_IOCP	*	pCliInfo	=	&pMtSock->cliInfos[i];
		 PER_SOCKET_CONTEXT		*  p			=  (  PER_SOCKET_CONTEXT  *  )pMtSock->pPerSocketContexts[i];
		 QMD_SESSION			*  pSession		=  (  QMD_SESSION  *  )pMtSock->pSessions[i];

		 memcpy(  &tmpNetStat,  &p->status.netStat,  sizeof(  tmpNetStat  )  );
		 //
		 i64InOctets  =  tmpNetStat.ui64MsgDataLenRecvd  -  p->status.oldNetStat.ui64MsgDataLenRecvd;
		 i64OutOctets  =  tmpNetStat.ui64MsgDataLenSent  -  p->status.oldNetStat.ui64MsgDataLenSent;
		 if  (  i64InOctets  <  0  ||  i64OutOctets  <  0  )  {
			 memcpy(  &p->status.oldNetStat,  &tmpNetStat,  sizeof(  p->status.oldNetStat  )  );
			 goto  errLabel;
		 }

		 p->status.netStat.uiInSpeedInKbps  =  i64InOctets  *  8.  /  nIntervalInMs;
		 p->status.netStat.uiOutSpeedInKbps  =  i64OutOctets  *  8.  /  nIntervalInMs;
		 //
		 memcpy(  &p->status.oldNetStat,  &tmpNetStat,  sizeof(  p->status.oldNetStat  )  );

		 #ifdef  __DEBUG__
			#if  0
				 traceLog(  _T(  "channel[%d].io %dkbps, %dkbps, %I64u, %s"  ),  i,
					 p->status.netStat.uiInSpeedInKbps,  
					 p->status.netStat.uiInSpeedInKbps,  
					 pSession->debugInfo.idInfo.ui64Id,
					 qyGetDesByType1(  CONST_channelTypeTable,  pSession->uiChannelType  )  );		
			#endif
		 #endif


		 switch  (  pSession->uiChannelType  )  {
				 case  CONST_channelType_realTimeMedia:
					   t.netStat_a.ui64MsgDataLenRecvd  +=  i64InOctets;
					   t.netStat_a.ui64MsgDataLenSent  +=  i64OutOctets;					   
					   break;
				 case  CONST_channelType_media:
					   t.netStat_v.ui64MsgDataLenRecvd  +=  i64InOctets;
					   t.netStat_v.ui64MsgDataLenSent  +=  i64OutOctets;					   
					   break;
				 case  CONST_channelType_robot:
					   t.netStat_f.ui64MsgDataLenRecvd  +=  i64InOctets;
					   t.netStat_f.ui64MsgDataLenSent  +=  i64OutOctets;
					   break;
				 default:
					     t.netStat_others.ui64MsgDataLenRecvd  +=  i64InOctets;
						 t.netStat_others.ui64MsgDataLenSent  +=  i64OutOctets;
						 break;
		 }

		 //  2011/01/29
		 if  (  !pCliInfo->bUsed  )  continue;

		 qmd_chkChannelTimeout(  pEnv,  pMtSock,  i,  pCliInfo,  p,  pSession  );
		 
	}

	//  
	memcpy(  &tmpNetStat,  &pMtSock->status.netStat_admin,  sizeof(  tmpNetStat  )  );

	i64InOctets		=	tmpNetStat.ui64MsgDataLenRecvd  -  pMtSock->status.oldNetStat_admin.ui64MsgDataLenRecvd;
	i64OutOctets	=	tmpNetStat.ui64MsgDataLenSent  -  pMtSock->status.oldNetStat_admin.ui64MsgDataLenSent;
	if  (  i64InOctets  <  0  ||  i64OutOctets  <  0  )  {
		memcpy(  &pMtSock->status.oldNetStat_admin,  &tmpNetStat,  sizeof(  pMtSock->status.oldNetStat_admin  )  );
		goto  errLabel;
	}
	pMtSock->status.netStat_admin.uiInSpeedInKbps  =  i64InOctets  *  8.  /  nIntervalInMs;
	pMtSock->status.netStat_admin.uiOutSpeedInKbps  =  i64OutOctets  *  8.  /  nIntervalInMs;
	//
	memcpy(  &pMtSock->status.oldNetStat_admin,  &tmpNetStat,  sizeof(  pMtSock->status.oldNetStat_admin  )  );
	//
	t.netStat_admin.ui64MsgDataLenRecvd  +=  i64InOctets;
	t.netStat_admin.ui64MsgDataLenSent  +=  i64OutOctets;
	//

#define	MACRO_getNetStat(  netStat,  netStat_add,  nIntervalInMs  )	{	\
			netStat.uiInSpeedInKbps  =  netStat_add.ui64MsgDataLenRecvd  *  8.  /  nIntervalInMs;	\
			netStat.uiOutSpeedInKbps  =  netStat_add.ui64MsgDataLenSent  *  8.  /  nIntervalInMs;	\
			netStat.ui64MsgDataLenRecvd  +=  netStat_add.ui64MsgDataLenRecvd;						\
			netStat.ui64MsgDataLenSent  +=  netStat_add.ui64MsgDataLenSent;  }

	MACRO_getNetStat(  pProcInfo->status.netStats.netStat_a,  t.netStat_a,  nIntervalInMs  );
	MACRO_getNetStat(  pProcInfo->status.netStats.netStat_v,  t.netStat_v,  nIntervalInMs  );
	MACRO_getNetStat(  pProcInfo->status.netStats.netStat_f,  t.netStat_f,  nIntervalInMs  );
	MACRO_getNetStat(  pProcInfo->status.netStats.netStat_others,  t.netStat_others,  nIntervalInMs  );
	MACRO_getNetStat(  pProcInfo->status.netStats.netStat_admin,  t.netStat_admin,  nIntervalInMs  );

	//
#if  0
	traceLog(  _T(  "a.io %dkbps, %dkbps, %I64u, %I64u"  ),  pProcInfo->status.netStats.netStat_a.uiInSpeedInKbps,  pProcInfo->status.netStats.netStat_a.uiOutSpeedInKbps,
		pProcInfo->status.netStats.netStat_a.ui64MsgDataLenRecvd,  pProcInfo->status.netStats.netStat_a.ui64MsgDataLenSent  );

	traceLog(  _T(  "v.io %dkbps, %dkbps, %I64u, %I64u"  ),  pProcInfo->status.netStats.netStat_v.uiInSpeedInKbps,  pProcInfo->status.netStats.netStat_v.uiOutSpeedInKbps,
		pProcInfo->status.netStats.netStat_v.ui64MsgDataLenRecvd,  pProcInfo->status.netStats.netStat_v.ui64MsgDataLenSent  );

	traceLog(  _T(  "r.io %dkbps, %dkbps, %I64u, %I64u"  ),  pProcInfo->status.netStats.netStat_f.uiInSpeedInKbps,  pProcInfo->status.netStats.netStat_f.uiOutSpeedInKbps,
		pProcInfo->status.netStats.netStat_f.ui64MsgDataLenRecvd,  pProcInfo->status.netStats.netStat_f.ui64MsgDataLenSent  );

	traceLog(  _T(  "others.io %dkbps, %dkbps, %I64u, %I64u"  ),  pProcInfo->status.netStats.netStat_others.uiInSpeedInKbps,  pProcInfo->status.netStats.netStat_others.uiOutSpeedInKbps,
		pProcInfo->status.netStats.netStat_others.ui64MsgDataLenRecvd,  pProcInfo->status.netStats.netStat_others.ui64MsgDataLenSent  );

	traceLog(  _T(  "admin.io %dkbps, %dkbps, %I64u, %I64u"  ),  pProcInfo->status.netStats.netStat_admin.uiInSpeedInKbps,  pProcInfo->status.netStats.netStat_admin.uiOutSpeedInKbps,
		pProcInfo->status.netStats.netStat_admin.ui64MsgDataLenRecvd,  pProcInfo->status.netStats.netStat_admin.ui64MsgDataLenSent  );
#endif

	iErr  =  0;
errLabel:
	return  iErr;
}


 // 处理库中的数据
 extern  "C"  DWORD  WINAPI  qmdProcessingThreadProc( LPVOID lpParameter )
{
	int					iErr			=		-1;
	CQyMcDaemon		*	pDaemon			=		(  CQyMcDaemon  *  )lpParameter;
	int					iServiceId		=		pDaemon->var.iServiceId;
	QY_SERVICE_CFG	*	pServiceCfg		=		(  QY_SERVICE_CFG  *  )pDaemon->getSpecialProperty(  CONST_qyPropertyId_serviceCfg,  (  void  *  )iServiceId,  0  );
	if  (  !pServiceCfg  )  return  -1;
	QY_SERVICE_INFO	*	pServiceInfo							=		(  QY_SERVICE_INFO  *  )pDaemon->getSpecialProperty(  CONST_qyPropertyId_serviceInfo_byServiceId,  (  void  *  )iServiceId,  0  );
	//
	CDatabase			tmpDb;
	MT_SUBTHREADINFO	tmpThreadInfo;
	int					loopCnt			=		0;
	
	traceLogA(  "qmdProcessingThreadProc ..  enters."  );

	TRY  {
		if  (  !tmpDb.OpenEx(  pServiceCfg->db.connectStr,  CONST_qyDbOpenOptions  )  )  {
			traceLogA(  "localDb.OpenEx( %s ) failed.",  pServiceCfg->db.connectStr  );
			goto errLabel;
		}
		}
	CATCH  (  CDBException,  e  )  {		
		debugLog( "localDb.Open( ) failed: [%s]", e->m_strError );
		goto errLabel;
	}
	END_CATCH
		
	memset(  &tmpThreadInfo,  0,  sizeof(  tmpThreadInfo  )  );
	tmpThreadInfo.pParentParam	=  (  void  *  )pDaemon;
	tmpThreadInfo.pDb			=  &tmpDb;
	
	//  作某些决策，有些应传入处理函数。
	for  (  ;  ;  loopCnt  ++  )  {

		 if  (  pDaemon->bQuit(  )  )  break;
		 if  (  pDaemon->bStop(  )  )  {
			 Sleep(  pDaemon->var.cfg.nQueryStopInterval  );
			 continue;
		 }

#ifndef  __DEBUG__
//  #error	"not finished. 这里什么也没有。"
#endif
		 

		 if  (  pDaemon->var.iServiceId  ==  CONST_qyServiceId_netMc  )  {

			 if  (  !(  loopCnt  %  pDaemon->var.cfg.nProcessQmObjQIntervalLoops_netMc  )  ||  pDaemon->var.status.ucbNeedRefreshQmObjQInfo  )  {
				 traceLogA(  "processQmObjQ, loopCnt is %d",  loopCnt  );
				 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  ""/*刷新管理队列策略信息开始*/  ),  _T(  "Begin to refresh management queue policy"  )  ); 
				 refreshQmObjQInfo_netMc(  &tmpThreadInfo  );	pDaemon->var.status.ucbNeedRefreshQmObjQInfo  =  FALSE;
				 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  ""/*刷新管理队列策略信息结束*/  ),  _T(  "End to refresh management queue policy"  )  ); 
			 }

			 if  (  !(  loopCnt  %  pDaemon->var.cfg.nRefreshQmObjQStatusInDbLoops_netMc  )  )  {
				 traceLogA(  "刷新所有节点的最近联系时间"  );
				 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  ""/*刷新各节点最近联系时间开始*/  ),  _T(  "Begin to refresh the latest contacting time"  )  ); 
				 refreshQmObjQLastCommTime_netMc(  &tmpThreadInfo  );
				 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  ""/*刷新各节点最近联系时间结束*/  ),  _T(  "End to refresh the latest contacting time"  )  ); 
			 }

		 }

		 if  (  pDaemon->var.iServiceId  ==  CONST_qyServiceId_is  )  {
			 QMD_VAR_MIS			*	pProcInfo			=		(  QMD_VAR_MIS  *  )pServiceInfo->pVar;
			 if  (  !pProcInfo  )  goto  errLabel;


			 //  这里先借用netMc里值，实际应该是自己有一个独立的设置过程，2007/08/04
			 pDaemon->var.cfg.nRefreshQmObjQStatusInDbLoops_is  =  pDaemon->var.cfg.nRefreshQmObjQStatusInDbLoops_netMc;
			 
			 if  (  !(  loopCnt  %  pDaemon->var.cfg.nRefreshQmObjQStatusInDbLoops_is  )  )  {	//  
				 traceLog(  _T(  "refreshQmObjQStatusInDb_is"  )  );
				 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "Server"  ),  0,  _T(  ""  ),  _T(  ""/*刷新各节点状态信息开始*/  ),  _T(  "Begin to refresh all nodes status"  )  ); 
				 refreshQmObjQStatusInDb_is(  &tmpThreadInfo  );
				 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "Server"  ),  0,  _T(  ""  ),  _T(  ""/*刷新各节点状态信息结束*/  ),  _T(  "End to refresh all nodes status"  )  ); 
			 }

			 if  (  !(  loopCnt  %  5  )  )  {		//  读取临时处理任务。比方：刷新一下某个imGrp的组成员

				 processScheduler_is(  &tmpThreadInfo  );

			 }

			 if  (  !(  loopCnt  %  pDaemon->var.cfg.nGetDaemonStatusLoops_is  )  )  {
				 DWORD	dwCurTickCnt	=	GetTickCount(  );

				 getNetStat_isMgr(  &pDaemon->var.env,  pDaemon,  dwCurTickCnt  -  pProcInfo->status.dwTickCnt_toStat  );

				 pProcInfo->status.dwTickCnt_toStat  =  dwCurTickCnt;
			 }

			 //  2011/02/05
			 int	nMemoryStatusLoops  =  30;
			 int	MAX_dwMemoryLoad	=	90;
			 #ifdef  __DEBUG__
					 #if  0
							nMemoryStatusLoops  =  1;
							MAX_dwMemoryLoad  =  50;
					 #endif
			 #endif
			 if  (  !(  loopCnt  %  nMemoryStatusLoops  )  )  {
				 pProcInfo->status.memory.memoryStatusEx.dwLength  =  sizeof(  pProcInfo->status.memory.memoryStatusEx  );
				 GlobalMemoryStatusEx(  &pProcInfo->status.memory.memoryStatusEx  );
				 #ifdef  __DEBUG__
						 //  traceLog(  _T(  "%d"  ),  pProcInfo->status.memory.dwMemoryLoad  );
				 #endif
				 if  (  pProcInfo->status.memory.memoryStatusEx.dwMemoryLoad  >  MAX_dwMemoryLoad  )  pProcInfo->status.memory.ucCnt_err  ++  ;
				 else  pProcInfo->status.memory.ucCnt_err  =  0;
				 //
				 if  (  pProcInfo->status.memory.ucCnt_err  >  3  )  {
					 QIS_EVENT	e;
					 memset(  &e,  0,  sizeof(  e  )  );
					 e.lEventType  =  CONST_qyEventType_im_memoryErr;
					 _sntprintf(  e.deses[0],  mycountof(  e.deses[0]  ),  _T(  "memoryLoad is %d, daemon need restart"  ),  pProcInfo->status.memory.memoryStatusEx.dwMemoryLoad  );
					 getCurTime(  e.localEventTime  );
					 getCurTime(  e.cntEventTime  );
					 //
					 //  if  (  postEvent2Log_is(  pProcInfo->cfg.misServName,  CONST_qyEventType_im_memoryErr,  "",  "",  NULL,  &e,  &pDaemon->var.logQ  )  )  traceLogA(  "postEvent2Log_is failed."  );
					 logEvent_is(  tmpThreadInfo.pDb,  pServiceInfo->cfg.db.iDbType,  NULL,  &e  );							  
					 //
					 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "Server"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "memoryLoad is %d, daemon need restart"  ),  pProcInfo->status.memory.memoryStatusEx.dwMemoryLoad  ); 
					 goto  errLabel;
				 }
			 }

		 }
		 
				 
		 Sleep(  pDaemon->var.cfg.nProcessingInterval  );		 
		 continue;

	}

	iErr  =  0;

errLabel:	

	if ( tmpDb.IsOpen(  )  ) tmpDb.Close(  );

	if  (  !pDaemon->bQuit(  )  )  {
		pDaemon->notifyPanic(  );
		debugLog(  "qmdProcessingThreadProc(  ):  notifyPanic."  );
	}

	traceLogA(  "qmdProcessingThreadProc ..  leaves."  );

	return  iErr;


}



/*

*/



 //  qyCfgWarnThreadProc ..  提供对告警的处理，告警条件为：
 //							1、bWarnOn标志位打开
 //							&&
 //							2、bNew标志位为'1'
 //							&&
 //							3、( 持续告警标志位打开直到用户使用界面
 //							|| 告警时间已过 )
 DWORD  WINAPI  qmdWarnThreadProc(  LPVOID  lpParameter  )
{

	CQyMcDaemon		*	pDaemon			=		(  CQyMcDaemon  *  )lpParameter;

	char		timeBuf[CONST_qyTimeLen  +  1];
	char		curTimeBuf[CONST_qyTimeLen  +  1];
	CTime		eventT,  curT;
	CTimeSpan	tDiff;
	BOOL		bNew	=	FALSE;
	
	while  (  !pDaemon->bQuit(  )  )  {

		   //  2006/06/03


		   if  (  pDaemon->var.cfg.warn.bWarnOn  
			   &&  !getQnmWarnInfo(  NULL,  timeBuf,  sizeof(  timeBuf  ),  &bNew  )  
				   &&  bNew  )  
		   {
			   
			   if  (  !pDaemon->var.cfg.warn.bWarnUntilUsrStopIt  )  {
				   getCurTime(  curTimeBuf  );
			   	   eventT  =  getCTimeByQyTime(  timeBuf  );
			   	   curT  =  getCTimeByQyTime(  curTimeBuf  );
				   tDiff  =  curT  -  eventT;
				   traceLogA(  "tDiff is %d seconds",   tDiff.GetTotalSeconds(  )  );
				   if  (  curT  <  eventT  
					   ||  (  tDiff.GetTotalSeconds(  )  *  1000  )  >  (  int  )pDaemon->var.cfg.warn.nMaxWarnElapse  )
				   {
					   clearQnmWarnFlg(  NULL  );
					   bNew  =  FALSE;
				   }				   
			   }

			   DWORD	dwTickCnt	=	GetTickCount(  );
			   if  (  bNew  )  {
				   DWORD		actSessionId	=	-1;
				   TCHAR	*	title			=	_T(  "Qycx"  );
				   TCHAR	*	hint			=	_T(  "Warning"  );
				   int			titleLen		=	lstrlen(  title  )  *  sizeof(   TCHAR  );
				   int			msgLen			=	lstrlen(  hint  )  *  sizeof(  TCHAR  );
				   DWORD		iResp;

				   if  (  !getWtsSessionId(  &pDaemon->var.env,  0,  &actSessionId  )  )  {
					   myWTSSendMessage(  &pDaemon->var.env,  0,  actSessionId,  title,  titleLen,  hint,  msgLen,  MB_OK  |  MB_TOPMOST,  1,  &iResp,  TRUE  );
				   }
				   
				   MessageBeep(  MB_OK  );
			   }
						   
			   dwTickCnt  =  GetTickCount(  )  -  dwTickCnt;
			   if  (  dwTickCnt  <  1000  )  {
				   Sleep(  1000  -  dwTickCnt  );
			   }
			   continue;

		   }

		   Sleep(  3500  );		   

	}
  
	return  0;
}





