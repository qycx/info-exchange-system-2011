
// testDevCon.cpp : Defines the entry point for the application.
//

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

//  2007/01/24, VC6下可以通过的，在。NET下编译通不过。把下面2行屏蔽就可以编译了
#ifndef  ULONG_PTR
  #define	ULONG_PTR	unsigned  long  *
#endif
#ifndef  DWORD_PTR
  #define	DWORD_PTR	unsigned  long  *
#endif

#include	"mySetupapi.h"
#include	"myCfgMgr32.h"

#include	"qnmDevCommProc.h"
#include	"asrWMon.h"



//  磁盘
DEFINE_GUID(DiskClassGuid,					0x53f56307L, 0xb6bf, 0x11d0, 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b);
/* A5DCBF10-6530-11D2-901F-00C04FB951ED */	//  MASS storage
DEFINE_GUID(GUID_CLASS_USB_DEVICE,			0xA5DCBF10L, 0x6530, 0x11D2, 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED);
DEFINE_GUID(GUID_CLASS_NET,					0x4D36E972L, 0xE325, 0x11CE, 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18);
DEFINE_GUID(GUID_CLASS_BLUETOOTH,			0xE0CBF06CL, 0xCD8B, 0x4647, 0xBB, 0x8A, 0x26, 0x3B, 0x43, 0xF0, 0xF9, 0x74);		//  2010/08/17
DEFINE_GUID(GUID_CLASS_IRDA,				0x6BDD1FC5L, 0x810F, 0x11D0, 0xBE, 0xC7, 0x08, 0x00, 0x2B, 0xE2, 0x09, 0x2F);
DEFINE_GUID(GUID_CLASS_1394,				0x6BDD1FC1L, 0x810F, 0x11D0, 0xBE, 0xC7, 0x08, 0x00, 0x2B, 0xE2, 0x09, 0x2F);

//{eec5ad98-8080-425f-922a-dabf3de3f69a}
DEFINE_GUID(GUID_CLASS_wpd,					0xeec5ad98,  0x8080,  0x425f,  0x92,  0x2a,  0xda,  0xbf,  0x3d,  0xe3,  0xf6,  0x9a  );
//{A0A588A4-C46F-4B37-B7EA-C82FE89870C6}
DEFINE_GUID(GUID_CLASS_sdHostAdapter,		0xA0A588A4,  0xC46F,  0x4B37,  0xB7,  0xEA,  0xC8,  0x2F,  0xE8,  0x98,  0x70,  0xC6  );
//  HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Control\Class\{25DBCE51-6C8F-4A72-8A6D-B54C2B4FC835}
DEFINE_GUID(GUID_CLASS_mobileDevice,		0x25DBCE51,  0x6C8F,  0x4A72,  0x8A,  0x6D,  0xB5,  0x4C,  0x2B,  0x4F,  0xC8,  0x35  );

