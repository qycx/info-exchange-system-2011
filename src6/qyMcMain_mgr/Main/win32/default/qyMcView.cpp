// qyMcView.cpp : implementation of the CQyMcView class
//

#include	"stdafx.h"
#include	<windowsx.h>
#include	"qyMcMainCommon.h"
#include	"qyCommCommon.h"
#include	"qyMc.h"
#include	"qyMcDoc.h"
#include	"qyMcView.h"
#include	"qyMcMainHint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BOOL  bGetMcRootDisplayCfg(  void  * pMcView,  QY_MC_DISPLAYCFG * pDisplayCfg  );
BOOL  bDisplayMcRootContent(  void  *  pQyMcView,  QY_MC_DISPLAYCFG  * pCfgParam,  QY_MCROOTTREE_SEL  *  pSel  );






/////////////////////////////////////////////////////////////////////////////
// CQyMcView

IMPLEMENT_DYNCREATE(CQyMcView, CListView)

BEGIN_MESSAGE_MAP(CQyMcView, CListView)
	//{{AFX_MSG_MAP(CQyMcView)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_COMMAND(IDC_BTN0, OnBtn0)
	ON_COMMAND(IDC_BTN1, OnBtn1)
	ON_COMMAND(IDC_BTN2, OnBtn2)
	//}}AFX_MSG_MAP
	ON_MESSAGE( QY_WM_COMM, OnQyComm )
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQyMcView construction/destruction

CQyMcView::CQyMcView()
{
	// TODO: add construction code here
	memset( &var, 0, sizeof( var ) );
	
	var.m_nItemSelected  =  -1;

}

CQyMcView::~CQyMcView()
{
}

BOOL CQyMcView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}



/////////////////////////////////////////////////////////////////////////////
// CQyMcView drawing


 void CQyMcView::OnInitialUpdate()
{
	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
	
	int				iErr		=	-1;
	QY_WMBUF_COMM	tmpComm;
	
	if  (  !GetDocument(  )->bDocAvail(  )  )  goto  errLabel;

	this->var.m_hMgrWnd  =  GetParentFrame( )->m_hWnd;

	memset(  &tmpComm,  0,  sizeof(  tmpComm  )  );
	tmpComm.uiType  =  QY_WMPARAM_GETVIEWTYPE;
	if  (  QY_RC_WMOK  !=  ::SendMessage(  this->var.m_hMgrWnd, QY_WM_COMM,  (  UINT  )this->m_hWnd,  (  LONG  )&tmpComm  )  )  goto errLabel;
	this->var.m_displayCfg.m_iViewType  =  tmpComm.u.getViewType.iViewType;
		
	if  ( !bInitialDisplay(  )  )  {
		traceInfo(  0, "[%s]::OnInitialUpdate(  ) -- bInitialDisplay(  ) failed.", qyViewTypeStr(  this->var.m_displayCfg.m_iViewType  )  );
		goto errLabel;
	}
	
	CListView::OnInitialUpdate();

	iErr  =  0;
	
errLabel:

	if  (  iErr  )  {
		::PostMessage(  this->var.m_hMgrWnd,  WM_CLOSE,  0,  0  );
	}

}

  void CQyMcView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{

	traceLogA(  "CQyMcView::OnUpdate(  ): selType is %d.",  var.m_superSel.type  );
	this->bDisplayContent(  &var.m_displayCfg  );
		
}


/////////////////////////////////////////////////////////////////////////////
// CQyMcView printing

BOOL CQyMcView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CQyMcView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CQyMcView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CQyMcView diagnostics

#ifdef _DEBUG
void CQyMcView::AssertValid() const
{
	CListView::AssertValid();
}

