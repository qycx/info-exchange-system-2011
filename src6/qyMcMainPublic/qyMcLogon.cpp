

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"myresource.h"
#if  !defined(  __isCli__  )  &&  !defined(  __APP_qyMc_touchscreen__  )	//  __SUPPORT_SERV__
	#include	"dlgMcLogon.h"
#endif

#ifdef  __WINCE__
#ifndef  __TEST__
		#include	"ceMenuBar.h"
#endif
#endif

#include	"DlgMcClientLogon.h"




 BOOL	bQyMcLogon(  QY_MC  * pQyMc,  PF_commonHandler  pf_showDlgLogon  )
{
	 BOOL				bRet			=	FALSE;
	 QY_OBJ_DB		*	pObjDb			=	NULL;


	 if  (  pQyMc->iAppType  !=  CONST_qyAppType_client  )  {
		 #if  !defined(  __isCli__  )  &&  !defined(  __APP_qyMc_touchscreen__  )	//  __SUPPORT_SERV__
				  CDlgMcLogon		dlg;
				  if  (  IDOK  !=  dlg.DoModal( )  )  goto  errLabel;
		 #endif
		 }
	 else  {
#if  0
				CDlgMcClientLogon	dlg;

			#if  0
				if  (  IDOK  !=  dlg.DoModal(  )  )  goto  errLabel;
			#endif

			if  (  DialogBoxParam(  g_hInst,  MAKEINTRESOURCE(  IDD_mcClient_logon  ),  NULL,  dlgProc_mcClientLogon,  (  LPARAM  )&dlg  )  !=  IDOK  )  goto  errLabel;
#endif
			if  (  !pf_showDlgLogon  )  {
				#ifdef  __DEBUG__
						traceLog(  _T(  "bQyMcLogon failed, pf_showDlgLogon is null"  )  );
			    #endif
				goto  errLabel;
			}
			if  (  pf_showDlgLogon(  pQyMc->g_hInst,  pQyMc->gui.hMainWnd,  0  )  )  goto  errLabel;

	 }
	 
	 //  2005/09/30, 加上了对用户权限的校验
	 if  (  !pQyMc->curUsrInfo.right.bAdmin  &&  !pQyMc->curUsrInfo.right.bXtpz  &&  !pQyMc->curUsrInfo.right.bRzsj  )  {
		 traceLogA(  "not permitted"  );  goto  errLabel;
	 }
		 
	 pObjDb  =  getProcedObjDb(  0,  pQyMc->iDsnIndex_mainSys  );
	 if  (  !pObjDb  )  goto  errLabel;
	 pObjDb->pLogObjDb  =  pObjDb;		//  指向自己，因为是用来记日志的
	 pObjDb->pUsrInfo	=	&pQyMc->curUsrInfo;

	 bRet  =  TRUE;
	 
errLabel:

	 if  (  !bRet  )  {
		 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bQyMcLogon failed."  )  );
	 }

	 if  (  bRet  )  {
		 pQyMc->bLogon = TRUE;	 
		 pQyMc->dwTickCnt_logon  =  GetTickCount(  );

		 qnmLogOpEvent(  pQyMc->iServiceId,  pObjDb,  CONST_qyEventType_nm_logon,  _T(  ""  )  );

		 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bQyMcLogon ok."  )  );
	 }

	 return  bRet;

}


 void  qyMcLogoff(  QY_MC  *  pQyMc  )
{
	 if  (  !pQyMc->bLogon  )  return;

	 QY_OBJ_DB	*	pObjDb	=	NULL;

	 pObjDb  =  getProcedObjDb(  0,  pQyMc->iDsnIndex_mainSys  );

	 qnmLogOpEvent(  pQyMc->iServiceId,  pObjDb,  CONST_qyEventType_nm_logoff,  _T(  ""  )  );

	 memset(  &pQyMc->curUsrInfo,  0,  sizeof(  pQyMc->curUsrInfo  )  );

	 pQyMc->bLogon  =  FALSE;

	 return;
}

