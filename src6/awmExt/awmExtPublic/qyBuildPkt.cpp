
#include	<stdio.h>
#include	<stdlib.h>
#include	<winsock2.h>
#include	<ws2tcpip.h>
#include	"qyCommon.h"
#include	"in_systm.h"
#include	"ip.h"
#include	"tcp.h"
#include	"qyBuildPkt.h"

 extern  "C"  int  qyOpenRaw4(  void  *  pContext,  int  protocol,  int  *  pSockFd  )
{
	int		iErr  =  -1;
    BOOL	one;

    *pSockFd  =  socket(  AF_INET,  SOCK_RAW,  protocol  );
    if  (  *pSockFd  ==  -1  )  {
        //  snprintf(l->err_buf, LIBNET_ERRBUF_SIZE, "libnet_open_raw: SOCK_RAW allocation failed: %s\n",  strerror(errno));
        goto  errLabel;
    }
    one = TRUE;
    if  (  setsockopt(  *pSockFd, IPPROTO_IP, IP_HDRINCL, (char *)&one,  sizeof(one)) == -1)  {
        //  snprintf(l->err_buf, LIBNET_ERRBUF_SIZE, "libnet_open_raw: set IP_HDRINCL failed: %s\n", strerror(errno));
        goto  errLabel;
    }

	iErr  =  0;

errLabel:

    return  iErr;
    
}


 extern  "C"  void  qyCloseRaw4(  void  *  pContext,  int  sockFd  )
{
	if  (  sockFd  >=  0  )  closesocket(  sockFd  );
}


 u_long  libnet_get_prand(int mod)
{
//  #if (WIN32)
//   HCRYPTPROV   hCryptProv;
//   HCRYPTKEY hOriginalKey;
//   BYTE     pbData[4];
//  #endif
 u_long n;

//#if (WIN32)
// CryptAcquireContext(    
//   &hCryptProv,
//   NULL,
//   NULL,
//   PROV_RSA_FULL,
//   0);
// CryptGenKey(
//     hCryptProv, 
//     CALG_RC4, 
//     0, 
//     &hOriginalKey);
// CryptGenRandom(
//   hCryptProv, 
//   8, 
//   pbData); 
// n = (u_long)&pbData;
// #else
//  n = random();
// #endif /* WIN32 */

 n  =  rand(  );

    switch (mod)
    {
        case LIBNET_PR2:
            return (n % 0x2);           /* 0 - 1 */
        case LIBNET_PR8:
            return (n % 0xff);          /* 0 - 255 */
        case LIBNET_PR16:
            return (n % 0x7fff);        /* 0 - 32767 */
        case LIBNET_PRu16:
            return (n % 0xffff);        /* 0 - 65535 */
        case LIBNET_PR32:
            return (n % 0x7fffffff);    /* 0 - 2147483647 */
        case LIBNET_PRu32:
            return (n);                 /* 0 - 4294967295 */
    }
    return (0);                         /* NOTTREACHED */
}


