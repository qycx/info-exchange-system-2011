

#ifndef  __dlgShareDynBmpsProc_h__
#define  __dlgShareDynBmpsProc_h__	//  {

#include	"gpsCommProc.h"


typedef  struct  __shareDynBmpMem_t			{
				 int						iMenuId;
				 TCHAR						name[32];
				 TCHAR						cusName[32];
				
				 struct						{
					BOOL					bUsing;
					BOOL					bShared;
					//
					int						iIndex_sharedObj;
					unsigned  char			ucbSendLocalScreen;
					unsigned  char			ucbLocalVideoOpen;		
					int						iTaskId;					//  2009/09/13

					//  2012/05/06
					ZONE_PARAM				zoneParam;
				 }							var;

}		 SHARE_dynBmp_mem;								

typedef  struct  __shareDynBmps_t			{
				 unsigned  int				uiObjType;
				 QY_DMITEM				*	pTable_ctrls;
				 unsigned  short			usCnt;
				 SHARE_dynBmp_mem			mems[3];
}		 SHARE_dynBmps;


typedef  struct  __shareGps_t				{

				 BOOL						bShare;

				 struct						{
					 #if 0

						BOOL					bUsing;
					//
					#endif

					//				 
					int						iIndex_sharedObj;
					int						iTaskId;
					//
					DWORD					dwTickCnt_start;
					int						portNo;

					//
					myGPS_POSITION			gpsPos;
					DWORD					dwTickCnt_modified_gpsPos;
				 }							var;

}		 SHARE_gps;								


typedef  struct									{
			CWnd					*		m_pParent;
			int								m_nID;
			BOOL							bInfoSet;
			BOOL							bCreated;					//  Õâ¸ö±êÖ¾Î»ÓÃÀ´±íÃ÷ÊÇ·ñCreate(  )³É¹¦ÁË¡£³É¹¦ÁË£¬Ôò½«×ÊÔ´µÄÊÍ·ÅÁô¸øÁËdlg×Ô¼º(ÔÚPostNcDestroy(  )ÖÐdelete)
			BOOL							bInited;					//  ±íÃ÷htmlEditºÍ¶Ô»°¶¼³õÊ¼»¯ÍêÁË.

			//
			struct							{
				int							iIDC_BUTTON_gps;
				int							iIDC_STATIC_gpsStatus;
				int							iIDC_STATIC_pic0;
			}								guiData;

			//
			MIS_CNT					*		pMisCnt;
			
			BOOL							bUseDirectX;

			int								iW_pic,  iH_pic;

			int								idc;
			HDC								hDc;
			CAP_IMAGES						images;

			//
			void					*		pCapStuff;

			SHARE_dynBmps					shares[2];		//  0 for screen, 1 for webcam

			//
			void					*		pComPort_gps;

			SHARE_gps						share_gps;

			//
			unsigned  int					uiTimerId;
			int								nElapseInMs;
			int								nCtrls;

			//
			unsigned  int					uiTimerId_test;
			int								nElapseInMs_test;
			int								nCtrls_test;

			//
			time_t							tLastModifiedTime;					
			time_t							tLastModifiedTime_ok;			

			MIS_MSGU				*		pMsgBuf_doWnd_guiMsgArrive;			//  2009/12/08

			//
			struct							{
				MIS_MSGU			*		pMsg;
				DWORD						dwTickCnt;							//  dwTickCnt为保存的时刻，如果此包保存时间过长，则清除掉
				unsigned  int				uiObjType;
				int							index_pShare_mem;
			}								recvdReqs[10];						//  2011/10/31. 将收到的获取共享请求都存在这里，然后向服务器发送验证请求，如果允许，则发送reply请求，否则就忽略掉
																		

			//  2011/10/15. 在会议自动响应时，自动触发，并设置此标志, 此窗口应自动置前。在启动摄像机共享后，此标志被复位
			BOOL							bNeed_shareWebcamInConference;

			//  2012/05/08
			BOOL							bLocked_bQuitDlg;

			//  2012/11/27. demo版客户端要求有时间限制.设置此位时,关闭对话框
			BOOL							bTimeoutForDemo_bQuitDlg;

	}										DLG_shareDynBmps_var;


#endif  //  }


