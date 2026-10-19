
#include	<windows.h>
#include	<ras.h>
#include	<raserror.h>
#include	<iphlpapi.h>
#include	<tchar.h>
#include	"qyCommon.h"
#include	"asrWMon.h"
#include	"qyTCharCommProc.h"


 extern  "C"  int  qwmLogRasEvent(  void  *  pSubThreadInfoParam,  int  eventType,  RAS_CONN_INFO  *  pRasConnInfo  )
{
	 QWM_EVENT  event;

	 memset(  &event,  0,  sizeof(  event  )  );
	 event.iCustomId  =  qyGetCustomId(  );
	 event.eventType  =  eventType;
	 getCurTime(  event.localEventTime  );				
	 event.u.ras.ucRasCmd  =  pRasConnInfo->ucRasCmd;

	 TCHAR	tBuf[256]  =  _T(  ""  );
#if  0
	 wsprintf(  (  char  *  )event.u.ras.fullPhoneNum,  "%d",  pRasConnInfo->dwCountryCode  );
	 lstrcpyn(  (  char  *  )(  event.u.ras.fullPhoneNum  +  lstrlen(  (  const  char  *  )event.u.ras.fullPhoneNum  )  ),  pRasConnInfo->szAreaCode,  sizeof(  event.u.ras.fullPhoneNum  )  -  lstrlen(  (  const  char  *  )event.u.ras.fullPhoneNum  )  );
	 lstrcpyn(  (  char  *  )(  event.u.ras.fullPhoneNum  +  lstrlen(  (  const  char  *  )event.u.ras.fullPhoneNum  )  ),  " ",  sizeof(  event.u.ras.fullPhoneNum  )  -  lstrlen(  (  const  char  *  )event.u.ras.fullPhoneNum  )  );
	 lstrcpyn(  (  char  *  )(  event.u.ras.fullPhoneNum  +  lstrlen(  (  const  char  *  )event.u.ras.fullPhoneNum  )  ),  pRasConnInfo->szLocalPhoneNumber,  sizeof(  event.u.ras.fullPhoneNum  )  -  lstrlen(  (  const  char  *  )event.u.ras.fullPhoneNum  )  );
#endif
	 if  (  pRasConnInfo->dwCountryCode  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%d"  ),  pRasConnInfo->dwCountryCode  );
	 safeTcsnCpy(  pRasConnInfo->szAreaCode,  tBuf  +  lstrlen(  tBuf  ),  mycountof(  tBuf  )  -  lstrlen(  tBuf  )  );
	 lstrcpyn(  tBuf  +  lstrlen(  tBuf  ),  _T(  " "  ),  mycountof(  tBuf  )  -  lstrlen(  tBuf  )  );
	 safeTcsnCpy(  pRasConnInfo->szLocalPhoneNumber,  tBuf  +  lstrlen(  tBuf  ),  mycountof(  tBuf  )  -  lstrlen(  tBuf  )  );
	 //
	 tTrim(  tBuf  );
	 lstrcpyn(  tBuf  +  lstrlen(  tBuf  ),  _T(  " "  ),  mycountof(  tBuf  )  -  lstrlen(  tBuf  )  );
	 safeTcsnCpy(  pRasConnInfo->szEntryName,  tBuf  +  lstrlen(  tBuf  ),  mycountof(  tBuf  )  -  lstrlen(  tBuf  )  );
	 //
	 myTChar2Utf8(  tBuf,  (  char  *  )event.u.ras.fullPhoneNum,  mycountof(  event.u.ras.fullPhoneNum  )  );
	
	 //  2010/05/21
	 event.ucbUtf8  =  TRUE;

	 return  qwmLogEvent(  pSubThreadInfoParam,  &event  );

}

 extern  "C"  int  qwmLogOnInternetEvent(  void  *  pSubThreadInfoParam,  int  eventType,  char  *  timeBuf  )
{
	 QWM_EVENT  event;

	 memset(  &event,  0,  sizeof(  event  )  );
	 event.iCustomId  =  qyGetCustomId(  );
	 event.eventType  =  eventType;
	 if  (  timeBuf  )  safeStrnCpy(  timeBuf,  event.localEventTime,  sizeof(  event.localEventTime  )  );
	 else  getCurTime(  event.localEventTime  );				

	 return  qwmLogEvent(  pSubThreadInfoParam,  &event  );

}

 extern  "C"  int  qwmLogGeneralEvent(  void  *  pSubThreadInfoParam,  int  eventType,  char  *  curUsrName,  char  *  comment0,  char  *  comment1,  unsigned  char  ucbUtf8  )
{
	 //  return  qwmLogProxyServerEvent(  pSubThreadInfoParam,  eventType,  curUsrName,  comment0  );

	 QWM_EVENT		event;
	 unsigned  int	len;

	 memset(  &event,  0,  sizeof(  event  )  );
	 event.iCustomId  =  qyGetCustomId(  );
	 event.eventType  =  eventType;
	 getCurTime(  event.localEventTime  );	
	 if  (  curUsrName  &&  curUsrName[0]  )  {
		 /*
		 lstrcpyn(  event.u.comment,  curUsrName,  sizeof(  event.u.comment  )  );
		 len  =  lstrlen(  event.u.comment  );
		 lstrcpyn(  event.u.comment  +  len,  ":",  sizeof(  event.u.comment  )  -  len  );
		 */
		 safeStrnCpy(  curUsrName,  event.usrName,  mycountof(  event.usrName  )  );	//  2007/02/18, 引入了用户信息，不再挤在comment里了
	 }
	 len  =  strlen(  event.u.comment  );
	 if  (  comment0  )  safeStrnCpy(  comment0,  event.u.comment  +  len,  sizeof(  event.u.comment  )  -  len  );
	 if  (  comment1  )  safeStrnCpy(  comment1,  event.u.comments[1],  sizeof(  event.u.comments[1]  )  );	//  2005/09/11
	 event.ucbUtf8  =  ucbUtf8;		//  2006/03/25加上

	 return  qwmLogEvent(  pSubThreadInfoParam,  &event  );
	 
}




 extern  "C"  int  qwmLogProxyServerEvent(  void  *  pSubThreadInfoParam,  int  eventType,  char  *  curUsrName,  char  *  proxyServer  )
{
	 QWM_EVENT		event;
	 unsigned  int	len;

	 memset(  &event,  0,  sizeof(  event  )  );
	 event.iCustomId  =  qyGetCustomId(  );
	 event.eventType  =  eventType;
	 getCurTime(  event.localEventTime  );	
	 if  (  curUsrName  )  {
		 /*
		 lstrcpyn(  event.u.comment,  curUsrName,  sizeof(  event.u.comment  )  );
		 len  =  lstrlen(  event.u.comment  );
		 lstrcpyn(  event.u.comment  +  len,  ":",  sizeof(  event.u.comment  )  -  len  );
		 */
		 safeStrnCpy(  curUsrName,  event.usrName,  mycountof(  event.usrName  )  );	//  2007/02/18, 引入了用户信息，不再挤在comment里了
	 }
	 len  =  strlen(  event.u.comment  );
	 if  (  proxyServer  )  safeStrnCpy(  proxyServer,  event.u.comment  +  len,  sizeof(  event.u.comment  )  -  len  );

	 return  qwmLogEvent(  pSubThreadInfoParam,  &event  );
	 
}


 //  2005/01/07
 extern  "C"  int  qwmLogDevEvent(  void  *  pSubThreadInfoParam,  int  eventType,  QWM_DEV_INFO  *  pDiskInfo  )
{
	 QWM_EVENT		event;
	 //  unsigned  int	len;

	 memset(  &event,  0,  sizeof(  event  )  );
	 event.iCustomId  =  qyGetCustomId(  );
	 event.eventType  =  eventType;
	 getCurTime(  event.localEventTime  );
	 if  (  pDiskInfo  )  {
		 _snprintf(  event.u.comment,  sizeof(  event.u.comment  ),  "%s",  pDiskInfo->devDesc  );
		 if  (  pDiskInfo->ucbDisabled  )  _snprintf(  event.u.comment,  sizeof(  event.u.comment  ),  "%s (%s)",  event.u.comment,  "Disabled"  );
		 //  2011/09/21
		 event.usQwmDevType  =  pDiskInfo->usQwmDevType;
	 }

	 //  2010/05/21
	 event.ucbUtf8  =  TRUE;

	 return  qwmLogEvent(  pSubThreadInfoParam,  &event  );
	 
}

 