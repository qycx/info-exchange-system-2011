// DlgPtzControl.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"myresource.h"
#include	"DlgPtzControl.h"

#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture.h"

#ifdef  __SUPPORT_HTMLEDIT__
	#include	"myHtmlEditCtrl.h"
#endif

#include	"tmpCeLib.h"

#include	"qyOpenShellCommon.h"
//  #include	"DlgTalk.h"
#include	"dlgTalkProc.h"
#include	"qyRtcCommProc.h"
#include	"qyCusResTemp.h"

#include	"qyComPortEx.h"

//  #include	"ptzSettings.h"

#include	"StageLens.h"

#include	"BitmapBtn.h"
//  #include	"CheckButton.h"

//  #include	"DlgProgress.h"
#include	"isCliHelpPublic.h"
#include	"FuncsforisCliHelp.h"

//
void dlg_YTCHECKBtn(  HWND  hDlg,  int  nResourceID  );
//  void  exitPtz(  );

__declspec(  dllexport  ) BOOL  isActive_comPort_ptz(  )
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  FALSE;

	if  (  !pProcInfo->ptz.pComPort  )  return  FALSE;

	CComPortEx  *  pPort  =  (  CComPortEx  *  )pProcInfo->ptz.pComPort;
	DWORD			dwTickCnt  =  GetTickCount(  );

	if  (  !pPort->bThreadAlive(  )  )  return  FALSE;
	if  (  dwTickCnt  -  pPort->m_var.dwTickCnt_lastWrite  >  30000  )  return  FALSE;

	return  TRUE;

}

 int  initPtz(  )
{
	int					iErr	=	-1;

	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

#ifdef  __DEBUG__
		traceLog(  _T(  "initPtz enters"  )  );
#endif

	if  (  pProcInfo->ptz.pComPort  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "comPort exists. initPtz leaves"  )  );
		#endif

		return  0;
	}

#if  0
	if  (  !pProcInfo->ptz.pStageLens  )  {
		pProcInfo->ptz.pStageLens  =  new  CStageLens;
		if  (  !pProcInfo->ptz.pStageLens  )  goto  errLabel;
	}
#endif

	pProcInfo->ptz.pComPort  =  new  CComPortEx;
	if  (  !pProcInfo->ptz.pComPort  )  goto  errLabel;

	CComPortEx	*	pPort  =  (  CComPortEx  *  )pProcInfo->ptz.pComPort;


	//
	memset(  &pProcInfo->ptz.m_var,  0,  sizeof(  pProcInfo->ptz.m_var  )  );
	{
		COM_PORT_cfg	cfg;
		if  (  getPtzSettings(  &cfg  )  )  goto  errLabel;
		if  (  memcmp(  &cfg,  &pProcInfo->ptz.m_var.cfg,  sizeof(  cfg  )  )  )  memcpy(  &pProcInfo->ptz.m_var.cfg,  &cfg,  sizeof(  pProcInfo->ptz.m_var.cfg  )  );
	}
	//  pProcInfo->ptz.m_var.m_nSpeed  =  23;


#if  0	//
	CStageLens  *  pStageLens  =  (  CStageLens  *  )pProcInfo->ptz.pStageLens;

	if  (  pProcInfo->ptz.m_var.cfg.m_pelcoType ==  0  )  
	{
		pStageLens->SetProtocol(  CStageLens::PELCO_D  );
	}
	else  if  (  pProcInfo->ptz.m_var.cfg.m_pelcoType  ==  1  )  {
			  pStageLens->SetProtocol(  CStageLens::PELCO_P  );
			  }
	else  {
		  goto  errLabel;
	}
	//
	pStageLens->SetSpeed(  pProcInfo->ptz.m_var.m_nSpeed  );
#endif


	//
	if  (  !pPort->bInitPort(  pQyMc->gui.hMainWnd,  pProcInfo->ptz.m_var.cfg.portNo,  pProcInfo->ptz.m_var.cfg.m_rate,  pProcInfo->ptz.m_var.cfg.m_parity,  pProcInfo->ptz.m_var.cfg.m_dataBit,  pProcInfo->ptz.m_var.cfg.m_stopBit,  EV_RXCHAR  |  EV_CTS,  512,  CONST_iComPortType_ptz,  0  )  )  goto  errLabel;

	if  (  !pPort->bStartMonitoring(  )  )  {
		qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "port.bStartMonitoring failed"  )  );
		goto  errLabel;
	}
	//  m_var.share_gps.var.dwTickCnt_start  =  GetTickCount(  );



	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		exitPtz(  );
	}

#ifdef  __DEBUG__
		traceLog(  _T(  "initPtz leaves"  )  );
#endif
		//  qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initPtz %s"  ),  iErr  ?  _T(  "failed"  )  :  _T(  "OK"  )  );

	return  iErr;
}

__declspec(  dllexport  ) void  exitPtz(  )
{
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return;

#ifdef  __DEBUG__
		traceLog(  _T(  "exitPtz enters"  )  );
#endif

#if  0
	if  (  pProcInfo->ptz.pStageLens  )  {
		CStageLens  *  pStageLens  =  (  CStageLens  *  )pProcInfo->ptz.pStageLens;
		delete  pStageLens;
		pProcInfo->ptz.pStageLens  =  NULL;
	}
#endif

	if  (  pProcInfo->ptz.pComPort  )  {
		CComPortEx  *  pPort  =  (  CComPortEx  *  )pProcInfo->ptz.pComPort;

		delete  pPort;
		pProcInfo->ptz.pComPort  =  NULL;
	}
	
#ifdef  __DEBUG__
		traceLog(  _T(  "exitPtz leaves"  )  );
#endif

	return;
}

 int myPtz_write(  void  *  pDlgPtzControlParam,  char  *  buf,  unsigned  int  iLen  )
{
	int		iErr	=	-1;

	if  (  !pDlgPtzControlParam  )  return  -1;
	CDlgPtzControl  *  pDlgPtzControl  =  (  CDlgPtzControl  *  )pDlgPtzControlParam;

	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );

	if  (  !pDlgPtzControl->m_var.bRemote  )  {

		if  (  !pProcInfo->ptz.pComPort  )  goto  errLabel;

		CComPortEx  *  pPort  =  (  CComPortEx  *  )pProcInfo->ptz.pComPort;

		if  (  !pPort->bThreadAlive(  )  )  goto  errLabel;

		if  (  pPort->WriteToPort(  (  BYTE  *  )buf,  iLen  )  )  goto  errLabel;

		}
	else  {
		  //  2012/08/06
		  PTZ_control_cmd	req;
		  MACRO_prepareForTran(  );

		  MIS_CNT	*	pMisCnt  =  pFuncs->pf_getMisCntByName(  0,  0,  _T(  ""  )  );
		  if  (  !pMisCnt  )  goto  errLabel;

		unsigned  int			uiChannelType	=	CONST_channelType_media;

#ifdef  __DEBUG__
		uiChannelType  =  0;
		traceLog(  _T(  "Note: send ptz req through talking channel, just for debug"  )  );
#endif

		//
		memset(  &req,  0,  sizeof(  req  )  );
		req.uiType  =  CONST_imCommType_ptzControlCmd;

		if  (  iLen  >  sizeof(  req.cmdBuf  )  )  goto  errLabel;
		memcpy(  req.cmdBuf,  buf,  iLen  );
		req.uiLen  =  iLen;


		//
		if  (  pFuncs->pf_postMsg2Mgr_mc(  pMisCnt,  NULL,  CONST_misMsgType_outputTask,  0,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  (  char  *  )&req,  sizeof(  req  ),  0,  &pDlgPtzControl->m_var.idInfo_remote,  uiChannelType,  NULL,  FALSE  )  )  traceLogA(  "postMsg2Mgr_mc failed"  );
	}

	iErr  =  0;

