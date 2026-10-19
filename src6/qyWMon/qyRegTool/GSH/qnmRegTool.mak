# Microsoft Developer Studio Generated NMAKE File, Based on qnmRegTool.dsp
!IF "$(CFG)" == ""
CFG=qnmRegTool - Win32 Debug for Nms 98
!MESSAGE No configuration specified. Defaulting to qnmRegTool - Win32 Debug for Nms 98.
!ENDIF 

!IF "$(CFG)" != "qnmRegTool - Win32 Release" && "$(CFG)" != "qnmRegTool - Win32 Debug" && "$(CFG)" != "qnmRegTool - Win32 Release for Nms" && "$(CFG)" != "qnmRegTool - Win32 Debug for Nms" && "$(CFG)" != "qnmRegTool - Win32 Release for 98" && "$(CFG)" != "qnmRegTool - Win32 Debug for 98" && "$(CFG)" != "qnmRegTool - Win32 Release for Nms 98" && "$(CFG)" != "qnmRegTool - Win32 Debug for Nms 98"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "qnmRegTool.mak" CFG="qnmRegTool - Win32 Debug for Nms 98"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "qnmRegTool - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "qnmRegTool - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "qnmRegTool - Win32 Release for Nms" (based on "Win32 (x86) Application")
!MESSAGE "qnmRegTool - Win32 Debug for Nms" (based on "Win32 (x86) Application")
!MESSAGE "qnmRegTool - Win32 Release for 98" (based on "Win32 (x86) Application")
!MESSAGE "qnmRegTool - Win32 Debug for 98" (based on "Win32 (x86) Application")
!MESSAGE "qnmRegTool - Win32 Release for Nms 98" (based on "Win32 (x86) Application")
!MESSAGE "qnmRegTool - Win32 Debug for Nms 98" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "qnmRegTool - Win32 Release"

OUTDIR=.\..\..\..\..\Release\bin
INTDIR=.\..\..\..\..\o\qnmRegTool\Release
# Begin Custom Macros
OutDir=.\..\..\..\..\Release\bin
# End Custom Macros

ALL : "$(OUTDIR)\qyRegTool.exe" "..\..\..\..\o\qnmRegTool\Release\qnmRegTool.pch" "$(OUTDIR)\qnmRegTool.bsc"


CLEAN :
	-@erase "$(INTDIR)\qnmCustom.obj"
	-@erase "$(INTDIR)\qnmCustom.sbr"
	-@erase "$(INTDIR)\qnmCustomRegTool.obj"
	-@erase "$(INTDIR)\qnmCustomRegTool.sbr"
	-@erase "$(INTDIR)\qnmGuiCommProc.obj"
	-@erase "$(INTDIR)\qnmGuiCommProc.sbr"
	-@erase "$(INTDIR)\qnmHotKeys.obj"
	-@erase "$(INTDIR)\qnmHotKeys.sbr"
	-@erase "$(INTDIR)\qnmRegTool.obj"
	-@erase "$(INTDIR)\qnmRegTool.pch"
	-@erase "$(INTDIR)\qnmRegTool.res"
	-@erase "$(INTDIR)\qnmRegTool.sbr"
	-@erase "$(INTDIR)\qwmAllHints.obj"
	-@erase "$(INTDIR)\qwmAllHints.sbr"
	-@erase "$(INTDIR)\qwmRegProc.obj"
	-@erase "$(INTDIR)\qwmRegProc.sbr"
	-@erase "$(INTDIR)\qyCustom.obj"
	-@erase "$(INTDIR)\qyCustom.sbr"
	-@erase "$(INTDIR)\qyRegToolProc.obj"
	-@erase "$(INTDIR)\qyRegToolProc.sbr"
	-@erase "$(INTDIR)\qyTCharCommProc.obj"
	-@erase "$(INTDIR)\qyTCharCommProc.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\qnmRegTool.bsc"
	-@erase "$(OUTDIR)\qyRegTool.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qnmRegTool.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\qnmRegTool.res" /i "..\..\..\qyCommProc\include" /i "..\..\..\qyCustom\include" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qnmRegTool.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\qnmRegTool.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\qnmCustom.sbr" \
	"$(INTDIR)\qnmCustomRegTool.sbr" \
	"$(INTDIR)\qwmAllHints.sbr" \
	"$(INTDIR)\qyCustom.sbr" \
	"$(INTDIR)\qyRegToolProc.sbr" \
	"$(INTDIR)\qwmRegProc.sbr" \
	"$(INTDIR)\qnmGuiCommProc.sbr" \
	"$(INTDIR)\qnmHotKeys.sbr" \
	"$(INTDIR)\qyTCharCommProc.sbr"

"$(OUTDIR)\qnmRegTool.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=qwmShared.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib qyPublicStaticNoMfc.lib qyEncLibStaticNoMfc.lib mpr.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\qyRegTool.pdb" /machine:I386 /out:"$(OUTDIR)\qyRegTool.exe" /libpath:"..\..\..\..\Release\lib" 
LINK32_OBJS= \
	"$(INTDIR)\qnmRegTool.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\qnmCustom.obj" \
	"$(INTDIR)\qnmCustomRegTool.obj" \
	"$(INTDIR)\qwmAllHints.obj" \
	"$(INTDIR)\qyCustom.obj" \
	"$(INTDIR)\qyRegToolProc.obj" \
	"$(INTDIR)\qwmRegProc.obj" \
	"$(INTDIR)\qnmGuiCommProc.obj" \
	"$(INTDIR)\qnmHotKeys.obj" \
	"$(INTDIR)\qyTCharCommProc.obj" \
	"$(INTDIR)\qnmRegTool.res"

