
#include	"stdafx.h"
#include	<stdlib.h>
#include	<stdio.h>
#include	<tchar.h>
#include	"qyCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyLicense.h"
#include	"qyCommProc.h"
#include	"qyLangCommProc.h"
#include	"qnmCommProc.h"

//  #include	"qmCommon.h"

#define MAX_CFG_NAME_LEN	256
#define MAX_CFG_VAL_LEN		256
 __declspec(  dllexport  )  extern  "C"  int  getCfgValByName(  LPCTSTR  cfgFile,  char  *  cfgName,  char  *  cfgVal,  int  size  )
{
	
	FILE *fp=NULL;
	char buf[MAX_CFG_NAME_LEN+MAX_CFG_VAL_LEN+1];
	char cfgNameBuf[MAX_CFG_NAME_LEN+1],cfgValBuf[MAX_CFG_VAL_LEN+1];
	char fmt[32];
	int iRet=-1;
	
	if( strlen(cfgName)>MAX_CFG_NAME_LEN || size>MAX_CFG_VAL_LEN+1 ) 
		return -1;

	if  (  !(  fp  =  _tfopen(  cfgFile,  _T(  "r"  )  )  )  )  return  -1;

	sprintf(fmt,"%%%ds%%%ds",MAX_CFG_NAME_LEN,MAX_CFG_VAL_LEN);

	for(;;){
		if(!fgets(buf,sizeof(buf),fp)) break;
		if(2!=sscanf(buf,fmt,cfgNameBuf,cfgValBuf)) continue;
		if(strcmp(cfgNameBuf,cfgName)) continue;
		iRet=0;
		break;
	}

	if(!iRet) strcpy(cfgVal,cfgValBuf);

	fclose(fp);

	return iRet;

	
}


 __declspec(  dllexport  )  extern  "C"  int  getCfgValByNameT(  LPCTSTR  cfgFile,  TCHAR  *  cfgName,  TCHAR  *  cfgVal,  int  size  )
{
	
	FILE	*	fp	=	NULL;
	TCHAR		buf[MAX_CFG_NAME_LEN+MAX_CFG_VAL_LEN+1];
	TCHAR		cfgNameBuf[MAX_CFG_NAME_LEN+1],cfgValBuf[MAX_CFG_VAL_LEN+1];
	TCHAR		fmt[32];
	int			iRet=-1;
	
	if  (  lstrlen(  cfgName  )  >  MAX_CFG_NAME_LEN  ||  size  >  MAX_CFG_VAL_LEN  +  1  )  return  -1;

	if  (  !(  fp  =  _tfopen(  cfgFile,  _T(  "r,ccs=UNICODE"  )  )  )  )  return  -1;

	_sntprintf(  fmt,  mycountof(  fmt  ),  _T(  "%%%ds%%%ds"  ),  MAX_CFG_NAME_LEN,  MAX_CFG_VAL_LEN  );

	for  (  ;  ;  ){
		 if  (  !_fgetts(  buf,  mycountof(  buf  ),  fp  )  )  break;
		 //
		 OutputDebugString(  buf  );  OutputDebugString(  _T(  "\n"  )  );
		 //
		 if  (  2  !=  _stscanf(  buf,  fmt,  cfgNameBuf,  cfgValBuf  )  )  continue;
		 if  (  lstrcmpi(  cfgNameBuf,  cfgName  )  )  continue;
		 iRet  =  0;
		 break;
	}

	if  (  !iRet  ) lstrcpyn(  cfgVal,  cfgValBuf,  size  );

	fclose(  fp  );

	return  iRet;

}

 __declspec(  dllexport  )  extern  "C"  BOOL  bQmAdvancedVer(  void  *  p0,  LPCTSTR  cfgFullFileName,  void  *  p2  )
{
	 char	buf[128];
	 
	 traceLogA(  "bQmAdvancedVer return  TRUE"  );

	 return  TRUE;	 


	 if  (  !getCfgValByName(  cfgFullFileName,  CONST_cfgName_bAdvancedVer,  buf,  sizeof(  buf  )  )    
		 &&  !_stricmp(  buf,  CONST_cfgVal_bAdvancedVer  )  )
	 {	
		 return  TRUE;
	 }

	 return  FALSE;
}




 QNM_SYSCFG_INFO  CONST_qnmSysCfgInfoTable[]  =																																														//  Mgr,  System,  Cfg,  pcList,  eventList,  netDevEventList,  searchList,
{																		// defaultDsnName;	rootKey_qnmScheduler;

	{	CONST_qySystemId_bhb,		CONST_qyAppType_null,				FALSE,	_T(  CONST_qyDsn_netMc  ),				_T(  CONST_qyRootKey_mcGui_netMc  ),		_T(  CONST_qyRootKey_qnmScheduler  ),								},
	{	CONST_qySystemId_bhb,		CONST_qyAppType_interMonOfBhb,		FALSE,	_T(  CONST_qyDsn_netMc  ),				_T(  CONST_qyRootKey_mcGui_netMc  ),		_T(  CONST_qyRootKey_qnmScheduler  ),								},
	{	CONST_qySystemId_netMc2,	CONST_qyAppType_null,				FALSE,	_T(  CONST_qyDsn_netMc  ),				_T(  CONST_qyRootKey_mcGui_netMc  ),		_T(  CONST_qyRootKey_qnmScheduler  ),								},
	{	CONST_qySystemId_nms,		CONST_qyAppType_null,				FALSE,	_T(  CONST_qyDsn_netMc  ),				_T(  CONST_qyRootKey_mcGui_netMc  ),		_T(  CONST_qyRootKey_qnmScheduler  ),								},
	{	CONST_qySystemId_secChk,	CONST_qyAppType_null,				FALSE,	_T(  CONST_qyDsn_netMc  ),				_T(  CONST_qyRootKey_mcGui_netMc  ),		_T(  CONST_qyRootKey_qnmScheduler  ),								},
	//  {	CONST_qySystemId_netMc4,	CONST_qyAppType_null,																																		},
	{	CONST_qySystemId_assetMgr,	CONST_qyAppType_null,				FALSE,	_T(  CONST_qyDsn_netMc  ),				_T(  CONST_qyRootKey_mcGui_netMc  ),		_T(  CONST_qyRootKey_qnmScheduler  ),								},
	//
	{	CONST_qySystemId_messenger,	CONST_qyAppType_null,				TRUE,	_T(  CONST_qyDbNamePrefix_mis  ),		_T(  CONST_qyRootKey_mcGui_mis  ),			_T(  CONST_qyRootKey_qnmScheduler_mis  ),							},
	{	CONST_qySystemId_messenger,	CONST_qyAppType_client,				TRUE,	_T(  CONST_qyDbNamePrefix_misClient  ),	_T(  CONST_qyRootKey_mcGui_misClient  ),	_T(  CONST_qyRootKey_qnmScheduler_misClient  ),						},
	{	-1,							NULL,																																},
};

 __declspec(  dllexport  )  QNM_SYSCFG_INFO	*	getQnmSysCfgInfo(  int  iSystemId,  int  iAppType  )
{
	 QNM_SYSCFG_INFO	*	p	=	NULL;

	 for  (  p  =  CONST_qnmSysCfgInfoTable;  p->iSystemId  !=  -1;  p  ++  )  {
		  if  (  p->iSystemId  ==  iSystemId  &&  iAppType  ==  p->iAppType  )  return  p;
	 }
	 //  如果没有全部对应的，则返回仅iSystemId符合的
	 for  (  p  =  CONST_qnmSysCfgInfoTable;  p->iSystemId  !=  -1;  p  ++  )  {
		  if  (  p->iSystemId  ==  iSystemId  )  return  p;
	 }
	 return  NULL;
}


  BOOL  b4Core(  )
{
	BOOL	bRet	=	FALSE;
	
#ifdef  __DEBUG__
		//  test
		//  return  FALSE;
#endif

	SYSTEM_INFO	si;
	GetSystemInfo(  &si  );
	if  (  si.dwNumberOfProcessors  <  4  )  goto  errLabel;

	bRet  =  TRUE;
			
errLabel:
	return  bRet;
}

