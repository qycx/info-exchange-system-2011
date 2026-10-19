// LeftView.cpp : implementation of the CLeftView class
//

#include	"stdafx.h"
#include	<windowsx.h>
#include	"qyMcMainCommon.h"
#include	"qyCommCommon.h"
#include	"qyMc.h"
#include	"qyMcDoc.h"
#include	"LeftView.h"
#include	"qyCusResTemp.h"
#include	"myDb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_MESSAGE(  QY_WM_COMM,  OnQyComm  )
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction




CLeftView::CLeftView()
{
	// TODO: add construction code here
	m_TreeCtrl  =  NULL;
	memset(  &m_var,  0,  sizeof(  m_var  )  );

}

CLeftView::~CLeftView()
{
}


CWnd * CLeftView::getMgrWnd( )
{	
	return ( CWnd * )GetParentFrame(  );
}


 int  tmpHandler_bRefreshContactsStatus_leftView(  void  *  pElemParam,  void  *  pMemParam,  void  *  pLeftViewParam  )
{
	 int								iErr							=	-1;
	 DISPLAYEDELEM_U				*	pElem							=	(  DISPLAYEDELEM_U  *  )pElemParam;
	 REFRESH_RECENTFRIEND_RESP		*	pMem							=	(  REFRESH_RECENTFRIEND_RESP  *  )pMemParam;
	 CLeftView						*	pLeftView						=	(  CLeftView  *  )pLeftViewParam;
	 //
	 QY_MC							*	pQyMc							=	QY_GET_GBUF(  );
	 //
	 TCHAR								tBuf[256]						=	_T(  ""  );
	 TCHAR								displayName[256  +  1]			=	_T(  ""  );	
	 int								nImage,  nSelectedImage;
	 //
	 HANDLE								hTreeItem						=	NULL;;

	 switch  (  pElem->uiType  )  {
			 case  CONST_displayedElemType_messengerTree:
				   hTreeItem  =  (  HTREEITEM  )pElem->messengerTree.hItem;
				   break;
			 case  CONST_displayedElemType_meTree:
				   hTreeItem  =  (  HTREEITEM  )pElem->meTree.hItem;
				   break;
			 default:	
					goto  errLabel;
	 }


	 //  只刷新展开节点
	 TVITEM								tvItem;
			 
	 tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
	 tvItem.hItem  =  (  HTREEITEM  )hTreeItem;
	 tvItem.pszText  =  tBuf;
	 tvItem.cchTextMax  =  mycountof(  tBuf  );
	 if  (  !pLeftView->m_TreeCtrl->GetItem(  &tvItem  )  )  {
		 traceLogA(  "bRefreshFriendsStatus_leftView: GetItem failed, 可能是此节点已经被删除了"  );
		 iErr  =  0;  goto  errLabel;				  
	 }

	 switch  (  pElem->uiType  )  {
			 case  CONST_displayedElemType_meTree:  {
				    MIS_CNT						*	pMisCnt					=	(  MIS_CNT  *  )pElem->meTree.pMisCnt;

					_sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s(%I64u)"  ),  pMisCnt->displayName,  pMisCnt->idInfo.ui64Id  );
					if  (  pMisCnt->taskStat.uiCnt_unprocedTasks  )  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s - %s %d"  ),  displayName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_unfinished  ),  pMisCnt->taskStat.uiCnt_unprocedTasks  );
					if  (  pMisCnt->taskStat.uiCnt_processingTasks  )  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s - %s %d"  ),  displayName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_beingProcessed  ),  pMisCnt->taskStat.uiCnt_processingTasks  );
					if  (  pMisCnt->taskStat.uiCnt_processBreakTasks  )  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s - %s %d"  ),  displayName,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_interrupted  ),  pMisCnt->taskStat.uiCnt_processBreakTasks  );
					//
					getMessengerImages(  pQyMc,  pMisCnt->status.usRunningStatus,  &nImage,  &nSelectedImage  );
					}
					break;
			 case  CONST_displayedElemType_messengerTree:
			 default:
				     lstrcpyn(  displayName,  tBuf,  mycountof(  tBuf  )  );  //  这里故意让displayName指向tBuf, 是因为这里暂时只需要变化图标
					 //
					 getMessengerImages(  pQyMc,  pMem->usRunningStatus,  &nImage,  &nSelectedImage  );
					 //
				     break;					
	 }
	
				
	 if  (  _tcsicmp(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  displayName  );
		 tvItem.iImage  =  nImage;
		 tvItem.iSelectedImage  =  nSelectedImage;
		 pLeftView->m_TreeCtrl->SetItem(  &tvItem  );
	 }

	 iErr  =  0;

errLabel:
	 return  iErr;
 }


 LRESULT CLeftView::OnQyComm(  WPARAM  wParam,  LPARAM  lParam  )
{
	 LONG				lRet	=	-1;
	 QY_WMBUF_COMM	*	pComm	=	(  QY_WMBUF_COMM  *  )lParam;
	 QY_MC			*	pQyMc	=	QY_GET_GBUF(  );
	 CQyMcDoc		*	pDoc	=	GetDocument(  );

	 traceLogA(  "CLeftView::OnQyComm: enters"  );

	 switch  (  pComm->uiType  )  {
			 case  QY_WMPARAM_GETDOCINFO:
				   pComm->u.getDocInfo.iDocType	=	GetDocument(  )->m_docStruct.iDocType;
				   break;
			 case  CONST_qyWmParam_refreshData:  
			 case  CONST_qyWmParam_refreshTvItem:  {
				   QY_WMBUF_COMM	wmBuf;

				   bDisplayContent(  );
				   memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
				   wmBuf.uiType  =  CONST_qyWmParam_refreshOthers;
				   wmBuf.hWndSrc  =  this->m_hWnd;
				   getMgrWnd(  )->SendMessage(  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
					}
				   break;
			 case  CONST_qyWmParam_delItem:			{
				   QY_MC_DOCSTRUCT		*	pDocStruct	=	&GetDocument(  )->m_docStruct;
				   QY_WMBUF_PROCTV		*	pProcTv  =  (  QY_WMBUF_PROCTV  *  )pComm;
				   QY_MC_SEL				curSel;
				   QY_WMBUF_PUTDATA			tmpPutData;
				   HTREEITEM				htItemWillFocusOn;
					 
				   if  (  pProcTv->hItem  ==  m_var.htMyRootItem  )  {
					   traceLogA(  "错误：试图删除跟节点"  );  goto  errLabel;
				   }
				   if  (  !(  htItemWillFocusOn  =  m_TreeCtrl->GetParentItem(  (  HTREEITEM  )pProcTv->hItem  )  )  )  goto  errLabel;

				   this->m_TreeCtrl->DeleteItem(  (  HTREEITEM  )pProcTv->hItem  );

				   m_TreeCtrl->SelectItem(  htItemWillFocusOn  );

				   #ifdef	__DEBUG__
							showItem(  htItemWillFocusOn  );
				   #endif

				   bRefreshItem(  htItemWillFocusOn  );
				   
				   memset( &curSel, 0, sizeof( curSel ) );
				   curSel.type  =  QY_SELTYPE_MCROOTTREE;
				   curSel.u.rootTree.type	=  pDocStruct->u.treeList.tree.type;
				   if  (  !(  curSel.u.rootTree.bRoot  =  (  htItemWillFocusOn  ==  m_var.htMyRootItem  )  )  )  {
					   curSel.u.rootTree.hItem  =  htItemWillFocusOn;
				   	   curSel.u.rootTree.iHelpId  =  m_TreeCtrl->GetItemData(  htItemWillFocusOn  );
				   }
				   if  (  pDoc->m_docStruct.u.treeList.tree.pfProcTreeSel  )  pDoc->m_docStruct.u.treeList.tree.pfProcTreeSel(  pQyMc,  &curSel,  0  );
					
				   memset(  &tmpPutData,  0,  sizeof(  tmpPutData  )  );
				   tmpPutData.uiType  =  QY_WMPARAM_MCPUTROOTDISPLAYDATA;
				   MACRO_qyAssert(  sizeof(  tmpPutData.u  )  >=  sizeof(  curSel  ),  _T(  "wmBuf to put data is too small."  )  );
				   memcpy(  &tmpPutData.u,	 &curSel,  sizeof(  curSel  )  );
				   getMgrWnd(  )->SendMessage(  CONST_qyWm_comm,  (  WPARAM  )this->m_hWnd,  (  LPARAM  )&tmpPutData  );
				   						 
					}
				   break;
			 case  CONST_qyWmParam_refreshOthers:
				   bDisplayContent(  );
				   break;	
			 case  CONST_qyWmParam_focusOnItem:		{
				   QY_WMBUF_FOCUSONITEM		*	pFocusOnItem	=	(  QY_WMBUF_FOCUSONITEM  *  )pComm;
				   HTREEITEM					htItem			=	NULL;
				   if  (  !pFocusOnItem->bRoot  &&  !bRefreshItem(  (  HTREEITEM  )pFocusOnItem->htItem  )  )  goto  errLabel;
				   htItem  =  pFocusOnItem->bRoot  ?  m_var.htMyRootItem  :  (  HTREEITEM  )pFocusOnItem->htItem;
				   if  (  !m_TreeCtrl->ItemHasChildren(  htItem  )  )  break;
				   if  (  !(  htItem  =  FindItem(  CString(  pFocusOnItem->name  ),  FALSE,  TRUE,  TRUE,  htItem  )  )  )  goto  errLabel;

				   this->m_TreeCtrl->SelectItem(  htItem  );
				   //  showItem(  (  HTREEITEM  )htItem  );
				   
					}
				   break;	
			 case  CONST_misMsgType_refreshContactsStatus_qmc:  {
				   MIS_MSG_REFRESHCONTACTSSTATUS_QMC  *  pMsg  =  (  MIS_MSG_REFRESHCONTACTSSTATUS_QMC  *  )pComm;
				   //
				   bRefreshContactsStatus_wnd(  pMsg,  &this->m_var.displayCtx,  tmpHandler_bRefreshContactsStatus_leftView,  this  ); 
				   
				   }
				   break;
			 case  CONST_misMsgType_refreshMeStatus_qmc:  {
				   MIS_MSG_REFRESHMESTATUS_QMC  *  pMsg  =  (  MIS_MSG_REFRESHMESTATUS_QMC  *  )pComm;
				   //
				   bRefreshMeStatus_wnd(  pMsg,  &this->m_var.displayCtx,  tmpHandler_bRefreshContactsStatus_leftView,  this  );				

				   }
				   break;
			 default:
					 goto  errLabel;
	 }

	 lRet  =  QY_RC_WMOK;

errLabel:
	 
	 return  lRet;

}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing



void CLeftView::OnDraw(CDC* pDC)
{
	CQyMcDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	//  cs.style |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_SHOWSELALWAYS;
	cs.style |= TVS_HASBUTTONS | TVS_HASLINES | TVS_SHOWSELALWAYS;
	return CTreeView::PreCreateWindow(cs);
}


/////////////////////////////////////////////////////////////////////////////
// CLeftView printing

BOOL CLeftView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLeftView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLeftView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CLeftView::OnInitialUpdate()
{
	QY_MC		*	pQyMc	=	QY_GET_GBUF(  );
	CQyMcDoc	*	pDoc  =  GetDocument(  );
	
	if  (  !this->bInitialDisplay(  )  )  {
		getMgrWnd(  )->PostMessage(  WM_CLOSE  );  return;
	}	


	CTreeView::OnInitialUpdate();

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().

	m_TreeCtrl->Expand(  this->m_var.htMyRootItem,  TVE_EXPAND  );

	if  (  m_var.htInitialItem  &&  m_var.htInitialItem  !=  m_var.htMyRootItem  )  {
		m_TreeCtrl->SetItemState(  m_var.htInitialItem,  TVIS_SELECTED,  TVIS_SELECTED  );
		m_TreeCtrl->SetItemText(  m_var.htMyRootItem,  CString(  "Related"  )  );
	}  
	
	QY_MC_SEL		curSel;

	memset( &curSel, 0, sizeof( curSel ) );
	curSel.type  =  QY_SELTYPE_MCROOTTREE;
	curSel.u.rootTree.type  =  pDoc->m_docStruct.u.treeList.tree.type;
	curSel.u.rootTree.iDsnIndex  =  pDoc->m_docStruct.u.treeList.tree.iDsnIndex;	//  2007/01/02
	
	if  (  !m_var.htInitialItem  )  curSel.u.rootTree.bRoot  =  TRUE;	
	else  {
		  curSel.u.rootTree.iHelpId  =  m_TreeCtrl->GetItemData(  m_var.htInitialItem  );
		  _snprintf(  curSel.u.rootTree.selectedMac,  sizeof(  curSel.u.rootTree.selectedMac  ),  "%s",  pDoc->m_docStruct.u.treeList.tree.selectedMac  );
	}
	if  (  pDoc->m_docStruct.u.treeList.tree.pfProcTreeSel  )  pDoc->m_docStruct.u.treeList.tree.pfProcTreeSel(  pQyMc,  &curSel,  0  );
		
	QY_WMBUF_PUTDATA  tmpPutData;

	memset(  &tmpPutData,  0,  sizeof(  tmpPutData  )  );
	tmpPutData.uiType  =  QY_WMPARAM_MCPUTROOTDISPLAYDATA;
	MACRO_qyAssert(  sizeof(  tmpPutData.u  )  >=  sizeof(  curSel  ),  _T(  "wmBuf to put data is too small."  )  );
	memcpy(  &tmpPutData.u,	 &curSel,  sizeof(  curSel  )  );

	getMgrWnd(  )->SendMessage(  CONST_qyWm_comm,  (  WPARAM  )this->m_hWnd,  (  LPARAM  )&tmpPutData  );
	
}


 void CLeftView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	traceLogA(  "CLeftView::OnUpdate called"  );
	
	this->bDisplayContent(  );

	
}


