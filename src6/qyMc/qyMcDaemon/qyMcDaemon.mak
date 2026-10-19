# Microsoft Developer Studio Generated NMAKE File, Based on qyMcDaemon.dsp
!IF "$(CFG)" == ""
CFG=qyMcDaemon - Win32 Debug
!MESSAGE No configuration specified. Defaulting to qyMcDaemon - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "qyMcDaemon - Win32 Release" && "$(CFG)" != "qyMcDaemon - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "qyMcDaemon.mak" CFG="qyMcDaemon - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "qyMcDaemon - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "qyMcDaemon - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "qyMcDaemon - Win32 Release"

OUTDIR=.\..\..\..\Release\bin
INTDIR=.\..\..\..\o\qyMcDaemon\Release
# Begin Custom Macros
OutDir=.\..\..\..\Release\bin
# End Custom Macros

ALL : "$(OUTDIR)\qyMcDaemon.exe" "..\..\..\o\qyMcDaemon\Release\qyMcDaemon.pch" "$(OUTDIR)\qyMcDaemon.bsc"


CLEAN :
	-@erase "$(INTDIR)\DlgPasswdForStopMon.obj"
	-@erase "$(INTDIR)\DlgPasswdForStopMon.sbr"
	-@erase "$(INTDIR)\qmCommonDbFunc.obj"
	-@erase "$(INTDIR)\qmCommonDbFunc.sbr"
	-@erase "$(INTDIR)\qmCommonFunc.obj"
	-@erase "$(INTDIR)\qmCommonFunc.sbr"
	-@erase "$(INTDIR)\qmCommonProc.obj"
	-@erase "$(INTDIR)\qmCommonProc.sbr"
	-@erase "$(INTDIR)\qmdDbProc.obj"
	-@erase "$(INTDIR)\qmdDbProc.sbr"
	-@erase "$(INTDIR)\qmdImcProc.obj"
	-@erase "$(INTDIR)\qmdImcProc.sbr"
	-@erase "$(INTDIR)\qmdMain.obj"
	-@erase "$(INTDIR)\qmdMain.sbr"
	-@erase "$(INTDIR)\qmdMgrThreadProc.obj"
	-@erase "$(INTDIR)\qmdMgrThreadProc.sbr"
	-@erase "$(INTDIR)\qmdNetMcProc.obj"
	-@erase "$(INTDIR)\qmdNetMcProc.sbr"
	-@erase "$(INTDIR)\qmdProc.obj"
	-@erase "$(INTDIR)\qmdProc.sbr"
	-@erase "$(INTDIR)\qmdProcessingThreadProc.obj"
	-@erase "$(INTDIR)\qmdProcessingThreadProc.sbr"
	-@erase "$(INTDIR)\qmdProcessingThreadsProc.obj"
	-@erase "$(INTDIR)\qmdProcessingThreadsProc.sbr"
	-@erase "$(INTDIR)\qmdPutLogIntoDbThreadProc.obj"
	-@erase "$(INTDIR)\qmdPutLogIntoDbThreadProc.sbr"
	-@erase "$(INTDIR)\qmdQnmProxyProc.obj"
	-@erase "$(INTDIR)\qmdQnmProxyProc.sbr"
	-@erase "$(INTDIR)\qmdSenderThreadProc.obj"
	-@erase "$(INTDIR)\qmdSenderThreadProc.sbr"
	-@erase "$(INTDIR)\qmdSendRequestThreadProc.obj"
	-@erase "$(INTDIR)\qmdSendRequestThreadProc.sbr"
	-@erase "$(INTDIR)\qmdWaitForCmdThreadProc.obj"
	-@erase "$(INTDIR)\qmdWaitForCmdThreadProc.sbr"
	-@erase "$(INTDIR)\qnmAssetsCommProc.obj"
	-@erase "$(INTDIR)\qnmAssetsCommProc.sbr"
	-@erase "$(INTDIR)\qnmAssetsTemp.obj"
	-@erase "$(INTDIR)\qnmAssetsTemp.sbr"
	-@erase "$(INTDIR)\qnmCommProc.obj"
	-@erase "$(INTDIR)\qnmCommProc.sbr"
	-@erase "$(INTDIR)\qnmCommProc1.obj"
	-@erase "$(INTDIR)\qnmCommProc1.sbr"
	-@erase "$(INTDIR)\qnmCustom.obj"
	-@erase "$(INTDIR)\qnmCustom.sbr"
	-@erase "$(INTDIR)\qnmCustomComm.obj"
	-@erase "$(INTDIR)\qnmCustomComm.sbr"
	-@erase "$(INTDIR)\qnmCustomRegTool.obj"
	-@erase "$(INTDIR)\qnmCustomRegTool.sbr"
	-@erase "$(INTDIR)\qnmFwCommProc.obj"
	-@erase "$(INTDIR)\qnmFwCommProc.sbr"
	-@erase "$(INTDIR)\qnmHttpSvr.obj"
	-@erase "$(INTDIR)\qnmHttpSvr.sbr"
	-@erase "$(INTDIR)\qnmOsAuditCommProc.obj"
	-@erase "$(INTDIR)\qnmOsAuditCommProc.sbr"
	-@erase "$(INTDIR)\qnmWarnCommProc.obj"
	-@erase "$(INTDIR)\qnmWarnCommProc.sbr"
	-@erase "$(INTDIR)\qwmAllHints.obj"
	-@erase "$(INTDIR)\qwmAllHints.sbr"
	-@erase "$(INTDIR)\qwmNetworkStatusCommProc.obj"
	-@erase "$(INTDIR)\qwmNetworkStatusCommProc.sbr"
	-@erase "$(INTDIR)\qyCommFunc.obj"
	-@erase "$(INTDIR)\qyCommFunc.sbr"
	-@erase "$(INTDIR)\qyCommProc.obj"
	-@erase "$(INTDIR)\qyCommProc.sbr"
	-@erase "$(INTDIR)\qyCustom.obj"
	-@erase "$(INTDIR)\qyCustom.sbr"
	-@erase "$(INTDIR)\qyImcLogFunc.obj"
	-@erase "$(INTDIR)\qyImcLogFunc.sbr"
	-@erase "$(INTDIR)\qyImcPublic.obj"
	-@erase "$(INTDIR)\qyImcPublic.sbr"
	-@erase "$(INTDIR)\qyLogHelpFunc.obj"
	-@erase "$(INTDIR)\qyLogHelpFunc.sbr"
	-@erase "$(INTDIR)\qyMcDaemon.obj"
	-@erase "$(INTDIR)\qyMcDaemon.pch"
	-@erase "$(INTDIR)\qyMcDaemon.res"
	-@erase "$(INTDIR)\qyMcDaemon.sbr"
	-@erase "$(INTDIR)\QyMcDaemonObj.obj"
	-@erase "$(INTDIR)\QyMcDaemonObj.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\qyMcDaemon.bsc"
	-@erase "$(OUTDIR)\qyMcDaemon.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\qyMcDaemon.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qyMcDaemon.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\qmdDbProc.sbr" \
	"$(INTDIR)\qmdImcProc.sbr" \
	"$(INTDIR)\qmdMain.sbr" \
	"$(INTDIR)\qmdMgrThreadProc.sbr" \
	"$(INTDIR)\qmdNetMcProc.sbr" \
	"$(INTDIR)\qmdProc.sbr" \
	"$(INTDIR)\qmdProcessingThreadProc.sbr" \
	"$(INTDIR)\qmdProcessingThreadsProc.sbr" \
	"$(INTDIR)\qmdPutLogIntoDbThreadProc.sbr" \
	"$(INTDIR)\qmdQnmProxyProc.sbr" \
	"$(INTDIR)\qmdSenderThreadProc.sbr" \
	"$(INTDIR)\qmdSendRequestThreadProc.sbr" \
	"$(INTDIR)\qmdWaitForCmdThreadProc.sbr" \
	"$(INTDIR)\qnmHttpSvr.sbr" \
	"$(INTDIR)\qmCommonDbFunc.sbr" \
	"$(INTDIR)\qmCommonFunc.sbr" \
	"$(INTDIR)\qmCommonProc.sbr" \
	"$(INTDIR)\DlgPasswdForStopMon.sbr" \
	"$(INTDIR)\qyMcDaemon.sbr" \
	"$(INTDIR)\QyMcDaemonObj.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\qyCommFunc.sbr" \
	"$(INTDIR)\qyLogHelpFunc.sbr" \
	"$(INTDIR)\qnmAssetsCommProc.sbr" \
	"$(INTDIR)\qnmAssetsTemp.sbr" \
	"$(INTDIR)\qnmCommProc.sbr" \
	"$(INTDIR)\qnmCommProc1.sbr" \
	"$(INTDIR)\qnmFwCommProc.sbr" \
	"$(INTDIR)\qnmOsAuditCommProc.sbr" \
	"$(INTDIR)\qnmWarnCommProc.sbr" \
	"$(INTDIR)\qwmNetworkStatusCommProc.sbr" \
	"$(INTDIR)\qyCommProc.sbr" \
	"$(INTDIR)\qyImcLogFunc.sbr" \
	"$(INTDIR)\qyImcPublic.sbr" \
	"$(INTDIR)\qnmCustom.sbr" \
	"$(INTDIR)\qnmCustomComm.sbr" \
	"$(INTDIR)\qnmCustomRegTool.sbr" \
	"$(INTDIR)\qwmAllHints.sbr" \
	"$(INTDIR)\qyCustom.sbr"

