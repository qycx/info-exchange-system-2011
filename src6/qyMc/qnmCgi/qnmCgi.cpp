// qnmCgi.cpp : Defines the entry point for the console application.
//
#include	"stdafx.h"
#include	"qnmCgi.h"

void  *  myGetCgiHints(  );
void  exitQnmCgi(  QNM_CGI  *  pCgi  );

#ifdef  __DEBUG__
 int  testCgiFunc(  void  *  pCgi  );
#endif


int  getPostData(  char  *  szBuffer,  unsigned  int  size  );
int  printPostData(  char  *  szBuffer  );

int  printSearchPage(  );

											//  为了方便，先将符号设为与qwmSvr相同，2005/02/02, 原来是用CONST_qyCfgSym_qnmProxy
char  gQyCfgs[CONST_qySize_cfgs  +  1]  =  CONST_qyCfgSym
										CONST_qyCfgName_cntIp			"="		DEFAULT_qwmServIp
										" "
										CONST_qyCfgName_cntPort			"="		"8768"
										" "
										CONST_qyCfgName_systemId		"="		"3"
										" "
										CONST_qyCfgName_bGetPcAsset		"="		"1"
										" "
										CONST_qyCfgName_bNetMc2			"="		"1"
										"\0";





 extern  "C"  int  qnmParseSpecialOpt(  QNM_SPECIAL_OPT  *  pSpecialCfg  )
{
	 int				iErr		=	-1;
	 char			*	p			=	NULL;
	 char				buf[1024];
	 char			*	pQyCfgs		=	gQyCfgs;
	 unsigned  int		size		=	sizeof(  gQyCfgs  );

	 traceLogA(  "qnmParseSpecialCfgs: pQyCfgs is [%s]",  pQyCfgs  );

	 if  (  size  )  {
		 if  (  strlen(  pQyCfgs  )  >=  (  int  )size   )  return  -1;
	 }

	 safeStrnCpy(  DEFAULT_qyCfgVal_cntIp,  pSpecialCfg->cnt.ip,  mycountof(  pSpecialCfg->cnt.ip  )  );
	 pSpecialCfg->cnt.port  =  DEFAULT_qyCfgVal_cntPort;
	 pSpecialCfg->iSystemId_wanted  =  DEFAULT_qyCfgVal_systemId;
	 
	 //  2006/07/01, 取管理端地址
	 if  (  parseQwmDynCfg(  pQyCfgs,  size,  &pSpecialCfg->dynCfg  )  )  goto  errLabel;


	 //  从孵化配置里选取一个有效的IP。因为cgi运行频繁，所以，不用动态域名。
	 if  (  bIpValid(  pSpecialCfg->dynCfg.cnt.cntIp  )  )  safeStrnCpy(  pSpecialCfg->dynCfg.cnt.cntIp,  pSpecialCfg->cnt.ip,  sizeof(  pSpecialCfg->cnt.ip  )  );
	 else  {
		   int  i;
		   for  (  i  =  0;  i  <  mycountof(  pSpecialCfg->dynCfg.cnt.cntAddrs  );  i  ++  )  {
			    if  (  bIpValid(  pSpecialCfg->dynCfg.cnt.cntAddrs[i]  )  )  {
				    safeStrnCpy(  pSpecialCfg->dynCfg.cnt.cntAddrs[i],  pSpecialCfg->cnt.ip,  sizeof(  pSpecialCfg->cnt.ip  )  );
				    break;			   
				}
		   }
		   if  (  i  ==  mycountof(  pSpecialCfg->dynCfg.cnt.cntAddrs  )  )  {
			   printf(  "Failed: server ip is not valid\n"  );  goto  errLabel;
		   }
	 }
	 //
	 pSpecialCfg->cnt.port  =  pSpecialCfg->dynCfg.cnt.usCntPort;


	 p  =  qwmGetCfg(  pQyCfgs,  CONST_qyCfgName_systemId,  buf,  sizeof(  buf  )  );
	 if  (  p  )  {
		 pSpecialCfg->iSystemId_wanted  =  (  unsigned  short  )atol(  buf  );
	 }

	 p  =  qwmGetCfg(  pQyCfgs,  CONST_qyCfgName_bGetPcAsset,  buf,  sizeof(  buf  )  );
	 if  (  p  )  {
		 pSpecialCfg->ucbGetPcAsset  =  (  atol(  buf  )  ?  TRUE  :  FALSE  );
	 }

	 p  =  qwmGetCfg(  pQyCfgs,  CONST_qyCfgName_bNetMc2,  buf,  sizeof(  buf  )  );
	 if  (  p  )  {
		 pSpecialCfg->ucbNetMc2  =  (  atol(  buf  )  ?  TRUE  :  FALSE  );
	 }

	 iErr  =  0;	  

errLabel:

	 return  iErr;

}

 int  initQnmCgi(  QNM_CGI  *  pCgi  )
{
	 int	iErr	=	-1;

	 if  (  qnmParseSpecialOpt(  &pCgi->cfg.opt  )  )  goto  errLabel;

	 pCgi->iCustomId  =  qyGetCustomId(  );
	 //
	 pCgi->iSystemId  =  qyGetSystemId(  );
	 pCgi->iServiceId  =  CONST_qyServiceId_qwm;
	 safeStrnCpy(  qnmVerStr(  pCgi->iServiceId  ),  pCgi->ver,  sizeof(  pCgi->ver  )  );
	 
	 pCgi->pHints  =  myGetCgiHints(  );

	 if  (  qyInitSnmp(  &ghDll_InetMib1  )  )  goto  errLabel;
	 if  (  qyTcpStart(  )  )  goto  errLabel;
	 pCgi->ucbTcpStarted  =  TRUE;

	 OutputDebugString(  _T(  "2008/06/22, 暂时在cgi中不采用加密方法.因为cgi需要快速运行.如用类ssl方法,会导致过大的消耗.\n"  )  );
	 if  (  0  )  {		//  2008/06/22, 暂时在cgi中不采用加密方法.因为cgi需要快速运行.如用类ssl方法,会导致过大的消耗.
		 if  (  initQnmEnc(  &pCgi->encCtx,  NULL,  NULL,  &pCgi->commEncCtx  )  )  goto  errLabel;
		 pCgi->ulbEncInited  =  TRUE;
	 }

	 setSockTimeout(  &pCgi->cfg.to  );

	 getQwmMacs(  &pCgi->env,  &pCgi->macsInfo  );	//  2004/05/20增加了取mac的补充手段

	 #ifdef  __DEBUG__							//  2007/12/10, 这里在出release版应该关上。
			 //  pCgi->ucbShowDebugHint  =  TRUE;
	 #endif


	 iErr  =  0;
errLabel:

	 if  (  iErr  )  exitQnmCgi(  pCgi  );

	 return  iErr;
}

 void  exitQnmCgi(  QNM_CGI  *  pCgi  )
{
		
	 if  (  pCgi->ulbEncInited  )  exitQnmEnc(  &pCgi->encCtx,  NULL,  NULL,  &pCgi->commEncCtx  );

	 if  (  pCgi->ucbTcpStarted  )  {
		 qyTcpEnd(  );  pCgi->ucbTcpStarted  =  FALSE;
	 }

	 if  (  ghDll_InetMib1  )  qyExitSnmp(  &ghDll_InetMib1  );

	 return;
}

