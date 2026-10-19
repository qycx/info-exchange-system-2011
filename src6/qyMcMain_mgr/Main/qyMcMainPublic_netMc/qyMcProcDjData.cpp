

#include	"stdafx.h"
//  #include	"myresource.h"
#include	"qyMcMainCommon.h"
#ifndef  __WINCE__
#include	"qyFile.h"
#endif
#include	"qwmDjCommProc.h"




 int  procDjData(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int					iErr								=	0;
	 QY_MC				*	pQyMc								=	QY_GET_GBUF(  );
	 COMMON_PARAM		*	pCommonParam						=	(  COMMON_PARAM  *  )p1;
	 TCHAR				*	dir									=	(  TCHAR  *  )pCommonParam->p1;
	 BOOL				*	pbEnumOk							=	(  BOOL  *  )pCommonParam->p2;
	 WIN32_FIND_DATA	*	pFindData							=	(  WIN32_FIND_DATA  *  )p2;
	 TCHAR					fileName[CONST_qyMaxPathLen  +  1];
	 unsigned  char			ucbMyFile							=	FALSE;
	 unsigned  char			ucbFileOk							=	FALSE;
	 unsigned  char			ucbFinished							=	FALSE;
	 QWM_MACS_INFO			macsInfo;
	 QNM_REG_INFO			regInfo;
	 char					ver[16];
	 QY_COMM_SESSION		session;
	 BOOL					bSessionOpen						=	FALSE;
	 QY_SOCK				sock;
	 QY_COMM_RESP			tmpResp;
	 char					cfgsBuf[4096];
	 int					i;
	 QNM_SECCHK_COMMHEAD	commHead;
	 QNM_SECCHK_EVENT		event;
	 char					xBuf[8192],  encBuf[8192];
	 FILE				*	fp									=	NULL;
	 int					djEndLen							=  strlen(  CONST_qyFileObj_djEnd  );
	 unsigned  int			len;
	 unsigned  int			uiSecChkEventSentCnt				=	0;
	 char					cntIp[CONST_qyMaxIpLen  +  1]		=	"127.0.0.1";
	 unsigned  short		usCntPort							=	DEFAULT_qyMcServPort;
	 QNM_CMDPARAM_showQwmSvrStatus	cmdParam;
	 char					buf[1024];


	 _sntprintf(  fileName,  mycountof(  fileName  ),  _T(  "%s"  ),  CQyString(  dir  )  );
	 tTrailDir(  fileName,  mycountof(  fileName  )  );
	 _sntprintf(  fileName,  mycountof(  fileName  ),  _T(  "%s%s"  ),  fileName,  pFindData->cFileName  );
	 
	 traceLogA(  "procDjData: %S",  fileName  );

	 if  (  bDir(  fileName  )  )  {
		 COMMON_PARAM	tmpCommonParam;
		 if  (  !_tcsicmp(  pFindData->cFileName,  _T(  "."  )  )  
			 ||  !_tcsicmp(  pFindData->cFileName,  _T(  ".."  )  )  )
		 {
			 goto  errLabel;
		 }

		 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  ""  ),  _T(  "遍历 "  ),  CQyString(  fileName  )  ); 

		 MACRO_makeCommonParam3(  0,  fileName,  pbEnumOk,  tmpCommonParam  );  
		 qwmEnumUsrDir(  NULL,  fileName,  procDjData,  p0,  &tmpCommonParam  );  
		 goto  errLabel;
	 }

	 //  判断是否我们的文件
	 if  (  getQwmFileObj(  fileName,  (  CONST_qyFileObj_djMagic  ),  0,  0  )  )  {
		 traceLogA(  "%S 不是我们的数据文件",  fileName  );  goto  errLabel;
	 }
	 ucbMyFile  =  TRUE;
	 //  macsInfo
	 memset(  &macsInfo,  0,  sizeof(  macsInfo  )  );
	 if  (  getQwmFileObj(  fileName,  (  CONST_qyFileObj_djMac  ),  buf,  mycountof(  buf  )  )  )  {
		 traceLogA(  "%s中没有mac项",  fileName  );  goto  errLabel;
	 }
	 strncpy(  (  char  *  )macsInfo.macs[0],  buf,  sizeof(  macsInfo.macs[0]  )  );
	 macsInfo.nMacs  =  1;
	 if  (  !bMacsInfoValid(  &macsInfo  )  )  {
		 traceLogA(  "macsInfo信息不对"  );  goto  errLabel;
	 }

	 //  ver
	 if  (  getQwmFileObj(  fileName,  (  CONST_qyFileObj_djVer  ),  buf,  mycountof(  buf  )  )  )  goto  errLabel;
	 strncpy(  ver,  buf,  sizeof(  ver  )  );

	 memset(  &regInfo,  0,  sizeof(  regInfo  )  );
	 regInfo.iCustomId  =  qyGetCustomId(  );
	 //
	 i  =  0;
	 regInfo.uiFieldIds[i]  =  CONST_fieldId_dw;
	 getQwmFileObj(  fileName,  (  CONST_qyFileObj_djDw  ),  regInfo.u.cols[i],  sizeof(  regInfo.u.cols[i]  )  );
	 i  ++  ;
	 regInfo.uiFieldIds[i]  =  CONST_fieldId_bm;
	 getQwmFileObj(  fileName,  (  CONST_qyFileObj_djBm  ),  regInfo.u.cols[i],  sizeof(  regInfo.u.cols[i]  )  );
	 i  ++  ;
	 regInfo.uiFieldIds[i]  =  CONST_fieldId_syr;
	 getQwmFileObj(  fileName,  (  CONST_qyFileObj_djSyr  ),  regInfo.u.cols[i],  sizeof(  regInfo.u.cols[i]  )  );


	 ucbFileOk  =  TRUE;


	 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  ""  ),  _T(  "导入 "  ),  CQyString(  fileName  )  ); 


	 clearQySock(  &sock  );
	 memset(  &session,  0,  sizeof(  session  )  );

	 if  (  qnmOpenSession(  cntIp,  usCntPort,  &macsInfo,  0,  CONST_qyServiceId_qwm,  ver,  &pQyMc->commEncCtx,  &session,  &sock,  &pQyMc->cfg.to,  0,  0  )  )  {
		 iErr  =  -1;  goto  errLabel;
	 }
	 bSessionOpen  =  TRUE;

	 regInfo.iCustomId  =  qyhtonl(  regInfo.iCustomId  );
	//  2005/01/18对注册信息转换成UTF编码
	for  (  i  =  0;  i  <  sizeof(  regInfo.u.cols  )  /  sizeof(  regInfo.u.cols[0]  );  i  ++  )  {
		 MACRO_htonl(  regInfo.uiFieldIds[i]  );  //  myStr2Utf8(  regInfo.u.cols[i],  sizeof(  regInfo.u.cols[i]  )  );
	}
	if  (  qySendReq(  &session,  &sock,  &pQyMc->cfg.to,  CONST_qyCmd_reg,  (  char  *  )&regInfo,  sizeof(  regInfo  )  )  )  goto  errLabel;
	regInfo.iCustomId  =  qyntohl(  regInfo.iCustomId  );	//  注意将iCustomId从网络字节顺序还原为主机字节顺序
	if  (  qyRecvResp(  &session,  &sock,  &pQyMc->cfg.to,  &tmpResp,  cfgsBuf,  sizeof(  cfgsBuf  )  )  )  goto  errLabel;
	if  (  !isRcOk(  tmpResp.head.usCode  )  )  goto  errLabel;

	//  下面发送安检日志
	memset(  &commHead,  0,  sizeof(  commHead  )  );
	len  =  sizeof(  encBuf  );
	if  (  qnmEncData(  &pQyMc->commEncCtx,  (  char  *  )&event,  sizeof(  event  ),  encBuf,  &len  )  )  {
		traceLogA(  "sndCacheToSvr里qnmEncData failed."  );  goto  errLabel;
	}
	commHead.uiEventSndSize  =  len;
	qyhtonQnmSecChkCommHead(  &commHead  );
	if  (  qySendReq(  &session,  &sock,  &pQyMc->cfg.to,  CONST_qyCmd_sndSecChkLog,  (  char  *  )&commHead,  sizeof(  commHead  )  )  )  goto  errLabel;

	fp  =  _tfopen(  fileName,  _T(  "r"  )  );
	//  先略过数据文件头
	for  (  ;  ;  )  {
		 if  (  !fgets(  xBuf,  sizeof(  xBuf  ),  fp  )  )  goto  errLabel;
		 if  (  !_strnicmp(  xBuf,  CONST_qyFileObj_djEnd,  djEndLen  )  )  break;
	}


	//  再读取数据
	for  (  ;  ;  )  {
		 if  (  !fgets(  xBuf,  sizeof(  xBuf  ),  fp  )  )  break;
		 trim(  xBuf  );
		 len  =  strlen(  xBuf  );
		 if  (  len  >  2  *  sizeof(  event  )  )  {
			 traceLogA(  "数据文件错误：记录太长了"  );  continue;
		 }
		 qyx2buf(  xBuf,  strlen(  xBuf  ),  (  char  *  )&event  );
		   
		 traceLogA(  "%s",  event.des0  );

		 len  =  sizeof(  encBuf  );
		 if  (  qnmEncData(  &pQyMc->commEncCtx,  (  char  *  )&event,  sizeof(  event  ),  encBuf,  &len  )  )  {
			 traceLogA(  "procDjData里qnmEncData failed."  );  goto  errLabel;
		 }		  

		 if  (  qySend(  &sock,  encBuf,  len,  pQyMc->cfg.to.iWrite  )  )  goto  errLabel;		 

		 uiSecChkEventSentCnt  ++  ;

		 if  (  !(  uiSecChkEventSentCnt  %  50  )  )  {
			  QY_COMM_RESP	resp;
			  char			buf[256];

			  memset(  &event,  0,  sizeof(  event  )  );
			  event.lEventType  =  -2;
			  qyhtonQnmSecChkEvent(  &event  );

			  len  =  sizeof(  encBuf  );
			  if  (  qnmEncData(  &pQyMc->commEncCtx,  (  char  *  )&event,  sizeof(  event  ),  encBuf,  &len  )  )  {
				  traceLogA(  "qrtSndThreadProc里qnmEncData failed."  );  goto  errLabel;
			  }		  

			  if  (  qySend(  &sock,  encBuf,  len,  pQyMc->cfg.to.iWrite  )  )  goto  errLabel;

			  if  (  qyRecvResp(  &session,  &sock,  &pQyMc->cfg.to,  &resp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;
			  
			  traceLogA(  "从管理端得到了接收顺利的响应"  );

		  }

		  //  发送顺利时，也抽空报个消息
		  if  (  !(  uiSecChkEventSentCnt  %  100  )  )  {
			  memset(  &cmdParam,  0,  sizeof(  cmdParam  )  );
			  cmdParam.uiSecChkEventCnt  =  uiSecChkEventSentCnt;
			  cmdParam.uiSecChkEventSentCnt  =  uiSecChkEventSentCnt;
			  _snprintf(  cmdParam.progressTxt,  sizeof(  cmdParam.progressTxt  ),  "%s",  "导入单机安检结果"  );
			  showQwmSvrStatus(  &pQyMc->env,  cntIp,  usCntPort,  CONST_qyServiceId_qwm,  ver,  &pQyMc->commEncCtx,  &pQyMc->cfg.to,  CONST_qwmSvrStatus_sndSecChkLogDetail,  &cmdParam  );
		  }

	}
	
	traceLogA(  "当发送日志完毕时，用发送lEventType为-1的事件表发送完毕"  );
	memset(  &event,  0,  sizeof(  event  )  );
	event.lEventType  =  -1;
	qyhtonQnmSecChkEvent(  &event  );		//  这里忘了加转换了，2005/05/02

	len  =  sizeof(  encBuf  );
	if  (  qnmEncData(  &pQyMc->commEncCtx,  (  char  *  )&event,  sizeof(  event  ),  encBuf,  &len  )  )  {
		traceLogA(  "qrtSndThreadProc里qnmEncData failed."  );  goto  errLabel;
	}		  

	qySend(  &sock,  encBuf,  len,  pQyMc->cfg.to.iWrite  );

	ucbFinished  =  TRUE;

errLabel:

	 if  (  fp  )  fclose(  fp  );

	 if  (  ucbMyFile  &&  (  !ucbFileOk  ||  ucbFinished  )  )  {
		 if  (  !DeleteFile(  CQyString(  fileName  ).GetBuffer(  0  )  )  )  {
			 qyDisplayLastError(  "procDjData"  );  goto  errLabel;
		 }
		 traceLogA(  "%s已删除",  fileName  );
	 }

	 if  (  bSessionOpen  )  qnmCloseSession(  &session,  &sock,  &pQyMc->cfg.to  );

	 if  (  ucbFileOk  &&  !ucbFinished  )   {
		 *  pbEnumOk  =  FALSE;  return  CONST_qyRet_quit;
	 }
	 return  0;
}


 //  这里应该调用qwmEnumUsrDir
 BOOL  bQnmImportDjData(  QY_IMEXPORTINFO  *  pImExport  )
{
	 BOOL				bRet		=		FALSE;
	 QY_MC			*	pQyMc		=		QY_GET_GBUF(  );
	 char			*	p0			=		NULL;
	 char			*	p1			=		NULL;
	 COMMON_PARAM		commonParam;
	 BOOL				bEnumOk		=		TRUE;
	 TCHAR				fileName[MAX_PATH  +  1];


	 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  ""  ),  _T(  "导入安检结果开始 ..."  ),  _T(  ""  )  ); 

	 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  ""  ),  _T(  "遍历 "  ),  CQyString(  pImExport->fileName  )  ); 

	 lstrcpyn(  fileName,  pImExport->fileName,  mycountof(  fileName  )  );		//  2006/04/22

	 MACRO_makeCommonParam3(  0,  fileName,  &bEnumOk,  commonParam  );  
	 qwmEnumUsrDir(  NULL,  fileName,  procDjData,  p0,  &commonParam  );  
	 if  (  !bEnumOk  )  goto  errLabel;

	 bRet  =  TRUE;

errLabel:

	 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  ""  ),  _T(  "导入结束"  ),  _T(  ""  )  ); 

	 return  bRet;

}
