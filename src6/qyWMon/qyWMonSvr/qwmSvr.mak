# Microsoft Developer Studio Generated NMAKE File, Based on qwmSvr.dsp
!IF "$(CFG)" == ""
CFG=qwmSvr - Win32 Debug
!MESSAGE No configuration specified. Defaulting to qwmSvr - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "qwmSvr - Win32 Release" && "$(CFG)" != "qwmSvr - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "qwmSvr - Win32 Release"

OUTDIR=.\..\..\..\Release\bin
INTDIR=.\..\..\..\o\qwmSvr\Release
# Begin Custom Macros
OutDir=.\..\..\..\Release\bin
# End Custom Macros

ALL : "$(OUTDIR)\qyWMonSvr2k.exe"


CLEAN :
	-@erase "$(INTDIR)\asrWMonRas.obj"
	-@erase "$(INTDIR)\awmRegFunc.obj"
	-@erase "$(INTDIR)\CNTRDATA.OBJ"
	-@erase "$(INTDIR)\commandloop.obj"
	-@erase "$(INTDIR)\CONFIG.OBJ"
	-@erase "$(INTDIR)\cpuInfo.obj"
	-@erase "$(INTDIR)\Decrypt.obj"
	-@erase "$(INTDIR)\devConProc.obj"
	-@erase "$(INTDIR)\diskIO.obj"
	-@erase "$(INTDIR)\error.obj"
	-@erase "$(INTDIR)\fatFs.obj"
	-@erase "$(INTDIR)\fatfs_dent.obj"
	-@erase "$(INTDIR)\fs_buf.obj"
	-@erase "$(INTDIR)\fs_data.obj"
	-@erase "$(INTDIR)\fs_dent.obj"
	-@erase "$(INTDIR)\fs_inode.obj"
	-@erase "$(INTDIR)\fs_io.obj"
	-@erase "$(INTDIR)\fs_open.obj"
	-@erase "$(INTDIR)\fs_types.obj"
	-@erase "$(INTDIR)\functions.obj"
	-@erase "$(INTDIR)\get.obj"
	-@erase "$(INTDIR)\ils.obj"
	-@erase "$(INTDIR)\INSTDATA.OBJ"
	-@erase "$(INTDIR)\io_simpletcp.obj"
	-@erase "$(INTDIR)\Main.obj"
	-@erase "$(INTDIR)\mymalloc.obj"
	-@erase "$(INTDIR)\nt_pviewer.obj"
	-@erase "$(INTDIR)\ntfs.obj"
	-@erase "$(INTDIR)\ntfs_dent.obj"
	-@erase "$(INTDIR)\OBJDATA.OBJ"
	-@erase "$(INTDIR)\PERFDATA.OBJ"
	-@erase "$(INTDIR)\process_hop.obj"
	-@erase "$(INTDIR)\procNtPcAdapters.obj"
	-@erase "$(INTDIR)\qnmAssetsCommProc.obj"
	-@erase "$(INTDIR)\qnmAssetsTemp.obj"
	-@erase "$(INTDIR)\qnmChkCommProc.obj"
	-@erase "$(INTDIR)\qnmCommProc.obj"
	-@erase "$(INTDIR)\qnmOsAuditCommProc.obj"
	-@erase "$(INTDIR)\qwmChkDiskDrvFile.obj"
	-@erase "$(INTDIR)\qwmChkIe.obj"
	-@erase "$(INTDIR)\qwmChkNormalFile.obj"
	-@erase "$(INTDIR)\qwmChkPcInfo.obj"
	-@erase "$(INTDIR)\qwmChkProxyCfg.obj"
	-@erase "$(INTDIR)\qwmChkRas.obj"
	-@erase "$(INTDIR)\qwmChkRecent.obj"
	-@erase "$(INTDIR)\qwmChkShare.obj"
	-@erase "$(INTDIR)\qwmDoReboot.obj"
	-@erase "$(INTDIR)\qwmFunc.obj"
	-@erase "$(INTDIR)\qwmGetAssetsInfo.obj"
	-@erase "$(INTDIR)\qwmHideProcess.obj"
	-@erase "$(INTDIR)\qwmHideProcessCommProc.obj"
	-@erase "$(INTDIR)\qwmLogProc.obj"
	-@erase "$(INTDIR)\qwmNetworkStatus.obj"
	-@erase "$(INTDIR)\qwmNetworkStatusCommProc.obj"
	-@erase "$(INTDIR)\qwmProc.obj"
	-@erase "$(INTDIR)\qwmProcDetectionResult.obj"
	-@erase "$(INTDIR)\qwmProcDevRule.obj"
	-@erase "$(INTDIR)\qwmProcDevRule1.obj"
	-@erase "$(INTDIR)\qwmRegistryFunc.obj"
	-@erase "$(INTDIR)\qwmSecChkProc.obj"
	-@erase "$(INTDIR)\qwmStartHelp2.obj"
	-@erase "$(INTDIR)\qwmSvrFakeProc.obj"
	-@erase "$(INTDIR)\qwmTemp.obj"
	-@erase "$(INTDIR)\qwmThreadFileMon.obj"
	-@erase "$(INTDIR)\qwmThreadPrinterMgr.obj"
	-@erase "$(INTDIR)\qwmThreadProc.obj"
	-@erase "$(INTDIR)\qyCommProc.obj"
	-@erase "$(INTDIR)\qyCustom.obj"
	-@erase "$(INTDIR)\qyWMonSvr.res"
	-@erase "$(INTDIR)\showPcProcess.obj"
	-@erase "$(INTDIR)\showPcProcess1.obj"
	-@erase "$(INTDIR)\sndEventLog.obj"
	-@erase "$(INTDIR)\sndNetStat.obj"
	-@erase "$(INTDIR)\sndUsrInfo.obj"
	-@erase "$(INTDIR)\split_at.obj"
	-@erase "$(INTDIR)\strhandle.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\qyWMonSvr2k.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "." /I "..\include" /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Fp"$(INTDIR)\qwmSvr.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\qyWMonSvr.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qwmSvr.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib qyPublicStaticNoMfc.lib qyEncLibStaticNoMfc.lib wsock32.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\qyWMonSvr2k.pdb" /machine:I386 /out:"$(OUTDIR)\qyWMonSvr2k.exe" /libpath:"..\..\..\Release\lib" 