errLabel:

	return  iErr;
}


 //  2012/08/08
__declspec(  dllexport  )  int doRemotePtzCmd(  char  *  buf,  unsigned  int  iLen  )
{
	int					iErr	=	-1;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	if  (  initPtz(  )  )  goto  errLabel;

	CComPortEx  *  pPort  =  (  CComPortEx  *  )pProcInfo->ptz.pComPort;
	if  (  !pPort  )  goto  errLabel;

	if  (  !pPort->bThreadAlive(  )  )  goto  errLabel;

	if  (  pPort->WriteToPort(  (  BYTE  *  )buf,  iLen  )  )  goto  errLabel;

	iErr  =  0;
errLabel:

	if  (  iErr  )  {
		qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "doRemotePtzCmd failed"  )  );

		exitPtz(  );
	}
	return  iErr;
}


__declspec(  dllexport  ) int  viewRemotePtzControl(  HWND  hParent,  HWND  hCurTalk,  void  *  pCurVarParam,  void  *  pMgrVarParam  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int					iErr	=	-1;

	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	FUNCS_for_isCliHelp		*	pFuncs	=  QY_GET_FUNCS_for_isCliHelp(  );

	//  MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	//  if  (  !pProcInfo  )  return  -1;

	CDlgPtzControl			*		pDlg					=	NULL;
	RECT							rect;

	HWND					*		phWnd_lv				=	NULL;

	DLG_TALK_var  *  pCurVar  =  (  DLG_TALK_var  *  )pCurVarParam;
	DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var  *  )pMgrVarParam;

	HWND	hMgr	=	NULL;
	//  DLG_TALK_var  *  pCurVar  =  getDlgTalkVar(  hCurTalk  );
	if  (  !pCurVar  )  goto  errLabel;
	if  (  isTalkerShadowMgr(  pCurVar->addr  )  )  hMgr  =  hCurTalk;
	else  {
		  TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pCurVar->pShadowInfo;
		  if  (  !pShadow  )  goto  errLabel;
		  hMgr  =  pShadow->hMgr;
	}
	//  DLG_TALK_var  *  pMgrVar  =  getDlgTalkVar(  hMgr  );
	if  (  !pMgrVar  )  goto  errLabel;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;
		
	//
	phWnd_lv  =  &pCurVar->ptzControl.hWnd_ptzControl;

	//
	if  (  phWnd_lv  )  {
		if  (  IsWindow(  *phWnd_lv  )  )  {
			MACRO_SetForegroundWindow(  *phWnd_lv  );
			iErr  =  0;  goto  errLabel;
		}

		*phWnd_lv  =  NULL;
	}

	//
	if  (  pShadowMgr->ptz.hWnd_ptzControl  )  {
		if  (  IsWindow(  pShadowMgr->ptz.hWnd_ptzControl  )  )  {
			SendMessage(  pShadowMgr->ptz.hWnd_ptzControl,  WM_CLOSE,  0,  0  );
		}
		if  (  IsWindow(  pShadowMgr->ptz.hWnd_ptzControl  )  )  goto  errLabel;
	}
	memset(  &pMgrVar->ptzControl,  0,  sizeof(  pMgrVar->ptzControl  )  );

	//
	{	
		//  2012/08/06
		PTZ_control_req	req;
		MACRO_prepareForTran(  );

		unsigned  int			uiChannelType	=	CONST_channelType_media;

		if  (  !pFuncs->pf_canRemotePtzControl(  )  )  {
			qyShowHint(  _T(  "No video"  )  );
			goto  errLabel;
		}

#ifdef  __DEBUG__
		uiChannelType  =  0;
		traceLog(  _T(  "Note: send ptz req through talking channel, just for debug"  )  );
#endif

		//
		memset(  &req,  0,  sizeof(  req  )  );
		req.uiType  =  CONST_imCommType_ptzControlReq;

		
		//  2010/08/14
		pFuncs->pf_startProgress(  uiTranNo  );

		//
		if  (  pFuncs->pf_postMsg2Mgr_mc(  pMgrVar->pMisCnt,  NULL,  CONST_misMsgType_outputTask,  0,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  (  char  *  )&req,  sizeof(  req  ),  0,  &pMgrVar->addr.idInfo,  uiChannelType,  NULL,  FALSE  )  )  traceLogA(  "postMsg2Mgr_mc failed"  );


#if  0
		{	
			CDlgProgress	dlg(  CWnd::FromHandle(  hParent  )  );
			dlg.bSetDlgInfo(  _T(  "Please waiting"  ),  NULL,  30,  -1,  uiTranNo  ); 

			//  traceLogA(  "if task is not ready, cancel the task by clear shmCmd, and the subprocess will quit when it read the shmCmd."  );
			if  (  dlg.DoModal(  )  !=  IDOK  )  {
				goto  errLabel;
			}
		}
#endif
		if  (  showDlgProgress(  hParent,  _T(  "Please waiting"  ),  NULL,  30,  -1,  uiTranNo  )  !=  IDOK  )  {
			goto  errLabel;
		}

	}


	
	//
	pDlg  =  new  CDlgPtzControl(  CWnd::FromHandle(  hParent  )  );
	if  (  !pDlg  )  goto  errLabel;

	//
	pDlg->m_var.bRemote   =  TRUE;
	pDlg->m_var.hDlgTalk  =  hCurTalk;
	pDlg->m_var.idInfo_remote.ui64Id  =  pMgrVar->addr.idInfo.ui64Id;
	//
	pDlg->m_var.m_nAddr  =  pMgrVar->ptzControl.cfg.nAddr;
	pDlg->m_var.m_pelcoType  =  pMgrVar->ptzControl.cfg.nPelcoType;
	lstrcpyn(  pDlg->m_var.tHint,  pMgrVar->ptzControl.tHint,  mycountof(  pDlg->m_var.tHint  )  );
	
	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;
	pDlg->ShowWindow(  SW_SHOW  );


	//
	if  (  phWnd_lv  )  *phWnd_lv  =  pDlg->m_hWnd;
	pShadowMgr->ptz.hWnd_ptzControl  =  pDlg->m_hWnd;

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}



	return  iErr;
}


