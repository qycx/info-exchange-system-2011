 
#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyWmComm.h"
#include	"qyCusResTemp.h"

#if  10
  #include	"qyMc.h"
  #include	"qyMcDoc.h"

  #include	"leftView.h"
  #include	"qyMcView.h"

#endif
#include	"myDb.h"

BOOL  bItemExists_imObjs(  QY_OBJ_DB  *  pObjDb,  CLeftView  *  pLeftView,  HTREEITEM  htItem  );

int  displayListContent_imObjs(  void  *  p0,  void  *  p1,  void  *  p2  );
//
BOOL  bViewImGrpAuthList_isMgr(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );

BOOL  bViewImObjView_isMgr(  QY_OBJ_DB  *  pObjDb  );

//
BOOL  bViewImObjView_isCli_mdi(  QY_OBJ_DB  *  pObjDb  );

 BOOL  bViewImObjView(  QY_OBJ_DB  *  pObjDb  )
{
	 BOOL			bRet	=	FALSE;
	 QY_MC		*	pQyMc	=  QY_GET_GBUF(  );
#if  0
	 if  (  pObjDb->cfg.iAppType  ==  CONST_qyAppType_client  )  bRet  =  bViewImObjView_isCli_mdi(  pObjDb  );
	 else  bRet  =  bViewImObjView_isMgr(  pObjDb  );
#endif
	 #ifdef  __isCli__
			 bRet  =  bViewImObjView_isCli_mdi(  pObjDb  );
	 #else
			 bRet  =  bViewImObjView_isMgr(  pObjDb  );
	 #endif

	 return  bRet;
}


 BOOL  bViewPhoneMessengerList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	
	BOOL					bRet	=	FALSE;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpPhoneMessengerListQueryStruct  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_phoneMessengerList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  NULL,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from (((qyMessengerPhoneInfoTab left join qyImObjAuthTab on (qyMessengerPhoneInfoTab.misServName=qyImObjAuthTab.misServName and qyMessengerPhoneInfoTab.idStr=qyImObjAuthTab.idStr)) left join qyImObjTab as A on (qyImObjAuthTab.misServName=A.misServName and qyImObjAuthTab.idStr=A.idstr)) left join qyImObjRegInfoTab as B on(qyImObjAuthTab.misServName=B.misServName and qyImObjAuthTab.idStr=B.idStr ) )"  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "1=1"  )  );
	if  (  wherePart  &&  wherePart[0]  ) _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s and %s"  ),  tmpSel.u.query.wherePart,  CString(  wherePart  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "qyMessengerPhoneInfoTab.idStr"  )  );
	
	tmpSel.u.query.data2DisplayProc			=  displayQnmElement;
	tmpSel.u.query.pfProcEvent				=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId				=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos				=  CONST_resId_popup_viewPhoneMessengerList_isMgr;					//  2003/12/17修改
	tmpSel.u.query.ucbMultiSel				=  TRUE;															//  2007/08/24
	tmpSel.u.query.nSubMenuPos_multiSel		=  CONST_resId_popup_viewPhoneMessengerList_multiSel_isMgr;		//  200
	tmpSel.u.query.nSubMenuPos_notSel		=	CONST_resId_popup_viewPhoneMessengerList_notSel_isMgr;			//  2008/01/29	


	_sntprintf(  tmpSel.u.query.docName,  mycountof(  tmpSel.u.query.docName  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  " %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyPhoneMessengerList  )  );
	
	bRet  =  pApp->bNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}


#if  0	//  2011/01/29
 int  applyForServWork(  unsigned  int  uiContentType,  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int						iErr									=	-1;
	QY_MC				*	pQyMc									=	QY_GET_GBUF(  );
	char				*	servIp									=	"127.0.0.1";
	unsigned  short			usPort									=	DEFAULT_qyPort_mis;
	int						iServiceId								=	CONST_qyServiceId_is;
	QY_COMM_SESSION			session;
	QY_SOCK					sock;
	BOOL					bSessionOpen							=	FALSE;

	CQyMalloc				mallocObj_stream;
	IM_STREAM_CONTENT	*	pStream									=	(  IM_STREAM_CONTENT  *  )mallocObj_stream.malloc(  sizeof(  IM_STREAM_CONTENT  )  );
	if  (  !pStream  )  return  -1;
	IM_STREAM_CONTENT	&	stream									=	*pStream;
	IM_STREAM_CONTENT_nh	stream_ntoh;
	char				*	ptr;
	int						len;
	QY_MSG_HEAD				msgHead;
	QY_COMM_AUTHINFO_MIS	authInfo;
	
	if  (  !uiContentType  )  return  -1;

	memset(  &authInfo,  0,  sizeof(  authInfo  )  );
	//
	safeStrnCpy(  qnmVerStr(  pQyMc->iServiceId  ),  authInfo.ver,  mycountof(  authInfo.ver  )  );
	authInfo.usLangId  =  pQyMc->env.usLangId;		 
	authInfo.uiDevType  =  CONST_objType_pc;
	//
	//  safeStrnCpy(  CONST_qyNullMac,  (  char  *  )authInfo.macsInfo.macs[0],  mycountof(  authInfo.macsInfo.macs[0]  )  );	//  2007/10/10, 这样，就为管理员伪装了一个MAC
	//  authInfo.macsInfo.nMacs  =  1;
	//
	myStr2TChar(  pQyMc->curUsrInfo.name,  authInfo.messengerName,  mycountof(  authInfo.messengerName  )  );
	authInfo.uiChannelType  =  CONST_channelType_talking; 

	memset(  &session,  0,  sizeof(  session  )  );			//  2007/08/31, 新建组有时要失败。原因可能是sock没有初始化造成的
	clearQySock(  &sock  );

	qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "连接服务器 %s"  ),  CString(  servIp  )  );

	if  (  qnmOpenSession_mis(  servIp,  usPort,  &authInfo,  CONST_qnmAuthCmd_guiTalk,  CONST_channelType_talking,  "127.0.0.1",  iServiceId,  qnmVerStr(  iServiceId  ),  &pQyMc->commEncCtx,  &session,  &sock,  &pQyMc->cfg.to,  0,  0  )  )  {
		qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "连接服务器失败"  )  );
		goto  errLabel;
	}
	bSessionOpen  =  TRUE;

	switch  (  uiContentType  )  {
			case  CONST_imCommType_newImGrp:  {
				  IM_GRP_INFO				grpInfo;
				  TCHAR				*		grpName		=	(  TCHAR  *  )p0;

				  if  (  !grpName  )  goto  errLabel;

				  memset(  &grpInfo,  0,  sizeof(  grpInfo  )  );
				  lstrcpyn(  grpInfo.name,  grpName,  mycountof(  grpInfo.name  )  );

				  memset(  &stream,  0,  sizeof(  stream  )  );
				  stream.uiType  =  CONST_imCommType_streamContent;
				  stream.uiContentType  =  uiContentType;
				  len  =  sizeof(  stream.buf  );
				  if  (  imGrpInfo2Stream(  stream.uiContentType,  &grpInfo,  stream.buf,  (  unsigned  int  *  )&len  )  )  goto  errLabel;
				  stream.usStreamLen  =  len;
				  //
				  if  (  (  len  =  qyhtonImStreamContent(  0,  &stream  )  )  <  0  )  goto  errLabel;
				  if  (  qySendMsg(  &session,  &sock,  &pQyMc->cfg.to,  0,  CONST_qyCmd_refreshImObjListReq,  0, 0,  0,  (  char  *  )&stream,  len  )  )  goto  errLabel;
				  //
				  memset(  &stream,  0,  sizeof(  stream  )  );
				  if  (  qyRecvMsg(  &session,  &sock,  &pQyMc->cfg.to,  &msgHead,  (  char  *  )&stream,  sizeof(  stream  )  )  )  goto  errLabel;
				  if  (  (  len  =  qyntohImStreamContent(  0,  (  char  *  )&stream,  &stream_ntoh  )  )  <  0  )  goto  errLabel;
				  if  (  stream_ntoh.uiType  !=  CONST_imCommType_streamContent  )  goto  errLabel;
				  ptr  =  stream_ntoh.p;  len  =  stream_ntoh.usStreamLen;
				  memset(  &grpInfo,  0, sizeof(  grpInfo  )  );
				  if  (  stream2Data(  &ptr,  (  unsigned  int  *  )&len,  filterStream_is,  tmpHandler_stream2ImGrpInfo,  0,  &grpInfo  )  )  goto  errLabel;

				  traceLogA(  "新建的组号为%I64u",  grpInfo.idInfo.ui64Id  );

				  qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "建新组 %s ( %I64u ) OK"  ),  grpInfo.name,  grpInfo.idInfo.ui64Id  );
				  }
				  break;
			case  CONST_imCommType_refreshImGrp:  {
				  QY_MESSENGER_ID	*		pIdInfo_grp		=	(  QY_MESSENGER_ID  *  )p0;
				  //
				  IM_GRP_INFO				grpInfo;
				  IM_SIMPLE_RESP			resp;


				  if  (  !pIdInfo_grp  )  goto  errLabel;

				  memset(  &grpInfo,  0,  sizeof(  grpInfo  )  );
				  grpInfo.idInfo.ui64Id  =  pIdInfo_grp->ui64Id;

				  memset(  &stream,  0,  sizeof(  stream  )  );
				  stream.uiType  =  CONST_imCommType_streamContent;
				  stream.uiContentType  =  uiContentType;
				  len  =  sizeof(  stream.buf  );
				  if  (  imGrpInfo2Stream(  stream.uiContentType,  &grpInfo,  stream.buf,  (  unsigned  int  *  )&len  )  )  goto  errLabel;
				  stream.usStreamLen  =  len;
				  //
				  if  (  (  len  =  qyhtonImStreamContent(  0,  &stream  )  )  <  0  )  goto  errLabel;
				  if  (  qySendMsg(  &session,  &sock,  &pQyMc->cfg.to,  0,  CONST_qyCmd_refreshImObjListReq,  0, 0,  0,  (  char  *  )&stream,  len  )  )  goto  errLabel;
				  //
				  memset(  &resp,  0,  sizeof(  resp  )  );
				  if  (  qyRecvMsg(  &session,  &sock,  &pQyMc->cfg.to,  &msgHead,  (  char  *  )&resp,  sizeof(  resp  )  )  )  goto  errLabel;
				  if  (  !isRcOk(  msgHead.usCode  )  )  goto  errLabel;
				  if  (  (  len  =  qyntohImSimpleResp(  0,  &resp  )  )  <  0  )  goto  errLabel;
				  if  (  resp.uiContentType_org  !=  uiContentType  )  goto  errLabel;

				  qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "刷新组 ( %I64u ) OK"  ),  grpInfo.idInfo.ui64Id  );

				  }
				  break;
			default:
					goto  errLabel;
	}

	

	iErr  =  0;