LINK32_OBJS= \
	"$(INTDIR)\CNTRDATA.OBJ" \
	"$(INTDIR)\INSTDATA.OBJ" \
	"$(INTDIR)\nt_pviewer.obj" \
	"$(INTDIR)\OBJDATA.OBJ" \
	"$(INTDIR)\PERFDATA.OBJ" \
	"$(INTDIR)\CONFIG.OBJ" \
	"$(INTDIR)\process_hop.obj" \
	"$(INTDIR)\strhandle.obj" \
	"$(INTDIR)\asrWMonRas.obj" \
	"$(INTDIR)\awmRegFunc.obj" \
	"$(INTDIR)\qwmHideProcess.obj" \
	"$(INTDIR)\qwmLogProc.obj" \
	"$(INTDIR)\qwmProcDetectionResult.obj" \
	"$(INTDIR)\qwmProcDevRule.obj" \
	"$(INTDIR)\qwmProcDevRule1.obj" \
	"$(INTDIR)\qwmStartHelp2.obj" \
	"$(INTDIR)\qwmSvrFakeProc.obj" \
	"$(INTDIR)\qwmThreadFileMon.obj" \
	"$(INTDIR)\qwmThreadPrinterMgr.obj" \
	"$(INTDIR)\qwmThreadProc.obj" \
	"$(INTDIR)\sndNetStat.obj" \
	"$(INTDIR)\io_simpletcp.obj" \
	"$(INTDIR)\Main.obj" \
	"$(INTDIR)\qnmAssetsCommProc.obj" \
	"$(INTDIR)\qnmAssetsTemp.obj" \
	"$(INTDIR)\qnmChkCommProc.obj" \
	"$(INTDIR)\qnmCommProc.obj" \
	"$(INTDIR)\qnmOsAuditCommProc.obj" \
	"$(INTDIR)\qwmHideProcessCommProc.obj" \
	"$(INTDIR)\qwmNetworkStatusCommProc.obj" \
	"$(INTDIR)\qyCommProc.obj" \
	"$(INTDIR)\commandloop.obj" \
	"$(INTDIR)\cpuInfo.obj" \
	"$(INTDIR)\Decrypt.obj" \
	"$(INTDIR)\devConProc.obj" \
	"$(INTDIR)\functions.obj" \
	"$(INTDIR)\procNtPcAdapters.obj" \
	"$(INTDIR)\qwmDoReboot.obj" \
	"$(INTDIR)\qwmFunc.obj" \
	"$(INTDIR)\qwmNetworkStatus.obj" \
	"$(INTDIR)\qwmProc.obj" \
	"$(INTDIR)\qwmRegistryFunc.obj" \
	"$(INTDIR)\qwmTemp.obj" \
	"$(INTDIR)\showPcProcess.obj" \
	"$(INTDIR)\showPcProcess1.obj" \
	"$(INTDIR)\sndEventLog.obj" \
	"$(INTDIR)\sndUsrInfo.obj" \
	"$(INTDIR)\qyCustom.obj" \
	"$(INTDIR)\qwmChkDiskDrvFile.obj" \
	"$(INTDIR)\qwmChkIe.obj" \
	"$(INTDIR)\qwmChkNormalFile.obj" \
	"$(INTDIR)\qwmChkPcInfo.obj" \
	"$(INTDIR)\qwmChkProxyCfg.obj" \
	"$(INTDIR)\qwmChkRas.obj" \
	"$(INTDIR)\qwmChkRecent.obj" \
	"$(INTDIR)\qwmChkShare.obj" \
	"$(INTDIR)\qwmGetAssetsInfo.obj" \
	"$(INTDIR)\qwmSecChkProc.obj" \
	"$(INTDIR)\diskIO.obj" \
	"$(INTDIR)\error.obj" \
	"$(INTDIR)\fatFs.obj" \
	"$(INTDIR)\fatfs_dent.obj" \
	"$(INTDIR)\fs_buf.obj" \
	"$(INTDIR)\fs_data.obj" \
	"$(INTDIR)\fs_dent.obj" \
	"$(INTDIR)\fs_inode.obj" \
	"$(INTDIR)\fs_io.obj" \
	"$(INTDIR)\fs_open.obj" \
	"$(INTDIR)\fs_types.obj" \
	"$(INTDIR)\get.obj" \
	"$(INTDIR)\ils.obj" \
	"$(INTDIR)\mymalloc.obj" \
	"$(INTDIR)\ntfs.obj" \
	"$(INTDIR)\ntfs_dent.obj" \
	"$(INTDIR)\split_at.obj" \
	"$(INTDIR)\qyWMonSvr.res"

