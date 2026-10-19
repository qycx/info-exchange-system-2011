
#include	"stdafx.h"

#ifndef  __WINCE__
	#include	<vfw.h>
#else
	#ifdef  __TEST__
			#include	<vfw.h>
	#endif
	#include	<mmreg.h>
	#include	<MSAcm.h>
#endif

#include	<Wincrypt.h>

#include	"qmCommon.h"
#include	"qmCrypt.h"


 BOOL  bGetExportedKey(  HCRYPTKEY hKey, DWORD dwBlobType,  LPBYTE *ppbKeyBlob, LPDWORD pdwBlobLen  )
{
    DWORD dwBlobLength;
    *ppbKeyBlob = NULL;
    *pdwBlobLen = 0;

    // Export the public key. Here the public key is exported to a 
    // PUBLICKEYBLOB. This BLOB can be written to a file and
    // sent to another user.

    if(CryptExportKey(   
        hKey,    
        NULL,    
        dwBlobType,
        0,    
        NULL, 
        &dwBlobLength)) 
    {
        printf("Size of the BLOB for the public key determined. \n");
    }
    else
    {
        printf("Error computing BLOB length.\n");
        return FALSE;
    }

    // Allocate memory for the pbKeyBlob.
    if(*ppbKeyBlob = (LPBYTE)malloc(dwBlobLength)) 
    {
        printf("Memory has been allocated for the BLOB. \n");
    }
    else
    {
        printf("Out of memory. \n");
        return FALSE;
    }

    // Do the actual exporting into the key BLOB.
    if(CryptExportKey(   
        hKey, 
        NULL,    
        dwBlobType,    
        0,    
        *ppbKeyBlob,    
        &dwBlobLength))
    {
        printf("Contents have been written to the BLOB. \n");
        *pdwBlobLen = dwBlobLength;
    }
    else
    {
        printf("Error exporting key.\n");
        free(*ppbKeyBlob);
        *ppbKeyBlob = NULL;

        return FALSE;
    }

    return TRUE;
}


 int  encryptData(  ENC_CTX_session  *  pEncCtx,  QY_BUF  *  pBuf_help,  char  *  data,  unsigned  int  *  puiDataLen,  unsigned  int  uiBufLen  )
{
	int				iErr				=	-1;
	unsigned  int	uiDataLen			=	0;	
	//  int				nIn;
	//  int				nOut;
	//  int				bufLen				=	0;
	//  int				len;
	//  DWORD			dwBlockLen			=	0;
	CQySyncObj			syncObj;

	if  (  !pEncCtx  ||  !pBuf_help  ||  !data  ||  !puiDataLen  )  return  -1;
	uiDataLen  =  *puiDataLen;

	if  (  !pEncCtx->common.type  
		||  !uiDataLen
			||  !pEncCtx->key_session.hKey  )  
	{					//  没有加密，所以不需要解密
		iErr  =  0;  goto  errLabel;
	}

	if  (  pEncCtx->mutexName_syncCrypt  &&  pEncCtx->mutexName_syncCrypt[0]  )  {
        if  (  syncObj.sync(  pEncCtx->mutexName_syncCrypt  )  )  goto  errLabel;
	}

	/*
	// Determine the number of bytes to encrypt at a time. 
	// This must be a multiple of ENCRYPT_BLOCK_SIZE.
	// ENCRYPT_BLOCK_SIZE is set by a #define statement.

	dwBlockLen = 1000 - 1000 % ENCRYPT_BLOCK_SIZE; 

	//-------------------------------------------------------------------
	// Determine the block size. If a block cipher is used, 
	// it must have room for an extra block. 

	if(ENCRYPT_BLOCK_SIZE > 1) 
		dwBufferLen = dwBlockLen + ENCRYPT_BLOCK_SIZE; 
	else 
	    dwBufferLen = dwBlockLen; 
	*/

	if  (  !pEncCtx->key_session.dwBlockLen_encrypt  )  {	//  流式加密的情况

		/*
		dwBlockLen  =  1000;  

		for  (  nIn  =  0,  nOut  =  0;  nIn  <  (  int  )uiDataLen  &&  nOut  <=  (  int  )uiBufLen;  )  {
			 len  =  min(  uiDataLen  -  nIn,  dwBlockLen  );
			 bufLen  =  len;
	
			 if  (  !CryptEncrypt(  pEncCtx->key_session.hKey,  0,  (  len  >=  (  int  )uiDataLen  -  nIn  ),  0,  (  BYTE  *  )data  +  nIn,  (  DWORD  *  )&bufLen,  uiBufLen  -  nOut  )  )  goto  errLabel;
			 if  (  bufLen  !=  len  )  {
				 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  "",  _T(  "IsClient"  ),  _T(  ""  ),  _T(  ""  ),  _T(  "encryptData err. "  ),  _T(  "流式加密：输出数据和输入长度不同"  )  );
				 goto  errLabel;				 
			 }

			 nIn  +=  len;
			 nOut  +=  bufLen;
		}

		uiDataLen  =  nOut;
		*/
		
		try  {
			 if  (  !CryptEncrypt(  pEncCtx->key_session.hKey,  0,  TRUE,  0,  (  BYTE  *  )data,  (  DWORD  *  )&uiDataLen,  uiBufLen  )  )  {
				 traceLogA(  "encryptData: CryptEncrypt failed."  );
				 goto  errLabel;
			 }
			 }
#ifndef  __noMfc__
		catch  (  CException  *  e  )  {
			   e->Delete(  );
			   traceLogA(  "encryptData: CryptEncrypt failed. exception caught."  );
			   goto  errLabel;
		}
#endif
		catch  (  ...  )  {
			   traceLogA(  "encryptData: CryptEncrypt failed. exception caught."  );
			   goto  errLabel;
		}

		iErr  =  0;  goto  errLabel;
	}

	//  块式加密的情况
	traceLogA(  "encryptData: 暂时使用流式加密, 这里不应该有. 未完成"  );  goto  errLabel;

	iErr  =  0;
errLabel:
	if  (  !iErr  )  {
		*puiDataLen  =  uiDataLen;
	}
	return  iErr;
}

