
#ifndef  __QYGUICOMMPROC_H__
#define  __QYGUICOMMPROC_H__	//  {




//
#define		CONST_maxCapImages									16


typedef  struct  __capImage_t									{

				 unsigned  int									iW_org,  iH_org;			//  原始大小,这是为了等比例缩放.
				 //
				 int											iX,  iY;					//  因为希望是等比例缩放, 所以图形的大小和位置也要计算
				 unsigned  int									iW,  iH;

				 QY_MESSENGER_ID								idInfo_sender;				//  idInfo_sender  +  uiObjType  +  uiTranNo_openAvDev  +  usIndex两个确定了一个图象源.
				 //  unsigned  int								uiObjType;					//  2009/09/03
				 unsigned  int									uiTranNo_openAvDev;
				 unsigned  short								usIndex;
				 //
				 int											iTaskId;

				 HWND											hWnd_remoteAv;				//  双击视频,可弹出独立窗口来显示的更清晰一点

				 //
				 unsigned  char									ucbUseVmr;					//  2012/02/06

				 HDRAWDIB										hDib;
				 DMO_info_vmr									dmoInfo;					//  用在vmr. 2012/02/06

				 //
				 BOOL											bResized;					//  此视频大小有变

				 DWORD											dwTickCnt_lastDrawing;		//  2009/09/10

}		 CAP_IMAGE;

typedef  struct  __capImages_t									{
				 BOOL											bResized;													//  此标志位表明需要全部重新排版。
				 unsigned  short								usCnt;														//  2012/05/22. 特别注意: usCnt不标明mems的前n个有效.但是表示所有的mems里,有n个有效.所以,当枚举有效的mem时, 要(i=0;i<mycountof( mems); i++)
				 CAP_IMAGE										mems[CONST_maxCapImages];
}		 CAP_IMAGES;


#if  0		//  2012/05/08
typedef  struct  __CAP_subWnds_t								{												//  2009/09/06  		
				 struct											{
					 HWND										hWnd;
					 int										iWndContentType;
					 int										iWndContentSubType;								//  2012/04/29
					 //
					 int										iTaskId;
					 //
					 QY_MESSENGER_ID							idInfo;
					 unsigned  int								uiObjType;
					 unsigned  short							usIndex;
				 }												mems[32];
}		 CAP_subWnds;
#endif

//
#define		DEFAULT_usMaxCnt_capSubWnds							32

typedef  struct  __CAP_subWnd_t									{												//  2009/09/06  		
					 HWND										hWnd;
					 int										iWndContentType;
					 int										iWndContentSubType;								//  2012/04/29
					 //
					 int										iTaskId;
					 //
					 QY_MESSENGER_ID							idInfo;
					 unsigned  int								uiObjType;
					 unsigned  short							usIndex;
}		 CAP_subWnd;


typedef  struct  __CAP_subWnds_t								{												//  2012/05/08
				 unsigned  short								usMaxCnt;
				 CAP_subWnd								*		pMems;
}		 CAP_subWnds;


//
typedef  struct  __zoneParam_t									{
				 int											index_subWall;									//  2009/10/04
				 int											index_zone;
				 unsigned  int									uiTranNo_zone;
				 //
				 int											index_capImage;
				 //
				 int											nRulePriority;									//  nPriority of the rule to get zoneParam

}		 ZONE_PARAM;


//  2013/02/27. 
typedef  struct  __dcDrawParam_t								{				 
				 //
				 HWND											hWnds_excludeClip[4];

				 //
				 BOOL											bDlgHidden;

				 //
				 unsigned  char									ucbFixedSize;

				 //
				 BOOL											bUseDxSurface;  
}		 DC_draw_param;

//  2013/02/17
typedef  struct  __dlgSyncFlgs_t								{
				BOOL											bSubWndExists;							//  2011/03/28
				//
				//  BOOL										bMessageBoxExists;						//  2013/02/17

				BOOL											bLocked_bQuitDlg;						//  2012/05/09				
}		 DLG_syncFlgs;


//  2012/05/08
int  initCapSubWnds(  unsigned  short  usMaxCnt,  CAP_subWnds  *  p  );
void  exitCapSubWnds(  CAP_subWnds  *  p  );


//  int  registerSubWnd(  HWND  hWnd,  int  iWndContentType,  int  iTaskId,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  int  uiObjType,  unsigned  short  usIndex,  CAP_subWnds  *  p,  int  *  pIndex_subWnd  );
int  registerSubWnd(  HWND  hWnd,  int  iWndContentType,  int  iWndContentSubType,  int  iTaskId,  QY_MESSENGER_ID  *  pIdInfo,  unsigned  int  uiObjType,  unsigned  short  usIndex,  CAP_subWnds  *  p,  int  *  pIndex_subWnd  );
int  closeSubWnds(  CAP_subWnds  *  p  );
HWND  findSubWnd(  CAP_subWnds  *  p,  int  iWndContentType,  int  iWndContentSubType  );
BOOL  bExists_capSubWnd(  CAP_subWnds  *  p  );

