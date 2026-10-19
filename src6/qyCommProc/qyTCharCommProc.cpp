
#include	"stdafx.h"

#include	<windows.h>
#include	<tchar.h>
#include	"qyCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"



 extern  "C"  TCHAR  *  myStr2TChar(  char  *  buf,  TCHAR  *  tBuf,  unsigned  int  tBufSize  )
{
	int		iErr	=	-1;
	#ifndef	UNICODE
			safeStrnCpy(  buf,  tBuf,  tBufSize  );			
	#else
			if  (  !myStr2WChar(  buf,  tBuf,  tBufSize  )  )  goto  errLabel;
	#endif

	iErr  =  0;

#ifdef  UNICODE
errLabel:
#endif

	return  iErr  ?  NULL  :  tBuf;

}

 extern  "C"  char  *  myTChar2Str(  LPCTSTR  tBuf,  char  *  buf,  unsigned  int  bufSize  )
{
	 int	iErr	=	-1;
	 #ifndef  UNICODE
			  safeStrnCpy(  (  char  *  )tBuf,  buf,  bufSize  );
	 #else
			  if  (  !myWChar2Str(  (  LPTSTR  )tBuf,  buf,  bufSize  )  )  goto  errLabel;
	 #endif
	 iErr  =  0;

#ifdef  UNICODE
errLabel:
#endif
	 return  iErr  ?  NULL  :  buf;

}


 extern  "C"  char  *  myTChar2Utf8(  LPCTSTR  tBuf,  char  *  buf,  unsigned  int  bufSize  )
{
	 int	iErr	=	-1;
	 #ifndef  UNICODE
			  safeStrnCpy(  (  char  *  )tBuf,  buf,  bufSize  );
			  myStr2Utf8(  buf,  bufSize  );
	 #else
			  if  (  !myWChar2Utf8(  tBuf,  buf,  bufSize  )  )  goto  errLabel;
	 #endif
	 iErr  =  0;
#ifdef  UNICODE
errLabel:
#endif
	 return  iErr  ?  NULL  :  buf;

}

 extern  "C"  TCHAR  *  myUtf82TChar(  char  *  buf,  TCHAR  *  tBuf,  unsigned  int  tBufSize  )
{
	int		iErr  =  -1;
	#ifndef  UNICODE
			 safeStrnCpy(  buf,  tBuf,  tBufSize  );  if  (  !myUtf82Str(  tBuf,  tBufSize  )  )  goto  errLabel;
	#else
			 if  (  !myUtf82WChar(  buf,  tBuf,  tBufSize  )  )  goto  errLabel;
	#endif
	
	iErr  =  0;

errLabel:
	return  iErr  ?  NULL  :  tBuf;
}


 //  2005/11/27
 extern  "C"  WCHAR  *  myTChar2WChar(  LPCTSTR  tBuf,  WCHAR  *  wBuf,  unsigned  int  wBufSize  )
{
	int		iErr	=	-1;

	#ifndef  UNICODE
			 if  (  !myStr2WChar(  tBuf,  wBuf,  wBufSize  )  )  goto  errLabel;
	#else
			 lstrcpyn(  wBuf,  tBuf,  wBufSize  );
	#endif
	iErr  =  0;

#ifndef  UNICODE
errLabel:
#endif

	return  iErr  ?  L""  :  wBuf;
}

 //  2005/11/27
 extern  "C"  TCHAR  *  myWChar2TChar(  LPCWSTR  wBuf,  TCHAR  *  tBuf,  unsigned  int  tBufSize  )
{
	int		iErr	=	-1;

	#ifndef  UNICODE
			 if  (  !myWChar2Str(  wBuf,  tBuf,  tBufSize  )  )  goto  errLabel;
	#else
			 lstrcpyn(  tBuf,  wBuf,  tBufSize  );
	#endif
	iErr  =  0;

#ifndef  UNICODE
errLabel:
#endif

	return  iErr  ?  _T(  ""  )  :  tBuf;
}



#if  0  
 extern  "C"  void  tTrim(  TCHAR  *  buf  )
{
        TCHAR			*	p;
		unsigned  int		len		=	lstrlen(  buf  );

		if  (  !buf  ||  !(  len  =  lstrlen(  buf  )  )  )  return;
        p  =  buf  +  len  -  1;

        while  (  _istspace(  *p  )  &&  p  >=  buf  )  p  --;
        p[1]  =  0;

        if  (  p  >=  buf  )  {
            p  =  buf;
            while  (  _istspace(  *p  )  )  p  ++;
			lstrcpy(  buf,  p  );
        }

        return;

}
#endif

 extern  "C"  int  tQyQuoteFileName(  TCHAR  *  fileName,  unsigned  int  charSize  )
{

	//  extern  "C"  int  qyQuoteFileName(  char  *  fileName,  unsigned  int  size  )

	 unsigned  int	len;
	 TCHAR			quotedFileName[MAX_PATH  +  1];

	 tTrim(  fileName  );
	 if  (  fileName[0]  ==  '\"'  )  return  0;
	 len  =  lstrlen(  fileName  );
	 if  (  len  >=  charSize  -  2  ||  len  +  2  >  MAX_PATH  )  return  -1;
	 _sntprintf(  quotedFileName,  sizeof(  quotedFileName  )  /  sizeof(  TCHAR  ),  _T(  "\"%s\""  ),  fileName  );
	 lstrcpy(  fileName,  quotedFileName  );
	 return  0;	 
}


 extern  "C"  int  tTrailDir(  TCHAR  *  dir,  unsigned  int  size  )
{
	 unsigned  int	len;

	 tTrim(  dir  );
	 len  =  lstrlen(  dir  );
	 if  (  dir[len  -  1]  ==  '\\'  )  return  0;
	 if  (  len  +  2  >  size  )  return  -1;
	 dir[len]  =  '\\';
	 dir[len  +  1]  =  0;
	 return  0;
	
}

#if  0
 extern  "C"  int  tQyStrCat(  TCHAR  *  str1,  TCHAR  *  str2,  TCHAR  *  containedBuf,  unsigned  int  bufSize  ) 
{
	 int  iErr  =  -1;

	 if  (  str2  ==  containedBuf  )  {
		 traceLogA(  "qyStrCat( ): str2 can't be the place to contain."  );
		 goto  errLabel;
	 }
	 if  (  lstrlen(  str1  )  +  lstrlen(  str2  )  >=  (  int  )bufSize  )  {
		 traceLogA(  "qyStrCat( ): buf too small."  );
		 goto  errLabel;
	 }
	 _sntprintf(  containedBuf,  bufSize,  _T(  "%s%s"  ),  str1,  str2  );
	 iErr  =  0;

errLabel:

	 return  iErr;

}
#endif
