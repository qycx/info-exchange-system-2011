

#include	<winsock2.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	"in_systm.h"
#include	"ip.h"
#include	"ip_icmp.h"
#include	"awmext.h"

int		qyGetRegCfg( char *rootKey, char *cfgName, char *cfgVal, int size );
int		qySetRegCfg( char *rootKey, char *cfgName, char *cfgVal );

// What happened?
 void  ReportError(  LPCSTR  pWhere  )
{
}

 void awmOutputStr( char *str, AWM_EXT *pAE )
{

	OutputDebugString( str );
	OutputDebugString( "\n" );

}


 //
// Mike Muuss' in_cksum() function
// and his comments from the original
// ping program
//
// * Author -
// *	Mike Muuss
// *	U. S. Army Ballistic Research Laboratory
// *	December, 1983

/*
 *			I N _ C K S U M
 *
 * Checksum routine for Internet Protocol family headers (C Version)
 *
 */
u_short in_cksum(u_short *addr, int len)
{
	register int nleft = len;
	register u_short *w = addr;
	register u_short answer;
	register int sum = 0;

	/*
	 *  Our algorithm is simple, using a 32 bit accumulator (sum),
	 *  we add sequential 16 bit words to it, and at the end, fold
	 *  back all the carry bits from the top 16 bits into the lower
	 *  16 bits.
	 */
	while( nleft > 1 )  {
		sum += *w++;
		nleft -= 2;
	}

	/* mop up an odd byte, if necessary */
	if( nleft == 1 ) {
		u_short	u = 0;

		*(u_char *)(&u) = *(u_char *)w ;
		sum += u;
	}

	/*
	 * add back carry outs from top 16 bits to low 16 bits
	 */
	sum = (sum >> 16) + (sum & 0xffff);	/* add hi 16 to low 16 */
	sum += (sum >> 16);			/* add carry */
	answer = ~sum;				/* truncate to 16 bits */
	return (answer);
}


