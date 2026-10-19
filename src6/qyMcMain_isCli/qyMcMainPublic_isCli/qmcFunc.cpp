
#include	"stdafx.h"
#include	<time.h>
#include	"qyMcMainCommon.h"
#include	"qyWnd.h"
#include	"qmcCmdProc.h"
#include	"qmcVWall.h"


 QY_DMITEM  CONST_capTypeTable[]  =
{
	{	CONST_capType_av,				_T(  "av"  ),	},
	{	CONST_capType_screen,			_T(  "screen"  ),	},
	{	CONST_capType_mediaFile,		_T(  "mediaFile"  ),	},
	{	CONST_capType_mediaDevice,		_T(  "mediaDevice"  ),  },
	{	-1,				},
};

 QY_DMITEM  CONST_subCapTypeTable[]  =
{
	{	CONST_subCapType_webcam,		_T(  "webcam"  ),	},
	{	-1,													},	
};

 //
  QY_DMITEM  CONST_rulePriorityTable[]  =
 {
	 {	CONST_vwRuleType_dynBmp,				(  TCHAR  *  )20,	},
	 {	CONST_vwRuleType_conference_imGrp,		(  TCHAR  *  )5,	},
	 {	CONST_vwRuleType_conference_imGrpMem,	(  TCHAR  *  )8,	},
	 //
	 {	CONST_vwRuleType_imObjs,				(  TCHAR  *  )1,	},		//  2012/04/02
	 {	CONST_vwRuleType_messenger,				(  TCHAR  *  )2,	},
	 {	-1,		},
 };

 //  2012/04/02. 仅用来显示
 QY_DMITEM  CONST_vwRuleTypeTable[]  =
 {
	 {	CONST_vwRuleType_dynBmp,					_T(  "Img"  ),		},
	 {	CONST_vwRuleType_conference_imGrp,			_T(  "Grp"  ),		},
	 {	CONST_vwRuleType_conference_imGrpMem,		_T(  "GrpMem"  ),		},
	 //
	 {	CONST_vwRuleType_imObjs,					_T(  "ImObjs"  ),	},
	 {	CONST_vwRuleType_messenger,					_T(  "Msgr"  ),	},

	 {	-1,		},
 };



 //
   int  setModalWnd(  HWND  hDlg  )
{
	 return  setModalWnd_func(  hDlg,  FALSE  );
}

 int  setModalWnd_func(  HWND  hDlg,  BOOL  bFileDialog  )
{
	int					iErr		=	-1;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	if  (  IsWindow(  pProcInfo->hWnd_menu  )  )  return  -1;

	if  (  !bFileDialog  )  {
		if  (  IsWindow(  pProcInfo->hWnd_modal  )  )  {
			SendMessage(  pProcInfo->hWnd_modal,  WM_CLOSE,  0,  0  );
		}
		if  (  IsWindow(  pProcInfo->hWnd_modal  )  )  goto  errLabel;
		
		pProcInfo->hWnd_modal  =  hDlg;
		}
	else  {
		  if  (  IsWindow(  pProcInfo->hWnd_fileDialog  )  )  {
			  SendMessage(  pProcInfo->hWnd_fileDialog,  WM_CLOSE,  0,  0  );
		  }
		  if  (  IsWindow(  pProcInfo->hWnd_fileDialog  )  )  goto  errLabel;

		  //  pProcInfo->bWndModal_fileDialog  =  bFileDialog;
		  pProcInfo->hWnd_fileDialog  =  hDlg;
		  pProcInfo->dwStartTickCnt_fileDialog  =  GetTickCount(  );
	}

	iErr  =  0;
errLabel:
	return  iErr;
}


 BOOL  bSupported_aec(  )
{
	BOOL  bRet  =  FALSE;

	//  Figure out what os version we're on. We currently support echo-cancellation only on windows vista and 7.
	OSVERSIONINFOEX  osvi;
	ZeroMemory(  &osvi,  sizeof(  OSVERSIONINFOEX  )  );
	osvi.dwOSVersionInfoSize  =  sizeof(  OSVERSIONINFOEX  );
	if  (  !GetVersionEx(  (  OSVERSIONINFO  *  )  &osvi  )  )  
	{
		printf(  "\t...  cannot determine platform;assuming AEC is unsupported:0x%1xL\n",  GetLastError(  )  );
		//  AEC_SUPPORTED  =  0;
	}
	else if  (  osvi.dwMajorVersion  >=  6  )  {
		if  (  osvi.dwMajorVersion  ==  6  &&  osvi.dwMinorVersion  ==  0  )  {
			printf(  "\t...  AEC  is supported on this platform(  Windows Vista  )\n"  );
		}
		else  {
			printf(  "\t...  AEC  is supported on this platform(  Windows 7  or  later  )\n"  );
		}

		//  AEC_SUPPORTED  =  1;
		bRet  =  TRUE;
	}
	else  {
		printf(  "\t...  AEC is not supported on Windows xp and earlier\n"  );
		//  AEC_SUPPORTED  =  0;
	}

#ifdef  __DEBUG__
		#if  0
			bRet  =  FALSE;
			traceLog(  _T(  "TEST: aec disabed"  )  );
		#endif
#endif

	return  bRet;
}


  __declspec(  dllexport  )  void  *  qyWnd_getGuiData(  void  *  pDlg  )
{
	if  (  !pDlg  )  return  NULL;
	return  (  (  CQyWnd  *  )pDlg  )->getGuiData(  );
}


  __declspec(  dllexport  )  void  *  qyWnd_getVar(  void  *  pDlg  )
{
	if  (  !pDlg  )  return  NULL;
	return  (  (  CQyWnd  *  )pDlg  )->getVar(  );
}

 __declspec(  dllexport  )  HWND  qyWnd_getHwnd(  void  *  pDlg  )
{
	if  (  !pDlg  )  return  NULL;
	return  (  (  CQyWnd  *  )pDlg  )->m_hWnd;
}

 __declspec(  dllexport  )  BOOL  qyWnd_Attach(  void  *  pDlgParam,  HWND hWndNew  )
{
	if  (  !pDlgParam  )  return  FALSE;
	if  (  !IsWindow(  hWndNew  )  )  return  FALSE;

	CQyWnd  *  pDlg  =  (  CQyWnd  *  )pDlgParam;

	SetWindowLong(  hWndNew,  GWLP_USERDATA,  (  LONG_PTR  )pDlg  );
	pDlg->m_hWnd  =  hWndNew;

	return  TRUE;
}

  __declspec(  dllexport  )  void  freeQyWnd(  void  *  pWndParam  )
 {
	 if  (  pWndParam  )  {
		 CQyWnd  *  pWnd  =  (  CQyWnd  *  )pWndParam;
		 if  (  IsWindow(  pWnd->m_hWnd  )  )  {
			 MACRO_qyAssert(  0,  _T(  "Serious error: freeQyWnd, hWnd is still alive"  )  );
		 }

		 delete  (  CQyWnd  *  )pWnd;
	 }
 }

 

 MIS_CNT  *  getMisCntByName(  void  *  pQyMcParam,  MC_VAR_isCli  *  pProcInfo,  LPCTSTR  misServName  )
{
	 int						iErr								=	-1;
	 QY_MC					*	pQyMc								=	(  QY_MC  *  )pQyMcParam;
	 int						i;

	 if  (  !pQyMc  )  pQyMc  =  QY_GET_GBUF(  );
	 if  (  !pProcInfo  )  {
		 pProcInfo		=	QY_GET_procInfo_isCli(  );
		 if  (  !pProcInfo  )  goto  errLabel;
	 }

	 for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  {
		  if  (  !lstrcmpi(  pProcInfo->misCnts[i].cfg.misServName,  misServName  )  )  return  &pProcInfo->misCnts[i];
	 }
errLabel:
	 return  NULL;
}


 MIS_CNT  *  getMisCntByIndex(  void  *  p0,  MC_VAR_isCli  *  pProcInfo,  int  iIndex  )
{
	if  (  iIndex  <  0  ||  iIndex  >  mycountof(  pProcInfo->misCnts  )  )  return  NULL;

	return  &pProcInfo->misCnts[iIndex];
}


 int  getMisCntIndexByName(  void  *  p0,  MC_VAR_isCli  *  pProcInfo,  LPCTSTR  misServName  )
{
	int							iErr							=	-1;
	int							i								=	0;

	if  (  !misServName  )  return  -1;

	for  (  i  =  0;  i  <  mycountof(  pProcInfo->misCnts  );  i  ++  )  {
		if  (  !lstrcmpi(  pProcInfo->misCnts[i].cfg.misServName,  misServName  )  )  return  i;
	}

//  errLabel:
	return  -1;
}

  char  *  displayShortTime(  time_t  t,  char  *  timeBuf,  unsigned  int  len  )
{
	char	timeBuf_t[CONST_qyTimeLen  +  1]	=	"";
	char	curTimeBuf[CONST_qyTimeLen  +  1]	=	"";
	char	displayBuf[128  +  1]				=	"";

	getCurTime(  curTimeBuf  );
	getTimeStr(  t,  timeBuf_t,  mycountof(  timeBuf_t  )  );

	qyDisplayTime(  timeBuf_t,  displayBuf,  mycountof(  displayBuf  )  );

	if  (  _strnicmp(  timeBuf_t,  curTimeBuf,  4  )  )  safeStrnCpy(  displayBuf,  timeBuf,  min(  len,  4  +  1  )  );
	else  if  (  _strnicmp(  timeBuf_t  +  4,  curTimeBuf  +  4,  4  )  )  safeStrnCpy(  displayBuf  +  5,  timeBuf,  min(  len,  5  +  1  )  );
	else  safeStrnCpy(  displayBuf  +  11,  timeBuf,  min(  len,  5  +  1  )  );

	return  timeBuf;
}

