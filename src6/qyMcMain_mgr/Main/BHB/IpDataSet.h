#if !defined(AFX_IPDATASET_H__36720C4E_BA5F_4B5E_B9A1_C10C7D604703__INCLUDED_)
#define AFX_IPDATASET_H__36720C4E_BA5F_4B5E_B9A1_C10C7D604703__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IpDataSet.h : header file
//
#include <AfxDb.h>
/////////////////////////////////////////////////////////////////////////////
// CIpDataSet recordset

class CIpDataSet : public CRecordset
{
public:
	CIpDataSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CIpDataSet)

// Field/Param Data
	//{{AFX_FIELD(CIpDataSet, CRecordset)
	CString	m_interMonIp;
	CString	m_officeName;
	CString	m_subOfficeName;
	CString	m_startIp;
	CString	m_endIp;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIpDataSet)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPDATASET_H__36720C4E_BA5F_4B5E_B9A1_C10C7D604703__INCLUDED_)