/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CQyMcDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CQyMcDoc)));
	return (CQyMcDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers


#ifdef  __DEBUG__
 void  CLeftView::showItem(  HTREEITEM  htItem  )
{
	 CString	str;
	 DWORD		dwData;

	 if  (  htItem  )  {
		 
		 str  =  m_TreeCtrl->GetItemText(  htItem  );
		 dwData  =  m_TreeCtrl->GetItemData(  htItem  );

		 traceLogA(  "该节点 %s, 数据 %d",  str.GetBuffer(  0  ),  dwData  );
	 }
}
#endif


 int CLeftView::bInitialDisplay( )
{
	 BOOL				bRet				=				FALSE;
 	 QY_MC		*		pQyMc				=				QY_GET_GBUF( );
	 //  unsigned  int		len;
	 CQyMcDoc	*		pDoc				=				GetDocument(  );


	 //

	 /*
	 if  (  pQyMc->cfg.usMaxDisplayedElemsPerWnd  &&  getDisplayQ(  pQyMc,  0,  0  )  )  {
		 if  (  initGenericQ(  _T(  "leftViewObjQ"  ),  0,  0,  pQyMc->cfg.usMaxDisplayedElemsPerWnd,  malloc,  free,  &this->m_var.displayCtx.displayedElemQ  )  )  goto  errLabel;
		 m_var.displayCtx.bQInited  =  TRUE;
		 //
		 len  =  pQyMc->cfg.usMaxDisplayedElemsPerWnd  *  sizeof(  void  *  );
		 //
		 //  m_var.ppSorted_byHandle  =  (  void  **  )malloc(  len  );
		 //  if  (  !m_var.ppSorted_byHandle  )  goto  errLabel;
		 //  memset(  m_var.ppSorted_byHandle,  0,  len  );
		 //
		 m_var.displayCtx.ppDisplayedElems_sortedByKey  =  (  void  **  )malloc(  len  );
		 if  (  !m_var.displayCtx.ppDisplayedElems_sortedByKey  )  goto  errLabel;
		 memset(  m_var.displayCtx.ppDisplayedElems_sortedByKey,  0,  len  );

		 //
		 MIS_MSG_DISPLAYEDELEM_QMC	msg;
		 memset(  &msg,  0,  sizeof(  msg  )  );
		 msg.uiType  =  CONST_misMsgType_displayedElem_qmc;
		 msg.elemU.wndInfo.uiType  =  CONST_displayedElemType_wndInfo;
		 msg.elemU.wndInfo.hWnd  =  this->m_hWnd;
		 lstrcpyn(  msg.elemU.wndInfo.wndName, pDoc->m_docStruct.docName,  mycountof(  msg.elemU.wndInfo.wndName  )  );
		 if  (  qPostMsg(  &msg,  sizeof(  msg  ),  getDisplayQ(  pQyMc,  0,  0  )  )  )  goto  errLabel;

	 }
	 */
	 if  (  initMcCtxDisplayedWnd(  this->m_hWnd,  pDoc->m_docStruct.docName,  &m_var.displayCtx  )  )  goto  errLabel;
	 m_var.bDisplayCtxInited  =  TRUE;


	 //
	 m_TreeCtrl  =  &GetTreeCtrl(  );

	 // Create the image list for the tree control
	 //  m_ImageList.Create(  IDB_qnmIcons,  16,  1,  RGB(  0,  255,  0  )  );
	 m_ImageList.Create(  IDB_qnmIcons,  16,  1,  0  );		//  2003/10/21修改
	 m_TreeCtrl->SetImageList(  &m_ImageList,  TVSIL_NORMAL  );

	 this->m_var.htMyRootItem  =  m_TreeCtrl->InsertItem(  CString(  pQyMc->cfg.name  )  );
	 m_TreeCtrl->SetItemState(  this->m_var.htMyRootItem,  TVIS_BOLD,  TVIS_BOLD  );
	 this->m_var.bInitialized  =  TRUE;

	 bRet  =  TRUE;
errLabel:
	 if  (  !bRet  )  {
		 /*
		 //  if  (  m_var.ppSorted_byHandle  )  {
		 //	     free(  m_var.ppSorted_byHandle  );  m_var.ppSorted_byHandle  =  NULL;
		 //  }
		 if  (  m_var.displayCtx.ppDisplayedElems_sortedByKey  )  {
			 free(  m_var.displayCtx.ppDisplayedElems_sortedByKey  );  m_var.displayCtx.ppDisplayedElems_sortedByKey  =  NULL;
		 }
		 if  (  m_var.displayCtx.bQInited  )  {
			 exitGenericQ(  &m_var.displayCtx.displayedElemQ  );  m_var.displayCtx.bQInited  =  FALSE;
		 }
		 */
		 if  (  m_var.bDisplayCtxInited  )  {
			 exitMcCtxDisplayedWnd(  this->m_hWnd,  &m_var.displayCtx  );  m_var.bDisplayCtxInited  =  FALSE;
		 }
	 }

	 return  bRet;

}



 BOOL  CLeftView::bDisplayContent(  )
{
	 BOOL					bRet				=				FALSE;
	 QY_MC				*	pQyMc				=				QY_GET_GBUF(  );
	 CQyMcDoc			*	pDoc				=				GetDocument(  );
	 if  (  pDoc->m_docStruct.iDocType  !=  CONST_qyDocType_mcRootTree  )  return  FALSE;
	 QY_OBJ_DB			*	pObjDb				=				getProcedObjDb(  0,  pDoc->m_docStruct.u.treeList.tree.iDsnIndex  );
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;
	 //
	 CRecordset				rs( ( CDatabase * )pObjDb->pDb );
	 CDBVariant				varVals[20];
	 int					index, nFields;
	 // CODBCFieldInfo		tmpFieldInfo;
	 QY_SNMPOBJ_HEAD		snmpObj;
	 QY_SNMPOBJ_HEAD	*	pObj				=				&snmpObj;
	 TCHAR					sqlBuf[QY_SQLBUFLEN  +  1];
	 HTREEITEM				tmphtItem			=				NULL;
	 TCHAR					displayName[512]	=				_T(  ""  );		
	 int					iObjId				=				0;
	 int					nImage,  nSelectedImage;
	 TCHAR				*	pStopString;
	 char					buf[256];
	 TCHAR					tBuf[256];

	 CWaitCursor			cursor;

	 //  2004/07/26增加了对显示的重定义
	 if  (  pDoc->m_docStruct.u.treeList.tree.pfDisplayContent  )  return  (  pDoc->m_docStruct.u.treeList.tree.pfDisplayContent(  this,  0,  0  )  ?  FALSE  :  TRUE  );

	 if  (  !this->m_var.bInitialized  ||  !this->m_var.htMyRootItem  )  goto  errLabel;

	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select iIpForwarding,ucbBridge,ucbHost,sysDescr,iMaker,maker,productName,lNetDevType,ip,mac,dot1dBaseNumPorts,lStatus,cusName,place,auditTime from qySnmpObjTab %s %s order by ip"  ),  pDoc->m_docStruct.u.treeList.tree.wherePart[0]  ?  _T(  "where"  )  :  _T(  ""  ),  CString(  pDoc->m_docStruct.u.treeList.tree.wherePart  )  );

	 try  {		
		  if  (  !rs.Open( CRecordset::forwardOnly,  sqlBuf  )  )  {
		 	  debugLog(  "rs open() failed."  );
			  goto  errLabel;
		  }
	  	
		  nFields  =  rs.GetODBCFieldCount(  );
		  //  rs.GetODBCFieldInfo(  index,  tmpFieldInfo  );
		  for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {
		
			   for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   
			   memset(  pObj,  0,  sizeof(  pObj[0]  )  ); 
					   			   
			   index  =  0;		//  iIpForwarding
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  pObj->iIpForwarding  =  _tcstol(  tBuf,  &pStopString,  10  );    
	 		   index  ++  ;		//  ucbBridge
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  pObj->ucbBridge  =  (  unsigned  char  )_tcstol(  tBuf,  &pStopString,  10  );    
	 		   index  ++  ;		//  ucbHost
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  pObj->ucbHost  =  (  unsigned  char  )_tcstol(  tBuf,  &pStopString,  10  );    
	 		   index  ++  ;		//  sysDescr	 
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  pObj->sysDescr,  tBuf,  mycountof(  pObj->sysDescr  )  );    
	 		   index  ++  ;		//  iMaker,
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  pObj->iMaker  =  _tcstol(  tBuf,  &pStopString,  10  );    
	 		   index  ++  ;		//  maker,
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  pObj->maker,  tBuf,  mycountof(  pObj->maker  )  );    
	 		   index  ++  ;		//  productName,
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  pObj->productName,  tBuf,  mycountof(  pObj->productName  )  );    
	 		   index  ++  ;		//  lNetDevType,
	 		   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pObj->lNetDevType  =  varVals[index].m_lVal;      }
	 		   index  ++  ;		//  ip,
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );  qyIp12ToStd(  buf,  pObj->ip  );    
	 		   index  ++  ;		//  mac,
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pObj->mac,  sizeof(  pObj->mac  )  );    
	 		   index  ++  ;		//  dot1dBaseNumPorts
	 		   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pObj->uiIfNumber  =  varVals[index].m_lVal;    }
	 		   index  ++  ;		//  lStatus
	 		   if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  pObj->lStatus  =  varVals[index].m_lVal;    }
	 		   index  ++  ;		//  cusName
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  pObj->cusName,  tBuf,  mycountof(  pObj->cusName  )  );	
	 		   index  ++  ;		//  place
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  pObj->place,  tBuf,  mycountof(  pObj->place  )  );	
	 		   index  ++  ;		//  auditTime
			   MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pObj->auditTime,  sizeof(  pObj->auditTime  )  );	
	 		   index  ++  ;		
			   
	 
			   iObjId  =  getObjId(  pObjDb,  0,  NULL,CONST_objType_qySwitch,  &snmpObj  );
			   if  (  iObjId  <  0  )  continue;

			   if  (  snmpObj.cusName[0]  )  lstrcpyn(  displayName,  snmpObj.cusName,  mycountof(  displayName  )  );
			   else  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%s ( %s )"  ),  snmpObj.productName,  CString(  snmpObj.ip  )  );
			   getSnmpObjImages(  pQyMc,  pObj,  &nImage,  &nSelectedImage  );

			   if  (  !(  tmphtItem  =  this->FindItemData(  iObjId,  TRUE,  this->m_var.htMyRootItem  )  )  )  {
				   tmphtItem  =  m_TreeCtrl->InsertItem(  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE  |  TVIF_PARAM,  
														  CString(  displayName  ),  
														  nImage,  
														  nSelectedImage,  
														  TVIS_EXPANDPARTIAL,  
														  TVIS_STATEIMAGEMASK, 
														  iObjId,  
														  this->m_var.htMyRootItem,  
														  TVI_LAST  );
				   m_TreeCtrl->SortChildren(  m_var.htMyRootItem  );
				   
				   }
			   else  {				  
				     //  只刷新展开节点
					 TVITEM				tvItem;
					 //  char				tmpBuf[512];

					 tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
					 tvItem.hItem  =  tmphtItem;
					 tvItem.pszText  =  tBuf;
					 tvItem.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );
					 m_TreeCtrl->GetItem(  &tvItem  );
					 //  myTChar2Str(  tBuf,  tmpBuf,  sizeof(  tmpBuf  )  );

					 if  (  lstrcmpi(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
						 lstrcpyn(  tBuf,  displayName,  mycountof(  tBuf  )  );
						 tvItem.iImage  =  nImage;
						 tvItem.iSelectedImage  =  nSelectedImage;
						 m_TreeCtrl->SetItem(  &tvItem  );
					 }

					 //  刷新展开节点
					 if  (  tvItem.state  &  TVIS_EXPANDED   )  bRefreshItem(  tmphtItem  );				   
			   }

			   if  (  pDoc->m_docStruct.u.treeList.tree.selectedSwitchMac[0]  
				   &&  !strcmpi(  pDoc->m_docStruct.u.treeList.tree.selectedSwitchMac,  pObj->mac  )  )
			   {
				   this->m_var.htInitialItem  =  tmphtItem;
			   }

		  }
	 	}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CLeftView::bDisplayContent failed."  )  );
		   goto  errLabel;
	}

	 bRet				=				TRUE;

