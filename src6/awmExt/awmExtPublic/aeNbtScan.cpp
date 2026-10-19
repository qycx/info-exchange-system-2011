
#include	<stdio.h>
#include	<stdlib.h>
#include	<winsock2.h>
#include	<ws2tcpip.h>
#include	<sys/timeb.h>
#include	"qyCommon.h"
#include	"in_systm.h"
#include	"ip.h"
#include	"tcp.h"
#include	"udp.h"
#include	"qyBuildPkt.h"
#include	"aeNbtScan.h"




typedef struct ip_hdr
{
    unsigned char  ip_verlen;        // IP version & length
    unsigned char  ip_tos;           // IP type of service
    unsigned short ip_totallength;   // Total length
    unsigned short ip_id;            // Unique identifier 
    unsigned short ip_offset;        // Fragment offset field
    unsigned char  ip_ttl;           // Time to live
    unsigned char  ip_protocol;      // Protocol(TCP,UDP etc)
    unsigned short ip_checksum;      // IP checksum
    unsigned int   ip_srcaddr;       // Source address
    unsigned int   ip_destaddr;      // Destination address
} IP_HDR, *PIP_HDR, FAR* LPIP_HDR;


#ifndef HAVE_GETTIMEOFDAY

extern  "C"  int  gettimeofday(struct timeval *tv, struct timezone *tz)
{
    struct _timeb   timebuffer;

    _ftime(&timebuffer);
    tv->tv_usec = timebuffer.millitm * 1000;
    tv->tv_sec = timebuffer.time;
    return (0);
}
#endif                          /* !HAVE_GETTIMEOFDAY */

#define MAX_MESSAGE        4068
#define MAX_PACKET         4096
//
// Setup some default values 
//
#define DEFAULT_PORT       5150
#define DEFAULT_IP         "10.0.0.1"
#define DEFAULT_COUNT      5
#define DEFAULT_MESSAGE    "This is a test"


//
// Global variables
//
typedef  struct  __aeNbtScan_t		{
				 int				rawSockFd;
				 unsigned  long		dwToIP;						// IP to send to
		 		 unsigned  long		dwFromIP;					// IP to send from (spoof)
				 unsigned  short	usToPort;					// Port to send to
				 unsigned  short	usFromPort;					// Port to send from (spoof)
				 DWORD				dwCount;					// Number of times to send
				 char				data[MAX_MESSAGE];			// Message to send
				 unsigned  short	dataLen;
}		  AE_NBT_SCAN;

int doAeNbtScan(  int  s,  AE_NBT_SCAN  *  pNbtScan  );