#include "windows.h"
//  #include "strsafe.h"
#include "wininet.h"
#include <stdlib.h>

	 TCHAR* schemeType[] =
{
  TEXT( "[Partial URL]" ),                //  0
  TEXT( "[Unknown scheme]" ),             //  1
  TEXT( "[Default scheme]" ),             //  2
  TEXT( "FTP" ),                          //  3
  TEXT( "Gopher" ),                       //  4
  TEXT( "HTTP" ),                         //  5
  TEXT( "HTTPS" ),                        //  6
  TEXT( "File" ),                         //  7
  TEXT( "News" ),                         //  8
  TEXT( "MailTo" ),                       //  9
  TEXT( "Socks" ),                        // 10
  TEXT( "JavaScript" ),                   // 11
  TEXT( "VBScript" )                      // 12
};

#define  CRACKER_SCHEME_TYPE_ARRAY_SIZE			13
#define  CRACKER_BUFFER_SIZE					MAX_PATH



 int  crackerUrl(  LPCSTR  URL_buffer,  char  *  extraInfoBuf,  unsigned  int  *  puiBufSize  )
{
   int						iErr								=	-1;
   //  int						i, j;
   TCHAR				*	failedFunctionName					=	_T(  ""  );
   //
   URL_COMPONENTSA			URLparts;
   //  TCHAR					urlPathBuf[2048]					=	_T(  ""  );
   
   if  (  !URL_buffer  )  return  -1;
   if  (  !extraInfoBuf  )  return  -1;
   if  (  !puiBufSize  ||  !puiBufSize[0]  )  return  -1;


   memset(  &URLparts,  0,  sizeof(  URLparts  )  );
   URLparts.dwStructSize = sizeof( URLparts );

   // The following elements determine which components are displayed
   /*
   URLparts.dwSchemeLength    = 1;
   URLparts.dwHostNameLength  = 1;
   URLparts.dwUserNameLength  = 1;
   URLparts.dwPasswordLength  = 1;
   URLparts.dwUrlPathLength   = mycountof(  urlPathBuf  );
   URLparts.dwExtraInfoLength = mycountof(  extraInfoBuf  );

   URLparts.lpszScheme     = NULL;
   URLparts.lpszHostName   = NULL;
   URLparts.lpszUserName   = NULL;
   URLparts.lpszPassword   = NULL;
   URLparts.lpszUrlPath    = urlPathBuf;
   URLparts.lpszExtraInfo  = extraInfoBuf;
   */

   URLparts.dwExtraInfoLength = puiBufSize[0];
   URLparts.lpszExtraInfo  = extraInfoBuf;


   /*
   if( FAILED( StringCchLength( URL_buffer, CRACKER_BUFFER_SIZE, 
                                (size_t*) &i ) ) )
   {
       failedFunctionName = TEXT( "StringCchLength" );
       goto CrackerError_01;
   }
   */

   if( !InternetCrackUrlA(  URL_buffer,  strlen( URL_buffer ), ICU_DECODE,  &URLparts ) )  {
       failedFunctionName = TEXT( "InternetCrackUrl" );
	   traceLogA(  "InternetCrackUrlA failed"  );
       goto errLabel;
   }


   //  这里是utf8的格式, 如果需要打印, 就要做一个转换.
   //  myUtf82Str(  extraInfoBuf,  mycountof(  extraInfoBuf  )  );

   failedFunctionName = TEXT( "listURLpart" );

   /*
   i = URLparts.nScheme + 2;
   if( ( i >= 0 ) && ( i < CRACKER_SCHEME_TYPE_ARRAY_SIZE ) )
   {
       StringCchLength( schemeType[i], CRACKER_BUFFER_SIZE, (size_t*) &j );
   }
   */

   //  traceLogA(  "urlPath is [%s]",  URLparts.lpszUrlPath  );

   traceLogA(  "extraInfo is [%s], dwExtraInfoLength is %d",  URLparts.lpszExtraInfo,  URLparts.dwExtraInfoLength  );
   
   if  (  URLparts.dwExtraInfoLength  >=  puiBufSize[0]  )  {
	   traceLogA(  "extraInfoBuf is too small"  );
	   goto  errLabel;
   }
   extraInfoBuf[URLparts.dwExtraInfoLength]  =  0;

   iErr  =  0;

errLabel:

// For sample source code of the InternetErrorOut( ) function 
// referenced below, see the "Handling Errors" 
// topic under "Using WinInet"
   
   if  (  iErr  )  traceLogA(  "error:  %d, %s",  GetLastError( ), failedFunctionName );
   if  (  !iErr  )  {
	   traceLogA(  "crackerUrl: orgStr is [%s]",  URL_buffer  );
	   traceLogA(  "crackerUrl: newStr is [%s]",  extraInfoBuf  );
	   
	   *puiBufSize  =  URLparts.dwExtraInfoLength;   
   }


   return  iErr;

}


 //  如果有&, 则ppNext指向&后的一个字符。同时，buf将存入&前的内容。
 //  如果没有&, 则ppNext[0]为NULL，同时，buf存入所有的内容.
 //
 int  myGetAPhrase(  char  *  p0,  char  *  buf,  unsigned  int  uiBufSize,  char  **  ppNext  )
{
	int			iErr	=	-1;
	char	*	p1	=	NULL;

	if  (  !p0  ||  !ppNext  )  return  -1;
	
	if  (  (  p1  =  strchr(  p0,  '&'  )  )  )  {
        safeStrnCpy(  p0,  buf,  min(  (  unsigned  int  )(  p1  -  p0  +  1  ),  uiBufSize  )  );
		}
	else  {
		  safeStrnCpy(  p0,  buf,  uiBufSize  );
	}
		
	iErr  =  0;
//  errLabel:
	if  (  !iErr  )  {
		if  (  p1  )  ppNext[0]  =  p1  +  1;
		else  ppNext[0]  =  NULL;
	}

	return  iErr;
}

 
 int  procPhrase(  char  *  buf,  WWWQM_COMM_BUF  *  pCommBuf,  unsigned  short  *  pusCmd  )
{
	int					iErr	=	-1;
	char			*	p;
	char			*	pScheme							=	"http://1.1.1.1/#";		
	unsigned  int		uiSchemeSize					=	strlen(  pScheme  );
	char				szBuf[100  *  1024]				=	"";
	char				extraInfoBuf[100  *  1024]		=	"";
	unsigned  int		uiExtraInfoBufSize				=	0;
	//
	char			*	pFieldName;
	unsigned  int		uiFieldNameLen;
	char			*	pVal;
	unsigned  int		uiValLen;
	//
	unsigned  short		usCmd							=	0;


	if  (  !buf  ||  !pCommBuf  ||  !pusCmd  )  return  -1;

	p  =  strchr(  buf,  '='  );
	if  (  !p  )  goto  errLabel;
	
	//
	pFieldName  =  "a=";		//  意思是app=
	uiFieldNameLen  =  strlen(  pFieldName  );
	if  (  !strnicmp(  buf,  pFieldName,  uiFieldNameLen  )  )  {			   
		pVal  =  "qm";  uiValLen  =  strlen(  pVal  );			   
		if  (  strnicmp(  buf  +  uiFieldNameLen,  pVal,  uiValLen  )  )  {
			traceLogA(  "这里只支持a=qm...的情况"  );  goto  errLabel;
		}
		//
		iErr  =  0;  goto  errLabel;
	}

	//
	pFieldName  =  "s=";			//  means sessId=
	uiFieldNameLen  =  strlen(  pFieldName  );
	if  (  !strnicmp(  buf,  pFieldName,  uiFieldNameLen  )  )  {

		_snprintf(  szBuf,  mycountof(  szBuf  ),  "%s%s",  pScheme,  (  buf  +  uiFieldNameLen  )  );
		uiExtraInfoBufSize  =  mycountof(  extraInfoBuf  );
		//  if  (  crackerUrl(  CStringA(  pScheme  )  +  (  buf  +  uiFieldNameLen  ),  extraInfoBuf,  &uiExtraInfoBufSize  )  )  goto  errLabel;
		if  (  crackerUrl(  szBuf,  extraInfoBuf,  &uiExtraInfoBufSize  )  )  goto  errLabel;
		p  =  extraInfoBuf;
		if  (  p[0]  ==  '#'  )  p  ++  ;

		if  (  sscanf(  p,  "%x",  &pCommBuf->authInfo.uiLogonId  )  !=  1  )  pCommBuf->authInfo.uiLogonId  =  0;

		iErr  =  0;  goto  errLabel;
	}

	//
	pFieldName  =  "v=";			//  means ver=
	uiFieldNameLen  =  strlen(  pFieldName  );
	if  (  !strnicmp(  buf,  pFieldName,  uiFieldNameLen  )  )  {

		_snprintf(  szBuf,  mycountof(  szBuf  ),  "%s%s",  pScheme,  (  buf  +  uiFieldNameLen  )  );
		uiExtraInfoBufSize  =  mycountof(  extraInfoBuf  );
		//  if  (  crackerUrl(  CStringA(  pScheme  )  +  (  buf  +  uiFieldNameLen  ),  extraInfoBuf,  &uiExtraInfoBufSize  )  )  goto  errLabel;
		if  (  crackerUrl(  szBuf,  extraInfoBuf,  &uiExtraInfoBufSize  )  )  goto  errLabel;
		p  =  extraInfoBuf;
		if  (  p[0]  ==  '#'  )  p  ++  ;

		safeStrnCpy(  p,  pCommBuf->authInfo.ver,  mycountof(  pCommBuf->authInfo.ver  )  );
		traceLogA(  "ver is [%s]",  pCommBuf->authInfo.ver  );

		iErr  =  0;  goto  errLabel;
	}



	/*
	//
	pFieldName  =  "usr=";
	uiFieldNameLen  =  strlen(  pFieldName  );
	//
	if  (  !strnicmp(  buf,  pFieldName,  uiFieldNameLen  )  )  {

		uiExtraInfoBufSize  =  mycountof(  extraInfoBuf  );
		if  (  crackerUrl(  CStringA(  pScheme  )  +  (  buf  +  uiFieldNameLen  ),  extraInfoBuf,  &uiExtraInfoBufSize  )  )  goto  errLabel;
		p  =  extraInfoBuf;
		if  (  p[0]  ==  '#'  )  p  ++  ;

		myUtf82WChar(  p,  pCommBuf->authInfo.messengerName,  mycountof(  pCommBuf->authInfo.messengerName  )  );
		iErr  =  0;  goto  errLabel;
	}
	
	//
	pFieldName  =  "pwd=";
	uiFieldNameLen  =  strlen(  pFieldName  );
	if  (  !strnicmp(  buf,  pFieldName,  uiFieldNameLen  )  )  {

		uiExtraInfoBufSize  =  mycountof(  extraInfoBuf  );
		if  (  crackerUrl(  CStringA(  pScheme  )  +  (  buf  +  uiFieldNameLen  ),  extraInfoBuf,  &uiExtraInfoBufSize  )  )  goto  errLabel;
		p  =  extraInfoBuf;
		if  (  p[0]  ==  '#'  )  p  ++  ;

		myUtf82WChar(  p,  pCommBuf->authInfo.messengerPasswd,  mycountof(  pCommBuf->authInfo.messengerPasswd  )  );
		iErr  =  0;  goto  errLabel;

	}
	*/

	//
	pFieldName  =  "rS=";
	uiFieldNameLen  =  strlen(  pFieldName  );
	if  (  !strnicmp(  buf,  pFieldName,  uiFieldNameLen  )  )  {

		_snprintf(  szBuf,  mycountof(  szBuf  ),  "%s%s",  pScheme,  (  buf  +  uiFieldNameLen  )  );
		uiExtraInfoBufSize  =  mycountof(  extraInfoBuf  );
		//  if  (  crackerUrl(  CStringA(  pScheme  )  +  (  buf  +  uiFieldNameLen  ),  extraInfoBuf,  &uiExtraInfoBufSize  )  )  goto  errLabel;
		if  (  crackerUrl(  szBuf,  extraInfoBuf,  &uiExtraInfoBufSize  )  )  goto  errLabel;
		p  =  extraInfoBuf;
		if  (  p[0]  ==  '#'  )  p  ++  ;

		myUtf82WChar(  p,  pCommBuf->authInfo.wRndName_serv,  mycountof(  pCommBuf->authInfo.wRndName_serv  )  );
		iErr  =  0;  goto  errLabel;
	}

	//
	pFieldName  =  "rC=";
	uiFieldNameLen  =  strlen(  pFieldName  );
	if  (  !strnicmp(  buf,  pFieldName,  uiFieldNameLen  )  )  {

		_snprintf(  szBuf,  mycountof(  szBuf  ),  "%s%s",  pScheme,  (  buf  +  uiFieldNameLen  )  );
		uiExtraInfoBufSize  =  mycountof(  extraInfoBuf  );
		//  if  (  crackerUrl(  CStringA(  pScheme  )  +  (  buf  +  uiFieldNameLen  ),  extraInfoBuf,  &uiExtraInfoBufSize  )  )  goto  errLabel;
		if  (  crackerUrl(  szBuf,  extraInfoBuf,  &uiExtraInfoBufSize  )  )  goto  errLabel;
		p  =  extraInfoBuf;
		if  (  p[0]  ==  '#'  )  p  ++  ;

		if  (  sscanf(  p,  "%x",  &pCommBuf->authInfo.uiRnd_cli  )  !=  1  )  pCommBuf->authInfo.uiRnd_cli  =  0;

		iErr  =  0;  goto  errLabel;
	}

	//
	pFieldName  =  "c=";
	uiFieldNameLen  =  strlen(  pFieldName  );
	if  (  !strnicmp(  buf,  pFieldName,  uiFieldNameLen  )  )  {

		_snprintf(  szBuf,  mycountof(  szBuf  ),  "%s%s",  pScheme,  (  buf  +  uiFieldNameLen  )  );
		uiExtraInfoBufSize  =  mycountof(  extraInfoBuf  );
		//  if  (  crackerUrl(  CStringA(  pScheme  )  +  (  buf  +  uiFieldNameLen  ),  extraInfoBuf,  &uiExtraInfoBufSize  )  )  goto  errLabel;
		if  (  crackerUrl(  szBuf,  extraInfoBuf,  &uiExtraInfoBufSize  )  )  goto  errLabel;
		p  =  extraInfoBuf;
		if  (  p[0]  ==  '#'  )  p  ++  ;

		if  (  !stricmp(  p,  "rcv"  ) )  usCmd  =  CONST_qyCmd_lastMsgInSession;		//  取所有的数据
		else  if  (  !stricmp(  p,  "tlk"  )  )  usCmd  =  CONST_qyCmd_talkTo;	
		else  if  (  !stricmp(  p,  "getU"  )  )  usCmd  =  CONST_qyCmd_refreshImObjListReq;	
		else  if  (  !stricmp(  p,  "refrshU"  )  )  usCmd  =  CONST_qyCmd_refreshRecentFriendsReq;
		else  {
			  traceLogA(  "Unknown cmd: [%s]",  p  );		
			  goto  errLabel;
		}

		traceLogA(  "c=[%s]",  p  );		

		iErr  =  0;  goto  errLabel;
	}

	//
	pFieldName  =  "msg=";
	uiFieldNameLen  =  strlen(  pFieldName  );
	if  (  !strnicmp(  buf,  pFieldName,  uiFieldNameLen  )  )  {

		_snprintf(  szBuf,  mycountof(  szBuf  ),  "%s%s",  pScheme,  (  buf  +  uiFieldNameLen  )  );
		uiExtraInfoBufSize  =  mycountof(  extraInfoBuf  );
		//  if  (  crackerUrl(  CStringA(  pScheme  )  +  (  buf  +  uiFieldNameLen  ),  extraInfoBuf,  &uiExtraInfoBufSize  )  )  goto  errLabel;
		if  (  crackerUrl(  szBuf,  extraInfoBuf,  &uiExtraInfoBufSize  )  )  goto  errLabel;
		p  =  extraInfoBuf;
		if  (  p[0]  ==  '#'  )  p  ++  ;

		pCommBuf->cmdParam.u.uiType  =  CONST_imCommType_htmlContent;
		myUtf82WChar(  p,  pCommBuf->cmdParam.u.html.wBuf,  mycountof(  pCommBuf->cmdParam.u.html.wBuf  )  );

		traceLogA(  "htmlContent: %S",  pCommBuf->cmdParam.u.html.wBuf  );

		iErr  =  0;  goto  errLabel;
	}

	//
	pFieldName  =  "frm=";
	uiFieldNameLen  =  strlen(  pFieldName  );
	if  (  !strnicmp(  buf,  pFieldName,  uiFieldNameLen  )  )  {

		_snprintf(  szBuf,  mycountof(  szBuf  ),  "%s%s",  pScheme,  (  buf  +  uiFieldNameLen  )  );
		uiExtraInfoBufSize  =  mycountof(  extraInfoBuf  );
		//  if  (  crackerUrl(  CStringA(  pScheme  )  +  (  buf  +  uiFieldNameLen  ),  extraInfoBuf,  &uiExtraInfoBufSize  )  )  goto  errLabel;
		if  (  crackerUrl(  szBuf,  extraInfoBuf,  &uiExtraInfoBufSize  )  )  goto  errLabel;
		p  =  extraInfoBuf;
		if  (  p[0]  ==  '#'  )  p  ++  ;

		pCommBuf->cmdParam.idInfo_from.ui64Id  =  atol(  p  );

		traceLogA(  "idInfo_from: %I64u",  pCommBuf->cmdParam.idInfo_from.ui64Id  );

		iErr  =  0;  goto  errLabel;
	}

	//
	pFieldName  =  "to=";
	uiFieldNameLen  =  strlen(  pFieldName  );
	if  (  !strnicmp(  buf,  pFieldName,  uiFieldNameLen  )  )  {

		_snprintf(  szBuf,  mycountof(  szBuf  ),  "%s%s",  pScheme,  (  buf  +  uiFieldNameLen  )  );
		uiExtraInfoBufSize  =  mycountof(  extraInfoBuf  );
		//  if  (  crackerUrl(  CStringA(  pScheme  )  +  (  buf  +  uiFieldNameLen  ),  extraInfoBuf,  &uiExtraInfoBufSize  )  )  goto  errLabel;
		if  (  crackerUrl(  szBuf,  extraInfoBuf,  &uiExtraInfoBufSize  )  )  goto  errLabel;
		p  =  extraInfoBuf;
		if  (  p[0]  ==  '#'  )  p  ++  ;

		pCommBuf->cmdParam.idInfo_to.ui64Id  =  atol(  p  );

		traceLogA(  "idInfo_to: %I64u",  pCommBuf->cmdParam.idInfo_to.ui64Id  );

		iErr  =  0;  goto  errLabel;
	}

	//  tranNo
	pFieldName  =  "tNo=";			
	uiFieldNameLen  =  strlen(  pFieldName  );
	if  (  !strnicmp(  buf,  pFieldName,  uiFieldNameLen  )  )  {

		_snprintf(  szBuf,  mycountof(  szBuf  ),  "%s%s",  pScheme,  (  buf  +  uiFieldNameLen  )  );
		uiExtraInfoBufSize  =  mycountof(  extraInfoBuf  );
		//  if  (  crackerUrl(  CStringA(  pScheme  )  +  (  buf  +  uiFieldNameLen  ),  extraInfoBuf,  &uiExtraInfoBufSize  )  )  goto  errLabel;
		if  (  crackerUrl(  szBuf,  extraInfoBuf,  &uiExtraInfoBufSize  )  )  goto  errLabel;
		p  =  extraInfoBuf;
		if  (  p[0]  ==  '#'  )  p  ++  ;

		pCommBuf->cmdParam.uiTranNo  =  atol(  p  );

		traceLogA(  "tranNo: %d",  pCommBuf->cmdParam.uiTranNo  );

		iErr  =  0;  goto  errLabel;
	}



   iErr  =  0;
errLabel:
   if  (  !iErr  )  {
	   if  (  pusCmd  )  *pusCmd  =  usCmd;
   }
   return  iErr;
			   
}

