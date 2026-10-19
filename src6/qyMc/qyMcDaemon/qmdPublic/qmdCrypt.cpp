

#include  "stdafx.h"

#include	"qmdCommon.h"
#include	"qmCrypt.h"

//-------------------------------------------------------------------
// Declare and initialize variables.


//-------------------------------------------------------------------
// Attempt to acquire a context and a key
// container. The context will use the default CSP
// for the RSA_FULL provider type. DwFlags is set to zero
// to attempt to open an existing key container.

 int  initCrypt_qmd(  QMD_VAR_MIS  *  pVar,  LPCTSTR  szContainer,  LPCTSTR  szProvider,  BOOL  bNewKeySetIfNotExists,  ENC_CTX_session  *  pEncCtx  )
{
	int				iErr			=		-1;
	HCRYPTPROV		hCryptProv		=		NULL;	       // handle for a cryptographic
	BOOL			bAcquired		=		FALSE;

	HCRYPTKEY		hKey_rsa		=		NULL;
	BYTE		*	pbKeyBlob		=		NULL;
	DWORD			dwBlobLen;

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
	
		  if  (  !bNewKeySetIfNotExists  )  goto  errLabel;

		  {
			  CQySyncObj	syncObj;
			  if  (  syncObj.sync(  CONST_mutexName_syncKey_qmc  )  )  goto  errLabel;			//  这里的同步是因为CRYPT_NEWKEYSET 不是thread safe

			  if  (  !CryptAcquireContext(  &hCryptProv,  szContainer,  szProvider,  PROV_RSA_FULL,  CRYPT_NEWKEYSET  )  )  {     
      			    printf("Could not create a new key container.\n");
					goto  errLabel;                    
			  }	
			  
		  }
		  
	} // End of else.

	bAcquired  =  TRUE;

	//-------------------------------------------------------------------
	// A cryptographic context and a key container are available. Perform
	// any functions that require a cryptographic provider handle.


	//  下面取得公钥

	if  (  !CryptGetUserKey(  hCryptProv,  AT_KEYEXCHANGE,  &hKey_rsa  )  )  {
		if  (  GetLastError(  )  != NTE_NO_KEY  )  goto  errLabel;

		//  Check to determine whether an exchange key needs to be created.
		//  Create a key exchange key pair.
		{
			CQySyncObj	syncObj;
			if  (  syncObj.sync(  CONST_mutexName_syncKey_qmc  )  )  goto  errLabel;		//  这里的同步是因为CryptGenKey 不是thread safe

			traceLogA(  "The exchange key dose not exist,Attempting to create an exchange key pair. \n"  );
			if  (  !CryptGenKey(  hCryptProv,	AT_KEYEXCHANGE,  0,  &hKey_rsa  )  )   goto  errLabel;
			traceLogA(  " Exchange key pair created.\n"  );
		}
	}

	//
	int		len					=	0;
	DWORD	dwBlockLen_encrypt  =	0;
	DWORD	dwBlockLen_decrypt	=	0;

	len  =  sizeof(  dwBlockLen_decrypt  );
	if  (  !CryptGetKeyParam(  hKey_rsa,  KP_KEYLEN,  (  BYTE  *  )&dwBlockLen_decrypt,  (  DWORD  *  )&len,  0  )  )  goto  errLabel;
	dwBlockLen_decrypt  /=  8;	
	dwBlockLen_encrypt  =  dwBlockLen_decrypt;
	if  (  dwBlockLen_encrypt  <=  11  )  goto  errLabel;
	dwBlockLen_encrypt  -=  11;


	//  导出公钥
	if  (  !pVar->crypt.uiBlobLen_publicKey  )  {
		if  (  !bGetExportedKey(  hKey_rsa,  PUBLICKEYBLOB,  &pbKeyBlob,  &dwBlobLen  )  )  goto  errLabel;
	
		if  (  dwBlobLen  >  mycountof(  pVar->crypt.publicKeyBlob  )  )  {
			goto  errLabel;
		}

		pVar->crypt.uiBlobLen_publicKey  =  dwBlobLen;
		memcpy(  pVar->crypt.publicKeyBlob,  pbKeyBlob,  pVar->crypt.uiBlobLen_publicKey  );
	}


	if  (  pEncCtx  )  {
		pEncCtx->key_rsa.hKey  =  hKey_rsa;  hKey_rsa  =  NULL;
		pEncCtx->key_rsa.dwBlockLen_decrypt  =  dwBlockLen_decrypt;									//  密钥长度的字节数
		pEncCtx->key_rsa.dwBlockLen_encrypt  =  dwBlockLen_encrypt;

		pEncCtx->hCryptProv  =  hCryptProv;		hCryptProv  =  NULL;
	}


	iErr  =  0;

errLabel:

	if  (  pbKeyBlob  )	 free(  pbKeyBlob  );

	//  Destroy the exchange key
	if  (  hKey_rsa  )  {
		if  (  !(  CryptDestroyKey(  hKey_rsa  )  )  )  traceLogA(  (  "Error  during CryptDestroyKey ."  )  );
	}

	if  (  bAcquired  )  {  
		// When the handle is no longer needed, it must be released.
		if  (  hCryptProv  )  {
            if  (  !CryptReleaseContext(  hCryptProv,  0  )  )  traceLogA("The handle could not be released.\n");			
		}
	}

	traceLogA(  "initCrypt_qmd %s",  iErr  ?  "failed."  :  "ok"  );

	return  iErr;
}


 void  exitCrypt_qmd(  QMD_VAR_MIS  *  pVar,  ENC_CTX_session  *  pEncCtx  )
{

	if  (  !pEncCtx  )  return;

	if  (  pEncCtx->key_session.hKey  )  {
		if  (  !(  CryptDestroyKey(  pEncCtx->key_session.hKey  )  )  )  traceLogA(  (  "Error  during CryptDestroyKey ."  )  );
	}
	if  (  pEncCtx->key_rsa.hKey  )  {
		if  (  !(  CryptDestroyKey(  pEncCtx->key_rsa.hKey  )  )  )  traceLogA(  (  "Error  during CryptDestroyKey ."  )  );
	}
	if  (  pEncCtx->hCryptProv  )  {
          if  (  !CryptReleaseContext(  pEncCtx->hCryptProv,  0  )  )  traceLogA("The handle could not be released.\n");			
	}

	traceLogA(  "exitCrypt_qmd ok"  );
	return;
}

 void  exitCrypt_qmd(  void  *  pQmdSession  )
{
	 QMD_SESSION  *  pSession  =  (  QMD_SESSION  *  )pQmdSession;

	 if  (  !pSession  )  return;

	 if  (  pSession->ucbEncInited  )  {
		 exitCrypt_qmd(  NULL,  &pSession->commEncCtx  );  pSession->ucbEncInited  =  FALSE;
	 }

	 return;
 }

