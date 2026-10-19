
#ifndef  __QYMCMAINEXTMODULE_H__
#define  __QYMCMAINEXTMODULE_H__	//  {

#if  0
typedef  void (  *PF_mainWnd_OnIsCmd  )(  HWND  hWnd,  void  *  pVar,  UINT nID  );
typedef  void (  *PF_mainWnd_OnUpdateIsCmd  )(  HWND  hWnd,  void *pCmdUI);



typedef  struct  __moduleExtGuiCommon_t			{							//  2010/04/28
				 MACRO_cusModuleCommon			

				 //  unsigned  char					ucbInited;

				 PF_mainWnd_OnIsCmd				pf_mainWnd_OnIsCmd;			//  2010/10/02
				 PF_mainWnd_OnUpdateIsCmd		pf_mainWnd_OnUpdateIsCmd;


}		 MODULE_EXT_guiCommon;

 //  2010/10/02
 int  getSize_moduleExt(  );
 BOOL  initModuleExt(  );
 void  exitModuleExt(  );
#endif



#endif  //  }

