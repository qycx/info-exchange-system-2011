// DlgStatusDaemon.cpp : implementation file
//


#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyMc.h"
#include	"DlgStatusDaemon.h"
#include	"qyCusResTemp.h"


  int viewStatusDaemon(  int  index  )
{
	int								iErr					=	-1;
	QY_MC					*		pQyMc					=	QY_GET_GBUF(  );
	int								iServiceId				=	CONST_qyServiceId_mis;
	MC_VAR_isMgr  			*		pProcInfo				=	QY_GET_procInfo_isMgr(  );
	if  (  !pProcInfo  )  return  -1;

	CDlgStatusDaemon		*		pDlg					=	NULL;
	RECT							rect;


	if  (  index  <  0  ||  index  >=  mycountof(  pProcInfo->hWnds_status_daemon  )  )  {
		traceLog(  _T(  "viewStatusDaemon failed, index %d error"  ),  index  );
		return  -1;
	}

	//
	if  (  IsWindow(  pProcInfo->hWnds_status_daemon[index]  )  )  {
		MACRO_SetForegroundWindow(  pProcInfo->hWnds_status_daemon[index]  );
		iErr  =  0;  goto  errLabel;
	}

	pProcInfo->hWnds_status_daemon[index]  =  NULL;

	//
	pDlg  =  new  CDlgStatusDaemon(  CWnd::GetDesktopWindow(  )  );
	if  (  !pDlg  )  goto  errLabel;

	//
	switch  (  index  )  {
			case  0:
			case  1:
				   pDlg->m_var.iDaemonStatusType  =  CONST_iDaemonStatusType_msgr;
				   break;
			case  2:
					pDlg->m_var.iDaemonStatusType  =  CONST_iDaemonStatusType_channel;
					break;
			default:
					goto  errLabel;
					break;
	}
	
	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;
	pDlg->ShowWindow(  SW_SHOW  );

	//  
	pProcInfo->hWnds_status_daemon[index]  =  pDlg->m_hWnd;

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}
	if  (  !iErr  )  {
	}

	//  traceLogA(  "viewMediaControl leaves, iErr is %d",  iErr  );

	return  iErr;
}



// CDlgStatusDaemon dialog

IMPLEMENT_DYNAMIC(CDlgStatusDaemon, CDialog)

CDlgStatusDaemon::CDlgStatusDaemon(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgStatusDaemon::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	//
	m_var.m_pParent = pParent;
	m_var.m_nID = CDlgStatusDaemon::IDD;

}

CDlgStatusDaemon::~CDlgStatusDaemon()
{
}

BOOL CDlgStatusDaemon::Create(const RECT& rect)
{

	// TODO: Add your specialized code here and/or call the base class
	BOOL						bRet		=	FALSE;
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isMgr			*	pProc		=	NULL;

	/*
	if  (  !m_var.bInfoSet  )  {
		traceLogA(  "CDlgTalk::Create(  ): 在创建对话框之前应先设置初始数据"  );
		return  FALSE;
	}
	*/

	if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_is  )  return  FALSE;
	

	//
	if  (  !CDialog::Create(  this->m_var.m_nID, m_var.m_pParent  )  )  goto  errLabel;

	//
	m_var.bCreated  =  TRUE;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}


 BOOL  CDlgStatusDaemon::bQuitDlg(  )		
{		
	traceLogA(  "CDlgDaemonStatus(  )::bQuitDlg enters"  );


	//  2009/05/01
	DestroyWindow();				  
		
//  errLabel:

	traceLogA(  "CDlgDaemonStatus(  )::bQuitDlg leaves"  );

	return  TRUE;
}


 int  CDlgStatusDaemon::sizeAllControls(  )
{
errLabel:
	return  0;
}



void CDlgStatusDaemon::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgStatusDaemon, CDialog)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_MESSAGE(CONST_qyWm_comm, OnQyComm)

	ON_WM_SIZE()
END_MESSAGE_MAP()

 void CDlgStatusDaemon::PostNcDestroy()
 {
	 // TODO: Add your specialized code here and/or call the base class

	 CDialog::PostNcDestroy();

	 delete  this;
 }

// CDlgStatusDaemon message handlers

void CDlgStatusDaemon::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	//  CDialog::OnClose();
	bQuitDlg(  );
}

