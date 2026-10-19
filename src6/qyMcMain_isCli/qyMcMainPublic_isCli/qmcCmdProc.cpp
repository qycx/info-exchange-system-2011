
#include	"stdafx.h"
#include	<stddef.h>

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

#include	"qmcCmdProc.h"

#include	"isCliHelpPublic.h"

 //  2009/12/22
 int  newShmCmdIndex(  MC_VAR_isCli  *  pProcInfo,  int  iIndex_sharedObj  )
{
	if  (  iIndex_sharedObj  <  0  ||  iIndex_sharedObj  >=  pProcInfo->cmdsShm.usMaxCnt_qmCmds  )  return  -1;
	
#if  1	
	QM_SHM_CMD	*	pShmCmd		=	getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  iIndex_sharedObj  );
	if  (  !pShmCmd  )  return  -1;
	memset(  pShmCmd,  0,  sizeof(  pShmCmd[0]  )  );
#endif

	return  iIndex_sharedObj;
}



 int  initVar_isGui_qmCmd(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int							iErr				=		-1;
	QY_MC					*	pQyMc				=	(  QY_MC  *  )p0;
	QY_SERVICEGUI_INFO		*	pSci				=	(  QY_SERVICEGUI_INFO  *  )p1;
	//  p2
	MC_VAR_qmCmd			*	pProcInfo			=	(  MC_VAR_qmCmd  *  )pSci->pVar;
	int							i,  j;


	pProcInfo->pQyMcParam  =  pQyMc;
	pProcInfo->pSgiParam  =  pSci;

	//
	_sntprintf(  pProcInfo->who_showInfo,  mycountof(  pProcInfo->who_showInfo  ),  _T(  "IsClient"  )  );

#ifdef  __DEBUG__
	if  (  !pQyMc->ucbUseNamedShm  )  {
		traceLogA(  "Not finished: unnamed shared memory shall be used"  );
		goto  errLabel;
	}
#endif

#if  0
	pProcInfo->cmdShm.hMap  =  OpenFileMapping(  FILE_MAP_ALL_ACCESS,
								FALSE,
								CString(  pQyMc->appObjPrefix  )  +  CONST_shmName_qm_cmd  );
#else
	unsigned  int  uiBufSize_qmShm  =  sizeof(  QM_SHM_CMDS  );
	pProcInfo->cmdsShm.hMap  =  CreateFileMapping(
                 INVALID_HANDLE_VALUE,						// use paging file
                 NULL,										// default security 
                 PAGE_READWRITE,							// read/write access
                 0,											// max. object size 
				 uiBufSize_qmShm,							// buffer size  
                 CQyString(  pQyMc->appParams.appObjPrefix  )  +  CONST_shmName_qm_cmd  );						// name of mapping object 
#endif
	if  (  pProcInfo->cmdsShm.hMap  ==  NULL  ||  GetLastError(  )  !=  ERROR_ALREADY_EXISTS  )  {		 
		traceInfo(  0,  "OpenFileMapping( ) failed."  );
		goto  errLabel;
	}

	pProcInfo->cmdsShm.pBuf  =  (  char  *  )MapViewOfFile(  pProcInfo->cmdsShm.hMap, 
									 FILE_MAP_WRITE,
									 0,
									 0,
									 0  );
	if  (  !pProcInfo->cmdsShm.pBuf  )  goto  errLabel;

	QM_SHM_CMDS	*	pCmds  =  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf;
	traceLogA(  "hint is %S",  pCmds->hint  );

	if  (  pQyMc->appParams.uiTranNo_sharedObj  )  {
		for  (  j  =  20;  j;  j  --,  Sleep(  250  )  )  {
			 for  (  i  =  0;  i  <  mycountof(  pCmds->mems  );  i  ++  )  {
				  if  (  pQyMc->appParams.uiTranNo_sharedObj  ==  pCmds->mems[i].uiTranNo_sharedObj  )  break;				  
			 }
			 if  (  i  <  mycountof(  pCmds->mems  )  )  break;
		}
		if  (  !j  )  goto  errLabel;
		pProcInfo->iIndex_shmCmd  =  i;

		//
		//  DWORD	dwProcessId	=	GetCurrentProcessId(  );
		}
	else  {
		  #ifdef  __DEBUG__
				  if  (  pQyMc->ucbDebugSeparately  )  {
					  pProcInfo->iIndex_shmCmd  =  0;
					  }
				  else  
		  #endif
				  {
					  traceLogA(  "initVar_isGui_qmCmd failed, uiTranNo_sharedObj  is 0"  );
					  goto  errLabel;
				  }
	}
	
	QM_SHM_CMD	*	pShmCmd  =  getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  pProcInfo->iIndex_shmCmd  );
	if  (  !pShmCmd  )  goto  errLabel;

