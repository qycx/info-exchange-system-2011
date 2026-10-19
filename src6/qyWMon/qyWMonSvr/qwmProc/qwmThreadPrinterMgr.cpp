

#include	<windows.h>            // required for all Windows applications
#include	<windowsx.h>

#include	<stdlib.h>
#include	<ras.h>
#include	<raserror.h>
#include	<lm.h>
#include	<iphlpapi.h>
#include	<tchar.h>
#include	"asrWMon.h"
#include	"config.h"
#include	"main.h"




#ifdef  __DEBUG__  //  {
 int  printPrinterNotifyInfo(  DWORD  ChangeReason,  PRINTER_NOTIFY_INFO  *  p  );
#endif  //  }
//
int  procPrinterNotifyInfo(  QWM_THREADINFO  *  pThreadInfo,  TCHAR  *  printerName,  DWORD  ChangeReason,  PRINTER_NOTIFY_INFO  *  p  );
int  watchPrinters(  QWM_THREADINFO  *  pThreadInfo  );


 int  sndPrintersInfo(  QWM_THREADINFO  *  pThreadInfo,  QWM_PRINTERMGR_PROCINFO  *  pProcInfo  )
{
	 int				iErr			=	-1;
	 QY_W_MON		*	pQwm			=	(  QY_W_MON  *  )pThreadInfo->pParaentParam;
	 QWM_SESSION		session;
	 BOOL				bSessionOpen	=	FALSE;
	 QY_SOCK			sock;
	 int				i;
	 QY_COMM_RESP		tmpResp;
	 QY_PC_COMMU		pcCommU;
	 int				len;
	 char				buf[4096];

	 memset(  &session,  0,  sizeof(  session  )  );
	 clearQySock(  &sock  );

	 if  (  qwmOpenSession(  pThreadInfo->pParaentParam,  &session,  &sock  )  )  goto  errLabel;
	 bSessionOpen  =  TRUE;

	 memset(  &pcCommU,  0,  sizeof(  pcCommU  )  );
	 MACRO_makePcCommHead(  CONST_pcCommType_printers,  pQwm,  pcCommU  );
	 for  (  i  =  0;  i  <  (  int  )pProcInfo->nPrinters;  i  ++  )  {
		  myTChar2Str(  pProcInfo->printers[i].name,  pcCommU.printers.mems[i].name,  mycountof(  pcCommU.printers.mems[i].name  )  );
		  pcCommU.head.cnt  ++  ;
		  if  (  pcCommU.printers.cnt  ==  sizeof(  pcCommU.printers.mems  )  /  sizeof(  pcCommU.printers.mems[0]  )  )  break;
	 }
	 if  (  (  len  =  qyhtonQyPcCommU(  0,  &pcCommU  )  )  ==  -1  )  goto  errLabel;
	 if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_sndPrinters,  (  char  *  )&pcCommU,  len  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;
	
	 memset(  &pcCommU,  0,  sizeof(  pcCommU  )  );
	 MACRO_makePcCommHead(  CONST_pcCommType_printers,  pQwm,  pcCommU  );
	 pcCommU.head.ucFlg  =  -1;
	 if  (  (  len  =  qyhtonQyPcCommU(  0,  &pcCommU  )  )  ==  -1  )  goto  errLabel;
	 if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_sndPrinters,  (  char  *  )&pcCommU,  len  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;


	 iErr  =  0;
errLabel:
	 
	 if  (  bSessionOpen  )  qwmCloseSession(  pThreadInfo->pParaentParam,  &session,  &sock  );

	 return  0;
}

 int  getPrinters(  QWM_THREADINFO  *  pThreadInfo,  QWM_PRINTERMGR_PROCINFO  *  pProcInfo  )
{
	 int								iErr					=	-1;
	 PPRINTER_INFO_1					pPrinters				=	NULL; 
	 DWORD								nPrinters				=	0;
	 DWORD								cbPrinters;     
	 DWORD								cbNeeded,  cReturned;
	 unsigned  char						ucbPrintersChanged		=	FALSE;
	 int								i,  j;

	 cbPrinters  =  4096L;          
	 if  (  !(  pPrinters  =  (  PPRINTER_INFO_1  )LocalAlloc(  (  LMEM_FIXED  |  LMEM_ZEROINIT  ),  cbPrinters  )  )  )  { 
		 traceLogA(  "InitPrint: LocalAlloc for gpPrinters failed."  );  goto  errLabel;
	 }      
	 if  (  !EnumPrinters(  PRINTER_ENUM_LOCAL  |  PRINTER_ENUM_CONNECTIONS,  NULL,  1,  (  LPBYTE  )pPrinters,  cbPrinters,  &cbNeeded,  &cReturned  )  )     {         
		 if  (  GetLastError(  )  !=  ERROR_INSUFFICIENT_BUFFER  )  goto  errLabel;
		 LocalFree(  (  LOCALHANDLE  )pPrinters  );  pPrinters  =  NULL;              
		 if  (  !(  pPrinters  =  (  PPRINTER_INFO_1  )LocalAlloc(  (  LMEM_FIXED  |  LMEM_ZEROINIT  ),  cbNeeded  )  )  )  goto  errLabel;             
		 cbPrinters  =  cbNeeded;              
		 if  (  !EnumPrinters(  PRINTER_ENUM_LOCAL  |  PRINTER_ENUM_CONNECTIONS,  NULL,  1,  (  LPBYTE  )pPrinters,  cbPrinters,  &cbNeeded,  &cReturned  )  )  goto  errLabel;
	 }
	 nPrinters  =  cReturned;     
		
	 //  这里比较procInfo和实际的信息，看是否变化了
	 if  (  nPrinters  !=  pProcInfo->nPrinters  )  ucbPrintersChanged  =  TRUE;
	 else  {
		   for  (  i  =  0;  i  <  (  int  )nPrinters;  i  ++  )  {
			    for  (  j  =  0;  j  <  (  int  )pProcInfo->nPrinters;  j  ++  )  {
					 if  (  !_tcsnicmp(  pPrinters[i].pName,  pProcInfo->printers[j].name,  lstrlen(  pProcInfo->printers[j].name  )  )  )  break;
				}
				if  (  j  >=  (  int  )pProcInfo->nPrinters  )  {
					ucbPrintersChanged  =  TRUE;  break;
				}
		   }
		
	 }
		  
	 //  如果变化了，则将原来的控制信息先释放，并建立最新的监控
	 if  (  ucbPrintersChanged  )  {
		 traceLogA(  "打印机配置有了变化，将建立最新的监控"  );
				  
		 traceLogA(  "先释放前面的监控"  );
		 pProcInfo->nPrinters  =  0;
				  
		 if  (  nPrinters  >  sizeof(  pProcInfo->printers  )  /  sizeof(  pProcInfo->printers[0]  )  )  {
			 traceLogA(  "打印机太多了，没法监控"  );  goto  errLabel;
		 }

		 traceLogA(  "将打印机配置保存起来"  );
		 for  (  i  =  0;  i  <  (  int  )nPrinters;  i  ++  )  {
			  safeTcsnCpy(  pPrinters[i].pName,  pProcInfo->printers[i].name,  mycountof(  pProcInfo->printers[i].name  )  );
			  tTrim(  pProcInfo->printers[i].name  );
		 }
							
		 pProcInfo->nPrinters  =  nPrinters;
				  
	 }  //  以上处理打印机变化		  
		
	 iErr  =  0;

errLabel:
			
	 if  (  pPrinters  )  {  LocalFree(  (  LOCALHANDLE  )pPrinters  );  pPrinters  =  NULL;  }

	 return  iErr;
}


 DWORD  WINAPI  qwmThreadPrinterMgr(  LPVOID  lpParameter  )
{
	 QWM_THREADINFO						threadInfo;
	 QY_W_MON						*	pQwm					=	(  QY_W_MON  *  )lpParameter;
	 QWM_THREAD_CFG						threadCfg;


	 traceLogA(  "qwmThreadProcPrintMgr enters"  );

	 if  (  !g_bIsWinNT  )  {
		 traceLogA(  "非NT系列的不支持打印监控"  );  goto  errLabel;
	 }

	 memset(  &threadInfo,  0,  sizeof(  threadInfo  )  );
	 memset(  &threadCfg,  0,  sizeof(  threadCfg  )  );
	 threadInfo.pParaentParam  =  lpParameter;
	 threadInfo.pCfg  =  &threadCfg;

	 for  (  ;  !pQwm->bQuit;  Sleep(  2000  )  )  {
		  if  (  pQwm->cfg.pcRules.osAudit.ucWatchPrinterCmd  ==  CONST_devCmd_permitted  )  watchPrinters(  &threadInfo  );
	 }

errLabel:
	 return  0;
}


 int  watchPrinters(  QWM_THREADINFO  *  pThreadInfo  )
{
	 int								iErr					=	-1;
	 QY_W_MON						*	pQwm					=	(  QY_W_MON  *  )pThreadInfo->pParaentParam;
	 QWM_PRINTERMGR_PROCINFO			procInfo;
	 PRINTER_NOTIFY_OPTIONS				no;
	 PRINTER_NOTIFY_OPTIONS_TYPE		not[2];
	 WORD								pnf[100],  jnf[100];
	 char								buf[256]				=	"";
	 int								i;	//  j;
	 HANDLE								hPrinter				=	INVALID_HANDLE_VALUE;
	 HANDLE								hNotify					=	NULL;
	 HANDLE								hNotifies[CONST_maxPrinters];
	 DWORD								nhNotifies				=	0;
	 DWORD								dwRet;
	 DWORD								ChangeReason;
	 PRINTER_NOTIFY_INFO			*	p						=	NULL;
	 int								loopCtrl				=	0;
	 QNM_CMDPARAM_showQwmSvrStatus		statusDetail;
	 unsigned  char						ucbWatchStarted			=	FALSE;
	 unsigned  char						ucbCfgChanged			=	FALSE;

	 memset(  &procInfo,  0,  sizeof(  procInfo  )  );
	 for  (  i  =  0;  i  <  sizeof(  procInfo.printers  )  /  sizeof(  procInfo.printers[0]  );  i  ++  )  {
		  safeTcsnCpy(  pQwm->cfg.printersProcInfo.printers[i].name,  procInfo.printers[i].name,  sizeof(  procInfo.printers[i].name  )  );
	 }
	 procInfo.nPrinters  =  pQwm->cfg.printersProcInfo.nPrinters;
	 if  (  procInfo.nPrinters  >  sizeof(  procInfo.printers  )  /  sizeof(  procInfo.printers[0]  )  )  goto  errLabel;
	 if  (  !procInfo.nPrinters  )  {
		 iErr  =  0;  goto  errLabel;
	 }


	 //  建立监控事件
	 no.Version		=  2;
	 no.Count		=  2;
	 no.pTypes		=  not;
	 
	 i  =  0;
	 pnf[i++] = PRINTER_NOTIFY_FIELD_SERVER_NAME;
	 pnf[i++] = PRINTER_NOTIFY_FIELD_PRINTER_NAME;
	 pnf[i++] = PRINTER_NOTIFY_FIELD_SHARE_NAME;
	 pnf[i++] = PRINTER_NOTIFY_FIELD_PORT_NAME;
	 pnf[i++] = PRINTER_NOTIFY_FIELD_DRIVER_NAME;
	 pnf[i++] = PRINTER_NOTIFY_FIELD_COMMENT;
	 pnf[i++] = PRINTER_NOTIFY_FIELD_LOCATION;
	 pnf[i++] = PRINTER_NOTIFY_FIELD_SEPFILE;
	 pnf[i++] = PRINTER_NOTIFY_FIELD_PRINT_PROCESSOR;
	 pnf[i++] = PRINTER_NOTIFY_FIELD_PARAMETERS;
	 pnf[i++] = PRINTER_NOTIFY_FIELD_DATATYPE;
	 pnf[i++] = PRINTER_NOTIFY_FIELD_ATTRIBUTES;
	 pnf[i++] = PRINTER_NOTIFY_FIELD_PRIORITY;
	 pnf[i++] = PRINTER_NOTIFY_FIELD_DEFAULT_PRIORITY;
	 pnf[i++] = PRINTER_NOTIFY_FIELD_START_TIME;
	 pnf[i++] = PRINTER_NOTIFY_FIELD_UNTIL_TIME;
	 pnf[i++] = PRINTER_NOTIFY_FIELD_STATUS_STRING;
	 pnf[i++] = PRINTER_NOTIFY_FIELD_CJOBS;
	 pnf[i++] = PRINTER_NOTIFY_FIELD_AVERAGE_PPM;
	 pnf[i++] = PRINTER_NOTIFY_FIELD_TOTAL_PAGES;
	 pnf[i++] = PRINTER_NOTIFY_FIELD_PAGES_PRINTED;
	 pnf[i++] = PRINTER_NOTIFY_FIELD_TOTAL_BYTES;
	 pnf[i++] = PRINTER_NOTIFY_FIELD_BYTES_PRINTED;

	 not[0].Type		=	PRINTER_NOTIFY_TYPE;
	 not[0].Count		=	i;
	 not[0].pFields		=	pnf;

	 i  =  0;
	 jnf[i++] = JOB_NOTIFY_FIELD_PRINTER_NAME;
	 jnf[i++] = JOB_NOTIFY_FIELD_MACHINE_NAME;
	 jnf[i++] = JOB_NOTIFY_FIELD_PORT_NAME;
	 jnf[i++] = JOB_NOTIFY_FIELD_USER_NAME;
	 jnf[i++] = JOB_NOTIFY_FIELD_NOTIFY_NAME;
	 jnf[i++] = JOB_NOTIFY_FIELD_DATATYPE;
	 jnf[i++] = JOB_NOTIFY_FIELD_PRINT_PROCESSOR;
	 jnf[i++] = JOB_NOTIFY_FIELD_PARAMETERS;
	 jnf[i++] = JOB_NOTIFY_FIELD_DRIVER_NAME;
	 jnf[i++] = JOB_NOTIFY_FIELD_STATUS_STRING;
	 jnf[i++] = JOB_NOTIFY_FIELD_DOCUMENT;
	 jnf[i++] = JOB_NOTIFY_FIELD_PRIORITY;
	 jnf[i++] = JOB_NOTIFY_FIELD_POSITION;
	 jnf[i++] = JOB_NOTIFY_FIELD_START_TIME;
	 jnf[i++] = JOB_NOTIFY_FIELD_UNTIL_TIME;
	 jnf[i++] = JOB_NOTIFY_FIELD_TIME;
	 jnf[i++] = JOB_NOTIFY_FIELD_TOTAL_PAGES;
	 jnf[i++] = JOB_NOTIFY_FIELD_PAGES_PRINTED;
	 jnf[i++] = JOB_NOTIFY_FIELD_TOTAL_BYTES;
	 jnf[i++] = JOB_NOTIFY_FIELD_BYTES_PRINTED;

	 not[1].Type		=	JOB_NOTIFY_TYPE;
	 not[1].Count		=	i;
	 not[1].pFields		=	jnf;
		

	 traceLogA(  "将打印机配置保存起来"  );
	 for  (  i  =  0;  i  <  (  int  )procInfo.nPrinters;  i  ++  )  {
		  if  (  procInfo.printers[i].name[0]  )  {
			  if  (  OpenPrinter(  procInfo.printers[i].name,  &hPrinter,  NULL  )  )  {
				  hNotify  =  FindFirstPrinterChangeNotification(  hPrinter,  PRINTER_CHANGE_ALL,  0,  &no  );
				  if  (  !isHandleValid(  hNotify  )  )  ClosePrinter(  hPrinter  );  
				  else  {
					    procInfo.printers[i].hPrinter  =  hPrinter;
						procInfo.printers[i].hNotify  =  hNotify;	
												
						traceLogA(  "watchPrinters: 将开始监视%s",  procInfo.printers[i].name  );
						memset(  &statusDetail,  0,  sizeof(  statusDetail  )  );
						myTChar2Utf8(  procInfo.printers[i].name,  statusDetail.progressTxt,  mycountof(  statusDetail.progressTxt  )  );							
						showQwmSvrStatus(  &pQwm->env,  pQwm->server.ip,  pQwm->server.port,  pQwm->iServiceId,  pQwm->ver,  &pQwm->commEncCtx,  &pQwm->cfg.to,  CONST_qwmSvrStatus_watchPrinters,  &statusDetail  );

						ucbWatchStarted  =  TRUE;

				  }
			  }								 
		  }
		
	 }
					  
	 //  建立等待信息源的集合
	 memset(  hNotifies,  0,  sizeof(  hNotifies  )  );
	 nhNotifies  =  0;  
	 for  (  i  =  0;  i  <  (  int  )procInfo.nPrinters;  i  ++  )  {
		  if  (  isHandleValid(  procInfo.printers[i].hNotify  )  )  {
			  hNotifies[nhNotifies]  =  procInfo.printers[i].hNotify;
			  nhNotifies  ++  ;
		  }
	 }
	
	 traceLogA(  "共有%d个信息源",  nhNotifies   );
	 if  (  !nhNotifies  )  goto  errLabel;
		
	 for  (  loopCtrl  =  0;  !pQwm->bQuit;   loopCtrl  ++  )  {

		 if  (  !(  loopCtrl  %  5  )  )  {
			 if  (  pQwm->cfg.pcRules.osAudit.ucWatchPrinterCmd  !=  CONST_devCmd_permitted  )  {
				 traceLogA(  "打印监视被要求终止"  );
				 iErr  =  0;  goto  errLabel;
			 }
			 //  这里比较打印机配置，若不同，则需要重新自动这个产品
			 if  (  pQwm->cfg.printersProcInfo.nPrinters  !=  procInfo.nPrinters  )  ucbCfgChanged  =  TRUE;
			 else  {
				   for  (  i  =  0;  i  <  (  int  )procInfo.nPrinters;  i  ++  )  {
					   if  (  lstrcmpi(  procInfo.printers[i].name,  pQwm->cfg.printersProcInfo.printers[i].name  )  )  {
						   ucbCfgChanged  =  TRUE;  break;
					   }
				   }
			 }
		 	 if  (  ucbCfgChanged  )  {
				 traceLogA(  "打印机被重新配置"  );  
				 iErr  =  0;  goto  errLabel;
			 }			 
		 }

		 dwRet  =   WaitForMultipleObjects(  nhNotifies,  hNotifies,  FALSE,  2000  );
		 if  (  dwRet  ==  WAIT_FAILED  )  {  traceLogA(  "WaitForMutipleObjects failed"  );  goto  errLabel;  }
		 if  (  dwRet  !=  WAIT_TIMEOUT  )  {
			 dwRet  -=  WAIT_OBJECT_0;		//  这里取得消息源的索引
			 if  (  dwRet  <  0  ||  dwRet  >  nhNotifies  )  {
				 traceLogA(  "WaitForMultipleObjects 返回值%d，不是预想值",  dwRet  );  goto  errLabel;
			 }

			 //  找到对应的打印机名
			 for  (  i  =  0;  i  <  (  int  )procInfo.nPrinters;  i  ++  )  {
				 if  (  procInfo.printers[i].hNotify  ==  hNotifies[dwRet]  )  break;
			 }
			 if  (  i  ==  (  int  )procInfo.nPrinters  )  {  traceLogA(  "编程出错，没找到对应的打印机"  );  goto  errLabel;  }

			 no.Flags  =  0;
			 if  (  FindNextPrinterChangeNotification(  hNotifies[dwRet],  &ChangeReason,  (  void  **  )&no,  (  void  **  )&p  )  )  {
				 #ifdef  __DEBUG__  //  {
						 printPrinterNotifyInfo(  ChangeReason,  p  );
				 #endif  //  }

				
				 procPrinterNotifyInfo(  pThreadInfo,  procInfo.printers[i].name,  ChangeReason,  p  );
				
				 if  (  p  &&  !FreePrinterNotifyInfo(  p  )  )  {  traceLogA(  "FreePrinterNotifyInfo failed"  );  goto  errLabel;  }
					  
			 }
		 

		 }
		 
	 }

	
	 

errLabel:

	 for  (  i  =  0;  i  <  (  int  )procInfo.nPrinters;  i  ++  )  {
		  if  (  isHandleValid(  procInfo.printers[i].hNotify  )  )  {  FindClosePrinterChangeNotification(  procInfo.printers[i].hNotify  );  procInfo.printers[i].hNotify  =  NULL;  }
		  if  (  isHandleValid(  procInfo.printers[i].hPrinter  )  )  {  ClosePrinter(  procInfo.printers[i].hPrinter  );  procInfo.printers[i].hPrinter  =  NULL;  }
		  procInfo.printers[i].name[0]  =  0;
	 }		
	 procInfo.nPrinters  =  0;

	 if  (  ucbWatchStarted  )  {
		 memset(  &statusDetail,  0,  sizeof(  statusDetail  )  );
		 myWChar2Utf8(  L"printing ends.",  statusDetail.progressTxt,  sizeof(  statusDetail.progressTxt  )  );			 
		 showQwmSvrStatus(  &pQwm->env,  pQwm->server.ip,  pQwm->server.port,  pQwm->iServiceId,  pQwm->ver,  &pQwm->commEncCtx,  &pQwm->cfg.to,  CONST_qwmSvrStatus_watchPrinters,  &statusDetail  );
	 }


	 traceLogA(  "qwmThreadProcPrintMgr leaves"  );

	 return  0;

}

