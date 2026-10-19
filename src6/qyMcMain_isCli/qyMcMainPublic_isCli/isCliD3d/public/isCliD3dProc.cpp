


#include "stdafx.h"
#include	<stdlib.h>
#include	<tchar.h>

#include <d3dx9.h>


#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"qySyncCommProc.h"
#include	"qmcVideoCapture.h"


#include	"isCliD3dCommon.h"
#include	"dlgWallD3d.h"






#ifdef  __DEBUG__
__declspec(  dllexport  )  int  testFunc_d3d(  )
{
	ATOM	a;
	HINSTANCE	hInst  =  get_my_hInst(  );


	return  0;
}
#endif



void  SetupMatrices(  D3D_context  *  pCtx  )
{

	// WorldMatrix
	D3DXMATRIXA16  matWorld;
	D3DXMatrixIdentity(&matWorld);
	pCtx->g_pd3dDevice->SetTransform(  D3DTS_WORLD,  &matWorld  );

	//  View Matrices
	D3DXVECTOR3  vEyePt( 0.0f, 0.0f, -10);
	D3DXVECTOR3  vLookatPt( 0.0f, 0.0f, 0.0f);
	D3DXVECTOR3  vUpVec( 0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16  matView;
	D3DXMatrixLookAtLH( &matView, &vEyePt,  &vLookatPt,  &vUpVec);
	pCtx->g_pd3dDevice->SetTransform(  D3DTS_VIEW,  &matView  );

	//ProjMatrices
	D3DXMATRIXA16  matProj;
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 1.0f, 1.0f, 100.0f);
	pCtx->g_pd3dDevice->SetTransform(  D3DTS_PROJECTION,  &matProj  );
}


