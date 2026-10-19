
#include  <windows.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <process.h>
#include  <tchar.h>

#include  "awpm.h"

typedef  struct  __qwpm_item_t  {
				 TCHAR			*	listItemName;
				 TCHAR			*	listItemData;
				 TCHAR			*	rootKey;
}		 QWPM_ITEM;

 extern  BOOL  gbMis;	//  2007/06/13

 QWPM_ITEM	*	gQwpmTable		=	NULL;

 QWPM_ITEM		gQwpmTable_netMc2[]	=	
{
	{	_T(  CONST_regValName_qwpmS10  ),	_T(  CONST_regValData_qwpmS10  ),	_T(  CONST_qyRootKey_qnmScheduler  ),	},
	{	_T(  CONST_regValName_qwpmS11  ),	_T(  CONST_regValData_qwpmS11  ),	_T(  CONST_qyRootKey_qmd_netMc  ),			},
	{	_T(  CONST_regValName_qwpmS12  ),	_T(  CONST_regValData_qwpmS12  ),	_T(  CONST_qyRootKey_qnmResp  ),		},
	{	NULL,																					},
};

 QWPM_ITEM		gQwpmTable_netMc[]	=	
{
	{	_T(  CONST_regValName_qwpmS10  ),	_T(  CONST_regValData_qwpmS10  ),	_T(  CONST_qyRootKey_qnmScheduler  ),	},
	{	_T(  CONST_regValName_qwpmS11  ),	_T(  CONST_regValData_qwpmS11  ),	_T(  CONST_qyRootKey_qmd_netMc  ),			},
	{	_T(  CONST_regValName_qwpmS12  ),	_T(  CONST_regValData_qwpmS12  ),	_T(  CONST_qyRootKey_qnmResp  ),		},
	//  {	CONST_regValName_qwpmS13,	CONST_regValData_qwpmS13,	CONST_qyRootKey_httpSvr,		},
	{	NULL,																					},
};

 QWPM_ITEM		gQwpmTable_netMc_secChk[]	=	
{
	{	_T(  CONST_regValName_qwpmS10  ),	_T(  CONST_regValData_qwpmS10  ),	_T(  CONST_qyRootKey_qnmScheduler  ),	},
	{	_T(  CONST_regValName_qwpmS11  ),	_T(  CONST_regValData_qwpmS11  ),	_T(  CONST_qyRootKey_qmd_netMc  ),			},
	{	_T(  CONST_regValName_qwpmS14  ),	_T(  CONST_regValData_qwpmS14  ),	_T(  ROOT_AWM_INTRA_MON_KEY  ),			},
	{	NULL,																					},
};


 QWPM_ITEM		gQwpmTable_default[]	=	
{
	{	_T(  CONST_regValName_qwpmS10  ),	_T(  CONST_regValData_qwpmS10  ),	_T(  CONST_qyRootKey_qnmScheduler  ),		},
	{	_T(  CONST_regValName_qwpmS11  ),	_T(  CONST_regValData_qwpmS11  ),	_T(  CONST_qyRootKey_qmd_netMc  ),			},
	{	_T(  CONST_regValName_qwpmS12  ),	_T(  CONST_regValData_qwpmS12  ),	_T(  CONST_qyRootKey_qnmResp  ),			},
	{	_T(  CONST_regValName_qwpmS14  ),	_T(  CONST_regValData_qwpmS14  ),	_T(  ROOT_AWM_INTRA_MON_KEY  ),				},
	{	_T(  CONST_regValName_qwpmS15  ),	_T(  CONST_regValData_qwpmS15  ),	_T(  ROOT_AWM_INTERMON_KEY  ),				},	//  2004/06/18将interMon放入此处，
	{	_T(  CONST_regValName_qwpmS16  ),	_T(  CONST_regValData_qwpmS16  ),	_T(  ROOT_AWM_INTER_MON_TOOL_KEY  ),		},	//  2004/06/18加
	//
	{	NULL,																					},
};

 QWPM_ITEM		gQwpmTable_mis[]	=	
{
	//
	{	_T(  CONST_regValName_qwpmS17  ),	_T(  CONST_regValData_qwpmS17  ),	_T(  CONST_qyRootKey_qmd_mis  ),			},	//  2007/06/13加
	{	_T(  CONST_regValName_qwpmS18  ),	_T(  CONST_regValData_qwpmS18  ),	_T(  CONST_qyRootKey_qnmScheduler_mis  ),	},	//  2007/06/13加
	//
	{	NULL,																					},
};


 extern  "C"  int  initAwpm(  AWPM  *  pAwpm  )
{
	int					iErr		=	-1;
	long				lRet;
	HKEY				hKey;
	BOOL				bKeyOpen	=	FALSE;
	DWORD				cb, type;
	TCHAR				buf[256];
	QWPM_ITEM	*		pItem		=	NULL;


	debugLog( "initAwpm( ) enters." );

	pAwpm->iSystemId  =  qyGetSystemId(  );
	pAwpm->iCustomId  =  qyGetCustomId(  );
	/*
	switch  (  pAwpm->iSystemId  )  {
			case  CONST_qySystemId_nms:  
				  if  (  pAwpm->iCustomId  ==  CONST_qyCustomId_secChk  )
					  gQwpmTable  =  gQwpmTable_netMc_secChk;
				  else  
					  gQwpmTable  =  gQwpmTable_netMc;
				  break;
			case  CONST_qySystemId_netMc2:
				  gQwpmTable  =  gQwpmTable_netMc2;
				  break;
			default:
					gQwpmTable  =  gQwpmTable_default;
					break;
	}
	*/
	gQwpmTable  =  gbMis  ?  gQwpmTable_mis  :  gQwpmTable_default;		//  2003/12/01修改，以后对管理service将没有对systemId的区分


	lRet  =  RegOpenKey(  HKEY_LOCAL_MACHINE,  _T(  CONST_qwpmKey_list  ),  &hKey  );
	if  (  lRet  !=  ERROR_SUCCESS  )  goto  errLabel;
	bKeyOpen  =  TRUE;

	pAwpm->totalServices = 0;
	// 0项对应退出事件，故不作使用。
	memset( &pAwpm->aSS[0], 0, sizeof( pAwpm->aSS[0] ) );
	
	pAwpm->totalServices  ++  ;

	for  (  pItem  =  gQwpmTable;  pItem->listItemName;  pItem  ++  )  {
	
		 cb = sizeof( buf );
		 if  (  RegQueryValueEx( hKey, pItem->listItemName, 0, &type, ( unsigned char * )buf, ( unsigned long * )&cb ) == ERROR_SUCCESS ) {
			 if  (  cb  <  1  )  buf[0]	=	0;
			 else  buf[cb - 1] = 0;
		
			 traceLogA(  "name is %s, data is %s",  pItem->listItemName,  pItem->listItemData  );

			 if  (  !_tcsicmp(  buf,  pItem->listItemData  )  )  {
				 if  (  !getServiceCfg(  pItem->rootKey, &pAwpm->aSS[pAwpm->totalServices]  )  )  {
					 pAwpm->totalServices  ++  ;
				 }
			 }
		 }
	}
	
	iErr  =  0;

errLabel:

	if  (  bKeyOpen  )  RegCloseKey(  hKey  );

	debugLog( "initAwpm( ) leaves." );

	return iErr;

}


 extern  "C"  int  getServiceCfg(  LPCTSTR  rootServiceKey,  AWPM_SUB_SERVICE  *  pASS  )
{
	 int	iErr	=	-1;

	 if  (  qyGetRegCfg(  rootServiceKey,  _T(  CONST_regValName_installDir  ),  (  char  *  )pASS->path,  sizeof(  pASS->path  )  )
		&&  qyGetRegCfg(  rootServiceKey,  _T(  CONST_regValName_installPath  ),  (  char  *  )pASS->path,  sizeof(  pASS->path  )  )  )
	{
		goto  errLabel;
	}

	if  (  qyGetRegCfg(  rootServiceKey,  _T(  CONST_regValName_appName  ),  (  char  *  )pASS->appName,  sizeof(  pASS->appName  )  )  )  goto  errLabel;

	//  2007/06/13
	if  (  qyGetRegCfg(  rootServiceKey,  _T(  CONST_regValName_cmdLine  ),  (  char  *  )pASS->cmdLine,  sizeof(  pASS->cmdLine  )  )  )  pASS->cmdLine[0]  =  0;


	iErr  =  0;

errLabel:

	return  iErr;
}

