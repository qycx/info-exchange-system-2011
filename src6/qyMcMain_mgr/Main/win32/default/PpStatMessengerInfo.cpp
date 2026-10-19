// PpStatMessengerInfo.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"PpStatMessengerInfo.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPpStatMessengerInfo property page

IMPLEMENT_DYNCREATE(CPpStatMessengerInfo, CPropertyPage)

CPpStatMessengerInfo::CPpStatMessengerInfo() : CPropertyPage(CPpStatMessengerInfo::IDD)
{
	//{{AFX_DATA_INIT(CPpStatMessengerInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CPpStatMessengerInfo::~CPpStatMessengerInfo()
{
}

void CPpStatMessengerInfo::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpStatMessengerInfo)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPpStatMessengerInfo, CPropertyPage)
	//{{AFX_MSG_MAP(CPpStatMessengerInfo)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_MESSAGE( QY_WM_COMM, OnQyComm )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpStatMessengerInfo message handlers

BOOL CPpStatMessengerInfo::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	QY_IDCITEM		*	pTable0		=	(  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpStatMessengerInfoTable0  );
	QY_IDCITEM		**	ppTables	=	(  QY_IDCITEM  **  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpStatMessengerInfoCb0Tables  );
	int					nTables		=	getnTables(  ppTables  );
	int					iCurSel		=	0;
	QY_IDCITEM		*	pCurTable	=	NULL;

	qnmSizeSearchControls(  &pQyMc->cusRes,  this->m_hWnd,  pTable0,  pTable0  );
	
	if  (  iCurSel  <  nTables  
		&&  (  pCurTable  =  ppTables[iCurSel]  )  )
	{
		qnmSizeSearchControls(  &pQyMc->cusRes,  this->m_hWnd,  pTable0,  pCurTable  );
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


 LRESULT  CPpStatMessengerInfo::OnQyComm(  WPARAM  wParam,  LPARAM  lParam  )
{
	long				lRet				=					-1;
	QY_MC			*	pQyMc				=					QY_GET_GBUF(  );
	QY_WMBUF_COMM	*	pComm				=					( QY_WMBUF_COMM * )lParam;
	int					iState;
	
	switch  (  pComm->uiType  )  {
			case  CONST_qyWmParam_chkPage:
				  if  (  (  iState  =  ::SendMessage(  GetDlgItem(  IDC_CHECK_messenger  )->m_hWnd,  BM_GETCHECK,  0,  0  )  )  !=  1  )
				  {
					  qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askForContentOfStat  )  );
					  goto  errLabel;
				  }
				  pComm->u.chkPage.IDD  =  CPpStatMessengerInfo::IDD;
				  pComm->u.chkPage.bOk  =  TRUE;
				  break;
			default:
					goto  errLabel;
	}

	lRet	=	QY_RC_WMOK;

errLabel:

	return  lRet;

}


