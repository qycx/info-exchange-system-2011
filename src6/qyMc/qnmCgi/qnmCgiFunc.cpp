
#include	"stdafx.h"
#include	"qnmCgi.h"


 int  printMimeHeader(  )
{
	 printf(  "Content-type:text/html\n\n"  );
	 return  0;
}

 void  printHtmlHeader(  char  *  charset,  char  *  title  )
{
	 if  (  !charset  )  charset  =  "utf-8";
	 if  (  !title  )  title  =  "";

	 printf(  "<html>\n"  
			  "<head><meta http-equiv=\"Content-Type\" content=\"text/html;charset=%s\"/><title>%s</title></head>\n"
			  "<body>\n",  charset,  title  );
			 
	 //  printf(  "<h1>Test :<i>Using CGI</i></h1>\n"  );
	 //  printf(  "<b>qnmCgi.cpp</b> -- demonstration CGI written in C to show environment variables and POSTed data<p>"  );
}

 void  printHtmlTrailer(  )
{
	 printf  (  "</body></html>\n" );
}


int  printXmlHeader(  )
{
	 printf(  "Content-type:text/xml\n\n"  );
	 return  0;
}



 void  outputErrHint(  BOOL  ucbXml,  int  iErrCode,  char  *  title,  char  *  content  )
{
	 if  (  ucbXml  )  {
		 printXmlHeader(  );
		 printf(  "<xml>"  );
		 printf(  "<errCode>%d</errCode>",  iErrCode  );
		 printf(  "<title>%s</title>",  title  ?  title  :  ""  );
		 printf(  "<content>%s</content>",  content  ?  content  :  ""  );
		 printf(  "</xml>"  );
		 //
		 return;
	 }
	 printMimeHeader(  );
	 printHtmlHeader(  NULL,  title  );
	 printf(  "Failed: %s",  (  content  ?  content  :  ""  )  );
	 printHtmlTrailer(  );
	 return;
}

 void  printVars(  BOOL  bOutputHtml  )
{
	 int  i  =  0;
	 char  buf[1024  +  1]  =  "";

	 if  (  bOutputHtml  )  {
         printf(  "<b>Environment Variables</b>\n"  );
	 	 printf(  "<ul>\n"  );
	 }

	 while  (  _environ[i]  )  {
		    _snprintf(  buf,  sizeof(  buf  ),  "%s",  _environ[i]  );
			urlDecode(  buf  );
			if  (  bOutputHtml  )  printf(  "<li>%s\n",  buf  );
			//
			//  traceLogA(  "µÚ%d¸öenv var is [%s]",  i,  buf  );
			//
			i  ++;
	 }
	 if  (  bOutputHtml  )  printf(  "</ul>\n"  );
}


  static  int  intFromHex(  char  *  pChars  )
{
	 int  hi;
	 int  lo;
	 int  result;

	 hi  =  pChars[0];
	 if  (  '0' <= hi && hi <= '9'  )  hi  -=  '0';
	 if  (  'a' <= hi && hi <- 'f'  )  hi  -=  (  'a'  -  10  );
	 if  (  'A' <= hi && hi <= 'F'  )  hi  -=  (  'A'  -  10  );

	 lo  =  pChars[1];
	 if  (  '0' <= lo && lo <= '9'  )  lo  -=  '0';
	 if  (  'a' <= lo && lo <- 'f'  )  lo  -=  (  'a'  -  10  );
	 if  (  'A' <= lo && lo <= 'F'  )  lo  -=  (  'A'  -  10  );

	 result  =  lo  +  (  16 *  hi  );
	 return  result;
}

 void  swapChar(  char  *  pOriginal,  char  cBad,  char  cGood  )
{
	 int  i  =  0;
	 while  (  pOriginal[i]  )  {  
		    if  (  pOriginal[i]  ==  cBad  )  pOriginal[i]  =  cGood;  i ++;  
	 }
}

 void  urlDecode(  char  *pEncoded  )  
{
	 char  *pDecoded  =  NULL;

	 swapChar(  pEncoded,  '+',  ' '  );
	 pDecoded  =  pEncoded;
	 while  (  *pEncoded  )  {
		    if  (  *pEncoded  ==  '%'  )  {
				pEncoded  ++;
				if  (  isxdigit(  pEncoded[0]  )  &&  isxdigit(  pEncoded[1]  )  )  {
					*pDecoded++  =   (  char  )  intFromHex(  pEncoded  );  pEncoded  +=  2;
				}
			}
			else  *pDecoded++  =  *pEncoded++;
	 }
	 *pDecoded  = '\0';
}

