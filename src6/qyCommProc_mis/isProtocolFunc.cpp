

#include	"stdafx.h"

#include	"qyPrecomp.h"
#include	<winsock2.h>
#include	<windows.h>
#include	<stddef.h>
#include	<assert.h>
#include	<tchar.h>
#ifndef  __WINCE__
	#include	<vfw.h>
#else
	#ifdef  __TEST__
		#include	<vfw.h>
	#endif

	#include	<mmreg.h>
	#include	<MSAcm.h>
#endif
#include	<Wincrypt.h>

#include	"qyCommon.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"qmOpenCommon.h"
#include	"qyMsgFunc.h"

#include	"qySyncCommProc.h"
#include	"genericQueue.h"
#include	"qyq2.h"				//  2009/05/13

#include	"qnmCommProc_mis.h"
#include	"qnmPcComm.h"
#include	"qnmAssetsCommProc.h"
#include	"qnmSpCommProc.h"
#include	"qwmNetworkStatusCommProc.h"
#include	"qyTCharCommProc.h"
#include	"qnmCustom.h"
#include	"qySyncCommProc.h"
#include	"qmCrypt.h"
#include	"qnmFwCommProc.h"
#include	"qyString.h"


 //  对orgData是WCHAR的情况，orgDataSize表示WCHAR的count
 //  对这个流要求用CONST_qnmCfgId_null结尾
 //  *pptr指向下一个空间，而不是输出串
 //  *pSize为剩余的字节数，不是一共得到了多少
#if  0
 int  data2Stream(  int  iDataType,  unsigned  short  usCfgId,  void  *  orgData,  unsigned  int  orgDataSize,  char  **  pptr_usable,  unsigned  int  *  pSize_usable  )
{
	 int					iErr			=	-1;
	 QY_CFGITEM_STR			itemStr;
	 QY_CFGITEM_LONG		itemLong;
	 QY_CFGITEM_CHAR		itemChar;
	 QY_CFGITEM_SHORT		itemShort;
	 QY_CFGITEM_L64			itemL64;
	 QY_CFGITEM			*	pItem			=	NULL;
	 unsigned  int			len;
	 unsigned  int			size			=	0;
	 char				*	ptr				=	NULL;
	 CQyMalloc				mallocObj;

	 if  (  !pptr_usable  ||  !*pptr_usable  ||  !pSize_usable  )  return  -1;
	 if  (  !orgData  )  {
		 switch  (  iDataType  )  {
			     case  CONST_qyDataType_long:
				 case  CONST_qyDataType_char:
				 case  CONST_qyDataType_short:
					   break;
				 default:
					     return  -1;	//  非数值的值为地址，不能为空
		 }
	 }
	 if  (  iDataType  ==  CONST_qyDataType_l64  )  {
		 if  (  orgDataSize  &&  orgDataSize  <  sizeof(  __int64  )  )  {		//  传入0也算了，早期代码都用0。2007/12/11
			 traceLogA(  "data2Stream: l64需要传入数据地址，故建议输入数据长度应>=sizeof(  __int64  )"  );  
		 }
	 }

	 ptr  =  *pptr_usable;
	 size  =  *pSize_usable;

	 switch  (  iDataType  )  {
			 case  CONST_qyDataType_long:
				   itemLong.cfgId  =  usCfgId;
				   itemLong.dataType  =  iDataType;
				   itemLong.ulVal  =  (  unsigned  long  )orgData;
				   pItem  =  (  QY_CFGITEM  *  )&itemLong;
				   break;
			 case  CONST_qyDataType_char:
				   itemChar.cfgId  =  usCfgId;
				   itemChar.dataType  =  iDataType;
				   itemChar.ucVal  =  (  unsigned  char  )orgData;
				   pItem  =  (  QY_CFGITEM  *  )&itemChar;
				   break;
			 case  CONST_qyDataType_short:
				   itemShort.cfgId  =  usCfgId;
				   itemShort.dataType  =  iDataType;
				   itemShort.usVal  =  (  unsigned  short  )orgData;
				   pItem  =  (  QY_CFGITEM  *  )&itemShort;				   
				   break;
			 case  CONST_qyDataType_data:  {
				   QY_CFGITEM_DATA	*	pItemData		=	NULL;
				   //
				   if  (  !(  pItemData  =  (  QY_CFGITEM_DATA  *  )mallocObj.malloc(  sizeof(  QY_CFGITEM_DATA  )  )  )  )  {
					   traceLogA(  "data2Stream. malloc from QY_CFGITEM_DATA failed."  );  goto  errLabel;
				   }
				   //
				   pItemData->cfgId  =  usCfgId;
				   pItemData->dataType  =  iDataType;
				   if  (  orgDataSize  >  sizeof(  pItemData->buf  )  )  {
					   traceLogA(  "data2Stream: dataType_data: too big dataSize"  );  goto  errLabel;
				   }
				   pItemData->len  =  orgDataSize;
				   if  (  pItemData->len  !=  orgDataSize  )  {		//  2008/04/01, 
					   traceLogA(  "data2Stream: dataType_data error, buf truncated. data只能装不超过一个short长度的数据。"  );  
					   goto  errLabel;
				   }
				   memcpy(  pItemData->buf,  orgData,  pItemData->len  );
				   pItem  =  (  QY_CFGITEM  *  )pItemData;				
					}
				   break;
			 case  CONST_qyDataType_lData:  {
				   QY_CFGITEM_LDATA	*	pItemLData		=	NULL;
				   //
				   if  (  !(  pItemLData  =  (  QY_CFGITEM_LDATA  *  )mallocObj.malloc(  sizeof(  QY_CFGITEM_LDATA  )  )  )  )  {
					   traceLogA(  "data2Stream. malloc from QY_CFGITEM_LDATA failed."  );  goto  errLabel;
				   }
				   //
				   pItemLData->cfgId  =  usCfgId;
				   pItemLData->dataType  =  iDataType;
				   if  (  orgDataSize  >  sizeof(  pItemLData->buf  )  )  {
					   traceLogA(  "data2Stream: dataType_lData: too big dataSize"  );  goto  errLabel;
				   }
				   pItemLData->ulLen  =  orgDataSize;
				   memcpy(  pItemLData->buf,  orgData,  pItemLData->ulLen  );
				   pItem  =  (  QY_CFGITEM  *  )pItemLData;				
				   }
				   break;
			 case  CONST_qyDataType_l64:
				   itemL64.cfgId  =  usCfgId;
				   itemL64.dataType  =  iDataType;
				   memcpy(  itemL64.buf_l64Val,  orgData,  sizeof(  __int64  )  );
				   pItem  =  (  QY_CFGITEM  *  )&itemL64;
				   break;
			 case  CONST_qyDataType_str:  
			 case  CONST_qyDataType_utf8Str:  {
				   //
				   itemStr.cfgId  =  usCfgId;
				   itemStr.dataType  =  iDataType;
				   itemStr.len  =  min(  sizeof(  itemStr.str  ),  orgDataSize  );
				   memcpy(  itemStr.str,  orgData,  itemStr.len  );
				   pItem  =  (  QY_CFGITEM  *  )&itemStr;
					}
				   break;
			 case  CONST_qyDataType_wStr:  {
				   WCHAR  *  wStr  =  (  WCHAR  *  )orgData;
				   wStr[orgDataSize]  =  0;
				   //
				   itemStr.cfgId  =  usCfgId;
				   if  (  !myWChar2Utf8(  wStr,  itemStr.str,  sizeof(  itemStr.str  )  )  )  goto  errLabel;
				   itemStr.dataType  =  CONST_qyDataType_utf8Str;
				   itemStr.len  =  strlen(  itemStr.str  );
				   pItem  =  (  QY_CFGITEM  *  )&itemStr;
					}
				   break;
			 default:
					goto  errLabel;
					
	 }


	 if  (  !pItem  )  goto  errLabel;
	 len  =  qyhtonCfgItem(  pItem  );
	 if  (  len  <=  0  ||  size  <  len  )  {
		 traceLogA(  "getStream_wStr  error."  );  goto  errLabel;
	 }

	 memcpy(  ptr,  (  char  *  )pItem,  len  );  ptr  +=  len;  size  -=  len;

	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *pptr_usable  =  ptr;
		 *pSize_usable  =  size;
	 }
	 return  iErr;
}
#endif

 int  data2Stream(  int  iDataType,  unsigned  short  usCfgId,  void  *  orgData,  unsigned  int  orgDataSize,  char  **  pptr_usable,  unsigned  int  *  pSize_usable  )
{
	 int					iErr			=	-1;
	 QY_CFGITEM_STR			itemStr;
	 QY_CFGITEM_LONG		itemLong;
	 QY_CFGITEM_CHAR		itemChar;
	 QY_CFGITEM_SHORT		itemShort;
	 QY_CFGITEM_L64			itemL64;
	 QY_CFGITEM			*	pItem			=	NULL;
	 unsigned  int			len;
	 unsigned  int			size			=	0;
	 char				*	ptr				=	NULL;
	 CQyMalloc				mallocObj;

	 if  (  !pptr_usable  ||  !*pptr_usable  ||  !pSize_usable  )  return  -1;
	 if  (  !orgData  )  {
		 switch  (  iDataType  )  {
			     case  CONST_qyDataType_long:
				 case  CONST_qyDataType_char:
				 case  CONST_qyDataType_short:
					   break;
				 default:
					     return  -1;	//  非数值的值为地址，不能为空
		 }
	 }
	 if  (  iDataType  ==  CONST_qyDataType_l64  )  {
		 if  (  orgDataSize  &&  orgDataSize  <  sizeof(  __int64  )  )  {		//  传入0也算了，早期代码都用0。2007/12/11
			 traceLogA(  "data2Stream: l64需要传入数据地址，故建议输入数据长度应>=sizeof(  __int64  )"  );  
		 }
	 }

	 ptr  =  *pptr_usable;
	 size  =  *pSize_usable;

	 switch  (  iDataType  )  {
			 case  CONST_qyDataType_long:
				   itemLong.cfgId  =  usCfgId;
				   itemLong.dataType  =  iDataType;
				   itemLong.ulVal  =  (  unsigned  long  )orgData;
				   pItem  =  (  QY_CFGITEM  *  )&itemLong;
				   break;
			 case  CONST_qyDataType_char:
				   itemChar.cfgId  =  usCfgId;
				   itemChar.dataType  =  iDataType;
				   itemChar.ucVal  =  (  unsigned  char  )orgData;
				   pItem  =  (  QY_CFGITEM  *  )&itemChar;
				   break;
			 case  CONST_qyDataType_short:
				   itemShort.cfgId  =  usCfgId;
				   itemShort.dataType  =  iDataType;
				   itemShort.usVal  =  (  unsigned  short  )orgData;
				   pItem  =  (  QY_CFGITEM  *  )&itemShort;				   
				   break;
			 case  CONST_qyDataType_data:  {
				   QY_CFGITEM_DATA	*	pItemData		=	NULL;
				   int					tmpSize			=	offsetof(  QY_CFGITEM_DATA,  buf  )  +  orgDataSize;	//  sizeof(  QY_CFGITEM_DATA  )	//  2010/09/10
				   //
				   if  (  !(  pItemData  =  (  QY_CFGITEM_DATA  *  )mallocObj.malloc(  tmpSize  )  )  )  {
					   traceLogA(  "data2Stream. malloc from QY_CFGITEM_DATA failed."  );  goto  errLabel;
				   }
				   //
				   pItemData->cfgId  =  usCfgId;
				   pItemData->dataType  =  iDataType;
				   if  (  orgDataSize  >  sizeof(  pItemData->buf  )  )  {
					   traceLogA(  "data2Stream: dataType_data: too big dataSize"  );  goto  errLabel;
				   }
				   pItemData->len  =  orgDataSize;
				   if  (  pItemData->len  !=  orgDataSize  )  {		//  2008/04/01, 
					   traceLogA(  "data2Stream: dataType_data error, buf truncated. data只能装不超过一个short长度的数据。"  );  
					   goto  errLabel;
				   }
				   memcpy(  pItemData->buf,  orgData,  pItemData->len  );
				   pItem  =  (  QY_CFGITEM  *  )pItemData;				
					}
				   break;
			 case  CONST_qyDataType_lData:  {
				   QY_CFGITEM_LDATA	*	pItemLData		=	NULL;
				   int					tmpSize			=	offsetof(  QY_CFGITEM_LDATA,  buf  )  +  orgDataSize;	//  sizeof(  QY_CFGITEM_LDATA  )	//  2010/09/10
				   //
				   if  (  !(  pItemLData  =  (  QY_CFGITEM_LDATA  *  )mallocObj.malloc(  tmpSize  )  )  )  {
					   traceLogA(  "data2Stream. malloc from QY_CFGITEM_LDATA failed."  );  goto  errLabel;
				   }
				   //
				   pItemLData->cfgId  =  usCfgId;
				   pItemLData->dataType  =  iDataType;
				   if  (  orgDataSize  >  sizeof(  pItemLData->buf  )  )  {
					   traceLogA(  "data2Stream: dataType_lData: too big dataSize"  );  goto  errLabel;
				   }
				   pItemLData->ulLen  =  orgDataSize;
				   memcpy(  pItemLData->buf,  orgData,  pItemLData->ulLen  );
				   pItem  =  (  QY_CFGITEM  *  )pItemLData;				
				   }
				   break;
			 case  CONST_qyDataType_l64:
				   itemL64.cfgId  =  usCfgId;
				   itemL64.dataType  =  iDataType;
				   memcpy(  itemL64.buf_l64Val,  orgData,  sizeof(  __int64  )  );
				   pItem  =  (  QY_CFGITEM  *  )&itemL64;
				   break;
			 case  CONST_qyDataType_str:  
			 case  CONST_qyDataType_utf8Str:  {
				   //
				   itemStr.cfgId  =  usCfgId;
				   itemStr.dataType  =  iDataType;
				   itemStr.len  =  min(  sizeof(  itemStr.str  ),  orgDataSize  );
				   memcpy(  itemStr.str,  orgData,  itemStr.len  );
				   pItem  =  (  QY_CFGITEM  *  )&itemStr;
					}
				   break;
			 case  CONST_qyDataType_wStr:  {
				   WCHAR  *  wStr  =  (  WCHAR  *  )orgData;
				   wStr[orgDataSize]  =  0;
				   //
				   if  (  orgDataSize  <  1024  )  {
					   itemStr.cfgId  =  usCfgId;
					   if  (  !myWChar2Utf8(  wStr,  itemStr.str,  sizeof(  itemStr.str  )  )  )  goto  errLabel;
					   itemStr.dataType  =  CONST_qyDataType_utf8Str;
					   itemStr.len  =  strlen(  itemStr.str  );
					   pItem  =  (  QY_CFGITEM  *  )&itemStr;
					   }
				   else  {  //2010/12/05
		   				 QY_CFGITEM_DATA	*	pItemData		=	NULL;
						 int					tmpBufSize		=	(  orgDataSize  +  1  )  *  sizeof(  WCHAR  );
						 int					tmpSize			=	offsetof(  QY_CFGITEM_DATA,  buf  )  +  tmpBufSize;
						 //
						 if  (  tmpBufSize  >  sizeof(  pItemData->buf  )  )  {
							 traceLogA(  "data2Stream: dataType_wStr: too big dataSize"  );  goto  errLabel;				   
						 }
						 //
						 if  (  !(  pItemData  =  (  QY_CFGITEM_DATA  *  )mallocObj.malloc(  tmpSize  )  )  )  {
							 traceLogA(  "data2Stream. malloc from QY_CFGITEM_DATA failed."  );  goto  errLabel;				   
						 }
						 //
						 pItemData->cfgId  =  usCfgId;
						 if  (  !myWChar2Utf8(  wStr,  pItemData->buf,  tmpBufSize  )  )  goto  errLabel;
						 pItemData->dataType  =  CONST_qyDataType_utf8Str;
						 pItemData->len  =  strlen(  pItemData->buf  );
						 pItem  =  (  QY_CFGITEM  *  )pItemData;									     
				   }
					}
				   break;
			 default:
					goto  errLabel;
					
	 }


	 if  (  !pItem  )  goto  errLabel;
	 len  =  qyhtonCfgItem(  pItem  );
	 if  (  len  <=  0  ||  size  <  len  )  {
		 traceLogA(  "getStream_wStr  error."  );  goto  errLabel;
	 }

	 memcpy(  ptr,  (  char  *  )pItem,  len  );  ptr  +=  len;  size  -=  len;

	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *pptr_usable  =  ptr;
		 *pSize_usable  =  size;
	 }
	 return  iErr;
}


//  原始的函数
#if  0	//  2010/04/08

 int  stream2Data(  char  **  pCfgsBuf_usable,  unsigned  int  *  pSize_usable,  PF_handler_stream2Data  pf_filter,  PF_handler_stream2Data  pf,  void  *  p0,  void  *  p1  )
{
	int						iErr		=	-1;
	unsigned  int			len;
	char				*	ptr			=	0;
	QY_CFGITEM			*	pItem;
	QY_CFGITEM_WSTR			itemWStr;
	char					buf[4096];
	BOOL					bStarted	=	FALSE;
	unsigned  int			uiStreamId	=	0;
	int						tmpiRet;
	char		*			cfgsBuf		=	NULL;
	unsigned  int			size		=	0;

	if  (  !pCfgsBuf_usable  ||  !pSize_usable  )  return  -1;

	cfgsBuf  =  *pCfgsBuf_usable;
	size  =  *pSize_usable;
	//
	if  (  !cfgsBuf  ||  !size  ||  !pf_filter  ||  !pf  )  return  -1;

	len  =  0;
	ptr  =  cfgsBuf;
	for  (  ;  size;  )  {
		 pItem  =  (  QY_CFGITEM  *  )ptr;
		 len  =  qyntohCfgItem(  pItem  );		//  这里要注意：这里qyntohCfgItem(  )返回的是转换前的字节流长度。和qyhtonCfgItem(  )返回的不同
		 if  (  len  <=  0  ||  len  >  size  )  goto  errLabel;
		 if  (  bStarted  )  {
			 if  (  pItem->cfgId  ==  CONST_qnmCfgId_start  )  {
				 if  (  pItem->dataType  !=  CONST_qyDataType_long  )  goto  errLabel;
				 len  =  qyhtonCfgItem(  pItem  );
				 if  (  len  <=  0  ||  len  >  size  )  goto  errLabel;		//  注意这里：因为要调用新的stream2Data, 要把刚刚转换的数据给转换回去，因为在新的调用里是一定要转换的
				 if  (  tmpiRet  =  stream2Data(  &ptr,  &size,  pf_filter,  pf,  p0,  p1  )  )  {
					 iErr  =  tmpiRet;  goto  errLabel;
				 }		
				 continue;
			 }
		 }
	 
		 ptr  +=  len;  size  -=  len;		 

		 if  (  !bStarted  )  {
			 if  (  pItem->cfgId  !=  CONST_qnmCfgId_start  )  goto  errLabel;
			 if  (  pItem->dataType  !=  CONST_qyDataType_long  )  goto  errLabel;
			 uiStreamId  =  (  (  QY_CFGITEM_LONG  *  )pItem  )->ulVal;
			 bStarted  =  TRUE;
			 //
			 if  (  (  tmpiRet  =  pf(  p0,  p1,  uiStreamId,  pItem  )  )  )  {		//  这里有利于处理结构起始时初始化，2007/08/01
				 iErr  =  tmpiRet;  goto  errLabel;
			 }
			 continue;
		 }
	
		 if  (  pItem->cfgId  ==  CONST_qnmCfgId_null  )  {
			 //
			 if  (  (  tmpiRet  =  pf(  p0,  p1,  uiStreamId,  pItem  )  )  )  {		//  这里有利于处理结构结束时做结尾工作，2007/08/01
				 iErr  =  tmpiRet;  goto  errLabel;
			 }
			 break;
		 }
			 
		 if  (  pItem->dataType  ==  CONST_qyDataType_utf8Str  )  {
			 QY_CFGITEM_STR  *  pItemStr  =  (  QY_CFGITEM_STR  *  )pItem;
			 itemWStr.cfgId  =  pItemStr->cfgId;
			 safeStrnCpy(  pItemStr->str,  buf,  min(  pItemStr->len  +  1,  sizeof(  buf  )  )  );
			 if  (  !myUtf82WChar(  buf,  itemWStr.wStr,  mycountof(  itemWStr.wStr  )  )  )  goto  errLabel;
			 itemWStr.len  =  min(  wcslen(  itemWStr.wStr  ),  mycountof(  itemWStr.wStr  )  -  1  );
			 itemWStr.dataType  =  CONST_qyDataType_wStr;
			 pItem  =  (  QY_CFGITEM  *  )&itemWStr;
		 }
		 if  (  (  tmpiRet  =  pf_filter(  p0,  p1,  uiStreamId,  pItem  )  )  )  {		//  2008/12/03, 主要是对pItem里的数据进行过滤。不是对结果的
			 iErr  =  tmpiRet;  goto  errLabel;
		 }
		 if  (  (  tmpiRet  =  pf(  p0,  p1,  uiStreamId,  pItem  )  )  )  {
			 iErr  =  tmpiRet;  goto  errLabel;
		 }
	}
	
	 iErr  =  0;
errLabel:

	 if  (  !iErr  )  {
		 *pCfgsBuf_usable  =  ptr;
		 *pSize_usable  =  size;
	 }

	 return  iErr;
}

