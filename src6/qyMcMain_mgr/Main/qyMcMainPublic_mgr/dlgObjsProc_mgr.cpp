

#include	"stdafx.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainCommon.h"

//  #include	"DlgObjs.h"
//  #include	"DlgTalk_ce.h"
#include	"dlgObjsProc.h"
#include	"qnmResDefs.h"
#include	"dlgTalkProc.h"

#include	"myDb.h"


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
#include	<dsound.h>

#include	"qmcDmoPublic.h"

#include	"qmcVideoCapture_dx.h"

#include	"myfourcc.h"
#include	"mywmcodecconst.h"

#include	"qmcCmdProc.h"
#include	"qyCusResTemp.h"


char  *  displayShortTime(  time_t  t,  char  *  timeBuf,  unsigned  int  len  );


#ifdef  __NOTSUPPORT_DB__

 int  tmpHandler_printQmObjQ(  void  *  p0,  void  *  p1,  QM_OBJQ_MEM  *  pMem  )
{
	int							iErr	=	-1;
	//  CDlgObjs				*   pDlg	=  (  CDlgObjs  *  )p0;
	HWND						hDlg	=	(  HWND  )p0;
	DLG_objs_var			*	pVar	=	(  DLG_objs_var  *  )p1;
	if  (  !pVar  )  return  -1;
	DLG_objs_var			&	m_var	=	*pVar;

	QY_MC					*	pQyMc	=	QY_GET_GBUF(  );
	QY_DMITEM				*	pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );
	//  char						idStr[32]	=  "";
				  

	QMEM_MESSENGER_CLI		*	pQMemObj;

	pQMemObj  =  (  QMEM_MESSENGER_CLI  *  )pMem->pQMemObj;

	switch  (  m_var.guiData.param.uiType  )  {
			case  CONST_objType_imGrp:
				  if  (  pQMemObj->uiType  !=  CONST_objType_imGrp  )  {
					  iErr  =  0;  goto  errLabel;
				  }
				  break;
			case  CONST_objType_messenger:
				  if  (  pQMemObj->uiType  ==  CONST_objType_imGrp  )  {
					  iErr  =  0;  goto  errLabel;
				  }
				  break;
			default:
				    iErr  =  0;  goto  errLabel;
	}

	//  _snprintf(  idStr, mycountof(  idStr  ),  "%I64u",  pQMemObj->idInfo.ui64Id  );

	HWND	hCtl	=	GetDlgItem(  hDlg,  m_var.guiData.iIDC_LIST0  );
	TCHAR	tBuf[256];
	int		tmpiRet;

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u %s"  ),  pQMemObj->idInfo.ui64Id,  pQMemObj->talkerDesc  );
	tmpiRet  =  SendMessage(  hCtl,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "\t%d,  %s, idInfo is %I64u, talkerDesc %s"  ),  m_var.usItemCount,  qyGetDesByType1(  pTable,  pQMemObj->uiType  ),  pQMemObj->idInfo.ui64Id,  pQMemObj->talkerDesc  );
	OutputDebugString(  tBuf  );
	OutputDebugString(  _T(  "\n"  )  );


	m_var.usItemCount  ++;

	iErr  =  0;
errLabel:
	return  iErr;
}

 #else  __NOTSUPPORT_DB__