"$(OUTDIR)\qyRegTool.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug"

OUTDIR=.\..\..\..\..\Debug\bin
INTDIR=.\..\..\..\..\o\qnmRegTool\Debug
# Begin Custom Macros
OutDir=.\..\..\..\..\Debug\bin
# End Custom Macros

ALL : "$(OUTDIR)\qyRegTool.exe" "..\..\..\..\o\qnmRegTool\Debug\qnmRegTool.pch" "$(OUTDIR)\qnmRegTool.bsc"


CLEAN :
	-@erase "$(INTDIR)\qnmCustom.obj"
	-@erase "$(INTDIR)\qnmCustom.sbr"
	-@erase "$(INTDIR)\qnmCustomRegTool.obj"
	-@erase "$(INTDIR)\qnmCustomRegTool.sbr"
	-@erase "$(INTDIR)\qnmGuiCommProc.obj"
	-@erase "$(INTDIR)\qnmGuiCommProc.sbr"
	-@erase "$(INTDIR)\qnmHotKeys.obj"
	-@erase "$(INTDIR)\qnmHotKeys.sbr"
	-@erase "$(INTDIR)\qnmRegTool.obj"
	-@erase "$(INTDIR)\qnmRegTool.pch"
	-@erase "$(INTDIR)\qnmRegTool.res"
	-@erase "$(INTDIR)\qnmRegTool.sbr"
	-@erase "$(INTDIR)\qwmAllHints.obj"
	-@erase "$(INTDIR)\qwmAllHints.sbr"
	-@erase "$(INTDIR)\qwmRegProc.obj"
	-@erase "$(INTDIR)\qwmRegProc.sbr"
	-@erase "$(INTDIR)\qyCustom.obj"
	-@erase "$(INTDIR)\qyCustom.sbr"
	-@erase "$(INTDIR)\qyRegToolProc.obj"
	-@erase "$(INTDIR)\qyRegToolProc.sbr"
	-@erase "$(INTDIR)\qyTCharCommProc.obj"
	-@erase "$(INTDIR)\qyTCharCommProc.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\qnmRegTool.bsc"
	-@erase "$(OUTDIR)\qyRegTool.exe"
	-@erase "$(OUTDIR)\qyRegTool.ilk"
	-@erase "$(OUTDIR)\qyRegTool.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qnmRegTool.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\qnmRegTool.res" /i "..\..\..\qyCommProc\include" /i "..\..\..\qyCustom\include" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qnmRegTool.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\qnmRegTool.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\qnmCustom.sbr" \
	"$(INTDIR)\qnmCustomRegTool.sbr" \
	"$(INTDIR)\qwmAllHints.sbr" \
	"$(INTDIR)\qyCustom.sbr" \
	"$(INTDIR)\qyRegToolProc.sbr" \
	"$(INTDIR)\qwmRegProc.sbr" \
	"$(INTDIR)\qnmGuiCommProc.sbr" \
	"$(INTDIR)\qnmHotKeys.sbr" \
	"$(INTDIR)\qyTCharCommProc.sbr"

"$(OUTDIR)\qnmRegTool.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=qwmShared.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib qyPublicStaticNoMfc.lib qyEncLibStaticNoMfc.lib mpr.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\qyRegTool.pdb" /debug /machine:I386 /out:"$(OUTDIR)\qyRegTool.exe" /pdbtype:sept /libpath:"..\..\..\..\Debug\lib" 
LINK32_OBJS= \
	"$(INTDIR)\qnmRegTool.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\qnmCustom.obj" \
	"$(INTDIR)\qnmCustomRegTool.obj" \
	"$(INTDIR)\qwmAllHints.obj" \
	"$(INTDIR)\qyCustom.obj" \
	"$(INTDIR)\qyRegToolProc.obj" \
	"$(INTDIR)\qwmRegProc.obj" \
	"$(INTDIR)\qnmGuiCommProc.obj" \
	"$(INTDIR)\qnmHotKeys.obj" \
	"$(INTDIR)\qyTCharCommProc.obj" \
	"$(INTDIR)\qnmRegTool.res"

"$(OUTDIR)\qyRegTool.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for Nms"

OUTDIR=.\..\..\..\..\Release\bin
INTDIR=.\..\..\..\..\o\qnmRegTool\ReleaseForQnm
# Begin Custom Macros
OutDir=.\..\..\..\..\Release\bin
# End Custom Macros

ALL : "$(OUTDIR)\qyRegToolForNms.exe" "..\..\..\..\o\qnmRegTool\ReleaseForQnm\qnmRegTool.pch" "$(OUTDIR)\qnmRegTool.bsc"


