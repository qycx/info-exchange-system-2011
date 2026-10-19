# Microsoft Developer Studio Generated NMAKE File, Based on qyMc.dsp
!IF "$(CFG)" == ""
CFG=qyMc - Win32 Debug
!MESSAGE No configuration specified. Defaulting to qyMc - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "qyMc - Win32 Release" && "$(CFG)" != "qyMc - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "qyMc.mak" CFG="qyMc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "qyMc - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "qyMc - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "qyMc - Win32 Release"

OUTDIR=.\..\..\..\Release\bin
INTDIR=.\..\..\..\o\qyMc\Release
# Begin Custom Macros
OutDir=.\..\..\..\Release\bin
# End Custom Macros

ALL : "$(OUTDIR)\qyMc.exe" "$(OUTDIR)\qyMc.bsc"


CLEAN :
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildFrm.sbr"
	-@erase "$(INTDIR)\DlgAddSwitchToGrp.obj"
	-@erase "$(INTDIR)\DlgAddSwitchToGrp.sbr"
	-@erase "$(INTDIR)\DlgCfgBoard.obj"
	-@erase "$(INTDIR)\DlgCfgBoard.sbr"
	-@erase "$(INTDIR)\DlgCfgCustom.obj"
	-@erase "$(INTDIR)\DlgCfgCustom.sbr"
	-@erase "$(INTDIR)\DlgCfgInterMonIp.obj"
	-@erase "$(INTDIR)\DlgCfgInterMonIp.sbr"
	-@erase "$(INTDIR)\DlgCfgPcProcessRule.obj"
	-@erase "$(INTDIR)\DlgCfgPcProcessRule.sbr"
	-@erase "$(INTDIR)\DlgCfgSwitchDefaultPolicyGrp.obj"
	-@erase "$(INTDIR)\DlgCfgSwitchDefaultPolicyGrp.sbr"
	-@erase "$(INTDIR)\DlgCfgSwitchPolicyGrp.obj"
	-@erase "$(INTDIR)\DlgCfgSwitchPolicyGrp.sbr"
	-@erase "$(INTDIR)\DlgCfgSwitchPolicyGrps.obj"
	-@erase "$(INTDIR)\DlgCfgSwitchPolicyGrps.sbr"
	-@erase "$(INTDIR)\DlgCfgSystemParams.obj"
	-@erase "$(INTDIR)\DlgCfgSystemParams.sbr"
	-@erase "$(INTDIR)\DlgCfgUsr.obj"
	-@erase "$(INTDIR)\DlgCfgUsr.sbr"
	-@erase "$(INTDIR)\DlgCfgUsrs.obj"
	-@erase "$(INTDIR)\DlgCfgUsrs.sbr"
	-@erase "$(INTDIR)\DlgCfgWarn.obj"
	-@erase "$(INTDIR)\DlgCfgWarn.sbr"
	-@erase "$(INTDIR)\DlgCusPcSp.obj"
	-@erase "$(INTDIR)\DlgCusPcSp.sbr"
	-@erase "$(INTDIR)\DlgEditSp.obj"
	-@erase "$(INTDIR)\DlgEditSp.sbr"
	-@erase "$(INTDIR)\DlgEditSwitchInfo.obj"
	-@erase "$(INTDIR)\DlgEditSwitchInfo.sbr"
	-@erase "$(INTDIR)\DlgIp.obj"
	-@erase "$(INTDIR)\DlgIp.sbr"
	-@erase "$(INTDIR)\DlgIpEx.obj"
	-@erase "$(INTDIR)\DlgIpEx.sbr"
	-@erase "$(INTDIR)\DlgMac.obj"
	-@erase "$(INTDIR)\DlgMac.sbr"
	-@erase "$(INTDIR)\DlgMcHint.obj"
	-@erase "$(INTDIR)\DlgMcHint.sbr"
	-@erase "$(INTDIR)\DlgMcLogon.obj"
	-@erase "$(INTDIR)\DlgMcLogon.sbr"
	-@erase "$(INTDIR)\DlgMgrSwitchPolicyGrps.obj"
	-@erase "$(INTDIR)\DlgMgrSwitchPolicyGrps.sbr"
	-@erase "$(INTDIR)\DlgNum.obj"
	-@erase "$(INTDIR)\DlgNum.sbr"
	-@erase "$(INTDIR)\DlgPasswdForStopMon.obj"
	-@erase "$(INTDIR)\DlgPasswdForStopMon.sbr"
	-@erase "$(INTDIR)\DlgPcAssetProperties.obj"
	-@erase "$(INTDIR)\DlgPcAssetProperties.sbr"
	-@erase "$(INTDIR)\DlgPhoneNum.obj"
	-@erase "$(INTDIR)\DlgPhoneNum.sbr"
	-@erase "$(INTDIR)\DlgPropPcComputer.obj"
	-@erase "$(INTDIR)\DlgPropPcComputer.sbr"
	-@erase "$(INTDIR)\DlgPropPcNetwork.obj"
	-@erase "$(INTDIR)\DlgPropPcNetwork.sbr"
	-@erase "$(INTDIR)\DlgPropPcProxyCfg.obj"
	-@erase "$(INTDIR)\DlgPropPcProxyCfg.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgAdvancedOptions.obj"
	-@erase "$(INTDIR)\DlgQnmCfgAdvancedOptions.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgIpGrp.obj"
	-@erase "$(INTDIR)\DlgQnmCfgIpGrp.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgIpScan.obj"
	-@erase "$(INTDIR)\DlgQnmCfgIpScan.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgOptions.obj"
	-@erase "$(INTDIR)\DlgQnmCfgOptions.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgPcComputer.obj"
	-@erase "$(INTDIR)\DlgQnmCfgPcComputer.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgPcGrp.obj"
	-@erase "$(INTDIR)\DlgQnmCfgPcGrp.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgPcGrps.obj"
	-@erase "$(INTDIR)\DlgQnmCfgPcGrps.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgPcNetworkOptions.obj"
	-@erase "$(INTDIR)\DlgQnmCfgPcNetworkOptions.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgPcNetworkRule.obj"
	-@erase "$(INTDIR)\DlgQnmCfgPcNetworkRule.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgPcProxyCfg.obj"
	-@erase "$(INTDIR)\DlgQnmCfgPcProxyCfg.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgPcRule.obj"
	-@erase "$(INTDIR)\DlgQnmCfgPcRule.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgRasOptions.obj"
	-@erase "$(INTDIR)\DlgQnmCfgRasOptions.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgSnmpObjRule.obj"
	-@erase "$(INTDIR)\DlgQnmCfgSnmpObjRule.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgUnchk.obj"
	-@erase "$(INTDIR)\DlgQnmCfgUnchk.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgUnchkedIpGrp.obj"
	-@erase "$(INTDIR)\DlgQnmCfgUnchkedIpGrp.sbr"
	-@erase "$(INTDIR)\DlgQnmEditMacInfo.obj"
	-@erase "$(INTDIR)\DlgQnmEditMacInfo.sbr"
	-@erase "$(INTDIR)\DlgQnmEditPcUsrInfo.obj"
	-@erase "$(INTDIR)\DlgQnmEditPcUsrInfo.sbr"
	-@erase "$(INTDIR)\DlgQnmEventSearch.obj"
	-@erase "$(INTDIR)\DlgQnmEventSearch.sbr"
	-@erase "$(INTDIR)\DlgQnmOtherMacInfo.obj"
	-@erase "$(INTDIR)\DlgQnmOtherMacInfo.sbr"
	-@erase "$(INTDIR)\DlgQnmPcAssetListSearch.obj"
	-@erase "$(INTDIR)\DlgQnmPcAssetListSearch.sbr"
	-@erase "$(INTDIR)\DlgQnmPcListSearch.obj"
	-@erase "$(INTDIR)\DlgQnmPcListSearch.sbr"
	-@erase "$(INTDIR)\DlgQnmPcSpListSearch.obj"
	-@erase "$(INTDIR)\DlgQnmPcSpListSearch.sbr"
	-@erase "$(INTDIR)\DlgQnmSearch.obj"
	-@erase "$(INTDIR)\DlgQnmSearch.sbr"
	-@erase "$(INTDIR)\DlgQnmSendHint.obj"
	-@erase "$(INTDIR)\DlgQnmSendHint.sbr"
	-@erase "$(INTDIR)\DlgQnmSnmpObjPortProperties.obj"
	-@erase "$(INTDIR)\DlgQnmSnmpObjPortProperties.sbr"
	-@erase "$(INTDIR)\DlgQnmSnmpObjProperties.obj"
	-@erase "$(INTDIR)\DlgQnmSnmpObjProperties.sbr"
	-@erase "$(INTDIR)\DlgShhgPcProperties.obj"
	-@erase "$(INTDIR)\DlgShhgPcProperties.sbr"
	-@erase "$(INTDIR)\DlgSpProperties.obj"
	-@erase "$(INTDIR)\DlgSpProperties.sbr"
	-@erase "$(INTDIR)\getObjId.obj"
	-@erase "$(INTDIR)\getObjId.sbr"
	-@erase "$(INTDIR)\HistoryView.obj"
	-@erase "$(INTDIR)\HistoryView.sbr"
	-@erase "$(INTDIR)\InforDlg.obj"
	-@erase "$(INTDIR)\InforDlg.sbr"
	-@erase "$(INTDIR)\InterIpSetup.obj"
	-@erase "$(INTDIR)\InterIpSetup.sbr"
	-@erase "$(INTDIR)\ipdataset.obj"
	-@erase "$(INTDIR)\ipdataset.sbr"
	-@erase "$(INTDIR)\IpInfoDlg.obj"
	-@erase "$(INTDIR)\IpInfoDlg.sbr"
	-@erase "$(INTDIR)\LeftView.obj"
	-@erase "$(INTDIR)\LeftView.sbr"
	-@erase "$(INTDIR)\logquery.obj"
	-@erase "$(INTDIR)\logquery.sbr"
	-@erase "$(INTDIR)\MainClient.obj"
	-@erase "$(INTDIR)\MainClient.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\netAlert.obj"
	-@erase "$(INTDIR)\netAlert.sbr"
	-@erase "$(INTDIR)\PpClearupEventCond.obj"
	-@erase "$(INTDIR)\PpClearupEventCond.sbr"
	-@erase "$(INTDIR)\PpQnmClearup.obj"
	-@erase "$(INTDIR)\PpQnmClearup.sbr"
	-@erase "$(INTDIR)\PpQnmStatGeneral.obj"
	-@erase "$(INTDIR)\PpQnmStatGeneral.sbr"
	-@erase "$(INTDIR)\PpQnmStatIpScan.obj"
	-@erase "$(INTDIR)\PpQnmStatIpScan.sbr"
	-@erase "$(INTDIR)\PpQnmStatOthers.obj"
	-@erase "$(INTDIR)\PpQnmStatOthers.sbr"
	-@erase "$(INTDIR)\PpQnmStatPcInfo.obj"
	-@erase "$(INTDIR)\PpQnmStatPcInfo.sbr"
	-@erase "$(INTDIR)\PpQnmStatUsrInfo.obj"
	-@erase "$(INTDIR)\PpQnmStatUsrInfo.sbr"
	-@erase "$(INTDIR)\PpQyExport.obj"
	-@erase "$(INTDIR)\PpQyExport.sbr"
	-@erase "$(INTDIR)\qmCommonDbFunc.obj"
	-@erase "$(INTDIR)\qmCommonDbFunc.sbr"
	-@erase "$(INTDIR)\qmCommonFunc.obj"
	-@erase "$(INTDIR)\qmCommonFunc.sbr"
	-@erase "$(INTDIR)\qmCommonProc.obj"
	-@erase "$(INTDIR)\qmCommonProc.sbr"
	-@erase "$(INTDIR)\qmSnmpProc.obj"
	-@erase "$(INTDIR)\qmSnmpProc.sbr"
	-@erase "$(INTDIR)\qnmAllHints.obj"
	-@erase "$(INTDIR)\qnmAllHints.sbr"
	-@erase "$(INTDIR)\qnmAssetsTemp.obj"
	-@erase "$(INTDIR)\qnmAssetsTemp.sbr"
	-@erase "$(INTDIR)\qnmChkCommProc.obj"
	-@erase "$(INTDIR)\qnmChkCommProc.sbr"
	-@erase "$(INTDIR)\qnmCommProc.obj"
	-@erase "$(INTDIR)\qnmCommProc.sbr"
	-@erase "$(INTDIR)\qnmCommProc1.obj"
	-@erase "$(INTDIR)\qnmCommProc1.sbr"
	-@erase "$(INTDIR)\qnmCustom.obj"
	-@erase "$(INTDIR)\qnmCustom.sbr"
	-@erase "$(INTDIR)\qnmCustomComm.obj"
	-@erase "$(INTDIR)\qnmCustomComm.sbr"
	-@erase "$(INTDIR)\qnmCustomGui.obj"
	-@erase "$(INTDIR)\qnmCustomGui.sbr"
	-@erase "$(INTDIR)\qnmCustomRegTool.obj"
	-@erase "$(INTDIR)\qnmCustomRegTool.sbr"
	-@erase "$(INTDIR)\qnmCustomSearch.obj"
	-@erase "$(INTDIR)\qnmCustomSearch.sbr"
	-@erase "$(INTDIR)\qnmCustomStat.obj"
	-@erase "$(INTDIR)\qnmCustomStat.sbr"
	-@erase "$(INTDIR)\QnmDb.obj"
	-@erase "$(INTDIR)\QnmDb.sbr"
	-@erase "$(INTDIR)\qnmFwCommProc.obj"
	-@erase "$(INTDIR)\qnmFwCommProc.sbr"
	-@erase "$(INTDIR)\qnmGuiCommProc.obj"
	-@erase "$(INTDIR)\qnmGuiCommProc.sbr"
	-@erase "$(INTDIR)\qnmHotKeys.obj"
	-@erase "$(INTDIR)\qnmHotKeys.sbr"
	-@erase "$(INTDIR)\qnmMainCustom.obj"
	-@erase "$(INTDIR)\qnmMainCustom.sbr"
	-@erase "$(INTDIR)\qnmMainMenuProc.obj"
	-@erase "$(INTDIR)\qnmMainMenuProc.sbr"
	-@erase "$(INTDIR)\qnmMainProc.obj"
	-@erase "$(INTDIR)\qnmMainProc.sbr"
	-@erase "$(INTDIR)\qnmOsAuditCommProc.obj"
	-@erase "$(INTDIR)\qnmOsAuditCommProc.sbr"
	-@erase "$(INTDIR)\qnmsCommProc.obj"
	-@erase "$(INTDIR)\qnmsCommProc.sbr"
	-@erase "$(INTDIR)\qnmSqlScripts.obj"
	-@erase "$(INTDIR)\qnmSqlScripts.sbr"
	-@erase "$(INTDIR)\qnmWarnCommProc.obj"
	-@erase "$(INTDIR)\qnmWarnCommProc.sbr"
	-@erase "$(INTDIR)\qwmAllHints.obj"
	-@erase "$(INTDIR)\qwmAllHints.sbr"
	-@erase "$(INTDIR)\qwmDjCommProc.obj"
	-@erase "$(INTDIR)\qwmDjCommProc.sbr"
	-@erase "$(INTDIR)\qwmNetworkStatusCommProc.obj"
	-@erase "$(INTDIR)\qwmNetworkStatusCommProc.sbr"
	-@erase "$(INTDIR)\QyBrowseView.obj"
	-@erase "$(INTDIR)\QyBrowseView.sbr"
	-@erase "$(INTDIR)\QyBulkset.obj"
	-@erase "$(INTDIR)\QyBulkset.sbr"
	-@erase "$(INTDIR)\QyChildFrm.obj"
	-@erase "$(INTDIR)\QyChildFrm.sbr"
	-@erase "$(INTDIR)\qyCommProc.obj"
	-@erase "$(INTDIR)\qyCommProc.sbr"
	-@erase "$(INTDIR)\qyCustom.obj"
	-@erase "$(INTDIR)\qyCustom.sbr"
	-@erase "$(INTDIR)\QyDialogBar.obj"
	-@erase "$(INTDIR)\QyDialogBar.sbr"
	-@erase "$(INTDIR)\QyFile.obj"
	-@erase "$(INTDIR)\QyFile.sbr"
	-@erase "$(INTDIR)\qyImcLogFunc.obj"
	-@erase "$(INTDIR)\qyImcLogFunc.sbr"
	-@erase "$(INTDIR)\qyImcPublic.obj"
	-@erase "$(INTDIR)\qyImcPublic.sbr"
	-@erase "$(INTDIR)\qyLangCommProc.obj"
	-@erase "$(INTDIR)\qyLangCommProc.sbr"
	-@erase "$(INTDIR)\qyMc.obj"
	-@erase "$(INTDIR)\qyMc.pch"
	-@erase "$(INTDIR)\qyMc.res"
	-@erase "$(INTDIR)\qyMc.sbr"
	-@erase "$(INTDIR)\qyMcAuth.obj"
	-@erase "$(INTDIR)\qyMcAuth.sbr"
	-@erase "$(INTDIR)\qyMcDoc.obj"
	-@erase "$(INTDIR)\qyMcDoc.sbr"
	-@erase "$(INTDIR)\qyMcLogon.obj"
	-@erase "$(INTDIR)\qyMcLogon.sbr"
	-@erase "$(INTDIR)\qyMcMainAssetProc.obj"
	-@erase "$(INTDIR)\qyMcMainAssetProc.sbr"
	-@erase "$(INTDIR)\qyMcMainAssetReport.obj"
	-@erase "$(INTDIR)\qyMcMainAssetReport.sbr"
	-@erase "$(INTDIR)\qyMcMainCfg.obj"
	-@erase "$(INTDIR)\qyMcMainCfg.sbr"
	-@erase "$(INTDIR)\qyMcMainCommon.obj"
	-@erase "$(INTDIR)\qyMcMainCommon.sbr"
	-@erase "$(INTDIR)\qyMcMainCommonObj.obj"
	-@erase "$(INTDIR)\qyMcMainCommonObj.sbr"
	-@erase "$(INTDIR)\qyMcMainDaemon.obj"
	-@erase "$(INTDIR)\qyMcMainDaemon.sbr"
	-@erase "$(INTDIR)\qyMcMainDb.obj"
	-@erase "$(INTDIR)\qyMcMainDb.sbr"
	-@erase "$(INTDIR)\qyMcMainHook.obj"
	-@erase "$(INTDIR)\qyMcMainHook.sbr"
	-@erase "$(INTDIR)\qyMcMainMenu.obj"
	-@erase "$(INTDIR)\qyMcMainMenu.sbr"
	-@erase "$(INTDIR)\qyMcMainObj.obj"
	-@erase "$(INTDIR)\qyMcMainObj.sbr"
	-@erase "$(INTDIR)\qyMcMainProc.obj"
	-@erase "$(INTDIR)\qyMcMainProc.sbr"
	-@erase "$(INTDIR)\qyMcMainProc1.obj"
	-@erase "$(INTDIR)\qyMcMainProc1.sbr"
	-@erase "$(INTDIR)\qyMcMainSpProc.obj"
	-@erase "$(INTDIR)\qyMcMainSpProc.sbr"
	-@erase "$(INTDIR)\qyMcMainTemp.obj"
	-@erase "$(INTDIR)\qyMcMainTemp.sbr"
	-@erase "$(INTDIR)\qyMcMonIf.obj"
	-@erase "$(INTDIR)\qyMcMonIf.sbr"
	-@erase "$(INTDIR)\qyMcProcDjData.obj"
	-@erase "$(INTDIR)\qyMcProcDjData.sbr"
	-@erase "$(INTDIR)\QyMcRootChildFrm.obj"
	-@erase "$(INTDIR)\QyMcRootChildFrm.sbr"
	-@erase "$(INTDIR)\qyMcRootProc.obj"
	-@erase "$(INTDIR)\qyMcRootProc.sbr"
	-@erase "$(INTDIR)\qyMcView.obj"
	-@erase "$(INTDIR)\qyMcView.sbr"
	-@erase "$(INTDIR)\QyPs.obj"
	-@erase "$(INTDIR)\QyPs.sbr"
	-@erase "$(INTDIR)\QyRcdset.obj"
	-@erase "$(INTDIR)\QyRcdset.sbr"
	-@erase "$(INTDIR)\qyTCharCommProc.obj"
	-@erase "$(INTDIR)\qyTCharCommProc.sbr"
	-@erase "$(INTDIR)\QyVirtualListView.obj"
	-@erase "$(INTDIR)\QyVirtualListView.sbr"
	-@erase "$(INTDIR)\Splash.obj"
	-@erase "$(INTDIR)\Splash.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\TestP.obj"
	-@erase "$(INTDIR)\TestP.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\webbrowser2.obj"
	-@erase "$(INTDIR)\webbrowser2.sbr"
	-@erase "$(OUTDIR)\qyMc.bsc"
	-@erase "$(OUTDIR)\qyMc.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qyMc.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\qyMc.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qyMc.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\getObjId.sbr" \
	"$(INTDIR)\netAlert.sbr" \
	"$(INTDIR)\qnmMainCustom.sbr" \
	"$(INTDIR)\qnmMainMenuProc.sbr" \
	"$(INTDIR)\qnmMainProc.sbr" \
	"$(INTDIR)\QyFile.sbr" \
	"$(INTDIR)\qyMcAuth.sbr" \
	"$(INTDIR)\qyMcLogon.sbr" \
	"$(INTDIR)\qyMcMainAssetProc.sbr" \
	"$(INTDIR)\qyMcMainAssetReport.sbr" \
	"$(INTDIR)\qyMcMainCfg.sbr" \
	"$(INTDIR)\qyMcMainCommon.sbr" \
	"$(INTDIR)\qyMcMainCommonObj.sbr" \
	"$(INTDIR)\qyMcMainDaemon.sbr" \
	"$(INTDIR)\qyMcMainDb.sbr" \
	"$(INTDIR)\qyMcMainHook.sbr" \
	"$(INTDIR)\qyMcMainMenu.sbr" \
	"$(INTDIR)\qyMcMainObj.sbr" \
	"$(INTDIR)\qyMcMainProc.sbr" \
	"$(INTDIR)\qyMcMainProc1.sbr" \
	"$(INTDIR)\qyMcMainSpProc.sbr" \
	"$(INTDIR)\qyMcMainTemp.sbr" \
	"$(INTDIR)\qyMcMonIf.sbr" \
	"$(INTDIR)\qyMcProcDjData.sbr" \
	"$(INTDIR)\qyMcRootProc.sbr" \
	"$(INTDIR)\DlgIp.sbr" \
	"$(INTDIR)\qmCommonDbFunc.sbr" \
	"$(INTDIR)\qmCommonFunc.sbr" \
	"$(INTDIR)\qmCommonProc.sbr" \
	"$(INTDIR)\qmSnmpProc.sbr" \
	"$(INTDIR)\QyPs.sbr" \
	"$(INTDIR)\DlgCfgInterMonIp.sbr" \
	"$(INTDIR)\InforDlg.sbr" \
	"$(INTDIR)\InterIpSetup.sbr" \
	"$(INTDIR)\IpInfoDlg.sbr" \
	"$(INTDIR)\logquery.sbr" \
	"$(INTDIR)\ChildFrm.sbr" \
	"$(INTDIR)\DlgAddSwitchToGrp.sbr" \
	"$(INTDIR)\DlgCfgBoard.sbr" \
	"$(INTDIR)\DlgCfgCustom.sbr" \
	"$(INTDIR)\DlgCfgPcProcessRule.sbr" \
	"$(INTDIR)\DlgCfgSwitchDefaultPolicyGrp.sbr" \
	"$(INTDIR)\DlgCfgSwitchPolicyGrp.sbr" \
	"$(INTDIR)\DlgCfgSwitchPolicyGrps.sbr" \
	"$(INTDIR)\DlgCfgSystemParams.sbr" \
	"$(INTDIR)\DlgCfgUsr.sbr" \
	"$(INTDIR)\DlgCfgUsrs.sbr" \
	"$(INTDIR)\DlgCfgWarn.sbr" \
	"$(INTDIR)\DlgCusPcSp.sbr" \
	"$(INTDIR)\DlgEditSp.sbr" \
	"$(INTDIR)\DlgEditSwitchInfo.sbr" \
	"$(INTDIR)\DlgIpEx.sbr" \
	"$(INTDIR)\DlgMac.sbr" \
	"$(INTDIR)\DlgMcHint.sbr" \
	"$(INTDIR)\DlgMcLogon.sbr" \
	"$(INTDIR)\DlgMgrSwitchPolicyGrps.sbr" \
	"$(INTDIR)\DlgNum.sbr" \
	"$(INTDIR)\DlgPasswdForStopMon.sbr" \
	"$(INTDIR)\DlgPcAssetProperties.sbr" \
	"$(INTDIR)\DlgPhoneNum.sbr" \
	"$(INTDIR)\DlgPropPcComputer.sbr" \
	"$(INTDIR)\DlgPropPcNetwork.sbr" \
	"$(INTDIR)\DlgPropPcProxyCfg.sbr" \
	"$(INTDIR)\DlgQnmCfgAdvancedOptions.sbr" \
	"$(INTDIR)\DlgQnmCfgIpGrp.sbr" \
	"$(INTDIR)\DlgQnmCfgIpScan.sbr" \
	"$(INTDIR)\DlgQnmCfgOptions.sbr" \
	"$(INTDIR)\DlgQnmCfgPcComputer.sbr" \
	"$(INTDIR)\DlgQnmCfgPcGrp.sbr" \
	"$(INTDIR)\DlgQnmCfgPcGrps.sbr" \
	"$(INTDIR)\DlgQnmCfgPcNetworkOptions.sbr" \
	"$(INTDIR)\DlgQnmCfgPcNetworkRule.sbr" \
	"$(INTDIR)\DlgQnmCfgPcProxyCfg.sbr" \
	"$(INTDIR)\DlgQnmCfgPcRule.sbr" \
	"$(INTDIR)\DlgQnmCfgRasOptions.sbr" \
	"$(INTDIR)\DlgQnmCfgSnmpObjRule.sbr" \
	"$(INTDIR)\DlgQnmCfgUnchk.sbr" \
	"$(INTDIR)\DlgQnmCfgUnchkedIpGrp.sbr" \
	"$(INTDIR)\DlgQnmEditMacInfo.sbr" \
	"$(INTDIR)\DlgQnmEditPcUsrInfo.sbr" \
	"$(INTDIR)\DlgQnmEventSearch.sbr" \
	"$(INTDIR)\DlgQnmOtherMacInfo.sbr" \
	"$(INTDIR)\DlgQnmPcAssetListSearch.sbr" \
	"$(INTDIR)\DlgQnmPcListSearch.sbr" \
	"$(INTDIR)\DlgQnmPcSpListSearch.sbr" \
	"$(INTDIR)\DlgQnmSearch.sbr" \
	"$(INTDIR)\DlgQnmSendHint.sbr" \
	"$(INTDIR)\DlgQnmSnmpObjPortProperties.sbr" \
	"$(INTDIR)\DlgQnmSnmpObjProperties.sbr" \
	"$(INTDIR)\DlgShhgPcProperties.sbr" \
	"$(INTDIR)\DlgSpProperties.sbr" \
	"$(INTDIR)\HistoryView.sbr" \
	"$(INTDIR)\ipdataset.sbr" \
	"$(INTDIR)\LeftView.sbr" \
	"$(INTDIR)\MainClient.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\PpClearupEventCond.sbr" \
	"$(INTDIR)\PpQnmClearup.sbr" \
	"$(INTDIR)\PpQnmStatGeneral.sbr" \
	"$(INTDIR)\PpQnmStatIpScan.sbr" \
	"$(INTDIR)\PpQnmStatOthers.sbr" \
	"$(INTDIR)\PpQnmStatPcInfo.sbr" \
	"$(INTDIR)\PpQnmStatUsrInfo.sbr" \
	"$(INTDIR)\PpQyExport.sbr" \
	"$(INTDIR)\QyBrowseView.sbr" \
	"$(INTDIR)\QyBulkset.sbr" \
	"$(INTDIR)\QyChildFrm.sbr" \
	"$(INTDIR)\QyDialogBar.sbr" \
	"$(INTDIR)\qyMc.sbr" \
	"$(INTDIR)\qyMcDoc.sbr" \
	"$(INTDIR)\QyMcRootChildFrm.sbr" \
	"$(INTDIR)\qyMcView.sbr" \
	"$(INTDIR)\QyRcdset.sbr" \
	"$(INTDIR)\QyVirtualListView.sbr" \
	"$(INTDIR)\Splash.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\TestP.sbr" \
	"$(INTDIR)\webbrowser2.sbr" \
	"$(INTDIR)\qnmAssetsTemp.sbr" \
	"$(INTDIR)\qnmChkCommProc.sbr" \
	"$(INTDIR)\qnmCommProc.sbr" \
	"$(INTDIR)\qnmCommProc1.sbr" \
	"$(INTDIR)\QnmDb.sbr" \
	"$(INTDIR)\qnmFwCommProc.sbr" \
	"$(INTDIR)\qnmGuiCommProc.sbr" \
	"$(INTDIR)\qnmHotKeys.sbr" \
	"$(INTDIR)\qnmOsAuditCommProc.sbr" \
	"$(INTDIR)\qnmsCommProc.sbr" \
	"$(INTDIR)\qnmSqlScripts.sbr" \
	"$(INTDIR)\qnmWarnCommProc.sbr" \
	"$(INTDIR)\qwmDjCommProc.sbr" \
	"$(INTDIR)\qwmNetworkStatusCommProc.sbr" \
	"$(INTDIR)\qyCommProc.sbr" \
	"$(INTDIR)\qyImcLogFunc.sbr" \
	"$(INTDIR)\qyImcPublic.sbr" \
	"$(INTDIR)\qyLangCommProc.sbr" \
	"$(INTDIR)\qyTCharCommProc.sbr" \
	"$(INTDIR)\qnmAllHints.sbr" \
	"$(INTDIR)\qnmCustom.sbr" \
	"$(INTDIR)\qnmCustomComm.sbr" \
	"$(INTDIR)\qnmCustomGui.sbr" \
	"$(INTDIR)\qnmCustomRegTool.sbr" \
	"$(INTDIR)\qnmCustomSearch.sbr" \
	"$(INTDIR)\qnmCustomStat.sbr" \
	"$(INTDIR)\qwmAllHints.sbr" \
	"$(INTDIR)\qyCustom.sbr"