#endif

#if  0	//  2010/04/25

 int  stream2Data(  char  **  pCfgsBuf_usable,  unsigned  int  *  pSize_usable,  PF_handler_stream2Data  pf_filter,  PF_handler_stream2Data  pf,  void  *  p0,  void  *  p1  )
{
	int						iErr		=	-1;
	unsigned  int			len;
	char				*	ptr			=	0;
	QY_CFGITEM			*	pItem;
	QY_CFGITEM_WSTR			itemWStr;
	char					buf[4096];
	BOOL					bStarted	=	FALSE;
	unsigned  int			uiStreamId	=	0;
	int						tmpiRet;
	char		*			cfgsBuf		=	NULL;
	unsigned  int			size		=	0;
	unsigned  short			tmp_cfgId;			//  2010/04/08
	unsigned  short			tmp_dataType;		//  2010/04/08

	if  (  !pCfgsBuf_usable  ||  !pSize_usable  )  return  -1;

	cfgsBuf  =  *pCfgsBuf_usable;
	size  =  *pSize_usable;
	//
	if  (  !cfgsBuf  ||  !size  ||  !pf_filter  ||  !pf  )  return  -1;

	len  =  0;
	ptr  =  cfgsBuf;
	for  (  ;  size;  )  {
		 pItem  =  (  QY_CFGITEM  *  )ptr;
		 len  =  qyntohCfgItem(  pItem  );		//  这里要注意：这里qyntohCfgItem(  )返回的是转换前的字节流长度。和qyhtonCfgItem(  )返回的不同
		 if  (  len  <=  0  ||  len  >  size  )  goto  errLabel;

		 memcpy(  &tmp_cfgId,  &pItem->cfgId,  sizeof(  short  )  );			//  2010/04/08
		 memcpy(  &tmp_dataType,  &pItem->dataType,  sizeof(  short  )  );		//  2010/04/08

		 if  (  bStarted  )  {
			 if  (  tmp_cfgId  ==  CONST_qnmCfgId_start  )  {
				 if  (  tmp_dataType  !=  CONST_qyDataType_long  )  goto  errLabel;
				 
				#if  0
					len  =  qyhtonCfgItem(  pItem  );				
					if  (  len  <=  0  ||  len  >  size  )  goto  errLabel;		//  注意这里：因为要调用新的stream2Data, 要把刚刚转换的数据给转换回去，因为在新的调用里是一定要转换的
				#else
				    unsigned  long  tmp_uiStreamId;

					memcpy(  &tmp_uiStreamId,  &(  (  (  QY_CFGITEM_LONG  *  )pItem  )->ulVal  ),  sizeof(  tmp_uiStreamId  )  );

					MACRO_htons(  tmp_cfgId  );	memcpy(  &pItem->cfgId,  &tmp_cfgId,  sizeof(  short  )  );
					MACRO_htons(  tmp_dataType  );	memcpy(  &pItem->dataType,  &tmp_dataType,  sizeof(  short  )  );
					MACRO_htonl(  tmp_uiStreamId  );  memcpy(  &(  (  (  QY_CFGITEM_LONG  *  )pItem  )->ulVal  ),  &tmp_uiStreamId,  sizeof(  long  )  );
				#endif

				 if  (  tmpiRet  =  stream2Data(  &ptr,  &size,  pf_filter,  pf,  p0,  p1  )  )  {
					 iErr  =  tmpiRet;  goto  errLabel;
				 }		
				 continue;
			 }
		 }
	 
		 ptr  +=  len;  size  -=  len;		 

		 if  (  !bStarted  )  {
			 if  (  tmp_cfgId  !=  CONST_qnmCfgId_start  )  goto  errLabel;
			 if  (  tmp_dataType  !=  CONST_qyDataType_long  )  goto  errLabel;
			 //  uiStreamId  =  (  (  QY_CFGITEM_LONG  *  )pItem  )->ulVal;
			 memcpy(  &uiStreamId,  &(  (  QY_CFGITEM_LONG  *  )pItem  )->ulVal,  sizeof(  uiStreamId  )  );
			 bStarted  =  TRUE;
			 //
			 if  (  (  tmpiRet  =  pf(  p0,  p1,  uiStreamId,  pItem  )  )  )  {		//  这里有利于处理结构起始时初始化，2007/08/01
				 iErr  =  tmpiRet;  goto  errLabel;
			 }
			 continue;
		 }
	
		 if  (  tmp_cfgId  ==  CONST_qnmCfgId_null  )  {
			 //
			 if  (  (  tmpiRet  =  pf(  p0,  p1,  uiStreamId,  pItem  )  )  )  {		//  这里有利于处理结构结束时做结尾工作，2007/08/01
				 iErr  =  tmpiRet;  goto  errLabel;
			 }
			 break;
		 }
			 
		 if  (  tmp_dataType  ==  CONST_qyDataType_utf8Str  )  {
			 QY_CFGITEM_STR  *  pItemStr  =  (  QY_CFGITEM_STR  *  )pItem;
			 unsigned  short  tmp_len;
			 memcpy(  &tmp_len,  &pItemStr->len,  sizeof(  short  )  );

			 itemWStr.cfgId  =  tmp_cfgId;
			 safeStrnCpy(  pItemStr->str,  buf,  min(  tmp_len  +  1,  sizeof(  buf  )  )  );
			 if  (  !myUtf82WChar(  buf,  itemWStr.wStr,  mycountof(  itemWStr.wStr  )  )  )  goto  errLabel;
			 itemWStr.len  =  min(  wcslen(  itemWStr.wStr  ),  mycountof(  itemWStr.wStr  )  -  1  );
			 itemWStr.dataType  =  CONST_qyDataType_wStr;
			 pItem  =  (  QY_CFGITEM  *  )&itemWStr;
		 }
		 if  (  (  tmpiRet  =  pf_filter(  p0,  p1,  uiStreamId,  pItem  )  )  )  {		//  2008/12/03, 主要是对pItem里的数据进行过滤。不是对结果的
			 iErr  =  tmpiRet;  goto  errLabel;
		 }
		 if  (  (  tmpiRet  =  pf(  p0,  p1,  uiStreamId,  pItem  )  )  )  {
			 iErr  =  tmpiRet;  goto  errLabel;
		 }
	}
	
	 iErr  =  0;
errLabel:

	 if  (  !iErr  )  {
		 *pCfgsBuf_usable  =  ptr;
		 *pSize_usable  =  size;
	 }

	 return  iErr;
}

#endif

 int  stream2Data(  char  **  pCfgsBuf_usable,  unsigned  int  *  pSize_usable,  PF_handler_stream2Data  pf_filter,  PF_handler_stream2Data  pf,  void  *  p0,  void  *  p1  )
{
	int						iErr			=	-1;
	unsigned  int			len;
	char				*	ptr				=	0;
	QY_CFGITEM_ntoh_U		item_ntoh_U;
	QY_CFGITEM_ntoh_U	*	pItem			=	NULL;
	//  QY_CFGITEM_WSTR			itemWStr;
	CQyString				wStr;
	int						nStarts			=	0;
	unsigned  int			uiStreamIds[5]	=	{	0,	};
	int						tmpiRet;
	char		*			cfgsBuf			=	NULL;
	unsigned  int			size			=	0;
	unsigned  short			tmp_cfgId;			//  2010/04/08
	unsigned  short			tmp_dataType;		//  2010/04/08

	if  (  !pCfgsBuf_usable  ||  !pSize_usable  )  return  -1;

	cfgsBuf  =  *pCfgsBuf_usable;
	size  =  *pSize_usable;
	//
	if  (  !cfgsBuf  ||  !size  ||  !pf_filter  ||  !pf  )  return  -1;

	len  =  0;
	ptr  =  cfgsBuf;
	for  (  ;  size;  )  {
#if  0
		 pItem  =  (  QY_CFGITEM  *  )ptr;
		 len  =  qyntohCfgItem(  pItem  );		//  这里要注意：这里qyntohCfgItem(  )返回的是转换前的字节流长度。和qyhtonCfgItem(  )返回的不同
#endif
		 len			=  qyntohCfgItem(  ptr,  &item_ntoh_U  );		//  这里要注意：这里qyntohCfgItem(  )返回的是转换前的字节流长度。和qyhtonCfgItem(  )返回的不同
		 pItem			=	&item_ntoh_U;

		 if  (  len  <=  0  ||  len  >  size  )  goto  errLabel;

		 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );			//  2010/04/08
		 memcpy(  &tmp_dataType,  &pItem->head.dataType,  sizeof(  short  )  );		//  2010/04/08
	 
		 ptr  +=  len;  size  -=  len;		 

		 if  (  !nStarts  )  {
			 if  (  tmp_cfgId  !=  CONST_qnmCfgId_start  )  goto  errLabel;
			 if  (  tmp_dataType  !=  CONST_qyDataType_long  )  goto  errLabel;
		 }

		 if  (  tmp_cfgId  ==  CONST_qnmCfgId_start  )  {

			 nStarts  ++  ;
			 if  (  nStarts  >  mycountof(  uiStreamIds  )  )  goto  errLabel;

			 //  uiStreamId  =  (  (  QY_CFGITEM_LONG  *  )pItem  )->ulVal;
			 memcpy(  &uiStreamIds[nStarts  -  1],  &(  (  QY_CFGITEM_LONG  *  )pItem  )->ulVal,  sizeof(  uiStreamIds[0]  )  );
			 //
			 if  (  (  tmpiRet  =  pf(  p0,  p1,  uiStreamIds[nStarts  -  1],  pItem  )  )  )  {		//  这里有利于处理结构起始时初始化，2007/08/01
				 iErr  =  tmpiRet;  goto  errLabel;
			 }
			 continue;
		 }
	
		 if  (  tmp_cfgId  ==  CONST_qnmCfgId_null  )  {
			 //
			 if  (  (  tmpiRet  =  pf(  p0,  p1,  uiStreamIds[nStarts  -  1],  pItem  )  )  )  {		//  这里有利于处理结构结束时做结尾工作，2007/08/01
				 iErr  =  tmpiRet;  goto  errLabel;
			 }
			 nStarts  --  ;
			 if  (  !nStarts  )  break;
			 continue;
		 }
			 
		 if  (  tmp_dataType  ==  CONST_qyDataType_utf8Str  )  {

//  #define		CONST_bufSize_utf8Str		4096
#define		CONST_bufSize_utf8Str		32  *  1024		//  2010/12/05

			 CQyMalloc				mallocObj_buf;
			 int					bufSize		=  CONST_bufSize_utf8Str;
			 char				*	pBuf		=	NULL;

			 if  (  pItem->data.len  +  1  >  CONST_bufSize_utf8Str  )  {
				 traceLog(  _T(  "stream2Data: utf8 too long string"  )  );
				 goto  errLabel;
			 }
			 bufSize  =  pItem->data.len  +  1;
			 pBuf  =  mallocObj_buf.malloc(  bufSize  );
			 if  (  !pBuf  )  goto  errLabel;

			 //
#if  0
			 QY_CFGITEM_STR  *  pItemStr  =  (  QY_CFGITEM_STR  *  )pItem;
			 unsigned  short  tmp_len;
			 memcpy(  &tmp_len,  &pItemStr->len,  sizeof(  short  )  );

			 itemWStr.cfgId  =  tmp_cfgId;
			 safeStrnCpy(  pItemStr->str,  pBuf,  min(  tmp_len  +  1,  bufSize  )  );
			 if  (  !myUtf82WChar(  pBuf,  itemWStr.wStr,  mycountof(  itemWStr.wStr  )  )  )  goto  errLabel;
			 itemWStr.len  =  min(  wcslen(  itemWStr.wStr  ),  mycountof(  itemWStr.wStr  )  -  1  );
			 itemWStr.dataType  =  CONST_qyDataType_wStr;
			 pItem  =  (  QY_CFGITEM  *  )&itemWStr;
#endif
			 safeStrnCpy(  pItem->data.p,  pBuf,  min(  pItem->data.len  +  1,  bufSize  )  );
			 wStr  =  CQyString(  pBuf  );
			 pItem->wStr.dataType  =  CONST_qyDataType_wStr;
			 pItem->wStr.len  =  wStr.GetLength(  );
			 pItem->wStr.pWStr  =  (  WCHAR  *  )wStr.GetBuffer(  0  );
		 }
		 if  (  (  tmpiRet  =  pf_filter(  p0,  p1,  uiStreamIds[nStarts  -  1],  pItem  )  )  )  {		//  2008/12/03, 主要是对pItem里的数据进行过滤。不是对结果的
			 iErr  =  tmpiRet;  goto  errLabel;
		 }
		 if  (  (  tmpiRet  =  pf(  p0,  p1,  uiStreamIds[nStarts  -  1],  pItem  )  )  )  {
			 iErr  =  tmpiRet;  goto  errLabel;
		 }
	}
	
	 iErr  =  0;
errLabel:

	 if  (  !iErr  )  {
		 *pCfgsBuf_usable  =  ptr;
		 *pSize_usable  =  size;
	 }

	 return  iErr;
}


#if  0
 extern  "C"  int  getFieldData_long(  QY_CFGITEM  *  pItem,  long  *  plVal  )
{
	 if  (  !pItem  ||  !plVal  )  return  -1;
	 if  (  pItem->dataType  !=  CONST_qyDataType_long  )  return  -1;
	 
	 *plVal  =  (  (  QY_CFGITEM_LONG  *  )pItem  )->ulVal;

	 return  0;

}
#else
 extern  "C"  int  getFieldData_long(  QY_CFGITEM_ntoh_U  *  pItem,  long  *  plVal  )
{
	 if  (  !pItem  ||  !plVal  )  return  -1;

	 unsigned  short	tmp_dataType;
	 memcpy(  &tmp_dataType,  &pItem->head.dataType,  sizeof(  tmp_dataType  )  );

	 if  (  tmp_dataType  !=  CONST_qyDataType_long  )  return  -1;
	 
	 //  *plVal  =  (  (  QY_CFGITEM_LONG  *  )pItem  )->ulVal;
	 memcpy(  plVal,  &(  (  QY_CFGITEM_LONG  *  )pItem  )->ulVal,  sizeof(  long  )  );

	 return  0;
}
#endif

#if  0
 extern  "C"  int  getFieldData_short(  QY_CFGITEM  *  pItem,  short  *  psVal  )
{
	 if  (  !pItem  ||  !psVal  )  return  -1;
	 if  (  pItem->dataType  !=  CONST_qyDataType_short  )  return  -1;
	 
	 *psVal  =  (  (  QY_CFGITEM_SHORT  *  )pItem  )->usVal;

	 return  0;

}
#else
 extern  "C"  int  getFieldData_short(  QY_CFGITEM_ntoh_U  *  pItem,  short  *  psVal  )
{
	 if  (  !pItem  ||  !psVal  )  return  -1;

	 unsigned  short	tmp_dataType;
	 memcpy(  &tmp_dataType,  &pItem->head.dataType,  sizeof(  tmp_dataType  )  );

	 if  (  tmp_dataType  !=  CONST_qyDataType_short  )  return  -1;
	 
	 //  *psVal  =  (  (  QY_CFGITEM_SHORT  *  )pItem  )->usVal;
	 memcpy(  psVal,  &(  (  QY_CFGITEM_SHORT  *  )pItem  )->usVal,  sizeof(  short  )  );

	 return  0;

}
#endif

#if  0
 extern  "C"  int  getFieldData_char(  QY_CFGITEM  *  pItem,  char  *  pcVal  )
{
	 if  (  !pItem  ||  !pcVal  )  return  -1;
	 if  (  pItem->dataType  !=  CONST_qyDataType_char  )  return  -1;
	 
	 *pcVal  =  (  (  QY_CFGITEM_CHAR  *  )pItem  )->ucVal;

	 return  0;

}
#else
 extern  "C"  int  getFieldData_char(  QY_CFGITEM_ntoh_U  *  pItem,  char  *  pcVal  )
{
	 if  (  !pItem  ||  !pcVal  )  return  -1;

	 unsigned  short	tmp_dataType;
	 memcpy(  &tmp_dataType,  &pItem->head.dataType,  sizeof(  tmp_dataType  )  );
	 if  (  tmp_dataType  !=  CONST_qyDataType_char  )  return  -1;
	 
	 *pcVal  =  (  (  QY_CFGITEM_CHAR  *  )pItem  )->ucVal;

	 return  0;

}
#endif


