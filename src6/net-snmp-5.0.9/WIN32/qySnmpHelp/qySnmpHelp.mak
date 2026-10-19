# Microsoft Developer Studio Generated NMAKE File, Based on qySnmpHelp.dsp
!IF "$(CFG)" == ""
CFG=qySnmpHelp - Win32 Debug
!MESSAGE No configuration specified. Defaulting to qySnmpHelp - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "qySnmpHelp - Win32 Release" && "$(CFG)" != "qySnmpHelp - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "qySnmpHelp.mak" CFG="qySnmpHelp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "qySnmpHelp - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "qySnmpHelp - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"

OUTDIR=.\..\..\..\..\Release\bin
INTDIR=.\..\..\..\..\o\qySnmpHelp\Release
# Begin Custom Macros
OutDir=.\..\..\..\..\Release\bin
# End Custom Macros

ALL : "$(OUTDIR)\qySnmpHelp.exe" "..\..\..\..\o\qySnmpHelp\Release\qySnmpHelp.pch"


CLEAN :
	-@erase "$(INTDIR)\getopt.obj"
	-@erase "$(INTDIR)\list.obj"
	-@erase "$(INTDIR)\myNbtScan.obj"
	-@erase "$(INTDIR)\myNbtScanCommon.obj"
	-@erase "$(INTDIR)\nbtscan.obj"
	-@erase "$(INTDIR)\qmCommonDbFunc.obj"
	-@erase "$(INTDIR)\qmCommonFunc.obj"
	-@erase "$(INTDIR)\qmSnmpProc.obj"
	-@erase "$(INTDIR)\qnmCommProc.obj"
	-@erase "$(INTDIR)\qnmCommProc1.obj"
	-@erase "$(INTDIR)\qnmCustom.obj"
	-@erase "$(INTDIR)\qnmCustomComm.obj"
	-@erase "$(INTDIR)\qnmsCommProc.obj"
	-@erase "$(INTDIR)\qnmWarnCommProc.obj"
	-@erase "$(INTDIR)\qyCommProc.obj"
	-@erase "$(INTDIR)\qyCustom.obj"
	-@erase "$(INTDIR)\qyNbtScanProc.obj"
	-@erase "$(INTDIR)\qySnmpCmdProc.obj"
	-@erase "$(INTDIR)\qySnmpDefs.obj"
	-@erase "$(INTDIR)\qySnmpGet.obj"
	-@erase "$(INTDIR)\qySnmpHelp.obj"
	-@erase "$(INTDIR)\qySnmpHelp.pch"
	-@erase "$(INTDIR)\qySnmpHelp.res"
	-@erase "$(INTDIR)\qySnmpHelpProc.obj"
	-@erase "$(INTDIR)\QySnmpHelpProcDaemon.obj"
	-@erase "$(INTDIR)\qySnmpScript.obj"
	-@erase "$(INTDIR)\qySnmpSet.obj"
	-@erase "$(INTDIR)\qySnmpWalk.obj"
	-@erase "$(INTDIR)\range.obj"
	-@erase "$(INTDIR)\statusq.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\qySnmpHelp.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

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
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\qySnmpHelp.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qySnmpHelp.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=libsnmp.lib ws2_32.lib qyPublic.lib qyEncLib.lib Spromeps.lib qyLicense.lib libDes.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\qySnmpHelp.pdb" /machine:I386 /out:"$(OUTDIR)\qySnmpHelp.exe" /libpath:"..\..\..\..\Release\lib" 
LINK32_OBJS= \
	"$(INTDIR)\qySnmpCmdProc.obj" \
	"$(INTDIR)\qySnmpDefs.obj" \
	"$(INTDIR)\qySnmpGet.obj" \
	"$(INTDIR)\qySnmpHelpProc.obj" \
	"$(INTDIR)\qySnmpScript.obj" \
	"$(INTDIR)\qySnmpSet.obj" \
	"$(INTDIR)\qySnmpWalk.obj" \
	"$(INTDIR)\qySnmpHelp.obj" \
	"$(INTDIR)\QySnmpHelpProcDaemon.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\qmCommonDbFunc.obj" \
	"$(INTDIR)\qmCommonFunc.obj" \
	"$(INTDIR)\qmSnmpProc.obj" \
	"$(INTDIR)\qnmCustom.obj" \
	"$(INTDIR)\qnmCustomComm.obj" \
	"$(INTDIR)\qyCustom.obj" \
	"$(INTDIR)\qnmCommProc.obj" \
	"$(INTDIR)\qnmCommProc1.obj" \
	"$(INTDIR)\qnmsCommProc.obj" \
	"$(INTDIR)\qnmWarnCommProc.obj" \
	"$(INTDIR)\qyCommProc.obj" \
	"$(INTDIR)\getopt.obj" \
	"$(INTDIR)\list.obj" \
	"$(INTDIR)\myNbtScan.obj" \
	"$(INTDIR)\myNbtScanCommon.obj" \
	"$(INTDIR)\nbtscan.obj" \
	"$(INTDIR)\qyNbtScanProc.obj" \
	"$(INTDIR)\range.obj" \
	"$(INTDIR)\statusq.obj" \
	"$(INTDIR)\qySnmpHelp.res"

