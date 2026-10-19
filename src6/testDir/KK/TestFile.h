// TestFile.h: interface for the CTestFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTFILE_H__E703D32B_E098_41A2_90A5_1A197CAC56B6__INCLUDED_)
#define AFX_TESTFILE_H__E703D32B_E098_41A2_90A5_1A197CAC56B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTestFile : public CFile  
{
public:
	CTestFile();
	virtual ~CTestFile();

	virtual void Close( );

};

#endif // !defined(AFX_TESTFILE_H__E703D32B_E098_41A2_90A5_1A197CAC56B6__INCLUDED_)
