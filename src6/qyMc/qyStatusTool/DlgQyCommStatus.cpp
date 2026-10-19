// DlgQyCommStatus.cpp : implementation file
//

#include	"stdafx.h"
#include	<winsvc.h>
#include	<vfw.h>
//
#include	"qmCommon.h"
#include	"qyPs.h"

#include	"qyStatusToolCommon.h"
#include	"qystatustool.h"
#include	"DlgQyCommStatus.h"

#include	"DlgFilters.h"
#include ".\dlgqycommstatus.h"
#include	"qyCusResPublic.h"
#include	"qyCusResTemp.h"
#include	"qmUiFunc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgQyCommStatus dialog


CDlgQyCommStatus::CDlgQyCommStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQyCommStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQyCommStatus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgQyCommStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQyCommStatus)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQyCommStatus, CDialog)
	//{{AFX_MSG_MAP(CDlgQyCommStatus)
	ON_WM_SIZE()
	ON_WM_COPYDATA()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_select, OnSelchangeCOMBOselect)
	//}}AFX_MSG_MAP
	ON_MESSAGE(  QY_WM_COMM,  OnQyComm  )
	ON_BN_CLICKED(IDC_RADIO_qwmComm, OnBnClickedRadioqwmcomm)
	ON_BN_CLICKED(IDC_RADIO_qnmChking, OnBnClickedRadioqnmchking)
	ON_BN_CLICKED(IDC_RADIO_scanningIp, OnBnClickedRadioscanningip)
	ON_BN_CLICKED(IDC_CHECK_autoClearup, OnBnClickedCheckautoclearup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQyCommStatus message handlers

 void  sizeDlg(  CDlgQyCommStatus  *  pDlg  )
{	
			   
	int					iWidth				=	0;
	int					iHeight				=	0;

	int					x,  y;
	RECT				rect, rc;
	int					nWidth_autoClearup,  nHeight_autoClearup;
	int					iW,  iH;

	pDlg->GetClientRect(  &rect  );
	iWidth  =  rect.right  -  rect.left;  iHeight  =  rect.bottom  -  rect.top;
	if  (  iWidth  <  10  ||  iHeight  <  10  )  goto  errLabel;
		
	CWnd  *  pCtrl;
	pCtrl  =  pDlg->GetDlgItem(  IDC_CHECK_autoClearup  );
	if  (  !pCtrl  )  goto  errLabel;
	pCtrl->GetWindowRect(  &rc  );
	nWidth_autoClearup  =  rc.right  -  rc.left;
	nHeight_autoClearup  =  rc.bottom  -  rc.top;
	//
	HDWP			hDwp;
	int				nTotal;	nTotal  =  2;

	hDwp  =  BeginDeferWindowPos(  nTotal  );
	if  (  hDwp  )  {		 
				
		pCtrl  =  pDlg->GetDlgItem(  IDC_LIST_display  );
		x  =  pDlg->m_var.iEdge_list_x;
		y  =  pDlg->m_var.iTop_list  -  23;				//  这个23是因为前面没有把坐标统一成window坐标或者client坐标。混用了，所以用23这个修正参数。
		iW  =  iWidth  -  2  *  pDlg->m_var.iEdge_list_x;
		iH  =  iHeight  -  pDlg->m_var.iTop_list  -  pDlg->m_var.iSpacing_list_autoClearup  -  nHeight_autoClearup  -  pDlg->m_var.iEdge_autoClearup_b  +  23;
        
		DeferWindowPos(  hDwp,  pCtrl->m_hWnd,  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );
		
		pCtrl  =  pDlg->GetDlgItem(  IDC_CHECK_autoClearup  );		
		x  =  pDlg->m_var.iX_autoClearup;
		y  +=  iH  +  pDlg->m_var.iSpacing_list_autoClearup;
		iW  =  nWidth_autoClearup;
		iH  =  nHeight_autoClearup;
		DeferWindowPos(  hDwp,  pCtrl->m_hWnd,  NULL,  x,  y,  iW,  iH,  SWP_NOZORDER  );
		
		EndDeferWindowPos(  hDwp  );
	}
			
errLabel:
	return;

}


BOOL CDlgQyCommStatus::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	BOOL					bRet			=	FALSE;
	QY_STATUS_STRUCT	*	pStatusStruct	=	&this->m_var.u.showInfo.statusStruct;
	
	cusDlgRes(  0,  &pStatusStruct->cusRes,  this->m_hWnd,  this->IDD  );

	GENERIC_Q_CFG	qCfg;
	int				len;

	memset(  &qCfg,  0,  sizeof(  qCfg  )  );
	_sntprintf(  qCfg.name,  mycountof(  qCfg.name  ),  _T(  "qyStatusToolQ"  )  );
	_sntprintf(  qCfg.mutexName_prefix,  mycountof(  qCfg.mutexName_prefix  ),  _T(  "qyStatusToolQ"  )  );
	qCfg.uiMaxQNodes  =  (  qyGetAppType(  0,  0  )  ==  CONST_qyAppType_client  )  ?  CONST_maxnItemsInListBox_client  :  CONST_maxnItemsInListBox_main;
	if  (  initGenericQ(  &qCfg,  malloc,  0,  0,  free,  NULL,  &m_var.infoQ  )  )  goto  errLabel;
	m_var.bInfoQInited  =  TRUE;
	//
	len  =  sizeof(  void  *  )  *  qCfg.uiMaxQNodes;
	m_var.ppInfos_sortedByTime  =  (  void  **  )malloc(  len   );	
	if  (  !m_var.ppInfos_sortedByTime  )  goto  errLabel;	 
	memset(  m_var.ppInfos_sortedByTime,  0,  len  );

	if  (  qyGetAppType(  0,  0  )  ==  CONST_qyAppType_client  )  SetWindowText(  CONST_qnmStatusWndTitle_client  );
	else  SetWindowText(  CONST_qnmStatusWndTitle  );

	GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_RESETCONTENT,  0,  0  );
	GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_communicationStatus  )  );
	GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_communicationStatusWithFilters  )  );
	GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_export  )  );
	//
	GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_SETCURSEL,  m_var.iCurSel,  0  );

	(  (  CButton  *  )GetDlgItem(  IDC_RADIO_qwmComm  )  )->SetCheck(  BST_CHECKED  );
	//
	/*
	this->m_var.u.showInfo.iShowFlgs[0]  =  (  1  <<  CONST_qyShowType_serviceStatus  )
											|  (  1  <<  CONST_qyShowType_qwmComm  )
												|  (  1  <<  CONST_qyShowType_qmdState  )
													|  (  1  <<  CONST_qyShowType_sysInfo  )
														|  (  1  <<  CONST_qyShowType_debug  )
															|  (  1  <<  CONST_qyShowType_debugWarning  )
																|  (  1  <<  CONST_qyShowType_warning  );
																*/
	OnBnClickedRadioqwmcomm(  );


	BOOL	bStopped;		bStopped		=	FALSE;
	BOOL	bNotAllAllowed;	bNotAllAllowed	=	FALSE;
	char	buf[128];
	TCHAR	tBuf[128];
	
	if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_stopMon  ),  buf,  sizeof(  buf  )  )  )  {
		if  (  atol(  buf  )  ==  1  )  bStopped  =  TRUE;
	}
	if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),   _T(  CONST_regValName_bNotAllAllowed  ),  buf,  sizeof(  buf  )  )  )  {
		if  (  atol(  buf  )  ==  1  )  bNotAllAllowed  =  TRUE;		
	}
	_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  bStopped  ?  getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_uninstallClient  )  :  getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_allClientsAllowed  )  );  
	_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  TCHAR  ),  _T(  "%s,%s"  ),  tBuf,  bNotAllAllowed  ?  getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_onlyMgrRegList  )  :  getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_mgrAnyOne  )  );
	
	SetDlgItemText(  IDC_STATIC_nm,  tBuf  );

	//  GetDlgItem(  IDC_LIST_display  )->SendMessage(  LB_RESETCONTENT,  0,  0  );

	_sntprintf(  tBuf,  sizeof(  tBuf  )  /  sizeof(  TCHAR  ),  _T(  "%d %s"  ),  m_var.infoQ.cfg.uiMaxQNodes,  getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_resetWhenUpTo    )  ); 
	SetDlgItemText(  IDC_CHECK_autoClearup,  tBuf  );

	(  (  CButton  *  )GetDlgItem(  IDC_CHECK_autoClearup  )  )->SetCheck(  BST_CHECKED  );
	m_var.bAutoClearup  =  TRUE;

	int		iWidth,  iHeight;
	RECT	rect, rc_list;
	int		iList_b;
	//
	GetWindowRect(  &rect  );
	iWidth  =  rect.right  -  rect.left;
	iHeight  =  rect.bottom  -  rect.top;
	//
	GetDlgItem(  IDC_LIST_display  )->GetWindowRect(  &rc_list  );
	m_var.iEdge_list_x  =  (  iWidth  -  (  rc_list.right  -  rc_list.left  )  )  /  2;
	m_var.iTop_list  =  rc_list.top;
	iList_b  =  rc_list.bottom  -  rect.top;
	//
	GetDlgItem(  IDC_CHECK_autoClearup  )->GetWindowRect(  &rect  );
	m_var.iX_autoClearup  =  rect.left;
	m_var.iEdge_autoClearup_b  =  iHeight  -  rect.bottom;
	m_var.iSpacing_list_autoClearup  =  rect.top  -  iList_b;

	sizeDlg(  this  );

	if  (  m_var.iType  ==  CONST_qyPsType_show  )  {
		SetTimer(  CONST_qyPsTimerId,  2000,  NULL  );
	}
	bRet  =  TRUE;