"$(OUTDIR)\qyMcDaemon.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=qyPublic.lib qyEncLib.lib qyLicense.lib Spromeps.lib libDes.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\qyMcDaemon.pdb" /machine:I386 /out:"$(OUTDIR)\qyMcDaemon.exe" /libpath:"..\..\..\Release\lib" 
LINK32_OBJS= \
	"$(INTDIR)\qmdDbProc.obj" \
	"$(INTDIR)\qmdImcProc.obj" \
	"$(INTDIR)\qmdMain.obj" \
	"$(INTDIR)\qmdMgrThreadProc.obj" \
	"$(INTDIR)\qmdNetMcProc.obj" \
	"$(INTDIR)\qmdProc.obj" \
	"$(INTDIR)\qmdProcessingThreadProc.obj" \
	"$(INTDIR)\qmdProcessingThreadsProc.obj" \
	"$(INTDIR)\qmdPutLogIntoDbThreadProc.obj" \
	"$(INTDIR)\qmdQnmProxyProc.obj" \
	"$(INTDIR)\qmdSenderThreadProc.obj" \
	"$(INTDIR)\qmdSendRequestThreadProc.obj" \
	"$(INTDIR)\qmdWaitForCmdThreadProc.obj" \
	"$(INTDIR)\qnmHttpSvr.obj" \
	"$(INTDIR)\qmCommonDbFunc.obj" \
	"$(INTDIR)\qmCommonFunc.obj" \
	"$(INTDIR)\qmCommonProc.obj" \
	"$(INTDIR)\DlgPasswdForStopMon.obj" \
	"$(INTDIR)\qyMcDaemon.obj" \
	"$(INTDIR)\QyMcDaemonObj.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\qyCommFunc.obj" \
	"$(INTDIR)\qyLogHelpFunc.obj" \
	"$(INTDIR)\qnmAssetsCommProc.obj" \
	"$(INTDIR)\qnmAssetsTemp.obj" \
	"$(INTDIR)\qnmCommProc.obj" \
	"$(INTDIR)\qnmCommProc1.obj" \
	"$(INTDIR)\qnmFwCommProc.obj" \
	"$(INTDIR)\qnmOsAuditCommProc.obj" \
	"$(INTDIR)\qnmWarnCommProc.obj" \
	"$(INTDIR)\qwmNetworkStatusCommProc.obj" \
	"$(INTDIR)\qyCommProc.obj" \
	"$(INTDIR)\qyImcLogFunc.obj" \
	"$(INTDIR)\qyImcPublic.obj" \
	"$(INTDIR)\qnmCustom.obj" \
	"$(INTDIR)\qnmCustomComm.obj" \
	"$(INTDIR)\qnmCustomRegTool.obj" \
	"$(INTDIR)\qwmAllHints.obj" \
	"$(INTDIR)\qyCustom.obj" \
	"$(INTDIR)\qyMcDaemon.res"

