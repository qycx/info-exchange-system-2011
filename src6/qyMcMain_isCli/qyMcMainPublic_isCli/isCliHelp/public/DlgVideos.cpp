// DlgVideos.cpp: implementation of the CDlgVideos class.
//
//////////////////////////////////////////////////////////////////////

#include	"stdafx.h"
#include	<math.h>

#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"tmpCeLib.h"

#include	"myresource.h"

#include	"DlgVideos.h"
#include	"qmcVideoCapture.h"
//  #include	"DlgCfgVideoConference.h"
#include	"qyVk.h"

#include	"qmcDxSurfacePublic.h"
#include	"dlgTalkProc.h"

#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"qycusResTemp.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



/////////////
#if  0
 __declspec(  dllexport  )  int  showEnlargedWnd(  HWND  hDlg_org,  BOOL  bDlgTalk,  void  *  pDLG_VIDEO_PARAMS,  CAP_subWnds  *  pSubWnds  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	DLG_VIDEO_PARAMS  *  p  =  (  DLG_VIDEO_PARAMS  *  )pDLG_VIDEO_PARAMS;

#ifndef  __SUPPORT_dlgDesktopsMon__
		 #ifdef  __DEBUG__
				 traceLog(  _T(  "showEnlargedWnd not supported"  )  );
		 #endif
		 return  -1;
#else
	int						iErr				=		-1;
	QY_MC				*	pQyMc				=		QY_GET_GBUF(  );
	CAP_IMAGE			*	pImg				=		NULL;
	CDlgVideos			*	pDlg				=		NULL;
	TCHAR					tBuf[256]			=		_T(  ""  );
	RECT					rect;
	MIS_CNT				*	pMisCnt				=		getMisCntByName(  pQyMc,  0,  _T(  ""  )  );			//  2009/
	if  (  !pMisCnt  )  return  -1;
	MC_VAR_isCli			*	pProcInfo			=		(  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;

	if  (  !hDlg_org  ||  !p  )  return  -1;
	if  (  !p->m_var.pImgs  )  return  -1;

	if  (  bDlgTalk  )  {
		CDlgTalk  *  pDlgTalk  =  (  CDlgTalk  *  )CWnd::FromHandle(  hDlg_org  );
		if  (  !pDlgTalk  )  goto  errLabel;

		DLG_TALK_var  *  pMgrVar  =  NULL;
		if  (  isTalkerShadowMgr(  pDlgTalk->m_var.addr  )  )  pMgrVar  =  &pDlgTalk->m_var;
		else  {
			  TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pDlgTalk->m_var.pShadowInfo;
			  if  (  !pTalkerShadow  )  goto  errLabel;
			  pMgrVar  =  getDlgTalkVar(  pTalkerShadow->hMgr  );
			  if  (  !pMgrVar  )  goto  errLabel;
		}


		if  (  !p->m_var.bMeImage  
			&&  pMgrVar->av.taskInfo.bTaskExists  )  
		{
			if  (  pMgrVar->av.taskInfo.iTaskId  ==  p->m_var.iTaskId  
				&&  IsWindow(  pDlgTalk->m_var.av.hWnd_remoteAv_taskInfo  )  )
			{
				if  (  IsIconic(  pDlgTalk->m_var.av.hWnd_remoteAv_taskInfo  )  )  ::SendMessage(  pDlgTalk->m_var.av.hWnd_remoteAv_taskInfo,  WM_SYSCOMMAND,  SC_RESTORE,  0  );

				if  (  p->m_var.bFreeCapImages  )  {
					QY_WMBUF_COMM	wmBuf;
					memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
					wmBuf.uiType  =  CONST_qyWmParam_freeCapImages;
					SendMessage(  pDlgTalk->m_var.av.hWnd_remoteAv_taskInfo,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
				}

				SetForegroundWindow(  pDlgTalk->m_var.av.hWnd_remoteAv_taskInfo  );
				iErr  =  0;  goto  errLabel;
			}
		}
		
		if  (  p->m_var.bLocalAvWnd  )  {	//  2011/03/13
			#if  0
			if  (  IsWindow(  pDlgTalk->m_var.av.hWnd_localAv  )  )  {

				if  (  p->m_var.bFreeCapImages  )  {
					QY_WMBUF_COMM	wmBuf;
					memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
					wmBuf.uiType  =  CONST_qyWmParam_freeCapImages;
					SendMessage(  pDlgTalk->m_var.av.hWnd_localAv,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
				}

				iErr  =  0;  goto  errLabel;
			}
			#endif
		}
	}

	if  (  p->m_var.iIndex_capImage  >=  0  &&  p->m_var.iIndex_capImage  <  mycountof(  p->m_var.pImgs->mems  )  )  {
		pImg  =  &p->m_var.pImgs->mems[p->m_var.iIndex_capImage];

		if  (  IsWindow(  pImg->hWnd_remoteAv  )  )  {
			if  (  ::IsIconic(  pImg->hWnd_remoteAv  )  )  ::SendMessage(  pImg->hWnd_remoteAv,  WM_SYSCOMMAND,  SC_RESTORE,  0  );
			else  ::SetForegroundWindow(  pImg->hWnd_remoteAv  );
			iErr  =  0;  goto  errLabel;
		}		
	}

	
	//
	//  2007/09/08	
	pDlg  =  new  CDlgVideos(  IsWindow(  p->m_var.hParent  )  ?  CWnd::FromHandle(  p->m_var.hParent  )  :  CWnd::GetDesktopWindow(  )  );
	if  (  !pDlg  )  goto  errLabel;
	if  (  pImg  )  {
		getTalkerDesc(  pMisCnt,  &pImg->idInfo_sender,  tBuf,  mycountof(  tBuf  ),  0,  0  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s( %d )"  ),  tBuf,  pImg->uiTranNo_openAvDev  );
		}
	else  if  (  p->m_var.bVideoConference  )  {
			  if  (  bDlgTalk  )  {
				  CDlgTalk  *  pDlgTalk  =  (  CDlgTalk  *  )CWnd::FromHandle(  hDlg_org  );
				  getTalkerDesc(  pMisCnt,  &pDlgTalk->m_var.addr.idInfo,  tBuf,  mycountof(  tBuf  ),  0,  0  );
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  tBuf,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_videoConference  )  );
			  }
	}
	int				iWndContentType		=	CONST_qyWndContentType_enlargedWnd;		//  2011/02/02
	int				iResId_menu			=	0;
	unsigned  int	nElapseInMs			=	0;
	if  (  p->m_var.bRemoteAssist  )  {
		iResId_menu  =  CONST_resId_menu_dlgRemoteAssist;
		nElapseInMs  =  1000;
	}
	if  (  !pDlg->bSetDlgInfo(  iWndContentType,  tBuf,  iResId_menu,  hDlg_org,  p->m_var.iTaskId,  &p->m_var.idInfo_sender,  p->m_var.uiTranNo_openAvDev,  pMisCnt,  p->m_var.usCnt_monPics_row,  p->m_var.usCnt_monPics_col,  p->m_var.uiInitW,  p->m_var.uiInitH,  FALSE,  nElapseInMs  )  )  goto  errLabel;
	//  pDlg->m_var.uiTaskType  =  p->m_var.uiTaskType;
	
	//
	pDlg->bEnableScrollBar(  p->m_var.bScrollBarEnabled  );
	pDlg->doLayout(  );
	pDlg->bEnableRemoteAssist(  p->m_var.bRemoteAssist  );

	//  2010/08/30
	if  (  p->m_var.bVideoConference  )  {
		pDlg->m_var.bVideoConference  =  TRUE;
	}

	//  2010/12/24
	if  (  p->m_var.bInstantAssistant  )  {
		pDlg->m_var.bInstantAssistant  =  TRUE;
	}

	//
	if  (  p->m_var.bMediaControl  )  {
		pDlg->m_var.bMediaControl  =  TRUE;
		pDlg->m_var.iIndex_capBmp  =  p->m_var.iIndex_capBmp;
		CAP_procInfo_bmpU  *  pCapBmp  =  getCapBmpBySth(  pProcInfo,  p->m_var.iIndex_capBmp,  0  );
		if  (  pCapBmp  )  {
			QY_SHARED_OBJ	*	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pCapBmp->common.iIndex_sharedObj  );
			if  (  pSharedObj  )  {
				pDlg->m_var.iIndex_capAudio  =  pSharedObj->iIndex_capAudio;
			}
		}
	}

	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;		
	//	
	if  (  p->m_var.bVideoConference  ||  p->m_var.bRemoteAssist  )  {
		if  (  registerSubWnd(  pDlg->m_hWnd,  0,  0,  p->m_var.iTaskId,  NULL,  0,  0,  pSubWnds,  NULL  )  )  {
			traceLogA(  "showEnlargedWnd failed. registerSubWnd failed."  );
			goto  errLabel;
		}
	}
	//
	pDlg->ShowWindow(  SW_SHOW  );
	//

	if  (  pImg  )  {
        pImg->hWnd_remoteAv  =  pDlg->m_hWnd;
		}
	else  if  (  bDlgTalk  )  {
			  CDlgTalk  *  pDlgTalk  =  (  CDlgTalk  *  )CWnd::FromHandle(  hDlg_org  );
			  	
			  DLG_TALK_var  *  pMgrVar  =  NULL;
			  if  (  isTalkerShadowMgr(  pDlgTalk->m_var.addr  )  )  pMgrVar  =  &pDlgTalk->m_var;
			  else  {
				    TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pDlgTalk->m_var.pShadowInfo;
					if  (  !pTalkerShadow  )  goto  errLabel;
					pMgrVar  =  getDlgTalkVar(  pTalkerShadow->hMgr  );
					if  (  !pMgrVar  )  goto  errLabel;
			  }

			  if  (  p->m_var.bLocalAvWnd  )  {	//  2011/03/13
				  //  pDlgTalk->m_var.av.hWnd_localAv  =  pDlg->m_hWnd;
			  }
			  else  if  (  pMgrVar->av.taskInfo.bTaskExists  )  {
						if  (  pMgrVar->av.taskInfo.iTaskId  ==  p->m_var.iTaskId  )  pDlgTalk->m_var.av.hWnd_remoteAv_taskInfo  =  pDlg->m_hWnd;
			  }
	}

	iErr  =  0;

errLabel:
	if  (  iErr  )  {
        if  (  pDlg  )  delete  pDlg;
	}

	return  iErr;
#endif
}
#endif

 __declspec(  dllexport  )  int  showEnlargedWnd(  HWND  hDlg_org,  BOOL  bDlgTalk,  void  *  pDLG_VIDEO_PARAMS,  CAP_subWnds  *  pSubWnds  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	DLG_VIDEO_PARAMS  *  p  =  (  DLG_VIDEO_PARAMS  *  )pDLG_VIDEO_PARAMS;

#ifndef  __SUPPORT_dlgDesktopsMon__
		 #ifdef  __DEBUG__
				 traceLog(  _T(  "showEnlargedWnd not supported"  )  );
		 #endif
		 return  -1;
#else
	int						iErr				=		-1;
	QY_MC				*	pQyMc				=		QY_GET_GBUF(  );
	FUNCS_for_isCliHelp	*	pFuncs				=		QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return  -1;
	CAP_IMAGE			*	pImg				=		NULL;
	CDlgVideos			*	pDlg				=		NULL;
	TCHAR					tBuf[256]			=		_T(  ""  );
	RECT					rect;
	MIS_CNT				*	pMisCnt				=		getMisCntByName(  pQyMc,  0,  _T(  ""  )  );			//  2009/
	if  (  !pMisCnt  )  return  -1;
	MC_VAR_isCli			*	pProcInfo			=		(  MC_VAR_isCli  *  )pMisCnt->pProcInfoParam;

	if  (  !hDlg_org  ||  !p  )  return  -1;
	if  (  !p->m_var.pImgs  )  return  -1;

	if  (  bDlgTalk  )  {
		//  CDlgTalk  *  pDlgTalk  =  (  CDlgTalk  *  )CWnd::FromHandle(  hDlg_org  );
		DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )getDlgTalkVar(  hDlg_org  );
		if  (  !pDlgTalkVar  )  goto  errLabel;

		DLG_TALK_var  *  pMgrVar  =  NULL;
		if  (  isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  pMgrVar  =  pDlgTalkVar;
		else  {
			  TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pDlgTalkVar->pShadowInfo;
			  if  (  !pTalkerShadow  )  goto  errLabel;
			  pMgrVar  =  (  DLG_TALK_var  *  )getDlgTalkVar(  pTalkerShadow->hMgr  );
			  if  (  !pMgrVar  )  goto  errLabel;
		}


		if  (  !p->m_var.bMeImage  
			&&  pMgrVar->av.taskInfo.bTaskExists  )  
		{
			if  (  pMgrVar->av.taskInfo.iTaskId  ==  p->m_var.iTaskId  
				&&  IsWindow(  pDlgTalkVar->av.hWnd_remoteAv_taskInfo  )  )
			{
				if  (  IsIconic(  pDlgTalkVar->av.hWnd_remoteAv_taskInfo  )  )  ::SendMessage(  pDlgTalkVar->av.hWnd_remoteAv_taskInfo,  WM_SYSCOMMAND,  SC_RESTORE,  0  );

				if  (  p->m_var.bFreeCapImages  )  {
					QY_WMBUF_COMM	wmBuf;
					memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
					wmBuf.uiType  =  CONST_qyWmParam_freeCapImages;
					SendMessage(  pDlgTalkVar->av.hWnd_remoteAv_taskInfo,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
				}

				SetForegroundWindow(  pDlgTalkVar->av.hWnd_remoteAv_taskInfo  );
				iErr  =  0;  goto  errLabel;
			}
		}
		
		if  (  p->m_var.bLocalAvWnd  )  {	//  2011/03/13
			#if  0
			if  (  IsWindow(  pDlgTalk->m_var.av.hWnd_localAv  )  )  {

				if  (  p->m_var.bFreeCapImages  )  {
					QY_WMBUF_COMM	wmBuf;
					memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
					wmBuf.uiType  =  CONST_qyWmParam_freeCapImages;
					SendMessage(  pDlgTalk->m_var.av.hWnd_localAv,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
				}

				iErr  =  0;  goto  errLabel;
			}
			#endif
		}
	}

	if  (  p->m_var.iIndex_capImage  >=  0  &&  p->m_var.iIndex_capImage  <  mycountof(  p->m_var.pImgs->mems  )  )  {
		pImg  =  &p->m_var.pImgs->mems[p->m_var.iIndex_capImage];

		if  (  IsWindow(  pImg->hWnd_remoteAv  )  )  {
			if  (  ::IsIconic(  pImg->hWnd_remoteAv  )  )  ::SendMessage(  pImg->hWnd_remoteAv,  WM_SYSCOMMAND,  SC_RESTORE,  0  );
			else  ::SetForegroundWindow(  pImg->hWnd_remoteAv  );
			iErr  =  0;  goto  errLabel;
		}		
	}

	
	//
	//  2007/09/08	
	pDlg  =  new  CDlgVideos(  IsWindow(  p->m_var.hParent  )  ?  CWnd::FromHandle(  p->m_var.hParent  )  :  CWnd::GetDesktopWindow(  )  );
	if  (  !pDlg  )  goto  errLabel;
	if  (  pImg  )  {
		pFuncs->pf_getTalkerDesc(  pMisCnt,  &pImg->idInfo_sender,  tBuf,  mycountof(  tBuf  ),  0,  0  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s( %d )"  ),  tBuf,  pImg->uiTranNo_openAvDev  );
		}
	else  if  (  p->m_var.bVideoConference  )  {
			  if  (  bDlgTalk  )  {
				  //  CDlgTalk  *  pDlgTalk  =  (  CDlgTalk  *  )CWnd::FromHandle(  hDlg_org  );
				  DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )getDlgTalkVar(  hDlg_org  );
				  if  (  !pDlgTalkVar  )  goto  errLabel;
				  pFuncs->pf_getTalkerDesc(  pMisCnt,  &pDlgTalkVar->addr.idInfo,  tBuf,  mycountof(  tBuf  ),  0,  0  );
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  tBuf,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_videoConference  )  );
			  }
	}
	int				iWndContentType		=	CONST_qyWndContentType_enlargedWnd;		//  2011/02/02
	int				iResId_menu			=	0;
	unsigned  int	nElapseInMs			=	0;
	if  (  p->m_var.bRemoteAssist  )  {
		iResId_menu  =  CONST_resId_menu_dlgRemoteAssist;
		nElapseInMs  =  1000;
	}
	if  (  !pDlg->bSetDlgInfo(  iWndContentType,  tBuf,  iResId_menu,  hDlg_org,  p->m_var.iTaskId,  &p->m_var.idInfo_sender,  p->m_var.uiTranNo_openAvDev,  pMisCnt,  p->m_var.usCnt_monPics_row,  p->m_var.usCnt_monPics_col,  p->m_var.uiInitW,  p->m_var.uiInitH,  FALSE,  nElapseInMs  )  )  goto  errLabel;
	//  pDlg->m_var.uiTaskType  =  p->m_var.uiTaskType;
	
	//
	pDlg->bEnableScrollBar(  p->m_var.bScrollBarEnabled  );
	pDlg->doLayout(  );
	pDlg->bEnableRemoteAssist(  p->m_var.bRemoteAssist  );

	//  2010/08/30
	if  (  p->m_var.bVideoConference  )  {
		pDlg->m_var.bVideoConference  =  TRUE;
	}

	//  2010/12/24
	if  (  p->m_var.bInstantAssistant  )  {
		pDlg->m_var.bInstantAssistant  =  TRUE;
	}

	//
	if  (  p->m_var.bMediaControl  )  {
		pDlg->m_var.bMediaControl  =  TRUE;
		pDlg->m_var.iIndex_capBmp  =  p->m_var.iIndex_capBmp;
		CAP_procInfo_bmpU  *  pCapBmp  =  getCapBmpBySth(  pProcInfo,  p->m_var.iIndex_capBmp,  0  );
		if  (  pCapBmp  )  {
			QY_SHARED_OBJ	*	pSharedObj  =  getSharedObjByIndex(  pProcInfo,  pCapBmp->common.iIndex_sharedObj  );
			if  (  pSharedObj  )  {
				pDlg->m_var.iIndex_capAudio  =  pSharedObj->iIndex_capAudio;
			}
		}
	}

	//
	if  (  !pDlg->Create(  rect  )  )  goto  errLabel;		
	//	
	if  (  p->m_var.bVideoConference  ||  p->m_var.bRemoteAssist  )  {
		if  (  registerSubWnd(  pDlg->m_hWnd,  0,  0,  p->m_var.iTaskId,  NULL,  0,  0,  pSubWnds,  NULL  )  )  {
			traceLogA(  "showEnlargedWnd failed. registerSubWnd failed."  );
			goto  errLabel;
		}
	}
	//
	pDlg->ShowWindow(  SW_SHOW  );
	//

	if  (  pImg  )  {
        pImg->hWnd_remoteAv  =  pDlg->m_hWnd;
		}
	else  if  (  bDlgTalk  )  {
			  //  CDlgTalk  *  pDlgTalk  =  (  CDlgTalk  *  )CWnd::FromHandle(  hDlg_org  );
			  DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )getDlgTalkVar(  hDlg_org  );
			  if  (  !pDlgTalkVar  )  goto  errLabel;
			  	
			  DLG_TALK_var  *  pMgrVar  =  NULL;
			  if  (  isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  pMgrVar  =  pDlgTalkVar;
			  else  {
				    TALKER_shadow  *  pTalkerShadow  =  (  TALKER_shadow  *  )pDlgTalkVar->pShadowInfo;
					if  (  !pTalkerShadow  )  goto  errLabel;
					pMgrVar  =  (  DLG_TALK_var  *  )getDlgTalkVar(  pTalkerShadow->hMgr  );
					if  (  !pMgrVar  )  goto  errLabel;
			  }

			  if  (  p->m_var.bLocalAvWnd  )  {	//  2011/03/13
				  //  pDlgTalk->m_var.av.hWnd_localAv  =  pDlg->m_hWnd;
			  }
			  else  if  (  pMgrVar->av.taskInfo.bTaskExists  )  {
						if  (  pMgrVar->av.taskInfo.iTaskId  ==  p->m_var.iTaskId  )  pDlgTalkVar->av.hWnd_remoteAv_taskInfo  =  pDlg->m_hWnd;
			  }
	}

	iErr  =  0;

errLabel:
	if  (  iErr  )  {
        if  (  pDlg  )  delete  pDlg;
	}

	return  iErr;
#endif
}



  __declspec(  dllexport  )  void  *  getDlgVideosVar(  HWND  hDlgVideos  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	if  (  !IsWindow(  hDlgVideos  )  )  return  NULL;
	CDlgVideos  *  pDlg  =  (  CDlgVideos  *  )CDlgVideos::FromHandlePermanent(  hDlgVideos  );
	if  (  !pDlg  )  return  NULL;

	return  &pDlg->m_var;
}




//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDlgVideos::CDlgVideos(  CWnd* pParent /*= NULL*/) :  CDlgDesktopsMon(  pParent  )
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );

	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	m_var.bUseDirectX  =  pQyMc->cfg.bUseDxSurface;	//  2009/08/06
}

