

#ifndef  __QYMCMAINCOMMON_H__
#define  __QYMCMAINCOMMON_H__	/* { */


#ifndef  __noMfc__
		 #include	<afxtempl.h>
#else
		#include	<CommCtrl.h>
#endif


#ifndef  __WINCE__
	#include	<vfw.h>
#else
	#ifdef  __TEST__
		#include	<vfw.h>
	#endif
	#include	<mmreg.h>
	#include	<MSAcm.h>
#endif

#include	<Wincrypt.h>


//
#include	"qmCommon.h"



#ifndef  __WINCE__
	#include	"qyDbCommon.h"
#endif


#include	"qyCommCommon.h"


#include	"qyGuiCommonEx.h"


#include	"qyGuiCommProc.h"

#include	"qnmDb.h"
#include	"qnmGuiCommProc.h"
#include	"qySnmpCommProc.h"
#include	"qnmCustomGui.h"
#include	"qnmCustomSearch.h"

#include	"avCapHelpCommProc.h"

#include	"qmUiFunc.h"

#include	"qmCrypt.h"

#include	"qmcCommFunc_netMc.h"
#include	"qmcCommFunc_mis.h"



#include	"qyOpenGuiCommon.h"

#include	"qyMcMainDefs.h"
#include	"qyMcDlgBarCfg.h"


#include	"qyMcMainObj.h"

#include	"qyMcMainCusModule.h"
#include	"qyMcMainExtModule.h"

#include	"qyMcInputMgr.h"


#ifndef  __WINCE__
		 #define  CONST_procedObjDbs						8		//  64
#else
		 #define  CONST_procedObjDbs						1
#endif
 
// 
typedef  struct  __qyMc_t									{

				 MACRO_qyAppCommonMems

				 QY_ENV										env;							//  2005/11/03
				 unsigned  int								uiTotalPhys_memStatus;			//  2008/10/08
				 unsigned  char								bUseDirectSound_toPlay;			//  2010/05/03

				 HINSTANCE									g_hInst;						//  2010/07/14

#if  0
				 struct										{
					 unsigned  char							ucbAv;
					 unsigned  char							ucbMediaFile;
					 //
					 unsigned  int							uiTranNo_sharedObj;		
				 }											cmd;							//  200912/21
#endif
				 QM_APP_PARAMS								appParams;
				 unsigned  char								ucbApp_ts;						//  2013/06/13
#ifdef  __DEBUG__
				 unsigned  char								ucbUseNamedShm;					// 
				 unsigned  char								ucbDebugSeparately;				//  2009/12/22
#endif

				 QY_MC_CFG									cfg;
				 
				 unsigned  char								ucbDynLibInited;				//  2007/01/21
				 //  unsigned  char								ucbOsUsrAdmin;					//  2008/11/15

				 QY_ENC_CTX									encCtx,  commEncCtx;  
				 unsigned  char								ucbEncInited;
				 //
				 QY_LICENSE_CTX								licenseCtx;
				 //
				 QNM_CUSRES_INFO							cusRes;							//  2005/11/03
				 unsigned  char								ucbResInited;

#if  0
				 //  2010/10/02
				 MODULE_EXT_guiCommon			*			pModuleExt;
				 unsigned  char								ucbInited_moduleExt;
#endif

				 //
				 QY_DMITEM						*			pQnmEventTypeTable0;
				 QY_DMITEM						*			pQnmEventTypeTable_pc;
				 QY_DMITEM						*			pQnmEventTypeTable_op;
				 QY_DMITEM						*			pQnmEventTypeTable_netDev;
					 
				 QY_MC_GUI									gui;

				 //  
				 QY_OBJ_DB									procedObjDbs[CONST_procedObjDbs];				//  2006/12/17
				 //
				 int										iDsnIndex_mainSys;								//  procedObjs Index

				 //  

				 BOOL										bLogon;
				 DWORD										dwTickCnt_logon;				//  2013/04/06
				 QYMC_USR									curUsrInfo;
				 //  TCHAR									appObjPrefix[16  +  1];			//  2010/03/10
				 BOOL										bQnmLicenseTimeout;				//  2010/03/22
					 
				 BOOL										bQuit;
				 BOOL										bGuiQuit;						//  2008/10/03
				 unsigned  short							usTimes_tryToQuit;
				 //
				 BOOL										bAskingToQuit;					//  2011/03/18
				 BOOL										bQuitVerified;					//  2011/03/16

				 //
#if  0
				 HANDLE										hSema_syncCusModules;			//  
#else			
				 CMutexRW								*	pRw_syncCusModules;
#endif
				 //
				 QY_GUI_OPEN_vDev							guiOpen_vDev;					//  2008/01/01
				 QIS_guiOpen								guiOpen;
				 //  
				 CUS_MODULES								cusModules;						//  2007/12/30
				 BOOL										bCusModulesLoaded;

				 //  
				 QY_SERVICEGUI_INFO							serviceGuiInfos[CONST_maxServiceGuis];

				 HANDLE										hDaemonThreads[QY_MC_TOTAL_DAEMON_THREADS];
				 QY_THREADPROC								threadProcs[QY_MC_TOTAL_DAEMON_THREADS];

				 //  2008/11/25
				 QM_INPUT_MGR								inputMgr;
				 BOOL										bInputMgrInited;

				 //  
				 void								*		pQisWalls;													//  2013/07/11
				 void								*		pGBuf_d3d;													//  2013/07/03

				 //  2009/10/11
				 unsigned  char								ucbDaemonDemo;
				 unsigned  short							usMaxVideoConferenceMems;
				 unsigned  char								ucDays_left;												//  2010/03/22
				 //
				 unsigned  short							usAppAvLevel_default;										//  2013/06/28
				 unsigned  short							usAppAvLevel_daemon;										//  2011/10/22

				 //
				 unsigned  char								ucbSupported_gps_default;									//  2013/06/28

				 //
				 unsigned  int								uiMaxTimeInS_videoConference;								//  2011/08/01
				 //

}		QY_MC;




