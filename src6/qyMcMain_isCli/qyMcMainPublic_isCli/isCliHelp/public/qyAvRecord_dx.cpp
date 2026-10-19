
#include	"stdafx.h"

#include	<dmoreg.h>
#ifndef  __WINCE__
	#include	<d3d9.h>
	#include	<d3dx9.h>
#endif

#include	"qyMcMainCommon.h"
#include	"qmShell_open.h"
#include	"qmcVideoCapture.h"

#include	"qyAvRecord.h"
#include	"qyAvRecord_dx.h"
#ifndef  __WINCE__
		 #include	"qyBoundWnd.h"
#endif
#include	"qyDynLib.h"
#include	"..\\qyHookHelp\\qyHookHelp.h"
//  #include	"myresource.h"
#include	"tmpCeLib.h"
#include	"funcsForIsCliHelp.h"


#define			CONST_bitsPerPixel		24


 




 __declspec(  dllexport  )  BOOL  canShareScreen_dx(  )
{
	BOOL							bRet				=	FALSE;
	QY_MC					*		pQyMc				=	QY_GET_GBUF(  );
	int								iServiceId			=	CONST_qyServiceId_mis;
	QY_SERVICEGUI_INFO		*		pSci				=	getServiceGuiInfo(  pQyMc,  iServiceId  );
	//
	QY_DYN_LIBS				*		pDynLibs			=	(  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs;
	DYN_LIB_DX				*		pLib_dx				=	(  DYN_LIB_DX  *  )pDynLibs->pLib_dx;
	//
	MC_VAR_isCli				*		pProcInfo			=	(  MC_VAR_isCli  *  )pSci->pVar;
	int								i;
	BOOL							bFull				=	TRUE;

	if  (  !pLib_dx  )  return  FALSE;
	if  (  !pLib_dx->pDirect3DCreate9  )  return  FALSE;

	if  (  !pProcInfo  )  return  FALSE;
	if  (  !pProcInfo->pSharedObjs  )  return  FALSE;

	for  (  i  =  1;  i  <  pProcInfo->cfg.usMaxCnt_pSharedObjs;  i  ++  )  {
		 if  (  !pProcInfo->pSharedObjs[i].bUsed  )  {
			 bFull  =  FALSE;
			 continue;
		 }
		 if  (  pProcInfo->pSharedObjs[i].bDirectX  )  return  FALSE;		//  远程协助只能一个。因为鼠标键盘只有一个
	}

	return  !bFull;
}

 void  exitD3D(  QY_AV_RECORD  *  pAvRecord  )
{		
#ifdef  __WINCE__
	return;
#else
	if  (  pAvRecord->directX.g_pSurface  )  {
		pAvRecord->directX.g_pSurface->Release(  );
		pAvRecord->directX.g_pSurface  =  NULL;
	}
	if  (  pAvRecord->directX.g_pd3dDevice  )  {
		pAvRecord->directX.g_pd3dDevice->Release(  );
		pAvRecord->directX.g_pd3dDevice  =  NULL;
	}
	if  (  pAvRecord->directX.g_pD3D  )  {
		pAvRecord->directX.g_pD3D->Release(  );
		pAvRecord->directX.g_pD3D  =  NULL;
	}
#endif
}


 int  initD3D(  DYN_LIB_DX  *  pDynLib,  HWND  hWnd,  QY_AV_RECORD  *  pAvRecord  )
{
#ifdef  __WINCE__
	return  -1;
#else
	 int						iErr	=	-1;
	 D3DDISPLAYMODE				ddm;
	 D3DPRESENT_PARAMETERS		d3dpp;
	 
	 if  (  !pDynLib->pDirect3DCreate9  )  return  -1;

	 if  (  (  pAvRecord->directX.g_pD3D  =  pDynLib->pDirect3DCreate9(  D3D_SDK_VERSION  )  )  ==  NULL  )  {
		 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  "",  _T(  "IsClient"  ),  0,  _T(  "capScreen"  ),  _T(  ""  ),  _T(  "Direct3DCreate9 failed"  )  );
		 traceLogA(  "Direct3DCreate9 failed."  );  goto  errLabel;
	 }	 
	 if  (  FAILED(  pAvRecord->directX.g_pD3D->GetAdapterDisplayMode(  D3DADAPTER_DEFAULT,  &ddm  )  )  )  {
		 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  "",  _T(  "IsClient"  ),  0,  _T(  "capScreen"  ),  _T(  ""  ),  _T(  "GetAdapterDisplayMode failed"  )  );
		 traceLogA(  "GetAdapterDisplayMode failed"  );  goto  errLabel;
	 }

	 ZeroMemory(  &d3dpp,  sizeof(  D3DPRESENT_PARAMETERS  )  );

	 d3dpp.Windowed  =  TRUE;
	 d3dpp.Flags  =  D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	 d3dpp.BackBufferFormat  =  ddm.Format;
	 //  d3dpp.BackBufferHeight  =  pAvRecord->directX.gScreenRect.bottom  =  ddm.Height;
	 //  d3dpp.BackBufferWidth  =  pAvRecord->directX.gScreenRect.right  =  ddm.Width;
	 d3dpp.BackBufferHeight  =  ddm.Height;
	 d3dpp.BackBufferWidth  =  ddm.Width;
	 d3dpp.MultiSampleType  =  D3DMULTISAMPLE_NONE;
	 d3dpp.SwapEffect  =  D3DSWAPEFFECT_DISCARD;
	 d3dpp.hDeviceWindow  =  hWnd;
	 d3dpp.PresentationInterval  =  D3DPRESENT_INTERVAL_DEFAULT;
	 d3dpp.FullScreen_RefreshRateInHz  =  D3DPRESENT_RATE_DEFAULT;

	 if  (  FAILED(  pAvRecord->directX.g_pD3D->CreateDevice(  D3DADAPTER_DEFAULT,  D3DDEVTYPE_HAL,  hWnd,  D3DCREATE_SOFTWARE_VERTEXPROCESSING,  &d3dpp,  &pAvRecord->directX.g_pd3dDevice  )  )  )  {
		 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  "",  _T(  "IsClient"  ),  0,  _T(  "capScreen"  ),  _T(  ""  ),  _T(  "CreateDevice failed"  )  );
		 traceLogA(  "Unable  to  Create Device  "  );  goto  errLabel;
	 }

	 if  (  FAILED(  pAvRecord->directX.g_pd3dDevice->CreateOffscreenPlainSurface(  ddm.Width,  ddm.Height,  D3DFMT_A8R8G8B8,  D3DPOOL_SCRATCH,  &pAvRecord->directX.g_pSurface,  NULL  )  )  )  {
		 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  "",  _T(  "IsClient"  ),  0,  _T(  "capScreen"  ),  _T(  ""  ),  _T(  "CreateOffscreenPlainSurface failed"  )  );
		 traceLogA(  "Unable to  Create  Surface  "  );  goto  errLabel;
	 }

	 iErr  =  0;
