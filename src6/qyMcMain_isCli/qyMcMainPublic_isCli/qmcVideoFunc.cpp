

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"
#include	"qmcDmoPublic.h"
#include	"qmcCmdProc.h"
#include	"tmpCeLib.h"
//  #include	"myfourcc.h"
#include	"module_qisCamCap.h"
#include	"isCmdConst.h"
#include	"qyOpenShellCommon.h"
#include	"qyCusResTemp.h"
#include	"policyAvParams.h"


 char  *  iFourcc2Str(  int  fourcc,  char  *  fourccStr,  unsigned  int  size  )
{
	unsigned  char  chs[5]			=	"";
	int				i				=	0;
	
	i  =  0;	chs[i]  =  (  unsigned  char  )fourcc;
	i  ++  ;	chs[i]  =  (  unsigned  char  )(  fourcc  >>  8  );
	i  ++  ;	chs[i]  =  (  unsigned  char  )(  fourcc  >>  16  );
	i  ++  ;	chs[i]  =  (  unsigned  char  )(  fourcc  >>  24  );
	i  ++  ;	chs[i]	=	0;

	if  (  !fourccStr  )  OutputDebugString(  CQyString(  (  char  *  )chs  )  +  _T(  "\n"  )  );

	if  (  fourccStr  &&  size  >  4  )  {
		safeStrnCpy(  (  char  *  )chs,  fourccStr,  size  );
		return  fourccStr;
	}

	return  NULL;
}

 int  fourccStr2i(  const  char  *  fourccStr  )
{
	if  (  !fourccStr  )  return  -1;
    
	return  mmioFOURCC(  fourccStr[0],  fourccStr[1],  fourccStr[2],  fourccStr[3]  );
}


 
 int  qisApplyForChkingTasks_gui(  )	//  2009/09/10
{
	#ifdef  __DEBUG__
			traceLog(  _T(  "qisApplyForChkingTasks_gui called"  )  );
	#endif

	if  (  g_pQyMc  )  {
		PostMessage(  g_pQyMc->gui.hMainWnd,  CONST_qyWm_postComm,  CONST_qyWmParam_chkTask,  0  );  
	}

	return  0;
}

 int  tmpHandler_bMediaTaskExists(  void  *  p0,  void  *  p1,  MIS_MSGU  *  pMsg  )
{
	int	iTaskId =  (  int  )p0;

	if  (  pMsg->uiType  ==  CONST_misMsgType_task  )  {
		if  (  pMsg->task.iTaskId  ==  iTaskId  )  return 1;
	}

	return  0;
}

 BOOL  bMediaTaskExists(  MC_VAR_isCli  *  pProcInfo,  int  iTaskId  )
{
	BOOL		bRet	=	FALSE;

	if  (  pProcInfo->processQ_media.qTraverse(  (  PF_commonHandler  )tmpHandler_bMediaTaskExists,  (  void  *  )iTaskId,  0  )  <=  0  )  goto  errLabel;

	bRet  =  TRUE;
errLabel:
	return  bRet;
}