#ifdef  __DEBUG__
		//  qyShowHint(  _T(  "iIndex_shmCmd %d"  ),  pProcInfo->iIndex_shmCmd  );
#endif

	//  qyShowHint(  pCmd->path  );
	//  PostMessage(  pCmd->hWnd_task,  CONST_qyWm_postComm,  CONST_qyWmParam_notifyQmShmCmdStatus,  pCmd->uiTranNo_sharedObj  );

	iErr	=	0;
errLabel:
	if  (  iErr  )  {
		exitVar_isGui_qmCmd(  p0,  p1,  p2  );
	}
	return  iErr;
}

 int  exitVar_isGui_qmCmd(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	QY_MC					*	pQyMc				=	(  QY_MC  *  )p0;
	QY_SERVICEGUI_INFO		*	pSci				=	(  QY_SERVICEGUI_INFO  *  )p1;
	//  p2
	MC_VAR_qmCmd			*	pProcInfo			=	(  MC_VAR_qmCmd  *  )pSci->pVar;

	QM_SHM_CMDS				*	pShmCmds			=	(  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf;
	if  (  pShmCmds  )  {
		QM_SHM_CMD			*	pShmCmd				=	getShmCmdByIndex(  pShmCmds,  pProcInfo->iIndex_shmCmd  );
		if  (  pShmCmd  )  {
			if  (  pQyMc->appParams.uiTranNo_sharedObj  
				&&  pShmCmd->uiTranNo_sharedObj  ==  pQyMc->appParams.uiTranNo_sharedObj  )  
			{				
				pShmCmd->ucbProcessEnd  =  TRUE;				
			}
		}
		PostMessage(  pShmCmds->hWnd_main,  CONST_qyWm_postComm,  CONST_qyWmParam_task_end,  0  );
	}

	if  (  pProcInfo->cmdsShm.pBuf  )  {
		UnmapViewOfFile(  pProcInfo->cmdsShm.pBuf  );  
		pProcInfo->cmdsShm.pBuf  =  NULL;
	}
	if  (  pProcInfo->cmdsShm.hMap  )  {
		CloseHandle(  pProcInfo->cmdsShm.hMap  );  pProcInfo->cmdsShm.hMap  =  NULL;
	}


	return  0;
}

VOID CALLBACK TimerProc_doQmCmdWndProc(  HWND hWnd,  UINT uMsg,  UINT_PTR idEvent,  DWORD dwTime  )
{
	int							iErr			=	-1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );				  
	if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_is  )  goto  errLabel;				  
	QY_SERVICEGUI_INFO		*	pSci;	pSci	=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSci  )  goto  errLabel;
	MC_VAR_qmCmd			*	pProcInfo;
	if  (  !(  pProcInfo  =  (  MC_VAR_qmCmd  *  )pSci->pVar  )  )  goto  errLabel;

	QM_SHM_CMDS				*	pShmCmds		=	(  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf;
	if  (  !pShmCmds  )  goto  errLabel;

	QM_SHM_CMD				*	pShmCmd			=	getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  pProcInfo->iIndex_shmCmd  );
	if  (  !pShmCmd  )  goto  errLabel;

	BOOL						bClose			=	FALSE;

	traceLogA(  "TimerProc_doQmCmdWndProc called"  );

	if  (  pShmCmd->bQuit  )  {
		#ifdef  __DEBUG__
				qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "TimeProc_doQmCmdWndProc: bQuit, now to close window"  )  );
		#endif
		bClose  =  TRUE;  
		iErr  =  0;  goto  errLabel;
	}
	if  (  pShmCmd->uiTranNo_sharedObj  !=  pQyMc->appParams.uiTranNo_sharedObj  )  {
		#ifdef  __DEBUG__
				qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "TimerProc_doQmCmdWndProc: uiTranNo_sharedObj changed, now to close window"  )  );
		#endif
		bClose  =  TRUE;
		iErr  =  0;  goto  errLabel;
	}
	if  (  !IsWindow(  pShmCmds->hWnd_main  )  )  {
		#ifdef  __DEBUG__
				qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "TimerProc_doQmCmdWndProc: mainWnd is invalid, now to close window"  )  );
		#endif
		bClose  =  TRUE;
		iErr  =  0;  goto  errLabel;
	}

	iErr  =  0;
