
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	<objbase.h>
#include	<winioctl.h>
#include	<initguid.h>
#include	<windows.h>
#include	<ras.h>
#include	<iphlpapi.h>
#include	<tchar.h>

#define	DWORD_PTR	unsigned  long  *
#define	ULONG_PTR	unsigned  long  *

#include	"mySetupapi.h"
#include	"myCfgMgr32.h"

#include	"qnmDevCommProc.h"
#include	"asrWMon.h"

#define		CONST_validRootKey_enum					(  "Enum"  )
#define		CONST_regValName_driver					(  "Driver"  )
#define		CONST_string_netTrans						"NetTrans"
#define		CONST_qyRootKey_serviceClass				"SYSTEM\\CurrentControlSet\\Services\\Class"
#define		CONST_regValName_driverDesc				(  "DriverDesc"  )
#define		CONST_regValName_ipAddress					"IPAddress"
#define		CONST_regValName_ipMask						"IPMask"
#define		CONST_qyRootKey_msTcp					"System\\CurrentControlSet\\Services\\VxD\\MSTCP"
	#define		CONST_regValName_enableDns				"EnableDNS"
	#define		CONST_regValName_nameServer				"NameServer"
	#define		CONST_regValName_hostName				"HostName"
	#define		CONST_regValName_domain					"Domain"
	#define		CONST_regValName_searchList				"SearchList"


 //  
#if  0
  int  get98AdapterInfo(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 COMMON_PARAM		*	pCommonParam	=  (  COMMON_PARAM  *  )p0;
	 QNM_DEV_INFO		*	pQnmDevInfo		=  (  QNM_DEV_INFO  *  )p2;
	 QY_PCADAPTER_INFO		pcAdapter;
	 TCHAR					keyBuf[256]		=  _T(  ""  );
	 char					tmpBuf[256]		=  "";


	 //  填充pcAdapter结构  {
	 {
		 memset(  &pcAdapter,  0,  sizeof(  pcAdapter  )  );
		 pcAdapter.uiType  =  CONST_pcNetworkPropType_adapter;
		 pcAdapter.uiSize  =  sizeof(  pcAdapter  );
		 safeStrnCpy(  pQnmDevInfo->devIdStr,  pcAdapter.devIdStr,  sizeof(  pcAdapter.devIdStr  )  );
		 safeStrnCpy(  pQnmDevInfo->devDesc,  pcAdapter.devDesc,  sizeof(  pcAdapter.devDesc  )  );

		 _snprintf(  keyBuf,  sizeof(  keyBuf  ),  "%s\\%s",  CONST_validRootKey_enum,  pQnmDevInfo->devIdStr  );  
		 qyGetRegCfg(  keyBuf,  CONST_regValName_driver,  tmpBuf,  sizeof(  tmpBuf  )  );
		 char  *p;
		 if  (  !(  p  =  strchr(  tmpBuf,  '\\'  )  )  )  goto  errLabel;

		 //  IP地址
		 _snprintf(  keyBuf,  sizeof(  keyBuf  ),  "%s\\%s%s",  CONST_qyRootKey_serviceClass,  CONST_string_netTrans,  p  );
		 qyGetRegCfg(  keyBuf,  CONST_regValName_ipAddress,  pcAdapter.ipBuf,  sizeof(  pcAdapter.ipBuf  )  );
		 //  IP掩码
		 qyGetRegCfg(  keyBuf,  CONST_regValName_ipMask,  pcAdapter.ipMaskBuf,  sizeof(  pcAdapter.ipMaskBuf  )  );
 		 //  路由
		 if  (  qyGetRegCfg(  keyBuf,  CONST_regValName_defaultGateway,  pcAdapter.gatewayBuf,  sizeof(  pcAdapter.gatewayBuf  )  )  )  pcAdapter.gatewayBuf[0]  =  0;

		 //  DhcpEnabled
		 if  (  !inet_addr(  pcAdapter.ipBuf  )  &&  !inet_addr(  pcAdapter.ipMaskBuf  )  )  {
			 pcAdapter.ucbDhcpEnabled  =  TRUE;
		 }

		 //  DNS
		 if  (  qyGetRegCfg(  CONST_qyRootKey_msTcp,  CONST_regValName_enableDns,  tmpBuf,  sizeof(  tmpBuf  )  )  )  tmpBuf[0]  =  0;
		 if  (  atol(  tmpBuf  )  )  {	//  在支持DNS的情况下, 才读取设置
			 if  (  qyGetRegCfg(  CONST_qyRootKey_msTcp,  CONST_regValName_nameServer,  pcAdapter.dnsBuf,  sizeof(  pcAdapter.dnsBuf  )  )  )  pcAdapter.dnsBuf[0]  =  0;
		 }

	 }
	 //  }

	 tmpHandler_sndPcNetworkProp(  p0,  p2,  &pcAdapter  );

errLabel:
	 return  0;
}
#endif
  int  get98AdapterInfo(  void  *  p0,  void  *  p1,  void  *  p2  )
  {
	  return  -1;
  }

 int  procNtPcAdapters(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 traceLogA(  "procNtPcAdapters: nt暂时不支持"  );
	 return  0;
}


 int  procPcNetworkPropChange_nt(  QWM_THREADINFO  *  pSubThreadInfo  )
{
	 traceLogA(  "procPcNetworkPropChange_nt: nt暂时不支持"  );
	 return  0;
}


