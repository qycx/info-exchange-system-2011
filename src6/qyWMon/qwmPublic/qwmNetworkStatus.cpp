
#include	<windows.h>
#include	<winsock.h>
#include	<ras.h>
#include	<raserror.h>
#include	<commctrl.h>
#include	<iphlpapi.h>
#include	<tchar.h>
#include	"asrWMon.h"
//  #include	"myiphlpapi.h"





 //  

 int  tmpHandler_sndPcNetworkProp(  void  *  pCommonParam1,  void  *  p1,  void  *  pAdapterInfoParam  )
{
	 int					iErr			=	-1;
	 COMMON_PARAM		*	pCommonParam	=	(  COMMON_PARAM  *  )pCommonParam1;
	 QY_W_MON			*	pQwm			=	(  QY_W_MON  *  )pCommonParam->p0;
	 QY_COMM_SESSION	*	pSession		=	(  QY_COMM_SESSION  *  )pCommonParam->p1;
	 QY_SOCK			*	pSock			=	(  QY_SOCK  *  )pCommonParam->p2;
	 QY_PCNETWORK_INFOU	*	pPcNetworkInfoU	=	(  QY_PCNETWORK_INFOU  *  )pAdapterInfoParam;
	 QY_PCNETWORK_PROPU		pcNetworkProp;
	 int					len;
	 QY_COMM_RESP			tmpResp;
	 char					buf[sizeof(  QY_PCNETWORK_PROPU  )  +  512];

	 if  (  pQwm->bQuit  )  goto  errLabel;		//  2007/02/18

	 memset(  &pcNetworkProp,  0,  sizeof(  pcNetworkProp  )  );
	 switch  (  pPcNetworkInfoU->uiType  )  {
			 case  CONST_pcNetworkPropType_adapter:  {
				   QNM_DEV_INFO			*	pQnmDevInfo		=	(  QNM_DEV_INFO  *  )p1;
				   QY_PCADAPTER_INFO	*	pAdapterInfo	=	&pPcNetworkInfoU->adapter;
				   
				   pAdapterInfo->uiSize  =  sizeof(  QY_PCADAPTER_PROP  );
				   
				   if  (  strcmpi(  pAdapterInfo->devIdStr,  pQnmDevInfo->devIdStr  )  )  return  0;
	 
				   //  给adapterInfo补充一些信息
				   safeStrnCpy(  pQnmDevInfo->devDesc,  pAdapterInfo->devDesc,  sizeof(  pAdapterInfo->devDesc  )  );
				   }
				   break;
			 case  CONST_pcNetworkPropType_proxy:  {
				   QWM_USR_INFO			*	pUsrInfo		=	&pPcNetworkInfoU->usrInfo;

				   if  (  g_bIsWinNT  )  getUsrProxyInfo(  pUsrInfo  );	//  2007/02/18, 由于在enumRegUsrs中把代理服务器的信息获取划了出来，故这里要加这样的工作

				   pUsrInfo->uiSize  =  sizeof(  QWM_USR_INFO  );

				   //  这里要过滤到没用的键值  
				   trim(  pUsrInfo->szSubKey  );  trim(  pUsrInfo->name  );
		  		   if  (  !strcmpi(  pUsrInfo->szSubKey,  CONST_subKey_defaultUsr  )  )  return  0;
				   if  (  !pUsrInfo->name[0]  )  return  0;

				   }			   	 
				   break;
			 default:	
					 break;
 
	 }
	 //
	 memcpy(  &pcNetworkProp,  pPcNetworkInfoU,  min(  pPcNetworkInfoU->head.uiSize,  sizeof(  pcNetworkProp  )  )  );

	
	 len  =  qyhtonQyPcNetworkPropU(  &pcNetworkProp  );
	 if  (  qySendReq(  pSession,  pSock,  &pQwm->cfg.to,  CONST_qyCmd_showPcNetworkProp,  (  char  *  )&pcNetworkProp,  len  )  )  goto  errLabel;
	 if  (  qyRecvResp(  pSession,  pSock,  &pQwm->cfg.to,  &tmpResp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;
	 if  (  tmpResp.head.usCode  ==  CONST_qyRc_user  )  {
		 QY_PCNETWORK_PROPU	*	pNewProp	=  &pQwm->cfg.newPcNetworkProp;
		 QY_PCNETWORK_INFOU	*	pCurInfo	=  &pQwm->cfg.curPcNetworkInfo;

		 //  保存新的配置信息和保存现有配置信息
		 qyntohQyPcNetworkPropU(  (  QY_PCNETWORK_PROPU  *  )buf  );
		 memcpy(  pNewProp,  buf,  sizeof(  QY_PCNETWORK_PROPU  )  );
		 memcpy(  pCurInfo,  pPcNetworkInfoU,  sizeof(  QY_PCNETWORK_INFOU  )  );
		 //  memcpy(  pCurInfo,  pPcNetworkInfoU,  min(  pPcNetworkInfoU->head.uiSize,  sizeof(  QY_PCNETWORK_INFOU  )  )  );	//  2006/05/23, 上面有越界的可能，故作了限制
																																//  2006/05/24, 注意：这里的uiSize表示的是prop的大小，没表示info的大小。
																																//				结果在网卡信息时把adapter的信息给截掉了，所以还得回到原来的拷贝方式。
																																//				以后还要增加对这样的数据结构的改进方案

		 //  2005/0628，对网卡的处理，如果网卡本身被拔掉了网线，那么本身的IP将为空（至少不正常）
		 //  或者是将设置的IP如果不正常，都不应该进入修改网络属性的步骤
		 if  (  pCurInfo->uiType  ==  CONST_pcNetworkPropType_adapter  )  {
			 if  (  (  g_bIsWinNT  &&  !bIpValid(  pCurInfo->adapter.ipBuf  )  )	//  2006/1/1, 因为鲁抗的98的DHCP未能修改成静态IP的结果，发现是这里的ipBuf的无效判断造成，在此，区分了98和2000，以修正这个错误
				 ||  (  !g_bIsWinNT  &&  !pCurInfo->adapter.ucbDhcpEnabled  &&  !bIpValid(  pCurInfo->adapter.ipBuf  )  )
					||  (  !pNewProp->adapter.ucbDhcpEnabled  &&  !bIpValid(  pNewProp->adapter.ipBuf  )  )  )
			 {
				 traceLogA(  "这里，至少有一个不对：cur.ip is %s, new.ucbDhcp is %d, new.ip is %s",  pCurInfo->adapter.ipBuf,  pNewProp->adapter.ucbDhcpEnabled,  pNewProp->adapter.ipBuf  );
				 iErr  =  0;  goto  errLabel;
			 }		 
		 }

		 traceLogA(  "现在需要修改网络属性了"  );
		 //  设置标志位
		 pQwm->cfg.ucbPcNetworkPropWillChange  =  TRUE;
		 goto  errLabel;	//  这里，表明将停止循环
	 }
	 if  (  !isRcOk(  tmpResp.head.usCode  )  )  {
		 traceLogA(  "sndQwmAdapterProp: 收到了错误的响应码"  );  goto  errLabel;
	 }

	 iErr  =  0;
errLabel:
	 
	 traceLogA(  "tmpHandler_sndPcNetworkProp leaves with %s",  iErr  ?  "失败"  :  "成功"  );

 	 return  iErr;
}


 int  showPcNetworkProp(  QY_W_MON  *  pQwm,  unsigned  int  uiType  )
{
	 int					iErr				=		-1;
	 QY_SOCK				sock;
	 QWM_SESSION			session;
	 BOOL					bSessionOpen		=		FALSE;
	 QY_COMM_RESP			tmpResp;
	 int					len;
	 COMMON_PARAM			commonParam;
	 char					buf[sizeof(  QY_PCNETWORK_PROPU  )  +  512];
	 QY_PCNETWORK_PROPU		pcNetworkProp;

	 if  (  pQwm->cfg.ucbPcNetworkPropWillChange  )  {
		 traceLogA(  "由于设置了网络属性变更的标识，在网络配置好之前，不再报告网络情况"  );  return  -1;
	 }

	 traceInfo(  &pQwm->logCtx,  "showpcNetworkProp enters."  );

	 clearQySock(  &sock  );
	 memset(  &session,  0,  sizeof(  session  )  );

	 if  (  qwmOpenSession(  pQwm,  &session,  &sock  )  )  goto  errLabel;
	 bSessionOpen		=		TRUE;
	 if  (  !isRcOk(  session.comm.usLastRespCode_i  )  )  goto  errLabel;

	 MACRO_makeCommonParam3(  pQwm,  &session,  &sock,  commonParam  );


	 switch  (  uiType  )  {
			 case  0:	
				   //  枚举发送网卡属性	 
				   if  (  showPcAdapters(  &commonParam,  NULL,  0  )  )  goto  errLabel;
				
				   //  枚举发送代理服务器属性
				   if  (  showProxyCfg(  &commonParam,  NULL,  0  )  )  goto  errLabel;
	
				   //  发送计算机名
				   //  if  (  showComputerProp(  &commonParam,  NULL,  0  )  )  goto  errLabel;
				   break;
			 case  CONST_pcCommType_windowsUpdatePolicy:
				   //  发送补丁配置信息
				   if  (  showPcWindowsUpdatePolicy(  &commonParam,  NULL,  0  )  )  goto  errLabel;
				   break;
			 default:
						traceLogA(  "未知的网络属性"  );  goto  errLabel;
	 }
	 

	 //  发送网卡完毕标识符
	 memset(  &pcNetworkProp,  0,  sizeof(  pcNetworkProp  )  );			//  2006/05/06, 发表此结束标识符，以清理数据库的信息
	 pcNetworkProp.uiType	=  uiType  ?  uiType  :  CONST_pcCommType_cleanNetworkProp;
	 pcNetworkProp.adapter.ucFlg		=  -1;

	 len  =  qyhtonQyPcNetworkPropU(  &pcNetworkProp  );
	 if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_showPcNetworkProp,  (  char  *  )&pcNetworkProp,  len  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;

	 //

	 iErr  =  0;

errLabel:

	 if  (  bSessionOpen  )  qwmCloseSession(  pQwm,  &session,  &sock  );

	 traceInfo(  &pQwm->logCtx,  "showpcNetworkProp leaves %s",  iErr  ?  "failed"  :  "ok"  );

	 return  iErr;
}


 //  在网卡设置错误的时候调用，使规则不再起作用
 int  showPcNetworkPropStatus(  QY_W_MON  *  pQwm,  QY_PCNETWORK_PROPU  *  pCur,  unsigned  char  ucFlg  )
{
	 int					iErr				=		-1;
	 QY_SOCK				sock;
	 QY_COMM_SESSION		session;
	 BOOL					bSessionOpen		=		FALSE;
	 QY_COMM_RESP			tmpResp;
	 int					len;
	 char					buf[sizeof(  QY_PCNETWORK_PROPU  )  +  512];
	 QY_PCNETWORK_PROPU		pcNetworkProp;
	 QWM_MACS_INFO			macsInfo;

	 if  (  !pCur  )  return  -1;

	 traceInfo(  &pQwm->logCtx,  "showPcNetworkPropRecover enters."  );

	 clearQySock(  &sock  );
	 memset(  &session,  0,  sizeof(  session  )  );

	 memset(  &macsInfo,  0,  sizeof(  macsInfo  )  );
	 getQwmMacs(  &pQwm->env,  &macsInfo  );
	 
	 if  (  qnmOpenSession(  pQwm->server.ip,  pQwm->server.port,  &macsInfo,  0,  pQwm->iServiceId,  pQwm->ver,  &pQwm->commEncCtx,  &session,  &sock,  &pQwm->cfg.to,  NULL,  NULL  )  )  goto  errLabel;
	 bSessionOpen		=		TRUE;
	 if  (  !isRcOk(  session.usLastRespCode_i  )  )  goto  errLabel;

	 memcpy(  &pcNetworkProp,  pCur,  sizeof(  pcNetworkProp  )  );
	 pcNetworkProp.adapter.ucFlg		=  ucFlg;

	 len  =  qyhtonQyPcNetworkPropU(  &pcNetworkProp  );
	 if  (  qySendReq(  &session,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_showPcNetworkProp,  (  char  *  )&pcNetworkProp,  len  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &session,  &sock,  &pQwm->cfg.to,  &tmpResp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;
	 	 
	 iErr  =  0;

errLabel:

	 if  (  bSessionOpen  )  qnmCloseSession(  &session,  &sock,  &pQwm->cfg.to  );

	 traceInfo(  &pQwm->logCtx,  "showPcNetworkPropRecover leaves %s",  iErr  ?  "failed"  :  "ok"  );

	 return  iErr;
}

 int  getUsrProxyInfo(  QWM_USR_INFO  *  pUsrInfo  )
{
	 QWM_USR_INFO			usrInfo;
	 QY_REG					reg;
	 DWORD					len;
	 DWORD					dwVal;
	 TCHAR					tBuf[512]  =  _T(  ""  );

	 if  (  !pUsrInfo  )  return  -1;

	 memcpy(  &usrInfo,  pUsrInfo,  sizeof(  usrInfo  )  );
	 
	 //  下面取代理配置,	2003/09/14
	 memset(  &reg,  0,  sizeof(  reg  )  );
	 reg.hKeyRoot0  =  HKEY_USERS;
	 //  lstrcpyn(  reg.rootKey,  usrInfo.szSubKey,  sizeof(  reg.rootKey  )  );
	 myUtf82TChar(  usrInfo.szSubKey,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	 len  =  lstrlen(  reg.rootKey  );
	 lstrcpyn(  reg.rootKey  +  len,  _T(  "\\"  ),  mycountof(  reg.rootKey  )  -  len  );
	 len  =  lstrlen(  reg.rootKey  );
	 lstrcpyn(  reg.rootKey  +  len,  _T(  CONST_qyRootKey_internetSettings  ),  mycountof(  reg.rootKey  )  -  len  );
	 
	 if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_enableAutodial  ),  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  0;
	 usrInfo.ucbEnableAutodial  =  (  unsigned  char  )dwVal;
	 if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_noNetAutodial  ),  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  0;
	 usrInfo.ucbNoNetAutodial  =  (  unsigned  char  )dwVal;
	 if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_proxyEnable  ),  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  0;
	 usrInfo.ucbProxyEnable  =  (  unsigned  char  )dwVal;
		  		

	 if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_proxyServer  ),  (  char  *  )tBuf,  sizeof(  tBuf  )  )  )  tBuf[0]  =  0;
	 myTChar2Utf8(  tBuf,  usrInfo.proxyServer,  mycountof(  usrInfo.proxyServer  )  );
	 trim(  usrInfo.proxyServer  );
	 if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_proxyOverride  ),  (  char  *  )tBuf,  sizeof(  tBuf  )  )  )  tBuf[0]  =  0;
	 myTChar2Utf8(  tBuf,  usrInfo.proxyOverride,  mycountof(  usrInfo.proxyOverride  )  );
	 trim(  usrInfo.proxyOverride  );
	 //  2006/11/25, 取自动设置脚本
	 if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_autoConfigUrl  ),  (  char  *  )tBuf,  sizeof(  tBuf  )  )  )  tBuf[0]  =  0;
	 myTChar2Utf8(  tBuf,  usrInfo.autoConfigUrl,  mycountof(  usrInfo.autoConfigUrl  )  );
	 trim(  usrInfo.autoConfigUrl  );

	 //  下面取DefaultConnectionSettings
	 _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\%s"  ),  reg.rootKey,  _T(  CONST_qySubKey_connections  )  );
	 char  buf[32];
	 if  (  !qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_defaultConnectionSettings  ),  buf,  sizeof(  buf  )  )  )  {
		 if  (  buf[8]  &  8  )  usrInfo.ucbAutoDetectSettings  =  TRUE;
	 }