errLabel:
	if  (  bClose  )  {
		SendMessage(  hWnd,  WM_CLOSE,  0,  0  );
	}
	return;
}


 int  doQmCmdWndProc_postComm(  HWND  hWnd,  WPARAM  wParam,  LPARAM  lParam  )
{
	int		iErr	=	-1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );				  
	if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_is  )  goto  errLabel;				  
	QY_SERVICEGUI_INFO		*	pSci;	pSci	=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSci  )  goto  errLabel;
	MC_VAR_qmCmd			*	pProcInfo;
	if  (  !(  pProcInfo  =  (  MC_VAR_qmCmd  *  )pSci->pVar  )  )  goto  errLabel;

	switch  (  wParam  )  {
			case  CONST_qyWmParam_mouseMove:
				  //  qyShowInfo(  CONST_qyShowType_debug,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doQmCmdWndProc_postComm: mouseMove"  )  );
				  viewMediaControl_qmCmd(  (  HWND  )lParam,  -1,  -1,  &pProcInfo->hWnd_mediaControl  );  
				  break;
			default:
					break;
	}

	iErr  =  0;
errLabel:
	return  iErr;
}

  LRESULT  WINAPI  doQmCmdWndProc(HWND hWnd, UINT wMessage, WPARAM wParam, LPARAM lParam)
{
	switch  (  wMessage  )  {
			case  WM_CLOSE:
				  traceLogA(  "doQmCmdWndProc: close"  );
				  DestroyWindow(  hWnd  );
				  PostQuitMessage(  -1  );
				  break;
			case  WM_CREATE:
				  //  traceLogA(  "create"  );
				  //  if  (  IsWindow(  hWnd  )  )  traceLogA(  "Valid"  );
				  SetTimer(  hWnd,  2,  1000,  TimerProc_doQmCmdWndProc  );
				  // 
				  return DefWindowProc(hWnd, wMessage, wParam, lParam);    	
			case  WM_DESTROY:
				  KillTimer(  hWnd,  2  );
				  return DefWindowProc(hWnd, wMessage, wParam, lParam);    	
			case  CONST_qyWm_graphNotify_mediaFile:  {
				  QY_MC	*	pQyMc	=	QY_GET_GBUF(  );				  
				  if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_is  )  goto  errLabel;				  
				  QY_SERVICEGUI_INFO		*	pSci;	pSci	=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
				  if  (  !pSci  )  goto  errLabel;
				  MC_VAR_qmCmd			*	pProcInfo;
				  if  (  !(  pProcInfo  =  (  MC_VAR_qmCmd  *  )pSci->pVar  )  )  goto  errLabel;
				  QM_SHM_CMD			*	pShmCmd				=	getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  pProcInfo->iIndex_shmCmd  );
				  if  (  !pShmCmd  )  goto  errLabel;

				  //  traceLogA(  "graphNotify"  );				  
				  handleGraphEvent_mediaFile(  pProcInfo->pShareMediaFile,  pQyMc->appParams.ucbMediaFile,  pShmCmd->bLooping,  pShmCmd->bPlayThrough  );

				  }
				  break;  
			case  CONST_qyWm_postComm:
				  doQmCmdWndProc_postComm(  hWnd,  wParam,  lParam  );
				  break;
			case  WM_COPYDATA:  
			default:
					return DefWindowProc(hWnd, wMessage, wParam, lParam);    

	}
errLabel:
	return  0;
}



int  doQmCmdMain(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int							iErr					=	-1;
	QY_MC					*	pQyMc					=	(  QY_MC  *  )p0;

	if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_is  )  return  -1;
	QY_SERVICEGUI_INFO		*	pSci					=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	if  (  !pSci  )  return  -1;
	MC_VAR_qmCmd			*	pProcInfo;
	if  (  !(  pProcInfo  =  (  MC_VAR_qmCmd  *  )pSci->pVar  )  )  return  -1;

