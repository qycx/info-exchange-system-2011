


#include	<windows.h> 
#include	<stdio.h>  
#include	<ras.h>
#include	<iphlpapi.h>
#include	<tchar.h>
#include	"asrWMon.h"


#define RTN_OK 0 
#define RTN_ERROR 13  


 void  DisplayWinError(  LPSTR  szAPI,  DWORD  dwError  ) 
{
	 return;
} 

/*
 int  setQwmReg777(  void  ) 
{     
	// SID_IDENTIFIER_AUTHORITY sia					=  SECURITY_NT_AUTHORITY;   
	SID_IDENTIFIER_AUTHORITY	authWorld			=  SECURITY_WORLD_SID_AUTHORITY;
	// PSID						pInteractiveSid		=  NULL;     
	// PSID						pAdministratorsSid	=  NULL;     
	PSID						pSidWorld			=  NULL;
	SECURITY_DESCRIPTOR			sd;     
	PACL						pDacl				=  NULL;     
	DWORD						dwAclSize;     
	HKEY						hKey;     
	LONG						lRetCode;     
	BOOL						bSuccess			=  FALSE; 
	
	if  (  RegCreateKeyEx(  HKEY_LOCAL_MACHINE,  CONST_qyKey_qwm,  0,  "",  0,  KEY_ALL_ACCESS,  NULL,  &hKey,  NULL  )  ==  ERROR_SUCCESS  )  {
		RegCloseKey(  hKey  );
	}
	
	// assume this function fails      
	//     
	// open the performance key for WRITE_DAC access     
	//     
	lRetCode  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  TEXT(  CONST_qyKey_qwm  ),  0,  WRITE_DAC,  &hKey  );      
	if  (  lRetCode  !=  ERROR_SUCCESS  )  {         
		//  DisplayWinError(  "RegOpenKeyEx",  lRetCode  );         
		traceLogA(  "setQwmReg777 RegOpenKeyEx %s failed.",  CONST_qyKey_qwm  );
		return  RTN_ERROR;     
	}      
	//     
	// prepare a Sid representing any Interactively logged-on user     
	//     
	// if(!AllocateAndInitializeSid( &sia,1,SECURITY_INTERACTIVE_RID,         
	//	0, 0, 0, 0, 0, 0, 0,&pInteractiveSid         )) 
	// {         
	//	DisplayWinError("AllocateAndInitializeSid", GetLastError());         		goto cleanup;     
	// }      
	//     
	// preprate a Sid representing the well-known admin group     
	//     
	// if(!AllocateAndInitializeSid( &sia,2, SECURITY_BUILTIN_DOMAIN_RID,         
	//	DOMAIN_ALIAS_RID_ADMINS,0, 0, 0, 0, 0, 0,         		&pAdministratorsSid         )) 
	// {         
	//	DisplayWinError("AllocateAndInitializeSid", GetLastError());         		goto cleanup;     
	// }

	BOOL  bRes;     
	
	bRes  =  pAllocateAndInitializeSid(  &authWorld,  1,  SECURITY_WORLD_RID, 
										 0,  0,  0,  0,  0,  0,  0,  &pSidWorld  );     
	if  (  FALSE  ==  bRes  )  { 
		traceLogA(  "AllocateAndInitializeSid"  ); 
		goto  cleanup;
	}      
	
	//     
	// compute size of new acl     
	//     
	// dwAclSize = sizeof(ACL) + 
	//	2 * ( sizeof(ACCESS_ALLOWED_ACE) - sizeof(DWORD) ) +         
	//	GetLengthSid(pInteractiveSid) +         
	//	GetLengthSid(pAdministratorsSid) ;      
	dwAclSize  =  sizeof(  ACL  )  +  1  *  (  sizeof(  ACCESS_ALLOWED_ACE  )  -  sizeof(  DWORD  )  )
				  +  pGetLengthSid(  pSidWorld  );
	//     
	// allocate storage for Acl     
	//     
	pDacl  =  (  PACL  )HeapAlloc(  GetProcessHeap(  ),  0,  dwAclSize  );     
	if  (  pDacl  ==  NULL  )  goto  cleanup;      
	if  (  !pInitializeAcl(  pDacl,  dwAclSize,  ACL_REVISION  )  )  {         
		DisplayWinError(  "InitializeAcl",  GetLastError(  )  );         
		goto  cleanup;     
	}      
	//     
	// grant the Interactive Sid KEY_READ access to the perf key     
	//     
	// if(!AddAccessAllowedAce( pDacl,ACL_REVISION,KEY_READ,
	//	pInteractiveSid         )) 
	// {         
	//	DisplayWinError("AddAccessAllowedAce", GetLastError());         
	//	goto cleanup;     
	// }      
	//     
	// grant the Administrators Sid KEY_ALL_ACCESS access to the perf key     	//     
	// if(!AddAccessAllowedAce( pDacl,ACL_REVISION,KEY_ALL_ACCESS,         
	// 	pAdministratorsSid         )) 
	// {         
	//	DisplayWinError("AddAccessAllowedAce", GetLastError());         
	//	goto cleanup;     
	// }      

	if  (  !pAddAccessAllowedAce(  pDacl,  ACL_REVISION,KEY_ALL_ACCESS,  pSidWorld  )  )  {         
		DisplayWinError(  "AddAccessAllowedAce",  GetLastError(  )  );         
		goto  cleanup;     
	}      


	if  (  !pInitializeSecurityDescriptor(  &sd,  SECURITY_DESCRIPTOR_REVISION  )  )  {         		DisplayWinError("InitializeSecurityDescriptor", GetLastError());         		goto cleanup;     
	}      
	if  (  !pSetSecurityDescriptorDacl(  &sd,  TRUE,  pDacl,  FALSE  )  )  {         		
		DisplayWinError(  "SetSecurityDescriptorDacl",  GetLastError(  )  );         		
		goto  cleanup;     
	}      
	//     
	// apply the security descriptor to the registry key     
	//     
	lRetCode  =  pRegSetKeySecurity(  hKey,  (  SECURITY_INFORMATION  )DACL_SECURITY_INFORMATION,  &sd  );      
	if  (  lRetCode  !=  ERROR_SUCCESS  )  {         		
		DisplayWinError(  "RegSetKeySecurity",  lRetCode  );         
		goto  cleanup;     
	}      
	
	bSuccess  =  TRUE; // indicate success  

cleanup:   
	
	RegCloseKey(  hKey  );     
	
	//     
	// free allocated resources     
	//     
	
	if  (  pDacl  !=  NULL  )  HeapFree(  GetProcessHeap(  ),  0,  pDacl  );      

	// if(pInteractiveSid != NULL)         
	//	FreeSid(pInteractiveSid);      
	//if(pAdministratorsSid != NULL)         
	//	FreeSid(pAdministratorsSid);      
	if  (  pSidWorld  !=  NULL  )  pFreeSid(  pSidWorld  );
	if  (  !bSuccess  )  {         
		traceLogA(  "setAwmReg ..  failed."  );         
		return  RTN_ERROR;  
	}
	
	return  RTN_OK;     
	
}  
*/
 

 extern  "C"  int  qwmGetProcessGrps(  QY_ENV  *  pEnv,  int  *  pFlg  )
{
	 int							iErr				=	-1;
	 DWORD							dwSize				=	0;
	 TOKEN_GROUPS				*	pSidInfo			=	NULL;
	 DWORD							i;
	 HANDLE							hToken				=	NULL;
	 unsigned  char					ucbTokenOpen		=	FALSE;
	 TOKEN_INFORMATION_CLASS		tic					=	TokenGroups;  
	 int							iType;
	 int							flg					=	0;				//  先将标志位清空
	 QWM_DYN_LIB				*	pDynLib				=	(  QWM_DYN_LIB  *  )pEnv->pDynLibs;
	 
	 if  (  !pDynLib->pOpenProcessToken(  GetCurrentProcess(  ),  TOKEN_QUERY,  &hToken  )  )  goto  errLabel;
	 ucbTokenOpen  =  TRUE;

	 dwSize  =  0;
	 pDynLib->pGetTokenInformation(  hToken,  tic,  NULL,  dwSize,  &dwSize  );
	 pSidInfo  =  (  PTOKEN_GROUPS  )new  BYTE[dwSize];
	 if  (  !pSidInfo  )  goto  errLabel;
	 if  (  !pDynLib->pGetTokenInformation(  hToken,  tic,  pSidInfo,  dwSize,  &dwSize  )  )  {
		 traceLogA(  "GetTokenInfomation Error %u\n",  GetLastError(  )  );
		 goto  errLabel;
	 }
	 if  (  !pSidInfo->GroupCount  )  {
		 traceLogA(  "\tNone!\n"  );
		 iErr  =  0;
		 goto  errLabel;
	 }
	 for  (  i  =  0;  i  <  pSidInfo->GroupCount;  i  ++  )  {
		  SID_NAME_USE	sidType;
		  TCHAR			nameBuf[256];
		  TCHAR			domainBuf[256];
		  DWORD			dwNameSize			=  mycountof(  nameBuf  );
		  DWORD			dwDomainSize		=  mycountof(  domainBuf  );
		  DWORD			dwAttr  =  0;

		  if  (  !pDynLib->pLookupAccountSid(  NULL,  pSidInfo->Groups[i].Sid,	nameBuf,  &dwNameSize,  domainBuf,  &dwDomainSize,  &sidType  )  )  {
			  if  (  GetLastError(  )  ==  ERROR_NONE_MAPPED  )  wsprintf(  nameBuf,  _T(  "NONE_MAPPED"  )  );
			  else  traceLogA(  "LoopupAccountSid Error %u\n",  GetLastError(  )  );
			  continue;
		  }
		
		  dwAttr  =  pSidInfo->Groups[i].Attributes;

		  //  traceLogA(  "%12s \\%-20s \t%s\n",  domainBuf,  nameBuf,  (  dwAttr  &  SE_GROUP_USE_FOR_DENY_ONLY  )  ?  "[DENY]"  :  ""  );
		  
		  if  (  !(  dwAttr  &  SE_GROUP_USE_FOR_DENY_ONLY  )  )  {
			  iType  =  qyGetTypeByDes(  CONST_qyGrpTable,  nameBuf  );
			  if  (  iType  !=  -1  )  flg  |=  1  <<  iType;
		  }
	 }

	 for  (  i  =  0;  CONST_qyGrpTable[i].type  !=  -1;  i  ++  )  {
		  if  (  flg  &  (  1  <<  CONST_qyGrpTable[i].type  )  )
			  traceLogA(  "\tbelongs to %s",  CONST_qyGrpTable[i].des  );
	 }

	 *pFlg  =  flg;
	 iErr  =  0;

errLabel:

	 if  (  pSidInfo  )  delete  []  (  LPBYTE  )pSidInfo;
	 if  (  ucbTokenOpen  &&  hToken  )  CloseHandle(  hToken  );

	 return  iErr;

}


 extern  "C"  int  qwmDelService(  QWM_DYN_LIB  *  pDynLib,  TCHAR  *  serviceName  )
{	 
	 TCHAR				buf[256];
	 unsigned  char		ucbServiceExists	=	FALSE;
	 LONG				KeyRes;
	 HKEY				PathKey				=	NULL;


	 if  (  !serviceName  ||  !serviceName[0]  )  return  -1;

	 wsprintf(  buf,  _T(  "System\\CurrentControlSet\\Services\\%s"  ),  serviceName  );
	 KeyRes  =  RegOpenKeyEx(  HKEY_LOCAL_MACHINE,  buf,  0,  KEY_READ,  &PathKey  );
	 if  (  KeyRes  ==  ERROR_SUCCESS  )  {
		 RegCloseKey(  PathKey  );
		 ucbServiceExists  =  TRUE;
	 }

	 if  (  ucbServiceExists  )  return  0;

	 SC_HANDLE  scm  =  pDynLib->pOpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS);
	 if  (  scm  !=  NULL  )  {
		 SC_HANDLE  srv  =  pDynLib->pOpenService(scm,serviceName,SERVICE_STOP|DELETE);
		 if  (  srv  !=  NULL  )  {
			 pDynLib->pDeleteService(srv);
			 pDynLib->pCloseServiceHandle(srv);
		 }
		 pDynLib->pCloseServiceHandle(scm);
	 }
	 
 	 return  0;
}