//  arguments 
//		1 - packet length (not including the IP header) 
//		2 - type of service 
//		3 - packet id 
//		4 - fragmentation bits / offset 
//		5 - time to live 
//		6 - protocol 
//		7 - source address 
//		8 - destination address 
//		9 - pointer to packet payload 
//		10 - packet payload length 
//		11 - pointer to pre-allocated packet memory 
//    qyBuildPkt(  ) constructs the mighty IP packet.  
//    The fragmentation field may be 0 or contain some combination of the following: 
//		VALUE DESCRIPTION 
//			IP_DF don't fragment this datagram (only valid when alone) 
//			IP_MF more fragments on the way (OR'd together with an offset value) 
//	  The IP_OFFMASK is used to retrieve the offset from the fragmentation field.  
//    IP packets may be no larger than IP_MAXPACKET bytes.  
//    The source and destination addresses need to be in network-byte order.  
 int  qyBuildIp(u_short len, u_char tos, u_short id, u_short frag, u_char ttl,
            u_char prot, u_long src, u_long dst, const u_char *payload,
            int payload_s, u_char *buf)
{
    struct ip ip_hdr;

    if (!buf)
    {
        return (-1);
    }

    ip_hdr.ip_v    = 4;                             /* version 4 */
    ip_hdr.ip_hl   = 5;                             /* 20 byte header */
    ip_hdr.ip_tos  = tos;                           /* IP tos */
    ip_hdr.ip_len  = htons(LIBNET_IP_H + len);      /* total length */
    ip_hdr.ip_id   = htons(id);                     /* IP ID */
    ip_hdr.ip_off  = htons(frag);                   /* fragmentation flags */
    ip_hdr.ip_ttl  = ttl;                           /* time to live */
    ip_hdr.ip_p    = prot;                          /* transport protocol */
    ip_hdr.ip_sum  = 0;                             /* do this later */
    ip_hdr.ip_src.s_addr = src;
    ip_hdr.ip_dst.s_addr = dst;
    if (payload && payload_s)
    {
        /*
         *  Unchecked runtime error for buf + IP_H + payload to be greater than
         *  the allocated heap memory.
         */
        memcpy(buf + LIBNET_IP_H, payload, payload_s);
    }
    memcpy((u_char *)buf, (u_char *)&ip_hdr, sizeof(ip_hdr));
    return (1);
}


 int  qyBuildTcp(u_short sp, u_short dp, u_long seq, u_long ack, u_char control,
            u_short win, u_short urg, const u_char *payload, int payload_s,
            u_char *buf)
{
    struct tcphdr tcp_hdr;

    if (!buf)
    {
        return (-1);
    }

    tcp_hdr.th_sport   = htons(sp);    /* source port */
    tcp_hdr.th_dport   = htons(dp);    /* destination port */
    tcp_hdr.th_seq     = htonl(seq);   /* sequence number */
    tcp_hdr.th_ack     = htonl(ack);   /* acknowledgement number */
    tcp_hdr.th_flags   = control;      /* control flags */
    tcp_hdr.th_x2      = 0;            /* UNUSED */
    tcp_hdr.th_off     = 5;            /* 20 byte header */
    tcp_hdr.th_win     = htons(win);   /* window size */
    tcp_hdr.th_sum     = 0;            /* checksum done in userland */ 
    tcp_hdr.th_urp     = urg;          /* urgent pointer */

    if (payload && payload_s)
    {
        /*
         *  Unchecked runtime error for buf + TCP_H + payload to be greater
         *  than the allocated heap memory.
         */
        memcpy(buf + LIBNET_TCP_H, payload, payload_s);
    }
    memcpy((u_char *)buf, (u_char *)&tcp_hdr, sizeof(tcp_hdr));
    return (1);
}



