// QnmDb.cpp: implementation of the CQnmDb class.
//
//////////////////////////////////////////////////////////////////////

#include	"stdafx.h"

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<tchar.h>

#ifndef  __noMfc__
		 #include	<afxmt.h>
		 #include	<afxdb.h>
#endif
#include	"qyCommon.h"


#include	"qyString.h"
#include	"qyDbCommon.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"

#include	"qyCommProc.h"
#include	"qnmCommProc.h"

#include	"QnmDb.h"
#include	"qySyncObj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//  静态成员区  {
 unsigned  char		CQnmDb::m_ucbInited	=	0;
 QNM_DB_MEM			CQnmDb::m_dbMems[CONST_qnmMaxDbs];

 //
 QNM_DB_MEM		*	CQnmDb::m_g_dbMems  =  NULL;
 int				CQnmDb::m_g_iCnt_dbMems  =  0;


 int  CQnmDb::initDbPool(  )
{
	 if  (  m_ucbInited  )  return  0;
	 
	 memset(  m_dbMems,  0,  sizeof(  m_dbMems  )  );
	 m_ucbInited  =  TRUE;
	 return  0;
}

 void  CQnmDb::exitDbPool(  )
{
	 int			i;
	 //  CDatabase	*	pDb		=	NULL;
	 void	*	pDb		=	NULL;

	 if  (  !m_ucbInited  )  return;

	 for  (  i  =  0;  i  <  sizeof(  m_dbMems  )  /  sizeof(  m_dbMems[0]  );  i  ++  )  {
		  if  (  !(  pDb  =  (  void  *  )m_dbMems[i].pDb  )  )  continue;
		  //  qyCloseDb(  pDb  );  delete  pDb;
		  qyFreeDb(  &pDb  );
	 }

	 m_ucbInited  =  FALSE;
	 return;
}


 int  CQnmDb::makeDbPool(  LPCWSTR  connectStr,  unsigned  int  cnt,  int  iDsnIndex  )
{
	 int			iErr		=		-1;
	 unsigned  int	i;
	 unsigned  int	index		=		0;
	 //  CDatabase	*	pDb			=		NULL;
	 void		*	pDb			=		NULL;

#if  0
	 CMutex			mutex(  FALSE,  CString(  CONST_mutexName_qnmDb  )  );
	 if  (  !mutex.Lock(  )  )  return  -1;
#endif
	 CQySyncObj		syncObj;
	 if  (  syncObj.sync(  _T(  CONST_mutexName_qnmDb  )  )  )  return  -1;

	 for  (  i  =  0;  i  <  cnt;  i  ++  )  {
		  
		  //  取空闲的dbMems
		  for  (  ;  index  <  sizeof(  m_dbMems  )  /  sizeof(  m_dbMems[0]  );  index  ++  )  if  (  !m_dbMems[index].pDb  )  break;
		  if  (  index  ==  sizeof(  m_dbMems  )  /  sizeof(  m_dbMems[0]  )  )  {
			  traceLogA(  "dbPool已满，makeDbPool失败"  );  goto  errLabel;
		  }

		  //  pDb  =  new  CDatabase;
		  pDb  =  qyNewDb(  );
		  if  (  !pDb  )  goto  errLabel;
		  if  (  !bQyOpenDb(  connectStr,  pDb  )  )  {
			  traceLogA(  "打开数据库连接失败，makeDbPool失败"  );  goto  errLabel;
		  }

		  m_dbMems[index].pDb  =  pDb;  pDb  =  NULL;
		  m_dbMems[index].uiThreadId  =  GetCurrentThreadId(  );
		  m_dbMems[index].iDsnIndex  =  iDsnIndex;					//  2006/12/22
		  m_dbMems[index].iDbType  =  0;							//  暂时不赋值

	 }

	 iErr  =  0;

errLabel:

#if  0
	 mutex.Unlock(  );  
#endif

	 if  (  pDb  )  {
		 //  qyCloseDb(  pDb  );  delete  pDb;
		 qyFreeDb(  &pDb  );
	 }

	 return  iErr;

}


  int  CQnmDb::makeDbPool_myDb(  void  *  pDb,  unsigned  int  cnt,  int  iDsnIndex  )
{
	 int			iErr		=		-1;
	 unsigned  int	i;
	 unsigned  int	index		=		0;


#if  0
	 CMutex			mutex(  FALSE,  CString(  CONST_mutexName_qnmDb  )  );	 
	 if  (  !mutex.Lock(  )  )  return  -1;
#endif
	 CQySyncObj	syncObj;
	 if  (  syncObj.sync(  _T(  CONST_mutexName_qnmDb  )  )  )  return  -1;

	 for  (  i  =  0;  i  <  cnt;  i  ++  )  {
		  
		  //  取空闲的dbMems
		  for  (  ;  index  <  sizeof(  m_dbMems  )  /  sizeof(  m_dbMems[0]  );  index  ++  )  if  (  !m_dbMems[index].pDb  )  break;
		  if  (  index  ==  sizeof(  m_dbMems  )  /  sizeof(  m_dbMems[0]  )  )  {
			  traceLogA(  "dbPool已满，makeDbPool失败"  );  goto  errLabel;
		  }

		  m_dbMems[index].pDb  =  pDb;  
		  m_dbMems[index].uiThreadId  =  GetCurrentThreadId(  );
		  m_dbMems[index].iDsnIndex  =  iDsnIndex;					//  2006/12/22
		  m_dbMems[index].iDbType  =  CONST_dbType_myDb;

	 }

	 iErr  =  0;

errLabel:

#if  0
	 mutex.Unlock(  );  
#endif


	 return  iErr;

}


 void  CQnmDb::freeDbPool(  int  iDsnIndex  )	//  2006/12/22, 这个函数用来卸载某个数据源时用的
{
	 int			i;

	 if  (  !m_ucbInited  )  return;

	 for  (  i  =  0;  i  <  sizeof(  m_dbMems  )  /  sizeof(  m_dbMems[0]  );  i  ++  )  {
		  if  (  m_dbMems[i].iDsnIndex  !=  iDsnIndex  )  continue;
		  if  (  !m_dbMems[i].pDb  )  continue;
		  if  (  m_dbMems[i].iDbType  ==  CONST_dbType_myDb  )  {
			  //  不需要操作. 2012/07/14
			  ;  
			  }
		  else  {
			     //  CDatabase	*	pDb		=	NULL;
			     void  *  pDb  =  NULL;
				 pDb  =  (  void  *  )m_dbMems[i].pDb;
				 //  qyCloseDb(  pDb  );  delete  pDb;
				 qyFreeDb(  &pDb  );
		  }
		  memset(  &m_dbMems[i],  0,  sizeof(  m_dbMems[i]  )  );
	 }

	 return;

}


 QNM_DB_MEM  *  CQnmDb::getDbPool(  int  *  piCnt    )
{
	if  (  !m_ucbInited  )  return  NULL;

	if  (  !piCnt  )  return  NULL;
	
	*piCnt  =  mycountof(  m_dbMems  );

	return  m_dbMems;
}