CDlgVideos::~CDlgVideos()
{

}





 //	 
 //  BOOL  CDlgVideos::bSetDlgInfo(  int  iWndContentType,  LPCTSTR  title,  int  iResId_menu,  HWND  hDlgTalk,  int  iTaskId,  int  iIndex_capImage,  MIS_CNT  *  pMisCnt,  unsigned  short  usCnt_row,  unsigned  short  usCnt_col,  unsigned  int  uiInitW_pc,  unsigned  int  uiInitH_pic,  unsigned  char  ucbLocalAv  )
 BOOL	CDlgVideos::bSetDlgInfo(  int  iWndContentType,  LPCTSTR  title,  int  iResId_menu,  HWND  hDlgTalk,  int  iTaskId,  QY_MESSENGER_ID  *  pIdInfo_sender,  unsigned  int  uiTranNo_openAvDev,  MIS_CNT  *  pMisCnt,  unsigned  short  usCnt_row,  unsigned  short  usCnt_col,  unsigned  int  uiInitW_pc,  unsigned  int  uiInitH_pic,  unsigned  char  ucbLocalAv,  unsigned  int  nElapseInMs  )
{
	BOOL							bRet		=	FALSE;
	QY_MC						*	pQyMc		=	QY_GET_GBUF(  );

	if  (  !pMisCnt  )  {
		traceLogA(  "dlgVideos::bSegDlgInfo failed, pMisCnt is null"  );
		return  FALSE;
	}

	if  (  !iResId_menu  )  iResId_menu  =  CONST_resId_menu_dlgVideos;

	if  (  !::CDlgDesktopsMon::bSetDlgInfo(  iWndContentType,  0,  iResId_menu,  usCnt_row,  usCnt_col,  uiInitW_pc,  uiInitH_pic  )  )  goto  errLabel;

	if  (  title  )  lstrcpyn(  m_var.title,  title,  mycountof(  m_var.title  )  );
	//  m_var.iResId_menu  =  iResId_menu  ?  iResId_menu  :  CONST_resId_menu_dlgVideos;		//  2009/09/20
	m_var.hDlgTalk  =  hDlgTalk;
	m_var.iTaskId  =  iTaskId;
	if  (  pIdInfo_sender  )  m_var.idInfo_sender.ui64Id  =  pIdInfo_sender->ui64Id;
	m_var.uiTranNo_openAvDev  =  uiTranNo_openAvDev;
	//  m_var.iIndex_capImage  =  iIndex_capImage;
	m_var.pMisCnt  =  pMisCnt;
	//
	m_var.ucbLocalAv  =  ucbLocalAv;
	//
	m_var.nElapseInMs  =  nElapseInMs;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}


 BOOL  CDlgVideos::bEnableRemoteAssist(  BOOL  bRemoteAssist  )
 {
	 if  (  m_var.bRemoteAssist  ==  bRemoteAssist  )  return  TRUE;
	 m_var.bRemoteAssist  =  bRemoteAssist;
	 return  TRUE;
 }


