
#include <sys/types.h>
//  #include <sys/socket.h>
//  #include <netinet/in.h>
//  #include <arpa/inet.h>
#include <stdlib.h>
//  #include <sys/time.h>
#include <string.h>
#if HAVE_STDINT_H
#include <stdint.h>
#endif

//  #include	<winsock2.h>
#include	"include\\myNbtScanCommon.h"

  


 void  sleep(  int  sec  )
{
	 Sleep(  sec  *  1000  );
	 return;
}


 BOOL  inet_aton(  char  *  str,  struct  in_addr  *  next_in_addr  ) 
{
	   next_in_addr->S_un.S_addr  =  inet_addr(  str  );
	 return  (  INADDR_NONE  !=  next_in_addr->S_un.S_addr  )  ?  TRUE  :  FALSE;
}


 void  bzero(  void  *  p,  unsigned  int  size  )
{
	 memset(  p,  0,  size  );
}


