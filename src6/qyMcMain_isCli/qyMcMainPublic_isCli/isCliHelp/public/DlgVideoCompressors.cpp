// DlgVideoCompressors.cpp : implementation file
//

#include	"stdafx.h"

#include	<tchar.h>
#include	"qyMcMainCommon.h"

#include	"myresource.h"

//  #include	"DlgPolicyIsClient.h"
#include	"DlgVideoCompressors.h"

#include	"qmcVideoCapture.h"
#include	"qyMcMainRealTimeMediaProc.h"
#include	"qyCusResTemp.h"

#include	<dmo.h>
#include	<uuids.h>

#include	"qyMcMainCommon.h"
#include	"qyDynLib.h"

#include	"qyMcMainRealTimeMediaProc.h"

#include	"qyAvRecord.h"

#include	"qyAvRecord_dx.h"

#include	"qmcDmoPublic.h"

#ifdef  __SUPPORT_CFGWMV__
	//  #include	"DlgCfgWmv.h"
#endif

#include	"myfourcc.h"

#include	"myresource.h"

#include	"qmShell_open.h"
#include	"policyAvParams.h"
#include	"isCliHelpPublic.h"
#include	"funcsForIsCliHelp.h"

 
int  getAudioCompressorCfg_default_acm(  unsigned  int  uiCapType,  AUDIO_COMPRESSOR_CFG  *  pCfg  );
int  getAudioCompressorCfg_default_dmo(  unsigned  int  uiCapType,  AUDIO_COMPRESSOR_CFG  *  pCfg  );
int  getAudioCompressorCfg_default_custom(  unsigned  int  uiCapType,  AUDIO_COMPRESSOR_CFG  *  pCfg  );
int  getAudioCompressorCfg_default_ipp(  unsigned  int  uiCapType,  AUDIO_COMPRESSOR_CFG  *  pCfg  );				//  2012/01/20

__declspec(  dllexport  )  int  showDlgVideoCompressors(  HWND  hParent,  AV_COMPRESSOR_CFG  *  pAvCompressor,  unsigned  int  uiCapType,  unsigned int uiSubCapType,  int  level,  AV_COMPRESSOR_CFG  *  pCompressor_o  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int		iRet	=	-1;
	
	CDlgVideoCompressors	dlg(  CWnd::FromHandle(  hParent  )  );

	dlg.bSetDlgInfo(  pAvCompressor,  uiCapType,  uiSubCapType,  level  );

	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;

	if  (  pCompressor_o  )  memcpy(  pCompressor_o,  &dlg.m_var.compressor,  sizeof(  dlg.m_var.compressor  )  );

	iRet  =  IDOK;
	errLabel:

	return  iRet;
}

// CDlgVideoCompressors dialog

IMPLEMENT_DYNAMIC(CDlgVideoCompressors, CDialog)

CDlgVideoCompressors::CDlgVideoCompressors(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVideoCompressors::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

CDlgVideoCompressors::~CDlgVideoCompressors()
{
}

#if  0
BOOL  CDlgVideoCompressors::bSetDlgInfo(  POLICY_av  *  pPolicy,  int  level,  unsigned  int  uiCapType,  unsigned int uiSubCapType  )
{
	//  m_var.pProcInfo  =  pProcInfo;
	m_var.level  =  level;
	m_var.pTaskAv_pc  =  pPolicy;
	m_var.uiCapType  =  uiCapType;
	m_var.uiSubCapType  =  uiSubCapType;
	return  TRUE; 
}
#endif

 BOOL  CDlgVideoCompressors::bSetDlgInfo(  AV_COMPRESSOR_CFG  *  pAvCompressor,  unsigned  int  uiCapType,  unsigned int uiSubCapType,  int  level  )
{
	//  m_var.pProcInfo  =  pProcInfo;
	m_var.pCompressor  =  pAvCompressor;
	m_var.uiCapType  =  uiCapType;
	m_var.uiSubCapType  =  uiSubCapType;
	m_var.level  =  level;
	return  TRUE; 
}



void CDlgVideoCompressors::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgVideoCompressors, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgVideoCompressors::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_audioCompressors, &CDlgVideoCompressors::OnCbnSelchangeComboaudiocompressors)
	ON_CBN_SELCHANGE(IDC_COMBO_audioCompressor, &CDlgVideoCompressors::OnCbnSelchangeComboaudiocompressor)
	ON_CBN_SELCHANGE(IDC_COMBO_audioOutputType, &CDlgVideoCompressors::OnCbnSelchangeComboaudiooutputtype)
	ON_CBN_SELCHANGE(IDC_COMBO_videoCompressors, &CDlgVideoCompressors::OnCbnSelchangeCombovideocompressors)
	ON_CBN_SELCHANGE(IDC_COMBO_videoCompressor, &CDlgVideoCompressors::OnCbnSelchangeCombovideocompressor)
	ON_CBN_SELCHANGE(IDC_COMBO_videoOutputType, &CDlgVideoCompressors::OnCbnSelchangeCombovideooutputtype)
	ON_BN_CLICKED(IDC_BUTTON_cfgWmv, &CDlgVideoCompressors::OnBnClickedButtoncfgwmv)
	ON_CBN_SELCHANGE(IDC_COMBO_videoEffect, &CDlgVideoCompressors::OnCbnSelchangeCombovideoeffect)
	ON_CBN_SELCHANGE(IDC_COMBO_avgBitrate, &CDlgVideoCompressors::OnCbnSelchangeComboavgbitrate)
END_MESSAGE_MAP()


 int  fill_uiBytesRecorded_perBlockAligns(  int  nSamplesPerSec,  CComboBox  *  pCb  )
{
	int			cnt									=	0;
	int			uiBytesRecorded_perBlockAligns;
	int			i;
	TCHAR		tBuf[256];
	CString		str;

	pCb->ResetContent(  );

	if  (  !(  nSamplesPerSec  %  100  )  )  cnt  =  100;
	else  if  (  !(  nSamplesPerSec  %  25  )  )  cnt  =  25;
	else  if  (  !(  nSamplesPerSec  %  10  )  )  cnt  =  10;
	else  if  (  !(  nSamplesPerSec  %  5  )  )  cnt  =  5;

	if  (  !cnt  )  return  -1;

	uiBytesRecorded_perBlockAligns  =  nSamplesPerSec  /  cnt;
	
	int  n  =  min(  cnt  /  2,  20  );
	for  (  i  =  1;  i  <=  n;  i  ++  )  {
		 /*
		 str  =  CString(  ""  );
		 str  +=  _ltot(  i,  tBuf,  10  );
		 str  +=  "*";
		 str  +=  _ltot(  uiBytesRecorded_perBlockAligns,  tBuf,  100  );
		 */
		 str  =  CString(  ""  )  +  _ltot(  i  *  uiBytesRecorded_perBlockAligns,  tBuf,  10  );
		 pCb->InsertString(  -1,  str  );
	}

	return  0;
}

// CDlgVideoCompressors message handlers

BOOL CDlgVideoCompressors::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	int						iErr		=	-1;
	QY_MC				*	pQyMc		=	QY_GET_GBUF(  );
	DYN_LIB_DX			*	pDynLib		=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;
	PolicyAvParams		&	gAvParams	=	*QY_GET_PolicyAvParams(  );
	//  FUNCS_for_isCliHelp	*	pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  );
	TCHAR					tBuf[128];
	QY_REG					reg;	
	TCHAR				*	pRegVal;
	TCHAR			*	pT;
	long				lVal;
	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	//  if  (  !m_var.pProcInfo  )  goto  errLabel;
	//  if  (  !m_var.pTaskAv_pc  )  goto  errLabel;

	int		idc;
	QY_DMITEM	*	pItem;
	
#if  0
	switch  (  m_var.uiCapType  )  {
			case  CONST_capType_screen:
				  m_var.pCompressor  =  &m_var.pTaskAv_pc->screenCompressor;
				  break;
			case  CONST_capType_mediaFile:
				  m_var.pCompressor  =  &m_var.pTaskAv_pc->mediaFileCompressor;
				  break;
			case  CONST_capType_mediaDevice:
				  m_var.pCompressor  =  &m_var.pTaskAv_pc->mediaDeviceCompressor;
				  break;
			default:
				   if  (  m_var.uiSubCapType  ==  CONST_subCapType_webcam  )  m_var.pCompressor  =  &m_var.pTaskAv_pc->webcamCompressor;
				   else  m_var.pCompressor  =  &m_var.pTaskAv_pc->avCompressor;
				   break;
	}
