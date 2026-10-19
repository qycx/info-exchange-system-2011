

#include	"stdafx.h"
#include	"qnmCgi.h"


 int  printImMsgContent_n(  void  *  pSessionParam,  MSG_ROUTE  *  pRoute,  IM_CONTENTU  *  pContent_n,  int  iContentLen,  TCHAR  *  tBuf,  unsigned  int  maxuiBufCnt  )
 {
	 return  0;
 }

#ifdef  __DEBUG__	//  {


 int  procGet(  void  *  pCgiParam  );
 int  crackerUrl(  LPCSTR  URL_buffer,  char  *  extraInfoBuf,  unsigned  int  *  puiBufSize  );
 
  

 int  testCgiFunc(  void  *  pCgiParam  )
{
	 QNM_CGI	*	pCgi		=  (  QNM_CGI  *  )pCgiParam;
	 char		*	testIp		=	"192.168.103.132";
	 CHAR		*	url			=	(  "a=qm&v=010101&rC=23f34&c=getU"  );
	         url  =  "a=qm&s=6&rC=23f34&c=rcv";
		//	 url  =  "a=qm&s=c&rC=1550c&c=rcv";
	     //  url  =  "a=qm&s=1&rC=23f34&c=refrshU";
		 //  url  =  "a=qm&s=2&rC=71015&c=refrshU";
		//   url  =  "a=qm&s=6&rC=23f34&frm=&c=tlk&to=139&tNo=101&msg=%3Cspan%20style%3D%22font-family%3ATahoma%2Csans-serif%3Bfont-size%3A12px%3Bcolor%3A%23000000%3B%22%3EHi%3C%2Fspan%3E&c=tlk&to=139&tNo=102&msg=%3Cspan%20style%3D%22font-family%3ATahoma%2Csans-serif%3Bfont-size%3A12px%3Bcolor%3A%23000000%3B%22%3EHe%3C%2Fspan%3E&c=tlk&to=139&tNo=103&msg=%3Cspan%20style%3D%22font-family%3ATahoma%2Csans-serif%3Bfont-size%3A12px%3Bcolor%3A%23000000%3B%22%3EHaHa%3C%2Fspan%3E";
			 url  =  "a=qm&s=6&rC=303dd&c=refrshU";
			 url  =  "a=qm&s=1&rC=a50ad&frm=&c=tlk&to=100&tNo=101&msg=%3Cspan%20style%3D%22font-family%3ATahoma%2Csans-serif%3Bfont-size%3A12px%3Bcolor%3A%23000000%3B%22%3Em%3C%2Fspan%3E";

	 char			buf[2048]	=	"  f0x11";
	 long			l			=	0;
	 int			iRet		=	0;
	 //
	 unsigned  short	usCmd	=	0;

	 
	    //  outputQmBBodyHtml(  pCgi  );

	   //  outputQmBInnerHtml(  pCgi  );

	 if  (  0  )  {

	 	 traceLogA(  "ÔÚtestCgiFuncÖÐÄØ"  );

		 procPost(  pCgi,  url  );
	 
	 }
	 

	 //  crackerUrl(  url,  tBuf,  mycountof(  tBuf  )  );

	 //  _snprintf(  pCgi->remoteIp,  sizeof(  pCgi->remoteIp  ),  "%s",  testIp  );
	 //  procGet(  pCgi  );

	 return  0;
}


#endif		//  }


