

#include	<windows.h>
#include	<winsock.h>
#include	<ras.h>
#include	<raserror.h>
#include	<commctrl.h>
#include	<lmaccess.h>
#include	<iphlpapi.h>
#include	<tchar.h>
//  #include	"resource.h"
#include	"asrWMon.h"
#include	"qyRegToolProc.h"


BOOL  bGetPhoneBk(  void  *  pSubThreadInfoParam );


 int  chkRas(  void  *  pSubThreadInfoParam,  void  *  p1Reserved,  void  *  p2Reserved  )
{
	 bGetPhoneBk(  pSubThreadInfoParam  );
	 return  0;
}

 BOOL  bGetPhoneBk(  void  *  pSubThreadInfoParam )
{
	BOOL						bRet				=   FALSE;
	MT_SUBTHREADINFO		*   pSubThreadInfo		=	(  MT_SUBTHREADINFO  *  ) pSubThreadInfoParam;
	QY_REG_TOOL				*	pRegTool			=   (  QY_REG_TOOL  *  )pSubThreadInfo->pParentParam;
    LPRASENTRYNAME				lpRasEntry			=	NULL;
    DWORD						cbBuf;
    DWORD						cEntry;
    DWORD						dwRet;
    UINT						ndx;
	QNM_WMBUF_SHOWSECCHKEVENT	wmBuf;
	QWM_DYN_LIB				*	pDynLib				=	(  QWM_DYN_LIB  *  )pRegTool->env.pDynLibs;

	if  (  !pDynLib->ghDll_RasApi32  )  return  0;

	cbBuf  =  sizeof(  RASENTRYNAME  );
    if  (  (  lpRasEntry  =  (  LPRASENTRYNAME  )malloc(  (  UINT  )cbBuf  )  )  ==  NULL  )  goto  errLabel;
	lpRasEntry->dwSize  =  sizeof(  RASENTRYNAME  );
    dwRet = pDynLib->pRasEnumEntries(  NULL,  NULL,  lpRasEntry,  &cbBuf,  &cEntry  );
    if  (  dwRet  ==  ERROR_BUFFER_TOO_SMALL  )    {
		free(  lpRasEntry  );  lpRasEntry  =  NULL;
		if (  (  lpRasEntry  =  (  LPRASENTRYNAME  ) malloc(  (  UINT  )cbBuf  )  )  ==  NULL  )  goto  errLabel;
		lpRasEntry->dwSize  =  sizeof(  RASENTRYNAME  );
		dwRet = pDynLib->pRasEnumEntries(  NULL,  NULL,  lpRasEntry,  &cbBuf,  &cEntry  );
	}
	if  (  dwRet  )  {
		traceLogA(  "R0a1s2hqgaE3n4u5m6E7n8t9r10ies failed"  );  goto  errLabel;
	}

	for  (  ndx  =  0;  ndx  <  cEntry;  ndx  ++  )  {
		
		 traceLogA(  "  the lpRasEntry[%d].szEntryName  is  %s  ",  ndx,  lpRasEntry[ndx].szEntryName  );  
		 //  
		 memset(  &wmBuf,  0,  sizeof(  wmBuf  )  );
		 wmBuf.uiType  =  CONST_qyWmParam_showSecChkEvent;
		 wmBuf.event.lEventType  =  CONST_qyEventType_secChk_rasPhoneBk;
		 safeStrnCpy(  CONST_qyNullTime,  wmBuf.event.localEventTime,  sizeof(  wmBuf.event.localEventTime  )  );
		 myTChar2Utf8(  lpRasEntry[ndx].szEntryName,  wmBuf.event.des0,  sizeof(  wmBuf.event.des0  )  );
		 if  (  addEventToCache(  pSubThreadInfoParam,  &wmBuf.event,  pRegTool  )  )  break;
		 SendMessage(  pRegTool->hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
	}


	bRet = TRUE; 

errLabel:

	if  (  lpRasEntry  )  free(  lpRasEntry  );

	return  bRet; 
}