void CDlgStatusDaemon::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	MC_VAR_isMgr	*	pProcInfo	=	QY_GET_procInfo_isMgr(  );

	TCHAR	tBuf[128]	=	_T(  ""  );
	char	buf[128]	=	"";
	QY_MESSENGER_ID	idInfo;

	GetDlgItemText(  IDC_EDIT_filter,  tBuf,  mycountof(  tBuf  )  );
	myTChar2Utf8(  tBuf,  buf,  mycountof(  buf  )  );
	idStr2Info(  buf,  &idInfo  );

	//  MIS
	CQyMalloc		mallocObj_pMsgReq;
	MIS_MSG_REQ	*	pMsgReq	=	(  MIS_MSG_REQ  *  )mallocObj_pMsgReq.malloc(  sizeof(  MIS_MSG_REQ  )  );
	if  (  !pMsgReq  )  return;

	MACRO_memset_misMsgReq(  pMsgReq  );

	pMsgReq->uiType  =  CONST_misMsgType_req;

	//
	GET_daemonStatus_req	*	pReq	=	(  GET_daemonStatus_req  *  )&pMsgReq->data;
	memset(  pReq,  0,  sizeof(  pReq[0]  )  );
	pReq->uiType  =  CONST_imCommType_getDaemonStatusReq;
	pReq->iSubType  =  m_var.iDaemonStatusType;
	pReq->ucbGetTotal  =  TRUE;
	pReq->idInfo.ui64Id  =  idInfo.ui64Id;
	pReq->tmpInternal.hWnd_status  =  this->m_hWnd;

	pMsgReq->lenInBytes  =  offsetof(  GET_daemonStatus_req,  tmpInternal  )  +  sizeof(  pReq->tmpInternal  );

	MACRO_prepareForTran(  );

	pMsgReq->usCode  =  CONST_qyCmd_getDaemonStatus;
	pMsgReq->tStartTime  =  tStartTran;
	pMsgReq->uiTranNo  =  uiTranNo;

	qPostMsgAndTrigger(  pMsgReq,  offsetof(  MIS_MSG_REQ,  data  )  +  pMsgReq->lenInBytes,  &pProcInfo->mgrQ  );  

	CDialog::OnTimer(nIDEvent);
}

 int  CDlgStatusDaemon::listDaemonStatus(  int i,  BOOL  bInsert,  DAEMON_status_msgrMem  *  pNew    )
{
	int				iErr			=  -1;
	int				j				=	0;
	TCHAR			tBuf[256]		=  _T(  ""  );
	CListCtrl	*	pListCtrl		=  (  CListCtrl  *  )GetDlgItem(  IDC_LIST_deamonStatus  );

	if  (  m_var.iDaemonStatusType  !=  CONST_iDaemonStatusType_msgr  )  return  -1;

	DAEMON_status_msgrMem	*	pCur  =  &m_var.curInfo.u.msgr.mems[i];

	if  (  bInsert  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pNew->idInfo.ui64Id  );
		pListCtrl->InsertItem(  LVIF_TEXT | LVIF_STATE,  i,  tBuf,  (  i % 2  )  ==  0  ?  LVIS_SELECTED  :  0,  LVIS_SELECTED,  0,  0  );
	}
	else  {
		if  (  pCur->idInfo.ui64Id  !=  pNew->idInfo.ui64Id  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pNew->idInfo.ui64Id  );
			pListCtrl->SetItemText(  i,  j,  tBuf  );
		}
	}

	j ++;
	if  (  bInsert  
		||  pCur->a.stat.uiInSpeedInKbps  !=  pNew->a.stat.uiInSpeedInKbps  
		||  pCur->a.io.ucbReceiveing  !=  pNew->a.io.ucbReceiveing  
		||  pNew->a.io.ucbReceiveing  )  
	{
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pNew->a.stat.uiInSpeedInKbps  );
		if  (  pNew->a.io.ucbReceiveing  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s(%d)"  ),  tBuf,  GetTickCount()  -  pNew->a.io.dwTickCnt_recv_first  );
		pListCtrl->SetItemText(  i,  j,  tBuf  );
	}
	j ++;
	if  (  bInsert 
		||  pCur->a.stat.uiOutSpeedInKbps  !=  pNew->a.stat.uiOutSpeedInKbps  
		||  pCur->a.io.ucbSending  !=  pNew->a.io.ucbSending
		||  pNew->a.io.ucbSending  )  
	{
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pNew->a.stat.uiOutSpeedInKbps  );
		if  (  pNew->a.io.ucbSending  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s(%d)"  ),  tBuf,  GetTickCount(  )  -  pNew->a.io.dwTickCnt_snd_start  );
		pListCtrl->SetItemText(  i,  j,  tBuf  );
	}
	j ++;
	if  (  bInsert 
		||	pCur->v.stat.uiInSpeedInKbps  !=  pNew->v.stat.uiInSpeedInKbps  
		||	pCur->v.io.ucbReceiveing  !=  pNew->v.io.ucbReceiveing
		||  pNew->v.io.ucbReceiveing  )  
	{
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pNew->v.stat.uiInSpeedInKbps  );
		if  (  pNew->v.io.ucbReceiveing  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s(%d)"  ),  tBuf,  GetTickCount(  )  -  pNew->v.io.dwTickCnt_recv_first  );
		pListCtrl->SetItemText(  i,  j,  tBuf  );
	}
	//
	j ++;
	if  (  bInsert 
		||	pCur->v.stat.uiOutSpeedInKbps  !=  pNew->v.stat.uiOutSpeedInKbps  
		||	pCur->v.io.ucbSending  !=  pNew->v.io.ucbSending	
		||  pNew->v.io.ucbSending  )  
	{
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pNew->v.stat.uiOutSpeedInKbps  );
		if  (  pNew->v.io.ucbSending  )_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s(%d)"  ),  tBuf,  GetTickCount(  )  -  pNew->v.io.dwTickCnt_snd_start  );
		pListCtrl->SetItemText(  i,  j,  tBuf  );
	}
	//
	j ++;
	if  (  bInsert 
		||	pCur->f.stat.uiInSpeedInKbps  !=  pNew->f.stat.uiInSpeedInKbps  
		||	pCur->f.io.ucbReceiveing  !=  pNew->f.io.ucbReceiveing
		||  pNew->f.io.ucbReceiveing  )  
	{
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pNew->f.stat.uiInSpeedInKbps  );
		if  (  pNew->f.io.ucbReceiveing  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s(%d)"  ),  tBuf,  GetTickCount(  )  -  pNew->f.io.dwTickCnt_recv_first  );
		pListCtrl->SetItemText(  i,  j,  tBuf  );
	}
	//
	j ++;
	if  (  bInsert 
		||	pCur->f.stat.uiOutSpeedInKbps  !=  pNew->f.stat.uiOutSpeedInKbps  
		||	pCur->f.io.ucbSending  !=  pNew->f.io.ucbSending
		||  pNew->f.io.ucbSending  )  
	{
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pNew->f.stat.uiOutSpeedInKbps  );
		if  (  pNew->f.io.ucbSending  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s(%d)"  ),  tBuf,  GetTickCount(  )  -  pNew->f.io.dwTickCnt_snd_start  );
		pListCtrl->SetItemText(  i,  j,  tBuf  );
	}
	//
	j ++;
	if  (  bInsert 
		||	pCur->t.stat.uiInSpeedInKbps  !=  pNew->t.stat.uiInSpeedInKbps  
		||	pCur->t.io.ucbReceiveing  !=  pNew->t.io.ucbReceiveing
		||  pNew->t.io.ucbReceiveing  )  
	{
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pNew->t.stat.uiInSpeedInKbps  );
		if  (  pNew->t.io.ucbReceiveing  )_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s(%d)"  ),  tBuf,  GetTickCount(  )  -  pNew->t.io.dwTickCnt_snd_start  );
		pListCtrl->SetItemText(  i,  j,  tBuf  );
	}
	//
	j ++;
	if  (  bInsert 
		||	pCur->t.stat.uiOutSpeedInKbps  !=  pNew->t.stat.uiOutSpeedInKbps  
		||	pCur->t.io.ucbSending  !=  pNew->t.io.ucbSending
		||  pNew->t.io.ucbSending  )  
	{
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pNew->t.stat.uiOutSpeedInKbps  );
		if  (  pNew->t.io.ucbSending  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s(%d)"  ),  tBuf,  GetTickCount(  )  -  pNew->t.io.dwTickCnt_snd_start  );
		pListCtrl->SetItemText(  i,  j,  tBuf  );
	}

	iErr  =  0;
