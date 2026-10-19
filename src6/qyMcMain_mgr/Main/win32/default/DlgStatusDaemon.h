#pragma once


// CDlgStatusDaemon dialog

class CDlgStatusDaemon : public CDialog
{
	DECLARE_DYNAMIC(CDlgStatusDaemon)

public:
	CDlgStatusDaemon(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgStatusDaemon();

// Dialog Data
	enum { IDD = IDD_status_daemon };

	struct									{
			CWnd					*		m_pParent;
			int								m_nID;
			BOOL							bInfoSet;
			BOOL							bCreated;					//  
			BOOL							bInited;					//  

			int								iDaemonStatusType;			//  2011/01/28

			GET_daemonStatus_req			curInfo;

			int								iEdge_list_x;
			int								iTop_list;

	}										m_var;

	BOOL Create(const RECT& rect);
	BOOL  bQuitDlg(  );		
	int  sizeAllControls(  );
	int  listDaemonStatus(  int i,  BOOL  bInsert,  DAEMON_status_msgrMem  *  pNew    );
	int  listDaemonStatus(  int i,  BOOL  bInsert,  DAEMON_status_channelMem  *  pNew    );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnQyComm(  WPARAM, LPARAM  );

	afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
public:
};