errLabel:
	 if  (  iErr  )  exitD3D(  pAvRecord  );
	 return  iErr;
#endif
}


 void  cleanUp_avRecord(  QY_AV_RECORD  *  pAvRecord  )  
{
	/*
	if  (  pAvRecord->directX.hBackBitmap  )  {
		DeleteObject(  pAvRecord->directX.hBackBitmap  );  pAvRecord->directX.hBackBitmap  =  NULL;
	}
	*/
	if  (  pAvRecord->pBits  )  {
		free(  pAvRecord->pBits  );  pAvRecord->pBits  =  NULL;
	}

	if  (  pAvRecord->bUseDirectX  )  {
		exitD3D(  pAvRecord  );
		/*
		if  (  pAvRecord->directX.g_pSurface  )  {
			pAvRecord->directX.g_pSurface->Release(  );
			pAvRecord->directX.g_pSurface  =  NULL;
		}
		if  (  pAvRecord->directX.g_pd3dDevice  )  {
			pAvRecord->directX.g_pd3dDevice->Release(  );
			pAvRecord->directX.g_pd3dDevice  =  NULL;
		}
		if  (  pAvRecord->directX.g_pD3D  )  {
			pAvRecord->directX.g_pD3D->Release(  );
			pAvRecord->directX.g_pD3D  =  NULL;
		}
		*/
	}

}


 int  doCreate_avRecord(  QY_DYN_LIBS  *  pDynLibs,  HWND  hWnd,  COMPRESS_VIDEO  *  pCompressVideo,  BOOL  bUseDirectX,  QY_AV_RECORD  *  pAvRecord  )
{
	int				iErr		=	-1;
	if  (  !pDynLibs  )  return  -1;
	DYN_LIB_DX  *	pDynLib		=	(  DYN_LIB_DX  *  )pDynLibs->pLib_dx;
	if  (  !pDynLib  )  return  -1;
	//  HWND			hDesktop	=	NULL;
	//  HDC				hdc			=	NULL;
	int				iWidth,  iHeight;

	pAvRecord->nBits  =  CONST_bitsPerPixel;

	iWidth  =  pCompressVideo->width;
	iHeight  =  pCompressVideo->height;
	makeBmpInfoHeader_rgb(  pAvRecord->nBits,  iWidth,  iHeight,  &pAvRecord->bmpInfo.bmiHeader  );

	/*
	hDesktop  =  GetDesktopWindow(  );
	hdc  =  GetDC(  hDesktop  );
	pAvRecord->directX.hBackBitmap  =  CreateDIBSection(  hdc,  &pAvRecord->directX.bmpInfo,  DIB_RGB_COLORS,  &pAvRecord->directX.pBits,  NULL,  0  );
	if  (  pAvRecord->directX.hBackBitmap  ==  NULL  )  {
		traceLogA(  "Unable  to  Create  BackBuffer  Bitmap  "  );
		goto  errLabel;
	}
	ReleaseDC(  hDesktop,  hdc  );  hdc  =  NULL;
	*/
	pAvRecord->pBits  =  malloc(  pAvRecord->bmpInfo.bmiHeader.biSizeImage  );
	if  (  !pAvRecord->pBits  )  goto  errLabel;

	pAvRecord->bUseDirectX  =  bUseDirectX;		//  2009/09/23

	if  (  pAvRecord->bUseDirectX  )  {

		if  (  initD3D(  pDynLib,  hWnd,  pAvRecord  )  )  goto  errLabel;

		//
		pAvRecord->directX.gCapturedRect.left  =  pCompressVideo->left;
		pAvRecord->directX.gCapturedRect.top  =  pCompressVideo->top;
		pAvRecord->directX.gCapturedRect.right  =  pCompressVideo->left  +  pCompressVideo->width  -  1;
		pAvRecord->directX.gCapturedRect.bottom  =  pCompressVideo->top  +  pCompressVideo->height  -  1;

	}

	iErr  =  0;

errLabel:

	/*
	if  (  hdc  )  {
		ReleaseDC(  hDesktop,  hdc  );
	}
	*/

	if  (  iErr  )  {
		cleanUp_avRecord(  pAvRecord  );
	}

	return  iErr;
}

 void  saveBitmap_debug(  char  *  szFilename,  HBITMAP  hBitmap  )
{
#ifdef  __WINCE__
	return;
#else
	HDC						hdc		=	NULL;
	FILE				*	fp		=	NULL;
	LPVOID					pBuf	=	NULL;
	BITMAPINFO				bmpInfo;
	BITMAPFILEHEADER		bmpFileHeader;

	do  {
		hdc  =  GetDC(  NULL  );
		ZeroMemory(  &bmpInfo,  sizeof(  BITMAPINFO  )  );
		bmpInfo.bmiHeader.biSize  =  sizeof(  BITMAPINFOHEADER  );
		GetDIBits(  hdc,  hBitmap,  0,  0,  NULL,  &bmpInfo,  DIB_RGB_COLORS  );

		if  (  bmpInfo.bmiHeader.biSizeImage  <=  0  )  
			bmpInfo.bmiHeader.biSizeImage  =  bmpInfo.bmiHeader.biWidth  *  abs(  bmpInfo.bmiHeader.biHeight  )*  (  bmpInfo.bmiHeader.biBitCount +7  )  /  8;
		
		if  (  (  pBuf  =  malloc(  bmpInfo.bmiHeader.biSizeImage  )  )  ==  NULL  )  {
			myMessageBox(  NULL,  _T(  "Unable  to  Allocate Bitmap Memory  "  ),  _T(  "Error"  ),  MB_OK | MB_ICONERROR  );
			break;
		}

		bmpInfo.bmiHeader.biCompression  =  BI_RGB;
		GetDIBits(  hdc,  hBitmap, 0,  bmpInfo.bmiHeader.biHeight,  pBuf,  &bmpInfo,  DIB_RGB_COLORS  );

		if  (  (  fp  =  fopen(  szFilename,  "wb"  )  )  ==  NULL  )  {
			myMessageBox(  NULL,  _T(  "Unable  to  Create Bitmap File"  ),  _T(  "Error"  ),  MB_OK|MB_ICONERROR   );
			break;
		}

		bmpFileHeader.bfReserved1  =  0;
		bmpFileHeader.bfReserved2  =  0;
		bmpFileHeader.bfSize  =  sizeof(  BITMAPFILEHEADER  )  +  sizeof(  BITMAPINFOHEADER  )  +  bmpInfo.bmiHeader.biSizeImage;
		bmpFileHeader.bfType  =  'MB';
		bmpFileHeader.bfOffBits  =  sizeof(  BITMAPFILEHEADER  )  +  sizeof(  BITMAPINFOHEADER  );

		fwrite(  &bmpFileHeader,  sizeof(  BITMAPFILEHEADER  ),  1,  fp  );
		fwrite(  &bmpInfo.bmiHeader,  sizeof(  BITMAPINFOHEADER  ),  1,  fp  );
		fwrite(  pBuf,  bmpInfo.bmiHeader.biSizeImage,  1,  fp  );

	}  while(  false  );

	if  (  hdc  )  ReleaseDC(  NULL,  hdc  );
	if  (  pBuf  )  free(  pBuf  );
	if  (  fp  )  fclose(  fp  );

	return;
#endif
}

 int  doCapture_dx(  DYN_LIB_DX  *  pDynLib,  COMPRESS_VIDEO  *  pCompressVideo,  QY_AV_RECORD  *  pAvRecord  )
{
#ifdef  __WINCE__
	return  -1;
#else
	int					iErr				=	-1;
	TCHAR				szFileName[512]		=	_T(  "c:\\tttbbb\\ScreenShot.bmp"  );
	BOOL				bLocked				=	FALSE;
	int					iWidth				=	pCompressVideo->width;
	int					iHeight				=	pCompressVideo->height;

		
	if  (  D3D_OK  !=  pAvRecord->directX.g_pd3dDevice->GetFrontBufferData(  0,  pAvRecord->directX.g_pSurface  )  )  {
		traceLogA(  "GetFrontBufferData failed."  );  goto  errLabel;
	}

	#ifdef  __DEBUG__
			if  (  10  )  {
				//  D3DXSaveSurfaceToFileW(  szFileName,  D3DXIFF_BMP,  pAvRecord->directX.g_pSurface,  NULL,  NULL  );
			}
	#endif

	D3DLOCKED_RECT  lockedRect;
	if  (  FAILED(  pAvRecord->directX.g_pSurface->LockRect(  &lockedRect,  &pAvRecord->directX.gCapturedRect,  D3DLOCK_NO_DIRTY_UPDATE|D3DLOCK_NOSYSLOCK|D3DLOCK_READONLY  )  )  )  {
		traceLogA(  "Unable to Lock Front Buffer Surface  "  ); goto  errLabel;				
	}
	bLocked  =  TRUE;

	//  saveBitmap_debug(  "c:\\tttbbb\\0.bmp",  pAvRecord->directX.hBackBitmap  );

	switch  (  pAvRecord->nBits  )  {
			case  32:
				    for  (  int  i  =  0;  i  <  iHeight; i ++  )  {
						 memcpy(  (  BYTE  *  )pAvRecord->pBits  +  (  iHeight  -  i  -  1  )  *  iWidth  *  pAvRecord->nBits  /  8,  (  BYTE  *  )lockedRect.pBits  +  i  *  lockedRect.Pitch,  iWidth  *  pAvRecord->nBits  /  8  );
					}
					break;
			case  24:  {  //  下面将32位图->24位

					//  int  widthBytes1  =  iWidth  *  4;					
				    int  widthBytes1  =  lockedRect.Pitch;
					int  widthBytes2  =  (  iWidth  *  24  +  31  )  /  32  *  4;
					int	 i,  j;
					int  offset1,  offset2;

					for  (  i  =  0;  i  <  iHeight;  i  ++  )  {
						 int  m1  =  (  iHeight  -  i  -  1  )  *  widthBytes1;
						 int  m2  =  i  *  widthBytes2;
						 for  (  j  =  0;  j  <  iWidth;  j  ++  )  {
							  offset1  =  m1  +  j  *  4;
							  offset2  =  m2  +  j  *  3;
							  (  (  BYTE  *  )pAvRecord->pBits  )[offset2  +  0]  =  *(  (  (  BYTE  *  )lockedRect.pBits  )  +  offset1  +  0  );
							  (  (  BYTE  *  )pAvRecord->pBits  )[offset2  +  1]  =  *(  (  (  BYTE  *  )lockedRect.pBits  )  +  offset1  +  1  );
							  (  (  BYTE  *  )pAvRecord->pBits  )[offset2  +  2]  =  *(  (  (  BYTE  *  )lockedRect.pBits  )  +  offset1  +  2  );							  
						 }
					}

				    }
				    break;
			default:
					goto  errLabel;
	}

	if  (  bLocked  )  {
		pAvRecord->directX.g_pSurface->UnlockRect(  );
		bLocked  =  FALSE;
	}

	//  saveBitmap_debug(  "c:\\tttbbb\\1.bmp",  pAvRecord->directX.hBackBitmap  );
	
	iErr  =  0;
				  
errLabel:

	if  (  bLocked  )  {
        pAvRecord->directX.g_pSurface->UnlockRect(  );
	}

	return  iErr;
#endif
}



