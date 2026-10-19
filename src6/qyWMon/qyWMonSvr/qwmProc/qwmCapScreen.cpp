

#include	<windows.h>            // required for all Windows applications
#include	<windowsx.h>

#include	<stdlib.h>
#include	<ras.h>
#include	<raserror.h>
#include	<lm.h>
#include	<iphlpapi.h>
#include	<tchar.h>

#include	"asrWMon.h"
//  #include	"osversion.h"
#include	"config.h"
#include	"main.h"
#include	"qyRegToolProc.h"


 //  2008/02/17, 似乎这个函数没用了。用usrScript里的功能替代了。
 //
 int  doCapScreen(  QWM_THREADINFO  *  pThreadInfo,  void  *  p1,  void  *  p2  )
{
	 int				iErr					=	-1;
	 QY_W_MON		*	pQwm					=  (  QY_W_MON  *  )pThreadInfo->pParaentParam;
	 unsigned  int		uiTickCnt				=	0;
	 unsigned  int		uiLastTickCnt			=	0;
	 unsigned  int		loopCtrl				=	0;
	 int				iRet;
	 //  unsigned  short	usCapScreenInterval;

	 for  (  ;  loopCtrl  <  1000  ;  Sleep(  2000  ),  loopCtrl  ++  )  {	//  每一千次就退出一次，以防止内存有问题
		  getQwmCfg(  pQwm,  TRUE  );
		  if  (  pQwm->bQuit  ||  pQwm->cfg.ucbStopMon_usrScript  ||  pQwm->cfg.pcRules.pcMon.ucCapScreenCmd  !=  CONST_devCmd_permitted  )  break;
		  uiTickCnt  =  GetTickCount(  );

		  if  (  uiTickCnt  -  uiLastTickCnt  >  (  unsigned  int  )pQwm->cfg.pcRules.pcMon.usCapScreenInterval  *  1000  )  {
			  iRet  =  qwmCapScreen(  pThreadInfo,  0,  0  );
			  if  (  iRet  >  0  )  showQwmSvrStatus(  &pQwm->env,  pQwm->server.ip,  pQwm->server.port,  pQwm->iServiceId,  pQwm->ver,  &pQwm->commEncCtx,  &pQwm->cfg.to,  CONST_qwmSvrStatus_capScreenNotSupported,  0  );
			  if  (  iRet  )  goto  errLabel;	//  qwmCapScreen如果抓屏不成功或者发送不成功都应该退出
			  uiLastTickCnt  =  uiTickCnt;
		  }

	 }
	 iErr  =  0;

errLabel:
	 return  iErr;
}





