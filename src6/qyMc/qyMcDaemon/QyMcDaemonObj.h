// QyMcDaemonObj.h: interface for the CQyMcDaemonObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QYMCDAEMONOBJ_H__BC18B8F1_25DC_47F6_B8AD_29E33A054BA3__INCLUDED_)
#define AFX_QYMCDAEMONOBJ_H__BC18B8F1_25DC_47F6_B8AD_29E33A054BA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CQyMcDaemon : public CQyGenericDaemon  
{	
public:
	CQyMcDaemon();
	virtual ~CQyMcDaemon();

public:
	virtual  int	init(  );
	virtual  void	exit(  );

private:
	virtual  int	getInitialCfg(  );
	BOOL			bChkBeforeRunning(  );
	virtual  int	refreshCfg(  );

public:							
	#ifdef  __DEBUG__
			int				myTest(  );		//  ²âÊÔÓÃµÄº¯Êý
	#endif

public:
	QY_MCDAEMON		var;
	
};

#endif // !defined(AFX_QYMCDAEMONOBJ_H__BC18B8F1_25DC_47F6_B8AD_29E33A054BA3__INCLUDED_)