#ifdef  __isCli__
 int  fillImObjs_selectRemoteVideo(  HWND  hDlg,  void  *  pVarParam  )
 {
	int  iRet  =  -1;
	QY_MC		*pQyMc		=	QY_GET_GBUF(  );

	DLG_objs_var  *  pVar  =  (  DLG_objs_var  *  )pVarParam;
	DLG_TALK_var  *  pDlgTalkVar  =  getDlgTalkVar(  pVar->guiData.param.hCurTalk  );
	if  (  !pDlgTalkVar  )  goto  errLabel;
	DLG_TALK_var  *	 pMgrVar	  =	 pDlgTalkVar;
	if  (  !isTalkerShadowMgr(  pDlgTalkVar->addr  )  )  {
		TALKER_shadow  *  pShadow  =  (  TALKER_shadow  *  )pDlgTalkVar->pShadowInfo;
		if  (  !pShadow  )  goto  errLabel;
		pMgrVar  =  getDlgTalkVar(  pShadow->hMgr  );
		if  (  !pMgrVar  )  goto  errLabel;
	}

	 
	QY_DMITEM	*	pTable	=	getResTable(  0,  &pQyMc->cusRes,  CONST_resId_remoteVideoTable  );
	QY_DMITEM	*	pItem;
	HWND	hCtl	=	GetDlgItem(  hDlg,  pVar->guiData.iIDC_LIST0  );

	int		tmpiRet;

	int		n  =  getnItems(  pTable  );
	if  (  n  <  0  )  goto  errLabel;
	pVar->uiSize_pData  =  n  *  sizeof(  QY_COLUMNINFO  );
	pVar->pData  =  malloc(  pVar->uiSize_pData  );
	if  (  !pVar->pData  )  goto  errLabel;
	memset(  pVar->pData,  0,  pVar->uiSize_pData  );

	pVar->dataHead.u.selectRemoteVideo.nColumns  =  n;
	QY_COLUMNINFO  *  pColumns  =  (  QY_COLUMNINFO  *  )pVar->pData;
	for  (  n  =  0,  pItem  =  pTable;  pItem->type  !=  -1;  n  ++  ,  pItem  ++  )  {
		 if  (  n  >=  pVar->dataHead.u.selectRemoteVideo.nColumns  )  goto  errLabel;
		 pColumns[n].type  =  pItem->type;
		 safeTcsnCpy(  pItem->des,  pColumns[n].label,  mycountof(  pColumns[n].label  )  );
		 switch  (  pItem->type  )  {
				 case  CONST_resId_selectScreen:
					   if  (  pMgrVar->vwRuleCmd_manual.ucbViewScreen  )  pColumns[n].lParam  =  TRUE;
					   break;
				 case  CONST_resId_selectWebcam0:
					   if  (  pMgrVar->vwRuleCmd_manual.ucbViewWebcam0  )  pColumns[n].lParam  =  TRUE;
					   break;
				 case  CONST_resId_selectWebcam1:
					   if  (  pMgrVar->vwRuleCmd_manual.ucbViewWebcam1  )  pColumns[n].lParam  =  TRUE;
					   break;
				 case  CONST_resId_selectWebcam2:
					   if  (  pMgrVar->vwRuleCmd_manual.ucbViewWebcam2  )  pColumns[n].lParam  =  TRUE;
					   break;
				 default:
						 break;
		 }
		 if  (  pColumns[n].lParam  )  _sntprintf(  pColumns[n].label,  mycountof(  pColumns[n].label  ),  _T(  "%s ( %s )"  ),  pColumns[n].label,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_started  )  );
		 //
		 tmpiRet  =  SendMessage(  hCtl,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )pColumns[n].label  );    

	}


	 iRet  =  0;
errLabel:

	 return  iRet;
 }

  int  fillImObjs_selectADev(  HWND  hDlg,  void  *  pVarParam  )
 {
	int  iRet  =  -1;
	QY_MC		*pQyMc		=	QY_GET_GBUF(  );
	DLG_objs_var  *  pVar  =  (  DLG_objs_var  *  )pVarParam;
	

	if  (  !pVar->guiData.param.p0  )  return  -1;
	CAP_STUFF	&	gcap	=	*(  CAP_STUFF  *  )pVar->guiData.param.p0;

	int		tmpiRet;
	HWND	hCtl	=	GetDlgItem(  hDlg,  pVar->guiData.iIDC_LIST0  );

	int		i;
	int		iSel  =  -1;
	for  (  i  =  0;  i  <  min(  mycountof(  gcap.old_audioDevices.mems  ),  gcap.old_audioDevices.iNumACapDevices  );  i  ++  )  {
		tmpiRet  =  SendMessage(  hCtl,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )gcap.old_audioDevices.mems[i].names_audio  );    		
		 if  (  pVar->guiData.param.iMenuId_selectedDev
			 &&  gcap.old_audioDevices.mems[i].iMenuIds_audio  ==  pVar->guiData.param.iMenuId_selectedDev  )
		 {
			 iSel  =  i;
		 }
	}

	//
	if  (  iSel  >=  0  )  {
		tmpiRet  =  SendMessage(  hCtl,  LB_SETCURSEL,  (  WPARAM  )iSel,  (  LPARAM  )0  );    		 		 
	}
	
	//
	iRet  =  0;

