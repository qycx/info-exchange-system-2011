
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
#include	"qyRegToolProc.h"
#include	"cpuInfo.h"

//  °´ÕÕclassGuid´óÐ¡Ë³ÐòÅÅÁÐ
#if  0
#define		CONST_classGUID_usb					"{36FC9E60-C465-11CF-8056-444553540000}""\0\0\0"  
#define		CONST_classGUID_cdrom				"{4D36E965-E325-11CE-BFC1-08002BE10318}""\0\0\0"  
#define		CONST_classGUID_disk				"{4D36E967-E325-11CE-BFC1-08002BE10318}""\0\0\0"  
#define		CONST_classGUID_display				"{4D36E968-E325-11CE-BFC1-08002BE10318}""\0\0\0"  
#define		CONST_classGUID_keyboard			"{4D36E96B-E325-11CE-BFC1-08002BE10318}""\0\0\0"  
#define		CONST_classGUID_soundCard			"{4D36E96C-E325-11CE-BFC1-08002BE10318}""\0\0\0"  
#define		CONST_classGUID_modem				"{4D36E96D-E325-11CE-BFC1-08002BE10318}""\0\0\0"  
#define		CONST_classGUID_monitor				"{4D36E96E-E325-11CE-BFC1-08002BE10318}""\0\0\0"  
#define		CONST_classGUID_mouse				"{4D36E96F-E325-11CE-BFC1-08002BE10318}""\0\0\0"  
#define		CONST_classGUID_networkCard			"{4D36E972-E325-11CE-BFC1-08002BE10318}""\0\0\0"  
#define		CONST_classGUID_ports				"{4D36E978-E325-11CE-BFC1-08002BE10318}""\0\0\0"  		// com,lpt
#define		CONST_classGUID_printer				"{4D36E979-E325-11CE-BFC1-08002BE10318}""\0\0\0"  
#define		CONST_classGUID_scsi				"{4D36E97B-E325-11CE-BFC1-08002BE10318}""\0\0\0"  
#define		CONST_classGUID_floppyDisk			"{4D36E980-E325-11CE-BFC1-08002BE10318}""\0\0\0"
#define		CONST_classGUID_volume				"{71A27CDD-812A-11D0-BEC7-08002BE2092F}""\0\0\0"  
#define		CONST_classGUID_battery				"{72631E54-78A4-11D0-BCF7-00AA00B7B32A}""\0\0\0"  
#endif

#define		CONST_classGUID_usb					"{36FC9E60-C465-11CF-8056-444553540000}\0\0\0"  
#define		CONST_classGUID_cdrom				"{4D36E965-E325-11CE-BFC1-08002BE10318}\0\0\0"  
#define		CONST_classGUID_disk				"{4D36E967-E325-11CE-BFC1-08002BE10318}\0\0\0"  
#define		CONST_classGUID_display				"{4D36E968-E325-11CE-BFC1-08002BE10318}\0\0\0"  
#define		CONST_classGUID_keyboard			"{4D36E96B-E325-11CE-BFC1-08002BE10318}\0\0\0"  
#define		CONST_classGUID_soundCard			"{4D36E96C-E325-11CE-BFC1-08002BE10318}\0\0\0"  
#define		CONST_classGUID_modem				"{4D36E96D-E325-11CE-BFC1-08002BE10318}\0\0\0"  
#define		CONST_classGUID_monitor				"{4D36E96E-E325-11CE-BFC1-08002BE10318}\0\0\0"  
#define		CONST_classGUID_mouse				"{4D36E96F-E325-11CE-BFC1-08002BE10318}\0\0\0"  
#define		CONST_classGUID_networkCard			"{4D36E972-E325-11CE-BFC1-08002BE10318}\0\0\0"  
#define		CONST_classGUID_ports				"{4D36E978-E325-11CE-BFC1-08002BE10318}\0\0\0"  		// com,lpt
#define		CONST_classGUID_printer				"{4D36E979-E325-11CE-BFC1-08002BE10318}\0\0\0"  
#define		CONST_classGUID_scsi				"{4D36E97B-E325-11CE-BFC1-08002BE10318}\0\0\0"  
#define		CONST_classGUID_floppyDisk			"{4D36E980-E325-11CE-BFC1-08002BE10318}\0\0\0"
#define		CONST_classGUID_volume				"{71A27CDD-812A-11D0-BEC7-08002BE2092F}\0\0\0"  
#define		CONST_classGUID_battery				"{72631E54-78A4-11D0-BCF7-00AA00B7B32A}\0\0\0"  


 QY_DMITEM	CONST_classGUIDTable[]	=
{
	//  {	CONST_assetType_cpu,				"CPU""\0\0\0",								},
	//  {	CONST_assetType_mem,				"ÄÚ´æ""\0\0\0",								},
	//  {	CONST_assetType_bios,				"BIOS""\0\0\0",								},
	{	CONST_assetType_floppy,					_T(  CONST_classGUID_floppyDisk  ),				},			//  "ÈíÇý",	
	{	CONST_assetType_monitor,				_T(  CONST_classGUID_monitor  ),				},			//  "¼àÊÓÆ÷",
	{	CONST_assetType_ideHardDisk,			_T(  CONST_classGUID_disk  ),					},			//  "IDEÓ²ÅÌ",
	//  {	CONST_assetType_usbDisk,			CONST_classGUID_usb,					},			//  "USB´ÅÅÌ",
	//  {	CONST_assetType_scsiHardDisk,		CONST_classGUID_scsi,					},			//	"SCSIÓ²ÅÌ",
	{	CONST_assetType_ideCdrom,				_T(  CONST_classGUID_cdrom  ),					},			//  "DVD/CD-ROM",
	{	CONST_assetType_display,				_T(  CONST_classGUID_display  ),				},			//  "ÏÔ¿¨",
	{	CONST_assetType_networkCard,			_T(  CONST_classGUID_networkCard  ),			},			//	"Íø¿¨",
	//  {	CONST_assetType_soundCard,			CONST_classGUID_soundCard,				},			//  "Éù¿¨",
	//  {	CONST_assetType_software,			"Èí¼þ""\0\0\0",								},
	{	-1,										NULL,								},
};



//  int  myGetCpuInfo(  QWM_COMPONENT_INFO  *  pComponent  ); 
int  myGetCpuInfo(  void  *  pRegTool,  QWM_ASSETS_INFO  *  pAssetsInfo  );
int  myGetMemInfo(  QWM_COMPONENT_INFO  *  pComponent  ); 
int  myGetBiosInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  );
//  int  myGetIdeDiskInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  );
//  int	 myGetIdeCdromInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  );
int	 myGetSoftwareInfo(  QY_ENV  *  pEnv,  QWM_ASSETS_INFO  *  pAssetsInfo  );
//  int	 myGetDisplayInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  );
//  int	 myGetNetworkCardInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  );
//  int  myGetMonitorInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  );
int  myGet98Devs(  QWM_ASSETS_INFO  *  pAssetsInfo  );
int  myGetDevs(  void  *  pRegTool,  QWM_ASSETS_INFO  *  pAssetsInfo  );
int  myGet98IdeDiskInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  );
int  myGet98CdromUsbInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  );
int	 myGet98DisplayInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  );
int	 myGet98NetworkCardInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  );
int	 myGet98MonitorInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  );
int	 myGet98ModemInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  );

#define			CONST_qyRootKey_controlClass		  "SYSTEM\\CurrentControlSet\\Control\\Class"  
#define			CONST_qyRootKey_controlNetwork		  "SYSTEM\\CurrentControlSet\\Control\\Network"  
#define			CONST_qyRootKey_enum				  "SYSTEM\\CurrentControlSet\\Enum"  
#define			CONST_qyRootKey_service				  "SYSTEM\\CurrentControlSet\\Services"  

#define			CONST_enumName_monitor				  "DISPLAY"  
#define			CONST_enumName_ide					  "IDE"  
#define			CONST_enumName_pci					  "PCI"  
#define			CONST_enumName_usbstor				  "USBSTOR"  


#define			CONST_validRootKey_control			  "Control"  
#define			CONST_validRootKey_enum				  "Enum"  
#define			CONST_validRootKey_cdrom			  "Cdrom"  
#define			CONST_invalidRootKey_properties		  "ProPerties"  
#define			CONST_invalidRootKey_descriptions	  "Descriptions"  

#define			CONST_regValName_deviceReference	  "DeviceReference"  
#define			CONST_regValName_classGUID			  "ClassGUID"  
#define			CONST_regValName_service			  "Service"  
#define			CONST_regValName_hardwareId			  "HardwareId"  
#define			CONST_regValName_matchingDeviceId	  "MatchingDeviceId"  
#define			CONST_regValName_driver				  "Driver"  
#define			CONST_regValName_pnpInstanceId		  "PnpInstanceID"  
#define			CONST_regValName_name				  "name"  
#define			CONST_regValName_networkaddress		  "networkaddress"  
#define			CONST_regValName_deviceReference	  "DeviceReference"  
#define			CONST_regValName_lowerRange			  "LowerRange"  

#define			CONST_regValName_friendlyName		  "FriendlyName"  
#define			CONST_regValName_vender				  "ProviderName"  
#define			CONST_regValName_driverDate			  "DriverDate"  
#define			CONST_regValName_driverDesc			  "DriverDesc"  
#define			CONST_regValName_driverVersion		  "DriverVersion"  
#define			CONST_regValName_driverVersion_98	  "Ver"  
#define			CONST_regValName_mfg				  "Mfg"  


#define			CONST_string_monitor				  "ÎÞ·¨Ê¶±ðµÄ¼àÊÓÆ÷"  
#define			CONST_string_display				  "ÎÞ·¨Ê¶±ðµÄÏÔ¿¨"  
#define			CONST_string_dialAdapter			  "²¦ºÅÊÊÅäÆ÷"  
#define			CONST_string_network				  "network"  
#define			CONST_string_connection				  "Connection"  

#define			CONST_string_ndiInterfaces			"Ndi\\Interfaces"
#define			CONST_string_ethernet				"ethernet"
#define			CONST_string_flop					"FLOP"




 QWM_COMPONENT_INFO  *  nextComponent(  QWM_ASSETS_INFO  *  pAssetsInfo  )
{
	 QWM_COMPONENT_INFO  *  pComponent	=	NULL;
	 if  (  pAssetsInfo->cnt  >=  sizeof(  pAssetsInfo->components  )  /  sizeof(  pAssetsInfo->components[0]  )  )  return  NULL;
	 pComponent  =  &pAssetsInfo->components[pAssetsInfo->cnt];
	 memset(  pComponent,  0,  sizeof(  pComponent[0]  )  );
	 return  pComponent;
}

 int  submitComponent(  QWM_ASSETS_INFO  *  pAssetsInfo,  unsigned  int  uiCodePage  )
{
	 if  (  pAssetsInfo->cnt  >=  sizeof(  pAssetsInfo->components  )  /  sizeof(  pAssetsInfo->components[0]  )  )  return  -1;
	 pAssetsInfo->uiCodePages[pAssetsInfo->cnt]  =  uiCodePage;			//  2006/05/05
	 pAssetsInfo->cnt  ++  ;
	 return  0;
}

  //  ×¢Òâ,ÔÚÕâÀï,ÐèÒªÓÃansiÀ´´¦ÀíËùÓÐµÄtable, ¹ÊÉèÖÃÕâÑùº¯ÊýÀ´´¦ÀíÒÅÁôÎÊÌâ,ÔÚqwmSharedÀï,±ØÐë¶¼ÓÃÕâÑùº¯Êý
  extern  "C"  int  myGetTypeByDes(  QY_DMITEM  *  pTable,  TCHAR  *  des  )
{
	 int	i;

	 if  (  !pTable  )  return  -1;			//  2005/02/08

	 for  (  i  =  0;  pTable[i].type  !=  -1;  i  ++  )  {
		  if  (  !lstrcmpi(  des,  pTable[i].des  )  )  return  pTable[i].type;
	 }
	 return  -1;
}

 
 int  getQwmAssetsHeadInfo(  void  *  pRegToolParam,  void  *  pAssetsInfoParam  )  
{
	 int					iErr		=	-1;
	 QY_REG_TOOL		*	pRegTool	=	(  QY_REG_TOOL  *  )pRegToolParam;
	 QWM_ASSETS_INFO	*	pAssetsInfo  =	(  QWM_ASSETS_INFO  *  )pAssetsInfoParam;
	 QWM_COMPONENT_INFO	*	pComponent	=	NULL;
	 
	 if  (  !pAssetsInfo  )  return  -1;
	 	 
	 pAssetsInfo->uiLangId		=	pRegTool->env.usLangId;	//  
	 pAssetsInfo->iPlatformId	=	pRegTool->env.iPlatformId;
	 TCHAR	tBuf[MAX_PATH];
	 //  GetWindowsDirectory(  pAssetsInfo->winDir,  sizeof(  pAssetsInfo->winDir  )  );
	 GetWindowsDirectory(  tBuf,  mycountof(  tBuf  )  );  myTChar2Utf8(  tBuf,  pAssetsInfo->winDir,  mycountof(  pAssetsInfo->winDir  )  );
	 safeStrnCpy(  pRegTool->curUsrName,  pAssetsInfo->usrName,  sizeof(  pAssetsInfo->usrName  )  );

	 return  0;
}


 int  getQwmAssetsHardwareInfo(  void  *  pRegToolParam,  void  *  pAssetsInfoParam  )
{
	 int					iErr		=	-1;
	 QY_REG_TOOL		*	pRegTool	=	(  QY_REG_TOOL  *  )pRegToolParam;
	 QWM_ASSETS_INFO	*	pAssetsInfo  =	(  QWM_ASSETS_INFO  *  )pAssetsInfoParam;
	 QWM_COMPONENT_INFO	*	pComponent	=	NULL;
	 
	 if  (  !pAssetsInfo  )  return  -1;
	 	 
	 if  (  getQwmAssetsHeadInfo(  pRegTool,  pAssetsInfo  )  )  goto  errLabel;

	 //  ÏÈÈ¡cpuÐÅÏ¢
	 /*
	 if  (  !(  pComponent  =  nextComponent(  pAssetsInfo  )  )  )  goto  errLabel;  
	 if  (  !myGetCpuInfo(  pComponent  )  )  submitComponent(  pAssetsInfo  );  
	 #ifdef  __DEBUG__
			 printComponentInfo(  0,  pComponent  );
	 #endif
	 */
	 myGetCpuInfo(  pRegToolParam,  pAssetsInfo  );
	 
	 //  È¡ÄÚ´æÐÅÏ¢
	 if  (  !(  pComponent  =  nextComponent(  pAssetsInfo  )  )  )  goto  errLabel;  
	 if  (  !myGetMemInfo(  pComponent  )  )  submitComponent(  pAssetsInfo,  0  );  
	 #ifdef	__DEBUG__	
			printComponentInfo(  0,  pComponent  );
	 #endif
	 
	 //  È¡biosÐÅÏ¢
	 myGetBiosInfo(  pAssetsInfo  );
	 
	 // È¡ÆäËûÉè±¸ÐÅÏ¢ 
	 if  (  !g_bIsWinNT  )  {
		 myGet98Devs(  pAssetsInfo  );

		 //  myGet98IdeDiskInfo(  pAssetsInfo  );

		 //  myGet98CdromUsbInfo(  pAssetsInfo  );

		 //  myGet98DisplayInfo(  pAssetsInfo  );

		 //  myGet98NetworkCardInfo(  pAssetsInfo  );
		 
		 //  myGet98MonitorInfo(  pAssetsInfo  );
		 
		 //  myGet98ModemInfo(  pAssetsInfo  );

		}
	 else  {


		myGetDevs(  pRegToolParam,  pAssetsInfo  );

		/*


		//  È¡Ó²ÅÌ(USB)ÐÅÏ¢
		myGetIdeDiskInfo(  pAssetsInfo  );

		//  È¡¹âÇýÐÅÏ¢
		myGetIdeCdromInfo(  pAssetsInfo  );

 		//  È¡ÏÔ¿¨ÐÅÏ¢
		myGetDisplayInfo(  pAssetsInfo  );

		//  È¡Íø¿¨ÐÅÏ¢
		myGetNetworkCardInfo(  pAssetsInfo  );

		//  È¡¼àÊÓÆ÷ÐÅÏ¢
		myGetMonitorInfo(  pAssetsInfo  );
		*/
	 }
	 
	 iErr  =  0;
errLabel:
	 return  0;		//  ÕâÀïÄÜÈ¡µ½¶àÉÙÊÇ¶àÉÙ£¬¹Ê×Ü·µ»Ø0
}


 int  getQwmAssetsSoftwareInfo(  void  *  pRegToolParam,  void  *  pAssetsInfoParam  )
{
	 int					iErr		=	-1;
	 QY_REG_TOOL		*	pRegTool	=	(  QY_REG_TOOL  *  )pRegToolParam;
	 QWM_ASSETS_INFO	*	pAssetsInfo  =	(  QWM_ASSETS_INFO  *  )pAssetsInfoParam;
	 QWM_COMPONENT_INFO	*	pComponent	=	NULL;
	 
	 if  (  !pAssetsInfo  )  return  -1;
	 	 
	 if  (  getQwmAssetsHeadInfo(  pRegTool,  pAssetsInfo  )  )  goto  errLabel;

	 //  È¡Èí¼þÐÅÏ¢
	 myGetSoftwareInfo(  &pRegTool->env,  pAssetsInfo  );
	 #ifdef	__DEBUG__	
			printQwmAssetsInfo(  pAssetsInfo  );
	 #endif

	 iErr  =  0;
errLabel:
	 return  0;
}

 

//--------------------------------------------------------------------------; 
// 
//  DWORD  myGetCpuInfo
// 
//  Description: 
//      This function returns the version of Windows that the application 
//      is running on plus some platform information. 
// 
//  Arguments: 
//      PTSTR pach: Options pointer to buffer to receive text string of 
//      the Windows version and platform. 
// 
//  Return (LRESULT): 
//      The return value will be ...
// 
//  History: 
//       2/13/93 
//--------------------------------------------------------------------------;  

#define		CONST_qyRootKey_cpu								"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\"
	#define			CONST_regValName_mHz						"~MHz"			//  REG_DWORD
	#define			CONST_regValName_processorName				"ProcessorNameString"
	#define			CONST_regValName_identifier					"Identifier"
	#define			CONST_regValName_vendor						"VendorIdentifier"
