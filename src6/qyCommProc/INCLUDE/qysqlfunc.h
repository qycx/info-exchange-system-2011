

#ifndef __QYSQLFUNC_H__
#define __QYSQLFUNC_H__	/* { */

#ifdef __cplusplus
extern "C" {
#endif

__declspec(  dllexport  )  DWORD  get_CONST_qyDbOpenOptions(  );
__declspec(  dllexport  )  BOOL  bQyOpenDb(  LPCWSTR  connectStr,  void  *  pDbParam  );
__declspec(  dllexport  )  void  qyCloseDb(  void  *  pDbParam  );
__declspec(  dllexport  )  void  *  qyNewDb(  );
__declspec(  dllexport  )  void  qyFreeDb(  void  **  ppDbParam  );
__declspec(  dllexport  )  BOOL bQyExecSql(  void  *  pDb,  LPCTSTR   sqlStr  );

#ifndef  __NOTSUPPORT_DB__
	//  BOOL bQyGetRcdBySql(  void  *  pDb,  LPCTSTR   sqlBuf,  int  cnt,  CDBVariant  *  varVal  );
#endif

BOOL  bQyGetRcdBySql(  void  *  pDb,  LPCTSTR   sqlBuf,  int  cnt,  void  *  pVarValsParam  );


#ifdef __cplusplus
}
#endif

#define		CONST_dbType_null						0
#define		CONST_dbType_access						1
#define		CONST_dbType_sqlServer					2
#define		CONST_dbType_oracle						3
//
#define		CONST_dbType_myDb						50			//  2012/07/12

//
#define		CONST_dbTypeName_myDb					"myDb"		//  2013/02/20
#define		CONST_dbTypeName_oracle					"Oracle"
#define		CONST_dbTypeName_sqlServer				"Sql Server"
#define		CONST_dbTypeName_access					"Access"

#define		CONST_qnmDbUid_access					"admin"
#define		CONST_qnmDbPwd_access					"lxdkgj!2004"

#define		CONST_qnmDbUid_oracle					"scott"
#define		CONST_qnmDbPwd_oracle					"tiger"


extern  QY_DMITEM  CONST_dbTypeTable[];

#define		CONST_ucbDsnless_true							(  unsigned  char  )TRUE
//	extern  QY_DMITEM  CONST_ucbDsnlessTable[];



 CQyString  getDbValStr(  int  iDbType,  int  iDataType,  LPCTSTR  val  );


#endif /* } */