typedef  struct  __qwmPrinterNotify_t	{
				 //  char					who[32  +  1];
				 TCHAR					who[32  +  1];
				 //  char					realPrinterName[64  +  1];
				 TCHAR					realPrinterName[64  +  1];
				 //  char					printerName[128  +  1];
				 TCHAR					printerName[128  +  1];
				 //  char					docName[255  +  1];
				 TCHAR					docName[255  +  1];				//  2010/11/29
}		 QWM_PRINTER_NOTIFY;

 int  procPrinterNotifyInfo(  QWM_THREADINFO  *  pThreadInfo,  TCHAR  *  printerName,  DWORD  ChangeReason,  PRINTER_NOTIFY_INFO  *  p  )
{
	 int						iErr  =  -1;
	 int						i;
	 char					*	pBuf;
	 DWORD					*	adwData;
	 QWM_PRINTER_NOTIFY			notify;
	 char						comments[2][255  +  1];
	 
	 memset(  &notify,  0,  sizeof(  notify  )  );
	 //
	 safeTcsnCpy(  printerName,  notify.printerName,  mycountof(  notify.printerName  )  );

	 if  (  (  ChangeReason  &  PRINTER_CHANGE_ADD_JOB  )  )  { 
		 traceLogA("打印機追加 ");
		 //
		 if  (  p  )  {
			 for  (  i  =  0;  i  <  (  int  )p->Count;  i  ++  )  {
				  pBuf = (  char  *  )p->aData[i].NotifyData.Data.pBuf;
				  adwData  =  p->aData[i].NotifyData.adwData;
			
				  switch  (  p->aData[i].Type  )  {
						  case  JOB_NOTIFY_TYPE:
							    traceLogA("\t工作通知(no.%d, id:%d)...", i, p->aData[i].Id);
								switch  (  p->aData[i].Field  )  {
										case  JOB_NOTIFY_FIELD_PRINTER_NAME:
											  //  traceLogA(  "打印機名稱：%s\n", pBuf);
											  //  safeStrnCpy(  pBuf,  notify.realPrinterName,  sizeof(  notify.realPrinterName  )  );
											  safeTcsnCpy(  (  TCHAR  *  )pBuf,  notify.realPrinterName,  mycountof(  notify.realPrinterName  )  );
											  break;
										case  JOB_NOTIFY_FIELD_MACHINE_NAME:
											  //  traceLogA(  "工作編製元(原來)機器名稱：%s\n", pBuf);
											  //  safeStrnCpy(  pBuf,  notify.who,  sizeof(  notify.who  )  );
											  safeTcsnCpy(  (  TCHAR  *  )pBuf,  notify.who,  mycountof(  notify.who  )  );
											  break;
										case  JOB_NOTIFY_FIELD_DOCUMENT:
											  //  traceLogA(  "文檔名稱:%s\n", pBuf);
											  //  safeStrnCpy(  pBuf,  notify.docName,  sizeof(  notify.docName  )  );  
											  safeTcsnCpy(  (  TCHAR  *  )pBuf,  notify.docName,  mycountof(  notify.docName  )  );
											  break;								
										default:
												break;
								}
								break;
						  default:
								  break;


				  }
			 }
			 
			 //  这里存条打印日志
			 tTrim(  notify.printerName  );
			 tTrim(  notify.who  );
			 tTrim(  notify.realPrinterName  );
			 tTrim(  notify.docName  );
			 if  (  notify.printerName[0]  &&  notify.who[0]  )  {
				 TCHAR  *  p  =  NULL;
				 TCHAR		tBuf[256]	=	_T(  ""  );

				 memset(  comments,  0,  sizeof(  comments  )  );
				 p  =  notify.who;  if  (  !_tcsnicmp(  p,  _T(  "\\\\"  ),  2  )  )  p  +=  2;
				 //  _snprintf(  comments[0],  sizeof(  comments[0]  ),  "%s %S(%s)",  p,  notify.printerName,  notify.realPrinterName  );
				 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s used %s(%s)"  ),  p,  notify.printerName,  notify.realPrinterName  );
				 myTChar2Utf8(  tBuf,  comments[0],  mycountof(  comments[0]  )  );
				 //  _snprintf(  comments[1],  sizeof(  comments[1]  ),  "%s",  notify.docName  );
				 myTChar2Utf8(  notify.docName,  comments[1],  mycountof(  comments[1]  )  );
				 qwmLogGeneralEvent(  pThreadInfo,  CONST_qyEventType_nm_printerJob,  "",  comments[0],  comments[1],  TRUE  );
			 }

		 }
	 }
	 
	 /*	//  先去掉打印机删除任务的日志
	 if  (  (  ChangeReason & PRINTER_CHANGE_DELETE_JOB  )  )  {
		 memset(  comments,  0,  sizeof(  comments  )  );
		 _snprintf(  comments[0],  sizeof(  comments[0]  ),  "%s上的打印任务被取消",  notify.printerName  );
		 qwmLogGeneralEvent(  pThreadInfo,  CONST_qyEventType_nm_printerJob,  "",  comments[0],  ""  );
	 }
	 */

	 iErr  =  0;
//  errLabel:
	 return  iErr;
}


