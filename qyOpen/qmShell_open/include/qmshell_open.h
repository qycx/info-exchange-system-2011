

#ifndef  __QMSHELLOPEN_H__
#define  __QMSHELLOPEN_H__	//  {


typedef  struct  __capRect_t										{
				 int												iX,  iY;				//  
				 unsigned  int										iW,  iH;				 
}		 CAP_RECT;


typedef  BOOL (  WINAPI  *  PF_SetDlgItemText  )( HWND hDlg, int nIDDlgItem, LPCTSTR lpString  ); 
typedef  UINT (  WINAPI  *  PF_GetDlgItemText  )( HWND hDlg, int nIDDlgItem, LPTSTR lpString, int nMaxCount  ); 

typedef  int  (  WINAPI  *  PF_MessageBox  )(  HWND hWnd ,  LPCTSTR lpText,  LPCTSTR lpCaption,  UINT uType  );


typedef  struct  __gGuiData_qyMc_t									{
				 BOOL												bInited;

				 //
				 void										*		pCusRes;

				 //
				 void										*		pf_MessageBox;							//  2010/08/11
				 //  void										*		pf_showDlgMcClientLogon;
				 void										*		pf_showDlgQnmCfgOptionsIsClient;

				 void										*		pf_newDlgTalk_ce;
				 void										*		pf_newDlgInstantAssistant;

				 //
				 float												fx;
				 float												fy;
				 int												iH_listFont_default;
				 HFONT												hFont_list;
				 int												iH_listFont_text_default;
				 HFONT												hFont_list_text;
				 int												iH_static_default;
				 HFONT												hFont_static;
				 int												iH_btn_default;							//  2011/03/27
				 HFONT												hFont_btn;
				 int												iH_bar_default;							//  2011/03/27
				 HFONT												hFont_bar;
				 int												iH_menu_default;
				 HFONT												hFont_menu;

 
				 //
				 int												lfHeight_videoHint_320x240;
				 HFONT												hFont_videoHint_320x240;				//  2011/08/10
				 int												lfHeight_videoHint_640x480;
				 HFONT												hFont_videoHint_640x480;				//  2011/08/05
				 int												lfHeight_videoHint_1280x720;
				 HFONT												hFont_videoHint_1280x720;				//  2011/08/05
				 int												lfHeight_videoHint_1920x1080;
				 HFONT												hFont_videoHint_1920x1080;				//  2011/08/05
				 //
				 int												lfHeight_demoHint_screen;
				 HFONT												hFont_demoHint_screen;					//  2011/07/26

}		 G_guiData_qyMc;

__declspec(  dllexport  )  int  centerWnd(  HWND  hWnd  );
__declspec(  dllexport  )  int  makeDlgResizable(  HWND  hDlg  );
__declspec(  dllexport  )  int  makeWndNoBorder(  HWND  hWnd,  BOOL  bThin,  HMENU  *  phMenu,  long  *  plStyle  );
int  restoreWndBorder(  HWND  hWnd,  HMENU  *  phMenu,  long  *  plStyle  );




G_guiData_qyMc  *  get_g_guiData(  );

HINSTANCE  get_my_hInst(  );


__declspec(  dllexport  )  void  *  newQyWnd(  int  iWndContentType  );
__declspec(  dllexport  )  void  freeQyWnd(  void  *  pWnd  );
__declspec(  dllexport  )  void  *  qyWnd_getGuiData(  void  *  pDlg  );
__declspec(  dllexport  )  void  *  qyWnd_getVar(  void  *  pDlg  );
__declspec(  dllexport  )  HWND  qyWnd_getHwnd(  void  *  pDlg  );
__declspec(  dllexport  )  BOOL  qyWnd_Attach(  void  *  pDlgParam,  HWND hWndNew  );

