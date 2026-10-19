

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qmcVideoCapture.h"
#include	"qyAvRecordPublic.h"
#include	"qyDynLib.h"

#include	<dbt.h>
#include	<mmreg.h>
#include	<msacm.h>
#ifndef  __WINCE__
	#include	<fcntl.h>
	#include	<io.h>
#endif
#include	<stdio.h>
#include	<commdlg.h>
#include	<strsafe.h>

#include	<dshow.h>

#ifndef  __WINCE__
	//  #include	<Qedit.h>
	#include	"myQedit.h"
#endif
#include	<Mediaobj.h>
#include	<Dmo.h>


#include	<dvdmedia.h>


#include	"qmcDmo.h"
#include	"qmcVideoCapture.h"
#ifndef  __WINCE__
	#include	"qmcVideoCapture_dx.h"
#endif

#include	"qyDynLib.h"

#include	"mywmcodecconst.h"
#include	"mywmcodeciface.h"
#include	"myfourcc.h"

#include	"qyAvRecord.h"
#include	"qyAvRecord_dx.h"

#include	"qySampleGrabberPublic.h"



QY_DMITEM  CONST_mediaSubtypeTable[] =  { 
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_RGB1,			L"RGB Monochrome",   },
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_RGB4,			L"RGB VGA",          },
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_RGB8,			L"RGB 8",            },
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_RGB565,			L"RGB 565 (16 bit)", },
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_RGB555,			L"RGB 555 (16 bit)", },
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_RGB24,			L"RGB 24",           },
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_RGB32,			L"RGB 32",			},
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_ARGB32,			L"ARGB 32",			},
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_Overlay,		L"Overlay",          },
	//
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_I420,		L"I420",				},
	//  {	0,	(  TCHAR  *  )&MEDIASUBTYPE_IYUV,			L"IYUV",				},
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_YV12,			L"YV12",				},
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_NV11,			L"NV11",				},
	//  {	0,	(  TCHAR  *  )&MEDIASUBTYPE_NV12,			L"NV12",				},
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_YUY2,			L"YUY2",				},
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_YVYU,			L"YVYU",				},
	//	
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_UYVY,			L"UYVY",				},
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_HDYC,			L"HDYC",				},	//  2012/01/03
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_v210,			L"v210",				},	//  2012/02/23
	//
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_VIDEOIMAGE,	L"VIDEOIMAGE",		},
	//
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_MJPG,			L"MJPG",			},
	//
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_MSS1,		L"MSS1",			},
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_MSS2,		L"MSS2",			},
	//
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_WMV1,		L"WMV1",			},
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_WMV2,		L"WMV2",			},
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_WMV3,		L"WMV3",			},
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_WMVA,		L"WMVA",			},
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_WMVP,		L"WMVP",			},
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_WMVR,			L"WMVR",			},
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_WVC1,			L"WVC1",			},
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_WVP2,			L"WVP2",			},

	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_Line21_VBIRawData,	L"Line21_VBIRawData",	},
	//
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_PCM,			L"PCM",				},

	//
	{	0,	(  TCHAR  *  )&MEDIASUBTYPE_WAVE,			L"WAVE",			},
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_MSA1,		L"MSA1",			},
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_WMA9,		L"WMA9",			},
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_WMA9Pro,		L"WMA9Pro",			},
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_WMA9Lossless,L"WMA9Lossless",	},
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_WMA9Voice,	L"WMA9Voice",		},

	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_ADPCM,		L"ADPCM",			},
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_GSM610,		L"GSM610",			},
	{	0,	(  TCHAR  *  )&WMCMEDIASUBTYPE_MP3,			L"MP3",				},


	{	-1, NULL,	},
};

 TCHAR  *  getMediaTypeName(  GUID  &  clsid  )
 {
	 if  (  clsid  ==  MEDIATYPE_Video  )  return  _T(  "Video"  );
	 if  (  clsid  ==  MEDIATYPE_Audio  )  return  _T(  "Audio"  );
	 return  _T(  "Unknown mediaType"  );
 }

 TCHAR  *  getMediaSubtypeName(  GUID  &  clsid  )
{
	QY_DMITEM	*	pItem;
	for  (  pItem  =  CONST_mediaSubtypeTable;  pItem->type  !=  -1;  pItem  ++  )  {
		 if  (  *(  GUID  *  )pItem->des  ==  clsid  )  return  pItem->pData;
	}
	return  _T(  ""  );		//  _T(  "Unknown subtype"  );
}

 int  getMediaSubtypeByName(  LPCTSTR  name,  GUID  *  pclsid  )
{
	QY_DMITEM  *  pItem;
	for  (  pItem  =  CONST_mediaSubtypeTable;  pItem->type  !=  -1;  pItem  ++  )  {
		if  (  !_tcsicmp(  name,  pItem->pData  )  )  {
			*pclsid  =  *(  GUID  *  )pItem->des;
			return  0;
		}
	}
	return  -1;
}

 TCHAR  *  getFormatTypeName(  GUID  &  clsid  )
 {
	 if  (  clsid  ==  FORMAT_VideoInfo  )  return  _T(  "Format_video"  );
	 if  (  clsid  ==  FORMAT_VideoInfo2  )  return  _T(  "Format_video2"  );
	 if  (  clsid  ==  FORMAT_WaveFormatEx  )  return  _T(  "Format_wave"  );
	 if  (  clsid  ==  GUID_NULL  )  return  _T(  "Format_null"  );
	 return  _T(  "Unknown format"  );
 }


