// PpExportClients.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"myresource.h"
#include	"PpExportClients.h"
#include	"qyPs.h"


// CPpExportClients dialog

IMPLEMENT_DYNAMIC(CPpExportClients, CPropertyPage)

CPpExportClients::CPpExportClients()
	: CPropertyPage(CPpExportClients::IDD)
{

}

CPpExportClients::~CPpExportClients()
{
}

void CPpExportClients::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPpExportClients, CPropertyPage)
	ON_BN_CLICKED(IDC_RADIO_default, &CPpExportClients::OnBnClickedRadiodefault)
	ON_BN_CLICKED(IDC_RADIO_ts_logon, &CPpExportClients::OnBnClickedRadiotslogon)
	ON_BN_CLICKED(IDC_RADIO_ts_dev, &CPpExportClients::OnBnClickedRadiotsdev)
END_MESSAGE_MAP()


// CPpExportClients message handlers

void CPpExportClients::OnBnClickedRadiodefault()
{
	// TODO: Add your control notification handler code here
	CQyPs		*	pPs  =  (  CQyPs  *  )GetParent(  );

	pPs->SetWizardButtons(  PSWIZB_FINISH  );
}

void CPpExportClients::OnBnClickedRadiotslogon()
{
	// TODO: Add your control notification handler code here
	CQyPs		*	pPs  =  (  CQyPs  *  )GetParent(  );

	pPs->SetWizardButtons(  PSWIZB_FINISH  );
}

void CPpExportClients::OnBnClickedRadiotsdev()
{
	// TODO: Add your control notification handler code here
	CQyPs		*	pPs  =  (  CQyPs  *  )GetParent(  );

	pPs->SetWizardButtons(  PSWIZB_FINISH  );
}

BOOL CPpExportClients::OnSetActive()
{
	// TODO: Add your specialized code here and/or call the base class
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	if  (  !bSupported_devAuth(  )  )  {
		GetDlgItem(  IDC_RADIO_ts_logon  )->ShowWindow(  SW_HIDE  );
		GetDlgItem(  IDC_RADIO_ts_dev  )->ShowWindow(  SW_HIDE  );
	}

	if  (  bSupported_devAuth(  )  )  {
		if  (  bQnmDemo(  )  )  {
			GetDlgItem(  IDC_RADIO_default  )->ShowWindow(  SW_HIDE  );
			GetDlgItem(  IDC_RADIO_ts_dev  )->ShowWindow(  SW_HIDE  );
		}
	}


#if  1	//  2013/03/07
		#ifdef  __DEBUG__
				traceLog(  _T(  "devAuth is not supported, IDC_RADIO_ts_dev is hidden"  )  );
		#endif
		GetDlgItem(  IDC_RADIO_ts_dev  )->ShowWindow(  SW_HIDE  );
#endif
	

	return CPropertyPage::OnSetActive();
}

BOOL CPpExportClients::OnWizardFinish()
{
	CQyPs			*	pPs  =  (  CQyPs  *  )GetParent(  );
	QY_IMEXPORTINFO	*	pExportInfo  =  &pPs->m_var.u.imExportInfo;

	// TODO: Add your specialized code here and/or call the base class
	if  (  GetDlgItem(  IDC_RADIO_default  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  {
		pExportInfo->iTask  =  CONST_qyPsTask_exportClient_default;
		}
	else  if  (  GetDlgItem(  IDC_RADIO_ts_logon  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  {
			  pExportInfo->iTask  =  CONST_qyPsTask_exportClient_ts_logon;
	}
	else  if  (  GetDlgItem(  IDC_RADIO_ts_dev  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  {
			  pExportInfo->iTask  =  CONST_qyPsTask_exportClient_ts_dev;
	}

	return CPropertyPage::OnWizardFinish();
}