errLabel:
	return  iRet;
  }

    int  fillImObjs_selectVDev(  HWND  hDlg,  void  *  pVarParam  )
 {
	int  iRet  =  -1;
	QY_MC		*pQyMc		=	QY_GET_GBUF(  );
	
	DLG_objs_var  *  pVar  =  (  DLG_objs_var  *  )pVarParam;
	
	if  (  !pVar->guiData.param.p0  )  return  -1;
	CAP_STUFF	&	gcap	=	*(  CAP_STUFF  *  )pVar->guiData.param.p0;

	int		tmpiRet;
	HWND	hCtl	=	GetDlgItem(  hDlg,  pVar->guiData.iIDC_LIST0  );

	int		i;
	int		iSel  =  -1;
	for  (  i  =  0;  i  <  min(  mycountof(  gcap.rgpmVideoMenu  ),  gcap.iNumVCapDevices  );  i  ++  )  {
		TCHAR	tBuf[256];
		getMonikerFriendlyName(  gcap.rgpmVideoMenu[i],  tBuf,  mycountof(  tBuf  )  );
		 tmpiRet  =  SendMessage(  hCtl,  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    		
		 if  (  pVar->guiData.param.iMenuId_selectedDev
			 &&  getMoniker_v(  &gcap,  pVar->guiData.param.iMenuId_selectedDev  )  ==  gcap.rgpmVideoMenu[i]  )
		 {
			 iSel  =  i;
		 }
	}

	//
	if  (  iSel  >=  0  )  {
		tmpiRet  =  SendMessage(  hCtl,  LB_SETCURSEL,  (  WPARAM  )iSel,  (  LPARAM  )0  );    		 		 
	}


	iRet  =  0;

errLabel:
	return  iRet;
  }
#endif

 int  fillImObjs(  HWND  hDlg,  void  *  pVar  )
{
	int				iErr	=	-1;
	DLG_objs_var	&	m_var	=	*(  DLG_objs_var  *  )pVar;
	QY_MC		*	pQyMc	=	QY_GET_GBUF(  );
	QY_OBJ_DB	*	pObjDb  =  getProcedObjDb(  0,  pQyMc->iDsnIndex_mainSys  );
	if  (  !pObjDb  )  return  -1;
	TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1];
	CDBVariant		varVals[10];

		QM_dbFuncs  *  pDbFuncs  =  QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	switch  (  m_var.guiData.param.uiType  )  {
			case  CONST_objType_messenger:

				  g_dbFuncs.pf_fillImObjs_msgr(  hDlg,  pVar,  pObjDb->pDb  );
				  break;

			case  CONST_objType_imGrp:

				  g_dbFuncs.pf_fillImObjs_grp(  hDlg,  pVar,  pObjDb->pDb  );
				  break;
			
#ifdef  __isCli__
			case  CONST_objType_selectRemoteVideo:
				  fillImObjs_selectRemoteVideo(  hDlg,  pVar  );
				  break;
			case  CONST_objType_selectADev:
				  fillImObjs_selectADev(  hDlg,  pVar  );
				  break;
			case  CONST_objType_selectVDev:
				  fillImObjs_selectVDev(  hDlg,  pVar  );
				  break;
#endif
			default:
					break;
	}


	iErr  =  0;
errLabel:
	return  iErr;
 }
