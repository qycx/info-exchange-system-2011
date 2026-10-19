

#include	"stdafx.h"

#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

#include	<dbt.h>
#include	<mmreg.h>
#include	<msacm.h>
#ifndef  __WINCE__
	#include	<fcntl.h>
	#include	<io.h>
#endif
#include	<stdio.h>
#include	<commdlg.h>
#include	<strsafe.h>

#include	<dshow.h>

#ifndef  __WINCE__
	//  #include	<Qedit.h>
	#include	"myQedit.h"
#endif
#include	<Mediaobj.h>
#include	<Dmo.h>

#include	"qmcDmoPublic.h"
#ifndef  __WINCE__
	#include	"qmcVideoCapture_dx.h"
#endif
#include	"myfourcc.h"

#include	"qyCusResTemp.h"

//  #include	"qyMc.h"
#include	"qyGuiCommProc.h"

#include	"tmpCeLib.h"

#include	"qyAvRecordPublic.h"

#include	"myresource.h"

#include	"qyOpenShellCommon.h"
#include	"wallTalkers.h"
#include	"DlgShareDynBmpsProc.h"

#include	"dlgTalkProc.h"
#include	"qmcCmdProc.h"

//  #include	"DlgProgress.h"
#include	"tmpCeLib.h"

#include	"qyComPortEx.h"
#include	"qmcGpsProc.h"

#include	"myDb.h"

#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

#define		MAX_portNo_gps		16



 int  dlgShareDynBmps_refreshShareStatus(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType  )
{
	if  (  !pDLG_shareDynBmps_var  )  return  -1;
	DLG_shareDynBmps_var  &  m_var  =  *(  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;

	if  (  !uiObjType  )  {
		dlgShareDynBmps_refreshShareStatus(  m_hWnd,  &m_var,  CONST_objType_screen  );
		dlgShareDynBmps_refreshShareStatus(  m_hWnd,  &m_var,  CONST_objType_webcam  );
		//  2012/04/17
		dlgShareDynBmps_refreshShareStatus_gps(  m_hWnd,  &m_var  );
		return  0;
	}

	int						iErr		=	-1;
	MC_VAR_isCli			*	pProcInfo	=	(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	int						i;
	int						idc;
	HWND					hCtrl		=	NULL;
	SHARE_dynBmps		*	pShare		=	(  SHARE_dynBmps  *  )dlgShareDynBmps_getShareDynBmpsBySth(  m_hWnd,  &m_var,  uiObjType  );
	QY_MC				*	pQyMc		=	(  QY_MC  *  )pProcInfo->pQyMcParam;
	if  (  !pShare  )  return  -1;

	 QY_DMITEM  *  pItem;	 
	 for  (  pItem  =  pShare->pTable_ctrls,  i  =  0;  pItem->type  !=  -1  &&  i  <  pShare->usCnt;  pItem  ++  )  {
		  
		  if  (  uiObjType  ==  CONST_objType_webcam  )  {
			  if  (  !pShare->mems[i].iMenuId  )  break;
			  pShare->mems[i].var.bShared  =  pShare->mems[i].var.ucbLocalVideoOpen;
			  pShare->mems[i].var.bUsing  =  bWebcamUsing(  pProcInfo,  getMoniker_v(  m_var.pCapStuff,  pShare->mems[i].iMenuId  ),  NULL,  NULL  );

		  }
		  else  if  (  uiObjType  ==  CONST_objType_screen  )  {
				    pShare->mems[i].var.bShared  =  pShare->mems[i].var.ucbSendLocalScreen;
		  }

		  idc  =  (  int  )pItem->pData;
		  hCtrl  =  GetDlgItem(  m_hWnd,  idc  );
		  if  (  !hCtrl  )  goto  errLabel;

		  if  (  pShare->mems[i].var.bUsing  &&  !pShare->mems[i].var.bShared  )  {
			  EnableWindow(  hCtrl,  FALSE  );
			  SetDlgItemText(  m_hWnd,  idc,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_running  )  );
			  }
		  else  {
			    EnableWindow(  hCtrl,  TRUE  );
				if  (  pShare->mems[i].var.bShared  )  SetDlgItemText(  m_hWnd,  idc,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_stopSharing  )  );
				else  SetDlgItemText(  m_hWnd,  idc,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_startSharing  )  );
		  }

		  i  ++  ;
	 }


	iErr  =  0;
errLabel:
	return  iErr;
}


