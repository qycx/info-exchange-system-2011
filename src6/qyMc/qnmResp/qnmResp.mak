# Microsoft Developer Studio Generated NMAKE File, Based on qnmResp.dsp
!IF "$(CFG)" == ""
CFG=qnmResp - Win32 Debug
!MESSAGE No configuration specified. Defaulting to qnmResp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "qnmResp - Win32 Release" && "$(CFG)" != "qnmResp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "qnmResp.mak" CFG="qnmResp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "qnmResp - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "qnmResp - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "qnmResp - Win32 Release"

OUTDIR=.\..\..\..\Release\bin
INTDIR=.\..\..\..\o\qnmResp\Release
# Begin Custom Macros
OutDir=.\..\..\..\Release\bin
# End Custom Macros

ALL : "$(OUTDIR)\qnmResp.exe" "$(OUTDIR)\qnmResp.bsc"


CLEAN :
	-@erase "$(INTDIR)\qmCommonDbFunc.obj"
	-@erase "$(INTDIR)\qmCommonDbFunc.sbr"
	-@erase "$(INTDIR)\qmCommonFunc.obj"
	-@erase "$(INTDIR)\qmCommonFunc.sbr"
	-@erase "$(INTDIR)\qnmCommProc.obj"
	-@erase "$(INTDIR)\qnmCommProc.sbr"
	-@erase "$(INTDIR)\qnmCommProc1.obj"
	-@erase "$(INTDIR)\qnmCommProc1.sbr"
	-@erase "$(INTDIR)\qnmCustom.obj"
	-@erase "$(INTDIR)\qnmCustom.sbr"
	-@erase "$(INTDIR)\qnmCustomComm.obj"
	-@erase "$(INTDIR)\qnmCustomComm.sbr"
	-@erase "$(INTDIR)\qnmResp.obj"
	-@erase "$(INTDIR)\qnmResp.pch"
	-@erase "$(INTDIR)\qnmResp.res"
	-@erase "$(INTDIR)\qnmResp.sbr"
	-@erase "$(INTDIR)\QnmRespDaemon.obj"
	-@erase "$(INTDIR)\QnmRespDaemon.sbr"
	-@erase "$(INTDIR)\qnmRespProc.obj"
	-@erase "$(INTDIR)\qnmRespProc.sbr"
	-@erase "$(INTDIR)\qnmRespProc_netMc2.obj"
	-@erase "$(INTDIR)\qnmRespProc_netMc2.sbr"
	-@erase "$(INTDIR)\qnmsCommProc.obj"
	-@erase "$(INTDIR)\qnmsCommProc.sbr"
	-@erase "$(INTDIR)\qnmWarnCommProc.obj"
	-@erase "$(INTDIR)\qnmWarnCommProc.sbr"
	-@erase "$(INTDIR)\qyArpProc.obj"
	-@erase "$(INTDIR)\qyArpProc.sbr"
	-@erase "$(INTDIR)\qyCommProc.obj"
	-@erase "$(INTDIR)\qyCommProc.sbr"
	-@erase "$(INTDIR)\qyCustom.obj"
	-@erase "$(INTDIR)\qyCustom.sbr"
	-@erase "$(INTDIR)\qyPing.obj"
	-@erase "$(INTDIR)\qyPing.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\winarp-sk.obj"
	-@erase "$(INTDIR)\winarp-sk.sbr"
	-@erase "$(INTDIR)\winpcap_common.obj"
	-@erase "$(INTDIR)\winpcap_common.sbr"
	-@erase "$(OUTDIR)\qnmResp.bsc"
	-@erase "$(OUTDIR)\qnmResp.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qnmResp.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\qnmResp.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qnmResp.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\qmCommonDbFunc.sbr" \
	"$(INTDIR)\qmCommonFunc.sbr" \
	"$(INTDIR)\qnmResp.sbr" \
	"$(INTDIR)\QnmRespDaemon.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\qnmRespProc.sbr" \
	"$(INTDIR)\qnmRespProc_netMc2.sbr" \
	"$(INTDIR)\qyPing.sbr" \
	"$(INTDIR)\winpcap_common.sbr" \
	"$(INTDIR)\qnmCommProc.sbr" \
	"$(INTDIR)\qnmCommProc1.sbr" \
	"$(INTDIR)\qnmsCommProc.sbr" \
	"$(INTDIR)\qnmWarnCommProc.sbr" \
	"$(INTDIR)\qyArpProc.sbr" \
	"$(INTDIR)\qyCommProc.sbr" \
	"$(INTDIR)\winarp-sk.sbr" \
	"$(INTDIR)\qnmCustom.sbr" \
	"$(INTDIR)\qnmCustomComm.sbr" \
	"$(INTDIR)\qyCustom.sbr"

