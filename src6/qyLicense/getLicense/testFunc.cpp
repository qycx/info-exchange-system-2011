

#include	"stdafx.h"
//  #include	"qyCommon.h"

#define  CONST_qyRcOk_smtp		"250"
 BOOL  bSmtpRcOk(  char  *  msg  )
{
	 return  !memcmp(  msg,  CONST_qyRcOk_smtp,  strlen(  CONST_qyRcOk_smtp  )  );
}



 void  testDb(  )
{
	 CDatabase  *  pDb  =  NULL;
	 char  *  dsnName  =  "testDsn";
	 CString  sqlStr;

	 TRY  {
		pDb = new CDatabase;
		if  (  !pDb  )  goto  errLabel;
		if  (  !pDb->Open(  dsnName  )  )  {
			goto errLabel;
		}

		sqlStr  =  CString( "" )  +  "create table qyOldPcTab("
									"mac0 char(12) primary key,"
									"mac1 char(12) null,"
									"mac2 char(12) null,"
									"otherMacs varchar(255) null,"
									"ip varchar(15) not null,"
									"qwmVer varchar(8),"
									"startTime char(14),"
									"lastCommTime char(14),"
									"osName varchar(64) null"
									")";
	
		pDb->ExecuteSQL(  sqlStr  );
		
		}
	CATCH  (  CDBException,  e  )  {
		AfxMessageBox(  e->m_strError  );
		goto  errLabel;
	}
	END_CATCH
	
errLabel:

	if  (  pDb  )  delete  pDb;

	return;
	 
}

