// IpDataSet.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"IpDataSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIpDataSet

IMPLEMENT_DYNAMIC(CIpDataSet, CRecordset)

CIpDataSet::CIpDataSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CIpDataSet)
	m_interMonIp = _T("");
	m_officeName = _T("");
	m_subOfficeName = _T("");
	m_startIp = _T("");
	m_endIp = _T("");
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CIpDataSet::GetDefaultConnect()
{
	QY_MC		*	pQyMc	=	QY_GET_GBUF(  );
	static  char	buf[256];

	_snprintf(  buf,  sizeof(  buf  ),  "ODBC;DSN=%s",  CONST_qyDsn_netMc  );
	//  return _T("ODBC;DSN=awmExtDsn");
	return  buf;
}

CString CIpDataSet::GetDefaultSQL()
{
	return _T("[scannedIpTab]");
}

void CIpDataSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CIpDataSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[interMonIp]"), m_interMonIp);
	RFX_Text(pFX, _T("[officeName]"), m_officeName);
	RFX_Text(pFX, _T("[subOfficeName]"), m_subOfficeName);
	RFX_Text(pFX, _T("[startIp]"), m_startIp);
	RFX_Text(pFX, _T("[endIp]"), m_endIp);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CIpDataSet diagnostics

#ifdef _DEBUG
void CIpDataSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CIpDataSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
