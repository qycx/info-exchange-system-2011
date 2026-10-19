#if !defined(AFX_DLGFILTERS_H__9B3D6169_0E68_4B88_97D6_A6EA5A0FBC0D__INCLUDED_)
#define AFX_DLGFILTERS_H__9B3D6169_0E68_4B88_97D6_A6EA5A0FBC0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFilters.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFilters dialog

class CDlgFilters : public CDialog
{
// Construction
public:
	CDlgFilters(CWnd* pParent = NULL);   // standard constructor

	struct				{
		int				type;
		HWND			hParent;
		unsigned  long	ulClientIp0;
		unsigned  long	ulClientIp1;
		TCHAR			filter0Buf[255  +  1];
		TCHAR			filter1Buf[255  +  1];
		TCHAR			contentFilter2Buf[255  +  1];
		TCHAR			contentFilter3Buf[255  +  1];

	}					m_var;

	BOOL  bSetDlgInfo(  int  type,  HWND  hParent,  unsigned  int  ulIp0,  unsigned  long  ulIp1,  LPCTSTR  filter0,  LPCTSTR  filter1,  LPCTSTR  contentFilter2,  LPCTSTR  contentFilter3  );


// Dialog Data
	//{{AFX_DATA(CDlgFilters)
	enum { IDD = IDD_filters };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFilters)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFilters)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFILTERS_H__9B3D6169_0E68_4B88_97D6_A6EA5A0FBC0D__INCLUDED_)
