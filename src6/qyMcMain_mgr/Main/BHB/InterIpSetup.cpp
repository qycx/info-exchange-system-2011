// InterIpSetup.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"bhbSrc1CommProc.h"
#include	"myresource.h"
#include	"InterIpSetup.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//  extern "C" int qySetRegCfg( char *rootKey, char *cfgName, char *cfgVal );


/////////////////////////////////////////////////////////////////////////////
// CInterIpSetup dialog


CInterIpSetup::CInterIpSetup(CWnd* pParent /*=NULL*/)
	: CDialog(CInterIpSetup::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInterIpSetup)
	m_nScanInterval = 10;
	m_nScanIntervalPerCNetSeg = 10;
	m_nScanIntervalPerPc = 0;
	//}}AFX_DATA_INIT
}


void CInterIpSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInterIpSetup)
	DDX_Control(pDX, IDC_IPADDRESS_INTER3, m_cInterIpAddress3);
	DDX_Control(pDX, IDC_IPADDRESS_INTER2, m_cInterIpAddress2);
	DDX_Control(pDX, IDC_IPADDRESS_INTER1, m_cInterIpAddress1);
	DDX_Control(pDX, IDC_IPADDRESS_INTER0, m_cInterIpAddress0);
	DDX_Control(pDX, IDC_IPADDRESS_INTER, m_cInterIpAddress);
	DDX_Text(pDX, IDC_SCANINTERVAL, m_nScanInterval);
	DDV_MinMaxUInt(pDX, m_nScanInterval, 5, 86400);
	DDX_Text(pDX, IDC_scanIntervalPerCNetSeg, m_nScanIntervalPerCNetSeg);
	DDV_MinMaxUInt(pDX, m_nScanIntervalPerCNetSeg, 5, 3600);
	DDX_Text(pDX, IDC_scanIntervalPerPc, m_nScanIntervalPerPc);
	DDV_MinMaxUInt(pDX, m_nScanIntervalPerPc, 0, 1000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInterIpSetup, CDialog)
	//{{AFX_MSG_MAP(CInterIpSetup)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterIpSetup message handlers
void CInterIpSetup::WriteIp2Reg(DWORD dwIpAddress)
{
	int iRet = -1;
	BOOL bKeyCreated = FALSE;
	HKEY hKey;
	int rc = -1;
	char buf[256];

	char cIpBuf[16];
	ZeroMemory(cIpBuf,16);
	struct in_addr inaddr;
	inaddr.S_un.S_addr = (unsigned long)dwIpAddress;
	memcpy(cIpBuf,::inet_ntoa(inaddr),15);

	sprintf( buf, "%s", "127.0.0.1" );

	if ( ( rc = RegCreateKey( HKEY_LOCAL_MACHINE, CString(  ROOT_AWM_INTRAMON_KEY  ), &hKey ) ) != ERROR_SUCCESS ) 
	{
		char buf[128];
		sprintf( buf, "RegCreate returns %d", rc );
		return;
	}
	bKeyCreated = TRUE;
	if ( RegSetValueEx( hKey, CString(  AWM_CHK_DOMAIN_CTRL_SERVER_IP_KEY  ), 0, REG_SZ, ( const unsigned char * )cIpBuf, strlen( cIpBuf ) ) != ERROR_SUCCESS ) 
	{
		return;
	}
	
	RegCloseKey(  hKey  );		//  added  by  ywm  on 2002/10/09

}


 void  CInterIpSetup::newWriteIp2Reg(  char  *  ipValName,  DWORD  dwIpAddress  )
{
	int iRet = -1;
	BOOL bKeyCreated = FALSE;
	HKEY hKey;
	int rc = -1;
	char buf[256];

	char cIpBuf[16];
	ZeroMemory(cIpBuf,16);
	struct in_addr inaddr;
	inaddr.S_un.S_addr = (unsigned long)dwIpAddress;
	//  memcpy(cIpBuf,::inet_ntoa(inaddr),15);
	strcpy(  cIpBuf,  ::inet_ntoa(  inaddr  )  );

	sprintf( buf, "%s", "127.0.0.1" );

	if ( ( rc = RegCreateKey( HKEY_LOCAL_MACHINE, CString(  ROOT_AWM_INTRAMON_KEY  ), &hKey ) ) != ERROR_SUCCESS ) 
	{
		char buf[128];
		sprintf( buf, "RegCreate returns %d", rc );
		return;
	}
	bKeyCreated = TRUE;
	if ( RegSetValueEx( hKey, CString(  ipValName  ), 0, REG_SZ, ( const unsigned char * )cIpBuf, strlen( cIpBuf ) ) != ERROR_SUCCESS ) 
	{
		return;
	}
	
	RegCloseKey(  hKey  );		//  added  by  ywm  on 2002/10/09

}