errLabel:
	return  iErr;
}

 int  CDlgStatusDaemon::listDaemonStatus(  int i,  BOOL  bInsert,  DAEMON_status_channelMem  *  pNew    )
{
	int				iErr			=  -1;
	int				j				=	0;
	TCHAR			tBuf[256]		=  _T(  ""  );
	CListCtrl	*	pListCtrl		=  (  CListCtrl  *  )GetDlgItem(  IDC_LIST_deamonStatus  );

	if  (  m_var.iDaemonStatusType  !=  CONST_iDaemonStatusType_channel  )  return  -1;

	DAEMON_status_channelMem	*	pCur  =  &m_var.curInfo.u.channel.mems[i];

	if  (  bInsert  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pNew->uiCliIndex  );
		pListCtrl->InsertItem(  LVIF_TEXT | LVIF_STATE,  i,  tBuf,  (  i % 2  )  ==  0  ?  LVIS_SELECTED  :  0,  LVIS_SELECTED,  0,  0  );
	}
	else  {
		if  (  pCur->uiCliIndex  !=  pNew->uiCliIndex  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pNew->uiCliIndex  );
			pListCtrl->SetItemText(  i,  j,  tBuf  );
		}
	}

	j ++;
	if  (  bInsert 	||	pCur->status.io.ucbReceiveing  !=  pNew->status.io.ucbReceiveing  ||  pNew->status.io.ucbReceiveing  )  
	{
		tBuf[0]  = 0;
		if  (  pNew->status.io.ucbReceiveing  )_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  GetTickCount(  )  -  pNew->status.io.dwTickCnt_recv_first  );
		pListCtrl->SetItemText(  i,  j,  tBuf  );
	}
	//
	j ++;
	if  (  bInsert 		||	pCur->status.io.ucbSending  !=  pNew->status.io.ucbSending  ||  pNew->status.io.ucbSending  )  
	{
		tBuf[0]  =  0;
		if  (  pNew->status.io.ucbSending  )_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  GetTickCount(  )  -  pNew->status.io.dwTickCnt_snd_start  );
		pListCtrl->SetItemText(  i,  j,  tBuf  );
	}
	//
	j ++;
	if  (  bInsert 	||	pCur->status.stat.uiInSpeedInKbps  !=  pNew->status.stat.uiInSpeedInKbps  )  
	{
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pNew->status.stat.uiInSpeedInKbps  );
		pListCtrl->SetItemText(  i,  j,  tBuf  );
	}
	//
	j ++;
	if  (  bInsert 	||	pCur->status.stat.uiOutSpeedInKbps  !=  pNew->status.stat.uiOutSpeedInKbps  )  
	{
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pNew->status.stat.uiOutSpeedInKbps  );
		pListCtrl->SetItemText(  i,  j,  tBuf  );
	}
	//
	j  ++  ;
	if  (  bInsert  ||  pCur->idInfo.ui64Id  !=  pNew->idInfo.ui64Id  )  
	{
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u"  ),  pNew->idInfo.ui64Id  );
		pListCtrl->SetItemText(  i,  j,  tBuf  );
	}
	j ++;
	//  if  (  bInsert ||  m_var.curInfo.mems[i].netStat_a.uiOutSpeedInKbps  !=  pNew->netStat_a.uiOutSpeedInKbps  )  {
	if  (  bInsert	||  pCur->uiChannelType !=  pNew->uiChannelType  )  
	{
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  qyGetDesByType1(  CONST_channelTypeTable,  pNew->uiChannelType  )  );
		pListCtrl->SetItemText(  i,  j,  tBuf  );
	}


	iErr  =  0;
