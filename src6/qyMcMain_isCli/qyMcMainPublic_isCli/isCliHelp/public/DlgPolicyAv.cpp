// DlgPolicyAv.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qyMc.h"
#include	"myresource.h"
#include	"DlgPolicyAv.h"
#include	"qyCusResTemp.h"
//
//  #include	"DlgVideoCompressors.h"
#include	"qmshell_open.h"
#include	"policyAvParams.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

extern    int  getDefaultPolicyAvLevel(  unsigned  int  uiCapType,  unsigned int uiSubCapType,  BOOL  bReply  );


__declspec(  dllexport  )  int  showDlgPolicyAv(  HWND  hParent,  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  BOOL  bReply  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int		iRet	=	-1;
	
	CDlgPolicyAv	dlg(  CWnd::FromHandle(  hParent  )  );
	dlg.bSetDlgInfo(  uiCapType,  uiSubCapType,  bReply  );
	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;

	iRet  =  IDOK;
errLabel:
	return  iRet;
}

// CDlgPolicyAv dialog

IMPLEMENT_DYNAMIC(CDlgPolicyAv, CDialog)

CDlgPolicyAv::CDlgPolicyAv(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPolicyAv::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );

}

CDlgPolicyAv::~CDlgPolicyAv()
{
}


#if  0
BOOL  CDlgPolicyAv::bSetDlgInfo(  int  level  )
{
	m_var.level  =  level;
	return  TRUE;
}
#endif

BOOL  CDlgPolicyAv::bSetDlgInfo(  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  BOOL  bReply  )
{
	m_var.uiCapType  =  uiCapType;
	m_var.uiSubCapType  =  uiSubCapType;
	m_var.bReply  =  bReply;

	return  TRUE;
}


BOOL  CDlgPolicyAv::bShowPolicy(  )
{
	QY_MC			*	pQyMc				=	QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo			=	QY_GET_procInfo_isCli(  );
	PolicyAvParams	&	gAvParams			=	*QY_GET_PolicyAvParams(  );

	/////////////
#if  0
	switch  (  m_var.uiCapType  )  {
		case  CONST_capType_av:
			  if  (  m_var.uiSubCapType  ==  CONST_subCapType_webcam  ) {
				  SetDlgItemInt(  IDC_EDIT_ucSeconds_perFrame,  m_var.oldPolicyAv.avCompressor_req.ucSeconds_perFrame_videoConference  );
				  GetDlgItem(  IDC_EDIT_ucSeconds_perFrame  )->EnableWindow(  FALSE  );
				  SetDlgItemInt(  IDC_EDIT_usFrames_perSecond,  m_var.oldPolicyAv.avCompressor_req.usFrames_perSecond_videoConference  );
				  SetDlgItemInt(  IDC_EDIT_iWidth_webcam,  m_var.oldPolicyAv.avCompressor_req.video.iWidth_pic  );
				  SetDlgItemInt(  IDC_EDIT_iHeight_webcam,  m_var.oldPolicyAv.avCompressor_req.video.iHeight_pic  );
				  SetDlgItemInt(  IDC_EDIT_usMaxFPS_toShareBmp,  m_var.oldPolicyAv.avCompressor_req.video.common.usMaxFps_toShareBmp  );
			  }
			  else  {
				  if  (  m_var.bReply  )  {
					  SetDlgItemInt(  IDC_EDIT_ucSeconds_perFrame,  m_var.oldPolicyAv.avCompressor_reply.ucSeconds_perFrame_videoConference  );
					  GetDlgItem(  IDC_EDIT_ucSeconds_perFrame  )->EnableWindow(  FALSE  );
					  SetDlgItemInt(  IDC_EDIT_usFrames_perSecond,  m_var.oldPolicyAv.avCompressor_reply.usFrames_perSecond_videoConference  );
					  SetDlgItemInt(  IDC_EDIT_iWidth,  m_var.oldPolicyAv.avCompressor_reply.video.iWidth_pic  );
					  SetDlgItemInt(  IDC_EDIT_iHeight,  m_var.oldPolicyAv.avCompressor_reply.video.iHeight_pic  );
					  SetDlgItemInt(  IDC_EDIT_usMaxFps_webcam,  m_var.oldPolicyAv.avCompressor_req.video.common.usMaxFps_toShareBmp  );
				  }
				  else  {
					  SetDlgItemInt(  IDC_EDIT_ucSeconds_perFrame,  m_var.oldPolicyAv.avCompressor_req.ucSeconds_perFrame_videoConference  );
					  GetDlgItem(  IDC_EDIT_ucSeconds_perFrame  )->EnableWindow(  FALSE  );
					  SetDlgItemInt(  IDC_EDIT_usFrames_perSecond,  m_var.oldPolicyAv.avCompressor_req.usFrames_perSecond_videoConference  );
					  SetDlgItemInt(  IDC_EDIT_iWidth,  m_var.oldPolicyAv.avCompressor_req.video.iWidth_pic  );
					  SetDlgItemInt(  IDC_EDIT_iHeight,  m_var.oldPolicyAv.avCompressor_req.video.iHeight_pic  );
					  SetDlgItemInt(  IDC_EDIT_usMaxFPS_toShareBmp,  m_var.oldPolicyAv.avCompressor_req.video.common.usMaxFps_toShareBmp  );
				  }
			  }
			  break;
		case  CONST_capType_mediaFile:
			  SetDlgItemInt(  IDC_EDIT_usMaxFps_mediaFile,  m_var.oldPolicyAv.avCompressor_req.video.common.usMaxFps_toShareBmp  );
			  break;
		case  CONST_capType_screen:
			  SetDlgItemInt(  IDC_EDIT_usMaxFPS_capScreen,  m_var.oldPolicyAv.avCompressor_req.video.common.usMaxFps_toShareBmp  );
			  break;
		case  CONST_capType_mediaDevice:
			  SetDlgItemInt(  IDC_EDIT_usFps_mediaDevice,  m_var.oldPolicyAv.avCompressor_req.video.common.usMaxFps_toShareBmp  );
			  break;
		default:
			break;
	}
#endif
	QY_REG				reg;
	TCHAR			*	pRegVal				=	NULL;
	TCHAR				tBuf[128]			=  _T(  ""  );
	TCHAR				tRootKey[256]		=	_T(  ""  );
	TCHAR			*   pT					=   NULL;
	CComboBox		*	pCb			=	NULL;
	//  long				lVal;
	int					level;
	int					idc			=	0;
	QY_DMITEM		*	pTable		=	NULL;
	QY_DMITEM		*	pItem		=	NULL;
	//  unsigned  char		ucCmd		=	0;
	//


#if  0
	if  (  bReply  )  level  =  pProcInfo->cfg.policy.iPolicyAvLevel_reply;
	else  if  (  !level  )  level  =  pProcInfo->cfg.policy.iPolicyAvLevel_req;
	if  (  !qyGetDesByType(  getResTable(  0,  &pQyMc->cusRes,  gAvParams.iResId_policyAvLevelTable  ),  level  )  )  level  =  CONST_policyAvLevel_ld;
#endif


	memset(  &reg,  0,  sizeof(  reg  )  );
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	//  safeStrnCpy(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	lstrcpyn(  reg.rootKey,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );
	//  AV_COMPRESSOR_CFG	avCompressor;

	switch  (  m_var.uiCapType  )  {
			case  CONST_capType_av:
				if  (  m_var.uiSubCapType  ==  CONST_subCapType_webcam  )  {
					pTable  =  getResTable(  0,  &pQyMc->cusRes,  gAvParams.iResId_policyAvLevelTable_webcam  );
					idc  =  IDC_COMBO_req;
					pRegVal  =  CONST_regValName_policyAvLevel_req;
					pCb  =  (  CComboBox  *  )GetDlgItem(  idc  );
					pCb->ResetContent(  );
					for  (  pItem  =  pTable;  pItem->type  !=  -1;  pItem  ++  )  pCb->AddString(  CQyString(  pItem->des  )  );
					if  (  !(  level  =  pProcInfo->cfg.policy.iPolicyAvLevel_webcam  )  )  level  =  DEFAULT_policyAvLevel_req_webcam;
					_sntprintf(  tRootKey,  mycountof(  tRootKey  ),  _T(  "%s\\%s.%s"  ),  reg.rootKey,  qyGetDesByType(  CONST_capTypeTable,  m_var.uiCapType  ),  qyGetDesByType(  CONST_subCapTypeTable,  m_var.uiSubCapType  )  );
					if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  tRootKey,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )
							&&  _ttol(  tBuf  )  
							&&  qyGetDesByType(  pTable,  _ttol(  tBuf  )  )	 )
						{
							level  =  (  unsigned  char  )_ttol(  tBuf  );
						}
					pCb->SelectString(  -1,  CQyString(  qyGetDesByType1(  pTable, level  )  )  );

					//
					level  =  CONST_policyAvLevel_ld;
					idc  =  IDC_STATIC_ldSettings;
					getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
					SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_req  )  );
					//
#if  0
					level  =  CONST_policyAvLevel_sd;
					idc  =  IDC_STATIC_sdSettings;
					getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
					SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_req  )  );