"$(OUTDIR)\qyMc.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=netapi32.lib qyPublic.lib qyEncLib.lib htmlhelp.lib Spromeps.lib qyLicense.lib libDes.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\qyMc.pdb" /machine:I386 /out:"$(OUTDIR)\qyMc.exe" /libpath:"..\..\..\Release\lib" 
LINK32_OBJS= \
	"$(INTDIR)\getObjId.obj" \
	"$(INTDIR)\netAlert.obj" \
	"$(INTDIR)\qnmMainCustom.obj" \
	"$(INTDIR)\qnmMainMenuProc.obj" \
	"$(INTDIR)\qnmMainProc.obj" \
	"$(INTDIR)\QyFile.obj" \
	"$(INTDIR)\qyMcAuth.obj" \
	"$(INTDIR)\qyMcLogon.obj" \
	"$(INTDIR)\qyMcMainAssetProc.obj" \
	"$(INTDIR)\qyMcMainAssetReport.obj" \
	"$(INTDIR)\qyMcMainCfg.obj" \
	"$(INTDIR)\qyMcMainCommon.obj" \
	"$(INTDIR)\qyMcMainCommonObj.obj" \
	"$(INTDIR)\qyMcMainDaemon.obj" \
	"$(INTDIR)\qyMcMainDb.obj" \
	"$(INTDIR)\qyMcMainHook.obj" \
	"$(INTDIR)\qyMcMainMenu.obj" \
	"$(INTDIR)\qyMcMainObj.obj" \
	"$(INTDIR)\qyMcMainProc.obj" \
	"$(INTDIR)\qyMcMainProc1.obj" \
	"$(INTDIR)\qyMcMainSpProc.obj" \
	"$(INTDIR)\qyMcMainTemp.obj" \
	"$(INTDIR)\qyMcMonIf.obj" \
	"$(INTDIR)\qyMcProcDjData.obj" \
	"$(INTDIR)\qyMcRootProc.obj" \
	"$(INTDIR)\DlgIp.obj" \
	"$(INTDIR)\qmCommonDbFunc.obj" \
	"$(INTDIR)\qmCommonFunc.obj" \
	"$(INTDIR)\qmCommonProc.obj" \
	"$(INTDIR)\qmSnmpProc.obj" \
	"$(INTDIR)\QyPs.obj" \
	"$(INTDIR)\DlgCfgInterMonIp.obj" \
	"$(INTDIR)\InforDlg.obj" \
	"$(INTDIR)\InterIpSetup.obj" \
	"$(INTDIR)\IpInfoDlg.obj" \
	"$(INTDIR)\logquery.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\DlgAddSwitchToGrp.obj" \
	"$(INTDIR)\DlgCfgBoard.obj" \
	"$(INTDIR)\DlgCfgCustom.obj" \
	"$(INTDIR)\DlgCfgPcProcessRule.obj" \
	"$(INTDIR)\DlgCfgSwitchDefaultPolicyGrp.obj" \
	"$(INTDIR)\DlgCfgSwitchPolicyGrp.obj" \
	"$(INTDIR)\DlgCfgSwitchPolicyGrps.obj" \
	"$(INTDIR)\DlgCfgSystemParams.obj" \
	"$(INTDIR)\DlgCfgUsr.obj" \
	"$(INTDIR)\DlgCfgUsrs.obj" \
	"$(INTDIR)\DlgCfgWarn.obj" \
	"$(INTDIR)\DlgCusPcSp.obj" \
	"$(INTDIR)\DlgEditSp.obj" \
	"$(INTDIR)\DlgEditSwitchInfo.obj" \
	"$(INTDIR)\DlgIpEx.obj" \
	"$(INTDIR)\DlgMac.obj" \
	"$(INTDIR)\DlgMcHint.obj" \
	"$(INTDIR)\DlgMcLogon.obj" \
	"$(INTDIR)\DlgMgrSwitchPolicyGrps.obj" \
	"$(INTDIR)\DlgNum.obj" \
	"$(INTDIR)\DlgPasswdForStopMon.obj" \
	"$(INTDIR)\DlgPcAssetProperties.obj" \
	"$(INTDIR)\DlgPhoneNum.obj" \
	"$(INTDIR)\DlgPropPcComputer.obj" \
	"$(INTDIR)\DlgPropPcNetwork.obj" \
	"$(INTDIR)\DlgPropPcProxyCfg.obj" \
	"$(INTDIR)\DlgQnmCfgAdvancedOptions.obj" \
	"$(INTDIR)\DlgQnmCfgIpGrp.obj" \
	"$(INTDIR)\DlgQnmCfgIpScan.obj" \
	"$(INTDIR)\DlgQnmCfgOptions.obj" \
	"$(INTDIR)\DlgQnmCfgPcComputer.obj" \
	"$(INTDIR)\DlgQnmCfgPcGrp.obj" \
	"$(INTDIR)\DlgQnmCfgPcGrps.obj" \
	"$(INTDIR)\DlgQnmCfgPcNetworkOptions.obj" \
	"$(INTDIR)\DlgQnmCfgPcNetworkRule.obj" \
	"$(INTDIR)\DlgQnmCfgPcProxyCfg.obj" \
	"$(INTDIR)\DlgQnmCfgPcRule.obj" \
	"$(INTDIR)\DlgQnmCfgRasOptions.obj" \
	"$(INTDIR)\DlgQnmCfgSnmpObjRule.obj" \
	"$(INTDIR)\DlgQnmCfgUnchk.obj" \
	"$(INTDIR)\DlgQnmCfgUnchkedIpGrp.obj" \
	"$(INTDIR)\DlgQnmEditMacInfo.obj" \
	"$(INTDIR)\DlgQnmEditPcUsrInfo.obj" \
	"$(INTDIR)\DlgQnmEventSearch.obj" \
	"$(INTDIR)\DlgQnmOtherMacInfo.obj" \
	"$(INTDIR)\DlgQnmPcAssetListSearch.obj" \
	"$(INTDIR)\DlgQnmPcListSearch.obj" \
	"$(INTDIR)\DlgQnmPcSpListSearch.obj" \
	"$(INTDIR)\DlgQnmSearch.obj" \
	"$(INTDIR)\DlgQnmSendHint.obj" \
	"$(INTDIR)\DlgQnmSnmpObjPortProperties.obj" \
	"$(INTDIR)\DlgQnmSnmpObjProperties.obj" \
	"$(INTDIR)\DlgShhgPcProperties.obj" \
	"$(INTDIR)\DlgSpProperties.obj" \
	"$(INTDIR)\HistoryView.obj" \
	"$(INTDIR)\ipdataset.obj" \
	"$(INTDIR)\LeftView.obj" \
	"$(INTDIR)\MainClient.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\PpClearupEventCond.obj" \
	"$(INTDIR)\PpQnmClearup.obj" \
	"$(INTDIR)\PpQnmStatGeneral.obj" \
	"$(INTDIR)\PpQnmStatIpScan.obj" \
	"$(INTDIR)\PpQnmStatOthers.obj" \
	"$(INTDIR)\PpQnmStatPcInfo.obj" \
	"$(INTDIR)\PpQnmStatUsrInfo.obj" \
	"$(INTDIR)\PpQyExport.obj" \
	"$(INTDIR)\QyBrowseView.obj" \
	"$(INTDIR)\QyBulkset.obj" \
	"$(INTDIR)\QyChildFrm.obj" \
	"$(INTDIR)\QyDialogBar.obj" \
	"$(INTDIR)\qyMc.obj" \
	"$(INTDIR)\qyMcDoc.obj" \
	"$(INTDIR)\QyMcRootChildFrm.obj" \
	"$(INTDIR)\qyMcView.obj" \
	"$(INTDIR)\QyRcdset.obj" \
	"$(INTDIR)\QyVirtualListView.obj" \
	"$(INTDIR)\Splash.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TestP.obj" \
	"$(INTDIR)\webbrowser2.obj" \
	"$(INTDIR)\qnmAssetsTemp.obj" \
	"$(INTDIR)\qnmChkCommProc.obj" \
	"$(INTDIR)\qnmCommProc.obj" \
	"$(INTDIR)\qnmCommProc1.obj" \
	"$(INTDIR)\QnmDb.obj" \
	"$(INTDIR)\qnmFwCommProc.obj" \
	"$(INTDIR)\qnmGuiCommProc.obj" \
	"$(INTDIR)\qnmHotKeys.obj" \
	"$(INTDIR)\qnmOsAuditCommProc.obj" \
	"$(INTDIR)\qnmsCommProc.obj" \
	"$(INTDIR)\qnmSqlScripts.obj" \
	"$(INTDIR)\qnmWarnCommProc.obj" \
	"$(INTDIR)\qwmDjCommProc.obj" \
	"$(INTDIR)\qwmNetworkStatusCommProc.obj" \
	"$(INTDIR)\qyCommProc.obj" \
	"$(INTDIR)\qyImcLogFunc.obj" \
	"$(INTDIR)\qyImcPublic.obj" \
	"$(INTDIR)\qyLangCommProc.obj" \
	"$(INTDIR)\qyTCharCommProc.obj" \
	"$(INTDIR)\qnmAllHints.obj" \
	"$(INTDIR)\qnmCustom.obj" \
	"$(INTDIR)\qnmCustomComm.obj" \
	"$(INTDIR)\qnmCustomGui.obj" \
	"$(INTDIR)\qnmCustomRegTool.obj" \
	"$(INTDIR)\qnmCustomSearch.obj" \
	"$(INTDIR)\qnmCustomStat.obj" \
	"$(INTDIR)\qwmAllHints.obj" \
	"$(INTDIR)\qyCustom.obj" \
	"$(INTDIR)\qyMc.res"