errLabel:
	if  (  !bRet  )  {
		EndDialog(  -1  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgQyCommStatus::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	sizeDlg(  this  );
}

BOOL CDlgQyCommStatus::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct) 
{
	// TODO: Add your message handler code here and/or call default
	COPYDATASTRUCT		*	pCopyData			=	(  COPYDATASTRUCT  *  )pCopyDataStruct;
	int						iShowType			=	0;
	QNM_WMBUF_SHOWSTRUCT	wmBufShowStruct;
		
	if  (  pCopyData->cbData  >=  sizeof(  (  (  QY_SHOW_STRUCT  *  )0  )->iType  )  )  {
		iShowType  =  (  (  QY_SHOW_STRUCT  *  )pCopyData->lpData  )->iType;
		//  tracelog(  "CQyPs::OnCopyData: iShowType is %d",  iShowType  );
		if  (  (  1  <<  iShowType  )  &  m_var.u.showInfo.iShowFlgs[0]  )  {

			memset(  &wmBufShowStruct,  0,  sizeof(  wmBufShowStruct  )  );
			wmBufShowStruct.uiType  =  CONST_qyWmParam_show;
			memcpy(  &wmBufShowStruct.showStruct,  pCopyData->lpData,  min(  sizeof(  QY_SHOW_STRUCT  ),  pCopyData->cbData  )  );
			this->SendMessage(  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBufShowStruct  );

		}
	}

	
	CDialog::OnCopyData(pWnd, pCopyDataStruct);
	return  TRUE;
}



