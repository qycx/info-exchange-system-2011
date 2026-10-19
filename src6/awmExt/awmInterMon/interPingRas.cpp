//
// PING.C -- Ping program using ICMP and RAW Sockets
//


//  #include <stdio.h>
//  #include <stdlib.h>
//  #include <winsock.h>
//  #include "commonFunc.h"
//  #include "awmExt.h"

#include	<stddef.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<winsock2.h>
#include	<ws2tcpip.h>
#include	"qyCommon.h"
#include	"in_systm.h"
#include	"ip.h"
#include	"tcp.h"
#include	"udp.h"
#include	"awmExt.h"


// Internal Functions
void Ping(LPCSTR pstrHost);
void ReportError(LPCSTR pstrFrom);
int  WaitForEchoReply(SOCKET s);
u_short in_cksum(u_short *addr, int len);




// SendEchoRequest()
// Fill in echo request header
// and send to destination
int SendEchoRequest(SOCKET s,LPSOCKADDR_IN lpstToAddr) 
{
	static ECHOREQUEST echoReq;
	static nId = 1;
	static nSeq = 1;
	int nRet;

	// Fill in echo request
	echoReq.icmpHdr.Type		= ICMP_ECHOREQ;
	echoReq.icmpHdr.Code		= 0;
	echoReq.icmpHdr.Checksum	= 0;
	echoReq.icmpHdr.ID			= nId++;
	echoReq.icmpHdr.Seq			= nSeq++;

	// Fill in some data to send
	for (nRet = 0; nRet < REQ_DATASIZE; nRet++)
		echoReq.cData[nRet] = ' '+nRet;

	// Save tick count when sent
	echoReq.dwTime				= GetTickCount();

	// Put data in packet and compute checksum
	echoReq.icmpHdr.Checksum = in_cksum((u_short *)&echoReq, sizeof(ECHOREQUEST));

	// Send the echo request  								  
	nRet = sendto(s,						/* socket */
				 (LPSTR)&echoReq,			/* buffer */
				 sizeof(ECHOREQUEST),
				 0,							/* flags */
				 (LPSOCKADDR)lpstToAddr, /* destination */
				 sizeof(SOCKADDR_IN));   /* address length */

	if (nRet == SOCKET_ERROR) 
		ReportError("sendto()");
	return (nRet);
}

 int processAwmIcmpEchoReply( AWM_EXT *pAE, ECHOREPLY *pER, AWM_MON_PROC_INFO *pAMPI, INTER_MON_THREAD_PROC_INFO *pIMTPI )
{
	int							iErr								=	-1;
	AWM_MON_DATAEx				amd;
	int							decLen;

	//  2004/05/23加入了对包大小的判断
	if  (  pAMPI->nRecvd  <  offsetof(  ECHOREPLY,  cFiller  )  )  {
		traceLogA(  "收到了不完整的数据包：nRecvd is %d, 包大小应>=%d",  pAMPI->nRecvd,  offsetof(  ECHOREPLY,  cFiller  )  );
		goto  errLabel;
	}

	decLen  =  sizeof(  amd  );
	if  (  qyDec(  pAE->pEncCtx,  pER->echoRequest.cData,  REQ_DATASIZE,  (  char  *  )&amd,  (  unsigned  int  *  )&decLen  )  )  goto  errLabel;
	memset(  (  (  char  *  )&amd  )  +  decLen,  0,  sizeof(  amd  )  -  decLen  );

	_snprintf(  amd.hint,  sizeof(  amd.hint  ),  "%s",  "icmp"  );		//  2004/05/24

	if  (  processAwmExtData(  pAE,  (  char  *  )&amd,  sizeof(  amd  ),  pAMPI,  pIMTPI  )  )  goto  errLabel;

	iErr  =  0;

errLabel:
	
	return  iErr;
}

 int processAwmIcmpInfo( AWM_EXT *pAE, ECHOREPLY *pER, AWM_MON_PROC_INFO *pAMPI, INTER_MON_THREAD_PROC_INFO *pIMTPI )
{
	char buf[1024];

	switch ( pER->echoRequest.icmpHdr.Type ) {
		case ICMP_ECHOREPLY:
			sprintf( buf, "processAwmIcmpInfo( ): icmpType is echoReply.\n" );
			OutputDebugString( buf );
			processAwmIcmpEchoReply( pAE, pER, pAMPI, pIMTPI );
			break;
		default:
			sprintf( buf, "processAwmIcmpInfo( ): icmpType is %d.\n", pER->echoRequest.icmpHdr.Type );
			OutputDebugString( buf );
			goto errLabel;
	}

errLabel:
	return 0;

}



 /*
  int  processAwmUdpInfo(  AWM_EXT  *  pAE,  ECHOREPLY  *  pER,  AWM_MON_PROC_INFO  *  pAMPI,  INTER_MON_THREAD_PROC_INFO  *  pIMTPI  )
{
	 int							iErr	=	-1;
	 struct	 ip					*	pIp		=	(  struct  ip  *  )pER;
	 int							ip_hl;
	 UDP_HDR					*	pUdp	=	NULL;
	 //  struct  in_addr				tmpIn;
	 //  unsigned  short				usPort;
	 //  unsigned  short				usChkSum;
	// 	 AWM_MON_DATA					tmpAmd;
	 
	 traceLogA(  "processAwmUdpInfo enters"  );

	 ip_hl  = pIp->ip_hl << 2;
	 pUdp  =  (  UDP_HDR  *  )(  (  (  char  *  )pER  )  +  ip_hl  );

	 traceLogA(  "srcPort is %d,  dstPort is %d",  ntohs(  pUdp->src_portno  ),  ntohs(  pUdp->dst_portno  )  );
	 //  traceLogA(  "原始usPort is %04x, chSum is %04x",  usPort,  usChkSum  );
	 //  traceLogA(  "get scanned ip is %s",  inet_ntoa(  tmpIn  )  );

	 OutputDebugString(  "processAwmUdpInfo:  没有实现udp的处理\n"  );

	 /*

	 memset(  &tmpAmd,  0,  sizeof(  tmpAmd  )  );
	 memcpy(  tmpAmd.magic,  AWM_MON_MAGIC,  min(  sizeof(  tmpAmd.magic  ),  strlen(  AWM_MON_MAGIC  )  )  );
	 //  对TCP包，不能有officeName和subOfficeName
	 memcpy(  tmpAmd.ucIp,  &tmpIn.s_addr,  sizeof(  tmpIn.s_addr  )  );

	 //  if  (  processAwmExtData(  pAE,  (  char  *  )&tmpAmd,  NULL,  pIMTPI  )  )  goto  errLabel;
	

	 iErr  =  0;

//  errLabel:

	 traceLogA(  "processAwmUdpInfo leaves"  );

	 return  iErr;
}
*/



 int  processAwmTcpInfo(  AWM_EXT  *  pAE,  ECHOREPLY  *  pER,  AWM_MON_PROC_INFO  *  pAMPI,  INTER_MON_THREAD_PROC_INFO  *  pIMTPI  )
{
	 int							iErr	=	-1;
	 struct	 ip					*	pIp		=	(  struct  ip  *  )pER;
	 int							ip_hl;
	 struct  tcphdr				*	pTcp	=	NULL;
	 struct  in_addr				tmpIn;
	 unsigned  short				usPort;
	 unsigned  short				usChkSum;
	 AWM_MON_DATAEx					amd;
	 
	 traceLogA(  "processAwmTcpInfo enters"  );

	 ip_hl  = pIp->ip_hl << 2;
	 pTcp  =  (  struct  tcphdr  *  )(  (  (  char  *  )pER  )  +  ip_hl  );

	 if  (  !(  pTcp->th_flags  &  TH_ACK  )  )  {
		 traceLogA(  "processAwmTcpInfo: It's not my tcp packet."  );
		 goto  errLabel;
	 }

	 tmpIn.s_addr  =  htonl(  ntohl(  pTcp->th_ack  )  -  1  );

	 usPort  =  ntohs(  pTcp->th_dport  );
	 usChkSum  =  in_cksum(  (  u_short  *  )&tmpIn.s_addr,  sizeof(  tmpIn.s_addr  )  );
	 
	 traceLogA(  "原始dPort is %04x, chSum is %04x",  usPort,  usChkSum  );
	 traceLogA(  "get scanned ip is %s, recvdIp is %s",  inet_ntoa(  tmpIn  ),  pAMPI->recvdIp  );
	 
	 if  (  usPort  !=  (  0x8000  |  usChkSum  )  )  {
		 traceLogA(  "收到校验错误的数据包，丢弃"  );
		 goto  errLabel;
	 }
	 traceLogA(  "校验成功"  );
	 
#ifdef		__NEW_AESWK__
	//  这一校验舍弃，是因为此版本不需要校验数据包从何而来
#else
	if ( inet_addr( pAMPI->recvdIp ) != tmpIn.S_un.S_addr ) {
		debugLog( "Captured ip is not ucIp, so discarded." );
		goto errLabel;
	}
#endif


	 memset(  &amd,  0,  sizeof(  amd  )  );
	 memcpy(  amd.magic,  AWM_MON_MAGIC,  min(  sizeof(  amd.magic  ),  strlen(  AWM_MON_MAGIC  )  )  );
	 //  对TCP包，不能有officeName和subOfficeName
	 memcpy(  amd.ucIp,  &tmpIn.s_addr,  sizeof(  tmpIn.s_addr  )  );

	 _snprintf(  amd.hint,  sizeof(  amd.hint  ),  "%s %d",  "tcp",  ntohs(  pTcp->th_sport  )  );		//  2004/05/24

	 if  (  processAwmExtData(  pAE,  (  char  *  )&amd,  sizeof(  amd  ),  pAMPI,  pIMTPI  )  )  goto  errLabel;
	
	 iErr  =  0;

errLabel:

	 traceLogA(  "processAwmTcpInfo leaves"  );

	 return  iErr;
}


  int  processAwmUdpInfo(  AWM_EXT  *  pAE,  AWM_MON_PROC_INFO  *  pAMPI,  INTER_MON_THREAD_PROC_INFO  *  pIMTPI  )
{
	 int						iErr							=	-1;
	 struct  nb_host_info  *	hostinfo						=	NULL;
	 int						i;
	 unsigned  char				service; /* 16th byte of NetBIOS name */
	 int						unique;
	 int						first_name						=	1;
	 AWM_MON_DATAEx				amd;
	 unsigned  long				ulIp;

	 //  traceLogA(  "processAmdUdpInfo enters，未完成."  );
	 hostinfo = (struct nb_host_info*)parse_response(  pAMPI->dataBuf,  pAMPI->nRecvd  );
	 if  (  !hostinfo  )  {
		 traceLogA(  "parse_response returned NULL"  );  goto  errLabel;
	 }

	 memset(  &amd,  0,  sizeof(  amd  )  );
	 memcpy(  amd.magic,  AWM_MON_MAGIC,  min(  sizeof(  amd.magic  ),  strlen(  AWM_MON_MAGIC  )  )  );
	 ulIp  =  inet_addr(  pAMPI->recvdIp  );
	 memcpy(  amd.ucIp,  &ulIp,  sizeof(  amd.ucIp  )  );
	 
	 if  (  hostinfo->header  &&  hostinfo->names  )  {
		 for  (  i  =  0;  i  <  hostinfo->header->number_of_names;  i  ++  )  {
			  service  =  hostinfo->names[i].ascii_name[15];
      		  unique  =  !(  hostinfo->names[i].rr_flags  &  0x0080  );
      		  if  (  service  ==  0  &&  unique  &&  first_name  )  {
				  /* Unique name, workstation service - this is computer name */ 
				  _snprintf(  amd.compName,  sizeof(  amd.compName  ),  "%s",  hostinfo->names[i].ascii_name  );
				  first_name  =  0;
			  };
      		  if  (  service  ==  0x20  &&  unique  )  amd.is_server  =  1;      		 
			  if  (  service  ==  0x03  &&  unique  )  {
				  _snprintf(  amd.usrName,  sizeof(  amd.usrName  ),  "%s",  hostinfo->names[i].ascii_name  );      		 
			  }
    	 };
  	 };
	
	 //  traceLogA(  "%-17s%-17s",  tpcInfo.ip,  pcInfo.compName  );
	 //  if  (  pcInfo.is_server  )  traceLogA(  "%-10s",  "<server>"  ); 
	 //  traceLogA(  "%s",  pcInfo.usrName  );
  	
  	 if  (  hostinfo->footer  )  {
		 //  2004/04/21加
		 _snprintf(  amd.mac,  sizeof(  amd.mac  ),  "%02x%02x%02x%02x%02x%02x",
					 hostinfo->footer->adapter_address[0],  hostinfo->footer->adapter_address[1],
	   				 hostinfo->footer->adapter_address[2],  hostinfo->footer->adapter_address[3],
	   				 hostinfo->footer->adapter_address[4],  hostinfo->footer->adapter_address[5]  );		
  		
	 } 
	 //  traceLogA(  "mac is %s",  pcInfo.mac  );

	 traceLogA(  "transaction_id is 0x%04x",  hostinfo->header->transaction_id  );
	 if  (  hostinfo->header->transaction_id  !=  in_cksum(  (  u_short  *  )&ulIp,  sizeof(  ulIp  )  )  )  {
		 traceLogA(  "udp校验失败, 不是我们需要的包"  );  goto  errLabel;
	 }

	 _snprintf(  amd.hint,  sizeof(  amd.hint  ),  "%s",  "udp"  );		//  2004/05/24

	 if  (  processAwmExtData(  pAE,  (  char  *  )&amd,  sizeof(  amd  ),  pAMPI,  pIMTPI  )  )  goto  errLabel;
	
	 iErr  =  0;
errLabel:
	 if  (  hostinfo  )   freeNbHostInfo(  	hostinfo  );
	 return  iErr;
}



 int processAwmInfo( AWM_EXT *pAE, ECHOREPLY *pER, AWM_MON_PROC_INFO *pAMPI, INTER_MON_THREAD_PROC_INFO *pIMTPI )
{
	 char  buf[1024];

	 switch  (  pER->ipHdr.Protocol  )  {
			 case  IPPROTO_ICMP:
				   processAwmIcmpInfo( pAE, pER, pAMPI, pIMTPI );
				   OutputDebugString( "It's a ICMP packet.\n" );
				   break;
			 case  IPPROTO_TCP:
				   processAwmTcpInfo(  pAE,  pER,  pAMPI,  pIMTPI  );
				   OutputDebugString(  "It's a TCP packet.\n"  );
				   break;
			 case  IPPROTO_UDP:
				   //  processAwmUdpInfo(  pAE,  pER,  pAMPI,  pIMTPI  );
				   OutputDebugString(  "It's a UDP packet.\n"  );
				   break;
			 default:
					 sprintf( buf, "processAwmInfo( ): captured a packet, the protocol is %d.\n", pER->ipHdr.Protocol );
					 // OutputDebugString( buf );
					 goto  errLabel;
	 }

errLabel:

	 return 0;
	
}




  extern  "C"  BOOL  bQyIpLocal(  unsigned  long  ulAddr  )
{
	BOOL				bRet	=	FALSE;
	char				ac[256];
	int					i		=	0;
	struct  hostent  *  phe		=	NULL;
    
	if  (  gethostname(  ac,  sizeof(  ac  )  )  ==  SOCKET_ERROR  )  {
        goto  errLabel;
    }
	
    phe  =  gethostbyname(  ac  );
    if  (  phe  ==  0  )  {
        goto  errLabel;
    }
    
    for  (  i  =  0;  phe->h_addr_list[i]  !=  0;  ++  i  )  {
         struct  in_addr  addr;
         
		 memcpy( &addr,  phe->h_addr_list[i],  sizeof(  struct  in_addr  )  );

		 if  (  addr.s_addr  ==  ulAddr  )  {
			 bRet  =  TRUE;	
			 goto  errLabel;
		 }

    }
    	
errLabel:

    return  bRet;

}