"$(OUTDIR)\qyMc.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

OUTDIR=.\..\..\..\Debug\bin
INTDIR=.\..\..\..\o\qyMc\Debug
# Begin Custom Macros
OutDir=.\..\..\..\Debug\bin
# End Custom Macros

ALL : "$(OUTDIR)\qyMc.exe" "$(OUTDIR)\qyMc.bsc"


CLEAN :
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildFrm.sbr"
	-@erase "$(INTDIR)\DlgAddSwitchToGrp.obj"
	-@erase "$(INTDIR)\DlgAddSwitchToGrp.sbr"
	-@erase "$(INTDIR)\DlgCfgBoard.obj"
	-@erase "$(INTDIR)\DlgCfgBoard.sbr"
	-@erase "$(INTDIR)\DlgCfgCustom.obj"
	-@erase "$(INTDIR)\DlgCfgCustom.sbr"
	-@erase "$(INTDIR)\DlgCfgInterMonIp.obj"
	-@erase "$(INTDIR)\DlgCfgInterMonIp.sbr"
	-@erase "$(INTDIR)\DlgCfgPcProcessRule.obj"
	-@erase "$(INTDIR)\DlgCfgPcProcessRule.sbr"
	-@erase "$(INTDIR)\DlgCfgSwitchDefaultPolicyGrp.obj"
	-@erase "$(INTDIR)\DlgCfgSwitchDefaultPolicyGrp.sbr"
	-@erase "$(INTDIR)\DlgCfgSwitchPolicyGrp.obj"
	-@erase "$(INTDIR)\DlgCfgSwitchPolicyGrp.sbr"
	-@erase "$(INTDIR)\DlgCfgSwitchPolicyGrps.obj"
	-@erase "$(INTDIR)\DlgCfgSwitchPolicyGrps.sbr"
	-@erase "$(INTDIR)\DlgCfgSystemParams.obj"
	-@erase "$(INTDIR)\DlgCfgSystemParams.sbr"
	-@erase "$(INTDIR)\DlgCfgUsr.obj"
	-@erase "$(INTDIR)\DlgCfgUsr.sbr"
	-@erase "$(INTDIR)\DlgCfgUsrs.obj"
	-@erase "$(INTDIR)\DlgCfgUsrs.sbr"
	-@erase "$(INTDIR)\DlgCfgWarn.obj"
	-@erase "$(INTDIR)\DlgCfgWarn.sbr"
	-@erase "$(INTDIR)\DlgCusPcSp.obj"
	-@erase "$(INTDIR)\DlgCusPcSp.sbr"
	-@erase "$(INTDIR)\DlgEditSp.obj"
	-@erase "$(INTDIR)\DlgEditSp.sbr"
	-@erase "$(INTDIR)\DlgEditSwitchInfo.obj"
	-@erase "$(INTDIR)\DlgEditSwitchInfo.sbr"
	-@erase "$(INTDIR)\DlgIp.obj"
	-@erase "$(INTDIR)\DlgIp.sbr"
	-@erase "$(INTDIR)\DlgIpEx.obj"
	-@erase "$(INTDIR)\DlgIpEx.sbr"
	-@erase "$(INTDIR)\DlgMac.obj"
	-@erase "$(INTDIR)\DlgMac.sbr"
	-@erase "$(INTDIR)\DlgMcHint.obj"
	-@erase "$(INTDIR)\DlgMcHint.sbr"
	-@erase "$(INTDIR)\DlgMcLogon.obj"
	-@erase "$(INTDIR)\DlgMcLogon.sbr"
	-@erase "$(INTDIR)\DlgMgrSwitchPolicyGrps.obj"
	-@erase "$(INTDIR)\DlgMgrSwitchPolicyGrps.sbr"
	-@erase "$(INTDIR)\DlgNum.obj"
	-@erase "$(INTDIR)\DlgNum.sbr"
	-@erase "$(INTDIR)\DlgPasswdForStopMon.obj"
	-@erase "$(INTDIR)\DlgPasswdForStopMon.sbr"
	-@erase "$(INTDIR)\DlgPcAssetProperties.obj"
	-@erase "$(INTDIR)\DlgPcAssetProperties.sbr"
	-@erase "$(INTDIR)\DlgPhoneNum.obj"
	-@erase "$(INTDIR)\DlgPhoneNum.sbr"
	-@erase "$(INTDIR)\DlgPropPcComputer.obj"
	-@erase "$(INTDIR)\DlgPropPcComputer.sbr"
	-@erase "$(INTDIR)\DlgPropPcNetwork.obj"
	-@erase "$(INTDIR)\DlgPropPcNetwork.sbr"
	-@erase "$(INTDIR)\DlgPropPcProxyCfg.obj"
	-@erase "$(INTDIR)\DlgPropPcProxyCfg.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgAdvancedOptions.obj"
	-@erase "$(INTDIR)\DlgQnmCfgAdvancedOptions.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgIpGrp.obj"
	-@erase "$(INTDIR)\DlgQnmCfgIpGrp.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgIpScan.obj"
	-@erase "$(INTDIR)\DlgQnmCfgIpScan.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgOptions.obj"
	-@erase "$(INTDIR)\DlgQnmCfgOptions.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgPcComputer.obj"
	-@erase "$(INTDIR)\DlgQnmCfgPcComputer.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgPcGrp.obj"
	-@erase "$(INTDIR)\DlgQnmCfgPcGrp.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgPcGrps.obj"
	-@erase "$(INTDIR)\DlgQnmCfgPcGrps.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgPcNetworkOptions.obj"
	-@erase "$(INTDIR)\DlgQnmCfgPcNetworkOptions.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgPcNetworkRule.obj"
	-@erase "$(INTDIR)\DlgQnmCfgPcNetworkRule.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgPcProxyCfg.obj"
	-@erase "$(INTDIR)\DlgQnmCfgPcProxyCfg.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgPcRule.obj"
	-@erase "$(INTDIR)\DlgQnmCfgPcRule.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgRasOptions.obj"
	-@erase "$(INTDIR)\DlgQnmCfgRasOptions.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgSnmpObjRule.obj"
	-@erase "$(INTDIR)\DlgQnmCfgSnmpObjRule.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgUnchk.obj"
	-@erase "$(INTDIR)\DlgQnmCfgUnchk.sbr"
	-@erase "$(INTDIR)\DlgQnmCfgUnchkedIpGrp.obj"
	-@erase "$(INTDIR)\DlgQnmCfgUnchkedIpGrp.sbr"
	-@erase "$(INTDIR)\DlgQnmEditMacInfo.obj"
	-@erase "$(INTDIR)\DlgQnmEditMacInfo.sbr"
	-@erase "$(INTDIR)\DlgQnmEditPcUsrInfo.obj"
	-@erase "$(INTDIR)\DlgQnmEditPcUsrInfo.sbr"
	-@erase "$(INTDIR)\DlgQnmEventSearch.obj"
	-@erase "$(INTDIR)\DlgQnmEventSearch.sbr"
	-@erase "$(INTDIR)\DlgQnmOtherMacInfo.obj"
	-@erase "$(INTDIR)\DlgQnmOtherMacInfo.sbr"
	-@erase "$(INTDIR)\DlgQnmPcAssetListSearch.obj"
	-@erase "$(INTDIR)\DlgQnmPcAssetListSearch.sbr"
	-@erase "$(INTDIR)\DlgQnmPcListSearch.obj"
	-@erase "$(INTDIR)\DlgQnmPcListSearch.sbr"
	-@erase "$(INTDIR)\DlgQnmPcSpListSearch.obj"
	-@erase "$(INTDIR)\DlgQnmPcSpListSearch.sbr"
	-@erase "$(INTDIR)\DlgQnmSearch.obj"
	-@erase "$(INTDIR)\DlgQnmSearch.sbr"
	-@erase "$(INTDIR)\DlgQnmSendHint.obj"
	-@erase "$(INTDIR)\DlgQnmSendHint.sbr"
	-@erase "$(INTDIR)\DlgQnmSnmpObjPortProperties.obj"
	-@erase "$(INTDIR)\DlgQnmSnmpObjPortProperties.sbr"
	-@erase "$(INTDIR)\DlgQnmSnmpObjProperties.obj"
	-@erase "$(INTDIR)\DlgQnmSnmpObjProperties.sbr"
	-@erase "$(INTDIR)\DlgShhgPcProperties.obj"
	-@erase "$(INTDIR)\DlgShhgPcProperties.sbr"
	-@erase "$(INTDIR)\DlgSpProperties.obj"
	-@erase "$(INTDIR)\DlgSpProperties.sbr"
	-@erase "$(INTDIR)\getObjId.obj"
	-@erase "$(INTDIR)\getObjId.sbr"
	-@erase "$(INTDIR)\HistoryView.obj"
	-@erase "$(INTDIR)\HistoryView.sbr"
	-@erase "$(INTDIR)\InforDlg.obj"
	-@erase "$(INTDIR)\InforDlg.sbr"
	-@erase "$(INTDIR)\InterIpSetup.obj"
	-@erase "$(INTDIR)\InterIpSetup.sbr"
	-@erase "$(INTDIR)\ipdataset.obj"
	-@erase "$(INTDIR)\ipdataset.sbr"
	-@erase "$(INTDIR)\IpInfoDlg.obj"
	-@erase "$(INTDIR)\IpInfoDlg.sbr"
	-@erase "$(INTDIR)\LeftView.obj"
	-@erase "$(INTDIR)\LeftView.sbr"
	-@erase "$(INTDIR)\logquery.obj"
	-@erase "$(INTDIR)\logquery.sbr"
	-@erase "$(INTDIR)\MainClient.obj"
	-@erase "$(INTDIR)\MainClient.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\netAlert.obj"
	-@erase "$(INTDIR)\netAlert.sbr"
	-@erase "$(INTDIR)\PpClearupEventCond.obj"
	-@erase "$(INTDIR)\PpClearupEventCond.sbr"
	-@erase "$(INTDIR)\PpQnmClearup.obj"
	-@erase "$(INTDIR)\PpQnmClearup.sbr"
	-@erase "$(INTDIR)\PpQnmStatGeneral.obj"
	-@erase "$(INTDIR)\PpQnmStatGeneral.sbr"
	-@erase "$(INTDIR)\PpQnmStatIpScan.obj"
	-@erase "$(INTDIR)\PpQnmStatIpScan.sbr"
	-@erase "$(INTDIR)\PpQnmStatOthers.obj"
	-@erase "$(INTDIR)\PpQnmStatOthers.sbr"
	-@erase "$(INTDIR)\PpQnmStatPcInfo.obj"
	-@erase "$(INTDIR)\PpQnmStatPcInfo.sbr"
	-@erase "$(INTDIR)\PpQnmStatUsrInfo.obj"
	-@erase "$(INTDIR)\PpQnmStatUsrInfo.sbr"
	-@erase "$(INTDIR)\PpQyExport.obj"
	-@erase "$(INTDIR)\PpQyExport.sbr"
	-@erase "$(INTDIR)\qmCommonDbFunc.obj"
	-@erase "$(INTDIR)\qmCommonDbFunc.sbr"
	-@erase "$(INTDIR)\qmCommonFunc.obj"
	-@erase "$(INTDIR)\qmCommonFunc.sbr"
	-@erase "$(INTDIR)\qmCommonProc.obj"
	-@erase "$(INTDIR)\qmCommonProc.sbr"
	-@erase "$(INTDIR)\qmSnmpProc.obj"
	-@erase "$(INTDIR)\qmSnmpProc.sbr"
	-@erase "$(INTDIR)\qnmAllHints.obj"
	-@erase "$(INTDIR)\qnmAllHints.sbr"
	-@erase "$(INTDIR)\qnmAssetsTemp.obj"
	-@erase "$(INTDIR)\qnmAssetsTemp.sbr"
	-@erase "$(INTDIR)\qnmChkCommProc.obj"
	-@erase "$(INTDIR)\qnmChkCommProc.sbr"
	-@erase "$(INTDIR)\qnmCommProc.obj"
	-@erase "$(INTDIR)\qnmCommProc.sbr"
	-@erase "$(INTDIR)\qnmCommProc1.obj"
	-@erase "$(INTDIR)\qnmCommProc1.sbr"
	-@erase "$(INTDIR)\qnmCustom.obj"
	-@erase "$(INTDIR)\qnmCustom.sbr"
	-@erase "$(INTDIR)\qnmCustomComm.obj"
	-@erase "$(INTDIR)\qnmCustomComm.sbr"
	-@erase "$(INTDIR)\qnmCustomGui.obj"
	-@erase "$(INTDIR)\qnmCustomGui.sbr"
	-@erase "$(INTDIR)\qnmCustomRegTool.obj"
	-@erase "$(INTDIR)\qnmCustomRegTool.sbr"
	-@erase "$(INTDIR)\qnmCustomSearch.obj"
	-@erase "$(INTDIR)\qnmCustomSearch.sbr"
	-@erase "$(INTDIR)\qnmCustomStat.obj"
	-@erase "$(INTDIR)\qnmCustomStat.sbr"
	-@erase "$(INTDIR)\QnmDb.obj"
	-@erase "$(INTDIR)\QnmDb.sbr"
	-@erase "$(INTDIR)\qnmFwCommProc.obj"
	-@erase "$(INTDIR)\qnmFwCommProc.sbr"
	-@erase "$(INTDIR)\qnmGuiCommProc.obj"
	-@erase "$(INTDIR)\qnmGuiCommProc.sbr"
	-@erase "$(INTDIR)\qnmHotKeys.obj"
	-@erase "$(INTDIR)\qnmHotKeys.sbr"
	-@erase "$(INTDIR)\qnmMainCustom.obj"
	-@erase "$(INTDIR)\qnmMainCustom.sbr"
	-@erase "$(INTDIR)\qnmMainMenuProc.obj"
	-@erase "$(INTDIR)\qnmMainMenuProc.sbr"
	-@erase "$(INTDIR)\qnmMainProc.obj"
	-@erase "$(INTDIR)\qnmMainProc.sbr"
	-@erase "$(INTDIR)\qnmOsAuditCommProc.obj"
	-@erase "$(INTDIR)\qnmOsAuditCommProc.sbr"
	-@erase "$(INTDIR)\qnmsCommProc.obj"
	-@erase "$(INTDIR)\qnmsCommProc.sbr"
	-@erase "$(INTDIR)\qnmSqlScripts.obj"
	-@erase "$(INTDIR)\qnmSqlScripts.sbr"
	-@erase "$(INTDIR)\qnmWarnCommProc.obj"
	-@erase "$(INTDIR)\qnmWarnCommProc.sbr"
	-@erase "$(INTDIR)\qwmAllHints.obj"
	-@erase "$(INTDIR)\qwmAllHints.sbr"
	-@erase "$(INTDIR)\qwmDjCommProc.obj"
	-@erase "$(INTDIR)\qwmDjCommProc.sbr"
	-@erase "$(INTDIR)\qwmNetworkStatusCommProc.obj"
	-@erase "$(INTDIR)\qwmNetworkStatusCommProc.sbr"
	-@erase "$(INTDIR)\QyBrowseView.obj"
	-@erase "$(INTDIR)\QyBrowseView.sbr"
	-@erase "$(INTDIR)\QyBulkset.obj"
	-@erase "$(INTDIR)\QyBulkset.sbr"
	-@erase "$(INTDIR)\QyChildFrm.obj"
	-@erase "$(INTDIR)\QyChildFrm.sbr"
	-@erase "$(INTDIR)\qyCommProc.obj"
	-@erase "$(INTDIR)\qyCommProc.sbr"
	-@erase "$(INTDIR)\qyCustom.obj"
	-@erase "$(INTDIR)\qyCustom.sbr"
	-@erase "$(INTDIR)\QyDialogBar.obj"
	-@erase "$(INTDIR)\QyDialogBar.sbr"
	-@erase "$(INTDIR)\QyFile.obj"
	-@erase "$(INTDIR)\QyFile.sbr"
	-@erase "$(INTDIR)\qyImcLogFunc.obj"
	-@erase "$(INTDIR)\qyImcLogFunc.sbr"
	-@erase "$(INTDIR)\qyImcPublic.obj"
	-@erase "$(INTDIR)\qyImcPublic.sbr"
	-@erase "$(INTDIR)\qyLangCommProc.obj"
	-@erase "$(INTDIR)\qyLangCommProc.sbr"
	-@erase "$(INTDIR)\qyMc.obj"
	-@erase "$(INTDIR)\qyMc.pch"
	-@erase "$(INTDIR)\qyMc.res"
	-@erase "$(INTDIR)\qyMc.sbr"
	-@erase "$(INTDIR)\qyMcAuth.obj"
	-@erase "$(INTDIR)\qyMcAuth.sbr"
	-@erase "$(INTDIR)\qyMcDoc.obj"
	-@erase "$(INTDIR)\qyMcDoc.sbr"
	-@erase "$(INTDIR)\qyMcLogon.obj"
	-@erase "$(INTDIR)\qyMcLogon.sbr"
	-@erase "$(INTDIR)\qyMcMainAssetProc.obj"
	-@erase "$(INTDIR)\qyMcMainAssetProc.sbr"
	-@erase "$(INTDIR)\qyMcMainAssetReport.obj"
	-@erase "$(INTDIR)\qyMcMainAssetReport.sbr"
	-@erase "$(INTDIR)\qyMcMainCfg.obj"
	-@erase "$(INTDIR)\qyMcMainCfg.sbr"
	-@erase "$(INTDIR)\qyMcMainCommon.obj"
	-@erase "$(INTDIR)\qyMcMainCommon.sbr"
	-@erase "$(INTDIR)\qyMcMainCommonObj.obj"
	-@erase "$(INTDIR)\qyMcMainCommonObj.sbr"
	-@erase "$(INTDIR)\qyMcMainDaemon.obj"
	-@erase "$(INTDIR)\qyMcMainDaemon.sbr"
	-@erase "$(INTDIR)\qyMcMainDb.obj"
	-@erase "$(INTDIR)\qyMcMainDb.sbr"
	-@erase "$(INTDIR)\qyMcMainHook.obj"
	-@erase "$(INTDIR)\qyMcMainHook.sbr"
	-@erase "$(INTDIR)\qyMcMainMenu.obj"
	-@erase "$(INTDIR)\qyMcMainMenu.sbr"
	-@erase "$(INTDIR)\qyMcMainObj.obj"
	-@erase "$(INTDIR)\qyMcMainObj.sbr"
	-@erase "$(INTDIR)\qyMcMainProc.obj"
	-@erase "$(INTDIR)\qyMcMainProc.sbr"
	-@erase "$(INTDIR)\qyMcMainProc1.obj"
	-@erase "$(INTDIR)\qyMcMainProc1.sbr"
	-@erase "$(INTDIR)\qyMcMainSpProc.obj"
	-@erase "$(INTDIR)\qyMcMainSpProc.sbr"
	-@erase "$(INTDIR)\qyMcMainTemp.obj"
	-@erase "$(INTDIR)\qyMcMainTemp.sbr"
	-@erase "$(INTDIR)\qyMcMonIf.obj"
	-@erase "$(INTDIR)\qyMcMonIf.sbr"
	-@erase "$(INTDIR)\qyMcProcDjData.obj"
	-@erase "$(INTDIR)\qyMcProcDjData.sbr"
	-@erase "$(INTDIR)\QyMcRootChildFrm.obj"
	-@erase "$(INTDIR)\QyMcRootChildFrm.sbr"
	-@erase "$(INTDIR)\qyMcRootProc.obj"
	-@erase "$(INTDIR)\qyMcRootProc.sbr"
	-@erase "$(INTDIR)\qyMcView.obj"
	-@erase "$(INTDIR)\qyMcView.sbr"
	-@erase "$(INTDIR)\QyPs.obj"
	-@erase "$(INTDIR)\QyPs.sbr"
	-@erase "$(INTDIR)\QyRcdset.obj"
	-@erase "$(INTDIR)\QyRcdset.sbr"
	-@erase "$(INTDIR)\qyTCharCommProc.obj"
	-@erase "$(INTDIR)\qyTCharCommProc.sbr"
	-@erase "$(INTDIR)\QyVirtualListView.obj"
	-@erase "$(INTDIR)\QyVirtualListView.sbr"
	-@erase "$(INTDIR)\Splash.obj"
	-@erase "$(INTDIR)\Splash.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\TestP.obj"
	-@erase "$(INTDIR)\TestP.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\webbrowser2.obj"
	-@erase "$(INTDIR)\webbrowser2.sbr"
	-@erase "$(OUTDIR)\qyMc.bsc"
	-@erase "$(OUTDIR)\qyMc.exe"
	-@erase "$(OUTDIR)\qyMc.ilk"
	-@erase "$(OUTDIR)\qyMc.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fp"$(INTDIR)\qyMc.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\qyMc.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qyMc.bsc" /n 