__declspec(  dllexport  ) int  viewLocalPtzControl(  HWND  hParent  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int					iErr	=	-1;

	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;

	CDlgPtzControl			*		pDlg					=	NULL;
	RECT							rect;

	HWND					*		phWnd_lv				=	NULL;

	phWnd_lv  =  &pProcInfo->ptz.hWnd_localPtzControl;

	if  (  phWnd_lv  )  {
		if  (  IsWindow(  *phWnd_lv  )  )  {
			MACRO_SetForegroundWindow(  *phWnd_lv  );
			iErr  =  0;  goto  errLabel;
		}

		*phWnd_lv  =  NULL;
	}

		//
	pDlg  =  new  CDlgPtzControl(  CWnd::FromHandle(  hParent  )  );
	if  (  !pDlg  )  goto  errLabel;

	
	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;
	pDlg->ShowWindow(  SW_SHOW  );


	//
	if  (  phWnd_lv  )  *phWnd_lv  =  pDlg->m_hWnd;

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		if  (  pDlg  )  delete  pDlg;
	}



	return  iErr;
}


// CDlgPtzControl dialog

IMPLEMENT_DYNAMIC(CDlgPtzControl, CDialog)

CDlgPtzControl::CDlgPtzControl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPtzControl::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
	m_var.m_pParent = pParent;
	m_var.m_nID = CDlgPtzControl::IDD;
}

CDlgPtzControl::~CDlgPtzControl()
{
}


 BOOL CDlgPtzControl::Create(const RECT& rect)
{

	// TODO: Add your specialized code here and/or call the base class
	BOOL						bRet		=	FALSE;
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli			*	pProc		=	NULL;

	/*
	if  (  !m_var.bInfoSet  )  {
		traceLogA(  "CDlgTalk::Create(  ): 在创建对话框之前应先设置初始数据"  );
		return  FALSE;
	}
	*/

	if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_is  )  return  FALSE;
	

	//
	if  (  !CDialog::Create(  this->m_var.m_nID, m_var.m_pParent  )  )  goto  errLabel;

	//
	m_var.bCreated  =  TRUE;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}


 BOOL  CDlgPtzControl::bQuitDlg(  )		
{		
	traceLogA(  "CDlgListView_db(  )::bQuitDlg enters"  );


	//  2009/05/01
	DestroyWindow();				  
		
//  errLabel:

	traceLogA(  "CDlgListView_db(  )::bQuitDlg leaves"  );

	return  TRUE;
}

 void  CDlgPtzControl::InitBtn(  )
 {
	BOOL  bRet;
	QY_MC		*  pQyMc		=  QY_GET_GBUF(  );

	bRet  =  m_btnUp.SubclassDlgItem(  IDC_BUTTON_UP,  this  );
	//  bRet  =  m_btnUp.LoadBitmaps(  IDB_BITMAP_up,  IDB_BITMAP_up_sel  );
	//  m_btnUp.SizeToContent(  );
	m_btnUp.setToolTipText(  _T(  "Up"  )  );

	m_btnDown.SubclassDlgItem(  IDC_BUTTON_DOWN,  this  );
	//  m_btnDown.LoadBitmaps(  IDB_BITMAP_down,  IDB_BITMAP_down_sel  );
	//  m_btnDown.SizeToContent(  );
	m_btnDown.setToolTipText(  _T(  "Down"  )  );

	m_btnLeft.SubclassDlgItem(  IDC_BUTTON_LEFT,  this  );
	//  m_btnLeft.LoadBitmaps(  IDB_BITMAP_left,  IDB_BITMAP_left_sel  );
	//  m_btnLeft.SizeToContent(  );
	m_btnLeft.setToolTipText(  _T(  "Left" )  );

	m_btnRight.SubclassDlgItem(  IDC_BUTTON_RIGHT,  this  );
	//  m_btnRight.LoadBitmaps(  IDB_BITMAP_right,  IDB_BITMAP_right_sel  );
	//  m_btnRight.SizeToContent(  );
	m_btnRight.setToolTipText(  _T(  "right" )  );

	m_btnTopLeft.SubclassDlgItem(  IDC_BUTTON_TOP_LEFT,  this  );
	//  m_btnTopLeft.LoadBitmaps(  IDB_BITMAP_topLeft,  IDB_BITMAP_topLeft_sel  );
	//  m_btnTopLeft.SizeToContent(  );
	m_btnTopLeft.setToolTipText(  _T(  "topLeft" )  );

	m_btnTopRight.SubclassDlgItem(  IDC_BUTTON_TOP_RIGHT,  this  );
	//  m_btnTopRight.LoadBitmaps(  IDB_BITMAP_topRight,  IDB_BITMAP_topRight_sel  );
	//  m_btnTopRight.SizeToContent(  );
	m_btnTopRight.setToolTipText(  _T(  "topRight" )  );

	m_btnBottomLeft.SubclassDlgItem(  IDC_BUTTON_BOTTOM_LEFT,  this  );
	//  m_btnBottomLeft.LoadBitmaps(  IDB_BITMAP_bottomLeft,  IDB_BITMAP_bottomLeft_sel  );
	//  m_btnBottomLeft.SizeToContent(  );
	m_btnBottomLeft.setToolTipText(  _T(  "bottomLeft" )  );

	m_btnBottomRight.SubclassDlgItem(  IDC_BUTTON_BOTTOM_RIGHT,  this  );
	//  m_btnBottomRight.LoadBitmaps(  IDB_BITMAP_bottomRight,  IDB_BITMAP_bottomRight_sel  );
	//  m_btnBottomRight.SizeToContent(  );
	m_btnBottomRight.setToolTipText(  _T(  "bottomRight" )  );

	//  2013/04/07
	m_btnNoop.SubclassDlgItem(  IDC_BUTTON_noop,  this  );
	m_btnNoop.setToolTipText(  _T(  "no op"  )  );

	//
	m_btnIrisIn.SubclassDlgItem(  IDC_BUTTON_IRIS_IN,  this  );
	//  m_btnIrisIn.LoadBitmaps(  IDB_BITMAP_plus,  IDB_BITMAP_plus_sel  );
	//  m_btnIrisIn.SizeToContent(  );
	m_btnIrisIn.setToolTipText(  _T(  "iris (+) plus"  )  );

	m_btnIrisOut.SubclassDlgItem(  IDC_BUTTON_IRIS_OUT,  this  );
	//  m_btnIrisOut.LoadBitmaps(  IDB_BITMAP_minus,  IDB_BITMAP_minus_sel  );
	//  m_btnIrisOut.SizeToContent(  );
	m_btnIrisOut.setToolTipText(  _T(  "iris (-) minus"  )  );

	m_btnFocusIn.SubclassDlgItem(  IDC_BUTTON_FOCUS_IN,  this  );
	//  m_btnFocusIn.LoadBitmaps(  IDB_BITMAP_plus,  IDB_BITMAP_plus_sel  );
	//  m_btnFocusIn.SizeToContent(  );
	m_btnFocusIn.setToolTipText(  _T(  "focus (+)  plus "  )  );

	m_btnFocusOut.SubclassDlgItem(  IDC_BUTTON_FOCUS_OUT,  this  );
	//  m_btnFocusOut.LoadBitmaps(  IDB_BITMAP_minus,  IDB_BITMAP_minus_sel  );
	//  m_btnFocusOut.SizeToContent(  );
	m_btnFocusOut.setToolTipText(  _T(  "focus (-)  minus "  )  );

	m_btnZoomIn.SubclassDlgItem(  IDC_BUTTON_ZOOM_IN,  this  );
	//  m_btnZoomIn.LoadBitmaps(  IDB_BITMAP_plus,  IDB_BITMAP_plus_sel  );
	//  m_btnZoomIn.SizeToContent(  );
	m_btnZoomIn.setToolTipText(  _T(  "zoom (+) plus"  )  );

	m_btnZoomOut.SubclassDlgItem(  IDC_BUTTON_ZOOM_OUT,  this  );
	m_btnZoomOut.setToolTipText(  _T(  "zoom (-) minus"  )  );

#if  0
	m_cbtnAutoScan.SubclassDlgItem(  IDC_BUTTON_AUTO_SCAN,  this  );
	m_cbtnAutoScan.setBmpID(  IDB_BITMAP_autoScan,  IDB_BITMAP_autoScan_sel  );
	m_cbtnAutoScan.setToolTipText(  _T(  "autoscan "  )  );

	m_cbtnRainBrush.SubclassDlgItem(  IDC_BUTTON_RAIN_BRUSH,  this  );
	m_cbtnRainBrush.setBmpID(  IDB_BITMAP_rainBrush,  IDB_BITMAP_rainBrush_sel  );
	m_cbtnRainBrush.setToolTipText(  _T(  "rainBrush"  ) );

	m_cbtnSearchLight.SubclassDlgItem(  IDC_BUTTON_SEARCH_LIGHT,  this  );
	m_cbtnSearchLight.setBmpID(  IDB_BITMAP_searchLight,  IDB_BITMAP_searchLight_sel  );
	m_cbtnSearchLight.setToolTipText(  _T(  "searchLight"  )  );
#endif

	m_buStatus_autoScan.SubclassDlgItem(  IDC_BUTTON_AUTO_SCAN,  this  );
	m_buStatus_autoScan.m_text  =  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_autoScan  );

	m_buStatus_rainBrush.SubclassDlgItem(  IDC_BUTTON_RAIN_BRUSH,  this  );
	m_buStatus_rainBrush.m_text  =  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rainBrush  );

	m_buStatus_searchLight.SubclassDlgItem(  IDC_BUTTON_SEARCH_LIGHT,  this  );
	m_buStatus_searchLight.m_text  =  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_searchLight  );

 }


 int  CDlgPtzControl::refreshStatus(  )
{
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	TCHAR				tBuf[128]	=	_T(  ""  );
	TCHAR				comBuf[128]	=	_T(  ""  );
	TCHAR				memoBuf[128]	=	_T(  ""  );
	QY_MC	*	pQyMc		=	QY_GET_GBUF(  );
	CQyString			rootKeyStr;
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  );
	rootKeyStr  =  CQyString(  tBuf  );

	if  (  !m_var.bRemote  )  {
		if  (  !pProcInfo->ptz.pComPort  )  _sntprintf(  comBuf,  mycountof(  comBuf  ),  _T(  "Com can't open"  )  );
		else  {
			  CComPortEx  *  pPort  =  (  CComPortEx  *  )pProcInfo->ptz.pComPort;
			  _sntprintf(  comBuf,  mycountof(  comBuf  ),  _T(  "COM%d open"  ),  pPort->m_nPortNo  );
		}

		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s. %s"  ),  comBuf,  pProcInfo->ptz.m_var.cfg.tHint  );
	}
	else  {
		  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  m_var.tHint  );
	}

	SetDlgItemText(  IDC_STATIC_hint,  tBuf  );