"$(OUTDIR)\qnmResp.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=qyPublic.lib qyEncLib.lib packet.lib qyLicense.lib Spromeps.lib libDes.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\qnmResp.pdb" /machine:I386 /out:"$(OUTDIR)\qnmResp.exe" /libpath:"..\..\..\Release\lib" /libpath:"..\..\..\others\winpcap\common" 
LINK32_OBJS= \
	"$(INTDIR)\qmCommonDbFunc.obj" \
	"$(INTDIR)\qmCommonFunc.obj" \
	"$(INTDIR)\qnmResp.obj" \
	"$(INTDIR)\QnmRespDaemon.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\qnmRespProc.obj" \
	"$(INTDIR)\qnmRespProc_netMc2.obj" \
	"$(INTDIR)\qyPing.obj" \
	"$(INTDIR)\winpcap_common.obj" \
	"$(INTDIR)\qnmCommProc.obj" \
	"$(INTDIR)\qnmCommProc1.obj" \
	"$(INTDIR)\qnmsCommProc.obj" \
	"$(INTDIR)\qnmWarnCommProc.obj" \
	"$(INTDIR)\qyArpProc.obj" \
	"$(INTDIR)\qyCommProc.obj" \
	"$(INTDIR)\winarp-sk.obj" \
	"$(INTDIR)\qnmCustom.obj" \
	"$(INTDIR)\qnmCustomComm.obj" \
	"$(INTDIR)\qyCustom.obj" \
	"$(INTDIR)\qnmResp.res"

"$(OUTDIR)\qnmResp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "qnmResp - Win32 Debug"

OUTDIR=.\..\..\..\Debug\bin
INTDIR=.\..\..\..\o\qnmResp\Debug
# Begin Custom Macros
OutDir=.\..\..\..\Debug\bin
# End Custom Macros

ALL : "$(OUTDIR)\qnmResp.exe"


CLEAN :
	-@erase "$(INTDIR)\qmCommonDbFunc.obj"
	-@erase "$(INTDIR)\qmCommonFunc.obj"
	-@erase "$(INTDIR)\qnmCommProc.obj"
	-@erase "$(INTDIR)\qnmCommProc1.obj"
	-@erase "$(INTDIR)\qnmCustom.obj"
	-@erase "$(INTDIR)\qnmCustomComm.obj"
	-@erase "$(INTDIR)\qnmResp.obj"
	-@erase "$(INTDIR)\qnmResp.pch"
	-@erase "$(INTDIR)\qnmResp.res"
	-@erase "$(INTDIR)\QnmRespDaemon.obj"
	-@erase "$(INTDIR)\qnmRespProc.obj"
	-@erase "$(INTDIR)\qnmRespProc_netMc2.obj"
	-@erase "$(INTDIR)\qnmsCommProc.obj"
	-@erase "$(INTDIR)\qnmWarnCommProc.obj"
	-@erase "$(INTDIR)\qyArpProc.obj"
	-@erase "$(INTDIR)\qyCommProc.obj"
	-@erase "$(INTDIR)\qyCustom.obj"
	-@erase "$(INTDIR)\qyPing.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\winarp-sk.obj"
	-@erase "$(INTDIR)\winpcap_common.obj"
	-@erase "$(OUTDIR)\qnmResp.exe"
	-@erase "$(OUTDIR)\qnmResp.ilk"
	-@erase "$(OUTDIR)\qnmResp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\qnmResp.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\qnmResp.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qnmResp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=qyPublic.lib qyEncLib.lib packetStatic.lib qyLicense.lib Spromeps.lib libDes.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\qnmResp.pdb" /debug /machine:I386 /out:"$(OUTDIR)\qnmResp.exe" /pdbtype:sept /libpath:"..\..\..\Debug\lib" /libpath:"..\..\..\others\winpcap\common" 
LINK32_OBJS= \
	"$(INTDIR)\qmCommonDbFunc.obj" \
	"$(INTDIR)\qmCommonFunc.obj" \
	"$(INTDIR)\qnmResp.obj" \
	"$(INTDIR)\QnmRespDaemon.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\qnmRespProc.obj" \
	"$(INTDIR)\qnmRespProc_netMc2.obj" \
	"$(INTDIR)\qyPing.obj" \
	"$(INTDIR)\winpcap_common.obj" \
	"$(INTDIR)\qnmCommProc.obj" \
	"$(INTDIR)\qnmCommProc1.obj" \
	"$(INTDIR)\qnmsCommProc.obj" \
	"$(INTDIR)\qnmWarnCommProc.obj" \
	"$(INTDIR)\qyArpProc.obj" \
	"$(INTDIR)\qyCommProc.obj" \
	"$(INTDIR)\winarp-sk.obj" \
	"$(INTDIR)\qnmCustom.obj" \
	"$(INTDIR)\qnmCustomComm.obj" \
	"$(INTDIR)\qyCustom.obj" \
	"$(INTDIR)\qnmResp.res"