void CDlgQyCommStatus::OnTimer(UINT_PTR nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
// TODO: Add your message handler code here and/or call default
	QY_STATUS_STRUCT	*	pStatusStruct	=	&this->m_var.u.showInfo.statusStruct;



	if  (  m_var.iType  ==  CONST_qyPsType_show  )  {
		DWORD						dwStatus;
		BOOL						bServiceRunning		=  FALSE;
		QNM_WMBUF_SHOWSTRUCT		wmBufShowStruct;
	
		if  (  m_var.u.showInfo.iShowFlgs[0]  &  (  1  <<  CONST_qyShowType_serviceStatus  )  )  {

			MACRO_qyAssert(  m_var.u.showInfo.serviceName_netMc[0],  _T(  "服务名字未填"  )  );
			MACRO_qyAssert(  m_var.u.showInfo.serviceName_is[0],  _T(  "服务名字未填"  )  );

			if  (  !qyGetServiceStatus(  NULL,  CString(  m_var.u.showInfo.serviceName_netMc  ).GetBuffer(  0  ),  &dwStatus  )  
				&&  dwStatus  ==  SERVICE_RUNNING  )  
			{
				bServiceRunning  =  TRUE;
			}

			#if  1
				 if  (  !qyGetServiceStatus(  NULL,  _T(  "awpmService"  ),  &dwStatus  )  
					 &&  dwStatus  ==  SERVICE_RUNNING  )  
				 {
					 bServiceRunning  =  TRUE;
				 }
			#endif

			if  (  bServiceRunning  !=  m_var.u.showInfo.bServiceRunning_netMc  )  {
				m_var.u.showInfo.bServiceRunning_netMc  =  bServiceRunning;
				memset(  &wmBufShowStruct,  0,  sizeof(  wmBufShowStruct  )  );
				wmBufShowStruct.uiType  =  CONST_qyWmParam_show;
				wmBufShowStruct.showStruct.iType  =  CONST_qyShowType_serviceStatus;
				_sntprintf(  wmBufShowStruct.showStruct.who_from,  mycountof(  wmBufShowStruct.showStruct.who_from  ),  _T(  "%s"  ),  qyGetDesByType1(  CONST_qyServiceIdTable,  CONST_qyServiceId_netMc  )  );
				_sntprintf(  wmBufShowStruct.showStruct.what,  mycountof(  wmBufShowStruct.showStruct.what  ),  bServiceRunning  ?  getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_serviceIsRunning  )  :  getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_serviceHaveStopped  )  );
				this->SendMessage(  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBufShowStruct  );
			}

			//  下面处理Is服务
			bServiceRunning  =  FALSE;
			if  (  !qyGetServiceStatus(  NULL,  CString(  m_var.u.showInfo.serviceName_is  ).GetBuffer(  0  ),  &dwStatus  )  
				&&  dwStatus  ==  SERVICE_RUNNING  )  
			{
				bServiceRunning  =  TRUE;
			}

			if  (  bServiceRunning  !=  m_var.u.showInfo.bServiceRunning_is  )  {
				m_var.u.showInfo.bServiceRunning_is  =  bServiceRunning;
				memset(  &wmBufShowStruct,  0,  sizeof(  wmBufShowStruct  )  );
				wmBufShowStruct.uiType  =  CONST_qyWmParam_show;
				wmBufShowStruct.showStruct.iType  =  CONST_qyShowType_serviceStatus;
				_sntprintf(  wmBufShowStruct.showStruct.who_from,  mycountof(  wmBufShowStruct.showStruct.who_from  ),  _T(  "%s"  ),  qyGetDesByType1(  CONST_qyServiceIdTable,  CONST_qyServiceId_is  )  );
				_sntprintf(  wmBufShowStruct.showStruct.what,  mycountof(  wmBufShowStruct.showStruct.what  ),  bServiceRunning  ?  getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_serviceIsRunning  )  :  getResStr(  0,  &pStatusStruct->cusRes,  CONST_resId_serviceHaveStopped  )  );
				this->SendMessage(  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBufShowStruct  );
			}


		}

		if  (  m_var.u.showInfo.iShowFlgs[0]  &  (  1  <<  CONST_qyShowType_refresh  )  )  {
			memset(  &wmBufShowStruct,  0,  sizeof(  wmBufShowStruct  )  );
			wmBufShowStruct.uiType  =  CONST_qyWmParam_show;
			wmBufShowStruct.showStruct.iType  =  CONST_qyShowType_refresh;
			this->SendMessage(  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBufShowStruct  );
		}

	}