BSC32_SBRS= \
	"$(INTDIR)\getObjId.sbr" \
	"$(INTDIR)\netAlert.sbr" \
	"$(INTDIR)\qnmMainCustom.sbr" \
	"$(INTDIR)\qnmMainMenuProc.sbr" \
	"$(INTDIR)\qnmMainProc.sbr" \
	"$(INTDIR)\QyFile.sbr" \
	"$(INTDIR)\qyMcAuth.sbr" \
	"$(INTDIR)\qyMcLogon.sbr" \
	"$(INTDIR)\qyMcMainAssetProc.sbr" \
	"$(INTDIR)\qyMcMainAssetReport.sbr" \
	"$(INTDIR)\qyMcMainCfg.sbr" \
	"$(INTDIR)\qyMcMainCommon.sbr" \
	"$(INTDIR)\qyMcMainCommonObj.sbr" \
	"$(INTDIR)\qyMcMainDaemon.sbr" \
	"$(INTDIR)\qyMcMainDb.sbr" \
	"$(INTDIR)\qyMcMainHook.sbr" \
	"$(INTDIR)\qyMcMainMenu.sbr" \
	"$(INTDIR)\qyMcMainObj.sbr" \
	"$(INTDIR)\qyMcMainProc.sbr" \
	"$(INTDIR)\qyMcMainProc1.sbr" \
	"$(INTDIR)\qyMcMainSpProc.sbr" \
	"$(INTDIR)\qyMcMainTemp.sbr" \
	"$(INTDIR)\qyMcMonIf.sbr" \
	"$(INTDIR)\qyMcProcDjData.sbr" \
	"$(INTDIR)\qyMcRootProc.sbr" \
	"$(INTDIR)\DlgIp.sbr" \
	"$(INTDIR)\qmCommonDbFunc.sbr" \
	"$(INTDIR)\qmCommonFunc.sbr" \
	"$(INTDIR)\qmCommonProc.sbr" \
	"$(INTDIR)\qmSnmpProc.sbr" \
	"$(INTDIR)\QyPs.sbr" \
	"$(INTDIR)\DlgCfgInterMonIp.sbr" \
	"$(INTDIR)\InforDlg.sbr" \
	"$(INTDIR)\InterIpSetup.sbr" \
	"$(INTDIR)\IpInfoDlg.sbr" \
	"$(INTDIR)\logquery.sbr" \
	"$(INTDIR)\ChildFrm.sbr" \
	"$(INTDIR)\DlgAddSwitchToGrp.sbr" \
	"$(INTDIR)\DlgCfgBoard.sbr" \
	"$(INTDIR)\DlgCfgCustom.sbr" \
	"$(INTDIR)\DlgCfgPcProcessRule.sbr" \
	"$(INTDIR)\DlgCfgSwitchDefaultPolicyGrp.sbr" \
	"$(INTDIR)\DlgCfgSwitchPolicyGrp.sbr" \
	"$(INTDIR)\DlgCfgSwitchPolicyGrps.sbr" \
	"$(INTDIR)\DlgCfgSystemParams.sbr" \
	"$(INTDIR)\DlgCfgUsr.sbr" \
	"$(INTDIR)\DlgCfgUsrs.sbr" \
	"$(INTDIR)\DlgCfgWarn.sbr" \
	"$(INTDIR)\DlgCusPcSp.sbr" \
	"$(INTDIR)\DlgEditSp.sbr" \
	"$(INTDIR)\DlgEditSwitchInfo.sbr" \
	"$(INTDIR)\DlgIpEx.sbr" \
	"$(INTDIR)\DlgMac.sbr" \
	"$(INTDIR)\DlgMcHint.sbr" \
	"$(INTDIR)\DlgMcLogon.sbr" \
	"$(INTDIR)\DlgMgrSwitchPolicyGrps.sbr" \
	"$(INTDIR)\DlgNum.sbr" \
	"$(INTDIR)\DlgPasswdForStopMon.sbr" \
	"$(INTDIR)\DlgPcAssetProperties.sbr" \
	"$(INTDIR)\DlgPhoneNum.sbr" \
	"$(INTDIR)\DlgPropPcComputer.sbr" \
	"$(INTDIR)\DlgPropPcNetwork.sbr" \
	"$(INTDIR)\DlgPropPcProxyCfg.sbr" \
	"$(INTDIR)\DlgQnmCfgAdvancedOptions.sbr" \
	"$(INTDIR)\DlgQnmCfgIpGrp.sbr" \
	"$(INTDIR)\DlgQnmCfgIpScan.sbr" \
	"$(INTDIR)\DlgQnmCfgOptions.sbr" \
	"$(INTDIR)\DlgQnmCfgPcComputer.sbr" \
	"$(INTDIR)\DlgQnmCfgPcGrp.sbr" \
	"$(INTDIR)\DlgQnmCfgPcGrps.sbr" \
	"$(INTDIR)\DlgQnmCfgPcNetworkOptions.sbr" \
	"$(INTDIR)\DlgQnmCfgPcNetworkRule.sbr" \
	"$(INTDIR)\DlgQnmCfgPcProxyCfg.sbr" \
	"$(INTDIR)\DlgQnmCfgPcRule.sbr" \
	"$(INTDIR)\DlgQnmCfgRasOptions.sbr" \
	"$(INTDIR)\DlgQnmCfgSnmpObjRule.sbr" \
	"$(INTDIR)\DlgQnmCfgUnchk.sbr" \
	"$(INTDIR)\DlgQnmCfgUnchkedIpGrp.sbr" \
	"$(INTDIR)\DlgQnmEditMacInfo.sbr" \
	"$(INTDIR)\DlgQnmEditPcUsrInfo.sbr" \
	"$(INTDIR)\DlgQnmEventSearch.sbr" \
	"$(INTDIR)\DlgQnmOtherMacInfo.sbr" \
	"$(INTDIR)\DlgQnmPcAssetListSearch.sbr" \
	"$(INTDIR)\DlgQnmPcListSearch.sbr" \
	"$(INTDIR)\DlgQnmPcSpListSearch.sbr" \
	"$(INTDIR)\DlgQnmSearch.sbr" \
	"$(INTDIR)\DlgQnmSendHint.sbr" \
	"$(INTDIR)\DlgQnmSnmpObjPortProperties.sbr" \
	"$(INTDIR)\DlgQnmSnmpObjProperties.sbr" \
	"$(INTDIR)\DlgShhgPcProperties.sbr" \
	"$(INTDIR)\DlgSpProperties.sbr" \
	"$(INTDIR)\HistoryView.sbr" \
	"$(INTDIR)\ipdataset.sbr" \
	"$(INTDIR)\LeftView.sbr" \
	"$(INTDIR)\MainClient.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\PpClearupEventCond.sbr" \
	"$(INTDIR)\PpQnmClearup.sbr" \
	"$(INTDIR)\PpQnmStatGeneral.sbr" \
	"$(INTDIR)\PpQnmStatIpScan.sbr" \
	"$(INTDIR)\PpQnmStatOthers.sbr" \
	"$(INTDIR)\PpQnmStatPcInfo.sbr" \
	"$(INTDIR)\PpQnmStatUsrInfo.sbr" \
	"$(INTDIR)\PpQyExport.sbr" \
	"$(INTDIR)\QyBrowseView.sbr" \
	"$(INTDIR)\QyBulkset.sbr" \
	"$(INTDIR)\QyChildFrm.sbr" \
	"$(INTDIR)\QyDialogBar.sbr" \
	"$(INTDIR)\qyMc.sbr" \
	"$(INTDIR)\qyMcDoc.sbr" \
	"$(INTDIR)\QyMcRootChildFrm.sbr" \
	"$(INTDIR)\qyMcView.sbr" \
	"$(INTDIR)\QyRcdset.sbr" \
	"$(INTDIR)\QyVirtualListView.sbr" \
	"$(INTDIR)\Splash.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\TestP.sbr" \
	"$(INTDIR)\webbrowser2.sbr" \
	"$(INTDIR)\qnmAssetsTemp.sbr" \
	"$(INTDIR)\qnmChkCommProc.sbr" \
	"$(INTDIR)\qnmCommProc.sbr" \
	"$(INTDIR)\qnmCommProc1.sbr" \
	"$(INTDIR)\QnmDb.sbr" \
	"$(INTDIR)\qnmFwCommProc.sbr" \
	"$(INTDIR)\qnmGuiCommProc.sbr" \
	"$(INTDIR)\qnmHotKeys.sbr" \
	"$(INTDIR)\qnmOsAuditCommProc.sbr" \
	"$(INTDIR)\qnmsCommProc.sbr" \
	"$(INTDIR)\qnmSqlScripts.sbr" \
	"$(INTDIR)\qnmWarnCommProc.sbr" \
	"$(INTDIR)\qwmDjCommProc.sbr" \
	"$(INTDIR)\qwmNetworkStatusCommProc.sbr" \
	"$(INTDIR)\qyCommProc.sbr" \
	"$(INTDIR)\qyImcLogFunc.sbr" \
	"$(INTDIR)\qyImcPublic.sbr" \
	"$(INTDIR)\qyLangCommProc.sbr" \
	"$(INTDIR)\qyTCharCommProc.sbr" \
	"$(INTDIR)\qnmAllHints.sbr" \
	"$(INTDIR)\qnmCustom.sbr" \
	"$(INTDIR)\qnmCustomComm.sbr" \
	"$(INTDIR)\qnmCustomGui.sbr" \
	"$(INTDIR)\qnmCustomRegTool.sbr" \
	"$(INTDIR)\qnmCustomSearch.sbr" \
	"$(INTDIR)\qnmCustomStat.sbr" \
	"$(INTDIR)\qwmAllHints.sbr" \
	"$(INTDIR)\qyCustom.sbr"

