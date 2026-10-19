
// qyMcDoc.h : interface of the CQyMcDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_QYMCDOC_H__D9E16AD7_EDF3_4B08_A9E8_616FC9CC6F57__INCLUDED_)
#define AFX_QYMCDOC_H__D9E16AD7_EDF3_4B08_A9E8_616FC9CC6F57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "qyMcMainCommon.h"


#if  0
typedef  struct  __qyMcDocStruct_t				{

				 int							iDocType;
	
				 TCHAR							dsnName[64  +  1];					//  2006/12/31

				 TCHAR							preDocName[CONST_qyMaxPreDocNameLen + 1];
				 TCHAR							docName[CONST_qyMaxDocNameLen  +  1];
				 TCHAR							postDocName[CONST_qyMaxPostDocNameLen + 1];

				 CQyMcObj					*	m_pMcObj;

				 union							{
					 QY_MC_QUERY				query;
					 struct						{
						 QY_MCROOTTREE_SEL		tree;
						 QY_MCROOTLIST_SEL		list;
					 }							treeList;	//  树列表结构
					 QY_MCVIEW_SEL				mcView;
				 }								u;
				 
				 BAR_CFG					*	pBarCfg;				 

}		 QY_MC_DOCSTRUCT;
#endif


class CQyMcDoc : public CDocument
{
protected: // create from serialization only
	CQyMcDoc();
	DECLARE_DYNCREATE(CQyMcDoc)

// Attributes
public:

	QY_MC_DOCSTRUCT			m_docStruct;
	CQyRcdset				m_rs;					 
	
// Operations

	
public:
	BOOL					bSetQyMcDoc(  QY_MC_DOCINFO  *  p  );
	BOOL					bSetQyMcDoc(  QY_MC_SEL  *  pSel  );
	BOOL					bDocAvail(  );
	BAR_CFG			*		getBarCfg(  QY_MC_DOCINFO  *  pDocInfo  );
	BOOL					bRefreshData(   BOOL bRequeryOk  = TRUE );
	BOOL					bSortData(  LPCTSTR  sortStr  );
	void					qySetTitle(  LPCTSTR  docName );
	
	int						getQueryCnt(  QY_MC_QUERY  *  pQuery  );

	QY_MC_SITE		*		getMcSite(  );
	QY_MC_WEB		*		getMcWeb(  );
	QY_MC_QUERY		*		getMcQuery(  );	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQyMcDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CQyMcDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CQyMcDoc)
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QYMCDOC_H__D9E16AD7_EDF3_4B08_A9E8_616FC9CC6F57__INCLUDED_)
