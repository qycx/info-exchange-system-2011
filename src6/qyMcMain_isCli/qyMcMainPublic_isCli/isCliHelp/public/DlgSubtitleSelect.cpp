// DlgSubtitleSelect.cpp : implementation file
//

#include "stdafx.h"
#include	"qyMcMainCommon.h"
#include	"myresource.h"
#include "DlgSubtitleSelect.h"
#include "afxdialogex.h"

#include	"isCliHelpPublic.h"



  __declspec(  dllexport  )  int  showDlgSubtitleSelect(  HWND  hParent,  void  *  pSUBTITLE_cfg  )
 {
	 AFX_MANAGE_STATE(AfxGetStaticModuleState());
	 
	int	iRet	=	-1;

	CDlgSubtitleSelect	dlg(  CWnd::FromHandle(  hParent  )  );
	memcpy(  &dlg.m_var.subtitleCfg,  pSUBTITLE_cfg,  sizeof(  dlg.m_var.subtitleCfg  )  );	

	if  (  dlg.DoModal(  )  !=  IDOK  )  goto  errLabel;

	memcpy(  pSUBTITLE_cfg,  &dlg.m_var.subtitleCfg,  sizeof(  dlg.m_var.subtitleCfg  )  );

	iRet  =  IDOK;
errLabel:
	return  iRet;

 }


// CDlgSubtitleSelect dialog

IMPLEMENT_DYNAMIC(CDlgSubtitleSelect, CDialogEx)

CDlgSubtitleSelect::CDlgSubtitleSelect(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgSubtitleSelect::IDD, pParent)
{
	memset(  &m_var,  0,  sizeof(  m_var  )  );

	//
	m_var.guiData.iIDC_CHECK_displayTime  =  IDC_CHECK_displayTime;

	m_var.guiData.iIDC_BUTTON_selectFont  =  IDC_BUTTON_selectFont;
	m_var.guiData.iIDC_BUTTON_fontColor  =  IDC_BUTTON_fontColor;

	m_var.guiData.iIDC_STATIC_staticMaskColor  =  IDC_STATIC_staticMaskColor;
	m_var.guiData.iIDC_EDIT_maskColor_r  =  IDC_EDIT_maskColor_r;
	m_var.guiData.iIDC_EDIT_maskColor_g  =  IDC_EDIT_maskColor_g;
	m_var.guiData.iIDC_EDIT_maskColor_b  =  IDC_EDIT_maskColor_b;

	m_var.guiData.iIDC_STATIC_xyStart  =  IDC_STATIC_xyStart;

	m_var.guiData.iIDC_EDIT_xStart  =  IDC_EDIT_xStart;
	m_var.guiData.iIDC_EDIT_yStart  =  IDC_EDIT_yStart;
				
	m_var.guiData.iIDC_CHECK_bottomUp  =  IDC_CHECK_bottomUp;

	//
	m_var.guiData.iIDC_CHECK_3dShadow  =  IDC_CHECK_3dShadow;
	m_var.guiData.iIDC_BUTTON_shadowColor  =  IDC_BUTTON_shadowColor;
	m_var.guiData.iIDC_EDIT_shadow_xOffset  =  IDC_EDIT_shadow_xOffset;
	m_var.guiData.iIDC_EDIT_shadow_yOffset  =  IDC_EDIT_shadow_yOffset;


	//
	m_var.guiData.iIDOK  =  IDOK;
	m_var.guiData.iIDCANCEL  =  IDCANCEL;


}

CDlgSubtitleSelect::~CDlgSubtitleSelect()
{
}

BOOL  CDlgSubtitleSelect::bShowInfo(  )
{
	TCHAR	tBuf[256];
	SUBTITLE_cfg	*	pTagCfg	=	&m_var.subtitleCfg;

	setIdcChked(  m_hWnd,  m_var.guiData.iIDC_CHECK_displayTime,  pTagCfg->tag.ucbDisplayTime  );
	
	//
	bShowInfo_selectFont(  );

	//
	bShowInfo_fontColor(  );

	//
	BYTE  r, g, b;
			
	//
	r  =  pTagCfg->color.maskColor_r;
	SetDlgItemInt(  m_var.guiData.iIDC_EDIT_maskColor_r,  r,  FALSE  );
	g  =  pTagCfg->color.maskColor_g;
	SetDlgItemInt(  m_var.guiData.iIDC_EDIT_maskColor_g,  g,  FALSE  );
	b  =  pTagCfg->color.maskColor_b;
	SetDlgItemInt(  m_var.guiData.iIDC_EDIT_maskColor_b,  b,  FALSE  );

	//
	SetDlgItemInt(  m_var.guiData.iIDC_EDIT_xStart,  pTagCfg->pos.xStart,  FALSE  );
	SetDlgItemInt(  m_var.guiData.iIDC_EDIT_yStart,  pTagCfg->pos.yStart,  FALSE  );
	setIdcChked(  m_hWnd,  m_var.guiData.iIDC_CHECK_bottomUp,  pTagCfg->pos.ucbBottomUp  );

	//
	setIdcChked(  m_hWnd,  m_var.guiData.iIDC_CHECK_3dShadow,  pTagCfg->color.ucb3dShadow  );

	//
	bShowInfo_shadowColor(  );

	//
	BOOL  bSigned  =  TRUE;
	SetDlgItemInt(  m_var.guiData.iIDC_EDIT_shadow_xOffset,  pTagCfg->color.shadow_xOffset,  bSigned  );
	SetDlgItemInt(  m_var.guiData.iIDC_EDIT_shadow_yOffset,  pTagCfg->color.shadow_yOffset,  bSigned  );
	
	//
	return  TRUE;
}


