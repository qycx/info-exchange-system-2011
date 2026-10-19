// DlgMessageBox.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyCommon.h"
#include	"myresource.h"
#include	"DlgMessageBox.h"
#include	"afxdialogex.h"

#include	"qyGuiHelpPublic.h"


__declspec(  dllexport  )  int  WINAPI  qyMessageBox(  HWND hWnd ,  LPCWSTR lpText,  LPCWSTR lpCaption,  UINT uType,  UINT  nTimeoutInS,  BOOL  *  pbSyncFlg  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int				iRet	=	IDCANCEL;
	CDlgMessageBox	dlg(  CWnd::FromHandle(  hWnd  )  );

	if  (  pbSyncFlg  )  {
		if  (  *pbSyncFlg  )  {
			#ifdef  __DEBUG__
					traceLog(  _T(  "qyMessageBox failed, syncFlg err"  )  );
			#endif				
			return  IDCANCEL;
		}
		*pbSyncFlg  =  TRUE;
	}

	//
	nTimeoutInS  =  10;
#ifdef  __DEBUG__
		nTimeoutInS  =  30;
#endif

	dlg.bSetDlgInfo(  lpText,  lpCaption,  uType,  nTimeoutInS  );
	iRet  =  dlg.DoModal(  );

errLabel:

	if  (  pbSyncFlg  )  {
		*pbSyncFlg  =  FALSE;
	}
	return  iRet;
}


// CDlgMessageBox dialog

IMPLEMENT_DYNAMIC(CDlgMessageBox, CDialog)

CDlgMessageBox::CDlgMessageBox(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMessageBox::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CDlgMessageBox::~CDlgMessageBox()
{
}


BOOL  CDlgMessageBox::bSetDlgInfo(  LPCTSTR  lpText,  LPCTSTR  lpCaption,  UINT  uType,  UINT  nTimeoutInS  )
{
	BOOL	bRet	=	FALSE;

	if  (  !nTimeoutInS  ||  nTimeoutInS  >  30  )  nTimeoutInS  =  30;

	safeTcsnCpy(  lpText,  m_var.hint,  mycountof(  m_var.hint  )  );
	safeTcsnCpy(  lpCaption,  m_var.title,  mycountof(  m_var.title  )  );
	m_var.uType  =  uType;
	//
	m_var.nTimeoutInS  =  nTimeoutInS;


	bRet  =  TRUE;
errLabel:

	return  bRet;

}


BOOL  CDlgMessageBox::bQuitDlg(  int  nResult  )
{
	EndDialog(  nResult  );
	return  TRUE;
}


void CDlgMessageBox::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgMessageBox, CDialog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CDlgMessageBox::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_no, &CDlgMessageBox::OnBnClickedButtonno)
END_MESSAGE_MAP()


// CDlgMessageBox message handlers


BOOL CDlgMessageBox::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	switch  (  m_var.uType  &  0xff  )  {
			case  MB_YESNOCANCEL:
				  SetDlgItemText(  IDOK,  _T(  "Yes"  )  );
				  SetDlgItemText(  IDC_BUTTON_no,  _T(  "No"  )  );
				  SetDlgItemText(  IDCANCEL,  _T(  "Cancel"  )  );
				  break;
			case  MB_YESNO:
				  SetDlgItemText(  IDOK,  _T(  "Yes"  )  );
				  SetDlgItemText(  IDC_BUTTON_no,  _T(  "No"  )  );
				  GetDlgItem(  IDCANCEL  )->ShowWindow(  SW_HIDE  );
				  break;
			case  MB_OKCANCEL:
				  SetDlgItemText(  IDOK,  _T(  "OK"  )  );
				  GetDlgItem(  IDC_BUTTON_no  )->ShowWindow(  SW_HIDE  );
				  SetDlgItemText(  IDCANCEL,  _T(  "Cancel"  )  );
				  break;
			default:
				  SetDlgItemText(  IDOK,  _T(  "OK"  )  );
				  GetDlgItem(  IDC_BUTTON_no  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDCANCEL  )->ShowWindow(  SW_HIDE  );
				  break;
	}

	switch  (  m_var.uType  &  0xf00  )  {
			case  MB_DEFBUTTON2:
				  if  (  GetDlgItem(  IDC_BUTTON_no  )->IsWindowVisible(  )  )  GetDlgItem(  IDC_BUTTON_no  )->SetFocus(  );
				  else  GetDlgItem(  IDCANCEL  )->SetFocus(  );
				  break;
			case  MB_DEFBUTTON3:
				  GetDlgItem(  IDCANCEL  )->SetFocus(  );
				  break;
			case  MB_DEFBUTTON1:
			default:
					break;
	}

	//
	TCHAR	tBuf[128];
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s...Auto canceled  after %d seconds.."  ),  m_var.title,  m_var.nTimeoutInS  -  m_var.uProgress  );
	SetWindowText(  tBuf  );

	SetDlgItemText(  IDC_STATIC_hint,  m_var.hint  );

	//
	m_var.uiTimerId  =  SetTimer(  1,  1000,  NULL  );

errLabel:

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgMessageBox::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	m_var.uProgress  ++  ;

	if  (  m_var.uProgress  >=  m_var.nTimeoutInS  )  {
		bQuitDlg(  IDCANCEL  );
		return;
	}

	TCHAR	tBuf[128];
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s...Auto canceled  after %d seconds.."  ),  m_var.title,  m_var.nTimeoutInS  -  m_var.uProgress  );
	SetWindowText(  tBuf  );


	CDialog::OnTimer(nIDEvent);
}


void CDlgMessageBox::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	switch  (  m_var.uType  &  0xff  )  {
			case  MB_YESNOCANCEL:
			case  MB_YESNO:
				  bQuitDlg(  IDYES  );
				  return;
				  break;
			default:
				  break;
	}

	CDialog::OnOK();
}


void CDlgMessageBox::OnBnClickedButtonno()
{
	// TODO: Add your control notification handler code here
	bQuitDlg(  IDNO  );
}


