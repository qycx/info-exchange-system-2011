# Microsoft Developer Studio Project File - Name="qnmResp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=qnmResp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "qnmResp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "qnmResp.mak" CFG="qnmResp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "qnmResp - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "qnmResp - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "qnmResp - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\Release\bin"
# PROP Intermediate_Dir "..\..\..\..\o\qnmResp\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\qyPublic2\include" /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\tmpInclude" /I "..\..\qyCustom\include" /I "..\..\..\qyCusResSrc\qyCusRes\include" /I "..\..\qyCommProc\include" /I "..\..\qyCommProc_mis\include" /I "..\..\..\qyOpen\qyCommProc_open\Include" /D "NDEBUG" /D "_UNICODE" /D "UNICODE" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D WINVER=0x0500 /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 qyPublic.lib qyEncLib.lib qyLicense.lib Spromeps.lib libDes.lib SentinelKeys_md.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /machine:I386 /libpath:"..\..\..\..\Release\lib" /libpath:"..\..\..\..\others\winpcap\common"

!ELSEIF  "$(CFG)" == "qnmResp - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\Debug\bin"
# PROP Intermediate_Dir "..\..\..\..\o\qnmResp\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\qyPublic2\include" /I "..\..\..\qyOpen\qyCommProc_open\Include" /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\tmpInclude" /I "..\..\qyCustom\include" /I "..\..\..\qyCusResSrc\qyCusRes\include" /I "..\..\qyCommProc\include" /I "..\..\qyCommProc_mis\include" /D "_DEBUG" /D "_UNICODE" /D "UNICODE" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D WINVER=0x0500 /Fr /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 qyPublic.lib qyEncLib.lib qyLicense.lib Spromeps.lib libDes.lib /nologo /entry:"wWinMainCRTStartup" /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\..\..\..\Debug\lib" /libpath:"..\..\..\..\others\winpcap\common"

!ENDIF 

# Begin Target

# Name "qnmResp - Win32 Release"
# Name "qnmResp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "qyMcPublic"

# PROP Default_Filter ""
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

!IF  "$(CFG)" == "qnmResp - Win32 Release"

!ELSEIF  "$(CFG)" == "qnmResp - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\qymcPublic\qmStr.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\qnmResp.cpp
# End Source File
# Begin Source File

SOURCE=.\qnmResp.rc
# End Source File
# Begin Source File

SOURCE=.\QnmRespDaemon.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "qyMcInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\INCLUDE\qmStr.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\qnmResp.h
# End Source File
# Begin Source File

SOURCE=.\QnmRespDaemon.h
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

SOURCE=.\res\qnmResp.ico
# End Source File
# Begin Source File

SOURCE=.\res\qnmResp.rc2
# End Source File
# Begin Source File

SOURCE=.\res\qnmRespDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "qnmRespPublic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\qnmRespPublic\qnmRespProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\qnmRespPublic\qnmRespProc_netMc2.cpp
# End Source File
# Begin Source File

SOURCE=.\qnmRespPublic\qyPing.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\qnmRespPublic\winpcap_common.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "qnmRespInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\qnmRespCfg.h
# End Source File
# Begin Source File

SOURCE=.\include\qnmRespCommon.h
# End Source File
# Begin Source File

SOURCE=.\include\qyPing.h
# End Source File
# End Group
# Begin Group "qyCommProc"

# PROP Default_Filter ""
# Begin Group "qyCommProcInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\qyCommProc\include\qnmCommProc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qnmCustom.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\INCLUDE\qnmFwCommProc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\INCLUDE\qwmDynFunc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qyCommProc.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\qyCommProc\genericqueue.cpp
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
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmsCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmWarnCommProc.cpp
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

SOURCE=..\..\qyCommProc\qyArpProc.cpp
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

SOURCE=..\..\qyCommProc\qyGenericDaemon.cpp
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

SOURCE=..\..\qyCommProc\traceLogA.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "qyCustom"

# PROP Default_Filter ""
# Begin Group "qyCustomInclude"

# PROP Default_Filter ""
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

SOURCE=..\..\qyCustom\qyCustom.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "qyPublic2"

# PROP Default_Filter ""
# End Group
# Begin Group "qyCommProc_mis"

# PROP Default_Filter ""
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
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