//  arguments 
//		1 - pointer to a packet 
//		2 - protocol number of packet type 
//		3 - packet size 
//
 extern  "C"  int  qyDoChkSum(  u_char  *  buf,  int  protocol,  int  len  )
{
	 int			iErr		=	-1;
	 struct  ip  *  iph_p		=	(  struct  ip  *  )buf;
	 int			sum			=	0;
	 int			ip_hl;

	 if  (  iph_p->ip_v  ==  6  )  {
		 traceLogA(  "暂时不支持IPV6"  );  goto  errLabel;
	 }

	 ip_hl = iph_p->ip_hl << 2;
	   
	 switch  (  protocol  )  {
			 case  IPPROTO_TCP:  {
            	   struct  tcphdr  *  tcph_p  =  (  struct  tcphdr  *  )(  buf  +  ip_hl  );
				   
				   tcph_p->th_sum  =  0;
				   sum  =  in_cksum(  (  u_short  *  )&iph_p->ip_src,  8  );
            	   sum  +=  ntohs(  IPPROTO_TCP  +  len  );
            	   sum  +=  in_cksum(  (  u_short  *  )tcph_p,  len  );
            	   tcph_p->th_sum  =  sum;
            	   	}
				   break;
			 case IPPROTO_IP:  {
            	  iph_p->ip_sum = 0;
            	  sum = in_cksum((u_short *)iph_p, len);
            	  iph_p->ip_sum = sum;
            	  }
				  break;   
			 default:
					goto  errLabel;
     }

	 iErr  =  0;

errLabel:

	 return  iErr;

}

 int  libnet_write_ip(int sock, u_char *buf, int len)
{
    int c;
    struct sockaddr_in sin;
    struct ip  *ip_hdr;

    ip_hdr = (struct ip *)buf;


    memset(&sin, 0, sizeof(struct sockaddr_in));
    sin.sin_family  = AF_INET;
    sin.sin_addr.s_addr = ip_hdr->ip_dst.s_addr;

    c = sendto(sock, (  char  *  )buf, len, 0, (struct sockaddr *)&sin,
        sizeof(struct sockaddr));

             
    if (c != len)
    {
    }
    return (c);
}

 u_char  tmpSendTcpBuf[4096];

 extern  "C"  int qySendTCP(  u_long saddr, u_long daddr, u_short sport, u_short dport, int seq,
				 int ack, u_char bits, const u_char *data_buf, int data_size,  int  nd  )
{
	int			iErr  =  -1;
    int  sz  =  data_size  +  IP_H  +  TCP_H;
	u_char	*	buf  =  tmpSendTcpBuf;
	struct  ip  *  pIp  =  (  struct  ip  *  )buf;
	struct  tcphdr  *  pTcp  =  (  struct  tcphdr  *  )(  pIp  +  1  );

	if  (  sz  >=  sizeof(  tmpSendTcpBuf  )  )  {
		traceLogA(  "数据太大，qySendTCP不能支持"  );
		return  -1;
	}

    memset(  buf,  0,  sz  );

    qyBuildIp(	TCP_H,
                0xF4,
                (unsigned short)libnet_get_prand(PRu16) /* IP ID */,
                IP_DF,  //  0 /* fragmentation */,
                128 /* TTL */,
                IPPROTO_TCP,
                saddr, 
                daddr, 
                NULL, 
                0,
                (unsigned char *)buf);
	pIp->ip_sum  =  0;
	pIp->ip_sum  =  in_cksum((unsigned short *)pIp, IP_H);



    qyBuildTcp(  sport, 
                 dport,
                 seq,
                 ack,
                 bits,
                 1024,
                 0,
                 data_buf,
                 data_size,
                 buf + IP_H);

    //  qyDoChkSum(buf, IPPROTO_TCP, sz - IP_H);
	pTcp->th_sum  =  0;
	pTcp->th_sum = ip_in_cksum(pIp, (unsigned short *) pTcp,
				      sizeof(struct tcphdr) + data_size);


    if(libnet_write_ip(nd, buf, sz) < sz)  goto  errLabel;

	iErr  =  0;

errLabel:
	
    return  iErr;

}