__declspec(  dllexport  )  int	initQyMc(  HINSTANCE  g_hInst  );
__declspec(  dllexport  )  void	 exitQyMc(  );

 __declspec(  dllexport  )  int  qyShowMainWnd(  HWND  hMainWnd,  void  *  pVar  );
 __declspec(  dllexport  )  int  initVar_onCreate_mainFrame(  void  *  p0,  HWND  hMainWnd,  void  *  pVarParam  );
 __declspec(  dllexport  )  int  exitVar_onDestroy_mainFrame(  void  *  p0,  HWND  hMainWnd,  void  *  pVarParam  );

 
 __declspec(  dllexport  )  int  mainWnd_OnQyQuitMainWnd(  HWND  hMainWnd,  void  *  pVar  );
 __declspec(  dllexport  )  int  mainWnd_OnClose(  HWND  hMainWnd,  void  *  pVar  );
 __declspec(  dllexport  )  int  mainWnd_OnTimer(  HWND  hMainWnd,  void  *  pVar,  UINT  nIDEvent  );

 __declspec(  dllexport  )  BOOL  dlgObjs_bFillContent(  HWND  hDlg,  void  *  pVar,  int  iObjType  );
 __declspec(  dllexport  )  int dlgObjs_OnOK(  HWND  hDlg,  void  *  pVarParam  );
 __declspec(  dllexport  )  int dlgObjs_OnLbnSelchangeList0(  HWND  hDlg,  void  *  pVarParam  );
 
 __declspec(  dllexport  )  int dlgMcClientLogon_OnInitDialog(  HWND  hDlg,  void  *  pVarParam  );
 __declspec(  dllexport  )  int dlgMcClientLogon_OnDestroy(  HWND  hDlg,  void  *  pVarParam  );
 __declspec(  dllexport  )  void dlgMcClientLogon_OnCbnSelchangeCombologonserver(  HWND  hDlg,  void  *  pVarParam  );


 //  __declspec(  dllexport  )  BOOL  myDialogProc_mcClientLogon(  void  *  pDlgParam,  HWND hDlg,  UINT uMsg,  WPARAM wParam,  LPARAM lParam  );
 __declspec(  dllexport  )  BOOL  myDialogProc_qyMc_winCe(  void  *  pDlg,  HWND hDlg,  UINT uMsg,  WPARAM wParam,  LPARAM lParam  );
 //  __declspec(  dllexport  )  BOOL  myDialogProc_objs(  void  *  pDlg,  HWND hDlg,  UINT uMsg,  WPARAM wParam,  LPARAM lParam  );
 __declspec(  dllexport  )  BOOL  myDialogProc_qnmCfgOptionsIsClient(  void  *  pDlgParam,  HWND hDlg,  UINT uMsg,  WPARAM wParam,  LPARAM lParam  );
 __declspec(  dllexport  )  BOOL  myDialogProc_talk_ce(  void  *  pDlgParam,  HWND hDlg,  UINT uMsg,  WPARAM wParam,  LPARAM lParam  );

 //  __declspec(  dllexport  )  INT_PTR CALLBACK dlgProc_instantAssistant(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


 __declspec(  dllexport  )  BOOL  dlgTalk_bRefresh(  void  *  pDlgTalkParam,  LPCTSTR  hint,  BOOL  bChanged_layout  =  FALSE,  BOOL  bChanged_status  =  FALSE  );
 //  __declspec(  dllexport  )  BOOL  dlgTalk_bSelTask(  void  *  pDlgTalkParam,  LPCTSTR  selStr  );
 __declspec(  dllexport  )  BOOL  dlgTalk_bSelTask(  HWND  hDlg,  LPCTSTR  selStr  );
 __declspec(  dllexport  )  BOOL  dlgTalk_bQuitDlg(  void  **  ppDlgTalkParam,  BOOL  bCancelTasks  );
 __declspec(  dllexport  )  BOOL  dlgTalk_canSpeak(  HWND  hDlgTalk  );

 __declspec(  dllexport  )  int  talkToMessenger(  unsigned  __int64  ui64Id,  BOOL  bNeedNotShowWnd,  BOOL  bActivateWnd,  HWND  *  phWnd  );
 __declspec(  dllexport  )  int  procTalkTo(  HWND  hDlgTalk,  LPCTSTR  inputStr  );

 __declspec(  dllexport  )  int dlgQnmCfgOptionsIsClient_OnInitDialog(  HWND  hDlg,  void  *  pVarParam  );
 __declspec(  dllexport  )  void dlgQnmCfgOptionsIsClient_OnOK(  HWND  hDlg  );
 __declspec(  dllexport  )  int	 dlgMcClientLogon_refresh(  HWND  hDlg  );
 void dlgMcClientLogon_OnTimer(  HWND  hDlg,  UINT_PTR nIDEvent);
 __declspec(  dllexport  )  int dlgMcClientLogon_OnOK(  HWND  hDlg,  LPTSTR  m_name,  LPTSTR  m_passwd  );