CLEAN :
	-@erase "$(INTDIR)\qnmCustom.obj"
	-@erase "$(INTDIR)\qnmCustom.sbr"
	-@erase "$(INTDIR)\qnmCustomRegTool.obj"
	-@erase "$(INTDIR)\qnmCustomRegTool.sbr"
	-@erase "$(INTDIR)\qnmGuiCommProc.obj"
	-@erase "$(INTDIR)\qnmGuiCommProc.sbr"
	-@erase "$(INTDIR)\qnmHotKeys.obj"
	-@erase "$(INTDIR)\qnmHotKeys.sbr"
	-@erase "$(INTDIR)\qnmRegTool.obj"
	-@erase "$(INTDIR)\qnmRegTool.pch"
	-@erase "$(INTDIR)\qnmRegTool.res"
	-@erase "$(INTDIR)\qnmRegTool.sbr"
	-@erase "$(INTDIR)\qwmAllHints.obj"
	-@erase "$(INTDIR)\qwmAllHints.sbr"
	-@erase "$(INTDIR)\qwmRegProc.obj"
	-@erase "$(INTDIR)\qwmRegProc.sbr"
	-@erase "$(INTDIR)\qyCustom.obj"
	-@erase "$(INTDIR)\qyCustom.sbr"
	-@erase "$(INTDIR)\qyRegToolProc.obj"
	-@erase "$(INTDIR)\qyRegToolProc.sbr"
	-@erase "$(INTDIR)\qyTCharCommProc.obj"
	-@erase "$(INTDIR)\qyTCharCommProc.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\qnmRegTool.bsc"
	-@erase "$(OUTDIR)\qyRegToolForNms.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qnmRegTool.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\qnmRegTool.res" /i "..\..\..\qyCommProc\include" /i "..\..\..\qyCustom\include" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qnmRegTool.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\qnmRegTool.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\qnmCustom.sbr" \
	"$(INTDIR)\qnmCustomRegTool.sbr" \
	"$(INTDIR)\qwmAllHints.sbr" \
	"$(INTDIR)\qyCustom.sbr" \
	"$(INTDIR)\qyRegToolProc.sbr" \
	"$(INTDIR)\qwmRegProc.sbr" \
	"$(INTDIR)\qnmGuiCommProc.sbr" \
	"$(INTDIR)\qnmHotKeys.sbr" \
	"$(INTDIR)\qyTCharCommProc.sbr"

"$(OUTDIR)\qnmRegTool.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=qwmShared.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib qyPublicStaticNoMfc.lib qyEncLibStaticNoMfc.lib mpr.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\qyRegToolForNms.pdb" /machine:I386 /out:"$(OUTDIR)\qyRegToolForNms.exe" /libpath:"..\..\..\..\Release\lib" 
LINK32_OBJS= \
	"$(INTDIR)\qnmRegTool.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\qnmCustom.obj" \
	"$(INTDIR)\qnmCustomRegTool.obj" \
	"$(INTDIR)\qwmAllHints.obj" \
	"$(INTDIR)\qyCustom.obj" \
	"$(INTDIR)\qyRegToolProc.obj" \
	"$(INTDIR)\qwmRegProc.obj" \
	"$(INTDIR)\qnmGuiCommProc.obj" \
	"$(INTDIR)\qnmHotKeys.obj" \
	"$(INTDIR)\qyTCharCommProc.obj" \
	"$(INTDIR)\qnmRegTool.res"

"$(OUTDIR)\qyRegToolForNms.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for Nms"

OUTDIR=.\..\..\..\..\Debug\bin
INTDIR=.\..\..\..\..\o\qnmRegTool\DebugForQnm
# Begin Custom Macros
OutDir=.\..\..\..\..\Debug\bin
# End Custom Macros

ALL : "$(OUTDIR)\qyRegToolForNms.exe" "..\..\..\..\o\qnmRegTool\DebugForQnm\qnmRegTool.pch" "$(OUTDIR)\qnmRegTool.bsc"


CLEAN :
	-@erase "$(INTDIR)\qnmCustom.obj"
	-@erase "$(INTDIR)\qnmCustom.sbr"
	-@erase "$(INTDIR)\qnmCustomRegTool.obj"
	-@erase "$(INTDIR)\qnmCustomRegTool.sbr"
	-@erase "$(INTDIR)\qnmGuiCommProc.obj"
	-@erase "$(INTDIR)\qnmGuiCommProc.sbr"
	-@erase "$(INTDIR)\qnmHotKeys.obj"
	-@erase "$(INTDIR)\qnmHotKeys.sbr"
	-@erase "$(INTDIR)\qnmRegTool.obj"
	-@erase "$(INTDIR)\qnmRegTool.pch"
	-@erase "$(INTDIR)\qnmRegTool.res"
	-@erase "$(INTDIR)\qnmRegTool.sbr"
	-@erase "$(INTDIR)\qwmAllHints.obj"
	-@erase "$(INTDIR)\qwmAllHints.sbr"
	-@erase "$(INTDIR)\qwmRegProc.obj"
	-@erase "$(INTDIR)\qwmRegProc.sbr"
	-@erase "$(INTDIR)\qyCustom.obj"
	-@erase "$(INTDIR)\qyCustom.sbr"
	-@erase "$(INTDIR)\qyRegToolProc.obj"
	-@erase "$(INTDIR)\qyRegToolProc.sbr"
	-@erase "$(INTDIR)\qyTCharCommProc.obj"
	-@erase "$(INTDIR)\qyTCharCommProc.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\qnmRegTool.bsc"
	-@erase "$(OUTDIR)\qyRegToolForNms.exe"
	-@erase "$(OUTDIR)\qyRegToolForNms.ilk"
	-@erase "$(OUTDIR)\qyRegToolForNms.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qnmRegTool.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\qnmRegTool.res" /i "..\..\..\qyCommProc\include" /i "..\..\..\qyCustom\include" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qnmRegTool.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\qnmRegTool.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\qnmCustom.sbr" \
	"$(INTDIR)\qnmCustomRegTool.sbr" \
	"$(INTDIR)\qwmAllHints.sbr" \
	"$(INTDIR)\qyCustom.sbr" \
	"$(INTDIR)\qyRegToolProc.sbr" \
	"$(INTDIR)\qwmRegProc.sbr" \
	"$(INTDIR)\qnmGuiCommProc.sbr" \
	"$(INTDIR)\qnmHotKeys.sbr" \
	"$(INTDIR)\qyTCharCommProc.sbr"

