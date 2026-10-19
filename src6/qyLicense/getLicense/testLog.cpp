
#include	<windows.h>

#ifdef  _DEBUG
  #define  __DEBUG__
  #define  LOGDIR	"c:\\temp"
#endif

extern  "C"  int  getCurTime(  char  *  timeBuf  );
extern  "C"  char  *  qyDisplayTime(  char  *  buf,  char  *  displayBuf,  unsigned  int  size  );

 
/*
  extern  "C"  int  getCurTime(  char  *  timeBuf  )
{
	SYSTEMTIME  when;
	
	GetLocalTime(  &when  );

	wsprintf(  timeBuf,  
				"%04d%02d%02d%02d%02d%02d", 
					when.wYear,  
						when.wMonth,  
							when.wDay,  
								when.wHour,  
									when.wMinute,  
										when.wSecond  );

	return  0;

}

 extern  "C"  char  *  qyDisplayTime(  char  *  buf,  char  *  displayBuf,  unsigned  int  size  )
{
	char  *  ptr  =  displayBuf;

	if  (  size  <  20  ||  lstrlen(  buf  )  <  14  )  return  NULL;
	memcpy(  displayBuf,  buf,  4  );  displayBuf  +=  4;	buf  +=  4;
	displayBuf[0]  =  '-';  displayBuf  ++;
	memcpy(  displayBuf, buf, 2 ); displayBuf += 2; buf += 2;
	displayBuf[0]  =  '-';  displayBuf  ++;
	memcpy(  displayBuf, buf, 2 ); displayBuf += 2; buf += 2;
	displayBuf[0] = ' '; displayBuf ++;
	memcpy(  displayBuf, buf, 2 ); displayBuf += 2; buf += 2;
	displayBuf[0] = ':'; displayBuf ++;
	memcpy(  displayBuf, buf, 2 ); displayBuf += 2; buf += 2;
	displayBuf[0] = ':'; displayBuf ++;
	memcpy(  displayBuf, buf, 2 ); displayBuf += 2; buf += 2;
	displayBuf[0] = '\0';
	
	return ptr;

}

  */

  

