
#include	"stdafx.h"
#include	<time.h>
#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"
#include	"qmcDmoPublic.h"
#include	"qmcCmdProc.h"
#include	"tmpCeLib.h"
//  #include	"myfourcc.h"
#include	"module_qisCamCap.h"
#include	"isCmdConst.h"
#include	"qyOpenShellCommon.h"
#include	"qyCusResTemp.h"
#include	"policyAvParams.h"
#include	"isCliHelpPublic.h"


void  CTX_mem_free(  CTX_addTxt  *  pCtx,  int  index  )
{
	if  (  !pCtx  )  return;
	if  (  index  <  0  ||  index  >=  mycountof(  pCtx->mems  )  )  return;

	if  (  pCtx->mems[index].hFont  )  {
		DeleteObject(  pCtx->mems[index].hFont  );  pCtx->mems[index].hFont  =  NULL;
	}

	//  2013/03/11
	MACRO_safeFree(  pCtx->mems[index].pTxtBuf  );
	pCtx->mems[index].iTxtBufSize  =  0;

	return;
}

void  CTX_addTxt_free(  void  *  pCTX_addTxt  )
{
	CTX_addTxt  *  pCtx  =  (    CTX_addTxt  *  )pCTX_addTxt;

	if  (  !pCtx  )  return;

	int  i;
	for  (  i  =  0;  i  <  mycountof(  pCtx->mems  );  i  ++  )  {
		CTX_mem_free(  pCtx,  i  );
	}

	return;
}


//  2010/09/13
#ifndef  __WINCE__

