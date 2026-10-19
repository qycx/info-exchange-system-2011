


#include	"stdafx.h"

#include	<windows.h>
#include	<tchar.h>
#include	"qyCommon.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCustom.h"
#include	"qyTCharCommProc.h"



#if  0
			#define		__SUPPORT_gps__				//  2012/05/23
#endif


//
#if  defined(  __APP_qyMc_touchscreen__  )  //  ||  defined(  __SUPPORT_devAuth__  )
		#define		DEFAULT_qyAppAvLevel					CONST_qyAppAvLevel_standard
#else	//  主要改下面这个策略

		#define		DEFAULT_qyAppAvLevel					CONST_qyAppAvLevel_basic  //  standard	//  high		//  

#endif



 extern  "C"  unsigned  short  qyGetAppAvLevel_default(  )
{
	return  DEFAULT_qyAppAvLevel;
}

  extern  "C"  BOOL  bSupported_gps_default(  )
{
	#ifdef  __SUPPORT_gps__
			return   TRUE;
	#endif

	 return  FALSE;
 }
