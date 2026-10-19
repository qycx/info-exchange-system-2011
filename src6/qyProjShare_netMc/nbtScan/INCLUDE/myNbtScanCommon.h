

#ifndef  __MYNBTSCANCOMMON__
#define  __MYNBTSCANCOMMON__

#include	<winsock2.h>
#include	<time.h>

#include	"qyNbtScanCommProc.h"


typedef  unsigned  char  my_uint8_t;
typedef  unsigned  short  my_uint16_t;
typedef  unsigned  int  my_uint32_t;

#ifndef  PF_commonHandler
	typedef  int  (  *  PF_commonHandler  )(  LPVOID  p0,  LPVOID  p1,  LPVOID  p2  );
#endif


#ifdef  __cplusplus
extern  "C"  {
#endif


void  bzero(  void  *  p,  unsigned  int  size  );
int	 gettimeofday(struct timeval *, struct timezone *tz);


#ifdef  __cplusplus
}
#endif


#endif