"$(OUTDIR)\qyWMonSvr2k.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"

OUTDIR=.\..\..\..\Debug\bin
INTDIR=.\..\..\..\o\qwmSvr\Debug
# Begin Custom Macros
OutDir=.\..\..\..\Debug\bin
# End Custom Macros

ALL : "$(OUTDIR)\qyWMonSvr2k.exe" "$(OUTDIR)\qwmSvr.bsc"


CLEAN :
	-@erase "$(INTDIR)\asrWMonRas.obj"
	-@erase "$(INTDIR)\asrWMonRas.sbr"
	-@erase "$(INTDIR)\awmRegFunc.obj"
	-@erase "$(INTDIR)\awmRegFunc.sbr"
	-@erase "$(INTDIR)\CNTRDATA.OBJ"
	-@erase "$(INTDIR)\CNTRDATA.SBR"
	-@erase "$(INTDIR)\commandloop.obj"
	-@erase "$(INTDIR)\commandloop.sbr"
	-@erase "$(INTDIR)\CONFIG.OBJ"
	-@erase "$(INTDIR)\CONFIG.SBR"
	-@erase "$(INTDIR)\cpuInfo.obj"
	-@erase "$(INTDIR)\cpuInfo.sbr"
	-@erase "$(INTDIR)\Decrypt.obj"
	-@erase "$(INTDIR)\Decrypt.sbr"
	-@erase "$(INTDIR)\devConProc.obj"
	-@erase "$(INTDIR)\devConProc.sbr"
	-@erase "$(INTDIR)\diskIO.obj"
	-@erase "$(INTDIR)\diskIO.sbr"
	-@erase "$(INTDIR)\error.obj"
	-@erase "$(INTDIR)\error.sbr"
	-@erase "$(INTDIR)\fatFs.obj"
	-@erase "$(INTDIR)\fatFs.sbr"
	-@erase "$(INTDIR)\fatfs_dent.obj"
	-@erase "$(INTDIR)\fatfs_dent.sbr"
	-@erase "$(INTDIR)\fs_buf.obj"
	-@erase "$(INTDIR)\fs_buf.sbr"
	-@erase "$(INTDIR)\fs_data.obj"
	-@erase "$(INTDIR)\fs_data.sbr"
	-@erase "$(INTDIR)\fs_dent.obj"
	-@erase "$(INTDIR)\fs_dent.sbr"
	-@erase "$(INTDIR)\fs_inode.obj"
	-@erase "$(INTDIR)\fs_inode.sbr"
	-@erase "$(INTDIR)\fs_io.obj"
	-@erase "$(INTDIR)\fs_io.sbr"
	-@erase "$(INTDIR)\fs_open.obj"
	-@erase "$(INTDIR)\fs_open.sbr"
	-@erase "$(INTDIR)\fs_types.obj"
	-@erase "$(INTDIR)\fs_types.sbr"
	-@erase "$(INTDIR)\functions.obj"
	-@erase "$(INTDIR)\functions.sbr"
	-@erase "$(INTDIR)\get.obj"
	-@erase "$(INTDIR)\get.sbr"
	-@erase "$(INTDIR)\ils.obj"
	-@erase "$(INTDIR)\ils.sbr"
	-@erase "$(INTDIR)\INSTDATA.OBJ"
	-@erase "$(INTDIR)\INSTDATA.SBR"
	-@erase "$(INTDIR)\io_simpletcp.obj"
	-@erase "$(INTDIR)\io_simpletcp.sbr"
	-@erase "$(INTDIR)\Main.obj"
	-@erase "$(INTDIR)\Main.sbr"
	-@erase "$(INTDIR)\mymalloc.obj"
	-@erase "$(INTDIR)\mymalloc.sbr"
	-@erase "$(INTDIR)\nt_pviewer.obj"
	-@erase "$(INTDIR)\nt_pviewer.sbr"
	-@erase "$(INTDIR)\ntfs.obj"
	-@erase "$(INTDIR)\ntfs.sbr"
	-@erase "$(INTDIR)\ntfs_dent.obj"
	-@erase "$(INTDIR)\ntfs_dent.sbr"
	-@erase "$(INTDIR)\OBJDATA.OBJ"
	-@erase "$(INTDIR)\OBJDATA.SBR"
	-@erase "$(INTDIR)\PERFDATA.OBJ"
	-@erase "$(INTDIR)\PERFDATA.SBR"
	-@erase "$(INTDIR)\process_hop.obj"
	-@erase "$(INTDIR)\process_hop.sbr"
	-@erase "$(INTDIR)\procNtPcAdapters.obj"
	-@erase "$(INTDIR)\procNtPcAdapters.sbr"
	-@erase "$(INTDIR)\qnmAssetsCommProc.obj"
	-@erase "$(INTDIR)\qnmAssetsCommProc.sbr"
	-@erase "$(INTDIR)\qnmAssetsTemp.obj"
	-@erase "$(INTDIR)\qnmAssetsTemp.sbr"
	-@erase "$(INTDIR)\qnmChkCommProc.obj"
	-@erase "$(INTDIR)\qnmChkCommProc.sbr"
	-@erase "$(INTDIR)\qnmCommProc.obj"
	-@erase "$(INTDIR)\qnmCommProc.sbr"
	-@erase "$(INTDIR)\qnmOsAuditCommProc.obj"
	-@erase "$(INTDIR)\qnmOsAuditCommProc.sbr"
	-@erase "$(INTDIR)\qwmChkDiskDrvFile.obj"
	-@erase "$(INTDIR)\qwmChkDiskDrvFile.sbr"
	-@erase "$(INTDIR)\qwmChkIe.obj"
	-@erase "$(INTDIR)\qwmChkIe.sbr"
	-@erase "$(INTDIR)\qwmChkNormalFile.obj"
	-@erase "$(INTDIR)\qwmChkNormalFile.sbr"
	-@erase "$(INTDIR)\qwmChkPcInfo.obj"
	-@erase "$(INTDIR)\qwmChkPcInfo.sbr"
	-@erase "$(INTDIR)\qwmChkProxyCfg.obj"
	-@erase "$(INTDIR)\qwmChkProxyCfg.sbr"
	-@erase "$(INTDIR)\qwmChkRas.obj"
	-@erase "$(INTDIR)\qwmChkRas.sbr"
	-@erase "$(INTDIR)\qwmChkRecent.obj"
	-@erase "$(INTDIR)\qwmChkRecent.sbr"
	-@erase "$(INTDIR)\qwmChkShare.obj"
	-@erase "$(INTDIR)\qwmChkShare.sbr"
	-@erase "$(INTDIR)\qwmDoReboot.obj"
	-@erase "$(INTDIR)\qwmDoReboot.sbr"
	-@erase "$(INTDIR)\qwmFunc.obj"
	-@erase "$(INTDIR)\qwmFunc.sbr"
	-@erase "$(INTDIR)\qwmGetAssetsInfo.obj"
	-@erase "$(INTDIR)\qwmGetAssetsInfo.sbr"
	-@erase "$(INTDIR)\qwmHideProcess.obj"
	-@erase "$(INTDIR)\qwmHideProcess.sbr"
	-@erase "$(INTDIR)\qwmHideProcessCommProc.obj"
	-@erase "$(INTDIR)\qwmHideProcessCommProc.sbr"
	-@erase "$(INTDIR)\qwmLogProc.obj"
	-@erase "$(INTDIR)\qwmLogProc.sbr"
	-@erase "$(INTDIR)\qwmNetworkStatus.obj"
	-@erase "$(INTDIR)\qwmNetworkStatus.sbr"
	-@erase "$(INTDIR)\qwmNetworkStatusCommProc.obj"
	-@erase "$(INTDIR)\qwmNetworkStatusCommProc.sbr"
	-@erase "$(INTDIR)\qwmProc.obj"
	-@erase "$(INTDIR)\qwmProc.sbr"
	-@erase "$(INTDIR)\qwmProcDetectionResult.obj"
	-@erase "$(INTDIR)\qwmProcDetectionResult.sbr"
	-@erase "$(INTDIR)\qwmProcDevRule.obj"
	-@erase "$(INTDIR)\qwmProcDevRule.sbr"
	-@erase "$(INTDIR)\qwmProcDevRule1.obj"
	-@erase "$(INTDIR)\qwmProcDevRule1.sbr"
	-@erase "$(INTDIR)\qwmRegistryFunc.obj"
	-@erase "$(INTDIR)\qwmRegistryFunc.sbr"
	-@erase "$(INTDIR)\qwmSecChkProc.obj"
	-@erase "$(INTDIR)\qwmSecChkProc.sbr"
	-@erase "$(INTDIR)\qwmStartHelp2.obj"
	-@erase "$(INTDIR)\qwmStartHelp2.sbr"
	-@erase "$(INTDIR)\qwmSvrFakeProc.obj"
	-@erase "$(INTDIR)\qwmSvrFakeProc.sbr"
	-@erase "$(INTDIR)\qwmTemp.obj"
	-@erase "$(INTDIR)\qwmTemp.sbr"
	-@erase "$(INTDIR)\qwmThreadFileMon.obj"
	-@erase "$(INTDIR)\qwmThreadFileMon.sbr"
	-@erase "$(INTDIR)\qwmThreadPrinterMgr.obj"
	-@erase "$(INTDIR)\qwmThreadPrinterMgr.sbr"
	-@erase "$(INTDIR)\qwmThreadProc.obj"
	-@erase "$(INTDIR)\qwmThreadProc.sbr"
	-@erase "$(INTDIR)\qyCommProc.obj"
	-@erase "$(INTDIR)\qyCommProc.sbr"
	-@erase "$(INTDIR)\qyCustom.obj"
	-@erase "$(INTDIR)\qyCustom.sbr"
	-@erase "$(INTDIR)\qyWMonSvr.res"
	-@erase "$(INTDIR)\showPcProcess.obj"
	-@erase "$(INTDIR)\showPcProcess.sbr"
	-@erase "$(INTDIR)\showPcProcess1.obj"
	-@erase "$(INTDIR)\showPcProcess1.sbr"
	-@erase "$(INTDIR)\sndEventLog.obj"
	-@erase "$(INTDIR)\sndEventLog.sbr"
	-@erase "$(INTDIR)\sndNetStat.obj"
	-@erase "$(INTDIR)\sndNetStat.sbr"
	-@erase "$(INTDIR)\sndUsrInfo.obj"
	-@erase "$(INTDIR)\sndUsrInfo.sbr"
	-@erase "$(INTDIR)\split_at.obj"
	-@erase "$(INTDIR)\split_at.sbr"
	-@erase "$(INTDIR)\strhandle.obj"
	-@erase "$(INTDIR)\strhandle.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\qwmSvr.bsc"
	-@erase "$(OUTDIR)\qyWMonSvr2k.exe"
	-@erase "$(OUTDIR)\qyWMonSvr2k.ilk"
	-@erase "$(OUTDIR)\qyWMonSvr2k.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "." /I "..\include" /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qwmSvr.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\qyWMonSvr.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qwmSvr.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\CNTRDATA.SBR" \
	"$(INTDIR)\INSTDATA.SBR" \
	"$(INTDIR)\nt_pviewer.sbr" \
	"$(INTDIR)\OBJDATA.SBR" \
	"$(INTDIR)\PERFDATA.SBR" \
	"$(INTDIR)\CONFIG.SBR" \
	"$(INTDIR)\process_hop.sbr" \
	"$(INTDIR)\strhandle.sbr" \
	"$(INTDIR)\asrWMonRas.sbr" \
	"$(INTDIR)\awmRegFunc.sbr" \
	"$(INTDIR)\qwmHideProcess.sbr" \
	"$(INTDIR)\qwmLogProc.sbr" \
	"$(INTDIR)\qwmProcDetectionResult.sbr" \
	"$(INTDIR)\qwmProcDevRule.sbr" \
	"$(INTDIR)\qwmProcDevRule1.sbr" \
	"$(INTDIR)\qwmStartHelp2.sbr" \
	"$(INTDIR)\qwmSvrFakeProc.sbr" \
	"$(INTDIR)\qwmThreadFileMon.sbr" \
	"$(INTDIR)\qwmThreadPrinterMgr.sbr" \
	"$(INTDIR)\qwmThreadProc.sbr" \
	"$(INTDIR)\sndNetStat.sbr" \
	"$(INTDIR)\io_simpletcp.sbr" \
	"$(INTDIR)\Main.sbr" \
	"$(INTDIR)\qnmAssetsCommProc.sbr" \
	"$(INTDIR)\qnmAssetsTemp.sbr" \
	"$(INTDIR)\qnmChkCommProc.sbr" \
	"$(INTDIR)\qnmCommProc.sbr" \
	"$(INTDIR)\qnmOsAuditCommProc.sbr" \
	"$(INTDIR)\qwmHideProcessCommProc.sbr" \
	"$(INTDIR)\qwmNetworkStatusCommProc.sbr" \
	"$(INTDIR)\qyCommProc.sbr" \
	"$(INTDIR)\commandloop.sbr" \
	"$(INTDIR)\cpuInfo.sbr" \
	"$(INTDIR)\Decrypt.sbr" \
	"$(INTDIR)\devConProc.sbr" \
	"$(INTDIR)\functions.sbr" \
	"$(INTDIR)\procNtPcAdapters.sbr" \
	"$(INTDIR)\qwmDoReboot.sbr" \
	"$(INTDIR)\qwmFunc.sbr" \
	"$(INTDIR)\qwmNetworkStatus.sbr" \
	"$(INTDIR)\qwmProc.sbr" \
	"$(INTDIR)\qwmRegistryFunc.sbr" \
	"$(INTDIR)\qwmTemp.sbr" \
	"$(INTDIR)\showPcProcess.sbr" \
	"$(INTDIR)\showPcProcess1.sbr" \
	"$(INTDIR)\sndEventLog.sbr" \
	"$(INTDIR)\sndUsrInfo.sbr" \
	"$(INTDIR)\qyCustom.sbr" \
	"$(INTDIR)\qwmChkDiskDrvFile.sbr" \
	"$(INTDIR)\qwmChkIe.sbr" \
	"$(INTDIR)\qwmChkNormalFile.sbr" \
	"$(INTDIR)\qwmChkPcInfo.sbr" \
	"$(INTDIR)\qwmChkProxyCfg.sbr" \
	"$(INTDIR)\qwmChkRas.sbr" \
	"$(INTDIR)\qwmChkRecent.sbr" \
	"$(INTDIR)\qwmChkShare.sbr" \
	"$(INTDIR)\qwmGetAssetsInfo.sbr" \
	"$(INTDIR)\qwmSecChkProc.sbr" \
	"$(INTDIR)\diskIO.sbr" \
	"$(INTDIR)\error.sbr" \
	"$(INTDIR)\fatFs.sbr" \
	"$(INTDIR)\fatfs_dent.sbr" \
	"$(INTDIR)\fs_buf.sbr" \
	"$(INTDIR)\fs_data.sbr" \
	"$(INTDIR)\fs_dent.sbr" \
	"$(INTDIR)\fs_inode.sbr" \
	"$(INTDIR)\fs_io.sbr" \
	"$(INTDIR)\fs_open.sbr" \
	"$(INTDIR)\fs_types.sbr" \
	"$(INTDIR)\get.sbr" \
	"$(INTDIR)\ils.sbr" \
	"$(INTDIR)\mymalloc.sbr" \
	"$(INTDIR)\ntfs.sbr" \
	"$(INTDIR)\ntfs_dent.sbr" \
	"$(INTDIR)\split_at.sbr"