//
// Function: usage:
//
// Description:
//    Print usage information and exit
//
 void usage(char *progname)
{
    printf("usage: %s [-fp:int] [-fi:str] [-tp:int] [-ti:str]\
 [-n:int] [-m:str]\n", progname);
    printf("       -fp:int   From (sender) port number\n");
    printf("       -fi:IP    From (sender) IP address\n");
    printf("       -tp:int   To (recipient) port number\n");
    printf("       -ti:IP    To (recipient) IP address\n");
    printf("       -n:int    Number of times to read message\n");
    printf("       -m:str    Size of buffer to read\n\n");
    ExitProcess(1);
}


 int name_mangle( char *In, char *Out, char name_type ) {
	int   i;
	int   c;
	int   len;
	char  buf[20];
	char *p = Out;
	char* scope="";

	/* Safely copy the input string, In, into buf[]. */
	(void)memset( buf, 0, 20 );
	if (strcmp(In,"*") == 0) buf[0] = '*';
	else
#ifdef HAVE_SNPRINTF
		(void)snprintf( buf, sizeof(buf) - 1, "%-15.15s%c", In, name_type );
#else
		(void)sprintf( buf, "%-15.15s%c", In, name_type );
#endif /* HAVE_SNPRINTF */

	/* Place the length of the first field into the output buffer. */
	p[0] = 32;
	p++;

	/* Now convert the name to the rfc1001/1002 format. */
	for( i = 0; i < 16; i++ ) {
		c = toupper( buf[i] );
		p[i*2]     = ( (c >> 4) & 0x000F ) + 'A';
		p[(i*2)+1] = (c & 0x000F) + 'A';
	}
	p += 32;
	p[0] = '\0';

	/* Add the scope string. */
	for( i = 0, len = 0; NULL != scope; i++, len++ ) {
		switch( scope[i] ) {
      		case '\0':
        		p[0]     = len;
        		if( len > 0 ) p[len+1] = 0;
        		return( strlen(Out) );
      		case '.':
        		p[0] = len;
      		p   += (len + 1);
    		len  = 0;
        		break;
      		default:
                        p[len+1] = scope[i];
                	break;
		}
    	}
        return( strlen(Out) );
}; /* name_mangle */
/* end of code from Samba */


 extern  "C"  void  aeNbtScan(  int  s,  char  *  srcIp,  char  *  dstIp,  char  *  data,  unsigned  int  dataSize  )
{
	AE_NBT_SCAN					nbtScan;
	my_uint32_t					rtt_base	=	1000;
	struct  nbname_request		request;
	//  struct  sockaddr_in			dest_sockaddr;
	struct  timeval				tv;
	
	if  (  !srcIp  ||  !dstIp  )  return;

	memset(  &nbtScan,  0,  sizeof(  AE_NBT_SCAN  )  );
	nbtScan.dwFromIP		= inet_addr( srcIp );
	nbtScan.dwToIP			=  inet_addr( dstIp );
	if  (  nbtScan.dwFromIP  ==  INADDR_NONE  ||  nbtScan.dwToIP  ==  INADDR_NONE  )  return;
	nbtScan.usFromPort		=  DEFAULT_UDP_PORT;		//  2004/05/22暂时定
	nbtScan.usToPort		=  NB_DGRAM;
	nbtScan.rawSockFd		=  s;
	 
	//  bzero( (  void  *  )&dest_sockaddr,  sizeof(  dest_sockaddr  )  );
	//  dest_sockaddr.sin_family = AF_INET;
	//  dest_sockaddr.sin_port = htons(NB_DGRAM);
	//  dest_sockaddr.sin_addr = dest_addr;
	//  dest_sockaddr.sin_addr.s_addr  =  nbtScan.dwToIP;
      
	request.flags = htons(FL_BROADCAST);
 	request.question_count = htons(1);
 	request.answer_count = 0;
 	request.name_service_count = 0;
 	request.additional_record_count = 0;
 	name_mangle("*", request.question_name,0);
 	request.question_type = htons(0x21);
 	request.question_class = htons(0x01);

	gettimeofday(&tv, NULL);
	/* Use transaction ID as a timestamp */
	//  request.transaction_id = htons((tv.tv_sec-rtt_base)*1000+tv.tv_usec/1000);
	//  request.transaction_id = htons(  51842  );		//  2004/05/27修改，加入了对ip的校验
	request.transaction_id  =  htons(  in_cksum(  (  u_short  *  )&nbtScan.dwToIP,  sizeof(  nbtScan.dwToIP  )  )  );
	/* printf("%s: timestamp: %d\n", inet_ntoa(dest_addr), request.transaction_id); */

	if  (  sizeof(  request  )  >  sizeof(  nbtScan.data  )  )  {
		traceLogA(  "nbtScan.缓冲太小"  );  goto  errLabel;
	}

	memcpy(  nbtScan.data,  &request,  sizeof(  request  )  );
	nbtScan.dataLen  =  sizeof(  request  );
	doAeNbtScan(  s,  &nbtScan  );
	
errLabel:
	return;

}


 int doAeNbtScan(  int  s,  AE_NBT_SCAN  *  pNbtScan  )
{
	int					iErr		=		-1;
    struct sockaddr_in	remote;       // IP addressing structures
    IP_HDR				ipHdr;
    UDP_HDR				udpHdr;
    int					ret;
    DWORD				i;
    unsigned short		iTotalSize,   // Lots of sizes needed to fill
						iUdpSize,     // the various headers with
						iUdpChecksumSize,
						iIPVersion,
						iIPSize,
						cksum = 0;
    char				buf[MAX_PACKET],
                      *	ptr = NULL;
    IN_ADDR				addr;

    // Parse command line arguments and print them out
    //
    //  ValidateArgs(argc, argv);
    addr.S_un.S_addr = pNbtScan->dwFromIP;
    traceLogA(  "From IP: <%s>\n     Port: %d\n", inet_ntoa(addr),  pNbtScan->usFromPort  );
    addr.S_un.S_addr = pNbtScan->dwToIP;
    traceLogA(  "To   IP: <%s>\n     Port: %d\n", inet_ntoa(addr),  pNbtScan->usToPort  );
    //  traceLogA(  "Message: [%s]\n", pNbtScan->data  );
    //  traceLogA(  "Count:   %d\n", dwCount  );

        
    //  iTotalSize = sizeof(ipHdr) + sizeof(udpHdr) + strlen(strMessage);
	iTotalSize = sizeof(ipHdr) + sizeof(udpHdr) + pNbtScan->dataLen;

    iIPVersion = 4;
    iIPSize = sizeof(ipHdr) / sizeof(unsigned long);
    //
    // IP version goes in the high order 4 bits of ip_verlen. The
    // IP header length (in 32-bit words) goes in the lower 4 bits.
    //
    ipHdr.ip_verlen = (iIPVersion << 4) | iIPSize;
    ipHdr.ip_tos = 0;                         // IP type of service
    ipHdr.ip_totallength = htons(iTotalSize); // Total packet len
    ipHdr.ip_id = 0;                 // Unique identifier: set to 0
    ipHdr.ip_offset = 0;             // Fragment offset field
    ipHdr.ip_ttl = 128;              // Time to live
    ipHdr.ip_protocol = 0x11;        // Protocol(UDP) 
    ipHdr.ip_checksum = 0 ;          // IP checksum
    ipHdr.ip_srcaddr = pNbtScan->dwFromIP;     // Source address
    ipHdr.ip_destaddr = pNbtScan->dwToIP;      // Destination address
    //
    // Initalize the UDP header
    //
    //  iUdpSize = sizeof(udpHdr) + strlen(strMessage);
	iUdpSize = sizeof(udpHdr) + pNbtScan->dataLen;

    //  udpHdr.src_portno = htons(iFromPort) ;
    //  udpHdr.dst_portno = htons(iToPort) ;
    udpHdr.src_portno = htons(  pNbtScan->usFromPort  ) ;
    udpHdr.dst_portno = htons(  pNbtScan->usToPort  ) ;
    udpHdr.udp_length = htons(iUdpSize) ;
    udpHdr.udp_checksum = 0 ;
    // 
    // Build the UDP pseudo-header for calculating the UDP checksum.
    // The pseudo-header consists of the 32-bit source IP address, 
    // the 32-bit destination IP address, a zero byte, the 8-bit
    // IP protocol field, the 16-bit UDP length, and the UDP
    // header itself along with its data (padded with a 0 if
    // the data is odd length).
    //
    iUdpChecksumSize = 0;
    ptr = buf;
    ZeroMemory(buf, MAX_PACKET);

    memcpy(ptr, &ipHdr.ip_srcaddr,  sizeof(ipHdr.ip_srcaddr));  
    ptr += sizeof(ipHdr.ip_srcaddr);
    iUdpChecksumSize += sizeof(ipHdr.ip_srcaddr);

    memcpy(ptr, &ipHdr.ip_destaddr, sizeof(ipHdr.ip_destaddr)); 
    ptr += sizeof(ipHdr.ip_destaddr);
    iUdpChecksumSize += sizeof(ipHdr.ip_destaddr);

    ptr++;
    iUdpChecksumSize += 1;

    memcpy(ptr, &ipHdr.ip_protocol, sizeof(ipHdr.ip_protocol)); 
    ptr += sizeof(ipHdr.ip_protocol);
    iUdpChecksumSize += sizeof(ipHdr.ip_protocol);

    memcpy(ptr, &udpHdr.udp_length, sizeof(udpHdr.udp_length)); 
    ptr += sizeof(udpHdr.udp_length);
    iUdpChecksumSize += sizeof(udpHdr.udp_length);
    
    memcpy(ptr, &udpHdr, sizeof(udpHdr)); 
    ptr += sizeof(udpHdr);
    iUdpChecksumSize += sizeof(udpHdr);

    //  for(i = 0; i < strlen(strMessage); i++, ptr++)  *ptr = strMessage[i];
    //  iUdpChecksumSize += strlen(strMessage);
	for(i = 0; i < pNbtScan->dataLen; i++, ptr++)  *ptr = pNbtScan->data[i];
    iUdpChecksumSize += pNbtScan->dataLen;

    cksum = in_cksum((USHORT *)buf, iUdpChecksumSize);
    udpHdr.udp_checksum = cksum;
    //
    // Now assemble the IP and UDP headers along with the data
    //  so we can send it
    //        
    ZeroMemory(buf, MAX_PACKET);
    ptr = buf;

    memcpy(ptr, &ipHdr, sizeof(ipHdr));   ptr += sizeof(ipHdr);
    memcpy(ptr, &udpHdr, sizeof(udpHdr)); ptr += sizeof(udpHdr);
    //  memcpy(ptr, strMessage, strlen(strMessage));
	memcpy(  ptr,  pNbtScan->data,  pNbtScan->dataLen  );

    // Apparently, this SOCKADDR_IN structure makes no difference.
    // Whatever we put as the destination IP addr in the IP header
    // is what goes. Specifying a different destination in remote
	 // will be ignored.
    //
    remote.sin_family = AF_INET;
    remote.sin_port = htons(  pNbtScan->usToPort  );
    remote.sin_addr.s_addr =  pNbtScan->dwToIP;
   
	ret = sendto(s, buf, iTotalSize, 0, (SOCKADDR *)&remote, sizeof(remote));
    if  (  ret  ==  SOCKET_ERROR  )  {
        traceLogA(  "sendto() failed: %d\n",  WSAGetLastError(  )  );  goto  errLabel;
	}


	iErr  =  0;

errLabel:

    return  iErr;

}

