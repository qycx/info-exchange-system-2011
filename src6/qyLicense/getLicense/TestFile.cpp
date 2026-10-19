// TestFile.cpp: implementation of the CTestFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "kk.h"
#include "TestFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestFile::CTestFile()
{

}

CTestFile::~CTestFile()
{
}

void  CTestFile::Close( )
{
	CFile::Close(  );
}