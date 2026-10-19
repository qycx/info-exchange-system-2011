# Microsoft Developer Studio Project File - Name="awmChkSecurity" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=awmChkSecurity - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "awmChkSecurity.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "awmChkSecurity.mak" CFG="awmChkSecurity - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "awmChkSecurity - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "awmChkSecurity - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "awmChkSecurity - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\Release\bin"
# PROP Intermediate_Dir "..\..\..\..\o\awmChk\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /I "..\..\qyCommProc\include" /I "..\..\qyCommProc_mis\include" /I "..\..\..\qyOpen\qyCommProc_open\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D WINVER=0x0500 /FR /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /i "..\..\qyCommProc\include" /i "..\..\qyCustom\include" /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 netapi32.lib qyPublic.lib qyEncLib.lib Spromeps.lib qyLicense.lib libDes.lib SentinelKeys_md.lib /nologo /subsystem:windows /machine:I386 /out:"..\..\..\..\Release\bin/qnmScheduler.exe" /libpath:"..\..\..\..\Release\lib"

!ELSEIF  "$(CFG)" == "awmChkSecurity - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\Debug\bin"
# PROP Intermediate_Dir "..\..\..\..\o\awmChk\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /I "..\..\qyCommProc\include" /I "..\..\qyCommProc_mis\include" /I "..\..\..\qyOpen\qyCommProc_open\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D WINVER=0x0500 /Fr /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /i "..\..\qyCommProc\include" /i "..\..\qyCustom\include" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 netapi32.lib qyPublic.lib qyEncLib.lib Spromeps.lib qyLicense.lib libDes.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\..\..\Debug\bin/qnmScheduler.exe" /pdbtype:sept /libpath:"..\..\..\..\Debug\lib"

!ENDIF 

# Begin Target

# Name "awmChkSecurity - Win32 Release"
# Name "awmChkSecurity - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\awmChkSecurity.cpp
# End Source File
# Begin Source File

SOURCE=.\awmChkSecurity.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\awmChk.h
# End Source File
# Begin Source File

SOURCE=.\awmChkCfg.h
# End Source File
# Begin Source File

SOURCE=.\awmChkSecurity.h
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

SOURCE=.\res\awmChkSecurity.ico
# End Source File
# Begin Source File

SOURCE=.\res\awmChkSecurity.rc2
# End Source File
# Begin Source File

SOURCE=.\res\awmChkSecurityDoc.ico
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

SOURCE=..\..\qyCommProc\include\qyCommProc.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\qyCommProc\qnmCommProc.cpp

!IF  "$(CFG)" == "awmChkSecurity - Win32 Release"

!ELSEIF  "$(CFG)" == "awmChkSecurity - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmOsAuditCommProc.cpp

!IF  "$(CFG)" == "awmChkSecurity - Win32 Release"

!ELSEIF  "$(CFG)" == "awmChkSecurity - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qwmDynFunc.cpp

!IF  "$(CFG)" == "awmChkSecurity - Win32 Release"

!ELSEIF  "$(CFG)" == "awmChkSecurity - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qwmNetworkStatusCommProc.cpp

!IF  "$(CFG)" == "awmChkSecurity - Win32 Release"

!ELSEIF  "$(CFG)" == "awmChkSecurity - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyCommProc.cpp

!IF  "$(CFG)" == "awmChkSecurity - Win32 Release"

!ELSEIF  "$(CFG)" == "awmChkSecurity - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyDmItemCommProc.cpp

!IF  "$(CFG)" == "awmChkSecurity - Win32 Release"

!ELSEIF  "$(CFG)" == "awmChkSecurity - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyTCharCommProc.cpp

!IF  "$(CFG)" == "awmChkSecurity - Win32 Release"

!ELSEIF  "$(CFG)" == "awmChkSecurity - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\tmpLib.cpp

!IF  "$(CFG)" == "awmChkSecurity - Win32 Release"

!ELSEIF  "$(CFG)" == "awmChkSecurity - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\traceLogA.cpp

!IF  "$(CFG)" == "awmChkSecurity - Win32 Release"

!ELSEIF  "$(CFG)" == "awmChkSecurity - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# End Group
# Begin Group "qyMcPublic"

# PROP Default_Filter ""
# End Group
# Begin Group "qyCustom"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\qyCustom\qnmCustom.cpp

!IF  "$(CFG)" == "awmChkSecurity - Win32 Release"

!ELSEIF  "$(CFG)" == "awmChkSecurity - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\qyCustom\qyCustom.cpp

!IF  "$(CFG)" == "awmChkSecurity - Win32 Release"

!ELSEIF  "$(CFG)" == "awmChkSecurity - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
