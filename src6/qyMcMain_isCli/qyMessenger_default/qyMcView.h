// qyMcView.h : interface of the CQyMcView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_QYMCVIEW_H__F0BB0BC5_8790_4128_857F_CEFE6CC9C16E__INCLUDED_)
#define AFX_QYMCVIEW_H__F0BB0BC5_8790_4128_857F_CEFE6CC9C16E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "qyMcDoc.h"

/*
#define iiINSERT_AN_ITEM( str, iImageParam, content, dwItemData, lvi, index, ListCtrl ) {		\
				( lvi ).mask		=		LVIF_TEXT | LVIF_IMAGE;				\
				( lvi ).iItem		=		( index );							\
				( lvi ).iSubItem	=		0;									\
				( lvi ).pszText		=		( str );							\
				( lvi ).iImage		=		( iImageParam );					\
				( ListCtrl ).InsertItem( &( lvi ) );							\
				( ListCtrl ).SetItemData( ( index ), ( dwItemData ) );						\
				( ListCtrl ).SetItemText( ( index ), 1, content );				\
				( index ) ++;													\
				( dwItemData )		=		QY_ITEMTYPE_NULL;					\
		}


#define iiTMP_INSERT_AN_ITEM( )	INSERT_AN_ITEM( pHint, 0, pContent, dwItemData, lvi, index, ListCtrl )
// 这里：用了TMP_INSERT_AN_ITEM( ), 不能重用，并且应完整的定义同样的变量。
// 注意：pContent指向buf, 故对buf的操作也意味着对pContent的操作。

*/ 

class CQyMcView : public CListView
{
protected: // create from serialization only
	CQyMcView();
	DECLARE_DYNCREATE(CQyMcView)

// Attributes
public:
	CQyMcDoc* GetDocument();

public:
	
private:
	CImageList					m_LargeImageList;
	CImageList					m_SmallImageList;
public:
	struct {
		int						m_nCols;
		HWND					m_hMgrWnd;
		QY_MC_DISPLAYCFG		m_displayCfg;
		QY_MC_SEL				m_superSel;
		int						m_nItemSelected;
	}						    var;
	
// Operations
public:
	virtual  BOOL	bInitialDisplay(  );
	
	virtual  void	preInitialDisplay(  );
	virtual  BOOL	bGetDisplayCfg(  QY_MC_DISPLAYCFG *  );
	virtual  void	delAllColumns(  );
	virtual	 BOOL	bAddColumns(  QY_COLUMNINFO *	pColumns  );
	virtual  BOOL	bDisplayContent(  QY_MC_DISPLAYCFG  *  pCfg  );
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQyMcView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CQyMcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CQyMcView)
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtn0();
	afx_msg void OnBtn1();
	afx_msg void OnBtn2();
	//}}AFX_MSG
	afx_msg LRESULT OnQyComm( WPARAM, LPARAM );
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in qyMcView.cpp
inline CQyMcDoc* CQyMcView::GetDocument()
   { return (CQyMcDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QYMCVIEW_H__F0BB0BC5_8790_4128_857F_CEFE6CC9C16E__INCLUDED_)
