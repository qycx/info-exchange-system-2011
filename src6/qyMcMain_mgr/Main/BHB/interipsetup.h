#if !defined(AFX_INTERIPSETUP_H__B583A095_3361_4E6B_B084_3D644208A575__INCLUDED_)
#define AFX_INTERIPSETUP_H__B583A095_3361_4E6B_B084_3D644208A575__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InterIpSetup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInterIpSetup dialog

class CInterIpSetup : public CDialog
{
// Construction
public:
	CInterIpSetup(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInterIpSetup)
	enum { IDD = IDD_DLG_IPSETUP };
	CIPAddressCtrl	m_cInterIpAddress3;
	CIPAddressCtrl	m_cInterIpAddress2;
	CIPAddressCtrl	m_cInterIpAddress1;
	CIPAddressCtrl	m_cInterIpAddress0;
	CIPAddressCtrl	m_cInterIpAddress;
	UINT	m_nScanInterval;
	UINT	m_nScanIntervalPerCNetSeg;
	UINT	m_nScanIntervalPerPc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterIpSetup)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	DWORD m_dwInterIpAddress;

	DWORD m_dwInterIpAddress0;	//  added by ywm, 仅用于为OnOK中提供临时变量，
	DWORD m_dwInterIpAddress1;
	DWORD m_dwInterIpAddress2;
	DWORD m_dwInterIpAddress3;

	
	void WriteIp2Reg(DWORD dwIpAddress);
	void  newWriteIp2Reg(  char  *  ipValName,  DWORD  dwIpAddress  );	//  added by ywm on 2002/10/09
	int GetRegCfg( char *cfgVal, int size );
	int DetectLegalIp(DWORD dwIpAddress);
	
	// Generated message map functions
	//{{AFX_MSG(CInterIpSetup)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERIPSETUP_H__B583A095_3361_4E6B_B084_3D644208A575__INCLUDED_)
