# Microsoft Developer Studio Generated NMAKE File, Based on awmChkSecurity.dsp
!IF "$(CFG)" == ""
CFG=awmChkSecurity - Win32 Debug
!MESSAGE No configuration specified. Defaulting to awmChkSecurity - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "awmChkSecurity - Win32 Release" && "$(CFG)" != "awmChkSecurity - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "awmChkSecurity.mak" CFG="awmChkSecurity - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "awmChkSecurity - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "awmChkSecurity - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "awmChkSecurity - Win32 Release"

OUTDIR=.\..\..\..\Release\bin
INTDIR=.\..\..\..\o\awmChk\Release
# Begin Custom Macros
OutDir=.\..\..\..\Release\bin
# End Custom Macros

ALL : "$(OUTDIR)\qnmScheduler.exe" "..\..\..\o\awmChk\Release\awmChkSecurity.pch" "$(OUTDIR)\awmChkSecurity.bsc"


CLEAN :
	-@erase "$(INTDIR)\awmChk.obj"
	-@erase "$(INTDIR)\awmChk.sbr"
	-@erase "$(INTDIR)\awmChkAddAce.obj"
	-@erase "$(INTDIR)\awmChkAddAce.sbr"
	-@erase "$(INTDIR)\awmChkFunc.obj"
	-@erase "$(INTDIR)\awmChkFunc.sbr"
	-@erase "$(INTDIR)\awmChkProc.obj"
	-@erase "$(INTDIR)\awmChkProc.sbr"
	-@erase "$(INTDIR)\awmChkSecurity.obj"
	-@erase "$(INTDIR)\awmChkSecurity.pch"
	-@erase "$(INTDIR)\awmChkSecurity.res"
	-@erase "$(INTDIR)\awmChkSecurity.sbr"
	-@erase "$(INTDIR)\awmChkTemp.obj"
	-@erase "$(INTDIR)\awmChkTemp.sbr"
	-@erase "$(INTDIR)\awmSetScriptPath.obj"
	-@erase "$(INTDIR)\awmSetScriptPath.sbr"
	-@erase "$(INTDIR)\qnmCommProc.obj"
	-@erase "$(INTDIR)\qnmCommProc.sbr"
	-@erase "$(INTDIR)\qnmCustom.obj"
	-@erase "$(INTDIR)\qnmCustom.sbr"
	-@erase "$(INTDIR)\qyCommProc.obj"
	-@erase "$(INTDIR)\qyCommProc.sbr"
	-@erase "$(INTDIR)\qyCustom.obj"
	-@erase "$(INTDIR)\qyCustom.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\awmChkSecurity.bsc"
	-@erase "$(OUTDIR)\qnmScheduler.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\awmChkSecurity.res" /i "..\..\qyCommProc\include" /i "..\..\qyCustom\include" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\awmChkSecurity.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\awmChk.sbr" \
	"$(INTDIR)\awmChkAddAce.sbr" \
	"$(INTDIR)\awmChkFunc.sbr" \
	"$(INTDIR)\awmChkProc.sbr" \
	"$(INTDIR)\awmChkSecurity.sbr" \
	"$(INTDIR)\awmChkTemp.sbr" \
	"$(INTDIR)\awmSetScriptPath.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\qnmCommProc.sbr" \
	"$(INTDIR)\qyCommProc.sbr" \
	"$(INTDIR)\qnmCustom.sbr" \
	"$(INTDIR)\qyCustom.sbr"

"$(OUTDIR)\awmChkSecurity.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=netapi32.lib qyPublic.lib qyEncLib.lib Spromeps.lib qyLicense.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\qnmScheduler.pdb" /machine:I386 /out:"$(OUTDIR)\qnmScheduler.exe" /libpath:"..\..\..\Release\lib" 
LINK32_OBJS= \
	"$(INTDIR)\awmChk.obj" \
	"$(INTDIR)\awmChkAddAce.obj" \
	"$(INTDIR)\awmChkFunc.obj" \
	"$(INTDIR)\awmChkProc.obj" \
	"$(INTDIR)\awmChkSecurity.obj" \
	"$(INTDIR)\awmChkTemp.obj" \
	"$(INTDIR)\awmSetScriptPath.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\qnmCommProc.obj" \
	"$(INTDIR)\qyCommProc.obj" \
	"$(INTDIR)\qnmCustom.obj" \
	"$(INTDIR)\qyCustom.obj" \
	"$(INTDIR)\awmChkSecurity.res"

"$(OUTDIR)\qnmScheduler.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "awmChkSecurity - Win32 Debug"

OUTDIR=.\..\..\..\Debug\bin
INTDIR=.\..\..\..\o\awmChk\Debug
# Begin Custom Macros
OutDir=.\..\..\..\Debug\bin
# End Custom Macros

ALL : "$(OUTDIR)\qnmScheduler.exe" "$(OUTDIR)\awmChkSecurity.bsc"


