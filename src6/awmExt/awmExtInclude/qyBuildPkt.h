
#ifndef  __QYBUILDPKT_H__
#define  __QYBUILDPKT_H__	/*  {  */


/* 
 *  Standard (IPv4) header sizes in bytes.
 */

#define LIBNET_ARP_H           0x1c    /* ARP header:          28 bytes */
#define LIBNET_DNS_H           0xc     /* DNS header base:     12 bytes */
#define LIBNET_ETH_H           0xe     /* Etherner header:     14 bytes */
#define LIBNET_ICMP_H          0x4     /* ICMP header base:     4 bytes */
#define LIBNET_ICMP_ECHO_H     0x8     /* ICMP_ECHO header:     8 bytes */
#define LIBNET_ICMP_MASK_H     0xc     /* ICMP_MASK header:    12 bytes */
#define LIBNET_ICMP_UNREACH_H  0x8     /* ICMP_UNREACH header:  8 bytes */
#define LIBNET_ICMP_TIMXCEED_H 0x8     /* ICMP_TIMXCEED header: 8 bytes */
#define LIBNET_ICMP_REDIRECT_H 0x8     /* ICMP_REDIRECT header: 8 bytes */
#define LIBNET_ICMP_TS_H       0x14    /* ICMP_TIMESTAMP headr:20 bytes */
#define LIBNET_IGMP_H          0x8     /* IGMP header:          8 bytes */
#define LIBNET_IP_H            0x14    /* IP header:           20 bytes */
/* See libnet-ospf.h for OSPF related header sizes */
#define LIBNET_RIP_H           0x18    /* RIP header base:     24 bytes */
#define LIBNET_TCP_H           0x14    /* TCP header:          20 bytes */
#define LIBNET_UDP_H           0x8     /* UDP header:           8 bytes */
#define LIBNET_VRRP_H          0x8     /* VRRP header:          8 bytes */

/*
 *  Concession to legacy naming scheme.
 */
#define ARP_H           LIBNET_ARP_H
#define DNS_H           LIBNET_DNS_H
#define ETH_H           LIBNET_ETH_H
#define ICMP_H          LIBNET_ICMP_H
#define ICMP_ECHO_H     LIBNET_ICMP_ECHO_H
#define ICMP_MASK_H     LIBNET_ICMP_MASK_H
#define ICMP_UNREACH_H  LIBNET_ICMP_UNREACH_H
#define ICMP_TIMXCEED_H LIBNET_ICMP_TIMXCEED_H
#define ICMP_REDIRECT_H LIBNET_ICMP_REDIRECT_H
#define ICMP_TS_H       LIBNET_ICMP_TS_H
#define IGMP_H          LIBNET_IGMP_H
#define IP_H            LIBNET_IP_H
#define RIP_H           LIBNET_RIP_H
#define TCP_H           LIBNET_TCP_H
#define UDP_H           LIBNET_UDP_H

/*
 *  prand constants
 */
#define LIBNET_PR2          0
#define LIBNET_PR8          1
#define LIBNET_PR16         2
#define LIBNET_PRu16        3
#define LIBNET_PR32         4
#define LIBNET_PRu32        5
#define LIBNET_PRAND_MAX    0xffffffff

/*
 *  Concession to legacy naming scheme
 */
#define PR2         LIBNET_PR2
#define PR8         LIBNET_PR8
#define PR16        LIBNET_PR16
#define PRu16       LIBNET_PRu16
#define PR32        LIBNET_PR32
#define PRu32       LIBNET_PRu32
#define PRAND_MAX   LIBNET_PRAND_MAX


#define		CONST_qyIpLen		LIBNET_IP_H
#define		CONST_qyTcpLen		LIBNET_TCP_H


//  for computing TCP checksum, see TCP/IP Illustrated p. 145 
struct  pseudo_header  { 
  						unsigned  int	s_addy;
  						unsigned  int	d_addr;
  						char			zer0;
  						unsigned  char	protocol;
  						unsigned  short length;
};


typedef  struct  __qyPacket_t  {
    			 struct  ip  *  iph,  *  orig_iph;      /* and orig. headers for ICMP_*_UNREACH family */
    			 struct  tcphdr  *  tcph,  *  orig_tcph;
}		 QY_PACKET;


 #define  CONST_qwmScanSportBase		1025



#ifdef  __cplusplus
  extern  "C"  {
#endif


int  qyOpenRaw4(  void  *  pContext,  int  protocol,  int  *  pSockFd  );
void  qyCloseRaw4(  void  *  pContext,  int  sockFd  );


u_long  libnet_get_prand(int mod);
int  libnet_write_ip(int sock, u_char *buf, int len);


u_short  in_cksum(  u_short  *  addr,  int  len  );
unsigned short ip_in_cksum(struct ip *iph, unsigned short *ptr, int nbytes);
unsigned  short  qwmTcpScanChkSum(  unsigned  long  ulInterMonIp,  unsigned  short  usId,  unsigned  long  ulScannedIp  );
int  qyDoChkSum(  u_char  *  buf,  int  protocol,  int  len  );
int  qyBuildIp(  u_short len, u_char tos, u_short id, u_short frag, u_char ttl,
				 u_char prot, u_long src, u_long dst, const u_char *payload,
            	 int payload_s, u_char *buf);
int  qyBuildTcp(  u_short  sp,  u_short  dp,  u_long  seq,  u_long  ack,
				  u_char  control,  u_short  win,  u_short  urg,  u_short  len,
				  u_char  *  options,  int optLen,	//  ‘›≤ª”√
				  u_char  *  payload,  u_long  payload_s, 
				  void  *  pContext,  long  ptag,  
				  char  *  tcpBuf,  u_short  *  pTcpLen  );

int qySendTCP(  u_long saddr, u_long daddr, u_short sport, u_short dport, int seq,
				 int ack, u_char bits, const u_char *data_buf, int data_size,  int  nd  );
int  qyReact(  QY_PACKET  *  p,  int  rawSockFd  );





#ifdef  __cplusplus
  }
#endif


#endif  /*  }  */




