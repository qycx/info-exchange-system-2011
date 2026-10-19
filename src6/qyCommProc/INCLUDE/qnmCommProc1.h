

#ifndef  __QNMCOMMPROC1_H__
#define  __QNMCOMMPROC1_H__	//  {

//  2012/07/11
#define		CONST_dbConnType_null							0
#define		CONST_dbConnType_odbc							1
#define		CONST_dbConnType_ado							2

//  #define		DEFAULT_dbConnType								CONST_dbConnType_odbc


//  数据库配置参数
typedef  struct  __qnmDbCfg_t								{

				 WCHAR										sysName[64  +  1];
				 int										iSystemId;									//  系统id
				 int										iAppType;									//  应用类型

				 BOOL										bDefault;
				 //  char									dsnName[MAX_QY_DSNNAMELEN + 1];
				 int										iDbType;									//  2006/05/02
				 //
				 int										iDbConnType;								//  2012/07/12. 数据库连接方式
				 //  
				 unsigned  char								ucbDsnless;									//  2007/06/13,  采用无DSN的连接方式
				 //
				 char										dbServIp[CONST_qyMaxIpLen  +  1];
				 //  WCHAR										dbName[64  +  1];
				 WCHAR										dbName[MAX_PATH  +  1];						//  2007/06/13, 对无DNS的方式，此变量存储文件名，故空间要长一些
				 WCHAR										uid[64  +  1];
				 WCHAR										pwd[64  +  1];
				 WCHAR										connectStr[CONST_maxConnectStrLen  +  1];
				 unsigned  long								ulOpenOptions;


}		 QNM_DB_CFG;


//  2006/12/23
typedef  struct  __qyObjDb_t								{
				 int										iType;
				 //
				 QNM_DB_CFG									cfg;
				 //
				 int										iDsnIndex;									//  数据源在procedObjs中的Index，在这里也为惟一的标识数据源，也用来标识在注册表中的序号，在表示添加附加的管理单元时才用，系统本身的主数据库设置为0
				 //
				 unsigned  char								ucbUsed;									//  是否被使用
				 //
				 void					*					pDb;
				 unsigned  char								ucbLoaded;									//  看是否装载，2006/12/21

				 //
				 //  QNM_CUSRES_INFO							cusRes;										//  2007/09/22
				 //  unsigned  char								ucbResInited;

				 //
				 unsigned  char								ucbDisplayPcStatus;							//  是否显示PC状态,			2006/08/13
				 unsigned  char								ucbShowPcOpNode;							//  是否显示可操作节点，	2006/08/15
 				 unsigned  char								ucbPcAssetMgr;								//  是否管理计算机资产,		2006/06/12
				 unsigned  char								ucbPcRegistryMgr;							//  是否管理注册表,			2006/06/12

				 struct  __qyObjDb_t	*					pLogObjDb;
				 QYMC_USR				*					pUsrInfo;

}		 QY_OBJ_DB;

//
BOOL  bObjDbAvail(  QY_OBJ_DB  *  pObj  );

//
BOOL  bUseDb(  );
int  getDefaultDbType(  );
int  getDbConnType(  int  iDbType  );

//
int  parseDbParams(  LPCTSTR  connectInput,  QNM_DB_CFG  *  pDb  );
//  int  constructDbConnectStr(  LPCTSTR  tmpDbTypeName,  int  iDbConnType,  BOOL  bDsnless,  char  *  dbServIp,  LPCTSTR  dbName,  LPCTSTR  uid,  LPCTSTR  pwd,  TCHAR  *  tmpConnectStr,  unsigned  long  size  );
int  constructDbConnectStr(  int  iDbType,  int  iDbConnType,  BOOL  bDsnless,  char  *  dbServIp,  LPCTSTR  dbName,  LPCTSTR  uid,  LPCTSTR  pwd,  TCHAR  *  tmpConnectStr,  unsigned  long  size  );
//
int  getQnmDbParams(  QY_REG  *  pReg, int  iDefaultSystemId,  unsigned  char  ucbDefaultDsnless,  LPCTSTR  defaultDbName,  QNM_DB_CFG  *  pDb  );


int  qyEnumModulesProc(  void  *  modulesParam,  LPCWSTR  funcName,  void  *  p1,  void  *  p2  );

//  int  getObjIndex(  QY_OBJ_DB  *  pObjDb,  int  iObjId,  QY_OBJINDEX_RCD  *  pObjIndex  );




#endif  //  }

