
#include	"stdafx.h"

#include	<windows.h>
#include	<tchar.h>
#include	<time.h>
#include	<stdlib.h>
#include	"qyCommon.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyDefs_open.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCustom.h"
#include	"qyTCharCommProc.h"

#include	"tmpCeLib.h"

//  Globals
QY_ENV	*	g_pEnv			=	NULL;


//
 QY_DMITEM  CONST_qyServiceIdTable[]  =
{
	{	CONST_qyServiceId_netMc,						_T(  "NetMc"  ),	},
	{	CONST_qyServiceId_is,							_T(  "Is"  ),		},
	{	-1,					},
};


 QY_DMITEM	CONST_qyAppTypeTable[]  =
{
	{	CONST_qyAppType_null,							_T(  ""  ),					},
	{	CONST_qyAppType_mc,								_T(  "mc"  ),				},		//  ???í????
	{	CONST_qyAppType_interMonOfBhb,					_T(  "interMon"  ),			},		//  bhb???????à????
	{	-1,												NULL,				},
};






 
 QY_DMITEM  CONST_qyCmdTable[]  =
{
	//  ????±?????
	{	CONST_qyCmd_tellService,						_T(  "tellService"  ),				},
	{	CONST_qyCmd_end,								_T(  "end"  ),						},
	//  ???§?¨??:
	{	CONST_qyCmd_usr,								_T(  "usr"  ),						},
	{	CONST_qyCmd_getGlCntIp,							_T(  "getGlCntIp"  ),					},
	{	CONST_qyCmd_getCfgs,							_T(  "getCfgs"  ),						},
	{	CONST_qyCmd_sndLog,								_T(  "sndLog"  ),						},
	{	CONST_qyCmd_reg,								_T(  "reg"  ),							},
	//  {	CONST_qyCmd_commWithGlCnt,					_T(  "commWithGlCnt"  ),				},
	{	CONST_qyCmd_showQwmInfo,						_T(  "showQwmInfo"  ),					},
	{	CONST_qyCmd_queryReg,							_T(  "queryReg"  ),						},
	{	CONST_qyCmd_getProxyCfgs,						_T(  "getProxyCfgs"  ),					},
	{	CONST_qyCmd_putProxyChkedPcsInfo,				_T(  "putProxyChkedPcsInfo"  ),			},
	{	CONST_qyCmd_getProxyChkedPcsInfo,				_T(  "getProxyChkedPcsInfo"  ),			},
	{	CONST_qyCmd_getMacByIp,							_T(  "getMacByIp"  ),					},
	{	CONST_qyCmd_refreshProxyPolicy,					_T(  "refreshProxyPolicy"  ),			},
	{	CONST_qyCmd_getProxyStatusParams,				_T(  "getProxyStatusParams"  ),			},
	{	CONST_qyCmd_policyChanged,						_T(  "policyChanged"  ),				},
	{	CONST_qyCmd_quit,								_T(  "quit"  ),							},
	{	CONST_qyCmd_sndSecChkLog,						_T(  "sndSecChkLog"  ),					},
	{	CONST_qyCmd_secChkGetCfgs,						_T(  "secChkGetCfgs"  ),				},
	{	CONST_qyCmd_showQwmInfoEx,						_T(  "showQwmInfoEx"  ),				},
	{	CONST_qyCmd_showQwmAssetsInfo,					_T(  "showQwmAssetsInfo"  ),			},
	{	CONST_qyCmd_endShowQwmAssetsInfo,				_T(  "endShowQwmAssetsInfo"  ),			},
	{	CONST_qyCmd_queryPcSp,							_T(  "queryPcSp"  ),					},
	{	CONST_qyCmd_showQwmSvrStatus,					_T(  "showQwmSvrStatus"  ),				},
	{	CONST_qyCmd_showPcNetworkProp,					_T(  "showPcNetworkProp"  ),			},
	{	CONST_qyCmd_tryToConnectToServer,				_T(  "tryToConnectToServer"  ),			},
	{	CONST_qyCmd_showPcProcess,						_T(  "showPcProcess"  ),				},
	{	CONST_qyCmd_sndEventLog,						_T(  "sndEventLog"  ),					},
	{	CONST_qyCmd_sndUsrInfo,							_T(  "sndUsrInfo"  ),					},
	{	CONST_qyCmd_sndNetStat,							_T(  "sndNetStat"  ),					},
	{	CONST_qyCmd_sndPrinters,						_T(  "sndPrinters"  ),					},
	{	CONST_qyCmd_queryAutoLogon,						_T(  "queryAutoLogon"  ),				},
	{	CONST_qyCmd_sndAutoLogon,						_T(  "sndAutoLogon"  ),					},
	{	CONST_qyCmd_getOpCmd,							_T(  "getOpCmd"  ),						},
	{	CONST_qyCmd_sndCapScreen,						_T(  "sndCapScreen"  ),					},
	{	CONST_qyCmd_queryCfgs,							_T(  "queryCfgs"  ),					},
	{	CONST_qyCmd_showPcProcessModule,				_T(  "showPcProcessModule"  ),			},
	{	CONST_qyCmd_retrieveWarningMsg,					_T(  "retrieveWarningMsg"  ),			},
	{	CONST_qyCmd_sndRegistryVals,					_T(  "sndRegistryVals"  ),				},
	{	CONST_qyCmd_showPcNetFlow,						_T(  "showPcNetFlow"  ),				},
	{	CONST_qyCmd_showPcNetShare,						_T(  "showPcNetShare"  ),				},
	//
	{	CONST_qyCmd_talkTo,								_T(  "talkTo"  ),						},	//  2007/04/09
	{	CONST_qyCmd_refreshImObjListReq,				_T(  "refreshImObjListReq"  ),			},	//  2007/05/06
	{	CONST_qyCmd_refreshRecentFriendsReq,			_T(  "refreshRecentFriendsReq"  ),		},
	//
	{	CONST_qyCmd_getDaemonStatus,					_T(  "getDaemonStatus"  ),				},	//  2011/01/09
	//
	{	CONST_qyCmd_sendTask,							_T(  "sndTask"  ),						},
	{	CONST_qyCmd_sendTaskReply,						_T(  "sndTaskReply"  ),				},
	{	CONST_qyCmd_sendRobotTask,						_T(  "sndRobotTask"  ),				},
	{	CONST_qyCmd_sendRobotTaskReply,					_T(  "sndRobotTaskReply"  ),			},
	{	CONST_qyCmd_sendRobotTaskData,					_T(  "sndRobotTaskData"  ),			},
	//
	{	CONST_qyCmd_sendMedia,							_T(  "sndMedia"  ),					},	//  2008/03/15
	//
	{	CONST_qyCmd_lastMsgInSession,					_T(  "lastMsgInSession"  ),				},	//  2007/12/11
	//
	{	CONST_qyCmd_sendVDevReq,						_T(  "sndVDevReq"  ),					},	//  2008/01/24
	//
	//  ????±?????
	{	CONST_qyCmd_upReserved,							_T(  "upReserved"  ),					},
	{	CONST_qyCmd_update,								_T(  "update"  ),						},
	{	CONST_qyCmd_getFile,							_T(  "getFile"  ),						},
	{	CONST_qyCmd_getDigest,							_T(  "getDigest"  ),					},
	{	-1,												NULL,						},
};




 QY_DMITEM  CONST_qyRcTable[]  =  
{
	 //  ????±???
	{	CONST_qyRc_ok,					_T(  "OK"  ),						},
	{	CONST_qyRc_err,					_T(  "Err"  ),						},
	 //			 ???§?¨??
	{	CONST_qyRc_user,				_T(  "User"  ),					},
	{	CONST_qyRc_redirect,			_T(  "Redirect"  ),					},
	{	CONST_qyRc_needAutoReg,			_T(  "Need auto req"  ),				},
	//  #define		CONST_qyRc_notFound
	{	CONST_qyRc_needVerified,		_T(  "Need verified"  ),				},
	//
	{	CONST_qyRc_peerOffline,			_T(  "Peer offline"  ),				},
	{	CONST_qyRc_servBusy,			_T(  "Serv busy"  ),				},
	//
	//			 ????±???
	{	CONST_qyRc_upReserved,			_T(  "Up reserved"  ),					},
	{	CONST_qyRc_quit,				_T(  "Quit"  ),						},
	{	CONST_qyRc_update,				_T(  "Update"  ),						},
	{	-1,								NULL,						},
};


 //  鉴于CONST_qyRet_err定义为-1, 故将显示""
 QY_DMITEM	CONST_qyRetTable[]  =
{
	{	CONST_qyRet_ok,					_T(  "OK"  ),						},
	{	CONST_qyRet_redirect,			_T(  "Redirect"  ),					},
	{	CONST_qyRet_update,				_T(  "Update"  ),						},
	{	CONST_qyRet_quit,				_T(  "Quit"  ),						},
	{	-1,								NULL,						},
};