//  当遇到一个c=时，就要退出。其中usCmd保存起来
 int  parsePostData(  char  *  szBuffer,  WWWQM_COMM_BUF  *  pCommBuf,  unsigned  short  *  pusCmd_parsed,  char  **  pp  )
{
	int						iErr		=	-1;
	char					buf[2048]	=	"";
	char				*	p0			=	szBuffer;
	long					lVer;
	unsigned  short			usCmd	=	0;
	
	if  (  !pusCmd_parsed  ||  !pp  )  return  -1;
			   
	for  (  ;  p0;  )  {
		 if  (  myGetAPhrase(  p0,  buf,  mycountof(  buf  ),  &p0  )  )  break;
		 //  traceLogA(  "buf is [%s],  p0 is [%s]",  buf,  (  p0  ?  p0  :  "NULL"  )  );
		 //
		 if  (  procPhrase(  buf,  pCommBuf,  &usCmd  )  )  goto  errLabel;
		 if  (  usCmd  )  break;
	}

	
	lVer  =  atol(  pCommBuf->authInfo.ver  );			   
	if  (  lVer  )  {				   //  在版本号有的情况下，一般是在第一次通信时，可以判断一下版本号是否兼容。
		if  (  lVer  /  100  >  atol(  qnmVerStr(  CONST_qyServiceId_is  )  )  /  100  )  {
			traceLogA(  "cgi 不能支持比cgi更高版本的脚本"  );  goto  errLabel;
		}
		traceLogA(  "ver is [%s]",  pCommBuf->authInfo.ver  );
	}
	
	iErr  =  0;
errLabel:
	if  (  !iErr  )  {
		if  (  pusCmd_parsed  )  *pusCmd_parsed  =  usCmd;
		if  (  pp  )  *pp  =  p0;
	}
	return  iErr;
}


 //   int main(int argc, char* argv[])
 int _tmain(int argc, _TCHAR* argv[])
{
	 int			iErr						=	-1;
	 QNM_CGI		gQnmCgi;
	 BOOL			bQnmCgiInited				=	FALSE;
	 char		*	pRequestMethod				=	NULL;
	 char		*	p							=	NULL;
	 void		*	pDynLib						=	NULL;
	 BOOL			bDynLibInited				=	FALSE;

	 //  setDebugLogFileModuleName(  );
	 //  setErrHintWndTitle(  CONST_qnmStatusWndTitle  );
	 	
	 if  (  initDynLib(  (  void  **  )&pDynLib  )  )  {
		traceLogA(  "InitDynamicLibraries(  ) failed."  );
		goto  errLabel;
	 }
	 bDynLibInited  =  TRUE;

	 memset(  &gQnmCgi,  0,  sizeof(  gQnmCgi  )  );

	 getQyEnv(  pDynLib,  &gQnmCgi.env  );
	 //  gQnmCgi.env.pDynLibs  =  pDynLib;

	 if  (  initQnmCgi(  &gQnmCgi  )  )  goto  errLabel;
	 bQnmCgiInited  =  TRUE;


	 gQnmCgi.uiLangId_browser  =  CONST_langId_US;
	 if  (  (  p  =  getenv(  "HTTP_ACCEPT_LANGUAGE"  )  )  )  {
		 //  if  (  !strcmpi(  p,  "zh-cn"  )  )  gQnmCgi.uiLangId_browser  =  CONST_langId_PRC;
		 //
		 unsigned  int		uiLangId_browser				=		0;
		 QY_IDCITEM		*	pItem							=		NULL;
		 //
		 pItem  =  (  QY_IDCITEM  *  )qyGetDmItemByDes(  (  QY_DMITEM  *  )CONST_langStrTable,  CString(  p  ),  sizeof(  CONST_langStrTable[0]    )  );
		 if  (  pItem  )  gQnmCgi.uiLangId_browser  =  pItem->idc;
	 }
	 gQnmCgi.isIE  =  TRUE;
	 if  (  (  p  =  getenv(  "HTTP_USER_AGENT"  )  )  )  {		//  2007/12/17
		 CString	str(  p  );
		 traceLogA(  "HTTP_USER_AGENT is [%S]",  str  );
		 if  (  str.Find(  _T(  "MSIE"  )  )  <  0  )  gQnmCgi.isIE  =  FALSE;	
	 }
	 traceLogA(  "isIE is %d",  gQnmCgi.isIE  );
	 //
	 if  (  (  p  =  getenv(  "REMOTE_ADDR"  )  )  &&  bIpValid(  p  )  )  {
		 traceLogA(  "remoteIp is %s",  p  );
		 safeStrnCpy(  p,  gQnmCgi.remoteIp,  sizeof(  gQnmCgi.remoteIp  )  );
	 }
	 

#ifdef  __DEBUG__
		testCgiFunc(  &gQnmCgi  );
#endif

	 printVars(  FALSE  );

	 //
	 pRequestMethod  =  getenv(  "REQUEST_METHOD"  );
	 if  (  !pRequestMethod  )  {
		 traceLogA(  "requestMethod is null"  );  
		 printf(  "server ip is [%s], port is %d\n",  gQnmCgi.cfg.opt.cnt.ip,  gQnmCgi.cfg.opt.cnt.port  );
		 goto  errLabel;
	 }
	 _snprintf(  gQnmCgi.requestMethod,  sizeof(  gQnmCgi.requestMethod  ),  "%s",  pRequestMethod  );
	 if  (  !strcmpi(  gQnmCgi.requestMethod,  "get"  )  )  {
		 //  outputLogin(  &gQnmCgi  );  
		 //  procGet(  &gQnmCgi  );
		 
		 goto  errLabel;	//  原来的补丁查询已经不用．这里暂时关闭，　２００７／１１／１５

		 }
	 else  if  (  !strcmpi(  gQnmCgi.requestMethod,  "post"  )  )  {
		
		 	   char					szBuffer[100  *  1024]			=	"";

			   traceLogA(  "method is post"  );
		 		
			   if  (  getPostData(  szBuffer  +  strlen(  szBuffer  ),  mycountof(  szBuffer  )  -  strlen(  szBuffer  )  )  <  0  )  goto  errLabel;
			   traceLogA(  "szBuffer is [%s]",  szBuffer  );
			   
			   //  printVars(  FALSE  );

			   procPost(  &gQnmCgi,  szBuffer  );

			   iErr  =  0;  goto  errLabel;
			   

			   /*
			   printMimeHeader(  );
			   printHtmlHeader(  NULL,  "测试post命令"  );

			   //  printVars(  );				//  仅用来显示环境变量和参数。
		 
			   //
			   //  printPostData(  szBuffer  );

			   printSearchPage(  );

			   printHtmlTrailer(  );
			   */

		 }
	 else  {
		   traceLogA(  "得到了意想不到的requestMethod: %s",  gQnmCgi.requestMethod  );
		   goto  errLabel;
	 }

	 iErr  =  0;

errLabel:
	 
	 if  (  bQnmCgiInited  )  exitQnmCgi(  &gQnmCgi  );

	 if  (  bDynLibInited  )  exitDynLib(  &pDynLib  );	//  2007/01/25

	 return  0;
}



 void  printOut(  char  *varVal  )  
{
	 char  *  pEquals  =  NULL;
	 int	  i;

	 pEquals  =  strchr(  varVal,  '='  );
	 if  (  pEquals  )  {
 		 traceLogA(  "before pEquals is %s",  pEquals  );
		 *pEquals  ++  = '\0';
 		 traceLogA(  "after pEquals is %s",  pEquals  );
		 urlDecode(  varVal  );

		 i = 0;
		 while  (  varVal[i]  )  {
			    varVal[i]  =  toupper(  varVal[i]  );  i++;
		 }

		 traceLogA(  "the last  pEquals is %s",  pEquals  );
		 urlDecode(  pEquals  );

		 printf(  "<li>%s = %s\n",  varVal,  pEquals  );
	 }
}


 //  返回读到的字节数
 int  getPostData(  char  *  szBuffer,  unsigned  int  size  )
{
	 int				iErr			=	-1;
	 char			*	pContentLength  =  NULL;
	 int				len;
	 int				i				=  0;
	 int				x				=  0;

	 if  (  !szBuffer  ||  !size  )  return  -1;

	 pContentLength  =  getenv(  "CONTENT_LENGTH"  );
	 if  (  pContentLength  )  len  =  atoi(  pContentLength  );
	 else  len  =  0; 

	 if  (  len  <  0  )  len  =  0;
	 if  (  (  unsigned  int  )len  >  size  -  1  )  len  =  size  -  1;

	 i  =  0;
	 while  (  i  <  len  )  {
		    x  =  fgetc(  stdin  );
			if  (  x  ==  EOF  )  break;
			szBuffer[i ++ ]  =  x;
	 }

	 szBuffer[i]  =  '\0';

	 traceLogA(  "len  is  %d,  szBuffer  is  %s",   len,  szBuffer  );

	 return  i;
}

 int  printPostData(  char  *  szBuffer  )
{
	 char  *  pToken  =  NULL;
	 printf(  "<b>POST  Data </b>\n"  );
	 printf(  "<ul>\n"  );

	 pToken  =  strtok(  szBuffer,  "&"  );
	 while  (  pToken  )  {
			traceLogA(  "提交的信息为:   %s\n",  pToken  );
		    printOut(  pToken  );
			pToken  =  strtok(  NULL,  "&"  );
	 }
	 
	 printf(  "</ul>\n"  );
	 return  0;
}

 int  printSearchPage(  )
{
	 printf(  "<b>请输入你需要的查询信息:</b>\n"  );
	 printf(
		   "<ul>\n"
		   "<A HREF = \"pcList.html\">计算机查询</A><P>\n"
		   "<A HREF = \"pcEventList.html\">计算机事件查询</A><P>\n"
		   "</ul>\n"  
		   );
	 return  0;
}
