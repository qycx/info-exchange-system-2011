// QnmDb.h: interface for the CQnmDb class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QNMDB_H__BD4DA457_3231_43FB_B368_298FC6649CA0__INCLUDED_)
#define AFX_QNMDB_H__BD4DA457_3231_43FB_B368_298FC6649CA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000









typedef  struct  __qnmDbMem_t		{
				 void  *			pDb;
				 unsigned  char		ucbUsed;
				 //  int			iStatus;
				 unsigned  int		uiThreadId;
				 int				iDsnIndex;		//  2006/12/22
				 int				iDbType;		//  2012/07/14
}		 QNM_DB_MEM;


class CQnmDb  
{

#define		CONST_qnmMaxDbs				32	//  128
#define		CONST_mutexName_qnmDb		"qnmDbMutex"

private:
	static  unsigned  char		m_ucbInited;
	static  QNM_DB_MEM			m_dbMems[CONST_qnmMaxDbs];

public:
	static  int					initDbPool(  );
	static  int					makeDbPool(  LPCWSTR  connectStr,  unsigned  int  cnt,  int  iDsnIndex  );
	static  int					makeDbPool_myDb(  void  *  pDb,  unsigned  int  cnt,  int  iDsnIndex  );
	static  void				freeDbPool(  int  iDsnIndex  );
	static  void				exitDbPool(  );

private:
	static	QNM_DB_MEM		*	m_g_dbMems;
	static  int					m_g_iCnt_dbMems;

public:

	static  QNM_DB_MEM  *  getDbPool(  int  *  piCnt    );
	static  int  useDbPool(  QNM_DB_MEM  *  g_dbMems,  int  iCnt  );

public:
	CQnmDb();
	virtual ~CQnmDb();

	QNM_DB_MEM	*	m_pDbMem;
	
	void  *		getAvailableDb(  int  iDsnIndex  );
	void		showQnmDbInfo(  );

};

#endif // !defined(AFX_QNMDB_H__BD4DA457_3231_43FB_B368_298FC6649CA0__INCLUDED_)

