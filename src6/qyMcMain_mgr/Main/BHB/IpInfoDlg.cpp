// IpInfoDlg.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"bhbSrc1CommProc.h"
#include	"myresource.h"
#include	"IpInfoDlg.h"
#include	"IpDataSet.h"
#include	"InforDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
COMPUTER_IP_INFO m_stuComputerInfo;
COMPUTER_IP_INFO m_stuNewComputerInfo;
//  CDatabase gdb;	//  2003/11/25，须采用统一的数据库入口，故注释掉了

/////////////////////////////////////////////////////////////////////////////
// CIpInfoDlg dialog

 
 BOOL  bQwmScannedPcsRestricted(  )
{
	#ifdef  CONST_qwmFlg_intraRestricted
			return  TRUE;
	#endif

	return  FALSE;
}


 int  restrictScannedPcs(  unsigned  int  *  puiPcsCnt,  BOOL  *  pbDel )
{
	 QY_MC			*	pQyMc		=		QY_GET_GBUF(  );
	 int				iErr		=		-1;
	 unsigned  int		cnt			=		0;
	 CString			sqlStr		=		CString(  "select startIp,endIp from scannedIpTab order by startIp"  );
	 CRecordset			rs(  (  CDatabase  *  )pQyMc->gui.pDb  );
	 CDBVariant			varVals[10];
	 unsigned  long		ulStartIp,  ulEndIp;
	 unsigned  long		ulhStartIp,  ulhEndIp;
	 int				index;
	 int				nFields;
	 char				buf[1024];
	 BOOL				bDel		=		FALSE;

	 try  {
		 if  (  !rs.Open(  CRecordset::forwardOnly,  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;
		 nFields  =  rs.GetODBCFieldCount(  );
		 ASSERT(  nFields  <  sizeof(  varVals  )  /  sizeof(  varVals[0]  )  );
		 for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {
			  for  (  index  =  0;  index  <  nFields;  index  ++  ) 
				   rs.GetFieldValue(  index,  varVals[index]  );			  
			  if  (  varVals[0].m_dwType  !=  DBVT_STRING  ||  varVals[1].m_dwType  !=  DBVT_STRING  )  continue;
			  if  (  !varVals[0].m_pstring->GetLength(  )  ||  !varVals[1].m_pstring->GetLength(  )  )  continue;
			  myTChar2Str(  varVals[0].m_pstring->GetBuffer(  0  ),  buf,  sizeof(  buf  )  );
			  ulStartIp  =  inet_addr(  buf  );
			  myTChar2Str(  varVals[1].m_pstring->GetBuffer(  0  ),  buf,  sizeof(  buf  )  );
			  ulEndIp  =  inet_addr(  buf  );
			  if  (  ulStartIp  ==  INADDR_NONE  ||  ulEndIp  ==  INADDR_NONE  )  continue;
			  ulhStartIp  =  ntohl(  ulStartIp  );
			  ulhEndIp  =  ntohl(  ulEndIp  );
			  if  (  ulhEndIp  <  ulStartIp  )  continue;
			  
			  if  (  cnt  +  (  ulhEndIp  -  ulhStartIp  +  1  )  >  CONST_maxQwmScannedSegs  *  256  )  {
				  sqlStr  =  CString(  "delete from scannedIpTab where startIp>='"  )  +  varVals[0].m_pstring->GetBuffer(  0  )  +  "'";
				  (  (  CDatabase  *  )pQyMc->gui.pDb  )->ExecuteSQL(  sqlStr.GetBuffer(  0  )  );
				  bDel  =  TRUE;
				  break;
			  }
			  cnt  +=  ulhEndIp  -  ulhStartIp  +  1;
			  
		 }

		 _snprintf(  buf,  sizeof(  buf  ),  "%d台PC\n",  cnt  );
		 OutputDebugString(  CString(  buf  )  );

		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bDbConnected_netMc failed."  )  );
		   goto  errLabel;
	}
	 if  (  puiPcsCnt  )  *puiPcsCnt  =  cnt;
	 if  (  pbDel  )  *pbDel  =  bDel;

	 iErr  =  0;

errLabel:

	 return  iErr;

}



CIpInfoDlg::CIpInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIpInfoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIpInfoDlg)
	//}}AFX_DATA_INIT
}


void CIpInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIpInfoDlg)
	DDX_Control(pDX, IDC_LIST_IPINFO, m_cListIpInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CIpInfoDlg, CDialog)
	//{{AFX_MSG_MAP(CIpInfoDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_IPINFO, OnDblclkListIpinfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIpInfoDlg message handlers