errLabel:
	return  iErr;
}


 void  sizeDlg(  CDlgStatusDaemon  *  pDlg  )
{
	int  iWidth = 0,  iHeight  = 0;
	int  x, y;
	RECT  rect;
	int  iW  = 0,  iH  =  0;
	CWnd  *  pCtrl;

	pDlg->GetClientRect(  &rect  );
	iWidth  =  rect.right  -  rect.left;  
	iHeight  =  rect.bottom  -  rect.top;
	if  (  iWidth  <  10  ||  iHeight  <  10  )  goto errLabel;

	pCtrl  =  pDlg->GetDlgItem(  IDC_LIST_deamonStatus  );
	if  (  !pCtrl  )  goto  errLabel;

	HDWP	hDwp;
	int  nTotal;  nTotal  =  1;

	hDwp  =  BeginDeferWindowPos(  nTotal  );
	if  (  hDwp  )  {
		x  =  pDlg->m_var.iEdge_list_x;
		y  =  pDlg->m_var.iTop_list  -  23;
		iW  =  iWidth  -  2  *  pDlg->m_var.iEdge_list_x;
		iH  =  iHeight  -  pDlg->m_var.iTop_list;

		DeferWindowPos(  hDwp,  pCtrl->m_hWnd,  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );

		EndDeferWindowPos(  hDwp  );
	}

errLabel:
	return;
}

 BOOL CDlgStatusDaemon::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	QY_COLUMNINFO	*	pColumnInfo	=	NULL;
	int					i,j,nFields;
	CListCtrl		*	pListCtrl	=  (  CListCtrl  *  )GetDlgItem(  IDC_LIST_deamonStatus  );

	SetWindowText(  getResStr(  0,  &pQyMc->cusRes,  this->IDD  )  );

	switch  (  m_var.iDaemonStatusType  )  {
			TCHAR  tBuf[128];
			case  CONST_iDaemonStatusType_channel:  {
				pColumnInfo		=	(  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_deamonStatus_listColumnsOfChannel  );
				CString			str;
				LV_COLUMN		lvc;
				lvc.mask  =  LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	
				for (  i = 0; pColumnInfo[i].type  != -1; i ++  ) {
					lvc.iSubItem  =  i;
					lvc.pszText  =  pColumnInfo[i].label;
					lvc.cx  =  pColumnInfo[i].width;
					lvc.fmt  =  pColumnInfo[i].fmt;
					pListCtrl->InsertColumn(  i,  &lvc  );
				}
				nFields  =  i;


				  GetDlgItem(  IDC_STATIC_filter  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_EDIT_filter  )->ShowWindow(  SW_HIDE  );
				  //
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Channel status will display channel flow(in,out), channel status"  )  );
				  SetDlgItemText(  IDC_STATIC_netStats,  tBuf  );
				}
				  break;
			case  CONST_iDaemonStatusType_msgr:{
				pColumnInfo		=	(  QY_COLUMNINFO  *  )getResColumnInfo(  0,  &pQyMc->cusRes,  CONST_resId_deamonStatus_listColumns  );
				CString			str;
				LV_COLUMN		lvc;
				lvc.mask  =  LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	
				for (  i = 0; pColumnInfo[i].type  != -1; i ++  ) {
					lvc.iSubItem  =  i;
					lvc.pszText  =  pColumnInfo[i].label;
					lvc.cx  =  pColumnInfo[i].width;
					lvc.fmt  =  pColumnInfo[i].fmt;
					pListCtrl->InsertColumn(  i,  &lvc  );
				}
				nFields  =  i;
				}
			default:
					break;
	}



	pListCtrl->DeleteAllItems(  );
	//
	int		iW,iH;
	RECT	rect,rc_list;

	GetWindowRect(  &rect  );
	iW  =  rect.right  -  rect.left;
	iH  =  rect.bottom  -  rect.top;

	GetDlgItem(  IDC_LIST_deamonStatus  )->GetWindowRect(  &rc_list  );
	m_var.iEdge_list_x  =  (  iW  -  (  rc_list.right  -  rc_list.left  )  )  /  2;
	m_var.iTop_list  =  rc_list.top;


	sizeDlg(  this  );
	//
	SetTimer(  1,  1000,  NULL  );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

 LRESULT CDlgStatusDaemon::OnQyComm(  WPARAM  wParam, LPARAM  lParam  )
{
		LONG				lRet			=	-1;
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	QY_WMBUF_COMM	*	pComm			=	(  QY_WMBUF_COMM  *  )lParam;
	TCHAR				tBuf[512]		=	_T(  ""  );
	int				i	=	0, nItemLeft=	0;
	
	if  (  !pComm  )  return  -1;

	switch  (  pComm->uiType  )  {
			case  CONST_misMsgType_getDaemonStatus:  {
				  MIS_MSG_getDaemonStatus  *  pMsg  =  (  MIS_MSG_getDaemonStatus  *  )pComm;

				  //  if  (  m_var.iDaemonStatusType  ==  CONST_iDaemonStatusType_msgr  )  
				  {
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "netstat( kbps ): audio %d, %d, video %d, %d, file %d, %d, others %d, %d, admin %d, %d"  ),  
					  pMsg->data.total.netStat_a.uiInSpeedInKbps,  pMsg->data.total.netStat_a.uiOutSpeedInKbps,
					  pMsg->data.total.netStat_v.uiInSpeedInKbps,  pMsg->data.total.netStat_v.uiOutSpeedInKbps,
					  pMsg->data.total.netStat_f.uiInSpeedInKbps,  pMsg->data.total.netStat_f.uiOutSpeedInKbps,
					  pMsg->data.total.netStat_others.uiInSpeedInKbps,  pMsg->data.total.netStat_others.uiOutSpeedInKbps,
					  pMsg->data.total.netStat_admin.uiInSpeedInKbps,  pMsg->data.total.netStat_admin.uiOutSpeedInKbps  );

					  SetDlgItemText(  IDC_STATIC_netStats,  tBuf  );
				  }
				  //
				  if  (  m_var.iDaemonStatusType  ==  CONST_iDaemonStatusType_msgr  )  {
					  nItemLeft  =  min(  m_var.curInfo.usCnt,  pMsg->data.usCnt  );
					  for  (  i  =  0;  i < nItemLeft;  i ++  )  {
						   listDaemonStatus(  i,  FALSE,  &pMsg->data.u.msgr.mems[i]  );
						   memcpy(  &m_var.curInfo.u.msgr.mems[i],  &pMsg->data.u.msgr.mems[i],  sizeof(  m_var.curInfo.u.msgr.mems[i]  )  );
					  }
					  if  (  m_var.curInfo.usCnt  >  pMsg->data.usCnt  )  {
						  CListCtrl  *  pListCtrl  =  (  CListCtrl  * )GetDlgItem(  IDC_LIST_deamonStatus  );
						  for  (  i = 0; i < m_var.curInfo.usCnt - pMsg->data.usCnt;  i ++  )  pListCtrl->DeleteItem(  nItemLeft  );
					  }
					  if  (  m_var.curInfo.usCnt  <  pMsg->data.usCnt  )  {
						  for  (  ;  i < pMsg->data.usCnt; i ++  )  {
							  listDaemonStatus(  i,  TRUE,  &pMsg->data.u.msgr.mems[i]  );
							  memcpy(  &m_var.curInfo.u.msgr.mems[i],  &pMsg->data.u.msgr.mems[i],  sizeof(  m_var.curInfo.u.msgr.mems[i]  )  );
						  }
					  }
					  m_var.curInfo.usCnt  =  pMsg->data.usCnt;
				  }
				  else  if  (  m_var.iDaemonStatusType  ==  CONST_iDaemonStatusType_channel  )  {
							//int  i;
							nItemLeft  =  min(  m_var.curInfo.usCnt,  pMsg->data.usCnt  );
							for  (  i = 0; i < nItemLeft; i ++  ){
								listDaemonStatus(  i,  FALSE,  &pMsg->data.u.channel.mems[i]  );
								memcpy(  &m_var.curInfo.u.channel.mems[i],  &pMsg->data.u.channel.mems[i],  sizeof(  m_var.curInfo.u.channel.mems[i]  )  );
							}
							if  (  m_var.curInfo.usCnt  >  pMsg->data.usCnt  )  {
								CListCtrl  *  pListCtrl  =  (  CListCtrl  * )GetDlgItem(  IDC_LIST_deamonStatus  );
								for  (  i = 0; i < m_var.curInfo.usCnt - pMsg->data.usCnt;  i ++  )  pListCtrl->DeleteItem(  nItemLeft  );
							}
							if  (  m_var.curInfo.usCnt  <  pMsg->data.usCnt  )  {
								for  (  ;  i < pMsg->data.usCnt; i ++  )  {
									listDaemonStatus(  i,  TRUE,  &pMsg->data.u.channel.mems[i]  );
									memcpy(  &m_var.curInfo.u.channel.mems[i],  &pMsg->data.u.channel.mems[i],  sizeof(  m_var.curInfo.u.channel.mems[i]  )  );
								}
							}
							m_var.curInfo.usCnt  =  pMsg->data.usCnt;
							}
				  else  
					  goto  errLabel;
				  }
				  break;
			default:
					break;
	}

	lRet  =  CONST_qyWmRc_ok;
errLabel:
	return	lRet;

 }

 void CDlgStatusDaemon::OnSize(UINT nType, int cx, int cy)
 {
	 CDialog::OnSize(nType, cx, cy);

	 // TODO: Add your message handler code here
	 sizeDlg(  this  );
 }


