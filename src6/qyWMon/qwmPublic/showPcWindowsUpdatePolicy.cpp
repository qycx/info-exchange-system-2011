

#include	<windows.h>
#include	<winsock.h>
#include	<ras.h>
#include	<raserror.h>
#include	<commctrl.h>
#include	<iphlpapi.h>
#include	<tchar.h>
#include	"asrWMon.h"



 int	 showPcWindowsUpdatePolicy(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int								iErr					=	-1;
	 COMMON_PARAM					*	pCommonParam			=	(  COMMON_PARAM  *  )p0;
	 QY_W_MON						*	pQwm					=	(  QY_W_MON  *  )pCommonParam->p0;
	 QWM_WINDOWSUPDATEPOLICY_PROP		policyInfo;
	 DWORD								dwVal;
	 //  char								buf[256];
	 //  DWORD								cb;

	 if  (  !g_bIsWinNT  ||  pQwm->env.iPlatformId  ==  CONST_qyPlatform_winnt  )  return  -1;

	 traceLogA(  "showPcWindowsUpdatePolicy enters"  );
	 
	 memset(  &policyInfo,  0,  sizeof(  policyInfo  )  );
	 policyInfo.uiType  =  CONST_pcCommType_windowsUpdatePolicy;
	 policyInfo.uiSize  =  sizeof(  policyInfo  );
	 policyInfo.iPlatformId  =  pQwm->env.iPlatformId;
	 policyInfo.uiLangId  =  pQwm->env.usLangId;

#define		CONST_qyRootKey_wsus						"SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate"
#define		CONST_qyRootKey_au							"SOFTWARE\\Policies\\Microsoft\\Windows\\WindowsUpdate\\AU"
#define		CONST_qyRootKey_autoUpdate					"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\WindowsUpdate\\Auto Update"
	#define		CONST_regValName_auOptions						"AUOptions"
	#define		CONST_regValName_rescheduleWaitTime				"RescheduleWaitTime"
	#define		CONST_regValName_rescheduleWaitTimeEnabled		"RescheduleWaitTimeEnabled"
	#define		CONST_regValName_noAutoRebootWithLoggedOnUsers	"NoAutoRebootWithLoggedOnUsers"
	#define		CONST_regValName_noAutoUpdate					"NoAutoUpdate"
	#define		CONST_regValName_aUOptions						"AUOptions"
	#define		CONST_regValName_scheduledInstallDay			"ScheduledInstallDay"
	#define		CONST_regValName_scheduledInstallTime			"ScheduledInstallTime"
	#define		CONST_regValName_detectionFrequencyEnabled		"DetectionFrequencyEnabled"
	#define		CONST_regValName_detectionFrequency				"DetectionFrequency"
	#define		CONST_regValName_useWUServer					"UseWUServer"
	//
	#define		CONST_regValName_wUServer						"WUServer"
	#define		CONST_regValName_wUStatusServer					"WUStatusServer"
	#define		CONST_regValName_elevateNonAdmins				"ElevateNonAdmins"
	#define		CONST_regValName_targetGroupEnabled				"TargetGroupEnabled"
	#define		CONST_regValName_targetGroup					"TargetGroup"
	
	 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_au  ),  _T(  CONST_regValName_auOptions  ),  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  CONST_dwRegVal_invalid;
	 policyInfo.AUOptions  =  dwVal;
	 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_au  ),  _T(  CONST_regValName_rescheduleWaitTime  ),  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  CONST_dwRegVal_invalid;
	 policyInfo.RescheduleWaitTime  =  dwVal;
	 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_au  ),  _T(  CONST_regValName_rescheduleWaitTimeEnabled  ),  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  CONST_dwRegVal_invalid;
	 policyInfo.RescheduleWaitTimeEnabled  =  dwVal;
	 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_au  ),  _T(  CONST_regValName_noAutoRebootWithLoggedOnUsers  ),  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  CONST_dwRegVal_invalid;
	 policyInfo.NoAutoRebootWithLoggedOnUsers  =  dwVal;
	 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_au  ),  _T(  CONST_regValName_noAutoUpdate  ),  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  CONST_dwRegVal_invalid;
	 policyInfo.NoAutoUpdate  =  dwVal;
	 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_au  ),  _T(  CONST_regValName_scheduledInstallDay  ),  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  CONST_dwRegVal_invalid;
	 policyInfo.ScheduledInstallDay  =  dwVal;
	 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_au  ),  _T(  CONST_regValName_scheduledInstallTime  ),  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  CONST_dwRegVal_invalid;
	 policyInfo.ScheduledInstallTime  =  dwVal;
	 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_au  ),  _T(  CONST_regValName_detectionFrequencyEnabled  ),  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  CONST_dwRegVal_invalid;
	 policyInfo.DetectionFrequencyEnabled  =  dwVal;
	 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_au  ),  _T(  CONST_regValName_detectionFrequency  ),  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  CONST_dwRegVal_invalid;
	 policyInfo.DetectionFrequency  =  dwVal;
	 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_au  ),  _T(  CONST_regValName_useWUServer  ),  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  CONST_dwRegVal_invalid;
	 policyInfo.UseWUServer  =  dwVal;
	 //
	 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_wsus  ),  _T(  CONST_regValName_wUServer  ),  policyInfo.WUServer,  sizeof(  policyInfo.WUServer  )  )  )  policyInfo.WUServer[0]  =  0;
	 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_wsus  ),  _T(  CONST_regValName_wUStatusServer  ),  policyInfo.WUStatusServer,  sizeof(  policyInfo.WUStatusServer  )  )  )  policyInfo.WUStatusServer[0]  =  0;
	 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_wsus  ),  _T(  CONST_regValName_elevateNonAdmins  ),  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  CONST_dwRegVal_invalid;
	 policyInfo.ElevateNonAdmins  =  dwVal;
	 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_wsus  ),  _T(  CONST_regValName_targetGroupEnabled  ),  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  CONST_dwRegVal_invalid;
	 policyInfo.TargetGroupEnabled  =  dwVal;
	 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_wsus  ),  _T(  CONST_regValName_targetGroup  ),  policyInfo.TargetGroup,  sizeof(  policyInfo.TargetGroup  )  )  )  policyInfo.TargetGroup[0]  =  0;
	 
	
	 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_autoUpdate  ),  _T(  CONST_regValName_auOptions  ),  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  CONST_dwRegVal_invalid;
	 policyInfo.AutoUpdate_AUOptions  =  dwVal;
	 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_autoUpdate  ),  _T(  CONST_regValName_scheduledInstallDay  ),  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  CONST_dwRegVal_invalid;
	 policyInfo.AutoUpdate_ScheduledInstallDay  =  dwVal;
	 if  (  qyGetRegCfg(  _T(  CONST_qyRootKey_autoUpdate  ),  _T(  CONST_regValName_scheduledInstallTime  ),  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  CONST_dwRegVal_invalid;
	 policyInfo.AutoUpdate_ScheduledInstallTime  =  dwVal;
		 

	 if  (  tmpHandler_sndPcNetworkProp(  p0,  0,  &policyInfo  )  )  goto  errLabel;
	 
	 iErr  =  0;

errLabel:
	 traceLogA(  "showPcWindowsUpdatePolicy leaves"  );

	 return  iErr;

}

 int  tmpChangeRegDwVal(  QY_REG  *  pReg,  TCHAR  *  pCfgName,  DWORD  dwNewVal  )
{
	 DWORD	dwVal;

 	 if  (  qyGetRegCfg(  pReg->rootKey,  pCfgName,  (  char  *  )&dwVal,  sizeof(  dwVal  )  )  )  dwVal  =  CONST_dwRegVal_invalid;
	 if  (  dwNewVal  !=  dwVal  )  {
		 if  (  dwNewVal  ==  CONST_dwRegVal_invalid  )  qyDelRegCfg(  pReg->rootKey,  pCfgName  );
		 else  {
			   pReg->uiType  =  REG_DWORD;
			   tmpSetRegCfgEx(  pReg,  pCfgName,  (  char  *  )&dwNewVal,  0  );
		 }
	 }

	 return  0;

}

  int  tmpChangeRegStrVal(  QY_REG  *  pReg,  TCHAR  *  pCfgName,  TCHAR  *  str  )
{
	 TCHAR		buf[1024];

	 if  (  !str  )  str  =  _T(  ""  );
	 if  (  qyGetRegCfg(  pReg->rootKey,  pCfgName,  (  char  *  )buf,  sizeof(  buf  )  )  ||  _tcsicmp(  buf,  str  )  )  {
		 qySetRegCfg(  pReg->rootKey,  pCfgName,  str  );
	 }

	 return  0;

}




 int  changeQwmWindowsUpdatePolicy(  	QWM_THREADINFO		*	pSubThreadInfo  )
{
	 int								iErr					=	-1;
	 QY_W_MON						*	pQwm					=	(  QY_W_MON  *  )pSubThreadInfo->pParaentParam;
	 QY_PCNETWORK_PROPU				*	pNewProp				=	(  QY_PCNETWORK_PROPU  *  )&pQwm->cfg.newPcNetworkProp;
	 QY_PCNETWORK_INFOU				*	pCurInfo				=	(  QY_PCNETWORK_INFOU  *  )&pQwm->cfg.curPcNetworkInfo;
	 QY_REG								reg;
	 QWM_WINDOWSUPDATEPOLICY_PROP	*	pPolicy					=	&pNewProp->windowsUpdatePolicy;
	 TCHAR								tBuf[256];


	 traceLogA(  "changeQwmWindowsUpdatePolicy enters"  );

	 memset(  &reg,  0,  sizeof(  reg  )  );
	 
	 safeTcsnCpy(  _T(  CONST_qyRootKey_autoUpdate  ),  reg.rootKey,  mycountof(  reg.rootKey  )  );  
	 //
	 tmpChangeRegDwVal(  &reg,  _T(  CONST_regValName_auOptions  ),  pPolicy->AutoUpdate_AUOptions  );
	 tmpChangeRegDwVal(  &reg,  _T(  CONST_regValName_scheduledInstallDay  ),  pPolicy->AutoUpdate_ScheduledInstallDay  );
	 tmpChangeRegDwVal(  &reg,  _T(  CONST_regValName_scheduledInstallTime  ),  pPolicy->AutoUpdate_ScheduledInstallTime  );

	 safeTcsnCpy(  _T(  CONST_qyRootKey_au  ),  reg.rootKey,  mycountof(  reg.rootKey  )  ); 
	 //
	 tmpChangeRegDwVal(  &reg,  _T(  CONST_regValName_auOptions  ),  pPolicy->AUOptions  );
	 tmpChangeRegDwVal(  &reg,  _T(  CONST_regValName_rescheduleWaitTime  ),  pPolicy->RescheduleWaitTime  );
	 tmpChangeRegDwVal(  &reg,  _T(  CONST_regValName_rescheduleWaitTimeEnabled  ),  pPolicy->RescheduleWaitTimeEnabled  );
	 tmpChangeRegDwVal(  &reg,  _T(  CONST_regValName_noAutoRebootWithLoggedOnUsers  ),  pPolicy->NoAutoRebootWithLoggedOnUsers  );
	 tmpChangeRegDwVal(  &reg,  _T(  CONST_regValName_noAutoUpdate  ),  pPolicy->NoAutoUpdate  );
	 tmpChangeRegDwVal(  &reg,  _T(  CONST_regValName_scheduledInstallDay  ),  pPolicy->ScheduledInstallDay  );
	 tmpChangeRegDwVal(  &reg,  _T(  CONST_regValName_scheduledInstallTime  ),  pPolicy->ScheduledInstallTime  );
	 tmpChangeRegDwVal(  &reg,  _T(  CONST_regValName_detectionFrequencyEnabled  ),  pPolicy->DetectionFrequencyEnabled  );
	 tmpChangeRegDwVal(  &reg,  _T(  CONST_regValName_detectionFrequency  ),  pPolicy->DetectionFrequency  );
	 tmpChangeRegDwVal(  &reg,  _T(  CONST_regValName_useWUServer  ),  pPolicy->UseWUServer  );

	 safeTcsnCpy(  _T(  CONST_qyRootKey_wsus  ),  reg.rootKey,  mycountof(  reg.rootKey  )  );
	 //
	 myUtf82TChar(  pPolicy->WUServer,  tBuf,  mycountof(  tBuf  )  );
	 tmpChangeRegStrVal(  &reg,  _T(  CONST_regValName_wUServer  ),  tBuf  );
	 myUtf82TChar(  pPolicy->WUStatusServer,  tBuf,  mycountof(  tBuf  )  );
	 tmpChangeRegStrVal(  &reg,  _T(  CONST_regValName_wUStatusServer  ),  tBuf  );
	 tmpChangeRegDwVal(  &reg,  _T(  CONST_regValName_elevateNonAdmins   ),  pPolicy->ElevateNonAdmins  );
	 tmpChangeRegDwVal(  &reg,  _T(  CONST_regValName_targetGroupEnabled  ),  pPolicy->TargetGroupEnabled  );
	 myUtf82TChar(  pPolicy->TargetGroup,  tBuf,  mycountof(  tBuf  )  );
	 tmpChangeRegStrVal(  &reg,  _T(  CONST_regValName_targetGroup  ),  tBuf  );
	 
	 iErr  =  0;

	 traceLogA(  "changeQwmWindowsUpdatePolicy leaves"  );

	 return  iErr;
}
