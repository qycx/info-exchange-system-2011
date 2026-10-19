
#include  "stdafx.h"
#include  <sys/types.h>
#include  <sys/stat.h>
#include  "qmdCommon.h"







//  2007/09/12, 专门用来记录日志或其他消息的线程
 DWORD  WINAPI  qmdLogThreadProc(  LPVOID  lpParameter  )
{
	DWORD				dwRet;
	CQyMcDaemon		*	pDaemon									=	(  CQyMcDaemon  *  )lpParameter;
	int					iServiceId								=		pDaemon->var.iServiceId;
	QY_SERVICE_INFO	*	pServiceInfo							=		(  QY_SERVICE_INFO  *  )pDaemon->getSpecialProperty(  CONST_qyPropertyId_serviceInfo_byServiceId,  (  void  *  )iServiceId,  0  );
	if  (  !pServiceInfo  ||  !pServiceInfo->pObjQ  ||  !pServiceInfo->ucbVarInited  )  return  -1;
	//
	GENERIC_Q		*	pLogQ									=	&pDaemon->var.logQ;
	unsigned  int		len;
	CQyMalloc			mallocObj;
	MIS_MSGU		*	pMsg									=	NULL;
	
	traceLogA(  "qmdLogThreadProc starts"  );

	CDatabase			tmpDb;
	MT_SUBTHREADINFO	tmpThreadInfo;
	int					loopCnt			=		0;
	
	traceLogA(  "qmdProcessingThreadProc ..  enters."  );

	TRY  {
		if  (  !tmpDb.OpenEx(  pServiceInfo->cfg.db.connectStr,  CONST_qyDbOpenOptions  )  )  {
			traceLogA(  "localDb.OpenEx( %s ) failed.",  pServiceInfo->cfg.db.connectStr  );
			goto errLabel;
		}
		}
	CATCH  (  CDBException,  e  )  {		
		debugLog( "localDb.Open( ) failed: [%s]", e->m_strError );
		goto errLabel;
	}
	END_CATCH
		
	memset(  &tmpThreadInfo,  0,  sizeof(  tmpThreadInfo  )  );
	tmpThreadInfo.pParentParam	=  (  void  *  )pDaemon;
	tmpThreadInfo.pDb			=  &tmpDb;

	if  (  !(  pMsg  =  (  MIS_MSGU  *  )mallocObj.malloc(  sizeof(  MIS_MSGU  )  )  )  )  goto  errLabel;
	 
	while  (  !pDaemon->bQuit(  )  )  {

		   //  2006/06/03
		   dwRet  =  WaitForSingleObject(  pLogQ->hSemaTrigger,  5000  );
		   if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;
		   //  超时也要接着处理，以getMsg为准
		   
		   for  (  ;  !pDaemon->bQuit(  );  )  {
			    len  =  sizeof(  pMsg[0]  );
				if  (  qGetMsg(  pLogQ,  pMsg,  &len  )  )  break;

				//
				switch  (  pMsg->uiType  )  {
						case  CONST_misMsgType_imMsgRcd:

							  logImMsg(  tmpThreadInfo.pDb,  pServiceInfo->cfg.db.iDbType,  CONST_fieldIdTable_en,  &pMsg->imMsgRcd.rcd  );
							  
							  break;
						case  CONST_misMsgType_event:
							  logEvent_is(  tmpThreadInfo.pDb,  pServiceInfo->cfg.db.iDbType,  NULL,  &pMsg->event.event  );
							  break;
						default:
								traceLogA(  "其他消息暂不处理"  );
								break;
				}
						   
				dwRet  =  WaitForSingleObject(  pLogQ->hSemaTrigger,  50  );
		   		if  (  dwRet  ==  WAIT_FAILED  )  goto  errLabel;		   
		   
		   }
	
		   
	}
  
errLabel:

	if ( tmpDb.IsOpen(  )  ) tmpDb.Close(  );

	if  (  !pDaemon->bQuit(  )  )  {
		pDaemon->notifyPanic(  );
		debugLog(  "qyPutLogInfoDbThreadProc(  ):  notifyPanic."  );
	}

	traceLogA(  "qmdLogThreadProc ends"  );

	return  0;
}