#endif
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	lstrcpyn(  reg.rootKey,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );

	if  (  getCompressorCfg(  &reg,  m_var.uiCapType,  m_var.uiSubCapType,  m_var.level,  &m_var.oldCompressor  )  )  goto  errLabel;
	m_var.pCompressor  =  &m_var.oldCompressor;

	if  (  !m_var.pCompressor  )  goto  errLabel;
	
	memcpy(  &m_var.compressor,  m_var.pCompressor,  sizeof(  m_var.compressor  )  );

	m_var.clsid_category_audio  =  DMOCATEGORY_AUDIO_ENCODER;
	m_var.bEnumCompressors_audio  =  (  m_var.clsid_category_audio  ==  DMOCATEGORY_AUDIO_ENCODER  );

	m_var.clsid_category_video  =  DMOCATEGORY_VIDEO_ENCODER;
	m_var.bEnumCompressors_video  =  (  m_var.clsid_category_video  ==  DMOCATEGORY_VIDEO_ENCODER  );

	if  (  m_var.pCompressor->audio.ucCompressors  )  {
		idc  =  IDC_COMBO_audioCompressors;
		for  (  pItem  =  gAvParams.pAudioCompressorsTable;  pItem->type  !=  -1;  pItem  ++  )  {
			 (  (  CComboBox  *  )GetDlgItem(  idc  )  )->AddString(  pItem->des  );	
		}
		(  (  CComboBox  *  )GetDlgItem(  idc  )  )->SelectString(  -1,  qyGetDesByType1(  gAvParams.pAudioCompressorsTable,  m_var.pCompressor->audio.ucCompressors  )  );
		this->OnCbnSelchangeComboaudiocompressors(  );
	}

	//  2010/03/11
	SetDlgItemInt(  IDC_EDIT_uiMinTimeInMsOfAudioDataPlaying,  m_var.pCompressor->audio.playCfg.usMinTimeInMsOfAudioDataPlaying  );
	SetDlgItemInt(  IDC_EDIT_uiAudioDataAddedToPlayEveryTime,  m_var.pCompressor->audio.playCfg.usAudioDataAddedToPlayEveryTime  );
	SetDlgItemInt(  IDC_EDIT_uiNotifyIntervalInMs_needMoreAudioData,  m_var.pCompressor->audio.playCfg.usNotifyIntervalInMs_needMoreAudioData  );
	//  2012/01/27
	SetDlgItemInt(  IDC_EDIT_uiMinTimeInMsToPlay,  m_var.pCompressor->audio.playCfg.usMinTimeInMsToPlay  );
	//  2009/06/03
	SetDlgItemInt(  IDC_EDIT_uiMaxTimeInMsToPlay,  m_var.pCompressor->audio.playCfg.usMaxTimeInMsToPlay  );
	SetDlgItemInt(  IDC_EDIT_uiMaxTimeInMsToBeRemoved,  m_var.pCompressor->audio.playCfg.usMaxTimeInMsToBeRemoved  );

	//
	if  (  m_var.pCompressor->video.common.ucCompressors  )  {
		idc  =  IDC_COMBO_videoCompressors;
		for  (  pItem  =  gAvParams.pVideoCompressorsTable;  pItem->type  !=  -1;  pItem  ++  )  {
			 (  (  CComboBox  *  )GetDlgItem(  idc  )  )->AddString(  pItem->des  );
		}
		(  (  CComboBox  *  )GetDlgItem(  idc  )  )->SelectString(  -1,  qyGetDesByType1(  gAvParams.pVideoCompressorsTable,  m_var.pCompressor->video.common.ucCompressors  )  );
		this->OnCbnSelchangeCombovideocompressors(  );
		//
		idc  =  IDC_COMBO_videoEffect;
		for  (  pItem  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_iTargetUsageTable  );  pItem->type  !=  -1;  pItem  ++  )  {
			 (  (  CComboBox  *  )GetDlgItem(  idc  )  )->AddString(  pItem->des  );
		}
		int  iTargetUsage  =  m_var.pCompressor->video.common.iTargetUsage;
		if  (  !iTargetUsage  )  iTargetUsage  =  DEFAULT_iTargetUsage;
		(  (  CComboBox  *  )GetDlgItem(  idc  )  )->SelectString(  -1,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_iTargetUsageTable  ),  iTargetUsage  )  );
		this->OnCbnSelchangeCombovideoeffect(  );
		if  (  m_var.pCompressor->video.common.ucCompressors  !=  CONST_videoCompressors_mediaSdk  )  {
		  GetDlgItem(  IDC_STATIC_videoEffect  )->ShowWindow(  SW_HIDE  );
		  GetDlgItem(  IDC_COMBO_videoEffect  )->ShowWindow(  SW_HIDE  );
		}

		idc  =  IDC_COMBO_avgBitrate;
		for  (  pItem  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_iAvgBitrateTable  );  pItem->type  !=  -1;  pItem  ++  )  {
			(  (  CComboBox  *  )GetDlgItem(  idc  )  )->AddString(  pItem->des  );
		}
		int  iAvgBitrate  =  m_var.pCompressor->video.common.iAvgBitrate;
		if  (  !iAvgBitrate  )  iAvgBitrate  =  DEFAULT_iAvgBitrate;
		(  (  CComboBox  *  )GetDlgItem(  idc  )  )->SelectString(  -1,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_iAvgBitrateTable  ),  iAvgBitrate  )  );
		this->OnCbnSelchangeComboavgbitrate(  );
		if  (  m_var.pCompressor->video.common.ucCompressors  !=  CONST_videoCompressors_cuda  )  {
			GetDlgItem(  IDC_STATIC_avgBitrate  )->ShowWindow(  SW_HIDE  );
			GetDlgItem(  IDC_COMBO_avgBitrate  )->ShowWindow(  SW_HIDE  );
		}
	}
#if 0
	//  2012/02/08
	if  (  m_var.pCompressor->video.common.ucCompressors  ==  CONST_videoCompressors_mediaSdk  )  {
		idc  =  IDC_COMBO_videoEffect;
		for  (  pItem  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_iTargetUsageTable  );  pItem->type  !=  -1;  pItem  ++  )  {
			 (  (  CComboBox  *  )GetDlgItem(  idc  )  )->AddString(  pItem->des  );
		}
		int  iTargetUsage  =  m_var.pCompressor->video.common.iTargetUsage;
		if  (  !iTargetUsage  )  iTargetUsage  =  DEFAULT_iTargetUsage;
		(  (  CComboBox  *  )GetDlgItem(  idc  )  )->SelectString(  -1,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_iTargetUsageTable  ),  iTargetUsage  )  );
		this->OnCbnSelchangeCombovideoeffect(  );
	}
	else  {
		  GetDlgItem(  IDC_STATIC_videoEffect  )->ShowWindow(  SW_HIDE  );
		  GetDlgItem(  IDC_COMBO_videoEffect  )->ShowWindow(  SW_HIDE  );
	}
