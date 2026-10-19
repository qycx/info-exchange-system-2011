


#include	<windows.h>
#include	<winsock.h>
#include	<ras.h>
#include	<raserror.h>
#include	<commctrl.h>
#include	<lmaccess.h>
#include	<iphlpapi.h>
#include	<tchar.h>
//  #include	"resource.h"
#include	"asrWMon.h"
#include	"qnmAssetsCommProc.h"
#include	"qyRegToolProc.h"
#include	"qwmAllHints.h"

 QY_REG_TOOL						gQyRegTool;


 int  sndAssetsInfo(  void  *  pSubThreadInfoParam,  QWM_ASSETS_INFO  *  pAssetsInfo,  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock  );
 

 int  chkPcInfo(  void  *  pSubThreadInfoParam,  void  *  p1Reserved,  void  *  p2Reserved  )
{	 
	int						iErr				=	-1;
	MT_SUBTHREADINFO	*	pSubThreadInfo		=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	QY_REG_TOOL			*	pQrt				=	(  QY_REG_TOOL  *  )pSubThreadInfo->pParentParam;
	ASR_SOCK				aS;
	int						i					=	0;
	char					ip[16];
	QNM_COMM_AUTHINFO		authInfo;
	QY_COMM_SESSION			session;
	QY_COMM_RESP			tmpResp;
	char					cfgsBuf[4096];
	QWM_INFO_EX			*	pQwmInfoEx			=	NULL;
	QWM_ASSETS_INFO		*	pQwmAssetInfo		=	NULL;
	int						len;

	traceLogA(  "chkPcInfo enters."  );
		
	clearQySock(  &aS  );
	memset(  &session,  0,  sizeof(  session  )  );
	
	traceLogA(  "连接服务器 %s : %d",  pQrt->cfg.cnt.ip,  pQrt->cfg.cnt.port  );
	for  (  i  =  0;  i  <  pQrt->cfg.usTries_connect;  i  ++  )  {
		 if  (  !qyConnect(  pQrt->cfg.cnt.ip,  pQrt->cfg.cnt.port,  &aS,  pQrt->cfg.to.iConnect  )  )  {
			 break;		
		 }
		 Sleep(  1000  );
	}
	if  (  i  ==  pQrt->cfg.usTries_connect  )  {
		traceLogA(  "连接服务器失败。"  );  goto  errLabel;
	}
	
	if  (  getLocalIpBySocket(  aS.sockFd,  ip  )  )  goto  errLabel;
	memset(  &authInfo,  0,  sizeof(  authInfo  )  );
	if  (  makeQwmAuthInfo(  pQrt->ver,  &pQrt->macsInfo,  &authInfo  )  )  goto  errLabel;
	memcpy(  authInfo.ip,  ip,  sizeof(  authInfo.ip  )  );
	
	session.encCtx.type  =  CONST_qyEncType_qnm;

	if  (  qyTellService(  pQrt->iServiceId,  pQrt->ver,  &pQrt->commEncCtx,  (  char  *  )&authInfo,  sizeof(  authInfo  ),  &aS,  &pQrt->cfg.to,  &session  )  )  goto  errLabel;
	traceLogA(  "qyTellService ok."  );
	if  (  qyRecvResp(  &session,  &aS,  &pQrt->cfg.to,  &tmpResp,  cfgsBuf,  sizeof(  cfgsBuf  )  )  )  goto  errLabel;
	traceLogA(  "get respCode %s",  qyGetDesByType1(  CONST_qyRcTable,  tmpResp.head.usCode  )  );
	if  (  !isRcOk(  tmpResp.head.usCode  )  )  goto  errLabel;
	
	traceLogA(  "发送终端信息"  );
	if  (  !(  pQwmInfoEx  =  (  QWM_INFO_EX  *  )malloc(  sizeof(  QWM_INFO_EX  )  )  )  )  goto  errLabel;
	//  取终端信息
	memset(  pQwmInfoEx,  0,  sizeof(  QWM_INFO_EX  )  );
	pQwmInfoEx->type  =  CONST_qwmInfoType_sp;
	pQwmInfoEx->u.sp.qwm.iPlatformId  =  pQrt->env.iPlatformId;
	safeStrnCpy(  pQrt->pcName,  pQwmInfoEx->u.sp.qwm.pcName,  sizeof(  pQwmInfoEx->u.sp.qwm.pcName  )  );
	myTChar2Utf8(  pQrt->env.systemBuf,  pQwmInfoEx->u.sp.qwm.systemBuf,  sizeof(  pQwmInfoEx->u.sp.qwm.systemBuf  )  );
	myTChar2Utf8(  pQrt->env.servicePackBuf,  pQwmInfoEx->u.sp.qwm.servicePackBuf,  sizeof(  pQwmInfoEx->u.sp.qwm.servicePackBuf  )  );
	//  safeStrnCpy(  pQrt->curUsrName,  pQwmInfoEx->u.sp.qwm.curUsrName,  sizeof(  pQwmInfoEx->u.sp.qwm.curUsrName  )  );
	pQwmInfoEx->u.sp.qwm.uiLangId  =  pQrt->env.usLangId;													//  2005/01/22
	TCHAR	tBuf[MAX_PATH];
	GetWindowsDirectory(  tBuf,  mycountof(  tBuf  )  );
	myTChar2Utf8(  tBuf,  pQwmInfoEx->u.sp.qwm.winDir,  sizeof(  pQwmInfoEx->u.sp.qwm.winDir  )  );		//  2005/01/22
	//
	//  取spInfo
	if  (  getQwmSpInfo(  pQrt->env.iPlatformId,  pQwmInfoEx  )  )  memset(  pQwmInfoEx,  0,  sizeof(  QWM_INFO_EX  )  );

	//  发送qwmInfo和qwmSpInfo
	len  =  qyhtonQwmInfoEx(  pQwmInfoEx  );
	if  (  qySendReq(  &session,  &aS,  &pQrt->cfg.to,  CONST_qyCmd_showQwmInfoEx,  (  char  *  )pQwmInfoEx,  len  )  )  goto  errLabel;
	if  (  qyRecvResp(  &session,  &aS,  &pQrt->cfg.to,  &tmpResp,  NULL,  0  )  )  goto  errLabel;

	//  及时释放pQwmInfoEx内存
	free(  pQwmInfoEx  );  pQwmInfoEx  =  NULL;

	//  作资产管理检查
	if  (  pQrt->cfg.ucbGetPcAsset  )  {
		traceLogA(  "to get pc asset"  );
		if  (  !(  pQwmAssetInfo  =  (  QWM_ASSETS_INFO  *  )malloc(  sizeof(  pQwmAssetInfo[0]  )  )  )  )  goto  errLabel;

		//  先发送硬件信息
		memset(  pQwmAssetInfo,  0,  sizeof(  pQwmAssetInfo[0]  )  );
		if  (  getQwmAssetsHardwareInfo(  pQrt,  pQwmAssetInfo  )  )  memset(  pQwmAssetInfo,  0,  sizeof(  pQwmAssetInfo[0]  )  );
		if  (  sndAssetsInfo(  pSubThreadInfoParam,  pQwmAssetInfo,  &session,  &aS  )  )  goto  errLabel;
		
		//  再发送软件信息
		memset(  pQwmAssetInfo,  0,  sizeof(  pQwmAssetInfo[0]  )  );
		if  (  getQwmAssetsSoftwareInfo(  pQrt,  pQwmAssetInfo  )  )  memset(  pQwmAssetInfo,  0,  sizeof(  pQwmAssetInfo[0]  )  );
		if  (  sndAssetsInfo(  pSubThreadInfoParam,  pQwmAssetInfo,  &session,  &aS  )  )  goto  errLabel;
				
		//  最后发送结束上传资产信息
		memset(  pQwmAssetInfo,  0,  sizeof(  pQwmAssetInfo[0]  )  );
		if  (  getQwmAssetsHeadInfo(  pQrt,  pQwmAssetInfo  )  )  memset(  pQwmAssetInfo,  0,  sizeof(  pQwmAssetInfo[0]  )  );
		pQwmAssetInfo->uiCodePage  =  CP_UTF8;		//  2005/01/14
		//  qyhtonQwmAssetsHeadInfo(  pQwmAssetInfo  );	//  2005/01/15
		len  =  qyhtonQwmAssetsInfo(  pQwmAssetInfo  );
		if  (  qySendReq(  &session,  &aS,  &pQrt->cfg.to,  CONST_qyCmd_endShowQwmAssetsInfo,  (  char  *  )pQwmAssetInfo,  len  )  )  goto  errLabel;
		if  (  qyRecvResp(  &session,  &aS,  &pQrt->cfg.to,  &tmpResp,  NULL,  0  )  )  goto  errLabel;

		free(  pQwmAssetInfo  );  pQwmAssetInfo  =  NULL;
	}

	//  最后发送结束信息
	if  (  qySendReq(  &session,  &aS,  &pQrt->cfg.to,  CONST_qyCmd_end,  NULL,  0  )  )  goto  errLabel;
	qyRecvResp(  &session,  &aS,  &pQrt->cfg.to,  &tmpResp,  cfgsBuf,  sizeof(  cfgsBuf  )  );

	
	iErr  =  0;
	
errLabel:

	if  (  bQySockOpen(  &aS  )  )  qyDisconnect(  &aS  );

	if  (  pQwmAssetInfo  )  free(  pQwmAssetInfo  );
	if  (  pQwmInfoEx  )  free(  pQwmInfoEx  );
	
	traceLogA(  "chkPcInfo leaves with %s.",  iErr  ?  "失败"  :  "成功"  );

	return  iErr;

}


