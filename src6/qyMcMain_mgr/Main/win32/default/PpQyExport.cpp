// PpQyExport.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyMc.h"
#include	"PpQyExport.h"
#include	"qyPs.h"
#include ".\ppqyexport.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPpQyExport property page

IMPLEMENT_DYNCREATE(CPpQyExport, CPropertyPage)

CPpQyExport::CPpQyExport() : CPropertyPage(CPpQyExport::IDD)
{
	//{{AFX_DATA_INIT(CPpQyExport)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPpQyExport::~CPpQyExport()
{
}

void CPpQyExport::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpQyExport)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPpQyExport, CPropertyPage)
	//{{AFX_MSG_MAP(CPpQyExport)
	ON_BN_CLICKED(IDC_RADIO_exportCurQuery, OnRADIOexportCurQuery)
	ON_BN_CLICKED(IDC_RADIO_exportRegInfo, OnRADIOexportRegInfo)
	ON_BN_CLICKED(IDC_RADIO_exportCfg, OnRADIOexportCfg)
	ON_BN_CLICKED(IDC_RADIO_exportBhbCfg, OnRADIOexportBhbCfg)
	ON_BN_CLICKED(IDC_RADIO_exportBakData, OnRADIOexportBakData)
	ON_BN_CLICKED(IDC_RADIO_procDj, OnRADIOprocDj)
	ON_BN_CLICKED(IDC_RADIO_procDj98, OnBnClickedRadioprocdj98)
	ON_BN_CLICKED(IDC_RADIO_procModuleKnowlege, OnRADIOprocModuleKnowlege)
	ON_BN_CLICKED(IDC_RADIO_procRegistryKnowlege, OnRADIOprocRegistryKnowlege)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_RADIO_procIpKnowledge, OnBnClickedRadioprocipknowledge)
	ON_BN_CLICKED(IDC_RADIO_procPhoneGuest, OnBnClickedRadioprocphoneguest)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpQyExport message handlers

