


#include	<windows.h>            // required for all Windows applications
#include	<windowsx.h>

#include	<stdlib.h>
#include	<ras.h>
#include	<raserror.h>
#include	<lm.h>
#include	<iphlpapi.h>
#include	<tchar.h>
//  #include	<iostream.h>
#include	"asrWMon.h"
//  #include	"osversion.h"
#include	"config.h"
#include	"main.h"





#ifdef  __DEBUG__
 int  printTcpTable(  PMIB_TCPTABLE  pTcpTable  )
{
	 int			i;
	 MIB_TCPROW	*	pTcp;

	 traceLogA(  "共%d个连接",  pTcpTable->dwNumEntries  );
	 for  (  i  =  0;  i  <  (  int  )pTcpTable->dwNumEntries;  i  ++  )  {
		  pTcp  =  &pTcpTable->table[i];
		  traceLogA(  "localIp is %s, localPort is %d, remoteIp is %s, remotePort is %d, state is %s",  inet_ntoa(  *(  in_addr  *  )&pTcp->dwLocalAddr  ),  ntohs(  (  unsigned  short  )pTcp->dwLocalPort  ),  inet_ntoa(  *(  in_addr  *  )&pTcp->dwRemoteAddr  ),  ntohs(  (  unsigned  short  )pTcp->dwRemotePort  ),  qyGetDesByType1(  CONST_tcpStateTable,  pTcp->dwState  )  );
	 }
	 
	 return  0;
}
#endif

 int  sndNetStat(  QWM_THREADINFO  *  pThreadInfo  )
{
	 int					iErr					=	-1;
	 QY_W_MON		*		pQwm					=	(  QY_W_MON  *  )pThreadInfo->pParaentParam;
	 BYTE			*		pTcpBuf					=	NULL;
	 BYTE			*		pUdpBuf					=	NULL;
	 DWORD					dwTableSize; 
	 DWORD					lRet; 
	 int					i						=	0; 
	 PMIB_TCPTABLE			pTcpTable;						//  保存TCP的链表 
	 PMIB_UDPTABLE			pUdpTable;						//  保存UDP的链表 
	 DWORD					dTcpNum;					//  tcp  数目 
	 DWORD					dUdpNum;					//  udp  数目 
	 QWM_SESSION			session;	
	 BOOL					bSessionOpen			=	FALSE;
	 QY_SOCK				sock;
	 int					cntRemains				=	0;
	 QY_PC_COMMU			pcCommU;
	 unsigned  int			len;
	 QY_COMM_RESP			tmpResp;
	 char					buf[4096];
	 QWM_DYN_LIB		*	pDynLib					=	(  QWM_DYN_LIB  *  )pQwm->env.pDynLibs;

	 if  (  !pDynLib->pGetTcpTable  ||  !pDynLib->pGetUdpTable  )  return  0;

 	 traceLogA(  "sndNetStat enters"  );

	 memset(  &session,  0,  sizeof(  session  )  );
	 clearQySock(  &sock  );

	 if  (  qwmOpenSession(  pQwm,  &session,  &sock  )  )  goto  errLabel;
	 bSessionOpen  =  TRUE;

	 dwTableSize  =  0;
	 if  (  ERROR_INSUFFICIENT_BUFFER  !=  (  lRet  =  pDynLib->pGetTcpTable(  (  PMIB_TCPTABLE  )pTcpBuf,  &dwTableSize,  false  )  )  )  goto  errLabel;
	 dwTableSize  +=  20  *  sizeof(  MIB_TCPROW  );
	 if  (  !(  pTcpBuf  =  (  BYTE  *  )malloc(  dwTableSize  )  )  )  goto  errLabel;
 	 if  (  NO_ERROR  !=  (  lRet  =  pDynLib->pGetTcpTable(  (  PMIB_TCPTABLE  )pTcpBuf,  &dwTableSize,  false  )  )  )  goto  errLabel;
	 pTcpTable  =  (  PMIB_TCPTABLE  )pTcpBuf; 
 	 dTcpNum  =  pTcpTable->dwNumEntries;		//  保存到成员函数 

	 #ifdef  __DEBUG__
			 //  printTcpTable(  pTcpTable  );
	 #endif
	 /********************************************************************************* 

	 格式：编号^状态^本地IP^本地端口^外部IP^外部端口\r\n

	 **********************************************************************************/ 
	 cntRemains  =  dTcpNum;
	 for  (  ;  cntRemains;  )  {

		  //  这里开始复位
		  memset(  &pcCommU,  0,  sizeof(  pcCommU  )  );
		  MACRO_makePcCommHead(  CONST_pcCommType_tcpTable,  pQwm,  pcCommU  );
		  pcCommU.head.cnt  =  sizeof(  pcCommU.tcpTable.mems  )  /  sizeof(  pcCommU.tcpTable.mems[0]  );
		  if  (  cntRemains  <  (  int  )pcCommU.head.cnt  )  pcCommU.head.cnt  =  cntRemains;
		  memcpy(  &pcCommU.tcpTable.mems,  &pTcpTable->table[dTcpNum  -  cntRemains],  pcCommU.head.cnt  *  sizeof(  pcCommU.tcpTable.mems[0]  )  ); 
		  cntRemains  -=  pcCommU.head.cnt;	
		  
		  if  (  (  len  =  qyhtonQyPcCommU(  0,  &pcCommU  )  )  ==  -1  )  goto  errLabel;
		  if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_sndNetStat,  (  char  *  )&pcCommU,  len  )  )  goto  errLabel;
		  if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;
		  //
		  
	 }

 	 dwTableSize  =  0;
 	 if  (  ERROR_INSUFFICIENT_BUFFER  !=  pDynLib->pGetUdpTable(  (  PMIB_UDPTABLE  )pUdpBuf,  &dwTableSize,  false  )  )  goto  errLabel;
	 dwTableSize  +=  20  *  sizeof(  MIB_UDPROW  );
	 if  (  !(  pUdpBuf  =  (  BYTE  *  )malloc(  dwTableSize  )  )  )  goto  errLabel;
 	 if  (  NO_ERROR  !=  pDynLib->pGetUdpTable(  (  PMIB_UDPTABLE  )pUdpBuf,  &dwTableSize,  false  )  )  goto  errLabel;
	 pUdpTable  =  (  PMIB_UDPTABLE  )pUdpBuf; 
 	 dUdpNum  =  pUdpTable->dwNumEntries;   //  保存到成员函数 
	 /*********************************************************************************
	 格式：编号^IP^端口\r\n
	 **********************************************************************************/ 
	 cntRemains  =  dUdpNum;
	 for  (  ;  cntRemains;  )  {

		  //  这里开始复位
		  memset(  &pcCommU,  0,  sizeof(  pcCommU  )  );
		  MACRO_makePcCommHead(  CONST_pcCommType_udpTable,  pQwm,  pcCommU  );
		  pcCommU.head.cnt  =  sizeof(  pcCommU.udpTable.mems  )  /  sizeof(  pcCommU.udpTable.mems[0]  );
		  if  (  cntRemains  <  (  int  )pcCommU.head.cnt  )  pcCommU.head.cnt  =  cntRemains;
		  memcpy(  &pcCommU.udpTable.mems,  &pUdpTable->table[dUdpNum  -  cntRemains],  pcCommU.head.cnt  *  sizeof(  pcCommU.udpTable.mems[0]  )  ); 
		  cntRemains  -=  pcCommU.head.cnt;	
		  
		  if  (  (  len  =  qyhtonQyPcCommU(  0,  &pcCommU  )  )  ==  -1  )  goto  errLabel;
		  if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_sndNetStat,  (  char  *  )&pcCommU,  len  )  )  goto  errLabel;
		  if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;
		  //
		  
	 }


	 //  发送结束符
	 memset(  &pcCommU,  0,  sizeof(  pcCommU  )  );
	 MACRO_makePcCommHead(  CONST_pcCommType_tcpTable,  pQwm,  pcCommU  );
	 pcCommU.head.ucFlg  =  -1;
	 if  (  (  len  =  qyhtonQyPcCommU(  0,  &pcCommU  )  )  ==  -1  )  goto  errLabel;
	 if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_sndNetStat,  (  char  *  )&pcCommU,  len  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  buf,  sizeof(  buf  )  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:

	 if  (  bSessionOpen  )  qwmCloseSession(  pQwm,  &session,  &sock  );
	 if  (  pTcpBuf  )  free(  pTcpBuf  );
	 if  (  pUdpBuf  )  free(  pUdpBuf  );

	 traceLogA(  "sndNetStat leaves"  );
	 return  iErr;

}


