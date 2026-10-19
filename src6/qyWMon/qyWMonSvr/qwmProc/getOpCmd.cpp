
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


 int  retrieveOpCmd(  QWM_THREADINFO  *  pThreadInfo  )
{
	 int								iErr				=		-1;
	 QY_W_MON						*	pQwm				=		(  QY_W_MON  *  )pThreadInfo->pParaentParam;
	 QY_SOCK							sock;
	 QWM_SESSION						session;
	 BOOL								bSessionOpen		=		FALSE;
	 QY_COMM_RESP						tmpResp;
	 char								buf[1024];
	 QNM_CMDPARAM_getOpCmd				cmdParam;
	 	 
	 traceLogA(  "retrieveOpCmd enters."  );

	 clearQySock(  &sock  );
	 memset(  &session,  0,  sizeof(  session  )  );

	 if  (  qwmOpenSession(  pQwm,  &session,  &sock  )  )  goto  errLabel;
	 bSessionOpen		=		TRUE;
	 if  (  !isRcOk(  session.comm.usLastRespCode_i  )  )  goto  errLabel;

	 //  qyhtonShowQwmSvrStatus(  &cmdParam  );

	 if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_getOpCmd,  0,  0  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  (  char  *  )buf,  sizeof(  buf  )  )  )  goto  errLabel;
	 //
	 memset(  &cmdParam,  0,  sizeof(  cmdParam  )  );
	 memcpy(  &cmdParam,  buf,  min(  sizeof(  cmdParam  ),  sizeof(  buf  )  )  );
	 traceLogA(  "实时操作命令: %s",  cmdParam.ucbViewRemoteDesktop  ?  "远程桌面"  :  "无"  );

	 //  2007/02/04
	 if  (  !cmdParam.ucbOped  )  memset(  &cmdParam,  0,  sizeof(  cmdParam  )  );

	 if  (  memcmp(  &pQwm->cfg.getOpCmd,  &cmdParam,  sizeof(  pQwm->cfg.getOpCmd  )  )  )  {
		 memcpy(  &pQwm->cfg.getOpCmd,  &cmdParam,  sizeof(  pQwm->cfg.getOpCmd  )  );
		 //
		 //  2007/02/04, 这里要把cmdParam写到注册表里去, 以方便用户进程来得到这些信息
		 QY_REG		reg;
		 //
		 memset(  &reg,  0,  sizeof(  reg  )  );
	 	 lstrcpyn(  reg.rootKey,  _T(  CONST_qyKey_qwm  ), mycountof(  reg.rootKey  )  );
	 	 reg.pEncCtx  =  &pQwm->encCtx;
		 //   
		 qySetRegDataEx(  &reg,  _T(  CONST_regValName_opCmd  ),  (  char  *  )&cmdParam,  sizeof(  cmdParam  )  );
		 
	 }

	 iErr  =  0;

errLabel:

	 if  (  bSessionOpen  )  qnmCloseSession(  &session.comm,  &sock,  &pQwm->cfg.to  );

	 traceLogA(  "retrieveOpCmd leaves %s",  iErr  ?  "失败"  :  "成功"  );

	 return  iErr;
}

