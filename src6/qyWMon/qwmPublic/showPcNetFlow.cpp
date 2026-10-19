

#include	<windows.h>
#include	<winsock.h>
#include	<ras.h>
#include	<raserror.h>
#include	<commctrl.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<iphlpapi.h>
#include	<tchar.h>
#include	"asrWMon.h"
#include	"showPcNetFlow.h"

 int  interruptNetworkCard(  QWM_THREADINFO  *  pThreadInfo,  MIB_IFROW  *  pIfRow,  unsigned  int  nSeconds  );

 BOOL  bDetectNetFlowSupported(  QY_W_MON  *  pQwm  )
{
	 QWM_DYN_LIB	*	pDynLib		=	(  QWM_DYN_LIB  *  )pQwm->env.pDynLibs;

	 if  (  !pDynLib->pGetIfTable  ||  !pDynLib->pSetIfEntry  ||  !pDynLib->pGetIfEntry  )  return  FALSE;
	 if  (  !g_bIsWinNT  ||  pQwm->env.iPlatformId  ==  CONST_qyPlatform_winnt  )  return  FALSE;
	 return  TRUE;
}

 int  fillNetFlowPropByMIB_IFROW(  MIB_IFROW  *  pIfRow,  QY_PCNETFLOW_PROP  *  pProp  )
{
	 pProp->dwIndex  =  pIfRow->dwIndex;		//  很多成员摘自MIB_IFROW
	 pProp->dwType  =  pIfRow->dwType;
	 pProp->dwSpeed  =  pIfRow->dwSpeed;
	 //  dwInSpeed;		//  入流量, 自定义
	 //  DWORD										dwOutSpeed;		//  出流量, 自定义
	 pProp->dwPhysAddrLen  =  pIfRow->dwPhysAddrLen;
	 memcpy(  pProp->bPhysAddr,  pIfRow->bPhysAddr,  min(  sizeof(  pProp->bPhysAddr  ),  sizeof(  pIfRow->bPhysAddr  )  )  );
	 //									
	 pProp->dwMtu  =  pIfRow->dwMtu;
	 pProp->dwAdminStatus  =  pIfRow->dwAdminStatus;
	 pProp->dwOperStatus  =  pIfRow->dwOperStatus;
	 pProp->dwLastChange  =  pIfRow->dwLastChange;
	 pProp->dwInOctets  =  pIfRow->dwInOctets;
	 pProp->dwInUcastPkts  =  pIfRow->dwInUcastPkts;
	 pProp->dwInNUcastPkts  =  pIfRow->dwInNUcastPkts;
	 pProp->dwInDiscards  =  pIfRow->dwInDiscards;
	 pProp->dwInErrors  =  pIfRow->dwInErrors;
	 pProp->dwInUnknownProtos  =  pIfRow->dwInUnknownProtos;
	 pProp->dwOutOctets  =  pIfRow->dwOutOctets;
	 pProp->dwOutUcastPkts  =  pIfRow->dwOutUcastPkts;
	 pProp->dwOutNUcastPkts  =  pIfRow->dwOutNUcastPkts;
	 pProp->dwOutDiscards  =  pIfRow->dwOutDiscards;
	 pProp->dwOutErrors  =  pIfRow->dwOutErrors;
	 pProp->dwOutQLen  =  pIfRow->dwOutQLen;
    			 
	 return  0;   			 
}

 int  getNetFlowIndexByIfIndex(  QY_W_MON  *  pQwm,  DWORD  dwIfIndex  )
{
	 int	i	=	-1;
	 
	 for  (  i  =  0;  (  unsigned  int  )i  <  pQwm->procStruct_netFlow.dwNumEntries;  i  ++  )  {
		  if  (  pQwm->procStruct_netFlow.netFlowProps[i].dwIndex  ==  dwIfIndex  )  return  i;
	 }
	 return  -1;
}

 //  ucbDetectNetFlow是个触发条件，因为流量不能立即得到，需要把入出字节数检测2次才能计算出来
 //  从ucbDetectNetFlow为TRUE开始，detectNetFlow就应该自己设立一个标志位，并在下次调用时计算流量
 //  从ucbShowNetFlow是计算完毕时应该赋值的标志位
 int  detectNetFlow(  QWM_THREADINFO  *  pThreadInfo,  unsigned  char  ucbDetectNetFlow,  unsigned  char  *  pucbShowNetFlow  )
{
	 int						iErr							=	-1;
	 QY_W_MON				*	pQwm							=	(  QY_W_MON  *  )pThreadInfo->pParaentParam;
	 static  unsigned  int		uiDetectCnt						=	0;		//  当cnt为非0，则开始启动检测，检测完毕，则将cnt设为0
	 unsigned  char				tmpucbShowNetFlow				=	FALSE;
	 MIB_IFTABLE			*	pIfTable						=	NULL;
	 MIB_IFROW				*	pIfRow							=	NULL;
	 DWORD						len								=	1024;
	 DWORD						dwDetectNetFlowLastTickCnt		=	0;
	 int						i;
	 int						index;
	 DWORD						dwInSpeed;
	 DWORD						dwOutSpeed;
	 DWORD						dwElapseMilliSeconds;
	 QY_PCNETFLOW_PROP		*	pProp;
	 float						f;
	 unsigned  char				ucbWarn							=	FALSE;
	 QWM_DYN_LIB			*	pDynLib							=	(  QWM_DYN_LIB  *  )pQwm->env.pDynLibs;
	 
	 if  (  !bDetectNetFlowSupported(  pQwm  )  )  return  -1;

	 if  (  !uiDetectCnt  )  {
		 if  (  ucbDetectNetFlow  )  uiDetectCnt  =  1;  	//  这里为触发
		 else  goto  errLabel;
		}
	 else  uiDetectCnt  ++  ;

	 traceLogA(  "detectNetFlow enters"  );
	 
	 len  =  1024;
	 if  (  !(  pIfTable  =  (  MIB_IFTABLE  *  )malloc(  len  )  )  )  goto  errLabel;
	 if  (  pDynLib->pGetIfTable(  pIfTable,  &len,  TRUE  )  ==  ERROR_INSUFFICIENT_BUFFER  )  {
		 free(  pIfTable  );  pIfTable  =  NULL;
		 if  (  !(  pIfTable  =  (  MIB_IFTABLE  *  )malloc(  len  )  )  )  goto  errLabel;
		 if  (  pDynLib->pGetIfTable(  pIfTable,  &len,  TRUE  )  !=  NO_ERROR  )  goto  errLabel;		 
	 }
	 dwDetectNetFlowLastTickCnt  =  GetTickCount(  );
	 if  (  pIfTable->dwNumEntries  >  mycountof(  pQwm->procStruct_netFlow.netFlowProps  )  )  {
		 #ifdef  __DEBUG__
				 traceLogA(  "too many entries,  %d",  pIfTable->dwNumEntries  );  
		 #endif
		 //  goto  errLabel;
	 }
	 if  (  uiDetectCnt  ==  1  )  {
		 memset(  &pQwm->procStruct_netFlow,  0,  sizeof(  &pQwm->procStruct_netFlow  )  );
		 pQwm->procStruct_netFlow.dwNumEntries  =  min(  mycountof(  pQwm->procStruct_netFlow.netFlowProps  ),  pIfTable->dwNumEntries  );
		 for  (  i  =  0;  (  unsigned  int  )i  <  pQwm->procStruct_netFlow.dwNumEntries;  i  ++  )  {
			  pIfRow  =  &pIfTable->table[i];
			  pProp  =  &pQwm->procStruct_netFlow.netFlowProps[i];

			  fillNetFlowPropByMIB_IFROW(  pIfRow,  pProp  );
		 }
		}
	 else  {  //  后面的次数可以用来计算流量了
		   if  (  pQwm->procStruct_netFlow.dwNumEntries  !=  min(  mycountof(  pQwm->procStruct_netFlow.netFlowProps  ),  pIfTable->dwNumEntries  )  )  {
			   traceLog(  _T(  "Serious error: dwNumEntries is not correct"  )  );
			   goto  errLabel;
		   }

		   for  (  i  =  0;  (  unsigned  int  )i  <  pQwm->procStruct_netFlow.dwNumEntries;  i  ++  )  {
			    pIfRow  =  &pIfTable->table[i];
				//
				index  =  getNetFlowIndexByIfIndex(  pQwm,  pIfRow->dwIndex  );
				if  (  index  <  0  )  continue;	//  这里是异常，可能是中间检测过程中网卡被禁掉或卸载了
				pProp  =  &pQwm->procStruct_netFlow.netFlowProps[index];
				//  
				dwElapseMilliSeconds  =  dwDetectNetFlowLastTickCnt  -  pQwm->procStruct_netFlow.dwDetectNetFlowLastTickCnt;
				if  (  !dwElapseMilliSeconds  )  continue;	//  这里也异常，不允许被0除
				//
				dwInSpeed  =  (  DWORD  )(  (  pIfRow->dwInOctets  -  pProp->dwInOctets  )  *  8  /  (  float  )dwElapseMilliSeconds  *  1000.  );
				dwOutSpeed  =  (  DWORD  )(  (  pIfRow->dwOutOctets  -  pProp->dwOutOctets  )  *  8  /  (  float  )dwElapseMilliSeconds  *  1000.  );

				//  再用新的数据来替代procStruct_netFlow里的数据
				memset(  pProp,  0,  sizeof(  pProp[0]  )  );
				fillNetFlowPropByMIB_IFROW(  pIfRow,  pProp  );	
				pProp->dwInSpeed  =  dwInSpeed;
				pProp->dwOutSpeed  =  dwOutSpeed;
		   }

		   //  下面计算报警流量
		   if  (  pQwm->cfg.pcRules.pcNetFlow.uiWarnPercentOfBandWithFactor  )  {
			   for  (  i  =  0;  (  unsigned  int  )i  <  pQwm->procStruct_netFlow.dwNumEntries;  i  ++  )  {
				    pProp  =  &pQwm->procStruct_netFlow.netFlowProps[i];
					if  (  pProp->dwType  !=  MIB_IF_TYPE_ETHERNET  )  continue;		//  只报警以太网卡
					if  (  !pProp->dwSpeed  )  continue;								//  异常
					f  =  (  float  )(  (  pProp->dwInSpeed  +  pProp->dwOutSpeed  )  /  (  float  )pProp->dwSpeed  );
					if  (  f  *  CONST_fakedFactor_percentOfBand  *  100.  >  pQwm->cfg.pcRules.pcNetFlow.uiWarnPercentOfBandWithFactor  )  {
						pProp->ucWarnCnt  ++  ;
						ucbWarn  =  TRUE;					
					}
			   }
		   }


	 }

	 if  (  uiDetectCnt  >  1  )  {
		 if  (  !ucbWarn  )  {				//  没有报警则随时关上检测，并发送
			 tmpucbShowNetFlow  =  TRUE;
			 uiDetectCnt  =  0;  
		 }
	 }

	 if  (  uiDetectCnt  >  1  &&  uiDetectCnt  >  pQwm->cfg.pcRules.pcNetFlow.ucDetectTimesBeforeWarn  )  {			//  持续达到报警条件2次，则启动报警，并关闭检测
		 pQwm->procStruct_netFlow.ucbWarn  =  TRUE;
		 tmpucbShowNetFlow  =  TRUE;
		 uiDetectCnt  =  0;  
	 }

	 pQwm->procStruct_netFlow.dwDetectNetFlowLastTickCnt  =  dwDetectNetFlowLastTickCnt;

	 iErr  =  0;

errLabel:

	 if  (  pIfTable  )  free(  pIfTable  );
	 if  (  iErr  )  {
	 	 uiDetectCnt  =  0;		// 出错则检测停止
	 }
	 if  (  !iErr  )  {
		 if  (  pucbShowNetFlow  )  *pucbShowNetFlow  =  tmpucbShowNetFlow;
	 }

	 traceLogA(  "detectNetFlow leaves"  );

	 return  iErr;
}


 int	 showPcNetFlow(  QWM_THREADINFO  *  pThreadInfo  )
{
	 int						iErr			=	-1;
	 QY_W_MON				*	pQwm			=	NULL;
	 QY_PC_COMMU				pcCommU;
	 int						len;
	 QWM_SESSION				session;
	 QY_SOCK					sock;
	 BOOL						bSessionOpen	=	FALSE;
	 char						buf[1024]		=	"";
	 QY_COMM_RESP				tmpResp;

	 
	 if  (  !pThreadInfo  )  return  -1;
	 pQwm  =  (  QY_W_MON  *  )pThreadInfo->pParaentParam;

	 if  (  !bDetectNetFlowSupported(  pQwm  )  )  return  -1;
	 
	 traceLogA(  "showPcNetFlow enters"  );

	 clearQySock(  &sock  );
	 memset(  &session,  0,  sizeof(  session  )  );

	 if  (  qwmOpenSession(  pQwm,  &session,  &sock  )  )  goto  errLabel;
	 bSessionOpen		=		TRUE;
	 if  (  !isRcOk(  session.comm.usLastRespCode_i  )  )  goto  errLabel;

	 memset(  &pcCommU,  0,  sizeof(  pcCommU  )  );
	 MACRO_makePcCommHead(  CONST_pcCommType_netFlow,  pQwm,  pcCommU  );
	 //
	 memcpy(  pcCommU.netFlows.mems,  pQwm->procStruct_netFlow.netFlowProps,  sizeof(  pcCommU.netFlows.mems  )  );
	 pcCommU.netFlows.cnt  =  pQwm->procStruct_netFlow.dwNumEntries;
	 if  (  (  len  =  qyhtonQyPcCommU(  0,  &pcCommU  )  )  ==  -1  )  goto  errLabel;
	 if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_showPcNetFlow,  (  char  *  )&pcCommU,  len  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;

	 memset(  &pcCommU,  0,  sizeof(  pcCommU  )  );		  
	 MACRO_makePcCommHead(  CONST_pcCommType_netFlow,  pQwm,  pcCommU  );
	 //  发结束符
	 pcCommU.head.ucFlg  =  -1;
	 if  (  (  len  =  qyhtonQyPcCommU(  0,  &pcCommU  )  )  ==  -1  )  goto  errLabel;
	 if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_showPcNetFlow,  (  char  *  )&pcCommU,  len  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;
	 
	 iErr  =  0;

errLabel:


	 if  (  bSessionOpen  )  qwmCloseSession(  pQwm,  &session,  &sock  );

	 traceLogA(  "showPcNetFlow leaves"  );

	 return  iErr;
}


  int  popupWndForNetFlowWarn(  unsigned  char  ucbDownNetworkCard,  unsigned  int  showSeconds  )
{
	 TCHAR	buf[32]	=	_T(  ""  );

	 _sntprintf(  buf,  mycountof(  buf  ),  _T(  "%d%d"  ),  (  ucbDownNetworkCard  ?  1  :  0  ),  showSeconds  );
	 return  qwmCmdBySubProcess(  0,  _T(  CONST_qwmCmdLine_netFlowWarn  ),  buf,  NULL  );  
}


 //  MIB_IF_ADMIN_STATUS_UP
 //  MIB_IF_ADMIN_STATUS_DOWN
 int  procNetFlowWarn(  QWM_THREADINFO  *  pThreadInfo  )
{
	 int					i;
	 QY_W_MON			*	pQwm		=	(  QY_W_MON  *  )pThreadInfo->pParaentParam;
	 QY_PCNETFLOW_PROP	*	pProp		=	NULL;
	 MIB_IFROW				ifRow;
	 int					cnt;
	 unsigned  char			ucbLogged	=	FALSE;	
	 char					buf[256];
	 char					buf1[256];
	 unsigned  char			ucbDown		=	FALSE;
	 QWM_DYN_LIB		*	pDynLib		=	(  QWM_DYN_LIB  *  )pQwm->env.pDynLibs;


	 if  (  !bDetectNetFlowSupported(  pQwm  )  )  return  -1;

	 if  (  !pQwm->procStruct_netFlow.ucbWarn  )  return  0;

	 if  (  pQwm->cfg.pcRules.pcNetFlow.ucWarnedNetworkCardCmd  ==  CONST_devCmd_prohibited  )  ucbDown  =  TRUE;


	 //  报警提示
	 if  (  pQwm->cfg.pcRules.pcNetFlow.ucbPopupToWarn  )  {
		 traceLogA(  "这里应弹出一个对话框来提示一下"  );
		 popupWndForNetFlowWarn(  ucbDown,  pQwm->cfg.pcRules.pcNetFlow.usStopNetworkCardTimeInSecond  );
	 }

	 //  注意：这里的起禁网卡是个原子过程，不能中间调用一个goto或return退出，要确保网卡的恢复
	 if  (  ucbDown  )  {

		 unsigned  char  ucbUseIpHlp	=	FALSE;

		 switch  (  pQwm->env.iPlatformId  )  {
				 case  CONST_qyPlatform_win2k:
				   case  CONST_qyPlatform_winxp:
				 case  CONST_qyPlatform_win2003:
					   ucbUseIpHlp  =  TRUE;
					   break;
				 default:
						break;
		 }

		 if  (  ucbUseIpHlp  )  {

			 //  禁用网卡
			 for  (  cnt  =  pQwm->cfg.pcRules.pcNetFlow.usStopNetworkCardTimeInSecond;  !pQwm->bQuit  &&  cnt  >=  0;  cnt  --  )  {

				 for  (  i  =  0;  !pQwm->bQuit  &&  (  unsigned  int  )i  <  pQwm->procStruct_netFlow.dwNumEntries;  i  ++  )  {
					  pProp  =  &pQwm->procStruct_netFlow.netFlowProps[i];
			  		  if  (  !pProp->ucWarnCnt  )  continue;
			  		  memset(  &ifRow,  0,  sizeof(  ifRow  )  );
			  		  ifRow.dwIndex  =  pProp->dwIndex;
		  			  if  (  pDynLib->pGetIfEntry(  &ifRow  )  !=  NO_ERROR  )  continue;
					  if  (  ifRow.dwAdminStatus  ==  MIB_IF_ADMIN_STATUS_DOWN  )  continue;  		  
					  ifRow.dwAdminStatus  =  MIB_IF_ADMIN_STATUS_DOWN;
					  if  (  pDynLib->pSetIfEntry(  &ifRow  )  !=  NO_ERROR  )  {
						  traceLogA(  "down networkCard failed"  );  continue;
					  }
			  	 }
			 
				 Sleep(  1000  );

			 }

			 //  恢复网卡
			 for  (  i  =  0;  (  unsigned  int  )i  <  pQwm->procStruct_netFlow.dwNumEntries;  i  ++  )  {
				  pProp  =  &pQwm->procStruct_netFlow.netFlowProps[i];
				  if  (  !pProp->ucWarnCnt  )  continue;
				  memset(  &ifRow,  0,  sizeof(  ifRow  )  );
				  ifRow.dwIndex  =  pProp->dwIndex;
				  if  (  pDynLib->pGetIfEntry(  &ifRow  )  !=  NO_ERROR  )  continue;
				  if  (  ifRow.dwAdminStatus  !=  MIB_IF_ADMIN_STATUS_DOWN  )  continue;  		  
				  ifRow.dwAdminStatus  =  MIB_IF_ADMIN_STATUS_UP;
				  if  (  pDynLib->pSetIfEntry(  &ifRow  )  !=  NO_ERROR  )  {
					  traceLogA(  "Error: restart networkCard failed"  );
				  }		  
			 }
		 
			}  //  end of useIpHelp
		 else  {	//  2007/02/19, 在vista里，使用iphlp禁不了网卡的通信，所以只好用禁止网卡的方式来完成
			   
			   for  (  i  =  0;  (  unsigned  int  )i  <  pQwm->procStruct_netFlow.dwNumEntries;  i  ++  )  {
				    pProp  =  &pQwm->procStruct_netFlow.netFlowProps[i];			  		  
				    if  (  !pProp->ucWarnCnt  )  continue;			   
			   	   	memset(  &ifRow,  0,  sizeof(  ifRow  )  );
				   	ifRow.dwIndex  =  pProp->dwIndex;
				   	if  (  pDynLib->pGetIfEntry(  &ifRow  )  ==  NO_ERROR  )  {
						interruptNetworkCard(  pThreadInfo,  &ifRow,  pQwm->cfg.pcRules.pcNetFlow.usStopNetworkCardTimeInSecond  ); 
					}
					break;	//  这里的方法不同于iphlp方法，不能继续循环，只能处理一个网卡就跳出了，不再处理了。
			   }
		 }

	 }


//  errLabel:

	 if  (  !ucbLogged  )  {		 
		 for  (  i  =  0;  (  unsigned  int  )i  <  pQwm->procStruct_netFlow.dwNumEntries;  i  ++  )  {
			  pProp  =  &pQwm->procStruct_netFlow.netFlowProps[i];
			  if  (  !pProp->ucWarnCnt  )  continue;
			  memset(  &ifRow,  0,  sizeof(  ifRow  )  );
			  ifRow.dwIndex  =  pProp->dwIndex;
			  if  (  pDynLib->pGetIfEntry(  &ifRow  )  !=  NO_ERROR  )  continue;
			  if  (  !pProp->dwSpeed  )  continue;							//  异常
			  buf[0]  =  0;
			  for  (  unsigned  int  j  =  0;  j  <  min(  pProp->dwPhysAddrLen,  mycountof(  pProp->bPhysAddr  )  );  j  ++  )  {
				   _snprintf(  buf,  mycountof(  buf  ),  "%s%02x",  buf,  pProp->bPhysAddr[j]  );
		 	  }
			  _snprintf(  buf,  mycountof(  buf  ),  "%s( %s ): %s",  buf,  ifRow.bDescr,  !ucbDown  ?  "warning"  :  "network is suspended"  );
			  _snprintf(  buf1,  mycountof(  buf1  ),  "InSpeed=%dkbps, OutSpeed=%dkbps. %.3f%% ( > %dkbps, %.3f%% )",  pProp->dwInSpeed  /  1000,  pProp->dwOutSpeed  /  1000,  (  pProp->dwInSpeed  +  pProp->dwOutSpeed  )  *  100.  /  (  float  )pProp->dwSpeed,  pProp->dwSpeed  /  1000,  pQwm->cfg.pcRules.pcNetFlow.uiWarnPercentOfBandWithFactor  /  (  float  )CONST_fakedFactor_percentOfBand  );

			  qwmLogGeneralEvent(  pThreadInfo,  CONST_qyEventType_nm_netFlowWarn,  NULL,  buf,  buf1,  0  );
		 }
	 }

	 return  0;

}