#define DW_ERR	( DWORD )( -1 )
// RecvEchoReply()
// Receive incoming data
// and parse out fields
 DWORD RecvEchoReply( void *pAEParam, SOCKET s, LPSOCKADDR_IN lpsaFrom, u_char *pTTL, void *pIMTPIParam ) 
{
	AWM_EXT						*	pAE			=	( AWM_EXT * )pAEParam;
	INTER_MON_THREAD_PROC_INFO	*	pIMTPI		=	( INTER_MON_THREAD_PROC_INFO * )pIMTPIParam;
	int								nRet;
	int								nAddrLen	=	sizeof(struct sockaddr_in);
	AWM_MON_PROC_INFO				aMPI;
	ECHOREPLY					*	pEchoReply	=	(  ECHOREPLY  *  )&aMPI.dataBuf;

	// Receive the echo reply	
	nRet  =  recvfrom(  s,							//  socket
						(  LPSTR  )aMPI.dataBuf,	//  buffer
						sizeof(  aMPI.dataBuf  ),	//  size of buffer
						0,							//	flags
						(  LPSOCKADDR  )lpsaFrom,	//  From address
						&nAddrLen  );				//  pointer to address len

	// Check return value
	if  (  nRet  ==  SOCKET_ERROR  )  { 
		OutputDebugString(  "RecvEchoReply( ): recvfrom() failed.\n"  );
		return  DW_ERR;
	}
	aMPI.nRecvd = nRet;


	/*
	if  (  pIMTPI->sa.sin_addr.s_addr  !=  echoReply.ipHdr.iaDst.s_addr  )  {
		OutputDebugString(  "不是发给本监视端的包。\n"  );
		return  DW_ERR;
	}
	*/
	if  (  !bQyIpLocal(  pEchoReply->ipHdr.iaDst.s_addr  )  )  {
		OutputDebugString(  "不是发给本监视端的包。\n"  );
		//  traceLogA(  "RecvEchoReply: dstIp is %s",  inet_ntoa(  echoReply.ipHdr.iaDst  )  );
		return  DW_ERR;
	}

	if  (  !inet_ntoa(  lpsaFrom->sin_addr  )  )  return  DW_ERR;
	_snprintf(  aMPI.recvdIp,  sizeof(  aMPI.recvdIp  ),  "%s",  inet_ntoa(  lpsaFrom->sin_addr  )  );

	processAwmInfo(  pAE,  pEchoReply,  &aMPI,  pIMTPI  );
	// return time sent and IP TTL
	*pTTL  =  pEchoReply->ipHdr.TTL;

	return  (  pEchoReply->echoRequest.dwTime  );
	
}



 
 DWORD  RecvUdpReply(  void  *  pAEParam,  SOCKET  s,  LPSOCKADDR_IN  lpsaFrom,  u_char  *  pTTL,  void  *  pIMTPIParam  ) 
{
	AWM_EXT						*	pAE		=  (  AWM_EXT * )pAEParam;
	INTER_MON_THREAD_PROC_INFO	*	pIMTPI	=  (  INTER_MON_THREAD_PROC_INFO * )pIMTPIParam;
	int								nRet;
	int								nAddrLen = sizeof(struct sockaddr_in);
	AWM_MON_PROC_INFO				aMPI;


	// Receive the echo reply	
	nRet  =  recvfrom(  s,  						//  socket
						(  LPSTR  )aMPI.dataBuf,			//  buffer
						sizeof(  aMPI.dataBuf  ),			//  size of buffer
						0,							//  flags
						(  LPSOCKADDR  )lpsaFrom,	// From address
						&nAddrLen  );				// pointer to address len

	//  Check return value
	if  (  nRet  ==  SOCKET_ERROR  )  { 
		OutputDebugString( "RecvEchoReply( ): recvfrom() failed.\n");  
		return  DW_ERR;
	}

	aMPI.nRecvd = nRet;
	if ( !inet_ntoa( lpsaFrom->sin_addr ) ) return DW_ERR;
	_snprintf(  aMPI.recvdIp,  sizeof(  aMPI.recvdIp  ),  "%s",  inet_ntoa(  lpsaFrom->sin_addr  )  );

	processAwmUdpInfo(  pAE,  &aMPI,  pIMTPI  );
	// return time sent and IP TTL
	*pTTL  =  0;

	return  0;   		
}



// WaitForEchoReply()
// Use select() to determine when
// data is waiting to be read
int WaitForEchoReply(SOCKET s)
{
	struct timeval Timeout;
	fd_set readfds;

	readfds.fd_count = 1;
	readfds.fd_array[0] = s;
	Timeout.tv_sec = 5;
    Timeout.tv_usec = 0;

	return(select(1, &readfds, NULL, NULL, &Timeout));
}