"$(OUTDIR)\qyMc.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=netapi32.lib qyPublic.lib qyEncLib.lib htmlhelp.lib Spromeps.lib qyLicense.lib libDes.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\qyMc.pdb" /debug /machine:I386 /out:"$(OUTDIR)\qyMc.exe" /pdbtype:sept /libpath:"..\..\..\Debug\lib" 
LINK32_OBJS= \
	"$(INTDIR)\getObjId.obj" \
	"$(INTDIR)\netAlert.obj" \
	"$(INTDIR)\qnmMainCustom.obj" \
	"$(INTDIR)\qnmMainMenuProc.obj" \
	"$(INTDIR)\qnmMainProc.obj" \
	"$(INTDIR)\QyFile.obj" \
	"$(INTDIR)\qyMcAuth.obj" \
	"$(INTDIR)\qyMcLogon.obj" \
	"$(INTDIR)\qyMcMainAssetProc.obj" \
	"$(INTDIR)\qyMcMainAssetReport.obj" \
	"$(INTDIR)\qyMcMainCfg.obj" \
	"$(INTDIR)\qyMcMainCommon.obj" \
	"$(INTDIR)\qyMcMainCommonObj.obj" \
	"$(INTDIR)\qyMcMainDaemon.obj" \
	"$(INTDIR)\qyMcMainDb.obj" \
	"$(INTDIR)\qyMcMainHook.obj" \
	"$(INTDIR)\qyMcMainMenu.obj" \
	"$(INTDIR)\qyMcMainObj.obj" \
	"$(INTDIR)\qyMcMainProc.obj" \
	"$(INTDIR)\qyMcMainProc1.obj" \
	"$(INTDIR)\qyMcMainSpProc.obj" \
	"$(INTDIR)\qyMcMainTemp.obj" \
	"$(INTDIR)\qyMcMonIf.obj" \
	"$(INTDIR)\qyMcProcDjData.obj" \
	"$(INTDIR)\qyMcRootProc.obj" \
	"$(INTDIR)\DlgIp.obj" \
	"$(INTDIR)\qmCommonDbFunc.obj" \
	"$(INTDIR)\qmCommonFunc.obj" \
	"$(INTDIR)\qmCommonProc.obj" \
	"$(INTDIR)\qmSnmpProc.obj" \
	"$(INTDIR)\QyPs.obj" \
	"$(INTDIR)\DlgCfgInterMonIp.obj" \
	"$(INTDIR)\InforDlg.obj" \
	"$(INTDIR)\InterIpSetup.obj" \
	"$(INTDIR)\IpInfoDlg.obj" \
	"$(INTDIR)\logquery.obj" \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\DlgAddSwitchToGrp.obj" \
	"$(INTDIR)\DlgCfgBoard.obj" \
	"$(INTDIR)\DlgCfgCustom.obj" \
	"$(INTDIR)\DlgCfgPcProcessRule.obj" \
	"$(INTDIR)\DlgCfgSwitchDefaultPolicyGrp.obj" \
	"$(INTDIR)\DlgCfgSwitchPolicyGrp.obj" \
	"$(INTDIR)\DlgCfgSwitchPolicyGrps.obj" \
	"$(INTDIR)\DlgCfgSystemParams.obj" \
	"$(INTDIR)\DlgCfgUsr.obj" \
	"$(INTDIR)\DlgCfgUsrs.obj" \
	"$(INTDIR)\DlgCfgWarn.obj" \
	"$(INTDIR)\DlgCusPcSp.obj" \
	"$(INTDIR)\DlgEditSp.obj" \
	"$(INTDIR)\DlgEditSwitchInfo.obj" \
	"$(INTDIR)\DlgIpEx.obj" \
	"$(INTDIR)\DlgMac.obj" \
	"$(INTDIR)\DlgMcHint.obj" \
	"$(INTDIR)\DlgMcLogon.obj" \
	"$(INTDIR)\DlgMgrSwitchPolicyGrps.obj" \
	"$(INTDIR)\DlgNum.obj" \
	"$(INTDIR)\DlgPasswdForStopMon.obj" \
	"$(INTDIR)\DlgPcAssetProperties.obj" \
	"$(INTDIR)\DlgPhoneNum.obj" \
	"$(INTDIR)\DlgPropPcComputer.obj" \
	"$(INTDIR)\DlgPropPcNetwork.obj" \
	"$(INTDIR)\DlgPropPcProxyCfg.obj" \
	"$(INTDIR)\DlgQnmCfgAdvancedOptions.obj" \
	"$(INTDIR)\DlgQnmCfgIpGrp.obj" \
	"$(INTDIR)\DlgQnmCfgIpScan.obj" \
	"$(INTDIR)\DlgQnmCfgOptions.obj" \
	"$(INTDIR)\DlgQnmCfgPcComputer.obj" \
	"$(INTDIR)\DlgQnmCfgPcGrp.obj" \
	"$(INTDIR)\DlgQnmCfgPcGrps.obj" \
	"$(INTDIR)\DlgQnmCfgPcNetworkOptions.obj" \
	"$(INTDIR)\DlgQnmCfgPcNetworkRule.obj" \
	"$(INTDIR)\DlgQnmCfgPcProxyCfg.obj" \
	"$(INTDIR)\DlgQnmCfgPcRule.obj" \
	"$(INTDIR)\DlgQnmCfgRasOptions.obj" \
	"$(INTDIR)\DlgQnmCfgSnmpObjRule.obj" \
	"$(INTDIR)\DlgQnmCfgUnchk.obj" \
	"$(INTDIR)\DlgQnmCfgUnchkedIpGrp.obj" \
	"$(INTDIR)\DlgQnmEditMacInfo.obj" \
	"$(INTDIR)\DlgQnmEditPcUsrInfo.obj" \
	"$(INTDIR)\DlgQnmEventSearch.obj" \
	"$(INTDIR)\DlgQnmOtherMacInfo.obj" \
	"$(INTDIR)\DlgQnmPcAssetListSearch.obj" \
	"$(INTDIR)\DlgQnmPcListSearch.obj" \
	"$(INTDIR)\DlgQnmPcSpListSearch.obj" \
	"$(INTDIR)\DlgQnmSearch.obj" \
	"$(INTDIR)\DlgQnmSendHint.obj" \
	"$(INTDIR)\DlgQnmSnmpObjPortProperties.obj" \
	"$(INTDIR)\DlgQnmSnmpObjProperties.obj" \
	"$(INTDIR)\DlgShhgPcProperties.obj" \
	"$(INTDIR)\DlgSpProperties.obj" \
	"$(INTDIR)\HistoryView.obj" \
	"$(INTDIR)\ipdataset.obj" \
	"$(INTDIR)\LeftView.obj" \
	"$(INTDIR)\MainClient.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\PpClearupEventCond.obj" \
	"$(INTDIR)\PpQnmClearup.obj" \
	"$(INTDIR)\PpQnmStatGeneral.obj" \
	"$(INTDIR)\PpQnmStatIpScan.obj" \
	"$(INTDIR)\PpQnmStatOthers.obj" \
	"$(INTDIR)\PpQnmStatPcInfo.obj" \
	"$(INTDIR)\PpQnmStatUsrInfo.obj" \
	"$(INTDIR)\PpQyExport.obj" \
	"$(INTDIR)\QyBrowseView.obj" \
	"$(INTDIR)\QyBulkset.obj" \
	"$(INTDIR)\QyChildFrm.obj" \
	"$(INTDIR)\QyDialogBar.obj" \
	"$(INTDIR)\qyMc.obj" \
	"$(INTDIR)\qyMcDoc.obj" \
	"$(INTDIR)\QyMcRootChildFrm.obj" \
	"$(INTDIR)\qyMcView.obj" \
	"$(INTDIR)\QyRcdset.obj" \
	"$(INTDIR)\QyVirtualListView.obj" \
	"$(INTDIR)\Splash.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TestP.obj" \
	"$(INTDIR)\webbrowser2.obj" \
	"$(INTDIR)\qnmAssetsTemp.obj" \
	"$(INTDIR)\qnmChkCommProc.obj" \
	"$(INTDIR)\qnmCommProc.obj" \
	"$(INTDIR)\qnmCommProc1.obj" \
	"$(INTDIR)\QnmDb.obj" \
	"$(INTDIR)\qnmFwCommProc.obj" \
	"$(INTDIR)\qnmGuiCommProc.obj" \
	"$(INTDIR)\qnmHotKeys.obj" \
	"$(INTDIR)\qnmOsAuditCommProc.obj" \
	"$(INTDIR)\qnmsCommProc.obj" \
	"$(INTDIR)\qnmSqlScripts.obj" \
	"$(INTDIR)\qnmWarnCommProc.obj" \
	"$(INTDIR)\qwmDjCommProc.obj" \
	"$(INTDIR)\qwmNetworkStatusCommProc.obj" \
	"$(INTDIR)\qyCommProc.obj" \
	"$(INTDIR)\qyImcLogFunc.obj" \
	"$(INTDIR)\qyImcPublic.obj" \
	"$(INTDIR)\qyLangCommProc.obj" \
	"$(INTDIR)\qyTCharCommProc.obj" \
	"$(INTDIR)\qnmAllHints.obj" \
	"$(INTDIR)\qnmCustom.obj" \
	"$(INTDIR)\qnmCustomComm.obj" \
	"$(INTDIR)\qnmCustomGui.obj" \
	"$(INTDIR)\qnmCustomRegTool.obj" \
	"$(INTDIR)\qnmCustomSearch.obj" \
	"$(INTDIR)\qnmCustomStat.obj" \
	"$(INTDIR)\qwmAllHints.obj" \
	"$(INTDIR)\qyCustom.obj" \
	"$(INTDIR)\qyMc.res"

