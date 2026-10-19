

//  这个文件由wqh所写, 2005/01/05


#include	<windows.h>            // required for all Windows applications
#include	<windowsx.h>

#include	<stdlib.h>
#include	<ras.h>
#include	<raserror.h>
#include	<lm.h>
#include	<tchar.h>
#include	<iphlpapi.h>
#include	"asrWMon.h"
//  #include	"osversion.h"
#include	"config.h"
#include	"main.h"
#include	"qyRegToolProc.h"

#define		CONST_subKeyName_explorer						"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\Explorer"
#define		CONST_subKeyName_fdc							"SYSTEM\\CurrentControlSet\\Services\\Fdc"
#define		CONST_subKeyName_cdrom							"SYSTEM\\CurrentControlSet\\Services\\Cdrom"
#define		CONST_subKeyName_usbStor						"SYSTEM\\CurrentControlSet\\Services\\USBSTOR"	//  2007/02/11
#define		CONST_subKeyName_scsi							"Enum\\SCSI"
#define		CONST_subKeyName_rootHub						"Enum\\USB\\ROOT_HUB"

#define		CONST_regValName_noDrives						"NoDrives"
#define		CONST_regValName_start							"Start"
#define		CONST_regValName_currentDriveLetterAssignment	"CurrentDriveLetterAssignment"
#define		CONST_regValName_classGUID						"ClassGUID"
#define		CONST_regValName_csConfigFlags					"CSConfigFlags"


#define		CONST_classGUID_cdrom							"{4D36E965-E325-11CE-BFC1-08002BE10318}"
#define		CONST_classGUID_disk							"{4D36E967-E325-11CE-BFC1-08002BE10318}"

 BOOL  haveDisk(  TCHAR  drvLetter  )
{
	  BOOL		bRet						=  FALSE;
	  TCHAR		rootPathName[MAX_PATH  +  1];

	  _sntprintf(  rootPathName,  mycountof(  rootPathName  ),  _T(  "%c:\\"  ),  drvLetter  );

      if  (  !GetVolumeInformation(  rootPathName,  0,  0,  NULL,  NULL,  NULL,  NULL,  0  )  )
	  {
		  goto  errLabel;
	  }


	  bRet  =  TRUE;

errLabel:

      return  bRet;

}


 BOOL  myStateChange(  QWM_DYN_LIB  *  pDynLib,  DWORD NewStatus,  DWORD SelectedItem,  HDEVINFO  hDevInfo  )
{
	 BOOL					bRet				=	FALSE;
	 SP_PROPCHANGE_PARAMS	PropChangeParams	=	{  sizeof(  SP_CLASSINSTALL_HEADER  )  };
	 SP_DEVINFO_DATA		DeviceInfoData		=	{  sizeof(  SP_DEVINFO_DATA  )  }; 

	 traceLogA(  "将改变%d的软驱",  SelectedItem  );

	 // Get a handle to the Selected Item.
	 if  (  !pDynLib->pSetupDiEnumDeviceInfo(  hDevInfo,  SelectedItem,  &DeviceInfoData  )  )  {
		 qyDisplayLastError(  ""  );  goto  errLabel;
	 }

	 // Set the PropChangeParams structure.
	 PropChangeParams.ClassInstallHeader.InstallFunction  =  DIF_PROPERTYCHANGE;
	 PropChangeParams.Scope  =  DICS_FLAG_GLOBAL;
	 PropChangeParams.StateChange  =  NewStatus;

	 if  (  !pDynLib->pSetupDiSetClassInstallParams(  hDevInfo,  &DeviceInfoData,  (  SP_CLASSINSTALL_HEADER  *  )&PropChangeParams,  sizeof(  PropChangeParams  )  )  )  {
		 qyDisplayLastError(  ""  );  goto  errLabel;
	 }

	 //  Call the ClassInstaller and perform the change.
	 if  (  !pDynLib->pSetupDiCallClassInstaller(  DIF_PROPERTYCHANGE,  hDevInfo,  &DeviceInfoData  )  )  {
		 qyDisplayLastError(  ""  );  goto  errLabel;
	 }

	 bRet  =  TRUE;
errLabel:
	
	 return  bRet;
}