/*
 extern  "C"  int  getServiceCfg(  LPCTSTR  rootServiceKey,  AWPM_SUB_SERVICE  *  pASS  )
{
	int		iErr		=  -1;
	long	lRet;
	HKEY	hKey;
	BOOL	bKeyOpen	=  FALSE;
	DWORD	cb, type;
	char	buf[256];

	lRet  =  RegOpenKey(  HKEY_LOCAL_MACHINE,  rootServiceKey,  &hKey  );
	if  (  lRet  !=  ERROR_SUCCESS  )  goto  errLabel;
	bKeyOpen  =  TRUE;
	
	cb  =  sizeof(  buf  );
	if  (  RegQueryValueEx(  hKey,  CONST_regValName_installDir,  0,  &type,  (  unsigned  char  *  )buf,  (  unsigned  long  *  )&cb  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	if  (  cb  <  1  )  buf[0]  =  0;
	else  buf[cb  -  1]  =  0;

	if  (  cb  >=  sizeof(  pASS->path  )  )  goto  errLabel;
	strcpy(  pASS->path,  buf  );

	cb  =  sizeof(  buf  );
	if  (  RegQueryValueEx(  hKey,  CONST_regValName_appName,  0,  &type,  (  unsigned  char  *  )buf,  (  unsigned  long  *  )&cb  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	if  (  cb  <  1  )  buf[0]  =  0;
	else  buf[cb  -  1]  =  0;
	
	if  (  cb  >=  sizeof(  pASS->appName  )  )  goto  errLabel;
	strcpy(  pASS->appName,  buf );
	
	iErr  =  0;

errLabel:

	if  (  bKeyOpen  )  RegCloseKey(  hKey  );

	traceLogA(  "getServiceCfg: rootKey is %s, installDir is %s, appName is %s, %s",  rootServiceKey,  pASS->path,  pASS->appName,  iErr  ?  "失败"  :  "成功"  );

	return  iErr;

}
*/


 extern "C" void exitAwpm( AWPM *pAwpm )
{
	return;
}


 extern "C" int tryToStopSubServices( AWPM *p )
{
	int		iErr	=	-1;
	int		i;
	DWORD	dwRet;

	debugLog( "tryToStopSubServices( ) enters." );
	if ( setAwpmQuitKey( ) ) goto errLabel;
	for ( i = 1; i < p->totalServices; i ++ ) {
		if ( p->hEvent[i] ) {
			//  ::WaitForSingleObject( p->hEvent[i], 2000 );						//  2003 0324 ，将2000改为INFINITE，以使退出完整
			dwRet  =  ::WaitForSingleObject( p->hEvent[i], INFINITE );
			if  (  dwRet  !=  WAIT_TIMEOUT  &&  dwRet  !=  WAIT_FAILED  )  {		//  
				CloseHandle( p->hEvent[i] ); p->hEvent[i] = NULL;
			}
		}
	}
	iErr = 0;

errLabel:

	debugLog( "tryToStopSubServices( ) leaves." );
	
	return iErr;

}


 extern  "C"  int  setAwpmQuitKey(  )
{
	 QWPM_ITEM	*		pItem		=	NULL;

	 for  (  pItem  =  gQwpmTable;  pItem->listItemName;  pItem  ++  )  {
		  setQuitKey(  pItem->rootKey  );
	 }
	 
	 return  0;

}

  extern  "C"  int  clearAwpmQuitKey(  )
{
	 QWPM_ITEM	*		pItem		=	NULL;

	 for  (  pItem  =  gQwpmTable;  pItem->listItemName;  pItem  ++  )  {
		  clearQuitKey(  pItem->rootKey  );
	 }
	
	 return  0;
}


 extern "C" int setQuitKey( TCHAR *rootKey )
{
	int iRet = -1;
	BOOL bKeyOpen = FALSE;
	HKEY hKey;
	int rc = -1;
	TCHAR buf[256];
	
	_sntprintf( buf, mycountof(  buf  ),  _T(  "%d"  ), ASR_QUIT_VAL );

	if  (  (  rc  =  RegOpenKey( HKEY_LOCAL_MACHINE, rootKey, &hKey ) ) != ERROR_SUCCESS )  goto errLabel;
	bKeyOpen = TRUE;

	if ( RegSetValueEx( hKey, _T(  ASR_QUIT_KEY  ), 0, REG_SZ, ( const unsigned char * )buf, (  lstrlen( buf )  +  1  )  *  sizeof(  TCHAR  )  ) != ERROR_SUCCESS ) {
		debugLog( "cfgAsrWMon( ): RegSetValueEx( ) failed." );
		goto errLabel;
	}

	iRet = 0;

errLabel:

	if ( bKeyOpen ) RegCloseKey( hKey );

	return iRet;

}



 extern "C" int clearQuitKey( TCHAR *rootKey )
{
	int iRet = -1;
	BOOL bKeyOpen = FALSE;
	HKEY hKey;
	int rc = -1;
	TCHAR buf[2]  =  _T(  ""  );

	//  buf[0] = ~ASR_QUIT_VAL;
	//  buf[1] = 0;
	
	if  (  (  rc  =  RegOpenKey( HKEY_LOCAL_MACHINE, rootKey, &hKey ) ) != ERROR_SUCCESS )  goto errLabel;
	bKeyOpen = TRUE;
	
	if ( RegSetValueEx( hKey, _T(  ASR_QUIT_KEY  ), 0, REG_SZ, ( const unsigned char * )buf, (  lstrlen( buf )  +  1  )  *  sizeof(  TCHAR  )  ) != ERROR_SUCCESS ) {
		debugLog( "cfgAsrWMon( ): RegSetValueEx( ) failed." );
		goto errLabel;
	}

	iRet = 0;

errLabel:

	if ( bKeyOpen ) RegCloseKey( hKey );

	return iRet;

}
	



 extern "C" int tryToMgrSubServices( AWPM *p,  TCHAR  *  hint,  unsigned  int  cnt  )
{
	int						iErr		= -1;
	int						i			= 0;
	HANDLE					hProcess	= NULL;
	PROCESS_INFORMATION		pI;
	STARTUPINFO				s;
	TCHAR					fullPath[2048];
	TCHAR					tHint[256]	=	_T(  ""  );

	clearAwpmQuitKey( );
	for ( i = 1; i < p->totalServices; i ++ ) {
		if ( !p->hEvent[i] ) {
			memset( &pI, 0, sizeof( pI ) );
			memset( &s, 0, sizeof( s ) );
			s.cb=sizeof(STARTUPINFO);
			s.dwFlags=STARTF_FORCEOFFFEEDBACK;
	
			debugLog( "Now call asrGetFullPath( )." );
			debugLog( "path is [%s], appName is [%s]", p->aSS[i].path, p->aSS[i].appName );
			//  if ( !tTrim( p->aSS[i].path ) ) goto errLabel;
			tTrim( p->aSS[i].path );
			if  (  !p->aSS[i].path ) goto errLabel;
			if ( p->aSS[i].path[lstrlen( p->aSS[i].path ) - 1] == '\\' ) {
				_sntprintf( fullPath,   mycountof(  fullPath  ),  _T(  "%sbin\\%s"  ), p->aSS[i].path, p->aSS[i].appName );
				}
			else
				_sntprintf( fullPath,  mycountof(  fullPath  ),  _T(  "%s\\bin\\%s"  ), p->aSS[i].path, p->aSS[i].appName );
			
			if  (  qyQuoteFileName(  fullPath,  mycountof(  fullPath  )  )  )  goto  errLabel;

			_sntprintf(  fullPath,  mycountof(  fullPath  ),  _T(  "%s %s"  ),  fullPath,  p->aSS[i].cmdLine  );

			debugLog( "try to start [%s]", fullPath );
			if ( !CreateProcess( NULL, 
								fullPath, 
								NULL,
								NULL,
								FALSE,
								0,
								NULL,
								NULL,
								&s,
								&pI	) )
			{
				DisplayLastError( "awpm" );
				debugLog( "CreateProcess( ) failed." );
				_sntprintf(  tHint,  mycountof(  tHint  ),  _T(  "CreateProcess( ) failed, %s"  ),  fullPath  );
				goto errLabel;
			}
			debugLog( "CreateProcess( ) succeeded." );
			p->hEvent[i] = pI.hProcess ;
		}
	}
	
	iErr = 0;

errLabel:
	
	if  (  hint  )  lstrcpyn(  hint,  tHint,  cnt  );

	return iErr;

}