"$(OUTDIR)\qySnmpHelp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"

OUTDIR=.\..\..\..\..\Debug\bin
INTDIR=.\..\..\..\..\o\qySnmpHelp\Debug
# Begin Custom Macros
OutDir=.\..\..\..\..\Debug\bin
# End Custom Macros

ALL : "$(OUTDIR)\qySnmpHelp.exe" "..\..\..\..\o\qySnmpHelp\Debug\qySnmpHelp.pch" "$(OUTDIR)\qySnmpHelp.bsc"


CLEAN :
	-@erase "$(INTDIR)\getopt.obj"
	-@erase "$(INTDIR)\getopt.sbr"
	-@erase "$(INTDIR)\list.obj"
	-@erase "$(INTDIR)\list.sbr"
	-@erase "$(INTDIR)\myNbtScan.obj"
	-@erase "$(INTDIR)\myNbtScan.sbr"
	-@erase "$(INTDIR)\myNbtScanCommon.obj"
	-@erase "$(INTDIR)\myNbtScanCommon.sbr"
	-@erase "$(INTDIR)\nbtscan.obj"
	-@erase "$(INTDIR)\nbtscan.sbr"
	-@erase "$(INTDIR)\qmCommonDbFunc.obj"
	-@erase "$(INTDIR)\qmCommonDbFunc.sbr"
	-@erase "$(INTDIR)\qmCommonFunc.obj"
	-@erase "$(INTDIR)\qmCommonFunc.sbr"
	-@erase "$(INTDIR)\qmSnmpProc.obj"
	-@erase "$(INTDIR)\qmSnmpProc.sbr"
	-@erase "$(INTDIR)\qnmCommProc.obj"
	-@erase "$(INTDIR)\qnmCommProc.sbr"
	-@erase "$(INTDIR)\qnmCommProc1.obj"
	-@erase "$(INTDIR)\qnmCommProc1.sbr"
	-@erase "$(INTDIR)\qnmCustom.obj"
	-@erase "$(INTDIR)\qnmCustom.sbr"
	-@erase "$(INTDIR)\qnmCustomComm.obj"
	-@erase "$(INTDIR)\qnmCustomComm.sbr"
	-@erase "$(INTDIR)\qnmsCommProc.obj"
	-@erase "$(INTDIR)\qnmsCommProc.sbr"
	-@erase "$(INTDIR)\qnmWarnCommProc.obj"
	-@erase "$(INTDIR)\qnmWarnCommProc.sbr"
	-@erase "$(INTDIR)\qyCommProc.obj"
	-@erase "$(INTDIR)\qyCommProc.sbr"
	-@erase "$(INTDIR)\qyCustom.obj"
	-@erase "$(INTDIR)\qyCustom.sbr"
	-@erase "$(INTDIR)\qyNbtScanProc.obj"
	-@erase "$(INTDIR)\qyNbtScanProc.sbr"
	-@erase "$(INTDIR)\qySnmpCmdProc.obj"
	-@erase "$(INTDIR)\qySnmpCmdProc.sbr"
	-@erase "$(INTDIR)\qySnmpDefs.obj"
	-@erase "$(INTDIR)\qySnmpDefs.sbr"
	-@erase "$(INTDIR)\qySnmpGet.obj"
	-@erase "$(INTDIR)\qySnmpGet.sbr"
	-@erase "$(INTDIR)\qySnmpHelp.obj"
	-@erase "$(INTDIR)\qySnmpHelp.pch"
	-@erase "$(INTDIR)\qySnmpHelp.res"
	-@erase "$(INTDIR)\qySnmpHelp.sbr"
	-@erase "$(INTDIR)\qySnmpHelpProc.obj"
	-@erase "$(INTDIR)\qySnmpHelpProc.sbr"
	-@erase "$(INTDIR)\QySnmpHelpProcDaemon.obj"
	-@erase "$(INTDIR)\QySnmpHelpProcDaemon.sbr"
	-@erase "$(INTDIR)\qySnmpScript.obj"
	-@erase "$(INTDIR)\qySnmpScript.sbr"
	-@erase "$(INTDIR)\qySnmpSet.obj"
	-@erase "$(INTDIR)\qySnmpSet.sbr"
	-@erase "$(INTDIR)\qySnmpWalk.obj"
	-@erase "$(INTDIR)\qySnmpWalk.sbr"
	-@erase "$(INTDIR)\range.obj"
	-@erase "$(INTDIR)\range.sbr"
	-@erase "$(INTDIR)\statusq.obj"
	-@erase "$(INTDIR)\statusq.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\qySnmpHelp.bsc"
	-@erase "$(OUTDIR)\qySnmpHelp.exe"
	-@erase "$(OUTDIR)\qySnmpHelp.ilk"
	-@erase "$(OUTDIR)\qySnmpHelp.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

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
RSC_PROJ=/l 0x804 /fo"$(INTDIR)\qySnmpHelp.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\qySnmpHelp.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\qySnmpCmdProc.sbr" \
	"$(INTDIR)\qySnmpDefs.sbr" \
	"$(INTDIR)\qySnmpGet.sbr" \
	"$(INTDIR)\qySnmpHelpProc.sbr" \
	"$(INTDIR)\qySnmpScript.sbr" \
	"$(INTDIR)\qySnmpSet.sbr" \
	"$(INTDIR)\qySnmpWalk.sbr" \
	"$(INTDIR)\qySnmpHelp.sbr" \
	"$(INTDIR)\QySnmpHelpProcDaemon.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\qmCommonDbFunc.sbr" \
	"$(INTDIR)\qmCommonFunc.sbr" \
	"$(INTDIR)\qmSnmpProc.sbr" \
	"$(INTDIR)\qnmCustom.sbr" \
	"$(INTDIR)\qnmCustomComm.sbr" \
	"$(INTDIR)\qyCustom.sbr" \
	"$(INTDIR)\qnmCommProc.sbr" \
	"$(INTDIR)\qnmCommProc1.sbr" \
	"$(INTDIR)\qnmsCommProc.sbr" \
	"$(INTDIR)\qnmWarnCommProc.sbr" \
	"$(INTDIR)\qyCommProc.sbr" \
	"$(INTDIR)\getopt.sbr" \
	"$(INTDIR)\list.sbr" \
	"$(INTDIR)\myNbtScan.sbr" \
	"$(INTDIR)\myNbtScanCommon.sbr" \
	"$(INTDIR)\nbtscan.sbr" \
	"$(INTDIR)\qyNbtScanProc.sbr" \
	"$(INTDIR)\range.sbr" \
	"$(INTDIR)\statusq.sbr"

