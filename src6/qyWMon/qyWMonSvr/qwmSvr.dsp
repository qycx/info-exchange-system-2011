# Microsoft Developer Studio Project File - Name="qwmSvr" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=qwmSvr - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "qwmSvr.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "qwmSvr.mak" CFG="qwmSvr - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "qwmSvr - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "qwmSvr - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "qwmSvr - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\Release\bin"
# PROP Intermediate_Dir "..\..\..\..\o\qwmSvr\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "." /I "..\include" /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyCommProc_mis\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /I "..\..\..\qyOpen\qyCommProc_open\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D WINVER=0x0400 /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib qyPublicStaticNoMfc.lib qyEncLibStaticNoMfc.lib wsock32.lib /nologo /subsystem:windows /machine:I386 /out:"..\..\..\..\Release\bin/qyWMonSvr2k.exe" /libpath:"..\..\..\..\Release\lib"

!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\Debug\bin"
# PROP Intermediate_Dir "..\..\..\..\o\qwmSvr\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "." /I "..\include" /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyCommProc_mis\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /I "..\..\..\qyOpen\qyCommProc_open\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D WINVER=0x0400 /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib qyPublicStaticNoMfc.lib qyEncLibStaticNoMfc.lib wsock32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\..\..\Debug\bin/qyWMonSvr2k.exe" /pdbtype:sept /libpath:"..\..\..\..\Debug\lib"

!ENDIF 

# Begin Target

# Name "qwmSvr - Win32 Release"
# Name "qwmSvr - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "misc"

# PROP Default_Filter ""
# Begin Group "config"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MISC\CONFIG\CONFIG.CPP
# End Source File
# End Group
# Begin Group "process_hop"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MISC\process_hop\process_hop.cpp
# End Source File
# End Group
# End Group
# Begin Group "libc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LIBC\strhandle.cpp
# End Source File
# End Group
# Begin Group "qwmProc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\qwmProc\asrWMonRas.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmProc\awmRegFunc.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmProc\getOpCmd.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmProc\queryAutoLogon.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmProc\qwmCapScreen.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmProc\qwmHideProcess.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmProc\qwmLogProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmProc\qwmProcDetectionResult.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmProc\qwmProcDevRule.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmProc\qwmProcDevRule1.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmProc\qwmStartHelp2.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmProc\qwmSvrFakeProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmProc\qwmThreadCollectUsrLog.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmProc\qwmThreadFileMon.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmProc\qwmThreadPcMon.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmProc\qwmThreadPrinterMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmProc\qwmThreadProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmProc\qwmThreadWndProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmProc\qwmUsrScript.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmProc\showNetShare.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmProc\sndNetStat.cpp
# End Source File
# End Group
# Begin Group "io"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\IO\io_simpletcp.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\Main.cpp
# End Source File
# Begin Source File

SOURCE=.\qyWMonSvr.rc
# End Source File
# Begin Source File

SOURCE=.\qyWMonSvr.rc2
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\include\asrWMon.h
# End Source File
# Begin Source File

SOURCE=..\include\asrWMonPrecomp.h
# End Source File
# Begin Source File

SOURCE=..\include\asrWMonRas.h
# End Source File
# Begin Source File

SOURCE=..\include\commandloop.h
# End Source File
# Begin Source File

SOURCE=..\include\commnet.h
# End Source File
# Begin Source File

SOURCE=..\include\config.h
# End Source File
# Begin Source File

SOURCE=..\include\cpuInfo.h
# End Source File
# Begin Source File

SOURCE=..\include\dll_load.h
# End Source File
# Begin Source File

SOURCE=..\include\main.h
# End Source File
# Begin Source File

SOURCE=..\include\ntScriptChk.h
# End Source File
# Begin Source File

SOURCE=..\include\perfdata.h
# End Source File
# Begin Source File

SOURCE=..\include\process_hop.h
# End Source File
# Begin Source File

SOURCE=..\include\pviewdat.h
# End Source File
# Begin Source File

SOURCE=..\include\qwmFunc.h
# End Source File
# Begin Source File

SOURCE=..\include\qwmRegistryFunc.h
# End Source File
# Begin Source File

SOURCE=..\include\qyRegToolProc.h
# End Source File
# Begin Source File

SOURCE=..\include\rasConn.h
# End Source File
# Begin Source File

SOURCE=..\include\strhandle.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\cursor1.cur
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

SOURCE=..\..\qyCommProc\include\qnmGuiCommProc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qnmPcComm.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qwmHideProcessCommProc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qwmNetworkStatusCommProc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qwmSvrChkCommProc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qyLangCommProc.h
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\include\qySnmpCommProc.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\qyCommProc\qnmAssetsCommProc.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmAssetsTemp.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmChkCommProc.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmCommProc.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmOsAuditCommProc.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmSockCommProc.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qwmDynFunc.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qwmHideProcessCommProc.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qwmNetworkStatusCommProc.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qwmRdCommProc.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyCommProc.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyDmItemCommProc.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qySyncCommProc.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyTCharCommProc.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\traceLogA.cpp
# SUBTRACT CPP /YX
# End Source File
# End Group
# Begin Group "qwmPublic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\qwmPublic\commandloop.cpp
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\cpuInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\Decrypt.cpp
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\devConProc.cpp
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\procNtPcAdapters.cpp
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\qwmDoReboot.cpp
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\qwmFunc.cpp
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\qwmNetworkStatus.cpp
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\qwmProc.cpp
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\qwmRegistryFunc.cpp
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\qwmTemp.CPP
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\qwmUsrScriptProc.cpp
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\showPcNetFlow.cpp
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\showPcProcess.cpp
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\showPcProcess1.CPP
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\showPcWindowsUpdatePolicy.cpp
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\sndEventLog.cpp
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\sndUsrInfo.cpp
# End Source File
# End Group
# Begin Group "qyCustom"

# PROP Default_Filter ""
# Begin Group "qyCustomInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\qyCustom\include\qnmCustomGui.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\qyCustom\qyCustom.cpp
# End Source File
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

SOURCE=..\qyRegTool\qrtSecChk\qwmChkNormalFile.cpp
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

SOURCE=..\qyRegTool\qrtSecChk\qwmChkShare.cpp
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
# End Group
# End Group
# End Target
# End Project
