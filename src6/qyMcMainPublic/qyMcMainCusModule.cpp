

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyMcMainCusModule.h"
#include	"qyCusResTemp.h"
#include	"qyVDev.h"
#include	"myresource.h"
#include	"qyCustom.h"
#include	"module_qisCamCap.h"
#include	"qyAvRecordPublic.h"





 //  2007/12/30
 //
 BOOL  bFindMenuItem(  HMENU  hMenu, LPCTSTR  MenuString,  int  *  pnPos  )
{
   int	nPos  =  -1;
 
   if  (  !hMenu  ||  !MenuString  )  return  FALSE;

   int  count  =  GetMenuItemCount(  hMenu  );
   for  (  int i = 0; i < count; i++  )  {
	    TCHAR	str[512]	=	_T(  ""  );
        if  (  GetMenuString(  hMenu,  i, str, mycountof(  str  ),  MF_BYPOSITION) &&  (lstrcmpi(str, MenuString) == 0))  {
			nPos  =  i;
			break;
		}         
   }

   if  (  nPos  >  0  )  {
	   if  (  pnPos  )  *pnPos  =  nPos;
   }
   return  (  nPos  >=  0  )  ?  TRUE  :  FALSE; 
}



 //  2007/12/30
 //
#ifndef  __WINCE__
#if  0
 int  cusModuleMenu(  void  *  pQyMcParam,  HMENU  hMenuFrm,  int  iResId_menu_modulesGuanLi  )
{
	QY_MC			*	pQyMc		=	(  QY_MC  *  )pQyMcParam;
	CUS_MODULE_U	*	pModule		=	NULL;
	HMENU				hMenu		=	NULL;
	int					cnt			=	0;
	int					nPos		=	0;
	//
	if  (  bFindMenuItem(  hMenuFrm,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_menu_guanLi  ),  &nPos  )  )  {
		if  (  (  hMenu  =  GetSubMenu(  hMenuFrm,  nPos  )  )  )  {
			if  (  bFindMenuItem(  hMenu,  getResStr(  0,  &pQyMc->cusRes,  iResId_menu_modulesGuanLi  ),  &nPos  )  )  {
				if  (  !pQyMc->cusModules.usCnt  )  {
					traceLogA(  "RemoveMenu returns %d",  RemoveMenu(  hMenu,  nPos,  MF_BYPOSITION  )  );	//  在没有模块时，需要将菜单上的模块管理给清除．
					traceLogA(  "RemoveMenu returns %d",  RemoveMenu(  hMenu,  nPos,  MF_BYPOSITION  )  );	//  这是将下面那个分隔线也给删掉．
					}
				else  {
					  if  (  (  hMenu  =  GetSubMenu(  hMenu,  nPos  )  )  )  {
						  for  (  nPos  =  GetMenuItemCount(  hMenu  )  -  1;  nPos  >=  0;  nPos  --  )  DeleteMenu(  hMenu,  nPos,  MF_BYPOSITION  );
						  //
						  for  (  int  i  =  0;  i  <  pQyMc->cusModules.usCnt;  i  ++  )  {
							   pModule  =  &pQyMc->cusModules.mems[i];
							   switch  (  pModule->common.uiType  )  {
									   case  CONST_moduleType_vDev:
										     pModule->vDev.uiCmd  =  ID_cliModule0  +  i;			//  注意，这里是给每个模块分配一个操作菜单．其中ID_cliModule0为起始命令．
											 //							   
											 AppendMenu(  hMenu,  MF_STRING,  pModule->vDev.uiCmd,  pModule->vDev.name  );
											 break;
									   default:
											   break;
							   }
						  }
					  }
				}
			}
		}		
	}

	return  0;

}
#endif

  //  2010/09/05
  int  cusModuleMenu(  void  *  pQyMcParam,  HMENU  hMenuFrm,  int  iResId_menu_modulesGuanLi  )
{
	QY_MC			*	pQyMc		=	(  QY_MC  *  )pQyMcParam;
	CUS_MODULE_U	*	pModule		=	NULL;
	HMENU				hMenu		=	NULL;
	int					cnt			=	0;
	int					nPos		=	0;
	BOOL				bMenuAdded	=	FALSE;
	//
	if  (  bFindMenuItem(  hMenuFrm,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_menu_guanLi  ),  &nPos  )  )  {
		if  (  (  hMenu  =  GetSubMenu(  hMenuFrm,  nPos  )  )  )  {
			if  (  bFindMenuItem(  hMenu,  getResStr(  0,  &pQyMc->cusRes,  iResId_menu_modulesGuanLi  ),  &nPos  )  )  {
				HMENU	hMenu_guanLi	=  hMenu;
				int		nPos_modules	=	nPos;
				//
				if  (  (  hMenu  =  GetSubMenu(  hMenu,  nPos  )  )  )  {
					for  (  nPos  =  GetMenuItemCount(  hMenu  )  -  1;  nPos  >=  0;  nPos  --  )  DeleteMenu(  hMenu,  nPos,  MF_BYPOSITION  );
					//
					for  (  int  i  =  0;  i  <  pQyMc->cusModules.usCnt;  i  ++  )  {
						 pModule  =  &pQyMc->cusModules.mems[i];
						 switch  (  pModule->common.uiType  )  {								   
								 case  CONST_moduleType_vDev:
									   pModule->vDev.uiCmd  =  ID_cliModule0  +  i;			//  注意，这里是给每个模块分配一个操作菜单．其中ID_cliModule0为起始命令．
									   //							   
									   AppendMenu(  hMenu,  MF_STRING,  pModule->vDev.uiCmd,  pModule->vDev.name  );
									   //
									   bMenuAdded  =  TRUE;											 
									   break;
								 default:
									     break;
						 }
					}					  
				}
				
				if  (  !bMenuAdded  )  {
					traceLogA(  "RemoveMenu returns %d",  RemoveMenu(  hMenu_guanLi,  nPos_modules,  MF_BYPOSITION  )  );	//  
					traceLogA(  "RemoveMenu returns %d",  RemoveMenu(  hMenu_guanLi,  nPos_modules,  MF_BYPOSITION  )  );	//  
				}
				
			}
		}		
	}

	return  0;

}


