
#if !defined(AFX_QNMCGI_H__68826118_E41A_4FA0_B645_42C9D71A8EC3__INCLUDED_)
#define AFX_QNMCGI_H__68826118_E41A_4FA0_B645_42C9D71A8EC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include	<afxdb.h>
#include	<winsock2.h>

#include	<windows.h>
#include	<vfw.h>

#include	"qyCommon.h"
//  #include	"qyDbCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qnmSysCustom.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"
#include	"qyGuiCommon.h"

#include	"qnmPcComm.h"
#include	"qySyncCommProc.h"
#include	"genericQueue.h"

#include	"qyCommProc.h"
#include	"qmOpenCommon.h"
//  #include	"qyCommProc_open.h"
#include	"qyLangCommProc.h"
#include	"qnmCommProc.h"
#include	"qyq2.h"
#include	"qnmCommProc_mis.h"
#include	"qnmSpCommProc.h"
#include	"qyMtSock.h"
//  #include	"traceLogA.h"
#include	"qyMsgFunc.h"

#include	"qwmNetworkStatusCommProc.h"
#include	"qysyncCommProc.h"

#include	"qyString.h"

//  这个结构应放到公用库里

typedef  struct  __qnmSpecialOpt_t					{
				 QWM_DYN_CFG						dynCfg;							//  2006/07/01
				 //
				 QY_LOGICAL_SERVER					cnt;					
				 int								iSystemId_wanted;		
				 unsigned  char						ucbGetPcAsset;			
				 unsigned  char						ucbNetMc2;
}		 QNM_SPECIAL_OPT;

extern  "C"  int  qnmParseSpecialOpt(  QNM_SPECIAL_OPT  *  pSpecialCfg  );



typedef  struct  __qnmCgiCfg_t						{
				 QNM_SPECIAL_OPT					opt;

				 SOCK_TIMEOUT						to;

}		 QNM_CGI_CFG;


typedef  struct  __qnmCgi_t							{
				 MACRO_qyAppCommonMems

				 QY_ENV								env;					//  2007/01/25

				 QNM_CGI_CFG						cfg;
				 QY_ENC_CTX							encCtx,  commEncCtx;	//  2004/01/03添加commEncCtx

				 //  控制变量
				 BOOL								bQuit;

				 //  输入环境变量
				 unsigned  int						uiLangId_browser;
				 char								remoteIp[CONST_qyMaxIpLen  +  1];
				 char								requestMethod[16];
				 BOOL								isIE;					//  2007/12/17

				 //  状态变量
				 unsigned  char						ucbSnmpInited;
				 unsigned  char						ucbTcpStarted;
				 unsigned  long						ulbEncInited:1;

				 //  
				 QWM_MACS_INFO						macsInfo;
				 QY_COMM_AUTHINFO_MIS				authInfo_mis;

				 //
				 void					*			pHints;

				 //  是否显示一些debug的信息				
				 unsigned  char						ucbShowDebugHint;

}		 QNM_CGI;


typedef  struct  __wwwQmCommBuf_T					{
				 int								iServiceId;
				 QY_COMM_AUTHINFO_MIS				authInfo;
				 AUTH_RESP_MIS						authResp;

				 QY_MESSENGER_ID					idInfo;

				 struct								{

					 unsigned  int					uiTranNo;

					 QY_MESSENGER_ID				idInfo_from;
					 QY_MESSENGER_ID				idInfo_to;

					 union							{
						 unsigned  int				uiType;
						 IM_HTML_CONTENT			html;
					 }								u;

				 }									cmdParam;

}		 WWWQM_COMM_BUF;


int		printMimeHeader(  );
void	printHtmlHeader(  char  *  charset,  char  *  title  );
void	printHtmlTrailer(  );

int		printXmlHeader(  );


void	printVars(  BOOL  bOutputHtml  );
void	urlDecode(  char  *pEncoded  );
void	swapChar(  char  *  pOriginal,  char  cBad,  char  cGood  );

//
void  outputErrHint(  BOOL  ucbXml,  int  iErrCode,  char  *  title,  char  *  content  );

//
int		outputLogin(  void  *  pQnmCgi  );
int		outputPcSearch(  void  *  pQnmCgi  );
int		procGet(  void  *  pCgi  );
//
int  outputQmBBodyHtml(  QNM_CGI  *  pCgi  );
int  outputQmBInnerHtml(  QNM_CGI  *  pCgi,  LPCTSTR  wAdvertisement  );
//
int		parsePostData(  char  *  szBuffer,  WWWQM_COMM_BUF  *  pCommBuf,  unsigned  short  *  pusCmd_parsed,  char  **  pp  );
int		procPost(  void  *  pCgiParam,  char  *  szBuffer  );



#endif // !defined(AFX_QNMCGI_H__68826118_E41A_4FA0_B645_42C9D71A8EC3__INCLUDED_)