#define		CONST_string_x86								"x86"
 int  tmpGetACpuInfo(  QY_REG_TOOL  *  pRegTool,  QWM_COMPONENT_INFO  *  pComponent,  int  iSeqNo  )
{
	 int					iErr		=	-1;
	 TCHAR					processorName[128  +  1];
	 TCHAR					vendor[64  +  1];
	 QY_REG					reg;
	 unsigned  int			uimHz		=	0;
	 unsigned  int			len;
     SYSTEM_INFO			sysInfo;

	 memset(  &reg,  0,  sizeof(  reg  )  );
	 _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s%d"  ),  _T(  CONST_qyRootKey_cpu  ),  iSeqNo  );
	 //
	 reg.uiType  =  REG_DWORD;
	 len  =  sizeof(  uimHz  );
	 if  (  tmpGetRegCfgEx(  &reg,  _T(  CONST_regValName_mHz  ),  (  char  *  )&uimHz,  &len  )  )  uimHz  =  0;    
	 //
	 reg.uiType  =  REG_SZ;
	 len  =  sizeof(  vendor  );
	 if  (  tmpGetRegCfgEx(  &reg,  _T(  CONST_regValName_vendor  ),  (  char  *  )vendor,  &len  )  )  vendor[0]  =  0;
	 //
	 reg.uiType  =  REG_SZ;
	 len  =  sizeof(  processorName  );
	 if  (  tmpGetRegCfgEx(  &reg,  _T(  CONST_regValName_processorName  ),  (  char  *  )processorName,  &len  )  )  processorName[0]  =  0;
	 tTrim(  processorName  );
	 if  (  !processorName[0]  )  {
		 len  =  sizeof(  processorName  );
		 if  (  tmpGetRegCfgEx(  &reg,  _T(  CONST_regValName_identifier  ),  (  char  *  )processorName,  &len  )  )  processorName[0]  =  0;
	 }
	 tTrim(  processorName  );
	 traceLog(  _T(  "processorName is %s"  ),  processorName  );

	 GetSystemInfo(  &sysInfo  );
	 if  (  !g_bIsWinNT  ||  (  sysInfo.dwNumberOfProcessors  ==  1  &&  (  !processorName[0]  ||  !_tcsnicmp(  processorName,  _T(  CONST_string_x86  ),  lstrlen(  _T(  CONST_string_x86  )  )  )  )  )  )  {
		 CPUInfo				info;

		 //  traceLogA(  ""  );

		 pComponent->uiType  =  CONST_assetType_cpu;

		 if  (  !info.bRetrieveAll(  )  )  goto  errLabel;
		 //
		 pComponent->u.cpu.iManufacturer	=  info.ChipManufacturer;
		 pComponent->u.cpu.iType			=  info.ChipID.Type;
		 pComponent->u.cpu.iFamily			=  info.ChipID.Family;
		 pComponent->u.cpu.iModel			=  info.ChipID.Model;
		 pComponent->u.cpu.iRevision		=  info.ChipID.Revision;
		 pComponent->u.cpu.iCache			=  info.ChipID.iCache;
		 pComponent->u.cpu.iExtendedFamily	=  info.ChipID.ExtendedFamily;
		 pComponent->u.cpu.iExtendedModel	=  info.ChipID.ExtendedModel;
		 pComponent->u.cpu.ucbHasMMX		=  !!info.Features.HasMMX;
		 pComponent->u.cpu.ucbSupportsMP	=  !!info.Features.ExtendedFeatures.SupportsMP;
		 pComponent->u.cpu.iFrequency		=  uimHz  ?  uimHz  :  info.GetProcessorClockFrequency(  );
		 pComponent->u.cpu.uiBrandId		=  info.ChipID.uiBrandId;		//  2005/01/16

		 iErr  =  0;  goto  errLabel;

	 }

	 pComponent->uiType  =  CONST_assetType_cpu1;
	 myTChar2Utf8(  processorName,  pComponent->u.cpu1.processorName,  sizeof(  pComponent->u.cpu1.processorName  )  );
	 myTChar2Utf8(  vendor,  pComponent->u.cpu1.vendor,  sizeof(  pComponent->u.cpu1.vendor  )  );
	 pComponent->u.cpu1.uimHz  =  uimHz;
	 pComponent->u.cpu1.ucSeqNo  =  (  unsigned  char  )iSeqNo;

	 iErr  =  0;
errLabel:
	 return  iErr;
}

	 //  int  myGetCpuInfo(  QWM_COMPONENT_INFO  *  pComponent  ) 
 int  myGetCpuInfo(  void  *  pRegToolParam,  QWM_ASSETS_INFO  *  pAssetsInfo  )
{	
	 int					iErr		=	-1;
     QY_REG_TOOL		*	pRegTool	=	(  QY_REG_TOOL  *  )pRegToolParam;
	 //  CPUInfo				info;
	 QWM_COMPONENT_INFO	*	pComponent	=	NULL;
     SYSTEM_INFO			sysInfo;
	 int					i;

	 GetSystemInfo(  &sysInfo  );
	 for  (  i  =  0;  i  <  (  int  )sysInfo.dwNumberOfProcessors;  i  ++  )  {
		  if  (  !(  pComponent  =  nextComponent(  pAssetsInfo  )  )  )  goto  errLabel;  
		  if  (  tmpGetACpuInfo(  pRegTool,  pComponent,  i  )  )  continue;
		  #ifdef  __DEBUG__
				  printComponentInfo(  0,  pComponent  );
	 	  #endif
		  submitComponent(  pAssetsInfo,  0  );  
	 }
	 
	 /*
	 traceLogA(  "ÕâÀï£ºÕâÑùÈ¡Öµ£ºÈç¹ûÄÜ¹»ÓÃ×¢²á±íÀ´È¡ÐÍºÅ£¬ÔòÓÃ×¢²á±íÈ¡£¬·ñÔòÔÙÓÃÏÂÃæµÄ³ÌÐòÈ¡"  );

	 if  (  !(  pComponent  =  nextComponent(  pAssetsInfo  )  )  )  goto  errLabel;  
	 
	 pComponent->uiType  =  CONST_assetType_cpu;
	 
	 if  (  !info.bRetrieveAll(  )  )  goto  errLabel;
	 //
	 pComponent->u.cpu.iManufacturer	=  info.ChipManufacturer;
	 pComponent->u.cpu.iType			=  info.ChipID.Type;
	 pComponent->u.cpu.iFamily			=  info.ChipID.Family;
	 pComponent->u.cpu.iModel			=  info.ChipID.Model;
	 pComponent->u.cpu.iRevision		=  info.ChipID.Revision;
	 pComponent->u.cpu.iCache			=  info.ChipID.iCache;
	 pComponent->u.cpu.iExtendedFamily	=  info.ChipID.ExtendedFamily;
	 pComponent->u.cpu.iExtendedModel	=  info.ChipID.ExtendedModel;
	 pComponent->u.cpu.ucbHasMMX		=  !!info.Features.HasMMX;
	 pComponent->u.cpu.ucbSupportsMP	=  !!info.Features.ExtendedFeatures.SupportsMP;
	 pComponent->u.cpu.iFrequency		=  info.GetProcessorClockFrequency(  );
	 pComponent->u.cpu.uiBrandId		=  info.ChipID.uiBrandId;		//  2005/01/16
	
	 submitComponent(  pAssetsInfo  );  
	
	 #ifdef  __DEBUG__
			 printComponentInfo(  0,  pComponent  );
	 #endif
	 */

	 iErr  =  0;
errLabel:
	 return  iErr; 
} 

 int  myGetMemInfo(  QWM_COMPONENT_INFO  *  pComponent  )
{
	 MEMORYSTATUSEX	memStatus;

	 if  (  !pComponent  )  return  -1;

	 pComponent->uiType  =  CONST_assetType_mem;
	 memStatus.dwLength  =  sizeof(  memStatus  );
	 GlobalMemoryStatusEx(  &memStatus  );

	 DWORDLONG  ullTotalPhysInM  =  (  memStatus.ullTotalPhys  +  16  *  1024  *  1024  )  /  (  32  *  1024  *  1024  )  *  32;
	 pComponent->u.mem.uiTotalPhys  =  ullTotalPhysInM;
	 return  0;
}

#define		CONST_qyRootKey_bios_98				  "Enum\\Root\\*PNP0C01\\0000"  
#define		CONST_qyRootKey_bios_nt				  "HARDWARE\\DESCRIPTION\\System"  
#define		CONST_regValName_biosDate_98		  "BIOSDate"  
#define		CONST_regValName_biosDate_nt		  "SystemBiosDate"  
#define		CONST_regValName_biosName_98		  "BIOSName"  
#define		CONST_regValName_biosVer_98			  "BIOSVersion"  
#define		CONST_regValName_biosVer_nt			  "SystemBiosVersion"  
#define		CONST_regValName_biosIdentifier_nt	  "Identifier"  
 int  myGetBiosInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  )
{
	 int						iErr						=   -1;
	 int						iRet						=   0;
	 TCHAR					*	pBiosKey					=	NULL;
	 TCHAR					*	pBiosDateRegValName			=   NULL;
	 TCHAR					*	pBiosNameRegValName			=	NULL;
	 TCHAR					*	pBiosVerRegValName			=   NULL;
	 TCHAR					*   pBiosIdentifierRegValName	=	NULL;
	 TCHAR						biosBuf[256  + 1]			=   _T(  ""  );
	 QWM_COMPONENT_INFO		*	pComponent					=   NULL;
 	 int						iAssetType					=  CONST_assetType_bios;


	 if  (  !pAssetsInfo  )  goto  errLabel;
	 switch  (  pAssetsInfo->iPlatformId  )  {
			 case  CONST_qyPlatform_win32:
			 case  CONST_qyPlatform_win95:  goto  errLabel;

			 case  CONST_qyPlatform_win98:			 
			 case  CONST_qyPlatform_winme:
				   pBiosKey  =  _T(  CONST_qyRootKey_bios_98  );
				   pBiosDateRegValName  =  _T(  CONST_regValName_biosDate_98  );
				   pBiosNameRegValName  =  _T(  CONST_regValName_biosName_98  );
				   pBiosVerRegValName  =  _T(  CONST_regValName_biosVer_98  );
				   break;
			 case  CONST_qyPlatform_nt: 
			 case  CONST_qyPlatform_win2k:
			 case  CONST_qyPlatform_winxp:
			 case  CONST_qyPlatform_win2003:
			 default:  
				   pBiosKey  =  _T(  CONST_qyRootKey_bios_nt  );
				   pBiosDateRegValName	=  _T(  CONST_regValName_biosDate_nt  );
				   pBiosVerRegValName  =  _T(  CONST_regValName_biosVer_nt  );
				   pBiosIdentifierRegValName  =  _T(  CONST_regValName_biosIdentifier_nt  );
				   break;
	 }

	 if  (  (  iRet  =  qyGetRegCfg(  pBiosKey,  pBiosDateRegValName,  (  char  *  )biosBuf,  sizeof(  biosBuf  )  )  )  )  goto  errLabel;

	 if  (  !(  pComponent  =  nextComponent(  pAssetsInfo  )  )  )  goto  errLabel;
	 pComponent->uiType  =  iAssetType;
	 //  _snprintf(  pComponent->u.bios.systemBiosDate,  sizeof(  pComponent->u.bios.systemBiosDate  ),  "%s",  biosBuf  );
	 myTChar2Utf8(  biosBuf,  pComponent->u.bios.systemBiosDate,  sizeof(  pComponent->u.bios.systemBiosDate  )  );

	 if  (  pBiosNameRegValName  )  {
		 if  (  qyGetRegCfg(  pBiosKey,  pBiosNameRegValName,  (  char  *  )biosBuf,  sizeof(  biosBuf  )  )  )  goto  errLabel;
		 //  _snprintf(  pComponent->u.bios.systemBiosVer,  sizeof(  pComponent->u.bios.systemBiosVer  ),  "%s",  biosBuf  );
		 myTChar2Utf8(  biosBuf,  pComponent->u.bios.systemBiosVer,  mycountof(  pComponent->u.bios.systemBiosVer  )  );
	 }
	 if  (  pBiosVerRegValName  )  {
		 if  (  qyGetRegCfg(  pBiosKey,  pBiosVerRegValName,  (  char  *  )biosBuf,  sizeof(  biosBuf  )  )  )  goto  errLabel;
		 if  (  !g_bIsWinNT  )  _snprintf(  pComponent->u.bios.systemBiosVer,  sizeof(  pComponent->u.bios.systemBiosVer  ),  "%s %s",  pComponent->u.bios.systemBiosVer,  biosBuf  );
		 else  {
			#if  0
			   for  (  TCHAR  *  p  =  biosBuf;  p[0]  ||  p[1];  p  +=  lstrlen(  p  )  +  1  )  {  
			 	    if  (  0  >  _snprintf(  pComponent->u.bios.systemBiosVer,  sizeof(  pComponent->u.bios.systemBiosVer  ),  "%s %s",  pComponent->u.bios.systemBiosVer,  p  )  )  break;				  			 
			   }
			#endif
			   myTChar2Utf8(  biosBuf,  pComponent->u.bios.systemBiosVer,  mycountof(  pComponent->u.bios.systemBiosVer  )  );
		 }
	 }
	 if  (  pBiosIdentifierRegValName  )  {
		 if  (  qyGetRegCfg(  pBiosKey,  pBiosIdentifierRegValName,  (  char  *  )biosBuf,  sizeof(  biosBuf  )  )  )  goto  errLabel;
		 //  _snprintf(  pComponent->u.bios.identifier,  sizeof(  pComponent->u.bios.identifier  ),  "%s",  biosBuf  );
		 myTChar2Utf8(  biosBuf,  pComponent->u.bios.identifier,  sizeof(  pComponent->u.bios.identifier  )  );
	 }

	 #ifdef	__DEBUG__	
			printComponentInfo(  0,  pComponent  );
	 #endif

	 submitComponent(  pAssetsInfo,  0  );

	 iErr		=  0;
errLabel:
	 return  iErr;
}


 //  ÓÃÓÚ98ÏµÍ³µÄÓ²¼þ·ÖÎö:Ò»¡¢Êý¾Ý¶ÁÈ¡£»¶þ¡¢ÑéÖ¤ÊÇ·ñ»î¶¯
#define		CONST_qyRootKey_ideDisk_98					  "Enum\\ESDI"  			//  Ó²ÅÌ
#define		CONST_qyRootKey_cdrom_usb_98				  "Enum\\SCSI"  			//  ¹âÇý¡¢usbÅÌ
#define		CONST_qyRootKey_networkCard_98				  "System\\CurrentControlSet\\Services\\Class\\Net"  
#define		CONST_qyRootKey_display_98					  "System\\CurrentControlSet\\Services\\Class\\Display"  
#define		CONST_qyRootKey_monitor_98					  "System\\CurrentControlSet\\Services\\Class\\Monitor"  
#define		CONST_qyRootKey_modem_98					  "System\\CurrentControlSet\\Services\\Class\\Modem"  
 //  
#define		CONST_regValName_deviceDesc					"DeviceDesc"


#define		CONST_qyRootKey_ideDisk_nt					"HARDWARE\\DEVICEMAP\\Scsi\\Scsi Port 0\\Scsi Bus 0\\Target Id 0"   //  ÊÇ·ñÎ¨Ò»ÉÐÎ´Öª
#define		CONST_qyRootKey_disk_2k						"SYSTEM\\CurrentControlSet\\Services\\Disk\\Enum"  					//  Í¬Ê±°üÀ¨ideDiskºÍusbDiskÐÅÏ¢
#define		CONST_qyRootKey_cdrom_2k					"SYSTEM\\CurrentControlSet\\Services\\Cdrom\\Enum"  
#define		CONST_regValName_count						"Count"  
#define		CONST_ideDisk_id							"IDE\\Disk"
#define		CONST_usbDisk_id							"USBSTOR\\Disk"
#define		CONST_ideCdrom_id							"IDE\\CdRom"
#define		CONST_qyRootKey_configMgrEnum_98			"Config Manager\\Enum"  
#define		CONST_regValName_hardwareKey				"HardWareKey"  
#define		CONST_qyRootKey_serviceClass_98				"SYSTEM\\CurrentControlSet\\Services\\Class"  