unsigned short ip_in_cksum(struct ip *iph, unsigned short *ptr, int nbytes)
{

	register long sum = 0;	/* assumes long == 32 bits */
	u_short oddbyte;
	int pheader_len;
	unsigned short *pheader_ptr;
	
	struct pseudo_header {
		unsigned long saddr;
		unsigned long daddr;
		unsigned char null;
		unsigned char proto;
		unsigned short tlen;
	} pheader;
	
	pheader.saddr = iph->ip_src.s_addr;
	pheader.daddr = iph->ip_dst.s_addr;
	pheader.null = 0;
	pheader.proto = iph->ip_p;
	pheader.tlen = htons(  (  unsigned  short  )nbytes  );

	pheader_ptr = (unsigned short *)&pheader;
	for (pheader_len = sizeof(pheader); pheader_len; pheader_len -= 2) {
		sum += *pheader_ptr++;
	}
	while (nbytes > 1) {
		sum += *ptr++;
		nbytes -= 2;
	}
	if (nbytes == 1) {	/* mop up an odd byte, if necessary */
		oddbyte = 0;	/* make sure top half is zero */
		*(u_char *) (& oddbyte) = *(u_char *) ptr;	/* one byte only */
		sum += oddbyte;
	}
	sum = (sum >> 16) + (sum & 0xFFFF);
	return ~(sum  + (sum >> 16)) & 0xFFFF;
}


 void awmIcmpEcho( int s, char *srcIp, char *dstIp, char *data, unsigned int dataSize )
{
	unsigned long ulSrc, ulDst;
	static nId = 1;
	static nSeq = 1;
	
	if ( !srcIp || !dstIp ) return;
	ulSrc = inet_addr( srcIp );
	ulDst = inet_addr( dstIp );
	if ( ulSrc == INADDR_NONE || ulDst == INADDR_NONE ) return;

	icmp_echo( s, ulSrc, ulDst, nId, nSeq, data, dataSize );
	nId ++;
	nSeq ++;

	return;

}

 void icmp_echo( int s, unsigned long int src, unsigned long int dest, 
			   int id, int seq, char *data, unsigned int datasize)
{

  unsigned char			*packet;
  unsigned int			packetSize = 0;
  struct   ip			*ip;
  ECHOREQUEST			*pER;

  struct   sockaddr_in	sin_dst;
  int n;
#define IPHDRSIZE sizeof( struct ip )		// 20

  int i = sizeof( ECHOREQUEST );

  packetSize = IPHDRSIZE + sizeof( ECHOREQUEST );
  packet = (char *)malloc( packetSize + 1 );
  if (packet == NULL) {
	perror("malloc");
	exit(ERROR);
  }

  
  memset( packet, 0, packetSize + 1 );
  ip       = (struct ip   *)packet;
  pER = ( ECHOREQUEST * )( packet + IPHDRSIZE );
  // icmp     = (struct icmp *)(packet + IPHDRSIZE);
  // icmpdata = ( char * )(packet + IPHDRSIZE + ICMPHDRSIZE);

  // ip->saddr    		=  src;
  ip->ip_src    		=  *( struct in_addr * )&src;
  // ip->daddr    		=  dest;
  ip->ip_dst	    	=  *( struct in_addr * )&dest;
  // ip->version  		=  4;
  ip->ip_v		  		=  4;
  // ip->ihl      		=  5;
  ip->ip_hl      		=  5;
  // ip->ttl      		=  255;
  ip->ip_ttl      		=  255;
  // ip->protocol 		=  1;
  ip->ip_p		 		=  IPPROTO_ICMP;
  // ip->tot_len  		=  htons(IPHDRSIZE + ICMPHDRSIZE + datasize);
  ip->ip_len	  		=  htons( ( short )packetSize );
  // ip->tos      		=  0;
  ip->ip_tos			=  0;
  // ip->id       		=  0;
  ip->ip_id       		=  0;
  // ip->frag_off 		=  0;
  ip->ip_off	 		=  0;
  // ip->check          =  0;
  ip->ip_sum			=  0;
  // ip->check          =  in_cksum(ip, IPHDRSIZE);
  ip->ip_sum			=  in_cksum( ( u_short * )ip, IPHDRSIZE );
  // icmp->type         =  8;
  // icmp->icmp_type		=  8;
  // icmp->code         =  0;
  // icmp->icmp_code       =  0;
  // icmp->checksum     =  0;
  // icmp->icmp_cksum		=  0;
  // icmp->un.echo.id   =  id;
  // icmp->icmp_id			= id;
  // icmp->un.echo.sequence		=  seq;
  // icmp->icmp_seq				= seq;
  // memcpy(icmpdata, data, datasize);

  // icmp->checksum				= in_cksum(icmp, ICMPHDRSIZE + datasize);
  // icmp->icmp_cksum				= in_cksum( ( unsigned short * )icmp, ICMPHDRSIZE + datasize );

  // Fill in echo request
	pER->icmpHdr.Type		= ICMP_ECHOREQ;
	pER->icmpHdr.Code		= 0;
	pER->icmpHdr.Checksum	= 0;
	pER->icmpHdr.ID			= id;
	pER->icmpHdr.Seq		= seq;

	// Fill in some data to send
	//for (nRet = 0; nRet < REQ_DATASIZE; nRet++)
	//	pER->cData[nRet] = ' '+nRet;
	memset( pER->cData, 0, sizeof( pER->cData ) );
	{
		// AWM_MON_DATA *pAMD = ( AWM_MON_DATA * )pER->cData;
		// memcpy( pAMD->magic, AWM_MON_MAGIC, sizeof( pAMD->magic ) );
		// pAMD->len = 34;
		// strcpy( pAMD->officeName, "技安所" );
		if ( datasize > sizeof( pER->cData ) )
			memcpy( pER->cData, data, sizeof( pER->cData ) );
		else
			memcpy( pER->cData, data, datasize );
	}

	// Save tick count when sent
	pER->dwTime				= GetTickCount();

	// Put data in packet and compute checksum
	pER->icmpHdr.Checksum = in_cksum((u_short *)pER, sizeof(ECHOREQUEST));

  // sin_dst.sin_addr.s_addr		= ip->daddr;
  sin_dst.sin_addr.s_addr		= *( u_long * )&ip->ip_dst;
  sin_dst.sin_family			= AF_INET;

  n = sendto(s, packet, packetSize, 0,
  	    (struct sockaddr*)&sin_dst, sizeof(struct sockaddr));

  if (n == ERROR) {
		perror("sendto");
		free(packet);
		exit(ERROR);
  }

  free(packet);
}