#endif
	//
	switch  (  m_var.uiCapType  )  {				//  audio
			case  CONST_capType_screen:
				  GetDlgItem(  IDC_COMBO_uiBytesRecorded_perBlockAlign  )->EnableWindow(  FALSE  );
				  GetDlgItem(  IDC_COMBO_audioCompressors  )->EnableWindow(  FALSE  );				  
				  GetDlgItem(  IDC_COMBO_audioCompressor  )->EnableWindow(  FALSE  );
				  GetDlgItem(  IDC_COMBO_audioOutputType  )->EnableWindow(  FALSE  );	
				  //
				  GetDlgItem(  IDC_EDIT_uiMinTimeInMsOfAudioDataPlaying  )->EnableWindow(  FALSE  );
				  GetDlgItem(  IDC_EDIT_uiAudioDataAddedToPlayEveryTime  )->EnableWindow(  FALSE  );
				  GetDlgItem(  IDC_EDIT_uiNotifyIntervalInMs_needMoreAudioData  )->EnableWindow(  FALSE  );
				  GetDlgItem(  IDC_EDIT_uiMinTimeInMsToPlay  )->EnableWindow(  FALSE  );				  //  2012/01/27
				  GetDlgItem(  IDC_EDIT_uiMaxTimeInMsToPlay  )->EnableWindow(  FALSE  );				  //  2009/06/03
				  GetDlgItem(  IDC_EDIT_uiMaxTimeInMsToBeRemoved  )->EnableWindow(  FALSE  );
				  //
				  break;
			case  CONST_capType_av:
			default:
				    SetDlgItemText(  IDC_STATIC_defaultFmtVal,  getWaveFormatExStr(  m_var.uiCapType,  &m_var.compressor.audio.wf_decompress_default,  tBuf,  mycountof(  tBuf  )  )  );
					
					fill_uiBytesRecorded_perBlockAligns(  m_var.compressor.audio.wf_decompress_default.nSamplesPerSec,  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_uiBytesRecorded_perBlockAlign  )  );
					(  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_uiBytesRecorded_perBlockAlign  )  )->SelectString(  -1,  _ltot(  m_var.compressor.audio.uiBytesRecorded_perBlockAlign,  tBuf,  10  )  );
					break;
	}

	switch  (  m_var.uiCapType  )  {			//  video
		case  CONST_capType_mediaFile:
				  GetDlgItem(  IDC_STATIC_ucSeconds_perFrame  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_EDIT_ucSeconds_perFrame  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_usMinFps_toShareBmp  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_EDIT_usMinFps_toShareBmp  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_iWidth  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_EDIT_iWidth  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_iHeight  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_EDIT_iHeight  )->ShowWindow(  SW_HIDE  );
				  //
				  SetDlgItemInt(  IDC_EDIT_usMinFps_toShareBmp,  m_var.compressor.video.common.usMinFps_toShareBmp  );
				  break;
		case  CONST_capType_screen:
		case  CONST_capType_mediaDevice:
				  GetDlgItem(  IDC_STATIC_ucSeconds_perFrame  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_EDIT_ucSeconds_perFrame  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_usMinFps_toShareBmp  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_EDIT_usMinFps_toShareBmp  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_iWidth  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_EDIT_iWidth  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_STATIC_iHeight  )->ShowWindow(  SW_HIDE  );
				  GetDlgItem(  IDC_EDIT_iHeight  )->ShowWindow(  SW_HIDE  );
				  break;
		case  CONST_capType_av:
			GetDlgItem(  IDC_STATIC_usMinFps_toShareBmp  )->ShowWindow(  SW_HIDE  );
			GetDlgItem(  IDC_EDIT_usMinFps_toShareBmp  )->ShowWindow(  SW_HIDE  );
			#if  0
				if  (  m_var.uiSubCapType  ==  CONST_subCapType_webcam  )  {
					GetDlgItem(  IDC_STATIC_ucSeconds_perFrame  )->ShowWindow(  SW_HIDE  );
				  	GetDlgItem(  IDC_EDIT_ucSeconds_perFrame  )->ShowWindow(  SW_HIDE  );
				}
			else  
			{
				  //	
				pRegVal  =  CONST_regValName_ucSeconds_perFrame_videoConference;
				if  (  qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ) + _T(  "\\av"  ),  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
				tTrim(  tBuf  );
				if  (  !tBuf[0]  )  m_var.compressor.ucSeconds_perFrame_videoConference  =  gAvParams.DEFAULT_ucSpf_toShareBmp_videoConference;
				else  m_var.compressor.ucSeconds_perFrame_videoConference  =  (  unsigned  char  )_tcstol(  tBuf,  &pT,  10  );

				pRegVal  =  CONST_regValName_usFps_videoConference;
				if  (  qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ) + _T(  "\\av"  ),  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
				lVal  =  _tcstol(  tBuf,  &pT,  10  );
				if  (  lVal  <=  0  ||  lVal  >  MAX_usFps_toShareBmp  )  lVal  =  m_var.compressor.usFrames_perSecond_videoConference;
				if  (  m_var.compressor.usFrames_perSecond_videoConference  !=  lVal  )  m_var.compressor.usFrames_perSecond_videoConference  =  (  unsigned  short  )lVal;

				SetDlgItemInt(  IDC_EDIT_ucSeconds_perFrame,  m_var.compressor.ucSeconds_perFrame_videoConference  );
				//  GetDlgItem(  IDC_EDIT_ucSeconds_perFrame  )->EnableWindow(  FALSE  );
			}
			#endif


			//
			SetDlgItemInt(  IDC_EDIT_iWidth,  m_var.compressor.video.iWidth_pic  );
			SetDlgItemInt(  IDC_EDIT_iHeight,  m_var.compressor.video.iHeight_pic  );
			//  2012/07/01
			GetDlgItem(  IDC_STATIC_ucSeconds_perFrame  )->ShowWindow(  SW_SHOW  );
		  	GetDlgItem(  IDC_EDIT_ucSeconds_perFrame  )->ShowWindow(  SW_SHOW  );
			break;
		default:
			break;
	}

	SetDlgItemInt(  IDC_EDIT_usMaxFPS_toShareBmp,  m_var.compressor.video.common.usMaxFps_toShareBmp  );
	SetDlgItemInt(  IDC_EDIT_ucSeconds_perFrame,  m_var.compressor.video.common.ucSeconds_perFrame  );

	GetDlgItem(  IDC_BUTTON_cfgWmv  )->ShowWindow(  SW_HIDE  );

	m_var.bInited  =  TRUE;

	iErr  =  0;

