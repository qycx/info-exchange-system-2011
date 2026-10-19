

#include	"stdafx.h"
#include	<stdlib.h>
#include	<math.h>
#include	<tchar.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"tmpCeLib.h"

#include	"myresource.h"
#include	"qmcVWall.h"
#include	"WallTalkers.h"

#include	"dlgDesktopsMonProc.h"
#include	"DlgDynBmpsProc.h"
#include	"dlgVideosProc.h"

#include	"qmcVideoCapture.h"
#include	"qyVk.h"

#include	"qmcDxSurfacePublic.h"

#include	"qyCusResTemp.h"

#include	"qyAvRecordPublic.h"

#include	"sp.h"


#if  !defined(  __WINCE__  )  &&  !defined(  __APP_qyMc_touchscreen__  )  
	#ifndef  __DEBUG__
		//  #include	"DlgQnmSendHint.h"
		#include	"qyPs.h"
	#endif
#endif

#include	"dlgTalkProc.h"

#include	"qmcGpsProc.h"
//
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"dlgSelect_isCli_public.h"

#include	"myDb.h"




 int  tmpHandler_getZoneParam(  void  *  p0,  void  *  p1,  void  *  p2  )
 {
	 int						iErr			=	-1;
	 MIS_MSG_procVideo_qmc	*	pMsg			=	(  MIS_MSG_procVideo_qmc  *  )p0;
	 COMMON_PARAM			*	pCommonParam	=	(  COMMON_PARAM  *  )p1;
	 VW_ruleU				*	pRuleElem		=	(  VW_ruleU  *  )p2;
	 //
	 //  pCommonParam->p0;
	 int						iTaskId_videoConference	=	(  int  )pCommonParam->p1;
	 ZONE_PARAM				*	pZoneParam		=	(  ZONE_PARAM  *  )pCommonParam->p2;

	 BOOL						bMatched		=	FALSE;
	 int						nRulePriority	=	0;

	 switch  (  pRuleElem->common.uiType  )  {
			 case  CONST_vwRuleType_dynBmp:  
				   //  if  (  pMsg->iTaskId  ==  pRuleElem->dynBmp.iTaskId  )  
				   if  (  pMsg->paramMsgToShadow.uiTranNo_zone  ==  pRuleElem->dynBmp.uiTranNo_spObj
					   &&  pMsg->idInfo_peer.ui64Id  ==  pRuleElem->dynBmp.dynBmp.idInfo.ui64Id
					   &&  pMsg->paramMsgToShadow.tmp_dynBmp.uiObjType  ==  pRuleElem->dynBmp.dynBmp.uiObjType
					   &&  pMsg->paramMsgToShadow.tmp_dynBmp.usIndex  ==  pRuleElem->dynBmp.dynBmp.usIndex  )
				   {		
					   bMatched  =  TRUE;  
					   break;
				   }				   
				   break;
			 case  CONST_vwRuleType_conference_imGrp:  {
				   bMatched  =  TRUE;
				   }
				   break;
			 case  CONST_vwRuleType_conference_imGrpMem:
				   if  (  iTaskId_videoConference  )  {		//  2010/09/12
					   if  (  pMsg->iTaskId  !=  iTaskId_videoConference  )  break;
				   }
				   if  (  pMsg->idInfo_sender.ui64Id  ==  pRuleElem->conference_imGrpMem.idInfo.ui64Id  )  {
					   bMatched  =  TRUE;
					   break;
				   }
				   break;
			 default:
				     traceLogA(  "tmpHandler_getZoneParam: unknown ruleType %d",  pRuleElem->common.uiType  );
					 break;
	 }

	 if  (  bMatched  )  {
		 nRulePriority  =  (  int  )qyGetDesByType(  CONST_rulePriorityTable,  pRuleElem->common.uiType  );
		 if  (  nRulePriority  <  0  )  {
			 traceLogA(  "tmphandle_getZoneparam: rulePriorityTable error"  );
			 goto  errLabel;
		 }
		 if  (  nRulePriority  >  pZoneParam->nRulePriority  )  {
			 memset(  pZoneParam,  0,  sizeof(  ZONE_PARAM  )  );
			 //  pZoneParam->uiTranNo_zone  =  pRuleElem->dynBmp.uiTranNo_spObj;
			 pZoneParam->uiTranNo_zone  =  pRuleElem->common.uiTranNo_spObj;		//  2012/04/03
			 pZoneParam->nRulePriority  =  nRulePriority;
		 }
	 }
	 iErr  =  0;
errLabel:

	 return  iErr;
 }