#if  0
 int  tmpHandler_changePcNetworkProp_98(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int						iErr					=	-1;
	QWM_THREADINFO		*	pSubThreadInfo			=	(  QWM_THREADINFO  *  )p0;
	QY_W_MON			*	pQwm					=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	PROC_DEV_STRUCT		*	pProcDevStruct			=	(  PROC_DEV_STRUCT  *  )p1;
	QNM_DEV_INFO		*	pQnmDevInfo				=	(  QNM_DEV_INFO  *  )p2;
	QY_PCNETWORK_PROPU	*	pNewProp				=	(  QY_PCNETWORK_PROPU  *  )&pQwm->cfg.newPcNetworkProp;
	QY_PCNETWORK_INFOU	*	pCurInfo				=	(  QY_PCNETWORK_INFOU  *  )&pQwm->cfg.curPcNetworkInfo;
	char					keyBuf[256]				=	"";
	char					tmpBuf[256]				=	"";
	DWORD					cb;
	BOOL					bNotSupported			=	FALSE;		//  2005/11/27, 对98的IP修改等功能再次开放，但是不再提供修改后立即重起的功能，需要在终端再次重起后生效
	
	traceLogA(  "tmpHandler_mgrNetworkPropChange_98(  ):  devId is %s",  pQnmDevInfo->devIdStr  );
	#ifdef		__DEBUG__
				printPcAdapterProp(  &pNewProp->adapter  );
	#endif

	if  (  !strcmpi(  pNewProp->adapter.devIdStr,  pQnmDevInfo->devIdStr  )  )  {
		unsigned  int	ucbRestartOs  =  FALSE;
		traceLogA(  "将修改网络配置"  );

		_snprintf(  keyBuf,  sizeof(  keyBuf  ),  "%s\\%s",  CONST_validRootKey_enum,  pQnmDevInfo->devIdStr  );  
		qyGetRegCfg(  keyBuf,  CONST_regValName_driver,  tmpBuf,  sizeof(  tmpBuf  )  );
		char  *p;
		if  (  !(  p  =  strchr(  tmpBuf,  '\\'  )  )  )  goto  errLabel;
		_snprintf(  keyBuf,  sizeof(  keyBuf  ),  "%s\\%s%s",  CONST_qyRootKey_serviceClass,  CONST_string_netTrans,  p  );

		if  (  pNewProp->adapter.ucbDhcpEnabled  )  {
			_snprintf(  pNewProp->adapter.ipBuf,  sizeof(  pNewProp->adapter.ipBuf  ),  "%s",  "0.0.0.0"  );
			_snprintf(  pNewProp->adapter.ipMaskBuf,  sizeof(  pNewProp->adapter.ipMaskBuf  ),  "%s",  "0.0.0.0"  );
		}
			  
		//  修改IP地址,需要系统重启
		if  (  pProcDevStruct->ucbNeedRecover  ||  strcmpi(  pNewProp->adapter.ipBuf,  pCurInfo->adapter.ipBuf  )  )  {
			if  (  !bNotSupported  )  {
				if  (  qySetRegCfg(  keyBuf,  CONST_regValName_ipAddress,  pNewProp->adapter.ipBuf  )  )  goto  errLabel;
			}
			ucbRestartOs  =  TRUE;
		}
		//  修改IP掩码,需要系统重启
		if  (  pProcDevStruct->ucbNeedRecover  ||  strcmpi(  pNewProp->adapter.ipMaskBuf,  pCurInfo->adapter.ipMaskBuf  )  )  {
			if  (  !bNotSupported  )  {
				if  (  qySetRegCfg(  keyBuf,  CONST_regValName_ipMask,  pNewProp->adapter.ipMaskBuf  )  )  goto  errLabel;
			}
			ucbRestartOs  =  TRUE;
		}
		//  修改路由,需要系统重启
		if  (  pProcDevStruct->ucbNeedRecover  ||  strcmpi(  pNewProp->adapter.gatewayBuf,  pCurInfo->adapter.gatewayBuf  )  )  {
			if  (  !pNewProp->adapter.ucbDhcpEnabled  )  {
				if  (  !bNotSupported  )  {
					if  (  !pNewProp->adapter.gatewayBuf[0]  )  qyDelRegCfg(  keyBuf,  CONST_regValName_defaultGateway  );
					else  {
						  if  (  qySetRegCfg(  keyBuf,  CONST_regValName_defaultGateway,  pNewProp->adapter.gatewayBuf  )  )  goto  errLabel;
					}
				}
				ucbRestartOs  =  TRUE;
			}
		}
		
		if  (  bNotSupported  &&  ucbRestartOs  )  showPcNetworkPropStatus(  pQwm,  (  QY_PCNETWORK_PROPU  *  )pCurInfo,  CONST_ucFlg_err  );  	//  切记，这里对98做了限制, 2005/06/12

		//  修改dns
		if  (  pProcDevStruct->ucbNeedRecover  ||  strcmpi(  pNewProp->adapter.dnsBuf,  pCurInfo->adapter.dnsBuf  )  )  {
			if  (  !pNewProp->adapter.dnsBuf[0]  )  {
				qySetRegCfg(  CONST_qyRootKey_msTcp,  CONST_regValName_enableDns,  "0"  );
				qyDelRegCfg(  CONST_qyRootKey_msTcp,  CONST_regValName_nameServer  );
				//  2006/01/01
				qyDelRegCfg(  CONST_qyRootKey_msTcp,  CONST_regValName_hostName  );
				qyDelRegCfg(  CONST_qyRootKey_msTcp,  CONST_regValName_domain  );
				qyDelRegCfg(  CONST_qyRootKey_msTcp,  CONST_regValName_searchList  );				
				}
			else  {
				  qySetRegCfg(  CONST_qyRootKey_msTcp,  CONST_regValName_enableDns,  "1"  );
				  qySetRegCfg(  CONST_qyRootKey_msTcp,  CONST_regValName_nameServer,  pNewProp->adapter.dnsBuf  );
				  cb  =  sizeof(  tmpBuf  );	//  2006/01/01,
	 			  if  (  !GetComputerName(  tmpBuf,  &cb  )  )  tmpBuf[0]  =  0;
				  qySetRegCfg(  CONST_qyRootKey_msTcp,  CONST_regValName_hostName,  tmpBuf  );
			}
		}


		if  (  !ucbRestartOs  )  {
			pProcDevStruct->ucbNeedReboot  =  FALSE;  traceLogA(  "98操作系统这里不需要重启"  );
		}
	}


	iErr  =  0;	 
errLabel:
	return  iErr;
}
#endif
 int  tmpHandler_changePcNetworkProp_98(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	return  -1;
 }



 int  tmpHandler_changeProxyCfg(  void  *  pCommonParam1,  void  *  p1,  void  *  pPcNetworkInfoParam  )
{
	 int					iErr			=	-1;
	 COMMON_PARAM		*	pCommonParam	=	(  COMMON_PARAM  *  )pCommonParam1;
	 QY_W_MON			*	pQwm			=	(  QY_W_MON  *  )pCommonParam->p0;
	 QY_PCNETWORK_INFOU	*	pCurU			=	(  QY_PCNETWORK_INFOU  *  )pPcNetworkInfoParam;
	 QY_PCNETWORK_PROPU	*	pNewU			=	&pQwm->cfg.newPcNetworkProp;
	 QY_REG					reg;
	 QWM_USR_INFO			usrInfo;
	 DWORD					dwVal;
	 TCHAR					tBuf[1024]		=	_T(  ""  );
	 unsigned  int			cb;

	 traceLogA(  "tmpHandler_changeProxyCfg enters"  );

	 if  (  g_bIsWinNT  )  getUsrProxyInfo(  &pCurU->usrInfo  );	//  2007/02/17, 因为在enumRegUsrs中把代理服务器的信息提取划了出来，故这里要这样再读一下

	 if  (  pCurU->uiType  !=  CONST_pcNetworkPropType_proxy  )  goto  errLabel;
	 if  (  !strcmpi(  pCurU->usrInfo.szSubKey,  CONST_subKey_defaultUsr  )  
		 ||  !pCurU->usrInfo.name[0]  )  
	 {
		 iErr  =  0;  goto  errLabel;
	 }

	 //  下面取代理配置,	2003/09/14
	 memset(  &reg,  0,  sizeof(  reg  )  );
	 if  (  !g_bIsWinNT  )  {
		 reg.hKeyRoot0  =  HKEY_CURRENT_USER;
		 _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s"  ),  _T(  CONST_qyRootKey_internetSettings  )  );
		}
	 else  {
		   reg.hKeyRoot0  =  HKEY_USERS;
		   _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%S\\%s"  ),  pCurU->usrInfo.szSubKey,  _T(  CONST_qyRootKey_internetSettings  )  );
	 }

	 memcpy(  &usrInfo,  pNewU,  sizeof(  usrInfo  )  );
	 
	 if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_enableAutodial  ),  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  0;
	 if  (  usrInfo.ucbEnableAutodial  !=  (  unsigned  char  )dwVal  )  {
		 reg.uiType  =  REG_DWORD;
		 dwVal  =  usrInfo.ucbEnableAutodial  ?  1  :  0;
		 tmpSetRegCfgEx(  &reg,  _T(  CONST_regValName_enableAutodial  ),  (  char  *  )&dwVal,  0  );		 
	 }
	 if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_noNetAutodial  ),  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  0;
	 if  (  usrInfo.ucbNoNetAutodial  !=  (  unsigned  char  )dwVal  )  {
		 reg.uiType  =  REG_DWORD;
		 dwVal  =  usrInfo.ucbNoNetAutodial  ?  1  :  0;
		 tmpSetRegCfgEx(  &reg,  _T(  CONST_regValName_noNetAutodial  ),  (  char  *  )&dwVal,  0  );
	 }
	 if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_proxyEnable  ),  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  0;
	 if  (  usrInfo.ucbProxyEnable  !=  (  unsigned  char  )dwVal  )  {
		 reg.uiType  =  REG_DWORD;
		 dwVal  =  usrInfo.ucbProxyEnable  ?  1  :  0;
		 tmpSetRegCfgEx(  &reg,  _T(  CONST_regValName_proxyEnable  ),  (  char  *  )&dwVal,  0  );
	 }
	 	 
	 if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_proxyServer  ),  (  char  *  )tBuf,  sizeof(  tBuf  )  )  )  tBuf[0]  =  0;
	 if  (  mystricmp(  usrInfo.proxyServer,  tBuf  )  )  {
		 reg.uiType  =  REG_SZ;
		 myStr2TChar(  usrInfo.proxyServer,  tBuf,  mycountof(  tBuf  )  );
		 tmpSetRegCfgEx(  &reg,  _T(  CONST_regValName_proxyServer  ),  (  char  *  )tBuf,  0  );
	 }

	 if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_proxyOverride  ),  (  char  *  )tBuf,  sizeof(  tBuf  )  )  )   tBuf[0]  =  0;
	 if  (  mystricmp(  usrInfo.proxyOverride,  tBuf  )  )  {
		 reg.uiType  =  REG_SZ;
		 myStr2TChar(  usrInfo.proxyOverride,  tBuf,  mycountof(  tBuf  )  );
		 tmpSetRegCfgEx(  &reg,  _T(  CONST_regValName_proxyOverride  ),  (  char  *  )tBuf,  0  );
	 }

	 //  2006/11/25
	 if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_autoConfigUrl  ),  (  char  *  )tBuf,  sizeof(  tBuf  )  )  )  tBuf[0]  =  0;
	 if  (  mystricmp(  usrInfo.autoConfigUrl,  tBuf  )  )  {
		 reg.uiType  =  REG_SZ;
		 myStr2TChar(  usrInfo.autoConfigUrl,  tBuf,  mycountof(  tBuf  )  );
		 tmpSetRegCfgEx(  &reg,  _T(  CONST_regValName_autoConfigUrl  ),  (  char  *  )tBuf,  0  );
	 }
 
	 //  下面取DefaultConnectionSettings
	 _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\%s"  ),  reg.rootKey,  _T(  CONST_qySubKey_connections  )  );
	 char  buf[32];
	 cb  =  sizeof(  buf  );
	 if  (  !tmpGetRegCfgEx(  &reg,  _T(  CONST_regValName_defaultConnectionSettings  ),  buf,  &cb  )  )  {
		 dwVal  =  (  buf[8]  &  8  )  ?  TRUE  :  FALSE;
		 if  (  usrInfo.ucbAutoDetectSettings  !=  (  unsigned  char  )dwVal  )  {
			 reg.uiType  =  REG_BINARY;
			 if  (  usrInfo.ucbAutoDetectSettings  )  buf[8]  |=  8;
			 else  buf[8]  &=  ~8;
			 tmpSetRegCfgEx(  &reg,  _T(  CONST_regValName_defaultConnectionSettings  ),  buf,  cb  );
		 }
	 }
	  

	 iErr  =  0;