void CQyMcView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CQyMcDoc* CQyMcView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CQyMcDoc)));
	return (CQyMcDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CQyMcView message handlers
void CQyMcView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}




 LRESULT  CQyMcView::OnQyComm( WPARAM wParam, LPARAM lParam )
{
	long				lRet				=					-1;
	QY_WMBUF_COMM	*	pComm				=					( QY_WMBUF_COMM * )lParam;
	
	switch  (  pComm->uiType  )  {
			case  QY_WMPARAM_GETDOCINFO:
				  pComm->u.getDocInfo.iDocType	=	GetDocument(  )->m_docStruct.iDocType;
				  break;
			case  CONST_qyWmParam_refreshData:
			case  CONST_qyWmParam_refreshOthers:
				  if  (  GetDocument(  )->m_docStruct.iDocType  ==  CONST_qyDocType_mcView  )  {
					  GetDocument(  )->m_docStruct.u.mcView.curnItem  =	 pComm->u.refreshData.curnRow;
				  }														//  2003/9/5				  
				  bDisplayContent(  &var.m_displayCfg  );
				  break;
			case  QY_WMPARAM_MCPUTROOTDISPLAYDATA:
			case  QY_WMPARAM_ITEMCHANGED:	{
				  QY_WMBUF_PUTDATA	*	p				=		( QY_WMBUF_PUTDATA * )lParam;
				  QY_MC_SEL			*	pCurSel			=		NULL;
		
				  pCurSel  =  ( QY_MC_SEL * )&p->u;
				  if  (  memcmp(  &var.m_superSel,  pCurSel,  sizeof(  pCurSel[0]  )  )  )  {
					  memcpy(  &this->var.m_superSel, pCurSel, sizeof( this->var.m_superSel ) );
				  	  bDisplayContent(  &var.m_displayCfg  );					  
				  }
				  OutputDebugString(  _T(  "CQyMcView(  )::OnQyPutData: here.\n"  )  );
				   }
				  break;
			case  CONST_qyWmParam_getnCol:  {
				  LVCOLUMN	column;
				  int		i;
				  TCHAR		tBuf[256];

				  memset(  &column,  0,  sizeof(  column  )  );
				  column.mask  =  LVCF_TEXT;
				  column.pszText  =  tBuf;
				  column.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );
				  for  (  i  =  0;  ;  i  ++  )  {
					   if  (  !this->GetListCtrl(  ).GetColumn( i,  &column  )  )  {
						   traceLogA(  "居然没有找到列%s，程序有问题",  pComm->u.getnCol.colName  );  goto  errLabel;
					   }
					   if  (  !lstrcmpi(  tBuf,  pComm->u.getnCol.colName  )  )  break;
				  }
				  pComm->u.getnCol.nCol  =  i;
				  }
				  break;
			case  CONST_qyWmParam_focusOnItem:  {
				  if  (  ::SendMessage(  var.m_hMgrWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )pComm  )  !=  CONST_qyWmRc_ok  )  goto  errLabel;
				  
					}
				  break;				  
			default:
					goto  errLabel;
	}

	lRet	=	QY_RC_WMOK;

errLabel:

	return  lRet;

}

 

 BOOL CQyMcView::bGetDisplayCfg(  QY_MC_DISPLAYCFG  *pDisplayCfg  )
{
	 switch  (  pDisplayCfg->m_iViewType  )  {
			 case  QY_VIEWTYPE_MCROOTLIST:
				   return  bGetMcRootDisplayCfg(  this,  pDisplayCfg  );
			 default:
					 break;
	 }

	 traceInfo(  0,  "CQyMcView::bGetDisplayCfg(  ) -- m_iViewType ( %d ) error.",  pDisplayCfg->m_iViewType  );

	 return			FALSE;

}

 void CQyMcView::preInitialDisplay(  )
{
	 
	/*
	 switch  (  this->var.m_displayCfg.m_iViewType  )  {
			   case  QY_VIEWTYPE_MCROOTLIST:
				     this->var.m_displayCfg.m_superSel.type					=		QY_SELTYPE_MCROOTTREE;
					 this->var.m_displayCfg.m_superSel.u.rootTree.bRoot		=		TRUE;		// 这里赋了值使初始显示根描述
					 break;							 
			   case  QY_VIEWTYPE_MCSITERIGHT:
				     this->var.m_displayCfg.m_superSel.type					=		QY_SELTYPE_MCSITELEFT;
					 this->var.m_displayCfg.m_superSel.u.siteLeft.itemId	=		0;
					 break;
			   default:
				   break;
	 }
	 */

	 return;

}

 


 BOOL CQyMcView::bInitialDisplay(  )
{
	BOOL						bRet		=	FALSE;
	CListCtrl				&	ListCtrl	=	GetListCtrl();
	CQyMcDoc				*	pDoc		=	GetDocument( );
	QY_COLUMNINFO			*	pColumns	=	NULL;
	int							nColumns	=	0;
	DWORD						dwStyle		=	0;
	
	
	preInitialDisplay(  );
	if  (  !bGetDisplayCfg(  &this->var.m_displayCfg  )  ) goto errLabel;


	if  (  pDoc->m_docStruct.iDocType  ==  CONST_qyDocType_mcView  )  {	//  2006/12/24
		dwStyle  =  LVS_REPORT  |  LVS_SHOWSELALWAYS;
		if  (  !pDoc->m_docStruct.u.mcView.ucbMultiSel  )  dwStyle  |=  LVS_SINGLESEL;		//  2007/08/24, 准备支持多选
		}
	else  dwStyle  =  LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL;

	ModifyStyle(  LVS_TYPEMASK,  dwStyle  );						//  ModifyStyle( LVS_TYPEMASK, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL );
	ListCtrl.SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE );

	m_LargeImageList.Create( IDB_LARGEICONS, 32, 1, RGB( 255, 255, 255 ) );
	//  m_SmallImageList.Create( IDB_SMALLICONS, 16, 1, RGB( 255, 255, 255 ) );
	m_SmallImageList.Create( IDB_qnmIcons, 16, 1, RGB( 255, 255, 255 ) );
	// m_LargeImageList.SetOverlayImage(  NUM_ITEMS,  1  );
	// m_SmallImageList.SetOverlayImage(  NUM_ITEMS,  1  );
	ListCtrl.SetImageList(  &m_LargeImageList,  LVSIL_NORMAL  );
	ListCtrl.SetImageList(  &m_SmallImageList,  LVSIL_SMALL  );
	
	bRet = TRUE;

