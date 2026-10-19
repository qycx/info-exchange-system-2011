
#include	"stdafx.h"

#include	"qyMcMainCommon.h"





 // 连接csp, import服务器公钥, 生成session key, export 到blob
  int  initCrypt_qmc(  MC_VAR_isCli  *  pVar,   MIS_CNT  *  pMisCnt,  LPCTSTR  szContainer,  LPCTSTR  szProvider,  BOOL  bNewKeySetIfNotExists,  ENC_CTX_session  *  pEncCtx  )
{
	int				iErr						=		-1;
	HCRYPTPROV		hCryptProv					=		NULL;	       // handle for a cryptographic
	BOOL			bAcquired					=		FALSE;

	HCRYPTKEY		hPublicKey					=		NULL;
	DWORD			dwBlockLen_rsa_encrypt		=		0;
	
	HCRYPTKEY		hKey_session				=		NULL;
	DWORD			dwBlockLen_session_encrypt	=		0;
	DWORD			dwBlockLen_session_decrypt	=		0;
	DWORD			dwBlobLen					=		0;

	int				len							=		0;
	DWORD			dwBlockLen					=		0;

	if  (  !pEncCtx->common.type  )  return  0;

	if  (  !CryptAcquireContext(  &hCryptProv,  szContainer,  szProvider,  PROV_RSA_FULL,  0  )  )  {	  
		  //-------------------------------------------------------------------
		  // An error occurred in acquiring the context. This could mean
		  // that the key container requested does not exist. In this case,
		  // the function can be called again to attempt to create a new key 
		  // container. Error codes are defined in Winerror.h.
		  if  (  GetLastError()  !=  NTE_BAD_KEYSET  )  {
			  traceLogA(  "A cryptographic service handle could not be acquired.\n"  );		
			  goto  errLabel;	  
		  }       

		  if  (  !bNewKeySetIfNotExists  )  goto  errLabel;		//  只有talking通道可以

		  {
			  CQySyncObj	syncObj;
			  if  (  syncObj.sync(  CONST_mutexName_syncKey_qmc  )  )  goto  errLabel;			//  这里的同步是因为CRYPT_NEWKEYSET 不是thread safe

			  if  (  !CryptAcquireContext(  &hCryptProv,  szContainer, szProvider, PROV_RSA_FULL, CRYPT_NEWKEYSET  )  )  {
				  traceLogA(  "Could not create a new key container.\n"  );
				  goto  errLabel;                    
			  }
		  }
	} 

	bAcquired  =  TRUE;

	//-------------------------------------------------------------------
	// A cryptographic context and a key container are available. Perform
	// any functions that require a cryptographic provider handle.

	if  (  !CryptImportKey(  hCryptProv,  (  const  BYTE  *  )pMisCnt->commEncCtx.publicKeyBlob,  pMisCnt->commEncCtx.uiBlobLen_publicKey,  0,  0,  &hPublicKey ) )  {
		traceLogA(  "Error 0x%08x in importing the Des key \n", GetLastError()  );  goto  errLabel;   
	}

	//  取blockLen
	len  =  sizeof(  dwBlockLen  );
	if  (  !CryptGetKeyParam(  hPublicKey,  KP_KEYLEN,  (  BYTE  *  )&dwBlockLen,  (  DWORD  *  )&len,  0  )  )  goto  errLabel;
	dwBlockLen  /=  8;
	if  (  dwBlockLen  <=  11  )  goto  errLabel;
	dwBlockLen  -=  11;

	dwBlockLen_rsa_encrypt  =  dwBlockLen;

	//  生成session key
	{
		CQySyncObj	syncObj;
		if  (  syncObj.sync(  CONST_mutexName_syncKey_qmc  )  )  goto  errLabel;		//  这里的同步是因为CryptGenKey 不是thread safe

		// Generate a session key.
		if  (  !CryptGenKey(  hCryptProv,  CALG_RC4,  CRYPT_EXPORTABLE,  &hKey_session  )  )  {   
			traceLogA("ERROR -- CryptGenKey.");  goto  errLabel;
		}
	}

	//  取blockLen
	len  =  sizeof(  dwBlockLen  );
	if  (  !CryptGetKeyParam(  hKey_session,  KP_BLOCKLEN,  (  BYTE  *  )&dwBlockLen,  (  DWORD  *  )&len,  0  )  )  goto  errLabel;
	dwBlockLen  /=  8;

	dwBlockLen_session_encrypt  =  dwBlockLen;
	dwBlockLen_session_decrypt  =  dwBlockLen;

	// Determine the size of the key BLOB and allocate memory.
	if  (  !CryptExportKey(  hKey_session,  hPublicKey, SIMPLEBLOB, 0, NULL, &dwBlobLen  )  ) {
		traceLogA(  "Error computing BLOB length."  );  goto  errLabel;
	}
	if  (  dwBlobLen  >  mycountof(  pEncCtx->sessionKeyBlob  )  )  goto  errLabel;

	// Export the key into a simple key BLOB.
	pEncCtx->uiBlobLen_sessionKey  =  dwBlobLen;
	if  (  !CryptExportKey(  hKey_session,  hPublicKey, SIMPLEBLOB, 0, (  BYTE  *  )pEncCtx->sessionKeyBlob, (  DWORD  *  )&pEncCtx->uiBlobLen_sessionKey  )  )  {
		qyDisplayLastError(  "Error during CryptExportKey."  );  goto  errLabel;
	}

	//--------------------------------------------------------------------

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  hKey_session  )  {
			if  (  !(  CryptDestroyKey(  hKey_session  )  )  )  traceLogA(  (  "Error  during CryptDestroyKey ."  )  );
		}

		//  Destroy the exchange key
		if  (  hPublicKey  )  {
			if  (  !(  CryptDestroyKey(  hPublicKey  )  )  )  traceLogA(  (  "Error  during CryptDestroyKey ."  )  );
		}

		if  (  bAcquired  )  {
			if  (  !CryptReleaseContext(  hCryptProv,  0  )  )  traceLogA("The handle could not be released.\n");
		}
	}

	if  (  !iErr  )  {
		pEncCtx->key_session.hKey  =  hKey_session;
		pEncCtx->key_session.dwBlockLen_encrypt  =  dwBlockLen_session_encrypt;
		pEncCtx->key_session.dwBlockLen_decrypt  =  dwBlockLen_session_decrypt;

		pEncCtx->key_rsa.hKey  =  hPublicKey;
		pEncCtx->key_rsa.dwBlockLen_encrypt  =  dwBlockLen_rsa_encrypt;
		
		pEncCtx->hCryptProv  =  hCryptProv;
	}

	traceLogA(  "initCrypt_qmc %s",  iErr  ?  "failed."  :  "ok"  );

	return  iErr;
}


 void  exitCrypt_qmc(  MC_VAR_isCli  *  pVar,  MIS_CNT  *  pMisCnt,  ENC_CTX_session  *  pEncCtx  )
{
	if  (  !pEncCtx->common.type  )  return;

	if  (  pEncCtx->key_session.hKey  )  {
		if  (  !(  CryptDestroyKey(  pEncCtx->key_session.hKey  )  )  )  traceLogA(  (  "Error  during CryptDestroyKey ."  )  );
	}
	//  Destroy the exchange key
	if  (  pEncCtx->key_rsa.hKey  )  {
		if  (  !(  CryptDestroyKey(  pEncCtx->key_rsa.hKey  )  )  )  traceLogA(  (  "Error  during CryptDestroyKey ."  )  );
	}
	if  (  pEncCtx->hCryptProv  )  {			
		if  (  !CryptReleaseContext(  pEncCtx->hCryptProv,  0  )  )  traceLogA("The handle could not be released.\n");		
	}

	traceLogA(  "exitCrypt_qmc ok"  );
	return;
}


 



