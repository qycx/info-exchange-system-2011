// testAec.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include	<comutil.h>

#include <string>
#include <windows.h>
#include <dmo.h>
//  #include <Mmsystem.h>
//  #include <objbase.h>
#include <mediaobj.h>
#include <uuids.h>
//  #include <propidl.h>
#include <wmcodecdsp.h>

#include <audioclient.h>

//  #include <AudioEngineEndpoint.h>
//  #include <DeviceTopology.h>
//#include <conio.h>



//  #include	<initguid.h>

#include	"qyMcMainCommon.h"
#include	"mmDeviceProc.h"
#include	"qyAvRecordPublic.h"

#include	"aecCommon.h"

#include  "AecKsBinder.h"
// #include  "sqVirtualMachine.h"

#include  "sqWin32AEC.h"
#include  "aecSoundDeviceSelection.h"
//  #include  "qRingBuffer.hpp"



	//  HANDLE  hPlayThread  =  NULL;
	//  HANDLE  hRecThread  =  NULL;
	//
	//  int  recTerminate;
	int  recSemaphore;
	int  recSampleRate;
	int  recIsStereo;
	//
	//  struct VirtualMachine  *  interpreterProxy;
	//
	int  AEC_ENABLED;
	int	 AEC_SUPPORTED;

	//
	//  static  Qwaq::QRingBuffer  *  g_aecRingBuffer  =  NULL;

#include  "mediabuf.h"
class  CStaticMediaBuffer :  public  CBaseMediaBuffer  {
public:
	STDMETHODIMP_(ULONG)  AddRef() {return 2;}
	STDMETHODIMP_(ULONG)  Release() {return 1;}
	void  Init(  BYTE *pData, ULONG ulSize,  ULONG  ulData  )  {
		m_pData  =  pData;
		m_ulSize  =  ulSize;
		m_ulData  =  ulData;
	}
};


#define	 SAFE_RELEASE( p )  {  if  ( NULL!=  p  )  {  p->Release();  p  =  NULL;  }  }


#if  0
HANDLE  hPlayEvent  =  NULL;
HANDLE  hRecEvent  =  NULL;


DeviceInfoList  playerDevices;
DeviceInfoList  recorderDevices;
#endif


IMediaObject  * lpDMO  =  NULL;



int aec_soundInit(  void  )
{
	AEC_ENABLED  =  0;

	//  Figure out what os version we're on. We currently support echo-cancellation only on windows vista and 7.
	OSVERSIONINFOEX  osvi;
	ZeroMemory(  &osvi,  sizeof(  OSVERSIONINFOEX  )  );
	osvi.dwOSVersionInfoSize  =  sizeof(  OSVERSIONINFOEX  );
	if  (  !GetVersionEx(  (  OSVERSIONINFO  *  )  &osvi  )  )  
	{
		printf(  "\t...  cannot determine platform;assuming AEC is unsupported:0x%1xL\n",  GetLastError(  )  );
		AEC_SUPPORTED  =  0;
	}
	else if  (  osvi.dwMajorVersion  >=  6  )  {
		if  (  osvi.dwMajorVersion  ==  6  &&  osvi.dwMinorVersion  ==  0  )  {
			printf(  "\t...  AEC  is supported on this platform(  Windows Vista  )\n"  );
		}
		else  {
			printf(  "\t...  AEC  is supported on this platform(  Windows 7  or  later  )\n"  );
		}

		AEC_SUPPORTED  =  1;
	}
	else  {
		printf(  "\t...  AEC is not supported on Windows xp and earlier\n"  );
		AEC_SUPPORTED  =  0;
	}

	lpDMO  =  NULL;

	return  1;

}

int aec_soundShutdown(  void  )
{
	return  1;
}


