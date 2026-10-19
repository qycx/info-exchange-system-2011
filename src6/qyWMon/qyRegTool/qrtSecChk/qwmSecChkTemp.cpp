

#include	<windows.h>
#include	<winsock.h>
#include	<ras.h>
#include	<raserror.h>
#include	<commctrl.h>
#include	<lmaccess.h>
#include	<iphlpapi.h>
#include	<tchar.h>
//  #include	"resource.h"
#include	"asrWMon.h"
#include	"qyRegToolProc.h"

 int  testFunc(  void  *  pQyRegToolParam  )
{
	 QY_REG_TOOL	*	pQyRegTool  =  (  QY_REG_TOOL  *  )pQyRegToolParam;
#ifdef  __DEBUG__
	    //  QWM_ASSETS_INFO		assetInfo;

		//  memset(  &assetInfo,  0,  sizeof(  assetInfo  )  );
	    //  getQwmAssetsHardwareInfo(  pQyRegTool,  &assetInfo  );

#endif
	 return  0;
}


/*

BOOL  GetTextualSid(  PSID pSid,  LPTSTR TextualSid,  LPDWORD  dwBufferLen  );
void myEnumAllUsrs(  const  wchar_t  *  server  );


//  这里带出一个分配了内存的psid，需要在后面将其释放
 int  myGetAccountSid(  char  *  systemName,  char  *  accountName,  SID  **  psid  ) 
{    
	 int		iErr		=	-1;
	 ULONG		ret			=	ERROR_SUCCESS;      	
	 SID	*	_psid		=	NULL;
	 char	*	domainName	=	NULL;
	 char		sidTxtBuf[1024];	DWORD  dwBufSize;
     
	 if  (  !accountName  )  goto  errLabel;
	 _psid  =  NULL;

	 if  (  _psid  ==  NULL  )  {
         DWORD  cusid  =  0,  crd  =  0;
         SID_NAME_USE	esnu;          
		 if  (  !pLookupAccountName(  systemName,  accountName,  NULL,  &cusid,  NULL,  &crd,  &esnu  )  )  {
             if  (  ERROR_INSUFFICIENT_BUFFER  ==  (  ret  =  GetLastError(  )  )  )  {
				 ret  =  ERROR_SUCCESS;  
				 if  (  NULL  ==  (  _psid  =  (  SID  *  )LocalAlloc(  LMEM_FIXED,  cusid  )  )  )  {
                     traceLogA(  "Error: not enough memory"  );  goto  errLabel;

				 }                 
				 if  (  NULL  ==  (  domainName  =  (  char  *  )LocalAlloc(  LMEM_FIXED,  crd  *  sizeof(  WCHAR  )  )  )  )  {
					 traceLogA(  "Error: not enough memory."  );  goto  errLabel;
                 }     
				 if  (  !pLookupAccountName(  systemName,  accountName,  _psid,  &cusid,  domainName,  &crd,  &esnu  )  )  {
					 ret  =  GetLastError(  );   goto  errLabel;
				 }  
			 } 
		 } 
     } 
     //  *psid  =  _psid;      

	 dwBufSize  =  sizeof(  sidTxtBuf  );
	 GetTextualSid(  _psid,  sidTxtBuf,  &dwBufSize  );
	 traceLogA(  "usrName is %s, sid is %s",  accountName,  sidTxtBuf  );

	 {
	  QY_REG						reg;
	 char						recentDir[CONST_qyMaxPathLen  +  1];
	 
	 memset(  &reg,  0,  sizeof(  reg  )  );
	 reg.hKeyRoot0  =  HKEY_USERS;
	 if  (  getUsrKey(  sidTxtBuf,  CONST_qyRootKey_shellFolders,  reg.rootKey,  sizeof(  reg.rootKey  )  )  )  goto  errLabel;
	 if  (  qyGetRegCfgEx(  &reg,  CONST_regValName_recent,  recentDir,  sizeof(  recentDir  )  )  )  goto  errLabel;
	 trim(  recentDir  );
	 traceLogA(  "recentDir of %s is %s",  accountName,  recentDir  );
	 }



	 iErr  =  0;
	
errLabel:

	 if  (  domainName  )  LocalFree(  domainName  );		//  _domain不需要带出去

	 return  iErr; 
} 

 BOOL  GetTextualSid(  PSID pSid,          // binary Sid
					   LPTSTR TextualSid,  // buffer for Textual representaion of Sid
    				   LPDWORD dwBufferLen // required/provided TextualSid buffersize
					   )

{ 
    PSID_IDENTIFIER_AUTHORITY psia;
    DWORD dwSubAuthorities;
    DWORD dwSidRev=SID_REVISION;
    DWORD dwCounter;
    DWORD dwSidSize;

    //
    // test if Sid passed in is valid
    //
    if  (  !pIsValidSid(  pSid  )  )  return  FALSE;

    // obtain SidIdentifierAuthority
    psia  =  pGetSidIdentifierAuthority(  pSid  );

    // obtain sidsubauthority count
    dwSubAuthorities  =  *pGetSidSubAuthorityCount(  pSid  );

    //
    // compute buffer length
    // S-SID_REVISION- + identifierauthority- + subauthorities- + NULL
    //
    dwSidSize=(15 + 12 + (12 * dwSubAuthorities) + 1) * sizeof(TCHAR);

    //
    // check provided buffer length.
    // If not large enough, indicate proper size and setlasterror
    //
    if (*dwBufferLen < dwSidSize)
    {
        *dwBufferLen = dwSidSize;
        SetLastError(ERROR_INSUFFICIENT_BUFFER);
        return FALSE;
    }

    //
    // prepare S-SID_REVISION-
    //
    dwSidSize=wsprintf(TextualSid, TEXT("S-%lu-"), dwSidRev );

    //
    // prepare SidIdentifierAuthority
    //
    if ( (psia->Value[0] != 0) || (psia->Value[1] != 0) )
    {
        dwSidSize+=wsprintf(TextualSid + lstrlen(TextualSid),
                    TEXT("0x%02hx%02hx%02hx%02hx%02hx%02hx"),
                    (USHORT)psia->Value[0],
                    (USHORT)psia->Value[1],
                    (USHORT)psia->Value[2],
                    (USHORT)psia->Value[3],
                    (USHORT)psia->Value[4],
                    (USHORT)psia->Value[5]);
    }
    else
    {
        dwSidSize+=wsprintf(TextualSid + lstrlen(TextualSid),
                    TEXT("%lu"),
                    (ULONG)(psia->Value[5]      )   +
                    (ULONG)(psia->Value[4] <<  8)   +
                    (ULONG)(psia->Value[3] << 16)   +
                    (ULONG)(psia->Value[2] << 24)   );
    }

    //
    // loop through SidSubAuthorities
    //
    for (dwCounter=0 ; dwCounter < dwSubAuthorities ; dwCounter++)
    {
        dwSidSize+=wsprintf(TextualSid + dwSidSize, TEXT("-%lu"),
                    *pGetSidSubAuthority(  pSid,  dwCounter  )  );
    }

    return TRUE;

} 

 void myEnumAllUsrs(  const  wchar_t  *  server  )
{
	USER_INFO_1  *  buf,  *  cur;
	DWORD  read,  totalremaining,  resumeh,  rc,  i;
	char  usrName[512];
	//  WCHAR  wScriptPath[MAX_PATH + 1];
	//  int  iRet;
	
	//  iRet  =  MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, scriptPath, -1,  wScriptPath, MAX_PATH );
	//  if ( !iRet ) goto errLabel;
	//  wScriptPath[iRet] = 0;

	resumeh  =  0;

	do  {
		buf  =  NULL;
		rc  =  pLMSNetUserEnum(  (  LPWSTR  )server,  1,  0,  (  BYTE  **  )&buf,  1024,  &read,  &totalremaining,  &resumeh  );
		if  (  rc  !=  ERROR_MORE_DATA  &&  rc  !=  ERROR_SUCCESS  )  break;

		traceLogA(  "\ngot %lu entries out of %lu\n",  read,  totalremaining  );
		for  (  i  =  0,  cur  =  buf;  i  <  read;  ++  i,  ++  cur  )  {
			 // print_user( cur->usri1_name, cur->usri1_flags );
			 // printf( "script path is [%S].\n", cur->usri1_script_path );
			 // if ( cur->usri1_priv == USER_PRIV_GUEST )
			 // 	printf( "He is a Guest.\n" );
			 // else if ( cur->usri1_priv == USER_PRIV_USER )
			 //	printf( "He is a User.\n" );
			 // else if ( cur->usri1_priv == USER_PRIV_ADMIN )
			 // 	printf( "He is the Administrator.\n" );
			 // else 
			 //	printf( "Unknown priv.\n" );
			 //  if  (  cur->usri1_flags  &  UF_NORMAL_ACCOUNT  )  
			{
				//  if ( wcscmp( cur->usri1_script_path, wScriptPath ) )
				//	setUsrScriptPath( wScriptPath, cur->usri1_name );
				traceLogA(  "usrName is %S",  cur->usri1_name  );
				_snprintf(  usrName,  sizeof(  usrName  ),  "%S",  cur->usri1_name  );
				myGetAccountSid(  NULL,  usrName,  NULL  );	//  for test
			}
		}
		
		if  (  buf  !=  NULL  )  pLMSNetApiBufferFree(  buf  );

	}  while  (  rc  ==  ERROR_MORE_DATA  );

	if  (  rc  !=  ERROR_SUCCESS  )  traceLogA(  "NUE() returned %lu\n",  rc  );

//  errLabel:
	return;

}


   int  qwmEnumUsr(  QY_ENV  *  pEnv,  PF_commonHandler  pF,  void  *  p0,  void  *  p1  )
{
	 int					iErr					=	-1;
	 QWM_USR_INFO			usrInfo;
	 DWORD					dwRtn, dwSubKeyLength;
	 unsigned  int			uiRegUsrIndex			=	0;
		 
	 for  (  uiRegUsrIndex  =  0;  ;  uiRegUsrIndex  ++  )  {
		  dwSubKeyLength  =  sizeof(  usrInfo.szSubKey  );
     	  dwRtn  =  RegEnumKeyEx(  HKEY_USERS,  uiRegUsrIndex,  usrInfo.szSubKey,  &dwSubKeyLength,  NULL,  NULL,  NULL,  NULL  );
	 	  if  (  dwRtn  !=  ERROR_SUCCESS  )  break;
		  
		  //
	 	  //  现在开始处理刚被枚举的用户
		  if  (  !usrInfo.szSubKey[0]  )  continue;		//  校验
	 
		  //  下面取用户名,  对NT, 除缺省外，统一为未知用户。
	 	  if  (  !lstrcmpi(  usrInfo.szSubKey,  ".Default"  )  )  lstrcpyn(  usrInfo.name,  "(缺省)",  sizeof(  usrInfo.name  )  );
	 	  else  if  (  getUsrNameFromReg(  usrInfo.szSubKey,  usrInfo.name,  sizeof(  usrInfo.name  )  )  )  continue;
		
		  traceLogA(  "qwmEnumUsr得到subKey is [%s], usrName is [%s], index is %d",  usrInfo.szSubKey,  usrInfo.name,  uiRegUsrIndex  );

		  if  (  pF  )  pF(  p0,  p1,  &usrInfo  );	 	  
	 	  
	 }
	 
	 
	 iErr  =  0;

//  errLabel:

	 return  iErr;

}


  */