// 后台线程的数据结构
typedef  struct  __qyMcThreadDaemon_t						{
				 int										iEnvType;
				 void						*				pParentParam;		//  指向pQyMc

				 HANDLE										hMutex;
				 void						*				pDb;

				 
}		 QY_MC_THREADDAEMON;


//  2010/06/07
class  CQyCoInit	{
		struct		{
			BOOL	bInited;
		}			m_var;
public:
		CQyCoInit(  )  {
			memset(  &m_var,  0,  sizeof(  m_var  )  );
			DWORD dwCoInit  =  COINIT_APARTMENTTHREADED;	// COINIT_MULTITHREADED. 2013/06/17
			if  (  SUCCEEDED(  CoInitializeEx(  NULL,  dwCoInit  )  )  )  {
				m_var.bInited  =  TRUE;
			}
		}
		~CQyCoInit(  )  {
			if  (  m_var.bInited  )  {
				CoUninitialize(  );
			}
		}
};



#include	"qyMcMainMenu.h"
#include	"qyMcMainProc.h"
#include	"qyMcMainDb.h"
#include	"qyMcMainTemp.h"
#include	"qyMcAuth.h"



#include	"qnmTrayProc.h"
#include	"qnmMainProc.h"
#include	"qnmMainProc_mis.h"
//
#include	"qnmHotKeys.h"

#ifdef  __SUPPORT_HTMLEDIT__
	#ifdef  __DLL_isCliHelp__
			#include	"qyCustSite.h"
			#include	"qyIdisImp.h"
			#include	"qyDropTarget.h"
	#endif
#endif


#include	"qyCusResPublic.h"


//
#include	"tmpLib.h"


extern  QY_MC  * g_pQyMc;

#define  QY_GET_GBUF( )			(  g_pQyMc  )