//
//  ¶Ô¹²Ïí¶ÔÏóÊý×éµÄ¿Õ¼äµÄ¹ÜÀí
//  ÓÉÖ÷Ïß³ÌÀ´·ÖÅä£¬ÓÉ¶ÔÏó×Ô¼ºÀ´Ê¹ÓÃ¡£¶ÔÏó½áÊøÊ±Í¨ÖªÖ÷Ïß³Ì£¬Ö÷Ïß³ÌÀ´ÊÍ·Å¶ÔÏó
//

 QY_SHARED_OBJ  *  getSharedObjByIndex(  MC_VAR_isCli  *  pProcInfo,  int  index  )
{

	if  (  !pProcInfo  )  return  NULL;
	if  (  !pProcInfo->pSharedObjs  )  return  NULL;
	if  (  index  <  0  ||  index  >  pProcInfo->cfg.usMaxCnt_pSharedObjs  )  return  NULL;

	return  &pProcInfo->pSharedObjs[index];
}

 CAP_procInfo_audioU  *  getCapAudioBySth(  MC_VAR_isCli  *  pProcInfo,  int  index,  unsigned  int  uiCapType  )
{
	BOOL							bRet				=	FALSE;

	if  (  !pProcInfo  )  return  NULL;

	if  (  index  <  0  ||  index  >=  pProcInfo->cfg.usMaxCnt_capProcInfoAudios  )  return  NULL;
	//  if  (  !index  )  return  NULL;
	if  (  !index  )  return  (  CAP_procInfo_audioU  *  )&pProcInfo->av.localAv.recordSoundProcInfo;
	if  (  uiCapType  )  {
		if  (  pProcInfo->pCapProcInfoAudios[index].common.uiType  !=  uiCapType  )  return  NULL;
	}
	return  &pProcInfo->pCapProcInfoAudios[index];
}

 //  if  uiCapType is 0, don't need to check capType. and if uiCapType is not 0, ...
 CAP_procInfo_bmpU  *  getCapBmpBySth(  MC_VAR_isCli  *  pProcInfo,  int  index,  unsigned  int  uiCapType  )
{
	BOOL							bRet				=	FALSE;

	if  (  !pProcInfo  )  return  NULL;

	if  (  index  <  0  ||  index  >=  pProcInfo->cfg.usMaxCnt_capProcInfoBmps  )  return  NULL;
	//  if  (  !index  )  return  NULL;
	if  (  !index  )  return  (  CAP_procInfo_bmpU  *  )&pProcInfo->av.localAv.videoCaptureProcInfo;	//  2009/06/02
	if  (  uiCapType  )  {
		if  (  pProcInfo->pCapProcInfoBmps[index].common.uiType  !=  uiCapType  )  return  NULL;
	}
	return  &pProcInfo->pCapProcInfoBmps[index];
}

  QM_SHM_CMD  *  getShmCmdByIndex(  QM_SHM_CMDS  *  pCmds,  int  iIndex  )
{
	 if  (  !pCmds  )  return  NULL;
	 if  (  iIndex  <  0  ||  iIndex  >=  mycountof(  pCmds->mems  )  )  return  NULL;
	 return  &pCmds->mems[iIndex];
}
 int  showTaskStatusFunc(  void  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_taskSender,  QY_MESSENGER_ID  *  pIdInfo_taskReceiver,  BOOL  bImGrpMem,  unsigned  short  cmdCode,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiContentType,  int  iTaskId,  int  iStatus,  unsigned  char  ucbNotification,  QY_MESSENGER_ID	*	pIdInfo_from,  unsigned  char  ucPercent,  unsigned  __int64  ui64Len_recvd,  LPCTSTR  fileName,  LPCTSTR  fullFilePath  )
{
	QY_MC				*	pQyMc				=	QY_GET_GBUF(  );
	//  CWnd				*	pMainWnd			=	AfxGetApp(  )->m_pMainWnd;
	MIS_MSG_TASKSTATUS		msgTaskStatus;

	//  if  (  !pIdInfo_taskSender->ui64Id  ||  !pIdInfo_taskReceiver->ui64Id  )  {
	//  	traceLogA(  "showTaskStatus err:"  );  return  -1;
	//  }
   
	//  ±¨¸æ×´Ì¬
	memset(  &msgTaskStatus,  0,  sizeof(  msgTaskStatus  )  );
	msgTaskStatus.uiType  =  CONST_misMsgType_taskStatus;
	msgTaskStatus.pMisCnt  =  pMisCnt;
	if  (  pIdInfo_logicalPeer  )  msgTaskStatus.idInfo_logicalPeer.ui64Id  =  pIdInfo_logicalPeer->ui64Id;
	//
	if  (  pIdInfo_taskSender  )  msgTaskStatus.idInfo_taskSender.ui64Id  =  pIdInfo_taskSender->ui64Id;
	if  (  pIdInfo_taskReceiver  )  msgTaskStatus.idInfo_taskReceiver.ui64Id  =  pIdInfo_taskReceiver->ui64Id;
	//
	msgTaskStatus.bImGrpMem  =  bImGrpMem;			//  
	//
	msgTaskStatus.cmdCode  =  cmdCode;				//  2009/10/18
	msgTaskStatus.tStartTime  =  tStartTime;		//  2009/10/18
	msgTaskStatus.uiTranNo  =  uiTranNo;			//  2009/10/18
	msgTaskStatus.uiContentType  =  uiContentType;	//  
	msgTaskStatus.iTaskId  =  iTaskId;
	msgTaskStatus.iStatus  =  iStatus;
	if  (  ucbNotification  )  {
		msgTaskStatus.ucbNotification  =  TRUE;
		if  (  pIdInfo_from  )  msgTaskStatus.u.notification.idInfo_from.ui64Id  =  pIdInfo_from->ui64Id;
		safeTcsnCpy(  fileName,  msgTaskStatus.u.notification.tBuf,  mycountof(  msgTaskStatus.u.notification.tBuf  )  );
		}
	else  {
		  msgTaskStatus.u.transferFileStatus.ucPercent	=	ucPercent;
		  msgTaskStatus.u.transferFileStatus.ui64Len_recvd  =  ui64Len_recvd;
		  if  (  fileName  )  lstrcpyn(  msgTaskStatus.u.transferFileStatus.fileName,  fileName,  mycountof(  msgTaskStatus.u.transferFileStatus.fileName  )  );
		  if  (  fullFilePath  )  lstrcpyn(  msgTaskStatus.u.transferFileStatus.fullFilePath,  fullFilePath,  mycountof(  msgTaskStatus.u.transferFileStatus.fullFilePath  )  );
	}

	//
	qPostMsg(  &msgTaskStatus,  sizeof(  msgTaskStatus  ),  &pQyMc->gui.processQ  );
	PostMessage(  g_pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );    

	return  0;
}
 int  showNotification(  void  *  pMisCnt,  QY_MESSENGER_ID  *  pIdInfo_logicalPeer,  QY_MESSENGER_ID  *  pIdInfo_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiContentType,  LPCTSTR  hint  )
{
	return  showTaskStatusFunc(  pMisCnt,  pIdInfo_logicalPeer,  NULL,  NULL,  0,  0,  tStartTime,  uiTranNo,  uiContentType,  0,  0,  TRUE,  pIdInfo_from,  0,  0,  hint,  NULL  );
}
 MIS_CHANNEL  *  getChannelByType(  MIS_CNT  *  pMisCnt,  unsigned  int  uiChannelType  )
{
	int		i;
	
	if  (  !pMisCnt  )  return  NULL;

	if  (  !uiChannelType  )  return  &pMisCnt->channels[0];

	for  (  i  =  0;  i  <  mycountof(  pMisCnt->channels  );  i  ++  )  {
		 if  (  pMisCnt->channels[i].uiType  ==  uiChannelType  )  return  &pMisCnt->channels[i];
	}

	return  &pMisCnt->channels[0];

}



 BOOL  bChannelOk(  QY_MC  *  pQyMc,  MIS_CNT  *  pMisCnt,  MIS_CHANNEL  *	pChannel  )
{
	if  (  !pChannel  )  return  FALSE;

	if  (  !pQyMc  )  pQyMc  =  QY_GET_GBUF(  );

	//
	if  (  pChannel->bSessionOpen  )  {
		DWORD	dwTickCnt  =  GetTickCount(  );
		if  (  pChannel->uiType  !=  CONST_channelType_talking  )  {
			if  (  dwTickCnt  -  pChannel->status.dwTickCnt_lastStartToRecv  >  pQyMc->cfg.iTimeoutInMs_channelIdle_others
				&&  dwTickCnt  -  pChannel->status.dwTickCnt_lastEndSending  >  pQyMc->cfg.iTimeoutInMs_channelIdle_others  )
			{
				qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Channel %s timeout, idle too long, iTimeoutInMs_channelsIdle_others %d"  ),  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  ),  pQyMc->cfg.iTimeoutInMs_channelIdle_others  );
				return  FALSE;
			}
			#if  0
				if  (  dwTickCnt  -  pChannel->status.dwTickCnt_lastStartToRecv  >  pQyMc->cfg.iTimeoutInMs_channelIdle_recv_others  )  {
					qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Channel %s timeout, idle too long, iTimeoutInMs_channelsIdle_recv_others %d"  ),  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  ),  pQyMc->cfg.iTimeoutInMs_channelIdle_recv_others  );
					return  FALSE;
				}
			#endif
			}
		else  {
			  if  (  dwTickCnt  -  pChannel->status.dwTickCnt_lastStartToRecv  >  pQyMc->cfg.iTimeoutInMs_channelIdle_recv_talk  )  {				
				  qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Channel %s timeout, idle too long, iTimeoutInMs_channelsIdle_recv_talk %d"  ),  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  ),  pQyMc->cfg.iTimeoutInMs_channelIdle_recv_talk  );
				  return  FALSE;
			  }
			  //  2012/05/21.以下为了防止误判,用另一个变量做了一个辅助. 这样让判断至少在超时2次后才生效
			  BOOL	tmp_bOk  =  TRUE;
			  if  (  !isQ2Empty(  &pChannel->toSendQ2  )  )  {	//  2012/05/21
				  if  (  dwTickCnt  -  pChannel->status.dwTickCnt_lastEndSending  >  pQyMc->cfg.iTimeoutInMs_channelIdle_others  )  {
					  tmp_bOk  =  FALSE;
				  }
			  }
			  if  (  tmp_bOk  )  pChannel->status.dwTickCnt_noSending_start  =  0;
			  if  (  pChannel->status.dwTickCnt_noSending_start  )  {
				  if  (  dwTickCnt  -  pChannel->status.dwTickCnt_noSending_start  >  pQyMc->cfg.iTimeoutInMs_channelIdle_others  +  5000  )  {
					  qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Channel %s timeout, idle too long, iTimeoutInMs_channelsIdle_others %d"  ),  qyGetDesByType1(  CONST_channelTypeTable,  pChannel->uiType  ),  pQyMc->cfg.iTimeoutInMs_channelIdle_others  );
					  return  FALSE;
				  }
			  }
			  if  (  !tmp_bOk  )  {
				  if  (  !pChannel->status.dwTickCnt_noSending_start  )  {
					  pChannel->status.dwTickCnt_noSending_start  =  dwTickCnt;
				  }
			  }
		}
	}
	
	return  (  !pQyMc->bQuit  &&  pChannel->bSessionOpen  &&  !pChannel->status.ulbSessionErr  );

}


 BOOL  bMessengerOnline(  QY_MC  *  pQyMc  )
{
	BOOL					bRet	=	FALSE;
	QY_SERVICEGUI_INFO	*	pSci  =  (  QY_SERVICEGUI_INFO  *  )getServiceGuiInfo(  pQyMc,  pQyMc->iServiceId  );
	if  (  !pSci  )  goto  errLabel;
	MC_VAR_isCli			*	pVar	=	(  MC_VAR_isCli  *  )pSci->pVar;
	if  (  !pVar  )  goto  errLabel;
	int						i;

	for  (  i  =  0;  i  <  mycountof(  pVar->misCnts  );  i  ++  )  {
		 if  (  pVar->misCnts[i].cfg.dynCfg.cnt.usCntPort  )  {
			 if  (  bChannelOk(  pQyMc,  &pVar->misCnts[i],  getChannelByType(  &pVar->misCnts[i],  CONST_channelType_talking  )  )  )  {
				 bRet  =  TRUE;  goto  errLabel;
			 }
		 }
	}
errLabel:
	return  bRet;

}
 int  brushDc(  COLORREF  color,  HDC  hDc,  int  x,  int  y,  int  iW,  int  iH  )
{
	int		iErr	=	-1;

	HBRUSH	hBrush		=	NULL;
	HBRUSH	oldhBrush	=	NULL;

	hBrush  =	CreateSolidBrush(  color  );
	if  (  !hBrush  )  goto  errLabel;
	oldhBrush = ( HBRUSH )SelectObject( hDc, hBrush );
	if  (  !isHandleValid(  oldhBrush  )  )  goto  errLabel;
	
	if  (  !PatBlt( hDc, x, y, iW, iH, PATCOPY )  )  goto  errLabel;

	iErr  =  0;
errLabel:

	if  (  isHandleValid(  oldhBrush  )  )  {
		SelectObject(  hDc,  oldhBrush  );
	}
	if  (  isHandleValid(  hBrush  )  )  DeleteObject(  hBrush  );
	return  iErr;
}


 //  2013/06/13
 BOOL  bApp_ts(  )
 {
	 QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	 return  pQyMc->ucbApp_ts;

 }
 //  2007/10/07
 BOOL  bMisCntOnline(  QY_MC  *  pQyMc,  MIS_CNT  *  pMisCnt  )
{
	if  (  !pMisCnt  )  return  FALSE;

	if  (  pMisCnt->cfg.dynCfg.cnt.usCntPort  )  {
		if  (  bChannelOk(  pQyMc,  pMisCnt,  getChannelByType(  pMisCnt,  CONST_channelType_talking  )  )  )  return  TRUE;
	}

	return  FALSE;
}


 int  myCompare_sortMessengerTreeByKey(  const  void  *  p1,  const  void  *  p2  )
{
	DISPLAYEDELEM_MESSENGER_TREE	*	pElem1  =  *(  DISPLAYEDELEM_MESSENGER_TREE  **  )p1;
	DISPLAYEDELEM_MESSENGER_TREE	*	pElem2  =  *(  DISPLAYEDELEM_MESSENGER_TREE  **  )p2;
	_int64								iDiff	=	0;				

	if  (  pElem1->pMisCnt  !=  pElem2->pMisCnt  )  return  (  MIS_CNT  *  )pElem1->pMisCnt  -  (  MIS_CNT  *  )pElem2->pMisCnt;
	//
	if  (  pElem1->uiType  !=  pElem2->uiType  )  return  pElem1->uiType  -  pElem2->uiType;
	//
	switch  (  pElem1->uiType  )  {
			case  CONST_displayedElemType_messengerTree:
				  iDiff  =  pElem1->idInfo.ui64Id  -  pElem2->idInfo.ui64Id;
				  break;
			default:
					break;
	}

	if  (  iDiff  <  0  )  return  -1;
	if  (  !iDiff  )  return  0;
	return  1;

}