#if  10	//  2013/06/12
int  dlgDynBmps_getZoneParam(  HWND  hDlgDynBmps,  MIS_MSG_procVideo_qmc  *  pMsg,  ZONE_PARAM  *  pParam  )
{
	int			iErr	=	-1;

	DLG_desktopsMon_var  *  pDlgDesktopsMonVar  =  (  DLG_desktopsMon_var  *  )getDlgDesktopsMonVar(  hDlgDynBmps  );
	if  (  !pDlgDesktopsMonVar  )  return  -1;
	DLG_dynBmps_var  *  pDlgDynBmpsVar  =  (  DLG_dynBmps_var  *  )getDlgDynBmpsVar(  hDlgDynBmps  );
	if  (  !pDlgDynBmpsVar  )  return  -1;
	DLG_dynBmps_var	&  m_var  =  *pDlgDynBmpsVar;

	int			i;
	int			tmpiRet;
	ZONE_PARAM	zoneParam;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return  -1;
	
	if  (  !IsWindow(  pMsg->hWnd_task  )  )  return  -1;

#if  0	//  2012/05/05
	if  (  pMsg->hWnd_task  !=  this->m_hWnd  )  {
		QY_WMBUF_COMM	wmBuf;
		memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
		wmBuf.uiType  =  CONST_qyWmParam_chkTask;
		wmBuf.u.chkTask.iTaskId  =  pMsg->iTaskId;
		if  (  CONST_qyWmRc_ok  ==  ::SendMessage(  pMsg->hWnd_task,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  )  )  {
			if  (  wmBuf.u.chkTask.bNotExists  )  {
				traceLogA(  "dlgDynBmps::getZoneParam, chkTask failed."  );
				goto  errLabel;
			}
		}
	}
#endif

	//  2010/09/12
	int				iTaskId_videoConference	=	0;
	if  (  pDlgDesktopsMonVar->iWndContentType  ==  CONST_qyWndContentType_vWall  )  {
		if  (  m_var.u.vWall.ucbVideoConference  )  {
			if  (  pMsg->hWnd_task  ==  m_var.u.vWall.hDlg_org  )  {
				DLG_TALK_var  *  pDlgTalkVar	=	(  DLG_TALK_var	*	)getDlgTalkVar(  m_var.u.vWall.hDlg_org  );

				if  (  pDlgTalkVar->av.taskInfo.bTaskExists  )  {
					iTaskId_videoConference  =  pDlgTalkVar->av.taskInfo.iTaskId;				
					//
					if  (  pMsg->iTaskId  ==  pDlgTalkVar->av.taskInfo.iTaskId  )  {

						QY_MESSENGER_ID	idInfo_sender;
						idInfo_sender.ui64Id  =  pMsg->idInfo_sender.ui64Id;
						if  (  !isMemFromActive(  &pDlgTalkVar->videoConference,  &idInfo_sender,  NULL  )  )  {
							traceLog(  _T(  "skipped: %I64u is not an activeMem"  ),  pMsg->idInfo_sender.ui64Id  );
							goto  errLabel;
						}
					}
				}
			}
		}
	}
	
	//
	COMMON_PARAM	commonParam;
	memset(  &zoneParam,  0,  sizeof(  zoneParam  )  );
	MACRO_makeCommonParam3(  0,  (  void  *  )iTaskId_videoConference,  &zoneParam,  commonParam  );
	for  (  i  =  0;  i  <  m_var.pWall->m_var.usCnt;  i  ++  )  {
		 tmpiRet  =  qTraverse(  m_var.pWall->getSubWall(  i  )->pRuleQ,  tmpHandler_getZoneParam,  pMsg,  &commonParam  );
		 if  (  tmpiRet  )  goto  errLabel;
		 if  (  zoneParam.uiTranNo_zone  )  {
			 zoneParam.index_subWall  =  i;
			 break;
		 }
	}
	if  (  i  ==  m_var.pWall->m_var.usCnt  )  goto  errLabel;

	//
	SUB_V_WALL	*	pSubWall	=	m_var.pWall->getSubWall(  zoneParam.index_subWall  );
	if  (  !pSubWall  )  goto  errLabel;
	for  (  i  =  0;  i  <  pSubWall->usCnt;  i  ++  )  {
		 if  (  pSubWall->mems[i].uiTranNo_spObj  ==  zoneParam.uiTranNo_zone  )  break;
	}
	if  (  i  ==  pSubWall->usCnt  )  goto  errLabel;
	zoneParam.index_zone  =  i;
	
	iErr  =  0;
errLabel:

	if  (  !iErr  )  {
		memcpy(  pParam,  &zoneParam,  sizeof(  ZONE_PARAM  )  );

	    #ifdef  __DEBUG__
		        traceLogA(  "getZoneParams: ( %I64u, %d, %d ) -> index_subWall %d, uiTranNo_spObj %d",  pMsg->idInfo_sender.ui64Id,  pMsg->uiTranNo_openAvDev,  pMsg->usIndex,  zoneParam.index_subWall,  zoneParam.uiTranNo_zone  );
		#endif
	}
	if  (  iErr  )  {
		#ifdef  __DEBUG__
			   traceLogA(  "getZoneParams failed: ( %I64u, %d, %d )",  pMsg->idInfo_sender.ui64Id,  pMsg->uiTranNo_openAvDev,  pMsg->usIndex  );
		#endif
	}

	return  iErr;
}
#endif


 //  2012/05/05
 int  tmpHandler_chkVWallRule_dlgDynBmps(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int					iErr			=	-1;
	//  p0
	COMMON_PARAM	*	pCommonParam	=	(  COMMON_PARAM  *  )p1;
	VW_ruleU		*	pRuleElem		=	(  VW_ruleU  *  )p2;
	//
	//  CDlgDynBmps		*	pDlg			=	(  CDlgDynBmps  *  )pCommonParam->p0;
	HWND				hDlgDynBmps		=	(  HWND  )pCommonParam->p0;
	int					subWallIndex	=	(  int  )pCommonParam->p1;
	BOOL			*	pbImgRestarted	=	(  BOOL  *  )pCommonParam->p2;
	//
	DLG_desktopsMon_var  *  pDlgDesktopsMonVar  =  (  DLG_desktopsMon_var  *  )getDlgDesktopsMonVar(  hDlgDynBmps  );
	if  (  !pDlgDesktopsMonVar  )  return  -1;
	DLG_dynBmps_var  *  pDlgDynBmpsVar  =  (  DLG_dynBmps_var  *  )getDlgDynBmpsVar(  hDlgDynBmps  );
	if  (  !pDlgDynBmpsVar  )  return  -1;
	DLG_dynBmps_var  &  m_var  =  *pDlgDynBmpsVar;
	//
	MC_VAR_isCli		*	pProcInfo		=	(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	QY_MC			*	pQyMc			=	(  QY_MC  *  )pProcInfo->pQyMcParam;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return  -1;
	//
	SUB_V_WALL		*	pSubWall		=	m_var.pWall->getSubWall(  subWallIndex  );
	if  (  !pSubWall  )  return  -1;
	int					j,  k;
	BOOL				bImgRestarted	=	FALSE;
	BOOL				bFound			=	FALSE;


	//  如果客户端没联上服务器,那么就不需要viewDynBmp
	if  (  !bMessengerOnline(  pQyMc  )  )  {
		char	timeBuf[CONST_qyTimeLen  +  1];
		getCurTime(  timeBuf  );
		char	buf[256];
		qyDisplayTime(  timeBuf,  buf,  mycountof(  buf  )  );

		_sntprintf(  m_var.tHint,  mycountof(  m_var.tHint  ),  _T(  "Can't connect to server, don't need to check vWall rule."  )  );
		_sntprintf(  m_var.tHint,  mycountof(  m_var.tHint  ),  _T(  "%s %s."  ),  m_var.tHint,  CQyString(  buf  )  );
		qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "vWall: %s"  ),  m_var.tHint  );

		goto  errLabel;
	}
	m_var.tHint[0]  =  0;


	if  (  pRuleElem->common.uiType  ==  CONST_vwRuleType_dynBmp  )  {
		

		//
#if  0
		if  (  pRuleElem->dynBmp.iTaskId  )  {
			for  (  j  =  0;  !bFound  &&  j  <  pSubWall->usCnt;  j  ++  )  {
				 for  (  k  =  0;  !bFound  &&  k  <  mycountof(  pSubWall->mems[j].images.mems  );  k  ++  )  {
					  CAP_IMAGE	*	pImg	=  &pSubWall->mems[j].images.mems[k];	
					  if  (  !pImg->idInfo_sender.ui64Id  )  continue;

					  if  (  pImg->iTaskId  ==  pRuleElem->dynBmp.iTaskId  )  {
						  bFound  =  TRUE;  break;
					  }
				 }
			}
		}
#endif

		for  (  j  =  0;  j  <  pSubWall->usCnt;  j  ++  )  {
			 if  (  pSubWall->mems[j].uiTranNo_spObj  ==  pRuleElem->dynBmp.uiTranNo_spObj  )  break;
		}
		if  (  j  <  pSubWall->usCnt  )  {
			for  (  k  =  0;  k  <  mycountof(  pSubWall->mems[j].images.mems  );  k  ++  )  {
				  CAP_IMAGE	*	pImg	=  &pSubWall->mems[j].images.mems[k];	
				  if  (  !pImg->idInfo_sender.ui64Id  )  continue;
				  if  (  pImg->idInfo_sender.ui64Id  ==  pRuleElem->dynBmp.dynBmp.idInfo.ui64Id  
					  &&  GetTickCount(  )  -  pImg->dwTickCnt_lastDrawing  <  15  *  1000  )
				  {
					  bFound  =  TRUE;
					  break;
				  }				 
			}
		}


		if  (  !bFound  )  {				 
			//
			//  pRuleElem->dynBmp.iTaskId  =  0;

			//
			QY_DMITEM	*	pTable				=					getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );
			char	timeBuf[CONST_qyTimeLen  +  1];
			getCurTime(  timeBuf  );
			char	buf[256];
			qyDisplayTime(  timeBuf,  buf,  mycountof(  buf  )  );

			_sntprintf(  m_var.tHint,  mycountof(  m_var.tHint  ),  _T(  "%s: %I64u, %s, %d."  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_statusVWallRestart  ),  pRuleElem->dynBmp.dynBmp.idInfo.ui64Id,  qyGetDesByType1(  pTable,  pRuleElem->dynBmp.dynBmp.uiObjType  ),  pRuleElem->dynBmp.dynBmp.usIndex  );
			_sntprintf(  m_var.tHint,  mycountof(  m_var.tHint  ),  _T(  "%s %s."  ),  m_var.tHint,  CQyString(  buf  )  );
			qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dynBmp: %s"  ),  m_var.tHint  );


#if  0
			MSGR_ADDR		addr;

			memset(  &addr,  0,  sizeof(  addr  )  );
			lstrcpyn(  addr.misServName,  pDlg->m_var.pMisCnt->cfg.misServName,  mycountof(  addr.misServName  )  );
			addr.idInfo.ui64Id  =  pRuleElem->dynBmp.dynBmp.idInfo.ui64Id;

			if  (  procSendAvInfo(  pDlg->m_var.pMisCnt,  pDlg->m_hWnd,  FALSE,  CONST_imTaskType_viewDynBmp,  NULL,  NULL,  NULL,  NULL,  NULL,  -1,  -1,  &pRuleElem->dynBmp.dynBmp,  &pRuleElem->dynBmp.iTaskId,  &addr  )  )  {
				qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dynBmp: procSendAvInfo failed"  )  );
				goto  errLabel;
			}
			
			bImgRestarted  =  TRUE;
#endif

			if  (  pRuleElem->dynBmp.hTalkerShadowMgr  )  {
				if  (  !IsWindow(  pRuleElem->dynBmp.hTalkerShadowMgr  )  )  pRuleElem->dynBmp.hTalkerShadowMgr  =  NULL;
			}
			if  (  !pRuleElem->dynBmp.hTalkerShadowMgr  )  {
				// 首先找到主窗口
				HWND	hDlgTalk  =  NULL;

				BOOL  bNeedNotShowWnd  =  TRUE;
				#ifdef  __DEBUG__	
					    #ifdef  __TEST_showTalkerShadowMgrFirst__
								bNeedNotShowWnd  =  FALSE;	
								traceLog(  _T(  "for test, bNeedNotShowWnd is false"  )  );
						#endif
				#endif				
				pFuncs->pf_talkToMessenger(  pRuleElem->dynBmp.dynBmp.idInfo.ui64Id,  bNeedNotShowWnd,  FALSE,  &hDlgTalk  );				
				if  (  IsWindow(  hDlgTalk  )  )  {
					pRuleElem->dynBmp.hTalkerShadowMgr  =  hDlgTalk;					  
				}				
			}
			if  (  pRuleElem->dynBmp.hTalkerShadowMgr  )  {

				VW_rule_messengerCmd	vwRuleCmd;
				memset(  &vwRuleCmd,  0,  sizeof(  vwRuleCmd  )  );
				if  (  pRuleElem->dynBmp.dynBmp.uiObjType  ==  CONST_objType_screen  )  {
					vwRuleCmd.ucbViewScreen  =  TRUE;
					}
				else  if  (  pRuleElem->dynBmp.dynBmp.uiObjType  ==  CONST_objType_webcam  )  {
						  switch  (  pRuleElem->dynBmp.dynBmp.usIndex  )  {
								  case  0:  
										vwRuleCmd.ucbViewWebcam0  =  TRUE;
										break;
								  case  1:
										vwRuleCmd.ucbViewWebcam1  =  TRUE;
										break;
								  case  2:
										vwRuleCmd.ucbViewWebcam2  =  TRUE;
										break;
								  default:
										#ifdef  __DEBUG__
												traceLog(  _T(  "tmpHandler_chkVWallRule: unprocessed usIndex %d"  ),  (  int  )pRuleElem->dynBmp.dynBmp.usIndex  );
										#endif
										break;
						  }
						  }
				else  {
					  #ifdef  __DEBUG__
							  traceLog(  _T(  "tmpHandler_chkVWallRule: unprocessed objType %d"  ),  pRuleElem->dynBmp.dynBmp.uiObjType  );
					  #endif
				}
				

				//		
				_sntprintf(  m_var.tHint,  mycountof(  m_var.tHint  ),  _T(  "start dynBmp: %I64u."  ),  pRuleElem->dynBmp.dynBmp.idInfo.ui64Id  );				
				qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dynBmp: %s"  ),  m_var.tHint  );

				MIS_MSG_applyForTalkerShadow_qmc	msg;
				memset(  &msg,  0,  sizeof(  msg  )  );
				msg.uiType  =  CONST_misMsgType_applyForTalkerShadow_qmc;
				msg.hWall  =  hDlgDynBmps;	//  pDlg->m_hWnd;
				msg.iWndContentType_wall  =  pDlgDesktopsMonVar->iWndContentType;	//  pDlg->getWndContentType(  );
				msg.uiVwRuleType  =  pRuleElem->common.uiType;
				msg.uiTranNo_zone  =  pRuleElem->common.uiTranNo_spObj;
				memcpy(  &msg.vwRuleCmd,  &vwRuleCmd,  sizeof(  msg.vwRuleCmd  )  );
				msg.idInfo.ui64Id  =  pRuleElem->dynBmp.dynBmp.idInfo.ui64Id;
				//
				pFuncs->pf_dlgTalk_qPostMsg(  pRuleElem->dynBmp.hTalkerShadowMgr,  &msg,  sizeof(  msg  )  );
				PostMessage(  pRuleElem->dynBmp.hTalkerShadowMgr,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );
				
			}

		}

		}
	else  if  (  pRuleElem->common.uiType  ==  CONST_vwRuleType_messenger  )  {		//  2012/04/22

			  //
			  if  (  !bSupported_vwRuleType_messenger(  )  )  {
				  _sntprintf(  m_var.tHint,  mycountof(  m_var.tHint  ),  _T(  "chkVWallRule failed, vwRuleType_messenger not supported"  )  );				
				  qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dynBmp: %s"  ),  m_var.tHint  );
				  goto  errLabel;
			  }
			  //  2012/05/27
			  int  iSubType  =  pDlgDesktopsMonVar->iSubType;	//  pDlg->getWndContentSubType(  );
			  switch  (  iSubType  )  {
					  case  CONST_vwSubType_global:
					  case  CONST_vwSubType_globalGps:
					  case  CONST_vwSubType_gps:
						    break;
					  default:
							_sntprintf(  m_var.tHint,  mycountof(  m_var.tHint  ),  _T(  "chkVWallRule failed, vwRuleType_messenger not supported in this wall"  )  );				
							qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "dynBmp: %s"  ),  m_var.tHint  );
							goto  errLabel;
			  }

			  //
			  for  (  j  =  0;  !bFound  &&  j  <  pSubWall->usCnt;  j  ++  )  {
				   if  (  pSubWall->mems[j].uiTranNo_spObj  ==  pRuleElem->messenger.uiTranNo_spObj  )  {
					   bFound  =  TRUE;
					   break;	
				   }		
			  }
			  if  (  bFound  )  {
				  if  (  pRuleElem->messenger.hTalkerShadowMgr  )  {
					  if  (  !IsWindow(  pRuleElem->messenger.hTalkerShadowMgr  )  )  pRuleElem->messenger.hTalkerShadowMgr  =  NULL;
				  }
				  if  (  !pRuleElem->messenger.hTalkerShadowMgr  )  {
					  // 首先找到主窗口
					  HWND	hDlgTalk  =  NULL;

					  BOOL  bNeedNotShowWnd  =  TRUE;
					  #ifdef  __DEBUG__	
							  #ifdef  __TEST_showTalkerShadowMgrFirst__
									bNeedNotShowWnd  =  FALSE;	
									traceLog(  _T(  "for test, bNeedNotShowWnd is false"  )  );
							  #endif
					  #endif
					  pFuncs->pf_talkToMessenger(  pRuleElem->messenger.idInfo.ui64Id,  bNeedNotShowWnd,  FALSE,  &hDlgTalk  );
					  if  (  IsWindow(  hDlgTalk  )  )  {
						  pRuleElem->messenger.hTalkerShadowMgr  =  hDlgTalk;
					  }
				  }
				  if  (  pRuleElem->messenger.hTalkerShadowMgr  )  {

					  //  再找影子窗口
					  if  (  pRuleElem->messenger.hTalkerShadow  )  {					  
						  if  (  !IsWindow(  pRuleElem->messenger.hTalkerShadow  )  )  pRuleElem->messenger.hTalkerShadow  =  NULL;				  
					  }

					  VW_rule_messengerCmd	vwRuleCmd;
					  memcpy(  &vwRuleCmd,  &pRuleElem->messenger.cmd,  sizeof(  vwRuleCmd  )  );
					  vwRuleCmd.ucbViewGps  =  isVwSubType_gps(  pDlgDesktopsMonVar->iSubType  );	//  pDlg->getWndContentSubType(  )  );

					  if  (  !pRuleElem->messenger.hTalkerShadow  )  {

						  _sntprintf(  m_var.tHint,  mycountof(  m_var.tHint  ),  _T(  "start shadow: %I64u."  ),  pRuleElem->messenger.idInfo.ui64Id  );
						  qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Messenger: %s"  ),  m_var.tHint  );

						  MIS_MSG_applyForTalkerShadow_qmc	msg;
						  memset(  &msg,  0,  sizeof(  msg  )  );
						  msg.uiType  =  CONST_misMsgType_applyForTalkerShadow_qmc;
						  msg.hWall  =  hDlgDynBmps;	//  pDlg->m_hWnd;
						  msg.iWndContentType_wall  =  pDlgDesktopsMonVar->iWndContentType;	//  pDlg->getWndContentType(  );
						  msg.uiVwRuleType  =  pRuleElem->common.uiType;
						  msg.uiTranNo_zone  =  pRuleElem->messenger.uiTranNo_spObj;
						  memcpy(  &msg.vwRuleCmd,  &vwRuleCmd,  sizeof(  msg.vwRuleCmd  )  );
						  msg.idInfo.ui64Id  =  pRuleElem->messenger.idInfo.ui64Id;
						  //
						  pFuncs->pf_dlgTalk_qPostMsg(  pRuleElem->messenger.hTalkerShadowMgr,  &msg,  sizeof(  msg  )  );
						  PostMessage(  pRuleElem->messenger.hTalkerShadowMgr,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );
					  }

					  //
					  if  (  pRuleElem->messenger.hTalkerShadow  )  {
						  DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var	*	)getDlgTalkVar(  pRuleElem->messenger.hTalkerShadowMgr  );
						  if  (  !pMgrVar  )  goto  errLabel;
						  if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;
						  TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
						  if  (  !pShadowMgr  )  goto  errLabel;
						  for  (  k  =  0;  k  <  mycountof(  pShadowMgr->shadows  );  k  ++  )  {
							   if  (  pShadowMgr->shadows[k].hShadow  ==  pRuleElem->messenger.hTalkerShadow  )  break;
						  }
						  if  (  k  <  mycountof(  pShadowMgr->shadows  )  )  {
					
							  if  (  memcmp(  &pShadowMgr->shadows[k].vwRuleCmd,  &vwRuleCmd,  sizeof(  pShadowMgr->shadows[k].vwRuleCmd  )  )  )  {						  
								  //
								  _sntprintf(  m_var.tHint,  mycountof(  m_var.tHint  ),  _T(  "cmd need refreshed: %I64u."  ),  pRuleElem->messenger.idInfo.ui64Id  );
								  qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "Messenger: %s"  ),  m_var.tHint  );

								  MIS_MSG_applyForTalkerShadow_qmc	msg;
								  memset(  &msg,  0,  sizeof(  msg  )  );
								  msg.uiType  =  CONST_misMsgType_applyForTalkerShadow_qmc;
								  msg.hWall  =  hDlgDynBmps;	//  pDlg->m_hWnd;
								  msg.iWndContentType_wall  =  pDlgDesktopsMonVar->iWndContentType;	//  pDlg->getWndContentType(  );
								  msg.uiVwRuleType  =  pRuleElem->common.uiType;
								  msg.uiTranNo_zone  =  pRuleElem->messenger.uiTranNo_spObj;
								  memcpy(  &msg.vwRuleCmd,  &vwRuleCmd,  sizeof(  msg.vwRuleCmd  )  );
								  msg.idInfo.ui64Id  =  pRuleElem->messenger.idInfo.ui64Id;
								  msg.ucbRefreshCmd  =  TRUE;
								  //
								  pFuncs->pf_dlgTalk_qPostMsg(  pRuleElem->messenger.hTalkerShadowMgr,  &msg,  sizeof(  msg  )  );
								  PostMessage(  pRuleElem->messenger.hTalkerShadowMgr,  CONST_qyWm_postComm,  CONST_qyWmParam_msgArrive,  0  );
							  }
						  }
					  }
				  }
			  }

	}


	if  (  bImgRestarted  )  {
		if  (  pbImgRestarted  )  *pbImgRestarted  =  TRUE;
	}

	iErr  =  0;
