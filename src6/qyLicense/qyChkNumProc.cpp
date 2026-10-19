

#include	<stdio.h> 
#include	<string.h>
#include    <time.h>
#include	<windows.h>
#include	<tchar.h>
#include	"qyCommon.h"
#include	"qyLicense.h"
#include	"qyTCharCommProc.h"

 //  注意：键值最好设为“默认”
 extern  "C"  QY_DMITEM    CONST_qyRootKey_chkNum_table[]  =						//  分段在5个之内
{
	{  0,			_T(  "Software\\Classes\\.axc"  ),      },
	{  1,			_T(  "Software\\Classes\\.bxc"  ),      },
	{  2,			_T(  "Software\\Classes\\.cxc"  ),      },
	{  3,			_T(  "Software\\Classes\\.dxc"  ),      },
	{  4,			_T(  "Software\\Classes\\.exc"  ),      },
	{  -1,			NULL,							},
};

 
 BOOL  bGetHardwareIdOk(  void  *  pEnvParam,  LPCTSTR  fileName  )
{
#if  0
	BOOL			bErr							=   FALSE;
	HANDLE			hFile							=   NULL;
	char			idBuf[CONST_hardwareId_len]		=   "";
	unsigned int	idBufSize;
	char			recvBuf[CONST_hardwareId_len]	=   "";
	LPDWORD			lpNumberOfBytesWritten			=   (  unsigned  long  *  )&recvBuf;

	//  读取硬件信息
	if  (  testProductIdMain(  pEnvParam,  idBuf,  &idBufSize  )  )  goto  errLabel;
	//  伪装硬件信息（ 校验码、加密）
	if  (  spoofHarewareId(  idBuf,  &idBufSize  )  ) goto  errLabel;
	//  存放至文件中
	if  (  (hFile  =  CreateFile(  fileName,  GENERIC_WRITE,  NULL,  NULL,  CREATE_ALWAYS,  NULL,  NULL  )  )  ==  INVALID_HANDLE_VALUE ) { traceLogA (  "error!"  ); goto  errLabel; }
	if  (  !WriteFile(  hFile,  idBuf,  idBufSize,  lpNumberOfBytesWritten,  NULL  )  ) { traceLogA(  "error!"  ); goto  errLabel; }

	bErr			=  TRUE;
errLabel:

	if  (  hFile  &&  hFile  !=  INVALID_HANDLE_VALUE  )  CloseHandle(  hFile  );
	return			bErr;

}

 BOOL  bCalcChkNumOk(  LPCTSTR  inputFileName,  LPCTSTR  outputFileName  )
{
    BOOL			bRet			=  FALSE;
	BOOL			bResult			=  FALSE;
	HANDLE			hIdFile			=  NULL;
	HANDLE			hLicenseFile	=  NULL;
	char			inBuf[256]		=  "";
	unsigned int	inBufSize;
	char			decBuf[256]		=  "";
	unsigned int	decBufSize;
	char			outBuf[512]		=  "";
	unsigned int 	outSize;
	unsigned long	recvSize;

	//  读取加密的硬件信息
	if  (  (  hIdFile  =  CreateFile(  inputFileName,  GENERIC_READ,  NULL,  NULL,  OPEN_EXISTING,  NULL,  NULL  )  )  ==  INVALID_HANDLE_VALUE  )  goto  errLabel; 
	if  (  !(bResult  =  ReadFile(  hIdFile,  inBuf,  sizeof( inBuf ),  (  unsigned  long * )&inBufSize,  NULL  )  )  )  goto  errLabel;

	//  还原硬件信息（校验、脱密）
	if  (  decProc(  inBuf,  inBufSize,  decBuf,  &decBufSize  )  )  goto  errLabel;
	//  产生出license
	if  (  testLicenseMain(  decBuf,  decBufSize,  outBuf,  &outSize  )  )  {  traceLogA(  "getChkNum  error!"  );  goto  errLabel;  }
	//  将license 转换为字符存在文件中
	if  (  (  hLicenseFile  =  CreateFile(  outputFileName,  GENERIC_WRITE,  NULL,  NULL,  CREATE_ALWAYS,  NULL,  NULL  )  )  ==  INVALID_HANDLE_VALUE  ) { traceLogA(  "create  license.txt  file  failed "  ); goto  errLabel;  }
	if  (  !WriteFile(  hLicenseFile,  outBuf,  outSize,  &recvSize,  NULL  )  )  { traceLogA(  " write  license.txt  failed "  ); goto  errLabel; }
	
	bRet		=   TRUE;
errLabel:

	if  (  hIdFile  &&  hIdFile  !=  INVALID_HANDLE_VALUE  )  CloseHandle(  hIdFile  );
	if  (  hLicenseFile  &&  hLicenseFile  !=  INVALID_HANDLE_VALUE  )  CloseHandle(  hLicenseFile  );

	return		bRet;
#endif
	return  FALSE;
}


 //      ----------------------------------------
 BOOL  bSetChkNumOk(  LPCTSTR  fileName  )
{
	BOOL					bRet			=  FALSE;
	BOOL					bResult			=  FALSE;
	HANDLE					hFile			=  NULL;
	char					readData[256]   =  "";
	char					xbuf[512]		=  "";
	//  unsigned int			xlen, i;
	unsigned long			readLen;
	CHKNUMFIELD				field;


	if  (  (  hFile  =  CreateFile(  fileName,  GENERIC_READ,  NULL,  NULL,  OPEN_EXISTING,  NULL,  NULL  )  )  ==  INVALID_HANDLE_VALUE  )  { traceLogA(  "create  license.txt  failed "  ); goto  errLabel; }
	if  (  !(  bResult  =  ReadFile(  hFile,  readData,  sizeof(  readData  ),  &readLen,  NULL  )  )  )  { traceLogA(  "  read license.txt failed "  ); goto  errLabel; }

	/*
	qyBuf2X(  readData,  readLen,  xbuf  );
	xlen		=  sizeof(  xbuf  );
	for (  i = xlen -1;  i >= 0;  i -- ) {
		if ( xbuf[i] != 0x30  )  break;
	}
	xbuf[i + 1] = 0;
	xlen			= strlen( xbuf );
	*/
	memset(  &field, 0,  sizeof(  field  )  );
	
	field.nField  =  3;
	field.u.fieldLen[0]  =  readLen / 3;
	field.u.fieldLen[1]  =  readLen / 4;
	field.u.fieldLen[2]  =  readLen - readLen / 3 - readLen / 4;
			
	//  char		data[256]  =  "aaaaaaaaaaaaaabbbbbbbbbbbbbbbcccccccccccccccddddddddddddddeeeeeeeeeeeeeeeeffffffffggggggggggggggghhhhhhhhh";
	//  char		data[256]  =  "";			//  边界测试
	if  (  qySetChkNum(  readData,  readLen,  &field  )  ) { traceLogA(  "error "  );	goto  errLabel;	}//  切记：需要加密后存储

	 bRet  =  TRUE;
errLabel:
	 if  (  hFile  &&  hFile  !=  INVALID_HANDLE_VALUE  )  CloseHandle(  hFile  );
	 return  bRet;
}


 //    分段截取(1/4;3/4*1/4;13/16)，分别写注册表；
 extern  "C"  int  qySetChkNum( char  *  input,  int  inputLen,  CHKNUMFIELD  *  field  )	//  分段分点存储校验值
{
	 
	 int					iRet		=  -1;
	 int					i;
	 char					buf[256]	=  "";
	 TCHAR					tBuf[256]	=  _T(  ""  );
	 char				*   p			=  NULL;
	 unsigned  int			len;
	 
	 p					=	input  ;
	 
	 strncpy(  buf,  p,  field->u.fieldLen[0]  );
		 

	 for (  i = 0; i < field->nField;  i ++  )  {
		 myStr2TChar(  buf,  tBuf,  mycountof(  tBuf  )  );
		 if (  qySetRegCfg(  CONST_qyRootKey_chkNum_table[i].des,  _T(  CONST_regValName_chkNum  ),  tBuf  ) )  goto  errLabel;
		 
		 p  =  p  +  field->u.fieldLen[i];
 		 memset(  buf,  0,  sizeof(  buf  )  );
		 len  =  field->u.fieldLen[i + 1] < sizeof(  buf ) ? field->u.fieldLen[i + 1] : sizeof( buf );

		 strncpy(  buf,  p,  len  );
		 len  =  strlen(  buf );
		 if (  !len  ||  ( field->u.fieldLen[i+1] > len  )  )  {
			 myStr2TChar(  buf,  tBuf,  mycountof(  tBuf  )  );
			 if (  qySetRegCfg(  CONST_qyRootKey_chkNum_table[i+1].des,  _T(  CONST_regValName_chkNum  ),  tBuf  )  )  goto  errLabel;
			 break;
		 }
	 }

	 iRet    =  0;
errLabel:
	 return  iRet;
}

 BOOL  bGetChkNumOk(  char  *  chkNumBuf  )
{
	 BOOL				bErr				=  FALSE;
	 char				tmpBuf[256]			=  "";
	 unsigned int		tmpBufSize			=  sizeof(  tmpBuf );
	 int				i;

	 memset(  tmpBuf,	0,  sizeof(  tmpBuf  )  );

	 for  (  i =  0;  CONST_qyRootKey_chkNum_table[i].type >= 0;  i ++  )  {
		 if  (  qyGetRegCfg(  CONST_qyRootKey_chkNum_table[i].des,  _T(  CONST_regValName_chkNum  ),  tmpBuf,  tmpBufSize  )  )  tmpBufSize  =  0;
		 if  (  !tmpBufSize  ||  !*tmpBuf  )  break;
		 strcat(  chkNumBuf,  tmpBuf  );	
	 }
	 
	 bErr				=  TRUE;
//errLabel:
	 return   bErr;

}