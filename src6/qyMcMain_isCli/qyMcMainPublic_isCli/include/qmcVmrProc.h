

#ifndef  __QMCVMRPROC_H__
#define  __QMCVMRPROC_H__	//  {


//  #define		__USE_vmr__		//  2012/02/06, 暂时用不着了
 
#ifdef  __USE_vmr__

 __declspec(dllexport) int OpenClip(  HWND  hWnd,  BITMAPINFOHEADER	*  pBih_in,  RECT  rect,  GENERIC_Q_CFG  *  pQCfg,  RW_lock_param  *  pRwLockParam,  DMO_info_vmr  *  pDmoInfo  );
 __declspec(dllexport) int CloseClip(  DMO_info_vmr  *  pDmoInfo  );

 __declspec(dllexport) int  postToDraw_vmr(  DMO_info_vmr  *  pDmoInfo,  void  *  pMsg,  int  len_pMsg,  BOOL  *  pbPktRedirected  );

#endif
	
#endif  //  }



