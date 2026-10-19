// QySnmpHelpProcDaemon.h: interface for the CQySnmpHelpProcDaemon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QYSNMPHELPPROCDAEMON_H__57B84073_AD63_4AA8_B28C_DDAB80785D9B__INCLUDED_)
#define AFX_QYSNMPHELPPROCDAEMON_H__57B84073_AD63_4AA8_B28C_DDAB80785D9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CQySnmpHelpProcDaemon : public CQyGenericDaemon  
{
public:
	QY_SNMP_HELPPROCINFO			var;

public:
	CQySnmpHelpProcDaemon();
	virtual ~CQySnmpHelpProcDaemon();


public:
	virtual  int	init(  );
	virtual  void	exit(  );
	virtual  int	getInitialCfg(  );
	virtual  int	refreshCfg(  );
	
	void	setStartToScanObjTime(  );


};

#endif // !defined(AFX_QYSNMPHELPPROCDAEMON_H__57B84073_AD63_4AA8_B28C_DDAB80785D9B__INCLUDED_)
