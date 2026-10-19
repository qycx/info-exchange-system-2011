


#include	"stdafx.h"

#include	<windowsx.h>
#include	<math.h>
#include	<time.h>
#include	<stddef.h>

#include	"qymcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"

#include	"qyAvRecordPublic.h"
#include	"qmcVideoCapture.h"

#ifdef  __SUPPORT_HTMLEDIT__
	//  #include	"myHtmlEditCtrl.h"
#endif

#include	"tmpCeLib.h"
#include	"qyWnd.h"

#include	"qyRtcCommProc.h"
#include	"qyCusResTemp.h"
#ifndef  __WINCE__
//		 #include	"DlgVideos.h"
		 //  #include	"DlgCfgVideoConference.h"
		 //  #include	"DlgPolicyIsClient.h"
		 //  #include	"DlgInstantAssistant.h"
#endif
#include	<assert.h>
#ifndef  __WINCE__
	//  #include	"qyPs.h"
#endif
#include	"qmcDxSurfacePublic.h"
#ifndef  __WINCE__
#include	"qmcConferenceWall.h"
//  #include	"dlgProgress.h"
#endif
#include	"qmcCmdProc.h"

#include	"policyAvParams.h"

#ifndef  __WINCE__
		 //  #include	"qyStatic.h"
#endif
#include	"dlgTalkProc.h"
#include	"qmcSharePublic.h"

#if  1  //  def  __APP_qyMc_touchscreen__
		#include	"DlgWalls.h"
#endif

#include	"gpsCommProc.h"
#include	"qmcGpsProc.h"


#include	"qmcVWall.h"
//  #include	"DlgDynBmps.h"

#include	"sp.h"
#include	"isCliHelpPublic.h"

void  TALKER_shadow_free(  BOOL  bMgr,  void  *  pShadowInfo  )
{
	if  (  !pShadowInfo  )  return;

	if  (  bMgr  )  {
		TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pShadowInfo;
		int  i;
		for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
			 TALKER_shadow_mgrMem  *  pMem  =  &pShadowMgr->shadows[i];
			 //  MACRO_safeFree(  pMem->pZoneParams  );
		}		
	}

	//
	free(  pShadowInfo  );
}

void  *  TALKER_shadow_new(  BOOL  bMgr  )
{
	int					iErr			=	-1;
	void			*	pShadowInfo		=	NULL;
	MC_VAR_isCli	*	pProcInfo		=	QY_GET_procInfo_isCli(  );
	int					iSize;

	if  (  bMgr  )  {
		iSize  =  sizeof(  TALKER_shadow_mgr  );
		pShadowInfo  =  mymalloc(  iSize  );
		if  (  !pShadowInfo  )  goto  errLabel;
		memset(  pShadowInfo,  0,  iSize);
		//
		TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pShadowInfo;
		int  i;
		for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
			 TALKER_shadow_mgrMem  *  pMem  =  &pShadowMgr->shadows[i];
#if  0
			 pMem->usCnt_zoneParams  =  pProcInfo->av.usCnt_players;
			 if  (  !pMem->usCnt_zoneParams  )  goto  errLabel;
			 iSize  =  pMem->usCnt_zoneParams  *  sizeof(  ZONE_PARAM  );
			 pMem->pZoneParams  =  (  ZONE_PARAM  *  )mymalloc(  iSize  );
			 if  (  !pMem->pZoneParams  )  goto  errLabel;
			 memset(  pMem->pZoneParams,  0,  iSize  );
#endif
		}
	    }
	else  {
		iSize  =  sizeof(  TALKER_shadow  );
		pShadowInfo  =  mymalloc(  iSize  );
		if  (  !pShadowInfo  )  goto  errLabel;
		memset(  pShadowInfo,  0,  iSize);
		  
	}

	iErr	=	0;

errLabel:
	if  (  iErr  )  {
		if  (  pShadowInfo  )  TALKER_shadow_free(  bMgr,  pShadowInfo  );
	}
	return  iErr  ?  NULL  :  pShadowInfo;

}

  int  dlgTalk_freeCapImageBySth_mgr(  HWND  hDlgTalk,  int  iTaskId,  QY_MESSENGER_ID  *  pIdInfo  )
{
	int					iErr		=	-1;

	DLG_TALK_var	*	pMgrVar  =  (  DLG_TALK_var	*	)getDlgTalkVar(  hDlgTalk  );
	if  (  !pMgrVar  )  goto  errLabel;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;


	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;

	int  i;
	for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
		 if  (  pShadowMgr->shadows[i].hShadow  )  {
			 dlgTalk_freeCapImageBySth(  pShadowMgr->shadows[i].hShadow,  iTaskId,  pIdInfo  );
		 }
	}
  
	dlgTalk_freeCapImageBySth(  hDlgTalk,  iTaskId,  pIdInfo  );

	iErr  =   0;

