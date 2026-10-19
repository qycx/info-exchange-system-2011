

#include	"stdafx.h"

#include	"qyMcMainCommon.h"
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

#include	"qmcDmoPublic.h"

#include	"qmcVideoCapture_dx.h"
#include	"myfourcc.h"

#include	"qyCusResTemp.h"

//  #include	"myresource.h"


#include	"qmcShareMediaFile.h"


 void  checkVisibility(  SHARE_MEDIA_FILE  *  p  )
{
    long lVisible;
    HRESULT hr;

    if ((!p->m_pVW) || (!p->m_pBV))
    {
        // Audio-only files have no video interfaces.  This might also
        // be a file whose video component uses an unknown video codec.
        p->g_bAudioOnly = TRUE;
        return;
    }
    else
    {
        // Clear the global flag
        p->g_bAudioOnly = FALSE;
    }

    hr = p->m_pVW->get_Visible(&lVisible);
    if (FAILED(hr))
    {
        // If this is an audio-only clip, get_Visible() won't work.
        //
        // Also, if this video is encoded with an unsupported codec,
        // we won't see any video, although the audio will work if it is
        // of a supported format.
        //
        if (hr == E_NOINTERFACE)
        {
            p->g_bAudioOnly = TRUE;
        }
        else
        {
            traceLogA(("Failed(%08lx) in pVW->get_Visible()!\r\n"), hr);
        }
    }
}

 BOOL  bAudioOnly(  void  *  pSharedMediaFileParam  )
{
	if  (  !pSharedMediaFileParam  )  return  FALSE;
	SHARE_MEDIA_FILE  *  p  =  (  SHARE_MEDIA_FILE  *  )pSharedMediaFileParam;
	return  p->g_bAudioOnly;
}


 BOOL  bNoAudio(  void  *  pSharedMediaFileParam  )
{
	if  (  !pSharedMediaFileParam  )  return  FALSE;
	SHARE_MEDIA_FILE  *  p  =  (  SHARE_MEDIA_FILE  *  )pSharedMediaFileParam;
	return  p->g_bNoAudio;
}


 int  initShareMediaFile(  LPCTSTR  tFile,  HWND  hWnd_notify,  LONG_PTR lInstanceData,  void  **  ppShareMediaFileParam  )
{
	int						iErr		=		-1;

	HRESULT					hr;
	SHARE_MEDIA_FILE	*	p			=		NULL;
	
	if  (  !tFile  ||  !tFile[0]  )  return  -1;
	if  (  !ppShareMediaFileParam  )  return  -1;
	if  (  *ppShareMediaFileParam  )  return  -1;
	
	traceLogA(  "initShareMediaFile enters"  );

	p  =  (  SHARE_MEDIA_FILE  *  )malloc(  sizeof(  SHARE_MEDIA_FILE  )  );
	if  (  !p  )  goto  errLabel;
	memset(  p,  0,  sizeof(  SHARE_MEDIA_FILE  )  );

	// Get the interface for DirectShow's GraphBuilder
	hr  =  CoCreateInstance(  CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,  IID_IGraphBuilder, (void **)&p->m_pGB  );
	if  (  FAILED(  hr  )  )  goto  errLabel;

	//
#ifndef  __SUPPORT_CUS_sampleGrabber__
	hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER,  IID_IBaseFilter, (void**)&p->video.m_pGrabberFilter); 
	if  (  FAILED(  hr  )  )  goto  errLabel;
#else

		if  (  myGetNewFilter(  g_pEnv,  CLSID_SampleGrabber_is,  0,  (  void  **  )&p->video.m_pGrabberFilter  )  )  goto  errLabel;

#endif
	hr = p->m_pGB->AddFilter(  p->video.m_pGrabberFilter, L"Sample Grabber video"); 
	if  (  FAILED(  hr  )  )  goto  errLabel;
#ifndef  __SUPPORT_CUS_sampleGrabber__
	hr = p->video.m_pGrabberFilter->QueryInterface(  IID_ISampleGrabber, (void**)&p->video.m_pGrabber  ); 
	if  (  FAILED(  hr  )  )  goto  errLabel;
#else
	hr = p->video.m_pGrabberFilter->QueryInterface(  IID_ISampleGrabber_is, (void**)&p->video.m_pGrabber  ); 
	if  (  FAILED(  hr  )  )  goto  errLabel;