errLabel:

	if  (  rs.IsOpen(  )  )  rs.Close(  );
	
	return  bRet;		

}


 BOOL  CLeftView::bRefreshItem(  HTREEITEM  htItem  )
{
	QM_dbFuncs  *  pDbFuncs  =  QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  return  FALSE;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	 BOOL					bRet				=	FALSE;
	 QY_MC				*	pQyMc				=	QY_GET_GBUF(  );
	 CQyMcDoc			*	pDoc				=				GetDocument(  );
	 if  (  pDoc->m_docStruct.iDocType  !=  CONST_qyDocType_mcRootTree  )  return  FALSE;
	 QY_OBJ_DB			*	pObjDb				=				getProcedObjDb(  0,  pDoc->m_docStruct.u.treeList.tree.iDsnIndex  );
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;
	 //
	 int					iObjId;
	 QY_SWITCHPORT_RCD		switchPort;
	 QY_OBJINDEX_RCD		objIndex;
	 CRecordset				rs( ( CDatabase * )pObjDb->pDb );
	 CDBVariant				varVals[10];
	 int					index,  nFields;
	 TCHAR					sqlBuf[1024];
	 int					nImage,  nSelectedImage;
	 HTREEITEM				tmphtItem			=				NULL;
	 TCHAR					displayName[512]	=				_T(  ""  );		
	 TCHAR				*	pStopString;
	 TCHAR					tBuf[256];

	 traceLogA(  "CLeftView::bRefreshItem enters"  );

	 //  2004/07/26
	 if  (  pDoc->m_docStruct.u.treeList.tree.pfRefreshItem  )  return  (  pDoc->m_docStruct.u.treeList.tree.pfRefreshItem(  this,  htItem,  0  )  ?  FALSE  :  TRUE  );

	 
	 if  (  htItem  ==  m_var.htMyRootItem  )  goto  errLabel;

	 iObjId  =  m_TreeCtrl->GetItemData(  htItem  );
	 if  (  g_dbFuncs.pf_getObjIndex(  pObjDb,  iObjId,  &objIndex  )  )  goto  errLabel;
	 
	 if  (  objIndex.objType  ==  CONST_objType_qySwitch  )  {
		 													//  0		1			2				3				4					5		6	
		 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "SELECT switchMac,portIfIndex,portIfDescr,portIfAdminStatus,portIfOperStatus,bridgePort,comment0 from qySwitchPortTab where switchMac='%s' order by portIfIndex "  ),  objIndex.objIdStr0  );
		 traceLogA(  "%s",  sqlBuf  );
		 if  (  !rs.Open( CRecordset::forwardOnly,  CString(  sqlBuf  )  )  )  {
			 traceLogA(  "rs open() failed."  );  goto  errLabel;
		 }
	  			 
		 nFields  =  rs.GetODBCFieldCount(  );
		 //  rs.GetODBCFieldInfo(  index,  tmpFieldInfo  );
		 for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {
			  memset(  &switchPort,  0,  sizeof(  switchPort  )  ); 
			  for  (  index  =  0;  index  <  nFields;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   				  
			  index  =  0;  //  switchMac
			  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  switchPort.switchMac,  sizeof(  switchPort.switchMac  )  );  
			  index  ++  ;	//  iPortIfIndex,
			  if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  switchPort.iPortIfIndex  =  varVals[index].m_lVal;  }
			  index  ++  ;  //  portIfDescr,
			  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  switchPort.portIfDescr,  sizeof(  switchPort.portIfDescr  )  );  
			  index  ++  ;  //  iPortIfAdminStatus,
			  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  switchPort.iPortIfAdminStatus  =  _tcstol(  tBuf,  &pStopString,  10  );  
			  index  ++  ;  //  iPortIfOperStatus,
			  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  switchPort.iPortIfOperStatus  =  _tcstol(  tBuf,  &pStopString,  10  );  
			  index  ++  ;  //  iBridgePort,
			  if  (  varVals[index].m_dwType  ==  DBVT_LONG  )  {  switchPort.iBridgePort  =  varVals[index].m_lVal;  }
			  index  ++  ;  //  comment0暂时不取
			  //  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  safeStrnCpy(  tBuf,  switchPort.comment,  sizeof(  switchPort.comment  )  );  }
			  index  ++  ;

			  iObjId  =  getObjId(  pObjDb,  0,  NULL,CONST_objType_qySwitchPort,  &switchPort  );
			  if  (  iObjId  <  0  )  continue;

			  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%d %s"  ),  switchPort.iPortIfIndex,  CString(  switchPort.portIfDescr  )  );
			  getSnmpPortImages(  pQyMc,  &switchPort,  &nImage,  &nSelectedImage  );

			  if  (  !(  tmphtItem  =  this->FindItemData(  iObjId,  TRUE,  htItem  )  )  )  {
				  m_TreeCtrl->InsertItem(  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE  |  TVIF_PARAM,  
										   CString(  displayName  ),  
										   nImage,  
										   nSelectedImage,  
										   TVIS_EXPANDPARTIAL,  
										   TVIS_STATEIMAGEMASK, 
										   iObjId,  
										   htItem,  
										   TVI_LAST  );			  	  
				}
			  else  {
				  				  
				     //  只刷新展开节点
					 TVITEM				tvItem;
					 //  char				tmpBuf[512];

					 tvItem.mask  =  TVIF_TEXT  |  TVIF_IMAGE  |  TVIF_SELECTEDIMAGE  |  TVIF_STATE;
					 tvItem.hItem  =  tmphtItem;
					 tvItem.pszText  =  tBuf;
					 tvItem.cchTextMax  =  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  );
					 m_TreeCtrl->GetItem(  &tvItem  );
					 //  myTChar2Str(  tBuf,  tmpBuf,  sizeof(  tmpBuf  )  );

					 //  traceLogA(  "displayName is %s, tvItem.iImage is %d, nImage is %d",  displayName,  tvItem.iImage,  nImage  );

					 if  (  lstrcmpi(  tBuf,  displayName  )  ||  tvItem.iImage  !=  nImage  ||  tvItem.iSelectedImage  !=  nSelectedImage  )  {
						 lstrcpyn(  tBuf,  displayName,  mycountof(  tBuf  )  );
						 tvItem.iImage  =  nImage;
						 tvItem.iSelectedImage  =  nSelectedImage;
						 m_TreeCtrl->SetItem(  &tvItem  );
					 }
			   
			  }
		 }					 
	 }
	 
	 bRet  =  TRUE;

