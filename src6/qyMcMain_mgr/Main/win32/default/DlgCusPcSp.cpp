// DlgCusPcSp.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgCusPcSp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCusPcSp dialog



CDlgCusPcSp::CDlgCusPcSp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCusPcSp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCusPcSp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgCusPcSp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCusPcSp)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCusPcSp, CDialog)
	//{{AFX_MSG_MAP(CDlgCusPcSp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCusPcSp message handlers



 BOOL  CDlgCusPcSp::bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  char  *  spName  )
{
	if  (  !spName  ||  !spName[0]  )  return  0;
	if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;

	m_var.pObjDb  =  pObjDb;
	m_var.cusPcSp.iType  =  CONST_cusNameType_pcSp;
	myStr2TChar(  spName,  m_var.cusPcSp.objNames[0],  mycountof(  m_var.cusPcSp.objNames[0]  )  );
	return  TRUE;
}


BOOL CDlgCusPcSp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	QY_MC		*	pQyMc		=		QY_GET_GBUF(  );
	CDBVariant		varVals[3];
	TCHAR			sqlBuf[CONST_qyMaxSqlBufLen  +  1];
	TCHAR			tBuf[1024];

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select cusName0 from qyCusNameTab where iType=%d and objName0='%s'"  ),  m_var.cusPcSp.iType,  m_var.cusPcSp.objNames[0]  );
	if  (  bQyGetRcdBySql(  m_var.pObjDb->pDb,  CString(  sqlBuf  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  {
		MACRO_sqlStr(  varVals[0],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  m_var.cusPcSp.cusNames[0],  tBuf,  mycountof(  m_var.cusPcSp.cusNames[0]  )  );
	}
	
	SetDlgItemText(  IDC_STATIC_spName,  CString(  m_var.cusPcSp.objNames[0]  )  );
	SetDlgItemText(  IDC_EDIT_cusPcSp,  CString(  m_var.cusPcSp.cusNames[0]  )  );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCusPcSp::OnOK() 
{
	QY_MC		*	pQyMc				=		QY_GET_GBUF(  );
	BOOL			bChanged			=		FALSE;
	CString			str;

	GetDlgItemText(  IDC_EDIT_cusPcSp,  str  );  
	MACRO_CStringTrim(  str  );
	lstrcpyn(  m_var.cusPcSp.cusNames[0],  str,  mycountof(  m_var.cusPcSp.cusNames[0]  )  );

	if  (  bSetCusName(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  0,  &m_var.cusPcSp,  &bChanged  )  )  m_var.ucbChanged  =  bChanged;
	
	CDialog::OnOK();
}


 //  有明确ID时，则选择用pCusName中的指来更新id对应的记录的内容
 BOOL  bSetCusName(  void  *  pDb,  int  iDbType,  int  id,  QY_CUSNAME_RCD  *  pCusName,  BOOL  *  pbChanged  )
{
	BOOL				bRet							=		FALSE;
	unsigned  char		ucbCusNameExists				=		FALSE;
	TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]=		_T(  ""  );	
	QY_CUSNAME_RCD		oldCusName;
	BOOL				bChanged						=		FALSE;
	int					iType							=		pCusName->iType;
	int					i;

	if  (  id  )  {
		_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update qyCusNameTab set "  )  );
		for  (  i  =  0;  i  <  mycountof(  pCusName->objNames  );  i  ++  )  {
			_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s %s objName%d=%s"  ),  sqlBuf,  i  ?  _T(  ","  )  :  _T(  ""  ),  i,  getDbValStr(  iDbType,  SQL_WVARCHAR,  pCusName->objNames[i]  )  );
		}
		for  (  i  =  0;  i  <  mycountof(  pCusName->cusNames  );  i  ++  )  {
			_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s %s cusName%d=%s"  ),  sqlBuf,   _T(  ","  ),  i,  getDbValStr(  iDbType,  SQL_WVARCHAR,  pCusName->cusNames[i]  )  );
		}
		_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s where id=%d"  ),  sqlBuf,  id  );
		if  (  !bQyExecSql(  pDb,  CString(  sqlBuf  )  )  )  goto  errLabel;

		bChanged  =  TRUE;
		bRet  =  TRUE;  goto  errLabel;

	}


	if  (  bGetCusNameBySth(  pDb,  iDbType,  pCusName,  0,  &oldCusName  )  )  ucbCusNameExists  =  TRUE;

	if  (  ucbCusNameExists  )  {
		for  (  i  =  0;  i  <  mycountof(  pCusName->cusNames  );  i  ++  )  {
			 if  (  _tcsicmp(  pCusName->cusNames[i],  oldCusName.cusNames[i]  )  )  break;
		}
		if  (  i  ==  mycountof(  pCusName->cusNames  )  )  {
			bRet  =  TRUE;  goto  errLabel;
		}
	}
	if  (  pCusName->iType  ==  CONST_cusNameType_pcSp  )  {
		if  (  !pCusName->cusNames[0][0]  )  {
			if  (  ucbCusNameExists  )  {  
				_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from qyCusNameTab where id=%d"  ),  oldCusName.id  );
				if  (  !bQyExecSql(  pDb,  CString(  sqlBuf  )  )  )  goto  errLabel;	
				bChanged  =  TRUE;
			}
			bRet  =  TRUE;  goto  errLabel;  
		}
	}
	if  (  ucbCusNameExists  )  {
		_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update qyCusNameTab set "  )  );
		for  (  i  =  0;  i  <  mycountof(  pCusName->cusNames  );  i  ++  )  {
			_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s %s cusName%d=%s"  ),  sqlBuf,  i  ?  _T(  ","  )  :  _T(  ""  ),  i,  getDbValStr(  iDbType,  SQL_WVARCHAR,  pCusName->cusNames[i]  )  );
		}
		_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s where id=%d"  ),  sqlBuf,  oldCusName.id  );
		if  (  !bQyExecSql(  pDb,  CString(  sqlBuf  )  )  )  goto  errLabel;
		}
	else  {
		  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qyCusNameTab(iType,uiLangId,objName0,cusName0,objName1,cusName1,objName2,cusName2,objName3,cusName3,objName4,cusName4,objName5,cusName5,objName6,cusName6,objName7,cusName7) values(%d,%d"  ),  pCusName->iType,  0  );
		  for  (  i  =  0;  i  <  mycountof(  pCusName->objNames  );  i  ++  )  {
			   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s,%s,%s"  ),  sqlBuf,  getDbValStr(  iDbType,  SQL_WVARCHAR,  pCusName->objNames[i]  ),  getDbValStr(  iDbType,  SQL_WVARCHAR,  pCusName->cusNames[i]  )  );
		  }
		  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s)"  ),  sqlBuf  );
		  if  (  !bQyExecSql(  pDb,  CString(  sqlBuf  )  )  )  goto  errLabel;
	}
	
	
	bChanged  =  TRUE;
	
	bRet  =  TRUE;
errLabel:

	if  (  bRet  )  {
		if  (  pbChanged  )  *pbChanged  =  bChanged;
	}
	return  bRet;
}

