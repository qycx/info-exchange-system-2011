
#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<windows.h>
#include	<assert.h>
#include	<tchar.h>
#ifndef  __WINCE__
	#include	<vfw.h>
#else
	#ifdef  __TEST__
		#include	<vfw.h>
	#endif
	#include	<mmreg.h>
	#include	<mSAcm.h>
#endif

#include	"qyCommon.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"
#include	"qyCommProc.h"
#include	"qmOpenCommon.h"

#include	"qySyncCommProc.h"
#include	"genericQueue.h"
#include	"qyq2.h"				//  2009/05/13

#include	"qnmCommProc.h"
#include	"qnmCommProc_mis.h"
#include	"qyWmComm_is.h"



 QY_DMITEM  CONST_misMsgTypeTable[]  =
{
	{	CONST_misMsgType_null,									_T(  "msg_null"  ),					},
	{	CONST_misMsgType_resp_onlySock,							_T(  "msg_resp_onlySock"  ),		},
	{	CONST_misMsgType_quit,									_T(  "msg_quit"  ),					},
	{	CONST_misMsgType_closeSession,							_T(  "msg_closeSession"  ),			},
	{	CONST_misMsgType_input,									_T(  "msg_input"  ),				},
	{	CONST_misMsgType_send,									_T(  "msg_send"  ),					},
	{	CONST_misMsgType_processSelf,							_T(  "msg_processSelf"  ),			},
	//  {	CONST_misMsgType_resumeToSend,						_T(  "msg_resumeToSend"  ),		},
	//  以上是动作
	{	CONST_misMsgType_req,									_T(  "msg_req"  ),					},
	{	CONST_misMsgType_resp,									_T(  "msg_resp"  ),					},
	{	CONST_misMsgType_talk,									_T(  "msg_talk"  ),					},
	{	CONST_misMsgType_task,									_T(  "msg_task"  ),					},
	//
	//
	{	CONST_misMsgType_isSendOk,								_T(  "msg_isSendOk"  ),				},
	{	CONST_misMsgType_sendOk,								_T(  "msg_sendOk"  ),				},
	{	CONST_misMsgType_sendFinished,							_T(  "msg_sendFinished"  ),			},
	{	CONST_misMsgType_closeChannel,							_T(  "msg_closeChannel"  ),			},
	//
	{	CONST_misMsgType_applyForWork,							_T(  "msg_applyForWork"  ),			},
	//
	{	CONST_misMsgType_taskStatus,							_T(  "msg_taskStatus"  ),			},
	//  以上是包类型
	{	CONST_misMsgType_talkingFriend_qmc,						_T(  "msg_talkingFriend_qmc"  ),	},
	{	CONST_misMsgType_recentFriend_qmc,						_T(  "msg_recentFriend_qmc"  ),		},
	{	CONST_misMsgType_displayedElem_qmc,						_T(  "msg_displayedElem_qmc"  ),	},
	{	CONST_misMsgType_refreshContactsStatus_qmc,				_T(  "msg_refreshContactsStatus_qmc"  ),	},
	{	CONST_misMsgType_refreshMeStatus_qmc,					_T(  "msg_refreshMeStatus_qmc"  ),	},
	{	CONST_misMsgType_applyForPlayer_qmc,					_T(  "msg_applyForPlayer_qmc"  ),	},
	{	CONST_misMsgType_applyForChkChannels_qmc,				_T(  "msg_applyForChkChannels_qmc"  ),	},
	{	CONST_misMsgType_applyForChkTasks_qmc,					_T(  "msg_applyForChkTasks_qmc"  ),		},
	{	CONST_misMsgType_applyForTalkerShadow_qmc,				_T(  "msg_applyForTalkerShadow_qmc"  ),	},
	//
	{	CONST_misMsgType_procVideo_qmc,							_T(  "msg_procVideo_qmc"  ),			},
	{	CONST_misMsgType_notifyTaskEnd_qmc,						_T(  "msg_notifyCapEnd_qmc"  ),			},
	{	CONST_misMsgType_procGps_qmc,							_T(  "msg_procGps_qmc"  ),				},
	//
	{	CONST_misMsgType_getDaemonStatus,						_T(  "msg_getDaemonStatus"  ),		},
	//
	{	CONST_misMsgType_outputTask,							_T(  "msg_outputTask"  ),			},
	{	CONST_misMsgType_outputTask_toMix,						_T(  "msg_outputTask_toMix"  ),		},

	//  2008/05/26
	{	CONST_misMsgType_grp,									_T(  "msg_grp"  ),					},

	//
	{	-1,						},
};