errLabel:
	 return  bRet;
}




 int  CLeftView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

		
	return 0;
}

void CLeftView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW				*		pNMTreeView		=		(NM_TREEVIEW*)pNMHDR;
	CTreeCtrl				&		treeCtrl		=		GetTreeCtrl( );
	HTREEITEM						hRoot			=		NULL;
	HTREEITEM						hCur			=		pNMTreeView->itemNew.hItem;
	HTREEITEM						hOld			=		pNMTreeView->itemOld.hItem;
	QY_MC					*		pQyMc			=		QY_GET_GBUF(  );
	CQyMcDoc				*		pDoc			=		GetDocument(  );
	QY_MC_SEL						curSel;
	QY_WMBUF_PUTDATA				tmpPutData;
	
	CWaitCursor						waitCursor;

	traceLogA(  "CLeftView::OnSelChanged"  );

	if  (  !hCur  )	 return;
	if  (  !(  hRoot  =  treeCtrl.GetRootItem(  )  )  )		return;
	if  (  !hOld  )	 return;
	if  (  hOld  ==  hCur  )	{
		qyDebugHint(  _T(  "CLeftView::OnSelchanged( ): how strange! hOld = hCur!" )  );
		return;
	}
	
	bRefreshItem(  hCur  );
	
	memset( &curSel, 0, sizeof( curSel ) );
	curSel.type  =  QY_SELTYPE_MCROOTTREE;
	curSel.u.rootTree.iDsnIndex  =  pDoc->m_docStruct.u.treeList.tree.iDsnIndex;	//  2007/01/02
	curSel.u.rootTree.hItem  =  hCur;
	if  (  hCur  ==  hRoot  )  curSel.u.rootTree.bRoot  =  TRUE;	
	else  curSel.u.rootTree.iHelpId  =  treeCtrl.GetItemData(  hCur  );
	if  (  pDoc->m_docStruct.u.treeList.tree.pfProcTreeSel  )  pDoc->m_docStruct.u.treeList.tree.pfProcTreeSel(  pQyMc,  &curSel,  0  );

	memset(  &tmpPutData,  0,  sizeof(  tmpPutData  )  );
	tmpPutData.uiType  =  QY_WMPARAM_MCPUTROOTDISPLAYDATA;
	MACRO_qyAssert(  MAX_QY_WMBUF_PUTDATALEN  >=  sizeof(  curSel  ),  _T(  "wmBuf to put data is too small."  )  );
	memcpy(  &tmpPutData.u,	 &curSel,  sizeof(  curSel  )  );

	getMgrWnd(  )->SendMessage(  CONST_qyWm_comm,  (  WPARAM  )this->m_hWnd,  (  LPARAM  )&tmpPutData  );