int aec_snd_StopRecording(  void )
{
	QY_MC						*	pQyMc						=	QY_GET_GBUF(  );
	MC_VAR_isCli				*	pProcInfo					=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	CAP_procInfo_recordSound  *  pRecordSoundProcInfo  =  &pProcInfo->av.localAv.recordSoundProcInfo;

	if  (  pRecordSoundProcInfo->thread.hThread  )  {
		//  recTerminate  =  1;
		pRecordSoundProcInfo->thread.bQuit  =  TRUE;
#if  0
		SetEvent(  hRecEvent  );
#endif
		if  (  WaitForSingleObject(  pRecordSoundProcInfo->thread.hThread,  1000  )  ==  WAIT_TIMEOUT  )  printf(  "Waring:  timed out after waiting 1 second for record thread to finish\n"  );
		pRecordSoundProcInfo->thread.hThread  =  NULL;
	}

#if  0
	if  (  g_aecRingBuffer  )  {
		delete  g_aecRingBuffer;
		g_aecRingBuffer  =  NULL;
	}
#endif

	SAFE_RELEASE(  lpDMO  );
#if  0
	ResetEvent(  hRecEvent  );
#endif
	//  recTerminate  =  0;
	pRecordSoundProcInfo->thread.bQuit  =  0;

	return  0;
}


#define  CHECK_START_RECORDING_HR(  hr,  errorText  )  {  if  (  FAILED(  hr  )  )  {  DPRINTF(  errorText);  hitAnError  =  true;  goto  error;  }  }

static  HRESULT  aec_findDeviceWithGUID(  IMMDeviceCollection  *  deviceCollection,  LPGUID  guid,  IMMDevice  **  resultDevice,  int  *  resultIndex  )
{
	UINT  index,  deviceCount;
	HRESULT  hr;
	bool  hitAnError  =  false;
	char  errBuf[128]  =  "";

	*resultDevice  =  NULL;
	*resultIndex  =  -2;
	IMMDevice  *  device  =  NULL;
	IPropertyStore  *  deviceProperties  =  NULL;

	if  (  !guid  ){
		hr  =  E_FAIL;
		CHECK_START_RECORDING_HR(   hr,  (  _T("Failed: no GUID  provided to find Device\n")  )  );
	}

	hr  =  deviceCollection->GetCount(  &deviceCount  );
	CHECK_START_RECORDING_HR(   hr,  (  _T(  "Failed(0x%1xL): cannot get number of device\n"  ),  hr  )  );


	for(  index =0;  index  <  deviceCount;  index++  ){
		
		GUID  enumGUID;

		hr  =  deviceCollection->Item(  index,  &device  );
		CHECK_START_RECORDING_HR(   hr,  (  _T(  "Failed(0x%1xL): cannot obtain device  #%d\n"  ),  hr,  index  )  );


		hr  =  device->OpenPropertyStore(  STGM_READ, &deviceProperties  );
		CHECK_START_RECORDING_HR(   hr,  (  _T(  "Failed(0x%1xL): cannot open device properties\n"  ),  hr  )  );

		PROPVARIANT  value;
		PropVariantInit(  &value  );
		hr  =  deviceProperties->GetValue(  PKEY_AudioEndpoint_GUID,  &value  );
		CHECK_START_RECORDING_HR(   hr,  (  _T(  "Failed(0x%1xL): cannot obtain device  GUID from properties\n"  ),  hr  )  );
		hr  =  IIDFromString(  value.pwszVal,  &enumGUID  );
		CHECK_START_RECORDING_HR(   hr,  (  _T(  "Failed(0x%1xL): unable to obtain device  GUID from string\n"  ),  hr  )  );
		PropVariantClear(  &value  );

		SAFE_RELEASE(  deviceProperties  );

		if(  IsEqualIID(  enumGUID,  *guid  )  )  {
			*resultDevice  =  device;
			*resultIndex  =  index;
			hr  =  S_OK;
			break;
		}  
		else{
			SAFE_RELEASE(  device  );
		}
	}
error:
	if(  hitAnError  ){
		SAFE_RELEASE(  device  );
		SAFE_RELEASE(  deviceProperties  );
	}
	return  hr;
}