errLabel:

	if  (  bSessionOpen  )  qnmCloseSession_msg(  &session,  &sock,  &pQyMc->cfg.to  );

	return  iErr;
}
#endif


 int  applyForServWork(  unsigned  int  uiContentType,  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int						iErr									=	-1;
	QY_MC				*	pQyMc									=	QY_GET_GBUF(  );
	MC_VAR_isMgr		*	pProcInfo								=	QY_GET_procInfo_isMgr(  );
	if  (  !pProcInfo  )  return  -1;
	char				*	servIp									=	"127.0.0.1";
	unsigned  short			usPort									=	DEFAULT_qyPort_mis;
	int						iServiceId								=	CONST_qyServiceId_is;
	QY_COMM_SESSION			session;
	QY_SOCK					sock;
	BOOL					bSessionOpen							=	FALSE;

	CQyMalloc				mallocObj_stream;
	IM_L_STREAM			*	pStream									=	(  IM_L_STREAM  *  )mallocObj_stream.malloc(  sizeof(  IM_L_STREAM  )  );
	if  (  !pStream  )  return  -1;
	IM_L_STREAM			&	stream									=	*pStream;
	IM_L_STREAM_nh			stream_ntoh;
	char				*	ptr;
	int						len;
	QY_MSG_HEAD				msgHead;
	QY_COMM_AUTHINFO_MIS	authInfo;
	
	if  (  !uiContentType  )  return  -1;

	memset(  &authInfo,  0,  sizeof(  authInfo  )  );
	//
	safeStrnCpy(  qnmVerStr(  pQyMc->iServiceId  ),  authInfo.ver,  mycountof(  authInfo.ver  )  );
	authInfo.usLangId  =  pQyMc->env.usLangId;		 
	authInfo.uiDevType  =  CONST_objType_pc;
	//
	//  safeStrnCpy(  CONST_qyNullMac,  (  char  *  )authInfo.macsInfo.macs[0],  mycountof(  authInfo.macsInfo.macs[0]  )  );	//  2007/10/10, 这样，就为管理员伪装了一个MAC
	//  authInfo.macsInfo.nMacs  =  1;
	//
	myStr2TChar(  pQyMc->curUsrInfo.name,  authInfo.messengerName,  mycountof(  authInfo.messengerName  )  );
	authInfo.uiChannelType  =  CONST_channelType_talking; 

	memset(  &session,  0,  sizeof(  session  )  );			//  2007/08/31, 新建组有时要失败。原因可能是sock没有初始化造成的
	clearQySock(  &sock  );

	qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "连接服务器 %s"  ),  CString(  servIp  )  );

