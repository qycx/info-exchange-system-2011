
#include	<windows.h>            // required for all Windows applications
#include	<windowsx.h>

#include	<stdlib.h>
#include	<ras.h>
#include	<raserror.h>
#include	<lm.h>
#include	<iphlpapi.h>
#include	"asrWMon.h"
#include	"config.h"
#include	"main.h"

 BOOL  bAutoLogonSupported(  QY_W_MON  *  pQwm  )
{
	BOOL  bRet  =  FALSE;

	if  (  !g_bIsWinNT  )  goto  errLabel;

	switch  (  pQwm->env.iPlatformId  )  {
			case  CONST_qyPlatform_winnt:  goto  errLabel;
			default:
					break;
	}

	bRet  =  TRUE;

errLabel:

	return  bRet;
}

 #define		CONST_qyRootKey_winLogon					"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Winlogon"
	#define		CONST_regValName_AutoAdminLogon				"AutoAdminLogon"
	#define		CONST_regValName_DefaultDomainName			"DefaultDomainName"
	#define		CONST_regValName_DefaultUserName			"DefaultUserName"
	#define		CONST_regValName_DefaultPassword			"DefaultPassword"


#if  0
 int  queryAutoLogon(  QWM_THREADINFO  *  pThreadInfo  )
{
	 int								iErr				=		-1;
	 QY_W_MON						*	pQwm				=		(  QY_W_MON  *  )pThreadInfo->pParaentParam;
	 QY_SOCK							sock;
	 QWM_SESSION						session;
	 BOOL								bSessionOpen		=		FALSE;
	 QY_COMM_RESP						tmpResp;
	 QNM_CMDPARAM_queryAutoLogon		cmdParam;
	 
	 if  (  !bAutoLogonSupported(  pQwm  )  )  goto  errLabel;

	 traceLogA(  "queryAutoLogon enters."  );

	 clearQySock(  &sock  );
	 memset(  &session,  0,  sizeof(  session  )  );

	 if  (  qwmOpenSession(  pQwm,  &session,  &sock  )  )  goto  errLabel;
	 bSessionOpen		=		TRUE;
	 if  (  !isRcOk(  session.comm.usLastRespCode_i  )  )  goto  errLabel;

	 //  qyhtonShowQwmSvrStatus(  &cmdParam  );

	 if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_queryAutoLogon,  0,  0  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  (  char  *  )&cmdParam,  sizeof(  cmdParam  )  )  )  goto  errLabel;
	 MACRO_ntohs(  cmdParam.usAutoLogonInterval  );
	 trim(  cmdParam.domainName  );  trim(  cmdParam.logonName  );  trim(  cmdParam.logonPasswd  );
	 traceLogA(  "需要用域[%s]的用户[%s]来自动登录, %d秒后重起",  cmdParam.domainName,  cmdParam.logonName,  cmdParam.usAutoLogonInterval  );

	 if  (  memcmp(  &pQwm->cfg.queryAutoLogon,  &cmdParam,  sizeof(  pQwm->cfg.queryAutoLogon  )  )  )  memcpy(  &pQwm->cfg.queryAutoLogon,  &cmdParam,  sizeof(  pQwm->cfg.queryAutoLogon  )  );

	 if  (  !cmdParam.logonName[0]  )  {
		 qySetRegCfg(  _T(  CONST_qyRootKey_winLogon  ),	CONST_regValName_AutoAdminLogon,		"0"  );
		 qySetRegCfg(  _T(  CONST_qyRootKey_winLogon  ),	CONST_regValName_DefaultDomainName,		""  );
		 qySetRegCfg(  _T(  CONST_qyRootKey_winLogon  ),	CONST_regValName_DefaultUserName,		""  );
		 qySetRegCfg(  _T(  CONST_qyRootKey_winLogon  ),	CONST_regValName_DefaultPassword,		""  );
	 }

	 iErr  =  0;

errLabel:

	 if  (  bSessionOpen  )  qnmCloseSession(  &session.comm,  &sock,  &pQwm->cfg.to  );

	 traceLogA(  "queryAutoLogon leaves %s",  iErr  ?  "失败"  :  "成功"  );

	 return  iErr;
}
#endif

  int  queryAutoLogon(  QWM_THREADINFO  *  pThreadInfo  )
  {
	  return  -1;
  }

 int  procAutoLogon(  QWM_THREADINFO  *  pThreadInfo  )
 {
	 return  -1;
 }