errLabel:
	return  0;
}

 int  CDlgPtzControl::sizeAllControls(  )
 {
	 int		iErr	=	-1;
	 RECT		rc, rcBtn;
	 HWND		hDlg	=	this->m_hWnd;
	 int		iw,ih;
	 float		fx,fy;
	 HWND		hBtn;


/*

	 ::GetClientRect(  hDlg,  &rc  );
	 iw  =  rc.right  -  rc.left;
	 ih  =  rc.bottom  -  rc.top;

	 if  ( !m_var.iw_org  ||  !m_var.ih_org  )  goto  errLabel;
	 fx  =  1.  *  iw  /  m_var.iw_org;
	 fy  =  1.  *  ih  /  m_var.ih_org;

	 hBtn  =  ::GetDlgItem(  hDlg,  IDC_BUTTON_UP );
	 ::GetWindowRect(  hBtn,  &rcBtn  );
	 ::MoveWindow(  hDlg,  rcBtn.right  -  rcBtn.left,  rcBtn.bottom  -  rcBtn.top,  (  rcBtn.right  -  rcBtn.left  )  *  fx,  (  rcBtn.bottom  -  rcBtn.top  )  *  fy,  TRUE  );
	 */

	iErr  =  0;
errLabel:
	return  iErr;
 }

void CDlgPtzControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_speed, m_slider_speed);
	DDX_Control(pDX, IDC_EDIT_PRE, m_edit_nPrePoint);
}

BOOL CDlgPtzControl::OnCommand(  WPARAM  wParam,  LPARAM  lParam  )
{
	UINT  nID  =  LOWORD(  wParam  );
	HWND  hWndCtrl  =  (  HWND  )lParam;
	int  nCode  =  HIWORD(  wParam  );

	if  (  (  nID  == IDC_BUTTON_AUTO_SCAN  )  ||  (  nID  ==  IDC_BUTTON_RAIN_BRUSH  )  ||  (  nID  ==  IDC_BUTTON_SEARCH_LIGHT  )  )
	{
		if  (  nCode  ==  BN_CLICKED  )
			OnChangeStatus(  nID  );
		//
		switch  (  nID  )  {
				case  IDC_BUTTON_AUTO_SCAN:
					  m_var.m_bnDown_autoScan  =  this->m_buStatus_autoScan.m_nFlag  ?  TRUE  :  FALSE;
					  break;
				case  IDC_BUTTON_RAIN_BRUSH:
					  m_var.m_bnDown_rainBrush  =  this->m_buStatus_rainBrush.m_nFlag  ?  TRUE  :  FALSE;
					  break;
				case  IDC_BUTTON_SEARCH_LIGHT:
					  m_var.m_bnDown_searchLight  =  this->m_buStatus_searchLight.m_nFlag  ?  TRUE  :  FALSE;
					  break;
				default:
						break;
		}
	
		
		OutputDebugString(  _T(  "OnCommand\n"  )  );


		//
		dlg_YTCHECKBtn(  m_hWnd,  nID  );
	}

	return  CDialog::OnCommand(  wParam,  lParam  );
}


