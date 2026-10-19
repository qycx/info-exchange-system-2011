

#ifndef  __QYMCMAINCUSMODULEMENU_H__
#define  __QYMCMAINCUSMODULEMENU_H__	//  {

//
#define		CONST_moduleType_null				0
#define		CONST_moduleType_vDev				1
#define		CONST_moduleType_compress			2
#define		CONST_moduleType_camCap				3
//
/*
#define		CONST_moduleType_ipp				4			//  2011/07/31
#define		CONST_moduleType_mediaSdk			5			//  2011/11/25
#define		CONST_moduleType_cuda				6			//  2012/06/17
*/
#define		CONST_moduleType_ipp				50			//  2011/07/31
//  #define		CONST_moduleType_ipp1				51			//  2012/09/15
//
#define		CONST_moduleType_mediaSdk			60			//  2011/11/25
#define		CONST_moduleType_cuda				70			//  2012/06/17




typedef  int  (  *  PF_qyVDev_postStr2Dev  )(  char  *  idStr_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  LPCTSTR  str,  unsigned  int  uiDevType_to,  WCHAR  *  wDevIdStr_to,  WCHAR  *  wForwardPath,  HWND  hWnd_notify,  int  iUsrData  );
typedef  int  (  *  PF_qyVDev_postData2Dev  )(  char  *  idStr_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  void  *  pQyVDevData,  unsigned  int  uiDataLen,  unsigned  int  uiDevType_to,  WCHAR  *  wDevIdStr_to,  unsigned  int  uiDevIndex  );


#define		MACRO_cusModuleCommon				unsigned  int					uiType;								\
												TCHAR							name[32  +  1];						\
												TCHAR							path[MAX_PATH  +  1];				\
												HMODULE							hModule;

typedef  struct  __cusModuleCommon_t			{
				 MACRO_cusModuleCommon
}		 CUS_MODULE_common;

typedef  struct  __cusModuleVDev_t				{
				 MACRO_cusModuleCommon			

				 PF_commonHandler				pf_qyVDev_getPtrProperty;
				 PF_commonHandler				pf_qyVDev_getInfo;
				 PF_commonHandler				pf_qyVDev_getCfg;
				 PF_commonHandler				pf_qyVDev_op;
				 PF_commonHandler				pf_qyVDev_chkBeforeInit;
				 PF_commonHandler				pf_qyVDev_init;
				 PF_commonHandler				pf_qyVDev_chkAfterInit;
				 PF_commonHandler				pf_qyVDev_start;
				 PF_commonHandler				pf_qyVDev_stop;
				 PF_commonHandler				pf_qyVDev_exit;
				 //
				 PF_bCommonHandler				pf_qyVDev_isSendable;
				 //
				 PF_qyVDev_postStr2Dev			pf_qyVDev_postStr2Dev;
				 PF_qyVDev_postData2Dev			pf_qyVDev_postData2Dev;
 
 
				 unsigned  char					ucbVDevInited;
				 unsigned  char					ucbVDevStarted;

				 unsigned  int					uiCmd;						//  模块管理上的菜单的对应命令
				 
}		 CUS_MODULE_vDev;





typedef  struct  __cusModuleCompress_t			{							//  2010/04/28
				 MACRO_cusModuleCommon			

				 QDC_MGR						mgr;

				 PF_qdcInit						pf_qdcInit;
				 PF_qdcExit						pf_qdcExit;

				 PF_qdcGetCompressAudioCfg		pf_qdcGetCompressAudioCfg;
				 PF_qdcGetCompressVideoCfg		pf_qdcGetCompressVideoCfg;

				 PF_qdcInitCompressAudio		pf_qdcInitCompressAudio;
				 PF_qdcExitCompressAudio		pf_qdcExitCompressAudio;
				 PF_qdcCompressAudio			pf_qdcCompressAudio;

				 PF_qdcInitDecompressAudio		pf_qdcInitDecompressAudio;
				 PF_qdcExitDecompressAudio		pf_qdcExitDecompressAudio;  
				 PF_qdcDecompressAudio			pf_qdcDecompressAudio;
				   				   
				 PF_qdcInitCompressVideo		pf_qdcInitCompressVideo;  
				 PF_qdcExitCompressVideo		pf_qdcExitCompressVideo;
				 PF_qdcCompressVideo			pf_qdcCompressVideo;
			   			   
				 PF_qdcInitDecompressVideo		pf_qdcInitDecompressVideo;
				 PF_qdcExitDecompressVideo		pf_qdcExitDecompressVideo;
				 PF_qdcDecompressVideo			pf_qdcDecompressVideo;  

				 //  2011/12/10
				 PF_qdcDecompressVideoAndOutput	pf_qdcDecompressVideoAndOutput;

				 //
				 PF_qdcGetOutputByIndex			pf_qdcGetOutputByIndex;
				 PF_qdcClearOutputs				pf_qdcClearOutputs;
				 
				 //
				 unsigned  char					ucbInited;

}		 CUS_MODULE_compress;


