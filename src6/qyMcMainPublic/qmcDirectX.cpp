

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

#include	<ddraw.h>
#include	<dmoreg.h>
#ifndef  __WINCE__
	#include	<d3d9.h>
	#include	<d3dx9.h>
#endif


#include	"qmcDirectX.h"
#include	"qmcDirectXPublic.h"
#include	"qySampleGrabberPublic.h"


 extern  "C"  int  initDynLib_dx(  LPCTSTR  systemDir,  void  **  pp  )
{
	int					iErr	=	-1;
	CQyString			strDir;

	if  (  !pp  )  return  -1;
	if  (  *pp  )  return  -1;

	DYN_LIB_DX	*	pDynLib	=	(  DYN_LIB_DX  *  )malloc(  sizeof(  DYN_LIB_DX  )  );
	if  (  !pDynLib  )  goto  errLabel;
	memset(  pDynLib,  0,  sizeof(  pDynLib[0]  )  );

	strDir  =  CQyString(  systemDir  )  +  CQyString(  _T(  "ddraw.dll"  )  );
	pDynLib->hDll_DDraw  =  LoadLibrary(  strDir.GetBuffer(  0  )  );
	if  (  pDynLib->hDll_DDraw  )  {
		pDynLib->pDirectDrawCreate  =  (  PF_DirectDrawCreate  )myGetProcAddress(  pDynLib->hDll_DDraw,  "DirectDrawCreate"  );
	}

	strDir  =  CQyString(  systemDir  )  +  CQyString(  _T(  "d3d9.dll"  )  );
	pDynLib->hDll_D3D9  =  LoadLibrary(  strDir.GetBuffer(  0  )  );
	if  (  pDynLib->hDll_D3D9  )  {
        pDynLib->pDirect3DCreate9  =  (  PF_Direct3DCreate9  )myGetProcAddress(  pDynLib->hDll_D3D9, "Direct3DCreate9"  );
	}

	strDir  =  CQyString(  systemDir  )  +  CQyString(  _T(  "dsound.dll"  )  );
	pDynLib->hDll_Dsound  =  LoadLibrary(  strDir.GetBuffer(  0  )  );
	if  (  pDynLib->hDll_Dsound  )  {
		pDynLib->pDirectSoundCreate  =  (  PF_DirectSoundCreate  )myGetProcAddress(  pDynLib->hDll_Dsound,  "DirectSoundCreate"  );
		pDynLib->pDirectSoundCaptureCreate  =  (  PF_DirectSoundCaptureCreate  )myGetProcAddress(  pDynLib->hDll_Dsound,  "DirectSoundCaptureCreate"  );
		pDynLib->pDirectSoundCaptureEnumerateW  =  (  PF_DirectSoundCaptureEnumerateW  )myGetProcAddress(  pDynLib->hDll_Dsound,  "DirectSoundCaptureEnumerateW"  );
	}
 
	strDir  =  CQyString(  systemDir  )  +  CQyString(  _T(  "msdmo.dll"  )  );
	pDynLib->hDll_MsDmo  =  LoadLibrary(  strDir.GetBuffer(  0  )  );
	if  (  pDynLib->hDll_MsDmo  )  {
		pDynLib->pDMOEnum  =  (  PF_DMOEnum  )myGetProcAddress(  pDynLib->hDll_MsDmo,  "DMOEnum"  );
		pDynLib->pMoInitMediaType  =  (  PF_MoInitMediaType  )myGetProcAddress(  pDynLib->hDll_MsDmo,  "MoInitMediaType"  );
		pDynLib->pMoFreeMediaType  =  (  PF_MoFreeMediaType  )myGetProcAddress(  pDynLib->hDll_MsDmo,  "MoFreeMediaType"  );
	}


	TCHAR		tmpFileName[MAX_PATH];

	GetModuleFileName(  NULL,  tmpFileName,  mycountof(  tmpFileName  )  );
	TCHAR	*	pT	=	_tcsrchr(  tmpFileName,  _T(  '\\'  )  );
	if  (  !pT  )  goto  errLabel;
	pT  ++  ;  *pT  =  0;

	_sntprintf(  tmpFileName,  mycountof(  tmpFileName  ),  _T(  "%s%s"  ),  tmpFileName,  _T(  "qySampleGrabber.dll"  )  );

	pDynLib->hDll_sampleGrabber  =  LoadLibrary(  tmpFileName  );
	if  (  pDynLib->hDll_sampleGrabber  )  {
		pDynLib->pf_getNewFilter  =  myGetProcAddress(  pDynLib->hDll_sampleGrabber,  "getNewFilter"  );
#if  0
		pDynLib->pf_newCrossBar  =  myGetProcAddress(  pDynLib->hDll_sampleGrabber,  "newCrossBar"  );
		pDynLib->pf_freeCrossBar  =  myGetProcAddress(  pDynLib->hDll_sampleGrabber,  "freeCrossBar"  );
		pDynLib->pf_crossBarGetInputCount  =  myGetProcAddress(  pDynLib->hDll_sampleGrabber,  "crossBarGetInputCount"  );
#endif


	}


	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		exitDynLib_dx(  (  void  **  )&pDynLib  );
	}
	if  (  !iErr  )  {
		*pp  =  pDynLib;
	}


	return  iErr;
}

 extern  "C"  int  exitDynLib_dx(  void  **  pp  )
{
	if  (  !pp  ||  !*pp  )  return  0;

	DYN_LIB_DX  *  pDynLib  =  (  DYN_LIB_DX  *  )*pp;
	
	if  (  pDynLib->hDll_sampleGrabber  )  {
		FreeLibrary(  pDynLib->hDll_sampleGrabber  );  pDynLib->hDll_sampleGrabber  =  NULL;
	}

	if  (  pDynLib->hDll_MsDmo  )  {
		FreeLibrary(  pDynLib->hDll_MsDmo  );  pDynLib->hDll_MsDmo  =  NULL;
	}
	if  (  pDynLib->hDll_Dsound  )  {
		FreeLibrary(  pDynLib->hDll_Dsound  );  pDynLib->hDll_Dsound  =  NULL;
	}
	if  (  pDynLib->hDll_D3D9  )  {
		FreeLibrary(  pDynLib->hDll_D3D9  );  pDynLib->hDll_D3D9  =  NULL;
	}
	if  (  pDynLib->hDll_DDraw  )  {
		FreeLibrary(  pDynLib->hDll_DDraw  );  pDynLib->hDll_DDraw  =  NULL;
	}

	free(  *pp  );  *pp  =  NULL;


	return  0;
}


 BOOL  bSupported_directSound(  )
{
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	if  (  !g_pEnv  )  return  FALSE;
	QY_DYN_LIBS  *  pLibs	=	(  QY_DYN_LIBS  *  )g_pEnv->pDynLibs;
	if  (  !pLibs  )  return  FALSE;
	DYN_LIB_DX	*	pDynLib  =  (  DYN_LIB_DX  *  )pLibs->pLib_dx;
	if  (  !pDynLib  )  return  FALSE;
	if  (  !pDynLib->hDll_Dsound  )  return  FALSE;
	return  TRUE;
}


 int  myGetNewFilter(  QY_ENV  *  pEnv,  REFCLSID  rclsid,  void  *  pParam,  void  **  ppIBaseFilter  )
{
	QY_DYN_LIBS					*	pDynLibs					=	(  QY_DYN_LIBS  *  )pEnv->pDynLibs;
	DYN_LIB_DX					*	pDynLib_dx					=	(  DYN_LIB_DX  *  )pDynLibs->pLib_dx;
	PF_getNewFilter					pf_getNewFilter				=	NULL;

	
	pf_getNewFilter  =  (  PF_getNewFilter  )pDynLib_dx->pf_getNewFilter;
	if  (  !pf_getNewFilter  )  return  -1;
	
	return  pf_getNewFilter(  rclsid,  pParam,  ppIBaseFilter  );
}