errLabel:
	return  iErr;
}


#if  0	//  2013/03/02
  int  freeCapImageByTaskId_mgr(  HWND    hDlgTalk,  int  idc,  int  iTaskId,  CAP_IMAGES  *  pImgs  )
{
	int					iErr		=	-1;

	DLG_TALK_var	*	pMgrVar  =  getDlgTalkVar(  hDlgTalk  );
	if  (  !pMgrVar  )  goto  errLabel;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;


	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;

	int  i;
	for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
		 if  (  pShadowMgr->shadows[i].hShadow  )  {			 
			 freeCapImageByTaskId(  pShadowMgr->shadows[i].hShadow,  idc,  iTaskId,  pImgs  );
		 }
	}
 
	freeCapImageByTaskId(  hDlgTalk,  idc,  iTaskId,  pImgs  );

	iErr  =   0;

errLabel:
	return  iErr;

}
#endif

	//  2013/03/02
  int  freeCapImageByTaskId_mgr(  HWND    hDlgTalk,  int  idc,  int  iTaskId,  CAP_IMAGES  *  pImgs,  int  idc_dst  )
{
	int					iErr		=	-1;

	DLG_TALK_var	*	pMgrVar  =  (  DLG_TALK_var	*	)getDlgTalkVar(  hDlgTalk  );
	if  (  !pMgrVar  )  goto  errLabel;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;


	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;

	int  i;
	for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
		 if  (  pShadowMgr->shadows[i].hShadow  )  {			 
			 freeCapImageByTaskId(  pShadowMgr->shadows[i].hShadow,  idc,  iTaskId,  pImgs,  M_GetDlgItem(  pShadowMgr->shadows[i].hShadow,  idc_dst  )  );
		 }
	}
 
	freeCapImageByTaskId(  hDlgTalk,  idc,  iTaskId,  pImgs,  M_GetDlgItem(  hDlgTalk,  idc  )  );

	iErr  =   0;

errLabel:
	return  iErr;

}


  void  chooseAvDevice_mgr(  void  *  pCapParam,  HWND  hDlgTalk,  HWND  hWndStatus,  int  iMenuId  )
{
	int					iErr		=	-1;

	DLG_TALK_var	*	pMgrVar  =  (  DLG_TALK_var	*	)getDlgTalkVar(  hDlgTalk  );
	if  (  !pMgrVar  )  goto  errLabel;
	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;


	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;

	int  i;
	for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
		 if  (  pShadowMgr->shadows[i].hShadow  )  {  
			 chooseAvDevice_shadow(  pMgrVar->pCapStuff,  pMgrVar->bIncludeAudio,  pShadowMgr->shadows[i].hShadow,  NULL,  iMenuId  );
		 }
	}
    
	chooseAvDevice(  pMgrVar->pCapStuff,  pMgrVar->bIncludeAudio,  hDlgTalk,  NULL,  iMenuId  );

	iErr  =   0;

errLabel:
	return;
}


 BOOL  InvalidateRect_mgr(  HWND hDlgTalk, CONST RECT *lpRect, BOOL bErase  )
{
	BOOL	bRet	=	FALSE;

	DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var	*	)getDlgTalkVar(  hDlgTalk  );
	if  (  !pMgrVar  )  goto  errLabel;

	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;
	int  i;
	for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
		if  (  !pShadowMgr->shadows[i].hShadow  )  continue;
		InvalidateRect(  pShadowMgr->shadows[i].hShadow,  lpRect,  bErase  );
	}
	InvalidateRect(  hDlgTalk,  lpRect,  bErase  );

	bRet  =  TRUE;

errLabel:
	return  bRet;
	 
}


 //
 int  askToRefreshLayout_mgr(  HWND  hDlgTalk  )
{
	int		iErr	=	-1;

	DLG_TALK_var  *  pMgrVar  =  (  DLG_TALK_var	*	)getDlgTalkVar(  hDlgTalk  );
	if  (  !pMgrVar  )  goto  errLabel;

	if  (  !isTalkerShadowMgr(  pMgrVar->addr  )  )  goto  errLabel;
	TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pMgrVar->pShadowInfo;
	if  (  !pShadowMgr  )  goto  errLabel;

	
	//
	 int  i;	 
	 for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
		  if  (  !pShadowMgr->shadows[i].hShadow  )  continue;
		  if  (  isTalkerSubType_canInput(  pShadowMgr->shadows[i].iTalkerSubType  )  )  {
			  ::PostMessage(   pShadowMgr->shadows[i].hShadow,  CONST_qyWm_postComm,  CONST_qyWmParam_refreshLayout,  0  );
		  }
	 }
	 ::PostMessage(   hDlgTalk,  CONST_qyWm_postComm,  CONST_qyWmParam_refreshLayout,  0  );

	 iErr  =  0;
errLabel:
	 return  iErr;
}