"$(OUTDIR)\qyMcDaemon.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "qyMcDaemon - Win32 Debug"

OUTDIR=.\..\..\..\Debug\bin
INTDIR=.\..\..\..\o\qyMcDaemon\Debug
# Begin Custom Macros
OutDir=.\..\..\..\Debug\bin
# End Custom Macros

ALL : "$(OUTDIR)\qyMcDaemon.exe" "..\..\..\o\qyMcDaemon\Debug\qyMcDaemon.pch" "$(OUTDIR)\qyMcDaemon.bsc"


CLEAN :
	-@erase "$(INTDIR)\DlgPasswdForStopMon.obj"
	-@erase "$(INTDIR)\DlgPasswdForStopMon.sbr"
	-@erase "$(INTDIR)\qmCommonDbFunc.obj"
	-@erase "$(INTDIR)\qmCommonDbFunc.sbr"
	-@erase "$(INTDIR)\qmCommonFunc.obj"
	-@erase "$(INTDIR)\qmCommonFunc.sbr"
	-@erase "$(INTDIR)\qmCommonProc.obj"
	-@erase "$(INTDIR)\qmCommonProc.sbr"
	-@erase "$(INTDIR)\qmdDbProc.obj"
	-@erase "$(INTDIR)\qmdDbProc.sbr"
	-@erase "$(INTDIR)\qmdImcProc.obj"
	-@erase "$(INTDIR)\qmdImcProc.sbr"
	-@erase "$(INTDIR)\qmdMain.obj"
	-@erase "$(INTDIR)\qmdMain.sbr"
	-@erase "$(INTDIR)\qmdMgrThreadProc.obj"
	-@erase "$(INTDIR)\qmdMgrThreadProc.sbr"
	-@erase "$(INTDIR)\qmdNetMcProc.obj"
	-@erase "$(INTDIR)\qmdNetMcProc.sbr"
	-@erase "$(INTDIR)\qmdProc.obj"
	-@erase "$(INTDIR)\qmdProc.sbr"
	-@erase "$(INTDIR)\qmdProcessingThreadProc.obj"
	-@erase "$(INTDIR)\qmdProcessingThreadProc.sbr"
	-@erase "$(INTDIR)\qmdProcessingThreadsProc.obj"
	-@erase "$(INTDIR)\qmdProcessingThreadsProc.sbr"
	-@erase "$(INTDIR)\qmdPutLogIntoDbThreadProc.obj"
	-@erase "$(INTDIR)\qmdPutLogIntoDbThreadProc.sbr"
	-@erase "$(INTDIR)\qmdQnmProxyProc.obj"
	-@erase "$(INTDIR)\qmdQnmProxyProc.sbr"
	-@erase "$(INTDIR)\qmdSenderThreadProc.obj"
	-@erase "$(INTDIR)\qmdSenderThreadProc.sbr"
	-@erase "$(INTDIR)\qmdSendRequestThreadProc.obj"
	-@erase "$(INTDIR)\qmdSendRequestThreadProc.sbr"
	-@erase "$(INTDIR)\qmdWaitForCmdThreadProc.obj"
	-@erase "$(INTDIR)\qmdWaitForCmdThreadProc.sbr"
	-@erase "$(INTDIR)\qnmAssetsCommProc.obj"
	-@erase "$(INTDIR)\qnmAssetsCommProc.sbr"
	-@erase "$(INTDIR)\qnmAssetsTemp.obj"
	-@erase "$(INTDIR)\qnmAssetsTemp.sbr"
	-@erase "$(INTDIR)\qnmCommProc.obj"
	-@erase "$(INTDIR)\qnmCommProc.sbr"
	-@erase "$(INTDIR)\qnmCommProc1.obj"
	-@erase "$(INTDIR)\qnmCommProc1.sbr"
	-@erase "$(INTDIR)\qnmCustom.obj"
	-@erase "$(INTDIR)\qnmCustom.sbr"
	-@erase "$(INTDIR)\qnmCustomComm.obj"
	-@erase "$(INTDIR)\qnmCustomComm.sbr"
	-@erase "$(INTDIR)\qnmCustomRegTool.obj"
	-@erase "$(INTDIR)\qnmCustomRegTool.sbr"
	-@erase "$(INTDIR)\qnmFwCommProc.obj"
	-@erase "$(INTDIR)\qnmFwCommProc.sbr"
	-@erase "$(INTDIR)\qnmHttpSvr.obj"
	-@erase "$(INTDIR)\qnmHttpSvr.sbr"
	-@erase "$(INTDIR)\qnmOsAuditCommProc.obj"
	-@erase "$(INTDIR)\qnmOsAuditCommProc.sbr"
	-@erase "$(INTDIR)\qnmWarnCommProc.obj"
	-@erase "$(INTDIR)\qnmWarnCommProc.sbr"
	-@erase "$(INTDIR)\qwmAllHints.obj"
	-@erase "$(INTDIR)\qwmAllHints.sbr"
	-@erase "$(INTDIR)\qwmNetworkStatusCommProc.obj"
	-@erase "$(INTDIR)\qwmNetworkStatusCommProc.sbr"
	-@erase "$(INTDIR)\qyCommFunc.obj"
	-@erase "$(INTDIR)\qyCommFunc.sbr"
	-@erase "$(INTDIR)\qyCommProc.obj"
	-@erase "$(INTDIR)\qyCommProc.sbr"
	-@erase "$(INTDIR)\qyCustom.obj"
	-@erase "$(INTDIR)\qyCustom.sbr"
	-@erase "$(INTDIR)\qyImcLogFunc.obj"
	-@erase "$(INTDIR)\qyImcLogFunc.sbr"
	-@erase "$(INTDIR)\qyImcPublic.obj"
	-@erase "$(INTDIR)\qyImcPublic.sbr"
	-@erase "$(INTDIR)\qyLogHelpFunc.obj"
	-@erase "$(INTDIR)\qyLogHelpFunc.sbr"
	-@erase "$(INTDIR)\qyMcDaemon.obj"
	-@erase "$(INTDIR)\qyMcDaemon.pch"
	-@erase "$(INTDIR)\qyMcDaemon.res"
	-@erase "$(INTDIR)\qyMcDaemon.sbr"
	-@erase "$(INTDIR)\QyMcDaemonObj.obj"
	-@erase "$(INTDIR)\QyMcDaemonObj.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\qyMcDaemon.bsc"
	-@erase "$(OUTDIR)\qyMcDaemon.exe"
	-@erase "$(OUTDIR)\qyMcDaemon.ilk"
	-@erase "$(OUTDIR)\qyMcDaemon.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC=rc.exe
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\qyMcDaemon.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qyMcDaemon.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\qmdDbProc.sbr" \
	"$(INTDIR)\qmdImcProc.sbr" \
	"$(INTDIR)\qmdMain.sbr" \
	"$(INTDIR)\qmdMgrThreadProc.sbr" \
	"$(INTDIR)\qmdNetMcProc.sbr" \
	"$(INTDIR)\qmdProc.sbr" \
	"$(INTDIR)\qmdProcessingThreadProc.sbr" \
	"$(INTDIR)\qmdProcessingThreadsProc.sbr" \
	"$(INTDIR)\qmdPutLogIntoDbThreadProc.sbr" \
	"$(INTDIR)\qmdQnmProxyProc.sbr" \
	"$(INTDIR)\qmdSenderThreadProc.sbr" \
	"$(INTDIR)\qmdSendRequestThreadProc.sbr" \
	"$(INTDIR)\qmdWaitForCmdThreadProc.sbr" \
	"$(INTDIR)\qnmHttpSvr.sbr" \
	"$(INTDIR)\qmCommonDbFunc.sbr" \
	"$(INTDIR)\qmCommonFunc.sbr" \
	"$(INTDIR)\qmCommonProc.sbr" \
	"$(INTDIR)\DlgPasswdForStopMon.sbr" \
	"$(INTDIR)\qyMcDaemon.sbr" \
	"$(INTDIR)\QyMcDaemonObj.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\qyCommFunc.sbr" \
	"$(INTDIR)\qyLogHelpFunc.sbr" \
	"$(INTDIR)\qnmAssetsCommProc.sbr" \
	"$(INTDIR)\qnmAssetsTemp.sbr" \
	"$(INTDIR)\qnmCommProc.sbr" \
	"$(INTDIR)\qnmCommProc1.sbr" \
	"$(INTDIR)\qnmFwCommProc.sbr" \
	"$(INTDIR)\qnmOsAuditCommProc.sbr" \
	"$(INTDIR)\qnmWarnCommProc.sbr" \
	"$(INTDIR)\qwmNetworkStatusCommProc.sbr" \
	"$(INTDIR)\qyCommProc.sbr" \
	"$(INTDIR)\qyImcLogFunc.sbr" \
	"$(INTDIR)\qyImcPublic.sbr" \
	"$(INTDIR)\qnmCustom.sbr" \
	"$(INTDIR)\qnmCustomComm.sbr" \
	"$(INTDIR)\qnmCustomRegTool.sbr" \
	"$(INTDIR)\qwmAllHints.sbr" \
	"$(INTDIR)\qyCustom.sbr"

