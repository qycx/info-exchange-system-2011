// qyCfgUsrTool.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include	<windows.H>
#include <lm.h>


#define		CONST_toolName		"qyCfgUsrTool.exe"

 void  usage(  int  argc,  char  *  argv[]  )
{
	 printf(  "Usage: %s	/set \"scriptPath\"\n",  CONST_toolName  );
	 printf(  "				--  set scriptPath for every user whose scriptPath is not set, but will ask for 'y' before really set it.\n"  );
	 printf(  "			/set -a \"scriptPath\"\n"  );
	 printf(  "				--  autimatically set scriptPath for every user who was not set any sciptPath.\n"  );
	 printf(  "			/clear \"scriptPath\"\n"  );
	 printf(  "				--  clear sciptPath for every user whose scipt path is matched.\n"  );
	 printf(  "			/clear -a \"scriptPath\"\n"  );
	 printf(  "				--  automatically clear sciptPath for every user whose scipt path is matched.\n"  );
	 printf(  "			/print\n"  );
	 printf(  "				--  printf all user scipt path\n"  );
	 printf(  "Version: 1.00.\n"  );	
	 printf(  "MSN:		qycx123@hotmail.com\n"  );
	 printf(  "Written by BeiJing Qycx Corp. ( www.qycx.com ).\n"  );
 
}


#define		CONST_myCmd_set			1
#define		CONST_myCmd_setAuto		2
#define		CONST_myCmd_clear		3
#define		CONST_myCmd_clearAuto	4
#define		CONST_myCmd_print		5

typedef  struct  __qyCfgUsrStruct_t	{
				 unsigned  int		uiCmd;				 
				 char				scriptPath[512];
}		 QY_CFGUSR_STRUCT;

QY_CFGUSR_STRUCT	gTool;

int setUsrScriptPath( WCHAR *wScriptPath, WCHAR *wUsrName );
void setAllUsrsScriptPath( const wchar_t *server, QY_CFGUSR_STRUCT  *  pTool );

