# Microsoft Developer Studio Project File - Name="qnmRegTool" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=qnmRegTool - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "qnmRegTool.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "qnmRegTool.mak" CFG="qnmRegTool - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "qnmRegTool - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "qnmRegTool - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "qnmRegTool - Win32 Release for 98" (based on "Win32 (x86) Application")
!MESSAGE "qnmRegTool - Win32 Debug for 98" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "qnmRegTool - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\..\Release\bin"
# PROP Intermediate_Dir "..\..\..\..\..\o\qnmRegTool\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\..\qyOpen\qyCommProc_open\include" /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /I "..\..\..\..\qyCusResSrc\qyCusRes\include" /I "..\..\..\..\qyCusResSrc\qyCusRes\general\include" /I "..\..\..\..\qyOpen\qyCommProc_open\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D WINVER=0x0400 /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /i "..\..\..\qyCommProc\include" /i "..\..\..\qyCustom\include" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 qwmShared.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib qyPublicStaticNoMfc.lib qyEncLibStaticNoMfc.lib mpr.lib wsock32.lib /nologo /subsystem:windows /machine:I386 /out:"..\..\..\..\..\Release\bin/qyRegTool.exe" /libpath:"..\..\..\..\..\Release\lib"

!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\..\Debug\bin"
# PROP Intermediate_Dir "..\..\..\..\..\o\qnmRegTool\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\..\qyOpen\qyCommProc_open\include" /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /I "..\..\..\..\qyCusResSrc\qyCusRes\include" /I "..\..\..\..\qyCusResSrc\qyCusRes\general\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_UNICODE" /D "UNICODE" /D WINVER=0x0400 /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /i "..\..\..\qyCommProc\include" /i "..\..\..\qyCustom\include" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 qwmShared.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib qyPublicStaticNoMfc.lib qyEncLibStaticNoMfc.lib mpr.lib wsock32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\..\..\..\Debug\bin/qyRegTool.exe" /pdbtype:sept /libpath:"..\..\..\..\..\Debug\lib"

!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Release for 98"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "qnmRegTool___Win32_Release_for_98"
# PROP BASE Intermediate_Dir "qnmRegTool___Win32_Release_for_98"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\..\..\Release\bin"
# PROP Intermediate_Dir "..\..\..\..\..\o\qnmRegTool\Releasefor98"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "..\..\..\qyOpen\qyCommProc_open\include" /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /I "..\..\..\..\qyCusResSrc\qyCusRes\include" /I "..\..\..\..\qyCusResSrc\qyCusRes\general\include" /I "..\..\..\..\qyOpen\qyCommProc_open\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D WINVER=0x0400 /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /i "..\..\..\qyCommProc\include" /i "..\..\..\qyCustom\include" /d "NDEBUG"
# ADD RSC /l 0x804 /i "..\..\..\qyCommProc\include" /i "..\..\..\qyCustom\include" /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib qyPublicStaticNoMfc.lib qyEncLibStaticNoMfc.lib mpr.lib /nologo /subsystem:windows /machine:I386 /out:"..\..\..\..\Release\bin/qyRegTool.exe" /libpath:"..\..\..\..\Release\lib"
# ADD LINK32 qwmShared.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib qyPublicStaticNoMfc.lib qyEncLibStaticNoMfc.lib mpr.lib wsock32.lib /nologo /subsystem:windows /machine:I386 /out:"..\..\..\..\..\Release\bin/qyRegTool98.exe" /libpath:"..\..\..\..\..\Release\lib"

!ELSEIF  "$(CFG)" == "qnmRegTool - Win32 Debug for 98"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "qnmRegTool___Win32_Debug_for_98"
# PROP BASE Intermediate_Dir "qnmRegTool___Win32_Debug_for_98"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\..\..\Debug\bin"
# PROP Intermediate_Dir "..\..\..\..\..\o\qnmRegTool\Debugfor98"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "..\..\..\qyOpen\qyCommProc_open\include" /I "..\..\..\asrInclude" /I "..\..\..\qyInclude" /I "..\..\..\qyPublic\include" /I "..\..\include" /I "." /I "..\..\..\qyCommProc\include" /I "..\..\..\qyEncLib\include" /I "..\qrtPublic" /I "..\..\..\qyCustom\include" /I "..\..\..\tmpInclude" /I "..\..\..\..\qyCusResSrc\qyCusRes\include" /I "..\..\..\..\qyCusResSrc\qyCusRes\general\include" /I "..\..\..\..\qyOpen\qyCommProc_open\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D WINVER=0x0400 /D CUR_qySystemId=CONST_qySystemId_netMc2 /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /i "..\..\..\qyCommProc\include" /i "..\..\..\qyCustom\include" /d "_DEBUG"
# ADD RSC /l 0x804 /i "..\..\..\qyCommProc\include" /i "..\..\..\qyCustom\include" /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib qyPublicStaticNoMfc.lib qyEncLibStaticNoMfc.lib mpr.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\..\..\Debug\bin/qyRegTool.exe" /pdbtype:sept /libpath:"..\..\..\..\Debug\lib"
# ADD LINK32 qwmShared.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib qyPublicStaticNoMfc.lib qyEncLibStaticNoMfc.lib mpr.lib wsock32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\..\..\..\..\Debug\bin/qyRegTool98.exe" /pdbtype:sept /libpath:"..\..\..\..\..\Debug\lib"

!ENDIF 

# Begin Target

# Name "qnmRegTool - Win32 Release"
# Name "qnmRegTool - Win32 Debug"
# Name "qnmRegTool - Win32 Release for 98"
# Name "qnmRegTool - Win32 Debug for 98"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\qnmRegTool.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=.\qnmRegTool.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\qnmRegTool.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\qnmRegTool.ico
# End Source File
# Begin Source File

SOURCE=.\res\qnmRegTool.rc2
# End Source File
# Begin Source File

SOURCE=.\small.ico
# End Source File
# End Group
# Begin Group "qyCustom"

# PROP Default_Filter ""
# Begin Group "qyCustomInclude"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\qyCustom\include\qnmCustom.h
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCustom\include\qnmCustomComm.h
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCustom\include\qwmAllHints.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\qyCustom\qnmCustom.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCustom\qnmCustomRegTool.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCustom\qwmAllHints.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCustom\qyCusResHelp.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCustom\qyCustom.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "qrtSecChk"

# PROP Default_Filter ""
# End Group
# Begin Group "qrtPublic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\qrtPublic\qyRegToolProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "qwmGuiPublic"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\qwmGuiPublic\qwmRegProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "qyCommProc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\qyCommProc\qnmCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qnmGuiCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qnmHotKeys.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qwmDynFunc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qwmStreamCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qyDmItemCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qyLangCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qyShowHintCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\qyTCharCommProc.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\qyCommProc\traceLogA.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# Begin Group "cusRes"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\..\qyCusResSrc\qyCusRes\shared\qnmCustomGui_qwm.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