#define		CONST_maxComponentsPerSend		40
 int  sndAssetsInfo(  void  *  pSubThreadInfoParam,  QWM_ASSETS_INFO  *  pAssetsInfo,  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock  )
{	 
	int						iErr				=	-1;
	MT_SUBTHREADINFO	*	pSubThreadInfo		=	(  MT_SUBTHREADINFO  *  )pSubThreadInfoParam;
	QY_REG_TOOL			*	pQrt				=	(  QY_REG_TOOL  *  )pSubThreadInfo->pParentParam;
	QY_COMM_RESP			tmpResp;
	unsigned  int			cnt					=	0;
	unsigned  int			nComponentsSent		=	0;		//  已发送的组件数
	unsigned  int			nComponentsToSend	=	0;
	unsigned  int			len;

	if  (  !pAssetsInfo  )  return  -1;

	cnt  =  pAssetsInfo->cnt;
	if  (  cnt  >  sizeof(  pAssetsInfo->components  )  /  sizeof(  pAssetsInfo->components[0]  )  )  goto  errLabel;

	//  qyhtonQwmAssetsHeadInfo(  pAssetsInfo  );
	for  (  ;  cnt  >  nComponentsSent;  )  {
		 nComponentsToSend	=  min(  cnt  -  nComponentsSent,  CONST_maxComponentsPerSend  );
		 if  (  nComponentsSent  )  memcpy(  &pAssetsInfo->components[0],  &pAssetsInfo->components[nComponentsSent],  nComponentsToSend  *  sizeof(  pAssetsInfo->components[0]  )  );
		 pAssetsInfo->cnt  =  nComponentsToSend;		 
		 pAssetsInfo->uiCodePage  =  CP_UTF8;		//  2005/01/14
		 len  =  qyhtonQwmAssetsInfo(  pAssetsInfo  );
		 if  (  qySendReq(  pSession,  pSock,  &pQrt->cfg.to,  CONST_qyCmd_showQwmAssetsInfo,  (  char  *  )pAssetsInfo,  len  )  )  goto  errLabel;
		 if  (  qyRecvResp(  pSession,  pSock,  &pQrt->cfg.to,  &tmpResp,  NULL,  0  )  )  goto  errLabel;
		 nComponentsSent  +=  nComponentsToSend;
	}

	iErr  =  0;

errLabel:

	return  iErr;
}


