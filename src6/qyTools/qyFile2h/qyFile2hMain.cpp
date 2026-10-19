

#include	"stdafx.h"
#include	"test.lib.h"

/*
		file = fopen( chkHeadFile, "w" );
		fprintf( file, "#define %s %d\n", fileSizeName, stat.st_size );
		fprintf( file, "#define %s {", macroName );
		for ( i = 0; i < 15; i ++ ) {
			fprintf( file, " ( unsigned char )0x%02x,", digest[i] );
		}
		fprintf( file, " ( unsigned char )0x%02x", digest[i] );
		fprintf( file, " }\n" );
		fclose( file );
*/

 extern "C" void replaceChar( unsigned char  replacedC, unsigned char replacingC, char *buf, unsigned int len )
{
	 //  traceLogA( "replaceChar( ): enters, buf is [%s]", buf );
	 for ( ; len; len -- ) {
		 if ( ( unsigned char )buf[len - 1] == replacedC ) buf[len - 1] = replacingC;
	 }
	 //  traceLogA( "replaceChar( ): leaves, buf is [%s]", buf );
	 return;
}


#define		CONST_kk	{  (  unsigned  char  )0x03,  (  unsigned  char  )0x04  }

unsigned  char	ptr[2]  =  CONST_kk;
unsigned  char  testLibBuf[CONST_test_lib_size]  =  CONST_test_lib;

 int  outputFile(  char  *  fileName,  char  *  buf,  int  size  )
{
	 CFile	fOut;
	 int	i;

	 if  (  !fOut.Open(  fileName,  CFile::modeCreate | CFile::modeWrite  )  )  goto  errLabel;
	 for  (  i  =  0;  i  <  size;  i  ++  )  {
		  fOut.Write(  &buf[i],  1  );
	 }
errLabel:
	 return  0;
}

 int  qyFile2hMain(  int  argc,  char  **  argv  )
{
	 
	int		iErr  =  -1;
	CFile   fIn,  fOut;
	UINT	nRead;
	char	buf[2048];
	int		i;
	DWORD	fileLen;
	char	fileLenMacroBuf[1024];
	char	fileMacroBuf[1024];
	char	outBuf[4096];
	int		nCharsOneLine  =  16;
	int		cnt  =  0;

	//  outputFile(  "my.test.lib",  (  char  *  )testLibBuf,  CONST_test_lib_size  );
	//  return  0;

	if  (  argc  !=  2  )  {
		printf(  "Usage: %s file.",  argv[0]  );
		return  -1;
	}

	if  ( !fIn.Open(  argv[1],  CFile::modeRead  )  )  goto  errLabel;
	if  (  !fOut.Open(  CString(  argv[1]  )  +  ".h",  CFile::modeCreate | CFile::modeWrite  )  )  goto  errLabel;

	strcpy(  outBuf,  "\r\n"  );
	fOut.Write(  outBuf,  strlen(  outBuf  )  );

	sprintf(  fileLenMacroBuf,  "CONST_%s_size",  argv[1]  );
	replaceChar(  '.',  '_',  fileLenMacroBuf,  strlen(  fileLenMacroBuf  )  );
	fileLen  =  fIn.GetLength(  );

	sprintf(  outBuf,  "#define	 %s	%d\r\n",	fileLenMacroBuf,  fileLen  );
	fOut.Write(  outBuf,  strlen(  outBuf  )  );

	printf(  "file has %d bytes.\n",  fileLen  );

	sprintf(  fileMacroBuf,  "CONST_%s",  argv[1]  );
	replaceChar(  '.',  '_',  fileMacroBuf,  strlen(  fileMacroBuf  )  );
	sprintf(  outBuf,  "#define  %s  {	\\\r\n",  fileMacroBuf  );
	fOut.Write(  outBuf,  strlen(  outBuf  )  );
		
	nRead  =  fIn.Read(  buf,  nCharsOneLine  );
	for  (  ;  nRead  ==  nCharsOneLine;  nRead  =  fIn.Read(  buf,  nCharsOneLine  )  )  {
		 outBuf[0]  =  0;
		 for  (  i  =  0;  i  <  nRead;  i  ++  )  {
			  sprintf(  outBuf,  "%s\t(  unsigned  char  )0x%02x,",  outBuf,  (  unsigned  char  )buf[i]  );
		 }
		 sprintf(  outBuf,  "%s\\\r\n",  outBuf  );		 
		 fOut.Write(  outBuf,  strlen(  outBuf  )  );
		 cnt  +=  nRead;
		 printf(  "%d bytes, %f have been processed.\n",  cnt,  cnt  /  (  float  )fileLen  );
	}

	if  (  nRead  )  {
		outBuf[0]  =  0;
		for  (  i  =  0;  i  <  nRead;  i  ++  )  {
			 sprintf(  outBuf,  "%s\t(  unsigned  char  )0x%02x,",  outBuf,  (  unsigned  char  )buf[i]  );
		}
		sprintf(  outBuf,  "%s\\\r\n",  outBuf  );
		fOut.Write(  outBuf,  strlen(  outBuf  )  );

		cnt  +=  nRead;
		printf(  "%d bytes, %f have been processed.\n",  cnt,  cnt  /  (  float  )fileLen  );

	}

	sprintf(  outBuf,  "}\r\n"   );
	fOut.Write(  outBuf,  strlen(  outBuf  )  );

	iErr  =  0;

errLabel:

	return  iErr;

}

