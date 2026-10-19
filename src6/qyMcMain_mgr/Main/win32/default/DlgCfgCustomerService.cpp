// DlgCfgCustomerService.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyMc.h"
#include	"DlgCfgCustomerService.h"
#include	"qyCusResTemp.h"


// CDlgCfgCustomerService dialog

IMPLEMENT_DYNAMIC(CDlgCfgCustomerService, CDialog)

CDlgCfgCustomerService::CDlgCfgCustomerService(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCfgCustomerService::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CDlgCfgCustomerService::~CDlgCfgCustomerService()
{
}

 BOOL  CDlgCfgCustomerService::bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  id  )
{
	 BOOL						bRet	=	FALSE;
	 QY_MC					*	pQyMc	=	QY_GET_GBUF(  );

	 if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;

	 m_var.pObjDb  =  pObjDb;	//  2007/01/02

	 if  (  misServName  &&  pIdInfo  )  {
		 
		 lstrcpyn(  m_var.misServName,  misServName,  mycountof(  m_var.misServName  )  );
		 m_var.idInfo.ui64Id  =  pIdInfo->ui64Id;

		 if  (  !bGetCustomerServiceObjRcdBySth(  m_var.pObjDb->pDb,  pObjDb->cfg.iDbType,  misServName,  pIdInfo,  0,  &m_var.oldRcd  )  )  memset(  &m_var.oldRcd,  0,  sizeof(  m_var.oldRcd  )  );

		}
	 else  {
		   m_var.id  =  id;
		 
		   if  (  !bGetCustomerServiceObjRcdBySth(  m_var.pObjDb->pDb,  pObjDb->cfg.iDbType,  NULL,  NULL,  id,  &m_var.oldRcd  )  )  goto  errLabel;
		   
	 }

	 bRet	=	TRUE;
errLabel:
	 return  bRet;
}


void CDlgCfgCustomerService::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgCfgCustomerService, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgCfgCustomerService::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgCfgCustomerService message handlers

BOOL CDlgCfgCustomerService::OnInitDialog()
{
	CDialog::OnInitDialog();

	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	// TODO:  Add extra initialization here
	HWND	hCombo  =  ::GetDlgItem(  m_hWnd,  IDC_COMBO_lang  );
	bQnmFillCol0FromTable(  CONST_qyLangTable_en,  hCombo,  TRUE  );
	
	(  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_lang  )  )->SelectString(  -1,  qyGetDesByType(  CONST_qyLangTable_en,  m_var.oldRcd.uiLangId  )  );
	SetDlgItemInt(  IDC_EDIT_category,  m_var.oldRcd.uiCategoryId  );

	SetDlgItemText(  IDC_EDIT_startIp,  CString(  m_var.oldRcd.startIp  )  );
	SetDlgItemText(  IDC_EDIT_endIp,  CString(  m_var.oldRcd.endIp  )  );

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCfgCustomerService::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	QY_MC		*		pQyMc								=	QY_GET_GBUF(  );
	TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1];
	char				idStr[CONST_qyMessengerIdStrLen  +  1];

	char				buf[255  +  1]						=	"";
	TCHAR				tBuf[255  +  1]						=	_T(  ""  );
	CString				str;
	int					idc;
	char				startIp12[32  +  1]					=	"";
	char				endIp12[32  +  1]					=	"";
	unsigned  long		ulhStartIp							=	0;
	unsigned  long		ulhEndIp							=	0;
	unsigned  long		ulIp								=	0;


	memset(  &m_var.rcd,  0,  sizeof(  m_var.rcd  )  );

	GetDlgItemText(  IDC_COMBO_lang,  str  );
	m_var.rcd.uiLangId  =  qyGetTypeByDes(  CONST_qyLangTable_en,  str  );
	if  (  m_var.rcd.uiLangId  ==  -1  )  m_var.rcd.uiLangId  =  0;
	GetDlgItemText(  IDC_EDIT_category,  str  );
	m_var.rcd.uiCategoryId  =  _ttol(  str  );

	idc  =  IDC_EDIT_startIp;
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str, buf,  mycountof(  buf  )  );  
	trim(  buf  );
	if  (  buf[0]  )  {
		if  (  (  ulIp  =  inet_addr(  buf  )  )  ==  INADDR_NONE  )  {
			qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_invaildIp  )  );  GetDlgItem(  idc  )->SetFocus(  );
			return;
		}
		}
	else  {
		  ulIp  =  0;
	}
	ulIp2Str(  ulIp,  m_var.rcd.startIp,  mycountof(  m_var.rcd.startIp  )  );
	ulhStartIp  =  qyntohl(  ulIp  );

	idc  =  IDC_EDIT_endIp;
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str, buf,  mycountof(  buf  )  );  
	trim(  buf  );  if  (  !buf[0]  )  safeStrnCpy(  m_var.rcd.startIp,  buf,  mycountof(  buf  )  );
	if  (  (  ulIp  =  inet_addr(  buf  )  )  ==  INADDR_NONE  )  {
		qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_invaildIp  )  );  GetDlgItem(  idc  )->SetFocus(  );
		return;
	}
	ulIp2Str(  ulIp,  m_var.rcd.endIp,  mycountof(  m_var.rcd.endIp  )  );
	ulhEndIp  =  qyntohl(  ulIp  );

	if  (  ulhEndIp  <  ulhStartIp  )  {
		qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_invaildEndIp  )  );  return;
	}



	if  (  !m_var.oldRcd.id  ||  memcmp(  &m_var.rcd,  &m_var.oldRcd,  sizeof(  m_var.rcd  )  )  )  {
		qyStdToIp12(  m_var.rcd.startIp,  startIp12  );
		qyStdToIp12(  m_var.rcd.endIp,  endIp12  );

		_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(id) from %s where id=%d"  ),  CONST_tabName_qyCustomerServiceObjTab,  m_var.oldRcd.id  );  
		if  (  !bSqlObjExists(  m_var.pObjDb->pDb,  sqlBuf  )  )  {	//  
			idInfo2Str(  &m_var.idInfo,  idStr,  mycountof(  idStr  )  );
			_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into %s(misServName,idStr,uiLangId,uiCategoryId,startIp,endIp) values(%s,'%s',%d,%d,'%s','%s')"  ),  CONST_tabName_qyCustomerServiceObjTab,  getDbValStr(  m_var.pObjDb->cfg.iDbType,  CONST_iDataType_misServName,  m_var.misServName  ),  CString(  idStr  ),  m_var.rcd.uiLangId,  m_var.rcd.uiCategoryId,  CString(  startIp12  ),  CString(  endIp12  )  );
			bQyExecSql(  m_var.pObjDb->pDb,  sqlBuf  );
			}
		else  {
			  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set uiLangId=%d,uiCategoryId=%d,startIp='%s',endIp='%s' where id=%d"  ),  CONST_tabName_qyCustomerServiceObjTab,  m_var.rcd.uiLangId,  m_var.rcd.uiCategoryId,  CString(  startIp12  ),  CString(  endIp12  ),  m_var.oldRcd.id  );
			  bQyExecSql(  m_var.pObjDb->pDb,  sqlBuf  );
		}

	}

	OnOK();
}