void CPpStatMessengerInfo::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	QY_MC			*	pQyMc				=  QY_GET_GBUF(  );
	char				buf[1024];
	TCHAR				buf1[CONST_qyMaxSqlClauseLen  +  1];
	QY_IDCITEM		*	pTable0				=	(  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpStatMessengerInfoTable0  );
	QY_IDCITEM		*	pItem				=	NULL;
	char				itemBuf[256];
	int					iCurSel				=	-1;
	int					i;
	int					iRet;
	int					nCols				=	0;
	int					iState;
	BOOL				bMessengerStated	=	FALSE;
	//  TCHAR				iifBuf[1024];
	//  TCHAR				condBuf[1024];
	CString				str;

	if  (  !bObjDbAvail(  m_var.pObjDb  )  )  return;	//  2007/01/03

	if  (  (  (  CPropertySheet  *  )GetParent(  )  )->GetActivePage(  )  !=  this  )  {
		traceLogA(  "The active page is not pcInfo, so returns."  );  return;
	}

	UpdateData(  TRUE  );

	for  (  pItem  =  pTable0;  pItem->idc  !=  -1;  pItem  ++  )  {
		 if  (  pItem->flg  &  CONST_qyIdcFlgHide  )  continue;
		 if  (  pItem->idcType  ==  CONST_qyIdcType_comboDesc  )  break;
	}
	if  (  pItem->idc  ==  -1  )  {
		MACRO_qyAssert(  0,  _T(  "统计缺少分组项CONST_qyIdcType_comboDesc"  )  );
		return;
	}
	iCurSel  =  ::SendMessage(  GetDlgItem(  pItem->idc  )->m_hWnd,  CB_GETCURSEL,  0,  0  );
	if  (  iCurSel  !=  CB_ERR  )  {
		for  (  i  =  0;  i  <=  iCurSel;  i  ++  )  {
			 iRet  =  ::SendMessage(  GetDlgItem(  pItem->idc  )->m_hWnd,  CB_GETLBTEXT,  i,  (  LPARAM  )itemBuf  );
		 	 MACRO_qyAssert(  iRet  !=  CB_ERR  &&  iRet  <  sizeof(  itemBuf  ),  _T(  "CPpQnmStatGeneral越界"  )  );
		 	 qnmFillColInfo(  nCols,  getResTable(  0,  &pQyMc->cusRes,  pItem->iResIdTable  )[i].pData,  SQL_CHAR,  CONST_qyColumnDisplayType_str,  getResTable(  0,  &pQyMc->cusRes,  pItem->iResIdTable  )[i].des,  80,  &m_var.sqlCols[nCols],  &m_var.displayCols[nCols]  );
		 	 nCols  ++  ;
		 	 if  (  !m_var.groupPart[0]  )  _sntprintf(  m_var.groupPart,  sizeof(  m_var.groupPart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  getResTable(  0,  &pQyMc->cusRes,  pItem->iResIdTable  )[i].pData  )  );
		 	 else  _sntprintf(  m_var.groupPart,  sizeof(  m_var.groupPart  )  /  sizeof(  TCHAR  ),  _T(  "%s,%s"  ),  CString(  m_var.groupPart  ),  CString(  getResTable(  0,  &pQyMc->cusRes,  pItem->iResIdTable  )[i].pData  )  );
		}
	}
	
	for  (  pItem  =  pTable0;  pItem->idc  !=  -1;  pItem  ++  )  {
		 if  (  pItem->idcType  !=  CONST_qyIdcType_combo  
			 &&  pItem->idcType  !=  CONST_qyIdcType_edit  
				&&  pItem->idcType  !=  CONST_qyIdcType_ip  )  continue;
		 if  (  pItem->flg  &  CONST_qyIdcFlgUnused  )  continue;
		 if  (  pItem->flg  &  CONST_qyIdcFlgHide  )  continue;
		 if  (  !pItem->sqlColName  ||  !pItem->sqlColName[0]  )  continue;
		 if  (  pItem->idcType  ==  CONST_qyIdcType_ip  )  {
			 DWORD					dwIp;
			 struct  in_addr		tmpInAddr;

			 if  (  4  ==  ::SendMessage(  GetDlgItem(  pItem->idc  )->m_hWnd,  IPM_GETADDRESS,  0,  (  LPARAM  )&dwIp  )  )  {
				 tmpInAddr.s_addr  =  qyhtonl(  dwIp  );
				 sprintf(  buf,  inet_ntoa(  tmpInAddr  )  );
				 if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s and "  ),  CString(  m_var.wherePart  )  );
				 _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s %s='%s'"  ),  CString(  m_var.wherePart  ),  CString(  pItem->sqlColName  ),  CString(  buf  )  );
			 }
			 continue;	
		 }
		 if  (  pItem->idcType  ==  CONST_qyIdcType_combo  )  {
		     iCurSel  =  ::SendMessage(  GetDlgItem(  pItem->idc  )->m_hWnd,  CB_GETCURSEL,  0,  0  );
			 if  (  iCurSel  ==  CB_ERR  )  continue;
			 if  (  getResTable(  0,  &pQyMc->cusRes,  pItem->iResIdTable  )[iCurSel].type  ==  CONST_qyStatType_all  )  {
			     MACRO_qyAssert(  0,  _T(  "CONST_qyStatType_all not supported now."  )  );
				 continue;
			 }
			 if  (  getResTable(  0,  &pQyMc->cusRes,  pItem->iResIdTable  )[iCurSel].type  ==  CONST_qyStatType_others  )  {
			     buf1[0]  =  0;
				 for  (  QY_DMITEM  *  p1  =  getResTable(  0,  &pQyMc->cusRes,  pItem->iResIdTable  );  p1->type  !=  -1;  p1  ++  )  {
				      if  (  p1->type  ==  CONST_qyStatType_others  ||  p1->type  ==  CONST_qyStatType_all  )  continue;
					  if  (  !buf1[0]  )  _sntprintf(  buf1,  sizeof(  buf1  )  /  sizeof(  TCHAR  ),  _T(  "not (%s='%s'"  ),  pItem->sqlColName,  p1->des  );
					  else  _sntprintf(  buf1,  sizeof(  buf1  )  /  sizeof(  TCHAR  ),  _T(  "%s or %s='%s'"  ),  buf1,  pItem->sqlColName,  p1->des  );
				 }
				 if  (  buf1[0]  )  _sntprintf(  buf1,  sizeof(  buf1  )  /  sizeof(  TCHAR  ),  _T(  "%s)"  ),  buf1  );
				 if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s and "  ),  CString(  m_var.wherePart  )  );
				 _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s %s or %s is null"  ),  m_var.wherePart,  CString(  buf1  ),  pItem->sqlColName  );
				 continue;
			 }
			 //  以下是普通的combo处理
			 GetDlgItemText(  pItem->idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );	
			 trim(  buf  );
			 if  (  buf[0]  )  {
				 if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s and "  ),  m_var.wherePart  );
				 _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s %s='%s'"  ),  m_var.wherePart,  pItem->sqlColName,  CString(  buf  )  );
			 }
			 continue;			
		 }
	 
		 GetDlgItemText(  pItem->idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );	
		 trim(  buf  );
		 if  (  buf[0]  )  {
			 if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s and "  ),  m_var.wherePart  );
			 _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s %s='%s'"  ),  CString(  m_var.wherePart  ),  CString(  pItem->sqlColName  ),  CString(  buf  )  );
		 }
	}
	

	//
	char										dbTypeName[32  +  1];	//  2006/12/18
	myTChar2Str(  qyGetDesByType1(  CONST_dbTypeTable,  m_var.pObjDb->cfg.iDbType  ),  dbTypeName,  mycountof(  dbTypeName  )  );


	if  (  (  iState  =  ::SendMessage(  GetDlgItem(  IDC_CHECK_messenger  )->m_hWnd,  BM_GETCHECK,  0,  0  )  )  ==  1  )  bMessengerStated  =  TRUE;
	if  (  !bMessengerStated  )  {
		MACRO_qyAssert(  0,  _T(  "请选择统计内容"  )  );
		return;
	}
	if  (  bMessengerStated  )  {
		qnmFillColInfo(  nCols,  _T(  "count(qyImObjTab.idStr)"  ),		SQL_INTEGER,	CONST_qyColumnDisplayType_long,  _T(  "Messenger"  ),	80,  &m_var.sqlCols[nCols],  &m_var.displayCols[nCols]  );
		nCols  ++  ;		
	}
	
	qnmFillColInfo(  -1,	 _T(  ""  ),								0,			0,								_T(  ""  ),			0,	 &m_var.sqlCols[nCols],  &m_var.displayCols[nCols]  );
	nCols  ++  ;

	m_var.bOk  =  TRUE;

	CPropertyPage::OnOK();
}
