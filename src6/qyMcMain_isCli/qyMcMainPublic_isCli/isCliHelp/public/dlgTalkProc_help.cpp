
#include	"stdafx.h"

#include	<windowsx.h>
#include	<math.h>
#include	"qymcMainCommon.h"
#include	"myresource.h"


#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture.h"

#ifdef  __SUPPORT_HTMLEDIT__
	#include	"myHtmlEditCtrl.h"
#endif

#include	"tmpCeLib.h"

#include	"qyOpenShellCommon.h"
#include	"DlgTalk.h"
#include	"qyRtcCommProc.h"
#include	"qyCusResTemp.h"
//  #include	"DlgVideos.h"
//  #include	"DlgCfgVideoConference.h"
//  #include	"DlgPolicyIsClient.h"
#include	"DlgInstantAssistant.h"
//  #include	"DlgSelectAvDev.h"

#include	<assert.h>
#ifndef  __WINCE__
	#include	"qyPs.h"
#endif
#include	"qmcDxSurfacePublic.h"
#include	"qmcConferenceWall.h"
//  #include	"dlgProgress.h"
#include	"isCliHelpPublic.h"
#include	"qmcCmdProc.h"
#include	"isCmdConst.h"

#include	"qmcVmrProc.h"
#include	"funcsForIsCliHelp.h"


//  2012/04/30
 __declspec(  dllexport  )  BOOL  dlgTalk_bQuitDlg(  void  **  ppDlgTalkParam,  BOOL  bCancelTasks  )
{
	if  (  !ppDlgTalkParam  ||  !*ppDlgTalkParam  )  return  FALSE;

	BOOL				bRet		=	FALSE;
	MACRO_CDlgTalk	*	pDlgTalk	=	(  MACRO_CDlgTalk  *  )*ppDlgTalkParam;

	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return  FALSE;
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	DLG_TALK_var	&	m_var		=	pDlgTalk->m_var;
	int					i;

#ifdef  __DEBUG__
		traceLogA(  "CDlgTalk(  )::bQuitDlg enters"  );
		//  MC_VAR_isCli  *  pProcInfo	=	QY_GET_procInfo_isCli(  );
#endif

	//  2012/05/25
	if  (  pProcInfo->cfg.debugStatusInfo.ucbShowDlgTalkStatus  )  {
		qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk_bQuitDlg %I64u, %d enters"  ),  m_var.addr.idInfo.ui64Id,  m_var.addr.uiTranNo_shadow  ); 
	}


	//
	BOOL				bShadowMgr	=	isTalkerShadowMgr(  m_var.addr  );
	QY_MESSENGER_ID		tmp_idInfo;	
	tmp_idInfo.ui64Id  =  m_var.addr.idInfo.ui64Id;
	unsigned  int		tmp_uiTranNo_shadow	=	m_var.addr.uiTranNo_shadow;
	int					tmp_iTalkerSubType	=	m_var.iTalkerSubType;
	HWND				tmphDlgTalk  =  pDlgTalk->m_hWnd;

	//
	M_syncFlg_bQuitDlg_start(  &m_var.syncFlgs.bLocked_bQuitDlg,  tmphDlgTalk,  _T(  "CDlgTalk::bQuitDlg failed, bLocked already."  )  );

	//
	{
		CQySyncFlg	syncFlg;
		if  (  syncFlg.sync(  &m_var.syncFlgs.bSubWndExists  )  )  {
			qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::bQuitDlg failed, subWnd exists."  )  );
			goto  errLabel;		//  2011/03/28. 如果子窗口不关闭，这个退出就不能进行。
		}

		//  2011/03/07. 要把instantAssistant放在这里，因为如果resourceWnd或者会议窗口先关闭时，instantAssistant作为resourceWnd的子窗口将失效，所以就关不了了，会造成内存泄露。
		if  (  m_var.hWnd_instantAssistant  )  closeInstantAssistant(  pDlgTalk->m_hWnd  );
		if  (  IsWindow(  m_var.hWnd_instantAssistant  )  )  {
			#ifdef  __DEBUG__
					traceLog(  _T(  "dlgTalk_bQuitDlg failed, closeInstantAssistant failed"  )  );
			#endif
			goto  errLabel;
		}

		//  2012/05/16. 先关闭所有输入窗口.
		if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
			TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
			if  (  pShadowMgr  )  {
				for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
					//
					if  (  !isTalkerSubType_canInput(  pShadowMgr->shadows[i].iTalkerSubType  )  )  continue;
					//
					if  (  IsWindow(  pShadowMgr->shadows[i].hShadow  )  )  {
						SendMessage(  pShadowMgr->shadows[i].hShadow,  WM_CLOSE,  0,  0  );
						if  (  IsWindow(  pShadowMgr->shadows[i].hShadow  )  )  goto  errLabel;
					}
				}
			}
		}
		//  2012/05/18
		if  (  !isTalkerShadowMgr(  m_var.addr  )  )  {
			TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )m_var.pShadowInfo;
			if  (  pShadow  )  {
				if  (  IsWindow(  pShadow->hEnlargedWnd  )  )  {
					SendMessage(  pShadow->hEnlargedWnd,  WM_CLOSE,  0,  0   );
					if  (  IsWindow(  pShadow->hEnlargedWnd  )  )  goto  errLabel;
				}
			}
		}


		//  2012/04/30
		if  (  !isTalkerShadowMgr(  m_var.addr  )  )  {
			  HWND				hMgr  =  NULL;
			  DLG_TALK_var	*	pMgrVar	=	NULL;

			  if  (  !isTalkerSubType_canInput(  m_var.iTalkerSubType  )  )  {
					bCancelTasks  =  FALSE;
					}			
			  else  {
				    if  (  !m_var.pShadowInfo  )  bCancelTasks  =  FALSE;				  
					else  {
					      TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )m_var.pShadowInfo;
						  hMgr  =  pTalkerShadow->hMgr;
						  pMgrVar  =  (  DLG_TALK_var  *  )getDlgTalkVar(  hMgr  );										  
					}			
			  }
			  if  (  !pMgrVar  ||  !pMgrVar->m_pProcessQ  )  bCancelTasks  =  FALSE;
			  else  if  (  isTalkerShadowMgr(  pMgrVar->addr  )  )  {
						TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
						if  (  pShadowMgr  )  {
							//  2012/05/14
							int  n  =  0;
							for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
								 if  (  pShadowMgr->shadows[i].hShadow  ==  pDlgTalk->m_hWnd  )  continue;
								 if  (  IsWindow(  pShadowMgr->shadows[i].hShadow  )  &&  isTalkerSubType_canInput(  pShadowMgr->shadows[i].iTalkerSubType  )  )  n  ++  ;
							}
							if  (  n  )  bCancelTasks  =  FALSE;
						}		
			  }
		}


		//
		if  (  bCancelTasks  )  {

			//  
			if  (  pFuncs->pf_dlgTalk_cancelTasks(  pDlgTalk->m_hWnd,  &m_var,  0  )  <  0  )  {
				QY_MC  *  pQyMc  =  QY_GET_GBUF(  );
				if  (  !pQyMc->bQuit  )  goto  errLabel;
			}
		}


		//
		if  (  m_var.av.hWnd_remoteAv_taskInfo  )  ::SendMessage(  m_var.av.hWnd_remoteAv_taskInfo,  WM_CLOSE,  0,  0  );
		if  (  m_var.av.hWnd_remoteAv_resourcesInfo  )  ::SendMessage(  m_var.av.hWnd_remoteAv_resourcesInfo,  WM_CLOSE,  0,  0  );
		//  if  (  m_var.hWnd_vWall  )  SendMessage(  m_var.hWnd_vWall,  WM_CLOSE,  0,  0  );
		//
		if  (  m_var.ptzControl.hWnd_ptzControl  )  ::SendMessage(  m_var.ptzControl.hWnd_ptzControl,  WM_CLOSE,  0,  0  );			//  2013/02/16
		if  (  IsWindow(  m_var.ptzControl.hWnd_ptzControl  )  )  {
			qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::bQuitDlg failed, ptz still exists."  )  );
			goto  errLabel;
		}
		if  (  m_var.subtitles.hWnd_subtitles  )  ::SendMessage(  m_var.subtitles.hWnd_subtitles,  WM_CLOSE,  0,  0  );
		if  (  IsWindow(  m_var.subtitles.hWnd_subtitles  )  )  {
			qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::bQuitDlg failed, subtitles still exists."  )  );
			goto  errLabel;
		}

		//  2012/04/23
		if  (  isTalkerShadowMgr(  m_var.addr  )  )  {
			TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )m_var.pShadowInfo;
			if  (  pShadowMgr  )  {
				for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
					if  (  IsWindow(  pShadowMgr->shadows[i].hShadow  )  )  {
						SendMessage(  pShadowMgr->shadows[i].hShadow,  WM_CLOSE,  0,  0  );
					}
				}
				//  2012/05/17. 要确保所有的子窗口都被关闭
				for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
					 if  (  IsWindow(  pShadowMgr->shadows[i].hShadow  )  )  break;					
				}
				if  (  i  <  mycountof(  pShadowMgr->shadows  )  )  {
					qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::bQuitDlg failed, shadow still exists."  )  );
					goto  errLabel;
				}
			}
		}
	}

	//  2009/05/01
	DestroyWindow(  tmphDlgTalk  );
#ifdef  __WINCE__
	    dlgTalk_PostNcDestroy(  ppDlgTalkParam  );
#endif

	//  2012/05/15. 检查一下
	if  (  !bShadowMgr  )  {
		if  (  tmp_idInfo.ui64Id  )  {
			HWND	hMgr	=	NULL;
			MIS_CNT	*	pMisCnt	=	getMisCntByName(  pQyMc,  NULL,  _T(  ""  )  );
			if  (  !findTalker(  pQyMc,  pMisCnt,  &tmp_idInfo,  &hMgr  )  )  {
				#if  0
				if  (  tmp_iTalkerSubType  ==  CONST_talkerSubType_enlarged_mgr  )  {
					//  该窗口代表主窗口,所以把主窗口也关闭
					PostMessage(  hMgr,  WM_CLOSE,  0,  0  );
					}
				else  
				#endif
				{  // 如果没有影子窗口,并且主窗口也不可视,则关闭主窗口 
					  DLG_TALK_var	*	pMgrVar  =  (  DLG_TALK_var	*	)getDlgTalkVar(  hMgr  );
					  if  (  pMgrVar  )  {
						  TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
						  if  (  pShadowMgr  )  {
							  for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
								   TALKER_shadow_mgrMem  *  pMem  =  &pShadowMgr->shadows[i];

								   if  (  IsWindow(  pMem->hShadow  )  )  break;							 
								   if  (  pMem->uiVwRuleType  ==  CONST_vwRuleType_dynBmp  &&  IsWindow(  pMem->hWall  )  )  break;
							  }
							  if  (  i  ==  mycountof(  pShadowMgr->shadows  )  )  {	//  说明没有影子了
								  if  (  isInvisibleMgr(  *pMgrVar  )  )  {	
									  #ifdef  __DEBUG__
											  traceLog(  _T(  "dlgTalk_bQuitDlg: %I64u, no shadow left and mgr is invisible, so close the shadow mgr"  ),  tmp_idInfo.ui64Id  );
									  #endif
									  PostMessage(  hMgr,  WM_CLOSE,  0,  0  );
								  }
							  }
						  }
					  }
				}
			}
		}
	}


	//
	bRet  =  TRUE;
		
