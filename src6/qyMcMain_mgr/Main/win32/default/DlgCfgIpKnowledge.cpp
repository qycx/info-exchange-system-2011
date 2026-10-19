// DlgCfgIpKnowledge.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgCfgIpKnowledge.h"
#include ".\dlgcfgipknowledge.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgIpKnowledge dialog


CDlgCfgIpKnowledge::CDlgCfgIpKnowledge(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCfgIpKnowledge::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCfgIpKnowledge)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


 BOOL  CDlgCfgIpKnowledge::bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  int  id  )
{
	 BOOL		bRet	=	FALSE;
	 QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
 
	 if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	 m_var.iDlgType  =  iDlgType;
	 m_var.pObjDb  =  pObjDb;
	 m_var.id  =  id;

	 
	 if  (  !bGetIpKnowledgeBySth(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  NULL,  NULL,  NULL,  m_var.id,  &m_var.knowledge  )  )  {
		 memset(  &m_var.knowledge,  0,  sizeof(  m_var.knowledge  )  );
	 }
	 

	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}



void CDlgCfgIpKnowledge::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgIpKnowledge)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfgIpKnowledge, CDialog)
	//{{AFX_MSG_MAP(CDlgCfgIpKnowledge)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgIpKnowledge message handlers

BOOL CDlgCfgIpKnowledge::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	QY_MC		*  pQyMc		=  QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	if  (  !m_var.pObjDb  )  {
		EndDialog(  -1  );  return  FALSE;
	}


	SetDlgItemText(  IDC_EDIT_startIp,  CString(  m_var.knowledge.startIp  )  );
	SetDlgItemText(  IDC_EDIT_endIp,  CString(  m_var.knowledge.endIp  )  );
	SetDlgItemText(  IDC_EDIT_wLocation,  m_var.knowledge.wLocation  );
	SetDlgItemInt(  IDC_EDIT_iWeight,  m_var.knowledge.iWeight  );


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


 void CDlgCfgIpKnowledge::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	int					iErr								=	-1;
	QY_MC			*	pQyMc								=	QY_GET_GBUF(  );
	IP_KNOWLEDGE_RCD	rcd;
	char				buf[255  +  1]						=	"";
	TCHAR				tBuf[255  +  1]						=	_T(  ""  );
	CString				str;
	int					idc;
	TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	char				startIp12[32  +  1]					=	"";
	char				endIp12[32  +  1]					=	"";
	unsigned  long		ulhStartIp;
	unsigned  long		ulhEndIp;
	unsigned  long		ulIp;

	memset(  &rcd,  0,  sizeof(  rcd  )  );
	rcd.uiType  =  CONST_imCommType_ipKnowledge;	
	
	idc  =  IDC_EDIT_startIp;
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str, buf,  mycountof(  buf  )  );  
	if  (  (  ulIp  =  inet_addr(  buf  )  )  ==  INADDR_NONE  )  {
		qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_invaildIp  )  );  GetDlgItem(  idc  )->SetFocus(  );
		return;
	}
	ulIp2Str(  ulIp,  rcd.startIp,  mycountof(  rcd.startIp  )  );
	ulhStartIp  =  qyntohl(  ulIp  );

	idc  =  IDC_EDIT_endIp;
	GetDlgItemText(  idc,  str  );  myTChar2Str(  str, buf,  mycountof(  buf  )  );  
	trim(  buf  );  if  (  !buf[0]  )  safeStrnCpy(  rcd.startIp,  buf,  mycountof(  buf  )  );
	if  (  (  ulIp  =  inet_addr(  buf  )  )  ==  INADDR_NONE  )  {
		qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_invaildIp  )  );  GetDlgItem(  idc  )->SetFocus(  );
		return;
	}
	ulIp2Str(  ulIp,  rcd.endIp,  mycountof(  rcd.endIp  )  );
	ulhEndIp  =  qyntohl(  ulIp  );

	if  (  ulhEndIp  <  ulhStartIp  )  {
		qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_invaildEndIp  )  );  return;
	}

	idc  =  IDC_EDIT_wLocation;
	GetDlgItemText(  idc,  rcd.wLocation,  mycountof(  rcd.wLocation  )  );

	idc  =  IDC_EDIT_iWeight;
	rcd.iWeight  =  GetDlgItemInt(  idc  );

	if  (  memcmp(  &rcd,  &m_var.knowledge,  sizeof(  rcd  )  )  )  {
	
		qyStdToIp12(  rcd.startIp,  startIp12  );
		qyStdToIp12(  rcd.endIp,  endIp12  );
		_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select count(id) from %s where uiType=%d and startIp='%s' and endIp='%s'"  ),  CONST_tabName_qyIpKnowledgeTab,  rcd.uiType,  CString(  startIp12  ),  CString(  endIp12  )  );
		if  (  m_var.id  )  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s and id<>%d"  ),  sqlBuf,  m_var.id  );
		if  (  bSqlObjExists(  m_var.pObjDb->pDb,  sqlBuf  )  )  {
			qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_hintOfRetype)  );  return;
		}

		if  (  m_var.id  )  {
			_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set uiType=%d,startIp='%s',endIp='%s',wLocation=%s,iWeight=%d where id=%d"  ),  CONST_tabName_qyIpKnowledgeTab,  rcd.uiType,  CString(  startIp12  ),  CString(  endIp12  ),  getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.wLocation  ),  rcd.iWeight,  m_var.id  );
			bQyExecSql(  m_var.pObjDb->pDb,  sqlBuf  );
			iErr  =  0;  goto  errLabel;
		}
		_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into %s(uiType,startIp,endIp,wLocation,iWeight) values( %d,'%s','%s',%s,%d)"  ),  CONST_tabName_qyIpKnowledgeTab,  rcd.uiType,  CString(  startIp12  ),  CString(  endIp12  ),  getDbValStr(  m_var.pObjDb->cfg.iDbType,  SQL_WVARCHAR,  rcd.wLocation  ),  rcd.iWeight  );
		bQyExecSql(  m_var.pObjDb->pDb,  sqlBuf  );
		iErr  =  0;  goto  errLabel;

	}

errLabel:


	OnOK();
}





