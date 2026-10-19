# Microsoft Developer Studio Project File - Name="awmIntraMon" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=awmIntraMon - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "awmIntraMon.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "awmIntraMon.mak" CFG="awmIntraMon - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "awmIntraMon - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "awmIntraMon - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "awmIntraMon - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\release\bin"
# PROP Intermediate_Dir "..\..\..\o\awmIntraMon\release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\awmExtInclude" /I "..\..\qyWMon\include" /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ws2_32.lib netapi32.lib qyPublic.lib qyEncLib.lib libDes.lib /nologo /subsystem:windows /machine:I386 /libpath:"..\..\..\Release\lib"

!ELSEIF  "$(CFG)" == "awmIntraMon - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\debug\bin"
# PROP Intermediate_Dir "..\..\..\o\awmIntraMon\debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\awmExtInclude" /I "..\..\qyWMon\include" /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\include" /I "include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ws2_32.lib netapi32.lib qyPublic.lib qyEncLib.lib libDes.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\..\..\Debug\lib"

!ENDIF 

# Begin Target

# Name "awmIntraMon - Win32 Release"
# Name "awmIntraMon - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "awmExtPublic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\awmExtPublic\aeHelpFunc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\awmExtPublic\aeNbtScan.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\awmExtPublic\awmExtFunc.c
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\awmExtPublic\awmUpnpFunc.cpp
# End Source File
# Begin Source File

SOURCE=..\awmExtPublic\qyBuildPkt.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "asrPublic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\asrPublic\commonfunc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Source File

SOURCE=.\awmIntraMon.cpp
# End Source File
# Begin Source File

SOURCE=.\awmIntraMon.rc
# End Source File
# Begin Source File

SOURCE=.\awmIntraMonMain.cpp
# End Source File
# Begin Source File

SOURCE=.\intraPingRas.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "awmExtInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\awmExtInclude\aeHelpFunc.h
# End Source File
# Begin Source File

SOURCE=..\awmExtInclude\awmExt.h
# End Source File
# Begin Source File

SOURCE=..\awmExtInclude\awmExtCfg.h
# End Source File
# Begin Source File

SOURCE=..\awmExtInclude\awmExtPrecomp.h
# End Source File
# Begin Source File

SOURCE=..\awmExtInclude\awmPING.H
# End Source File
# Begin Source File

SOURCE=..\awmExtInclude\IN_SYSTM.H
# End Source File
# Begin Source File

SOURCE=..\awmExtInclude\ip.h
# End Source File
# Begin Source File

SOURCE=..\awmExtInclude\ip_icmp.h
# End Source File
# Begin Source File

SOURCE=..\awmExtInclude\TCP.H
# End Source File
# Begin Source File

SOURCE=..\awmExtInclude\udp.h
# End Source File
# End Group
# Begin Group "awmInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\asrWMon\include\asrWMonCfg.h
# End Source File
# End Group
# Begin Group "asrInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\asrInclude\asrPrecomp.h
# End Source File
# Begin Source File

SOURCE=..\..\asrInclude\commondefs.h
# End Source File
# Begin Source File

SOURCE=..\..\asrInclude\commonDefs1.h
# End Source File
# Begin Source File

SOURCE=..\..\asrInclude\commonfunc.h
# End Source File
# End Group
# Begin Group "asrInclude1"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\asrInclude1\asrCfg.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\awmIntraMon.h
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

SOURCE=.\res\awmIntraMon.ico
# End Source File
# Begin Source File

SOURCE=.\res\awmIntraMon.rc2
# End Source File
# Begin Source File

SOURCE=.\res\awmIntraMonDoc.ico
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