errLabel:

	 traceLogA(  "tmpHandler_changeProxyCfg leaves with %s",  iErr  ?  "失败"  :  "成功"  );

	 return  iErr;

}


 int  changeProxyCfg(  	QWM_THREADINFO		*	pSubThreadInfo  )
{
	int						iErr					=	-1;
	QY_W_MON			*	pQwm					=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	QY_PCNETWORK_PROPU	*	pNewProp				=	(  QY_PCNETWORK_PROPU  *  )&pQwm->cfg.newPcNetworkProp;
	QY_PCNETWORK_INFOU	*	pCurInfo				=	(  QY_PCNETWORK_INFOU  *  )&pQwm->cfg.curPcNetworkInfo;
	//  QY_REG					reg;
	long					l						=	0;
	//  QY_PCNETWORK_PROPU		tmpProp;
	char					buf[128]				=	"";
	QWM_USR_INFO		*	pNewUsrInfo				=	NULL;
	QWM_USR_INFO		*	pCurUsrInfo				=	NULL;
	COMMON_PARAM			param;
	 
	if  (  pNewProp->uiType  !=  CONST_pcNetworkPropType_proxy  ||  pCurInfo->uiType  !=  CONST_pcNetworkPropType_proxy  )  goto  errLabel;
	
	MACRO_makeCommonParam3(  pQwm,  0,  0,  param  );

	switch  (  pQwm->env.iPlatformId  )  {
			case  CONST_qyPlatform_nt:
				  traceLogA(  "不支持"  );  
				  iErr  =  0;  break;
			default:
				   if  (  !g_bIsWinNT  )  iErr  =  proc98RegUsr(  pQwm->env.iPlatformId,  &param,  0,  tmpHandler_changeProxyCfg  );
				   else  iErr  =  enumRegUsrs(  pQwm->env.iPlatformId,  &param,  0,  tmpHandler_changeProxyCfg  );
				   break;
	}
errLabel:
	return  iErr;

}