//  errLabel:

	*pResult  =  0;

}


void CLeftView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	QY_MC			*		pQyMc			=		QY_GET_GBUF(  );
	CQyMcDoc		*		pDoc			=		GetDocument(  );
	// POINT					point;
	CTreeCtrl		&		treeCtrl		=		GetTreeCtrl( );
	QY_MC_SEL				curSel;
	HTREEITEM				hRoot			=		NULL;
	HTREEITEM				hCur			=		NULL;
	QY_EVENTINFO			tmpEventInfo;
	
	traceLogA(  "CLeftView::OnRclick enters"  );

	/* Get the mouse cursor position */
	DWORD dwPos = GetMessagePos();

	/* Convert the co-ords into a CPoint structure */
	CPoint point( GET_X_LPARAM( dwPos ), GET_Y_LPARAM( dwPos ) ), spt;
	spt = point;

	if ( !( hRoot = treeCtrl.GetRootItem( ) ) )		goto errLabel;
	
	/* Convert to screen co-ords for hittesting */
	treeCtrl.ScreenToClient( &spt );

	UINT test;
	hCur = treeCtrl.HitTest( spt, &test );
	
	/* Did the click occur on an item */
	if ( !hCur || !( test & ( TVHT_ONITEM | TVHT_ONITEMRIGHT ) ) )  goto errLabel;
			
	memset( &curSel, 0, sizeof( curSel ) );
	curSel.type		=		QY_SELTYPE_MCROOTTREE;
	curSel.u.rootTree.type  =  pDoc->m_docStruct.u.treeList.tree.type;				//  2007/08/06
	curSel.u.rootTree.iDsnIndex  =  pDoc->m_docStruct.u.treeList.tree.iDsnIndex;	//  2007/01/02
	curSel.u.rootTree.hItem  =  hCur;		
	if  (  hCur  ==  hRoot  )  curSel.u.rootTree.bRoot		=		TRUE;	
	else  curSel.u.rootTree.iHelpId		=			treeCtrl.GetItemData(  hCur  );
	if  (  pDoc->m_docStruct.u.treeList.tree.pfProcTreeSel  &&  pDoc->m_docStruct.u.treeList.tree.pfProcTreeSel(  pQyMc,  &curSel,  0  )  )  goto  errLabel;
	
	memset(  &tmpEventInfo,  0,  sizeof(  tmpEventInfo  )  );
	tmpEventInfo.type  =  CONST_qyEventType_rClick;
	tmpEventInfo.hWnd  =  this->m_hWnd;
	tmpEventInfo.click.x  =  point.x;
	tmpEventInfo.click.y  =  point.y;
  	
	if  (  pDoc->m_docStruct.u.treeList.tree.pfProcEvent  )  pDoc->m_docStruct.u.treeList.tree.pfProcEvent(  pQyMc,  &curSel,  &tmpEventInfo  );

