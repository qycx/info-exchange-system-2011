
#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<stdlib.h>
#include	<stdio.h>
#include	<stddef.h>
#include	<winsock2.h>
#include	<windows.h>
#include	<Wincrypt.h>

#include	"qyCommon.h"
#include	"qyCommCommon.h"
#include	"qyMsgFunc.h"
#include	"qyCommProc.h"
#include	"qyWmComm.h"
#include	"qnmCommProc.h"
#include	<tchar.h>
#include	"qmCrypt.h"
#ifndef  __WINCE__
	#include	<errno.h>
#else
	#include	"myerrno.h"

#ifndef  __TEST__
 int  tmp_errno  =  0;
 int * __cdecl _errno(void)
{
	return  &tmp_errno;
}
#endif

#endif



// Use select() to determine when
// data is waiting to be read
//  返回值：>  0  为有数据
//			== 0  为超时
//			<  0  为失败
 extern  "C"  int  qyWaitForRead(  int  fd,  int  timeout  )
{
	 while  (  true  )  {
    	    fd_set rfds;
   			struct timeval tv;
       
			tv.tv_sec = timeout / 1000;
    		tv.tv_usec = (timeout % 1000) * 1000;
    
			FD_ZERO(&rfds);
			FD_SET(fd, &rfds);
			int n = select(fd+1, &rfds, 0, 0, &tv);
			if  (  n  !=  -1  ||  errno  !=  EINTR  )  return  n;
			traceLogA(  "select returned EINTR"  );
	 }
}

 extern  "C"  int  qyWaitForWrite(  int  fd,  int  timeout  )
{
	 while  (  true  )  {
    	    fd_set wfds;
   			struct timeval tv;
       
			tv.tv_sec = timeout / 1000;
    		tv.tv_usec = (timeout % 1000) * 1000;
    
			FD_ZERO(&wfds);
			FD_SET(fd, &wfds);
			int n = select(fd+1, 0,  &wfds, 0, &tv);
			if  (  n  !=  -1  ||  errno  !=  EINTR  )  return  n;
			traceLogA(  "select returned EINTR"  );
	 }
}


#if  0  //  2010/04/24
 extern  "C"  int  qyRecvMsg(  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo,  QY_MSG_HEAD * pMsgHead,  char  *  dataBuf,  unsigned  int  bufSize  )
{
	 int				iErr		=	-1;
	 char			*	encBuf		=	NULL;
	 unsigned  int		encLen		=	CONST_maxReqDataLen_enc_is;		  

	 if  (  qyRecvX(  pSock, ( char * )pMsgHead,  sizeof(  QY_MSG_HEAD  ), pTo->iRead  )  )  goto  errLabel;
	 MACRO_ntohs(  pMsgHead->usLen  );
	 MACRO_ntohs(  pMsgHead->usCode  );
	 MACRO_ntohl64(  pMsgHead->i64StartTime  );	//  2007/05/07
	 MACRO_ntohl(  pMsgHead->uiTranNo  );
	 MACRO_ntohl(  pMsgHead->uiSeqNo  );
	 
	 if  (  !(  encBuf  =  (  char  *  )malloc(  encLen  )  )  )  goto  errLabel;

	 if  (  pMsgHead->usLen  >  encLen  )  {
		 traceLogA(  "qyRecvMsg err, dataLen [%d] > encLen [%d]",  pMsgHead->usLen,  encLen  );
		 goto  errLabel;
	 }
	 if  (  pMsgHead->usLen  )  {
	 	 if  (  qyRecvX(  pSock,  encBuf,  pMsgHead->usLen,  pTo->iRead  )  )  goto  errLabel;

		 if  (  pSession->service.encType  ==  CONST_qyEncType_qwm  )  {
			 if  (  qnmDecData(  &pSession->commEncCtx,  encBuf,  pMsgHead->usLen,  dataBuf,  &bufSize  )  )  {
				 traceLogA(  "qyRecvReq里qnmDecData failed"  );  goto  errLabel;
			 }
			 pMsgHead->usLen  =  bufSize;
			 }
		 else  if  (  pMsgHead->usLen  >  bufSize  )  {  
			       traceLogA(  "qyRecvMsg err, dataLen [%d] > bufSize [%d]",  pMsgHead->usLen,  bufSize  );
				   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  "",  _T(  "IsClient"  ),  _T(  ""  ),  _T(  ""  ),  _T(  "qyRecvMsg err. "  ),  _T(  "收到数据过大, dataLen [%d] "  ),  pMsgHead->usLen  );
				   iErr  =  -2;  goto  errLabel;  
				   }
		 else  
			 memcpy(  dataBuf,  encBuf,  pMsgHead->usLen  );
	 }

	 //
	 if  (  isUcFlgResp(  pMsgHead->ucFlg  )  )  pSession->usLastRespCode_i  =  pMsgHead->usCode;
	 else  pSession->usLastReqCode_i  =  pMsgHead->usCode;

	 iErr	=		0;