#endif

	AM_MEDIA_TYPE mt; 

	ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
	// mt.majortype  =  MEDIATYPE_Audio;
	mt.majortype = MEDIATYPE_Video; 
	//mt.majortype  =  MEDIATYPE_Stream;
	mt.subtype = MEDIASUBTYPE_RGB24; 
	//mt.subtype  =  MEDIASUBTYPE_YUY2;

	hr  =  p->video.m_pGrabber->SetMediaType(&mt); 
	if  (  FAILED(  hr  )  )  goto  errLabel;
		
	p->video.m_pCallBack  =  new  CMySampleGrabberCB;
	if  (  !p->video.m_pCallBack  )  goto  errLabel;

	// Set modes
	p->video.m_pGrabber->SetBufferSamples(FALSE);	// Buffer seems to be no use in callback mode
	p->video.m_pGrabber->SetCallback(  p->video.m_pCallBack,  1  );
			

	//
#ifndef  __SUPPORT_CUS_sampleGrabber__
	hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER,  IID_IBaseFilter, (void**)&p->audio.m_pGrabberFilter); 
	if  (  FAILED(  hr  )  )  goto  errLabel;
#else

	if  (  myGetNewFilter(  g_pEnv,  CLSID_SampleGrabber_is,  0,  (  void  **  )&p->audio.m_pGrabberFilter  )  )  goto  errLabel;

#endif
	hr = p->m_pGB->AddFilter(  p->audio.m_pGrabberFilter, L"Sample Grabber audio"); 
	if  (  FAILED(  hr  )  )  goto  errLabel;
#ifndef  __SUPPORT_CUS_sampleGrabber__
	hr = p->audio.m_pGrabberFilter->QueryInterface(  IID_ISampleGrabber, (void**)&p->audio.m_pGrabber  ); 
	if  (  FAILED(  hr  )  )  goto  errLabel;
#else
	hr = p->audio.m_pGrabberFilter->QueryInterface(  IID_ISampleGrabber_is, (void**)&p->audio.m_pGrabber  ); 
	if  (  FAILED(  hr  )  )  goto  errLabel;
#endif
	
	ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
	mt.majortype  =  MEDIATYPE_Audio;
	mt.subtype = MEDIASUBTYPE_PCM; 

	hr  =  p->audio.m_pGrabber->SetMediaType(&mt); 
	if  (  FAILED(  hr  )  )  goto  errLabel;
		
	p->audio.m_pCallBack  =  new  CMySampleGrabberCB;
	if  (  !p->audio.m_pCallBack  )  goto  errLabel;

	// Set modes
	p->audio.m_pGrabber->SetBufferSamples(FALSE);	// Buffer seems to be no use in callback mode
	p->audio.m_pGrabber->SetCallback(  p->audio.m_pCallBack,  1  );

	//
	qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initShareMediaFile, to RendFile"  )  );
	//
	hr  =  p->m_pGB->RenderFile(  tFile, NULL  );
	if  (  FAILED(  hr  )  )  {
		qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initShareMediaFile, RendFile failed"  )  );
		goto  errLabel;
	}
	qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "initShareMediaFile: RendFile OK"  )  );
	
	//
	lstrcpyn(  p->tFile,  tFile,  mycountof(  p->tFile  )  );


	// QueryInterface for DirectShow interfaces
	hr  =  p->m_pGB->QueryInterface(IID_IMediaControl, (void **)&p->m_pMC);
	hr  =  p->m_pGB->QueryInterface(IID_IMediaEventEx, (void **)&p->m_pME);
	hr  =  p->m_pGB->QueryInterface(IID_IMediaSeeking, (void **)&p->m_pMS);
	hr  =  p->m_pGB->QueryInterface(IID_IMediaPosition, (void **)&p->m_pMP);

	// Query for video interfaces, which may not be relevant for audio files
	hr  =  p->m_pGB->QueryInterface(IID_IVideoWindow, (void **)&p->m_pVW);
	hr  =  p->m_pGB->QueryInterface(IID_IBasicVideo, (void **)&p->m_pBV);

	// Query for audio interfaces, which may not be relevant for video-only files
	hr  =  p->m_pGB->QueryInterface(IID_IBasicAudio, (void **)&p->m_pBA);

	//
	hr  =  p->m_pGB->QueryInterface(__uuidof(IVideoFrameStep), (PVOID *)&p->m_pFS);


	//
	if  (  IsWindow(  hWnd_notify  )  )  {
	    // Have the graph signal event via window callbacks		
		hr = p->m_pME->SetNotifyWindow(  (OAHWND)hWnd_notify, CONST_qyWm_graphNotify_mediaFile, lInstanceData  );
	}

	checkVisibility(  p  );

