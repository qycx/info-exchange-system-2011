
#include	<windows.h>
#include	<iphlpapi.h>
#include	<tchar.h>
#include	"qyCommon.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qwmFunc.h"
#include	"qwmDynFunc.h"



 QY_DMITEM  CONST_wellKnownSiteTable[]  =
{
	{	0,		(  TCHAR  *  )"202.108.119.194",		_T(  ""  ),				},				//  "www.xinhuanet.com",	
	{	1,		(  TCHAR  *  )"202.106.185.238",		_T(  ""  ),					},				//  "www.sina.com.cn",		
	//{	1,		"202.108.37.41",		"新浪",					},				//  "www.sina.com.cn",		
	{	2,		(  TCHAR  *  )"211.99.196.218",			_T(  ""  ),			},				//  "www.fmprc.gov.cn",	
	
	{	3,		(  TCHAR  *  )"4.19.71.34",				_T(  ""  ),			},				//  "www.cctv-4.com",	
	{	4,		(  TCHAR  *  )"202.99.23.208",			_T(  ""  ),				},				//  "www.people.com.cn",
	{	5,		(  TCHAR  *  )"211.100.24.131",			_T(  ""  ),					},				//  "www.263.net",		
	{	6,		(  TCHAR  *  )"202.127.48.5",			_T(  ""  ),				},				//  "www.customs.gov.cn",
	{	7,		(  TCHAR  *  )"211.99.194.234",			_T(  ""  ),				},				//  "www.chinatelcom.com",	
	//{	8,		"61.135.133.109",		"搜狐",					},				//  "www.sohu.com",	
	{	8,		(  TCHAR  *  )"211.154.211.74",			_T(  ""  ),			},				//  "www.cctv-4.com",	
	{	-1,		NULL,											},
};



 //  BOOL  canConnectWebSite(  QWM_THREADINFO  *  pSubThreadInfo,  QY_DMITEM  *  pItem  )
 BOOL  canConnectWebSite(  SOCK_TIMEOUT  *  pTo,  QY_DMITEM  *  pItem  )
{
	 BOOL					bRet			=	FALSE;
	 QY_SOCK				tmpSock;
	 char					recvBuf[128];
	 int					recvBufSize		=	0;

	 clearQySock(  &tmpSock  );

	 traceLogA(  "\t尝试连接\"%s\"",  pItem->pData  ?  (  char  *  )pItem->pData  :  ""  );
	 if  (  qyConnect(  (  char  *  )pItem->des,  80,  &tmpSock,  3000  )  )  goto  errLabel;
	 traceLogA(  "\t\"%s\" is connecting ",  pItem->pData  ?  (  char  *  )pItem->pData  :  ""  );
	 safeStrnCpy(  "GET / HTTP/1.0 \n\n",  recvBuf,  sizeof(  recvBuf  )  );
	 if  (  qySend(  &tmpSock,  recvBuf,  strlen(  recvBuf  ),  pTo->iWrite  )  )  goto  errLabel;
	 recvBufSize  =  sizeof(  recvBuf  )  -  1;
	 if  (  qyRecv(  &tmpSock,  recvBuf,  &recvBufSize,  pTo->iRead  )  )  goto  errLabel;
	 recvBuf[sizeof(  recvBuf  )  -  1]  =  0;
	 trim(  recvBuf  );
	 //  traceLogA(  " recvBuf is  %s\n ,the cnt is %d ",  recvBuf, cnt  );
	 if  (  strnicmp(  recvBuf,  CONST_httpFlag,  strlen(  CONST_httpFlag  )  )  )  goto  errLabel;
	 traceLogA(  "\t\"%s\" is connected",  pItem->pData  ?  (  char  *  )pItem->pData  :  ""  );
	
	 bRet  =  TRUE;

errLabel:
	
	 if  (  bQySockOpen(  &tmpSock  )  )  qyDisconnect(  &tmpSock  );

	 return  bRet;

}



 //  因为是通过NetAPI来获取网卡信息，所以需要包含其题头文件nb30.h #include < nb30.h > 