errLabel:
	
	*pResult = 0;

}


 void CLeftView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	QY_MC			*		pQyMc			=		QY_GET_GBUF(  );
	CQyMcDoc		*		pDoc			=		GetDocument(  );
	// POINT					point;
	CTreeCtrl		&		treeCtrl		=		GetTreeCtrl( );
	QY_MC_SEL				curSel;
	HTREEITEM				hRoot			=		NULL;
	HTREEITEM				hCur			=		NULL;
	QY_EVENTINFO			tmpEventInfo;

	traceLogA(  "CLeftView::OnDblclk: enters"  );
	
	/* Get the mouse cursor position */
	DWORD dwPos = GetMessagePos();

	/* Convert the co-ords into a CPoint structure */
	CPoint point( GET_X_LPARAM( dwPos ), GET_Y_LPARAM( dwPos ) ), spt;
	spt = point;

	if ( !( hRoot = treeCtrl.GetRootItem( ) ) )		goto errLabel;
	
	/* Convert to screen co-ords for hittesting */
	treeCtrl.ScreenToClient( &spt );

	UINT test;
	hCur = treeCtrl.HitTest( spt, &test );
	
	/* Did the click occur on an item */
	if ( !hCur || !( test & ( TVHT_ONITEM | TVHT_ONITEMRIGHT ) ) )  goto errLabel;
			
	memset( &curSel, 0, sizeof( curSel ) );
	curSel.type		=		QY_SELTYPE_MCROOTTREE;
	curSel.u.rootTree.iDsnIndex  =  pDoc->m_docStruct.u.treeList.tree.iDsnIndex;	//  2007/01/02
	curSel.u.rootTree.hItem  =  hCur;		
	if  (  hCur  ==  hRoot  )  curSel.u.rootTree.bRoot		=		TRUE;	
	else  curSel.u.rootTree.iHelpId		=			treeCtrl.GetItemData(  hCur  );
	if  (  pDoc->m_docStruct.u.treeList.tree.pfProcTreeSel  &&  pDoc->m_docStruct.u.treeList.tree.pfProcTreeSel(  pQyMc,  &curSel,  0  )  )  goto  errLabel;
	
	memset(  &tmpEventInfo,  0,  sizeof(  tmpEventInfo  )  );
	tmpEventInfo.type  =  CONST_qyEventType_dblClick;
	tmpEventInfo.hWnd  =  this->m_hWnd;
	tmpEventInfo.click.x  =  point.x;
	tmpEventInfo.click.y  =  point.y;
  	
	if  (  pDoc->m_docStruct.u.treeList.tree.pfProcEvent  )  pDoc->m_docStruct.u.treeList.tree.pfProcEvent(  pQyMc,  &curSel,  &tmpEventInfo  );