#if  0
	HINSTANCE					hInstance				=	0;
#ifndef  __WINCE__
		 hInstance  =  AfxGetInstanceHandle( );
#else
		hInstance  =  g_hInst;
#endif
#endif
	WNDCLASS					wcx; 
	HWND						hWnd					=	NULL;
	//  IMoniker				*	pMoniker				=	NULL;
 
	TCHAR						tName[128]				=	_T(  ""  );
	unsigned  int				uiCamType				=	getCamCapType_default(  );

    // Fill in the window class structure with parameters 
    // that describe the main window. 
 
    wcx.style = 0;									// redraw if size changes 
    wcx.lpfnWndProc = doQmCmdWndProc;				// points to window procedure 
    wcx.cbClsExtra = 0;								// no extra class memory 
    wcx.cbWndExtra = 0;								// no extra window memory 
	wcx.hInstance = pQyMc->g_hInst;					// handle to instance 
    wcx.hIcon = 0;									// predefined app. icon 
    wcx.hCursor = 0;								// predefined arrow 
    wcx.hbrBackground = 0;							// white background brush 
    wcx.lpszMenuName =  0;							// name of menu resource 
    wcx.lpszClassName = DEFAULT_qmcCmdProcWndCls;	// name of window class 
 
	// Register the window class. 
	if  (  !RegisterClass(  &wcx  )  )  goto  errLabel;

	hWnd = CreateWindow(  DEFAULT_qmcCmdProcWndCls,  _T(  ""  ),  WS_OVERLAPPEDWINDOW,0,0,0,0,NULL,NULL, pQyMc->g_hInst,  NULL);
	if  (  !hWnd  )  goto  errLabel;

	//  pProcInfo->hWnd_main  =  hWnd;
	pQyMc->gui.hMainWnd  =  hWnd;		//  2010/09/13
	
	//
	QM_SHM_CMD	*	pShmCmd	=	getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  pProcInfo->iIndex_shmCmd  );
	if  (  !pShmCmd  )  goto  errLabel;

	//
	pShmCmd->hWnd_qmShmCmd  =  hWnd;

	//
	if  (  !pShmCmd->path[0]  )  {
		#ifdef  __DEBUG__
			    if  (  pQyMc->ucbDebugSeparately  )  {
					if  (  pQyMc->appParams.ucbAv  )  {
						lstrcpyn(  pShmCmd->path,  _T(  "\\\\?\\usb#vid_1871&pid_01f0&mi_00#6&1c20a68f&0&0000#{65e8773d-8f56-11d0-a3b9-00a0c9223196}\\global"  ),  mycountof(  pShmCmd->path  )  );
						}
					else  if  (  pQyMc->appParams.ucbMediaFile  )  {
							  lstrcpyn(  pShmCmd->path,  _T(  "C:\\tttbbb\\lake.wmv"  ),  mycountof(  pShmCmd->path  )  );							
					}
					}
				else  
		#endif
					goto  errLabel;
	}


	SAMPLE_grabberCb_cache	cache;
	memset(  &cache,  0,  sizeof(  cache  )  );

	if  (  pQyMc->appParams.ucbAv  )  {

		//  
		if  (  openLocalVideo(  (  MC_VAR_common  *  )pProcInfo,  uiCamType,  pShmCmd->path,  NULL,  NULL,  NULL,  0,  &pProcInfo->vc  )  )  goto  errLabel;

		//  memcpy(  &pProcInfo->vh_org,  &pProcInfo->vc.vh_pic,  sizeof(  pProcInfo->vh_org  )  );
		memcpy(  &pProcInfo->vh_org,  pProcInfo->vc.bOrg2RgbBufInited  ?  &pProcInfo->vc.vh_rgb  :  &pProcInfo->vc.vh_org,  sizeof(  pProcInfo->vh_org  )  );

		}
	else  if  (  pQyMc->appParams.ucbMediaFile  )  {
			  LONG_PTR lInstanceData	=	0;

			  //  if  (  initShareMediaFile(  pShmCmd->path,  pProcInfo->hWnd_main,  lInstanceData,  &pProcInfo->pShareMediaFile  )  )  goto  errLabel;
			  if  (  initShareMediaFile(  pShmCmd->path,  pQyMc->gui.hMainWnd,  lInstanceData,  &pProcInfo->pShareMediaFile  )  )  goto  errLabel;
			  if  (  !bGetCapturePara_shareMediaFile(  (  MC_VAR_common  *  )pProcInfo,  0,  0,  pProcInfo->pShareMediaFile,  &pProcInfo->ah_org.wfx,  &pProcInfo->vh_org,  &cache  )  )  goto  errLabel;
			  }
	else  {
		  traceLogA(  "doQmCmdMain: No cmd"  );
		  goto  errLabel;
	}

	unsigned  int								nBytes_audioPktHead		=	0;
	unsigned  int								nBytes_audioPktData		=	0;
	unsigned  int								nBytes_videoPktHead		=	0;
	unsigned  int								nBytes_videoPktData		=	0;
	unsigned  short								usMaxCnt_a				=	0;
	unsigned  short								usMaxCnt_v				=	0;

	nBytes_audioPktHead  =  sizeof(  QM_SHM_pktHead  );
	nBytes_audioPktData  =  cache.nBytes_pkt;
	usMaxCnt_a  =  (  cache.nBytes_pkt  )  ?  (  2  *  cache.nAvgBytesPerSec  /  cache.nBytes_pkt  )  :  3;
	//
	nBytes_videoPktHead  =  sizeof(  QM_SHM_pktHead  );
	nBytes_videoPktData  =  pProcInfo->vh_org.bih.biSizeImage;
	usMaxCnt_v  =  8;

	//
	_sntprintf(  tName,  mycountof(  tName  ),  _T(  "%s%u"  ),  CONST_shmName_qm_data,  pQyMc->appParams.uiTranNo_sharedObj  );
	pProcInfo->dataShm.uiBufSize_qmShm  =  offsetof(  QM_SHM_data,  buf  )  +  (  nBytes_audioPktHead  +  nBytes_audioPktData  )  *  usMaxCnt_a  +  (  nBytes_videoPktHead  +  nBytes_videoPktData  )  *  usMaxCnt_v;
	if  (  !pProcInfo->dataShm.uiBufSize_qmShm  )  goto  errLabel;
	pProcInfo->dataShm.hMap  =  CreateFileMapping(
                 INVALID_HANDLE_VALUE,						// use paging file
                 NULL,										// default security 
                 PAGE_READWRITE,							// read/write access
                 0,											// max. object size 
				 pProcInfo->dataShm.uiBufSize_qmShm,				// buffer size  
                 CQyString(  pQyMc->appParams.appObjPrefix  )  +  tName  );						// name of mapping object 
	if  (  pProcInfo->dataShm.hMap  ==  NULL  ) { 
		 traceLogA("Could not create file mapping object (%d).\n",  GetLastError());
		 goto  errLabel;	 
	}
	if  (  GetLastError(  )  ==  ERROR_ALREADY_EXISTS  )  {
		qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doQmCmdMain failed: shm already exists"  )  );
		goto  errLabel;
	}
	pProcInfo->dataShm.pBuf  =  (  char  *  ) MapViewOfFile(pProcInfo->dataShm.hMap,   // handle to map object
						                        FILE_MAP_ALL_ACCESS,			// read/write permission
						                        0,                   
						                        0,                   
												pProcInfo->dataShm.uiBufSize_qmShm  );           
	if  (  pProcInfo->dataShm.pBuf == NULL  )  {
		 traceLogA("Could not map view of file (%d).\n", GetLastError()); 
		 goto  errLabel;	 
	}
	memset(  pProcInfo->dataShm.pBuf,  0,  pProcInfo->dataShm.uiBufSize_qmShm  );
	QM_SHM_data	*	pShm	=	(  QM_SHM_data  *  )pProcInfo->dataShm.pBuf;
