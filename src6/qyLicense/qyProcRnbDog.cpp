
#include	<windows.h>
#include	"spromeps.h"	//  rainbow API的头文件
#include	"qyPreLicense.h"
#include	"qyLicense.h"
#include	"qyCommon.h"
#include	<tchar.h>




//
//
#define		CONST_qyMcHelpDll				"qyMcHelp.dll"
#define		CONST_getQyMcHelpDs				"getQyMcHelpDs"		//  

HINSTANCE			ghDll_qyMcHelp		=	NULL;
PF_commonHandler	pfGetQyMcHelpDs		=	NULL;

int  getLicenseCtxType(  );
//
int  getDevId_sentinelKey(  );
//
int  initSentinelKey(  QY_LICENSE_CTX  *  pCtx,  unsigned  int  devId  );
void  exitSentinelKey(  QY_LICENSE_CTX  *  pCtx  );
BOOL  bQySentinelKeyOk(  QY_LICENSE_CTX  *  pCtx,  LPCWSTR  moduleName  );

/*
 extern  "C"  int  initRnbDog(  QY_LICENSE_CTX  *  pCtx  )
{
	 static  RB_SPRO_APIPACKET		ApiPacket;		//  Rainbow 所定义的数据结构

	 if  (  !pCtx  )  return  -1;

	 memset(  pCtx,  0,  sizeof(  pCtx[0]  )  );

	 if  (  !ghDll_qyMcHelp  )	{
		 char		tmpFileName[MAX_PATH  +  1];
		 char		pathBuf[MAX_PATH  +  1];
		 char	*	filePart;

	 	 GetModuleFileName(  NULL,  tmpFileName,  sizeof(  tmpFileName  )  );
		 if  (  !GetFullPathName(  tmpFileName,  sizeof(  pathBuf  ),  pathBuf,  &filePart  )  )  return  -1;
		 filePart[0]  =  0;
		 _snprintf(  tmpFileName,  sizeof(  tmpFileName  ),  "%s%s",  pathBuf,  CONST_qyMcHelpDll  );
		 //  if  (  qyQuoteFileName(  tmpFileName,  sizeof(  tmpFileName  )  )  )  return  -1;
		 
		 if  (  !(  ghDll_qyMcHelp  =  LoadLibrary(  tmpFileName  )  )  )  {
			 qyDisplayLastError(  ""  );
			 traceLogA(  "没找到%s",  tmpFileName  );  return  -1;
		 }
		 pfGetQyMcHelpDs  =  (  PF_commonHandler  )GetProcAddress(  ghDll_qyMcHelp,  CONST_getQyMcHelpDs  );
		 if  (  !pfGetQyMcHelpDs  )  return  -1;

	 }

	 //
	 pCtx->type  =  getLicenseCtxType(  );			//  2007/02/28

	 //  if  (  pCtx->bRnbDogInited  )  return  0;

	 if  (  MACRO_bQnmWithoutChkDog(  pCtx  )  )  {
		 pCtx->bRnbDogInited  =  TRUE;  return  0;	//  2004/08/10增加
	 }


	 switch  (  pCtx->type  )  {
			 case  CONST_qyLicenseCtxType_superPro:
				   if  (  RNBOsproFormatPacket(  ApiPacket,  sizeof(  ApiPacket  )  )	//  初始化数据结构（仅Win32程序使用） 
		 			   ||  RNBOsproInitialize(  ApiPacket  )  )						//  初始化函数
				   {
					   return  -1;
				   }
	 			   pCtx->pApiPacket  =  &ApiPacket;
				   break;
			 case  CONST_qyLicenseCtxType_sentinelKey:
				   if  (  initSentinelKey(  pCtx,   getDevId_sentinelKey(  )  )  )  return  -1;
				   break;
			 default:
					return  -1;
	 }

	 pCtx->bRnbDogInited  =  TRUE;

	 return  0;
}
*/

 extern  "C"  int  initRnbDog(  QY_LICENSE_CTX  *  pCtx  )
{
	 int							iErr			=	-1;
	 static  RB_SPRO_APIPACKET		ApiPacket;		//  Rainbow 所定义的数据结构

	 if  (  !pCtx  )  return  -1;

	 memset(  pCtx,  0,  sizeof(  pCtx[0]  )  );

	 if  (  !ghDll_qyMcHelp  )	{
		 TCHAR		tmpFileName[MAX_PATH  +  1];
		 TCHAR		pathBuf[MAX_PATH  +  1];
		 TCHAR	*	filePart;

	 	 GetModuleFileName(  NULL,  tmpFileName,  mycountof(  tmpFileName  )  );
		 if  (  !GetFullPathName(  tmpFileName,  mycountof(  pathBuf  ),  pathBuf,  &filePart  )  )  return  -1;
		 filePart[0]  =  0;
		 _sntprintf(  tmpFileName,  mycountof(  tmpFileName  ),  _T(  "%s%s"  ),  pathBuf,  _T(  CONST_qyMcHelpDll  )  );
		 //  if  (  qyQuoteFileName(  tmpFileName,  sizeof(  tmpFileName  )  )  )  return  -1;
		 
		 if  (  !(  ghDll_qyMcHelp  =  LoadLibrary(  tmpFileName  )  )  )  {
			 qyDisplayLastError(  ""  );
			 traceLogA(  "%s",  tmpFileName  );  return  -1;
		 }
		 pfGetQyMcHelpDs  =  (  PF_commonHandler  )GetProcAddress(  ghDll_qyMcHelp,  CONST_getQyMcHelpDs  );
		 if  (  !pfGetQyMcHelpDs  )  return  -1;

	 }

	 //
	 pCtx->type  =  getLicenseCtxType(  );			//  2007/02/28

	 //  if  (  pCtx->bRnbDogInited  )  return  0;

	 #ifndef  CONST_TEST_DOG_SN
			  if  (  MACRO_bQnmWithoutChkDog(  pCtx  )  )  {
				  pCtx->bRnbDogInited  =  TRUE;  return  0;	//  2004/08/10增加
			  }
	 #endif

	 switch  (  pCtx->type  )  {
			 case  CONST_qyLicenseCtxType_superPro:
#ifdef  __NOTSUPPORT_superPro__
				   return  -1;
#else
#ifndef  __X64__
				   if  (  RNBOsproFormatPacket(  ApiPacket,  sizeof(  ApiPacket  )  )	//  初始化数据结构（仅Win32程序使用） 
		 			   ||  RNBOsproInitialize(  ApiPacket  )  )						//  初始化函数
				   {
					   return  -1;
				   }
	 			   pCtx->pApiPacket  =  &ApiPacket;
#else
				   return  -1;
#endif
#endif
				   break;
			 case  CONST_qyLicenseCtxType_sentinelKey:
				   if  (  initSentinelKey(  pCtx,   getDevId_sentinelKey(  )  )  )  {
					   if  (  MACRO_bQnmWithoutChkDog(  pCtx  )  )  {
						   pCtx->bRnbDogInited  =  TRUE;  
						   iErr  =  0;  goto  errLabel;
					   }
					   goto  errLabel;
				   }
				   #ifdef  CONST_TEST_DOG_SN
				           if  (  pCtx->uiSerialNo  ==  CONST_TEST_DOG_SN  
							   ||  pCtx->uiSerialNo  ==  CONST_TEST_DOG_SN1  )  
						   {
							   pCtx->bSnTest  =  TRUE;
						   }
				   #endif
				   break;
			 default:
					return  -1;
	 }

	 pCtx->bRnbDogInited  =  TRUE;

	 iErr  =  0;
errLabel:
	 return  iErr;
}


 extern  "C"  void  exitRnbDog(  QY_LICENSE_CTX  *  pCtx  )
{
	 if  (  !pCtx  )  return;

	 if  (  pCtx->bRnbDogInited  )  {
		 switch  (  pCtx->type  )  {
			     case  CONST_qyLicenseCtxType_superPro:
					   break;
				 case  CONST_qyLicenseCtxType_sentinelKey:
					   exitSentinelKey(  pCtx  );
					   break;
				 default:
						break;
		 }
		 pCtx->bRnbDogInited  =  FALSE;
	 }
	 if  (  ghDll_qyMcHelp  )	{

		 //  先放弃函数指针
		 pfGetQyMcHelpDs	=	NULL;
		 //
		 traceLogA(  "释放qyMcHelp.dll"  );
		 FreeLibrary(  ghDll_qyMcHelp  );  ghDll_qyMcHelp  =  NULL;
	 }

	 return;
}


 extern  "C"  BOOL  bQyDogOk(  QY_LICENSE_CTX  *  pCtx,  LPCWSTR  moduleName  )
{
	BOOL					bRet		=		FALSE;
	SP_STATUS				spStatus;
	static   RB_DWORD		qResult32;	
	RB_WORD					developerID;
	RB_SPRO_APIPACKET  *	pApiPacket	=  (  RB_SPRO_APIPACKET  *  )pCtx->pApiPacket;

	if  (  MACRO_bQnmWithoutChkDog(  pCtx  )  )  return  TRUE;	//  2004/08/10增加

	if  (  !pCtx   ||  !pCtx->bRnbDogInited  )  goto  errLabel;

	switch  (  pCtx->type  )  {
			case  CONST_qyLicenseCtxType_superPro:
				  break;
			case  CONST_qyLicenseCtxType_sentinelKey:
				  return  bQySentinelKeyOk(  pCtx,  moduleName  );
				  break;
			default:
					goto  errLabel;
	}
#ifdef  __NOTSUPPORT_superPro__
	goto  errLabel;
#else
#ifndef  __X64__

	developerID  =  0xF278;		//  开发者ID号
	//  注：这里所提到的ID号均为16进制数	
	spStatus  =  RNBOsproFindFirstUnit(  *pApiPacket,  developerID  );	//  找到Developer ID指定加密锁
	//									         ▲▲▲ 
	//									       加密琐的ID号 
	//  Findfirst返回值为0，代表找到加密锁，其他代表未找到加密锁，详细信息请参阅API手册
	if  (  spStatus  )  {
		OutputDebugString(  _T(  "找不到加密锁"  )  );  goto  errLabel;
	}
	{  
	//  "B1A8E011"(查询串),  "68A46B98"(响应串)   Rainbow Wizard所生成的数据 
	unsigned  char  queryData[]  =  {  0xB1,  0xA8,  0xE0,  0x11  };	//  欲查询数据	
	unsigned  char  cmpqueryData[]  =  { 0x68, 0xA4, 0x6B, 0x98 } ;	//  响应数据
	unsigned  char  response[]  =  {  0,  0,  0,  0  };				
	int  cellAddress  =  0x3A;	//  设置查询单元号
	int  queryLength  =  sizeof(  queryData  );		//  设置查询数据长度
	if  (  queryLength  !=  sizeof(  cmpqueryData  )  ||  queryLength  !=  sizeof(  response  )  )  {
		OutputDebugString(  _T(  "校验错误：	queryData、cmpqueryData、response的长度没有相等"  )  );  goto  errLabel;
	}
	spStatus  =  RNBOsproQuery(  *pApiPacket,		//  Apipacket为 Rainbow公司保留数据结构
								 cellAddress,	//  查询单元号
                             	 &queryData,	//  查询数据(输入加密锁的数据)
							     &response,     //  响应数据(经加密锁计算返回数据)
                             	 &qResult32,	//  qResult32为 Rainbow公司保留数据结构
								 queryLength  );//  查询数据长度
	spStatus  =  memcmp(  response,  cmpqueryData,  queryLength  );	//  比较响应数据和预知数据
	if  (  spStatus  !=  0  )  {							//  比较后返回值为0，代表查询响应正确，其他代表不正确，详细信息请参阅API手册
		OutputDebugString(  _T(  "查询不成功"  )  );  goto  errLabel;
	}
	}
#else
	goto  errLabel;
#endif
#endif
	bRet  =  TRUE;
errLabel:

	return  bRet;

}