//  2010/08/11
typedef  struct  __dlgGuiData_MessageBox_t							{
				 int												iIDOK;
				 int												iIDCANCEL;
				 int												iIDC_STATIC_hint;

				 PF_SetDlgItemText									pf_SetDlgItemText;		
				 PF_GetDlgItemText									pf_GetDlgItemText;		

				 TCHAR										*		lpText;
				 TCHAR										*		lpCaption;
				 UINT												uType;

}		 DLG_guiData_MessageBox;

//
typedef  struct  __wndGuiData_main_t								{
				 int												iIDC_BUTTON_contact;
				 int												iIDC_BUTTON_group;
				 int												iIDC_BUTTON_bar;
				 //
				 #ifdef  __WINCE__
						 int										iIDC_BUTTON_status;
				 #endif
				 //
				 int												w_org,  h_org;
				 RECT												rcIDC_BUTTON_contact;	
				 RECT												rcIDC_BUTTON_group;
				 RECT												rcIDC_BUTTON_bar;
				 //
				 void										*		pf_displayNotification_mainWnd;	//  (  void  *  pDlg,  HWND  hDlg,  LPCTSTR  hint  )

}		 WND_guiData_main;


//
typedef  struct  __dlgGuiDataMcClientLogon_t						{
				 BOOL												bInited;

				 int												iIDC_STATIC_logonServer;
				 int												iIDC_COMBO_logonServer;
				 int												iIDC_STATIC_usrName;
				 int												iIDC_NAME;
				 int												iIDC_STATIC_passwd;
				 int												iIDC_PASSWD;
				 int												iIDC_STATIC_hint;
				 int												iIDOK;
				 int												iIDCANCEL;
				 int												iIDC_BUTTON_option;
				 
				 PF_SetDlgItemText									pf_SetDlgItemText;		
				 PF_GetDlgItemText									pf_GetDlgItemText;		

				 //  2011/02/27
				 int												w_org,  h_org;
				 RECT												rcIDC_STATIC_logonServer;	
				 RECT												rcIDC_COMBO_logonServer;
				 RECT												rcIDC_STATIC_usrName;
				 RECT												rcIDC_NAME;
				 RECT												rcIDC_STATIC_passwd;
				 RECT												rcIDC_PASSWD;
				 RECT												rcIDC_STATIC_hint;
				 RECT												rcIDOK;	
				 RECT												rcIDC_BUTTON_option;	
				 RECT												rcIDCANCEL;	



}		 DLG_guiData_mcClientLogon;

//
typedef  struct  __dlgGuiDataParamObjs_t							{
				 unsigned  int										uiType;
				 //
				 unsigned  char										ucbActiveTalker;				//  2012/04/21
				 //
				 HWND												hCurTalk;
				 void										*		pCurVar;						//  2013/0610
				 void										*		pMgrVar;
				 //
				 void										*		p0;								//  2013/04/04
				 int												iMenuId_selectedDev;

				 //
				 struct												{
					 unsigned  __int64								ui64Id_selected;
					 
					 //  2013/02/13
					 //  int											iRedId_selectRemoteVideo;		//  2013/02/13

					 //  2013/06/24
					 int											iVal_selected;
					 
					 //  2013/04/04
					 int											iSel;

				 }													o;

}		 DLG_guiDataParam_objs;