errLabel:
	
	*pResult = 0;
}


void CLeftView::OnDestroy() 
{
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	/*
	if  (  getDisplayQ(  pQyMc,  0,  0  )  )  {
		//  先发送到displayQ将displayedObj释放掉
		MIS_MSG_DISPLAYEDELEM_QMC	msg;
		memset(  &msg,  0,  sizeof(  msg  )  );
		msg.uiType  =  CONST_misMsgType_displayedElem_qmc;
		msg.elemU.wndInfo.uiType  =  CONST_displayedElemType_wndInfo;
		msg.elemU.wndInfo.hWnd  =  this->m_hWnd;
		msg.elemU.wndInfo.bClosed  =  TRUE;
		//
		if  (  qPostMsg(  &msg,  sizeof(  msg  ),  getDisplayQ(  pQyMc,  0,  0  )  )  )  {
			traceLogA(  "CLeftView::OnDestry: 发送close的CONST_misMsgType_displayedElem_qmc消息 failed."  );
		}
	}

	//  这里要记住释放，2007/06/09
	//
	//  if  (  m_var.ppSorted_byHandle  )  {
	//  	free(  m_var.ppSorted_byHandle  );  m_var.ppSorted_byHandle  =  NULL;
	//  }
	if  (  m_var.displayCtx.ppDisplayedElems_sortedByKey  )  {
		free(  m_var.displayCtx.ppDisplayedElems_sortedByKey  );  m_var.displayCtx.ppDisplayedElems_sortedByKey  =  NULL;
	}
	if  (  m_var.displayCtx.bQInited  )  {
		exitGenericQ(  &m_var.displayCtx.displayedElemQ  );  m_var.displayCtx.bQInited  =  FALSE;
	}
	*/
	if  (  m_var.bDisplayCtxInited  )  {
		exitMcCtxDisplayedWnd(  this->m_hWnd,  &m_var.displayCtx  );  m_var.bDisplayCtxInited  =  FALSE;
	}


	CTreeView::OnDestroy();
	
	// TODO: Add your message handler code here
	
}



// GetLastItem  - Gets last item in the branch
// Returns      - Last item
// hItem        - Node identifying the branch. NULL will 
//                return the last item in outine

HTREEITEM CLeftView::GetLastItem( HTREEITEM hItem )
{
        // Last child of the last child of the last child ...
        HTREEITEM htiNext;

        if( hItem == NULL ){
                // Get the last item at the top level
                htiNext = m_TreeCtrl->GetRootItem();
                while( htiNext ){
                        hItem = htiNext;
                        htiNext = m_TreeCtrl->GetNextSiblingItem( htiNext );
                }
        }

        while( m_TreeCtrl->ItemHasChildren( hItem ) ){
                htiNext = m_TreeCtrl->GetChildItem( hItem );
                while( htiNext ){
                        hItem = htiNext;
                        htiNext = m_TreeCtrl->GetNextSiblingItem( htiNext );
                }
        }

        return hItem;
}



// GetNextItem  - Get next item as if outline was completely expanded
// Returns      - The item immediately below the reference item
// hItem        - The reference item
HTREEITEM CLeftView::GetNextItem( HTREEITEM hItem )
{
        HTREEITEM       hti;

        if( m_TreeCtrl->ItemHasChildren( hItem ) )
                return m_TreeCtrl->GetChildItem( hItem );           // return first child
        else{
                // return next sibling item
                // Go up the tree to find a parent's sibling if needed.
                while( (hti = m_TreeCtrl->GetNextSiblingItem( hItem )) == NULL ){
                        if( (hItem = m_TreeCtrl->GetParentItem( hItem ) ) == NULL )
                                return NULL;
                }
        }
        return hti;
}

// GetNextItem  - Get previous item as if outline was completely expanded
// Returns              - The item immediately above the reference item
// hItem                - The reference item
HTREEITEM CLeftView::GetPrevItem( HTREEITEM hItem )
{
        HTREEITEM       hti;

        hti = m_TreeCtrl->GetPrevSiblingItem(hItem);
        if( hti == NULL )
                hti = m_TreeCtrl->GetParentItem(hItem);
        else
                hti = GetLastItem(hti);
        return hti;
}