#if  0
 int  myGet98Devs(  QWM_ASSETS_INFO  *  pAssetsInfo  )
{
	 int						iErr								=  -1;
	 BOOL						bKeyOpen							=  FALSE;
	 HKEY						hKey								=  NULL;
	 //  ×é¼þ³õÊ¼»¯²ÎÊý
	 char					*   pEnumKey							=  CONST_qyRootKey_configMgrEnum_98;
	 char					*	pClassGUID							=  CONST_classGUID_networkCard;	
	 char					*   pString								=  CONST_string_connection;
	 int						iAssetType							=  CONST_assetType_networkCard;
	 //  Æ¥Åä²ÎÊý
	 //  char						matchingDeviceBuf[MAX_PATH  +  1]	=  "";
	 //  Êý¾Ý
	 char					*	pVendor								=  CONST_regValName_vender;
	 char					*   pDriverDate							=  CONST_regValName_driverDate;
	 char					*   pDriverDesc							=  CONST_regValName_driverDesc;
	 char					*   pDriverVersion						=  CONST_regValName_driverVersion_98;
	 char					*   pNetworkaddress						=  CONST_regValName_networkaddress;
	 char					*   pName								=  CONST_regValName_name;		//  ±¾µØÁ¬½Ó
	 char						vendorBuf[64  + 1]					=  "";
	 char						driverDateBuf[64 +1]				=  "";
	 //  char						driverDescBuf[64 +1]				=  "";
	 char						driverDescBuf[256 +1]				=  "";		//  2005/01/25½«ÉÏÃæµÄBUF¸ÄÎª256×Ö½Ú
	 char						driverVersionBuf[64 + 1]			=  "";
	 char						networkaddressBuf[12 + 1]			=  "";
	 char						nameBuf[16 + 1]						=  "";
	 //  ±äÁ¿
	 int						iRet								=  0;
	 char						tSubKey[MAX_PATH  +  1]				=  "";
	 char						tmpBuf[MAX_PATH  +  1]				=  "";
	 int						i  =  0,  cnt	=  0;
	 char						keyBuf[MAX_PATH  +  1]				=	"";
	 char						key1Buf[MAX_PATH  + 1]				=  "";
	 char						subKeyBuf[MAX_PATH  + 1]			=  "";
	 //  char						enumDeviceBuf[MAX_PATH  + 1]		=  "";
 	 //  char						classDeviceBuf[MAX_PATH  + 1]		=  "";
	 char						networkCfgBuf[MAX_PATH + 1]			=  "";
	 BOOL						bWanted								=  FALSE;
 	 BOOL						bFloppy								=  FALSE;
	 QWM_COMPONENT_INFO		*	pComponent							=  NULL;
	 QY_REG						reg;
	 
	 traceLogA(  "myGet98Devs():  ½øÈë!"  );
	 if  (  !pAssetsInfo  )  goto  errLabel;

	 if  (  (  iRet  =  RegOpenKeyEx(  HKEY_DYN_DATA,  pEnumKey,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey  )  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	 bKeyOpen  =  TRUE;
	 for  (  i = 0; ; i ++  )  {

		  iRet  =  RegEnumKey(  hKey,  i,  tSubKey,  sizeof(  tSubKey  )  );
		  if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  )  break;
		  
		  memset(  (  char *  )&reg, 0, sizeof( reg )  );
		  reg.hKeyRoot0  =  HKEY_DYN_DATA;
		  _snprintf(  reg.rootKey,  sizeof(  reg.rootKey  ),  "%s\\%s",  pEnumKey,  tSubKey  );
		  if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_hardwareKey,  tmpBuf,  sizeof(  tmpBuf  )  )  )  continue;
		  traceLogA(  "µÚ%d¸öhardwareKey(%s) is %s",  i,  reg.rootKey,  tmpBuf  );
  		  if  ( !_strnicmp(  tmpBuf,  CONST_string_flop,  strlen(  CONST_string_flop  )  )  )   bFloppy  =  TRUE;

		  bWanted  =  FALSE;
		  
		  _snprintf(  keyBuf,  sizeof(  keyBuf ),  "%s\\%s",  CONST_validRootKey_enum,  tmpBuf  );
		  if  (  qyGetRegCfg(  keyBuf,  CONST_regValName_classGUID,  tmpBuf,  sizeof(  tmpBuf  )  )  )  continue;
		  if  (  (  iAssetType  =  myGetTypeByDes(  CONST_classGUIDTable,  tmpBuf  )  )  <  0  )continue;
		  if  (  iAssetType  ==  CONST_assetType_ideHardDisk  )  {
			  if  (  bFloppy  )  {  
				  iAssetType  =  CONST_assetType_floppy;  bFloppy  =  FALSE;
			  }
		  }
		  traceLogA(  "×é¼þÀàÐÍÎª£º %s",  qyGetDesByType1(  CONST_assetTypeTable,  iAssetType  )  );		  
		  
		  if  (  qyGetRegCfg(  keyBuf,  CONST_regValName_driver,  tmpBuf, sizeof(  tmpBuf  )  )  )  continue;
		  traceLogA(  "×é¼þÎ»ÖÃÎª£º%s",  tmpBuf  );
		  _snprintf(  key1Buf,  sizeof(  key1Buf ),  "%s\\%s",  CONST_qyRootKey_serviceClass_98,  tmpBuf  );
		  traceLogA(  "key1BufÎª:  %s",  key1Buf  );

		  if  (  !(  pComponent  =  nextComponent(  pAssetsInfo  )  )  )  goto  errLabel;
		  pComponent->uiType  = iAssetType;
		  
		  switch  (  iAssetType  )  {
		  		  case	CONST_assetType_monitor:
					    if  (  qyGetRegCfg(  keyBuf,  CONST_regValName_deviceDesc,	driverDescBuf,  sizeof(  driverDescBuf  )  )  )  {  memset(  driverDescBuf,  0,  sizeof(  driverDescBuf  )  );  }
						if  (  qyGetRegCfg(  key1Buf,  pDriverDate,	 driverDateBuf,  sizeof(  driverDateBuf  )  )  )  {  memset(  driverDateBuf,  0,  sizeof(  driverDateBuf  )  );  }
						if  (  qyGetRegCfg(  key1Buf,  pDriverVersion,  driverVersionBuf,  sizeof(  driverVersionBuf  )  )  )  {  memset(  driverVersionBuf,  0,  sizeof(  driverVersionBuf  )  );  }
						if  (  qyGetRegCfg(  keyBuf,  CONST_regValName_mfg,	vendorBuf,  sizeof(  vendorBuf  )  )  )  {  memset(  vendorBuf,  0,  sizeof(  vendorBuf  )  );  }
				
						_snprintf(  pComponent->u.monitor.driverDesc,  sizeof( pComponent->u.monitor.driverDesc  ),  "%s",  driverDescBuf  );
						_snprintf(  pComponent->u.monitor.driverDate,  sizeof(  pComponent->u.monitor.driverDate  ),  "%s",  driverDateBuf  );
						traceLogA(  "Ê±¼ä%s",  pComponent->u.monitor.driverDate  );
						_snprintf(  pComponent->u.monitor.driverVersion,  sizeof( pComponent->u.monitor.driverVersion  ),  "%s",  driverVersionBuf  );
						_snprintf(  pComponent->u.monitor.vendor,  sizeof(  pComponent->u.monitor.vendor  ),  "%s",  vendorBuf  );
						traceLogA(  "ÖÆÔìÉÌ%s",  pComponent->u.monitor.vendor  );

						bWanted  =  TRUE;  break;

				  case	CONST_assetType_ideHardDisk:		  
					    
					    if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_hardwareKey,  tmpBuf,  sizeof(  tmpBuf  )  )  )  break;
						_snprintf(  keyBuf,  sizeof(  keyBuf ),  "%s\\%s",  CONST_validRootKey_enum,  tmpBuf  );
						traceLogA(  "Ó²ÅÌkeyBuf is %s",  keyBuf );
						strcpy(  tmpBuf,  "deviceDesc"  );
						pDriverDesc   =  tmpBuf;
		  					    
					    if  (  qyGetRegCfg(  keyBuf,  pDriverDesc,	driverDescBuf,  sizeof(  driverDescBuf  )  )  )  {  memset(  driverDescBuf,  0,  sizeof(  driverDescBuf  )  );  }
						//  if  (  qyGetRegCfg(  key1Buf,  pDriverDate,	driverDateBuf,  sizeof(  driverDateBuf  )  )  )  {  memset(  driverDateBuf,  0,  sizeof(  driverDateBuf  )  );  }
						//  if  (  qyGetRegCfg(  key1Buf,  pVendor,	vendorBuf,  sizeof(  vendorBuf  )  )  )  {  memset(  vendorBuf,  0,  sizeof(  vendorBuf  )  );  }
						//  if  (  qyGetRegCfg(  key1Buf,  pDriverVersion,  driverVersionBuf,  sizeof(  driverVersionBuf  )  )  )  {  memset(  driverVersionBuf,  0,  sizeof(  driverVersionBuf  )  );  }

						_snprintf(  pComponent->u.disk.modelNo,  sizeof( pComponent->u.disk.modelNo  ),  "%s",  driverDescBuf  );
						traceLogA(  " driverDesc is  %s,  ide's  modelNo is  %s",  driverDescBuf,  pComponent->u.disk.modelNo  );
						//  _snprintf(  pComponent->u.disk.driverDate,  sizeof(  pComponent->u.disk.driverDate  ),  "%s",  driverDateBuf  );
						//  _snprintf(  pComponent->u.disk.firmwareRevision,  sizeof( pComponent->u.disk.firmwareRevision  ),  "%s",  driverVersionBuf  );
						//  _snprintf(  pComponent->u.disk.vendor,  sizeof(  pComponent->u.disk.vendor  ),  "%s",  vendorBuf  );  
						bWanted  =  TRUE;  break;
					//  case	CONST_assetType_usbDisk:
						//  _snprintf(  pComponent->u.usb.modelNo,  sizeof( pComponent->u.usb.modelNo  ),  "%s",  driverDescBuf  );
						//  _snprintf(  pComponent->u.usb.driverDate,  sizeof(  pComponent->u.usb.driverDate  ),  "%s",  driverDateBuf  );
						//  _snprintf(  pComponent->u.usb.driverVersion,  sizeof( pComponent->u.usb.driverVersion  ),  "%s",  driverVersionBuf  );
						//  _snprintf(  pComponent->u.usb.vendor,  sizeof(  pComponent->u.usb.vendor  ),  "%s",  vendorBuf  );
						//  break;
				  case	CONST_assetType_ideCdrom:
					    if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_hardwareKey,  tmpBuf,  sizeof(  tmpBuf  )  )  )  break;
						_snprintf(  keyBuf,  sizeof(  keyBuf ),  "%s\\%s",  CONST_validRootKey_enum,  tmpBuf  );
						traceLogA(  "Cdrom keyBuf is %s",  keyBuf );
						strcpy(  tmpBuf,  "deviceDesc"  );
						pDriverDesc   =  tmpBuf;
						
						if  (  qyGetRegCfg(  keyBuf,  pDriverDesc,	driverDescBuf,  sizeof(  driverDescBuf  )  )  )  {  memset(  driverDescBuf,  0,  sizeof(  driverDescBuf  )  );  }
						trim(  driverDescBuf  );
						
						_snprintf(  pComponent->u.disk.modelNo,  sizeof( pComponent->u.disk.modelNo  ),  "%s",  driverDescBuf  );
						//  _snprintf(  pComponent->u.disk.driverDate,  sizeof(  pComponent->u.disk.driverDate  ),  "%s",  driverDateBuf  );
						//  _snprintf(  pComponent->u.disk.firmwareRevision,  sizeof( pComponent->u.disk.firmwareRevision  ),  "%s",  driverVersionBuf  );
						//  _snprintf(  pComponent->u.disk.vendor,  sizeof(  pComponent->u.disk.vendor  ),  "%s",  vendorBuf  );  
						bWanted  =  TRUE;  break; 
				 case	CONST_assetType_display:
					    if  (  qyGetRegCfg(  keyBuf,  CONST_regValName_deviceDesc,	driverDescBuf,  sizeof(  driverDescBuf  )  )  )  {  memset(  driverDescBuf,  0,  sizeof(  driverDescBuf  )  );  }
						if  (  qyGetRegCfg(  key1Buf,  pDriverDate,	driverDateBuf,  sizeof(  driverDateBuf  )  )  )  {  memset(  driverDateBuf,  0,  sizeof(  driverDateBuf  )  );  }
						if  (  qyGetRegCfg(  key1Buf,  pDriverVersion,  driverVersionBuf,  sizeof(  driverVersionBuf  )  )  )  {  memset(  driverVersionBuf,  0,  sizeof(  driverVersionBuf  )  );  }
						if  (  qyGetRegCfg(  keyBuf,  CONST_regValName_mfg,	vendorBuf,  sizeof(  vendorBuf  )  )  )  {  memset(  vendorBuf,  0,  sizeof(  vendorBuf  )  );  }
						
						_snprintf(  pComponent->u.display.driverDesc,  sizeof( pComponent->u.display.driverDesc  ),  "%s",  driverDescBuf  );
						traceLogA(  "ÐÍºÅ%s",  pComponent->u.display.driverDesc  );
						_snprintf(  pComponent->u.display.driverDate,  sizeof(  pComponent->u.display.driverDate  ),  "%s",  driverDateBuf  );
						traceLogA(  "ÈÕÆÚ%s",  pComponent->u.display.driverDate  );
						_snprintf(  pComponent->u.display.driverVersion,  sizeof( pComponent->u.display.driverVersion  ),  "%s",  driverVersionBuf  );
						traceLogA(  "°æ±¾%s",  pComponent->u.display.driverVersion  );
						_snprintf(  pComponent->u.display.vendor,  sizeof(  pComponent->u.display.vendor  ),  "%s",  vendorBuf  );
						traceLogA(  "ÖÆÔìÉÌ%s",  pComponent->u.display.vendor  );
						bWanted  =  TRUE;  break; 
		  
				 case	CONST_assetType_networkCard:
					    _snprintf(  subKeyBuf,  sizeof(  subKeyBuf  ),  "%s\\%s",  key1Buf,  CONST_string_ndiInterfaces  );
						traceLogA(  "subKeyBuf  is  %s",  subKeyBuf  );
						if  (  qyGetRegCfg(  subKeyBuf,  CONST_regValName_lowerRange,  tmpBuf,  sizeof(  tmpBuf  )  )  )  {  traceLogA(  "interfaceÎª:%s,  ÎÞ·¨¶Á³ölowerRange!",  subKeyBuf  );  break;  }
						if  (  _strnicmp(  tmpBuf,  CONST_string_ethernet,  sizeof(  CONST_string_ethernet  )  )  )  {  traceLogA(  "²»ÊÇethernetÍø¿¨!"  );  break;  }
				
						if  (  qyGetRegCfg(  key1Buf,  pDriverDesc,	driverDescBuf,  sizeof(  driverDescBuf  )  )  )  {  memset(  driverDescBuf,  0,  sizeof(  driverDescBuf  )  );  }
						traceLogA(  "DriverDesc  is  %s",  driverDescBuf  );

						if  (  qyGetRegCfg(  key1Buf,  pDriverDate,	driverDateBuf,  sizeof(  driverDateBuf  )  )  )  {  memset(  driverDateBuf,  0,  sizeof(  driverDateBuf  )  );  }
						if  (  qyGetRegCfg(  key1Buf,  pVendor,	vendorBuf,  sizeof(  vendorBuf  )  )  )  {  memset(  vendorBuf,  0,  sizeof(  vendorBuf  )  );  }
						if  (  qyGetRegCfg(  key1Buf,  pDriverVersion,  driverVersionBuf,  sizeof(  driverVersionBuf  )  )  )  {  memset(  driverVersionBuf,  0,  sizeof(  driverVersionBuf  )  );  }
						if  (  qyGetRegCfg(  key1Buf,  pNetworkaddress,  networkaddressBuf,  sizeof(  networkaddressBuf  )  )  )  {  memset(  networkaddressBuf,  0,  sizeof(  networkaddressBuf  )  );  }
						//  if  (  qyGetRegCfg(  networkCfgBuf,  pName,  nameBuf,  sizeof(  nameBuf  )  )  )  {  memset(  nameBuf,  0,  sizeof(  nameBuf  )  );  }
				
						_snprintf(  pComponent->u.net.name,  sizeof(  pComponent->u.net.name  ),  "%s",  nameBuf  );
						_snprintf(  pComponent->u.net.driverDesc,  sizeof( pComponent->u.net.driverDesc  ),  "%s",  driverDescBuf  );
						_snprintf(  pComponent->u.net.driverDate,  sizeof(  pComponent->u.net.driverDate  ),  "%s",  driverDateBuf  );
						_snprintf(  pComponent->u.net.driverVersion,  sizeof( pComponent->u.net.driverVersion  ),  "%s",  driverVersionBuf  );
						_snprintf(  pComponent->u.net.vendor,  sizeof(  pComponent->u.net.vendor  ),  "%s",  vendorBuf  );
						//  _snprintf(  pComponent->u.net.networkaddress,  sizeof(  pComponent->u.net.networkaddress  ),  "%s",  networkaddressBuf  );
						bWanted  =  TRUE;  break;
				 case   CONST_assetType_floppy:
				 		if  (  qyGetRegCfg(  keyBuf,  CONST_regValName_deviceDesc,	driverDescBuf,  sizeof(  driverDescBuf  )  )  )  {  memset(  driverDescBuf,  0,  sizeof(  driverDescBuf  )  );  }
						if  (  qyGetRegCfg(  key1Buf,  pDriverDate,	driverDateBuf,  sizeof(  driverDateBuf  )  )  )  {  memset(  driverDateBuf,  0,  sizeof(  driverDateBuf  )  );  }
						if  (  qyGetRegCfg(  key1Buf,  pDriverVersion,  driverVersionBuf,  sizeof(  driverVersionBuf  )  )  )  {  memset(  driverVersionBuf,  0,  sizeof(  driverVersionBuf  )  );  }
						if  (  qyGetRegCfg(  keyBuf,  CONST_regValName_mfg,	vendorBuf,  sizeof(  vendorBuf  )  )  )  {  memset(  vendorBuf,  0,  sizeof(  vendorBuf  )  );  }
		
						_snprintf(  pComponent->u.floppy.driverDesc,  sizeof( pComponent->u.floppy.driverDesc  ),  "%s",  driverDescBuf  );
						traceLogA(  "ÐÍºÅ%s",  pComponent->u.floppy.driverDesc  );
						_snprintf(  pComponent->u.floppy.driverDate,  sizeof(  pComponent->u.floppy.driverDate  ),  "%s",  driverDateBuf  );
						traceLogA(  "ÈÕÆÚ%s",  pComponent->u.floppy.driverDate  );
						_snprintf(  pComponent->u.floppy.driverVersion,  sizeof( pComponent->u.floppy.driverVersion  ),  "%s",  driverVersionBuf  );
						_snprintf(  pComponent->u.floppy.vendor,  sizeof(  pComponent->u.floppy.vendor  ),  "%s",  vendorBuf  );
						bWanted  = TRUE;  break;

				 default:
					    traceLogA(  "Î´Öª»ò²»Ðè´¦ÀíµÄÉè±¸!"  );
						break;
		  }
		  
		  if  (  bWanted  )  {
			  #ifdef	__DEBUG__	
	 					printComponentInfo(  cnt,  pComponent  );
			  #endif
			  submitComponent(  pAssetsInfo,  0  );  cnt ++;  
		  }
		  
	 }  //  end of for(  ;  ;  )

	 RegCloseKey(  hKey  );  bKeyOpen  =  FALSE;

	 iErr  =  0;
errLabel:

	 if  (  bKeyOpen  )  RegCloseKey(  hKey  );

	 return  iErr;
}

