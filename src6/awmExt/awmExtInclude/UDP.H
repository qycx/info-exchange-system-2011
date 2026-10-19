

#ifndef  __UDP_H__
#define  __UDP_H__	/*  {  */



//
// Define the UDP header 
//
typedef  struct  udp_hdr			{

				 unsigned  short	src_portno;       // Source port number
    			 unsigned  short	dst_portno;       // Destination port number
    			 unsigned  short	udp_length;       // UDP packet length
    			 unsigned  short	udp_checksum;     // UDP checksum (optional)

}		 UDP_HDR,  *  PUDP_HDR;



#endif  /*  }  */