BOOL CDlgVideos::OnInitDialog()
{
	int								iErr	=	-1;
	QY_MC						*	pQyMc	=	QY_GET_GBUF(  );
	if  (  !m_var.pMisCnt  )  return  FALSE;
	MC_VAR_isCli  *  pProcInfo				=	(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	CDlgDesktopsMon				*	pBase	=	this;
	QY_DMITEM					*	pItem	=	pBase->m_var.pIdcTable;

	m_var.idc  =  (  int  )pItem[0].des;

	CDlgDesktopsMon::OnInitDialog(  );
	
	//  cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	//  m_var.bUseDirectX  =  pQyMc->cfg.bUseDxSurface;	//  2009/08/06

	SetWindowText(  m_var.title  );


	//
	m_var.pMsgBuf_doWnd_guiMsgArrive  =  (  MIS_MSGU  *  )malloc(  sizeof(  MIS_MSGU  )  );
	if  (  !m_var.pMsgBuf_doWnd_guiMsgArrive  )  goto  errLabel;


	//  2012/05/05
	int  iSize;	
	m_var.usCnt_zoneParams  =  pProcInfo->av.usCnt_players;
	iSize  =  m_var.usCnt_zoneParams  *  sizeof(  ZONE_PARAM  );
	m_var.pZoneParams  =  (  ZONE_PARAM  *  )mymalloc(  iSize  );
	if  (  !m_var.pZoneParams  )  goto  errLabel;
	memset(  m_var.pZoneParams,  0,  iSize  );


	//  if  (  m_var.iIndex_capImage  <  0  &&  m_var.iTaskId  )  SetTimer(  1,  1000,  NULL  );
	if  (  m_var.nElapseInMs  )  SetTimer(  1,  m_var.nElapseInMs,  NULL  );

	//  2011/03/25
	m_var.guiData.bInited  =  TRUE;

	iErr  =  0;

errLabel:
	
	if  (  iErr  )  {
		traceLogA(  "CDlgVideo::OnInitDialog error exists."  );
		PostMessage(  WM_CLOSE,  0,  0  );
	}

	return  TRUE;
}


BEGIN_MESSAGE_MAP(CDlgVideos, CDlgDesktopsMon)
	ON_WM_DESTROY()
	ON_WM_ACTIVATE()
//	ON_WM_SIZE()
//	ON_COMMAND(ID_stopScrollBar, Onstopscrollbar)
//	ON_UPDATE_COMMAND_UI(ID_stopScrollBar, OnUpdatestopscrollbar)
//	ON_COMMAND(ID_startScrollBar, Onstartscrollbar)
//	ON_UPDATE_COMMAND_UI(ID_startScrollBar, OnUpdatestartscrollbar)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

void CDlgVideos::OnDestroy()
{
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	MACRO_safeFree(  m_var.pZoneParams  );							//  2012/05/05

	MACRO_safeFree(  m_var.pMsgBuf_doWnd_guiMsgArrive  );			//  2009/12/08

	int  idc_dst  =  m_var.idc;
	freeCapImages(  this->m_hWnd,  m_var.idc,  &m_var.images,  M_GetDlgItem(  m_hWnd,  idc_dst  ),  &m_var.hDc  );

	CDlgDesktopsMon::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}



 LRESULT  CDlgVideos::OnQyComm(  WPARAM  wParam,  LPARAM  lParam  )
{
	long				lRet				=					-1;
	QY_WMBUF_COMM	*	pComm				=					( QY_WMBUF_COMM * )lParam;
	CDlgDesktopsMon	*	pBase				=					this;
	QY_MC			*	pQyMc				=					QY_GET_GBUF(  );
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return  -1;
	MC_VAR_isCli	*	pProcInfo			=					QY_GET_procInfo_isCli(  );
	int  idc_dst;  
	
	if  (  !pComm  )  return  -1;

	if  (  !m_var.guiData.bInited  )  {
		//  MACRO_qyAssert(  0,  _T(  "CDlgVideos::OnQyComm, can't be called before inited"  )  );
		#ifdef  __DEBUG__
				traceLog(  _T(  "CDlgVideos::OnQyComm, can't be called before inited"  )  );
		#endif
		return  -1;
	}


	switch  (  pComm->uiType  )  {
			case  CONST_misMsgType_procVideo_qmc:  {  		
				  MIS_MSG_procVideo_qmc		*	pMsg			=	(  MIS_MSG_procVideo_qmc  *  )pComm;
				  if  (  pFuncs->pf_dlgVideos_procVideo(  m_hWnd,  &pBase->m_var,  &m_var,  pMsg  )  )  goto  errLabel;
				  }
				  break;

			case  CONST_qyWmParam_freeCapImage:
				  QY_MESSENGER_ID	idInfo;
				  idInfo.ui64Id  =  pComm->u.freeCapImage.idInfo.ui64Id;
				  int  idc_dst;  idc_dst  =  m_var.idc;
				  freeCapImageBySth(  m_hWnd,  m_var.idc,  pComm->u.freeCapImage.iTaskId,  &idInfo,  &m_var.images,  M_GetDlgItem(  m_hWnd,  idc_dst  )  );				  
				  break;

			case  CONST_qyWmParam_freeCapImages:	//  2010/12/27
				  idc_dst  =  m_var.idc;
				  freeCapImages(  m_hWnd,  m_var.idc,  &m_var.images,  M_GetDlgItem(  m_hWnd,  idc_dst  ),  &m_var.hDc  );
				  break;

			default:
					break;
	}

	lRet  =  QY_RC_WMOK;

errLabel:

	return  lRet;
}






 LRESULT  CDlgVideos::OnQyPostComm(  WPARAM  wParam,  LPARAM  lParam  )
{
	long				lRet			=		-1;
	MC_VAR_isCli		*	pProcInfo		=		(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;

	switch  (  wParam  )  {
			case  CONST_qyWmParam_guiMsgArrive:  
				  doWnd_guiMsgArrive(  pProcInfo,  lParam,  this->m_hWnd,  TRUE,  m_var.pMsgBuf_doWnd_guiMsgArrive  );
				  break;
			default:
					break;
	}
	
//  errLabel:

	return  lRet;
}

void CDlgVideos::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDlgDesktopsMon::OnActivate(nState, pWndOther, bMinimized);

	traceLogA(  "DlgVideos: OnActivate: nState %d",  nState  );
	
	// TODO: 在此处添加消息处理程序代码
	if  (  m_var.ucbLocalAv  )  {
		if  (  nState  !=  WA_INACTIVE  )  {
			traceLogA(  "DlgVideos::OnActivate  ... "  );			
			//  
		}
	}
}

int  CDlgVideos::sizeAllControls(  RECT  rcParam  )
{
	int					iErr	=	-1;
	int					i;
	int					idc;
	QY_DMITEM		*	pItem;
	CWnd			*	pCtrl;
	CDlgDesktopsMon	*	pBase	=	this;

	//
	CDlgDesktopsMon::sizeAllControls(  rcParam  );

	//
	for  (  i  =  0;  i  <  pBase->m_var.usCnt_row  *  pBase->m_var.usCnt_col;  i  ++  )  {
		 pItem  =  &pBase->m_var.pIdcTable[i];
		 idc  =  (  int  )pItem->des;		
		 pCtrl  =  GetDlgItem(  idc  );
		 if  (  !pCtrl  )  goto  errLabel;
		 pCtrl->Invalidate(  TRUE  );
		 //  pCtrl->UpdateWindow(  );

		 if  (  m_var.ucbLocalAv  )  myGetImageInfo(  TRUE,  m_var.images.mems[i].iW_org,  m_var.images.mems[i].iH_org,  0,  0,  pBase->m_var.mems_org[i].iW,  pBase->m_var.mems_org[i].iH,  &m_var.images.mems[i].iX,  &m_var.images.mems[i].iY,  &m_var.images.mems[i].iW,  &m_var.images.mems[i].iH  );
		 else  {
			   //  getCapImages(  0,  0,  pBase->m_var.mems[i].iW,  pBase->m_var.mems[i].iH,  &m_var.images  );
			   RECT	rc;
			   ::GetClientRect(  pCtrl->m_hWnd,  &rc  );
			   int	iX,  iY,  iW,  iH;
			   iX  =  rc.left;
			   iY  =  rc.top;
			   iW  =  rc.right  -  rc.left;
			   iH  =  rc.bottom  -  rc.top;
			   getCapImages(  iX,  iY,  iW,  iH,  &m_var.images  );
		 }


	}

	iErr  =  0;
errLabel:
	return  iErr;
}

//void CDlgVideos::OnSize(UINT nType, int cx, int cy)
//{
//	CDlgDesktopsMon::OnSize(nType, cx, cy);
//
//	// TODO: 在此处添加消息处理程序代码
//	sizeAllControls_videos(  );
//
//  errLabel:
//	return;
//}



//void CDlgVideos::Onstopscrollbar()
//{
//	// TODO: 在此添加命令处理程序代码
//	CDlgDesktopsMon::bEnableScrollBar(  FALSE  );
//
//	sizeAllControls(  );
//
//}

//void CDlgVideos::OnUpdatestopscrollbar(CCmdUI *pCmdUI)
//{
//	// TODO: 在此添加命令更新用户界面处理程序代码
//	CDlgDesktopsMon  *  pBase  =  this;
//	if  (  !pBase->m_var.bScrollBarEnabled  )  pCmdUI->Enable(  FALSE  );
//}


//void CDlgVideos::Onstartscrollbar()
//{
//	// TODO: 在此添加命令处理程序代码
//	CDlgDesktopsMon::bEnableScrollBar(  TRUE  );
//	
//	sizeAllControls(  );
//
//}




//void CDlgVideos::OnUpdatestartscrollbar(CCmdUI *pCmdUI)
//{
//	// TODO: 在此添加命令更新用户界面处理程序代码
//	CDlgDesktopsMon  *  pBase  =  this;
//	if  (  pBase->m_var.bScrollBarEnabled  )  pCmdUI->Enable(  FALSE  );
//}

void CDlgVideos::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//  traceLogA(  "OnTimer(  ) called"  );

	/*
	if  (  m_var.bRemoteAssist  &&  m_var.iIndex_capImage  <  0  &&  m_var.hDlgTalk  &&  m_var.iTaskId  )  {
		QY_WMBUF_COMM		wmBuf;

		traceLogA(  "CDlgVideos::OnTimer called. 用来向dlgTalk发起SendMessage 询问，利用iTaskId来获取相应的iIndex_capImage,设置hWnd。对了，这里还需要有dlgTalk的句柄，应从bSetDlgInfo中传进来。"  );

		memset(  &wmBuf.u.getCapImageInfo,  0,  sizeof(  wmBuf.u.getCapImageInfo  )  );
		wmBuf.uiType  =  CONST_qyWmParam_getCapImageInfo;
		wmBuf.u.getCapImageInfo.iTaskId  =  m_var.iTaskId;
		wmBuf.u.getCapImageInfo.iIndex_capImage  =  -1;				//  要取回  
		wmBuf.u.getCapImageInfo.hWnd_remoteAssist  =  this->m_hWnd;
		if  (  ::SendMessage(  m_var.hDlgTalk,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  )  ==  CONST_qyWmRc_ok  )  {
			if  (  wmBuf.u.getCapImageInfo.iIndex_capImage  >=  0  )  {
				traceLogA(  "CDlgVideos::OnTimer 得到了 iIndex_capImage %d",  wmBuf.u.getCapImageInfo.iIndex_capImage  );
				m_var.iIndex_capImage  =  wmBuf.u.getCapImageInfo.iIndex_capImage;
				m_var.idInfo_sender.ui64Id  =  wmBuf.u.getCapImageInfo.idInfo_sender.ui64Id;
				m_var.uiTranNo_openAvDev  =  wmBuf.u.getCapImageInfo.uiTranNo_openAvDev;
										   
				getTalkerDesc(  m_var.pMisCnt,  &m_var.idInfo_sender,  m_var.title,  mycountof(  m_var.title  ),  0,  0  );
				_sntprintf(  m_var.title,  mycountof(  m_var.title  ),  _T(  "%s( %d )"  ),  m_var.title,  m_var.uiTranNo_openAvDev  );
				SetWindowText(  m_var.title  );
			}
		}
	}
	*/

	//  如果最后的鼠标事件有未发送的，在这里发送出去
	if  (  m_var.bRemoteAssist  )  {
		if  (  m_var.bNeedSend_lastMouseEvent  )  {
			processPointerEvent(  m_var.lastMouseEvent.x,  m_var.lastMouseEvent.y,  m_var.lastMouseEvent.nFlags,  m_var.lastMouseEvent.bMouseMove,  TRUE  );
		}
	}


	CDlgDesktopsMon::OnTimer(nIDEvent);
}


 //  要准备把这个鼠标移动的消息发送到对方去。
 int  CDlgVideos::processPointerEvent(  int  x,  int  y,  UINT nFlags,  BOOL  bMouseMove,  BOOL  bSendForce  )
{
		int						iErr			=	-1;
		if  (  !m_var.pMisCnt  )  return  -1;
		FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  );
		if  (  !pFuncs  )  return  -1;
		MC_VAR_isCli		*		pProcInfo		=	(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
		CDlgDesktopsMon	*		pBase			=	this;

		if  (  !m_var.bRemoteAssist  ||  m_var.images.usCnt  !=  1  )  return  -1;

		//  if (  ::GetFocus() != m_hWnd) return 0;

		MACRO_prepareForTran(  )
		unsigned  int			uiChannelType	=	CONST_channelType_media;
		MIS_CHANNEL			*	pChannel		=	NULL;
		if  (  !(  pChannel  =  getChannelByType(  m_var.pMisCnt,  uiChannelType  )  )  )  goto  errLabel;

		REMOTE_ASSIST_REQ		req;
		int						mask;
 		CAP_IMAGE			*	pImg			=	&m_var.images.mems[0];
		if  (  !pImg->iW_org  ||  !pImg->iH_org  )  goto  errLabel;

		if  (  m_var.bSwapMouse  )  {
    		mask  =  (  (  (  nFlags  &  MK_LBUTTON  )  ?  CONST_button1Mask  :  0  ) 
					|  (  (  nFlags  &  MK_MBUTTON  )  ?  CONST_button3Mask  :  0  ) 
					|  (  (  nFlags  &  MK_RBUTTON  )  ?  CONST_button2Mask  :  0  )  );
			} 
		else {
			 mask  =  (  (  (  nFlags  &  MK_LBUTTON  )  ?   CONST_button1Mask  :  0  ) 
					|  (  (  nFlags  &  MK_MBUTTON  )  ?  CONST_button2Mask  :  0  ) 
					|  (  (  nFlags  &  MK_RBUTTON  )  ?  CONST_button3Mask  :  0  )  );
		}
 
		memset(  &req,  0,  sizeof(  req  )  );
		req.uiType  =  CONST_imCommType_remoteAssistReq;
		req.uiTranNo_openAvDev  =  m_var.uiTranNo_openAvDev;
		req.u.usRaType  =  CONST_usRaType_pointerEvent;
		req.u.pointerEvent.ucButtonMask  =  mask;
		req.u.pointerEvent.x  =  (  unsigned  short  )(  x  +  pBase->m_var.m_nScrollPos_h  );  
		req.u.pointerEvent.y  =  (  unsigned  short  )(  y  +  pBase->m_var.m_nScrollPos_v  );  
		//  确保在捕获范围内
		if  (  req.u.pointerEvent.x  <  pBase->m_var.layoutParam.iEdge_l  ||  req.u.pointerEvent.y  <  pBase->m_var.layoutParam.iEdge_t  )  goto  errLabel;
		//  去掉边界部分     
		req.u.pointerEvent.x  -=  pBase->m_var.layoutParam.iEdge_l;
		req.u.pointerEvent.y  -=  pBase->m_var.layoutParam.iEdge_t;


		//  1。未完成。鼠标过快，要从图像带回个标识当响应。
		//  2。有好几个地方是通过对mediaQ的warningInterval进行限速，这实际很多是错的。应该对toSendQ 进行判断。注意。。。。


		//  将事件记录下来。如果没发送出去，可以在OnTimer里发送
		m_var.lastMouseEvent.x  =  x;
		m_var.lastMouseEvent.y  =  y;
		m_var.lastMouseEvent.nFlags  =  nFlags;
		m_var.lastMouseEvent.bMouseMove  =  bMouseMove;
		//
		m_var.bNeedSend_lastMouseEvent  =  TRUE;

		//  这里要改为从mousemove里把dwTickCnt带上，有被协助端把此值从图像历带回。然后，继续发送mousemove。其他包不限
		if  (  !bSendForce  &&  bMouseMove  )  {
			if  (  m_var.uiEventId_lastRecvd  !=  m_var.dwTickCnt_sendLastMouseMove  )  {		//  表明响应未收到
				traceLogA(  "mouseMove is skipped."  );
				goto  errLabel;
			}					
		}									

		if  (  pProcInfo->av.bMediaChannelReady  
			&&  !isQ2Warning(  &pChannel->toSendQ2,  CONST_uiQNodes_warningInterval_toSendQ  )				//  保持这个报警间隔主要是为了防止队列被视频数据占满，导致无法将控制信息放入队列。
			)
		{			
			if  (  bMouseMove  )  {
				m_var.dwTickCnt_sendLastMouseMove  =  GetTickCount(  );
				req.u.pointerEvent.uiEventId  =  m_var.dwTickCnt_sendLastMouseMove;
				//
				traceLogA(  "mouseMove sending."  );
			}

			//
			m_var.bNeedSend_lastMouseEvent  =  FALSE;

			if  (  pFuncs->pf_postMsg2Mgr_mc(  m_var.pMisCnt,  NULL,  CONST_misMsgType_outputTask,  0,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  (  char  *  )&req,  sizeof(  req  ),  0,  &m_var.idInfo_sender,  uiChannelType,  NULL,  FALSE  )  )  traceLogA(  "postMsg2Mgr_mc failed"  );
		}

		iErr  =  0;

errLabel:
		return  iErr;
}


