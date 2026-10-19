# Microsoft Developer Studio Project File - Name="kk" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=kk - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "kk.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "kk.mak" CFG="kk - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "kk - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "kk - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "kk - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\Release\bin"
# PROP Intermediate_Dir "..\..\..\o\kk\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\asrComm\include" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyEncLib\include" /I "..\..\qycommproc\include" /I "..\..\qyCustom\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 netapi32.lib qyPublic.lib qyEncLib.lib mpr.lib rasapi32.lib Spromeps.lib qyLicense.lib libDes.lib /nologo /subsystem:windows /machine:I386 /libpath:"..\..\..\Release\lib"

!ELSEIF  "$(CFG)" == "kk - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\Debug\bin"
# PROP Intermediate_Dir "..\..\..\o\kk\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\asrComm\include" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyEncLib\include" /I "..\..\qycommproc\include" /I "..\..\qyCustom\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 netapi32.lib qyPublic.lib qyEncLib.lib mpr.lib rasapi32.lib Spromeps.lib qyLicense.lib libDes.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"..\..\..\Debug\lib"

!ENDIF 

# Begin Target

# Name "kk - Win32 Release"
# Name "kk - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\DlgStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTest.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTestQnm.cpp
# End Source File
# Begin Source File

SOURCE=.\kk.cpp
# End Source File
# Begin Source File

SOURCE=.\kk.rc
# End Source File
# Begin Source File

SOURCE=.\kkDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\kkView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\PpStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\Ps.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TestFile.cpp
# End Source File
# Begin Source File

SOURCE=.\testFunc.cpp
# End Source File
# Begin Source File

SOURCE=.\testLog.cpp

!IF  "$(CFG)" == "kk - Win32 Release"

!ELSEIF  "$(CFG)" == "kk - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TestP1.cpp
# End Source File
# Begin Source File

SOURCE=.\TestP2.cpp
# End Source File
# Begin Source File

SOURCE=.\TestP3.cpp
# End Source File
# Begin Source File

SOURCE=.\TestPs.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\DlgStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgTest.h
# End Source File
# Begin Source File

SOURCE=.\DlgTestQnm.h
# End Source File
# Begin Source File

SOURCE=.\kk.h
# End Source File
# Begin Source File

SOURCE=.\kkDoc.h
# End Source File
# Begin Source File

SOURCE=.\kkView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\PpStatus.h
# End Source File
# Begin Source File

SOURCE=.\Ps.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\testCommon.h
# End Source File
# Begin Source File

SOURCE=.\TestFile.h
# End Source File
# Begin Source File

SOURCE=.\TestP1.h
# End Source File
# Begin Source File

SOURCE=.\TestP2.h
# End Source File
# Begin Source File

SOURCE=.\TestP3.h
# End Source File
# Begin Source File

SOURCE=.\TestPs.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\RES\4.ico
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\RES\folder.ico
# End Source File
# Begin Source File

SOURCE=.\res\kk.ico
# End Source File
# Begin Source File

SOURCE=.\res\kk.rc2
# End Source File
# Begin Source File

SOURCE=.\res\kkDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "qycommproc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\qyCommProc\qnmCommProc.cpp

!IF  "$(CFG)" == "kk - Win32 Release"

!ELSEIF  "$(CFG)" == "kk - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyCommProc.cpp

!IF  "$(CFG)" == "kk - Win32 Release"

!ELSEIF  "$(CFG)" == "kk - Win32 Debug"

# SUBTRACT CPP /YX /Yc /Yu

!ENDIF 

# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