"$(OUTDIR)\qnmRegTool.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=qwmShared.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib qyPublicStaticNoMfc.lib qyEncLibStaticNoMfc.lib mpr.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\qyRegToolForNms.pdb" /debug /machine:I386 /out:"$(OUTDIR)\qyRegToolForNms.exe" /pdbtype:sept /libpath:"..\..\..\..\Debug\lib" 
LINK32_OBJS= \
	"$(INTDIR)\qnmRegTool.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\qnmCustom.obj" \
	"$(INTDIR)\qnmCustomRegTool.obj" \
	"$(INTDIR)\qwmAllHints.obj" \
	"$(INTDIR)\qyCustom.obj" \
	"$(INTDIR)\qyRegToolProc.obj" \
	"$(INTDIR)\qwmRegProc.obj" \
	"$(INTDIR)\qnmGuiCommProc.obj" \
	"$(INTDIR)\qnmHotKeys.obj" \
	"$(INTDIR)\qyTCharCommProc.obj" \
	"$(INTDIR)\qnmRegTool.res"

"$(OUTDIR)\qyRegToolForNms.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for 98"

OUTDIR=.\..\..\..\..\Release\bin
INTDIR=.\..\..\..\..\o\qnmRegTool\Releasefor98
# Begin Custom Macros
OutDir=.\..\..\..\..\Release\bin
# End Custom Macros

ALL : "$(OUTDIR)\qyRegTool98.exe" "..\..\..\..\o\qnmRegTool\Releasefor98\qnmRegTool.pch" "$(OUTDIR)\qnmRegTool.bsc"


CLEAN :
	-@erase "$(INTDIR)\qnmCustom.obj"
	-@erase "$(INTDIR)\qnmCustom.sbr"
	-@erase "$(INTDIR)\qnmCustomRegTool.obj"
	-@erase "$(INTDIR)\qnmCustomRegTool.sbr"
	-@erase "$(INTDIR)\qnmGuiCommProc.obj"
	-@erase "$(INTDIR)\qnmGuiCommProc.sbr"
	-@erase "$(INTDIR)\qnmHotKeys.obj"
	-@erase "$(INTDIR)\qnmHotKeys.sbr"
	-@erase "$(INTDIR)\qnmRegTool.obj"
	-@erase "$(INTDIR)\qnmRegTool.pch"
	-@erase "$(INTDIR)\qnmRegTool.res"
	-@erase "$(INTDIR)\qnmRegTool.sbr"
	-@erase "$(INTDIR)\qwmAllHints.obj"
	-@erase "$(INTDIR)\qwmAllHints.sbr"
	-@erase "$(INTDIR)\qwmRegProc.obj"
	-@erase "$(INTDIR)\qwmRegProc.sbr"
	-@erase "$(INTDIR)\qyCustom.obj"
	-@erase "$(INTDIR)\qyCustom.sbr"
	-@erase "$(INTDIR)\qyRegToolProc.obj"
	-@erase "$(INTDIR)\qyRegToolProc.sbr"
	-@erase "$(INTDIR)\qyTCharCommProc.obj"
	-@erase "$(INTDIR)\qyTCharCommProc.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\qnmRegTool.bsc"
	-@erase "$(OUTDIR)\qyRegTool98.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qnmRegTool.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\qnmRegTool.res" /i "..\..\..\qyCommProc\include" /i "..\..\..\qyCustom\include" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qnmRegTool.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\qnmRegTool.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\qnmCustom.sbr" \
	"$(INTDIR)\qnmCustomRegTool.sbr" \
	"$(INTDIR)\qwmAllHints.sbr" \
	"$(INTDIR)\qyCustom.sbr" \
	"$(INTDIR)\qyRegToolProc.sbr" \
	"$(INTDIR)\qwmRegProc.sbr" \
	"$(INTDIR)\qnmGuiCommProc.sbr" \
	"$(INTDIR)\qnmHotKeys.sbr" \
	"$(INTDIR)\qyTCharCommProc.sbr"

"$(OUTDIR)\qnmRegTool.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=qwmShared.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib qyPublicStaticNoMfc.lib qyEncLibStaticNoMfc.lib mpr.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\qyRegTool98.pdb" /machine:I386 /out:"$(OUTDIR)\qyRegTool98.exe" /libpath:"..\..\..\..\Release\lib" 
LINK32_OBJS= \
	"$(INTDIR)\qnmRegTool.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\qnmCustom.obj" \
	"$(INTDIR)\qnmCustomRegTool.obj" \
	"$(INTDIR)\qwmAllHints.obj" \
	"$(INTDIR)\qyCustom.obj" \
	"$(INTDIR)\qyRegToolProc.obj" \
	"$(INTDIR)\qwmRegProc.obj" \
	"$(INTDIR)\qnmGuiCommProc.obj" \
	"$(INTDIR)\qnmHotKeys.obj" \
	"$(INTDIR)\qyTCharCommProc.obj" \
	"$(INTDIR)\qnmRegTool.res"