#if  0
	if  (  qnmOpenSession_mis(  servIp,  usPort,  &authInfo,  CONST_qnmAuthCmd_guiTalk,  CONST_channelType_talking,  "127.0.0.1",  iServiceId,  qnmVerStr(  iServiceId  ),  &pQyMc->commEncCtx,  &session,  &sock,  &pQyMc->cfg.to,  0,  0  )  )  {
		qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "连接服务器失败"  )  );
		goto  errLabel;
	}
	bSessionOpen  =  TRUE;
#endif
	
	//  MIS
	CQyMalloc		mallocObj_pMsgReq;
	MIS_MSG_REQ	*	pMsgReq	=	(  MIS_MSG_REQ  *  )mallocObj_pMsgReq.malloc(  sizeof(  MIS_MSG_REQ  )  );
	if  (  !pMsgReq  )  goto  errLabel;

	MACRO_memset_misMsgReq(  pMsgReq  );

	pMsgReq->uiType  =  CONST_misMsgType_req;

	switch  (  uiContentType  )  {
			case  CONST_imCommType_newImGrp:  {
				  TCHAR				*		grpName		=	(  TCHAR  *  )p0;

				  if  (  !grpName  )  goto  errLabel;

				  IM_GRP_INFO  *  pReq;  pReq  =  (  IM_GRP_INFO  *  )&pMsgReq->data;
				  memset(  pReq,  0,  sizeof(  pReq[0]  )  );
				  pReq->uiType  =  uiContentType;
				  lstrcpyn(  pReq->name,  grpName,  mycountof(  pReq->name  )  );
				  //
				  pReq->tmpInternal.hWnd_status  =  NULL;	//  this->m_hWnd;

				  pMsgReq->lenInBytes  =  offsetof(  IM_GRP_INFO,  tmpInternal  )  +  sizeof(  pReq->tmpInternal  );

				  }
				  break;
			case  CONST_imCommType_refreshImGrp:  {
				  QY_MESSENGER_ID	*		pIdInfo_grp		=	(  QY_MESSENGER_ID  *  )p0;
				  //
				  //  IM_GRP_INFO				grpInfo;
				  IM_SIMPLE_RESP			resp;

				  if  (  !pIdInfo_grp  )  goto  errLabel;

				  IM_GRP_INFO  *  pReq;  pReq  =  (  IM_GRP_INFO  *  )&pMsgReq->data;
				  memset(  pReq,  0,  sizeof(  pReq[0]  )  );
				  pReq->uiType  =  uiContentType;
				  pReq->idInfo.ui64Id  =  pIdInfo_grp->ui64Id;
				  //
				  pReq->tmpInternal.hWnd_status  =  NULL;	//  this->m_hWnd;

				  pMsgReq->lenInBytes  =  offsetof(  IM_GRP_INFO,  tmpInternal  )  +  sizeof(  pReq->tmpInternal  );

				  }				  
				  break;
			default:
					goto  errLabel;
	}

#if  0
	switch  (  uiContentType  )  {
			case  CONST_imCommType_refreshImGrp:  {
				  QY_MESSENGER_ID	*		pIdInfo_grp		=	(  QY_MESSENGER_ID  *  )p0;
				  //
				  IM_GRP_INFO				grpInfo;
				  IM_SIMPLE_RESP			resp;


				  if  (  !pIdInfo_grp  )  goto  errLabel;

				  memset(  &grpInfo,  0,  sizeof(  grpInfo  )  );
				  grpInfo.idInfo.ui64Id  =  pIdInfo_grp->ui64Id;

				  memset(  &stream,  0,  sizeof(  stream  )  );
				  stream.uiType  =  CONST_imCommType_streamContent;
				  stream.uiContentType  =  uiContentType;
				  len  =  sizeof(  stream.buf  );
				  if  (  imGrpInfo2Stream(  stream.uiContentType,  &grpInfo,  stream.buf,  (  unsigned  int  *  )&len  )  )  goto  errLabel;
				  stream.usStreamLen  =  len;
				  //
				  if  (  (  len  =  qyhtonImStreamContent(  0,  &stream  )  )  <  0  )  goto  errLabel;
				  if  (  qySendMsg(  &session,  &sock,  &pQyMc->cfg.to,  0,  CONST_qyCmd_refreshImObjListReq,  0, 0,  0,  (  char  *  )&stream,  len  )  )  goto  errLabel;
				  //
				  memset(  &resp,  0,  sizeof(  resp  )  );
				  if  (  qyRecvMsg(  &session,  &sock,  &pQyMc->cfg.to,  &msgHead,  (  char  *  )&resp,  sizeof(  resp  )  )  )  goto  errLabel;
				  if  (  !isRcOk(  msgHead.usCode  )  )  goto  errLabel;
				  if  (  (  len  =  qyntohImSimpleResp(  0,  &resp  )  )  <  0  )  goto  errLabel;
				  if  (  resp.uiContentType_org  !=  uiContentType  )  goto  errLabel;

				  qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "刷新组 ( %I64u ) OK"  ),  grpInfo.idInfo.ui64Id  );

				  }
				  break;
			default:
					goto  errLabel;
	}