errLabel:

	//
	traceLogA(  "CDlgTalk(  )::bQuitDlg leaves"  );
	//  2012/05/25
	if  (  pProcInfo->cfg.debugStatusInfo.ucbShowDlgTalkStatus  )  {
		qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dlgTalk_bQuitDlg %I64u, %d leaves"  ),  tmp_idInfo.ui64Id,  tmp_uiTranNo_shadow  ); 
	}
	
	//
	M_syncFlg_bQuitDlg_end
		
	return  bRet;
}


 void  dlgTalk_PostNcDestroy(  void  **  ppDlgTalkParam  )
{
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return;

	if  (  !ppDlgTalkParam  ||  !*ppDlgTalkParam  )  return;

	MACRO_CDlgTalk	*	pDlgTalk	=	(  MACRO_CDlgTalk  *  )*ppDlgTalkParam;
	DLG_TALK_var	&	m_var		=	pDlgTalk->m_var;


#if  0
	#ifdef  __DEBUG__
			traceLogA(  "PostNcDestroy: exit gpsQ"  );
	#endif
	if  (  m_var.ucbGpsQ2Inited  )  exitQyQ2(  &m_var.m_gpsQ2  );
#endif

	#ifdef  __DEBUG__
			traceLogA(  "PostNcDestroy: exit processQ"  );
	#endif
#if  0
	if  (  m_var.bProcessQInited  )  exitGenericQ(  &m_var.m_processQ  );	//  ÒòÎªprocessQ¹ØÏµµ½ÆäËûµÄ´°¿ÚÒª·¢ÏûÏ¢¹ýÀ´¡£ËùÒÔ£¬Ó¦¸ÃÔÚdestroyÖ®ºó£¬ÔÙÇå³ý¶ÓÁÐ¡£
#endif
	if  (  m_var.m_pProcessQ  )  genericQFree(  m_var.m_pProcessQ  );


	//
	if  (  m_var.m_pHtmlEdit_input  )  {  delete  m_var.m_pHtmlEdit_input;  m_var.m_pHtmlEdit_input  =  NULL;	}
	if  (  m_var.m_pHtmlEdit_recentMsgList  )  {  delete  m_var.m_pHtmlEdit_recentMsgList;  m_var.m_pHtmlEdit_recentMsgList  =  NULL;	}

	//  2012/04/24
	pFuncs->pf_TALKER_shadow_free(  isTalkerShadowMgr(  m_var.addr  ),  m_var.pShadowInfo  );

	//  2012/05/08
	exitCapSubWnds(  &m_var.subWnds  );

	//
	if  (  !m_var.guiData.bCreated  )  traceLogA(  "DlgTalk::PostNcDestroy(  ): don't need delete"  );

	if  (  m_var.guiData.bCreated  )  {

		#ifdef  __DEBUG__
				traceLog(  _T(  "DlgTalk::PostNcDestroy(  ): delete this, %I64u"  ),  m_var.addr.idInfo.ui64Id  );
		#endif

		//
		try  {
			 delete  pDlgTalk;  *ppDlgTalkParam  =  NULL;		
			}
#ifndef  __WINCE__
		catch  (  CException  *  e  )  {
			   e->Delete(  );
			   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::PostNcDestroy failed."  )  );
		}
#endif
		catch  (  ...  )  {
			   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::PostNcDestroy failed."  )  );
		}
	}

	#if  1	//  def  __SUPPORT_dlgWalls__	
			MC_VAR_isCli			*		pProcInfo	=	QY_GET_procInfo_isCli(  );
			if  (  pProcInfo  )  {
				PostMessage(  pProcInfo->g_hVWall,  WM_COMMAND,  MAKEWPARAM(  ID_applyForChkingWalls,  0  ),  0  );
			}		 
	#endif
	qisApplyForChkingTasks_gui(  );	//  2009/09/10

	traceLogA(  "DlgTalk::PostNcDestroy(  ) leaves"  );

}

 
 int  tmpHandler_findTalker(  void  *  p0,  void  *  pCommonParam1Param,  void  *  pQElem  )
{
	 int					iRet				=	-1;
	 //  p0;
	 COMMON_PARAM		*	pCommonParam1		=	(  COMMON_PARAM  *  )pCommonParam1Param;
	 //
	 MSGR_ADDR			*	pAddr				=	(  MSGR_ADDR  *  )pCommonParam1->p0;
	 unsigned  int			unused				=	(  unsigned  int  )pCommonParam1->p1;
	 //  pCommonParam1->p2;
	 //  
	 MIS_MSGU			*	pMsg				=	(  MIS_MSGU  *  )pQElem;
	 //
	 BOOL					bMatched			=	FALSE;

	 if  (  pMsg->uiType  ==  CONST_misMsgType_talkingFriend_qmc  )  {
		 
		 //
		 if  (  !lstrcmpi(  pAddr->misServName,  pMsg->talkingFriend_qmc.addr.misServName  )  )  {

			 //  2012/04/23
			 if  (  pAddr->uiTranNo_shadow  !=  pMsg->talkingFriend_qmc.addr.uiTranNo_shadow  )  {
				 iRet  =  0;  goto  errLabel;
			 }

			 //
			 switch  (  pAddr->uiObjType  )  {
					 case  CONST_objType_phoneGuest:
						   if  (  pAddr->uiDevType  ==  pMsg->talkingFriend_qmc.addr.uiDevType  
							   &&  !wcsicmp(  pAddr->wDevIdStr,  pMsg->talkingFriend_qmc.addr.wDevIdStr  )
								   &&  !wcsicmp(  pAddr->wPath,  pMsg->talkingFriend_qmc.addr.wPath  )  )  bMatched  =  TRUE;
						   break;
					 case  CONST_objType_tmpGrp:  
						   if  (  pAddr->uiDevType  ==  pMsg->talkingFriend_qmc.addr.uiDevType  
							   &&  !wcsicmp(  pAddr->wDevIdStr,  pMsg->talkingFriend_qmc.addr.wDevIdStr  )
								   &&  !wcsicmp(  pAddr->wPath,  pMsg->talkingFriend_qmc.addr.wPath  )  
									   &&  (  void  *  )pAddr->tStartTime_notice  ==  (  void  *  )pMsg->talkingFriend_qmc.addr.tStartTime_notice  
										   &&  pAddr->uiTranNo_notice  ==  pMsg->talkingFriend_qmc.addr.uiTranNo_notice  )  bMatched  =  TRUE;
						   break;
					 default:
						     if  (  pAddr->idInfo.ui64Id  ==  pMsg->talkingFriend_qmc.addr.idInfo.ui64Id  )  bMatched  =  TRUE;
							 break;
			 }
			 if  (  bMatched  )  {
			 	 pCommonParam1->p2  =  (  void  *  )pMsg->talkingFriend_qmc.hWnd;
			 	 iRet  =  1;	goto  errLabel;
		 	 }
		 }
	 
	 }

	 iRet  =  0;
errLabel:
	 return  iRet;
}


 __declspec(  dllexport  )  int  findTalker(  void  *  pQyMcParam,  MSGR_ADDR  *  pAddr,  unsigned  int  unused,  HWND  *  phWnd  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int						iErr								=	-1;
	 QY_MC					*	pQyMc								=	(  QY_MC  *  )pQyMcParam;
	 COMMON_PARAM				commonParam1;
	 MIS_CNT				*	pMisCnt								=	NULL;
	 int						iRet;
	 HWND						hWnd								=	NULL;

	 if  (  !pAddr  )  return  -1;

	 //  2012/04/23
	 assert(  !pAddr->uiTranNo_shadow  );

	 //
	 if  (  !(  pMisCnt  =  getMisCntByName(  pQyMc,  NULL,  pAddr->misServName  )  )  )  goto  errLabel;

	 MACRO_makeCommonParam3(  (  void  *  )pAddr,  (  void  *  )unused,  0,  commonParam1  );
	 iRet  =  qTraverse(  &pMisCnt->talkingFriendQ,  tmpHandler_findTalker,  0,  &commonParam1  );
	 if  (  iRet  <=  0  )  goto  errLabel;
	 hWnd  =  (  HWND  )commonParam1.p2;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 if  (  phWnd  )  *phWnd  =  hWnd;
	 }
	 return  iErr;
 }


  int  tmpHandler_findTalker_simple(  void  *  p0,  void  *  pCommonParam1Param,  void  *  pQElem  )
{
	 int					iRet				=	-1;
	 //  p0;
	 COMMON_PARAM		*	pCommonParam1		=	(  COMMON_PARAM  *  )pCommonParam1Param;
	 //
	 TCHAR				*	misServName			=	(  TCHAR  *  )pCommonParam1->p0;
	 QY_MESSENGER_ID	*	pIdInfo				=	(  QY_MESSENGER_ID  *  )pCommonParam1->p1;
	 //  pCommonParam1->p2;
	 //  
	 MIS_MSGU			*	pMsg				=	(  MIS_MSGU  *  )pQElem;
	 //
	 BOOL					bMatched			=	FALSE;

	 if  (  pMsg->uiType  ==  CONST_misMsgType_talkingFriend_qmc  )  {
		 
		 //
		 if  (  !lstrcmpi(  misServName,  pMsg->talkingFriend_qmc.addr.misServName  )  )  {

			 //  2012/04/23. 这里只需要找主窗口,所以把影子窗口略过
			 if  (  !isTalkerShadowMgr(  pMsg->talkingFriend_qmc.addr  )  )  {
				 iRet  =  0;  goto  errLabel;
			 }

			 //
			 if  (  pIdInfo->ui64Id  ==  pMsg->talkingFriend_qmc.addr.idInfo.ui64Id  )  bMatched  =  TRUE;
		 }

		 if  (  bMatched  )  {
			 pCommonParam1->p2  =  (  void  *  )pMsg->talkingFriend_qmc.hWnd;
			 iRet  =  1;	goto  errLabel;
		 }
	 }

	 iRet  =  0;
errLabel:
	 return  iRet;
}


 __declspec(  dllexport  )  int  findTalker(  void  *  pQyMcParam,  void  *  pMisCntParam,  QY_MESSENGER_ID  *  pIdInfo,  HWND  *  phWnd  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int						iErr								=	-1;
	 QY_MC					*	pQyMc								=	(  QY_MC  *  )pQyMcParam;
	 MIS_CNT				*	pMisCnt								=	(  MIS_CNT  *  )pMisCntParam;
	 COMMON_PARAM				commonParam1;
	 int						iRet;
	 HWND						hWnd								=	NULL;

	 if  (  !pMisCnt  ||  !pIdInfo  ||  !pIdInfo->ui64Id  )  return  -1;

	 MACRO_makeCommonParam3(  (  void  *  )pMisCnt->cfg.misServName,  (  void  *  )pIdInfo,  0,  commonParam1  );
	 iRet  =  qTraverse(  &pMisCnt->talkingFriendQ,  tmpHandler_findTalker_simple,  0,  &commonParam1  );
	 if  (  iRet  <=  0  )  goto  errLabel;
	 hWnd  =  (  HWND  )commonParam1.p2;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 if  (  phWnd  )  *phWnd  =  hWnd;
	 }
	 return  iErr;
}


 __declspec(  dllexport  )  int  removeTalker(  void  *  pQyMcParam,  MSGR_ADDR  *  pAddr,  unsigned  int  unused  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	MIS_CNT	*	pMisCnt	=  getMisCntByName(  (  QY_MC  *  )pQyMcParam,  NULL,  pAddr->misServName  );
	if  (  !pMisCnt  )  return  -1;
	COMMON_PARAM	commonParam1;
	MACRO_makeCommonParam3(  (  void  *  )pAddr,  (  void  *  )unused,  0,  commonParam1  );

	qRemoveMsg(  &pMisCnt->talkingFriendQ,  tmpHandler_findTalker,  NULL,  &commonParam1  );  

	return  0;
}


   //  
 __declspec(  dllexport  )  int  talkToMessenger(  void  *  pQyMcParam,  MSGR_ADDR  *  pAddr,  GENERIC_Q  *  pTmpGrpMemQ,  BOOL  bNeedNotShowWnd,  BOOL  bActivateWnd,  HWND  *  phWnd  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int						iErr								=	-1;
	 QY_MC					*	pQyMc								=	(  QY_MC  *  )pQyMcParam;
	 RECT						rect;
	 COMMON_PARAM				commonParam1;
	 MIS_CNT				*	pMisCnt								=	NULL;
	 MC_VAR_isCli			*	pProcInfo							=	NULL;
	 HWND						hWnd								=	NULL;
	 int						iRet;
	 HWND						hFore								=	NULL;
 	 HWND						hParent								=	NULL;

	 MACRO_CDlgTalk			*	pDlgTalk							=	NULL;

	 int						nStep								=	0;

	 if  (  !pAddr  )  return  -1;

	 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "talkToMessenger enters %I64u, %d"  ),  pAddr->idInfo.ui64Id,  pAddr->uiTranNo_shadow  );

	 if  (  !(  pMisCnt  =  getMisCntByName(  pQyMc,  NULL,  pAddr->misServName  )  )  )  {
		 nStep  =  10;
		 goto  errLabel;
	 }
	 pProcInfo  =  (  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;

	 	//  2011/03/01
#ifdef  __SUPPORT_dlgWalls__
		//  viewWalls(  );
#endif


	 MACRO_makeCommonParam3(  (  void  *  )pAddr,  (  void  *  )0,  (  void  *  )0,  commonParam1  );
	 //
	 iRet  =  qTraverse(  &pMisCnt->talkingFriendQ,  tmpHandler_findTalker,  0,  &commonParam1  );  
	 if  (  iRet  <  0  )  {
		 nStep  =  20;
		 goto  errLabel;
		 }
	 else  if  (  iRet  >  0  )  {			
			   hWnd  =  (  HWND  )commonParam1.p2;
			   //
			   if  (  isTalkerShadowMgr(  *pAddr  )  )  {
				   //  2012/04/30. 如果有其他的影子窗口可以接收输入,那么就不把主窗口显示出来
				   DLG_TALK_var	*	pVar  =  (  DLG_TALK_var	*	)getDlgTalkVar(  hWnd  );
				   if  (  !pVar  )  {
					   nStep  =  30;
					   goto  errLabel;
				   }
				   TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pVar->pShadowInfo;
				   if  (  !pShadowMgr  )  {
					   nStep  =  40;
					   goto  errLabel;
				   }
				   int  i;
				   for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
					    if  (  IsWindow(  pShadowMgr->shadows[i].hShadow  )
							&&  isTalkerSubType_canInput(  pShadowMgr->shadows[i].iTalkerSubType  )  )
						{
							break;
						}
				   }
				   if  (  i  <  mycountof(  pShadowMgr->shadows  )  )  {
					   if  (  bActivateWnd  )  {
						   PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_setActiveWindow,  (  LPARAM  )pShadowMgr->shadows[i].hShadow  );
					   }
					   iErr  =  0;  goto  errLabel;
				   }
			   }
			   //
			   if  (  !bNeedNotShowWnd  )  {			 
				   DLG_TALK_var	*	pVar  =  (  DLG_TALK_var	*	)getDlgTalkVar(  hWnd  );
				   if  (  !pVar  )  {
					   nStep  =  60;
					   goto  errLabel;
				   }
				   if  (  pVar->guiData.param.bNeedNotShowWnd  )  pVar->guiData.param.bNeedNotShowWnd  =  FALSE;

				   //  ShowWindow(  hWnd,  SW_SHOWNOACTIVATE    );
				   ShowWindow(  hWnd,  SW_SHOWNA  );
			   }

			   if  (  bActivateWnd  )  {
				   PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_setActiveWindow,  (  LPARAM  )hWnd  );
			   }

			   iErr  =  0;  goto  errLabel;
			   
			   //
			   }
	 else  {
		   if  (  pAddr->uiTranNo_shadow  )  {	//  对辅助窗口,不可以在这里建立. 2012/04/22
			   #ifdef  __DEBUG__
					   traceLog(  _T(  "talkToMessenger failed, primary talker doesn't exists"  )  );
			   #endif
			   nStep  =  70;
			   goto  errLabel;
		   }
	 }


	 memset(  &rect,  0,  sizeof(  rect  )  );
	 
	 if  (  !bActivateWnd  )  {		//
         hFore  =  GetForegroundWindow(  );
	 }

		