"$(OUTDIR)\qyRegTool98.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for 98"

OUTDIR=.\..\..\..\..\Debug\bin
INTDIR=.\..\..\..\..\o\qnmRegTool\Debugfor98
# Begin Custom Macros
OutDir=.\..\..\..\..\Debug\bin
# End Custom Macros

ALL : "$(OUTDIR)\qyRegTool98.exe" "..\..\..\..\o\qnmRegTool\Debugfor98\qnmRegTool.pch" "$(OUTDIR)\qnmRegTool.bsc"


CLEAN :
	-@erase "$(INTDIR)\qnmCustom.obj"
	-@erase "$(INTDIR)\qnmCustom.sbr"
	-@erase "$(INTDIR)\qnmCustomRegTool.obj"
	-@erase "$(INTDIR)\qnmCustomRegTool.sbr"
	-@erase "$(INTDIR)\qnmGuiCommProc.obj"
	-@erase "$(INTDIR)\qnmGuiCommProc.sbr"
	-@erase "$(INTDIR)\qnmHotKeys.obj"
	-@erase "$(INTDIR)\qnmHotKeys.sbr"
	-@erase "$(INTDIR)\qnmRegTool.obj"
	-@erase "$(INTDIR)\qnmRegTool.pch"
	-@erase "$(INTDIR)\qnmRegTool.res"
	-@erase "$(INTDIR)\qnmRegTool.sbr"
	-@erase "$(INTDIR)\qwmAllHints.obj"
	-@erase "$(INTDIR)\qwmAllHints.sbr"
	-@erase "$(INTDIR)\qwmRegProc.obj"
	-@erase "$(INTDIR)\qwmRegProc.sbr"
	-@erase "$(INTDIR)\qyCustom.obj"
	-@erase "$(INTDIR)\qyCustom.sbr"
	-@erase "$(INTDIR)\qyRegToolProc.obj"
	-@erase "$(INTDIR)\qyRegToolProc.sbr"
	-@erase "$(INTDIR)\qyTCharCommProc.obj"
	-@erase "$(INTDIR)\qyTCharCommProc.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\qnmRegTool.bsc"
	-@erase "$(OUTDIR)\qyRegTool98.exe"
	-@erase "$(OUTDIR)\qyRegTool98.ilk"
	-@erase "$(OUTDIR)\qyRegTool98.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qnmRegTool.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\qnmRegTool.res" /i "..\..\..\qyCommProc\include" /i "..\..\..\qyCustom\include" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qnmRegTool.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\qnmRegTool.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\qnmCustom.sbr" \
	"$(INTDIR)\qnmCustomRegTool.sbr" \
	"$(INTDIR)\qwmAllHints.sbr" \
	"$(INTDIR)\qyCustom.sbr" \
	"$(INTDIR)\qyRegToolProc.sbr" \
	"$(INTDIR)\qwmRegProc.sbr" \
	"$(INTDIR)\qnmGuiCommProc.sbr" \
	"$(INTDIR)\qnmHotKeys.sbr" \
	"$(INTDIR)\qyTCharCommProc.sbr"

"$(OUTDIR)\qnmRegTool.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=qwmShared.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib qyPublicStaticNoMfc.lib qyEncLibStaticNoMfc.lib mpr.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\qyRegTool98.pdb" /debug /machine:I386 /out:"$(OUTDIR)\qyRegTool98.exe" /pdbtype:sept /libpath:"..\..\..\..\Debug\lib" 
LINK32_OBJS= \
	"$(INTDIR)\qnmRegTool.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\qnmCustom.obj" \
	"$(INTDIR)\qnmCustomRegTool.obj" \
	"$(INTDIR)\qwmAllHints.obj" \
	"$(INTDIR)\qyCustom.obj" \
	"$(INTDIR)\qyRegToolProc.obj" \
	"$(INTDIR)\qwmRegProc.obj" \
	"$(INTDIR)\qnmGuiCommProc.obj" \
	"$(INTDIR)\qnmHotKeys.obj" \
	"$(INTDIR)\qyTCharCommProc.obj" \
	"$(INTDIR)\qnmRegTool.res"

"$(OUTDIR)\qyRegTool98.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for Nms 98"

OUTDIR=.\..\..\..\..\Release\bin
INTDIR=.\..\..\..\..\o\qnmRegTool\ReleaseforNms98
# Begin Custom Macros
OutDir=.\..\..\..\..\Release\bin
# End Custom Macros

ALL : "$(OUTDIR)\qyRegToolForNms98.exe" "..\..\..\..\o\qnmRegTool\ReleaseforNms98\qnmRegTool.pch" "$(OUTDIR)\qnmRegTool.bsc"