BOOL CPpQyExport::OnSetActive() 
{
	QY_MC			*	pQyMc	=	QY_GET_GBUF(  );
	CQyPs			*	pPs  =  (  CQyPs  *  )GetParent(  );
	unsigned  char		ucbExportCurQueryShow				=	pPs->m_var.iType  ==  CONST_qyPsType_export  ?  TRUE  :  FALSE;
	unsigned  char		ucbExportRegInfoShow				=	FALSE;	//  TRUE;
	unsigned  char		ucbExportBhbCfgShow					=	FALSE;
	unsigned  char		ucbExportBakDataShow				=	TRUE;
	unsigned  char		ucbProcDjShow						=	FALSE;
	unsigned  char		ucbProcDj98Show						=	FALSE;
	unsigned  char		ucbProcModuleKnowledgeShow			=	FALSE;
	unsigned  char		ucbProcRegistryKnowledgeShow		=	FALSE;
	unsigned  char		ucbProcIpKnowledgeShow				=	FALSE;
	unsigned  char		ucbProcPhoneGuestShow				=	FALSE;
				  

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );


	switch  (  qyGetSystemId(  )  )  {
			case  CONST_qySystemId_bhb:
				  //  ucbExportCurQueryShow  =  (  pQyMc->iAppType  ==  CONST_qyAppType_null  )  ?  FALSE  :  TRUE;
				  ucbExportRegInfoShow  =  FALSE;
				  ucbExportBhbCfgShow  =  (  pQyMc->iAppType  ==  CONST_qyAppType_null  )  ?  TRUE  :  FALSE;
				  ucbExportBakDataShow  =    (  pQyMc->iAppType  ==  CONST_qyAppType_null  )  ?  TRUE  :  FALSE;  
				  break;
			case  CONST_qySystemId_secChk:
				  GetDlgItem(  IDC_RADIO_exportRegInfo  )->ShowWindow(  SW_SHOW  );				  
				  if  (  pQyMc->cfg.ucbHaveDj   )  {
					  ucbProcDjShow  =  TRUE;
				  	  if  (  pPs->m_var.iType  ==  CONST_qyPsType_export  )  ucbProcDj98Show  =  TRUE;
				  }
				  if  (  pPs->m_var.iType  ==  CONST_qyPsType_export  )  {
					  SetDlgItemText(  IDC_RADIO_procDj,  _T(  "批量导出单机安检工具, 仅用于2000以上系统，导出目录应在NTFS文件系统中"  )  );
					  SetDlgItemText(  IDC_RADIO_procDj98,  _T(  "批量导出单机安检工具, 仅用于98系统，导出目录应在FAT文件系统中"  )  );
				  }
				  break;
			case  CONST_qySystemId_netMc2:
				  ucbProcModuleKnowledgeShow  =  TRUE;
				  ucbProcRegistryKnowledgeShow  =  TRUE;
				  break;
			case  CONST_qySystemId_messenger:
				  if  (  pQyMc->iAppType  ==  CONST_qyAppType_null  )  {
					  //  ucbProcIpKnowledgeShow  =  TRUE;
					  }
				  else  {
					    ucbProcPhoneGuestShow  =  TRUE;
				  }
				  break;
			default:				   
					break;
	}

	if  (  pQyMc->curUsrInfo.scope.bRestricted  )  {
		ucbExportBakDataShow			=	FALSE;		
	}

	if  (  pPs->m_var.bProcCurQueryOnly  )  {
	
		ucbExportRegInfoShow			=	FALSE;
		ucbExportBhbCfgShow				=	FALSE;
		ucbExportBakDataShow			=	FALSE;
		ucbProcDjShow					=	FALSE;
		ucbProcDj98Show					=	FALSE;
		ucbProcModuleKnowledgeShow		=	FALSE;
		ucbProcRegistryKnowledgeShow	=	FALSE;
		ucbProcIpKnowledgeShow			=	FALSE;
		ucbProcPhoneGuestShow			=	FALSE;
	
	}


	GetDlgItem(  IDC_RADIO_exportCurQuery  )->ShowWindow(  ucbExportCurQueryShow  ?  SW_SHOW  :  SW_HIDE  );
	GetDlgItem(  IDC_RADIO_exportRegInfo  )->ShowWindow(  ucbExportRegInfoShow  ?  SW_SHOW  :  SW_HIDE  );
	GetDlgItem(  IDC_RADIO_exportBhbCfg  )->ShowWindow(  ucbExportBhbCfgShow  ?  SW_SHOW  :  SW_HIDE  );
	GetDlgItem(  IDC_RADIO_exportBakData  )->ShowWindow(  ucbExportBakDataShow  ?  SW_SHOW  :  SW_HIDE  );
	GetDlgItem(  IDC_RADIO_procDj  )->ShowWindow(  ucbProcDjShow  ?  SW_SHOW  :  SW_HIDE  );
	GetDlgItem(  IDC_RADIO_procDj98  )->ShowWindow(  ucbProcDj98Show  ?  SW_SHOW  :  SW_HIDE  );
	GetDlgItem(  IDC_RADIO_procModuleKnowlege  )->ShowWindow(  ucbProcModuleKnowledgeShow  ?  SW_SHOW  :  SW_HIDE  );
	GetDlgItem(  IDC_RADIO_procRegistryKnowlege  )->ShowWindow(  ucbProcRegistryKnowledgeShow  ?  SW_SHOW  :  SW_HIDE  );
	GetDlgItem(  IDC_RADIO_procIpKnowledge  )->ShowWindow(  ucbProcIpKnowledgeShow  ?  SW_SHOW  :  SW_HIDE  );
	GetDlgItem(  IDC_RADIO_procPhoneGuest  )->ShowWindow(  ucbProcPhoneGuestShow  ?  SW_SHOW  :  SW_HIDE  );
	

	if  (  pPs->m_var.iType  ==  CONST_qyPsType_export  )  {
		QY_IMEXPORTINFO	*  pExportInfo  =  &pPs->m_var.u.imExportInfo;
		
		if  (  !pExportInfo->hCurWnd  )  {
			GetDlgItem(  IDC_RADIO_exportCurQuery  )->EnableWindow(  FALSE  );
			pPs->SetWizardButtons(  PSWIZB_DISABLEDFINISH  );
			}
		else  {
			  GetDlgItem(  IDC_RADIO_exportCurQuery  )->SendMessage(  BM_SETCHECK ,  BST_CHECKED,  0  );
			  pPs->SetWizardButtons(  PSWIZB_FINISH  );
		}
		}
	else  if  (  pPs->m_var.iType  ==  CONST_qyPsType_import  )  {

		      SetDlgItemText(  IDC_STATIC_hint,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectContentOfImport  )  );
			  SetDlgItemText(  IDC_RADIO_exportBakData,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_importBakData  )  );
			  SetDlgItemText(  IDC_RADIO_exportRegInfo,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_importRegInfo  )  );
			  SetDlgItemText(  IDC_RADIO_exportBhbCfg,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_importBhbInfo  )  );

			  pPs->SetWizardButtons(  PSWIZB_DISABLEDFINISH  );
		    
			}
	else
		pPs->PostMessage(  WM_CLOSE,  0,  0  );
		
	return CPropertyPage::OnSetActive();
}


void CPpQyExport::OnRADIOexportCurQuery() 
{
	CQyPs		*	pPs  =  (  CQyPs  *  )GetParent(  );

	pPs->SetWizardButtons(  PSWIZB_FINISH  );
	
}