CLEAN :
	-@erase "$(INTDIR)\awmChk.obj"
	-@erase "$(INTDIR)\awmChk.sbr"
	-@erase "$(INTDIR)\awmChkAddAce.obj"
	-@erase "$(INTDIR)\awmChkAddAce.sbr"
	-@erase "$(INTDIR)\awmChkFunc.obj"
	-@erase "$(INTDIR)\awmChkFunc.sbr"
	-@erase "$(INTDIR)\awmChkProc.obj"
	-@erase "$(INTDIR)\awmChkProc.sbr"
	-@erase "$(INTDIR)\awmChkSecurity.obj"
	-@erase "$(INTDIR)\awmChkSecurity.pch"
	-@erase "$(INTDIR)\awmChkSecurity.res"
	-@erase "$(INTDIR)\awmChkSecurity.sbr"
	-@erase "$(INTDIR)\awmChkTemp.obj"
	-@erase "$(INTDIR)\awmChkTemp.sbr"
	-@erase "$(INTDIR)\awmSetScriptPath.obj"
	-@erase "$(INTDIR)\awmSetScriptPath.sbr"
	-@erase "$(INTDIR)\qnmCommProc.obj"
	-@erase "$(INTDIR)\qnmCommProc.sbr"
	-@erase "$(INTDIR)\qnmCustom.obj"
	-@erase "$(INTDIR)\qnmCustom.sbr"
	-@erase "$(INTDIR)\qyCommProc.obj"
	-@erase "$(INTDIR)\qyCommProc.sbr"
	-@erase "$(INTDIR)\qyCustom.obj"
	-@erase "$(INTDIR)\qyCustom.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\awmChkSecurity.bsc"
	-@erase "$(OUTDIR)\qnmScheduler.exe"
	-@erase "$(OUTDIR)\qnmScheduler.ilk"
	-@erase "$(OUTDIR)\qnmScheduler.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fp"$(INTDIR)\awmChkSecurity.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\awmChkSecurity.res" /i "..\..\qyCommProc\include" /i "..\..\qyCustom\include" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\awmChkSecurity.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\awmChk.sbr" \
	"$(INTDIR)\awmChkAddAce.sbr" \
	"$(INTDIR)\awmChkFunc.sbr" \
	"$(INTDIR)\awmChkProc.sbr" \
	"$(INTDIR)\awmChkSecurity.sbr" \
	"$(INTDIR)\awmChkTemp.sbr" \
	"$(INTDIR)\awmSetScriptPath.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\qnmCommProc.sbr" \
	"$(INTDIR)\qyCommProc.sbr" \
	"$(INTDIR)\qnmCustom.sbr" \
	"$(INTDIR)\qyCustom.sbr"

"$(OUTDIR)\awmChkSecurity.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=netapi32.lib qyPublic.lib qyEncLib.lib Spromeps.lib qyLicense.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\qnmScheduler.pdb" /debug /machine:I386 /out:"$(OUTDIR)\qnmScheduler.exe" /pdbtype:sept /libpath:"..\..\..\Debug\lib" 
LINK32_OBJS= \
	"$(INTDIR)\awmChk.obj" \
	"$(INTDIR)\awmChkAddAce.obj" \
	"$(INTDIR)\awmChkFunc.obj" \
	"$(INTDIR)\awmChkProc.obj" \
	"$(INTDIR)\awmChkSecurity.obj" \
	"$(INTDIR)\awmChkTemp.obj" \
	"$(INTDIR)\awmSetScriptPath.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\qnmCommProc.obj" \
	"$(INTDIR)\qyCommProc.obj" \
	"$(INTDIR)\qnmCustom.obj" \
	"$(INTDIR)\qyCustom.obj" \
	"$(INTDIR)\awmChkSecurity.res"

"$(OUTDIR)\qnmScheduler.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("awmChkSecurity.dep")
!INCLUDE "awmChkSecurity.dep"
!ELSE 
!MESSAGE Warning: cannot find "awmChkSecurity.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "awmChkSecurity - Win32 Release" || "$(CFG)" == "awmChkSecurity - Win32 Debug"
SOURCE=.\awmChk.cpp

"$(INTDIR)\awmChk.obj"	"$(INTDIR)\awmChk.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\awmChkAddAce.cpp

"$(INTDIR)\awmChkAddAce.obj"	"$(INTDIR)\awmChkAddAce.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\awmChkFunc.cpp

"$(INTDIR)\awmChkFunc.obj"	"$(INTDIR)\awmChkFunc.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\awmChkProc.cpp

"$(INTDIR)\awmChkProc.obj"	"$(INTDIR)\awmChkProc.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\awmChkSecurity.cpp

"$(INTDIR)\awmChkSecurity.obj"	"$(INTDIR)\awmChkSecurity.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\awmChkSecurity.rc

"$(INTDIR)\awmChkSecurity.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\awmChkTemp.cpp

"$(INTDIR)\awmChkTemp.obj"	"$(INTDIR)\awmChkTemp.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\awmSetScriptPath.cpp

"$(INTDIR)\awmSetScriptPath.obj"	"$(INTDIR)\awmSetScriptPath.sbr" : $(SOURCE) "$(INTDIR)"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "awmChkSecurity - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\awmChkSecurity.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\awmChkSecurity.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "awmChkSecurity - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fp"$(INTDIR)\awmChkSecurity.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\awmChkSecurity.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qnmCommProc.cpp

!IF  "$(CFG)" == "awmChkSecurity - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCommProc.obj"	"$(INTDIR)\qnmCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "awmChkSecurity - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCommProc.obj"	"$(INTDIR)\qnmCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qyCommProc.cpp

!IF  "$(CFG)" == "awmChkSecurity - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyCommProc.obj"	"$(INTDIR)\qyCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "awmChkSecurity - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyCommProc.obj"	"$(INTDIR)\qyCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCustom\qnmCustom.cpp

!IF  "$(CFG)" == "awmChkSecurity - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCustom.obj"	"$(INTDIR)\qnmCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "awmChkSecurity - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCustom.obj"	"$(INTDIR)\qnmCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCustom\qyCustom.cpp

!IF  "$(CFG)" == "awmChkSecurity - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyCustom.obj"	"$(INTDIR)\qyCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "awmChkSecurity - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\qyCustom\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyCustom.obj"	"$(INTDIR)\qyCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

