

#include	"stdafx.h"

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainWndProc.h"

#include	"qyCusResTemp.h"

#ifndef  __NOTSUPPORT_MULTIDOC__
	#include	"mainClient.h"
	#include	"mainFrm.h"
#endif
#include	"qyDynLib.h"
#include	"qyAvRecordPublic.h"

#include	"qmcVideoCapture.h"

#include	"myresource.h"

#ifdef  __WINCE__
		#ifndef  __TEST__
				 #include	"ceMenuBar.h"
		#endif
		#include	"dlgTalk_ce.h"
#else
		//  #include	"myHtmlEditCtrl.h"		 
		//  #include	"DlgTalk.h"
		#include	"dlgtalkproc.h"
#endif

#include	"QyPlaySound_wave.h"
#include	"qmcDxSurfacePublic.h"
#include	"qyWnd.h"

#include	"dlgMcClientLogon.h"
#ifdef  __WINCE__
		#include	"dlg_qyMc_winCe.h"
		#include	"dlgObjs.h"
#endif
#include	"DlgQnmCfgOptionsIsClient.h"
//  #include	"DlgInstantAssistant.h"
#include	"module_qisCamCap.h"

#ifndef  __NOTSUPPORT_MULTIDOC__
		 #include	"dlgNotification.h"
#endif
#ifdef  __APP_qyMc_touchscreen__
		//  #include	"qyMc_touchscreenDlg.h"
#endif

//  #include	"DlgMenuIsCli.h"
#include	"mmDeviceProc.h"
#include	"isCliHelpPublic.h"


	extern QYMC_HOTKEY	gHotKeys_main[];

int  getProcedObjsCfg(  );
int  displayNotification(  MIS_CNT  *  pMisCnt,  MIS_MSG_taskStatus  *  pStatus  );





#if  10  // 2013/01/15
// 以下4个函数都是提供的给其他程序调用的
 __declspec(  dllexport  )  void  *  newQyWnd(  int  iWndContentType  )
{
	CQyWnd	*	pWnd	=	NULL;

	switch  (  iWndContentType  )  {
		    case  CONST_qyWndContentType_mcClientLogon:
				  pWnd  =  new  CDlgMcClientLogon;
				  break;
			case  CONST_qyWndContentType_qyMc_winCe:
				  #ifdef  __WINCE__
						  pWnd  =  new  CDlg_qyMc_winCe;
				  #endif
				  break;
			case  CONST_qyWndContentType_qnmCfgOptionsIsClient:
				  pWnd  =  new  CDlgQnmCfgOptionsIsClient;
				  break;
			case  CONST_qyWndContentType_talker:
				  #ifdef  __WINCE__
						  pWnd  =  new  CDlgTalk_ce(  GetDesktopWindow(  )  );
				  #endif
				  break;
			case  CONST_qyWndContentType_objs:
				  #ifdef  __WINCE__
						  pWnd  =  new  CDlgObjs(  GetDesktopWindow(  )  );
				  #endif
				  break;
#if  0
			case  CONST_qyWndContentType_instantAssistant:
				  #ifndef  __SUPPORT_dlgInstantAssistant_mfc__
						  pWnd  =  new  CDlgInstantAssistant;
				  #endif
				  break;
#endif
#if  0
			case  CONST_qyWndContentType_menu_walls:
				  pWnd  =  new  CDlgMenuIsCli;
				  break;
#endif
			default:
					break;
	}
	
	if  (  pWnd  )  pWnd->m_var.iWndContentType  =  iWndContentType;

	return  pWnd;
}
 





