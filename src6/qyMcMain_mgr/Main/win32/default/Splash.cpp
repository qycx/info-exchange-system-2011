// CG: This file was added by the Splash Screen component.
// Splash.cpp : implementation file
//

#include	"stdafx.h"				// e. g. stdafx.h
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainWndProc.h"
#include	"mainClient.h"
#include	"mainFrm.h"

#include	"resource.h"			// e.g. resource.h
#include	"Splash.h"				// e.g. splash.h

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


 BOOL  LoadBitmapFromBMPFile( LPTSTR szFileName, HBITMAP *phBitmap, HPALETTE *phPalette )
{     
	 BITMAP  bm;

     *phBitmap  =  NULL;
     *phPalette  =  NULL;

     // Use LoadImage() to get the image loaded into a DIBSection
     *phBitmap  =  (  HBITMAP  )LoadImage(  NULL,  szFileName,  IMAGE_BITMAP,  0,  0,  LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE  );
     if  (  *phBitmap  ==  NULL  )  return  FALSE;

     // Get the color depth of the DIBSection
     GetObject(  *phBitmap,  sizeof(BITMAP),  &bm  );
     // If the DIBSection is 256 color or less, it has a color table
     if  (  (  bm.bmBitsPixel * bm.bmPlanes  )  <=  8  )  {
       	 HDC           hMemDC;
       	 HBITMAP       hOldBitmap;
       	 RGBQUAD       rgb[256];
       	 LPLOGPALETTE  pLogPal;
       	 WORD          i;

       	 // Create a memory DC and select the DIBSection into it
       	 hMemDC = CreateCompatibleDC( NULL );
       	 hOldBitmap = (  HBITMAP  )SelectObject( hMemDC, *phBitmap );
       	 // Get the DIBSection's color table
       	 GetDIBColorTable( hMemDC, 0, 256, rgb );
       	 // Create a palette from the color table
       	 pLogPal = (  LPLOGPALETTE  )malloc( sizeof(LOGPALETTE) + (256*sizeof(PALETTEENTRY)) );
       	 pLogPal->palVersion = 0x300;
       	 pLogPal->palNumEntries = 256;
       	 for  (  i  =  0;  i  <  256;  i  ++  )  {
         	  pLogPal->palPalEntry[i].peRed = rgb[i].rgbRed;
         	  pLogPal->palPalEntry[i].peGreen = rgb[i].rgbGreen;
         	  pLogPal->palPalEntry[i].peBlue = rgb[i].rgbBlue;
         	  pLogPal->palPalEntry[i].peFlags = 0;
       	 }
       	 *phPalette  =  CreatePalette(  pLogPal  );
       	 // Clean up
       	 free( pLogPal );
       	 SelectObject( hMemDC, hOldBitmap );
       	 DeleteDC( hMemDC );
     	 }
     else   {   // It has no color table, so use a halftone palette
     
     		 HDC    hRefDC;

     		 hRefDC = GetDC( NULL );
     		 *phPalette = CreateHalftonePalette( hRefDC );
     		 ReleaseDC( NULL, hRefDC );
     }
     
	 return TRUE;

}


/////////////////////////////////////////////////////////////////////////////
//   Splash Screen class

BOOL CSplashWnd::c_bShowSplashWnd;
CSplashWnd* CSplashWnd::c_pSplashWnd;
CSplashWnd::CSplashWnd()
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	
}

CSplashWnd::~CSplashWnd()
{
	// Clear the static window pointer.
	ASSERT(c_pSplashWnd == this);
	c_pSplashWnd = NULL;
}

BEGIN_MESSAGE_MAP(CSplashWnd, CWnd)
	//{{AFX_MSG_MAP(CSplashWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CSplashWnd::EnableSplashScreen(BOOL bEnable /*= TRUE*/)
{
	c_bShowSplashWnd = bEnable;
}

void CSplashWnd::ShowSplashScreen(CWnd* pParentWnd /*= NULL*/)
{
	if  (  !c_bShowSplashWnd  ||  c_pSplashWnd  !=  NULL  )  return;

	// Allocate a new splash screen, and create the window.
	c_pSplashWnd = new CSplashWnd;
	if  (  !c_pSplashWnd->Create(  pParentWnd  )  )  {
		delete  c_pSplashWnd;
		
		QY_MC		*	pQyMc	=	QY_GET_GBUF(  );

		pQyMc->gui.ucbNotSplashed  =  TRUE;		//  2005/11/06

		/*
		if  (  !bQyMcLogon(  pQyMc  )  )  {
			PostQuitMessage(  1  );  return;
		}

		AfxGetMainWnd(  )->CenterWindow(  );
		AfxGetMainWnd(  )->ShowWindow(  AfxGetApp(  )->m_nCmdShow  );
		AfxGetMainWnd(  )->UpdateWindow(  );
		*/

		}
	else
		c_pSplashWnd->UpdateWindow();
}