BOOL CIpInfoDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_cListIpInfo.SetExtendedStyle(  LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES  );	

	m_cListIpInfo.InsertColumn( 0, _T(  "单位名称"  ),   LVCFMT_CENTER, 80,  0 );
	m_cListIpInfo.InsertColumn( 1, _T(  "部门名称"  ),   LVCFMT_CENTER, 80,  0 );
	m_cListIpInfo.InsertColumn( 2, _T(  "局域网IP起始地址"  ), LVCFMT_CENTER, 130,  0 );
	m_cListIpInfo.InsertColumn( 3, _T(  "局域网IP结束地址"  ), LVCFMT_CENTER, 130,  0 );
	
	if  (  bQwmScannedPcsRestricted(  )  )  restrictScannedPcs(  NULL,  NULL  );
	
	m_cListIpInfo.DeleteAllItems();
	FillIpListDlg();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CIpInfoDlg::InsertSingleInfo(int nIndex,COMPUTER_IP_INFO objComputerInfo)
{
	m_cListIpInfo.InsertItem(  nIndex,  CString(  objComputerInfo.cUnitInfo  )  );
	m_cListIpInfo.SetItemText(  nIndex,  1,  CString(  objComputerInfo.cSubOffice  )  );
	m_cListIpInfo.SetItemText(  nIndex,  2,  CString(  objComputerInfo.cStartIp  )  );
	m_cListIpInfo.SetItemText(  nIndex,  3,  CString(  objComputerInfo.cEndIp  )  );	
}

void CIpInfoDlg::FillIpListDlg()
{
	CIpDataSet objIpDataSet;
	CString msg;

	m_cListIpInfo.DeleteAllItems();
	try
	{
		if(!objIpDataSet.IsOpen())
			objIpDataSet.Open();
		for(int nIndex = 0 ; !objIpDataSet.IsEOF ();nIndex ++)
		{
			ZeroMemory(&m_stuComputerInfo,sizeof(COMPUTER_IP_INFO));
			memcpy(m_stuComputerInfo.cUnitInfo,objIpDataSet.m_officeName,8);
			memcpy(m_stuComputerInfo.cStartIp,objIpDataSet.m_startIp,15);
			memcpy(m_stuComputerInfo.cEndIp,objIpDataSet.m_endIp,15);
			memcpy(m_stuComputerInfo.cSubOffice,objIpDataSet.m_subOfficeName,8);

			InsertSingleInfo(0,m_stuComputerInfo);
			objIpDataSet.MoveNext();
		}
		objIpDataSet.Close ();
	}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CIpInfoDlg::FillIpListDlg failed."  )  );
	}

}

int CIpInfoDlg::GetRegCfg( char *cfgVal, int size )
{
	int iRet = -1;
	BOOL bKeyOpen = FALSE;
	HKEY hKey;
	int lRet = 0;
	long cb;
	DWORD type;
			
	lRet = RegOpenKey( HKEY_LOCAL_MACHINE, CString(  ROOT_AWM_INTRAMON_KEY  ), &hKey );
	if ( lRet != ERROR_SUCCESS ) goto errLabel;
	bKeyOpen = TRUE;
	
	cb = size;
	if ( RegQueryValueEx( hKey, CString(  AWM_CHK_DOMAIN_CTRL_SERVER_IP_KEY  ), 0, &type, ( unsigned char * )cfgVal, 
			( unsigned long * )&cb ) != ERROR_SUCCESS ) 
	{
		goto errLabel;
	}
	cfgVal[cb - 1] = 0;
	
	iRet = 0;
	
errLabel:

	if ( bKeyOpen ) RegCloseKey( hKey );

	return iRet;

}

