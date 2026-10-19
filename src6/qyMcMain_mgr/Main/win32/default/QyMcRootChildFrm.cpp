// QyMcRootChildFrm.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMaincommon.h"
#include	"qyCommCommon.h"
#include	"qyMc.h"
#include	"qyMcDoc.h"
#include	"qyMcView.h"
// #include "qyMcRootView.h"
#include	"leftView.h"
#include	"QyMcRootChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQyMcRootChildFrm

IMPLEMENT_DYNCREATE(CQyMcRootChildFrm, CMDIChildWnd)

CQyMcRootChildFrm::CQyMcRootChildFrm()
{
	memset( &this->var, 0, sizeof( this->var ) );
	this->var.m_uCfgTimerId = DEFAULT_QY_MC_CHILD_FRM_TIMER_ID;
}

CQyMcRootChildFrm::~CQyMcRootChildFrm()
{
}


BEGIN_MESSAGE_MAP(CQyMcRootChildFrm, CMDIChildWnd)
	//{{AFX_MSG_MAP(CQyMcRootChildFrm)
	ON_UPDATE_COMMAND_UI(ID_WINDOW_NEW, OnUpdateWindowNew)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, OnUpdateFileSaveAs)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_MESSAGE( QY_WM_COMM, OnQyComm )
	ON_MESSAGE( QY_WM_PUTDATA, OnQyPutData )	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQyMcRootChildFrm message handlers

 QY_DMITEM  CONST_wmBufTypeTable[]  = 
{	
	{	QY_WMPARAM_MCPUTROOTDISPLAYDATA,		_T(  "QY_WM_PUTDATA送rootList的显示参数"  ),					},
	{	QY_WMPARAM_GETVIEWTYPE,					_T(  "QY_WM_COMM 取iViewType "  ),								},
	{	QY_WMPARAM_GETDOCINFO,					_T(  "QY_WM_COMM要求取得docInfo"  ),							},
	{	QY_WMPARAM_TELLDOCINFO,					_T(  "QY_WM_COMM要求告知docInfo"  ),							},
	{	QY_WMPARAM_UPDATEBAR,					_T(  "QY_WM_COMM要求更新工具栏显示"  ),							},
	{	QY_WMPARAM_ITEMCHANGED,					_T(  "QY_WM_COMM要求相关视跟着刷新"  ),							},
	{	QY_WMPARAM_PREPARETOCLOSE,				_T(  "QY_WM_COMM要求子窗口退出"  ),								},
	{	QY_WMPARAM_NEWWEBBROWSER,				_T(  "QY_WM_COMM要求建立一新的浏览窗口"  ),						},
	{	CONST_qyWmParam_refreshData,			_T(  "QY_WM_COMM要求刷新文档"  ),								},
	{	CONST_qyWmParam_getnCol,				_T(  "QY_WM_COMM从CQyVirtualListView中根据列名取列位置"  ),		},
	{	CONST_qyWmParam_chkPage,				_T(  "QY_WM_COMM从ActivePage中校验数据"  ),						},
	{	CONST_qyWmParam_export,					_T(  "export"  ),												},
	{	CONST_qyWmParam_show,					_T(  "show"  ),													},
	{	CONST_qyWmParam_addIp,					_T(  "添加IP"  ),												},
	{	CONST_qyWmParam_getIdcInfo,				_T(  "取与控件关联的信息"  ),									},
	{	CONST_qyWmParam_getSelInfo,				_T(  "读取被选中的项内容和其他信息"  ),							},
	{	CONST_qyWmParam_refreshTvItem,			_T(  "刷新树窗口节点"  ),										},
	{	CONST_qyWmParam_refreshOthers,			_T(  "刷新另一窗口"  ),											},
	{	CONST_qyWmParam_delItem,				_T(  "删除一节点"  ),											},
	{	CONST_qyWmParam_showSecChkEvent,		_T(  "显示检查事件"  ),											},
	{	CONST_qyWmParam_setFocusOnRightView,	_T(  "将聚焦右边视图"  ),										},
	{	CONST_qyWmParam_focusOnItem,			_T(  "将聚焦某节点"  ),											},
	{	CONST_qyWmParam_focusOnItem1,			_T(  "将聚焦某节点, 从rightView发起，由frame来存储此数据包，返回对rightView的控制，然后通过此数据包来接着让leftView执行变焦工作"  ),	},
	{	CONST_qyWmParam_getDropTarget,			_T(  "发给控件的父窗口，取相关控件的dropTarget"  ),				},
	//
	//  以下参数主要用来在CONST_qyWm_postComm的wParam参数
	{	CONST_qyWmParam_setActiveWindow,		_T(  "激活窗口, lParam为将激活的窗口句柄"  ),					},
	{	CONST_qyWmParam_idcInited,				_T(  "发给父窗口表明idc已初始化完成, lParam表idc的句柄"  ),		},
	{	CONST_qyWmParam_msgArrive,				_T(  "发给gui表明有消息到达了"  ),								},
	//
	{	-1,					},
};
	
 LRESULT CQyMcRootChildFrm::OnQyComm( WPARAM wParam, LPARAM lParam )
{
	int								lErr			=			-1;
	QY_MC				*			pQyMc			=			QY_GET_GBUF( );
	QY_WMBUF_COMM		*			pComm			=			( QY_WMBUF_COMM * )lParam;
	
	traceLogA(  "CQyMcRootChildFrm::OnQyComm enters, %S",  qyGetDesByType1(  CONST_wmBufTypeTable,  pComm->uiType  )  );
	
	switch  (  pComm->uiType  )  {
			case  QY_WMPARAM_GETVIEWTYPE:
				  if  (  (  HWND  )wParam  ==  this->getLeftView(  )->m_hWnd  )  pComm->u.getViewType.iViewType  =  this->var.mgrLeft.iViewType;
				  else  if  (  (  HWND  )wParam  ==  this->getRightView(  )->m_hWnd  )  pComm->u.getViewType.iViewType  =  this->var.mgrRight.iViewType;
				  else  goto errLabel;
				  break;
			case  QY_WMPARAM_MCPUTROOTDISPLAYDATA:
				  if  (  wParam  ==  (  UINT  )this->getLeftView(  )->m_hWnd  )  this->getQyMcView(  )->SendMessage(  CONST_qyWm_comm,  wParam,  lParam  );
				  break;
			case  CONST_qyWmParam_refreshOthers:
				  if  (  pComm->hWndSrc  ==  getLeftView(  )->m_hWnd  )  getRightView(  )->SendMessage(  CONST_qyWm_comm,  wParam,  lParam  );
				  else  if  (  pComm->hWndSrc  ==  getRightView(  )->m_hWnd  )  getLeftView(  )->SendMessage(  CONST_qyWm_comm,  wParam,  lParam  );
				  break;
			case  CONST_qyWmParam_setFocusOnRightView:
				  getRightView(  )->SetFocus(  );
				  break;
			case  CONST_qyWmParam_focusOnItem:
				  memcpy(  &var.wmBuf,  (  char  *  )lParam,  sizeof(  var.wmBuf  )  );
				  var.wmBuf.uiType  =  CONST_qyWmParam_focusOnItem1;
				  PostMessage(  CONST_qyWm_comm,  wParam,  (  LPARAM  )&var.wmBuf  );
				  //  if  (  getLeftView(  )->SendMessage(  CONST_qyWm_comm,  wParam,  lParam  )  !=  CONST_qyWmRc_ok  )  goto  errLabel;
				  break;
			case  CONST_qyWmParam_focusOnItem1:
				  pComm->uiType  =  CONST_qyWmParam_focusOnItem;
  				  if  (  getLeftView(  )->SendMessage(  CONST_qyWm_comm,  wParam,  lParam  )  !=  CONST_qyWmRc_ok  )  goto  errLabel;
				  break;
			default:
					goto  errLabel;
	
	}
	
	lErr  =  QY_RC_WMOK;

errLabel:

	return  lErr;

}


 LRESULT CQyMcRootChildFrm::OnQyPutData( WPARAM wParam, LPARAM lParam )
{
	 traceLogA(  "CQyMcRootChildFrm::OnQyPutData enters"  );

	 MACRO_qyAssert(  0,  _T(  "OnQyPutData应改为从CONST_qyWm_comm入手"  )  );

	 if ( wParam == ( UINT )this->getLeftView( )->m_hWnd ) {
		 return this->getQyMcView( )->SendMessage( QY_WM_PUTDATA, wParam, lParam );
	 }
	 return -1;
}
 


