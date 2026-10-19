
#include	"stdafx.h"
#include	"qnmCgi.h"

typedef  struct  __qnmCgiHints_t	{
				 char			*	pBjcx;				//  补丁查询
				 char			*	pGgxx;				//  公告信息
				 char			*	pDefaultGgxx;
				 char			*	pJsjxx;				//  计算机信息
				 char			*	pYy;				//  语言
				 char			*	pJsjm;				//  计算机名
				 char			*	pCzxt;				//  操作系统
				 char			*	pServicePack;		//  ServicePack
				 char			*	pLastTime;			//  最近补丁检查时间
				 char			*	pCxjg;				//  查询结果
				 char			*	pHavebeenupdated;
				 char			*	pNeedToUpdate;		//
				 char			*	pBd;				//  补丁
				 char			*	pBm;				//  别名
				 char			*	pMs;				//  描述
				 char			*	pBz;				//  备注
				 char			*	pXz;				//  下载

}		 QNM_CGI_HINTS;

 QNM_CGI_HINTS	gQnmCgiHints;

 void  *  myGetCgiHints(  )
{
	 return  (  void  *  )&gQnmCgiHints;
}

 int  setQnmCgiHints(  unsigned  int  uiLangId,  QNM_CGI_HINTS  *  pHints  )
{
	 if  (  !pHints  )  return  -1;

	 memset(  pHints,  0,  sizeof(  QNM_CGI_HINTS  )  );
	 if  (  uiLangId  ==  CONST_langId_PRC  )  {
		 pHints->pBjcx  =  "补丁查询:";
		 pHints->pGgxx  =  "公告信息:";
		 pHints->pDefaultGgxx  =  "欢迎查询Windows操作系统补丁信息!";
		 pHints->pJsjxx  =  "计算机信息:";
		 pHints->pYy  =  "语言";
		 pHints->pJsjm  =  "计算机名";
		 pHints->pCzxt  =  "操作系统";
		 pHints->pServicePack  =  "ServicePack";
		 pHints->pLastTime  =  "最近补丁检查时间";
		 pHints->pCxjg  =  "查询结果:";
		 pHints->pHavebeenupdated  =  "你的补丁已经更新";
		 pHints->pNeedToUpdate  =  "你需要更新下列补丁";		//
		 //
		 pHints->pBd  =  "补丁";
		 pHints->pBm  =  "别名";
		 pHints->pMs  =  "描述";
		 pHints->pBz  =  "备注";
		 pHints->pXz  =  "下载";
		}
	 else  {
			pHints->pBjcx  =  "Hotfix and service pack query";
			pHints->pGgxx  =  "Note:";
			pHints->pDefaultGgxx  =  "You are welcome to query information about windows hotfix and service pack!";
			pHints->pJsjxx  =  "Computer Information:";
			pHints->pYy  =  "Language";
			pHints->pJsjm  =  "Computer Name";
			pHints->pCzxt  =  "OS";
			pHints->pServicePack  =  "ServicePack";
			pHints->pLastTime  =  "Last check time";
			pHints->pCxjg  =  "Results:";
			pHints->pHavebeenupdated  =  "You system have been updated!";
			pHints->pNeedToUpdate  =  "You need to download the following patches";		//
			//
			pHints->pBd  =  "Patch";
			pHints->pBm  =  "Alias";
			pHints->pMs  =  "Description";
			pHints->pBz  =  "Comment";
			pHints->pXz  =  "download";
	 }
	 return  0;
}

#define		MACRO_myPtr(  p  )	(  (  p  )  ?  (  p  )  :  ""  )
 int  procGet(  void  *  pCgiParam  )
{
	 int					iErr			=	-1;
	 QNM_CGI			*	pCgi			=   (  QNM_CGI  *  )pCgiParam;
	 QNM_CGI_HINTS		*	pCgiHints		=	(  QNM_CGI_HINTS  *  )pCgi->pHints;
	 QY_COMM_SESSION		session;
	 unsigned  char			ucbSessionOpen	=	FALSE;
	 QY_SOCK				sock;
	 QY_COMM_RESP			resp;
	 char					buf[4196];
	 QWM_QUERYPCSP_REQ		queryPcSpReq;
	 QWM_QUERYPCSP_RESP		queryPcSpResp;
	 QWM_PC_SPINFO			pcSps[CONST_maxPcSps];
	 unsigned  int			len;
	 int					i;

	 traceLogA(  "procGet: enters"  );
	 clearQySock(  &sock  );
	 memset(  &session,  0,  sizeof(  session  )  );

	 if  (  qnmOpenSession(  pCgi->cfg.opt.cnt.ip,  pCgi->cfg.opt.cnt.port,  &pCgi->macsInfo,  0,  pCgi->iServiceId,  pCgi->ver,  &pCgi->commEncCtx,  &session,  &sock,  &pCgi->cfg.to,  0,  0  )  )  {
		 outputErrHint(  FALSE,  0,  "Failed",  "Can't connect to server"  );  goto  errLabel;
	 }
	 ucbSessionOpen  =  TRUE;
	 traceLogA(  "procGet: session is open"  );

	 memset(  &queryPcSpReq,  0,  sizeof(  queryPcSpReq  )  );
	 queryPcSpReq.ulQwmIp  =  inet_addr(  pCgi->remoteIp  );
	 if  (  bQyIpLocal(  queryPcSpReq.ulQwmIp  )  ||  !strcmp(  pCgi->remoteIp,  "127.0.0.1"  )  )  queryPcSpReq.ucbCgiSelf  =  TRUE;
	 len  =  qyhtonQwmQueryPcSpReq(  &queryPcSpReq  );
	 if  (  qySendReq(  &session,  &sock,  &pCgi->cfg.to,  CONST_qyCmd_queryPcSp,  (  char  *  )&queryPcSpReq,  len  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &session,  &sock,  &pCgi->cfg.to,  &resp,  (  char  *  )buf,  sizeof(  buf  )  )  )  goto  errLabel;
	 if  (  resp.head.usCode  !=  CONST_qyRc_ok  )  {
		 outputErrHint(  FALSE,  0,  "Failed to query hotfix",  buf  );  goto  errLabel;
	 }
	 memset(  &queryPcSpResp,  0,  sizeof(  queryPcSpResp  )  );
	 memcpy(  &queryPcSpResp,  buf,  min(  resp.head.len,  sizeof(  queryPcSpResp  )  )  );
	 len  =  qyntohQwmQueryPcSpResp(  &queryPcSpResp  );
	 if  (  queryPcSpResp.uiPcSpSize  !=  sizeof(  QWM_PC_SPINFO  )  ||  queryPcSpResp.uiPcSpCnt  >  sizeof(  pcSps  )  /  sizeof(  pcSps[0]  )  )  goto  errLabel;

	 memset(  pcSps,  0,  sizeof(  pcSps  )  );
	 len  =  queryPcSpResp.uiPcSpSize  *  queryPcSpResp.uiPcSpCnt;
	 if  (  queryPcSpResp.uiPcSpCnt  )  {
		 if  (  qyRecvEx(  &sock,  (  char  *  )pcSps,  len,  pCgi->cfg.to.iRead  )  )  goto  errLabel;
		 for  (  i  =  0;  i  <  (  int  )queryPcSpResp.uiPcSpCnt;  i  ++  )  qyntohQwmPcSpInfo(  &pcSps[i]  );
	 }

	 traceLogA(  "pcName is %s,  servicePack is %s",  queryPcSpResp.pcName,  queryPcSpResp.servicePack  );

	 setQnmCgiHints(  pCgi->uiLangId_browser,  pCgiHints  );

	 printMimeHeader(  );
	 printHtmlHeader(  NULL,  pCgiHints->pBjcx  );
	 //  printVars(  );				//  仅用来显示环境变量和参数。
	
	 printf(  "<b>%s</b><br>\n",  MACRO_myPtr(  pCgiHints->pGgxx  )  );
	 printf(  "&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;%s\n",  (  queryPcSpResp.hint0[0]  ?  queryPcSpResp.hint0  :  MACRO_myPtr(  pCgiHints->pDefaultGgxx  )  )  );
	 printf(  "<p>\n"  );
	 printf(  "<b>%s</b>\n",  MACRO_myPtr(  pCgiHints->pJsjxx  )  );
	 printf(  "<li>%s: %s\n",  MACRO_myPtr(  pCgiHints->pYy  ),  qyGetDesByType1(  CONST_qyLangTable_en,  queryPcSpResp.uiLangId  )  );
	 printf(  "<li>%s: %s\n",  MACRO_myPtr(  pCgiHints->pJsjm  ),  queryPcSpResp.pcName  );
	 printf(  "<li>%s: %s\n",  MACRO_myPtr(  pCgiHints->pCzxt  ),  qyGetDesByType1(  CONST_qyPlatformTable,  queryPcSpResp.iPlatformId  )  );  
	 printf(  "<li>%s: %s\n",  MACRO_myPtr(  pCgiHints->pServicePack  ),  queryPcSpResp.servicePack  );  
	 qyDisplayTime(  queryPcSpResp.lastTime,  buf,  sizeof(  buf  )  );
	 printf(  "<li>%s: %s\n",  MACRO_myPtr(  pCgiHints->pLastTime  ),  buf  );  
	 printf(  "<p>\n"  );
	 printf(  "<b>%s </b>\n",  MACRO_myPtr(  pCgiHints->pCxjg  )  );
	 trim(  queryPcSpResp.resultBuf  );
	 if  (  queryPcSpResp.resultBuf[0]  )  printf(  "%s\n",  queryPcSpResp.resultBuf  );  
	 else  if  (  !queryPcSpResp.uiPcSpCnt  )  printf(  "%s\n",  MACRO_myPtr(  pCgiHints->pHavebeenupdated  )  );
	 else  {  
		   printf(  "%s\n",  MACRO_myPtr(  pCgiHints->pNeedToUpdate  )  );
		   printf(  "<table width=100%% border style=\'border-collapse:collapse\'>\n"  );
		   printf(  "<tr>"  );
		   printf(  "<td width=9%%><center>%s</center></td>",  MACRO_myPtr(  pCgiHints->pBd  )  );
		   printf(  "<td width=9%%><center>%s</center></td>",  MACRO_myPtr(  pCgiHints->pBm  )  );
		   printf(  "<td width=65%%><center>%s</center></td>",  MACRO_myPtr(  pCgiHints->pMs  )  );
		   printf(  "<td width=7%%><center>%s</center></td>",  MACRO_myPtr(  pCgiHints->pBz  )  );
		   printf(  "</tr>\n"  );
	 	   for  (  i  =  0;  i  <  (  int  )queryPcSpResp.uiPcSpCnt;  i  ++  )  {
			    printf(  "<tr>"  );
				printf(  "<td heigth=58><a href=\"%s\">%s</a></td>",  pcSps[i].url,  pcSps[i].name  );
				printf(  "<td>%s</td>",  pcSps[i].cusName  );
				printf(  "<td>%s</td>",  pcSps[i].des0  );
				printf(  "<td><a href=\"%s\"><center>%s</center></a></td>",  pcSps[i].url,  MACRO_myPtr(  pCgiHints->pXz  )  );
				printf(  "</tr>\n"  );

			    //  printf(  "<td %s %d: %s   %s  %s  %s",  (  pcSps[i].iType  ==  CONST_spType_sp  ?  "Hotfix"  :  "ServicePack"  ),  i,  pcSps[i].name,  pcSps[i].cusName,  pcSps[i].des0,  pcSps[i].url  );
	 	   }

		   printf(  "</table>\n"  );		   
	 }

	 printHtmlTrailer(  );

	 iErr  =  0;

errLabel:

	 if  (  ucbSessionOpen  )  qnmCloseSession(  &session,  &sock,  &pCgi->cfg.to  );

	 traceLogA(  "procGet: leaves"  );
	 return  0;
}

 int  outputSth(  QNM_CGI  *  pCgi,  WWWQM_COMM_BUF  *  pCommBuf,  unsigned  short  usCmd  )
{
	 char	buf[1024]		=	"";
	 char	timeBuf[128]	=	"";

	 if  (  pCgi->ucbShowDebugHint  )  {
		 getCurTime(  timeBuf  );
		 //
		 printf(  "<hint>%s: msgr is %I64u,uiRnd_cli is %d",  timeBuf,  pCommBuf->idInfo.ui64Id,  pCommBuf->authInfo.uiRnd_cli  );
		 myWChar2Utf8(  pCommBuf->authInfo.wRndName_serv,  buf,  mycountof(  buf  )  );
		 printf(  ",rndName_serv is %s",  buf  );
		 printf(  ",uiLogonId is %d",  pCommBuf->authInfo.uiLogonId  );
		 myWChar2Utf8(  qyGetDesByType1(  CONST_qyCmdTable,  usCmd  ),  buf,  mycountof(  buf  )  );
		 printf(  ",cmd is %s",  buf  );
		 myWChar2Utf8(  pCommBuf->authResp.wRndName_serv,  buf,  mycountof(  buf  )  );
		 printf(  ",resp.rndName_serv is %s",  buf  );
		 printf(  ",resp.uiLogonId is %d",  pCommBuf->authResp.uiLogonId  );
		 printf(  "</hint>"  );
	 }
	 
	 if  (  pCommBuf->authResp.uiLogonId  )  {
		 printf(  "<s>%x</s>",  pCommBuf->authResp.uiLogonId  );
	 }
	 if  (  pCommBuf->authResp.wRndName_serv[0]  )  {
		 myWChar2Utf8(  pCommBuf->authResp.wRndName_serv,  buf,  mycountof(  buf  )  );
		 printf(  "<rS>%s</rS>",  buf  );
	 }
	 return  0;
}



