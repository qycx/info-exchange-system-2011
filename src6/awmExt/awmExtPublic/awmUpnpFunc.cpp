
#include	"stdafx.h"
#include	<winsock2.h>
#include	<stdlib.h>
#include	<stdio.h>
#include	"qyCommon.h"
#include	"awmext.h"
#include	"aeHelpFunc.h"


 char  *  str_replace(  char  *  rep,  char  *  orig,  char  *  string  ) 
{ 
	 int  len  =  strlen(  orig  ); 
	 char buf[CONST_qyBufSize_upnp]  =  ""; 
	 char  *  pt  =  strstr(  string,  orig  ); 

	 if  (  !pt  )  return  NULL;
	 strncpy(  buf,  string,  pt  -  string  ); 
	 strcat(  buf,  rep  ); 
	 strcat(  buf,  pt  +  strlen(  orig  )  ); 
	 strcpy(  string,  buf  ); 

	 return  string; 

} 



 extern  "C"  int  qyUpnpScan(  char  *  interMonIp,  unsigned  short  interMonPort,  char  *  scannedIp,  unsigned  short  upnpPort,  char  *  sndData,  unsigned  int  sndLen,  int  sockFd  )
{
	int						iErr  =  -1;
	struct  sockaddr_in		their_addr; 
	char					portBuf[16];
	char					xSndDataBuf[8  +  CONST_qyDataMaxLen  *  2];
	int						numBytes; 
	char				*	ptr;

	
	if  (  sockFd  <  0  )  return  -1;
	if  (  INADDR_NONE  ==  inet_addr(  interMonIp  )  ||  INADDR_NONE  ==  inet_addr(  scannedIp  )  )  return  -1;
	if  (  sndLen  >  CONST_qyDataMaxLen  )  return  -1;
	
	char  send_buffer[CONST_qyBufSize_upnp]   =	  "NOTIFY * HTTP/1.1\r\nHOST: 239.255.255.250:1900\r\n" 
												  "CACHE-CONTROL: max-age=1\r\nLOCATION: http://www.host.com:port/qyUpnpParam\r\n" 
												  "NT: urn:schemas-upnp-org:device:InternetGatewayDevice:1\r\n" 
												  "NTS: ssdp:alive\r\nSERVER: QB0X/201 UPnP/1.0 prouct/1.1\r\n" 
												  "USN: uuid:QB0X\r\n\r\n\r\n"; 
	char  *  aux			=	send_buffer; 
	
	sprintf(  portBuf,  "%d",  interMonPort  );
	aux  =  str_replace(  interMonIp,  "www.host.com",  send_buffer  ); 
	aux  =  str_replace(  portBuf,  "port",  send_buffer  ); 
		
	ptr  =  xSndDataBuf;
	strcpy(  ptr,  CONST_qyMagic_upnp  );
	ptr  +=  strlen(  CONST_qyMagic_upnp  );
	qyL2XStr(  sndLen,  ptr,  8  );
	ptr  +=  8;
	qyBuf2X(  sndData,  sndLen,  ptr  );
	ptr[2  *  sndLen]  =  0;
	aux  =  str_replace(  xSndDataBuf,  "qyUpnpParam",  send_buffer  );

	memset(  &their_addr,  0,  sizeof(  their_addr  )  );
	their_addr.sin_family  =  AF_INET; 
	their_addr.sin_port  =  htons(  upnpPort  ); 
	their_addr.sin_addr.S_un.S_addr  =  inet_addr(  scannedIp  );
		
	if  (  (  numBytes  =  sendto(  sockFd,  send_buffer,  strlen(  send_buffer  ),  0,  (  struct  sockaddr  *  )&their_addr,  sizeof(  struct  sockaddr  )  )  )  ==  -1  )  { 
		perror(  "send"  );   
		goto  errLabel;
	} 

	iErr   =   0;

errLabel:

	return  iErr;

}