errLabel:
	if  (  iErr  )  {
		traceLogA(  "DDlgVideoCompressors:;OnInitDialog(  ) failed."  );
		SendMessage(  WM_CLOSE,  0,  0  );
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVideoCompressors::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	PolicyAvParams	&	gAvParams	=	*QY_GET_PolicyAvParams(  );
	FUNCS_for_isCliHelp	*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  );
	int					idc;
	CString				str;
	TCHAR				tBuf[256]	=	_T(  ""  );
	TCHAR			*	pT;
	unsigned  char		ucbAsked				=	FALSE;
	QY_REG				reg;	
	BOOL				bNoAudio				=	FALSE;

	//
	if  (  m_var.uiCapType  ==  CONST_capType_screen  )  bNoAudio  =  TRUE;

	//
	reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	lstrcpyn(  reg.rootKey,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  reg.rootKey  )  );
	
	//  memset(  &m_var.compressor,  0,  sizeof(  m_var.compressor  )  );

	
	if  (  !bNoAudio  )  {

		GetDlgItemText(  IDC_COMBO_audioCompressors,  str  );
		m_var.compressor.audio.ucCompressors  =  qyGetTypeByDes(  gAvParams.pAudioCompressorsTable,  str  );


		GetDlgItemText(  IDC_COMBO_audioCompressor,  m_var.compressor.audio.compressorName,  mycountof(  m_var.compressor.audio.compressorName  )  );
		if  (  !m_var.compressor.audio.compressorName[0]  )  {
			myMessageBox(  m_hWnd,  _T(  "Compressor error"  ),  _T(  ""  ),  MB_OK  );
			GetDlgItem(  IDC_COMBO_audioCompressor  )->SetFocus(  );
			return;
		}


		if  (  m_var.uiCapType  ==  CONST_capType_av  )  {
			GetDlgItemText(  IDC_STATIC_defaultFmtVal,  tBuf,  mycountof(  tBuf  )  );
			getWaveFormatExByStr(  tBuf,  &m_var.compressor.audio.wf_decompress_default  );
		}

		GetDlgItemText(  IDC_COMBO_audioOutputType,  tBuf,  mycountof(  tBuf  )  );
		if  (  getWaveFormatExByStr(  tBuf,  &m_var.compressor.audio.wf_compress  )  )  {
			myMessageBox(  m_hWnd,  _T(  "Output type error"  ),  _T(  ""  ),  MB_OK  );
			GetDlgItem(  IDC_COMBO_audioOutputType  )->SetFocus(  );
			return;
		}

		//
		GetDlgItemText(  IDC_COMBO_uiBytesRecorded_perBlockAlign,  tBuf,  mycountof(  tBuf  )  );
		m_var.compressor.audio.uiBytesRecorded_perBlockAlign  =  _ttol(  tBuf  );

		//  2010/03/11
		idc  =  IDC_EDIT_uiMinTimeInMsOfAudioDataPlaying;		//  
		m_var.compressor.audio.playCfg.usMinTimeInMsOfAudioDataPlaying  =  GetDlgItemInt(  idc  );
		if  (  m_var.compressor.audio.playCfg.usMinTimeInMsOfAudioDataPlaying  <  MIN_uiMinTimeInMsOfAudioDataPlaying  ||  m_var.compressor.audio.playCfg.usMinTimeInMsOfAudioDataPlaying  >  MAX_uiMinTimeInMsOfAudioDataPlaying  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s: [ %d, %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  MIN_uiMinTimeInMsOfAudioDataPlaying,  MAX_uiMinTimeInMsOfAudioDataPlaying  );
			myMessageBox(  m_hWnd,  tBuf,  _T(  ""  ),  MB_OK  );
			GetDlgItem(  idc  )->SetFocus(  );  return;
		}

		idc  =  IDC_EDIT_uiAudioDataAddedToPlayEveryTime;		//  
		m_var.compressor.audio.playCfg.usAudioDataAddedToPlayEveryTime  =  GetDlgItemInt(  idc  );
		if  (  m_var.compressor.audio.playCfg.usAudioDataAddedToPlayEveryTime  <  MIN_uiAudioDataAddedToPlayEveryTime  ||  m_var.compressor.audio.playCfg.usAudioDataAddedToPlayEveryTime  >  MAX_uiAudioDataAddedToPlayEveryTime  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s: [ %d, %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  MIN_uiAudioDataAddedToPlayEveryTime,  MAX_uiAudioDataAddedToPlayEveryTime  );
			myMessageBox(  m_hWnd,  tBuf,  _T(  ""  ),  MB_OK  );
			GetDlgItem(  idc  )->SetFocus(  );  return;
		}

		idc  =  IDC_EDIT_uiNotifyIntervalInMs_needMoreAudioData;		//  
		m_var.compressor.audio.playCfg.usNotifyIntervalInMs_needMoreAudioData  =  GetDlgItemInt(  idc  );
		if  (  m_var.compressor.audio.playCfg.usNotifyIntervalInMs_needMoreAudioData  <  MIN_uiNotifyIntervalInMs_needMoreAudioData  ||  m_var.compressor.audio.playCfg.usNotifyIntervalInMs_needMoreAudioData  >  MAX_uiNotifyIntervalInMs_needMoreAudioData  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s: [ %d, %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  MIN_uiNotifyIntervalInMs_needMoreAudioData,  MAX_uiNotifyIntervalInMs_needMoreAudioData  );
			myMessageBox(  m_hWnd,  tBuf,  _T(  ""  ),  MB_OK  );
			GetDlgItem(  idc  )->SetFocus(  );  return;
		}
		if  (  m_var.compressor.audio.playCfg.usNotifyIntervalInMs_needMoreAudioData  >  m_var.compressor.audio.playCfg.usMinTimeInMsOfAudioDataPlaying  ||  m_var.compressor.audio.playCfg.usNotifyIntervalInMs_needMoreAudioData  >  m_var.compressor.audio.playCfg.usAudioDataAddedToPlayEveryTime  )  {
			//	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Error! The value of %s should be less than the value of %s or the value of %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_uiNotifyIntervalInMs_needMoreAudioData  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_uiMinTimeInMsOfAudioDataPlaying  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_uiMaxTimeInMsOfAudioDataPlaying  )  );
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Error! The value should be less than any of the value of the above items"  )  );
			myMessageBox(  m_hWnd,  tBuf,  _T(  ""  ),  MB_OK  );
			GetDlgItem(  idc  )->SetFocus(  );  return;
		}

		idc  =  IDC_EDIT_uiMinTimeInMsToPlay;
		m_var.compressor.audio.playCfg.usMinTimeInMsToPlay  =  GetDlgItemInt(  idc  );
		if  (  m_var.compressor.audio.playCfg.usMinTimeInMsToPlay  <=  0  ||  m_var.compressor.audio.playCfg.usMinTimeInMsToPlay  >  MAX_uiMinTimeInMsToPlay  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s: [ %d, %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  0,  MAX_uiMinTimeInMsToPlay  );
			myMessageBox(  m_hWnd,  tBuf,  _T(  ""  ),  MB_OK  );
			GetDlgItem(  idc  )->SetFocus(  );  return;
		}

		idc  =  IDC_EDIT_uiMaxTimeInMsToPlay;
		m_var.compressor.audio.playCfg.usMaxTimeInMsToPlay  =  GetDlgItemInt(  idc  );
		if  (  m_var.compressor.audio.playCfg.usMaxTimeInMsToPlay  <=  0  ||  m_var.compressor.audio.playCfg.usMaxTimeInMsToPlay  >  MAX_uiMaxTimeInMsToPlay  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s: [ %d, %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  0,  MAX_uiMaxTimeInMsToPlay  );
			myMessageBox(  m_hWnd,  tBuf,  _T(  ""  ),  MB_OK  );
			GetDlgItem(  idc  )->SetFocus(  );  return;
		}
	
		idc  =  IDC_EDIT_uiMaxTimeInMsToBeRemoved;
		m_var.compressor.audio.playCfg.usMaxTimeInMsToBeRemoved  =  GetDlgItemInt(  idc  );
		if  (  m_var.compressor.audio.playCfg.usMaxTimeInMsToBeRemoved  <=  0  ||  m_var.compressor.audio.playCfg.usMaxTimeInMsToBeRemoved  >  MAX_uiMaxTimeInMsToBeRemoved  )  {
			_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s: [ %d, %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  0,  MAX_uiMaxTimeInMsToBeRemoved  );
			myMessageBox(  m_hWnd,  tBuf,  _T(  ""  ),  MB_OK  );
			GetDlgItem(  idc  )->SetFocus(  );  return;
		}

	}
	

	//
	GetDlgItemText(  IDC_COMBO_videoCompressors,  str  );
	m_var.compressor.video.common.ucCompressors  =  qyGetTypeByDes(  gAvParams.pVideoCompressorsTable,  str  );

	if  (  m_var.compressor.video.common.ucCompressors  !=  CONST_videoCompressors_mediaSdk  )  {
		  GetDlgItem(  IDC_STATIC_videoEffect  )->ShowWindow(  SW_HIDE  );
		  GetDlgItem(  IDC_COMBO_videoEffect  )->ShowWindow(  SW_HIDE  );
	}

	if  (  m_var.compressor.video.common.ucCompressors  !=  CONST_videoCompressors_cuda  )  {
		  GetDlgItem(  IDC_STATIC_avgBitrate  )->ShowWindow(  SW_HIDE  );
		  GetDlgItem(  IDC_COMBO_avgBitrate  )->ShowWindow(  SW_HIDE  );
	}

	GetDlgItemText(  IDC_COMBO_videoCompressor,  m_var.compressor.video.compressorName,  mycountof(  m_var.compressor.video.compressorName  )  );
	if  (  !m_var.compressor.video.compressorName[0]  )  {
		myMessageBox(  m_hWnd,  _T(  "Compressor error"  ),  _T(  ""  ),  MB_OK  );
		GetDlgItem(  IDC_COMBO_videoCompressor  )->SetFocus(  );
		return;
	}


	//
	GetDlgItemText(  IDC_COMBO_videoOutputType,  tBuf,  mycountof(  tBuf  )  );
	pT  =  _tcschr(  tBuf,  _T(  ':'  )  );
	if  (  pT  )  *pT  =  0;
	tTrim(  tBuf  );
	if  (  !tBuf[0]  )  {
		myMessageBox(  m_hWnd,  _T(  "Output type error"  ),  _T(  ""  ),  MB_OK  );
		GetDlgItem(  IDC_COMBO_videoOutputType  )->SetFocus(  );
		return;
	}
	myTChar2Str(  tBuf,  m_var.compressor.video.common.fourccStr,  mycountof(  m_var.compressor.video.common.fourccStr  )  );
	
	//  2012/02/08
	if  (  m_var.compressor.video.common.ucCompressors  ==  CONST_videoCompressors_mediaSdk  )  {
		GetDlgItemText(  IDC_COMBO_videoEffect,  tBuf,  mycountof(  tBuf  )  );
		if  (  tBuf[0]  )  {
			m_var.compressor.video.common.iTargetUsage  =  qyGetTypeByDes(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_iTargetUsageTable  ),  tBuf  );
		}
	}
	//  2012/06/27
	if  (  m_var.compressor.video.common.ucCompressors  ==  CONST_videoCompressors_cuda  )  {
		GetDlgItemText(  IDC_COMBO_avgBitrate,  tBuf,  mycountof(  tBuf  )  );
		if  (  tBuf[0]  )  {
			m_var.compressor.video.common.iAvgBitrate  =  qyGetTypeByDes(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_iAvgBitrateTable  ),  tBuf  );
		}
	}
	// 
	traceLogA(  "Not finished: DlgVideoCompressors: set VIDEO_ENC_PARAMS to defaults. the params need to be modified munally. 2009/03/31"  );
	pFuncs->pf_setEncodingDefaults_video(  m_var.uiCapType,  m_var.pCompressor->video.common.usMaxFps_toShareBmp,  fourccStr2i(  m_var.compressor.video.common.fourccStr  ),  &m_var.compressor.video.params  );


	idc  =  IDC_EDIT_usMaxFPS_toShareBmp;
	m_var.compressor.video.common.usMaxFps_toShareBmp  =  GetDlgItemInt(  idc  );
	if  (  m_var.compressor.video.common.usMaxFps_toShareBmp  <=  0  ||  m_var.compressor.video.common.usMaxFps_toShareBmp  >  MAX_usFps_toShareBmp  )  {
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s: [ %d, %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  0,  MAX_usFps_toShareBmp  );
		myMessageBox(  m_hWnd,  tBuf,  _T(  ""  ),  MB_OK  );
		GetDlgItem(  idc  )->SetFocus(  );  return;
	}


	switch  (  m_var.uiCapType  )  {
		case  CONST_capType_av:
#if  0
			if  (  m_var.uiSubCapType  ==  CONST_subCapType_webcam  )  {
			}
			else  {
				#if  0
					idc  =  IDC_EDIT_usFrames_perSecond;
					m_var.compressor.usFrames_perSecond_videoConference  =  GetDlgItemInt(  idc  );
				#endif
				m_var.compressor.usFrames_perSecond_videoConference  =  m_var.compressor.video.common.usMaxFps_toShareBmp;
				if  (  m_var.compressor.usFrames_perSecond_videoConference  <=  0  ||  m_var.compressor.usFrames_perSecond_videoConference  >  MAX_usFps_toShareBmp  )  {
					_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s: [ %d, %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  0,  MAX_usFps_toShareBmp  );
					myMessageBox(  m_hWnd,  tBuf,  _T(  ""  ),  MB_OK  );
					GetDlgItem(  idc  )->SetFocus(  );  return;
				}
			}
#endif
			idc  =  IDC_EDIT_ucSeconds_perFrame;
			m_var.compressor.video.common.ucSeconds_perFrame  =  GetDlgItemInt(  idc  );
			if  (  m_var.compressor.video.common.ucSeconds_perFrame  <  0  ||  m_var.compressor.video.common.ucSeconds_perFrame  >  MAX_ucSeconds_perFrame  )  {
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s: [ %d, %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  0,  MAX_ucSeconds_perFrame  );
				myMessageBox(  m_hWnd,  tBuf,  _T(  ""  ),  MB_OK  );
				GetDlgItem(  idc  )->SetFocus(  );  return;
			}

			idc  =  IDC_EDIT_iWidth;
			m_var.compressor.video.iWidth_pic  =  GetDlgItemInt(  idc  );
			if  (  !m_var.compressor.video.iWidth_pic  ){
				GetDlgItem(  idc  )->SetFocus(  );  return;
			}

			idc  =  IDC_EDIT_iHeight;
			m_var.compressor.video.iHeight_pic  =  GetDlgItemInt(  idc  );
			if  (  !m_var.compressor.video.iHeight_pic  ){
				GetDlgItem(  idc  )->SetFocus(  );  return;
			}
			break;
		case  CONST_capType_mediaFile:
			/*  //  2012/11/05
			idc  =  IDC_EDIT_usMinFps_toShareBmp;
			m_var.compressor.video.common.usMinFps_toShareBmp  =  GetDlgItemInt(  idc  );
			if  (  m_var.compressor.video.common.usMinFps_toShareBmp  <=  0  ||  m_var.compressor.video.common.usMinFps_toShareBmp  >  MAX_usFps_toShareBmp  )  {
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s: [ %d, %d ]"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_rangeOfNumber  ),  0,  MAX_usFps_toShareBmp  );
				myMessageBox(  m_hWnd,  tBuf,  _T(  ""  ),  MB_OK  );
				GetDlgItem(  idc  )->SetFocus(  );  return;
			}
			break;  */
		case  CONST_capType_screen:
		case  CONST_capType_mediaDevice:
		default:
			break;
	}


	if  (  m_var.oldCompressor.ucSeconds_perFrame_videoConference  !=  m_var.compressor.ucSeconds_perFrame_videoConference
		||  m_var.oldCompressor.usFrames_perSecond_videoConference  !=  m_var.compressor.usFrames_perSecond_videoConference
		||  m_var.oldCompressor.audio.ucCompressors  !=  m_var.compressor.audio.ucCompressors  
		||  m_var.oldCompressor.audio.uiBytesRecorded_perBlockAlign  !=  m_var.compressor.audio.uiBytesRecorded_perBlockAlign  
		||  memcmp(  &m_var.oldCompressor.audio.playCfg,  &m_var.compressor.audio.playCfg,  sizeof(  m_var.oldCompressor.audio.playCfg  )  )
		||  memcmp(  &m_var.oldCompressor.video.common,  &m_var.compressor.video.common,  sizeof(  m_var.oldCompressor.video.common  )  )  
		||  m_var.oldCompressor.video.iWidth_pic  !=  m_var.compressor.video.iWidth_pic
		||  m_var.oldCompressor.video.iHeight_pic  !=  m_var.compressor.video.iHeight_pic  )
	{
				 //  memcmp(  &m_var.oldCompressor,  &m_var.compressor,  sizeof(  m_var.oldCompressor  )  )  ) {
				 if  (  !ucbAsked  &&  myMessageBox(  m_hWnd,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_whetherToModify  ),  _T(  ""  ),  MB_YESNO  )  !=  IDYES  )  return;
				 ucbAsked  =  TRUE;
				 saveCompressorCfg(  reg,  m_var.uiCapType,  m_var.uiSubCapType,  m_var.level,  &m_var.compressor  );
	}
	OnOK();
}