void CDlgVideos::OnLButtonDown(UINT nFlags, CPoint point)
{
	//  traceLogA(  "LButtonDown, nFlags %d",  nFlags  );

	// TODO: 在此添加消息处理程序代码和/或调用默认值
	processPointerEvent(  point.x,  point.y,  nFlags  );

	CDlgDesktopsMon::OnLButtonDown(nFlags, point);
}

void CDlgVideos::OnLButtonUp(UINT nFlags, CPoint point)
{
	//  traceLogA(  "LButtonUp,  nFlags %d",  nFlags  );

	// TODO: 在此添加消息处理程序代码和/或调用默认值
	processPointerEvent(  point.x,  point.y,  nFlags  );

	CDlgDesktopsMon::OnLButtonUp(nFlags, point);
}

void CDlgVideos::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//  traceLogA(  "LButtonDblClk, nFlags %d",  nFlags  );

	// TODO: 在此添加消息处理程序代码和/或调用默认值
	processPointerEvent(  point.x,  point.y,  nFlags  );

	CDlgDesktopsMon::OnLButtonDblClk(nFlags, point);
}

void CDlgVideos::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	processPointerEvent(  point.x,  point.y,  nFlags  );

	CDlgDesktopsMon::OnMButtonDown(nFlags, point);
}