int CInterIpSetup::GetRegCfg( char *cfgVal, int size )
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

int CInterIpSetup::DetectLegalIp(DWORD dwIpAddress)
{
	DWORD dwShield = 0xFF;

	DWORD dwResult = 0;

	dwResult = dwIpAddress & dwShield;

	if(dwResult == 0 ||dwResult == 0xFF )
	   return -1;

	return 0;
}

/*
 void CInterIpSetup::OnOK() 
{
	CString msg;
	struct in_addr inaddr;
	char cIpBuf[16];
	CString csSql;

	UpdateData(TRUE);
	m_cInterIpAddress.GetAddress(m_dwInterIpAddress);

	if( DetectLegalIp( m_dwInterIpAddress ) ){
		MessageBox( "请输入合法的IP值!", "IP错误", MB_OK|MB_ICONWARNING );
		return;
	}

	m_dwInterIpAddress = ::htonl((unsigned long)m_dwInterIpAddress);

	WriteIp2Reg(m_dwInterIpAddress);
	
	inaddr.S_un.S_addr = (unsigned long)m_dwInterIpAddress;
	
	ZeroMemory(cIpBuf,16);
	memcpy(cIpBuf,::inet_ntoa(inaddr),15);
	
	csSql = "UPDATE scannedIpTab SET interMonIp='" 
		+ ( CString )cIpBuf  + "'";

	try
	{
		(  (  CDatabase  *  )pQyMc->gui.pDb  )->ExecuteSQL(csSql);
	}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CInterIpSetup::OnOK failed."  )  );
	}

	CDialog::OnOK();

}
*/

 // 上面的代码被下面替换，2002/10/09
 void CInterIpSetup::OnOK() 
{
	//  CString msg;
	//  struct in_addr inaddr;
	//  char cIpBuf[16];
	//  CString csSql;
	 char  buf[256];

	if  (  !UpdateData(TRUE)  )  return;
	
	m_cInterIpAddress.GetAddress(m_dwInterIpAddress);
	if( DetectLegalIp( m_dwInterIpAddress ) ){
		MessageBox(  _T(  "请输入合法的IP值!"  ),  _T(  "IP错误"  ), MB_OK|MB_ICONWARNING );
		return;
	}
	m_dwInterIpAddress = ::htonl((unsigned long)m_dwInterIpAddress);
	WriteIp2Reg(m_dwInterIpAddress);

	/*		//  被注释，因为已改为靠注册表来存放4个监视端ip
	*/

	BOOL	bIpInputOk   =	FALSE;

	m_cInterIpAddress0.GetAddress(m_dwInterIpAddress0);
	m_cInterIpAddress1.GetAddress(m_dwInterIpAddress1);
	m_cInterIpAddress2.GetAddress(m_dwInterIpAddress2);
	m_cInterIpAddress3.GetAddress(m_dwInterIpAddress3);

	if  (  DetectLegalIp(  m_dwInterIpAddress0  )  
		&&  DetectLegalIp(  m_dwInterIpAddress1  )  
			&&  DetectLegalIp(  m_dwInterIpAddress2  )  
				&&  DetectLegalIp(  m_dwInterIpAddress3  )  )
	{
		MessageBox(  _T(  "请输入至少一个合法的IP值!"  ),  _T(  "IP错误"  ), MB_OK|MB_ICONWARNING );
		return;
	}

	m_dwInterIpAddress  =  m_dwInterIpAddress0;
	if( !DetectLegalIp( m_dwInterIpAddress ) ){
		m_dwInterIpAddress = ::htonl((unsigned long)m_dwInterIpAddress);
		newWriteIp2Reg(  CONST_regValName_newInterMonIp0,  m_dwInterIpAddress  );
		}
	else 
		qyDelRegCfg(  _T(  ROOT_AWM_INTRA_MON_KEY  ),  _T(  CONST_regValName_newInterMonIp0  )  );

	m_dwInterIpAddress  =  m_dwInterIpAddress1;
	if( !DetectLegalIp( m_dwInterIpAddress ) ){
		m_dwInterIpAddress = ::htonl((unsigned long)m_dwInterIpAddress);
		newWriteIp2Reg(  CONST_regValName_newInterMonIp1,  m_dwInterIpAddress  );
		}
	else 
		qyDelRegCfg(  _T(  ROOT_AWM_INTRA_MON_KEY  ),  _T(  CONST_regValName_newInterMonIp1  )  );

	m_dwInterIpAddress  =  m_dwInterIpAddress2;
	if( !DetectLegalIp( m_dwInterIpAddress ) ){
		m_dwInterIpAddress = ::htonl((unsigned long)m_dwInterIpAddress);
		newWriteIp2Reg(  CONST_regValName_newInterMonIp2,  m_dwInterIpAddress  );
		}
	else 
		qyDelRegCfg(  _T(  ROOT_AWM_INTRA_MON_KEY  ),  _T(  CONST_regValName_newInterMonIp2  )  );

	m_dwInterIpAddress  =  m_dwInterIpAddress3;
	if( !DetectLegalIp( m_dwInterIpAddress ) ){
		m_dwInterIpAddress = ::htonl((unsigned long)m_dwInterIpAddress);
		newWriteIp2Reg(  CONST_regValName_newInterMonIp3,  m_dwInterIpAddress  );
		}
	else 
		qyDelRegCfg(  _T(  ROOT_AWM_INTRA_MON_KEY  ),  _T(  CONST_regValName_newInterMonIp3  )  );

	_snprintf(  buf,  sizeof(  buf  ),  "%d",  this->m_nScanIntervalPerPc  );
	qySetRegCfg(  _T(  ROOT_AWM_INTRA_MON_KEY  ),  _T(  CONST_regValName_scanIntervalPerPcInMilliSecond  ),  CString(  buf  )  );

	sprintf(  buf,  "%d",  m_nScanInterval  );
	qySetRegCfg(  _T(  ROOT_AWM_INTRA_MON_KEY  ),  _T(  CONST_regValName_scanIntervalInSecond  ),  CString(  buf  )  );
	
	sprintf(  buf,  "%d",  m_nScanIntervalPerCNetSeg  );
	qySetRegCfg(  _T(  ROOT_AWM_INTRA_MON_KEY  ),  _T(  CONST_regValName_scanIntervalPerCNetSegInSecond  ),  CString(  buf  )  );

	CDialog::OnOK();

}