BEGIN_MESSAGE_MAP(CDlgPtzControl, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_ptzSettings, &CDlgPtzControl::OnBnClickedButtonptzsettings)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_speed, &CDlgPtzControl::OnNMReleasedcaptureSliderspeed)
	ON_EN_CHANGE(IDC_EDIT_PRE, &CDlgPtzControl::OnEnChangeEditPre)
	ON_BN_CLICKED(IDC_BUTTON_PRE_GO, &CDlgPtzControl::OnBnClickedButtonPreGo)
	ON_BN_CLICKED(IDC_BUTTON_PRE_SET, &CDlgPtzControl::OnBnClickedButtonPreSet)
	ON_BN_CLICKED(IDC_BUTTON_PRE_CLEAR, &CDlgPtzControl::OnBnClickedButtonPreClear)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgPtzControl message handlers

BOOL CDlgPtzControl::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	int			iErr	=	-1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	RECT		rc;
	HWND		hDlg	=	this->m_hWnd;

	::SetWindowPos(  m_hWnd,  HWND_TOPMOST,  0,  0,  0,  0,  SWP_NOMOVE  |  SWP_NOSIZE  );

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	DLG_guiData_ptzControl		*  p	= &m_var.guiData;

	::GetClientRect(  hDlg,  &rc  );
	p->iw_org  =  rc.right  -  rc.left;
	p->ih_org  =  rc.bottom  -  rc.top;

	if  (  !p->iw_org  ||  !p->ih_org  )  goto  errLabel;

	//  header
	p->iIDC_BUTTON_ptzSettings  =  IDC_BUTTON_ptzSettings;
	p->iIDC_STATIC_hint  =  IDC_STATIC_hint;
	p->iIDC_STATIC_speed  =  IDC_STATIC_speed;
	p->iIDC_SLIDER_speed  =  IDC_SLIDER_speed;
	//  body
	p->iIDC_BUTTON_TOP_LEFT  =  IDC_BUTTON_TOP_LEFT;
	p->iIDC_BUTTON_UP  =  IDC_BUTTON_UP;
	p->iIDC_BUTTON_TOP_RIGHT  =  IDC_BUTTON_TOP_RIGHT;
				 
	p->iIDC_BUTTON_LEFT  =  IDC_BUTTON_LEFT;
	p->iIDC_BUTTON_AUTO_SCAN  =  IDC_BUTTON_AUTO_SCAN;
	p->iIDC_BUTTON_RIGHT  =  IDC_BUTTON_RIGHT;
					 
	p->iIDC_BUTTON_BOTTOM_LEFT  =  IDC_BUTTON_BOTTOM_LEFT;
	p->iIDC_BUTTON_DOWN  =  IDC_BUTTON_DOWN;
	p->iIDC_BUTTON_BOTTOM_RIGHT  =  IDC_BUTTON_BOTTOM_RIGHT;

	p->iIDC_BUTTON_noop  =  IDC_BUTTON_noop;					//  2013/04/07
	
	p->iIDC_BUTTON_FOCUS_OUT  =  IDC_BUTTON_FOCUS_OUT;
	p->iIDC_BUTTON_IRIS_OUT  =  IDC_BUTTON_IRIS_OUT;
	p->iIDC_BUTTON_ZOOM_OUT  =  IDC_BUTTON_ZOOM_OUT;
	
	p->iIDC_STATIC_focus  =  IDC_STATIC_focus;
	p->iIDC_STATIC_iris  =  IDC_STATIC_iris;
	p->iIDC_STATIC_zoom  =  IDC_STATIC_zoom;
	
	p->iIDC_BUTTON_FOCUS_IN  =  IDC_BUTTON_FOCUS_IN;
	p->iIDC_BUTTON_IRIS_IN  =  IDC_BUTTON_IRIS_IN;
	p->iIDC_BUTTON_ZOOM_IN  =  IDC_BUTTON_ZOOM_IN;

	p->iIDCANCEL  =  IDCANCEL;
	//  tailer
	p->iIDC_BUTTON_RAIN_BRUSH  =  IDC_BUTTON_RAIN_BRUSH;
	p->iIDC_BUTTON_SEARCH_LIGHT  =  IDC_BUTTON_SEARCH_LIGHT;
	p->iIDC_STATIC_preset  =  IDC_STATIC_preset;
	p->iIDC_EDIT_PRE  =  IDC_EDIT_PRE;
	p->iIDC_BUTTON_PRE_GO  =  IDC_BUTTON_PRE_GO;
	p->iIDC_BUTTON_PRE_SET  =  IDC_BUTTON_PRE_SET;
	p->iIDC_BUTTON_PRE_CLEAR  =  IDC_BUTTON_PRE_CLEAR;


	//  header
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_ptzSettings  ),  &p->rcIDC_BUTTON_ptzSettings  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_ptzSettings,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_STATIC_hint  ),  &p->rcIDC_STATIC_hint  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_hint,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_STATIC_speed  ),  &p->rcIDC_STATIC_speed  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_speed,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_SLIDER_speed  ),  &p->rcIDC_SLIDER_speed  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_SLIDER_speed,  2  );

	//  body
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_TOP_LEFT  ),  &p->rcIDC_BUTTON_TOP_LEFT  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_TOP_LEFT,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_UP  ),  &p->rcIDC_BUTTON_UP  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_UP,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_TOP_RIGHT  ),  &p->rcIDC_BUTTON_TOP_RIGHT  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_TOP_RIGHT,  2  );

	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_LEFT  ),  &p->rcIDC_BUTTON_LEFT  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_LEFT,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_AUTO_SCAN  ),  &p->rcIDC_BUTTON_AUTO_SCAN  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_AUTO_SCAN,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_RIGHT  ),  &p->rcIDC_BUTTON_RIGHT  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_RIGHT,  2  );

	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_BOTTOM_LEFT  ),  &p->rcIDC_BUTTON_BOTTOM_LEFT  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_BOTTOM_LEFT,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_DOWN  ),  &p->rcIDC_BUTTON_DOWN  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_DOWN,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_BOTTOM_RIGHT  ),  &p->rcIDC_BUTTON_BOTTOM_RIGHT  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_BOTTOM_RIGHT,  2  );

	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_noop  ),  &p->rcIDC_BUTTON_noop  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_noop,  2  );

	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_FOCUS_OUT  ),  &p->rcIDC_BUTTON_FOCUS_OUT  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_FOCUS_OUT,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_IRIS_OUT  ),  &p->rcIDC_BUTTON_IRIS_OUT  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_IRIS_OUT,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_ZOOM_OUT  ),  &p->rcIDC_BUTTON_ZOOM_OUT  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_ZOOM_OUT,  2  );

	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_STATIC_focus  ),  &p->rcIDC_STATIC_focus  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_focus,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_STATIC_iris  ),  &p->rcIDC_STATIC_iris  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_iris,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_STATIC_zoom  ),  &p->rcIDC_STATIC_zoom  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_zoom,  2  );

	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_FOCUS_IN  ),  &p->rcIDC_BUTTON_FOCUS_IN  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_FOCUS_IN,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_IRIS_IN  ),  &p->rcIDC_BUTTON_IRIS_IN  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_IRIS_IN,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_ZOOM_IN  ),  &p->rcIDC_BUTTON_ZOOM_IN  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_ZOOM_IN,  2  );

	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDCANCEL  ),  &p->rcIDCANCEL  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDCANCEL,  2  );
	//  tailer
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_RAIN_BRUSH  ),  &p->rcIDC_BUTTON_RAIN_BRUSH  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_RAIN_BRUSH,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_SEARCH_LIGHT  ),  &p->rcIDC_BUTTON_SEARCH_LIGHT  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_SEARCH_LIGHT,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_STATIC_preset  ),  &p->rcIDC_STATIC_preset  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_STATIC_preset,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_EDIT_PRE  ),  &p->rcIDC_EDIT_PRE  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_EDIT_PRE,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_PRE_GO  ),  &p->rcIDC_BUTTON_PRE_GO  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_PRE_GO,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_PRE_SET  ),  &p->rcIDC_BUTTON_PRE_SET  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_PRE_SET,  2  );
	::GetWindowRect(  ::GetDlgItem(  hDlg,  p->iIDC_BUTTON_PRE_CLEAR  ),  &p->rcIDC_BUTTON_PRE_CLEAR  );
	::MapWindowPoints(  NULL,  hDlg,  (  LPPOINT  )&p->rcIDC_BUTTON_PRE_CLEAR,  2  );

	p->bInited  =  TRUE;
	
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );

	if  (  !m_var.bRemote  )  {
		if  (  !pProcInfo->ptz.pComPort  )  {
			initPtz(  );
		}
		m_var.m_nAddr  =  pProcInfo->ptz.m_var.cfg.m_nAddr;
		m_var.m_pelcoType  =  pProcInfo->ptz.m_var.cfg.m_pelcoType;
		//  m_var.m_nSpeed  =  pProcInfo->ptz.m_var.m_nSpeed;
		}
	else  {
		  //  viewRemotePtz里已经赋值了
		  makeWndNoBorder(  m_hWnd,  FALSE,  NULL,  NULL  );
	}

	//
	m_var.pStageLens  =  new  CStageLens;
	if  (  !m_var.pStageLens  )  goto  errLabel;

	CStageLens  *  pStageLens  =  (  CStageLens  *  )m_var.pStageLens;
	pStageLens->pDlgPtzControl  =  this;

	if  (  m_var.m_pelcoType ==  CONST_ptzProto_PELCO_D  )  {
		pStageLens->SetProtocol(  CStageLens::PELCO_D  );
		}
	else  if  (  m_var.m_pelcoType  ==  CONST_ptzProto_PELCO_P  )  {
			  pStageLens->SetProtocol(  CStageLens::PELCO_P  );
			  }
	else  {
		  qyShowHint(  _T(  "ptz proto type error"  )  );
		  goto  errLabel;
	}
	//
	m_var.m_nSpeed  =  23;
	pStageLens->SetSpeed(  m_var.m_nSpeed  );

	//
	InitBtn(  );

	//
	refreshStatus(  );

	//
	int  iPos  =  m_var.m_nSpeed  *  100  /  0x3f;
	m_slider_speed.SetPos(  iPos  );

	//
	if  (  m_var.bRemote  )  {
		::ShowWindow(  ::GetDlgItem(  m_hWnd,  IDC_BUTTON_ptzSettings  ),  SW_HIDE  );
	}

	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		PostMessage(  WM_CLOSE,  0,  0  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPtzControl::OnClose()
{
	// TODO: Add your message handler code here and/or call default

	//  CDialog::OnClose();
	bQuitDlg(  );
}

void CDlgPtzControl::PostNcDestroy()
{
	// TODO: Add your specialized code here and/or call the base class

	CDialog::PostNcDestroy();

	if  (  m_var.pStageLens  )  {
		CStageLens  *  pStageLens  =  (  CStageLens  *  )m_var.pStageLens;
		delete  pStageLens;
		m_var.pStageLens  =  NULL;
	}

	//  2012/09/05
	if  (  m_var.bRemote  &&  m_var.hDlgTalk  )  {
		::PostMessage(  m_var.hDlgTalk,  WM_SIZE,  0,  0  );
	}

	//
	delete  this;
}

void CDlgPtzControl::OnBnClickedButtonptzsettings()
{
	// TODO: Add your control notification handler code here
	if  (  m_var.bRemote  )  return;

	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );

#if  0
	CPtzSettings  dlg;

	if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif

	if  (  showDlgPtzSettings(  m_hWnd  )  ==  IDOK  )	
	{
		exitPtz(  );
		initPtz(  );

		//
		m_var.m_nAddr  =  pProcInfo->ptz.m_var.cfg.m_nAddr;
		m_var.m_pelcoType  =  pProcInfo->ptz.m_var.cfg.m_pelcoType;
		//  m_var.m_nSpeed  =  pProcInfo->ptz.m_var.m_nSpeed;

		//
		CStageLens  *  pStageLens  =  (  CStageLens  *  )m_var.pStageLens;

		if  (  m_var.m_pelcoType ==  CONST_ptzProto_PELCO_D  )  {
			pStageLens->SetProtocol(  CStageLens::PELCO_D  );
			}	
		else  if  (  m_var.m_pelcoType  ==  CONST_ptzProto_PELCO_P  )  {
			  pStageLens->SetProtocol(  CStageLens::PELCO_P  );
			  }
		else  {
			  qyShowHint(  _T(  "ptz proto type error"  )  );
			  #ifdef  __DEBUG__
					  traceLog(  _T(  "Err"  )  );
			  #endif
		}

	}

	//
	refreshStatus(  );

}