int  updateImg_addTxt(  CTX_addTxt  *  pCtx,  LPCTSTR  videoHint,  BITMAPINFO  *  pBmi_pic,  int  index  )
{
	int			iErr	=	-1;
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	HWND				hWnd		=	pQyMc->gui.hMainWnd;
	HDC					hDc			=	NULL;
	HDC					hDc_mem		=	NULL;
	HBITMAP				hBmp		=	NULL;
	HBITMAP				hBmp_old	=	NULL;
	HFONT				hFont		=	NULL;
	
	
	if  (  index  <  0  ||  index  >=  mycountof(  pCtx->mems  )  )  return  -1;
	
	//
	BOOL	bNeedUpdate  =  FALSE;
	if  (  pCtx->mems[index].tickCnts.dwModifiedTickCnt_font  !=  pCtx->subtitlesCfg.mems[index].tickCnts.dwModifiedTickCnt_font  
		||  pCtx->mems[index].tickCnts.dwModifiedTickCnt_color  !=  pCtx->subtitlesCfg.mems[index].tickCnts.dwModifiedTickCnt_color
		||  pCtx->mems[index].tickCnts.dwModifiedTickCnt_tag  !=  pCtx->subtitlesCfg.mems[index].tickCnts.dwModifiedTickCnt_tag  )
	{
		bNeedUpdate  =  TRUE;
	}
	if  (  !bNeedUpdate  )  {
		if  (  !index  )  {//  注意: 实际上只有index为0时才使用这个videoHint. 
			if  (  !videoHint  )  videoHint  =  _T(  ""  );
			if  (  _tcscmp(  videoHint,  pCtx->subtitle0_defaultTag  )  )  {
				safeTcsnCpy(  videoHint,  pCtx->subtitle0_defaultTag,  mycountof(  pCtx->subtitle0_defaultTag  )  );
				bNeedUpdate  =  TRUE;  
			}
		}
	}
	if  (  !bNeedUpdate  )  {
		if  (  pCtx->subtitlesCfg.mems[index].subtitle.tag.ucbDisplayTime  )  {
			time_t				t;
			char				timeBuf[CONST_qyTimeLen  +  1]	=	"";
			//
			time(  &t  );
			getTimelStr(  t,  timeBuf,  mycountof(  timeBuf  )  );		//  2013/03/25
			//
			if  (  strcmp(  timeBuf,  pCtx->timeBuf  )  )  {
				safeStrnCpy(  timeBuf,  pCtx->timeBuf,  mycountof(  pCtx->timeBuf  )  );
				bNeedUpdate  =  TRUE;
			}
		}
	}
	if  (  !bNeedUpdate  )  {
		iErr  =  0;  goto  errLabel;
	}

	//
#ifdef  __DEBUG__
		traceLog(  _T(  "updateImg_addTxt,  bNeedUpdate true, index %d"  ),  index  );
#endif

	//
	if  (  pCtx->mems[index].tickCnts.dwModifiedTickCnt_font  !=  pCtx->subtitlesCfg.mems[index].tickCnts.dwModifiedTickCnt_font  )  {
		if  (  pCtx->mems[index].hFont  )  {
			DeleteObject(  pCtx->mems[index].hFont  );  pCtx->mems[index].hFont  =  NULL;					 
		}
	}

	//
	if  (  !pCtx->mems[index].hFont  )  {				
		if  (  pCtx->subtitlesCfg.mems[index].subtitle.font.lf.lfFaceName[0]  )  {
			pCtx->mems[index].hFont  =  CreateFontIndirect(  &pCtx->subtitlesCfg.mems[index].subtitle.font.lf  );  				 
		}								 
	}
			
	
	//
	TCHAR	hint[256]	=	_T(  ""  );		

	//		
	if  (  pCtx->subtitlesCfg.mems[index].subtitle.tag.ucbUseDefault  )  {
		if  (  !index  )  {
			_sntprintf(  hint,  mycountof(  hint  ),  _T(  "%s%s"  ),  hint,  pCtx->subtitle0_defaultTag  );
		}
		}		
	else  {
		  _sntprintf(  hint,  mycountof(  hint  ),  _T(  "%s%s"  ),  hint,  pCtx->subtitlesCfg.mems[index].subtitle.tag.txt  );		
	}

	//  2013/03/21. 第0行在demo中不让修改
	QM_SHM_CMDS	*	pShmCmds  =  QY_GET_shmCmds(  );				
	if  (  pShmCmds  )  {
		if  (  pShmCmds->ucbDaemonDemo  )  {
			if  (  !index  )  {
				_sntprintf(  hint,  mycountof(  hint  ),  _T(  "%s"  ),  pCtx->subtitle0_defaultTag  );
			}
		}	
	}


	//				
	if  (  pCtx->subtitlesCfg.mems[index].subtitle.tag.ucbDisplayTime  )  {
				char  y2[2  +  1],  MM[2  +  1],  dd[2  +  1],  hh[2  +  1],  mm[2  +  1],  ss[2  +  1];
				safeStrnCpy(  pCtx->timeBuf  +  2,  y2,  mycountof(  y2  )  );
				safeStrnCpy(  pCtx->timeBuf  +  4,  MM,  mycountof(  MM  )  );
				safeStrnCpy(  pCtx->timeBuf  +  6,  dd,  mycountof(  dd  )  );
				safeStrnCpy(  pCtx->timeBuf  +  8,  hh,  mycountof(  hh  )  );
				safeStrnCpy(  pCtx->timeBuf  +  10,  mm,  mycountof(  mm  )  );
				safeStrnCpy(  pCtx->timeBuf  +  12,  ss,  mycountof(  ss  )  );

				_sntprintf(  hint,  mycountof(  hint  ),  _T(  "%s %S/%S/%S %S:%S:%S"  ),  hint,  y2,  MM,  dd,  hh,  mm,  ss  );					
	}	

	//
	if  (  !hint[0]  )  {  //  这里表明没有txt
		MACRO_safeFree(  pCtx->mems[index].pTxtBuf  );
		iErr  =  0;  goto  errLabel;
	}

		//
		//  2013/03/11
		G_guiData_qyMc  *  pGuiData  =  get_g_guiData(  );
		

		HFONT				hFont_toTextOut		=	NULL;
		int  iW_txtImg  =  0;	//  pBmi_pic->bmiHeader.biWidth;
		int  iH_txtImg  =  0;
		
		if  (  pCtx->mems[index].hFont  )  {
			hFont_toTextOut  =  pCtx->mems[index].hFont;
			iH_txtImg  =  abs(  pCtx->subtitlesCfg.mems[index].subtitle.font.lf.lfHeight  );
			}
		else  {
			  if  (  pBmi_pic->bmiHeader.biWidth  <=  320  )  {
				  hFont_toTextOut  =  pGuiData->hFont_videoHint_320x240;
				  iH_txtImg  =  pGuiData->lfHeight_videoHint_320x240;
				  }
			  else  if  (  pBmi_pic->bmiHeader.biWidth  <  1280  )  {
						hFont_toTextOut  =  pGuiData->hFont_videoHint_640x480;
						iH_txtImg  =  pGuiData->lfHeight_videoHint_640x480;
				        }
			  else  if  (  pBmi_pic->bmiHeader.biWidth  <  1920  )  {
						hFont_toTextOut  =  pGuiData->hFont_videoHint_1280x720;
						iH_txtImg  =  pGuiData->lfHeight_videoHint_1280x720;	
				  		}		
			  else  {
				    hFont_toTextOut  =  pGuiData->hFont_videoHint_1920x1080;
					iH_txtImg  =  pGuiData->lfHeight_videoHint_1920x1080;		  
			  }
		}


		//
		hDc  =  GetDC(  hWnd  );
		if  (  !hDc  )  goto  errLabel;

		hDc_mem  =  CreateCompatibleDC(  hDc  );
		if  (  !hDc_mem  )  goto  errLabel;


#if  10
		//
		if  (  hFont_toTextOut  )  {
			hFont  =  (  HFONT  )SelectObject(  hDc_mem,  hFont_toTextOut  );
		}

		//  2013/03/11
		GetTextExtentPoint32(  hDc_mem,  hint,  lstrlen(  hint  ),  &pCtx->mems[index].size_GetTextExtentPoint32  );
		if  (  pCtx->mems[index].size_GetTextExtentPoint32.cy  <=  0  )  goto  errLabel;

		//
		int  shadow_xOffset  =  0;  
		int  shadow_yOffset  =  0;
		if  (  pCtx->subtitlesCfg.mems[index].subtitle.color.ucb3dShadow  )  {
			shadow_xOffset  =  pCtx->subtitlesCfg.mems[index].subtitle.color.shadow_xOffset;
			shadow_yOffset  =  pCtx->subtitlesCfg.mems[index].subtitle.color.shadow_yOffset;
		}

		//
		iW_txtImg  =  min(  pBmi_pic->bmiHeader.biWidth,  pCtx->mems[index].size_GetTextExtentPoint32.cx  +  abs(  shadow_xOffset  )  );
		iH_txtImg  =  min(  pBmi_pic->bmiHeader.biHeight,  pCtx->mems[index].size_GetTextExtentPoint32.cy  +  abs(  shadow_yOffset  )  );
		
		if  (  iW_txtImg  <=  0  ||  iH_txtImg  <=  0  )  goto  errLabel;
		
		//
		if  (  pCtx->mems[index].pTxtBuf  )  {
			if  (  iW_txtImg  !=  pCtx->mems[index].bih_txt.biWidth  ||  iH_txtImg  !=  pCtx->mems[index].bih_txt.biHeight  )  {
				MACRO_safeFree(  pCtx->mems[index].pTxtBuf  );
			}
		}

		//
		if  (  !pCtx->mems[index].pTxtBuf  )  {					
			makeBmpInfoHeader_rgb(  24,  iW_txtImg,  iH_txtImg,  &pCtx->mems[index].bih_txt  );
			pCtx->mems[index].iTxtBufSize  =  pCtx->mems[index].bih_txt.biSizeImage;
			pCtx->mems[index].pTxtBuf  =  (  char  *  )malloc(  pCtx->mems[index].iTxtBufSize  );
			if  (  !pCtx->mems[index].pTxtBuf  )  goto  errLabel;
		}


		//  2013/03/11
		BITMAPINFO	*	pBmi_txt	=	(  BITMAPINFO  *  )&pCtx->mems[index].bih_txt;
		char		*	pTxtBuf		=	pCtx->mems[index].pTxtBuf;
		
		if  (  !pTxtBuf  ||  !pBmi_txt->bmiHeader.biWidth  ||  !pBmi_txt->bmiHeader.biHeight  )  goto  errLabel;
#endif

		//
		hBmp  =  CreateCompatibleBitmap(  hDc,  pBmi_txt->bmiHeader.biWidth,  pBmi_txt->bmiHeader.biHeight  );
		if  (  !hBmp  )  goto  errLabel;

		hBmp_old  =  (  HBITMAP  )SelectObject(  hDc_mem,  hBmp  );
		if  (  !hBmp_old  )  goto  errLabel;

		//  
		//  brushDc(  RGB(  222,  222,  222  ),  hDc_mem,  0,  0,  pBmi_txt->bmiHeader.biWidth,  pBmi_txt->bmiHeader.biHeight  );
		brushDc(  RGB(  pCtx->subtitlesCfg.mems[index].subtitle.color.maskColor_r,  pCtx->subtitlesCfg.mems[index].subtitle.color.maskColor_g,  pCtx->subtitlesCfg.mems[index].subtitle.color.maskColor_b  ),  hDc_mem,  0,  0,  pBmi_txt->bmiHeader.biWidth,  pBmi_txt->bmiHeader.biHeight  );



		#ifdef  __DEBUG__
				//  traceLog(  _T(  "iW_txtImg %d, iH_txtImg %d, size_GetTextExtentPoint32.cx %d, cy %d"  ),  iW_txtImg,  iH_txtImg,  pCtx->size_GetTextExtentPoint32.cx,  pCtx->size_GetTextExtentPoint32.cy  );
		#endif

		//
		SetBkMode(  hDc_mem,  TRANSPARENT  );
		//
		int  xStart  =  0;
		int  yStart  =  0;
		//
		if  (  pCtx->subtitlesCfg.mems[index].subtitle.color.ucb3dShadow  )  {
			SetTextColor(  hDc_mem,  RGB(  pCtx->subtitlesCfg.mems[index].subtitle.color.shadowColor_r,  pCtx->subtitlesCfg.mems[index].subtitle.color.shadowColor_g,  pCtx->subtitlesCfg.mems[index].subtitle.color.shadowColor_b  )  );
			if  (  shadow_xOffset  <  0  )  xStart  =  0;
			else  xStart  =  shadow_xOffset;
			if  (  shadow_yOffset  <  0  )  yStart  =  0;
			else  yStart  =  shadow_yOffset;
			TextOut(  hDc_mem,  xStart,  yStart,  hint,  lstrlen(  hint  )  );		
		}
		//
		SetTextColor(  hDc_mem,  RGB(  pCtx->subtitlesCfg.mems[index].subtitle.color.fontColor_r,  pCtx->subtitlesCfg.mems[index].subtitle.color.fontColor_g,  pCtx->subtitlesCfg.mems[index].subtitle.color.fontColor_b  )  );
		if  (  shadow_xOffset  <  0  )  xStart  =  abs(  shadow_xOffset  );
		else  xStart  =  0;
		if  (  shadow_yOffset  <  0  )  yStart  =  abs(  shadow_yOffset  );
		else  yStart  =  0;
		TextOut(  hDc_mem,  xStart,  yStart,  hint,  lstrlen(  hint  )  );		
		SetBkMode(  hDc_mem,  OPAQUE  );
		if  (  hFont  )  {
			SelectObject(  hDc_mem,  hFont  );  hFont  =  NULL;
		}

		//  
		int	nCount  =  GetDIBits(  hDc_mem,  hBmp,  0,  pBmi_txt->bmiHeader.biHeight,  pTxtBuf,  (  BITMAPINFO  *  )pBmi_txt,  DIB_RGB_COLORS  );
		
		//
		iErr  =  0;

errLabel:

		if  (  !iErr  )  {
			//	
			memcpy(  &pCtx->mems[index].tickCnts,  &pCtx->subtitlesCfg.mems[index].tickCnts,  sizeof(  pCtx->mems[index].tickCnts  )  );
		}

		//
	if  (  hFont  )  {
		SelectObject(  hDc_mem,  hFont  );  hFont  =  NULL;	
	}


	if  (  hBmp_old  )  SelectObject(  hDc_mem,  hBmp_old  );

	if  (  hBmp  )  DeleteObject(  hBmp  );
	if  (  hDc_mem  )  DeleteDC(  hDc_mem  );
	if  (  hDc  )  ReleaseDC(  hWnd,  hDc  );

		return  iErr;

}