errLabel:

	 if  (  encBuf  )  free(  encBuf  );

	 return  iErr;

}
#endif
 
 
  extern  "C"  int  qyRecvMsg(  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo,  QY_MSG_HEAD * pMsgHead,  char  *  dataBuf,  unsigned  int  bufSize  )
{
	 int				iErr		=	-1;
	 char			*	encBuf		=	NULL;
	 unsigned  int		encLen		=	CONST_maxReqDataLen_enc_is;		  

	 if  (  qyRecvX(  pSock, ( char * )pMsgHead,  sizeof(  QY_MSG_HEAD  ), pTo->iRead  )  )  goto  errLabel;
	 MACRO_ntohl(  pMsgHead->uiLen  );
	 MACRO_ntohs(  pMsgHead->usCode  );
	 MACRO_ntohl64(  pMsgHead->i64StartTime  );	//  2007/05/07
	 MACRO_ntohl(  pMsgHead->uiTranNo  );
	 MACRO_ntohs(  pMsgHead->usSeqNo  );
	 
	 if  (  pMsgHead->uiLen  )  {

		 if  (  pSession->service.encType  ==  CONST_qyEncType_qwm  )  {

			 if  (  !(  encBuf  =  (  char  *  )malloc(  encLen  )  )  )  goto  errLabel;

			 if  (  pMsgHead->uiLen  >  encLen  )  {
				 traceLogA(  "qyRecvMsg err, dataLen [%d] > encLen [%d]",  pMsgHead->uiLen,  encLen  );
				 goto  errLabel;
			 }

			 if  (  qyRecvX(  pSock,  encBuf,  pMsgHead->uiLen,  pTo->iRead  )  )  goto  errLabel;

			 if  (  qnmDecData(  &pSession->commEncCtx,  encBuf,  pMsgHead->uiLen,  dataBuf,  &bufSize  )  )  {
				 traceLogA(  "qyRecvReq里qnmDecData failed"  );  goto  errLabel;
			 }
			 pMsgHead->uiLen  =  bufSize;

			 }  
		 else  {

			   if  (  pMsgHead->uiLen  >  bufSize  )  {  
			       traceLogA(  "qyRecvMsg err, dataLen [%d] > bufSize [%d]",  pMsgHead->uiLen,  bufSize  );
				   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  "",  _T(  "IsClient"  ),  _T(  ""  ),  _T(  ""  ),  _T(  "qyRecvMsg err. "  ),  _T(  "收到数据过大, dataLen [%d] "  ),  pMsgHead->uiLen  );
				   iErr  =  -2;  goto  errLabel;  		
			   }

			   if  (  qyRecvX(  pSock,  dataBuf,  pMsgHead->uiLen,  pTo->iRead  )  )  goto  errLabel;
		 }
	 }

	 //
	 if  (  isUcFlgResp(  pMsgHead->ucFlg  )  )  pSession->usLastRespCode_i  =  pMsgHead->usCode;
	 else  pSession->usLastReqCode_i  =  pMsgHead->usCode;

	 iErr	=		0;