void CDlgPtzControl::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class

	//  CDialog::OnCancel();

	bQuitDlg(  );
}

void dlg_YTBtnDown(  HWND  hDlg,  int  nResourceID  )
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
#if  0
	if  (  !pProcInfo->ptz.pStageLens  )  return;

	CStageLens  &  m_CStageLens  =  *(  CStageLens  *  )pProcInfo->ptz.pStageLens;
#endif
	CDlgPtzControl  *  pDlg  =  (  CDlgPtzControl  *  )CWnd::FromHandlePermanent(  hDlg  );
	if  (  !pDlg  )  return;

	if  (  !pDlg->m_var.pStageLens  )  return;

	CStageLens  &  m_CStageLens  =  *(  CStageLens  *  )pDlg->m_var.pStageLens;
	
	int  m_nAddr  =  pDlg->m_var.m_nAddr;

	switch  (  nResourceID  )  {
			case  IDC_BUTTON_UP:
				  m_CStageLens.Up(  m_nAddr  );
				  break;
			case  IDC_BUTTON_DOWN:
				  m_CStageLens.Down(  m_nAddr  );
				  break;
			case  IDC_BUTTON_LEFT:
				  m_CStageLens.Left(  m_nAddr  );
				  break;
			case  IDC_BUTTON_RIGHT:
				  m_CStageLens.Right(  m_nAddr  );
				  break;
			case  IDC_BUTTON_TOP_LEFT:
				  m_CStageLens.TopLeft(  m_nAddr  );
				  break;
			case  IDC_BUTTON_TOP_RIGHT:
				  m_CStageLens.TopRight(  m_nAddr  );
				  break;
			case  IDC_BUTTON_BOTTOM_LEFT:
				  m_CStageLens.BottomLeft(  m_nAddr  );
				  break;
			case  IDC_BUTTON_BOTTOM_RIGHT:
				  m_CStageLens.BottomRight(  m_nAddr  );
				  break;

			//  2013/04/07
			case  IDC_BUTTON_noop:
				  m_CStageLens.Noop(  m_nAddr  );
				  break;

			//
			case  IDC_BUTTON_FOCUS_IN:
				  m_CStageLens.FocusMinus(  m_nAddr  );
				  break;
			case  IDC_BUTTON_FOCUS_OUT:
				  m_CStageLens.FocusPlus(  m_nAddr  );
				  break;

			case  IDC_BUTTON_IRIS_IN:
				  m_CStageLens.IrisMinus(  m_nAddr  );
				  break;
			case  IDC_BUTTON_IRIS_OUT:
				  m_CStageLens.IrisPlus(  m_nAddr  );
				  break;

			case  IDC_BUTTON_ZOOM_IN:
				  m_CStageLens.ZoomMinus(  m_nAddr  );
				  break;
			case  IDC_BUTTON_ZOOM_OUT:
				  m_CStageLens.ZoomPlus(  m_nAddr  );
				  break;
		  
	}
}

