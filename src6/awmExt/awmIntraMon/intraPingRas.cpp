//
// PING.C -- Ping program using ICMP and RAW Sockets
//

//  #include <stdio.h>
//  #include <stdlib.h>
//  #include <winsock.h>

#include	<stdio.h>
#include	<stdlib.h>
#include	<winsock2.h>
#include	<ws2tcpip.h>
#include	"qyCommon.h"
#include	"in_systm.h"
#include	"ip.h"
#include	"tcp.h"
#include	"qyBuildPkt.h"
#include	"awmExt.h"


// Internal Functions
void Ping(LPCSTR pstrHost);
void ReportError(LPCSTR pstrFrom);
//int  WaitForEchoReply(SOCKET s);
extern  "C"  u_short in_cksum(u_short *addr, int len);

// ICMP Echo Request/Reply functions
int		SendEchoRequest(SOCKET, LPSOCKADDR_IN);
//DWORD	RecvEchoReply(SOCKET, LPSOCKADDR_IN, u_char *);


// main()
void main(int argc, char **argv)
{
    WSADATA wsaData;
    WORD wVersionRequested = MAKEWORD(1,1);
    int nRet;

	// Check arguments
    if (argc != 2)
    {
		fprintf(stderr,"\nUsage: ping hostname\n");
		return;
    }

	// Init WinSock
    nRet = WSAStartup(wVersionRequested, &wsaData);
    if (nRet)
    {
		fprintf(stderr,"\nError initializing WinSock\n");
		return;
    }

	// Check version
	if (wsaData.wVersion != wVersionRequested)
	{
		fprintf(stderr,"\nWinSock version not supported\n");
		return;
	}

	// Go do the ping
	Ping(argv[1]);

	// Free WinSock
    WSACleanup();
}


// Ping()
// Calls SendEchoRequest() and
// RecvEchoReply() and prints results
void Ping(LPCSTR pstrHost)
{
	SOCKET	  rawSocket;
	LPHOSTENT lpHost;
	struct    sockaddr_in saDest;
//	struct    sockaddr_in saSrc;
//	DWORD	  dwTimeSent;
//	DWORD	  dwElapsed;
//	u_char    cTTL;
	int       nLoop;
	int       nRet;

	// Create a Raw socket
	rawSocket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (rawSocket == SOCKET_ERROR) 
	{
//		ReportError("socket()");
		return;
	}
	
	// Lookup host
	lpHost = gethostbyname(pstrHost);
	if (lpHost == NULL)
	{
		fprintf(stderr,"\nHost not found: %s\n", pstrHost);
		return;
	}
	
	// Setup destination socket address
	saDest.sin_addr.s_addr = *((u_long FAR *) (lpHost->h_addr));
	saDest.sin_family = AF_INET;
	saDest.sin_port = 0;

	// Tell the user what we're doing
	printf("\nPinging %s [%s] with %d bytes of data:\n",
				pstrHost,
				inet_ntoa(saDest.sin_addr),
				REQ_DATASIZE);

	// Ping multiple times
	for (nLoop = 0; nLoop < 4; nLoop++)
	{
		// Send ICMP echo request
		SendEchoRequest(rawSocket, &saDest);

		// Use select() to wait for data to be received
//		nRet = WaitForEchoReply(rawSocket);
//		if (nRet == SOCKET_ERROR)
//		{
//			ReportError("select()");
//			break;
//		}
//		if (!nRet)
//		{
//			printf("\nTimeOut");
//			break;
//		}

		// Receive reply
		//dwTimeSent = RecvEchoReply(rawSocket, &saSrc, &cTTL);

		// Calculate elapsed time
		//dwElapsed = GetTickCount() - dwTimeSent;
		//printf("\nReply from: %s: bytes=%d time=%ldms TTL=%d", 
        //		inet_ntoa(saSrc.sin_addr), 
		//		REQ_DATASIZE,
        //		dwElapsed,
        //		cTTL);
	}
//	printf("\n");
	nRet = closesocket(rawSocket);
//	if (nRet == SOCKET_ERROR)
//		ReportError("closesocket()");
}


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


// RecvEchoReply()
// Receive incoming data
// and parse out fields
//DWORD RecvEchoReply(SOCKET s, LPSOCKADDR_IN lpsaFrom, u_char *pTTL) 
//{
//	ECHOREPLY echoReply;
//	int nRet;
//	int nAddrLen = sizeof(struct sockaddr_in);

	// Receive the echo reply	
//	nRet = recvfrom(s,					// socket
//					(LPSTR)&echoReply,	// buffer
//					sizeof(ECHOREPLY),	// size of buffer
//					0,					// flags
//					(LPSOCKADDR)lpsaFrom,	// From address
//					&nAddrLen);			// pointer to address len
//
	// Check return value
//	if (nRet == SOCKET_ERROR) 
//		ReportError("recvfrom()");

	// return time sent and IP TTL
//	*pTTL = echoReply.ipHdr.TTL;
//	return(echoReply.echoRequest.dwTime);   		
//}



// WaitForEchoReply()
// Use select() to determine when
// data is waiting to be read
//int WaitForEchoReply(SOCKET s)
//{
//	struct timeval Timeout;
//	fd_set readfds;

//	readfds.fd_count = 1;
//	readfds.fd_array[0] = s;
//	Timeout.tv_sec = 5;
//    Timeout.tv_usec = 0;

//	return(select(1, &readfds, NULL, NULL, &Timeout));
//}


 extern  "C"  void  qyTcpScan(  int  s,  char  *  srcIp,  char  *  dstIp,  char  *  data,  unsigned  int  dataSize  )
{
	unsigned  long		ulSrc, ulDst;
	unsigned  short		usPort;
	unsigned  long		ulhAckNo;
	static				nId				=	1;
	static				nSeq			=	1;
	AWM_MON_DATA	*	pAmd			=	(  AWM_MON_DATA  *  )data;
	unsigned  short		usChkSum;
	
	
	if  (  !srcIp  ||  !dstIp  )  return;
	ulSrc = inet_addr( srcIp );
	ulDst = inet_addr( dstIp );
	if ( ulSrc == INADDR_NONE || ulDst == INADDR_NONE ) return;

	dataSize  =  0;
	//  qySendTCP(  ulSrc, ulDst,  1279,  80,  3787944985,  0,  TH_SYN, (  u_char  *  )data,  dataSize,  s  );

	usChkSum  =  in_cksum(  (  unsigned  short  *  )&ulDst,  sizeof(  ulDst  )  );
	
	usPort  =  usChkSum  |  0x8000;

	traceLogA(  "usChkSum is %x, usPort is %x",  usChkSum,  usPort  );

	ulhAckNo  =  ntohl(  ulDst  );
	qySendTCP(  ulSrc,  ulDst,  usPort,  80,  ulhAckNo,  0,  TH_SYN,  (  u_char  *  )data,  0,  s  );
	qySendTCP(  ulSrc,  ulDst,  usPort,  139,  ulhAckNo,  0,  TH_SYN,  (  u_char  *  )data,  0,  s  );
	qySendTCP(  ulSrc,  ulDst,  usPort,  135,  ulhAckNo,  0,  TH_SYN,  (  u_char  *  )data,  0,  s  );

            
	nId ++;
	nSeq ++;

	return;

}


