// public\DlgObjs.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainCommon.h"
#ifndef  __TEST__
		 #include	"ceMenuBar.h"
#endif
#include	"qyMc_winCe.h"
#include	"DlgObjs.h"
#include	"DlgTalk_ce.h"

#include	"qnmResDefs.h"



CDlgObjs::CDlgObjs(  HWND  hParent /*=NULL*/)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CDlgObjs::~CDlgObjs()
{
}



// CDlgObjs message handlers







#if  0
BOOL dlgObjs_OnInitDialog(  HWND  hDlg,  void  *  pVarParam  )
{
	int	iErr	=	-1;
	if  (  !pVarParam  )  goto  errLabel;
	DLG_objs_var	&	m_var  =  *(  DLG_objs_var  *  )pVarParam;

	centerWnd(  hDlg  );

	// TODO:  Add extra initialization here
	dlgObjs_bFillContent(  hDlg,  pVarParam,  m_var.guiData.param.uiType  );

	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		EndDialog(  hDlg,  -1  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
#endif





#if  0
 __declspec(  dllexport  )BOOL  myDialogProc_objs(  void  *  pDlgParam,  HWND hDlg,  UINT uMsg,  WPARAM wParam,  LPARAM lParam  )
{
	CDlgObjs  *  pDlg  =  (  CDlgObjs  *  )pDlgParam;	//  GetWindowLong(  hDlg,  GWLP_USERDATA  );

	UNREFERENCED_PARAMETER(lParam);
	switch  (  uMsg  )  {
		    case  WM_INITDIALOG:  {
				  //  pDlg  =  (  CDlg_qyMc_winCe  *  )lParam;
				  //  pDlg->Attach(  hDlg  );
				  qyWnd_Attach(  pDlg,  hDlg  );
#if  10
				  dlgObjs_OnInitDialog(  hDlg,  qyWnd_getVar(  pDlg  )  );		
#endif
				  }					
				  return (INT_PTR)TRUE;
			case  CONST_qyWm_postComm:
#if  10
#endif
				  return  TRUE;
				  break;

			case  WM_COMMAND:  {
				  WORD  wNotifyCode = HIWORD(wParam); 
				  WORD  wID = LOWORD(wParam); 
				  HWND  hwndCtl = (HWND) lParam;

				  if  (  wID  ==  IDCANCEL  )  {
					  EndDialog(  hDlg,  wID  );
					  return  TRUE;
				  }
				  if  (  wID  ==  IDOK  )  {
					  pDlg->OnOK(  );
					  return (INT_PTR)TRUE;
				  }
				  if  (  wID  ==  pDlg->m_var.guiData.iIDC_BUTTON_contact  )  {
					  dlgObjs_bFillContent(  hDlg,  qyWnd_getVar(  pDlg  ),  CONST_objType_messenger  );
					  return  TRUE;
				  }
				  if  (  wID  ==  pDlg->m_var.guiData.iIDC_BUTTON_group  )  {
					  dlgObjs_bFillContent(  hDlg,  qyWnd_getVar(  pDlg  ),  CONST_objType_imGrp  );
					  return  TRUE;
				  }
				  if  (  wID  ==  pDlg->m_var.guiData.iIDC_BUTTON_status  )  {
					  dlgObjs_bFillContent(  hDlg,  qyWnd_getVar(  pDlg  ),  0  );
					  return  TRUE;
				  }

				  }
				  break;
			case  WM_TIMER:
				  return  TRUE;
				  break;
			case  WM_DESTROY:
#if  10
#endif
				  break;
			default:
					break;
	}
	return (INT_PTR)FALSE;
}
#endif


