# Microsoft Developer Studio Generated NMAKE File, Based on qwmHelp.dsp
!IF "$(CFG)" == ""
CFG=qwmHelp - Win32 Debug
!MESSAGE No configuration specified. Defaulting to qwmHelp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "qwmHelp - Win32 Release" && "$(CFG)" != "qwmHelp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "qwmHelp.mak" CFG="qwmHelp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "qwmHelp - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "qwmHelp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "qwmHelp - Win32 Release"

OUTDIR=.\..\..\..\Release\bin
INTDIR=.\..\..\..\o\qwmHelp\Release
# Begin Custom Macros
OutDir=.\..\..\..\Release\bin
# End Custom Macros

ALL : "$(OUTDIR)\qwmHelp.dll"


CLEAN :
	-@erase "$(INTDIR)\HookApi.obj"
	-@erase "$(INTDIR)\HookClass.obj"
	-@erase "$(INTDIR)\qwmHideProcessCommProc.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\qwmHelp.dll"
	-@erase "$(OUTDIR)\qwmHelp.exp"
	-@erase "$(OUTDIR)\qwmHelp.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QWMHELP_EXPORTS" /Fp"$(INTDIR)\qwmHelp.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qwmHelp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Imagehlp.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\qwmHelp.pdb" /machine:I386 /out:"$(OUTDIR)\qwmHelp.dll" /implib:"$(OUTDIR)\qwmHelp.lib" 
LINK32_OBJS= \
	"$(INTDIR)\HookApi.obj" \
	"$(INTDIR)\HookClass.obj" \
	"$(INTDIR)\qwmHideProcessCommProc.obj"

"$(OUTDIR)\qwmHelp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "qwmHelp - Win32 Debug"

OUTDIR=.\..\..\..\Debug\bin
INTDIR=.\..\..\..\o\qwmHelp\Debug
# Begin Custom Macros
OutDir=.\..\..\..\Debug\bin
# End Custom Macros

ALL : "$(OUTDIR)\qwmHelp.dll" "$(OUTDIR)\qwmHelp.bsc"


CLEAN :
	-@erase "$(INTDIR)\HookApi.obj"
	-@erase "$(INTDIR)\HookApi.sbr"
	-@erase "$(INTDIR)\HookClass.obj"
	-@erase "$(INTDIR)\HookClass.sbr"
	-@erase "$(INTDIR)\qwmHideProcessCommProc.obj"
	-@erase "$(INTDIR)\qwmHideProcessCommProc.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\qwmHelp.bsc"
	-@erase "$(OUTDIR)\qwmHelp.dll"
	-@erase "$(OUTDIR)\qwmHelp.exp"
	-@erase "$(OUTDIR)\qwmHelp.ilk"
	-@erase "$(OUTDIR)\qwmHelp.lib"
	-@erase "$(OUTDIR)\qwmHelp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QWMHELP_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qwmHelp.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qwmHelp.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\HookApi.sbr" \
	"$(INTDIR)\HookClass.sbr" \
	"$(INTDIR)\qwmHideProcessCommProc.sbr"

"$(OUTDIR)\qwmHelp.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib Imagehlp.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\qwmHelp.pdb" /debug /machine:I386 /out:"$(OUTDIR)\qwmHelp.dll" /implib:"$(OUTDIR)\qwmHelp.lib" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\HookApi.obj" \
	"$(INTDIR)\HookClass.obj" \
	"$(INTDIR)\qwmHideProcessCommProc.obj"

"$(OUTDIR)\qwmHelp.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("qwmHelp.dep")
!INCLUDE "qwmHelp.dep"
!ELSE 
!MESSAGE Warning: cannot find "qwmHelp.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "qwmHelp - Win32 Release" || "$(CFG)" == "qwmHelp - Win32 Debug"
SOURCE=.\HookApi.cpp

!IF  "$(CFG)" == "qwmHelp - Win32 Release"


"$(INTDIR)\HookApi.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "qwmHelp - Win32 Debug"


"$(INTDIR)\HookApi.obj"	"$(INTDIR)\HookApi.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\HookClass.cpp

!IF  "$(CFG)" == "qwmHelp - Win32 Release"


"$(INTDIR)\HookClass.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "qwmHelp - Win32 Debug"


"$(INTDIR)\HookClass.obj"	"$(INTDIR)\HookClass.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=..\..\qyCommProc\qwmHideProcessCommProc.cpp

!IF  "$(CFG)" == "qwmHelp - Win32 Release"


"$(INTDIR)\qwmHideProcessCommProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qwmHelp - Win32 Debug"


"$(INTDIR)\qwmHideProcessCommProc.obj"	"$(INTDIR)\qwmHideProcessCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

