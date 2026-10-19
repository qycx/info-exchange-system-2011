# Microsoft Developer Studio Project File - Name="qyMc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=qyMc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "qyMc.mak".
!MESSAGE 
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

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "qyMc - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\Release\bin"
# PROP Intermediate_Dir "..\..\..\..\o\qyMc\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /I "..\..\..\qyCusResSrc\qyCusRes\include" /I "..\..\qyCommProc\include" /I "..\..\qyCommProc_mis\include" /I "..\..\..\qyOpen\qyCommProc_open\include" /I "..\..\..\componentsSrc\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D WINVER=0x0500 /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 SentinelKeys_md.lib netapi32.lib vfw32.lib Winmm.lib qyPublic.lib qyEncLib.lib htmlhelp.lib Spromeps.lib qyLicense.lib libDes.lib Msacm32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /libpath:"..\..\..\..\Release\lib"

!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\Debug\bin"
# PROP Intermediate_Dir "..\..\..\..\o\qyMc\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /I "." /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /I "..\..\..\qyCusResSrc\qyCusRes\include" /I "..\..\qyCommProc\include" /I "..\..\qyCommProc_mis\include" /I "..\..\..\qyOpen\qyCommProc_open\include" /I "..\..\..\componentsSrc\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D WINVER=0x0500 /Fr /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /n
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 netapi32.lib vfw32.lib Winmm.lib qyPublic.lib qyEncLib.lib htmlhelp.lib Spromeps.lib qyLicense.lib libDes.lib Msacm32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\..\..\..\Debug\lib"

!ENDIF 

# Begin Target

# Name "qyMc - Win32 Release"
# Name "qyMc - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "qymcMainPublic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\qyMcMainPublic\capImageProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\getObjId.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\netAlert.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qmcAcm.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qmcCrypt.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qmcVideoCapture.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qnmMainCustom.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qnmMainMenuProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qnmMainProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qnmMainProc_mis.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qnmMainProc_misClient.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qnmMainRemoteDesktop.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qnmTrayProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyAvRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyAvRecord_dx.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyBoundWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyCustSite.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\QyFile.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyIdisImp.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcAuth.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcInputMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcLogon.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcMainAssetProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcMainAssetReport.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcMainCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcMainCommon.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcMainCommonObj.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcMainCusModule.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcMainDaemon.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcMainDaemon_mis.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcMainDaemon_netMc.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcMainDb.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcMainHook.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcMainInternalBak.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcMainMediaProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcMainMediaReceiver.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcMainMediaSender.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcMainMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcMainModuleKnowlegeProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcMainObj.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcMainProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcMainProc1.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcMainRealTimeMediaProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcMainRobotProc_misClient.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcMainSpProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcMainTemp.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcMonIf.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcProcDjData.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcMainPublic\qyMcRootProc.cpp
# End Source File
# End Group
# Begin Group "qyMcPublic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\qymcPublic\DlgIp.cpp
# End Source File
# Begin Source File

SOURCE=..\qymcPublic\qmCommonDbFunc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\qymcPublic\qmCommondbFunc_mis.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\qymcPublic\qmCommonFunc.cpp

!IF  "$(CFG)" == "qyMc - Win32 Release"

!ELSEIF  "$(CFG)" == "qyMc - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\qymcPublic\qmCommonProc.cpp
# End Source File
# Begin Source File

SOURCE=..\qymcPublic\qmCrypt.cpp
# End Source File
# Begin Source File

SOURCE=..\qymcPublic\qmObjQProc.cpp
# End Source File
# Begin Source File

SOURCE=..\qymcPublic\qmSnmpProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\qymcPublic\QyPs.cpp
# End Source File
# End Group
# Begin Group "bhb"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\bhb\DlgCfgInterMonIp.cpp
# End Source File
# Begin Source File

SOURCE=.\bhb\InforDlg.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\bhb\InterIpSetup.cpp
# End Source File
# Begin Source File

