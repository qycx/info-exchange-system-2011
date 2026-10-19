
#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<winsock2.h>
#include	<windows.h>
#include	<assert.h>
#include	<tchar.h>
#include	<iphlpapi.h>

#ifndef  __WINCE__
	#include	<vfw.h>
#else
	#ifdef  __TEST__
		#include	<vfw.h>
	#endif

	#include	<mmreg.h>
	#include	<MSAcm.h>
#endif
#include	<Wincrypt.h>
#include	<time.h>

#include	"qyCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qySyncCommProc.h"

#include	"qmOpenCommon.h"
#include	"qyMsgFunc.h"

#include	"qySyncCommProc.h"
#include	"genericQueue.h"
#include	"qyq2.h"				//  2009/05/13

#include	"qnmCommProc_mis.h"


//  #include	<lmshare.h>

//  #include	"qwmDynFunc.h"

#include	"qnmCommProc_mis.h"



////////////////////////


 // 1需要修改qRemoveMsg等函数，增加initGenericQ的一个节点自动清除的函数pfQElemRemove，和pfQElemExit不同，在qGetMsg时不起作用，在qRemoveMsg和emptyQ时要起作用。
//  2。在从需要释放的包里读取数据时，最好专门作一个函数，将一个局部的CQyMalloc变量引入，在读取到数据时，直接和mallocObj->attach. 可以确保数据的自动释放。


 //  2009/12/08
 void  clean_myPLAY_AUDIO_DATA(  myPLAY_AUDIO_DATA  *  p,  LPCTSTR  hint  )
{
	if  (  !p  )  return;

	//  traceLogA(  "clean_myPLAY_AUDIO_DATA"  );

	//  MACRO_safeFree(  p->pBuf  );
	freeMemory(  &p->memory  );

	return;
}

 void  clean_myDRAW_VIDEO_DATA(  myDRAW_VIDEO_DATA  *  p,  LPCTSTR  hint  )
{
	if  (  !p  )  return;
	
	TCHAR	tBuf[128]	=	_T(  ""  );
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  hint  ?  hint  :  _T(  ""  ),  _T(  "clean_myDRAW_VIDEO_DATA: free"  )  );

	//  traceLogA(  "clean_myDRAW_VIDEO-DATA"  );
	M_pkt_showNo(  *p,  tBuf  );

	//  MACRO_safeFree(  p->pBuf  );
	freeMemory(  &p->memory  );

	return;
}

 //  2012/11/10
 void  cleanEx_myDRAW_VIDEO_DATA(  myDRAW_VIDEO_DATA  *  p,  size_t	size,  LPCTSTR  hint  )
 {
	 int	nPkts  =  size  /  sizeof(  myDRAW_VIDEO_DATA  );

	 TCHAR	tBuf[128]	=	_T(  ""  );
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  hint  ?  hint  :  _T(  ""  ),  _T(  "Ex"  )  );
	 
	 int  i;
	 for  (  i  =  0;  i  <  nPkts;  i  ++  )  {
		  clean_myDRAW_VIDEO_DATA(  &p[i],  tBuf  );
	 }
	 return;
 }

 //  2011/12/15. player.displayQ用到了
 void  clean_MIS_MSG_procVideo_qmc(  MIS_MSG_procVideo_qmc  *  p,  LPCTSTR  hint  )
{
	if  (  !p  )  return;
	
	TCHAR	tBuf[128]	=	_T(  ""  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  hint  ?  hint  :  _T(  ""  ),  _T(  "clean_MIS_MSG_procVideo_qmc: free"  )  );
	 
#ifdef  __DEBUG__
	assert(  p->uiType  ==  CONST_misMsgType_procVideo_qmc  );
#endif

	if  (  p->uiType  ==  CONST_misMsgType_procVideo_qmc  )  {
		//  2012/11/09
		M_msg_showNo(  *p,  tBuf  );
		//
		freeMemory(  &p->memory  );
	}
	return;
}

 void  cleanEx_MIS_MSG_procVideo_qmc(  MIS_MSG_procVideo_qmc  *  p,  size_t  size,  LPCTSTR  hint )
 {
	 int	nPkts  =  size  /  sizeof(  MIS_MSG_procVideo_qmc  );

	 TCHAR	tBuf[128]	=	_T(  ""  );
	_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s"  ),  hint  ?  hint  :  _T(  ""  ),  _T(  "Ex"  )  );
	 
	 int  i;
	 for  (  i  =  0;  i  <  nPkts;  i  ++  )  {
		  clean_MIS_MSG_procVideo_qmc(  &p[i],  tBuf  );
	 }
	 return;
 }