"$(OUTDIR)\qyMcDaemon.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=qyPublic.lib qyEncLib.lib qyLicense.lib Spromeps.lib libDes.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\qyMcDaemon.pdb" /debug /machine:I386 /out:"$(OUTDIR)\qyMcDaemon.exe" /pdbtype:sept /libpath:"..\..\..\Debug\lib" 
LINK32_OBJS= \
	"$(INTDIR)\qmdDbProc.obj" \
	"$(INTDIR)\qmdImcProc.obj" \
	"$(INTDIR)\qmdMain.obj" \
	"$(INTDIR)\qmdMgrThreadProc.obj" \
	"$(INTDIR)\qmdNetMcProc.obj" \
	"$(INTDIR)\qmdProc.obj" \
	"$(INTDIR)\qmdProcessingThreadProc.obj" \
	"$(INTDIR)\qmdProcessingThreadsProc.obj" \
	"$(INTDIR)\qmdPutLogIntoDbThreadProc.obj" \
	"$(INTDIR)\qmdQnmProxyProc.obj" \
	"$(INTDIR)\qmdSenderThreadProc.obj" \
	"$(INTDIR)\qmdSendRequestThreadProc.obj" \
	"$(INTDIR)\qmdWaitForCmdThreadProc.obj" \
	"$(INTDIR)\qnmHttpSvr.obj" \
	"$(INTDIR)\qmCommonDbFunc.obj" \
	"$(INTDIR)\qmCommonFunc.obj" \
	"$(INTDIR)\qmCommonProc.obj" \
	"$(INTDIR)\DlgPasswdForStopMon.obj" \
	"$(INTDIR)\qyMcDaemon.obj" \
	"$(INTDIR)\QyMcDaemonObj.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\qyCommFunc.obj" \
	"$(INTDIR)\qyLogHelpFunc.obj" \
	"$(INTDIR)\qnmAssetsCommProc.obj" \
	"$(INTDIR)\qnmAssetsTemp.obj" \
	"$(INTDIR)\qnmCommProc.obj" \
	"$(INTDIR)\qnmCommProc1.obj" \
	"$(INTDIR)\qnmFwCommProc.obj" \
	"$(INTDIR)\qnmOsAuditCommProc.obj" \
	"$(INTDIR)\qnmWarnCommProc.obj" \
	"$(INTDIR)\qwmNetworkStatusCommProc.obj" \
	"$(INTDIR)\qyCommProc.obj" \
	"$(INTDIR)\qyImcLogFunc.obj" \
	"$(INTDIR)\qyImcPublic.obj" \
	"$(INTDIR)\qnmCustom.obj" \
	"$(INTDIR)\qnmCustomComm.obj" \
	"$(INTDIR)\qnmCustomRegTool.obj" \
	"$(INTDIR)\qwmAllHints.obj" \
	"$(INTDIR)\qyCustom.obj" \
	"$(INTDIR)\qyMcDaemon.res"