CString  replaceForXml(  LPCTSTR  buf  )
{
	CString		str(  buf  ?  buf  :  _T(  ""  )  );

	//.将<换成&lt, >换成&gt
	str.Replace(  _T(  "&"  ),  _T(  "&amp;"  )  );
	str.Replace(  _T(  "<"  ),  _T(  "&lt;"  )  );
	str.Replace(  _T(  ">"  ),  _T(  "&gt;"  )  );

	return  str;	
}


 int  myRecvMsgs(  QNM_CGI  *  pCgi,  WWWQM_COMM_BUF  *  pCommBuf,  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock  )
{
	int							iErr				=	-1;
	QNM_CGI_HINTS		*		pCgiHints			=	(  QNM_CGI_HINTS  *  )pCgi->pHints;
	CQyMalloc					mallocObj;
	unsigned  int				uiBufSize			=	sizeof(  MIS_MSG_routeTalkData  );
	//  char						buf[sizeof(  MIS_MSG_routeTalkData  )]	=	"";
	char				*		pBuf				=	mallocObj.malloc(  uiBufSize  );
	if  (  !pBuf  )  return  -1;

	MSG_ROUTE					addr;
  //    int							lenInBytes;
	BOOL						bLastMsgInSession	=	FALSE;
	CString						str;


	setQnmCgiHints(  pCgi->uiLangId_browser,  pCgiHints  );
	

	//  下面为接收daemon来的msg
	QY_MSG_HEAD					msgHead;
	CQyMalloc					mallocObj_content;
	IM_CONTENTU			*		pContent	=	(  IM_CONTENTU  *  )mallocObj_content.malloc(  sizeof(  IM_CONTENTU  )  );
	if  (  !pContent  )  goto  errLabel;

	for  (  ;  !bLastMsgInSession  ;  )  {
	 
		 memset(  &msgHead,  0,  sizeof(  msgHead  )  );
		 if  (  qyRecvMsg(  pSession,  pSock,  &pCgi->cfg.to,  &msgHead,  (  char  *  )pBuf,  uiBufSize  )  )  goto  errLabel;

		 memset(  &addr,  0,  sizeof(  addr  )  );
		 memset(  pContent,  0,  sizeof(  pContent[0]  )  );
		 if  (  qyntohRouteTalkData(  msgHead.ucFlg,  pBuf,  msgHead.uiLen,  &addr,  pContent,  NULL,  0  )  <  0  )  goto  errLabel;
	 
		 switch  (  pContent->uiType  )  {
			     case  CONST_imCommType_simpleResp:
					   if  (  pContent->simpleResp.usCmd_org  ==  CONST_qyCmd_lastMsgInSession  )  {
						   traceLogA(  "这是最后一个消息"  );  
						   bLastMsgInSession  =  TRUE;
					   }
					   break;
				 case  CONST_imCommType_htmlContent:
					   traceLogA(  "html is [%S]",  pContent->html.wBuf  );
					   OutputDebugString(  pContent->html.wBuf  );  OutputDebugString(  L"\n"  );

					   #ifdef  __DEBUG__  //  这里可以造一些数据, 方便网页输出.2007/12/13, fot test
					   {
							   TCHAR	*  pT  =  _T(  "<TABLE cellSpacing=0 cols=8 cellPadding=0 width=\"100%\" border=0><TBODY><TR id=\"\" vAlign=top><TD style=\"FONT-SIZE: 11pt\">admin&nbsp;says &nbsp;(12:32:29): </TD></TR><TR id=\"\" vAlign=top><TD style=\"FONT-SIZE: 11pt\">type=2/bFol=0</TD><TD style=\"FONT-SIZE: 11pt\">0</TD><TD style=\"PADDING-RIGHT: 10px; FONT-SIZE: 11pt; LEFT: 10px; POSITION: relative\">,,,</TD></TR></TBODY></TABLE>"  );
							   //
							   //  pT  =  _T(  "<TABLE cellSpacing=0 cols=8 cellPadding=0 width=\"100%\" border=0><TBODY><TR id=\"\" vAlign=top><TD style=\"FONT-SIZE: 11pt\">admin&nbsp;says &nbsp;"  );  //  (12:32:29): </TD></TR><TR id=\"\" vAlign=top><TD style=\"FONT-SIZE: 11pt\">type=2/bFol=0</TD><TD style=\"FONT-SIZE: 11pt\">0</TD><TD style=\"PADDING-RIGHT: 10px; FONT-SIZE: 11pt; LEFT: 10px; POSITION: relative\">,,,</TD></TR></TBODY></TABLE>"  );
							   // pT  =  _T(  "<TABLE cellSpacing=0 cols=8 cellPadding=0 width=\"100%\""  );
							   //  pT  =  _T(  "<TABLE cell"  );
							   //  pT  =  _T(  "<TABLEcell"  );
							   pT  =  _T(  "<TABLE cellSpacing=0 cols=8 cellPadding=0 width=\"100%\" border=0><TBODY><TR id=\"\" vAlign=top><TD style=\"FONT-SIZE: 11pt\">admin&nbsp;says &nbsp;(16:41:51): </TD></TR><TR id=\"\" vAlign=top><TD style=\"FONT-SIZE: 11pt\">type=2/bFol=0</TD><TD style=\"FONT-SIZE: 11pt\">0</TD><TD style=\"PADDING-RIGHT: 10px; FONT-SIZE: 11pt; LEFT: 10px; POSITION: relative\">nihao</TD></TR><TR id=\"\" vAlign=top><TD style=\"FONT-SIZE: 11pt\">type=1/bFol=0</TD><TD style=\"FONT-SIZE: 11pt\">0</TD><TD style=\"FONT-SIZE: 11pt\">admin&nbsp;says &nbsp;(16:42:06): </TD></TR><TR id=\"\" vAlign=top><TD style=\"FONT-SIZE: 11pt\">type=2/bFol=0</TD><TD style=\"FONT-SIZE: 11pt\">0</TD><TD style=\"PADDING-RIGHT: 10px; FONT-SIZE: 11pt; LEFT: 10px; POSITION: relative\">请问你是哪一位</TD></TR><TR id=\"\" vAlign=top><TD style=\"FONT-SIZE: 11pt\">type=1/bFol=0</TD><TD style=\"FONT-SIZE: 11pt\">0</TD><TD style=\"FONT-SIZE: 11pt\">admin&nbsp;says &nbsp;(16:42:18): </TD>"  )
								   _T(  "</TR><TR id=\"\" vAlign=top><TD style=\"FONT-SIZE: 11pt\">type=2/bFol=0</TD><TD style=\"FONT-SIZE: 11pt\">0</TD><TD style=\"PADDING-RIGHT: 10px; FONT-SIZE: 11pt; LEFT: 10px; POSITION: relative\"><TABLE cellSpacing=0 cols=8 cellPadding=0 width=\"100%\" border=0><TBODY><TR id=\"\" vAlign=top><TD style=\"FONT-SIZE: 11pt\">1000004)&nbsp;says &nbsp;(16:41:42): </TD></TR><TR id=\"\" vAlign=top><TD style=\"FONT-SIZE: 11pt\">type=2/bFol=0</TD><TD style=\"FONT-SIZE: 11pt\">0</TD><TD style=\"PADDING-RIGHT: 10px; FONT-SIZE: 11pt; LEFT: 10px; POSITION: relative\"><SPAN style=\"FONT-SIZE: 12px; COLOR: #000000; FONT-FAMILY: Tahoma,sans-serif\">Hi</SPAN></TD></TR><TR id=\"\" vAlign=top><TD style=\"FONT-SIZE: 11pt\">type=1/bFol=0</TD></TR></TBODY></TD></TR></TBODY></TABLE></FONT></TR></TBODY></TABLE>"  );

							   //  pT  =  _T(  "<TABLE cellSpacing=0 cols=8 cellPadding=0 width=\"100%\" border=0><TBODY><TR id=\"\" vAlign=top><TD style=\"FONT-SIZE: 11pt\">admin&nbsp;says &nbsp;(16:41:51): </TD></TR><TR id=\"\" vAlign=top><TD style=\"FONT-SIZE: 11pt\">type=2/bFol=0</TD><TD style=\"FONT-SIZE: 11pt\">0</TD><TD style=\"PADDING-RIGHT: 10px; FONT-SIZE: 11pt; LEFT: 10px; POSITION: relative\">nihao</TD></TR><TR id=\"\" vAlign=top><TD style=\"FONT-SIZE: 11pt\">type=1/bFol=0</TD><TD style=\"FONT-SIZE: 11pt\">0</TD><TD style=\"FONT-SIZE: 11pt\">admin&nbsp;says &nbsp;(16:42:06): </TD></TR><TR id=\"\" vAlign=top><TD style=\"FONT-SIZE: 11pt\">type=2/bFol=0</TD><TD style=\"FONT-SIZE: 11pt\">0</TD><TD style=\"PADDING-RIGHT: 10px; FONT-SIZE: 11pt; LEFT: 10px; POSITION: relative\">请问你是哪一位</TD>"  );  //  </TR><TR id=\"\" vAlign=top><TD style=\"FONT-SIZE: 11pt\">type=1/bFol=0</TD><TD style=\"FONT-SIZE: 11pt\">0</TD><TD style=\"FONT-SIZE: 11pt\">admin&nbsp;says &nbsp;(16:42:18): </TD>"  )
							   //  pT  =  _T(  "<TABLE cellSpacing=0 cols=8 cellPadding=0 width=\"100%\" border=0><TBODY><TR id=\"\" vAlign=top><TD style=\"FONT-SIZE: 11pt\">admin&nbsp;says &nbsp;(16:41:51): </TD></TR><TR id=\"\" vAlign=top><TD style=\"FONT-SIZE: 11pt\">type=2/bFol=0</TD><TD style=\"FONT-SIZE: 11pt\">0</TD><TD style=\"PADDING-RIGHT: 10px; FONT-SIZE: 11pt; LEFT: 10px; POSITION: relative\">nihao</TD></TR><TR id=\"\" vAlign=top><TD style=\"FONT-SIZE: 11pt\">type=1/bFol=0</TD><TD style=\"FONT-SIZE: 11pt\">0</TD><TD style=\"FONT-SIZE: 11pt\">admin&nbsp;says &nbsp;(16:42:06): </TD></TR><TR id=\"\" vAlign=top><TD style=\"FONT-SIZE: 11pt\">type=2/bFol=0</TD><TD style=\"FONT-SIZE: 11pt\">0</TD>"  );  //  <TD style=\"PADDING-RIGHT: 10px; FONT-SIZE: 11pt; LEFT: 10px; POSITION: relative\">请问你是哪一位</TD>"  );  //
							   //  pT  =  _T(  "<TD style=\"PADDING-RIGHT: 10px; FONT-SIZE: 11pt; LEFT: 10px; POSITION: relative\">请问你是哪一位</TD>"  );  //
							

							   //  lstrcpyn(  content.html.wBuf,  pT,  mycountof(  content.html.wBuf  )  );
					   }
					   #endif

					   if  (  pContent->html.wBuf[0]  )  {
						   printf(  "<tlk>"  );
						   printf(  "<msgr>%I64u</msgr>",  addr.idInfo_from.ui64Id  );
						   if  (  addr.displayName_from[0]  )  {
							   str  =  replaceForXml(  addr.displayName_from  );
							   myWChar2Utf8(  str.GetBuffer(  0  ),  pBuf,  uiBufSize  );
							   printf(  "<name>%s</name>",  pBuf  );
						   }
						   //
						   str  =  replaceForXml(  pContent->html.wBuf  );
						   myWChar2Utf8(  str.GetBuffer(  0  ),  pBuf,  uiBufSize  );
						   pBuf[uiBufSize  -  1]  =  0;
						   // 转换一些字符以适应xml
						   //
						   //
						   printf(  "<str>%s</str>",  pBuf  );
						   printf(  "</tlk>"  );

					   }
					   break;
				 case  CONST_imCommType_refreshRecentFriendsResp:
					   int  i;
					   //
					   #ifdef  __DEBUG__
						       TCHAR	tBuf[1024];
	 	
							   _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d, t is %I64u, usCnt is %d"  ),   pContent->refreshRecentFriendsResp.uiType,  pContent->refreshRecentFriendsResp.tLastRefreshedTime_misServ,  pContent->refreshRecentFriendsResp.usCnt  );
							   for  (  i  =  0;  i  <  pContent->refreshRecentFriendsResp.usCnt;  i  ++  )  {
								    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, mems[%d], id %I64u, runStatus %s, ulIp %u"  ),  tBuf,  i,  pContent->refreshRecentFriendsResp.mems[i].idInfo.ui64Id,  qyGetDesByType1(  CONST_usRunningStatusTable_en,  pContent->refreshRecentFriendsResp.mems[i].usRunningStatus  ),  pContent->refreshRecentFriendsResp.mems[i].ulIp  );  
							   }
							   //  OutputDebugString(  tBuf  );
							   traceLogA(  "%S",  tBuf  );
					   #endif

					   for  (  i  =  0;  i  <  pContent->refreshRecentFriendsResp.usCnt;  i  ++  )  {
							 printf(  "<usr>"  );
							 printf(  "<msgr>%I64u</msgr>",  pContent->refreshRecentFriendsResp.mems[i].idInfo.ui64Id  );
							 printf(  "<st>%d</st>",  pContent->refreshRecentFriendsResp.mems[i].usRunningStatus  );
							 printf(  "</usr>"  );
					   }
					   bLastMsgInSession  =  TRUE;	//  这也是读完后，就停止了。事实上，因为webSending没有messenger的输出队列，所以不会有其他包。
					   break;
				 default:
					    //  traceLogA(  "这里得到了未处理的contentType %d, %S",  pContent->uiType,  qyGetDesByType1(  CONST_qyCommTypeTable, pContent->uiType  )  ); 
						break;
		 }
	}	
    
	 //  printf(  "<g>'hehe''bb'</g>"  );
	 //  printf(  "<g>vv</g>"  );

	 iErr  =  0;

errLabel:
	 return  iErr;

}




 int  getUsrList(  void  *  pCgiParam,  WWWQM_COMM_BUF  *  pCommBuf,  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock  )	
{
	 int					iErr			=	-1;
	 QNM_CGI			*	pCgi			=   (  QNM_CGI  *  )pCgiParam;
	 QNM_CGI_HINTS		*	pCgiHints		=	(  QNM_CGI_HINTS  *  )pCgi->pHints;
	 //
	 char					buf[4196];
	 int					i;
	 int					j;
	 int					len;
	 CString				str;



	 RETRIEVE_IMOBJLIST_REQ		req;
	 time_t  tStartTran;  unsigned  int	uiTranNo;  time(  &tStartTran  );  uiTranNo  =  0;
	 
	 memset(  &req,  0,  sizeof(  req  )  );
	 req.uiType  =  CONST_imCommType_retrieveWebContactListReq;
	 req.tLastRefreshedTime_contactList_misServ  =  0;	
	 req.usMaxContactUpdateInfosPerSnd  =  CONST_usMaxContactUpdateInfosPerSnd;	//  pMisCnt->cfg.usMaxContactUpdateInfosPerSnd;
	 //
	 IM_L_STREAM			stream;
	 IM_L_STREAM_nh		stream_ntoh;

	 memset(  &stream,  0,  sizeof(  stream  )  );
	 stream.uiType  =  CONST_imCommType_lStream;
	 stream.uiContentType  =  req.uiType;
	 len  =  sizeof(  stream.buf  );
	 if  (  retrieveImObjListReq2Stream(  stream.uiContentType,  &req,  stream.buf,  (  unsigned  int  *  )&len  )  )  goto  errLabel;
	 stream.ulStreamLen  =  len;
	 len  +=  offsetof(  IM_L_STREAM,  buf  ); 
	 //
	 if  (  (  len  =  qyhtonImLStream(  0,  &stream  )  )  ==  -1  )  goto  errLabel;
	 if  (  qySendMsg(  pSession,  pSock,  &pCgi->cfg.to,  0,  CONST_qyCmd_refreshImObjListReq,  tStartTran,  uiTranNo,  0,  (  char  *  )&stream,  len  )  )  {
		 traceLogA(  "qySendMsg failed"  );  goto  errLabel;
	 }

	 QY_MSG_HEAD	msgHead;
	 memset(  &msgHead,  0,  sizeof(  msgHead  )  );
	 memset(  &stream,  0,  sizeof(  stream  )  );
	 if  (  qyRecvMsg(  pSession,  pSock,  &pCgi->cfg.to,  &msgHead,  (  char  *  )&stream,  sizeof(  stream  )  )  )  goto  errLabel;

	 if  (  (  len  =  qyntohImLStream(  0,  (  char  *  )&stream,  &stream_ntoh  )  )  <  0  )  {
		 traceLogA(  "scheduler: qyntohContactUpdateInfos failed"  );
		 goto  errLabel;
	 }
	 char							*	ptr;
	 unsigned  int						size;
     RETRIEVE_WEBCONTACTLIST_RESP		resp;
	 memset(  &resp,  0,  sizeof(  resp  )  );
	 ptr  =  stream_ntoh.p;
	 size  =  stream_ntoh.ulStreamLen;

	 if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RetrieveWebContactListResp,  0,  &resp  )  )  goto  errLabel;      
	
	 //
	 if  (  outputQmBInnerHtml(  pCgi,  resp.wAdvertisement  )  )  goto  errLabel;

	 //  下面再发送最近联系人请求，实际是为了获得在线离线状态信息
	 REFRESH_RECENTFRIENDS_REQ		recentFriendsReq;

	 memset(  &recentFriendsReq,  0,  sizeof(  recentFriendsReq  )  );
	 recentFriendsReq.uiType  =  CONST_imCommType_refreshRecentFriendsReq;
	 for  (  i  =  0;  i  <  (  int  )min(  resp.usCnt,  mycountof(  recentFriendsReq.mems  )  );  i  ++  )  {
		  recentFriendsReq.mems[i].idInfo.ui64Id  =  resp.mems[i].idInfo.ui64Id;
		  recentFriendsReq.usCnt  ++  ;
	 }
	 if  (  (  len  =  qyhtonRefreshRecentFriendsReq(  0,  &recentFriendsReq  )  )  <  0  )  goto  errLabel;
	 uiTranNo  ++  ;
	 if  (  qySendMsg(  pSession,  pSock,  &pCgi->cfg.to,  0,  CONST_qyCmd_refreshRecentFriendsReq,  tStartTran,  uiTranNo,  0,  (  char  *  )&recentFriendsReq,  len  )  )  {
		 traceLogA(  "qySendMsg failed"  );  goto  errLabel;
	 }
	 
	 memset(  &msgHead,  0,  sizeof(  msgHead  )  );
	 memset(  &stream,  0,  sizeof(  stream  )  );
	 if  (  qyRecvMsg(  pSession,  pSock,  &pCgi->cfg.to,  &msgHead,  (  char  *  )&stream,  sizeof(  stream  )  )  )  goto  errLabel;
	 if  (  (  len  =  qyntohImLStream(  0,  (  char  *  )&stream,  &stream_ntoh  )  )  <  0  )  {
		 traceLogA(  "scheduler: qyntohRefreshRecentFriendsResp failed"  );
		 goto  errLabel;
	 }	 

	 REFRESH_RECENTFRIENDS_RESP		recentFriendsResp;
	 memset(  &recentFriendsResp,  0,  sizeof(  recentFriendsResp  )  );
	 ptr  =  stream_ntoh.p;
	 size  =  stream_ntoh.ulStreamLen;

	 if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RefreshRecentFriendsResp,  0,  &recentFriendsResp  )  )  goto  errLabel;      

	 #ifdef  __DEBUG__
	         TCHAR	tBuf[1024];
	 		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d, t is %I64u, usCnt is %d"  ),   recentFriendsResp.uiType,  recentFriendsResp.tLastRefreshedTime_misServ,  recentFriendsResp.usCnt  );
			 for  (  i  =  0;  i  <  recentFriendsResp.usCnt;  i  ++  )  {
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, 第%d个, id %I64u, runStatus %s, ulIp %u"  ),  tBuf,  i,  recentFriendsResp.mems[i].idInfo.ui64Id,  qyGetDesByType1(  CONST_usRunningStatusTable_en,  recentFriendsResp.mems[i].usRunningStatus  ),  recentFriendsResp.mems[i].ulIp  );  
			 }
			 OutputDebugString(  tBuf  );
	 #endif


	 setQnmCgiHints(  pCgi->uiLangId_browser,  pCgiHints  );



	 //  printf(  "<g>'hehe''bb'</g>"  );
	 //  printf(  "<g>vv</g>"  );

	 for  (  i  =  0;  i  <  resp.usCnt;  i  ++  )  {
		  printf(  "<usr>"  );
		  printf(  "<msgr>%I64u</msgr>",  resp.mems[i].idInfo.ui64Id  );
		  str  =  replaceForXml(  resp.mems[i].displayName  );
		  myWChar2Utf8(  str.GetBuffer(  0  ),  buf,  mycountof(  buf  )  );		  
		  printf(  "<name>%s</name>",  buf  );
		  str  =  replaceForXml(  resp.mems[i].grpDisplayName  );		  
		  myWChar2Utf8(  str.GetBuffer(  0  ),  buf,  mycountof(  buf  )  );
		  printf(  "<grp>%s</grp>",  buf  );
		  for  (  j  =  0;  j  <  recentFriendsResp.usCnt;  j  ++  )  {
			   if  (  resp.mems[i].idInfo.ui64Id  ==  recentFriendsResp.mems[j].idInfo.ui64Id  )  break;
		  }
		  if  (  j  <  recentFriendsResp.usCnt  )  {
			  printf(  "<st>%d</st>",  recentFriendsResp.mems[j].usRunningStatus  );
		  }
		  printf(  "</usr>"  );
	 }

	 iErr  =  0;