void CDlgVideoCompressors::OnCbnSelchangeComboaudiocompressors()
{	
	// TODO: Add your control notification handler code here	 
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	PolicyAvParams	&	gAvParams		=	*QY_GET_PolicyAvParams(  );
	FUNCS_for_isCliHelp	*	pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  );
	DYN_LIB_DX		*	pDynLib			=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;
	CString				str;
	unsigned  char		ucCompressors;
	CComboBox		*	pCb_compressor	=	(  CComboBox  *  )GetDlgItem(  IDC_COMBO_audioCompressor  );
	CComboBox		*	pCb_outputType	=	(  CComboBox  *  )GetDlgItem(  IDC_COMBO_audioOutputType  );
	GUID				clsid;
	TCHAR				tBuf[128];

	GetDlgItemText(  IDC_COMBO_audioCompressors,  str  );
	ucCompressors  =  qyGetTypeByDes(  gAvParams.pAudioCompressorsTable,  str  );

	if  (  m_var.bInited  )  {
		if  (  ucCompressors  ==  m_var.compressor.audio.ucCompressors  )  return;
		memset(  &m_var.compressor.audio,  0,  sizeof(  m_var.compressor.audio  )  );
		m_var.compressor.audio.ucCompressors  =  ucCompressors;
		switch  (  m_var.compressor.audio.ucCompressors  )  {
				case  CONST_audioCompressors_acm:
					  getAudioCompressorCfg_default_acm(  m_var.uiCapType,  &m_var.compressor.audio  );
					  break;
				case  CONST_audioCompressors_dmo:
					  getAudioCompressorCfg_default_dmo(  m_var.uiCapType,  &m_var.compressor.audio  );
					  break;
				case  CONST_audioCompressors_ipp:
					  getAudioCompressorCfg_default_ipp(  m_var.uiCapType,  &m_var.compressor.audio  );
					  break;
				case  CONST_audioCompressors_custom:	//  2010/04/28
					  getAudioCompressorCfg_default_custom(  m_var.uiCapType,  &m_var.compressor.audio  );					  
					  break;
				default:
						break;
		}
		m_var.compressor.audio.uiBytesRecorded_perBlockAlign  =  MACRO_getuiBytesRecorded_perBlockAlign(  m_var.compressor.audio,  &m_var.compressor.audio.wf_decompress_default  );
	}

	pCb_compressor->ResetContent(  );
	pCb_outputType->ResetContent(  );

	switch  (  ucCompressors  )  {
			case  CONST_audioCompressors_acm:  
				  clsid  =  FOURCCMap(  m_var.compressor.audio.wf_compress.wFormatTag  );
				  pCb_compressor->InsertString(  -1,  getMediaSubtypeName(  clsid  )  );		  
				  pCb_compressor->SelectString(  -1,  getMediaSubtypeName(  clsid  )  );

				  //
				  str  =  CString(  ""  )  +  getWaveFormatExStr(  ucCompressors,  &m_var.compressor.audio.wf_compress,  tBuf,  mycountof(  tBuf  )  );
				  pCb_outputType->InsertString(  -1,  str  );
				  pCb_outputType->SelectString(  -1,  str  );
				  break;
			case  CONST_audioCompressors_dmo:  
				  clsid  =  FOURCCMap(  m_var.compressor.audio.wf_compress.wFormatTag  );
				  pFuncs->pf_getDmoInfoBySth(  pDynLib,  &m_var.clsid_category_audio,  NULL,  NULL,  NULL,  &clsid,  NULL,  NULL,  &m_var.compressor.audio  );    

				  pFuncs->pf_enumDmos(  (  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx,  &m_var.clsid_category_audio,  pCb_compressor->m_hWnd  );

				  pCb_compressor->SelectString(  -1,  m_var.compressor.audio.compressorName  );

				  if  (  !pFuncs->pf_getDmoInfoBySth(  pDynLib,  &m_var.clsid_category_audio,  m_var.compressor.audio.compressorName,  NULL,  NULL,  NULL,  NULL,  &clsid,  NULL  )  )  {
					  QY_AUDIO_HEADER	ah;
					  BOOL				bOutputSupported  =  FALSE;
					  memcpy(  &ah.wfx,  &m_var.compressor.audio.wf_compress,  sizeof(  ah.wfx  )  );
					  if  (  !pFuncs->pf_enumDmoIoTypes(  &clsid,  NULL,  NULL,  NULL,  NULL,  &ah,  &bOutputSupported,  pCb_outputType->m_hWnd  )  )  {
						  if  (  bOutputSupported  )  memcpy(  &m_var.compressor.audio.wf_compress,  &ah.wfx,  sizeof(  m_var.compressor.audio.wf_compress  )  );
					  }		
					  if  (  !bOutputSupported  )  {
					  }
				  }
				  
				  int		i;
				  for  (  i  =  0;  i  <  pCb_outputType->GetCount(  );  i  ++  )  {
					   CString	str;

					   pCb_outputType->GetLBText(  i,  str  );
					   //  traceLogA(  "%d is %S",  i,  str  );
					   if  (  _tcsstr(  str,  getWaveFormatExStr(  m_var.compressor.audio.ucCompressors,  &m_var.compressor.audio.wf_compress,  tBuf,  mycountof(  tBuf  )  )  )  )  {
						   pCb_outputType->SetCurSel(  i  );
						   break;			 
					  }		
				  }			  		  
				
				  //  SetDlgItemText(  IDC_STATIC_defaultFmtVal,  getWaveFormatExStr(  m_var.compressor.audio.ucCompressors,  &m_var.compressor.audio.wf_decompress_default  )  );
				  break;	
			case  CONST_audioCompressors_ipp:	{		//  2012/01/20
				  clsid  =  FOURCCMap(  m_var.compressor.audio.wf_compress.wFormatTag  );
				  pCb_compressor->InsertString(  -1,  getMediaSubtypeName(  clsid  )  );		  
				  pCb_compressor->SelectString(  -1,  getMediaSubtypeName(  clsid  )  );

				  //
				  str  =  CString(  ""  )  +  getWaveFormatExStr(  ucCompressors,  &m_var.compressor.audio.wf_compress,  tBuf,  mycountof(  tBuf  )  );
				  pCb_outputType->InsertString(  -1,  str  );
				  pCb_outputType->SelectString(  -1,  str  );
				  }				  
				  break;
			case  CONST_audioCompressors_custom:  {
				  clsid  =  FOURCCMap(  m_var.compressor.audio.wf_compress.wFormatTag  );
				  pCb_compressor->InsertString(  -1,  getMediaSubtypeName(  clsid  )  );		  
				  pCb_compressor->SelectString(  -1,  getMediaSubtypeName(  clsid  )  );

				  //
				  str  =  CString(  ""  )  +  getWaveFormatExStr(  ucCompressors,  &m_var.compressor.audio.wf_compress,  tBuf,  mycountof(  tBuf  )  );
				  pCb_outputType->InsertString(  -1,  str  );
				  pCb_outputType->SelectString(  -1,  str  );
				  }				  
				  break;
			default:
					break;
	}

	if  (  m_var.uiCapType  ==  CONST_capType_av  )  {
		SetDlgItemText(  IDC_STATIC_defaultFmtVal,  getWaveFormatExStr(  m_var.compressor.audio.ucCompressors,  &m_var.compressor.audio.wf_decompress_default,  tBuf,  mycountof(  tBuf  )  )  );
	}

	fill_uiBytesRecorded_perBlockAligns(  m_var.compressor.audio.wf_decompress_default.nSamplesPerSec,  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_uiBytesRecorded_perBlockAlign  )  );
	(  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_uiBytesRecorded_perBlockAlign  )  )->SelectString(  -1,  _ltot(  m_var.compressor.audio.uiBytesRecorded_perBlockAlign,  tBuf,  10  )  );

