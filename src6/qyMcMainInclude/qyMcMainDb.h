
#ifndef __QYMCMAINDB_H__
#define __QYMCMAINDB_H__	/* { */





int  initQyMcDb(  void  *  p0,  void  *  p1,  QY_OBJ_DB  *  pObj  );
void  exitQyMcDb(  void  *  p0,  void  *  p1,  QY_OBJ_DB  *  pObj  );

int  setProcedObjSth(  QY_OBJ_DB  *  pObjDb  );


BOOL  bDbConnected_netMc(  LPCWSTR  dbTypeName,  char  *  servIp,  LPCWSTR  uid,  LPCWSTR  pwd,  LPCWSTR  dbName  );
BOOL  bDbInstalled_netMc(  LPCWSTR  dbTypeName,  char  *  servIp,  LPCWSTR  uid,  LPCWSTR  pwd,  LPCWSTR  dbName  );
int  makeDb_netMc(  LPCWSTR  dbTypeName,  char  *  servIp,  LPCWSTR  uid,  LPCWSTR  pwd,  LPCWSTR  dbName,  int  iServiceId,  char  *  dbVer  );
int  makeDb_isMgr(  LPCWSTR  dbTypeName,  char  *  servIp,  LPCWSTR  uid,  LPCWSTR  pwd,  LPCWSTR  dbName,  int  iServiceId,  int  iSystemId,  int  iAppType,  char  *  dbVer  );
int  makeDb_isClient(  LPCWSTR  dbTypeName,  char  *  servIp,  LPCWSTR  uid,  LPCWSTR  pwd,  LPCWSTR  dbName,  int  iServiceId,  int  iSystemId,  int  iAppType,  char  *  dbVer  );





#endif /* } */