//  errLabel:

	 memcpy(  pUsrInfo,  &usrInfo,  sizeof(  pUsrInfo[0]  )  );
	
	 return  0;

}

 //  对这里的用户，因为不会总是在线，为了方便检索，不再使用ucFlg=-1的方式在数据库里清除
 int  enumRegUsrs(  int  iPlatformId,  void  *  p0,  void  *  p1,  PF_commonHandler  pf  )
{
	 int					iErr					=	-1;
	 //  COMMON_PARAM		*	pCommonParam			=	(  COMMON_PARAM  *  )p0;
	 //  QY_W_MON			*	pQwm					=	(  QY_W_MON  *  )pCommonParam->p0;
	 QWM_USR_INFO			usrInfo;
	 QY_REG					reg;
	 DWORD					len;
	 DWORD					dwRtn, dwSubKeyLength;
	 unsigned  int			uiRegUsrIndex			=	0;
	 TCHAR					tBuf[256];
	 
	 //  traceLogA(  "enumRegUsrs enters"  );

	 for  (  uiRegUsrIndex  =  0;  ;  uiRegUsrIndex  ++  )  {
	 	 
		  memset(  &usrInfo,  0,  sizeof(  usrInfo  )  );
		  usrInfo.uiType  =  CONST_pcNetworkPropType_proxy;
		  usrInfo.uiSize  =  sizeof(  usrInfo  );
		  usrInfo.iPlatformId  =  iPlatformId;

		  dwSubKeyLength  =  mycountof(  tBuf  );
     	  dwRtn  =  RegEnumKeyEx(  HKEY_USERS,  uiRegUsrIndex,  tBuf,  &dwSubKeyLength,  NULL,  NULL,  NULL,  NULL  );
		  if  (  dwRtn  !=  ERROR_SUCCESS  )  {  	//  所有的用户检查完毕，等待下一轮检查
		 	  iErr  =  0;  goto  errLabel;
	 	  }
		  myTChar2Utf8(  tBuf,  usrInfo.szSubKey,  mycountof(  usrInfo.szSubKey  )  );
	 	 		  
	 	  //  现在开始处理刚被枚举的用户
		  if  (  !usrInfo.szSubKey[0]  )  continue;		//  校验

	 	  memset(  &reg,  0,  sizeof(  reg  )  );
	 	  reg.hKeyRoot0  =  HKEY_USERS;

		  /*  
		  //  {
	 	  //  下面取代理配置,	2003/09/14
	 	  lstrcpyn(  reg.rootKey,  usrInfo.szSubKey,  sizeof(  reg.rootKey  )  );
	 	  len  =  lstrlen(  reg.rootKey  );
	 	  lstrcpyn(  reg.rootKey  +  len,  "\\",  sizeof(  reg.rootKey  )  -  len  );
	 	  len  =  lstrlen(  reg.rootKey  );
	 	  lstrcpyn(  reg.rootKey  +  len,  CONST_qyRootKey_internetSettings,  sizeof(  reg.rootKey  )  -  len  );
	 	 
		  if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_enableAutodial,  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  0;
		  usrInfo.ucbEnableAutodial  =  (  unsigned  char  )dwVal;
		  if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_noNetAutodial,  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  0;
		  usrInfo.ucbNoNetAutodial  =  (  unsigned  char  )dwVal;
		  if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_proxyEnable,  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  0;
		  usrInfo.ucbProxyEnable  =  (  unsigned  char  )dwVal;
		  		
		  if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_proxyServer,  usrInfo.proxyServer,  sizeof(  usrInfo.proxyServer  )  )  )  usrInfo.proxyServer[0]  =  0;
		  trim(  usrInfo.proxyServer  );
		  if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_proxyOverride,  usrInfo.proxyOverride,  sizeof(  usrInfo.proxyOverride  )  )  )  usrInfo.proxyOverride[0]  =  0;
		  trim(  usrInfo.proxyOverride  );
		  //  2006/11/25, 取自动设置脚本
		  if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_autoConfigUrl,  usrInfo.autoConfigUrl,  sizeof(  usrInfo.autoConfigUrl  )  )  )  usrInfo.autoConfigUrl[0]  =  0;
		  trim(  usrInfo.autoConfigUrl  );

		  //  下面取DefaultConnectionSettings
		  _snprintf(  reg.rootKey,  sizeof(  reg.rootKey  ),  "%s\\%s",  reg.rootKey,  CONST_qySubKey_connections  );
		  if  (  !qyGetRegCfgEx(  &reg,  CONST_regValName_defaultConnectionSettings,  buf,  sizeof(  buf  )  )  )  {
			  if  (  buf[8]  &  8  )  usrInfo.ucbAutoDetectSettings  =  TRUE;
		  }
		  //  }
		  */

	 
	 	  //  下面取用户名,  对NT, 除缺省外，统一为未知用户。
	 	  if  (  !strcmpi(  usrInfo.szSubKey,  ".Default"  )  )  safeStrnCpy(  "(Default)",  usrInfo.name,  sizeof(  usrInfo.name  )  );
	 	  else  {
			    switch  (  iPlatformId  )  {
						case  CONST_qyPlatform_winnt:  
							  safeStrnCpy(  "(Unknown User)",  usrInfo.name,  sizeof(  usrInfo.name  )  );
							  break;
						case  CONST_qyPlatform_win32:	//  2007/01/28, 这里可能不是这样的
						case  CONST_qyPlatform_win95:	//  2007/01/28, 这里可能不是这样的
						case  CONST_qyPlatform_win98:	//  2007/01/28, 这里可能不是这样的
						case  CONST_qyPlatform_winme:	//  2007/01/28, 这里可能不是这样的
						case  CONST_qyPlatform_win2k:
						case  CONST_qyPlatform_winxp:
						case  CONST_qyPlatform_win2003:  
							  //  lstrcpyn(  reg.rootKey,  usrInfo.szSubKey,  sizeof(  reg.rootKey  )  );
							  myUtf82TChar(  usrInfo.szSubKey,  reg.rootKey,  mycountof(  reg.rootKey  )  );
							  len  =  lstrlen(  reg.rootKey  );
							  lstrcpyn(  reg.rootKey  +  len,  _T(  "\\"  ),  mycountof(  reg.rootKey  )  -  len  );
							  len  =  lstrlen(  reg.rootKey  );
							  lstrcpyn(  reg.rootKey  +  len,  _T(  CONST_qyRootKey_explorer  ),  mycountof(  reg.rootKey  )  -  len  );
							  if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_logonUsrName  ),  (  char  *  )tBuf,  sizeof(  tBuf  )  )  )  tBuf[0]  =  0;
							  myTChar2Utf8(  tBuf,  usrInfo.name,  mycountof(  usrInfo.name  )  );
							  break;
						case  CONST_qyPlatform_winVista:	//  2007/01/28, 在vista中，用户名是有另外的取法
						default:
							    //  lstrcpyn(  reg.rootKey,  usrInfo.szSubKey,  sizeof(  reg.rootKey  )  );
							    myUtf82TChar(  usrInfo.szSubKey,  reg.rootKey,  mycountof(  reg.rootKey  )  );
							  	len  =  lstrlen(  reg.rootKey  );
							  	lstrcpyn(  reg.rootKey  +  len,  _T(  "\\"  ),  mycountof(  reg.rootKey  )  -  len  );
							  	len  =  lstrlen(  reg.rootKey  );
							  	lstrcpyn(  reg.rootKey  +  len,  _T(  CONST_subKey_volatileEnvironment  ),  mycountof(  reg.rootKey  )  -  len  );
							  	if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_userName  ),  (  char  *  )tBuf,  sizeof(  tBuf  )  )  )  tBuf[0]  =  0;
								myTChar2Utf8(  tBuf,  usrInfo.name,  mycountof(  tBuf  )  );
							    break;
				}

		  }
	 
		  //  traceLogA(  "detectProxyServer检查到subKey is [%s], usrName is [%s], proxyServer is [%s], index is %d",  usrInfo.szSubKey,  usrInfo.name,  usrInfo.proxyServer,  uiRegUsrIndex  );
		  #ifdef	__DEBUG__
					printQwmUsrInfo(  &usrInfo  );
		  #endif

		  /*
		  //  这里要过滤到没用的键值  
		  trim(  usrInfo.szSubKey  );  trim(  usrInfo.name  );
		  if  (  !lstrcmpi(  usrInfo.szSubKey,  CONST_subKey_defaultUsr  )  )  continue;
		  if  (  !usrInfo.name[0]  )  continue;

		  if  (  tmpHandler_sndPcNetworkProp(  p0,  NULL,  &usrInfo  )  )  goto  errLabel;
		  */
		  //  if  (  pf  &&  pf(  p0,  NULL,  &usrInfo  )  )  goto  errLabel;

		  if  (  pf  )  {
			  int  tmpiRet  =  pf(  p0,  p1,  &usrInfo  );
			  if  (  tmpiRet  )  {
				  iErr  =  tmpiRet;  goto  errLabel;		//  2006/08/06, 因为觉得将上面的NULL改为P1没有影响，故这样去修改
			  }
		  }

	 }

	 iErr  =  0;