errLabel:
	return  iErr;
}


int  dlgVideos_procVideo(  HWND  m_hWnd,  void  *  pDLG_desktopsMon_var,  void  *  pDlgVideosVar,  MIS_MSG_procVideo_qmc  *	pMsg    )
 {
	 int		iErr	=	-1;

	 FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );
	 if  (  !pFuncs  )  return  -1;
	 
	 DLG_desktopsMon_var  *  pBaseVar  =  (  DLG_desktopsMon_var  *  )pDLG_desktopsMon_var;
	 if  (  !pBaseVar  ||  !pDlgVideosVar  )  return  -1;
	 DLG_videos_var  &  m_var  =  *(  DLG_videos_var  *  )pDlgVideosVar;

	 BOOL							bUseDxSurface	=	m_var.bUseDirectX;
	 ZONE_PARAM				*	pZoneParam		=	NULL;
	 int							i;

				  /*
				  switch  (  m_var.uiTaskType  )  {
						  case  CONST_imTaskType_shareScreen:
						  case  CONST_imTaskType_remoteAssist:
						  case  0:									//  2009/10/12. for vWall
							    bUseDxSurface  =  FALSE;
								break;
						  default:
								  break;
				  }
				  */
				  bUseDxSurface  =  FALSE;
				  #ifdef  __DEBUG__
						  {
							  static  BOOL  b  =  FALSE;
							  if  (  !b  )  traceLogA(  "Not finished: dlgVideos, bUseDxSurface shall be processed."  );
							  b  =  TRUE;
						  }
				  #endif

				
				  //  if  (  m_var.bVideoConference  )  
				  {  //  2010/09/12

					  //			
					  CAP_IMAGES			*	pImgs		=	&m_var.images;
					  HWND						hDlg		=	m_hWnd;

					#if  0
					  QY_PLAYER				*	pPlayer;
					  
					  if  (  pMsg->index_player  <  0  ||  pMsg->index_player  >=  pProcInfo->av.usCnt_players  )  goto  errLabel;
					  pPlayer  =  &pProcInfo->av.pPlayers[pMsg->index_player];
					#endif

					  if  (  pMsg->index_player  <  0  ||  pMsg->index_player  >=  m_var.usCnt_zoneParams  )  goto  errLabel;
					  pZoneParam  =  &m_var.pZoneParams[pMsg->index_player];
				  						
					  BOOL			bZoneOk		=	FALSE;				  
					  if  (  pZoneParam->index_capImage  >=  0  &&  pZoneParam->index_capImage  <  mycountof(  pImgs->mems  )  )  {
						  CAP_IMAGE	*	pImg	=	&pImgs->mems[pZoneParam->index_capImage];
						  if  (  pImg->idInfo_sender.ui64Id  ==  pMsg->idInfo_sender.ui64Id  
							  &&  pImg->uiTranNo_openAvDev  ==  pMsg->uiTranNo_openAvDev
							  &&  pImg->usIndex  ==  pMsg->usIndex  )  
						  {
							  bZoneOk  =  TRUE;
						  }
					  }											   
					  //
					  #ifdef  __DEBUG__
						  //  if  (  !bMeImages  ) traceLog(  _T(  "dlgTalk: bZoneOk %d, index_player %d, usIndex %d, index_capImage %d, "  ),  bZoneOk,  pMsg->index_player,  pMsg->usIndex,  pPlayer->video.m_var.zoneParam.index_capImage  );
					  #endif
					  //
					  if  (  !bZoneOk  )  {							
						  memset(  pZoneParam,  0,  sizeof(  pZoneParam[0]  )  );
				  
						  if  (  m_var.bVideoConference  )  {

							  DLG_TALK_var	*	pDlgTalkVar	=	(  DLG_TALK_var	*	)getDlgTalkVar(  m_var.hDlgTalk  );
							  if  (  !pDlgTalkVar  )  goto  errLabel;

							  DLG_TALK_var	*	pMgrVar		=	NULL;
							  if  (  isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  pMgrVar  =  pDlgTalkVar;
							  else  {
								    TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pDlgTalkVar->pShadowInfo;
									if  (  !pShadow  )  goto  errLabel;
									pMgrVar  =  (  DLG_TALK_var	*	)getDlgTalkVar(  pShadow->hMgr  );
									if  (  !pMgrVar  )  goto  errLabel;
							  }

							  BOOL	bFound  =  FALSE;
							  if  (  !pMsg->iTaskId  )  {
								  traceLogA(  "dlgTalk::OnQyComm failed: iTaskId is 0"  );
								  goto  errLabel;					  
							  }
							  MIS_MSG_TASK	*	pMsgTask;
							  if  (  (  pMsgTask  =  pFuncs->pf_findTaskInProcessQ(  pMgrVar,  pMsg->iTaskId,  FALSE,  FALSE  )  )  )  {
								  if  (  !bTaskAlive(  pMsgTask->iStatus  )  )  goto  errLabel;			  
								  bFound  =  TRUE;
							  }
							  if  (  !bFound  )  {
								  //  2012/04/25			
								  TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
								  for  (  i  =  0;  i  <  mycountof(  pShadowMgr->rules_viewDynBmp  );  i  ++  )  {
									  if  (  pMsg->iTaskId  ==  pShadowMgr->rules_viewDynBmp[i].taskInfo.iTaskId  )  {
										  bFound  =  TRUE;
										  break;
									  }
								  }	
							  }							  		
							  if  (  !bFound  )  {
								  #ifdef  __DEBUG__
								          traceLog(  _T(  "dlgTalk_OnQyComm failed: findTaskInProcessQ failed, iTaskId %d"  ),  pMsg->iTaskId  );
								  #endif
								  goto  errLabel;
							  }

							  //  {	//  2010/09/12
							  if  (  pMgrVar->av.taskInfo.bTaskExists
								  &&  pMgrVar->av.taskInfo.iTaskId  ==  pMsg->iTaskId  
								  &&  pMgrVar->av.taskInfo.ucbVideoConference  )
							  {
								  CAP_IMAGE	*	pImg	=	NULL;
								  int				i;
								
								  for  (  i  =  0;  i  <  mycountof(  pImgs->mems  );  i  ++  )  {
									   pImg  =  &pImgs->mems[i];
									   if  (  pImg->iTaskId  ==  pMsg->iTaskId
										   &&  pImg->idInfo_sender.ui64Id  ==  pMsg->idInfo_sender.ui64Id  )  
									   {
										   //  freeCapImage(  hDlg,  0,  pImg  );
										   int  idc_dst  =  m_var.idc;
										   freeCapImage(  hDlg,  m_var.idc,  pImg,  M_GetDlgItem(  hDlg,  idc_dst  )  );
									   }
								  }

								  QY_MESSENGER_ID	idInfo_sender;
								  idInfo_sender.ui64Id  =  pMsg->idInfo_sender.ui64Id;
								  if  (  !isMemFromActive(  &pMgrVar->videoConference,  &idInfo_sender,  NULL  )  )  {
									  traceLog(  _T(  "skipped: %I64u is not an activeMem"  ),  pMsg->idInfo_sender.ui64Id  );
									  goto  errLabel;
								  }

								  if  (  pMsg->usIndex  >=  mycountof(  pImgs->mems  )  )  goto  errLabel;
								  pImg  =  &pImgs->mems[pMsg->usIndex];
								  //  freeCapImage(  hDlg,  0,  pImg  );
								  int  idc_dst  =  m_var.idc;
								  freeCapImage(  hDlg,  m_var.idc,  pImg,  M_GetDlgItem(  hDlg,  idc_dst  )  );

								  pImg->iW_org  =  pMsg->bih.biWidth;
								  pImg->iH_org  =  pMsg->bih.biHeight;
								  pImg->idInfo_sender.ui64Id  =  pMsg->idInfo_sender.ui64Id;
								  pImg->uiTranNo_openAvDev  =  pMsg->uiTranNo_openAvDev;
								  pImg->usIndex  =  pMsg->usIndex;

								  pImgs->bResized  =  TRUE;
							  }
							  //  }
						  }
					  }

				  }
				
				  //  if  (  drawCapImages(  this->m_hWnd,  m_var.idc,  &m_var.hDc,  m_var.ucbLocalAv,  pMsg,  0,  0,  pBase->m_var.mems_org[0].iW,  pBase->m_var.mems_org[0].iH,  NULL,  pZoneParam,  &m_var.images,  bUseDxSurface  )  )  goto  errLabel;
				  if  (  drawCapImages(  m_hWnd,  m_var.idc,  &m_var.hDc,  NULL,  m_var.ucbLocalAv,  pMsg,  0,  0,  pBaseVar->mems[0].iW,  pBaseVar->mems[0].iH,  NULL,  pZoneParam,  &m_var.images,  bUseDxSurface,  FALSE  )  )  goto  errLabel;
				  if  (  pMsg->uiEventId_lastRecvd  )  {
					  m_var.uiEventId_lastRecvd  =  pMsg->uiEventId_lastRecvd;
				  }  

				  iErr  =  0;
errLabel:
				  return  iErr;
				  
}
