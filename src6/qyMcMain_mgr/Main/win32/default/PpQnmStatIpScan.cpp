// PpQnmStatIpScan.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyMc.h"
#include	"PpQnmStatIpScan.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPpQnmStatIpScan property page

IMPLEMENT_DYNCREATE(CPpQnmStatIpScan, CPropertyPage)

CPpQnmStatIpScan::CPpQnmStatIpScan() : CPropertyPage(CPpQnmStatIpScan::IDD)
{
	//{{AFX_DATA_INIT(CPpQnmStatIpScan)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	memset(  &m_var,  0,  sizeof(  m_var  )  );

}

CPpQnmStatIpScan::~CPpQnmStatIpScan()
{
}

void CPpQnmStatIpScan::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPpQnmStatIpScan)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPpQnmStatIpScan, CPropertyPage)
	//{{AFX_MSG_MAP(CPpQnmStatIpScan)
	ON_CBN_SELCHANGE(IDC_COMBO0, OnSelchangeCombo0)
	//}}AFX_MSG_MAP
	ON_MESSAGE( QY_WM_COMM, OnQyComm )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPpQnmStatIpScan message handlers

BOOL CPpQnmStatIpScan::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	qnmSizeSearchControls(  &pQyMc->cusRes,  this->m_hWnd,  (  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpStatIpScanTable0  ),  (  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpStatIpScanTable0  )  );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

 LRESULT CPpQnmStatIpScan::OnQyComm(  WPARAM  wParam,  LPARAM  lParam  )
{
	long				lRet				=					-1;
	QY_MC			*	pQyMc				=					QY_GET_GBUF(  );
	QY_WMBUF_COMM	*	pComm				=					( QY_WMBUF_COMM * )lParam;
	int					iState;
	
	switch  (  pComm->uiType  )  {
			case  CONST_qyWmParam_chkPage:
				  if  (  (  iState  =  ::SendMessage(  GetDlgItem(  IDC_CHECK_ip  )->m_hWnd,  BM_GETCHECK,  0,  0  )  )  !=  1  )  {
					  qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askForContentOfStat  )  );
					  goto  errLabel;
				  }
				  pComm->u.chkPage.IDD  =  CPpQnmStatIpScan::IDD;				  
				  pComm->u.chkPage.bOk  =  TRUE;
				  break;
			default:
					goto  errLabel;
	}

	lRet	=	QY_RC_WMOK;

