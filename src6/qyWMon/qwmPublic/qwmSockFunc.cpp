

#include	<windows.h>
#include	<winsock.h>
#include	<ras.h>
#include	<raserror.h>
#include	<commctrl.h>
#include	<iphlpapi.h>
#include	<tchar.h>
#include	"asrWMon.h"


/*

 extern  "C"  int  WINAPI  WSAStartup(  WORD wVersionRequested,  LPWSADATA lpWSAData  )
{
	 return  pWSAStartup(  wVersionRequested,  lpWSAData  );
}

 extern	 "C"  int  WINAPI  WSACleanup(  void  )
{
	 return  pWSACleanup(  );
}

 extern  "C"  unsigned  long  WINAPI  inet_addr(  const char FAR * cp  )
{
	 return	 pinet_addr(  cp  );
}

 extern  "C"  char *  WINAPI  inet_ntoa  (  struct in_addr in  )
{
	 return  pinet_ntoa(  in  );
}


 extern  "C"   SOCKET  WINAPI   socket(  int af,  int type,  int protocol  )
{
	 return  psocket(  af,   type,   protocol  );
}
 extern  "C"   int  WINAPI   bind(  SOCKET s,  const struct sockaddr FAR*  name,  int namelen  )
{
	 return  pbind(  s,  name,   namelen  );
}
 extern  "C"   int  WINAPI   listen(  SOCKET s,  int backlog  )
{
	 return  plisten(   s,   backlog  );
}
 extern  "C"   SOCKET  WINAPI   accept(  SOCKET s,  struct sockaddr FAR* addr,  int FAR* addrlen  )
{
	 return  paccept(   s,  addr,  addrlen  );
}
 extern  "C"   int  WINAPI   connect(  SOCKET s,  const struct sockaddr FAR*  name,  int namelen  )
{
	 return  pconnect(   s,  name,   namelen  );
}
 extern  "C"   int  WINAPI   select(  int nfds,  fd_set FAR * readfds,  fd_set FAR * writefds,  fd_set FAR * exceptfds,  const struct timeval FAR * timeout  )
{
	 return  pselect(   nfds,  readfds,  writefds,  exceptfds,  timeout  );
}
 extern  "C"   int  WINAPI   getsockname(  SOCKET s,  struct sockaddr FAR*  name,  int FAR*  namelen  )
{
	 return  pgetsockname(   s,  name,   namelen  );
}
 extern  "C"   int  WINAPI   getpeername(  SOCKET s,  struct sockaddr FAR*  name,  int FAR*  namelen  )
{
	 return  pgetpeername(   s,  name,   namelen  );
}
 extern  "C"   int  WINAPI   closesocket(  SOCKET s  )
{
	 return  pclosesocket(   s  );
}
 extern  "C"   int  WINAPI   recv(  SOCKET s,  char FAR* buf,  int len,  int flags  )
{
	 return   precv(   s,  buf,   len,   flags  );
}
 extern  "C"   int  WINAPI   send(  SOCKET s,  const char FAR * buf,  int len,  int flags  )
{
	 return  psend(   s,  buf,  len,   flags  );
}
 extern  "C"   int  WINAPI   WSAGetLastError(void)
{
	 return  pWSAGetLastError();
}
 extern  "C"   int  WINAPI   ioctlsocket(  SOCKET s,  long cmd,  u_long FAR* argp  )
{
	 return  pioctlsocket(   s,  cmd,  argp  );
}
 extern  "C"   int  WINAPI   gethostname(  char FAR * name,  int namelen  )
{
	 return  pgethostname(  name,   namelen  );
}
 extern  "C"   struct hostent FAR *  WINAPI   gethostbyname(  const char FAR * name  )
{
	 return  pgethostbyname( name  );
}
 extern  "C"   u_short  WINAPI   htons(  u_short hostshort  )
{
	 return   phtons(  hostshort  );
}
 extern  "C"   int  WINAPI   setsockopt(  SOCKET s,  int level,  int optname,  const char FAR * optval,  int optlen  )
{
	 return   psetsockopt(   s,   level,   optname,  optval,   optlen  );
}

*/