#if  0		//  2013/01/18
  __declspec(  dllexport  )  BOOL  dlgTalk_bRefresh(  void  *  pDlgTalkParam,  LPCTSTR  hint,  BOOL  bChanged_layout,  BOOL  bChanged_status  )
{
	MACRO_CDlgTalk	*	pDlgTalk	=	(  MACRO_CDlgTalk  *  )pDlgTalkParam;
	DLG_TALK_var	&	m_var		=	pDlgTalk->m_var;


 	if  (  m_var.guiData.bChanged_layout  ||  bChanged_layout  )  {
		m_var.guiData.bChanged_layout  =  FALSE;
		//
		sizeAllControls_dlgTalk(  pDlgTalk->m_hWnd,  m_var,  NULL  );
		//
		m_var.guiData.bChanged_status  =  TRUE;

		#ifdef  __DEBUG__
				if  (  !hint  )  hint  =  _T(  ""  );
				traceLog(  _T(  "dlgTalk_bRefresh: layout, %s"  ),  hint  );
		#endif

	}
	if  (  m_var.guiData.bChanged_status  ||  bChanged_status  )  {
		m_var.guiData.bChanged_status  =  FALSE;

		PF_commonHandler	pf		=	NULL;
		pf  =  (  PF_commonHandler  )m_var.guiData.pf_refreshDlg_talk_ce;
		if  (  pf  )  pf(  pDlgTalk->m_hWnd,  &m_var.guiData,  0  );

		#ifdef  __DEBUG__
				if  (  !hint  )  hint  =  _T(  ""  );
				traceLog(  _T(  "dlgTalk_bRefresh: status, %s"  ),  hint  );
		#endif

	}

	return  TRUE;
}

 //  __declspec(  dllexport  )  BOOL  dlgTalk_bSelTask(  void  *  pDlgTalkParam,  LPCTSTR  selStr  )
 __declspec(  dllexport  )  BOOL  dlgTalk_bSelTask(  HWND  hDlg,  LPCTSTR  selStr  ) 
{
	BOOL				bRet		=	FALSE;
	//  MACRO_CDlgTalk	*	pDlgTalk	=	(  MACRO_CDlgTalk  *  )pDlgTalkParam;
	DLG_TALK_var		*	pVar	=	getDlgTalkVar(  hDlg  );
	if  (  !pVar  )  return  FALSE;
	DLG_TALK_var	&	m_var		=	*pVar;

	if  (  !selStr  )  return  FALSE;
	
	if  (  m_var.guiData.param.iPageType  !=  CONST_iPageType_task  )  goto  errLabel;
	
	int	iTaskId  =  _ttol(  selStr  );

	traceLog(  _T(  "seltask %d"  ),  iTaskId  );
	MIS_MSG_TASK	*	pMsgTask	=	findTaskInProcessQ(  &m_var,  iTaskId  );
	if  (  !pMsgTask  )  goto  errLabel;
	
	m_var.guiData.task.curSel.iTaskId  =  pMsgTask->iTaskId;
	m_var.guiData.task.curSel.uiTaskType  =  pMsgTask->uiTaskType;
	m_var.guiData.task.curSel.iStatus  =  pMsgTask->iStatus;
	m_var.guiData.task.curSel.bTaskAlive  =  bTaskAlive(  pMsgTask->iStatus  );

	bRet  =  TRUE;

errLabel:
	return  bRet;
}
#endif



 


 



 

 __declspec(  dllexport  )  int  talkToMessenger(  unsigned  __int64  ui64Id,  BOOL  bNeedNotShowWnd,  BOOL  bActivateWnd,  HWND  *  phWnd  )
{
	MSGR_ADDR	addr;
	memset(  &addr,  0,  sizeof(  addr  )  );
	addr.idInfo.ui64Id  =  ui64Id;

	return  talkToMessenger(  g_pQyMc,  &addr,  NULL,  bNeedNotShowWnd,  bActivateWnd,  phWnd  );
}


