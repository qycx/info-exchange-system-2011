



#include "stdafx.h"
#include	<stdlib.h>
#include	<tchar.h>

#include	<windowsx.h>

#include <d3dx9.h>



#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"qySyncCommProc.h"
#include	"qmcVideoCapture.h"


#include	"isCliD3dCommon.h"
#include	"dlgWallD3d.h"

#include	"myresource.h"

#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

 __declspec(  dllexport  )  void  *  getDlgWallsVar_wallD3d(  HWND  hDlgWalls,  int  iWndContentType  )
{

	if  (  iWndContentType  !=  CONST_qyWndContentType_wallD3d  )  {
#ifdef  __DEBUG__
		traceLog(  _T(  "getDlgWallsVar_ts: iWndContentType err, %d"  ),  iWndContentType  );
#endif
		return  NULL;
	}

#if  10

	CDlgWallD3d  *  pDlgWalls  =  (  CDlgWallD3d  *  )CDlgWallD3d::FromHandlePermanent(  hDlgWalls  );
	if  (  !pDlgWalls  )  return  NULL;

	return  &pDlgWalls->m_var.wall;
#endif

}


CDlgWallD3d::CDlgWallD3d()	// standard constructor
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );

	//
	CQyWnd  *  pBase  =  this;
	pBase->m_var.iWndContentType  =  CONST_qyWndContentType_wallD3d;
}


CDlgWallD3d::~CDlgWallD3d(  )
{
}

INT_PTR CALLBACK dlgProc_wall_d3d(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CDlgWallD3d  *  pDlg  =  (  CDlgWallD3d  *  )GetWindowLong(  hDlg,  GWLP_USERDATA  );


	switch  (  uMsg  )  {
			case  WM_INITDIALOG:  {
				  pDlg  =  (  CDlgWallD3d  *  )lParam;
				  if  (  !pDlg  )  goto  errLabel;

				  qyWnd_Attach(  pDlg,  hDlg  );
				  
				  pDlg->OnInitDialog(  );		
			      }
				  return (INT_PTR)TRUE;
				  break;

			case  WM_SIZE:  {
				  UINT  nType  =  wParam;
				  int  cx  =  LOWORD(  lParam  );
				  int  cy  =  HIWORD(  lParam  );
				  //
				  if  (  !pDlg  )  goto  errLabel;
				  //
				  pDlg->OnSize(  nType,  cx,  cy  );
				  }
				  break;
			case  WM_MOVE:  {
				  int  x  =  LOWORD(  lParam  );
				  int  y  =  HIWORD(  lParam  );
				  if  (  !pDlg  )  goto  errLabel;
				  pDlg->OnMove(  x,  y  );				  
				  }
				  break;
			case  WM_MOVING:  {
				  UINT fwSide  =  0;
				  LPRECT  pRect  =  (  LPRECT  )lParam;
				  if  (  !pDlg  )  goto  errLabel;
				  pDlg->OnMoving(  fwSide,  pRect  );
				  }
				  break;
			case  WM_MOUSEMOVE:  {
				  if  (  !pDlg  )  goto  errLabel;
				  pDlg->myMouseMove(  wParam,  lParam  );
				  }
				  break;

			case  WM_COMMAND:  {
				  WORD  wNotifyCode = HIWORD(wParam); 
				  WORD  wID = LOWORD(wParam); 
				  HWND  hwndCtl = (HWND) lParam;
				  
				  FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  );
				  if  (  !pFuncs  )  goto  errLabel;

				  if  (  !pDlg  )  goto  errLabel;

				  if  (  wID  ==  IDCANCEL  )  {
					  pDlg->OnCancel(  );
					  return  TRUE;
				  }
				  
				  pDlg->OnIsCmd(  wID  );
				  
				  return  TRUE;
				  }
				  break;
			case  WM_TIMER:  {
				  if  (  !pDlg  )  goto  errLabel;
				  UINT  nIDEvent  =  (  UINT  )wParam;
				  pDlg->OnTimer(  nIDEvent  );
				  return  TRUE;				  
				  }
				  break;

			case  WM_CLOSE:  {
				  if  (  !pDlg  )  goto  errLabel;
				  pDlg->OnClose(  );
				  return  TRUE;
				  }
				  break;

			case  WM_NCDESTROY:  {
				  OutputDebugString(  _T(  "WM_NCDESTROY\n"  )  );
				  //  if  (  IsWindow(  hDlg  )  )  OutputDebugString(  _T(  "wnd\n"  )  );
				  //  else  OutputDebugString(  _T(  "false\n"  )  );
				  //
				  pDlg->PostNcDestroy(  );
				  //
				  }
				  break;
			case  WM_DESTROY:  {
				  OutputDebugString(  _T(  "WM_DESTROY\n"  )  );
				  if  (  !pDlg  )  goto  errLabel;
				  pDlg->OnDestroy(  );
				  }
				  break;
			default:
					break;
	}

errLabel:

	return (INT_PTR)FALSE;
}

