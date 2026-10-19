# Microsoft Developer Studio Project File - Name="qwmRd" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=qwmRd - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "qwmRd.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "qwmRd.mak" CFG="qwmRd - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "qwmRd - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "qwmRd - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "qwmRd - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\..\Release\bin"
# PROP Intermediate_Dir "..\..\..\..\..\o\qwmRd\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QWMRD_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\include" /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyPublic2\include" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /I "..\..\qwmHelp3" /I ".." /I "..\.." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyPublic\include" /I "..\..\..\..\qyOpen\qyCommProc_open\include" /I "..\..\..\qyCommProc_mis\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QWMRD_EXPORTS" /D "__WIN32__" /D "_OMNITHREAD_DLL" /D _WIN32_WINNT=0x400 /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib qyPublicStaticNoMfc.lib qyEncLibStaticNoMfc.lib /nologo /dll /machine:I386 /libpath:"..\..\..\..\..\Release\lib"

!ELSEIF  "$(CFG)" == "qwmRd - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\..\Debug\bin"
# PROP Intermediate_Dir "..\..\..\..\..\o\qwmRd\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QWMRD_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\include" /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyPublic2\include" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /I "..\..\qwmHelp3" /I ".." /I "..\.." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyPublic\include" /I "..\..\..\..\qyOpen\qyCommProc_open\include" /I "..\..\..\qyCommProc_mis\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QWMRD_EXPORTS" /D "__WIN32__" /D "_OMNITHREAD_DLL" /D _WIN32_WINNT=0x400 /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 qyPublicStaticNoMfc.lib qyEncLibStaticNoMfc.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib wsock32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept /libpath:"..\..\..\..\..\Debug\lib"

!ENDIF 

# Begin Target

# Name "qwmRd - Win32 Release"
# Name "qwmRd - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\buildtime.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmRd.cpp
# End Source File
# Begin Source File

SOURCE=.\qwmRd.rc

!IF  "$(CFG)" == "qwmRd - Win32 Release"

!ELSEIF  "$(CFG)" == "qwmRd - Win32 Debug"

# ADD BASE RSC /l 0x804
# ADD RSC /l 0x409

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\rdAgent.cpp
# End Source File
# Begin Source File

SOURCE=.\rdConn.cpp
# End Source File
# Begin Source File

SOURCE=.\rdMenu.cpp
# End Source File
# Begin Source File

SOURCE=.\rfbRegion_win32.cpp
# End Source File
# Begin Source File

SOURCE=.\rfbRegion_X11.cxx
# End Source File
# Begin Source File

SOURCE=.\rfbUpdateTracker.cpp
# End Source File
# Begin Source File

SOURCE=.\stdhdrs.cpp
# End Source File
# Begin Source File

SOURCE=.\translate.cpp
# End Source File
# Begin Source File

SOURCE=.\vncabout.cpp
# End Source File
# Begin Source File

SOURCE=.\vncacceptdialog.cpp
# End Source File
# Begin Source File

SOURCE=.\vncauth.c
# End Source File
# Begin Source File

SOURCE=.\vncbuffer.cpp
# End Source File
# Begin Source File

SOURCE=.\vncdesktop.cpp
# End Source File
# Begin Source File

SOURCE=.\vncencodecorre.cpp
# End Source File
# Begin Source File

SOURCE=.\vncencodehext.cpp
# End Source File
# Begin Source File

SOURCE=.\vncencoder.cpp
# End Source File
# Begin Source File

SOURCE=.\vncencoderre.cpp
# End Source File
# Begin Source File

SOURCE=.\vncencodezrle.cxx
# End Source File
# Begin Source File

SOURCE=.\vnchttpconnect.cpp
# End Source File
# Begin Source File

SOURCE=.\vncinsthandler.cpp
# End Source File
# Begin Source File

SOURCE=.\vnckeymap.cpp
# End Source File
# Begin Source File

SOURCE=.\vncproperties.cpp
# End Source File
# Begin Source File

SOURCE=.\vncservice.cpp
# End Source File
# Begin Source File

SOURCE=.\vncsockconnect.cpp
# End Source File
# Begin Source File

SOURCE=.\vnctimedmsgbox.cpp
# End Source File
# Begin Source File

SOURCE=.\winvnc.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\keysymdef.h
# End Source File
# Begin Source File

