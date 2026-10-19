

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
#include	"qmcDxSurfacePublic.h"


#include	"qmcDxSurface.h"

#include	"tmpCeLib.h"

QY_dxSurface_mgr	gDxSurfaceMgr;
BOOL				gbInited_gDxSurfaceMgr	=	FALSE;

 BOOL  bDxSurfaceInited(  )
{
	return  gbInited_gDxSurfaceMgr;
}

 int  initDxSurfaceMgr(  HWND  hWnd  )
{
	int								iErr				=	-1;
	QY_MC					*		pQyMc				=	QY_GET_GBUF(  );
	QY_DYN_LIBS				*		pDynLibs			=	(  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs;
	DYN_LIB_DX				*		pLib_dx				=	(  DYN_LIB_DX  *  )pDynLibs->pLib_dx;

	QY_dxSurface_mgr		*		p					=	&gDxSurfaceMgr;

	memset(  p,  0,  sizeof(  p[0]  )  );
	
	HRESULT         DDConnect	=	-1;
	LPDIRECTDRAW	lpDD		=	NULL;    // Pointer to DirectDraw

	if  (  !pLib_dx->pDirectDrawCreate  )  goto  errLabel;

	DDConnect  =  pLib_dx->pDirectDrawCreate (  NULL,  &lpDD,  NULL  );     
	if  (  DDConnect  !=  DD_OK  )  goto  errLabel;

    // Atempt to locate DirectDraw4 interface
    DDConnect = lpDD->QueryInterface(
				IID_IDirectDraw,            //    IID_IDirectDraw4,	//  2010/04/01
	            (LPVOID *) &p->lpDD4);
    if  (  DDConnect  !=  S_OK  )  goto  errLabel;

	HRESULT                     hRet;

	// Set cooperative level to exclusive and full screen
    hRet  =  p->lpDD4->SetCooperativeLevel(hWnd, DDSCL_NORMAL);
    if (hRet != DD_OK)  goto  errLabel;

    //**********************************
	//    Create the primary surface
	//**********************************
	// ddsd is a structure of type DDSRUFACEDESC2
	//  DDSURFACEDESC2              ddsd;	//  2010/04/01
	DDSURFACEDESC              ddsd; 
    ZeroMemory(&ddsd, sizeof(ddsd));  // Fill structure with zeros
	// Fill in other members
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS ;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

    hRet = p->lpDD4->CreateSurface(  &ddsd,  &p->lpDDSPrimary,  NULL  );
    if  (  hRet  !=  DD_OK  )  goto  errLabel;

	//**********************************
	//    Create a clipper
	//**********************************
    hRet  =  p->lpDD4->CreateClipper(0, &p->lpDDClipper, NULL);
    if (hRet != DD_OK)  goto  errLabel;

	// Associate clipper with application window
	hRet = p->lpDDClipper->SetHWnd(0, hWnd);
	if (hRet != DD_OK)  {
		traceLogA(  "Clipper not linked to application window"  );
		goto  errLabel;
	}
    // Associate clipper with primary surface
	hRet = p->lpDDSPrimary->SetClipper(  p->lpDDClipper  );
	if (hRet != DD_OK)  {
		traceLogA(  "Clipper not linked to primary surface"  );
		goto  errLabel;
	}

	// First create an off-screen surface
	// in system memory
	
	memset(  &ddsd,  0,  sizeof(  ddsd  )  );
	ddsd.dwSize  =  sizeof(  ddsd  );
	hRet  =  p->lpDDSPrimary->GetSurfaceDesc(  &ddsd  );
	if  (  hRet  !=  DD_OK  )  goto  errLabel;
	traceLogA(  "initDxSurfaceMgr:  ddsd.dwWidth %d, dwHeight %d",  ddsd.dwWidth,  ddsd.dwHeight  );
	p->iWidth  =  ddsd.dwWidth;
	p->iHeight  =  ddsd.dwHeight;

	ZeroMemory(&ddsd, sizeof(ddsd));  // Fill structure with zeros
	// Fill in other members
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
	//  ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;	// | DDSCAPS_SYSTEMMEMORY;
	#ifndef  __WINCE__
			 ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN  |  DDSCAPS_SYSTEMMEMORY;
	#else
			 ddsd.ddsCaps.dwCaps = DDSCAPS_SYSTEMMEMORY;
	#endif	
	ddsd.dwWidth = p->iWidth;
	ddsd.dwHeight = p->iHeight;
    hRet  =  p->lpDD4->CreateSurface(&ddsd, &p->lpDDSOffscreen, NULL);
    if (hRet != DD_OK)  goto  errLabel;

	gbInited_gDxSurfaceMgr  =  TRUE;

	iErr  =  0;

errLabel:

	MACRO_safeRelease(  lpDD  );      // Release old pointer

	traceLogA(  "initDxSurfaceMgr %s",  iErr  ?  "failed."  :  "ok"  );
	qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initDxSurfaceMgr %s"  ),  iErr  ?  _T(  "failed"  )  :  _T(  "OK"  )  );

	if  (  iErr  )  exitDxSurfaceMgr(  );

	return  iErr;
}

 void  exitDxSurfaceMgr(  )
{
	QY_MC					*		pQyMc				=	QY_GET_GBUF(  );
	QY_DYN_LIBS				*		pDynLibs			=	(  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs;
	DYN_LIB_DX				*		pLib_dx				=	(  DYN_LIB_DX  *  )pDynLibs->pLib_dx;

	QY_dxSurface_mgr		*		p					=	&gDxSurfaceMgr;

	if  (  !pLib_dx->pDirectDrawCreate  )  return;

	MACRO_safeRelease(  p->lpDDSOffscreen  );
	MACRO_safeRelease(  p->lpDDClipper  );
	MACRO_safeRelease(  p->lpDDSPrimary  );
	MACRO_safeRelease(  p->lpDD4  );

	gbInited_gDxSurfaceMgr  =  FALSE;

	traceLogA(  "exitDxSurfaceMgr leaves"  );
	qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "exitDxSurfaceMgr returns"  )  );

	return;
}

