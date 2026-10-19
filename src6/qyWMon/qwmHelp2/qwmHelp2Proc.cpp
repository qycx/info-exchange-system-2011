

#include	"stdafx.h"
#include	<stdlib.h>
//
#include	"qyCommon.h"
#include	"qyCommon\\asrObjs.h"

#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qnmSysCustom.h"
#include	"asrWMonPrecomp.h"
#include	"qyCommon\\asrLog.h"
#include	"qyCommon\\asrComm.h"

#include	"qyCommon\\awmComm.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"
#include	"qyGuiCommon.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qwmHideProcessCommProc.h"
#include	<tchar.h>
#include	"qySyncCommProc.h"
#include	"qwmFunc.h"

/////////////////////  {

#pragma  data_seg(  "qwmData"  )

BOOL					bQwmQuitFlg		=	FALSE;
QWM_GBUF				gBuf			=	{	"",	};

#pragma  data_seg(  )

#pragma  comment(  linker,  "/section:qwmData,rws"  )

///////////////////////  }



 //  这里应该加一个mutex,使当服务退出时，则所有的标志位都不能再设
 //  一般的用户脚本则需要将remoteProcess给设上
 //  下面的工作很不理想，应该在gBuf里增加一个数组，建立对应关系，将每个用户的监控情况都列在里面，并且能够各自清理各自的线程
 //


 extern  "C"  __declspec( dllexport )  void  *  getQwmGBuf(  )
{
	 if  (  sizeof(  QWM_GBUF_DETAIL  )  >=  sizeof(  gBuf  )  )  {
		 traceLogA(  "gBuf.dataBuf is too small"  );  return  NULL;
	 }

	 return  &gBuf;	 
}



 extern  "C"  __declspec(  dllexport  )  int  setGBufSth(  int  iCfgId,  void  *  pSth  )
{
	 int					iErr		=	-1;
	 QWM_GBUF_DETAIL	*	pDetail		=	(  QWM_GBUF_DETAIL  *  )&gBuf;
	 CQySyncObj				syncObj;

	 if  (  !pSth  )  goto  errLabel;

	 //  if  (  !bSetPermitted(  )  )  goto  errLabel;

	 traceLogA(  "setGBufSth(  )  called: iCfgId is %d",  iCfgId  );

	 if  (  syncObj.sync(  _T(  CONST_mutexName_syncQwmGBuf  )  )  )  {
		 traceLogA(  "setGBufSth(  ): sync failed"  );  goto  errLabel;
	 }

	 /*
	 switch  (  iCfgId  )  {
			 //  case  CONST_qnmCfgId_pcRules:
			 //  case  CONST_qnmCfgId_bServerOnline:
			 default:
				     traceLogA(  "setGBufSth(  ):  iCfgId error"  );
				     goto  errLabel;
	 }
	 */


	 iErr  =  0;
errLabel:
	 return  iErr;
}
