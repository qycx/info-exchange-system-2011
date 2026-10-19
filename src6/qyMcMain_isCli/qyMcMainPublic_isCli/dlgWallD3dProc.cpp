





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
		//  #include	"qyPs.h"
	#endif
#endif

#include	"dlgTalkProc.h"

#include	"qmcGpsProc.h"
//
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

#include	"dlgSelect_isCli_public.h"

#include	"myDb.h"
#include	"isCliD3dPublic.h"


 int  tryToTalkToMessenger_wallD3d(  void  *  p0,  QY_MESSENGER_ID  *  pIdInfo  )
 {
	 int		iErr	=	-1;
	 QY_MC			*	pQyMc	=	QY_GET_GBUF(  );
	 FUNCS_for_isCliHelp  *  pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  );
	 if  (  !pFuncs  )  return  -1;

	 GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
	 TCHAR	tBuf[129]  =  _T(  ""  );
	 
	 //
	 if  (  pGBuf->peer.idInfo_peer.ui64Id  !=  pIdInfo->ui64Id  )  {
		 //  清理掉原有的资源
		 if  (  pGBuf->peer.hTalkerMgr  )  {
			 if  (  IsWindow(  pGBuf->peer.hTalkerMgr  )  )  {
				 //  这里应该:
				 //			试图把wallD3d从hTalkerMgr中移出
				 //			如果hTalkerMgr里只有这一个影子,那么就判断是否有任务,如果有,就提问下,切换后该talker将被取消所有任务.
				 //			如果仍然继续,那么就关闭talker.
				 //
				 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Are you sure to close talker %I64u"  ),  pGBuf->peer.idInfo_peer.ui64Id  );
				 if  (  myMessageBox(  pGBuf->hWall_d3d,  tBuf,  _T(  "qycx.com"  ),  MB_YESNO  )  !=  IDYES  )  return  -1;
				 SendMessage(  pGBuf->peer.hTalkerMgr,  WM_CLOSE,  0,  0  );
			 }
			 pGBuf->peer.hTalkerMgr  =  NULL;			 
		 }
		 //
		 pGBuf->peer.idInfo_peer.ui64Id  =  pIdInfo->ui64Id;
	 }
	 //
	 if  (  pGBuf->peer.hTalkerMgr  )  {
		 if  (  !IsWindow(  pGBuf->peer.hTalkerMgr  )  )  {
			 pGBuf->peer.hTalkerMgr  =  NULL;
		 }
	 }
	 if  (  !pGBuf->peer.hTalkerMgr  )  {
		 			
		 // 首先找到主窗口		
		 HWND	hDlgTalk  =  NULL;
		 
		 BOOL  bNeedNotShowWnd  =  TRUE;
		 #ifdef  __DEBUG__	
					    #ifdef  __TEST_showTalkerShadowMgrFirst__
								bNeedNotShowWnd  =  FALSE;	
								traceLog(  _T(  "for test, bNeedNotShowWnd is false"  )  );
						#endif
		 #endif						
		 pFuncs->pf_talkToMessenger(  pIdInfo->ui64Id,  bNeedNotShowWnd,  FALSE,  &hDlgTalk  );				
		 if  (  !IsWindow(  hDlgTalk  )  )  goto  errLabel;
	 	 
		 pGBuf->peer.hTalkerMgr  =  hDlgTalk;
	 }
	 if  (  !pGBuf->peer.hTalkerMgr  )  goto  errLabel;

	 //  下面准备将hWall_d3d加为talkerMgr的影子
	 HWND  hTalkerMgr  =  pGBuf->peer.hTalkerMgr;
	 		
	 //	 
	 DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var	*	)getDlgTalkVar(  hTalkerMgr  );
	 if  (  !pDlgTalkVar  )  goto  errLabel;
	 if  (  !isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  goto  errLabel;
		 
	 //  2012/05/23
	 if  (  pDlgTalkVar->ucbTmpMsgr  )  {
		 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "Gui"  ),  NULL,  _T(  ""  ),  _T(  ""  ),  _T(  "tryToTalkToMessenger_dlgWallD3d failed: no shadow allowed,  %I64u is tmpMsgr"  ),  pIdInfo->ui64Id  );
		 goto  errLabel;	 
	 }
		 

	 //
	 int  i;
	 TALKER_shadow_mgr  *  pShadowMgr  =  (  TALKER_shadow_mgr  *  )pDlgTalkVar->pShadowInfo;
	 if  (  !pShadowMgr  )  goto  errLabel;
	 for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {
		  if  (  pShadowMgr->shadows[i].hWall  ==  pGBuf->hWall_d3d  )  break;	 
	 }
	 if  (  i  <  mycountof(  pShadowMgr->shadows  )  )  {
		 #ifdef  __DEBUG__
				 traceLog(  _T(  "tryToTalkToMessenger_dlgWallD3d: hWall_d3d has already been a shadow"  )  );
		 #endif		
		 iErr  =  0;  goto  errLabel;
	 }


	 //  	
	 for  (  i  =  0;  i  <  mycountof(  pShadowMgr->shadows  );  i  ++  )  {		
		  if  (  !IsWindow(  pShadowMgr->shadows[i].hWall  )  )  break;			   
	 }
	 if  (  i  ==  mycountof(  pShadowMgr->shadows  )  )  goto  errLabel;


	 //	
	 memset(  &pShadowMgr->shadows[i],  0,  sizeof(  pShadowMgr->shadows[i]  )  );		
	 pShadowMgr->shadows[i].hWall  =  pGBuf->hWall_d3d;
	 pShadowMgr->shadows[i].iWndContentType_wall  =  CONST_qyWndContentType_wallD3d;


	 iErr  =  0;
	 
errLabel:

	 //
	 refreshPeerInfo_wallD3d(  );

	 return  iErr;

 }


 int  refreshPeerInfo_wallD3d(  )
 {
	 int				iErr	=	-1;
	 QY_MC			*	pQyMc	=	QY_GET_GBUF(  );
	 GBuf_d3d_isCli  *  pGBuf  =  (  GBuf_d3d_isCli  *  )pQyMc->pGBuf_d3d;
	 if  (  !pGBuf  )  return  -1;

	 TCHAR	hint[128]  =  _T(  ""  );
	 if  (  !pGBuf->peer.idInfo_peer.ui64Id  )  {
		 pGBuf->peer.info.iAvStatus  =  0;
		 }
	 else  {
		   DLG_TALK_var  *  pDlgTalkVar  =  (  DLG_TALK_var  *  )getDlgTalkVar(  pGBuf->peer.hTalkerMgr  );
		   if  (  !pDlgTalkVar  )  goto  errLabel;
		   if  (  pGBuf->peer.info.iAvStatus  !=  pDlgTalkVar->guiData.av.iStatus  )  {
			   pGBuf->peer.info.iAvStatus  =  pDlgTalkVar->guiData.av.iStatus;
		   }
	 }

	 //
	 if  (  !pGBuf->peer.idInfo_peer.ui64Id  )  {
		 _sntprintf(  hint,  mycountof(  hint  ),  _T(  "Welcome"  )  );
	 }
	 else  {
		   _sntprintf(  hint,  mycountof(  hint  ),  _T(  "talk to %I64u"  ),  pGBuf->peer.idInfo_peer.ui64Id  );
	 }

	 if  (  _tcscmp(  hint,  pGBuf->hint  )  )  {
		 safeTcsnCpy(  hint,  pGBuf->hint,  mycountof(  pGBuf->hint  )  );
		 pGBuf->ucbChanged  =  TRUE;
	 }



	 iErr  =  0;
errLabel:
	 return  iErr;

}