// FindItem			- Finds an item that contains the search string
// Returns			- Handle to the item or NULL
// str				- String to search for
// bCaseSensitive	- Should the search be case sensitive
// bDownDir			- Search direction - TRUE for down
// bWholeWord		- True if search should match whole words
// hItem			- Item to start searching from. NULL for
//					- currently selected item
 HTREEITEM  CLeftView::FindItem(  CString	&	str, 
								  BOOL			bCaseSensitive  /*=  FALSE  */, 
								  BOOL			bDownDir		/*=  TRUE   */, 
								  BOOL			bWholeWord		/*=  FALSE  */, 
								  HTREEITEM		hItem			/*=	 NULL	*/  )
{
	int lenSearchStr = str.GetLength();
	if( lenSearchStr == 0 ) return NULL;

	HTREEITEM htiSel = hItem ? hItem : m_TreeCtrl->GetSelectedItem();
	HTREEITEM htiCur = bDownDir ?GetNextItem( htiSel ) : GetPrevItem( htiSel );
	CString sSearch = str;

	if( htiCur == NULL )
	{
		if( bDownDir )  htiCur = m_TreeCtrl->GetRootItem();
		else htiCur = GetLastItem( NULL );
	}

	if( !bCaseSensitive )
		sSearch.MakeLower();

	while( htiCur && htiCur != htiSel )
	{
		CString sItemText = m_TreeCtrl->GetItemText( htiCur );
		if( !bCaseSensitive )
			sItemText.MakeLower();

		int n;
		while( (n = sItemText.Find( sSearch )) != -1 )
		{
			// Search string found
			if( bWholeWord )
			{
				// Check preceding char
				if( n != 0 )
				{
					if( isalpha(sItemText[n-1]) || 
					    	sItemText[n-1] == '_' ){
						// Not whole word
						sItemText = sItemText.Right(
							sItemText.GetLength() - n - 
							lenSearchStr );
						continue;
					}
				}

				// Check succeeding char
				if( sItemText.GetLength() > n + lenSearchStr
					&& ( isalpha(sItemText[n+lenSearchStr]) ||
					sItemText[n+lenSearchStr] == '_' ) )
				{
					// Not whole word
					sItemText = sItemText.Right( sItemText.GetLength() 
							- n - sSearch.GetLength() );
					continue;
				}
			}
			
			if( IsFindValid( htiCur ) )
				return htiCur;
			else break;
		}


		htiCur = bDownDir ? GetNextItem( htiCur ) : GetPrevItem( htiCur );
		if( htiCur == NULL )
		{
			if( bDownDir )  htiCur = m_TreeCtrl->GetRootItem();
			else htiCur = GetLastItem( NULL );
		}
	}
	return NULL;
}

// IsFindValid	- Virtual function used by FindItem to allow this
//		  function to filter the result of FindItem
// Returns	- True if item matches the criteria
// Arg		- Handle of the item
 BOOL CLeftView::IsFindValid( HTREEITEM )
{
	return TRUE;
}

 // 执行此函数须通过SetItemData( )设置数据，条目掩码中须包括TVIF_PARAM.
 // 注：未测试，摘自《Visual C++ 图形用户界面开发指南》P277.
 HTREEITEM CLeftView::FindItemData( DWORD lParam, BOOL bDownDir, HTREEITEM hItem )
{
	 HTREEITEM htiSel = hItem ? hItem : m_TreeCtrl->GetSelectedItem( );
	 HTREEITEM htiCur = bDownDir ? GetNextItem( htiSel ) : GetPrevItem( htiSel );
	 if ( htiCur == NULL ) {
		 if ( bDownDir ) 
			 htiCur = m_TreeCtrl->GetRootItem( );
		 else
			 htiCur = GetLastItem( NULL );
	 }
	 while ( htiCur && htiCur != htiSel ) {

		 DWORD sItemData = m_TreeCtrl->GetItemData( htiCur );
		 
		 if ( sItemData == lParam )
			 return htiCur;
		 htiCur = bDownDir ? GetNextItem( htiCur ) : GetPrevItem( htiCur );
		 if ( htiCur == NULL ) {
			 if ( bDownDir )
				 htiCur = m_TreeCtrl->GetRootItem( );
			 else
				 htiCur = GetLastItem( NULL );
		 }
	 }
	 return NULL;
}


 
 // 此函数在调用前确保有子节点。
 BOOL CLeftView::bGetNodePath( HTREEITEM h, char *path, unsigned int size )
{
	 BOOL					bRet			=		FALSE;
	 CTreeCtrl		&		treeCtrl		=		this->GetTreeCtrl( );
	 HTREEITEM				tmph;
	 CString				tmpCStr, tmpCStr1;

	 if ( !path ) goto errLabel;
	 if ( !h ) goto errLabel;
	 if ( size <= QIM_FULLNAMELEN ) goto errLabel;

	 tmph			=		treeCtrl.GetParentItem( h );
	 if ( !tmph ) {
		 if ( !( *path ) ) strcpy( path, "" );
		 bRet = TRUE;
		 goto errLabel;
	 }

	 tmpCStr1		=		treeCtrl.GetItemText( tmph );
	 if ( !( *path ) )
	 	 sprintf( path, "%s", tmpCStr1 );
	 else {
		 tmpCStr	=		tmpCStr1 + "/" + CString( path ) ;
		 sprintf( path, "%s", tmpCStr );
	 }

	 if ( !bGetNodePath( tmph, path, size ) ) goto errLabel;

	 bRet = TRUE;

errLabel:

	 return bRet;

}


 



 
BOOL  CLeftView::bRootTreeGetSel(  CTreeCtrl &	treeCtrl,  HTREEITEM  hRoot,  HTREEITEM  hCur,  QY_MC_SEL  *  pCurSel  )
{
	 BOOL						bRet			=	FALSE;
	 QY_MCROOTTREE_SEL		*	pRootTreeSel	=	NULL;
	 
	 memset(	pCurSel,  0,  sizeof(  pCurSel[0]  )  );

	 pCurSel->type		=			QY_SELTYPE_MCROOTTREE;
	 pRootTreeSel		=		&	pCurSel->u.rootTree;
		
	if ( hCur == hRoot ) {	
		pRootTreeSel->bRoot					=					TRUE;	
		}
	else  {
		pRootTreeSel->iHelpId					=					treeCtrl.GetItemData(  hCur  );
		
	}
	 bRet		=		TRUE;
//  errLabel:
	 return		bRet;
}