#endif

	MACRO_prepareForTran(  );

	pMsgReq->usCode  =  CONST_qyCmd_refreshImObjListReq;
	pMsgReq->tStartTime  =  tStartTran;
	pMsgReq->uiTranNo  =  uiTranNo;

	qPostMsgAndTrigger(  pMsgReq,  offsetof(  MIS_MSG_REQ,  data  )  +  pMsgReq->lenInBytes,  &pProcInfo->mgrQ  );  


	iErr  =  0;

errLabel:

	if  (  bSessionOpen  )  qnmCloseSession_msg(  &session,  &sock,  &pQyMc->cfg.to  );

	return  iErr;
}



#if  0	//  2013/02/20
 BOOL  bNewMessenger(  )
{
	BOOL					bRet		=		FALSE;
	CDlgMessenger				dlg;
	
	if  (  	dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
	
	bRet  =  TRUE;

errLabel:

	return  bRet;

}


 BOOL  bNewImGrp(  )
{
	BOOL					bRet		=		FALSE;
#ifndef  __isCli__
	CDlgImGrp				dlg;
	
	if  (  	dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
	
	bRet  =  TRUE;
#endif

errLabel:

	return  bRet;

}
#endif



 BOOL  bViewImGrpAuthList(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	 BOOL			bRet	=	FALSE;
	 QY_MC		*	pQyMc  =  QY_GET_GBUF(  );

#if 0
	 if  (  pObjDb->cfg.iAppType  ==  CONST_qyAppType_client  )  bRet  =  FALSE;
	 else  bRet  =  bViewImGrpAuthList_isMgr(  pObjDb,  docName,  wherePart  );
#endif
	 #ifdef  __isCli__
			 bRet  =  FALSE;
	 #else
			 bRet  =  bViewImGrpAuthList_isMgr(  pObjDb,  docName,  wherePart  );
	 #endif
	 return  bRet;
}


 BOOL  bViewMessengerList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL			bRet									=	FALSE;
	CString			titleStr;
	QY_MC		*	pQyMc	=	QY_GET_GBUF(  );

	if  (  docName  )  titleStr  =  CString(  docName  );
	titleStr  +=  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyMessengerList  );

	bRet  =  bViewImObjListFunc(  pObjDb,  titleStr,  wherePart  );

	return  bRet;

}

 BOOL  bViewImGrpList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL					bRet	=	FALSE;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
#if  0
	CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