#if  0

 TMP_MEMORY  *  getTmpMemoryByIndex(  int  iIndex  )
 {
	 if  (  !g_pEnv  )  return  NULL;
	 TMP_MEMORYS_MC	*	pMemorys  =  (  TMP_MEMORYS_MC  *  )g_pEnv->pTmpMemorys;
	 if  (  !pMemorys  )  return  NULL;

	 if  (  iIndex  <  0  ||  iIndex  >=  pMemorys->usMaxCnt  )  return  NULL;

	 return  &pMemorys->pMems[iIndex];
 }


 int  newTmpMemoryGrp(  int  iTaskId,  unsigned  int  cnt,  unsigned  int  uiBufSize,  TMP_MEMORY_GRP  *  pGrp  )
{
	int				iErr		=	-1;

	if  (  !g_pEnv  )  return  NULL;
	TMP_MEMORYS_MC	*	pMemorys  =  (  TMP_MEMORYS_MC  *  )g_pEnv->pTmpMemorys;
	if  (  !pMemorys  )  return  NULL;

	int				i;
	CQySyncObj			syncObj;

	if  (  !cnt  ||  !uiBufSize  ||  !pGrp  )  return  -1;
	if  (  cnt  >  mycountof(  pGrp->indexes  )  )  return  -1;

	memset(  pGrp,  0,  sizeof(  pGrp[0]  )  );
	pGrp->uiBufSize  =  uiBufSize;

	int	uiTranNo_identity  =  getuiNextTranNo(  0,  0,  0  );

	if  (  syncObj.sync(  pMemorys->mutexName  )  )  goto  errLabel;

	for  (  i  =  0;  i  <  pMemorys->usMaxCnt;  i  ++  )  {
		 TMP_MEMORY	*	pMem	=	&pMemorys->pMems[i];
		 if  (  pMem->ucbUsed  )  continue;
		 if  (  pMem->pBuf  )  continue;
		 //
		 memset(  pMem,  0,  sizeof(  pMem[0]  )  );
		 pMem->ucbUsed  =  TRUE;
		 //
		 pMem->iTaskId  =  iTaskId;
		 pMem->uiTranNo_identify  =  uiTranNo_identity;
		 //
		 pGrp->indexes[pGrp->usCnt]  =  i;
		 pGrp->usCnt  ++  ;
		 //
		 if  (  pGrp->usCnt  ==  cnt  )  break;
	}

	if  (  !pGrp->usCnt  )  goto  errLabel;

	for  (  i  =  0;  i  <  pGrp->usCnt;  i  ++  )  {
		 TMP_MEMORY  *  pMem  =  getTmpMemoryByIndex(  pGrp->indexes[i]  );
		 pMem->uiBufSize  =  uiBufSize;
		 pMem->pBuf  =  (  char  *  )malloc(  pMem->uiBufSize  );
		 if  (  !pMem->pBuf  )  goto  errLabel;
	}

	iErr  =  0;
errLabel:

	if  (  iErr  )  {
		for  (  i  =  0;  i  <  pGrp->usCnt;  i  ++  )  {
			 TMP_MEMORY  *  pMem  =  getTmpMemoryByIndex(  pGrp->indexes[i]  );
			 MACRO_safeFree(  pMem->pBuf  );
			 pMem->ucbUsed  =  FALSE;
		}
		memset(  pGrp,  0,  sizeof(  pGrp[0]  )  );
	}

	return  iErr;
}

 int  freeTmpMemoryGrp(  TMP_MEMORY_GRP  *  pGrp  )
{
	int				iErr		=	-1;

	if  (  !g_pEnv  )  return  -1;
	TMP_MEMORYS_MC	*	pMemorys  =  (  TMP_MEMORYS_MC  *  )g_pEnv->pTmpMemorys;
	if  (  !pMemorys  )  return  -1;

	int				i;
	
	{
		CQySyncObj			syncObj;

		if  (  syncObj.sync(  pMemorys->mutexName  )  )  return  -1;

		for  (  i  =  0;  i  <  pGrp->usCnt;  i  ++  )  {
			 TMP_MEMORY	*	pMem  =  getTmpMemoryByIndex(  pGrp->indexes[i]  );
			 pMem->ucbUsed  =  FALSE;
		}
	}

	if  (  !IsWindow(  pMemorys->hWnd_toChkTmpMemorys  )  )  {
		traceLog(  _T(  "freeTmpMemoryGrp: hWnd_toChkTmpMemorys is not valid"  )  );
	}
	PostMessage(  pMemorys->hWnd_toChkTmpMemorys,  CONST_qyWm_postComm,  CONST_qyWmParam_chkTmpMemorys,  0  );  

	memset(  pGrp,  0,  sizeof(  pGrp[0]  )  );

	iErr  =  0;

	return  iErr;
}

 int  newTmpMemoryIndex(  TMP_MEMORY_GRP  *  pGrp  )
{
	int				iErr		=	-1;

	if  (  !g_pEnv  )  return  -1;
	TMP_MEMORYS_MC	*	pMemorys  =  (  TMP_MEMORYS_MC  *  )g_pEnv->pTmpMemorys;
	if  (  !pMemorys  )  return  -1;

	int				i;
	TMP_MEMORY  *	pMem		=	NULL;

	if  (  !pGrp->usCnt  )  return  -1;

	for  (  i  =  pGrp->iIndex_toAlloc;  i  <  pGrp->usCnt;  i  ++  )  {
		 pMem  =  getTmpMemoryByIndex(  pGrp->indexes[i]  );
		 MACRO_qyAssert(  pMem,  _T(  "newTmpMemoryIndex error"  )  );
		 if  (  InterlockedExchangeAdd(  &pMem->m_cRef,  0  )  )  continue;
		 break;
	}
	if  (  i  ==  pGrp->usCnt  )  {
		for  (  i  =  0;  i  <  pGrp->iIndex_toAlloc;  i  ++  )  {
			 pMem  =  getTmpMemoryByIndex(  pGrp->indexes[i]  );
			 MACRO_qyAssert(  pMem,  _T(  "newTmpMemoryIndex error"  )  );
			 if  (  InterlockedExchangeAdd(  &pMem->m_cRef,  0  )  )  continue;
			 break;
		}
		if  (  i  ==  pGrp->iIndex_toAlloc  )  goto  errLabel;
	}

	InterlockedExchangeAdd(  &pMem->m_cRef,  1  );
	
	pGrp->iIndex_toAlloc  =  (  i  +  1  )  %  pGrp->usCnt;

	iErr  =  0;
errLabel:
	return  iErr  ?  iErr  :  pGrp->indexes[i];
}

 int  freeTmpMemoryIndex(  int  index  )
{
	int				iErr		=	-1;

	if  (  !g_pEnv  )  return  -1;
	TMP_MEMORYS_MC	*	pMemorys  =  (  TMP_MEMORYS_MC  *  )g_pEnv->pTmpMemorys;
	if  (  !pMemorys  )  return  -1;

	TMP_MEMORY  *	pMem		=	NULL;

	pMem  =  getTmpMemoryByIndex(  index  );
	MACRO_qyAssert(  pMem,  _T(  "freeTmpMemoryIndex error"  )  );

	InterlockedExchangeAdd(  &pMem->m_cRef,  -1  );

#ifdef  __DEBUG__
		//  traceLog(  _T(  "freeTmpMemoryIndex %d"  ),  index  );
#endif

	iErr  =  0;
	return  iErr;
}

 int  chkTmpMemorys(  )
{
	int				iErr		=	-1;

	if  (  !g_pEnv  )  return  -1;
	TMP_MEMORYS_MC	*	pMemorys  =  (  TMP_MEMORYS_MC  *  )g_pEnv->pTmpMemorys;
	if  (  !pMemorys  )  return  -1;

	int				i;
	CQySyncObj			syncObj;

	if  (  syncObj.sync(  pMemorys->mutexName  )  )  return  -1;

	for  (  i  =  0;  i  <  pMemorys->usMaxCnt;  i  ++  )  {
		 TMP_MEMORY	*  pMem  =  &pMemorys->pMems[i];
		 if  (  pMem->ucbUsed  )  continue;
		 if  (  !pMem->pBuf  )  continue;
		 if  (  InterlockedExchangeAdd(  &pMem->m_cRef,  0  )  )  continue;
		 MACRO_safeFree(  pMem->pBuf  );
	}


	return  0;
}
 
#endif