/*
#define		CONST_qrtStep_waitForQwm		20
#define		CONST_qrtStep_connected			24			//  服务器已连接
#define		CONST_qrtStep_canReg			25
#define		CONST_qrtStep_chkQwmVer			26			//  检查软件版本
#define		CONST_qrtStep_regOk				32			//  注册完成
#define		CONST_qrtStep_finished			36			//  注册对话流程结束

*/



//  HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Hotfix\Q823980
//  HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Updates\Windows 2000\SP5\KB824146
//  HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Updates\Windows XP\SP1\KB824146
//  HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Updates\Windows Server 2003\SP1\KB824146


#define		CONST_qyKey_update						"Software\\Microsoft\\Updates"
#define		CONST_qyKey_update_nt					"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Hotfix"
#define		CONST_qyKey_update_2000					"SOFTWARE\\Microsoft\\Updates\\Windows 2000"
#define		CONST_qyKey_update_xp					"SOFTWARE\\Microsoft\\Updates\\Windows XP"
#define		CONST_qyKey_update_2003					"SOFTWARE\\Microsoft\\Updates\\Windows Server 2003"
#define		CONST_regValName_servicePackUnin		"ServicePackUninstall"

 int  getQwmSpInfo(  int  iPlatformId,  QWM_INFO_EX  *  pSpInfo  )
{
	int				iErr				=	-1;
	unsigned  char  ucbGetBiggestSp		=	TRUE;		//  要得到最大的sp
	TCHAR	*		pUpdateKey			=	NULL;
	int				i;
	TCHAR			spNameBuf[32]		=	_T(  ""  );
	int				cnt					=	0;
	TCHAR			updateKeyBuf[255];
	long			lRet;     
	TCHAR			tSubKey[MAX_PATH  +  1];   
	HKEY			hkUpdateKey		=	NULL; 
	HKEY			hkSpKey			=	NULL;


	if  (  pSpInfo->type  !=  CONST_qwmInfoType_sp  )  goto  errLabel;

	if  (  !g_bIsWinNT  )  {  iErr  =  0;  goto  errLabel;  }
	pUpdateKey  =  _T(  CONST_qyKey_update_nt  );
	ucbGetBiggestSp  =  FALSE;

	/*  //  2005/01/23将取sp的方式统一到上面的从hotfix中取
	switch  (  iPlatformId  )  {
		    case  CONST_qyPlatform_nt:
				  pUpdateKey  =  CONST_qyKey_update_nt;
				  ucbGetBiggestSp  =  FALSE;
				  break;
			case  CONST_qyPlatform_win2k:
				  pUpdateKey  =  CONST_qyKey_update_2000;
				  break;
			case  CONST_qyPlatform_winxp:
				  pUpdateKey  =  CONST_qyKey_update_xp;
				  break;
			case  CONST_qyPlatform_win2003:
				  pUpdateKey  =  CONST_qyKey_update_2003;
				  break;
			default:
					//  不需要查SP
					iErr  =  0;  goto  errLabel;
	 }
	 */

	if  (  ucbGetBiggestSp  )  {
		
		lRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  pUpdateKey,  0,  KEY_ENUMERATE_SUB_KEYS,  &hkUpdateKey  ); 
		if  (  lRet  ==  ERROR_SUCCESS  )  {        
			/* enumerate the subkeys */     
			for  (  i  =  0;  ;  i  ++  )  {
			     lRet  =  RegEnumKey(  hkUpdateKey,  i,  tSubKey,  sizeof(  tSubKey  )  ); 
				 if  (  lRet  ==  ERROR_NO_MORE_ITEMS  ||  lRet  !=  ERROR_SUCCESS  )  break;
				 traceLogA(  "tSubKey is %s",  tSubKey  );
				 if  (  !spNameBuf[0]  ||  lstrcmpi(  spNameBuf,  tSubKey  )  <  0  )  {
					 lstrcpyn(  spNameBuf,  tSubKey,  sizeof(  spNameBuf  )  );
				 }				 
			}
			
			RegCloseKey(  hkUpdateKey  );  
		}
	}

	//  2004/05/18修改
	//  _snprintf(  updateKeyBuf,  sizeof(  updateKeyBuf  ),  "%s\\%s",  pUpdateKey,  spNameBuf  );
	lstrcpyn(  updateKeyBuf,  pUpdateKey,  mycountof(  updateKeyBuf  )  );
	lstrcpyn(  updateKeyBuf  +  lstrlen(  updateKeyBuf  ),  _T(  "\\"  ),  mycountof(  updateKeyBuf  )  -  lstrlen(  updateKeyBuf  )  );
	lstrcpyn(  updateKeyBuf  +  lstrlen(  updateKeyBuf  ),  spNameBuf,  mycountof(  updateKeyBuf  )  -  lstrlen(  updateKeyBuf  )  );


	//  枚举各补丁
	lRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  updateKeyBuf,  0,  KEY_ENUMERATE_SUB_KEYS,  &hkSpKey  ); 
	if  (  lRet  ==  ERROR_SUCCESS  )  {        
		for  (  i  =  0;  ;  i  ++  )  {
			 lRet  =  RegEnumKey(  hkSpKey,  i,  tSubKey,  sizeof(  tSubKey  )  ); 
			 if  (  lRet  ==  ERROR_NO_MORE_ITEMS  ||  lRet  !=  ERROR_SUCCESS  )  break;
			 traceLogA(  "补丁 is %s",  tSubKey  );
			 if  (  cnt  <  sizeof(  pSpInfo->u.sp.spNames  )  /  sizeof(  pSpInfo->u.sp.spNames[0]  )  
				 &&  lstrcmpi(  tSubKey,  _T(  CONST_regValName_servicePackUnin  )  )  )  //  这句话是把servicePackUnin略掉
			 {
				 //  lstrcpyn(  pSpInfo->u.sp.spNames[cnt],  tSubKey,  sizeof(  pSpInfo->u.sp.spNames[cnt]  )  );
				 myTChar2Utf8(  tSubKey,  pSpInfo->u.sp.spNames[cnt],  mycountof(  pSpInfo->u.sp.spNames[cnt]  )  );
				 cnt  ++  ;
			 }
		}	
		
		RegCloseKey(  hkSpKey  );
		
	}
			


	iErr  =  0;
errLabel:
	 return  iErr;
}