void CDlgVideos::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	processPointerEvent(  point.x,  point.y,  nFlags  );

	CDlgDesktopsMon::OnMButtonUp(nFlags, point);
}

void CDlgVideos::OnMButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	processPointerEvent(  point.x,  point.y,  nFlags  );

	CDlgDesktopsMon::OnMButtonDblClk(nFlags, point);
}

void CDlgVideos::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	processPointerEvent(  point.x,  point.y,  nFlags  );

	CDlgDesktopsMon::OnRButtonDown(nFlags, point);
}

void CDlgVideos::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	processPointerEvent(  point.x,  point.y,  nFlags  );

	CDlgDesktopsMon::OnRButtonUp(nFlags, point);
}

void CDlgVideos::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	processPointerEvent(  point.x,  point.y,  nFlags  );

	CDlgDesktopsMon::OnRButtonDblClk(nFlags, point);
}

 void  CDlgVideos::OnMouseMove(UINT nFlags, CPoint point)
{
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return;

	//  2010/08/30
	if  (  m_var.bInstantAssistant  )  {
		POINT	tmpPoint;
		tmpPoint.x  =  point.x;
		tmpPoint.y  =  point.y;
		::MapWindowPoints(  this->m_hWnd,  NULL,  &tmpPoint,  1  );
		pFuncs->pf_viewInstantAssistant(  this->m_hWnd,  0,  tmpPoint.x,  tmpPoint.y,  m_var.hDlgTalk,  FALSE  );
	}

	//
	if  (  m_var.bMediaControl  )  {
		viewMediaControl(  this->m_hWnd,  m_var.iIndex_capAudio,  m_var.iIndex_capBmp,  &m_var.hWnd_mediaControl  );		
	}

	// TODO: 
	processPointerEvent(  point.x,  point.y,  nFlags,  TRUE  );

//  errLabel:
	
	CDlgDesktopsMon::OnMouseMove(nFlags, point);
}