#if  0
 extern  "C"  int  getFieldData_l64(  QY_CFGITEM  *  pItem,  __int64  *  pl64Val  )
{
	 if  (  !pItem  ||  !pl64Val  )  return  -1;
	 if  (  pItem->dataType  !=  CONST_qyDataType_l64  )  return  -1;
	 
	 //  *pl64Val  =  *(  __int64  *  )(  (  QY_CFGITEM_L64  *  )pItem  )->buf_l64Val;
	 memcpy(  pl64Val,  (  (  QY_CFGITEM_L64  *  )pItem  )->buf_l64Val,  sizeof(  __int64  )  );	//  2010/04/08

	 return  0;

}
#else
 extern  "C"  int  getFieldData_l64(  QY_CFGITEM_ntoh_U  *  pItem,  __int64  *  pl64Val  )
{
	 if  (  !pItem  ||  !pl64Val  )  return  -1;

	 unsigned  short  tmp_dataType;
	 memcpy(  &tmp_dataType,  &pItem->head.dataType,  sizeof(  short  )  );
	 if  (  tmp_dataType  !=  CONST_qyDataType_l64  )  return  -1;
	 
	 //  *pl64Val  =  *(  __int64  *  )(  (  QY_CFGITEM_L64  *  )pItem  )->buf_l64Val;
	 memcpy(  pl64Val,  (  (  QY_CFGITEM_L64  *  )pItem  )->buf_l64Val,  sizeof(  __int64  )  );	//  2010/04/08

	 return  0;

}
#endif

#if  0
 extern  "C"  int  getFieldData_data(  QY_CFGITEM  *  pItem,  char  *  val,  unsigned  int  *  pSize  )
{
	 if  (  !pSize  )  return  -1;
	 if  (  pItem->dataType  !=  CONST_qyDataType_data  )  return  -1;

	 QY_CFGITEM_DATA *	pItemData	=	(  QY_CFGITEM_DATA  *  )pItem;
	 
	 if  (  pItemData->len  >  *pSize  )  return  -1;			//  2008/03/23

	 memcpy(  val,  pItemData->buf,  pItemData->len  );
	 *pSize  =  pItemData->len;

	 return  0;
}
#else
 extern  "C"  int  getFieldData_data(  QY_CFGITEM_ntoh_U  *  pItem,  char  *  val,  unsigned  int  *  pSize  )
{
	 if  (  !pSize  )  return  -1;

	 unsigned  short  tmp_dataType;
	 memcpy(  &tmp_dataType,  &pItem->head.dataType,  sizeof(  short  )  );
	 if  (  tmp_dataType  !=  CONST_qyDataType_data  )  return  -1;

	 //  QY_CFGITEM_DATA *	pItemData	=	(  QY_CFGITEM_DATA  *  )pItem;

	 unsigned  short  tmp_len;
	 memcpy(  &tmp_len,  &pItem->data.len,  sizeof(  short  )  );
	 if  (  tmp_len  >  *pSize  )  return  -1;			//  2008/03/23

	 memcpy(  val,  pItem->data.p,  tmp_len  );
	 //	*pSize  =  pItemData->len;
	 *pSize  =  tmp_len;

	 return  0;
}
#endif

#if  0
 extern  "C"  int  getFieldData_lData(  QY_CFGITEM  *  pItem,  char  *  val,  unsigned  int  *  pSize  )
{
	 if  (  !pSize  )  return  -1;
	 if  (  pItem->dataType  !=  CONST_qyDataType_lData  )  return  -1;

	 QY_CFGITEM_LDATA *	pItemData	=	(  QY_CFGITEM_LDATA  *  )pItem;
	 
	 if  (  pItemData->ulLen  >  *pSize  )  return  -1;			//  2008/03/23

	 memcpy(  val,  pItemData->buf,  pItemData->ulLen  );
	 *pSize  =  pItemData->ulLen;

	 return  0;
}
#else
 extern  "C"  int  getFieldData_lData(  QY_CFGITEM_ntoh_U  *  pItem,  char  *  val,  unsigned  int  *  pSize  )
{
	 if  (  !pSize  )  return  -1;

	 unsigned  short  tmp_dataType;
	 memcpy(  &tmp_dataType,  &pItem->head.dataType,  sizeof(  short  )  );
	 if  (  tmp_dataType  !=  CONST_qyDataType_lData  )  return  -1;

	 //  QY_CFGITEM_LDATA *	pItemData	=	(  QY_CFGITEM_LDATA  *  )pItem;
	 
	 unsigned  long  tmp_ulLen;
	 memcpy(  &tmp_ulLen,  &pItem->lData.ulLen,  sizeof(  long  )  );	 
	 if  (  tmp_ulLen  >  *pSize  )  return  -1;			//  2008/03/23

	 memcpy(  val,  pItem->lData.p,  tmp_ulLen  );
	 *pSize  =  tmp_ulLen;

	 return  0;
}
#endif  

#if  0
 extern  "C"  int  getFieldData_str(  QY_CFGITEM  *  pItem,  char  *  val,  unsigned  int  size  )
{
	 if  (  pItem->dataType  !=  CONST_qyDataType_str  )  return  -1;
	 QY_CFGITEM_STR	*	pItemStr	=	(  QY_CFGITEM_STR  *  )pItem;
	 
	 safeStrnCpy(  pItemStr->str,  val,  min(  (  unsigned  int  )(  pItemStr->len  +  1  ),  size  )  );

	 return  0;
}
#else 
 extern  "C"  int  getFieldData_str(  QY_CFGITEM_ntoh_U  *  pItem,  char  *  val,  unsigned  int  size  )
{
	 unsigned short  tmp_dataType;
	 memcpy(  &tmp_dataType,  &pItem->head.dataType,  sizeof(  short  )  );
	 if  (  tmp_dataType  !=  CONST_qyDataType_str  )  return  -1;

	 //  QY_CFGITEM_STR	*	pItemStr	=	(  QY_CFGITEM_STR  *  )pItem;

	 unsigned short  tmp_len;
	 memcpy(  &tmp_len,  &pItem->data.len,  sizeof(  short  )  );
	 safeStrnCpy(  pItem->data.p,  val,  min(  (  unsigned  int  )(  tmp_len  +  1  ),  size  )  );

	 return  0;
}
#endif

#if  0
 extern  "C"  int  getFieldData_wStr(  QY_CFGITEM  *  pItem,  WCHAR  *  val,  unsigned  int  size  )
{
	 if  (  pItem->dataType  !=  CONST_qyDataType_wStr  )  return  -1;
	 QY_CFGITEM_WSTR  *  pItemWStr  =  (  QY_CFGITEM_WSTR  *  )pItem;
	 
	 safeWcsnCpy(  pItemWStr->wStr,  val,  min(  (  unsigned  int  )(  pItemWStr->len  +  1  ),  size  )  );
	 return  0;
}
#else
 extern  "C"  int  getFieldData_wStr(  QY_CFGITEM_ntoh_U  *  pItem,  WCHAR  *  val,  unsigned  int  size  )
{
	 unsigned  short  tmp_dataType;
	 memcpy(  &tmp_dataType,  &pItem->head.dataType,  sizeof(  short  )  );
	 if  (  tmp_dataType  !=  CONST_qyDataType_wStr  )  return  -1;

	 //  QY_CFGITEM_WSTR  *  pItemWStr  =  (  QY_CFGITEM_WSTR  *  )pItem;
	 
	 unsigned  short  tmp_len;
	 memcpy(  &tmp_len,  &pItem->wStr.len,  sizeof(  short  )  );
	 safeWcsnCpy(  pItem->wStr.pWStr,  val,  min(  (  unsigned  int  )(  tmp_len  +  1  ),  size  )  );
	 return  0;
}
#endif


 /////////////

 

 QY_MESSENGER_ID  *  idStr2Info(  char  *  idStr,  QY_MESSENGER_ID  *  pIdInfo  )
{
	 int	iErr	=	-1;

	 if  (  !idStr  ||  !pIdInfo  )  return  NULL;

	 pIdInfo->ui64Id  =  (  unsigned  __int64  )atof(  idStr  );	//  2007/04/03, 这里暂时只取低位的数。
	 return  pIdInfo;
}

 char  *  idInfo2Str(  QY_MESSENGER_ID  *  pIdInfo,  char  *  idStr,  unsigned  int  size  )
{
	 if  (    !pIdInfo  ||!idStr  ||  size  <=  CONST_qyMessengerIdStrLen  )  return  NULL;
	 _snprintf(  idStr,  size,  "%018I64u",  pIdInfo->ui64Id  );
	 return  idStr;
}

 //  网络上的idInfo不能是0的。但是，在手机外设发短信到本机上时，可能用的是0。然后用uiObjType来识别。
 BOOL  bMessengerIdValid(  QY_MESSENGER_ID  *  pIdInfo  )
{
	//  if  (  pIdInfo  &&  pIdInfo->ui64Id  &&  pIdInfo->ui64Id  !=  CONST_invalidMessengerId  )  return  TRUE;
	if  (  pIdInfo  &&  pIdInfo->ui64Id  !=  CONST_invalidMessengerId  )  return  TRUE;
	return  FALSE;
}

 BOOL  bMessengerIdStrValid(  char  *  idStr  )
{
	 if  (  !idStr  ||  strlen(  idStr  )  !=  CONST_qyMessengerIdStrLen  )  return  FALSE;
	 for  (  int  i  =  0;  i  <  CONST_qyMessengerIdStrLen;  i  ++  )  {
		  if  (  !isdigit(  idStr[i]  )  )  return  FALSE;
	 }
	 return  TRUE;
}


 ////
 BOOL  bMessengerGuest(  unsigned  int  uiObjType  )
{
	switch  (  uiObjType  )  {
		    case  CONST_objType_webGuest:
			case  CONST_objType_phoneGuest:
			case  CONST_objType_newDevGuest:
				  return  TRUE;
			default:
					break;
	}
	return  FALSE;
}


 ///////////


 /////////////////////
//
//  2008/12/03, 为通信加一个过滤规则。

#define		CONST_filterChars	"'"

 int  filterStream_is(  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	int							iErr		=	-1;
	//  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	unsigned  short				tmp_len;

	unsigned  short	tmp_dataType;
	memcpy(  &tmp_dataType,  &pItem->head.dataType,  sizeof(  tmp_dataType  )  );
	
	switch  (  tmp_dataType  )  {
			case  CONST_qyDataType_str:
			case  CONST_qyDataType_utf8Str:
				  memcpy(  &tmp_len,  &(  (  QY_CFGITEM_STR  *  )pItem  )->len,  sizeof(  tmp_len  )  );
				  fwFilterBuf(  CONST_filterChars,  pItem->data.p,  tmp_len  );
				  break;
			case  CONST_qyDataType_wStr:
				  switch  (  uiStreamId  )  {
						  case  CONST_imCommType_htmlContent:	
							    switch  (  pItem->head.cfgId  )  {
										case  CONST_qnmCfgId_hint:
											  iErr  =  0;  goto  errLabel;
											  break;
										default:
												break;
								}
							    break;
						  default:
								 break;
				  }
				  memcpy(  &tmp_len,  &(  (  QY_CFGITEM_WSTR  *  )pItem  )->len,  sizeof(  tmp_len  )  );
				  fwFilterTBuf(  _T(  CONST_filterChars  ),  pItem->wStr.pWStr,  tmp_len  );
				  break;
			default:
					break;
	}

	iErr  =  0;
errLabel:
	return  iErr;
}

/////////////////////////

  

 int  commAuthInfo2Stream_mis(  QY_COMM_AUTHINFO_MIS  *  pAuthInfo,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pAuthInfo  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )CONST_imCommType_auth,  0,  &ptr,  &len  )  )  goto  errLabel;
	 if  (  pAuthInfo->ver[0]  &&  data2Stream(  CONST_qyDataType_str,  CONST_qnmCfgId_clientVer,  pAuthInfo->ver,  strlen(  pAuthInfo->ver  ),  &ptr,  &len  )  )  goto  errLabel;
	 if  (  pAuthInfo->ucCmd  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_authCmd,  (  void  *  )pAuthInfo->ucCmd,  0,  &ptr,  &len  )  )  goto  errLabel;
#if  0
	 if  (  pAuthInfo->uiObjType  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiObjType,  (  void  *  )pAuthInfo->uiObjType,  0,  &ptr,  &len  )  )  goto  errLabel;
#endif
	 if  (  pAuthInfo->iAppType  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_iAppType,  (  void  *  )pAuthInfo->iAppType,  0,  &ptr,  &len  )  )  goto  errLabel;		//  2011/03/27
	 if  (  pAuthInfo->iCustemId  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_iCustemId,  (  void  *  )pAuthInfo->iCustemId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 if  (  pAuthInfo->uiChannelType  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiChannelType,  (  void  *  )pAuthInfo->uiChannelType,  0,  &ptr,  &len  )  )  goto  errLabel;	//  2007/07/08

	 //
	 if  (  pAuthInfo->usLangId  &&  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_langId,  (  void  *  )pAuthInfo->usLangId,  0,  &ptr,  &len  )  )  goto  errLabel;	//  2007/07/08
	 if  (  pAuthInfo->uiDevType  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiDevType_from,  (  void  *  )pAuthInfo->uiDevType,  0,  &ptr,  &len  )  )  goto  errLabel;	//  2007/07/08

	 //
	 if  (  pAuthInfo->usAuthType  &&  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usAuthType,  (  void  *  )pAuthInfo->usAuthType,  0,  &ptr,  &len  )  )  goto  errLabel;	//  2011/03/22

	 //
	 for  (  i  =  0;  i  <  mycountof(  pAuthInfo->macsInfo.macs  );  i  ++  )  {
		  if  (  bMacValid(  (  char  *  )pAuthInfo->macsInfo.macs[i]  )  &&  data2Stream(  CONST_qyDataType_str,  CONST_qnmCfgId_mac,  pAuthInfo->macsInfo.macs[i],  sizeof(  pAuthInfo->macsInfo.macs[i]  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  bIpValid(  pAuthInfo->ip  )  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_ulIp,  (  void  *  )inet_addr(  pAuthInfo->ip  ),  0,  &ptr,  &len  )  )  goto  errLabel;
	 if  (  pAuthInfo->pcName[0]  &&  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_pcName,  pAuthInfo->pcName,  wcslen(  pAuthInfo->pcName  ),  &ptr,  &len  )  )  goto  errLabel;
	 if  (  pAuthInfo->domainName[0]  &&  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_domainName,  pAuthInfo->domainName,  wcslen(  pAuthInfo->domainName  ),  &ptr,  &len  )  )  goto  errLabel;
	 if  (  pAuthInfo->osUsrName[0]  &&  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_osUsrName,  pAuthInfo->osUsrName,  wcslen(  pAuthInfo->osUsrName  ),  &ptr,  &len  )  )  goto  errLabel;
	 
#if  0
	 //  2011/08/15
	 if  (  pAuthInfo->usAppAvLevel  &&  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usAppAvLevel,  (  void  *  )pAuthInfo->usAppAvLevel,  0,  &ptr,  &len  )  )  goto  errLabel;