errLabel:

	return  lRet;
}

	
 extern  "C"  int  qnmFillColInfo(  int  iType,  LPCTSTR  sqlColName,  int  iSqlDataType,  int  iDisplayType,  LPCTSTR  displayColName,  int  nWidth,  QY_COLUMNINFO  *  pSqlCol,  QY_COLUMNINFO  *  pDisplayCol  )
{
	 if  (  iType  >=  CONST_qnmMaxStatCols  )  {		//  2005/02/15增加了这个判断，因为前面是将iType当nCols第几列来做的，所以可以这么判断，但实际上这个方法不过好
		 MACRO_qyAssert(  0,  _T(  "不能填充超过CONST_qnmMaxStatCols个"  )  );  return  -1;
	 }
	 pSqlCol->type  =  iType;
	 if  (  iType  ==  -1  )  {
		 pDisplayCol->type  =  -1;
		 return  0;
	 }
	 lstrcpyn(  pSqlCol->label,  sqlColName,  sizeof(  pSqlCol->label  )  /  sizeof(  pSqlCol->label[0]  )  );
	 pSqlCol->iDataType  =  iSqlDataType;
	 pDisplayCol->type  =  iDisplayType;
	 lstrcpyn(  pDisplayCol->label,  displayColName,  sizeof(  pDisplayCol->label  )  /  sizeof(  pDisplayCol->label[0]  )  );
	 pDisplayCol->iDataType  =  SQL_CHAR;
	 pDisplayCol->fmt  =  LVCFMT_LEFT;
	 pDisplayCol->width  =  nWidth;
	 pDisplayCol->ucLevel  =  0;
	 pDisplayCol->nMaxBytes  =  50;
	 return  0;
}


 void CPpQnmStatIpScan::OnOK() 
{
	char				buf[1024];
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	QY_IDCITEM		*	pTable0			=	(  QY_IDCITEM  *  )getResSearch(  0,  &pQyMc->cusRes,  CONST_resId_gpStatIpScanTable0  );
	QY_IDCITEM		*	pItem			=	NULL;
	char				itemBuf[256];
	int					iCurSel			=	-1;
	int					i;
	int					iRet;
	int					nCols			=	0;
	int					iState;
	CString				str;

	if  (  (  (  CPropertySheet  *  )GetParent(  )  )->GetActivePage(  )  !=  this  )  {
		return;
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
	if  (  iCurSel  ==  CB_ERR  )  {
		MACRO_qyAssert(  0,  _T(  "应选中其中一项"  )  );
		return;
	}
	for  (  i  =  0;  i  <=  iCurSel;  i  ++  )  {
		 iRet  =  ::SendMessage(  GetDlgItem(  pItem->idc  )->m_hWnd,  CB_GETLBTEXT,  i,  (  LPARAM  )itemBuf  );
		 MACRO_qyAssert(  iRet  !=  CB_ERR  &&  iRet  <  sizeof(  itemBuf  ),  _T(  "CPpQnmStatGeneral越界"  )  );
		 qnmFillColInfo(  nCols,  getResTable(  0,  &pQyMc->cusRes,  pItem->iResIdTable  )[i].pData,  SQL_CHAR,  CONST_qyColumnDisplayType_str,  getResTable(  0,  &pQyMc->cusRes,  pItem->iResIdTable  )[i].des,  80,  &m_var.sqlCols[nCols],  &m_var.displayCols[nCols]  );
		 nCols  ++  ;
		 if  (  !m_var.groupPart[0]  )  _sntprintf(  m_var.groupPart,  sizeof(  m_var.groupPart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  getResTable(  0,  &pQyMc->cusRes,  pItem->iResIdTable  )[i].pData  )  );
		 else  _sntprintf(  m_var.groupPart,  sizeof(  m_var.groupPart  )  /  sizeof(  TCHAR  ),  _T(  "%s,%s"  ),  CString(  m_var.groupPart  ),  CString(  getResTable(  0,  &pQyMc->cusRes,  pItem->iResIdTable  )[i].pData  )  );
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
			}
		 else  {
				GetDlgItemText(  pItem->idc,  str  );  myTChar2Str(  str,  buf,  sizeof(  buf  )  );	
				trim(  buf  );
				if  (  buf[0]  )  {
					if  (  m_var.wherePart[0]  )  _sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s and "  ),  CString(  m_var.wherePart  )  );
					_sntprintf(  m_var.wherePart,  sizeof(  m_var.wherePart  )  /  sizeof(  TCHAR  ),  _T(  "%s %s='%s'"  ),  CString(  m_var.wherePart  ),  CString(  pItem->sqlColName  ),  CString(  buf  )  );
				}
		 }		 
	}
	
	if  (  (  iState  =  ::SendMessage(  GetDlgItem(  IDC_CHECK_ip  )->m_hWnd,  BM_GETCHECK,  0,  0  )  )  !=  1  )  {
		qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_askForContentOfStat  )  );
		goto  errLabel;
	}

	qnmFillColInfo(  nCols,  _T(  "count(qnmScannedIpTab.ip)"  ),		SQL_CHAR,	CONST_qyColumnDisplayType_str,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_ipCount  ),	80,  &m_var.sqlCols[nCols],  &m_var.displayCols[nCols]  );
	nCols  ++  ;
	qnmFillColInfo(  -1,	 _T(  ""  ),								0,			0,								_T(  ""  ),			0,	 &m_var.sqlCols[nCols],  &m_var.displayCols[nCols]  );
	nCols  ++  ;

	m_var.bOk  =  TRUE;

errLabel:
	
	CPropertyPage::OnOK();

}

void CPpQnmStatIpScan::OnSelchangeCombo0() 
{
	// TODO: Add your control notification handler code here
	
}