SOURCE=.\bhb\IpInfoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\bhb\logquery.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAddFileMonRule.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAddSwitchToGrp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAutoLogon.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAutoLogons.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgBoard.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgCustom.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgFileMonFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgGsmModem.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgIpKnowledge.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgModuleKnowlege.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgPcProcessRule.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgPcRegistry.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgPcRegistryKnowledge.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgPcRegistrys.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgPhoneMessenger.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgSkippedMacs.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgStandardName.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgStandardNames.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgSwitchDefaultPolicyGrp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgSwitchPolicyGrp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgSwitchPolicyGrps.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgSystemParams.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgSystemParams_is.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgUsr.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgUsrs.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgVideoConference.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCfgWarn.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCusPcSp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDesktopsMon.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEditSp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEditSwitchInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgImGrp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgImMsgSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIpEx.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMac.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMcHint.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMcLogon.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMgrSwitchPolicyGrps.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgModuleKnowlegeOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNum.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPasswdForStopMon.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPcAssetProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPcNetworkOptionsSel.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPhoneNum.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPolicyImAuthCond.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPolicyIsClient.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPolicyIsMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPropImGrp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPropImMsg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPropImTask.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPropIpKnowledge.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPropMessenger.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPropModuleKnowlege.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPropPcComputer.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPropPcNetwork.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPropPcProxyCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPropPcRegistryKnowledge.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPropWindowsUpdatePolicy.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgAdvancedOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgIpGrp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgIpScan.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgOptionsIsClient.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgPcComputer.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgPcGrp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgPcGrps.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgPcMonOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgPcNetworkOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgPcNetworkRule.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgPcProxyCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgPcRule.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgRasOptions.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgSnmpObjRule.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgUnchk.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgUnchkedIpGrp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgWindowsUpdatePolicy.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmEditMacInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmEditPcUsrInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmEventSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmOtherMacInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmPcAssetListSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmPcListSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmPcProcessModuleListSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmPcSpListSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmSendHint.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmSnmpObjPortProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQnmSnmpObjProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQyCfgSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQyCfgSystems.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSelect.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSelectDsn.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgShhgPcProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSpProperties.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTalk.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVerifyPhoneList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVideos.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWwwQmContact.cpp
# End Source File
# Begin Source File

SOURCE=.\HistoryView.cpp
# End Source File
# Begin Source File

SOURCE=.\bhb\ipdataset.cpp
# ADD CPP /I ".."
# End Source File
# Begin Source File

SOURCE=.\LeftView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainClient.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\PpClearupEventCond.cpp
# End Source File
# Begin Source File

SOURCE=.\PpQnmClearup.cpp
# End Source File
# Begin Source File

SOURCE=.\PpQnmStatGeneral.cpp
# End Source File
# Begin Source File

SOURCE=.\PpQnmStatIpScan.cpp
# End Source File
# Begin Source File

SOURCE=.\PpQnmStatOthers.cpp
# End Source File
# Begin Source File

SOURCE=.\PpQnmStatPcInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\PpQnmStatUsrInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\PpQyExport.cpp
# End Source File
# Begin Source File

SOURCE=.\PpStatMessengerInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\QyBrowseView.cpp
# End Source File
# Begin Source File

SOURCE=.\QyBulkset.cpp
# End Source File
# Begin Source File

SOURCE=.\QyChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\QyDialogBar.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMc.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMc.rc
# End Source File
# Begin Source File

SOURCE=.\qyMcDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\QyMcRootChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcView.cpp
# End Source File
# Begin Source File

SOURCE=.\QyPlaySound.cpp
# End Source File
# Begin Source File

SOURCE=.\QyRcdset.cpp
# End Source File
# Begin Source File

SOURCE=.\QyRecordSound.cpp
# End Source File
# Begin Source File

SOURCE=.\QyStatic.cpp
# End Source File
# Begin Source File

SOURCE=.\QyVirtualListView.cpp
# End Source File
# Begin Source File

