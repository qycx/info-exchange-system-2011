
#include	<stdio.h>
#include	<stdlib.h>
#include	<windows.h>
#include	<tchar.h>
#include	"qyPreLicense.h"
#include	"sentinelkeys.h"
#include	"sentinelkeystypes.h"
#ifdef  __SystemId_Is__
		#include	"SentinelKeysLicense_is.h"
#else
		#include	"SentinelKeysLicense_netMc.h"
#endif
#include	"qyLicense.h"

typedef  SP_STATUS (  SP_API  *  PF_SFNTGetLicense  )(SP_IN SP_DWORD	devID, 
										  SP_IN SPP_BYTE	softwareKey, 
										  SP_IN SP_DWORD	licID, 
										  SP_IN SP_DWORD	flags, 
										  SP_IO SPP_HANDLE	licHandle);
typedef  SP_STATUS (  SP_API  *  PF_SFNTGetDeviceInfo  )(SP_IN SP_HANDLE			licHandle, 
											 SP_OUT SPP_DEVICE_INFO		deviceInfo);

typedef  SP_STATUS (  SP_API  *  PF_SFNTReleaseLicense  )(SP_IN SP_HANDLE		licHandle);
typedef  SP_STATUS (  SP_API  *  PF_SFNTReadString  )(SP_IN SP_HANDLE	licHandle, 
										  SP_IN SP_DWORD	featureID, 
										  SP_OUT SPP_CHAR	string, 
										  SP_IN SP_DWORD	stringLength);



#ifdef  __DEBUG__

SP_EXPORT SP_STATUS SP_API mySFNTGetLicense(  SP_DYN_LIB  *  pDynLib,  SP_IN SP_DWORD	devID, 
										  SP_IN SPP_BYTE	softwareKey, 
										  SP_IN SP_DWORD	licID, 
										  SP_IN SP_DWORD	flags, 
										  SP_IO SPP_HANDLE	licHandle)
{
	if  (  !pDynLib  ||  !pDynLib->pSFNTGetLicense  )  return  SP_ERR_ACCESS_DENIED;
	return  (  (  PF_SFNTGetLicense  )pDynLib->pSFNTGetLicense  )(	 devID,  softwareKey,  licID,  flags,  licHandle  );
}

SP_EXPORT SP_STATUS SP_API mySFNTGetDeviceInfo(  SP_DYN_LIB  *  pDynLib,  SP_IN SP_HANDLE			licHandle, 
											 SP_OUT SPP_DEVICE_INFO		deviceInfo)
{
	if  (  !pDynLib  ||  !pDynLib->pSFNTGetDeviceInfo  )  return  SP_ERR_ACCESS_DENIED;
	return  (  (  PF_SFNTGetDeviceInfo  )pDynLib->pSFNTGetDeviceInfo  )(  licHandle,  deviceInfo  );

}

 SP_EXPORT SP_STATUS SP_API mySFNTReleaseLicense(  SP_DYN_LIB  *  pDynLib,  SP_IN SP_HANDLE		licHandle)
{
	 if  (  !pDynLib  ||  !pDynLib->pSFNTReleaseLicense  )  return  SP_ERR_ACCESS_DENIED;
	 return  (  (  PF_SFNTReleaseLicense  )pDynLib->pSFNTReleaseLicense  )(  licHandle  );
}

 SP_EXPORT SP_STATUS SP_API mySFNTReadString(  SP_DYN_LIB  *  pDynLib,  SP_IN SP_HANDLE	licHandle, 
										  SP_IN SP_DWORD	featureID, 
										  SP_OUT SPP_CHAR	string, 
										  SP_IN SP_DWORD	stringLength)
{
	 if  (  !pDynLib  ||  !pDynLib->pSFNTReadString  )  return  SP_ERR_ACCESS_DENIED;
	 return  (  (  PF_SFNTReadString  )pDynLib->pSFNTReadString  )(  licHandle,  featureID,  string,  stringLength  );
}

#else

	#define		mySFNTGetLicense(  p0,  p1,  p2,  p3,  p4,  p5  )		SFNTGetLicense(  p1,  p2,  p3,  p4,  p5  )
	#define		mySFNTGetDeviceInfo(  p0,  p1,  p2  )					SFNTGetDeviceInfo(  p1,  p2  )
	#define		mySFNTReleaseLicense(  p0,  p1  )						SFNTReleaseLicense(  p1  )					
	#define		mySFNTReadString(  p0,  p1,  p2,  p3,  p4  )			SFNTReadString(  p1,  p2,  p3,  p4  )

#endif



#ifdef  __SystemId_Is__

		 #define		CONST_featureId_qexdz							SP_QYNEWEXDZ_STRING

#else

		 //  #define		CONST_devId_sentinelKey						0xe4313f8d							//  2007/02/28
		 #define  DEVELOPERID											0xE4313F8D

		 #define		CONST_featureId_qexdz							SP_QEXDZ_STRING

 
