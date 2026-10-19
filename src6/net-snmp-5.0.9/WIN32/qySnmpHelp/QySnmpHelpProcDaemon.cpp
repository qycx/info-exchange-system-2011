// QySnmpHelpProcDaemon.cpp: implementation of the CQySnmpHelpProcDaemon class.
//
//////////////////////////////////////////////////////////////////////

#include	"stdafx.h"
#include	"qySnmpHelpProcCommon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQySnmpHelpProcDaemon::CQySnmpHelpProcDaemon()
{
	memset(  &var,  0,  sizeof(  var  )  );
}

CQySnmpHelpProcDaemon::~CQySnmpHelpProcDaemon()
{

}

 int  CQySnmpHelpProcDaemon::getInitialCfg(  )
{
	 int	iErr  =  -1;
	 int	index;

	 if  (  initQnmEnc(  &var.encCtx,  NULL,  NULL,  NULL  )  )  goto  errLabel;

 	 #ifndef  __WITHOUT_CHKDOG__
			 //  初始化软件狗校验工作，注意，没清除工作，2003/12/05
		     if  (  initRnbDog(  &var.licenseCtx  )  )  {
				 traceLogA(  "软件狗校验初始化失败"  );  goto  errLabel;	 
			 }
	 #endif


	 QY_REG		reg;
	 memset(  &reg,  0,  sizeof(  reg  )  );
	 //  safeStrnCpy(  CONST_qyRootKey_qnmScheduler,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	 safeTcsnCpy(  _T(  CONST_qyRootKey_qnmScheduler  ),  reg.rootKey,  mycountof(  reg.rootKey  )  );
	 reg.pEncCtx  =  &var.encCtx;
	 if  (  getQnmDbParams(  &reg,  qyGetSystemId(  ),  FALSE,  _T(  CONST_qyDsn_netMc  ),  &var.cfg.db  )  )  goto  errLabel;
	 /*
	 if  (  getQnmDbParams(  &var.encCtx,  NULL,  &iDbType,  NULL,  0,  NULL,  0,  NULL,  0,  NULL,  0,  connectStr,  sizeof(  connectStr  ),  NULL  )  )  goto  errLabel;
	 if  (  !bSetLongProperty(  CONST_qyPropertyId_dbType,  iDbType  )  )  goto  errLabel;			//  2006/05/03
	 if  (  !bSetStrProperty(  CONST_qyPropertyId_connectStr,  connectStr  )  )  goto  errLabel;
	 */

	 switch  (  var.cfg.iNmsOp  )  {
			 case  CONST_nmsOp_nbtScan:
				   setScanStruct(  var.cfg.iNmsOp,  var.cfg.iSnmpOpCmd,  qyNbtScanThreadProc,  NULL,  this,  &var.cfg.scanStruct  );
				   break;
			 default:
					 setScanStruct(  var.cfg.iNmsOp,  var.cfg.iSnmpOpCmd,  qySnmpHelpThreadProc,  NULL,  this,  &var.cfg.scanStruct  );
					 break;
	 }

	 index  =  0;
	 var.threadProcs[index]  =  (  QY_THREADPROC  )var.cfg.scanStruct.pfThreadProc;  var.pThreadParams[index]  =  &var.cfg.scanStruct;
	 index  ++  ;
	 ASSERT(  index  <  sizeof(  var.threadProcs  )  /  sizeof(  var.threadProcs[0]  )  );

	 //  2004/07/12
	 if  (  index  >  1  )  traceLogA(  "由于全部使用全局变量而不是线程独立的变量控制处理线程，故本程序的处理线程只能有一个，不可原谅的错误：index is %d",  index  );
	 
	 iErr  =  0;

errLabel:

	 
	 return  iErr;
}


 int  CQySnmpHelpProcDaemon::init(  )
{	 
	 int	iErr  =  -1;
	 int	index  =  0;
	 DWORD	dwThreadId;

	 if  (  this->refreshCfg(  )  )  goto  errLabel;

	 for  (  index  =  0;  var.threadProcs[index];  index  ++  )  {
		  var.hThreads[index]  =  CreateThread(  NULL,  0,  var.threadProcs[index],  var.pThreadParams[index],  0,  &dwThreadId  );
		  if  (  !var.hThreads[index]  )  goto  errLabel;
	 }

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  exit(  );

	 return  iErr;
}
 
 void  CQySnmpHelpProcDaemon::exit(  )
{
	 int  index  =  0;
	
	traceLogA(  "CQySnmpHelpProcDaemon::exit(  ) enters."  );

	startToQuit(  );
	
	for  (  index  =  0;  index  <  sizeof(  var.hThreads  )  /  sizeof(  var.hThreads[0]  )  &&  var.hThreads[index];  index  ++  )  {
		 MACRO_qyNullThread(  var.hThreads[index]  );
	}

	exitRnbDog(  &var.licenseCtx  );	//  2005/06/27

	exitQnmEnc(  &var.encCtx,  NULL,  NULL,  NULL  );

	traceLogA(  "CQySnmpHelpProcDaemon::exit(  ) leaves."  );

}


 int  CQySnmpHelpProcDaemon::refreshCfg(  )
{
	 traceLogA(  "qySnmpHelpProcDaemon::refreshCfg"  );
	 if  (  var.ucbScanFinished  )  {
		 traceLogA(  "工作已完成，进程将退出运行"  );  startToQuit(  );
	 }
	 if  (  var.tStartToScanInSecond  )  {	//  注意，当tStartToScanInSecond为0时，表没有启动超时检查
	 	 if  (  (  (  unsigned  )(  time(  NULL  )  -  var.tStartToScanInSecond  )  )  >  600  )  {
			 qyShowInfo(  CONST_qyShowType_qnmChking,  NULL,  NULL,  L"",  L"",  L"",  L"Warning: ",  L"the scanning is too slow, and will be stopped"  );
			 traceLogA(  "太慢了，扫描将被中止"  );  startToQuit(  );
		 }
	 }

	 qyRefreshRegCfg_ucb(  _T(  CONST_qyRootKey_qnmScheduler  ),  var.cfg.scanStruct.pRegValName,  &var.cfg.scanStruct.ucbStopScan  );
	 qyRefreshRegCfg_ucb(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_startRegScan  ),  &var.cfg.ucbStartRegScan  );
	 qyRefreshRegCfg_ucb(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_stopWatchIp  ),  &var.cfg.ucbStopWatchIp  );
	 qyRefreshRegCfg_ucb(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_startRespForUnreg  ),  &var.cfg.ucbStartRespForUnreg  );
	 
	 return  0;
}


 //  2004/07/12设检测扫描一台设备的超时计算起点，由于仅使用一个变量，故本程序的处理线程只能有一个，
 //  注意，当tStartToScanInSecond为0时，表没有启动超时检查
 void  CQySnmpHelpProcDaemon::setStartToScanObjTime(  )
{	 
	 var.tStartToScanInSecond  =  time(  NULL  );
}