SOURCE=.\Splash.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TestP.cpp
# End Source File
# Begin Source File

SOURCE=.\webbrowser2.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "qyMcMainInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\INCLUDE\qmcAcm.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\qmcCommFunc_mis.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\qmcCommFunc_netMc.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\qmcVideoCapture.h
# End Source File
# Begin Source File

SOURCE=.\include\qnmMainProc.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\qnmMainProc_mis.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\qnmTrayProc.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\qyAvRecord.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\qyAvRecord_dx.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\qyAvRecordPublic.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\qyBoundWnd.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\qyCustSite.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\qyDropTarget.h
# End Source File
# Begin Source File

SOURCE=.\include\QyFile.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\qyIdisImp.h
# End Source File
# Begin Source File

SOURCE=.\include\qyMcAuth.h
# End Source File
# Begin Source File

SOURCE=.\include\qyMcDlgBarCfg.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\qyMcInputMgr.h
# End Source File
# Begin Source File

SOURCE=.\include\qyMcMainCommon.h
# End Source File
# Begin Source File

SOURCE=.\include\qyMcMainCommonObj.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\qyMcMainCusModule.h
# End Source File
# Begin Source File

SOURCE=.\include\qyMcMainDb.h
# End Source File
# Begin Source File

SOURCE=.\include\qyMcMainDefs.h
# End Source File
# Begin Source File

SOURCE=.\include\qyMcMainHint.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\qyMcMainInternalBak.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\qyMcMainMediaProc.h
# End Source File
# Begin Source File

SOURCE=.\include\qyMcMainMenu.h
# End Source File
# Begin Source File

SOURCE=.\include\qyMcMainObj.h
# End Source File
# Begin Source File

SOURCE=.\include\qyMcMainProc.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\qyMcMainRealTimeMediaProc.h
# End Source File
# Begin Source File

SOURCE=.\include\qyMcMainTemp.h
# End Source File
# Begin Source File

SOURCE=.\include\qyMcWmComm.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\qyVk.h
# End Source File
# End Group
# Begin Group "qmInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\DlgIp.h
# End Source File
# Begin Source File

SOURCE=..\include\qmCfg.h
# End Source File
# Begin Source File

SOURCE=..\include\qmCommon.h
# End Source File
# Begin Source File

SOURCE=..\include\qmCommonFunc.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\qmCommonFunc_mis.h
# End Source File
# Begin Source File

SOURCE=..\INCLUDE\qmObjQProc.h
# End Source File
# Begin Source File

SOURCE=..\include\qmObjs.h
# End Source File
# Begin Source File

SOURCE=..\include\qmReadme.h
# End Source File
# Begin Source File

SOURCE=..\include\QyPs.h
# End Source File
# End Group
# Begin Group "bhbInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\bhb\DlgCfgInterMonIp.h
# End Source File
# Begin Source File

SOURCE=.\bhb\InforDlg.h
# End Source File
# Begin Source File

SOURCE=.\bhb\InterIpSetup.h
# End Source File
# Begin Source File

SOURCE=.\bhb\IpInfoDlg.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\DlgAddFileMonRule.h
# End Source File
# Begin Source File

SOURCE=.\DlgAddSwitchToGrp.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAutoLogon.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgAutoLogons.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgBoard.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgCustom.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgFileMonFilter.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgGsmModem.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgIpKnowledge.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgModuleKnowlege.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgPcProcessRule.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgPcRegistry.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgPcRegistryKnowledge.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgPcRegistrys.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgPhoneMessenger.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgSkippedMacs.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgStandardName.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgStandardNames.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgSwitchDefaultPolicyGrp.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgSwitchPolicyGrp.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgSwitchPolicyGrps.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgSystemParams.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgSystemParams_is.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgUsr.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgUsrs.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgVideoConference.h
# End Source File
# Begin Source File

SOURCE=.\DlgCfgWarn.h
# End Source File
# Begin Source File