#ifndef  __WINCE__
		 if  (  bApp_ts(  )  )  {  //  #ifdef  __APP_qyMc_touchscreen__  		//  2012/05/12
				 if  (  IsWindow(  pProcInfo->g_hVWall  )  )  {
					 hParent  =  pProcInfo->g_hVWall;
					 }
				 else 
					 hParent	=	::GetDesktopWindow(  );		 
		 }	//  #endif
		 
		 pDlgTalk  =  new  MACRO_CDlgTalk(  hParent  );
		 if  (  !pDlgTalk  )  {
			 nStep  =  80;
			 goto  errLabel;
		 }

		 //  if  (  !pDlgTalk->bSetDlgInfo(  0,  pAddr,  pTmpGrpMemQ,  bNeedNotShowWnd,  hFore  )  )  goto  errLabel;
		 if  (  !dlgTalk_bSetDlgInfo(  pDlgTalk->m_hWnd,  pDlgTalk->m_var,  pAddr,  pTmpGrpMemQ,  0,  bNeedNotShowWnd,  hFore  )  )  {
			 nStep  =  90;
			 goto  errLabel;
		 }

		 if  (  !pDlgTalk->Create(  rect  )  )  {
			 nStep  =  100;
			 goto  errLabel;
		 }

#else

	 G_guiData_qyMc			*	pGuiData							=	(  G_guiData_qyMc  *  )get_g_guiData(  );
	 PF_commonHandler			pf_newDlgTalk_ce					=	(  PF_commonHandler  )pGuiData->pf_newDlgTalk_ce;
	 if  (  !pf_newDlgTalk_ce  )  goto  errLabel;
	 
	 DLG_guiDataParam_talk			guiDataParam;
	 memset(  &guiDataParam,  0,  sizeof(  guiDataParam  )  );
	 guiDataParam.iDlgType  =  0;
	 guiDataParam.pAddr  =  pAddr;
	 guiDataParam.pTmpGrpMemQ  =  pTmpGrpMemQ;
	 guiDataParam.bNeedNotShowWnd  =  bNeedNotShowWnd;
	 guiDataParam.hFore  =  hFore;

	 hParent	=	pQyMc->gui.hMainWnd;	//  GetDesktopWindow(  );

	 pDlgTalk  =  (  CDlgTalk_ce  *  )pf_newDlgTalk_ce(  pQyMc->g_hInst,  hParent,  &guiDataParam  );
	 if  (  !pDlgTalk  )  goto  errLabel;

#endif 

	 //  
	 hWnd  =  pDlgTalk->m_hWnd;

	 if  (  !bNeedNotShowWnd  )  {		
		 #ifndef  __WINCE__
				 if  (  hFore  )  ::SetWindowPos(  pDlgTalk->m_hWnd,  HWND_BOTTOM,  0,  0,  0,  0,  SWP_NOSIZE  |  SWP_NOMOVE  |  SWP_NOACTIVATE  |  SWP_SHOWWINDOW  );
				 else  ShowWindow(  pDlgTalk->m_hWnd,  SW_SHOW  );
		 #else
				 if  (  hFore  )  {
					 //  ShowWindow(  pDlgTalk->m_hWnd,  SW_SHOWNOACTIVATE    );				
					 ShowWindow(  pDlgTalk->m_hWnd,  SW_SHOWNA    );				
					 }
			  else  
				  ShowWindow(  pDlgTalk->m_hWnd,  SW_SHOW  );
		 #endif
	 }

	 if  (  bActivateWnd  )  {	 
		 PostMessage(  g_pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_setActiveWindow,  (  LPARAM  )hWnd  );
	 }

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
		 #ifndef  __WINCE__
				  if  (  pDlgTalk  )  delete  pDlgTalk;
		 #else
				  if  (  pDlgTalk  )  freeQyWnd(  pDlgTalk  );
		 #endif
	 }
	 if  (  !iErr  )  {
		 if  (  bActivateWnd  )  {
			 #ifndef  __WINCE__
					  if  (  IsIconic(  hWnd  )  )  SendMessage(  hWnd,  WM_SYSCOMMAND,  SC_RESTORE,  0  );
			 #endif
		 }
		 if  (  phWnd  )  *phWnd  =  hWnd;
	 }

	 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "talkToMessenger called %s, nStep %d"  ),  iErr  ?  _T(  "failed"  )  :  _T(  "OK"  ),  nStep  );
	 
	 return  0;

}


