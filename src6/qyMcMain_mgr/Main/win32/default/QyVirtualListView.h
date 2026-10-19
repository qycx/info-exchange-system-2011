#if !defined(AFX_QYVIRTUALLISTVIEW_H__4298162D_18F1_4163_BBCA_F7B671F6BB43__INCLUDED_)
#define AFX_QYVIRTUALLISTVIEW_H__4298162D_18F1_4163_BBCA_F7B671F6BB43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QyVirtualListView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CQyVirtualListView view

class CQyVirtualListView : public CListView
{
protected:
	CQyVirtualListView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CQyVirtualListView)

// Attributes
private:
	CImageList					m_LargeImageList;
	CImageList					m_SmallImageList;
public:

	struct  {
			int					m_nItemSelected;
			int					m_nColSelected;
			BOOL				bDesc;
			PF_qyLvConvrtProc	data2DisplayProc;
			PF_qyLvConvrtProc	display2DataProc;
	}		var;

public:
	CQyMcDoc *	GetDocument(  );
	int			getItemContent(  int  nItem,  QY_ITEMCONTENT  *  pItemContent  );
	int			getSelectedItemContent(  QY_ITEMCONTENT  *  pItemContent  );

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQyVirtualListView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CQyVirtualListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CQyVirtualListView)
	afx_msg void OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtn0();
	afx_msg void OnUpdateBtn0(CCmdUI* pCmdUI);
	afx_msg void OnBtn1();
	afx_msg void OnUpdateBtn1(CCmdUI* pCmdUI);
	afx_msg void OnBtn2();
	afx_msg void OnUpdateBtn2(CCmdUI* pCmdUI);
	afx_msg void OnBtn3();
	afx_msg void OnUpdateBtn3(CCmdUI* pCmdUI);
	afx_msg void OnBtn4();
	afx_msg void OnUpdateBtn4(CCmdUI* pCmdUI);
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtn5();
	afx_msg void OnUpdateBtn5(CCmdUI* pCmdUI);
	afx_msg void OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	afx_msg LRESULT OnQyComm(  WPARAM  wParam,  LPARAM  lParam  );
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QYVIRTUALLISTVIEW_H__4298162D_18F1_4163_BBCA_F7B671F6BB43__INCLUDED_)
