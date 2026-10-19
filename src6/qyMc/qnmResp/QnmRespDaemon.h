// QnmRespDaemon.h: interface for the CQnmRespDaemon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QNMRESPDAEMON_H__D54D6419_9565_4FAF_84FA_91BF4443232F__INCLUDED_)
#define AFX_QNMRESPDAEMON_H__D54D6419_9565_4FAF_84FA_91BF4443232F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CQnmRespDaemon : public CQyGenericDaemon  
{
public:
	CQnmRespDaemon();
	virtual ~CQnmRespDaemon();

public:
	virtual  int		init(  );
	virtual  void		exit(  );

private:
	virtual  int		getInitialCfg(  );
	BOOL				bChkBeforeRunning(  );
	virtual  int		refreshCfg(  );
	
	
public:
	QNMRESP_DAEMON		var;


};

#endif // !defined(AFX_QNMRESPDAEMON_H__D54D6419_9565_4FAF_84FA_91BF4443232F__INCLUDED_)
