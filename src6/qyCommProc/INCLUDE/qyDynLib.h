
#ifndef  __QYDYNLIB_H__
#define  __QYDYNLIB_H__	//  {

typedef  struct  __qyDynLibs_t								{

				 //  200812/12. DirectXµÄ¿â
				 void									*	pLib_dx;
				 
}		 QY_DYN_LIBS;


extern  "C"  int  initDynLib_dx(  LPCTSTR  systemDir,  void  **  pp  );
extern  "C"  int  exitDynLib_dx(  void  **  pp  );

BOOL  bSupported_directSound(  );

int  myGetNewFilter(  QY_ENV  *  pEnv,  REFCLSID  rclsid,  void  *  pParam,  void  **  ppIBaseFilter  );
#if  0
void  *  myNewCrossBar(  QY_ENV  *  pEnv,  void  *  pStartingInputPin,  HRESULT  *  phr  );
void  myFreeCrossBar(  QY_ENV  *  pEnv,  void  *  pCrossBarParam  );
int  myCrossBarGetInputCount(  QY_ENV  *  pEnv,  void  *  pCrossBarParam,  long  *  pCount  );
#endif

#endif  //  }

