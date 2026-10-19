
#ifndef __AWMPING_H__
#define __AWMPING_H__	/* { */

//
// Ping.h
//
#ifdef __cplusplus
extern "C" {
#endif

// #pragma pack(1)

#define ICMP_ECHOREPLY	0
#define ICMP_ECHOREQ	8

// IP Header -- RFC 791
typedef struct tagIPHDR
{
	u_char  VIHL;			// Version and IHL
	u_char	TOS;			// Type Of Service
	short	TotLen;			// Total Length
	short	ID;				// Identification
	short	FlagOff;		// Flags and Fragment Offset
	u_char	TTL;			// Time To Live
	u_char	Protocol;		// Protocol
	u_short	Checksum;		// Checksum
	struct	in_addr iaSrc;	// Internet Address - Source
	struct	in_addr iaDst;	// Internet Address - Destination
}IPHDR, *PIPHDR;


// ICMP Header - RFC 792
typedef struct tagICMPHDR
{
	u_char	Type;			// Type
	u_char	Code;			// Code
	u_short	Checksum;		// Checksum
	u_short	ID;				// Identification
	u_short	Seq;			// Sequence
	char	Data;			// Data
}ICMPHDR, *PICMPHDR;

// 结构AWM_MON_DATA应等于32字节

#define		MAX_AWM_MON_OFFICE_NAME_LEN				8
#define		MAX_AWM_MON_SUB_OFFICE_NAME_LEN			8
#define		MAX_AWM_MON_COMMENT_LEN					9

#define		AWM_MON_MAGIC							"&2"

//  下面的结构代表了在网络上传输的数据包，不能修改，切切, 2004/05/23
#define		MACRO_qwmMonData																		\
				 unsigned  char						magic[2];										\
				 unsigned  char						len;											\
				 unsigned  char						officeName[MAX_AWM_MON_OFFICE_NAME_LEN];		\
				 unsigned  char						subOfficeName[MAX_AWM_MON_SUB_OFFICE_NAME_LEN];	\
				 unsigned  char						ucIp[sizeof( unsigned long )];					\
				 unsigned  char						comment[MAX_AWM_MON_COMMENT_LEN];

typedef  struct  __awm_mon_data_t					{		//  这个结构代表了在网络上传输的数据包，不能随便修改，2004/05/23
				MACRO_qwmMonData
}		AWM_MON_DATA;

#define		AWM_MON_DATA_SIZE						sizeof(  AWM_MON_DATA  )	
#define		REQ_DATASIZE							32		//  Echo Request Data size，不能随便修改，2004/05/23


#define		CONST_maxAwmMonCompNameLen				16
#define		CONST_maxAwmMonUsrNameLen				16
#define		CONST_maxAwmMonIsServerLen				1

typedef  struct  __awmMonDataEx_t					{		//  这个结构代表了处理各数据包的函数的通用的结构
															//  其中前面的成员应保持和AWM_MON_DATA的一致性
				 MACRO_qwmMonData
				 char								mac[CONST_qyMacLen  +  1];
				 char								compName[CONST_maxAwmMonCompNameLen  +  1];		//  2004/05/23
				 char								usrName[CONST_maxAwmMonUsrNameLen  +  1];		//  2004/05/23
				 unsigned  char						is_server;				//  2004/05/23
				 char								recvdTime[14 + 1];	

				 char								hint[16];				//  为调试显示用, 2004/05/24		

}		AWM_MON_DATAEx;



// ICMP Echo Request
typedef  struct  tagECHOREQUEST  {
	
				 ICMPHDR							icmpHdr;
				 DWORD								dwTime;
				 char								cData[REQ_DATASIZE];

}		ECHOREQUEST, * PECHOREQUEST;


// ICMP Echo Reply
typedef  struct  tagECHOREPLY	{
				 IPHDR			ipHdr;
				 ECHOREQUEST	echoRequest;
				 //  char			cFiller[256];
				 char			cFiller[1024];			//  2004/05/22放大了此缓冲
}		 ECHOREPLY,  *  PECHOREPLY;

void Ping(LPCSTR pstrHost);
int SendEchoRequest(SOCKET s,LPSOCKADDR_IN lpstToAddr);
int WaitForEchoReply(SOCKET s);
DWORD RecvEchoReply( void *pAE, SOCKET s, LPSOCKADDR_IN lpsaFrom, u_char *pTTL, void *pIMTPI );
DWORD RecvUdpReply( void *pAE, SOCKET s, LPSOCKADDR_IN lpsaFrom, u_char *pTTL, void *pIMTPI );



#ifdef __cplusplus
}
#endif

// #pragma pack()

#endif	/* } */