errLabel:

	 //  traceLogA(  "enumRegUsrs leaves"  );

	 return  iErr;
}


#if  0
 extern  "C"  int  proc98RegUsr(  int  iPlatformId,  void  *  p0,  void  *  p1,  PF_commonHandler  pf  )
{
	 int					iErr					=	-1;
	 COMMON_PARAM		*	pCommonParam			=	(  COMMON_PARAM  *  )p0;
	 QY_W_MON			*	pQwm					=	(  QY_W_MON  *  )pCommonParam->p0;
	 QY_REG					reg;
	 QWM_USR_INFO			usrInfo;
	 DWORD					dwVal;
	 char					buf[256];
		  
	 memset(  &usrInfo,  0,  sizeof(  usrInfo  )  );
	 usrInfo.uiType  =  CONST_pcNetworkPropType_proxy;
	 usrInfo.uiSize  =  sizeof(  usrInfo  );
	 usrInfo.iPlatformId  =  iPlatformId;

	 //  下面取代理配置,	2003/09/14
	 memset(  &reg,  0,  sizeof(  reg  )  );
	 reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	 _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  _T(  CONST_qyRootKey_internetSettings  )  );
	 	 
	 if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_enableAutodial  ),  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  0;
	 usrInfo.ucbEnableAutodial  =  (  unsigned  char  )dwVal;
	 if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_noNetAutodial,  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  0;
	 usrInfo.ucbNoNetAutodial  =  (  unsigned  char  )dwVal;
	 if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_proxyEnable,  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  0;
	 usrInfo.ucbProxyEnable  =  (  unsigned  char  )dwVal;
		  		
	 if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_proxyServer,  usrInfo.proxyServer,  sizeof(  usrInfo.proxyServer  )  )  )  usrInfo.proxyServer[0]  =  0;
	 trim(  usrInfo.proxyServer  );
	 if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_proxyOverride,  usrInfo.proxyOverride,  sizeof(  usrInfo.proxyOverride  )  )  )  usrInfo.proxyOverride[0]  =  0;
	 trim(  usrInfo.proxyOverride  );
	 //  2006/11/25, 取自动设置脚本
	 if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_autoConfigUrl,  usrInfo.autoConfigUrl,  sizeof(  usrInfo.autoConfigUrl  )  )  )  usrInfo.autoConfigUrl[0]  =  0;
	 trim(  usrInfo.autoConfigUrl  );

	 //  下面取DefaultConnectionSettings
	 _snprintf(  reg.rootKey,  sizeof(  reg.rootKey  ),  "%s\\%s",  reg.rootKey,  CONST_qySubKey_connections  );
	 if  (  !qyGetRegCfgEx(  &reg,  CONST_regValName_defaultConnectionSettings,  buf,  sizeof(  buf  )  )  )  {
		 if  (  buf[8]  &  8  )  usrInfo.ucbAutoDetectSettings  =  TRUE;
	 }

	 _snprintf(  usrInfo.name,  sizeof(  usrInfo.name  ),  "(Default)"  );
	 #ifdef		__DEBUG__
				printQwmUsrInfo(  &usrInfo  );
	 #endif

	 if  (  pf  &&  pf(  p0,  NULL,  &usrInfo  )  )  goto  errLabel;

	 iErr  =  0;