"$(OUTDIR)\qnmResp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("qnmResp.dep")
!INCLUDE "qnmResp.dep"
!ELSE 
!MESSAGE Warning: cannot find "qnmResp.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "qnmResp - Win32 Release" || "$(CFG)" == "qnmResp - Win32 Debug"
SOURCE=..\qymcPublic\qmCommonDbFunc.cpp

!IF  "$(CFG)" == "qnmResp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qmCommonDbFunc.obj"	"$(INTDIR)\qmCommonDbFunc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmResp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qmCommonDbFunc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\qymcPublic\qmCommonFunc.cpp

!IF  "$(CFG)" == "qnmResp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qnmResp.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qmCommonFunc.obj"	"$(INTDIR)\qmCommonFunc.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qnmResp.pch"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmResp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qmCommonFunc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\qnmResp.cpp

!IF  "$(CFG)" == "qnmResp - Win32 Release"


"$(INTDIR)\qnmResp.obj"	"$(INTDIR)\qnmResp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qnmResp.pch"


!ELSEIF  "$(CFG)" == "qnmResp - Win32 Debug"


"$(INTDIR)\qnmResp.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qnmResp.pch"


!ENDIF 

SOURCE=.\qnmResp.rc

"$(INTDIR)\qnmResp.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\QnmRespDaemon.cpp

!IF  "$(CFG)" == "qnmResp - Win32 Release"


"$(INTDIR)\QnmRespDaemon.obj"	"$(INTDIR)\QnmRespDaemon.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qnmResp.pch"


!ELSEIF  "$(CFG)" == "qnmResp - Win32 Debug"


"$(INTDIR)\QnmRespDaemon.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qnmResp.pch"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "qnmResp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\qnmResp.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\qnmResp.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmResp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\qnmResp.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\qnmResp.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\qnmRespPublic\qnmRespProc.cpp

!IF  "$(CFG)" == "qnmResp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmRespProc.obj"	"$(INTDIR)\qnmRespProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmResp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmRespProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\qnmRespPublic\qnmRespProc_netMc2.cpp

!IF  "$(CFG)" == "qnmResp - Win32 Release"


"$(INTDIR)\qnmRespProc_netMc2.obj"	"$(INTDIR)\qnmRespProc_netMc2.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qnmResp.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qnmResp - Win32 Debug"


"$(INTDIR)\qnmRespProc_netMc2.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\qnmResp.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\qnmRespPublic\qyPing.c

!IF  "$(CFG)" == "qnmResp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyPing.obj"	"$(INTDIR)\qyPing.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmResp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyPing.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\qnmRespPublic\winpcap_common.cpp

!IF  "$(CFG)" == "qnmResp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\winpcap_common.obj"	"$(INTDIR)\winpcap_common.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmResp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\winpcap_common.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qnmCommProc.cpp

!IF  "$(CFG)" == "qnmResp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCommProc.obj"	"$(INTDIR)\qnmCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmResp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCommProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qnmCommProc1.cpp

!IF  "$(CFG)" == "qnmResp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCommProc1.obj"	"$(INTDIR)\qnmCommProc1.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmResp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCommProc1.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qnmsCommProc.cpp

!IF  "$(CFG)" == "qnmResp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmsCommProc.obj"	"$(INTDIR)\qnmsCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmResp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmsCommProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qnmWarnCommProc.cpp

!IF  "$(CFG)" == "qnmResp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmWarnCommProc.obj"	"$(INTDIR)\qnmWarnCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmResp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmWarnCommProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qyArpProc.cpp

!IF  "$(CFG)" == "qnmResp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyArpProc.obj"	"$(INTDIR)\qyArpProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmResp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyArpProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCommProc\qyCommProc.cpp

!IF  "$(CFG)" == "qnmResp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyCommProc.obj"	"$(INTDIR)\qyCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmResp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyCommProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE="..\..\qyCommProc\winarp-sk.cpp"

!IF  "$(CFG)" == "qnmResp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\winarp-sk.obj"	"$(INTDIR)\winarp-sk.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmResp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\winarp-sk.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCustom\qnmCustom.cpp

!IF  "$(CFG)" == "qnmResp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCustom.obj"	"$(INTDIR)\qnmCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmResp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCustom.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCustom\qnmCustomComm.cpp

!IF  "$(CFG)" == "qnmResp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCustomComm.obj"	"$(INTDIR)\qnmCustomComm.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmResp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCustomComm.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\qyCustom\qyCustom.cpp

!IF  "$(CFG)" == "qnmResp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyCustom.obj"	"$(INTDIR)\qyCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qnmResp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\asrInclude" /I "..\..\qyInclude" /I "..\..\qyPublic\include" /I "..\include" /I "include" /I "." /I "..\..\qyCommProc\include" /I "..\..\qyEncLib\include" /I "..\..\winpcap\common" /I "..\..\qyCustom\include" /I "..\..\qyPublic2\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyCustom.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

