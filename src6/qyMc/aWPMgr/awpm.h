
#ifndef  __AWPM_H__
#define  __AWPM_H__		/*  {  */

#include	"qyCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"

#include	"qyCommProc.h"
#include	"bhbSrc1CommProc.h"

#include	"awpmCfg.h"
#include	"asrWMonCfg.h"
#include	"awpmService.h"
#include	"qnmCustom.h"

#ifdef  __cplusplus
  extern  "C"  {
#endif

typedef  struct  __awpm_sub_service_t	{
				 TCHAR					appName[256];
				 TCHAR					path[1024];
				 TCHAR					cmdLine[512];		//  2007/06/13
}		 AWPM_SUB_SERVICE;

typedef  struct  __awpm_t  {

				 MACRO_qyAppCommonMems

				 HANDLE				hEvent[AWPM_MAX_SERVICES];
				 AWPM_SUB_SERVICE	aSS[AWPM_MAX_SERVICES];
				 int				totalServices;

}		 AWPM;

int  initAwpm( AWPM *pAwpm );
void  exitAwpm( AWPM *pAwpm );
int  setAwpmQuitKey( );
int  clearAwpmQuitKey( );
int  tryToMgrSubServices( AWPM *p,  TCHAR  *  hint,  unsigned  int  cnt  );
int  tryToStopSubServices( AWPM *p );
#define		DisplayLastError(  szApi  )		qyDisplayLastError(  szApi  )
int  getServiceCfg( LPCTSTR rootServiceKey, AWPM_SUB_SERVICE *pASS );
int  setQuitKey( TCHAR *rootKey );
int  setAwpmQuitKey( );
int  clearQuitKey( TCHAR *rootKey );
int  clearAwpmQuitKey( );


#ifdef  __cplusplus
  }
#endif

#endif  /* } */