//
 BOOL	CDlgWallD3d::Create(const RECT& rect)
{
	BOOL	bRet	=	FALSE;

	HINSTANCE	hInst  =  NULL;
	hInst  =  get_my_hInst(  );
	HWND hWndParent  =  NULL;		//  2011/02/26
	hWndParent  =  NULL;	//  hParent;


	HWND  hWnd  =  NULL;
		
	hWnd = CreateDialogParam(  hInst,  MAKEINTRESOURCE(IDD_wall_d3d), hWndParent,  dlgProc_wall_d3d,  (  LPARAM  )this   );
	if  (  !hWnd  )  goto  errLabel;



	bRet  =  TRUE;

errLabel:
	return  bRet;
}

BOOL	CDlgWallD3d::bQuitDlg(  )
{
	BOOL		bRet	=	FALSE;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );


	::DestroyWindow(  m_hWnd  );
	bRet  =  TRUE;	
errLabel:
	return  bRet;
}

//
void  CDlgWallD3d::endFullScreen(  )
{
	traceLog(  _T(  "Not finished: dlgWallD3d, endFullScreen"  )  );
}

	
//
BOOL  CDlgWallD3d::OnInitDialog()
{
	return  TRUE;
}


void CDlgWallD3d::OnCancel()
{
	//  bQuitDlg(  );
#ifdef  __DEBUG__
	traceLog(  _T(  "CDlgWallD3d::OnCancel"  )  );
#endif
}


void CDlgWallD3d::OnClose()
{

	//
	bQuitDlg(  );
}

void CDlgWallD3d::OnDestroy()
{
}



void CDlgWallD3d::OnSize(UINT nType, int cx, int cy)
{
}


void  CDlgWallD3d::Onfullscreen()
{
	traceLog(  _T(  "Not finished: dlgWallD3d, Onfullscreen"  )  );
}

	
void  CDlgWallD3d:: OnMoving(UINT fwSide, LPRECT pRect)
{
	setWallsBarPos(  m_hWnd,  &m_var.wall,  NULL  );

}

void  CDlgWallD3d::OnMove(int x, int y)
{

	setWallsBarPos(  m_hWnd,  &m_var.wall,  NULL  );

}



void CDlgWallD3d::myMouseMove(  WPARAM  wParam, LPARAM  lParam)
{
	int  xPos,  yPos;

	 xPos = GET_X_LPARAM(lParam); 
	 yPos = GET_Y_LPARAM(lParam); 

	 
	 //	
	 viewWallsBar(  m_hWnd,  getWndContentType(  ),  xPos,  yPos,  m_hWnd,  &m_var.wall,  FALSE  );



}

//

void  CDlgWallD3d::OnTimer(UINT_PTR nIDEvent)
{
}

void  CDlgWallD3d::OnIsCmd(  UINT nID  )
{
	int		iErr		=	-1;
	TCHAR	tBuf[128]	=	_T(  ""  );

	switch  (  nID  )  {
			case  ID_showMenu_wallsBar:  {
	  				  HWND				hDlgWall		=	m_hWnd;

					  #ifdef  __DEBUG__

							  DLG_wall_var	*	pDlgWallsVar	=	&m_var.wall;
							  if  (  !pDlgWallsVar  )  goto  errLabel;

					  #endif
					  showMenu_wallsBar(  NULL,  hDlgWall,  getWndContentType(  ),  0  );
					  
					  iErr  =  0;  goto  errLabel;
				  }
				  break;

			case  ID_about:
				  myOnAppAbout(  m_hWnd  );
				  break;

			case  ID_selectContact:  {
				  FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );
				  if  (  !pFuncs  )  goto  errLabel;

				  DLG_guiDataParam_objs		param;
				  memset(  &param,  0,  sizeof(  param  )  );
				  param.uiType  =  CONST_objType_messenger;
				  if  (  !showDlgObjs(  NULL,  m_hWnd,  &param  )  )  {
					  QY_MESSENGER_ID	idInfo;
					  idInfo.ui64Id  =  param.o.ui64Id_selected;
					  pFuncs->pf_tryToTalkToMessenger_wallD3d(  0,  &idInfo  );					 
				  }
				  }
				  break;
			case  ID_selectGroup:  {
				  FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );
				  if  (  !pFuncs  )  goto  errLabel;

				  DLG_guiDataParam_objs	param;
				  memset(  &param,  0,  sizeof(  param  )  );
				  param.uiType  =  CONST_objType_imGrp;
				  if  (  !showDlgObjs(  NULL,  m_hWnd,  &param  )  )  {
					  QY_MESSENGER_ID	idInfo;
					  idInfo.ui64Id  =  param.o.ui64Id_selected;
					  pFuncs->pf_tryToTalkToMessenger_wallD3d(  0,  &idInfo  );					 
					 }
				  }
				  break;

			default:
					traceLog(  _T(  "dlgWallsD3d: unprocessed nID %d"  ),  nID  );
					break;
	}
	iErr  =  0;
errLabel:
	return;
}


//
void  CDlgWallD3d::PostNcDestroy()
{

	OutputDebugString(  _T(  "DlgWallD3d::PostNcDestroy: delete this\n"  )  );

	delete  this;

}


