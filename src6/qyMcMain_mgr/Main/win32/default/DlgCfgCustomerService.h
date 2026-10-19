#pragma once


// CDlgCfgCustomerService dialog

class CDlgCfgCustomerService : public CDialog
{
	DECLARE_DYNAMIC(CDlgCfgCustomerService)

public:
	CDlgCfgCustomerService(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgCfgCustomerService();

// Dialog Data
	enum { IDD = IDD_cfgCustomerService };

	struct								{
		QY_OBJ_DB					*	pObjDb;
		
		TCHAR							misServName[CONST_maxMisServNameLen  +  1];
		QY_MESSENGER_ID					idInfo;
		
		int								id;
		//

		CUSTOMER_serviceObj_rcd		oldRcd;
		CUSTOMER_serviceObj_rcd		rcd;

	}				m_var;

	BOOL  bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  id  );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
