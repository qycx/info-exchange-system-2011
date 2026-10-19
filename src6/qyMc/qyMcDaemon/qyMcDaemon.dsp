# Microsoft Developer Studio Project File - Name="qyMcDaemon" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=qyMcDaemon - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "qyMcDaemon.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "qyMcDaemon.mak" CFG="qyMcDaemon - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "qyMcDaemon - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "qyMcDaemon - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "qyMcDaemon - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\Release\bin"
# PROP Intermediate_Dir "..\..\..\..\o\qyMcDaemon\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /I "..\..\..\qyCusResSrc\qyCusRes\include" /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "." /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyCommProc\include" /I "..\..\qyCommProc_mis\include" /I "..\..\..\qyOpen\qyCommProc_open\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D WINVER=0x0500 /FR /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 SentinelKeys_md.lib qyPublic.lib qyEncLib.lib qyLicense.lib Spromeps.lib libDes.lib Ws2_32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /libpath:"..\..\..\..\Release\lib"

!ELSEIF  "$(CFG)" == "qyMcDaemon - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\Debug\bin"
# PROP Intermediate_Dir "..\..\..\..\o\qyMcDaemon\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /I "..\..\..\qyCusResSrc\qyCusRes\include" /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "." /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyCommProc\include" /I "..\..\qyCommProc_mis\include" /I "..\..\..\qyOpen\qyCommProc_open\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D WINVER=0x0500 /Fr /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 qyPublic.lib qyEncLib.lib qyLicense.lib Spromeps.lib libDes.lib Ws2_32.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\..\..\..\Debug\lib"

!ENDIF 

# Begin Target

# Name "qyMcDaemon - Win32 Release"
# Name "qyMcDaemon - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "qmdPublic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\qmdPublic\qmdCrypt.cpp
# End Source File
# Begin Source File

SOURCE=.\qmdPublic\qmdDbProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qmdPublic\qmdImcProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qmdPublic\qmdMain.cpp
# End Source File
# Begin Source File

SOURCE=.\qmdPublic\qmdMgrThreadProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qmdPublic\qmdMisProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qmdPublic\qmdNetMcProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qmdPublic\qmdProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qmdPublic\qmdProc_mis.cpp
# End Source File
# Begin Source File

SOURCE=.\qmdPublic\qmdProcessingThreadProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qmdPublic\qmdProcessingThreadsProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qmdPublic\qmdPutLogIntoDbThreadProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qmdPublic\qmdQnmProxyProc.cpp

!IF  "$(CFG)" == "qyMcDaemon - Win32 Release"

!ELSEIF  "$(CFG)" == "qyMcDaemon - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\qmdPublic\qmdSenderThreadProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qmdPublic\qmdSendRequestThreadProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qmdPublic\qmdWaitForCmdThreadProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qmdPublic\qnmHttpSvr.cpp
# End Source File
# End Group
# Begin Group "qyMcPublic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\qymcPublic\qmCommonDbFunc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\qymcPublic\qmCommondbFunc_mis.cpp
# End Source File
# Begin Source File

SOURCE=..\qymcPublic\qmCommonFunc.cpp

!IF  "$(CFG)" == "qyMcDaemon - Win32 Release"

!ELSEIF  "$(CFG)" == "qyMcDaemon - Win32 Debug"

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

SOURCE=..\qymcPublic\qmStr.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\DlgPasswdForStopMon.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcDaemon.cpp
# End Source File
# Begin Source File

SOURCE=.\qyMcDaemon.rc
# End Source File
# Begin Source File

SOURCE=.\QyMcDaemonObj.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "qmdInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\INCLUDE\qmdCommFunc_mis.h
# End Source File
# Begin Source File

SOURCE=.\INCLUDE\qmdCommFunc_netMc.h
# End Source File
# Begin Source File

SOURCE=.\include\qmdCommon.h
# End Source File
# Begin Source File

SOURCE=.\include\qmdMain.h
# End Source File
# Begin Source File

SOURCE=.\include\qmdProc.h
# End Source File
# End Group
# Begin Group "qmInclude"

# PROP Default_Filter ""
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

SOURCE=..\INCLUDE\qmStr.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\DlgPasswdForStopMon.h
# End Source File
# Begin Source File

SOURCE=.\qyMcDaemon.h
# End Source File
# Begin Source File

SOURCE=.\QyMcDaemonObj.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\qyMcDaemon.ico
# End Source File
# Begin Source File

SOURCE=.\res\qyMcDaemon.rc2
# End Source File
# Begin Source File

SOURCE=.\res\qyMcDaemonDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "qyPublicInclude"

# PROP Default_Filter ""
# Begin Group "qyCommonInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\qyPublic\qyCommon\include\qyDefs.h
# End Source File
# End Group
# End Group
# Begin Group "qyPublic2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\qyPublic2\qyLogHelpFunc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "qyCommProc"

# PROP Default_Filter ""
# Begin Group "include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\qyCommProc\INCLUDE\genericqueue.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qnmCommProc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qnmCustom.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qnmFwCommProc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qnmPrecomp.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\INCLUDE\qwmDynFunc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qwmNetworkStatusCommProc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qyCommProc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qyImcComm.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qyImcCommonCfg.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qyImcCommProc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qyImcLogFunc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qyImcSndObjs.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qyImcSql.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\INCLUDE\qyModuleFunc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\INCLUDE\qyMtSock.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\INCLUDE\qySyncCommProc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\INCLUDE\traceLogA.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\qyCommProc\genericqueue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmAssetsCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmAssetsTemp.cpp
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

SOURCE=..\..\qyCommProc\qnmFwCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmOsAuditCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmSockCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmWarnCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qwmDynFunc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qwmNetworkStatusCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyDmItemCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyGenericDaemon.cpp
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
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyModuleFunc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyMtSock.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qySharedQ.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyShowInfoCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qySqlFunc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qySyncCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyTCharCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\traceLogA.cpp
# End Source File
# End Group
# Begin Group "qyCommProc_mis"

# PROP Default_Filter ""
# Begin Group "include_qyCommProc_mis"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\qyCommProc_mis\include\mtSock_iOCP.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc_mis\include\qnmCommProc_mis.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\qyCommProc_mis\mtSock_iOCP.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc_mis\qnmCommProc_mis.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc_mis\qyMsgFunc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc_mis\qyMsgFunc_iocp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc_mis\qyWmComm_is.cpp
# End Source File
# End Group
# Begin Group "qyCustom"

# PROP Default_Filter ""
# Begin Group "qyCustomInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\qyCustom\include\qnmCustomComm.h
# End Source File
# End Group
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

SOURCE=..\..\qyCustom\qwmAllHints.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCustom\qyCustom.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