#endif

 int  myGet98Devs(  QWM_ASSETS_INFO  *  pAssetsInfo  )
 {
	 return  -1;
 }


 int  myGetDevs(  void  *  pRegToolParam,  QWM_ASSETS_INFO  *  pAssetsInfo  )
{
	 int						iErr								=  -1;
	 QY_REG_TOOL			*	pRegTool							=	(  QY_REG_TOOL  *  )pRegToolParam;
	 HKEY						hKey								=  NULL;
	 HKEY						hKey1								=  NULL;
	 HKEY						hKey2								=  NULL;
	 HKEY						hKey3								=  NULL;
	 BOOL						bKeyOpen							=  FALSE;
	 BOOL						bKey1Open							=  FALSE;
	 BOOL						bKey2Open							=  FALSE;
	 BOOL						bKey3Open							=  FALSE;
	 //  ×é¼þ³õÊ¼»¯²ÎÊý
	 TCHAR					*   pEnumKey							=  _T(  CONST_qyRootKey_enum  );
	 char					*	pClassGUID							=  CONST_classGUID_networkCard;	
	 char					*   pString								=  CONST_string_connection;
	 int						iAssetType							=  CONST_assetType_networkCard;
	 //  Æ¥Åä²ÎÊý
	 //  char						matchingDeviceBuf[MAX_PATH  +  1]	=  "";
	 //  Êý¾Ý
	 char					*	pVendor								=  CONST_regValName_vender;
	 TCHAR					*   pDriverDate							=  _T(  CONST_regValName_driverDate  );
	 TCHAR					*   pDriverDesc							=  _T(  CONST_regValName_driverDesc  );
	 TCHAR					*   pDriverVersion						=  _T(  CONST_regValName_driverVersion  );
	 char					*   pNetworkaddress						=  CONST_regValName_networkaddress;
	 char					*   pName								=  CONST_regValName_name;		//  ±¾µØÁ¬½Ó
	 TCHAR						vendorBuf[64  + 1]					=  _T(  ""  );
	 TCHAR						driverDateBuf[64 +1]				=  _T(  ""  );
	 TCHAR						driverDescBuf[256 +1]				=  _T(  ""  );
	 TCHAR						driverVersionBuf[64 + 1]			=  _T(  ""  );
	 //  char						networkaddressBuf[12 + 1]			=  "";
	 //  char						nameBuf[16 + 1]						=  "";
	 //  ±äÁ¿
	 int						iRet								=  0;
	 TCHAR						tSubKey[MAX_PATH  +  1]				=  _T(  ""  );
	 TCHAR						tSubKey1[MAX_PATH  +  1]			=  _T(  ""  );
	 TCHAR						tSubKey2[MAX_PATH  +  1]			=  _T(  ""  );
	 TCHAR						tmpBuf[MAX_PATH  +  1]				=  _T(  ""  );
	 int						i  =  0,  i1 = 0, i2 = 0, cnt	=  0;
	 TCHAR						keyBuf[MAX_PATH  +  1]				=	_T(  ""  );
	 TCHAR						key1Buf[MAX_PATH  +  1]				=	_T(  ""  );
	 TCHAR						key2Buf[MAX_PATH  +  1]				=	_T(  ""  );
	 TCHAR						subKeyBuf[MAX_PATH  + 1]			=	_T(  ""  );
	 //  char						enumDeviceBuf[MAX_PATH  + 1]		=  "";
 	 TCHAR						classDeviceBuf[MAX_PATH  + 1]		=  _T(  ""  );
	 //  char						networkCfgBuf[MAX_PATH + 1]			=  "";
	 BOOL						bWanted								=  FALSE;
	 BOOL						bUsb								=  FALSE;
	 QWM_COMPONENT_INFO		*	pComponent							=  NULL;
	 char						buf[1024]							=	"";
	 
	 traceLogA(  "myGetDevs():  enters"  );
	 if  (  !pRegTool  ||  !pAssetsInfo  )  goto  errLabel;

	 if  (  (  iRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  pEnumKey,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey  )  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	 bKeyOpen  =  TRUE;
	 for  (  i = 0; ; i ++  )  {

		  iRet  =  RegEnumKey(  hKey,  i,  tSubKey,  mycountof(  tSubKey  )  );
		  if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  )  break;
		  //  keyBuf:  enumÏÂÒ»¼¶Ä¿Â¼,  ÀýÈç£ºenmu\\display
		  _sntprintf(  keyBuf,  mycountof(  keyBuf  ),  _T(  "%s\\%s"  ),  pEnumKey,  tSubKey  );
		  if  ( !_tcsnicmp(  tSubKey,  _T(  CONST_enumName_usbstor  ),  strlen(  CONST_enumName_usbstor  )  )  )  bUsb  =  TRUE;
		  else  bUsb  =  FALSE;		//  2006/03/26
		  if  (  (  iRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  keyBuf,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey1  )  ) !=  ERROR_SUCCESS  )  continue;
		  bKey1Open  =  TRUE;
		  for  (  i1 = 0; ; i1 ++  )  {
			   iRet  =  RegEnumKey(  hKey1,  i1,  tSubKey1,  mycountof(  tSubKey1  )  );
			   if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  )  break;
			   //  key1Buf:  enumÏÂ¶þ¼¶Ä¿Â¼,  enum\\default_monitor
			   _sntprintf(  key1Buf, mycountof(  key1Buf  ),  _T(  "%s\\%s"  ),  keyBuf,  tSubKey1 );

			   if  (  (  iRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  key1Buf,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey2  )  )  !=  ERROR_SUCCESS  )  continue;
			   bKey2Open  =  TRUE;

			   for  (  i2 = 0;  ; i2 ++  )  {
				    iRet  =  RegEnumKey(  hKey2,  i2,  tSubKey2,  mycountof(  tSubKey2  )  );
					if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  )  break;
					//  key2Buf:  enumÏÂÈý¼¶Ä¿Â¼,  enum\\default_monitor_4&5248809&0&80861100&00&02
					_sntprintf(  key2Buf,  mycountof(  key2Buf  ),  _T(  "%s\\%s"  ),  key1Buf,  tSubKey2  );
					_sntprintf(  subKeyBuf,  mycountof(  subKeyBuf  ),  _T(  "%s\\%s"  ),  key2Buf,  _T(  CONST_validRootKey_control  )  );
					if  (  (  iRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  subKeyBuf,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey3  )  )  !=  ERROR_SUCCESS  )  continue;
					bKey3Open  =  TRUE;
					
					traceLog(  _T(  "%d¸ hardwareKey(%s)"  ),  cnt,  subKeyBuf  );  cnt  ++;

					bWanted  =  FALSE;
					if  (  qyGetRegCfg(  key2Buf,  _T(  CONST_regValName_classGUID  ),  (  char  *  )tmpBuf,  sizeof(  tmpBuf  )  )  )  continue;
					if  (  (  iAssetType  =  myGetTypeByDes(  CONST_classGUIDTable,  tmpBuf  )  )  <  0  )  continue;
					if  (  iAssetType  ==  CONST_assetType_ideHardDisk  &&  bUsb   )  {
						iAssetType  =  CONST_assetType_usbDisk;
						traceLogA(  "ucbDisk"  );  //  bUsb  =  FALSE;		//  2006/03/26  
					}

					traceLog(  _T(  "assetType %s"  ),  qyGetDesByType1(  CONST_assetTypeTable,  iAssetType  )  );
		  
					if  (  qyGetRegCfg(  key2Buf,  _T(  CONST_regValName_driver  ),  (  char  *  )tmpBuf, sizeof(  tmpBuf  )  )  )  continue;
		  			traceLog(  _T(  "driver %s"  ),  tmpBuf  );
					_sntprintf(  classDeviceBuf,  mycountof(  classDeviceBuf ),  _T(  "%s\\%s"  ),  _T(  CONST_qyRootKey_controlClass  ),  tmpBuf  );
		  			traceLog(  _T(  "class keyBuf:  %s"  ),  classDeviceBuf  );
		  
					if  (  !(  pComponent  =  nextComponent(  pAssetsInfo  )  )  )  goto  errLabel;
					pComponent->uiType  = iAssetType;
					
					switch  (  iAssetType  )  {
							case	CONST_assetType_monitor:
								    //  if  (  qyGetRegCfg(  key2Buf,  CONST_regValName_deviceDesc,	driverDescBuf,  sizeof(  driverDescBuf  )  )  )  {  memset(  driverDescBuf,  0,  sizeof(  driverDescBuf  )  );  }
								    if  (  qyGetRegCfg(  classDeviceBuf,  pDriverDesc,	(  char  *  )driverDescBuf,  sizeof(  driverDescBuf  )  )  )  {  memset(  driverDescBuf,  0,  sizeof(  driverDescBuf  )  );  }	//  2007/02/21, ÒòVISTA¶ÁÈ¡²»¶Ô£¬×öÐÞ¸Ä
									//
									if  (  qyGetRegCfg(  classDeviceBuf,  pDriverDate,	(  char  *  )driverDateBuf,  sizeof(  driverDateBuf  )  )  )  {  memset(  driverDateBuf,  0,  sizeof(  driverDateBuf  )  );  }
									if  (  qyGetRegCfg(  classDeviceBuf,  pDriverVersion,  (  char  *  )driverVersionBuf,  sizeof(  driverVersionBuf  )  )  )  {  memset(  driverVersionBuf,  0,  sizeof(  driverVersionBuf  )  );  }
									if  (  qyGetRegCfg(  key2Buf,  _T(  CONST_regValName_mfg  ),	(  char  *  )vendorBuf,  sizeof(  vendorBuf  )  )  )  {  memset(  vendorBuf,  0,  sizeof(  vendorBuf  )  );  }
									
								#if  0
									_snprintf(  pComponent->u.monitor.driverDesc,  sizeof( pComponent->u.monitor.driverDesc  ),  "%s",  driverDescBuf  );
									_snprintf(  pComponent->u.monitor.driverDate,  sizeof(  pComponent->u.monitor.driverDate  ),  "%s",  driverDateBuf  );
									_snprintf(  pComponent->u.monitor.driverVersion,  sizeof( pComponent->u.monitor.driverVersion  ),  "%s",  driverVersionBuf  );
									_snprintf(  pComponent->u.monitor.vendor,  sizeof(  pComponent->u.monitor.vendor  ),  "%s",  vendorBuf  );
								#endif
									myTChar2Utf8(  driverDescBuf,  pComponent->u.monitor.driverDesc,  sizeof( pComponent->u.monitor.driverDesc  )  );
									myTChar2Utf8(  driverDateBuf,  pComponent->u.monitor.driverDate,  sizeof(  pComponent->u.monitor.driverDate  )  );
									myTChar2Utf8(  driverVersionBuf,  pComponent->u.monitor.driverVersion,  sizeof( pComponent->u.monitor.driverVersion  )  );
									myTChar2Utf8(  vendorBuf,  pComponent->u.monitor.vendor,  sizeof(  pComponent->u.monitor.vendor  )  );

									bWanted  =  TRUE;  break;
							case	CONST_assetType_ideHardDisk:		  
								    if  (  qyGetRegCfg(  key2Buf,  _T(  CONST_regValName_friendlyName  ),  (  char  *  )driverDescBuf,  sizeof(  driverDescBuf  )  )  )  break;
									if  (  qyGetRegCfg(  classDeviceBuf,  pDriverDate,	(  char  *  )driverDateBuf,  sizeof(  driverDateBuf  )  )  )  {  memset(  driverDateBuf,  0,  sizeof(  driverDateBuf  )  );  }
									if  (  qyGetRegCfg(  classDeviceBuf,  pDriverVersion,	(  char  *  )driverVersionBuf,  sizeof(  driverVersionBuf  )  )  )  {  memset(  driverVersionBuf,  0,  sizeof(  driverVersionBuf  )  );  }
									if  (  qyGetRegCfg(  key2Buf,  _T(  CONST_regValName_mfg  ),  (  char  *  )vendorBuf,  sizeof(  vendorBuf  )  )  )  {  memset(  vendorBuf,  0,  sizeof(  vendorBuf  )  );  }
								#if  0
									_snprintf(  pComponent->u.disk.modelNo,  sizeof( pComponent->u.disk.modelNo  ),  "%s",  driverDescBuf  );
									_snprintf(  pComponent->u.disk.driverDate,  sizeof(  pComponent->u.disk.driverDate  ),  "%s",  driverDateBuf  );
									_snprintf(  pComponent->u.disk.firmwareRevision,  sizeof( pComponent->u.disk.firmwareRevision  ),  "%s",  driverVersionBuf  );
									_snprintf(  pComponent->u.disk.vendor,  sizeof(  pComponent->u.disk.vendor  ),  "%s",  vendorBuf  );  
								#endif
									myTChar2Utf8(  driverDescBuf,  pComponent->u.disk.modelNo,  sizeof( pComponent->u.disk.modelNo  )  );
									myTChar2Utf8(  driverDateBuf,  pComponent->u.disk.driverDate,  sizeof(  pComponent->u.disk.driverDate  )  );
									myTChar2Utf8(  driverVersionBuf,  pComponent->u.disk.firmwareRevision,  sizeof( pComponent->u.disk.firmwareRevision  )  );
									myTChar2Utf8(  vendorBuf,  pComponent->u.disk.vendor,  sizeof(  pComponent->u.disk.vendor  )  );  
									bWanted  =  TRUE;  break;
							case	CONST_assetType_usbDisk:
								    break;						//  2006/03/26, USBDisk
								    if  (  qyGetRegCfg(  key2Buf,  _T(  CONST_regValName_friendlyName  ),  (  char  *  )driverDescBuf,  sizeof(  driverDescBuf  )  )  )  break;
									if  (  qyGetRegCfg(  classDeviceBuf,  pDriverDate,	(  char  *  )driverDateBuf,  sizeof(  driverDateBuf  )  )  )  {  memset(  driverDateBuf,  0,  sizeof(  driverDateBuf  )  );  }
									if  (  qyGetRegCfg(  classDeviceBuf,  pDriverVersion,	(  char  *  )driverVersionBuf,  sizeof(  driverVersionBuf  )  )  )  {  memset(  driverVersionBuf,  0,  sizeof(  driverVersionBuf  )  );  }
									if  (  qyGetRegCfg(  key2Buf,  _T(  CONST_regValName_mfg  ),  (  char  *  )vendorBuf,  sizeof(  vendorBuf  )  )  )  {  memset(  vendorBuf,  0,  sizeof(  vendorBuf  )  );  }
								#if  0
									_snprintf(  pComponent->u.disk.modelNo,  sizeof( pComponent->u.disk.modelNo  ),  "%s",  driverDescBuf  );
									_snprintf(  pComponent->u.disk.driverDate,  sizeof(  pComponent->u.disk.driverDate  ),  "%s",  driverDateBuf  );
									_snprintf(  pComponent->u.disk.firmwareRevision,  sizeof( pComponent->u.disk.firmwareRevision  ),  "%s",  driverVersionBuf  );
									_snprintf(  pComponent->u.disk.vendor,  sizeof(  pComponent->u.disk.vendor  ),  "%s",  vendorBuf  );  
								#endif
									myTChar2Utf8(  driverDescBuf,  pComponent->u.disk.modelNo,  sizeof( pComponent->u.disk.modelNo  )  );
									myTChar2Utf8(  driverDateBuf,  pComponent->u.disk.driverDate,  sizeof(  pComponent->u.disk.driverDate  )  );
									myTChar2Utf8(  driverVersionBuf,  pComponent->u.disk.firmwareRevision,  sizeof( pComponent->u.disk.firmwareRevision  )  );
									myTChar2Utf8(  vendorBuf,  pComponent->u.disk.vendor,  sizeof(  pComponent->u.disk.vendor  )  );  
									bWanted  =  TRUE;  break;  
							case	CONST_assetType_ideCdrom:
									if  (  qyGetRegCfg(  key2Buf,  _T(  CONST_regValName_friendlyName  ),  (  char  *  )driverDescBuf,  sizeof(  driverDescBuf  )  )  )  break;
									if  (  qyGetRegCfg(  classDeviceBuf,  pDriverDate,	(  char  *  )driverDateBuf,  sizeof(  driverDateBuf  )  )  )  {  memset(  driverDateBuf,  0,  sizeof(  driverDateBuf  )  );  }
									if  (  qyGetRegCfg(  classDeviceBuf,  pDriverVersion,	(  char  *  )driverVersionBuf,  sizeof(  driverVersionBuf  )  )  )  {  memset(  driverVersionBuf,  0,  sizeof(  driverVersionBuf  )  );  }
									if  (  qyGetRegCfg(  key2Buf,  _T(  CONST_regValName_mfg  ),  (  char  *  )vendorBuf,  sizeof(  vendorBuf  )  )  )  {  memset(  vendorBuf,  0,  sizeof(  vendorBuf  )  );  }
								#if  0									
									_snprintf(  pComponent->u.disk.modelNo,  sizeof( pComponent->u.disk.modelNo  ),  "%s",  driverDescBuf  );
									_snprintf(  pComponent->u.disk.driverDate,  sizeof(  pComponent->u.disk.driverDate  ),  "%s",  driverDateBuf  );
									_snprintf(  pComponent->u.disk.firmwareRevision,  sizeof( pComponent->u.disk.firmwareRevision  ),  "%s",  driverVersionBuf  );
									_snprintf(  pComponent->u.disk.vendor,  sizeof(  pComponent->u.disk.vendor  ),  "%s",  vendorBuf  );  
								#endif
									myTChar2Utf8(  driverDescBuf,  pComponent->u.disk.modelNo,  sizeof( pComponent->u.disk.modelNo  )  );
									myTChar2Utf8(  driverDateBuf,  pComponent->u.disk.driverDate,  sizeof(  pComponent->u.disk.driverDate  )  );
									myTChar2Utf8(  driverVersionBuf,  pComponent->u.disk.firmwareRevision,  sizeof( pComponent->u.disk.firmwareRevision  )  );
									myTChar2Utf8(  vendorBuf,  pComponent->u.disk.vendor,  sizeof(  pComponent->u.disk.vendor  )  );  
									bWanted  =  TRUE;  break; 
							case	CONST_assetType_display:  
								    BOOL	bChk_volatileSettings;  bChk_volatileSettings  =  FALSE;

								    switch  (  pRegTool->env.iPlatformId  )  {
											case  CONST_qyPlatform_win98:
											case  CONST_qyPlatform_winme:
											case  CONST_qyPlatform_nt:
											case  CONST_qyPlatform_win2k:
										    case  CONST_qyPlatform_winxp:
												  break;
											default:
												   bChk_volatileSettings  =  TRUE;
												   break;
									}
									if  (  bChk_volatileSettings  )  {								
										_sntprintf(  subKeyBuf,  mycountof(  subKeyBuf  ),  _T(  "%s\\%s"  ),  classDeviceBuf,  _T(  "VolatileSettings"  )  );
										HKEY	hKey4	=	NULL;
										if  (  (  iRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  subKeyBuf,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey4  )  )  !=  ERROR_SUCCESS  )  break;
										RegCloseKey(  hKey4  );
									}

									//  if  (  qyGetRegCfg(  key2Buf,  CONST_regValName_deviceDesc,	driverDescBuf,  sizeof(  driverDescBuf  )  )  )  {  memset(  driverDescBuf,  0,  sizeof(  driverDescBuf  )  );  }
									if  (  qyGetRegCfg(  classDeviceBuf,  pDriverDesc,	(  char  *  )driverDescBuf,  sizeof(  driverDescBuf  )  )  )  {  memset(  driverDescBuf,  0,  sizeof(  driverDescBuf  )  );  }	//  2007/02/21
									//
									if  (  qyGetRegCfg(  classDeviceBuf,  pDriverDate,	(  char  *  )driverDateBuf,  sizeof(  driverDateBuf  )  )  )  {  memset(  driverDateBuf,  0,  sizeof(  driverDateBuf  )  );  }
									if  (  qyGetRegCfg(  classDeviceBuf,  pDriverVersion,  (  char  *  )driverVersionBuf,  sizeof(  driverVersionBuf  )  )  )  {  memset(  driverVersionBuf,  0,  sizeof(  driverVersionBuf  )  );  }
									if  (  qyGetRegCfg(  key2Buf,  _T(  CONST_regValName_mfg  ),	(  char  *  )vendorBuf,  sizeof(  vendorBuf  )  )  )  {  memset(  vendorBuf,  0,  sizeof(  vendorBuf  )  );  }
								#if  0
									_snprintf(  pComponent->u.display.driverDesc,  sizeof( pComponent->u.display.driverDesc  ),  "%s",  driverDescBuf  );
									_snprintf(  pComponent->u.display.driverDate,  sizeof(  pComponent->u.display.driverDate  ),  "%s",  driverDateBuf  );
									_snprintf(  pComponent->u.display.driverVersion,  sizeof( pComponent->u.display.driverVersion  ),  "%s",  driverVersionBuf  );
									_snprintf(  pComponent->u.display.vendor,  sizeof(  pComponent->u.display.vendor  ),  "%s",  vendorBuf  );
								#endif
									myTChar2Utf8(  driverDescBuf,  buf,  mycountof(  buf  )  );  safeStrnCpy(  buf,  pComponent->u.display.driverDesc,  sizeof( pComponent->u.display.driverDesc  )  );
									myTChar2Utf8(  driverDateBuf,  buf,  mycountof(  buf  )  );  safeStrnCpy(  buf,    pComponent->u.display.driverDate,  sizeof(  pComponent->u.display.driverDate  )  );
									myTChar2Utf8(  driverVersionBuf,  buf,  mycountof(  buf  )  );  safeStrnCpy(  buf,    pComponent->u.display.driverVersion,  sizeof( pComponent->u.display.driverVersion  )  );
									myTChar2Utf8(  vendorBuf,  buf,  mycountof(  buf  )  );  safeStrnCpy(  buf,    pComponent->u.display.vendor,  sizeof(  pComponent->u.display.vendor  )  );
									bWanted  =  TRUE;  break; 
							case	CONST_assetType_networkCard:
									_sntprintf(  subKeyBuf,  mycountof(  subKeyBuf  ),  _T(  "%s\\%s"  ),  classDeviceBuf,  _T(  CONST_string_ndiInterfaces  )  );
									traceLogA(  "subKeyBuf  is  %s",  subKeyBuf  );
									if  (  qyGetRegCfg(  subKeyBuf,  _T(  CONST_regValName_lowerRange  ),  (  char  *  )tmpBuf,  sizeof(  tmpBuf  )  )  )  {  traceLogA(  "interfaceÎª:%s,  ÎÞ·¨¶Á³ölowerRange!",  subKeyBuf  );  break;  }
									if  (  _tcsnicmp(  tmpBuf,  _T(  CONST_string_ethernet  ),  sizeof(  CONST_string_ethernet  )  )  )  {  traceLogA(  "not ethernetÍ!"  );  break;  }
				
									//  if  (  qyGetRegCfg(  key2Buf,  CONST_regValName_deviceDesc,	driverDescBuf,  sizeof(  driverDescBuf  )  )  )  {  memset(  driverDescBuf,  0,  sizeof(  driverDescBuf  )  );  }
									if  (  qyGetRegCfg(  classDeviceBuf,  pDriverDesc,	(  char  *  )driverDescBuf,  sizeof(  driverDescBuf  )  )  )  {  memset(  driverDescBuf,  0,  sizeof(  driverDescBuf  )  );  }	//  2007/02/21, Òòvista¶ÁÈ¡²»¶Ô¶øÐÞ¸Ä¶ÁÈ¡Î»ÖÃ
									traceLog(  _T(  "DriverDesc  is  %s"  ),  driverDescBuf  );
				
									if  (  qyGetRegCfg(  classDeviceBuf,  pDriverDate,	(  char  *  )driverDateBuf,  sizeof(  driverDateBuf  )  )  )  {  memset(  driverDateBuf,  0,  sizeof(  driverDateBuf  )  );  }
									if  (  qyGetRegCfg(  classDeviceBuf,  pDriverVersion,  (  char  *  )driverVersionBuf,  sizeof(  driverVersionBuf  )  )  )  {  memset(  driverVersionBuf,  0,  sizeof(  driverVersionBuf  )  );  }
									if  (  qyGetRegCfg(  key2Buf,  _T(  CONST_regValName_mfg  ),	(  char  *  )vendorBuf,  sizeof(  vendorBuf  )  )  )  {  memset(  vendorBuf,  0,  sizeof(  vendorBuf  )  );  }
									//  if  (  qyGetRegCfg(  classDeviceBuf,  pNetworkaddress,  networkaddressBuf,  sizeof(  networkaddressBuf  )  )  )  {  memset(  networkaddressBuf,  0,  sizeof(  networkaddressBuf  )  );  }
									//  if  (  qyGetRegCfg(  networkCfgBuf,  pName,  nameBuf,  sizeof(  nameBuf  )  )  )  {  memset(  nameBuf,  0,  sizeof(  nameBuf  )  );  }
								#if  0
									//  _snprintf(  pComponent->u.net.name,  sizeof(  pComponent->u.net.name  ),  "%s",  nameBuf  );
									_snprintf(  pComponent->u.net.driverDesc,  sizeof( pComponent->u.net.driverDesc  ),  "%s",  driverDescBuf  );
									_snprintf(  pComponent->u.net.driverDate,  sizeof(  pComponent->u.net.driverDate  ),  "%s",  driverDateBuf  );
									_snprintf(  pComponent->u.net.driverVersion,  sizeof( pComponent->u.net.driverVersion  ),  "%s",  driverVersionBuf  );
									_snprintf(  pComponent->u.net.vendor,  sizeof(  pComponent->u.net.vendor  ),  "%s",  vendorBuf  );
									//  _snprintf(  pComponent->u.net.networkaddress,  sizeof(  pComponent->u.net.networkaddress  ),  "%s",  networkaddressBuf  );
								#endif
									myTChar2Utf8(  driverDescBuf,  buf,  mycountof(  buf  )  );  safeStrnCpy(  buf,  pComponent->u.net.driverDesc,  sizeof( pComponent->u.net.driverDesc  )  );
									myTChar2Utf8(  driverDateBuf,  pComponent->u.net.driverDate,  sizeof(  pComponent->u.net.driverDate  )  );
									myTChar2Utf8(  driverVersionBuf,  pComponent->u.net.driverVersion,  sizeof( pComponent->u.net.driverVersion  )  );
									myTChar2Utf8(  vendorBuf,  pComponent->u.net.vendor,  sizeof(  pComponent->u.net.vendor  )  );
									bWanted  =  TRUE;  break;
							case    CONST_assetType_floppy:
									if  (  qyGetRegCfg(  key2Buf,  _T(  CONST_regValName_deviceDesc  ),	(  char  *  )driverDescBuf,  sizeof(  driverDescBuf  )  )  )  {  memset(  driverDescBuf,  0,  sizeof(  driverDescBuf  )  );  }
									if  (  qyGetRegCfg(  classDeviceBuf,  pDriverDate,	(  char  *  )driverDateBuf,  sizeof(  driverDateBuf  )  )  )  {  memset(  driverDateBuf,  0,  sizeof(  driverDateBuf  )  );  }
									if  (  qyGetRegCfg(  classDeviceBuf,  pDriverVersion,  (  char  *  )driverVersionBuf,  sizeof(  driverVersionBuf  )  )  )  {  memset(  driverVersionBuf,  0,  sizeof(  driverVersionBuf  )  );  }
									if  (  qyGetRegCfg(  key2Buf,  _T(  CONST_regValName_mfg  ),	(  char  *  )vendorBuf,  sizeof(  vendorBuf  )  )  )  {  memset(  vendorBuf,  0,  sizeof(  vendorBuf  )  );  }
								#if  0
									_snprintf(  pComponent->u.floppy.driverDesc,  sizeof( pComponent->u.floppy.driverDesc  ),  "%s",  driverDescBuf  );
									_snprintf(  pComponent->u.floppy.driverDate,  sizeof(  pComponent->u.floppy.driverDate  ),  "%s",  driverDateBuf  );
									_snprintf(  pComponent->u.floppy.driverVersion,  sizeof( pComponent->u.floppy.driverVersion  ),  "%s",  driverVersionBuf  );
									_snprintf(  pComponent->u.floppy.vendor,  sizeof(  pComponent->u.floppy.vendor  ),  "%s",  vendorBuf  );
								#endif
									myTChar2Utf8(  driverDescBuf,  pComponent->u.floppy.driverDesc,  sizeof( pComponent->u.floppy.driverDesc  )  );
									myTChar2Utf8(  driverDateBuf,  pComponent->u.floppy.driverDate,  sizeof(  pComponent->u.floppy.driverDate  )  );
									myTChar2Utf8(  driverVersionBuf,  pComponent->u.floppy.driverVersion,  sizeof( pComponent->u.floppy.driverVersion  )  );
									myTChar2Utf8(  vendorBuf,  pComponent->u.floppy.vendor,  sizeof(  pComponent->u.floppy.vendor  )  );
								    bWanted  =  TRUE;  break;
							default:
									traceLogA(  "myGetDevs"  );
									break;
					}
					if  (  bWanted  )  {
						#ifdef	__DEBUG__	
								printComponentInfo(  cnt,  pComponent  );
						#endif
						submitComponent(  pAssetsInfo,  0  );  cnt ++;  
					}

				}  //  end of for(  ;  ;  )
			}
	 }
	 RegCloseKey(  hKey  );  bKeyOpen  =  FALSE;
	 RegCloseKey(  hKey1  );  bKey1Open	 =  FALSE;
	 RegCloseKey(  hKey2  );  bKey2Open  =  FALSE;
	 RegCloseKey(  hKey3  );  bKey3Open  =  FALSE;

	 iErr  =  0;