BOOL CInterIpSetup::OnInitDialog() 
{
	CDialog::OnInitDialog();

	char	sIP[256];
	int		len				=	sizeof(  sIP  );
	DWORD	dwIpAddress;
	char	buf[256];
	int		nScanInterval;
	int		nScanIntervalPerCNetSeg;
	int		nScanIntervalPerPc;


	memset(  sIP,  0,  sizeof(  sIP  )  );
	
	/*		//  被注释  2002/10/09
	if( !GetRegCfg( sIP, len ) ){
		dwIpAddress = ::inet_addr( sIP );	
		dwIpAddress = ::ntohl( ( unsigned long)dwIpAddress );
		m_cInterIpAddress.SetAddress( dwIpAddress );	
	}
	*/

	//  原有的ipAddress控件已被废弃(使用Invisible的方式), 这里给置一固定值，以避免后面的校验
	m_cInterIpAddress.SetAddress(  128,  0,  0,  1  );
	
	if  (  !qyGetRegCfg(  _T(  ROOT_AWM_INTRA_MON_KEY  ),  _T(  CONST_regValName_newInterMonIp0  ),  sIP,  sizeof(  sIP  )  )  )  {
		dwIpAddress = ::inet_addr( sIP );	
		dwIpAddress = ::ntohl( ( unsigned long)dwIpAddress );
		m_cInterIpAddress0.SetAddress( dwIpAddress );	
	}
	if  (  !qyGetRegCfg(  _T(  ROOT_AWM_INTRA_MON_KEY  ),  _T(  CONST_regValName_newInterMonIp1  ),  sIP,  sizeof(  sIP  )  )  )  {
		dwIpAddress = ::inet_addr( sIP );	
		dwIpAddress = ::ntohl( ( unsigned long)dwIpAddress );
		m_cInterIpAddress1.SetAddress( dwIpAddress );	
	}
	if  (  !qyGetRegCfg(  _T(  ROOT_AWM_INTRA_MON_KEY  ),  _T(  CONST_regValName_newInterMonIp2  ),  sIP,  sizeof(  sIP  )  )  )  {
		dwIpAddress = ::inet_addr( sIP );	
		dwIpAddress = ::ntohl( ( unsigned long)dwIpAddress );
		m_cInterIpAddress2.SetAddress( dwIpAddress );	
	}
	if  (  !qyGetRegCfg(  _T(  ROOT_AWM_INTRA_MON_KEY  ),  _T(  CONST_regValName_newInterMonIp3  ),  sIP,  sizeof(  sIP  )  )  )  {
		dwIpAddress = ::inet_addr( sIP );	
		dwIpAddress = ::ntohl( ( unsigned long)dwIpAddress );
		m_cInterIpAddress3.SetAddress( dwIpAddress );	
	}
	
	//  扫描间歇
	nScanInterval  =  0;
	if  (  !qyGetRegCfg(  _T(  ROOT_AWM_INTRA_MON_KEY  ),  _T(  CONST_regValName_scanIntervalInSecond  ),  buf,  sizeof(  buf  )  )  )  {
		nScanInterval  =  atol(  buf  );
	}

	if  (  nScanInterval  <=  CONST_max_nScanIntervalInSecond  &&  nScanInterval  >=  CONST_min_nScanIntervalInSecond  )  {
		m_nScanInterval  =  nScanInterval;
		}
	else  m_nScanInterval  =  CONST_min_nScanIntervalInSecond;

	SetDlgItemInt(  IDC_SCANINTERVAL,  m_nScanInterval  );

	//  扫描网段间歇
	nScanIntervalPerCNetSeg  =  0;
	if  (  !qyGetRegCfg(  _T(  ROOT_AWM_INTRA_MON_KEY  ),  _T(  CONST_regValName_scanIntervalPerCNetSegInSecond  ),  buf,  sizeof(  buf  )  )  )  {
		nScanIntervalPerCNetSeg  =  atol(  buf  );
	}
	if  (  nScanIntervalPerCNetSeg  <=  CONST_max_nScanIntervalPerCNetSegInSecond  &&  nScanIntervalPerCNetSeg  >=  CONST_min_nScanIntervalPerCNetSegInSecond  )  {
		m_nScanIntervalPerCNetSeg  =  nScanIntervalPerCNetSeg;
		}
	else  m_nScanIntervalPerCNetSeg  =  DEFAULT_nScanIntervalPerCNetSegInSecond;

	SetDlgItemInt(  IDC_scanIntervalPerCNetSeg,  m_nScanIntervalPerCNetSeg  );

	//  扫描主机间歇
	nScanIntervalPerPc		=	0;
	if  (  !qyGetRegCfg(  _T(  ROOT_AWM_INTRA_MON_KEY  ),  _T(  CONST_regValName_scanIntervalPerPcInMilliSecond  ),  buf,  sizeof(  buf  )  )  )  {
		nScanIntervalPerPc  =  atol(  buf  );
	}
	if  (  nScanIntervalPerPc  >  CONST_max_nScanIntervalPerPcInMilliSecond  )  m_nScanIntervalPerPc  =  CONST_max_nScanIntervalPerPcInMilliSecond;
	else  m_nScanIntervalPerPc  =  nScanIntervalPerPc;

	SetDlgItemInt(  IDC_scanIntervalPerPc,  m_nScanIntervalPerPc  );


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