typedef  struct  __dlgGuiDataObjs_t									{
				 DLG_guiDataParam_objs								param;

				 BOOL												bInited;						//  2011/03/03

				 int												iIDC_LIST0;
				 int												iIDC_BUTTON_contact;
				 int												iIDC_BUTTON_group;
				 int												iIDC_BUTTON_status;
				 int												iIDCANCEL;
				 int												iIDOK;

				 //
 				 int												w_org,  h_org;
				 RECT												rcIDC_LIST0;
				 RECT												rcIDC_BUTTON_contact;
				 RECT												rcIDC_BUTTON_group;
				 RECT												rcIDC_BUTTON_status;
				 RECT												rcIDCANCEL;
				 RECT												rcIDOK;
}		 DLG_guiData_objs;

typedef  struct  __dlgGuiDataMsgList_t								{
				 //  DLG_guiDataParam_objs								param;

				 BOOL												bInited;			//  2011/03/03

				 int												iIDC_LIST_msg;
				 int												iIDC_BUTTON_export;
				 int												iIDC_BUTTON_clear;
				 int												iIDCANCEL;

				 //
 				 int												w_org,  h_org;
				 RECT												rcIDC_LIST_msg;
				 RECT												rcIDC_BUTTON_export;
				 RECT												rcIDC_BUTTON_clear;
				 RECT												rcIDCANCEL;
}		 DLG_guiData_msgList;



typedef  struct  __dlgGuiDataQnmCfgOptionsIsClient_t				{
				 BOOL												bInited;

				 int												iIDC_STATIC_centerAddr;				// group
				 int												iIDC_STATIC_cntAddr0;				// static
				 int												iIDC_cntIp;
				 int												iIDC_STATIC_cntAddr1;				// static			
				 int												iIDC_EDIT_cntAddr1;
				 int												iIDC_STATIC_cntAddr2;				// static
				 int												iIDC_EDIT_cntAddr2;
				 int												iIDC_STATIC_cntName;				// static
				 int												iIDC_cntName;
				 int												iIDC_STATIC_cntPort;				// static
				 int												iIDC_cntPort;
				 //  int												iIDC_STATIC_centerAddr;
				 //
				 int												iIDC_CHECK_useDb;					//  2013/02/20
				 //
				 int												iIDOK;
				 int												iIDCANCEL;
				 //
				 int												iIDC_BUTTON_more;					//  2012/02/19
				 //
				 int												iIDC_LIST_vcServer;
				 int												iIDC_ADD;
				 int												iIDC_MODIFY;
				 int												iIDC_DEL;

				 //
				 PF_SetDlgItemText									pf_SetDlgItemText;		
				 PF_GetDlgItemText									pf_GetDlgItemText;		

				 //  for modification
				 int												iParam_qyDlgType;
				 RECT												rc;
				 int												iItemSelected;

				 //
				 BOOL												bMore;			//  2012/02/19

				 //
				 int												w_org,  h_org;
				 int												w_org_hideMore,  h_org_hideMore;	//  2012/02/20
				 //
				 RECT												rcIDC_STATIC_centerAddr;
		 		 RECT												rcIDC_STATIC_cntAddr0;				//  2011/02/27
				 RECT												rcIDC_cntIp;
				 RECT												rcIDC_STATIC_cntAddr1;
				 RECT												rcIDC_EDIT_cntAddr1;
				 RECT												rcIDC_STATIC_cntAddr2;
				 RECT												rcIDC_EDIT_cntAddr2;
				 RECT												rcIDC_STATIC_cntName;
				 RECT												rcIDC_cntName;
				 RECT												rcIDC_STATIC_cntPort;
				 RECT												rcIDC_cntPort;
				 //
				 RECT												rcIDC_CHECK_useDb;					//  2013/02/20
				 //
				 RECT												rcIDCANCEL;
				 RECT												rcIDOK;
				 //
				 RECT												rcIDC_BUTTON_more;
				 //
				 RECT												rcIDC_LIST_vcServer;
				 RECT												rcIDC_ADD;
				 RECT												rcIDC_MODIFY;
				 RECT												rcIDC_DEL;



}		 DLG_guiData_qnmCfgOptionsIsClient;


