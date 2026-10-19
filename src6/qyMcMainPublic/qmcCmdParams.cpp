

#include	"stdafx.h"
#include	<windows.h>

#ifndef  __WINCE__
	#include	<vfw.h>
#else
	#ifdef  __TEST__
		#include	<vfw.h>
	#endif
	#include	<mmreg.h>
	#include	<MSAcm.h>
#endif

#include	<Wincrypt.h>

#include	<tchar.h>

#include	"qmcommon.h"

 //  TCHAR	*	pCmdLine  =  GetCommandLine(  );
 extern  "C"  __declspec(  dllexport  )  int  parseCmdLine_qmc(  LPCTSTR  pCmdLine,  QM_APP_PARAMS  *  pParams  )
{
	int		iErr	=	-1;
		 
	 TCHAR	*	pT;
	 TCHAR	*	pT1;
	 TCHAR	*	pT2;

	 if  (  !pParams  )  return  -1;

	 memset(  pParams,  0,  sizeof(  pParams[0]  )  );

	 for  (  pT  =  (  TCHAR  *  )pCmdLine;  pT;  )  {
		  if  (  !(  pT  =  _tcschr(  pT,  _T(  '-'  )  )  )  )  break;
		  pT  ++  ;
		  switch  (  *pT  )  {
				 case  _T(  'c'  ):
				 case  _T(  'C'  ):
					   pT  ++  ;
					   pT1  =  CONST_qmCmdLine_av;
					   if  (  !_tcsnicmp(  pT,  pT1,  _tcslen(  pT1  )  )  )  {
						   pParams->ucbAv  =  TRUE;
						   //
						   pT  +=  _tcslen(  pT1  );
						   pParams->uiTranNo_sharedObj  =  _tcstoul(  pT,  &pT2,  10  );						   
						   break;
					   }
					   pT1  =  CONST_qmCmdLine_mediaFile;
					   if  (  !_tcsnicmp(  pT,  pT1,  _tcslen(  pT1  )  )  )  {
						   pParams->ucbMediaFile  =  TRUE;
						   //
						   pT  +=  _tcslen(  pT1  );
						   pParams->uiTranNo_sharedObj  =  _tcstoul(  pT,  &pT2,  10  );
						   //
						   #ifdef  __DEBUG__
								   //  qyShowHint(  _T(  "cmdLine %s, uiTranNo_sharedObj %d"  ),  pCmdLine,  pQM->cmd.uiTranNo_sharedObj  );
						   #endif
						   break;
					   }
					   break;
				 case  _T(  'a'  ):
				 case  _T(  'A'  ):
					   pT  ++  ;
					   pT2  =  _tcschr(  pT,  _T(  '-'  )  );
					   if  (  pT2  )  lstrcpyn(  pParams->appObjPrefix,  pT,  min(  pT2  -  pT  +  1,  mycountof(  pParams->appObjPrefix  )  )  );
					   else  lstrcpyn(  pParams->appObjPrefix,  pT,  mycountof(  pParams->appObjPrefix  )  );
					   tTrim(  pParams->appObjPrefix  );
					   break;
				 default:
						break;
		 }	 
	 }

	iErr  =  0;
errLabel:
	return  iErr;
}


 extern  "C"  __declspec(  dllexport  )  int  makeCmdLine_qmc(  QM_APP_PARAMS  *  pParams,  TCHAR  *  cmdLineBuf,  unsigned  int  cnt  )
{
	TCHAR	*	cmdStr  =  _T(  ""  );
	if  (  pParams->ucbAv  )  cmdStr  =  CONST_qmCmdLine_av;
	else  if  (  pParams->ucbMediaFile  )  cmdStr  =  CONST_qmCmdLine_mediaFile;
	else  return  -1;

	_sntprintf(  cmdLineBuf,  cnt,  _T(  "-c%s%u -a%s"  ),  cmdStr,  pParams->uiTranNo_sharedObj,  pParams->appObjPrefix  );    
	return  0;
}