"$(OUTDIR)\qwmSvr.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib qyPublicStaticNoMfc.lib qyEncLibStaticNoMfc.lib wsock32.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\qyWMonSvr2k.pdb" /debug /machine:I386 /out:"$(OUTDIR)\qyWMonSvr2k.exe" /pdbtype:sept /libpath:"..\..\..\Debug\lib" 
LINK32_OBJS= \
	"$(INTDIR)\CNTRDATA.OBJ" \
	"$(INTDIR)\INSTDATA.OBJ" \
	"$(INTDIR)\nt_pviewer.obj" \
	"$(INTDIR)\OBJDATA.OBJ" \
	"$(INTDIR)\PERFDATA.OBJ" \
	"$(INTDIR)\CONFIG.OBJ" \
	"$(INTDIR)\process_hop.obj" \
	"$(INTDIR)\strhandle.obj" \
	"$(INTDIR)\asrWMonRas.obj" \
	"$(INTDIR)\awmRegFunc.obj" \
	"$(INTDIR)\qwmHideProcess.obj" \
	"$(INTDIR)\qwmLogProc.obj" \
	"$(INTDIR)\qwmProcDetectionResult.obj" \
	"$(INTDIR)\qwmProcDevRule.obj" \
	"$(INTDIR)\qwmProcDevRule1.obj" \
	"$(INTDIR)\qwmStartHelp2.obj" \
	"$(INTDIR)\qwmSvrFakeProc.obj" \
	"$(INTDIR)\qwmThreadFileMon.obj" \
	"$(INTDIR)\qwmThreadPrinterMgr.obj" \
	"$(INTDIR)\qwmThreadProc.obj" \
	"$(INTDIR)\sndNetStat.obj" \
	"$(INTDIR)\io_simpletcp.obj" \
	"$(INTDIR)\Main.obj" \
	"$(INTDIR)\qnmAssetsCommProc.obj" \
	"$(INTDIR)\qnmAssetsTemp.obj" \
	"$(INTDIR)\qnmChkCommProc.obj" \
	"$(INTDIR)\qnmCommProc.obj" \
	"$(INTDIR)\qnmOsAuditCommProc.obj" \
	"$(INTDIR)\qwmHideProcessCommProc.obj" \
	"$(INTDIR)\qwmNetworkStatusCommProc.obj" \
	"$(INTDIR)\qyCommProc.obj" \
	"$(INTDIR)\commandloop.obj" \
	"$(INTDIR)\cpuInfo.obj" \
	"$(INTDIR)\Decrypt.obj" \
	"$(INTDIR)\devConProc.obj" \
	"$(INTDIR)\functions.obj" \
	"$(INTDIR)\procNtPcAdapters.obj" \
	"$(INTDIR)\qwmDoReboot.obj" \
	"$(INTDIR)\qwmFunc.obj" \
	"$(INTDIR)\qwmNetworkStatus.obj" \
	"$(INTDIR)\qwmProc.obj" \
	"$(INTDIR)\qwmRegistryFunc.obj" \
	"$(INTDIR)\qwmTemp.obj" \
	"$(INTDIR)\showPcProcess.obj" \
	"$(INTDIR)\showPcProcess1.obj" \
	"$(INTDIR)\sndEventLog.obj" \
	"$(INTDIR)\sndUsrInfo.obj" \
	"$(INTDIR)\qyCustom.obj" \
	"$(INTDIR)\qwmChkDiskDrvFile.obj" \
	"$(INTDIR)\qwmChkIe.obj" \
	"$(INTDIR)\qwmChkNormalFile.obj" \
	"$(INTDIR)\qwmChkPcInfo.obj" \
	"$(INTDIR)\qwmChkProxyCfg.obj" \
	"$(INTDIR)\qwmChkRas.obj" \
	"$(INTDIR)\qwmChkRecent.obj" \
	"$(INTDIR)\qwmChkShare.obj" \
	"$(INTDIR)\qwmGetAssetsInfo.obj" \
	"$(INTDIR)\qwmSecChkProc.obj" \
	"$(INTDIR)\diskIO.obj" \
	"$(INTDIR)\error.obj" \
	"$(INTDIR)\fatFs.obj" \
	"$(INTDIR)\fatfs_dent.obj" \
	"$(INTDIR)\fs_buf.obj" \
	"$(INTDIR)\fs_data.obj" \
	"$(INTDIR)\fs_dent.obj" \
	"$(INTDIR)\fs_inode.obj" \
	"$(INTDIR)\fs_io.obj" \
	"$(INTDIR)\fs_open.obj" \
	"$(INTDIR)\fs_types.obj" \
	"$(INTDIR)\get.obj" \
	"$(INTDIR)\ils.obj" \
	"$(INTDIR)\mymalloc.obj" \
	"$(INTDIR)\ntfs.obj" \
	"$(INTDIR)\ntfs_dent.obj" \
	"$(INTDIR)\split_at.obj" \
	"$(INTDIR)\qyWMonSvr.res"