#endif

	 //
	 if  (  pAuthInfo->messengerName[0]  &&  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_messengerName,  pAuthInfo->messengerName,  wcslen(  pAuthInfo->messengerName  ),  &ptr,  &len  )  )  goto  errLabel;
	 if  (  pAuthInfo->messengerPasswd[0]  &&  data2Stream(  CONST_qyDataType_str,  CONST_qnmCfgId_messengerPasswd,  pAuthInfo->messengerPasswd,  strlen(  pAuthInfo->messengerPasswd  ),  &ptr,  &len  )  )  goto  errLabel;

	 //
	 if  (  pAuthInfo->wRndName_serv[0]  &&  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_wRndName_serv,  (  void  *  )pAuthInfo->wRndName_serv,  wcslen(  pAuthInfo->wRndName_serv  ),  &ptr,  &len  )  )  goto  errLabel;  //  2007/11/22
	 if  (  pAuthInfo->uiRnd_cli  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiRnd_cli,  (  void  *  )pAuthInfo->uiRnd_cli,  0,  &ptr,  &len  )  )  goto  errLabel;  //  2007/11/22
	 //  if  (  pAuthInfo->uiWebSessId  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiWebSessId,  (  void  *  )pAuthInfo->uiWebSessId,  0,  &ptr,  &len  )  )  goto  errLabel;  //  2007/11/22
	 if  (  pAuthInfo->uiLogonId  &&  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiLogonId,  (  void  *  )pAuthInfo->uiLogonId,  0,  &ptr,  &len  )  )  goto  errLabel;  //  2007/11/22

	 //  2008/06/10
	 if  (  pAuthInfo->uiBlobLen_sessionKey  )  {
		 if  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_sessionKeyBlob,  pAuthInfo->sessionKeyBlob,  pAuthInfo->uiBlobLen_sessionKey,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 
}


 int  tmpHandler_stream2CommAuthInfo_mis(  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 QY_COMM_AUTHINFO_MIS  *	pAuthInfo	=	(  QY_COMM_AUTHINFO_MIS  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 long						lVal;

	 if  (  uiStreamId  !=  CONST_imCommType_auth  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );
	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_start:	//  2007/12/11
				   break;
			 case  CONST_qnmCfgId_null:		//  2007/12/11
				   break;
			 case  CONST_qnmCfgId_clientVer:
				   getFieldData_str(  pItem,  pAuthInfo->ver,  mycountof(  pAuthInfo->ver  )  );
				   break;
			 case  CONST_qnmCfgId_authCmd:
				   if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
				   pAuthInfo->ucCmd  =  (  unsigned  char  )lVal;
				   break;
#if  0
			 case  CONST_qnmCfgId_uiObjType:
				   if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
				   pAuthInfo->uiObjType  =  lVal;
				   break;
#endif
			 case  CONST_qnmCfgId_iAppType:							//  2011/03/27
				   if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
				   pAuthInfo->iAppType  =  lVal;
				   break;
			 case  CONST_qnmCfgId_iCustemId:
				   if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
				   pAuthInfo->iCustemId  =  lVal;
				   break;
			 case  CONST_qnmCfgId_uiChannelType:	//  2007/07/08
				   if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
				   pAuthInfo->uiChannelType  =  lVal;
				   break;
			 case  CONST_qnmCfgId_langId:
				   unsigned  short  tmp_dataType;
				   memcpy(  &tmp_dataType,  &pItem->head.dataType,  sizeof(  short  )  );
				   if  (  tmp_dataType  ==  CONST_qyDataType_long  )  {
					   if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
					   pAuthInfo->usLangId  =  (  unsigned  short  )lVal;				 
					   }
				   else  if  (  tmp_dataType  ==  CONST_qyDataType_short  )  {			//  2007/12/07, 允许usLangId以long或者short的形式发送.
					         if  (  getFieldData_short(  pItem,  (  short  *  )&pAuthInfo->usLangId  )  )  goto  errLabel;
							 }
				   else  {
					     traceLogA(  "CONST_qnmCfgId_usLangId的传输类型不对。"  );  goto  errLabel;					
				   }
				   break;
			 case  CONST_qnmCfgId_uiDevType_from:
  				   if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
				   pAuthInfo->uiDevType  =  lVal;				 
				   break;
			 case  CONST_qnmCfgId_usAuthType:			//  2011/03/22
				   short  sVal;
				   if  (  getFieldData_short(  pItem,  &sVal  )  )  goto  errLabel;
				   pAuthInfo->usAuthType  =  sVal;
				   break;
			 case  CONST_qnmCfgId_mac:
				   if  (  pAuthInfo->macsInfo.nMacs  >=  mycountof(  pAuthInfo->macsInfo.macs  )  )  {
					   traceLogA(  "too many macs"  );  goto  errLabel;
				   }				   
				   getFieldData_str(  pItem,  (  char  *  )pAuthInfo->macsInfo.macs[pAuthInfo->macsInfo.nMacs],  sizeof(  pAuthInfo->macsInfo.macs[pAuthInfo->macsInfo.nMacs]  )  );
				   pAuthInfo->macsInfo.nMacs  ++  ;
				   break;
			 case  CONST_qnmCfgId_ulIp:  
				   if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
				   ulIp2Str(  lVal,  pAuthInfo->ip,  mycountof(  pAuthInfo->ip  )  );				   
				   break;
			 case  CONST_qnmCfgId_pcName:
				   getFieldData_wStr(  pItem,  pAuthInfo->pcName,  mycountof(  pAuthInfo->pcName  )  );
				   break;
			 case  CONST_qnmCfgId_domainName:
				   getFieldData_wStr(  pItem,  pAuthInfo->domainName,  mycountof(  pAuthInfo->domainName  )  );
				   break;
			 case  CONST_qnmCfgId_osUsrName:
				   getFieldData_wStr(  pItem,  pAuthInfo->osUsrName,  mycountof(  pAuthInfo->osUsrName  )  );
				   break;
#if  0
			 case  CONST_qnmCfgId_usAppAvLevel:		//  2011/08/15
				   getFieldData_short(  pItem,  (  short  *  )&pAuthInfo->usAppAvLevel  );
				   break;
#endif
			 case  CONST_qnmCfgId_messengerName:
				   getFieldData_wStr(  pItem,  pAuthInfo->messengerName,  mycountof(  pAuthInfo->messengerName  )  );
				   break;
			 case  CONST_qnmCfgId_messengerPasswd:	//  2010/01/02
				   getFieldData_str(  pItem,  pAuthInfo->messengerPasswd,  mycountof(  pAuthInfo->messengerPasswd  )  );
				   break;
			 case  CONST_qnmCfgId_wRndName_serv:
				   getFieldData_wStr(  pItem,  pAuthInfo->wRndName_serv,  mycountof(  pAuthInfo->wRndName_serv  )  );
				   break;
			 case  CONST_qnmCfgId_uiRnd_cli:	//  2007/11/22
				   if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
				   pAuthInfo->uiRnd_cli  =  lVal;
				   break;
			 case  CONST_qnmCfgId_uiLogonId:	//  2007/11/22
				   if  (  getFieldData_long(  pItem,  &lVal  )  )  goto  errLabel;
				   pAuthInfo->uiLogonId  =  lVal;
				   break;
			 case  CONST_qnmCfgId_sessionKeyBlob:
				   pAuthInfo->uiBlobLen_sessionKey  =  mycountof(  pAuthInfo->sessionKeyBlob  );
				   if  (  getFieldData_data(  pItem,  pAuthInfo->sessionKeyBlob,  &pAuthInfo->uiBlobLen_sessionKey  )  )  goto  errLabel;
				   break;
			 default:
				    traceLogA(  "tmpHandler_stream2CommAuthInfo_mis: 未处理的cfgId %d",  pItem->head.cfgId  );
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}


 int  authResp2Stream_mis(  unsigned  int  uiStreamId,  AUTH_RESP_MIS  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 //  serverHello
	 if  (  pReq->uiCommEncCtxType  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiCommEncCtxType,  (  void  *  )pReq->uiCommEncCtxType,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->uiBlobLen_publicKey  )  {
		 if  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_publicKeyBlob,  pReq->publicKeyBlob,  pReq->uiBlobLen_publicKey,  &ptr,  &len  )  )  goto  errLabel;  
	 }

	 //  
	 if  (  pReq->idInfo.ui64Id  )  {						   
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId,  &pReq->idInfo.ui64Id,  sizeof(  pReq->idInfo.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  pReq->uiLogonId  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiLogonId,  (  void  *  )pReq->uiLogonId,  0,  &ptr,  &len  )  )  goto  errLabel;  
	 }
	 if  (  pReq->wRndName_serv[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_wRndName_serv,  pReq->wRndName_serv,  wcslen(  pReq->wRndName_serv  ),  &ptr,  &len  )  )  goto  errLabel;  
	 }

	 //  2009/10/11
	 if  (  pReq->ucbDaemonDemo  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbDaemonDemo,  (  void  *  )pReq->ucbDaemonDemo,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //  2009/11/05
	 if  (  pReq->usMaxVideoConferenceMems  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usMaxVideoConferenceMems,  (  void  *  )pReq->usMaxVideoConferenceMems,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->ucDays_left  )  {	//  2010/03/22
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucDays_left,  (  void  *  )pReq->ucDays_left,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //  2011/10/22
	 if  (  pReq->usAppAvLevel_daemon  &&  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usAppAvLevel,  (  void  *  )pReq->usAppAvLevel_daemon,  0,  &ptr,  &len  )  )  goto  errLabel;

	 //  2011/04/07
	 if  (  pReq->talkerDesc[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_talkerDesc,  pReq->talkerDesc,  lstrlen(  pReq->talkerDesc  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->wBuf_hint[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_hint,  pReq->wBuf_hint,  lstrlen(  pReq->wBuf_hint  ),  &ptr,  &len  )  )  goto  errLabel;
	 }


	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2AuthResp_mis(  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0
	 AUTH_RESP_MIS			*	pAuthResp	=	(  AUTH_RESP_MIS  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;

	 if  (  uiStreamId  !=  CONST_imCommType_authResp  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );
	 switch  (  tmp_cfgId  )  {
		     case  CONST_qnmCfgId_uiCommEncCtxType:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pAuthResp->uiCommEncCtxType  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_publicKeyBlob:
				   pAuthResp->uiBlobLen_publicKey  =  sizeof(  pAuthResp->publicKeyBlob  );
				   if  (  getFieldData_data(  pItem,  pAuthResp->publicKeyBlob,  &pAuthResp->uiBlobLen_publicKey  )  )  goto  errLabel;
				   break;
				   //
			 case  CONST_qnmCfgId_messengerId:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pAuthResp->idInfo.ui64Id  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiLogonId:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pAuthResp->uiLogonId  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_wRndName_serv:
				   if  (  getFieldData_wStr(  pItem,  pAuthResp->wRndName_serv,  mycountof(  pAuthResp->wRndName_serv  )  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_ucbDaemonDemo:	//  2009/10/11
				   if  (  getFieldData_char(  pItem,  (  char  *  )&pAuthResp->ucbDaemonDemo  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usMaxVideoConferenceMems:	//  2009/11/05
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pAuthResp->usMaxVideoConferenceMems  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_ucDays_left:				//  2010/03/22
				   if  (  getFieldData_char(  pItem,  (  char  *  )&pAuthResp->ucDays_left  )  )  goto  errLabel;
				   break;
				   //
			 case  CONST_qnmCfgId_usAppAvLevel:		//  2011/10/22
				   getFieldData_short(  pItem,  (  short  *  )&pAuthResp->usAppAvLevel_daemon  );
				   break;
				   //
			 case  CONST_qnmCfgId_talkerDesc:
				   if  (  getFieldData_wStr(  pItem,  pAuthResp->talkerDesc,  mycountof(  pAuthResp->talkerDesc  )  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_hint:
				   getFieldData_wStr(  pItem,  pAuthResp->wBuf_hint,  mycountof(  pAuthResp->wBuf_hint  )  );
				   break;
			 default:
					break;
					
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
	 
}



 int  msgRoute2Stream(  unsigned  int  uiStreamId,  MSG_ROUTE  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->idInfo_to.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId_to,  (  void  *  )&pReq->idInfo_to.ui64Id,  sizeof(  pReq->idInfo_to.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->idInfo_from.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId_from,  (  void  *  )&pReq->idInfo_from.ui64Id,  sizeof(  pReq->idInfo_from.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //
	 if  (  pReq->uiMsgRouteId  )  {		//  2008/05/27
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiMsgRouteId,  (  void  *  )pReq->uiMsgRouteId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //
	 if  (  pReq->uiLogonId  )  {			//  2007/12/22
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiLogonId,  (  void  *  )pReq->uiLogonId,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //
	 if  (  pReq->usLangId_from  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_langId,  (  void  *  )pReq->usLangId_from,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //
	 if  (  pReq->uiDevType_to  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiDevType_to,  (  void  *  )pReq->uiDevType_to,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->wDevIdStr_to[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_wDevIdStr_to,  pReq->wDevIdStr_to,  lstrlen(  pReq->wDevIdStr_to  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->uiDevType_from  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiDevType_from,  (  void  *  )pReq->uiDevType_from,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->wDevIdStr_from[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_wDevIdStr_from,  pReq->wDevIdStr_from,  lstrlen(  pReq->wDevIdStr_from  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->wReversePath[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_wReversePath,  pReq->wReversePath,  lstrlen(  pReq->wReversePath  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->wForwardPath[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_wForwardPath,  pReq->wForwardPath,  lstrlen(  pReq->wForwardPath  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //
	 /*	 
	 struct												{
			 QY_MESSENGER_ID							idInfo;
	 }													mems_to[CONST_maxMsgrs_sendTo];	//  2008/03/27, 可同时发到的若干联系人.
	 */
	 //  2009/09/12
	 for  (  i  =  0;  i  <  mycountof(  pReq->mems_to  );  i  ++  )  {
		  if  (  pReq->mems_to[i].idInfo.ui64Id  )  {		  
			  if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_messengerId_to,  (  void  *  )&pReq->mems_to[i].idInfo.ui64Id,  sizeof(  pReq->mems_to[i].idInfo.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
		  }
	 }
	 //
	 if  (  pReq->uiObjType_src  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiObjType,  (  void  *  )pReq->uiObjType_src,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->ulDetectedIp_from  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_ulDetectedIp,  (  void  *  )pReq->ulDetectedIp_from,  0,  &ptr,  &len  )  )  goto  errLabel;    
	 }
	 if  (  pReq->displayName_from[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_displayName, pReq->displayName_from,  lstrlen(  pReq->displayName_from  ),  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //  以下为了解数据报的性能而做.通常在release中是要取消的
	 if  (  pReq->debugInfo.tTime_start  )  {

		 //  发起端
		 if  (  pReq->debugInfo.tTime_start  )  {
			 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tTime_start,  (  void  *  )&pReq->debugInfo.tTime_start,  sizeof(  pReq->debugInfo.tTime_start  ),  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->debugInfo.usElapsed_toSend  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_toSend,  (  void  *  )pReq->debugInfo.usElapsed_toSend,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }

		 //  2008/11/19
		 if  (  pReq->debugInfo.index  )  {
			 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_index,  (  void  *  )pReq->debugInfo.index,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }

		 //  server转发请求
		 if  (  pReq->debugInfo.req.tTime_serv_startToRecv  )  {
			 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tTime_serv_startToRecv,  (  void  *  )&pReq->debugInfo.req.tTime_serv_startToRecv,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->debugInfo.req.usElapsed_serv_recved  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_serv_recved,  (  void  *  )pReq->debugInfo.req.usElapsed_serv_recved,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->debugInfo.req.usElapsed_serv_startToProcess  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_serv_startToProcess,  (  void  *  )pReq->debugInfo.req.usElapsed_serv_startToProcess,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }				 
		 if  (  pReq->debugInfo.req.usElapsed_serv_toFindDst  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_serv_toFindDst,  (  void  *  )pReq->debugInfo.req.usElapsed_serv_toFindDst,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->debugInfo.req.usElapsed_serv_toBeSwitched  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_serv_toBeSwitched,  (  void  *  )pReq->debugInfo.req.usElapsed_serv_toBeSwitched,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->debugInfo.req.usElapsed_serv_toSend  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_serv_toSend,  (  void  *  )pReq->debugInfo.req.usElapsed_serv_toSend,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }

		 //  接受并响应端
		 if  (  pReq->debugInfo.dwTickCnt_peer_recved  )  {
			 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_dwTickCnt_peer_recved,  (  void  *  )pReq->debugInfo.dwTickCnt_peer_recved,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->debugInfo.tTime_peer_recved  )  {
			 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tTime_peer_recved,  (  void  *  )&pReq->debugInfo.tTime_peer_recved,  sizeof(  pReq->debugInfo.tTime_peer_recved  ),  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->debugInfo.usElapsed_peer_resp_toSend  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_peer_resp_toSend,  (  void  *  )pReq->debugInfo.usElapsed_peer_resp_toSend,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }

		 //  server转发响应
		 if  (  pReq->debugInfo.resp.tTime_serv_startToRecv  )  {
			 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tTime_serv_resp_startToRecv,  (  void  *  )&pReq->debugInfo.resp.tTime_serv_startToRecv,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->debugInfo.resp.usElapsed_serv_recved  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_serv_resp_recved,  (  void  *  )pReq->debugInfo.resp.usElapsed_serv_recved,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->debugInfo.resp.usElapsed_serv_startToProcess  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_serv_resp_startToProcess,  (  void  *  )pReq->debugInfo.resp.usElapsed_serv_startToProcess,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }				 
		 if  (  pReq->debugInfo.resp.usElapsed_serv_toFindDst  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_serv_resp_toFindDst,  (  void  *  )pReq->debugInfo.resp.usElapsed_serv_toFindDst,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->debugInfo.resp.usElapsed_serv_toBeSwitched  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_serv_resp_toBeSwitched,  (  void  *  )pReq->debugInfo.resp.usElapsed_serv_toBeSwitched,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }
		 if  (  pReq->debugInfo.resp.usElapsed_serv_toSend  )  {
			 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_serv_resp_toSend,  (  void  *  )pReq->debugInfo.resp.usElapsed_serv_toSend,  0,  &ptr,  &len  )  )  goto  errLabel;
		 }

		 //  响应回到发起端
		 //  if  (  pReq->debugInfo.dwTickCnt_resp_recved  )  {
		 //		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_dwTickCnt_resp_recved,  (  void  *  )pReq->debugInfo.dwTickCnt_resp_recved,  0,  &ptr,  &len  )  )  goto  errLabel;
		 //	 }
		 //	 if  (  pReq->debugInfo.usElapsed_resp_end  )  {
		 //		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usElapsed_resp_end,  (  void  *  )pReq->debugInfo.usElapsed_resp_end,  0,  &ptr,  &len  )  )  goto  errLabel;
		 //	 }
	 }
				
	 

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2MsgRoute(  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 MSG_ROUTE				*	pContent	=	(  MSG_ROUTE  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_msgRoute  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );
	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_displayName:
				   if  (  getFieldData_wStr(  pItem,  pContent->displayName_from,  mycountof(  pContent->displayName_from  )  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_ulDetectedIp:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->ulDetectedIp_from  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiObjType:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiObjType_src  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiDevType_from:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiDevType_from  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_wDevIdStr_from:
				   if  (  getFieldData_wStr(  pItem,  pContent->wDevIdStr_from,  mycountof(  pContent->wDevIdStr_from  )  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiDevType_to:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiDevType_to  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_wDevIdStr_to:
				   if  (  getFieldData_wStr(  pItem,  pContent->wDevIdStr_to,  mycountof(  pContent->wDevIdStr_to  )  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_wReversePath:
				   if  (  getFieldData_wStr(  pItem,  pContent->wReversePath,  mycountof(  pContent->wReversePath  )  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_wForwardPath:
				   if  (  getFieldData_wStr(  pItem,  pContent->wForwardPath,  mycountof(  pContent->wForwardPath  )  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_langId:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usLangId_from  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiLogonId:		//  2007/12/22
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiLogonId  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiMsgRouteId:		//  2008/05/27
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiMsgRouteId  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_messengerId_from:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->idInfo_from.ui64Id  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_messengerId_to:
				   if  (  !pContent->idInfo_to.ui64Id  )  {
					   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->idInfo_to.ui64Id  )  )  goto  errLabel;
					   }
				   else  {
					     if  (  pContent->tmpInternal.usCnt_mems_to  >=  mycountof(  pContent->mems_to  )  )  {
							 traceLogA(  "stream2MsgRoute: usCnt_mems_to >= mycountof(  mems_to  )"  );
						     break;
						 }
						 if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->mems_to[pContent->tmpInternal.usCnt_mems_to].idInfo.ui64Id  )  )  goto  errLabel;
						 pContent->tmpInternal.usCnt_mems_to  ++  ;					     
				   }
				   break;

		     //  下面为一些用于性能评估的参数

			 case  CONST_qnmCfgId_tTime_start:
				   if  (  getFieldData_l64(  pItem,  &pContent->debugInfo.tTime_start  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usElapsed_toSend:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.usElapsed_toSend  )  )  goto  errLabel;
				   break;

			 case  CONST_qnmCfgId_index:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->debugInfo.index  )  )  goto  errLabel;
				   break;
			 //
			 case  CONST_qnmCfgId_tTime_serv_startToRecv:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->debugInfo.req.tTime_serv_startToRecv  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usElapsed_serv_recved:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.req.usElapsed_serv_recved  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usElapsed_serv_startToProcess:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.req.usElapsed_serv_startToProcess  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usElapsed_serv_toFindDst:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.req.usElapsed_serv_toFindDst  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usElapsed_serv_toBeSwitched:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.req.usElapsed_serv_toBeSwitched  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usElapsed_serv_toSend:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.req.usElapsed_serv_toSend  )  )  goto  errLabel;
				   break;
			 //			
			 case  CONST_qnmCfgId_dwTickCnt_peer_recved:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->debugInfo.dwTickCnt_peer_recved  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_tTime_peer_recved:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->debugInfo.tTime_peer_recved  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usElapsed_peer_resp_toSend:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.usElapsed_peer_resp_toSend  )  )  goto  errLabel;
				   break;
		     //		
			 case  CONST_qnmCfgId_tTime_serv_resp_startToRecv:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->debugInfo.resp.tTime_serv_startToRecv  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usElapsed_serv_resp_recved:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.resp.usElapsed_serv_recved  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usElapsed_serv_resp_startToProcess:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.resp.usElapsed_serv_startToProcess  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usElapsed_serv_resp_toFindDst:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.resp.usElapsed_serv_toFindDst  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usElapsed_serv_resp_toBeSwitched:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.resp.usElapsed_serv_toBeSwitched  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usElapsed_serv_resp_toSend:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.resp.usElapsed_serv_toSend  )  )  goto  errLabel;
				   break;
			 //
			 //  case  CONST_qnmCfgId_dwTickCnt_resp_recved:
			 //	   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->debugInfo.dwTickCnt_resp_recved  )  )  goto  errLabel;
			 //	   break;
			 //  case  CONST_qnmCfgId_usElapsed_resp_end:
			 //	   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->debugInfo.usElapsed_resp_end  )  )  goto  errLabel;
			 //	   break;
				

			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}


////////////////


 int  imHtmlContent2Stream(  unsigned  int  uiStreamId,  IM_HTML_CONTENT  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->uiSerialNo  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiSerialNo,  (  void  *  )pReq->uiSerialNo,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->wBuf[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_wStr,  CONST_qnmCfgId_hint, pReq->wBuf,  lstrlen(  pReq->wBuf  ),  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2ImHtmlContent(  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 IM_HTML_CONTENT		*	pContent	=	(  IM_HTML_CONTENT  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_htmlContent  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );
	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_start:
				   pContent->uiType  =  uiStreamId;   
				   break;
			 case  CONST_qnmCfgId_hint:
				   if  (  getFieldData_wStr(  pItem,  pContent->wBuf,  mycountof(  pContent->wBuf  )  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_tStartTime_serv:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->tStartTime_serv  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiSerialNo:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiSerialNo  )  )  goto  errLabel;
				   break;
			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}


////////////////////


 int  rtcCallReq2Stream(  unsigned  int  uiStreamId,  RTC_CALL_REQ  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->uiTaskType  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTaskType,  (  void  *  )pReq->uiTaskType,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->ulIp_caller  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_ulIp_caller,  (  void  *  )pReq->ulIp_caller,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2RtcCallReq(  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 RTC_CALL_REQ			*	pContent	=	(  RTC_CALL_REQ  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_rtcCallReq  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_start:
				   pContent->uiType  =  uiStreamId;
				   break;
			 case  CONST_qnmCfgId_uiTaskType:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiTaskType  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_ulIp_caller:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->ulIp_caller  )  )  goto  errLabel;
				   break;
			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}


//////////////////

  int  qyhtonVideoHeader(  QY_VIDEO_HEADER  *  pVh  )
{
	if  (  !pVh  )  return  -1;
	BITMAPINFOHEADER	*	p  =  &pVh->bih;

	if  (  !p->biSize  )  p->biSize  =  sizeof(  BITMAPINFOHEADER  );
	if  (  p->biSize  <  sizeof(  pVh->bih  )  )  {
		traceLogA(  "Warning: qyhtonVideoHeader failed: biSize too small, %d",  p->biSize  );
		qyShowInfo(  CONST_qyShowType_qwmComm,  NULL,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "qyhtonVideoHeader: biSize to small %d"  ),  p->biSize  );
		return  -1;
	}
	if  (  p->biSize  >  sizeof(  pVh->bih  )  +  sizeof(  pVh->bPrivateData  )  )  {
		traceLogA(  "qyhtonVideoHeader failed: biSize too large, %d",  p->biSize  );
		return  -1;
	}

	DWORD	biSize  =  p->biSize;

	MACRO_htonl(  p->biSize  );
	MACRO_htonl(  p->biWidth  );
	MACRO_htonl(  p->biHeight  );
	MACRO_htons(  p->biPlanes  );
	MACRO_htons(  p->biBitCount  );
	MACRO_htonl(  p->biCompression  );
	MACRO_htonl(  p->biSizeImage  );
	MACRO_htonl(  p->biXPelsPerMeter  );
	MACRO_htonl(  p->biYPelsPerMeter  );
	MACRO_htonl(  p->biClrUsed  );
	MACRO_htonl(  p->biClrImportant  );

	return  biSize;
}

#if  0
 int  qyntohVideoHeader(  QY_VIDEO_HEADER  *  pVh  )
{
	if  (  !pVh  )  return  -1;
	BITMAPINFOHEADER  *  p  =  &pVh->bih;
	
	MACRO_ntohl(  p->biSize  );
	if  (  !p->biSize  )  p->biSize  =  sizeof(  BITMAPINFOHEADER  );
	if  (  p->biSize  <  sizeof(  pVh->bih  )  )  {
		traceLogA(  "Warning: qyntohVideoHeader: biSize too small, %d",  p->biSize  );
		qyShowInfo(  CONST_qyShowType_qwmComm,  NULL,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "qyntohVideoHeader: biSize to small %d"  ),  p->biSize  );
		return  -1;
	}
	if  (  p->biSize  >  sizeof(  pVh->bih  )  +  sizeof(  pVh->bPrivateData  )  )  {
		traceLogA(  "qyntohVideoHeader: biSize too large, %d",  p->biSize  );
		return  -1;
	}

	MACRO_ntohl(  p->biWidth  );
	MACRO_ntohl(  p->biHeight  );
	MACRO_ntohs(  p->biPlanes  );
	MACRO_ntohs(  p->biBitCount  );
	MACRO_ntohl(  p->biCompression  );
	MACRO_ntohl(  p->biSizeImage  );
	MACRO_ntohl(  p->biXPelsPerMeter  );
	MACRO_ntohl(  p->biYPelsPerMeter  );
	MACRO_ntohl(  p->biClrUsed  );
	MACRO_ntohl(  p->biClrImportant  );

	return  sizeof(  pVh[0]  );
}
#else
 int  qyntohVideoHeader(  QY_VIDEO_HEADER  *  pVh  )
{
	if  (  !pVh  )  return  -1;
	BITMAPINFOHEADER  *  p  =  &pVh->bih;
	
	MACRO_ntohl(  p->biSize  );

	DWORD  tmp_biSize;
	memcpy(  &tmp_biSize,  &p->biSize,  sizeof(  tmp_biSize  )  );
	if  (  !tmp_biSize  )  tmp_biSize  =  sizeof(  BITMAPINFOHEADER  );
	if  (  tmp_biSize  <  sizeof(  pVh->bih  )  )  {
		traceLogA(  "Warning: qyntohVideoHeader: biSize too small, %d",  tmp_biSize  );
		qyShowInfo(  CONST_qyShowType_qwmComm,  NULL,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "qyntohVideoHeader: biSize to small %d"  ),  tmp_biSize  );
		return  -1;
	}
	if  (  tmp_biSize  >  sizeof(  pVh->bih  )  +  sizeof(  pVh->bPrivateData  )  )  {
		traceLogA(  "qyntohVideoHeader: biSize too large, %d",  tmp_biSize  );
		return  -1;
	}
	memcpy(  &p->biSize,  &tmp_biSize,  sizeof(  p->biSize  )  );

	MACRO_ntohl(  p->biWidth  );
	MACRO_ntohl(  p->biHeight  );
	MACRO_ntohs(  p->biPlanes  );
	MACRO_ntohs(  p->biBitCount  );
	MACRO_ntohl(  p->biCompression  );
	MACRO_ntohl(  p->biSizeImage  );
	MACRO_ntohl(  p->biXPelsPerMeter  );
	MACRO_ntohl(  p->biYPelsPerMeter  );
	MACRO_ntohl(  p->biClrUsed  );
	MACRO_ntohl(  p->biClrImportant  );

	return  sizeof(  pVh[0]  );
}
#endif





/////////////////

  int  qyhtonAudioHeader(  QY_AUDIO_HEADER  *  pAh  )
{
	if  (  !pAh  )  return  -1;
	WAVEFORMATEX  *  p  =  &pAh->wfx;
	if  (  p->cbSize  >  sizeof(  pAh->bExtraData  )  )  {
		traceLogA(  "qyhtonAudioHeader failed: cbSize too large, %d",  p->cbSize  );
		return  -1;
	}

	DWORD	biSize  =  sizeof(  p[0]  )  +  p->cbSize;

	MACRO_htons(  p->wFormatTag  );        // format type 
	MACRO_htons(  p->nChannels  );         // number of channels (i.e. mono, stereo...) 
	MACRO_htonl(  p->nSamplesPerSec  );    // sample rate 
	MACRO_htonl(  p->nAvgBytesPerSec  );   // for buffer estimation 
	MACRO_htons(  p->nBlockAlign  );       // block size of data 
	MACRO_htons(  p->wBitsPerSample  );    // Number of bits per sample of mono data 
	MACRO_htons(  p->cbSize  );            // The count in bytes of the size of  

	return  biSize;
}

 int  qyntohAudioHeader(  QY_AUDIO_HEADER  *  pAh  )
{
	if  (  !pAh  )  return  -1;
	WAVEFORMATEX	*	p	=	&pAh->wfx;

	MACRO_ntohs(  p->wFormatTag  );        // format type 
	MACRO_ntohs(  p->nChannels  );         // number of channels (i.e. mono, stereo...) 
	MACRO_ntohl(  p->nSamplesPerSec  );    // sample rate 
	MACRO_ntohl(  p->nAvgBytesPerSec  );   // for buffer estimation 
	MACRO_ntohs(  p->nBlockAlign  );       // block size of data 
	MACRO_ntohs(  p->wBitsPerSample  );    // Number of bits per sample of mono data 
	MACRO_ntohs(  p->cbSize  );            // The count in bytes of the size of  

	WORD	tmp_cbSize;
	memcpy(  &tmp_cbSize,  &p->cbSize,  sizeof(  tmp_cbSize  )  );
	if  (  tmp_cbSize  >  sizeof(  pAh->bExtraData  )  )  {
		traceLogA(  "qyntohAudioHeader failed: cbSize too large, %d",  tmp_cbSize  );
		return  -1;
	}

	return  sizeof(  p[0]  );
}



 int  tmp_htonAvTranInfo(  AV_TRAN_INFO  *  pTranInfo,  char  **  pBuf,  unsigned  int  *  puiBufSize  )
{
	int					iErr	=	-1;
	int					i		=  0;
	char			*	ptr		=	*pBuf;
	unsigned  int		len		=	*puiBufSize;


	 if  (  pTranInfo->usCntLimit_mems_from  )  {	//  2009/05/30
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCntLimit_mems_from,  (  void  *  )pTranInfo->usCntLimit_mems_from,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pTranInfo->usCntLimit_activeMems_from  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCntLimit_activeMems_from,  (  void  *  )pTranInfo->usCntLimit_activeMems_from,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pTranInfo->video.usMaxFps_toShareBmp_videoConference  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usMaxFps_toShareBmp,  (  void  *  )pTranInfo->video.usMaxFps_toShareBmp_videoConference,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pTranInfo->video.usCapDriverIndex  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCapDriverIndex,  (  void  *  )pTranInfo->video.usCapDriverIndex,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pTranInfo->video.compressor.common.ucCompressors  )  {  //  200903/30
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucVideoCompressors,  (  void  *  )pTranInfo->video.compressor.common.ucCompressors,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pTranInfo->video.compressor.common.fourccStr[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_str,  CONST_qnmCfgId_fourccStr,  pTranInfo->video.compressor.common.fourccStr,  strlen(  pTranInfo->video.compressor.common.fourccStr  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pTranInfo->video.compressor.common.ucbOutputFlippedImg  )  {	//  2011/12/11
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbFlippedImg,  (  void  *  )pTranInfo->video.compressor.common.ucbOutputFlippedImg,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 
	 //  BITMAPINFOHEADER									bih;
	 QY_VIDEO_HEADER									vh;
	 int												tmpLen;
	 memcpy(  &vh,  &pTranInfo->video.vh_compress,  sizeof(  vh  )  );
	 if  (  (  tmpLen  =  qyhtonVideoHeader(  &vh  )  )  <  0  )  goto  errLabel;
	 if  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_bih_compress,  &vh,  tmpLen,  &ptr,  &len  )  )  goto  errLabel;
	 memcpy(  &vh,  &pTranInfo->video.vh_decompress,  sizeof(  vh  )  );
	 if  (  (  tmpLen  =  qyhtonVideoHeader(  &vh  )  )  <  0  )  goto  errLabel;
	 if  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_bih_decompress,  &vh,  tmpLen,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pTranInfo->video.uiTranNo_openAvDev  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_openVideoDev,  (  void  *  )pTranInfo->video.uiTranNo_openAvDev,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }


	 if  (  pTranInfo->audio.uiTranNo_openAvDev  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_openAudioDev,  (  void  *  )pTranInfo->audio.uiTranNo_openAvDev,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pTranInfo->audio.compressor.ucCompressors  )  {		//  2009/05/18
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucAudioCompressors,  (  void  *  )pTranInfo->audio.compressor.ucCompressors,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pTranInfo->audio.compressor.uiBytesRecorded_perBlockAlign  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiBytesRecorded_perBlockAlign,  (  void  *  )pTranInfo->audio.compressor.uiBytesRecorded_perBlockAlign,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //  WAVEFORMATEX										wf;
	 QY_AUDIO_HEADER									ah;
	 memcpy(  &ah,  &pTranInfo->audio.ah_compress,  sizeof(  ah  )  );
	 if  (  (  tmpLen  =  qyhtonAudioHeader(  &ah  )  )  <  0  )  goto  errLabel;
	 if  (  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_wf_compress,  &ah,  tmpLen,  &ptr,  &len  )  )  )  goto  errLabel;

	 //  2009/04/27
	 memcpy(  &ah,  &pTranInfo->audio.ah_decompress,  sizeof(  ah  )  );
	 if  (  (  tmpLen  =  qyhtonAudioHeader(  &ah  )  )  <  0  )  goto  errLabel;
	 if  (  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_wf_decompress,  &ah,  tmpLen,  &ptr,  &len  )  )  )  goto  errLabel;

	 //  2009/06/14
	 if  (  pTranInfo->audio.compressor.playCfg.usMinTimeInMsOfAudioDataPlaying  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usMinTimeInMsOfAudioDataPlaying,  (  void  *  )pTranInfo->audio.compressor.playCfg.usMinTimeInMsOfAudioDataPlaying,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pTranInfo->audio.compressor.playCfg.usAudioDataAddedToPlayEveryTime  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usAudioDataAddedToPlayEveryTime,  (  void  *  )pTranInfo->audio.compressor.playCfg.usAudioDataAddedToPlayEveryTime,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pTranInfo->audio.compressor.playCfg.usNotifyIntervalInMs_needMoreAudioData  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usNotifyIntervalInMs_needMoreAudioData,  (  void  *  )pTranInfo->audio.compressor.playCfg.usNotifyIntervalInMs_needMoreAudioData,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //  2012/01/27
	 if  (  pTranInfo->audio.compressor.playCfg.usMinTimeInMsToPlay  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usMinTimeInMsToPlay,  (  void  *  )pTranInfo->audio.compressor.playCfg.usMinTimeInMsToPlay,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //  2009/06/03
	 if  (  pTranInfo->audio.compressor.playCfg.usMaxTimeInMsToPlay  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usMaxTimeInMsToPlay,  (  void  *  )pTranInfo->audio.compressor.playCfg.usMaxTimeInMsToPlay,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pTranInfo->audio.compressor.playCfg.usMaxTimeInMsToBeRemoved  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usMaxTimeInMsToBeRemoved,  (  void  *  )pTranInfo->audio.compressor.playCfg.usMaxTimeInMsToBeRemoved,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //
	 //  unsigned  short								usMaxTimeInMsToPlay;				//  2009/06/03
	 //  unsigned  short								usMaxTimeToBeRemoved;				//  2009/06/03

	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *pBuf  =  ptr;
		 *puiBufSize  =  len;
	 }
	 return  iErr;
 
}


 int  tmp_ntohAvTranInfo(  QY_CFGITEM_ntoh_U  *  pItem,  AV_TRAN_INFO  *  pTranInfo  )
{
	 int						iErr		=	-1;
	 int						tmpLen;
	 char						buf[sizeof(  QY_VIDEO_HEADER  )  +  1024];

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_usCntLimit_mems_from:			//  2009/05/30
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pTranInfo->usCntLimit_mems_from  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usCntLimit_activeMems_from:	//  2009/05/31
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pTranInfo->usCntLimit_activeMems_from  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiTranNo_openVideoDev:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pTranInfo->video.uiTranNo_openAvDev  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usMaxFps_toShareBmp:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pTranInfo->video.usMaxFps_toShareBmp_videoConference  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usCapDriverIndex:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pTranInfo->video.usCapDriverIndex  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_ucVideoCompressors:	//  2009/03/30
				   if  (  getFieldData_char(  pItem,  (  char  *  )&pTranInfo->video.compressor.common.ucCompressors  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_fourccStr:
				   if  (  getFieldData_str(  pItem,  pTranInfo->video.compressor.common.fourccStr,  mycountof(  pTranInfo->video.compressor.common.fourccStr  )  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_ucbFlippedImg:		//  2011/12/11
				   if  (  getFieldData_char(  pItem,  (  char  *  )&pTranInfo->video.compressor.common.ucbOutputFlippedImg  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_bih_compress:
				   tmpLen  =  sizeof(  buf  );
				   if  (  getFieldData_data(  pItem,  buf,  (  unsigned  int  *  )&tmpLen  )  )  goto  errLabel;
				   if  (  tmpLen  >  sizeof(  buf  )  )  goto  errLabel;											//  impossible  
				   memset(  buf  +  tmpLen,  0,  sizeof(  buf  )  -  tmpLen  );
				   if  (  qyntohVideoHeader(  (  QY_VIDEO_HEADER  *  )buf  )  <  0  )  goto  errLabel;
				   memcpy(  &pTranInfo->video.vh_compress,  buf,  sizeof(  pTranInfo->video.vh_compress  )  );
				   break;
			 case  CONST_qnmCfgId_bih_decompress:
				   tmpLen  =  sizeof(  buf  );
				   if  (  getFieldData_data(  pItem,  buf,  (  unsigned  int  *  )&tmpLen  )  )  goto  errLabel;
				   if  (  tmpLen  >  sizeof(  buf  )  )  goto  errLabel;											//  impossible  
				   memset(  buf  +  tmpLen,  0,  sizeof(  buf  )  -  tmpLen  );
				   if  (  qyntohVideoHeader(  (  QY_VIDEO_HEADER  *  )buf  )  <  0  )  goto  errLabel;
				   memcpy(  &pTranInfo->video.vh_decompress,  buf,  sizeof(  pTranInfo->video.vh_decompress  )  );
				   break;

				   //
			 case  CONST_qnmCfgId_uiTranNo_openAudioDev:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pTranInfo->audio.uiTranNo_openAvDev  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_ucAudioCompressors:		//  2009/05/18
				   if  (  getFieldData_char(  pItem,  (  char  *  )&pTranInfo->audio.compressor.ucCompressors  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiBytesRecorded_perBlockAlign:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pTranInfo->audio.compressor.uiBytesRecorded_perBlockAlign  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_wf_compress:
				   tmpLen  =  sizeof(  buf  );
				   if  (  getFieldData_data(  pItem,  buf,  (  unsigned  int  *  )&tmpLen  )  )  goto  errLabel;
				   if  (  tmpLen  >  sizeof(  buf  )  )  goto  errLabel;
				   memset(  buf  +  tmpLen,  0,  sizeof(  buf  )  -  tmpLen  );
				   if  (  qyntohAudioHeader(  (  QY_AUDIO_HEADER  *  )buf  )  <  0  )  goto  errLabel;
				   memcpy(  &pTranInfo->audio.ah_compress,  buf,  sizeof(  pTranInfo->audio.ah_compress  )  );
				   break;
			 case  CONST_qnmCfgId_wf_decompress:	//  2009/04/27
				   tmpLen  =  sizeof(  buf  );
				   if  (  getFieldData_data(  pItem,  buf,  (  unsigned  int  *  )&tmpLen  )  )  goto  errLabel;
				   if  (  tmpLen  >  sizeof(  buf  )  )  goto  errLabel;
				   memset(  buf  +  tmpLen,  0,  sizeof(  buf  )  -  tmpLen  );
				   if  (  qyntohAudioHeader(  (  QY_AUDIO_HEADER  *  )buf  )  <  0  )  goto  errLabel;
				   memcpy(  &pTranInfo->audio.ah_decompress,  buf,  sizeof(  pTranInfo->audio.ah_decompress  )  );
				   break;

				   //  2009/06/14
			 case  CONST_qnmCfgId_usMinTimeInMsOfAudioDataPlaying:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pTranInfo->audio.compressor.playCfg.usMinTimeInMsOfAudioDataPlaying  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usAudioDataAddedToPlayEveryTime:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pTranInfo->audio.compressor.playCfg.usAudioDataAddedToPlayEveryTime  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usNotifyIntervalInMs_needMoreAudioData:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pTranInfo->audio.compressor.playCfg.usNotifyIntervalInMs_needMoreAudioData  )  )  goto  errLabel;
				   break;
				   //
			 case  CONST_qnmCfgId_usMinTimeInMsToPlay:		//  2012/01/27
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pTranInfo->audio.compressor.playCfg.usMinTimeInMsToPlay  )  )  goto  errLabel;
				   break;
				   //
			 case  CONST_qnmCfgId_usMaxTimeInMsToPlay:		//  2009/06/03
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pTranInfo->audio.compressor.playCfg.usMaxTimeInMsToPlay  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usMaxTimeInMsToBeRemoved:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pTranInfo->audio.compressor.playCfg.usMaxTimeInMsToBeRemoved  )  )  goto  errLabel;
				   break;

			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}


 ////////////////////////////










 int  transferAvInfo2Stream(  unsigned  int  uiStreamId,  TRANSFER_AV_INFO  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->ucbResp  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbResp,  (  void  *  )pReq->ucbResp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pReq->uiTaskType  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTaskType,  (  void  *  )pReq->uiTaskType,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  tmp_htonAvTranInfo(  &pReq->tranInfo,  &ptr,  &len  )  )  goto  errLabel;

	 //  2009/09/07
	 if  (  pReq->viewDynBmp.uiObjType  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiObjType,  (  void  *  )pReq->viewDynBmp.uiObjType,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->viewDynBmp.usIndex  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_index,  (  void  *  )pReq->viewDynBmp.usIndex,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //  2009/10/18
	 if  (  pReq->idInfo_logicalPeer.ui64Id  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_idInfo_logicalPeer,  (  void  *  )&pReq->idInfo_logicalPeer.ui64Id,  sizeof(  pReq->idInfo_logicalPeer.ui64Id  ),  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //  qyShowInfo(  CONST_qyShowType_debug,  (  ""  ),  _T(  ""  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "    transferAvInfo2stream: uiTranNo_openAvDev %d"  ),  pReq->uiTranNo_openAvDev  );

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2TransferAvInfo(  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 TRANSFER_AV_INFO		*	pContent	=	(  TRANSFER_AV_INFO  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  int						tmpLen;
	 //  char						buf[sizeof(  QY_VIDEO_HEADER  )  +  1024];
	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_transferAvInfo  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_start:
				   pContent->uiType  =  uiStreamId;
				   break;
			 case  CONST_qnmCfgId_ucbResp:
				   if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->ucbResp  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiTaskType:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiTaskType  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiObjType:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->viewDynBmp.uiObjType  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_index:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->viewDynBmp.usIndex  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_idInfo_logicalPeer:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->idInfo_logicalPeer.ui64Id  )  )  goto  errLabel;
				   break;
			 default:
				    if  (  tmp_ntohAvTranInfo(  pItem,  &pContent->tranInfo  )  )  goto  errLabel;
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}


#if  0	//  2011/12/24
 int  transferAvReplyInfo2Stream(  unsigned  int  uiStreamId,  TRANSFER_AV_replyInfo  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->usOp  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usOp,  (  void  *  )pReq->usOp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->tStartTime_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tStartTime_org,  &pReq->tStartTime_org,  sizeof(  pReq->tStartTime_org  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->uiTranNo_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_org,  (  void  *  )pReq->uiTranNo_org,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }


	 //
	 if  (  pReq->tranInfo.video.uiTranNo_openAvDev  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_openVideoDev,  (  void  *  )pReq->tranInfo.video.uiTranNo_openAvDev,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pReq->tranInfo.video.usCapDriverIndex  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usCapDriverIndex,  (  void  *  )pReq->tranInfo.video.usCapDriverIndex,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->tranInfo.video.compressor.common.ucCompressors  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucVideoCompressors,  (  void  *  )pReq->tranInfo.video.compressor.common.ucCompressors,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->tranInfo.video.compressor.common.fourccStr[0]  )  {
		 if  (  data2Stream(  CONST_qyDataType_str,  CONST_qnmCfgId_fourccStr,  pReq->tranInfo.video.compressor.common.fourccStr,  strlen(  pReq->tranInfo.video.compressor.common.fourccStr  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->tranInfo.video.compressor.common.ucbOutputFlippedImg  )  {	//  2011/12/11
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucbFlippedImg,  (  void  *  )pReq->tranInfo.video.compressor.common.ucbOutputFlippedImg,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 
	 //  BITMAPINFOHEADER									bih;
	 QY_VIDEO_HEADER									vh;
	 int												tmpLen;
	 memcpy(  &vh,  &pReq->tranInfo.video.vh_compress,  sizeof(  vh  )  );
	 if  (  (  tmpLen  =  qyhtonVideoHeader(  &vh  )  )  <  0  )  goto  errLabel;
	 if  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_bih_compress,  &vh,  tmpLen,  &ptr,  &len  )  )  goto  errLabel;
	 memcpy(  &vh,  &pReq->tranInfo.video.vh_decompress,  sizeof(  vh  )  );
	 if  (  (  tmpLen  =  qyhtonVideoHeader(  &vh  )  )  <  0  )  goto  errLabel;
	 if  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_bih_decompress,  &vh,  tmpLen,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->tranInfo.video.uiTranNo_openAvDev  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_openVideoDev,  (  void  *  )pReq->tranInfo.video.uiTranNo_openAvDev,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 if  (  pReq->tranInfo.audio.uiTranNo_openAvDev  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_openAudioDev,  (  void  *  )pReq->tranInfo.audio.uiTranNo_openAvDev,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->tranInfo.audio.compressor.ucCompressors  )  {
		 if  (  data2Stream(  CONST_qyDataType_char,  CONST_qnmCfgId_ucAudioCompressors,  (  void  *  )pReq->tranInfo.audio.compressor.ucCompressors,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 //  WAVEFORMATEX										wf;
	 QY_AUDIO_HEADER										ah;
	 memcpy(  &ah,  &pReq->tranInfo.audio.ah_compress,  sizeof(  ah  )  );
	 if  (  (  tmpLen  =  qyhtonAudioHeader(  &ah  )  )  <  0  )  goto  errLabel;
	 if  (  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_wf_compress,  &ah,  tmpLen,  &ptr,  &len  )  )  )  goto  errLabel;
	 //  2009/04/27
	 memcpy(  &ah,  &pReq->tranInfo.audio.ah_decompress,  sizeof(  ah  )  );
	 if  (  (  tmpLen  =  qyhtonAudioHeader(  &ah  )  )  <  0  )  goto  errLabel;
	 if  (  (  data2Stream(  CONST_qyDataType_data,  CONST_qnmCfgId_wf_decompress,  &ah,  tmpLen,  &ptr,  &len  )  )  )  goto  errLabel;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2TransferAvReplyInfo(  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 TRANSFER_AV_replyInfo	*	pContent	=	(  TRANSFER_AV_replyInfo  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 int						tmpLen;
	 char						buf[sizeof(  QY_VIDEO_HEADER  )  +  1024];

	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_transferAvReplyInfo  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_start:
				   pContent->uiType  =  uiStreamId;
				   break;
			 case  CONST_qnmCfgId_usOp:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usOp  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_tStartTime_org:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->tStartTime_org  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiTranNo_org:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiTranNo_org  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiTranNo_openVideoDev:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->tranInfo.video.uiTranNo_openAvDev  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_usCapDriverIndex:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->tranInfo.video.usCapDriverIndex  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_ucVideoCompressors:
				   if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->tranInfo.video.compressor.common.ucCompressors  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_fourccStr:
				   if  (  getFieldData_str(  pItem,  pContent->tranInfo.video.compressor.common.fourccStr,  mycountof(  pContent->tranInfo.video.compressor.common.fourccStr  )  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_ucbFlippedImg:	//  2011/12/12
				   if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->tranInfo.video.compressor.common.ucbOutputFlippedImg  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_bih_compress:
				   tmpLen  =  sizeof(  buf  );
				   if  (  getFieldData_data(  pItem,  buf,  (  unsigned  int  *  )&tmpLen  )  )  goto  errLabel;
				   if  (  tmpLen  >  sizeof(  buf  )  )  goto  errLabel;											//  impossible  
				   memset(  buf  +  tmpLen,  0,  sizeof(  buf  )  -  tmpLen  );
				   if  (  qyntohVideoHeader(  (  QY_VIDEO_HEADER  *  )buf  )  <  0  )  goto  errLabel;
				   memcpy(  &pContent->tranInfo.video.vh_compress,  buf,  sizeof(  pContent->tranInfo.video.vh_compress  )  );
				   break;
			 case  CONST_qnmCfgId_bih_decompress:
				   tmpLen  =  sizeof(  buf  );
				   if  (  getFieldData_data(  pItem,  buf,  (  unsigned  int  *  )&tmpLen  )  )  goto  errLabel;
				   if  (  tmpLen  >  sizeof(  buf  )  )  goto  errLabel;											//  impossible  
				   memset(  buf  +  tmpLen,  0,  sizeof(  buf  )  -  tmpLen  );
				   if  (  qyntohVideoHeader(  (  QY_VIDEO_HEADER  *  )buf  )  <  0  )  goto  errLabel;
				   memcpy(  &pContent->tranInfo.video.vh_decompress,  buf,  sizeof(  pContent->tranInfo.video.vh_decompress  )  );
				   break;		

				   //
			 case  CONST_qnmCfgId_uiTranNo_openAudioDev:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->tranInfo.audio.uiTranNo_openAvDev  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_ucAudioCompressors:		//  2009/05/18
				   if  (  getFieldData_char(  pItem,  (  char  *  )&pContent->tranInfo.audio.compressor.ucCompressors  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_wf_compress:
				   tmpLen  =  sizeof(  buf  );
				   if  (  getFieldData_data(  pItem,  buf,  (  unsigned  int  *  )&tmpLen  )  )  goto  errLabel;
				   if  (  tmpLen  >  sizeof(  buf  )  )  goto  errLabel;
				   memset(  buf  +  tmpLen,  0,  sizeof(  buf  )  -  tmpLen  );
				   if  (  qyntohAudioHeader(  (  QY_AUDIO_HEADER  *  )buf  )  <  0  )  goto  errLabel;
				   memcpy(  &pContent->tranInfo.audio.ah_compress,  buf,  sizeof(  pContent->tranInfo.audio.ah_compress  )  );
				   break;
			 case  CONST_qnmCfgId_wf_decompress:
				   tmpLen  =  sizeof(  buf  );
				   if  (  getFieldData_data(  pItem,  buf,  (  unsigned  int  *  )&tmpLen  )  )  goto  errLabel;
				   if  (  tmpLen  >  sizeof(  buf  )  )  goto  errLabel;
				   memset(  buf  +  tmpLen,  0,  sizeof(  buf  )  -  tmpLen  );
				   if  (  qyntohAudioHeader(  (  QY_AUDIO_HEADER  *  )buf  )  <  0  )  goto  errLabel;
				   memcpy(  &pContent->tranInfo.audio.ah_decompress,  buf,  sizeof(  pContent->tranInfo.audio.ah_decompress  )  );
				   break;
			 default:
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}
#endif


 //  2011/12/24
 int  transferAvReplyInfo2Stream(  unsigned  int  uiStreamId,  TRANSFER_AV_replyInfo  *  pReq,  char  *  buf,  unsigned  int  *  uiBufSize  )
{
	 int				iErr	=	-1;
	 int				i		=  0;
	 char		*		ptr		=	buf;
	 unsigned  int		len		=	*uiBufSize;

	 if  (  !pReq  )  return  -1;
	 if  (  !buf  )  return  -1;

	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_start,  (  void  *  )uiStreamId,  0,  &ptr,  &len  )  )  goto  errLabel;

	 if  (  pReq->usOp  )  {
		 if  (  data2Stream(  CONST_qyDataType_short,  CONST_qnmCfgId_usOp,  (  void  *  )pReq->usOp,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->tStartTime_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_l64,  CONST_qnmCfgId_tStartTime_org,  &pReq->tStartTime_org,  sizeof(  pReq->tStartTime_org  ),  &ptr,  &len  )  )  goto  errLabel;
	 }
	 if  (  pReq->uiTranNo_org  )  {
		 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_uiTranNo_org,  (  void  *  )pReq->uiTranNo_org,  0,  &ptr,  &len  )  )  goto  errLabel;
	 }

	 //
	 if  (  tmp_htonAvTranInfo(  &pReq->tranInfo,  &ptr,  &len  )  )  goto  errLabel;

	 //
	 if  (  data2Stream(  CONST_qyDataType_long,  CONST_qnmCfgId_null,  0,  0,  &ptr,  &len  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 if  (  !iErr  )  {
		 *uiBufSize  =  *uiBufSize  -  len;
	 }
	 return  iErr;	 

}


 int  tmpHandler_stream2TransferAvReplyInfo(  void  *  p0,  void  *  p1,  unsigned  int  uiStreamId,  QY_CFGITEM_ntoh_U  *  pItem  )
{
	 int						iErr		=	-1;
	 //  p0;
	 TRANSFER_AV_replyInfo	*	pContent	=	(  TRANSFER_AV_replyInfo  *  )p1;
	 //  QY_CFGITEM				*	pItem		=	(  QY_CFGITEM  *  )p2;
	 //  long						lVal;
	 int						tmpLen;
	 char						buf[sizeof(  QY_VIDEO_HEADER  )  +  1024];

	 
	 if  (  !pContent  )  goto  errLabel;
	 
	 if  (  uiStreamId  !=  CONST_imCommType_transferAvReplyInfo  )  goto  errLabel;

	 unsigned  short  tmp_cfgId;
	 memcpy(  &tmp_cfgId,  &pItem->head.cfgId,  sizeof(  short  )  );

	 switch  (  tmp_cfgId  )  {
			 case  CONST_qnmCfgId_start:
				   pContent->uiType  =  uiStreamId;
				   break;
			 case  CONST_qnmCfgId_usOp:
				   if  (  getFieldData_short(  pItem,  (  short  *  )&pContent->usOp  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_tStartTime_org:
				   if  (  getFieldData_l64(  pItem,  (  __int64  *  )&pContent->tStartTime_org  )  )  goto  errLabel;
				   break;
			 case  CONST_qnmCfgId_uiTranNo_org:
				   if  (  getFieldData_long(  pItem,  (  long  *  )&pContent->uiTranNo_org  )  )  goto  errLabel;
				   break;
			 default:
				    if  (  tmp_ntohAvTranInfo(  pItem,  &pContent->tranInfo  )  )  goto  errLabel;
					break;
	 }
	 iErr  =  0;
errLabel:
	 return  iErr;
}






////////////////////////

#if  0	//  2010/07/10
 int  qyhtonRouteTalkData(  MSG_ROUTE  *  pAddr,  char  *  pContentParam,  unsigned  int  lenInBytes_content,  BOOL  bNeedContentConvrted,  unsigned  char  ucFlg,  char  *  buf,  unsigned  int  *puiBufSize,  TCHAR  *  tHintBuf_showInfo,  unsigned  int  uiCnt_tHintBuf_showInfo  ) 
{
	int							iErr									=	-1;
	IM_CONTENTU			*		pContent								=	(  IM_CONTENTU  *  )pContentParam;
	int							lenInBytes;
	char				*		ptr;
	IM_L_STREAM			*		pStream									=	NULL;
	unsigned  int				uiBufSize;
	int							lenInBytes_addr							=	0;
	long						tmp_l;


	if  (  !buf  ||  !puiBufSize  )  return  -1;
	uiBufSize  =  *puiBufSize;

	if  (  isUcFlgRouteTalkData(  ucFlg  )  )  {

		lenInBytes_addr  =  uiBufSize;
		if  (  msgRoute2Stream(  CONST_imCommType_msgRoute,  pAddr,  buf,  (  unsigned  int  *  )&lenInBytes_addr  )  )  goto  errLabel;
		}
	else  if  (  isUcFlgTalkData(  ucFlg  )  )  {		//  仅用来talkData
		  if  (  !pAddr  ||  uiBufSize  <  sizeof(  MSG_SIMPLE_ROUTE  )  )  goto  errLabel;
		  MSG_SIMPLE_ROUTE  *  pTalkDataAddr;
		  pTalkDataAddr  =  (  MSG_SIMPLE_ROUTE  *  )buf;
		  pTalkDataAddr->idInfo_from.ui64Id  =  pAddr->idInfo_from.ui64Id;
		  pTalkDataAddr->idInfo_to.ui64Id  =  pAddr->idInfo_to.ui64Id;
		  //
		  MACRO_htonl64(  pTalkDataAddr->idInfo_from.ui64Id  );
		  MACRO_htonl64(  pTalkDataAddr->idInfo_to.ui64Id  );
		  //
		  lenInBytes_addr  =  sizeof(  MSG_SIMPLE_ROUTE  );		  
	}
	
	//
	ptr  =  buf  +  lenInBytes_addr;
	
	//  要求不转换的		  
	//
	if  (  !bNeedContentConvrted  )  {										
	
		if  (  lenInBytes_content  >  uiBufSize  -  lenInBytes_addr  )  {
			traceLogA(  "lenInBytes_content is too large"  );  goto  errLabel;
		}
		if  (  !pContent  )  lenInBytes  =  lenInBytes_addr;
		else  {
			  memcpy(  ptr,  pContent,  lenInBytes_content  );
			  lenInBytes  =  lenInBytes_addr  +  lenInBytes_content;			
		}		
			
		iErr  =  0;  goto  errLabel;
	}

	if  (  !pContent  )  goto  errLabel;
	
	switch  (  pContent->uiType  )  {
			case  0:  //  允许用一个为0的整形变量来代替。是为了有时方便发个小数据包, 2007/12/11
				  if  (  uiBufSize  -  lenInBytes_addr  <  sizeof(  pContent->uiType  )  )  goto  errLabel;
				  memcpy(  ptr,  &pContent->uiType,  sizeof(  pContent->uiType  )  );
				  MACRO_htonl(  *(  unsigned  int  *  )ptr  );
				  lenInBytes  =  sizeof(  pContent->uiType  );
				  lenInBytes  +=  lenInBytes_addr;
				  iErr  =  0;  goto  errLabel;
				  break;
			case  CONST_imCommType_simpleResp:
				  if  (  uiBufSize  -  lenInBytes_addr  <  sizeof(  IM_SIMPLE_RESP  )  )  goto  errLabel;
				  memcpy(  ptr,  &pContent->simpleResp,  sizeof(  IM_SIMPLE_RESP  )  );
				  if  (  (  lenInBytes  =  qyhtonImSimpleResp(  0,  (  IM_SIMPLE_RESP  *  )ptr  )  )  <  0  )  goto  errLabel; 
				  lenInBytes  +=  lenInBytes_addr;
				  iErr  =  0;  goto  errLabel;
				  break;
			default:
					break;
	}

	//
	pStream  =  (  IM_L_STREAM  *  )ptr;
	if  (  uiBufSize  -  lenInBytes_addr  <  offsetof(  IM_L_STREAM,  buf  )  )  {
		traceLogA(  "qyhtonRouteTalkData failed: buf is too small"  );  goto  errLabel;	//  怕空间不够了
	}
	//  pStream->uiType  =  CONST_imCommType_lStream;
	tmp_l  =  CONST_imCommType_lStream;	memcpy(  &pStream->uiType,  &tmp_l,  sizeof(  long  )  );
	//  pStream->uiContentType  =  pContent->uiType;				   
	memcpy(  &pStream->uiContentType,  &pContent->uiType,  sizeof(  long  )  );
	lenInBytes  =  uiBufSize  -  lenInBytes_addr;		//  sizeof(  pStream->buf  );				
	switch  (  pContent->uiType  )  {
			case  CONST_imCommType_htmlContent:
				  if  (  imHtmlContent2Stream(  pContent->uiType,  &pContent->html,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferFileReq:
				  if  (  transferFileReq2Stream(  pContent->uiType,  &pContent->transferFileReq,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_taskProcReq:
				  if  (  taskProcReq2Stream(  pContent->uiType,  &pContent->taskProcReq,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_taskProcResp:
				  if  (  taskProcResp2Stream(  pContent->uiType,  &pContent->taskProcResp,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferFileReplyReq:
				  if  (  transferFileReplyReq2Stream(  pContent->uiType,  &pContent->transferFileReplyReq,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferFileDataReq:
				  if  (  transferFileDataReq2Stream(  pContent->uiType,  &pContent->transferFileDataReq,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferFileDataResp:
				  if  (  transferFileDataResp2Stream(  pContent->uiType,  &pContent->transferFileDataResp,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferFileEndReq:
				  if  (  transferFileEndReq2Stream(  pContent->uiType,  &pContent->transferFileEndReq,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferFileEndResp:
				  if  (  transferFileEndResp2Stream(  pContent->uiType,  &pContent->transferFileEndResp,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_rtcCallReq:
				  if  (  rtcCallReq2Stream(  pContent->uiType,  &pContent->rtcCallReq,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferAvInfo:
				  if  (  transferAvInfo2Stream(  pContent->uiType,  &pContent->transferAvInfo,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferAvReplyInfo:
				  if  (  transferAvReplyInfo2Stream(  pContent->uiType,  &pContent->transferAvReplyInfo,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferVideoData:
				  if  (  transferVideoData2Stream(  pContent->uiType,  &pContent->transferVideoData,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;  
				  break;
			case  CONST_imCommType_transferVideoDataResp:
				  if  (  transferVideoDataResp2Stream(  pContent->uiType,  &pContent->transferVideoDataResp,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;  
				  break;
			case  CONST_imCommType_transferAudioData:
				  if  (  transferAudioData2Stream(  pContent->uiType,  &pContent->transferAudioData,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;  
				  break;
			case  CONST_imCommType_transferAudioDataResp:
				  if  (  transferAudioDataResp2Stream(  pContent->uiType,  &pContent->transferAudioDataResp,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_remoteAssistReq:
				  if  (  remoteAssistReq2Stream(  pContent->uiType,  &pContent->remoteAssistReq,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_taskInteractionReq:
				  if  (  taskInteractionReq2Stream(  pContent->uiType,  &pContent->taskInteractionReq,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_videoConferenceStatus:
				  if  (  videoConferenceStatus2Stream(  pContent->uiType,  &pContent->videoConferenceStatus,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_refreshWebContactsInfo:
				  if  (  refreshWebContactsInfo2Stream(  pContent->uiType,  &pContent->refreshWebContactsInfo,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_vDevComs:
				  if  (  qyVDevComs2Stream(  pContent->uiType,  &pContent->vDevComs,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_retrieveSmPolicy:
				  if  (  retrieveSmPolicy2Stream(  pContent->uiType,  &pContent->retrieveSmPolicy,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;	  
				  break;
			case  CONST_imCommType_retrievePhoneMsgrs:
				  if  (  retrievePhoneMsgrs2Stream(  pContent->uiType,  &pContent->retrievePhoneMsgrs,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_retrieveToPaths:
				  if  (  retrieveToPaths2Stream(  pContent->uiType,  &pContent->retrieveToPaths,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_refreshDynBmps:
				  if  (  refreshDynBmps2Stream(  pContent->uiType,  &pContent->refreshDynBmps,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_retrieveDynBmps:
				  if  (  retrieveDynBmps2Stream(  pContent->uiType,  &pContent->retrieveDynBmps,  pStream->buf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			default:
				   traceLogA(  "qyhtonRouteTalkData: uiContentType %d can't be supported",  pContent->uiType  );
				   goto  errLabel;
	}
				
	//  pStream->ulStreamLen  =  lenInBytes;
	memcpy(  &pStream->ulStreamLen,  &lenInBytes,  sizeof(  long  )  );
	lenInBytes  +=  offsetof(  IM_L_STREAM,  buf  );

	if  (  (  lenInBytes  =  qyhtonImLStream(  0,  pStream  )  )  ==  -1  )  goto  errLabel;

	lenInBytes  +=  lenInBytes_addr;

	iErr  =  0;
errLabel:
	if  (  !iErr  )  {
		*puiBufSize  =  lenInBytes;
	}
	return  iErr;

}
#endif

 int  qyhtonRouteTalkData(  MSG_ROUTE  *  pAddr,  char  *  pContentParam,  unsigned  int  lenInBytes_content,  BOOL  bNeedContentConvrted,  unsigned  char  ucFlg,  char  *  buf,  unsigned  int  *puiBufSize,  TCHAR  *  tHintBuf_showInfo,  unsigned  int  uiCnt_tHintBuf_showInfo  ) 
{
	int							iErr									=	-1;
	IM_CONTENTU			*		pContent								=	(  IM_CONTENTU  *  )pContentParam;
	int							lenInBytes;
	char				*		ptr;
	//  IM_L_STREAM			*		pStream									=	NULL;
	unsigned  int				uiBufSize;
	int							lenInBytes_addr							=	0;
	//  long						tmp_l;


	if  (  !buf  ||  !puiBufSize  )  return  -1;
	uiBufSize  =  *puiBufSize;

	if  (  isUcFlgRouteTalkData(  ucFlg  )  )  {

		lenInBytes_addr  =  uiBufSize;
		if  (  msgRoute2Stream(  CONST_imCommType_msgRoute,  pAddr,  buf,  (  unsigned  int  *  )&lenInBytes_addr  )  )  goto  errLabel;
		}
	else  if  (  isUcFlgTalkData(  ucFlg  )  )  {		//  仅用来talkData
		  if  (  !pAddr  ||  uiBufSize  <  sizeof(  MSG_SIMPLE_ROUTE  )  )  goto  errLabel;
		  MSG_SIMPLE_ROUTE		talkDataAddr;
		  MSG_SIMPLE_ROUTE  *  pTalkDataAddr	=	&talkDataAddr;
		  //  pTalkDataAddr  =  (  MSG_SIMPLE_ROUTE  *  )buf;
		  pTalkDataAddr->idInfo_from.ui64Id  =  pAddr->idInfo_from.ui64Id;
		  pTalkDataAddr->idInfo_to.ui64Id  =  pAddr->idInfo_to.ui64Id;
		  //
		  MACRO_htonl64(  pTalkDataAddr->idInfo_from.ui64Id  );
		  MACRO_htonl64(  pTalkDataAddr->idInfo_to.ui64Id  );
		  //
		  memcpy(  buf,  pTalkDataAddr,  sizeof(  MSG_SIMPLE_ROUTE  )  );
		  //
		  lenInBytes_addr  =  sizeof(  MSG_SIMPLE_ROUTE  );		  
	}
	
	//
	ptr  =  buf  +  lenInBytes_addr;
	
	//  要求不转换的		  
	//
	if  (  !bNeedContentConvrted  )  {										
	
		if  (  lenInBytes_content  >  uiBufSize  -  lenInBytes_addr  )  {
			traceLogA(  "lenInBytes_content is too large"  );  goto  errLabel;
		}
		if  (  !pContent  )  lenInBytes  =  lenInBytes_addr;
		else  {
			  memcpy(  ptr,  pContent,  lenInBytes_content  );
			  lenInBytes  =  lenInBytes_addr  +  lenInBytes_content;			
		}		
			
		iErr  =  0;  goto  errLabel;
	}

	if  (  !pContent  )  goto  errLabel;
	
	switch  (  pContent->uiType  )  {
			case  0:  {
				  unsigned  int  uiType  =  pContent->uiType;
				  MACRO_htonl(  uiType  );
				  lenInBytes  =  sizeof(  uiType  );
				  if  (  uiBufSize  -  lenInBytes_addr  <  lenInBytes  )  goto  errLabel;
				  memcpy(  ptr,  &uiType,  lenInBytes  );
				  lenInBytes  +=  lenInBytes_addr;
				  iErr  =  0;  goto  errLabel;
				  }
				  break;
			case  CONST_imCommType_simpleResp:  {
				  IM_SIMPLE_RESP	simpleResp;
				  memcpy(  &simpleResp,  &pContent->simpleResp,  sizeof(  simpleResp  )  );
				  if  (  (  lenInBytes  =  qyhtonImSimpleResp(  0,  &simpleResp  )  )  <  0  )  goto  errLabel; 
				  if  (  uiBufSize  -  lenInBytes_addr  <  lenInBytes  )  goto  errLabel;
				  memcpy(  ptr,  &simpleResp,  lenInBytes  );
				  lenInBytes  +=  lenInBytes_addr;
				  iErr  =  0;  goto  errLabel;
				  }
				  break;
			default:
					break;
	}

	//
	IM_L_STREAM_nh				stream_hton;
	char				*		stream_pBuf								=	NULL;
	//  pStream  =  (  IM_L_STREAM  *  )ptr;

	if  (  uiBufSize  -  lenInBytes_addr  <  offsetof(  IM_L_STREAM,  buf  )  )  {
		traceLogA(  "qyhtonRouteTalkData failed: buf is too small"  );  goto  errLabel;	//  怕空间不够了
	}
	memset(  &stream_hton,  0,  offsetof(  IM_L_STREAM,  buf  )  );
	stream_hton.uiType  =  CONST_imCommType_lStream;
	stream_hton.uiContentType  =  pContent->uiType;	
	stream_pBuf  =  ptr  +  offsetof( IM_L_STREAM,  buf  );
	lenInBytes  =  uiBufSize  -  lenInBytes_addr;		//  sizeof(  pStream->buf  );				
	switch  (  pContent->uiType  )  {
			case  CONST_imCommType_htmlContent:
				  if  (  imHtmlContent2Stream(  pContent->uiType,  &pContent->html,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferFileReq:
				  if  (  transferFileReq2Stream(  pContent->uiType,  &pContent->transferFileReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_taskProcReq:
				  if  (  taskProcReq2Stream(  pContent->uiType,  &pContent->taskProcReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_taskProcResp:
				  if  (  taskProcResp2Stream(  pContent->uiType,  &pContent->taskProcResp,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferFileReplyReq:
				  if  (  transferFileReplyReq2Stream(  pContent->uiType,  &pContent->transferFileReplyReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferFileDataReq:
				  if  (  transferFileDataReq2Stream(  pContent->uiType,  &pContent->transferFileDataReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferFileDataResp:
				  if  (  transferFileDataResp2Stream(  pContent->uiType,  &pContent->transferFileDataResp,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferFileEndReq:
				  if  (  transferFileEndReq2Stream(  pContent->uiType,  &pContent->transferFileEndReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferFileEndResp:
				  if  (  transferFileEndResp2Stream(  pContent->uiType,  &pContent->transferFileEndResp,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_rtcCallReq:
				  if  (  rtcCallReq2Stream(  pContent->uiType,  &pContent->rtcCallReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferAvInfo:
				  if  (  transferAvInfo2Stream(  pContent->uiType,  &pContent->transferAvInfo,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferAvReplyInfo:
				  if  (  transferAvReplyInfo2Stream(  pContent->uiType,  &pContent->transferAvReplyInfo,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferVideoData:
				  if  (  transferVideoData2Stream(  pContent->uiType,  &pContent->transferVideoData,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;  
				  break;
			case  CONST_imCommType_transferVideoDataResp:
				  if  (  transferVideoDataResp2Stream(  pContent->uiType,  &pContent->transferVideoDataResp,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;  
				  break;
			case  CONST_imCommType_transferAudioData:
				  if  (  transferAudioData2Stream(  pContent->uiType,  &pContent->transferAudioData,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;  
				  break;
			case  CONST_imCommType_transferAudioDataResp:
				  if  (  transferAudioDataResp2Stream(  pContent->uiType,  &pContent->transferAudioDataResp,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_remoteAssistReq:
				  if  (  remoteAssistReq2Stream(  pContent->uiType,  &pContent->remoteAssistReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_taskInteractionReq:
				  if  (  taskInteractionReq2Stream(  pContent->uiType,  &pContent->taskInteractionReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_videoConferenceStatus:
				  if  (  videoConferenceStatus2Stream(  pContent->uiType,  &pContent->videoConferenceStatus,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_videoConferenceLayout:
				  if  (  videoConferenceLayout2Stream(  pContent->uiType,  &pContent->videoConferenceLayout,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_refreshWebContactsInfo:
				  if  (  refreshWebContactsInfo2Stream(  pContent->uiType,  &pContent->refreshWebContactsInfo,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_vDevComs:
				  if  (  qyVDevComs2Stream(  pContent->uiType,  &pContent->vDevComs,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_retrieveSmPolicy:
				  if  (  retrieveSmPolicy2Stream(  pContent->uiType,  &pContent->retrieveSmPolicy,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;	  
				  break;
			case  CONST_imCommType_retrievePhoneMsgrs:
				  if  (  retrievePhoneMsgrs2Stream(  pContent->uiType,  &pContent->retrievePhoneMsgrs,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_getCfgsReq:	//  2011/01/30
				  if  (  qisGetCfgsReq2Stream(  pContent->uiType,  &pContent->getCfgsReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_retrieveToPaths:
				  if  (  retrieveToPaths2Stream(  pContent->uiType,  &pContent->retrieveToPaths,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_refreshDynBmps:
				  if  (  refreshDynBmps2Stream(  pContent->uiType,  &pContent->refreshDynBmps,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_verifyViewDynBmp:	//  2011/10/31
				  if  (  verifyViewDynBmp2Stream(  pContent->uiType,  &pContent->verifyViewDynBmp,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_retrieveDynBmps:
				  if  (  retrieveDynBmps2Stream(  pContent->uiType,  &pContent->retrieveDynBmps,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_getDaemonStatusReq:	//  2011/01/09
				  if  (  getDaemonStatusReq2Stream(  pContent->uiType,  &pContent->getDaemonStatusReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_queryCustomerServiceOfficerReq:	//  2011/04/06
				  if  (  queryCustomerServiceOfficerReq2Stream(  pContent->uiType,  &pContent->queryCustomerServiceOfficerReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_queryCustomerServiceOfficerReplyReq:	//  2011/04/06
				  if  (  queryCustomerServiceOfficerReplyReq2Stream(  pContent->uiType,  &pContent->queryCustomerServiceOfficerReplyReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;
				  break;
			case  CONST_imCommType_transferGpsInfo:  //  2012/04/20
				  if  (  transferGpsInfo2Stream(  pContent->uiType,  &pContent->transferGpsInfo,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;  
				  break;
			case  CONST_imCommType_transferGpsReplyInfo:	//  2012/04/20
				  if  (  transferGpsReplyInfo2Stream(  pContent->uiType,  &pContent->transferGpsReplyInfo,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;  
				  break;
			case  CONST_imCommType_transferGpsData:
				  if  (  transferGpsData2Stream(  pContent->uiType,  &pContent->transferGpsData,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;  
				  break;
			case  CONST_imCommType_transferGpsDataResp:
				  if  (  transferGpsDataResp2Stream(  pContent->uiType,  &pContent->transferGpsDataResp,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;  
				  break;				  
			case  CONST_imCommType_ptzControlReq:	//  2012/08/05
				  if  (  ptzControlReq2Stream(  pContent->uiType,  &pContent->ptzControlReq,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;  
				  break;
			case  CONST_imCommType_ptzControlCmd:	//  2012/08/05
				  if  (  ptzControlCmd2Stream(  pContent->uiType,  &pContent->ptzControlCmd,  stream_pBuf,  (  unsigned  int  *  )&lenInBytes  )  )  goto  errLabel;  
				  break;
				  //
			default:
				   #ifdef  __DEBUG__
						   traceLog(  _T(  "qyhtonRouteTalkData: uiContentType %d can't be supported"  ),  pContent->uiType  );
				   #endif
				   goto  errLabel;
	}
				
	stream_hton.ulStreamLen  =  lenInBytes;
	lenInBytes  +=  offsetof(  IM_L_STREAM,  buf  );

	if  (  (  lenInBytes  =  qyhtonImLStream(  0,  (  IM_L_STREAM  *  )&stream_hton  )  )  ==  -1  )  goto  errLabel;
	memcpy(  ptr,  &stream_hton,  offsetof(  IM_L_STREAM,  buf  )  );

	lenInBytes  +=  lenInBytes_addr;

	iErr  =  0;
errLabel:
	if  (  !iErr  )  {
		*puiBufSize  =  lenInBytes;
	}
	return  iErr;

}



 //  其中ucFlg用来表示要转换成talkData或addrTalkData
 int  qyntohRouteTalkData(  unsigned  char  ucFlg,  char  *  data,  unsigned  int  dataLen,  MSG_ROUTE  *  pAddr,  IM_CONTENTU  *  pContent,  TCHAR  *  tHintBuf_showInfo,  unsigned  int  uiCnt_tHintBuf_showInfo  ) 
{
	int							iErr									=	-1;
	int							lenInBytes;
	char				*		ptr;
	unsigned  int				size;
	TCHAR						tHintBuf[255  +  1]						=	_T(  ""  );
	unsigned  int				uiType									=	0;
	unsigned  int				uiContentType							=	0;
	
	if  (  !data  ||  !pContent  )  return  -1;

	if  (  isUcFlgRouteTalkData(  ucFlg  )  )  {
		 //
		 if  (  !pAddr  )  goto  errLabel;
		 memset(  pAddr,  0,  sizeof(  pAddr[0]  )  );
		 //
		 ptr  =  data;
		 size  =  dataLen;
		 //
		 if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2MsgRoute,  0,  pAddr  )  )  {
			 OutputDebugString(  _T(  "qyntohRouteTalkData: stream2Data 1 failed.\n"  )  );
			 goto  errLabel;      
		 }
		 //  剩下的size就是pStream
		}
	else  if  (  isUcFlgTalkData(  ucFlg  )  )  {		//  仅用来talkData
		      if  (  !pAddr  )  goto  errLabel;
			  memset(  pAddr,  0,  sizeof(  pAddr[0]  )  );
			  if  (  dataLen  <  sizeof(  MSG_SIMPLE_ROUTE  )  )  goto  errLabel;

			  MSG_SIMPLE_ROUTE		*		pTalkDataAddr;
			  int							lenInBytes_addr;

			  pTalkDataAddr  =  (  MSG_SIMPLE_ROUTE  *  )data;
			  pAddr->idInfo_from.ui64Id  =  pTalkDataAddr->idInfo_from.ui64Id;
			  pAddr->idInfo_to.ui64Id  =  pTalkDataAddr->idInfo_to.ui64Id;
			  //
			  MACRO_ntohl64(  pAddr->idInfo_from.ui64Id  );
			  MACRO_ntohl64(  pAddr->idInfo_to.ui64Id  );
			  //
			  lenInBytes_addr  =  sizeof(  MSG_SIMPLE_ROUTE  );		  
			  //
			  ptr  =  data  +  lenInBytes_addr;
			  size  =  dataLen  -  lenInBytes_addr;
			  }
	else  {
		  //  这里是没有addr的数据
		  ptr  =  data;
		  size  =  dataLen;
	}
	
	//
	//
	//  这里应该做一个将contentU转换guo来的工作。
	//  注意：在qyMc里，有所有的input的数据转换时，都要修改
	//  另外：要特别注意和老程序的通信的兼容性。老程序的talk和task等结构都是用MIS_MSG_TALKDATA发的。
	//

	if  (  size  <  sizeof(   uiType  )  )  goto  errLabel; 

	//  uiType  =  qyntohl(  (  (  IM_CONTENTU  *  )ptr  )->uiType  );
	//  memcpy(  &uiType,  &(  (  IM_CONTENTU  *  )ptr  )->uiType,  sizeof(  uiType  )  );
	memcpy(  &uiType,  ptr,  sizeof(  uiType  )  );
	MACRO_ntohl(  uiType  );
	switch  (  uiType  )  {
			case  0:
				  if  (  size  <  sizeof(  pContent->uiType  )  )  goto  errLabel;
				  memcpy(  &pContent->uiType,  ptr,  sizeof(  pContent->uiType  )  );
				  MACRO_ntohl(  pContent->uiType  );
				  lenInBytes  =  sizeof(  pContent->uiType  );
				  iErr  =  0;  goto  errLabel;
				  break;
		    case  CONST_imCommType_simpleResp:
				  if  (  size  <  sizeof(  IM_SIMPLE_RESP  )  )  goto  errLabel;
				  memcpy(  &pContent->simpleResp,  ptr,  sizeof(  pContent->simpleResp  )  );
				  if  (  (  lenInBytes  =  qyntohImSimpleResp(  0,  &pContent->simpleResp  )  )  <  0  )  goto  errLabel; 
				  iErr  =  0;  goto  errLabel;
				  break;
			case  CONST_imCommType_refreshRecentFriendsReq:
				  //
				  memcpy(  &pContent->refreshRecentFriendsReq,  ptr,  min(  size,  sizeof(  pContent->refreshRecentFriendsReq  )  )  );
				  if  (  (  lenInBytes  =  qyntohRefreshRecentFriendsReq(  0,  &pContent->refreshRecentFriendsReq  )  )  <  0  )  goto  errLabel;
				  iErr  =  0;  goto  errLabel;
			default:
					break;
	}

#if  0	//  2011/01/29
	if  (  uiType  ==  CONST_imCommType_streamContent  )  {

		IM_STREAM_CONTENT_nh			stream_ntoh;
		IM_STREAM_CONTENT_nh	*		pStream		=	&stream_ntoh;

		//  pStream  =  (  IM_STREAM_CONTENT  *  )ptr;

		if  (  (  lenInBytes  =  qyntohImStreamContent(  0,  ptr,  pStream  )  )  <  0  )  goto  errLabel;

		if  (  size  <  (  unsigned  int  )lenInBytes  )  goto  errLabel;

		ptr  =  pStream->p;
		size  =  pStream->usStreamLen;

		if  (  size  <  offsetof(  IM_STREAM_CONTENT,  buf  )  )  goto  errLabel;

		uiContentType  =  pStream->uiContentType;

		}
	else
#endif
		if  (  uiType  ==  CONST_imCommType_lStream  )  {
		      //
			  IM_L_STREAM_nh				stream_ntoh;
			  IM_L_STREAM_nh		*		pStream			=	&stream_ntoh;

			  //  pStream  =  (  IM_L_STREAM  *  )ptr;

			  if  (  (  lenInBytes  =  qyntohImLStream(  0,  ptr,  pStream  )  )  <  0  )  goto  errLabel;

			  if  (  size  <  (  unsigned  int  )lenInBytes  )  goto  errLabel;

			  ptr  =  pStream->p;
			  //  size  =  pStream->ulStreamLen;
			  memcpy(  &size,  &pStream->ulStreamLen,  sizeof(  long  )  );

			  if  (  size  <  offsetof(  IM_L_STREAM,  buf  )  )  goto  errLabel;

			  //  uiContentType  =  pStream->uiContentType;
			  memcpy(  &uiContentType,  &pStream->uiContentType,  sizeof(  long  )  );
		}
	else  {
  		  traceLogA(  "qyntohRouteTalkData 得到了非长流的数据包, uiType %d, size %d",  uiType,  size  );
		  goto  errLabel;
	}
	
	{
		switch  (  uiContentType  )  {
				case  CONST_imCommType_htmlContent:
					  memset(  &pContent->html,  0,  sizeof(  pContent->html  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2ImHtmlContent,  0,  pContent  )  )  goto  errLabel;  
					  break;
				case  CONST_imCommType_refreshRecentFriendsResp:
					  memset(  &pContent->refreshRecentFriendsResp,  0,  sizeof(  pContent->refreshRecentFriendsResp  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RefreshRecentFriendsResp,  0,  pContent  )  )  {		//  这里，对万一有数据包下发不完整的情况下，做截断处理。不简单退出
						  //  
						  //  qyShowInfo(  CONST_qyShowType_qwmComm,  (  ""  ),  _T(  ""  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "    stream2Data failed, usCnt is %d, 截断处理"  ),  pContent->refreshRecentFriendsResp.usCnt  );
						  _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "stream2Data failed, usCnt is %d, 截断处理"  ),  pContent->refreshRecentFriendsResp.usCnt  );
						  //
						  if  (  pContent->refreshRecentFriendsResp.usCnt_mems  )  pContent->refreshRecentFriendsResp.usCnt_mems  --  ;	//  因为最后一个包不完整，所以要去掉
						  pContent->refreshRecentFriendsResp.usCnt  =  pContent->refreshRecentFriendsResp.usCnt_mems;
						  //
					  }
					  if  (  pContent->refreshRecentFriendsResp.usCnt  >  mycountof(  pContent->refreshRecentFriendsResp.mems  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_getCfgsReq:
					  //  memset(  &pContent->intervalParams,  0,  sizeof(  pContent->intervalParams  )  );
					  memset(  &pContent->getCfgsReq,  0,  sizeof(  pContent->getCfgsReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2QisGetCfgsReq,  0,  pContent  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_retrieveImGrpListResp:
					  memset(  &pContent->retrieveImGrpListResp,  0,  sizeof(  pContent->retrieveImGrpListResp  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RetrieveImGrpListResp,  0,  &pContent->retrieveImGrpListResp  )  )  goto  errLabel;
					  if  (  pContent->retrieveImGrpListResp.usCnt  >  mycountof(  pContent->retrieveImGrpListResp.mems  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_retrieveImGrpMemListResp:
					  memset(  &pContent->retrieveImGrpMemListResp,  0,  sizeof(  pContent->retrieveImGrpMemListResp  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RetrieveImGrpMemListResp,  0,  &pContent->retrieveImGrpMemListResp  )  )  goto  errLabel;
					  if  (  pContent->retrieveImGrpMemListResp.usCnt  >  mycountof(  pContent->retrieveImGrpMemListResp.mems  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_retrieveContactListResp:
					  memset(  &pContent->retrieveContactListResp,  0,  sizeof(  pContent->retrieveContactListResp  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RetrieveContactListResp,  0,  &pContent->retrieveContactListResp  )  )  goto  errLabel;
					  if  (  pContent->retrieveContactListResp.usCnt  >  mycountof(  pContent->retrieveContactListResp.mems  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_retrieveImObjListEndResp:
					  memset(  &pContent->retrieveImObjListEndResp,  0,  sizeof(  pContent->retrieveImObjListEndResp  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RetrieveImObjListEndResp,  0,  &pContent->retrieveImObjListEndResp  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferFileReq:
					  memset(  &pContent->transferFileReq,  0,  sizeof(  pContent->transferFileReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferFileReq,  0,  &pContent->transferFileReq  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferFileReplyReq:
					  memset(  &pContent->transferFileReplyReq,  0,  sizeof(  pContent->transferFileReplyReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferFileReplyReq,  0,  &pContent->transferFileReplyReq  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_taskProcReq:
					  memset(  &pContent->taskProcReq,  0,  sizeof(  pContent->taskProcReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TaskProcReq,  0,  &pContent->taskProcReq  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_taskProcResp:
					  memset(  &pContent->taskProcResp,  0,  sizeof(  pContent->taskProcResp  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TaskProcResp,  0,  &pContent->taskProcResp  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferFileDataReq:
					  memset(  &pContent->transferFileDataReq,  0,  sizeof(  pContent->transferFileDataReq  )  );	
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferFileDataReq,  0,  &pContent->transferFileDataReq  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferFileDataResp:
					  memset(  &pContent->transferFileDataResp,  0,  offsetof(  TRANSFER_FILEDATA_RESP,  buf  )  );	//  把控制数据清空即可
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferFileDataResp,  0,  &pContent->transferFileDataResp  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferFileEndReq:
					  memset(  &pContent->transferFileEndReq,  0,  sizeof(  pContent->transferFileEndReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferFileEndReq,  0,  &pContent->transferFileEndReq  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_rtcCallReq:
					  memset(  &pContent->rtcCallReq,  0,  sizeof(  pContent->rtcCallReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RtcCallReq,  0,  &pContent->rtcCallReq  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferAvInfo:
					  memset(  &pContent->transferAvInfo,  0,  sizeof(  pContent->transferAvInfo  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferAvInfo,  0,  &pContent->transferAvInfo  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferAvReplyInfo:
					  memset(  &pContent->transferAvReplyInfo,  0,  sizeof(  pContent->transferAvReplyInfo  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferAvReplyInfo,  0,  &pContent->transferAvReplyInfo  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferVideoData:
					  memset(  &pContent->transferVideoData,  0,  offsetof(  TRANSFER_VIDEO_DATA,  buf  )  );  //  这里，把控制数据清空即可。
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferVideoData,  0,  &pContent->transferVideoData  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferVideoDataResp:
					  memset(  &pContent->transferVideoDataResp,  0,  sizeof(  pContent->transferVideoDataResp  )  );  //  这里，把控制数据清空即可。
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferVideoDataResp,  0,  &pContent->transferVideoDataResp  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferAudioData:
					  memset(  &pContent->transferAudioData,  0,  offsetof(  TRANSFER_AUDIO_DATA,  buf  )  );  //  这里，把控制数据清空即可。
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferAudioData,  0,  &pContent->transferAudioData  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferAudioDataResp:
					  memset(  &pContent->transferAudioDataResp,  0,  sizeof(  pContent->transferAudioDataResp  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferAudioDataResp,  0,  &pContent->transferAudioDataResp  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_remoteAssistReq:
					  memset(  &pContent->remoteAssistReq,  0,  sizeof(  pContent->remoteAssistReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RemoteAssistReq,  0,  &pContent->remoteAssistReq  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_taskInteractionReq:
					  memset(  &pContent->taskInteractionReq,  0,  sizeof(  pContent->taskInteractionReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TaskInteractionReq,  0,  &pContent->taskInteractionReq  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_videoConferenceStatus:
					  memset(  &pContent->videoConferenceStatus,  0,  sizeof(  pContent->videoConferenceStatus  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2VideoConferenceStatus,  0,  &pContent->videoConferenceStatus  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_videoConferenceLayout:
					  memset(  &pContent->videoConferenceLayout,  0,  sizeof(  pContent->videoConferenceLayout  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2VideoConferenceLayout,  0,  &pContent->videoConferenceLayout  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_refreshWebContactsInfo:
					  memset(  &pContent->refreshWebContactsInfo,  0,  sizeof(  pContent->refreshWebContactsInfo  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RefreshWebContactsInfo,  0,  &pContent->refreshWebContactsInfo  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_vDevComs:
					  memset(  &pContent->vDevComs,  0,  sizeof(  pContent->vDevComs  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2QyVDevComs,  0,  &pContent->vDevComs  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_retrieveSmPolicy:
					  memset(  &pContent->retrieveSmPolicy,  0,  sizeof(  pContent->retrieveSmPolicy  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RetrieveSmPolicy,  0,  &pContent->retrieveSmPolicy  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_retrievePhoneMsgrs:
					  memset(  &pContent->retrievePhoneMsgrs,  0,  sizeof(  pContent->retrievePhoneMsgrs  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RetrievePhoneMsgrs,  0,  &pContent->retrievePhoneMsgrs  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_retrieveToPaths:
					  memset(  &pContent->retrieveToPaths,  0,  sizeof(  pContent->retrieveToPaths  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RetrieveToPaths,  0,  &pContent->retrieveToPaths  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_refreshDynBmps:
					  memset(  &pContent->refreshDynBmps,  0,  sizeof(  pContent->refreshDynBmps  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RefreshDynBmps,  0,  &pContent->refreshDynBmps  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_verifyViewDynBmp:	//  2011/10/31
					  memset(  &pContent->verifyViewDynBmp,  0,  sizeof(  pContent->verifyViewDynBmp  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2VerifyViewDynBmp,  0,  &pContent->verifyViewDynBmp  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_retrieveDynBmps:
					  memset(  &pContent->retrieveDynBmps,  0,  sizeof(  pContent->retrieveDynBmps  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RetrieveDynBmps,  0,  &pContent->retrieveDynBmps  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_refreshImObjRulesReq:	//  2010/08/15
					  memset(  &pContent->refreshImObjRulesReq,  0,  sizeof(  pContent->refreshImObjRulesReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RefreshImObjRulesReq,  0,  &pContent->refreshImObjRulesReq  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_getDaemonStatusReq:		//  2011/01/09
					  memset(  &pContent->getDaemonStatusReq,  0,  sizeof(  pContent->getDaemonStatusReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2GetDaemonStatusReq,  0,  &pContent->getDaemonStatusReq  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_retrieveCustomerServiceObjListReq:	//  2011/04/04
					  memset(  &pContent->retrieveCustomerServiceObjListReq,  0,  sizeof(  pContent->retrieveCustomerServiceObjListReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2RetrieveCustomerServiceObjListReq,  0,  &pContent->retrieveCustomerServiceObjListReq  )  )  goto  errLabel;				  
					  break;
				case  CONST_imCommType_queryCustomerServiceOfficerReq:		//  2011/04/06
					  memset(  &pContent->queryCustomerServiceOfficerReq,  0,  sizeof(  pContent->queryCustomerServiceOfficerReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2QueryCustomerServiceOfficerReq,  0,  &pContent->queryCustomerServiceOfficerReq  )  )  goto  errLabel;				  					  
					  break;
				case  CONST_imCommType_queryCustomerServiceOfficerReplyReq:		//  2011/04/06
					  memset(  &pContent->queryCustomerServiceOfficerReplyReq,  0,  sizeof(  pContent->queryCustomerServiceOfficerReplyReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2QueryCustomerServiceOfficerReplyReq,  0,  &pContent->queryCustomerServiceOfficerReplyReq  )  )  goto  errLabel;				  					  
					  break;
				case  CONST_imCommType_transferGpsInfo:		//  2012/04/20
					  memset(  &pContent->transferGpsInfo,  0,  sizeof(  pContent->transferGpsInfo  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferGpsInfo,  0,  &pContent->transferGpsInfo  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferGpsReplyInfo:
					  memset(  &pContent->transferGpsReplyInfo,  0,  sizeof(  pContent->transferGpsReplyInfo  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferGpsReplyInfo,  0,  &pContent->transferGpsReplyInfo  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferGpsData:
					  memset(  &pContent->transferGpsData,  0,  sizeof(  pContent->transferGpsData  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferGpsData,  0,  &pContent->transferGpsData  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_transferGpsDataResp:
					  memset(  &pContent->transferGpsDataResp,  0,  sizeof(  pContent->transferGpsDataResp  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2TransferGpsDataResp,  0,  &pContent->transferGpsDataResp  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_ptzControlReq:
					  memset(  &pContent->ptzControlReq,  0,  sizeof(  pContent->ptzControlReq  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2PtzControlReq,  0,  &pContent->ptzControlReq  )  )  goto  errLabel;
					  break;
				case  CONST_imCommType_ptzControlCmd:
					  memset(  &pContent->ptzControlCmd,  0,  sizeof(  pContent->ptzControlCmd  )  );
					  if  (  stream2Data(  &ptr,  &size,  filterStream_is,  tmpHandler_stream2PtzControlCmd,  0,  &pContent->ptzControlCmd  )  )  goto  errLabel;
					  break;

				default:
					   #ifdef  __DEBUG__
							   traceLog(  _T(  "qyntohRouteTalkData failed: uiContentType %d %s, error"  ),  uiContentType,  qyGetDesByType1(  CONST_qyCommTypeTable_en,  uiContentType  )  );  
					   #endif
					   goto  errLabel;	
			}

			iErr  =  0;  goto  errLabel;
	}
			

	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		//  _sntprintf(  tHintBuf,  mycountof(  tHintBuf  ),  _T(  "%scontentType [%s]"  ),  tHintBuf,  qyGetDesByType1(  CONST_qyCommTypeTable,  uiContentType  )  );
		traceLogA(  "qyntohAddrTalkData failed"  );
	}
	if  (  !iErr  )  {
	}
	//
	if  (  tHintBuf_showInfo  )  lstrcpyn(  tHintBuf_showInfo,  tHintBuf,  uiCnt_tHintBuf_showInfo  );

	return  iErr;

}