"$(OUTDIR)\qyMcDaemon.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("qyMcDaemon.dep")
!INCLUDE "qyMcDaemon.dep"
!ELSE 
!MESSAGE Warning: cannot find "qyMcDaemon.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "qyMcDaemon - Win32 Release" || "$(CFG)" == "qyMcDaemon - Win32 Debug"
SOURCE=.\qmdPublic\qmdDbProc.cpp

"$(INTDIR)\qmdDbProc.obj"	"$(INTDIR)\qmdDbProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qmdPublic\qmdImcProc.cpp

"$(INTDIR)\qmdImcProc.obj"	"$(INTDIR)\qmdImcProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qmdPublic\qmdMain.cpp

"$(INTDIR)\qmdMain.obj"	"$(INTDIR)\qmdMain.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qmdPublic\qmdMgrThreadProc.cpp

"$(INTDIR)\qmdMgrThreadProc.obj"	"$(INTDIR)\qmdMgrThreadProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qmdPublic\qmdNetMcProc.cpp

"$(INTDIR)\qmdNetMcProc.obj"	"$(INTDIR)\qmdNetMcProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qmdPublic\qmdProc.cpp

"$(INTDIR)\qmdProc.obj"	"$(INTDIR)\qmdProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qmdPublic\qmdProcessingThreadProc.cpp

