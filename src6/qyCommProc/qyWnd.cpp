
#include	"stdafx.h"

#include	<windows.h>
#include	<tchar.h>
#include	"qyCommon.h"
#include	"qyWnd.h"


CQyWnd::CQyWnd(  )
{
	this->m_hWnd  =  NULL;
#if  0
	this->iWndContentType  =  0;
	this->iSubType  =  0;
#endif
	memset(  &m_var,  0,  sizeof(  m_var  )  );

}


CQyWnd::~CQyWnd(  )
{
}


int  CQyWnd::getWndContentType(  )
{
	return  m_var.iWndContentType;
}

//  2012/04/02
int  CQyWnd::getWndContentSubType(  )
{
	return  m_var.iSubType;
}

#if  0
BOOL CQyWnd::Attach(  HWND hWndNew  )
{
	if  (  !IsWindow(  hWndNew  )  )  return  FALSE;

	SetWindowLong(  hWndNew,  GWL_USERDATA,  (  LONG_PTR  )this  );
	this->m_hWnd  =  hWndNew;

	return  TRUE;
}
#endif

	
CQyWnd* CQyWnd::FromHandle(  HWND  hWnd  )
{
	CQyWnd  *  pWnd  =  (  CQyWnd  *  )GetWindowLong(  hWnd,  GWLP_USERDATA  );
	return  pWnd;
}

CQyWnd* CQyWnd::FromHandlePermanent(HWND hWnd)
{
	CQyWnd  *  pWnd  =  (  CQyWnd  *  )GetWindowLong(  hWnd,  GWLP_USERDATA  );
	return  pWnd;
}




 //
 __declspec(  dllexport  )  int  centerWnd(  HWND  hWnd  )
{
	RECT	rc;
	int		cx,  cy;

	GetWindowRect(  hWnd,  &rc  );
	cx  =  rc.right  -  rc.left;
	cy  =  rc.bottom  -  rc.top;

	SetWindowPos(  hWnd,  HWND_TOP,  GetSystemMetrics(  SM_CXSCREEN  )  /  2  -  cx  /  2,  GetSystemMetrics(  SM_CYSCREEN  )  /  2  -  cy  /  2,  0,  0,  SWP_NOSIZE  );
	
	return  0;
}

 __declspec(  dllexport  )  int  makeDlgResizable(  HWND  hDlg  )
{
	DWORD	dwStyle;  dwStyle  =  GetWindowLong(  hDlg,  GWL_STYLE  );
	if  (  !(  dwStyle  &  WS_THICKFRAME  )  )  {		  
		dwStyle  |=  WS_THICKFRAME;
		SetWindowLong(  hDlg,  GWL_STYLE,  dwStyle  );
		//
		HMENU	hMenu  =  GetSystemMenu(  hDlg,  FALSE  );
		if  (  hMenu  )  {
			InsertMenu(  hMenu,  0,  MF_BYPOSITION  |  MF_STRING,  SC_SIZE,  _T(  "&Size"  )  );
		}
	}
	return  0;
 }


 __declspec(  dllexport  )  int  makeWndNoBorder(  HWND  hWnd,  BOOL  bThin,  HMENU  *  phMenu,  long  *  plStyle  ) 
{
	long  lStyle	=	0;
	lStyle  =  GetWindowLong(  hWnd,  GWL_STYLE  );
	//  2012/07/07
	if  (  plStyle  )  *plStyle  =  lStyle;
	//
	lStyle  &=  ~(  WS_CAPTION  |  WS_THICKFRAME  );
	if  (  bThin  )  lStyle  |=  WS_BORDER;
	SetWindowLong(  hWnd,  GWL_STYLE,  lStyle  );


	HMENU	hMenu	=	GetMenu(  hWnd  );
	//
	::SetMenu(  hWnd,  NULL  );
	if  (  !phMenu  )  {
		if  (  hMenu  )  DestroyMenu(  hMenu  );
		}
	else  {
		  *phMenu  =  hMenu;
	}

	return  0;
}

 int  restoreWndBorder(  HWND  hWnd,  HMENU  *  phMenu,  long  *  plStyle  )
{
	 if  (  !phMenu  ||  !plStyle  )  return  -1;

	 long	lStyle  =  *plStyle;
	 SetWindowLong(  hWnd,  GWL_STYLE,  lStyle  );


	 //
	 BOOL	bRet;	 
	 bRet  =  ::SetMenu(  hWnd,  *phMenu  );
	 if  (  bRet  )  {
		 *phMenu  =  NULL;		
	 }
					  
	 return  0;
 }