BOOL CSplashWnd::PreTranslateAppMessage(MSG* pMsg)
{
	if (c_pSplashWnd == NULL)
		return FALSE;

	// If we get a keyboard or mouse message, hide the splash screen.
	if (pMsg->message == WM_KEYDOWN ||
	    pMsg->message == WM_SYSKEYDOWN ||
	    pMsg->message == WM_LBUTTONDOWN ||
	    pMsg->message == WM_RBUTTONDOWN ||
	    pMsg->message == WM_MBUTTONDOWN ||
	    pMsg->message == WM_NCLBUTTONDOWN ||
	    pMsg->message == WM_NCRBUTTONDOWN ||
	    pMsg->message == WM_NCMBUTTONDOWN)
	{
		c_pSplashWnd->HideSplashScreen();
		return TRUE;	// message handled here
	}

	return FALSE;	// message not handled
}

BOOL CSplashWnd::Create(CWnd* pParentWnd /*= NULL*/)
{

	//  if (!m_bitmap.LoadBitmap(IDB_SPLASH))  return FALSE;
	//  这里将IDB_SPLASH的装载改为从目录里读取
	QY_MC		*	pQyMc										=	QY_GET_GBUF(  );
	HBITMAP			hBitmap										=	NULL;
	HPALETTE		hPalette									=	NULL;
	TCHAR			splashFileName[CONST_qyMaxPathLen  +  1];

	if  (  !pQyMc  ||  !pQyMc->cfg.pGuiCfg  )  return  FALSE;
	_sntprintf(  splashFileName,  mycountof(  splashFileName  ),  _T(  "%s%s%s"  ),  pQyMc->cfg.installDir,  CString(  CONST_qyResSubDir  ),  CString(  pQyMc->cfg.pGuiCfg->splashBmpPureFile  )  );
	if  (  !LoadBitmapFromBMPFile(  CString(  splashFileName  ).GetBuffer(  0  ),  &hBitmap,  &hPalette  )  )  return  FALSE;
	if  (  hPalette  )  DeleteObject(  hPalette  );
	if  (  !m_bitmap.Attach(  hBitmap  )  )  return  FALSE;

	BITMAP  bm;
	m_bitmap.GetBitmap(  &bm  );

	return  CreateEx(  0,  AfxRegisterWndClass(0, AfxGetApp()->LoadStandardCursor(IDC_ARROW)),
					   NULL, WS_POPUP | WS_VISIBLE, 0, 0, bm.bmWidth, bm.bmHeight, pParentWnd->GetSafeHwnd(), NULL);
}

 
void CSplashWnd::HideSplashScreen()
{
	// Destroy the window, and update the mainframe.
	DestroyWindow();

	CMainFrame	*	pMainFrame  =  (  CMainFrame  *  )AfxGetMainWnd(  );

	qyShowMainWnd(  pMainFrame->m_hWnd,  &pMainFrame->var  );

}

void CSplashWnd::PostNcDestroy()
{
	// Free the C++ class.
	delete this;
}

//  注意，这里生成了一个定时器，不知在窗口消失时是否自动释放?
int CSplashWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Center the window.
	CenterWindow();

	// Set a timer to destroy the splash screen.
	SetTimer(  1,  1000,  NULL  );

	return 0;
}

void CSplashWnd::OnPaint()
{
	CPaintDC dc(this);

	CDC dcImage;
	if (!dcImage.CreateCompatibleDC(&dc))
		return;

	BITMAP bm;
	m_bitmap.GetBitmap(&bm);

	// Paint the image.
	CBitmap* pOldBitmap = dcImage.SelectObject(&m_bitmap);
	dc.BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCCOPY);
	dcImage.SelectObject(pOldBitmap);
}

void CSplashWnd::OnTimer(UINT_PTR nIDEvent)
{
	// Destroy the splash screen window.
	traceLogA(  "SplashWnd OnTimes(  ), %d",  m_var.iTimes  );
	
	m_var.iTimes  ++  ;
	if  (  m_var.iTimes  <  5  )  return;
	HideSplashScreen();
}