"$(OUTDIR)\qyWMonSvr2k.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("qwmSvr.dep")
!INCLUDE "qwmSvr.dep"
!ELSE 
!MESSAGE Warning: cannot find "qwmSvr.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "qwmSvr - Win32 Release" || "$(CFG)" == "qwmSvr - Win32 Debug"
SOURCE=".\MISC\PROCLIST\nt-pviewer\CNTRDATA.CPP"

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\CNTRDATA.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\CNTRDATA.OBJ"	"$(INTDIR)\CNTRDATA.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=".\MISC\PROCLIST\nt-pviewer\INSTDATA.CPP"

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\INSTDATA.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\INSTDATA.OBJ"	"$(INTDIR)\INSTDATA.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=".\MISC\PROCLIST\nt-pviewer\nt_pviewer.cpp"

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\nt_pviewer.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\nt_pviewer.obj"	"$(INTDIR)\nt_pviewer.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=".\MISC\PROCLIST\nt-pviewer\OBJDATA.CPP"

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\OBJDATA.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\OBJDATA.OBJ"	"$(INTDIR)\OBJDATA.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=".\MISC\PROCLIST\nt-pviewer\PERFDATA.CPP"

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\PERFDATA.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\PERFDATA.OBJ"	"$(INTDIR)\PERFDATA.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\MISC\CONFIG\CONFIG.CPP

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\CONFIG.OBJ" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\CONFIG.OBJ"	"$(INTDIR)\CONFIG.SBR" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\MISC\process_hop\process_hop.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\process_hop.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\process_hop.obj"	"$(INTDIR)\process_hop.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\LIBC\strhandle.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\strhandle.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\strhandle.obj"	"$(INTDIR)\strhandle.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\qwmProc\asrWMonRas.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\asrWMonRas.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\asrWMonRas.obj"	"$(INTDIR)\asrWMonRas.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\qwmProc\awmRegFunc.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\awmRegFunc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\awmRegFunc.obj"	"$(INTDIR)\awmRegFunc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\qwmProc\qwmHideProcess.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmHideProcess.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmHideProcess.obj"	"$(INTDIR)\qwmHideProcess.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\qwmProc\qwmLogProc.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmLogProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmLogProc.obj"	"$(INTDIR)\qwmLogProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\qwmProc\qwmProcDetectionResult.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmProcDetectionResult.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmProcDetectionResult.obj"	"$(INTDIR)\qwmProcDetectionResult.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\qwmProc\qwmProcDevRule.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmProcDevRule.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmProcDevRule.obj"	"$(INTDIR)\qwmProcDevRule.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\qwmProc\qwmProcDevRule1.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmProcDevRule1.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmProcDevRule1.obj"	"$(INTDIR)\qwmProcDevRule1.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\qwmProc\qwmStartHelp2.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmStartHelp2.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmStartHelp2.obj"	"$(INTDIR)\qwmStartHelp2.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\qwmProc\qwmSvrFakeProc.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmSvrFakeProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmSvrFakeProc.obj"	"$(INTDIR)\qwmSvrFakeProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\qwmProc\qwmThreadFileMon.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmThreadFileMon.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmThreadFileMon.obj"	"$(INTDIR)\qwmThreadFileMon.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\qwmProc\qwmThreadPrinterMgr.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmThreadPrinterMgr.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmThreadPrinterMgr.obj"	"$(INTDIR)\qwmThreadPrinterMgr.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\qwmProc\qwmThreadProc.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmThreadProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmThreadProc.obj"	"$(INTDIR)\qwmThreadProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\qwmProc\sndNetStat.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\sndNetStat.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\sndNetStat.obj"	"$(INTDIR)\sndNetStat.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\IO\io_simpletcp.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\io_simpletcp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\io_simpletcp.obj"	"$(INTDIR)\io_simpletcp.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\Main.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\Main.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\Main.obj"	"$(INTDIR)\Main.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\qyWMonSvr.rc

