

#include	"stdafx.h"

#include	<afxdb.h>
#include	<windowsx.h>
#include	"qyCommon.h"
#include	"qyGuiCommon.h"
#include	"qyString.h"
#include	"qySqlFunc.h"


 __declspec(  dllexport  )  extern  "C"  DWORD  get_CONST_qyDbOpenOptions(  )
{
	return  CONST_qyDbOpenOptions;
}


 __declspec(  dllexport  )  extern  "C"  BOOL  bQyOpenDb(  LPCWSTR  connectStr,  void  *  pDbParam  ) 
{
	 BOOL			bRet  =  FALSE;
	 CDatabase  *	pDb  =  (  CDatabase  *  )pDbParam;

	 if  (  !pDb  )  goto  errLabel;
			 
	 try  {			 
		  if  (  !pDb->OpenEx(  CString(  connectStr  ).GetBuffer(  0  ),  CONST_qyDbOpenOptions  )  )  {
		 	  traceLogA(  "db.Open( %s ) failed.",  connectStr  );
			  goto  errLabel;
		  }		
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   //	qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bQyOpenDb failed."  )  );
		   goto  errLabel;
	}

	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}

 //  2004/04/15ÐÞ¸Ä
 __declspec(  dllexport  )  extern  "C"  void  qyCloseDb(  void  *  pDbParam  ) 
{
	 CDatabase  *	pDb  =  (  CDatabase  *  )pDbParam;

	 if  (  !pDb  )  return;
	 if  (  pDb->IsOpen(  )  )  pDb->Close(  );
}


__declspec(  dllexport  )  extern  "C"  void  *  qyNewDb(  )
{
	return  new  CDatabase;
}


 //  2013/06/18
 __declspec(  dllexport  )  extern  "C"  void  qyFreeDb(  void  **  ppDbParam  )
 {
	 if  (  !ppDbParam  )  return;
	 if  (  !*ppDbParam  )  return;
	 CDatabase  *  pDb  =  *(  CDatabase  **  )ppDbParam;
	 qyCloseDb(  pDb  );
	 delete  pDb;
	 *ppDbParam  =  NULL;
	 return;
 }

 //  extern  "C"  BOOL  bQyGetRcdBySql(  void  *  pDb,  LPCTSTR   sqlBuf,  int  cnt,  CDBVariant  *  varVal  )
 extern  "C"  BOOL  bQyGetRcdBySql(  void  *  pDb,  LPCTSTR   sqlBuf,  int  cnt,  void  *  pVarValsParam  )
{
	 BOOL			bRet	=	FALSE;
	 CDBVariant  *  varVal	=	(  CDBVariant  *  )pVarValsParam;
 	 CRecordset		rs( ( CDatabase * )pDb );
	 int			index = 0;

	 try  {		
		  if  (  !rs.Open(  CRecordset::forwardOnly,  sqlBuf  )  )  {
		 	  traceLogA(  "rs.Open(  ) failed."  );
			  goto  errLabel;
		  }
		  if  (  rs.GetODBCFieldCount(  )  >  cnt  )  goto  errLabel;
		  if  (  rs.IsEOF(  )  )  goto  errLabel;
		  cnt  =  rs.GetODBCFieldCount(  );
		  for  (  index  =  0;  index  <  cnt;  index  ++  )
		  	   rs.GetFieldValue(  index,  varVal[index]  );
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   //  qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bQyGetRcdBySql failed."  )  );
		   goto  errLabel;
	}

	 bRet	=	TRUE;

errLabel:

	if  (  rs.IsOpen(  )  )  rs.Close(  );
	
	return	bRet;
	
}

#if  0
 extern "C" int qyGetAFieldBySql( void *pDb, char *sqlStr, CDBVariant *pVariant )
{
	 int iErr = -1;
 	 CRecordset rs( ( CDatabase * )pDb );
	 CDBVariant varValue;
	 int index = 0;
	 int nField = 0;

	 try {		
		  if( !rs.Open( CRecordset::forwardOnly, CString(  sqlStr  ).GetBuffer(  0  )  ) ) {
		 	  debugLog( "LoadDBLog() open() failed." );
			  goto errLabel;
		  }
	  	
		  nField = rs.GetODBCFieldCount( );
		  if ( nField != 1 ) goto errLabel;
		  if ( rs.IsEOF( ) ) goto errLabel;
		  rs.GetFieldValue( index, *pVariant );
		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   //  qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "qyGetAFieldBySql failed."  )  );
		   goto  errLabel;
	}
		  		  

	 iErr = 0;

errLabel:

	if ( rs.IsOpen( ) ) rs.Close( );
	
	return iErr;		


}
#endif
 
  __declspec(  dllexport  )  extern  "C"  BOOL  bQyExecSql(  void  *  pDbParam,  LPCTSTR  sqlStr  )
{
	BOOL			bRet	=	FALSE;
	CDatabase  *	pDb		=	(  CDatabase  *  )pDbParam;
	
	try	 {
		pDb->ExecuteSQL(  sqlStr  );
		} 
	catch  (  CDBException  *  e  )  {
#ifdef  __DEBUG__
		   e->ReportError(  );
#endif
		   e->Delete(  );
#ifdef  __DEBUG__
		   //  traceLog(  _T(  "bQyExecSql failed,  sql is %s"  ),  sqlStr  );  		
		   OutputDebugString(  _T(  "bQyExecSql failed,  sql is "  )  );
		   OutputDebugString(  sqlStr  );  		
		   OutputDebugString(  _T(  "\n"  )  );
#endif
		   goto  errLabel;
	}
	
	bRet  =  TRUE;

errLabel:

	return  bRet;

}


