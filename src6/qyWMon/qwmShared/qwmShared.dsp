# Microsoft Developer Studio Project File - Name="qwmShared" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=qwmShared - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "qwmShared.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "qwmShared.mak" CFG="qwmShared - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "qwmShared - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "qwmShared - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "qwmShared - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\Release\lib"
# PROP Intermediate_Dir "..\..\..\..\o\qwmShared\Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\..\qyOpen\qyCommProc_open\include" /I "." /I "..\include" /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyCommProc_mis\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D WINVER=0x0400 /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\Debug\lib"
# PROP Intermediate_Dir "..\..\..\..\o\qwmShared\Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "." /I "..\include" /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyCommProc_mis\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /I "..\..\..\qyOpen\qyCommProc_open\include" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D WINVER=0x0400 /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "qwmShared - Win32 Release"
# Name "qwmShared - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# End Group
# Begin Group "qrtSecChk"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\qyRegTool\qrtSecChk\qwmChkDiskDrvFile.cpp
# End Source File
# Begin Source File

SOURCE=..\qyRegTool\qrtSecChk\qwmChkIe.cpp
# End Source File
# Begin Source File

SOURCE=..\qyRegTool\qrtSecChk\qwmChkInternet.cpp
# End Source File
# Begin Source File

SOURCE=..\qyRegTool\qrtSecChk\qwmChkNormalFile.cpp
# End Source File
# Begin Source File

SOURCE=..\qyRegTool\qrtSecChk\qwmChkOsInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\qyRegTool\qrtSecChk\qwmChkPcInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\qyRegTool\qrtSecChk\qwmChkProxyCfg.cpp
# End Source File
# Begin Source File

SOURCE=..\qyRegTool\qrtSecChk\qwmChkRas.cpp
# End Source File
# Begin Source File

SOURCE=..\qyRegTool\qrtSecChk\qwmChkRecent.cpp
# End Source File
# Begin Source File

SOURCE=..\qyRegTool\qrtSecChk\qwmChkRecycler.cpp
# End Source File
# Begin Source File

SOURCE=..\qyRegTool\qrtSecChk\qwmChkRemovableStorage.cpp
# End Source File
# Begin Source File

SOURCE=..\qyRegTool\qrtSecChk\qwmChkShare.cpp
# End Source File
# Begin Source File

SOURCE=..\qyRegTool\qrtSecChk\qwmChkSoftwareInstalled.cpp
# End Source File
# Begin Source File

SOURCE=..\qyRegTool\qrtSecChk\qwmChkUsrInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\qyRegTool\qrtSecChk\qwmGetAssetsInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\qyRegTool\qrtSecChk\qwmGetAssetsInfoW.cpp
# End Source File
# Begin Source File

SOURCE=..\qyRegTool\qrtSecChk\qwmSecChkProc.cpp
# End Source File
# Begin Source File

SOURCE=..\qyRegTool\qrtSecChk\qwmSecChkTemp.cpp
# End Source File
# End Group
# Begin Group "qwmPublic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\qwmPublic\cpuInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\delSelf.cpp
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\qwmFunc.cpp
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\qwmGetAssetFunc.cpp
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\qwmOutputFile.cpp
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\qwmRegProcHelp.cpp
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\qwmSockFunc.cpp
# End Source File
# End Group
# Begin Group "qyProjShare"

# PROP Default_Filter ""
# Begin Group "chkDisk"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\qyProjShare\chkDisk\diskIO.c
# End Source File
# Begin Source File

SOURCE=..\..\qyProjShare\chkDisk\error.c
# End Source File
# Begin Source File

SOURCE=..\..\qyProjShare\chkDisk\fatFs.c
# End Source File
# Begin Source File

SOURCE=..\..\qyProjShare\chkDisk\fatfs_dent.c
# End Source File
# Begin Source File

SOURCE=..\..\qyProjShare\chkDisk\fs_buf.c
# End Source File
# Begin Source File

SOURCE=..\..\qyProjShare\chkDisk\fs_data.c
# End Source File
# Begin Source File

SOURCE=..\..\qyProjShare\chkDisk\fs_dent.c
# End Source File
# Begin Source File

SOURCE=..\..\qyProjShare\chkDisk\fs_inode.c
# End Source File
# Begin Source File

SOURCE=..\..\qyProjShare\chkDisk\fs_io.c
# End Source File
# Begin Source File

SOURCE=..\..\qyProjShare\chkDisk\fs_open.c
# End Source File
# Begin Source File

SOURCE=..\..\qyProjShare\chkDisk\fs_types.c
# End Source File
# Begin Source File

SOURCE=..\..\qyProjShare\chkDisk\get.c
# End Source File
# Begin Source File

SOURCE=..\..\qyProjShare\chkDisk\ils.c
# End Source File
# Begin Source File

SOURCE=..\..\qyProjShare\chkDisk\mymalloc.c
# End Source File
# Begin Source File

SOURCE=..\..\qyProjShare\chkDisk\ntfs.c
# End Source File
# Begin Source File

SOURCE=..\..\qyProjShare\chkDisk\ntfs_dent.c
# End Source File
# Begin Source File

SOURCE=..\..\qyProjShare\chkDisk\split_at.c
# End Source File
# Begin Source File

SOURCE=..\..\qyProjShare\chkDisk\testDiskIOProc.c
# End Source File
# End Group
# End Group
# Begin Group "qyCommProc"

# PROP Default_Filter ""
# Begin Group "qyCommProcInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\qyCommProc\include\qnmHotKeys.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\qyCommProc\qnmAssetsCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmAssetsTemp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmChkCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmOsAuditCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmSockCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qwmHideProcessCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qwmNetworkStatusCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyCommProc.cpp
# End Source File
# End Group
# End Target
# End Project