int aec_snd_StartRecording(  int  samplesPerSec,  int  stereo,  int  semaIndex,  LPGUID  lpGuid_recorder  )
{
	int  iErr  =  -1;
	QY_MC						*	pQyMc						=	QY_GET_GBUF(  );
	MC_VAR_isCli				*	pProcInfo					=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	CAP_procInfo_recordSound  *  pRecordSoundProcInfo  =  &pProcInfo->av.localAv.recordSoundProcInfo;

	if  (  !lpGuid_recorder  )  return  -1;
	
	//  We don't support stereo for now.IMPORTANT: if we change this,  we also need to change aec_snd_RecordSamplesIntoAtLength(  ),  which assumes 2 bytes/sample.
	if  (  stereo  )  {
		printf(  "sound_startRecording: stereo not supported; recording not started\n"  );
		return  -1;
	}


#if  1		//  def  __DEBUG__


#if  0
	static  BOOL  bInited  =  FALSE;
	if  (  !bInited  )  {
		bInited  =  TRUE;
		dx_soundInit(  );
		getNumberOfSoundPlayerDevices(  );
		getNumberOfSoundRecorderDevices(  );
	}
#endif

	//
		OLD_audioDevice	oldDev_render;
		if  (  getDefaultPlaybackDevice(  &oldDev_render  )  )  return  -1;
		//  setDeviceGUID(  &playerDevices.defaultDevice,  &oldDev.guid_audio  );
		//  setDeviceGUID(  &recorderDevices.defaultDevice,  lpGuid_recorder  );
		safeTcsnCpy(  oldDev_render.names_audio,  pRecordSoundProcInfo->aec_rendDevDesc,  mycountof(  pRecordSoundProcInfo->aec_rendDevDesc  )  );

		traceLog(  _T(  "AECTEST:"  )  );
#endif

	recSampleRate  =  samplesPerSec;
	recIsStereo  =  stereo;
	recSemaphore  =  semaIndex;

#if  0
	if  (  g_aecRingBuffer  )  aec_snd_StopRecording(  );
#endif
	
	printf(  "sound_startRecording:  beginning DMO AEC audio capture\n"  );
	printf(  "\tsampleRate:%d stereo:%d sem-index:%d\n",  samplesPerSec,  stereo,  semaIndex  );

#if  0
	//  Allocate a ring-buffer with enough room for 1280ms of  16kHz 16-bit sound
	g_aecRingBuffer  =  new  Qwaq::QRingBuffer(  40960  );
	if  (  !g_aecRingBuffer  )  {
		printf(  "sound_startRecording:  failed to allocate ring-buffer\n"  );
		//  return  0;
		goto  error;
	}
#endif


	IMMDeviceEnumerator  *  enumerator  =  NULL;
	IMMDeviceCollection  *  deviceCollection  =  NULL;
	IMMDevice  *  device  =  NULL;
	IPropertyStore  *  dmoProperties  =  NULL;
	IPropertyStore  *  deviceProperties  =  NULL;
	bool  isArrayDevice;
	LPGUID  renderGUID  =  &oldDev_render.guid_audio;	//  playerDevices.defaultDevice.guid;
	LPGUID  captureGUID  =  lpGuid_recorder;			//  recorderDevices.defaultDevice.guid;
	int renderDeviceIndex  =  -1;
	int captureDeviceIndex  =  -1;
	HRESULT  hr;
	bool  hitAnError  =  false;


	hr  =  CoCreateInstance(  CLSID_CWMAudioAEC,  NULL, CLSCTX_INPROC_SERVER,  IID_IMediaObject,  (  void  **)&lpDMO  );	
	CHECK_START_RECORDING_HR(  hr,  (  _T(  "FAILED(0x%1xL): cannot instantiate the DMO\n"  ),  hr  )  );


	hr  =  lpDMO->QueryInterface(  IID_IPropertyStore,  (  void  **  )&dmoProperties  );
	CHECK_START_RECORDING_HR(  hr,  (  _T(  "Failed(0x%1xL): cannot obtain DMO's property-store\n"  ),  hr  )  );

	
	//
	hr  =  CoCreateInstance(  __uuidof(MMDeviceEnumerator),  NULL,  CLSCTX_INPROC_SERVER,  __uuidof(IMMDeviceEnumerator),  (  void  **  )&enumerator  );
	CHECK_START_RECORDING_HR(  hr,  (  _T(  "Failed(0x%1xL): cannot instantiate device-enumerator\n"  ),  hr  )  );


	//
	hr  =  enumerator->EnumAudioEndpoints(  eRender,  DEVICE_STATE_ACTIVE,  &deviceCollection  );
	CHECK_START_RECORDING_HR(  hr,  (  _T(  "Failed(0x%1xL): cannot enumerate audio-playback device\n"  ),  hr  )  );


	hr  =  aec_findDeviceWithGUID(  deviceCollection,  renderGUID,  &device,  &renderDeviceIndex  );
	CHECK_START_RECORDING_HR(  hr,  (  _T(  "Failed(0x%1xL),  cannot find matching audio-playback device\n"  ),  hr  )  );
	SAFE_RELEASE(  deviceCollection  );
	SAFE_RELEASE(  device  );

	//
	hr  =  enumerator->EnumAudioEndpoints(  eCapture,  DEVICE_STATE_ACTIVE,  &deviceCollection  );
	CHECK_START_RECORDING_HR(  hr,  (  _T(  "Failed(0x%1xL),  cannot enumerate audio-capture device\n"  ),  hr  )  );
	hr  =  aec_findDeviceWithGUID(  deviceCollection,  captureGUID,  &device,  &captureDeviceIndex  );
	CHECK_START_RECORDING_HR(  hr,  (  _T(  "Failed(0x%1xL), cannot find matching audio-capture device\n"  ),  hr  )  );

	hr  =  EndpointIsMicArray(  device,  isArrayDevice  );
	CHECK_START_RECORDING_HR(  hr,  (  _T(  "Failed(0x%1xL),  unable to determine whether device is a mic_array\n"  ),  hr  )  );

	SAFE_RELEASE(  deviceCollection  );
	SAFE_RELEASE(  device  );

	if  (  captureDeviceIndex  <  0  ||  renderDeviceIndex  <  0  )  {
		goto  error;
	}

	DPRINTF( (  _T(  "matched render and capture devices %d and %d\n"  ),  renderDeviceIndex,  captureDeviceIndex  ));

	//  Set DMO system mode
	{
		PROPVARIANT  systemMode;
		PropVariantInit(  &systemMode  );
		systemMode.vt  =  VT_I4;

		if  (  isArrayDevice  )  {
			DPRINTF( ( _T(  "Found mic array,  so using mode:OPTIBEAM_ARRAY_AND_AEC\n"  )  ));
			systemMode.lVal  =  (  LONG  )OPTIBEAM_ARRAY_AND_AEC;
			//
			DPRINTF( ( _T(  "For safety/compatibility,  forcing mode:SINGLE_CHANNEL_AEC\n"  ) ) );
			systemMode.lVal  =  (  LONG  )SINGLE_CHANNEL_AEC;
		}
		else  {
			DPRINTF( ( _T(  "Found single channel mic,so using mode:SINGLE_CHANNEL_AEC\n"  )  )  );
			systemMode.lVal  =  (  LONG  )SINGLE_CHANNEL_AEC;
		}
		hr  =  dmoProperties->SetValue(  MFPKEY_WMAAECMA_SYSTEM_MODE,  systemMode  );
		CHECK_START_RECORDING_HR(  hr,  (  _T(  "Failed(0x%1xL),  cannot set system mode\n"  ),  hr  )  );
		hr  =  dmoProperties->GetValue(  MFPKEY_WMAAECMA_SYSTEM_MODE,  &systemMode  );
		CHECK_START_RECORDING_HR(  hr,  (  _T(  "Failed(0x%1xL), readback of system mode failed\n"  ),  hr  )  );
		PropVariantClear(  &systemMode  );
	}

	//  Set the capture & render device for the DMO to use
	{
		PROPVARIANT  deviceIDs;
		PropVariantInit(  &deviceIDs  );
		deviceIDs.vt  =  VT_I4;
		deviceIDs.lVal  =  (  unsigned long  )(  renderDeviceIndex <<  16  ) + (  unsigned long  )(  0x0000ffff & captureDeviceIndex  );

		hr  =  dmoProperties->SetValue(  MFPKEY_WMAAECMA_DEVICE_INDEXES,  deviceIDs  );
		CHECK_START_RECORDING_HR(  hr,  (  _T(  "Failed(0x%1xL),  cannot set device IDs\n"  ),  hr  )  );
		hr  =  dmoProperties->GetValue(  MFPKEY_WMAAECMA_DEVICE_INDEXES,  &deviceIDs  );
		CHECK_START_RECORDING_HR(  hr,  (  _T(  "Failed(0x%1xL), readback of deviceIDs failed\n"  ),  hr  )  );
		PropVariantClear(  &deviceIDs  );
	}

	//  Turn off additional feature modes.
	{
		PROPVARIANT  shouldEnableExtraFeatures;
		PropVariantInit(  &shouldEnableExtraFeatures  );
		shouldEnableExtraFeatures.vt  =  VT_BOOL;
		shouldEnableExtraFeatures.boolVal  =  (  VARIANT_BOOL  )0;

		hr  =  dmoProperties->SetValue(  MFPKEY_WMAAECMA_FEATURE_MODE,  shouldEnableExtraFeatures  );
		CHECK_START_RECORDING_HR(  hr,  (  _T(  "Failed(0x%1xL),  cannot disable extra features\n"  ),  hr  )  );
		hr  =  dmoProperties->GetValue(  MFPKEY_WMAAECMA_FEATURE_MODE,  &shouldEnableExtraFeatures  );
		CHECK_START_RECORDING_HR(  hr,  (  _T(  "Failed(0x%1xL),  cannot tell if extra features are enabled\n"  ),  hr  )  );
		PropVariantClear(  &shouldEnableExtraFeatures  );
	}

	//  Set DMO output format
	{
		DMO_MEDIA_TYPE  mediaType  = {0};
		WAVEFORMATEX  wfxOut  =  {WAVE_FORMAT_PCM, 1,  recSampleRate,  recSampleRate * 2, 2, 16, 0 };

		hr  =  MoInitMediaType(  &mediaType,  sizeof(  WAVEFORMATEX  )  );
		CHECK_START_RECORDING_HR(  hr,  (  _T(  "Failed(0x%1xL),  cannot init media-type object\n"  ),  hr  )  );

		mediaType.majortype  =  MEDIATYPE_Audio;
		mediaType.subtype  =  MEDIASUBTYPE_PCM;
		mediaType.bFixedSizeSamples  =  TRUE;
		mediaType.bTemporalCompression  =  FALSE;
		mediaType.lSampleSize  =  0;
		mediaType.formattype  =  FORMAT_WaveFormatEx;
		memcpy(  mediaType.pbFormat,  &wfxOut,  sizeof( WAVEFORMATEX ) );

		hr  =  lpDMO->SetOutputType(  0,  &mediaType,  0  );
		MoFreeMediaType(  &mediaType );
		CHECK_START_RECORDING_HR(  hr,  (  _T(  "Failed(0x%1xL),  cannot set Dmo output format\n"  ),  hr  )  );
	}

	//  Final Dmo preparations...
	{
		hr  =  lpDMO->AllocateStreamingResources();
		CHECK_START_RECORDING_HR(  hr,  (  _T(  "Failed(0x%1xL),  cannot AllocateStreamingResources\n"  ),  hr  )  );

		PROPVARIANT  frameSize;
		PropVariantInit(  &frameSize  );
		hr  =  dmoProperties->GetValue(  MFPKEY_WMAAECMA_FEATURE_MODE,  &frameSize  );
		CHECK_START_RECORDING_HR(  hr,  (  _T(  "Failed(0x%1xL),  cannot get frameSize\n"  ),  hr  )  );
		DPRINTF(  (  _T(  "Read frame size: %d\n"  ),  frameSize.lVal  ) );
		PropVariantClear(  &frameSize  );
	}

	//  Create  the thread
	pRecordSoundProcInfo->thread.hThread  =  CreateThread(  NULL,  128*1024,  aecRecThreadFunc,  NULL,  STACK_SIZE_PARAM_IS_A_RESERVATION,  NULL  );
	if  (  !pRecordSoundProcInfo->thread.hThread  )  {
		CHECK_START_RECORDING_HR(  E_FAIL,  (  _T(  "Failed: CreateThread() in aec_snd_StartRecording\n"  ),  hr  )  );
	}
	if  (  !SetThreadPriority(  pRecordSoundProcInfo->thread.hThread,  THREAD_PRIORITY_HIGHEST  )  )  {
		DPRINTF(  (  _T(  "Warning: SetThreadPriority failed in aec_snd_StartRecording\n"  )  ) );
	}

	//
	iErr  =  0;

error:
	
	if  (  iErr  )  {	
		//  if  (  hitAnError  )  
		{	 
			aec_snd_StopRecording();  
		};
	}

	SAFE_RELEASE(  dmoProperties  );
	SAFE_RELEASE(  enumerator  );
	SAFE_RELEASE(  deviceCollection  );
	SAFE_RELEASE(  device  );
	SAFE_RELEASE(  deviceProperties  );

	return  iErr;
}