//

 BOOL  canShareScreen(  )
{
	QY_MC					*		pQyMc				=	QY_GET_GBUF(  );
	int								iServiceId			=	CONST_qyServiceId_mis;
	QY_SERVICEGUI_INFO		*		pSci				=	getServiceGuiInfo(  pQyMc,  iServiceId  );
	//
	MC_VAR_isCli				*		pProcInfo			=	(  MC_VAR_isCli  *  )pSci->pVar;
	int								i;

	if  (  !pProcInfo  )  return  FALSE;
	if  (  !pProcInfo->pSharedObjs  )  return  FALSE;

	for  (  i  =  1;  i  <  pProcInfo->cfg.usMaxCnt_pSharedObjs;  i  ++  )  {
		 if  (  !pProcInfo->pSharedObjs[i].bUsed  )  return  TRUE;
	}

	return  FALSE;
}



 BOOL  canRemoteAssist(  )
{
	BOOL							bRet				=	FALSE;
	QY_MC					*		pQyMc				=	QY_GET_GBUF(  );
	int								iServiceId			=	CONST_qyServiceId_mis;
	QY_SERVICEGUI_INFO		*		pSci				=	getServiceGuiInfo(  pQyMc,  iServiceId  );
	//
	MC_VAR_isCli				*		pProcInfo			=	(  MC_VAR_isCli  *  )pSci->pVar;
	int								i;
	BOOL							bFull				=	TRUE;

	if  (  !pProcInfo  )  return  FALSE;
	if  (  !pProcInfo->pSharedObjs  )  return  FALSE;

	for  (  i  =  1;  i  <  pProcInfo->cfg.usMaxCnt_pSharedObjs;  i  ++  )  {
		 if  (  !pProcInfo->pSharedObjs[i].bUsed  )  {
			 bFull  =  FALSE;
			 continue;
		 }
		 if  (  pProcInfo->pSharedObjs[i].bRemoteAssist  )  return  FALSE;		//  Ô¶³ÌÐ­ÖúÖ»ÄÜÒ»¸ö¡£ÒòÎªÊó±ê¼üÅÌÖ»ÓÐÒ»¸ö
	}

	return  !bFull;
}

  BOOL  canRemotePtzControl(  )
 {
	 BOOL	bRet	=	FALSE;
	 	 
	 QY_MC				*	pQyMc			=	QY_GET_GBUF(  );
	 unsigned  int			uiChannelType	=	CONST_channelType_media;	
	 MIS_CHANNEL		*	pChannel		=	NULL;
	 MIS_CNT			*	pMisCnt			=	getMisCntByName(  pQyMc,  0,  _T(  ""  )  );
	 if  (  !pMisCnt  )  goto  errLabel;
	 
#ifdef  __DEBUG__
		traceLog(  _T(  "For test, canRemotePtzControl(  ) returns TRUE"  )  );
		bRet  =  TRUE;  goto  errLabel;
#endif

	 if  (  !(  pChannel  =  getChannelByType(  pMisCnt,  uiChannelType  )  )  )  goto  errLabel;
	
	 if  (  !bChannelOk(  0,  0,  pChannel  )  )  goto  errLabel;

	 bRet  =  TRUE;
errLabel:
	 return  bRet;

 }

 int  makeBmpInfoHeader_rgb(  unsigned  int  bits,  int  iWidth,  int  iHeight,  BITMAPINFOHEADER  *  p  )
{
	if  (  !p  )  return  -1;

	memset(  p,  0,  sizeof(  p[0]  )  );

	p->biSize  =  sizeof(  BITMAPINFOHEADER  );
	p->biWidth  =  iWidth;
	p->biHeight  =  iHeight;
	p->biPlanes  =  1;
	p->biBitCount  =  (  WORD  )bits;
	p->biCompression  =  BI_RGB;
	p->biSizeImage  =  (  p->biWidth  *  p->biBitCount  +  31  )  /  32  *  4  *  p->biHeight;
	p->biClrUsed = (bits <= 8) ? 1<<bits : 0;

	return  0;
}

 int  makeBmpInfoHeader_yuy2(  unsigned  int  bits,  int  iWidth,  int  iHeight,  BITMAPINFOHEADER  *  p  )
{
	if  (  !p  )  return  -1;

	memset(  p,  0,  sizeof(  p[0]  )  );

	p->biSize  =  sizeof(  BITMAPINFOHEADER  );
	p->biWidth  =  iWidth;
	p->biHeight  =  iHeight;
	p->biPlanes  =  1;
	p->biBitCount  =  16;	//  (  WORD  )bits;
	p->biCompression  =  CONST_fourcc_YUY2;
	p->biSizeImage  =  (  p->biWidth  *  p->biBitCount  +  31  )  /  32  *  4  *  p->biHeight;
	p->biClrUsed = (bits <= 8) ? 1<<bits : 0;

	return  0;
}

 int  makeBmpInfoHeader_yv12(  unsigned int bits,  int iWidth,  int iHeight,  BITMAPINFOHEADER  * p  )
{
	if  (  !p  )  return  -1;

	bits  =  12;

	memset(  p,  0,  sizeof(  p[0]  )  );

	p->biSize  =  sizeof(  BITMAPINFOHEADER  );
	p->biWidth  =  iWidth;
	p->biHeight  =  iHeight;
	p->biPlanes  =  1;
	p->biBitCount  =  bits;
	p->biCompression  =  CONST_fourcc_YV12;
	p->biSizeImage  =  (  p->biWidth  *  p->biBitCount  +  31  )  /  32  *  4  *  p->biHeight;
	p->biClrUsed  =  (  bits  <=  8  )  ?  1<<bits  :  0;

	return  0;
}

 // #define		getSharedObjUsr(  pSharedObj,  iIndex_usr  )		(  (  (  pSharedObj  )  &&  (  iIndex_usr  )  >=0  &&  (  iIndex_usr  )  <  MAX_sharedObjUsrs  )  ?  &(  pSharedObj  )->usrs[iIndex_usr]  :  NULL  )
 SHARED_OBJ_USR  *  getSharedObjUsr(  QY_SHARED_OBJ  *  pSharedObj,  int  iIndex_usr  )
{
	return  (  (  (  pSharedObj  )  &&  (  iIndex_usr  )  >=0  &&  (  iIndex_usr  )  <  MAX_sharedObjUsrs  )  ?  &(  pSharedObj  )->usrs[iIndex_usr]  :  NULL  );
}


 int  getSharedObjIndex_localAv(  )
{
	return  0;
}

 //
 void  askSharedObjToStop(  MC_VAR_isCli  *  pProcInfo,  QY_SHARED_OBJ  *  pSharedObj,  HWND  hWnd_notifyEnd  )
{
	 if  (  !pSharedObj  )  return;
 
	 if  (  !pSharedObj->bQuit  ) {
		 pSharedObj->bQuit  =  TRUE;
	 }

	 QM_SHM_CMD		*	pShmCmd		=	NULL;
	 pShmCmd  =  getShmCmdByIndex(  (  QM_SHM_CMDS  *  )pProcInfo->cmdsShm.pBuf,  pSharedObj->iIndex_shmCmd  );
	 if  (  pShmCmd  )  pShmCmd->bQuit  =  TRUE;

	
	 PostMessage(  hWnd_notifyEnd,  CONST_qyWm_postComm,  CONST_qyWmParam_task_end,  0  );	

	 return;
}