#if  0	//  2010/05/21. not supported
 int  changePcComputer(  	QWM_THREADINFO		*	pSubThreadInfo  )
{
	 int		iErr	=	-1;
	 QY_W_MON			*	pQwm					=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	 QY_PCNETWORK_PROPU	*	pNewProp				=	(  QY_PCNETWORK_PROPU  *  )&pQwm->cfg.newPcNetworkProp;
	 QY_PCNETWORK_INFOU	*	pCurInfo				=	(  QY_PCNETWORK_INFOU  *  )&pQwm->cfg.curPcNetworkInfo;
	 TCHAR					buf[256];
	 unsigned  char			ucbRestart				=	FALSE;
	 QWM_DYN_LIB		*	pDynLib					=	(  QWM_DYN_LIB  *  )pQwm->env.pDynLibs;

	 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_computerName  ),  _T(  CONST_regValName_computerName  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
	 if  (  mystricmp(  pNewProp->computer.computerName,  buf  )  )  {
		 myUtf82TChar(  pNewProp->computer.computerName,  buf,  mycountof(  buf  )  );
		 SetComputerName(  buf  );  
		 ucbRestart  =  TRUE;
	 }
	 if  (  g_bIsWinNT  )  {
		 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_tcpParameters  ),  _T(  CONST_regValName_nvHostname  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
		 if  (  mystricmp(  pNewProp->computer.hostname,  buf  )  )  {
			 //  qySetRegCfg(  CONST_qyRootKey_tcpParameters,  CONST_regValName_nvHostname,  pNewProp->computer.hostname  );
			 if  (  g_bIsWinNT  &&  pQwm->env.iPlatformId  !=  CONST_qyPlatform_nt  )  {  //  2000以上才支持, 因为直接修改注册表容易造成域内主机失去联接，故改为用API的方式, 2005/09/18
				 myUtf82TChar(  pNewProp->computer.hostname,  buf,  mycountof(  buf  )  );
				 if  (  pDynLib->pSetComputerNameEx  &&  pDynLib->pSetComputerNameEx(  myComputerNamePhysicalDnsHostName,  buf  )  )  {
					 ucbRestart  =  TRUE;
				 }
			 }
			 
		 }
	 }
	 if  (  pNewProp->computer.ucbAutoRestartIfChanged  &&  ucbRestart  )  willReboot(  pQwm  );

	 iErr  =  0;
//  errLabel:
	 return  iErr;
}
#endif

 int  changePcComputer(  	QWM_THREADINFO		*	pSubThreadInfo  )
{
	 traceLog(  _T(  "Do not support to change pc name"  )  );	//  2010/05/21
	 return  0;
}

 

