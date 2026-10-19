
#include	<windows.h>            // required for all Windows applications
#include	<windowsx.h>

#include	<stdlib.h>
#include	<ras.h>
#include	<raserror.h>
#include	<lm.h>
#include	<iphlpapi.h>
#include	<tchar.h>
#include	"asrWMon.h"
//  #include	"osversion.h"
#include	"config.h"
#include	"main.h"
#include	"qyTCharCommProc.h"

#include	<sys/types.h>
#include	<sys/stat.h>

 int  collectUsrLog(  QWM_THREADINFO  *  pThreadInfo  );

 DWORD  WINAPI  qwmThreadCollectUsrLog(  LPVOID  lpParameter  )
{
	 QWM_THREADINFO						threadInfo;
	 QY_W_MON						*	pQwm					=	(  QY_W_MON  *  )lpParameter;
	 QWM_THREAD_CFG						threadCfg;
	 unsigned  int						loopCtrl				=	0;
	 unsigned  int						loopCtrl_collectUsrLog	=	60;
	 unsigned  long						dwcSubKeys				=	1;


	 traceLogA(  "qwmThreadCollectUsrLog enters"  );

	 memset(  &threadInfo,  0,  sizeof(  threadInfo  )  );
	 memset(  &threadCfg,  0,  sizeof(  threadCfg  )  );
	 threadInfo.pParaentParam  =  lpParameter;
	 threadInfo.pCfg  =  &threadCfg;


	 for  (  ;  !pQwm->bQuit;  Sleep(  2000  ),  loopCtrl  ++  )  {

		  if  (  loopCtrl  %  60  )  {
			  if  (  !getKeyInfo(  HKEY_USERS,  _T(  ""  ),  &dwcSubKeys,  0  )  )  {
				  if  (  dwcSubKeys  <  20  )  loopCtrl_collectUsrLog  =  30;			//  一般终端为1分钟收集一次
				  else  if  (  dwcSubKeys  <  50  )  loopCtrl_collectUsrLog  =  90;		//	很多用户时为3分钟
				  else  loopCtrl_collectUsrLog  =  300;									//  极端情况下为10分钟
			  }
		  }

		  if  (  !(  loopCtrl  %  (  loopCtrl_collectUsrLog  +  1  )  )  )  {
			  collectUsrLog(  &threadInfo  );
		  }
	 }


	 return  0;

} 


 int  tmpHandler_collectUsrLog(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int					iErr			=	-1;
	 QWM_THREADINFO		*	pThreadInfo		=	(  QWM_THREADINFO  *  )p0;
	 QY_W_MON			*	pQwm			=	(  QY_W_MON  *  )pThreadInfo->pParaentParam;
	 QWM_USR_INFO		*	pUsrInfo		=	(  QWM_USR_INFO  *  )p2;
	 QY_REG					reg;
	 unsigned  int			len;
	 DWORD					dwcVals			=		0;
	 DWORD					dwcPtrs			=		0;
	 char					buf[128];
	 HKEY					hKey			=		NULL;
	 BOOL					bKeyOpen		=		FALSE;
	 DWORD					j;   
	 DWORD					retValue;   
	 DWORD					dwcValueName;
	 TCHAR					valueName[256];
	 char					data[2048];
	 DWORD					cbData;
	 QWM_EVENT				event;
	 //
	 int					iSent			=	0;		//  发送日志的计数
	 
	 if  (  pQwm->bQuit  )  goto  errLabel;

	 //  traceLogA(  "szKey is %s",  pUsrInfo->szSubKey  );

	 if  (  strstr(  pUsrInfo->szSubKey,  "_Classes"  )  )  {
		 iErr  =  0;  goto  errLabel;
	 }
	 if  (  !stricmp(  pUsrInfo->szSubKey,  ".Default"  )  )  {
		 iErr  =  0;  goto  errLabel;
	 }

	 memset(  &reg,  0,  sizeof(  reg  )  );
	 reg.hKeyRoot0  =  HKEY_USERS;
	 //
	 //  lstrcpyn(  reg.rootKey,  pUsrInfo->szSubKey,  sizeof(  reg.rootKey  )  );
	 myStr2TChar(  pUsrInfo->szSubKey,  reg.rootKey,  mycountof(  reg.rootKey  )  );
	 len  =  lstrlen(  reg.rootKey  );
	 lstrcpyn(  reg.rootKey  +  len,  _T(  "\\"  ),  mycountof(  reg.rootKey  )  -  len  );
	 len  =  lstrlen(  reg.rootKey  );
	 lstrcpyn(  reg.rootKey  +  len,  _T(  CONST_qyKey_qwmLog_usr  ),  mycountof(  reg.rootKey  )  -  len  );

	 //	 
	 dwcVals  =  getKeyValsCnt(  reg.hKeyRoot0,  reg.rootKey  );
	 len  =  sizeof(  buf  );
	 if  (  !tmpGetRegCfgEx(  &reg,  _T(  CONST_qwmLogPtr  ),  buf,  &len  )  )  {
		 dwcPtrs  ++  ;
	 }
	 if  (  dwcVals  <=  dwcPtrs  )  {
		 iErr  =  0;  goto  errLabel;
	 }
 
	 reg.pEncCtx  =  &gQyWMon.encCtx;
	 
	 if  (  ERROR_SUCCESS  !=  RegOpenKey(  reg.hKeyRoot0,  reg.rootKey,  &hKey  )  )  goto  errLabel;
	 bKeyOpen  =  TRUE;

	 //  注意这里，由dwcVals来控制循环次数，而j来指向将读取的记录
	 for  (  j  =  0;  dwcVals ;  dwcVals  --  )  {
		  dwcValueName  =  sizeof(  valueName  );        
		  valueName[0] = '\0';
		  cbData  =  sizeof(  data  );
		  data[0]  =  0;
		  retValue  =  RegEnumValue(  hKey,  j,  valueName,  
									  &dwcValueName,  
									  NULL,  
									  NULL,			//  &dwType,         
			  						  NULL,			//  data, 
									  NULL  );		//  &cbData  );    
		  if  (  retValue  !=  (  DWORD  )ERROR_SUCCESS  )  break;
		  
		  if  (  !lstrcmpi(  valueName,  _T(  CONST_qwmLogPtr  )  )  )  { 
			  j  ++  ;continue;
		  }
		  if  (  qyGetRegDataEx(  &reg,  valueName,  data,  &cbData  )  )  {
			  RegDeleteValue(  hKey,  valueName  );
			  continue;
		  }

		  memset(  &event,  0,  sizeof(  event  )  );
		  memcpy(  &event,  data,  min(  sizeof(  event  ),  cbData  )  );

		  //  2006/03/23, 将event.comments[]转化为utf8,			//  032006起做以下改动
		  switch  (  event.eventType  )  {
			   	  case  CONST_qyEventType_nm_rasStart:
			 	  case  CONST_qyEventType_nm_rasEnd:
			 	  case  CONST_qyEventType_nm_rasProhibited:
					    break;
				  default:
						  if  (  !event.ucbUtf8  )  myStr2Utf8(  event.u.comments[0],  sizeof(  event.u.comments[0]  )  );
						  if  (  !event.ucbUtf8  )  myStr2Utf8(  event.u.comments[1],  sizeof(  event.u.comments[1]  )  );
						  event.ucbUtf8  =  TRUE;
						  break;
		  }

		  //  下面将日志存在hkey_local_machine下面
		  if  (  qwmLogEventInReg(  &gQyWMon,  &event  )  )  goto  errLabel;

		  //  发完后，将日志清除
		  RegDeleteValue(  hKey,  valueName  );		  

		  iSent  ++  ;  if  (  iSent  >=  50  )  break;		//  2005/10/04,  对一次性发送的日志有限制，以使有时间去下载配置

	 }

	 	 
	 iErr  =  0;

errLabel:


	 if  (  bKeyOpen  )  RegCloseKey(  hKey  );

	 return  iErr;
}

 int  collectUsrLog(  QWM_THREADINFO  *  pThreadInfo  )
{
	 QY_W_MON  *  pQwm  =  (  QY_W_MON  *  )pThreadInfo->pParaentParam;

	 enumRegUsrs(  pQwm->env.iPlatformId,  pThreadInfo,  0,  tmpHandler_collectUsrLog  );  

	 return  0;
}