errLabel:

	return bRet;

}


 void CQyMcView::delAllColumns(  )
{
	 for ( ; ; )  {
		 if  (  !GetListCtrl(  ).DeleteColumn( 0  )  )  break;
	 }
	 var.m_nCols  =  0;
}








 BOOL CQyMcView::bAddColumns(  QY_COLUMNINFO * pColumns  )
{
	 CQyMcDoc  *  pDoc	=  GetDocument(  );

	 if  (  !pColumns  )  return  TRUE;
	 
	 int		i;
	 LV_COLUMN	lvc;

	 lvc.mask  =  LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	
	 for  (  i  =  0;  pColumns[i].type  !=  -1  &&  pColumns[i].label[0];  i  ++  )  {
		   lvc.iSubItem		=	i;
		   lvc.pszText		=	pColumns[i].label;
		   lvc.cx			=	pColumns[i].width;
		   lvc.fmt			=	pColumns[i].fmt;
		   GetListCtrl(  ).InsertColumn(  var.m_nCols  +  i,  &lvc  );
		   memcpy(  &pDoc->m_docStruct.u.treeList.list.columns[var.m_nCols  +  i],  &pColumns[i],  sizeof(  QY_COLUMNINFO  )  );
	  }
	 var.m_nCols  +=  i;
	 pDoc->m_docStruct.u.treeList.list.columns[var.m_nCols].type  =  -1;
	
	 return  TRUE;
}

 




// 这里：用了TMP_INSERT_AN_ITEM( ), 不能重用，并且应完整的定义同样的变量。
// 注意：pContent指向buf, 故对buf的操作也意味着对pContent的操作。
 BOOL CQyMcView::bDisplayContent( QY_MC_DISPLAYCFG *pCfgParam )
{
	 CQyMcDoc	*	pDoc	=	GetDocument(  );
	 CListCtrl	&	ListCtrl	=	GetListCtrl(  );
	 BOOL			bRet	=	FALSE;
	 int			nItem	=	0;
	 int			cnt;

	 if  (  pDoc->m_docStruct.iDocType  ==  CONST_qyDocType_mcView  )  {	//  2006/12/24
		 if  (  pDoc->m_docStruct.u.mcView.pfDisplayListContent  )  bRet  =  pDoc->m_docStruct.u.mcView.pfDisplayListContent(  this,  pCfgParam,  &pDoc->m_docStruct.u.mcView  );
		
		 cnt  =  this->GetListCtrl( ).GetItemCount(  );						//  2008/01/02
		 if  (  cnt  <  0  )  cnt  =  0;

		 nItem  =  pDoc->m_docStruct.u.mcView.curnItem;
		 if  (  nItem  >=  cnt  )  nItem  =  cnt  -  1;						//  2003/9/5.
		 if  (  nItem  >= 0  )  {
			 ListView_EnsureVisible(  this->m_hWnd, nItem,  FALSE  );
			 ListCtrl.SetItemState(  nItem,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING );
			 ListCtrl.Update(  nItem  );
		 }

		 return  bRet;
	 }

	 if  (  pDoc->m_docStruct.u.treeList.tree.pfDisplayListContent  )  return  (  pDoc->m_docStruct.u.treeList.tree.pfDisplayListContent(  this,  pCfgParam,  &pDoc->m_docStruct.u.treeList.tree  )  ?  FALSE  :  TRUE  );

	 return  bDisplayMcRootContent(  this,  pCfgParam,  &pDoc->m_docStruct.u.treeList.tree  );
}





