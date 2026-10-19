// DlgImGrp.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgImGrp.h"
#include	"qyCusResTemp.h"
#include ".\dlgimgrp.h"
#include	"myDb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgImGrp dialog


CDlgImGrp::CDlgImGrp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgImGrp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgImGrp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


BOOL  CDlgImGrp::bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  )
{  
	if  (  !pObjDb  ||  !misServName  ||  !pIdInfo  )  return  FALSE;

	m_var.iDlgType  =  iDlgType; 
	m_var.pObjDb  =  pObjDb;  
	lstrcpyn(  m_var.misServName,  misServName,  mycountof(  m_var.misServName  )  );  
	m_var.idInfo.ui64Id  =  pIdInfo->ui64Id;

	return  TRUE;
}


void CDlgImGrp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgImGrp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgImGrp, CDialog)
	//{{AFX_MSG_MAP(CDlgImGrp)
	//}}AFX_MSG_MAP
	//	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgImGrp message handlers

void CDlgImGrp::OnOK() 
{
	// TODO: Add extra validation here
	QY_MC				*	pQyMc									=	QY_GET_GBUF(  );
	CString					nameStr;
	static  BOOL			bFirstPrompted							=	FALSE;

	GetDlgItemText(  IDC_EDIT_name,  nameStr  );
	MACRO_CStringTrim(  nameStr  );
	if  (  !nameStr.GetLength(  )  )  {
		AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_grpNameCannotEmpty  )/*_T(  "请输入组名以方便识别"  )*/  );
		return;
	}

	if  (  m_var.iDlgType  !=  CONST_qyDlgType_modify  )  {
		if  (  applyForServWork(  CONST_imCommType_newImGrp,  (  void  *  )nameStr.GetBuffer(  0  ),  0,  0  )  )  {
			AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_createGroupFailed  )  );  return;
		}
		if  (  !bFirstPrompted  )  {
			bFirstPrompted  =  TRUE;
			AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_hintToAddMember  )  );
		}
		}
	else  {
		  if  (  lstrcmpi(  nameStr,  m_var.rcd.name  )  )  {
			  lstrcpyn(  m_var.rcd.name,  nameStr,  mycountof(  m_var.rcd.name  )  );
			  if  (  recoverImGrp(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  CONST_objType_imGrp,  &m_var.rcd,  0  )  )  {
				  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_modifyGroupNameFailed  )  );  return;
			  }
		  }
	
	}
//  errLabel:

	CDialog::OnOK();
}

BOOL CDlgImGrp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int					iErr				=	-1;
	QY_MC	*			pQyMc				=	QY_GET_GBUF(  );
	TCHAR				tBuf[255  +  1]		=	_T(  ""  );


	QM_dbFuncs  *  pDbFuncs  =  QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	if  (  m_var.iDlgType  !=  CONST_qyDlgType_modify  )  {
        _sntprintf(  tBuf,  mycountof(  tBuf  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_hintToCreateGroup  )  );
		}
	else  {
		   _sntprintf(  tBuf,  mycountof(  tBuf  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_hintToModifyGroup  )  );

		   if  (  !g_dbFuncs.pf_bGetImGrpInfoBySth(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  m_var.misServName,  &m_var.idInfo,  &m_var.rcd  )  )  {
			   memset(  &m_var.rcd,  0,  sizeof(  m_var.rcd  )  );
			   lstrcpyn(  m_var.rcd.misServName,  m_var.misServName,  mycountof(  m_var.rcd.misServName  )  );
			   m_var.rcd.idInfo.ui64Id  =  m_var.idInfo.ui64Id;
		   }

		   SetDlgItemText(  IDC_EDIT_name,  m_var.rcd.name  );

	}
	SetDlgItemText(  IDC_STATIC_hint,  tBuf  );

	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		PostMessage(  WM_CLOSE  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