#undef  CHECK_START_RECORDING_HR

DWORD  WINAPI  aecRecThreadFunc(  LPVOID ignored  )
{
	int								iErr						=	-1;
	QY_MC						*	pQyMc						=	QY_GET_GBUF(  );
	MC_VAR_isCli				*	pProcInfo					=	QY_GET_procInfo_isCli(  );
	if  (  !pProcInfo  )  return  -1;
	CAP_procInfo_recordSound  *  pRecordSoundProcInfo  =  &pProcInfo->av.localAv.recordSoundProcInfo;

	CQyMalloc						mallocObj_pAudioDataBuf;
	 char						*	pAudioDataBuf				=	NULL;
	 int							dataLen_pAudioDataBuf		=	0;

	 CQyMalloc						mallocObj_pMsgBuf;
	 MIS_MSGU					*	pMsgBuf						=	(  MIS_MSGU  *  )mallocObj_pMsgBuf.malloc(  CONST_iAllocType_longTimeMsg,  sizeof(  MIS_MSGU  )  );
	 if  (  !pMsgBuf  )  return  -1;

	 traceLogA(  "recordSound enters"  );



	 //
	CStaticMediaBuffer mediaBuffer;	
	const  DWORD gBufLen = 32000;	//  16000 samples, 2bytes each
	BYTE  gBuf[gBufLen];

	mediaBuffer.Init(  (byte*)gBuf,  gBufLen,  0  );
	DMO_OUTPUT_DATA_BUFFER dmoBuffer  =  {0};
	dmoBuffer.pBuffer  =  &mediaBuffer;

	//
	 int	bufSize_pAudioDataBuf  =  pProcInfo->cfg.uiBufSize_myPlayAudioData;
	 if  (  !(  pAudioDataBuf  =  (  char  *  )mallocObj_pAudioDataBuf.malloc(  bufSize_pAudioDataBuf  )  )  )  goto  errLabel;

	 int	iCapTimeInMs  =  40;
	 int  nBytes_toRecord  =  pRecordSoundProcInfo->compressAudio.compressor.uiBytesRecorded_perBlockAlign  *  pRecordSoundProcInfo->compressAudio.ah_decompress.wfx.nBlockAlign;
	 int  nAvgBytesPerSec  =  pRecordSoundProcInfo->compressAudio.ah_decompress.wfx.nAvgBytesPerSec;
	 
	 if  (  !nAvgBytesPerSec  )  goto  errLabel;
	 if  (  iCapTimeInMs  <=  10  )  goto  errLabel;
	 
	 //
	 pRecordSoundProcInfo->thread.bQuit  =  FALSE;
	 pRecordSoundProcInfo->thread.bRunning  =  TRUE;
	 pRecordSoundProcInfo->usErrors_processInput  =  0;
	 
	 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "AEC record sound starts"  )  );

	 //
	 broadcastRecorderStatus(  pQyMc  );

	//
	int  loopin  =  0;
	while( 1)  {

		//  DWORD  waitResult  =  WaitForSingleObject(  hRecEvent,  iCapTimeInMs  );
		Sleep(  iCapTimeInMs  );

		if  (  pRecordSoundProcInfo->thread.bQuit  )  break;
		
		do  {
			//  reset
			mediaBuffer.SetLength(0);
			dmoBuffer.dwStatus  =  0;

			BOOL		bInputErr_aec  =  FALSE;
			HRESULT		hr;
			DWORD		dataLength  =  0;
			DWORD		ignored;
			hr  =  lpDMO->ProcessOutput(  0,  1,  &dmoBuffer,  &ignored  );
			if  (FAILED(hr)) {
				bInputErr_aec  =  TRUE;

				#ifdef  __DEBUG__
						traceLog(  _T(  "DMO->ProcessOutput() failed: 0x%1xL\n"  ),  hr  );
				#endif
				qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "aecRec: DMO->ProcessOutput() failed: 0x%1xL\n"  ),  hr  );
				}
			else  if  (  hr  ==  S_FALSE  ){
					  DPRINTF(  (  _T(  "no data for you\n"  )  ) );
					  }
			else  {
				hr  =  mediaBuffer.GetBufferAndLength(NULL,  &dataLength);
				if  (FAILED(hr)) {
				DPRINTF(  (  _T(  "failed to get data length\n"  )  ) );
				}
				else {
					#if  0
					try {  g_aecRingBuffer->put(  gBuf,  dataLength  );  }
					catch  ( std::string ex )  {
						DPRINTF(  (  _T(  "failed to stash mic input into ring buffer\n"  )  ) );
					}
					#endif

					//
					#ifdef  _DEBUG
							#if  0
							TCHAR	tBuf[128]  =  _T(  ""  );
							_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "get audio %d bytes\n"  ),  dataLength  );
							OutputDebugString(  tBuf  );
							#endif
					#endif

					//
					if  (  dataLength  +  dataLen_pAudioDataBuf  <  bufSize_pAudioDataBuf  )  {
						memcpy(  pAudioDataBuf  +  dataLen_pAudioDataBuf,  gBuf,  dataLength  );
						dataLen_pAudioDataBuf  +=  dataLength;
					}

				}
			}

			//
			if  (  pRecordSoundProcInfo->bInputErr_aec  !=  bInputErr_aec  )  pRecordSoundProcInfo->bInputErr_aec  =  bInputErr_aec;
			if  (  pRecordSoundProcInfo->bInputErr_aec  
				||  !pProcInfo->av.localAv.player.audio.bRunning  )  
			{	//  2013/05/26
				DWORD	dwTickCnt  =  GetTickCount(  );
				int  iDiff  =  dwTickCnt  -  pRecordSoundProcInfo->dwLastTickCnt_toStartLocalAudioPlayer;
				if  (  abs(  iDiff  )  >  1000  )  {
					pRecordSoundProcInfo->dwLastTickCnt_toStartLocalAudioPlayer  =  dwTickCnt;
					//
					PostMessage(  pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_toStartLocalAudioPlayer,  0  );
					if  (  pRecordSoundProcInfo->bInputErr_aec  )  {
						qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "aecRec: postMsg to notify inputErr"  )  );				
						showNotification(  0,  0,  0,  0,  0,  0,  _T(  "aecRec: inputErr, notify"  )  );
						}
					else  {
						  qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "aecRec: postMsg to start local audio player"  )  );				
					}
				}
			}
				

			

		}  while  (  dmoBuffer.dwStatus  &  DMO_OUTPUT_DATA_BUFFERF_INCOMPLETE  );

		//
		#ifdef  _DEBUG
				TCHAR	tBuf[128]  =  _T(  ""  );
				_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "get audio %d bytes\n"  ),  dataLen_pAudioDataBuf  );
				OutputDebugString(  tBuf  );
		#endif


		for  (  ;  ;  )  {
			 if  (  dataLen_pAudioDataBuf  <  nBytes_toRecord  )  break;								
			 //
			 processInput_post(  pProcInfo,  nAvgBytesPerSec,  (  BYTE  *  )pAudioDataBuf,  nBytes_toRecord,  pMsgBuf  );				    					
			 memcpy(  pAudioDataBuf,  pAudioDataBuf  +  nBytes_toRecord,  dataLen_pAudioDataBuf  -  nBytes_toRecord  );
			 dataLen_pAudioDataBuf  -=  nBytes_toRecord;			 
		}			
	
	}

	iErr  =  0;

errLabel:


	pRecordSoundProcInfo->thread.bRunning  =  FALSE;

	 qyShowInfo(  CONST_qyShowType_qwmComm,  0,  "",  pProcInfo->who_showInfo,  0,  _T(  ""  ),  _T(  ""  ),  _T(  "AEC record sound ends"  )  );
	 
	 broadcastRecorderStatus(  pQyMc  );

	return  iErr;

}