CLEAN :
	-@erase "$(INTDIR)\qnmCustom.obj"
	-@erase "$(INTDIR)\qnmCustom.sbr"
	-@erase "$(INTDIR)\qnmCustomRegTool.obj"
	-@erase "$(INTDIR)\qnmCustomRegTool.sbr"
	-@erase "$(INTDIR)\qnmGuiCommProc.obj"
	-@erase "$(INTDIR)\qnmGuiCommProc.sbr"
	-@erase "$(INTDIR)\qnmHotKeys.obj"
	-@erase "$(INTDIR)\qnmHotKeys.sbr"
	-@erase "$(INTDIR)\qnmRegTool.obj"
	-@erase "$(INTDIR)\qnmRegTool.pch"
	-@erase "$(INTDIR)\qnmRegTool.res"
	-@erase "$(INTDIR)\qnmRegTool.sbr"
	-@erase "$(INTDIR)\qwmAllHints.obj"
	-@erase "$(INTDIR)\qwmAllHints.sbr"
	-@erase "$(INTDIR)\qwmRegProc.obj"
	-@erase "$(INTDIR)\qwmRegProc.sbr"
	-@erase "$(INTDIR)\qyCustom.obj"
	-@erase "$(INTDIR)\qyCustom.sbr"
	-@erase "$(INTDIR)\qyRegToolProc.obj"
	-@erase "$(INTDIR)\qyRegToolProc.sbr"
	-@erase "$(INTDIR)\qyTCharCommProc.obj"
	-@erase "$(INTDIR)\qyTCharCommProc.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\qnmRegTool.bsc"
	-@erase "$(OUTDIR)\qyRegToolForNms98.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qnmRegTool.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\qnmRegTool.res" /i "..\..\..\qyCommProc\include" /i "..\..\..\qyCustom\include" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qnmRegTool.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\qnmRegTool.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\qnmCustom.sbr" \
	"$(INTDIR)\qnmCustomRegTool.sbr" \
	"$(INTDIR)\qwmAllHints.sbr" \
	"$(INTDIR)\qyCustom.sbr" \
	"$(INTDIR)\qyRegToolProc.sbr" \
	"$(INTDIR)\qwmRegProc.sbr" \
	"$(INTDIR)\qnmGuiCommProc.sbr" \
	"$(INTDIR)\qnmHotKeys.sbr" \
	"$(INTDIR)\qyTCharCommProc.sbr"

"$(OUTDIR)\qnmRegTool.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=qwmShared.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib qyPublicStaticNoMfc.lib qyEncLibStaticNoMfc.lib mpr.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\qyRegToolForNms98.pdb" /machine:I386 /out:"$(OUTDIR)\qyRegToolForNms98.exe" /libpath:"..\..\..\..\Release\lib" 
LINK32_OBJS= \
	"$(INTDIR)\qnmRegTool.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\qnmCustom.obj" \
	"$(INTDIR)\qnmCustomRegTool.obj" \
	"$(INTDIR)\qwmAllHints.obj" \
	"$(INTDIR)\qyCustom.obj" \
	"$(INTDIR)\qyRegToolProc.obj" \
	"$(INTDIR)\qwmRegProc.obj" \
	"$(INTDIR)\qnmGuiCommProc.obj" \
	"$(INTDIR)\qnmHotKeys.obj" \
	"$(INTDIR)\qyTCharCommProc.obj" \
	"$(INTDIR)\qnmRegTool.res"

"$(OUTDIR)\qyRegToolForNms98.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for Nms 98"

OUTDIR=.\..\..\..\..\Debug\bin
INTDIR=.\..\..\..\..\o\qnmRegTool\DebugforNms98
# Begin Custom Macros
OutDir=.\..\..\..\..\Debug\bin
# End Custom Macros

ALL : "$(OUTDIR)\qyRegToolForNms98.exe" "..\..\..\..\o\qnmRegTool\DebugforNms98\qnmRegTool.pch" "$(OUTDIR)\qnmRegTool.bsc"


CLEAN :
	-@erase "$(INTDIR)\qnmCustom.obj"
	-@erase "$(INTDIR)\qnmCustom.sbr"
	-@erase "$(INTDIR)\qnmCustomRegTool.obj"
	-@erase "$(INTDIR)\qnmCustomRegTool.sbr"
	-@erase "$(INTDIR)\qnmGuiCommProc.obj"
	-@erase "$(INTDIR)\qnmGuiCommProc.sbr"
	-@erase "$(INTDIR)\qnmHotKeys.obj"
	-@erase "$(INTDIR)\qnmHotKeys.sbr"
	-@erase "$(INTDIR)\qnmRegTool.obj"
	-@erase "$(INTDIR)\qnmRegTool.pch"
	-@erase "$(INTDIR)\qnmRegTool.res"
	-@erase "$(INTDIR)\qnmRegTool.sbr"
	-@erase "$(INTDIR)\qwmAllHints.obj"
	-@erase "$(INTDIR)\qwmAllHints.sbr"
	-@erase "$(INTDIR)\qwmRegProc.obj"
	-@erase "$(INTDIR)\qwmRegProc.sbr"
	-@erase "$(INTDIR)\qyCustom.obj"
	-@erase "$(INTDIR)\qyCustom.sbr"
	-@erase "$(INTDIR)\qyRegToolProc.obj"
	-@erase "$(INTDIR)\qyRegToolProc.sbr"
	-@erase "$(INTDIR)\qyTCharCommProc.obj"
	-@erase "$(INTDIR)\qyTCharCommProc.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\qnmRegTool.bsc"
	-@erase "$(OUTDIR)\qyRegToolForNms98.exe"
	-@erase "$(OUTDIR)\qyRegToolForNms98.ilk"
	-@erase "$(OUTDIR)\qyRegToolForNms98.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qnmRegTool.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\qnmRegTool.res" /i "..\..\..\qyCommProc\include" /i "..\..\..\qyCustom\include" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qnmRegTool.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\qnmRegTool.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\qnmCustom.sbr" \
	"$(INTDIR)\qnmCustomRegTool.sbr" \
	"$(INTDIR)\qwmAllHints.sbr" \
	"$(INTDIR)\qyCustom.sbr" \
	"$(INTDIR)\qyRegToolProc.sbr" \
	"$(INTDIR)\qwmRegProc.sbr" \
	"$(INTDIR)\qnmGuiCommProc.sbr" \
	"$(INTDIR)\qnmHotKeys.sbr" \
	"$(INTDIR)\qyTCharCommProc.sbr"