errLabel:

	 if  (  encBuf  )  free(  encBuf  );

	 return  iErr;

}



 extern  "C"  int  qySendMsg(  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo,  unsigned  char  ucFlg,  unsigned  short  cmdCode,  time_t  uiStartTime,  unsigned  int  uiTranNo,  unsigned  short  usSeqNo,  char  *  data,  unsigned  int  dataLen  )
{
	 int					iErr		=	-1;
	 QY_MSG_HEAD			tmpHead;
	 char				*	encBuf		=	NULL;
	 unsigned  int			encLen		=	CONST_maxReqDataLen_enc_is;
	 
	 memset(  &tmpHead,  0,  sizeof(  tmpHead  )  );
	 tmpHead.usCode  =  qyhtons(  cmdCode  );
	 tmpHead.ucFlg  =  ucFlg;

	 if  (  !data  )  dataLen  =  0;

	 if  (  dataLen  )  {		//  2004/01/02里加入了加密的处理
		 if  (  pSession->service.encType  ==  CONST_qyEncType_qwm  )  {
			 
			 if  (  !(  encBuf  =  (  char  *  )malloc(  encLen  )  )  )  goto  errLabel;

			 if  (  qnmEncData(  &pSession->commEncCtx,  data,  dataLen,  encBuf,  &encLen  )  )  {
				 traceLogA(  "qySendReq里qnmEncData failed."  );  goto  errLabel;
			 }

			 //  {
			 //		 char  buf1[8192];  unsigned  int  len1  =  sizeof(  buf1  );
			 //		 qnmDecData(  &pSession->commEncCtx,  encBuf,  encLen,  buf1,  &len1  );
			 //	 }


			 data  =  encBuf;  dataLen  =  encLen;
		 }
	 }

	 tmpHead.uiLen  =  (  unsigned  int  )dataLen;
	 if  (  tmpHead.uiLen  !=  dataLen  )  {
		 traceLogA(  "dataLen"  );  goto  errLabel;		//  这里要防止dataLen是个过大的数
	 }
	 MACRO_htonl(  tmpHead.uiLen  );
	 tmpHead.i64StartTime  =  qyhtonl64(  uiStartTime  );	//  2007/05/07
	 tmpHead.uiTranNo  =  qyhtonl(  uiTranNo  );
	 tmpHead.usSeqNo  =  qyhtons(  usSeqNo  );			//  2007/05/02
	 if  (  qySend(  pSock,  (  char  *  )&tmpHead,  sizeof(  tmpHead  ),  pTo->iWrite  )  )  {
		 traceLogA(  "qySend msgHead failed"  );  goto  errLabel;
	 }
	 if  (  dataLen  )  {	
		 if  (  qySend(  pSock,  data,  dataLen,  pTo->iWrite  )  )  {
			 qyDisplayLastError(  "qySend data failed"  );  goto  errLabel;
		 }
	 }
 
	 iErr  =  0;
	 
errLabel:

	 if  (  encBuf  )  free(  encBuf  );

	 return  iErr;

}



 //  2008/06/09, usCmd固定使用CONST_qyCmd_tellService。
 //  extern  "C"  int  qyTellService_msg(  unsigned  int  serviceId,  char * version,  unsigned  short  usCmd,  void  *  pCommEncCtx,  char * data,  int dataLen,  QY_SOCK * pSock,  SOCK_TIMEOUT * pTo,  QY_COMM_SESSION * pSession )
 extern  "C"  int  qyTellService_msg(  unsigned  int  serviceId,  char * version,  void  *  pCommEncCtx,  unsigned  short  usCmd,  time_t  tStartTime,  unsigned  int  uiTranNo,  char * data,  int dataLen,  QY_SOCK * pSock,  SOCK_TIMEOUT * pTo,  QY_COMM_SESSION * pSession )
{
	 int					iErr			=		-1;
	 QY_COMM_SERVICE		service; 
	 int					len;
	 //  unsigned  int			uiStartTime		=		0;
	 //  unsigned  int			uiTranNo		=		0;		//
#ifdef  __DEBUG__		
#endif
	 
	 //  traceLogA(  "qyTellService(  ) enters."  );

	 if  (  !data  ||  dataLen  <=  0  )  return  -1;

	 //  清空pSession->service
	 memset(  &pSession->service,  0,  sizeof(  pSession->service  )  );

	 //  重新组织service
 	 memset(  &service,  ' ',  sizeof(  service  )  );
	 service.serviceId  =  serviceId;
	 MACRO_safeStrMemCpy(  version,  service.version,  sizeof(  service.version  )  );
	 if  (  pCommEncCtx  )  service.encType  =  (  (  QY_ENC_CTX  *  )pCommEncCtx  )->type;
	 else  service.encType  =  0;	 

	 switch  (  service.encType  )  {
		     case  CONST_qyEncType_rsa:  {	//  
				   ENC_CTX_session	*	pEncCtx  =  (  ENC_CTX_session  *  )pCommEncCtx;
	
				   //  这里应该用hPublicKey加密。
				   if  (  !pEncCtx  ||  !pEncCtx->key_rsa.hKey  )  goto  errLabel;
				   DWORD	dwBlockLen  =  pEncCtx->key_rsa.dwBlockLen_encrypt;
				   int		nIn  =  0;
				   int		nOut  =  0;
				   int		bufLen  =  0;

				   if  (  !dwBlockLen  )  goto  errLabel;

				   for  (  nIn  =  0,  nOut  =  0;  nIn  <  (  int  )dataLen  &&  nOut  <=  sizeof(  service.data  );  )  {
					    len  =  min(  dataLen  -  nIn,  (  int  )dwBlockLen  );

						memcpy(  service.data  +  nOut,  data  +  nIn,  len  );
						bufLen  =  len;

						if  (  !CryptEncrypt(  pEncCtx->key_rsa.hKey,  0,  (  len  >=  (  int  )(  dataLen  -  nIn  )  ),  0,  (  BYTE  *  )(  service.data  +  nOut  ),  (  DWORD  *  )&bufLen,  sizeof(  service.data  )  -  nOut  )  )  {
							qyDisplayLastError(  "qyTellService_msg CryptEncrypt failed."  );
							goto  errLabel;
						}

						nIn  +=  len;
						nOut  +=  bufLen;				   		 
				   }

				   dataLen  =  nOut;
				   }
				   break;
			 default:
				 	 dataLen  =  min(  dataLen,  sizeof(  service.data  )  );
					 memcpy(  service.data,  data,  dataLen  );
					 break;
	 }

	 MACRO_htonl(  service.serviceId  );
	 MACRO_htonl(  service.encType  );
	 
	 len  =  offsetof(  QY_COMM_SERVICE,  data  )  +  dataLen;		//  2007/04/19, 原来发送的len为sizeof(  service  ), 现在做了修改。主要为了让发送的数据能灵活控制
	 if  (  qySendMsg(  pSession,  pSock,  pTo,  0,  usCmd,  tStartTime,  uiTranNo,  0,  (  char  *  )&service,  len  )  )  goto  errLabel;

	 //  将service赋入pSession中
	 service.serviceId  =  serviceId;			//  
	 if  (  pCommEncCtx  )  service.encType  =  (  (  QY_ENC_CTX  *  )pCommEncCtx  )->type;	 
	 memcpy(  &pSession->service,  &service,  sizeof(  service  )  );
	 if  (  pCommEncCtx  )  memcpy(  &pSession->commEncCtx,  pCommEncCtx,  sizeof(  pSession->commEncCtx  )  );	//  2004/01/03添加对加密的支持
	 
	 iErr  =  0;

errLabel:

	 //  traceLogA(  "qyTellService(  ) leaves, %s",  iErr  ?  "失败"  :  "成功"  );

	 return  iErr;
	 
}


 extern  "C"  void  qnmCloseSession_msg(  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock,  SOCK_TIMEOUT  *  pTo  )
{
	 QY_MSG_HEAD			tmpResp;

	 traceLogA(  "qnmCloseSession_msg enters"  );

	 if  (  bQySockOpen(  pSock  )  )  {
		 if  (  isRcOk(  pSession->usLastRespCode_i  )  ||  pSession->usLastRespCode_i  ==  CONST_qyRc_user  )  {
			 if  (  !qySendMsg(  pSession,  pSock,  pTo,  0,  CONST_qyCmd_end,  0,  0,  0,  NULL,  0  )  )  {
				qyRecvMsg(  pSession,  pSock,  pTo,  &tmpResp,  NULL,  0  );
			 }
		 }
		 qyDisconnect(  pSock  );
	 }

	 traceLogA(  "qnmCloseSession_msg leaves"  );

	 return;
}