#if  0
 int  testCap(  )
{
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	//  CWnd			*	pWnd			=	AfxGetMainWnd(  );
	BOOL				bDynLibInited	=	FALSE;
	QY_DYN_LIBS		*	pDynLibs		=	(  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs;
	TCHAR				systemDir[MAX_PATH];

	myGetSystemDirectory(  systemDir,  mycountof(  systemDir  )  );	
	tTrailDir(  systemDir,  mycountof(  systemDir  )  );
	if  (  initDynLib_dx(  CQyString(  systemDir  ),  &pDynLibs->pLib_dx  )  )  goto  errLabel;
	bDynLibInited  =  TRUE;

	/*
	doCreate(  (  DYN_LIB_DX  *  )pDynLibs->pLibDx,  pWnd->m_hWnd,  NULL  );
	
	doKk(  (  DYN_LIB_DX  *  )pDynLibs->pLibDx,  NULL  );

	doDestroy(  );
	*/

errLabel:

	if  (  bDynLibInited  )  exitDynLib_dx(  &pDynLibs->pLib_dx  );
	return  0;
}
#endif



 int  recordVideo_dx(  MC_VAR_isCli  *  pProcInfo,  QY_AV_recordMgr  *  pMgr,  int  iIndex_screenCapProcInfo,  int  top,  int  left,  int  width,  int  height,  int  fps,  LPCTSTR  szFileName  ) 
{
#ifdef  __NOTSUPPORT_qyAvRecord__
		return  -1;
#else

	int								iErr				=	-1;
	if  (  !pProcInfo  )  return  -1;
	QY_MC					*		pQyMc				=	(  QY_MC  *  )pProcInfo->pQyMcParam;
	if  (  !pQyMc  )  return  -1;
	FUNCS_for_isCliHelp		*		pFuncs				=	QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return  -1;
	//	 
	CAP_procInfo_screen		*		pScreenCapProcInfo	=	(  CAP_procInfo_screen  *  )getCapBmpBySth(  pProcInfo,  iIndex_screenCapProcInfo,  0  );
	if  (  !pScreenCapProcInfo  )  return  -1;
	QY_SHARED_OBJ			*		pSharedObj			=	getSharedObjByIndex(  pProcInfo,  pScreenCapProcInfo->iIndex_sharedObj  );
	if  (  !pSharedObj  )  return  -1;
	COMPRESS_VIDEO			*		pCompressVideo		=	&pScreenCapProcInfo->compressVideo;
	QY_AV_RECORD			*		pAvRecord			=	(  QY_AV_RECORD  *  )pCompressVideo->pData;
	//  POINT							cursorPoint;

	QY_DYN_LIBS				*		pDynLibs			=	(  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs;
	//  CWnd					*		pWnd				=	AfxGetMainWnd(  );
	//  if  (  !pWnd  )  return  -1;
	HWND							hWnd				=	pQyMc->gui.hMainWnd;

	myDRAW_VIDEO_DATA				pkts[1];				//  2011/07/15

	CQyMalloc						mallocObj_pMsgBuf;
	MIS_MSGU				*		pMsgBuf				=	(  MIS_MSGU  *  )mallocObj_pMsgBuf.malloc(  sizeof(  MIS_MSGU  )  );
	if  (  !pMsgBuf  )  return  -1;

	//
	int				timelapse;				// =5;
	DWORD			nFrames					=	0;		//  2011/07/25

	timelapse  =  5;
	if  (  fps  )  {
		timelapse  =  1000  /  fps;
		if  (  timelapse  *  fps  <  1000  )  {
			timelapse  ++  ;
		}
	}

	//  2011/07/15
	memset(  pkts,  0,  sizeof(  pkts  )  );

	if  (  pMgr->m_var.flashingRect  )  {
		pAvRecord->pFrame->SetUpRegion(left,top,width,height,0);
		pAvRecord->pFrame->ShowWindow(  SW_SHOW  );

		pAvRecord->pFrame->PaintBorder(  pAvRecord->borderColor  );
	}

	if  (  doCreate_avRecord(  pDynLibs,  hWnd,  pCompressVideo,  TRUE,  pAvRecord  )  )  goto  errLabel;

	DWORD  timeexpended,  frametime,  oldframetime;	
	BOOL   bFirstCapture;			//	=  0;
	
	pAvRecord->initialtime = mytimeGetTime();		
	bFirstCapture  =  TRUE;	
	oldframetime = 0;
	pAvRecord->nCurrFrame = 0;
	pAvRecord->nActualFrame = 0;

	long  divx,  oldsec;
	divx  =  0;
	oldsec  =  0;
	while  (  !pSharedObj->bQuit  &&  pSharedObj->bUsed  &&  !pMgr->m_var.bStop  ) {  //repeatedly loop

		   /*
		   char  tBuf[256];
		   static  int  iLoops  =  0;  iLoops  ++  ;
		   _sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  ),  _T(  "RecordVideo %d\n"  ),  iLoops  );
		   OutputDebugString(  tBuf  );
		   */
	
		   if  (  !bFirstCapture  )  {			 
			   timeexpended  =  mytimeGetTime()  -  pAvRecord->initialtime;			
			   }
		   else {
			    frametime = 0;
				timeexpended = 0;			
		   }		
		
		   //  moving region
		   pAvRecord->pFrame->m_var.readingRegion = 0;
		   while  (  pAvRecord->pFrame->m_var.writingRegion)
		   {
		   }
		   pAvRecord->pFrame->m_var.readingRegion = 1;

		   if  (   pAvRecord->pFrame->m_var.newRegionUsed   )  {

			   left  =  pAvRecord->pFrame->newRect.left;
			   top  =  pAvRecord->pFrame->newRect.top;
			   pAvRecord->pFrame->m_var.newRegionUsed = 0;
			   //  width and height unchanged
		   }
		   pAvRecord->pFrame->m_var.readingRegion = 0;			
			
		   if  (  left  !=  pCompressVideo->left  ||  top  !=  pCompressVideo->top  )  {	//  2008/11/17，将左上角记录下来。在远程协助时有用
			   pCompressVideo->left  =  left;
			   pCompressVideo->top  =  top;

			   pAvRecord->directX.gCapturedRect.left  =  pCompressVideo->left;
			   pAvRecord->directX.gCapturedRect.top  =  pCompressVideo->top;
			   pAvRecord->directX.gCapturedRect.right  =  pCompressVideo->left  +  pCompressVideo->width  -  1;
			   pAvRecord->directX.gCapturedRect.bottom  =  pCompressVideo->top  +  pCompressVideo->height  -  1;

			   pAvRecord->pFrame->PaintBorder(  pAvRecord->borderColor  );
		   }

		   doCapture_dx(  (  DYN_LIB_DX  *  )pDynLibs->pLib_dx,  pCompressVideo,  pAvRecord  );

		   if  (  !bFirstCapture  ) {
			   if  (  timelapse  >  1000  )  frametime  ++  ;
			   else  frametime  =  (  DWORD  )(  (  (  double  )timeexpended  /  1000.0  )  *  (  double  )(  1000.0  /  timelapse  )  );
			   }
		   else  {
			     bFirstCapture  =  FALSE;			//  设置为0表明后续工作是第2次了
		   }
		
		   pAvRecord->fTimeLength = ((float) timeexpended) /((float) 1000.0);

		   if  (  (frametime==0) || (frametime>oldframetime)) { 

			    pkts[0].head.uiLen  =  pAvRecord->bmpInfo.bmiHeader.biSizeImage;
				pkts[0].memory.m_pBuf  =  (  char  *  )pAvRecord->pBits;

				//  2011/12/05
				memcpy(  &pkts[0].bih,  (  BITMAPINFO  *  )&pAvRecord->bmpInfo,  sizeof(  pkts[0].bih  )  );

            	//  toShareBmp(  pProcInfo,  CONST_capType_screen,  iIndex_screenCapProcInfo,  (  BITMAPINFO  *  )&pAvRecord->bmpInfo,  pkts,  1,  pCompressVideo,  pSharedObj,  pMsgBuf  );
				pFuncs->pf_toShareBmp(  pProcInfo,  CONST_capType_screen,  iIndex_screenCapProcInfo,  pkts,  1,  pCompressVideo,  pSharedObj,  pMsgBuf  );
                        
				
				pAvRecord->nActualFrame ++ ;
				pAvRecord->nCurrFrame = frametime;
				pAvRecord->fRate  =  (  (  float  )pAvRecord->nCurrFrame  )  /  pAvRecord->fTimeLength;						
				pAvRecord->fActualRate  =  (  (  float  )pAvRecord->nActualFrame  )  /  pAvRecord->fTimeLength;
			
				//Update recording stats every half a second
				//  divx = timeexpended / 500;
				divx  =  timeexpended  / 30000;		//  20秒显示一次状态信息
				if  (  divx  !=  oldsec  )  {				
					oldsec  =  divx;
					//  InvalidateRect(  pMgr->m_var.hWndMgr,NULL, FALSE);	
					//  traceLogA(  "fRate %f, fActualRate %f",  pAvRecord->fRate,  pAvRecord->fActualRate  );
					qyShowInfo(  CONST_qyShowType_qwmComm,  0,  "",  _T(  "IsClient"  ),  0,  _T(  "capScreen"  ),  _T(  ""  ),  _T(  "fps %.2f, actual fps %.2f"  ),  pAvRecord->fRate,  pAvRecord->fActualRate  );
				}			

				//
				oldframetime  =  frametime;

		   } // if frametime is different


		   nFrames  ++  ;	//  2011/07/25

		   DWORD  timeexpended1  =  timeGetTime()  -  pAvRecord->initialtime;			
		   DWORD	timeexpended_needed  =  nFrames  *  timelapse;
		   int  remainlapse  =  5;
		   if  (  timeexpended_needed  >  timeexpended1  +  5  )  {
			   remainlapse  =  timeexpended_needed  -  timeexpended1;
		   }
		   Sleep(  remainlapse  );

#ifdef  __DEBUG__
		   int  n  =  timeexpended  /  timelapse;
		   traceLog(  _T(  "timeexpended %d, n%d, nFrames %d, remainlaps %d"  ),  timeexpended,  n,  nFrames,  remainlapse  );
#endif

#if  0
		   {
			   //  introduce time lapse
			   //  maximum lapse when recordstate changes will be less than 100 milliseconds
			   int  no_iteration  =  timelapse  /  50;
			   int  remainlapse  =  timelapse  -  no_iteration  *  50;		 
			   for  (  int  j  =  0;  j  <  no_iteration;  j  ++  )  {
				    ::Sleep(  50  ); //  Sleep for 50 milliseconds many times
					if (  pSharedObj->bQuit  )  break;
			   }		
			   if (  !pSharedObj->bQuit  )  Sleep(  remainlapse  );
		   }
#endif

	}  //  for loop

	

	iErr  =  0;

errLabel:

	if (  pMgr->m_var.flashingRect) {
		pAvRecord->pFrame->ShowWindow(SW_HIDE);
	}

	cleanUp_avRecord(  pAvRecord  );

	OutputDebugString(  _T(  "recordVideo_dx leaves\n"  )  );

	return  iErr;
#endif
}