errLabel:

	 if  (  bKeyOpen  )  RegCloseKey(  hKey  );
	 if  (  bKey1Open  )  RegCloseKey(  hKey1  );
	 if  (  bKey2Open  )  RegCloseKey(  hKey2  );
	 if  (  bKey3Open  )  RegCloseKey(  hKey3  );
	 return  iErr;
}


#if  0
 int  myGet98IdeDiskInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  )
{	 
	 int						iErr						=	-1;
	 int						iRet						=   0;
	 char					*	pEnumKey					=	NULL;
	 char					*   pEnumKey1					=   CONST_qyRootKey_configMgrEnum_98;
 	 HKEY						hKey						=   NULL;
	 HKEY						hKey1						=   NULL;
	 HKEY						hKey2						=	NULL;
	 BOOL						bKeyOpen					=	FALSE;
	 BOOL						bKey1Open					=	FALSE;
	 BOOL						bKey2Open					=	FALSE;
	 char						tSubKey[MAX_PATH  +  1]		=   "";  
	 char						tSubKey1[MAX_PATH  +  1]	=   "";
	 char						tSubKey2[MAX_PATH  +  1]	=	"";
	 int						i = 0, i1 = 0, i2 = 0, cnt1 = 0, cnt2  =0;
	 char						dataKey[MAX_PATH + 1]		=   "";
	 char						activeDataKey[MAX_PATH + 1] =   "";
	 char						tmpKey[MAX_PATH  +  1]		=	"";
	 char						dataBuf[MAX_PATH + 1]		=	"";		//  ÐèÑéÖ¤Öµ
	 char						activeDataBuf[MAX_PATH + 1] =	"";
	 QY_REG						reg;
	 //  QY_REG						reg1;
	 char						regValBuf[255]				=   "";
	 char						regValBuf1[255]				=	"";
	 QWM_COMPONENT_INFO		*	pComponent					=	NULL;

	 if  (  !pAssetsInfo  )  return  -1;
	 traceLogA(  "myGet98IdeDiskInfo()  enter"  );

	 //  Ó²ÅÌ	[HKEY_LOCAL_MACHINE\Enum\ESDI\GENERIC_IDE__DISK_TYPE47_\MF&CHILD0000&PCI&VEN_1106&DEV_0571&SUBSYS_05711106&REV_10&BUS_00&DEV_07&FUNC_0110]
	 pEnumKey  =  CONST_qyRootKey_ideDisk_98;
	 //  µÚÒ»²ãÃ¶¾Ù:Enum\ESDI\ÏÂ
	 if  (  (  iRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  pEnumKey,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey  )  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	 bKeyOpen  =  TRUE;
	 for  (  i = 0; ; i ++ )  {
		  iRet  =  RegEnumKey(  hKey,  i,  tSubKey, sizeof(  tSubKey  )  );
		  if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  )  break;
		  _snprintf(  dataKey,  sizeof(  dataKey  ),  "%s\\%s",  pEnumKey,  tSubKey  );  
		  _snprintf(  dataBuf,  sizeof(  dataBuf  ),  "%s\\%s",  "ESDI",  tSubKey  );
		  traceLogA(  "  µÃµ½µÚ%d¸öÐèÑéÖ¤µÄÓ²¼þÊý¾ÝµÄÇ°Ãæ²¿·Ö:%s",  i,  dataBuf  );

		  //  µÚ¶þ²ãÃ¶¾Ù£ºEnum\ESDI\GENERIC_IDE__DISK_TYPE47_\ÏÂ
		  if  (  (  iRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  dataKey,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey2  )  )  !=  ERROR_SUCCESS  )  goto  errLabel;
		  bKey2Open	=  TRUE;
		  for  (  i2 = 0; ; i2 ++ )  {
			   iRet  =  RegEnumKey(  hKey2,  i2,  tSubKey2,  sizeof(  tSubKey2  )  );
			   if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  )  break;
			   _snprintf(  activeDataKey,  sizeof(  activeDataKey  ),  "%s\\%s",  dataKey,  tSubKey2  );
   			   _snprintf(  activeDataBuf,  sizeof(  activeDataBuf  ),  "%s\\%s",  dataBuf,  tSubKey2  );
			   traceLogA(  "  µÃµ½µÚ%d¸öÐèÑéÖ¤µÄÍêÕûµÄÓ²¼þÊý¾Ý:%s",  cnt2,  activeDataBuf  );

			   if  (  (  iRet  =  RegOpenKeyEx(  HKEY_DYN_DATA,  pEnumKey1,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey1  )  )  !=  ERROR_SUCCESS  )  goto  errLabel;
			   bKey1Open  =  TRUE;
			   for  (  i1 = 0;  ;  i1++ )  {
				    iRet  =  RegEnumKey(  hKey1,  i1,  tSubKey1,  sizeof(  tSubKey1  )  );
					if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  )  break;
					_snprintf(  tmpKey,  sizeof(  tmpKey  ),  "%s\\%s",  pEnumKey1,  tSubKey1  );
					
					memset(  (  char  *  )&reg,  0,  sizeof(  reg  )  );
					reg.hKeyRoot0  =  HKEY_DYN_DATA;
					lstrcpyn(  reg.rootKey,  tmpKey,  sizeof(  reg.rootKey  )  );
					if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_hardwareKey,  regValBuf,  sizeof(  regValBuf  )  )  )  continue;
					traceLogA(  "µÚ%d¸öhardwareKey is %s",  i1,  regValBuf  );
					
					if  (  _strnicmp(  activeDataBuf,  regValBuf,  strlen(  activeDataBuf  )  )  )  continue;
					traceLogA(  "µÚ%d¸öÆ¥Åä²ÎÊý is %s,ÎªµÚ%d¸öhardwareKey",  cnt1,  regValBuf,  i1  );
							   
					//  µÃµ½µ±Ç°»î¶¯µÄÓ²¼þ²ÎÊý

					
					if  (  qyGetRegCfg(  activeDataKey,  CONST_regValName_deviceDesc,  regValBuf1,  sizeof(  regValBuf1  )  )  )  break;
					traceLogA(  "×é¼þÐÍºÅÎª£º%s",  regValBuf1 );
					if  (  !(  pComponent  =  nextComponent(  pAssetsInfo  )  )  )  goto  errLabel;
					pComponent->uiType  =  CONST_assetType_ideHardDisk;

					_snprintf(  pComponent->u.disk.modelNo,  sizeof(  pComponent->u.disk.modelNo  ),  "%s",  regValBuf1  );
					#ifdef	__DEBUG__	
							printComponentInfo(  cnt2,  pComponent  );
					#endif

					submitComponent(  pAssetsInfo,  0  );
					cnt2  ++;  break;
			   }
			   traceLogA(  "µÚ¶þ²ãÃ¶¾Ù£ºEnum\\ESDI\\GENERIC_IDE__DISK_TYPE47_\\ÏÂµÚ%d¸ö",  cnt1  );
			   cnt1 ++;
			}
	 }
	 RegCloseKey(  hKey  );  bKeyOpen  =  FALSE;
	 RegCloseKey(  hKey1  );  bKey1Open  =  FALSE;
	 RegCloseKey(  hKey2  );  bKey2Open  =  FALSE;

	 iErr  =  0;

errLabel:

	 if  (  bKeyOpen  )  RegCloseKey(  hKey  );
	 if  (  bKey1Open  )  RegCloseKey(  hKey1  );
	 if  (  bKey2Open  )  RegCloseKey(  hKey2  ); 


	 return  iErr;
}
#endif
 int  myGet98IdeDiskInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  )
 {
	 return  -1;
 }

#if  0
 int  myGet98CdromUsbInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  )
{	 
	 int						iErr						=	-1;
	 int						iRet						=   0;
	 char					*	pEnumKey					=	NULL;
	 char					*   pEnumKey1					=   CONST_qyRootKey_configMgrEnum_98;
 	 HKEY						hKey						=   NULL;
	 HKEY						hKey1						=   NULL;
	 HKEY						hKey2						=	NULL;
	 BOOL						bKeyOpen					=	FALSE;
	 BOOL						bKey1Open					=	FALSE;
	 BOOL						bKey2Open					=	FALSE;
	 char						tSubKey[MAX_PATH  +  1]		=   "";  
	 char						tSubKey1[MAX_PATH  +  1]	=   "";
	 char						tSubKey2[MAX_PATH  +  1]	=	"";
	 int						i = 0, i1 = 0, i2 = 0, cnt1 = 0, cnt2  =0;
	 char						dataKey[MAX_PATH + 1]		=   "";
	 char						activeDataKey[MAX_PATH + 1] =   "";
	 char						tmpKey[MAX_PATH  +  1]		=	"";
	 char						dataBuf[MAX_PATH + 1]		=	"";		//  ÐèÑéÖ¤Öµ
	 char						activeDataBuf[MAX_PATH + 1] =	"";
	 QY_REG						reg;
	 //  QY_REG						reg1;
	 char						regValBuf[255]				=   "";
	 char						regValBuf1[255]				=	"";
	 char						classIdBuf[MAX_PATH + 1]	=	"";
	 QWM_COMPONENT_INFO		*	pComponent					=	NULL;

	 if  (  !pAssetsInfo  )  return  -1;
	 traceLogA(  "myGet98CdromUsbInfo()  enter"  );

	 //  ¹âÇý	[HKEY_LOCAL_MACHINE\Enum\SCSI\SHARK___44X_CD-ROM______0\MF&CHILD0001&PCI&VEN_1106&DEV_0571&SUBSYS_05711106&REV_10&BUS_00&DEV_07&FUNC_0110]  
	 //	 USB	[HKEY_LOCAL_MACHINE\Enum\SCSI\IC25N020ATDA04-0________D\USB&VID_04CE&PID_0002_0&HTREE&ROOT&000]
	 pEnumKey  =  CONST_qyRootKey_cdrom_usb_98;
	 //  µÚÒ»²ãÃ¶¾Ù:Enum\SCSI\ÏÂ
	 if  (  (  iRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  pEnumKey,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey  )  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	 bKeyOpen  =  TRUE;
	 for  (  i = 0; ; i ++ )  {
		  iRet  =  RegEnumKey(  hKey,  i,  tSubKey, sizeof(  tSubKey  )  );
		  if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  )  break;
		  _snprintf(  dataKey,  sizeof(  dataKey  ),  "%s\\%s",  pEnumKey,  tSubKey  );  
		  _snprintf(  dataBuf,  sizeof(  dataBuf  ),  "%s\\%s",  "SCSI",  tSubKey  );
		  traceLogA(  "  µÃµ½µÚ%d¸öÐèÑéÖ¤µÄÓ²¼þÊý¾ÝµÄÇ°Ãæ²¿·Ö:%s",  i,  dataBuf  );

		  //  µÚ¶þ²ãÃ¶¾Ù£ºEnum\SCSI\SHARK___44X_CD-ROM______0\ÏÂ
		  if  (  (  iRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  dataKey,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey2  )  )  !=  ERROR_SUCCESS  )  goto  errLabel;
		  bKey2Open	=  TRUE;
		  for  (  i2 = 0; ; i2 ++ )  {
			   iRet  =  RegEnumKey(  hKey2,  i2,  tSubKey2,  sizeof(  tSubKey2  )  );
			   if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  )  break;
			   _snprintf(  activeDataKey,  sizeof(  activeDataKey  ),  "%s\\%s",  dataKey,  tSubKey2  );
   			   _snprintf(  activeDataBuf,  sizeof(  activeDataBuf  ),  "%s\\%s",  dataBuf,  tSubKey2  );
			   traceLogA(  "  µÃµ½µÚ%d¸öÐèÑéÖ¤µÄÍêÕûµÄÓ²¼þÊý¾Ý:%s",  cnt2,  activeDataBuf  );

			   if  (  (  iRet  =  RegOpenKeyEx(  HKEY_DYN_DATA,  pEnumKey1,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey1  )  )  !=  ERROR_SUCCESS  )  goto  errLabel;
			   bKey1Open  =  TRUE;
			   for  (  i1 = 0;  ;  i1++ )  {
				    iRet  =  RegEnumKey(  hKey1,  i1,  tSubKey1,  sizeof(  tSubKey1  )  );
					if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  )  break;
					_snprintf(  tmpKey,  sizeof(  tmpKey  ),  "%s\\%s",  pEnumKey1,  tSubKey1  );
					
					memset(  (  char  *  )&reg,  0,  sizeof(  reg  )  );
					reg.hKeyRoot0  =  HKEY_DYN_DATA;
					lstrcpyn(  reg.rootKey,  tmpKey,  sizeof(  reg.rootKey  )  );
					if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_hardwareKey,  regValBuf,  sizeof(  regValBuf  )  )  )  continue;
					traceLogA(  "µÚ%d¸öhardwareKey is %s",  i1,  regValBuf  );
					
					if  (  _strnicmp(  activeDataBuf,  regValBuf,  strlen(  activeDataBuf  )  )  )  continue;
					traceLogA(  "µÚ%d¸öÆ¥Åä²ÎÊý is %s,ÎªµÚ%d¸öhardwareKey",  cnt1,  regValBuf,  i1  );
							   
					//  µÃµ½µ±Ç°»î¶¯µÄÓ²¼þ²ÎÊý

					
					if  (  qyGetRegCfg(  activeDataKey,  CONST_regValName_deviceDesc,  regValBuf1,  sizeof(  regValBuf1  )  )
						||  qyGetRegCfg(  activeDataKey,  CONST_regValName_classGUID,  classIdBuf, sizeof(  classIdBuf )  )  )  break;

					traceLogA(  "×é¼þÐÍºÅÎª£º%s",  regValBuf1 );
					if  (  !(  pComponent  =  nextComponent(  pAssetsInfo  )  )  )  goto  errLabel;
					if  (  _strnicmp(  classIdBuf,  CONST_classGUID_cdrom, sizeof(  CONST_classGUID_cdrom  )  )  )  pComponent->uiType  =  CONST_assetType_usbDisk;
					else  pComponent->uiType  =  CONST_assetType_ideCdrom;

			
					_snprintf(  pComponent->u.disk.modelNo,  sizeof(  pComponent->u.disk.modelNo  ),  "%s",  regValBuf1  );

					#ifdef	__DEBUG__	
	 						printComponentInfo(  cnt2,  pComponent  );
					#endif

					submitComponent(  pAssetsInfo,  0  );
					cnt2  ++;  break;
			   }
			   traceLogA(  "µÚ¶þ²ãÃ¶¾Ù£ºEnum\\SCSI\\SHARK___44X_CD-ROM______0ÏÂµÚ%d¸ö½áÊø",  cnt1  );
			   cnt1 ++;
			}
	 }
	 RegCloseKey(  hKey  );  bKeyOpen  =  FALSE;
	 RegCloseKey(  hKey1  );  bKey1Open  =  FALSE;
	 RegCloseKey(  hKey2  );  bKey2Open  =  FALSE;

	 iErr  =  0;

errLabel:

	 if  (  bKeyOpen  )  RegCloseKey(  hKey  );
	 if  (  bKey1Open  )  RegCloseKey(  hKey1  );
	 if  (  bKey2Open  )  RegCloseKey(  hKey2  ); 


	 return  iErr;
}
#endif
 int  myGet98CdromUsbInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  )
 {
	 return  -1;
 }

#if  0
int	 myGet98DisplayInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  ) 
{	 
	 int						iErr						=	-1;
	 int						iRet						=   0;
	 char					*	pEnumKey					=	NULL;
	 char					*   pEnumKey1					=   CONST_qyRootKey_configMgrEnum_98;
 	 HKEY						hKey						=   NULL;
	 HKEY						hKey1						=   NULL;
	 BOOL						bKeyOpen					=	FALSE;
	 BOOL						bKey1Open					=	FALSE;
	 char						tSubKey[MAX_PATH  +  1]		=   "";  
	 char						tSubKey1[MAX_PATH  +  1]	=   "";
	 int						i = 0, i1 = 0, cnt = 0;
	 char						dataKey[MAX_PATH + 1]		=   "";
	 char						activeDataKey[MAX_PATH + 1] =   "";
	 char						tmpKey[MAX_PATH  +  1]		=	"";
	 char						dataBuf[MAX_PATH + 1]		=	"";		//  ÐèÑéÖ¤Öµ
	 QY_REG						reg;
	 char						regValBuf[255]				=   "";
	 char						driverDescBuf[MAX_PATH + 1]	=	"";
	 char						driverDateBuf[MAX_PATH + 1] =	"";
	 char						versionBuf[MAX_PATH + 1]	=	"";
	 char						providerName[MAX_PATH + 1]	=	"";
	 char						matchingIdBuf[MAX_PATH + 1]	=	"";
	 QWM_COMPONENT_INFO		*	pComponent					=	NULL;


	 //CONST_regValName_matchingDeviceId
	 if  (  !pAssetsInfo  )  return  -1;
	 traceLogA(  "myGet98DisplayInfo()  enter"  );

	 //  ÏÔÊ¾¿¨	[HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\Class\Display\0000]
	 pEnumKey  =  CONST_qyRootKey_display_98;
	 //  Ã¶¾Ù:
	 if  (  (  iRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  pEnumKey,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey  )  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	 bKeyOpen  =  TRUE;
	 for  (  i = 0; ; i ++ )  {
		  iRet  =  RegEnumKey(  hKey,  i,  tSubKey, sizeof(  tSubKey  )  );
		  if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  )  break;
		  _snprintf(  dataKey,  sizeof(  dataKey  ),  "%s\\%s",  pEnumKey,  tSubKey  );  
		  //  _snprintf(  dataBuf,  sizeof(  dataBuf  ),  "%s\\%s",  "SCSI",  tSubKey  );
		  
		  if  (  qyGetRegCfg(  dataKey,  CONST_regValName_matchingDeviceId,  matchingIdBuf,  sizeof( matchingIdBuf  )  )  )   goto  errLabel;
		  traceLogA(  "  µÃµ½µÚ%d¸öÐèÑéÖ¤µÄÓ²¼þÊý¾Ý:%s",  i,  matchingIdBuf  );

		  //  ±È¶Ô
		  if  (  (  iRet  =  RegOpenKeyEx(  HKEY_DYN_DATA,  pEnumKey1,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey1  )  )  !=  ERROR_SUCCESS  )  goto  errLabel;
			   bKey1Open  =  TRUE;
			   for  (  i1 = 0;  ;  i1++ )  {
				    iRet  =  RegEnumKey(  hKey1,  i1,  tSubKey1,  sizeof(  tSubKey1  )  );
					if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  )  break;
					_snprintf(  tmpKey,  sizeof(  tmpKey  ),  "%s\\%s",  pEnumKey1,  tSubKey1  );
					
					memset(  (  char  *  )&reg,  0,  sizeof(  reg  )  );
					reg.hKeyRoot0  =  HKEY_DYN_DATA;
					lstrcpyn(  reg.rootKey,  tmpKey,  sizeof(  reg.rootKey  )  );
					if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_hardwareKey,  regValBuf,  sizeof(  regValBuf  )  )  )  continue;
					traceLogA(  "µÚ%d¸öhardwareKey is %s",  i1,  regValBuf  );
					
					if  (  _strnicmp(  matchingIdBuf,  regValBuf,  strlen(  matchingIdBuf  )  )  )  continue;
					traceLogA(  "µÚ%d¸öÆ¥Åä²ÎÊý is %s,ÎªµÚ%d¸öhardwareKey",  cnt,  regValBuf,  i1  );
							   
					//  µÃµ½µ±Ç°»î¶¯µÄÓ²¼þ²ÎÊý
					if  (  qyGetRegCfg(  dataKey,  CONST_regValName_driverDesc,  driverDescBuf,  sizeof(  driverDescBuf  )  )
						||  qyGetRegCfg(  dataKey,  CONST_regValName_driverDate,  driverDateBuf,  sizeof(  driverDateBuf  )  )  
						  ||  qyGetRegCfg(  dataKey,  CONST_regValName_driverVersion_98,  versionBuf,  sizeof(  versionBuf  )  )  )  break;
														
					if  (  !(  pComponent  =  nextComponent(  pAssetsInfo  )  )  )  goto  errLabel;
					pComponent->uiType  =  CONST_assetType_display;
			
					_snprintf(  pComponent->u.display.driverDesc,  sizeof(  pComponent->u.display.driverDesc  ),  "%s",  driverDescBuf  );
					_snprintf(  pComponent->u.display.driverDate,  sizeof(  pComponent->u.display.driverDate  ),  "%s",  driverDateBuf  );
					_snprintf(  pComponent->u.display.driverVersion,  sizeof(  pComponent->u.display.driverVersion  ),  "%s",  versionBuf  );


					#ifdef	__DEBUG__	
							printComponentInfo(  cnt,  pComponent  );
					#endif

					submitComponent(  pAssetsInfo,  0  );
					cnt  ++;  break;
			   }
	 }
	 
	 RegCloseKey(  hKey  );  bKeyOpen  =  FALSE;
	 RegCloseKey(  hKey1  );  bKey1Open  =  FALSE;

	 iErr  =  0;