void dlg_YTBtnUp(  HWND  hDlg,  int  nResourceID  )
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
#if  0
	if  (  !pProcInfo->ptz.pStageLens  )  return;

	CStageLens  &  m_CStageLens  =  *(  CStageLens  *  )pProcInfo->ptz.pStageLens;
#endif
	
	CDlgPtzControl  *  pDlg  =  (  CDlgPtzControl  *  )CWnd::FromHandlePermanent(  hDlg  );
	if  (  !pDlg  )  return;

	if  (  !pDlg->m_var.pStageLens  )  return;

	CStageLens  &  m_CStageLens  =  *(  CStageLens  *  )pDlg->m_var.pStageLens;


	int  m_nAddr  =  pDlg->m_var.m_nAddr;

	m_CStageLens.Noop(  m_nAddr  );

}

void dlg_YTCHECKBtn(  HWND  hDlg,  int  nResourceID  )
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
#if  0
	if  (  !pProcInfo->ptz.pStageLens  )  return;

	CStageLens  &  m_CStageLens  =  *(  CStageLens  *  )pProcInfo->ptz.pStageLens;
#endif

	CDlgPtzControl  *  pDlg  =  (  CDlgPtzControl  *  )CWnd::FromHandlePermanent(  hDlg  );
	if  (  !pDlg  )  return;

	if  (  !pDlg->m_var.pStageLens  )  return;

	CStageLens  &  m_CStageLens  =  *(  CStageLens  *  )pDlg->m_var.pStageLens;


	int  m_nAddr  =  pDlg->m_var.m_nAddr;  

	switch  (  nResourceID  )  {
			case  IDC_BUTTON_AUTO_SCAN:
				  if  (  pDlg->m_var.m_bnDown_autoScan )  {
					  m_CStageLens.AutoScan(  m_nAddr  );
					  m_CStageLens.PreSet(  m_nAddr,  99,  CStageLens::PresetAction_Goto  );
				  }
				  else  
				  {
					  m_CStageLens.Noop(  m_nAddr  );
				  }
				  break;			
			case  IDC_BUTTON_RAIN_BRUSH:
				  if  (  pDlg->m_var.m_bnDown_rainBrush  )
				  {
					  m_CStageLens.RainBrushOn(  m_nAddr  );
				  }
				  else  
				  {
					  m_CStageLens.RainBrushOff(  m_nAddr  );
				  }
				  break;
			case  IDC_BUTTON_SEARCH_LIGHT:
				  if  (  pDlg->m_var.m_bnDown_searchLight  )
				  {
					  m_CStageLens.SearchLightOn(  m_nAddr  );
				  }
				  else
				  {
					  m_CStageLens.SearchLightOff(  m_nAddr  );
				  }
				  break;
			default:
				break;
	}
}

void CDlgPtzControl::OnNMReleasedcaptureSliderspeed(NMHDR *pNMHDR, LRESULT *pResult)
{
	MC_VAR_isCli  *  pProcInfo  =  QY_GET_procInfo_isCli(  );
#if  0
	if  (  !pProcInfo->ptz.pStageLens  )  return;

	CStageLens  &  m_CStageLens  =  *(  CStageLens  *  )pProcInfo->ptz.pStageLens;
#endif

	if  (  !m_var.pStageLens  )  return;
	CStageLens  &  m_CStageLens  =  *(  CStageLens  *  )m_var.pStageLens;

	//
	UpdateData(  );
	int  iTest  =  m_slider_speed.GetPos(  );
	m_var.m_nSpeed  =  m_slider_speed.GetPos(  )  *  0x3f  /  100;
	m_CStageLens.SetSpeed(  m_var.m_nSpeed  );
	*pResult = 0;
}

void CDlgPtzControl::OnChangeStatus(  UINT  nID  )
{
	switch(  nID  )  {
		case  IDC_BUTTON_AUTO_SCAN:
			  m_buStatus_autoScan.m_nFlag  =  1 - m_buStatus_autoScan.m_nFlag;
			  m_byStatus_autoScan  =  m_buStatus_autoScan.m_nFlag;
			  m_buStatus_autoScan.RedrawWindow(  );
			  break;
		case  IDC_BUTTON_RAIN_BRUSH:
			  m_buStatus_rainBrush.m_nFlag  =  1 - m_buStatus_rainBrush.m_nFlag;
			  m_byStatus_rainBrush  =  m_buStatus_rainBrush.m_nFlag;
			  m_buStatus_rainBrush.RedrawWindow(  );
			  break;
		case  IDC_BUTTON_SEARCH_LIGHT:
			  m_buStatus_searchLight.m_nFlag  =  1 - m_buStatus_searchLight.m_nFlag;
			  m_byStatus_searchLight  =  m_buStatus_searchLight.m_nFlag;
			  m_buStatus_searchLight.RedrawWindow(  );
			  break;
		default:
			break;
	}
}