errLabel:
	 return  iErr;

}


 int  refreshUsrList(  void  *  pCgiParam,  WWWQM_COMM_BUF  *  pCommBuf,  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock  )	
{
	 int					iErr			=	-1;
	 QNM_CGI			*	pCgi			=   (  QNM_CGI  *  )pCgiParam;
	 QNM_CGI_HINTS		*	pCgiHints		=	(  QNM_CGI_HINTS  *  )pCgi->pHints;
	 //
	 //  int					i;
	 int					len;



	 time_t  tStartTran;  unsigned  int	uiTranNo;  time(  &tStartTran  );  uiTranNo  =  0;
	 

	 //  QY_MSG_HEAD						msgHead;
	 //  char							*	ptr;
	 //  unsigned  int						size;
	
	 //  下面再发送最近联系人请求，实际是为了获得在线离线状态信息
	 REFRESH_RECENTFRIENDS_REQ		recentFriendsReq;
	 //  IM_STREAM_CONTENT				stream;

	 memset(  &recentFriendsReq,  0,  sizeof(  recentFriendsReq  )  );
	 recentFriendsReq.uiType  =  CONST_imCommType_refreshRecentFriendsReq;

	 if  (  (  len  =  qyhtonRefreshRecentFriendsReq(  0,  &recentFriendsReq  )  )  <  0  )  goto  errLabel;
	 uiTranNo  ++  ;
	 if  (  qySendMsg(  pSession,  pSock,  &pCgi->cfg.to,  0,  CONST_qyCmd_refreshRecentFriendsReq,  tStartTran,  uiTranNo,  0,  (  char  *  )&recentFriendsReq,  len  )  )  {
		 traceLogA(  "qySendMsg failed"  );  goto  errLabel;
	 }
	 
	 /*
	 memset(  &msgHead,  0,  sizeof(  msgHead  )  );
	 memset(  &stream,  0,  sizeof(  stream  )  );
	 if  (  qyRecvMsg(  pSession,  pSock,  &pCgi->cfg.to,  &msgHead,  (  char  *  )&stream,  sizeof(  stream  )  )  )  goto  errLabel;
	 if  (  (  len  =  qyntohImStreamContent(  0,  &stream  )  )  <  0  )  {
		 traceLogA(  "scheduler: qyntohRefreshRecentFriendsResp failed"  );
		 goto  errLabel;
	 }	 

	 REFRESH_RECENTFRIENDS_RESP		recentFriendsResp;
	 memset(  &recentFriendsResp,  0,  sizeof(  recentFriendsResp  )  );
	 ptr  =  stream.buf;
	 size  =  stream.usStreamLen;

	 if  (  stream2Data(  &ptr,  &size,  tmpHandler_stream2RefreshRecentFriendsResp,  0,  &recentFriendsResp  )  )  goto  errLabel;      

	 #ifdef  __DEBUG__
	         TCHAR	tBuf[1024];
	 		 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d, t is %I64u, usCnt is %d"  ),   recentFriendsResp.uiType,  recentFriendsResp.tLastRefreshedTime_misServ,  recentFriendsResp.usCnt  );
			 for  (  i  =  0;  i  <  recentFriendsResp.usCnt;  i  ++  )  {
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, 第%d个, id %I64u, runStatus %s, ulIp %u"  ),  tBuf,  i,  recentFriendsResp.mems[i].idInfo.ui64Id,  qyGetDesByType1(  CONST_usRunningStatusTable,  recentFriendsResp.mems[i].usRunningStatus  ),  recentFriendsResp.mems[i].ulIp  );  
			 }
			 OutputDebugString(  tBuf  );
	 #endif


	 setQnmCgiHints(  pCgi->uiLangId_browser,  pCgiHints  );


	 //  printMimeHeader(  );
	 printf(  "Content-type:text/xml\n\n"  );

	 
	 printf(  "<xml>"  );

	 //  printf(  "<g>'hehe''bb'</g>"  );
	 //  printf(  "<g>vv</g>"  );

	 outputSth(  pCgi,  pCommBuf  );

	 for  (  i  =  0;  i  <  recentFriendsResp.usCnt;  i  ++  )  {
		  printf(  "<usr>"  );
		  printf(  "<msgr>%I64u</msgr>",  recentFriendsResp.mems[i].idInfo.ui64Id  );
		  printf(  "<st>%d</st>",  recentFriendsResp.mems[i].usRunningStatus  );
		  printf(  "</usr>"  );
	 }

	 printf(  "</xml>"  );

	 */

	 iErr  =  0;

errLabel:
	 return  iErr;

}




 int  talkTo(  void  *  pCgiParam,  WWWQM_COMM_BUF  *  pCommBuf,  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock  )	
{
	 int					iErr			=	-1;
	 QNM_CGI			*	pCgi			=   (  QNM_CGI  *  )pCgiParam;
	 QNM_CGI_HINTS		*	pCgiHints		=	(  QNM_CGI_HINTS  *  )pCgi->pHints;
	 MSG_ROUTE				route;
	 int					lenInBytes;
	 IM_L_STREAM	*	pStream			=	NULL;
	 unsigned  char			ucFlg			=	CONST_commFlg_routeTalkData;

	 CQyMalloc				mallocObj;
	 unsigned  int			uiBufSize		=	sizeof(  MIS_MSG_routeTalkData  );
	 char				*	pBuf			=	mallocObj.malloc(  uiBufSize  );
	 if  (  !pBuf  )  goto  errLabel;
	 //
	 time_t  tStartTran;  time(  &tStartTran  ); 

	 traceLogA(  "talkTo enters"  );

	//

	memset(  &route,  0,  sizeof(  route  )  );
	//  
	route.idInfo_from.ui64Id  =  pCommBuf->idInfo.ui64Id;				//  因为临时对应的号。所以
	route.idInfo_to.ui64Id  =  pCommBuf->cmdParam.idInfo_to.ui64Id;
	//
	route.ulDetectedIp_from  =  inet_addr(  pCgi->remoteIp  );			//  需要带入远程IP.
	//

	if  (  pCommBuf->cmdParam.u.uiType  ==  CONST_imCommType_htmlContent  &&  pCommBuf->cmdParam.u.html.wBuf[0]  )  {

		lenInBytes  =  uiBufSize;
		if  (  qyhtonRouteTalkData(  &route,  (  char  *  )&pCommBuf->cmdParam.u.html,  0,  TRUE,  ucFlg,  pBuf,  (  unsigned  int  *  )&lenInBytes,  NULL,  0  )  )  goto  errLabel;
	
		if  (  qySendMsg(  pSession,  pSock,  &pCgi->cfg.to,  ucFlg,  CONST_qyCmd_talkTo,  tStartTran,  pCommBuf->cmdParam.uiTranNo,  0,  (  char  *  )pBuf,  lenInBytes  )  )  goto  errLabel;

		//  返回一个tranNo, 告诉webQm这个算发成了
	
		printf(  "<tlk>"  );
		printf(  "<rc>0</rc>"  );
		printf(  "<tNo>0x%x</tNo>",  pCommBuf->cmdParam.uiTranNo  );
		printf(  "</tlk>"  );

	}

	
	 iErr  =  0;

errLabel:

	 traceLogA(  "talkTo leaves"  );

	 return  iErr;

}

 int  outputQmBBodyHtml(  QNM_CGI  *  pCgi  )
{
	CString		str;
	char		buf[8192  +  1]		=	"<div class=\"vLst\" id=\"fontsList\">"
										"<a href=\"#\" onclick=\"setFont('Tahoma');return false;\">Tahoma</a>"
										"<a href=\"#\" onclick=\"setFont('Verdana');return false;\">Verdana</a>"
										"<a href=\"#\" onclick=\"setFont('Georgia');return false;\">Georgia</a>"
										"<a href=\"#\" onclick=\"setFont('Garamond');return false;\">Garamond</a>"
										"<a href=\"#\" onclick=\"setFont('Arial');return false;\">Arial</a>"
										"<a href=\"#\" onclick=\"setFont('Times New Roman');return false;\">Times New Roman</a>"
										"<a href=\"#\" onclick=\"setFont('Courier New');return false;\">Courier News</a>"
										"</div>"
										"<div class=\"vLst\" id=\"fontSizeList\">"
                                        "<a href=\"#\" onclick=\"setFontSize(8);return false;\">8</a>"
										"<a href=\"#\" onclick=\"setFontSize(10);return false;\">10</a>" 
										"<a href=\"#\" onclick=\"setFontSize(12);return false;\">12</a>"
										"<a href=\"#\" onclick=\"setFontSize(14);return false;\">14</a>" 
										"<a href=\"#\" onclick=\"setFontSize(16);return false;\">16</a>"
										"<a href=\"#\" onclick=\"setFontSize(18);return false;\">18</a>"
										"<a href=\"#\" onclick=\"setFontSize(20);return false;\">20</a>"
										"<a href=\"#\" onclick=\"setFontSize(22);return false;\">22</a>"
										"<a href=\"#\" onclick=\"setFontSize(24);return false;\">24</a>"
                                        "</div>"
                                        "<div class=\"vLst\" id=\"emotLst\">"
										"<table>"/**/
										"<tr>"
                                        "<td><a href=\"#\" onmousedown=\"return false;\"><img class=\"emotCls\" src=\"images/emots/smile.gif\" width=\"19\" height=\"19\" style=\"border:0;\"	onclick=\"insertText(':)');\" /></a></td>"
                                        "<td><a href=\"#\" onmousedown=\"return false;\"><img class=\"emotCls\" src=\"images/emots/grin.gif\" width=\"19\" height=\"19\" style=\"border:0;\"	onclick=\"insertText(':D');\" /></a></td>"
										"<td><a href=\"#\" onmousedown=\"return false;\"><img class=\"emotCls\" src=\"images/emots/wink.gif\" width=\"19\" height=\"19\" style=\"border:0;\"	onclick=\"insertText(';)');\" /></a></td>"
                                        "<td><a href=\"#\" onmousedown=\"return false;\"><img class=\"emotCls\" src=\"images/emots/embarassed.gif\" width=\"19\" height=\"19\" style=\"border:0;\" onclick=\"insertText(':[');\" /></a></td>"
                                        "<td><a href=\"#\" onmousedown=\"return false;\"><img class=\"emotCls\" src=\"images/emots/love.gif\" width=\"19\" height=\"19\" style=\"border:0;\"	onclick=\"insertText(':*');\" /></a></td>"
                                        "</tr>"
										"<tr>"
										"<td><a href=\"#\" onmousedown=\"return false;\"><img class=\"emotCls\" src=\"images/emots/sad.gif\" width=\"19\" height=\"19\" style=\"border:0;\" onclick=\"insertText(':(');\" /></a></td>"
										"<td><a href=\"#\" onmousedown=\"return false;\"><img class=\"emotCls\" src=\"images/emots/cry.gif\" width=\"19\" height=\"19\" style=\"border:0;\" onclick=\"insertText(':\\'(');\" /></a></td>"
										"<td><a href=\"#\" onmousedown=\"return false;\"><img class=\"emotCls\" src=\"images/emots/cool.gif\" width=\"19\" height=\"19\" style=\"border:0;\"	onclick=\"insertText('8-)');\" /></a></td>"
										"<td><a href=\"#\" onmousedown=\"return false;\"><img class=\"emotCls\" src=\"images/emots/angry.gif\" width=\"19\" height=\"19\" style=\"border:0;\"	onclick=\"insertText('>:o');\" /></a></td>"
										"<td><a href=\"#\" onmousedown=\"return false;\"><img class=\"emotCls\" src=\"images/emots/surprised.gif\" width=\"19\" height=\"19\" style=\"border:0;\"	onclick=\"insertText(':O');\" /></a></td>"
										"</tr>"
                                        "<tr>"
										"<td><a href=\"#\" onmousedown=\"return false;\"><img class=\"emotCls\" src=\"images/emots/serious.gif\" width=\"19\" height=\"19\" style=\"border:0;\" onclick=\"insertText(':|');\" /></a></td>"
										"<td><a href=\"#\" onmousedown=\"return false;\"><img class=\"emotCls\" src=\"images/emots/sick.gif\" width=\"19\" height=\"19\" style=\"border:0;\"	onclick=\"insertText(':-S');\" /></a></td>"
										"<td><a href=\"#\" onmousedown=\"return false;\"><img class=\"emotCls\" src=\"images/emots/tongue.gif\" width=\"19\" height=\"19\" style=\"border:0;\" onclick=\"insertText(':P');\" /></a></td>"
										"<td><a href=\"#\" onmousedown=\"return false;\"><img class=\"emotCls\" src=\"images/emots/heart.gif\" width=\"19\" height=\"19\" style=\"border:0;\"	onclick=\"insertText('<3');\" /></a></td>"
										"<td><a href=\"#\" onmousedown=\"return false;\"><img class=\"emotCls\" src=\"images/emots/heartbroken.gif\" width=\"19\" height=\"19\" style=\"border:0;\" onclick=\"insertText('</3');\" /></a></td>"
										"</tr>"
										"</table>"
										"</div>"										
										"<div class=\"vLst\" id=\"fontColorList\">"
										"<table>"/**/
										"<tr>"
										"<td class=\"colorItem\" style=\"width:13px;height:13px;border:1px solid #000;background-color:#000000;\" onclick=\"setFontColor('#000000');\"></td>"
										"<td class=\"colorItem\" style=\"width:13px;height:13px;border:1px solid #000;background-color:#b8b8b8;\" onclick=\"setFontColor('#b8b8b8');\"></td>"
										"<td class=\"colorItem\" style=\"width:13px;height:13px;border:1px solid #000;background-color:#b4ad3b;\" onclick=\"setFontColor('#b4ad3b');\"></td>"
										"<td class=\"colorItem\" style=\"width:13px;height:13px;border:1px solid #000;background-color:#bb5c54;\" onclick=\"setFontColor('#bb5c54');\"></td>"
										"<td class=\"colorItem\" style=\"width:13px;height:13px;border:1px solid #000;background-color:#755a5c;\" onclick=\"setFontColor('#755a5c');\"></td>"
										"</tr>"
                                        "<tr>"
										"<td class=\"colorItem\" style=\"width:13px;height:13px;border:1px solid #000;background-color:#a9b5ef;\" onclick=\"setFontColor('#a9b5ef');\"></td>"
                                        "<td class=\"colorItem\" style=\"width:13px;height:13px;border:1px solid #000;background-color:#d65a20;\" onclick=\"setFontColor('#d65a20');\"></td>"
										"<td class=\"colorItem\" style=\"width:13px;height:13px;border:1px solid #000;background-color:#e39230;\" onclick=\"setFontColor('#e39230');\"></td>"
										"<td class=\"colorItem\" style=\"width:13px;height:13px;border:1px solid #000;background-color:#a71334;\" onclick=\"setFontColor('#a71334');\"></td>"
										"<td class=\"colorItem\" style=\"width:13px;height:13px;border:1px solid #000;background-color:#a68978;\" onclick=\"setFontColor('#a68978');\"></td>"
										"</tr>"
                                        "<tr>"
										"<td class=\"colorItem\" style=\"width:13px;height:13px;border:1px solid #000;background-color:#600c1f;\" onclick=\"setFontColor('#600c1f');\"></td>"
										"<td class=\"colorItem\" style=\"width:13px;height:13px;border:1px solid #000;background-color:#491130;\" onclick=\"setFontColor('#491130');\"></td>"
										"<td class=\"colorItem\" style=\"width:13px;height:13px;border:1px solid #000;background-color:#676f11;\" onclick=\"setFontColor('#676f11');\"></td>"
										"<td class=\"colorItem\" style=\"width:13px;height:13px;border:1px solid #000;background-color:#769321;\" onclick=\"setFontColor('#769321');\"></td>"
										"<td class=\"colorItem\" style=\"width:13px;height:13px;border:1px solid #000;background-color:#3966fe;\" onclick=\"setFontColor('#3966fe');\"></td>"
										"</tr>"
										"</table>"
										"</div>"
										"";

	traceLogA(  "len is %d",  strlen(  buf  )  );
	str  =  replaceForXml(  CString(  buf  )  );
	buf[0]  =  0;
	myWChar2Utf8(  str.GetBuffer(  0  ),  buf,  mycountof(  buf  )  );
	printf(  "<bBody>%s</bBody>",  buf  );

	/*
		<div class="itemList" id="fontsList">
			<a href="#" onclick="setFont('Tahoma');return false;">Tahoma</a> <a href="#" onclick="setFont('Verdana');return false;">
				Verdana</a> <a href="#" onclick="setFont('Georgia');return false;">Georgia</a>
			<a href="#" onclick="setFont('Garamond');return false;">Garamond</a> <a href="#" onclick="setFont('Arial');return false;">
				Arial</a> <a href="#" onclick="setFont('Times New Roman');return false;">Times 
				New Roman</a> <a href="#" onclick="setFont('Courier New');return false;">Courier 
				News</a>
		</div>
		<div class="itemList" id="fontSizeList">
			<a href="#" onclick="setFontSize(8);return false;">8</a> <a href="#" onclick="setFontSize(10);return false;">
				10</a> <a href="#" onclick="setFontSize(12);return false;">12</a> <a href="#" onclick="setFontSize(14);return false;">
				14</a> <a href="#" onclick="setFontSize(16);return false;">16</a> <a href="#" onclick="setFontSize(18);return false;">
				18</a> <a href="#" onclick="setFontSize(20);return false;">20</a> <a href="#" onclick="setFontSize(22);return false;">
				22</a> <a href="#" onclick="setFontSize(24);return false;">24</a>
		</div>
		<div class="itemList" id="emoticonList">
			<table>
				<tr>
					<td><a href="#" onmousedown="return false;"><img class="emotIcon" src="images/emoticons/smile.gif" width="19" height="19" style="border:0;"
								onclick="insertText(':)');" /></a></td>
					<td><a href="#" onmousedown="return false;"><img class="emotIcon" src="images/emoticons/grin.gif" width="19" height="19" style="border:0;"
								onclick="insertText(':D');" /></a></td>
					<td><a href="#" onmousedown="return false;"><img class="emotIcon" src="images/emoticons/wink.gif" width="19" height="19" style="border:0;"
								onclick="insertText(';)');" /></a></td>
					<td><a href="#" onmousedown="return false;"><img class="emotIcon" src="images/emoticons/embarassed.gif" width="19" height="19" style="border:0;"
								onclick="insertText(':[');" /></a></td>
					<td><a href="#" onmousedown="return false;"><img class="emotIcon" src="images/emoticons/love.gif" width="19" height="19" style="border:0;"
								onclick="insertText(':*');" /></a></td>
				</tr>
				<tr>
					<td><a href="#" onmousedown="return false;"><img class="emotIcon" src="images/emoticons/sad.gif" width="19" height="19" style="border:0;"
								onclick="insertText(':(');" /></a></td>
					<td><a href="#" onmousedown="return false;"><img class="emotIcon" src="images/emoticons/cry.gif" width="19" height="19" style="border:0;"
								onclick="insertText(':\'(');" /></a></td>
					<td><a href="#" onmousedown="return false;"><img class="emotIcon" src="images/emoticons/cool.gif" width="19" height="19" style="border:0;"
								onclick="insertText('8-)');" /></a></td>
					<td><a href="#" onmousedown="return false;"><img class="emotIcon" src="images/emoticons/angry.gif" width="19" height="19" style="border:0;"
								onclick="insertText('>:o');" /></a></td>
					<td><a href="#" onmousedown="return false;"><img class="emotIcon" src="images/emoticons/surprised.gif" width="19" height="19" style="border:0;"
								onclick="insertText(':O');" /></a></td>
				</tr>
				<tr>
					<td><a href="#" onmousedown="return false;"><img class="emotIcon" src="images/emoticons/serious.gif" width="19" height="19" style="border:0;"
								onclick="insertText(':|');" /></a></td>
					<td><a href="#" onmousedown="return false;"><img class="emotIcon" src="images/emoticons/sick.gif" width="19" height="19" style="border:0;"
								onclick="insertText(':-S');" /></a></td>
					<td><a href="#" onmousedown="return false;"><img class="emotIcon" src="images/emoticons/tongue.gif" width="19" height="19" style="border:0;"
								onclick="insertText(':P');" /></a></td>
					<td><a href="#" onmousedown="return false;"><img class="emotIcon" src="images/emoticons/heart.gif" width="19" height="19" style="border:0;"
								onclick="insertText('<3');" /></a></td>
					<td><a href="#" onmousedown="return false;"><img class="emotIcon" src="images/emoticons/heartbroken.gif" width="19" height="19" style="border:0;"
								onclick="insertText('</3');" /></a></td>
				</tr>
			</table>
		</div>
		<div class="itemList" id="fontColorList">
			<table>
				<tr>
					<td class="colorItem" style="width:13px;height:13px;border:1px solid #000;background-color:#000000;"
						onclick="setFontColor('#000000');"></td>
					<td class="colorItem" style="width:13px;height:13px;border:1px solid #000;background-color:#b8b8b8;"
						onclick="setFontColor('#b8b8b8');"></td>
					<td class="colorItem" style="width:13px;height:13px;border:1px solid #000;background-color:#b4ad3b;"
						onclick="setFontColor('#b4ad3b');"></td>
					<td class="colorItem" style="width:13px;height:13px;border:1px solid #000;background-color:#bb5c54;"
						onclick="setFontColor('#bb5c54');"></td>
					<td class="colorItem" style="width:13px;height:13px;border:1px solid #000;background-color:#755a5c;"
						onclick="setFontColor('#755a5c');"></td>
				</tr>
				<tr>
					<td class="colorItem" style="width:13px;height:13px;border:1px solid #000;background-color:#a9b5ef;"
						onclick="setFontColor('#a9b5ef');"></td>
					<td class="colorItem" style="width:13px;height:13px;border:1px solid #000;background-color:#d65a20;"
						onclick="setFontColor('#d65a20');"></td>
					<td class="colorItem" style="width:13px;height:13px;border:1px solid #000;background-color:#e39230;"
						onclick="setFontColor('#e39230');"></td>
					<td class="colorItem" style="width:13px;height:13px;border:1px solid #000;background-color:#a71334;"
						onclick="setFontColor('#a71334');"></td>
					<td class="colorItem" style="width:13px;height:13px;border:1px solid #000;background-color:#a68978;"
						onclick="setFontColor('#a68978');"></td>
				</tr>
				<tr>
					<td class="colorItem" style="width:13px;height:13px;border:1px solid #000;background-color:#600c1f;"
						onclick="setFontColor('#600c1f');"></td>
					<td class="colorItem" style="width:13px;height:13px;border:1px solid #000;background-color:#491130;"
						onclick="setFontColor('#491130');"></td>
					<td class="colorItem" style="width:13px;height:13px;border:1px solid #000;background-color:#676f11;"
						onclick="setFontColor('#676f11');"></td>
					<td class="colorItem" style="width:13px;height:13px;border:1px solid #000;background-color:#769321;"
						onclick="setFontColor('#769321');"></td>
					<td class="colorItem" style="width:13px;height:13px;border:1px solid #000;background-color:#3966fe;"
						onclick="setFontColor('#3966fe');"></td>
				</tr>
			</table>
		</div>
		*/

	//  _sntprintf(  buf,  mycountof(  buf  ),  "%


	return  0;
}


 int  outputQmBInnerHtml(  QNM_CGI  *  pCgi,  LPCTSTR  wAdvertisement  )
{
	TCHAR	tBuf[8192  +  1]	=	_T(  ""  );
	BOOL	isIE				=	pCgi->isIE;
	CString	str;

	if  (  !wAdvertisement  )  return  -1;

	/*  b.html里init(  )里的, 用下面输出来代替.2007/12/17
	   dlgTalk.innerHTML = '<div class="recentMsgListCls" id="recentMsgList"></div>' + "\n" +
                               ' <a href="#" class="setFontLink" id="imSetFont" ' + (isIE ? 'style="height:20px;" ' : '') + 'onclick="toggleFontList();return false;">Tahoma</a>' +
                               ' <a href="#" class="setFontSizeLink" id="imSetFontSize" ' + (isIE ? 'style="height:20px;" ' : '') + 'onclick="toggleFontSizeList();return false;" onselectstart="return false;">12</a>' +
                               '<div class="imToolbarCls" id="imToolbar"><img src="images/bold_off.png" onmouseover="self.opener.btnHover(this);" onmouseout="self.opener.btnNormal(this);" onclick="toggleBold();" alt="Bold" id="imBold" /> ' +
                               '<img src="images/italic_off.png" onmouseover="self.opener.btnHover(this);" onmouseout="self.opener.btnNormal(this);" onclick="toggleItalic();" alt="Italic" id="imItalic" /> '+
                               '<img src="images/underline_off.png" onmouseover="self.opener.btnHover(this);" onmouseout="self.opener.btnNormal(this);" onclick="toggleUnderline();" alt="Underline" id="imUnderline" /></div>' +
                               ' <a href="#" class="setFontColorLink" id="imSetFontColor" ' + (isIE ? 'style="height:20px;" ' : '') + 'onclick="toggleFontColorList();return false;" onselectstart="return false;"><div id="imSetFontColorColor" style="width:14px;height:14px;display:block;"></div></a>' +
                               ' <a href="#" class="insertEmoticonLink" id="imInsertEmoticon" ' + (isIE ? 'style="height:20px;" ' : '') + 'onclick="toggleEmoticonList();return false;" onselectstart="return false;"><img src="images/emoticons/mini_smile.gif" width="14" height="14" style="border:0;" /></a>' +
                               "\n" + '<div style="overflow:auto;"><textarea class="inputText" id="imInput" onfocus="return false;" onkeypress="return keyHandler(event);"></textarea></div>'  +
                               '<div class="advCls" id=advertisement><br>&nbsp;&nbsp;&nbsp;<b>You are welcome to <a href="http://www.qycx.com/" target="_blank">www.qycx.com!</a></b></div>'
                               ;
                              
                              alert(  dlgTalk.innerHTML  );
	*/

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s %s "  ),  
												_T(  "<div class=\"recentMsgListCls\" id=\"recentMsgList\"></div>\n"  ),
												_T(  "<a href=\"#\" class=\"setFontLink\" id=\"imSetFont\" "  ),  CString(isIE ? "style=\"height:20px;\" " : ""  ), _T(  "onclick=\"toggleFontList();return false;\">Tahoma</a>"  ),
												_T(  "<a href=\"#\" class=\"setFontSizeLink\" id=\"imSetFontSize\" "  ),  CString(isIE ? "style=\"height:20px;\" " : ""),  _T(  "onclick=\"toggleFontSizeList();return false;\" onselectstart=\"return false;\">12</a>"  ),
												_T(  "<div class=\"imToolbarCls\" id=\"imToolbar\">"  ),
												_T(  "<img src=\"images/bold_off.png\" onmouseover=\"self.opener.btnHover(this);\" onmouseout=\"self.opener.btnNormal(this);\" onclick=\"toggleBold();\" alt=\"Bold\" id=\"imBold\" /> "  ),
												_T(  "<img src=\"images/italic_off.png\" onmouseover=\"self.opener.btnHover(this);\" onmouseout=\"self.opener.btnNormal(this);\" onclick=\"toggleItalic();\" alt=\"Italic\" id=\"imItalic\" />"  ),
												_T(  "<img src=\"images/underline_off.png\" onmouseover=\"self.opener.btnHover(this);\" onmouseout=\"self.opener.btnNormal(this);\" onclick=\"toggleUnderline();\" alt=\"Underline\" id=\"imUnderline\" />"  ),
												_T(  "</div>"  ),
												_T(  "<a href=\"#\" class=\"setFontColorLink\" id=\"imSetFontColor\""  ),  CString(isIE ? "style=\"height:20px;\"" : ""),  _T(  "onclick=\"toggleFontColorList();return false;\" onselectstart=\"return false;\"><div id=\"imSetFontColorColor\" style=\"width:14px;height:14px;display:block;\"></div></a>"  ),
												_T(  "<a href=\"#\" class=\"insertEmotLink\" id=\"imInsertEmot\""  ),  CString(isIE ? "style=\"height:20px;\"" : ""),  _T(  "onclick=\"toggleEmotLst();return false;\" onselectstart=\"return false;\"><img src=\"images/emots/mini_smile.gif\" width=\"14\" height=\"14\" style=\"border:0;\" /></a>\n"  ),
                                                _T(  "<div style=\"overflow:auto;\"><textarea class=\"inputText\" id=\"imInput\" onfocus=\"return false;\" onkeypress=\"return keyHandler(event);\"></textarea></div>"  ),
												//  _T(  "<div class=\"advCls\" id=advertisement><br>&nbsp;&nbsp;&nbsp;<b>Welcome to <a href=\"http://www.qycx.com/\" target=\"_blank\">www.qycx.com!</a></b></div>"  )  
												_T(  "<div class=\"advCls\" id=advertisement>"  ),  wAdvertisement,  _T(  "</div>"  )  
												);

	OutputDebugString(  CString(  tBuf  )  );
	OutputDebugString(  _T(  "\n"  )  );
	str  =  replaceForXml(  CString(  tBuf  )  );
	tBuf[0]  =  0;
	myWChar2Utf8(  str.GetBuffer(  0  ),  (  char  *  )tBuf,  sizeof(  tBuf  )  );
	printf(  "<bInner>%s</bInner>",  (  char  *  )tBuf  );

	return  0;
 
}



 int  procPost(  void  *  pCgiParam,  char  *  szBuffer  )
{
	 int						iErr					=	-1;
	 QNM_CGI				*	pCgi					=   (  QNM_CGI  *  )pCgiParam;
	 QNM_CGI_HINTS			*	pCgiHints				=	(  QNM_CGI_HINTS  *  )pCgi->pHints;
	 QY_COMM_SESSION			session;
	 unsigned  char				ucbSessionOpen			=	FALSE;
	 QY_SOCK					sock;
	 //
	 char						buf[4096];
	 char					*	ptr;
	 unsigned  int				len;
	 //
	 BOOL						bAuthed					=	FALSE;
	 BOOL						bNeedVerified			=	FALSE;
	 int						iErrCode				=	0;
	 char						errTitle[64  + 1]		=	"Failed";
	 char						errContent[255  +  1]	=	"";
	 //
	 WWWQM_COMM_BUF				commBuf;
	 unsigned  short			usCmd_parsed			=	0;
	 unsigned  short			usCmd					=	0;
	 //
	 WWWQM_COMM_BUF			*	pCommBuf				=	&commBuf;
	 //
	 unsigned  char				ucFlg					=	CONST_commFlg_routeTalkData;
	 unsigned  int				uiChannelType			=	0;
	 MSG_ROUTE					route;
	 int						lenInBytes;

	 traceLogA(  "procPost: enters"  );

	 //
	 memset(  &commBuf,  0, sizeof(  commBuf  )  );
	 //  先取一个数据头信息
	 if  (  parsePostData(  szBuffer,  &commBuf,  &usCmd_parsed,  &szBuffer  )  )  goto  errLabel;
	 if  (  !usCmd_parsed  )  {
		 traceLogA(  "没有遇到命令"  );  goto  errLabel;
	 }

	 clearQySock(  &sock  );
	 memset(  &session,  0,  sizeof(  session  )  );
	 

	 pCgi->iServiceId  =  CONST_qyServiceId_is;
	 safeStrnCpy(  qnmVerStr(  pCgi->iServiceId  ),  pCgi->ver,  sizeof(  pCgi->ver  )  );

	 //  
	 {
		 QY_COMM_AUTHINFO_MIS	*	pAuthInfo			=	&pCommBuf->authInfo;
	
		 //  先填充authInfo
		 pAuthInfo->usLangId  =  pCgi->uiLangId_browser;
		 pAuthInfo->uiDevType  =  CONST_objType_browser;
		 //
		 //  getQwmMacs(  &pCgi->env,  &pAuthInfo->macsInfo  );

	 }

	 switch  (  usCmd_parsed  )  {
			 case  CONST_qyCmd_talkTo:
				   uiChannelType  =  CONST_channelType_webSending;
				   break;
			 case  CONST_qyCmd_refreshRecentFriendsReq:
			 default:
				    uiChannelType  =  CONST_channelType_talking;
				    break;
	 }				   


	 len  =  sizeof(  buf  );
	 if  (  qnmOpenSession_mis(  pCgi->cfg.opt.cnt.ip,  pCgi->cfg.opt.cnt.port,  &pCommBuf->authInfo,  CONST_qnmAuthCmd_cgiTalk,  uiChannelType,  pCgi->remoteIp,  pCgi->iServiceId,  pCgi->ver,  &pCgi->commEncCtx,  &session,  &sock,  &pCgi->cfg.to,  buf,  &len  )  )  {
		 traceLogA(  "can't connect to server"  );
		 safeStrnCpy(  "Can't connect to server.",  errContent,  mycountof(  errContent  )  );
		 goto  errLabel;
	 }
	 ucbSessionOpen  =  TRUE;
	 memset(  &pCommBuf->authResp,  0,  sizeof(  pCommBuf->authResp  )  );
	 ptr  =  buf;
	 if  (  stream2Data(  &ptr,  &len,  filterStream_is,  tmpHandler_stream2AuthResp_mis,  NULL,  &pCommBuf->authResp  )  )  goto  errLabel;
	 
	 traceLogA(  "uiLogonId is %x, wRndName_serv is %S",  pCommBuf->authResp.uiLogonId,  pCommBuf->authResp.wRndName_serv  );

	 
	 if  (  !isRcOk(  session.usLastRespCode_i  )  )  {
		 //
		 //  if  (  !isRcNeedVerified(  session.usLastRespCode_i  )  )  goto  errLabel;
		 //  traceLogA(  "get hint from server: [%S]",  pCommBuf->authResp.wBuf_hint  );
		 //  bNeedVerified  =  TRUE;
		 //
		 iErrCode  =  255;
		 safeStrnCpy(  "Session need reset.",  errContent,  mycountof(  errContent  )  );
		 goto  errLabel;
	 }	 
	 if  (  isRcOk(  session.usLastRespCode_i  )  )  bAuthed  =  TRUE;		   
	 
	 if  (  !bAuthed  )  {
		 traceLogA(  "这里没有通过认证.不能进行通话"  );  goto  errLabel;
	 }
	 if  (  !bMessengerIdValid(  &pCommBuf->authResp.idInfo  )  )  goto  errLabel;

	 pCommBuf->idInfo.ui64Id  =  pCommBuf->authResp.idInfo.ui64Id;

	 traceLogA(  "procPost: session is open, idInfo is %I64u",  pCommBuf->idInfo.ui64Id  );

	 //  printMimeHeader(  );
	 printf(  "Content-type:text/xml\n\n"  );
	 
	 printf(  "<xml>"  );

	 outputSth(  pCgi,  pCommBuf,  0  );

	 for  (  ;  usCmd_parsed;  )  {

		  usCmd  =  usCmd_parsed;

		  memset(  &pCommBuf->cmdParam,  0,  sizeof(  pCommBuf->cmdParam  )  );
		  //
		  if  (  !szBuffer  )  usCmd_parsed  =  0;
		  else  {
              if  (  parsePostData(  szBuffer,  &commBuf,  &usCmd_parsed,  &szBuffer  )  )  goto  errLabel;
		  }
		  
		  switch  (  usCmd  )  {
			 case  CONST_qyCmd_refreshImObjListReq:
				   if  (  outputQmBBodyHtml(  pCgi  )  )  goto  errLabel;
				   //
				   if  (  getUsrList(  pCgi,  pCommBuf,  &session,  &sock  )  )  goto  errLabel;
				   break;
			 case  CONST_qyCmd_talkTo:
				   if  (  talkTo(  pCgi,  pCommBuf,  &session,  &sock  )  )  goto  errLabel;
				   break;
			 case  CONST_qyCmd_refreshRecentFriendsReq:
				   if  (  refreshUsrList(  pCgi,  pCommBuf,  &session,  &sock  )  )  goto  errLabel;
				   if  (  myRecvMsgs(  pCgi,  pCommBuf,  &session,  &sock  )  )  goto  errLabel;
				   //  
				   memset(  &route,  0,  sizeof(  route  )  );
				   route.idInfo_from.ui64Id  =  pCommBuf->idInfo.ui64Id;	//  因为临时对应的号。所以
				   route.idInfo_to.ui64Id  =  pCommBuf->idInfo.ui64Id;		//  注意，这个是发给自己的号
				   //
				   lenInBytes  =  sizeof(  buf  );
				   if  (  qyhtonRouteTalkData(  &route,  0,  0,  FALSE,  ucFlg,  buf,  (  unsigned  int  *  )&lenInBytes,  NULL,  0  )  )  goto  errLabel;
				   //
				   if  (  qySendMsg(  &session,  &sock,  &pCgi->cfg.to,  ucFlg,  CONST_qyCmd_lastMsgInSession,  0,  0,  0,  buf,  lenInBytes  )  )  goto  errLabel;
				   if  (  myRecvMsgs(  pCgi,  pCommBuf,  &session,  &sock  )  )  goto  errLabel;
				   break;
			 case  CONST_qyCmd_lastMsgInSession:
				   memset(  &route,  0,  sizeof(  route  )  );
				   route.idInfo_from.ui64Id  =  pCommBuf->idInfo.ui64Id;	//  因为临时对应的号。所以
				   route.idInfo_to.ui64Id  =  pCommBuf->idInfo.ui64Id;		//  注意，这个是发给自己的号
				   //
				   lenInBytes  =  sizeof(  buf  );
				   if  (  qyhtonRouteTalkData(  &route,  0,  0,  FALSE,  ucFlg,  buf,  (  unsigned  int  *  )&lenInBytes,  NULL,  0  )  )  goto  errLabel;
				   //
				   if  (  qySendMsg(  &session,  &sock,  &pCgi->cfg.to,  ucFlg,  CONST_qyCmd_lastMsgInSession,  0,  0,  0,  buf,  lenInBytes  )  )  goto  errLabel;
				   if  (  myRecvMsgs(  pCgi,  pCommBuf,  &session,  &sock  )  )  goto  errLabel;
				   break;
			 default:
					traceLogA(  "usCmd error"  );  goto  errLabel;
					break;
	 
		  }

	 }

	 printf(  "</xml>"  );

	 /*
	 printMimeHeader(  );
	 printHtmlHeader(  NULL,  pCgiHints->pBjcx  );
	 	 
	 //  printVars(  );				//  仅用来显示环境变量和参数。
	 
	 printHtmlTrailer(  );
	 */

	 iErr  =  0;

errLabel:

	 if  (  ucbSessionOpen  )  qnmCloseSession_msg(  &session,  &sock,  &pCgi->cfg.to  );

	 if  (  iErr  )  {
		 outputErrHint(  TRUE,  iErrCode,  errTitle,  errContent  );  
	 }

	 traceLogA(  "procPost: leaves"  );
	 return  0;
}


