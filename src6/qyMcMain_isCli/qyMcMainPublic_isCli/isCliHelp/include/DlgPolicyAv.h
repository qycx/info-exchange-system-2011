#pragma once


// CDlgPolicyAv dialog

class CDlgPolicyAv : public CDialog
{
	DECLARE_DYNAMIC(CDlgPolicyAv)

public:
	CDlgPolicyAv(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPolicyAv();

// Dialog Data
	enum { IDD = IDD_policyAv };

	struct				{
		unsigned  int	uiCapType;
		unsigned  int	uiSubCapType;
		BOOL			bReply;

		//  int				level;

#if  0
		POLICY_av		oldPolicyAv;
		POLICY_av		policyAv;
#endif

		struct												{
			AV_COMPRESSOR_CFG								avCompressor_req;
			AV_COMPRESSOR_CFG								avCompressor_reply;
		}				oldPolicyAv,  policyAv;


	}					m_var;

	//  BOOL	bSetDlgInfo(  int  level  );
	BOOL	bSetDlgInfo(  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  BOOL  bReply  );
	BOOL	bShowPolicy(  );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
#if  0
	afx_msg void OnBnClickedButtonavcompressor();
	afx_msg void OnBnClickedButtonscreencompressor();
	afx_msg void OnBnClickedButtonmediafilecompressor();
	afx_msg void OnBnClickedButtonwebcamcompressor();
	afx_msg void OnBnClickedButtonmediadevicecompressor();
#endif

	afx_msg void OnBnClickedButtonsetldsettings();
	afx_msg void OnBnClickedButtonsetld1settings();
	afx_msg void OnBnClickedButtonsetsdsettings();
	afx_msg void OnBnClickedButtonsetsd1settings();
	afx_msg void OnBnClickedButtonsetsd2settings();
	afx_msg void OnBnClickedButtonsetsd3settings();
	afx_msg void OnBnClickedButtonsethdsettings();
	afx_msg void OnBnClickedButtonsethd1settings();
	afx_msg void OnBnClickedButtonsethd2settings();
	afx_msg void OnBnClickedButtonsethd3settings();
	afx_msg void OnBnClickedButtonsetfullhdsettings();
	afx_msg void OnBnClickedButtonsetfullhd1settings();
	afx_msg void OnBnClickedButtonsetfullhd2settings();
	afx_msg void OnBnClickedButtonsetfullhd3settings();
	afx_msg void OnBnClickedButtonsetdev2fpssettings();
	afx_msg void OnBnClickedButtonsetdev5fpssettings();
	afx_msg void OnBnClickedButtonsetdev5fpssettings1();
	afx_msg void OnBnClickedButtonsetdev5fpssettings2();
	afx_msg void OnBnClickedButtonsetdev5fpssettings3();
	afx_msg void OnBnClickedButtonsetdev5fpssettings4();
	afx_msg void OnBnClickedButtonsetdev5fpssettings5();
	afx_msg void OnBnClickedButtonsetdev10fpssettings();
	afx_msg void OnBnClickedButtonsetdevsd24fpssettings();
	afx_msg void OnBnClickedButtonsetdevsd25fpssettings();
	afx_msg void OnBnClickedButtonsetdevsd30fpssettings();
	afx_msg void OnBnClickedButtonsetdev24fpssettings();
	afx_msg void OnBnClickedButtonsetdev25fpssettings();
	afx_msg void OnBnClickedButtonsetdev30fpssettings();
};
