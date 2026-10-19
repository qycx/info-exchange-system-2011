// DlgQnmPcAssetListSearch.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"

#include	"qymc.h"
#include	"DlgQnmPcAssetListSearch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmPcAssetListSearch dialog


CDlgQnmPcAssetListSearch::CDlgQnmPcAssetListSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQnmPcAssetListSearch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQnmPcAssetListSearch)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}


void CDlgQnmPcAssetListSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQnmPcAssetListSearch)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQnmPcAssetListSearch, CDialog)
	//{{AFX_MSG_MAP(CDlgQnmPcAssetListSearch)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmPcAssetListSearch message handlers

BOOL CDlgQnmPcAssetListSearch::OnInitDialog() 
{
	CDialog::OnInitDialog();
	QY_MC	*	pQyMc	=  QY_GET_GBUF(  );
	
	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	
	// TODO: Add extra initialization here
	GetDlgItem(  IDC_CHECK_onlyLast  )->SendMessage(  BM_SETCHECK ,  BST_UNCHECKED,  0  );
	for  (  int  i  =  0;  CONST_assetTypeTable[i].type  !=  -1;  i  ++  )  {
		 GetDlgItem(  IDC_COMBO_assetType  )->SendMessage(  CB_ADDSTRING,  0,  (  LPARAM  )CONST_assetTypeTable[i].des  );
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


 void CDlgQnmPcAssetListSearch::OnOK() 
{
	if  (  !m_var.pDbBufs  )  return;
	int		i;

	for  (  i  =  0;  ;  i  ++   )  {
		 if  (  m_var.pDbBufs[i].iDbType  ==  -1  )  break;
		 m_var.wherePart[0]   =   0;
		 if  (  getWherePart(  m_var.pDbBufs[i].iDbType  )  )  continue;
		 lstrcpyn(  m_var.pDbBufs[i].tBuf,  m_var.wherePart,  mycountof(  m_var.pDbBufs[i].tBuf  )  );
	}
	CDialog::OnOK();
}
 int CDlgQnmPcAssetListSearch::getWherePart(  int  iDbType  ) 
{
	int				iErr			=		-1;
	CString			str;
	QY_MC		*	pQyMc			=		QY_GET_GBUF(  );
	int				iDataType		=		SQL_WVARCHAR;
	char			ip12Buf[128]	=		"";

	GetDlgItemText(  IDC_EDIT_col2,  m_var.col2,  mycountof(  m_var.col2  )  );  
	GetDlgItemText(  IDC_EDIT_col3,  m_var.col3,  mycountof(  m_var.col3  )  );  
	GetDlgItemText(  IDC_EDIT_col4,  m_var.col4,  mycountof(  m_var.col4  )  );  
	GetDlgItemText(  IDC_EDIT_pcName,  str  );  myTChar2Str(  str,  m_var.pcName,  sizeof(  m_var.pcName  )  );  trim(  m_var.pcName  );
	GetDlgItemText(  IDC_IP,  str  );  myTChar2Str(  str,  m_var.ip,  sizeof(  m_var.ip  )  );  trim(  m_var.ip  );
	GetDlgItemText(  IDC_COMBO_assetType,  str  );  MACRO_CStringTrim(  str  );
	if  (  str.GetLength(  )  )  m_var.uiAssetType  =  qyGetTypeByDes(  CONST_assetTypeTable,  str  );
	GetDlgItemText(  IDC_EDIT_assetName,  m_var.assetName,  mycountof(  m_var.assetName  )  );  
	GetDlgItemText(  IDC_EDIT_assetDes0,  m_var.assetDes0,  mycountof(  m_var.assetDes0  )  );  
	m_var.ucbOnlyLast  =  (  (  (  CButton  *  )GetDlgItem(  IDC_CHECK_onlyLast  )  )->GetCheck(  )  ==  0  )  ?  FALSE  :  TRUE;

	m_var.wherePart[0]  =  0;
	if  (  m_var.col2[0]  )  _sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s %s qyPcRegInfoTab.col2=%s"  ),  m_var.wherePart,  (  m_var.wherePart[0]  ?  _T(  "and"  )  :  _T(  ""  )  ),  getDbValStr(  iDbType,  iDataType,  m_var.col2  )  );
	if  (  m_var.col3[0]  )  _sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s %s qyPcRegInfoTab.col3=%s"  ),  m_var.wherePart,  (  m_var.wherePart[0]  ?  _T(  "and"  )  :  _T(  ""  )),  getDbValStr(  iDbType,  iDataType,  m_var.col3  )  );
	if  (  m_var.col4[0]  )  _sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s %s qyPcRegInfoTab.col4=%s"  ),  m_var.wherePart,  (  m_var.wherePart[0]  ?  _T(  "and"  )  :  _T(  ""  )),  getDbValStr(  iDbType,  iDataType,  m_var.col4  )  );
	if  (  m_var.pcName[0]  )  _sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s %s qyPcTab.pcName='%s'"  ),  m_var.wherePart,  (  m_var.wherePart[0]  ?  _T(  "and"  )  :  _T(  ""  )),  CString(  m_var.pcName  )  );
	if  (  inet_addr(  m_var.ip  )  )  {
		qyStdToIp12(  m_var.ip,  ip12Buf  );	//  2007/02/20
		_sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s %s qyPcTab.ip='%s'"  ),  m_var.wherePart,  (  m_var.wherePart[0]  ?  _T(  "and"  )  :  _T(  ""  )),  CString(  ip12Buf  )  );
	}
	if  (  m_var.uiAssetType  )  _sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s %s qyPcAssetTab.iType=%d"  ),  m_var.wherePart,  (  m_var.wherePart[0]  ?  _T(  "and"  )  :  _T(  ""  )),  m_var.uiAssetType  );
	if  (  m_var.assetName[0]  )  _sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s %s qyPcAssetTab.name like %s"  ),  m_var.wherePart,  (  m_var.wherePart[0]  ?  _T(  "and"  )  :  _T(  ""  )),  getDbValStr(  iDbType,  iDataType,  CString(  "%"  )  +  m_var.assetName  +  "%"  )  );
	if  (  m_var.assetDes0[0]  )  _sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s %s qyPcAssetTab.des0 like %s"  ),  m_var.wherePart,  (  m_var.wherePart[0]  ?  _T(  "and"  )  :  _T(  ""  )),  getDbValStr(  iDbType,  iDataType,  CString(  "%"  )  +  m_var.assetDes0  +  "%"  )  );
	if  (  m_var.ucbOnlyLast  )  _sntprintf(  m_var.wherePart,  mycountof(  m_var.wherePart  ),  _T(  "%s %s qyPcAssetTab.endTime in (select max(b.endTime) from qyPcAssetTab as b where b.mac0=qyPcAssetTab.mac0)"  ),  m_var.wherePart,  (  m_var.wherePart[0]  ?  _T(  "and"  )  :  _T(  ""  ))  );

	traceLogA(  "m_var.wherePart is [%s]",  m_var.wherePart  );

	iErr  =  0;

	return  iErr;
	
}