#ifdef  __DEBUG__  //  {

 int  printPrinterNotifyInfo(  DWORD  ChangeReason,  PRINTER_NOTIFY_INFO  *  p  )
{
	 int		i;
	 char	*	pBuf;
	 DWORD	*	adwData;


	 traceLogA("\n集會發生...\n");
	 traceLogA("\t通知理由: ");

	 if(ChangeReason & PRINTER_CHANGE_ADD_PRINTER) traceLogA("打印機追加 ");
	 if(ChangeReason & PRINTER_CHANGE_SET_PRINTER) traceLogA("打印機的設置變更 " );
	 if(ChangeReason & PRINTER_CHANGE_DELETE_PRINTER) traceLogA("打印機刪除 ");
	 if(ChangeReason & PRINTER_CHANGE_FAILED_CONNECTION_PRINTER) traceLogA("連接失敗 ");
	 if(ChangeReason & PRINTER_CHANGE_ADD_JOB) traceLogA("工作追加 ");
	 if(ChangeReason & PRINTER_CHANGE_SET_JOB) traceLogA("工作設置變更 ");
	 if(ChangeReason & PRINTER_CHANGE_DELETE_JOB) traceLogA("工作刪除 ");
	 if(ChangeReason & PRINTER_CHANGE_WRITE_JOB) traceLogA("工作寫上 ");
	 if(ChangeReason & PRINTER_CHANGE_ADD_FORM) traceLogA("表單追加 ");
	 if(ChangeReason & PRINTER_CHANGE_SET_FORM) traceLogA("表單設置變更 ");
	 if(ChangeReason & PRINTER_CHANGE_DELETE_FORM) traceLogA("表單刪除 ");
	 if(ChangeReason & PRINTER_CHANGE_ADD_PORT) traceLogA("接口追加 ");
	 if(ChangeReason & PRINTER_CHANGE_CONFIGURE_PORT) traceLogA("接口設置變更 ");
	 if(ChangeReason & PRINTER_CHANGE_DELETE_PORT) traceLogA("接口刪除 ");
	 if(ChangeReason & PRINTER_CHANGE_ADD_PRINT_PROCESSOR) traceLogA("打印處理器追加 ");
	 if(ChangeReason & PRINTER_CHANGE_DELETE_PRINT_PROCESSOR) traceLogA("打印處理器刪除 ");
	 if(ChangeReason & PRINTER_CHANGE_ADD_PRINTER_DRIVER) traceLogA("驅動程序追加 ");
	 if(ChangeReason & PRINTER_CHANGE_SET_PRINTER_DRIVER) traceLogA("驅動程序設置變更 ");
	 if(ChangeReason & PRINTER_CHANGE_DELETE_PRINTER_DRIVER) traceLogA("驅動程序刪除 ");
	 if(ChangeReason & PRINTER_CHANGE_TIMEOUT) traceLogA("暫停 ");
	 traceLogA("\n");

	 if  (  p  != NULL  )  {
		 for  (  i  =  0;  i  <  (  int  )p->Count;  i  ++  )  {
			  pBuf = (  char  *  )p->aData[i].NotifyData.Data.pBuf;
			  adwData  =  p->aData[i].NotifyData.adwData;
			
			  switch  (  p->aData[i].Type  )  {
					  case  PRINTER_NOTIFY_TYPE:
					 	    traceLogA("\t打印機通知(no.%d)...", i);
					 	    switch  (  p->aData[i].Field) {
					 			 case PRINTER_NOTIFY_FIELD_SERVER_NAME:
									 traceLogA("先生ba名稱：%s\n", pBuf  ?  pBuf  :  ""  );
									 break;
								 case PRINTER_NOTIFY_FIELD_PRINTER_NAME:
									 traceLogA("打印機名稱：%s\n", pBuf);
									 break; 
								 case PRINTER_NOTIFY_FIELD_SHARE_NAME:
									 traceLogA("共有名稱：%s\n", pBuf);
									 break;
								 case PRINTER_NOTIFY_FIELD_PORT_NAME:
									 traceLogA("接口名稱：%s\n", pBuf);
									 break;
								 case PRINTER_NOTIFY_FIELD_DRIVER_NAME:
									 traceLogA("驅動程序名稱：%s\n", pBuf);
									 break;
								 case PRINTER_NOTIFY_FIELD_COMMENT:
									 traceLogA("打印機的說明：%s\n", pBuf);
									 break;
								 case PRINTER_NOTIFY_FIELD_LOCATION:
									 traceLogA("設置地方:%s\n", pBuf);
									 break;
								 case PRINTER_NOTIFY_FIELD_DEVMODE:
									 // DEVMODE structure
									 break;
								 case PRINTER_NOTIFY_FIELD_SEPFILE:
									 traceLogA("斷句文件名:%s\n", pBuf);
									 break;
					 			 case PRINTER_NOTIFY_FIELD_PRINT_PROCESSOR:
									 traceLogA("打印處理器名稱:%s\n", pBuf);
									 break;
								 case PRINTER_NOTIFY_FIELD_PARAMETERS:
									 traceLogA("打印處理器的參數:%s\n", pBuf);
									 break;
								 case PRINTER_NOTIFY_FIELD_DATATYPE:
									 traceLogA("數據的種類:%s\n", pBuf);
									 break;
								 case PRINTER_NOTIFY_FIELD_SECURITY_DESCRIPTOR:
									 // SECURITY_DESCRIPTOR
									 break;
								 case PRINTER_NOTIFY_FIELD_ATTRIBUTES:
									 traceLogA("打印機的狀態:\n");
									 if(PRINTER_ATTRIBUTE_QUEUED & adwData[0]) traceLogA("\t\t尾白\n");
									 if(PRINTER_ATTRIBUTE_DIRECT & adwData[0]) traceLogA("\t\t打印機直接數據送\n");
									 if(PRINTER_ATTRIBUTE_DEFAULT & adwData[0]) traceLogA("\t\t默認\n");
									 if(PRINTER_ATTRIBUTE_SHARED & adwData[0]) traceLogA("\t\t共有\n");
									 if(PRINTER_ATTRIBUTE_NETWORK & adwData[0]) traceLogA("\t\t網絡\n");
									 if(PRINTER_ATTRIBUTE_HIDDEN & adwData[0]) traceLogA("\t\t藏打印機\n");
									 if(PRINTER_ATTRIBUTE_LOCAL & adwData[0]) traceLogA("\t\t地方的打印機\n");
									 if(PRINTER_ATTRIBUTE_ENABLE_DEVQ & adwData[0]) traceLogA("\t\t不一致文檔保留\n");
									 if(PRINTER_ATTRIBUTE_KEEPPRINTEDJOBS & adwData[0]) traceLogA("\t\t印後面文檔剩\n");
									 if(PRINTER_ATTRIBUTE_DO_COMPLETE_FIRST & adwData[0]) traceLogA("\t\t線軸做了文檔開頭印\n");
									 if(PRINTER_ATTRIBUTE_WORK_OFFLINE & adwData[0]) traceLogA("\t\t離線印\n");
									 if(PRINTER_ATTRIBUTE_ENABLE_BIDI & adwData[0]) traceLogA("\t\tenable BIDI(?)\n");
									 if(PRINTER_ATTRIBUTE_RAW_ONLY & adwData[0]) traceLogA("\t\t直接數據發報喝\n");
									 break;
								 case PRINTER_NOTIFY_FIELD_PRIORITY:
									 traceLogA("現在的優先次：%d\n", adwData[0]);
									 break;
								 case PRINTER_NOTIFY_FIELD_DEFAULT_PRIORITY:
									 traceLogA("默認的優先次:%d\n", adwData[0]);
									 break;
								 case PRINTER_NOTIFY_FIELD_START_TIME:
									 traceLogA("利用可能成為開始時間：%02d:%02d\n", adwData[0]/60, adwData[0]%60);
									 break;
								 case PRINTER_NOTIFY_FIELD_UNTIL_TIME:
									 traceLogA("利用不可能腹足類爐缸時間：%02d:%02d\n", adwData[0]/60, adwData[0]%60);
									 break;
								 case PRINTER_NOTIFY_FIELD_STATUS:
									 if(adwData[0] & PRINTER_STATUS_PAUSED) traceLogA("一時(一點)停 ");
									 if(adwData[0] & PRINTER_STATUS_ERROR) traceLogA("錯誤 ");
									 if(adwData[0] & PRINTER_STATUS_PENDING_DELETION) traceLogA("pending_deletion ");
									 if(adwData[0] & PRINTER_STATUS_PAPER_JAM) traceLogA("紙塞滿 ");
									 if(adwData[0] & PRINTER_STATUS_PAPER_OUT) traceLogA("紙排出 ");
									 if(adwData[0] & PRINTER_STATUS_MANUAL_FEED) traceLogA("manual_feed ");
									 if(adwData[0] & PRINTER_STATUS_PAPER_PROBLEM) traceLogA("紙的問題 ");
									 if(adwData[0] & PRINTER_STATUS_OFFLINE) traceLogA("離線 ");
									 if(adwData[0] & PRINTER_STATUS_IO_ACTIVE) traceLogA("io_active ");
									 if(adwData[0] & PRINTER_STATUS_BUSY) traceLogA("busy ");
									 if(adwData[0] & PRINTER_STATUS_PRINTING) traceLogA("印中央 ");
									 if(adwData[0] & PRINTER_STATUS_OUTPUT_BIN_FULL) traceLogA("output_bin_full ");
									 if(adwData[0] & PRINTER_STATUS_NOT_AVAILABLE) traceLogA("not_available ");
									 if(adwData[0] & PRINTER_STATUS_WAITING) traceLogA("待命中央 ");
									 if(adwData[0] & PRINTER_STATUS_PROCESSING) traceLogA("處理中央 ");
									 if(adwData[0] & PRINTER_STATUS_INITIALIZING) traceLogA("初始化中央 ");
									 if(adwData[0] & PRINTER_STATUS_WARMING_UP) traceLogA("warming_up ");
									 if(adwData[0] & PRINTER_STATUS_TONER_LOW) traceLogA("墨粉少 ");
									 if(adwData[0] & PRINTER_STATUS_NO_TONER) traceLogA("墨粉沒 ");
									 if(adwData[0] & PRINTER_STATUS_PAGE_PUNT) traceLogA("page_punt ");
									 if(adwData[0] & PRINTER_STATUS_USER_INTERVENTION) traceLogA("user_intervention ");
									 if(adwData[0] & PRINTER_STATUS_OUT_OF_MEMORY) traceLogA("out_of_memory ");
									 if(adwData[0] & PRINTER_STATUS_DOOR_OPEN) traceLogA("door_open ");
									 if(adwData[0] & PRINTER_STATUS_SERVER_UNKNOWN) traceLogA("server_unknown ");
									 if(adwData[0] & PRINTER_STATUS_POWER_SAVE) traceLogA("power_save ");
									 break;
								 case PRINTER_NOTIFY_FIELD_STATUS_STRING:
									 traceLogA("狀態：%d\n", pBuf);
								 case PRINTER_NOTIFY_FIELD_CJOBS:
									 traceLogA("尾白滾開布良?稻田工作的數目:%d\n", adwData[0]);
									 break;
								 case PRINTER_NOTIFY_FIELD_AVERAGE_PPM:
									 traceLogA("１頁擊打的平均印時間:%d分\n", adwData[0]);
									 break;
								 case PRINTER_NOTIFY_FIELD_TOTAL_PAGES:
									 traceLogA("總頁數目：%d\n", adwData[0]);
									 break;
								 case PRINTER_NOTIFY_FIELD_PAGES_PRINTED:
									 traceLogA("印頁數目：%d\n", adwData[0]);
									 break;
								 case PRINTER_NOTIFY_FIELD_TOTAL_BYTES:
									 traceLogA("總字節數目：%d\n", adwData[0]);
									 break;
								 case PRINTER_NOTIFY_FIELD_BYTES_PRINTED:
									 traceLogA("印字節數目：%d\n", adwData[0]);
									 break;
							}
							break;
						case JOB_NOTIFY_TYPE:
							traceLogA("\t工作通知(no.%d, id:%d)...", i, p->aData[i].Id);
							switch  (  p->aData[i].Field  )  {
								case  JOB_NOTIFY_FIELD_PRINTER_NAME:
									traceLogA("打印機名稱：%s\n", pBuf);
									break;
								case JOB_NOTIFY_FIELD_MACHINE_NAME:
									traceLogA("工作編製元(原來)機器名稱：%s\n", pBuf);
									break;
								case JOB_NOTIFY_FIELD_PORT_NAME:
									traceLogA("接口：%s\n", pBuf);
									break;
								case JOB_NOTIFY_FIELD_USER_NAME:
									traceLogA("工作編製元(原來)客戶名稱：%s\n", pBuf);
									break;
								case JOB_NOTIFY_FIELD_NOTIFY_NAME:
									traceLogA("通知以前客戶：%s\n", pBuf);
									break;
								case JOB_NOTIFY_FIELD_DATATYPE:
									traceLogA("數據的種類:%s\n", pBuf);
									break;
								case JOB_NOTIFY_FIELD_PRINT_PROCESSOR:
									traceLogA("打印處理器名稱:%s\n", pBuf);
									break;
								case JOB_NOTIFY_FIELD_PARAMETERS:
									traceLogA("打印處理器往的參數:%s\n", pBuf);
									break;
								case JOB_NOTIFY_FIELD_DRIVER_NAME:
									traceLogA("驅動程序名稱:%s\n", pBuf);
									break;
								case JOB_NOTIFY_FIELD_DEVMODE:
									// DEVMODE
									break;
								case JOB_NOTIFY_FIELD_STATUS:
									traceLogA("工作的狀態(flag):");
									if(adwData[0] & JOB_STATUS_PAUSED) traceLogA("一時(一點)停 ");
									if(adwData[0] & JOB_STATUS_ERROR) traceLogA("錯誤 ");
									if(adwData[0] & JOB_STATUS_DELETING) traceLogA("刪除中央 ");
									if(adwData[0] & JOB_STATUS_SPOOLING) traceLogA("線軸中央 ");
									if(adwData[0] & JOB_STATUS_PRINTING) traceLogA("印中央 ");
									if(adwData[0] & JOB_STATUS_OFFLINE) traceLogA("離線 ");
									if(adwData[0] & JOB_STATUS_PAPEROUT) traceLogA("輸出中央 ");
									if(adwData[0] & JOB_STATUS_PRINTED) traceLogA("印終了 ");
									if(adwData[0] & JOB_STATUS_DELETED) traceLogA("刪除終了 ");
									if(adwData[0] & JOB_STATUS_BLOCKED_DEVQ) traceLogA("blocked_dev_queue ");
									if(adwData[0] & JOB_STATUS_USER_INTERVENTION) traceLogA("user_intervention ");
									if(adwData[0] & JOB_STATUS_RESTART) traceLogA("重新啟動 ");
									traceLogA("\n");
									break;
								case JOB_NOTIFY_FIELD_STATUS_STRING:
									traceLogA("工作的狀態(msg):%s\n", pBuf);
									break;
								case JOB_NOTIFY_FIELD_DOCUMENT:
									traceLogA("文檔名稱:%s\n", pBuf);
									break;
								case JOB_NOTIFY_FIELD_PRIORITY:
									traceLogA("優先次:%d\n", adwData[0]);
									break;
								case JOB_NOTIFY_FIELD_POSITION:
									traceLogA("順序:%d\n", adwData[0]);
									break;
								case JOB_NOTIFY_FIELD_SUBMITTED:
									//SYSTEMTIME
									break;
								case JOB_NOTIFY_FIELD_START_TIME:
									traceLogA("印開始時間: %d:%d\n", adwData[0]/60, adwData[0]%60);
									break;
								case JOB_NOTIFY_FIELD_UNTIL_TIME:
									traceLogA("印終了時間: %d:%d\n", adwData[0]/60, adwData[0]%60);
									break;
								case JOB_NOTIFY_FIELD_TIME:
									traceLogA("過去時間: %d: %d\n", adwData[0]/60, adwData[0]%60);
									break;
								case JOB_NOTIFY_FIELD_TOTAL_PAGES:
									traceLogA("印總張數: %d\n", adwData[0]);
									break;
								case JOB_NOTIFY_FIELD_PAGES_PRINTED:
									traceLogA("印張數: %d\n", adwData[0]);
									break;
								case JOB_NOTIFY_FIELD_TOTAL_BYTES:
									traceLogA("總字節數目: %d\n", adwData[0]);
									break;
								case JOB_NOTIFY_FIELD_BYTES_PRINTED:
									traceLogA("印字節數目: %d\n", adwData[0]);
									break;

							}
							
						}
						
		}
					
	}

	return  0;

}

#endif  //  }