// 这些设备的启用和禁用主要有此函数实现
// 参数说明,nStatus 可取3个值，-1 ：啥也不做
//								0   禁用设备，
//								1   启用设备。
// nIndex用于控制是对光驱，软驱还是对USB启用或禁用
// 也是可取3个值，0 代表软驱，
//				  1 代表光驱
//				  2 代表USB
// 譬如要对光驱实现禁用，可以这样调用此函数
// ControlDisk(1,  0);
 BOOL  myControlDisk(  QWM_DYN_LIB  *  pDynLib,  int  nIndex,  int  nStatus  )
{
	 BOOL			bRet				=	FALSE;
	 HDEVINFO		hDevInfo			=	NULL;
	 char		*	GUIDString			=	NULL;
	 GUID			guid;

	 if  (  !pDynLib->pUuidFromString
		 ||  !pDynLib->pSetupDiGetClassDevs
			||  !pDynLib->pSetupDiEnumDeviceInfo
				||  !pDynLib->pSetupDiDestroyDeviceInfoList
					||  !pDynLib->pSetupDiEnumDeviceInfo
						||  !pDynLib->pSetupDiSetClassInstallParams
							||  !pDynLib->pSetupDiCallClassInstaller  )  return  FALSE;
	 if  (  -1  ==  nStatus  )  return FALSE;

	 ZeroMemory(  &guid,  sizeof(  GUID  )  );
	 switch  (  nIndex  )  {
		     case  0: // 0 代表软驱
					//  GUIDString = ("4D36E980-E325-11CE-BFC1-08002BE10318");
					//  GUIDString = ("4D36E967-E325-11CE-BFC1-08002BE10318");
				    GUIDString  =  (  "4D36E969-E325-11CE-BFC1-08002BE10318"  );
					pDynLib->pUuidFromString(  (  unsigned  char  *  )GUIDString,  &guid  );
					break; 
			 case  1: // 1 代表光驱 
				    GUIDString  =  (  "4D36E965-E325-11CE-BFC1-08002BE10318"  );
					pDynLib->pUuidFromString(  (  unsigned  char  *  )GUIDString,  &guid  );
					break;
			   case 2: // 2 代表USB
					GUIDString  =  (  "36FC9E60-C465-11CF-8056-444553540000"  );
					pDynLib->pUuidFromString(  (  unsigned  char  *  )GUIDString,  &guid  );
					break;
			   default:
						goto  errLabel;
	 }
			 
	 hDevInfo  =  pDynLib->pSetupDiGetClassDevs(  &guid,  NULL,  NULL,  DIGCF_PRESENT  );
	 if  (  INVALID_HANDLE_VALUE == hDevInfo  )  {
		 qyDisplayLastError(  ""  );  goto  errLabel;
	 }
	
	 DWORD				i;
	 SP_DEVINFO_DATA	DeviceInfoData;
	
	 ZeroMemory(  &DeviceInfoData,  sizeof(  SP_DEVINFO_DATA  )  );
	 DeviceInfoData.cbSize  =  sizeof(  SP_DEVINFO_DATA  );

	 for  (  i  =  0;  pDynLib->pSetupDiEnumDeviceInfo(  hDevInfo,  i,  &DeviceInfoData  );  ++  i  )  {
		 if  (  1  ==  nStatus  )  myStateChange(  pDynLib,  DICS_ENABLE,  i,  hDevInfo  );
		 else  if  (  0  ==  nStatus  )  myStateChange(  pDynLib,  DICS_DISABLE,  i,  hDevInfo  );
	 }

	 bRet  =  TRUE;

errLabel:

	 // 释放 device information set
	 if  (  isHandleValid(  hDevInfo  )  )  pDynLib->pSetupDiDestroyDeviceInfoList(  hDevInfo  );
	 
	 return  bRet;

}


 //  98下禁用：floppy\cdrom\usb
 //  1）floppy:驱动器名称A、B；在HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Policies\Explorer,用NoDrives隐藏
 //  2）cdrom:在HKEY_LOCAL_MACHINE\Enum\SCSI\**\**,读取Class = "CDROM"设备的CurrentDriveLetterAssignment,然后同上面一样进行隐藏
 //	 3）usb:同cdrom，"ClassGUID"="{4d36e967-e325-11ce-bfc1-08002be10318}"CONST_classGUID_disk
 int  proc98DevRule(  QWM_THREADINFO  *  pSubThreadInfo  )
{
	 int	iErr  =  -1;
	 QY_W_MON				*	pQwm									=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	 //  DWORD						dwDriveFlags							=	0;
	 HKEY						hKey	=	NULL;	BOOL	bKeyOpen	=  FALSE;
 	 HKEY						hKey1	=	NULL;	BOOL	bKey1Open	=  FALSE;
 	 HKEY						hKey2	=	NULL;	BOOL	bKey2Open	=  FALSE;
	 DWORD						dwType;
	 DWORD						cbData									=  sizeof(  DWORD  );
 	 TCHAR					*	subKeyName								=  NULL;
	 TCHAR					*	regValName								=  NULL;
	 DWORD						dwNeededVal;
	 DWORD						dwRegVal;
	 TCHAR						tSubKey[MAX_PATH  +  1]					=  _T(  ""  );
	 TCHAR						tmpBuf[MAX_PATH  +  1]					=  _T(  ""  );
	 int						i;
	 DWORD						flag_floppy								=	0;
	 DWORD						flag_cdrom								=	0;
	 int						iRet;
	 char						regData[40]								=  "";
	 unsigned  char				ucDevCmd_floppy;
	 unsigned  char				ucDevCmd_cdrom;
	 unsigned  char				ucDevCmd_usb;
	 unsigned  char				ucbNeedToLog_floppy						=	FALSE;
	 unsigned  char				ucbNeedToLog_cdrom						=	FALSE;
	 unsigned  char				ucbNeedToLog_usb						=	FALSE;
	 TCHAR						drv;
	 TCHAR						drvName[128];
	 int						iDrvType;
	 //  unsigned  char				ucbFloppyExists;
	 //  static  unsigned  char		ucbRestarted							=	FALSE;	//  这个变量为了在没有软驱的计算机上避免反复启用软驱而设置的
	 QWM_DYN_LIB		*		pDynLib									=	(  QWM_DYN_LIB  *  )pQwm->env.pDynLibs;

	 
	 subKeyName		=  _T(  CONST_subKeyName_explorer  );
	 regValName		=  _T(  CONST_regValName_noDrives  );
	 if  (  RegOpenKeyEx(  HKEY_CURRENT_USER,  subKeyName,  0,  KEY_ALL_ACCESS,  &hKey  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	 bKeyOpen	=  TRUE;

	 cbData  =  sizeof(  dwRegVal  );
	 if  (  RegQueryValueEx(  hKey,  regValName,  0,  &dwType,  (  unsigned  char  *  )&dwRegVal,  &cbData  )  !=  ERROR_SUCCESS  )  {
		 traceLogA(  "没有[%s]注册表项",  regValName  );  dwRegVal  =  0;
	 }
	 traceLogA(  "首次读取的noDrives值为 [%d]",  dwRegVal  );

	 ucDevCmd_floppy  =  pQwm->cfg.pcRules.dev.ucFloppyCmd;
	 ucDevCmd_cdrom  =  pQwm->cfg.pcRules.dev.ucCdromCmd;
	 ucDevCmd_usb	=	pQwm->cfg.pcRules.dev.ucUsbStorCmd;


	 //  处理floppy
	 flag_floppy  =  (  ucDevCmd_floppy  ==  CONST_devCmd_prohibited  )  ?  3  :  0;
	 if  (  (  dwRegVal  &  0x3  )  !=  flag_floppy  )  ucbNeedToLog_floppy  =  TRUE;

	 //  2005/12/25, 加入在设备管理器里起禁软驱的功能
	 /*  //  2005/12/27, 取消起禁软驱的功能，因为发现鲁抗公司的98有的禁了软驱之后仍有盘符存在，显然对这里的规律还不是很了解。故暂时注释掉
	 ucbFloppyExists  =  FALSE;
	 iDrvType  =  GetDriveType(  "a:"  );
	 if  (  iDrvType  ==  DRIVE_REMOVABLE  )  ucbFloppyExists  =  TRUE;
	 iDrvType  =  GetDriveType(  "b:"  );
	 if  (  iDrvType  ==  DRIVE_REMOVABLE  )  ucbFloppyExists  =  TRUE;
	 //	 
	 if  (  !ucbFloppyExists  &&  ucDevCmd_floppy  ==  CONST_devCmd_permitted  )  {
		 if  (  !ucbRestarted  )  {
			 traceLogA(  "floppy doesn't exist and cmd is permitted so we will call controlDisk to restart fdc"  );
		 	 myControlDisk(  0,  1  );
		 	 ucbRestarted  =  TRUE;
		}
		}
	 else  ucbRestarted  =  FALSE;
	 //		   
	 if  (  ucbFloppyExists  &&  ucDevCmd_floppy  ==  CONST_devCmd_prohibited  )  {
		 traceLogA(  "floppy exists and cmd is prohibited so we will call controlDisk to prohibit fdc"  );
		 myControlDisk(  0,  0  );
	 }
	 */
 

	 //  为处理cdrom和USB盘
	 for  (  drv  =  'c';  drv  <=  'z';  drv  ++  )  {
		  _sntprintf(  drvName,  mycountof(  drvName  ),  _T(  "%c:"  ),  drv  );
		  iDrvType  =  GetDriveType(  drvName  );

		  if  (  iDrvType  ==  DRIVE_CDROM  )  {
			  
			  if  (  ucDevCmd_cdrom  ==  CONST_devCmd_prohibited  )  {

				  flag_cdrom  |=  1  <<  (  drv  -  'a'  );	
			  
				  if  (  haveDisk(  drv  )  &&  pDynLib->pmciSendCommand  )  {
			  	  	  DWORD					flag;
			  	  	  MCI_OPEN_PARMS		openParams;
			  	  	  MCI_SET_PARMS			setParams;

				  	  traceLogA(  "准备弹出光盘"  );

			  	  	  flag  =  MCI_NOTIFY  |  MCI_OPEN_TYPE  |  MCI_OPEN_SHAREABLE  |  MCI_OPEN_ELEMENT  |  MCI_OPEN_TYPE_ID;
				  	  memset(  &openParams,  0,  sizeof(  openParams  )  );
				  	  openParams.lpstrDeviceType   =  (  LPCTSTR  )MCI_DEVTYPE_CD_AUDIO;
				  	  openParams.lpstrElementName   =  drvName;
			  		  if  (  pDynLib->pmciSendCommand(  0,  MCI_OPEN,  flag,  (  DWORD  )&openParams  )  )  {
						  traceLogA(  "mciSendCommand failed"  );  continue;
					  }
		  
					  flag  =  MCI_NOTIFY  |  MCI_SET_DOOR_OPEN;
					  memset(  &setParams,  0,  sizeof(  setParams  )  );
					  if  (  pDynLib->pmciSendCommand(  MCI_ALL_DEVICE_ID,  MCI_SET,  flag,  (  DWORD  )&setParams  )  )  {
						  traceLogA(  "mciSendCommand failed"  );
					  }

					  pDynLib->pmciSendCommand(  MCI_ALL_DEVICE_ID,  MCI_CLOSE,  0,  NULL  );
				  }

		 	  }
		  }		//  cdrom的处理

		  if  (  iDrvType  ==  DRIVE_REMOVABLE  &&  iDrvType  !=  DRIVE_CDROM  )  {
			  if  (  ucDevCmd_usb  ==  CONST_devCmd_restartToProhibit  )  {
				  traceLogA(  "将重起以阻断USB盘"  );
				  qwmLogDevEvent(  pSubThreadInfo,  CONST_qyEventType_nm_usbRestartToProhibit,  NULL  );
				  doReboot(  pSubThreadInfo,  TRUE,  TRUE,  TRUE  );
			  }
		  }		 

	 }
	 if  (  (  dwRegVal  &  ~0x3  )  !=  flag_cdrom  )  ucbNeedToLog_cdrom  =  TRUE;
	
	 if  (  ucbNeedToLog_floppy  ||  ucbNeedToLog_cdrom  )  {
		 dwNeededVal  =  flag_floppy  |  flag_cdrom;
		 cbData  =  sizeof(  dwNeededVal  );
		 if  (  RegSetValueEx(  hKey,  _T(  CONST_regValName_noDrives  ),  0,  REG_DWORD,  (  unsigned  char  *  )&dwNeededVal,  cbData  )  !=  ERROR_SUCCESS  )  goto  errLabel;

		 if  (  ucbNeedToLog_floppy  )  {
			 if  (  ucDevCmd_floppy  ==  CONST_devCmd_prohibited  )  qwmLogDevEvent(  pSubThreadInfo,  CONST_qyEventType_nm_floppyOff,  NULL  );
			 else  qwmLogDevEvent(  pSubThreadInfo,  CONST_qyEventType_nm_floppyOn,  NULL  );
		 }	
		 if  (  ucbNeedToLog_cdrom  )  {
			 if  (  ucDevCmd_cdrom  ==  CONST_devCmd_prohibited  )  qwmLogDevEvent(  pSubThreadInfo,  CONST_qyEventType_nm_cdromOff,  NULL  );
		 	 else  qwmLogDevEvent(  pSubThreadInfo,  CONST_qyEventType_nm_cdromOn,  NULL  );					   
	 	 }
	 }

	
	 /*
	 */
	 traceLogA(  "cdrom  ok!"  );  
	 

	 //  处理usb,  禁止所有usb
	 memset(  &tSubKey,  0,  sizeof(  tSubKey  )  );
	 memset(  &tmpBuf,  0,  sizeof(  tmpBuf  )  );
	 subKeyName		=  _T(  CONST_subKeyName_rootHub  );
	 if  (  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  subKeyName,  0,  KEY_ALL_ACCESS,  &hKey1  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	 bKey1Open	=  TRUE;

	 for  (  i = 0; ; i ++  )  {
		  iRet  =  RegEnumKey(  hKey1,  i,  tSubKey,  sizeof(  tSubKey  )  );
		  if  (  iRet  ==  ERROR_NO_MORE_ITEMS  ||  iRet  !=  ERROR_SUCCESS  )  break;
  		  _sntprintf(  tmpBuf,  mycountof(  tmpBuf  ),  _T(  "%s\\%s"  ),  subKeyName,  tSubKey  );
		  traceLogA(  "包含以下usb root_hub：%s",  tmpBuf  );

		  if  (  RegCreateKey(  HKEY_CURRENT_CONFIG,  tmpBuf,  &hKey2  )  ==  ERROR_SUCCESS  )  {
			  bKey2Open  =  TRUE;
			  traceLogA(  " 成功创建 [%s]",  tmpBuf  );
			  if  (  RegQueryValueEx(  hKey2,  _T(  CONST_regValName_csConfigFlags  ),  0,  &dwType,  (  unsigned  char  *  )&dwRegVal,  &cbData  )  !=  ERROR_SUCCESS  )  {
				  dwRegVal  =  0;
				  if  (  RegSetValueEx(  hKey2,  _T(  CONST_regValName_csConfigFlags  ),  0,  REG_BINARY,  (  unsigned  char  *  )&dwRegVal,  cbData  )  ==  ERROR_SUCCESS  )  
					  traceLogA(  "成功创建[%s]",  CONST_regValName_csConfigFlags  );
			  	  }
			  else  {
				    if  (  ucDevCmd_usb  ==  CONST_devCmd_prohibited  )  dwNeededVal  =  1;
					else  dwNeededVal  =  0;

				  	if  (  dwRegVal != dwNeededVal  )  {				
						ucbNeedToLog_usb  =  TRUE;
					  	if  (  ucDevCmd_usb  ==  CONST_devCmd_prohibited  )  {
							if  (  RegSetValueEx(  hKey2,  _T(  CONST_regValName_csConfigFlags  ),  0,  REG_BINARY,  (  unsigned  char  *  )&dwNeededVal,  cbData  )  !=  ERROR_SUCCESS  )  goto  errLabel;
							traceLogA(  "采用第二套方案禁用usb,  csConfigFlags is [%d]",  dwNeededVal  );    
							}
						else  {
							  if  (  RegSetValueEx(  hKey2,  _T(  CONST_regValName_csConfigFlags  ),  0,  REG_BINARY,  (  unsigned  char  *  )&dwNeededVal,  cbData  )  !=  ERROR_SUCCESS  )  goto  errLabel;
							  traceLogA(  "采用第二套方案启用usb,  csConfigFlags is [%d]",  dwNeededVal  );
					  	}
				  	}
			  }
		  }
		  RegCloseKey(  hKey2  );  bKey2Open  =  FALSE;
	 }

	 if  (  ucbNeedToLog_usb  )  {
		 if  (  ucDevCmd_usb  ==  CONST_devCmd_prohibited  )  qwmLogDevEvent(  pSubThreadInfo,  CONST_qyEventType_nm_usbStorOffFor9x,  NULL  );
		 else  qwmLogDevEvent(  pSubThreadInfo,  CONST_qyEventType_nm_usbStorOnFor9x,  NULL  );
	 }
	 traceLogA(  "usb  ok!"  );  

	 iErr  =  0;
errLabel:
	 if  (  bKeyOpen  )  RegCloseKey( hKey  );
	 if  (  bKey1Open  )  RegCloseKey(  hKey1  );
	 if  (  bKey2Open  )  RegCloseKey(  hKey2  );
	 return  iErr;
}


 int  procNtUsbRule(  QWM_THREADINFO  *  pSubThreadInfo  );
 int  procWLanAdapterRule(  QWM_THREADINFO  *  pSubThreadInfo  );
 int  procBlueToothRule(  QWM_THREADINFO  *  pSubThreadInfo  );
 int  procInfraredRule(  QWM_THREADINFO  *  pSubThreadInfo  );
 int  proc1394Rule(  QWM_THREADINFO  *  pSubThreadInfo  );
 int  procWpdRule(  QWM_THREADINFO  *  pSubThreadInfo  );

 int  procNtDevRule(  QWM_THREADINFO  *  pSubThreadInfo  )
{
	 int					iErr			=  -1;
	 QY_W_MON		*		pQwm			=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	 DWORD					dwNeededVal;
	 DWORD					dwRegVal;
	 HKEY					hKeyResult;			
	 DWORD					dwType;
	 DWORD					cbData			=  sizeof(  long  );
 	 TCHAR				*	subKeyName		=  NULL;
	 TCHAR				*	regValName		=  NULL;
	 BOOL					bKeyOpen		=  FALSE;
	 
	 if  (  pQwm->env.iPlatformId  ==  CONST_qyPlatform_nt  )  {
		 traceLogA(  "Sorry, nt is not supported"  );  goto  errLabel;
	 }

	 //  禁止fdc,  start =  4;
	 subKeyName  =  _T(  CONST_subKeyName_fdc  );
	 regValName	=  _T(  CONST_regValName_start  );
	 //  注意这里的设值
	 if  (  pQwm->cfg.pcRules.dev.ucFloppyCmd  ==  CONST_devCmd_prohibited  )  dwNeededVal  =  4;
	 else  dwNeededVal  =  3;

	 if  (  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  subKeyName,  0,  KEY_ALL_ACCESS,  &hKeyResult  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	 bKeyOpen  =  TRUE;

	 cbData  =  sizeof(  dwRegVal  );
	 if  (  RegQueryValueEx(  hKeyResult,  regValName,  0,  &dwType,  (  unsigned  char  *  )&dwRegVal,  &cbData  )  !=  ERROR_SUCCESS  )  {
		 traceLogA(  "没有[%s]注册表项",  regValName  );  dwRegVal  =  0;
	 }
	 if  (  dwRegVal  !=  dwNeededVal  )  {
		 traceLogA(  "可提供报警, 下面要设置软驱为%d",  dwNeededVal  );
	 	 if  (  RegSetValueEx(  hKeyResult,  regValName,  0,  REG_DWORD,  (  unsigned  char  *  )&dwNeededVal,  cbData  )  !=  ERROR_SUCCESS  )  goto  errLabel;
		 if  (  pQwm->cfg.pcRules.dev.ucFloppyCmd  ==  CONST_devCmd_prohibited  )  qwmLogDevEvent(  pSubThreadInfo,  CONST_qyEventType_nm_floppyOff,  NULL  );
		 else  qwmLogDevEvent(  pSubThreadInfo,  CONST_qyEventType_nm_floppyOn,  NULL  );
	 }	 
	 RegCloseKey(  hKeyResult  );  bKeyOpen  =  FALSE;

	 //  下面禁止cdrom
	 subKeyName  =  _T(  CONST_subKeyName_cdrom  );
	 regValName	=  _T(  CONST_regValName_start  );
	 //  注意这里的设值
	 if  (  pQwm->cfg.pcRules.dev.ucCdromCmd  ==  CONST_devCmd_prohibited  )  dwNeededVal  =  4;
	 else  dwNeededVal  =  1;
	 	 
	 //
	 if  (  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  subKeyName,  0,  KEY_ALL_ACCESS,  &hKeyResult  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	 bKeyOpen  =  TRUE;
	 
	 cbData  =  sizeof(  dwRegVal  );
	 if  (  RegQueryValueEx(  hKeyResult,  regValName,  0,  &dwType,  (  unsigned  char  *  )&dwRegVal,  &cbData  )  !=  ERROR_SUCCESS  )  {
		 traceLogA(  "没有[%s]注册表项",  regValName  );  dwRegVal  =  0;
	 }
	 if  (  dwRegVal  !=  dwNeededVal  )  {
		 traceLogA(  "可提供报警, 下面要设置cdrom为%d",  dwNeededVal  );
		 if  (  RegSetValueEx(  hKeyResult,  regValName,  0,  REG_DWORD,  (  unsigned  char  *  )&dwNeededVal,  cbData  )  !=  ERROR_SUCCESS  )  goto  errLabel;
		 if  (  pQwm->cfg.pcRules.dev.ucCdromCmd  ==  CONST_devCmd_prohibited  )  qwmLogDevEvent(  pSubThreadInfo,  CONST_qyEventType_nm_cdromOff,  NULL  );
		 else  qwmLogDevEvent(  pSubThreadInfo,  CONST_qyEventType_nm_cdromOn,  NULL  );
	 }
	 RegCloseKey(  hKeyResult  );  bKeyOpen  =  FALSE;
	 
	 //  2007/02/11, 对vista,在注册表里也禁用USB
	 switch  (  pQwm->env.iPlatformId  )  {
			 case  CONST_qyPlatform_winnt:
			 case  CONST_qyPlatform_win2k:
			 case  CONST_qyPlatform_win2003:
				   break;
			 case  CONST_qyPlatform_winxp:	
				   break;
			 case  CONST_qyPlatform_winVista:		//  2007/02/11, 因为vista禁用不了安全模式，所以也加上注册表禁用的方式来加强USB的管理
		 	 default:
				     subKeyName  =  _T(  CONST_subKeyName_usbStor  );
					 regValName	=  _T(  CONST_regValName_start  );
					 //  注意这里的设值
					 switch  (  pQwm->cfg.pcRules.dev.ucUsbStorCmd  )  {
							 case  CONST_devCmd_prohibited:
					 		 case  CONST_devCmd_restartToProhibit:
						 		   dwNeededVal  =  4;
								   break;
							 default:
								     dwNeededVal  =  3;
									 break;
					 }
	 	 
					 //
					 if  (  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  subKeyName,  0,  KEY_ALL_ACCESS,  &hKeyResult  )  !=  ERROR_SUCCESS  )  goto  errLabel;
					 bKeyOpen  =  TRUE;
	 
					 cbData  =  sizeof(  dwRegVal  );
					 if  (  RegQueryValueEx(  hKeyResult,  regValName,  0,  &dwType,  (  unsigned  char  *  )&dwRegVal,  &cbData  )  !=  ERROR_SUCCESS  )  {
						 traceLogA(  "没有[%s]注册表项",  regValName  );  dwRegVal  =  0;
					 }
					 if  (  dwRegVal  !=  dwNeededVal  )  {
						 traceLogA(  "可提供报警, 下面要设置usbstor为%d",  dwNeededVal  );
						 if  (  RegSetValueEx(  hKeyResult,  regValName,  0,  REG_DWORD,  (  unsigned  char  *  )&dwNeededVal,  cbData  )  !=  ERROR_SUCCESS  )  goto  errLabel;
					 }
					 RegCloseKey(  hKeyResult  );  bKeyOpen  =  FALSE;

				     break;
	 }

	 //  禁止usb
	 procNtUsbRule(  pSubThreadInfo  );	

	 //  2010/05/20
	 procWLanAdapterRule(  pSubThreadInfo  );

	 //  2010/08/18
	 procBlueToothRule(  pSubThreadInfo  );
	 procInfraredRule(  pSubThreadInfo  );
	 proc1394Rule(  pSubThreadInfo  );

	 //  2011/08/20
	 procWpdRule(  pSubThreadInfo  );	  


	 iErr  =  0;
errLabel:

	 if  (  bKeyOpen  )  RegCloseKey(  hKeyResult  );
	 return  iErr;
}