#ifdef  __DEBUG__
		lstrcpyn(  pShm->hint,  _T(  "Hello"  ),  mycountof(  pShm->hint  )  );
#endif
	memcpy(  &pShm->ah_org,  &pProcInfo->ah_org,  sizeof(  pShm->ah_org  )  );
	memcpy(  &pShm->vh_org,  &pProcInfo->vh_org,  sizeof(  pShm->vh_org  )  );
	//
	pShm->a.nBytes_pktHead  =  nBytes_audioPktHead;
	pShm->a.nBytes_pktData  =  nBytes_audioPktData;
	pShm->v.nBytes_pktHead  =  nBytes_videoPktHead;
	pShm->v.nBytes_pktData  =  nBytes_videoPktData;
	pShm->a.usMaxCnt  = usMaxCnt_a;
	pShm->v.usMaxCnt  =  usMaxCnt_v;
	//
	if  (  !pShm->a.usMaxCnt  ||  !pShm->v.usMaxCnt  )  {
		qyShowInfo(  CONST_qyShowType_debug,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doQmCmdMain failed: a.usMaxCnt or v.usMaxCnt is 0"  )  );
		goto  errLabel;
	}
	//
	pShm->a.iIndex_post  =  -1;
	pShm->a.iIndex_get  =  -1;
	pShm->v.iIndex_post  =  -1;
	pShm->v.iIndex_get  =  -1;
	//
	if  (  pProcInfo->pShareMediaFile  )  {
		pShm->ucbAudioOnly  =  bAudioOnly(  pProcInfo->pShareMediaFile  );
		pShm->ucbNoAudio  =  bNoAudio(  pProcInfo->pShareMediaFile  );
		pShmCmd->psCurrent  =  getShareMediaFileState(  pProcInfo->pShareMediaFile  );
	}

	_sntprintf(  tName,  mycountof(  tName  ),  _T(  "%s%u"  ),  CONST_evtName_qm_data_a,  pQyMc->appParams.uiTranNo_sharedObj  );
	pProcInfo->a.hEvent_toSendData = CreateEvent( NULL, FALSE, FALSE, CQyString(  pQyMc->appParams.appObjPrefix  )  +  tName  );
	if ( NULL == pProcInfo->a.hEvent_toSendData ) goto  errLabel;
	_sntprintf(  tName,  mycountof(  tName  ),  _T(  "%s%u"  ),  CONST_evtName_qm_data_v,  pQyMc->appParams.uiTranNo_sharedObj  );
	pProcInfo->v.hEvent_toSendData = CreateEvent( NULL, FALSE, FALSE, CQyString(  pQyMc->appParams.appObjPrefix  )  +  tName  );
	if ( NULL == pProcInfo->v.hEvent_toSendData ) goto  errLabel;
	_sntprintf(  pProcInfo->a.mutexName_syncShmData,  mycountof(  pProcInfo->a.mutexName_syncShmData  ),  _T(  "%s%u"  ),  CONST_mutexName_qm_syncData_a,  pQyMc->appParams.uiTranNo_sharedObj  );
	_sntprintf(  pProcInfo->v.mutexName_syncShmData,  mycountof(  pProcInfo->v.mutexName_syncShmData  ),  _T(  "%s%u"  ),  CONST_mutexName_qm_syncData_v,  pQyMc->appParams.uiTranNo_sharedObj  );

	//
	pShmCmd->ucbShmCmdInited  =  TRUE;

	//
	//  PostMessage(  pShmCmd->hWnd_progress,  CONST_qyWm_postComm,  CONST_qyWmParam_notifyQmShmCmdStatus,  pShmCmd->iIndex_sharedObj  );
	PostMessage(  pShmCmd->hWnd_progress,  CONST_qyWm_postComm,  CONST_qyWmParam_notifyQmShmCmdStatus,  pShmCmd->uiTranNo_sharedObj  );	//  2010/12/29

	//
	if  (  pQyMc->appParams.ucbAv  )  {
		if  (  pProcInfo->vc.bCapDevConnected  )  {
			if  (  startCapture(  &pProcInfo->vc  )  )  goto  errLabel;
		}
		}
	else  if  (  pQyMc->appParams.ucbMediaFile  )  {
			  if  (  runShareMediaFile(  pProcInfo->pShareMediaFile  )  )  goto  errLabel;
	}

#ifdef  __DEBUG__
		//  qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "startCapture ok"  )  );

	if  (  0  )  {
		int  nCmdShow  =  SW_SHOW;
		//  int  nCmdShow  =  SW_HIDE;

		if  (  pQyMc->ucbDebugSeparately  )  {
			ShowWindow(hWnd, nCmdShow); 
			UpdateWindow(hWnd); 
		}
	}
#endif

	MSG msg; 
	BOOL fGotMessage;
    while ((fGotMessage = GetMessage(&msg, (HWND) NULL, 0, 0)) != 0 && fGotMessage != -1) 
    { 
        TranslateMessage(&msg); 
        DispatchMessage(&msg); 
    } 
    //  msg.wParam; 


	iErr  =  0;

errLabel:

	if  (  pProcInfo->vc.bCapDevConnected  )  {
		//  
		closeLocalVideo(  (  MC_VAR_common  *  )pProcInfo,  0,  &pProcInfo->vc  );
	}
	if  (  pProcInfo->pShareMediaFile  )  exitShareMediaFile(  &pProcInfo->pShareMediaFile  );

	if  (  pProcInfo->a.hEvent_toSendData  )  {
		CloseHandle(  pProcInfo->a.hEvent_toSendData  );  pProcInfo->a.hEvent_toSendData  =  NULL;
	}
	if  (  pProcInfo->v.hEvent_toSendData  )  {
		CloseHandle(  pProcInfo->v.hEvent_toSendData  );  pProcInfo->v.hEvent_toSendData  =  NULL;
	}

	if  (  pProcInfo->dataShm.pBuf  )  {
		UnmapViewOfFile(  pProcInfo->dataShm.pBuf  );  
		pProcInfo->dataShm.pBuf  =  NULL;
	}
	if  (  pProcInfo->dataShm.hMap  )  {
		CloseHandle(  pProcInfo->dataShm.hMap  );  pProcInfo->dataShm.hMap  =  NULL;
	}

	if  (  IsWindow(  hWnd  )  )  {
		DestroyWindow(  hWnd  );
	}

	return  iErr;
}


 //  2005/05/01
 int  doCmdBySubProcess(  void  *  p0,  LPCTSTR  cmdStr,  LPCTSTR  cmdParam,  HANDLE  *  phProcess,  DWORD  *  pdwProcessId  )
{
	 int							iErr		=		-1;
	 TCHAR							buf[4096];
	 STARTUPINFO					si;
	 PROCESS_INFORMATION			pi;
	 TCHAR							tmpFileName[MAX_PATH  +  1];

	 if  (  !cmdStr  )  return  -1;

	 memset(  &pi,  0,  sizeof(  pi  )  );
	 memset(  &si,  0,  sizeof(  STARTUPINFO  )  );
	 si.cb  =  sizeof(  STARTUPINFO  );
#ifndef  __WINCE__
	 si.dwFlags  =  STARTF_FORCEOFFFEEDBACK;
#endif

	 GetModuleFileName(  NULL,  tmpFileName,  mycountof(  tmpFileName  )  );
	 if  (  tQyQuoteFileName(  tmpFileName,  mycountof(  tmpFileName  )  )  )  goto  errLabel;

	 _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s %s"  ),  tmpFileName,  cmdStr  );
	 if  (  cmdParam  )  _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%s%s"  ),  buf,  cmdParam  );
	 if  (  !CreateProcess(  NULL,  buf,  NULL,  NULL,  0,  0,  NULL,  NULL,  &si,  &pi  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:

	 if  (  pi.hThread  )  {  CloseHandle(  pi.hThread  );  pi.hThread  =  NULL;  }
	 if  (  iErr  )  {
		 if  (  pi.hProcess  )  {  CloseHandle(  pi.hProcess  );  pi.hProcess  =  NULL;  }
	 }

	 if  (  !iErr  )  {
		 if  (  phProcess  )  *phProcess  =  pi.hProcess;
		 else  {  CloseHandle(  pi.hProcess  );  pi.hProcess  =  NULL;  }	//  2005/10/08，增加这一句，以方便在不需要传出句柄时，将句柄清除
		 if  (  pdwProcessId  )  *pdwProcessId  =  pi.dwProcessId;
	 }


	 //  traceLogA(  "doCmdBySubProcess{%s}%s, pid is %d",  buf,  (  iErr  ?  "failed"  :  "ok?  ),  pi.dwProcessId  );  

	 return  iErr;
}
