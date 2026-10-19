

#ifndef  __isCliD3dPublic_h__
#define  __isCliD3dPublic_h__	//  {

typedef  struct  __gBuf_d3d_isCli_t			{

				 HWND						hWall_d3d;

				 struct						{
					 QY_MESSENGER_ID		idInfo_peer;
					 HWND					hTalkerMgr;
					 //
					 struct					{
						 int				iAvStatus;
					 }						info;

				 }							peer;

				 //
				 TCHAR						hint[128];
				 unsigned  char				ucbChanged;

}		 GBuf_d3d_isCli;


//
__declspec(dllexport)  int   set_g_pQyMc_isCliD3d(  void  *  pQyMc  );


//
__declspec(  dllexport  )  int  dllInit_d3d_isCli(  );
__declspec(  dllexport  )  int  dllExit_d3d_isCli(  );



//
__declspec(  dllexport  )  void  *  GBuf_d3d_isCli_new(  );
__declspec(  dllexport  )  void  GBuf_d3d_isCli_free(  void  **  ppGBuf_d3d_isCli  );



__declspec(  dllexport  )  int  createWall_d3d(  void  *  pGBuf_d3d  );
__declspec(  dllexport  )  int  closeWall_d3d(  void  *  pGBuf_d3d  );

__declspec(  dllexport  )  void  myRender();


__declspec(  dllexport  )  int  fillData_d3d(  BITMAPINFOHEADER  *  pBih,  BYTE  *  pData  );


#ifdef  __DEBUG__
__declspec(  dllexport  )  int  testFunc_d3d(  );
#endif

 __declspec(  dllexport  )  void  *  getDlgWallsVar_wallD3d(  HWND  hDlgWalls,  int  iWndContentType  );


#endif  //  }