#endif
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  ?  CONST_resId_gpImGrpListQueryStruct_isClient  :  CONST_resId_gpImGrpListQueryStruct_isMgr  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_imGrpList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  NULL,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from ((qyImObjTab left join qyImObjAuthTab on (qyImObjTab.misServName=qyImObjAuthTab.misServName and qyImObjTab.idStr=qyImObjAuthTab.idStr)  ) left join qyImGrpInfoTab on(qyImObjTab.misServName=qyImGrpInfoTab.misServName and qyImObjTab.idStr=qyImGrpInfoTab.idStr ) )"  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "qyImObjTab.uiType in(%d)"  ),  CONST_objType_imGrp  );
	if  (  wherePart  &&  wherePart[0]  ) _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s and %s"  ),  tmpSel.u.query.wherePart,  CQyString(  wherePart  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "qyImObjTab.idStr"  )  );
	
	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	tmpSel.u.query.pfProcEvent  =  netMc_procEvent;
	tmpSel.u.query.pfProcEvent_new  =  is_procEvent_new;
	tmpSel.u.query.uPopupMenuId  =  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos  =  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  ?  CONST_resId_popup_viewImGrpList_isClient  :  CONST_resId_popup_viewImGrpList_isMgr;		//  2003/12/17修改

	_sntprintf(  tmpSel.u.query.docName,  mycountof(  tmpSel.u.query.docName  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  " %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyImGrpList  )  );
	
#if  0
	bRet  =  pApp->bNewQueryView(  &tmpSel  );
#endif
	bRet  =  bQyMcNewQueryView(  &tmpSel  );  

errLabel:

	return  bRet;
	
}


#if 0
 BOOL  bViewImGrpMemList_isMgr(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL					bRet	=	FALSE;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpImGrpMemListQueryStruct_isMgr  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_imGrpMemList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  NULL,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from ((qyImGrpMemTab left join qyImObjAuthTab on (qyImGrpMemTab.misServName=qyImObjAuthTab.misServname and qyImGrpMemTab.idStr_mem=qyImObjAuthTab.idStr)) left join qyImGrpInfoTab on (qyImGrpMemTab.misServName=qyImGrpInfoTab.misServName and qyImGrpMemTab.idStr_grp=qyImGrpInfoTab.idStr)) left join qyImObjRegInfoTab  on (qyImGrpMemTab.misServName=qyImObjRegInfoTab.misServName and qyImGrpMemTab.idStr_mem=qyImObjRegInfoTab.idStr)"  )  );
	if  (  wherePart  &&  wherePart[0]  ) _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s"  ),  CString(  wherePart  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "qyImGrpMemTab.idStr_grp,qyImGrpMemTab.idStr_mem"  )  );
	
	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	tmpSel.u.query.pfProcEvent  =  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId  =  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos  =  CONST_resId_popup_viewImGrpMemList_isMgr;							//  2003/12/17修改
	tmpSel.u.query.ucbMultiSel  =  TRUE;
	tmpSel.u.query.nSubMenuPos_multiSel  =  CONST_resId_popup_viewImGrpMemList_multiSel_isMgr;		//  2003/12/17修改

	_sntprintf(  tmpSel.u.query.docName,  mycountof(  tmpSel.u.query.docName  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  " %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyImGrpMemList  )  );
	
	bRet  =  pApp->bNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}
#endif

 BOOL  bViewImGrpMemList_isClient(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL					bRet	=	FALSE;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
#if  0
	CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
#endif
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpImGrpMemListQueryStruct_isClient  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_imGrpMemList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  NULL,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from ((qyImGrpMemTab left join qyImObjTab on (qyImGrpMemTab.misServName=qyImObjTab.misServname and qyImGrpMemTab.idStr_grp=qyImObjTab.idStr)) left join qyImGrpInfoTab on (qyImGrpMemTab.misServName=qyImGrpInfoTab.misServName and qyImGrpMemTab.idStr_grp=qyImGrpInfoTab.idStr)) left join qyImObjRegInfoTab  on (qyImGrpMemTab.misServName=qyImObjRegInfoTab.misServName and qyImGrpMemTab.idStr_mem=qyImObjRegInfoTab.idStr)"  )  );
	if  (  wherePart  &&  wherePart[0]  ) _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s"  ),  CQyString(  wherePart  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "qyImGrpMemTab.idStr_grp,qyImGrpMemTab.idStr_mem"  )  );
	
	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	tmpSel.u.query.pfProcEvent  =  netMc_procEvent;
	tmpSel.u.query.pfProcEvent_new  =  is_procEvent_new;
	tmpSel.u.query.uPopupMenuId  =  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos  =  CONST_resId_popup_viewImGrpMemList_isClient;						//  2003/12/17修改
	//  tmpSel.u.query.ucbMultiSel  =  TRUE;
	//  tmpSel.u.query.nSubMenuPos_multiSel  =  CONST_resId_popup_viewImGrpMemList_multiSel;		//  2003/12/17修改

	_sntprintf(  tmpSel.u.query.docName,  mycountof(  tmpSel.u.query.docName  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  " %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyImGrpMemList  )  );
#if  0
	bRet  =  pApp->bNewQueryView(  &tmpSel  );
#endif
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}

#if  0
 BOOL  bViewImGrpMemList_isMgr(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  );
BOOL  bViewImGrpMemList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	BOOL					bRet	=	FALSE;

	if  (  pObjDb->cfg.iAppType  ==  CONST_qyAppType_client  )  bRet  =  bViewImGrpMemList_isClient(  pObjDb,  docName,  wherePart  );
	else  bRet  =  bViewImGrpMemList_isMgr(  pObjDb,  docName,  wherePart  );

	return  bRet;

}
#endif

 BOOL  bViewCustomerServiceOfficerList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,	LPCTSTR  wherePart  )
{
	BOOL					bRet	=	FALSE;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpCustomerServiceListQueryStruct_is  );
	//
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_customerServiceList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  NULL,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
#if  10
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from (qyCustomerServiceObjTab left join qyImObjAuthTab on (qyCustomerServiceObjTab.misServName=qyImObjAuthTab.misServname and qyCustomerServiceObjTab.idStr=qyImObjAuthTab.idStr)) left join qyImObjRegInfoTab  on (qyCustomerServiceObjTab.misServName=qyImObjRegInfoTab.misServName and qyCustomerServiceObjTab.idStr=qyImObjRegInfoTab.idStr)"  )  );
	if  (  wherePart  &&  wherePart[0]  ) _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s"  ),  CString(  wherePart  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "qyCustomerServiceObjTab.idStr"  )  );
#endif
	
	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	tmpSel.u.query.pfProcEvent  =  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId  =  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos  =  CONST_resId_popup_customerServiceList_isMgr;							//  2003/12/17修改
	//  tmpSel.u.query.ucbMultiSel  =  TRUE;
	//  tmpSel.u.query.nSubMenuPos_multiSel  =  CONST_resId_popup_viewImGrpMemList_multiSel_isMgr;		//  2003/12/17修改

	_sntprintf(  tmpSel.u.query.docName,  mycountof(  tmpSel.u.query.docName  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_customerServiceList  )  );
	
	bRet  =  pApp->bNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
}


 BOOL  bViewWebContactList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,	LPCTSTR  wherePart  )
{
	BOOL					bRet	=	FALSE;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpWebContactListQueryStruct_is  );
	//
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_wwwQmCfgList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  NULL,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from (qyWebContactTab left join qyImObjAuthTab on (qyWebContactTab.misServName=qyImObjAuthTab.misServname and qyWebContactTab.idStr=qyImObjAuthTab.idStr)) left join qyImObjRegInfoTab  on (qyWebContactTab.misServName=qyImObjRegInfoTab.misServName and qyWebContactTab.idStr=qyImObjRegInfoTab.idStr)"  )  );
	if  (  wherePart  &&  wherePart[0]  ) _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s"  ),  CString(  wherePart  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "qyWebContactTab.idStr"  )  );
	
	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	tmpSel.u.query.pfProcEvent  =  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId  =  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos  =  CONST_resId_popup_wwwQmCfgList_isMgr;							//  2003/12/17修改
	//  tmpSel.u.query.ucbMultiSel  =  TRUE;
	//  tmpSel.u.query.nSubMenuPos_multiSel  =  CONST_resId_popup_viewImGrpMemList_multiSel_isMgr;		//  2003/12/17修改

	_sntprintf(  tmpSel.u.query.docName,  mycountof(  tmpSel.u.query.docName  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_wwwQmCfgList  )  );
	
	bRet  =  pApp->bNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
}





 BOOL  bViewIpKnowledgeList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,	LPCTSTR  wherePart  )
{
	BOOL					bRet	=	FALSE;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpIpKnowledgeListQueryStruct_is  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_ipKnowledgeList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  NULL,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from qyIpKnowledgeTab"  )  );
	if  (  wherePart  &&  wherePart[0]  ) _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s"  ),  CString(  wherePart  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "qyIpKnowledgeTab.startIp,qyIpKnowledgeTab.iWeight "  )  );
	
	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	tmpSel.u.query.pfProcEvent  =  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId  =  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos  =  CONST_resId_popup_cfgPcModuleKnowlege;							//  2003/12/17修改
	tmpSel.u.query.nSubMenuPos_notSel  =  CONST_resId_popup_cfgPcModuleKnowlege_notSel;
	//  tmpSel.u.query.ucbMultiSel  =  TRUE;
	//  tmpSel.u.query.nSubMenuPos_multiSel  =  CONST_resId_popup_viewImGrpMemList_multiSel_isMgr;		//  2003/12/17修改
	tmpSel.u.query.uiDefaultCmd  =  ID_qyProp_pcModuleKnowlege;

	_sntprintf(  tmpSel.u.query.docName,  mycountof(  tmpSel.u.query.docName  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_procIpKnowledge  )  );
	
	bRet  =  pApp->bNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
}


 BOOL  bViewPhoneGuestList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,	LPCTSTR  wherePart  )
{
	BOOL					bRet	=	FALSE;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  CONST_resId_gpPhoneGuestListQueryStruct_is  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_phoneGuestList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  NULL,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from qyPhoneGuestTab left join qyImOtherRegInfoTab on (qyPhoneGuestTab.uiDevType=qyImOtherRegInfoTab.uiDevType and qyPhoneGuestTab.wDevIdStr=qyImOtherRegInfotab.wDevIdStr)"  )  );
	if  (  wherePart  &&  wherePart[0]  ) _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s"  ),  CString(  wherePart  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "qyPhoneGuestTab.startTime "  )  );
	
	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	tmpSel.u.query.pfProcEvent  =  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId  =  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos  =  CONST_resId_popup_phoneGuestList;						//  2003/12/17修改
	tmpSel.u.query.nSubMenuPos_notSel  =  CONST_resId_popup_commonList_notSel;
	tmpSel.u.query.ucbMultiSel  =  TRUE;
	tmpSel.u.query.nSubMenuPos_multiSel  =  CONST_resId_popup_phoneGuestList_multiSel;		//  2003/12/17修改
	//  tmpSel.u.query.uiDefaultCmd  =  ID_qyProp_pcModuleKnowlege;

	_sntprintf(  tmpSel.u.query.docName,  mycountof(  tmpSel.u.query.docName  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyPhoneGuestList  )  );
	
	bRet  =  pApp->bNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
}

  //  2013/02/20
 BOOL  bViewImObjListFunc(   QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  wherePart  )
{
	BOOL					bRet			=	FALSE;
	QY_MC				*	pQyMc			=	QY_GET_GBUF(  );
#if  0
	CQyMcApp			*	pApp			=	(  CQyMcApp  *  )AfxGetApp(  );
#endif
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  ?  CONST_resId_gpImObjListQueryStruct_isClient  :  CONST_resId_gpImObjListQueryStruct_isMgr  );
	
	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_imObjList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  NULL,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
	 
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from ((qyImObjTab as A left join qyMessengerPhoneInfoTab on (A.misServName=qyMessengerPhoneInfoTab.misServName and A.idStr=qyMessengerPhoneInfoTab.idStr)) left join qyImObjAuthTab on (A.misServName=qyImObjAuthTab.misServName and A.idStr=qyImObjAuthTab.idStr)) left join qyImObjRegInfoTab as B on (A.misServName=B.misServName and A.idStr=B.idStr) "   )  );
	_sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "A.uiType not in(%d)"  ),  CONST_objType_imGrp  );
	if  (  wherePart  &&  wherePart[0]  ) _sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  "%s and %s"  ),  tmpSel.u.query.wherePart,  CQyString(  wherePart  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "A.idStr"  )  );
	
	tmpSel.u.query.data2DisplayProc  =  displayQnmElement;
	tmpSel.u.query.pfProcEvent  =  netMc_procEvent;
	tmpSel.u.query.pfProcEvent_new  =  is_procEvent_new;
	tmpSel.u.query.uPopupMenuId  =  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos  =  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  ?  CONST_resId_popup_viewMessengerList_isClient  :  CONST_resId_popup_viewMessengerList_isMgr;		//  2003/12/17修改
	tmpSel.u.query.ucbMultiSel  =  TRUE;
	tmpSel.u.query.nSubMenuPos_multiSel  =  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  ?  CONST_resId_popup_viewMessengerList_multiSel_isClient  :  CONST_resId_popup_viewMessengerList_multiSel_isMgr;
	tmpSel.u.query.uiDefaultCmd  =  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  ?  ID_qyTalk  :  ID_qyProperties;

	_sntprintf(  tmpSel.u.query.docName,  mycountof(  tmpSel.u.query.docName  ),  _T(  "%s"  ),  docName  );
	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  "%s"  ),  _T(  ""  )  );