#if  0
 void  *  myNewCrossBar(  QY_ENV  *  pEnv,  void  *  pStartingInputPin,  HRESULT  *  phr  )
{
	QY_DYN_LIBS					*	pDynLibs					=	(  QY_DYN_LIBS  *  )pEnv->pDynLibs;
	DYN_LIB_DX					*	pDynLib_dx					=	(  DYN_LIB_DX  *  )pDynLibs->pLib_dx;
	PF_newCrossBar					pf							=	NULL;

	
	pf  =  (  PF_newCrossBar  )pDynLib_dx->pf_newCrossBar;
	if  (  !pf  )  return  NULL;
	
	return  pf(  pStartingInputPin,  phr  );
}

 void  myFreeCrossBar(  QY_ENV  *  pEnv,  void  *  pCrossBarParam  )
{
	QY_DYN_LIBS					*	pDynLibs					=	(  QY_DYN_LIBS  *  )pEnv->pDynLibs;
	DYN_LIB_DX					*	pDynLib_dx					=	(  DYN_LIB_DX  *  )pDynLibs->pLib_dx;
	PF_freeCrossBar					pf							=	NULL;

	
	pf  =  (  PF_freeCrossBar  )pDynLib_dx->pf_freeCrossBar;
	if  (  !pf  )  return;
	
	return  pf(  pCrossBarParam  );
}

 int  myCrossBarGetInputCount(  QY_ENV  *  pEnv,  void  *  pCrossBarParam,  long  *  pCount  )
{
	QY_DYN_LIBS					*	pDynLibs					=	(  QY_DYN_LIBS  *  )pEnv->pDynLibs;
	DYN_LIB_DX					*	pDynLib_dx					=	(  DYN_LIB_DX  *  )pDynLibs->pLib_dx;
	PF_crossBarGetInputCount		pf							=	NULL;

	
	pf  =  (  PF_crossBarGetInputCount  )pDynLib_dx->pf_crossBarGetInputCount;
	if  (  !pf  )  return  -1;
	
	return  pf(  pCrossBarParam,  pCount  );

}
#endif

