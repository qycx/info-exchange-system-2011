
#include	"stdafx.h"
#include	"proxyChkCommon.h"

 extern  "C"  int  _cdecl  qyTcpStart(  )
{
	// Initialize Winsock 1.1
	WSADATA  wsaData;
	
	if  (  WSAStartup(  MAKEWORD(  1,  1  ),  &wsaData  )  !=  0  )  return -1;
	if  (  LOBYTE(  wsaData.wVersion  )  !=  1  ||  HIBYTE(  wsaData.wVersion  )  !=  1  )  {
		WSACleanup(  );
		return   -1;
	}
	
	return  0;
}

 extern  "C"  int  _cdecl  qyTcpEnd(  )
{
	// Clean up Winsock 1.1
	WSACleanup(  );
	return		0;
}



extern  "C"  int
gettimeofday(struct timeval *tv, struct timezone *tz)
{
    struct _timeb   timebuffer;

    _ftime(&timebuffer);
    tv->tv_usec = timebuffer.millitm * 1000;
    tv->tv_sec = timebuffer.time;
    return (0);
}


 extern  "C"  BOOL  inet_aton(  char  *  str,  struct  in_addr  *  next_in_addr  ) 
{
	   next_in_addr->S_un.S_addr  =  inet_addr(  str  );
	 return  (  INADDR_NONE  !=  next_in_addr->S_un.S_addr  )  ?  TRUE  :  FALSE;
}