"$(OUTDIR)\qySnmpHelp.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=libsnmp.lib ws2_32.lib qyPublic.lib qyEncLib.lib Spromeps.lib qyLicense.lib libDes.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\qySnmpHelp.pdb" /debug /machine:I386 /out:"$(OUTDIR)\qySnmpHelp.exe" /pdbtype:sept /libpath:"..\..\..\..\Debug\lib" 
LINK32_OBJS= \
	"$(INTDIR)\qySnmpCmdProc.obj" \
	"$(INTDIR)\qySnmpDefs.obj" \
	"$(INTDIR)\qySnmpGet.obj" \
	"$(INTDIR)\qySnmpHelpProc.obj" \
	"$(INTDIR)\qySnmpScript.obj" \
	"$(INTDIR)\qySnmpSet.obj" \
	"$(INTDIR)\qySnmpWalk.obj" \
	"$(INTDIR)\qySnmpHelp.obj" \
	"$(INTDIR)\QySnmpHelpProcDaemon.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\qmCommonDbFunc.obj" \
	"$(INTDIR)\qmCommonFunc.obj" \
	"$(INTDIR)\qmSnmpProc.obj" \
	"$(INTDIR)\qnmCustom.obj" \
	"$(INTDIR)\qnmCustomComm.obj" \
	"$(INTDIR)\qyCustom.obj" \
	"$(INTDIR)\qnmCommProc.obj" \
	"$(INTDIR)\qnmCommProc1.obj" \
	"$(INTDIR)\qnmsCommProc.obj" \
	"$(INTDIR)\qnmWarnCommProc.obj" \
	"$(INTDIR)\qyCommProc.obj" \
	"$(INTDIR)\getopt.obj" \
	"$(INTDIR)\list.obj" \
	"$(INTDIR)\myNbtScan.obj" \
	"$(INTDIR)\myNbtScanCommon.obj" \
	"$(INTDIR)\nbtscan.obj" \
	"$(INTDIR)\qyNbtScanProc.obj" \
	"$(INTDIR)\range.obj" \
	"$(INTDIR)\statusq.obj" \
	"$(INTDIR)\qySnmpHelp.res"