SOURCE=.\DlgCusPcSp.h
# End Source File
# Begin Source File

SOURCE=.\DlgDesktopsMon.h
# End Source File
# Begin Source File

SOURCE=.\DlgEditSp.h
# End Source File
# Begin Source File

SOURCE=.\DlgEditSwitchInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgImGrp.h
# End Source File
# Begin Source File

SOURCE=.\DlgImMsgSearch.h
# End Source File
# Begin Source File

SOURCE=.\DlgIpEx.h
# End Source File
# Begin Source File

SOURCE=.\DlgMac.h
# End Source File
# Begin Source File

SOURCE=.\DlgMcHint.h
# End Source File
# Begin Source File

SOURCE=.\DlgMcLogon.h
# End Source File
# Begin Source File

SOURCE=.\DlgMgrSwitchPolicyGrps.h
# End Source File
# Begin Source File

SOURCE=.\DlgModuleKnowlegeOptions.h
# End Source File
# Begin Source File

SOURCE=.\DlgNum.h
# End Source File
# Begin Source File

SOURCE=.\DlgPasswdForStopMon.h
# End Source File
# Begin Source File

SOURCE=.\DlgPcAssetProperties.h
# End Source File
# Begin Source File

SOURCE=.\DlgPcNetworkOptionsSel.h
# End Source File
# Begin Source File

SOURCE=.\DlgPhoneNum.h
# End Source File
# Begin Source File

SOURCE=.\DlgPolicyImAuthCond.h
# End Source File
# Begin Source File

SOURCE=.\DlgPolicyIsClient.h
# End Source File
# Begin Source File

SOURCE=.\DlgPolicyIsMgr.h
# End Source File
# Begin Source File

SOURCE=.\DlgPropImGrp.h
# End Source File
# Begin Source File

SOURCE=.\DlgPropImMsg.h
# End Source File
# Begin Source File

SOURCE=.\DlgPropImTask.h
# End Source File
# Begin Source File

SOURCE=.\DlgPropIpKnowledge.h
# End Source File
# Begin Source File

SOURCE=.\DlgPropMessenger.h
# End Source File
# Begin Source File

SOURCE=.\DlgPropModuleKnowlege.h
# End Source File
# Begin Source File

SOURCE=.\DlgPropPcComputer.h
# End Source File
# Begin Source File

SOURCE=.\DlgPropPcNetwork.h
# End Source File
# Begin Source File

SOURCE=.\DlgPropPcProxyCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgPropPcRegistryKnowledge.h
# End Source File
# Begin Source File

SOURCE=.\DlgPropWindowsUpdatePolicy.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgAdvancedOptions.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgIpGrp.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgIpScan.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgOptions.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgOptionsIsClient.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgPcComputer.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgPcGrp.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgPcGrps.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgPcMonOptions.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgPcNetworkOptions.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgPcNetworkRule.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgPcProxyCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgPcRule.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgRasOptions.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgSnmpObjRule.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgUnchk.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgUnchkedIpGrp.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmCfgWindowsUpdatePolicy.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmEditMacInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmEditPcUsrInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmEventSearch.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmOtherMacInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmPcAssetListSearch.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmPcListSearch.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmPcProcessModuleListSearch.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmPcSpListSearch.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmSearch.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmSendHint.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmSnmpObjPortProperties.h
# End Source File
# Begin Source File

SOURCE=.\DlgQnmSnmpObjProperties.h
# End Source File
# Begin Source File

SOURCE=.\DlgQyCfgSystem.h
# End Source File
# Begin Source File

SOURCE=.\DlgQyCfgSystems.h
# End Source File
# Begin Source File

SOURCE=.\DlgSelect.h
# End Source File
# Begin Source File

SOURCE=.\DlgSelectDsn.h
# End Source File
# Begin Source File

SOURCE=.\DlgShhgPcProperties.h
# End Source File
# Begin Source File

SOURCE=.\DlgSpProperties.h
# End Source File
# Begin Source File