#ifdef  __DEBUG__
		//  myDumpGraph(  p->m_pGB,  0  );
#endif

	//
	// Get connection information.
	// This must be done after the Graph is created
	// by RenderFile.
	if  (  !p->g_bAudioOnly  )  {
		hr  =  p->video.m_pGrabber->GetConnectedMediaType(&mt);
		if  (  FAILED(  hr  )  )  goto  errLabel;
		else  {
			  traceLogA(  "video.m_pGrabber.formattype %S",  getFormatTypeName(  mt.formattype  )  );
			  myFreeMediaType(  mt  );
		}
	}

	hr  =  p->audio.m_pGrabber->GetConnectedMediaType(  &mt  );
	if  (  FAILED(  hr  )  )  {
		p->g_bNoAudio  =  TRUE;
		traceLogA(  "initShareMediaFile: no audio data"  );
		}
	else  {
		  traceLogA(  "audio.m_pGrabber.formattype %S",  getFormatTypeName(  mt.formattype  )  );
		  myFreeMediaType(  mt  );
	}



	#if  1
		 if  (  !p->g_bAudioOnly  )  {
			 if  (  p->m_pVW  )  {		
				 hr  =  p->m_pVW->put_AutoShow(  OAFALSE  );
				 if  (  FAILED(  hr  )  )  goto  errLabel;
				 hr  =  p->m_pVW->put_Visible(  OAFALSE  );
				 if  (  FAILED(  hr  )  )  goto  errLabel;
			 }
		 }
		 if  (  p->m_pBA  )  {
			 hr  =  p->m_pBA->put_Volume(  -10000  );
			 if  (  FAILED(  hr  )  )  {
				 if  (  !p->g_bNoAudio  )  goto  errLabel;
			 }
		 }
	#endif

    //  2009/04/30
    p->psCurrent  = State_Stopped;

	//
	p->bInited  =  TRUE;

	iErr  =  0;

errLabel:
	
	if  (  iErr  )  exitShareMediaFile(  (  void  **  )&p  );
	if  (  !iErr  )  {
		*ppShareMediaFileParam  =  p;
	}
	
	traceLogA(  "initShareMediaFile leaves with %s",  iErr  ?  "failed"  :  "Ok"  );

	return  iErr;
}

#ifdef  __DEBUG__

#if  0
 // Tear down everything downstream of a given filter
void NukeDownstream(IGraphBuilder  *  pFg,  IBaseFilter *pf)
{
    IPin *pP=0, *pTo=0;
    ULONG u;
    IEnumPins *pins = NULL;
    PIN_INFO pininfo;

    if (!pf)
        return;

    HRESULT hr = pf->EnumPins(&pins);
    pins->Reset();

    while(hr == NOERROR)
    {
        hr = pins->Next(1, &pP, &u);
        if(hr == S_OK && pP)
        {
            pP->ConnectedTo(&pTo);
            if(pTo)
            {
                hr = pTo->QueryPinInfo(&pininfo);
                if(hr == NOERROR)
                {
                    if(pininfo.dir == PINDIR_INPUT)
                    {
                        NukeDownstream(pFg,  pininfo.pFilter);
                        pFg->Disconnect(pTo);
                        pFg->Disconnect(pP);
						
						//
						FILTER_INFO	fi;
						hr  =  pininfo.pFilter->QueryFilterInfo(  &fi  );
						traceLogA(  "NukeDownstream: to removeFilter %S",  fi.achName  );
						//

                        pFg->RemoveFilter(pininfo.pFilter);
                    }
                    pininfo.pFilter->Release();
                }
                pTo->Release();
            }
            pP->Release();
        }
    }

    if(pins)
        pins->Release();
}
#endif


 int  printFilters(  IGraphBuilder  *  p  )
 {
#ifndef  __noMfc__
	 CComPtr<IEnumFilters> pEnum;
	 IBaseFilter  *  pFilter;
  ULONG cFetched;

  traceLogA(  "printFilters enters"  );

  HRESULT hr = p->EnumFilters(&pEnum);
  if (FAILED(hr)) 
  {
    return hr;
  }

    while(pEnum->Next(1, &pFilter, &cFetched) == S_OK)
  {
	  
	  FILTER_INFO	fi;
	  hr  =  pFilter->QueryFilterInfo(  &fi  );
	  traceLogA(  "name %S",  fi.achName  );

	  //  hr  =  p->RemoveFilter(  pFilter  );
	  //  hr  =  pEnum->Reset(  );
	  hr  =  pFilter->Release(  );
  }
 

	traceLogA(  "printFilters leaves"  );

#endif

	 return  0;
 }


