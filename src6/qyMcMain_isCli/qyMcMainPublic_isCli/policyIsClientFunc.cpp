
#include	"stdafx.h"
#include	<tchar.h>
#ifndef  __WINCE__
	#include	<vfw.h>
#else
	#ifdef  __TEST__
		#include	<vfw.h>
	#endif
	#include	<mmreg.h>
	#include	<msacm.h>
#endif

#include	<shlobj.h>

#include	"qyMcMainCommon.h"
#include	"myresource.h"

#include	"myfourcc.h"


#include	"tmpCeLib.h"
#include	"policyAvParams.h"
#include	"qmcVideoCapture.h"
#include	"qyMcMainRealTimeMediaProc.h"

#include	"qmcDmoPublic.h"

#include	"qyOpenShellCommon.h"
#include	"policyIsClientFunc.h"
#include	"funcsForIsCliHelp.h"


 int  get_pcm_forAcm(  unsigned  int  uiCapType,  WAVEFORMATEX  *  pWfx  )
{
	switch  (  uiCapType  )  {
			case  CONST_capType_av:
				  makeWaveFormat_pcm(  DEFAULT_nChannels_pcm_av,  DEFAULT_iHertz_pcm_av,  DEFAULT_wBitsPerSample_pcm_av,  pWfx  );
				  break;
			case  CONST_capType_mediaFile:
				  makeWaveFormat_pcm(  DEFAULT_nChannels_pcm_mediaFile,  DEFAULT_iHertz_pcm_mediaFile,  DEFAULT_wBitsPerSample_pcm_mediaFile,  pWfx  );
				  break;
			case  CONST_capType_mediaDevice:
				  makeWaveFormat_pcm(  DEFAULT_nChannels_pcm_mediaDevice,  DEFAULT_iHertz_pcm_mediaDevice,  DEFAULT_wBitsPerSample_pcm_mediaDevice,  pWfx  );
				  break;
			default:
					break;
	}

	return  0;				  
}
 				  

 int  getAudioCompressorCfg_default_acm(  unsigned  int  uiCapType,  AUDIO_COMPRESSOR_CFG  *  pCfg  )
{
	memset(  pCfg,  0,  sizeof(  pCfg  )  );

	pCfg->ucCompressors  =  CONST_audioCompressors_acm;

	switch  (  uiCapType  )  {
			case  CONST_capType_screen:
				  break;			
			case  CONST_capType_mediaFile:
				  //  2009/05/05
				  pCfg->wf_compress.wFormatTag  =  DEFAULT_wFormatTag_acm_mediaFile;
				  pCfg->wf_compress.nChannels  =  DEFAULT_nChannels_acm_mediaFile;
				  pCfg->wf_compress.nSamplesPerSec  =  DEFAULT_nSamplesPerSec_acm_mediaFile;
				  pCfg->wf_compress.wBitsPerSample  =  DEFAULT_wBitsPerSample_acm_mediaFile;
				  //
				  break;
			case  CONST_capType_mediaDevice:
				  //  2009/05/05
				  pCfg->wf_compress.wFormatTag  =  DEFAULT_wFormatTag_acm_mediaDevice;
				  pCfg->wf_compress.nChannels  =  DEFAULT_nChannels_acm_mediaDevice;
				  pCfg->wf_compress.nSamplesPerSec  =  DEFAULT_nSamplesPerSec_acm_mediaDevice;
				  pCfg->wf_compress.wBitsPerSample  =  DEFAULT_wBitsPerSample_acm_mediaDevice;
				  //
				  break;
			case  CONST_capType_av:
				  pCfg->wf_compress.wFormatTag  =  DEFAULT_wFormatTag_acm_av;
				  pCfg->wf_compress.nChannels  =  DEFAULT_nChannels_acm_av;
				  pCfg->wf_compress.nSamplesPerSec  =  DEFAULT_nSamplesPerSec_acm_av;
				  pCfg->wf_compress.wBitsPerSample  =  DEFAULT_wBitsPerSample_acm_av;
				  //
				  break;
			default:
					break;
	}
	
	get_pcm_forAcm(  uiCapType,  &pCfg->wf_decompress_default  );

	return  0;
}


 int  getAudioCompressorCfg_default_dmo(  unsigned  int  uiCapType,  AUDIO_COMPRESSOR_CFG  *  pCfg  )
{
	memset(  pCfg,  0,  sizeof(  pCfg  )  );

	pCfg->ucCompressors  =  CONST_audioCompressors_dmo;

	switch  (  uiCapType  )  {
			case  CONST_capType_screen:
				  break;			
			case  CONST_capType_mediaFile:
				  pCfg->wf_compress.wFormatTag  =  DEFAULT_wFormatTag_dmo_mediaFile;
				  pCfg->wf_compress.nChannels  =  DEFAULT_nChannels_dmo_mediaFile;
				  pCfg->wf_compress.nSamplesPerSec  =  DEFAULT_nSamplesPerSec_dmo_mediaFile;
				  pCfg->wf_compress.wBitsPerSample  =  DEFAULT_wBitsPerSample_dmo_mediaFile;				  
				  break;
			case  CONST_capType_mediaDevice:
				  pCfg->wf_compress.wFormatTag  =  DEFAULT_wFormatTag_dmo_mediaDevice;
				  pCfg->wf_compress.nChannels  =  DEFAULT_nChannels_dmo_mediaDevice;
				  pCfg->wf_compress.nSamplesPerSec  =  DEFAULT_nSamplesPerSec_dmo_mediaDevice;
				  pCfg->wf_compress.wBitsPerSample  =  DEFAULT_wBitsPerSample_dmo_mediaDevice;
				  break;
			case  CONST_capType_av:
				  pCfg->wf_compress.wFormatTag  =  DEFAULT_wFormatTag_dmo_av;
				  pCfg->wf_compress.nChannels  =  DEFAULT_nChannels_dmo_av;
				  pCfg->wf_compress.nSamplesPerSec  =  DEFAULT_nSamplesPerSec_dmo_av;
				  pCfg->wf_compress.wBitsPerSample  =  DEFAULT_wBitsPerSample_dmo_av;
				  //
				  break;
			default:
					break;
	}
	makeWaveFormat_pcm(  pCfg->wf_compress.nChannels,  pCfg->wf_compress.nSamplesPerSec,  pCfg->wf_compress.wBitsPerSample,  &pCfg->wf_decompress_default  );

	return  0;
}

 int  getAudioCompressorCfg_default_ipp(  unsigned  int  uiCapType,  AUDIO_COMPRESSOR_CFG  *  pCfg  )				//  2012/01/20
{
	int		iErr	=	-1;
	QY_MC				*	pQyMc	=	QY_GET_GBUF(  );
	FUNCS_for_isCliHelp	*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  );

	memset(  pCfg,  0,  sizeof(  pCfg  )  );

	pCfg->ucCompressors  =  CONST_audioCompressors_ipp;


	CUS_MODULE_U	*  pModule	=	pFuncs->pf_getCusModule(  pQyMc,  CONST_moduleType_ipp,  0,  0,  NULL  );
	if  (  !pModule  )  goto  errLabel;
	if  (  !pModule->compress.ucbInited  )  goto  errLabel;

	if  (  !pModule->compress.pf_qdcGetCompressAudioCfg  )  goto  errLabel;
	if  (  pModule->compress.pf_qdcGetCompressAudioCfg(  &pCfg->wf_decompress_default,  &pCfg->wf_compress  )  )  goto  errLabel;
	
	//  get_pcm_forAcm(  uiCapType,  &pCfg->wf_decompress_default  );

	iErr  =  0;
