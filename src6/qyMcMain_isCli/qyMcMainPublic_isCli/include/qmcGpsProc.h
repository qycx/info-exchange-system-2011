
#ifndef  __QMCGPSPROC_H__
#define  __QMCGPSPROC_H__	//  {


int  toShareGps(  MC_VAR_isCli  *  pProcInfo,  void  *  pComPortEx,  int  iSampleTimeInMs,  void  *  pmyGPS_POSITION,  QY_SHARED_OBJ  *  pSharedObj,  BOOL  *  pbHaveMsgrs_sendLocalAv,  MIS_MSGU  *  pMsgBuf  );

//
int  gps2Pnt(  void  *  p0,  myGPS_POSITION  *  pGpsPos,  int  zoom,  POINT  *  pPnt  );

int  talkerShadow_procGps(  void  *  pProcInfoParam,  HWND  hDlgTalk,  BOOL  bForceRefreshPos,  int  index_shadow,  HWND  hDlgDynBmps_param,  void  *  pDlgDynBmpsVar_param,  int  index_wallGpsMgrMem  );


#endif  //  }