void CPpQyExport::OnRADIOexportBakData() 
{
	CQyPs		*	pPs  =  (  CQyPs  *  )GetParent(  );

	pPs->SetWizardButtons(  PSWIZB_FINISH  );
}


 void CPpQyExport::OnRADIOexportRegInfo() 
{
	CQyPs		*	pPs  =  (  CQyPs  *  )GetParent(  );

	pPs->SetWizardButtons(  PSWIZB_FINISH  );
}

 void CPpQyExport::OnRADIOexportCfg() 
{
	CQyPs		*	pPs  =  (  CQyPs  *  )GetParent(  );

	pPs->SetWizardButtons(  PSWIZB_FINISH  );
	
}

 void CPpQyExport::OnRADIOexportBhbCfg() 
{
	CQyPs		*	pPs  =  (  CQyPs  *  )GetParent(  );

	pPs->SetWizardButtons(  PSWIZB_FINISH  );
	
}

 

 void CPpQyExport::OnRADIOprocDj() 
{
	// TODO: Add your control notification handler code here
	CQyPs		*	pPs  =  (  CQyPs  *  )GetParent(  );

	pPs->SetWizardButtons(  PSWIZB_FINISH  );
	
}

void CPpQyExport::OnBnClickedRadioprocdj98()
{
	// TODO: 在此添加控件通知处理程序代码
	CQyPs		*	pPs  =  (  CQyPs  *  )GetParent(  );

	pPs->SetWizardButtons(  PSWIZB_FINISH  );
}


 void CPpQyExport::OnRADIOprocModuleKnowlege() 
{
	// TODO: Add your control notification handler code here
	CQyPs		*	pPs  =  (  CQyPs  *  )GetParent(  );

	pPs->SetWizardButtons(  PSWIZB_FINISH  );
	
}

void CPpQyExport::OnRADIOprocRegistryKnowlege() 
{
	// TODO: Add your control notification handler code here
	CQyPs		*	pPs  =  (  CQyPs  *  )GetParent(  );

	pPs->SetWizardButtons(  PSWIZB_FINISH  );
	
}

void CPpQyExport::OnBnClickedRadioprocipknowledge()
{
	// TODO: 在此添加控件通知处理程序代码
	CQyPs		*	pPs  =  (  CQyPs  *  )GetParent(  );

	pPs->SetWizardButtons(  PSWIZB_FINISH  );

}


void CPpQyExport::OnBnClickedRadioprocphoneguest()
{
	// TODO: 在此添加控件通知处理程序代码
	CQyPs		*	pPs  =  (  CQyPs  *  )GetParent(  );

	pPs->SetWizardButtons(  PSWIZB_FINISH  );
}


BOOL CPpQyExport::OnWizardFinish() 
{

	CQyPs			*	pPs  =  (  CQyPs  *  )GetParent(  );
	QY_IMEXPORTINFO	*	pExportInfo  =  &pPs->m_var.u.imExportInfo;

	if  (  GetDlgItem(  IDC_RADIO_exportCurQuery  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  {
		pExportInfo->iTask  =  CONST_qyPsTask_procCurQuery;
		}
	//  else  if  (  GetDlgItem(  IDC_RADIO_exportRegInfo  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  {
	//		  pExportInfo->iTask  =  CONST_qyPsTask_procRegInfo;
	//		}
	//  else  if  (  GetDlgItem(  IDC_RADIO_exportCfg  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  {
	//		  pExportInfo->iTask  =  CONST_qyPsTask_procCfg;
	//		}
	else  if  (  GetDlgItem(  IDC_RADIO_exportBhbCfg  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  {
			  pExportInfo->iTask  =  CONST_qyPsTask_procBhbCfg;
			}
	else  if  (  GetDlgItem(  IDC_RADIO_exportBakData  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  {
			  pExportInfo->iTask  =  CONST_qyPsTask_procBakData;
			}
	else  if  (  GetDlgItem(  IDC_RADIO_procDj  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  {
			  pExportInfo->iTask  =  CONST_qyPsTask_procDjData;
			}
	else  if  (  GetDlgItem(  IDC_RADIO_procDj98  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  {
		      pExportInfo->iTask  =  CONST_qyPsTask_procDj98;
			}
	else  if  (  GetDlgItem(  IDC_RADIO_procModuleKnowlege  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  {
			  pExportInfo->iTask  =  CONST_qyPsTask_procPcProcessKnowledge;
			}
	else  if  (  GetDlgItem(  IDC_RADIO_procRegistryKnowlege  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  {
			  pExportInfo->iTask  =  CONST_qyPsTask_procPcRegistryKnowledge;
			}
	else  if  (  GetDlgItem(  IDC_RADIO_procIpKnowledge  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  {
			  pExportInfo->iTask  =  CONST_qyPsTask_procIpKnowledge;
			}
	else  if  (  GetDlgItem(  IDC_RADIO_procPhoneGuest  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  {
			  pExportInfo->iTask  =  CONST_qyPsTask_procPhoneGuest;
	}

	
	return CPropertyPage::OnWizardFinish();
}










