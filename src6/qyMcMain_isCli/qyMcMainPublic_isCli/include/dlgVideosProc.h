
#ifndef  __dlgVideosProc_h__
#define  __dlgVideosProc_h__	//  {


typedef  struct								{

		MIS_CNT						*	pMisCnt;

		BOOL							bClosed;							//  关闭标志位

		BOOL							bUseDirectX;						//  2009/08/06

		TCHAR							title[128  +  1];

		HWND							hDlgTalk;							//  
		int								iTaskId;
		//  
		QY_MESSENGER_ID					idInfo_sender;
		unsigned  int					uiTranNo_openAvDev;
				
		unsigned  char					ucbLocalAv;							//  
		BOOL							bVideoConference;					//  2010/08/30
		BOOL							bRemoteAssist;

		unsigned  int					nElapseInMs;						//  2009/10/14

		BOOL							bSwapMouse;							//  2008/11/16

		struct							{
			BOOL						bInited;							//  2011/03/25
		}								guiData;

		int								idc;
		HDC								hDc;
		CAP_IMAGES						images;
		

		//  2012/05/05
		unsigned  short					usCnt_zoneParams;
		ZONE_PARAM				*		pZoneParams;

		//
		DWORD							dwTickCnt_sendLastMouseMove;		//  200811/22
		unsigned  int					uiEventId_lastRecvd;				//  

		//  
		struct							{		 
			int							x;
			int							y;
			UINT						nFlags;
			BOOL						bMouseMove;
		}								lastMouseEvent;
		BOOL							bNeedSend_lastMouseEvent;			//  是否需要发送

		BOOL							bInstantAssistant;					//  2010/12/24

		BOOL							bMediaControl;						//  2009/04/29
		int								iIndex_capBmp;
		int								iIndex_capAudio;
		HWND							hWnd_mediaControl;	
		DWORD							dwTickCnt_lastViewMediaControl;		//  200811/22

		MIS_MSGU				*		pMsgBuf_doWnd_guiMsgArrive;			//  2009/12/08

	}	DLG_videos_var;



#endif  //  }