typedef  union  __cusModuleU_t					{
				CUS_MODULE_common				common;
				CUS_MODULE_vDev					vDev;
				CUS_MODULE_compress				compress;
				struct							{
					MACRO_cusModuleCommon
					void					*	ps[50];
				}								maxMem;
}		 CUS_MODULE_U;

//  #define		CONST_maxCusModules				5
//  #define		CONST_maxCusModules				8					//  2011/11/25
#define		CONST_maxCusModules					12					//  2012/09/15

typedef  struct  __cusModules_t					{	

				 unsigned  short				usCnt;
				 CUS_MODULE_U					mems[CONST_maxCusModules];

				 CUS_MODULE_U				*	pIpp;				//  2011/07/31
				 //  CUS_MODULE_U			*	pIpp1;				//  2012/09/15
				 CUS_MODULE_U				*	pMediaSdk;			//  2011/11/25
				 CUS_MODULE_U				*	pCuda;				//  2012/06/17

}		 CUS_MODULES;




 //
 BOOL  bFindMenuItem(  HMENU  hMenu, LPCTSTR  MenuString,  int  *  pnPos  );

 int  cusModuleMenu(  void  *  pQyMc,  HMENU  hMenuFrm,  int  iResId_menu_modulesGuanLi  );

 int  loadCusModules(  void  *  pQyMc  );
 int  unloadCusModules(  void  *  pQyMc  );
 //
 int  initCusModules(  void  *  pQyMcParam  );
 int  startCusModules(  void  *  pQyMcParam  );
 int  stopCusModules(  void  *  pQyMcParam  );

 //
 CUS_MODULE_U  *  getCusModule(  void  *  pQyMcParam,  unsigned  int  uiModuleType,  unsigned  int  uiVDevId  =  0,  unsigned  int  uiDevType  =  0,  WCHAR  *  wDevIdStr  =  NULL  );

 //
 int  myVDev_postStr2Dev(  char  *  idStr_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  LPCTSTR  str,  unsigned  int  uiDevType_to,  WCHAR  *  wDevIdStr_to,  WCHAR  *  wForwardPath,  HWND  hWnd_notify,  int  iUsrData  );
 int  myVDev_postData2Dev(  unsigned  int  uiVDevId,  char  *  idStr_from,  time_t  tStartTime,  unsigned  int  uiTranNo,  unsigned  int  uiSeqNo,  void  *  pQyVDevData,  unsigned  int  uiDataLen,  unsigned  int  uiDevType_to,  WCHAR  *  wDevIdStr_to,  unsigned  int  uiDevIndex  );

//
BOOL  bSupported_mediaSdk(  );

//  2012/09/09
#define		M_getCompressModule(  pQyMc,  uiModuleType,  pModule  )  {															\
					switch  (  uiModuleType  )  {																				\
							case  CONST_moduleType_ipp:																			\
								  pModule	=	pQyMc->cusModules.pIpp;															\
								  break;																						\
							case  CONST_moduleType_mediaSdk:																	\
								  pModule  =  pQyMc->cusModules.pMediaSdk;														\
								  break;																						\
							case  CONST_moduleType_cuda:																		\
								  pModule  =  pQyMc->cusModules.pCuda;															\
								  break;																						\
							case  CONST_moduleType_compress:																	\
								  pModule	=	getCusModule(  pQyMc,  CONST_moduleType_compress  );							\
								  break;																						\
							default:																							\
									pModule  =  NULL;																			\
									break;																						\
					}																											\
			}


#endif  //  }


