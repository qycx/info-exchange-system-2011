# Microsoft Developer Studio Generated NMAKE File, Based on qwmShared.dsp
!IF "$(CFG)" == ""
CFG=qwmShared - Win32 Debug
!MESSAGE No configuration specified. Defaulting to qwmShared - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "qwmShared - Win32 Release" && "$(CFG)" != "qwmShared - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "qwmShared - Win32 Release"

OUTDIR=.\..\..\..\Release\lib
INTDIR=.\..\..\..\o\qwmShared\Release
# Begin Custom Macros
OutDir=.\..\..\..\Release\lib
# End Custom Macros

ALL : "$(OUTDIR)\qwmShared.lib"


CLEAN :
	-@erase "$(INTDIR)\cpuInfo.obj"
	-@erase "$(INTDIR)\delSelf.obj"
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
	-@erase "$(INTDIR)\mymalloc.obj"
	-@erase "$(INTDIR)\ntfs.obj"
	-@erase "$(INTDIR)\ntfs_dent.obj"
	-@erase "$(INTDIR)\qnmAssetsCommProc.obj"
	-@erase "$(INTDIR)\qnmAssetsTemp.obj"
	-@erase "$(INTDIR)\qnmChkCommProc.obj"
	-@erase "$(INTDIR)\qnmCommProc.obj"
	-@erase "$(INTDIR)\qwmChkDiskDrvFile.obj"
	-@erase "$(INTDIR)\qwmChkIe.obj"
	-@erase "$(INTDIR)\qwmChkInternet.obj"
	-@erase "$(INTDIR)\qwmChkNormalFile.obj"
	-@erase "$(INTDIR)\qwmChkOsInfo.obj"
	-@erase "$(INTDIR)\qwmChkPcInfo.obj"
	-@erase "$(INTDIR)\qwmChkProxyCfg.obj"
	-@erase "$(INTDIR)\qwmChkRas.obj"
	-@erase "$(INTDIR)\qwmChkRecent.obj"
	-@erase "$(INTDIR)\qwmChkRecycler.obj"
	-@erase "$(INTDIR)\qwmChkRemovableStorage.obj"
	-@erase "$(INTDIR)\qwmChkShare.obj"
	-@erase "$(INTDIR)\qwmChkSoftwareInstalled.obj"
	-@erase "$(INTDIR)\qwmChkUsrInfo.obj"
	-@erase "$(INTDIR)\qwmFunc.obj"
	-@erase "$(INTDIR)\qwmGetAssetFunc.obj"
	-@erase "$(INTDIR)\qwmGetAssetsInfo.obj"
	-@erase "$(INTDIR)\qwmHideProcessCommProc.obj"
	-@erase "$(INTDIR)\qwmOutputFile.obj"
	-@erase "$(INTDIR)\qwmRegProcHelp.obj"
	-@erase "$(INTDIR)\qwmSecChkProc.obj"
	-@erase "$(INTDIR)\qwmSecChkTemp.obj"
	-@erase "$(INTDIR)\qwmSockFunc.obj"
	-@erase "$(INTDIR)\qyCommProc.obj"
	-@erase "$(INTDIR)\split_at.obj"
	-@erase "$(INTDIR)\testDiskIOProc.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\qwmShared.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "." /I "..\include" /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\qwmShared.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qwmShared.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\qwmShared.lib" 
LIB32_OBJS= \
	"$(INTDIR)\qwmChkDiskDrvFile.obj" \
	"$(INTDIR)\qwmChkIe.obj" \
	"$(INTDIR)\qwmChkInternet.obj" \
	"$(INTDIR)\qwmChkNormalFile.obj" \
	"$(INTDIR)\qwmChkOsInfo.obj" \
	"$(INTDIR)\qwmChkPcInfo.obj" \
	"$(INTDIR)\qwmChkProxyCfg.obj" \
	"$(INTDIR)\qwmChkRas.obj" \
	"$(INTDIR)\qwmChkRecent.obj" \
	"$(INTDIR)\qwmChkRecycler.obj" \
	"$(INTDIR)\qwmChkRemovableStorage.obj" \
	"$(INTDIR)\qwmChkShare.obj" \
	"$(INTDIR)\qwmChkSoftwareInstalled.obj" \
	"$(INTDIR)\qwmChkUsrInfo.obj" \
	"$(INTDIR)\qwmGetAssetsInfo.obj" \
	"$(INTDIR)\qwmSecChkProc.obj" \
	"$(INTDIR)\qwmSecChkTemp.obj" \
	"$(INTDIR)\cpuInfo.obj" \
	"$(INTDIR)\delSelf.obj" \
	"$(INTDIR)\functions.obj" \
	"$(INTDIR)\qwmFunc.obj" \
	"$(INTDIR)\qwmGetAssetFunc.obj" \
	"$(INTDIR)\qwmOutputFile.obj" \
	"$(INTDIR)\qwmRegProcHelp.obj" \
	"$(INTDIR)\qwmSockFunc.obj" \
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
	"$(INTDIR)\testDiskIOProc.obj" \
	"$(INTDIR)\qnmAssetsCommProc.obj" \
	"$(INTDIR)\qnmAssetsTemp.obj" \
	"$(INTDIR)\qnmChkCommProc.obj" \
	"$(INTDIR)\qnmCommProc.obj" \
	"$(INTDIR)\qwmHideProcessCommProc.obj" \
	"$(INTDIR)\qyCommProc.obj"