//
#define		CONST_iPageType_null									0
#define		CONST_iPageType_msg										1
#define		CONST_iPageType_task									2
#define		CONST_iPageType_av										3

//
typedef  struct  __dlgGuiDataParamTalk_t							{

				 int												iDlgType;
				 void										*		pAddr;
				 void										*		pTmpGrpMemQ;
				 BOOL												bNeedNotShowWnd;
				 HWND												hFore;
				 //	
				 int												iPageType;

}		 DLG_guiDataParam_talk;



//
typedef  struct  __dlgGuiDataTalk_t									{

				 DLG_guiDataParam_talk								param;
				 BOOL												bInfoSet;


				 //
				 int												iIDC_STATIC_dlgDesc;

				 //				 
				 int												iIDC_LIST_members;		

				 //  2012/05/18
				 int												iIDC_LIST_task;
				 int												iIDC_STATIC_instantStatus;
				 int												iIDC_STATIC_recentMsgList;
				 int												iIDC_STATIC_input;

				 //				 	
				 int												iIDC_STATIC_ptz;				//  2012/09/05
				 //
				 int												iIDC_STATIC_subtitles;			//  2013/04/05

				 //
				 int												iIDC_STATIC_peerDesc;
				 int												iIDC_STATIC_meDesc;
				 int												iIDC_STATIC_otherDesc;			//  2013/02/25
				 
#if  0
				 //
				 int												iIDC_LIST_msg;
				 //  int												iIDC_STATIC_taskStatus;
				 int												iIDC_BUTTON_status;
				 int												iIDCANCEL;
				 int												iIDC_BUTTON_msg;
				 int												iIDC_BUTTON_task;
				 int												iIDC_BUTTON_av;
				 int												iIDC_BUTTON_op1;
				 int												iIDC_BUTTON_op0;
				 //
				 int												iIDC_COMBO_toPath;
#endif


				 void										*		pf_refreshDlg_talk_ce;			//  (  void  *  pDlg,  HWND  hDlg,  void  *  p2  )
				 void										*		pf_sizeAllControls_talk_ce;		//  (  void  *  pDlg,  HWND  hDlg,  void  *  p2  )
				 void										*		pf_displayNotification_talk_ce;	//  (  void  *  pDlg,  HWND  hDlg,  LPCTSTR  hint  )

				 //
				 float												fx,  fy;

				 //
				 unsigned  char										ucbShowDlgDesc;
				 //
				 unsigned  char										ucbShowImGrpMems;				//  2007/06/22
				 //  unsigned  char										ucbShowMsgBox;
				 unsigned  char										snmpbShowMsgBox;				//  2011/10/02
				 //
				 unsigned  char										ucbShowMore;


				 //
				 int												idc_hidden;
				 BOOL												bListHidden;
				 BOOL												bTaskStatusHidden;
				 BOOL												bOp0Hidden;
				 BOOL												bOp1Hidden;
				 //
				 BOOL												bChanged_layout;

				 //				
				 CAP_RECT											peerCapRect,  meCapRect;
				 CAP_RECT											otherCapRect;					//  2013/02/25. 

				 //
				 BOOL												bImGrp;

				 //
				 BOOL												bFinished_createCtrls;
				 BOOL												bCreated;
				 //  2012/05/14
				 //  BOOL												bDone_init_showMsg;

				 //
				 struct												{
					 int											nItems_list;
				 }													msg;
				 struct												{
					 int											nCurSel;
					 struct											{
						 //
						 int										iTaskId;
						 unsigned  int								uiTaskType;
						 int										iStatus;
						 BOOL										bTaskAlive;
					 }												curSel;
					 //
					 int											nItems_list;
				 }													task;
				 struct												{
					 int											iTaskId;
					 int											iStatus;
					 TCHAR											statusDesc[64];
					 //
				 }													av;
				 BOOL												bChanged_status;

 }		  DLG_guiData_talk;