int drawImg_addTxt(  CTX_addTxt  *  pCtx,  BITMAPINFO  *  pBmi_pic,  char  *  pPicBuf,  int  index  )
{
	int		iErr	=	-1;

	if  (  index  <  0  ||  index  >=  mycountof(  pCtx->mems  )  )  return  -1;	

	//
	BITMAPINFO	*	pBmi_txt	=	(  BITMAPINFO  *  )&pCtx->mems[index].bih_txt;
	char		*	pTxtBuf		=	pCtx->mems[index].pTxtBuf;

	if  (  !pTxtBuf  ||  !pBmi_txt->bmiHeader.biWidth  ||  !pBmi_txt->bmiHeader.biHeight  )  goto  errLabel;

	//
	int				lineBytes_txt	=	M_lineBytes_rgb(  24,  pBmi_txt->bmiHeader.biWidth  );
	int				lineBytes_pic	=	M_lineBytes_rgb(  24,  pBmi_pic->bmiHeader.biWidth  );
	int				iW			=	min(  pBmi_txt->bmiHeader.biWidth,  pBmi_pic->bmiHeader.biWidth  );
	int				iH			=	min(  pBmi_txt->bmiHeader.biHeight,  pBmi_pic->bmiHeader.biHeight  );
	int				i,  j;
	BYTE		*	pPix_txt;
	BYTE		*	pPix_pic;

	//
	int  shadow_xOffset  =  0;  		
	int  shadow_yOffset  =  0;
	if  (  pCtx->subtitlesCfg.mems[index].subtitle.color.ucb3dShadow  )  {
		shadow_xOffset  =  pCtx->subtitlesCfg.mems[index].subtitle.color.shadow_xOffset;
		shadow_yOffset  =  pCtx->subtitlesCfg.mems[index].subtitle.color.shadow_yOffset;		
	}
	int  shadow_xOffset_abs  =  abs(  shadow_xOffset  );
	int  shadow_yOffset_abs  =  abs(  shadow_yOffset  );

	//
	int  xStart  =  pCtx->subtitlesCfg.mems[index].subtitle.pos.xStart;
	int  yStart  =  pCtx->subtitlesCfg.mems[index].subtitle.pos.yStart;
	if  (  shadow_xOffset  <  0  )  xStart  -=  shadow_xOffset_abs;
	if  (  shadow_yOffset  <  0  )  yStart  -=  shadow_yOffset_abs;
	//
	int  x;
	int	 y;
	//
	if  (  xStart  <  0  )  xStart  =  0;
	if  (  yStart  <  0  )  yStart  =  0;
	//
	for  (  j  =  0;  j  <  iH;  j  ++  )  {
		 //
		 if  (  j  >=  pCtx->mems[index].size_GetTextExtentPoint32.cy  +  shadow_yOffset_abs  )  {
			 #ifdef  __DEBUG__
					 //  traceLog(  _T(  "j %d, size_GetTextExtentPoint32.cy %d"  ),  j,  pCtx->size_GetTextExtentPoint32.cy  );
			 #endif
			 break;
		 }

		 //
		 if  (  !pCtx->subtitlesCfg.mems[index].subtitle.pos.ucbBottomUp  )  {
			 y  =  (  j  +  pBmi_pic->bmiHeader.biHeight  -  iH  )  -  yStart;
			 }
		 else  {
			   y  =  j  +  yStart;
		 }
		 if  (  y  <  0  )  continue;
		 if  (  y  >=  pBmi_pic->bmiHeader.biHeight  )  break;

		 //
		 for  (  i  =  0;  i  <  iW;  i  ++  )  {
			  //
			  if  (  i  >=  pCtx->mems[index].size_GetTextExtentPoint32.cx  +  shadow_xOffset_abs  )  break;
			  //
			  pPix_txt  =  (  BYTE  *  )(  pTxtBuf  +  j  *  lineBytes_txt  +  i  *  3  );
			  if  (  pPix_txt[0]  ==  pCtx->subtitlesCfg.mems[index].subtitle.color.maskColor_b	//  222
				  &&  pPix_txt[1]  ==  pCtx->subtitlesCfg.mems[index].subtitle.color.maskColor_g	//  222
				  &&  pPix_txt[2]  ==  pCtx->subtitlesCfg.mems[index].subtitle.color.maskColor_r	//  222  
				  )  
			  {			
				  continue;
			  }
			  //
			  //  pPix_pic  =  (  BYTE  *  )(  pPicBuf  +  (  j  +  pBmi_pic->bmiHeader.biHeight  -  iH  )  *  lineBytes_pic  +  i  *  3  );
			  x  =  i  +  xStart;
			  if  (  x  <  0  )  continue;
			  if  (  x  >=  pBmi_pic->bmiHeader.biWidth  )  break;
			  //
			  pPix_pic  =  (  BYTE  *  )(  pPicBuf  +  y  *  lineBytes_pic  +  x  *  3  );			  
			  memcpy(  pPix_pic,  pPix_txt,  3  );
			  continue;
		 }
	}

	iErr  =  0;

errLabel:


	return  iErr;
	
}

 //  2013/03/10
 //  int  addTxtToPic(  CTX_addTxt  *  pCtx,  unsigned  char  ucbDaemonDemo,  LPCTSTR  videoHint,  DWORD  dwTickCnt_start,  COMPRESS_VIDEO  *  pCompressVideo,  BITMAPINFO  *  pBmi_pic,  char  *  pPicBuf  )
 int  addTxtToPic(  CTX_addTxt  *  pCtx,  unsigned  char  ucbDaemonDemo,  LPCTSTR  videoHint,  DWORD  dwTickCnt_start,  QY_SHARED_OBJ  *  pSharedObj,  COMPRESS_VIDEO  *  pCompressVideo,  BITMAPINFO  *  pBmi_pic,  char  *  pPicBuf  )
{
	int					iErr		=	-1;
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	int					i;

	//  2013/03/10
	if  (  !pCompressVideo  )  return  -1;
	
	//
	SUBTITLES_cfg	*	pSubtitlesCfg  =  &pCtx->subtitlesCfg;
	
	//
	if  (  !pPicBuf  )  {
		#ifdef  __DEBUG__
				traceLog(  _T(  "addTxtToPic failed, pPicBuf is null"  )  );
		#endif
		return  -1;
	}
	if  (  pBmi_pic->bmiHeader.biClrImportant  !=  BI_RGB  
		||  pBmi_pic->bmiHeader.biBitCount  !=  24  )  
	{
		#ifdef  __DEBUG__
				traceLog(  _T(  "addTxtToPic failed, pPic is not rgb24"  )  );
		#endif
		return  -1;
	}
 

	//
	if  (  1  //  pCompressVideo->tLastTime_addTxt  !=  pCompressVideo->input.tStartTran  
		)  
	{
		//  pCompressVideo->tLastTime_addTxt  =  pCompressVideo->input.tStartTran;		
		
		SUBTITLES_cfg	*	pCurCfg  =  (  SUBTITLES_cfg  *  )getCurSubtitlesCfg(  pSharedObj->uiType,  pCompressVideo->compressor.common.uiCapType,  pCompressVideo->compressor.common.uiSubCapType  );
		if  (  !pCurCfg  )  goto  errLabel;

		//
		if  (  pCurCfg->dwModifiedTickCnt_any_start  !=  pSubtitlesCfg->dwModifiedTickCnt_any_start  )  {
			SUBTITLES_cfg	tmpCfg;
			memcpy(  &tmpCfg,  pCurCfg,  sizeof(  tmpCfg  )  );
			if  (  tmpCfg.dwModifiedTickCnt_any_start  !=  tmpCfg.dwModifiedTickCnt_any_end  )  goto  errLabel;
			//
			memcpy(  pSubtitlesCfg,  &tmpCfg,  sizeof(  pSubtitlesCfg[0]  )  );
			//
		}

		//
		TCHAR	hint[256]	=	_T(  ""  );		
		TCHAR	*	pT		=	_T(  ""  );
		if  (  ucbDaemonDemo  )  {
			if  (  dwTickCnt_start  )  {
				int  n  =  GetTickCount(  )  -  dwTickCnt_start;
				n  =  n  /  1000;			
				n  =  pQyMc->uiMaxTimeInS_videoConference  -  n;
				_sntprintf(  hint,  mycountof(  hint  ),  _T(  "剩余%d分%d秒. "  ),  n  /  60,  n  %  60  );
			}
	
			pT  =  _T(  ""  );
			switch  (  pQyMc->env.usLangId  )  {
					case  CONST_langId_PRC:
						  pT  =  _T(  "清扬试用版. www.qycx.com"  );
						  break;
					case  CONST_langId_tw:
						  pT  =  _T(  "清揚试用版. www.qycx.com"  );
						  break;
					default:
						    pT  =  _T(  "Qycx trial edition. www.qycx.com"  );
							break;
			}
			_sntprintf(  hint,  mycountof(  hint  ),  _T(  "%s%s "  ),  hint,  pT  );
		}
				
		//	
		if  (  pCtx->subtitlesCfg.mems[0].subtitle.tag.ucbUseDefault
			&&  videoHint  )  
		{
			_sntprintf(  hint,  mycountof(  hint  ),  _T(  "%s %s"  ),  hint,  videoHint  );	
		}

		//
		for  (  i  =  0;  i  <  mycountof(  pCtx->mems  );  i  ++  )  {

			 //
			 updateImg_addTxt(  pCtx,  i  ?  NULL  :  hint,  pBmi_pic,  i  );
		}
	}

	//
	if  (  !pSubtitlesCfg->flgs.ucbShowVideoHint  )  {
		if  (  !ucbDaemonDemo  )  {	//  2013/04/06
			iErr  =  0;  goto  errLabel;
		}
	}
	
#if  10
	for  (  i  =  0;  i  <  mycountof(  pCtx->mems  );  i  ++  )  {
		 if  (  !pSubtitlesCfg->flgs.ucbShowVideoHint  )  {
			 MACRO_qyAssert(  ucbDaemonDemo,  _T(  "Demo"  )  );
			 //  要把提示行显示出来
			 if  (  i  !=  0  )  continue;
		 }
		 //
		 drawImg_addTxt(  pCtx,  pBmi_pic,  pPicBuf,  i  );
	}
#endif
		 

	iErr  =  0;

errLabel:

	return  iErr;
}