#if  0	
	bRet  =  pApp->bNewQueryView(  &tmpSel  );
#endif
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}


  //  2013/02/20
 BOOL  bViewMessengerRegInfoList(  QY_OBJ_DB  *  pObjDb  )
{
	BOOL					bRet			=	FALSE;
	QY_MC				*	pQyMc			=	QY_GET_GBUF(  );
#if  0
	CQyMcApp			*	pApp			=	(  CQyMcApp  *  )AfxGetApp(  );
#endif
	QY_MC_SEL				tmpSel;
	BOOL					bClient			=	pQyMc->iAppType  ==  CONST_qyAppType_client;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &pQyMc->cusRes,  bClient  ?  CONST_resId_gpImObjUsrListQueryStruct_isClient  :  CONST_resId_gpImObjUsrListQueryStruct_isMgr  );

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_imObjRegInfoList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
													//				0					1					2		  3			 4					5			6			7				8
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  " from qyImObjRegInfoTab as B left join qyImObjTab as A on (A.misServName=B.misServName and A.idStr=B.idStr) "  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  ""  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "B.col0"  )  );
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.pfProcEvent_new		=  is_procEvent_new;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  bClient  ?  CONST_resId_popup0  :  CONST_resId_popup_viewPcUsrList;

	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyPcUsrList2  )  );
#if  0	
	bRet  =  pApp->bNewQueryView(  &tmpSel  );
#endif
	bRet  =  bQyMcNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}


 BOOL  bViewMessengerRegInfoInTab1List(  QY_OBJ_DB  *  pObjDb  )
{
	BOOL					bRet	=	FALSE;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  (  pQyMc->iAppType  ==  CONST_qyAppType_client  )  ?  CONST_resId_gpImObjUsrInTab1ListQueryStruct_isClient  :  CONST_resId_gpImObjUsrInTab1ListQueryStruct_isMgr  );

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_imObjRegInfoInTab1List;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
													//				0					1					2		  3			 4					5			6			7				8
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  " from qyImObjRegInfoTab1 as B left join qyImObjTab as A on (A.misServName=B.misServName and A.idStr=B.idStr) "  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  ""  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "B.col0"  )  );
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  7;


	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_qyMessengerAuthList_needAudited  )  );
	
	bRet  =  pApp->bNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}


