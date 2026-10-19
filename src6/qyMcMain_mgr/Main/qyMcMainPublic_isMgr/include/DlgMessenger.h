#pragma once


// CDlgMessenger dialog

class CDlgMessenger : public CDialog
{
	DECLARE_DYNAMIC(CDlgMessenger)

public:
	CDlgMessenger(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgMessenger();

// Dialog Data
	enum { IDD = IDD_messenger };

	struct				{
		int				iDlgType;
		QY_OBJ_DB	*	pObjDb;
		TCHAR			misServName[CONST_maxMisServNameLen  +  1];
		QY_MESSENGER_ID	idInfo;
		int				id;

		QY_imAm_RCD		rcd;
	}					m_var;

	BOOL  bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
};
