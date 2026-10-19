
#include	<windows.h>            // required for all Windows applications
#include	<windowsx.h>

#include	<stdlib.h>
#include	<ras.h>
#include	<raserror.h>
#include	<lm.h>
#include	<tchar.h>
#include	<iphlpapi.h>
#include	<iphlpapi.h>
#include	<tchar.h>
#include	"asrWMon.h"
//  #include	"osversion.h"
#include	"config.h"
#include	"main.h"
#include	<tchar.h>
#include	"qySyncCommProc.h"

 int	 enumPcNetShares(  QY_ENV  *  pEnv,  PF_commonHandler  pf,  void  *  p0,  void  *  p1  )
{
	 int						iErr				=	-1;
	 PSHARE_INFO_502			BufPtr,  p;
	 BOOL						bBufPtrNeedFree		=	FALSE;
	 NET_API_STATUS				res;
	 LPWSTR						lpszServer			= NULL;
	 DWORD						er=0,tr=0,resume=0, i;
	 QWM_DYN_LIB			*	pDynLib				=	(  QWM_DYN_LIB  *  )pEnv->pDynLibs;

	 
	 if  (  !g_bIsWinNT  )  return  0;
	 if  (  !pDynLib->pLMSNetShareEnum  ||  !pDynLib->pNetApiBufferFree  )  return  -1;

   	 //
   	 // Call the NetShareEnum function; specify level 502.
   	 //
   	 do  {
   		 res  =  pDynLib->pLMSNetShareEnum(  lpszServer,  502,  (  LPBYTE  *  )&BufPtr,  -1,  &er,  &tr,  &resume  );
      	 //
      	 //  If the call succeeds,
      	 //
		 if  (  res  ==  ERROR_SUCCESS  ||  res  ==  ERROR_MORE_DATA  )  {
			 
			 bBufPtrNeedFree	=	TRUE;

			 p  =  BufPtr;

         	 // Loop through the entries,  print retrieved data.
         	 //
         	 for  (  i  =  0;  i  <  er;  i  ++,  p  ++  )  {
				  traceLogA(  "%-20S%-30S%-8u",  p->shi502_netname,  p->shi502_path,  p->shi502_current_uses);
           
				  if  (  pf  )  {
					  int	tmpiRet  =  pf(  p0,  p1,  p  );
					  if  (  tmpiRet  )  {
						  iErr  =  tmpiRet;  goto  errLabel;
					  }
				  }
				  //
         	 }			 
		 
			 pDynLib->pNetApiBufferFree(  BufPtr  );  bBufPtrNeedFree  =  FALSE;
			 }
    	 else 
        	 traceLogA(  "Error: %ld",  res  );

	 }  while  (  res  ==  ERROR_MORE_DATA  ); // end do


	 iErr  =  0;

errLabel:

	 if  (  bBufPtrNeedFree  )  pDynLib->pNetApiBufferFree(  BufPtr  );

	 return  iErr;
}

 int  tmpHandler_showPcNetShare(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int						iErr			=	-1;
	 COMMON_PARAM			*	pCommonParam0	=	(  COMMON_PARAM  *  )p0;
	 COMMON_PARAM			*	pCommonParam1	=	(  COMMON_PARAM  *  )p1;
	 PSHARE_INFO_502			p				=	(  PSHARE_INFO_502  )p2;
	 //
	 QWM_THREADINFO			*	pThreadInfo		=	(  QWM_THREADINFO  *  )pCommonParam0->p0;
	 QWM_SESSION			*	pSession		=	(  QWM_SESSION  *  )pCommonParam0->p1;
	 QY_SOCK				*	pSock			=	(  QY_SOCK  *  )pCommonParam0->p2;
	 QY_PC_COMMU			*	pPcCommU		=	(  QY_PC_COMMU  *  )pCommonParam1->p0;
	 QWM_NETSHARE_STATUS	*	pStatus			=	(  QWM_NETSHARE_STATUS  *  )pCommonParam1->p1;
	 QY_W_MON				*	pQwm			=	(  QY_W_MON  *  )pThreadInfo->pParaentParam;
	 QY_PCNETSHARE_PROP		*	pNetShare;
	 int						len;
	 char						buf[1024]		=	"";
	 QY_COMM_RESP				tmpResp;

	 
	 if  (  pPcCommU->netShares.cnt  >=  mycountof(  pPcCommU->netShares.mems  )  )  goto  errLabel;

	 pNetShare  =  &pPcCommU->netShares.mems[pPcCommU->netShares.cnt];
	 wcsncpy(  pNetShare->shi502_netname,  (  WCHAR  *  )p->shi502_netname,  mycountof(  pNetShare->shi502_netname  )  );
	 wcsncpy(  pNetShare->shi502_path,  (  WCHAR  *  )p->shi502_path,  mycountof(  pNetShare->shi502_path  )  );
	 pNetShare->shi502_type  =  p->shi502_type;
		
	 pPcCommU->netShares.cnt  ++  ;
			
	 if  (  pPcCommU->netShares.cnt  <  mycountof(  pPcCommU->netShares.mems  )  )  {
		 iErr  =  0;  goto  errLabel;
	 }
			
	 //			  	 
	 if  (  (  len  =  qyhtonQyPcCommU(  0,  pPcCommU  )  )  ==  -1  )  goto  errLabel;
	 if  (  qySendReq(  &pSession->comm,  pSock,  &pQwm->cfg.to,  CONST_qyCmd_showPcNetShare,  (  char  *  )pPcCommU,  len  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &pSession->comm,  pSock,  &pQwm->cfg.to,  &tmpResp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;
	 
	 //	
	 memset(  pPcCommU,  0,  sizeof(  pPcCommU[0]  )  );		  
	 MACRO_makePcCommHead(  CONST_pcCommType_netShare,  pQwm,  pPcCommU[0]  );

	 iErr  =  0;
errLabel:

	 return  iErr;
}

 int	 showPcNetShare(  QWM_THREADINFO  *  pThreadInfo  )
{
	 int						iErr				=	-1;
	 QY_W_MON				*	pQwm				=	(  QY_W_MON  *  )pThreadInfo->pParaentParam;
	 QWM_DYN_LIB			*	pDynLib				=	(  QWM_DYN_LIB  *  )pQwm->env.pDynLibs;
	 QY_PC_COMMU				pcCommU;
	 int						len;
	 QWM_SESSION				session;
	 QY_SOCK					sock;
	 BOOL						bSessionOpen		=	FALSE;
	 char						buf[1024]			=	"";
	 QY_COMM_RESP				tmpResp;
	 COMMON_PARAM				commonParam0,  commonParam1;
	 QWM_NETSHARE_STATUS		netShareStatus;

	 
	 if  (  !g_bIsWinNT  )  return  0;
	 if  (  !pDynLib->pLMSNetShareEnum  ||  !pDynLib->pNetApiBufferFree  )  return  -1;

	 CQySyncObj		syncObj;
	 if  (  syncObj.sync(  pQwm->cfg.mutexName_syncNetShare,  pQwm->cfg.ulMilliSeconds_syncNetShare  )  )  goto  errLabel;

	 clearQySock(  &sock  );
	 memset(  &session,  0,  sizeof(  session  )  );

	 if  (  qwmOpenSession(  pQwm,  &session,  &sock  )  )  goto  errLabel;
	 bSessionOpen		=		TRUE;
	 if  (  !isRcOk(  session.comm.usLastRespCode_i  )  )  goto  errLabel;

	 memset(  &pcCommU,  0,  sizeof(  pcCommU  )  );
	 MACRO_makePcCommHead(  CONST_pcCommType_netShare,  pQwm,  pcCommU  );

	 memset(  &netShareStatus,  0,  sizeof(  netShareStatus  )  );
	 MACRO_makeCommonParam3(  pThreadInfo,  &session,  &sock,  commonParam0  );
	 MACRO_makeCommonParam3(  &pcCommU,  &netShareStatus,  0,  commonParam1  );

	 if  (  enumPcNetShares(  &pQwm->env,  tmpHandler_showPcNetShare,  &commonParam0,  &commonParam1  )  )  goto  errLabel;
   	 
	 if  (  pcCommU.netShares.cnt  )  {
		 if  (  (  len  =  qyhtonQyPcCommU(  0,  &pcCommU  )  )  ==  -1  )  goto  errLabel;
		 if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_showPcNetShare,  (  char  *  )&pcCommU,  len  )  )  goto  errLabel;
		 if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;

		 //
		 memset(  &pcCommU,  0,  sizeof(  pcCommU  )  );		  
	 	 MACRO_makePcCommHead(  CONST_pcCommType_netShare,  pQwm,  pcCommU  );
	 }

	 //  发送结束标志	 	 
	 pcCommU.head.ucFlg  =  -1;
	 if  (  (  len  =  qyhtonQyPcCommU(  0,  &pcCommU  )  )  ==  -1  )  goto  errLabel;
	 if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_showPcNetShare,  (  char  *  )&pcCommU,  len  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:

	 
	 if  (  bSessionOpen  )  qwmCloseSession(  pQwm,  &session,  &sock  );

	 return  iErr;
}

 int	 showPcArp(  QWM_THREADINFO  *  pThreadInfo  )
{
	 traceLogA(  "showPcArp 未完成"  );
	 return  0;
}