void CQyMcView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	QY_MC			*	pQyMc		=		QY_GET_GBUF(  );
	CQyMcDoc		*	pDoc		=		GetDocument(  );
	QY_MC_SEL			curSel;
	CListCtrl		&	listCtrl	=		GetListCtrl(  );
	int					iCurItem;
	QY_EVENTINFO		tmpEventInfo;
	PF_commonHandler	pfProcEvent	=		NULL;				//  2006/12/25


	DWORD dwPos = GetMessagePos();

	/* Convert the co-ords into a CPoint structure */
	CPoint point( GET_X_LPARAM( dwPos ), GET_Y_LPARAM( dwPos ) ), spt;
	spt = point;
	
	/* Convert to screen co-ords for hittesting */
	listCtrl.ScreenToClient( &spt );

	UINT test;
	iCurItem = listCtrl.HitTest( spt, &test );
	
	/* Did the click occur on an item */
	if ( iCurItem < 0 || !( test & ( TVHT_ONITEM | TVHT_ONITEMRIGHT ) ) )  goto errLabel;

	memset(  &curSel,  0,  sizeof(  curSel  )  );
	if  (  pDoc->m_docStruct.iDocType  ==  CONST_qyDocType_mcView  )  {
		curSel.type  =  CONST_qySelType_mcView;		
		memcpy(  &curSel.u.mcView,  &pDoc->m_docStruct.u.mcView,  sizeof(  pDoc->m_docStruct.u.mcView  )  );
		//
		pfProcEvent  =  pDoc->m_docStruct.u.mcView.pfProcEvent;
		}
	else  {
		  curSel.type  =  CONST_qySelType_mcRootList;
		  memcpy(  &curSel.u.rootList.leftTreeSel,  &var.m_superSel.u.rootTree,  sizeof(  curSel.u.rootList.leftTreeSel  )  );
		  curSel.u.rootList.leftTreeSel.type  =  pDoc->m_docStruct.u.treeList.tree.type;
		  curSel.u.rootList.leftTreeSel.iDsnIndex  =  pDoc->m_docStruct.u.treeList.tree.iDsnIndex;
		  //
		  pfProcEvent  =  pDoc->m_docStruct.u.treeList.tree.pfProcEvent;
	}

	memset(  &tmpEventInfo,  0,  sizeof(  tmpEventInfo  )  );
	tmpEventInfo.type  =  CONST_qyEventType_rClick;
	tmpEventInfo.hWnd  =  this->m_hWnd;
	tmpEventInfo.click.x  =  point.x;
	tmpEventInfo.click.y  =  point.y;

	if  (  pfProcEvent  )  pfProcEvent(  pQyMc,  &curSel,  &tmpEventInfo  );
		
errLabel:	

	*pResult = 0;

}


void CQyMcView::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW		*	pNMListView =	(NM_LISTVIEW*)pNMHDR;
	CListCtrl		&	listCtrl	=	GetListCtrl(  );
	QY_MC_SEL			sel;
	// TODO: Add your control notification handler code here
		
	if  (  pNMListView->iItem >= 0 
		&&  pNMListView->uNewState  ==  (  LVIS_SELECTED | LVIS_FOCUSED  )  )
	{
		var.m_nItemSelected  =  pNMListView->iItem;

		if  (  this->var.m_displayCfg.m_iViewType  ==  QY_VIEWTYPE_MCSITELEFT  )  {
		
			DWORD  dwData  =  listCtrl.GetItemData(  pNMListView->iItem  );

			memset(  &sel,  0,  sizeof(  sel  )  );
			sel.type			=	QY_SELTYPE_MCSITELEFT;
			sel.u.siteLeft.itemId	=	dwData;

			QY_WMBUF_PUTDATA		tmpPutData;

			memset(  &tmpPutData,  0,  sizeof(  tmpPutData  )  );
			tmpPutData.uiType		=	QY_WMPARAM_ITEMCHANGED;
			memcpy( &tmpPutData.u,  &sel,  sizeof(  sel  )  );
			if  (  QY_RC_WMOK  !=  ::SendMessage(  this->var.m_hMgrWnd, QY_WM_PUTDATA,  ( UINT )this->m_hWnd,  ( LONG )&tmpPutData  )  )  {
				traceInfo(  0, "OnItemchanged:  putdata  failed." );
				goto errLabel;	
			}

			}
		else  {
			traceInfo(  0,  "CQyMcView::OnItemchanged(  ) --- viewType( %d) unsupported.",  this->var.m_displayCfg.m_iViewType  );
		}
		
		}
	else  {
		var.m_nItemSelected  =  -1;
	}

