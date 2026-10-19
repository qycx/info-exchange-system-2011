

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
//  #include	"qyMc.h"
//  #include	"leftView.h"
//  #include	"qyMcView.h"
#include	"qyCusResTemp.h"






//  这里要保证队列不能过长，如果发现超出了，就先从前面去掉几个，然后再添加一个,  2007/06/05
__declspec(  dllexport  )  int  postRecentFriend(  void  *  pSciParam,  void  *  pMisCntParam,  QY_MESSENGER_ID  *  pIdInfo,  int  iOp  )
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int							iErr	=	-1;
	QY_SERVICEGUI_INFO  *  pSci  =  (  QY_SERVICEGUI_INFO  *  )pSciParam;
	MIS_CNT  *  pMisCnt  =  (  MIS_CNT  *  )pMisCntParam;
	CQyMalloc					mallocObj;
	MIS_MSGU				*	pMsg	=	(  MIS_MSGU  *  )mallocObj.malloc(  sizeof(  MIS_MSGU  )  );
	if  (  !pMsg  )  return  -1;
	GENERIC_Q				*	pQ		=	0;
	unsigned  int				len;

	//  这里检查一下。不能是把自己的节点也加进最近使用人系列
	if  (  pIdInfo->ui64Id  ==  pMisCnt->idInfo.ui64Id  )  return  0;

	for  (  ;  ;  )  {		//  这里要保持队列总是被新操作所更新，所以要把前面的一些节点给删除
		 if  (  pMisCnt->recentFriendQ.uiQNodes  <  pMisCnt->recentFriendQ.cfg.uiMaxQNodes  -  10  )  break;
		
		 len  =  sizeof(  pMsg[0]  );
		 if  (  qGetMsg(  &pMisCnt->recentFriendQ,  pMsg,  &len  )  )  goto  errLabel;
		 continue;
	}
	
	memset(  &pMsg->recentFriend_qmc,  0,  sizeof(  pMsg->recentFriend_qmc  )  );
	pMsg->uiType  =  CONST_misMsgType_recentFriend_qmc;
	pMsg->recentFriend_qmc.idInfo.ui64Id  =  pIdInfo->ui64Id;
	pMsg->recentFriend_qmc.iOp  =  iOp;
	pMsg->recentFriend_qmc.dwTickCnt_op  =  GetTickCount(  );

	if  (  qPostMsg(  pMsg,  sizeof(  pMsg->recentFriend_qmc  ),  &pMisCnt->recentFriendQ  )  )  goto  errLabel;
	iErr  =  0;

errLabel:
	return  iErr;

}
