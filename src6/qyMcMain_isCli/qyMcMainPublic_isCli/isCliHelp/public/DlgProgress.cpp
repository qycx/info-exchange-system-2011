// DlgProgress.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"myresource.h"
#include	"DlgProgress.h"
#include	"qmcCmdProc.h"



__declspec(dllexport)  int  showDlgProgress(  HWND  hParent,  LPCTSTR  title,  LPCTSTR  progressTxt,  int  nStep_finished,  int  iIndex_shmCmd,  unsigned  int  uiTranNo,  BOOL  canUsrOk,  PF_commonHandler  pf_doProgress  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int				iRet	=	-1;
	CDlgProgress	dlg(  CWnd::FromHandle(  hParent  )  );
	
	dlg.bSetDlgInfo(  _T(  "Please waiting"  ),  NULL,  30,  -1,  uiTranNo  ); 
	
	//  traceLogA(  "if task is not ready, cancel the task by clear shmCmd, and the subprocess will quit when it read the shmCmd."  );	
	if  (  dlg.DoModal(  )  !=  IDOK  )  {
		goto  errLabel;		
	}

	iRet  =  IDOK;

errLabel:		
	return  iRet;	
}


// CDlgProgress dialog

IMPLEMENT_DYNAMIC(CDlgProgress, CDialog)

CDlgProgress::CDlgProgress(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProgress::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CDlgProgress::~CDlgProgress()
{
}


BOOL	CDlgProgress::bSetDlgInfo(  LPCTSTR  title,  LPCTSTR  progressTxt,  int  nStep_finished,  int  iIndex_shmCmd,  unsigned  int  uiTranNo,  BOOL  canUsrOk,  PF_commonHandler  pf_doProgress  )
{
	if  (  title  )  lstrcpyn(  m_var.title,  title,  mycountof(  m_var.title  )  );
	if  (  progressTxt  )  lstrcpyn(  m_var.progressTxt,  progressTxt,  mycountof(  m_var.progressTxt  )  );
	m_var.nStep_finished  =  nStep_finished;
	m_var.iIndex_shmCmd  =  iIndex_shmCmd;
	m_var.uiTranNo  =  uiTranNo;
	m_var.canUsrOk  =  canUsrOk;
	m_var.pf_doProgress  =  pf_doProgress;
	
	return  TRUE;
}

BOOL	CDlgProgress::bQuitDlg(  int  nResult  )
{
	EndDialog(  nResult  );
	return  TRUE;
}

void CDlgProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgProgress, CDialog)
	ON_WM_TIMER()
	ON_MESSAGE(CONST_qyWm_postComm, OnQyPostComm)
END_MESSAGE_MAP()


// CDlgProgress message handlers

BOOL CDlgProgress::OnInitDialog()
{
	CDialog::OnInitDialog();
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli			*	pProcInfo	=	QY_GET_procInfo_isCli(  );	//  (  MC_VAR_isCli  *  )pSci->pVar;
	if  (  !pProcInfo  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "dlgProgress::OnInitDialog failed, pProcInfo is null"  )  );
		#endif
		return  FALSE;
	}

	// TODO:  Add extra initialization here
	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	QM_SHM_CMD	*	pShmCmd	=	getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  m_var.iIndex_shmCmd  );
	if  (  pShmCmd  )  {
		pShmCmd->hWnd_progress  =  this->m_hWnd;
		//
		if  (  pShmCmd->ucbShmCmdInited  )  
		{
			this->bQuitDlg(  IDOK  );  return  FALSE;
		}
	}
	if  (  pProcInfo->status.progress.uiTranNo  &&  pProcInfo->status.progress.uiTranNo  ==  m_var.uiTranNo  )  {
		pProcInfo->status.progress.hWnd  =  this->m_hWnd;
	}

	SetWindowText(  m_var.title  );				//  È±Ê¡£ºregTool
			
	if  (  !m_var.nStep_finished  )  m_var.nStep_finished  =  100;
	::SendMessage(  GetDlgItem(  IDC_PROGRESS  )->m_hWnd,  PBM_SETRANGE,  0,  myMAKELPARAM(  0,  m_var.nStep_finished  )  );
	::SendMessage(  GetDlgItem(  IDC_PROGRESS  )->m_hWnd,  PBM_SETSTEP,  1,  0  );

	m_var.uiTimerId  =  SetTimer(  1,  1000,  NULL  );

	if  (  !m_var.canUsrOk  )  {
		GetDlgItem(  IDOK  )->EnableWindow(  FALSE  );
	}

	if  (  m_var.pf_doProgress  )  m_var.pf_doProgress(  0,  GetParent(  ),  this  );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgProgress::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	m_var.iProgress  ++  ;

	if  (  m_var.pf_doProgress  )  {
		if  (  m_var.pf_doProgress(  0,  GetParent(  ),  this  )  )  return;
	}

	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  pProcInfo  )  {
		if  (  pProcInfo->status.progress.uiTranNo  
			&&  pProcInfo->status.progress.uiTranNo  ==  m_var.uiTranNo  
			&&  pProcInfo->status.progress.ucbProgessEnd  )  
		{
			#if  1
				 pProcInfo->debugInfo.nStep_progress  =  53;
			#endif
			//
			bQuitDlg(  IDOK  );
			return;
		}
	}

	if  (  m_var.iProgress  >=  m_var.nStep_finished  )  {
		bQuitDlg(  IDCANCEL  );
		return;
	}

	SetDlgItemText(  IDC_STATIC_progress,  m_var.progressTxt  );
	::SendMessage(  GetDlgItem(  IDC_PROGRESS  )->m_hWnd,  PBM_SETPOS,  m_var.iProgress,  0  );							   

	CDialog::OnTimer(nIDEvent);
}

LRESULT CDlgProgress::OnQyPostComm(  WPARAM  wParam, LPARAM  lParam  )
{
	LONG				lRet			=	-1;

	switch  (  wParam  )  {
			case  CONST_qyWmParam_notifyQmShmCmdStatus:  {
				  MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
				  if  (  !pProcInfo  )  goto  errLabel;
				  QM_SHM_CMD	*	pShmCmd	=	getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  m_var.iIndex_shmCmd  );
				  if  (  lParam  &&  lParam  ==  pShmCmd->uiTranNo_sharedObj  )  {
					  #if  1
							pProcInfo->debugInfo.nStep_progress  =  100;
					  #endif
					  //
					  this->bQuitDlg(  IDOK  );
					  return  0;
				  }
				  }
				  break;
			case  CONST_qyWmParam_notifyProgressEnd:	//  2010/08/14
				  if  (  lParam  &&  lParam  ==  m_var.uiTranNo  )  {
					  bQuitDlg(  IDOK  );
					  return  0;
				  }
				  break;
			default:
					break;
	}

	lRet  =  QY_RC_WMOK;

errLabel:

	return	lRet;

}
