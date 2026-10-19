

#include  "stdafx.h"

#include  "qmdCommon.h"

 int qmdInitServWork(  void * pSubThreadInfoParam,  void * reserved2  )
{
	int							iErr			=	-1;
	MT_SOCK_SUBTHREADINFO	*	pSubThreadInfo	=	(  MT_SOCK_SUBTHREADINFO *  )pSubThreadInfoParam;
	CQyMcDaemon				*	pDaemon			=	(  CQyMcDaemon  *  )pSubThreadInfo->pParentParam;
	CDatabase				*	pDb				=	NULL;
	CString						errStr;
	QY_SERVICE_CFG			*	pServiceCfg		=	(  QY_SERVICE_CFG  *  )pDaemon->getSpecialProperty(  CONST_qyPropertyId_serviceCfg,  (  void  *  )pSubThreadInfo->iServiceId,  0  );

	if  (  pSubThreadInfo->pDb  )  {
		traceLogA(  "qmdInitServWork(  ) failed: pSubThreadInfo->pDb is not NULL."  );  return  -1;
	}
	if  (  !pServiceCfg  )  {
		traceLogA(  "qmdInitServwork(  ) failed:  pServiceCfg is null"  );  return  -1;
	}

	TRY  {
		pDb = new CDatabase;
		if  (  !pDb  )  goto  errLabel;
		if  (  !pDb->OpenEx(  pServiceCfg->db.connectStr,  pServiceCfg->db.ulOpenOptions  )  )  {
			debugLog(  "localDb.OpenEx( %S ) failed.",  pServiceCfg->db.connectStr  );
			errStr  =  _T(  "打开数据库失败: "  );
			goto errLabel;
		}
		 
		}
	CATCH( CDBException, e ){		
		debugLog( "localDb.Open( ) failed: [%S]", e->m_strError );
		errStr  =  _T(  "打开数据库失败: "  )  +  e->m_strError;
		goto errLabel;
	}
	END_CATCH
	
	//  现在将pSubThreadInfo->pCfg指向pDaemon->var.cfg, 以后使用独立的缓存
	pSubThreadInfo->pCfg  =  &pDaemon->var.cfg;

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pDb  )  {
			if  (  pDb->IsOpen(  )  )  pDb->Close(  );
			delete  pDb;
		}

		qyShowInfo(  CONST_qyShowType_qwmComm,  0,  "",  _T(  "(Server)"  ),  NULL,  _T(  "服务线程初始化失败: "  ),  _T(  "%s"  ),  errStr  );

	}
	if  (  !iErr  )  {
		pSubThreadInfo->pDb  =  pDb;
	}
	return  iErr;
	
}


 int qmdExitServWork(  void * pSubThreadInfoParam,  void * reserved2  )
{
	MT_SOCK_SUBTHREADINFO	*	pSubThreadInfo	=	(  MT_SOCK_SUBTHREADINFO *  )pSubThreadInfoParam;
	CDatabase				*	pDb				=	(  CDatabase  *  )pSubThreadInfo->pDb;
	
	if  (  pDb  )  {
		if  (  pDb->IsOpen(  )  )  pDb->Close(  );
		delete  pDb;
	}
	pSubThreadInfo->pDb  =  NULL;

	 return  0;
}