#endif
					level  =  CONST_policyAvLevel_sd3;
					idc  =  IDC_STATIC_sd3Settings;
					getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
					SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_req  )  );
					//
				}
				else  {
						pTable  =  getResTable(  0,  &pQyMc->cusRes,  gAvParams.iResId_policyAvLevelTable  );
						idc  =  IDC_COMBO_req;
						pRegVal  =  CONST_regValName_policyAvLevel_req;
						pCb  =  (  CComboBox  *  )GetDlgItem(  idc  );
						level  =  DEFAULT_policyAvLevel_req;	
						pCb->ResetContent(  );
						for  (  pItem  =  pTable;  pItem->type  !=  -1;  pItem  ++  )  pCb->AddString(  CQyString(  pItem->des  )  );
						//  if  (  pProcInfo->cfg.policy.iPolicyAvLevel_req  &&  qyGet)
						_sntprintf(  tRootKey,  mycountof(  tRootKey  ),  _T(  "%s\\%s"  ),  reg.rootKey,  qyGetDesByType(  CONST_capTypeTable,  m_var.uiCapType  )  );
						if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  tRootKey,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )
							&&  _ttol(  tBuf  )  
							&&  qyGetDesByType(  pTable,  _ttol(  tBuf  )  )	 )
						{
							level  =  (  unsigned  char  )_ttol(  tBuf  );
						}
						pCb->SelectString(  -1,  CQyString(  qyGetDesByType1(  pTable, level  )  )  );
						//
						pTable  =  getResTable(  0,  &pQyMc->cusRes,  gAvParams.iResId_policyAvLevelTable  );
						idc  =  IDC_COMBO_reply;
						pRegVal  =  CONST_regValName_policyAvLevel_reply;
						pCb  =  (  CComboBox  *  )GetDlgItem(  idc  );
						level  =  getDefaultPolicyAvLevel(  CONST_capType_av,  0,  TRUE  );
						pCb->ResetContent(  );
						for  (  pItem  =  pTable;  pItem->type  !=  -1;  pItem  ++  )  pCb->AddString(  CQyString(  pItem->des  )  );
						_sntprintf(  tRootKey,  mycountof(  tRootKey  ),  _T(  "%s\\%s"  ),  reg.rootKey,  qyGetDesByType(  CONST_capTypeTable,  CONST_capType_av  )  );
						if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  tRootKey,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )
							&&  _ttol(  tBuf  )  
							&&  qyGetDesByType(  pTable,  _ttol(  tBuf  )  )	 )
						{
							level  =  (  unsigned  char  )_ttol(  tBuf  );
						}
						pCb->SelectString(  -1,  CQyString(  qyGetDesByType1(  pTable, level  )  )  );
						//
						level  =  CONST_policyAvLevel_ld;
						idc  =  IDC_STATIC_ldSettings;						
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
						//  2012/03/16
						level  =  CONST_policyAvLevel_ld1;
						idc  =  IDC_STATIC_ld1Settings;						
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
					    //
						level  =  CONST_policyAvLevel_sd;
						idc  =  IDC_STATIC_sdSettings;
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
						level  =  CONST_policyAvLevel_sd1;
						idc  =  IDC_STATIC_sd1Settings;
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
						level  =  CONST_policyAvLevel_sd2;
						idc  =  IDC_STATIC_sd2Settings;
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
						level  =  CONST_policyAvLevel_sd3;
						idc  =  IDC_STATIC_sd3Settings;
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
						//
					    level  =  CONST_policyAvLevel_hd;
						idc  =  IDC_STATIC_hdSettings;
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
						level  =  CONST_policyAvLevel_hd1;
						idc  =  IDC_STATIC_hd1Settings;
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
						level  =  CONST_policyAvLevel_hd2;
						idc  =  IDC_STATIC_hd2Settings;
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
					    level  =  CONST_policyAvLevel_hd3;
						idc  =  IDC_STATIC_hd3Settings;
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
					    //
						level  =  CONST_policyAvLevel_fullHd;
						idc  =  IDC_STATIC_fullHdSettings;
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
						level  =  CONST_policyAvLevel_fullHd1;
						idc  =  IDC_STATIC_fullHd1Settings;
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
						level  =  CONST_policyAvLevel_fullHd2;
						idc  =  IDC_STATIC_fullHd2Settings;
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
						level  =  CONST_policyAvLevel_fullHd3;
						idc  =  IDC_STATIC_fullHd3Settings;
						getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_reply  );
						SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.oldPolicyAv.avCompressor_reply  )  );
				  }
				  break;
			case  CONST_capType_screen:
				  pTable  =  getResTable(  0,  &pQyMc->cusRes,  gAvParams.iResId_policyAvLevelTable_screen  );
				  idc  =  IDC_COMBO_req;
				  pRegVal  =  CONST_regValName_policyAvLevel_req;
				  pCb  =  (  CComboBox  *  )GetDlgItem(  idc  );
				  pCb->ResetContent(  );
				  for  (  pItem  =  pTable;  pItem->type  !=  -1;  pItem  ++  )  pCb->AddString(  CQyString(  pItem->des  )  );
				  level  =  getDefaultPolicyAvLevel(  m_var.uiCapType,  m_var.uiSubCapType,  FALSE  );	
				  _sntprintf(  tRootKey,  mycountof(  tRootKey  ),  _T(  "%s\\%s"  ),  reg.rootKey,  qyGetDesByType(  CONST_capTypeTable,  m_var.uiCapType  )  );
				  if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  tRootKey,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )
					  &&  _ttol(  tBuf  )  
					  &&  qyGetDesByType(  pTable,  _ttol(  tBuf  )  )	 )
				  {
					  level  =  (  unsigned  char  )_ttol(  tBuf  );
				  }
				  pCb->SelectString(  -1,  CQyString(  qyGetDesByType1(  pTable, level  )  )  );
				  //
				  level  =  CONST_policyAvLevel_dev_2fps;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev2fpsSettings,  getCompressorDesc(  CONST_capType_screen,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_5fps;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev5fpsSettings,  getCompressorDesc(  CONST_capType_screen,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_5fps1;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev5fpsSettings1,  getCompressorDesc(  CONST_capType_screen,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_5fps2;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev5fpsSettings2,  getCompressorDesc(  CONST_capType_screen,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_5fps3;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev5fpsSettings3,  getCompressorDesc(  CONST_capType_screen,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_5fps4;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev5fpsSettings4,  getCompressorDesc(  CONST_capType_screen,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_5fps5;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev5fpsSettings5,  getCompressorDesc(  CONST_capType_screen,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  break;
			case  CONST_capType_mediaFile:
				  pTable  =  getResTable(  0,  &pQyMc->cusRes,  gAvParams.iResId_policyAvLevelTable_mediaFile  );
				  idc  =  IDC_COMBO_req;
				  pRegVal  =  CONST_regValName_policyAvLevel_req;
				  pCb  =  (  CComboBox  *  )GetDlgItem(  idc  );
				  pCb->ResetContent(  );
				  for  (  pItem  =  pTable;  pItem->type  !=  -1;  pItem  ++  )  pCb->AddString(  CQyString(  pItem->des  )  );
				  level  =  getDefaultPolicyAvLevel(  m_var.uiCapType,  m_var.uiSubCapType,  FALSE  );	//  DEFAULT_policyAvLevel_req_mediaFile;	
				  _sntprintf(  tRootKey,  mycountof(  tRootKey  ),  _T(  "%s\\%s"  ),  reg.rootKey,  qyGetDesByType(  CONST_capTypeTable,  m_var.uiCapType  )  );
				  if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  tRootKey,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )
					  &&  _ttol(  tBuf  )  
					  &&  qyGetDesByType(  pTable,  _ttol(  tBuf  )  )	 )
				  {
					  level  =  (  unsigned  char  )_ttol(  tBuf  );
				  }

				  pCb->SelectString(  -1,  CQyString(  qyGetDesByType1(  pTable, level  )  )  );
				  //
				  level  =  CONST_policyAvLevel_dev_2fps;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev2fpsSettings,  getCompressorDesc(  CONST_capType_mediaFile,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_5fps;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev5fpsSettings,  getCompressorDesc(  CONST_capType_mediaFile,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_5fps1;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev5fpsSettings1,  getCompressorDesc(  CONST_capType_mediaFile,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_5fps2;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev5fpsSettings2,  getCompressorDesc(  CONST_capType_mediaFile,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_5fps3;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev5fpsSettings3,  getCompressorDesc(  CONST_capType_mediaFile,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_10fps;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev10fpsSettings,  getCompressorDesc(  CONST_capType_mediaFile,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_sd24fps;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDevSd24fpsSettings,  getCompressorDesc(  CONST_capType_mediaFile,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_sd25fps;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDevSd25fpsSettings,  getCompressorDesc(  CONST_capType_mediaFile,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_sd30fps;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDevSd30fpsSettings,  getCompressorDesc(  CONST_capType_mediaFile,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  //  2012/11/08
				  level  =  CONST_policyAvLevel_dev_24fps;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev24fpsSettings,  getCompressorDesc(  CONST_capType_mediaFile,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_25fps;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev25fpsSettings,  getCompressorDesc(  CONST_capType_mediaFile,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_30fps;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev30fpsSettings,  getCompressorDesc(  CONST_capType_mediaFile,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  break;
			case  CONST_capType_mediaDevice:
				  pTable  =  getResTable(  0,  &pQyMc->cusRes,  gAvParams.iResId_policyAvLevelTable_mediaDevice  );
				  idc  =  IDC_COMBO_req;
				  pRegVal  =  CONST_regValName_policyAvLevel_req;
				  pCb  =  (  CComboBox  *  )GetDlgItem(  idc  );
				  pCb->ResetContent(  );
				  for  (  pItem  =  pTable;  pItem->type  !=  -1;  pItem  ++  )  pCb->AddString(  CQyString(  pItem->des  )  );
				  level  =  getDefaultPolicyAvLevel(  m_var.uiCapType,  m_var.uiSubCapType,  FALSE  );	
				  _sntprintf(  tRootKey,  mycountof(  tRootKey  ),  _T(  "%s\\%s"  ),  reg.rootKey,  qyGetDesByType(  CONST_capTypeTable,  m_var.uiCapType  )  );
				  if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  tRootKey,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )
					  &&  _ttol(  tBuf  )  
					  &&  qyGetDesByType(  pTable,  _ttol(  tBuf  )  )	 )
				  {
					  level  =  (  unsigned  char  )_ttol(  tBuf  );
				  }
				  pCb->SelectString(  -1,  CQyString(  qyGetDesByType1(  pTable, level  )  )  );
				  //
				  level  =  CONST_policyAvLevel_dev_2fps;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev2fpsSettings,  getCompressorDesc(  CONST_capType_mediaDevice,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_5fps1;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev5fpsSettings1,  getCompressorDesc(  CONST_capType_mediaFile,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_5fps2;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev5fpsSettings2,  getCompressorDesc(  CONST_capType_mediaFile,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_5fps3;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev5fpsSettings3,  getCompressorDesc(  CONST_capType_mediaFile,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_sd24fps;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDevSd24fpsSettings,  getCompressorDesc(  CONST_capType_mediaFile,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_sd25fps;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDevSd25fpsSettings,  getCompressorDesc(  CONST_capType_mediaFile,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_sd30fps;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDevSd30fpsSettings,  getCompressorDesc(  CONST_capType_mediaFile,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_24fps;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev24fpsSettings,  getCompressorDesc(  CONST_capType_mediaDevice,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_25fps;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev25fpsSettings,  getCompressorDesc(  CONST_capType_mediaDevice,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  level  =  CONST_policyAvLevel_dev_30fps;
				  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &m_var.oldPolicyAv.avCompressor_req  );
				  SetDlgItemText(  IDC_STATIC_setDev30fpsSettings,  getCompressorDesc(  CONST_capType_mediaDevice,  &m_var.oldPolicyAv.avCompressor_req  )  );
				  break;
			default:
					break;
	}

	return  TRUE;
}


void CDlgPolicyAv::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgPolicyAv, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgPolicyAv::OnBnClickedOk)
#if  0
	ON_BN_CLICKED(IDC_BUTTON_avCompressor, &CDlgPolicyAv::OnBnClickedButtonavcompressor)
	ON_BN_CLICKED(IDC_BUTTON_screenCompressor, &CDlgPolicyAv::OnBnClickedButtonscreencompressor)
	ON_BN_CLICKED(IDC_BUTTON_mediaFileCompressor, &CDlgPolicyAv::OnBnClickedButtonmediafilecompressor)
	ON_BN_CLICKED(IDC_BUTTON_mediaDeviceCompressor, &CDlgPolicyAv::OnBnClickedButtonmediadevicecompressor)
	ON_BN_CLICKED(IDC_BUTTON_webcamCompressor, &CDlgPolicyAv::OnBnClickedButtonwebcamcompressor)
#endif
	ON_BN_CLICKED(IDC_BUTTON_setLdSettings, &CDlgPolicyAv::OnBnClickedButtonsetldsettings)
	ON_BN_CLICKED(IDC_BUTTON_setLd1Settings, &CDlgPolicyAv::OnBnClickedButtonsetld1settings)
	ON_BN_CLICKED(IDC_BUTTON_setSdSettings, &CDlgPolicyAv::OnBnClickedButtonsetsdsettings)
	ON_BN_CLICKED(IDC_BUTTON_setSd1Settings, &CDlgPolicyAv::OnBnClickedButtonsetsd1settings)
	ON_BN_CLICKED(IDC_BUTTON_setSd2Settings, &CDlgPolicyAv::OnBnClickedButtonsetsd2settings)
	ON_BN_CLICKED(IDC_BUTTON_setSd3Settings, &CDlgPolicyAv::OnBnClickedButtonsetsd3settings)
	ON_BN_CLICKED(IDC_BUTTON_setHdSettings, &CDlgPolicyAv::OnBnClickedButtonsethdsettings)
	ON_BN_CLICKED(IDC_BUTTON_setHd1Settings, &CDlgPolicyAv::OnBnClickedButtonsethd1settings)
	ON_BN_CLICKED(IDC_BUTTON_setHd2Settings, &CDlgPolicyAv::OnBnClickedButtonsethd2settings)
	ON_BN_CLICKED(IDC_BUTTON_setHd3Settings, &CDlgPolicyAv::OnBnClickedButtonsethd3settings)
	ON_BN_CLICKED(IDC_BUTTON_setFullHdSettings, &CDlgPolicyAv::OnBnClickedButtonsetfullhdsettings)
	ON_BN_CLICKED(IDC_BUTTON_setFullHd1Settings, &CDlgPolicyAv::OnBnClickedButtonsetfullhd1settings)
	ON_BN_CLICKED(IDC_BUTTON_setFullHd2Settings, &CDlgPolicyAv::OnBnClickedButtonsetfullhd2settings)
	ON_BN_CLICKED(IDC_BUTTON_setFullHd3Settings, &CDlgPolicyAv::OnBnClickedButtonsetfullhd3settings)
	ON_BN_CLICKED(IDC_BUTTON_setDev2fpsSettings, &CDlgPolicyAv::OnBnClickedButtonsetdev2fpssettings)
	ON_BN_CLICKED(IDC_BUTTON_setDev5fpsSettings, &CDlgPolicyAv::OnBnClickedButtonsetdev5fpssettings)
	ON_BN_CLICKED(IDC_BUTTON_setDev24fpsSettings, &CDlgPolicyAv::OnBnClickedButtonsetdev24fpssettings)
	ON_BN_CLICKED(IDC_BUTTON_setDev25fpsSettings, &CDlgPolicyAv::OnBnClickedButtonsetdev25fpssettings)
	ON_BN_CLICKED(IDC_BUTTON_setDev30fpsSettings, &CDlgPolicyAv::OnBnClickedButtonsetdev30fpssettings)
	ON_BN_CLICKED(IDC_BUTTON_setDev5fpsSettings1, &CDlgPolicyAv::OnBnClickedButtonsetdev5fpssettings1)
	ON_BN_CLICKED(IDC_BUTTON_setDev5fpsSettings2, &CDlgPolicyAv::OnBnClickedButtonsetdev5fpssettings2)
	ON_BN_CLICKED(IDC_BUTTON_setDev5fpsSettings3, &CDlgPolicyAv::OnBnClickedButtonsetdev5fpssettings3)
	ON_BN_CLICKED(IDC_BUTTON_setDev10fpsSettings, &CDlgPolicyAv::OnBnClickedButtonsetdev10fpssettings)
	ON_BN_CLICKED(IDC_BUTTON_setDevSd24fpsSettings, &CDlgPolicyAv::OnBnClickedButtonsetdevsd24fpssettings)
	ON_BN_CLICKED(IDC_BUTTON_setDevSd25fpsSettings, &CDlgPolicyAv::OnBnClickedButtonsetdevsd25fpssettings)
	ON_BN_CLICKED(IDC_BUTTON_setDevSd30fpsSettings, &CDlgPolicyAv::OnBnClickedButtonsetdevsd30fpssettings)
	ON_BN_CLICKED(IDC_BUTTON_setDev5fpsSettings4, &CDlgPolicyAv::OnBnClickedButtonsetdev5fpssettings4)
	ON_BN_CLICKED(IDC_BUTTON_setDev5fpsSettings5, &CDlgPolicyAv::OnBnClickedButtonsetdev5fpssettings5)
END_MESSAGE_MAP()


// CDlgPolicyAv message handlers

#if  10
#define		M_tmpMoveLine(  idc_l,  idc_r  )  {																	\
				idc  =  idc_l;																					\
				GetWindowRect(  GetDlgItem(  pDlg->m_hWnd,  idc  ),  &rc  );									\
				MapWindowPoints(  NULL,  pDlg->m_hWnd,  (  LPPOINT  )&rc,  2  );								\
				iX  =  rc.left;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;						\
				MoveWindow(  GetDlgItem(  pDlg->m_hWnd,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );					\
				idc  =  idc_r;																					\
				GetWindowRect(  GetDlgItem(  pDlg->m_hWnd,  idc  ),  &rc  );									\
				MapWindowPoints(  NULL,  pDlg->m_hWnd,  (  LPPOINT  )&rc,  2  );								\
				iX  =  rc.left;  iW  =  rc.right  -  rc.left;  iH  =  rc.bottom  -  rc.top;						\
				MoveWindow(  GetDlgItem(  pDlg->m_hWnd,  idc  ),  iX,  iY,  iW,  iH,  TRUE  );					\
				iY  +=  iH_btn  +  iY_space;																	\
			}

#else

	#define		M_tmpMoveLine(  idc_l,  idc_r  )  {										\
					}

#endif



int	sizeControls(  CDlgPolicyAv  *  pDlg  )
{
	RECT	rc;
	int		idc;
	int		iY_t  =  0;
	int		iH_btn  =  0;
	int		iY_space  =  20;
	int		iX,  iY, iW,  iH;
	int		iEdge_b;
	
	idc  =  IDC_BUTTON_setLdSettings;
	GetWindowRect(  GetDlgItem(  pDlg->m_hWnd,  idc  ),  &rc  );
	MapWindowPoints(  NULL,  pDlg->m_hWnd,  (  LPPOINT  )&rc,  2  );
	iY_t  =  rc.top;
	iH_btn  =  rc.bottom  -  rc.top;

	idc  =  IDC_BUTTON_setLd1Settings;
	GetWindowRect(  GetDlgItem(  pDlg->m_hWnd,  idc  ),  &rc  );
	MapWindowPoints(  NULL,  pDlg->m_hWnd,  (  LPPOINT  )&rc,  2  );
	iY_space  =  rc.top  -  (  iY_t  +  iH_btn  );

	idc  =  IDOK;
	GetWindowRect(  GetDlgItem(  pDlg->m_hWnd,  idc  ),  &rc  );
	RECT	rcDlg;
	GetWindowRect(  pDlg->m_hWnd,  &rcDlg  );
	iEdge_b  =  rcDlg.bottom  -  rc.bottom;
	
	
	//
	iY  =  iY_t;

	switch  (  qyGetAppAvLevel_qyMc(  )  )  {
			case  CONST_qyAppAvLevel_basic:
				  switch  (  pDlg->m_var.uiCapType   )  {
			  			   case  CONST_capType_av:
							     M_tmpMoveLine(  IDC_BUTTON_setLdSettings,  IDC_STATIC_ldSettings  );
								 M_tmpMoveLine(  IDC_BUTTON_setSdSettings,  IDC_STATIC_sdSettings  );
								 M_tmpMoveLine(  IDC_BUTTON_setSd1Settings,  IDC_STATIC_sd1Settings  );
							     break;
						  case  CONST_capType_screen:
							    M_tmpMoveLine(  IDC_BUTTON_setDev2fpsSettings,  IDC_STATIC_setDev2fpsSettings  );
								break;
						  case  CONST_capType_mediaFile:
							    M_tmpMoveLine(  IDC_BUTTON_setDev2fpsSettings,  IDC_STATIC_setDev2fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev10fpsSettings,  IDC_STATIC_setDev10fpsSettings  );
							    break;
						  case  CONST_capType_mediaDevice:
							    M_tmpMoveLine(  IDC_BUTTON_setDev2fpsSettings,  IDC_STATIC_setDev2fpsSettings  );
							    break;
						   default:
								  break;
				  }				  
				  break;
			case  CONST_qyAppAvLevel_standard:
				  switch  (  pDlg->m_var.uiCapType  )  {
						  case  CONST_capType_av:{
							    if  (  pDlg->m_var.uiSubCapType  ==  CONST_subCapType_webcam  )  {
									M_tmpMoveLine(  IDC_BUTTON_setLdSettings,  IDC_STATIC_ldSettings  );
									M_tmpMoveLine(  IDC_BUTTON_setSd3Settings,  IDC_STATIC_sd3Settings  );
								}
								else  {
									M_tmpMoveLine(  IDC_BUTTON_setLdSettings,  IDC_STATIC_ldSettings  );
									M_tmpMoveLine(  IDC_BUTTON_setSdSettings,  IDC_STATIC_sdSettings  );
									M_tmpMoveLine(  IDC_BUTTON_setSd1Settings,  IDC_STATIC_sd1Settings  );
									M_tmpMoveLine(  IDC_BUTTON_setSd2Settings,  IDC_STATIC_sd2Settings  );
									M_tmpMoveLine(  IDC_BUTTON_setSd3Settings,  IDC_STATIC_sd3Settings  );
									M_tmpMoveLine(  IDC_BUTTON_setHdSettings,  IDC_STATIC_hdSettings  );
								}
								}
							    break;
						  case  CONST_capType_screen:
							    M_tmpMoveLine(  IDC_BUTTON_setDev2fpsSettings,  IDC_STATIC_setDev2fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings,  IDC_STATIC_setDev5fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings1,  IDC_STATIC_setDev5fpsSettings1  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings2,  IDC_STATIC_setDev5fpsSettings2  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings3,  IDC_STATIC_setDev5fpsSettings3  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings4,  IDC_STATIC_setDev5fpsSettings4  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings5,  IDC_STATIC_setDev5fpsSettings5  );
								break;
						  case  CONST_capType_mediaFile:
							    M_tmpMoveLine(  IDC_BUTTON_setDev2fpsSettings,  IDC_STATIC_setDev2fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings1,  IDC_STATIC_setDev5fpsSettings1  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings2,  IDC_STATIC_setDev5fpsSettings2  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings3,  IDC_STATIC_setDev5fpsSettings3  );
							    M_tmpMoveLine(  IDC_BUTTON_setDevSd24fpsSettings,  IDC_STATIC_setDevSd24fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDevSd25fpsSettings,  IDC_STATIC_setDevSd25fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDevSd30fpsSettings,  IDC_STATIC_setDevSd30fpsSettings  );
							    break;
						  case  CONST_capType_mediaDevice:
							    M_tmpMoveLine(  IDC_BUTTON_setDev2fpsSettings,  IDC_STATIC_setDev2fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings1,  IDC_STATIC_setDev5fpsSettings1  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings2,  IDC_STATIC_setDev5fpsSettings2  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings3,  IDC_STATIC_setDev5fpsSettings3  );
							    M_tmpMoveLine(  IDC_BUTTON_setDevSd24fpsSettings,  IDC_STATIC_setDevSd24fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDevSd25fpsSettings,  IDC_STATIC_setDevSd25fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDevSd30fpsSettings,  IDC_STATIC_setDevSd30fpsSettings  );
							    break;
						  default:
							     break;
				  }
				  break;
			case  CONST_qyAppAvLevel_high:
				  switch  (  pDlg->m_var.uiCapType  )  {
						  case  CONST_capType_av:{
							    if  (  pDlg->m_var.uiSubCapType  ==  CONST_subCapType_webcam  )  {
									M_tmpMoveLine(  IDC_BUTTON_setLdSettings,  IDC_STATIC_ldSettings  );
									M_tmpMoveLine(  IDC_BUTTON_setSd3Settings,  IDC_STATIC_sd3Settings  );
								}
								else  {
								    M_tmpMoveLine(  IDC_BUTTON_setLdSettings,  IDC_STATIC_ldSettings  );
								    M_tmpMoveLine(  IDC_BUTTON_setSdSettings,  IDC_STATIC_sdSettings  );
									M_tmpMoveLine(  IDC_BUTTON_setSd1Settings,  IDC_STATIC_sd1Settings  );
								    M_tmpMoveLine(  IDC_BUTTON_setSd2Settings,  IDC_STATIC_sd2Settings  );
								    M_tmpMoveLine(  IDC_BUTTON_setSd3Settings,  IDC_STATIC_sd3Settings  );
								    M_tmpMoveLine(  IDC_BUTTON_setHdSettings,  IDC_STATIC_hdSettings  );
									M_tmpMoveLine(  IDC_BUTTON_setHd1Settings,  IDC_STATIC_hd1Settings  );
									M_tmpMoveLine(  IDC_BUTTON_setHd2Settings,  IDC_STATIC_hd2Settings  );
									M_tmpMoveLine(  IDC_BUTTON_setHd3Settings,  IDC_STATIC_hd3Settings  );
									M_tmpMoveLine(  IDC_BUTTON_setFullHdSettings,  IDC_STATIC_fullHdSettings  );
									M_tmpMoveLine(  IDC_BUTTON_setFullHd1Settings,  IDC_STATIC_fullHd1Settings  );
									M_tmpMoveLine(  IDC_BUTTON_setFullHd2Settings,  IDC_STATIC_fullHd2Settings  );
									M_tmpMoveLine(  IDC_BUTTON_setFullHd3Settings,  IDC_STATIC_fullHd3Settings  );
								}
								}
							    break;
						  case  CONST_capType_screen:
							    M_tmpMoveLine(  IDC_BUTTON_setDev2fpsSettings,  IDC_STATIC_setDev2fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings,  IDC_STATIC_setDev5fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings1,  IDC_STATIC_setDev5fpsSettings1  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings2,  IDC_STATIC_setDev5fpsSettings2  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings3,  IDC_STATIC_setDev5fpsSettings3  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings4,  IDC_STATIC_setDev5fpsSettings4  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings5,  IDC_STATIC_setDev5fpsSettings5  );
								break;
						  case  CONST_capType_mediaFile:
							    M_tmpMoveLine(  IDC_BUTTON_setDev2fpsSettings,  IDC_STATIC_setDev2fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings1,  IDC_STATIC_setDev5fpsSettings1  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings2,  IDC_STATIC_setDev5fpsSettings2  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings3,  IDC_STATIC_setDev5fpsSettings3  );
							    M_tmpMoveLine(  IDC_BUTTON_setDevSd24fpsSettings,  IDC_STATIC_setDevSd24fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDevSd25fpsSettings,  IDC_STATIC_setDevSd25fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDevSd30fpsSettings,  IDC_STATIC_setDevSd30fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev24fpsSettings,  IDC_STATIC_setDev24fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev25fpsSettings,  IDC_STATIC_setDev25fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev30fpsSettings,  IDC_STATIC_setDev30fpsSettings  );
							    break;
						  case  CONST_capType_mediaDevice:
							    M_tmpMoveLine(  IDC_BUTTON_setDev2fpsSettings,  IDC_STATIC_setDev2fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings1,  IDC_STATIC_setDev5fpsSettings1  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings2,  IDC_STATIC_setDev5fpsSettings2  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev5fpsSettings3,  IDC_STATIC_setDev5fpsSettings3  );
							    M_tmpMoveLine(  IDC_BUTTON_setDevSd24fpsSettings,  IDC_STATIC_setDevSd24fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDevSd25fpsSettings,  IDC_STATIC_setDevSd25fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDevSd30fpsSettings,  IDC_STATIC_setDevSd30fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev24fpsSettings,  IDC_STATIC_setDev24fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev25fpsSettings,  IDC_STATIC_setDev25fpsSettings  );
							    M_tmpMoveLine(  IDC_BUTTON_setDev30fpsSettings,  IDC_STATIC_setDev30fpsSettings  );
							    break;
						  default:
							     break;
				  }
				  break;
			default:
					break;
	}

	iY  =  iY_t  +  13  *  (  iH_btn  +  iY_space  );
	iY  +=  4  *  iY_space;
	M_tmpMoveLine(  IDOK,  IDCANCEL  );


	GetWindowRect(  pDlg->m_hWnd,  &rc  );
	//
	RECT	rcClient;
	GetClientRect(  pDlg->m_hWnd,  &rcClient  );
	int  iH_notClient  =  rc.bottom  -  rc.top  -  (  rcClient.bottom  -  rcClient.top  );
	//
	MoveWindow(  pDlg->m_hWnd,  rc.left,  rc.top,  rc.right  -  rc.left,  iH_notClient  +  iY  +  iEdge_b,  TRUE  );
	
	return  0;
}

BOOL CDlgPolicyAv::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	int		iErr	=	-1;
	QY_MC		*	pQyMc	= QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  m_hWnd,  IDD_policyAv  );

	int	iAppAvLevel  =  qyGetAppAvLevel_qyMc(  );
	switch  (  iAppAvLevel  )  {
			case  CONST_qyAppAvLevel_basic:
				  //
				  GetDlgItem(  IDC_BUTTON_setLd1Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_ld1Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_BUTTON_setSd2Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_sd2Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_BUTTON_setSd3Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_sd3Settings  )->ShowWindow(  SW_HIDE  );
				  //
				  GetDlgItem(  IDC_BUTTON_setHdSettings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_STATIC_hdSettings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_BUTTON_setHd1Settings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_STATIC_hd1Settings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_BUTTON_setHd2Settings  )->ShowWindow(  SW_HIDE  );	//  2012/01/28
				  GetDlgItem(  IDC_STATIC_hd2Settings  )->ShowWindow(  SW_HIDE  );	//  2012/01/28
				  GetDlgItem(  IDC_BUTTON_setHd3Settings  )->ShowWindow(  SW_HIDE  );	//  2012/01/28
				  GetDlgItem(  IDC_STATIC_hd3Settings  )->ShowWindow(  SW_HIDE  );	//  2012/01/28
				  GetDlgItem(  IDC_BUTTON_setFullHdSettings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_STATIC_fullHdSettings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_BUTTON_setFullHd1Settings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_STATIC_fullHd1Settings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_BUTTON_setFullHd2Settings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_STATIC_fullHd2Settings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_BUTTON_setFullHd3Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_fullHd3Settings  )->ShowWindow(  SW_HIDE  );
/*				  //  2012/03/04
				  GetDlgItem(  IDC_BUTTON_setDev5fpsSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_setDev5fpsSettings  )->ShowWindow(  SW_HIDE  );
*/				  //  2012/10/29
				  GetDlgItem(  IDC_BUTTON_setDev5fpsSettings1  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_setDev5fpsSettings1  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_BUTTON_setDev5fpsSettings2  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_setDev5fpsSettings2  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_BUTTON_setDev5fpsSettings3  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_setDev5fpsSettings3  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_BUTTON_setDev5fpsSettings4  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_setDev5fpsSettings4  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_BUTTON_setDev5fpsSettings5  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_setDev5fpsSettings5  )->ShowWindow(  SW_HIDE  );

				  GetDlgItem(  IDC_BUTTON_setDev24fpsSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_setDev24fpsSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_BUTTON_setDev30fpsSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_setDev30fpsSettings  )->ShowWindow(  SW_HIDE  );
				  break;
			case  CONST_qyAppAvLevel_standard:
				  //  2012/03/16
				  GetDlgItem(  IDC_BUTTON_setLd1Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_ld1Settings  )->ShowWindow(  SW_HIDE  );
				  //
				  GetDlgItem(  IDC_BUTTON_setHd1Settings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_STATIC_hd1Settings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_BUTTON_setHd2Settings  )->ShowWindow(  SW_HIDE  );	//  2012/01/28
				  GetDlgItem(  IDC_STATIC_hd2Settings  )->ShowWindow(  SW_HIDE  );	//  2012/01/28
				  GetDlgItem(  IDC_BUTTON_setHd3Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_hd3Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_BUTTON_setFullHdSettings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_STATIC_fullHdSettings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_BUTTON_setFullHd1Settings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_STATIC_fullHd1Settings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_BUTTON_setFullHd2Settings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_STATIC_fullHd2Settings  )->ShowWindow(  SW_HIDE  );	//  2009/10/27
				  GetDlgItem(  IDC_BUTTON_setFullHd3Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_fullHd3Settings  )->ShowWindow(  SW_HIDE  );
				  //  2012/03/04
				  GetDlgItem(  IDC_BUTTON_setDev24fpsSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_setDev24fpsSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_BUTTON_setDev30fpsSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_setDev30fpsSettings  )->ShowWindow(  SW_HIDE  );
				  break;
			case  CONST_qyAppAvLevel_high:
				  //  GetDlgItem(  IDC_BUTTON_setLdSettings  )->ShowWindow(  SW_HIDE  );
				  //  GetDlgItem(  IDC_STATIC_ldSettings  )->ShowWindow(  SW_HIDE  );
				  //  2012/03/16
				  GetDlgItem(  IDC_BUTTON_setLd1Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_ld1Settings  )->ShowWindow(  SW_HIDE  );
				  break;
			default:
					break;
	}

	switch  (  m_var.uiCapType  )  {
		case  CONST_capType_av:
			  GetDlgItem(  IDC_BUTTON_setDev2fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_setDev2fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setDev5fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_setDev5fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setDev24fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_setDev24fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setDev30fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_setDev30fpsSettings  )->ShowWindow(  SW_HIDE  );
			  if  (  m_var.uiSubCapType  ==  CONST_subCapType_webcam  ){
				  //
				  GetDlgItem(  IDC_STATIC_reply  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_COMBO_reply  )->ShowWindow(  SW_HIDE  );
				  //
  				  GetDlgItem(  IDC_BUTTON_setLdSettings  )->ShowWindow(  SW_SHOW  );
				  GetDlgItem(  IDC_STATIC_ldSettings  )->ShowWindow(  SW_SHOW  );
				  //  2012/03/16
				  GetDlgItem(  IDC_BUTTON_setLd1Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_ld1Settings  )->ShowWindow(  SW_HIDE  );
				  //
				  GetDlgItem(  IDC_BUTTON_setSdSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_sdSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_BUTTON_setSd1Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_sd1Settings  )->ShowWindow(  SW_HIDE  );
				  //  2012/03/16
				  GetDlgItem(  IDC_BUTTON_setSd2Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_sd2Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_BUTTON_setSd3Settings  )->ShowWindow(  (  iAppAvLevel  ==  CONST_qyAppAvLevel_basic  ) ?  SW_HIDE  :  SW_SHOW  );		//  2012/06/12
				  GetDlgItem(  IDC_STATIC_sd3Settings  )->ShowWindow(  (  iAppAvLevel  ==  CONST_qyAppAvLevel_basic  ) ?  SW_HIDE  :  SW_SHOW  );			//  2012/06/12
				  //					
				  GetDlgItem(  IDC_BUTTON_setHdSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_hdSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_BUTTON_setHd1Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_hd1Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_BUTTON_setHd2Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_hd2Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_BUTTON_setHd3Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_hd3Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_BUTTON_setFullHdSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_fullHdSettings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_BUTTON_setFullHd1Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_fullHd1Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_BUTTON_setFullHd2Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_fullHd2Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_BUTTON_setFullHd3Settings  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_fullHd3Settings  )->ShowWindow(  SW_HIDE  );
			  }
			  break;
		case  CONST_capType_screen:
			  //
			  GetDlgItem(  IDC_STATIC_reply  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_COMBO_reply  )->ShowWindow(  SW_HIDE  );
			  //
			  GetDlgItem(  IDC_BUTTON_setLdSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_ldSettings  )->ShowWindow(  SW_HIDE  );
			  //  2012/03/16
			  GetDlgItem(  IDC_BUTTON_setLd1Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_ld1Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setSdSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_sdSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setSd1Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_sd1Settings  )->ShowWindow(  SW_HIDE  );
			  //  2012/03/16
			  GetDlgItem(  IDC_BUTTON_setSd2Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_sd2Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setSd3Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_sd3Settings  )->ShowWindow(  SW_HIDE  );
			  //
			  GetDlgItem(  IDC_BUTTON_setHdSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_hdSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setHd1Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_hd1Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setHd2Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_hd2Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setHd3Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_hd3Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setFullHdSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_fullHdSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setFullHd1Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_fullHd1Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setFullHd2Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_fullHd2Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setFullHd3Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_fullHd3Settings  )->ShowWindow(  SW_HIDE  );
			  //
			  GetDlgItem(  IDC_BUTTON_setDev24fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_setDev24fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setDev30fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_setDev30fpsSettings  )->ShowWindow(  SW_HIDE  );
			  break;
		case  CONST_capType_mediaFile:
			  //
			  GetDlgItem(  IDC_STATIC_reply  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_COMBO_reply  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setLdSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_ldSettings  )->ShowWindow(  SW_HIDE  );
			  //  2012/03/16
			  GetDlgItem(  IDC_BUTTON_setLd1Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_ld1Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setSdSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_sdSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setSd1Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_sd1Settings  )->ShowWindow(  SW_HIDE  );
			  //  2012/03/16
			  GetDlgItem(  IDC_BUTTON_setSd2Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_sd2Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setSd3Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_sd3Settings  )->ShowWindow(  SW_HIDE  );
			  //
			  GetDlgItem(  IDC_BUTTON_setHdSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_hdSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setHd1Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_hd1Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setHd2Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_hd2Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setHd3Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_hd3Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setFullHdSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_fullHdSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setFullHd1Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_fullHd1Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setFullHd2Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_fullHd2Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setFullHd3Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_fullHd3Settings  )->ShowWindow(  SW_HIDE  );
/*			  //  2012/11/03
			  GetDlgItem(  IDC_BUTTON_setDev2fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_setDev2fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setDev5fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_setDev5fpsSettings  )->ShowWindow(  SW_HIDE  );
*/
			  GetDlgItem(  IDC_BUTTON_setDev5fpsSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_setDev5fpsSettings  )->ShowWindow(  SW_HIDE  );
			  break;
		case  CONST_capType_mediaDevice:
			  //
			  GetDlgItem(  IDC_STATIC_reply  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_COMBO_reply  )->ShowWindow(  SW_HIDE  );
			  //
			  GetDlgItem(  IDC_BUTTON_setLdSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_ldSettings  )->ShowWindow(  SW_HIDE  );
			  //  2012/03/16
			  GetDlgItem(  IDC_BUTTON_setLd1Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_ld1Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setSdSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_sdSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setSd1Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_sd1Settings  )->ShowWindow(  SW_HIDE  );
			  //  2012/03/16
			  GetDlgItem(  IDC_BUTTON_setSd2Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_sd2Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setSd3Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_sd3Settings  )->ShowWindow(  SW_HIDE  );
			  //
			  GetDlgItem(  IDC_BUTTON_setHdSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_hdSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setHd1Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_hd1Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setHd2Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_hd2Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setHd3Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_hd3Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setFullHdSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_fullHdSettings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setFullHd1Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_fullHd1Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setFullHd2Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_fullHd2Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_BUTTON_setFullHd3Settings  )->ShowWindow(  SW_HIDE  );
			  GetDlgItem(  IDC_STATIC_fullHd3Settings  )->ShowWindow(  SW_HIDE  );
			  break;
		default:
			break;
	}

	
	sizeControls(  this  );
	bShowPolicy(  );

	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		EndDialog(  -1  );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPolicyAv::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	QY_MC			*	pQyMc					=  QY_GET_GBUF(  );
	MC_VAR_isCli	*	pProcInfo				=	QY_GET_procInfo_isCli(  );
	PolicyAvParams	&	gAvParams				=	*QY_GET_PolicyAvParams(  );
	QY_REG				reg;	
	TCHAR			*	pRegVal					=	NULL;
	TCHAR				tBuf[128]				=  _T(  ""  );
	TCHAR			*   pT;
	int					idc						=	0;
	unsigned  char		ucbAsked				=	FALSE;
	TCHAR				tRootKey_av[256]		=	_T(  ""  );
	TCHAR				tRootKey_screen[256]	=	_T(  ""  );
	TCHAR				tRootKey_mediaFile[256]	=	_T(  ""  );
	TCHAR				tRootKey_webcam[256]	=	_T(  ""  );
	unsigned short		usTmp					=   0;
	TCHAR				name[128]				=	_T(  ""  );
	unsigned  char		ucCmd		=	0;
	CString				tmpCStr;

	CComboBox		*	pCb						=	NULL;
	QY_DMITEM		*	pTable		=	NULL;



	 if  (  !(  pT  =  qyGetDesByType(  CONST_capTypeTable,  m_var.uiCapType  )  )  )  return;		 
	 if  (  !pT[0]  )  return;
	 _sntprintf(  name,  mycountof(  name  ),  _T(  "%s"  ),  pT  );
	 if  (  m_var.uiSubCapType  )  {
		 if  (  !(  pT  =  qyGetDesByType(  CONST_subCapTypeTable,  m_var.uiSubCapType  )  )  )  return;
		 if  (  !pT[0]  )  return;
		 _sntprintf(  name,  mycountof(  name  ),  _T(  "%s.%s"  ),  name,  pT  );
	 }


	 reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	 lstrcpyn(  reg.rootKey,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );

	 _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\%s"  ),  reg.rootKey,  name  );


#if  0
	//  _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\level%d"  ),  reg.rootKey,  m_var.level  );
	_sntprintf(  tRootKey_av,  mycountof(  tRootKey_av  ),  _T(  "%s\\av\\level%d"  ),  reg.rootKey,  m_var.level  );
	_sntprintf(  tRootKey_screen,  mycountof(  tRootKey_screen  ),  _T(  "%s\\screen\\level%d"  ),  reg.rootKey,  m_var.level  );
	_sntprintf(  tRootKey_mediaFile,  mycountof(  tRootKey_mediaFile  ),  _T(  "%s\\mediaFile\\level%d"  ),  reg.rootKey,  m_var.level  );
	_sntprintf(  tRootKey_webcam,  mycountof(  tRootKey_webcam  ),  _T(  "%s\\webcam\\level%d"  ),  reg.rootKey,  m_var.level  );


	idc  =  IDC_EDIT_ucSeconds_perFrame;
	GetDlgItemText(  idc,  (  LPTSTR  )tBuf,  mycountof(  tBuf  )  );
	if  (  m_var.oldPolicyAv.ucSeconds_perFrame_videoConference  !=  (  unsigned  char  )_tcstol(  tBuf,  &pT,  10  )  ) {
		m_var.policyAv.ucSeconds_perFrame_videoConference  =  (  unsigned char  )_tcstol(  tBuf,  &pT,  10  );
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  CONST_regValName_ucSeconds_perFrame_videoConference,  CQyString(  _ltot(  m_var.policyAv.ucSeconds_perFrame_videoConference,  tBuf,  10  )  )  );
	}



	idc  =  IDC_EDIT_usFrames_perSecond;
	usTmp  =  GetDlgItemInt(  idc  );
	if  (  m_var.oldPolicyAv.usFrames_perSecond_videoConference  !=  usTmp
		&&  usTmp
		 &&  usTmp  <= MAX_usFps_toShareBmp  )  
	{
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		m_var.policyAv.usFrames_perSecond_videoConference  =  usTmp;
		qySetRegCfgT(  reg.hKeyRoot0,  tRootKey_av,  CONST_regValName_usFps_videoConference,  CQyString(  _ltot(  m_var.policyAv.usFrames_perSecond_videoConference,  tBuf,  10  )  )  );
	}


	idc  =  IDC_EDIT_usMaxFPS_toShareBmp;
	usTmp  =  GetDlgItemInt(  idc  );
	if  (  usTmp  &&  usTmp  <=  MAX_usFps_toShareBmp  )  m_var.policyAv.avCompressor.video.common.usMaxFps_toShareBmp  =  usTmp;
	if  (  m_var.oldPolicyAv.avCompressor.video.common.usMaxFps_toShareBmp  !=  m_var.policyAv.avCompressor.video.common.usMaxFps_toShareBmp  )
	{
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
	}

	idc  =  IDC_EDIT_usMaxFPS_capScreen;
	usTmp  =  GetDlgItemInt(  idc  );
	if  (  usTmp  &&  usTmp  <=  MAX_usFps_toShareBmp  )  m_var.policyAv.screenCompressor.video.common.usMaxFps_toShareBmp  =  usTmp;
	if  (  m_var.oldPolicyAv.screenCompressor.video.common.usMaxFps_toShareBmp  !=  m_var.policyAv.screenCompressor.video.common.usMaxFps_toShareBmp  )  
	{
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
	}

	idc  =  IDC_EDIT_usMaxFps_mediaFile;
	usTmp  =  GetDlgItemInt(  idc  );
	if  (  usTmp  &&  usTmp  <=  MAX_usFps_toShareBmp  )  m_var.policyAv.mediaFileCompressor.video.common.usMaxFps_toShareBmp  =  usTmp;
	if  (  m_var.oldPolicyAv.mediaFileCompressor.video.common.usMaxFps_toShareBmp  !=  m_var.policyAv.mediaFileCompressor.video.common.usMaxFps_toShareBmp  )  
	{
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
	}


	idc  =  IDC_EDIT_usMinFps_mediaFile;
	usTmp  =  GetDlgItemInt(  idc  );
	if  (  usTmp  &&  usTmp  <=  MAX_usFps_toShareBmp  )  m_var.policyAv.mediaFileCompressor.video.common.usMinFps_toShareBmp  =  usTmp;
	if  (  m_var.oldPolicyAv.mediaFileCompressor.video.common.usMinFps_toShareBmp  !=  m_var.policyAv.mediaFileCompressor.video.common.usMinFps_toShareBmp  )  
	{
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
	}

	//  2012/01/03
	idc  =  IDC_EDIT_usFps_mediaDevice;
	usTmp  =  GetDlgItemInt(  idc  );
	if  (  usTmp  &&  usTmp  <=  MAX_usFps_toShareBmp  )  m_var.policyAv.mediaDeviceCompressor.video.common.usMaxFps_toShareBmp  =  usTmp;
	if  (  m_var.oldPolicyAv.mediaDeviceCompressor.video.common.usMaxFps_toShareBmp  !=  m_var.policyAv.mediaDeviceCompressor.video.common.usMaxFps_toShareBmp  )  
	{
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
	}

	//  2011/08/10
	idc  =  IDC_EDIT_usMaxFps_webcam;
	usTmp  =  GetDlgItemInt(  idc  );
	if  (  usTmp  &&  usTmp  <=  MAX_usFps_toShareBmp  )  m_var.policyAv.webcamCompressor.video.common.usMaxFps_toShareBmp  =  usTmp;
	if  (  m_var.oldPolicyAv.webcamCompressor.video.common.usMaxFps_toShareBmp  !=  m_var.policyAv.webcamCompressor.video.common.usMaxFps_toShareBmp  )
	{
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
	}


	idc  =  IDC_EDIT_iWidth;
	if  (  !(  m_var.policyAv.avCompressor.video.iWidth_pic  =  GetDlgItemInt(  idc  )  )  )  {
		GetDlgItem(  idc  )->SetFocus(  );	return;
	}
	if  (  m_var.oldPolicyAv.avCompressor.video.iWidth_pic  !=  m_var.policyAv.avCompressor.video.iWidth_pic  )  {
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
	}

	idc  =  IDC_EDIT_iHeight;
	if  (  !(  m_var.policyAv.avCompressor.video.iHeight_pic  =  GetDlgItemInt(  idc  )  )  )  {
		GetDlgItem(  idc  )->SetFocus(  );	return;
	}
	if  (  m_var.oldPolicyAv.avCompressor.video.iHeight_pic  !=  m_var.policyAv.avCompressor.video.iHeight_pic  )  {
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
	}

	idc  =  IDC_EDIT_iWidth_webcam;
	if  (  !(  m_var.policyAv.webcamCompressor.video.iWidth_pic  =  GetDlgItemInt(  idc  )  )  )  {
		GetDlgItem(  idc  )->SetFocus(  );	return;
	}
	if  (  m_var.oldPolicyAv.webcamCompressor.video.iWidth_pic  !=  m_var.policyAv.webcamCompressor.video.iWidth_pic  )  {
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
	}

	idc  =  IDC_EDIT_iHeight_webcam;
	if  (  !(  m_var.policyAv.webcamCompressor.video.iHeight_pic  =  GetDlgItemInt(  idc  )  )  )  {
		GetDlgItem(  idc  )->SetFocus(  );	return;
	}
	if  (  m_var.oldPolicyAv.webcamCompressor.video.iHeight_pic  !=  m_var.policyAv.webcamCompressor.video.iHeight_pic  )  {
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
	}

	if  (  memcmp(  &m_var.oldPolicyAv.avCompressor,  &m_var.policyAv.avCompressor,  sizeof(  m_var.oldPolicyAv.avCompressor  )  )  )  {
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		saveCompressorCfg(  reg,  CONST_capType_av,  NULL,  m_var.level,  &m_var.policyAv.avCompressor  );
	}
	if  (  memcmp(  &m_var.oldPolicyAv.screenCompressor,  &m_var.policyAv.screenCompressor,  sizeof(  m_var.oldPolicyAv.screenCompressor  )  )  )  {
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		saveCompressorCfg(  reg,  CONST_capType_screen,  NULL,  m_var.level,  &m_var.policyAv.screenCompressor  );
	}
	if  (  memcmp(  &m_var.oldPolicyAv.mediaFileCompressor,  &m_var.policyAv.mediaFileCompressor,  sizeof(  m_var.oldPolicyAv.mediaFileCompressor  )  )  )  {
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		saveCompressorCfg(  reg,  CONST_capType_mediaFile,  NULL,  m_var.level,  &m_var.policyAv.mediaFileCompressor  );
	}
	//  2012/01/03
	if  (  memcmp(  &m_var.oldPolicyAv.mediaDeviceCompressor,  &m_var.policyAv.mediaDeviceCompressor,  sizeof(  m_var.oldPolicyAv.mediaDeviceCompressor  )  )  )  {
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		saveCompressorCfg(  reg,  CONST_capType_mediaDevice,  NULL,  m_var.level,  &m_var.policyAv.mediaDeviceCompressor  );
	}
	if  (  memcmp(  &m_var.oldPolicyAv.webcamCompressor,  &m_var.policyAv.webcamCompressor,  sizeof(  m_var.oldPolicyAv.webcamCompressor  )  )  )  {
		if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
		ucbAsked  =  TRUE;
		saveCompressorCfg(  reg,  CONST_capType_av,  CONST_subCapType_webcam,  m_var.level,  &m_var.policyAv.webcamCompressor  );
	}
#endif

	//  2012/02/15
	switch  (  m_var.uiCapType  )  {
		case  CONST_capType_av:  {
			if  (  m_var.uiSubCapType  ==  CONST_subCapType_webcam  )  {
			  idc			=	IDC_COMBO_req;
			  pRegVal		=	CONST_regValName_policyAvLevel_req;
			  pCb			=	(  CComboBox  *  )GetDlgItem(  idc  );
			  pTable		=	getResTable(  0,  &pQyMc->cusRes,  gAvParams.iResId_policyAvLevelTable_webcam  );
			  ucCmd			=	DEFAULT_policyAvLevel_req_webcam;
			  //		
			  pCb->GetLBText(  pCb->GetCurSel(  ),  tmpCStr  );  
			  ucCmd  =  qyGetTypeByDes(  pTable,  tmpCStr  );
			  if  (  ucCmd  !=  pProcInfo->cfg.policy.iPolicyAvLevel_webcam  )  {
				  if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0, &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
				  ucbAsked  =  TRUE;
				  qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  _ltot(  ucCmd,  tBuf,  10  )  );
			  }
			  pProcInfo->cfg.policy.iPolicyAvLevel_webcam  =  ucCmd;			  
			}
			else {
			  idc			=	IDC_COMBO_req;
			  pRegVal		=	CONST_regValName_policyAvLevel_req;
			  pCb			=	(  CComboBox  *  )GetDlgItem(  idc  );
			  pTable		=	getResTable(  0,  &pQyMc->cusRes,  gAvParams.iResId_policyAvLevelTable  );
			  ucCmd			=	DEFAULT_policyAvLevel_req;
			  //		
			  pCb->GetLBText(  pCb->GetCurSel(  ),  tmpCStr  );  
			  ucCmd  =  qyGetTypeByDes(  pTable,  tmpCStr  );
			  if  (  ucCmd  !=  pProcInfo->cfg.policy.iPolicyAvLevel_req  )  {
				  if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0, &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
				  ucbAsked  =  TRUE;
				  qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  _ltot(  ucCmd,  tBuf,  10  )  );
			  }
			  pProcInfo->cfg.policy.iPolicyAvLevel_req  =  ucCmd;
			  
			  idc			=	IDC_COMBO_reply;
			  pRegVal		=	CONST_regValName_policyAvLevel_reply;
			  pCb			=	(  CComboBox  *  )GetDlgItem(  idc  );
			  pTable		=	getResTable(  0,  &pQyMc->cusRes,  gAvParams.iResId_policyAvLevelTable  );
			  ucCmd		=	getDefaultPolicyAvLevel(  CONST_capType_av,  0,  TRUE  );
			  //		
			  pCb->GetLBText(  pCb->GetCurSel(  ),  tmpCStr  );  
			  ucCmd  =  qyGetTypeByDes(  pTable,  tmpCStr  );
			  if  (  ucCmd  !=  pProcInfo->cfg.policy.iPolicyAvLevel_reply  )  {
				  if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0, &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
				  ucbAsked  =  TRUE;
				  qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  _ltot(  ucCmd,  tBuf,  10  )  );
			  }
			  pProcInfo->cfg.policy.iPolicyAvLevel_reply  =  ucCmd;
			}
			}
			break;
		case CONST_capType_screen:{
			  idc			=	IDC_COMBO_req;
			  pRegVal		=	CONST_regValName_policyAvLevel_req;
			  pCb			=	(  CComboBox  *  )GetDlgItem(  idc  );
			  pTable		=   getResTable(  0,  &pQyMc->cusRes,  gAvParams.iResId_policyAvLevelTable_screen  );
			  ucCmd			=	DEFAULT_policyAvLevel_req_screen;
			  //		
			  pCb->GetLBText(  pCb->GetCurSel(  ),  tmpCStr  );  
			  ucCmd  =  qyGetTypeByDes(  pTable,  tmpCStr  );
			  if  (  ucCmd  !=  pProcInfo->cfg.policy.iPolicyAvLevel_screen  )  {
				  if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0, &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
				  ucbAsked  =  TRUE;
				  qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  _ltot(  ucCmd,  tBuf,  10  )  );
			  }
			  pProcInfo->cfg.policy.iPolicyAvLevel_screen  =  ucCmd;
			}
			break;
		case CONST_capType_mediaFile:{
			  idc			=	IDC_COMBO_req;
			  pRegVal		=	CONST_regValName_policyAvLevel_req;
			  pCb			=	(  CComboBox  *  )GetDlgItem(  idc  );
			  pTable		=   getResTable(  0,  &pQyMc->cusRes,  gAvParams.iResId_policyAvLevelTable_mediaFile  );
			  ucCmd			=	DEFAULT_policyAvLevel_req_mediaFile;
			  //		
			  pCb->GetLBText(  pCb->GetCurSel(  ),  tmpCStr  );  
			  ucCmd  =  qyGetTypeByDes(  pTable,  tmpCStr  );
			  if  (  ucCmd  !=  pProcInfo->cfg.policy.iPolicyAvLevel_mediaFile  )  {
				  if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0, &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
				  ucbAsked  =  TRUE;
				  qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  _ltot(  ucCmd,  tBuf,  10  )  );
			  }
			  pProcInfo->cfg.policy.iPolicyAvLevel_mediaFile  =  ucCmd;
			}
			break;
		case CONST_capType_mediaDevice:{
			  idc			=	IDC_COMBO_req;
			  pRegVal		=	CONST_regValName_policyAvLevel_req;
			  pCb			=	(  CComboBox  *  )GetDlgItem(  idc  );
			  pTable		=   getResTable(  0,  &pQyMc->cusRes,  gAvParams.iResId_policyAvLevelTable_mediaDevice  );
			  ucCmd			=	DEFAULT_policyAvLevel_req_mediaDevice;
			  //		
			  pCb->GetLBText(  pCb->GetCurSel(  ),  tmpCStr  );  
			  ucCmd  =  qyGetTypeByDes(  pTable,  tmpCStr  );
			  if  (  ucCmd  !=  pProcInfo->cfg.policy.iPolicyAvLevel_mediaDevice  )  {
				  if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0, &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
				  ucbAsked  =  TRUE;
				  qySetRegCfgT(  reg.hKeyRoot0,  reg.rootKey,  pRegVal,  _ltot(  ucCmd,  tBuf,  10  )  );
			  }
			  pProcInfo->cfg.policy.iPolicyAvLevel_mediaDevice  =  ucCmd;
			}
			break;
		default:
			break;
	}


	OnOK();
}

#if  0
void CDlgPolicyAv::OnBnClickedButtonavcompressor()
{
	// TODO: Add your control notification handler code here
	CDlgVideoCompressors  dlg;
	dlg.bSetDlgInfo(  &m_var.oldPolicyAv,  m_var.level,  CONST_capType_av,  0  );

	if  (  dlg.DoModal(  )  ==  IDOK  )  {
		if  (  memcmp(  &dlg.m_var.compressor,  &m_var.oldPolicyAv.avCompressor,  sizeof(  dlg.m_var.compressor  )  )  )  {
			memcpy(  &m_var.policyAv.avCompressor,  &dlg.m_var.compressor,  sizeof(  m_var.policyAv.avCompressor  )  );
			SetDlgItemText(  IDC_STATIC_avCompressorVal,  getCompressorDesc(  CONST_capType_av,  &m_var.policyAv.avCompressor  )  );
		}
	}
}

void CDlgPolicyAv::OnBnClickedButtonscreencompressor()
{
	// TODO: Add your control notification handler code here
	CDlgVideoCompressors  dlg;
	dlg.bSetDlgInfo(  &m_var.oldPolicyAv,  m_var.level,  CONST_capType_screen,  0  );

	if  (  dlg.DoModal(  )  ==  IDOK  )  {
		if  (  memcmp(  &dlg.m_var.compressor,  &m_var.oldPolicyAv.screenCompressor,  sizeof  (  dlg.m_var.compressor  )  )  )  {
			memcpy(  &m_var.policyAv.screenCompressor,  &dlg.m_var.compressor,  sizeof(  m_var.policyAv.screenCompressor  )  );
			SetDlgItemText(  IDC_STATIC_screenCompressorVal,  getCompressorDesc(  CONST_capType_screen,  &m_var.policyAv.screenCompressor  )  );
		}
	}

}

void CDlgPolicyAv::OnBnClickedButtonmediafilecompressor()
{
	// TODO: Add your control notification handler code here
	CDlgVideoCompressors  dlg;
	dlg.bSetDlgInfo(  &m_var.oldPolicyAv,  m_var.level,  CONST_capType_mediaFile,  0  );

	if  (  dlg.DoModal(  )  ==  IDOK  )  {
		if  (  memcmp(  &dlg.m_var.compressor,  &m_var.oldPolicyAv.mediaFileCompressor,  sizeof(  dlg.m_var.compressor  )  )  )  {
			memcpy(  &m_var.policyAv.mediaFileCompressor,  &dlg.m_var.compressor,  sizeof(  m_var.policyAv.mediaFileCompressor  )  );
			SetDlgItemText(  IDC_STATIC_mediaFileCompressorVal,  getCompressorDesc(  CONST_capType_mediaFile,  &m_var.policyAv.mediaFileCompressor  )  );
		}
	}
}

void CDlgPolicyAv::OnBnClickedButtonmediadevicecompressor()
{
	// TODO: Add your control notification handler code here
	CDlgVideoCompressors  dlg;
	dlg.bSetDlgInfo(  &m_var.oldPolicyAv,  m_var.level,  CONST_capType_mediaDevice,  0  );

	if  (  dlg.DoModal(  )  ==  IDOK  )  {
		if  (  memcmp(  &dlg.m_var.compressor,  &m_var.oldPolicyAv.mediaDeviceCompressor,  sizeof(  dlg.m_var.compressor  )  )  )  {
			memcpy(  &m_var.policyAv.mediaDeviceCompressor,  &dlg.m_var.compressor,  sizeof(  m_var.policyAv.mediaDeviceCompressor  )  );
			SetDlgItemText(  IDC_STATIC_mediaDeviceCompressorVal,  getCompressorDesc(  CONST_capType_mediaDevice,  &m_var.policyAv.mediaDeviceCompressor  )  );
		}
	}
}


void CDlgPolicyAv::OnBnClickedButtonwebcamcompressor()
{
	// TODO: Add your control notification handler code here
	CDlgVideoCompressors  dlg;
	dlg.bSetDlgInfo(  &m_var.oldPolicyAv,  m_var.level,  CONST_capType_av,  CONST_subCapType_webcam  );

	if  (  dlg.DoModal(  )  ==  IDOK  )  {
		if  (  memcmp(  &dlg.m_var.compressor,  &m_var.oldPolicyAv.webcamCompressor,  sizeof(  dlg.m_var.compressor  )  )  )  {
			memcpy(  &m_var.policyAv.webcamCompressor,  &dlg.m_var.compressor,  sizeof(  m_var.policyAv.webcamCompressor  )  );
			SetDlgItemText(  IDC_STATIC_webcamCompressorVal,  getCompressorDesc(  CONST_capType_av,  &m_var.policyAv.webcamCompressor  )  );
		}
	}

}

#endif
void CDlgPolicyAv::OnBnClickedButtonsetldsettings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_ld;
	idc  =  IDC_STATIC_ldSettings;

	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsetld1settings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;
	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_ld1;
	idc  =  IDC_STATIC_ld1Settings;

	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsetsdsettings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_sd;
	idc  =  IDC_STATIC_sdSettings;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsetsd1settings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_sd1;
	idc  =  IDC_STATIC_sd1Settings;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsetsd2settings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;
	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_sd2;
	idc  =  IDC_STATIC_sd2Settings;

	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsetsd3settings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;
	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_sd3;
	idc  =  IDC_STATIC_sd3Settings;

	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}


void CDlgPolicyAv::OnBnClickedButtonsethdsettings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_hd;
	idc  =  IDC_STATIC_hdSettings;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsethd1settings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_hd1;
	idc  =  IDC_STATIC_hd1Settings;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsethd2settings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_hd2;
	idc  =  IDC_STATIC_hd2Settings;

	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsethd3settings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_hd3;
	idc  =  IDC_STATIC_hd3Settings;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsetfullhdsettings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_fullHd;
	idc  =  IDC_STATIC_fullHdSettings;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsetfullhd1settings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_fullHd1;
	idc  =  IDC_STATIC_fullHd1Settings;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsetfullhd2settings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_fullHd2;
	idc  =  IDC_STATIC_fullHd2Settings;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsetfullhd3settings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_fullHd3;
	idc  =  IDC_STATIC_fullHd3Settings;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsetdev2fpssettings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_dev_2fps;
	idc  =  IDC_STATIC_setDev2fpsSettings;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsetdev5fpssettings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_dev_5fps;
	idc  =  IDC_STATIC_setDev5fpsSettings;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsetdev5fpssettings1()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_dev_5fps1;
	idc  =  IDC_STATIC_setDev5fpsSettings1;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsetdev5fpssettings2()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_dev_5fps2;
	idc  =  IDC_STATIC_setDev5fpsSettings2;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsetdev5fpssettings3()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_dev_5fps3;
	idc  =  IDC_STATIC_setDev5fpsSettings3;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsetdev5fpssettings4()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_dev_5fps4;
	idc  =  IDC_STATIC_setDev5fpsSettings4;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsetdev5fpssettings5()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_dev_5fps5;
	idc  =  IDC_STATIC_setDev5fpsSettings5;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsetdev10fpssettings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_dev_10fps;
	idc  =  IDC_STATIC_setDev10fpsSettings;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsetdevsd24fpssettings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_dev_sd24fps;
	idc  =  IDC_STATIC_setDevSd24fpsSettings;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsetdevsd25fpssettings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_dev_sd25fps;
	idc  =  IDC_STATIC_setDevSd25fpsSettings;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsetdevsd30fpssettings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_dev_sd30fps;
	idc  =  IDC_STATIC_setDevSd30fpsSettings;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsetdev24fpssettings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_dev_24fps;
	idc  =  IDC_STATIC_setDev24fpsSettings;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsetdev25fpssettings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_dev_25fps;
	idc  =  IDC_STATIC_setDev25fpsSettings;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}

void CDlgPolicyAv::OnBnClickedButtonsetdev30fpssettings()
{
	// TODO: Add your control notification handler code here
	//  CDlgVideoCompressors	dlg(  this  );
	AV_COMPRESSOR_CFG		compressor;

	int						level;
	int						idc;

	level  =  CONST_policyAvLevel_dev_30fps;
	idc  =  IDC_STATIC_setDev30fpsSettings;


	if  (  m_var.bReply  )  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_reply,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_reply,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_reply,  &compressor,  sizeof(  m_var.policyAv.avCompressor_reply  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_reply  )  );
			}
		}
	}
	else  {
#if  0
		dlg.bSetDlgInfo(  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level  );

		if  (  dlg.DoModal(  )  ==  IDOK  )  
#endif
		if  (  showDlgVideoCompressors(  m_hWnd,  &m_var.oldPolicyAv.avCompressor_req,  m_var.uiCapType,  m_var.uiSubCapType,  level,  &compressor  )  ==  IDOK  )
		{
			if  (  memcmp(  &compressor,  &m_var.oldPolicyAv.avCompressor_req,  sizeof(  compressor  )  )  )  {
				memcpy(  &m_var.policyAv.avCompressor_req,  &compressor,  sizeof(  m_var.policyAv.avCompressor_req  )  );
				//

				SetDlgItemText(  idc,  getCompressorDesc(  m_var.uiCapType,  &m_var.policyAv.avCompressor_req  )  );
			}
		}
	}

	return;
}
