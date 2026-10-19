// DlgQnmCfgPcGrp.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyMc.h"
#include	"DlgQnmCfgPcGrp.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


 //    
 BOOL  bQnmPcGrpNotConflict(  void  *  pDb,  unsigned  int  ulStartIp,  unsigned  int  ulEndIp  )
{
	 BOOL				bRet	=	FALSE;
	 CString			sqlStr;
	 char				startIp[CONST_qyMaxIpLen  +  1],  endIp[CONST_qyMaxIpLen  +  1];
	 CDBVariant			varVals[3];
	 char				startIp12[128],  endIp12[128];

	 safeStrnCpy(  inet_ntoa(  *(  in_addr  *  )&ulStartIp  ),  startIp,  sizeof(  startIp  )  );
	 safeStrnCpy(  inet_ntoa(  *(  in_addr  *  )&ulEndIp  ),  endIp,  sizeof(  endIp  )  );

	 qyStdToIp12(  startIp,  startIp12  );
	 sqlStr  =  CString(  ""  )  +  "select lanName from qnmPcGrpTab where startIp<='"  +  startIp12  +  "'"
				+  " and endIp>='"  +  startIp12  +  "'";
	 if  (  bQyGetRcdBySql(  pDb,  sqlStr.GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals )  )  {
		 traceLogA(  "startIp在其他网段中"  );
		 goto  errLabel;
	 }
	 qyStdToIp12(  endIp,  endIp12  );
	 sqlStr  =  CString(  ""  )  +  "select lanName from qnmPcGrpTab where startIp<='"  +  endIp12  +  "'"
				+  " and endIp>='"  +  endIp12  +  "'";
	 if  (  bQyGetRcdBySql(  pDb,  sqlStr.GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals )  )  {
		 traceLogA(  "startIp在其他网段中"  );
		 goto  errLabel;
	 }

	 sqlStr  =  CString(  ""  )  +  "select lanName from qnmPcGrpTab where startIp>'"  +  startIp12  +  "'"
				+  " and endIp<'"  +  endIp12  +  "'";
	 if  (  bQyGetRcdBySql(  pDb,  sqlStr.GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals )  )  {
		 traceLogA(  "该网段包含了其他已输入网段"  );
		 goto  errLabel;
	 }


	 bRet  =  TRUE;

errLabel:
	 
	 return  bRet;

}


/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgPcGrp dialog


CDlgQnmCfgPcGrp::CDlgQnmCfgPcGrp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQnmCfgPcGrp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQnmCfgPcGrp)
	m_officeName = _T("");
	m_subOfficeName = _T("");
	//}}AFX_DATA_INIT
}


void CDlgQnmCfgPcGrp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQnmCfgPcGrp)
	DDX_Control(pDX, IDC_startIp, m_startIp);
	DDX_Control(pDX, IDC_endIp, m_endIp);
	DDX_Text(pDX, IDC_EDIT_officeName, m_officeName);
	DDV_MaxChars(pDX, m_officeName, 64);
	DDX_Text(pDX, IDC_EDIT_subOfficeName, m_subOfficeName);
	DDV_MaxChars(pDX, m_subOfficeName, 64);
	//}}AFX_DATA_MAP
}
 