void CDlgPtzControl::OnEnChangeEditPre()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(  TRUE  );
	CString  str;
	m_edit_nPrePoint.GetWindowText(  str  );
	m_var.m_nPre  =  _tstoi(  str  );
}

void CDlgPtzControl::OnBnClickedButtonPreGo()
{

	if  (  m_var.m_nPre  >  255  )  {
		AfxMessageBox(  _T(  "Preset ID cannot be more than 255!"  )  );
		SetDlgItemInt(  IDC_EDIT_PRE,  0  );
		return;
	}
	CStageLens  &  m_CStageLens  =  *(  CStageLens  *  )m_var.pStageLens;
	int  m_nAddr  =  m_var.m_nAddr;
	int  m_nPre  =  m_var.m_nPre;

	m_CStageLens.PreSet(  m_nAddr,  m_nPre,  CStageLens::PresetAction_Goto  );
}

void CDlgPtzControl::OnBnClickedButtonPreSet()
{
	if  (  m_var.m_nPre  >  255  )  {
		AfxMessageBox(  _T(  "Preset ID cannot be more than 255!"  )  );
		SetDlgItemInt(  IDC_EDIT_PRE,  0  );
		return;
	}
	CStageLens  &  m_CStageLens  =  *(  CStageLens  *  )m_var.pStageLens;
	int  m_nAddr  =  m_var.m_nAddr;
	int  m_nPre  =  m_var.m_nPre;

	m_CStageLens.PreSet(  m_nAddr,  m_nPre,  CStageLens::PresetAction_Set  );
}

void CDlgPtzControl::OnBnClickedButtonPreClear()
{
	if  (  m_var.m_nPre  >  255  )  {
		AfxMessageBox(  _T(  "Preset ID cannot be more than 255!"  )  );
		SetDlgItemInt(  IDC_EDIT_PRE,  0  );
		return;
	}
	CStageLens  &  m_CStageLens  =  *(  CStageLens  *  )m_var.pStageLens;
	int  m_nAddr  =  m_var.m_nAddr;
	int  m_nPre  =  m_var.m_nPre;

	SetDlgItemInt(  IDC_EDIT_PRE,  0  );
	m_CStageLens.PreSet(  m_nAddr,  m_nPre,  CStageLens::PresetAction_Clear  );
}



void CDlgPtzControl::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	DLG_guiData_ptzControl	*	p	=	&m_var.guiData;

	if  (  !p->iw_org  ||  !p->ih_org  )  return;

	RECT	rc;
	GetClientRect(  &rc  );
	int  w,  h;
	w  =  rc.right  -  rc.left;
	h  =  rc.bottom  -  rc.top;


	//  
	int	idc;
	int  iX,  iY,  iW,  iH;
	float  fx,  fy;
	fx  =  1.  *  w  /  p->iw_org;
	fy  =  1.  *  h  /  p->ih_org;

	 //  header
	idc  =  p->iIDC_BUTTON_ptzSettings;
	rc  =  p->rcIDC_BUTTON_ptzSettings;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_STATIC_hint;
	rc  =  p->rcIDC_STATIC_hint;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_STATIC_speed;
	rc  =  p->rcIDC_STATIC_speed;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_SLIDER_speed;
	rc  =  p->rcIDC_SLIDER_speed;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  
	//	 body
	idc  =  p->iIDC_BUTTON_TOP_LEFT;
	rc  =  p->rcIDC_BUTTON_TOP_LEFT;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_UP;
	rc  =  p->rcIDC_BUTTON_UP;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_TOP_RIGHT;
	rc  =  p->rcIDC_BUTTON_TOP_RIGHT;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_LEFT;
	rc  =  p->rcIDC_BUTTON_LEFT;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_AUTO_SCAN;
	rc  =  p->rcIDC_BUTTON_AUTO_SCAN;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_RIGHT;
	rc  =  p->rcIDC_BUTTON_RIGHT;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_BOTTOM_LEFT;
	rc  =  p->rcIDC_BUTTON_BOTTOM_LEFT;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_DOWN;
	rc  =  p->rcIDC_BUTTON_DOWN;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_BOTTOM_RIGHT;
	rc  =  p->rcIDC_BUTTON_BOTTOM_RIGHT;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_BOTTOM_LEFT;
	rc  =  p->rcIDC_BUTTON_BOTTOM_LEFT;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_noop;
	rc  =  p->rcIDC_BUTTON_noop;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_FOCUS_OUT;
	rc  =  p->rcIDC_BUTTON_FOCUS_OUT;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_IRIS_OUT;
	rc  =  p->rcIDC_BUTTON_IRIS_OUT;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_ZOOM_OUT;
	rc  =  p->rcIDC_BUTTON_ZOOM_OUT;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  
	
	idc  =  p->iIDC_STATIC_focus;
	rc  =  p->rcIDC_STATIC_focus;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_STATIC_iris;
	rc  =  p->rcIDC_STATIC_iris;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_STATIC_zoom;
	rc  =  p->rcIDC_STATIC_zoom;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_FOCUS_IN;
	rc  =  p->rcIDC_BUTTON_FOCUS_IN;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_IRIS_IN;
	rc  =  p->rcIDC_BUTTON_IRIS_IN;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_ZOOM_IN;
	rc  =  p->rcIDC_BUTTON_ZOOM_IN;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_RAIN_BRUSH;
	rc  =  p->rcIDC_BUTTON_RAIN_BRUSH;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_SEARCH_LIGHT;
	rc  =  p->rcIDC_BUTTON_SEARCH_LIGHT;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_STATIC_preset;
	rc  =  p->rcIDC_STATIC_preset;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_EDIT_PRE;
	rc  =  p->rcIDC_EDIT_PRE;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_PRE_GO;
	rc  =  p->rcIDC_BUTTON_PRE_GO;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_PRE_SET;
	rc  =  p->rcIDC_BUTTON_PRE_SET;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDC_BUTTON_PRE_CLEAR;
	rc  =  p->rcIDC_BUTTON_PRE_CLEAR;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	idc  =  p->iIDCANCEL;
	rc  =  p->rcIDCANCEL;
	iX  =  rc.left;  iY  =  rc.top;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;
	iX  *=  fx;  iY  *=  fy;  iW  *=  fx;  iH  *=  fy;  
	::MoveWindow(  GetDlgItem(  idc  )->m_hWnd,  iX,  iY,  iW,  iH,  TRUE  );  

	return;

	//  sizeAllControls(  );

}