int  CQnmDb::useDbPool(  QNM_DB_MEM  *  g_dbMems,  int  iCnt  )
{
	if  (  !g_dbMems  ||  iCnt  <=  0  )  return  -1;

	m_g_dbMems  =  g_dbMems;
	m_g_iCnt_dbMems  =  iCnt;
	return  0;
}


//  }



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQnmDb::CQnmDb()
{
	m_pDbMem  =  NULL;

}

CQnmDb::~CQnmDb()
{
	if  (  !m_pDbMem  )  return;
#if  0
	CMutex			mutex(  FALSE,  CString(  CONST_mutexName_qnmDb  )  );
	if  (  !mutex.Lock(  )  )  {
		traceLogA(  "最严重警告：CQnmDb::~CQnmDb(  ) 中mutex.Lock failed"  );
		return;
	}
#endif
	CQySyncObj	syncObj;
	if  (  syncObj.sync(  _T(  CONST_mutexName_qnmDb  )  )  )  {
		traceLogA(  "最严重警告：CQnmDb::~CQnmDb(  ) 中mutex.Lock failed"  );
		return;
	}

	m_pDbMem->ucbUsed  =  FALSE;

#if  0
	mutex.Unlock(  );
#endif
}

	
 void  *  CQnmDb::getAvailableDb(  int  iDsnIndex  )
{
	 int			index	=	-1;

	 if  (  m_pDbMem  )  return  m_pDbMem->pDb;

	 //
	 if  (  !m_g_dbMems  ||  m_g_iCnt_dbMems  <=  0  )  return  NULL;

	 //
#if  0
	 CMutex			mutex(  FALSE,  CString(  CONST_mutexName_qnmDb  )  );
	 if  (  !mutex.Lock(  )  )  return  NULL;
#endif
	 CQySyncObj	syncObj;
	 if  (  syncObj.sync(  _T(  CONST_mutexName_qnmDb  )  )  )  return  NULL;

	 for  (  index  =  0;  index  <  m_g_iCnt_dbMems;  index  ++  )  {
		  if  (  !m_g_dbMems[index].pDb  )  continue;
		  if  (  m_g_dbMems[index].iDsnIndex  !=  iDsnIndex  )  continue;
		  //  if  (  m_dbMems[index].uiThreadId  !=  GetCurrentThreadId(  )  )  continue;
		  //  traceLogA(  "2007/05/09, CDatabase应该可以支持多线程的调用，只要有同步就可以了, 这里把对threadId的考虑暂时去掉了"  );
		  if  (  !m_g_dbMems[index].ucbUsed  )  break;
	 }

	 if  (  index  <  m_g_iCnt_dbMems  )  {
		 m_pDbMem  =  &m_g_dbMems[index];  
		 m_pDbMem->ucbUsed  =  TRUE;
		 
		 #ifdef  __DEBUG__
		 		 //  qyShowInfo(  CONST_qyShowType_qnmChking,  "",  "qyMc",  "",  "",  "CQnmDb::getAvailableDb %d",  index  );
		 #endif

	 }
	
//  errLabel:

#if  0
	 mutex.Unlock(  );
#endif
	 
	 if  (  !m_pDbMem  )  {
		 traceLogA(  "CQnmDb::getAvailableDb failed, return  NULL."  );
	 }

	 return  m_pDbMem  ?  m_pDbMem->pDb  :  NULL;
}



 void  CQnmDb::showQnmDbInfo(  )
{
	 int	i	=	0;
	 //  for  (  i  =  0;  i  <  m_
}