BEGIN_MESSAGE_MAP(CDlgQnmCfgPcGrp, CDialog)
	//{{AFX_MSG_MAP(CDlgQnmCfgPcGrp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmCfgPcGrp message handlers

 BOOL CDlgQnmCfgPcGrp::bSetDlgInfo(  int  type,  CWnd * pSrcWnd,  char  *  startIp  )
{
	m_var.type			=  type;
	m_var.pSrcWnd		=  pSrcWnd;
	if  (  startIp  )  _snprintf(  m_var.startIp,  sizeof(  m_var.startIp  ),  "%s",  startIp  );
	return  TRUE;
}

 BOOL  bGetQnmPcGrpInfoByStartIp(  void  *  pDb,  char  *  startIp,  QNM_PCGRP_RCD  *  pPcGrpInfo  )
{
	 BOOL				bRet	=	FALSE;
	 CString			sqlStr;
	 char				ip12[12  +  1];
	 CDBVariant			varVals[10];
	 QNM_PCGRP_RCD		pcGrpInfo;
	 int				index;
	 char				buf[256];
	 TCHAR			*	pStopString;
	 TCHAR				tBuf[256];

	 qyStdToIp12(  startIp,  ip12  );
	 sqlStr  =  CString(  "select startIp,endIp,officeName,subOfficeName,lanName,ucbStopSnmpScan,ucbStopMacScan from qnmPcGrpTab"  )
				+  " where startIp='"  +  ip12  +  "'";
	 if  (  !bQyGetRcdBySql(  pDb,  sqlStr.GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  goto  errLabel;

	 memset(  &pcGrpInfo,  0,  sizeof(  pcGrpInfo  )  );

	 index  =  0;	//  startIp
	 MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
	 if  (  lstrlen(  tBuf  )  >=  12  )  {
		 myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );  qyIp12ToStd(  buf,  pcGrpInfo.startIp  );  
	 }
	 index  ++  ;	//  endIp
	 MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
	 if  (  lstrlen(  tBuf  )  >=  12  )  {
		 myTChar2Str(  tBuf,  buf,  sizeof(  buf  )  );  qyIp12ToStd(  buf,  pcGrpInfo.endIp  );
	 }
	 index  ++  ;	//  officeName
	 MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
	 myTChar2Str(  tBuf,  pcGrpInfo.officeName,  sizeof(  pcGrpInfo.officeName  )  );
	 index  ++  ;	//  subOfficeName
	 MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
	 myTChar2Str(  tBuf,  pcGrpInfo.subOfficeName,  sizeof(  pcGrpInfo.subOfficeName  )  );
	 index  ++  ;	//  lanName
	 MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
	 myTChar2Str(  tBuf,  pcGrpInfo.lanName,  sizeof(  pcGrpInfo.lanName  )  );
	 index  ++  ;	//  ucbStopSnmpScan
	 MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
	 if  (  _tcstol(  tBuf,  &pStopString,  10  )  ==  1  )  pcGrpInfo.ucbStopSnmpScan  =  TRUE;
	 index  ++  ;	//  ucbStopMacScan
	 MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
	 if  (  _tcstol(  tBuf,  &pStopString,  10  )  ==  1  )  pcGrpInfo.ucbStopMacScan  =  TRUE;
	 index  ++  ;

	 bRet  =  TRUE;
errLabel:
	 if  (  bRet  )  memcpy(  pPcGrpInfo,  &pcGrpInfo,  sizeof(  pPcGrpInfo[0]  )  );
	 return  bRet;

}

 BOOL CDlgQnmCfgPcGrp::OnInitDialog() 
{
	CDialog::OnInitDialog();

	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );


	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );


	GetDlgItem(  IDC_STATIC_scanedObj  )->ShowWindow(  SW_SHOW  );
	GetDlgItem(  IDC_COMBO_scanedObj  )->ShowWindow(  SW_SHOW  );
	
	//  定制部分
	GetDlgItem(  IDC_COMBO_scanedObj  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )getResStr(  0,  &pQyMc->cusRes,  CONST_resId_all  )  );
	if  (  pQyMc->cfg.pGuiCfg->ucbSupportNbtScan  )  GetDlgItem(  IDC_COMBO_scanedObj  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )getResStr(  0,  &pQyMc->cusRes,  CONST_resId_computer  )  );
	if  (  pQyMc->cfg.pGuiCfg->ucbSupportSnmpScan  )  GetDlgItem(  IDC_COMBO_scanedObj  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )getResStr(  0,  &pQyMc->cusRes,  CONST_resId_wangLuoSheBei  )  );
	GetDlgItem(  IDC_COMBO_scanedObj  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )getResStr(  0,  &pQyMc->cusRes,  CONST_resId_none  )  );

	//  添加操作时总设在所有那儿
	if  (  m_var.type  ==  CONST_qyDlgType_add  )  GetDlgItem(  IDC_COMBO_scanedObj  )->SendMessage(  CB_SELECTSTRING,  -1,  (  LPARAM  )getResStr(  0,  &pQyMc->cusRes,  CONST_resId_all  )  );

	
	if  (  m_var.type  ==  CONST_qyDlgType_modify  )  {
		if  (  bGetQnmPcGrpInfoByStartIp(  pQyMc->gui.pDb,  m_var.startIp,  &m_var.procedPcGrp  )  )  {
			m_startIp.SetAddress(  qyntohl(  inet_addr(  m_var.procedPcGrp.startIp  )  )  );
			m_endIp.SetAddress(  qyntohl(  inet_addr(  m_var.procedPcGrp.endIp  )  )  );
			SetDlgItemText(  IDC_EDIT_officeName,  CString(  m_var.procedPcGrp.officeName  )  );
			SetDlgItemText(  IDC_EDIT_subOfficeName,  CString(  m_var.procedPcGrp.subOfficeName  )  );

			if  (  !m_var.procedPcGrp.ucbStopMacScan  &&  !m_var.procedPcGrp.ucbStopSnmpScan  )  GetDlgItem(  IDC_COMBO_scanedObj  )->SendMessage(  CB_SELECTSTRING,  -1,  (  LPARAM  )getResStr(  0,  &pQyMc->cusRes,  CONST_resId_all  )  );
			else  if  (  !m_var.procedPcGrp.ucbStopMacScan  )  GetDlgItem(  IDC_COMBO_scanedObj  )->SendMessage(  CB_SELECTSTRING,  -1,  (  LPARAM  )getResStr(  0,  &pQyMc->cusRes,  CONST_resId_computer  )  );
			else  if  (  !m_var.procedPcGrp.ucbStopSnmpScan  )  GetDlgItem(  IDC_COMBO_scanedObj  )->SendMessage(  CB_SELECTSTRING,  -1,  (  LPARAM  )getResStr(  0,  &pQyMc->cusRes,  CONST_resId_wangLuoSheBei  )  );
			else  GetDlgItem(  IDC_COMBO_scanedObj  )->SendMessage(  CB_SELECTSTRING,  -1,  (  LPARAM  )getResStr(  0,  &pQyMc->cusRes,  CONST_resId_none  )  );
						
			GetDlgItem(  IDC_startIp  )->EnableWindow(  FALSE  );

		}
	}
			
	return  TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

 void  CDlgQnmCfgPcGrp::OnOK() 
{
	QY_MC			*	pQyMc						=	QY_GET_GBUF(  );
	unsigned  long		hStartIp,  hEndIp;
	unsigned  long		ulStartIp,  ulEndIp;
	int					n;
	CString				sqlStr;
	char				buf[128];
	QNM_PCGRP_RCD		pcGrpInfo;
	char				ucbStopSnmpScanBuf[2]		=	"";
	char				ucbStopNbtScanBuf[2]		=	"";
	CString				str;

	UpdateData(  TRUE  );

	memset(  &pcGrpInfo,  0,  sizeof(  pcGrpInfo  )  );

	n  =  m_startIp.GetAddress(  hStartIp  );
	if  (  n  !=  4  )  {
		MessageBeep(  -1  );  AfxMessageBox(  CString(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qnmHint_startIp0  )  )  );  return;
	}
	n  =  m_endIp.GetAddress(  hEndIp  );
	if  (  n  ==  0  )  hEndIp  =  hStartIp;
	else  if  (  n  !=  4  )  {
			  MessageBeep(  -1  );  return;
	}
	
	if  (  hStartIp  >  hEndIp  )  {
		MessageBeep(  -1  );  AfxMessageBox(  CString(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qnmHint_endIpLtStartIp  )  )  );  return;
	} 

	ulStartIp  =  qyhtonl(  hStartIp  );
	ulEndIp  =  qyhtonl(  hEndIp  );
		
	GetDlgItemText(  IDC_COMBO_scanedObj,  str  );  
	if  (  !lstrcmp(  str,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_none  )  )  )  pcGrpInfo.ucbStopMacScan  =  pcGrpInfo.ucbStopSnmpScan  =  TRUE;
	else  if  (  !lstrcmp(  str,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_wangLuoSheBei  )  )  )  pcGrpInfo.ucbStopMacScan  =  TRUE;
	else  if  (  !lstrcmp(  str,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_computer  )  )  )  pcGrpInfo.ucbStopSnmpScan  =  TRUE;
	else  ;
			
	_snprintf(  ucbStopSnmpScanBuf,  sizeof(  ucbStopSnmpScanBuf  ),  "%s",  pcGrpInfo.ucbStopSnmpScan  ?  "1"  :  ""  );
	_snprintf(  ucbStopNbtScanBuf,  sizeof(  ucbStopNbtScanBuf  ),  "%s",  pcGrpInfo.ucbStopMacScan  ?  "1"  :  ""  );
		
	
	if  (  m_var.type  ==  CONST_qyDlgType_add  )  {

		if  (  !bQnmPcGrpNotConflict(  pQyMc->gui.pDb,  ulStartIp,  ulEndIp  )  )  {
			MessageBeep(  -1  );  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_fieldCannotSame  )  );  return;
		}

		sqlStr  =  CString(  ""  )  +  "insert into qnmPcGrpTab(startIp,endIp,officeName,subOfficeName,lanName";
		if  (  pQyMc->cfg.pGuiCfg->ucbSupportNbtScan  )  sqlStr  +=  CString(  ",ucbStopMacScan"  );
		if  (  pQyMc->cfg.pGuiCfg->ucbSupportSnmpScan  )  sqlStr  +=  CString(  ",ucbStopSnmpScan"  );
		sqlStr  +=  CString(  ""  )  +  ",fBwd) values("  +  "'"  +  qyStdToIp12(  inet_ntoa(  *(  in_addr  *  )&ulStartIp  ),  buf  )  +  "',";
		sqlStr  =  sqlStr  +  "'"  +  qyStdToIp12(  inet_ntoa(  *(  in_addr  *  )&ulEndIp  ),  buf  )  +  "',";
		sqlStr  =  sqlStr  +  "'"  +  m_officeName.GetBuffer(  0  )  +  "',";
		sqlStr  =  sqlStr  +  "'"  +  m_subOfficeName.GetBuffer(  0  )  +  "',";
		sqlStr  =  sqlStr  +  "'"  +  ""  +  "'";		//  2004/11/25
		//  if  (  pQyMc->cfg.pGuiCfg->ucbSupportNbtScan  )  sqlStr  +=  CString(  ""  )  +  "','"  +  ucbStopNbtScanBuf  +  "'";
		if  (  pQyMc->cfg.pGuiCfg->ucbSupportNbtScan  )  sqlStr  +=  CString(  ""  )  +  ",'"  +  ucbStopNbtScanBuf  +  "'";
		if  (  pQyMc->cfg.pGuiCfg->ucbSupportSnmpScan  )  sqlStr  +=  CString(  ""  )  +  ",'"  +  ucbStopSnmpScanBuf  +  "'";
		sqlStr  +=  CString(  ""  )  +  ",'"  +  ""    +  "')";

		if  (  !bQyExecSql(  pQyMc->gui.pDb,  sqlStr.GetBuffer(  0  )  )  )  {
			MessageBeep(  -1  );  AfxMessageBox(  CString(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_fieldCannotSame  )  )  );  return;
		}
		m_var.bChanged  =  TRUE;
	}
	if  (  m_var.type  ==  CONST_qyDlgType_modify  )  {

		sqlStr  =  CString(  ""  )  +  "update qnmPcGrpTab set endIp='"  +  qyStdToIp12(  inet_ntoa(  *(  in_addr  *  )&ulEndIp  ),  buf  )  +  "'"
			+  ",officeName='"  +  m_officeName.GetBuffer(  0  )  +  "'"
			+  ",subOfficeName='"  +  m_subOfficeName.GetBuffer(  0  )  +  "'";
		if  (  pQyMc->cfg.pGuiCfg->ucbSupportNbtScan  )  sqlStr  +=  CString(  ""  )  +  ",ucbStopMacScan='"  +  ucbStopNbtScanBuf  +  "'";
		if  (  pQyMc->cfg.pGuiCfg->ucbSupportSnmpScan  )  sqlStr  +=  CString(  ""  )  +  ",ucbStopSnmpScan='"  +  ucbStopSnmpScanBuf  +  "'";
		sqlStr  =  sqlStr  +  " where startIp='"  +  qyStdToIp12(  inet_ntoa(  *(  in_addr  *  )&ulStartIp  ),  buf  )  +  "'";

		if  (  !bQyExecSql(  pQyMc->gui.pDb,  sqlStr.GetBuffer(  0  )  )  )  {
			MessageBeep(  -1  );  AfxMessageBox(  CString(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_fieldCannotSame  )  )  );  return;
		}
		m_var.bChanged  =  TRUE;
	}
	
	CDialog::OnOK();
}