errLabel:
	return;
}


 void CDlgVideoCompressors::OnCbnSelchangeComboaudiocompressor()
{
	// TODO: Add your control notification handler code here
	int						iErr			=	-1;
	QY_MC				*	pQyMc			=	QY_GET_GBUF(  );
	FUNCS_for_isCliHelp	*	pFuncs			=	QY_GET_FUNCS_for_isCliHelp(  );
	DYN_LIB_DX			*	pDynLib			=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;
	CString					str;
	GUID					clsid;
	BOOL					bInputSupported	=	FALSE;

	CComboBox			*	pCb_compressor	=	(  CComboBox  *  )GetDlgItem(  IDC_COMBO_audioCompressor  );
	CComboBox			*	pCb_outputType	=	(  CComboBox  *  )GetDlgItem(  IDC_COMBO_audioOutputType  );

	int						iCurSel;

	iCurSel  =  pCb_compressor->GetCurSel(  );

	if  (  m_var.compressor.audio.ucCompressors  ==  CONST_audioCompressors_acm  )  {
		
		iErr  =  0;  goto  errLabel;
	}

	GetDlgItemText(  IDC_COMBO_audioCompressor,  str  );
	
	(  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_audioOutputType  )  )->ResetContent(  );
	if  (  !pFuncs->pf_getDmoInfoBySth(  pDynLib,  &m_var.clsid_category_audio,  str,  NULL,  NULL,  NULL,  NULL,  &clsid,  NULL  )  )  {
		if  (  !pFuncs->pf_enumDmoIoTypes(  &clsid,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  GetDlgItem(  IDC_COMBO_audioOutputType  )->m_hWnd  )  )  {
		}
	}

	iErr  =  0;
errLabel:
	return;
}


 void CDlgVideoCompressors::OnCbnSelchangeComboaudiooutputtype()
{
	// TODO: Add your control notification handler code here
	TCHAR	tBuf[128];

	GetDlgItemText(  IDC_COMBO_audioOutputType,  tBuf,  mycountof(  tBuf  )  );
	getWaveFormatExByStr(   tBuf,  &m_var.compressor.audio.wf_compress  );

	makeWaveFormat_pcm(  m_var.compressor.audio.wf_compress.nChannels,  m_var.compressor.audio.wf_compress.nSamplesPerSec,  m_var.compressor.audio.wf_compress.wBitsPerSample,  &m_var.compressor.audio.wf_decompress_default  );

	SetDlgItemText(  IDC_STATIC_defaultFmtVal,  getWaveFormatExStr(  m_var.compressor.audio.ucCompressors,  &m_var.compressor.audio.wf_decompress_default,  tBuf,  mycountof(  tBuf  )  )  );

	//  m_var.compressor.audio.uiBytesRecorded_perBlockAlign  =  m_var.compressor.audio.wf_decompress_default.nSamplesPerSec  /  5;
	m_var.compressor.audio.uiBytesRecorded_perBlockAlign  =  MACRO_getuiBytesRecorded_perBlockAlign(  m_var.compressor.audio,  &m_var.compressor.audio.wf_decompress_default  );


	fill_uiBytesRecorded_perBlockAligns(  m_var.compressor.audio.wf_decompress_default.nSamplesPerSec,  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_uiBytesRecorded_perBlockAlign  )  );
	(  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_uiBytesRecorded_perBlockAlign  )  )->SelectString(  -1,  _ltot(  m_var.compressor.audio.uiBytesRecorded_perBlockAlign,  tBuf,  10  )  );

}


