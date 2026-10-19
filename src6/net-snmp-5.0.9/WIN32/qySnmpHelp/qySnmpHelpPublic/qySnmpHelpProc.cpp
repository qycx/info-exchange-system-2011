
#include	"stdafx.h"
#include	<winsock2.h>
#include	"qySnmpHelpProcCommon.h"


extern  "C"  void  init_snmp(const char *);
extern  "C"  void  snmp_shutdown(const char *type);
extern  "C"  void  qySnmpWalkInit(  );
extern  "C"  void  qySnmpWalkExit(  );





 int  failures  =  0;

 void  resetAllGlobals(  )
{
	  failures  =  0;

	  numprinted = 0;	//  snmpwalk里的全局变量

}



  	 /*  Examples
	 _snprintf(  oidBuf,  sizeof(  oidBuf  ),  "%s",  "1.3.6.1.2.1.2.1.0"  );
	 qySnmpHelpFunc(  &ctx,  "get",  ip,  oidBuf,  NULL,  NULL  );

	 _snprintf(  oidBuf,  sizeof(  oidBuf  ),  "%s",  "1.3.6.1.2.1.1.4.0"  );
	 _snprintf(  typeBuf,  sizeof(  typeBuf  ),  "%s",  "s"  );
	 _snprintf(  valBuf,  sizeof(  valBuf  ),  "%s",  "ppp"  );
	 qySnmpHelpFunc(  &ctx,  "set",  ip,  oidBuf,  typeBuf,  valBuf  );

	 _snprintf(  oidBuf,  sizeof(  oidBuf  ),  "%s",  "1.3.6.1.2.1.1.4.0"  );
	 qySnmpHelpFunc(  &ctx,  "walk",  ip,  oidBuf,  typeBuf,  valBuf  );
	 */

 int  qySnmpHelpFunc(  QY_SNMP_CTX  *  pCtx,  char  *  method,  char  *  ip,  char  *  oidStr,   int  iCmd,  char  *  typeBuf,  char  *  valBuf,  QY_SNMP_ARG  *  pArgParam  )
{
	 int				iErr		=	-1;
	 int				i			=	0;
	 int				argc		=	0;
	 char				argvArray[CONST_qyMaxArgvs][256];
	 char			*	argv[CONST_qyMaxArgvs]  =  {
												"-v1",
												"-c",
												"public",
												NULL,
	 											};
	 QY_SNMP_ARG	*	pArg		=	NULL;

	 i  =  sizeof(  argv  )  /  sizeof(  argv[0]  );
	 for  (  i  =  0;  i  <  sizeof(  argv  )  /  sizeof(  argv[0]  );  i  ++  )  argv[i]  =  argvArray[i];

	 if  (  pArgParam  )  pArg  =  pArgParam;
	 else  if  (  !strcmpi(  method,  "get"  )  ||  !strcmpi(  method,  "walk"  )  )  pArg  =  &pCtx->curPolicy;
	 else  if  (  !strcmpi(  method,  "set"  )  )  pArg  =  &pCtx->curPolicy;
	 else  goto  errLabel;
	 
	 argc  =  0;
	 _snprintf(  argvArray[argc],  sizeof(  argvArray[argc]  ),  "snmp%s",  method  );  argc  ++  ;
	 if  (  !strcmpi(  method,  "get"  )  ||  !strcmpi(  method,  "walk"  )  )  {
		 _snprintf(  argvArray[argc],  sizeof(  argvArray[argc]  ),  "-%s",  pArg->snmpVer  );  argc  ++  ;
		 _snprintf(  argvArray[argc],  sizeof(  argvArray[argc]  ),  "%s",  "-c"  );  argc  ++  ;
		 _snprintf(  argvArray[argc],  sizeof(  argvArray[argc]  ),  "%s",  pArg->getCommunity  );  argc  ++  ;
		 if  (  pArg->usmName[0]  )  {
			 _snprintf(  argvArray[argc],  sizeof(  argvArray[argc]  ),  "%s",  "-u"  );  argc  ++  ;
			 _snprintf(  argvArray[argc],  sizeof(  argvArray[argc]  ),  "%s",  pArg->usmName  );  argc  ++  ;
		 }

		}
	 else  if  (  !strcmpi(  method,  "set"  )  )  {
				_snprintf(  argvArray[argc],  sizeof(  argvArray[argc]  ),  "-%s",  pArg->snmpVer  );  argc  ++  ;
		 		_snprintf(  argvArray[argc],  sizeof(  argvArray[argc]  ),  "%s",  "-c"  );  argc  ++  ;
	 			_snprintf(  argvArray[argc],  sizeof(  argvArray[argc]  ),  "%s",  pArg->setCommunity  );  argc  ++  ;				
		}
	 else  goto  errLabel; 

	 _snprintf(  argvArray[argc],  sizeof(  argvArray[argc]  ),  "%s",  ip  );  argc  ++  ;
	 _snprintf(  argvArray[argc],  sizeof(  argvArray[argc]  ),  "%s",  oidStr  );  argc  ++  ;

	 if  (  !strcmpi(  method,  "set"  )  )  {
		 _snprintf(  argvArray[argc],  sizeof(  argvArray[argc]  ),  "%s",  typeBuf  );  argc  ++  ;
		 _snprintf(  argvArray[argc],  sizeof(  argvArray[argc]  ),  "%s",  valBuf  );  argc  ++  ;
	 }

	 pCtx->iCmd  =  iCmd;
	 if  (  safeStrCpy(  oidStr,  pCtx->oidBuf,  sizeof(  pCtx->oidBuf  )  )  )  {
		 traceLogA(  "qySnmHelpFunc: ctx中的oidBuf不够大"  );  goto  errLabel;
	 }
	   
	 showArg(  argc,  argv  );

	 if  (  !strcmpi(  method,  "get"  )  )  {
		 if  (  qySnmpGetFunc(  argc,  argv,  pCtx  )  )  goto  errLabel;
		}
	 else  if  (  !strcmpi(  method,  "set"  )  )  {
				if  (  qySnmpSetFunc(  argc,  argv,  pCtx  )  )  goto  errLabel;
				}
	 else  if  (  !strcmpi(  method,  "walk"  )  )  {
				if  (  qySnmpWalkFunc(  argc,  argv,  pCtx  )  )  goto  errLabel;
				if  (  pCtx->pfProcSnmpBuf  &&  pCtx->pfProcSnmpBuf(  NULL,  pCtx  )  )  goto  errLabel;
		}
	 else  goto  errLabel;
		  

	 iErr  =  0;	 
	 
errLabel:

	 resetSnmpBufInfo(  &pCtx->snmpBuf  );
	 setSnmpBufInfo(  &pCtx->snmpBuf,  0  );	//  停止使用snmpBuf

	 return  iErr;
}

 void  usage(  )
{
	 traceLogA(  "Usage: qySnmpHelp.exe"  );
	 traceLogA(  "					-dsnmpScan或者macScan		--  表do snmpScan(  缺省  )或macScan"  );
	 traceLogA(  "					-f							--  表示使命令前台运行"  );
	 traceLogA(  "					-b1或者2					--  1表示开放,2表示阻断，前台运行"  );
	 traceLogA(  "					-c4='ssss'					--  表执行命令: 4, 参数: 'ssss'"  );
	 traceLogA(  "					-p1							--  端口索引: 1"  );
	 traceLogA(  "					-m001122334455				--  处理的MAC:  001122334455"  );
	 traceLogA(  "					-i192.168.103.1				--  处理的IP:  192.168.103.1"  );
	 traceLogA(  ""  );
	 traceLogA(  "					-s1.1.1.1					--  扫描的起始IP: 1.1.1.1"  );
	 traceLogA(  "					-e2.2.2.2					--  扫描的结束IP: 2.2.2.2"  );
	 return;
}




 int  qySnmpHelpProcMain(  )
{	 
	 int						iErr							=	-1;
	 CQySnmpHelpProcDaemon		daemon;
	 BOOL						bInited							=	FALSE;
	 TCHAR						moduleFileName[MAX_PATH  +  1];
	 TCHAR						pathBuf[MAX_PATH  +  1];
	 TCHAR					*	filePart						=	NULL;
	 char					*	pCmdLine						=	NULL;
	 char					*	p								=	NULL;
	 unsigned  char				ucbCmdErr						=	FALSE;
	 unsigned  long				ulStartIp  =  0,  ulEndIp  =  0;
	 //
	 BOOL					bDynLibInited	=	FALSE;
	 void				*	pDynLib			=	NULL;
	 CString				errHintWndCls;
	 BOOL					bShowInfoInited	=	FALSE;

	 
	 setDebugLogFileModuleName(  );
	 setErrHintWndCls(  CONST_qnmStatusToolWndClass  );

	 if  (  initDynLib(  &pDynLib  )  )  goto  errLabel;
	 bDynLibInited  =  TRUE;

	 getQyEnv(  pDynLib,  &daemon.var.env  );
	 //  daemon.var.env.pDynLibs  =  pDynLib;

	 errHintWndCls  =  CONST_qnmStatusToolWndClass;
	 if  (  initShowInfo(  0,  _T(  "syncQ_showInfo_snmpHelp"  ),  errHintWndCls,  NULL  )  )  goto  errLabel;
	 bShowInfoInited  =  TRUE;

	 traceLogA(  ""  );
	 traceLogA(  "Daemon starts..."  );

	 GetModuleFileName(  NULL,  moduleFileName,  mycountof(  moduleFileName  )  );
	 GetFullPathName(  moduleFileName,  mycountof(  pathBuf  ),  pathBuf,  &filePart  );
	 pCmdLine  =  GetCommandLineA(  );
	 traceLogA(  "pCmdLine is %s",  pCmdLine  ?  pCmdLine  :  ""  );

	 daemon.var.cfg.iNmsOp  =  CONST_nmsOp_snmpScan;	//  缺省
	 for  (  p  =  strchr(  pCmdLine,  '-'  );  !ucbCmdErr  &&  p  &&  p[0];  p  =  strchr(  p,  '-'  )  )  {
		  p  ++  ;
		  switch  (  *p  )  {
				  case  'd':  {
					        char  buf[32];  char  *  p1;  TCHAR  tBuf[32];

							buf[0]  =  0;
							if  (  !(  p1  =  strchr(  p  +  1,  ' '  )  )  )  safeStrnCpy(  p  +  1,  buf,  sizeof(  buf  )  );
							else  safeStrnCpy(  p  +  1,  buf,  min(  sizeof(  buf  ),  p1  -  (  p  +  1  )  +  1  )  );
							myUtf82TChar(  buf,  tBuf,  mycountof(  tBuf  )  );
							if  (  (  daemon.var.cfg.iNmsOp  =  qyGetTypeByDes(  CONST_nmsOpTable,  tBuf  )  )  ==  -1  )  {
								ucbCmdErr  =  TRUE;  break;
							}
							}
							break;
				  case  'f':
							daemon.var.cfg.ucbForeground  =  TRUE;
							daemon.var.cfg.ucbQuitIfErr  =  TRUE;		//  2004/06/20, 将此标志位与ucbForground关联
							break;
				  case  'b':
							daemon.var.cfg.iSnmpOpCmd  =  CONST_snmpOpCmd_willAttack;
							daemon.var.cfg.ucbForeground  =  TRUE;  
							daemon.var.cfg.opCmdU.block.ifAdminStatus  =  atol(  p  +  1  );
							break;
				  case  'c':		//  cmd code
						    daemon.var.cfg.iSnmpOpCmd  =  atol(  p  +  1  );
							for  (  p  =  p  +  1;  *p  &&  !qyIsSpace(  *p  );  p  ++  )  if  (  *p  ==  '\''  )  break;
							if  (  *p  ==  '\''  )  {
								char  *  p1  =  daemon.var.cfg.opCmdU.buf;
								p  +=  1;

								for  (  ;  *p  &&  *p  !=  '\''  &&  p1  <  daemon.var.cfg.opCmdU.buf  +  sizeof(  daemon.var.cfg.opCmdU.buf  )  -  1;  p  ++,  p1  ++  )  *p1  =  *p;
								if  (  *p  !=  '\''  )  {  ucbCmdErr  =  TRUE;  break;  }
								*p1  =  0;
							}

							break;
				  case  'p':
							daemon.var.cfg.ifPortIndex  =  atol(  p  +  1  );
							break;
				  case  'm':
					        safeStrnCpy(  p  +  1,  daemon.var.cfg.processedMac,  sizeof(  daemon.var.cfg.processedMac  )  );
							if  (  !bMacValid(  daemon.var.cfg.processedMac  )  )  daemon.var.cfg.processedMac[0]  =  0;
					        break;
				  case  'i':  {					  								
					          char  *  p1  =  daemon.var.cfg.processedIp;
							  p  +=  1;
						
							  for  (  ;  *p  &&  !qyIsSpace(  *p  )  &&  p1  <  daemon.var.cfg.processedIp  +  sizeof(  daemon.var.cfg.processedIp  )  -  1;  p  ++,  p1  ++  )  *p1  =  *p;
							  *p1  =  0;
							}			
					        if  (  !bIpValid(  daemon.var.cfg.processedIp  )  )  daemon.var.cfg.processedIp[0]  =  0;
					        break;
				  case  's':
							ulStartIp  =  inet_addr(  p  +  1  );
							break;
				  case  'e':
							ulEndIp  =  inet_addr(  p  +  1  );
							break;
				  default:
							break;
		  }		  
	 }

	 traceLogA(  "opCode is %d, param is [%s], portIfIndex is %d, processedMac is %s, processedIp is %s",  daemon.var.cfg.iSnmpOpCmd,  daemon.var.cfg.opCmdU.buf,  daemon.var.cfg.ifPortIndex,  daemon.var.cfg.processedMac,  daemon.var.cfg.processedIp  );

	 if  (  ucbCmdErr  )  {
		 usage(  );  goto  errLabel;
	 }

	 if  (  !ulEndIp  )  ulEndIp  =  ulStartIp;
	 if  (  qyntohl(  ulEndIp  )  <  qyntohl(  ulStartIp  )  ||  !ulEndIp  )  {
		 traceLogA(  "结束IP须>=起始IP并且不能为0.0.0.0"  );  goto  errLabel;
	 }
	 if  (  (  p  =  inet_ntoa(  *(  in_addr  *  )&ulStartIp  )  )  )  _snprintf(  daemon.var.cfg.startIp,  sizeof(  daemon.var.cfg.startIp  ),  "%s",  p  );
	 if  (  (  p  =  inet_ntoa(  *(  in_addr  *  )&ulEndIp  )  )  )  _snprintf(  daemon.var.cfg.endIp,  sizeof(  daemon.var.cfg.endIp  ),  "%s",  p  );
	 traceLogA(  "将扫描%s - %s",  daemon.var.cfg.startIp,  daemon.var.cfg.endIp  );
	 
	 if  (  daemon.preInit(  &daemon.var.env,  CONST_qyRootKey_qnmResp  )  )  goto  errLabel;
	 
	 if  (  daemon.var.cfg.ucbForeground  )  {
		 if  (  daemon.getInitialCfg(  )  )  goto  errLabel;
		 if  (  daemon.refreshCfg(  )  )  goto  errLabel;
		 //  if  (  qySnmpHelpThreadProc(  &daemon  )  )  goto  errLabel;
		 if  (  daemon.var.cfg.scanStruct.pfThreadProc  &&  (  (  QY_THREADPROC  )daemon.var.cfg.scanStruct.pfThreadProc  )(  &daemon.var.cfg.scanStruct  )  )  goto  errLabel;
		}
	 else  {
		   if  (  daemon.runAsApp(  )  )  goto  errLabel;
	 }

	 iErr   =  0;

errLabel:

	 if  (  bShowInfoInited  )  exitShowInfo(  0  );

	 if  (  bDynLibInited  )  exitDynLib(  &pDynLib  );

	 traceLogA(  "Daemon ends."  );

	 return  daemon.var.iQuitCode  ?  daemon.var.iQuitCode  :  iErr;

}
  
 
 unsigned  long  WINAPI  qySnmpHelpThreadProc(  void  *  p  )
{
	 int						iErr						=	-1;
	 NMS_SCAN_STRUCT		*	pScanStruct					=	(  NMS_SCAN_STRUCT  *  )p;
	 CQySnmpHelpProcDaemon	*	pDaemon						=	(  CQySnmpHelpProcDaemon  *  )pScanStruct->pParentParam;
	 //  Declare the variables needed
	 #ifdef  _DEBUG
			 CMemoryState		oldMemState,  newMemState,  diffMemState;
	 #endif
	 CDatabase					db;
	 char					*	snmpType					=	NULL;
	 unsigned  char				ucbTcpStarted				=	FALSE;
	 QY_SNMP_CTX				ctx;
	 char						ip[CONST_qyMaxIpLen  +  1]  =	"192.168.103.254";
	 char						oidBuf[256]					=	"";
	 int						nTries						=	1;
	 unsigned  long				ulhStartIp,  ulhEndIp,  ulhIp,  ulIp;
	 char						ipBuf[CONST_qyMaxIpLen  +  1];
	 HANDLE						hMutex						=	NULL;
	 TCHAR						mutexName[32  +  1];
	 int						iRet_doSnmpOpCmd			=	0;

	 memset(  &ctx,  0,  sizeof(  ctx  )  );
	 
	 init_snmp(  snmpType  );
	 if  (  qyTcpStart(  )  )  goto  errLabel;
	 ucbTcpStarted  =  TRUE;

	 qySnmpWalkInit(  );

	 #ifdef  _DEBUG
			 oldMemState.Checkpoint(  );
	 #endif

	 if  (  !bQyOpenDb(  pDaemon->var.cfg.db.connectStr,  &db  )  )  goto  errLabel;
	 ctx.pDb  =  &db;
	 ctx.pParentParam  =  pDaemon;
	 lstrcpynW(  ctx.showWho,  CONST_showWho_snmpScan,  mycountof(  ctx.showWho  )  );

	 ctx.snmpBuf.uiBufSize  =  CONST_snmpBufSize;
	 if  (  !(  ctx.snmpBuf.ptr  =  (  char  *  )malloc(  ctx.snmpBuf.uiBufSize  )  )  )  goto  errLabel;

	 //  设置缺省策略
	 //		注：2005/08/02年修改了缺省策略
	 //  _snprintf(  ctx.defaultPolicy.snmpVer,  sizeof(  ctx.defaultPolicy.snmpVer  ),  "%s",  "v1"  );
	 //  _snprintf(  ctx.defaultPolicy.getCommunity,  sizeof(  ctx.defaultPolicy.getCommunity  ),  "%s",  "public"  );
	 //  _snprintf(  ctx.defaultPolicy.setCommunity,  sizeof(  ctx.defaultPolicy.setCommunity  ),  "%s",  "private"  );
	 if  (  !bGetDefSnmpPolicy(  0,  &pDaemon->var.encCtx,  &ctx.defaultPolicy  )  )  goto  errLabel;    

	 //  
	 ctx.pfOutput  =  qySnmpOutputProc;
	 ctx.pfProcSnmpBuf  =  qyProcSnmpBuf;

	 #ifdef  __DEBUG__
			 testSnmpFunc(  );
	 #endif

	 //  2004/07/11对流量监控，从qySnmpObjTab中寻找须监控的交换机
	 switch  (  pDaemon->var.cfg.iSnmpOpCmd  )  {
			 case  CONST_snmpOpCmd_monFlow:
				   qySnmpMonFlow(  &ctx  );
				   iErr  =  0;  goto  errLabel;
			 case  CONST_snmpOpCmd_monIfFlow:
				   qySnmpMonIfFlow(  &ctx  );
				   iErr  =  0;  goto  errLabel;
			 default:
					break;
	 }


	 //  对扫描监控，从扫描配置里读取扫描范围并遍历
	 ulhStartIp  =  qyntohl(  inet_addr(  pDaemon->var.cfg.startIp  )  );
	 ulhEndIp  =  qyntohl(  inet_addr(  pDaemon->var.cfg.endIp  )  );
	 for  (  ulhIp  =  ulhStartIp;    ulhIp  <=  ulhEndIp;  ulhIp  ++  )  {
		  
		  if  (  !pDaemon->var.cfg.ucbForeground  )  {
		  	  if  (  pDaemon->bQuit(  )  ||  pDaemon->var.cfg.scanStruct.ucbStopScan  )  break;
		  }

		  ulIp  =  qyhtonl(  ulhIp  );
		  if  (  !bulIpValid(  ulIp  )  )  continue;
		  _snprintf(  ipBuf,  sizeof(  ipBuf  ),  "%s",  inet_ntoa(  *(  in_addr  *  )&ulIp  )  );		  

		  getCurTime(  ctx.scanningTime  );							//  取扫描时间

		  traceLogA(  "获取策略"  );
		  if  (  !bGetSnmpObjPolicyBySth(  ctx.pDb,  ipBuf,  &ctx.curPolicy  )  )  memcpy(  &ctx.curPolicy,  &ctx.defaultPolicy,  sizeof(  ctx.curPolicy  )  );
  

		  //  准备同步，这以下的工作必须串行进行
		  _sntprintf(  mutexName,  mycountof(  mutexName  ),  _T(  "syncSnmp%s"  ),  CString(  ipBuf  )  );
		  traceLog(  _T(  "mutexName, %s"  ),  mutexName  );
		  hMutex = CreateMutex(  NULL,  TRUE,  mutexName  );
		  if  (  !hMutex  ||  GetLastError(  )  ==  ERROR_ALREADY_EXISTS  )  {	//  2004/05/03修改，增加了对已存在的mutex的处理			
			  traceLogA(  "CreateMutex failed: %s,  lastError is %d",  (  hMutex  ?  "hMutex is ok"  :  "hMutex is null"  ),  GetLastError(  )  );  //  2004/05/13
			  if  (  hMutex  )  {  traceLogA(  "取消同步"  );  CloseHandle(  hMutex  );  hMutex  =  NULL;  }
			  if  (  pDaemon->var.cfg.ucbQuitIfErr  )  {
				  pDaemon->var.iQuitCode  =  CONST_qyRet_syncConflict;  goto  errLabel; 
			  }
			  continue;			  
		  }

		  //  2004/05/14添加此项以防止扫描进入死循环
		  pDaemon->setStartToScanObjTime(  );
		  
		  switch  (  pDaemon->var.cfg.iSnmpOpCmd  )  {
				  case  CONST_snmpOpCmd_null:
			 	  case  CONST_snmpOpCmd_refresh:
					    break;
				  //  case  CONST_snmpOpCmd_willAttack:				//  2004/07/11将端口阻断合入doSnmpOpCmd里
				  //	    if  (  qySnmpWillBlockSwitchPort(  &ctx,  ipBuf,  pDaemon->var.cfg.ifPortIndex,  pDaemon->var.cfg.opCmdU.block.ifAdminStatus  )  )  goto  errLabel;
				  // 		iErr  =  0;  goto  errLabel;				//  注意：这里已退出，hMutex由errLabe后释放
				  // 		break;
				  default:						
					      pDaemon->var.cfg.ulbNotRefreshPortStatus  =  TRUE;
					      pDaemon->var.cfg.ulbNotRefreshCdp  =  TRUE;
					      pDaemon->var.cfg.ulbNotRefreshInOutOctets  =  TRUE;	//  不刷新流量
						  pDaemon->var.cfg.ulbNotRefreshMac  =  TRUE;			//  不刷新MAC

						  iRet_doSnmpOpCmd  =  doSnmpOpCmd(  &ctx,  ipBuf,  pDaemon->var.cfg.ifPortIndex,  pDaemon->var.cfg.processedMac,  pDaemon->var.cfg.processedIp,  pDaemon->var.cfg.iSnmpOpCmd,  &pDaemon->var.cfg.opCmdU  );
						  if  (  iRet_doSnmpOpCmd  &&  iRet_doSnmpOpCmd  !=  CONST_qyRet_needRefresh  )  {
							  traceLogA(  "doSnmpOpCmd failed, cmd is %d",  pDaemon->var.cfg.iSnmpOpCmd  );  goto  errLabel;
						  }
						  if  (  iRet_doSnmpOpCmd  ==  CONST_qyRet_needRefresh  )  qySnmpScript(  &ctx,  ipBuf  );  
						  iErr  =  0;  goto  errLabel;			   //  注意：这里已退出，hMutex由errLabe后释放
	 					  break;
	 	  }

		  qySnmpScript(  &ctx,  ipBuf  );			//  扫描

		  ReleaseMutex(  hMutex  );  CloseHandle(  hMutex  );  hMutex  =  NULL;			  
		  traceLogA(  "取消同步"  );  

	 }

	 iErr  =  0;

errLabel:

	 traceLogA(  "qySnmpHelpThreadProc ready to leave"  );	//  2004/05/13

	 if  (  hMutex  )  {
		 ReleaseMutex(  hMutex  );  CloseHandle(  hMutex  );  traceLogA(  "取消同步"  );
	 }

	 if  (  ctx.snmpBuf.ptr  )  {  free(  ctx.snmpBuf.ptr  );  memset(  &ctx.snmpBuf,  0,  sizeof(  ctx.snmpBuf  )  );  }

	 #ifdef  _DEBUG
			 newMemState.Checkpoint(  );
    		 if  (  !diffMemState.Difference(  oldMemState,  newMemState  )  )  traceLogA(  "庆幸：没有内存泄露"  );
			 else  {
        		   traceLogA(  "注意：有内存泄露"  );
				   diffMemState.DumpAllObjectsSince();
    		 }
	 #endif

	 qySnmpWalkExit(  );

	 if  (  ucbTcpStarted  )  qyTcpEnd(  );
	 snmp_shutdown(  snmpType  );

	 //  提示工作已完成
	 pDaemon->var.ucbScanFinished  =  TRUE;

	 traceLogA(  "qySnmpHelpThreadProc returns %d",  iErr   );
	 
	 return  iErr;
}



 int  qySnmpMonFlow(  QY_SNMP_CTX  *  pCtx  )
{
	 int						iErr								=		-1;
	 CQySnmpHelpProcDaemon	*	pDaemon								=		(  CQySnmpHelpProcDaemon  *  )pCtx->pParentParam;
	 unsigned  char				ucbFirst							=		TRUE;
	 char						startIp12[12  +  1]					=		"";
	 char						endIp12[12  +  1]					=		"";
	 TCHAR						sqlBuf[CONST_qyMaxSqlBufLen  +  1]	=		_T(  ""  );
	 CDBVariant					varVals[1];
	 char						ip[CONST_qyMaxIpLen  +  1]			=		"";
	 
	 traceLogA(  "qySnmpMonFlow enters"  );

	 if  (  !qyStdToIp12(  pDaemon->var.cfg.startIp,  startIp12  )  )  startIp12[0]  =  0;
	 if  (  !bIpValid(  pDaemon->var.cfg.endIp  )  )  goto  errLabel;
	 qyStdToIp12(  pDaemon->var.cfg.endIp,  endIp12  );

	 for  (  ;  !pDaemon->bQuit(  );  )  {
		  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qySnmpObjTab.ip from qySnmpObjTab"  )  );
		  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s where qySnmpObjTab.ip%s'%s' and qySnmpObjTab.ip<='%s' order by qySnmpObjTab.ip"  ),  sqlBuf,  (  ucbFirst  ?  _T(  ">="  )  :  _T(  ">"  )  ),  CString(  startIp12  ),  CString(  endIp12  )  );
		  ucbFirst  =  FALSE;

		  //  traceLogA(  "sqlbuf is %s",  sqlBuf  );
		  if  (  !bQyGetRcdBySql(  pCtx->pDb,  sqlBuf,  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  break;
		  if  (  varVals[0].m_dwType  !=  DBVT_STRING  )  goto  errLabel;
		  MACRO_CStringTrim(  *varVals[0].m_pstring  );
		  //  safeStrnCpy(  varVals[0].m_pstring->GetBuffer(  0  ),  startIp12,  sizeof(  startIp12  )  );
		  myTChar2Utf8(  varVals[0].m_pstring->GetBuffer(  0  ),  startIp12,  sizeof(  startIp12  )  );
		  qyIp12ToStd(  startIp12,  ip  );

		  if  (  !bIpValid(  ip  )  )  continue;
		  			  
		  getCurTime(  pCtx->scanningTime  );							//  取扫描时间
		  traceLogA(  "获取策略"  );
		  if  (  !bGetSnmpObjPolicyBySth(  pCtx->pDb,  ip,  &pCtx->curPolicy  )  )  memcpy(  &pCtx->curPolicy,  &pCtx->defaultPolicy,  sizeof(  pCtx->curPolicy  )  );

		  traceLogA(  "ip : %s",  ip  );
		  qySnmpMonSwitchFlow(  pCtx,  ip  );
		  

	 }

	 iErr  =  0;
errLabel:
	 traceLogA(  "qySnmpMonFlow leaves"  );
	 return  iErr;
}


 int  qySnmpMonIfFlow(  QY_SNMP_CTX  *  pCtx  )
{
	 int						iErr								=		-1;
	 CQySnmpHelpProcDaemon	*	pDaemon								=	(  CQySnmpHelpProcDaemon  *  )pCtx->pParentParam;
	 char						ip12[12  +  1]						=		"";
	 char						sqlBuf[CONST_qyMaxSqlBufLen  +  1]	=		"";
	 CDBVariant					varVals[1];
	 char						ip[CONST_qyMaxIpLen  +  1]			=		"";
	 
	 traceLogA(  "qySnmpMonIfFlow enters"  );
	 
	 for  (  ;  !pDaemon->bQuit(  );  )  {
	

		 //  CONST_qyKey_qnmsMonIfs

		 
		/*_snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "select min(qySnmpObjTab.ip) from qySnmpObjTab"  );
		  if  (  ip12  )  _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "%s where qySnmpObjTab.ip>'%s'",  sqlBuf,  ip12  );
		  if  (  !bQyGetRcdBySql(  pCtx->pDb,  sqlBuf,  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  break;
		  if  (  varVals[0].m_dwType  !=  DBVT_STRING  )  goto  errLabel;
		  MACRO_CStringTrim(  *varVals[0].m_pstring  );
		  if  (  !strcmpi(  varVals[0].m_pstring->GetBuffer(  0  ),  ip12  )  )  goto  errLabel;
		  safeStrnCpy(  varVals[0].m_pstring->GetBuffer(  0  ),  ip12,  sizeof(  ip12  )  );
		  qyIp12ToStd(  ip12,  ip  );
		  if  (  !bIpValid(  ip  )  )  continue;

		  getCurTime(  pCtx->scanningTime  );							//  取扫描时间

		  traceLogA(  "获取策略"  );
		  if  (  !bGetSnmpObjPolicyBySth(  pCtx->pDb,  ip,  &pCtx->curPolicy  )  )  memcpy(  &pCtx->curPolicy,  &pCtx->defaultPolicy,  sizeof(  pCtx->curPolicy  )  );

		  traceLogA(  "监控%s的流量",  ip  );
		  qySnmpMonSwitchFlow(  pCtx,  ip  );

			*/

	 }
	 

	 iErr  =  0;
//  errLabel:
	 traceLogA(  "qySnmpMonIfFlow leaves"  );
	 return  iErr;
}


#ifdef  __DEBUG__	/*  {  */

 int  testSnmpFunc(  )
{
	 int	iErr  =  -1;

	 char	p[128]	=	"  A2 69 01 EE";

	 traceLogA(  "testSnmpFunc enters."  );

	 /*
	 unsigned  long	ulIp;

	 ulIp  =  convrtHexStr2ulIp(  p  );
	 traceLogA(  "ip is %s",  inet_ntoa(  *(  in_addr  *  )&ulIp  )  );
	 */

	 iErr  =  0;

	 traceLogA(  "testSnmpFunc leaves."  );
	 
	 return  iErr;
}


 int  qySnmpOutputProc_enumDot1dTpFdbPort(  char  *  str,  void  *  p2  );
 int  testSnmpFunc1(  void  *  pCtxParam  )
{
	 QY_SNMP_CTX	*	pCtx	=	(  QY_SNMP_CTX  *  )pCtxParam;
	 //  char  *  str	=	"1.3.6.1.2.1.17.4.3.1.2.0.10.235.17.240.230 = INTEGER: 8";
	 //  char	*	str		=	"1.3.6.1.2.1.17.4.3.1.2.12.224.76.191.86.241 = INTEGER: 5";
	 //  char  *  str	=	"1.3.6.1.2.1.17.4.3.1.2.12.48.48.48.48.48.48.48.48.48.48.48.48 = INTEGER: 170";	//  avaya
	 //  char  *  str	=	"1.3.6.1.2.1.17.4.3.1.2.12.48.48.48.48.48.101.102.100.51.48.54.54 = INTEGER: 172";
	 //  char  *  str  =  "1.3.6.1.2.1.17.4.3.1.2.12.48.48.48.48.56.54.52.56.56.53.52.98 = INTEGER: 219";		//  STRING: "00008648854b"

	 QNM_REG_INFO	regInfo;

	 bGetPcInfoByMacEx(  pCtx->pDb,  "001320a5671e",  TRUE,  CONST_fieldIdTable_en,  NULL,  &regInfo,  0  );  
	 
	 //  safeStrnCpy(  CONST_snmpMib2_dot1dTpFdbPort,  pCtx->oidBuf,  sizeof(  pCtx->oidBuf  )  );
	 //  qySnmpOutputProc_enumDot1dTpFdbPort(  str,  pCtxParam  );

	 return  0;
}

#endif  /*  }  */
 
 