"$(OUTDIR)\qyMc.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("qyMc.dep")
!INCLUDE "qyMc.dep"
!ELSE 
!MESSAGE Warning: cannot find "qyMc.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "qyMc - Win32 Release" || "$(CFG)" == "qyMc - Win32 Debug"
SOURCE=.\qyMcMainPublic\getObjId.cpp

"$(INTDIR)\getObjId.obj"	"$(INTDIR)\getObjId.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qyMcMainPublic\netAlert.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qyMc.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\netAlert.obj"	"$(INTDIR)\netAlert.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\netAlert.obj"	"$(INTDIR)\netAlert.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\qyMcMainPublic\qnmMainCustom.cpp

"$(INTDIR)\qnmMainCustom.obj"	"$(INTDIR)\qnmMainCustom.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qyMcMainPublic\qnmMainMenuProc.cpp

"$(INTDIR)\qnmMainMenuProc.obj"	"$(INTDIR)\qnmMainMenuProc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qyMcMainPublic\qnmMainProc.cpp

"$(INTDIR)\qnmMainProc.obj"	"$(INTDIR)\qnmMainProc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qyMcMainPublic\QyFile.cpp

"$(INTDIR)\QyFile.obj"	"$(INTDIR)\QyFile.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qyMcMainPublic\qyMcAuth.cpp

