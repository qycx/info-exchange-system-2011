# Microsoft Developer Studio Project File - Name="schedulerHelp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=schedulerHelp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "schedulerHelp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "schedulerHelp.mak" CFG="schedulerHelp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "schedulerHelp - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "schedulerHelp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "schedulerHelp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\Release\bin"
# PROP Intermediate_Dir "..\..\..\..\o\schedulerHelp\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SCHEDULERHELP_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyCommProc_mis\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /I "..\..\..\qyOpen\qyCommProc_open\Include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D WINVER=0x0500 /D "_USRDLL" /D "SCHEDULERHELP_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /FR /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 Netapi32.lib Advapi32.lib User32.lib qyPublic.lib qyEncLib.lib Spromeps.lib qyLicense.lib wsock32.lib libDes.lib SentinelKeys_md.lib /nologo /dll /machine:I386 /libpath:"..\..\..\..\Release\lib"

!ELSEIF  "$(CFG)" == "schedulerHelp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\Debug\bin"
# PROP Intermediate_Dir "..\..\..\..\o\schedulerHelp\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "SCHEDULERHELP_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyCommProc_mis\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /I "..\..\..\qyOpen\qyCommProc_open\Include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D WINVER=0x0500 /D "_USRDLL" /D "SCHEDULERHELP_EXPORTS" /D "_WINDLL" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Netapi32.lib Advapi32.lib User32.lib qyPublic.lib qyEncLib.lib Spromeps.lib qyLicense.lib wsock32.lib libDes.lib /nologo /dll /debug /machine:I386 /pdbtype:sept /libpath:"..\..\..\..\Debug\lib"

!ENDIF 

# Begin Target

# Name "schedulerHelp - Win32 Release"
# Name "schedulerHelp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\newawmChk.cpp
# End Source File
# Begin Source File

SOURCE=.\newawmChkTemp.cpp
# End Source File
# Begin Source File

SOURCE=.\schedulerHelp.cpp
# End Source File
# Begin Source File

SOURCE=.\schedulerHelp.rc
# End Source File
# Begin Source File

SOURCE=.\schedulerHelpProc.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\newawmChk.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\schedulerHelpProc.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\schedulerHelp.rc2
# End Source File
# End Group
# Begin Group "qyCommProc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\qyCommProc\qnmCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmOsAuditCommProc.cpp

!IF  "$(CFG)" == "schedulerHelp - Win32 Release"

!ELSEIF  "$(CFG)" == "schedulerHelp - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qwmDynFunc.cpp

!IF  "$(CFG)" == "schedulerHelp - Win32 Release"

!ELSEIF  "$(CFG)" == "schedulerHelp - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qwmNetworkStatusCommProc.cpp

!IF  "$(CFG)" == "schedulerHelp - Win32 Release"

!ELSEIF  "$(CFG)" == "schedulerHelp - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyDmItemCommProc.cpp

!IF  "$(CFG)" == "schedulerHelp - Win32 Release"

!ELSEIF  "$(CFG)" == "schedulerHelp - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyTCharCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\tmpLib.cpp

!IF  "$(CFG)" == "schedulerHelp - Win32 Release"

!ELSEIF  "$(CFG)" == "schedulerHelp - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\traceLogA.cpp

!IF  "$(CFG)" == "schedulerHelp - Win32 Release"

!ELSEIF  "$(CFG)" == "schedulerHelp - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# End Group
# Begin Group "qyMcPublic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\qymcPublic\qmCommonProc.cpp
# End Source File
# End Group
# Begin Group "qyCustom"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\qyCustom\qyCustom.cpp

!IF  "$(CFG)" == "schedulerHelp - Win32 Release"

!ELSEIF  "$(CFG)" == "schedulerHelp - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