#endif


  int  exitShareMediaFile(  void  **  ppShareMediaFileParam  )
{
	HRESULT					hr;
	SHARE_MEDIA_FILE	*	p		=	(  SHARE_MEDIA_FILE  *  )*ppShareMediaFileParam;
	if  (  !p  )  return  -1;

	traceLogA(  "exitShareMediaFile enters"  );

	if  (  p->m_pMC  )  p->m_pMC->Stop();
	if  (  p->m_pVW  )  {
		p->m_pVW->put_Visible(OAFALSE);
		p->m_pVW->put_Owner(NULL);
	}
   if (  p->m_pME  )
        hr = p->m_pME->SetNotifyWindow((OAHWND)NULL, 0, 0);

    // Release and zero DirectShow interfaces
   MACRO_safeRelease(  p->m_pME  );
   MACRO_safeRelease(  p->m_pMS  );
   MACRO_safeRelease(  p->m_pMP  );
   MACRO_safeRelease(  p->m_pMC  );
   MACRO_safeRelease(  p->m_pBA  );
   MACRO_safeRelease(  p->m_pBV  );
   MACRO_safeRelease(  p->m_pVW  );
   MACRO_safeRelease(  p->m_pFS  );
   MACRO_safeRelease(  p->m_pGB  );

#ifdef  __SUPPORT_CUS_sampleGrabber__
   MACRO_safeRelease(  p->m_pWMASFReader  );
#endif

   	MACRO_safeRelease(  p->video.m_pGrabber  );
	MACRO_safeRelease(  p->video.m_pGrabberFilter  );
	if  (  p->video.m_pCallBack  )  {
		MACRO_safeFree(  p->video.m_pCallBack->m_var.pMsgBuf  );
		delete  p->video.m_pCallBack;
	}
	MACRO_safeRelease(  p->video.m_pNullRenderer  );

	MACRO_safeRelease(  p->audio.m_pGrabber  );
	MACRO_safeRelease(  p->audio.m_pGrabberFilter  );
	if  (  p->audio.m_pCallBack  )  {
		MACRO_safeFree(  p->audio.m_pCallBack->m_var.pMsgBuf  );
		delete  p->audio.m_pCallBack;
	}
	MACRO_safeRelease(  p->audio.m_pNullRenderer  );

	free(  p  );

	*ppShareMediaFileParam  =  NULL;

	traceLogA(  "exitShareMediaFile leaves"  );

	return  0;
}



 BOOL  bGetCapturePara_shareMediaFile(  MC_VAR_common  *  pProcInfo,  int  iIndex_capAudio,  int  iIndex_capBmp,  void  *  pShareMediaFile,  WAVEFORMATEX  *  pWf_org,  QY_VIDEO_HEADER  *  pVh_org,  SAMPLE_grabberCb_cache  *  pCache  )
{
	SHARE_MEDIA_FILE				*	p				=	(  SHARE_MEDIA_FILE  *  )pShareMediaFile;
	SAMPLE_grabber_info  *  pA  =  NULL;
	SAMPLE_grabber_info  *  pV  =  NULL;

	if  (  !p->g_bNoAudio  )  pA  =  &p->audio;
	if  (  !p->g_bAudioOnly  )  pV  =  &p->video;
	
	//  return  bGetCapturePara_shareMediaObj(  pProcInfo,  CONST_capType_mediaFile,  iIndex_capAudio,  iIndex_capBmp,  pA,  pV,  pWf_org,  pVh_org,  pCache  );  
	return  bGetCapturePara_shareMediaObj(  pProcInfo,  CONST_capType_mediaFile,  iIndex_capAudio,  0,  pA,  pWf_org,  iIndex_capBmp,  0,  pV,  pVh_org,  pCache  );
}


 //  2011/12/27
 //  BOOL  bGetCapturePara_shareMediaObj(  MC_VAR_common  *  pProcInfo,  unsigned  int  uiCapType,  int  iIndex_capAudio,  int  iIndex_capBmp,  void  *  pSampleGrabberInfo_a,  void  *  pSampleGrabberInfo_v,  WAVEFORMATEX  *  pWf_org,  QY_VIDEO_HEADER  *  pVh_org,  SAMPLE_grabberCb_cache  *  pCache_unused  )
 BOOL  bGetCapturePara_shareMediaObj(  MC_VAR_common  *  pProcInfo,  unsigned  int  uiCapType,  
			int  iIndex_capAudio,  unsigned  int  uiBufSize_pMsgBuf_a,  void  *  pSampleGrabberInfo_a,  WAVEFORMATEX  *  pWf_org,  
			int  iIndex_capBmp,  unsigned  int  uiBufSize_pMsgBuf_v,  void  *  pSampleGrabberInfo_v,  QY_VIDEO_HEADER  *  pVh_org,  
			SAMPLE_grabberCb_cache  *  pCache_unused  )
{
	BOOL								bRet			=	FALSE;
	HRESULT								hr;

	SAMPLE_grabber_info				*	pA				=	(  SAMPLE_grabber_info  *  )pSampleGrabberInfo_a;
	SAMPLE_grabber_info				*	pV				=	(  SAMPLE_grabber_info  *  )pSampleGrabberInfo_v;

	//  SHARE_MEDIA_FILE				*	p				=	(  SHARE_MEDIA_FILE  *  )pShareMediaFile;
	DMO_MEDIA_TYPE						mt;
	BOOL								bMtGot			=	FALSE;

	if  (  !pProcInfo  )  return  FALSE;
	if  (  pA  )  {
		if  (  !pA->m_pGrabber  ||  !pWf_org  )  return  FALSE;
	}
	if  (  pV  )  {
		if  (  !pV->m_pGrabber  ||  !pVh_org  )  return  FALSE;
	}

	//  if  (  !p->g_bAudioOnly  )  
	if  (  pV  )
	{
		hr  =  pV->m_pGrabber->GetConnectedMediaType(  &mt  );
		if  (  FAILED(  hr  )  )  goto  errLabel;
		bMtGot  =  TRUE;

		if  (  mt.majortype  !=  MEDIATYPE_Video  )  goto  errLabel;
		traceLogA(  "bGetCapturePara_shareMediaFile: video.mediaSubtype: %S",  getMediaSubtypeName(  mt.subtype  )  );

		if  (  mt.formattype  !=  FORMAT_VideoInfo  ) goto  errLabel;
		if  (  NULL  ==  mt.pbFormat  ||  mt.cbFormat  <  sizeof(  VIDEOINFOHEADER  )  )  goto  errLabel;

		VIDEOINFO *pVih = (VIDEOINFO *)mt.pbFormat;
		memcpy(  &pVh_org->bih,  &pVih->bmiHeader,  sizeof(  pVh_org->bih  )  );

		myFreeMediaType(  mt  );  bMtGot  =  FALSE;

		//
		pV->m_pCallBack->m_var.pProcInfo  =  pProcInfo;
		pV->m_pCallBack->m_var.uiCapType  =  uiCapType;
		pV->m_pCallBack->m_var.iIndex_capProcInfo  =  iIndex_capBmp;
	}

	//  if  (  !p->g_bNoAudio  )  
	if  (  pA  )
	{
		//
		hr  =  pA->m_pGrabber->GetConnectedMediaType(  &mt  );
		if  (  FAILED(  hr  )  )  goto  errLabel;
		bMtGot  =  TRUE;

		if  (  mt.majortype  !=  MEDIATYPE_Audio  )  goto  errLabel;
		traceLogA(  "bGetCapturePara_shareMediaFile: audio.mediaSubtype: %S",  getMediaSubtypeName(  mt.subtype  )  );

		if  (  mt.formattype  !=  FORMAT_WaveFormatEx  ) goto  errLabel;
		if  (  NULL  ==  mt.pbFormat  ||  mt.cbFormat  <  sizeof(  WAVEFORMATEX  )  )  goto  errLabel;

		WAVEFORMATEX *pWf = (WAVEFORMATEX *)mt.pbFormat;
		memcpy(  pWf_org,  pWf,  sizeof(  pWf_org[0]  )  );

		myFreeMediaType(  mt  );  bMtGot  =  FALSE;

		//
		pA->m_pCallBack->m_var.pProcInfo  =  pProcInfo;
		pA->m_pCallBack->m_var.uiCapType  =  uiCapType;
		pA->m_pCallBack->m_var.iIndex_capProcInfo  =  iIndex_capAudio;
		pA->m_pCallBack->m_var.bAudio  =  TRUE;
		//  2013/03/19
		pA->m_pCallBack->m_var.uiBufSize_pMsgBuf  =  uiBufSize_pMsgBuf_a;
		if  (  pA->m_pCallBack->m_var.uiBufSize_pMsgBuf  )  {
			pA->m_pCallBack->m_var.pMsgBuf  =  malloc(  pA->m_pCallBack->m_var.uiBufSize_pMsgBuf  );
			if  (  !pA->m_pCallBack->m_var.pMsgBuf  )  goto  errLabel;	
		}


		//  2009/12/24
#if  0
		int  nBytes_pkt  =  0;		
		if  (  !(  pWf_org->nAvgBytesPerSec  %  12  )  )  nBytes_pkt  =  pWf_org->nAvgBytesPerSec  /  12;
		else  if  (  !(  pWf_org->nAvgBytesPerSec  %  10  )  )  nBytes_pkt  =  pWf_org->nAvgBytesPerSec  /  10;
		else  if  (  !(  pWf_org->nAvgBytesPerSec  %  8  )  )  nBytes_pkt  =  pWf_org->nAvgBytesPerSec  /  8;
		else  if  (  !(  pWf_org->nAvgBytesPerSec  %  15  )  )  nBytes_pkt  =  pWf_org->nAvgBytesPerSec  /  15;
		else  if  (  !(  pWf_org->nAvgBytesPerSec  %  5  )  )  nBytes_pkt  =  pWf_org->nAvgBytesPerSec  /  5;

		if  (  nBytes_pkt  )  {
			pA->m_pCallBack->m_var.cache.nAvgBytesPerSec  =  pWf_org->nAvgBytesPerSec;
			pA->m_pCallBack->m_var.cache.uiBufSize  =  2  *  pWf_org->nAvgBytesPerSec;	//  2 seconds
			pA->m_pCallBack->m_var.cache.nBytes_pkt  =  nBytes_pkt;
			//
			if  (  pCache  )  memcpy(  pCache,  &pA->m_pCallBack->m_var.cache,  sizeof(  pCache[0]  )  );
		}
#endif
	}

	bRet  =  TRUE;

errLabel:

	if  (  bMtGot  )  myFreeMediaType(  mt  );

	return  bRet;
}




 int  runShareMediaFile(  void  *  pShareMediaFileParam  )
{
	int						iErr	=	-1;
	HRESULT					hr;
	SHARE_MEDIA_FILE	*	p		=	(  SHARE_MEDIA_FILE  *  )pShareMediaFileParam;
	
	if  (  !p  )  return  -1;
	if  (  !p->bInited  )  return  -1;
	if  (  !p->m_pMC  )  return  -1;

	hr  =  p->m_pMC->Run(  );
	if  (  FAILED(  hr  )  )  goto  errLabel;

	// Remember play state
	p->psCurrent  =  State_Running;

	iErr  =  0;
errLabel:
	return  iErr;
}


 int  stopShareMediaFile(  void  *  pShareMediaFileParam  )
{
	int						iErr	=	-1;
	HRESULT					hr;
	SHARE_MEDIA_FILE	*	p		=	(  SHARE_MEDIA_FILE  *  )pShareMediaFileParam;
	
	if  (  !p  )  return  -1;
	if  (  !p->bInited  )  return  -1;

	if  (  p->psCurrent  ==  State_Stopped  )  return  0;

	traceLogA(  "stopShareMediaFile enters"  );

	if  (  p->m_pMC  )  {
		hr  =  p->m_pMC->Stop();
		if  (  FAILED(  hr  )  )  goto  errLabel;
	}

	/*
	if  (  p->m_pMC  )  {
	
		traceLogA(  "stopShareMediaFile: Wait for the stop to propagate to all filters"  );
    	OAFilterState fs;
    	hr = p->m_pMC->GetState(500, &fs);
    	if (FAILED(hr))  {
			traceLogA(("Failed to read graph state!  hr=0x%x\r\n"), hr);
			}
		else  {
			  traceLogA(  "propagated"  );
		}
	}

    // Reset to beginning of media clip
	if  (  p->m_pMS  )  {
		LONGLONG pos=0;
		hr = p->m_pMS->SetPositions(&pos, AM_SEEKING_AbsolutePositioning ,
                           NULL, AM_SEEKING_NoPositioning);
		if (FAILED(hr))  {
			traceLogA(("Failed to seek to beginning of media!  hr=0x%x\r\n"), hr);    
		}
	}

	if  (  p->m_pMC  )  {
		// Display the first frame of the media clip, if it contains video.
		// StopWhenReady() pauses all filters internally (which allows the video
		// renderer to queue and display the first video frame), after which
		// it sets the filters to the stopped state.  This enables easy preview
		// of the video's poster frame.
		hr = p->m_pMC->StopWhenReady();
		if (FAILED(hr))  {
			traceLogA(("Failed in StopWhenReady!  hr=0x%x\r\n"), hr);
		}
	}
	*/


	p->psCurrent  =  State_Stopped;

	iErr  =  0;

errLabel:

	traceLogA(  "stopShareMediaFile leaves with %s",  iErr  ?  "failed"  :  "Ok"  );

	return  iErr;
}


 int  pauseShareMediaFile(  void  *  pShareMediaFileParam  )
{
	int						iErr	=	-1;
	HRESULT					hr		=	S_OK;
	SHARE_MEDIA_FILE	*	p		=	(  SHARE_MEDIA_FILE  *  )pShareMediaFileParam;

	if  (  !p  )  return  -1;
	if  (  !p->bInited  )  return  -1;

    if  (  !p->m_pMC  )  return  -1;

    // Play/pause
    if  (  p->psCurrent  !=  State_Running  )  return  0;

    hr = p->m_pMC->Pause();
    if (FAILED(hr)) goto  errLabel;
	
    // Remember play state
    p->psCurrent = State_Paused;

	iErr  =  0;

errLabel:
    
	return hr;

}

 int  getShareMediaFileState(  void  *  pShareMediaFileParam  )
{
	SHARE_MEDIA_FILE  *  p  =  (  SHARE_MEDIA_FILE  *  )pShareMediaFileParam;
	if  (  !p  )  return  -1;

	return  p->psCurrent;
}


 /*
 int  muteAudio(  void  *  pShareMediaFileParam  )
{
	int						iErr	=	-1;
	SHARE_MEDIA_FILE  *		p		=  (  SHARE_MEDIA_FILE  *  )pShareMediaFileParam;
	if  (  !p  )  return  -1;

    HRESULT hr=S_OK;
    long	lVolume;

    if  (  !p->m_pGB  )  return -1;
	if  (  !p->m_pBA  )  return  -1;

    // Read current volume
    hr = p->m_pBA->get_Volume(&lVolume);
	if (hr == E_NOTIMPL)  {
        // Fail quietly if this is a video-only media file
		goto  errLabel;
    }
    else if (FAILED(hr))  {
			goto  errLabel;
    }

    lVolume = CONST_volume_silence;

    // Set new volume
    hr = p->m_pBA->put_Volume(lVolume);
    if (FAILED(hr))  {
		traceLogA("Failed in pBA->put_Volume!  hr=0x%x\r\n", hr);
		goto  errLabel;
    }

	iErr  =  0;

errLabel:
    return  iErr;
}


  int  resumeAudio(  void  *  pShareMediaFileParam  )
{
	int						iErr	=	-1;
	SHARE_MEDIA_FILE  *		p		=	(  SHARE_MEDIA_FILE  *  )pShareMediaFileParam;
	if  (  !p  )  return  -1;

    HRESULT hr=S_OK;
    long lVolume;

    if (!p->m_pGB)  return  -1;
	if  (  !p->m_pBA  )  return  -1;
	

    // Read current volume
    hr = p->m_pBA->get_Volume(&lVolume);
    if (hr == E_NOTIMPL)  {
        // Fail quietly if this is a video-only media file
		goto  errLabel;
    }
    else if (FAILED(hr))  {
		traceLogA(("Failed in pBA->get_Volume!  hr=0x%x\r\n"), hr);
		goto  errLabel;
    }

    // Set new volume
    lVolume = CONST_volume_full;	
    hr = p->m_pBA->put_Volume(lVolume);
    if (FAILED(hr))  {
		traceLogA(("Failed in pBA->put_Volume!  hr=0x%x\r\n"), hr);
		goto  errLabel;
    }

	iErr  =  0;
errLabel:
    return  iErr;
}
*/