"$(INTDIR)\qmdProcessingThreadProc.obj"	"$(INTDIR)\qmdProcessingThreadProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qmdPublic\qmdProcessingThreadsProc.cpp

"$(INTDIR)\qmdProcessingThreadsProc.obj"	"$(INTDIR)\qmdProcessingThreadsProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qmdPublic\qmdPutLogIntoDbThreadProc.cpp

"$(INTDIR)\qmdPutLogIntoDbThreadProc.obj"	"$(INTDIR)\qmdPutLogIntoDbThreadProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qmdPublic\qmdQnmProxyProc.cpp

!IF  "$(CFG)" == "qyMcDaemon - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qmdQnmProxyProc.obj"	"$(INTDIR)\qmdQnmProxyProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMcDaemon - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qmdQnmProxyProc.obj"	"$(INTDIR)\qmdQnmProxyProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\qmdPublic\qmdSenderThreadProc.cpp

"$(INTDIR)\qmdSenderThreadProc.obj"	"$(INTDIR)\qmdSenderThreadProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qmdPublic\qmdSendRequestThreadProc.cpp

"$(INTDIR)\qmdSendRequestThreadProc.obj"	"$(INTDIR)\qmdSendRequestThreadProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qmdPublic\qmdWaitForCmdThreadProc.cpp