errLabel:
	 return  iErr;
}
#endif
 extern  "C"  int  proc98RegUsr(  int  iPlatformId,  void  *  p0,  void  *  p1,  PF_commonHandler  pf  )
{
	return  -1;
 }


 int  showProxyCfg(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int					iErr					=	-1;
	 COMMON_PARAM		*	pCommonParam			=	(  COMMON_PARAM  *  )p0;
	 QY_W_MON			*	pQwm					=	(  QY_W_MON  *  )pCommonParam->p0;

	 switch  (  pQwm->env.iPlatformId  )  {
			 case  CONST_qyPlatform_nt:
				   traceLogA(  "nt is not supported now"  );
				   iErr  =  0;
				   break;
			 default:
					if  (  !g_bIsWinNT  )  iErr  =  proc98RegUsr(  pQwm->env.iPlatformId,  p0,  p1,  tmpHandler_sndPcNetworkProp  );
					else  iErr  =  enumRegUsrs(  pQwm->env.iPlatformId,  p0,  p1,  tmpHandler_sndPcNetworkProp  );
					break;
					
	 }
	 return  iErr;


}


#if  0
 int  showComputerProp(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int					iErr					=	-1;
	 COMMON_PARAM		*	pCommonParam			=	(  COMMON_PARAM  *  )p0;
	 QY_W_MON			*	pQwm					=	(  QY_W_MON  *  )pCommonParam->p0;
	 QWM_COMPUTER_PROP		computerProp;
	 TCHAR					buf[256];
	 DWORD					cb;
	 
	 memset(  &computerProp,  0,  sizeof(  computerProp  )  );
	 computerProp.uiType  =  CONST_pcNetworkPropType_computer;
	 computerProp.uiSize  =  sizeof(  computerProp  );
	 computerProp.iPlatformId  =  pQwm->env.iPlatformId;
	 computerProp.uiLangId  =  pQwm->env.usLangId;

	 GetWindowsDirectory(  buf,  mycountof(  buf  )  );
	 myTChar2Utf8(  buf,  computerProp.winDir,  sizeof(  computerProp.winDir  )  );
	 //  
	 cb  =  mycountof(  buf  );
	 if  (  !GetComputerName(  buf,  &cb  )  )  buf[0]  =  0;
	 //  _snprintf(  computerProp.activeComputerName,  sizeof(  computerProp.activeComputerName  ),  "%s",  buf  );
	 myTChar2Utf8(  buf,  computerProp.activeComputerName,  mycountof(  computerProp.activeComputerName  )  );
	 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_computerName  ),  _T(  CONST_regValName_computerName  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
	 //  _snprintf(  computerProp.computerName,  sizeof(  computerProp.computerName  ),  "%s",  buf  );
	 myTChar2Utf8(  buf,  computerProp.computerName,  mycountof(  computerProp.computerName  )  );
	 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_tcpParameters  ),  _T(  CONST_regValName_nvHostname  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
	 //  _snprintf(  computerProp.hostname,  sizeof(  computerProp.hostname  ),  "%s",  buf  );
	 myTChar2Utf8(  buf,  computerProp.hostname,  mycountof(  computerProp.hostname  )  );
	 
	 if  (  tmpHandler_sndPcNetworkProp(  p0,  0,  &computerProp  )  )  goto  errLabel;

	 iErr  =  0;
errLabel:
	 return  iErr;
}
#endif