CQyMcView *CQyMcRootChildFrm::GetRightPane( )
{
	 CQyMcView *pView = DYNAMIC_DOWNCAST( CQyMcView, m_wndSplitter.GetPane( 0, 1 ) );
	 ASSERT( pView );
	 
	 return pView;


}


CQyMcView *CQyMcRootChildFrm::getQyMcView( )
{
	 CQyMcView *pView = DYNAMIC_DOWNCAST( CQyMcView, m_wndSplitter.GetPane( 0, 1 ) );
	 ASSERT( pView );
	 
	 return pView;
}
	
CLeftView *CQyMcRootChildFrm::getLeftView( )
{
	 CLeftView *pView = DYNAMIC_DOWNCAST( CLeftView, m_wndSplitter.GetPane( 0, 0 ) );
	 ASSERT( pView );
	 
	 return pView;

}

 CQyMcView  *  CQyMcRootChildFrm::getRightView(  )
{
	 CQyMcView *pView = DYNAMIC_DOWNCAST( CQyMcView, m_wndSplitter.GetPane( 0, 1 ) );
	 ASSERT( pView );
	 
	 return pView;

}




 
 BOOL CQyMcRootChildFrm::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	this->var.mgrLeft.iViewType			=		QY_VIEWTYPE_MCROOTTREE;
	this->var.mgrRight.iViewType		=		QY_VIEWTYPE_MCROOTLIST;
	

	// create splitter window
	if ( !m_wndSplitter.CreateStatic( this, 1, 2, WS_CHILD | WS_VISIBLE ) )
		return FALSE;
	
	//增加两个视图，并调整视图大小 
	if ( !m_wndSplitter.CreateView( 0, 0, pContext->m_pNewViewClass,
		CSize( 100, 175 ), pContext ) )
	{ 
		TRACE0( "Failed to create second pane\n" );
		return FALSE; 
	} 

	if ( !m_wndSplitter.CreateView( 0, 1, RUNTIME_CLASS( CQyMcView ), 
		CSize( 0, 0 ),pContext ) )
	{ 
		TRACE0( "Failed to create third pane\n" );
		return FALSE; 
	}
	// pContext->m_pCurrentDoc->AddView(  GetRightView( )  );
		
	SetActiveView( getLeftView( ) );

	int cyCur, cyMin;

	m_wndSplitter.GetColumnInfo( 0, cyCur,	cyMin );
	m_wndSplitter.GetColumnInfo( 1, cyCur,	cyMin );
	m_wndSplitter.SetColumnInfo( 0, 210,	0 );
	//  m_wndSplitter.SetColumnInfo( 1, 180, 0 );
	
