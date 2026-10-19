

#include	<stdio.h>
#include	<stdlib.h>
#include	<memory.h>
#include	<ctype.h>
#include	<string.h>
#include	<windows.h>
#include	"qyCommon.h"
#include	"awmExtCfg.h"


/* 
 extern  "C"  int  qyEnc(  void  *  pEncCtx,  char  *  input,  size_t  inputSize,  char  *  output,  size_t  *  pOutputSize  )
{
	 if  (  inputSize  >  *  pOutputSize  )  return  -1;
	 memmove(  output,  input,  inputSize  );
	 *pOutputSize  =  inputSize;
	 return  0;
}

 extern  "C"  int  qyDec(  void  *  pEncCtx,  char  *  input,  size_t  inputSize,  char  *  output,  size_t  *  pOutputSize  )
{
	 if  (  inputSize  >  *  pOutputSize  )  return  -1;
	 memmove(  output,  input,  inputSize  );
	 *pOutputSize  =  inputSize;
	 return  0;
}
*/

/*
 extern  "C"  int  clearInterMonWarnFlg(  void  *  pAE  )
{
	 qySetRegCfg(  ROOT_AWM_INTER_MON_KEY,  CONST_regValName_newEmergency,  "0"  );
	 return  0;
}

 extern  "C"  int  setInterMonWarnInfo(  void  *  pAE )
{
	 char	timeBuf[14  +  1];

	 if  (  getCurTime(  timeBuf  )  )  return  -1;
	 
	 qySetRegCfg(  ROOT_AWM_INTER_MON_KEY,  CONST_regValName_emergencyTime,  timeBuf  );
	 qySetRegCfg(  ROOT_AWM_INTER_MON_KEY,  CONST_regValName_newEmergency,  "1"  );
	 
	 return  0;

}


 extern  "C"  int  getInterMonWarnInfo(  void  *  pAE,  char  *  timeBuf,  int  size,  BOOL  *  pbNew  )
{
	 int	iErr  =  -1;
	 char	tmpTimeBuf[14  +  1];
	 char	bNewBuf[2];
	 
	 if  (  size  <=  14  )  return  -1;

	 if  (  qyGetRegCfg(  ROOT_AWM_INTER_MON_KEY,  CONST_regValName_emergencyTime,  tmpTimeBuf,  sizeof(  tmpTimeBuf  )  )  )  goto  errLabel;
	 if  (  strlen(  tmpTimeBuf  )  !=  14  )  goto  errLabel;
	 
	 if  (  qyGetRegCfg(  ROOT_AWM_INTER_MON_KEY,  CONST_regValName_newEmergency,  bNewBuf,  sizeof(  bNewBuf  )  )  )  goto  errLabel;
	 
	 strcpy(  timeBuf,  tmpTimeBuf  );
	 *pbNew  =  (  bNewBuf[0]  ==  '1'  );

	 iErr  =  0;

errLabel:

	 return  iErr;

}
*/


#define ASR_ERR_STR					"err"
#define ASR_STATUS_STR				"status"

 extern  "C"  int asrSetRegCfg( char *rootKey, char *cfgName, char *cfgVal )
{
	int iRet = -1;
	BOOL bKeyCreated = FALSE;
	HKEY hKey;
	int rc = -1;
	// char buf[256];
	
	// sprintf( buf, "%d", ASR_QUIT_VAL );

	if ( ( rc = RegCreateKey( HKEY_LOCAL_MACHINE, rootKey, &hKey ) ) != ERROR_SUCCESS ) {
		char buf[128];
		wsprintf( buf, "RegCreate returns %d", rc );
		debugLog( "asrSetRegCfg( ): RegCreateKey( ) failed: %s", buf );
		goto errLabel;
	}
	bKeyCreated = TRUE;
	if ( RegSetValueEx( hKey, cfgName, 0, REG_SZ, ( const unsigned char * )cfgVal, lstrlen( cfgVal ) ) != ERROR_SUCCESS ) {
		debugLog( "asrSetRegCfg( ): RegSetValueEx( ) failed." );
		goto errLabel;
	}

	iRet = 0;

errLabel:

	if ( bKeyCreated ) RegCloseKey( hKey );

	return iRet;

}

 extern  "C"  int asrShowRegErr( char *rootKey, char *errStr )
{
	return asrSetRegCfg( rootKey, ASR_ERR_STR, errStr );
}

 extern  "C"  int asrShowRegStatus( char *rootKey, char *statusStr )
{
	return asrSetRegCfg( rootKey, ASR_STATUS_STR, statusStr );
}


