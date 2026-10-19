# Microsoft Developer Studio Project File - Name="qwmHelp2" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=qwmHelp2 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "qwmHelp2.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "qwmHelp2.mak" CFG="qwmHelp2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "qwmHelp2 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "qwmHelp2 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "qwmHelp2 - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\Release\bin"
# PROP Intermediate_Dir "..\..\..\..\o\qwmHelp2\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QWMHELP2_EXPORTS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "." /I "..\include" /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D WINVER=0x0400 /D "_USRDLL" /D "QWMHELP2_EXPORTS" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib qyPublicStaticNoMfc.lib qyEncLibStaticNoMfc.lib wsock32.lib /nologo /dll /machine:I386 /libpath:"..\..\..\..\Release\lib"

!ELSEIF  "$(CFG)" == "qwmHelp2 - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\Debug\bin"
# PROP Intermediate_Dir "..\..\..\..\o\qwmHelp2\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QWMHELP2_EXPORTS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "." /I "..\include" /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D WINVER=0x0400 /D "_USRDLL" /D "QWMHELP2_EXPORTS" /FR /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib qyPublicStaticNoMfc.lib qyEncLibStaticNoMfc.lib wsock32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept /libpath:"..\..\..\..\Debug\lib"

!ENDIF 

# Begin Target

# Name "qwmHelp2 - Win32 Release"
# Name "qwmHelp2 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\qwmHelp2.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\qwmHelp2Proc.cpp

!IF  "$(CFG)" == "qwmHelp2 - Win32 Release"

!ELSEIF  "$(CFG)" == "qwmHelp2 - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "qyCommProc"

# PROP Default_Filter ""
# Begin Group "qyCommProcInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\qyCommProc\include\qwmHideProcessCommProc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\INCLUDE\qySyncCommProc.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\qyCommProc\qwmHideProcessCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyDmItemCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qySyncCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\traceLogA.cpp
# End Source File
# End Group
# Begin Group "qwmPublic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\qwmPublic\qwmUsrScriptProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
