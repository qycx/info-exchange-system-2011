

#ifndef  __dlgDynBmpsProc_h__
#define  __dlgDynBmpsProc_h__	//  {


//
#include	"gpsCommProc.h"


#define		DEFAULT_uiInitW_wall	1024  +  30  +  32
#define		DEFAULT_uiInitH_wall	768  +  30  +  32
			

//  2012/05/08
typedef  struct  __wallGpsMgrMem_t				{
				 HWND							hMem;
				 int							iIndex_shadow;

				 //
				 myGPS_POSITION					gpsPos;

				 //
				 int							x,  y,  iW,  iH;
				 UINT							uFlags;

}		 WALL_gps_mgrMem;

typedef  struct									{
			    DWORD							dwTickCnt_lastRefreshed;
				//				
				BOOL							bMoving;
				//
				WALL_gps_mgrMem					mems[350];
}		 WALL_gps_mgr;


//
typedef  struct  __dlgDynBmpsVar_t				{

				 TCHAR							title[128  +  1];

				 MIS_CNT				*		pMisCnt;
				 //
				 BOOL							bUseDirectX;
				 unsigned  char					ucbLocalAv;							//  
				 unsigned  char					ucbAutoSize;						//  2009/10/02

				 unsigned  char					ucbEditable;						//  2009/10/04
				 unsigned  char					ucbShowRules;						//  2009/10/04

				 union							{
					 struct						{
						 char					reserved;
					 }							testLocalWebcam;
					 struct						{
						 unsigned  char			ucbVideoConference;					//  2009/10/14
						 HWND					hDlg_org;							//  2010/08/30

						 QY_MESSENGER_ID			idInfo;								//  2009/09/03
						 unsigned  int			uiObjType;							//  2009/09/03
						 unsigned  short			usIndex;
						 TCHAR					cusName[32];
						 //
						 unsigned  int			uiTranNo_spObj;
				
						 //  2012/04/24
						 struct					{
							 int				zoom;
							 POINT				origin;
						 }						coord;
					 }							vWall;

				 }								u;

				 //
				 CQyVWall				*		pWall;
				 //  2012/04/02
				 void					*		pZoneWall_talkers;					//  WALL_talkers. 在globalVWall里,未指定的talker都放置在这里. 

				 //
				 void					*		pCapStuff;							//  2009/09/09/16

				 BOOL							bGot_sharedObjIndex_localAv;		//  2009/12/28
				 int								iIndex_sharedObj_localAv;

				 UINT							nElapseInMs;
				 UINT_PTR						nTimerId;

				 int							nCtrls;

				 TCHAR							tHint[256];
				 VW_ruleU						rule_sel;

				 //
				 unsigned  char					ucbNeedToChkRules;					//  2012/04/29. 在stopedit后,用这个标志位来促使立即刷新策略. 只触发一次

				 //  2012/05/08
				 CAP_subWnds					subWnds;

				 //  2012/05/08
				 WALL_gps_mgr					wallGpsMgr;

				 //
				 MIS_MSGU				*		pMsgBuf_doWnd_guiMsgArrive;			//  2009/12/08

				 BOOL							bInited;
	
				 //
				 BOOL							bLocked_toQuitDlg;					//  2012/05/08

}		DLG_dynBmps_var;	




#endif  //  }


