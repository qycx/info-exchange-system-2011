

#include	"stdafx.h"
#include	<sys/types.h>
#include	<sys/stat.h>
#include	"qmdCommon.h"


 int  fwFilterComponentInfo(  QWM_COMPONENT_INFO  *  pComponent  )
{
	 int						iErr			=	-1;
	 char						c				=	'\'';

	 if  (  !pComponent  )  return  0;
	 fwReplaceChrInStr(  c,  pComponent->makeTime,  sizeof(  pComponent->makeTime  )  );
	 fwReplaceChrInStr(  c,  pComponent->installTime,  sizeof(  pComponent->installTime  )  );
	 //  2005/11/16起，ＣＯＭＰＯＮＥＮＴ里的大部分数据使用ＵＮＩＣＯＤＥ编码，不需要下面的过滤了
	 switch  (  pComponent->uiType  )  {
		     
			 case  CONST_assetType_cpu:		break;
			 case  CONST_assetType_mem:		break;
			 case  CONST_assetType_bios:    
				   //  fwReplaceChrInStr(  c,  pComponent->u.bios.identifier,  sizeof(  pComponent->u.bios.identifier  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.bios.identifier,  sizeof(  pComponent->u.bios.identifier  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.bios.systemBiosDate,  sizeof(  pComponent->u.bios.systemBiosDate  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.bios.systemBiosDate,  sizeof(  pComponent->u.bios.systemBiosDate  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.bios.systemBiosVer,  sizeof(  pComponent->u.bios.systemBiosVer  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.bios.systemBiosVer,  sizeof(  pComponent->u.bios.systemBiosVer  )  /  sizeof(  TCHAR  )  );
				   break;
			 case  CONST_assetType_floppy:
				   //  fwReplaceChrInStr(  c,  pComponent->u.floppy.driverDesc,  sizeof(  pComponent->u.floppy.driverDesc  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.floppy.driverDesc,  sizeof(  pComponent->u.floppy.driverDesc  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.floppy.driverDate,  sizeof(  pComponent->u.floppy.driverDate  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.floppy.driverDate,  sizeof(  pComponent->u.floppy.driverDate  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.floppy.driverVersion,  sizeof(  pComponent->u.floppy.driverVersion  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.floppy.driverVersion,  sizeof(  pComponent->u.floppy.driverVersion  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.floppy.vendor,  sizeof(  pComponent->u.floppy.vendor  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.floppy.vendor,  sizeof(  pComponent->u.floppy.vendor  )  /  sizeof(  TCHAR  )  );
				   break;				   
			 case  CONST_assetType_monitor:
				   //  fwReplaceChrInStr(  c,  pComponent->u.monitor.driverDesc,  sizeof(  pComponent->u.monitor.driverDesc  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.monitor.driverDesc,  sizeof(  pComponent->u.monitor.driverDesc  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.monitor.driverDate,  sizeof(  pComponent->u.monitor.driverDate  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.monitor.driverDate,  sizeof(  pComponent->u.monitor.driverDate  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.monitor.driverVersion,  sizeof(  pComponent->u.monitor.driverVersion  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.monitor.driverVersion,  sizeof(  pComponent->u.monitor.driverVersion  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.monitor.vendor,  sizeof(  pComponent->u.monitor.vendor  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.monitor.vendor,  sizeof(  pComponent->u.monitor.vendor  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.monitor.locationInformation,  sizeof(  pComponent->u.monitor.locationInformation  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.monitor.locationInformation,  sizeof(  pComponent->u.monitor.locationInformation  )  /  sizeof(  TCHAR  )  );
				   break;
			 case  CONST_assetType_ideHardDisk:
			 case  CONST_assetType_scsiHardDisk:
			 case  CONST_assetType_ideCdrom:
			 case  CONST_assetType_usbDisk:
				   //  fwReplaceChrInStr(  c,  pComponent->u.disk.modelNo,  sizeof(  pComponent->u.disk.modelNo  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.disk.modelNo,  sizeof(  pComponent->u.disk.modelNo  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.disk.firmwareRevision,  sizeof(  pComponent->u.disk.firmwareRevision  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.disk.firmwareRevision,  sizeof(  pComponent->u.disk.firmwareRevision  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.disk.serialNo,  sizeof(  pComponent->u.disk.serialNo  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.disk.serialNo,  sizeof(  pComponent->u.disk.serialNo  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.disk.driverDesc,  sizeof(  pComponent->u.disk.driverDesc  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.disk.driverDesc,  sizeof(  pComponent->u.disk.driverDesc  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.disk.driverDate,  sizeof(  pComponent->u.disk.driverDate  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.disk.driverDate,  sizeof(  pComponent->u.disk.driverDate  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.disk.driverVersion,  sizeof(  pComponent->u.disk.driverVersion  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.disk.driverVersion,  sizeof(  pComponent->u.disk.driverVersion  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.disk.vendor,  sizeof(  pComponent->u.disk.vendor  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.disk.vendor,  sizeof(  pComponent->u.disk.vendor  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.disk.locationInformation,  sizeof(  pComponent->u.disk.locationInformation  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.disk.locationInformation,  sizeof(  pComponent->u.disk.locationInformation  )  /  sizeof(  TCHAR  )  );
				   break;
			 case  CONST_assetType_display:
				   //  fwReplaceChrInStr(  c,  pComponent->u.display.driverDesc,  sizeof(  pComponent->u.display.driverDesc  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.display.driverDesc,  sizeof(  pComponent->u.display.driverDesc  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.display.driverDate,  sizeof(  pComponent->u.display.driverDate  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.display.driverDate,  sizeof(  pComponent->u.display.driverDate  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.display.driverVersion,  sizeof(  pComponent->u.display.driverVersion  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.display.driverVersion,  sizeof(  pComponent->u.display.driverVersion  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.display.vendor,  sizeof(  pComponent->u.display.vendor  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.display.vendor,  sizeof(  pComponent->u.display.vendor  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.display.locationInformation,  sizeof(  pComponent->u.display.locationInformation  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.display.locationInformation,  sizeof(  pComponent->u.display.locationInformation  )  /  sizeof(  TCHAR  )  );
				   break;
			 case  CONST_assetType_networkCard:
 				   //  fwReplaceChrInStr(  c,  pComponent->u.net.driverDesc,  sizeof(  pComponent->u.net.driverDesc  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.net.driverDesc,  sizeof(  pComponent->u.net.driverDesc  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.net.driverDate,  sizeof(  pComponent->u.net.driverDate  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.net.driverDate,  sizeof(  pComponent->u.net.driverDate  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.net.driverVersion,  sizeof(  pComponent->u.net.driverVersion  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.net.driverVersion,  sizeof(  pComponent->u.net.driverVersion  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.net.vendor,  sizeof(  pComponent->u.net.vendor  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.net.vendor,  sizeof(  pComponent->u.net.vendor  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.net.locationInformation,  sizeof(  pComponent->u.net.locationInformation  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.net.locationInformation,  sizeof(  pComponent->u.net.locationInformation  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.net.name,  sizeof(  pComponent->u.net.name  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.net.name,  sizeof(  pComponent->u.net.name  )  /  sizeof(  TCHAR  )  );
				   //  fwReplaceChrInStr(  c,  pComponent->u.net.networkaddress,  sizeof(  pComponent->u.net.networkaddress  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.net.networkaddress,  sizeof(  pComponent->u.net.networkaddress  )  /  sizeof(  TCHAR  )  );
				   break;
			 case  CONST_assetType_software:
				   //  fwReplaceChrInStr(  c,  pComponent->u.software.displayName,  sizeof(  pComponent->u.software.displayName  )  );
				   filterStr2Display(  (  TCHAR  *  )pComponent->u.software.displayName,  sizeof(  pComponent->u.software.displayName  )  /  sizeof(  TCHAR  )  );
				   break;
			 case  CONST_assetType_soundCard:
			 case  CONST_assetType_modem:
			 default:
					break;
	 }
	 
	 iErr  =  0;
//  errLabel:
	 return  iErr;
}

 extern  "C"  int  fwFilterAssetsInfo(  QWM_ASSETS_INFO  *  pAssetsInfo  )
{
	 int						iErr			=	-1;
	 char						c				=	'\'';

	 if  (  !pAssetsInfo  )  return  0;
	 if  (  pAssetsInfo->cnt  >  sizeof(  pAssetsInfo->components  )  /  sizeof(  pAssetsInfo->components[0]  )  )  return  -1;

	 fwReplaceChrInStr(  c,  pAssetsInfo->winDir,  sizeof(  pAssetsInfo->winDir  )  );
	 fwReplaceChrInStr(  c,  pAssetsInfo->usrName,  sizeof(  pAssetsInfo->usrName  )  );
	 for  (  unsigned  int  ui  =  0;  ui  <  pAssetsInfo->cnt;  ui  ++  )  {
		  if  (  fwFilterComponentInfo(  &pAssetsInfo->components[ui]  )  )  goto  errLabel;
	 }
	 iErr	=	0;
errLabel:
	 return  iErr;
}

 extern  "C"  int  fwFilterPcCommU(  QY_PC_COMMU  *  pPcCommU  )
{
	 int						iErr			=	-1;
	 char						c				=	'\'';
	 unsigned  int				ui;
	 int						len;

	 fwReplaceChrInStr(  c,  pPcCommU->head.winDir,  sizeof(  pPcCommU->head.winDir  )  );

	 switch  (  pPcCommU->uiType  )  {
			 case  CONST_pcCommType_eventLog:  {
				   QY_EVENTLOG_PROP	*	pEventLog	=	NULL;
				   //
				   if  (  pPcCommU->head.cnt  >  sizeof(  pPcCommU->eventLogsInfo.mems  )  /  sizeof(  pPcCommU->eventLogsInfo.mems[0]  )  )  goto  errLabel;
				   for  (  ui  =  0;  ui  <  pPcCommU->head.cnt;  ui  ++  )  {
					    pEventLog  =  &pPcCommU->eventLogsInfo.mems[ui];
					    fwReplaceChrInStr(  c,  pEventLog->eventLogDesc,  sizeof(  pEventLog->eventLogDesc  )  );
						trim(  pEventLog->eventLogDesc  );
						pEventLog->eventLogDesc[sizeof(  pEventLog->eventLogDesc  )  -  2]  =  0;
						len  =  strlen(  pEventLog->eventLogDesc  );
						pEventLog->eventLogDesc[len]  =  ' ';
						pEventLog->eventLogDesc[len  +  1]  =  0;
				   }
					}
				   break;
			 case  CONST_pcCommType_registryVal:  {
				   QY_PC_REGISTRYVAL  *  pVal  =  NULL;
				   //
				   if  (  pPcCommU->registryVals.cnt  >  mycountof(  pPcCommU->registryVals.mems  )  )  goto  errLabel;
				   //
				   fwReplaceChrInStr(  c,  pPcCommU->registryVals.szSidKey,  sizeof(  pPcCommU->registryVals.szSidKey  )  );
				   filterStr2Display(  pPcCommU->registryVals.wUsrName,  mycountof(  pPcCommU->registryVals.wUsrName  )  );
				   for  (  ui  =  0;  ui  <  pPcCommU->registryVals.cnt;  ui  ++  )  {
					    pVal  =  &pPcCommU->registryVals.mems[ui];
						filterStr2Display(  pVal->wCfgName,  mycountof(  pVal->wCfgName  )  );
						switch  (  pVal->iValType  )  {
								case  REG_SZ:
								case  REG_EXPAND_SZ:
								case  REG_MULTI_SZ:
									  filterStr2Display(  pVal->u.wCfgVal,  mycountof(  pVal->u.wCfgVal  )  );
									  break;
								default:
										break;
						}

				   }
					}
				   break;
			 case  CONST_pcCommType_process:  {
				   QY_PROCESS_PROP	*	p	=	NULL;
				   
				   if  (  pPcCommU->processesInfo.cnt  >  mycountof(  pPcCommU->processesInfo.mems  )  )  goto  errLabel;
				   for  (  ui  =  0;  ui  <  (  int  )pPcCommU->processesInfo.cnt;  ui  ++  )  {
					    p  =  &pPcCommU->processesInfo.mems[ui];
						//
						fwReplaceChrInStr(  c,  p->appPath,  mycountof(  p->appPath  )  );
						fwReplaceChrInStr(  c,  p->cmdLine,  mycountof(  p->cmdLine  )  );
				   }
					}
				   break;
			 default:
					break;
	 }

	 iErr  =  0;
errLabel:
	 return  iErr;
}


 extern  "C"  int  fwFilterPcNetworkPropU(  QY_PCNETWORK_PROPU    *  pPropU  )
{
	 int						iErr			=	-1;
	 char						c				=	'\'';

	 //fwReplaceChrInStr(  c,  pPcCommU->head.winDir,  sizeof(  pPcCommU->head.winDir  )  );

	 switch  (  pPropU->uiType  )  {
			 case  CONST_pcCommType_adapter:
				   break;
			 case  CONST_pcCommType_proxy:  {
				   QWM_USR_INFO  *  pUsrInfo	=	(  QWM_USR_INFO  *  )pPropU;
				   fwReplaceChrInStr(  c,  pUsrInfo->szSubKey,  sizeof(  pUsrInfo->szSubKey  )  );			//  用户子键名
				   fwReplaceChrInStr(  c,  pUsrInfo->name,  sizeof(  pUsrInfo->name  )  );					//  当前登录用户名，2003/09/12添加
				   fwReplaceChrInStr(  c,  pUsrInfo->proxyServer,  sizeof(  pUsrInfo->proxyServer  )  );	//  IE的代理设置，2003/09/12添加
				   fwReplaceChrInStr(  c,  pUsrInfo->proxyOverride,  sizeof(  pUsrInfo->proxyOverride  )  );//		设置为<local>，则表明对本地地址不使用代理服务器
				   fwReplaceChrInStr(  c,  pUsrInfo->autoConfigUrl,  sizeof(  pUsrInfo->autoConfigUrl  )  );//  2006/11/15, 自动配置脚本
					}
				   break;
			 case  CONST_pcCommType_computer:
			 case  CONST_pcCommType_cleanNetworkProp:
			 case  CONST_pcCommType_windowsUpdatePolicy:
			 default:
					break;
 
	}

	 iErr  =  0;  
//  errLabel:
	 return  iErr;

}


 extern  "C"  int  fwFilterSecChkEvent(  QNM_SECCHK_EVENT  *  pEvent  )
{
	 int						iErr			=	-1;
	 char						c				=	'\'';

	 if  (  !pEvent  )  return  0;

	 fwReplaceChrInStr(  c,  pEvent->des0,  sizeof(  pEvent->des0  )  );
	 fwReplaceChrInStr(  c,  pEvent->des1,  sizeof(  pEvent->des1  )  );
	 fwReplaceChrInStr(  c,  pEvent->des2,  sizeof(  pEvent->des2  )  );

	 iErr  =  0;

//  errLabel:
	 return  iErr;
}