#if  0
 extern  "C"  unsigned  int  getuiNextTranNo(  void  *  p0,  void  *  p1,  long  *  puiTranNo  )		//  2008/04/01, 将交易号的产生由使用mutex改为interlocked..也许会快一点。
{
	 static	 long	uiTranNo		=	0;

	 return  InterlockedIncrement(  puiTranNo  ?  puiTranNo  :  &uiTranNo  );
}
#endif

 //  2010/09/04
 extern  "C"  unsigned  int	getuiNextTranNo(  void  *  p0,  long  val,  long  *  puiTranNo  )
{
	static	 long	suiTranNo		=	0;

	if  (  !val  )  val  =  1;
	if  (  !puiTranNo  )  puiTranNo  =  &suiTranNo;

	return  InterlockedExchangeAdd(  puiTranNo,  val  )  +  1;
}





  extern  "C"  time_t  gettTimeBylStr(  char  *  timeBuf  )
{
	int			iErr	=	-1;
	char		buf[5];
	struct tm	tm;
	time_t		t1 = 0;

	memset( &tm, 0, sizeof( struct tm ) );
	memcpy( buf, timeBuf, 4 );
	buf[4] = 0;
	tm.tm_year += atol( buf ) - 1900;
	memcpy( buf, timeBuf + 4, 2 );
	buf[2] = 0;
	tm.tm_mon += atol( buf ) - 1;
	memcpy( buf, timeBuf + 6, 2 );
	tm.tm_mday += atol( buf );
	memcpy( buf, timeBuf + 8, 2 );
	tm.tm_hour += atol( buf );
	memcpy( buf, timeBuf + 10, 2 );
	tm.tm_min += atol( buf );
	memcpy( buf, timeBuf + 12, 2 );
	tm.tm_sec += atol( buf );

	t1  =  mymktime( &tm );
	if  (  t1  ==  -1  )  goto  errLabel;

	iErr  =  0;
    
errLabel:
	  
	return  iErr  ?  iErr  :  t1;

}






 extern  "C"  int  getTimeStr(  time_t  t,  char  *  timeBuf,  unsigned  int  size  )
{
	 struct  tm		*	p		=	NULL;
	 struct  tm			when;
     
	 if  (  !timeBuf  )  return  -1;
	 if  (  !(  p  =  mygmtime(  &t  )  )  )  return  -1;

     when  =  *p;		 
	 _snprintf(  timeBuf,  size,  "%04d%02d%02d%02d%02d%02d",  when.tm_year  +  1900,
				when.tm_mon  +  1,  when.tm_mday,  when.tm_hour,  when.tm_min,
		 		when.tm_sec  );        
   
	 return  0;

}


 extern  "C"  int  waitForObject(  HANDLE  *  ph, DWORD  dwMilliseconds   )  
{  
	DWORD	dwRet  =  0;														

	if  (  !ph  )  return  -1;

	if  (  *ph  )  {											

		dwRet  =  WaitForSingleObject(  *ph,  dwMilliseconds   );				
		if  (  dwRet  !=  WAIT_TIMEOUT  &&  dwRet  !=  WAIT_FAILED  )  {	

			CloseHandle(  *ph  );  *ph  =  NULL;								

		}																											
	}																		

	return  0;

}


 extern  "C"  BOOL  bTaskAlive(  int  iStatus  )
{
	switch  (  iStatus  )  {
			case  0:
			case  CONST_imTaskStatus_req:
			case  CONST_imTaskStatus_resp:  
			case  CONST_imTaskStatus_applyToSend:
			case  CONST_imTaskStatus_waitToSend:
			case  CONST_imTaskStatus_applyToRecv:
			case  CONST_imTaskStatus_waitToRecv:
			case  CONST_imTaskStatus_acceptedByReceiver:
			case  CONST_imTaskStatus_dualByReceiver:
				  return  TRUE;
				  break;
			default:
					break;
	}
	return  FALSE;

 }

#if  0
  extern  "C"  BOOL  bTaskSender(  int  iStatus  )
{
	switch  (  iStatus  )  {
			case  CONST_imTaskStatus_req:
			case  CONST_imTaskStatus_applyToSend:
			case  CONST_imTaskStatus_waitToSend:
			case  CONST_imTaskStatus_acceptedByReceiver:
			case  CONST_imTaskStatus_dualByReceiver:
				  return  TRUE;
				  break;
			default:
					break;
	}
	return  FALSE;
}
#endif