"$(OUTDIR)\qwmShared.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"

OUTDIR=.\..\..\..\Debug\lib
INTDIR=.\..\..\..\o\qwmShared\Debug
# Begin Custom Macros
OutDir=.\..\..\..\Debug\lib
# End Custom Macros

ALL : "$(OUTDIR)\qwmShared.lib" "$(OUTDIR)\qwmShared.bsc"


CLEAN :
	-@erase "$(INTDIR)\cpuInfo.obj"
	-@erase "$(INTDIR)\cpuInfo.sbr"
	-@erase "$(INTDIR)\delSelf.obj"
	-@erase "$(INTDIR)\delSelf.sbr"
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
	-@erase "$(INTDIR)\mymalloc.obj"
	-@erase "$(INTDIR)\mymalloc.sbr"
	-@erase "$(INTDIR)\ntfs.obj"
	-@erase "$(INTDIR)\ntfs.sbr"
	-@erase "$(INTDIR)\ntfs_dent.obj"
	-@erase "$(INTDIR)\ntfs_dent.sbr"
	-@erase "$(INTDIR)\qnmAssetsCommProc.obj"
	-@erase "$(INTDIR)\qnmAssetsCommProc.sbr"
	-@erase "$(INTDIR)\qnmAssetsTemp.obj"
	-@erase "$(INTDIR)\qnmAssetsTemp.sbr"
	-@erase "$(INTDIR)\qnmChkCommProc.obj"
	-@erase "$(INTDIR)\qnmChkCommProc.sbr"
	-@erase "$(INTDIR)\qnmCommProc.obj"
	-@erase "$(INTDIR)\qnmCommProc.sbr"
	-@erase "$(INTDIR)\qwmChkDiskDrvFile.obj"
	-@erase "$(INTDIR)\qwmChkDiskDrvFile.sbr"
	-@erase "$(INTDIR)\qwmChkIe.obj"
	-@erase "$(INTDIR)\qwmChkIe.sbr"
	-@erase "$(INTDIR)\qwmChkInternet.obj"
	-@erase "$(INTDIR)\qwmChkInternet.sbr"
	-@erase "$(INTDIR)\qwmChkNormalFile.obj"
	-@erase "$(INTDIR)\qwmChkNormalFile.sbr"
	-@erase "$(INTDIR)\qwmChkOsInfo.obj"
	-@erase "$(INTDIR)\qwmChkOsInfo.sbr"
	-@erase "$(INTDIR)\qwmChkPcInfo.obj"
	-@erase "$(INTDIR)\qwmChkPcInfo.sbr"
	-@erase "$(INTDIR)\qwmChkProxyCfg.obj"
	-@erase "$(INTDIR)\qwmChkProxyCfg.sbr"
	-@erase "$(INTDIR)\qwmChkRas.obj"
	-@erase "$(INTDIR)\qwmChkRas.sbr"
	-@erase "$(INTDIR)\qwmChkRecent.obj"
	-@erase "$(INTDIR)\qwmChkRecent.sbr"
	-@erase "$(INTDIR)\qwmChkRecycler.obj"
	-@erase "$(INTDIR)\qwmChkRecycler.sbr"
	-@erase "$(INTDIR)\qwmChkRemovableStorage.obj"
	-@erase "$(INTDIR)\qwmChkRemovableStorage.sbr"
	-@erase "$(INTDIR)\qwmChkShare.obj"
	-@erase "$(INTDIR)\qwmChkShare.sbr"
	-@erase "$(INTDIR)\qwmChkSoftwareInstalled.obj"
	-@erase "$(INTDIR)\qwmChkSoftwareInstalled.sbr"
	-@erase "$(INTDIR)\qwmChkUsrInfo.obj"
	-@erase "$(INTDIR)\qwmChkUsrInfo.sbr"
	-@erase "$(INTDIR)\qwmFunc.obj"
	-@erase "$(INTDIR)\qwmFunc.sbr"
	-@erase "$(INTDIR)\qwmGetAssetFunc.obj"
	-@erase "$(INTDIR)\qwmGetAssetFunc.sbr"
	-@erase "$(INTDIR)\qwmGetAssetsInfo.obj"
	-@erase "$(INTDIR)\qwmGetAssetsInfo.sbr"
	-@erase "$(INTDIR)\qwmHideProcessCommProc.obj"
	-@erase "$(INTDIR)\qwmHideProcessCommProc.sbr"
	-@erase "$(INTDIR)\qwmOutputFile.obj"
	-@erase "$(INTDIR)\qwmOutputFile.sbr"
	-@erase "$(INTDIR)\qwmRegProcHelp.obj"
	-@erase "$(INTDIR)\qwmRegProcHelp.sbr"
	-@erase "$(INTDIR)\qwmSecChkProc.obj"
	-@erase "$(INTDIR)\qwmSecChkProc.sbr"
	-@erase "$(INTDIR)\qwmSecChkTemp.obj"
	-@erase "$(INTDIR)\qwmSecChkTemp.sbr"
	-@erase "$(INTDIR)\qwmSockFunc.obj"
	-@erase "$(INTDIR)\qwmSockFunc.sbr"
	-@erase "$(INTDIR)\qyCommProc.obj"
	-@erase "$(INTDIR)\qyCommProc.sbr"
	-@erase "$(INTDIR)\split_at.obj"
	-@erase "$(INTDIR)\split_at.sbr"
	-@erase "$(INTDIR)\testDiskIOProc.obj"
	-@erase "$(INTDIR)\testDiskIOProc.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\qwmShared.bsc"
	-@erase "$(OUTDIR)\qwmShared.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "." /I "..\include" /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qwmShared.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qwmShared.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\qwmChkDiskDrvFile.sbr" \
	"$(INTDIR)\qwmChkIe.sbr" \
	"$(INTDIR)\qwmChkInternet.sbr" \
	"$(INTDIR)\qwmChkNormalFile.sbr" \
	"$(INTDIR)\qwmChkOsInfo.sbr" \
	"$(INTDIR)\qwmChkPcInfo.sbr" \
	"$(INTDIR)\qwmChkProxyCfg.sbr" \
	"$(INTDIR)\qwmChkRas.sbr" \
	"$(INTDIR)\qwmChkRecent.sbr" \
	"$(INTDIR)\qwmChkRecycler.sbr" \
	"$(INTDIR)\qwmChkRemovableStorage.sbr" \
	"$(INTDIR)\qwmChkShare.sbr" \
	"$(INTDIR)\qwmChkSoftwareInstalled.sbr" \
	"$(INTDIR)\qwmChkUsrInfo.sbr" \
	"$(INTDIR)\qwmGetAssetsInfo.sbr" \
	"$(INTDIR)\qwmSecChkProc.sbr" \
	"$(INTDIR)\qwmSecChkTemp.sbr" \
	"$(INTDIR)\cpuInfo.sbr" \
	"$(INTDIR)\delSelf.sbr" \
	"$(INTDIR)\functions.sbr" \
	"$(INTDIR)\qwmFunc.sbr" \
	"$(INTDIR)\qwmGetAssetFunc.sbr" \
	"$(INTDIR)\qwmOutputFile.sbr" \
	"$(INTDIR)\qwmRegProcHelp.sbr" \
	"$(INTDIR)\qwmSockFunc.sbr" \
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
	"$(INTDIR)\split_at.sbr" \
	"$(INTDIR)\testDiskIOProc.sbr" \
	"$(INTDIR)\qnmAssetsCommProc.sbr" \
	"$(INTDIR)\qnmAssetsTemp.sbr" \
	"$(INTDIR)\qnmChkCommProc.sbr" \
	"$(INTDIR)\qnmCommProc.sbr" \
	"$(INTDIR)\qwmHideProcessCommProc.sbr" \
	"$(INTDIR)\qyCommProc.sbr"