BOOL  CDlgSubtitleSelect::bShowInfo_selectFont(  )
{
	TCHAR	tBuf[256];
	SUBTITLE_cfg	*	pTagCfg	=	&m_var.subtitleCfg;
	
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  pTagCfg->font.lf.lfFaceName  );	
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %d"  ),  tBuf,  pTagCfg->font.iFontSize  );
	SetDlgItemText(  m_var.guiData.iIDC_BUTTON_selectFont,  tBuf  );

	return  TRUE;
}

BOOL  CDlgSubtitleSelect::bShowInfo_fontColor(  )
{
	TCHAR	tBuf[256];
	SUBTITLE_cfg	*	pTagCfg	=	&m_var.subtitleCfg;
	
	//
	tBuf[0]  =  0;
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s RGB(%d,%d,%d)"  ),  tBuf,  (  int  )pTagCfg->color.fontColor_r,  (  int  )pTagCfg->color.fontColor_g,  (  int  )pTagCfg->color.fontColor_b  );
	SetDlgItemText(  m_var.guiData.iIDC_BUTTON_fontColor,  tBuf  );

	return  TRUE;
}

BOOL  CDlgSubtitleSelect::bShowInfo_shadowColor(  )
{
	TCHAR	tBuf[256];
	SUBTITLE_cfg	*	pTagCfg	=	&m_var.subtitleCfg;
	
	//
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "Shadow:"  )  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s RGB(%d,%d,%d)"  ),  tBuf,  (  int  )pTagCfg->color.shadowColor_r,  (  int  )pTagCfg->color.shadowColor_g,  (  int  )pTagCfg->color.shadowColor_b  );
	SetDlgItemText(  m_var.guiData.iIDC_BUTTON_shadowColor,  tBuf  );

	return  TRUE;
}


void CDlgSubtitleSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgSubtitleSelect, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgSubtitleSelect::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_selectFont, &CDlgSubtitleSelect::OnBnClickedButtonselectfont)
	ON_BN_CLICKED(IDC_BUTTON_fontColor, &CDlgSubtitleSelect::OnBnClickedButtonfontcolor)
	ON_BN_CLICKED(IDC_BUTTON_shadowColor, &CDlgSubtitleSelect::OnBnClickedButtonshadowcolor)
END_MESSAGE_MAP()


// CDlgSubtitleSelect message handlers


void CDlgSubtitleSelect::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	m_var.subtitleCfg.tag.ucbDisplayTime  =  isIdcChked(  m_hWnd,  m_var.guiData.iIDC_CHECK_displayTime  );

	//
	unsigned  char  r  =  ::GetDlgItemInt(  m_hWnd,  m_var.guiData.iIDC_EDIT_maskColor_r,  NULL,  FALSE  );
	m_var.subtitleCfg.color.maskColor_r  =  r;
	
	unsigned  char  g  =  ::GetDlgItemInt(  m_hWnd,  m_var.guiData.iIDC_EDIT_maskColor_g,  NULL,  FALSE  );
	m_var.subtitleCfg.color.maskColor_g  =  g;
	
	unsigned  char  b  =  ::GetDlgItemInt(  m_hWnd,  m_var.guiData.iIDC_EDIT_maskColor_b,  NULL,  FALSE  );
	m_var.subtitleCfg.color.maskColor_b  =  b;

	//
	int	xStart  =  ::GetDlgItemInt(  m_hWnd,  m_var.guiData.iIDC_EDIT_xStart,  NULL,  FALSE  );
	m_var.subtitleCfg.pos.xStart  =  xStart;
	
	int	yStart  =  ::GetDlgItemInt(  m_hWnd,  m_var.guiData.iIDC_EDIT_yStart,  NULL,  FALSE  );
	m_var.subtitleCfg.pos.yStart  =  yStart;

	//
	m_var.subtitleCfg.pos.ucbBottomUp  =  isIdcChked(  m_hWnd,  m_var.guiData.iIDC_CHECK_bottomUp  );

	//
	m_var.subtitleCfg.color.ucb3dShadow  =  isIdcChked(  m_hWnd,  m_var.guiData.iIDC_CHECK_3dShadow  );
	if  (  m_var.subtitleCfg.color.ucb3dShadow  )  {
		BOOL  bSigned  =  TRUE;
		m_var.subtitleCfg.color.shadow_xOffset  =  ::GetDlgItemInt(  m_hWnd,  m_var.guiData.iIDC_EDIT_shadow_xOffset,  NULL,  bSigned  );
		m_var.subtitleCfg.color.shadow_yOffset  =  ::GetDlgItemInt(  m_hWnd,  m_var.guiData.iIDC_EDIT_shadow_yOffset,  NULL,  bSigned  );
	}

	//
	CDialogEx::OnOK();
}