errLabel:

	 if  (  bKeyOpen  )  RegCloseKey(  hKey  );
	 if  (  bKey1Open  )  RegCloseKey(  hKey1  );


	 return  iErr;
}
#endif
int	 myGet98DisplayInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  ) 
{
	return  -1;
}

#if  0
int	 myGet98NetworkCardInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  )
{	 
	 int						iErr						=	-1;
	 int						iRet						=   0;
	 char					*	pEnumKey					=	NULL;
	 char					*   pEnumKey1					=   CONST_qyRootKey_configMgrEnum_98;
 	 HKEY						hKey						=   NULL;
	 HKEY						hKey1						=   NULL;
	 BOOL						bKeyOpen					=	FALSE;
	 BOOL						bKey1Open					=	FALSE;
	 char						tSubKey[MAX_PATH  +  1]		=   "";  
	 char						tSubKey1[MAX_PATH  +  1]	=   "";
	 int						i = 0, i1 = 0, cnt = 0;
	 char						dataKey[MAX_PATH + 1]		=   "";
	 char						activeDataKey[MAX_PATH + 1] =   "";
	 char						tmpKey[MAX_PATH  +  1]		=	"";
	 char						dataBuf[MAX_PATH + 1]		=	"";		//  ÐèÑéÖ¤Öµ
	 QY_REG						reg;
	 char						regValBuf[255]				=   "";
	 char						driverDescBuf[MAX_PATH + 1]	=	"";
	 char						driverDateBuf[MAX_PATH + 1] =	"";
	 char						versionBuf[MAX_PATH + 1]	=	"";
	 char						matchingIdBuf[MAX_PATH + 1]	=	"";
	 QWM_COMPONENT_INFO		*	pComponent					=	NULL;


	 if  (  !pAssetsInfo  )  return  -1;
	 traceLogA(  "myGet98NetworkCardInfo()  enter"  );

	 //  Íø¿¨£º[HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\Class\Net\0001]
	 pEnumKey  =  CONST_qyRootKey_networkCard_98;
	 //  Ã¶¾Ù:
	 if  (  (  iRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  pEnumKey,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey  )  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	 bKeyOpen  =  TRUE;
	 for  (  i = 0; ; i ++ )  {
		  iRet  =  RegEnumKey(  hKey,  i,  tSubKey, sizeof(  tSubKey  )  );
		  if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  )  break;
		  _snprintf(  dataKey,  sizeof(  dataKey  ),  "%s\\%s",  pEnumKey,  tSubKey  );  
		  
		  if  (  qyGetRegCfg(  dataKey,  CONST_regValName_matchingDeviceId,  matchingIdBuf,  sizeof( matchingIdBuf  )  )  )   goto  errLabel;
		  traceLogA(  "  µÃµ½µÚ%d¸öÐèÑéÖ¤µÄÓ²¼þÊý¾Ý:%s",  i,  matchingIdBuf  );

		  //  ±È¶Ô
		  if  (  (  iRet  =  RegOpenKeyEx(  HKEY_DYN_DATA,  pEnumKey1,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey1  )  )  !=  ERROR_SUCCESS  )  goto  errLabel;
			   bKey1Open  =  TRUE;
			   for  (  i1 = 0;  ;  i1++ )  {
				    iRet  =  RegEnumKey(  hKey1,  i1,  tSubKey1,  sizeof(  tSubKey1  )  );
					if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  )  break;
					_snprintf(  tmpKey,  sizeof(  tmpKey  ),  "%s\\%s",  pEnumKey1,  tSubKey1  );
					
					memset(  (  char  *  )&reg,  0,  sizeof(  reg  )  );
					reg.hKeyRoot0  =  HKEY_DYN_DATA;
					lstrcpyn(  reg.rootKey,  tmpKey,  sizeof(  reg.rootKey  )  );
					if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_hardwareKey,  regValBuf,  sizeof(  regValBuf  )  )  )  continue;
					traceLogA(  "µÚ%d¸öhardwareKey is %s",  i1,  regValBuf  );
					
					if  (  _strnicmp(  matchingIdBuf,  regValBuf,  strlen(  matchingIdBuf  )  )  )  continue;
					traceLogA(  "µÚ%d¸öÆ¥Åä²ÎÊý is %s,ÎªµÚ%d¸öhardwareKey",  cnt,  regValBuf,  i1  );
							   
					//  µÃµ½µ±Ç°»î¶¯µÄÓ²¼þ²ÎÊý
					if  (  qyGetRegCfg(  dataKey,  CONST_regValName_driverDesc,  driverDescBuf,  sizeof(  driverDescBuf  )  )
						||  qyGetRegCfg(  dataKey,  CONST_regValName_driverDate,  driverDateBuf,  sizeof(  driverDateBuf  )  )  )  break;
							
					traceLogA(  "dataKey is %s, driverDescBuf is %s, driverDateBuf is %s",  dataKey,  driverDescBuf,  driverDateBuf  );

					if  (  !(  pComponent  =  nextComponent(  pAssetsInfo  )  )  )  goto  errLabel;
					pComponent->uiType  =  CONST_assetType_networkCard;
			
					safeStrnCpy(  driverDescBuf,  pComponent->u.net.driverDesc,  sizeof(  pComponent->u.net.driverDesc  )  );  
					safeStrnCpy(  driverDateBuf,  pComponent->u.net.driverDate,  sizeof(  pComponent->u.net.driverDate  )  );
	
					#ifdef	__DEBUG__	
							printComponentInfo(  cnt,  pComponent  );
					#endif

					submitComponent(  pAssetsInfo,  0  );
					cnt  ++;  break;
			   }
	 }
	 
	 RegCloseKey(  hKey  );  bKeyOpen  =  FALSE;
	 RegCloseKey(  hKey1  );  bKey1Open  =  FALSE;

	 iErr  =  0;

errLabel:

	 if  (  bKeyOpen  )  RegCloseKey(  hKey  );
	 if  (  bKey1Open  )  RegCloseKey(  hKey1  );


	 return  iErr;
}
#endif
int	 myGet98NetworkCardInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  )
{
	return  -1;
}

#if  0
int	 myGet98MonitorInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  )
{	 
	 int						iErr						=	-1;
	 int						iRet						=   0;
	 char					*	pEnumKey					=	NULL;
	 char					*   pEnumKey1					=   CONST_qyRootKey_configMgrEnum_98;
 	 HKEY						hKey						=   NULL;
	 HKEY						hKey1						=   NULL;
	 BOOL						bKeyOpen					=	FALSE;
	 BOOL						bKey1Open					=	FALSE;
	 char						tSubKey[MAX_PATH  +  1]		=   "";  
	 char						tSubKey1[MAX_PATH  +  1]	=   "";
	 int						i = 0, i1 = 0, cnt = 0;
	 char						dataKey[MAX_PATH + 1]		=   "";
	 char						activeDataKey[MAX_PATH + 1] =   "";
	 char						tmpKey[MAX_PATH  +  1]		=	"";
	 char						dataBuf[MAX_PATH + 1]		=	"";		//  ÐèÑéÖ¤Öµ
	 QY_REG						reg;
	 char						regValBuf[255]				=   "";
	 char						driverDescBuf[MAX_PATH + 1]	=	"";
	 char						driverDateBuf[MAX_PATH + 1] =	"";
	 char						versionBuf[MAX_PATH + 1]	=	"";
	 char						matchingIdBuf[MAX_PATH + 1]	=	"";
	 QWM_COMPONENT_INFO		*	pComponent					=	NULL;


	 if  (  !pAssetsInfo  )  return  -1;
	 traceLogA(  "myGet98MonitorInfo()  enter"  );

	 //  ¼àÊÓÆ÷£º[HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\Class\Monitor\0000]
	 pEnumKey  =  CONST_qyRootKey_monitor_98;
	 //  Ã¶¾Ù:
	 if  (  (  iRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  pEnumKey,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey  )  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	 bKeyOpen  =  TRUE;
	 for  (  i = 0; ; i ++ )  {
		  iRet  =  RegEnumKey(  hKey,  i,  tSubKey, sizeof(  tSubKey  )  );
		  if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  )  break;
		  _snprintf(  dataKey,  sizeof(  dataKey  ),  "%s\\%s",  pEnumKey,  tSubKey  );  
		  
		  if  (  qyGetRegCfg(  dataKey,  CONST_regValName_matchingDeviceId,  matchingIdBuf,  sizeof( matchingIdBuf  )  )  )   goto  errLabel;
		  traceLogA(  "  µÃµ½µÚ%d¸öÐèÑéÖ¤µÄÓ²¼þÊý¾Ý:%s",  i,  matchingIdBuf  );

		  //  ±È¶Ô
		  if  (  (  iRet  =  RegOpenKeyEx(  HKEY_DYN_DATA,  pEnumKey1,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey1  )  )  !=  ERROR_SUCCESS  )  goto  errLabel;
			   bKey1Open  =  TRUE;
			   for  (  i1 = 0;  ;  i1++ )  {
				    iRet  =  RegEnumKey(  hKey1,  i1,  tSubKey1,  sizeof(  tSubKey1  )  );
					if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  )  break;
					_snprintf(  tmpKey,  sizeof(  tmpKey  ),  "%s\\%s",  pEnumKey1,  tSubKey1  );
					
					memset(  (  char  *  )&reg,  0,  sizeof(  reg  )  );
					reg.hKeyRoot0  =  HKEY_DYN_DATA;
					lstrcpyn(  reg.rootKey,  tmpKey,  sizeof(  reg.rootKey  )  );
					if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_hardwareKey,  regValBuf,  sizeof(  regValBuf  )  )  )  continue;
					traceLogA(  "µÚ%d¸öhardwareKey is %s",  i1,  regValBuf  );
					
					if  (  _strnicmp(  matchingIdBuf,  regValBuf,  strlen(  matchingIdBuf  )  )  )  continue;
					traceLogA(  "µÚ%d¸öÆ¥Åä²ÎÊý is %s,ÎªµÚ%d¸öhardwareKey",  cnt,  regValBuf,  i1  );
							   
					//  µÃµ½µ±Ç°»î¶¯µÄÓ²¼þ²ÎÊý
					if  (  qyGetRegCfg(  dataKey,  CONST_regValName_driverDesc,  driverDescBuf,  sizeof(  driverDescBuf  )  )
						||  qyGetRegCfg(  dataKey,  CONST_regValName_driverDate,  driverDateBuf,  sizeof(  driverDateBuf  )  )  )  break;
														
					if  (  !(  pComponent  =  nextComponent(  pAssetsInfo  )  )  )  goto  errLabel;
					pComponent->uiType  =  CONST_assetType_monitor;
			
					_snprintf(  pComponent->u.monitor.driverDesc,  sizeof(  pComponent->u.monitor.driverDesc  ),  "%s",  driverDescBuf  );
					_snprintf(  pComponent->u.monitor.driverDate,  sizeof(  pComponent->u.monitor.driverDate  ),  "%s",  driverDateBuf  );

					#ifdef	__DEBUG__	
	 						printComponentInfo(  cnt,  pComponent  );
					#endif

					submitComponent(  pAssetsInfo,  0  );
					cnt  ++;  break;
			   }
	 }
	 
	 RegCloseKey(  hKey  );  bKeyOpen  =  FALSE;
	 RegCloseKey(  hKey1  );  bKey1Open  =  FALSE;

	 iErr  =  0;

errLabel:

	 if  (  bKeyOpen  )  RegCloseKey(  hKey  );
	 if  (  bKey1Open  )  RegCloseKey(  hKey1  );


	 return  iErr;
}
#endif
int	 myGet98MonitorInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  )
{
	return  -1;
}

int	 myGet98ModemInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  )
{
	return  0;
}

    //  test:  usb
	//  #define		CONST_test			(  "USBSTOR\\Disk&Ven_IC25N020&Prod_ATDA04-0&Rev_DA3O\\6&2c99f521&0"  )
#if  0
  int  myGetIdeDiskInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  )
{
	 int						iErr					=  -1;
	 int						iRet					=  0;
	 TCHAR					*   pDiskKey				=  NULL;
	 char					*	pIdStr					=  CONST_ideDisk_id;
	 int						iAssetType				=  CONST_assetType_ideHardDisk;
	 char						regValue[1024  +  1]	=  "";
	 char					*	p						=  NULL;
	 char					*	p1						=  NULL;
	 char					*	p2						=  NULL;
	 char					*   cP						=  NULL;
	 char					*	cP1						=  NULL;
	 char					*	cP2						=  NULL;
	 char						usbBuf[1024  +  1]		=  "";
	 char						tmpBuf[1024  +  1]		=  "";
	 char						buf[1024 + 1]			=  "";
	 TCHAR						noBuf[32]				=  _T(  ""  );
	 int						i						=  0;
	 unsigned  int				cnt						=  0;
	 unsigned  int				len;
	 QWM_COMPONENT_INFO		*	pComponent				=	NULL;
	 HKEY						hEsdiKey				=	NULL;
	 HKEY						hSubKey					=	NULL;
	 BOOL						bEsdiKeyOpen			=	FALSE;
	 BOOL						bSubKeyOpen				=	FALSE;
	 //  pSoftwareInstalledKey


	 
	 if  (  !pAssetsInfo  )  goto  errLabel;
	 switch  (  pAssetsInfo->iPlatformId  )  {
			 case  CONST_qyPlatform_win32:
			 case  CONST_qyPlatform_win95:  goto  errLabel;

			 case  CONST_qyPlatform_win98:			 
			 case  CONST_qyPlatform_winme:
				   pDiskKey  =  _T(  CONST_qyRootKey_ideDisk_98  );
				   break;
			 case  CONST_qyPlatform_nt:
			 case  CONST_qyPlatform_winxp:
			 case  CONST_qyPlatform_win2003:
			 case  CONST_qyPlatform_win2k:
				   pDiskKey  =  _T(  CONST_qyRootKey_disk_2k  );
				   break;
			 default:  
				   traceLogA(  "²»Ö§³Ö¸Ã²Ù×÷ÏµÍ³¶ÔÓ²ÅÌµÄ¼ì²â"  );  goto  errLabel;
	 }

	 
	 //  È¡Ó²ÅÌÐÅÏ¢
	 if  (  qyGetRegCfg(  pDiskKey,  _T(  CONST_regValName_count  ),  ( char  *  )&cnt,  sizeof( cnt  )  )  )  goto  errLabel;

	 for  (  i  =  0;  i  <  (  int  )cnt;  i  ++  )  {
		  _itot(  i,  noBuf,  10  );
		  if  (  qyGetRegCfg(  pDiskKey,  noBuf,  regValue,  sizeof(  regValue  )  )  )  goto  errLabel; 
		  
		  if  (  !_strnicmp(  regValue,  pIdStr,  strlen(  pIdStr  )  )  )  {
			  traceLogA(  "¼ì²â³ödiskÐÅÏ¢%s",  regValue  );

			  p  =  regValue  +  strlen(  pIdStr  );
			  if  (  !(  p1  =  strchr(  p,  '\\'  )  )  )  continue;
			  *p1  =  0;

			  if  (  strlen(  p  )  !=  48  )  continue;

			  if  (  !(  pComponent  =  nextComponent(  pAssetsInfo  )  )  )  goto  errLabel;
			  
			  pComponent->uiType  =  iAssetType;
			  
			  for  (  p2  =  p;  p2  <  p1 ;  p2  ++  )  if  (  *p2  ==  '_'  )  *p2  =  ' ';

			  len  =  min(  40,  sizeof(  pComponent->u.disk.modelNo  )  -  1  );
			  memcpy(  pComponent->u.disk.modelNo,  p,  len  );
			  pComponent->u.disk.modelNo[len]  =  0;  trim(  pComponent->u.disk.modelNo  );
			  len  =  min(  8,  sizeof(  pComponent->u.disk.firmwareRevision  )  -  1  );
			  memcpy(  pComponent->u.disk.firmwareRevision,  p  +40,  len  );
			  pComponent->u.disk.firmwareRevision[len]  =  0;  trim(  pComponent->u.disk.firmwareRevision  );
			  
			  p1  ++  ;
			  //  ÕâÀïÐèÒª½«ÐòÁÐºÅ×ª»»Ò»ÏÂ
			  _snprintf(  pComponent->u.disk.serialNo,  sizeof(  pComponent->u.disk.serialNo  ),  "%s",  p1  );

			  #ifdef	__DEBUG__	
	 				    printComponentInfo(  0,  pComponent  );
			  #endif

			  submitComponent(  pAssetsInfo,  0  );

			  continue;
			}
		  //  È¡USBÐÅÏ¢
		  else  {
			    traceLogA(  "¶Áµ½ÁËusbµÄÐÅÏ¢: %s",  regValue  );
				if  (  !(  pComponent  =  nextComponent(  pAssetsInfo  )  )  )  goto  errLabel;
				iAssetType  =  CONST_assetType_usbDisk;
				pComponent->uiType  =  iAssetType;

				if  (  !(  cP  =  strchr(  regValue,  '&'  )  )  )  continue;
				if  (  !(  cP1  =  strchr(  cP + 1,  '\\'  )  )  )  continue;
				memcpy(  usbBuf,  cP  + 1,  cP1 - cP - 1  );
				
				/*
				//  usbBuf:  Ven_IC25N020&Prod_ATDA04-0&Rev_DA3O
				if  (  !(  cP  =  strchr(  usbBuf,  '_'  )  )  )  continue;
				if  (  !(  cP1  =  strchr(  cP + 1,  '&'  )  )  )  continue;
				memcpy(  pComponent->u.usb.vendor,  cP + 1,  cP1 - cP - 1  );
				if  (  !(  cP  =  strchr(  cP1 + 1,  '_'  )  )  )  continue;
				if  (  !(  cP2  =  strchr(  cP + 1,  '&'  )  )  )  continue;
				memcpy(  pComponent->u.usb.modelNo,  cP + 1,  cP2 - cP - 1  );
				memcpy(  pComponent->u.usb.revision,  cP2 + 1, sizeof(  pComponent->u.usb.revision  )  );   
				*/

				#ifdef	__DEBUG__	
						printComponentInfo(  0,  pComponent  );
				#endif
				submitComponent(  pAssetsInfo,  0  );
				continue;
		  }
	 }
	 
	 iErr  =  0;
errLabel:

	 return  iErr;
}
#endif