#if  0
 BOOL  bViewSharedDynBmpList_isMgr(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause  )
{
	BOOL					bRet	=	FALSE;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpSharedDynBmpListQueryStruct_isMgr  );

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_sharedDynBmpList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
													//				0					1					2		  3			 4					5			6			7				8
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from qyDynBmpTab left join qyImObjRegInfoTab on (qyDynBmpTab.misServName=qyImObjRegInfoTab.misServName and qyDynBmpTab.idStr=qyImObjRegInfoTab.idStr)"  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  ""  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "qyImObjRegInfoTab.col0,qyDynBmpTab.idStr,qyDynBmpTab.usIndex"  )  );
	
	tmpSel.u.query.data2DisplayProc			=  displayQnmElement;
	tmpSel.u.query.pfProcEvent				=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId				=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos				=  CONST_resId_popup_sharedDynBmpList_isMgr;
	tmpSel.u.query.ucbMultiSel				=  TRUE;															//  2007/08/24
	tmpSel.u.query.nSubMenuPos_multiSel		=  CONST_resId_popup_sharedDynBmpList_multiSel_isMgr;			//  200
	//  tmpSel.u.query.nSubMenuPos_notSel		=	CONST_resId_popup_sharedDynBmpList_notSel_isMgr;		//  2008/01/29	



	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_sharedDynBmpList  )  );
	
	bRet  =  pApp->bNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}
