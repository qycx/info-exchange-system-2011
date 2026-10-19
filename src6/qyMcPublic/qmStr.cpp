

#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<windows.h>
#include	<tchar.h>
#include	"qyCommon.h"
#include	"qyCommProc.h"
#include	"qyLangCommProc.h"
#include	"qyTCharCommProc.h"
//  #include	"qyCusResPublic.h"
#include	"tmpCeLib.h"

#include	"qmStr.h"
#include	"qyPreCustom.h"




LPCTSTR		CONST_str_serviceExits		=	_T(  "Service exits."  );	//服务退出完毕

 
 QY_DMITEM  CONST_qyAppAvLevelTable_en[]  =
{
	{		CONST_qyAppAvLevel_null,	},
	{		CONST_qyAppAvLevel_basic,							_T(  "Basic"  ),			(  TCHAR  *  )CONST_resId_qyAppAvLevel_basic,	},
	{		CONST_qyAppAvLevel_standard,						_T(  "Standard"  ),			(  TCHAR  *  )CONST_resId_qyAppAvLevel_standard,	},
	{		CONST_qyAppAvLevel_high,							_T(  "High"  ),				(  TCHAR  *  )CONST_resId_qyAppAvLevel_high,	},
	{		CONST_qyAppAvLevel_top,								_T(  "Top"  ),				(  TCHAR  *  )CONST_resId_qyAppAvLevel_top,	},
	{		-1,							},

};