#if  0
  int  myGetIdeCdromInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  )
{
  	 //  º¯Êý·µ»ØÖµ
	 int						iErr								=  -1;
	 //  ×¢²á±íÏî
 	 HKEY						hKey								=  NULL;
	 HKEY						hKey1								=  NULL;
	 HKEY						hKey2								=  NULL;
	 HKEY						hKey3								=  NULL;
	 BOOL						bKeyOpen							=  FALSE;
	 BOOL						bKey1Open							=  FALSE;
	 BOOL						bKey2Open							=  FALSE;
	 BOOL						bKey3Open							=  FALSE;
	 char						classDeviceKeyBuf[MAX_PATH  + 1]	=  "";
	 char						enumDeviceKeyBuf[MAX_PATH  + 1]		=  "";
	 char						enumDeviceKey1Buf[MAX_PATH  + 1]	=  "";
	 char						enumDeviceKey2Buf[MAX_PATH  + 1]	=  "";
	 TCHAR						serviceKeyBuf[MAX_PATH  +  1]		=  _T(  ""  );
	 //  ×é¼þÏà¹ØµÄ³õÊ¼»¯²ÎÊý
	 char					*	pClassGUID							=  CONST_classGUID_cdrom;	
	 char					*	pEnumName							=  CONST_enumName_ide;
 	 TCHAR					*	pIdStr								=  _T(  CONST_ideCdrom_id  );
	 int						iAssetType							=  CONST_assetType_ideCdrom;
	 //  Êý¾Ý
	 char					*	pVendor								=  CONST_regValName_vender;
	 char					*   pDriverDate							=  CONST_regValName_driverDate;
	 char					*   pDriverDesc							=  CONST_regValName_driverDesc;
	 char					*   pDriverVersion						=  CONST_regValName_driverVersion;
	 char						classDeviceBuf[MAX_PATH + 1]		=  "";
	 char						enumDeviceBuf[MAX_PATH  + 1]		=  "";
	 TCHAR						serviceNameEnumBuf[128  + 1]		=  _T(  ""  );
	 char						vendorBuf[MAX_PATH  + 1]			=  "";
	 char						driverDateBuf[MAX_PATH +1]			=  "";
	 char						driverDescBuf[MAX_PATH +1]			=  "";
	 char						driverVersionBuf[MAX_PATH + 1]			=  "";
	 //  ±äÁ¿
	 int						iRet								=  0;
	 TCHAR						tSubKey[MAX_PATH  +  1]				=  _T(  ""  );
	 TCHAR						regValue[1024  +  1]				=  _T(  ""  );
	 char						tmpBuf[MAX_PATH  +  1]				=  "";
	 TCHAR						noBuf[32]							=  _T(  ""  );
	 int						i = 0, i1 = 0, i2 = 0, i3 = 0;
	 int						len  = 0, count = 0;
 	 TCHAR					*	p									=  NULL;
	 TCHAR					*	p1									=  NULL;
	 TCHAR					*	p2									=  NULL;
	 QWM_COMPONENT_INFO		*	pComponent							=  NULL;

	 if  (  !pAssetsInfo  )  goto  errLabel;

	 _snprintf(  classDeviceKeyBuf,  sizeof( classDeviceKeyBuf  ),  "%s\\%s",  CONST_qyRootKey_controlClass,  pClassGUID  );
	 _snprintf(  enumDeviceKeyBuf,  sizeof(  enumDeviceKeyBuf  ),  "%s\\%s",  CONST_qyRootKey_enum,  pEnumName  );

	 /*
	 if  (  (  iRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  classDeviceKeyBuf,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey  )  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	 bKeyOpen  =  TRUE;

	 for  ( i = 0; ; i ++ )  {
		  iRet  =  RegEnumKey(  hKey,  i,  tSubKey,  sizeof(  tSubKey  )  );
		  if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  ) break;
		  // 1¡¢  classÖÐµÄÓ²¼þÐÅÏ¢
		  if  (  !_strnicmp(  tSubKey,  CONST_invalidRootKey_properties,  sizeof(  CONST_invalidRootKey_properties  )  )  )  continue;
		  _snprintf(  classDeviceBuf,  sizeof(  classDeviceBuf  ),  "%s\\%s",  classDeviceKeyBuf,  tSubKey  );
	 }
	 */

 
	 /*
	 // 2-1¡¢  enum: Ò»¼¶Ä¿Â¼
	 if  (  (  iRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  enumDeviceKeyBuf,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey1  )  )  !=  ERROR_SUCCESS  )  break;
	 bKey1Open  =  TRUE;
	 for  (  i1= 0; ; i1 ++  )  {
	      iRet  =  RegEnumKey(  hKey1,  i1,  tSubKey,  sizeof(  tSubKey  )  );
		  if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  )  break;
		  //  2-2¡¢  enum: ¶þ¼¶Ä¿Â¼
		  _snprintf(  enumDeviceKey1Buf,  sizeof(  enumDeviceKey1Buf  ),  "%s\\%s",  enumDeviceKeyBuf,  tSubKey  );
		
		  if  (  (  iRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  enumDeviceKey1Buf, 0,  KEY_ENUMERATE_SUB_KEYS,  &hKey2  )  )  !=  ERROR_SUCCESS  )  break;
		  bKey2Open  =  TRUE;
	   	  for  (  i2 = 0; ; i2 ++  )  {
			   iRet  =  RegEnumKey(  hKey2,  i2,  tSubKey,  sizeof(  tSubKey  )  );
			   if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  )  break;
			   //  2-3¡¢  enum: Èý¼¶Ä¿Â¼,°üº¬Ó²¼þÐÅÏ¢
			   _snprintf(  enumDeviceBuf,  sizeof(  enumDeviceBuf  ),  "%s\\%s",  enumDeviceKey1Buf,  tSubKey  );
			   
			   if  (  qyGetRegCfg(  enumDeviceBuf,  CONST_regValName_service,  tmpBuf,  sizeof(  tmpBuf  )  )  )  continue;
			   _snprintf(  serviceKeyBuf,  sizeof(  serviceKeyBuf  ),  "%s\\%s",  CONST_qyRootKey_service,  tmpBuf  );
		  }
	 }
	 */

	 _sntprintf(  serviceKeyBuf,  mycountof(  serviceKeyBuf  ),  _T(  "%s\\%s"  ),  _T(  CONST_qyRootKey_service  ),  _T(  CONST_validRootKey_cdrom  )  );
	 if  (  (  iRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  serviceKeyBuf,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey3  )  )  !=  ERROR_SUCCESS  )   goto  errLabel;
	 bKey3Open  =  TRUE;
	 for  (  i3 = 0; ; i3 ++  )  {
		  iRet  =  RegEnumKey(  hKey3,  i3,  tSubKey,  mycountof(  tSubKey  )  );
		  if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  )  break;
		  if  (  _tcsnicmp(  tSubKey,  _T(  CONST_validRootKey_enum  ),  strlen(  CONST_validRootKey_enum  )  )  )  continue;
		  _sntprintf(  serviceNameEnumBuf,  mycountof(  serviceNameEnumBuf  ),  _T(  "%s\\%s"  ),  serviceKeyBuf,  _T(  CONST_validRootKey_enum  )  );  
		  
		  if  (  qyGetRegCfg(  serviceNameEnumBuf,  _T(  CONST_regValName_count  ),  (  char  *  )&count,  sizeof(  count  )  )  )  continue;
		  for  (  i  =  0;  i  <  count;  i  ++  )  {						 
			   _itot(  i,  noBuf,  10  );
			   if  (  qyGetRegCfg(  serviceNameEnumBuf,  noBuf,  (  char  *  )regValue,  sizeof(  regValue  )  )  )  goto  errLabel; 
			   if  (  !_tcsnicmp(  regValue,  pIdStr,  lstrlen(  pIdStr  )  )  )  {
				   traceLogA(  "¼ì²â³öcdrom%s",  regValue  );
				   
				   p  =  regValue  +  lstrlen(  pIdStr  );
				   if  (  !(  p1  =  _tcschr(  p,  '\\'  )  )  )  continue;
				   *p1  =  0;
				   
				   if  (  lstrlen(  p  )  !=  48  )  continue;
				   
				   if  (  !(  pComponent  =  nextComponent(  pAssetsInfo  )  )  )  goto  errLabel;
				   pComponent->uiType  =  iAssetType;
				   
				   for  (  p2  =  p;  p2  <  p1 ;  p2  ++  )  if  (  *p2  ==  '_'  )  *p2  =  ' ';
				   
				   len  =  min(  40,  sizeof(  pComponent->u.disk.modelNo  )  -  1  );
				   memcpy(  pComponent->u.disk.modelNo,  p,  len  );
				   pComponent->u.disk.modelNo[len]  =  0;  trim(  pComponent->u.disk.modelNo  );
				   len  =  min(  8,  sizeof(  pComponent->u.disk.firmwareRevision  )  -  1  );
				   memcpy(  pComponent->u.disk.firmwareRevision,  p  +40,  len  );
				   pComponent->u.disk.firmwareRevision[len]  =  0;  trim(  pComponent->u.disk.firmwareRevision  );
				   
				   p1  ++  ;
				   //  ÕâÀïÐèÒª½«ÐòÁÐºÅ×ª»»Ò»ÏÂ
				   //  _snprintf(  pComponent->u.disk.serialNo,  sizeof(  pComponent->u.disk.serialNo  ),  "%s",  p1  );

				   #ifdef	__DEBUG__	
						    printComponentInfo(  0,  pComponent  );
				   #endif
				   
				   pAssetsInfo->cnt  ++  ;  continue;
			   }
			   else  traceLogA(  "¶Áµ½ÁË·ÇCDROMµÄÐÅÏ¢: %s",  regValue  );
		  }
	 }
	
	 //  RegCloseKey(  hKey  );  bKeyOpen  =  FALSE;
	 //  RegCloseKey(  hKey1  );  bKey1Open  =  FALSE;
	 //  RegCloseKey(  hKey2  );  bKey2Open  =  FALSE;
	 RegCloseKey(  hKey3  );  bKey3Open  =  FALSE;
	 
	 iErr  =  0;
errLabel:

	 //  if  (  bKeyOpen  )  RegCloseKey(  hKey  );
	 //  if  (  bKey1Open  )  RegCloseKey(  hKey1  );
	 //  if  (  bKey2Open  )  RegCloseKey(  hKey2  );
	 if  (  bKey3Open  )  RegCloseKey(  hKey3  );

	 return  iErr;
}
#endif

 //  1£©µ¥ÏÔÊ¾¿¨£»2£©¶àÏÔÊ¾¿¨;
#if  0
 int  myGetDisplayInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  )
{
	 int						iErr								=  -1;
	 BOOL						bKeyOpen							=  FALSE;
	 HKEY						hKey								=  NULL;
	 TCHAR						classDeviceKeyBuf[MAX_PATH + 1]		=  _T(  ""  );
 	 char						enumDeviceKeyBuf[MAX_PATH  + 1]		=  "";
	 TCHAR						classDeviceBuf[MAX_PATH + 1]		=  _T(  ""  );

  	 //  ×é¼þÏà¹ØµÄ³õÊ¼»¯²ÎÊý
	 TCHAR					*	pClassGUID							=  _T(  CONST_classGUID_display  );	
	 char					*	pEnumName							=  CONST_enumName_pci;
	 int						iAssetType							=  CONST_assetType_display;
	 char					*	pString								=  CONST_string_display;
	 //  Êý¾Ý
	 TCHAR					*	pVendor								=  _T(  CONST_regValName_vender  );
	 TCHAR					*   pDriverDate							=  _T(  CONST_regValName_driverDate  );
	 TCHAR					*   pDriverDesc							=  _T(  CONST_regValName_driverDesc  );
	 TCHAR					*   pDriverVersion						=  _T(  CONST_regValName_driverVersion  );
	 TCHAR						vendorBuf[64  + 1]					=  _T(  ""  );
	 TCHAR						driverDateBuf[64 +1]				=  _T(  ""  );
	 TCHAR						driverDescBuf[64 +1]				=  _T(  ""  );
	 TCHAR						driverVersionBuf[64 + 1]			=  _T(  ""  );
	 //  ±äÁ¿
	 int						iRet								=  0;
	 TCHAR						tSubKey[MAX_PATH  +  1]				=  _T(  ""  );
	 int						i	=  0,  cnt  =  0;
	 QWM_COMPONENT_INFO		*	pComponent							=  NULL;

	 traceLogA(  "myGetDisplayInfo()  ½øÈë!"  );
	 if  (  !pAssetsInfo  )  goto  errLabel;

	 _sntprintf(  classDeviceKeyBuf,  mycountof(  classDeviceKeyBuf  ),  _T(  "%s\\%s"  ),  _T(  CONST_qyRootKey_controlClass  ),  pClassGUID  );
	 _snprintf(  enumDeviceKeyBuf,  sizeof(  enumDeviceKeyBuf  ),  "%s\\%s",  CONST_qyRootKey_enum,  CONST_enumName_pci  );

	 if  (  (  iRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  classDeviceKeyBuf,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey  )  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	 bKeyOpen  =  TRUE;
	 for  (  i = 0; ; i++  )  {
		  iRet  =  RegEnumKey(  hKey,  i,  tSubKey,  sizeof(  tSubKey  )  );
		  if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  ) {
			  if  (  iRet  ==  ERROR_NO_MORE_ITEMS  &&  i == 0 )  {
				  traceLogA(  "myGetDisplayInfo():  Ã»ÓÐ°²×°ÏÔ¿¨Çý¶¯,  ¹ÊÈ±Ê¡Îª  Î´ÖªÏÔÊ¾¿¨ ! "  );
				  
				  if  (  !(  pComponent  = nextComponent(  pAssetsInfo  )  )  )  goto  errLabel;
				  pComponent->uiType  =  iAssetType;
				  _snprintf(  pComponent->u.monitor.driverDesc,  sizeof( pComponent->u.monitor.driverDesc  ),  "%s",  pString  );

				  #ifdef	__DEBUG__	
						    printComponentInfo(  cnt,  pComponent  );
				  #endif
				  submitComponent(  pAssetsInfo,  0  );   
			  }
			  break;
		  }

		  if  (  !_tcsnicmp(  tSubKey,  _T(  CONST_invalidRootKey_properties  ),  sizeof(  CONST_invalidRootKey_properties  )  )  )  continue;
		  _sntprintf(  classDeviceBuf,  mycountof(  classDeviceBuf  ),  _T(  "%s\\%s"  ),  classDeviceKeyBuf,  tSubKey  );

		  



		  if  (  qyGetRegCfg(  classDeviceBuf,  pDriverDesc,	(  char  *  )driverDescBuf,  sizeof(  driverDescBuf  )  )  )  {  memset(  driverDescBuf,  0,  mycountof(  driverDescBuf  )  );  }
		  if  (  qyGetRegCfg(  classDeviceBuf,  pDriverDate,	(  char  *  )driverDateBuf,  sizeof(  driverDateBuf  )  )  )  {  memset(  driverDateBuf,  0,  mycountof(  driverDateBuf  )  );  }
		  if  (  qyGetRegCfg(  classDeviceBuf,  pVendor,	(  char  *  )vendorBuf,  sizeof(  vendorBuf  )  )  )  {  memset(  vendorBuf,  0,  sizeof(  vendorBuf  )  );  }
		  if  (  qyGetRegCfg(  classDeviceBuf,  pDriverVersion,  (  char  *  )driverVersionBuf,  sizeof(  driverVersionBuf  )  )  )  {  memset(  driverVersionBuf,  0,  sizeof(  driverVersionBuf  )  );  }
		  
		  if  (  !(  pComponent  = nextComponent(  pAssetsInfo  )  )  )  goto  errLabel;
		  pComponent->uiType  =  iAssetType;

		  _snprintf(  pComponent->u.display.driverDesc,  sizeof( pComponent->u.display.driverDesc  ),  "%s",  driverDescBuf  );
		  _snprintf(  pComponent->u.display.driverDate,  sizeof(  pComponent->u.display.driverDate  ),  "%s",  driverDateBuf  );
		  _snprintf(  pComponent->u.display.driverVersion,  sizeof( pComponent->u.display.driverVersion  ),  "%s",  driverVersionBuf  );
		  _snprintf(  pComponent->u.display.vendor,  sizeof(  pComponent->u.display.vendor  ),  "%s",  vendorBuf  );

		  #ifdef	__DEBUG__	
				    printComponentInfo(  cnt,  pComponent  );
		  #endif
		  submitComponent(  pAssetsInfo,  0  );	 cnt ++;
	 }

	 RegCloseKey(  hKey  );  bKeyOpen  =  FALSE;
	 
	 iErr  =  0;
errLabel:

	 if  (  bKeyOpen  )  RegCloseKey(  hKey  );
	 return  iErr;
}
#endif

#define			CONST_qyRootKey_enum_pci_2k				(  "SYSTEM\\CurrentControlSet\\Enum\\PCI"  )
#define			CONST_qyRootKey_enum_root_2k			(  "SYSTEM\\CurrentControlSet\\Enum\\Root"  )
#define			CONST_qyRootKey_service					(  "SYSTEM\\CurrentControlSet\\Services"  )
#define			CONST_regValName_net_driverDate			(  "DriverDate"  )
#define			CONST_regValName_net_driverDesc			(  "DriverDesc"  )
#define			CONST_qyRootKey_service_2k				(
//  #define			CONST_regValName_net_driverVersion_2k	(  "DriverVersion"  )
#define			CONST_invalidRootKey_descriptions		(  "Descriptions"  )
#define			CONST_regValName_busType				(  "BusType"  )
#define			CONST_regValName_service				(  "Service"  )
#define			CONST_enum								(  "ENUM"  )


 //  1) Control\Network\{4D36E972-E325-11CE-BFC1-08002BE10318}:	 PnpInstanceID
 //  2)	Enum\PCI\VEN_10EC&DEV_8139&SUBSYS_813910EC&REV_10\2&ebb567f&0&80:  matchingDeviceId
 //  3) Control\Class\{4D36E972-E325-11CE-BFC1-08002BE10318}:  driverDesc
#if  0
 int  myGetNetworkCardInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  )
{
	 int						iErr								=  -1;
	 BOOL						bKeyOpen							=  FALSE;
	 HKEY						hKey								=  NULL;
	 TCHAR						keyBuf[MAX_PATH  + 1]				=  _T(  ""  );
	 TCHAR						enumDeviceBuf[MAX_PATH  + 1]		=  _T(  ""  );
 	 TCHAR						networkCfgBuf[MAX_PATH  + 1]		=  _T(  ""  );
	 TCHAR						classDeviceBuf[MAX_PATH + 1]		=  _T(  ""  );
 	 //  ×é¼þÏà¹ØµÄ³õÊ¼»¯²ÎÊý
	 TCHAR					*	pClassGUID							=  _T(  CONST_classGUID_networkCard  );	
	 TCHAR					*   pString								=  _T(  CONST_string_connection  );
	 int						iAssetType							=  CONST_assetType_networkCard;
	 char					*   pKeyName							=  CONST_qyRootKey_controlNetwork;
	 //  Æ¥Åä²ÎÊý
	 //  char						matchingDeviceBuf[MAX_PATH  +  1]	=  "";
	 //  Êý¾Ý
	 TCHAR					*	pVendor								=  _T(  CONST_regValName_vender  );
	 TCHAR					*   pDriverDate							=  _T(  CONST_regValName_driverDate  );
	 TCHAR					*   pDriverDesc							=  _T(  CONST_regValName_driverDesc  );
	 TCHAR					*   pDriverVersion						=  _T(  CONST_regValName_driverVersion  );
	 TCHAR					*   pNetworkaddress						=  _T(  CONST_regValName_networkaddress  );
	 TCHAR					*   pName								=  _T(  CONST_regValName_name  );		//  ±¾µØÁ¬½Ó
	 TCHAR						vendorBuf[64  + 1]					=  _T(  ""  );
	 TCHAR						driverDateBuf[64 +1]				=  _T(  ""  );
	 TCHAR						driverDescBuf[64 +1]				=  _T(  ""  );
	 TCHAR						driverVersionBuf[64 + 1]			=  _T(  ""  );
	 TCHAR						networkaddressBuf[12 + 1]			=  _T(  ""  );
	 TCHAR						nameBuf[16 + 1]						=  _T(  ""  );
	 //  ±äÁ¿
	 int						iRet								=  0;
	 TCHAR						tSubKey[MAX_PATH  +  1]				=  _T(  ""  );
	 TCHAR						tmpBuf[MAX_PATH  +  1]				=  _T(  ""  );
	 int						i,  cnt								=  0;
	 QWM_COMPONENT_INFO		*	pComponent							=  NULL;

	 
	 traceLogA(  "myGetNetworkCardInfo():  ½øÈë!"  );
	 if  (  !pAssetsInfo  )  goto  errLabel;

 	 _sntprintf(  keyBuf,  mycountof(  keyBuf  ),  _T(  "%s\\%s"  ),  _T(  CONST_qyRootKey_controlNetwork  ),  pClassGUID  );
	 if  (  (  iRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  keyBuf,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey  )  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	 bKeyOpen	=  TRUE;
	 for  (  i = 0; ; i ++  )  {
		  iRet  =  RegEnumKey(  hKey,  i,  tSubKey,  sizeof(  tSubKey  )  );
		  if  (  !_tcsnicmp(  tSubKey,  _T(  "CONST_invalidRootKey_descriptions"  ),  strlen(  CONST_invalidRootKey_descriptions  )  )  )  continue;
		  if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  )  break;

		  _sntprintf(  networkCfgBuf,  mycountof(  networkCfgBuf  ),  _T(  "%s\\%s\\%s"  ),  keyBuf,  tSubKey,  pString  );

		  if  (  qyGetRegCfg(  networkCfgBuf,  _T(  CONST_regValName_pnpInstanceId  ),  (  char  *  )tmpBuf,  sizeof(  tmpBuf  )  )  )  continue;
		  _sntprintf(  enumDeviceBuf,  mycountof(  enumDeviceBuf  ),  _T(  "%s\\%s"  ),  _T(  CONST_qyRootKey_enum  ),  tmpBuf  );

		  if  (  qyGetRegCfg(  enumDeviceBuf,  _T(  CONST_regValName_driver  ),  (  char  *  )tmpBuf,  sizeof(  tmpBuf  )  )  )  continue;
		  _sntprintf(  classDeviceBuf,  mycountof(  classDeviceBuf  ),  _T(  "%s\\%s"  ),  _T(  CONST_qyRootKey_controlClass  ),  tmpBuf  );


		  if  (  qyGetRegCfg(  networkCfgBuf,  pName,  (  char  *  )nameBuf,  sizeof(  nameBuf  )  )  )  {  memset(  nameBuf,  0,  mycountof(  nameBuf  )  );  }
		  if  (  qyGetRegCfg(  classDeviceBuf,  pDriverDesc,	(  char  *  )driverDescBuf,  sizeof(  driverDescBuf  )  )  )  {  memset(  driverDescBuf,  0,  mycountof(  driverDescBuf  )  );  }
		  if  (  qyGetRegCfg(  classDeviceBuf,  pDriverDate,	(  char  *  )driverDateBuf,  sizeof(  driverDateBuf  )  )  )  {  memset(  driverDateBuf,  0,  mycountof(  driverDateBuf  )  );  }
		  if  (  qyGetRegCfg(  classDeviceBuf,  pVendor,	(  char  *  )vendorBuf,  sizeof(  vendorBuf  )  )  )  {  memset(  vendorBuf,  0,  mycountof(  vendorBuf  )  );  }
		  if  (  qyGetRegCfg(  classDeviceBuf,  pDriverVersion,  (  char  *  )driverVersionBuf,  sizeof(  driverVersionBuf  )  )  )  {  memset(  driverVersionBuf,  0,  mycountof(  driverVersionBuf  )  );  }
		  if  (  qyGetRegCfg(  classDeviceBuf,  pNetworkaddress,  (  char  *  )networkaddressBuf,  sizeof(  networkaddressBuf  )  )  )  {  memset(  networkaddressBuf,  0,  mycountof(  networkaddressBuf  )  );  }
	  
		  if  (  !(  pComponent  = nextComponent(  pAssetsInfo  )  )  )  goto  errLabel;

		  pComponent->uiType  =  iAssetType;
		  _snprintf(  pComponent->u.net.name,  sizeof(  pComponent->u.net.name  ),  "%s",  nameBuf  );
		  _snprintf(  pComponent->u.net.driverDesc,  sizeof( pComponent->u.net.driverDesc  ),  "%s",  driverDescBuf  );
		  _snprintf(  pComponent->u.net.driverDate,  sizeof(  pComponent->u.net.driverDate  ),  "%s",  driverDateBuf  );
		  _snprintf(  pComponent->u.net.driverVersion,  sizeof( pComponent->u.net.driverVersion  ),  "%s",  driverVersionBuf  );
		  _snprintf(  pComponent->u.net.vendor,  sizeof(  pComponent->u.net.vendor  ),  "%s",  vendorBuf  );
		  _snprintf(  pComponent->u.net.networkaddress,  sizeof(  pComponent->u.net.networkaddress  ),  "%s",  networkaddressBuf  );

		  #ifdef	__DEBUG__	
				    printComponentInfo(  cnt,  pComponent  );
		  #endif
						
		  submitComponent(  pAssetsInfo,  0  );
	 }
	 
	 RegCloseKey(  hKey  );  bKeyOpen  =  FALSE;
	 
	 iErr  =  0;
errLabel:

	 if  (  bKeyOpen  )  RegCloseKey(  hKey  );

	 return  iErr;
}
#endif


 //  ´ÓCONST_classGUID_monitorÖÐ»ñÈ¡¼àÊÓÆ÷ÐÅÏ¢;ÔÙÔÚenumÖÐ½øÐÐÑéÖ¤
 //  1£©ÎÞÏÔ¿¨£»2£©µ¥ÏÔ¿¨µ¥¼àÊÓÆ÷£»  3£©µ¥ÏÔ¿¨¶à¼àÊÓÆ÷; 4£©¶àÏÔ¿¨¶à¼àÊÓÆ÷  
 //  ¶à¼àÊÓÆ÷¹¦ÄÜµÄÉè±¸ÐèÒªÁ½¸öÆ¥Åä²ÎÊý£ºmatchingDeviceId,  driver;
