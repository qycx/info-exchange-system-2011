
#ifndef  __MMDEVICEPROC_H__
#define  __MMDEVICEPROC_H__	//  {

typedef  struct  __old_audioDevice_t		{
				 int						iMenuIds_audio;
				 TCHAR						names_audio[128  +  1];
				 GUID						guid_audio;				//  2011/10/23				 
}		 OLD_audioDevice;

	//  2012/01/04
typedef  struct  __old_audioDevices_t		{
				 #if  0
					 int						iMenuIds_audio[10];
					 TCHAR						names_audio[10][128  +  1];
					 GUID						guid_audio[10];				//  2011/10/23				 
				 #endif
				 OLD_audioDevice			mems[10];
				 //
				 int						iNumACapDevices;
				 //
				 int						iMenuId_selectedAudio;
	
}		 OLD_audioDevices;

//  EDataFlow  iEFlow
int  list_devices_a(  BOOL  b_eCapture,  OLD_audioDevices  *  pAudioDevices );
int  getDefaultPlaybackDevice(  OLD_audioDevice  *  pAudioDevice );


#endif  //  }