int CIpInfoDlg::DetectLegalIp(DWORD dwIpAddress)
{
	DWORD dwShield = 0xFF;

	DWORD dwResult = 0;

	dwResult = dwIpAddress & dwShield;

	if(dwResult == 0 ||dwResult == 0xFF )
	   return -1;

	return 0;
}



 void CIpInfoDlg::OnButtonAdd() 
{
	QY_MC			*	pQyMc		=		QY_GET_GBUF(  );
	CString				msg;
	CInforDlg			objInforDlg(0);
	unsigned  int		uiPcsCnt		=	0;
	BOOL				bDel			=	FALSE;
	unsigned  long		ulStartIp  =  0,  ulEndIp  =  0;
	unsigned  long		ulhStartIp  =  0,  ulhEndIp  =  0;
	char				buf[1024]	=  "";

	if  (  objInforDlg.DoModal()  ==  IDOK  )  {
		CString			csSql;
		char			sIP[256];		
		DWORD			dwIp;
		int				len  =  sizeof(  sIP  );

		memset( sIP, 0, len );
		GetRegCfg( sIP, len );
		dwIp = ::inet_addr( sIP );
		if  (  DetectLegalIp(  dwIp  )  )  {
			MessageBox( _T(  "请输入监视端IP地址"  ),  _T(  "错误"  ), MB_OK|MB_ICONERROR );
			return;
		}
		strcpy(  m_stuComputerInfo.interMonIp,  sIP  );

		//  对限制版，需要判断是否超出限制网段数
		if  (  bQwmScannedPcsRestricted(  )  )  {
			ulStartIp  =  inet_addr(  m_stuComputerInfo.cStartIp  );
			ulEndIp  =  inet_addr(  m_stuComputerInfo.cEndIp  );
			if  (  ulStartIp  ==  INADDR_NONE  ||  ulEndIp  ==  INADDR_NONE  )  return;
			ulhStartIp  =  ntohl(  ulStartIp  );  ulhEndIp  =  ntohl(  ulEndIp  );
			if  (  restrictScannedPcs(  &uiPcsCnt,  &bDel  )  )  goto  errLabel;
			if  (  uiPcsCnt  +  (  ulhEndIp  -  ulhStartIp  +  1  )  >  CONST_maxQwmScannedSegs  *  256  )  {
				_snprintf(  buf,  sizeof(  buf  ),  "此版本最多输入%d个C类网段",  CONST_maxQwmScannedSegs  );
				AfxMessageBox(  CString(  buf  )  );  goto  errLabel;
			}
		}

		csSql  =  CString(  "insert into scannedIpTab(interMonIp,Officename,subofficename,startip,endip) values ("  )  +
						"'" + m_stuComputerInfo.interMonIp +"'"+","+
						"'" + m_stuComputerInfo.cUnitInfo +"'"+","+
						"'" + m_stuComputerInfo.cSubOffice +"'"+","+
						"'" + m_stuComputerInfo.cStartIp +"'"+","+
						"'" + m_stuComputerInfo.cEndIp +"'"+")";
		
		try  {
			(  (  CDatabase  *  )pQyMc->gui.pDb  )->ExecuteSQL(csSql);
			InsertSingleInfo(0,m_stuComputerInfo);
			}

		catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CIpInfoDlg::OnButtonAdd failed."  )  );
		}
	}