errLabel:

	*pResult = 0;
}

void CQyMcView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	QY_MC			*	pQyMc		=		QY_GET_GBUF(  );
	CQyMcDoc		*	pDoc		=		GetDocument(  );
	QY_MC_SEL			curSel;
	CListCtrl		&	listCtrl	=		GetListCtrl(  );
	int					iCurItem;
	QY_EVENTINFO		tmpEventInfo;
	PF_commonHandler	pfProcEvent	=		NULL;				//  2006/12/25


	DWORD dwPos = GetMessagePos();

	/* Convert the co-ords into a CPoint structure */
	CPoint point( GET_X_LPARAM( dwPos ), GET_Y_LPARAM( dwPos ) ), spt;
	spt = point;
	
	/* Convert to screen co-ords for hittesting */
	listCtrl.ScreenToClient( &spt );

	UINT test;
	iCurItem = listCtrl.HitTest( spt, &test );
	
	/* Did the click occur on an item */
	if ( iCurItem < 0 || !( test & ( TVHT_ONITEM | TVHT_ONITEMRIGHT ) ) )  goto errLabel;
	
	memset(  &curSel,  0,  sizeof(  curSel  )  );
	if  (  pDoc->m_docStruct.iDocType  ==  CONST_qyDocType_mcView  )  {
		curSel.type  =  CONST_qySelType_mcView;		
		memcpy(  &curSel.u.mcView,  &pDoc->m_docStruct.u.mcView,  sizeof(  pDoc->m_docStruct.u.mcView  )  );
		//
		pfProcEvent  =  pDoc->m_docStruct.u.mcView.pfProcEvent;
		}
	else  {
		  curSel.type  =  CONST_qySelType_mcRootList;
		  memcpy(  &curSel.u.rootList.leftTreeSel,  &var.m_superSel.u.rootTree,  sizeof(  curSel.u.rootList.leftTreeSel  )  );
		  curSel.u.rootList.leftTreeSel.type  =  pDoc->m_docStruct.u.treeList.tree.type;
		  curSel.u.rootList.leftTreeSel.iDsnIndex  =  pDoc->m_docStruct.u.treeList.tree.iDsnIndex;
		  //
		  pfProcEvent  =  pDoc->m_docStruct.u.treeList.tree.pfProcEvent;
	}
	
	memset(  &tmpEventInfo,  0,  sizeof(  tmpEventInfo  )  );
	tmpEventInfo.type  =  CONST_qyEventType_dblClick;
	tmpEventInfo.hWnd  =  this->m_hWnd;
	tmpEventInfo.click.x  =  point.x;
	tmpEventInfo.click.y  =  point.y;

	if  (  pfProcEvent  )  pfProcEvent(  pQyMc,  &curSel,  &tmpEventInfo  );
	
errLabel:	
	
	*pResult  =  0;
}

 void CQyMcView::OnBtn0() 
{
	CQyMcDoc	*	pDoc	=	GetDocument(  );
	
	return;
	
}

 void CQyMcView::OnBtn1() 
{
	CQyMcDoc	*	pDoc	=	GetDocument(  );

	traceLogA(  "OnBtn1: selType is %d.",  var.m_superSel.type  );
	
	return;
	
}






void CQyMcView::OnBtn2() 
{
	CQyMcDoc	*	pDoc	=	GetDocument(  );

	traceLogA(  "OnBtn1: selType is %d.",  var.m_superSel.type  );
	
	return;
	
}