BOOL CDlgSubtitleSelect::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );

	cusDlgRes(  0,  &pQyMc->cusRes,  m_hWnd,  IDD  );
	bShowInfo(  );


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgSubtitleSelect::OnBnClickedButtonselectfont()
{
	// TODO: Add your control notification handler code here
	SUBTITLE_cfg  *  pTagCfg	=	&m_var.subtitleCfg;

	DWORD dwFlags = CF_SCREENFONTS;	//  CF_EFFECTS | CF_SCREENFONTS;
	CFontDialog	fontDlg(  &pTagCfg->font.lf,  dwFlags,  0,  this  );
	fontDlg.m_cf.rgbColors  =  RGB(  pTagCfg->color.fontColor_r,  pTagCfg->color.fontColor_g,  pTagCfg->color.fontColor_b  );

	if  (  fontDlg.DoModal(  )  ==  IDOK  )  {
		DWORD	dwTickCnt  =  GetTickCount(  );

		memcpy(  &pTagCfg->font.lf,  fontDlg.m_cf.lpLogFont,  sizeof(  pTagCfg->font.lf  )  );
		//
#if  0
		pTagCfg->color.fontColor_r  =  GetRValue(  fontDlg.m_cf.rgbColors  );
		pTagCfg->color.fontColor_g  =  GetGValue(  fontDlg.m_cf.rgbColors  );
		pTagCfg->color.fontColor_b  =  GetBValue(  fontDlg.m_cf.rgbColors  );
#endif
		//
		pTagCfg->font.iFontSize  =  fontDlg.m_cf.iPointSize  /  10;
		//
		bShowInfo_selectFont(  );
		//
	}

}


void CDlgSubtitleSelect::OnBnClickedButtonfontcolor()
{
	// TODO: Add your control notification handler code here
	SUBTITLE_cfg  *  pTagCfg	=	&m_var.subtitleCfg;

	COLORREF		color  =  RGB(  pTagCfg->color.fontColor_r,  pTagCfg->color.fontColor_g,  pTagCfg->color.fontColor_b  );;
	DWORD			dwFlags  =  CC_RGBINIT;
	dwFlags  |=  CC_FULLOPEN;	//  CC_ANYCOLOR;			//  
	CColorDialog	dlg(  color,  dwFlags,  this  );

	if  (  dlg.DoModal(  )  ==  IDOK  )  {
		color  =  dlg.GetColor(  );
		//
		pTagCfg->color.fontColor_r  =  GetRValue(  color  );
		pTagCfg->color.fontColor_g  =  GetGValue(  color  );
		pTagCfg->color.fontColor_b  =  GetBValue(  color  );

		//
		bShowInfo_fontColor(  );
	}
}

void CDlgSubtitleSelect::OnBnClickedButtonshadowcolor()
{
	// TODO: Add your control notification handler code here
	SUBTITLE_cfg  *  pTagCfg	=	&m_var.subtitleCfg;

	COLORREF		color  =  RGB(  pTagCfg->color.shadowColor_r,  pTagCfg->color.shadowColor_g,  pTagCfg->color.shadowColor_b  );;
	DWORD			dwFlags  =  CC_RGBINIT;
	dwFlags  |=  CC_FULLOPEN;	//  CC_ANYCOLOR;			//  
	CColorDialog	dlg(  color,  dwFlags,  this  );

	if  (  dlg.DoModal(  )  ==  IDOK  )  {
		color  =  dlg.GetColor(  );
		//
		pTagCfg->color.shadowColor_r  =  GetRValue(  color  );
		pTagCfg->color.shadowColor_g  =  GetGValue(  color  );
		pTagCfg->color.shadowColor_b  =  GetBValue(  color  );

		//
		bShowInfo_shadowColor(  );
	}



}


