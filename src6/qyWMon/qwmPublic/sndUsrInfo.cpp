


#include	<windows.h>
#include	<winsock.h>
#include	<ras.h>
#include	<raserror.h>
#include	<commctrl.h>
#include	<iphlpapi.h>
#include	<tchar.h>
#include	"asrWMon.h"
#include	"osAuditProc.h"
#include	<time.h>
#include	<lmaccess.h>
#include	<lm.h>

int  enumAllPcUsrs(   QY_ENV  *  pEnv,  void  *  pEventLogInfoParam,  PF_commonHandler  pf,  void  *  p0,  void  *  p1  );


 int  tmpHandler_sndUsrInfo(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int						iErr			=	-1;
	 COMMON_PARAM			*	pCommonParam	=	(  COMMON_PARAM  *  )p0;
	 QWM_THREADINFO			*	pThreadInfo		=	(  QWM_THREADINFO  *  )pCommonParam->p0;
	 QY_W_MON				*	pQwm			=	(  QY_W_MON  *  )pThreadInfo->pParaentParam;
	 QWM_SESSION			*	pSession		=	(  QWM_SESSION  *  )pCommonParam->p1;
	 QY_SOCK				*	pSock			=	(  QY_SOCK  *  )pCommonParam->p2;
	 QWM_USR_PROCINFO		*	pProcInfo		=	(  QWM_USR_PROCINFO  *  )p1;
	 QY_PCUSR_PROP			*	pUsrProp		=	(  QY_PCUSR_PROP  *  )p2;
	 unsigned  int				len;
	 QY_COMM_RESP				tmpResp;
	 char						buf[1024];


	 //  printEventLogProp(  pEventLog  );
	 if  (  pProcInfo->pcCommU.head.cnt  >=  sizeof(  pProcInfo->pcCommU.usrInfos.mems  )  /  sizeof(  pProcInfo->pcCommU.usrInfos.mems[0]  )  )  {
		 traceLogA(  "tmpHandler_sndUsrInfo: 出现了编程错误"  );  goto  errLabel;
	 }
	 memcpy(  &pProcInfo->pcCommU.usrInfos.mems[pProcInfo->pcCommU.usrInfos.cnt],  pUsrProp,  sizeof(  QY_PCUSR_PROP  )  );
	 pProcInfo->pcCommU.usrInfos.cnt  ++  ;

	 if  (  pProcInfo->pcCommU.usrInfos.cnt  ==  sizeof(  pProcInfo->pcCommU.usrInfos.mems  )  /  sizeof(  pProcInfo->pcCommU.usrInfos.mems[0]  )  )  {
		 if  (  (  len  =  qyhtonQyPcCommU(  0,  &pProcInfo->pcCommU  )  )  ==  -1  )  goto  errLabel;
		 if  (  qySendReq(  &pSession->comm,  pSock,  &pQwm->cfg.to,  CONST_qyCmd_sndUsrInfo,  (  char  *  )&pProcInfo->pcCommU,  len  )  )  goto  errLabel;
		 if  (  qyRecvResp(  &pSession->comm,  pSock,  &pQwm->cfg.to,  &tmpResp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;

		 //  这里开始复位
		 memset(  &pProcInfo->pcCommU,  0,  sizeof(  pProcInfo->pcCommU  )  );
		 MACRO_makePcCommHead(  CONST_pcCommType_usrInfo,  pQwm,  pProcInfo->pcCommU  );
		 
	 }

	 iErr  =  0;
errLabel:
	 if  (  iErr  )  pProcInfo->ucbErr  =  TRUE;
	 return  iErr  ?  CONST_qyRet_quit  :  0;
}

 int  sndUsrInfo(  QWM_THREADINFO  *  pThreadInfo  )
{
	 int							iErr				=	-1;
	 QY_W_MON					*	pQwm				=	(  QY_W_MON  *  )pThreadInfo->pParaentParam;
	 QWM_USR_PROCINFO				procInfo;
	 COMMON_PARAM					commonParam;
	 QWM_SESSION					session;
	 QY_SOCK						sock;
	 BOOL							bSessionOpen		=	FALSE;
	 QY_COMM_RESP					tmpResp;
	 char							buf[1024];
	 int							len;

	 if  (  !g_bIsWinNT  )  return  0;
	 traceLogA(  "sndEventLog enters"  );

	 memset(  &session,  0,  sizeof(  session  )  );
	 clearQySock(  &sock  );

	 memset(  &procInfo,  0,  sizeof(  procInfo  )  );
	 MACRO_makePcCommHead(  CONST_pcCommType_usrInfo,  pQwm,  procInfo.pcCommU  );
	 
	 if  (  qwmOpenSession(  pThreadInfo->pParaentParam,  &session,  &sock  )  )  goto  errLabel;
	 bSessionOpen  =  TRUE;

	 MACRO_makeCommonParam3(  pThreadInfo,  &session,  &sock,  commonParam  );
	 enumAllPcUsrs(  &pQwm->env,  &procInfo,  tmpHandler_sndUsrInfo,  &commonParam,  &procInfo  );
	 if  (  procInfo.ucbErr  )  goto  errLabel;

	 //  在tmpHandler_eventLog中没发送完的在这里发送
	 traceLogA(  "发送剩下的%d条事件",  procInfo.pcCommU.head.cnt  );
	 if  (  (  len  =  qyhtonQyPcCommU(  0,  &procInfo.pcCommU  )  )  ==  -1  )  goto  errLabel;
	 if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_sndUsrInfo,  (  char  *  )&procInfo.pcCommU,  len  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;

	 //  发送结束标志
	 memset(  &procInfo.pcCommU,  0,  sizeof(  procInfo.pcCommU  )  );
	 MACRO_makePcCommHead(  CONST_pcCommType_usrInfo,  pQwm,  procInfo.pcCommU  );
	 procInfo.pcCommU.head.ucFlg  =  -1;
	 if  (  (  len  =  qyhtonQyPcCommU(  0,  &procInfo.pcCommU  )  )  ==  -1  )  goto  errLabel;
	 if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_sndUsrInfo,  (  char  *  )&procInfo.pcCommU,  len  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:

	 if  (  bSessionOpen  )  qwmCloseSession(  pThreadInfo->pParaentParam,  &session,  &sock  );

	 return  iErr;

}


 int  enumAllPcUsrs(   QY_ENV  *  pEnv,  void  *  pEventLogInfoParam,  PF_commonHandler  pf,  void  *  p0,  void  *  p1  )
{
	 int				iErr	=  -1;
	 USER_INFO_1	*	buf,	*	cur;
	 DWORD				read,  totalremaining,  rc,  i;
	 DWORD				resumeh =	NULL;
	 wchar_t		*	server	=	NULL;
	 unsigned  char		ucbStop	=	FALSE;
	 QY_PCUSR_PROP		usrProp;
	 QWM_DYN_LIB	*	pDynLib	=	(  QWM_DYN_LIB  *  )pEnv->pDynLibs;
	 
	 if  (  !g_bIsWinNT  )  return  0;
	 traceLogA(  "sndUsrInfo enters"  );

	 do  {
		buf  =  NULL;
		rc  =  pDynLib->pLMSNetUserEnum(  0,  1,  0,  (  BYTE  **  )&buf,  1024,  &read,  &totalremaining,  &resumeh  );
		if  (  rc  !=  ERROR_MORE_DATA  &&  rc !=  ERROR_SUCCESS  )  break;

		//  注意这里不能随便退出，因为在NetUserEnum（）里有内存分配，所以采用了ucbStop的方式，确保buf释放掉

		//  printf( "\ngot %lu entries out of %lu\n", read, totalremaining );
		for  (  i  =  0,  cur  =  buf;  i  <  read;  ++  i,  ++  cur  )  {
			// print_user( cur->usri1_name, cur->usri1_flags );
			//  printf( "script path is [%S].\n", cur->usri1_script_path );
			// if ( cur->usri1_priv == USER_PRIV_GUEST )
			// 	printf( "He is a Guest.\n" );
			// else if ( cur->usri1_priv == USER_PRIV_USER )
			//	printf( "He is a User.\n" );
			// else if ( cur->usri1_priv == USER_PRIV_ADMIN )
			// 	printf( "He is the Administrator.\n" );
			// else 
			//	printf( "Unknown priv.\n" );

			if  (  cur->usri1_flags  &  UF_NORMAL_ACCOUNT  )  {
				traceLogA(  "%S		%s		%S		%2dDays %2dHours\n",  cur->usri1_name,  (  (  cur->usri1_flags  &  UF_ACCOUNTDISABLE  )  ?  " Disabled"  :  ""  ),  cur->usri1_script_path,  cur->usri1_password_age  /  (  24  *  3600  ),  (  cur->usri1_password_age  %  (  24  *  3600  )  )  /  3600  );
				memset(  &usrProp,  0,  sizeof(  usrProp  )  );
				//  _snprintf(  usrProp.usrName,  sizeof(  usrProp.usrName  ),  "%S",  cur->usri1_name  );
				if  (  !WideCharToMultiByte(  CP_ACP,  0,  cur->usri1_name,  -1,  usrProp.usrName,  sizeof(  usrProp.usrName  ),  NULL,  NULL  ) )  usrProp.usrName[0]  =  0;
				usrProp.ucbDisabled  =  (  cur->usri1_flags  &  UF_ACCOUNTDISABLE  )  ?  TRUE  :  FALSE;
				if  (  pf  &&  pf(  p0,  p1,  &usrProp  )  ==  CONST_qyRet_quit  )  ucbStop  =  TRUE;
			}
		}

		if  (  buf  )  pDynLib->pNetApiBufferFree(  buf  );

	 }  while  (  rc  ==  ERROR_MORE_DATA  &&  !ucbStop  );


	 iErr  =  0;

//  errLabel:
	 traceLogA(  "sndUsrInfo leaves with %s",  iErr  ?  "失败"  :  "成功"  );
	 return  iErr;
}



 int  enumUsrLocalGroups(  QY_ENV  *  pEnv,  LPCWSTR  wUsrName,  LPCWSTR  wDomainName,  PF_commonHandler  pf,  void  *  p0,  void  *  p1  )
{
   int								iErr			=	-1;
   LPLOCALGROUP_USERS_INFO_0		pBuf			=	NULL;
   DWORD							dwLevel			=	0;
   DWORD							dwFlags			=	LG_INCLUDE_INDIRECT ;
   DWORD							dwPrefMaxLen	=	MAX_PREFERRED_LENGTH;
   DWORD							dwEntriesRead	=	0;
   DWORD							dwTotalEntries	=	0;
   NET_API_STATUS					nStatus;
   QWM_DYN_LIB					*	pDynLib			=	(  QWM_DYN_LIB  *  )pEnv->pDynLibs;
   BOOL								bBufNeedFree	=	FALSE;

   if  (  !pDynLib  ||  !pDynLib->pNetUserGetLocalGroups  ||  !pDynLib->pNetApiBufferFree  )  return  -1;

   //
   // Call the NetUserGetLocalGroups function 
   //  specifying information level 0.
   //
   //  The LG_INCLUDE_INDIRECT flag specifies that the 
   //   function should also return the names of the local 
   //   groups in which the user is indirectly a member.
   //
   nStatus  =  pDynLib->pNetUserGetLocalGroups(  wDomainName,
												 wUsrName,
                            					 dwLevel,
                            					 dwFlags,
                            					 (LPBYTE *) &pBuf,
                            					 dwPrefMaxLen,				//  由于这个值采用了MAX_PREFERRED_LENGTH, 所以不用考虑空间不够的返回值了
                            					 &dwEntriesRead,
                            					 &dwTotalEntries  );
   //
   // If the call succeeds,
   //
   if  (  nStatus !=  NERR_Success  &&  nStatus  !=  ERROR_MORE_DATA  )  goto  errLabel;
   bBufNeedFree  =  TRUE;

   {
      LPLOCALGROUP_USERS_INFO_0		pTmpBuf;
      DWORD							i;
      DWORD							dwTotalCount	=	0;

      if  (  (  pTmpBuf  =  pBuf  )  !=  NULL  )  {
  		  // Loop through the entries and 
  		  //  print the names of the local groups 
  		  //  to which the user belongs. 
  		  //
  		  for  (  i  =  0;  i  <  dwEntriesRead;  i  ++  )  {
                        
			   if  (  pTmpBuf  ==  NULL  )  {
              	   fprintf(stderr, "An access violation has occurred\n");
              	   break;
               }

			   traceLogA(  "Local:  -- [%S]",  pTmpBuf->lgrui0_name  );

			   if  (  pf  )  {
				   int  tmpiRet	=	pf(  p0,  p1,  pTmpBuf->lgrui0_name  );
				   if  (  tmpiRet  )  {
					   iErr  =  tmpiRet;  goto  errLabel;
				   }
			   }

			   pTmpBuf  ++  ;
			   dwTotalCount  ++  ;
         
		  }
      
	  }
      
	  // If all available entries were
      //  not enumerated, print the number actually 
      //  enumerated and the total number available.
      //
      if  (  dwEntriesRead  <  dwTotalEntries  )  fprintf(  stderr,  "\nTotal entries: %d",  dwTotalEntries  );
      
	  // Otherwise, just print the total.
      printf(  "\nEntries enumerated: %d\n",  dwTotalCount  );

   }
 
   iErr  =  0;

errLabel:

   // Free the allocated memory.
   if  (  bBufNeedFree  )  if  (  pBuf  !=  NULL  )  pDynLib->pNetApiBufferFree(  pBuf  );

   return  iErr;
}


 int  enumUsrGroups(  QY_ENV  *  pEnv,  LPCWSTR  wUsrName,  LPCWSTR  wDomainName,  PF_commonHandler  pf,  void  *  p0,  void  *  p1  )
{
   int									iErr			=	-1;
   LPGROUP_USERS_INFO_0					pBuf			=	NULL;
   DWORD								dwLevel			=	0;
   DWORD								dwPrefMaxLen	=	MAX_PREFERRED_LENGTH;
   DWORD								dwEntriesRead	=	0;
   DWORD								dwTotalEntries	=	0;
   NET_API_STATUS						nStatus;
   QWM_DYN_LIB					*		pDynLib			=	(  QWM_DYN_LIB  *  )pEnv->pDynLibs;
   BOOL									bBufNeedFree	=	FALSE;

   if  (  !pDynLib  ||  !pDynLib->pNetUserGetGroups  ||  !pDynLib->pNetApiBufferFree  )  goto  errLabel;

   // Call the NetUserGetGroups function, specifying level 0.
   nStatus  =  pDynLib->pNetUserGetGroups(  wDomainName,
											wUsrName,
                        					dwLevel,
                        					(LPBYTE*)&pBuf,
                        					dwPrefMaxLen,
                        					&dwEntriesRead,
                        					&dwTotalEntries  );
   // If the call succeeds,
   if  (  nStatus != NERR_Success  &&  nStatus  !=  ERROR_MORE_DATA  )  goto  errLabel;
   bBufNeedFree  =  TRUE;

   {
      LPGROUP_USERS_INFO_0	pTmpBuf;
      DWORD					i;
      DWORD					dwTotalCount = 0;

      if  (  (  pTmpBuf  =  pBuf  )  !=  NULL  )  {
          // Loop through the entries; 
          //  print the name of the global groups 
          //  to which the user belongs.
          //
          for  (  i  =  0;  i  <  dwEntriesRead;  i  ++  )  {
            
               if  (  pTmpBuf  ==  NULL  )  {
               	   fprintf(stderr, "An access violation has occurred\n");
               	   break;
               }

               traceLogA(  "Global:  -- [%S]",  pTmpBuf->grui0_name  );

			   if  (  pf  )  {
				   int  tmpiRet	=	pf(  p0,  p1,  pTmpBuf->grui0_name  );
				   if  (  tmpiRet  )  {
					   iErr  =  tmpiRet;  goto  errLabel;
				   }
			   }

               pTmpBuf  ++  ;
               dwTotalCount  ++  ;
           }
      }

      // If all available entries were
      //  not enumerated, print the number actually 
      //  enumerated and the total number available.
      //
      if  (  dwEntriesRead  <  dwTotalEntries  )  fprintf(stderr, "\nTotal entries: %d", dwTotalEntries);
      
	  // Otherwise, just print the total.
      printf(  "\nEntries enumerated: %d\n",  dwTotalCount  );
   }
  
   iErr  =  0;

errLabel:

   if  (  bBufNeedFree  )  if  (  pBuf  !=  NULL  )  pDynLib->pNetApiBufferFree(  pBuf  );

   return  iErr;
}


 QY_DMITEM  CONST_myAdminGrpTable[]  =
{
	{	0,	L"Administrators",		},		//  local 
	//
	{	0,	L"Enterprise Admins",	},		//  global
	{	0,	L"Schema Admins",		},
	{	0,	L"Domain Admins",		},
	{	-1,		},
};

 int  tmpHandler_bUsrInAdminGrp(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 WCHAR		*	pGrpName  =  (  WCHAR  *  )p2;
	 QY_DMITEM	*	pItem	=	0;

	 for  (  pItem  =  CONST_myAdminGrpTable;  pItem->type  !=  -1;  pItem  ++  )  {
		  if  (  !wcsicmp(  pGrpName,  (  LPCWSTR  )pItem->des  )  )  return  1;
	 }

	 return  0;
}

 BOOL  bUsrInAdminGrp(  QY_ENV  *  pEnv,  LPCWSTR  wUsrName,  LPCWSTR  wDomainName  )
{
	 if  (  enumUsrLocalGroups(  pEnv,  wUsrName,  wDomainName,  tmpHandler_bUsrInAdminGrp,  0,  0  )  >  0  )  return  TRUE;
	 if  (  enumUsrGroups(  pEnv,  wUsrName,  wDomainName,  tmpHandler_bUsrInAdminGrp,  0,  0  )  >  0  )  return  TRUE;

	 return  FALSE;
}



 ////////////////////////////////
 /*
 //  2007/12/06, 上面的判断是否在adminGrp中的做法，对在域中成员（非域控制器）PC上的域用户登陆时不生效。
     有下面的做法可以生效，
	 但是因为实际使用中，域的adminGrp的使用是由网管做的，实际中并不需要管理。所以还是保留上述做法。

 QY_DMITEM  CONST_myAdminGrpTable_a[]  =
{
	{	0,	(  char  *  )"Administrators",		},		//  local 
	//
	{	0,	(  char  *  )"Enterprise Admins",	},		//  global
	{	0,	(  char  *  )"Schema Admins",		},
	{	0,	(  char  *  )"Domain Admins",		},
	{	-1,		},
};



 //  2007/12/03, 上面用NetUserGetGroups来枚举组的方式，在普通域成员PC上运行都失败。所以改用原来的方案。
  //  只不过，因为vista下的administrator的用户进程有 administrators的deny标志。所以，不要去判断这个deny标志。
 
 BOOL  bUsrInAdminGrp(  QY_ENV  *  pEnv,  LPCWSTR  wUsrName,  LPCWSTR  wDomainName  )
{
	 BOOL							bRet				=	FALSE;
	 DWORD							dwSize				=	0;
	 TOKEN_GROUPS				*	pSidInfo			=	NULL;
	 DWORD							i;
	 HANDLE							hToken				=	NULL;
	 unsigned  char					ucbTokenOpen		=	FALSE;
	 TOKEN_INFORMATION_CLASS		tic					=	TokenGroups;  
	 int							iType;
	 QWM_DYN_LIB				*	pDynLib				=	(  QWM_DYN_LIB  *  )pEnv->pDynLib;
	 
	 //  2007/12/04
	 if  (  !pDynLib  ||  !pDynLib->pOpenProcessToken  ||  !pDynLib->pGetTokenInformation  )  goto  errLabel;

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
		 goto  errLabel;
	 }
	 for  (  i  =  0;  i  <  pSidInfo->GroupCount;  i  ++  )  {
		  SID_NAME_USE	sidType;
		  char			nameBuf[256];
		  char			domainBuf[256];
		  DWORD			dwNameSize			=  sizeof(  nameBuf  );
		  DWORD			dwDomainSize		=  sizeof(  domainBuf  );
		  DWORD			dwAttr  =  0;

		  if  (  !pDynLib->pLookupAccountSid(  NULL,  pSidInfo->Groups[i].Sid,	nameBuf,  &dwNameSize,  domainBuf,  &dwDomainSize,  &sidType  )  )  {
			  if  (  GetLastError(  )  ==  ERROR_NONE_MAPPED  )  wsprintf(  nameBuf,  "NONE_MAPPED"  );
			  else  traceLogA(  "LoopupAccountSid Error %u\n",  GetLastError(  )  );
			  continue;
		  }
		
		  dwAttr  =  pSidInfo->Groups[i].Attributes;

		  traceLogA(  "%12s \\%-20s \t%s\n",  domainBuf,  nameBuf,  (  dwAttr  &  SE_GROUP_USE_FOR_DENY_ONLY  )  ?  "[DENY]"  :  ""  );
		  
		  
		  //  if  (  !(  dwAttr  &  SE_GROUP_USE_FOR_DENY_ONLY  )  )  {
		  // 	  iType  =  qyGetTypeByDes(  CONST_qyGrpTable,  nameBuf  );
		  //	  if  (  iType  !=  -1  )  flg  |=  1  <<  iType;
		  //  }
		  

		  iType  =  qyGetTypeByDes(  CONST_myAdminGrpTable_a,  nameBuf  );
		  if  (  iType  !=  -1  )  {
			  traceLogA(  "\tbelongs to admin grp"  );
			  bRet  =  TRUE;  goto  errLabel;
		  }

	 }

errLabel:

	 if  (  pSidInfo  )  delete  []  (  LPBYTE  )pSidInfo;
	 if  (  ucbTokenOpen  &&  hToken  )  CloseHandle(  hToken  );

	 return  bRet;

}


  */