int  dlgShareDynBmps_refreshShareStatus_gps(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var  )
{
	int				iErr	=	-1;
	QY_MC		*	pQyMc	=	QY_GET_GBUF(  );

	if  (  !pDLG_shareDynBmps_var  )  return  -1;
	DLG_shareDynBmps_var  &m_var  =  *(  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;

	int	idc  =  m_var.guiData.iIDC_BUTTON_gps;

	if  (  m_var.share_gps.bShare  )  SetDlgItemText(  m_hWnd,  idc,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_stopSharing  )  );
	else  SetDlgItemText(  m_hWnd,  idc,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_startSharing  )  );

	iErr  =  0;
	return  iErr;
}


 //  SHARE_dynBmps	*	dlgShareDynBmps_getShareDynBmpsBySth(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  int  uiObjType  )
 void  *  dlgShareDynBmps_getShareDynBmpsBySth(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  int  uiObjType  )
{
	if  (  !pDLG_shareDynBmps_var  )  return  NULL;
	DLG_shareDynBmps_var  &m_var  =  *(  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;

	switch  (  uiObjType  )  {
			case  CONST_objType_screen:
				  return  &m_var.shares[0];
		    case  CONST_objType_webcam:
				  return  &m_var.shares[1];
			default:
					break;
	}
	return  NULL;
}

  LRESULT  dlgShareDynBmps_OnQyComm( HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  WPARAM wParam, LPARAM lParam )
{
	if  (  !pDLG_shareDynBmps_var  )  return  -1;
	DLG_shareDynBmps_var  &  m_var  =  *(  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;


	long				lRet				=					-1;
	QY_WMBUF_COMM	*	pComm				=					( QY_WMBUF_COMM * )lParam;
	QY_MC			*	pQyMc				=					QY_GET_GBUF(  );
	int					i					=					0;
	int					j					=					0;
	MC_VAR_isCli	*	pProcInfo			=					(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;

	if  (  !pComm  )  return  -1;

	switch  (  pComm->uiType  )  {
			case  CONST_misMsgType_procVideo_qmc:  {
				  MIS_MSG_procVideo_qmc  *  pMsg			=  (  MIS_MSG_procVideo_qmc  *  )pComm;
				  BOOL						bUseDxSurface	=	m_var.bUseDirectX;	
				  ZONE_PARAM			*	pZoneParam		=	NULL;

#if  0
				  {
				  QY_PLAYER				*	pPlayer;

				  if  (  pMsg->index_player  <  0  ||  pMsg->index_player  >=  pProcInfo->av.usCnt_players  )  goto  errLabel;
				  pPlayer  =  &pProcInfo->av.pPlayers[pMsg->index_player];
				  pZoneParam  =  &pPlayer->video.m_var.zoneParam;
				  }
#endif
				  BOOL	bExists  =  FALSE;
				  for  (  i  =  0;  !bExists  &&  i  <  mycountof(  m_var.shares  );  i  ++  )  {
					   for  (  j  =  0;  j  <  m_var.shares[i].usCnt;  j  ++  )  {
						    SHARE_dynBmp_mem  *  pMem  =  &m_var.shares[i].mems[j];							
							if  (  pMem->var.bShared  &&  pMem->var.iTaskId  ==  pMsg->iTaskId  )  {
								pZoneParam  =  &pMem->var.zoneParam;
								bExists  =  TRUE;
								break;
							}
					   }
				  }
				  if  (  !pZoneParam  )  {
					  #ifdef  __DEBUG__
							  traceLog(  _T(  "dlgShareQynBmps, OnQyPostComm failed, pZoneParam is null"  )  );
					  #endif
					  goto  errLabel;
				  }
				  						
				  BOOL			bZoneOk		=	FALSE;				  
				  if  (  pZoneParam->index_capImage  >=  0  &&  pZoneParam->index_capImage  <  mycountof(  m_var.images.mems  )  )  {
					  CAP_IMAGE	*	pImg	=	&m_var.images.mems[pZoneParam->index_capImage];
					  if  (  pImg->idInfo_sender.ui64Id  ==  pMsg->idInfo_sender.ui64Id  
						  &&  pImg->uiTranNo_openAvDev  ==  pMsg->uiTranNo_openAvDev
						  &&  pImg->usIndex  ==  pMsg->usIndex  )  
					  {
						  bZoneOk  =  TRUE;
					  }
				  }											   
				  //				
				  //  if  (  !bZoneOk  )  freeCapImages(  this,  m_var.idc,  NULL,  &m_var.images  );
				  if  (  !bZoneOk  )  {							
					  memset(  pZoneParam,  0,  sizeof(  pZoneParam[0]  )  );
					  //					  
					  BOOL	bExists  =  FALSE;
					  for  (  i  =  0;  !bExists  &&  i  <  mycountof(  m_var.shares  );  i  ++  )  {
						   for  (  j  =  0;  j  <  m_var.shares[i].usCnt;  j  ++  )  {
						   	    SHARE_dynBmp_mem  *  pMem  =  &m_var.shares[i].mems[j];					
								if  (  pMem->var.bShared  &&  pMem->var.iTaskId  ==  pMsg->iTaskId  )  {
									bExists  =  TRUE;
									break;
								}
						   }
					  }	
					  if  (  !bExists  )  goto  errLabel;				  					  
				  }
				  if  (  drawCapImages(  m_hWnd,  m_var.idc,  &m_var.hDc,  NULL,  FALSE,  pMsg,  0,  0,  m_var.iW_pic,  m_var.iH_pic,  NULL,  pZoneParam,  &m_var.images,  bUseDxSurface,  FALSE  )  )  goto  errLabel;

				  }				  
				  break;
			case  CONST_misMsgType_input:  {
				  MIS_MSG_INPUT		*	pMsg		=	(  MIS_MSG_INPUT  *  )pComm;
				  IM_CONTENTU		*	pContent	=	(  IM_CONTENTU  *  )&pMsg->data;

				  switch  (  pContent->uiType  )  {
						  case  CONST_imCommType_refreshDynBmps:
							    if  (  pContent->refreshDynBmps.ucbResp  )  {
									m_var.tLastModifiedTime_ok  =  pContent->refreshDynBmps.tLastModifiedTime;
								}
							    break;
						  case  CONST_imCommType_verifyViewDynBmp:
								#ifdef  __DEBUG__
										traceLog(  _T(  "verifyViewDynBmp resp"  )  );
								#endif
								if  (  !pContent->verifyViewDynBmp.ucbResp  )  {
									#ifdef  __DEBUG__
											traceLog(  _T(  "verifyViewDynBmp resp failed, ucbResp is false"  )  );
									#endif
									goto  errLabel;
								}
								if  (  !pContent->verifyViewDynBmp.idInfo_viewer.ui64Id  )  goto  errLabel;
								
								//
								for  (  j  =  0;  j  <  mycountof(  m_var.recvdReqs  );  j  ++  )  {
									 if  (  !m_var.recvdReqs[j].dwTickCnt  )  continue;
									 if  (  m_var.recvdReqs[j].pMsg->task.addr_logicalPeer.idInfo.ui64Id  ==  pContent->verifyViewDynBmp.idInfo_viewer.ui64Id  )  break;
								}
								if  (  j  ==  mycountof(  m_var.recvdReqs  )  )  goto  errLabel;
								
								//																
								if  (  !isRuleCmdPermit(  pContent->verifyViewDynBmp.uiCmd  )  )  {

									m_var.recvdReqs[j].dwTickCnt  =  0;		//  这里要记得清除

									qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp: viewer %I64u, access denied"  ),  pContent->verifyViewDynBmp.idInfo_viewer.ui64Id  );
									goto  errLabel;
								}

								if  (  m_var.recvdReqs[j].uiObjType  )  {
									//
									SHARE_dynBmps	*	pShare;														
									pShare  =  (  SHARE_dynBmps  *  )dlgShareDynBmps_getShareDynBmpsBySth(  m_hWnd,  &m_var,  m_var.recvdReqs[j].uiObjType  );
									if  (  !pShare  )  goto  errLabel;							    

									i  =  m_var.recvdReqs[j].index_pShare_mem;
									//
									if  (  i  >=  pShare->usCnt  )  goto  errLabel;
									if  (  !pShare->mems[i].var.bShared  )  goto  errLabel;
									//
									{
										MIS_MSG_TASK	*	pMsg  =  &m_var.recvdReqs[j].pMsg->task;								
								
										if  (  pMsg->uiTaskType  ==  CONST_imTaskType_viewDynBmp  )  {
											//
											if  (  procSendAvReplyInfo(  (  MIS_CNT  *  )pMsg->pMisCnt,  m_hWnd,  pMsg,  TRUE,  pShare->mems[i].var.iIndex_sharedObj,  &pMsg->addr_logicalPeer  )  )  goto  errLabel;
											}
										else  {
											  #ifdef  __DEBUG__
													  traceLog(  _T(  "dlgShare: unknown recvd taskType"  )  );
											  #endif
											  goto  errLabel;
										}
									}
									//
									}
								else  {
									  if  (  !m_var.share_gps.bShare  )  {
										  goto  errLabel;
									  }
									  MIS_MSG_TASK  *  pMsg  =  &m_var.recvdReqs[j].pMsg->task;

									  if  (  pMsg->uiTaskType  !=  CONST_imTaskType_viewGps  )  goto  errLabel;

									  if  (  procSendGpsReplyInfo(  (  MIS_CNT  *  )pMsg->pMisCnt,  m_hWnd,  pMsg,  TRUE,  m_var.share_gps.var.iIndex_sharedObj,  &pMsg->addr_logicalPeer  )  )  goto  errLabel;
								}

								//
								m_var.recvdReqs[j].dwTickCnt  =  0;		//  完成了要清除
								//
								qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp: viewer %I64u, accepted. i %d"  ),  pContent->verifyViewDynBmp.idInfo_viewer.ui64Id,  i  );
								//
							    break;
						  default:
								  break;
				  }
										
				  }
				  break;
			case  CONST_misMsgType_task:  {
				  MIS_MSG_TASK		*	pMsg		=	(  MIS_MSG_TASK  *  )pComm;
				  IM_CONTENTU		*	pContent	=	(  IM_CONTENTU  *  )&pMsg->data.buf;
				  SHARE_dynBmps		*	pShare		=	NULL;

				  switch  (  pContent->uiType  )  {
					      case  CONST_imCommType_transferAvInfo:
							    pShare  =  (  SHARE_dynBmps  * )dlgShareDynBmps_getShareDynBmpsBySth(  m_hWnd,  &m_var,  pContent->transferAvInfo.viewDynBmp.uiObjType  );
								if  (  !pShare  )  goto  errLabel;							    
								
								if  (  pContent->transferAvInfo.viewDynBmp.usIndex  >=  pShare->usCnt  )  goto  errLabel;
								//  if  (  pProcInfo->cfg.policy.ucbDistinguishSharedWebcams  )  
								if  (  m_var.pMisCnt->imRules.ucbDistinguishSharedWebcams  )  
								{
									i  =  pContent->transferAvInfo.viewDynBmp.usIndex;									
									if  (  !pShare->mems[i].var.bShared  )  {
										traceLogA(  "Need to return status_stopped."  );
										break;
									}								
									}
								else  {  //  2011/10/15. 这里不再区分不同的共享摄像机。
									  for  (  i  =  0;  i  <  pShare->usCnt;  i  ++  )  {
										   if  (  pShare->mems[i].var.bShared  )  break;
									  }
									  if  (  i  ==  pShare->usCnt  )  {
										  traceLog(  _T(  "no shared webcam"  )  );
										  break;
									  }
								}

							#if  0		//  2011/10/31. 不直接发送响应包，因为要发送到服务器上去校验下
								if  (  procSendAvReplyInfo(  (  MIS_CNT  *  )pMsg->pMisCnt,  this->m_hWnd,  pMsg,  TRUE,  pShare->mems[i].var.iIndex_sharedObj,  &pMsg->addr_logicalPeer  )  )  goto  errLabel;
							#endif

								DWORD  dwTickCnt_cur;  dwTickCnt_cur	=	GetTickCount(  );
								for  (  j  =  0;  j  <  mycountof(  m_var.recvdReqs  );  j  ++  )  {
									 if  (  !m_var.recvdReqs[j].dwTickCnt  )  break;
									 if  (  m_var.recvdReqs[j].pMsg->task.addr_logicalPeer.idInfo.ui64Id  ==  pMsg->addr_logicalPeer.idInfo.ui64Id  )  {
										 #ifdef  __DEBUG__
												 traceLog(  _T(  "recv req again"  )  );
										 #endif
										 break;
									 }
									 if  (  dwTickCnt_cur  -  m_var.recvdReqs[j].dwTickCnt  >  5000  )  {
										 m_var.recvdReqs[j].dwTickCnt  =  0;		//  将dwTickCnt设为0，表明该buf已经回收了
										 break;
									 }
								}
								if  (  j  ==  mycountof(  m_var.recvdReqs  )  )  {
									#ifdef  __DEBUG__
											traceLog(  _T(  "no recvdReqBuf available"  )  );
									#endif
									qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp: warning: no recvdReqBuf available"  )  );
									goto  errLabel;
								}
								if  (  !m_var.recvdReqs[j].dwTickCnt  )  {		//  只有dwTickCnt为0的包才表明是要填充的
									memcpy(  m_var.recvdReqs[j].pMsg,  pMsg,  sizeof(  pMsg[0]  )  );
									m_var.recvdReqs[j].uiObjType  =  pContent->transferAvInfo.viewDynBmp.uiObjType;
									m_var.recvdReqs[j].index_pShare_mem  =  i;
									m_var.recvdReqs[j].dwTickCnt  =  dwTickCnt_cur;
								}

								MACRO_prepareForTran(  );
								VERIFY_viewDynBmp	req;
								int					len;

								memset(  &req,  0,  sizeof(  req  )  );
								req.uiType  =  CONST_imCommType_verifyViewDynBmp;

								req.idInfo_viewer.ui64Id  =  pMsg->addr_logicalPeer.idInfo.ui64Id;

								len  =  sizeof(  req  );
								//
								postMsg2Mgr_mc(  m_var.pMisCnt,  NULL,  CONST_misMsgType_req,  0,   CONST_qyCmd_sendVDevReq,  tStartTran,  uiTranNo,  0,  (  char  *  )&req,  len,  NULL,  0,  0,  NULL,  0  ); 

								qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp: to verifyViewer %I64u. j %d"  ),  req.idInfo_viewer.ui64Id,  j  );

								//
							    break;
						  case  CONST_imCommType_taskProcReq:
							    pShare  =  (  SHARE_dynBmps  *  )dlgShareDynBmps_getShareDynBmpsBySth(  m_hWnd,  &m_var,  pContent->taskProcReq.viewDynBmp.uiObjType  );
								if  (  !pShare  )  goto  errLabel;							    							

								if  (  pContent->taskProcReq.viewDynBmp.usIndex  >=  pShare->usCnt  )  goto  errLabel;
								i  =  pContent->taskProcReq.viewDynBmp.usIndex;
								if  (  !pShare->mems[i].var.bUsing  ||  !pShare->mems[i].var.bShared  )  {									
									traceLogA(  "not shared."  );
									break;
								}
								QY_SHARED_OBJ	*	pSharedObj;
								pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pShare->mems[i].var.iIndex_sharedObj  );
								if  (  !pSharedObj  )  goto  errLabel;
								removeFromMsgrs_sendLocalAv(  pProcInfo,  m_var.pMisCnt,  &pMsg->data.route.idInfo_from,  pSharedObj  );
								qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp: removeFromMsgrs_sendLocalAv, %I64u"  ),  pMsg->data.route.idInfo_from.ui64Id  );
							    break;

								//  
						  case  CONST_imCommType_transferGpsInfo:	{  //  2012/04/20
							    if  (  !m_var.share_gps.bShare  )  {
								    #ifdef  __DEBUG__
											traceLog(  _T(  "dlgShare: gps is not shared"  )  );
									#endif
									goto  errLabel;
								}

								//  2011/10/31. 不直接发送响应包，因为要发送到服务器上去校验下

								DWORD  dwTickCnt_cur;  dwTickCnt_cur	=	GetTickCount(  );
								for  (  j  =  0;  j  <  mycountof(  m_var.recvdReqs  );  j  ++  )  {
									 if  (  !m_var.recvdReqs[j].dwTickCnt  )  break;
									 if  (  m_var.recvdReqs[j].pMsg->task.addr_logicalPeer.idInfo.ui64Id  ==  pMsg->addr_logicalPeer.idInfo.ui64Id  )  {
										 #ifdef  __DEBUG__
												 traceLog(  _T(  "recv req again"  )  );
										 #endif
										 break;
									 }
									 if  (  dwTickCnt_cur  -  m_var.recvdReqs[j].dwTickCnt  >  5000  )  {
										 m_var.recvdReqs[j].dwTickCnt  =  0;		//  将dwTickCnt设为0，表明该buf已经回收了
										 break;
									 }
								}
								if  (  j  ==  mycountof(  m_var.recvdReqs  )  )  {
									#ifdef  __DEBUG__
											traceLog(  _T(  "no recvdReqBuf available"  )  );
									#endif
									qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp: warning: no recvdReqBuf available"  )  );
									goto  errLabel;
								}
								if  (  !m_var.recvdReqs[j].dwTickCnt  )  {		//  只有dwTickCnt为0的包才表明是要填充的
									memcpy(  m_var.recvdReqs[j].pMsg,  pMsg,  sizeof(  pMsg[0]  )  );
									m_var.recvdReqs[j].uiObjType  =  0;
									m_var.recvdReqs[j].index_pShare_mem  =  0;
									m_var.recvdReqs[j].dwTickCnt  =  dwTickCnt_cur;
								}

								MACRO_prepareForTran(  );
								VERIFY_viewDynBmp	req;
								int					len;

								memset(  &req,  0,  sizeof(  req  )  );
								req.uiType  =  CONST_imCommType_verifyViewDynBmp;

								req.idInfo_viewer.ui64Id  =  pMsg->addr_logicalPeer.idInfo.ui64Id;

								len  =  sizeof(  req  );
								//
								postMsg2Mgr_mc(  m_var.pMisCnt,  NULL,  CONST_misMsgType_req,  0,   CONST_qyCmd_sendVDevReq,  tStartTran,  uiTranNo,  0,  (  char  *  )&req,  len,  NULL,  0,  0,  NULL,  0  ); 

								qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp: to verifyViewer %I64u. j %d"  ),  req.idInfo_viewer.ui64Id,  j  );

								//
								}
							    break;

								//
						  default:
								  #ifdef  __DEBUG__
										  traceLog(  _T(  "dlgShare, unprocessed contentType"  )  );
								  #endif
								  break;
				  }
				
				  }
				  break;
			case  CONST_qyWmParam_chkTask:  {
				  BOOL	bExists  =  FALSE;
				  for  (  i  =  0;  !bExists  &&  i  <  mycountof(  m_var.shares  );  i  ++  )  {
					   for  (  j  =  0;  j  <  m_var.shares[i].usCnt;  j  ++  )  {
						    SHARE_dynBmp_mem  *  pMem  =  &m_var.shares[i].mems[j];
							if  (  pMem->var.bShared  &&  pMem->var.iTaskId  ==  pComm->u.chkTask.iTaskId  )  {
								//  task is active
								bExists  =  TRUE;
								break;
							}
					   }
				  }
				  //  2012/04/19
				  if  (  !bExists  )  {
					  if  (  m_var.share_gps.bShare  )  {
						  if  (  m_var.share_gps.var.iTaskId  ==  pComm->u.chkTask.iTaskId  )  {
							  //  task is active;
							  bExists  =  TRUE;
						  }
					  }
				  }
				  //
				  if  (  !bExists  )  pComm->u.chkTask.bNotExists  =  TRUE;
				  pComm->u.chkTask.bChked  =  TRUE;		//  2013/03/07
				  }
				  break;
			case  CONST_qyWmParam_chkSharedObject:  {
				  BOOL  bExists  =  FALSE;
				  for  (  i  =  0;  !bExists  &&  i  <  mycountof(  m_var.shares  );  i  ++  )  {
					   for  (  j  =  0;  j  <  m_var.shares[i].usCnt;  j  ++  )  {
						    SHARE_dynBmp_mem  *  pMem  =  &m_var.shares[i].mems[j];
							if  (  pMem->var.bShared  &&  pMem->var.iIndex_sharedObj  ==  pComm->u.chkSharedObject.iIndex_sharedObject  )  {
								//  sharedObj is in use
								bExists  =  TRUE;
								break;
							}
					   }
				  }
				  //  2012/04/19
				  if  (  !bExists  )  {
					  if  (  m_var.share_gps.bShare  )  {
						  if  (  m_var.share_gps.var.iIndex_sharedObj  ==  pComm->u.chkSharedObject.iIndex_sharedObject  )  {
							  //
							  bExists  =  TRUE;
						  }
					  }
				  }
				  //
				  if  (  !bExists  )  pComm->u.chkSharedObject.bNotExists  =  TRUE;
				  }
				  break;
#if  0
			case  CONST_qyWmParam_getCapImageInfo:  {
				  BOOL	bExists  =  FALSE;
				  for  (  i  =  0;  !bExists  &&  i  <  mycountof(  m_var.shares  );  i  ++  )  {
					   for  (  j  =  0;  j  <  m_var.shares[i].usCnt;  j  ++  )  {
						    SHARE_dynBmp_mem  *  pMem  =  &m_var.shares[i].mems[j];
							if  (  pMem->var.bShared  &&  pMem->var.iTaskId  ==  pComm->u.getCapImageInfo.iTaskId  )  {
								bExists  =  TRUE;
							    break;
							}
					   }
				  }	
				  if  (  !bExists  )  {
					  pComm->u.getCapImageInfo.bImageInvalid  =  TRUE;
					  break;
				  }
				  }
				  break;
#endif
			default:
					break;
	}

	lRet  =  QY_RC_WMOK;

errLabel:

	return  lRet;
}

LRESULT  dlgShareDynBmps_OnQyPostComm( HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  WPARAM wParam, LPARAM lParam )
{
	if  (  !pDLG_shareDynBmps_var  )  return  -1;
	DLG_shareDynBmps_var  &  m_var  =  *(  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;

	long				lRet			=		-1;
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	MC_VAR_isCli		*	pProcInfo		=	(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;

	switch  (  wParam  )  {
			case  CONST_qyWmParam_guiMsgArrive:  
				  doWnd_guiMsgArrive(  pProcInfo,  lParam,  m_hWnd,  TRUE,  m_var.pMsgBuf_doWnd_guiMsgArrive  );
				  break;
				  			
			case  CONST_qyWmParam_avRecord_start:  {				  
				  int						iIndex_sharedObj;
				  int						iIndex_sharedObjUsr		=	0;
				  QY_SHARED_OBJ			*	pSharedObj				=	NULL;
				  int						iIndex_screenCapProcInfo;
				  CAP_procInfo_screen	*	pScreenCapProcInfo		=	NULL;
				  COMPRESS_VIDEO		*	pCompressVideo			=	NULL;
				  unsigned  int				uiTaskType;

				  OutputDebugString(  _T(  "avRecord_start\n"  )  );

				  iIndex_sharedObj  =  newSharedObjIndex(  m_hWnd,  &iIndex_sharedObjUsr,  NULL  );
				  if  (  iIndex_sharedObj  <  0  )  goto  errLabel;
				  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
				  if  (  !pSharedObj  )  goto  errLabel;
				  iIndex_screenCapProcInfo  =  newCapProcInfoBmpIndex(  pProcInfo,  iIndex_sharedObj  );	
				  pScreenCapProcInfo  =  (  CAP_procInfo_screen  *  )getCapBmpBySth(  pProcInfo,  iIndex_screenCapProcInfo,  0  );
				  if  (  !pScreenCapProcInfo  )  goto  errLabel;
				  pScreenCapProcInfo->uiType  =  CONST_capType_screen;
				  pScreenCapProcInfo->iIndex_sharedObj  =  iIndex_sharedObj;
				  pScreenCapProcInfo->uiTranNo_sharedObj  =  pSharedObj->uiTranNo;
				  pCompressVideo  =  &pScreenCapProcInfo->compressVideo;
				  
				  //
				  pSharedObj->bDirectX  =  bDirectX_avRecord(  );
				  pSharedObj->bRemoteAssist  =  bRemoteAssist_avRecord(  );		//  2008/11/09, ÊÇ·ñÔ¶³ÌÐ­Öú				
				  pSharedObj->iIndex_capBmp  =  iIndex_screenCapProcInfo;
				  int  iIndex_dynBmp  =  getiParam_avRecord(  );
				  
				  //
				  uiTaskType  =  CONST_imTaskType_shareDynBmp;

				  //
				  SHARE_dynBmps	*	pShare  =  (  SHARE_dynBmps  *  )dlgShareDynBmps_getShareDynBmpsBySth(  m_hWnd,  &m_var,  CONST_objType_screen  );
				  if  (  !pShare  )  goto  errLabel;
				  if  (  iIndex_dynBmp  <  0  ||  iIndex_dynBmp  >=  pShare->usCnt  )  goto  errLabel;
				  pShare->mems[iIndex_dynBmp].var.iIndex_sharedObj  =  iIndex_sharedObj;
				  pShare->mems[iIndex_dynBmp].var.ucbSendLocalScreen  =  TRUE;	

				  //  2011/08/07
				  #if  0
						POLICY_av	policyAv;
						if  (  getPolicyAv(  FALSE,  0,  &policyAv  )  )  goto  errLabel;
				  #endif
				  AV_COMPRESSOR_CFG		screenCompressor;
				  if  (  myGetAvCompressorCfg(  CONST_capType_screen,  0,  FALSE,  0,  &screenCompressor  )  )  goto  errLabel;

				  //
				  RECT	selectedRc;		//  ÕâÀïÒª×¢Òâ£ºbmp¿í¶ÈÊÇselectedRcµÄ¿í¶È+1¡£³¤¶ÈÒ²ÊÇÈç´Ë¡£

				  selectedRc  =  getSelectedRect(  );				  
				  makeBmpInfoHeader_rgb(  24,  selectedRc.right  -  selectedRc.left  +  1,  selectedRc.bottom  -  selectedRc.top  +  1,  &pCompressVideo->vh_decompress.bih  );
				  if  (  initCompressVideo(  pProcInfo,  NULL,  CONST_capType_screen,  &screenCompressor.video,  FALSE,  0,  getSize_qyAvRecord(  ),  pCompressVideo  )  )  {
					  qyShowHint(  _T(  "Initialize video compress failed!"  )  );  goto  errLabel;
				  }

				  //  ³õÊ¼»¯avRecord
	
				  //  »¹ÒªÆô¶¯av
				  setFps_capScreen(  screenCompressor.video.common.usMaxFps_toShareBmp  );
				  startAvRecord(  pProcInfo,  iIndex_screenCapProcInfo,  AfxGetMainWnd(  )->m_hWnd  );

				  //
				  TALKER_rule_dynBmp	rule_dynBmp;
				  //  QIS_DYN_BMP	dynBmp;
				  memset(  &rule_dynBmp,  0,  sizeof(  rule_dynBmp  )   );
				  rule_dynBmp.uiType  =  CONST_vwRuleType_dynBmp;
				  rule_dynBmp.dynBmp.uiObjType  =  pShare->uiObjType;
				  rule_dynBmp.dynBmp.usIndex  =  iIndex_dynBmp;
				  if  (  procSendAvInfo(  m_var.pMisCnt,  m_hWnd,  FALSE,  uiTaskType,  NULL,  NULL,  NULL,  pCompressVideo,  NULL,  iIndex_sharedObj,  iIndex_sharedObjUsr,  (  TALKER_ruleU  *  )&rule_dynBmp,  &pShare->mems[iIndex_dynBmp].var.iTaskId,  NULL  )  )  goto  errLabel;

				  //  2010/09/09
				  setCurSharedObjUsr(  iIndex_sharedObj,  m_hWnd  );


				  //
				  mytime(  &m_var.tLastModifiedTime  );

				  dlgShareDynBmps_refreshShareStatus(  m_hWnd,  &m_var,  CONST_objType_screen  );

				  }
				  break;

			case  CONST_qyWmParam_gps:  {
				  CComPortEx  *  pPort  =  (  CComPortEx  *  )m_var.pComPort_gps;
				  if  (  !pPort  )  goto  errLabel;
				  //
				  if  (  pPort->m_var.dwTickCnt_modified_gpsPos  ==  m_var.share_gps.var.dwTickCnt_modified_gpsPos  )  break;
				  if  (  getGpsPos(  pPort,  &m_var.share_gps.var.gpsPos,  &m_var.share_gps.var.dwTickCnt_modified_gpsPos  )  )  goto  errLabel;
				  //
				  TCHAR	tBuf[256]  =  _T(  ""  );
				  if  (  pProcInfo->cfg.ucbTestGps  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Test: "  )  );
				  gps_DisplayStr(  &m_var.share_gps.var.gpsPos,  tBuf  +  lstrlen(  tBuf  ),  mycountof(  tBuf  )  -  lstrlen(  tBuf  )  );
				  SetDlgItemText(  m_hWnd,  m_var.guiData.iIDC_STATIC_gpsStatus,  tBuf  );

				  }
				  //
				  break;

			default:
					break;
	}
	
errLabel:

	return  lRet;

}

 int  dlgShareDynBmps_chkSharedObj(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  int  iIndex_sharedObj  )
{
	if  (  !pDLG_shareDynBmps_var  )  return  -1;
	DLG_shareDynBmps_var  &  m_var  =  *(  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;

	int				iErr		=	-1;
	MC_VAR_isCli  *  pProcInfo	=	QY_GET_procInfo_isCli(  );

	//  int				i;
	int					j;
	QY_SHARED_OBJ	*	pSharedObj;
	time_t				t;				mytime(  &t  );

	
	if  (  !(  pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  )  )  )  goto  errLabel;

	if  (  pSharedObj->curRoute_sendLocalAv.videoConference_idInfo_to.ui64Id  )  {
		iErr  =  0;  goto  errLabel;
	}
	
	if  (  pSharedObj->curRoute_sendLocalAv.route.idInfo_to.ui64Id  )  {
		if  (  t  -  pSharedObj->routeInfo.tModifiedTime  >  120  
			&&  t  -  pSharedObj->routeInfo.tRecvTime_lastResp  >  300  )  
		{				
			removeFromMsgrs_sendLocalAv(  pProcInfo,  m_var.pMisCnt,  &pSharedObj->curRoute_sendLocalAv.route.idInfo_to,  pSharedObj  );
			qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp: removeFromMsgrs_sendLocalAv, %I64u"  ),  pSharedObj->curRoute_sendLocalAv.route.idInfo_to.ui64Id  );
		}
	}

	for  (  j  =  0;  j  <  mycountof(  pSharedObj->curRoute_sendLocalAv.route.mems_to  );  j  ++  )  {
		 if  (  !pSharedObj->curRoute_sendLocalAv.route.mems_to[j].idInfo.ui64Id  )  continue;		
		 if  (  t  -  pSharedObj->routeInfo.mems[j].tModifiedTime  >  120
			 &&  t  -  pSharedObj->routeInfo.mems[j].tRecvTime_lastResp  >  300  )
		 {		
			 removeFromMsgrs_sendLocalAv(  pProcInfo,  m_var.pMisCnt,  &pSharedObj->curRoute_sendLocalAv.route.mems_to[j].idInfo,  pSharedObj  );
			 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "sharedDynBmp: removeFromMsgrs_sendLocalAv, %I64u"  ),  pSharedObj->curRoute_sendLocalAv.route.mems_to[j].idInfo.ui64Id  );
		 }
	}

	iErr  =  0;
errLabel:
	return  iErr;

}

int  dlgShareDynBmps_toShareWebcam(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  int  index  )
{
	if  (  !pDLG_shareDynBmps_var  )  return  -1;
	DLG_shareDynBmps_var	&	m_var		=	*(  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;

	int		iErr	=	-1;

	SHARE_dynBmps	*	pShare;
	pShare  =  (  SHARE_dynBmps  *  )dlgShareDynBmps_getShareDynBmpsBySth(  m_hWnd,  &m_var,  CONST_objType_webcam  );
	if  (  !pShare  )  return  -1;
	if  (  index  <  0  ||  index  >=  pShare->usCnt  )  return  -1;
	
	if  (  !pShare->mems[index].iMenuId  )  return  -1;

	//  2011/10/15 在点击启动共享后，就可以不必保持置前状态了
	if  (  m_var.bNeed_shareWebcamInConference  )  {
		m_var.bNeed_shareWebcamInConference  =  FALSE;
	}

	//
	if  (  pShare->mems[index].var.ucbLocalVideoOpen  )  {
		dlgShareDynBmps_closeTaskAv(  m_hWnd,  &m_var,  pShare->uiObjType,  index  );

		mytime(  &m_var.tLastModifiedTime  );

		iErr  =  0;  goto  errLabel;
	}

	QY_MC						*	pQyMc					=	QY_GET_GBUF(  );
	MC_VAR_isCli				*	pProcInfo				=	(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	int								iIndex_sharedObj		=	-1;
	int								iIndex_sharedObjUsr		=	-1;
	QY_SHARED_OBJ				*	pSharedObj				=	NULL;
	int								iIndex_capBmp			=	-1;
	CAP_procInfo_video			*	pCapBmp					=	NULL;
	COMPRESS_VIDEO				*	pCompressVideo			=	NULL;	
	int								iIndex_shmCmd			=	-1;
	QM_SHM_CMD					*	pShmCmd					=	NULL;
	VIDEO_COMPRESSOR_CFG			videoCompressor;
	unsigned  int					uiTaskType				=	0;

	#ifdef  __DEBUG__
	#endif
	
	iIndex_sharedObj  =  newSharedObjIndex(  m_hWnd,  &iIndex_sharedObjUsr,  NULL  );
	if  (  iIndex_sharedObj  <  0  )  goto  errLabel;
	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;
	//  pSharedObj->uiCapType  =  CONST_capType_av;
	pSharedObj->uiType  =  CONST_sharedObjType_webcam;
	iIndex_capBmp  =  newCapProcInfoBmpIndex(  pProcInfo,  iIndex_sharedObj  );
	pCapBmp  =  (  CAP_procInfo_video  *  )getCapBmpBySth(  pProcInfo,  iIndex_capBmp,  0  );
	if  (  !pCapBmp  )  goto  errLabel;
	pCapBmp->uiType  =  CONST_capType_av;
	pCapBmp->iIndex_sharedObj  =  iIndex_sharedObj;
	pCapBmp->uiTranNo_sharedObj  =  pSharedObj->uiTranNo;
	pCompressVideo  =  &pCapBmp->compressVideo;
	//
	iIndex_shmCmd  =  newShmCmdIndex(  pProcInfo,  iIndex_sharedObj  );
	pShmCmd  =  getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  iIndex_shmCmd  );
	if  (  !pShmCmd  )  goto  errLabel;
		    
	//
	pSharedObj->iIndex_capBmp  =  iIndex_capBmp;
	pSharedObj->iIndex_shmCmd  =  iIndex_shmCmd;


	//
	uiTaskType  =  CONST_imTaskType_shareDynBmp;

	//  2011/08/07
#if  0
	POLICY_av	policyAv;
	if  (  getPolicyAv(  FALSE,  0,  &policyAv  )  )  goto  errLabel;
#endif
	AV_COMPRESSOR_CFG	webcamCompressor;
	if  (  myGetAvCompressorCfg(  CONST_capType_av,  CONST_subCapType_webcam,  0,  0,  &webcamCompressor  )  )  goto  errLabel;

	//  2009/06/04
	//  memcpy(  &videoCompressor,  &pProcInfo->cfg.policy.taskAv_pc.avCompressor.video,  sizeof(  videoCompressor  )  );
	memcpy(  &videoCompressor,  &webcamCompressor.video,  sizeof(  videoCompressor  )  );
	//  2012/06/12
	videoCompressor.common.uiCapType  =  CONST_capType_av;
	videoCompressor.common.uiSubCapType  =  CONST_subCapType_webcam;

	//
	if  (  pCapBmp->bCapDevConnected  )  {
		qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CDlgSharedWebcams::toShareWebcam failed, bCapDevConntected true."  )  );
		goto  errLabel;
	}

	//  CDlgShareDynBmps	*	pDlg	=	this;

	TCHAR	displayName[MAX_monikerDisplayNameLen  +  1]	=	_T(  ""  );	
	if  (  !bWebcamUsing(  pProcInfo,  getMoniker_v(  m_var.pCapStuff,  pShare->mems[index].iMenuId  ),  NULL,  NULL  )  )  {
		if  (  getMonikerDisplayName(  getMoniker_v(  m_var.pCapStuff,  pShare->mems[index].iMenuId  ),  displayName,  mycountof(  displayName  )  )  )  displayName[0]  =  0;
	}

	if  (  !displayName[0]  )  goto  errLabel;

#ifndef  __SUPPORT_subProcessToStartAvCall__
	{
		CWaitCursor		cur;

		if  (  openLocalVideo(  (  MC_VAR_common  *  )pProcInfo,  pProcInfo->cfg.policy.video.uiCamCapType,  displayName,  NULL,  &videoCompressor,  NULL,  iIndex_sharedObj,  NULL  )  )  {
			#ifdef  __DEBUG__
					traceLogA(  "CDlgSharedWebcamps::toShare: openLocalVideo failed."  );
			#endif		
			goto  errLabel;
		}
		
		pShare->mems[index].var.iIndex_sharedObj  =  iIndex_sharedObj;
		pShare->mems[index].var.ucbLocalVideoOpen  =  TRUE;

		//  2011/07/29	
		if  (  startQThreadToShareAv(  pProcInfo,  iIndex_sharedObj,  FALSE  )  )  {
			goto  errLabel;
		}
		
		
	}
#else

	{
		//
		DWORD					dwProcessId;
		TCHAR	tBuf[256];
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "-c%s%u -a%s"  ),  CONST_qmCmdLine_av,  pSharedObj->uiTranNo,  pQyMc->appParams.appObjPrefix  );    
		if  (  doCmdBySubProcess(  0,  tBuf,  NULL,  &pSharedObj->hProcess,  &dwProcessId  )  )  goto  errLabel;

		if  (  lstrlen(  devicePath  )  >=  mycountof(  pShmCmd->path  )  )  goto  errLabel;
		lstrcpyn(  pShmCmd->path,  devicePath,  mycountof(  pShmCmd->path  )  );
		pShmCmd->hWnd_task  =  pDlg->m_hWnd;
		pShmCmd->dwProcessId  =  dwProcessId;
		pShmCmd->iIndex_sharedObj  =  iIndex_sharedObj;
		pShmCmd->uiTranNo_sharedObj  =  pSharedObj->uiTranNo;		

		//
		//  pDlg->m_var.av.ucbLocalVideoOpen  =  TRUE;

		//
		{
			CDlgProgress	dlg(  pDlg  );
			dlg.bSetDlgInfo(  _T(  "Please waiting"  ),  NULL,  30,  iIndex_shmCmd  ); 

			//  traceLogA(  "if task is not ready, cancel the task by clear shmCmd, and the subprocess will quit when it read the shmCmd."  );
			if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;
		}
				
		if  (  doCmd_startAvCall_step2_subProcess(  pProcInfo,  this->m_hWnd,  NULL,  iIndex_sharedObj  )  )  goto  errLabel;
	
		pShare->mems[index].var.iIndex_sharedObj  =  iIndex_sharedObj;
		pShare->mems[index].var.ucbLocalVideoOpen  =  TRUE;
	}

#endif

	if  (  pCapBmp->bCapDevConnected  )  {
		pCapBmp->curhWnd  =  m_hWnd;
	}
	
	//
	pCompressVideo		=	&pCapBmp->compressVideo;

	//
	TALKER_rule_dynBmp	rule_dynBmp;
	//  QIS_DYN_BMP	dynBmp;
	memset(  &rule_dynBmp,  0,  sizeof(  rule_dynBmp  )   );
	rule_dynBmp.uiType  =  CONST_vwRuleType_dynBmp;
	rule_dynBmp.dynBmp.uiObjType  =  pShare->uiObjType;
	rule_dynBmp.dynBmp.usIndex  =  index;
	if  (  procSendAvInfo(  m_var.pMisCnt,  m_hWnd,  FALSE,  uiTaskType,  NULL,  NULL,  NULL,  pCompressVideo,  NULL,  iIndex_sharedObj,  iIndex_sharedObjUsr,  (  TALKER_ruleU  *  )&rule_dynBmp,  &pShare->mems[index].var.iTaskId,  NULL  )  )  goto  errLabel;

	//  2010/09/09
	setCurSharedObjUsr(  iIndex_sharedObj,  m_hWnd  );

	//
#ifndef  __SUPPORT_subProcessToStartAvCall__
	if  (  pCapBmp->bCapDevConnected  )  {
		startCapture(  pCapBmp  );  
	}
#endif

	mytime(  &m_var.tLastModifiedTime  );

	iErr  =  0;
errLabel:
	
	if  (  iErr  )  {
		askSharedObjToStop(  pProcInfo,  pSharedObj,  pQyMc->gui.hMainWnd  );
		pShare->mems[index].var.ucbLocalVideoOpen  =  FALSE;
	}

	dlgShareDynBmps_refreshShareStatus(  m_hWnd,  &m_var,  CONST_objType_webcam  );

	return  iErr;
}

int  dlgShareDynBmps_toShareGps(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var)
{
	if  (  !pDLG_shareDynBmps_var  )  return  -1;
	DLG_shareDynBmps_var	&	m_var		=	*(  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;

	int		iErr	=	-1;
	CComPortEx	*	pPort	=	(  CComPortEx  *  )m_var.pComPort_gps;
	
	m_var.share_gps.bShare  =  !m_var.share_gps.bShare;

	if  (  !m_var.share_gps.bShare  )  {
		if  (  pPort  )  delete  pPort;
		m_var.pComPort_gps  =  NULL;
		dlgShareDynBmps_refreshShareStatus_gps(  m_hWnd,  &m_var  );
		return  0;
	}

	//
	if  (  pPort  )  {
		delete  pPort;
		m_var.pComPort_gps  =  NULL;
	}

	memset(  &m_var.share_gps.var,  0,  sizeof(  m_var.share_gps.var  )  );

	//
	QY_MC						*	pQyMc					=	QY_GET_GBUF(  );
	MC_VAR_isCli				*	pProcInfo				=	(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	int								iIndex_sharedObj		=	-1;
	int								iIndex_sharedObjUsr		=	-1;
	QY_SHARED_OBJ				*	pSharedObj				=	NULL;
	int								iIndex_shmCmd			=	-1;
	QM_SHM_CMD					*	pShmCmd					=	NULL;
	unsigned  int					uiTaskType				=	0;

	#ifdef  __DEBUG__
	#endif
	
	iIndex_sharedObj  =  newSharedObjIndex(  m_hWnd,  &iIndex_sharedObjUsr,  NULL  );
	if  (  iIndex_sharedObj  <  0  )  goto  errLabel;
	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;
	//
	iIndex_shmCmd  =  newShmCmdIndex(  pProcInfo,  iIndex_sharedObj  );
	pShmCmd  =  getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  iIndex_shmCmd  );
	if  (  !pShmCmd  )  goto  errLabel;
		    
	//
	pSharedObj->iIndex_shmCmd  =  iIndex_shmCmd;


	//
	uiTaskType  =  CONST_imTaskType_shareGps;

	//
	m_var.share_gps.var.iIndex_sharedObj  =  iIndex_sharedObj;


	//
	dlgShareDynBmps_chkShareGps(  m_hWnd,  &m_var  );


	//
#if  10
	if  (  procSendGpsInfo(  m_var.pMisCnt,  m_hWnd,  FALSE,  uiTaskType,  iIndex_sharedObj,  iIndex_sharedObjUsr,  NULL,  &m_var.share_gps.var.iTaskId,  NULL  )  )  goto  errLabel;
#endif

	//  2010/09/09
	setCurSharedObjUsr(  iIndex_sharedObj,  m_hWnd  );


	iErr  =  0;
errLabel:
	
	if  (  iErr  )  {
		askSharedObjToStop(  pProcInfo,  pSharedObj,  pQyMc->gui.hMainWnd  );
	}

	dlgShareDynBmps_refreshShareStatus_gps(  m_hWnd,  &m_var  );

	return  iErr;
}

int  dlgShareDynBmps_closeTaskAv(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var,  unsigned  int  uiObjType,  int  index  )
{
	if  (  !pDLG_shareDynBmps_var  )  return  -1;
	DLG_shareDynBmps_var	&	m_var		=	*(  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;

#ifdef  __WINCE__
	return  -1;
#else
	int								iErr	=	-1;

	MC_VAR_isCli				*		pProcInfo							=	(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	QY_MC					*		pQyMc								=	(  QY_MC  *  )pProcInfo->pQyMcParam;
	 FUNCS_for_isCliHelp  *  pFuncs  =  QY_GET_FUNCS_for_isCliHelp(  );
	 if  (  !pFuncs  )  return  -1;
	CQnmDb							db;
	int								iDbType								=	pQyMc->cfg.db.iDbType;
	IM_TASK_RCD						rcd;
	CQyMalloc						mallocObj;
	MIS_MSG_TASK			*		pMsgTask							=	(  MIS_MSG_TASK  *  )mallocObj.malloc(  sizeof(  MIS_MSG_TASK  )  );
	if  (  !pMsgTask  )  return  -1;
	int								lenInBytes							=	0;
	SHARE_dynBmps			*		pShare;
	pShare  =  (  SHARE_dynBmps  *  )dlgShareDynBmps_getShareDynBmpsBySth(  m_hWnd,  &m_var,  uiObjType  );
	if  (  !pShare  )  return  -1;

	if  (  index  <  0  ||  index  >=  pShare->usCnt  )  return  -1;

	//
	QM_dbFuncs		*	pDbFuncs	=	QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  goto  errLabel;
	QM_dbFuncs		&	g_dbFuncs	=	*pDbFuncs;


	QY_SHARED_OBJ  *  pSharedObj;
	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pShare->mems[index].var.iIndex_sharedObj  );
	if  (  !pSharedObj  )  goto  errLabel;

	if  (  pShare->mems[index].var.ucbLocalVideoOpen  )  {
		//  
		//  if  (  pSharedObj->bCapDev  )  memset(  pSharedObj,  0,  sizeof(  pSharedObj[0]  )  );
		CWnd  *  pMainWnd  =  AfxGetApp(  )->m_pMainWnd;
		askSharedObjToStop(  pProcInfo,  pSharedObj,  pMainWnd  ?  pMainWnd->m_hWnd  :  NULL  );
		//
		}
	else  if  (  pShare->mems[index].var.ucbSendLocalScreen  )  {
		      CWnd  *  pMainWnd  =  AfxGetApp(  )->m_pMainWnd;
			  askSharedObjToStop(  pProcInfo,  pSharedObj,  pMainWnd  ?  pMainWnd->m_hWnd  :  NULL  );
	}

	if  (  !db.getAvailableDb(  pQyMc->iDsnIndex_mainSys  )  )  goto  errLabel;
	//
	if  (  !g_dbFuncs.pf_bGetImTaskRcdBySth(  db.m_pDbMem->pDb,  iDbType, FALSE,  NULL,  NULL,  0,  0,  pShare->mems[index].var.iTaskId,  &rcd  )  )  goto  errLabel;

	MIS_CNT	*	pMisCnt	=	getMisCntByName(  pQyMc,  pProcInfo,  _T(  ""  )  );

	if  (  !taskRcd2Msg(  pMisCnt,  &rcd,  pMsgTask  )  )  goto  errLabel;

	//  
	unsigned  short	usOp		=	CONST_imOp_send_cancel;

	TASK_PROC_REQ		taskProcReq;
	memset(  &taskProcReq,  0,  sizeof(  taskProcReq  )  );
	taskProcReq.uiType  =  CONST_imCommType_taskProcReq;
	taskProcReq.usOp  =  usOp;
	taskProcReq.tStartTime_org  =  rcd.tSendTime;
	taskProcReq.uiTranNo_org  =  rcd.uiTranNo;
	taskProcReq.uiSerialNo_org  =  rcd.uiSerialNo;
	taskProcReq.uiContentType_org  =  rcd.uiContentType;
	//
	lenInBytes  =  sizeof(  taskProcReq  ); 
	//					  
	MACRO_prepareForTran(  );						
	//						  
	if  (  pFuncs->pf_postMsgTask2Mgr_mc(  pMisCnt,  CONST_misMsgType_task,  0,  pMsgTask->usCode,  tStartTran,  uiTranNo,  0,  rcd.id,  rcd.uiType,  (  char  *  )&taskProcReq,  lenInBytes,  NULL,  &pMsgTask->idInfo_taskSender,  &pMsgTask->idInfo_taskReceiver,  &rcd.idInfo_recv,  pMsgTask->uiChannelType,  NULL,  0  )  )  goto  errLabel;

	//
	int						idc				=	m_var.guiData.iIDC_STATIC_pic0;
	int						idc_dst			=	idc;
	freeCapImageByTaskId(  m_hWnd,  idc,  rcd.id,  &m_var.images,  M_GetDlgItem(  m_hWnd,  idc_dst  )  );

	//

	//
	memset(  &pShare->mems[index].var,  0,  sizeof(  pShare->mems[index].var  )  );

	
	iErr  =  0;
errLabel:
	
	qisApplyForChkingTasks_gui(  );

	return  iErr;
#endif
}


int  dlgShareDynBmps_chkShareGps(  HWND  m_hWnd,  void  *  pDLG_shareDynBmps_var  )
{
	if  (  !pDLG_shareDynBmps_var  )  return  -1;
	DLG_shareDynBmps_var	&	m_var		=	*(  DLG_shareDynBmps_var  *  )pDLG_shareDynBmps_var;

	int		iErr	=	-1;
	CComPortEx	*	pPort	=	(  CComPortEx  *  )m_var.pComPort_gps;

	if  (  !m_var.share_gps.bShare  )  return  0;

	if  (  pPort  )  {
		DWORD	dwTickCnt  =  GetTickCount(  );

		if  (  dwTickCnt  -  pPort->m_var.dwTickCnt_modified_gpsPos  <  10000  )  {
			//  接收数据正常
			return  0;
		}

		if  (  m_var.share_gps.var.dwTickCnt_start
			&&  dwTickCnt  -  m_var.share_gps.var.dwTickCnt_start  <  10000  )  
		{
			//  还在探测中
			return  0;
		}
	}

	if  (  !pPort  )  {
		pPort  =  new  CComPortEx;
		if  (  !pPort  )  goto  errLabel;
		m_var.pComPort_gps  =  pPort;
	}

	for  (  ;  m_var.share_gps.var.portNo  <  MAX_portNo_gps;  m_var.share_gps.var.portNo  ++  )  {
		 if  (  !m_var.share_gps.var.portNo  )  continue;
		 
		 char  parity  =  'N';
		 parity  =  NOPARITY;
		 UINT  stopbits  = 1;
		 stopbits  =  ONESTOPBIT;

		 if  (  !pPort->bInitPort(  m_hWnd,  m_var.share_gps.var.portNo,  4800,  parity,  8,  stopbits,  EV_RXCHAR  |  EV_CTS,  512,  CONST_iComPortType_gps,  m_var.share_gps.var.iIndex_sharedObj  )  )  continue;		 
		 break;
	}
	if  (  m_var.share_gps.var.portNo  ==  MAX_portNo_gps  )  {
		m_var.share_gps.var.portNo  =  0;
		goto  errLabel;
	}

	if  (  !pPort->bStartMonitoring(  )  )  goto  errLabel;
	m_var.share_gps.var.dwTickCnt_start  =  GetTickCount(  );

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		CComPortEx  *  pPort  =  (  CComPortEx  *  )m_var.pComPort_gps;
		if  (  pPort  )  {
			delete  pPort;
			m_var.pComPort_gps  =  NULL;
		}
	}

	return  iErr;

}