typedef  struct  __dlgGuiDataParamInstantAssistant_t				{	
				 //
				 HWND												hDlgTalk;
				 HWND												hShadow;				//  2012/05/04

				 int												iIDD;
				 int												iStatus;
				 BOOL												bMin;

				 //
				 int												xPos_screen;
				 int												yPos_screen;

}		 DLG_guiDataParam_instantAssistant;		

typedef  struct  __dlgGuiDataInstantAssistant_t						{
				 DLG_guiDataParam_instantAssistant					param;

				 BOOL												bInited;				//  2011/03/25

				 int												iIDC_request;
				 int												iIDC_talkerList;
				 int												iIDC_BUTTON_msgBox;
				 //  int												iIDC_COMBO_usLayoutType;	//  2013/06/24
				 int												iIDC_BUTTON_layoutType;			//  2013/06/24
				 int												iIDC_STATIC_status;

				 //  pc
				 int												iIDC_BUTTON_fullScreen;
				 //  new,2013/02/12
				 int												iIDC_BUTTON_ptzPanel;
				 int												iIDC_BUTTON_remoteVideo;
				 //
				 int												iIDC_BUTTON_subtitles;

				 //  ts
				 int												iIDC_BUTTON_msg;
				 int												iIDC_BUTTON_av;
				 int												iIDC_BUTTON_av_accept;
				 int												iIDC_BUTTON_av_deny;
				 int												iIDC_BUTTON_shareScreen;
				 int												iIDC_BUTTON_enlarge;
				 int												iIDC_BUTTON_close;
				 int												iIDC_BUTTON_more;
				 int												iIDC_BUTTON_rule;
				 int												iIDC_BUTTON_nonexclusive;
				 int												iIDC_BUTTON_shareMediaFile;
				 int												iIDC_BUTTON_showDlgMenu;
				 int												iIDC_BUTTON_closeAndClean;

				 HWND												hParent;

}		  DLG_guiData_instantAssistant;


#ifndef  _USRDLL

		int  gGuiData_init(  G_guiData_qyMc  *  pGuiData  );
		int  gGuiData_exit(  G_guiData_qyMc  *  pGuiData  );


		BOOL WINAPI  mySetDlgItemText( HWND hDlg, int nIDDlgItem, LPCTSTR lpString  );

		int  WINAPI  myMessageBox(  HWND hWnd ,  LPCWSTR lpText,  LPCWSTR lpCaption,  UINT uType  );

		int  showDlgMcClientLogon(  HINSTANCE  g_hInst,  HWND  hMainWnd,  void  *  p2  ); 
	    int  showDlgMcClientDevAuth(  HINSTANCE  g_hInst,  HWND  hMainWnd,  void  *  p2  );

		int  showDlg_qyMc_winCe(  HINSTANCE  g_hInst,  void  *  p1,  void  *  p2  );
		//  int  showDlgObjs(  HINSTANCE  g_hInst,  HWND  hParent,  DLG_guiDataParam_objs  *  pParam  );
		int  showDlgQnmCfgOptionsIsClient(  HINSTANCE  g_hInst,  HWND  hParent,  DLG_guiData_qnmCfgOptionsIsClient  *  pParam  );



		void  *  newDlgTalk_ce(  HINSTANCE  g_hInst,  HWND  hParent,  DLG_guiDataParam_talk  *  pParam  );
	    void  *  newDlgInstantAssistant(  HINSTANCE  g_hInst,  HWND  hParent,  DLG_guiDataParam_instantAssistant  *  pParam  );

#endif


#endif