#if  0
 int  handleGraphEvent(  void  *  pProcInfoParam,  int  iIndex_sharedObj  )
{
	int						iErr	=	-1;
	MC_VAR_isCli			*	pProcInfo	=	(  MC_VAR_isCli  *  )pProcInfoParam;
	if  (  !pProcInfo  )  return  -1;
	QY_SHARED_OBJ		*	pSharedObj	=	getSharedObjByIndex(  pProcInfo,  iIndex_sharedObj  );
	if  (  !pSharedObj  )  return  -1;
	CAP_procInfo_bmpU	*	pCapBmp	=	getCapBmpBySth(  pProcInfo,  pSharedObj->iIndex_capBmp,  CONST_capType_mediaFile  );
	if  (  !pCapBmp  )  return  -1;

	SHARE_MEDIA_FILE  *		p		=	(  SHARE_MEDIA_FILE  *  )pSharedObj->pShareMediaFile;
	if  (  !p  )  return  -1;
	
	IMediaEventEx	*		pME		=	p->m_pME;
	IMediaSeeking	*		pMS		=	p->m_pMS;

    LONG evCode;
	LONG_PTR evParam1, evParam2;
    HRESULT hr=S_OK;

    // Since we may have a scenario where we're shutting down the application,
    // but events are still being generated, make sure that the event
    // interface is still valid before using it.  It's possible that
    // the interface could be freed during shutdown but later referenced in
    // this callback before the app completely exits.
    if  (  !pME  ||  !pMS  )  return  -1;
	
    while(SUCCEEDED(pME->GetEvent(&evCode, &evParam1, &evParam2, 0)))
    {
        // Spin through the events
        if(EC_COMPLETE == evCode)
        {
            // If looping, reset to beginning and continue playing
            if (  pCapBmp->mediaFile.bLooping)
            {
                LONGLONG pos=0;

                // Reset to first frame of movie
                hr = pMS->SetPositions(&pos, AM_SEEKING_AbsolutePositioning ,
                                       NULL, AM_SEEKING_NoPositioning);
                if (FAILED(hr))
                {
                    // Some custom filters (like the Windows CE MIDI filter)
                    // may not implement seeking interfaces (IMediaSeeking)
                    // to allow seeking to the start.  In that case, just stop
                    // and restart for the same effect.  This should not be
                    // necessary in most cases.
                    stopShareMediaFile(  p  );
                    runShareMediaFile(  p  );
                }
            }
            else if (  pCapBmp->mediaFile.bPlayThrough  )
            {
                // Tell the app to select the next file in the list
                //  PostMessage(WM_NEXTFILE, 0, 0);
				traceLogA(  "Not finished: need to play next file"  );
            }
            else
            {
                // Stop playback and display first frame of movie
                stopShareMediaFile(  p  );
            }
        }

        // Free memory associated with this event
        hr = pME->FreeEventParams(evCode, evParam1, evParam2);

    }

    return hr;
}

