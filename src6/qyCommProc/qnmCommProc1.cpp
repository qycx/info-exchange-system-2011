
#include	"stdafx.h"

//  #include	<windows.h>
//  #include	<afxdb.h>
#include	<tchar.h>

#include	"qyCommon.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qyLangCommProc.h"
#include	"qnmCommProc.h"
#include	"qnmCommProc1.h"
#include	"qnmCustom.h"
#include	"qyString.h"
#include	"qySqlFunc.h"
#include	"qyModuleFunc.h"
#include	"qyTCharCommProc.h"

/*     ±¾ÎÄ¼þ´æ·ÅÔÚËùÓÐµÄServer¶ËµÄ³ÌÐò£¬
   ²»ÓÃÔÚqwmSvrÖÐµÄÒ»Ð©º¯Êý¿É¿¼ÂÇ·ÅÔÚ´ËÎÄ¼þÖÐ
 */

 //  2013/02/
 BOOL  bUseDb(  )
 {
	BOOL		bRet	=	FALSE;
	TCHAR		tBuf[32]	=	_T(  ""  );

#ifndef  __isCli__
		 return  TRUE;
#endif

#ifndef  __X64__	//  对win32, 缺省采用db. 对x64, 因为没有access, 所以只能不用db
		 bRet  =  TRUE;
#endif
	 
	//  CONST_dbType_myDb
	tBuf[0]  =  0;
	if  (  !qyGetRegCfgT(  HKEY_CURRENT_USER,  _T(  CONST_qyRootKey_qnmScheduler_misClient  ),  _T(  CONST_regValName_bNotUseDb  ),  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
		bRet  =  !_ttol(  tBuf  );
	}
	
	return  bRet;
 }

 int  getDefaultDbType(  )
{
	int	 iDbType	=	CONST_dbType_access;

#ifdef  __isCli__
		
		#ifdef  __X64__
				iDbType  =  CONST_dbType_myDb;
		#endif
#endif

	return  iDbType;
}

 int  getDbConnType(  int  iDbType  )
{
	int		iDbConnType	=	CONST_dbConnType_odbc;

	return  iDbConnType;
}


 //  2007/06/13, ÔÚdsnlessµÄ¹¤×÷·½Ê½ÖÐ£¬dbNameÐèÒªÊÇÈ«Â·¾¶µÄÎÄ¼þÃû
 //  int  constructDbConnectStr(  LPCTSTR  tmpDbTypeName,  int  iDbConnType,  BOOL  bDsnless,  char  *  dbServIp,  LPCTSTR  dbName,  LPCTSTR  uid,  LPCTSTR  pwd,  TCHAR  *  tmpConnectStr,  unsigned  long  size  )
 int  constructDbConnectStr(  int  iDbType,  int  iDbConnType,  BOOL  bDsnless,  char  *  dbServIp,  LPCTSTR  dbName,  LPCTSTR  uid,  LPCTSTR  pwd,  TCHAR  *  tmpConnectStr,  unsigned  long  size  )
{
	int		iErr				=	-1;
	TCHAR	tDbServIpBuf[256]	=	_T(  ""  );

	myStr2TChar(  dbServIp,  tDbServIpBuf,  mycountof(  tDbServIpBuf  )  );

	//  2012/07/12
	if  (  iDbType  ==  CONST_dbType_myDb  )  return  0;

	//
	if  (  iDbConnType  ==  CONST_dbConnType_ado  )  {
 		if  (  iDbType  ==  CONST_dbType_access  )  {
			_sntprintf(  tmpConnectStr,  size,  _T(  "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;User ID=%s;Password=%s;"  ),  dbName,  _T(  CONST_qnmDbUid_access  ),  _T(  CONST_qnmDbPwd_access  )  );
			}
		else  {
			  #ifdef  __DEBUG__
					  traceLog(  _T(  "constructDbConnectStr not finished, dbType err"  )  );
			  #endif
			  goto  errLabel;
		}
		}
	else  {

 		  if  (  iDbType  ==  CONST_dbType_access  )  {
			  if  (  !bDsnless  )  _sntprintf(  tmpConnectStr,  size,  _T(  "Dsn=%s;Uid=%s;Pwd=%s;"  ),  dbName,  _T(  CONST_qnmDbUid_access  ),  _T(  CONST_qnmDbPwd_access  )  );
			  else  _sntprintf(  tmpConnectStr,  size,  _T(  "Driver={Microsoft Access Driver (*.mdb)};Dbq=%s;Uid=%s;Pwd=%s;"  ),  dbName,  _T(  CONST_qnmDbUid_access  ),  _T(  CONST_qnmDbPwd_access  )  );
			  }
		  else  if  (  iDbType  ==  CONST_dbType_oracle  )  {			      
					//  "Driver={Microsoft ODBC for Oracle};Server=qnmDb;Uid=scott;Pwd=tiger;";	
				    _sntprintf(  tmpConnectStr,  size,  _T(  "Driver={Microsoft ODBC for Oracle};Server=%s;Uid=%s;Pwd=%s;"  ),  dbName,  uid  ?  uid  :  _T(  ""  ),  pwd  ?  pwd  :  _T(  ""  )  );
					}
		  else  {	  //  "PROVIDER=MSDASQL;Dsn=testSqlDsn;Uid=;Pwd=;";
			    //  _snprintf(  tmpConnectStr,  size,  "PROVIDER=MSDASQL;Dsn=%s;Uid=;Pwd=;",  CONST_qnmDsn_sqlServer  );
			    //  _snprintf(  tmpConnectStr,  size,  "DRIVER={SQL Server};SERVER=(local);Uid=%s;Pwd=%s;DATABASE=pubs;",  uid  ?  uid  :  "",  pwd  ?  pwd  :  ""  );
			    _sntprintf(  tmpConnectStr,  size,  _T(  "DRIVER={SQL Server};Server=%s;Uid=%s;Pwd=%s;Database=%s;"  ),  tDbServIpBuf,  uid  ?  uid  :  _T(  ""  ),  pwd  ?  pwd  :  _T(  ""  ),  dbName  );
		  }
	}

	iErr  =  0;
errLabel:
	return  iErr;
}

 QY_DMITEM  CONST_dbTypeTable[]	=
{
	//  {	CONST_dbType_null,								_T(  ""  ),									},
	{	CONST_dbType_access,								_T(  CONST_dbTypeName_access  ),			},
	{	CONST_dbType_sqlServer,								_T(  CONST_dbTypeName_sqlServer  ),			},
	//  {	CONST_dbType_oracle,							_T(  CONST_dbTypeName_oracle  ),			},
	{	CONST_dbType_myDb,									_T(  CONST_dbTypeName_myDb  ),					},		//  2013/02/20
	{	-1,						},
};

/*
 QY_DMITEM  CONST_ucbDsnlessTable[]  =
{
	{	CONST_ucbDsnless_true,								_T(  "ÎÞÊý¾ÝÔ´Á¬½Ó"  ),  },
	{	FALSE,												_T(  "Êý¾ÝÔ´Á¬½Ó"  ),	},
	{	-1,				},
};
*/


 int  getCfgValFromStr(  LPCTSTR  str,  LPCTSTR  cfg,  TCHAR  *  val,  unsigned  int  size  )
{
	int				iErr		=	-1;
	TCHAR  			hint[256]	=	_T(  ""  );
	TCHAR  *		p0			=	0;
	TCHAR  *		p1			=	0;

	if  (  !str  ||  !cfg  ||  !val  ||  !size  )  return  -1;
	
	_sntprintf(  hint,  mycountof(  hint  ),  _T(  "%s="  ),  cfg  );

	val[0]  =  0;
 	if  (  !(  p0  =  (  TCHAR  *  )_tcsstr(  str,  hint  )  )  )  goto  errLabel;
	p1  =  _tcschr(  p0,  ';'  );
	//	
	p0  +=  _tcslen(  hint  );

	if  (  p1  )  lstrcpyn(  val,  p0,  min(  (  unsigned  int  )(  p1  -  p0  +  1  ),  size  )  );
	else  lstrcpyn(  val,  p0,  size  );		// ¾ÍÊÇËµÒªÊÇÄ©Î²Ã»ÓÐ;µÄ»°£¬ÄÇÃ´Ê£ÏÂµÄ×Ö·û¶¼¹éÕâ¸öÖµÁË

	iErr  =  0;  goto  errLabel;

	
errLabel:
	return  iErr;

}

 int  parseDbParams(  LPCTSTR  connectInput,  QNM_DB_CFG  *  pDb  )
{
	int					iErr								=	-1;
	int					iDbType								=	0;
	TCHAR				tmpDbTypeName[32  +  1]				=	_T(  ""  );
	int					iDbConnType							=	0;
	unsigned  char		ucbDsnless							=	CONST_ucbDsnless_true;			//  È±Ê¡²ÉÓÃÎÞDSNµÄ·½Ê½£¬2007/06/13
	char				tmpDbServIp[CONST_qyMaxIpLen  +  1]	=	"";
	TCHAR				tmpDbName[MAX_PATH  +  1]			=	_T(  ""  );
	TCHAR				tmpUid[64  +  1]					=	_T(  ""  );
	TCHAR				tmpPwd[64  +  1]					=	_T(  ""  );
	TCHAR				tmpConnectStr[256  +  1]			=	_T(  ""  );
	unsigned  long		ulOpenOptions						=	0;	
						ulOpenOptions  =  get_CONST_qyDbOpenOptions(  );
	TCHAR				tmpSysName[128]						=	_T(  ""  );
	TCHAR				tmpSystemId[128]					=	_T(  ""  );
	int					iSystemId							=	0;
	TCHAR				tBuf[1024];
	TCHAR			*	pT;

	if  (  !connectInput  ||  !pDb  )  return  -1;

	memset(  pDb,  0,  sizeof(  pDb[0]  )  );

	if  (  getCfgValFromStr(  connectInput,  _T(  CONST_qyCfgName_sysName  ),  tmpSysName,  mycountof(  tmpSysName  )  )  )  goto  errLabel;
	//
	if  (  getCfgValFromStr(  connectInput,  _T(  CONST_qyCfgName_systemId  ),  tmpSystemId,  mycountof(  tmpSystemId  )  )  )  goto errLabel;
	iSystemId  =  _tcstol(  tmpSystemId,  &pT,  10  );

	if  (  getCfgValFromStr(  connectInput,  _T(  CONST_qyCfgName_dbType  ),  tmpDbTypeName,  mycountof(  tmpDbTypeName  )  )  )  goto  errLabel;
	
	iDbType  =  qyGetTypeByDes(  CONST_dbTypeTable,  tmpDbTypeName  );		//  2006/05/03
	if  (  iDbType  <=  0  )  goto  errLabel;

	//  2012/07/12
	iDbConnType  =  getDbConnType(  iDbType  );

	//
	switch  (  iDbType  )  {
			case  CONST_dbType_access: 
				  if  (  !getCfgValFromStr(  connectInput,  _T(  "Dsn"  ),  tBuf,  mycountof(  tBuf  )  )  )  ucbDsnless  =  FALSE;
				  if  (  !ucbDsnless  )  lstrcpyn(  tmpDbName,  tBuf,  mycountof(  tmpDbName  )  );
				  //
				  if  (  !getCfgValFromStr(  connectInput,  _T(  "Dbq"  ),  tBuf,  mycountof(  tBuf  )  )  )  ucbDsnless  =  CONST_ucbDsnless_true;
				  if  (  ucbDsnless  )  lstrcpyn(  tmpDbName,  tBuf,  mycountof(  tmpDbName  )  );
				  
				  break;
			case  CONST_dbType_sqlServer:
				  if  (  getCfgValFromStr(  connectInput,  _T(  "Server"  ),  tBuf,  mycountof(  tBuf  )  )  )  goto  errLabel;
				  myTChar2Str(  tBuf,  tmpDbServIp,  mycountof(  tmpDbServIp  )  );
				  if  (  getCfgValFromStr(  connectInput,  _T(  "Database"  ),  tmpDbName,  mycountof(  tmpDbName  )  )  )  goto  errLabel;
				  break;
			default:
					goto  errLabel;
	}
	
	if  (  getCfgValFromStr(  connectInput,  _T(  "Uid"  ),  tmpUid,  mycountof(  tmpUid  )  )  )  goto  errLabel;
	if  (  getCfgValFromStr(  connectInput,  _T(  "Pwd"  ),  tmpPwd,  mycountof(  tmpPwd  )  )  )  goto  errLabel;

	if  (  _tcsicmp(  tmpDbTypeName,  _T(  CONST_dbTypeName_sqlServer  )  )
		&&  _tcsicmp(  tmpDbTypeName,  _T(  CONST_dbTypeName_oracle  )  )  )  
	{					
		//  È±Ê¡Access
		lstrcpyn(  tmpDbTypeName,  _T(  CONST_dbTypeName_access  ),  mycountof(  tmpDbTypeName  )  );

		tmpUid[0]  =  0;
		tmpPwd[0]  =  0;

	}


	if  (  constructDbConnectStr(  iDbType,  iDbConnType,  ucbDsnless,  tmpDbServIp,  tmpDbName,  tmpUid,  tmpPwd,  tmpConnectStr,  mycountof(  tmpConnectStr  )  )  )  goto  errLabel;

	iErr  =  0;

errLabel:

	if  (  !iErr  )  {
		myTChar2WChar(  tmpSysName,  pDb->sysName,  mycountof(  pDb->sysName  )  );
		pDb->iSystemId  =  iSystemId;
		pDb->iDbType  =  iDbType;
		pDb->iDbConnType  =  iDbConnType;
		pDb->ucbDsnless  =  ucbDsnless;
		safeStrnCpy(  tmpDbServIp,  pDb->dbServIp,  mycountof(  pDb->dbServIp  )  );
		myTChar2WChar(  tmpDbName,  pDb->dbName,  mycountof(  pDb->dbName  )  );
		myTChar2WChar(  tmpUid,  pDb->uid,  mycountof(  pDb->uid  )  );
		myTChar2WChar(  tmpPwd,  pDb->pwd,  mycountof(  pDb->pwd  )  );
		myTChar2WChar(  tmpConnectStr,  pDb->connectStr,  mycountof(  pDb->connectStr  )  );
		pDb->ulOpenOptions  =  ulOpenOptions;
	}

	return  iErr;

}



 int  getQnmDbParams(  QY_REG  *  pReg,  int  iDefaultSystemId,  unsigned  char  ucbDefaultDsnless,  LPCTSTR  defaultDbName,  QNM_DB_CFG  *  pDb  )
{
	int					iErr								=	-1;
	WCHAR			*	hint								=	NULL;
	WCHAR			*	p0									=	NULL;
	WCHAR			*	p1									=	NULL;
	//  BOOL				bDefault							=	FALSE;
	int					iDbType								=	0;
	WCHAR				tmpDbTypeName[32  +  1]				=	L"";
	BOOL				bDsnless							=	FALSE;
	char				tmpDbServIp[CONST_qyMaxIpLen  +  1]	=	"";
	WCHAR				tmpDbName[64  +  1]					=	L"";
	WCHAR				tmpUid[64  +  1]					=	L"";
	WCHAR				tmpPwd[64  +  1]					=	L"";
	TCHAR				tmpConnectStr[256  +  1]			=	_T(  ""  );
	unsigned  long		ulOpenOptions						=	0;
						ulOpenOptions  =  get_CONST_qyDbOpenOptions(  );
	unsigned  long		len;
	char				buf[2048];

	if  (  !pReg  ||  !defaultDbName  ||  !pDb  )  return  -1;
	
	if  (  qyGetRegCfg(  pReg->rootKey,  _T(  CONST_regValName_dbTypeName  ),  (  char  *  )tmpDbTypeName,  sizeof(  tmpDbTypeName  )  )  )  {
		tmpDbTypeName[0]  =  0;
		//  bDefault  =  TRUE;
	}
	tTrim(  tmpDbTypeName  );

	iDbType  =  qyGetTypeByDes(  CONST_dbTypeTable,  tmpDbTypeName  );		//  2006/05/03
	if  (  iDbType  <=  0  )  {
		iDbType  =  getDefaultDbType(  );
	}
	if  (  !bUseDb(  )  )  {		//  2013/02/21
		iDbType  =  CONST_dbType_myDb;
	}

	//
	len  =  sizeof(  buf  );
	if  (  qyGetRegDataEx(  pReg,  _T(  CONST_regValName_connectStr  ),  (  char  *  )buf,  &len  )  )  buf[0]  =  0;
	else  buf[len]  =  0;
	myUtf82TChar(  buf,  tmpConnectStr,  mycountof(  tmpConnectStr  )  );
	
	//
	if  (  !parseDbParams(  tmpConnectStr,  pDb  )  &&  pDb->iDbType  ==  iDbType  )  {
		iErr  =  0;  goto  errLabel;
	}

	//  ÒªÊÇÃ»ÓÐ·ÖÎö³öÀ´£¬¾ÍÒªÓÃÈ±Ê¡µÄ
	memset(  pDb,  0,  sizeof(  pDb[0]  )  );
	//
	pDb->iSystemId  =  iDefaultSystemId;
	//
	pDb->bDefault  =  TRUE;
	pDb->iDbType  =  getDefaultDbType(  );
	if  (  !bUseDb(  )  )  {	//  2013/02/21
		pDb->iDbType  =  CONST_dbType_myDb;
	}

	//
	pDb->iDbConnType  =  getDbConnType(  pDb->iDbType  );	//  2012/07/12
	//
	pDb->ucbDsnless  =  ucbDefaultDsnless;
	//
	myTChar2WChar(  defaultDbName,  pDb->dbName,  mycountof(  pDb->dbName  )  );

	pDb->ulOpenOptions  =  get_CONST_qyDbOpenOptions(  );

	tmpConnectStr[0]  =  0;
	if  (  constructDbConnectStr(  pDb->iDbType,  pDb->iDbConnType,  pDb->ucbDsnless,  pDb->dbServIp,  pDb->dbName,  pDb->uid,  pDb->pwd,  tmpConnectStr,  mycountof(  tmpConnectStr  )  )  )  goto  errLabel;
	myTChar2WChar(  tmpConnectStr,  pDb->connectStr,  mycountof(  pDb->connectStr  )  );
	
	iErr  =  0;
errLabel:

	return  iErr;

}

 BOOL  bObjDbAvail(  QY_OBJ_DB  *  pObj  )
{
	if  (  !pObj  ||  !pObj->ucbLoaded  )  return  FALSE;
	return  TRUE;
}