#endif



  int  getDevId_sentinelKey(  )
{
	 return  DEVELOPERID;
}



 int  initSentinelKey(  QY_LICENSE_CTX  *  pCtx,  unsigned  int  devId  )
{
	 int					iErr		=	-1;
	 SP_STATUS				status;
	 SP_DWORD				flags		=	0;
	 SP_HANDLE				licHandle	=	0;               /* Sentinel Keys license handle */
	 BOOL					bLicenseGot	=	FALSE;
	 HINSTANCE				hDll		=	0;
	 
	 if  (  pCtx->bSentinelKeyInited  )  return  -1;
	 
	 #ifdef  __DEBUG__
			 pCtx->spDynLib.hDll_sentinelKeyW  =  hDll  =  LoadLibrary(  _T(  "SentinelKeyW.dll"  )  );
			 if  (  !pCtx->spDynLib.hDll_sentinelKeyW  )  {
				 traceLogA(  "initSentinelKey failed: hDll_sentinelKeyW not loaded."  );
				 goto  errLabel;
			 }
			 pCtx->spDynLib.pSFNTGetLicense  =  (  void  *  )GetProcAddress(  hDll,  "SFNTGetLicense"  );
			 pCtx->spDynLib.pSFNTGetDeviceInfo  =  (  void  *  )GetProcAddress(  hDll,  "SFNTGetDeviceInfo"  );
			 pCtx->spDynLib.pSFNTReleaseLicense  =  (  void  *  )GetProcAddress(  hDll,  "SFNTReleaseLicense"  );
			 pCtx->spDynLib.pSFNTReadString  =  (  void  *  )GetProcAddress(  hDll,  "SFNTReadString"  );
	 #endif

	 flags  =  SP_STANDALONE_MODE  |  SP_ENABLE_TERMINAL_CLIENT;
	 /* Get the license to run the application */
     status = mySFNTGetLicense(  &pCtx->spDynLib,  devId,
                             SOFTWARE_KEY,   /* Software key specified in SentinelKeysLicense.h */
                             LICENSEID,      /* LicenseID specified in SentinelKeysLicense.h */
                             flags,
                             &licHandle );   
    if  ( status != SP_SUCCESS)  {
		traceLogA(  "Failed to get license. Return code: %d.", status );
		goto  errLabel;
    }
	bLicenseGot  =  TRUE;

	SP_DEVICE_INFO	deviceInfo;
	status  =  mySFNTGetDeviceInfo(  &pCtx->spDynLib,  licHandle,  &deviceInfo  );
	if  (  status  !=  SP_SUCCESS  )  goto  errLabel;


	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  bLicenseGot  )  mySFNTReleaseLicense(  &pCtx->spDynLib,  licHandle  );
		if  (  pCtx->spDynLib.hDll_sentinelKeyW  )  {
			FreeLibrary(  pCtx->spDynLib.hDll_sentinelKeyW  );  pCtx->spDynLib.hDll_sentinelKeyW  =  NULL;
		}
	}
	if  (  !iErr  )  {
		pCtx->licHandle  =  licHandle;
		pCtx->bSentinelKeyInited  =  TRUE;
		pCtx->uiSerialNo  =  deviceInfo.devSN;
	}

	traceLogA(  "initSentinelKey(  )  leaves %s",  iErr  ?  "Failed"  :  "Ok"  );

	return  iErr;
}

 void  exitSentinelKey(  QY_LICENSE_CTX  *  pCtx  )
{
	 if  (  pCtx->bSentinelKeyInited  )  {
		 if  (  pCtx->licHandle  )  {
		 	 mySFNTReleaseLicense(  &pCtx->spDynLib,  pCtx->licHandle  );  pCtx->licHandle  =  NULL;
	 	 }
		 if  (  pCtx->spDynLib.hDll_sentinelKeyW  )  {
			 FreeLibrary(  pCtx->spDynLib.hDll_sentinelKeyW  );  pCtx->spDynLib.hDll_sentinelKeyW  =  NULL;
		 }
		 pCtx->bSentinelKeyInited  =  FALSE;
	 }

	 traceLogA(  "exitSentinelKey(  )  leaves"  );

	 return;
}


 BOOL  bQySentinelKeyOk(  QY_LICENSE_CTX  *  pCtx,  LPCWSTR  moduleName  )
{
	 BOOL			bRet		=	FALSE;
	 SP_STATUS		status;
	 unsigned  int	featureId	=  CONST_featureId_qexdz;
	 char			value[256]	=	"";
	 
	 if  (  !pCtx->bSentinelKeyInited  )  goto  errLabel;

	 status  =  mySFNTReadString(  &pCtx->spDynLib,  pCtx->licHandle,  featureId,  value,  sizeof(  value  )  );
	 if  (  status  !=  SP_SUCCESS  )  goto  errLabel;

	 if  (  stricmp(  value,  "qadqenhmwsngg"  )  )  goto  errLabel;

	 bRet  =  TRUE;
errLabel:
	 return  bRet;
}