"$(INTDIR)\qyMcAuth.obj"	"$(INTDIR)\qyMcAuth.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qyMcMainPublic\qyMcLogon.cpp

"$(INTDIR)\qyMcLogon.obj"	"$(INTDIR)\qyMcLogon.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qyMcMainPublic\qyMcMainAssetProc.cpp

"$(INTDIR)\qyMcMainAssetProc.obj"	"$(INTDIR)\qyMcMainAssetProc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qyMcMainPublic\qyMcMainAssetReport.cpp

"$(INTDIR)\qyMcMainAssetReport.obj"	"$(INTDIR)\qyMcMainAssetReport.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qyMcMainPublic\qyMcMainCfg.cpp

"$(INTDIR)\qyMcMainCfg.obj"	"$(INTDIR)\qyMcMainCfg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qyMcMainPublic\qyMcMainCommon.cpp

"$(INTDIR)\qyMcMainCommon.obj"	"$(INTDIR)\qyMcMainCommon.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qyMcMainPublic\qyMcMainCommonObj.cpp

"$(INTDIR)\qyMcMainCommonObj.obj"	"$(INTDIR)\qyMcMainCommonObj.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qyMcMainPublic\qyMcMainDaemon.cpp

"$(INTDIR)\qyMcMainDaemon.obj"	"$(INTDIR)\qyMcMainDaemon.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qyMcMainPublic\qyMcMainDb.cpp

"$(INTDIR)\qyMcMainDb.obj"	"$(INTDIR)\qyMcMainDb.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qyMcMainPublic\qyMcMainHook.cpp

"$(INTDIR)\qyMcMainHook.obj"	"$(INTDIR)\qyMcMainHook.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qyMcMainPublic\qyMcMainMenu.cpp

"$(INTDIR)\qyMcMainMenu.obj"	"$(INTDIR)\qyMcMainMenu.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qyMcMainPublic\qyMcMainObj.cpp

"$(INTDIR)\qyMcMainObj.obj"	"$(INTDIR)\qyMcMainObj.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qyMcMainPublic\qyMcMainProc.cpp

"$(INTDIR)\qyMcMainProc.obj"	"$(INTDIR)\qyMcMainProc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qyMcMainPublic\qyMcMainProc1.cpp

"$(INTDIR)\qyMcMainProc1.obj"	"$(INTDIR)\qyMcMainProc1.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qyMcMainPublic\qyMcMainSpProc.cpp

"$(INTDIR)\qyMcMainSpProc.obj"	"$(INTDIR)\qyMcMainSpProc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qyMcMainPublic\qyMcMainTemp.cpp

"$(INTDIR)\qyMcMainTemp.obj"	"$(INTDIR)\qyMcMainTemp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qyMcMainPublic\qyMcMonIf.cpp

"$(INTDIR)\qyMcMonIf.obj"	"$(INTDIR)\qyMcMonIf.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qyMcMainPublic\qyMcProcDjData.cpp

"$(INTDIR)\qyMcProcDjData.obj"	"$(INTDIR)\qyMcProcDjData.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qyMcMainPublic\qyMcRootProc.cpp

"$(INTDIR)\qyMcRootProc.obj"	"$(INTDIR)\qyMcRootProc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\qymcPublic\DlgIp.cpp

"$(INTDIR)\DlgIp.obj"	"$(INTDIR)\DlgIp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\qymcPublic\qmCommonDbFunc.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qmCommonDbFunc.obj"	"$(INTDIR)\qmCommonDbFunc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qmCommonDbFunc.obj"	"$(INTDIR)\qmCommonDbFunc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\qymcPublic\qmCommonFunc.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qyMc.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qmCommonFunc.obj"	"$(INTDIR)\qmCommonFunc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qmCommonFunc.obj"	"$(INTDIR)\qmCommonFunc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\qymcPublic\qmCommonProc.cpp

"$(INTDIR)\qmCommonProc.obj"	"$(INTDIR)\qmCommonProc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\qymcPublic\qmSnmpProc.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qmSnmpProc.obj"	"$(INTDIR)\qmSnmpProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qmSnmpProc.obj"	"$(INTDIR)\qmSnmpProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\qymcPublic\QyPs.cpp

"$(INTDIR)\QyPs.obj"	"$(INTDIR)\QyPs.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\bhb\DlgCfgInterMonIp.cpp

"$(INTDIR)\DlgCfgInterMonIp.obj"	"$(INTDIR)\DlgCfgInterMonIp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\bhb\InforDlg.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qyMc.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\InforDlg.obj"	"$(INTDIR)\InforDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fp"$(INTDIR)\qyMc.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\InforDlg.obj"	"$(INTDIR)\InforDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\bhb\InterIpSetup.cpp

"$(INTDIR)\InterIpSetup.obj"	"$(INTDIR)\InterIpSetup.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\bhb\IpInfoDlg.cpp

"$(INTDIR)\IpInfoDlg.obj"	"$(INTDIR)\IpInfoDlg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\bhb\logquery.cpp

"$(INTDIR)\logquery.obj"	"$(INTDIR)\logquery.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\ChildFrm.cpp

"$(INTDIR)\ChildFrm.obj"	"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgAddSwitchToGrp.cpp

"$(INTDIR)\DlgAddSwitchToGrp.obj"	"$(INTDIR)\DlgAddSwitchToGrp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgCfgBoard.cpp

"$(INTDIR)\DlgCfgBoard.obj"	"$(INTDIR)\DlgCfgBoard.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgCfgCustom.cpp

"$(INTDIR)\DlgCfgCustom.obj"	"$(INTDIR)\DlgCfgCustom.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgCfgPcProcessRule.cpp

"$(INTDIR)\DlgCfgPcProcessRule.obj"	"$(INTDIR)\DlgCfgPcProcessRule.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgCfgSwitchDefaultPolicyGrp.cpp

"$(INTDIR)\DlgCfgSwitchDefaultPolicyGrp.obj"	"$(INTDIR)\DlgCfgSwitchDefaultPolicyGrp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgCfgSwitchPolicyGrp.cpp

"$(INTDIR)\DlgCfgSwitchPolicyGrp.obj"	"$(INTDIR)\DlgCfgSwitchPolicyGrp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgCfgSwitchPolicyGrps.cpp

"$(INTDIR)\DlgCfgSwitchPolicyGrps.obj"	"$(INTDIR)\DlgCfgSwitchPolicyGrps.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgCfgSystemParams.cpp

"$(INTDIR)\DlgCfgSystemParams.obj"	"$(INTDIR)\DlgCfgSystemParams.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgCfgUsr.cpp

"$(INTDIR)\DlgCfgUsr.obj"	"$(INTDIR)\DlgCfgUsr.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgCfgUsrs.cpp

"$(INTDIR)\DlgCfgUsrs.obj"	"$(INTDIR)\DlgCfgUsrs.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgCfgWarn.cpp

"$(INTDIR)\DlgCfgWarn.obj"	"$(INTDIR)\DlgCfgWarn.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgCusPcSp.cpp

"$(INTDIR)\DlgCusPcSp.obj"	"$(INTDIR)\DlgCusPcSp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgEditSp.cpp

"$(INTDIR)\DlgEditSp.obj"	"$(INTDIR)\DlgEditSp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgEditSwitchInfo.cpp

"$(INTDIR)\DlgEditSwitchInfo.obj"	"$(INTDIR)\DlgEditSwitchInfo.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgIpEx.cpp

"$(INTDIR)\DlgIpEx.obj"	"$(INTDIR)\DlgIpEx.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgMac.cpp

"$(INTDIR)\DlgMac.obj"	"$(INTDIR)\DlgMac.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgMcHint.cpp

"$(INTDIR)\DlgMcHint.obj"	"$(INTDIR)\DlgMcHint.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgMcLogon.cpp

"$(INTDIR)\DlgMcLogon.obj"	"$(INTDIR)\DlgMcLogon.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgMgrSwitchPolicyGrps.cpp

"$(INTDIR)\DlgMgrSwitchPolicyGrps.obj"	"$(INTDIR)\DlgMgrSwitchPolicyGrps.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgNum.cpp

"$(INTDIR)\DlgNum.obj"	"$(INTDIR)\DlgNum.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgPasswdForStopMon.cpp

"$(INTDIR)\DlgPasswdForStopMon.obj"	"$(INTDIR)\DlgPasswdForStopMon.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgPcAssetProperties.cpp

"$(INTDIR)\DlgPcAssetProperties.obj"	"$(INTDIR)\DlgPcAssetProperties.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgPhoneNum.cpp

"$(INTDIR)\DlgPhoneNum.obj"	"$(INTDIR)\DlgPhoneNum.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgPropPcComputer.cpp

"$(INTDIR)\DlgPropPcComputer.obj"	"$(INTDIR)\DlgPropPcComputer.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgPropPcNetwork.cpp

"$(INTDIR)\DlgPropPcNetwork.obj"	"$(INTDIR)\DlgPropPcNetwork.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgPropPcProxyCfg.cpp

"$(INTDIR)\DlgPropPcProxyCfg.obj"	"$(INTDIR)\DlgPropPcProxyCfg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmCfgAdvancedOptions.cpp

"$(INTDIR)\DlgQnmCfgAdvancedOptions.obj"	"$(INTDIR)\DlgQnmCfgAdvancedOptions.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmCfgIpGrp.cpp

"$(INTDIR)\DlgQnmCfgIpGrp.obj"	"$(INTDIR)\DlgQnmCfgIpGrp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmCfgIpScan.cpp