__declspec(  dllexport  )  int  getTalkerShadow(  HWND  hParent,  MSGR_ADDR  *  pAddr,  GENERIC_Q  *  pTmpGrpMemQ,  int  iTalkerSubType,  BOOL  bNeedNotShowWnd,  BOOL  bActivateWnd,  HWND  *  phWnd  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int						iErr								=	-1;
	 QY_MC					*	pQyMc								=	QY_GET_GBUF(  );
	 RECT						rect;
	 COMMON_PARAM				commonParam1;
	 MIS_CNT				*	pMisCnt								=	NULL;
	 MC_VAR_isCli			*	pProcInfo							=	NULL;
	 HWND						hWnd								=	NULL;
	 int						iRet;
	 HWND						hFore								=	NULL;

	 MACRO_CDlgTalk			*	pDlgTalk							=	NULL;

	 int						nStep								=	0;

	 if  (  !pAddr  )  return  -1;

	 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "getTalkerShadow enters, %I64u, %d"  ),  pAddr->idInfo.ui64Id,  pAddr->uiTranNo_shadow  );
	 	 

	 if  (  !(  pMisCnt  =  getMisCntByName(  pQyMc,  NULL,  pAddr->misServName  )  )  )  {
		 nStep  =  10;
		 goto  errLabel;
	 }
	 pProcInfo  =  (  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;


	 if  (  !pAddr->uiTranNo_shadow  )  {	//  此函数不能用于建主窗口. 2012/04/22
	     #ifdef  __DEBUG__
			   traceLog(  _T(  "getTalkerShadow failed, iParam is 0"  )  );
		 #endif
	     nStep  =  15;
	     goto  errLabel;
	 }


	 //  BOOL	bNeedNotShowWnd		=	TRUE;

	 memset(  &rect,  0,  sizeof(  rect  )  );
	 
	 pDlgTalk  =  new  MACRO_CDlgTalk(  hParent  );
	 if  (  !pDlgTalk  )  {
		 nStep  =  80;
		 goto  errLabel;
	 }

	 //  if  (  !pDlgTalk->bSetDlgInfo(  0,  pAddr,  pTmpGrpMemQ,  bNeedNotShowWnd,  hFore  )  )  goto  errLabel;
	 if  (  !dlgTalk_bSetDlgInfo(  pDlgTalk->m_hWnd,  pDlgTalk->m_var,  pAddr,  pTmpGrpMemQ,  iTalkerSubType,  bNeedNotShowWnd,  hFore  )  )  {
		 nStep  =  90;
		 goto  errLabel;
	 }

	 if  (  !pDlgTalk->Create(  rect  )  )  {
		 nStep  =  100;
		 goto  errLabel;
	 }


	 //  
	 hWnd  =  pDlgTalk->m_hWnd;

	 if  (  !bNeedNotShowWnd  )  {		
		 #ifndef  __WINCE__
				 if  (  hFore  )  ::SetWindowPos(  pDlgTalk->m_hWnd,  HWND_BOTTOM,  0,  0,  0,  0,  SWP_NOSIZE  |  SWP_NOMOVE  |  SWP_NOACTIVATE  |  SWP_SHOWWINDOW  );
				 else  ShowWindow(  pDlgTalk->m_hWnd,  SW_SHOW  );
		 #else
				 if  (  hFore  )  {
					 //  ShowWindow(  pDlgTalk->m_hWnd,  SW_SHOWNOACTIVATE    );				
					 ShowWindow(  pDlgTalk->m_hWnd,  SW_SHOWNA    );				
					 }
			  else  
				  ShowWindow(  pDlgTalk->m_hWnd,  SW_SHOW  );
		 #endif
	 }

	 if  (  bActivateWnd  )  {	 
		 PostMessage(  g_pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_setActiveWindow,  (  LPARAM  )hWnd  );
	 }

	 iErr  =  0;

errLabel:

	 if  (  iErr  )  {
		 #ifndef  __WINCE__
				  if  (  pDlgTalk  )  delete  pDlgTalk;
		 #else
				  if  (  pDlgTalk  )  freeQyWnd(  pDlgTalk  );
		 #endif
	 }
	 if  (  !iErr  )  {
 		 if  (  bActivateWnd  )  {
			 #ifndef  __WINCE__
					  if  (  IsIconic(  hWnd  )  )  SendMessage(  hWnd,  WM_SYSCOMMAND,  SC_RESTORE,  0  );
			 #endif
		 }
		 if  (  phWnd  )  *phWnd  =  hWnd;
	 }

	 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "getTalkerShadow called %s, nStep %d"  ),  iErr  ?  _T(  "failed"  )  :  _T(  "OK"  ),  nStep  );
	 
	 return  0;

}


 int  procTalkTo(  HWND  hDlgTalk,  LPCTSTR  inputStr  )
{
	int						iErr				=	-1;
	QY_MC				*	pQyMc				=	QY_GET_GBUF(  );
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return  -1;
	CQyString				str;
	TCHAR					txtContent[1024];			
	BOOL					bNothing			=	FALSE;
	MIS_CNT				*	pMisCnt				=	NULL;
	MC_VAR_isCli			*	pProcInfo			=	NULL;
	TCHAR				*	pT					=	NULL;
	TCHAR					tBuf[255  +  1]		=	_T(  ""  );
	char					buf[255  +  1]		=	"";
	if  (  !hDlgTalk  )  return  -1;
	DLG_TALK_var		&	m_var				=	*(  DLG_TALK_var	*	)getDlgTalkVar(  hDlgTalk  );

	CQyMalloc				mallocObj_pMsgBuf;
	MIS_MSGU			*	pMsgBuf				=	(  MIS_MSGU  *  )mallocObj_pMsgBuf.malloc(  sizeof(  MIS_MSGU  )  );
	if  (  !pMsgBuf  )  return  -1;

	HWND					hMgr				=	hDlgTalk;
	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  {
		TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )m_var.pShadowInfo;
		if  (  !pShadow  )  goto  errLabel;
		hMgr  =  pShadow->hMgr;		
	}
	if  (  !IsWindow(  hMgr  )  )  goto  errLabel;
	
	//
	if  (  !(  pMisCnt  =  m_var.pMisCnt  )  )  goto  errLabel;
	if  (  !(  pProcInfo  =  (  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam  )  )  goto  errLabel;
	//
#ifdef  __SUPPORT_HTMLEDIT__
	IHTMLDocument2		*	pDoc				=	NULL;
	IHTMLElement		*	pBody				=	NULL;
	if  (  !m_var.m_pHtmlEdit_input->GetDHtmlDocument(  &pDoc  )  )  goto  errLabel;

	if  (  SUCCEEDED(  pDoc->get_body(  &pBody  )  )  )  {
		BSTR  bstr  =  NULL;
		if  (  SUCCEEDED(  pBody->get_innerText(  &bstr  )  )  )  {
			str  =  bstr;
			SysFreeString(  bstr  );
		}
		//  MACRO_CStringTrim(  str  );
		str.Trim(  );
		if  (  !str.GetLength(  )  )  bNothing  =  TRUE;
		
		if  (  !m_var.addr.bInNoticeMode  )  {	//  
			if  (  SUCCEEDED(  pBody->get_innerHTML(  &bstr  )  )  )  {
				str  =  bstr;
				SysFreeString(  bstr  );
			}
		}

		pBody->Release(  );
	}
#else
	if  (  !inputStr  )  goto  errLabel;
	str  =  inputStr;
	str.Trim(  );
	if  (  !str[0]  )  bNothing  =  TRUE;
#endif
	 
	if  (  bNothing  )  {
		traceLogA(  "procTalkTo failed: nothing input"  );  goto  errLabel;
	}

	if  (  m_var.addr.bInNoticeMode  )  {
		#ifndef  __WINCE__
				 if  (  myMessageBox(  hDlgTalk,  CQyString(  "Whether to send \""  )  +  str  +  _T(  "\""  ),  _T(  ""  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
		#else
				traceLog(  _T(  "Not supported in ce"  )  );
				goto  errLabel;
		#endif
	}

#ifdef  __SUPPORT_HTMLEDIT__
		#ifdef  __DEBUG__
				printHtmlEdit(  m_var.m_pHtmlEdit_input  );
		#endif
#endif


#if  0

//	
	txtContent[0]  =  0;
	addToRecentMsg(  hDlgTalk,  &m_var,  -1,  0,  &m_var.pMisCnt->idInfo,  NULL,  CONST_imOp_says,  0,  NULL,  NULL,  str,  FALSE,  TRUE,  txtContent,  mycountof(  txtContent  )  );
#ifdef  __SUPPORT_HTMLEDIT__
		#ifdef  __DEBUG__
				printHtmlEdit(  m_var.m_pHtmlEdit_recentMsgList  );
		#endif
#endif
	
	//  2012/04/30.如果是在放大影子窗口里输入,那么还需要把消息更新到主窗口
	if  (  !isTalkerShadowMgr(  m_var.addr  )  )  {
		TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )m_var.pShadowInfo;
		if  (  !pTalkerShadow  )  goto  errLabel;
		txtContent[0]  =  0;
		addToRecentMsg(  pTalkerShadow->hMgr,  getDlgTalkVar(  pTalkerShadow->hMgr  ),  -1,  0,  &m_var.pMisCnt->idInfo,  NULL,  CONST_imOp_says,  0,  NULL,  NULL,  str,  FALSE,  TRUE,  txtContent,  mycountof(  txtContent  )  );
	}
#endif


	//  Æä´ÎÔÙ·¢ÍùmgrÊ¹·¢ËÍ
	unsigned  char		ucFlg;
	IM_HTML_CONTENT		content;
	int					lenInBytes;
	//
	ucFlg  =  0;
	//
	memset(  &content,  0,  sizeof(  content  )  );
	content.uiType  =  CONST_imCommType_htmlContent;
	lstrcpyn(  content.wBuf,  str,  mycountof(  content.wBuf  )  );
	lenInBytes  =  offsetof(  IM_HTML_CONTENT,  wBuf  )  +  (  lstrlen(  content.wBuf  )  +  1  )  *  sizeof(  content.wBuf[0]  );
	//
	MSG_ROUTE	route;
	memset(  &route,  0,  sizeof(  route  )  );
	//
	route.idInfo_from.ui64Id  =  m_var.pMisCnt->idInfo.ui64Id;
	//
	if  (  !m_var.addr.wPath[0]  )  {
		route.idInfo_to.ui64Id  =  m_var.addr.idInfo.ui64Id;
		route.uiDevType_to  =  m_var.addr.uiDevType;
		safeWcsnCpy(  m_var.addr.wDevIdStr,  route.wDevIdStr_to,  mycountof(  route.wDevIdStr_to  )  );
		if  (  m_var.addr.wDevIdStr[0]  )  {
			traceLogA(  "procTalkTo: ÕâÀï£¬²»ÖªµÀÎªÊ²Ã´wDevIdStrÓÐÄÚÈÝ[%S]?",  m_var.addr.wDevIdStr  );
		}

		MACRO_prepareForTran(  );

		if  (  pFuncs->pf_postMsg2Mgr_mc(  m_var.pMisCnt,  &route,  CONST_misMsgType_talk,  ucFlg,  CONST_qyCmd_talkTo,  tStartTran,  uiTranNo,  0,  (  char  *  )&content,  lenInBytes,  &m_var.addr.idInfo,  &m_var.addr.idInfo,  0,  pMsgBuf,  TRUE  )  )  goto  errLabel;

		// 
		//  postImMsg2Log(  pMisCnt->cfg.misServName,  &pMisCnt->idInfo,  pMisCnt->talkerDesc,  tStartTran,  uiTranNo,  &m_var.addr.idInfo,  m_var.talkerDesc,  content.uiType,  str,  txtContent,  0,  &pProcInfo->schedulerQ  );    

		}
	else  {  //  ÕâÀï£¬Ó¦¸Ã£¬½«wPathÔÚwpathÀïÓÐÄÚÈÝÊ±£¬±íÃ÷£¬ÐèÒªÖ¸¶¨Â·¾¶·¢ËÍ¡£ÄÇÃ´£¬ÐèÒª½«¸ÃÄÚÈÝÈ¡³ö¡£²¢½«Ä¿µÄ¶ÔÏóÌîÈëwPathÖÐ
		  TCHAR	*	pStr;
		  //
		  ucFlg  =  CONST_commFlg_routeTalkData;
		  //
		  if  (  _tcschr(  m_var.addr.wPath,  _T(  '|'  )  )  )  {
			  traceLogA(  "procTalkTo: Ê§°Ü£ºÔÝÊ±Ö»Ö§³ÖÒ»´Î×ª·¢"  );  goto  errLabel;
		  }
		  //
		  if  (  !_tcsnicmp(  m_var.addr.wPath,  CONST_str_im,  lstrlen(  CONST_str_im  )  )  )  {
			  pT  =  m_var.addr.wPath  +  lstrlen(  CONST_str_im  );
			  if  (  *pT  !=  _T(  ':'  )  )  goto  errLabel;
			  pT  ++  ;
			  pStr  =  _T(  "//"  );
			  if  (  _tcsnicmp(  pT,  pStr,  lstrlen(  pStr  )  )  )  goto  errLabel;
			  pT  =  pT  +  lstrlen(  pStr  );
			  //
			  if  (  !(  pT  =  _tcschr(  pT,  _T(  '/'  )  )  )  )  goto  errLabel;
			  pT  ++  ;
			  safeWcsnCpy(  pT,  tBuf,  mycountof(  tBuf  )  );
			  if  (  !(  pT  =  _tcschr(  tBuf,  _T(  '/'  )  )  )  )  goto  errLabel;
			  *pT  =  0;
			  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &route.idInfo_to  );
			  pT  ++  ;
			  safeWcsnCpy(  pT,  route.wDevIdStr_to,  mycountof(  route.wDevIdStr_to  )  );
			  tTrim(  route.wDevIdStr_to  );
			  //
			  route.uiDevType_to  =  CONST_objType_dev;
			  //  

			}
		  else  {
			    traceLogA(  "procTalkTo:  Ê§°Ü£ºÔÝÊ±Ö»´¦ÀíimµÄÇé¿ö"  );  goto  errLabel;
		  }	

		  switch  (  m_var.addr.uiObjType  )  {
				  case  CONST_objType_tmpGrp:
			      	    Q_NODE  *  pQNode;
						MSGR_ADDR  *  pMem;
						//		
						for  (  pQNode  =  m_var.tmpGrpMemQ.front.pNext;  pQNode;  pQNode  =  pQNode->pNext  )  {
							 pMem  =  (  MSGR_ADDR  *  )pQNode->qElemMemory.m_pBuf;
							 switch  (  pMem->uiObjType  )  {
									 case  CONST_objType_messenger:
										   _sntprintf(  route.wForwardPath,  mycountof(  route.wForwardPath  ),  _T(  "%s://%s/%I64u/%s"  ),  CONST_str_im,  m_var.addr.misServName,  pMem->idInfo.ui64Id,  CONST_str_phone  );		
										   break;
									 default:
										    _sntprintf(  route.wForwardPath,  mycountof(  route.wForwardPath  ),  _T(  "%s:%s"  ),  CONST_str_phone,  pMem->wDevIdStr  );		
										    break;					
							 }

							 MACRO_prepareForTran(  );
	
						 	 if  (  pFuncs->pf_postMsg2Mgr_mc(  m_var.pMisCnt,  &route,  CONST_misMsgType_talk,  ucFlg,  CONST_qyCmd_talkTo,  tStartTran,  uiTranNo,  0,  (  char  *  )&content,  lenInBytes,  &m_var.addr.idInfo,  NULL,  0,  pMsgBuf,  TRUE  )  )  goto  errLabel;

							 // 
							 //  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  pMem->displayName,  pMem->wDevIdStr  );
							 //  postImMsg2Log(  pMisCnt->cfg.misServName,  &pMisCnt->idInfo,  pMisCnt->talkerDesc,  tStartTran,  uiTranNo,  &m_var.addr.idInfo,  tBuf,  content.uiType,  str,  txtContent,  0,  &pProcInfo->schedulerQ  );    
						}
						//
						break;
				  case  CONST_objType_phoneGuest:
				  default:
					    if  (  !m_var.addr.idInfo.ui64Id  )  _sntprintf(  route.wForwardPath,  mycountof(  route.wForwardPath  ),  _T(  "%s:%s"  ),  CONST_str_phone,  m_var.addr.wDevIdStr  );		
						else  _sntprintf(  route.wForwardPath,  mycountof(  route.wForwardPath  ),  _T(  "%s://%s/%I64u/%s"  ),  CONST_str_im,  m_var.addr.misServName,  m_var.addr.idInfo.ui64Id,  CONST_str_phone  );
	
						MACRO_prepareForTran(  );
	
						if  (  pFuncs->pf_postMsg2Mgr_mc(  m_var.pMisCnt,  &route,  CONST_misMsgType_talk,  ucFlg,  CONST_qyCmd_talkTo,  tStartTran,  uiTranNo,  0,  (  char  *  )&content,  lenInBytes,  &m_var.addr.idInfo,  NULL,  0,  pMsgBuf,  TRUE  )  )  goto  errLabel;

						// 
						//  postImMsg2Log(  pMisCnt->cfg.misServName,  &pMisCnt->idInfo,  pMisCnt->talkerDesc,  tStartTran,  uiTranNo,  &m_var.addr.idInfo,  m_var.talkerDesc,  content.uiType,  str,  txtContent,  0,  &pProcInfo->schedulerQ  );    

						break;
		  }

	}

	pFuncs->pf_dlgTalk_qPostMsg(  hMgr,  pMsgBuf,  sizeof(  MIS_MSGU  )  );
	PostMessage(  hMgr,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );


	//  ½«ÏÂÃæµÄinputÊäÈëÇå¿Õ
#ifdef  __SUPPORT_HTMLEDIT__
	if  (  m_var.m_pHtmlEdit_input->GetDHtmlDocument(  &pDoc  )  )  {
		if  (  SUCCEEDED(  pDoc->get_body(  &pBody  )  )  )  {
			BSTR  bstr  =  NULL;
			//  str  =  CString(  ""  );
			//  bstr  =  str.AllocSysString(  );
			bstr  =  SysAllocString(  _T(  ""  )  );
			if  (  bstr  )  {
				pBody->put_innerHTML(  bstr  );
				SysFreeString(  bstr  );
			}
			pBody->Release(  );
		}		
	}
#else
	//  SetDlgItemText(  hDlgTalk,  m_var.guiData.iIDC_EDIT_input,  _T(  ""  )  );
#endif

	iErr  =  0;

errLabel:
	return  iErr;
}

 __declspec(  dllexport  )  int  dlgTalk_OnQyPostComm_idcInited(  HWND  hDlg,  void  *  pDLG_TALK_var,  UINT  wParam,  LONG  lParam  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int	iErr	=	-1;
	FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return  -1;


	if  (  !pDLG_TALK_var  )  return  -1;
	DLG_TALK_var  &  m_var  =  *(  DLG_TALK_var  *  )pDLG_TALK_var;

	
				  #ifdef  __SUPPORT_HTMLEDIT__
						   CString				strInfo;
						   IHTMLDocument2  *	pDoc			=	NULL  ; // Declared earlier in the code
						   CMyHtmlEditCtrl  *  pEditCtrl	=	NULL;
						   
						   //  2012/05/17
						   if  (  !m_var.m_pHtmlEdit_input  ||  !m_var.m_pHtmlEdit_recentMsgList  )  {
							   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::postComm: idcInited, failed, htmlEdit_input or recentMsgList is null."  )  );
							   goto  errLabel;
						   }

						   //
						   if  (  m_var.m_pHtmlEdit_input->m_hWnd  ==  (  HWND  )lParam  )  {
							   pEditCtrl  =  m_var.m_pHtmlEdit_input;
				  
							   strInfo  =  CString(  CONST_html_input  );			  						
							   }
						   else  if  (  m_var.m_pHtmlEdit_recentMsgList->m_hWnd  ==  (  HWND  )lParam  )  {
							         pEditCtrl  =  m_var.m_pHtmlEdit_recentMsgList;
					  	
									 strInfo  =  CString(  CONST_html_recentMsgList  );
									 }
						   else  {
							     traceLogA(  "CDlgTalk::OnQyPostComm(  ): µÃµ½²»Æ¥ÅäµÄ¿Ø¼þ¾ä±ú"  );
								 goto  errLabel;
						   }

						   if  (  !pEditCtrl->GetDHtmlDocument(  &pDoc  )  ||  !pDoc  )  goto  errLabel;					
					
						   if  (  initHtmlDisplay(  pDoc,  strInfo  )  )  goto  errLabel;

						   pEditCtrl->m_bDisplayInited  =  TRUE;

						   if  (  m_var.m_pHtmlEdit_recentMsgList->m_bDisplayInited  &&  m_var.m_pHtmlEdit_input->m_bDisplayInited  )  {

							   //  Èç¹û³õÊ¼»¯³ö´í£¬ÕâÀïÓ¦¸ÃÖ÷¶¯ÍË³ö
							   if  (  m_var.bInitFailed  )  {
								   //
								   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgTalk::postComm: bInitFailed, to close Window."  )  );
								   #ifdef  __DEBUG__
										   traceLog(  _T(  "CDlgTalk::postComm: bInitFailed, to close Window."  )  );								   
								   #endif

								   //  2012/05/17
								   PostMessage(  hDlg,  WM_CLOSE,  0,  0  );
								   goto  errLabel;
							   }

							   //  2008/11/14
							   m_var.guiData.bFinished_createCtrls  =  TRUE;

							   #ifndef  __WINCE__
										m_var.m_pHtmlEdit_input->SetFocus(  );	
							   #else
										SetForegroundWindow(  hDlg  );
							   #endif

							   //  
							   if  (  m_var.hFore  )  {		//  2007/09/09
								   ::SetForegroundWindow(  m_var.hFore  );  m_var.hFore  =  NULL;						
			  					   #if !defined(  __WINCE__  )  &&  !defined(  __APP_qyMc_touchscreen__  )			//  2010/09/08
											::SetWindowPos(  hDlg,  HWND_BOTTOM,  0,  0,  0,  0,  SWP_NOSIZE  |  SWP_NOMOVE  |  SWP_NOACTIVATE  );
								   #endif
							   }				  
						   }
		
						   //  if  (  m_var.m_pHtmlEdit_recentMsgList->m_hWnd  ==  (  HWND  )lParam  )  
						   if  (  m_var.guiData.bFinished_createCtrls  )
						   {
#if  0
							   
							   //  2012/05/14
							   if  (  !bReady_toShowMsg(  hDlg  )  )  goto  errLabel;

							   HWND  hMgr  =  hDlg;
							   if  (  !isTalkerShadowMgr(  m_var.addr  )  )  {
								   TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )m_var.pShadowInfo;
								   if  (  !pShadow  )  goto  errLabel;
								   hMgr  =  pShadow->hMgr;
							   }
							   DLG_TALK_var  *  pMgrVar  =  getDlgTalkVar(  hMgr  );
							   if  (  !pMgrVar  )  goto  errLabel;

							   //
							   param.bScrollIntoView  =  TRUE;													//  ÕâÀïÒª×¢Òâ£ºÒòÎª
							   param.bNewMsg  =  TRUE;		

							   //  if  (  !pMgrVar->guiData.bDone_init_showMsg  )  
							   {
								   qTraverse(  pMgrVar->m_pProcessQ, tmpHandler_showMsg,  hMgr,  &param  );				//  2007/08/13
								   //  pMgrVar->guiData.bDone_init_showMsg  =  TRUE;
								   }
							   //  else  
							   {
								     if  (  !isTalkerShadowMgr(  m_var.addr  )  )  {
										 if  (  isTalkerSubType_canInput(  m_var.iTalkerSubType  )  )  {										 
											 qTraverse(  pMgrVar->m_pProcessQ,  tmpHandler_shadow_displayMsg,  hDlg,  &param  );
										 }
									 }										 								   
							   }

							   if  (  m_var.ucbTaskIdSet  )  activateImTask(  hDlg,  m_var,  m_var.iTaskId_activated  );	//  2006/08/11
#endif
							   //  2012/05/17
							   pFuncs->pf_doSth_afterInitDlgTalk(  hDlg,  &m_var  );
						   }
						#endif

		iErr  =  0;

errLabel:

		return  iErr;

}


 __declspec(  dllexport  )  int  dlgTalk_OnInitDialog_createHtmlEdits(  HWND  hDlgTalk,  void  *  pDLG_TALK_var  )
 {
	 int	iErr	=	-1;

	 if  (  !pDLG_TALK_var  )  return  -1;
	 DLG_TALK_var  &  m_var  =  *(  DLG_TALK_var  *  )pDLG_TALK_var;
	 
	 int							idc;
	BOOL						tmpbRet;
	RECT						rect;


	 

		m_var.m_pHtmlEdit_input  =  new  CMyHtmlEditCtrl(  );
		if  (  !m_var.m_pHtmlEdit_input  )  goto  errLabel;
		m_var.m_pHtmlEdit_recentMsgList  =  new  CMyHtmlEditCtrl(  );
		if  (  !m_var.m_pHtmlEdit_recentMsgList  )  goto  errLabel;

		//
		idc  =  m_var.guiData.iIDC_STATIC_input;		//  
		//
		GetWindowRect(  GetDlgItem(  hDlgTalk,  idc  ),  &rect  );
		ScreenToClient(  hDlgTalk,  (  LPPOINT  )&rect  );
		//
		idc  =  IDC_htmlEdit_input;		//  
		m_var.m_pHtmlEdit_input->m_bDesignMode  =  TRUE;
		tmpbRet  =  m_var.m_pHtmlEdit_input->Create(  NULL,  WS_CHILD  |  WS_VISIBLE,  rect,  CWnd::FromHandle(  hDlgTalk  ),  idc,  NULL  );
		if  (  !tmpbRet  )  {
			traceLogA(  "m_htmlEdit_input create(  ) failed"  );
			goto  errLabel;
		}
		m_var.m_pHtmlEdit_input->m_uiType  =  CONST_htmlEditType_input;
		m_var.m_pHtmlEdit_input->m_dropTarget.Register(  m_var.m_pHtmlEdit_input  );
	
		idc  =  IDC_STATIC_recentMsgList;
		//
		GetWindowRect(  GetDlgItem(  hDlgTalk,  idc  ),  &rect  );
		ScreenToClient(  hDlgTalk,  (  LPPOINT  )&rect  );
		//  
		idc  =  IDC_htmlEdit_recentMsgList;
		m_var.m_pHtmlEdit_recentMsgList->m_bDesignMode  =  FALSE;
		tmpbRet  =  m_var.m_pHtmlEdit_recentMsgList->Create(  NULL,  WS_CHILD  |  WS_VISIBLE,  rect,  CWnd::FromHandle(  hDlgTalk  ),  idc,  NULL  );
		if  (  !tmpbRet  )  {
			traceLogA(  "m_htmlEdit_recentMsgList create(  ) failed"  );
			goto  errLabel;
		}
		m_var.m_pHtmlEdit_recentMsgList->m_uiType  =  CONST_htmlEditType_recentMsgList;
		m_var.m_pHtmlEdit_recentMsgList->m_dropTarget.Register(  m_var.m_pHtmlEdit_recentMsgList  );

		iErr  =  0;

errLabel:
		return  iErr;
 }


 __declspec(  dllexport  ) int  dlgTalk_OnQyComm_getDropTarget(  HWND  hDlg,  void  *  pDLG_TALK_var,  UINT  wParam,  LONG  lParam  )
 {
	 int	iErr	=	-1;

	 if  (  !pDLG_TALK_var  )  return  -1;
	 DLG_TALK_var  &  m_var  =  *(  DLG_TALK_var  *  )pDLG_TALK_var;
	 
	 QY_WMBUF_COMM	*	pComm			=	(  QY_WMBUF_COMM  *  )lParam;

	 		//  ÕâÀïÊôÓÚ³õÊ¼»¯µÄ¹¤×÷£¬²»ÄÜµÈ¶Ô»°´°¿Ú¶¼³õÊ¼»¯ÍêÁË¡£
				  LPDROPTARGET  pMyDropTarget  =  NULL;
				  
				  if  (  pComm->u.getIDropTarget.hWnd  ==  m_var.m_pHtmlEdit_input->m_hWnd  )  {
					  pMyDropTarget  =  (  LPDROPTARGET  )m_var.m_pHtmlEdit_input->m_dropTarget.GetInterface(  &IID_IDropTarget  );					  
				  }
				  else  if  (  pComm->u.getIDropTarget.hWnd  ==  m_var.m_pHtmlEdit_recentMsgList->m_hWnd  )  {
					        pMyDropTarget  =  (  LPDROPTARGET  )m_var.m_pHtmlEdit_recentMsgList->m_dropTarget.GetInterface(  &IID_IDropTarget  );
						    }
				  else  
					  goto  errLabel;

				  if  (  pMyDropTarget  )  {
					  pComm->u.getIDropTarget.pIDropTarget  =  pMyDropTarget;
					  pMyDropTarget->AddRef(  );
				  }

				  
				  iErr  =  0;
errLabel:
				  return  iErr;
 }


 __declspec(  dllexport  )  int  doDoc_doTable_byRowId_param(  void  *  pDLG_TALK_var,  void  *  pPARAM_PROC_ROW  )
 {
	 int		iErr	=	-1;
	 if  (  !pDLG_TALK_var  )  return  -1;
	 DLG_TALK_var  &m_var  =  *(  DLG_TALK_var  *  )pDLG_TALK_var;
	 if  (  !pPARAM_PROC_ROW  )  return  -1;
	 PARAM_PROC_ROW  &  param  =  *(  PARAM_PROC_ROW  *  )pPARAM_PROC_ROW;
	 
	 if  (  m_var.m_pHtmlEdit_recentMsgList  )  {	
		 IHTMLDocument2				*	pDoc								=	NULL;
		 if  (  !m_var.m_pHtmlEdit_recentMsgList->GetDHtmlDocument(  &pDoc  )  )  goto  errLabel;
		 
		 doDoc(  pDoc,  (  PF_commonHandler  )doTable_byRowId,  0,  &param  );	
	 } 
	 
	 iErr  =  0;
errLabel:
	
	 return  iErr;
 }


  __declspec(  dllexport  )  BOOL  isMemFromActive(  void  *  pDLG_TALK_videoConference,  QY_MESSENGER_ID  *  pIdInfo_from,  int  *  pIndex_activeMems_from  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int		i;

	DLG_TALK_videoConference  *  pVc  =  (  DLG_TALK_videoConference  *  )pDLG_TALK_videoConference;

	for  (  i  =  0;  i  <  mycountof(  pVc->activeMems_from  );  i  ++  )  {
		 if  (  pIdInfo_from->ui64Id  ==  pVc->activeMems_from[i].mem.idInfo.ui64Id  )  break;
	}
	if  (  i  ==  mycountof(  pVc->activeMems_from  )  )  return  FALSE;

	if  (  pIndex_activeMems_from  )  *pIndex_activeMems_from  =  i;

	return  TRUE;
}

  __declspec(  dllexport  )  BOOL  dlgTalk_canSpeak(  HWND  hDlgTalk  )
{
	BOOL							bRet				=	FALSE;
	DLG_TALK_var				&	m_var				=	*(  DLG_TALK_var	*	)getDlgTalkVar(  hDlgTalk  );
	MC_VAR_isCli					*	pProcInfo			=	(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	QY_SHARED_OBJ				*	pSharedObj			=	NULL;
	SHARED_OBJ_USR				*	pSharedObjUsr		=	NULL;

	if  (  !m_var.av.taskInfo.bTaskExists  )  return  FALSE;

	if  (  !(  pSharedObj  =	getSharedObjByIndex(  pProcInfo,  m_var.av.iIndex_sharedObj_localAv  )  )  )  goto  errLabel;
	if  (  pSharedObj->iIndex_curUsr  !=  m_var.av.iIndex_usr_localAv  )  goto  errLabel;		//  2010/09/07
	if  (  !(  pSharedObjUsr  =  getSharedObjUsr(  pSharedObj,  m_var.av.iIndex_usr_localAv  )  )  )  goto  errLabel;

	//  if  (  m_var.av.taskInfo.ucbVideoConference  )  
	{	//  2010/09/04
		if  (  !isMemFromActive(  &m_var.videoConference,  &m_var.pMisCnt->idInfo,  NULL  )  ||  m_var.videoConference.bNeedRefresh_activeMems_from  )  goto  errLabel;
	}

	if  (  pSharedObjUsr->ucbNotSendData  )  goto  errLabel;
	
	if  (  !pSharedObj->route_sendLocalAv.videoConference_idInfo_to.ui64Id  &&  !pSharedObj->route_sendLocalAv.route.idInfo_to.ui64Id  )  goto  errLabel;
		
	//  2013/03/19
	if  (  pSharedObj->uiType  !=  CONST_sharedObjType_av  )  {
		if  (  pProcInfo->av.localAv.recordSoundProcInfo.uiRecordType  ==  CONST_recordType_directX  )  {
			if  (  !pProcInfo->av.localAv.recordSoundProcInfo.bCapDevConnected  )  goto  errLabel;
		    }
		else  {
			  if  (  !pProcInfo->av.localAv.recordSoundProcInfo.thread.bRunning  )  goto  errLabel;

			  //  2013/05/26
			  if  (  pProcInfo->av.localAv.recordSoundProcInfo.uiRecordType  ==  CONST_recordType_aec  )  {
				  if  (  pProcInfo->av.localAv.recordSoundProcInfo.bInputErr_aec  )  goto  errLabel;
			  }
		}
	}

	bRet  =  TRUE;
errLabel:
	return  bRet;

}

 //  2012/05/05
#if  0
 BOOL  dlgTalk_bShowMsgBox(  HWND  hCurTalker  )
{
	DLG_TALK_var  *  pCurTalkerVar  =  (  DLG_TALK_var	*	)getDlgTalkVar(  hCurTalker  );
	if  (  !pCurTalkerVar  )  return  FALSE;

	DLG_TALK_var  *  pMgrVar  =  NULL;
	if  (  !isTalkerShadowMgr(  pCurTalkerVar->addr  )  )  {
		TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pCurTalkerVar->pShadowInfo;
		if  (  !pTalkerShadow  )  return  FALSE;
		pMgrVar  =  (  DLG_TALK_var	*	)getDlgTalkVar(  pTalkerShadow->hMgr  );
		if  (  !pMgrVar  )  return  FALSE;
		}
	else  {
		  pMgrVar  =  pCurTalkerVar;
	}
		

	//  1. 本地设置优先
	if  (  pCurTalkerVar->guiData.snmpbShowMsgBox  )  {	 
		if  (  pCurTalkerVar->guiData.snmpbShowMsgBox  ==  CONST_snmpTrue  )  return  TRUE;
		return  FALSE;
	}


	//  一般墙也不显示. 2012/04/23
	if  (  pCurTalkerVar->iTalkerSubType  ==  CONST_talkerSubType_onVWall  )  return  FALSE;


	//
	DLG_TALK_var  &  m_var  =  *pMgrVar;

	//  2013/02/28
	unsigned  short  usLayoutType_local  =  dlgTalk_get_usLayoutType_local(  hCurTalker  );

	//  2. 模式为对话框时显示
 	if  (  m_var.av.taskInfo.bTaskExists
		||  m_var.av.resourcesInfo.bTaskExists  )  
	{
		if  (  usLayoutType_local  )  {
			if  (  usLayoutType_local  ==  CONST_usLayoutType_dialog  )  return  TRUE;
			return  FALSE;
		}
		if  (  m_var.av.taskInfo.usLayoutType_starter  )  {
			if  (  m_var.av.taskInfo.usLayoutType_starter  ==  CONST_usLayoutType_dialog  )  return  TRUE;
			return  FALSE;
		}
		//  2011/10/11
		if  (  m_var.m_layout.usLayoutType_cur  ==  CONST_usLayoutType_conference  
			||  m_var.m_layout.usLayoutType_cur  ==  CONST_usLayoutType_resourceOnly  )  
		{
			return  FALSE;
		}
	}

	//  3. 全局会议墙不显示. 2012/04/10
	if  (  pCurTalkerVar->ucbOnGlobalVWall  )  return  FALSE;
	 

	//  4. 缺省策略设置
 	MC_VAR_isCli		*	pProcInfo	=	(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	if  (  pProcInfo->cfg.policy.dlgTalk.snmpbShowMsgBox  ==  CONST_snmpTrue  )  return  TRUE;
	return  FALSE;
}
#endif

 BOOL  dlgTalk_bShowMsgBox(  HWND  hCurTalker  )
{
	DLG_TALK_var  *  pCurTalkerVar  =  (  DLG_TALK_var	*	)getDlgTalkVar(  hCurTalker  );
	if  (  !pCurTalkerVar  )  return  FALSE;

	DLG_TALK_var  *  pMgrVar  =  NULL;
	if  (  !isTalkerShadowMgr(  pCurTalkerVar->addr  )  )  {
		TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pCurTalkerVar->pShadowInfo;
		if  (  !pTalkerShadow  )  return  FALSE;
		pMgrVar  =  (  DLG_TALK_var	*	)getDlgTalkVar(  pTalkerShadow->hMgr  );
		if  (  !pMgrVar  )  return  FALSE;
		}
	else  {
		  pMgrVar  =  pCurTalkerVar;
	}
		

	//  1. 本地设置优先
	if  (  pCurTalkerVar->guiData.snmpbShowMsgBox  )  {	 
		if  (  pCurTalkerVar->guiData.snmpbShowMsgBox  ==  CONST_snmpTrue  )  return  TRUE;
		return  FALSE;
	}


	//  一般墙也不显示. 2012/04/23
	if  (  pCurTalkerVar->iTalkerSubType  ==  CONST_talkerSubType_onVWall  )  return  FALSE;


	//
	//  DLG_TALK_var  &  m_var  =  *pMgrVar;

	//  2013/02/28
	unsigned  short  usLayoutType_local  =  dlgTalk_get_usLayoutType_local(  hCurTalker  );

	//  2. 模式为对话框时显示
 	if  (  pMgrVar->av.taskInfo.bTaskExists
		||  pMgrVar->av.resourcesInfo.bTaskExists  )  
	{
		if  (  usLayoutType_local  )  {
			if  (  usLayoutType_local  ==  CONST_usLayoutType_dialog  )  return  TRUE;
			return  FALSE;
		}
		if  (  pMgrVar->av.taskInfo.usLayoutType_starter  )  {
			if  (  pMgrVar->av.taskInfo.usLayoutType_starter  ==  CONST_usLayoutType_dialog  )  return  TRUE;
			return  FALSE;
		}
		//  2011/10/11
#if  0
		if  (  pCurTalkerVar->m_layout.usLayoutType_cur  ==  CONST_usLayoutType_conference  
			||  pCurTalkerVar->m_layout.usLayoutType_cur  ==  CONST_usLayoutType_resourceOnly  )  
		{
			return  FALSE;
		}
#endif
	}

	//  3. 全局会议墙不显示. 2012/04/10
	if  (  pCurTalkerVar->ucbOnGlobalVWall  )  return  FALSE;
	 

	//  4. 缺省策略设置
 	MC_VAR_isCli		*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	if  (  pProcInfo->cfg.policy.dlgTalk.snmpbShowMsgBox  ==  CONST_snmpTrue  )  return  TRUE;
	return  FALSE;
}



//  2012/09/05
  BOOL  dlgTalk_bShowPtz(  HWND  hCurTalker  )
{
#ifdef  __DEBUG__
		#if  0
			traceLog(  _T(  "Test: dlgTalk_bShowPtz returns true"  )  );
			return  TRUE;
		#endif
#endif

	DLG_TALK_var  *  pCurTalkerVar  =  (  DLG_TALK_var	*	)getDlgTalkVar(  hCurTalker  );
	if  (  !pCurTalkerVar  )  return  FALSE;


	return  IsWindow(  pCurTalkerVar->ptzControl.hWnd_ptzControl  );
  }

//  2013/04/05
 BOOL  dlgTalk_bShowSubtitles(  HWND  hCurTalker  )
{
	DLG_TALK_var  *  pCurTalkerVar  =  (  DLG_TALK_var	*	)getDlgTalkVar(  hCurTalker  );
	if  (  !pCurTalkerVar  )  return  FALSE;

	return  IsWindow(  pCurTalkerVar->subtitles.hWnd_subtitles  );
}

  //  2010/12/23
 BOOL  bTaskExists_sendingResource(  DLG_TALK_var  &  m_var,  int  *  pnScreens,  int  *  pnMediaFiles  )
{
	BOOL				bRet			=	FALSE;
	MIS_MSGU		*	pMsg			=	NULL;
	Q_NODE			*	pQNode			=	NULL;
	int					nScreens		=	0;
	int					nMediaFiles		=	0;
	int					iW_screen		=	0;
	int					iH_screen		=	0;
	IM_CONTENTU		*	pContent		=	NULL;

	if  (  !m_var.m_pProcessQ  )  return  FALSE;
	GENERIC_Q		&	m_processQ		=	*m_var.m_pProcessQ;

#ifdef  __DEBUG__
		printQ_mis(  &m_processQ,  FALSE  );
#endif

	for  (  pQNode  =  m_processQ.front.pNext;  pQNode;  pQNode  =  pQNode->pNext  )  {
		pMsg  =  (  MIS_MSGU  *  )pQNode->qElemMemory.m_pBuf;
		if  (  pMsg->uiType  !=  CONST_misMsgType_task  )  continue;
		if  (  !bTaskAlive(  pMsg->task.iStatus  )  )  continue;
		//
		if  (  pMsg->task.data.route.idInfo_from.ui64Id  !=  m_var.pMisCnt->idInfo.ui64Id  )  continue;
		//
		pContent  =  (  IM_CONTENTU  *  )pMsg->task.data.buf;
		if  (  pContent->uiType  !=  CONST_imCommType_transferAvInfo  )  continue;
		switch  (  pContent->transferAvInfo.uiTaskType  )  {
				case  CONST_imTaskType_shareScreen:
					  nScreens  ++  ;
					  if  (  nScreens  ==  1  )  {
						  iW_screen  =  pContent->transferAvInfo.tranInfo.video.vh_decompress.bih.biWidth;
						  iH_screen  =  pContent->transferAvInfo.tranInfo.video.vh_decompress.bih.biHeight;
					  }
					  break;
				case  CONST_imTaskType_shareMediaFile:
					  nMediaFiles  ++  ;
					  break;
				default:
						break;
		}		
	}

	if  (  pnScreens  )  *pnScreens  =  nScreens;
	if  (  pnMediaFiles  )  *pnMediaFiles  =  nMediaFiles;
	if  (  nScreens  ==  1  )  {
		//  if  (  piW_screen  )  *piW_screen  =  iW_screen;
		//  if  (  piH_screen  )  *piH_screen  =  iH_screen;
	}
	if  (  nScreens  ||  nMediaFiles  )  bRet  =  TRUE;
	
	return  bRet;
}

 //  2010/12/23
 __declspec(  dllexport  )  BOOL  bTaskExists_recvdResource(  void  *  pDLG_TALK_var,  int  *  pnScreens,  int  *  pnMediaFiles,  int  *  piW_screen,  int  *  piH_screen  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	BOOL				bRet			=	FALSE;
	DLG_TALK_var	&	m_var			=	*(  DLG_TALK_var  *  )pDLG_TALK_var;
	MIS_MSGU		*	pMsg			=	NULL;
	Q_NODE			*	pQNode			=	NULL;
	int					nScreens		=	0;
	int					nMediaFiles		=	0;
	int					iW_screen		=	0;
	int					iH_screen		=	0;
	IM_CONTENTU		*	pContent		=	NULL;

	if  (  !m_var.m_pProcessQ  )  return  FALSE;
	GENERIC_Q		&	m_processQ		=	*m_var.m_pProcessQ;

#ifdef  __DEBUG__
		printQ_mis(  &m_processQ,  FALSE  );
#endif

	for  (  pQNode  =  m_processQ.front.pNext;  pQNode;  pQNode  =  pQNode->pNext  )  {
		pMsg  =  (  MIS_MSGU  *  )pQNode->qElemMemory.m_pBuf;
		if  (  pMsg->uiType  !=  CONST_misMsgType_task  )  continue;
		if  (  !bTaskAlive(  pMsg->task.iStatus  )  )  continue;
		//
		if  (  pMsg->task.data.route.idInfo_from.ui64Id  ==  m_var.pMisCnt->idInfo.ui64Id  )  continue;
		//
		pContent  =  (  IM_CONTENTU  *  )pMsg->task.data.buf;
		if  (  pContent->uiType  !=  CONST_imCommType_transferAvInfo  )  continue;
		switch  (  pContent->transferAvInfo.uiTaskType  )  {
				case  CONST_imTaskType_shareScreen:
					  nScreens  ++  ;
					  if  (  nScreens  ==  1  )  {
						  iW_screen  =  pContent->transferAvInfo.tranInfo.video.vh_decompress.bih.biWidth;
						  iH_screen  =  pContent->transferAvInfo.tranInfo.video.vh_decompress.bih.biHeight;
					  }
					  break;
				case  CONST_imTaskType_shareMediaFile:
					  nMediaFiles  ++  ;
					  break;
				default:
						break;
		}		
	}

	if  (  pnScreens  )  *pnScreens  =  nScreens;
	if  (  pnMediaFiles  )  *pnMediaFiles  =  nMediaFiles;
	if  (  nScreens  ==  1  )  {
		if  (  piW_screen  )  *piW_screen  =  iW_screen;
		if  (  piH_screen  )  *piH_screen  =  iH_screen;
	}
	if  (  nScreens  ||  nMediaFiles  )  bRet  =  TRUE;
	
	return  bRet;
 }
   int  tmpHandler_fillTmpGrpMemQ(  void  *  p0,  void  *  p1,  void  *  pQElem  )
{
	int				iErr		=	-1;
	//  p0
	GENERIC_Q	*	pTmpGrpMemQ	=	(  GENERIC_Q  *  )p1;
	//
	if  (  qPostMsg(  pQElem,  sizeof(  MSGR_ADDR  ),  pTmpGrpMemQ  )  )  goto  errLabel;

	iErr  =  0;
errLabel:
	return  iErr;
}


 BOOL  dlgTalk_bSetDlgInfo(  HWND  hDlgTalk,  DLG_TALK_var  &  m_var,  MSGR_ADDR  *  pAddr,  GENERIC_Q  *  pTmpGrpMemQ,  int  iTalkerSubType,  BOOL  bNeedNotShowWnd,  HWND  hFore  )
{
	 BOOL						bRet		=	FALSE;
	 QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	 

	 if  (  !pAddr  )  return  FALSE;
	 if  (  !bMessengerIdValid(  &pAddr->idInfo  )  )  return  FALSE;
	 if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_is  )  return  FALSE;
	 
	 
	 //
	 m_var.usMaxDisplayedTasks  =  pQyMc->cfg.usMaxDisplayedTasksInDlgTalk;
	 //
	 memcpy(  &m_var.addr,  pAddr,  sizeof(  m_var.addr  )  );

	 //
	 m_var.ucbGuest  =  bMessengerGuest(  m_var.addr.uiObjType  );
	 if  (  m_var.ucbGuest  )  {
         m_var.addr.uiLogonId  =  pAddr->uiLogonId;
	 }
	 //
	 if  (  pTmpGrpMemQ  )  {
		 if  (  m_var.bTmpGrpMemQInited  )  {
			 exitGenericQ(  &m_var.tmpGrpMemQ  );  m_var.bTmpGrpMemQInited  =  FALSE;
		 }
		 if  (  initGenericQ(  _T(  "tmpGrpMemQ"  ),  NULL,  0,  CONST_uiMaxQNodes_tmpGrpMemQ,  mymalloc,  free,  &m_var.tmpGrpMemQ  )  )  goto  errLabel;
		 m_var.bTmpGrpMemQInited  =  TRUE;
		 //
		 if  (  qTraverse(  pTmpGrpMemQ,  tmpHandler_fillTmpGrpMemQ,  0,  &m_var.tmpGrpMemQ  )  )  goto  errLabel;
	 }

	 //  2012/04/30
	 m_var.iTalkerSubType  =  iTalkerSubType;

	 //
	 m_var.guiData.param.bNeedNotShowWnd  =  bNeedNotShowWnd;		//  2010/04/22
	 m_var.hFore  =  hFore;	//  2007/09/09


	 //  ¼ÆËãÒ»ÏÂºÍmisServNameÏà¹ØµÄpMisCnt
	 if  (  !(  m_var.pMisCnt  =  getMisCntByName(  pQyMc,  NULL,  m_var.addr.misServName  )  )  )  goto  errLabel;
	 //


	 switch  (  m_var.addr.uiObjType  )  {
			 case  CONST_objType_phoneGuest:
			 case  CONST_objType_tmpGrp:
				   break;
			 default:
					 //  Í¨³£µÄidInfo²»ÄÜÎª0
					 if  (  !m_var.addr.idInfo.ui64Id  )  {
						 traceLogA(  "CDlgTalk::bSetDlgInfo(  ) failed, idInfo is 0"  );
						 goto  errLabel;
					 }
				     //  ¼ì²éÒ»ÏÂ£¬²»ÄÜ¶Ô±¾ÈËÁÄÌì
				     if  (  m_var.addr.idInfo.ui64Id  ==  m_var.pMisCnt->idInfo.ui64Id  &&  !m_var.addr.uiDevType  )  {
						 traceLogA(  "CDlgTalk::bSetDlgInfo(  ) failed: idInfo is me, can't be talked to"  );  goto  errLabel;
					 }
					 break;
	 }

	 bRet  =  TRUE;

errLabel:

	 if  (  bRet  )  {
		 m_var.guiData.bInfoSet  =  TRUE;
	 }

	 return  bRet;
}

 //  2013/02/28
  __declspec(  dllexport  )  unsigned  short  dlgTalk_get_usLayoutType_local(  HWND  hDlgTalk  )
 {
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	unsigned  short  usLayoutType_local		=	0;

	 DLG_TALK_var				*	pm_var		=		(  DLG_TALK_var	*	)getDlgTalkVar(  hDlgTalk  );
	 if  (  !pm_var  )  goto  errLabel;
	 	 
	 
	 //  2013/02/28
	DLG_TALK_var  *  pMgrVar  =  pm_var;
	if  (  !isTalkerShadowMgr(  pm_var->addr  )  )  {
		TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pm_var->pShadowInfo;
		if  (  !pTalkerShadow  )  goto  errLabel;
		if  (  !IsWindow(  pTalkerShadow->hMgr  )  )  goto  errLabel;
		//  hMgr  =  pTalkerShadow->hMgr;		//  2013/02/15
		pMgrVar  =  (  DLG_TALK_var	*	)getDlgTalkVar(  pTalkerShadow->hMgr  );
		if  (  !pMgrVar  )  goto  errLabel;
	}
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;	
	if  (  !pShadowMgr  )  goto  errLabel;

	usLayoutType_local  =  pShadowMgr->av.usLayoutType_local;

errLabel:
	return  usLayoutType_local;
 }


 //
__declspec(  dllexport  )  int  tmpHandler_bRemoveMsgInProcessQ(  void  *  p0,  void  *  p1, void  *  pMsgParam  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int					iErr					=	-1;
	HWND				hDlgTalk				=	(  HWND  )p0;
	PARAM_PROC_ROW	*	pParam					=	(  PARAM_PROC_ROW  *  )p1;
	MIS_MSGU		*	pMsg					=	(  MIS_MSGU  *  )pMsgParam;
	QY_MC			*	pQyMc					=	QY_GET_GBUF(  );

	if  (  !pParam  ||  !pMsg  )  return  -1;
	DLG_TALK_var	*	pDlgTalkVar				=	(  DLG_TALK_var	*	)getDlgTalkVar(  hDlgTalk  );
	if  (  !pDlgTalkVar  )  {
		#ifdef  __DEBUG__
				MACRO_qyAssert(  0,  _T(  "tmpHandler_bRemoveMsgInProcessQ failed, hDlgTalk err"  )  );
		#endif
		return  -1;
	}

	switch  (  pMsg->uiType  )  {
			case  CONST_misMsgType_talk:  
				  if  (  !pMsg->talk.tStartTime_processed  )  break;
			
				  if  (  pDlgTalkVar->nMsgTalks_processed_inProcessQ  <  50  )  {		//  保留到50个消息
					  pParam->nMsgTalks_processed_inProcessQ  ++  ;
					  break;
				  }
				  pDlgTalkVar->nMsgTalks_processed_inProcessQ  --  ;

				  iErr  =  1;  goto  errLabel;
				  break;
			case  CONST_misMsgType_task:
				  if  (  pParam->iTaskId  )  {
					  if  (  pMsg->task.iTaskId  ==  pParam->iTaskId  )  {
						  iErr  =  1;  goto  errLabel;
					  }
					  break;
				  }

				  if  (  !pMsg->task.tStartTime_processed  )  break;

				  if  (  !pMsg->task.iTaskId  )  {
					  iErr  =  1;  goto  errLabel;
				  }
				  break;
			case  CONST_misMsgType_taskStatus:
				  if  (  !pMsg->taskStatus.tStartTime_processed  )  break;
				  iErr  =  1;  goto  errLabel;
				  break;
			case  CONST_misMsgType_notifyTaskEnd_qmc:
				  if  (  !pMsg->notifyTaskEnd.tStartTime_processed  )  break;
				  iErr  =  1;  goto  errLabel;
				  break;
			case  CONST_misMsgType_applyForWork:		//  2011/04/08
				  if  (  !pMsg->applyForWork.tStartTime_processed  )  break;
				  iErr  =  1;  goto  errLabel;
				  break;
			case  CONST_misMsgType_applyForTalkerShadow_qmc:	//  2012/04/23
				  if  (  !pMsg->applyForTalkerShadow_qmc.tStartTime_processed  )  break;
				  iErr  =  1;  goto  errLabel;
				  break;
			default:
					#ifdef  __DEBUG__
						    traceLogA(  "tmp_bRemoveMsgInProcessQ: unprocessed msg, %d",  pMsg->uiType  );
							assert(  0  );
					#endif
					break;
	}

	iErr  =  0;
errLabel:
	return  iErr;
}



  //  2012/05/02. 在这个函数中,不应该采用qRemoveMsg,因为可能其他地方正在使用被删除的消息.应该做一个需要删除的标志位,并且其他的地方不能再采用这个消息就可以了
  //  int  dlgTalk_qPostMsg(  DLG_TALK_var  *  pVar,  Q_ELEM_T  *  pQElem,  unsigned  int  size  )
  __declspec(  dllexport  )  int  dlgTalk_qPostMsg(  HWND  hDlgTalk,  Q_ELEM_T  *  pQElem,  unsigned  int  size  )
{
	DLG_TALK_var  *  pVar  =  (  DLG_TALK_var	*	)getDlgTalkVar(  hDlgTalk  );
	if  (  !pVar  )  return  -1;
	if  (  !pVar->m_pProcessQ  )  return  -1;
	if  (  !pQElem  ||  !size  )  return  -1;

#ifdef  __DEBUG__
		traceLog(  _T(  "dlgTalk_qPostMsg not finished"  )  );
#endif

	MIS_MSGU	*	pMsg	=	(  MIS_MSGU  *  )pQElem;
	switch  (  pMsg->uiType  )  {
			case  CONST_misMsgType_task:
				  if  (  pMsg->task.iTaskId  )  {
					  PARAM_PROC_ROW	param;
					  memset(  &param,  0,  sizeof(  param  )  );
					  param.iTaskId  =  pMsg->task.iTaskId;
					  qRemoveMsg(  pVar->m_pProcessQ,  tmpHandler_bRemoveMsgInProcessQ,  hDlgTalk,  &param  );
				  }
				  break;
			case  CONST_misMsgType_talk:
				  break;
			case  CONST_misMsgType_taskStatus:
				  traceLog(  _T(  "dlgTalk_qPostMsg: msgTaskStatus"  )  );
				  break;
			case  CONST_misMsgType_applyForTalkerShadow_qmc:
				  break;
			default:
				    traceLog(  _T(  "dlgTalk_qPostMsg: unexpected msgType, %d"  ),  pMsg->uiType  );
					break;
	}

	return  ::qPostMsg(  pQElem,  size,  pVar->m_pProcessQ  );
}