typedef  struct  _ASTAT_			{
				 ADAPTER_STATUS		adapt;
				 NAME_BUFFER		NameBuff[30];
}		 ASTAT,  *  PASTAT;


 //  定义一个存放返回网卡信息的变量 
 //  输入参数：lana_num为网卡编号，一般地，从0开始，但在Windows 2000中并不一定是连续分配的 
 static  int  getAdapterInfo(  QY_ENV  *  pEnv,  int  lana_num,  char  *  macBuf,  unsigned  int  size  )
{
	int					iErr		=	-1;
    NCB					ncb;
    UCHAR				uRetCode;
	ASTAT				Adapter;    
	QWM_DYN_LIB		*	pDynLib		=	(  QWM_DYN_LIB  *  )pEnv->pDynLibs;

	if  (  !pDynLib->pNetbios  ||  !macBuf  ||  size  <  CONST_qyMacLen  +  1  )  return  -1;

    memset(  &ncb,  0,  sizeof(  ncb  )  );
    ncb.ncb_command		=	NCBRESET;
    ncb.ncb_lana_num	=	lana_num;			//  指定网卡号

	//  首先对选定的网卡发送一个NCBRESET命令，以便进行初始化 
    uRetCode  =  pDynLib->pNetbios(  &ncb  );
    //  printf(  "The NCBRESET return code is: 0x%x \n",  uRetCode  );

    memset(  &ncb,  0,  sizeof(  ncb  )  );
    ncb.ncb_command		=	NCBASTAT;
    ncb.ncb_lana_num	=	lana_num;							// 指定网卡号
    safeStrnCpy(  (  "*               "  ),  (  char  *  )ncb.ncb_callname,  mycountof(  ncb.ncb_callname  )  );
    ncb.ncb_buffer		=	(  unsigned  char  *  )&Adapter;		//  指定返回的信息存放的变量 
    ncb.ncb_length		=	sizeof(  Adapter  );

	// 接着，可以发送NCBASTAT命令以获取网卡的信息 
    uRetCode  =  pDynLib->pNetbios(  &ncb  );
    if  (  uRetCode  !=  0  )  {
		traceLogA(  "The NCBASTAT return code is: 0x%x \n",  uRetCode  );  goto  errLabel;
	}
	
	// 把网卡MAC地址格式化成常用的16进制形式，如0010-A4E4-5802 
	_snprintf(  macBuf,  size,  "%02X%02X%02X%02X%02X%02X",     
						(  unsigned  char  )Adapter.adapt.adapter_address[0],
						(  unsigned  char  )Adapter.adapt.adapter_address[1],
						(  unsigned  char  )Adapter.adapt.adapter_address[2],
						(  unsigned  char  )Adapter.adapt.adapter_address[3],
						(  unsigned  char  )Adapter.adapt.adapter_address[4],
						(  unsigned  char  )Adapter.adapt.adapter_address[5]  );
	
	iErr  =  0;
    
errLabel:
	return  iErr;
}

 extern  "C"  int getQwmMacsByNetbios(  QY_ENV  *  pEnv,  QWM_MACS_INFO  *  pMacsInfo  )
{
	int					iErr		=		-1;
    NCB					ncb;
    UCHAR				uRetCode;
    LANA_ENUM			lana_enum;
	unsigned  int		nMacs		=	0;
	int					i;
	char				macBuf[CONST_qyMacLen  +  1];
	QWM_DYN_LIB		*	pDynLib		=	(  QWM_DYN_LIB  *  )pEnv->pDynLibs;

	if  (  !pDynLib->pNetbios  ||  !pMacsInfo  )  return  -1;
	memset(  pMacsInfo,  0,  sizeof(  QWM_MACS_INFO  )  );

    memset(  &ncb,  0,  sizeof(  ncb  )  );
    ncb.ncb_command		=	NCBENUM;
    ncb.ncb_buffer		=	(  unsigned  char  *  )&lana_enum;
    ncb.ncb_length		=	sizeof(  lana_enum  );

	//  向网卡发送NCBENUM命令，以获取当前机器的网卡信息，如有多少个网卡、每张网卡的编号等 
	uRetCode	=	pDynLib->pNetbios(  &ncb  );
	if  (  uRetCode  !=  0  )  {
		traceLogA(  "The NCBENUM return code is: 0x%x \n",  uRetCode  );  goto  errLabel;
	}
	//  printf( "Ethernet Count is : %d\n\n", lana_enum.length);

	nMacs  =  min(  lana_enum.length,  sizeof(  pMacsInfo->macs  )  /  sizeof(  pMacsInfo->macs[0]  )  );

	// 对每一张网卡，以其网卡编号为输入编号，获取其MAC地址 
	pMacsInfo->nMacs  =  0;
	for  (  i  =  0;  i  <  (  int  )nMacs;  ++  i  )  {
		 if  (  getAdapterInfo(  pEnv,  lana_enum.lana[i],  macBuf,  sizeof(  macBuf  )  )  )  goto  errLabel;
		 if  (  !bMacValid(  macBuf  )  )  continue;
		 safeStrnCpy(  macBuf,  (  char  *  )pMacsInfo->macs[pMacsInfo->nMacs],  sizeof(  pMacsInfo->macs[pMacsInfo->nMacs]  )  );
		 pMacsInfo->nMacs  ++  ;		 
	 }

	for  (  i  =  0;  i  <  (  int  )pMacsInfo->nMacs;  i  ++  )  pMacsInfo->macs[i][CONST_qyMacLen]  =  0;
	
	iErr  =  0;

errLabel:

	return  iErr;

}





