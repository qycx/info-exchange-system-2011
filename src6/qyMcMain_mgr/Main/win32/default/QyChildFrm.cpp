// QyChildFrm.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"

#include	"qyMc.h"

#include	"QyChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQyChildFrm

IMPLEMENT_DYNCREATE(CQyChildFrm, CMDIChildWnd)

CQyChildFrm::CQyChildFrm()
{
}

CQyChildFrm::~CQyChildFrm()
{
}


BEGIN_MESSAGE_MAP(CQyChildFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CQyChildFrm)
	//}}AFX_MSG_MAP
	ON_MESSAGE( QY_WM_COMM, OnQyComm )
	ON_MESSAGE(  CONST_qyWm_postComm,  OnQyPostComm  )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQyChildFrm message handlers


BOOL CQyChildFrm::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CMDIFrameWnd* pParentWnd, CCreateContext* pContext) 
{
	QY_MC	*	pQyMc  =  QY_GET_GBUF(  );
	m_hMenuShared  =  pQyMc->gui.hMenuChildFrm;
		
	return CMDIChildWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, pContext);
}


 LRESULT  CQyChildFrm::OnQyComm( WPARAM wParam, LPARAM lParam )
{
	int								lErr			=			-1;
	QY_MC				*			pQyMc			=			QY_GET_GBUF( );
	QY_WMBUF_COMM		*			pComm			=			( QY_WMBUF_COMM * )lParam;
	

	switch  (  pComm->uiType  )  {
			case  QY_WMPARAM_GETVIEWTYPE:				  
				  pComm->u.getViewType.iViewType  =  QY_VIEWTYPE_MCROOTLIST;		//  2004/07/12ÔÝ¶¨
				  break;
			default:
					goto  errLabel;
	
	}
	
	lErr  =  QY_RC_WMOK;

errLabel:

	return  lErr;

}


 LRESULT  CQyChildFrm::OnQyPostComm( WPARAM wParam, LPARAM lParam )
{
	int							lErr	=	-1;

	switch  (  wParam  )  {
			case  CONST_qyWmParam_refreshContent:  {
				  CQyMcDoc	*	pDoc  =  (  CQyMcDoc *  )this->GetActiveDocument(  );
				  if  (  !pDoc  )  break;
				  
				  traceLogA(  "docTitle is %S",  pDoc->GetTitle(  )  );
				  
				  pDoc->bRefreshData(  );
				  pDoc->UpdateAllViews(  NULL  );			
				  }
				  break;
			default:
					break;
	}

	return  lErr;
}