int  decryptData(  ENC_CTX_session  *  pEncCtx,  QY_BUF  *  pBuf_help,  char  *  data,  unsigned  int  *  puiDataLen  )
{
	int				iErr				=	-1;
	unsigned  int	uiDataLen			=	0;
	//  int				nIn					=	0;
	//  int				nOut				=	0;
	//  int				len					=	0;
	//  int				tmpLen				=	0;
	//  DWORD			dwBlockLen			=	0;

	CQySyncObj			syncObj;
	
	if  (  !pEncCtx  ||  !pBuf_help  ||  !data  ||  !puiDataLen  )  return  -1;
	uiDataLen  =  *puiDataLen;

	if  (  !pEncCtx->common.type  
		||  !uiDataLen  
			||  !pEncCtx->key_session.hKey  )  
	{
		iErr  =  0;  goto  errLabel;
	}

	if  (  pEncCtx->mutexName_syncCrypt  &&  pEncCtx->mutexName_syncCrypt[0]  )  {
        if  (  syncObj.sync(  pEncCtx->mutexName_syncCrypt  )  )  goto  errLabel;
	}

	if  (  !pEncCtx->key_session.dwBlockLen_decrypt  )  {	

		/*
		dwBlockLen  =  1000;  

		for  (  nIn  =  0, nOut  =  0;  nIn  <  (  int  )uiDataLen  &&  nOut  <=  (  int  )uiDataLen;  )  {
			 len  =  min(  (  int  )dwBlockLen,  uiDataLen  -  nIn  );	
			 tmpLen  =  len;
			 
			 if  (  !CryptDecrypt(  pEncCtx->key_session.hKey,  0,  (  len  >=  (  int  )(  uiDataLen  -  nIn  )  ),  0,  (  BYTE  *  )data  +  nOut,  (  DWORD  *  )&tmpLen  )  )  goto  errLabel;
			 if  (  tmpLen  !=  len  )  {
				 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  "",  _T(  "IsClient"  ),  _T(  ""  ),  _T(  ""  ),  _T(  "decryptData err. "  ),  _T(  "流式解密：输出数据和输入长度不同"  )  );
				 goto  errLabel;				 
			 }

			 nIn  +=  len;
			 nOut  +=  tmpLen;
		}

		uiDataLen  =  nOut;
		*/

		try  {
			 if  (  !CryptDecrypt(  pEncCtx->key_session.hKey,  0,  TRUE,  0,  (  BYTE  *  )data,  (  DWORD  *  )&uiDataLen  )  )  {
				 traceLogA(  "decryptData: CryptDecrypt failed."  );
				 goto  errLabel;
			 }
			 }
#ifndef  __noMfc__
		catch  (  CException  *  e  )  {
			   e->Delete(  );
			   traceLogA(  "decryptData: CryptDecrypt failed. exception caught."  );
			   goto  errLabel;
		}
#endif
		catch  (  ...  )  {
			   traceLogA(  "decryptData: CryptDecrypt failed. exception caught."  );
			   goto  errLabel;
		}


		iErr  =  0;  goto  errLabel;
	}
	
	//  块式解密
	traceLogA(  "decryptData: 暂时使用流式解密，这里不应该有。未完成"  );  goto  errLabel;

	iErr  =  0;

errLabel:
	if  (  !iErr  )  {
		*puiDataLen  =  uiDataLen;
	}
	return  iErr;

}