#endif


 int  handleGraphEvent_mediaFile(  void  *  pShareMediaFile,  BOOL  bMediaFile,  BOOL  bLooping,  BOOL  bPlayThrough  )
{
	int						iErr	=	-1;

	SHARE_MEDIA_FILE  *		p		=	(  SHARE_MEDIA_FILE  *  )pShareMediaFile;
	if  (  !p  )  return  -1;
	
	IMediaEventEx	*		pME		=	p->m_pME;
	IMediaSeeking	*		pMS		=	p->m_pMS;

    LONG evCode;
	LONG_PTR evParam1, evParam2;
    HRESULT hr=S_OK;

    // Since we may have a scenario where we're shutting down the application,
    // but events are still being generated, make sure that the event
    // interface is still valid before using it.  It's possible that
    // the interface could be freed during shutdown but later referenced in
    // this callback before the app completely exits.
    if  (  !pME  ||  !pMS  )  return  -1;
	
    while(SUCCEEDED(pME->GetEvent(&evCode, &evParam1, &evParam2, 0)))
    {
        // Spin through the events
        if(EC_COMPLETE == evCode)
        {
            // If looping, reset to beginning and continue playing
            if (  bMediaFile  &&  bLooping)
            {
                LONGLONG pos=0;

                // Reset to first frame of movie
                hr = pMS->SetPositions(&pos, AM_SEEKING_AbsolutePositioning ,
                                       NULL, AM_SEEKING_NoPositioning);
                if (FAILED(hr))
                {
                    // Some custom filters (like the Windows CE MIDI filter)
                    // may not implement seeking interfaces (IMediaSeeking)
                    // to allow seeking to the start.  In that case, just stop
                    // and restart for the same effect.  This should not be
                    // necessary in most cases.
                    stopShareMediaFile(  p  );
                    runShareMediaFile(  p  );
                }
            }
            else if (  bMediaFile  &&  bPlayThrough  )
            {
                // Tell the app to select the next file in the list
                //  PostMessage(WM_NEXTFILE, 0, 0);
				traceLogA(  "Not finished: need to play next file"  );
            }
            else
            {
                // Stop playback and display first frame of movie
                stopShareMediaFile(  p  );
            }
        }

        // Free memory associated with this event
        hr = pME->FreeEventParams(evCode, evParam1, evParam2);

    }

    return hr;
}