#endif


 //  2013/03/10

 int  addTxtToPic_screen(  void  *  pCTX_addTxt,  unsigned  char  ucbDaemonDemo,  int  iW_pic,  int  iH_pic,  HDC  hMemDC  )
{
	 int		iErr	=	-1;

	 CTX_addTxt  *  pCtx  =  (  CTX_addTxt  *  )pCTX_addTxt;
	 
	 QY_MC	*	pQyMc		=	QY_GET_GBUF(  );	
	 HDC		hDc_mem		=  hMemDC;
	 TCHAR		hint[256]	=	_T(  ""  );
	 TCHAR	*	pT			=	_T(  ""  );
	 TCHAR	*	videoHint	=	_T(  ""  );
	 
	 //
	 SUBTITLES_cfg	*	pSubtitlesCfg  =  &pCtx->subtitlesCfg;
	 
	 {
		 //
		 SUBTITLES_cfg  *  pCurCfg  =  (  SUBTITLES_cfg  *  )getCurSubtitlesCfg(  0,  CONST_capType_screen,  0  );	
		 if  (  !pCurCfg  )  goto  errLabel;
	 	
		 //	
		 if  (  pCurCfg->dwModifiedTickCnt_any_start  !=  pSubtitlesCfg->dwModifiedTickCnt_any_start  )  {			
			 SUBTITLES_cfg	tmpCfg;
			 memcpy(  &tmpCfg,  pCurCfg,  sizeof(  tmpCfg  )  );
			 if  (  tmpCfg.dwModifiedTickCnt_any_start  !=  tmpCfg.dwModifiedTickCnt_any_end  )  goto  errLabel;
			 //
			 memcpy(  pSubtitlesCfg,  &tmpCfg,  sizeof(  pSubtitlesCfg[0]  )  );
			 //		
		 }	 
	 }


	 int  index;
	 for  (  index  =  0;  index  <  mycountof(  pCtx->mems  );  index  ++  )  {
		  //
		  if  (  pCtx->mems[index].tickCnts.dwModifiedTickCnt_font  !=  pCtx->subtitlesCfg.mems[index].tickCnts.dwModifiedTickCnt_font  )  {
			  if  (  pCtx->mems[index].hFont  )  {
				  DeleteObject(  pCtx->mems[index].hFont  );  pCtx->mems[index].hFont  =  NULL;					 		
			  }	
		  }
		  
		  //
		  if  (  !pCtx->mems[index].hFont  )  {				
			  if  (  pCtx->subtitlesCfg.mems[index].subtitle.font.lf.lfFaceName[0]  )  {
				  pCtx->mems[index].hFont  =  CreateFontIndirect(  &pCtx->subtitlesCfg.mems[index].subtitle.font.lf  );  				 
			  }								 	
		  }

		  //
		  memcpy(  &pCtx->mems[index].tickCnts,  &pCtx->subtitlesCfg.mems[index].tickCnts,  sizeof(  pCtx->mems[index].tickCnts  )  );	
	 }

	 //
	 if  (  !pCtx->subtitlesCfg.flgs.ucbShowVideoHint  )  {
		 if  (  !ucbDaemonDemo  )  {
			 iErr  =  0;  goto  errLabel;
		 }
	 }


	 for  (  index  =  0;  index  <  mycountof(  pCtx->mems  );  index  ++  )  {

		  //
		  if  (  !pCtx->subtitlesCfg.flgs.ucbShowVideoHint  )  {
			  MACRO_qyAssert(  ucbDaemonDemo,  _T(  "Demo"  )  );
			  //  对demo, 要把提示行显示出来. 非提示行都过滤掉
			  if  (  index  !=  0  )  continue;
		  }

		  //
		  if  (  !pSubtitlesCfg->mems[index].subtitle.tag.ucbUseDefault  )  videoHint  =  pSubtitlesCfg->mems[index].subtitle.tag.txt;				 		  
		  else  videoHint  =  _T(  ""  );

		  pT  =  _T(  ""  );
		  if  (  ucbDaemonDemo  )  {		
			  if  (  !index  )  {
				  switch  (  pQyMc->env.usLangId  )  {			
						  case  CONST_langId_PRC:
								pT  =  _T(  "清扬视频会议试用版. www.qycx.com"  );
								break;
						  case  CONST_langId_tw:
							    pT  =  _T(  "清揚視訊會議试用版. www.qycx.com"  );
								break;
						  default:					
								pT  =  _T(  "Qycx Video Conference trial edition. www.qycx.com"  );						
								break;				
				  }	 
			  }
		  }
	
		  //
		  if  (  !pT[0]  &&  !videoHint[0]  &&  !pSubtitlesCfg->mems[index].subtitle.tag.ucbDisplayTime  )  {		
			  continue;	 
		  }

		  //
		  //  if  (  pSubtitlesCfg->flgs.ucbShowVideoHint  )  
		  {
			  hint[0]  =  0;
			  if  (  pT[0]  )  {
				  _sntprintf(  hint,  mycountof(  hint  ),  _T(  "%s"  ),  pT  );
			  }
			  if  (  videoHint  )  {
				  _sntprintf(  hint,  mycountof(  hint  ),  _T(  "%s%s"  ),  hint,  videoHint  );
			  }
			  if  (  pSubtitlesCfg->mems[index].subtitle.tag.ucbDisplayTime  )  {				
				  time_t	t;
				  char		timeBuf[CONST_qyTimeLen  +  1];				
				  char		displayBuf[128];
				  //
				  time(  &t  );
				  getTimelStr(  t,  timeBuf,  mycountof(  timeBuf  )  );
				  //
				  char  y2[2  +  1],  MM[2  +  1],  dd[2  +  1],  hh[2  +  1],  mm[2  +  1],  ss[2  +  1];
				  safeStrnCpy(  timeBuf  +  2,  y2,  mycountof(  y2  )  );
				  safeStrnCpy(  timeBuf  +  4,  MM,  mycountof(  MM  )  );
				  safeStrnCpy(  timeBuf  +  6,  dd,  mycountof(  dd  )  );
				  safeStrnCpy(  timeBuf  +  8,  hh,  mycountof(  hh  )  );
				  safeStrnCpy(  timeBuf  +  10,  mm,  mycountof(  mm  )  );
				  safeStrnCpy(  timeBuf  +  12,  ss,  mycountof(  ss  )  );
				  
				  _sntprintf(  hint,  mycountof(  hint  ),  _T(  "%s %S/%S/%S %S:%S:%S"  ),  hint,  y2,  MM,  dd,  hh,  mm,  ss  );			
			  }			 
		  }

	
		  //
		  HFONT				hFont		=	NULL;
		  int				xStart;
		  int				yStart;

		  //
		  if  (  pCtx->mems[index].hFont  )  {			
			  hFont  =  (  HFONT  )SelectObject(  hDc_mem,  pCtx->mems[index].hFont  );			
		  }
		  
		  //
		  GetTextExtentPoint32(  hDc_mem,  hint,  lstrlen(  hint  ),  &pCtx->mems[index].size_GetTextExtentPoint32  );
	 
		  //	 
		  SetBkMode(  hDc_mem,  TRANSPARENT  );		
		  if  (  pSubtitlesCfg->mems[index].subtitle.color.ucb3dShadow  )  {
			  SetTextColor(  hDc_mem,  RGB(  pSubtitlesCfg->mems[index].subtitle.color.shadowColor_r,  pSubtitlesCfg->mems[index].subtitle.color.shadowColor_g,  pSubtitlesCfg->mems[index].subtitle.color.shadowColor_b  )  );
			  xStart  =  pSubtitlesCfg->mems[index].subtitle.pos.xStart  +  pSubtitlesCfg->mems[index].subtitle.color.shadow_xOffset;		//  11
			  yStart  =  pSubtitlesCfg->mems[index].subtitle.pos.yStart;
			  if  (  pSubtitlesCfg->mems[index].subtitle.pos.ucbBottomUp  )  {
				  yStart  =  iH_pic  -  pCtx->mems[index].size_GetTextExtentPoint32.cy  -  pSubtitlesCfg->mems[index].subtitle.pos.yStart;		  
			  }
			  yStart  +=  pSubtitlesCfg->mems[index].subtitle.color.shadow_yOffset;		//  51
			  TextOut(  hDc_mem,  xStart,  yStart,  hint,  lstrlen(  hint  )  );
		  }
		  SetTextColor(  hDc_mem,  RGB(  pSubtitlesCfg->mems[index].subtitle.color.fontColor_r,  pSubtitlesCfg->mems[index].subtitle.color.fontColor_g,  pSubtitlesCfg->mems[index].subtitle.color.fontColor_b  )  );
		  xStart  =  pSubtitlesCfg->mems[index].subtitle.pos.xStart;		//  11
		  yStart  =  pSubtitlesCfg->mems[index].subtitle.pos.yStart;		//  51
		  if  (  pSubtitlesCfg->mems[index].subtitle.pos.ucbBottomUp  )  {
			  yStart  =  iH_pic  -  pCtx->mems[index].size_GetTextExtentPoint32.cy  -  pSubtitlesCfg->mems[index].subtitle.pos.yStart;
		  }
		  
		  TextOut(  hDc_mem,  xStart,  yStart,  hint,  lstrlen(  hint  )  );
		  
		  SetBkMode(  hDc_mem,  OPAQUE  );
		  if  (  hFont  )  {
			  SelectObject(  hDc_mem,  hFont  );			 
		  }		

	 }
	
	 iErr  =  0;

errLabel:
	 	
	 return  iErr;
}