#if  0
 //
  int  tmpHandler_broadcastMsg(  void  *  p0,  void  *  p1,  void  *  pQElem  )
{
	 int					iRet				=	-1;
	 COMMON_PARAM		*	pCommonParam0		=	(  COMMON_PARAM  *  )p0;
	 COMMON_PARAM		*	pCommonParam1		=	(  COMMON_PARAM  *  )p1;
	 //
	 BOOL					bActivateWnd		=	(  BOOL  )pCommonParam0->p1;
	 unsigned  int		*	puiCnt				=	(  unsigned  int  *  )pCommonParam0->p2;
	 //
	 MSGR_ADDR			*	pAddr				=	(  MSGR_ADDR  *  )pCommonParam1->p0;
	 MIS_MSGU			*	pMsg				=	(  MIS_MSGU  *  )pCommonParam1->p1;
	 unsigned  int			uiMsgLen			=	(  unsigned  int  )pCommonParam1->p2;
	 //  
	 MIS_MSGU			*	pMsgElem			=	(  MIS_MSGU  *  )pQElem;
	 //
	 BOOL					bMatched			=	FALSE;
	 //
	 HWND					hWnd				=	NULL;
	 HWND					hDlgTalk			=	NULL;


	 if  (  pMsgElem->uiType  ==  CONST_misMsgType_talkingFriend_qmc  )  {
		 		 
		 if  (  !lstrcmpi(  pAddr->misServName,  pMsgElem->talkingFriend_qmc.addr.misServName  )  )  {
			 switch  (  pMsgElem->talkingFriend_qmc.addr.uiObjType  )  {
					 case  CONST_objType_phoneGuest:
						   if  (  pAddr->uiObjType  ==  pMsgElem->talkingFriend_qmc.addr.uiObjType
							   &&  pAddr->uiDevType  ==  pMsgElem->talkingFriend_qmc.addr.uiDevType  
									&&  !wcsicmp(  pAddr->wDevIdStr,  pMsgElem->talkingFriend_qmc.addr.wDevIdStr  )
										&&  !wcsicmp(  pAddr->wPath,  pMsgElem->talkingFriend_qmc.addr.wPath  )  )  bMatched  =  TRUE;
						   break;
					 case  CONST_objType_tmpGrp:    
						   if  (  pAddr->uiObjType  ==  CONST_objType_phoneGuest  
							   &&  !wcsicmp(  pAddr->wPath,  pMsgElem->talkingFriend_qmc.addr.wPath  )  )  
						   {
							   if  (  !(  hWnd  =  pMsgElem->talkingFriend_qmc.hWnd  )  )  goto  errLabel;

							   hDlgTalk  =  hWnd;
							   if  (  !hDlgTalk  )  goto  errLabel;
							   DLG_TALK_var	&m_var  =  *getDlgTalkVar(  hDlgTalk  );

							   if  (  !isQEmpty(  &m_var.tmpGrpMemQ  )  )  {  
								   Q_NODE  *  pQNode;
								   MSGR_ADDR  *  pMem;
								   //					
								   for  (  pQNode  =  m_var.tmpGrpMemQ.front.pNext;  pQNode;  pQNode  =  pQNode->pNext  )  {
									    pMem  =  (  MSGR_ADDR  *  )pQNode->qElemMemory.m_pBuf;

										if  (  pAddr->idInfo.ui64Id  )  {	//  µ±ÊÇÕýÊ½³ÉÔ±Ê±£¬idInfoÍ¨³£ÄÜ¾ö¶¨Î¨Ò»ÐÔ
											if  (  pMem->idInfo.ui64Id  ==  pAddr->idInfo.ui64Id  )  {
												bMatched  =  TRUE;  break;											
											}
											continue;
										}

										//  ÁÙÊ±³ÉÔ±£¬ÔòÐèÒª±È½ÏÏÂÃæµÄ²ÎÊý
										if  (  pMem->uiObjType  ==  pAddr->uiObjType
											&&  pMem->uiDevType  ==  pAddr->uiDevType
												&&  !wcsicmp(  pMem->wDevIdStr,  pAddr->wDevIdStr  )  )  
										{										
											bMatched  =  TRUE;  break;
										}
								   }
							   }
						   }
						   break;
					 default:
						     if  (  pAddr->idInfo.ui64Id  ==  pMsgElem->talkingFriend_qmc.addr.idInfo.ui64Id  )  bMatched  =  TRUE;
							 break;
			 }

			 //
			 if  (  bMatched  )  {
				 if  (  !(  hWnd  =  pMsgElem->talkingFriend_qmc.hWnd  )  )  goto  errLabel;
							   
				 hDlgTalk  =  hWnd;
				 if  (  !hDlgTalk  )  goto  errLabel;
									 
				 //  if  (  qPostMsg(   pMsg,  uiMsgLen,  &pDlg->m_var.processQ  )  )  goto  errLabel;
				 if  (  dlgTalk_qPostMsg(  hDlgTalk,  pMsg,  uiMsgLen  )  )  goto  errLabel;
				 ::PostMessage(  hWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );
							 
				 //
				 if  (  bActivateWnd  )  {
					 PostMessage(  g_pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_setActiveWindow,  (  LPARAM  )hWnd  );
				 }	
				 //
				 if  (  puiCnt  )  (  *puiCnt  )  ++  ;
			 }

		 }
	 }

	 iRet  =  0;
errLabel:
	 return  iRet;
}


 //  bActivateWnd±íÊ¾Èç¹û´°¿Ú×îÐ¡»¯£¬ÔòÒª»Ö¸´Õý³£»¯¡£Ò»°ãÔÚ½çÃæ²Ù×÷Ê±ÉèÖÃ´Ë±êÖ¾
 int  broadcastMsg(  void  *  pQyMcParam,  MSGR_ADDR  *  pAddr,  BOOL  bActivateWnd,  MIS_MSGU  *  pMsg,  unsigned  int  uiMsgLen  )
{
	 int						iErr								=	-1;
	 QY_MC					*	pQyMc								=	(  QY_MC  *  )pQyMcParam;
	 MACRO_CDlgTalk			*	pDlgTalk							=	NULL;
	 RECT						rect;
	 unsigned  int				uiCnt;
	 COMMON_PARAM				commonParam0;
	 COMMON_PARAM				commonParam1;
	 MIS_CNT				*	pMisCnt								=	NULL;
	 HWND						hWnd								=	NULL;
	 int						iRet;
	 HWND						hFore								=	NULL;
	 //     
	 
	 if  (  !pAddr  )  return  -1;

	 if  (  !(  pMisCnt  =  getMisCntByName(  pQyMc,  NULL,  pAddr->misServName  )  )  )  goto  errLabel;
	 
	 uiCnt  =  0;
	 MACRO_makeCommonParam3(  0,  (  void  *  )bActivateWnd,  &uiCnt,  commonParam0  );
	 MACRO_makeCommonParam3(  (  void  *  )pAddr,  (  void  *  )pMsg,  (  void  *  )uiMsgLen,  commonParam1  );
	 //
	 iRet  =  qTraverse(  &pMisCnt->talkingFriendQ,  tmpHandler_broadcastMsg,  &commonParam0,  &commonParam1  );  
	 if  (  iRet  )  goto  errLabel;

	 if  (  uiCnt  )  {		//  ÒÑ¾­ÕÒµ½ÁËÏà¹ØµÄ´°¿Ú¡£ËùÒÔ£¬²»ÓÃÐÂÉú³É´°¿ÚÁË
		 iErr  =  0;  goto  errLabel;
	 }


	 memset(  &rect,  0,  sizeof(  rect  )  );
	 
	 if  (  !bActivateWnd  )  {		//
         hFore  =  GetForegroundWindow(  );
	 }

	 pDlgTalk  =  new  MACRO_CDlgTalk(  ::GetDesktopWindow(  )  );
	 if  (  !pDlgTalk  )  goto  errLabel;

	 BOOL  bNeedNotShowWnd  =  FALSE;

#ifndef  __WINCE__
	 //  if  (  !pDlgTalk->bSetDlgInfo(  0,  pAddr,  NULL,  bNeedNotShowWnd,  hFore  )  )  goto  errLabel;
	 if  (  !dlgTalk_bSetDlgInfo(  pDlgTalk->m_hWnd,  pDlgTalk->m_var,  pAddr,  NULL,  0,  bNeedNotShowWnd,  hFore  )  )  goto  errLabel;
	 if  (  !pDlgTalk->Create(  rect  )  )  goto  errLabel;
#else
	 //  if  (  !pDlgTalk->bSetDlgInfo(  0,  pAddr,  NULL,  bNeedNotShowWnd,  hFore  )  )  goto  errLabel;
	 //  if  (  !pDlgTalk->Create(  rect  )  )  goto  errLabel;

	 traceLog(  _T(  "broadcastMsg failed,  dlgTalk_ce.Create not finished"  )  );
	 goto  errLabel;
#endif
	 //  
	 hWnd  =  pDlgTalk->m_hWnd;

	 //  2010/01/08
	 if  (  !bNeedNotShowWnd  )  {			
		 if  (  hFore  )  {
			 //  ShowWindow(  pDlgTalk->m_hWnd,  SW_SHOWNOACTIVATE    );				
			 ShowWindow(  pDlgTalk->m_hWnd,  SW_SHOWNA    );				
			 }
		 else  
			 ShowWindow(  pDlgTalk->m_hWnd,  SW_SHOW  );
	 }

	 //
	 PostMessage(  g_pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_setActiveWindow,  (  LPARAM  )hWnd  );

	 //
	 //
	 //  if  (  qPostMsg(   pMsg,  uiMsgLen,  &pDlgTalk->m_var.processQ  )  )  goto  errLabel;
	 if  (  dlgTalk_qPostMsg(  pDlgTalk->m_hWnd,  pMsg,  uiMsgLen  )  )  goto  errLabel;
	 ::PostMessage(  hWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
		 if  (  pDlgTalk  )  delete  pDlgTalk;
	 }
	 if  (  !iErr  )  {
		 if  (  bActivateWnd  )  {
			 #ifndef  __WINCE__
					  if  (  IsIconic(  hWnd  )  )  SendMessage(  hWnd,  WM_SYSCOMMAND,  SC_RESTORE,  0  );
			 #endif
		 }
	 }

	 return  0;
}
#endif



 //  2012/05/13
 int  tryToTalkToMessenger(  void  *  pMSGR_ADDR,  BOOL  bActivateWnd,  HWND	*	phWnd  )
 {
	 int					iErr				=	-1;
	 MSGR_ADDR			*	pAddr				=  (  MSGR_ADDR  *  )pMSGR_ADDR;
	 QY_MC				*	pQyMc				=	QY_GET_GBUF(  );
	 MC_VAR_isCli		*	pProcInfo			=	QY_GET_procInfo_isCli(  );
	 HWND					hWnd				=	NULL;
	 BOOL					bExists_already		=	FALSE;
	 HWND					hShadow				=  NULL;

	 if  (  !pAddr  )  return  -1;

	 MSGR_ADDR  &  addr_logicalPeer  =  *pAddr;
	 								
	 BOOL	bTalkerOk  =  FALSE;
	 int	i;
	 if  (  !findTalker(  pQyMc,  &addr_logicalPeer,  0,  &hWnd  )  )  bExists_already  =  TRUE;
	 
	 if  (  !bExists_already  )  {
		  if  (  talkToMessenger(  pQyMc,  &addr_logicalPeer,  NULL,  TRUE,  FALSE,  &hWnd  )  )  goto  errLabel;
	 }

	 //
	 DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var	*	)getDlgTalkVar(  hWnd  );
	 if  (  !pDlgTalkVar  )  goto  errLabel;
	 if  (  !isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  goto  errLabel;

	 //  2012/05/23
	 if  (  pDlgTalkVar->ucbTmpMsgr  )  {
		 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "Gui"  ),  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "tryToTalkToMessenger failed: no shadow allowed,  %I64u is tmpMsgr"  ),  addr_logicalPeer.idInfo.ui64Id  );
		 goto  errLabel;
	 }

	 //
	 TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pDlgTalkVar->pShadowInfo;
	 if  (  !pShadowMgr  )  goto  errLabel;
	 for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
		  if  (  !IsWindow(  pShadowMgr->shadows[i].hShadow  )  )  continue;
		  if  (  isTalkerSubType_canInput(  pShadowMgr->shadows[i].iTalkerSubType  )  )													 												   
		  {
			  bTalkerOk  =  TRUE;													  
			  break;													  
		  }												  
	 }
	 if  (  !bTalkerOk  )  {
		 if  (  !pDlgTalkVar->guiData.param.bNeedNotShowWnd  )  {
			 bTalkerOk  =  TRUE;
		 }
	 }
	 if  (  !bTalkerOk  )  {
		 if  (  IsWindow(  pProcInfo->g_hVWall  )  )  {
			 //			
			 //  先在shadows里找个空位			
			 for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {									
				  if  (  !IsWindow(  pShadowMgr->shadows[i].hWall  )  )  break;				
			 }
			 if  (  i  ==  mycountof(  pShadowMgr->shadows  )  )  {
				 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "Gui"  ),  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "tryToTalkToMessenger failed: no new shadow allowed,  %I64u"  ),  addr_logicalPeer.idInfo.ui64Id  );
				 goto  errLabel;
			 }

			 //
			 int	iTalkerSubType  =  CONST_talkerSubType_onVWall_global;
			 MSGR_ADDR	addr;
			 memcpy(  &addr,  &pDlgTalkVar->addr,  sizeof(  addr  )  );
			 addr.uiTranNo_shadow  =  getuiNextTranNo(  0,  0,  0  );
			 //
			 getTalkerShadow(  pProcInfo->g_hVWall,  &addr,  NULL,  iTalkerSubType,  FALSE,  0,  &hShadow  );				  
			 if  (  !IsWindow(  hShadow  )  )  goto  errLabel;
			 //
			 memset(  &pShadowMgr->shadows[i],  0,  sizeof(  pShadowMgr->shadows[i]  )  );
			 pShadowMgr->shadows[i].hWall  =  pProcInfo->g_hVWall;
			 pShadowMgr->shadows[i].iWndContentType_wall  =  CONST_qyWndContentType_vWall;
			 pShadowMgr->shadows[i].iTalkerSubType  =  iTalkerSubType;
			 pShadowMgr->shadows[i].hShadow  =  hShadow;
			 //
			 bTalkerOk  =  TRUE;
		 }											  
	 }

	 //  2012/05/18
	 if  (  !bTalkerOk  )  {
			 //			
			 //  先在shadows里找个空位			
			 for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {									
				  if  (  !IsWindow(  pShadowMgr->shadows[i].hWall  )  )  break;				
			 }
			 if  (  i  ==  mycountof(  pShadowMgr->shadows  )  )  {
				 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "Gui"  ),  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "tryToTalkToMessenger failed: no new shadow allowed,  %I64u"  ),  addr_logicalPeer.idInfo.ui64Id  );
				 goto  errLabel;
			 }

			 //
			 int	iTalkerSubType  =  CONST_talkerSubType_enlarged_mgr;
			 MSGR_ADDR	addr;
			 memcpy(  &addr,  &pDlgTalkVar->addr,  sizeof(  addr  )  );
			 addr.uiTranNo_shadow  =  getuiNextTranNo(  0,  0,  0  );
			 //
			 getTalkerShadow(  GetDesktopWindow(  ),  &addr,  NULL,  iTalkerSubType,  FALSE,  0,  &hShadow  );				  
			 if  (  !IsWindow(  hShadow  )  )  goto  errLabel;
			 //
			 memset(  &pShadowMgr->shadows[i],  0,  sizeof(  pShadowMgr->shadows[i]  )  );
			 pShadowMgr->shadows[i].hWall  =  hWnd;
			 pShadowMgr->shadows[i].iWndContentType_wall  =  0;
			 pShadowMgr->shadows[i].iTalkerSubType  =  iTalkerSubType;
			 pShadowMgr->shadows[i].hShadow  =  hShadow;
			 //
			 bTalkerOk  =  TRUE;
	 }


	 //
	 if  (  !bTalkerOk  )  {
		 if  (  talkToMessenger(  pQyMc,  &addr_logicalPeer,  NULL,  FALSE,  bActivateWnd,  &hWnd  )  )  goto  errLabel;
		 }
	 else  if  (  bActivateWnd  )  {
			   if  (  talkToMessenger(  pQyMc,  &addr_logicalPeer,  NULL,  TRUE,  bActivateWnd,  &hWnd  )  )  goto  errLabel;
	 }

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
		 if  (  IsWindow(  hShadow  )  )  PostMessage(  hShadow,  WM_CLOSE,  0,  0  );
		 if  (  !bExists_already  )  {
			 if  (  IsWindow(  hWnd  )  )  PostMessage(  hWnd,  WM_CLOSE,  0,  0  );
		 }
	 }
	 if  (  !iErr  )  {
		 if  (  phWnd  )  *phWnd  =  hWnd;
	 }

	 return  iErr;
}