#endif


 //  2012/04/21
  int  tmpHandler_showActiveTalker(  void  *  p0,  void  *  p1,  MIS_MSGU  *  pMsg  )
{
	//  CDlgObjs  *		pDlg				=  (  CDlgObjs  *  )p0;
	HWND			hDlg				=	(  HWND  )p0;
	DLG_objs_var	*	pVar			=	(  DLG_objs_var  *  )p1;
	if  (  !pVar  )  return  -1;
	DLG_objs_var	&	m_var			=	*pVar;
	//
	TCHAR			tBuf[256]			=	_T(  ""  );
	char			buf[32]				=	"";
	
	MIS_CNT			*	pMisCnt			=	getMisCntByName(  0,  0,  _T(  ""  )  );
	if  (  !pMisCnt  )  return  -1;

	TCHAR	talkerDesc[128];

#ifdef  __isCli__
	switch  (  pMsg->uiType  )  {
			case  CONST_misMsgType_talkingFriend_qmc:
				  
				  //  影子窗口不需要显示
				  if  (  pMsg->talkingFriend_qmc.addr.uiTranNo_shadow  )  break;

				  //
				  getTalkerDesc(  pMisCnt,  &pMsg->talkingFriend_qmc.addr.idInfo,  0,  0,  talkerDesc,  mycountof(  talkerDesc  )  );

				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%I64u %s"  ),  pMsg->talkingFriend_qmc.addr.idInfo.ui64Id,  talkerDesc  );

				  //  2012/05/24
				  DLG_TALK_var  *  pDlgTalkVar;
				  pDlgTalkVar  =  getDlgTalkVar(  pMsg->talkingFriend_qmc.hWnd  );
				  if  (  pDlgTalkVar  )  {
					  if  (  pDlgTalkVar->ucbTmpMsgr  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s ( Tmp )"  ),  tBuf  );
				  }
				  //
				  SendMessage(  GetDlgItem(  hDlg,  m_var.guiData.iIDC_LIST0  ),  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    
				  break;
			default:
					break;
	}
#endif

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "\t%d"  ),  m_var.usItemCount );
	OutputDebugString(  tBuf  );
	OutputDebugString(  _T(  "\n"  )  );
	



	return  0;
}


  int  tmpHandler_showImMsgLogQ(  void  *  p0,  void  *  p1,  MIS_MSGU  *  pMsg  )
{
	//  CDlgObjs  *		pDlg				=  (  CDlgObjs  *  )p0;
	HWND			hDlg				=	(  HWND  )p0;
	DLG_objs_var	*	pVar			=	(  DLG_objs_var  *  )p1;
	if  (  !pVar  )  return  -1;
	DLG_objs_var	&	m_var			=	*pVar;
	//
	TCHAR			tBuf[256]			=	_T(  ""  );
	char			buf[32]				=	"";
	TCHAR			senderDesc[64]		=	_T(  ""  );
	TCHAR			receiverDesc[64]	=	_T(  ""  );
	IM_CONTENTU	*	pContent			=	NULL;
	
	switch  (  pMsg->uiType  )  {
			case  CONST_misMsgType_talk:
				  pContent  =  (  IM_CONTENTU  *  )pMsg->talk.data.buf;
				  displayShortTime(  pMsg->talk.tStartTime,  buf,  mycountof(  buf  )  );
				  getTalkerDesc(  (  MIS_CNT  *  )pMsg->talk.pMisCnt,  &pMsg->talk.data.route.idInfo_from,  0,  0,  senderDesc,  mycountof(  senderDesc  )  );
				  getTalkerDesc(  (  MIS_CNT  *  )pMsg->talk.pMisCnt,  &pMsg->talk.data.route.idInfo_to,  0,  0,  receiverDesc,  mycountof(  receiverDesc  )  );

				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u %s->%I64u %s"  ),  CQyString(  buf  ),  pMsg->talk.data.route.idInfo_from.ui64Id,  senderDesc,  pMsg->talk.data.route.idInfo_to.ui64Id,  receiverDesc  );
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s: %s"  ),  tBuf,  qyGetDesByType1(  getResTable(  0,  &g_pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );
				  if  (  pContent->uiType  ==  CONST_imCommType_htmlContent  )  {
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %s"  ),  tBuf,  pContent->html.wBuf  );
				  }

				  SendMessage(  GetDlgItem(  hDlg,  m_var.guiData.iIDC_LIST0  ),  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    
				  break;
			case  CONST_misMsgType_task:
				  pContent  =  (  IM_CONTENTU  *  )pMsg->task.data.buf;
				  displayShortTime(  pMsg->task.tStartTime,  buf,  mycountof(  buf  )  );
				  getTalkerDesc(  (  MIS_CNT  *  )pMsg->task.pMisCnt,  &pMsg->task.data.route.idInfo_from,  0,  0,  senderDesc,  mycountof(  senderDesc  )  );
				  getTalkerDesc(  (  MIS_CNT  *  )pMsg->task.pMisCnt,  &pMsg->task.data.route.idInfo_to,  0,  0,  receiverDesc,  mycountof(  receiverDesc  )  );

				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %I64u %s->%I64u %s"  ),  CQyString(  buf  ),  pMsg->task.data.route.idInfo_from.ui64Id,  senderDesc,  pMsg->task.data.route.idInfo_to.ui64Id,  receiverDesc  );
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s: %s"  ),  tBuf,  qyGetDesByType1(  getResTable(  0,  &g_pQyMc->cusRes,  CONST_resId_qyCommTypeTable  ),  pContent->uiType  )  );
				  if  (  pContent->uiType  ==  CONST_imCommType_htmlContent  )  {
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %s"  ),  tBuf,  pContent->html.wBuf  );
				  }

				  SendMessage(  GetDlgItem(  hDlg,  m_var.guiData.iIDC_LIST0  ),  LB_INSERTSTRING,  (  WPARAM  )-1,  (  LPARAM  )tBuf  );    

				  break;
			default:
					break;
	}

	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "\t%d"  ),  m_var.usItemCount );
	OutputDebugString(  tBuf  );
	OutputDebugString(  _T(  "\n"  )  );
	



	return  0;
}



 __declspec(  dllexport  )  BOOL  dlgObjs_bFillContent(  HWND  hDlg,  void  *  pVar,  int  iObjType  )
{
	BOOL	bRet	=	FALSE;

	if  (  !pVar  )  return  FALSE;
	DLG_objs_var  &  m_var  =  *(  DLG_objs_var  *  )pVar;


	HWND	hCtl	=	GetDlgItem(  hDlg,  m_var.guiData.iIDC_LIST0  );

	SendMessage(  hCtl,  LB_RESETCONTENT,  0,  0  );
	m_var.usItemCount  =  0;

	int				iErr		=	-1;
	QY_MC		*	pQyMc		=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo	=	QY_GET_procInfo_isCli(  );
	int				idc_hidden	=	0;
	BOOL			bHidden;
	int				idc;
	MIS_CNT		*	pMisCnt		=	NULL;

	m_var.pMisCnt  =  getMisCntByName(  pQyMc,  NULL,  _T(  ""  )  );  
	pMisCnt  =  (  MIS_CNT  *  )m_var.pMisCnt;

	m_var.guiData.param.uiType  =  iObjType;

	switch  (  m_var.guiData.param.uiType  )  {
			case  CONST_objType_messenger:
				  #ifdef  __NOTSUPPORT_DB__
						  qmObjQTraverse(  0,  pMisCnt->pObjQ,  (  PF_commonHandler  )tmpHandler_printQmObjQ,  hDlg,  &m_var  );
				  #else
						fillImObjs(  hDlg,  pVar  );
				  #endif
				  idc_hidden  =  m_var.guiData.iIDC_BUTTON_contact;
				  break;
			case  CONST_objType_imGrp:
				  #ifdef  __NOTSUPPORT_DB__
						  qmObjQTraverse(  0,  pMisCnt->pObjQ,  (  PF_commonHandler  )tmpHandler_printQmObjQ,  hDlg,  &m_var  );
				  #else
						fillImObjs(  hDlg,  pVar  );
				  #endif
				  idc_hidden  =  m_var.guiData.iIDC_BUTTON_group;
				  break;

			case  CONST_objType_selectRemoteVideo:
				  fillImObjs(  hDlg,  pVar  );
				  break;				  
				  
			case  CONST_objType_selectADev:			//  2013/04/04
			case  CONST_objType_selectVDev:			//  2013/04/04
				  fillImObjs(  hDlg,  pVar  );
				  break;				  

			default:
				    if  (  m_var.guiData.param.ucbActiveTalker  )  {		//  2012/04/21
						if  (  !pMisCnt  )  goto  errLabel;
						qTraverse(  &pMisCnt->talkingFriendQ,  (  PF_commonHandler  )tmpHandler_showActiveTalker,  hDlg,  &m_var  );
					
						break;
					}

				    qTraverse(  &pProcInfo->imMsgLogQ,  (  PF_commonHandler  )tmpHandler_showImMsgLogQ,  hDlg,  &m_var  );
					idc_hidden  =  m_var.guiData.iIDC_BUTTON_status;
					break;
	}

	idc  =  m_var.guiData.iIDC_BUTTON_contact;
	bHidden  =  idc_hidden  ==  idc;
	ShowWindow(  GetDlgItem(  hDlg,  idc  ),  bHidden  ?  SW_HIDE  :  SW_SHOW  );

	idc  =  m_var.guiData.iIDC_BUTTON_group;
	bHidden  =  idc_hidden  ==  idc;
	ShowWindow(  GetDlgItem(  hDlg,  idc  ),  bHidden  ?  SW_HIDE  :  SW_SHOW  );

	idc  =  m_var.guiData.iIDC_BUTTON_status;
	bHidden  =  idc_hidden  ==  idc;
	ShowWindow(  GetDlgItem(  hDlg,  idc  ),  bHidden  ?  SW_HIDE  :  SW_SHOW  );

	bRet  =  TRUE;

errLabel:

	return  bRet;
}

 __declspec(  dllexport  )  int dlgObjs_OnOK(  HWND  hDlg,  void  *  pVarParam  )
{
	int		iErr	=	-1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	if  (  !pVarParam  )  return  -1;
	DLG_objs_var	&	m_var  =  *(  DLG_objs_var  *  )pVarParam;
	MIS_CNT			*	pMisCnt	=	(  MIS_CNT  *  )m_var.pMisCnt;
	
	// TODO: Add your specialized code here and/or call the base class
	//
	CQyMalloc	mallocObj;
	TCHAR  *	pT	=	NULL;

	HWND	hCtrl  =  GetDlgItem(  hDlg,  m_var.guiData.iIDC_LIST0  );

	int			iItemSelected	=	SendMessage(  hCtrl,  LB_GETCURSEL,  0,  0  );	
	if  (  iItemSelected  <  0  )  goto  errLabel;

	int		len  =  SendMessage(  hCtrl,  LB_GETTEXTLEN,  iItemSelected,  0  );
	if  (  len  <  0  )  goto  errLabel;
	len  ++  ;

	pT  =  (  TCHAR  *  )mallocObj.malloc(  sizeof(  TCHAR  )  *  len  );
	if  (  !pT  )  goto  errLabel;
	SendMessage(  hCtrl,  LB_GETTEXT,  iItemSelected,  (  LPARAM  )pT  );

	char						buf[32];
	QY_MESSENGER_ID				idInfo_selected;
	TCHAR					*	pT1;


	switch  (  m_var.guiData.param.uiType  )  {
			case  CONST_objType_messenger:
			case  CONST_objType_imGrp:
				  pT1  =  _tcschr(  pT,  _T(  ' '  )  );
				  if  (  !pT1  )  goto  errLabel;
				  *pT1  =  0;

				  myTChar2Str(  pT,  buf,  mycountof(  buf  )  );
				  idStr2Info(  buf,  &idInfo_selected  );
				  //
				  if  (  idInfo_selected.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  goto  errLabel;
				  //
				  m_var.guiData.param.o.ui64Id_selected  =  idInfo_selected.ui64Id;
				  break;
			case  CONST_objType_selectRemoteVideo:  {
				  //  2013/02/13
				  QY_COLUMNINFO  *  pColumns  =  (  QY_COLUMNINFO  *  )m_var.pData;
				  if  (  iItemSelected  <  0  ||  iItemSelected  >=  m_var.dataHead.u.selectRemoteVideo.nColumns  )  goto  errLabel;

				  m_var.guiData.param.o.iVal_selected  =  pColumns[iItemSelected].type;

				  }
				  break;
			case  CONST_objType_selectADev:	{
				  if  (  !m_var.guiData.param.p0  )  goto  errLabel;
				  CAP_STUFF  &  gcap  =  *(  CAP_STUFF  *  )m_var.guiData.param.p0;
				  if  (  iItemSelected  <  0  ||  iItemSelected  >=  mycountof(  gcap.old_audioDevices.mems  )  )  goto  errLabel;
				  m_var.guiData.param.o.iSel  =  iItemSelected;
				  }
				  break;
			case  CONST_objType_selectVDev:  {
				  if  (  !m_var.guiData.param.p0  )  goto  errLabel;
				  CAP_STUFF  &  gcap  =  *(  CAP_STUFF  *  )m_var.guiData.param.p0;
				  if  (  iItemSelected  <  0  ||  iItemSelected  >=  mycountof(  gcap.rgpmVideoMenu  )  )  goto  errLabel;
				  m_var.guiData.param.o.iSel  =  iItemSelected;
				  }
				  break;
			default:

				  //  2012/04/21
				  if  (  m_var.guiData.param.ucbActiveTalker  )  {
					  pT1  =  _tcschr(  pT,  _T(  ' '  )  );
					  if  (  !pT1  )  goto  errLabel;
					  *pT1  =  0;

					  myTChar2Str(  pT,  buf,  mycountof(  buf  )  );
					  idStr2Info(  buf,  &idInfo_selected  );
					  //
					  if  (  idInfo_selected.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  goto  errLabel;
					  //
					  m_var.guiData.param.o.ui64Id_selected  =  idInfo_selected.ui64Id;
					  break;
				  }

				  pT1  =  _tcschr(  pT,  _T(  ' '  )  );
				  if  (  !pT1  )  goto  errLabel;
				  pT1  ++  ;
				  pT  =  pT1;  

				  pT1  =  _tcschr(  pT,  _T(  '>'  )  );
				  if  (  !pT1  )  goto  errLabel;
				  *pT1  =  0;  pT1  ++  ;

				  tTrim(  pT  );
				  myTChar2Str(  pT,  buf,  mycountof(  buf  )  );
				  idStr2Info(  buf,  &idInfo_selected  );
				  if  (  idInfo_selected.ui64Id  ==  pMisCnt->idInfo.ui64Id  )  {
					  pT  =  pT1;
					  pT1  =  _tcschr(  pT,  _T(  ':'  )  );
					  if  (  !pT1  )  goto  errLabel;
					  *pT1  =  0;

					  myTChar2Str(  pT,  buf,  mycountof(  buf  )  );
		
					  idStr2Info(  buf,  &idInfo_selected  );
				  }	
				  m_var.guiData.param.o.ui64Id_selected  =  idInfo_selected.ui64Id;
				  break;
	}

	iErr  =  0;
errLabel:
	return  iErr;
	
}

 __declspec(  dllexport  )  int dlgObjs_OnLbnSelchangeList0(  HWND  hDlg,  void  *  pVarParam  )
{
	int  iErr  =  -1;

	DLG_objs_var  *  pVar	=  (  DLG_objs_var  *  )pVarParam;
	QY_MC		  *  pQyMc	=  QY_GET_GBUF(  );

	CQyMalloc	mallocObj;
	TCHAR  *  pT	=  NULL;

	HWND	hCtrl  =  GetDlgItem(  hDlg,  pVar->guiData.iIDC_LIST0  );

	int  iItemSelected  =  SendMessage(  hCtrl,  LB_GETCURSEL,  0,  0  );
	if  (  iItemSelected  ==  LB_ERR  )  goto  errLabel;

	int  len  =  SendMessage(  hCtrl, LB_GETTEXTLEN,  iItemSelected,  0  );
	if  (  !len  )  goto  errLabel;
	len  ++;

	pT  =  (  TCHAR  *  )mallocObj.malloc(  sizeof(  TCHAR  )  *  len  );
	if  (  !pT  )  goto  errLabel;
	SendMessage(  hCtrl,  LB_GETTEXT,  iItemSelected,  (  LPARAM  )pT  );


	switch  (  pVar->guiData.param.uiType  )  {
			case  CONST_objType_selectRemoteVideo:  {
				  QY_DMITEM	   *  pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_remoteVideoTable  );
				  QY_COLUMNINFO  *  pColumns  =  (  QY_COLUMNINFO  *  )pVar->pData;
				  int				  n;

				  if  (  iItemSelected  <  0  ||  iItemSelected  >=  pVar->dataHead.u.selectRemoteVideo.nColumns  )  goto  errLabel;

				  if  (  pColumns[iItemSelected].lParam  )  SetDlgItemText(  hDlg,  pVar->guiData.iIDOK,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_stop  )  );
				  else  SetDlgItemText(  hDlg,  pVar->guiData.iIDOK,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_start  )  );
				  }
				  break;
			default:
					break;
	}

	iErr  =  0;
errLabel:
	return  iErr;
}