//  2010/01/06
#define  isIsCli(  )			(  g_pQyMc														\
									&&  g_pQyMc->iServiceId  ==  CONST_qyServiceId_is			\
									&&  (  g_pQyMc->iAppType  ==  CONST_qyAppType_client		\
										||  g_pQyMc->iAppType  ==  CONST_qyAppType_client_ts	\
										)														\
									)

#define  isIsMgr(  )			(  g_pQyMc  &&  g_pQyMc->iServiceId  ==  CONST_qyServiceId_is  &&  !isIsCli(  )  )
#define  isIs(  )				(  g_pQyMc  &&  g_pQyMc->iServiceId  ==  CONST_qyServiceId_is  )

//
#define	 isQmCmd(  )			(  g_pQyMc->appParams.ucbAv  ||  g_pQyMc->appParams.ucbMediaFile  )

//
#define  QY_GET_procInfo_isCli(  )	(  isIsCli(  )  ?  (  (  MC_VAR_isCli  *  )g_pQyMc->serviceGuiInfos[0].pVar  )  :  NULL  )
#define  QY_GET_procInfo_isMgr(  )	(  isIsMgr(  )  ?  (  (  MC_VAR_isMgr  *  )g_pQyMc->serviceGuiInfos[0].pVar  )  :  NULL  )

//  2010/09/14
#define  QY_GET_shmCmds(  )		(  QM_SHM_CMDS  *  )(  isQmCmd(  )  ?  (  (  MC_VAR_qmCmd  *  )QY_GET_procInfo_isCli(  )  )->cmdsShm.pBuf  :  (  (  MC_VAR_isCli  *  )QY_GET_procInfo_isCli(  )  )->cmdsShm.pBuf  )

//  2013/06/08
#define  QY_GET_PolicyAvParams(  )			(  PolicyAvParams  *  )(  (  (  MC_VAR_isCli  *  )  QY_GET_procInfo_isCli(  )  )->p_gAvParams  )
#define	 QY_GET_FUNCS_for_isCliHelp(  )		(  FUNCS_for_isCliHelp  *  )(  (  (  MC_VAR_isCli  *  )  QY_GET_procInfo_isCli(  )  )->pFuncs_for_isCliHelp  )


//  2013/03/10
#define		isIdcChked(  hDlg,  idc  )				( ::SendMessage(  ::GetDlgItem(  hDlg,  idc  ),  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )
#define		setIdcChked(  hDlg,  idc,  bChked  )	::SendMessage(  ::GetDlgItem(  hDlg,  idc  ),  BM_SETCHECK,  bChked  ?  BST_CHECKED  :  BST_UNCHECKED,  0  );


//
int  letInScope(  QY_MC  *  pQyMc,  TCHAR  *  wherePart,  unsigned  int  cnt  );

BOOL  isMem512(  );
BOOL  bLikeXp(  );
BOOL  isWinCe(  );
BOOL  b4Core(  );

//  2012/11/09
#define	isLowCfg(  )	(  isMem512(  )  ||  bLikeXp(  )  )

//
unsigned  short  qyGetAppAvLevel_qyMc(  );
BOOL  bSupported_gps(  );
BOOL  bSupported_vwRuleType_messenger(  );

int  getMenuStatus_frame(  void  *  p0,  void  *  p1,  void  *  piStatusParam  );

#if  (  defined  __APP_qyMc_touchscreen__  ||  defined  __APP_qyMc_ts_noMfc__  ) 
		void  *  getDlgWallsVar_ts(  HWND  hDlgWalls,  int  iWndContentType  );
		int  getRect_talkers_ts(  HWND  hDlgWalls,  RECT  *  pRc  );
		BOOL  bFullScreen_walls_ts(  HWND  hDlgWalls,  int  iWndContentType  );
#endif

BOOL  bProcessOsUsrAdmin(  );


#ifndef  ASSERT
	#define	ASSERT(  x  )	MACRO_qyAssert(  x,  _T(  ""  )  )
#endif
#ifndef  _ASSERT
	#define	_ASSERT(  x  )	MACRO_qyAssert(  x,  _T(  ""  )  )
#endif

#endif /* } */

