#pragma once

typedef  struct  __dlgInstantAssistantVar_t				{
				 BOOL									bVideoConferenceStarter;
				 //
				 //  int									m_nID;
				 BOOL									bCreated;

				 struct									{
					 int								iEdge_t;
					 int								iEdge_l;

					 int								iW_btn_request;
					 int								iW_btn,  iH_btn;
			
					 int								iX_spacing;
					 int								iY_spacing;

					 int								iW_talkerList,  iH_talkerList;
		
					 //  int								iW_usLayoutType,  iH_usLayoutType;		//  2010/12/21

					 int								iW_status,  iH_status;					//  2010/12/22

					 int								iW_dlg,  iH_dlg;
					 int								iW_dlg_more,  iH_dlg_more;

				 }										oldLayout;
		
				 int									idcList;
				 QY_COLUMNINFO					*		pColumns;

				 //  2013/07/04
				 void							*		pm_LargeImageList;
				 void							*		pm_SmallImageList;

				 //
				 VIDEO_CONFERENCE_STATUS				videoConferenceStatus;

				 //
				 BOOL									bTaskAvInited;

				 //
				 BOOL									canSpeak;

				 //
				 DLG_guiData_instantAssistant			guiData;

				 //
				 UINT_PTR								wTimerID;

				 DWORD									dwTickCnt_lastMouseMove;			//  2010/08/29

				 //  2013/02/17
				 DLG_syncFlgs							syncFlgs;

}		 DLG_instantAssistant_var;


#ifdef  __SUPPORT_dlgInstantAssistant_mfc__

// CDlgInstantAssistant dialog


class CDlgInstantAssistant : public CDialog
{
	DECLARE_DYNAMIC(CDlgInstantAssistant)

public:
	CDlgInstantAssistant(HWND  hParent = NULL);   // standard constructor
	virtual ~CDlgInstantAssistant();

// Dialog Data
	enum { IDD = IDD_instantAssistant_0 };

public:

	DLG_instantAssistant_var			m_var;

	CBrush								m_brush_bk_status;

#if  0
	CImageList							m_LargeImageList;
	CImageList							m_SmallImageList;
#endif

protected:
	
public:
	BOOL	Create(const RECT& rect);
	BOOL	bQuitDlg(  );
	int		fillTalkerList(  );
	int		initForTaskAv(  );
	//  int		requestToSpeak(  BOOL  bEnable  );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedrequest();
	afx_msg LRESULT OnQyComm(  WPARAM, LPARAM  );
protected:
	virtual void PostNcDestroy();
	virtual void OnCancel();
public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
//	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNMRClicktalkerlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//  afx_msg void OnCbnSelchangeCombouslayouttype();
	afx_msg void OnBnClickedButtonav();
	afx_msg void OnBnClickedButtonavaccept();
	afx_msg void OnBnClickedButtonavdeny();
	afx_msg void OnBnClickedButtonsharescreen();
	afx_msg void OnBnClickedButtonmsgbox();
	afx_msg void OnBnClickedButtonfullscreen();
	afx_msg void OnBnClickedButtonenlarge();
	afx_msg void OnBnClickedButtonclose();
	afx_msg void OnBnClickedButtonmore();
	afx_msg void OnBnClickedButtonrule();
	afx_msg void OnBnClickedButtonnonexclusive();
	afx_msg void OnBnClickedButtonmsg();
	afx_msg void OnBnClickedButtonsharemediafile();
	afx_msg void OnBnClickedButtonshowdlgmenu();
	afx_msg void OnBnClickedButtoncloseandclean();
	afx_msg void OnBnClickedButtonremoteVideo();
	afx_msg void OnBnClickedButtonptzPanel();

	afx_msg void OnBnClickedButtonsubtitles();
	afx_msg void OnBnClickedButtonlayouttype();
};

#endif