#if  0
 int  myGetMonitorInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  )
{
	 //  º¯Êý·µ»ØÖµ
	 int						iErr								=  -1;
	 //  ×¢²á±íÏî
 	 HKEY						hKey								=  NULL;
	 HKEY						hKey1								=  NULL;
	 HKEY						hKey2								=  NULL;
	 HKEY						hKey3								=  NULL;
	 BOOL						bKeyOpen							=  FALSE;
	 BOOL						bKey1Open							=  FALSE;
	 BOOL						bKey2Open							=  FALSE;
	 BOOL						bKey3Open							=  FALSE;
	 TCHAR						classDeviceKeyBuf[MAX_PATH  + 1]	=  _T(  ""  );
	 TCHAR						enumDeviceKeyBuf[MAX_PATH  + 1]		=  _T(  ""  );
	 TCHAR						enumDeviceKey1Buf[MAX_PATH  + 1]	=  _T(  ""  );
	 TCHAR						enumDeviceKey2Buf[MAX_PATH  + 1]	=  _T(  ""  );
	 //  ×é¼þÏà¹ØµÄ³õÊ¼»¯²ÎÊý
	 char					*	pClassGUID							=  CONST_classGUID_monitor;	
	 char					*	pEnumName							=  CONST_enumName_monitor;
	 int						iAssetType							=  CONST_assetType_monitor;
	 char					*   pString								=  CONST_string_monitor;
	 //  Æ¥Åä²ÎÊý
	 TCHAR						matchingDeviceBuf[MAX_PATH  +  1]	=  _T(  ""  );
	 TCHAR						matchingDriverBuf[128 + 1]			=  _T(  ""  );
	 //  Êý¾Ý
	 TCHAR					*	pVendor								=  _T(  CONST_regValName_vender  );
	 TCHAR					*   pDriverDate							=  _T(  CONST_regValName_driverDate  );
	 TCHAR					*   pDriverDesc							=  _T(  CONST_regValName_driverDesc  );
	 TCHAR					*   pDriverVersion						=  _T(  CONST_regValName_driverVersion  );
	 TCHAR						classDeviceBuf[MAX_PATH + 1]		=  _T(  ""  );
	 TCHAR						enumDeviceBuf[MAX_PATH  + 1]		=  _T(  ""  );
	 TCHAR						vendorBuf[64  + 1]					=  _T(  ""  );
	 TCHAR						driverDateBuf[64 +1]				=  _T(  ""  );
	 TCHAR						driverDescBuf[64 +1]				=  _T(  ""  );
	 TCHAR						driverVersionBuf[64 + 1]			=  _T(  ""  );
	 //  ±äÁ¿
	 int						iRet								=  0;
	 TCHAR						tSubKey[MAX_PATH  +  1]				=  _T(  ""  );
	 TCHAR						tmpBuf[MAX_PATH  +  1]				=  _T(  ""  );
	 int						i	=  0,  i1  =  0,  i2 = 0, cnt  =  0;
	 QWM_COMPONENT_INFO		*	pComponent							=  NULL;

	 traceLogA(  "myGetMonitorInfo():  ½øÈë!"  );
 	 if  (  !pAssetsInfo  )  goto  errLabel;

	 _sntprintf(  classDeviceKeyBuf,  mycountof( classDeviceKeyBuf  ),  _T(  "%s\\%s"  ),  _T(  CONST_qyRootKey_controlClass  ),  pClassGUID  );
	 _sntprintf(  enumDeviceKeyBuf,  mycountof(  enumDeviceKeyBuf  ),  _T(  "%s\\%s"  ),  _T(  CONST_qyRootKey_enum  ),  pEnumName  );

	 if  (  (  iRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  classDeviceKeyBuf,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey  )  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	 bKeyOpen  =  TRUE;
	 for  (  i = 0; ; i++  )  {
		  iRet  =  RegEnumKey(  hKey,  i,  tSubKey,  sizeof(  tSubKey  )  );
		  if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  ) {
			  //  1£©Ã»ÓÐ°²×°ÏÔ¿¨£º¼àÊÓÆ÷classÏÂ¶Á²»³ö×ÓÄ¿Â¼, Í¬Ê±²»´æÔÚenmu\Display.
			  if  (  iRet  ==  ERROR_NO_MORE_ITEMS  &&  i == 0 )  {
				  traceLogA(  "myGetMonitorInfo():  Ã»ÓÐ°²×°ÏÔ¿¨Çý¶¯£¬¼àÊÓÆ÷classÏÂ¶Á²»³ö×ÓÄ¿Â¼,  ¹ÊÈ±Ê¡Îª  Î´Öª¼àÊÓÆ÷ ! "  );
				  
				  if  (  !(  pComponent  = nextComponent(  pAssetsInfo  )  )  )  goto  errLabel;
				  pComponent->uiType  =  iAssetType;
				  _snprintf(  pComponent->u.monitor.driverDesc,  sizeof( pComponent->u.monitor.driverDesc  ),  "%s",  pString  );

				  #ifdef	__DEBUG__	
							printComponentInfo(  cnt,  pComponent  );
				  #endif
				  submitComponent(  pAssetsInfo,  0  );   
			  }
			  break;
		  }
		  if  (  !_tcsnicmp(  tSubKey,  _T(  CONST_invalidRootKey_properties  ),  mycountof(  CONST_invalidRootKey_properties  )  )  )  continue;
		  //  classÖÐµÄÓ²¼þÐÅÏ¢(  pMonitorKey µÄÏÂÒ»¼¶Ä¿Â¼  )
		  _sntprintf(  classDeviceBuf,  mycountof(  classDeviceBuf  ),  _T(  "%s\\%s"  ),  classDeviceKeyBuf,  tSubKey  );
		  //  ÊµÊ±ÐÔ(active):ÕÒenumÖÐµÄÆ¥Åä²ÎÊýdriverºÍmatchingDeviceId
		  _sntprintf(  matchingDriverBuf,  mycountof(  matchingDriverBuf  ),  _T(  "%s\\%s"  ),  CONST_classGUID_monitor,  tSubKey  );
		  if  (  qyGetRegCfg(  classDeviceBuf,  _T(  CONST_regValName_matchingDeviceId  ),  (  char  *  )matchingDeviceBuf,  sizeof(  matchingDeviceBuf  )  )  )  continue;
		  
		  if  (  (  iRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  enumDeviceKeyBuf,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey1  )  )  !=  ERROR_SUCCESS  )  break;
		  bKey1Open  =  TRUE;
		  for  (  i1= 0; ; i1 ++  )  {
			   iRet  =  RegEnumKey(  hKey1,  i1,  tSubKey,  sizeof(  tSubKey  )  );
			   if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  )  break;
			   //  2¡¢  enumÖÐµÄÓ²¼þÐÅÏ¢,  Ò»¼¶Ä¿Â¼
			   _sntprintf(  enumDeviceKey1Buf,  mycountof(  enumDeviceKey1Buf  ),  _T(  "%s\\%s"  ),  enumDeviceKeyBuf,  tSubKey  );

			   if  (  (  iRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  enumDeviceKey1Buf, 0,  KEY_ENUMERATE_SUB_KEYS,  &hKey2  )  )  !=  ERROR_SUCCESS  )  break;
			   bKey2Open  =  TRUE;
			   for  (  i2 = 0; ; i2 ++  )  {
				    iRet  =  RegEnumKey(  hKey2,  i2,  tSubKey,  sizeof(  tSubKey  )  );
					if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  )  break;
					//   ¶þ¼¶Ä¿Â¼
					_sntprintf(  enumDeviceBuf,  mycountof(  enumDeviceBuf  ),  _T(  "%s\\%s"  ),  enumDeviceKey1Buf,  tSubKey  );
					//  Í¨¹ýÖØÒª²ÎÊýÑéÖ¤ÊÇ·ñÎªµ±Ç°¼àÊÓÆ÷
					if  (  qyGetRegCfg(  enumDeviceBuf,  _T(  CONST_regValName_hardwareId  ),  (  char  *  )tmpBuf,  sizeof(  tmpBuf  )  )  )  {  traceLogA(  "¶Á²»³öhardwareId,¹Ê²»ÊÇµ±Ç°µÄ¼àÊÓÆ÷£¬ myGetMonitorInfo() ÍË³ö!"  );  continue;  }
					if  (  _tcsnicmp(  tmpBuf,  matchingDeviceBuf,  lstrlen(  matchingDeviceBuf  )  )  )  {  traceLogA(  "hardwareIdÎª%s,matchingDeviceIdÎª%s,²»Æ¥Åä£¬ myGetMonitorInfo() ÍË³ö!",  tmpBuf,  matchingDeviceBuf  );  continue;  }
					if  (  qyGetRegCfg(  enumDeviceBuf,  _T(  CONST_regValName_driver  ),  (  char  *  )tmpBuf,  sizeof(  tmpBuf  )  )  )  {  traceLogA(  "¶Á²»³ödriver,¹Ê²»ÊÇµ±Ç°µÄ¼àÊÓÆ÷£¬ myGetMonitorInfo() ÍË³ö!"  );  continue;  }
					if  (  _tcsnicmp(  tmpBuf,  matchingDriverBuf,  lstrlen(  matchingDriverBuf  )  )  )  {  traceLogA(  "driverÎª%s,  matchingDriverBufÎª%s,  ²»Æ¥Åä£¬ myGetMonitorInfo() ÍË³ö!",  tmpBuf,  matchingDriverBuf  );  continue;  }
					
					
					_sntprintf(  enumDeviceKey2Buf,  mycountof( enumDeviceKey2Buf  ),  _T(  "%s\\%s"  ),  enumDeviceBuf,  _T(  CONST_validRootKey_control  )  );
					//   ÊÇ·ñÎª»î¶¯×´Ì¬
					if  (  (  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  enumDeviceKey2Buf,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey3  )  )  !=  ERROR_SUCCESS  )  {  traceLogA(  "enumDeviceKey2BufÎª%s£¬ myGetMonitorInfo() ÎÞ·¨´ò¿ª!",  enumDeviceKey2Buf  );  continue;  }
					bKey3Open  =  TRUE;
					
					if  (  qyGetRegCfg(  classDeviceBuf,  pDriverDesc,	(  char  *  )driverDescBuf,  sizeof(  driverDescBuf  )  )  )  {  memset(  driverDescBuf,  0,  sizeof(  driverDescBuf  )  );  }
			   		if  (  qyGetRegCfg(  classDeviceBuf,  pDriverDate,	(  char  *  )driverDateBuf,  sizeof(  driverDateBuf  )  )  )  {  memset(  driverDateBuf,  0,  sizeof(  driverDateBuf  )  );  }
			   		if  (  qyGetRegCfg(  classDeviceBuf,  pVendor,	(  char  *  )vendorBuf,  sizeof(  vendorBuf  )  )  )  {  memset(  vendorBuf,  0,  sizeof(  vendorBuf  )  );  }
			   		if  (  qyGetRegCfg(  classDeviceBuf,  pDriverVersion,  (  char  *  )driverVersionBuf,  sizeof(  driverVersionBuf  )  )  )  {  memset(  driverVersionBuf,  0,  sizeof(  driverVersionBuf  )  );  }
			   
			   		if  (  !(  pComponent  = nextComponent(  pAssetsInfo  )  )  )  goto  errLabel;

			   		pComponent->uiType  =  iAssetType;
			   		_snprintf(  pComponent->u.monitor.driverDesc,  sizeof( pComponent->u.monitor.driverDesc  ),  "%s",  driverDescBuf  );
					_snprintf(  pComponent->u.monitor.driverDate,  sizeof(  pComponent->u.monitor.driverDate  ),  "%s",  driverDateBuf  );
					_snprintf(  pComponent->u.monitor.driverVersion,  sizeof( pComponent->u.monitor.driverVersion  ),  "%s",  driverVersionBuf  );
					_snprintf(  pComponent->u.monitor.vendor,  sizeof(  pComponent->u.monitor.vendor  ),  "%s",  vendorBuf  );

					#ifdef	__DEBUG__	
							printComponentInfo(  cnt,  pComponent  );
					#endif
						
					submitComponent(  pAssetsInfo,  0  );   cnt ++;
			   }
		  }
	 }
	 if  (  bKeyOpen  )  RegCloseKey(  hKey  );  bKeyOpen  =  FALSE;
	 if  (  bKey1Open  )  RegCloseKey(  hKey1  );  bKey1Open  =  FALSE;
	 if  (  bKey2Open  )  RegCloseKey(  hKey2  );  bKey2Open  =  FALSE;
	 if  (  bKey3Open  )  RegCloseKey(  hKey3  );  bKey3Open  =  FALSE;
	 
	 iErr  =  0;
errLabel:

	 if  (  bKeyOpen  )  RegCloseKey(  hKey  );
	 if  (  bKey1Open  )  RegCloseKey(  hKey1  );
	 if  (  bKey2Open  )  RegCloseKey(  hKey2  );
	 if  (  bKey3Open  )  RegCloseKey(  hKey3  );

	 return  iErr;
}
#endif

 int	 myGetSoftwareInfo98(  QWM_ASSETS_INFO  *  pAssetsInfo  );
 int	 myGetSoftwareInfoNt(  QY_ENV  *  pEnv,  LPCTSTR  pSoftwareInstalledKey,  QWM_ASSETS_INFO  *  pAssetsInfo  );


 int	 myGetSoftwareInfo(  QY_ENV  *  pEnv,  QWM_ASSETS_INFO  *  pAssetsInfo  )
{
	 if  (  !g_bIsWinNT  )  return  myGetSoftwareInfo98(  pAssetsInfo  );
	 else  {
		   myGetSoftwareInfoNt(  pEnv,  _T(  CONST_qyRootKey_softwareInstalled  ),  pAssetsInfo  );
		   #ifdef  __X64__
				   myGetSoftwareInfoNt(  pEnv,  _T(  CONST_qyRootKey_softwareInstalled_wow64  ),  pAssetsInfo  );		   
		   #endif
		   return  0;
	 }
}


//////////////////

 int	 myGetSoftwareInfo98(  QWM_ASSETS_INFO  *  pAssetsInfo  )
{
	 int						iErr						=	-1;
	 int						iRet						=  0;
	 TCHAR						softwareRegKey[255 + 1]		=  _T(  ""  );
 	 TCHAR						tSubKey[MAX_PATH  +  1]		=  _T(  ""  );
	 TCHAR					*   pSoftwareInstalledKey		=  NULL;
	 HKEY						hKey						=  NULL;
	 char						displayNameValue[255]		=  "";
	 DWORD						dwSystemComponentValue		=  0;
	 char						uninstallStringValue[255]	=  "";
	 int						i  =  0, cnt  =  0;
	 BOOL						bKeyOpen					=	FALSE;
	 QWM_COMPONENT_INFO		*	pComponent	=	NULL;
	 
	 
	 if  (  !pAssetsInfo  )  return  -1;

	 switch  (  pAssetsInfo->iPlatformId  )  {
			  
			 case  CONST_qyPlatform_win98:
			 case  CONST_qyPlatform_nt:
			 case  CONST_qyPlatform_win2k:
			 case  CONST_qyPlatform_winxp:
			 case  CONST_qyPlatform_win2003:
			 default:  
					pSoftwareInstalledKey  =  _T(  CONST_qyRootKey_softwareInstalled  );
					break;
	 }
 
	 if  (  (  iRet  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  pSoftwareInstalledKey,  0,  KEY_ENUMERATE_SUB_KEYS,  &hKey  )  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	 bKeyOpen  =  TRUE;
	 for  (  i = 0;  ;  i++ )  {
		  iRet  =  RegEnumKey(  hKey,  i,  tSubKey,  sizeof(  tSubKey  )  );
		  if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  )  break;
		  _sntprintf(  softwareRegKey,  mycountof(  softwareRegKey  ),  _T(  "%s\\%s"  ),  pSoftwareInstalledKey,  tSubKey  );
		  
		  if  (  qyGetRegCfg(  softwareRegKey,  _T(  CONST_regValName_displayName  ),  displayNameValue,  sizeof(  displayNameValue  )  )  
			  ||  qyGetRegCfg(  softwareRegKey,  _T(  CONST_regValName_uninstallString  ),  uninstallStringValue,  sizeof(  uninstallStringValue  )  )  )  {
			  traceLogA(  "µÚ%d¸öÈí¼þÎÞ·¨Ìí¼Ó/É¾³ý£¬ ²»ÏÔÊ¾",  i  );	  continue;
		  }
		  if  (  !qyGetRegCfg(  softwareRegKey, _T(  CONST_regValName_systemComponent  ),  (  char  *  )&dwSystemComponentValue,  sizeof(  dwSystemComponentValue  )  )  &&  dwSystemComponentValue  ==  1  )  {
			  traceLogA(  "%sµÄÈí¼þÎªÏµÍ³×é¼þ£¬²»ÏÔÊ¾",  displayNameValue  );  continue;
		  }
		  trim(  displayNameValue  );
		  if  (  !*displayNameValue  )  continue;
		  
		  if  (  !(  pComponent  =  nextComponent(  pAssetsInfo  )  )  )  goto  errLabel;
	 	  pComponent->uiType  =  CONST_assetType_software;
		  _snprintf(  pComponent->u.software.displayName,  sizeof(  pAssetsInfo->components[pAssetsInfo->cnt].u.software.displayName  ),  "%s",  displayNameValue  );
		  traceLogA(  "ÒÑ°²×°µÄÈí¼þÎª£º%s",  pComponent->u.software.displayName  );
		  cnt  ++  ;
		  submitComponent(  pAssetsInfo,  0  );
	 }

	 RegCloseKey(  hKey  );  bKeyOpen  =  FALSE;
	 
	 traceLogA(  "¹²°²×°ÁË%d¸öÈí¼þ",  cnt  );

	 iErr  =  0;

errLabel:

	 if  (  bKeyOpen  )  RegCloseKey(  hKey  );

	 return  iErr;
}