SOURCE=.\DlgTalk.h
# End Source File
# Begin Source File

SOURCE=.\DlgVerifyPhoneList.h
# End Source File
# Begin Source File

SOURCE=.\DlgVideos.h
# End Source File
# Begin Source File

SOURCE=.\DlgWwwQmContact.h
# End Source File
# Begin Source File

SOURCE=.\HistoryView.h
# End Source File
# Begin Source File

SOURCE=.\bhb\ipdataset.h
# End Source File
# Begin Source File

SOURCE=.\LeftView.h
# End Source File
# Begin Source File

SOURCE=.\bhb\logquery.h
# End Source File
# Begin Source File

SOURCE=.\MainClient.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\PpClearupEventCond.h
# End Source File
# Begin Source File

SOURCE=.\PpQnmClearup.h
# End Source File
# Begin Source File

SOURCE=.\PpQnmStatGeneral.h
# End Source File
# Begin Source File

SOURCE=.\PpQnmStatIpScan.h
# End Source File
# Begin Source File

SOURCE=.\PpQnmStatOthers.h
# End Source File
# Begin Source File

SOURCE=.\PpQnmStatPcInfo.h
# End Source File
# Begin Source File

SOURCE=.\PpQnmStatUsrInfo.h
# End Source File
# Begin Source File

SOURCE=.\PpQyExport.h
# End Source File
# Begin Source File

SOURCE=.\PpStatMessengerInfo.h
# End Source File
# Begin Source File

SOURCE=.\QyBrowseView.h
# End Source File
# Begin Source File

SOURCE=.\QyBulkset.h
# End Source File
# Begin Source File

SOURCE=.\QyChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\QyDialogBar.h
# End Source File
# Begin Source File

SOURCE=.\qyMc.h
# End Source File
# Begin Source File

SOURCE=.\qyMcDoc.h
# End Source File
# Begin Source File

SOURCE=.\QyMcRootChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\qyMcView.h
# End Source File
# Begin Source File

SOURCE=.\QyPlaySound.h
# End Source File
# Begin Source File

SOURCE=.\QyRcdset.h
# End Source File
# Begin Source File

SOURCE=.\QyRecordSound.h
# End Source File
# Begin Source File

SOURCE=.\QyStatic.h
# End Source File
# Begin Source File

SOURCE=.\QyVirtualListView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\Splash.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TestP.h
# End Source File
# Begin Source File

SOURCE=.\webbrowser2.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bak_idr_.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\btn1.ico
# End Source File
# Begin Source File

SOURCE=.\RES\dir.ico
# End Source File
# Begin Source File

SOURCE=.\res\FIND.BMP
# End Source File
# Begin Source File

SOURCE=.\res\graph9.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\RES\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\RES\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\RES\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\RES\idr_tray.ico
# End Source File
# Begin Source File

SOURCE=.\RES\IDR_TRAY_offline.ico
# End Source File
# Begin Source File

SOURCE=.\RES\IDR_TRAY_online.ico
# End Source File
# Begin Source File

SOURCE=.\res\largeico.bmp
# End Source File
# Begin Source File

SOURCE=.\res\myToolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\qnmSplash.bmp
# End Source File
# Begin Source File

SOURCE=.\res\qyMc.ico
# End Source File
# Begin Source File

SOURCE=.\res\qyMc.rc2
# End Source File
# Begin Source File

SOURCE=.\res\qyMcDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\refresh.bmp
# End Source File
# Begin Source File

SOURCE=.\res\small_bt.ico
# End Source File
# Begin Source File

SOURCE=.\res\smallico.bmp
# End Source File
# Begin Source File

SOURCE=.\Splsh16.bmp
# End Source File
# Begin Source File

SOURCE=.\res\stat.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# End Group
# Begin Group "qyPublic2"

# PROP Default_Filter ""
# End Group
# Begin Group "qyCommProc"

