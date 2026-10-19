

#ifndef  __QMCRYPT_H__
#define  __QMCRYPT_H__	//  {



#define		CONST_cspContainer_qmd								_T(  "QmdKeyContainer"  )			//  name of the key container to be used

#define		CONST_cspContainer_qmc								_T(  "QmcKeyContainer"  )			//  name of the key container to be used
#define		CONST_mutexName_syncKey_qmc							_T(  "QmcSyncKey"  )


#define		DEFAULT_cspProvider									MS_ENHANCED_PROV


#define		CONST_encryptBlockSize								8 



typedef  struct  __encCtx_session_t								{
				 QY_ENC_CTX										common;
				 //
				 HCRYPTPROV										hCryptProv;										// handle for a cryptographic

				 struct											{
                     HCRYPTKEY									hKey;										//  在messenger, 表示公钥. //  在daemon, 表示private/public pairs
					 DWORD										dwBlockLen_encrypt;							//  加密的blockLen, 密钥长度的字节数 - 11
					 DWORD										dwBlockLen_decrypt;							//  解密的blockLen, 密钥长度的字节数
				 }												key_rsa;

				 struct											{
				 	 HCRYPTKEY									hKey;
					 DWORD										dwBlockLen_encrypt;							//  加密的blockLen 
					 DWORD										dwBlockLen_decrypt;							//  解密的blockLen
				 }												key_session;

				 //
				 unsigned  int									uiBlobLen_sessionKey;
				 char											sessionKeyBlob[CONST_bufSize_sessionKeyBlob];

				 TCHAR											mutexName_syncCrypt[24];					//  2008/10/12, 对每个会话密钥，要保证线程同步。微软的api不支持在2个线程里同时用一个密钥

}		 ENC_CTX_session;


BOOL  bGetExportedKey(  HCRYPTKEY hKey, DWORD dwBlobType,  LPBYTE *ppbKeyBlob, LPDWORD pdwBlobLen  );

int  encryptData(  ENC_CTX_session  *  pEncCtx,  QY_BUF  *  pBuf_help,  char  *  data,  unsigned  int  *  puiDataLen,  unsigned  int  uiBufLen  );
int  decryptData(  ENC_CTX_session  *  pEncCtx,  QY_BUF  *  pBuf_help,  char  *  encData,  unsigned  int  *  puiEncDataLen  );


#endif