#endif


  BOOL  bViewSharedDynBmpRuleList(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  docName,  LPCTSTR  whereClause  )
{
	BOOL					bRet	=	FALSE;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	CQyMcApp			*	pApp	=	(  CQyMcApp  *  )AfxGetApp(  );
	QY_MC_SEL				tmpSel;
	QNM_QUERY_STRUCT	*	pQueryStruct	=	(  QNM_QUERY_STRUCT  *  )getResQueryStruct(  0,  &g_pQyMc->cusRes,  CONST_resId_gpSharedDynBmpRuleListQueryStruct_isMgr  );

	if  (  !bObjDbAvail(  pObjDb  )  )  goto  errLabel;

	memset(  &tmpSel,  0,  sizeof(  tmpSel  )  );
	tmpSel.type					=	CONST_qySelType_mcQuery;
	tmpSel.u.query.type			=	CONST_qyQueryType_sharedDynBmpRuleList;
	tmpSel.u.query.iDsnIndex	=	pObjDb->iDsnIndex;

	if  (  setQueryColumns(  0,  pQueryStruct,  &tmpSel.u.query  )  )  goto  errLabel;
													//				0					1					2		  3			 4					5			6			7				8
	//
	_sntprintf(  tmpSel.u.query.fromPart,  mycountof(  tmpSel.u.query.fromPart  ),  _T(  "from ((qyDynBmpRuleTab left join qyImObjRegInfoTab on (qyDynBmpRuleTab.misServName=qyImObjRegInfoTab.misServName and qyDynBmpRuleTab.idStr=qyImObjRegInfoTab.idStr)) left join qyImObjRegInfoTab as B on (qyDynBmpRuleTab.misServName=B.misServName and qyDynBmpRuleTab.idStr_visitor=B.idStr)) left join qyImGrpInfoTab on (qyDynBmpRuleTab.misServname=qyImGrpInfoTab.misServName and qyDynBmpRuleTab.idStr_visitor=qyImGrpInfoTab.idStr)"  )  );
	_sntprintf(  tmpSel.u.query.wherePart,  mycountof(  tmpSel.u.query.wherePart  ),  _T(  ""  )  );
	_sntprintf(  tmpSel.u.query.sortPart,  mycountof(  tmpSel.u.query.sortPart  ),  _T(  "qyImObjRegInfoTab.col0,qyDynBmpRuleTab.idStr"  )  );
	
	tmpSel.u.query.data2DisplayProc		=  displayQnmElement;
	tmpSel.u.query.pfProcEvent			=  netMc_procEvent;
	tmpSel.u.query.uPopupMenuId			=  IDR_QYMCPOPUP;
	tmpSel.u.query.nSubMenuPos			=  CONST_resId_popup_sharedDynBmpRuleList_isMgr;


	_sntprintf(  tmpSel.u.query.postDocName,  mycountof(  tmpSel.u.query.postDocName  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_sharedDynBmpRuleList  )  );
	
	bRet  =  pApp->bNewQueryView(  &tmpSel  );

errLabel:

	return  bRet;
	
}
  int  getSthForObjs(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  tabName_regInfo,  QY_OBJINDEX_RCD  *  pObjIndex,  int  *  pIndexDisplayed,  int  *  pIndexToDisplay,  int  *  piObjTypeToDisplay,  TCHAR  *  whereClause,  unsigned  int  size  )
{
	 int					iRet					=		-1;
	 QY_OBJINDEX_RCD		objIndex;
	 int					zbIndex,  bbIndex,  dwIndex,  bmIndex,  syrIndex;
	 int					indexDisplayed,  indexToDisplay;
	 int					iObjTypeToDisplay;
	 int					iDataType_displayed		=		SQL_VARCHAR;
	 int					iDbType;
	QM_dbFuncs		*	pDbFuncs	=	QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;

	 if  (  !bObjDbAvail(  pObjDb  )  ||  !tabName_regInfo  )  goto  errLabel;
	 iDbType  =  pObjDb->cfg.iDbType;

	 if  (  (  zbIndex  =  getRegIndexByFieldId(  CONST_fieldId_zb  )  )  <  0  )  goto  errLabel;
	 if  (  (  bbIndex  =  getRegIndexByFieldId(  CONST_fieldId_bb  )  )  <  0  )  goto  errLabel;
	 if  (  (  dwIndex  =  getRegIndexByFieldId(  CONST_fieldId_dw  )  )  <  0  )  goto  errLabel;
	 if  (  (  bmIndex  =  getRegIndexByFieldId(  CONST_fieldId_bm  )  )  <  0  )  goto  errLabel;
	 if  (  (  syrIndex =  getRegIndexByFieldId(  CONST_fieldId_syr  )  )  <  0  )  goto  errLabel;
	 
	 switch  (  pObjIndex->objType  )  {
	 		 case  CONST_objType_bm:
				   indexDisplayed  =  bmIndex;  iDataType_displayed  =  SQL_WVARCHAR;  indexToDisplay  =  syrIndex;  iObjTypeToDisplay  =  CONST_objType_syr;
				   break;
			 case  CONST_objType_dw:
				   indexDisplayed  =  dwIndex;  iDataType_displayed  =  SQL_WVARCHAR;  indexToDisplay  =  bmIndex;  iObjTypeToDisplay  =  CONST_objType_bm;
				   break;	
			 case  CONST_objType_bb:
				   indexDisplayed  =  bbIndex;  iDataType_displayed  =  SQL_WVARCHAR;  indexToDisplay  =  dwIndex;  iObjTypeToDisplay  =  CONST_objType_dw;
				   break;	
			 case  CONST_objType_zb:
				   indexDisplayed  =  zbIndex;  iDataType_displayed  =  SQL_WVARCHAR;  indexToDisplay  =  bbIndex;  iObjTypeToDisplay  =  CONST_objType_bb;
				   break;	
			 default:	goto  errLabel;
	 }
	 if  (  whereClause  &&  size  )  {
		 tTrim(  whereClause  );
	 	 if  (  whereClause[0]  )  _sntprintf(  whereClause,  size,  _T(  "%s and"  ),  whereClause  );
	 	 _sntprintf(  whereClause,  size,  _T(  "%s %s.col%d=%s"  ),  whereClause,  tabName_regInfo,  indexDisplayed,  getDbValStr(  iDbType,  iDataType_displayed,  pObjIndex->objIdStr0  )  );
	 	 if  (  pObjIndex->objId0  )  {
			 if  (  g_dbFuncs.pf_getObjIndex(  pObjDb,  pObjIndex->objId0,  &objIndex  )  )  goto  errLabel;
			 if  (  getSthForObjs(  pObjDb,  tabName_regInfo,  &objIndex,  NULL,  NULL,  NULL,  whereClause,  size  )  )  goto  errLabel;
		 }
	 }
	 iRet  =  0;
errLabel:
	 if  (  !iRet  )  {
		 if  (  pIndexDisplayed  )  *pIndexDisplayed  =  indexDisplayed;
		 if  (  pIndexToDisplay  )  *pIndexToDisplay  =  indexToDisplay;
		 if  (  piObjTypeToDisplay  )  *piObjTypeToDisplay  =  iObjTypeToDisplay;
	 }
	 return  iRet;
}

 BOOL  bItemExists_imObjs(  QY_OBJ_DB  *  pObjDb,  CLeftView  *  pLeftView,  HTREEITEM  htItem  )
{
	 BOOL				bRet								=	FALSE;
	 QY_MC			*	pQyMc								=	QY_GET_GBUF(  );
	 int				iObjId								=	pLeftView->m_TreeCtrl->GetItemData(  htItem  );
	 QY_OBJINDEX_RCD	objIndex;
	 TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	 int				indexDisplayed,  indexToDisplay;
	 TCHAR				whereClause[1024]					=	_T(  ""  );
	 //
	 TCHAR			*	pObjTab								=	CONST_tabName_qyImObjTab;
	 TCHAR			*	pRegInfoTab							=	CONST_tabName_qyImObjRegInfoTab;
	QM_dbFuncs		*	pDbFuncs	=	QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;
	 
	 if  (  g_dbFuncs.pf_getObjIndex(  pObjDb,  iObjId,  &objIndex  )  )  goto  errLabel;  

	 switch  (  objIndex.objType  )  {
			 case  CONST_objType_zb:
			 case  CONST_objType_bb:
			 case  CONST_objType_col2:
			 case  CONST_objType_col3:
				   if  (  getSthForObjs(  pObjDb,  _T(  "B"  ),  &objIndex,  &indexDisplayed,  &indexToDisplay,  NULL,  whereClause,  mycountof(  whereClause  )  )  )  goto  errLabel;
		   		   _sntprintf(  sqlBuf,  sizeof(  sqlBuf  )  /  sizeof(  sqlBuf[0]  ),  _T(  "select count(B.id) from %s as B  where  %s"  ),  pRegInfoTab,  whereClause  );
				   break;
			 case  CONST_objType_col4:
				   _sntprintf(  sqlBuf,  sizeof(  sqlBuf  )  /  sizeof(  sqlBuf[0]  ),  _T(  "select count(B.id) from %s as B where B.idStr='%s'"  ),  pRegInfoTab,  objIndex.objIdStr0  );
				   break;
			 case  CONST_objType_unRegGrp:
				   bRet  =  TRUE;  goto  errLabel;
			 case  CONST_objType_unRegPc:
				   _sntprintf(  sqlBuf,  sizeof(  sqlBuf  )  /  sizeof(  sqlBuf[0]  ),  _T(  "SELECT count(A.id) from %s as A where A.idStr not in( select B.idStr from %s as B) and A.idStr='%s'"  ),  pObjTab,  pRegInfoTab,  objIndex.objIdStr0  );
				   break;
			 case  CONST_objType_messenger:  {
				   MIS_CNT				*	pMisCnt	=  NULL;
				   QY_MESSENGER_ID			idInfo;
				   char						idStr[CONST_qyMessengerIdStrLen  +  1]	=	"";

				   pMisCnt  =  getMisCntByName(  pQyMc,  NULL,  objIndex.objIdStr0  );
				   if  (  !pMisCnt  )  goto  errLabel;
				   if  (  !myTChar2Str(  objIndex.objIdStr1,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
				   if  (  !idStr2Info(  idStr,  &idInfo  )  )  goto  errLabel;
				   if  (  idInfo.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  goto  errLabel;	//  Õâ¾ä»°±íÃ÷£¬ÎÒÕâ¸ö×Ö¶ÎÔÚÎ´×¢²áµÄmessengerÀïÊÇ²»´æÔÚµÄ¡£µ«ÊÇ¿ÉÒÔÔÚ×¢²áµÄ×éÀï´æÔÚ£¬ÒòÎªÕâ¿ÉÒÔ²»Ó°ÏìÒ»¸ö×éµÄÍêÕûÐÔ
				   }
				   bRet  =  TRUE;  goto  errLabel;
				   break;
			 default:
					//  ÕâÀï¼ÙÉè£¬ÐèÒª¼ìÑéµÄ¶¼ÒªÖ¸¶¨
				    bRet  =  TRUE;  goto  errLabel;
	 }
	 if  (  !bSqlObjExists(  pObjDb->pDb,  CString(  sqlBuf  ).GetBuffer(  0  )  )  )  goto  errLabel;

	 bRet  =  TRUE;
errLabel:

	 traceLogA(  "½Úµã[%d] %S %S %S %s",  objIndex.objType,  objIndex.objIdStr0,  objIndex.objIdStr1,  objIndex.objIdStr2,  (  bRet  ?  "´æÔÚ"  :  "²»´æÔÚ"  )  );

	 return  bRet;
}



