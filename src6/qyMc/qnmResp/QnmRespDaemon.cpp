// QnmRespDaemon.cpp: implementation of the CQnmRespDaemon class.
//
//////////////////////////////////////////////////////////////////////

#include	"stdafx.h"
#include	"qnmRespCommon.h"
#include	"qyGuiCommon.h"
#include	"qnmResp.h"
#include	"QnmRespDaemon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CQnmRespDaemon::CQnmRespDaemon()
{
	memset(  &var,  0,  sizeof(  var  )  );
}

CQnmRespDaemon::~CQnmRespDaemon()
{

}
   

 int  CQnmRespDaemon::getInitialCfg(  )
{	 
	int			iRet					=	-1;
	int			index;
	int			iDbType					=	0;
	WCHAR		connectStr[256  +  1]	=	L"";
	
	//  2005/10/03
	qyShowInfo(  CONST_qyShowType_qnmChking,  NULL,  NULL,  _T(  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  "Begin to initialize service,waiting for 40s ..."  ),  _T(  ""  )  ); 

	//  2003/12/01取消对systemId的判断，使respDaemon成为通用框架
	//  var.iSystemId  =  qyGetSystemId(  );

	#ifndef  __WITHOUT_CHKDOG__
		     //  初始化软件狗校验工作，注意，没清除工作，2003/12/05
			 if  (  initRnbDog(  &var.licenseCtx  )  )  {
		 		 traceLogA(  "Load USB Key failed!"  );  goto  errLabel;	 
	 		 }
	#endif

	if  (  initQnmEnc(  &var.encCtx,  NULL,  NULL,  NULL  )  )  goto  errLabel;
	var.ucbEncInited  =  TRUE;


	//  if  (  !bSetStrProperty(  CONST_qyPropertyId_sysRootKey,  CString(  CONST_qyRootKey_mc  )  )  )  goto  errLabel;
	if  (  !bSetStrProperty(  CONST_qyPropertyId_moduleIdName,  CString(  "resp"  )  )  )  goto  errLabel;
	if  (  !bSetStrProperty(  CONST_qyPropertyId_lckFileName,  CString(  CONST_qyLckFileName_qnmResp  )  )  )  goto  errLabel;
	if  (  !bSetPtrProperty(  CONST_qyPropertyId_licenseCtx,  &var.licenseCtx  )  )  goto  errLabel;

	//  Sleep(  40000  );  //  2004/04/15已改进。由于Sql Server启动很慢，故设此延时为等待Sql Server
	//  traceLogA(  "After Sleep(  40000  ),  connectStr is %s",  connectStr  );


	setSockTimeout(  &var.cfg.to  );
	var.cfg.to.iSelect  =  1000;

	var.cfg.maxPcLastCommInterval  =  CONST_qnmMaxPcLastCommInterval;
	var.cfg.maxWaitPcCommTime  =  CONST_qnmMaxWaitPcCommTime;
	//  var.cfg.minInvalidChkedIpTime	=  CONST_qnmMinInvalidChkedIpTime;	

	MACRO_qyAssert(  var.cfg.maxPcLastCommInterval  >  var.cfg.maxWaitPcCommTime  *  3,  _T(  "maxPcLastCommInterval应远大于maxWaitPcCommTime"  )  );

	//  判断模块的装载状态	 
	if  (  getQnmModulesLoadedInfo(  &var.cfg.modulesLoadedInfo  )  )  goto  errLabel;


	QY_REG			reg;
	QY_SERVICE_CFG	serviceCfg;
	//
	memset(  &reg,  0,  sizeof(  reg  )  );
	memset(  &serviceCfg,  0,  sizeof(  serviceCfg  )  );
	if  (  var.cfg.modulesLoadedInfo.ulbServiceNetMcLoaded  )  {
		//
		serviceCfg.iServiceId  =  CONST_qyServiceId_qwm;
		//
		if  (  safeStrCpy(  qnmVerStr(  serviceCfg.iServiceId  ),  serviceCfg.ver,  sizeof(  serviceCfg.ver  )  )  )  goto  errLabel;
		if  (  safeWcsCpy(  _T(  CONST_qyRootKey_mc  ),  serviceCfg.sysRootKey,  mycountof(  serviceCfg.sysRootKey  )  )  )  goto  errLabel;
		//
		safeTcsnCpy(  _T(  CONST_qyRootKey_qnmScheduler  ),  reg.rootKey,  mycountof(  reg.rootKey  )  );
		reg.pEncCtx  =  &var.encCtx;
		//  if  (  getQnmDbParams(  &reg,  CONST_qyDsn_netMc,  NULL,  &serviceCfg.db.iDbType,  NULL,  0,  NULL,  0,  NULL,  0,  NULL,  0,  serviceCfg.db.connectStr,  mycountof(  serviceCfg.db.connectStr  ),  NULL  )  )  goto  errLabel;
		if  (  getQnmDbParams(  &reg,  qyGetSystemId(  ),  FALSE,  _T(  CONST_qyDsn_netMc  ),  &serviceCfg.db  )  )  goto  errLabel;
		serviceCfg.ucbAutoOpenDb  =  TRUE;
		//
		//
		if  (  !bSetSpecialProperty(  CONST_qyPropertyId_serviceCfg,  &serviceCfg,  0,  0  )  )  goto  errLabel;
	}


	/*
	if  (  var.iSystemId  ==  CONST_qySystemId_netMc2  )  {
		var.threadProcs[0]  =  qnmIpScanProc;
		if  (  !var.cfg.ulbNmsModuleLoaded  )  var.threadProcs[1]  =  qnmRespProc_netMc2;
		ASSERT(  2  <=  sizeof(  var.threadProcs  )  /  sizeof(  var.threadProcs[0]  )  );
		}
	else  {  //  对CONST_qySystemId_nms,  由于引入了交换机扫描，不再留用此接口  2003/10/05修改
		  var.threadProcs[0]  =  qnmIpScanProc;
		  var.threadProcs[1]  =  qnmRespProc;		
	}
	*/
	//  2003/12/01取消对systemId的判断，使respDaemon成为通用的框架
	index  =  0;
	if  (  var.cfg.modulesLoadedInfo.ulbNetMc2ModuleLoaded  )  {
		var.threadProcs[index]  =  qnmIpScanProc;  index  ++  ;
		var.threadProcs[index]  =  qnmRespProc_netMc2;  index  ++  ;
	}	
	//  此时index相当于threadProcs的cnt
	ASSERT(  index  <=  sizeof(  var.threadProcs  )  /  sizeof(  var.threadProcs[0]  )  );
		
	iRet  =  0;
	
errLabel:
	
	return iRet;

}

 BOOL  CQnmRespDaemon::bChkBeforeRunning(  )
{
	 int	iPlatformId	 =  -1;
	 TCHAR	productStr[513];

	 if  (  !var.pDb_netMc  )  return  FALSE;
	 if  (  !bQyGetSystemVersionEx(  &iPlatformId,  productStr,  mycountof(  productStr  ),  NULL,  0,  NULL  )  )  return  FALSE;
	 
	 /*
	 if  (  var.iSystemId  ==  CONST_qySystemId_netMc2  ||  var.iSystemId  ==  CONST_qySystemId_netMc2  )  {	//  对上海海关版有Win2000的限制
		 if  (  iPlatformId  !=  CONST_qyPlatform_win2k  )  {
		 	 qyShowHint(  "本程序须在Win2000下运行"  );
		 	 return  FALSE;
		 }    
	 }
	 */

	 return  TRUE;
}


 int  CQnmRespDaemon::init(  )
{	 
	 int				iErr					=	-1;
	 DWORD				dwThreadId;
	 int				index;
	 CDatabase		*	pDb						=	0;


	 if  (  qyTcpStart(  )  )  goto  errLabel;
	 var.status.ulbTcpStarted  =  TRUE;

	 if  (  qyInitSnmp(  &ghDll_InetMib1  )  )  goto  errLabel;

	 //  var.pDb  =  getPtrProperty(  CONST_qyPropertyId_db  );	 
	
	 //  if  (  qyGetSystemId(  )  ==  CONST_qySystemId_netMc2  )  {	//  只对上海海关版起作用  2003/10/05
	 /*
	 if  (  var.cfg.modulesLoadedInfo.ulbNetMc2ModuleLoaded  ||  var.cfg.modulesLoadedInfo.ulbNetMc4ModuleLoaded  )  {  //  2003/12/11将上述条件改为对模块安装条件的判断,  2003/12/23 添加了netMc4模块。
		 if  (  qnmInstallDriver(  IDR_DATA_packet2k,  CONST_qnmPacketDrvName  )  )  goto  errLabel;
	 }
	 */
	 //  }

	 for  (  index  =  0;  ;  index  ++  )  {
		  QY_SERVICE_INFO  *  pServiceInfo  =  (  QY_SERVICE_INFO  *  )getSpecialProperty(  CONST_qyPropertyId_serviceInfo_byIndex,  (  void  *  )index,  0  );
		  //
		  if  (  !pServiceInfo  )  break;
		  if  (  !pServiceInfo->cfg.iServiceId  )  continue;
		  //
		  _sntprintf(  pServiceInfo->name,  mycountof(  pServiceInfo->name  ),  _T(  "%s"  ),  qyGetDesByType1(  CONST_qyServiceIdTable,  pServiceInfo->cfg.iServiceId  )  );
		  //
		  pServiceInfo->pParent  =  this;	//  2007/05/29
		  //
		  if  (  pServiceInfo->cfg.ucbAutoOpenDb  &&  pServiceInfo->cfg.db.connectStr[0]  )  {
		 
			  TRY  {
			 	    pDb  =  new  CDatabase;
			 		if  (  !pDb  )  goto  errLabel;
			 
					if  (  !pDb->OpenEx(  pServiceInfo->cfg.db.connectStr,  pServiceInfo->cfg.db.ulOpenOptions  )  )  {
						traceLogA(  "db.OpenEx( %s ) failed.",  pServiceInfo->cfg.db.connectStr  );
						goto errLabel;
					}		
				  }	
			  CATCH  (  CDBException,  e  )  {		
					 traceLogA(  "db.Open( ) failed: [%S]",  e->m_strError  );
					 goto  errLabel;
			 		  }
		 	  END_CATCH
	 
			  pServiceInfo->pDb  =  pDb;	pDb  =  NULL;	//  这里表明处理交给了serviceInfo
	 	  }

	 }


	 {
		 QY_SERVICE_INFO		*	pServiceInfo_qwm				=	(  QY_SERVICE_INFO  *  )getSpecialProperty(  CONST_qyPropertyId_serviceInfo_byServiceId,  (  void  *  )CONST_qyServiceId_qwm,  0  );
		 if  (  !pServiceInfo_qwm  )  goto  errLabel;
		 var.pDb_netMc  =  pServiceInfo_qwm->pDb;
	 }


	 if  (  !bChkBeforeRunning(  )  )  goto  errLabel;

	 if  (  this->refreshCfg(  )  )  goto  errLabel;
	 
	 for  (  index  =  0;  var.threadProcs[index];  index  ++  )  {
		  var.hThreads[index]  =  CreateThread(  NULL,  0,  var.threadProcs[index],  (  LPVOID  )this,  0,  &dwThreadId  );
		  if  (  !var.hThreads[index]  )  goto  errLabel;
	 }

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
		 if  (  pDb  )  delete  pDb;
		 exit(  );
	 }

	 return iErr;

}

 void  CQnmRespDaemon::exit(  )
{
	 int  index  =  0;

	 startToQuit(  );

	 index  =  0;
	 for  (  index  =  0;  index  <  sizeof(  var.hThreads  )  /  sizeof(  var.hThreads[0]  );  index  ++  )  {
		  MACRO_qyNullThread(  var.hThreads[index]  );
	 }

	 for  (  index  =  0;  ;  index  ++  )  {
		  QY_SERVICE_INFO  *  pServiceInfo  =  (  QY_SERVICE_INFO  *  )getSpecialProperty(  CONST_qyPropertyId_serviceInfo_byIndex,  (  void  *  )index,  0  );
		  //
		  if  (  !pServiceInfo  )  break;
		  if  (  !pServiceInfo->cfg.iServiceId  )  continue;
		  //

		  if  (  pServiceInfo->pDb  )  {
			  CDatabase  *  pDb  =  (  CDatabase  *  )pServiceInfo->pDb;
			  delete  pDb;
			  pServiceInfo->pDb  =  NULL;
		  }
		  
	}




	 if  (  var.ucbEncInited  )  exitQnmEnc(  &var.encCtx,  NULL,  NULL,  NULL  );
	
	 exitRnbDog(  &var.licenseCtx  );	//  2005/06/27

	 if  (  ghDll_InetMib1  )  qyExitSnmp(  &ghDll_InetMib1  );

	 if  (  var.status.ulbTcpStarted  )  {
		 qyTcpEnd(  );  var.status.ulbTcpStarted  =  FALSE;
	 }

	 //  2005/10/03
	 qyShowInfo(  CONST_qyShowType_qnmChking,  NULL,  NULL,  _T(  ""  ),  _T(  "127.0.0.1"  ),  0,  _T(  "(Server)"  ),  _T(  "Service exits"/*服务退出完毕*/  ),  _T(  ""  )  ); 

	 return;	 

}


 int  CQnmRespDaemon::refreshCfg(  )
{
	 int						iErr							=	-1;
	 static	 unsigned  int		cnt								=	0;
	 TCHAR						buf[255];
	 unsigned  char				ucbStarted;

	 //  校验软件狗
 	 #ifndef  __WITHOUT_CHKDOG__
		 if  (  !(  cnt  %  30  )  )  {
			 if  (  !bQyDogOk(  &var.licenseCtx,  _T(  CONST_qyModuleName_resp  )  )  )  {
				 AfxMessageBox(  _T(  "Need software USB key"  )  );  startToQuit(  );  goto  errLabel;
			 }
		 }
	 #endif

	 //  检查数据库
	 if  (  !(  cnt  %  30  )  )  {
		 if  (  !bQnmDbOk(  var.pDb_netMc  )  )  {
			 traceLogA(  "数据库坏了"  );  goto  errLabel;
		 }
	 }

	 ucbStarted  =  FALSE;
	 if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_startIpScan  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  {
		 if  (  _ttol(  buf  )  ==  1  )  ucbStarted  =  TRUE;
	 }
	 if  (  ucbStarted  !=  var.cfg.ucbStartIpScan  )  var.cfg.ucbStartIpScan  =  ucbStarted;

	 ucbStarted  =  FALSE;
	 if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_startRegScan  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  {
		 if  (  _ttol(  buf  )  ==  1  )  ucbStarted  =  TRUE;
	 }
	 if  (  ucbStarted  !=  var.cfg.ucbStartRegScan  )  var.cfg.ucbStartRegScan  =  ucbStarted;

	 ucbStarted  =  FALSE;
	 if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  _T(  CONST_regValName_startRespForUnreg  ),  (  char  *  )buf,  sizeof(  buf  )  )  )  {
		 if  (  _ttol(  buf  )  ==  1  )  ucbStarted  =  TRUE;
	 }
	 if  (  ucbStarted  !=  var.cfg.ucbStartRespForUnreg  )  var.cfg.ucbStartRespForUnreg  =  ucbStarted;

	 if  (  !var.macsInfo.nMacs  )  getQwmSortedMacs(  &var.env,  &var.macsInfo  );

	 cnt  ++  ;

	 iErr  =  0;

errLabel:

	 return  iErr;

}