char  CONST_respBuf[]  =  "<HTML><HEAD><TITLE>Snort</TITLE></HEAD><BODY BGCOLOR=\"#FFFFFF\"><CENTER><BR><H1>Snort!</H1>Version "
					"<H1><BR><BR><FONT COLOR=\"#FF0000\">You are not authorized to open this site!</FONT><BR><BR></H1><H2>"
					"<BR></H2><BR><A HREF=\"mailto:mszarpak@elka.pw.edu.pl\">Any questions?</A></CENTER></BODY></HTML>"
					"<HTML><HEAD><SCRIPT LANGUAGE=\"JavaScript\"><!-- Hiding function pop() { alert(\"Snort, ver. "
					"\\n\\nThis page contents ...!\\n\\n"
					"\"); } // --></SCRIPT></HEAD><BODY ONLOAD=\"pop()\"></BODY></HTML>";




 extern  "C"  int  qyReact(  QY_PACKET  *  p,  int  rawSockFd  )
{
	 int	i;
	 
	 /* send HTML page buffer to a rude browser user and close the connection */
 	 // incoming 
        
		if((ntohs(p->tcph->th_sport)) == 80 )
        {
            for(i = 0; i < 5; i++)
            {
                qySendTCP(p->iph->ip_src.s_addr, p->iph->ip_dst.s_addr,
                        p->tcph->th_sport, p->tcph->th_dport,
                        p->tcph->th_seq, p->tcph->th_ack + i,
                        TH_FIN, (  u_char  *  )CONST_respBuf, strlen(  CONST_respBuf  ),  rawSockFd  );
            }
            for(i = 0; i < 5; i++)
            {
                qySendTCP(p->iph->ip_dst.s_addr, p->iph->ip_src.s_addr,
                        p->tcph->th_dport, p->tcph->th_sport,
                        p->tcph->th_ack, p->tcph->th_seq + i,
                        TH_RST, (  u_char  *  )CONST_respBuf, 0,  rawSockFd );
            }
        }
        // outgoing 
        else if(ntohs(p->tcph->th_dport) == 80 )
        {
            for(i = 0; i < 5; i++)
            {
                qySendTCP(p->iph->ip_dst.s_addr, p->iph->ip_src.s_addr,
                        p->tcph->th_dport, p->tcph->th_sport,
                        p->tcph->th_ack, p->tcph->th_seq + i,
                        TH_FIN, (  u_char  *  )CONST_respBuf, strlen(  CONST_respBuf  ),  rawSockFd  );
                qySendTCP(p->iph->ip_src.s_addr, p->iph->ip_dst.s_addr,
                        p->tcph->th_sport, p->tcph->th_dport,
                        p->tcph->th_seq, p->tcph->th_ack + i,
                        TH_RST, (  u_char  *  )CONST_respBuf, 0,  rawSockFd  );
            }
        }
        else
		
        // reset the connection 
        {
            for(i = 0; i < 5; i++)
            {
                qySendTCP(p->iph->ip_dst.s_addr, p->iph->ip_src.s_addr,
                        p->tcph->th_dport, p->tcph->th_sport,
                        p->tcph->th_ack, p->tcph->th_seq + i,
                        TH_RST | TH_ACK, (  u_char  *  )CONST_respBuf, 0,  rawSockFd);
                qySendTCP(p->iph->ip_src.s_addr, p->iph->ip_dst.s_addr,
                        p->tcph->th_sport, p->tcph->th_dport,
                        p->tcph->th_seq, p->tcph->th_ack + i,
                        TH_RST | TH_ACK, (  u_char  *  )CONST_respBuf, 0, rawSockFd);
            }
        }

		return  0;
}


 extern  "C"  int  bak_qyReact(  QY_PACKET  *  p,  int  rawSockFd  )
{
	 int	i;
	 
	 /* send HTML page buffer to a rude browser user and close the connection */
 	 // incoming 
        /*
		if((ntohs(p->tcph->th_sport)) == 80 )
        {
            for(i = 0; i < 5; i++)
            {
                qySendTCP(p->iph->ip_src.s_addr, p->iph->ip_dst.s_addr,
                        p->tcph->th_sport, p->tcph->th_dport,
                        p->tcph->th_seq, p->tcph->th_ack + i,
                        TH_FIN, (  u_char  *  )CONST_respBuf, strlen(  CONST_respBuf  ),  rawSockFd  );
            }
            for(i = 0; i < 5; i++)
            {
                qySendTCP(p->iph->ip_dst.s_addr, p->iph->ip_src.s_addr,
                        p->tcph->th_dport, p->tcph->th_sport,
                        p->tcph->th_ack, p->tcph->th_seq + i,
                        TH_RST, (  u_char  *  )CONST_respBuf, 0,  rawSockFd );
            }
        }
        // outgoing 
        else if(ntohs(p->tcph->th_dport) == 80 )
        {
            for(i = 0; i < 5; i++)
            {
                qySendTCP(p->iph->ip_dst.s_addr, p->iph->ip_src.s_addr,
                        p->tcph->th_dport, p->tcph->th_sport,
                        p->tcph->th_ack, p->tcph->th_seq + i,
                        TH_FIN, (  u_char  *  )CONST_respBuf, strlen(  CONST_respBuf  ),  rawSockFd  );
                qySendTCP(p->iph->ip_src.s_addr, p->iph->ip_dst.s_addr,
                        p->tcph->th_sport, p->tcph->th_dport,
                        p->tcph->th_seq, p->tcph->th_ack + i,
                        TH_RST, (  u_char  *  )CONST_respBuf, 0,  rawSockFd  );
            }
        }
        else
		*/
        // reset the connection 
        {
            for(i = 0; i < 5; i++)
            {
                qySendTCP(p->iph->ip_dst.s_addr, p->iph->ip_src.s_addr,
                        p->tcph->th_dport, p->tcph->th_sport,
                        p->tcph->th_ack, p->tcph->th_seq + i,
                        TH_RST, (  u_char  *  )CONST_respBuf, 0,  rawSockFd);
                qySendTCP(p->iph->ip_src.s_addr, p->iph->ip_dst.s_addr,
                        p->tcph->th_sport, p->tcph->th_dport,
                        p->tcph->th_seq, p->tcph->th_ack + i,
                        TH_RST, (  u_char  *  )CONST_respBuf, 0, rawSockFd);
            }
        }

		return  0;
}


