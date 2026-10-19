#if !defined(AFX_QYPS_H__8162ECB2_2135_4026_8BB1_3C4DD442C219__INCLUDED_)
#define AFX_QYPS_H__8162ECB2_2135_4026_8BB1_3C4DD442C219__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QyPs.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CQyPs

typedef  struct  __qyStatusStruct_t				{
	
				 unsigned  short				usLangId;

				 QNM_CUSRES_INFO				cusRes;
				 unsigned  char					ucbCusResInited;

				 BOOL							bQuit;

				 HANDLE							hThreads[2];

				 HWND							hPs;									//  propertySheet的句柄，2006/08/16

				 TCHAR							serviceStatus_netMc[255  +  1];				//  用来保存
				 TCHAR							qmdState_netMc[255  +  1];
				 TCHAR							serviceStatus_is[255  +  1];
				 TCHAR							qmdState_is[255  +  1];

}		 QY_STATUS_STRUCT;


class CQyPs : public CPropertySheet
{
	DECLARE_DYNAMIC(CQyPs)

// Construction
public:
	CQyPs(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CQyPs(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	struct								{
		int								iType;
		BOOL							bProcCurQueryOnly;
		
		union							{
			QY_IMEXPORTINFO				imExportInfo;
			QY_CLEARUPINFO				clearupInfo;
			struct						{
				int						iShowFlgs[1];		//  qyShowInfo的开关标志
				//
				char					serviceName_netMc[128];
				BOOL					bServiceRunning_netMc;
				char					serviceName_is[128];
				BOOL					bServiceRunning_is;
				//
				CPropertyPage		*	pActivePage;
				QY_STATUS_STRUCT		statusStruct;
			}							showInfo;
		}								u;
	}									m_var;
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQyPs)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CQyPs();

	// Generated message map functions
protected:
	//{{AFX_MSG(CQyPs)
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	afx_msg  void  OnOK(  );
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QYPS_H__8162ECB2_2135_4026_8BB1_3C4DD442C219__INCLUDED_)


