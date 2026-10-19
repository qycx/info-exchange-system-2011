

#ifndef  __QMCSHAREMEDIAFILE_H__
#define  __QMCSHAREMEDIAFILE_H__	//  {

#define		CONST_volume_full		0L
#define		CONST_volume_silence	-10000L



typedef  struct  __shareMediaFile_t			{
			
				 BOOL							bInited;
				 
				 TCHAR							tFile[MAX_PATH];

				 IGraphBuilder				*	m_pGB;

				 IMediaControl				*	m_pMC;
				 IMediaEventEx				*	m_pME;
				 IVideoWindow				*	m_pVW;
				 IBasicAudio				*	m_pBA;
				 IBasicVideo				*	m_pBV;
				 IMediaSeeking				*	m_pMS;
				 IMediaPosition				*	m_pMP;
				 IVideoFrameStep			*	m_pFS;

				 //
				 BOOL							g_bAudioOnly;
				 BOOL							g_bNoAudio;

				 #ifdef  __SUPPORT_CUS_sampleGrabber__
						 IBaseFilter		*	m_pWMASFReader;
				 #endif

				 #if  0
				 struct							{
					 IBaseFilter			*	m_pGrabberFilter;
					 #ifndef  __SUPPORT_CUS_sampleGrabber__
							  ISampleGrabber			*	m_pGrabber;
					 #else
							  ISampleGrabber_is			*	m_pGrabber;
							  IBaseFilter				*	m_pNullRenderer;
					 #endif

					 CMySampleGrabberCB		*	m_pCallBack;
				 }								video, audio;
				 #endif

				 SAMPLE_grabber_info			audio,  video;

				 //
				 FILTER_STATE					psCurrent;			//   = State_Stopped;






}		 SHARE_MEDIA_FILE;




#endif  //  }