BOOL CDlgVideos::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	return CDlgDesktopsMon::OnMouseWheel(nFlags, zDelta, pt);
}



#define		CONST_maxKeysPerKey			4
#define		CONST_voidKeyCode			-1

// keycodes contains the keysyms terminated by an VoidKeyCode.
// The releaseModifiers is a set of ORed flags indicating whether 
// particular modifier-up messages should be sent before the keys 
// and modifier-down after.

#define		CONST_KEYMAP_LCONTROL		0x0001
#define		CONST_KEYMAP_RCONTROL		0x0002
#define		CONST_KEYMAP_LALT			0x0004
#define		CONST_KEYMAP_RALT			0x0008

typedef  struct  __key2Send_t			{
				 unsigned  int			keycodes[CONST_maxKeysPerKey];
				 unsigned  int			releaseModifiers;
}		 KEY_2_SEND;

/*
#define		CONST_VK_dead_grave       0xFE50
#define		CONST_VK_dead_acute       0xFE51
#define		CONST_VK_dead_circumflex  0xFE52
#define		CONST_VK_dead_tilde       0xFE53
*/


 KEY_2_SEND  vk2Send(  UINT  virtkey,  DWORD  keyData  ) 
{ 
	UINT numkeys = 0;
    
	BYTE keystate[256];
	unsigned char buf[4]; // lots of space for now

    KEY_2_SEND		kas;
    kas.releaseModifiers  =  0;

    bool extended = ((keyData & 0x1000000) != 0);
    
    if  (  extended  )  { 
        switch  (  virtkey  )  {
		        case  VK_MENU :
					  virtkey  =  VK_RMENU;  
					  break;
				case  VK_CONTROL:
					  virtkey  =  VK_RCONTROL; 
					  break;  
				case  VK_RETURN:
            		  //  virtkey = VK_KEYPAD_ENTER; 
					  break;
				default:
						break;
        }
    }
    
    // We try looking it up in our table
	QY_DMITEM	*	pItem;
        
    // Look up the desired code in the table
    for  (  pItem  =  CONST_qyKeyTable; pItem->type  !=  -1; pItem  ++  )  {
		 if  (  pItem->type  ==  virtkey  ) {
            kas.keycodes[numkeys  ++  ]  =  (  unsigned  int  )pItem->des;
            break;
        }
    }
    

    if  (  numkeys  !=  0  ) {
        UINT key = kas.keycodes[numkeys-1];
		traceLogA(  "keymap gives %u (%x) ", key, key);
	    } 
	else {
         // not found in table
		
         // we try a simple conversion to Ascii, using the current keyboard mapping
		 ::myGetKeyboardState(keystate);
   	
		 int ret = ::myToAscii(virtkey, 0, keystate, (WORD *) buf, 0);

		 // If Left Ctrl & Alt both pressed and ToAscii gives a valid keysym
		 // This is for AltGr on international keyboards  (= LCtrl-Alt).
		 // e.g. Ctrl-Alt-Q gives @ on German keyboards
		 if  (  ((keystate[VK_MENU] & 0x80) != 0) &&
            ((keystate[VK_CONTROL] & 0x80) != 0) ) 
		 {

           // If the key means anything in this keyboard layout
           if  ( (ret >= 1) && 
                 ( ( (*buf >= 32) && (*buf <= 126) ) ||
                   ( (*buf >= 160) && (*buf <= 255) ) ) 
                ) 
		   {
               // Send the modifiers up, then the keystroke, then mods down
               // We don't release the right control; this allows German users
               // to use it for doing Ctl-@ etc. (though not under Win95 --
               // see below)

               if (GetKeyState(VK_LCONTROL) & 0x8000) kas.releaseModifiers |= CONST_KEYMAP_LCONTROL;
               if (GetKeyState(VK_LMENU)    & 0x8000) kas.releaseModifiers |= CONST_KEYMAP_LALT;
               if (GetKeyState(VK_RMENU)    & 0x8000) kas.releaseModifiers |= CONST_KEYMAP_RALT;

               // This is for windows 95, and possibly other systems.  
               // The above GetKeyState calls don't work in 95 - they always return 0.
               // But if we're here at all we know that control and alt are pressed, so let's
               // raise all Control and Alt keys if we haven't registered any yet.
               if  (  kas.releaseModifiers  ==  0  )
                   kas.releaseModifiers  =  CONST_KEYMAP_LCONTROL | CONST_KEYMAP_LALT | CONST_KEYMAP_RALT;

			   for  (  int  i  =  0;  i  <  ret;  i  ++  ) {
                    kas.keycodes[numkeys++]  =  *(buf+i);
                    //  log.Print(8, _T("%02x (%c) "), *(buf+i) , *(buf+i));
                }                
           } 
        } 
        
        // If not a ctrl-alt key
        if  (  numkeys  ==  0  ) {

            // There are no keysyms corresponding to control characters 
            // Eg Ctrl F.  The server already knows whether the control 
            // key is pressed. So we are interested in the key that would be 
            // there if the Ctrl were not pressed.
            keystate[VK_CONTROL] = keystate[VK_LCONTROL] = keystate[VK_RCONTROL] = 0;

		    int ret = ::myToAscii(virtkey, 0, keystate, (WORD *) buf, 0);
            if (ret < 0) {
				/*
                switch (*buf) {
				case '`' :
					kas.keycodes[numkeys++] = XK_dead_grave; break;
				case '\'' :
					kas.keycodes[numkeys++] = XK_dead_acute; break;
				case '~' :
					kas.keycodes[numkeys++] = XK_dead_tilde; break;
				case '^':
					kas.keycodes[numkeys++] = XK_dead_circumflex; break;
				}
				*/
				traceLogA(  "vk2Send: 这里遇到了ToAscii返回 %d, 为dead key, 看有没有影响",  ret  );
            }
            // if this works, and it's a regular printable character, we just send that
            if (ret >= 1) {
                //  log.Print(8,_T("ToAscii (without ctrl) returns %d byte(s): "), ret);
                for (int i = 0; i < ret; i++) {
                   kas.keycodes[numkeys++] = *(buf+i);
                   //  log.Print(8, _T("%02x (%c) "), *(buf+i) , *(buf+i));
                }
            }
        }

    }

    kas.keycodes[numkeys] = CONST_voidKeyCode;
	return  kas;
};

 int  CDlgVideos::sendKeyEvent(  unsigned  int  nChar, unsigned  char  ucbDown  ) 
{
	int						iErr			=	-1;
	FUNCS_for_isCliHelp		*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  );
	if  (  !pFuncs  )  return  -1;
	MC_VAR_isCli			*	pProcInfo		=	(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	MACRO_prepareForTran(  )
	unsigned  int			uiChannelType	=	CONST_channelType_media;
	REMOTE_ASSIST_REQ		req;

	memset(  &req,  0,  sizeof(  req  )  );
	req.uiType  =  CONST_imCommType_remoteAssistReq;
	req.uiTranNo_openAvDev  =  m_var.uiTranNo_openAvDev;
	req.u.usRaType  =  CONST_usRaType_keyEvent;
	req.u.keyEvent.ucbDown  =  ucbDown;
	req.u.keyEvent.key  =  nChar;

	if  (  pFuncs->pf_postMsg2Mgr_mc(  m_var.pMisCnt,  NULL,  CONST_misMsgType_outputTask,  0,  CONST_qyCmd_sendMedia, tStartTran,  uiTranNo,  0,  (  char  *  )&req,  sizeof(  req  ),  0,  &m_var.idInfo_sender,  uiChannelType,  NULL,  0  )  )  traceLogA(  "postMsg2Mgr_mc failed"  );

	iErr  =  0;
//  errLabel:
	return  iErr;

}


 int  CDlgVideos::processKeyEvent(  UINT  nChar, DWORD  keyData  )
{
	int					iErr		=	-1;
	MC_VAR_isCli		*	pProcInfo	=	(  MC_VAR_isCli  *  )m_var.pMisCnt->pProcInfoParam;
	unsigned  char		ucbDown		=  (  (  keyData  &  0x80000000l  )  ==  0  );


	if  (  !m_var.bRemoteAssist  ||  m_var.images.usCnt  !=  1  )  return  -1;

	CAP_IMAGE			*	pImg			=	&m_var.images.mems[0];
	if  (  !pImg->iW_org  ||  !pImg->iH_org  )  goto  errLabel;

	//  if (  ::GetFocus() != m_hWnd) return 0;

	//  traceLogA(  "down %d",  down  );
	#ifdef  __DEBUG__  
			#ifndef  __WINCE__
			TCHAR  keyname[32];
			if  (  GetKeyNameText(  keyData,  keyname,  31  )  )  {
				traceLogA(  "Process key: %S, nChar %d, (keyData %04x): ", keyname,  nChar,  keyData  );
			}
			#endif
	#endif

	KEY_2_SEND  kas;
	kas  =  vk2Send(  nChar,  keyData  );    

	if  (  pProcInfo->av.bMediaChannelReady  
		&&  !isQ2Warning(  &pProcInfo->mediaQ2,  CONST_uiQNodes_warningInterval_mediaQ  )		//  保持这个报警间隔主要是为了防止队列被视频数据占满，导致无法将控制信息放入队列。
		)
	{		
		if  (  kas.releaseModifiers  &  CONST_KEYMAP_LCONTROL  )  {
			sendKeyEvent(  CONST_qK_LCONTROL,  false  );
		}
		if  (  kas.releaseModifiers  &  CONST_KEYMAP_LALT  )  {
			sendKeyEvent(  CONST_qK_LMENU,  false  );
		}
		if  (  kas.releaseModifiers  &  CONST_KEYMAP_RCONTROL  )  {
			sendKeyEvent(  CONST_qK_RCONTROL,  false  );
		}
		if  (  kas.releaseModifiers  &  CONST_KEYMAP_RALT  )  {
			sendKeyEvent(  CONST_qK_RMENU,  false  );
		}
		
		for  (  int  i  =  0;  kas.keycodes[i]  !=   CONST_voidKeyCode  &&  i  <  CONST_maxKeysPerKey;  i  ++  )  {
			 sendKeyEvent(  kas.keycodes[i],  ucbDown  );
		}
		
		if  (  kas.releaseModifiers  &  CONST_KEYMAP_RALT  )  {
			sendKeyEvent(  CONST_qK_RMENU, true );
		}
		if  (  kas.releaseModifiers  &  CONST_KEYMAP_RCONTROL  )  {
			sendKeyEvent(  CONST_qK_RCONTROL,  true  );
		}
		if  (  kas.releaseModifiers  &  CONST_KEYMAP_LALT  )  {
			sendKeyEvent(  CONST_qK_LMENU,  false  );
		}
		if  (  kas.releaseModifiers  &  CONST_KEYMAP_LCONTROL  )  {
			sendKeyEvent(  CONST_qK_CONTROL,  false  );
		}
		
	}


	iErr  =  0;
errLabel:
	return  iErr;
}




 int  CDlgVideos::resetKeyEvent(  )
{
	if  (  !m_var.bRemoteAssist  ||  m_var.images.usCnt  !=  1  )  return  -1;


	traceLogA(  "Losing focus - cancelling modifiers"  );
	
	sendKeyEvent(  CONST_qK_MENU,		false  );
	sendKeyEvent(  CONST_qK_CONTROL,	false  );
	sendKeyEvent(  CONST_qK_SHIFT,		false  );

	sendKeyEvent(  CONST_qK_LMENU,		false);
	sendKeyEvent(  CONST_qK_LCONTROL,	false);
	sendKeyEvent(  CONST_qK_LSHIFT,		false);
	sendKeyEvent(  CONST_qK_RMENU,		false);
	sendKeyEvent(  CONST_qK_RCONTROL,	false);
	sendKeyEvent(  CONST_qK_RSHIFT,		false);
	

	return  0;
}


 /*
 int  CDlgVideos::getCapImageInfo(  QY_WMBUF_COMM  *  pComm  )
{
	return  0;
}
*/


 /*
 int  CDlgVideos::chkTask(  QY_WMBUF_COMM  *  pComm  )
{
	return  0;
}
*/