int  tryToTalkToMessenger(  unsigned  __int64  ui64Id,  BOOL  bActivateWnd,  HWND	*	phWnd  )
{
 
 	MSGR_ADDR	addr;
	memset(  &addr,  0,  sizeof(  addr  )  );
	addr.idInfo.ui64Id  =  ui64Id;

	return  tryToTalkToMessenger(  &addr,  bActivateWnd,  phWnd  );
}


//  2013/05/24
BOOL  bTaskId_conference(  int  iTaskId  )
{
	BOOL				bRet				=	FALSE;
	MC_VAR_isCli	*	pProcInfo			=	QY_GET_procInfo_isCli(  );
	int					iIndex_sharedObj	=  getSharedObjIndex_localAv(  );
	QY_SHARED_OBJ	*	pSharedObj			=	getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;

	if  (  !iTaskId  )  goto  errLabel;

	if  (  !bSharedObjActive(  pProcInfo,  iIndex_sharedObj  )  )  goto  errLabel;

	int  i;
	for  (  i  =  0;  i  <  mycountof(  pSharedObj->usrs  );  i  ++  )  {
		if  (  pSharedObj->usrs[i].iTaskId  ==  iTaskId  )  break;		 
	}
	if  (  i  ==  mycountof(  pSharedObj->usrs  )  )  goto  errLabel;

	bRet  =  TRUE;

errLabel:
	return  bRet;
}

 //  2012/03/30
 int  doApplyForPlayer(  HWND  hMainWnd,  MIS_MSGU  *  pMsg  )
 {
	 int						iErr	=	-1;
	 QY_MC					*	pQyMc	=	QY_GET_GBUF(  );
	 int						i;

	 QY_SERVICEGUI_INFO		*	pSgi;		pSgi		=	getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
	 if  (  !pSgi  )  goto  errLabel;
	 MC_VAR_isCli				*	pProcInfo;	pProcInfo	=  (  MC_VAR_isCli  *  )pSgi->pVar;
	 if  (  !pProcInfo  )  goto  errLabel;
	 DWORD						dwThreadDaemonId;

	 TCHAR						tHintBuf[256]				=	_T(  ""  );

	 traceLogA(  "CMainFrame: get applyForPlayer_qmc msg: %I64u",  pMsg->applyForPlayer_qmc.idInfo_recorder.ui64Id  );

	 if  (  !pMsg->applyForPlayer_qmc.idInfo_recorder.ui64Id  &&  !pMsg->applyForPlayer_qmc.audio.uiTranNo  &&  !pMsg->applyForPlayer_qmc.video.uiTranNo  )  {
		 safeTcsnCpy(  _T(  "idInfo and uiTranNo are 0"  ),  tHintBuf,  mycountof(  tHintBuf  )  );
		 goto  errLabel;
	 }

	 //  2012/05/07
	 if  (  pMsg->applyForPlayer_qmc.bGps  )  {
		 //
		 QY_PLAYER_gps		*	pPlayer_gps;
		 for  (  i  =  0;  i  <  pProcInfo->gps.usCnt_players;  i  ++  )  {
			  pPlayer_gps  =  &pProcInfo->gps.pPlayers[i];
			  if  (  pPlayer_gps->idInfo.ui64Id  )  {
				  if  (  GetTickCount(  )  -  pPlayer_gps->dwTickCnt_lastRecvd  >  30  *  1000  )  {
					  pPlayer_gps->idInfo.ui64Id  =  0;
					  pPlayer_gps->iTaskId  =  0;
				  }
			  }
			  if  (  pMsg->applyForPlayer_qmc.idInfo_recorder.ui64Id  ==  pPlayer_gps->idInfo.ui64Id
				  &&  pMsg->applyForPlayer_qmc.iTaskId  ==  pPlayer_gps->iTaskId  )
			  {
				  break;
			  }
		 }
		 if  (  i  ==  pProcInfo->gps.usCnt_players  )  {
			 //  try to find an unused player
			 for  (  i  =  0;  i  <  pProcInfo->gps.usCnt_players;  i  ++  )  {
				  pPlayer_gps  =  &pProcInfo->gps.pPlayers[i];
				  if  (  !pPlayer_gps->idInfo.ui64Id
					  &&  !pPlayer_gps->iTaskId  )
				  {
					  break;
				  }
			 }
			 if  (  i  ==  pProcInfo->gps.usCnt_players  )  {
				 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "too many gps players"  )  );
				 goto  errLabel;
			 }
			 pPlayer_gps->idInfo.ui64Id  =  pMsg->applyForPlayer_qmc.idInfo_recorder.ui64Id;
			 pPlayer_gps->iTaskId  =  pMsg->applyForPlayer_qmc.iTaskId;
			 pPlayer_gps->dwTickCnt_lastRecvd  =  GetTickCount(  );
		 }

		 //
		 iErr  =  0;  goto  errLabel;
	 }

	 //
	 QY_PLAYER				*	pPlayer;
	 PLAY_AUDIO_procInfo	*	pPlayAudio;
	 PLAY_VIDEO_procInfo	*	pPlayVideo;

	 for  (  i  =  0;  i  <  pProcInfo->av.usCnt_players;  i  ++  )  {
		 pPlayer  =  &pProcInfo->av.pPlayers[i];
		 pPlayAudio  =  &pProcInfo->av.pPlayers[i].audio;
		 pPlayVideo  =  &pProcInfo->av.pPlayers[i].video;
		 //
		 waitForQThread(  (  QY_qThreadProcInfo_common  *  )pPlayAudio,  0  );
		 waitForQThread(  (  QY_qThreadProcInfo_common  *  )pPlayVideo,  0  );
		 if  (  !bQThreadExists(  *pPlayAudio  )  &&  !bQThreadExists(  *pPlayVideo  )  )  {
			 if  (  pPlayer->idInfo_recorder.ui64Id  ||  pPlayAudio->uiTranNo  ||  pPlayVideo->uiTranNo  )  											  
			 {
				 pPlayer->idInfo_recorder.ui64Id  =  0;										//  reset
				 pPlayAudio->uiTranNo  =  0;
				 pPlayVideo->uiTranNo  =  0;
				 pPlayer->iTaskId  =  0;														//  2009/09/17
			 }
		 }										  
		 //
		 if  (  pMsg->applyForPlayer_qmc.iTaskId  ==  pPlayer->iTaskId
			 &&  pMsg->applyForPlayer_qmc.idInfo_recorder.ui64Id  ==  pPlayer->idInfo_recorder.ui64Id  
			 &&  pMsg->applyForPlayer_qmc.audio.uiTranNo  ==  pPlayAudio->uiTranNo
			 &&  pMsg->applyForPlayer_qmc.video.uiTranNo  ==  pPlayVideo->uiTranNo  )  												
		 {									
			 break;
		 }
	 }
	 if  (  i  ==  pProcInfo->av.usCnt_players  )  {

		 //  try to find an unused player
		 for  (  i  =  0;  i  <  pProcInfo->av.usCnt_players;  i  ++  )  {
			 pPlayer  =  &pProcInfo->av.pPlayers[i];
			 pPlayAudio  =  &pProcInfo->av.pPlayers[i].audio;
			 pPlayVideo  =  &pProcInfo->av.pPlayers[i].video;
			 if  (  !pPlayer->idInfo_recorder.ui64Id
				 &&  !pPlayAudio->uiTranNo
				 &&  !pPlayVideo->uiTranNo  )  
			 {
				 break;
			 }
		 }
		 if  (  i  ==  pProcInfo->av.usCnt_players  )  {
			 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "too many players"  )  );
			 goto  errLabel;
		 }

		 pPlayer->idInfo_recorder.ui64Id  =  pMsg->applyForPlayer_qmc.idInfo_recorder.ui64Id;
		 //
		 pPlayAudio->uiTranNo  =  pMsg->applyForPlayer_qmc.audio.uiTranNo;
		 memcpy(  &pPlayAudio->ah,  &pMsg->applyForPlayer_qmc.audio.ah,  sizeof(  pPlayAudio->ah  )  );
		 //  2009/06/14
		 memcpy(  &pPlayAudio->playCfg,  &pMsg->applyForPlayer_qmc.audio.playCfg,  sizeof(  pPlayAudio->playCfg  )  );
		 //
		 pPlayVideo->uiTranNo  =  pMsg->applyForPlayer_qmc.video.uiTranNo;
		 memcpy(  &pPlayVideo->vh,  &pMsg->applyForPlayer_qmc.video.vh,  sizeof(  pPlayVideo->vh  )  );
		 pPlayVideo->ucbFlippedImg  =  pMsg->applyForPlayer_qmc.video.ucbFlippedImg;		//  2011/12/11
		 //
		 pPlayer->iTaskId  =  pMsg->applyForPlayer_qmc.iTaskId;			//  2009/09/17
	 }
	 //  2009/02/09

	 waitForQThread(  (  QY_qThreadProcInfo_common  *  )pPlayAudio, 10  );
	 if  (  !bQThreadExists(  *pPlayAudio  )  )  {

		 //  2013/05/24
		 pPlayAudio->playbackDevDesc[0]  =  0;

		 //
		 if  (  pQyMc->bUseDirectSound_toPlay  )  {
			 exitDSoundToPlayIfNoPlayer(  );

			 //
			 LPGUID  lpGuid  =  NULL;
			 
			 //  还要检查是否是会议里的player. 对于不是会议的播放,采用系统缺省设备.
			 OLD_audioDevice	audioDev;
			 if  (  bTaskId_conference(  pPlayer->iTaskId  )  )  {
				 if  (  !getDefaultPlaybackDevice(  &audioDev  )  )  {				 
					 lpGuid  =  &audioDev.guid_audio;
					 safeTcsnCpy(  audioDev.names_audio,  pPlayAudio->playbackDevDesc,  mycountof(  pPlayAudio->playbackDevDesc  )  );
				 }
			 }

			 //
			 if  (  initDSoundToPlay(  (  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx,  lpGuid,  hMainWnd,  0  )  )  {
				 traceLogA(  "CMainFrame::OnQyPostComm: initDSoundToPlay failed."  );
				 //  goto  errLabel;
			 }
			 else  {

				 //
				 traceLogA(  "CMainFrame: start audio player: %I64u,%d",  pMsg->applyForPlayer_qmc.idInfo_recorder.ui64Id,  pMsg->applyForPlayer_qmc.audio.uiTranNo  );
				 if  (  startQThread(  mcThreadProc_playAudio,  pSgi,  NULL,  (  QY_qThreadProcInfo_common  *  )pPlayAudio  )  )  goto  errLabel;
			 }
		 }
		 else  {	//  use wave api. 2010/05/03

			   #if  0	//  def  __DEBUG__
					if  (  startQThread(  NULL,  0,  RUNTIME_CLASS(  CQyPlaySound  ),  *(  QY_qThreadProcInfo_common  * )pPlayAudio  )  )  goto  errLabel;
			   #endif

				if  (  startQThread(  NULL,  0,  new  CQyPlaySound,  (  QY_qThreadProcInfo_common  * )pPlayAudio  )  )  goto  errLabel;
		 }
	 }
	 waitForQThread(  (  QY_qThreadProcInfo_common  *  )pPlayVideo,  10  );
	 if  (  !bQThreadExists(  *pPlayVideo  )  )  {

		 traceLogA(  "CMainFrame: start video player: %I64u,%d",  pMsg->applyForPlayer_qmc.idInfo_recorder.ui64Id,  pMsg->applyForPlayer_qmc.video.uiTranNo  );
		 //
		 pPlayVideo->hThread  =  CreateThread(  NULL,  0,  mcThreadProc_playVideo,  pSgi,  CREATE_SUSPENDED,  &dwThreadDaemonId  );
		 if  (  !pPlayVideo->hThread  )  {
			 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "applyForPlayer failed. CreateThread video failed"  )  );
			 goto  errLabel;
		 }
		 pPlayVideo->dwThreadId  =  dwThreadDaemonId;
		 if  (  ResumeThread(  pPlayVideo->hThread  )  ==  -1  )  goto  errLabel;
	 }


	 iErr  =  0;

errLabel:

	 //  if  (  iErr  )  
	 {
		 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "applyForPlayer leave, %s. %s"  ),  iErr  ?  _T(  "failed"  )  :  _T(  "OK"  ),  tHintBuf  );
	 }

	 //
	 int  nThreads_player   =  0;
	 for  (  i  =  0;  i  <  pProcInfo->av.usCnt_players;  i  ++  )  {
		  pPlayer  =  &pProcInfo->av.pPlayers[i];
		  if  (  bQThreadExists(  pPlayer->audio  )  )  nThreads_player  ++  ;
		  if  (  bQThreadExists(  pPlayer->video  )  )  nThreads_player  ++  ;	  
	 }
	 if  (  bQThreadExists(  pProcInfo->av.localAv.player.audio  )  )  nThreads_player  ++  ;
	 if  (  bQThreadExists(  pProcInfo->av.localAv.player.video  )  )  nThreads_player  ++  ;
	 if  (  pProcInfo->status.nThreads_player  !=  nThreads_player  )  pProcInfo->status.nThreads_player  =  nThreads_player; 
	

	return  iErr;
									 
}
#endif