"$(INTDIR)\qmdWaitForCmdThreadProc.obj"	"$(INTDIR)\qmdWaitForCmdThreadProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\qmdPublic\qnmHttpSvr.cpp

"$(INTDIR)\qnmHttpSvr.obj"	"$(INTDIR)\qnmHttpSvr.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\qymcPublic\qmCommonDbFunc.cpp

!IF  "$(CFG)" == "qyMcDaemon - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qmCommonDbFunc.obj"	"$(INTDIR)\qmCommonDbFunc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMcDaemon - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qmCommonDbFunc.obj"	"$(INTDIR)\qmCommonDbFunc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\qymcPublic\qmCommonFunc.cpp

!IF  "$(CFG)" == "qyMcDaemon - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qmCommonFunc.obj"	"$(INTDIR)\qmCommonFunc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMcDaemon - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qmCommonFunc.obj"	"$(INTDIR)\qmCommonFunc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\qymcPublic\qmCommonProc.cpp

"$(INTDIR)\qmCommonProc.obj"	"$(INTDIR)\qmCommonProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\DlgPasswdForStopMon.cpp

"$(INTDIR)\DlgPasswdForStopMon.obj"	"$(INTDIR)\DlgPasswdForStopMon.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\qyMcDaemon.cpp

"$(INTDIR)\qyMcDaemon.obj"	"$(INTDIR)\qyMcDaemon.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\qyMcDaemon.rc

"$(INTDIR)\qyMcDaemon.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\QyMcDaemonObj.cpp

"$(INTDIR)\QyMcDaemonObj.obj"	"$(INTDIR)\QyMcDaemonObj.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "qyMcDaemon - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qyMcDaemon.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\qyMcDaemon.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMcDaemon - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fp"$(INTDIR)\qyMcDaemon.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\qyMcDaemon.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyPublic\qyComm\qyCommFunc.cpp

!IF  "$(CFG)" == "qyMcDaemon - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyCommFunc.obj"	"$(INTDIR)\qyCommFunc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMcDaemon - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyCommFunc.obj"	"$(INTDIR)\qyCommFunc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyPublic2\qyLogHelpFunc.cpp