void CDlgVideoCompressors::OnCbnSelchangeCombovideocompressors()
{
	// TODO: Add your control notification handler code here	
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	PolicyAvParams	&	gAvParams		=	*QY_GET_PolicyAvParams(  );
	FUNCS_for_isCliHelp	*	pFuncs		=	QY_GET_FUNCS_for_isCliHelp(  );
	DYN_LIB_DX		*	pDynLib			=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;
	CString				str;
	unsigned  char		ucCompressors;
	CComboBox		*	pCb_compressor	=	(  CComboBox  *  )GetDlgItem(  IDC_COMBO_videoCompressor  );
	CComboBox		*	pCb_outputType	=	(  CComboBox  *  )GetDlgItem(  IDC_COMBO_videoOutputType  );
	TCHAR				tBuf[128];


	GetDlgItemText(  IDC_COMBO_videoCompressors,  str  );
	ucCompressors  =  qyGetTypeByDes(  gAvParams.pVideoCompressorsTable,  str  );

	if  (  m_var.bInited  )  {
		if  (  ucCompressors  ==  m_var.compressor.video.common.ucCompressors  )  return;
		memset(  &m_var.compressor.video,  0,  sizeof(  m_var.compressor.video  )  );
		m_var.compressor.video.common.ucCompressors  =  ucCompressors;
		switch  (  m_var.compressor.video.common.ucCompressors  )  {
				case  CONST_videoCompressors_vcm:
					  safeStrnCpy(  DEFAULT_fourccStr_vcm,  m_var.compressor.video.common.fourccStr,  mycountof(  m_var.compressor.video.common.fourccStr  )  );
					  break;
				case  CONST_videoCompressors_dmo:
					  safeStrnCpy(  DEFAULT_fourccStr_dmo_video,  m_var.compressor.video.common.fourccStr,  mycountof(  m_var.compressor.video.common.fourccStr  )  );
					  pFuncs->pf_setEncodingDefaults_video(  m_var.uiCapType,  m_var.pCompressor->video.common.usMaxFps_toShareBmp,  fourccStr2i(  m_var.compressor.video.common.fourccStr  ),  &m_var.compressor.video.params  );
					  break;

				case  CONST_videoCompressors_ipp:  {		//  2011/07/31
					  CUS_MODULE_U  *  pModule	=	pQyMc->cusModules.pIpp;
					  if  (  !pModule  )  goto  errLabel;
					  if  (  !pModule->compress.ucbInited  )  goto  errLabel;

					  if  (  !pModule->compress.pf_qdcGetCompressVideoCfg  )  goto  errLabel;
					  if  (  pModule->compress.pf_qdcGetCompressVideoCfg(  m_var.compressor.video.common.fourccStr,  mycountof(  m_var.compressor.video.common.fourccStr  )  )  )  goto  errLabel;

					  }
					  break;

				case  CONST_videoCompressors_mediaSdk:  {		//  2011/11/25
					  CUS_MODULE_U  *  pModule	=	pQyMc->cusModules.pMediaSdk;
					  if  (  !pModule  )  goto  errLabel;
					  if  (  !pModule->compress.ucbInited  )  goto  errLabel;

					  if  (  !pModule->compress.pf_qdcGetCompressVideoCfg  )  goto  errLabel;
					  if  (  pModule->compress.pf_qdcGetCompressVideoCfg(  m_var.compressor.video.common.fourccStr,  mycountof(  m_var.compressor.video.common.fourccStr  )  )  )  goto  errLabel;

					  }
					  break;

				case  CONST_videoCompressors_cuda:  {		//  2012/06/17
					  CUS_MODULE_U  *  pModule	=	pQyMc->cusModules.pCuda;
					  if  (  !pModule  )  goto  errLabel;
					  if  (  !pModule->compress.ucbInited  )  goto  errLabel;

					  if  (  !pModule->compress.pf_qdcGetCompressVideoCfg  )  goto  errLabel;
					  if  (  pModule->compress.pf_qdcGetCompressVideoCfg(  m_var.compressor.video.common.fourccStr,  mycountof(  m_var.compressor.video.common.fourccStr  )  )  )  goto  errLabel;

					  }
					  break;

				case  CONST_videoCompressors_custom:  {
					  CUS_MODULE_U  *  pModule	=	pFuncs->pf_getCusModule(  pQyMc,  CONST_moduleType_compress,  0,  0,  NULL  );
					  if  (  !pModule  )  goto  errLabel;
					  if  (  !pModule->compress.ucbInited  )  goto  errLabel;

					  if  (  !pModule->compress.pf_qdcGetCompressVideoCfg  )  goto  errLabel;
					  if  (  pModule->compress.pf_qdcGetCompressVideoCfg(  m_var.compressor.video.common.fourccStr,  mycountof(  m_var.compressor.video.common.fourccStr  )  )  )  goto  errLabel;

					  }
					  break;
				default:
						goto  errLabel;
						break;
		}
	}


	pCb_compressor->ResetContent(  );
	pCb_outputType->ResetContent(  );

	switch  (  ucCompressors  )  {
			case  CONST_videoCompressors_vcm:  
				  pCb_compressor->InsertString(  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectCompressor  )  );

				  //  if  (  m_var.bInited  )  {
				  //	  safeStrnCpy(  DEFAULT_fourccStr_vcm,  m_var.compressor.video.fourccStr,  mycountof(  m_var.compressor.video.fourccStr  )  );
				  //  }

				  pCb_compressor->InsertString(  -1,  CString(  m_var.compressor.video.common.fourccStr  )  );		  
				  pCb_compressor->SelectString(  -1,  CString(  m_var.compressor.video.common.fourccStr  )  );

				  pCb_outputType->InsertString(  -1,  CString(  m_var.compressor.video.common.fourccStr  )  );
				  pCb_outputType->SelectString(  -1,  CString(  m_var.compressor.video.common.fourccStr  )  );
				  break;
			case  CONST_videoCompressors_dmo:
				  //  if  (  m_var.bInited  )  {
				  // 	  safeStrnCpy(  DEFAULT_fourccStr_dmo_video,  m_var.compressor.video.fourccStr,  mycountof(  m_var.compressor.video.fourccStr  )  );
				  //	  setEncodingDefaults_video(  m_var.uiCapType,  fourccStr2i(  m_var.compressor.video.fourccStr  ),  &m_var.compressor.video.params  );
				  //  }

				  GUID	clsid;
				  clsid  =  FOURCCMap(  fourccStr2i(  m_var.compressor.video.common.fourccStr  )  );
				  pFuncs->pf_getDmoInfoBySth(  pDynLib,  &m_var.clsid_category_video,  NULL,  NULL,  NULL,  &clsid,  NULL,  NULL,  &m_var.compressor.video  );    

				  pFuncs->pf_enumDmos(  (  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx,  &m_var.clsid_category_video,  GetDlgItem(  IDC_COMBO_videoCompressor  )->m_hWnd  );

				  (  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_videoCompressor  )  )->SelectString(  -1,  m_var.compressor.video.compressorName  );

				  if  (  !pFuncs->pf_getDmoInfoBySth(  pDynLib,  &m_var.clsid_category_video,  m_var.compressor.video.compressorName,  NULL,  NULL,  NULL,  NULL,  &clsid,  NULL  )  )  {
					  if  (  !pFuncs->pf_enumDmoIoTypes(  &clsid,  (  m_var.bEnumCompressors_video  ?  &MEDIASUBTYPE_RGB24  :  NULL  ),  NULL,  NULL,  (  m_var.bEnumCompressors_video  ?  NULL  :  &MEDIASUBTYPE_RGB24  ),  NULL,  NULL,  pCb_outputType->m_hWnd  )  )  {
					  }					
				  }
				  int		i;
				  for  (  i  =  0;  i  <  pCb_outputType->GetCount(  );  i  ++  )  {
					   CString	str;

					   pCb_outputType->GetLBText(  i,  str  );
					   //  traceLogA(  "%d is %S",  i,  str  );
					   if  (  _tcsstr(  str,  CString(  m_var.compressor.video.common.fourccStr  )  )  )  {
						   pCb_outputType->SetCurSel(  i  );
						   break;			 
					  }		
				  }
				  break;	
			case  CONST_videoCompressors_ipp:
			case  CONST_videoCompressors_mediaSdk:
			case  CONST_videoCompressors_cuda:
			case  CONST_videoCompressors_custom:  {		  
				  pCb_compressor->InsertString(  -1,  CString(  m_var.compressor.video.common.fourccStr  )  );		  
				  pCb_compressor->SelectString(  -1,  CString(  m_var.compressor.video.common.fourccStr  )  );

				  pCb_outputType->InsertString(  -1,  CString(  m_var.compressor.video.common.fourccStr  )  );
				  pCb_outputType->SelectString(  -1,  CString(  m_var.compressor.video.common.fourccStr  )  );
				  }
				  break;
			default:
					break;
	}

