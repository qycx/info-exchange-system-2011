

#include	"stdafx.h"
#include	"qmdCommon.h"






 //  Response  =  str0  +  len  +  str1  +  htmlStr  +  "\r\n"

char  *  CONST_qnmRegResponseStr0	=	"HTTP/1.0 200 OK\r\n"
									"Server: Microsoft-IIS/5.0/1.0\r\n"
									//  "Date: Mon, 19 May 2003 03:50:08 GMT\r\n"
									"Content-type: text/html\r\n"
									"Content-length: ";
									//  69
char  *  CONST_qnmRegResponseStr1  =  "\r\n"
									//  "Last-Modified: Sat, 17 May 2003 18:04:07 GMT\r\n"
									"\r\n";
char  *  CONST_qnmRegHtmlStr		=	"<html><title>欢迎登记您的信息</title><body>我们jjjjmmm</body></html>\r\n";

								








 






 void  swapChar(  char  *  pOriginal,  char  cBad,  char  cGood  )
{
	 int	i;

	 i  =  0;
	 while  (  pOriginal[i]  )  {
			if  (  pOriginal[i]  ==  cBad  )  pOriginal[i]  =  cGood;
			i  ++  ;
	 }
}

 static  int  intFromHex(  char  *  pChars1  )
{
	 int				hi;
	 int				lo;
	 int				result;
	 unsigned  char	*	pChars	=	(  unsigned  char  *  )pChars1;

	 hi  =  pChars[0];
	 if  (  '0'  <=  hi  &&  hi  <=  '9'  )  {
		 hi  -=  '0';
		}
	 else  if  (  'a'  <=  hi  &&  hi  <=  'f'  )  {
			   hi  -=  (  'a'  -  10  );
			}
	 else  if  (  'A'  <=  hi  &&  hi  <=  'F'  )  {
			   hi  -=  (  'A'  -  10  );
	 }

	 lo  =  pChars[1];
	 if  (  '0'  <=  lo  &&  lo  <=  '9'  )  {
		 lo  -=  '0';
		}
	 else  if  (  'a'  <=  lo  &&  lo  <=  'f'  )  {
				lo  -=  (  'a'  -  10  );
				}
	 else  if  (  'A'  <=  lo  &&  lo  <=  'F'  )  {
			   lo  -=  (  'A'  -  10  );
	 }

	 result  =  lo  +  (  16  *  hi  );

	 return  result;
 
}

 extern  "C"  void  urlDecode(  char  *  pEncoded  )
{
	 unsigned  char  *  pDecoded;

	 swapChar(  (  char  *  )pEncoded,  '+',  ' '  );

	 pDecoded  =  (  unsigned  char  *  )pEncoded;
	 while  (  *pEncoded  )  {
			if  (  *pEncoded  ==  '%'  )  {
				pEncoded  ++  ;
				if  (  isxdigit(  pEncoded[0]  )  &&  isxdigit(  pEncoded[1]  )  )  {
					*pDecoded  ++  =  (  char  )intFromHex(  pEncoded  );
					pEncoded +=  2;
				}
				
				}				
			else  {
					*pDecoded  ++=  *pEncoded  ++;
			}
	 }

	 *pDecoded  =  '\0';
			
}


 extern  "C"  int  qnmGetHttpVarPair(  char  *  varVal,  QY_VAR_PAIR	*  pPair  )
{
	 char  *	pEquals;
	 int		i;

	 pEquals  =  strchr(  varVal,  '='  );
	 if  (  !pEquals  )  return  -1;
	 *pEquals  ++  =  '\0';
	 urlDecode(  varVal  );
	
	 i  =  0;
	 while  (  varVal[i]  )  {
			varVal[i]  =  toupper(  varVal[i]  );
			i  ++  ;
	 }
	
	 urlDecode(  pEquals  );
	 //  traceLogA(  "%s=%s",  varVal,  pEquals  );
	 
	 pPair->name  =  varVal;
	 pPair->val  =  pEquals;
	 return  0;
}


 /*
 void  printOut(  unsigned  char  *  varVal  )
{
	 unsigned  char  *	pEquals;
	 int		i;

	 pEquals  =  (  unsigned  char  *  )strchr(  (  char  *  )varVal,  '='  );
	 if  (  pEquals  )  {
		 *pEquals  ++  =  '\0';
		 urlDecode(  varVal  );

		 i  =  0;
		 while  (  varVal[i]  )  {
				varVal[i]  =  toupper(  varVal[i]  );
				i  ++  ;
		 }

		 urlDecode(  pEquals  );
		 traceLogA(  "%s=%s",  varVal,  pEquals  );
	 }
}

 int  showPostData(  char  *  inputBuffer  )
{
	 char  *  pToken;

	 pToken  =  strtok(  inputBuffer,  "&"  );
	 while  (  pToken  !=  NULL  )  {
			printOut(  (  unsigned  char  *  )pToken  );
			pToken  =  strtok(  NULL,  "&"  );
	 }
	 return  0;

}

*/