"$(OUTDIR)\qySnmpHelp.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("qySnmpHelp.dep")
!INCLUDE "qySnmpHelp.dep"
!ELSE 
!MESSAGE Warning: cannot find "qySnmpHelp.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "qySnmpHelp - Win32 Release" || "$(CFG)" == "qySnmpHelp - Win32 Debug"
SOURCE=.\qySnmpHelpPublic\qySnmpCmdProc.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"


"$(INTDIR)\qySnmpCmdProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"


"$(INTDIR)\qySnmpCmdProc.obj"	"$(INTDIR)\qySnmpCmdProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=.\qySnmpHelpPublic\qySnmpDefs.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qySnmpDefs.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qySnmpDefs.obj"	"$(INTDIR)\qySnmpDefs.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\qySnmpHelpPublic\qySnmpGet.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qySnmpGet.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qySnmpGet.obj"	"$(INTDIR)\qySnmpGet.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\qySnmpHelpPublic\qySnmpHelpProc.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qySnmpHelpProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qySnmpHelpProc.obj"	"$(INTDIR)\qySnmpHelpProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\qySnmpHelpPublic\qySnmpScript.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qySnmpScript.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qySnmpScript.obj"	"$(INTDIR)\qySnmpScript.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\qySnmpHelpPublic\qySnmpSet.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qySnmpSet.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qySnmpSet.obj"	"$(INTDIR)\qySnmpSet.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\qySnmpHelpPublic\qySnmpWalk.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qySnmpWalk.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qySnmpWalk.obj"	"$(INTDIR)\qySnmpWalk.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\qySnmpHelp.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"


"$(INTDIR)\qySnmpHelp.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"


"$(INTDIR)\qySnmpHelp.obj"	"$(INTDIR)\qySnmpHelp.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\qySnmpHelp.rc

"$(INTDIR)\qySnmpHelp.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\QySnmpHelpProcDaemon.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"


"$(INTDIR)\QySnmpHelpProcDaemon.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"


