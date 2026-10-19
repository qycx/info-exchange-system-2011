#pragma once


// CPpExportClients dialog

class CPpExportClients : public CPropertyPage
{
	DECLARE_DYNAMIC(CPpExportClients)

public:
	CPpExportClients();
	virtual ~CPpExportClients();

// Dialog Data
	enum { IDD = IDD_exportClients };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadiodefault();
	afx_msg void OnBnClickedRadiotslogon();
	afx_msg void OnBnClickedRadiotsdev();
	virtual BOOL OnSetActive();
	virtual BOOL OnWizardFinish();
};