SOURCE=.\minmax.h
# End Source File
# Begin Source File

SOURCE=.\qwmRd.h
# End Source File
# Begin Source File

SOURCE=.\rdAgent.h
# End Source File
# Begin Source File

SOURCE=.\rdConn.h
# End Source File
# Begin Source File

SOURCE=.\rdMenu.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\rfb.h
# End Source File
# Begin Source File

SOURCE=.\rfbMisc.h
# End Source File
# Begin Source File

SOURCE=.\rfbRect.h
# End Source File
# Begin Source File

SOURCE=.\rfbRegion.h
# End Source File
# Begin Source File

SOURCE=.\rfbRegion_win32.h
# End Source File
# Begin Source File

SOURCE=.\rfbRegion_X11.h
# End Source File
# Begin Source File

SOURCE=.\rfbUpdateTracker.h
# End Source File
# Begin Source File

SOURCE=.\stdhdrs.h
# End Source File
# Begin Source File

SOURCE=.\translate.h
# End Source File
# Begin Source File

SOURCE=.\vncabout.h
# End Source File
# Begin Source File

SOURCE=.\vncacceptdialog.h
# End Source File
# Begin Source File

SOURCE=.\vncauth.h
# End Source File
# Begin Source File

SOURCE=.\vncbuffer.h
# End Source File
# Begin Source File

SOURCE=.\vnccorbaconnect.h
# End Source File
# Begin Source File

SOURCE=.\vncdesktop.h
# End Source File
# Begin Source File

SOURCE=.\vncencodecorre.h
# End Source File
# Begin Source File

SOURCE=.\vncencodehext.h
# End Source File
# Begin Source File

SOURCE=.\vncencodemgr.h
# End Source File
# Begin Source File

SOURCE=.\vncencoder.h
# End Source File
# Begin Source File

SOURCE=.\vncencoderre.h
# End Source File
# Begin Source File

SOURCE=.\vncencodezrle.h
# End Source File
# Begin Source File

SOURCE=.\vnchttpconnect.h
# End Source File
# Begin Source File

SOURCE=.\vncinsthandler.h
# End Source File
# Begin Source File

SOURCE=.\vnckeymap.h
# End Source File
# Begin Source File

SOURCE=.\vncpasswd.h
# End Source File
# Begin Source File

SOURCE=.\vncproperties.h
# End Source File
# Begin Source File

SOURCE=.\vncservice.h
# End Source File
# Begin Source File

SOURCE=.\vncsockconnect.h
# End Source File
# Begin Source File

SOURCE=.\vnctimedmsgbox.h
# End Source File
# Begin Source File

SOURCE=.\vtypes.h
# End Source File
# Begin Source File

SOURCE=.\winvnc.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\vnc.bmp
# End Source File
# Begin Source File

SOURCE=.\res\winvnc.ico
# End Source File
# End Group
# Begin Group "qyCommProc"

# PROP Default_Filter ""
# Begin Group "qyCommProcInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\qyCommProc\INCLUDE\qwmHideProcessCommProc.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\qyCommProc\qnmCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qnmOsAuditCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qwmDynFunc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qwmHideProcessCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qwmNetworkStatusCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qwmRdCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qyCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qyDmItemCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qyTCharCommProc.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\traceLogA.cpp
# End Source File
# End Group
# Begin Group "rdPublic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\rdPublic\qysock.cpp
# End Source File
# End Group
# Begin Group "rdInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\include\qySock.h
# End Source File
# Begin Source File

SOURCE=..\..\include\vtypes.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\animatedmemoryimagesource.class
# End Source File
# Begin Source File

SOURCE=.\res\authenticationpanel.class
# End Source File
# Begin Source File

SOURCE=.\res\clipboardframe.class
# End Source File
# Begin Source File

SOURCE=.\res\descipher.class
# End Source File
# Begin Source File

SOURCE=.\res\optionsframe.class
# End Source File
# Begin Source File

SOURCE=.\res\rfbproto.class
# End Source File
# Begin Source File

SOURCE=.\res\vnccanvas.class
# End Source File
# Begin Source File

SOURCE=.\res\vncviewer.class
# End Source File
# Begin Source File

SOURCE=.\res\vncviewer.jar
# End Source File
# End Target
# End Project
