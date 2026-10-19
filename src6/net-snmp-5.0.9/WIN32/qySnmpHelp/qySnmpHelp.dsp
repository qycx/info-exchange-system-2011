# Microsoft Developer Studio Project File - Name="qySnmpHelp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=qySnmpHelp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "qySnmpHelp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "qySnmpHelp.mak" CFG="qySnmpHelp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "qySnmpHelp - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "qySnmpHelp - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\..\Release\bin"
# PROP Intermediate_Dir "..\..\..\..\..\o\qySnmpHelp\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyCommProc_mis\include" /I "..\..\..\qyMc\include" /I "..\..\..\..\qyCusResSrc\qyCusRes\include" /I "..\..\..\tmpInclude" /I "..\..\..\..\qyOpen\qyCommProc_open\Include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D WINVER=0x0500 /FR /FD /c
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
# ADD LINK32 libsnmp.lib ws2_32.lib qyPublic.lib qyEncLib.lib Spromeps.lib qyLicense.lib libDes.lib SentinelKeys_md.lib /nologo /subsystem:windows /machine:I386 /libpath:"..\..\..\..\..\Release\lib"

!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\..\Debug\bin"
# PROP Intermediate_Dir "..\..\..\..\..\o\qySnmpHelp\Debug\"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyCommProc_mis\include" /I "..\..\..\qyMc\include" /I "..\..\..\..\qyCusResSrc\qyCusRes\include" /I "..\..\..\tmpInclude" /I "..\..\..\..\qyOpen\qyCommProc_open\Include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D WINVER=0x0500 /Fr /FD /GZ /c
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
# ADD LINK32 libsnmp.lib ws2_32.lib qyPublic.lib qyEncLib.lib Spromeps.lib qyLicense.lib libDes.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\..\..\..\..\Debug\lib"

!ENDIF 

# Begin Target

# Name "qySnmpHelp - Win32 Release"
# Name "qySnmpHelp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "qySnmpHelpPublic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\qySnmpHelpPublic\qySnmpCmdProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qySnmpHelpPublic\qySnmpDefs.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\qySnmpHelpPublic\qySnmpGet.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\qySnmpHelpPublic\qySnmpHelpProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\qySnmpHelpPublic\qySnmpScript.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"

!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\qySnmpHelpPublic\qySnmpSet.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\qySnmpHelpPublic\qySnmpWalk.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Source File

SOURCE=.\qySnmpHelp.cpp
# End Source File
# Begin Source File

SOURCE=.\qySnmpHelp.rc
# End Source File
# Begin Source File

SOURCE=.\QySnmpHelpProcDaemon.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "include"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\include\qySnmpHelpProc.h
# End Source File
# Begin Source File

SOURCE=.\include\qySnmpHelpProcCommon.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\qySnmpHelp.h
# End Source File
# Begin Source File

SOURCE=.\QySnmpHelpProcDaemon.h
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

SOURCE=.\res\qySnmpHelp.ico
# End Source File
# Begin Source File

SOURCE=.\res\qySnmpHelp.rc2
# End Source File
# Begin Source File

SOURCE=.\res\qySnmpHelpDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "qyMcPublic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\qyMc\qymcPublic\qmCommonDbFunc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\qyMc\qymcPublic\qmCommonFunc.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"

!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\qyMc\qymcPublic\qmSnmpProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "qyCustom"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\qyCustom\qnmCustom.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCustom\qnmCustomComm.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCustom\qyCustom.cpp
# End Source File
# End Group
# Begin Group "qyCommProc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\qyCommProc\genericqueue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qnmCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qnmCommProc1.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"

# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qnmOsAuditCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qnmsCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qnmWarnCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qwmDynFunc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qwmNetworkStatusCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qyCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qyDmItemCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qyGenericDaemon.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qyModuleFunc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qyShowInfoCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qySqlFunc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qySyncCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qyTCharCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\traceLogA.cpp
# End Source File
# End Group
# Begin Group "qyProjShare"

# PROP Default_Filter ""
# Begin Group "nbtScan"

# PROP Default_Filter ""
# Begin Group "nbtScanInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\qyProjShare\nbtScan\include\errors.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\qyProjShare\nbtScan\getopt.c
# End Source File
# Begin Source File

SOURCE=..\..\..\qyProjShare\nbtScan\list.c
# End Source File
# Begin Source File

SOURCE=..\..\..\qyProjShare\nbtScan\myNbtScan.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\qyProjShare\nbtScan\myNbtScanCommon.c
# End Source File
# Begin Source File

SOURCE=..\..\..\qyProjShare\nbtScan\nbtscan.c
# End Source File
# Begin Source File

SOURCE=..\..\..\qyProjShare\nbtScan\qyNbtScanProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\qyProjShare\nbtScan\range.c
# End Source File
# Begin Source File

SOURCE=..\..\..\qyProjShare\nbtScan\statusq.cpp
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
