// qmVmrHelp.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include <tchar.h>
#include <dshow.h>
#include <shellapi.h>
#include <commctrl.h>
#include <commdlg.h>
#include <stdio.h>


#include	<winsock2.h>
#include	<windows.h>
#include	<stddef.h>
#include	<assert.h>
#include	<tchar.h>
#ifndef  __WINCE__
	#include	<vfw.h>
#else
	#ifdef  __TEST__
		#include	<vfw.h>
	#endif

	#include	<mmreg.h>
	#include	<MSAcm.h>
#endif
#include	<Wincrypt.h>



#include <d3d9.h>
#include <vmr9.h>

#include	<Mediaobj.h>

#include <Dmo.h>


#include "smartptr.h"

#include	"initGuid.h"
#include	"qySampleGrabberPublic.h"
#include	"qyCommon.h"

#include	"qysyncCommproc.h"
#include	"genericqueue.h"
#include	"qyq2.h"

#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qmOpenCommon.h"
#include	"qyMsgFunc.h"

#include	"qnmCommProc_mis.h"


#include	"qmcVmrProc.h"

/////////////////////////

#define WM_GRAPHNOTIFY  WM_USER+13


/////////////////////


// Macros
//
#define SAFE_RELEASE(x) { if (x) x->Release(); x = NULL; }