HRESULT  InitD3D(  D3D_context  *  pCtx,  HWND  hWnd,  int  wnd_w,  int  wnd_h  )
{
	if  (  !wnd_w  ||  !wnd_h  )  return  E_FAIL;

	if (  NULL  ==  (  pCtx->g_pD3D = Direct3DCreate9(  D3D_SDK_VERSION  )  )  )  {
		return  E_FAIL;
	}

	D3DDISPLAYMODE  d3ddm;

	if (  FAILED(  pCtx->g_pD3D->GetAdapterDisplayMode(  D3DADAPTER_DEFAULT,  &d3ddm  )  )  ){
		return  E_FAIL;
	}

	HRESULT  hr;
	if (  FAILED(  hr  =  pCtx->g_pD3D->CheckDeviceFormat(  D3DADAPTER_DEFAULT,  D3DDEVTYPE_HAL,  d3ddm.Format,  D3DUSAGE_DEPTHSTENCIL,  D3DRTYPE_SURFACE,  D3DFMT_D16  )  )  ){
		if  (  hr  ==  D3DERR_NOTAVAILABLE  )  {
			return  E_FAIL;
		}
	}

	D3DCAPS9 d3dCaps;
	if (  FAILED(  pCtx->g_pD3D->GetDeviceCaps(  D3DADAPTER_DEFAULT,  D3DDEVTYPE_HAL,  &d3dCaps  )  )  ){
			return  E_FAIL;
	}

	DWORD  dwBehaviorFlags  =  0;

	if  (  d3dCaps.VertexProcessingCaps  !=  0 )  dwBehaviorFlags  |=  D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else   dwBehaviorFlags  |=  D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	//
	dwBehaviorFlags  |=  D3DCREATE_MULTITHREADED;	//  2013/07/03

	//
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(  &d3dpp,  sizeof(  d3dpp  )  );
#if  0
	d3dpp.Windowed  =  TRUE;
	d3dpp.SwapEffect  =  D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat  =  D3DFMT_UNKNOWN;
#else
	d3dpp.BackBufferWidth  =  wnd_w;	//  WINDOW_WIDTH;
	d3dpp.BackBufferHeight  =  wnd_h;	//  WINDOW_HEIGHT;
	d3dpp.BackBufferFormat  =  d3ddm.Format;  //  D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount  =  1;
	d3dpp.MultiSampleType  =  D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality  =  0;
	d3dpp.SwapEffect  =  D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow  =  hWnd;
	d3dpp.Windowed  =  TRUE;
	d3dpp.EnableAutoDepthStencil  =  0;
	d3dpp.AutoDepthStencilFormat  =  D3DFMT_UNKNOWN;
	d3dpp.Flags  =  0;
	d3dpp.FullScreen_RefreshRateInHz  =  D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval  =  D3DPRESENT_INTERVAL_IMMEDIATE;
#endif


	//
	if (  FAILED(  pCtx->g_pD3D->CreateDevice(  D3DADAPTER_DEFAULT,  D3DDEVTYPE_HAL,  hWnd,  dwBehaviorFlags,  &d3dpp,  &pCtx->g_pd3dDevice  )  )  ){
			return  E_FAIL;
	}

	pCtx->g_pd3dDevice->SetRenderState(  D3DRS_LIGHTING,  FALSE  );		//  禁用照明

	SetupMatrices(  pCtx  );
	//  bSetupMatrix_txt(  pCtx->g_pd3dDevice,  pCtx->wnd_w,  pCtx->wnd_h  );

	return  S_OK;
}

 __declspec(  dllexport  )  int  fillData_d3d(  BITMAPINFOHEADER  *  pBih,  BYTE  *  pData  )
{
	int				iErr	=	-1;
	
	CQySyncCnt	syncCnt;
	
	D3D_context  *  pCtx  =  &g_d3dContext;

	QIS_textureInfo2  *  pTextureInfo2  =  &pCtx->textureInfo2;

	if  (  pTextureInfo2->iW  <=  0  ||  pTextureInfo2->iH  <=  0  )  goto  errLabel;
	if  (  pBih->biWidth  <=  0  ||  pBih->biHeight  <=  0  )  goto  errLabel;
	if  (  pBih->biBitCount  !=  24  )  goto  errLabel;

	//
	if  (  pTextureInfo2->bQuit  )  goto  errLabel;

	QIS_textureInfo  *  pTextureInfo  =  getTextureInfo_toFill(  pTextureInfo2  );
	if  (  !pTextureInfo  )  goto  errLabel;

	if  (  syncCnt.sync(  &pTextureInfo->lCnt_used  )  )  goto  errLabel;

	if  (  pTextureInfo2->bQuit  )  goto  errLabel;

	//
	D3DLOCKED_RECT d3dLocked_rect;
	if(FAILED(  pTextureInfo->pTexture->LockRect(0,&d3dLocked_rect,0,D3DLOCK_DISCARD)))  {
		goto  errLabel;
	}

	BYTE * pTextureBuffer = static_cast<BYTE*>(d3dLocked_rect.pBits);
	int    nTexturePitch = d3dLocked_rect.Pitch;

	int				lineBytes_src	=	M_lineBytes_rgb(  24,  pBih->biWidth  );

	
	for ( UINT row = 0; row < pTextureInfo2->iH; ++row )  {
		
		//
		if  (  row  >=  pBih->biHeight  )  break;

		//
		BYTE  *  pDest  =  pTextureBuffer  +  (  pTextureInfo2->iH  -  row  -1  )  *  nTexturePitch;
		BYTE  *  pSrc  =  pData  +  row  *  lineBytes_src;

		for ( UINT column = 0; column < pTextureInfo2->iW; ++ column )  {
			
			//
			if  (  column  >=  pBih->biWidth  )  break;

			//
			pDest[0]  =  pSrc[0];
			pDest[1]  =  pSrc[1];
			pDest[2]  =  pSrc[2];
			pDest[3]  =  0xff;

			pDest  +=  4;
			pSrc  +=  3;
			
		}
	}
	
	if(FAILED(pTextureInfo->pTexture->UnlockRect(0)))  {
		goto  errLabel;
	}

	//
	pTextureInfo->bDataReady  =  TRUE;






errLabel:

	return  iErr;
}

 int  fillTestData(  QIS_textureInfo2  *  pTextureInfo2  )
 {
	 int  iErr  =  -1;
	 
	 CQySyncCnt	syncCnt;

	 int  nTextureWidth  =  pTextureInfo2->iW;
	 int  nTextureHeight  =  pTextureInfo2->iH;

	 if  (  !nTextureWidth  ||  !nTextureHeight  )  goto  errLabel;

	 //
	 if  (  pTextureInfo2->bQuit  )  goto  errLabel;

	 //
	QIS_textureInfo  *  pTextureInfo  =  getTextureInfo_toFill(  pTextureInfo2  );
	if  (  !pTextureInfo  )  goto  errLabel;


	if  (  syncCnt.sync(  &pTextureInfo->lCnt_used  )  )  goto  errLabel;

	if  (  pTextureInfo2->bQuit  )  goto  errLabel;
		

	//
	D3DLOCKED_RECT d3dLocked_rect;
	if(FAILED(  pTextureInfo->pTexture->LockRect(0,&d3dLocked_rect,0,D3DLOCK_DISCARD)))  {
		goto  errLabel;
	}

	BYTE * pTextureBuffer = static_cast<BYTE*>(d3dLocked_rect.pBits);
	int    nTexturePitch = d3dLocked_rect.Pitch;
	for ( UINT row = 0; row < nTextureHeight; ++row )
	{
		DWORD  *  pdwDest  =  (DWORD*)pTextureBuffer;

		UINT  nPartWidth  =  nTextureWidth / 4 / 4;

		for ( UINT column = 0; column < nPartWidth; ++ column )
		{
			pdwDest[0]  =  0xFF0000FF;
			pdwDest[1]  =  0xFF0000FF;
			pdwDest[2]  =  0xFF0000FF;
			pdwDest[3]  =  0xFF0000FF;

			pdwDest += 4;
		}
		for ( UINT column = nPartWidth; column < nPartWidth * 2; ++ column )
		{
			pdwDest[0]  =  0xFFFFFF00;
			pdwDest[1]  =  0xFFFFFF00;
			pdwDest[2]  =  0xFFFFFF00;
			pdwDest[3]  =  0xFFFFFF00;

			pdwDest += 4;
		}
		for ( UINT column = nPartWidth * 2; column < nPartWidth * 3; ++ column )
		{
			pdwDest[0]  =  0xFFFF0000;
			pdwDest[1]  =  0xFFFF0000;
			pdwDest[2]  =  0xFFFF0000;
			pdwDest[3]  =  0xFFFF0000;

			pdwDest += 4;
		}
		for ( UINT column = nPartWidth * 3; column < nPartWidth * 4; ++ column )
		{
			pdwDest[0]  =  0xFFFF0000;
			pdwDest[1]  =  0xFFFF0000;
			pdwDest[2]  =  0xFFFF0000;
			pdwDest[3]  =  0xFFFF0000;

			pdwDest += 4;
		}
		pTextureBuffer += nTexturePitch;
	}


	if(FAILED(pTextureInfo->pTexture->UnlockRect(0)))  {
		goto  errLabel;
	}

	//
	pTextureInfo->bDataReady  =  TRUE;

	//
	iErr  =  0;

errLabel:

	return  iErr;
 }


