

#ifndef  __policyIsClientFunc_h__
#define  __policyIsClientFunc_h__	//  {


//  2011/11/27
#if  0
	#define		CONST_uiMinTimeInMsOfAudioDataPlaying_1s			500
	#define		CONST_uiAudioDataAddedToPlayEveryTime_1s			200
	#define		CONST_uiNotifyIntervalInMs_needMoreAudioData_1s		70
	#define		CONST_uiMaxTimeInMsToPlay_1s						500
	#define		CONST_uiMaxTimeInMsToBeRemoved_1s					200

	//
	#define		CONST_uiMinTimeInMsOfAudioDataPlaying_05s			300
	#define		CONST_uiAudioDataAddedToPlayEveryTime_05s			120
	#define		CONST_uiNotifyIntervalInMs_needMoreAudioData_05s	70
	#define		CONST_uiMaxTimeInMsToPlay_05s						300
	#define		CONST_uiMaxTimeInMsToBeRemoved_05s					60

#else

	// 1.5s,  2012/01/28
	#define		CONST_usMinTimeInMsOfAudioDataPlaying_15s			500
	#define		CONST_usAudioDataAddedToPlayEveryTime_15s			200
	#define		CONST_usNotifyIntervalInMs_needMoreAudioData_15s	70
	#define		CONST_usMinTimeInMsToPlay_15s						650
	#define		CONST_usMaxTimeInMsToPlay_15s						900
	#define		CONST_usMaxTimeInMsToBeRemoved_15s					200
	// 1s
	#define		CONST_uiMinTimeInMsOfAudioDataPlaying_1s			500
	#define		CONST_uiAudioDataAddedToPlayEveryTime_1s			200
	#define		CONST_uiNotifyIntervalInMs_needMoreAudioData_1s		70
	#define		CONST_uiMinTimeInMsToPlay_1s						250
	#define		CONST_uiMaxTimeInMsToPlay_1s						500
	#define		CONST_uiMaxTimeInMsToBeRemoved_1s					200

	//
	#define		CONST_uiMinTimeInMsOfAudioDataPlaying_07s			150
	#define		CONST_uiAudioDataAddedToPlayEveryTime_07s			200
	#define		CONST_uiNotifyIntervalInMs_needMoreAudioData_07s	70
	#define		CONST_uiMinTimeInMsToPlay_07s						100
	#define		CONST_uiMaxTimeInMsToPlay_07s						220
	#define		CONST_uiMaxTimeInMsToBeRemoved_07s					200

	//
	#define		CONST_uiMinTimeInMsOfAudioDataPlaying_05s			150
	#define		CONST_uiAudioDataAddedToPlayEveryTime_05s			120
	#define		CONST_uiNotifyIntervalInMs_needMoreAudioData_05s	70
	#define		CONST_uiMinTimeInMsToPlay_05s						100
	#define		CONST_uiMaxTimeInMsToPlay_05s						150
	#define		CONST_uiMaxTimeInMsToBeRemoved_05s					120

#endif

 int  getDefaultPolicyAvLevel(  unsigned  int  uiCapType,  unsigned int uiSubCapType,  BOOL  bReply  );

#endif  //  }