"$(OUTDIR)\qnmRegTool.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=qwmShared.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib qyPublicStaticNoMfc.lib qyEncLibStaticNoMfc.lib mpr.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\qyRegToolForNms98.pdb" /debug /machine:I386 /out:"$(OUTDIR)\qyRegToolForNms98.exe" /pdbtype:sept /libpath:"..\..\..\..\Debug\lib" 
LINK32_OBJS= \
	"$(INTDIR)\qnmRegTool.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\qnmCustom.obj" \
	"$(INTDIR)\qnmCustomRegTool.obj" \
	"$(INTDIR)\qwmAllHints.obj" \
	"$(INTDIR)\qyCustom.obj" \
	"$(INTDIR)\qyRegToolProc.obj" \
	"$(INTDIR)\qwmRegProc.obj" \
	"$(INTDIR)\qnmGuiCommProc.obj" \
	"$(INTDIR)\qnmHotKeys.obj" \
	"$(INTDIR)\qyTCharCommProc.obj" \
	"$(INTDIR)\qnmRegTool.res"

"$(OUTDIR)\qyRegToolForNms98.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("qnmRegTool.dep")
!INCLUDE "qnmRegTool.dep"
!ELSE 
!MESSAGE Warning: cannot find "qnmRegTool.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "qnmRegTool - Win32 Release" || "$(CFG)" == "qnmRegTool - Win32 Debug" || "$(CFG)" == "qnmRegTool - Win32 Release for Nms" || "$(CFG)" == "qnmRegTool - Win32 Debug for Nms" || "$(CFG)" == "qnmRegTool - Win32 Release for 98" || "$(CFG)" == "qnmRegTool - Win32 Debug for 98" || "$(CFG)" == "qnmRegTool - Win32 Release for Nms 98" || "$(CFG)" == "qnmRegTool - Win32 Debug for Nms 98"
SOURCE=.\qnmRegTool.cpp

!IF  "$(CFG)" == "qnmRegTool - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmRegTool.obj"	"$(INTDIR)\qnmRegTool.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmRegTool.obj"	"$(INTDIR)\qnmRegTool.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for Nms"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmRegTool.obj"	"$(INTDIR)\qnmRegTool.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for Nms"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmRegTool.obj"	"$(INTDIR)\qnmRegTool.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for 98"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmRegTool.obj"	"$(INTDIR)\qnmRegTool.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for 98"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmRegTool.obj"	"$(INTDIR)\qnmRegTool.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for Nms 98"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmRegTool.obj"	"$(INTDIR)\qnmRegTool.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for Nms 98"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmRegTool.obj"	"$(INTDIR)\qnmRegTool.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\qnmRegTool.rc

"$(INTDIR)\qnmRegTool.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "qnmRegTool - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qnmRegTool.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\qnmRegTool.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qnmRegTool.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\qnmRegTool.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for Nms"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qnmRegTool.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\qnmRegTool.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for Nms"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qnmRegTool.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\qnmRegTool.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for 98"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qnmRegTool.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\qnmRegTool.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for 98"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qnmRegTool.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\qnmRegTool.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for Nms 98"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qnmRegTool.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\qnmRegTool.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for Nms 98"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qnmRegTool.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\qnmRegTool.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\qyCustom\qnmCustom.cpp

!IF  "$(CFG)" == "qnmRegTool - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCustom.obj"	"$(INTDIR)\qnmCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCustom.obj"	"$(INTDIR)\qnmCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for Nms"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCustom.obj"	"$(INTDIR)\qnmCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for Nms"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCustom.obj"	"$(INTDIR)\qnmCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for 98"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCustom.obj"	"$(INTDIR)\qnmCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for 98"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCustom.obj"	"$(INTDIR)\qnmCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for Nms 98"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCustom.obj"	"$(INTDIR)\qnmCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for Nms 98"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCustom.obj"	"$(INTDIR)\qnmCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\qyCustom\qnmCustomRegTool.cpp

!IF  "$(CFG)" == "qnmRegTool - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCustomRegTool.obj"	"$(INTDIR)\qnmCustomRegTool.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCustomRegTool.obj"	"$(INTDIR)\qnmCustomRegTool.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for Nms"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCustomRegTool.obj"	"$(INTDIR)\qnmCustomRegTool.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for Nms"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCustomRegTool.obj"	"$(INTDIR)\qnmCustomRegTool.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for 98"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCustomRegTool.obj"	"$(INTDIR)\qnmCustomRegTool.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for 98"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCustomRegTool.obj"	"$(INTDIR)\qnmCustomRegTool.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for Nms 98"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCustomRegTool.obj"	"$(INTDIR)\qnmCustomRegTool.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for Nms 98"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCustomRegTool.obj"	"$(INTDIR)\qnmCustomRegTool.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\qyCustom\qwmAllHints.cpp