errLabel:

	BOOL	bVisible_iTargetUsage  =  FALSE;
	BOOL	bVisible_iAvgBitrate  =  FALSE;
	switch  (  ucCompressors  )  {
			case  CONST_videoCompressors_mediaSdk:
				  bVisible_iTargetUsage  =  TRUE;
				  break;
			case  CONST_videoCompressors_cuda:		//  2012/06/27
				  bVisible_iAvgBitrate  =  TRUE;
				  break;
			default:
					break;
	}
	GetDlgItem(  IDC_STATIC_videoEffect  )->ShowWindow(  bVisible_iTargetUsage  ?  SW_SHOW  :  SW_HIDE  );
	GetDlgItem(  IDC_COMBO_videoEffect  )->ShowWindow(  bVisible_iTargetUsage  ?  SW_SHOW  :  SW_HIDE  );
	int  iTargetUsage  =  DEFAULT_iTargetUsage;
	(  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_videoEffect  )  )->SelectString(  -1,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_iTargetUsageTable  ),  iTargetUsage  )  );
	//  2012/06/27
	GetDlgItem(  IDC_STATIC_avgBitrate  )->ShowWindow(  bVisible_iAvgBitrate  ?  SW_SHOW  :  SW_HIDE  );
	GetDlgItem(  IDC_COMBO_avgBitrate  )->ShowWindow(  bVisible_iAvgBitrate  ?  SW_SHOW  :  SW_HIDE  );
	int  iAvgBitrate  =  DEFAULT_iAvgBitrate;
	(  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_avgBitrate  )  )->SelectString(  -1,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_iAvgBitrateTable  ),  iAvgBitrate  )  );

	return;
}

 int  selectCompressor_vcm(  /*MC_VAR_isCli  *  pProcInfo,*/  CDialog  *  pDlg,  CAP_procInfo_video  *  pVc,  BOOL  *  pbSupported,  VIDEO_COMPRESSOR_CFG  *  pCfg  )
{
#ifdef  __WINCE__
		return  -1;
#else

	int						iErr							=	-1;
	QY_MC				*	pQyMc							=	QY_GET_GBUF(  );
	COMPVARS				cv;
	BOOL					bSupported						=	FALSE;
	TCHAR					tHintBuf[256]					=	_T(  ""  );


	memset(  &cv,  0,  sizeof(  cv  )  );
	cv.cbSize  =  sizeof(  cv  );
	cv.fccType  =  ICTYPE_VIDEO;
	// 
	if  (  !ICCompressorChoose(  pDlg->m_hWnd,  ICMF_CHOOSE_ALLCOMPRESSORS,  NULL,  NULL,  &cv,  (  "To choose compressor"  )  )  )  goto  errLabel;
	
	bSupported  =  TRUE;

	ICINFO	icInfo;

	//  printFourcc(  cv.fccHandler  );
	memset(  &icInfo,  0,  sizeof(  icInfo  )  );
	if  (  !ICGetInfo(  cv.hic,  &icInfo,  sizeof(  icInfo  )  )  )  goto  errLabel;

	//
	memset(  pCfg,  0,  sizeof(  pCfg[0]  )  );
	pCfg->common.ucCompressors  =  CONST_videoCompressors_vcm;
	if  (  !iFourcc2Str(  cv.fccHandler,  pCfg->common.fourccStr,  mycountof(  pCfg->common.fourccStr  )  )  )  pCfg->common.fourccStr[0]  =  0;		
	lstrcpyn(  pCfg->compressorName,  icInfo.szDescription,  mycountof(  pCfg->compressorName  )  );

	iErr  =  0;

errLabel:

	if  (  cv.hic  )  ICClose(  cv.hic  );
	if  (  tHintBuf[0]  )  myMessageBox(  NULL,  tHintBuf,  _T(  ""  ),  MB_OK  );
	if  (  !iErr  )  {
		if  (  pbSupported  )  *pbSupported  =  bSupported;
	}
	
	return  iErr;
#endif
}


void CDlgVideoCompressors::OnCbnSelchangeCombovideocompressor()
{
	// TODO: Add your control notification handler code here
	int						iErr			=	-1;
	QY_MC				*	pQyMc			=	QY_GET_GBUF(  );
	FUNCS_for_isCliHelp	*	pFuncs			=	QY_GET_FUNCS_for_isCliHelp(  );
	DYN_LIB_DX			*	pDynLib			=	(  DYN_LIB_DX  *  )(  (  QY_DYN_LIBS  *  )pQyMc->env.pDynLibs  )->pLib_dx;
	CString					str;
	GUID					clsid;
	BOOL					bInputSupported	=	FALSE;

	CComboBox			*	pCb_compressor	=	(  CComboBox  *  )GetDlgItem(  IDC_COMBO_videoCompressor  );
	CComboBox			*	pCb_outputType	=	(  CComboBox  *  )GetDlgItem(  IDC_COMBO_videoOutputType  );

	int						iCurSel;

	iCurSel  =  pCb_compressor->GetCurSel(  );

	if  (  m_var.compressor.video.common.ucCompressors  ==  CONST_videoCompressors_vcm  )  {
		if  (  !iCurSel  )  {
			BOOL	bSupported  =  FALSE;
			
			for  (  ;  ;  )  {

				 bSupported	=	FALSE;
				 if  (  selectCompressor_vcm(  /*m_var.pProcInfo, */ this,  NULL,  &bSupported,  &m_var.compressor.video  )  )  break;
				 if  (  !bSupported  )  continue;

				 break;
			}

			pCb_compressor->ResetContent(  );
			pCb_outputType->ResetContent(  );

			pCb_compressor->InsertString(  0,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectCompressor  )  );

			pCb_compressor->InsertString(  -1,  CString(  m_var.compressor.video.compressorName  )  );		  
			pCb_compressor->SelectString(  -1,  CString(  m_var.compressor.video.compressorName  )  );

			pCb_outputType->InsertString(  -1,  CString(  m_var.compressor.video.common.fourccStr  )  );
			pCb_outputType->SelectString(  -1,  CString(  m_var.compressor.video.common.fourccStr  )  );

			iErr  =  0;  goto  errLabel;
		}

		iErr  =  0;  goto  errLabel;
	}

	GetDlgItemText(  IDC_COMBO_videoCompressor,  str  );
	
	(  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_videoOutputType  )  )->ResetContent(  );
	if  (  !pFuncs->pf_getDmoInfoBySth(  pDynLib,  &m_var.clsid_category_video,  str,  NULL,  NULL,  NULL,  NULL,  &clsid,  NULL  )  )  {
		if  (  !pFuncs->pf_enumDmoIoTypes(  &clsid,  (  m_var.bEnumCompressors_video  ?  &MEDIASUBTYPE_RGB24  :  NULL  ),  NULL,  &bInputSupported,  (  m_var.bEnumCompressors_video  ?  NULL  :  &MEDIASUBTYPE_RGB24  ),  NULL,  NULL,  GetDlgItem(  IDC_COMBO_videoOutputType  )->m_hWnd  )  )  {
			if  (  !bInputSupported  )  (  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_videoOutputType  )  )->ResetContent(  );
		}
	}

	iErr  =  0;
errLabel:
	return;
}

void CDlgVideoCompressors::OnCbnSelchangeCombovideooutputtype()
{
}

void CDlgVideoCompressors::OnBnClickedButtoncfgwmv()
{
	// TODO: Add your control notification handler code here
#ifdef  __SUPPORT_CFGWMV__
#if  0
	CDlgCfgWmv	dlg;

	dlg.DoModal(  );
#endif
#endif
	showDlgCfgWmv(  m_hWnd  );
}



void CDlgVideoCompressors::OnCbnSelchangeCombovideoeffect()
{
	// TODO: Add your control notification handler code here	
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	CString				str;
	int					iVideoEffect;
	CComboBox		*	pCb_videoEffect	=	(  CComboBox  *  )GetDlgItem(  IDC_COMBO_videoEffect  );
	int					idc;

	idc  =  IDC_COMBO_videoEffect;
	GetDlgItemText(  idc,  str  );
	iVideoEffect  =  qyGetTypeByDes(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_iTargetUsageTable  ),  str  );

	if  (  m_var.bInited  )  {
		if  (  iVideoEffect  ==  m_var.compressor.video.common.iTargetUsage  )  return;
		m_var.compressor.video.common.iTargetUsage  =  iVideoEffect;
	}


	(  (  CComboBox  *  )GetDlgItem(  idc  )  )->SelectString(  -1,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_iTargetUsageTable  ),  iVideoEffect  )  );
	//  pCb_videoEffect->ResetContent(  );

errLabel:
	return;
}

void CDlgVideoCompressors::OnCbnSelchangeComboavgbitrate()
{
	// TODO: Add your control notification handler code here	
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );
	CString				str;
	int					iAvgBitrate;
	CComboBox		*	pCb_avgBitrate	=	(  CComboBox  *  )GetDlgItem(  IDC_COMBO_avgBitrate  );
	int					idc;

	idc  =  IDC_COMBO_avgBitrate;
	GetDlgItemText(  idc,  str  );
	iAvgBitrate  =  qyGetTypeByDes(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_iAvgBitrateTable  ),  str  );

	if  (  m_var.bInited  )  {
		if  (  iAvgBitrate  ==  m_var.compressor.video.common.iAvgBitrate  )  return;
		m_var.compressor.video.common.iAvgBitrate  =  iAvgBitrate;
	}

	(  (  CComboBox  *  )GetDlgItem(  idc  )  )->SelectString(  -1,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_iAvgBitrateTable  ),  iAvgBitrate  )  );

errLabel:
	return;
}
