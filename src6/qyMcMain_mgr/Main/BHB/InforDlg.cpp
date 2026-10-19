// InforDlg.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"bhbSrc1CommProc.h"
//#include	"NetTracer.h"
#include	"InforDlg.h"
#include	"IpInfoDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInforDlg dialog


CInforDlg::CInforDlg(int iType,CWnd* pParent /*=NULL*/)
	: CDialog(CInforDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInforDlg)
	m_csComInfo = _T("");
	m_csDepart = _T("");
	m_iFlag = iType;
	//}}AFX_DATA_INIT
}


void CInforDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInforDlg)
	DDX_Control(pDX, IDC_IPADDRESS_INTRA_START, m_cIntraStartIp);
	DDX_Control(pDX, IDC_IPADDRESS_INTRA_END, m_cIntraEndIp);
	DDX_Text(pDX, IDC_EDIT_COMINFO, m_csComInfo);
	DDV_MaxChars(pDX, m_csComInfo, 8);
	DDX_Text(pDX, IDC_EDIT_DEPART, m_csDepart);
	DDV_MaxChars(pDX, m_csDepart, 8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInforDlg, CDialog)
	//{{AFX_MSG_MAP(CInforDlg)
	ON_BN_CLICKED(IDC_BUTTON_ADD_IP, OnButtonAddIp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInforDlg message handlers

void CInforDlg::OnOK() 
{
	UpdateData(TRUE);

	ZeroMemory(&m_stuComputerInfo,sizeof(COMPUTER_IP_INFO));
	
	m_cIntraStartIp.GetAddress(m_dwIntraStartIp);
	m_cIntraEndIp.GetAddress(m_dwIntraEndIp);

	//1.
	if(m_csDepart == "")
	{
		MessageBox(  _T(  "请输入单位名称\n请重新输入"  ),  _T(  "注意"  ),  MB_OK|MB_ICONERROR  );
		return ;
	}

	memcpy(m_stuComputerInfo.cUnitInfo,m_csDepart,8);
	memcpy(m_stuComputerInfo.cSubOffice,m_csComInfo,8);
	
	if(m_dwIntraStartIp != 0 && m_dwIntraEndIp == 0)
	{
		m_dwIntraEndIp = m_dwIntraStartIp;
		if(DetectLegalIp(m_dwIntraStartIp) == -1)
		{
			MessageBox(  _T(  "IP地址输入错误\n请重新输入"  ),  _T(  "注意"  ),  MB_OK|MB_ICONERROR  );
			return ;
		}
		else
		{
			m_dwIntraStartIp = ::htonl((unsigned long)m_dwIntraStartIp);
			struct in_addr inaddr;
			inaddr.S_un.S_addr = (unsigned long)m_dwIntraStartIp;
			memcpy(m_stuComputerInfo.cStartIp,::inet_ntoa(inaddr),15);
			memcpy(m_stuComputerInfo.cEndIp,::inet_ntoa(inaddr),15);
		}
	}
	else
	{
		if(DetectLegalIp(m_dwIntraStartIp) == -1){
			MessageBox(  _T(  "起始IP地址输入错误\n请重新输入"  ),  _T(  "注意"  ),MB_OK|MB_ICONERROR );
			return ;
		}
		else
		{
			m_dwIntraStartIp = ::htonl((unsigned long)m_dwIntraStartIp);
			struct in_addr inaddr;
			inaddr.S_un.S_addr = (unsigned long)m_dwIntraStartIp;
			memcpy(m_stuComputerInfo.cStartIp,::inet_ntoa(inaddr),15);
		}
		
		if(DetectLegalIp(m_dwIntraEndIp) == -1)
		{
			MessageBox(  _T(  "结束IP地址输入错误\n请重新输入"  ),  _T(  "注意"  ),MB_OK|MB_ICONERROR );
			return ;
		}
		else
		{
			m_dwIntraEndIp = ::htonl((unsigned long)m_dwIntraEndIp);
			struct in_addr inaddr;
			inaddr.S_un.S_addr = (unsigned long)m_dwIntraEndIp;
			memcpy(m_stuComputerInfo.cEndIp,::inet_ntoa(inaddr),15);
		}
		// if(m_dwIntraStartIp > m_dwIntraEndIp)
		if  (  ntohl(  m_dwIntraStartIp  )  >   ntohl(  m_dwIntraEndIp  )  )
		{
			MessageBox(  _T(  "起始IP地址大于结束IP地址\n请重新输入"  ),  _T(  "注意"  ),  MB_OK|MB_ICONERROR  );
			return ;
		}
	}
	
	CDialog::OnOK();
}

void CInforDlg::OnButtonAddIp() 
{	
}

int CInforDlg::DetectLegalIp(DWORD dwIpAddress)
{
	DWORD dwShield = 0xFF;

	DWORD dwResult = 0;

	dwResult = dwIpAddress & dwShield;

	if(dwResult == 0 ||dwResult == 0xFF )
	   return -1;

	return 0;
}


BOOL CInforDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if(m_iFlag == 1)
	{
		m_csDepart  += m_stuNewComputerInfo.cUnitInfo;
		m_csComInfo  += m_stuNewComputerInfo.cSubOffice;

		DWORD dwIpAddress = inet_addr(m_stuNewComputerInfo.cStartIp);
		m_cIntraStartIp.SetAddress(ntohl(dwIpAddress));

		dwIpAddress = inet_addr(m_stuNewComputerInfo.cEndIp);
		m_cIntraEndIp.SetAddress(ntohl(dwIpAddress));

		UpdateData(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