"$(INTDIR)\qyWMonSvr.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=..\..\qyCommProc\qnmAssetsCommProc.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qnmAssetsCommProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qnmAssetsCommProc.obj"	"$(INTDIR)\qnmAssetsCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyCommProc\qnmAssetsTemp.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qnmAssetsTemp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qnmAssetsTemp.obj"	"$(INTDIR)\qnmAssetsTemp.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyCommProc\qnmChkCommProc.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qnmChkCommProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qnmChkCommProc.obj"	"$(INTDIR)\qnmChkCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyCommProc\qnmCommProc.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qnmCommProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qnmCommProc.obj"	"$(INTDIR)\qnmCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyCommProc\qnmOsAuditCommProc.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qnmOsAuditCommProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qnmOsAuditCommProc.obj"	"$(INTDIR)\qnmOsAuditCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyCommProc\qwmHideProcessCommProc.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmHideProcessCommProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmHideProcessCommProc.obj"	"$(INTDIR)\qwmHideProcessCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyCommProc\qwmNetworkStatusCommProc.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmNetworkStatusCommProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmNetworkStatusCommProc.obj"	"$(INTDIR)\qwmNetworkStatusCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyCommProc\qyCommProc.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qyCommProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qyCommProc.obj"	"$(INTDIR)\qyCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qwmPublic\commandloop.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\commandloop.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\commandloop.obj"	"$(INTDIR)\commandloop.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qwmPublic\cpuInfo.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\cpuInfo.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\cpuInfo.obj"	"$(INTDIR)\cpuInfo.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qwmPublic\Decrypt.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\Decrypt.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\Decrypt.obj"	"$(INTDIR)\Decrypt.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qwmPublic\devConProc.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\devConProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\devConProc.obj"	"$(INTDIR)\devConProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qwmPublic\functions.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\functions.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\functions.obj"	"$(INTDIR)\functions.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qwmPublic\procNtPcAdapters.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\procNtPcAdapters.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\procNtPcAdapters.obj"	"$(INTDIR)\procNtPcAdapters.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qwmPublic\qwmDoReboot.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmDoReboot.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmDoReboot.obj"	"$(INTDIR)\qwmDoReboot.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qwmPublic\qwmFunc.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmFunc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmFunc.obj"	"$(INTDIR)\qwmFunc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qwmPublic\qwmNetworkStatus.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmNetworkStatus.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmNetworkStatus.obj"	"$(INTDIR)\qwmNetworkStatus.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qwmPublic\qwmProc.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmProc.obj"	"$(INTDIR)\qwmProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qwmPublic\qwmRegistryFunc.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmRegistryFunc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmRegistryFunc.obj"	"$(INTDIR)\qwmRegistryFunc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qwmPublic\qwmTemp.CPP

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmTemp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmTemp.obj"	"$(INTDIR)\qwmTemp.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qwmPublic\showPcProcess.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\showPcProcess.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\showPcProcess.obj"	"$(INTDIR)\showPcProcess.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qwmPublic\showPcProcess1.CPP

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\showPcProcess1.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\showPcProcess1.obj"	"$(INTDIR)\showPcProcess1.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qwmPublic\sndEventLog.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\sndEventLog.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\sndEventLog.obj"	"$(INTDIR)\sndEventLog.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qwmPublic\sndUsrInfo.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\sndUsrInfo.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\sndUsrInfo.obj"	"$(INTDIR)\sndUsrInfo.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyCustom\qyCustom.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qyCustom.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qyCustom.obj"	"$(INTDIR)\qyCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmChkDiskDrvFile.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmChkDiskDrvFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmChkDiskDrvFile.obj"	"$(INTDIR)\qwmChkDiskDrvFile.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmChkIe.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmChkIe.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmChkIe.obj"	"$(INTDIR)\qwmChkIe.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmChkNormalFile.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmChkNormalFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmChkNormalFile.obj"	"$(INTDIR)\qwmChkNormalFile.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmChkPcInfo.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmChkPcInfo.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmChkPcInfo.obj"	"$(INTDIR)\qwmChkPcInfo.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmChkProxyCfg.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmChkProxyCfg.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmChkProxyCfg.obj"	"$(INTDIR)\qwmChkProxyCfg.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmChkRas.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmChkRas.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmChkRas.obj"	"$(INTDIR)\qwmChkRas.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmChkRecent.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmChkRecent.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmChkRecent.obj"	"$(INTDIR)\qwmChkRecent.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmChkShare.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmChkShare.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmChkShare.obj"	"$(INTDIR)\qwmChkShare.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmGetAssetsInfo.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmGetAssetsInfo.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmGetAssetsInfo.obj"	"$(INTDIR)\qwmGetAssetsInfo.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmSecChkProc.cpp

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\qwmSecChkProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\qwmSecChkProc.obj"	"$(INTDIR)\qwmSecChkProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\diskIO.c

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\diskIO.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\diskIO.obj"	"$(INTDIR)\diskIO.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\error.c

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\error.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\error.obj"	"$(INTDIR)\error.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\fatFs.c

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\fatFs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\fatFs.obj"	"$(INTDIR)\fatFs.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\fatfs_dent.c

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\fatfs_dent.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\fatfs_dent.obj"	"$(INTDIR)\fatfs_dent.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\fs_buf.c

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\fs_buf.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\fs_buf.obj"	"$(INTDIR)\fs_buf.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\fs_data.c

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\fs_data.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\fs_data.obj"	"$(INTDIR)\fs_data.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\fs_dent.c

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\fs_dent.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\fs_dent.obj"	"$(INTDIR)\fs_dent.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\fs_inode.c

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\fs_inode.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\fs_inode.obj"	"$(INTDIR)\fs_inode.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\fs_io.c

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\fs_io.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\fs_io.obj"	"$(INTDIR)\fs_io.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\fs_open.c

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\fs_open.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\fs_open.obj"	"$(INTDIR)\fs_open.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\fs_types.c

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\fs_types.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\fs_types.obj"	"$(INTDIR)\fs_types.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\get.c

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\get.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\get.obj"	"$(INTDIR)\get.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\ils.c

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\ils.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\ils.obj"	"$(INTDIR)\ils.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\mymalloc.c

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\mymalloc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\mymalloc.obj"	"$(INTDIR)\mymalloc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\ntfs.c

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\ntfs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\ntfs.obj"	"$(INTDIR)\ntfs.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\ntfs_dent.c

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\ntfs_dent.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\ntfs_dent.obj"	"$(INTDIR)\ntfs_dent.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\split_at.c

!IF  "$(CFG)" == "qwmSvr - Win32 Release"


"$(INTDIR)\split_at.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmSvr - Win32 Debug"


"$(INTDIR)\split_at.obj"	"$(INTDIR)\split_at.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

