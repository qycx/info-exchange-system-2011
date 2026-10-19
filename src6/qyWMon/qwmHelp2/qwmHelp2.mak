# Microsoft Developer Studio Generated NMAKE File, Based on qwmHelp2.dsp
!IF "$(CFG)" == ""
CFG=qwmHelp2 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to qwmHelp2 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "qwmHelp2 - Win32 Release" && "$(CFG)" != "qwmHelp2 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "qwmHelp2.mak" CFG="qwmHelp2 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "qwmHelp2 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "qwmHelp2 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "qwmHelp2 - Win32 Release"

OUTDIR=.\..\..\..\Release\bin
INTDIR=.\..\..\..\o\qwmHelp2\Release
# Begin Custom Macros
OutDir=.\..\..\..\Release\bin
# End Custom Macros

ALL : "$(OUTDIR)\qwmHelp2.dll"


CLEAN :
	-@erase "$(INTDIR)\qwmHelp2.obj"
	-@erase "$(INTDIR)\qwmHelp2.pch"
	-@erase "$(INTDIR)\qwmHideProcessCommProc.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\qwmHelp2.dll"
	-@erase "$(OUTDIR)\qwmHelp2.exp"
	-@erase "$(OUTDIR)\qwmHelp2.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "." /I "..\include" /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QWMHELP2_EXPORTS" /Fp"$(INTDIR)\qwmHelp2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qwmHelp2.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib qyPublicStaticNoMfc.lib qyEncLibStaticNoMfc.lib wsock32.lib /nologo /dll /incremental:no /pdb:"$(OUTDIR)\qwmHelp2.pdb" /machine:I386 /out:"$(OUTDIR)\qwmHelp2.dll" /implib:"$(OUTDIR)\qwmHelp2.lib" /libpath:"..\..\..\Release\lib" 
LINK32_OBJS= \
	"$(INTDIR)\qwmHelp2.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\qwmHideProcessCommProc.obj"

"$(OUTDIR)\qwmHelp2.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "qwmHelp2 - Win32 Debug"

OUTDIR=.\..\..\..\Debug\bin
INTDIR=.\..\..\..\o\qwmHelp2\Debug
# Begin Custom Macros
OutDir=.\..\..\..\Debug\bin
# End Custom Macros

ALL : "$(OUTDIR)\qwmHelp2.dll" "$(OUTDIR)\qwmHelp2.bsc"


CLEAN :
	-@erase "$(INTDIR)\qwmHelp2.obj"
	-@erase "$(INTDIR)\qwmHelp2.pch"
	-@erase "$(INTDIR)\qwmHelp2.sbr"
	-@erase "$(INTDIR)\qwmHideProcessCommProc.obj"
	-@erase "$(INTDIR)\qwmHideProcessCommProc.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\qwmHelp2.bsc"
	-@erase "$(OUTDIR)\qwmHelp2.dll"
	-@erase "$(OUTDIR)\qwmHelp2.exp"
	-@erase "$(OUTDIR)\qwmHelp2.ilk"
	-@erase "$(OUTDIR)\qwmHelp2.lib"
	-@erase "$(OUTDIR)\qwmHelp2.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "." /I "..\include" /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QWMHELP2_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qwmHelp2.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qwmHelp2.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\qwmHelp2.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\qwmHideProcessCommProc.sbr"

"$(OUTDIR)\qwmHelp2.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib qyPublicStaticNoMfc.lib qyEncLibStaticNoMfc.lib wsock32.lib /nologo /dll /incremental:yes /pdb:"$(OUTDIR)\qwmHelp2.pdb" /debug /machine:I386 /out:"$(OUTDIR)\qwmHelp2.dll" /implib:"$(OUTDIR)\qwmHelp2.lib" /pdbtype:sept /libpath:"..\..\..\Debug\lib" 
LINK32_OBJS= \
	"$(INTDIR)\qwmHelp2.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\qwmHideProcessCommProc.obj"

"$(OUTDIR)\qwmHelp2.dll" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("qwmHelp2.dep")
!INCLUDE "qwmHelp2.dep"
!ELSE 
!MESSAGE Warning: cannot find "qwmHelp2.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "qwmHelp2 - Win32 Release" || "$(CFG)" == "qwmHelp2 - Win32 Debug"
SOURCE=.\qwmHelp2.cpp

!IF  "$(CFG)" == "qwmHelp2 - Win32 Release"


"$(INTDIR)\qwmHelp2.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qwmHelp2.pch"


!ELSEIF  "$(CFG)" == "qwmHelp2 - Win32 Debug"


"$(INTDIR)\qwmHelp2.obj"	"$(INTDIR)\qwmHelp2.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qwmHelp2.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "qwmHelp2 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "." /I "..\include" /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QWMHELP2_EXPORTS" /Fp"$(INTDIR)\qwmHelp2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\qwmHelp2.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qwmHelp2 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "." /I "..\include" /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QWMHELP2_EXPORTS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qwmHelp2.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\qwmHelp2.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qwmHideProcessCommProc.cpp

!IF  "$(CFG)" == "qwmHelp2 - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "." /I "..\include" /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QWMHELP2_EXPORTS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qwmHideProcessCommProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qwmHelp2 - Win32 Debug"

CPP_SWITCHES=/nologo /MTd /W3 /Gm /GX /ZI /Od /I "." /I "..\include" /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /I "..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "QWMHELP2_EXPORTS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qwmHideProcessCommProc.obj"	"$(INTDIR)\qwmHideProcessCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