//  errLabel:

	return TRUE;
	
}


BOOL CQyMcRootChildFrm::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class

	cs.style &= ~( FWS_ADDTOTITLE | FWS_PREFIXTITLE );
	return CMDIChildWnd::PreCreateWindow(cs);

}


void CQyMcRootChildFrm::OnUpdateWindowNew(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( 0 );
}

void CQyMcRootChildFrm::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( 0 );
}

void CQyMcRootChildFrm::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable( 0 );
}


// 这里的程序很不好，反复测m_bTo
 void CQyMcRootChildFrm::OnTimer(UINT_PTR nIDEvent) 
{
	 
	 debugLog( "CQyMcRootChildFrm::OnTimer(  ) enters." );
	 traceInfo(  0,  "CQyMcRootChildFrm::OnTimer(  ) enters."  );
	
	 if ( this->var.m_uTimerId != nIDEvent || !this->var.m_uTimerId ) {
		 qyDebugHint(  _T(  "Error: m_uTimerId is not equal to nIDEvent." )  );
		 return;
	 }
	 
	return;

}



BOOL CQyMcRootChildFrm::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CMDIFrameWnd* pParentWnd, CCreateContext* pContext) 
{
	QY_MC	*	pQyMc  =  QY_GET_GBUF(  );
	m_hMenuShared  =  pQyMc->gui.hMenuChildFrm;
	
	return CMDIChildWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, pContext);
}