//  char  *  getDeviceDescription(  QY_ENV  *  pEnv,  HDEVINFO Devs,PSP_DEVINFO_DATA DevInfo,  char  *  buffer,  unsigned  int  size  );
TCHAR  *  getDeviceDescription(  QY_ENV  *  pEnv,  HDEVINFO Devs,PSP_DEVINFO_DATA DevInfo,  TCHAR  *  buffer,  unsigned  int  size  );
int  enumDevices(  QY_ENV  *  pEnv,  LPGUID lpGuid,  void  *  p0,  void  *  p1,  PF_commonHandler  handler  );
int  enumDevInterfaces(  QY_ENV  *  pEnv,  LPGUID lpGuid,  void  *  p0,  void  *  p1,  PF_commonHandler  handler  );
int  removeCallback(  void  *  p0,  void  *  p1,  void  *  p2  );
int  removeMassStorCallback(  void  *  p0,  void  *  p1,  void  *  p2  );
int  controlCallback(  void  *  p0,  CONTROL_DEV_PARAM  *  p1,  void  *  p2  );
int  procUsbEnumDev(  void  *  p0,  void  *  p1,  void  *  p2  );
int  tmpHandler_mgrUsb(  void  *  p0,  void  *  p1,  void  *  p2  );
//
int  sndQwmAdapterProp(  void  *  pCommonParam1,  void  *  p1,  void  *  pAdapterInfoParam  );
int  get98AdapterInfo(  void  *  p0,  void  *  p1,  void  *  p2  );
int  procNtPcAdapters(  void  *  p0,  void  *  p1,  void  *  p2  );
int  procPcNetworkPropChange_nt(  QWM_THREADINFO  *  pSubThreadInfo  );
int  tmpHandler_changePcNetworkProp_98(  void  *  p0,  void  *  p1,  void  *  p2  );
int  changePcNetworkProp(  QWM_THREADINFO  *  pSubThreadInfo  );
int  changeProxyCfg(  	QWM_THREADINFO		*	pSubThreadInfo  );
int  changePcComputer(  	QWM_THREADINFO		*	pSubThreadInfo  );
int  changeQwmWindowsUpdatePolicy(  	QWM_THREADINFO		*	pSubThreadInfo  );



 int  procNtUsbRule(  QWM_THREADINFO  *  pSubThreadInfo  )
{
	 int					iErr			=	-1;
	 QY_W_MON		*		pQwm			=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;

	 //  traceLogA(  "Sorry, nt is not supported"  );  
	 if  (  pQwm->env.iPlatformId  ==  CONST_qyPlatform_nt  )  goto  errLabel;
	 
	 procUsbEnumDev(  pSubThreadInfo,  &pQwm->procDevStruct,  NULL  );

	 iErr  =  0;
errLabel:
	 return  iErr;
}


 int  procUsbEnumDev(  void  *  p0,  void  *  p1,  void  *  p2  )
{	
	QWM_THREADINFO  *	pSubThreadInfo		=  (  QWM_THREADINFO  *  )p0;
	QY_W_MON		*	pQwm				=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	PROC_DEV_STRUCT	*	pProcDevStruct		=	(  PROC_DEV_STRUCT  *  )p1;
	int					i;
	unsigned  char		ucbUsbStorExists	=	FALSE;
	
	traceLogA(  "procUsbEnumDev enters"  );

	pProcDevStruct->ucMaxDisks  =  sizeof(  pProcDevStruct->disks  )  /  sizeof(  pProcDevStruct->disks[0]  );
	pProcDevStruct->dwProcedLoopCtrl  =  pSubThreadInfo->dwLoopCtrl;	//  标志这一次的处理序号

	pProcDevStruct->ucbRemoved  =  FALSE;
	//  枚举磁盘，以发现USB盘
	enumDevInterfaces(  &pQwm->env,  (  LPGUID  )&DiskClassGuid,  p0,  pProcDevStruct,  tmpHandler_mgrUsb  );
	for  (  i  =  0;  i  <  pProcDevStruct->ucMaxDisks;  i  ++  )  {
		 if  (  pProcDevStruct->disks[i].devIdStr[0]  &&  pProcDevStruct->disks[i].ucbUsb  )  {
			 ucbUsbStorExists  =  TRUE;  break;
		 }
	}

	if  (  ucbUsbStorExists  )  {
		if  (  pQwm->cfg.pcRules.dev.ucUsbStorCmd  ==  CONST_devCmd_restartToProhibit  )  {
			traceLogA(  "对重起阻断的指令，需要重起"  );
			qwmLogDevEvent(  pSubThreadInfo,  CONST_qyEventType_nm_usbRestartToProhibit,  NULL  );
			doReboot(  pSubThreadInfo,  TRUE,  TRUE,  TRUE  );
			//  willReboot(  pQwm  );
			}
		else  if  (  pQwm->cfg.pcRules.dev.ucUsbStorCmd  ==  CONST_devCmd_prohibited  )  {
				  traceLogA(  "对禁用USB的指令，将弹出USB"  );
				  //  枚举MASS STORAGE DEVICE，以删除USB盘,  2005/10/07将removeCallback改为removeMassStorCallback, 以限制其不影响鼠标键盘
				  enumDevInterfaces(  &pQwm->env,  (  LPGUID  )&GUID_CLASS_USB_DEVICE,  p0,  p1,  removeMassStorCallback  );
				  
				  //  如果发生过USB动作，
				  if  (  pProcDevStruct->ucbRemoved  )  	{

					  //  生成一条日志
					  qwmLogDevEvent(  pSubThreadInfo,  CONST_qyEventType_nm_usbStorProhibited,  NULL  );

					  pProcDevStruct->dwProcedLoopCtrl  +=  100000;	//  故意加一个大的增量，作为处理的标记
					  enumDevInterfaces(  &pQwm->env,  (  LPGUID  )&DiskClassGuid,  p0,  pProcDevStruct,  tmpHandler_mgrUsb  );
				  }
		}
	}

	//  在处理完所有现有的磁盘后，没处理的就是消失了的磁盘，这样，要复位这个磁盘结构，并生成日志
	for  (  i  =  0;  i  <  pProcDevStruct->ucMaxDisks;  i  ++  )  {
		 if  (  pProcDevStruct->disks[i].devIdStr[0]  &&  pProcDevStruct->dwProcedLoopCtrl  !=  pProcDevStruct->disks[i].dwProcedLoopCtrl  )  {
			 traceLogA(  "表明这个磁盘消失了"  );
			 if  (  pProcDevStruct->disks[i].ucbUsb  )  {
				 //  traceLogA(  "这里应加入代码，使之产生一条USB盘消失的日志"  );
				 qwmLogDevEvent(  pSubThreadInfo,  CONST_qyEventType_nm_usbStorOut,  &pProcDevStruct->disks[i]  );
			 }
			 memset(  &pProcDevStruct->disks[i],  0,  sizeof(  pProcDevStruct->disks[i]  )  );
		 }
	}

	ucbUsbStorExists  =  FALSE;
	for  (  i  =  0;  i  <  pProcDevStruct->ucMaxDisks;  i  ++  )  {
		 if  (  pProcDevStruct->disks[i].devIdStr[0]  &&  pProcDevStruct->disks[i].ucbUsb  )  {
			 ucbUsbStorExists  =  TRUE;  break;
		 }
	}
	//  2005/10/06, 在这里增加对USB的状态标识, 以便建立对USB存储的文件监视
	pQwm->status.ulbUsbStorExists  =  ucbUsbStorExists  ?  TRUE  :  FALSE;


//  errLabel:

	traceLogA(  "procUsbEnumDev leaves"  );

	return  0;
}


 int  myRemoveUsbFunc(  QY_ENV  *  pEnv,  void  *  p0  )
{
	 //  枚举MASS STORAGE DEVICE，以删除USB盘,  2005/10/07将removeCallback改为removeMassStorCallback, 以限制其不影响鼠标键盘
	 enumDevInterfaces(  pEnv,  (  LPGUID  )&GUID_CLASS_USB_DEVICE,  p0,  NULL,  removeMassStorCallback  );
	 return  0;
}


 int  tmpHandler_mgrUsb(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int					iErr					=	-1;
	QWM_THREADINFO  *	pSubThreadInfo			=	(  QWM_THREADINFO  *  )p0;
	QY_W_MON		*	pQwm					=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	PROC_DEV_STRUCT	*	pProcDevStruct			=	(  PROC_DEV_STRUCT  *  )p1;
	QNM_DEV_INFO	*	pQnmDevInfo				=	(  QNM_DEV_INFO  *  )p2;
	char			*	CONST_usbStorPrefix		=	"usb";
	char			*   CONST_usbDiskFlag		=	"disk";
	char			*   p						=   NULL;
	int					i;

	 traceLogA(  "devId is %s",  pQnmDevInfo->devIdStr  );
	 if  (  !_strnicmp(  pQnmDevInfo->devIdStr,  CONST_usbStorPrefix,  strlen(  CONST_usbStorPrefix  )  )  )  {
		 if  (  (  p  =  strchr(  pQnmDevInfo->devIdStr,  '\\'  )  )  )  {
			 p  ++  ;
			 if  (  !_strnicmp(  p,  CONST_usbDiskFlag,  strlen(  CONST_usbDiskFlag  )  )  )  pQnmDevInfo->ucbUsb  =  TRUE;
		 }
	 }
	 
	 //  先查找是否在队列中
	 for  (  i  =  0;  i  <  pProcDevStruct->ucMaxDisks;  i  ++  )  {
		  if  (  pProcDevStruct->disks[i].devIdStr[0]  &&  !_strnicmp(  pProcDevStruct->disks[i].devIdStr,  pQnmDevInfo->devIdStr,  strlen(  pProcDevStruct->disks[i].devIdStr  )  )  )  break;
	 }

	 if  (  i  <  pProcDevStruct->ucMaxDisks  )  {	// 还在队列中
		 pProcDevStruct->disks[i].dwProcedLoopCtrl  =  pProcDevStruct->dwProcedLoopCtrl;	//  表明已处理过了
		 iErr  =  0;  goto  errLabel;
	 }
	 
	 traceLogA(  "否则表明这个磁盘还没加入队列中, 需要加入队列中"  );
	 for  (  i  =  0;  i  <  pProcDevStruct->ucMaxDisks;  i  ++  )  if  (  !pProcDevStruct->disks[i].devIdStr[0]  )  break;
	 if  (  i  ==  pProcDevStruct->ucMaxDisks  )  {  traceLogA(  "怎么磁盘这么多啊，加不进去了"  );  goto  errLabel;  }
	 //  加入队列
	 safeStrnCpy(  pQnmDevInfo->devIdStr,  pProcDevStruct->disks[i].devIdStr,  sizeof(  pProcDevStruct->disks[i].devIdStr  )  );
	 safeStrnCpy(  pQnmDevInfo->devDesc,  pProcDevStruct->disks[i].devDesc,  sizeof(  pProcDevStruct->disks[i].devDesc  )  );
	 pProcDevStruct->disks[i].ucbUsb  =  pQnmDevInfo->ucbUsb;
	 pProcDevStruct->disks[i].dwProcedLoopCtrl  =  pProcDevStruct->dwProcedLoopCtrl;
	 if  (  pProcDevStruct->disks[i].ucbUsb  )  {
		 traceLogA(  "需要加些代码以生成USB接入主机的日志"  );
		 if  (  pQwm->cfg.pcRules.dev.ucUsbStorCmd  ==  CONST_devCmd_prohibited  )  qwmLogDevEvent(  pSubThreadInfo,  CONST_qyEventType_nm_usbStorUnallowedIn,  &pProcDevStruct->disks[i]  );
		 else  qwmLogDevEvent(  pSubThreadInfo,  CONST_qyEventType_nm_usbStorIn,  &pProcDevStruct->disks[i]  );
	 }
			 
	 iErr  =  0;

errLabel:
	 return  0;
}




 int  tmpHandler_changePcNetworkProp(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int						iErr					=	-1;
	QWM_THREADINFO		*	pSubThreadInfo			=	(  QWM_THREADINFO  *  )p0;
	QY_W_MON			*	pQwm					=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	PROC_DEV_STRUCT		*	pProcDevStruct			=	(  PROC_DEV_STRUCT  *  )p1;
	QNM_DEV_INFO		*	pQnmDevInfo				=	(  QNM_DEV_INFO  *  )p2;
	QY_PCNETWORK_PROPU	*	pNewProp				=	(  QY_PCNETWORK_PROPU  *  )&pQwm->cfg.newPcNetworkProp;
	QY_PCNETWORK_INFOU	*	pCurInfo				=	(  QY_PCNETWORK_INFOU  *  )&pQwm->cfg.curPcNetworkInfo;
	QY_REG					reg;
	long					l						=	0;
	QY_PCNETWORK_PROPU		tmpProp;
	TCHAR					buf[128]				=	_T(  ""  );
	
	traceLogA(  "devId is %s",  pQnmDevInfo->devIdStr  );
	#ifdef		__DEBUG__
				printPcAdapterProp(  &pNewProp->adapter  );
	#endif

	memset(  &tmpProp,  0,  sizeof(  tmpProp  )  );

	if  (  !strcmpi(  pCurInfo->adapter.devIdStr,  pQnmDevInfo->devIdStr  )  )  {
		unsigned  int	ucbRestartAdapter  =  FALSE;
		traceLogA(  "将修改网卡%s %s",  pCurInfo->adapter.connectionName,  pCurInfo->adapter.mac  );

		/////////////////
		//
		memset(  &reg,  0,  sizeof(  reg  )  );
		_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s%S"  ),  _T(  CONST_qyRootKey_tcpIpInterfaces  ),  pCurInfo->adapter.adapterName  );
		if  (  !qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_enableDhcp  ),  (  char  *  )&l,  sizeof(  l  )  )  &&  l  )  tmpProp.adapter.ucbDhcpEnabled  =  TRUE;
		if  (  pProcDevStruct->ucbNeedRecover  ||  pNewProp->adapter.ucbDhcpEnabled  !=  tmpProp.adapter.ucbDhcpEnabled  )  {
			traceLogA(  "DHCP标志位需要改"  );

			//  修改DHCP启停
			reg.uiType  =  REG_DWORD;
			l  =  pNewProp->adapter.ucbDhcpEnabled  ?  1  :  0;
			if  (  tmpSetRegCfgEx(  &reg,  _T(  CONST_regValName_enableDhcp  ),  (  char  *  )&l,  0  )  )  goto  errLabel;
			
			ucbRestartAdapter  =  TRUE;
		}

		//  {
		if  (  pNewProp->adapter.ucbDhcpEnabled  )  {
			_snprintf(  pNewProp->adapter.ipBuf,  sizeof(  pNewProp->adapter.ipBuf  ),  "%s",  "0.0.0.0"  );
			_snprintf(  pNewProp->adapter.ipMaskBuf,  sizeof(  pNewProp->adapter.ipMaskBuf  ),  "%s",  "0.0.0.0"  );
			_snprintf(  pNewProp->adapter.gatewayBuf,  sizeof(  pNewProp->adapter.gatewayBuf  ),  "%s",  ""  );

			memset(  &reg,  0,  sizeof(  reg  )  );
			_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s%S"  ),  _T(  CONST_qyRootKey_tcpIpInterfaces  ),  pCurInfo->adapter.adapterName  );
			l  =  qyntohl(  inet_addr(  "169.254.0.0"  )  )  +  (  rand(  )  &  0xffff  );
			l  =  qyhtonl(  l  );
			if  (  !bulIpValid(  l  )  )  _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s"  ),  _T(  "169.254.2.178"  )  );
			else  myStr2TChar(  inet_ntoa(  *(  struct  in_addr  *  )&l  ),  buf,  mycountof(  buf  )  );
			traceLogA(  "将设置DHCPIP为%s",  buf    );
			tmpSetRegCfgEx(  &reg,  _T(  CONST_regValName_dhcpIpAddress  ),  (  char  *  )buf,  0  );
			tmpSetRegCfgEx(  &reg,  _T(  CONST_regValName_dhcpSubnetMask  ),  (  char  *  )_T(  "255.255.0.0"  ),  0  );
			reg.uiType  =  REG_DWORD;
			l  =  1;
			tmpSetRegCfgEx(  &reg,  _T(  CONST_regValName_addressType  ),  (  char  *  )&l,  0  );
		}
		//  }

		memset(  &reg,  0,  sizeof(  reg  )  );
		_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s%S"  ),  _T(  CONST_qyRootKey_tcpIpInterfaces  ),  pCurInfo->adapter.adapterName  );
		//  if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_ipAddress,  tmpProp.adapter.ipBuf,  sizeof(  tmpProp.adapter.ipBuf  )  )  )  tmpProp.adapter.ipBuf[0]  =  0;
		if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_ipAddress  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
		myTChar2Str(  buf,  tmpProp.adapter.ipBuf,  mycountof(  tmpProp.adapter.ipBuf  )  );
		if  (  pProcDevStruct->ucbNeedRecover  ||  strcmpi(  pNewProp->adapter.ipBuf,  tmpProp.adapter.ipBuf  )  )  {
			traceLogA(  "IP需要改"  );

			//  修改IP地址,需要网卡重启
			reg.uiType  =  REG_MULTI_SZ;
			myStr2TChar(  pNewProp->adapter.ipBuf,  buf,  mycountof(  buf  )  );
			if  (  tmpSetRegCfgEx(  &reg,  _T(  CONST_regValName_ipAddress  ),  (  char  *  )buf,  0  )  )  goto  errLabel; 

			ucbRestartAdapter  =  TRUE;
		}
		//  IP有时没有及时生效，故作下述加强, 2006/08/20
		if  (  !ucbRestartAdapter  )  {
			if  (  !pNewProp->adapter.ucbDhcpEnabled  &&  strcmpi(  pNewProp->adapter.ipBuf,  pCurInfo->adapter.ipBuf  )  )  {
				traceLogA(  "IP没有锁定，需要网卡重启"  );
				ucbRestartAdapter  =  TRUE;
			}
		}


		memset(  &reg,  0,  sizeof(  reg  )  );
		_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s%S"  ),  _T(  CONST_qyRootKey_tcpIpInterfaces  ),  pCurInfo->adapter.adapterName  );
		// if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_subnetMask,  tmpProp.adapter.ipMaskBuf,  sizeof(  tmpProp.adapter.ipMaskBuf  )  )  )  tmpProp.adapter.ipMaskBuf[0]  =  0;
		if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_subnetMask  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
		myTChar2Str(  buf,  tmpProp.adapter.ipMaskBuf,  mycountof(  tmpProp.adapter.ipMaskBuf  )  );
		if  (  pProcDevStruct->ucbNeedRecover  ||  strcmpi(  pNewProp->adapter.ipMaskBuf,  tmpProp.adapter.ipMaskBuf  )  )  {
			traceLogA(  "IP掩码需要改"  );
			
			//  修改IP掩码,需要网卡重启
			reg.uiType  =  REG_MULTI_SZ;
			myStr2TChar(  pNewProp->adapter.ipMaskBuf,  buf,  mycountof(  buf  )  );
			if  (  tmpSetRegCfgEx(  &reg,  _T(  CONST_regValName_subnetMask  ),  (  char  *  )buf,  0  )  )  goto  errLabel; 

			ucbRestartAdapter  =  TRUE;
		}

		memset(  &reg,  0,  sizeof(  reg  )  );
		_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s%S"  ),  _T(  CONST_qyRootKey_tcpIpInterfaces  ),  pCurInfo->adapter.adapterName  );
		//  if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_defaultGateway,  tmpProp.adapter.gatewayBuf,  sizeof(  tmpProp.adapter.gatewayBuf  )  )  )  tmpProp.adapter.gatewayBuf[0]  =  0;
		if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_defaultGateway  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
		myTChar2Str(  buf,  tmpProp.adapter.gatewayBuf,  mycountof(  tmpProp.adapter.gatewayBuf  )  );
		//  if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_defaultGatewayMetric,  tmpProp.adapter.gatewayMetricBuf,  sizeof(  tmpProp.adapter.gatewayMetricBuf  )  )  )  tmpProp.adapter.gatewayMetricBuf[0]  =  0;
		if  (  qyGetRegCfgEx(  &reg,  _T(  CONST_regValName_defaultGatewayMetric  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
		myTChar2Str(  buf,  tmpProp.adapter.gatewayMetricBuf,  mycountof(  tmpProp.adapter.gatewayMetricBuf  )  );
		if  (  pProcDevStruct->ucbNeedRecover  ||  strcmpi(  pNewProp->adapter.gatewayBuf,  tmpProp.adapter.gatewayBuf  )  
			//  ||  strcmpi(  pNewProp->adapter.gatewayMetricBuf,  (  pNewProp->adapter.ucbDhcpEnabled  ?  ""  :  "1"  )  )  
			)  
		{
			traceLogA(  "路由需要改"  );

			//  修改路由,需要网卡重启
			reg.uiType  =  REG_MULTI_SZ;

			myStr2TChar(  pNewProp->adapter.gatewayBuf,  buf,  mycountof(  buf  )  );
			if  (  tmpSetRegCfgEx(  &reg,  _T(  CONST_regValName_defaultGateway  ),  (  char  *  )buf,  0  )  )  goto  errLabel; 
			if  (  tmpSetRegCfgEx(  &reg,  _T(  CONST_regValName_defaultGatewayMetric  ),  (  char  *  )(  pNewProp->adapter.ucbDhcpEnabled  ?  _T(  ""  )  :  _T(  "1"  )  ),  0  )  )  goto  errLabel; 

			ucbRestartAdapter  =  TRUE;
		}


		memset(  &reg,  0,  sizeof(  reg  )  );
		_sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s%S"  ),  _T(  CONST_qyRootKey_tcpIpInterfaces  ),  pCurInfo->adapter.adapterName  );
		if  (  strcmpi(  pNewProp->adapter.dnsBuf,  pCurInfo->adapter.dnsBuf  )  )  {
			traceLogA(  "DNS需要改"  );

			//  
			reg.uiType  =  REG_SZ;
			myStr2TChar(  pNewProp->adapter.dnsBuf,  buf,  mycountof(  buf  )  );
			if  (  tmpSetRegCfgEx(  &reg,  _T(  CONST_regValName_dns  ),  (  char  *  )buf,  0  )  )  goto  errLabel;

		}

		//
		///////////////////////

		if  (  ucbRestartAdapter  )  {
			traceLogA(  "将重新启动网卡%s %s",  pCurInfo->adapter.connectionName,  pCurInfo->adapter.mac  );
		
			pProcDevStruct->controlParam.dwControl  =  DICS_DISABLE;
			if  (  controlCallback(  p0,  &pProcDevStruct->controlParam, p2  )  )  {
				traceLogA(  "禁用网卡失败"  );  goto  errLabel;
			}
			pProcDevStruct->controlParam.dwControl  =  DICS_ENABLE;
			if  (  controlCallback(  p0,  &pProcDevStruct->controlParam, p2  )  )  {
				traceLogA(  "启用网卡成功"  );  goto  errLabel;
			}
			traceLogA(  "重起网卡成功"  );
		}

		traceLogA(  "修改网卡成功"  );
		
		iErr  =  1;  goto  errLabel;
	}
			 
	iErr  =  0;

errLabel:
	 return  0;
}

/*
 BOOL  bServConnected(  QY_W_MON  *  pQwm  )
{
	 BOOL						bRet  =  FALSE;
	 QY_SOCK					sock;
	 QY_COMM_SESSION			session;
	 BOOL						bSessionOpen		=		FALSE;
	 QY_COMM_RESP				tmpResp;
	 QWM_MACS_INFO				macsInfo;


	 clearQySock(  &sock  );
	 memset(  &session,  0,  sizeof(  session  )  );
	 	 
	 memset(  &macsInfo,  0,  sizeof(  macsInfo  )  );
	 getQwmMacs(  &macsInfo  );
	 
	 if  (  qnmOpenSession(  pQwm->server.ip,  pQwm->server.port,  &macsInfo,  0,  pQwm->iServiceId,  pQwm->ver,  &pQwm->commEncCtx,  &session,  &sock,  &pQwm->cfg.to,  NULL,  NULL  )  )  goto  errLabel;
	 bSessionOpen		=		TRUE;
	 if  (  !isRcOk(  session.usLastRespCode  )  )  goto  errLabel;

	 if  (  qySendReq(  &session,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_tryToConnectToServer,  NULL,  0  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &session,  &sock,  &pQwm->cfg.to,  &tmpResp,  NULL,  0  )  )  goto  errLabel;
	 if  (  !isRcOk(  tmpResp.head.usCode  )  )  goto  errLabel;

	 bRet  =  TRUE;

errLabel:

	 if  (  bSessionOpen  )  qnmCloseSession(  &session,  &sock,  &pQwm->cfg.to  );

	 return  bRet;

}
*/


 int  savePcNetworkPropInReg(  QY_W_MON  *  pQwm,  QY_PCNETWORK_INFOU  *  pInfo    )
{
	 int	iErr		=	-1;
	 TCHAR	buf[512]	=	_T(  ""  );

	 traceLogA(  "savePcNetworkPropInReg enters"  );

	 switch  (  pInfo->uiType  )  {
			 case  CONST_pcNetworkPropType_adapter:
				   myStr2TChar(  pInfo->adapter.devIdStr,  buf,  mycountof(  buf  )  );
				   qySetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywDevIdStr  ),  buf  );
				   _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%d"  ),  pInfo->adapter.devIndex  );
				   qySetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywDevIndex  ),  buf  );
				   myStr2TChar(  pInfo->adapter.mac,  buf,  mycountof(  buf  )  );
				   qySetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywMac  ),  buf  );
				   myStr2TChar(  pInfo->adapter.ipBuf,  buf,  mycountof(  buf  )  );
				   qySetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywIp  ),  buf  );
				   myStr2TChar(  pInfo->adapter.ipMaskBuf,  buf,  mycountof(  buf  )  );
				   qySetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywIpMask  ),  buf  );
				   myStr2TChar(  pInfo->adapter.gatewayBuf,  buf,  mycountof(  buf  )  );
				   qySetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywGateway  ),  buf  );
				   qySetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywUcbDhcpEnabled  ),  pInfo->adapter.ucbDhcpEnabled  ?  _T(  "1"  )  :  _T(  "0"  )  );
				   myStr2TChar(  pInfo->adapter.dnsBuf,  buf,  mycountof(  buf  )  );
				   qySetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywDns  ),  buf  );
				   _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%d"  ),  pInfo->uiType  );
				   qySetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywPcNetworkPropType  ),  buf  );
	 }

	 iErr  =  0;