int  getDib(  void  *  p0,  HDC  hDc,  int  nBt,  BOOL  bCompr  );  //  hDc is memory dc, nBt is color bits per pixel(default = 0), bCompr  is compression(default=true)
int  qwmSndCapScreen(  void  *  p0,  char  *  data,  unsigned  int  dataLen  );
BOOL  myWrite(  TCHAR  *  fileName,  char  *  m_lpBuf,  unsigned  int  m_dwLength  );



 int  qwmCapScreen(  QWM_THREADINFO  *  pThreadInfo,  char *svArg2, BOOL  b256  )
{
	int					iErr		=	-1;
	HDC					hdc			=	NULL;
	HDC					hdc2		=	NULL;
	HBITMAP				bitmap		=	NULL;
	BITMAPINFO			bmpinfo;
	LPVOID				pBits		=	NULL;
	HGDIOBJ				gdiobj		=	NULL;

	traceLogA(  "qwmCapScreen enters"  );
	
	// Create device context
	hdc  =  CreateDC(  _T(  "DISPLAY"  ),  NULL,  NULL,  NULL  );
	if  (  hdc  ==  NULL  ) goto  errLabel;
							
	// Get dimensions
	DWORD dwWidth, dwHeight, dwBPP, dwNumColors;

	dwWidth = GetDeviceCaps(hdc, HORZRES);
	dwHeight = GetDeviceCaps(hdc, VERTRES);
	dwBPP = GetDeviceCaps(hdc, BITSPIXEL);
	if(dwBPP<=8) {
		dwNumColors = GetDeviceCaps(hdc, NUMCOLORS);
		dwNumColors = 256;
	} else {
		dwNumColors = 0;
	}

	if  (  dwBPP  <  8  )  {
		traceLogA(  "不支持16色的屏幕监控"  );  iErr  =  1;  goto  errLabel;
	}

	// Create compatible DC
	hdc2  =  CreateCompatibleDC(  hdc  );
	if  (  hdc2  ==  NULL  )  goto  errLabel;

	// Create bitmap

	bmpinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpinfo.bmiHeader.biWidth = dwWidth;
	bmpinfo.bmiHeader.biHeight = dwHeight;
	bmpinfo.bmiHeader.biPlanes = 1;
	bmpinfo.bmiHeader.biBitCount = (WORD) dwBPP;
	bmpinfo.bmiHeader.biCompression = BI_RGB;
	bmpinfo.bmiHeader.biSizeImage = 0;
	bmpinfo.bmiHeader.biXPelsPerMeter = 0;
	bmpinfo.bmiHeader.biYPelsPerMeter = 0;
	bmpinfo.bmiHeader.biClrUsed = dwNumColors;
	bmpinfo.bmiHeader.biClrImportant = dwNumColors;
	
	bitmap = CreateDIBSection(hdc, &bmpinfo, DIB_PAL_COLORS, &pBits, NULL, 0);
	if  (  bitmap  ==  NULL  )  goto  errLabel;
	
	gdiobj  =  SelectObject(  hdc2, (HGDIOBJ)bitmap);
	if  (  (  gdiobj  ==  NULL  )  ||  (  gdiobj  ==  (void *)GDI_ERROR  )  )  goto  errLabel;
	
	if  (  !BitBlt(hdc2, 0,0, dwWidth, dwHeight, hdc, 0,0, SRCCOPY  )  )  {
		traceLogA(  "qwmCapScreen:  BitBlt failed"  );  goto  errLabel;
	}

	//  hDc is memory dc, nBt is color bits per pixel(default = 0), bCompr  is compression(default=true)
	//  if  (  getDib(  pThreadInfo,  hdc2,  4,  TRUE  )  )  goto  errLabel;
	if  (  getDib(  pThreadInfo,  hdc2,  (  b256  ?  8  :  4  ),  TRUE  )  )  goto  errLabel;


	iErr  =  0;


errLabel:  // Clean up
		

	if  (  (  gdiobj  !=  NULL  )  &&  (  gdiobj  !=  (void *)GDI_ERROR  )  )  SelectObject(  hdc2,  gdiobj  );
	if  (  bitmap  )  DeleteObject(  bitmap  ); 
	if  (  hdc2  )  DeleteDC(  hdc2  );
	if  (  hdc  )  DeleteDC(  hdc  );
	
	traceLogA(  "qwmCapScreen leaves %s",  iErr  ?  "失败"  :  "成功"  );

	return  iErr;
}


	 HANDLE					m_hDib			=		NULL;
	 char				*	m_lpBuf			=		NULL;
	 DWORD					m_dwLength		=		0;
	 int					m_nBits			=		0;
	 LPBITMAPFILEHEADER		m_lpBMFH		=		NULL;
	 LPBITMAPINFOHEADER		m_lpBMIH		=		NULL;
	 LPBITMAPINFO			m_lpBMI			=		NULL;
	 LPSTR					m_lpData		=		NULL;

 BOOL  myAllocateMemory(  BOOL  bRealloc  )	//  bRealloc default =  FALSE
{
	 BOOL  bRet  =  FALSE;

	 if  (  bRealloc  )  {
		 HANDLE		tmph	=	NULL;
		 GlobalUnlock(  m_hDib  );
		 tmph  =  (  char  *  )GlobalReAlloc(  m_hDib,  m_dwLength,  GHND  );
		 if  (  !tmph  )  goto  errLabel;

		 m_hDib  =  tmph;

		 if  (  !(  m_lpBuf  =  (  char  *  )GlobalLock(  m_hDib  )  )  )  goto  errLabel;

		}
	 else  {
		   if  (  !(  m_hDib  =  GlobalAlloc(  GHND,  m_dwLength  )  )  )  goto  errLabel;
		   if  (  !(  m_lpBuf  =  (  char  *  )GlobalLock(  m_hDib  )  )  )  goto  errLabel;
	 }
	 m_lpBMFH  =  (  LPBITMAPFILEHEADER  )m_lpBuf;
	 m_lpBMIH  =  (  LPBITMAPINFOHEADER  )(  m_lpBuf  +  sizeof(  BITMAPFILEHEADER  )  );
	 m_lpBMI  =  (  LPBITMAPINFO  )m_lpBMIH;
	 
	 bRet  =  TRUE;
errLabel:
	 
	 if  (  !bRet  )  {
		 if  (  m_lpBuf  )  {  GlobalUnlock(  m_hDib  );  m_lpBuf  =  NULL;  }
		 if  (  m_hDib  )  {  GlobalFree(  m_hDib  );  m_hDib  =  NULL;  }
	 }
	 
	 if  (  !m_lpBuf  )  {
		 m_dwLength  =  0;
		 m_nBits  =  0;
	 }

	 return  bRet;

}

 int  getDib(  void  *  p0,  HDC  hDc,  int  nBt,  BOOL  bCompr  )  //  hDc is memory dc, nBt is color bits per pixel(default = 0), bCompr  is compression(default=true)
{
	 int					iErr			=		-1;
	 //
	 BITMAP			bm;
	 int			nPaletteSize;
	 HBITMAP		hEmptyBitmap			=	NULL;
	 HBITMAP		hBitmap					=	NULL;	


	 traceLogA(  "getDib enters"  );

	 {	//  2007/02/03, 注意这里的全局变量的复位，否则，中间运行时容易出错
		 m_hDib			=		NULL;
		 m_lpBuf		=		NULL;
		 m_dwLength		=		0;
		 m_nBits		=		0;
		 m_lpBMFH		=		NULL;
		 m_lpBMIH		=		NULL;
		 m_lpBMI		=		NULL;
		 m_lpData		=		NULL;
	 }

	 if  (  !(  hEmptyBitmap  =  CreateCompatibleBitmap(  hDc,  GetDeviceCaps(hDc, HORZRES),  GetDeviceCaps(hDc, VERTRES)  )  )  )  {
		 qyDisplayLastError(  ""  );  goto  errLabel;
	 }
	 if  (  !(  hBitmap  =  (  HBITMAP  )SelectObject(  hDc,  hEmptyBitmap  )  )  )  goto  errLabel;
	 if  (  !GetObject(  hBitmap,  sizeof(  bm  ),  &bm  )  )  goto  errLabel;

	 if  (  (  nBt  ==  1  )  ||  (  nBt  ==  4  )  ||  (  nBt  ==  8  )  ||  (  nBt  ==  24  )  )  {
		 m_nBits  =  nBt;
		}
	 else  {	//  nBt  ==  0
		   m_nBits  =  bm.bmPlanes  *  bm.bmBitsPixel;	//  color bits per pixel
	 }
	 if  (  m_nBits  ==  1  )  {
		 nPaletteSize  =  2;
		}
	 else  {
			if  (  m_nBits  ==  4  )  {
				nPaletteSize  =  16;
				}
			else  {
				  if  (  m_nBits  ==  8  )  {
					  nPaletteSize  =  256;
					}
				  else  {
						nPaletteSize  =  0;		//  no palette for 24-bits display
				  }		
			}
	 }
	 // fills out row to 4-byte boundary
	 DWORD  dwBytes;
	 dwBytes  =  (  (  DWORD  )bm.bmWidth  *  m_nBits  )  /  32;
	 if  (  (  (  DWORD  )bm.bmWidth  *  m_nBits  )  %  32  )  {
		 dwBytes  ++  ;
	 }
	 dwBytes  *=  4;


	 m_dwLength  =  sizeof(  BITMAPFILEHEADER  )  +  sizeof(  BITMAPINFOHEADER  )  +  sizeof(  RGBQUAD  )  *  nPaletteSize;
	 if  (  !myAllocateMemory(  FALSE  )  )  goto  errLabel;

	 m_lpBMIH->biSize  =  sizeof(  BITMAPINFOHEADER  );
	 m_lpBMIH->biWidth  =  bm.bmWidth;
	 m_lpBMIH->biHeight  =  bm.bmHeight;
	 m_lpBMIH->biPlanes  =  1;
	 m_lpBMIH->biBitCount  =  m_nBits;
	 if  (  bCompr  &&  (  m_nBits  ==  4  )  )  {
		 m_lpBMIH->biCompression  =  BI_RLE4;
		}
	 else  {
		   if  (  bCompr  &&  (  m_nBits  ==  8  )  )  {
			   m_lpBMIH->biCompression  =  BI_RLE8;
				}
		   else  {
			     m_lpBMIH->biCompression  =  BI_RGB;
		   }
		   
	 }
	 m_lpBMIH->biSizeImage  =  0;
	 m_lpBMIH->biXPelsPerMeter  =  0;
	 m_lpBMIH->biYPelsPerMeter  =  0;
	 m_lpBMIH->biClrUsed  =  0;
	 m_lpBMIH->biClrImportant  =  0;


	 if  (  !GetDIBits(  hDc,  hBitmap,  0,  (  WORD  )bm.bmHeight,  NULL,  m_lpBMI,  DIB_RGB_COLORS  )  )  goto  errLabel;

	 if  (  m_lpBMIH->biSizeImage  ==  0  )  {
		 m_dwLength  +=  dwBytes  *  bm.bmHeight;
		 m_lpBMIH->biCompression  =  BI_RGB;
		}
	 else  {
		   m_dwLength  +=  m_lpBMIH->biSizeImage;
	 }


	 if  (  !myAllocateMemory(  TRUE  )  )  goto  errLabel;

	 m_lpData  =  (  (  LPSTR  )m_lpBMIH  )  +  sizeof(  BITMAPINFOHEADER  )  +  sizeof(  RGBQUAD  )  *  nPaletteSize;
	 m_lpBMFH->bfType  =  0x4d42;	//  'BM'
	 m_lpBMFH->bfSize  =  m_dwLength;
	 m_lpBMFH->bfReserved1  =  0;
	 m_lpBMFH->bfReserved2  =  0;
	 m_lpBMFH->bfOffBits  =  (  char  *  )m_lpData  -  m_lpBuf;

	 if  (  !GetDIBits(  hDc,  hBitmap,  0,  bm.bmHeight,  m_lpData,  m_lpBMI,  DIB_RGB_COLORS  )  )  {
		 m_dwLength  =  0;
	 }

	 
	 #ifdef  __DEBUG__
			 myWrite(  _T(  "c:\\tempbbb\\testDib.bmp"  ),  m_lpBuf,  m_dwLength  );
	 #endif
	 traceLogA(  "这里不能写到文件里去，应该送到管理端来"  );
	 //  把起始地址为m_lpBuf长度为m_dwLength的数据送到管理端来。
	 if  (  qwmSndCapScreen(  p0,  m_lpBuf,  m_dwLength  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:
	
	 if  (  m_lpBuf  )  GlobalUnlock(  m_hDib  );
	 if  (  m_hDib  )  GlobalFree(  m_hDib  );

	 if  (  hBitmap  )  SelectObject(  hDc,  hBitmap  );
	 if  (  hEmptyBitmap  )  DeleteObject(  hEmptyBitmap  );

	 return  iErr;

}


#define		CONST_sizePerSnd_capScreen	16 * 1024

 int  qwmSndCapScreen(  void  *  p0,  char  *  data,  unsigned  int  dataLen  )
{
	 int								iErr				=		-1;
	 QWM_THREADINFO					*	pThreadInfo			=		(  QWM_THREADINFO  *  )p0;
	 QY_W_MON						*	pQwm				=		(  QY_W_MON  *  )pThreadInfo->pParaentParam;
	 QY_SOCK							sock;
	 QWM_SESSION						session;
	 BOOL								bSessionOpen		=		FALSE;
	 QY_COMM_RESP						tmpResp;
	 QNM_CMDPARAM_sndCapScreen			cmdParam;
	 QWM_MACS_INFO						macsInfo;
	 unsigned  int						len;

	 traceLogA(  "qwmSndCapScreen enters."  );

	 clearQySock(  &sock  );
	 memset(  &session,  0,  sizeof(  session  )  );

	 memset(  &macsInfo,  0,  sizeof(  macsInfo  )  );
	 getQwmMacs(  &pQwm->env,  &macsInfo  );
	 
	 if  (  qwmOpenSession(  pQwm,  &session,  &sock  )  )  goto  errLabel;
	 bSessionOpen  =  TRUE;
	 if  (  !isRcOk(  session.comm.usLastRespCode_i  )  )  goto  errLabel;

	 memset(  &cmdParam,  0,  sizeof(  cmdParam  )  );
	 cmdParam.uiFileSize			=	dataLen;
	 cmdParam.uiSizePerSnd			=	CONST_sizePerSnd_capScreen;	
	 cmdParam.uiCurSessionId		=	pQwm->dwCurSessionId;
	 cmdParam.uiActiveSessionId		=	pQwm->dwActiveSessionId;	
	 MACRO_htonl(  cmdParam.uiFileSize  );
	 MACRO_htonl(  cmdParam.uiSizePerSnd  );
	 MACRO_htonl(  cmdParam.uiCurSessionId  );
	 MACRO_htonl(  cmdParam.uiActiveSessionId  );
	 if  (  pQwm->wUsrName[0]  )  {
		 WCHAR	wBuf[mycountof(  cmdParam.wUsrDomainInfo  )]	=	L"";
		 //
		 _snwprintf(  wBuf,  mycountof(  wBuf  ),  L"%s@%s",  pQwm->wUsrName,  pQwm->wDomainName  );
		 myWChar2Utf8(  wBuf,  (  char  *  )cmdParam.wUsrDomainInfo,  sizeof(  cmdParam.wUsrDomainInfo  )  );
	 }
	 
	 if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_sndCapScreen,  (  char  *  )&cmdParam,  sizeof(  cmdParam  )  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  NULL,  0  )  )  goto  errLabel;
	 
	 for  (  ;  dataLen;  )  {
		 len  =  dataLen  >=  CONST_sizePerSnd_capScreen  ?  CONST_sizePerSnd_capScreen  :  dataLen;
		 if  (  qySend(  &sock,  data,  len,  pQwm->cfg.to.iWrite  )  )  goto  errLabel;
		 if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  NULL,  0  )  )  goto  errLabel;
	 
		 data  +=  len;
		 dataLen  -=  len;
	 }

	 iErr  =  0;

errLabel:

	 if  (  bSessionOpen  )  qnmCloseSession(  &session.comm,  &sock,  &pQwm->cfg.to  );

	 traceLogA(  "qwmSndCapScreen leaves %s",  iErr  ?  "失败"  :  "成功"  );
	 
	 return  iErr;

}


 BOOL  myWrite(  TCHAR  *  fileName,  char  *  m_lpBuf,  unsigned  int  m_dwLength  )
{
	BOOL	bRet	=	FALSE;
	HANDLE	hfile	=	NULL;
	DWORD dwBytes;
	

	hfile=CreateFile(fileName,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hfile==INVALID_HANDLE_VALUE) goto  errLabel;


	WriteFile(hfile,m_lpBuf,m_dwLength,&dwBytes,NULL);


	bRet  =  TRUE;
errLabel:
	if  (  hfile  &&  hfile  !=  INVALID_HANDLE_VALUE  )  CloseHandle(hfile);
	return  bRet;
}