!IF  "$(CFG)" == "qyMcDaemon - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyLogHelpFunc.obj"	"$(INTDIR)\qyLogHelpFunc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMcDaemon - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyLogHelpFunc.obj"	"$(INTDIR)\qyLogHelpFunc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qnmAssetsCommProc.cpp

!IF  "$(CFG)" == "qyMcDaemon - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmAssetsCommProc.obj"	"$(INTDIR)\qnmAssetsCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMcDaemon - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmAssetsCommProc.obj"	"$(INTDIR)\qnmAssetsCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qnmAssetsTemp.cpp

!IF  "$(CFG)" == "qyMcDaemon - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmAssetsTemp.obj"	"$(INTDIR)\qnmAssetsTemp.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMcDaemon - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmAssetsTemp.obj"	"$(INTDIR)\qnmAssetsTemp.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qnmCommProc.cpp

!IF  "$(CFG)" == "qyMcDaemon - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCommProc.obj"	"$(INTDIR)\qnmCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMcDaemon - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCommProc.obj"	"$(INTDIR)\qnmCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qnmCommProc1.cpp

!IF  "$(CFG)" == "qyMcDaemon - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCommProc1.obj"	"$(INTDIR)\qnmCommProc1.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMcDaemon - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCommProc1.obj"	"$(INTDIR)\qnmCommProc1.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qnmFwCommProc.cpp

!IF  "$(CFG)" == "qyMcDaemon - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmFwCommProc.obj"	"$(INTDIR)\qnmFwCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMcDaemon - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmFwCommProc.obj"	"$(INTDIR)\qnmFwCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qnmOsAuditCommProc.cpp

"$(INTDIR)\qnmOsAuditCommProc.obj"	"$(INTDIR)\qnmOsAuditCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\qyCommProc\qnmWarnCommProc.cpp

!IF  "$(CFG)" == "qyMcDaemon - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmWarnCommProc.obj"	"$(INTDIR)\qnmWarnCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMcDaemon - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmWarnCommProc.obj"	"$(INTDIR)\qnmWarnCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qwmNetworkStatusCommProc.cpp

"$(INTDIR)\qwmNetworkStatusCommProc.obj"	"$(INTDIR)\qwmNetworkStatusCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\qyCommProc\qyCommProc.cpp

!IF  "$(CFG)" == "qyMcDaemon - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyCommProc.obj"	"$(INTDIR)\qyCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMcDaemon - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyCommProc.obj"	"$(INTDIR)\qyCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qyImcLogFunc.cpp

!IF  "$(CFG)" == "qyMcDaemon - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyImcLogFunc.obj"	"$(INTDIR)\qyImcLogFunc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMcDaemon - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyImcLogFunc.obj"	"$(INTDIR)\qyImcLogFunc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qyImcPublic.cpp

!IF  "$(CFG)" == "qyMcDaemon - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyImcPublic.obj"	"$(INTDIR)\qyImcPublic.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMcDaemon - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyImcPublic.obj"	"$(INTDIR)\qyImcPublic.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCustom\qnmCustom.cpp

!IF  "$(CFG)" == "qyMcDaemon - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCustom.obj"	"$(INTDIR)\qnmCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMcDaemon - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCustom.obj"	"$(INTDIR)\qnmCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCustom\qnmCustomComm.cpp

!IF  "$(CFG)" == "qyMcDaemon - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCustomComm.obj"	"$(INTDIR)\qnmCustomComm.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMcDaemon - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCustomComm.obj"	"$(INTDIR)\qnmCustomComm.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCustom\qnmCustomRegTool.cpp

!IF  "$(CFG)" == "qyMcDaemon - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCustomRegTool.obj"	"$(INTDIR)\qnmCustomRegTool.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qyMcDaemon - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCustomRegTool.obj"	"$(INTDIR)\qnmCustomRegTool.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCustom\qwmAllHints.cpp

"$(INTDIR)\qwmAllHints.obj"	"$(INTDIR)\qwmAllHints.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\qyCustom\qyCustom.cpp

"$(INTDIR)\qyCustom.obj"	"$(INTDIR)\qyCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