errLabel:
	return  iErr;
}

 int  getAudioCompressorCfg_default_custom(  unsigned  int  uiCapType,  AUDIO_COMPRESSOR_CFG  *  pCfg  )
{
	int		iErr	=	-1;
	QY_MC			*	pQyMc	=	QY_GET_GBUF(  );
	FUNCS_for_isCliHelp	*	pFuncs	=	QY_GET_FUNCS_for_isCliHelp(  );

	memset(  pCfg,  0,  sizeof(  pCfg  )  );

	pCfg->ucCompressors  =  CONST_audioCompressors_custom;


	CUS_MODULE_U	*  pModule	=	pFuncs->pf_getCusModule(  pQyMc,  CONST_moduleType_compress,  0,  0,  NULL  );
	if  (  !pModule  )  goto  errLabel;
	if  (  !pModule->compress.ucbInited  )  goto  errLabel;

	if  (  !pModule->compress.pf_qdcGetCompressAudioCfg  )  goto  errLabel;
	if  (  pModule->compress.pf_qdcGetCompressAudioCfg(  &pCfg->wf_decompress_default,  &pCfg->wf_compress  )  )  goto  errLabel;
	
	//  get_pcm_forAcm(  uiCapType,  &pCfg->wf_decompress_default  );

	iErr  =  0;
errLabel:
	return  iErr;
}

 int  getAudioCompressorCfg_default(  unsigned  int  uiCapType,  int  level,  AUDIO_COMPRESSOR_CFG  *  pCfg  )
{
	unsigned  char			ucCompressors	=	0;								//  acm or dmo
				 
	switch  (  uiCapType  )  {
			case  CONST_capType_screen:
				  return  0;
			case  CONST_capType_av:
				  ucCompressors  =  DEFAULT_audioCompressors_av;
				  break;
			case  CONST_capType_mediaDevice:  
				  /*{
				  if  (  level  >=  CONST_policyAvLevel_dev_sd24fps  )  ucCompressors  =  CONST_audioCompressors_ipp;			//  mp3;
				  else  ucCompressors  =  DEFAULT_audioCompressors_mediaFile;												//  dmo
				  break;				
				  }*/
			case  CONST_capType_mediaFile:
				  if  (  level  ==  CONST_policyAvLevel_dev_2fps  
					  ||  level  ==  CONST_policyAvLevel_dev_10fps  )  {
						  ucCompressors  =  DEFAULT_audioCompressors_mediaFile;												//  dmo
				  }
				  else  ucCompressors  =  CONST_audioCompressors_ipp;
				  break;				
			default:
				    ucCompressors  =  DEFAULT_audioCompressors_mediaFile;
				    break;
	}

	switch  (  ucCompressors  )  {
			case  CONST_audioCompressors_acm:
				  return  getAudioCompressorCfg_default_acm(  uiCapType,  pCfg  );
				  break;
			case  CONST_audioCompressors_dmo:
				  return  getAudioCompressorCfg_default_dmo(  uiCapType,  pCfg  );
				  break;
			case  CONST_audioCompressors_ipp:
				  return  getAudioCompressorCfg_default_ipp(  uiCapType,  pCfg  );
				  break;
			case  CONST_audioCompressors_custom:
				  return  getAudioCompressorCfg_default_custom(  uiCapType,  pCfg  );
				  break;
			default:
					break;
	}
	return  -1;
}


 //  2011/08/08
 int  getAudioPlayCfg(  QY_REG  reg,  unsigned int  uiCapType,  unsigned int  uiSubCapType,  int  level,  AUDIO_PLAY_CFG  *  pPlayCfg  )
{
	PolicyAvParams		&	gAvParams	=	*QY_GET_PolicyAvParams(  );
	 //
	 TCHAR		*	pRegVal;
	 TCHAR			tBuf[256];
	 //  char			buf[128];
	 //  TCHAR		*	name;
	 TCHAR		*	pT;
	 long			lVal;

		//  2009/06/14
	pRegVal  =  CONST_regValName_uiMinTimeInMsOfAudioDataPlaying;
	if  (  qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	lVal  =  _tcstol(  tBuf,  &pT,  10  );
	if  (  lVal  <  MIN_uiMinTimeInMsOfAudioDataPlaying  ||  lVal  >  MAX_uiMinTimeInMsOfAudioDataPlaying  )  {  //  		lVal  =  DEFAULT_uiMinTimeInMsOfAudioDataPlaying;
		switch  (  uiCapType  )  {
			case  CONST_capType_av:  {
				if  (  uiSubCapType  ==  CONST_subCapType_webcam  )  {
					lVal  =  gAvParams.DEFAULT_audioPlayCfg_webcam.usMinTimeInMsOfAudioDataPlaying;
				}
				else  {
					switch  (  level  )  {
							case  CONST_policyAvLevel_ld1:
								lVal  =  gAvParams.audioPlayCfg_ld1.usMinTimeInMsOfAudioDataPlaying;
								break;
							case  CONST_policyAvLevel_sd:
								lVal  =  gAvParams.audioPlayCfg_sd.usMinTimeInMsOfAudioDataPlaying;
								break;
							case  CONST_policyAvLevel_sd1:
								lVal  =  gAvParams.audioPlayCfg_sd1.usMinTimeInMsOfAudioDataPlaying;
								break;
							case  CONST_policyAvLevel_sd2:
								lVal  =  gAvParams.audioPlayCfg_sd2.usMinTimeInMsOfAudioDataPlaying;
								break;
							case  CONST_policyAvLevel_sd3:
								lVal  =  gAvParams.audioPlayCfg_sd3.usMinTimeInMsOfAudioDataPlaying;
								break;
							case  CONST_policyAvLevel_hd:
								lVal  =  gAvParams.audioPlayCfg_hd.usMinTimeInMsOfAudioDataPlaying;
								break;
							case  CONST_policyAvLevel_hd1:
								lVal  =  gAvParams.audioPlayCfg_hd1.usMinTimeInMsOfAudioDataPlaying;
								break;
							case  CONST_policyAvLevel_hd2:
								lVal  =  gAvParams.audioPlayCfg_hd2.usMinTimeInMsOfAudioDataPlaying;
								break;
							case  CONST_policyAvLevel_hd3:
								lVal  =  gAvParams.audioPlayCfg_hd3.usMinTimeInMsOfAudioDataPlaying;
								break;
							case  CONST_policyAvLevel_fullHd:
								lVal  =  gAvParams.audioPlayCfg_fullHd.usMinTimeInMsOfAudioDataPlaying;
								break;
							case  CONST_policyAvLevel_fullHd1:
								lVal  =  gAvParams.audioPlayCfg_fullHd1.usMinTimeInMsOfAudioDataPlaying;
								break;
							case  CONST_policyAvLevel_fullHd2:
								lVal  =  gAvParams.audioPlayCfg_fullHd2.usMinTimeInMsOfAudioDataPlaying;
								break;
							case  CONST_policyAvLevel_fullHd3:
								lVal  =  gAvParams.audioPlayCfg_fullHd3.usMinTimeInMsOfAudioDataPlaying;
								break;
							case  CONST_policyAvLevel_ld:
							default:
								lVal  =  gAvParams.audioPlayCfg_ld.usMinTimeInMsOfAudioDataPlaying;
								break;
					}
				}
				}
				break;
			case  CONST_capType_mediaDevice:
			case  CONST_capType_mediaFile:
				lVal  =  CONST_uiMinTimeInMsOfAudioDataPlaying_1s;
				break;
			default:
				break;
		}
	}
	if  (  pPlayCfg->usMinTimeInMsOfAudioDataPlaying  !=  lVal  )  pPlayCfg->usMinTimeInMsOfAudioDataPlaying  =  (  unsigned  short  )lVal;

	pRegVal  =  CONST_regValName_uiAudioDataAddedToPlayEveryTime;
	if  (  qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	lVal  =  _tcstol(  tBuf,  &pT,  10  );
	if  (  lVal  <  MIN_uiAudioDataAddedToPlayEveryTime  ||  lVal  >  MAX_uiAudioDataAddedToPlayEveryTime  )  {  //  lVal  =  DEFAULT_uiAudioDataAddedToPlayEveryTime;
		switch  (  uiCapType  )  {
			case  CONST_capType_av:{
				if  (  uiSubCapType  ==  CONST_subCapType_webcam  )  {
					lVal  =  gAvParams.DEFAULT_audioPlayCfg_webcam.usAudioDataAddedToPlayEveryTime;
				}
				else  {
					switch  (  level  )  {
						case  CONST_policyAvLevel_ld1:
							lVal  =  gAvParams.audioPlayCfg_ld1.usAudioDataAddedToPlayEveryTime;
							break;
						case  CONST_policyAvLevel_sd:
							lVal  =  gAvParams.audioPlayCfg_sd.usAudioDataAddedToPlayEveryTime;
							break;
						case  CONST_policyAvLevel_sd1:
							lVal  =  gAvParams.audioPlayCfg_sd1.usAudioDataAddedToPlayEveryTime;
							break;
						case  CONST_policyAvLevel_sd2:
							lVal  =  gAvParams.audioPlayCfg_sd2.usAudioDataAddedToPlayEveryTime;
							break;
						case  CONST_policyAvLevel_sd3:
							lVal  =  gAvParams.audioPlayCfg_sd3.usAudioDataAddedToPlayEveryTime;
							break;
						case  CONST_policyAvLevel_hd:
							lVal  =  gAvParams.audioPlayCfg_hd.usAudioDataAddedToPlayEveryTime;
							break;
						case  CONST_policyAvLevel_hd1:
							lVal  =  gAvParams.audioPlayCfg_hd1.usAudioDataAddedToPlayEveryTime;
							break;
						case  CONST_policyAvLevel_hd2:
							lVal  =  gAvParams.audioPlayCfg_hd2.usAudioDataAddedToPlayEveryTime;
							break;
						case  CONST_policyAvLevel_hd3:
							lVal  =  gAvParams.audioPlayCfg_hd3.usAudioDataAddedToPlayEveryTime;
							break;
						case  CONST_policyAvLevel_fullHd:
							lVal  =  gAvParams.audioPlayCfg_fullHd.usAudioDataAddedToPlayEveryTime;
							break;
						case  CONST_policyAvLevel_fullHd1:
							lVal  =  gAvParams.audioPlayCfg_fullHd1.usAudioDataAddedToPlayEveryTime;
							break;
						case  CONST_policyAvLevel_fullHd2:
							lVal  =  gAvParams.audioPlayCfg_fullHd2.usAudioDataAddedToPlayEveryTime;
							break;
						case  CONST_policyAvLevel_fullHd3:
							lVal  =  gAvParams.audioPlayCfg_fullHd3.usAudioDataAddedToPlayEveryTime;
							break;
						case  CONST_policyAvLevel_ld:
						default:
							lVal  =  gAvParams.audioPlayCfg_ld.usAudioDataAddedToPlayEveryTime;
							break;
						}
					}
				}
				break;
			case  CONST_capType_mediaDevice:
			case  CONST_capType_mediaFile:
				lVal  =  CONST_uiAudioDataAddedToPlayEveryTime_1s;
				break;
			default:
				break;
		}
	}
	if  (  pPlayCfg->usAudioDataAddedToPlayEveryTime  !=  lVal  )  pPlayCfg->usAudioDataAddedToPlayEveryTime  =  (  unsigned  short  )lVal;

	pRegVal  =  CONST_regValName_uiNotifyIntervalInMs_needMoreAudioData;
	if  (  qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	lVal  =  _tcstol(  tBuf,  &pT,  10  );
	if  (  lVal  <  MIN_uiNotifyIntervalInMs_needMoreAudioData  ||  lVal  >  MAX_uiNotifyIntervalInMs_needMoreAudioData  )  {  //  lVal  =  DEFAULT_uiNotifyIntervalInMs_needMoreAudioData;
		switch  (  uiCapType  )  {
			case  CONST_capType_av:{
				if  (  uiSubCapType  ==  CONST_subCapType_webcam  )  {
					lVal  =  gAvParams.DEFAULT_audioPlayCfg_webcam.usNotifyIntervalInMs_needMoreAudioData;
				}
				else  {
					switch  (  level  )  {
						case  CONST_policyAvLevel_ld1:
							lVal  =  gAvParams.audioPlayCfg_ld1.usNotifyIntervalInMs_needMoreAudioData;
							break;
						case  CONST_policyAvLevel_sd:
							lVal  =  gAvParams.audioPlayCfg_sd.usNotifyIntervalInMs_needMoreAudioData;
							break;
						case  CONST_policyAvLevel_sd1:
							lVal  =  gAvParams.audioPlayCfg_sd1.usNotifyIntervalInMs_needMoreAudioData;
							break;
						case  CONST_policyAvLevel_sd2:
							lVal  =  gAvParams.audioPlayCfg_sd2.usNotifyIntervalInMs_needMoreAudioData;
							break;
						case  CONST_policyAvLevel_sd3:
							lVal  =  gAvParams.audioPlayCfg_sd3.usNotifyIntervalInMs_needMoreAudioData;
							break;
						case  CONST_policyAvLevel_hd:
							lVal  =  gAvParams.audioPlayCfg_hd.usNotifyIntervalInMs_needMoreAudioData;
							break;
						case  CONST_policyAvLevel_hd1:
							lVal  =  gAvParams.audioPlayCfg_hd1.usNotifyIntervalInMs_needMoreAudioData;
							break;
						case  CONST_policyAvLevel_hd2:
							lVal  =  gAvParams.audioPlayCfg_hd2.usNotifyIntervalInMs_needMoreAudioData;
							break;
						case  CONST_policyAvLevel_hd3:
							lVal  =  gAvParams.audioPlayCfg_hd3.usNotifyIntervalInMs_needMoreAudioData;
							break;
						case  CONST_policyAvLevel_fullHd:
							lVal  =  gAvParams.audioPlayCfg_fullHd.usNotifyIntervalInMs_needMoreAudioData;
							break;
						case  CONST_policyAvLevel_fullHd1:
							lVal  =  gAvParams.audioPlayCfg_fullHd1.usNotifyIntervalInMs_needMoreAudioData;
							break;
						case  CONST_policyAvLevel_fullHd2:
							lVal  =  gAvParams.audioPlayCfg_fullHd2.usNotifyIntervalInMs_needMoreAudioData;
							break;
						case  CONST_policyAvLevel_fullHd3:
							lVal  =  gAvParams.audioPlayCfg_fullHd3.usNotifyIntervalInMs_needMoreAudioData;
							break;
						case  CONST_policyAvLevel_ld:
						default:
							lVal  =  gAvParams.audioPlayCfg_ld.usNotifyIntervalInMs_needMoreAudioData;
							break;
						}
					}
				}
				break;
			case  CONST_capType_mediaDevice:
			case  CONST_capType_mediaFile:
				lVal  =  CONST_uiNotifyIntervalInMs_needMoreAudioData_1s;
				break;
			default:
				break;
		}
	}
	if  (  pPlayCfg->usNotifyIntervalInMs_needMoreAudioData  !=  lVal  )  pPlayCfg->usNotifyIntervalInMs_needMoreAudioData  =  (  unsigned  short  )lVal;

	//  2012/01/27
	pRegVal  =  CONST_regValName_uiMinTimeInMsToPlay;
	if  (  qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	lVal  =  _tcstol(  tBuf,  &pT,  10  );
	if  (  lVal  <=  0  ||  lVal  >  MAX_uiMinTimeInMsToPlay  )  {	//  lVal  =  DEFAULT_uiMinTimeInMsToPlay;
		switch  (  uiCapType  )  {
			case  CONST_capType_av:{
				if  (  uiSubCapType  ==  CONST_subCapType_webcam  )  {
					lVal  =  gAvParams.DEFAULT_audioPlayCfg_webcam.usMinTimeInMsToPlay;
				}
				else  {
					switch  (  level  )  {
						case  CONST_policyAvLevel_ld1:
							  lVal  =  gAvParams.audioPlayCfg_ld1.usMinTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_sd:
							  lVal  =  gAvParams.audioPlayCfg_sd.usMinTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_sd1:
							  lVal  =  gAvParams.audioPlayCfg_sd1.usMinTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_sd2:
							  lVal  =  gAvParams.audioPlayCfg_sd2.usMinTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_sd3:
							  lVal  =  gAvParams.audioPlayCfg_sd3.usMinTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_hd:
							  lVal  =  gAvParams.audioPlayCfg_hd.usMinTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_hd1:
							  lVal  =  gAvParams.audioPlayCfg_hd1.usMinTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_hd2:
							  lVal  =  gAvParams.audioPlayCfg_hd2.usMinTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_hd3:
							  lVal  =  gAvParams.audioPlayCfg_hd3.usMinTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_fullHd:
							  lVal  =  gAvParams.audioPlayCfg_fullHd.usMinTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_fullHd1:
							  lVal  =  gAvParams.audioPlayCfg_fullHd1.usMinTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_fullHd2:
							  lVal  =  gAvParams.audioPlayCfg_fullHd2.usMinTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_fullHd3:
							  lVal  =  gAvParams.audioPlayCfg_fullHd3.usMinTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_ld:
						default:
							  lVal  =  gAvParams.audioPlayCfg_ld.usMinTimeInMsToPlay;
							  break;
						}
					}
			    }
				break;
			case  CONST_capType_mediaDevice:
			case  CONST_capType_mediaFile:
				lVal  =  CONST_uiMinTimeInMsToPlay_1s;
				break;
			default:
				break;
		}
	}
	if  (  pPlayCfg->usMinTimeInMsToPlay  !=  lVal  )  pPlayCfg->usMinTimeInMsToPlay  =  (  unsigned  short  )lVal;


	//  2009/06/03
	pRegVal  =  CONST_regValName_uiMaxTimeInMsToPlay;
	if  (  qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	lVal  =  _tcstol(  tBuf,  &pT,  10  );
	if  (  lVal  <=  0  ||  lVal  >  MAX_uiMaxTimeInMsToPlay  )  {	//  lVal  =  DEFAULT_uiMaxTimeInMsToPlay;
		switch  (  uiCapType  )  {
			case  CONST_capType_av:{
				if  (  uiSubCapType  ==  CONST_subCapType_webcam  )  {
					lVal  =  gAvParams.DEFAULT_audioPlayCfg_webcam.usMaxTimeInMsToPlay;
				}
				else  {
					switch  (  level  )  {
						case  CONST_policyAvLevel_ld1:
							  lVal  =  gAvParams.audioPlayCfg_ld1.usMaxTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_sd:
							  lVal  =  gAvParams.audioPlayCfg_sd.usMaxTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_sd1:
							  lVal  =  gAvParams.audioPlayCfg_sd1.usMaxTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_sd2:
							  lVal  =  gAvParams.audioPlayCfg_sd2.usMaxTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_sd3:
							  lVal  =  gAvParams.audioPlayCfg_sd3.usMaxTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_hd:
							  lVal  =  gAvParams.audioPlayCfg_hd.usMaxTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_hd1:
							  lVal  =  gAvParams.audioPlayCfg_hd1.usMaxTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_hd2:
							  lVal  =  gAvParams.audioPlayCfg_hd2.usMaxTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_hd3:
							  lVal  =  gAvParams.audioPlayCfg_hd3.usMaxTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_fullHd:
							  lVal  =  gAvParams.audioPlayCfg_fullHd.usMaxTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_fullHd1:
							  lVal  =  gAvParams.audioPlayCfg_fullHd1.usMaxTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_fullHd2:
							  lVal  =  gAvParams.audioPlayCfg_fullHd2.usMaxTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_fullHd3:
							  lVal  =  gAvParams.audioPlayCfg_fullHd3.usMaxTimeInMsToPlay;
							  break;
						case  CONST_policyAvLevel_ld:
						default:
							  lVal  =  gAvParams.audioPlayCfg_ld.usMaxTimeInMsToPlay;
							  break;
						}
					}
				}
				break;
			case  CONST_capType_mediaDevice:
			case  CONST_capType_mediaFile:
				lVal  =  CONST_uiMaxTimeInMsToPlay_1s;
				break;
			default:
				break;
			}	
	}
	if  (  pPlayCfg->usMaxTimeInMsToPlay  !=  lVal  )  pPlayCfg->usMaxTimeInMsToPlay  =  (  unsigned  short  )lVal;
	
	//  
	pRegVal  =  CONST_regValName_uiMaxTimeInMsToBeRemoved;
	if  (  qyGetRegCfgT(  reg.hKeyRoot0,  CQyString(  reg.rootKey  ),  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	lVal  =  _tcstol(  tBuf,  &pT,  10  );
	if  (  lVal  <=  0  ||  lVal  >  MAX_uiMaxTimeInMsToBeRemoved  )  {	//  lVal  =  DEFAULT_uiMaxTimeInMsToBeRemoved;
		switch  (  uiCapType  )  {
			case  CONST_capType_av:{
				if  (  uiSubCapType  ==  CONST_subCapType_webcam  )  {
					lVal  =  gAvParams.DEFAULT_audioPlayCfg_webcam.usMaxTimeInMsToBeRemoved;
				}
				else  {
					switch  (  level  )  {
						case  CONST_policyAvLevel_ld1:
							  lVal  =  gAvParams.audioPlayCfg_ld1.usMaxTimeInMsToBeRemoved;
							  break;
						case  CONST_policyAvLevel_sd:
							  lVal  =  gAvParams.audioPlayCfg_sd.usMaxTimeInMsToBeRemoved;
							  break;
						case  CONST_policyAvLevel_sd1:
							  lVal  =  gAvParams.audioPlayCfg_sd1.usMaxTimeInMsToBeRemoved;
							  break;
						case  CONST_policyAvLevel_sd2:
							  lVal  =  gAvParams.audioPlayCfg_sd2.usMaxTimeInMsToBeRemoved;
							  break;
						case  CONST_policyAvLevel_sd3:
							  lVal  =  gAvParams.audioPlayCfg_sd3.usMaxTimeInMsToBeRemoved;
							  break;
						case  CONST_policyAvLevel_hd:
							  lVal  =  gAvParams.audioPlayCfg_hd.usMaxTimeInMsToBeRemoved;
							  break;
						case  CONST_policyAvLevel_hd1:
							  lVal  =  gAvParams.audioPlayCfg_hd1.usMaxTimeInMsToBeRemoved;
							  break;
						case  CONST_policyAvLevel_hd2:
							  lVal  =  gAvParams.audioPlayCfg_hd2.usMaxTimeInMsToBeRemoved;
							  break;
						case  CONST_policyAvLevel_hd3:
							  lVal  =  gAvParams.audioPlayCfg_hd3.usMaxTimeInMsToBeRemoved;
							  break;
						case  CONST_policyAvLevel_fullHd:
							  lVal  =  gAvParams.audioPlayCfg_fullHd.usMaxTimeInMsToBeRemoved;
							  break;
						case  CONST_policyAvLevel_fullHd1:
							  lVal  =  gAvParams.audioPlayCfg_fullHd1.usMaxTimeInMsToBeRemoved;
							  break;
						case  CONST_policyAvLevel_fullHd2:
							  lVal  =  gAvParams.audioPlayCfg_fullHd2.usMaxTimeInMsToBeRemoved;
							  break;
						case  CONST_policyAvLevel_fullHd3:
							  lVal  =  gAvParams.audioPlayCfg_fullHd3.usMaxTimeInMsToBeRemoved;
							  break;
						case  CONST_policyAvLevel_ld:
						default:
							  lVal  =  gAvParams.audioPlayCfg_ld.usMaxTimeInMsToBeRemoved;
							  break;
						}
					}
				}
				break;
			case  CONST_capType_mediaDevice:
			case  CONST_capType_mediaFile:
				lVal  =  CONST_uiMaxTimeInMsToBeRemoved_1s;
				break;
			default:
				break;
		}						  
	}
	if  (  pPlayCfg->usMaxTimeInMsToBeRemoved  !=  lVal  )  pPlayCfg->usMaxTimeInMsToBeRemoved  =  (  unsigned  short  )lVal;

	return  0;
}


 int  getCompressorCfg(  QY_REG  *  pReg,  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  int  level,  AV_COMPRESSOR_CFG  *  pCompressor  )
{
	 QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	 PolicyAvParams		&	gAvParams	=	*QY_GET_PolicyAvParams(  );

	 CQyString		rootKeyStr;
	 TCHAR		*	pRegVal;
	 TCHAR			tBuf[256]	=  _T(  ""  );
	 char			buf[128];
	 TCHAR			name[128]	=	_T(  ""  );
	 TCHAR		*	pT;
	 long			lVal;
	 QY_REG			reg;

	 //
	 memset(  pCompressor,  0,  sizeof(  pCompressor[0]  )  );

	 //
	 if  (  pReg  )  memcpy(  &reg,  pReg,  sizeof(  reg  )  );
	 else  {
		   memset(  &reg,  0,  sizeof(  reg  )  );
		   reg.hKeyRoot0  =  HKEY_CURRENT_USER;
	 }
	
	 if  (  !(  pT  =  qyGetDesByType(  CONST_capTypeTable,  uiCapType  )  )  )  return  -1;		 
	 if  (  !pT[0]  )  return  -1;
	 _sntprintf(  name,  mycountof(  name  ),  _T(  "%s"  ),  pT  );
	 if  (  uiSubCapType  )  {
		 if  (  !(  pT  =  qyGetDesByType(  CONST_subCapTypeTable,  uiSubCapType  )  )  )  return  -1;
		 if  (  !pT[0]  )  return  -1;
		 _sntprintf(  name,  mycountof(  name  ),  _T(  "%s.%s"  ),  name,  pT  );
	 }
	 

	 lstrcpyn(  tBuf,  CQyString(  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler  ),  mycountof(  tBuf  )  );
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\\%s"  ),  tBuf,  name  );
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\\level%d"  ),  tBuf,  level  );
	 //  _sntprintf(  reg.rootKey,  mycountof(  reg.rootKey  ),  _T(  "%s\\level%d"  ),  reg.rootKey,  level  );

	 rootKeyStr  =  CQyString(  tBuf  );

	 tBuf[0]  =  0;

	 pRegVal  =  _T(  CONST_regValName_audioCompressors  );
	 if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
		 pCompressor->audio.ucCompressors  =  (  unsigned  char  )_ttol(  tBuf  );
	 }
	 if  (  pQyMc->cfg.bGetPolicyFromIni  )  {	 
		 if  (  !getCfgValByName(  pQyMc->cfg.iniFullFileName,  CONST_regValName_audioCompressors,  buf,  sizeof(  buf  )  )  )  {
			 trim(  buf  );
			 lVal  =  qyGetTypeByDes(  gAvParams.pAudioCompressorsTable,  CQyString(  buf  )  );
			 if  (  lVal  !=  -1  )  pCompressor->audio.ucCompressors  =  lVal;
		}
	 }

	 pRegVal  =  _T(  CONST_regValName_audioCompressorName  );
	 if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
		 lstrcpyn(  pCompressor->audio.compressorName,  tBuf,  mycountof(  pCompressor->audio.compressorName  )  );
	 }
	 pRegVal  =  _T(  CONST_regValName_wfx_enc_wFormatTag  );
	 if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
		 pCompressor->audio.wf_compress.wFormatTag  =  (  WORD  )_ttol(  tBuf  );
	 }
	 pRegVal  =  _T(  CONST_regValName_wfx_enc_nChannels  );
	 if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
		 pCompressor->audio.wf_compress.nChannels  =  (  WORD  )_ttol(  tBuf  );
	 }	 
	 pRegVal  =  _T(  CONST_regValName_wfx_enc_nSamplesPerSec  );
	 if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
		 pCompressor->audio.wf_compress.nSamplesPerSec  =  (  DWORD  )_ttol(  tBuf  );
	 }	
	 pRegVal  =  _T(  CONST_regValName_wfx_enc_wBitsPerSample  );
	 if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
		 pCompressor->audio.wf_compress.wBitsPerSample  =  (  WORD  )_ttol(  tBuf  );
	 }
	 pRegVal  =  _T(  CONST_regValName_wfx_enc_nAvgBytesPerSec  );
	 if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
		 pCompressor->audio.wf_compress.nAvgBytesPerSec  =  (  DWORD  )_ttol(  tBuf  );
	 }


	 //
	 if  (  pCompressor->audio.ucCompressors  ==  CONST_audioCompressors_custom  )  getAudioCompressorCfg_default_custom(  uiCapType,  &pCompressor->audio  );
	 else  if  (  pCompressor->audio.ucCompressors  ==  CONST_audioCompressors_ipp  )  getAudioCompressorCfg_default_ipp(  uiCapType,  &pCompressor->audio  );
	 else  if  (  pCompressor->audio.ucCompressors  
		 &&  pCompressor->audio.wf_compress.wFormatTag
			&&  pCompressor->audio.wf_compress.nChannels  
				&&  pCompressor->audio.wf_compress.nSamplesPerSec
					&&  pCompressor->audio.wf_compress.wBitsPerSample  )
	 {
		 if  (  pCompressor->audio.ucCompressors  ==  CONST_audioCompressors_acm  )  get_pcm_forAcm(  uiCapType,  &pCompressor->audio.wf_decompress_default  );
		 else  makeWaveFormat_pcm(  pCompressor->audio.wf_compress.nChannels,  pCompressor->audio.wf_compress.nSamplesPerSec,  pCompressor->audio.wf_compress.wBitsPerSample,  &pCompressor->audio.wf_decompress_default  );
		 }
	 else  	
		 getAudioCompressorCfg_default(  uiCapType,  level,  &pCompressor->audio  );
 	 
	 //  2010/03/11
	 QY_REG	tmpReg;
	 tmpReg  =  reg;
	 //  myTChar2Str(  rootKeyStr,  tmpReg.rootKey,  mycountof(  tmpReg.rootKey  )  );
	 lstrcpyn(  tmpReg.rootKey,  rootKeyStr,  mycountof(  tmpReg.rootKey  )  );
	 getAudioPlayCfg(  tmpReg,  uiCapType,  uiSubCapType,  level,  &pCompressor->audio.playCfg  );

	 //
	 pRegVal  =  CONST_regValName_uiBytesRecorded_perBlockAlign;
	 if  (  qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	 lVal  =  _tcstol(  tBuf,  &pT,  10  );
	 if  (  lVal  <  MIN_uiBytesRecorded_perBlockAlign  ||  lVal  >  MAX_uiBytesRecorded_perBlockAlign  )  {
		 lVal  =  MACRO_getuiBytesRecorded_perBlockAlign(  pCompressor->audio,  &pCompressor->audio.wf_decompress_default  );
	 }
	 if  (  pCompressor->audio.uiBytesRecorded_perBlockAlign  !=  lVal  )  pCompressor->audio.uiBytesRecorded_perBlockAlign  =  lVal;
	 
	 //
	 pRegVal  =  _T(  CONST_regValName_videoCompressors  );
	 if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
		 pCompressor->video.common.ucCompressors  =  (  unsigned  char  )_ttol(  tBuf  );
	 }
	 if  (  pQyMc->cfg.bGetPolicyFromIni  )  {
		 if  (  !getCfgValByName(  pQyMc->cfg.iniFullFileName,  CONST_regValName_videoCompressors,  buf,  sizeof(  buf  )  )  )  {
			 trim(  buf  );
			 lVal  =  qyGetTypeByDes(  gAvParams.pVideoCompressorsTable,  CQyString(  buf  )  );
			 if  (  lVal  !=  -1  )  pCompressor->video.common.ucCompressors  =  lVal;
		}
	 }
	 if  (  !qyGetDesByType(  gAvParams.pVideoCompressorsTable,  pCompressor->video.common.ucCompressors  )  )  {
		 switch  (  uiCapType  )  {
				 case  CONST_capType_screen:		//  2012/02/16
					   switch  (  level  )  {
							   case  CONST_policyAvLevel_dev_2fps:
								     pCompressor->video.common.ucCompressors  =  gAvParams.DEV2FPS_videoCompressors_screen;
								     break;
							   case  CONST_policyAvLevel_dev_5fps:
							   case  CONST_policyAvLevel_dev_5fps1:
							   case  CONST_policyAvLevel_dev_5fps2:
							   case  CONST_policyAvLevel_dev_5fps3:
							   case  CONST_policyAvLevel_dev_5fps4:
							   case  CONST_policyAvLevel_dev_5fps5:
							   default:
								       pCompressor->video.common.ucCompressors  =  gAvParams.DEV5FPS_videoCompressors_screen;
									   break;
					   }
					   break;
				 case  CONST_capType_mediaFile:
					   switch  (  level  )  {
							   case  CONST_policyAvLevel_dev_2fps:
							   case  CONST_policyAvLevel_dev_10fps:
								     pCompressor->video.common.ucCompressors  =  gAvParams.DEV2FPS_videoCompressors_mediaFile;
								     break;
							   case  CONST_policyAvLevel_dev_sd24fps:
							   case  CONST_policyAvLevel_dev_sd25fps:
							   case  CONST_policyAvLevel_dev_sd30fps:
								       pCompressor->video.common.ucCompressors  =  gAvParams.SD_DEV24FPS_videoCompressors;
									   break;
							   case  CONST_policyAvLevel_dev_24fps:
							   case  CONST_policyAvLevel_dev_25fps:
							   case  CONST_policyAvLevel_dev_30fps:
								       pCompressor->video.common.ucCompressors  =  gAvParams.DEV24FPS_videoCompressors;
									   break;
							   default:
								       pCompressor->video.common.ucCompressors  =  gAvParams.DEV5FPS_videoCompressors_mediaFile;
									   break;
					   }
					   break;
				 case  CONST_capType_mediaDevice:
					   switch  (  level  )  {
							   case  CONST_policyAvLevel_dev_2fps:
								     pCompressor->video.common.ucCompressors  =  gAvParams.DEV2FPS_videoCompressors_mediaDevice;
									 break;
							   case  CONST_policyAvLevel_dev_5fps:
							   case  CONST_policyAvLevel_dev_5fps1:
							   case  CONST_policyAvLevel_dev_5fps2:
							   case  CONST_policyAvLevel_dev_5fps3:
							   case  CONST_policyAvLevel_dev_sd24fps:
							   case  CONST_policyAvLevel_dev_sd25fps:
							   case  CONST_policyAvLevel_dev_sd30fps:
								     pCompressor->video.common.ucCompressors  =  gAvParams.DEV5FPS_videoCompressors_mediaDevice;
									 break;
							   case  CONST_policyAvLevel_dev_24fps:
							   case  CONST_policyAvLevel_dev_25fps:
							   case  CONST_policyAvLevel_dev_30fps:
							   default:
								       pCompressor->video.common.ucCompressors  =  gAvParams.DEV30FPS_videoCompressors_mediaDevice;
									   break;
					   }
					   break;
				 case  CONST_capType_av:
				 default:
					 if  (  uiSubCapType  ==  CONST_subCapType_webcam  )  {
					     switch  (  level  )  {
								 case  CONST_policyAvLevel_sd3:
									   pCompressor->video.common.ucCompressors  =  gAvParams.SD3_videoCompressors_webcam;
									   pCompressor->video.iWidth_pic  =  gAvParams.SD3_iW_webcam;
									   pCompressor->video.iHeight_pic  =  gAvParams.SD3_iH_webcam;
									   break;
							     case  CONST_policyAvLevel_ld:
								 default:
									   pCompressor->video.common.ucCompressors  =  gAvParams.LD_videoCompressors_webcam;
									   pCompressor->video.iWidth_pic  =  gAvParams.LD_iW_webcam;
									   pCompressor->video.iHeight_pic  =  gAvParams.LD_iH_webcam;
									   break;
						 }
					 }
					 else  {
					     switch  (  level  )  {
							     case  CONST_policyAvLevel_ld1:
									   pCompressor->video.common.ucCompressors  =  gAvParams.LD1_videoCompressors_av;
									   pCompressor->video.iWidth_pic  =  gAvParams.LD1_iW_av;
									   pCompressor->video.iHeight_pic  =  gAvParams.LD1_iH_av;
									   break;
							     case  CONST_policyAvLevel_sd:
									   pCompressor->video.common.ucCompressors  =  gAvParams.SD_videoCompressors_av;
									   pCompressor->video.iWidth_pic  =  gAvParams.SD_iW_av;
									   pCompressor->video.iHeight_pic  =  gAvParams.SD_iH_av;
									   break;
								 case  CONST_policyAvLevel_sd1:
									   pCompressor->video.common.ucCompressors  =  gAvParams.SD1_videoCompressors_av;
									   pCompressor->video.iWidth_pic  =  gAvParams.SD1_iW_av;
									   pCompressor->video.iHeight_pic  =  gAvParams.SD1_iH_av;
									   break;
							     case  CONST_policyAvLevel_sd2:
									   pCompressor->video.common.ucCompressors  =  gAvParams.SD2_videoCompressors_av;
									   pCompressor->video.iWidth_pic  =  gAvParams.SD2_iW_av;
									   pCompressor->video.iHeight_pic  =  gAvParams.SD2_iH_av;
									   break;
							     case  CONST_policyAvLevel_sd3:
									   pCompressor->video.common.ucCompressors  =  gAvParams.SD3_videoCompressors_av;
									   pCompressor->video.iWidth_pic  =  gAvParams.SD3_iW_av;
									   pCompressor->video.iHeight_pic  =  gAvParams.SD3_iH_av;
									   break;
							     case  CONST_policyAvLevel_hd:
									   pCompressor->video.common.ucCompressors  =  gAvParams.HD_videoCompressors_av;
									   pCompressor->video.iWidth_pic  =  gAvParams.HD_iW_av;
									   pCompressor->video.iHeight_pic  =  gAvParams.HD_iH_av;
									   break;
							     case  CONST_policyAvLevel_hd1:
									   pCompressor->video.common.ucCompressors  =  gAvParams.HD1_videoCompressors_av;
									   pCompressor->video.iWidth_pic  =  gAvParams.HD1_iW_av;
									   pCompressor->video.iHeight_pic  =  gAvParams.HD1_iH_av;
									   break;
							     case  CONST_policyAvLevel_hd2:
									   pCompressor->video.common.ucCompressors  =  gAvParams.HD2_videoCompressors_av;
									   pCompressor->video.iWidth_pic  =  gAvParams.HD2_iW_av;
									   pCompressor->video.iHeight_pic  =  gAvParams.HD2_iH_av;
									   break;
							     case  CONST_policyAvLevel_hd3:
									   pCompressor->video.common.ucCompressors  =  gAvParams.HD3_videoCompressors_av;
									   pCompressor->video.iWidth_pic  =  gAvParams.HD3_iW_av;
									   pCompressor->video.iHeight_pic  =  gAvParams.HD3_iH_av;
									   break;
							     case  CONST_policyAvLevel_fullHd:
									   pCompressor->video.common.ucCompressors  =  gAvParams.FULLHD_videoCompressors_av;
									   pCompressor->video.iWidth_pic  =  gAvParams.FULLHD_iW_av;
									   pCompressor->video.iHeight_pic  =  gAvParams.FULLHD_iH_av;
									   break;
							     case  CONST_policyAvLevel_fullHd1:
									   pCompressor->video.common.ucCompressors  =  gAvParams.FULLHD1_videoCompressors_av;
									   pCompressor->video.iWidth_pic  =  gAvParams.FULLHD1_iW_av;
									   pCompressor->video.iHeight_pic  =  gAvParams.FULLHD1_iH_av;
									   break;
							     case  CONST_policyAvLevel_fullHd2:
									   pCompressor->video.common.ucCompressors  =  gAvParams.FULLHD2_videoCompressors_av;
									   pCompressor->video.iWidth_pic  =  gAvParams.FULLHD2_iW_av;
									   pCompressor->video.iHeight_pic  =  gAvParams.FULLHD2_iH_av;
									   break;
							     case  CONST_policyAvLevel_fullHd3:
									   pCompressor->video.common.ucCompressors  =  gAvParams.FULLHD3_videoCompressors_av;
									   pCompressor->video.iWidth_pic  =  gAvParams.FULLHD3_iW_av;
									   pCompressor->video.iHeight_pic  =  gAvParams.FULLHD3_iH_av;
									   break;
							     case  CONST_policyAvLevel_ld:
								 default:
									   pCompressor->video.common.ucCompressors  =  gAvParams.LD_videoCompressors_av;
									   pCompressor->video.iWidth_pic  =  gAvParams.LD_iW_av;
									   pCompressor->video.iHeight_pic  =  gAvParams.LD_iH_av;
									   break;
						 }
					 }
						 break;
		 }
	 }
	 pRegVal  =  _T(  CONST_regValName_videoCompressorName  );
	 if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
		 lstrcpyn(  pCompressor->video.compressorName,  tBuf,  mycountof(  pCompressor->video.compressorName  )  );
	 }
	 //  2008/03/15
	 pRegVal  =  _T(  CONST_regValName_videoCompressor  );
	 if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
		 myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );
		 safeStrnCpy(  buf,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
	 }


	 if  (  pCompressor->video.common.ucCompressors  !=  CONST_videoCompressors_custom  )  {
		 if  (  !pCompressor->video.common.fourccStr[0]  )  {
			 switch  (  uiCapType  )  {
					 case  CONST_capType_screen:		//  2012/02/16
						   switch  (  level  )  {
								   case  CONST_policyAvLevel_dev_2fps:
									     safeStrnCpy(  gAvParams.DEV2FPS_videoFourccStr_screen,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
									     break;
								   case  CONST_policyAvLevel_dev_5fps:
								   case  CONST_policyAvLevel_dev_5fps1:
								   case  CONST_policyAvLevel_dev_5fps2:
								   case  CONST_policyAvLevel_dev_5fps3:
								   case  CONST_policyAvLevel_dev_5fps4:
								   case  CONST_policyAvLevel_dev_5fps5:
								   default:
									     safeStrnCpy(  gAvParams.DEV5FPS_videoFourccStr_screen,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
									     break;
						   }
						   break;
					 case  CONST_capType_mediaFile:
					       switch  (  level  )  {
								   case  CONST_policyAvLevel_dev_2fps:
									     safeStrnCpy(  gAvParams.DEV2FPS_videoFourccStr_mediaFile,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
										 break;
								   case  CONST_policyAvLevel_dev_10fps:
									     safeStrnCpy(  gAvParams.DEV10FPS_videoFourccStr_mediaFile,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
									     break;
								   case  CONST_policyAvLevel_dev_sd24fps:
								   case  CONST_policyAvLevel_dev_sd25fps:
								   case  CONST_policyAvLevel_dev_sd30fps:
									     safeStrnCpy(  gAvParams.SD_DEV24FPS_videoFourccStr,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
									     break;
								   case  CONST_policyAvLevel_dev_24fps:
								   case  CONST_policyAvLevel_dev_25fps:
								   case  CONST_policyAvLevel_dev_30fps:
									       safeStrnCpy(  gAvParams.DEV24FPS_videoFourccStr,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
										   break;
								   default:
									       safeStrnCpy(  gAvParams.DEV5FPS_videoFourccStr_mediaFile,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
										   break;
						   }
						   break;
					 case  CONST_capType_mediaDevice:
						   switch  (  level  )  {
								   case  CONST_policyAvLevel_dev_2fps:
									     safeStrnCpy(  gAvParams.DEV2FPS_videoFourccStr_mediaDevice,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
									     break;
								   case  CONST_policyAvLevel_dev_5fps:
								   case  CONST_policyAvLevel_dev_5fps1:
								   case  CONST_policyAvLevel_dev_5fps2:
								   case  CONST_policyAvLevel_dev_5fps3:
								   case  CONST_policyAvLevel_dev_sd24fps:
								   case  CONST_policyAvLevel_dev_sd25fps:
								   case  CONST_policyAvLevel_dev_sd30fps:
									     safeStrnCpy(  gAvParams.DEV5FPS_videoFourccStr_mediaDevice,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
									     break;
								   case  CONST_policyAvLevel_dev_24fps:
								   case  CONST_policyAvLevel_dev_25fps:
								   case  CONST_policyAvLevel_dev_30fps:
								   default:
									     safeStrnCpy(  gAvParams.DEV30FPS_videoFourccStr_mediaDevice,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
									     break;
						  }
						  break;
					case  CONST_capType_av:
					default:
						if  (  uiSubCapType  ==  CONST_subCapType_webcam  )  {
						   switch  (  level  )  {
								   case  CONST_policyAvLevel_sd3:
									     safeStrnCpy(  gAvParams.SD3_videoFourccStr_webcam,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
									     break;
								   case  CONST_policyAvLevel_ld:
								   default:
									     safeStrnCpy(  gAvParams.LD_videoFourccStr_webcam,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
									     break;
						   }
						}
						else  {
						   switch  (  level  )  {
							       case  CONST_policyAvLevel_ld1:
									     safeStrnCpy(  gAvParams.LD1_videoFourccStr_av,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
										 break;
							       case  CONST_policyAvLevel_sd:
									     safeStrnCpy(  gAvParams.SD_videoFourccStr_av,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
										 break;
								   case  CONST_policyAvLevel_sd1:
									     safeStrnCpy(  gAvParams.SD1_videoFourccStr_av,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
										 break;
							       case  CONST_policyAvLevel_sd2:
									     safeStrnCpy(  gAvParams.SD2_videoFourccStr_av,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
										 break;
							       case  CONST_policyAvLevel_sd3:
									     safeStrnCpy(  gAvParams.SD3_videoFourccStr_av,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
										 break;
								   case  CONST_policyAvLevel_hd:
									     safeStrnCpy(  gAvParams.HD_videoFourccStr_av,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
									     break;
								   case  CONST_policyAvLevel_hd1:
									     safeStrnCpy(  gAvParams.HD1_videoFourccStr_av,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
									     break;
								   case  CONST_policyAvLevel_hd2:
									     safeStrnCpy(  gAvParams.HD2_videoFourccStr_av,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
									     break;
								   case  CONST_policyAvLevel_hd3:
									     safeStrnCpy(  gAvParams.HD3_videoFourccStr_av,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
									     break;
								   case  CONST_policyAvLevel_fullHd:
									     safeStrnCpy(  gAvParams.FULLHD_videoFourccStr_av,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
									     break;
								   case  CONST_policyAvLevel_fullHd1:
									     safeStrnCpy(  gAvParams.FULLHD1_videoFourccStr_av,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
									     break;
								   case  CONST_policyAvLevel_fullHd2:
									     safeStrnCpy(  gAvParams.FULLHD2_videoFourccStr_av,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
									     break;
								   case  CONST_policyAvLevel_fullHd3:
									     safeStrnCpy(  gAvParams.FULLHD3_videoFourccStr_av,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
									     break;
								   case  CONST_policyAvLevel_ld:
								   default:
									     safeStrnCpy(  gAvParams.LD_videoFourccStr_av,  pCompressor->video.common.fourccStr,  mycountof(  pCompressor->video.common.fourccStr  )  );
									     break;
						   }
						}
						break;
				}	
		 }
	 }

	 //  2011/07/31

	 if  (  pCompressor->video.common.ucCompressors  ==  CONST_videoCompressors_ipp  )  {
		 pCompressor->video.common.profile_idc  =  H264_PROFILE_BASELINE;
	 }

	 //
	 switch  (  uiCapType  )  {
			 case  CONST_capType_screen:
				   switch  (  level  )  {
						   case  CONST_policyAvLevel_dev_2fps:
							     pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.DEV2FPS_usMaxFps;										//  2012/02/16..FULLHD2_usMaxFps_screen;											//  2008/12/6,
								 break;
						   case  CONST_policyAvLevel_dev_5fps:
						   default:
							     pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.DEV5FPS_usMaxFps;											//  2012/02/16;.LD_usMaxFps_screen;											//  2008/12/6,
								 break;
				   }
				   //  2012/10/29
				   if  (  pCompressor->video.common.ucCompressors  ==  CONST_videoCompressors_ipp  )  {
					   switch  (  level  )  {
							   case  CONST_policyAvLevel_dev_5fps1:
								     pCompressor->video.common.iAvgBitrate  =  gAvParams.DEV5FPS1_bitrate;
								     break;
							   case  CONST_policyAvLevel_dev_5fps2:
								     pCompressor->video.common.iAvgBitrate  =  gAvParams.DEV5FPS2_bitrate;
								     break;
							   case  CONST_policyAvLevel_dev_5fps3:
								     pCompressor->video.common.iAvgBitrate  =  gAvParams.DEV5FPS3_bitrate;
								     break;
							   case  CONST_policyAvLevel_dev_5fps4:
								     pCompressor->video.common.iAvgBitrate  =  gAvParams.DEV5FPS4_bitrate;
								     break;
							   case  CONST_policyAvLevel_dev_5fps5:
								     pCompressor->video.common.iAvgBitrate  =  gAvParams.DEV5FPS5_bitrate;
								     break;
							   case  CONST_policyAvLevel_dev_5fps:
							   default:
									  pCompressor->video.common.iAvgBitrate  =  gAvParams.DEV5FPS_bitrate;
									  break;
					   }
				   }
				   break;
			 case  CONST_capType_mediaFile:
				   switch  (  level  )  {
						   case  CONST_policyAvLevel_dev_2fps:
								 pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.DEV2FPS_usMaxFps;
								 break;
						   case  CONST_policyAvLevel_dev_5fps:
								 pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.DEV5FPS_usMaxFps;
								 break;
						   case  CONST_policyAvLevel_dev_10fps:
								 pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.DEV10FPS_usMaxFps;
								 break;
						   case  CONST_policyAvLevel_dev_sd24fps:
						   case  CONST_policyAvLevel_dev_24fps:
								 pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.DEV24FPS_usMaxFps;
								 break;
						   case  CONST_policyAvLevel_dev_sd25fps:
						   case  CONST_policyAvLevel_dev_25fps:
								 pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.DEV25FPS_usMaxFps;
								 break;
						   case  CONST_policyAvLevel_dev_sd30fps:
						   case  CONST_policyAvLevel_dev_30fps:
								 pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.DEV30FPS_usMaxFps;
								 break;
						   default:
							   pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.DEFAULT_usMaxFps_mediaFile;
							   break;
				   }
				   //  2012/11/03, bitrate
				   if  (  pCompressor->video.common.ucCompressors  ==  CONST_videoCompressors_ipp  )  {
					   switch  (  level  )  {
							   case  CONST_policyAvLevel_dev_5fps1:
								     pCompressor->video.common.iAvgBitrate  =  gAvParams.DEV5FPS1_bitrate;
								     break;
							   case  CONST_policyAvLevel_dev_5fps2:
								     pCompressor->video.common.iAvgBitrate  =  gAvParams.DEV5FPS2_bitrate;
								     break;
							   case  CONST_policyAvLevel_dev_5fps3:
								     pCompressor->video.common.iAvgBitrate  =  gAvParams.DEV5FPS3_bitrate;
								     break;
							   case  CONST_policyAvLevel_dev_sd24fps:
							   case  CONST_policyAvLevel_dev_sd25fps:
							   case  CONST_policyAvLevel_dev_sd30fps:
								     pCompressor->video.common.iAvgBitrate  =  gAvParams.SD_DEV24FPS_bitrate;
								     break;
							   case  CONST_policyAvLevel_dev_5fps:
							   default:
									  pCompressor->video.common.iAvgBitrate  =  gAvParams.DEV5FPS_bitrate;
									  break;
					   }
				   }
				   break;
			 case  CONST_capType_mediaDevice:
				   switch  (  level  )  {
						   case  CONST_policyAvLevel_dev_2fps:
								 pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.DEV2FPS_usMaxFps;
								 break;
						   case  CONST_policyAvLevel_dev_5fps:
						   case  CONST_policyAvLevel_dev_5fps1:
						   case  CONST_policyAvLevel_dev_5fps2:
						   case  CONST_policyAvLevel_dev_5fps3:
								 pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.DEV5FPS_usMaxFps;
								 break;
						   case  CONST_policyAvLevel_dev_sd24fps:
						   case  CONST_policyAvLevel_dev_24fps:
								 pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.DEV24FPS_usMaxFps;
								 break;
						   case  CONST_policyAvLevel_dev_sd25fps:
						   case  CONST_policyAvLevel_dev_25fps:
								 pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.DEV25FPS_usMaxFps;
								 break;
						   case  CONST_policyAvLevel_dev_sd30fps:
						   case  CONST_policyAvLevel_dev_30fps:
								 pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.DEV30FPS_usMaxFps;
								 break;
						   default:
							   pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.DEFAULT_usFps_mediaDevice;
							   break;
				   }
				   //  2012/11/03
				   if  (  pCompressor->video.common.ucCompressors  ==  CONST_videoCompressors_ipp  )  {
					   switch  (  level  )  {
							   case  CONST_policyAvLevel_dev_5fps1:
								     pCompressor->video.common.iAvgBitrate  =  gAvParams.DEV5FPS1_bitrate;
								     break;
							   case  CONST_policyAvLevel_dev_5fps2:
								     pCompressor->video.common.iAvgBitrate  =  gAvParams.DEV5FPS2_bitrate;
								     break;
							   case  CONST_policyAvLevel_dev_5fps3:
								     pCompressor->video.common.iAvgBitrate  =  gAvParams.DEV5FPS3_bitrate;
								     break;
							   case  CONST_policyAvLevel_dev_sd24fps:
							   case  CONST_policyAvLevel_dev_sd25fps:
							   case  CONST_policyAvLevel_dev_sd30fps:
								     pCompressor->video.common.iAvgBitrate  =  gAvParams.SD_DEV24FPS_bitrate;
								     break;
							   case  CONST_policyAvLevel_dev_5fps:
							   default:
									  pCompressor->video.common.iAvgBitrate  =  gAvParams.DEV5FPS_bitrate;
									  break;
					   }
				   }
				   break;
			 case  CONST_capType_av:
			 default:
				 if  (  uiSubCapType  ==  CONST_subCapType_webcam  )  {
				    switch  (  level  )  {
			                case  CONST_policyAvLevel_sd3:
								  pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.SD3_usMaxFps_webcam;										//  2012/6/12,
								  break;
							case  CONST_policyAvLevel_ld:
							default:
								  pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.LD_usMaxFps_webcam;										//  2008/12/6,
								  break;
					}
				}
				else  {
				    switch  (  level  )  {
							case  CONST_policyAvLevel_ld1:
								  pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.LD1_usMaxFps_toShareBmp;
								  pCompressor->usFrames_perSecond_videoConference  =  gAvParams.LD1_usFps_toShareBmp_videoConference;
								  break;
							case  CONST_policyAvLevel_sd:
								  pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.SD_usMaxFps_toShareBmp;										//  2008/12/6,
								  pCompressor->usFrames_perSecond_videoConference  =  gAvParams.SD_usFps_toShareBmp_videoConference;						//  2012/02/16
								  break;
							case  CONST_policyAvLevel_sd1:
								  pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.SD1_usMaxFps_toShareBmp;										//  2008/12/6,
								  pCompressor->usFrames_perSecond_videoConference  =  gAvParams.SD1_usFps_toShareBmp_videoConference;						//  2012/02/16
								  break;
							case  CONST_policyAvLevel_sd2:
								  pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.SD2_usMaxFps_toShareBmp;										//  2008/12/6,
								  pCompressor->usFrames_perSecond_videoConference  =  gAvParams.SD2_usFps_toShareBmp_videoConference;						//  2012/02/16
								  break;
							case  CONST_policyAvLevel_sd3:
								  pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.SD3_usMaxFps_toShareBmp;										//  2008/12/6,
								  pCompressor->usFrames_perSecond_videoConference  =  gAvParams.SD3_usFps_toShareBmp_videoConference;						//  2012/02/16
								  break;
							case  CONST_policyAvLevel_hd:
								  pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.HD_usMaxFps_toShareBmp;										//  2008/12/6,
								  pCompressor->usFrames_perSecond_videoConference  =  gAvParams.HD_usFps_toShareBmp_videoConference;						//  2012/02/16
								  break;
							case  CONST_policyAvLevel_hd1:
								  pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.HD1_usMaxFps_toShareBmp;										//  2008/12/6,
								  pCompressor->usFrames_perSecond_videoConference  =  gAvParams.HD1_usFps_toShareBmp_videoConference;						//  2012/02/16
								  break;
							case  CONST_policyAvLevel_hd2:
								  pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.HD2_usMaxFps_toShareBmp;										//  2008/12/6,
								  pCompressor->usFrames_perSecond_videoConference  =  gAvParams.HD2_usFps_toShareBmp_videoConference;						//  2012/02/16
								  break;
							case  CONST_policyAvLevel_hd3:
								  pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.HD3_usMaxFps_toShareBmp;										//  2008/12/6,
								  pCompressor->usFrames_perSecond_videoConference  =  gAvParams.HD3_usFps_toShareBmp_videoConference;						//  2012/02/16
								  break;
							case  CONST_policyAvLevel_fullHd:
								  pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.FULLHD_usMaxFps_toShareBmp;										//  2008/12/6,
								  pCompressor->usFrames_perSecond_videoConference  =  gAvParams.FULLHD_usFps_toShareBmp_videoConference;						//  2012/02/16
								  break;
							case  CONST_policyAvLevel_fullHd1:
								  pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.FULLHD1_usMaxFps_toShareBmp;										//  2008/12/6,
								  pCompressor->usFrames_perSecond_videoConference  =  gAvParams.FULLHD1_usFps_toShareBmp_videoConference;						//  2012/02/16
								  break;
							case  CONST_policyAvLevel_fullHd2:
								  pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.FULLHD2_usMaxFps_toShareBmp;										//  2008/12/6,
								  pCompressor->usFrames_perSecond_videoConference  =  gAvParams.FULLHD2_usFps_toShareBmp_videoConference;						//  2012/02/16
								  break;
							case  CONST_policyAvLevel_fullHd3:
								  pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.FULLHD3_usMaxFps_toShareBmp;										//  2008/12/6,
								  pCompressor->usFrames_perSecond_videoConference  =  gAvParams.FULLHD3_usFps_toShareBmp_videoConference;						//  2012/02/16
								  break;
							case  CONST_policyAvLevel_ld:
							default:
								  pCompressor->video.common.usMaxFps_toShareBmp  =  gAvParams.LD_usMaxFps_toShareBmp;										//  2008/12/6,
								  pCompressor->usFrames_perSecond_videoConference  =  gAvParams.LD_usFps_toShareBmp_videoConference;						//  2012/02/16
								  break;
					}
				}
				break;
	 }

	 pRegVal  =  _T(  CONST_regValName_usMaxFps_toShareBmp  );
	 if  (  qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	 lVal  =  (  short  )_tcstol(  tBuf,  &pT,  10  );
	 if  (  lVal  >  0  &&  lVal  <=  MAX_usFps_toShareBmp  )  pCompressor->video.common.usMaxFps_toShareBmp  =  (  unsigned  short  )lVal;
	 //
	 if  (  pQyMc->cfg.bGetPolicyFromIni  )  {
		if  (  !getCfgValByName(  pQyMc->cfg.iniFullFileName,  CONST_regValName_usMaxFps_toShareBmp,  buf,  sizeof(  buf  )  )  )  {
			trim(  buf  );
			lVal  =  (  unsigned  short  )atol(  buf  );
			if  (  lVal  &&  lVal  <=  MAX_usFps_toShareBmp  )  {
				pCompressor->video.common.usMaxFps_toShareBmp  =  lVal;
			}
		}
	 }

	 pRegVal  =  _T(  CONST_regValName_usMinFps_toShareBmp  );
	 if  (  qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	 lVal  =  (  short  )_tcstol(  tBuf,  &pT,  10  );
	 if  (  lVal  >  0  &&  lVal  <=  pCompressor->video.common.usMaxFps_toShareBmp  )  pCompressor->video.common.usMinFps_toShareBmp  =  (  unsigned  short  )lVal;

	 //  2012/07/01
	 pRegVal  =  _T(  CONST_regValName_ucSeconds_perFrame  );
	 if  (  qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	 lVal  =  (  short  )_tcstol(  tBuf,  &pT,  10  );
	 if  (  lVal  >  0  &&  lVal  <=  MAX_ucSeconds_perFrame  )  pCompressor->video.common.ucSeconds_perFrame  =  (  unsigned  short  )lVal;


	 //
	 if  (  uiCapType  ==  CONST_capType_av  ) {
		 	 pRegVal  =  _T(  CONST_regValName_iWidth_pic  );
			 if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  NULL  )  
				 && tBuf[0]  )pCompressor->video.iWidth_pic  =  _ttol(  tBuf  );
	 
			 pRegVal  =  _T(  CONST_regValName_iHeight_pic  );
			 if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  NULL  )
				 && tBuf[0]  )pCompressor->video.iHeight_pic  =  _ttol(  tBuf  );
	 }

	 //  2011/12/10
	 switch  (  pCompressor->video.common.ucCompressors  )  {
			 case  CONST_videoCompressors_mediaSdk:		//  2011/12/10, 调用ipp的rgb2Yv12的转换函数，送出的是翻转的图像
				   pCompressor->video.common.ucbOutputFlippedImg  =  TRUE;
				   //  2012/02/08
				   pRegVal  =  _T(  CONST_regValName_videoEffect  );
				   if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
					   pCompressor->video.common.iTargetUsage  =  _ttol(  tBuf  );
				   }
				   if  (  !pCompressor->video.common.iTargetUsage  )  pCompressor->video.common.iTargetUsage  =  DEFAULT_iTargetUsage;
				   break;
			 case  CONST_videoCompressors_cuda:		//  2012/06/27
				   //  2012/06/27
				   pRegVal  =  _T(  CONST_regValName_avgBitrate  );
				   if  (  !qyGetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  {
					   pCompressor->video.common.iAvgBitrate  =  _ttol(  tBuf  );
				   }
				   if  (  !pCompressor->video.common.iAvgBitrate  )  pCompressor->video.common.iAvgBitrate  =  DEFAULT_iAvgBitrate;
				   break;
			 default:
					 break;
	 }

	 return  0;
}


 int  saveCompressorCfg(  QY_REG  reg,  unsigned  int  uiCapType,  unsigned  int  uiSubCapType,  int  level,  AV_COMPRESSOR_CFG  *  pCompressor  )
{
	QY_MC			*	pQyMc		=  QY_GET_GBUF(  );
	CQyString			rootKeyStr;
	//  TCHAR		*	pRegVal;
	TCHAR				tBuf[256]	=  _T(  ""  );
	//  char			buf[128];
	TCHAR			name[128]		=	_T(  ""  );
	TCHAR		*	pT;
	//  long			lVal;

	 if  (  !(  pT  =  qyGetDesByType(  CONST_capTypeTable,  uiCapType  )  )  )  return  -1;		 
	 if  (  !pT[0]  )  return  -1;
	 _sntprintf(  name,  mycountof(  name  ),  _T(  "%s"  ),  pT  );
	 if  (  uiSubCapType  )  {
		 if  (  !(  pT  =  qyGetDesByType(  CONST_subCapTypeTable,  uiSubCapType  )  )  )  return  -1;
		 if  (  !pT[0]  )  return  -1;
		 _sntprintf(  name,  mycountof(  name  ),  _T(  "%s.%s"  ),  name,  pT  );
	 }

	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\\%s"  ),  pQyMc->cfg.pSysCfg->rootKey_qnmScheduler,  name  );
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s\\level%d"  ),  tBuf,  level  );

	 rootKeyStr  =  CQyString(  tBuf  );

	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_audioCompressors  ),  CQyString(  _ltot(  pCompressor->audio.ucCompressors,  tBuf,  10  )  )  );	
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_audioCompressorName  ),  CQyString(  pCompressor->audio.compressorName  )  );

	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_wfx_enc_wFormatTag  ),  CQyString(  _ltot(  pCompressor->audio.wf_compress.wFormatTag,  tBuf,  10  )  )  );	
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_wfx_enc_nChannels  ),  CQyString(  _ltot(  pCompressor->audio.wf_compress.nChannels,  tBuf,  10  )  )  );	
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_wfx_enc_nSamplesPerSec  ),  CQyString(  _ltot(  pCompressor->audio.wf_compress.nSamplesPerSec,  tBuf,  10  )  )  );	
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_wfx_enc_nAvgBytesPerSec  ),  CQyString(  _ltot(  pCompressor->audio.wf_compress.nAvgBytesPerSec,  tBuf,  10  )  )  );	
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_wfx_enc_wBitsPerSample  ),  CQyString(  _ltot(  pCompressor->audio.wf_compress.wBitsPerSample,  tBuf,  10  )  )  );	

	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  CONST_regValName_uiBytesRecorded_perBlockAlign,  CQyString(  _ltot(  pCompressor->audio.uiBytesRecorded_perBlockAlign,  tBuf,  10  )  )  );	

	//  2010/03/11
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  CONST_regValName_uiMinTimeInMsOfAudioDataPlaying,  CQyString(  _ltot(  pCompressor->audio.playCfg.usMinTimeInMsOfAudioDataPlaying,  tBuf,  10  )  )  );
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  CONST_regValName_uiAudioDataAddedToPlayEveryTime,  CQyString(  _ltot(  pCompressor->audio.playCfg.usAudioDataAddedToPlayEveryTime,  tBuf,  10  )  )  );
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  CONST_regValName_uiNotifyIntervalInMs_needMoreAudioData,  CQyString(  _ltot(  pCompressor->audio.playCfg.usNotifyIntervalInMs_needMoreAudioData,  tBuf,  10  )  )  );
	//  2012/01/27
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  CONST_regValName_uiMinTimeInMsToPlay,  CQyString(  _ltot(  pCompressor->audio.playCfg.usMinTimeInMsToPlay,  tBuf,  10  )  )  );
	//
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  CONST_regValName_uiMaxTimeInMsToPlay,  CQyString(  _ltot(  pCompressor->audio.playCfg.usMaxTimeInMsToPlay,  tBuf,  10  )  )  );
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  CONST_regValName_uiMaxTimeInMsToBeRemoved,  CQyString(  _ltot(  pCompressor->audio.playCfg.usMaxTimeInMsToBeRemoved,  tBuf,  10  )  )  );


	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_iWidth_pic  ),  CQyString(  _ltot(  pCompressor->video.iWidth_pic,  tBuf,  10  )  )  );
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_iHeight_pic  ),  CQyString(  _ltot(  pCompressor->video.iHeight_pic,  tBuf,  10  )  )  );
	//
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_videoCompressors  ),  CQyString(  _ltot(  pCompressor->video.common.ucCompressors,  tBuf,  10  )  )  );
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_videoCompressorName  ),  CQyString(  pCompressor->video.compressorName  )  );
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_videoCompressor  ),  CQyString(  pCompressor->video.common.fourccStr  )  );
	//  2012/02/08
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_videoEffect  ),  _ltot(  pCompressor->video.common.iTargetUsage,  tBuf,  10  )  );
	//  2012/06/27
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_avgBitrate  ),  _ltot(  pCompressor->video.common.iAvgBitrate,  tBuf,  10  )  );
	//
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_usMaxFps_toShareBmp  ), _ltot(  pCompressor->video.common.usMaxFps_toShareBmp,  tBuf,  10  )  );
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_usMinFps_toShareBmp  ), _ltot(  pCompressor->video.common.usMinFps_toShareBmp,  tBuf,  10  )  );
	//  2012/07/01
	qySetRegCfgT(  reg.hKeyRoot0,  rootKeyStr,  _T(  CONST_regValName_ucSeconds_perFrame  ),  _ltot(  pCompressor->video.common.ucSeconds_perFrame,   tBuf,  10  )  );

	return  0;
}

 CQyString  getCompressorDesc(  unsigned  int  uiCapType,  AV_COMPRESSOR_CFG  *  pCompressor  )
{
	PolicyAvParams		&	gAvParams	=	*QY_GET_PolicyAvParams(  );
	TCHAR	tBuf[256]	=	_T(  ""  );
	QY_MC			*	pQyMc			=	QY_GET_GBUF(  );

	switch  (  uiCapType  )  {
			case  CONST_capType_av:
			case  CONST_capType_mediaFile:
			case  CONST_capType_mediaDevice:
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "(%d,%d,%d)%d"  ),  pCompressor->audio.wf_decompress_default.nChannels,  pCompressor->audio.wf_decompress_default.nSamplesPerSec,  pCompressor->audio.wf_decompress_default.wBitsPerSample,  pCompressor->audio.uiBytesRecorded_perBlockAlign  );
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %s:%s(%d,%d,%d,%d)"  ),  tBuf,  qyGetDesByType1(  gAvParams.pAudioCompressorsTable,  pCompressor->audio.ucCompressors  ),  getMediaSubtypeName(  FOURCCMap(  pCompressor->audio.wf_compress.wFormatTag  )  ),  pCompressor->audio.wf_compress.nChannels,  pCompressor->audio.wf_compress.nSamplesPerSec,  pCompressor->audio.wf_compress.wBitsPerSample,  pCompressor->audio.wf_compress.nAvgBytesPerSec  );

				  int  iDelayInMs;
				  iDelayInMs  =  MACRO_getDelayInMs(  pCompressor->audio.playCfg  );
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %.1fs"  ),  tBuf,  iDelayInMs  /  1000.  );

				  //
				  if  (  uiCapType  ==  CONST_capType_av  )  {
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %d*%d %dfps"  ),  tBuf,  pCompressor->video.iWidth_pic,  pCompressor->video.iHeight_pic,  (  int  )pCompressor->video.common.usMaxFps_toShareBmp  );
				      }
				  else  {
					    _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %dfps"  ),  tBuf,  (  int  )pCompressor->video.common.usMaxFps_toShareBmp  );
				  }
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %s:%s"  ),  tBuf,  qyGetDesByType1(  gAvParams.pVideoCompressorsTable,  pCompressor->video.common.ucCompressors  ),  CQyString(  pCompressor->video.common.fourccStr  )  );
				  if  (  pCompressor->video.common.iTargetUsage  )_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  tBuf,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_iTargetUsageTable  ),  pCompressor->video.common.iTargetUsage  )  );
				  if  (  pCompressor->video.common.iAvgBitrate  ) {
					  if  (  uiCapType  ==  CONST_capType_mediaDevice  )  {
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  tBuf,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_iAvgBitrateTable  ),  pCompressor->video.common.iAvgBitrate  )  ); 
					  }
					  else  {
						  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %dk"  ),  tBuf,  pCompressor->video.common.iAvgBitrate  /  1000  );
					  }
				  }
				  break;

			case  CONST_capType_screen:
				  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  ",,,%dfps, %s:%s"  ),  (  int  )pCompressor->video.common.usMaxFps_toShareBmp,  qyGetDesByType1(  gAvParams.pVideoCompressorsTable,  pCompressor->video.common.ucCompressors  ),  CQyString(  pCompressor->video.common.fourccStr  )  );
				  if  (  pCompressor->video.common.ucCompressors  ==  CONST_videoCompressors_ipp  )  {
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %dkbps"  ),  tBuf,  pCompressor->video.common.iAvgBitrate  /  1000  );
				  }
				  break;
			default:
				    break;
	}

	return  CQyString(  tBuf  );
 }