# PROP Default_Filter ""
# Begin Group "qyCommProcInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\qyCommProc\INCLUDE\qnmAssetsCommProc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qnmCommProc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\INCLUDE\qnmCommProc1.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\INCLUDE\qnmCommproc_netMc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\QnmDb.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qnmGuiCommProc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qnmHotKeys.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\INCLUDE\qnmPcComm.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qnmsCommProc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qnmSpCommProc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\INCLUDE\qnmSqlScripts.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qwmDjCommProc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qyCommProc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\INCLUDE\qyDynLib.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\INCLUDE\qyGuiCommProc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qyImcComm.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qyImcPublic.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qyModuleCommProc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\INCLUDE\qySharedQ.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qySnmpCommProc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\INCLUDE\qyWmComm.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\INCLUDE\traceLogA.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\qyCommProc\BTNST.CPP
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\genericqueue.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmAssetsTemp.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmChkCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmCommProc1.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\QnmDb.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmFwCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmGuiCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmHotKeys.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmOsAuditCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmsCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmSqlScripts.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmSqlScripts_mis.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmWarnCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qwmDjCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qwmDynFunc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qwmNetworkStatusCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qwmStreamCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyDmItemCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyImcLogFunc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyImcPublic.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyLangCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyModuleFunc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyMtSock.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\QyRestrictEdit.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qySharedQ.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyShowHintCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyShowInfoCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qySqlFunc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qySyncCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyTCharCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\tmpCntLib.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\tmpLib.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\traceLogA.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "qyCommProc_mis"

# PROP Default_Filter ""
# Begin Group "qyCommProc_mis_include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\qyCommProc_mis\include\mtSock_iOCP.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc_mis\include\qnmCommProc_mis.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc_mis\include\qyMsgFunc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc_mis\include\qyRtcCommProc.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\qyCommProc_mis\qnmCommProc_mis.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc_mis\qyMsgFunc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc_mis\qyWmComm_is.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "qyCustom"

# PROP Default_Filter ""
# Begin Group "qyCustomInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\qyCustom\INCLUDE\qnmAllHints.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCustom\include\qnmCustom.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCustom\include\qnmCustomComm.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCustom\include\qnmCustomGui.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCustom\include\qnmCustomSearch.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCustom\INCLUDE\qyCustom.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\qyCustom\qnmAllHints.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCustom\qnmCustom.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCustom\qnmCustomComm.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCustom\qnmCustomRegTool.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCustom\qnmCustomSearch.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCustom\qnmCustomStat.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCustom\qyCusResHelp.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCustom\qyCustom.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "qyCusResSrc"

# PROP Default_Filter ""
# Begin Group "qyCusResInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\qyCusResSrc\qyCusRes\include\qnmResDefs.h
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCusResSrc\qyCusRes\include\qyCusResCommon.h
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCusResSrc\qyCusRes\include\qyCusResTemp.h
# End Source File
# End Group
# End Group
# Begin Group "qyCommProc_open"

# PROP Default_Filter ""
# Begin Group "qyCommProc_open_include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\qyOpen\qyCommProc_open\include\qyCommProc_open.h
# End Source File
# Begin Source File

SOURCE=..\..\..\qyOpen\qyCommProc_open\include\qyCusGui.h
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section qyMc : {D30C1661-CDAF-11D0-8A3E-00C04FC9E26E}
# 	2:5:Class:CWebBrowser2
# 	2:10:HeaderFile:webbrowser2.h
# 	2:8:ImplFile:webbrowser2.cpp
# End Section
# Section qyMc : {8856F961-340A-11D0-A96B-00C04FD705A2}
# 	2:21:DefaultSinkHeaderFile:webbrowser2.h
# 	2:16:DefaultSinkClass:CWebBrowser2
# End Section
# Section qyMc : {72ADFD78-2C39-11D0-9903-00A0C91BC942}
# 	1:10:IDB_SPLASH:116
# 	2:21:SplashScreenInsertKey:4.0
# End Section