errLabel:
		
		if  (  bDel  )  FillIpListDlg(  );

}

 
 void  CIpInfoDlg::OnButtonEdit(  ) 
{	
	QY_MC		*	pQyMc				=	QY_GET_GBUF(  );
	CInforDlg		objInfoDlg(  1  );
	CString			msg;
	int				iCount  =  m_cListIpInfo.GetItemCount();
	unsigned  int	uiPcsCnt	=	0;					 
	BOOL			bDel		=	FALSE;
	unsigned  long	ulStartIp	=	0,  ulEndIp		=	0;
	unsigned  long	ulhStartIp	=	0,  ulhEndIp	=	0;
	char			buf[1024];

	for  (  int  nItem  =  0;  nItem  <  iCount;  nItem  ++  )  {
		 if  (  m_cListIpInfo.GetItemState(  nItem,  LVIS_SELECTED  )  ==  LVIS_SELECTED  )  {
			 memcpy(  m_stuNewComputerInfo.cUnitInfo,  m_cListIpInfo.GetItemText(nItem,0),  8  );
			 memcpy(  m_stuNewComputerInfo.cSubOffice,  m_cListIpInfo.GetItemText(nItem,1),  8  );
			 memcpy(  m_stuNewComputerInfo.cStartIp,  m_cListIpInfo.GetItemText(nItem,2),  15  );
			 memcpy(  m_stuNewComputerInfo.cEndIp,  m_cListIpInfo.GetItemText(nItem,3),  15  );

			 ulStartIp  =  inet_addr(  m_stuNewComputerInfo.cStartIp  );  
			 ulEndIp  =  inet_addr(  m_stuNewComputerInfo.cEndIp  );
			 if  (  ulStartIp  ==  INADDR_NONE  ||  ulEndIp  ==  INADDR_NONE  )  goto  errLabel;
			 ulhStartIp  =  ntohl(  ulStartIp  );  ulhEndIp  =  ntohl(  ulEndIp  );

			 if  (  objInfoDlg.DoModal(  )  ==  IDOK  )  {

				 //  对限制版，需要判断是否超出限制
				 if  (  bQwmScannedPcsRestricted(  )  )  {					 
					 if  (  restrictScannedPcs(  &uiPcsCnt,  &bDel )  )  goto  errLabel;
					 uiPcsCnt  -=  ulhEndIp  -  ulhStartIp  +  1;	//  去除编辑栏外的Pc数
					 ulStartIp  =  inet_addr(  m_stuComputerInfo.cStartIp  );
					 ulEndIp  =  inet_addr(  m_stuComputerInfo.cEndIp  );
					 if  (  ulStartIp  ==  INADDR_NONE  ||  ulEndIp  ==  INADDR_NONE  )  goto  errLabel;
					 ulhStartIp  =  ntohl(  ulStartIp  );  ulhEndIp  =  ntohl(  ulEndIp  );
					 uiPcsCnt  +=  ulhEndIp  -  ulhStartIp  +  1;
					 if  (  uiPcsCnt  >=  CONST_maxQwmScannedSegs  *  256  )  {
						 _snprintf(  buf,  sizeof(  buf  ),  "此版本最多输入%d个C类网段",  CONST_maxQwmScannedSegs  );
						 AfxMessageBox(  CString(  buf  )  );  goto  errLabel;
					 }
				 }

				 m_cListIpInfo.SetItemText(  nItem,  0,  CString(  m_stuComputerInfo.cUnitInfo  )  );
				 m_cListIpInfo.SetItemText(  nItem,  1,  CString(  m_stuComputerInfo.cSubOffice  )  );
				 m_cListIpInfo.SetItemText(  nItem,  2,  CString(  m_stuComputerInfo.cStartIp  )  );	
				 m_cListIpInfo.SetItemText(  nItem,  3,  CString(  m_stuComputerInfo.cEndIp  )  );

				 CString  csSql;
				 csSql  =  "UPDATE scannedIpTab SET officeName='" 
					+ ( CString )m_stuComputerInfo.cUnitInfo  + "', subOfficeName='"
					+ ( CString )m_stuComputerInfo.cSubOffice + "', startIp='"
					+ ( CString )m_stuComputerInfo.cStartIp + "', endIp='"
					+ ( CString )m_stuComputerInfo.cEndIp + "'"
					+ " WHERE officeName = '" + (CString)m_stuNewComputerInfo.cUnitInfo + "' AND " 
					+ "subOfficeName = '" + (CString)m_stuNewComputerInfo.cSubOffice + "' AND "
					+ "startIp = '" + (CString)m_stuNewComputerInfo.cStartIp + "' AND "
					+ "endIp = '" + (CString)m_stuNewComputerInfo.cEndIp + "'";

				try  {
					(  (  CDatabase  *  )pQyMc->gui.pDb  )->ExecuteSQL(csSql);
					}
				catch  (  CException  *  e  )  {
					   e->Delete(  );
					   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CIpInfoDlg::OnButtonEdit failed."  )  );
				}
			}
			break;
		}	
	}

errLabel:

	if  (  bDel  )  FillIpListDlg(  );

}

 void CIpInfoDlg::OnButtonDel() 
{
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	CString msg;
	CIpDataSet objIpDataSet;
	int nReturn;

	POSITION pos = m_cListIpInfo.GetFirstSelectedItemPosition();
	if (pos == NULL) 
		return;
	else
	{
		nReturn = MessageBox(  _T(  "确定要删除吗?"  ), _T(  "删除规则"  ), MB_YESNO|MB_ICONQUESTION|MB_DEFBUTTON2 );
		if( nReturn ==IDYES)
		{
			int iCount=m_cListIpInfo.GetItemCount();
			for(int middle=iCount;middle>0;middle--)
			{
				for(int nItem=0;nItem<middle;nItem++)
				{   
					if(m_cListIpInfo.GetItemState(nItem,LVIS_SELECTED)==LVIS_SELECTED)
					{
						memcpy(m_stuComputerInfo.cUnitInfo ,m_cListIpInfo.GetItemText(nItem,0),8);
						memcpy(m_stuComputerInfo.cSubOffice ,m_cListIpInfo.GetItemText(nItem,1),8);
						memcpy(m_stuComputerInfo.cStartIp  ,m_cListIpInfo.GetItemText(nItem,2),15);
						memcpy(m_stuComputerInfo.cEndIp, m_cListIpInfo.GetItemText(nItem,3),15);

						CString csSql;
						csSql = CString ("delete from scannedIpTab where ") 
							+ "Officename = '" + (char *)m_stuComputerInfo.cUnitInfo +"' AND "
							+ "subofficename = '" + (char *)m_stuComputerInfo.cSubOffice +"' AND "
							+ "startip = '" + (char *)m_stuComputerInfo.cStartIp +"' AND "
							+ "endip = '" + (char *)m_stuComputerInfo.cEndIp +"'" ;

						try
						{
							(  (  CDatabase  *  )pQyMc->gui.pDb  )->ExecuteSQL(csSql);
							m_cListIpInfo.DeleteItem(nItem);
						}

						catch  (  CException  *  e  )  {
		           			   e->Delete(  );
		   					   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CIpInfoDlg::OnButtonDel failed."  )  );
						}
					}
				}
			}
		}
	}
}


void CIpInfoDlg::OnDblclkListIpinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
		
	OnButtonEdit();
	
	*pResult = 0;
}