#endif

 int  loadCusModules(  void  *  pQyMcParam  )
{
	int					iErr			=	-1;
	int					index			=	0;
	QY_MC			*	pQyMc			=	(  QY_MC  *  )pQyMcParam;
	CUS_MODULE_U	*	pModule			=	NULL;
	TCHAR				tBuf[256]		=	_T(  ""  );
	unsigned  int		uiVDevId		=	DEFAULT_vDevId_base;
	//
	CQyRWLock			syncObj;
	//
#if  0
	if  (  syncObj.wLock(  pQyMc->cfg.cusModules.mutexName,  pQyMc->cfg.cusModules.uiMilliSeconds_mutex_w,  pQyMc->hSema_syncCusModules,  pQyMc->cfg.cusModules.uiMilliSeconds_sema_w,  pQyMc->cfg.cusModules.uiInitCnt_sema  )  )  return  -1;
#else
	if  (  syncObj.wLock(  pQyMc->pRw_syncCusModules,  pQyMc->cfg.cusModules.uiMilliSeconds_sema_w  )  )  return  -1;
#endif

#ifndef  __WINCE__
	//  2008/01/02, 填充guiOpen
	pQyMc->guiOpen_vDev.pf_bGetLongProperty  =  bGetLongProperty_open;
	pQyMc->guiOpen_vDev.pf_bQyOpenMcView  =  (  PF_commonHandler  )bQyOpenMcView;
	pQyMc->guiOpen_vDev.pf_qyMcView_delAllColumns  =  (  PF_commonHandler  )qyMcView_delAllColumns;
	pQyMc->guiOpen_vDev.pf_qyMcView_bAddColumns  =  (  PF_commonHandler  )qyMcView_bAddColumns;
	//
	pQyMc->guiOpen_vDev.pf_enumLvSelEventFunc  =  enumLvSelEventFunc;
	pQyMc->guiOpen_vDev.pf_getLvColContent  =  getLvColContent;
	//
	pQyMc->guiOpen_vDev.pf_postHint2Mgr_mc_open  =  postHint2Mgr_mc_open;
	pQyMc->guiOpen_vDev.pf_postStr2Mgr_mc_open  =  postStr2Mgr_mc_open;
	pQyMc->guiOpen_vDev.pf_postReq2Mgr_mc_open  =  postReq2Mgr_mc_open;
#endif

	//  2010/07/29
	pQyMc->guiOpen.g_hInst  =  pQyMc->g_hInst;
	pQyMc->guiOpen.pCusModuleDir  =  pQyMc->cfg.cusModuleDir;
	pQyMc->guiOpen.pf_showNotification  =  showNotification_open;
	pQyMc->guiOpen.pf_showInfo  =  showInfo_open;	

	//  
	index  =  0;

	#ifdef  __SUPPORT_CUSMODULE_gsmModem__
			pModule  =  &pQyMc->cusModules.mems[index];
			pModule->common.uiType  =  CONST_moduleType_vDev;
			lstrcpyn(  pModule->common.name,  _T(  "GSM Modems"  ),  mycountof(  pModule->common.name  )  );
			_sntprintf(  pModule->common.path,  mycountof(  pModule->common.path  ),  _T(  "%s%s"  ),  pQyMc->cfg.cusModuleDir,  _T(  "qyVDev_coms.dll"  )  );
			index  ++  ;
	#endif
	#ifdef  __SUPPORT_CUSMODULE_compress__
			pModule  =  &pQyMc->cusModules.mems[index];
			pModule->common.uiType  =  CONST_moduleType_compress;
			lstrcpyn(  pModule->common.name,  _T(  "compress"  ),  mycountof(  pModule->common.name  )  );
			_sntprintf(  pModule->common.path,  mycountof(  pModule->common.path  ),  _T(  "%s%s"  ),  pQyMc->cfg.cusModuleDir,  _T(  "qisCompress.dll"  )  );
			index  ++  ;
	#endif
	#ifdef  __SUPPORT_CUSMODULE_camCap__				//  2010/07/26
			//
			tBuf[0]  =  0;
			if  (  pQyMc->cfg.bGetPolicyFromIni  )  {
				if  (  getCfgValByNameT(  pQyMc->cfg.iniFullFileName,  _T(  CONST_regValName_camCapDll  ),  tBuf,  mycountof(  tBuf  )  )  )  tBuf[0]  =  0;
				else  {
					  tTrim(  tBuf  );
				}
			}
			if  (  !tBuf[0]  )  safeTcsnCpy(  _T(  "qisCamCap.dll"  ),  tBuf,  mycountof(  tBuf  )  );
			//
			pModule  =  &pQyMc->cusModules.mems[index]; 
			pModule->common.uiType  =  CONST_moduleType_camCap;
			lstrcpyn(  pModule->common.name,  _T(  "camCap"  ),  mycountof(  pModule->common.name  )  );
			_sntprintf(  pModule->common.path,  mycountof(  pModule->common.path  ),  _T(  "%s%s"  ),  pQyMc->cfg.cusModuleDir,  tBuf  );
			index  ++  ;
	#endif

	#ifdef	__SUPPORT_CUSMODULE_ipp__				//  2011/07/31
			pModule  =  &pQyMc->cusModules.mems[index];
			pModule->common.uiType  =  CONST_moduleType_ipp;
			lstrcpyn(  pModule->common.name,  _T(  "ipp"  ),  mycountof(  pModule->common.name  )  );
			_sntprintf(  pModule->common.path,  mycountof(  pModule->common.path  ),  _T(  "%s%s"  ),  pQyMc->cfg.cusModuleDir,  _T(  "h264Compress.dll"  )  );
			index  ++  ;

	#endif

	#ifdef	__SUPPORT_CUSMODULE_mediaSdk__				//  2011/11/25
			pModule  =  &pQyMc->cusModules.mems[index];
			pModule->common.uiType  =  CONST_moduleType_mediaSdk;
			lstrcpyn(  pModule->common.name,  _T(  "mediaSdk"  ),  mycountof(  pModule->common.name  )  );
			_sntprintf(  pModule->common.path,  mycountof(  pModule->common.path  ),  _T(  "%s%s"  ),  pQyMc->cfg.cusModuleDir,  _T(  "hdCompress.dll"  )  );
			index  ++  ;
	#endif

	#ifdef  __SUPPORT_CUSMODULE_cuda__					//  2012/06/17
			pModule  =  &pQyMc->cusModules.mems[index];
			pModule->common.uiType  =  CONST_moduleType_cuda;
			lstrcpyn(  pModule->common.name,  _T(  "cuda"  ),  mycountof(  pModule->common.name  )  );
			_sntprintf(  pModule->common.path,  mycountof(  pModule->common.path  ),  _T(  "%s%s"  ),  pQyMc->cfg.cusModuleDir,  _T(  "hd1Compress.dll"  )  );
			index  ++  ;
	#endif

	//
	pQyMc->cusModules.usCnt  =  index;

	MACRO_qyAssert(  pQyMc->cusModules.usCnt  <=  mycountof(  pQyMc->cusModules.mems  ),  _T(  "Too many modules"  )  );

	//
	for  (  index  =  0;  index  <  pQyMc->cusModules.usCnt;  index  ++  )  {
		 pModule  =  &pQyMc->cusModules.mems[index];
		 //
#if  0
		 if  (  pQyMc->ucbOsUsrAdmin  )  {  //  为提高安全性，在管理员权限运行此程序时，将提问是否装载某模块。普通用户则不提示，以为了方便。
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "whether to load module %s ( %s )?"  ),  pModule->common.name,  pModule->common.path  );
			 if  (  myMessageBox(  NULL,  tBuf,  _T(  "Qycx"  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  continue;
		 }
#endif

		 if  (  !(  pModule->common.hModule  =  LoadLibrary(  pModule->common.path  )  )  )  {
			 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Failed to load (%s)"  ),  pModule->common.path  );
			 traceLog(  _T(  "Failed to load the module %s ( %s )"  ),  pModule->common.name,  pModule->common.path  );
			 continue;
		 }

		 switch  (  pModule->common.uiType  )  {
			 case  CONST_moduleType_vDev:		
				   pModule->vDev.pf_qyVDev_getPtrProperty  =  (  PF_commonHandler  )myGetProcAddress(  pModule->common.hModule,  "qyVDev_getPtrProperty"  );
				   pModule->vDev.pf_qyVDev_getInfo  =  (  PF_commonHandler  )myGetProcAddress(  pModule->common.hModule,  "qyVDev_getInfo"  );
				   pModule->vDev.pf_qyVDev_getCfg  =  (  PF_commonHandler  )myGetProcAddress(  pModule->common.hModule,  "qyVDev_getCfg"  );
				   pModule->vDev.pf_qyVDev_chkBeforeInit  =  (  PF_commonHandler  )myGetProcAddress(  pModule->common.hModule,  "qyVDev_chkBeforeInit"  );
				   pModule->vDev.pf_qyVDev_chkAfterInit  =  (  PF_commonHandler  )myGetProcAddress(  pModule->common.hModule,  "qyVDev_chkAfterInit"  );
				   pModule->vDev.pf_qyVDev_op  =  (  PF_commonHandler  )myGetProcAddress(  pModule->common.hModule,  "qyVDev_op"  );
				   pModule->vDev.pf_qyVDev_postStr2Dev  =  (  PF_qyVDev_postStr2Dev  )myGetProcAddress(  pModule->common.hModule,  "qyVDev_postStr2Dev"  );
				   pModule->vDev.pf_qyVDev_postData2Dev  =  (  PF_qyVDev_postData2Dev  )myGetProcAddress(  pModule->common.hModule,  "qyVDev_postData2Dev"  );
				   pModule->vDev.pf_qyVDev_init  =  (  PF_commonHandler  )myGetProcAddress(  pModule->common.hModule,  "qyVDev_init"  );
				   pModule->vDev.pf_qyVDev_start  =  (  PF_commonHandler  )myGetProcAddress(  pModule->common.hModule,  "qyVDev_start"  );
				   pModule->vDev.pf_qyVDev_stop  =  (  PF_commonHandler  )myGetProcAddress(  pModule->common.hModule,  "qyVDev_stop"  );
				   pModule->vDev.pf_qyVDev_exit  =  (  PF_commonHandler  )myGetProcAddress(  pModule->common.hModule,  "qyVDev_exit"  );
				   pModule->vDev.pf_qyVDev_isSendable  =  (  PF_bCommonHandler  )myGetProcAddress(  pModule->common.hModule,  "qyVDev_isSendable"  );

				   if  (  !pModule->vDev.pf_qyVDev_getPtrProperty  )  goto  errLabel;
				   QY_VDEV	*	pVDev;
				   if (  !(  pVDev  =  (  QY_VDEV  *  )pModule->vDev.pf_qyVDev_getPtrProperty(  0,  (  void  *  )CONST_qyPropertyId_vDev,  0  )  )  )  goto  errLabel;
				   //
				   pVDev->uiVDevId  =  uiVDevId;	uiVDevId  ++  ;	//  这是为了识别vDev的需要
				   //
				   pVDev->hModule  =  pModule->common.hModule;
				   pVDev->pGuiOpen  =  &pQyMc->guiOpen_vDev;
				   //
				   break;
			 case  CONST_moduleType_compress:
			 case  CONST_moduleType_ipp:
			 case  CONST_moduleType_mediaSdk:
			 case  CONST_moduleType_cuda:
				   pModule->compress.pf_qdcInit  =  (  PF_qdcInit  )myGetProcAddress(  pModule->common.hModule,  "qdcInit"  );
				   pModule->compress.pf_qdcExit  =  (  PF_qdcExit  )myGetProcAddress(  pModule->common.hModule,  "qdcExit"  );

				   pModule->compress.pf_qdcGetCompressAudioCfg  =  (  PF_qdcGetCompressAudioCfg  )myGetProcAddress(  pModule->common.hModule,  "qdcGetCompressAudioCfg"  );
				   pModule->compress.pf_qdcGetCompressVideoCfg  =  (  PF_qdcGetCompressVideoCfg  )myGetProcAddress(  pModule->common.hModule,  "qdcGetCompressVideoCfg"  );

				   pModule->compress.pf_qdcInitCompressAudio  =  (  PF_qdcInitCompressAudio  )myGetProcAddress(  pModule->common.hModule,  "qdcInitCompressAudio"  );
				   pModule->compress.pf_qdcExitCompressAudio  =  (  PF_qdcExitCompressAudio  )myGetProcAddress(  pModule->common.hModule,  "qdcExitCompressAudio"  );
				   pModule->compress.pf_qdcCompressAudio  =  (  PF_qdcCompressAudio  )myGetProcAddress(  pModule->common.hModule,  "qdcCompressAudio"  );
				   pModule->compress.pf_qdcInitDecompressAudio  =  (  PF_qdcInitDecompressAudio  )myGetProcAddress(  pModule->common.hModule,  "qdcInitDecompressAudio"  );
				   pModule->compress.pf_qdcExitDecompressAudio  =  (  PF_qdcExitDecompressAudio  )myGetProcAddress(  pModule->common.hModule,  "qdcExitDecompressAudio"  );
				   pModule->compress.pf_qdcDecompressAudio  =  (  PF_qdcDecompressAudio  )myGetProcAddress(  pModule->common.hModule,  "qdcDecompressAudio"  );

				   pModule->compress.pf_qdcInitCompressVideo  =  (  PF_qdcInitCompressVideo  )myGetProcAddress(  pModule->common.hModule,  "qdcInitCompressVideo"  );
				   pModule->compress.pf_qdcExitCompressVideo  =  (  PF_qdcExitCompressVideo  )myGetProcAddress(  pModule->common.hModule,  "qdcExitCompressVideo"  );
				   pModule->compress.pf_qdcCompressVideo  =  (  PF_qdcCompressVideo  )myGetProcAddress(  pModule->common.hModule,  "qdcCompressVideo"  );
				   pModule->compress.pf_qdcInitDecompressVideo  =  (  PF_qdcInitDecompressVideo  )myGetProcAddress(  pModule->common.hModule,  "qdcInitDecompressVideo"  );
				   pModule->compress.pf_qdcExitDecompressVideo  =  (  PF_qdcExitDecompressVideo  )myGetProcAddress(  pModule->common.hModule,  "qdcExitDecompressVideo"  );
				   pModule->compress.pf_qdcDecompressVideo  =  (  PF_qdcDecompressVideo  )myGetProcAddress(  pModule->common.hModule,  "qdcDecompressVideo"  );

				   //  2011/12/10
				   pModule->compress.pf_qdcDecompressVideoAndOutput  =  (  PF_qdcDecompressVideoAndOutput  )myGetProcAddress(  pModule->common.hModule,  "qdcDecompressVideoAndOutput"  );

				   //
				   pModule->compress.pf_qdcGetOutputByIndex  =  (  PF_qdcGetOutputByIndex  )myGetProcAddress(  pModule->common.hModule,  "qdcGetOutputByIndex"  );
				   pModule->compress.pf_qdcClearOutputs  =  (  PF_qdcClearOutputs  )myGetProcAddress(  pModule->common.hModule,  "qdcClearOutputs"  );

				   break;
			 case  CONST_moduleType_camCap:
				   if  (  sizeof(  MODULE_camCap  )  >  sizeof(  pModule[0]  )  )  goto  errLabel;
				   MODULE_camCap  *	pCamCap;	pCamCap  =  (  MODULE_camCap  *  )pModule;
				   				   
				   pCamCap->pf_setGuiOpen  =  (  PF_setGuiOpen  )myGetProcAddress(  pModule->common.hModule,  "setGuiOpen"  );

				   //
				   pCamCap->pf_doInitRecordSound  =  (  PF_doInitRecordSound  )myGetProcAddress(  pModule->common.hModule,  "doInitRecordSound"  );
				   pCamCap->pf_doExitRecordSound  =  (  PF_doExitRecordSound  )myGetProcAddress(  pModule->common.hModule,  "doExitRecordSound"  );

				   //
				   pCamCap->pf_initVideoCapDev  =  (  PF_initVideoCapDev  )myGetProcAddress(  pModule->common.hModule,  "initVideoCapDev"  );
				   pCamCap->pf_exitVideoCapDev  =  (  PF_exitVideoCapDev  )myGetProcAddress(  pModule->common.hModule,  "exitVideoCapDev"  );
				   pCamCap->pf_bGetCapturePara  =  (  PF_bGetCapturePara  )myGetProcAddress(  pModule->common.hModule,  "bGetCapturePara"  );
				   pCamCap->pf_startCapture  =  (  PF_startCapture  )myGetProcAddress(  pModule->common.hModule,  "startCapture"  );
				   pCamCap->pf_stopCapture  =  (  PF_stopCapture  )myGetProcAddress(  pModule->common.hModule,  "stopCapture"  );

#ifdef  __DEBUG__
#if  0
				   //  for test
				   pCamCap->pf_initVideoCapDev  =  initVideoCapDev_dx;
				   pCamCap->pf_exitVideoCapDev  =  exitVideoCapDev_dx;
				   pCamCap->pf_bGetCapturePara  =  bGetCapturePara_dx;
				   pCamCap->pf_startCapture  =  startCapture_dx;
				   pCamCap->pf_stopCapture  =  stopCapture_dx;
#endif
#endif

				   traceLog(  _T(  "module camCap loaded"  )  );
				   //
				   break;
			 default:
					 break;
		 }

	}

	//
	pQyMc->cusModules.pIpp  =  getCusModule(  pQyMc,  CONST_moduleType_ipp  );
	pQyMc->cusModules.pMediaSdk  =  getCusModule(  pQyMc,  CONST_moduleType_mediaSdk  );
	pQyMc->cusModules.pCuda  =  getCusModule(  pQyMc,  CONST_moduleType_cuda  );

	//
	iErr  =  0;

errLabel:

#ifdef  __DEBUG__
		traceLog(  _T(  "loadCusModule leaves %s"  ),  iErr  ?  _T(  "failed"  )  :  _T(  "ok"  )  );
#endif

	return  iErr;
}
 
 int  initCusModules(  void  *  pQyMcParam  )
{
	int						iErr	=	-1;
	int						index	=	0;
	QY_MC				*	pQyMc	=	(  QY_MC  *  )pQyMcParam;
	QY_SERVICEGUI_INFO	*	pSci	=	getServiceGuiInfo(  pQyMc,  pQyMc->iServiceId  );
	if  (  !pSci  )  return  -1;
	CUS_MODULE_U		*	pModule	=	NULL;

	CQyRWLock		syncObj;
	//
#if  0
	if  (  syncObj.wLock(  pQyMc->cfg.cusModules.mutexName,  pQyMc->cfg.cusModules.uiMilliSeconds_mutex_w,  pQyMc->hSema_syncCusModules,  pQyMc->cfg.cusModules.uiMilliSeconds_sema_w,  pQyMc->cfg.cusModules.uiInitCnt_sema  )  )  return  -1;
#else
	if  (  syncObj.wLock(  pQyMc->pRw_syncCusModules,  pQyMc->cfg.cusModules.uiMilliSeconds_sema_w  )  )  return  -1;
#endif


	for  (  index  =  0;  index  <  pQyMc->cusModules.usCnt;  index  ++  )  {
		 pModule  =  &pQyMc->cusModules.mems[index];
		 //
		 if  (  !pModule->common.hModule  )  continue;
		 switch  (  pModule->common.uiType  )  {
				 case  CONST_moduleType_vDev:
					   if  (  pModule->vDev.pf_qyVDev_getCfg  &&  pModule->vDev.pf_qyVDev_getCfg(  0,  0,  0  )  )  goto  errLabel;
					   if  (  pModule->vDev.pf_qyVDev_chkBeforeInit  &&  pModule->vDev.pf_qyVDev_chkBeforeInit(  0,  0,  0  )  )  goto  errLabel;
					   if  (  pModule->vDev.pf_qyVDev_init  &&  pModule->vDev.pf_qyVDev_init(  0,  0,  0  )  )  goto  errLabel;
					   pModule->vDev.ucbVDevInited  =  TRUE;
					   if  (  pModule->vDev.pf_qyVDev_chkAfterInit  &&  pModule->vDev.pf_qyVDev_chkAfterInit(  0,  0,  0  )  )  goto  errLabel;
					   break;
				 case  CONST_moduleType_compress:
				 case  CONST_moduleType_ipp:
				 case  CONST_moduleType_mediaSdk:
				 case  CONST_moduleType_cuda:
					   pModule->compress.mgr.pGuiOpen  =  &pQyMc->guiOpen;
					   //
					   if  (  pModule->compress.pf_qdcInit  &&  pModule->compress.pf_qdcInit(  &pModule->compress.mgr  )  )  goto  errLabel;
					   pModule->compress.ucbInited  =  TRUE;
					   break;
				 case  CONST_moduleType_camCap:  {
					   MODULE_camCap	*	pCamCap  =  (  MODULE_camCap  *  )pModule;
					   if  (  pCamCap->pf_setGuiOpen  )  pCamCap->pf_setGuiOpen(  &pQyMc->guiOpen  );
					   }
					   break;
				 default:
						 break;
		 }
	}


	for  (  index  =  0;  index  <  pQyMc->cusModules.usCnt;  index  ++  )  {
		 pModule  =  &pQyMc->cusModules.mems[index];
		 //
		 switch  (  pModule->common.uiType  )  {
				 case  CONST_moduleType_vDev:
					   if  (  pModule->vDev.ucbVDevInited  )  {
						   QY_VDEV	*	pVDev;

						   if (  !(  pVDev  =  (  QY_VDEV  *  )pModule->vDev.pf_qyVDev_getPtrProperty(  0,  (  void  *  )CONST_qyPropertyId_vDev,  0  )  )  )  goto  errLabel;
		
						   if  (  pQyMc->iServiceId  ==  CONST_qyServiceId_is  )  {
							   MC_VAR_isCli	*	pProcInfo  =  (  MC_VAR_isCli  *  )pSci->pVar;
							   if  (  !pProcInfo  )  goto  errLabel;
              
							   //  此标志的存在，是为了决定是否PhoneMsgrList下载。2008/02/01
							   if  (  pModule->vDev.pf_qyVDev_isSendable  &&  pModule->vDev.pf_qyVDev_isSendable(  0,  (  void  *  )CONST_objType_phoneMessenger,  NULL  )  )  pProcInfo->bPhoneModuleLoaded  =  TRUE;
							   //
						   }
						   break;
					   }
		 }	
	}

	iErr  =  0;
errLabel:
	return  iErr;

}



 int  startCusModules(  void  *  pQyMcParam  )
{
	int					iErr	=	-1;
	int					index	=	0;
	QY_MC			*	pQyMc	=	(  QY_MC  *  )pQyMcParam;
	CUS_MODULE_U	*	pModule	=	NULL;

	CQyRWLock		syncObj;
	//
#if  0
	if  (  syncObj.wLock(  pQyMc->cfg.cusModules.mutexName,  pQyMc->cfg.cusModules.uiMilliSeconds_mutex_w,  pQyMc->hSema_syncCusModules,  pQyMc->cfg.cusModules.uiMilliSeconds_sema_w,  pQyMc->cfg.cusModules.uiInitCnt_sema  )  )  return  -1;
#else
	if  (  syncObj.wLock(  pQyMc->pRw_syncCusModules,  pQyMc->cfg.cusModules.uiMilliSeconds_sema_w  )  )  return  -1;
#endif

	for  (  index  =  0;  index  <  pQyMc->cusModules.usCnt;  index  ++  )  {
		 pModule  =  &pQyMc->cusModules.mems[index];
		 //
		 if  (  !pModule->common.hModule  )  continue;
		 
		 switch  (  pModule->common.uiType  )  {
				 case  CONST_moduleType_vDev:
					   if  (  pModule->vDev.ucbVDevStarted  )  continue;
					   if  (  !pModule->vDev.ucbVDevInited  )  goto  errLabel;
					   //
					   if  (  pModule->vDev.pf_qyVDev_start  &&  pModule->vDev.pf_qyVDev_start(  0,  0,  0  )  )  goto  errLabel;
					   pModule->vDev.ucbVDevStarted  =  TRUE;
					   break;
				 default:
						 break;
		 }
	}


	iErr  =  0;
errLabel:
	return  iErr;
}

 int  stopCusModules(  void  *  pQyMcParam  )
{
	int					iErr	=	-1;
	int					index	=	0;
	QY_MC			*	pQyMc	=	(  QY_MC  *  )pQyMcParam;
	CUS_MODULE_U	*	pModule	=	NULL;

	CQyRWLock		syncObj;
	//
#if  0
	if  (  syncObj.wLock(  pQyMc->cfg.cusModules.mutexName,  pQyMc->cfg.cusModules.uiMilliSeconds_mutex_w,  pQyMc->hSema_syncCusModules,  pQyMc->cfg.cusModules.uiMilliSeconds_sema_w,  pQyMc->cfg.cusModules.uiInitCnt_sema  )  )  return  -1;
#else
	if  (  syncObj.wLock(  pQyMc->pRw_syncCusModules,  pQyMc->cfg.cusModules.uiMilliSeconds_sema_w  )  )  return  -1;
#endif

	for  (  index  =  0;  index  <  pQyMc->cusModules.usCnt;  index  ++  )  {
		 pModule  =  &pQyMc->cusModules.mems[index];
		 //
		 if  (  !pModule->common.hModule  )  continue;
		 switch  (  pModule->common.uiType  )  {
				 case  CONST_moduleType_vDev:
					   if  (  pModule->vDev.ucbVDevStarted  )  {
						   if  (  pModule->vDev.pf_qyVDev_stop  &&  pModule->vDev.pf_qyVDev_stop(  0,  0,  0  )  )  goto  errLabel;
						   pModule->vDev.ucbVDevStarted  =  FALSE;
					   }
					   break;
				 default:
						 break;
		 }
	}


	iErr  =  0;
errLabel:
	return  iErr;
}


 int  unloadCusModules(  void  *  pQyMcParam  )
{
	int					index	=	0;
	QY_MC			*	pQyMc	=	(  QY_MC  *  )pQyMcParam;
	CUS_MODULE_U	*	pModule	=	NULL;

	stopCusModules(  pQyMcParam  );

	CQyRWLock		syncObj;
	//
#if  0
	if  (  syncObj.wLock(  pQyMc->cfg.cusModules.mutexName,  pQyMc->cfg.cusModules.uiMilliSeconds_mutex_w,  pQyMc->hSema_syncCusModules,  pQyMc->cfg.cusModules.uiMilliSeconds_sema_w,  pQyMc->cfg.cusModules.uiInitCnt_sema  )  )  return  -1;
#else
	if  (  syncObj.wLock(  pQyMc->pRw_syncCusModules,  pQyMc->cfg.cusModules.uiMilliSeconds_sema_w  )  )  return  -1;
#endif

	//
	for  (  index  =  0;  index  <  pQyMc->cusModules.usCnt;  index  ++  )  {
		pModule  =  &pQyMc->cusModules.mems[index];
		//
		if  (  !pModule->common.hModule  )  continue;
		switch  (  pModule->common.uiType  )  {
				case  CONST_moduleType_vDev:
					  //
					  if  (  pModule->vDev.ucbVDevInited  )  {
					      if  (  pModule->vDev.pf_qyVDev_exit  )  pModule->vDev.pf_qyVDev_exit(  0,  0,  0  );
						  pModule->vDev.ucbVDevInited  =  FALSE;
					  }
					  break;
				case  CONST_moduleType_compress:
				case  CONST_moduleType_ipp:
				case  CONST_moduleType_mediaSdk:
				case  CONST_moduleType_cuda:
					  if  (  pModule->compress.ucbInited  )  {
						  if  (  pModule->compress.pf_qdcExit  )  pModule->compress.pf_qdcExit(  &pModule->compress.mgr  );
						  pModule->compress.ucbInited  =  FALSE;					
					  }
					  break;
				default:
						break;		

		}

		FreeLibrary(  pModule->common.hModule  );  pModule->common.hModule  =  NULL;
	}

	return  0;
}


 CUS_MODULE_U  *  getCusModule(  void  *  pQyMcParam,  unsigned  int  uiModuleType,  unsigned  int  uiVDevId,  unsigned  int  uiDevType,  WCHAR  *  wDevIdStr  )
{
	int					index	=	0;
	QY_MC			*	pQyMc	=	(  QY_MC  *  )pQyMcParam;
	CUS_MODULE_U	*	pModule	=	NULL;

	//
	for  (  index  =  0;  index  <  pQyMc->cusModules.usCnt;  index  ++  )  {
		 pModule  =  &pQyMc->cusModules.mems[index];
		 //
		 if  (  pModule->common.uiType  !=  uiModuleType  )  continue;

		 if  (  pModule->common.uiType  ==  CONST_moduleType_vDev  )  {			 
			 if  (  !pModule->vDev.ucbVDevInited  )  continue;
			 if  (  !pModule->vDev.ucbVDevStarted  )  continue;
			 //
			 QY_VDEV	*	pVDev;
			 if (  !(  pVDev  =  (  QY_VDEV  *  )pModule->vDev.pf_qyVDev_getPtrProperty(  0,  (  void  *  )CONST_qyPropertyId_vDev,  0  )  )  )  continue;
			 //
			 if  (  uiVDevId  &&  pVDev->uiVDevId  ==  uiVDevId  )  break;
			 if  (  pModule->vDev.pf_qyVDev_isSendable  &&  pModule->vDev.pf_qyVDev_isSendable(  0,  0,  wDevIdStr  )  )  break;
		 }
		 //
		 break;
	}

	if  (  index  ==  pQyMc->cusModules.usCnt  )  return  NULL;

	return  pModule;
}



 int  myVDev_postStr2Dev(  char  *  idStr_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  LPCTSTR  str,  unsigned  int  uiDevType_to,  WCHAR  *  wDevIdStr_to,  WCHAR  *  wForwardPath,  HWND  hWnd_notify,  int  iUsrData  )
{
	int					iErr		=	-1;
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	CUS_MODULE_U	*	pModule		=	NULL;

	CQyRWLock		syncObj;
	//
#if  0
	if  (  syncObj.rLock(  pQyMc->cfg.cusModules.mutexName,  pQyMc->cfg.cusModules.uiMilliSeconds_mutex_r,  pQyMc->hSema_syncCusModules,  pQyMc->cfg.cusModules.uiMilliSeconds_sema_r  )  )  return  -1;
#else
	if  (  syncObj.rLock(  pQyMc->pRw_syncCusModules,  pQyMc->cfg.cusModules.uiMilliSeconds_sema_r  )  )  return  -1;
#endif

	if  (  !(  pModule  =  getCusModule(  pQyMc,  CONST_moduleType_vDev,  0,  uiDevType_to,  wDevIdStr_to  )  )  )  goto  errLabel;

	if  (  pModule->vDev.pf_qyVDev_postStr2Dev  &&  pModule->vDev.pf_qyVDev_postStr2Dev(  idStr_from,  tStartTime,  uiTranNo,  uiSeqNo,  str,  uiDevType_to,  wDevIdStr_to,  wForwardPath,  hWnd_notify,  iUsrData  )  )  goto  errLabel;
	
	iErr  =  0;
errLabel:
	return  iErr;

}
  


 int  myVDev_postData2Dev(  unsigned  int  uiVDevId,  char  *  idStr_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  void  *  pQyVDevData,  unsigned  int  uiDataLen,  unsigned  int  uiDevType_to,  WCHAR  *  wDevIdStr_to,  unsigned  int  uiDevIndex  )
{
	int					iErr		=	-1;
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	CUS_MODULE_U	*	pModule		=	NULL;

	CQyRWLock		syncObj;
	//
#if  0
	if  (  syncObj.rLock(  pQyMc->cfg.cusModules.mutexName,  pQyMc->cfg.cusModules.uiMilliSeconds_mutex_r,  pQyMc->hSema_syncCusModules,  pQyMc->cfg.cusModules.uiMilliSeconds_sema_r  )  )  return  -1;
#else
	if  (  syncObj.rLock(  pQyMc->pRw_syncCusModules,  pQyMc->cfg.cusModules.uiMilliSeconds_sema_r  )  )  return  -1;
#endif
	
	if  (  !(  pModule  =  getCusModule(  pQyMc,  CONST_moduleType_vDev,  uiVDevId,  0,  0  )  )  )  goto  errLabel;

	if  (  pModule->vDev.pf_qyVDev_postData2Dev  &&  pModule->vDev.pf_qyVDev_postData2Dev(   idStr_from,  tStartTime,  uiTranNo,  uiSeqNo,  pQyVDevData,  uiDataLen,  uiDevType_to,  wDevIdStr_to,  uiDevIndex  )  )  goto  errLabel;

	iErr  =  0;
errLabel:
	return  iErr;

}