BOOL CDlgVideos::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	switch  (  pMsg->message  )  {
			case  WM_KEYDOWN:
			case  WM_KEYUP:
			case  WM_SYSKEYDOWN:
			case  WM_SYSKEYUP:
				  processKeyEvent(  pMsg->wParam,  pMsg->lParam  );
				  break;
			case  WM_CHAR:
			case  WM_SYSCHAR:
				  break;
			case  WM_KILLFOCUS:
				  resetKeyEvent(  );
				  break;
			default:
					break;
	}


	return CDlgDesktopsMon::PreTranslateMessage(pMsg);
}


void CDlgVideos::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	if  (  m_var.bClosed  )  {				//  200/11/17. 使用这个标志位是为了防止用escape退出。因为在远程协助的情况下，escape需要送到对方的窗口去
        CDlgDesktopsMon::OnCancel();
		}
	else  if  (  !m_var.bRemoteAssist  &&  !m_var.bInstantAssistant  )  {	//  2012/07/06. 在没有浮动菜单和不是远程协助时,都需要立即关闭窗口.
			   CDlgDesktopsMon::OnCancel();
	}
}

void CDlgVideos::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_var.bClosed  =  TRUE;

	//  通知结束此任务
	if  (  m_var.bRemoteAssist  &&  m_var.hDlgTalk  &&  m_var.iTaskId  )  {
		/*QY_WMBUF_COMM		wmBuf;

		traceLogA(  "CDlgVideos::OnDestroy. 用来向dlgTalk发起SendMessage 询问，利用iTaskId来关闭此任务。"  );

		memset(  &wmBuf.u.getCapImageInfo,  0,  sizeof(  wmBuf.u.getCapImageInfo  )  );
		wmBuf.uiType  =  CONST_qyWmParam_getCapImageInfo;
		wmBuf.u.getCapImageInfo.iTaskId  =  m_var.iTaskId;
		wmBuf.u.getCapImageInfo.bStopRemoteAssist  =  TRUE;
		if  (  ::SendMessage(  m_var.hDlgTalk,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  )  !=  CONST_qyWmRc_ok  )  {
			traceLogA(  "CDlgVideos::OnDestroy(  ): SendMessage failed."  );
		}
		*/
		MIS_MSG_notifyTaskEnd_qmc	msg;
		memset(  &msg,  0,  sizeof(  msg  )  );
		msg.uiType  =  CONST_misMsgType_notifyTaskEnd_qmc;
		msg.iTaskId  =  m_var.iTaskId;
		msg.bToCancel  =  TRUE;
		if  (  ::SendMessage(  m_var.hDlgTalk,  CONST_qyWm_comm,  0,  (  LPARAM  )&msg  )  !=  CONST_qyWmRc_ok  )  {
			traceLogA(  "CDlgVideos::OnDestroy(  ): SendMessage failed."  );
		}		
	}

	CDlgDesktopsMon::OnClose();
}

HBRUSH CDlgVideos::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDlgDesktopsMon::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  Change any attributes of the DC here
	CDlgDesktopsMon  *  pBase  =  this;
	if  (  pBase->m_var.m_bFullScreen
		||  pBase->m_var.ucbBkBlack  )  
	{
		switch  (  nCtlColor  )  {
			case  CTLCOLOR_DLG:
			case  CTLCOLOR_STATIC:
				  return  (  HBRUSH  )GetStockObject(  BLACK_BRUSH  );
				  break;
			default:
					break;
		}		
	}

	// TODO:  Return a different brush if the default is not desired
	return hbr;
}
