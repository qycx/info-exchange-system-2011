#if !defined(AFX_DLGQNMPCASSETLISTSEARCH_H__A8F3AA33_B5FC_4380_B0E2_343FC64A8F89__INCLUDED_)
#define AFX_DLGQNMPCASSETLISTSEARCH_H__A8F3AA33_B5FC_4380_B0E2_343FC64A8F89__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgQnmPcAssetListSearch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgQnmPcAssetListSearch dialog

class CDlgQnmPcAssetListSearch : public CDialog
{
// Construction
public:
	CDlgQnmPcAssetListSearch(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgQnmPcAssetListSearch)
	enum { IDD = IDD_qnmPcAssetListSearch };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	struct							{
			MY_DB_BUF			*	pDbBufs;

			TCHAR					col2[255  +  1],  col3[255  +  1],  col4[255  +  1];
			char					pcName[64  +  1];
			char					ip[CONST_qyMaxIpLen  +  1];
			unsigned  int			uiAssetType;
			TCHAR					assetName[64  +  1],  assetDes0[64  +  1];
			unsigned  char			ucbOnlyLast;
				
			TCHAR					wherePart[CONST_maxSqlBufLen  +  1];
	}								m_var;

	BOOL  bSetDlgInfo(  MY_DB_BUF  *  pDbBufs  )  {  m_var.pDbBufs  =  pDbBufs;  return  TRUE;  };
	int getWherePart(  int  iDbType  );


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgQnmPcAssetListSearch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgQnmPcAssetListSearch)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGQNMPCASSETLISTSEARCH_H__A8F3AA33_B5FC_4380_B0E2_343FC64A8F89__INCLUDED_)