//  errLabel:

	 traceLogA(  "savePcNetworkPropInReg leaves"  );

	 return  iErr;
}

 int  clearPcNetworkPropInReg(  QY_W_MON  *  pQwm  )
{
	 char	buf[512];

	 traceLogA(  "clearPcNetworkPropInReg enters"  );

	 if  (  !qyGetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywPcNetworkPropType  ),  buf,  sizeof(  buf  )  )  )  {
		 qyDelRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywDevIdStr  )  );
		 qyDelRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywDevIndex  )  );
		 qyDelRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywMac  )  );
		 qyDelRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywIp  )  );
		 qyDelRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywIpMask  )  );
		 qyDelRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywGateway  )  );
		 qyDelRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywUcbDhcpEnabled  )  );
		 qyDelRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywDns  )  );
		 qyDelRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywPcNetworkPropType  )  );
	 }


	 traceLogA(  "clearPcNetworkPropInReg leaves"  );

	 return  0;
}

 int  getPcNetworkPropInReg(  QY_W_MON  *  pQwm,  QY_PCNETWORK_INFOU  *  pInfo  )
{
	 TCHAR	buf[512];

	 if  (  qyGetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywPcNetworkPropType  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
	 pInfo->uiType  =  _ttol(  buf  );
	 switch  (  pInfo->uiType  )  {
			 case  CONST_pcNetworkPropType_adapter:
				   if  (  qyGetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywDevIdStr  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
				   myTChar2Str(  buf,  pInfo->adapter.devIdStr,  sizeof(  pInfo->adapter.devIdStr  )  );
				   if  (  qyGetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywDevIndex  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
				   pInfo->adapter.devIndex  =  _ttol(  buf  );
				   if  (  qyGetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywMac  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
				   myTChar2Str(  buf,  pInfo->adapter.mac,  sizeof(  pInfo->adapter.mac  )  );
				   if  (  qyGetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywIp  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
				   myTChar2Str(  buf,  pInfo->adapter.ipBuf,  sizeof(  pInfo->adapter.ipBuf  )  );
				   if  (  qyGetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywIpMask  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
				   myTChar2Str(  buf,  pInfo->adapter.ipMaskBuf,  sizeof(  pInfo->adapter.ipMaskBuf  )  );
				   if  (  qyGetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywGateway  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
				   myTChar2Str(  buf,  pInfo->adapter.gatewayBuf,  sizeof(  pInfo->adapter.gatewayBuf  )  );
				   if  (  qyGetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywUcbDhcpEnabled  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
				   pInfo->adapter.ucbDhcpEnabled  =  _ttol(  buf  )  ?  TRUE  :  FALSE;
				   if  (  qyGetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywDns  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
				   myTChar2Str(  buf,  pInfo->adapter.dnsBuf,  sizeof(  pInfo->adapter.dnsBuf  )  );
				   break;
			 default:
					break;
					
	 }

	 return  0;
}

 BOOL  bPcNetworkPropNeedRecover(  )
{
	 TCHAR	buf[32];
	 
	 if  (  qyGetRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywNeedRecover  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  buf[0]  =  0;
	 return  _ttol(  buf  )  ?  TRUE  :  FALSE;
}

 int  clearNeedRecoverFlg(  )
{
	 traceLogA(  "clearNeedRecoverFlg enters"  );

	 qyDelRegCfg(  _T(  CONST_qyKey_qwm  ),  _T(  CONST_regValName_ywNeedRecover  )  );

	 traceLogA(  "clearNeedRecoverFlg leaves"  );

	 return  0;
}


#if  0
 int  willReboot(  QY_W_MON  *  pQwm  )
{
	 int		iErr					=	-1;
	 HANDLE		hProcess				=	NULL;
	 TCHAR		buf[32]					=	_T(  ""  );
	 BOOL		bProcessCreated			=	FALSE;
	 DWORD		dwExitCode				=	-1;

	 showQwmSvrStatus(  &pQwm->env,  pQwm->server.ip,  pQwm->server.port,  pQwm->iServiceId,  pQwm->ver,  &pQwm->commEncCtx,  &pQwm->cfg.to,  CONST_qwmSvrStatus_needReboot,  0  );

	 _sntprintf(  buf,  mycountof(  buf  ),  _T(  ""  )  );
	 if  (  qwmCmdBySubProcess(  0,  _T(  CONST_qwmCmdLine_doReboot  ),  buf,  &hProcess  )  )  goto  errLabel;
	 bProcessCreated  =  TRUE;

	 iErr  =  0;
errLabel:

	 if  (  bProcessCreated  )  {
		 ::WaitForSingleObject(  hProcess,  INFINITE  );
		 if  (  !GetExitCodeProcess(  hProcess,  &dwExitCode  )  )  dwExitCode  =  -1;
		 CloseHandle(  hProcess  );
	 }

	 return  iErr  ?  iErr  :  dwExitCode;

}
#endif

  //  对某些修改行为，仍然需要用避免再一次的重起来恢复。当需要qwmSvr也同样退出运行时，请返回1
 int  procPcNetworkPropChangeAtStart(  QY_W_MON  *  pQwm  )
{
	 int					iErr							=	-1;
	 
	 clearPcNetworkPropInReg(  pQwm  );	//  在重起之后，必须清理掉保存信息，避免进入死循环
	 clearNeedRecoverFlg(  );

	 iErr  =  0;

	 return  iErr;

}

  //
  int  tmpHandler_testAdapterOk(  void  *  pCommonParam1,  void  *  p1,  void  *  pAdapterInfoParam  )
{
	 int					iErr				=	-1;
	 COMMON_PARAM		*	pCommonParam		=	(  COMMON_PARAM  *  )pCommonParam1;
	 QY_W_MON			*	pQwm				=	(  QY_W_MON  *  )pCommonParam->p0;
	 QY_PCNETWORK_INFOU	*	pCurPcNetworkInfo	=	(  QY_PCNETWORK_INFOU  *  )pCommonParam->p1;
	 BOOL				*	pbAdapterOk			=	(  BOOL  *  )pCommonParam->p2;
	 QY_PCADAPTER_INFO	*	pAdapterInfo		=	(  QY_PCADAPTER_INFO  *  )pAdapterInfoParam;

	 if  (  strcmpi(  pAdapterInfo->mac,  pCurPcNetworkInfo->adapter.mac  )  )  {
		 iErr  =  0;  goto  errLabel;
	 }
	 if  (  bIpValid(  pAdapterInfo->ipBuf  )  )  *pbAdapterOk  =  TRUE;

	 iErr  =  0;
errLabel:
	 return  iErr;
}


 BOOL  bAdapterOk(  QY_W_MON  *  pQwm,  unsigned  int  uiMinSeconds  )
{
	 BOOL					bRet  =  FALSE;
	 BOOL					bOk  =  FALSE;
	 unsigned  int			i;
	 COMMON_PARAM			commonParam;

	 if  (  !g_bIsWinNT  ||  pQwm->env.iPlatformId  ==  CONST_qyPlatform_nt  )  {
		 for  (  i  =  0;  i  <  20;  i  ++,  Sleep(  1000  )  )  {
			  if  (  pQwm->bQuit  )  goto  errLabel;
		 }
		 bRet  =  TRUE;  goto  errLabel;
	 }

	 MACRO_makeCommonParam3(  pQwm,  &pQwm->cfg.curPcNetworkInfo,  &bOk,  commonParam  );
	 for  (  i  =  0;  i  <  600  &&  !bOk;  i  ++,  Sleep(  1000  )  )  {
		  if  (  pQwm->bQuit  )  goto  errLabel;
	 	  enumPcAdaptersByIpHlp(  NULL,  &pQwm->env,  tmpHandler_testAdapterOk,  &commonParam,  NULL  );
	 }
	 if  (  !bOk  )  goto  errLabel;
	 
	 for  (  ;  i  <  uiMinSeconds;  i  ++,  Sleep(  1000  )  )  {
		  if  (  pQwm->bQuit  )  goto  errLabel;
	 }

	 bRet  =  TRUE;

errLabel:

	 if  (  bRet  )  traceLogA(  "等了%d秒后，网卡恢复",  i  );
	 else  traceLogA(  "坏了，等了%d秒，网卡仍然无效",  i  );

	 return  bRet;

}


 int  procPcNetworkPropChange(  void  *  lpParameter  )
{
	 int								iErr			=	-1;
	 QY_W_MON						*	pQwm			=	(  QY_W_MON  *  )lpParameter;
	 QWM_THREADINFO						threadInfo;
	 QWM_THREAD_CFG						threadCfg;
	 void							*	p0				=	&threadInfo;
	 void							*	p1				=	&pQwm->procDevStruct;
	 void							*	p2				=	NULL;
	 unsigned  char						ucbSaved		=	FALSE;
	 QNM_CMDPARAM_showQwmSvrStatus		statusDetail;
	 int								i;
	 
	 if  (  !pQwm->cfg.ucbPcNetworkPropWillChange  )  return  0;

	 traceLogA(  "procPcNetworkPropChanged enters"  );
	 
	 memset(  &threadInfo,  0,  sizeof(  threadInfo  )  );
	 memset(  &threadCfg,  0,  sizeof(  threadCfg  )  );
	 threadInfo.pParaentParam  =  pQwm;
	 threadInfo.pCfg  =  &threadCfg;

	 memset(  &statusDetail,  0,  sizeof(  statusDetail  )  );
	 _snprintf(  statusDetail.progressTxt,  sizeof(  statusDetail.progressTxt  ),  "%s",  qyGetDesByType1(  CONST_pcCommTypeTable_en,  pQwm->cfg.curPcNetworkInfo.uiType  )  ); 
	 showQwmSvrStatus(  &pQwm->env,  pQwm->server.ip,  pQwm->server.port,  pQwm->iServiceId,  pQwm->ver,  &pQwm->commEncCtx,  &pQwm->cfg.to,  CONST_qwmSvrStatus_pcNetworkPropWillChange,  &statusDetail  );

	 if  (  pQwm->cfg.curPcNetworkInfo.uiType  !=  CONST_pcNetworkPropType_adapter  )  {
		 if  (  changePcNetworkProp(  &threadInfo  )  )  goto  errLabel;
		 iErr  =  0;  goto  errLabel;
	 }

	 pQwm->procDevStruct.ucbNeedReboot		=  FALSE;
	 pQwm->procDevStruct.ucbNeedRecover		=  FALSE;

	 //  确保服务器连接通畅，保存有效现场
	 if  (  !bServConnected(  &pQwm->env,  pQwm->server.ip,  pQwm->server.port,  0,  pQwm->iServiceId,  pQwm->ver,  &pQwm->commEncCtx,  &pQwm->cfg.to  )  )  goto  errLabel;
	 if  (  savePcNetworkPropInReg(  pQwm,  &pQwm->cfg.curPcNetworkInfo  )  )  goto  errLabel;
	 ucbSaved  =  TRUE;

	 if  (  changePcNetworkProp(  &threadInfo  )  )  goto  errLabel;

	 /*		//  2005/11/27, 暂时在这里避免重起的动作，在98的修改网卡，也是改完就停止了, 等重起了再继续
	 if  (  pQwm->procDevStruct.ucbNeedReboot  )  {
		 traceLogA(  "做一个重起的动作"  );  
		 willReboot(  pQwm  );
		 iErr  =  0;  goto  errLabel;
	 }
	 */

	 traceLogA(  "等待为了让mac恢复，在网卡禁掉时MAC会暂时的失效"  );
	 if  (  !bAdapterOk(  pQwm,  0  )  )  goto  errLabel;
	 traceLogA(  "等待结束, 下面测试与服务器是否相连"  );

	 //  对不需重起的工作:
	 //		 检测服务器连接是否通畅，如是，则清除保存；如否，则恢复现场，清除保存
#define		CONST_maxConnectToServTimes		15
	 for  (  i  =  0;  i  <  CONST_maxConnectToServTimes;  i  ++  )  {
		  if  (  bServConnected(  &pQwm->env,  pQwm->server.ip,  pQwm->server.port,  0,  pQwm->iServiceId,  pQwm->ver,  &pQwm->commEncCtx,  &pQwm->cfg.to  )  )  break;
		  Sleep(  2000  );
	 }
	 traceLogA(  "共连接服务器%d次",  i  );
	 if  (  i  ==  CONST_maxConnectToServTimes  )  {
		 traceLogA(  "新的网卡设置导致连不上管理端，是错误的设置，将恢复原来的设置"  );
		 pQwm->procDevStruct.ucbNeedRecover  =  TRUE;
		 memcpy(  &pQwm->cfg.newPcNetworkProp.adapter,  &pQwm->cfg.curPcNetworkInfo.adapter,  sizeof(  pQwm->cfg.newPcNetworkProp.adapter  )  );
		 if  (  changePcNetworkProp(  &threadInfo  )  )  goto  errLabel;

		 traceLogA(  "等待为了让mac恢复，在网卡禁掉时MAC会暂时的失效"  );
		 if  (  !bAdapterOk(  pQwm,  60  )  )  goto  errLabel;
		 traceLogA(  "等待结束"  );
		 
		 showQwmSvrStatus(  &pQwm->env,  pQwm->server.ip,  pQwm->server.port,  pQwm->iServiceId,  pQwm->ver,  &pQwm->commEncCtx,  &pQwm->cfg.to,  CONST_qwmSvrStatus_recoverPcNetworkPropForErr,  0  );
		 showPcNetworkPropStatus(  pQwm,  &pQwm->cfg.newPcNetworkProp,  CONST_ucFlg_err  );
	 }

	 clearPcNetworkPropInReg(  pQwm  );
	 iErr  =  0;
	   
errLabel:

	 if  (  iErr  )  {
		 if  (  ucbSaved  )  clearPcNetworkPropInReg(  pQwm  );
	 }

	 //  if  (  !pQwm->procDevStruct.ucbNeedReboot  )  pQwm->cfg.ucbPcNetworkPropWillChange  =  FALSE;
	 pQwm->cfg.ucbPcNetworkPropWillChange  =  FALSE;
	 pQwm->procDevStruct.ucbNeedRecover		=  FALSE;

	 showQwmSvrStatus(  &pQwm->env,  pQwm->server.ip,  pQwm->server.port,  pQwm->iServiceId,  pQwm->ver,  &pQwm->commEncCtx,  &pQwm->cfg.to,  CONST_qwmSvrStatus_pcNetworkPropChangeFinished,  &statusDetail  );
	 
	 traceLogA(  "procPcNetworkPropChanged leaves, ucbPcNeedReboot is %d, ucbPcNetworkPropWillChanged is %d",  pQwm->procDevStruct.ucbNeedReboot,  pQwm->cfg.ucbPcNetworkPropWillChange  );

	 return  0;

}


 int  changePcNetworkProp(  QWM_THREADINFO  *  pSubThreadInfo  )
{
	 int					iErr			=	0;
	 QY_W_MON			*	pQwm			=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	 void				*	p0				=	pSubThreadInfo;
	 void				*	p1				=	&pQwm->procDevStruct;
	 void				*	p2				=	NULL;

	 traceLogA(  "changePcNetworkProp enters"  );

	 switch  (  pQwm->env.iPlatformId  )  {
			 case  CONST_qyPlatform_nt:
				   //  pQwm->procDevStruct.ucbNeedReboot  =  TRUE;
				   procPcNetworkPropChange_nt(  pSubThreadInfo  );
				   break;
			 default:
				     switch  (  pQwm->cfg.curPcNetworkInfo.uiType  )  {
							 case  CONST_pcNetworkPropType_adapter:
	  			     	 		   if  (  !g_bIsWinNT  )  enumDevices(  &pQwm->env,  (  LPGUID  )&GUID_CLASS_NET,  p0,  p1,  tmpHandler_changePcNetworkProp_98  );  							 
						 		   else  enumDevices(  &pQwm->env,  (  LPGUID  )&GUID_CLASS_NET,  p0,  p1,  tmpHandler_changePcNetworkProp  );  
								   break;
							 case  CONST_pcNetworkPropType_proxy:
								   if  (  changeProxyCfg(  pSubThreadInfo  )  )  goto  errLabel;
								   break;
							 case  CONST_pcNetworkPropType_computer:
								   if  ( changePcComputer(  pSubThreadInfo  )  )  goto  errLabel;								   
								   break;
							 case  CONST_pcCommType_windowsUpdatePolicy:		//  2006/05/23
								   if  (  changeQwmWindowsUpdatePolicy(  pSubThreadInfo  )  )  goto  errLabel;
								   break;
							 default:	traceLogA(  "需要修改未知类型的计算机属性, %d",  pQwm->cfg.curPcNetworkInfo.uiType  );
										goto  errLabel;
					 }
					 break;
	 }

	 iErr  =  0;

errLabel:		

	 traceLogA(  "changePcNetworkProp leaves"  );

	 return  iErr;
}


 int  tmpHandler_interruptNetworkCard_getDevId(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int					iErr			=	-1;
	 MIB_IFROW			*	pIfRow			=	(  MIB_IFROW  *  )p0;
	 QY_PCADAPTER_INFO	*	pMyAdapterInfo	=	(  QY_PCADAPTER_INFO  *  )p1;
	 QY_PCADAPTER_INFO	*	pPcAdapterInfo	=	(  QY_PCADAPTER_INFO  *  )p2;

	 if  (  pIfRow->dwIndex  ==  pPcAdapterInfo->uiAdapterIndex  )  {
		 memcpy(  pMyAdapterInfo,  pPcAdapterInfo,  sizeof(  pMyAdapterInfo[0]  )  );
		 iErr  =  1;  goto  errLabel;
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}

 int  tmpHandler_interruptNetworkCard(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int						iErr					=	-1;
	QWM_THREADINFO		*	pSubThreadInfo			=	(  QWM_THREADINFO  *  )p0;
	COMMON_PARAM		*	pCommonParam1			=	(  COMMON_PARAM  *  )p1;
	QNM_DEV_INFO		*	pQnmDevInfo				=	(  QNM_DEV_INFO  *  )p2;
	//
	QY_W_MON			*	pQwm					=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	QY_PCADAPTER_INFO	*	pPcAdapterInfo			=	(  QY_PCADAPTER_INFO  *  )pCommonParam1->p0;
	unsigned  int			nSeconds				=	(  unsigned  int  )pCommonParam1->p1;
	BOOL					bDisableForever			=	FALSE;

	if  (  nSeconds  ==  -1  )  {
		bDisableForever  =  TRUE;
		traceLog(  _T(  "tmpHandler_interruptNetworkcard: disable %S for ever"  ),  pPcAdapterInfo->connectionName  );
		}
	else  {
		  if  (  nSeconds  >  3600  )  {
			  traceLogA(  "tmpHandler_interruptNetworkCard(  ):  nSeconds is %d",  nSeconds  );  nSeconds  =  3600;
		  }
	}

	if  (  !stricmp(  pPcAdapterInfo->devIdStr,  pQnmDevInfo->devIdStr  )  )  {	//  注意，这里，暂停网卡应是个原子动作，不要中间退出。要保证网卡被恢复
		CONTROL_DEV_PARAM	controlParam;
		int					i;

		memset(  &controlParam,  0,  sizeof(  controlParam  )  );
			
		traceLogA(  "to disable %s %s",  pPcAdapterInfo->connectionName,  pPcAdapterInfo->mac  );
				
		controlParam.dwControl  =  DICS_DISABLE;
		if  (  controlCallback(  p0,  &controlParam,   p2  )  )  {
			traceLogA(  "disable networkcard failed"  );  goto  errLabel;
		}

		if  (  bDisableForever  )  {
			iErr  =  1;  goto  errLabel;
		}
		//
		for  (  i  =  0;  i  <  (  int  )nSeconds  &&  !pQwm->bQuit;  i  ++  )  {
			 Sleep(  1000  );
		}

		//
		controlParam.dwControl  =  DICS_ENABLE;
		if  (  controlCallback(  p0,  &controlParam, p2  )  )  {
			traceLogA(  "recover networkcard failed"  );  goto  errLabel;
		}		
		traceLogA(  "recover networkcard ok"  );

		iErr  =  1;  goto  errLabel;
	}

	iErr  =  0;

errLabel:
	return  iErr;
}


 int  interruptNetworkCard(  QWM_THREADINFO  *  pThreadInfo,  MIB_IFROW  *  pIfRow,  unsigned  int  nSeconds  )
{
	 int					iErr				=	-1;
	 QY_W_MON			*	pQwm				=	(  QY_W_MON  *  )pThreadInfo->pParaentParam;
	 COMMON_PARAM			commonParam1;
	 QY_PCADAPTER_INFO		pcAdapterInfo;

	 //  首先要得到通过pIfRow->index得到devIp
	 if  (  enumPcAdaptersByIpHlp(  0,  &pQwm->env,  tmpHandler_interruptNetworkCard_getDevId,  pIfRow,  &pcAdapterInfo  )  <=  0  )  {
		 traceLogA(  "interruptNetworkCard: 得到devId失败"  );  goto  errLabel;  
	 }

	 MACRO_makeCommonParam3(  &pcAdapterInfo,  (  void  *  )nSeconds,  0,  commonParam1  );
	 enumDevices(  &pQwm->env,  (  LPGUID  )&GUID_CLASS_NET,  pThreadInfo,  &commonParam1,  tmpHandler_interruptNetworkCard  );  

	 iErr  =  0;
errLabel:
	 return  iErr;
}


 int  tmpHandler_showPcAdapter(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int				iErr			=	-1;
	 COMMON_PARAM	*	pCommonParam	=	(  COMMON_PARAM  *  )p0;
	 QNM_DEV_INFO	*	pQnmDevInfo		=	(  QNM_DEV_INFO  *  )p2;
	 QY_W_MON		*	pQwm			=	(  QY_W_MON  *  )pCommonParam->p0;
	 QWM_SESSION	*	pSession		=	(  QWM_SESSION  *  )pCommonParam->p1;
	 QY_SOCK		*	pSock			=	(  QY_SOCK  *  )pCommonParam->p2;

	 //  还要取对应的网络状态信息
	 if  (  !g_bIsWinNT  )  iErr  =  get98AdapterInfo(  p0,  p1,  p2  );
	 else  iErr  =  enumPcAdaptersByIpHlp(  NULL,  &pQwm->env,  tmpHandler_sndPcNetworkProp,  p0,  pQnmDevInfo  );

	 return  iErr;
}



 int  showPcAdapters(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int				iErr			=	-1;
	 COMMON_PARAM	*	pCommonParam	=	(  COMMON_PARAM  *  )p0;
	 QY_W_MON		*	pQwm			=	(  QY_W_MON  *  )pCommonParam->p0;
	 QWM_SESSION	*	pSession		=	(  QWM_SESSION  *  )pCommonParam->p1;
	 QY_SOCK		*	pSock			=	(  QY_SOCK  *  )pCommonParam->p2;

	 traceLogA(  "showPcAdapters enters"  );

	 switch  (  pQwm->env.iPlatformId  )  {
			 case  CONST_qyPlatform_nt:
				   traceLogA(  "nt is not supported now"  );  
				   if  (  procNtPcAdapters(  p0,  p1,  p2  )  )  goto  errLabel;
				   break;
			 default:
				     if  (  enumDevices(  &pQwm->env,  (  LPGUID  )&GUID_CLASS_NET,  p0,  p1,  tmpHandler_showPcAdapter  )  )  goto  errLabel;
					 break;
		}
	 iErr  =  0;
errLabel:

	 traceLogA(  "showPcAdapters leaves with %s",  iErr  ?  "失败"  :  "成功"  );

	 return  iErr;
}


 int  enumDevices(  QY_ENV  *  pEnv,  LPGUID lpGuid,  void  *  p0,  void  *  p1,  PF_commonHandler  handler  )
{
	int					iErr		=	-1;
    HDEVINFO			hDevInfoSet =	INVALID_HANDLE_VALUE;
    DWORD				devIndex;
    SP_DEVINFO_DATA		devInfo;
	QWM_DYN_LIB		*	pDynLib		=	(  QWM_DYN_LIB  *  )pEnv->pDynLibs;

	if  (  !bSetupApiOk(  pDynLib  )  )  return  -1;
	
	// 取得一个该GUID相关的设备信息集句柄
	hDevInfoSet = pDynLib->pSetupDiGetClassDevs(lpGuid, 	// class GUID 
			NULL,									// 无关键字 
			NULL,									// 不指定父窗口句柄 
			DIGCF_PRESENT );	// 目前存在的设备
	// 失败...
	if(hDevInfoSet == INVALID_HANDLE_VALUE)  goto  errLabel;


	devInfo.cbSize = sizeof(devInfo);
    for  (  devIndex=0;  pDynLib->pSetupDiEnumDeviceInfo(hDevInfoSet,devIndex,&devInfo);devIndex++) {
		 TCHAR				tmpBuf[1024];
		 QNM_DEV_INFO		qnmDevInfo;

		 memset(  &qnmDevInfo,  0,  sizeof(  qnmDevInfo  )  );
		 qnmDevInfo.hDevs		=	hDevInfoSet;
		 qnmDevInfo.pDevInfo	=	&devInfo;
		 qnmDevInfo.index		=	devIndex;
		 
		 //
		 // determine instance ID
		 //
		 if  (  pDynLib->pCM_Get_Device_ID(  devInfo.DevInst,  tmpBuf,  mycountof(  tmpBuf  ),  0  )  !=  CR_SUCCESS  )  tmpBuf[0]  =  0;
		 myTChar2Utf8(  tmpBuf,  qnmDevInfo.devIdStr,  mycountof(  qnmDevInfo.devIdStr  )  );
                
		 //  getDeviceDescription(  pEnv,  hDevInfoSet,  &devInfo,  qnmDevInfo.devDesc,  sizeof(  qnmDevInfo.devDesc  )  );
		 getDeviceDescription(  pEnv,  hDevInfoSet,  &devInfo,  tmpBuf,  mycountof(  tmpBuf  )  );
		 myTChar2Utf8(  tmpBuf,  qnmDevInfo.devDesc,  mycountof(  qnmDevInfo.devDesc   )  );
		
		 ULONG  ulStatus		=	0;
		 ULONG  ulProblemNumber	=	0;    
		 //  IN DEVINST  dnDevInst,    
		 ULONG  ulFlags			=	0;
		 if  (  pDynLib->pCM_Get_DevNode_Status(  &ulStatus,  &ulProblemNumber,  devInfo.DevInst,  ulFlags  )  !=  CR_SUCCESS  )  {
			 ulStatus  =  0;
			 ulProblemNumber  =  0;
		 }
		 qnmDevInfo.ulStatus  =  ulStatus;
		 qnmDevInfo.ulProblemNumber  =  ulProblemNumber;

		 if  (  handler  &&  handler(  p0,  p1,  &qnmDevInfo  )  )  goto  errLabel;
	}

	iErr  =  0;

errLabel:
	if  (  hDevInfoSet  !=  INVALID_HANDLE_VALUE  )  pDynLib->pSetupDiDestroyDeviceInfoList(hDevInfoSet);
    
    return  iErr;
}

 int  enumDevInterfaces(  QY_ENV  *  pEnv,  LPGUID lpGuid,  void  *  p0,  void  *  p1,  PF_commonHandler  handler  )
{
	int					iErr		=	-1;
    HDEVINFO			hDevInfoSet =	INVALID_HANDLE_VALUE;
    DWORD				devIndex;
    SP_DEVINFO_DATA		devInfo;
	QWM_DYN_LIB		*	pDynLib		=	(  QWM_DYN_LIB  *  )pEnv->pDynLibs;

	if  (  !bSetupApiOk(  pDynLib  )  )  return  -1;
	
	// 取得一个该GUID相关的设备信息集句柄
	hDevInfoSet = pDynLib->pSetupDiGetClassDevs(lpGuid, 	// class GUID 
			NULL,									// 无关键字 
			NULL,									// 不指定父窗口句柄 
			DIGCF_PRESENT | DIGCF_DEVICEINTERFACE);	// 目前存在的设备
	// 失败...
	if(hDevInfoSet == INVALID_HANDLE_VALUE)  goto  errLabel;


	devInfo.cbSize = sizeof(devInfo);
    for  (  devIndex=0;  pDynLib->pSetupDiEnumDeviceInfo(hDevInfoSet,devIndex,&devInfo);devIndex++) {
		 TCHAR				tmpBuf[1024];
		 QNM_DEV_INFO		qnmDevInfo;

		 memset(  &qnmDevInfo,  0,  sizeof(  qnmDevInfo  )  );
		 qnmDevInfo.hDevs		=	hDevInfoSet;
		 qnmDevInfo.pDevInfo	=	&devInfo;
		 qnmDevInfo.index		=	devIndex;
		 
		 //
		 // determine instance ID
		 //
		 //  if  (  pDynLib->pCM_Get_Device_ID(  devInfo.DevInst,  qnmDevInfo.devIdStr,  sizeof(  qnmDevInfo.devIdStr  ),  0  )  !=  CR_SUCCESS  )  qnmDevInfo.devIdStr[0]  =  0;
		 if  (  pDynLib->pCM_Get_Device_ID(  devInfo.DevInst,  tmpBuf,  mycountof(  tmpBuf  ),  0  )  !=  CR_SUCCESS  )  tmpBuf[0]  =  0;
		 myTChar2Utf8(  tmpBuf,  qnmDevInfo.devIdStr,  mycountof(  qnmDevInfo.devIdStr  )  );
              
		 //	 getDeviceDescription(  pEnv,  hDevInfoSet,  &devInfo,  qnmDevInfo.devDesc,  sizeof(  qnmDevInfo.devDesc  )  );
		 getDeviceDescription(  pEnv,  hDevInfoSet,  &devInfo,  tmpBuf,  mycountof(  tmpBuf  )  );
		 myTChar2Utf8(  tmpBuf,  qnmDevInfo.devDesc,  mycountof(  qnmDevInfo.devDesc  )  );
		 //  _sntprintf(  tmpBuf,  mycountof(  tmpBuf  ),  _T(  "devID is %s, device is %s\n"  ),  tmpBuf2,  tmpBuf  );
		 //  OutputDebugString(  tmpBuf  );
		 //  AfxMessageBox(  tmpBuf  );
		 {
			 SP_DEVICE_INTERFACE_DATA								ifdata;
			 char													interfaceDetailBuf[1024];
			 PSP_DEVICE_INTERFACE_DETAIL_DATA						pDetail		=	(  PSP_DEVICE_INTERFACE_DETAIL_DATA  )interfaceDetailBuf;
			 int													nCount		=	0;

			 pDetail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);
			 for  (  nCount  =  0;  ;  nCount  ++  )  {
				  ifdata.cbSize=sizeof(ifdata);
	  			  if  (  !pDynLib->pSetupDiEnumDeviceInterfaces(  hDevInfoSet,  &devInfo,  lpGuid,  (ULONG)nCount,  &ifdata  )  )  break;
				  if  (  !pDynLib->pSetupDiGetDeviceInterfaceDetail(  hDevInfoSet,  &ifdata,  pDetail,  sizeof(  interfaceDetailBuf  ),  NULL,  NULL  )  )  {
					  qyDisplayLastError(  "enumDevInterfaces: SetupDiGetDeviceInterfaceDetail failed"  );
					  }
				  else  {
					    myTChar2Utf8(  pDetail->DevicePath,  qnmDevInfo.devicePath,  mycountof(  qnmDevInfo.devicePath  )  );						
				  }
				  if  (  handler  )  handler(  p0,  p1,  &qnmDevInfo  );
			 }		 	
		 }
	}

	iErr  =  0;

errLabel:
	if  (  hDevInfoSet  !=  INVALID_HANDLE_VALUE  )  pDynLib->pSetupDiDestroyDeviceInfoList(hDevInfoSet);
    
    return  iErr;
}


/*++

Routine Description:

    Return a string property for a device, otherwise NULL

Arguments:

    Devs    )_ uniquely identify device
    DevInfo )
    Prop     - string property to obtain

Return Value:

    string containing description

--*/
 TCHAR  *  getDeviceStringProperty(  QY_ENV  *  pEnv,  HDEVINFO Devs,PSP_DEVINFO_DATA DevInfo,DWORD Prop,  TCHAR  *  buffer,  unsigned  int  size  )
{
	int				iErr		=	-1;
    DWORD			reqSize;
    DWORD			dataType;
	QWM_DYN_LIB	*	pDynLib	=	(  QWM_DYN_LIB  *  )pEnv->pDynLibs;

    if  (  !buffer  ||  !size  ) return  NULL;
    
	size  =  size  *  sizeof(  TCHAR  );
    if  (  !pDynLib->pSetupDiGetDeviceRegistryProperty(Devs,DevInfo,Prop,&dataType,(LPBYTE)buffer,size,&reqSize  )  ) {
        if  (  GetLastError() == ERROR_INSUFFICIENT_BUFFER  )  OutputDebugString(  _T(  "insufficient buffer"  )  );
		goto  errLabel;
	}        
	if  (  dataType  !=  REG_SZ  )  goto  errLabel;
	if  (  size  <  reqSize  +  1  )  goto  errLabel;
    buffer[reqSize  /  sizeof(  TCHAR  )]  =  0;

	iErr  =  0;
errLabel:
    return  iErr  ?  NULL  :  buffer;
}



/*++

Routine Description:

    Return a string containing a description of the device, otherwise NULL
    Always try friendly name first

Arguments:

    Devs    )_ uniquely identify device
    DevInfo )

Return Value:

    string containing description

--*/
 TCHAR  *  getDeviceDescription(  QY_ENV  *  pEnv,  HDEVINFO Devs,PSP_DEVINFO_DATA DevInfo,  TCHAR  *  buffer,  unsigned  int  size  )
{
    LPTSTR desc	=	NULL;

    desc = getDeviceStringProperty(  pEnv,  Devs,DevInfo,SPDRP_FRIENDLYNAME,  buffer,  size  );
    if(!desc) {
        desc = getDeviceStringProperty(  pEnv,  Devs,DevInfo,SPDRP_DEVICEDESC,  buffer,  size  );
    }
    return  desc;
}

 int  tmpHandler_bUsbStor(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int						iErr			=	-1;
	BOOL					bRet			=	FALSE;
	QWM_THREADINFO		*	pSubThreadInfo  =	(  QWM_THREADINFO  *  )p0;
	QY_W_MON			*	pQwm			=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	WCHAR				*	wDevIdStr		=	(  WCHAR  *  )p1;
	QY_PC_REGISTRYVAL	*	pVal			=	(  QY_PC_REGISTRYVAL  *  )p2;

	if  (  pVal->iValType  ==  REG_SZ  )  {
		traceLogA(  "val is %S",  pVal->u.wCfgVal  );
		if  (  !wcsicmp(  wDevIdStr,  pVal->u.wCfgVal  )  )  {
			iErr  =  1;  goto  errLabel;
		}
	}	

	iErr  =  0;
errLabel:
	return  iErr;
}

 BOOL  bUsbStor(  void  *  p0,  char  *  devIdStr,  char  *  devDesc  )
{
	BOOL					bRet				=	FALSE;
	QWM_THREADINFO		*	pSubThreadInfo		=	(  QWM_THREADINFO  *  )p0;
	QY_W_MON			*	pQwm				=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	WCHAR					wDevIdStr[512]		=	L"";
	int						iRet				=	-1;

	
	if  (  !devIdStr  ||  !devDesc  )  goto  errLabel;

	traceLogA(  "devId is %s",  devIdStr  );

	if  (  !myStr2WChar(  devIdStr,  wDevIdStr,  mycountof(  wDevIdStr  )  )  )  goto  errLabel;

	iRet  =  enumReg(  &pQwm->env,  0,  HKEY_LOCAL_MACHINE,  L"SYSTEM\\CurrentControlSet\\Services\\USBSTOR\\Enum",  tmpHandler_bUsbStor,  pQwm,  wDevIdStr  );
	if  (  iRet  <=  0  )  goto  errLabel;	//  表明没找着

	bRet  =  TRUE;

errLabel:
	 return  bRet;
}


 //  2005/10/07, 对removeCallback做了限制，使只移除mass storage device, 从而不影响USB鼠标、键盘等
 int  removeMassStorCallback(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int						iErr			=	-1;
	QWM_THREADINFO		*	pSubThreadInfo  =	(  QWM_THREADINFO  *  )p0;
	PROC_DEV_STRUCT		*	pProcDevStruct	=	(  PROC_DEV_STRUCT  *  )p1;
	QNM_DEV_INFO		*	pQnmDevInfo		=	(  QNM_DEV_INFO  *  )p2;
	//  HDEVINFO				Devs			=	(  HDEVINFO  )pQnmDevInfo->hDevs;
	//  PSP_DEVINFO_DATA		DevInfo			=	(  PSP_DEVINFO_DATA  )pQnmDevInfo->pDevInfo;
	//  DWORD					Index			=	(  DWORD  )pQnmDevInfo->index;
	//  char				*	p;
	//  char				*	pStorSym		=	"Storage";		//  有的是Mass Storage, 有的是USB AutoRun Storage
	//  int						len				=	strlen(  pStorSym  );

	traceLogA(  "removeMassStorCallback enters, devId is %s,  devDesc is %s",  pQnmDevInfo->devIdStr,  pQnmDevInfo->devDesc  );

	//  2007/02/10, 取消下面的判断U盘的方式，改为用devIdStr来判断的方式
	/*
	for  (  p  =  pQnmDevInfo->devDesc;  *p;  p  ++  )  {
		 if  (  !strnicmp(  p,  pStorSym,  len  )  )  break;
	}
	if  (  !*p  )  {
		iErr  =  0;  goto  errLabel;
	}
	*/
	if  (  !bUsbStor(  p0,  pQnmDevInfo->devIdStr,  pQnmDevInfo->devDesc  )  )  {
		iErr  =  0;  goto  errLabel;
	}

	traceLogA(  "will call removeCallback(  )"  );

	if  (  removeCallback(  p0,  p1,  p2  )  )  goto  errLabel;
	
	iErr  =  0;

errLabel:

	traceLogA(  "removeMassStorCallback leaves"  );
	return  iErr;
}

/*++

Routine Description:

    Callback for use by Remove
    Invokes DIF_REMOVE
    uses SetupDiCallClassInstaller so cannot be done for remote devices
    Don't use CM_xxx API's, they bypass class/co-installers and this is bad.

Arguments:

    Devs    )_ uniquely identify the device
    DevInfo )
    Index    - index of device
    Context  - GenericContext

Return Value:

    EXIT_xxxx

--*/
 int  removeCallback(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	QWM_THREADINFO		*	pSubThreadInfo  =	(  QWM_THREADINFO  *  )p0;
	QY_W_MON			*	pQwm			=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	PROC_DEV_STRUCT		*	pProcDevStruct	=	(  PROC_DEV_STRUCT  *  )p1;
	QNM_DEV_INFO		*	pQnmDevInfo		=	(  QNM_DEV_INFO  *  )p2;
	HDEVINFO				Devs			=	(  HDEVINFO  )pQnmDevInfo->hDevs;
	PSP_DEVINFO_DATA		DevInfo			=	(  PSP_DEVINFO_DATA  )pQnmDevInfo->pDevInfo;
	DWORD					Index			=	(  DWORD  )pQnmDevInfo->index;
	unsigned  char			ucbRemoved		=	FALSE;
	QWM_DYN_LIB			*	pDynLib			=	(  QWM_DYN_LIB  *  )pQwm->env.pDynLibs;
	
    SP_REMOVEDEVICE_PARAMS	rmdParams;
    SP_DEVINSTALL_PARAMS	devParams;
    LPCTSTR					action			=	_T(  ""  );	//  NULL;
    
    rmdParams.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
    rmdParams.ClassInstallHeader.InstallFunction = DIF_REMOVE;
    rmdParams.Scope = DI_REMOVEDEVICE_GLOBAL;
    rmdParams.HwProfile = 0;
    if(!pDynLib->pSetupDiSetClassInstallParams(Devs,DevInfo,&rmdParams.ClassInstallHeader,sizeof(rmdParams)) ||
       !pDynLib->pSetupDiCallClassInstaller(DIF_REMOVE,Devs,DevInfo)) {
        //
        // failed to invoke DIF_REMOVE
        //
        action = _T(  "remove failed"  );
    } else {
        //
        // see if device needs reboot
        //
        devParams.cbSize = sizeof(devParams);
        if(pDynLib->pSetupDiGetDeviceInstallParams(Devs,DevInfo,&devParams) && (devParams.Flags & (DI_NEEDRESTART|DI_NEEDREBOOT))) {
            //
            // reboot required
            //
            action = _T(  "removed on reboot"  );
            
        } else {
            //
            // appears to have succeeded
            //
            action = _T(  "removed"  );		ucbRemoved  =  TRUE;
        }
        
    }

	_snprintf(  pQnmDevInfo->buf,  sizeof(  pQnmDevInfo->buf  ),  "%s %s\n",  pQnmDevInfo->devIdStr,  action  );
	traceLogA(  "Removing %s succeeded: %s",  ucbRemoved  ?  ""  :  "not",  pQnmDevInfo->buf  );

	if  (  pProcDevStruct  )  pProcDevStruct->ucbRemoved  =  ucbRemoved;	//  表明删除过了

    return  0;
}


/*++

Routine Description:

    Callback for use by Enable/Disable/Restart
    Invokes DIF_PROPERTYCHANGE with correct parameters
    uses SetupDiCallClassInstaller so cannot be done for remote devices
    Don't use CM_xxx API's, they bypass class/co-installers and this is bad.

    In Enable case, we try global first, and if still disabled, enable local

Arguments:

    Devs    )_ uniquely identify the device
    DevInfo )
    Index    - index of device
    Context  - GenericContext

Return Value:

    EXIT_xxxx

--*/
  //  int controlCallback(HDEVINFO Devs,PSP_DEVINFO_DATA DevInfo,DWORD Index,LPVOID Context)
 int  controlCallback(  void  *  p0,  CONTROL_DEV_PARAM  *  p11,  void  *  p2  )
{
	int						iErr			=	-1;
	QWM_THREADINFO		*	pSubThreadInfo  =	(  QWM_THREADINFO  *  )p0;
	QY_W_MON			*	pQwm			=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	//  PROC_DEV_STRUCT		*	pProcDevStruct	=	(  PROC_DEV_STRUCT  *  )p1;
	CONTROL_DEV_PARAM	*	pControlParam	=	(  CONTROL_DEV_PARAM  *  )p11;
	QNM_DEV_INFO		*	pQnmDevInfo		=	(  QNM_DEV_INFO  *  )p2;
	HDEVINFO				Devs			=	(  HDEVINFO  )pQnmDevInfo->hDevs;
	PSP_DEVINFO_DATA		DevInfo			=	(  PSP_DEVINFO_DATA  )pQnmDevInfo->pDevInfo;
	DWORD					Index			=	(  DWORD  )pQnmDevInfo->index;
	QWM_DYN_LIB			*	pDynLib			=	(  QWM_DYN_LIB  *  )pQwm->env.pDynLibs;


    SP_PROPCHANGE_PARAMS pcp;
    //  GenericContext *pControlContext = (GenericContext*)Context;
    SP_DEVINSTALL_PARAMS devParams;

    switch  (  pControlParam->dwControl) {
        case DICS_ENABLE:
            //
            // enable both on global and config-specific profile
            // do global first and see if that succeeded in enabling the device
            // (global enable doesn't mark reboot required if device is still
            // disabled on current config whereas vice-versa isn't true)
            //
            pcp.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
            pcp.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
            pcp.StateChange = pControlParam->dwControl;
            pcp.Scope = DICS_FLAG_GLOBAL;
            pcp.HwProfile = 0;
            //
            // don't worry if this fails, we'll get an error when we try config-
            // specific.
            if(pDynLib->pSetupDiSetClassInstallParams(Devs,DevInfo,&pcp.ClassInstallHeader,sizeof(pcp))) {
               pDynLib->pSetupDiCallClassInstaller(DIF_PROPERTYCHANGE,Devs,DevInfo);
            }
            //
            // now enable on config-specific
            //
            pcp.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
            pcp.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
            pcp.StateChange = pControlParam->dwControl;
            pcp.Scope = DICS_FLAG_CONFIGSPECIFIC;
            pcp.HwProfile = 0;
            break;

        default:
            //
            // operate on config-specific profile
            //
            pcp.ClassInstallHeader.cbSize = sizeof(SP_CLASSINSTALL_HEADER);
            pcp.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
            pcp.StateChange = pControlParam->dwControl;
            pcp.Scope = DICS_FLAG_CONFIGSPECIFIC;
            pcp.HwProfile = 0;
            break;

    }

    if(!pDynLib->pSetupDiSetClassInstallParams(Devs,DevInfo,&pcp.ClassInstallHeader,sizeof(pcp)) ||
       !pDynLib->pSetupDiCallClassInstaller(DIF_PROPERTYCHANGE,Devs,DevInfo)) {
        //
        // failed to invoke DIF_PROPERTYCHANGE
        //
        //  DumpDeviceWithInfo(Devs,DevInfo,pControlContext->strFail);
		#ifdef  __DEBUG__
				traceLogA(  "setupDi* failed"  );  
		#endif
		goto  errLabel;
    } else {
        //
        // see if device needs reboot
        //
        devParams.cbSize = sizeof(devParams);
        if(pDynLib->pSetupDiGetDeviceInstallParams(Devs,DevInfo,&devParams) && (devParams.Flags & (DI_NEEDRESTART|DI_NEEDREBOOT))) {
                //  DumpDeviceWithInfo(Devs,DevInfo,pControlContext->strReboot);
				#ifdef  __DEBUG__
						traceLogA(  "SetupDi* need reboot"  );
						//  MessageBox(  0,  _T(  "Need to reboot"  ),  _T(  "qycx"  ),  MB_OK  );
				#endif
                pControlParam->bRebootForDev = TRUE;
        } else {
            //
            // appears to have succeeded
            //
            //  DumpDeviceWithInfo(Devs,DevInfo,pControlContext->strSuccess);
			#ifdef  __DEBUG__
					traceLogA(  "SetupDi* ok"  );
			#endif
        }
        pControlParam->count++;
    }

	iErr  =  0;
errLabel:
    return iErr;
}

#if  0
 BOOL	bWireless(  char  *  devDesc  )
{
	char  *  p;
	char  *  pWireless	=	"Wireless";
	int		n  =  strlen(  pWireless  );

	for  (  p  =  devDesc;  *p;  p  ++  )  {
		 if  (  !strnicmp(  p,  pWireless,  n  )  )  return  TRUE;
	}
	return  FALSE;
}
#endif

 static  int  tmpHandler_enumWLanAdapter(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int					iErr			=	-1;

	 QWM_THREADINFO		*	pSubThreadInfo	=	(  QWM_THREADINFO  *  )p0;
	 QY_W_MON			*	pQwm			=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	 QY_PCADAPTER_INFO	*	pMyAdapterInfo	=	(  QY_PCADAPTER_INFO  *  )p1;
	 QY_PCADAPTER_INFO	*	pPcAdapterInfo	=	(  QY_PCADAPTER_INFO  *  )p2;

	 if  (  pPcAdapterInfo->uiAdapterType  ==  71  
		 ||  (  pPcAdapterInfo->uiAdapterType  ==  6  &&  pPcAdapterInfo->mediaSubType  ==  2  )    
		 )  
	 {
		 traceLog(  _T(  "wLan: %S"  ),  pPcAdapterInfo->connectionName  );
		 if  (  pQwm->cfg.pcRules.dev.ucWLanAdapterCmd  ==  CONST_devCmd_prohibited  )  {
			 memcpy(  pMyAdapterInfo,  pPcAdapterInfo,  sizeof(  pMyAdapterInfo[0]  )  );
			 iErr  =  1;  goto  errLabel;
		 }
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}


 //  2010/05/20
 int  procWLanAdapterRule(  QWM_THREADINFO  *  pSubThreadInfo  )
{
	 int					iErr			=	-1;
	 QY_W_MON		*		pQwm			=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	 unsigned  int			nSeconds		=	-1;

	 switch  (  pQwm->cfg.pcRules.dev.ucWLanAdapterCmd  )  {
			 case  CONST_devCmd_permitted:
				   iErr  =  0;  goto  errLabel;
				   break;
			 case  CONST_devCmd_prohibited:
			 case  CONST_devCmd_permittedAndLog:
				   break;
			 default:
					 break;
	 }

	 COMMON_PARAM			commonParam1;
	 QY_PCADAPTER_INFO		pcAdapterInfo;

	 //  首先要得到通过pIfRow->index得到devIp
	 if  (  enumPcAdaptersByIpHlp(  0,  &pQwm->env,  tmpHandler_enumWLanAdapter,  pSubThreadInfo,  &pcAdapterInfo  )  <=  0  )  {
		 traceLog(  _T(  "procWLanAdapterRule: no wLan adapter need to block"  )  );  goto  errLabel;  
	 }

	 if  (  pQwm->cfg.pcRules.dev.ucWLanAdapterCmd  ==  CONST_devCmd_prohibited  )  {
		 QWM_DEV_INFO	devInfo;
		 memset(  &devInfo,  0,  sizeof(  devInfo  )  );
		 safeStrnCpy(  pcAdapterInfo.devDesc,  devInfo.devDesc,  mycountof(  devInfo.devDesc  )  );
		 qwmLogDevEvent(  pSubThreadInfo,  CONST_qyEventType_nm_wLanAdapterProhibited,  &devInfo  );

		 MACRO_makeCommonParam3(  &pcAdapterInfo,  (  void  *  )nSeconds,  0,  commonParam1  );
		 enumDevices(  &pQwm->env,  (  LPGUID  )&GUID_CLASS_NET,  pSubThreadInfo,  &commonParam1,  tmpHandler_interruptNetworkCard  );  
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
 }


  int  tmpHandler_disableDev(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int						iErr					=	-1;

	if  (  !p0  ||  !p1  )  {
		traceLog(  _T(  "tmpHandler_disableDev failed, p0 or p1 is null"  )  );
		return  -1;
	}

	QWM_THREADINFO		*	pSubThreadInfo			=	(  QWM_THREADINFO  *  )p0;
	COMMON_PARAM		*	pCommonParam1			=	(  COMMON_PARAM  *  )p1;
	QNM_DEV_INFO		*	pQnmDevInfo				=	(  QNM_DEV_INFO  *  )p2;
	//
	QY_W_MON			*	pQwm					=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	//
	GUID				*	pGuid					=	(  GUID  *  )pCommonParam1->p1;
	BOOL				*	pbNeedReboot			=	(  BOOL  *  )pCommonParam1->p2;
	//
	int						iEventType				=	0;
	unsigned  short			usQwmDevType			=	0;


	//  traceLog(  _T(  "dev %S, %d"  ),  pQnmDevInfo->devDesc,  pQnmDevInfo->ulProblemNumber  );

	if  (  pQnmDevInfo->ulProblemNumber  &  CM_PROB_DISABLED  )  {
		return  0;
	}
  

	if  (  *pGuid  ==  GUID_CLASS_BLUETOOTH  )  iEventType  =  CONST_qyEventType_nm_ucBlueToothProhibited;
	else  if  (  *pGuid  ==  GUID_CLASS_IRDA  )  iEventType  =  CONST_qyEventType_nm_ucInfraredProhibited;
	else  if  (  *pGuid  ==  GUID_CLASS_1394  )  iEventType  =  CONST_qyEventType_nm_uc1394Prohibited;
	else  if  (  *pGuid  ==  GUID_CLASS_sdHostAdapter  )  iEventType  =  CONST_qyEventType_nm_sdHostAdapterProhibited;	
	else  if  (  *pGuid  ==  GUID_CLASS_wpd  )  {
			  iEventType  =  CONST_qyEventType_nm_devProhibited;				//  2011/08/26
			  usQwmDevType  =  CONST_qwmDevType_wpd;
			  }
	else  if  (  *pGuid  ==  GUID_CLASS_mobileDevice  )  {
		      iEventType  =  CONST_qyEventType_nm_devProhibited;
			  usQwmDevType  =  CONST_qwmDevType_mobileDevice;
			  }
	else  if  (  *pGuid  ==  GUID_CLASS_NET  )  {
		      iEventType  =  CONST_qyEventType_nm_devProhibited;
			  usQwmDevType  =  CONST_qwmDevType_usbNetworkCard;
			  }


#ifdef  __DEBUG__
		if  (  !iEventType  )  iEventType  =  CONST_qyEventType_nm_strangePc;
#endif

	{	//  注意，这里，暂停网卡应是个原子动作，不要中间退出。要保证网卡被恢复
		CONTROL_DEV_PARAM	controlParam;
		int					i;

		memset(  &controlParam,  0,  sizeof(  controlParam  )  );
			
		traceLogA(  "to disable %s %s",  pQnmDevInfo->devDesc,  pQnmDevInfo->devIdStr  );

		QWM_DEV_INFO	devInfo;
		memset(  &devInfo,  0,  sizeof(  devInfo  )  );
		safeStrnCpy(  pQnmDevInfo->devDesc,  devInfo.devDesc,  mycountof(  devInfo.devDesc  )  );
		devInfo.usQwmDevType  =  usQwmDevType;
		qwmLogDevEvent(  pSubThreadInfo,  iEventType,  &devInfo  );

				
		controlParam.dwControl  =  DICS_DISABLE;
		if  (  controlCallback(  p0,  &controlParam,   p2  )  )  {
			traceLogA(  "tmpHandler_disableDev failed"  ); 
			goto  errLabel;
		}
		if  (  controlParam.bRebootForDev  )  {
			if  (  pbNeedReboot  )  *pbNeedReboot  =  TRUE;
		}

	}

	iErr  =  0;

errLabel:
	return  iErr;
}


 int  procBlueToothRule(  QWM_THREADINFO  *  pSubThreadInfo  )
{
	int						iErr			=	-1;
	QY_W_MON		*		pQwm			=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	GUID					guid			=	GUID_CLASS_BLUETOOTH;
#ifdef  __DEBUG__
	//  GUID					guid			=	GUID_CLASS_NET;
#endif
	COMMON_PARAM			commonParam1;

	MACRO_makeCommonParam3(  0,  &guid,  0,  commonParam1  );

	if  (  pQwm->cfg.pcRules.dev.ucBlueToothCmd  ==  CONST_devCmd_prohibited  )  {
		 enumDevices(  &pQwm->env,  (  LPGUID  )&guid,  pSubThreadInfo,  &commonParam1,  tmpHandler_disableDev  );  
	}

	iErr   =  0;
errLabel:
	return  iErr;
}

 int  procInfraredRule(  QWM_THREADINFO  *  pSubThreadInfo  )
{
	int						iErr			=	-1;
	QY_W_MON		*		pQwm			=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	GUID					guid			=	GUID_CLASS_IRDA;
	COMMON_PARAM			commonParam1;

	MACRO_makeCommonParam3(  0,  &guid,  0,  commonParam1  );

	if  (  pQwm->cfg.pcRules.dev.ucInfraredCmd  ==  CONST_devCmd_prohibited  )  {
		 enumDevices(  &pQwm->env,  (  LPGUID  )&guid,  pSubThreadInfo,  &commonParam1,  tmpHandler_disableDev  );  
	}

	iErr   =  0;
errLabel:
	return  iErr;
}


 int  proc1394Rule(  QWM_THREADINFO  *  pSubThreadInfo  )
{
	int						iErr			=	-1;
	QY_W_MON		*		pQwm			=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	GUID					guid			=	GUID_CLASS_1394;
	COMMON_PARAM			commonParam1;

	MACRO_makeCommonParam3(  0,  &guid,  0,  commonParam1  );

	if  (  pQwm->cfg.pcRules.dev.uc1394Cmd  ==  CONST_devCmd_prohibited  )  {
		 enumDevices(  &pQwm->env,  (  LPGUID  )&guid,  pSubThreadInfo,  &commonParam1,  tmpHandler_disableDev  );  
	}

	iErr   =  0;
errLabel:
	return  iErr;
}



