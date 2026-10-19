
#ifndef  __QYAVRECORDDX_H__
#define  __QYAVRECORDDX_H__		//  {


#include	"qmcDirectX.h"


int  initD3D(  DYN_LIB_DX  *  pDynLib,  HWND  hWnd,  QY_AV_RECORD  *  pAvRecord  );




int  recordVideo_dx(  MC_VAR_isCli  *  pProcInfo,  QY_AV_recordMgr  *  pMgr,  int  iIndex_screenCapProcInfo,  int  top,  int  left,  int  width,  int  height,  int  fps,  LPCTSTR  szFileName  );


#endif  //  }