"$(INTDIR)\DlgQnmCfgIpScan.obj"	"$(INTDIR)\DlgQnmCfgIpScan.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmCfgOptions.cpp

"$(INTDIR)\DlgQnmCfgOptions.obj"	"$(INTDIR)\DlgQnmCfgOptions.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmCfgPcComputer.cpp

"$(INTDIR)\DlgQnmCfgPcComputer.obj"	"$(INTDIR)\DlgQnmCfgPcComputer.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmCfgPcGrp.cpp

"$(INTDIR)\DlgQnmCfgPcGrp.obj"	"$(INTDIR)\DlgQnmCfgPcGrp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmCfgPcGrps.cpp

"$(INTDIR)\DlgQnmCfgPcGrps.obj"	"$(INTDIR)\DlgQnmCfgPcGrps.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmCfgPcNetworkOptions.cpp

"$(INTDIR)\DlgQnmCfgPcNetworkOptions.obj"	"$(INTDIR)\DlgQnmCfgPcNetworkOptions.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmCfgPcNetworkRule.cpp

"$(INTDIR)\DlgQnmCfgPcNetworkRule.obj"	"$(INTDIR)\DlgQnmCfgPcNetworkRule.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmCfgPcProxyCfg.cpp

"$(INTDIR)\DlgQnmCfgPcProxyCfg.obj"	"$(INTDIR)\DlgQnmCfgPcProxyCfg.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmCfgPcRule.cpp

"$(INTDIR)\DlgQnmCfgPcRule.obj"	"$(INTDIR)\DlgQnmCfgPcRule.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmCfgRasOptions.cpp

"$(INTDIR)\DlgQnmCfgRasOptions.obj"	"$(INTDIR)\DlgQnmCfgRasOptions.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmCfgSnmpObjRule.cpp

"$(INTDIR)\DlgQnmCfgSnmpObjRule.obj"	"$(INTDIR)\DlgQnmCfgSnmpObjRule.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmCfgUnchk.cpp

"$(INTDIR)\DlgQnmCfgUnchk.obj"	"$(INTDIR)\DlgQnmCfgUnchk.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmCfgUnchkedIpGrp.cpp

"$(INTDIR)\DlgQnmCfgUnchkedIpGrp.obj"	"$(INTDIR)\DlgQnmCfgUnchkedIpGrp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmEditMacInfo.cpp

"$(INTDIR)\DlgQnmEditMacInfo.obj"	"$(INTDIR)\DlgQnmEditMacInfo.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmEditPcUsrInfo.cpp

"$(INTDIR)\DlgQnmEditPcUsrInfo.obj"	"$(INTDIR)\DlgQnmEditPcUsrInfo.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmEventSearch.cpp

"$(INTDIR)\DlgQnmEventSearch.obj"	"$(INTDIR)\DlgQnmEventSearch.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmOtherMacInfo.cpp

"$(INTDIR)\DlgQnmOtherMacInfo.obj"	"$(INTDIR)\DlgQnmOtherMacInfo.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmPcAssetListSearch.cpp

"$(INTDIR)\DlgQnmPcAssetListSearch.obj"	"$(INTDIR)\DlgQnmPcAssetListSearch.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmPcListSearch.cpp

"$(INTDIR)\DlgQnmPcListSearch.obj"	"$(INTDIR)\DlgQnmPcListSearch.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmPcSpListSearch.cpp

"$(INTDIR)\DlgQnmPcSpListSearch.obj"	"$(INTDIR)\DlgQnmPcSpListSearch.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmSearch.cpp

"$(INTDIR)\DlgQnmSearch.obj"	"$(INTDIR)\DlgQnmSearch.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmSendHint.cpp

"$(INTDIR)\DlgQnmSendHint.obj"	"$(INTDIR)\DlgQnmSendHint.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmSnmpObjPortProperties.cpp

"$(INTDIR)\DlgQnmSnmpObjPortProperties.obj"	"$(INTDIR)\DlgQnmSnmpObjPortProperties.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgQnmSnmpObjProperties.cpp

"$(INTDIR)\DlgQnmSnmpObjProperties.obj"	"$(INTDIR)\DlgQnmSnmpObjProperties.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgShhgPcProperties.cpp

"$(INTDIR)\DlgShhgPcProperties.obj"	"$(INTDIR)\DlgShhgPcProperties.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\DlgSpProperties.cpp

"$(INTDIR)\DlgSpProperties.obj"	"$(INTDIR)\DlgSpProperties.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\HistoryView.cpp

"$(INTDIR)\HistoryView.obj"	"$(INTDIR)\HistoryView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\bhb\ipdataset.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /I ".." /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qyMc.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\ipdataset.obj"	"$(INTDIR)\ipdataset.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /I ".." /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fp"$(INTDIR)\qyMc.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\ipdataset.obj"	"$(INTDIR)\ipdataset.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\LeftView.cpp

"$(INTDIR)\LeftView.obj"	"$(INTDIR)\LeftView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\MainClient.cpp

"$(INTDIR)\MainClient.obj"	"$(INTDIR)\MainClient.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\MainFrm.cpp

"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\PpClearupEventCond.cpp

"$(INTDIR)\PpClearupEventCond.obj"	"$(INTDIR)\PpClearupEventCond.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\PpQnmClearup.cpp

"$(INTDIR)\PpQnmClearup.obj"	"$(INTDIR)\PpQnmClearup.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\PpQnmStatGeneral.cpp

"$(INTDIR)\PpQnmStatGeneral.obj"	"$(INTDIR)\PpQnmStatGeneral.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\PpQnmStatIpScan.cpp

"$(INTDIR)\PpQnmStatIpScan.obj"	"$(INTDIR)\PpQnmStatIpScan.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\PpQnmStatOthers.cpp

"$(INTDIR)\PpQnmStatOthers.obj"	"$(INTDIR)\PpQnmStatOthers.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\PpQnmStatPcInfo.cpp

"$(INTDIR)\PpQnmStatPcInfo.obj"	"$(INTDIR)\PpQnmStatPcInfo.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\PpQnmStatUsrInfo.cpp

"$(INTDIR)\PpQnmStatUsrInfo.obj"	"$(INTDIR)\PpQnmStatUsrInfo.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\PpQyExport.cpp

"$(INTDIR)\PpQyExport.obj"	"$(INTDIR)\PpQyExport.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\QyBrowseView.cpp

"$(INTDIR)\QyBrowseView.obj"	"$(INTDIR)\QyBrowseView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\QyBulkset.cpp

"$(INTDIR)\QyBulkset.obj"	"$(INTDIR)\QyBulkset.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\QyChildFrm.cpp

"$(INTDIR)\QyChildFrm.obj"	"$(INTDIR)\QyChildFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\QyDialogBar.cpp

"$(INTDIR)\QyDialogBar.obj"	"$(INTDIR)\QyDialogBar.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\qyMc.cpp

"$(INTDIR)\qyMc.obj"	"$(INTDIR)\qyMc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\qyMc.rc

"$(INTDIR)\qyMc.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\qyMcDoc.cpp

"$(INTDIR)\qyMcDoc.obj"	"$(INTDIR)\qyMcDoc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\QyMcRootChildFrm.cpp

"$(INTDIR)\QyMcRootChildFrm.obj"	"$(INTDIR)\QyMcRootChildFrm.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\qyMcView.cpp

"$(INTDIR)\qyMcView.obj"	"$(INTDIR)\qyMcView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\QyRcdset.cpp

"$(INTDIR)\QyRcdset.obj"	"$(INTDIR)\QyRcdset.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\QyVirtualListView.cpp

"$(INTDIR)\QyVirtualListView.obj"	"$(INTDIR)\QyVirtualListView.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\Splash.cpp

"$(INTDIR)\Splash.obj"	"$(INTDIR)\Splash.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qyMc.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\qyMc.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fp"$(INTDIR)\qyMc.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\qyMc.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TestP.cpp

"$(INTDIR)\TestP.obj"	"$(INTDIR)\TestP.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=.\webbrowser2.cpp

"$(INTDIR)\webbrowser2.obj"	"$(INTDIR)\webbrowser2.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"


SOURCE=..\..\qyCommProc\qnmAssetsTemp.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmAssetsTemp.obj"	"$(INTDIR)\qnmAssetsTemp.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmAssetsTemp.obj"	"$(INTDIR)\qnmAssetsTemp.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qnmChkCommProc.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmChkCommProc.obj"	"$(INTDIR)\qnmChkCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmChkCommProc.obj"	"$(INTDIR)\qnmChkCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qnmCommProc.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCommProc.obj"	"$(INTDIR)\qnmCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCommProc.obj"	"$(INTDIR)\qnmCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qnmCommProc1.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCommProc1.obj"	"$(INTDIR)\qnmCommProc1.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCommProc1.obj"	"$(INTDIR)\qnmCommProc1.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\QnmDb.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\QnmDb.obj"	"$(INTDIR)\QnmDb.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\QnmDb.obj"	"$(INTDIR)\QnmDb.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qnmFwCommProc.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmFwCommProc.obj"	"$(INTDIR)\qnmFwCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmFwCommProc.obj"	"$(INTDIR)\qnmFwCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qnmGuiCommProc.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmGuiCommProc.obj"	"$(INTDIR)\qnmGuiCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmGuiCommProc.obj"	"$(INTDIR)\qnmGuiCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qnmHotKeys.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmHotKeys.obj"	"$(INTDIR)\qnmHotKeys.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmHotKeys.obj"	"$(INTDIR)\qnmHotKeys.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qnmOsAuditCommProc.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmOsAuditCommProc.obj"	"$(INTDIR)\qnmOsAuditCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmOsAuditCommProc.obj"	"$(INTDIR)\qnmOsAuditCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qnmsCommProc.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmsCommProc.obj"	"$(INTDIR)\qnmsCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmsCommProc.obj"	"$(INTDIR)\qnmsCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qnmSqlScripts.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmSqlScripts.obj"	"$(INTDIR)\qnmSqlScripts.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmSqlScripts.obj"	"$(INTDIR)\qnmSqlScripts.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qnmWarnCommProc.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmWarnCommProc.obj"	"$(INTDIR)\qnmWarnCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmWarnCommProc.obj"	"$(INTDIR)\qnmWarnCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qwmDjCommProc.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qwmDjCommProc.obj"	"$(INTDIR)\qwmDjCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qwmDjCommProc.obj"	"$(INTDIR)\qwmDjCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qwmNetworkStatusCommProc.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qwmNetworkStatusCommProc.obj"	"$(INTDIR)\qwmNetworkStatusCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qwmNetworkStatusCommProc.obj"	"$(INTDIR)\qwmNetworkStatusCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qyCommProc.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyCommProc.obj"	"$(INTDIR)\qyCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyCommProc.obj"	"$(INTDIR)\qyCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qyImcLogFunc.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyImcLogFunc.obj"	"$(INTDIR)\qyImcLogFunc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyImcLogFunc.obj"	"$(INTDIR)\qyImcLogFunc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qyImcPublic.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyImcPublic.obj"	"$(INTDIR)\qyImcPublic.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyImcPublic.obj"	"$(INTDIR)\qyImcPublic.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qyLangCommProc.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyLangCommProc.obj"	"$(INTDIR)\qyLangCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyLangCommProc.obj"	"$(INTDIR)\qyLangCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qyTCharCommProc.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyTCharCommProc.obj"	"$(INTDIR)\qyTCharCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyTCharCommProc.obj"	"$(INTDIR)\qyTCharCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCustom\qnmAllHints.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmAllHints.obj"	"$(INTDIR)\qnmAllHints.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmAllHints.obj"	"$(INTDIR)\qnmAllHints.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCustom\qnmCustom.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCustom.obj"	"$(INTDIR)\qnmCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCustom.obj"	"$(INTDIR)\qnmCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCustom\qnmCustomComm.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCustomComm.obj"	"$(INTDIR)\qnmCustomComm.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCustomComm.obj"	"$(INTDIR)\qnmCustomComm.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCustom\qnmCustomGui.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qyMc.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCustomGui.obj"	"$(INTDIR)\qnmCustomGui.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCustomGui.obj"	"$(INTDIR)\qnmCustomGui.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCustom\qnmCustomRegTool.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCustomRegTool.obj"	"$(INTDIR)\qnmCustomRegTool.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCustomRegTool.obj"	"$(INTDIR)\qnmCustomRegTool.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCustom\qnmCustomSearch.cpp

"$(INTDIR)\qnmCustomSearch.obj"	"$(INTDIR)\qnmCustomSearch.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\qyCustom\qnmCustomStat.cpp

"$(INTDIR)\qnmCustomStat.obj"	"$(INTDIR)\qnmCustomStat.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qyMc.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\qyCustom\qwmAllHints.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qwmAllHints.obj"	"$(INTDIR)\qwmAllHints.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qwmAllHints.obj"	"$(INTDIR)\qwmAllHints.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCustom\qyCustom.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyCustom.obj"	"$(INTDIR)\qyCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyCustom.obj"	"$(INTDIR)\qyCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