/****************************************************************************/
/*                          SEND A ICMP PACKET                              */
/*  icmp_echo(socket fd, source, destinatiton, id, sequence number, data,   */
/*            datasize);						    */
/****************************************************************************/
/* IN TEST !!!!!!!							    */

void iiicmp_echo( int s, unsigned long int src, unsigned long int dest, 
			   int id, int seq, char *data, unsigned int datasize)
{

  unsigned char			*packet;
  unsigned int			packetSize = 0;
  unsigned char			*icmpdata;
  struct   ip			*ip;
  struct   icmp			*icmp;
  struct   sockaddr_in	sin_dst;
  int n;
#define IPHDRSIZE sizeof( struct ip )		// 20
#define ICMPHDRSIZE sizeof( struct icmp )	// 28

  packetSize = IPHDRSIZE + ICMPHDRSIZE + datasize;
  packet = (char *)malloc( packetSize + 1 );
  if (packet == NULL) {
	perror("malloc");
	exit(ERROR);
  }

  memset( packet, 0, packetSize + 1 );
  ip       = (struct ip   *)packet;
  icmp     = (struct icmp *)(packet + IPHDRSIZE);
  icmpdata = ( char * )(packet + IPHDRSIZE + ICMPHDRSIZE);

  // ip->saddr    		=  src;
  ip->ip_src    		=  *( struct in_addr * )&src;
  // ip->daddr    		=  dest;
  ip->ip_dst	    	=  *( struct in_addr * )&dest;
  // ip->version  		=  4;
  ip->ip_v		  		=  4;
  // ip->ihl      		=  5;
  ip->ip_hl      		=  5;
  // ip->ttl      		=  255;
  ip->ip_ttl      		=  255;
  // ip->protocol 		=  1;
  ip->ip_p		 		=  IPPROTO_ICMP;
  // ip->tot_len  		=  htons(IPHDRSIZE + ICMPHDRSIZE + datasize);
  ip->ip_len	  		=  htons( ( short )packetSize );
  // ip->tos      		=  0;
  ip->ip_tos			=  0;
  // ip->id       		=  0;
  ip->ip_id       		=  0;
  // ip->frag_off 		=  0;
  ip->ip_off	 		=  0;
  // ip->check          =  0;
  ip->ip_sum			=  0;
  // ip->check          =  in_cksum(ip, IPHDRSIZE);
  ip->ip_sum			=  in_cksum( ( u_short * )ip, IPHDRSIZE );
  // icmp->type         =  8;
  icmp->icmp_type		=  8;
  // icmp->code         =  0;
  icmp->icmp_code       =  0;
  // icmp->checksum     =  0;
  icmp->icmp_cksum		=  0;
  // icmp->un.echo.id   =  id;
  icmp->icmp_id			= id;
  // icmp->un.echo.sequence		=  seq;
  icmp->icmp_seq				= seq;
  memcpy(icmpdata, data, datasize);

  // icmp->checksum				= in_cksum(icmp, ICMPHDRSIZE + datasize);
  icmp->icmp_cksum				= in_cksum( ( unsigned short * )icmp, ICMPHDRSIZE + datasize );

  // sin_dst.sin_addr.s_addr		= ip->daddr;
  sin_dst.sin_addr.s_addr		= *( u_long * )&ip->ip_dst;
  sin_dst.sin_family			= AF_INET;

  n = sendto(s, packet, packetSize, 0,
  	    (struct sockaddr*)&sin_dst, sizeof(struct sockaddr));

  if (n == ERROR) {
		perror("sendto");
		free(packet);
		exit(ERROR);
  }

  free(packet);
}


//  2003/11/26加
 BOOL  bQyIpOnline(  unsigned  long  ulAddr  )
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


 