//
int  myGetImageInfo(  unsigned  char  ucbFixedSize,  int  iW_image,  int  iH_image,  int  iX,  int  iY,  unsigned  int  iW,  unsigned  int  iH,  int  *  piX_image,  int  *  piY_image,  unsigned  int  *  piW_image,  unsigned  int  *  piH_image  );

int  getCapImages(  int  iX_desc,  int  iY_desc,  int  iW_desc,  int  iH_desc,  CAP_IMAGES  *  pImages  );
int  redrawImage(  HWND    hDlg,  int  idc,  int  iX,  int  iY,  unsigned  int  iW,  unsigned  int  iH  );

//  
//  int  drawCapImages(  HWND    hDlg,  int  idc,  HDC  *  phDc,  unsigned  char  ucbFixedSize,  MIS_MSG_procVideo_qmc  *  pMsg,  int  iX,  int  iY,  unsigned  int  iW,  unsigned  int  iH,  CAP_subWnds  *  pSubWnds,  ZONE_PARAM  *  pZoneParam,  CAP_IMAGES  *  pImgs,  BOOL  bUseDxSurface,  BOOL  bDlgHidden  );
int  drawCapImages(  HWND    hDlg,  int  idc,  HDC  *  phDc,  DC_draw_param  *  pDcDrawParam,  unsigned  char  ucbFixedSize,  MIS_MSG_procVideo_qmc  *  pMsg,  int  iX,  int  iY,  unsigned  int  iW,  unsigned  int  iH,  CAP_subWnds  *  pSubWnds,  ZONE_PARAM  *  pZoneParam,  CAP_IMAGES  *  pImgs,  BOOL  bUseDxSurface,  BOOL  bDlgHidden  );
int  drawCapImages(  HWND    hWnd_src,  MIS_MSG_procVideo_qmc  *  pMsg,  int  iX,  int  iY,  unsigned  int  iW,  unsigned  int  iH,  CAP_subWnds  *  pSubWnds,  ZONE_PARAM  *  pZoneParam,  CAP_IMAGES  *  pImgs,  HWND  hWnd_dst,  HDC  *  phDc_dst,  DC_draw_param  *  pDcDrawParam  );

//  2013/03/02
#define		M_GetDlgItem(  hDlg,  idc  )	idc  ?  ::GetDlgItem(  hDlg,  idc  )  :  hDlg

//
//  int  freeCapImage(  HWND    hDlg,  int  idc,  CAP_IMAGE  *  pImg  );
//  int  freeCapImageByTaskId(  HWND    hDlg,  int  idc,  int  iTaskId,  CAP_IMAGES  *  pImgs  );
//  int  freeCapImageBySth(  HWND    hDlg,  int  idc,  int  iTaskId,  QY_MESSENGER_ID	*	pIdInfo,  CAP_IMAGES  *  pImgs  );
//  int  freeCapImages(  HWND    hDlg,  int  idc,  HDC  *  phDc,  CAP_IMAGES  *  pImgs  );

int  freeCapImage(  HWND    hDlg,  int  idc,  CAP_IMAGE  *  pImg,  HWND  hWnd_dst  );	//  2013/03/02
int  freeCapImageByTaskId(  HWND    hDlg,  int  idc,  int  iTaskId,  CAP_IMAGES  *  pImgs,  HWND  hWnd_dst  );
int  freeCapImageBySth(  HWND    hDlg,  int  idc,  int  iTaskId,  QY_MESSENGER_ID	*	pIdInfo,  CAP_IMAGES  *  pImgs,  HWND  hWnd_dst  );
int  freeCapImages(  HWND    hDlg,  int  idc,  CAP_IMAGES  *  pImgs,  HWND  hWnd_dst,  HDC  *  phDc_dst  );


int  doWnd_guiMsgArrive(  void  *  pProcInfoParam,  int  index_player,  HWND  hWnd,  BOOL  bForce_displayAllFrames,  MIS_MSGU  *  pMsgBuf  );
int  doMainWnd_procVideo(  void  *  pQyMcParam,  MIS_MSG_procVideo_qmc  *  pMsg  );

int  brushDc(  COLORREF  color,  HDC  hDc,  int  x,  int  y,  int  iW,  int  iH  );

 BOOL  bApp_ts(  );


#endif  //  }