int  addToDisplayedObjQ(  MC_CTX_DISPLAYEDWND  *  pCtx,  QMOBJQ_PARAM_MISCLIENT  *  pParam,  HWND  hWnd,  int  iObjId  )
{
	return  addToDisplayedObjQ(  pCtx,  pParam,  hWnd,  (  HTREEITEM  )iObjId  );		//  ÒòÎªÕâ2¸öÖµ´óÐ¡Ò»Ñù£¬¹ÊÔÝÊ±ÓÃÕâ¸öÀ´´úÌæ
}

 int  addToDisplayedObjQ(  MC_CTX_DISPLAYEDWND  *  pCtx,  QMOBJQ_PARAM_MISCLIENT  *  pParam,  HWND  hWnd,  HTREEITEM  hItem  )
{
	int									iErr				=		-1;
	MIS_MSG_DISPLAYEDELEM_QMC			msg;

	switch  (  pParam->iObjType  )  {
			case  CONST_objType_me:  {
				  DISPLAYEDELEM_MESSENGER_TREE			elem;
				  //
				  memset(  &elem,  0,  sizeof(  elem  )  );
				  elem.uiType  =  CONST_displayedElemType_meTree;
				  elem.pMisCnt  =  pParam->pMisCnt;
				  elem.hItem  =  hItem;

				  if  (  qPostMsg(  &elem,  sizeof(  elem  ),  &pCtx->displayedElemQ  )  )  goto  errLabel;
				  pCtx->ppDisplayedElems_sortedByKey[pCtx->displayedElemQ.uiQNodes  -  1]  =  (  void  *  )pCtx->displayedElemQ.pRear->qElemMemory.m_pBuf;

				  traceLogA(  "addToDisplayedObjQ: ÅÅÐòÇ°"  );
				  //  printDisplayedObjQ(  pCtx->ppDisplayedElems_sortedByKey,  pCtx->displayedElemQ.uiQNodes  );

				  qsort(  pCtx->ppDisplayedElems_sortedByKey,  pCtx->displayedElemQ.uiQNodes,  sizeof(  void  *  ),  myCompare_sortMessengerTreeByKey  );

				  traceLogA(  "addToDisplayedObjQ: ÅÅÐòºó"  );
				  //  printDisplayedObjQ(  pCtx->ppDisplayedElems_sortedByKey,  pCtx->displayedElemQ.uiQNodes  );

				  //  ÎÒ½Úµã²»ÓÃ·¢¸ødisplayQ, ÒòÎªÊµ¼ÊÉÏÕâÖ»ÊÇ¸ömisCntµÄÐèÄâÖ¸³Æ£¬Ò²²»¹Ì¶¨id

				  }				  
				  break;
			case  CONST_objType_messenger:  {
				  DISPLAYEDELEM_MESSENGER_TREE			elem;
				  //				  
				  memset(  &elem,  0,  sizeof(  elem  )  );
				  elem.uiType  =  CONST_displayedElemType_messengerTree;
				  elem.pMisCnt  =  pParam->pMisCnt;
				  elem.idInfo.ui64Id  =  (  (  QY_MESSENGER_INFO  *  )pParam->pClient  )->idInfo.ui64Id;
				  elem.hItem  =  hItem;

				  if  (  qPostMsg(  &elem,  sizeof(  elem  ),  &pCtx->displayedElemQ  )  )  goto  errLabel;
				  pCtx->ppDisplayedElems_sortedByKey[pCtx->displayedElemQ.uiQNodes  -  1]  =  (  void  *  )pCtx->displayedElemQ.pRear->qElemMemory.m_pBuf;

				  traceLogA(  "addToDisplayedObjQ: ÅÅÐòÇ°"  );
				  //  printDisplayedObjQ(  pCtx->ppDisplayedElems_sortedByKey,  pCtx->displayedElemQ.uiQNodes  );

				  qsort(  pCtx->ppDisplayedElems_sortedByKey,  pCtx->displayedElemQ.uiQNodes,  sizeof(  void  *  ),  myCompare_sortMessengerTreeByKey  );

				  traceLogA(  "addToDisplayedObjQ: ÅÅÐòºó"  );
				  //  printDisplayedObjQ(  pCtx->ppDisplayedElems_sortedByKey,  pCtx->displayedElemQ.uiQNodes  );

				  traceLogA(  "ÏÂÃæÒª·¢¸ødisplayÏß³Ì£¬¸æËßÓÐÕâÃ´Ò»¸öÏÔÊ¾ÔªËØ"  );
				  memset(  &msg,  0,  sizeof(  msg  )  );
				  //
				  msg.uiType  =  CONST_misMsgType_displayedElem_qmc;
				  msg.elemU.uiType  =  CONST_displayedElemType_messengerWnd;
				  msg.elemU.messengerWnd.pMisCnt  =  pParam->pMisCnt;
				  msg.elemU.messengerWnd.idInfo.ui64Id  =  (  (  QY_MESSENGER_INFO  *  )pParam->pClient  )->idInfo.ui64Id;
				  msg.elemU.messengerWnd.hWnd  =  hWnd;

				  if  (   qPostMsgAndTrigger(  &msg,  sizeof(  msg  ),  &(  (  MC_VAR_isCli  *  )pParam->pSci->pVar  )->displayQ  )  )  goto  errLabel;

				 }

				 break;
			default:
					break;
	}
					 
	iErr  =  0;
errLabel:
	return  iErr;
}


 int  getMessengerImages(  QY_MC  *  pQyMc,  unsigned  short  usRunningStatus,  int  *  pnImage,  int  *  pnSelectedImage  )
{
	int  nImage,  nSelectedImage;

    switch  (  usRunningStatus  )  {
		    case  CONST_usRunningStatus_online:
				  nImage  =  nSelectedImage  =  pQyMc->cfg.image.normal.nImage_pcNormal;
				  break;
			case  CONST_usRunningStatus_away:
				  nImage  =  nSelectedImage  =  pQyMc->cfg.image.normal.nImage_pcWait;
				  break;
			case  CONST_usRunningStatus_hide:
			case  CONST_usRunningStatus_offline:
			default:
				    nImage  =  nSelectedImage  =  pQyMc->cfg.image.offline.nImage_pcNormal;
					break;
	}				   

	if  (  pnImage  )  *pnImage  =  nImage;
	if  (  pnSelectedImage  )  *pnSelectedImage  =  nSelectedImage;

	return  0;
}