"$(OUTDIR)\qwmShared.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\qwmShared.lib" 
LIB32_OBJS= \
	"$(INTDIR)\qwmChkDiskDrvFile.obj" \
	"$(INTDIR)\qwmChkIe.obj" \
	"$(INTDIR)\qwmChkInternet.obj" \
	"$(INTDIR)\qwmChkNormalFile.obj" \
	"$(INTDIR)\qwmChkOsInfo.obj" \
	"$(INTDIR)\qwmChkPcInfo.obj" \
	"$(INTDIR)\qwmChkProxyCfg.obj" \
	"$(INTDIR)\qwmChkRas.obj" \
	"$(INTDIR)\qwmChkRecent.obj" \
	"$(INTDIR)\qwmChkRecycler.obj" \
	"$(INTDIR)\qwmChkRemovableStorage.obj" \
	"$(INTDIR)\qwmChkShare.obj" \
	"$(INTDIR)\qwmChkSoftwareInstalled.obj" \
	"$(INTDIR)\qwmChkUsrInfo.obj" \
	"$(INTDIR)\qwmGetAssetsInfo.obj" \
	"$(INTDIR)\qwmSecChkProc.obj" \
	"$(INTDIR)\qwmSecChkTemp.obj" \
	"$(INTDIR)\cpuInfo.obj" \
	"$(INTDIR)\delSelf.obj" \
	"$(INTDIR)\functions.obj" \
	"$(INTDIR)\qwmFunc.obj" \
	"$(INTDIR)\qwmGetAssetFunc.obj" \
	"$(INTDIR)\qwmOutputFile.obj" \
	"$(INTDIR)\qwmRegProcHelp.obj" \
	"$(INTDIR)\qwmSockFunc.obj" \
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
	"$(INTDIR)\testDiskIOProc.obj" \
	"$(INTDIR)\qnmAssetsCommProc.obj" \
	"$(INTDIR)\qnmAssetsTemp.obj" \
	"$(INTDIR)\qnmChkCommProc.obj" \
	"$(INTDIR)\qnmCommProc.obj" \
	"$(INTDIR)\qwmHideProcessCommProc.obj" \
	"$(INTDIR)\qyCommProc.obj"

