

#include	"stdafx.h"
#include	<tchar.h>
#ifndef  __WINCE__
	#include	<vfw.h>
#else
	#ifdef  __TEST__
		#include	<vfw.h>
	#endif
	#include	<mmreg.h>
	#include	<msacm.h>
#endif

#include	<shlobj.h>

#include	"qyMcMainCommon.h"
#include	"myresource.h"

#include	"myfourcc.h"


#include	"tmpCeLib.h"
#include	"policyAvParams.h"
#include	"qmcVideoCapture.h"
#include	"qyMcMainRealTimeMediaProc.h"

#include	"qmcDmoPublic.h"

#include	"qyOpenShellCommon.h"
#include	"policyIsClientFunc.h"
#include	"funcsForIsCliHelp.h"



//
struct  PolicyAvParams  gAvParams;



