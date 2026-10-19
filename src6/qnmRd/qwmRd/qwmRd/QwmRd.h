// QwmRd.h: interface for the CQwmRd class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QWMRD_H__63E91210_5FC4_49ED_B2D0_78C666D4C2D1__INCLUDED_)
#define AFX_QWMRD_H__63E91210_5FC4_49ED_B2D0_78C666D4C2D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include	"qwmHideProcessCommProc.h"		//  2006/02/13




#define		CONST_qyRet_rdConnectFailed		-2
#define		CONST_qyRet_rdEnd				-3


extern HINSTANCE	hAppInstance;
extern const char	*szAppName;
extern DWORD		mainthreadId;

extern int qwmRdMain();

#define		des(inblock, outblock)	desd3(inblock, outblock)		//  2006/10/04, 发现和qyEncLib里的这个函数是一样的


#ifdef  __cplusplus

class CQwmRd  
{
public:
	CQwmRd();
	virtual ~CQwmRd();

	static BOOL PostAddNewClient(unsigned long ipaddress);

};

#endif

#endif // !defined(AFX_QWMRD_H__63E91210_5FC4_49ED_B2D0_78C666D4C2D1__INCLUDED_)