"$(OUTDIR)\qwmShared.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("qwmShared.dep")
!INCLUDE "qwmShared.dep"
!ELSE 
!MESSAGE Warning: cannot find "qwmShared.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "qwmShared - Win32 Release" || "$(CFG)" == "qwmShared - Win32 Debug"
SOURCE=..\qyRegTool\qrtSecChk\qwmChkDiskDrvFile.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qwmChkDiskDrvFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qwmChkDiskDrvFile.obj"	"$(INTDIR)\qwmChkDiskDrvFile.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmChkIe.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qwmChkIe.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qwmChkIe.obj"	"$(INTDIR)\qwmChkIe.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmChkInternet.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qwmChkInternet.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qwmChkInternet.obj"	"$(INTDIR)\qwmChkInternet.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmChkNormalFile.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qwmChkNormalFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qwmChkNormalFile.obj"	"$(INTDIR)\qwmChkNormalFile.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmChkOsInfo.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qwmChkOsInfo.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qwmChkOsInfo.obj"	"$(INTDIR)\qwmChkOsInfo.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmChkPcInfo.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qwmChkPcInfo.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qwmChkPcInfo.obj"	"$(INTDIR)\qwmChkPcInfo.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmChkProxyCfg.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qwmChkProxyCfg.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qwmChkProxyCfg.obj"	"$(INTDIR)\qwmChkProxyCfg.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmChkRas.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qwmChkRas.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qwmChkRas.obj"	"$(INTDIR)\qwmChkRas.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmChkRecent.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qwmChkRecent.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qwmChkRecent.obj"	"$(INTDIR)\qwmChkRecent.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmChkRecycler.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qwmChkRecycler.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qwmChkRecycler.obj"	"$(INTDIR)\qwmChkRecycler.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmChkRemovableStorage.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qwmChkRemovableStorage.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qwmChkRemovableStorage.obj"	"$(INTDIR)\qwmChkRemovableStorage.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmChkShare.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qwmChkShare.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qwmChkShare.obj"	"$(INTDIR)\qwmChkShare.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmChkSoftwareInstalled.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qwmChkSoftwareInstalled.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qwmChkSoftwareInstalled.obj"	"$(INTDIR)\qwmChkSoftwareInstalled.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmChkUsrInfo.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qwmChkUsrInfo.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qwmChkUsrInfo.obj"	"$(INTDIR)\qwmChkUsrInfo.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmGetAssetsInfo.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qwmGetAssetsInfo.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qwmGetAssetsInfo.obj"	"$(INTDIR)\qwmGetAssetsInfo.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmSecChkProc.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qwmSecChkProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qwmSecChkProc.obj"	"$(INTDIR)\qwmSecChkProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qyRegTool\qrtSecChk\qwmSecChkTemp.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qwmSecChkTemp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qwmSecChkTemp.obj"	"$(INTDIR)\qwmSecChkTemp.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qwmPublic\cpuInfo.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\cpuInfo.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\cpuInfo.obj"	"$(INTDIR)\cpuInfo.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qwmPublic\delSelf.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\delSelf.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\delSelf.obj"	"$(INTDIR)\delSelf.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qwmPublic\functions.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\functions.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\functions.obj"	"$(INTDIR)\functions.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qwmPublic\qwmFunc.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qwmFunc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qwmFunc.obj"	"$(INTDIR)\qwmFunc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qwmPublic\qwmGetAssetFunc.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qwmGetAssetFunc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qwmGetAssetFunc.obj"	"$(INTDIR)\qwmGetAssetFunc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qwmPublic\qwmOutputFile.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qwmOutputFile.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qwmOutputFile.obj"	"$(INTDIR)\qwmOutputFile.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qwmPublic\qwmRegProcHelp.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qwmRegProcHelp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qwmRegProcHelp.obj"	"$(INTDIR)\qwmRegProcHelp.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\qwmPublic\qwmSockFunc.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qwmSockFunc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qwmSockFunc.obj"	"$(INTDIR)\qwmSockFunc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\diskIO.c

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\diskIO.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\diskIO.obj"	"$(INTDIR)\diskIO.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\error.c

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\error.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\error.obj"	"$(INTDIR)\error.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\fatFs.c

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\fatFs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\fatFs.obj"	"$(INTDIR)\fatFs.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\fatfs_dent.c

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\fatfs_dent.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\fatfs_dent.obj"	"$(INTDIR)\fatfs_dent.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\fs_buf.c

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\fs_buf.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\fs_buf.obj"	"$(INTDIR)\fs_buf.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\fs_data.c

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\fs_data.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\fs_data.obj"	"$(INTDIR)\fs_data.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\fs_dent.c

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\fs_dent.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\fs_dent.obj"	"$(INTDIR)\fs_dent.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\fs_inode.c

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\fs_inode.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\fs_inode.obj"	"$(INTDIR)\fs_inode.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\fs_io.c

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\fs_io.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\fs_io.obj"	"$(INTDIR)\fs_io.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\fs_open.c

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\fs_open.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\fs_open.obj"	"$(INTDIR)\fs_open.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\fs_types.c

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\fs_types.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\fs_types.obj"	"$(INTDIR)\fs_types.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\get.c

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\get.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\get.obj"	"$(INTDIR)\get.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\ils.c

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\ils.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\ils.obj"	"$(INTDIR)\ils.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\mymalloc.c

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\mymalloc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\mymalloc.obj"	"$(INTDIR)\mymalloc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\ntfs.c

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\ntfs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\ntfs.obj"	"$(INTDIR)\ntfs.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\ntfs_dent.c

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\ntfs_dent.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\ntfs_dent.obj"	"$(INTDIR)\ntfs_dent.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\split_at.c

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\split_at.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\split_at.obj"	"$(INTDIR)\split_at.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyProjShare\chkDisk\testDiskIOProc.c

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\testDiskIOProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\testDiskIOProc.obj"	"$(INTDIR)\testDiskIOProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyCommProc\qnmAssetsCommProc.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qnmAssetsCommProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qnmAssetsCommProc.obj"	"$(INTDIR)\qnmAssetsCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyCommProc\qnmAssetsTemp.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qnmAssetsTemp.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qnmAssetsTemp.obj"	"$(INTDIR)\qnmAssetsTemp.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyCommProc\qnmChkCommProc.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qnmChkCommProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qnmChkCommProc.obj"	"$(INTDIR)\qnmChkCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyCommProc\qnmCommProc.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qnmCommProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qnmCommProc.obj"	"$(INTDIR)\qnmCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyCommProc\qwmHideProcessCommProc.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qwmHideProcessCommProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qwmHideProcessCommProc.obj"	"$(INTDIR)\qwmHideProcessCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\qyCommProc\qyCommProc.cpp

!IF  "$(CFG)" == "qwmShared - Win32 Release"


"$(INTDIR)\qyCommProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmShared - Win32 Debug"


"$(INTDIR)\qyCommProc.obj"	"$(INTDIR)\qyCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