#define JIF(x) if (FAILED(hr=(x))) \
    {Msg(TEXT("FAILED(hr=0x%x) in ") TEXT(#x) TEXT("\n\0"), hr); return hr;}

#define LIF(x) if (FAILED(hr=(x))) \
    {Msg(TEXT("FAILED(hr=0x%x) in ") TEXT(#x) TEXT("\n\0"), hr);}

//
// Resource constants
//
#define IDI_WINDOWLESS                  100
#define IDR_MENU                        101
#define IDD_ABOUTBOX                    200
#define ID_FILE_OPENCLIP                40001
#define ID_FILE_EXIT                    40002
#define ID_FILE_PAUSE                   40003
#define ID_FILE_STOP                    40004
#define ID_FILE_CLOSE                   40005
#define ID_FILE_MUTE                    40006
#define ID_FILE_FULLSCREEN              40007
#define ID_FILE_SIZE_NORMAL             40008
#define ID_FILE_SIZE_HALF               40009
#define ID_FILE_SIZE_DOUBLE             40010
#define ID_FILE_SIZE_QUARTER            40011
#define ID_FILE_SIZE_THREEQUARTER       40012
#define ID_HELP_ABOUT                   40014
#define ID_RATE_INCREASE                40020
#define ID_RATE_DECREASE                40021
#define ID_RATE_NORMAL                  40022
#define ID_RATE_DOUBLE                  40023
#define ID_RATE_HALF                    40024
#define ID_SINGLE_STEP                  40025
#define ID_CAPTURE_IMAGE				40030
#define ID_DISPLAY_IMAGE				40031


const int AUDIO=1, VIDEO=2; // Used for enabling playback menu items

 typedef  struct  __qmcFilterGraph_vmr_t		{


				 //
				 // Global data
				 //
				 HWND							ghApp;
				 HMENU							ghMenu;
				 HINSTANCE						ghInst;
				 TCHAR							g_szFileName[MAX_PATH];
				 BOOL							g_bAudioOnly;
				 //  LONG						g_lVolume=VOLUME_FULL;
				 DWORD							g_dwGraphRegister;
				 //  PLAYSTATE					g_psCurrent=Stopped;
				 double							g_PlaybackRate;
				 RECT							g_rcDest;

				 // DirectShow interfaces
				 IGraphBuilder			*		pGB;
				 IMediaControl			*		pMC;
				 IMediaEventEx			*		pME;
				 IBasicAudio			*		pBA;
				 IMediaSeeking			*		pMS;
				 IMediaPosition			*		pMP;
				 IVideoFrameStep		*		pFS;

				 // VMR9 interfaces
				 IVMRWindowlessControl9 *		pWC;

				 //
				 BOOL							bQuit;
				 QY_Q2						*	pQ2;
				 BOOL							bQInited;
	
				 unsigned  int					uiBufSize_pPkt;
				 char						*	pPkt;

}		 QMC_filterGraph_vmr;




void Msg(TCHAR *szFormat, ...)
{
    TCHAR szBuffer[1024];  // Large buffer for long filenames or URLs
    const size_t NUMCHARS = sizeof(szBuffer) / sizeof(szBuffer[0]);
    const int LASTCHAR = NUMCHARS - 1;

    // Format the input string
    va_list pArgs;
    va_start(pArgs, szFormat);

    // Use a bounded buffer size to prevent buffer overruns.  Limit count to
    // character size minus one to allow for a NULL terminating character.
    (void)StringCchVPrintf(szBuffer, NUMCHARS - 1, szFormat, pArgs);
    va_end(pArgs);

    // Ensure that the formatted string is NULL-terminated
    szBuffer[LASTCHAR] = TEXT('\0');

    // Display a message box with the formatted string
    MessageBox(NULL, szBuffer, TEXT("Windowless Sample"), MB_OK);
}

HRESULT InitializeWindowlessVMR(  QMC_filterGraph_vmr * p,  IBaseFilter **ppVmr9)
{
    IBaseFilter* pVmr = NULL;

    if (!ppVmr9)
        return E_POINTER;
    *ppVmr9 = NULL;

    // Create the VMR and add it to the filter graph.
    HRESULT hr = CoCreateInstance(CLSID_VideoMixingRenderer9, NULL,
                     CLSCTX_INPROC, IID_IBaseFilter, (void**)&pVmr);
    if (SUCCEEDED(hr))
    {
        hr = p->pGB->AddFilter(pVmr, L"Video Mixing Renderer 9");
        if (SUCCEEDED(hr))
        {
            // Set the rendering mode and number of streams
            SmartPtr <IVMRFilterConfig9> pConfig;

            JIF(pVmr->QueryInterface(IID_IVMRFilterConfig9, (void**)&pConfig));
            JIF(pConfig->SetRenderingMode(VMR9Mode_Windowless));

            hr = pVmr->QueryInterface(IID_IVMRWindowlessControl9, (void**)&p->pWC);
            if( SUCCEEDED(hr))
            {
                JIF(p->pWC->SetVideoClippingWindow(p->ghApp));
                JIF(p->pWC->SetBorderColor(RGB(0,0,0)));
            }
        }

        // Don't release the pVmr interface because we are copying it into
        // the caller's ppVmr9 pointer
        *ppVmr9 = pVmr;
    }

    return hr;
}


BOOL IsWindowsMediaFile(WCHAR *lpszFile)
{
    TCHAR szFilename[MAX_PATH];

    // Copy the file name to a local string and convert to lowercase
    (void)StringCchCopy(szFilename,NUMELMS(szFilename), lpszFile);
    szFilename[MAX_PATH-1] = 0;
    _wcslwr_s(szFilename);

    if (wcsstr(szFilename, TEXT(".asf")) ||
        wcsstr(szFilename, TEXT(".wma")) ||
        wcsstr(szFilename, TEXT(".wmv")))
        return TRUE;
    else
        return FALSE;
}

HRESULT GetUnconnectedPin(
    IBaseFilter *pFilter,   // Pointer to the filter.
    PIN_DIRECTION PinDir,   // Direction of the pin to find.
    IPin **ppPin)           // Receives a pointer to the pin.
{
    IEnumPins *pEnum = 0;
    IPin *pPin = 0;

    if (!ppPin)
        return E_POINTER;
    *ppPin = 0;

    // Get a pin enumerator
    HRESULT hr = pFilter->EnumPins(&pEnum);
    if (FAILED(hr))
        return hr;

    // Look for the first unconnected pin
    while (pEnum->Next(1, &pPin, NULL) == S_OK)
    {
        PIN_DIRECTION ThisPinDir;

        pPin->QueryDirection(&ThisPinDir);
        if (ThisPinDir == PinDir)
        {
            IPin *pTmp = 0;

            hr = pPin->ConnectedTo(&pTmp);
            if (SUCCEEDED(hr))  // Already connected, not the pin we want.
            {
                pTmp->Release();
            }
            else  // Unconnected, this is the pin we want.
            {
                pEnum->Release();
                *ppPin = pPin;
                return S_OK;
            }
        }
        pPin->Release();
    }

    // Release the enumerator
    pEnum->Release();

    // Did not find a matching pin
    return E_FAIL;
}


#ifdef  __DEBUG__
HRESULT RenderFileToVMR9(IGraphBuilder *pGB, WCHAR *wFileName,
                         IBaseFilter *pRenderer, BOOL bRenderAudio=TRUE)
{
    HRESULT hr=S_OK;
    SmartPtr <IPin> pOutputPin;
    SmartPtr <IBaseFilter> pSource;
    SmartPtr <IBaseFilter> pAudioRenderer;
    SmartPtr <IFilterGraph2> pFG;

    // Add a file source filter for this media file
    if (!IsWindowsMediaFile(wFileName))
    {
        // Add the source filter to the graph
        if (FAILED(hr = pGB->AddSourceFilter(wFileName, L"SOURCE", &pSource)))
        {
            TCHAR szMsg[MAX_PATH + 128];

            hr = StringCchPrintf(szMsg, NUMELMS(szMsg), TEXT("Failed to add the source filter to the graph!  hr=0x%x\r\n\r\n")
                     TEXT("Filename: %s\0"), hr, wFileName);
            MessageBox(NULL, szMsg, TEXT("Failed to render file to VMR9"), MB_OK | MB_ICONERROR);

            return hr;
        }

        // Get the interface for the first unconnected output pin
        JIF(GetUnconnectedPin(pSource, PINDIR_OUTPUT, &pOutputPin));
    }
    else
    {
        MessageBox(NULL, TEXT("Windows Media files (ASF,WMA,WMV) are not supported by this application.\r\n\r\n")
                   TEXT("For a full example of Windows Media support using the\r\n")
                   TEXT("DirectShow WM ASF Reader filter and implementing a key provider\r\n")
                   TEXT("for Windows Media content, refer to the following SDK samples:\r\n\r\n")
                   TEXT("\t- ASFCopy\t- AudioBox\r\n\t- Jukebox  \t- PlayWndASF\r\n\r\n")
                   TEXT("Each of the listed samples provides the necessary extra code\r\n")
                   TEXT("and links with the required Windows Media libraries.\0"),
                   TEXT("Windows Media files are not supported"), MB_OK);
        return E_FAIL;
    }

    // Render audio if requested (defaults to TRUE)
    if (bRenderAudio)
    {
        // Because we will be rendering with the RENDERTOEXISTINGRENDERERS flag,
        // we need to create an audio renderer and add it to the graph.
        // Create an instance of the DirectSound renderer (for each media file).
        //
        // Note that if the system has no sound card (or if the card is disabled),
        // then creating the DirectShow renderer will fail.  In that case,
        // handle the failure quietly.
        if (SUCCEEDED(CoCreateInstance(CLSID_DSoundRender, NULL, CLSCTX_INPROC_SERVER,
                                       IID_IBaseFilter, (void **)&pAudioRenderer)))
        {
            // The audio renderer was successfully created, so add it to the graph
            JIF(pGB->AddFilter(pAudioRenderer, L"Audio Renderer"));
        }
    }

    // Get an IFilterGraph2 interface to assist in building the
    // multifile graph with the non-default VMR9 renderer
    JIF(pGB->QueryInterface(IID_IFilterGraph2, (void **)&pFG));

    // Render the output pin, using the VMR9 as the specified renderer.  This is
    // necessary in case the GraphBuilder needs to insert a Color Space convertor,
    // or if multiple filters insist on using multiple allocators.
    // The audio renderer will also be used, if the media file contains audio.
    JIF(pFG->RenderEx(pOutputPin, AM_RENDEREX_RENDERTOEXISTINGRENDERERS, NULL));

    // If this media file does not contain an audio stream, then the
    // audio renderer that we created will be unconnected.  If left in the
    // graph, it could interfere with rate changes and timing.
    // Therefore, if the audio renderer is unconnected, remove it from the graph.
    if (pAudioRenderer != NULL)
    {
        IPin *pUnconnectedPin=0;

        // Is the audio renderer's input pin connected?
        HRESULT hrPin = GetUnconnectedPin(pAudioRenderer, PINDIR_INPUT, &pUnconnectedPin);

        // If there is an unconnected pin, then remove the unused filter
        if (SUCCEEDED(hrPin) && (pUnconnectedPin != NULL))
        {
            // Release the returned IPin interface
            pUnconnectedPin->Release();

            // Remove the audio renderer from the graph
            hrPin = pGB->RemoveFilter(pAudioRenderer);
        }
    }

    return hr;
}
#endif


#ifdef  __DEBUG__

 void  clean_MIS_MSG_procVideo_qmc_vmr(  MIS_MSG_procVideo_qmc  *  p,  LPCTSTR  hint  )
 {
	 clean_MIS_MSG_procVideo_qmc(  p  );
 }
#else

	#define	clean_MIS_MSG_procVideo_qmc_vmr		clean_MIS_MSG_procVideo_qmc

#endif

HRESULT RenderVideoToVMR9(DMO_info_vmr  *  pDmoInfo,						  
						  IGraphBuilder *pGB, 
						  BITMAPINFOHEADER  &bih_in,  
						  GENERIC_Q_CFG	*	pQCfg,
						  RW_lock_param  *  pRwLockParam  )
{
    HRESULT hr=S_OK;
    SmartPtr <IPin> pOutputPin;
    SmartPtr <IBaseFilter> pSource;
    SmartPtr <IBaseFilter> pAudioRenderer;
    SmartPtr <IFilterGraph2> pFG;

	DMO_MEDIA_TYPE			mIn;
	 
	memset(  &mIn,  0, sizeof(  mIn  )  );

	GUID					clsid_mInSubType;
	 
	clsid_mInSubType  =  MEDIASUBTYPE_RGB24;

	QMC_filterGraph_vmr  *  pVmr	=	(  QMC_filterGraph_vmr  *  )pDmoInfo->pDmo;

	hr  =  MoInitMediaType(  &mIn,  sizeof(  VIDEOINFOHEADER  )  +  bih_in.biSize  -  sizeof(  BITMAPINFOHEADER  )  );
	if  (  FAILED(  hr  )  )  goto  errLabel;
	if  (  mIn.cbFormat  )  memset(  mIn.pbFormat,  0,  mIn.cbFormat  );

	mIn.majortype  =  MEDIATYPE_Video;
	mIn.subtype  =  clsid_mInSubType;
	mIn.formattype  =  FORMAT_VideoInfo;	
	VIDEOINFOHEADER  *  pViho;	pViho  =  (  VIDEOINFOHEADER  *  )mIn.pbFormat;
	memcpy(  &pViho->bmiHeader,  &bih_in,  bih_in.biSize  );

	//
	pDmoInfo->cbInputBuffer  =  sizeof(  MIS_MSG_procVideo_qmc  );
	pDmoInfo->cbOutputBuffer  =  sizeof(  MIS_MSG_procVideo_qmc  );

	//
	QMC_filterGraph_vmr  *  pDmo  =  pVmr;

	//
	pDmo->pQ2  =  (  QY_Q2  *  )malloc(  sizeof(  QY_Q2  )  );
	if  (  !pDmo->pQ2  )  goto  errLabel;
	memset(  pDmo->pQ2,  0,  sizeof(  QY_Q2  )  );


	GENERIC_Q_CFG	&	tmpCfg  =  *pQCfg;

#if  0
	//
	memcpy(  &tmpCfg,  &pProcInfo->cfg.vCamQ,  sizeof(  tmpCfg  )  );
	long  tn;	getuiNextTranNo(  0,  0,  &tn  );
	_sntprintf(  tmpCfg.name,  mycountof(  tmpCfg.name  ),  _T(  "%s%d"  ),  tmpCfg.name,  tn  );
	_sntprintf(  tmpCfg.mutexName_prefix,  mycountof(  tmpCfg.mutexName_prefix  ),  _T(  "%s%d"  ),  tmpCfg.mutexName_prefix,  tn  );
#endif

	if  (  initQyQ2(  &tmpCfg,  pRwLockParam,  mycountof(  pDmo->pQ2->hEvents  ),  0,  mallocMemory,  malloc,  0,  0,  freeMemory,  free,  (  PF_qElemRemove  )clean_MIS_MSG_procVideo_qmc_vmr,  pDmo->pQ2  )  )  goto  errLabel;
	pDmo->bQInited  =  TRUE;


	//
	pDmo->uiBufSize_pPkt  =  pDmoInfo->cbInputBuffer;
	pDmo->pPkt  =  (  char  *  )malloc(  pDmo->uiBufSize_pPkt  );
	if  (  !pDmo->pPkt  )  goto  errLabel;
	memset(  pDmo->pPkt,  0,  pDmo->uiBufSize_pPkt  );


    // Add a file source filter for this media file
    
#if  0

		// Add the source filter to the graph
        if (FAILED(hr = pGB->AddSourceFilter(wFileName, L"SOURCE", &pSource)))
        {
            TCHAR szMsg[MAX_PATH + 128];

            hr = StringCchPrintf(szMsg, NUMELMS(szMsg), TEXT("Failed to add the source filter to the graph!  hr=0x%x\r\n\r\n")
                     TEXT("Filename: %s\0"), hr, wFileName);
            MessageBox(NULL, szMsg, TEXT("Failed to render file to VMR9"), MB_OK | MB_ICONERROR);

            return hr;
        }

#else


	PARAM_vCam	param;
	memset(  &param,  0,  sizeof(  param  )  );
	param.pAmMediaType  =  &mIn;


	param.uiBufSize_pPkt  =  pVmr->uiBufSize_pPkt;
	param.bPkt_MIS_MSG_procVideo_qmc  =  TRUE;
				 
	param.pDmoInfo  =  pDmoInfo;

	param.pbQuit  =  &pVmr->bQuit;
	param.pQ2  =  pVmr->pQ2;
	param.pf_q2GetMsg  =  q2GetMsg;

	//  param.ucbPrint_v  =  pProcInfo->cfg.debugStatusInfo.ucbPrint_v_in;		//  2010/06/25

	if  (  getNewFilter(  CLSID_VCam_is,  &param,  (  void  **  )&pSource  )  )  goto  errLabel;
	hr  =  pGB->AddFilter(  pSource,  _T(  "VCam"  )  );
	if  (  FAILED(  hr  )  )  goto  errLabel;

#endif

	// Get the interface for the first unconnected output pin
	hr  =  GetUnconnectedPin(pSource, PINDIR_OUTPUT, &pOutputPin);
	if  (  FAILED(  hr  )  )  goto  errLabel;
    
   


    // Get an IFilterGraph2 interface to assist in building the
    // multifile graph with the non-default VMR9 renderer
	hr  =  pGB->QueryInterface(IID_IFilterGraph2, (void **)&pFG);
	if  (  FAILED(  hr  )  )  goto  errLabel;

    // Render the output pin, using the VMR9 as the specified renderer.  This is
    // necessary in case the GraphBuilder needs to insert a Color Space convertor,
    // or if multiple filters insist on using multiple allocators.
    // The audio renderer will also be used, if the media file contains audio.
	hr  =  pFG->RenderEx(pOutputPin, AM_RENDEREX_RENDERTOEXISTINGRENDERERS, NULL);
	if  (  FAILED(  hr  )  )  goto  errLabel;

#ifdef  __DEBUG__
		//  myDumpGraph(  pGB,  6  );  
#endif


	//
	IMediaFilter  *  pMf  =  NULL;
	hr  =  pGB->QueryInterface(  IID_IMediaFilter,  (  void  **  )&pMf  );
	if  (  !FAILED(  hr  )  )  {
		hr  =  pMf->SetSyncSource(  NULL  );
		pMf->Release(  );
	}


errLabel:
	
	MoFreeMediaType(  &mIn  );

    return hr;
}

 __declspec(dllexport) int  postToDraw_vmr(  DMO_info_vmr  *  pDmoInfo,  void  *  pMsg,  int  len_pMsg,  BOOL  *  pbRedirected  )
{
	int  iErr  =  -1;
	QMC_filterGraph_vmr  *  pDmo  =  (  QMC_filterGraph_vmr  *  )pDmoInfo->pDmo;


	if  (  q2PostMsgAndTrigger(  pMsg,  len_pMsg,  pDmo->pQ2  )  )  goto  errLabel;
	*pbRedirected  =  TRUE;

	iErr  =  0;

errLabel:

	return  iErr;

}

void CheckVisibility(  QMC_filterGraph_vmr  *  p)
{
    HRESULT hr;

    // Clear the global flag
    p->g_bAudioOnly = FALSE;

    //
    // Because this sample explicitly loads the VMR9 into the filter graph
    // before rendering a file, the IVMRWindowlessControl interface will exist
    // for all properly rendered files.  As a result, we can't depend on the
    // existence of the pWC interface to determine whether the media file has
    // a video component.  Instead, check the width and height values.
    //
    if (p->pWC)
    {
        LONG lWidth=0, lHeight=0;

        hr = p->pWC->GetNativeVideoSize(&lWidth, &lHeight, 0, 0);
        if (hr == E_NOINTERFACE)
        {
            // If this video is encoded with an unsupported codec,
            // we won't see any video, although the audio will work if it is
            // of a supported format.
            p->g_bAudioOnly = TRUE;
        }

        // If this is an audio-only clip, width and height will be 0.
        if ((lWidth == 0) && (lHeight == 0))
            p->g_bAudioOnly = TRUE;
    }
    else
    {
        // No windowless control interface, so assume audio only
        p->g_bAudioOnly = TRUE;
    }

}

HRESULT InitVideoWindow(QMC_filterGraph_vmr  *  p,  int nMultiplier, int nDivider)
{
    LONG lHeight, lWidth;
    HRESULT hr = S_OK;

    if (!p->pWC)
        return S_OK;

    // Read the default video size
    hr = p->pWC->GetNativeVideoSize(&lWidth, &lHeight, NULL, NULL);
    if (hr == E_NOINTERFACE)
        return S_OK;

    //  EnablePlaybackMenu(TRUE, VIDEO);

    // Account for requests of normal, half, or double size
    lWidth  = lWidth  * nMultiplier / nDivider;
    lHeight = lHeight * nMultiplier / nDivider;

    int nTitleHeight  = GetSystemMetrics(SM_CYCAPTION);
    int nBorderWidth  = GetSystemMetrics(SM_CXBORDER);
    int nBorderHeight = GetSystemMetrics(SM_CYBORDER);

#if  0
    // Account for size of title bar and borders for exact match
    // of window client area to default video size
    SetWindowPos(ghApp, NULL, 0, 0, lWidth + 2*nBorderWidth,
                 lHeight + nTitleHeight + 2*nBorderHeight,
                 SWP_NOMOVE | SWP_NOOWNERZORDER);
#endif

	if  (  p->g_rcDest.right  -  p->g_rcDest.left  &&  p->g_rcDest.bottom  -  p->g_rcDest.top  );
	else  GetClientRect(p->ghApp, &p->g_rcDest);

    hr = p->pWC->SetVideoPosition(NULL, &p->g_rcDest);

    return hr;
}


#if  0  //  def  __DEBUG__
HRESULT PlayMovieInWindow(LPTSTR szFile)
{
    HRESULT hr;

    // Check input string
    if (szFile == NULL)
        return E_POINTER;

    // Clear open dialog remnants before calling RenderFile()
    UpdateWindow(ghApp);

    // Get the interface for DirectShow's GraphBuilder
    JIF(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
                         IID_IGraphBuilder, (void **)&pGB));

    if(SUCCEEDED(hr))
    {
        SmartPtr <IBaseFilter> pVmr;

        // Create the Video Mixing Renderer and add it to the graph
        JIF(InitializeWindowlessVMR(&pVmr));

        // Render the file programmatically to use the VMR9 as renderer.
        // We pass a pointer to the VMR9 so that it will be used as the
        // video renderer.  Pass TRUE to create an audio renderer also.
        if (FAILED(hr = RenderFileToVMR9(pGB, szFile, pVmr, TRUE)))
            return hr;

        // QueryInterface for DirectShow interfaces
        JIF(pGB->QueryInterface(IID_IMediaControl, (void **)&pMC));
        JIF(pGB->QueryInterface(IID_IMediaEventEx, (void **)&pME));
        JIF(pGB->QueryInterface(IID_IMediaSeeking, (void **)&pMS));
        JIF(pGB->QueryInterface(IID_IMediaPosition, (void **)&pMP));
        JIF(pGB->QueryInterface(IID_IBasicAudio, (void **)&pBA));

        // Is this an audio-only file (no video component)?
        CheckVisibility();

        // Have the graph signal event via window callbacks for performance
        JIF(pME->SetNotifyWindow((OAHWND)ghApp, WM_GRAPHNOTIFY, 0));

        if (!g_bAudioOnly)
        {
            JIF(InitVideoWindow(1, 1));
            //  GetFrameStepInterface();
        }
        else
        {
            //  JIF(InitPlayerWindow());
            //  EnablePlaybackMenu(TRUE, AUDIO);
        }

        // Complete initialization
        //  CheckSizeMenu(ID_FILE_SIZE_NORMAL);
        ShowWindow(ghApp, SW_SHOWNORMAL);
        UpdateWindow(ghApp);
        SetForegroundWindow(ghApp);
        SetFocus(ghApp);

        g_PlaybackRate = 1.0;
        //  UpdateMainTitle();

#ifdef REGISTER_FILTERGRAPH
        hr = AddGraphToRot(pGB, &g_dwGraphRegister);
        if (FAILED(hr))
        {
            Msg(TEXT("Failed to register filter graph with ROT!  hr=0x%x"), hr);
            g_dwGraphRegister = 0;
        }
#endif

        // Run the graph to play the media file
        JIF(pMC->Run());
        //  g_psCurrent=Running;

        SetFocus(ghApp);
    }

    return hr;
}
#endif


void CloseInterfaces(QMC_filterGraph_vmr  *  p)
{
    HRESULT hr;

    // Disable event callbacks
    if (p->pME)
        hr = p->pME->SetNotifyWindow((OAHWND)NULL, 0, 0);

#ifdef REGISTER_FILTERGRAPH
    if (g_dwGraphRegister)
    {
        RemoveGraphFromRot(g_dwGraphRegister);
        g_dwGraphRegister = 0;
    }
#endif

    // Release and zero DirectShow interfaces
    SAFE_RELEASE(p->pME);
    SAFE_RELEASE(p->pMS);
    SAFE_RELEASE(p->pMP);
    SAFE_RELEASE(p->pMC);
    SAFE_RELEASE(p->pBA);
    SAFE_RELEASE(p->pWC);
    SAFE_RELEASE(p->pFS);
    SAFE_RELEASE(p->pGB);
}


//  这里还有很多没清理的数据，比如q2,pSource的release等。
 __declspec(dllexport) int CloseClip(  DMO_info_vmr  *  pDmoInfo  )
{
    HRESULT hr;

	if  (  !pDmoInfo  ||  !pDmoInfo->pDmo  )  return  0;

	QMC_filterGraph_vmr	*	pDmo	=	(  QMC_filterGraph_vmr  *  )pDmoInfo->pDmo;
	if  (  !pDmo  )  return  -1;
	QMC_filterGraph_vmr  *  p  =  pDmo;


	p->bQuit  =  TRUE;
	if  (  p->pQ2  &&  p->bQInited  )  {
		q2PostMsgAndTrigger(  NULL,  0,  p->pQ2  );
	}

    // Stop media playback
    if(p->pMC)
        hr = p->pMC->Stop();

    // Clear global flags
    //  g_psCurrent = Stopped;
    p->g_bAudioOnly = TRUE;

    // Free DirectShow interfaces
    CloseInterfaces(p);


	//
	MACRO_safeFree(  p->pPkt  );
	if  (  p->pQ2  )  {
		if  (  p->bQInited  )  exitQyQ2(  p->pQ2  );
		free(  p->pQ2  );
	}


    // Clear file name to allow selection of new file with open dialog
    p->g_szFileName[0] = L'\0';

    // No current media state
    //  g_psCurrent = Init;


	if  (  pDmoInfo->pDmo  )  {
		free(  pDmoInfo->pDmo  );  pDmoInfo->pDmo  =  NULL;
	}

	return  0;
}


 __declspec(dllexport) int OpenClip(  HWND  hWnd,  BITMAPINFOHEADER	*  pBih_in,  RECT  rect,  GENERIC_Q_CFG  *  pQCfg,  RW_lock_param  *  pRwLockParam,  DMO_info_vmr  *  pDmoInfo  )
{
	int			iErr	=	-1;
    HRESULT		hr		=  -1;

	if  (  pDmoInfo->pDmo  )  return  -1;


	QMC_filterGraph_vmr	*	pDmo	=	(  QMC_filterGraph_vmr  *  )malloc(  sizeof(  QMC_filterGraph_vmr  )  );
	if  (  !pDmo  )  return  -1;
	memset(  pDmo,  0,  sizeof(  pDmo[0]  )  );
	//
	pDmoInfo->pDmo  =  pDmo;

	//
	pDmo->g_rcDest  =  rect;
	

	//
#if  0
	GUID	kk	=	CLSID_VCam_is;	
	getNewFilter(  kk,  0,  0  );
#endif

    // Reset status variables

#if  0
    g_psCurrent = Stopped;
    g_lVolume = VOLUME_FULL;
#endif

	pDmo->ghApp  =  hWnd;
#ifdef  __DEBUG__
	lstrcpyn(  pDmo->g_szFileName,  _T(  "c:\\tttbbb\\FlickAnimation.avi"  ),  sizeof(  pDmo->g_szFileName  )  /  sizeof(  pDmo->g_szFileName[0]  )  );
#endif

#if  0
    // Start playing the media file
    hr = PlayMovieInWindow(g_szFileName);

#else
	

    // Get the interface for DirectShow's GraphBuilder
    JIF(CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
                         IID_IGraphBuilder, (void **)&pDmo->pGB));

    if(SUCCEEDED(hr))
    {
        SmartPtr <IBaseFilter> pVmr;

        // Create the Video Mixing Renderer and add it to the graph
        JIF(InitializeWindowlessVMR(  pDmo,&pVmr));


        // Render the file programmatically to use the VMR9 as renderer.
        // We pass a pointer to the VMR9 so that it will be used as the
        // video renderer.  Pass TRUE to create an audio renderer also.
        if (FAILED(hr = RenderVideoToVMR9(pDmoInfo,  pDmo->pGB, *pBih_in,  pQCfg,  pRwLockParam  )))
            return hr;

        // QueryInterface for DirectShow interfaces
        JIF(pDmo->pGB->QueryInterface(IID_IMediaControl, (void **)&pDmo->pMC));
        JIF(pDmo->pGB->QueryInterface(IID_IMediaEventEx, (void **)&pDmo->pME));
        JIF(pDmo->pGB->QueryInterface(IID_IMediaSeeking, (void **)&pDmo->pMS));
        JIF(pDmo->pGB->QueryInterface(IID_IMediaPosition, (void **)&pDmo->pMP));
        JIF(pDmo->pGB->QueryInterface(IID_IBasicAudio, (void **)&pDmo->pBA));

        // Is this an audio-only file (no video component)?
        CheckVisibility(pDmo);

        // Have the graph signal event via window callbacks for performance
        JIF(pDmo->pME->SetNotifyWindow((OAHWND)pDmo->ghApp, WM_GRAPHNOTIFY, 0));

        if (pDmo->g_bAudioOnly)  goto  errLabel;

        
		JIF(InitVideoWindow(  pDmo,1, 1));
            //  GetFrameStepInterface();
        
        // Complete initialization
        //  CheckSizeMenu(ID_FILE_SIZE_NORMAL);
#if  0
        ShowWindow(ghApp, SW_SHOWNORMAL);
        UpdateWindow(ghApp);
        SetForegroundWindow(ghApp);
        SetFocus(ghApp);
#endif

        pDmo->g_PlaybackRate = 1.0;
        //  UpdateMainTitle();

#ifdef REGISTER_FILTERGRAPH
        hr = AddGraphToRot(pGB, &g_dwGraphRegister);
        if (FAILED(hr))
        {
            Msg(TEXT("Failed to register filter graph with ROT!  hr=0x%x"), hr);
            g_dwGraphRegister = 0;
        }
#endif

        // Run the graph to play the media file
        JIF(pDmo->pMC->Run());
        //  g_psCurrent=Running;

        //  SetFocus(ghApp);
    }




#endif


	iErr  =  0;

errLabel:

    // If we couldn't play the clip, clean up
	if (  iErr  )  {
        CloseClip(pDmoInfo);
	}

	return  iErr;
}