//  errLabel:

	CDialog::OnTimer(nIDEvent);
}

 static  char  *  myDisplayTime(  SYSTEMTIME  *  when,  char  *  displayBuf,  unsigned  int  size  )
{
	char  *  ptr  =  displayBuf;

	if  (  size  <  32  )  return  NULL;

	_snprintf(  displayBuf,  size,  
				"%04d-%02d-%02d %02d:%02d:%02d::%03d", 
					when->wYear,  
						when->wMonth,  
							when->wDay,  
								when->wHour,  
									when->wMinute,  
										when->wSecond,
											when->wMilliseconds  );

	
	return ptr;

}


void CDlgQyCommStatus::OnDestroy() 
{
	BOOL  bRet  =  KillTimer(  CONST_qyPsTimerId  );

	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

#define FILE_FILTER_TEXT \
    TEXT("Log File (*.txt)\0*.txt\0")\
    TEXT("All Files (*.*)\0*.*;\0\0")

 int  myExportSth(  CDlgQyCommStatus  *  pDlg  )
 {
	 CListBox  *  pLb  =  (  CListBox  *  )pDlg->GetDlgItem(  IDC_LIST_display  );
	 int		i;
	
	LPCTSTR						lpszDefExt  =	TEXT("*\0");
	LPCTSTR							lpszFilter	=	FILE_FILTER_TEXT;
	LPCTSTR							title		=	TEXT("Open Log File...\0");
	CQyString						pathCStr;
	DWORD							dwFlags     =	OFN_READONLY;
	FILE				*			fp			=	NULL;

	//
	qyBrowseForFile(  pDlg->m_hWnd,  TRUE,  lpszDefExt,  dwFlags,  FILE_FILTER_TEXT,  title,  NULL,  pathCStr  );
	if  (  pathCStr.GetLength(  )  ==  0  )  goto  errLabel;

	{
		CWaitCursor	cur;
		fp  =  _tfopen(  pathCStr.GetBuffer(  0  ),  _T(  "a"  )  );  
		if  (  !fp  )  goto  errLabel;

		for  (  i  =  0;  i  <  pLb->GetCount(  );  i  ++  )  {
			 CString		str;

			 pLb->GetText(  i,  str  );
			 _ftprintf(  fp,  _T(  "%s\n"  ),  str  );
		}
	}

errLabel:
	 if  (  fp  )  fclose(  fp  );
	 return  0;
 }

void CDlgQyCommStatus::OnSelchangeCOMBOselect() 
{
	QY_STATUS_STRUCT	*	pStatusStruct	=  &m_var.u.showInfo.statusStruct;
	char					ip[128]			=	"";
	unsigned  long			ulIp0			=	0;
	unsigned  long			ulIp1			=	0;
	CString					str0,  str1,  str2,  str3;

	int	 iCurSel  =  GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_GETCURSEL,  0,  0  );
	
	if  (  iCurSel  ==  CB_ERR  )  return;

	switch  (  iCurSel  )  {
			case  0:
					GetDlgItem(  IDC_STATIC_clientIp0  )->ShowWindow(  SW_HIDE  );
					GetDlgItem(  IDC_STATIC_clientIp1  )->ShowWindow(  SW_HIDE  );
				    GetDlgItem(  IDC_STATIC_filter0  )->ShowWindow(  SW_HIDE  );					
					GetDlgItem(  IDC_STATIC_filter1  )->ShowWindow(  SW_HIDE  );
					GetDlgItem(  IDC_STATIC_contentFilter2  )->ShowWindow(  SW_HIDE  );	
					GetDlgItem(  IDC_STATIC_contentFilter3  )->ShowWindow(  SW_HIDE  );	

					break;
			case  1:  {
					  CDlgFilters	dlg;
				  

					  dlg.bSetDlgInfo(  0,  this->m_hWnd,  m_var.ulClientIp0,  m_var.ulClientIp1,  m_var.filter0Buf,  m_var.filter1Buf,  m_var.contentFilter2Buf,  m_var.contentFilter3Buf  );
					  if  (  dlg.DoModal(  )  !=  IDOK  )  {
						  GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_SETCURSEL,  0,  0  );
						  GetDlgItem(  IDC_STATIC_clientIp0  )->ShowWindow(  SW_HIDE  );
						  GetDlgItem(  IDC_STATIC_clientIp1  )->ShowWindow(  SW_HIDE  );
						  GetDlgItem(  IDC_STATIC_filter0  )->ShowWindow(  SW_HIDE  );					
						  GetDlgItem(  IDC_STATIC_filter1  )->ShowWindow(  SW_HIDE  );	
						  GetDlgItem(  IDC_STATIC_contentFilter2  )->ShowWindow(  SW_HIDE  );	
						  GetDlgItem(  IDC_STATIC_contentFilter3  )->ShowWindow(  SW_HIDE  );	
						  
						  iCurSel  =  0;
						  break;  
					  }
					  //
					  GetDlgItem(  IDC_STATIC_clientIp0  )->ShowWindow( SW_SHOW  );
					  ulIp0  =  dlg.m_var.ulClientIp0;
					  ip[0]  =  0;
					  if  (  ulIp0  &&  !ulIp2Str(  ulIp0,  ip,  mycountof(  ip  )  )  )  ip[0]  =  0;
					  SetDlgItemText(  IDC_STATIC_clientIp0,  CString(  ip  )  );
					  //
					  GetDlgItem(  IDC_STATIC_clientIp1  )->ShowWindow( SW_SHOW  );
					  ulIp1  =  dlg.m_var.ulClientIp1;
					  ip[0]  =  0;
					  if  (  ulIp1  &&  !ulIp2Str(  ulIp1,  ip,  mycountof(  ip  )  )  )  ip[0]  =  0;
					  SetDlgItemText(  IDC_STATIC_clientIp1,  CString(  ip  )  );
					  //
					  GetDlgItem(  IDC_STATIC_filter0  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_filter0,  CString(  dlg.m_var.filter0Buf  )  );
					  GetDlgItem(  IDC_STATIC_filter1  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_filter1,  CString(  dlg.m_var.filter1Buf  )  );
					  //
					  GetDlgItem(  IDC_STATIC_contentFilter2  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_contentFilter2,  CString(  dlg.m_var.contentFilter2Buf  )  );
					  GetDlgItem(  IDC_STATIC_contentFilter3  )->ShowWindow(  SW_SHOW  );
					  SetDlgItemText(  IDC_STATIC_contentFilter3,  CString(  dlg.m_var.contentFilter3Buf  )  );
					  //
					  str0  =  CString(  dlg.m_var.filter0Buf  );
					  str0.TrimLeft(  );  str0.TrimRight(   );  str0.MakeUpper(  );
					  str1  =  CString(  dlg.m_var.filter1Buf  );
					  str1.TrimLeft(  );  str1.TrimRight(  );  str1.MakeUpper(  );
					  str2  =  CString(  dlg.m_var.contentFilter2Buf  );
					  str2.TrimLeft(  );  str2.TrimRight(  );  str2.MakeUpper(  );
					  str3  =  CString(  dlg.m_var.contentFilter3Buf  );
					  str3.TrimLeft(  );  str3.TrimRight(  );  str3.MakeUpper(  );					  
					  //
					  }
					break;
			case  2:
				   myExportSth(  this  );
				   //
				   GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_SETCURSEL,  m_var.iCurSel,  0  );
				   return;
				   break;
			default:
					break;
	}
	m_var.iCurSel  =  iCurSel;

	if  (  ulIp0  !=  m_var.ulClientIp0  ||  ulIp1  !=  m_var.ulClientIp1  ||  str0  !=  CString(  m_var.filter0Buf  )  ||  str1  !=  CString(  m_var.filter1Buf  )  ||  str2  !=  CString(  m_var.contentFilter2Buf  )  ||  str3  !=  CString(  m_var.contentFilter3Buf  )  )  {
		m_var.ulClientIp0  =  ulIp0;
		m_var.ulClientIp1  =  ulIp1;
		lstrcpyn(  m_var.filter0Buf,  str0,  mycountof(  m_var.filter0Buf  )  );
		lstrcpyn(  m_var.filter1Buf,  str1,  mycountof(  m_var.filter1Buf  )  );
		lstrcpyn(  m_var.contentFilter2Buf,  str2,  mycountof(  m_var.contentFilter2Buf  )  );
		lstrcpyn(  m_var.contentFilter3Buf,  str3,  mycountof(  m_var.contentFilter3Buf  )  );
		
		//
		GetDlgItem(  IDC_LIST_display  )->SendMessage(  LB_RESETCONTENT,  0,  0  );
		emptyGenericQ(  &m_var.infoQ  );
	}
	
}


 
 int  printInfos(  void  **  ppElem,  unsigned  int  uiQNodes  )
{
	INFO_ELEM	*	pGuest;
	int					i;

	#ifndef  __DEBUG__
			 return  0;
	#endif

	TRACE(  _T(  "printInfos enters\n"  )  );

	for  (  i  =  0;  i  <  (  int  )uiQNodes;  i  ++  )  {
		 pGuest  =  (  INFO_ELEM  *  )ppElem[i];
		 TRACE(  _T(  "\t第%d个info是["  ),  i  );
		 OutputDebugString(  pGuest->wBuf  );
		 OutputDebugString(  _T(  "]\n"  )  );
	}

	TRACE(  _T(  "printInfos leaves\n"  )  );

	return  0;
}

 int  iCmpSystemTime(  SYSTEMTIME  *  t0,  SYSTEMTIME  *  t1  )
{
	int	 iRet	=	-1;

	if  (  t0->wYear  >  t1->wYear  )  return  1;
	if  (  t0->wYear  <  t1->wYear  )  return  -1;
	if  (  t0->wMonth  >  t1->wMonth  )  return  1;
	if  (  t0->wMonth  <  t1->wMonth  )  return  -1;
	if  (  t0->wDay  >  t1->wDay  )  return  1;
	if  (  t0->wDay  <  t1->wDay  )  return  -1;
	if  (  t0->wHour  >  t1->wHour  )  return  1;
	if  (  t0->wHour  <  t1->wHour  )  return  -1;
	if  (  t0->wMinute  >  t1->wMinute  )  return  1;
	if  (  t0->wMinute  <  t1->wMinute  )  return  -1;
	if  (  t0->wSecond  >  t1->wSecond  )  return  1;
	if  (  t0->wSecond  <  t1->wSecond  )  return  -1;
	if  (  t0->wMilliseconds  >  t1->wMilliseconds  )  return  1;
	if  (  t0->wMilliseconds  <  t1->wMilliseconds  )  return  -1;
	return  0;
}

 int  iCmpInfoElem(  INFO_ELEM  *  pElem0,  INFO_ELEM  *  pElem1  )
{
	int		iRet	=	-1;

	iRet  =  iCmpSystemTime(  &pElem0->when,  &pElem1->when  );
	if  (  iRet  )  return  iRet;
	
	return  pElem0->uiStep  -  pElem1->uiStep;
}

 int  __cdecl  myCompare_searchInfoByTime(  const  void  *  key,  const  void  *  pElemParam  )
{
	INFO_ELEM				*	pGuest			=	(  INFO_ELEM  *  )key;
	INFO_ELEM				*	pElem			=	*(  INFO_ELEM  **  )pElemParam;

	return  iCmpInfoElem(  pGuest,  pElem  );
	
}

 LRESULT CDlgQyCommStatus::OnQyComm(  WPARAM wParam,  LPARAM lParam  )
{
	long					lRet				=					-1;
	QY_WMBUF_COMM		*	pComm				=					( QY_WMBUF_COMM * )lParam;
	TCHAR					tBuf[1024];
	int						iCurSel;
	
	if  (  !pComm  )  goto  errLabel;

	traceLogA(  "CPpQwmCommStatus::OnQyComm  enters"  );

	switch  (  pComm->uiType  )  {
			case  CONST_qyWmParam_show:  {
				  QY_SHOW_STRUCT	*	pShowStruct				=	&(  (  QNM_WMBUF_SHOWSTRUCT  *  )pComm  )->showStruct;
				  char					stepBuf[16  +  1]		=	"    ";
				  char					clientIp[128  +  1]		=	"";
				  char					displayBuf[128]			=	"";
				  CString				fromStr,  toStr;
				  BOOL					bWatching				=	TRUE;
				  CString				curSelStr;

				  
				  switch  (  pShowStruct->iType  )  {
						  case  CONST_qyShowType_qwmComm:
						  case  CONST_qyShowType_sysInfo:
						  case  CONST_qyShowType_debug:
						  case  CONST_qyShowType_debugWarning:
						  case  CONST_qyShowType_warning:
						  case  CONST_qyShowType_detail:		//  2009/05/10
						  //
						  case  CONST_qyShowType_qnmChking:
						  case  CONST_qyShowType_qnmProxyChking:
						  //
						  case  CONST_qyShowType_scanningNetworkSegment:
						  case  CONST_qyShowType_scanningIp:
						  case  CONST_qyShowType_bhbScanningNetworkSegment:

							  								
							    if  (  m_var.ulClientIp0  ||  m_var.ulClientIp1  ||  m_var.filter0Buf[0]  ||  m_var.filter1Buf[0]  )  {
									fromStr  =  CString(  pShowStruct->who_from  );  fromStr.MakeUpper(  );
									toStr  =  CString(  pShowStruct->who_to  );  toStr.MakeUpper(  );
									//
									bWatching  =  FALSE;
									if  (  m_var.ulClientIp0  )  {
										if  (  pShowStruct->ulClientIp  ==  m_var.ulClientIp0  )  bWatching  =  TRUE;
									}
									if  (  m_var.ulClientIp1  )  {
										if  (  pShowStruct->ulClientIp  ==  m_var.ulClientIp1  )  bWatching  =  TRUE;
									}
									if  (  m_var.filter0Buf[0]  )  {
										if  (  _tcsstr(  fromStr,  m_var.filter0Buf  )  ||  _tcsstr(  toStr,  m_var.filter0Buf  )  )  bWatching  =  TRUE;
									}									
									if  (  m_var.filter1Buf[0]  )  {																				
										if  (  _tcsstr(  fromStr,  m_var.filter1Buf  )  ||  _tcsstr(  toStr,  m_var.filter1Buf  )  )  bWatching  =  TRUE;
									}
							  	}
								if  (  !bWatching  )  break;

								if  (  isQFull(  &m_var.infoQ  )  )  {
									if  (  !m_var.bAutoClearup  )  break;
									GetDlgItem(  IDC_LIST_display  )->SendMessage(  LB_RESETCONTENT,  0,  0  );
									emptyGenericQ(  &m_var.infoQ  );
								}
								
								//  注意，要在加入之前先获取iCurSel, 因为排序功能会在加入后，重新调整的, 2007/06/01
								if  (  !m_var.infoQ.uiQNodes  )  iCurSel  =  -1;
								else  {
									  iCurSel  =  GetDlgItem(  IDC_LIST_display  )->SendMessage(  LB_GETCURSEL,  0,  0  );
									  if  (  iCurSel  ==  m_var.infoQ.uiQNodes  -  1  )  iCurSel  =  -1;
									  if  (  iCurSel  >=  0  )  {		//  未选或选最后一行,都是自动调整.不能跟踪.																										
										  (  (  CListBox  *  )GetDlgItem(  IDC_LIST_display  )  )->GetText(  iCurSel,  curSelStr  );									
									  }
								}

								//  
								myDisplayTime(  &pShowStruct->when,  displayBuf,  mycountof(  displayBuf  )  );
								if  (  pShowStruct->uiStep  )  {
									_snprintf(  stepBuf,  mycountof(  stepBuf  ),  (  "%3d"  ),  pShowStruct->uiStep  );
								}
								if  (  !pShowStruct->ulClientIp  ||  !ulIp2Str(  pShowStruct->ulClientIp,  clientIp,  mycountof(  clientIp  )  )  )  safeStrnCpy(  "                      ",  clientIp,  mycountof(  clientIp  )  );
								if  (  pShowStruct->who_to[0]  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s  %-15s %-15s %-6s %s%s"  ),  CString(  displayBuf  +  5  ),  CString(  stepBuf  ),  CString(  clientIp  ),  CString(  pShowStruct->who_from  )  +  " -> "  +  pShowStruct->who_to,  pShowStruct->whereBuf,  pShowStruct->doStr,  pShowStruct->what  );
								else  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s  %-15s %-15s  %-6s %s%s"  ),  CString(  displayBuf  +  5  ),  CString(  stepBuf  ),  CString(  clientIp  ),  pShowStruct->who_from,  pShowStruct->whereBuf,  pShowStruct->doStr,  pShowStruct->what  );
								//  OutputDebugString(  CString(  "qwmComm:  [  "  )  +  tBuf  +  "]\n"  );

								//  对内容做一下过滤
								bWatching  =  TRUE;
								if  (  m_var.contentFilter2Buf[0]  ||  m_var.contentFilter3Buf[0]  )  {
									CString		str;
									str  =  tBuf;
									str.MakeUpper(  );

									bWatching  =  FALSE;
									if  (  m_var.contentFilter2Buf[0]  )  {																				
										if  (  _tcsstr(  str.GetBuffer(  0  ),  m_var.contentFilter2Buf  )  )  bWatching  =  TRUE;
									}
									if  (  m_var.contentFilter3Buf[0]  )  {
										if  (  _tcsstr(  str.GetBuffer(  0  ),  m_var.contentFilter3Buf  )  )  bWatching  =  TRUE;    
									}
								}
								if  (  !bWatching  )  break;

							    //  
								INFO_ELEM		info;
								INFO_ELEM	*	pElem;
								INFO_ELEM	**	ppElem;
								int				iNewPos,  i;

								//  printInfos(  m_var.ppInfos_sortedByStr,  m_var.infoQ.uiQNodes  );

								memset(  &info,  0,  sizeof(  info  )  );
								memcpy(  &info.when,  &pShowStruct->when,  sizeof(  info.when  )  );
								info.uiStep  =  pShowStruct->uiStep;
								lstrcpyn(  info.wBuf,  tBuf,  mycountof(  info.wBuf  )  );

								/*
								ppElem  =  (  INFO_ELEM  **  )bsearch(  &info,  m_var.ppInfos_sortedByStr,  m_var.infoQ.uiQNodes,  sizeof(  void  *  ),  myCompare_searchInfoByStr  );  
								if  (  ppElem  )  {
									//  traceLogA(  "这表明可能有2条相同的信息,忽略掉了"  );
									break;	//  这表明可能有2条相同的信息,忽略掉了
								}
								*/
								if  (  qPostMsg(  &info,  sizeof(  info  ),  &m_var.infoQ  )  )  goto  errLabel;
								if  (  m_var.infoQ.uiQNodes  <=  1  )  {
									iNewPos  =  0;
									m_var.ppInfos_sortedByTime[iNewPos]  =  m_var.infoQ.pRear->qElemMemory.m_pBuf;
									}
								else  {
									  for  (  i  =  m_var.infoQ.uiQNodes  -  2;  i  >=  0;  i  --  )  {
										   pElem  =  (  INFO_ELEM  *  )m_var.ppInfos_sortedByTime[i];

										   int  iCmp;
										   iCmp  =  iCmpInfoElem(  &info,  pElem  );
										   if  (  iCmp  >=  0  )  {
											   iNewPos  =  i  +  1;
											   m_var.ppInfos_sortedByTime[iNewPos]  =  m_var.infoQ.pRear->qElemMemory.m_pBuf;
											   break;
										   }
										   //  往后移一个
										   m_var.ppInfos_sortedByTime[i  +  1]  =  m_var.ppInfos_sortedByTime[i];									
									  }
									  if  (  i  ==  -1  )  {
										  iNewPos  =  0;
										  //  m_var.ppInfos_sortedByTime[iNewPos]  =  m_var.infoQ.pRear->pQElem;
										  m_var.ppInfos_sortedByTime[iNewPos]  =  m_var.infoQ.pRear->qElemMemory.m_pBuf;
									  }
								}
								GetDlgItem(  IDC_LIST_display  )->SendMessage(  LB_INSERTSTRING,  iNewPos,  (  LPARAM  )(  (  INFO_ELEM  *  )m_var.ppInfos_sortedByTime[iNewPos]  )->wBuf  );

								//  2006/04/16
								if  (  iCurSel  >=  0  )  {
									memset(  &info,  0,  sizeof(  info  )  );
									lstrcpyn(  info.wBuf,  curSelStr,  mycountof(  info.wBuf  )  );

									ppElem  =  (  INFO_ELEM  **  )bsearch(  &info,  m_var.ppInfos_sortedByTime,  m_var.infoQ.uiQNodes,  sizeof(  void  *  ),  myCompare_searchInfoByTime  );  
									if  (  !ppElem  )  break;

									iCurSel  =  (  ppElem  -  (  INFO_ELEM  **  )m_var.ppInfos_sortedByTime  );

									GetDlgItem(  IDC_LIST_display  )->SendMessage(  LB_SETCURSEL,  iCurSel,  0  );
									}
								else  {
									  iCurSel  =  m_var.infoQ.uiQNodes  -  1;
									  GetDlgItem(  IDC_LIST_display  )->SendMessage(  LB_SETCURSEL,  iCurSel,  0  );								
								}
								
								//
								break;
						  case  CONST_qyShowType_serviceStatus:
							    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s%s%s"  ),  pShowStruct->who_from,  pShowStruct->whereBuf,  pShowStruct->doStr,  pShowStruct->what  );
							    if  (  !lstrcmpi(  pShowStruct->who_from,  qyGetDesByType1(  CONST_qyServiceIdTable,  CONST_qyServiceId_is  )  )  )  SetDlgItemText(  IDC_STATIC_serviceStatus_is,  tBuf  );
								else  SetDlgItemText(  IDC_STATIC_serviceStatus_netMc,  tBuf  );
								break;
						  case  CONST_qyShowType_qmdState:
							    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s%s%s"  ),  pShowStruct->who_from,  pShowStruct->whereBuf,  pShowStruct->doStr,  pShowStruct->what  );
								if  (  !lstrcmpi(  pShowStruct->who_from,  qyGetDesByType1(  CONST_qyServiceIdTable,  CONST_qyServiceId_is  )  )  )  SetDlgItemText(  IDC_STATIC_serviceStatus_is,  tBuf  );
								else  SetDlgItemText(  IDC_STATIC_serviceStatus_netMc,  tBuf  );
								break;
												
						  case  CONST_qyShowType_addChkingType:
							    OutputDebugString(  _T(  "addChkingType: 这里不用了\n"  )  );
							    /*
								tTrim(  pShowStruct->who_from  );
							    if  (  !pShowStruct->who_from[0]  )  break;
							    if  (	CB_ERR  !=  GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_FINDSTRING,  -1,  (  LPARAM  )pShowStruct->who_from  )  )  break;
								GetDlgItem(  IDC_COMBO_select  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )pShowStruct->who_from  );
								*/
							    break;					  							    
						  case  CONST_qyShowType_refresh:
							    OutputDebugString(  _T(  "可以刷新状态, 暂时不用\n"  )  );
							    break;
						  default:
							      break;
					}
				  				  
					}
				  break;
			default:					
					break;
	}

	lRet  =  0;

errLabel:

	traceLogA(  "CPpQwmCommStatus::OnQyComm  leaves"  );

	return  lRet;
}

void CDlgQyCommStatus::OnBnClickedRadioqwmcomm()
{
	// TODO: 在此添加控件通知处理程序代码
		m_var.u.showInfo.iShowFlgs[0]  =  (  1  <<  CONST_qyShowType_serviceStatus  )
											|  (  1  <<  CONST_qyShowType_qwmComm  )
												|  (  1  <<  CONST_qyShowType_qmdState  )
													|  (  1  <<  CONST_qyShowType_sysInfo  )
														|  (  1  <<  CONST_qyShowType_debug  )
															|  (  1  <<  CONST_qyShowType_debugWarning  )
																|  (  1  <<  CONST_qyShowType_warning  )  
																	|  (  1  <<  CONST_qyShowType_detail  );

}

void CDlgQyCommStatus::OnBnClickedRadioqnmchking()
{
	// TODO: 在此添加控件通知处理程序代码

	m_var.u.showInfo.iShowFlgs[0]  =  (  1  <<  CONST_qyShowType_serviceStatus  )
											|  (  1  <<  CONST_qyShowType_qnmChking  )
												|  (  1  <<  CONST_qyShowType_addChkingType  );

}

void CDlgQyCommStatus::OnBnClickedRadioscanningip()
{
	// TODO: 在此添加控件通知处理程序代码

	m_var.u.showInfo.iShowFlgs[0]  =  (  1  <<  CONST_qyShowType_scanningNetworkSegment  )
											|  (  1  <<  CONST_qyShowType_scanningIp  )
												|  (  1  <<  CONST_qyShowType_serviceStatus  )
													|  (  1  <<  CONST_qyShowType_refresh  )
														|  (  1  <<  CONST_qyShowType_bhbScanningNetworkSegment  );

}

void CDlgQyCommStatus::OnBnClickedCheckautoclearup()
{
	// TODO: 在此添加控件通知处理程序代码
	if  (  BST_CHECKED  ==  GetDlgItem(  IDC_CHECK_autoClearup  )->SendMessage(  BM_GETCHECK,  0,  0  )  )  {
		m_var.bAutoClearup  =  TRUE;
		}
	else  m_var.bAutoClearup  =  FALSE;

}

void CDlgQyCommStatus::PostNcDestroy()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialog::PostNcDestroy();

	if  (  m_var.ppInfos_sortedByTime  )  free(  m_var.ppInfos_sortedByTime  );
	if  (  m_var.bInfoQInited  )  exitGenericQ(  &m_var.infoQ  );

}