!IF  "$(CFG)" == "qnmRegTool - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qwmAllHints.obj"	"$(INTDIR)\qwmAllHints.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qwmAllHints.obj"	"$(INTDIR)\qwmAllHints.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for Nms"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qwmAllHints.obj"	"$(INTDIR)\qwmAllHints.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for Nms"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qwmAllHints.obj"	"$(INTDIR)\qwmAllHints.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for 98"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qwmAllHints.obj"	"$(INTDIR)\qwmAllHints.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for 98"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qwmAllHints.obj"	"$(INTDIR)\qwmAllHints.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for Nms 98"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qwmAllHints.obj"	"$(INTDIR)\qwmAllHints.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for Nms 98"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qwmAllHints.obj"	"$(INTDIR)\qwmAllHints.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\qyCustom\qyCustom.cpp

!IF  "$(CFG)" == "qnmRegTool - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyCustom.obj"	"$(INTDIR)\qyCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyCustom.obj"	"$(INTDIR)\qyCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for Nms"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyCustom.obj"	"$(INTDIR)\qyCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for Nms"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyCustom.obj"	"$(INTDIR)\qyCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for 98"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyCustom.obj"	"$(INTDIR)\qyCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for 98"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyCustom.obj"	"$(INTDIR)\qyCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for Nms 98"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyCustom.obj"	"$(INTDIR)\qyCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for Nms 98"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyCustom.obj"	"$(INTDIR)\qyCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\qrtPublic\qyRegToolProc.cpp

!IF  "$(CFG)" == "qnmRegTool - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyRegToolProc.obj"	"$(INTDIR)\qyRegToolProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyRegToolProc.obj"	"$(INTDIR)\qyRegToolProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for Nms"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyRegToolProc.obj"	"$(INTDIR)\qyRegToolProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for Nms"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyRegToolProc.obj"	"$(INTDIR)\qyRegToolProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for 98"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyRegToolProc.obj"	"$(INTDIR)\qyRegToolProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for 98"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyRegToolProc.obj"	"$(INTDIR)\qyRegToolProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for Nms 98"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyRegToolProc.obj"	"$(INTDIR)\qyRegToolProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for Nms 98"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyRegToolProc.obj"	"$(INTDIR)\qyRegToolProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qwmGuiPublic\qwmRegProc.cpp

!IF  "$(CFG)" == "qnmRegTool - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qwmRegProc.obj"	"$(INTDIR)\qwmRegProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qwmRegProc.obj"	"$(INTDIR)\qwmRegProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for Nms"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qwmRegProc.obj"	"$(INTDIR)\qwmRegProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for Nms"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qwmRegProc.obj"	"$(INTDIR)\qwmRegProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for 98"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qwmRegProc.obj"	"$(INTDIR)\qwmRegProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for 98"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qwmRegProc.obj"	"$(INTDIR)\qwmRegProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for Nms 98"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qwmRegProc.obj"	"$(INTDIR)\qwmRegProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for Nms 98"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qwmRegProc.obj"	"$(INTDIR)\qwmRegProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\qyCommProc\qnmGuiCommProc.cpp

!IF  "$(CFG)" == "qnmRegTool - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmGuiCommProc.obj"	"$(INTDIR)\qnmGuiCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmGuiCommProc.obj"	"$(INTDIR)\qnmGuiCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for Nms"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmGuiCommProc.obj"	"$(INTDIR)\qnmGuiCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for Nms"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmGuiCommProc.obj"	"$(INTDIR)\qnmGuiCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for 98"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmGuiCommProc.obj"	"$(INTDIR)\qnmGuiCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for 98"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmGuiCommProc.obj"	"$(INTDIR)\qnmGuiCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for Nms 98"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmGuiCommProc.obj"	"$(INTDIR)\qnmGuiCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for Nms 98"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmGuiCommProc.obj"	"$(INTDIR)\qnmGuiCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\qyCommProc\qnmHotKeys.cpp

!IF  "$(CFG)" == "qnmRegTool - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmHotKeys.obj"	"$(INTDIR)\qnmHotKeys.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmHotKeys.obj"	"$(INTDIR)\qnmHotKeys.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for Nms"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmHotKeys.obj"	"$(INTDIR)\qnmHotKeys.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for Nms"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmHotKeys.obj"	"$(INTDIR)\qnmHotKeys.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for 98"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmHotKeys.obj"	"$(INTDIR)\qnmHotKeys.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for 98"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmHotKeys.obj"	"$(INTDIR)\qnmHotKeys.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for Nms 98"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmHotKeys.obj"	"$(INTDIR)\qnmHotKeys.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for Nms 98"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmHotKeys.obj"	"$(INTDIR)\qnmHotKeys.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\qyCommProc\qyTCharCommProc.cpp

!IF  "$(CFG)" == "qnmRegTool - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyTCharCommProc.obj"	"$(INTDIR)\qyTCharCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyTCharCommProc.obj"	"$(INTDIR)\qyTCharCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for Nms"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyTCharCommProc.obj"	"$(INTDIR)\qyTCharCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for Nms"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyTCharCommProc.obj"	"$(INTDIR)\qyTCharCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for 98"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyTCharCommProc.obj"	"$(INTDIR)\qyTCharCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for 98"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyTCharCommProc.obj"	"$(INTDIR)\qyTCharCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for Nms 98"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyTCharCommProc.obj"	"$(INTDIR)\qyTCharCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for Nms 98"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_nms /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyTCharCommProc.obj"	"$(INTDIR)\qyTCharCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