//  #define		MACRO_getuiBytesRecorded_perBlockAlign(  audioCompressor  )		(  (  (  audioCompressor.ucCompressors  ==  CONST_audioCompressors_acm  )  ?  1  :  1  )  *  audioCompressor.wf_decompress_default.nSamplesPerSec  /  5  )
 int  MACRO_getuiBytesRecorded_perBlockAlign(  AUDIO_COMPRESSOR_CFG  &audioCompressor,  WAVEFORMATEX  *  pWf_org  )		
{
	PolicyAvParams		&	gAvParams	=	*QY_GET_PolicyAvParams(  );

	//
	int  uiBytesRecorded_perBlockAlign	=	-1;
	
	//  2013/03/09
	if  (  !memcmp(  &audioCompressor.playCfg,  &gAvParams.CONST_audioPlayCfg_07s,  sizeof(  audioCompressor.playCfg  )  )  )  {
		if  (  !(  pWf_org->nSamplesPerSec  %  100  )  )  {
			uiBytesRecorded_perBlockAlign  =  pWf_org->nSamplesPerSec  /  100  *  12;
			return  uiBytesRecorded_perBlockAlign;
		}		
	}

	//
	uiBytesRecorded_perBlockAlign  =  pWf_org->nSamplesPerSec  /  5;

	return  uiBytesRecorded_perBlockAlign;
}

 //  2011/12/13
 int  getDefaultPolicyAvLevel(  unsigned  int  uiCapType,  unsigned int uiSubCapType,  BOOL  bReply  )
{
	int	ucCmd;

	switch  (  uiCapType  )  {
		case  CONST_capType_av:
			if  (  uiSubCapType  ==  CONST_subCapType_webcam  )  {
				ucCmd  =  DEFAULT_policyAvLevel_req_webcam;
			}
			else  {
				if  (  bReply  )  {
					ucCmd  =  DEFAULT_policyAvLevel_reply_standard;
					if  (  qyGetAppAvLevel_qyMc(  )  ==  CONST_qyAppAvLevel_high  )  ucCmd  =  DEFAULT_policyAvLevel_reply_high;
				}
				else  ucCmd  =  DEFAULT_policyAvLevel_req;
			}
			break;
		case  CONST_capType_screen:
			ucCmd  =  DEFAULT_policyAvLevel_req_screen;
			if  (  qyGetAppAvLevel_qyMc(  )  ==  CONST_qyAppAvLevel_basic  )  ucCmd  =  DEFAULT_policyAvLevel_req_screen_basic;
			break;
		case  CONST_capType_mediaFile:
			ucCmd  =  DEFAULT_policyAvLevel_req_mediaFile;
			if  (  qyGetAppAvLevel_qyMc(  )  ==  CONST_qyAppAvLevel_basic  )  ucCmd  =  DEFAULT_policyAvLevel_req_mediaFile_basic;
			break;
		case  CONST_capType_mediaDevice:
			ucCmd  =  DEFAULT_policyAvLevel_req_mediaDevice;
			if  (  qyGetAppAvLevel_qyMc(  )  ==  CONST_qyAppAvLevel_basic  )  ucCmd  =  DEFAULT_policyAvLevel_req_mediaDevice_basic;
			break;
		default:
			break;
	}
	return  ucCmd;
}