HRESULT  InitGriphics(  D3D_context  *  pCtx  )
{
	int			iErr	=	-1;

	
	if  (  FAILED(  D3DXCreateFont(  pCtx->g_pd3dDevice,  30,  0,  0,  1,  FALSE,  DEFAULT_CHARSET,  OUT_DEFAULT_PRECIS,  DEFAULT_QUALITY,  0,  _T(  "Times New Roman"  ),  &pCtx->g_pFont  )  )   )  goto  errLabel;


#if  0
	//  创建纹理对象
	if (  FAILED(  D3DXCreateTextureFromFile(  g_pd3dDevice,  L"512.jpg",  &g_pTexture  )  )  ){
		MessageBox(  NULL,  L"创建纹理失败",  L"Texture.exe",  MB_OK  );
		return  E_FAIL;
	}
#endif

	int  nTextureWidth  =  890;
	int  nTextureHeight =  590;

	QIS_textureInfo2  *  pTextureInfo2  =  &pCtx->textureInfo2;

	//  更换为动态创建纹理
#if  0
	pCtx->g_pd3dDevice->CreateTexture(  nTextureWidth, nTextureHeight,1,D3DUSAGE_DYNAMIC, D3DFMT_X8R8G8B8,  D3DPOOL_DEFAULT,  &pCtx->g_pTexture,  NULL  );
#endif
	if  (  FAILED(  pCtx->g_pd3dDevice->CreateTexture(  nTextureWidth, nTextureHeight,1,D3DUSAGE_DYNAMIC, D3DFMT_X8R8G8B8,  D3DPOOL_DEFAULT,  &pTextureInfo2->mems[0].pTexture,  NULL  )  )  )  goto  errLabel;
	if  (  FAILED(  pCtx->g_pd3dDevice->CreateTexture(  nTextureWidth, nTextureHeight,1,D3DUSAGE_DYNAMIC, D3DFMT_X8R8G8B8,  D3DPOOL_DEFAULT,  &pTextureInfo2->mems[1].pTexture,  NULL  )  )  )  goto  errLabel;

	//
	pTextureInfo2->iW  =  nTextureWidth;
	pTextureInfo2->iH  =  nTextureHeight;

	//
	fillTestData(  pTextureInfo2  );

	//
	CUSTOMVERTEX g_Vertices[]  =
	{
		{	-3,	-3,	0.0f,	0.0f,	1.0f},
		{	-3,	3,	0.0f,	0.0f,	0.0f},
		{	3,	-3,	0.0f,	1.0f,	1.0f},
		{	3,	3,	0.0f,	1.0f,	0.0f},	
	};

	if(FAILED(pCtx->g_pd3dDevice->CreateVertexBuffer(  4 * sizeof( CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX,  D3DPOOL_MANAGED,  &pCtx->g_pVB,  NULL  ))){
		goto  errLabel;
	}



	void  *  pVertices;
	if  (  SUCCEEDED(pCtx->g_pVB->Lock(0,sizeof(g_Vertices), (void**)&pVertices, 0 )))  {
		memcpy(pVertices,g_Vertices,sizeof(g_Vertices));
		pCtx->g_pVB->Unlock();
		}
	else  {
		  goto  errLabel;
	}


	iErr  =  0;

errLabel:

	return  iErr;
}

void  Cleanup(  D3D_context  *  pCtx  )
{
	//
	exit_txt(  pCtx->g_pd3dDevice,  &pCtx->ctx_txt  );

	//
	QIS_textureInfo2  *  pTextureInfo2  =  &pCtx->textureInfo2;
	int					i;

	pTextureInfo2->bQuit  =  TRUE;
	for  (  i  =  0;  i  <  mycountof(  pTextureInfo2->mems  );  i  ++  )  {
		 if  (  pTextureInfo2->mems[i].lCnt_used  )  {
			 Sleep(  50  );
			 continue;
		 }
	}
	for  (  i  =  0;  i  <  mycountof(  pTextureInfo2->mems  );  i  ++  )  {
		 MACRO_safeRelease(  pTextureInfo2->mems[i].pTexture  );
	}

	//
	MACRO_safeRelease(  pCtx->g_pVB  );

	//
	MACRO_safeRelease(  pCtx->g_pFont  );

	//
	MACRO_safeRelease(  pCtx->g_pd3dDevice  );

	MACRO_safeRelease(  pCtx->g_pD3D  );

}

float  get_fps(  )
{
	static  float	fps  =  0;				//  fps
	static  int		iCount  =  0;			//  帧数
	static	float	curTime  =  0.0f;
	static	float	lastTime  =  0.0f;

	iCount ++;
	curTime  =  timeGetTime(  )  *  0.001f;
	
	if  (  curTime  -  lastTime  >  1.0f  )
	{
		fps  =  (  float  )iCount  /  (  curTime  -  lastTime  );
		lastTime  =  curTime;
		iCount  =  0;
	}

	return  fps;			
}


__declspec(  dllexport  )  void  myRender()
{
	D3D_context  *  pCtx  =  &g_d3dContext;

	if  (  !pCtx->g_pd3dDevice  )  return;
	
	//
	QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
	GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
	if  (  pGBuf->ucbChanged  )  {
		exit_txt(  pCtx->g_pd3dDevice,  &pCtx->ctx_txt  );
		init_txt(  pCtx->g_pd3dDevice,  &pCtx->ctx_txt,  pGBuf->hint  );
		pGBuf->ucbChanged  =  FALSE;
	}


	//
	float  cur_time  =  (  float  )timeGetTime(  );	
	float  time_delta  =  (  cur_time  - pCtx->last_time  )  *  0.001f;
	pCtx->last_time  =  cur_time;
	
	//
	pCtx->g_pd3dDevice->Clear(  0,  NULL,  D3DCLEAR_TARGET,  D3DCOLOR_XRGB(  45,50,170),  1.0f, 0  );


	if  (  SUCCEEDED(  pCtx->g_pd3dDevice->BeginScene())){

#if  10
		QIS_textureInfo  *  pTextureInfo  =  getTextureInfo_toRend(  &pCtx->textureInfo2  );
		if  (  pTextureInfo  )  {
			pCtx->g_pd3dDevice->SetTexture(  0,  pTextureInfo->pTexture  );		
			pCtx->g_pd3dDevice->SetStreamSource(  0,  pCtx->g_pVB,  0,  sizeof(  CUSTOMVERTEX)  );
			pCtx->g_pd3dDevice->SetFVF(  D3DFVF_CUSTOMVERTEX );
			pCtx->g_pd3dDevice->DrawPrimitive(  D3DPT_TRIANGLESTRIP,  0,  2  );
		}
#endif

		//
		//  bSetMatrix_txt(  pCtx->g_pd3dDevice,  pCtx->wnd_w,  pCtx->wnd_h  );  
		display_txt(  pCtx->g_pd3dDevice,  &pCtx->ctx_txt,  time_delta  );

		//
		TCHAR	g_strFPS[50]  =  _T(  ""  );
		int  charCount  =  swprintf_s(  g_strFPS,  20,  _T(  "中文FPS:%0.3f"  ),  get_fps(  )  );
		RECT	rc  =  {  0,  0,  pCtx->wnd_w,  pCtx->wnd_h,  };
		pCtx->g_pFont->DrawText(  NULL,  g_strFPS,  charCount,  &rc,  DT_CENTER,  D3DCOLOR_XRGB(  255,  239,  136  )  );


		//
		pCtx->g_pd3dDevice->EndScene();
	}
	pCtx->g_pd3dDevice->Present(  NULL,  NULL, NULL,NULL  );

}

void  SetClientSize(  HWND  hWnd,  int  clientWidth,  int  clientHeight  )
{
	if  (  IsWindow(  hWnd  )  )
	{
		DWORD  dwStyle  =  GetWindowLongPtr(  hWnd,  GWL_STYLE  );
		DWORD  dwExStyle  =  GetWindowLongPtr(  hWnd,  GWL_EXSTYLE  );
		HMENU  menu  =  GetMenu(  hWnd  );

		RECT  rc  =  {  0,  0,  clientWidth,  clientHeight  };

		if  (  !AdjustWindowRectEx(  &rc,  dwStyle,  menu  ?  TRUE  :FALSE,  dwExStyle  )  )
			MessageBox(  NULL,  L"AdjustWindowRectEx Failed",  L"error",  MB_OK  );

		SetWindowPos(  hWnd,  NULL,  0,  0,  rc.right  -  rc.left,  rc.bottom  -  rc.top,  SWP_NOZORDER  |  SWP_NOMOVE  );

#ifdef  _DEBUG
		RECT  newClientRC;
		GetClientRect(  hWnd,  &newClientRC  );
		assert(  (  newClientRC.right  -  newClientRC.left  )  ==  clientWidth  );
		assert(  (  newClientRC.bottom  -  newClientRC.top  )  ==  clientHeight  );
#endif
	}
}

__declspec(  dllexport  )  int  createWall_d3d(  void  *  pGBuf_d3d  )
{
	int					iErr	=	-1;
	GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pGBuf_d3d;
	if  (  !pGBuf  )  return  -1;
	
	HINSTANCE		hInstance  =  get_my_hInst(  );

    //
    CDlgWallD3d  *  pDlg	=  NULL;
	RECT			rect;
	BOOL			bCreated  =  FALSE;


	pDlg  =  new  CDlgWallD3d;
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;
	bCreated  =  TRUE;

#if  10
	//
	int  flg  =  SWP_NOMOVE  |  SWP_NOSIZE  |  SWP_NOACTIVATE  |  SWP_SHOWWINDOW;	
	SetWindowPos(  pDlg->m_hWnd,  NULL,  0,  0,  0,  0,  flg  );
#endif


   pGBuf->hWall_d3d  =  pDlg->m_hWnd;


   //
   D3D_context  *  pCtx  =  &g_d3dContext;
   
   //
   int  wnd_w  =  1024;
   int  wnd_h  =  768;
   SetClientSize(  pGBuf->hWall_d3d,  wnd_w,  wnd_h  );

   //
   GetClientRect(  pGBuf->hWall_d3d,  &rect  );
   pCtx->wnd_w  =  rect.right  -  rect.left;
   pCtx->wnd_h  =  rect.bottom  -  rect.top;

   //
   if  (  !SUCCEEDED(  InitD3D(  pCtx,  pGBuf->hWall_d3d,  pCtx->wnd_w,  pCtx->wnd_h  )  )  )  goto  errLabel;

   //
   pCtx->last_time  =  (  float  )timeGetTime(  );

   //
   if  ( !SUCCEEDED( InitGriphics(  pCtx  )  )  )  goto  errLabel;

   //
   TCHAR	*	hint  =  _T(  "Welcome to use Qycx video conference!"  );
   if  (  init_txt(  pCtx->g_pd3dDevice,  &pCtx->ctx_txt,  hint  )  )  goto  errLabel;  


	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  !bCreated  )  {
			if  (  pDlg  )  delete  pDlg;
		}
		//
		closeWall_d3d(  pGBuf_d3d  );
	}


	return  iErr;

}


 __declspec(  dllexport  )  int  closeWall_d3d(  void  *  pGBuf_d3d  )
{
	int					iErr		=	-1;

	GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pGBuf_d3d;
	if  (  !pGBuf  )  return  -1;

	D3D_context  *  pCtx  =  &g_d3dContext;

	if  (  pGBuf->hWall_d3d  )  {
		if  (  IsWindow(  pGBuf->hWall_d3d  )  )  {
			//
			SendMessage(  pGBuf->hWall_d3d,  WM_CLOSE,  0,  0  );
			//
			if  (  IsWindow(  pGBuf->hWall_d3d  )  )  {
				traceLog(  _T(  "closeTestWnd_d3d: failed, hWnd_test still exists"  )  );
				goto  errLabel;
			}
		}	
		pGBuf->hWall_d3d  =  NULL;
	}


	//  这里似乎应该先停止d3d的动作，然后再Cleanup。	
	Cleanup(  pCtx  );


	iErr  =  0;

errLabel:
	return  iErr;

}


 