int main(int argc, char* argv[])
{
	int			iErr	=	-1;

	memset(  &gTool,  0,  sizeof(  gTool  )  );

	if  (  argc  <  2  )  goto  errLabel;
	if  (  argc  ==  2  )  {
		if  (  !strcmpi(  "/print",  argv[1]  )  )  gTool.uiCmd  =  CONST_myCmd_print;
		else  goto  errLabel;
		}
	else  if  (  !strcmpi(  "/set",  argv[1]  )  )  {
			  if  (  argc <  3  )  goto  errLabel;
			  else  if  (  argc  ==  3  )  {  gTool.uiCmd  =  CONST_myCmd_set;
											_snprintf(  gTool.scriptPath,  sizeof(  gTool.scriptPath  ),  "%s",  argv[2]  );
											}
			  else  if  (  !strcmpi(  "-a",  argv[2]  )  )  {  gTool.uiCmd  =  CONST_myCmd_setAuto;
															   _snprintf(  gTool.scriptPath,  sizeof(  gTool.scriptPath  ),  "%s",  argv[3]  );
															}
			  else  goto  errLabel;
			}
	else  if  (  !strcmpi(  "/clear",  argv[1]  )  )  {
			  if  (  argc  <  3  )  goto  errLabel;
			  else  if  (  argc  ==  3  )  {  gTool.uiCmd  =  CONST_myCmd_clear;
											  _snprintf(  gTool.scriptPath,  sizeof(  gTool.scriptPath  ),  "%s",  argv[2]  );
											}
			  else  if  (  !strcmpi(  "-a",  argv[2]  )  )  {  gTool.uiCmd  =  CONST_myCmd_clearAuto;
															   _snprintf(  gTool.scriptPath,  sizeof(  gTool.scriptPath  ),  "%s",  argv[3]  );
															}
			  else  goto  errLabel;
				}
	else  goto  errLabel;
	
	if  (  gTool.uiCmd  !=  CONST_myCmd_print  &&  !gTool.scriptPath[0]  )  goto  errLabel;

	setAllUsrsScriptPath(  NULL,  &gTool  );

	iErr  =  0;
errLabel:
	if  (  iErr  )  usage(  argc,  argv  );
	return 0;
}

 void setAllUsrsScriptPath( const wchar_t *server, QY_CFGUSR_STRUCT  *  pTool )
{
	USER_INFO_1 *buf, *cur;
	DWORD read, totalremaining, resumeh, rc, i;
	WCHAR wScriptPath[MAX_PATH + 1];
	int iRet;
	char *scriptPath	=  pTool->scriptPath;
	char	myBuf[1024];

	resumeh = 0;

	iRet = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, scriptPath, -1, 
				wScriptPath, MAX_PATH );
	if ( !iRet ) goto errLabel;
	wScriptPath[iRet] = 0;

	if  (  pTool->uiCmd  ==  CONST_myCmd_print  )  printf(  "User		Status			ScriptPath		Passwd age\n"  );
					
	do {
		buf = NULL;
		rc = NetUserEnum( server, 1, 0, (BYTE **) &buf, 1024, &read, &totalremaining, &resumeh );
		if ( rc != ERROR_MORE_DATA && rc != ERROR_SUCCESS )
			break;

		//  printf( "\ngot %lu entries out of %lu\n", read, totalremaining );
		for ( i = 0, cur = buf; i < read; ++ i, ++ cur ) {
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

			if ( cur->usri1_flags & UF_NORMAL_ACCOUNT ) {
				//  if ( wcscmp( cur->usri1_script_path, wScriptPath ) )  setUsrScriptPath( wScriptPath, cur->usri1_name );
				if  (  pTool->uiCmd  ==  CONST_myCmd_print  )  {
					printf(  "%S		%s		%S		%2dDays %2dHours\n",  cur->usri1_name,  (  (  cur->usri1_flags  &  UF_ACCOUNTDISABLE  )  ?  " Disabled"  :  ""  ),  cur->usri1_script_path,  cur->usri1_password_age  /  (  24  *  3600  ),  (  cur->usri1_password_age  %  (  24  *  3600  )  )  /  3600  );
					}
				else  if  (  pTool->uiCmd  ==  CONST_myCmd_set  ||  pTool->uiCmd  ==  CONST_myCmd_setAuto  )  {
					if  (  cur->usri1_script_path[0]  )  {
						if  (  wcscmp(  cur->usri1_script_path,  wScriptPath  )  )  printf(  "%S will not be set, Current sciprtPath is %S\n",  cur->usri1_name,  cur->usri1_script_path  );
						else  printf(  "%S is ok\n",  cur->usri1_name  );
						}
					else  {
						  if  (  pTool->uiCmd  !=  CONST_myCmd_setAuto  )  {
							  printf(  "Are you sure to set %S's scriptPath, 'y' or 'n'\n",  cur->usri1_name  );
						  	  if  (  !fgets(  myBuf,  sizeof(  myBuf  ),  stdin  )  )  goto  errLabel;
							  if  (  myBuf[0]  !=  'y'  )  continue;
						  }
						  if  (  setUsrScriptPath( wScriptPath, cur->usri1_name )  )  {
							  printf(  "Can't set %S's scirptPath, failed\n",  cur->usri1_name  );  goto  errLabel;
						  }
						  printf(  "%S is set\n",  cur->usri1_name  );
						  continue;
					}
					}
				else  if  (  pTool->uiCmd  ==  CONST_myCmd_clear  ||  pTool->uiCmd  ==  CONST_myCmd_clearAuto  )  {
					      if  (  !cur->usri1_script_path[0]  )  {  
							  printf(  "%S has no scriptPath\n",  cur->usri1_name  );
							  continue;
						  }
						  if  (  wcscmp(  cur->usri1_script_path,  wScriptPath  )  )  {
							  printf(  "%S has scriptPath %S, will not be cleared\n",  cur->usri1_name,  cur->usri1_script_path  );
							  continue;
						  }
						  if  (  pTool->uiCmd  !=  CONST_myCmd_clearAuto  )  {
							  printf(  "Are you sure to clear %S's scriptPath, 'y' or 'n'\n",  cur->usri1_name  );
							  if  (  !fgets(  myBuf,  sizeof(  myBuf  ),  stdin  )  )  goto  errLabel;
							  if  (  myBuf[0]  !=  'y'  )  continue;
						  }
						  if  (  setUsrScriptPath( L"", cur->usri1_name )  )  {
							  printf(  "Can't clear %S's scirptPath, failed\n",  cur->usri1_name  );  goto  errLabel;
						  }
						  printf(  "%S's scriptPath is cleared\n",  cur->usri1_name  );
						  continue;						  	
				}
			}
		}

		if ( buf != NULL )
			NetApiBufferFree( buf );

	} while ( rc == ERROR_MORE_DATA );

	//  if ( rc != ERROR_SUCCESS )  printf( "NUE() returned %lu\n", rc );

errLabel:
	return;

}


 int setUsrScriptPath( WCHAR *wScriptPath, WCHAR *wUsrName )
{	 
	int iErr = -1;
	USER_INFO_1009 usriScrPath;
	NET_API_STATUS netRet;
	DWORD dwErr;
	
	if ( !wScriptPath || !wUsrName ) return -1;

	usriScrPath.usri1009_script_path  = wScriptPath;
	
	netRet = NetUserSetInfo( NULL, wUsrName,  1009, (LPBYTE)&usriScrPath, &dwErr );
	if( netRet != NERR_Success ) goto errLabel;

	iErr = 0;

errLabel:
		
	return iErr;
 
}