"$(INTDIR)\QySnmpHelpProcDaemon.obj"	"$(INTDIR)\QySnmpHelpProcDaemon.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\qySnmpHelp.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\qySnmpHelp.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fp"$(INTDIR)\qySnmpHelp.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\qySnmpHelp.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\qyMc\qymcPublic\qmCommonDbFunc.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qmCommonDbFunc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qmCommonDbFunc.obj"	"$(INTDIR)\qmCommonDbFunc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\qyMc\qymcPublic\qmCommonFunc.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qmCommonFunc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qmCommonFunc.obj"	"$(INTDIR)\qmCommonFunc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\qyMc\qymcPublic\qmSnmpProc.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qmSnmpProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qmSnmpProc.obj"	"$(INTDIR)\qmSnmpProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\qyCustom\qnmCustom.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCustom.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCustom.obj"	"$(INTDIR)\qnmCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\qyCustom\qnmCustomComm.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCustomComm.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCustomComm.obj"	"$(INTDIR)\qnmCustomComm.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\qyCustom\qyCustom.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"


"$(INTDIR)\qyCustom.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"


"$(INTDIR)\qyCustom.obj"	"$(INTDIR)\qyCustom.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\qyCommProc\qnmCommProc.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCommProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCommProc.obj"	"$(INTDIR)\qnmCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\qyCommProc\qnmCommProc1.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qnmCommProc1.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qnmCommProc1.obj"	"$(INTDIR)\qnmCommProc1.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\qyCommProc\qnmsCommProc.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"


"$(INTDIR)\qnmsCommProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"


"$(INTDIR)\qnmsCommProc.obj"	"$(INTDIR)\qnmsCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\qyCommProc\qnmWarnCommProc.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"


"$(INTDIR)\qnmWarnCommProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"


"$(INTDIR)\qnmWarnCommProc.obj"	"$(INTDIR)\qnmWarnCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\qyCommProc\qyCommProc.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\qyCommProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /I "." /I ".." /I "..\..\snmplib" /I "..\.." /I "..\..\include" /I "include" /I "..\..\..\qyInclude" /I "..\..\..\asrInclude" /I "..\..\..\qyPublic\include" /I "..\..\..\qyEncLib\include" /I "..\..\..\qyCustom\include" /I "..\..\..\qyCommProc\include" /I "..\..\..\qyMc\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fr"$(INTDIR)\\" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\qyCommProc.obj"	"$(INTDIR)\qyCommProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\qyProjShare\nbtScan\getopt.c

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"


"$(INTDIR)\getopt.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"


"$(INTDIR)\getopt.obj"	"$(INTDIR)\getopt.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\qyProjShare\nbtScan\list.c

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"


"$(INTDIR)\list.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"


"$(INTDIR)\list.obj"	"$(INTDIR)\list.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\qyProjShare\nbtScan\myNbtScan.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"


"$(INTDIR)\myNbtScan.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"


"$(INTDIR)\myNbtScan.obj"	"$(INTDIR)\myNbtScan.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\qyProjShare\nbtScan\myNbtScanCommon.c

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"


"$(INTDIR)\myNbtScanCommon.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"


"$(INTDIR)\myNbtScanCommon.obj"	"$(INTDIR)\myNbtScanCommon.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\qyProjShare\nbtScan\nbtscan.c

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"


"$(INTDIR)\nbtscan.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"


"$(INTDIR)\nbtscan.obj"	"$(INTDIR)\nbtscan.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\qyProjShare\nbtScan\qyNbtScanProc.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"


"$(INTDIR)\qyNbtScanProc.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"


"$(INTDIR)\qyNbtScanProc.obj"	"$(INTDIR)\qyNbtScanProc.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\qyProjShare\nbtScan\range.c

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"


"$(INTDIR)\range.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"


"$(INTDIR)\range.obj"	"$(INTDIR)\range.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 

SOURCE=..\..\..\qyProjShare\nbtScan\statusq.cpp

!IF  "$(CFG)" == "qySnmpHelp - Win32 Release"


"$(INTDIR)\statusq.obj" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ELSEIF  "$(CFG)" == "qySnmpHelp - Win32 Debug"


"$(INTDIR)\statusq.obj"	"$(INTDIR)\statusq.sbr" : $(SOURCE) "$(INTDIR)"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!ENDIF 


!ENDIF 

