
//  #include	"stdafx.h"
#include	<afxdb.h>
#include	<windowsx.h>
#include	<winsock2.h>
#include	<vfw.h>

#include	"qmCommon.h"
#include	"qyDbCommon.h"
#include	"qyTCharCommProc.h"
#include	"myDb.h"


#define		CONST_tmpStr						CString(  "1=1"  )

//   


 BOOL  bGetPolicyImAuthCond(  HKEY  hKeyRoot,  LPCTSTR  rootKey_qnmScheduler,  POLICY_imAuthCond  *  p  )
{
	int						iErr		=		-1;
	POLICY_imAuthCond		policy;
	POLICY_imAuthCond		policy_0;

	if  (  !p  )  return  FALSE;

	memset(  &policy,  0,  sizeof(  policy  )  );

	qyRefreshRegCfg_ucb(  CString(  rootKey_qnmScheduler  ),  _T(  CONST_regValName_ucbUseMac  ),  &policy.ucbUseMac  );
	qyRefreshRegCfg_ucb(  CString(  rootKey_qnmScheduler  ),  _T(  CONST_regValName_ucbUsePcName  ),  &policy.ucbUsePcName  );
	qyRefreshRegCfg_ucb(  CString(  rootKey_qnmScheduler  ),  _T(  CONST_regValName_ucbUseDomainName  ),  &policy.ucbUseDomainName  );
	qyRefreshRegCfg_ucb(  CString(  rootKey_qnmScheduler  ),  _T(  CONST_regValName_ucbUseOsUsrName  ),  &policy.ucbUseOsUsrName  );
	//
	qyRefreshRegCfg_ucb(  CString(  rootKey_qnmScheduler  ),  _T(  CONST_regValName_ucbUseMessengerName  ),  &policy.ucbUseMessengerName  );
	//
	qyRefreshRegCfg_ucb(  CString(  rootKey_qnmScheduler  ),  _T(  CONST_regValName_ucbAutoVerification  ),  &policy.ucbAutoVerification  );

	//
	qyRefreshRegCfg_ucb(  CString(  rootKey_qnmScheduler  ),  _T(  CONST_regValName_ucbNeedValidIpForDevice  ),  &policy.ucbNeedValidIpForDevice  );
	TCHAR	tBuf[128];	char	buf[128];
	if  (  !qyGetRegCfg(  rootKey_qnmScheduler,  _T(  CONST_regValName_startIp_device  ),  (  char  *  )tBuf,  sizeof(  tBuf  )  )  )  {
		myTChar2Utf8(  tBuf,  buf,  mycountof(  buf  )  );
		trim(  buf  );
		if  (  bIpValid(  buf  )  )  safeStrnCpy(  buf,  policy.startIp,  mycountof(  policy.startIp  )  );
	}
	if  (  !qyGetRegCfg(  rootKey_qnmScheduler,  _T(  CONST_regValName_endIp_device  ),  (  char  *  )tBuf,  sizeof(  tBuf  )  )  )  {
		myTChar2Utf8(  tBuf,  buf,  mycountof(  buf  )  );
		trim(  buf  );
		if  (  bIpValid(  buf  )  )  safeStrnCpy(  buf,  policy.endIp,  mycountof(  policy.endIp  )  );
	}

	memset(  &policy_0,  0,  sizeof(  policy_0  )  );
	if  (  !memcmp(  &policy,  &policy_0,  sizeof(  policy  )  )  )  {	//  没有设置则采用缺省
		policy.ucbUseMac  =  TRUE;										//  使用MAC为认证规则
		//
		policy.ucbAutoVerification  =  TRUE;							//  缺省选择自动认证。
	}

	policy.ucbUseMessengerName  =  TRUE;	//  因为管理员的需要，所以肯定是需要messengerName的，因为其他信息他没有. 2007/10/10

	if  (  memcmp(  p,  &policy,  sizeof(  policy  )  )  )  memcpy(  p,  &policy,  sizeof(  p[0]  )  );

	return  TRUE;

}


 BOOL  bGetPolicyIsMgr(  HKEY  hKeyRoot,  LPCTSTR  rootKey_qnmScheduler,  POLICY_isMgr  *  p  )
{
	TCHAR			*	pRegVal				=	NULL;
	TCHAR				tBuf[255  +  1]		=	_T(  ""  );
	TCHAR			*	pT;
	long				lVal;


	 if  (  !p  )  return  FALSE;

	 memset(  p,  0,  sizeof(  p[0]  )  );

	 qyRefreshRegCfg_ucb(  CString(  rootKey_qnmScheduler  ),  _T(  CONST_regValName_ucbLogImMsg  ),  &p->ucbLogImMsg  );

	 //
	 p->startTmpMessengerId.ui64Id  =  1000000;												//  
	 p->uiMaxCnt_tmpMessengers  =  CONST_maxTmpMessengers;									//  2007/11/23

	 //
	 p->usMaxIntervalIsSBetweenWebSessions  =  CONST_usMaxIntervalIsSBetweenWebSessions;	//  2007/12/11
	 p->usIntervalInSBetweenWebSessions  =  CONST_usIntervalInSBetweenWebSessions;			//  2007/12/23

	 //
	 p->usTimeoutInMsToSwitch  =  DEFAULT_usTimeoutInMsToSwitch_isMgr;								//  2008/10/28
	 pRegVal  =  CONST_regValName_usTimeoutInMsToSwitch;
	 if  (  qyGetRegCfgT(  hKeyRoot,  CString(  rootKey_qnmScheduler  ),  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	 lVal  =  (  short  )_tcstol(  tBuf,  &pT,  10  );
	 if  (  lVal  )  p->usTimeoutInMsToSwitch  =  (  unsigned  short  )lVal;

	 //  2009/04/02
	 p->usMaxMsgs_allowedToSwitchToTalkChannel_robot  =  DEFAULT_usMaxMsgs_allowedToSwitchToTalkChannel_robot;
	 pRegVal  =  CONST_regValName_usMaxMsgs_allowedToSwitchToTalkChannel_robot;
	 if  (  qyGetRegCfgT(  hKeyRoot,  CString(  rootKey_qnmScheduler  ),  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	 lVal  =  (  short  )_tcstol(  tBuf,  &pT,  10  );
	 if  (  lVal  &&  lVal  <=  MAX_usMaxMsgs_allowedToSwitchToTalkChannel  )  p->usMaxMsgs_allowedToSwitchToTalkChannel_robot  =  (  unsigned  short  )lVal;

	 p->usMaxMsgs_allowedToSwitchToTalkChannel_media  =  DEFAULT_usMaxMsgs_allowedToSwitchToTalkChannel_media;
	 pRegVal  =  CONST_regValName_usMaxMsgs_allowedToSwitchToTalkChannel_media;
	 if  (  qyGetRegCfgT(  hKeyRoot,  CString(  rootKey_qnmScheduler  ),  pRegVal,  (  char  *  )tBuf,  sizeof(  tBuf  ),  0  )  )  tBuf[0]  =  0;
	 lVal  =  (  short  )_tcstol(  tBuf,  &pT,  10  );
	 if  (  lVal  &&  lVal  <=  MAX_usMaxMsgs_allowedToSwitchToTalkChannel  )  p->usMaxMsgs_allowedToSwitchToTalkChannel_media  =  (  unsigned  short  )lVal;


	 //  
	 p->uiCommEncCtxType  =  qyGetEncType(  0  );											//  2008/06/09

	 //  2009/09/17
	 p->ucbUseDynBmpRule  =  bQnmDemo(  )  ?  FALSE  :  TRUE;
	 if  (  bQnmDemo(  )  )  {
		 qyRefreshRegCfg_ucb(  CString(  rootKey_qnmScheduler  ),  _T(  CONST_regValName_ucbUseDynBmpRule  ),  &p->ucbUseDynBmpRule  );
	 }

	 //  2011/01/30
	 p->uiSizePerSnd_media  =  DEFAULT_uiSizePerSnd_media_isMgr;
	 if  (  p->uiSizePerSnd_media  >  MAX_uiSizePerSnd_media  )  {
		 traceLog(  _T(  "bGetPolicyInMgr error: uiSizePerSnd_media can't be > %d"  ),  MAX_uiSizePerSnd_media  );
	 }


	 return  TRUE;
}


  BOOL  bGetQisIntervalParams(  HKEY  hKeyRoot,  LPCTSTR  rootKey_qnmScheduler,  QIS_INTERVAL_PARAMS  *  pIntervalParams  )
{		 
	 int	iDef;

	 if  (  !pIntervalParams  )  return  FALSE;

	 memset(  pIntervalParams,  0,  sizeof(  pIntervalParams[0]  )  );

	 iDef  =  CONST_usIntervalInS_refreshRecentFriends;  MACRO_getInterval(  iDef,  CString(  rootKey_qnmScheduler  ),  _T(  CONST_regValName_usIntervalInS_refreshRecentFriends  ),  pIntervalParams->usIntervalInS_refreshRecentFriends  );
	 iDef  =  CONST_usIntervalInS_refreshContactList;  MACRO_getInterval(  iDef,  CString(  rootKey_qnmScheduler  ),  _T(  CONST_regValName_usIntervalInS_refreshContactList  ),  pIntervalParams->usIntervalInS_refreshContactList  );

	 return  TRUE;

}


////
//BOOL  bGetMessengerAuthRcdBySth(  void  *  pDbParam,  int  iDbType,  QY_imAm_RCD  *  pImAm,  POLICY_imAuthCond  *  pAuthCond,  QY_COMM_AUTHINFO_MIS  *  pAuthInfo,  int  iRcdId,  QY_MESSENGERAUTH_RCD  *  pObj  )
  BOOL  bGetMessengerAuthRcdBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  POLICY_imAuthCond  *  pAuthCond,  QY_COMM_AUTHINFO_MIS  *  pAuthInfo,  int  iRcdId,  QY_MESSENGERAUTH_RCD  *  pObj  )
{
	 BOOL			bRet									=		FALSE;
	 CString		sqlStr;
	 CString		whereStr;
	 CDBVariant		varVals[15  +  CONST_qnmMaxRegFields];
	 int			index									=		0;
	 char			idStr[CONST_qyMessengerIdStrLen  +  1]	=	"";
	 char			ip12Buf[128]							=		"";
	 int			iDataType_pcName						=		SQL_WVARCHAR;
	 int			iDataType_domainName					=		SQL_WVARCHAR;
	 int			iDataType_osUsrName						=		SQL_WVARCHAR;
	 int			iDataType_messengerName					=		SQL_WVARCHAR;
	 TCHAR			tBuf[256  +  1];
	 
				//						  0			   1			2		   3			  4			     5				6				  7				8					9
	 sqlStr  =  CString(  "select id,misServName,idStr,uiType,mac0,mac1,mac2,nMacs,ip,pcName,domainName,osUsrName,messengerName"  )
					+  " from qyImObjAuthTab";
	 whereStr  =  CONST_tmpStr;

	 if  (  misServName  &&  pIdInfo  &&  pIdInfo->ui64Id  )  {
		 idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  );
		 whereStr  =  whereStr  +  " and misServName="  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )  + " and idStr='"  +  idStr  +  "'";
		 }
	 else  if  (  pAuthCond  &&  pAuthInfo  )  {
		 if  (  pAuthCond->ucbUseMac  )  {
			 if  (  bMacValid(  (  char  *  )pAuthInfo->macsInfo.macs[0]  )  )  whereStr  =  whereStr  +  " and mac0='"  +  pAuthInfo->macsInfo.macs[0]  +  "'";
			 if  (  bMacValid(  (  char  *  )pAuthInfo->macsInfo.macs[1]  )  )  whereStr  =  whereStr  +  " and mac1='"  +  pAuthInfo->macsInfo.macs[1]  +  "'";
			 if  (  bMacValid(  (  char  *  )pAuthInfo->macsInfo.macs[2]  )  )  whereStr  =  whereStr  +  " and mac2='"  +  pAuthInfo->macsInfo.macs[2]  +  "'";
			 //
			 whereStr  =  whereStr  +  " and nMacs="  +  CString(  _ltot(  pAuthInfo->macsInfo.nMacs,  tBuf,  10  )  );
		 }
		 if  (  pAuthCond->ucbUsePcName  )  whereStr  =  whereStr  +  " and pcName="  +  getDbValStr(  iDbType,  iDataType_pcName,  pAuthInfo->pcName  );
		 if  (  pAuthCond->ucbUseDomainName  )  whereStr  =  whereStr  +  " and domainName="  +  getDbValStr(  iDbType,  iDataType_domainName,  pAuthInfo->domainName  );
		 if  (  pAuthCond->ucbUseOsUsrName  )  whereStr  =  whereStr  +  " and osUsrName="  +  getDbValStr(  iDbType,  iDataType_osUsrName,  pAuthInfo->osUsrName  );
		 if  (  pAuthCond->ucbUseMessengerName  )  whereStr  =  whereStr  +  " and messengerName="  +  getDbValStr(  iDbType,  iDataType_messengerName,  pAuthInfo->messengerName  );
		}
	 else  {
		   whereStr  =  whereStr  +  " and id="  +  CString(  _ltot(  iRcdId,  tBuf,  10  )  );  
	 }
	 if  (  whereStr  ==  CONST_tmpStr  )  {
		 traceLogA(  "条件应该设置"  );  goto  errLabel;
	 }
	 sqlStr  =  sqlStr  +  " where "  +  whereStr;
	 traceLogA(  "sql is [%S]",  sqlStr.GetBuffer(  0  )  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  sqlStr.GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  goto  errLabel;
	 
	 if  (  pObj  )  {	
		 //
		 memset(  pObj,  0,  sizeof(  pObj[0]  )  );
		 //
		 index  =  0;	//  id  
		 MACRO_sqlLong(  varVals[index],  pObj->id  );
		 index  ++  ;	//  misServName
		 MACRO_sqlStr(  varVals[index],  pObj->misServName,  mycountof(  pObj->misServName  )  );  
		 index  ++  ;	//  idStr
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  idStr,  mycountof(  idStr  )  );  if  (  !idStr2Info(  idStr,  &pObj->idInfo  )  )  goto  errLabel;
		 index  ++  ;  //  iType
		 MACRO_sqlLong(  varVals[index],  pObj->uiType  );
		 /*
		 index  ++  ;  //  mac2
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPcInfo->macs[2],  sizeof(  pPcInfo->macs[2]  )  );  pPcInfo->nMacs  ++  ;  
		 index  ++  ;  //  ip
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12Buf,  sizeof(  ip12Buf  )  );  qyIp12ToStd(  ip12Buf,  pPcInfo->ip  );
		 index  ++  ;  //  iPlatformId
		 MACRO_sqlLong(  varVals[index],  pPcInfo->iPlatformId  );
		 index  ++  ;  //  pcName
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPcInfo->pcName,  sizeof(  pPcInfo->pcName  )  );
		 index  ++  ;  //  osName 
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPcInfo->osName,  sizeof(  pPcInfo->osName  )  );
		 index  ++  ;  //  qwmVer
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPcInfo->qwmVer,  sizeof(  pPcInfo->qwmVer  )  );
		 index  ++  ;  //  startTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPcInfo->startTime,  sizeof(  pPcInfo->startTime  )  );
		 index  ++  ;  //  lastCommTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pPcInfo->lastCommTime,  sizeof(  pPcInfo->lastCommTime  )  );
		 index  ++  ;
		 */

		 //  MACRO_qyAssert(  index  ==  10,  "bGetPcInfoByMac0Ex: index错误"  );

	 }
	 	 

	 
	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}


 BOOL  bGetMessengerAuthTmpRcdBySth(  void  *  pDbParam,  int  iDbType,  POLICY_imAuthCond  *  pAuthCond,  QY_COMM_AUTHINFO_MIS  *  pAuthInfo,  QY_MESSENGERAUTHTMP_RCD  *  pObj  )
{
	 BOOL			bRet						=		FALSE;
	 CString		sqlStr;
	 CString		whereStr;
	 CDBVariant		varVals[15  +  CONST_qnmMaxRegFields];
	 int			index						=		0;
	 char			ip12Buf[128]				=		"";
	 int			iDataType_pcName			=		SQL_WVARCHAR;
	 int			iDataType_domainName		=		SQL_WVARCHAR;
	 int			iDataType_osUsrName			=		SQL_WVARCHAR;
	 int			iDataType_messengerName		=		SQL_WVARCHAR;
	 TCHAR			tBuf[256  +  1];
	 int			i;

	 
	 if  (  !pAuthCond  ||  !pAuthInfo  )  return  FALSE;

				//						  0			   1			2		   3			  4			     5				6				  7				8					9
	 sqlStr  =  CString(  "select id,misServName,idStr,uiType,mac0,mac1,mac2,ip,pcName,domainName,osUsrName,messengerName,clientVer,uiLangId,iPlatformId,iStatus,startTime"  )
					+  " from "  +  CONST_tabName_qyImObjAuthTmpTab;
	 whereStr  =  CONST_tmpStr;
	 if  (  pAuthCond->ucbUseMac  )  {
		 if  (  bMacValid(  (  char  *  )pAuthInfo->macsInfo.macs[0]  )  )  whereStr  =  whereStr  +  " and mac0='"  +  pAuthInfo->macsInfo.macs[0]  +  "'";
		 if  (  bMacValid(  (  char  *  )pAuthInfo->macsInfo.macs[1]  )  )  whereStr  =  whereStr  +  " and mac1='"  +  pAuthInfo->macsInfo.macs[1]  +  "'";
		 if  (  bMacValid(  (  char  *  )pAuthInfo->macsInfo.macs[2]  )  )  whereStr  =  whereStr  +  " and mac2='"  +  pAuthInfo->macsInfo.macs[2]  +  "'";
		 //
		 whereStr  =  whereStr  +  " and nMacs="  +  CString(  _ltot(  pAuthInfo->macsInfo.nMacs,  tBuf,  10  )  );
	 }
	 if  (  pAuthCond->ucbUsePcName  )  whereStr  =  whereStr  +  " and pcName="  +  getDbValStr(  iDbType,  iDataType_pcName,  pAuthInfo->pcName  );
	 if  (  pAuthCond->ucbUseDomainName  )  whereStr  =  whereStr  +  " and domainName="  +  getDbValStr(  iDbType,  iDataType_domainName,  pAuthInfo->domainName  );
	 if  (  pAuthCond->ucbUseOsUsrName  )  whereStr  =  whereStr  +  " and osUsrName="  +  getDbValStr(  iDbType,  iDataType_osUsrName,  pAuthInfo->osUsrName  );
	 //
	 if  (  pAuthCond->ucbUseMessengerName  )  whereStr  =  whereStr  +  " and messengerName="  +  getDbValStr(  iDbType,  iDataType_messengerName,  pAuthInfo->messengerName  );
	 
	 if  (  whereStr  ==  CONST_tmpStr  )  {
		 traceLogA(  "没有设置认证要求的条件"  );  goto  errLabel;
	 }
	 sqlStr  =  sqlStr  +  " where "  +  whereStr;
	 traceLogA(  "sql is [%s]",  sqlStr.GetBuffer(  0  )  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  sqlStr.GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  goto  errLabel;
	 
	 if  (  pObj  )  {	
		 //
		 memset(  pObj,  0,  sizeof(  pObj[0]  )  );
		 //
		 index  =  0;	//  id  
		 MACRO_sqlLong(  varVals[index],  pObj->id  );
		 index  ++  ;	//  misServName
		 MACRO_sqlStr(  varVals[index],  pObj->misServName,  mycountof(  pObj->misServName  )  );  myTChar2Str(  tBuf,  pObj->idStr,  mycountof(  pObj->idStr  )  );
		 index  ++  ;	//  idStr
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pObj->idStr,  mycountof(  pObj->idStr  )  );
		 index  ++  ;  //  uiType
		 MACRO_sqlLong(  varVals[index],  pObj->uiType  );
		 index  ++  ;  //  mac0
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  (  char  *  )pObj->macsInfo.macs[0],  sizeof(  pObj->macsInfo.macs[0]  )  );  
		 index  ++  ;  //  mac1
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  (  char  *  )pObj->macsInfo.macs[1],  sizeof(  pObj->macsInfo.macs[1]  )  );  
		 index  ++  ;  //  mac2
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  (  char  *  )pObj->macsInfo.macs[2],  sizeof(  pObj->macsInfo.macs[2]  )  );  
		 index  ++  ;  //  ip
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12Buf,  sizeof(  ip12Buf  )  );  qyIp12ToStd(  ip12Buf,  pObj->ip  );
		 index  ++  ;  //  pcName
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2WChar(  tBuf,  pObj->pcName,  mycountof(  pObj->pcName  )  );
		 index  ++  ;  //  domainName 
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2WChar(  tBuf,  pObj->domainName,  mycountof(  pObj->domainName  )  );
		 index  ++  ;  //  osUsrName 
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2WChar(  tBuf,  pObj->osUsrName,  mycountof(  pObj->osUsrName  )  );
		 index  ++  ;  //  messengerName
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2WChar(  tBuf,  pObj->messengerName,  mycountof(  pObj->messengerName  )  );
		 index  ++  ;  //  clientVer 
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pObj->clientVer,  mycountof(  pObj->clientVer  )  );
		 index  ++  ;  //  uiLangId
		 MACRO_sqlLong(  varVals[index],  pObj->uiLangId  );
		 index  ++  ;  //  iPlatformId
		 MACRO_sqlLong(  varVals[index],  pObj->iPlatformId  );
		 index  ++  ;  //  iStatus
		 MACRO_sqlLong(  varVals[index],  pObj->iStatus  );
  		 index  ++  ;  //  startTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pObj->startTime,  sizeof(  pObj->startTime  )  );
		 index  ++  ;

		 //  MACRO_qyAssert(  index  ==  10,  "bGetPcInfoByMac0Ex: index错误"  );

		 //  这里再计算一下nMacs
		 for  (  i  =  0;  i  <  mycountof(  pObj->macsInfo.macs  );  i  ++  )  if  (  bMacValid(  (  char  *  )pObj->macsInfo.macs[i]  )  )  pObj->macsInfo.nMacs  ++  ;

	 }
	 	 
	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}

#if 0  //  2013/02/19
 BOOL  bGetImAmRcdBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  LPCTSTR  messengerName,  int  id,  QY_imAm_RCD  *  pObj  )
{
	 BOOL			bRet						=		FALSE;
	 CString		sqlStr;
	 CString		whereStr;
	 CDBVariant		varVals[15  +  CONST_qnmMaxRegFields];
	 int			index						=		0;
	 char			ip12Buf[128]				=		"";
	 TCHAR			tBuf[256  +  1];
	 char			buf[256  +  1];
	 int			i;

	 
	 if  (  !pDbParam  )  return  FALSE;

				//						  0			   1			2		   3			  4			     5				6				  7				8					9
	 sqlStr  =  CString(  "select id,misServName,idStr,messengerName,messengerPasswd,iPasswdType,salt,iStatus,startTime,tLastModifiedTime"  )
					+  " from "  +  CONST_tabName_qyImAmTab;
	 whereStr  =  CONST_tmpStr;
	 if  (  misServName  &&  pIdInfo  &&  pIdInfo->ui64Id  )  {
		 idInfo2Str(  pIdInfo,  buf,  mycountof(  buf  )  );
		 whereStr  =  whereStr  +  " and misServName="  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )  +  " and idStr='"  +  buf  +  "'";
		 }
	 else  if  (  misServName  &&  messengerName  &&  messengerName[0]  )  {
			   whereStr  =  whereStr  +  " and misServName="  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )  +  " and messengerName="  +  getDbValStr(  iDbType,  CONST_iDataType_name,  messengerName  );
			   }
	 else  {
		   whereStr  =  whereStr  +  " and id="  +  _ltot(  id,  tBuf,  10  );
	 }
	 
	 if  (  whereStr  ==  CONST_tmpStr  )  {
		 traceLogA(  ""  );  goto  errLabel;
	 }
	 sqlStr  =  sqlStr  +  " where "  +  whereStr;
	 traceLogA(  "sql is [%s]",  sqlStr.GetBuffer(  0  )  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  sqlStr.GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  goto  errLabel;
	 
	 if  (  pObj  )  {	
		 //
		 memset(  pObj,  0,  sizeof(  pObj[0]  )  );
		 //
		 index  =  0;	//  id  
		 MACRO_sqlLong(  varVals[index],  pObj->id  );
		 index  ++  ;	//  misServName
		 MACRO_sqlStr(  varVals[index],  pObj->misServName,  mycountof(  pObj->misServName  )  );  
		 index  ++  ;	//  idStr
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pObj->idInfo  );
		 index  ++  ;  //  messengerName
		 MACRO_sqlStr(  varVals[index],  pObj->messengerName,  mycountof(  pObj->messengerName  )  );
		 index  ++  ;  //  messengerPasswd
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  (  char  *  )pObj->messengerPasswd,  sizeof(  pObj->messengerPasswd  )  );  
		 index  ++  ;  //  iPasswdType
		 MACRO_sqlLong(  varVals[index],  pObj->iPasswdType  );
		 index  ++  ;  //  salt
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );	myTChar2Str(  tBuf,  pObj->salt,  mycountof(  pObj->salt  )  );
		 index  ++  ;  //  iStatus
		 MACRO_sqlLong(  varVals[index],  pObj->iStatus  );
  		 index  ++  ;  //  startTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pObj->startTime,  sizeof(  pObj->startTime  )  );
		 index  ++  ;	//  tLastModifiedTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pObj->tLastModifiedTime,  sizeof(  pObj->tLastModifiedTime  )  );
		 index  ++  ;

		 //  MACRO_qyAssert(  index  ==  10,  "bGetPcInfoByMac0Ex: index错误"  );

	 }
	 	 
	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}
#endif


 int  putNewMessengerIntoTmpTab(  void  *  pLicenseCtx,  void  *  pDbParam,  int  iDbType,  POLICY_imAuthCond  *  pAuthCond,  QY_COMM_AUTHINFO_MIS  *  pAuthInfo,  unsigned  int  uiObjType  )
{
	 int		iErr								=	-1;
	 CString	sqlStr;
	 char		nMacsBuf[32];
	 char		ip12Buf[32];
	 char		timeBuf[CONST_qyTimeLen  +  1];
	 //
	 int		iDataType_pcName					=	SQL_WVARCHAR;
	 int		iDataType_osUsrName					=	SQL_WVARCHAR;
	 int		iDataType_domainName				=	SQL_WVARCHAR;
	 //
	 TCHAR		misServName[64]						=	_T(  ""  );
	 char		idStr[20  +  1]						=	"";
	 char		imObjTypeBuf[32]					=	"";

	 
	 if  (  bGetMessengerAuthTmpRcdBySth(  pDbParam,  iDbType,  pAuthCond,  pAuthInfo,  NULL  )  )  {
		 iErr  =  0;  goto  errLabel;
	 }
	 
	 qyStdToIp12(  pAuthInfo->ip,  ip12Buf  );	//  2007/02/20
	 getCurTime(  timeBuf  );

	 ltoa(  uiObjType,  imObjTypeBuf,  10  );

	 sqlStr  =  CString(  ""  )  +  "insert into "  +  CONST_tabName_qyImObjAuthTmpTab  +  "(uiType,misServName,idStr,mac0,mac1,mac2,nMacs,ip,pcName,osUsrName,domainName,messengerName,clientVer,startTime)"
									"Values("  +
									imObjTypeBuf  +  ","  +
									getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )  +  ","  +
									"'"  +  idStr  +  "',"  +
									"'"  +  pAuthInfo->macsInfo.macs[0]  +  "',"  +
									"'"  +  pAuthInfo->macsInfo.macs[1]  +  "',"  +
									"'"  +  pAuthInfo->macsInfo.macs[2]  +  "',"  +
									ltoa(  pAuthInfo->macsInfo.nMacs,  nMacsBuf,  10  )  +  ","  +
									"'"  +  ip12Buf  +  "',"  +
									getDbValStr(  iDbType,  iDataType_pcName,  pAuthInfo->pcName  )  +  ","  +
									getDbValStr(  iDbType,  iDataType_osUsrName,  pAuthInfo->osUsrName  )  +  ","  +
									getDbValStr(  iDbType,  iDataType_domainName,  pAuthInfo->domainName  )  +  ","  +
									getDbValStr(  iDbType,  CONST_iDataType_messengerName,  pAuthInfo->messengerName  )  +  ","  +
									"'"  +  pAuthInfo->ver  +  "',"  +
									"'"  +  timeBuf  +  "')";
	 if  (  !bQyExecSql(  pDbParam,  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;
	 

	 iErr  =  0;
errLabel:
	 return  iErr;
}

//


 //  初始化的号，为表中已有的最大的号。从此号起，新号为此号  ++
 int  getCurMaxMessengerId(  void  *  pDb,  QY_MESSENGER_ID  *  pIdInfo  )
{
	 int					iErr				=	-1;
	 CString				str;
	 CDBVariant				varVals[1];
	 QY_MESSENGER_ID		idInfo;
	 TCHAR					tBuf[256];
	 char					buf[256];
	 BOOL					bMaxIdStrFound		=	FALSE;

	 if  (  !pIdInfo  )  return  -1;

	 str  =  CString(  "select max(idStr) from "  )  +  CONST_tabName_qyImObjAuthTab;

	 memset(  &idInfo,  0,  sizeof(  idInfo  )  );
	 if  (  bQyGetRcdBySql(  pDb,  str,  mycountof(  varVals  ),  varVals  )  )  {
		 MACRO_sqlStr(  varVals[0],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );
		 //
		 if  (  bMessengerIdStrValid(  buf  )  )  {
			 idStr2Info(  buf,  &idInfo  );
			 bMaxIdStrFound  =  TRUE;
		 }
	 }
		
	 if  (  !bMaxIdStrFound  )  {
		   idInfo.ui64Id  =  DEFAULT_initialMessengerId_ui64Id;
	 }

	 iErr  =  0;

//  errLabel:

	 if  (  !iErr  )  memcpy(  pIdInfo,  &idInfo,  sizeof(  pIdInfo[0]  )  );

	 return  iErr;

}

//  在调用此函数时，应该先作好同步
 int  getNextMessengerId(  void  *  p0,  void  *  pDb,  QY_MESSENGER_ID  *  pLastIdInfo,  char  *  idStrBuf,  unsigned  int  size  )
{
	 int					iErr	=	-1;
	 CQySyncObj				syncObj;
	 QY_MESSENGER_ID		curMaxIdInfo;
	 
	 if  (  !pDb  ||  !pLastIdInfo  ||  !idStrBuf  ||  !size  )  return  -1;
	
	 if  (  syncObj.sync(  CONST_mutexname_syncGetNextMessengerId  )  )  {
		 traceLogA(  "mutexName_syncGetNextMessengerId failed"  );
		 goto  errLabel;
	 }

	 if  (  getCurMaxMessengerId(  pDb,  &curMaxIdInfo  )  )  goto  errLabel;

	 //  注意这里，对lastIdInfo要不小于curMaxIdInfo
	 if  (  pLastIdInfo->ui64Id  <  curMaxIdInfo.ui64Id  )  pLastIdInfo->ui64Id  =  curMaxIdInfo.ui64Id;

	 pLastIdInfo->ui64Id  ++  ;

	 if  (  !pLastIdInfo->ui64Id  )  pLastIdInfo->ui64Id  ++  ;	//  这里是为了希望不要用0当ID
	 
	 if  (  !idInfo2Str(  pLastIdInfo,  idStrBuf,  size  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:

	 return  iErr;
}



 unsigned  int  qnmGetnMessengers(  void  *  pDb  )
{
	 TCHAR			sqlStr[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	 CDBVariant		varVal[3];

	 _sntprintf(  sqlStr,  mycountof(  sqlStr  ),  _T(  "select count(idStr) from %s where uiType in (%d)"  ),  CONST_tabName_qyImObjAuthTab,  CONST_objType_messenger  );
	 if  (  bQyGetRcdBySql(  pDb,  sqlStr,  sizeof(  varVal  )  /  sizeof(  varVal[0]  ),  varVal  )  
		 &&  varVal[0].m_dwType  ==  DBVT_LONG  
			&&  varVal[0].m_lVal  >=  0  )
	 {
		 return  varVal[0].m_lVal;
	 }

	 return  0;
}

 unsigned  int  qnmGetnPhoneMessengers(  void  *  pDb  )
{
	 TCHAR			sqlStr[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	 CDBVariant		varVal[3];

	 _sntprintf(  sqlStr,  mycountof(  sqlStr  ),  _T(  "select count(idStr) from %s where uiType in (%d)"  ),  CONST_tabName_qyImObjAuthTab,  CONST_objType_phoneMessenger  );
	 if  (  bQyGetRcdBySql(  pDb,  sqlStr,  sizeof(  varVal  )  /  sizeof(  varVal[0]  ),  varVal  )  
		 &&  varVal[0].m_dwType  ==  DBVT_LONG  
			&&  varVal[0].m_lVal  >=  0  )
	 {
		 return  varVal[0].m_lVal;
	 }

	 return  0;
}


  unsigned  int  qnmGetnImGrps(  void  *  pDb  )
{
	 TCHAR			sqlStr[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	 CDBVariant		varVal[3];

	 _sntprintf(  sqlStr,  mycountof(  sqlStr  ),  _T(  "select count(idStr) from %s where uiType in (%d)"  ),  CONST_tabName_qyImObjAuthTab,  CONST_objType_imGrp  );
	 if  (  bQyGetRcdBySql(  pDb,  sqlStr,  sizeof(  varVal  )  /  sizeof(  varVal[0]  ),  varVal  )  
		 &&  varVal[0].m_dwType  ==  DBVT_LONG  
			&&  varVal[0].m_lVal  >=  0  )
	 {
		 return  varVal[0].m_lVal;
	 }

	 return  0;
}




#if  0
 BOOL  bGetMeInfoBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_INFO  *  pObj  )
{
	 BOOL			bRet									=		FALSE;
	 TCHAR			sqlBuf[1024];
	 CDBVariant		varVals[2];
	 int			index;
	 TCHAR			tBuf[256];
	 char			idStr[CONST_qyMessengerIdStrLen  +  1]	=		"";

	 if  (  !misServName  )  misServName  =  _T(  ""  );

	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select idStr,uiType from qyImObjTab where misServName=%s and uiType=%d"  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CONST_objType_me  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  sqlBuf,  mycountof(  varVals  ),  varVals  )  )  goto  errLabel;

	 if  (  pObj  )  {
		 memset(  pObj,  0,  sizeof(  pObj[0]  )  );
		 //
		 lstrcpyn(  pObj->misServName,  misServName,  mycountof(  pObj->misServName  )  );

		 index  =  0;  MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  idStr,  mycountof(  idStr  )  );  if  (  !idStr2Info(  idStr,  &pObj->idInfo  )  )  goto  errLabel;
		 index  ++  ;  MACRO_sqlLong(  varVals[index],  pObj->uiType  );

	 }

	 bRet  =  TRUE;

errLabel:

	 return  bRet;
}
#endif



#if  0
 BOOL  bGetMessengerInfoBySth(  void  *  pDbParam,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  iRcdId,  QY_MESSENGER_INFO  *  pObjParam,  QY_MESSENGER_REGINFO  *  pRegInfo,  QY_MESSENGER_REGINFO  *  pRegInfoInTab1,  QY_MESSENGER_phoneInfo  *  pPhoneInfo  )
{
	 BOOL					bRet									=		FALSE;
#if  0
	 CString				sqlStr;
	 TCHAR					whereBuf[CONST_maxSqlBufLen  +  1]		=		_T(  ""  );
	 CDBVariant				varVals[15  +  CONST_qnmMaxRegFields];
	 int					index									=		0;
	 int					i;
	 char					ip12Buf[128]							=		"";
	 char					idStr[CONST_qyMessengerIdStrLen  +  1]	=		"";
	 TCHAR					tBuf[256  +  1];
	 char					buf[256  +  1]							=		"";
	 long					lVal									=		0;
	 QY_MESSENGER_INFO		tmpObjInfo;
	 QY_MESSENGER_INFO	*	pObj									=		NULL;
#endif
	 

	 //  2012/07/15
	 if  (  iDbType  ==  CONST_dbType_myDb  )  return  bGetMessengerInfoBySth_myDb(  pDbParam,  iDbType,  pFieldIdTable,  misServName,  pIdInfo,  iRcdId,  pObjParam,  pRegInfo,  pRegInfoInTab1,  pPhoneInfo  );

	 return  bGetMessengerInfoBySth_odbc(  pDbParam,  iDbType,  pFieldIdTable,  misServName,  pIdInfo,  iRcdId,  pObjParam,  pRegInfo,  pRegInfoInTab1,  pPhoneInfo  );

#if  0
	 //
	 if  (  !misServName  )  misServName  =  _T(  ""  );

				//				  0		   1	2		   3			  4			     5				6		  7				8					9          10
	 sqlStr  =  CString(  "select id,uiType,misServName,idStr,ip,detectedIp,usLangId,uiDevType,messengerName,startTime,usRunningStatus,tLastModifiedTime,iStatus"  )
					+  " from "  +  CONST_tabName_qyImObjTab;
	 _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%s"  ),  CONST_tmpStr.GetBuffer(  0  )  );
	 if  (  misServName  &&  pIdInfo  )  {
		 if  (  !idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
		 _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%s and misServName=%s and idStr='%s'"  ),  whereBuf,  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  )  );
		}
	 else  {
		   _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%s and id=%d"  ),  whereBuf,  iRcdId  );
	 }

	 sqlStr  =  sqlStr  +  " where "  +  whereBuf;
	 traceLogA(  "sql is [%S]",  sqlStr.GetBuffer(  0  )  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  sqlStr.GetBuffer(  0  ),  mycountof(  varVals  ),  varVals  )  )  goto  errLabel;
	 
	 pObj  =  pObjParam  ?  pObjParam  :  &tmpObjInfo;	//  注意，这里，因为下面的regInfo都要用到uiType, 所以，这里是一定需要把信息取出来的。
	 
	 if  (  pObj  )  {	
		 //
		 memset(  pObj,  0,  sizeof(  pObj[0]  )  );
		 //
		 index  =  0;	//  id
		 MACRO_sqlLong(  varVals[index],  pObj->iRcdId  );
		 index  ++  ;	//  uiType		 
		 MACRO_sqlLong(  varVals[index],  pObj->uiType  );
		 index  ++  ;	//  misServName
		 MACRO_sqlStr(  varVals[index],  pObj->misServName,  mycountof(  pObj->misServName  )  );  
		 index  ++  ;	//  idStr
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  idStr,  mycountof(  idStr  )  );  if  (  !idStr2Info(  idStr,  &pObj->idInfo  )  )  goto  errLabel;
		 index  ++  ;	//  ip
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12Buf,  mycountof(  ip12Buf  )  );  qyIp12ToStd(  ip12Buf,  pObj->ip  );  
		 index  ++  ;	//  detectedIp
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  ip12Buf,  mycountof(  ip12Buf  )  );  qyIp12ToStd(  ip12Buf,  pObj->detectedIp  );  
		 index  ++  ;	//  usLangId
		 MACRO_sqlLong(  varVals[index],  lVal  );  pObj->usLangId  =  (  unsigned  short  )lVal;
		 index  ++  ;	//  uiDevType
		 MACRO_sqlLong(  varVals[index],  pObj->uiDevType  );
		 index  ++  ;	//  messengerName
		 MACRO_sqlStr(  varVals[index],  pObj->messengerName,  mycountof(  pObj->messengerName  )  );  
		 index  ++  ;	//  startTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pObj->startTime  =  gettTimeByBuf(  buf  );
		 index  ++  ;	//  usRunningStatus
		 MACRO_sqlLong(  varVals[index],  lVal  );  pObj->usRunningStatus  =  (  unsigned  short  )lVal;
		 index  ++  ;	//  tLastModifiedTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pObj->tLastModifiedTime  =  gettTimeByBuf(  buf  );
		 index  ++  ;	//  iStatus
		 MACRO_sqlLong(  varVals[index],  pObj->iStatus  );
		 index  ++  ;

		 //  MACRO_qyAssert(  index  ==  10,  "bGetPcInfoByMac0Ex: index错误"  );

		 //  这2个参数是为下面的
		 if  (  !misServName  )  misServName  =  pObj->misServName;
		 if  (  !idInfo2Str(  &pObj->idInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
	 }

	 if  (  !misServName  ||  !bMessengerIdStrValid(  idStr  )  )  goto  errLabel;
	 _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%s"  ),  CONST_tmpStr.GetBuffer(  0  )  );
	 _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%s and misServName=%s and idStr='%s'"  ),  whereBuf,  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  )  );

	 if  (  pRegInfo  )  {
		 //
		 memset(  pRegInfo,  0,  sizeof(  pRegInfo[0]  )  );
		 //
		 pRegInfo->uiType  =  CONST_imCommType_messengerRegInfo;
		 pRegInfo->iCustomId  =  qyGetCustomId(  );
		 //
		 MACRO_setFieldIdInRegInfo(  pRegInfo[0]  );
		 MACRO_setPtrs(  pFieldIdTable,  pRegInfo[0],  pRegInfo->fields  );
		 //
		 sqlStr  =  CString(  "select"  )  
	 	 					//			1			2						(  +  30  )												
				+  " qyImObjRegInfoTab.regTime,qyImObjRegInfoTab.auditTime,qyImObjRegInfoTab.tLastModifiedTime,qyImObjRegInfoTab.col0,qyImObjRegInfoTab.col1,qyImObjRegInfoTab.col2,qyImObjRegInfoTab.col3,qyImObjRegInfoTab.col4,qyImObjRegInfoTab.col5,qyImObjRegInfoTab.col6,qyImObjRegInfoTab.col7,qyImObjRegInfoTab.col8,qyImObjRegInfoTab.col9,qyImObjRegInfoTab.col10,qyImObjRegInfoTab.col11,qyImObjRegInfoTab.col12,qyImObjRegInfoTab.col13,qyImObjRegInfoTab.col14,qyImObjRegInfoTab.col15,qyImObjRegInfoTab.col16,qyImObjRegInfoTab.col17,qyImObjRegInfoTab.col18,qyImObjRegInfoTab.col19,qyImObjRegInfoTab.col20,qyImObjRegInfoTab.col21,qyImObjRegInfoTab.col22,qyImObjRegInfoTab.col23,qyImObjRegInfoTab.col24,qyImObjRegInfoTab.col25,qyImObjRegInfoTab.col26,qyImObjRegInfoTab.col27,qyImObjRegInfoTab.col28,qyImObjRegInfoTab.col29" 
				+  " from qyImObjRegInfoTab"
				+  " where "  +  whereBuf;
		 OutputDebugString(  sqlStr  +  "\n"  );
		 if  (  bQyGetRcdBySql(  pDbParam,  sqlStr.GetBuffer(  0  ),  mycountof(  varVals  ),  varVals  )  )  {

			 lstrcpyn(  pRegInfo->addr.misServName,  misServName,  mycountof(  pRegInfo->addr.misServName  )  );
			 pRegInfo->addr.uiObjType  =  pObj->uiType;
			 pRegInfo->addr.idInfo.ui64Id  =  pIdInfo->ui64Id;

			 index  =  0;  //  regTime
			 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfo->regTime,  mycountof(  pRegInfo->regTime  )  );  
			 index  ++  ;  //  auditTime
			 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfo->auditTime,  mycountof(  pRegInfo->auditTime  )  );  
			 index  ++  ;	//  lastModifiedTime
			 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfo->tLastModifiedTime,  mycountof(  pRegInfo->tLastModifiedTime  )  );
			 index  ++  ;
			 

			 for  (  i  =  0;  i  <  CONST_qnmMaxRegFields;  i  ++  )  {
				  //  if  (  varVals[i  +  index].m_dwType  ==  DBVT_STRING  )  myTChar2Str(  varVals[i  +  index].m_pstring->GetBuffer(  0  ),  fields[i].ptr,  fields[i].bufSize  );
				  MACRO_sqlStr(  varVals[i  +  index],  pRegInfo->fields[i].ptr,  pRegInfo->fields[i].bufSize  );
	 	 	 }
	 	 	 index  +=  i;
	 	 }
	 
	 }
	 	 
	 if  (  pRegInfoInTab1  )  {
		 //
		 memset(  pRegInfoInTab1,  0,  sizeof(  pRegInfoInTab1[0]  )  );
		 //
		 pRegInfoInTab1->uiType  =  CONST_imCommType_messengerRegInfo;
		 pRegInfoInTab1->iCustomId  =  qyGetCustomId(  );
		 //
		 MACRO_setFieldIdInRegInfo(  pRegInfoInTab1[0]  );
		 MACRO_setPtrs(  pFieldIdTable,  pRegInfoInTab1[0],  pRegInfoInTab1->fields  );
		 //
		 sqlStr  =  CString(  "select"  )  
	 	 					//			1			2						(  +  30  )												
				+  " qyImObjRegInfoTab1.regTime,qyImObjRegInfoTab1.auditTime,qyImObjRegInfoTab1.tCommitTime,qyImObjRegInfoTab1.col0,qyImObjRegInfoTab1.col1,qyImObjRegInfoTab1.col2,qyImObjRegInfoTab1.col3,qyImObjRegInfoTab1.col4,qyImObjRegInfoTab1.col5,qyImObjRegInfoTab1.col6,qyImObjRegInfoTab1.col7,qyImObjRegInfoTab1.col8,qyImObjRegInfoTab1.col9,qyImObjRegInfoTab1.col10,qyImObjRegInfoTab1.col11,qyImObjRegInfoTab1.col12,qyImObjRegInfoTab1.col13,qyImObjRegInfoTab1.col14,qyImObjRegInfoTab1.col15,qyImObjRegInfoTab1.col16,qyImObjRegInfoTab1.col17,qyImObjRegInfoTab1.col18,qyImObjRegInfoTab1.col19,qyImObjRegInfoTab1.col20,qyImObjRegInfoTab1.col21,qyImObjRegInfoTab1.col22,qyImObjRegInfoTab1.col23,qyImObjRegInfoTab1.col24,qyImObjRegInfoTab1.col25,qyImObjRegInfoTab1.col26,qyImObjRegInfoTab1.col27,qyImObjRegInfoTab1.col28,qyImObjRegInfoTab1.col29"  
				+  " from qyImObjRegInfoTab1"
				+  " where "  +  whereBuf;
		 OutputDebugString(  sqlStr  +  "\n"  );
		 if  (  bQyGetRcdBySql(  pDbParam,  sqlStr.GetBuffer(  0  ),  mycountof(  varVals  ),  varVals  )  )  {

			 lstrcpyn(  pRegInfoInTab1->addr.misServName,  misServName,  mycountof(  pRegInfoInTab1->addr.misServName  )  );
			 pRegInfoInTab1->addr.uiObjType  =  pObj->uiType;
			 pRegInfoInTab1->addr.idInfo.ui64Id  =  pIdInfo->ui64Id;

			 index  =  0;	//  regTime
			 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfoInTab1->regTime,  sizeof(  pRegInfoInTab1->regTime  )  );  
			 index  ++  ;	 //  auditTime	
			 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfoInTab1->auditTime,  sizeof(  pRegInfoInTab1->auditTime  )  );  
			 index  ++  ;
			 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfoInTab1->tCommitTime,  sizeof(  pRegInfoInTab1->tCommitTime  )  );  
			 index  ++  ;


			 for  (  i  =  0;  i  <  CONST_qnmMaxRegFields;  i  ++  )  {
				  //  if  (  varVals[i  +  index].m_dwType  ==  DBVT_STRING  )  myTChar2Str(  varVals[i  +  index].m_pstring->GetBuffer(  0  ),  fields[i].ptr,  fields[i].bufSize  );
				  MACRO_sqlStr(  varVals[i  +  index],  pRegInfoInTab1->fields[i].ptr,  pRegInfoInTab1->fields[i].bufSize  );
	 	 	 }
	 	 	 index  +=  i;
		 }

	 }

	 if  (  pPhoneInfo  )  {	//  2008/02/14
		 //
		 if  (  !bGetMessengerPhoneInfoBySth(  pDbParam,  iDbType,  misServName,  0,  0,  pIdInfo,  0,  pPhoneInfo  )  )  memset(  pPhoneInfo,  0,  sizeof(  pPhoneInfo[0]  )  );
	 
	 }


	 
	 bRet  =  TRUE;

#endif

errLabel:

	 return  bRet;

}
#endif

#if  0
//
int  insertImObj(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_INFO  *  pObj  )
{
	if  (  iDbType  ==  CONST_dbType_myDb  )  return  insertImObj_myDb(  pDbParam,  iDbType,  pObj  );

	return  insertImObj_odbc(  pDbParam,  iDbType,  pObj  );
}

 int  updateImObj(  void  *  pDbParam,  int  iDbType,  QY_MESSENGER_INFO  *  pObj,  int  iRcdId  )
 {
	 if  (  iDbType  ==  CONST_dbType_myDb  )  return  updateImObj_myDb(  pDbParam,  iDbType,  pObj,  iRcdId  );

	 return  updateImObj_odbc(  pDbParam,  iDbType,  pObj,  iRcdId  );
 }
#endif

#if  0
 BOOL  bGetMessengerRegInfoBySth(  void  *  pDbParam,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  LPCTSTR  pTabName,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  iRcdId,  QY_MESSENGER_REGINFO  *  pRegInfo  )
{
	 BOOL			bRet									=		FALSE;
	 CString		sqlStr;
	 TCHAR			whereBuf[CONST_maxSqlBufLen  +  1]		=		_T(  ""  );
	 CDBVariant		varVals[15  +  CONST_qnmMaxRegFields];
	 int			index									=		0;
	 int			i;
	 char			ip12Buf[128]							=		"";
	 char			idStr[CONST_qyMessengerIdStrLen  +  1]	=		"";
	 TCHAR			tBuf[256  +  1];
	 char			buf[256  +  1]							=		"";
	 long			lVal									=		0;
	 	 
	 if  (  !pTabName  )  return  FALSE;

	 _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%s"  ),  CONST_tmpStr.GetBuffer(  0  )  );
	 if  (  misServName  &&  pIdInfo  )  {
		 if  (  !idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
		 _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%s and misServName=%s and idStr='%s'"  ),  whereBuf,  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  )  );
		}
	 else  {
		   _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%s and id=%d"  ),  whereBuf,  iRcdId  );
	 }
	 

	 //
	 sqlStr  =  CString(  "select"  )  
	 	 					//			1			2						(  +  30  )												
				+  " misServName,idStr,regTime,auditTime,tCommitTime,tLastModifiedTime,col0,col1,col2,col3,col4,col5,col6,col7,col8,col9,col10,col11,col12,col13,col14,col15,col16,col17,col18,col19,col20,col21,col22,col23,col24,col25,col26,col27,col28,col29" 
				+  " from "  +  pTabName
				+  " where "  +  whereBuf;
	 OutputDebugString(  sqlStr  +  "\n"  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  sqlStr.GetBuffer(  0  ),  mycountof(  varVals  ),  varVals  )  )  goto  errLabel;
	
	 if  (  pRegInfo  )  {

		 memset(  pRegInfo,  0,  sizeof(  pRegInfo[0]  )  );
		 //
		 pRegInfo->uiType  =  CONST_imCommType_messengerRegInfo;
		 pRegInfo->iCustomId  =  qyGetCustomId(  );
		 //
		 MACRO_setFieldIdInRegInfo(  pRegInfo[0]  );
		 MACRO_setPtrs(  pFieldIdTable,  pRegInfo[0],  pRegInfo->fields  );


		 index  =  0;	//  misServName
		 MACRO_sqlStr(  varVals[index],  pRegInfo->addr.misServName,  mycountof(  pRegInfo->addr.misServName  )  );
		 index  ++  ;	//  idStr
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  idStr,  mycountof(  idStr  )  );  idStr2Info(  idStr,  &pRegInfo->addr.idInfo  );
		 index  ++  ;	//  regTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfo->regTime,  mycountof(  pRegInfo->regTime  )  );  
		 index  ++  ;	//  auditTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfo->auditTime,  mycountof(  pRegInfo->auditTime  )  );  
		 index  ++  ;	//  tComminTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfo->tCommitTime,  mycountof(  pRegInfo->tCommitTime  )  );  
		 index  ++  ;	//  lastModifiedTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRegInfo->tLastModifiedTime,  mycountof(  pRegInfo->tLastModifiedTime  )  );
		 index  ++  ;
			 
		 for  (  i  =  0;  i  <  CONST_qnmMaxRegFields;  i  ++  )  {
			  MACRO_sqlStr(  varVals[i  +  index],  pRegInfo->fields[i].ptr,  pRegInfo->fields[i].bufSize  );
		 }
		 index  +=  i;
	 
	 }
 
	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}
#endif



#if  0  //  2013/01/02//////
 BOOL  bGetImObjRuleRcdBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  REFRESH_imObjRule_reqMem  *  pMem,  int  iRcdId,  QY_imObjRule_rcd  *  pRcd  )
{
	 BOOL			bRet									=		FALSE;
	 CQyString		sqlStr;
	 TCHAR			whereBuf[CONST_maxSqlBufLen  +  1]		=		_T(  ""  );
	 CDBVariant		varVals[15];
	 int			index									=		0;
	 int			i;
	 char			ip12Buf[128]							=		"";
	 char			idStr[CONST_qyMessengerIdStrLen  +  1]	=		"";
	 char			idStr_related[CONST_qyMessengerIdStrLen  +  1]	=	"";
	 TCHAR			tBuf[256  +  1];
	 char			buf[256  +  1]							=		"";
	 long			lVal									=		0;
	 TCHAR		*	pTabName								=		CONST_tabName_qyImObjRuleTab;
	 	 
	 if  (  !pTabName  )  return  FALSE;

	 _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%s"  ),  CONST_tmpStr.GetBuffer(  0  )  );
	 if  (  misServName  &&  pIdInfo  &&  pMem  )  {
		 idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  );
		 idInfo2Str(  &pMem->idInfo_related,  idStr_related,  mycountof(  idStr_related  )  );
		 //
		 _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%s and misServName=%s and idStr='%s' and idStr_related='%s' and uiRuleType=%d and usIndex=%d"  ),  
			 whereBuf,  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CQyString(  idStr  ),
			 CQyString(  idStr_related  ),  pMem->uiRuleType,  pMem->usIndex  );
		}
	 else  {
		   _sntprintf(  whereBuf,  mycountof(  whereBuf  ),  _T(  "%s and id=%d"  ),  whereBuf,  iRcdId  );
	 }
	 

	 //
	 sqlStr  =  CQyString(  "select"  )  		 
				+	" id,misServName,idStr,uiRuleType,usIndex,idStr_related,uiCmd,startTime,tLastModifiedTime,iStatus,col0"
				+  " from "  +  pTabName
				+  " where "  +  whereBuf;
	 OutputDebugString(  sqlStr  +  "\n"  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  sqlStr.GetBuffer(  0  ),  mycountof(  varVals  ),  varVals  )  )  goto  errLabel;
	
	 if  (  pRcd  )  {
		 memset(  pRcd,  0,  sizeof(  pRcd[0]  )  );
		 //
		 index  =  0;	//  id
		 MACRO_sqlLong(  varVals[index],  pRcd->id  );
		 index  ++  ;	//  misServName
		 MACRO_sqlStr(  varVals[index],  pRcd->misServName,  mycountof(  pRcd->misServName  )  );
		 index  ++  ;	//  idStr
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Utf8(  tBuf,  idStr,  mycountof(  idStr  )  );  idStr2Info(  idStr,  &pRcd->idInfo  );
		 index  ++  ;	//  uiRuleType
		 MACRO_sqlLong(  varVals[index],  pRcd->uiRuleType  );
		 index  ++  ;	//  usIndex
		 MACRO_sqlLong(  varVals[index],  pRcd->usIndex  );
		 index  ++  ;	//  idStr_related
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  idStr,  mycountof(  idStr  )  );  idStr2Info(  idStr,  &pRcd->idInfo_related  );
		 index  ++  ;	//  uiCmd
		 MACRO_sqlLong(  varVals[index],  pRcd->uiCmd  );
		 index  ++  ;	//  startTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->startTime  =  gettTimeBylStr(  buf  );
		 index  ++  ;	//  lastModifiedTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tLastModifiedTime  =  gettTimeBylStr(  buf  );
		 index  ++  ;	//  iStatus
		 MACRO_sqlLong(  varVals[index],  pRcd->iStatus  );
		 index  ++  ;	//  col0
		 MACRO_sqlStr(  varVals[index],  pRcd->col0,  mycountof(  pRcd->col0  )  );
		 index  ++  ;
	 
	 }
 
	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}
#endif

 #if  0

int  tmpHandler_bGetImObjRules(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	int							iErr		=	-1;
	REFRESH_imObjRules_req	*	pReq		=	(  REFRESH_imObjRules_req  *  )p1;
	CDBVariant				*	varVals		=	(  CDBVariant  *  )p2;
	//

	TCHAR					tBuf[256]	=	_T(  ""  );
	char					idStr[CONST_qyMessengerIdStrLen  +  1];
	char					buf[256]	=	"";
	QY_imObjRule_rcd		rcd;
	QY_imObjRule_rcd	*	pRcd		=	&rcd;
	int						index;

	memset(  &rcd,  0,  sizeof(  rcd  )  );

	index  =  0;	//  id
	MACRO_sqlLong(  varVals[index],  pRcd->id  );
	index  ++  ;	//  misServName
	MACRO_sqlStr(  varVals[index],  pRcd->misServName,  mycountof(  pRcd->misServName  )  );
	index  ++  ;	//  idStr
	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Utf8(  tBuf,  idStr,  mycountof(  idStr  )  );  idStr2Info(  idStr,  &pRcd->idInfo  );
	index  ++  ;	//  idStr_related
	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  idStr,  mycountof(  idStr  )  );  idStr2Info(  idStr,  &pRcd->idInfo_related  );
	index  ++  ;	//  uiRuleType
	MACRO_sqlLong(  varVals[index],  pRcd->uiRuleType  );
	index  ++  ;	//  usIndex
	MACRO_sqlLong(  varVals[index],  pRcd->usIndex  );
	index  ++  ;	//  uiCmd
	MACRO_sqlLong(  varVals[index],  pRcd->uiCmd  );
	index  ++  ;	//  startTime
	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->startTime  =  gettTimeBylStr(  buf  );
	index  ++  ;	//  lastModifiedTime
	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tLastModifiedTime  =  gettTimeBylStr(  buf  );
	index  ++  ;	//  iStatus
	MACRO_sqlLong(  varVals[index],  pRcd->iStatus  );
	index  ++  ;	//  col0, 2011/11/14
	MACRO_sqlStr(  varVals[index],  pRcd->col0,  mycountof(  pRcd->col0  )  );
	index  ++  ;


	pReq->mems[pReq->usCnt].idInfo_related.ui64Id  =  rcd.idInfo_related.ui64Id;
	pReq->mems[pReq->usCnt].uiRuleType  =  rcd.uiRuleType;
	pReq->mems[pReq->usCnt].uiCmd  =  rcd.uiCmd;
	safeTcsnCpy(  rcd.col0,  pReq->mems[pReq->usCnt].wDesc,  mycountof(  pReq->mems[pReq->usCnt].wDesc  )  );		//  2011/11/14

	pReq->usCnt  ++  ;
	if  (  pReq->usCnt  >=  mycountof(  pReq->mems  )  
		||  (  pReq->usMaxMemsPerSnd  &&  pReq->usCnt  >=  pReq->usMaxMemsPerSnd  )  )  
	{
		iErr  =  1;
		goto  errLabel;
	}

	iErr  =  0;
errLabel:

	return  iErr;
}


 //  BOOL  bGetImObjRulesReq(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  QY_MESSENGER_ID	*	pIdInfo_related,  REFRESH_imObjRules_req  *  pReq  )
 BOOL  bGetImObjRulesReq(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  QY_MESSENGER_ID	*	pIdInfo_related,  LPCTSTR  condPart,  unsigned  short  usMaxMemsPerSnd,  REFRESH_imObjRules_req  *  pReq  )
{
	BOOL				bRet										=	FALSE;
	CQyString			sqlStr;
	char				idStr[CONST_qyMessengerIdStrLen  +  1]		=	"";
	char				idStr_related[CONST_qyMessengerIdStrLen  +  1]	=	"";
	int					tmpiRet										=	-1;
	CDBVariant			varVals[15];

	if  (  !pReq  )  return  FALSE;

	memset(  pReq,  0,  sizeof(  pReq[0]  )  );

	sqlStr  =  CQyString(  "select"  )  		 
				+	" id,misServName,idStr,idStr_related,uiRuleType,usIndex,uiCmd,startTime,tLastModifiedTime,iStatus,col0"
				+  " from "  +  CONST_tabName_qyImObjRuleTab
				+  " where 1=1";
	if  (  pIdInfo  &&  pIdInfo->ui64Id  )  {
		idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  );
		sqlStr  =  sqlStr  +  " and idStr='"  +  idStr  +  "'";		
	}
	if  (  pIdInfo_related  &&  pIdInfo_related->ui64Id  )  {
		idInfo2Str(  pIdInfo_related,  idStr_related,  mycountof(  idStr_related  )  );	//  2009/09/08
		sqlStr  =  sqlStr  +  " and idStr_related='"  +  idStr_related  +  "'";
	}
	if  (  condPart  &&  condPart[0]  )  {	//  2011/11/12
		sqlStr  =  sqlStr  +  " and ("  +  condPart  +  ")";
	}
	sqlStr  =  sqlStr  +  " order by idStr,idStr_related,uiRuleType,usIndex";

	OutputDebugString(  sqlStr  +  "\n"  );
	 
	pReq->usMaxMemsPerSnd  =  usMaxMemsPerSnd;
	tmpiRet  =  enumSqlQuery(  pDbParam,  sqlStr,  tmpHandler_bGetImObjRules,  0,  pReq,  varVals,  mycountof(  varVals  ),  NULL  );
	if  (  tmpiRet  <  0  )  goto  errLabel;

	bRet  =  TRUE;

errLabel:
	return  bRet;
}
#endif


 //

  BOOL  bGetMessengerPcInfoBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  QY_MESSENGER_PCINFO  *  pRcd  )
 {
	 BOOL			bRet									=		FALSE;
	 CString		sqlStr;
	 CString		whereStr;
	 CDBVariant		varVals[15  +  CONST_qnmMaxRegFields];
	 int			index									=		0;
	 char			ip12Buf[128]							=		"";
	 char			idStr[CONST_qyMessengerIdStrLen  +  1]	=		"";
	 TCHAR			tBuf[256  +  1];
	 char			buf[256  +  1]							=		"";
	 	 
	 if  (  !pIdInfo  )  return  FALSE;
	 if  (  !idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  )  )  return  FALSE;

	 if  (  !misServName  )  misServName  =  _T(  ""  );

				//				  0		   1	2		   3			  4			     5				6				  7				8					9
	 sqlStr  =  CString(  "select id,misServName,idStr,uiType,uiLangId,iPlatformId,pcName,domainName,osUsrName,tLastModifiedTime"  )
					+  " from "  +  CONST_tabName_qyMessengerPcInfoTab;
	 whereStr  =  CONST_tmpStr;
	 whereStr  =  whereStr  +  " and misServName="  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )  +  " and idStr="  +  getDbValStr(  iDbType,  CONST_iDataType_idStr,  CString(  idStr  )  );
	 if  (  whereStr  ==  CONST_tmpStr  )  {
		 traceLogA(  "条件应该设置"  );  goto  errLabel;
	 }
	 sqlStr  =  sqlStr  +  " where "  +  whereStr;
	 traceLogA(  "sql is [%S]",  sqlStr.GetBuffer(  0  )  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  sqlStr.GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  goto  errLabel;

	 if  (  pRcd  )  {

         index  =  0;	 //  id
		 MACRO_sqlLong(  varVals[index],  pRcd->id  );
         index  ++  ;	 //  misServName
		 MACRO_sqlStr(  varVals[index],  pRcd->misServName,  mycountof(  pRcd->misServName  )  );  
         index  ++  ;	 //  idStr
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo  );
		 index  ++  ;	//  uiType
		 MACRO_sqlLong(  varVals[index],  pRcd->uiType  );
		 index  ++  ;	//  iPlatformId
		 MACRO_sqlLong(  varVals[index],  pRcd->iPlatformId  );
		 index  ++  ;	//  pcName
		 MACRO_sqlStr(  varVals[index],  pRcd->pcName,  mycountof(  pRcd->pcName  )  );
		 index  ++  ;	//  domainName
		 MACRO_sqlStr(  varVals[index],  pRcd->domainName,  mycountof(  pRcd->domainName  )  );
		 index  ++  ;	//  osUsrName
		 MACRO_sqlStr(  varVals[index],  pRcd->osUsrName,  mycountof(  pRcd->osUsrName  )  );
		 index  ++  ;	//  tLastModifiedTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tLastModifiedTime  =  gettTimeByBuf(  buf  );
		 index  ++  ;
	 

	 }
	 
	 bRet  =  TRUE;

errLabel:

	 return  bRet;


}

#if  0
 BOOL  bGetImGrpInfoBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  IM_GRP_INFO  *  pRcd  )
{
 	 BOOL			bRet									=		FALSE;
	 CString		sqlStr;
	 CString		whereStr;
	 CDBVariant		varVals[15  +  CONST_qnmMaxRegFields];
	 int			index									=		0;
	 char			ip12Buf[128]							=		"";
	 char			idStr[CONST_qyMessengerIdStrLen  +  1]	=		"";
	 TCHAR			tBuf[256  +  1];
	 char			buf[256  +  1]							=		"";

	 if  (  !misServName  ||  !pIdInfo  )  return  FALSE;

	 if  (  !idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;

				//				   0		   1	2		   3			 4			     5			
	 sqlStr  =  CString(  "select id,misServName,idStr,name,startTime,tLastModifiedTime"  )
					+  " from "  +  CONST_tabName_qyImGrpInfoTab;
	 whereStr  =  CONST_tmpStr;
	 whereStr  =  whereStr  +  " and misServName="  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )  +  " and idStr="  +  getDbValStr(  iDbType,  CONST_iDataType_idStr,  CString(  idStr  )  );
	 if  (  whereStr  ==  CONST_tmpStr  )  {
		 traceLogA(  "条件应该设置"  );  goto  errLabel;
	 }
	 sqlStr  =  sqlStr  +  " where "  +  whereStr;
	 traceLogA(  "sql is [%S]",  sqlStr.GetBuffer(  0  )  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  sqlStr,  mycountof(  varVals  ),  varVals  )  )  goto  errLabel;

	 if  (  pRcd  )  {

		 memset(  pRcd,  0,  sizeof(  pRcd[0]  )  );

         index  =  0;	 //  id
		 MACRO_sqlLong(  varVals[index],  pRcd->id  );
         index  ++  ;	 //  misServName
		 MACRO_sqlStr(  varVals[index],  pRcd->misServName,  mycountof(  pRcd->misServName  )  );  
         index  ++  ;	 //  idStr
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo  );
		 index  ++  ;	 //  name
		 MACRO_sqlStr(  varVals[index],  pRcd->name,  mycountof(  pRcd->name  )  );  
		 index  ++  ;	//  startTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->startTime  =  gettTimeByBuf(  buf  );
		 index  ++  ;	//  tLastModifiedTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tLastModifiedTime  =  gettTimeByBuf(  buf  );
		 index  ++  ;

	 }
	 
	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}
#endif
 
#if  0	//  2013/02/01
 BOOL  bGetImGrpMemBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo_grp,  QY_MESSENGER_ID  *  pIdInfo_mem,  int  iRcdId,  IM_GRP_MEM  *  pRcd  )
{
 	 BOOL			bRet									=		FALSE;
	 CString		sqlStr;
	 CString		whereStr;
	 CDBVariant		varVals[15  +  CONST_qnmMaxRegFields];
	 int			index									=		0;
	 char			ip12Buf[128]							=		"";
	 char			idStr_grp[CONST_qyMessengerIdStrLen  +  1]	=		"";
	 char			idStr_mem[CONST_qyMessengerIdStrLen  +  1]	=		"";
	 TCHAR			tBuf[256  +  1];
	 char			buf[256  +  1]							=		"";

				//				   0		   1	2		   3			 4			     5			
	 sqlStr  =  CString(  "select id,misServName,idStr_grp,idStr_mem,iRole,startTime,tLastModifiedTime,iStatus"  )
					+  " from "  +  CONST_tabName_qyImGrpMemTab;
	 whereStr  =  CONST_tmpStr;
	 if  (  misServName  &&  pIdInfo_grp  &&  pIdInfo_mem  )  {
		 idInfo2Str(  pIdInfo_grp,  idStr_grp,  mycountof(  idStr_grp  )  );
		 idInfo2Str(  pIdInfo_mem,  idStr_mem,  mycountof(  idStr_mem  )  );
		 whereStr  =  whereStr  +  " and misServName="  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )  + " and idStr_grp='"  +  idStr_grp  +  "' and idStr_mem='"  +  idStr_mem  +  "'";
		}
	 else  whereStr  =  whereStr  +  " and id="  +  ltoa(  iRcdId,  buf,  10  );
	 if  (  whereStr  ==  CONST_tmpStr  )  {
		 traceLogA(  "条件应该设置"  );  goto  errLabel;
	 }
	 sqlStr  =  sqlStr  +  " where "  +  whereStr;
	 traceLogA(  "sql is [%S]",  sqlStr.GetBuffer(  0  )  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  sqlStr,  mycountof(  varVals  ),  varVals  )  )  goto  errLabel;

	 if  (  pRcd  )  {

		 memset(  pRcd,  0,  sizeof(  pRcd[0]  )  );

         index  =  0;	 //  id
		 MACRO_sqlLong(  varVals[index],  pRcd->id  );
         index  ++  ;	 //  misServName
		 MACRO_sqlStr(  varVals[index],  pRcd->misServName,  mycountof(  pRcd->misServName  )  );  
         index  ++  ;	 //  idStr_grp
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo_grp  );
		 index  ++  ;	 //  idStr_mem
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo_mem  );
		 index  ++  ;	//  iRole
		 MACRO_sqlLong(  varVals[index],  pRcd->iRole  );
		 index  ++  ;	//  startTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->startTime  =  gettTimeByBuf(  buf  );
		 index  ++  ;	//  tLastModifiedTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tLastModifiedTime  =  gettTimeByBuf(  buf  );
		 index  ++  ;	//  iStatus
		 MACRO_sqlLong(  varVals[index],  pRcd->iStatus  );
		 index  ++  ;

	 }
	 
	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}
#endif



  BOOL  bGetCustomerServiceObjRcdBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  iRcdId,  CUSTOMER_serviceObj_rcd  *  pRcd  )
{
 	 BOOL			bRet									=		FALSE;
	 CString		sqlStr;
	 CString		whereStr;
	 CDBVariant		varVals[15  +  CONST_qnmMaxRegFields];
	 int			index									=		0;
	 char			ip12Buf[128]							=		"";
	 char			idStr[CONST_qyMessengerIdStrLen  +  1]	=		"";
	 TCHAR			tBuf[256  +  1];
	 char			buf[256  +  1]							=		"";

				//				   0		   1	2		   3			 4			     5			
	 sqlStr  =  CString(  "select id,misServName,idStr,uiLangId,uiCategoryId,startIp,endIp,startTime,tLastModifiedTime"  )
					+  " from "  +  CONST_tabName_qyCustomerServiceObjTab;
	 whereStr  =  CONST_tmpStr;
	 if  (  misServName  &&  pIdInfo  )  {
		 idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  );
		 whereStr  =  whereStr  +  " and misServName="  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )  + " and idStr='"  +  idStr  +  "'";
		}
	 else  whereStr  =  whereStr  +  " and id="  +  ltoa(  iRcdId,  buf,  10  );
	 if  (  whereStr  ==  CONST_tmpStr  )  {
		 traceLogA(  ""  );  
		 goto  errLabel;
	 }
	 sqlStr  =  sqlStr  +  " where "  +  whereStr;
	 traceLogA(  "sql is [%S]",  sqlStr.GetBuffer(  0  )  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  sqlStr,  mycountof(  varVals  ),  varVals  )  )  goto  errLabel;

	 if  (  pRcd  )  {

		 memset(  pRcd,  0,  sizeof(  pRcd[0]  )  );

         index  =  0;	 //  id
		 MACRO_sqlLong(  varVals[index],  pRcd->id  );
         index  ++  ;	 //  misServName
		 MACRO_sqlStr(  varVals[index],  pRcd->misServName,  mycountof(  pRcd->misServName  )  );  
         index  ++  ;	 //  idStr
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo  );
		 index  ++  ;	//  uiLangId
		 MACRO_sqlLong(  varVals[index],  pRcd->uiLangId  );
		 index  ++  ;	//  uiCategoryId;
		 MACRO_sqlLong(  varVals[index],  pRcd->uiCategoryId  );
		 index  ++  ;	//  startIp;
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );	qyIp12ToStd(  buf,  pRcd->startIp  );
		 index  ++  ;	//  endIp
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  qyIp12ToStd(  buf,  pRcd->endIp  );
		 index  ++  ;	//  startTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->startTime  =  gettTimeByBuf(  buf  );
		 index  ++  ;	//  tLastModifiedTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tLastModifiedTime  =  gettTimeByBuf(  buf  );
		 index  ++  ;

	 }
	 

	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}


 BOOL  bGetWebContactRcdBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  iRcdId,  WEB_CONTACT_RCD  *  pRcd  )
{
 	 BOOL			bRet									=		FALSE;
	 CString		sqlStr;
	 CString		whereStr;
	 CDBVariant		varVals[15  +  CONST_qnmMaxRegFields];
	 int			index									=		0;
	 char			ip12Buf[128]							=		"";
	 char			idStr[CONST_qyMessengerIdStrLen  +  1]	=		"";
	 TCHAR			tBuf[256  +  1];
	 char			buf[256  +  1]							=		"";
	 

				//				   0		   1	2		   3			 4			     5			
	 sqlStr  =  CString(  "select id,misServName,idStr,ucbPublic,grpDisplayName,displayName,ucbImSwitchable,startTime,tLastModifiedTime,iStatus"  )
					+  " from "  +  CONST_tabName_qyWebContactTab;
	 whereStr  =  CONST_tmpStr;
	 if  (  misServName  &&  pIdInfo  )  {
		 idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  );
		 whereStr  =  whereStr  +  " and misServName="  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )  + " and idStr='"  +  idStr  +  "'";
		}
	 else  whereStr  =  whereStr  +  " and id="  +  ltoa(  iRcdId,  buf,  10  );
	 if  (  whereStr  ==  CONST_tmpStr  )  {
		 traceLogA(  "条件应该设置"  );  goto  errLabel;
	 }
	 sqlStr  =  sqlStr  +  " where "  +  whereStr;
	 traceLogA(  "sql is [%S]",  sqlStr.GetBuffer(  0  )  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  sqlStr,  mycountof(  varVals  ),  varVals  )  )  goto  errLabel;

	 if  (  pRcd  )  {

		 memset(  pRcd,  0,  sizeof(  pRcd[0]  )  );

         index  =  0;	 //  id
		 MACRO_sqlLong(  varVals[index],  pRcd->id  );
         index  ++  ;	 //  misServName
		 MACRO_sqlStr(  varVals[index],  pRcd->misServName,  mycountof(  pRcd->misServName  )  );  
         index  ++  ;	 //  idStr
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo  );
		 index  ++  ;	//  ucbPublic
		 MACRO_sqlUcb(  varVals[index],  pRcd->ucbPublic  );
		 index  ++  ;	//  grpDisplayName
		 MACRO_sqlStr(  varVals[index],  pRcd->grpDisplayName,  mycountof(  pRcd->grpDisplayName  )  );
		 index  ++  ;	//  displayName
		 MACRO_sqlStr(  varVals[index],  pRcd->displayName,  mycountof(  pRcd->displayName  )  );
		 index  ++  ;	//  ucbImSwitchable
		 MACRO_sqlUcb(  varVals[index],  pRcd->ucbImSwitchable  );
		 index  ++  ;	//  startTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->startTime  =  gettTimeByBuf(  buf  );
		 index  ++  ;	//  tLastModifiedTime
		 MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tLastModifiedTime  =  gettTimeByBuf(  buf  );
		 index  ++  ;	//  iStatus
		 MACRO_sqlLong(  varVals[index],  pRcd->iStatus  );
		 index  ++  ;

	 }
	 

	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}



#if  0
 int  tmpHandler_enumMisTasks(  void  *  p0Param,  void  *  p1Param,  void  *  pVarValsParam  )
{
	int						iErr			=	-1;
	COMMON_PARAM		*	pCommonParam	=	(  COMMON_PARAM  *  )p0Param;
	PF_commonHandler		pf				=	(  PF_commonHandler  )pCommonParam->p0;
	void				*	p0				=	pCommonParam->p1;
	void				*	p1				=	pCommonParam->p2;
	IM_TASK_RCD			*	pRcd			=	(  IM_TASK_RCD  *  )p1Param;
	CDBVariant			*	varVals			=	(  CDBVariant  *  )pVarValsParam;
	//
	int						index;
	TCHAR					tBuf[256];
	 char					buf[256];
	 long					lVal;
	 int					i;


	if  (  pRcd  )  {
		 memset(  pRcd,  0,  sizeof(  pRcd[0]  )  );

         index  =  0;	MACRO_sqlLong(  varVals[index],  pRcd->id  );
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->misServName,  mycountof(  pRcd->misServName  )  );
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo_send  );
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->senderDesc,  mycountof(  pRcd->senderDesc  )  );
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tSendTime  =  gettTimeByBuf(  buf  );
		 index  ++  ;	MACRO_sqlLong(  varVals[index],  pRcd->uiTranNo  );
		 index  ++  ;	MACRO_sqlLong(  varVals[index],  pRcd->uiContentType  );
		 index  ++  ;	MACRO_sqlLong(  varVals[index],  pRcd->uiSerialNo  );
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo_recv  );
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->receiverDesc,  mycountof(  pRcd->receiverDesc  )  );
		 //
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tRecvTime  =  gettTimeByBuf(  buf  );
		 index  ++  ;	MACRO_sqlLong(  varVals[index],  lVal  );  pRcd->usRespCode  =  (  unsigned  short  )lVal;

		 index  ++  ;	MACRO_sqlLong(  varVals[index],  lVal  );  pRcd->ibReply  =  lVal;
		 index  ++  ;	MACRO_sqlLong(  varVals[index],  lVal  );  pRcd->uiType  =  lVal;
		 index  ++  ;	MACRO_sqlLong(  varVals[index],  lVal  );  pRcd->uiMode  =  lVal;
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->subTypeStr,  mycountof(  pRcd->subTypeStr  )  );
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->subject,  mycountof(  pRcd->subject  )  );  
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->content,  mycountof(  pRcd->content  )  );  
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->txtContent,  mycountof(  pRcd->txtContent  )  );  
		 index  ++  ;	MACRO_sqlLong(  varVals[index],  lVal  );  pRcd->ibNeedReply  =  lVal;
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tEndTime  =  gettTimeByBuf(  buf  );
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->issuer,  mycountof(  pRcd->issuer  )  );
		 index  ++	;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tIssueTime  =  gettTimeByBuf(  buf  );
		 //
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tStartTime_req  =  gettTimeByBuf(  buf  );
		 index  ++  ;	MACRO_sqlLong(  varVals[index],  pRcd->uiTranNo_req  );
		 //
		 index  ++  ;	MACRO_sqlLong(  varVals[index],  lVal  );  pRcd->iStatus  =  lVal;
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tLastModifiedTime  =  gettTimeByBuf(  buf  );
		 //
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo_auditor  );
		 index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo_replyTo  );
		 //
		 for  (  i  =  0;  i  <  10;  i  ++  )  {
			  index  ++  ;	MACRO_sqlLong(  varVals[index],  pRcd->iProps[i]  );
		 }
		 for  (  i  =  0;  i  <  10;  i  ++  )  {
			  index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  lstrcpyn(  pRcd->propStrs[i],  tBuf,  mycountof(  pRcd->propStrs[i]  )  );  
		 }

		 if  (  pf  )  pf(  p0,  p1,  pRcd  );

	 }
	
	iErr  =  0;

//  errLabel:

	return  iErr;
}

 int  enumImTasks(  void  *  pDb,  int  iDbType,  BOOL  bHisTab,  LPCTSTR  misServName,  LPCTSTR  whereClause,  PF_commonHandler  pf,  void  *  p0,  void  *  p1,  unsigned  int  *puiRcdCnt,  IM_TASK_RCD  *  pTaskRcd  )
{
	int					iErr								=	-1;
	TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	CDBVariant			varVals[50];
	COMMON_PARAM		commonParam;
	TCHAR			*	pTabName							=	bHisTab  ?  CONST_tabName_qyImTaskHisTab  :  CONST_tabName_qyImTaskTab;

	if  (  !whereClause  )  whereClause  =  CString(  "1=1"  );

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select id,misServName,idStr_send,senderDesc,tSendTime,uiTranNo,uiContentType,uiSerialNo,idStr_recv,receiverDesc"  )
													_T(  ",tRecvTime,usRespCode,ibReply,uiType,uiMode,subTypeStr,subject,content0,txtContent0,ibNeedReply,tEndTime,issuer,tIssueTime"  )
													_T(  ",tStartTime_req,uiTranNo_req"  )
													_T(  ",iStatus,tLastModifiedTime"  )
													_T(  ",idStr_auditor,idStr_replyTo"  )
													_T(  ",iProp0,iProp1,iProp2,iProp3,iProp4,iProp5,iProp6,iProp7,iProp8,iProp9"  )
													_T(  ",propStr0,propStr1,propStr2,propStr3,propStr4,propStr5,propStr6,propStr7,propStr8,propStr9"  )
													_T(  " from %s where %s"  ),  pTabName,  whereClause  );

	MACRO_makeCommonParam3(  pf,  p0,  p1,  commonParam  );
	if  (  enumSqlQuery(  pDb,  sqlBuf,  tmpHandler_enumMisTasks,  &commonParam,  pTaskRcd,  varVals,  mycountof(  varVals  ),  puiRcdCnt  )  )  goto  errLabel;
	
	iErr  =  0;

errLabel:
	return  iErr;
}
#endif
#if  0  //  2013/02/06
 BOOL  bGetImTaskRcdBySth(  void  *  pDb,  int  iDbType,  BOOL  bHisTab,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  time_t  tSendTime,  unsigned  int  uiTranNo,  int  id,  IM_TASK_RCD  *  pRcd  )
{
	 BOOL			bRet								=	FALSE;
	 TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	 TCHAR			whereClause[256]					=	_T(  ""  );
	 unsigned  int	uiRcdCnt							=	0;


	 if  (  misServName  &&  pIdInfo  )  {
		 char	timeBuf[CONST_qyTimeLen  +  1]	=	"";
		 char	idStr[CONST_qyMessengerIdStrLen  +  1]	=	"";
		 //
		 getTimeStr(  tSendTime,  timeBuf,  mycountof(  timeBuf  )  );
		 idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  );
		 _sntprintf(  whereClause,  mycountof(  whereClause  ),  _T(  "misServName=%s and idStr_send='%s' and tSendTime='%s' and uiTranNo=%d"  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  idStr  ),  CString(  timeBuf  ),  uiTranNo  );
		}
	 else  {
		   _sntprintf(  whereClause,  mycountof(  whereClause ),  _T(  "id =%d"  ),  id  );
	 }

	 if  (  enumImTasks(  pDb,  iDbType,  bHisTab,  misServName,  whereClause,  NULL,  0,  0,  &uiRcdCnt,  pRcd  )  )  goto  errLabel;
	 if  (  !uiRcdCnt  )  goto  errLabel;
	

	 bRet   =  TRUE;

errLabel:

	 return  bRet;
}
#endif

#if 0  //  2013/02/02
 //  pRegInfo->auditTime,qyPcRegInfoTab
 int  qisRegUsrInfo(  void  *  pDb,  int  iDbType,  QY_DMITEM  *  pFieldIdTable,  QY_MESSENGER_INFO  *  pMessengerInfo,  QY_MESSENGER_REGINFO  *  pRegInfo,  BOOL  bLogReRegEvent  )
{
	 int						iErr										=	-1;
	 CString					sqlStr;
	 int						i;
	 int						iQwmVer										=	0;
	 CDBVariant					varVals[5];
	 unsigned  char				ucbAudited									=	FALSE;
	 unsigned  char				ucbReged									=	FALSE;
	 QIS_EVENT					tmpEvent;
	 int						index;
	 TCHAR						tBuf[1024];
	 char						idStr[CONST_qyMessengerIdStrLen  +  1]		=	"";

	 traceLogA(  "qisRegUsrInfo enters"  );

	 if  (  !pRegInfo  )  goto  errLabel;
	 if  (  !pMessengerInfo  )  {
		 if  (  !bMessengerIdValid(  &pRegInfo->addr.idInfo  )  )  goto  errLabel;
		}
	 else  {
		   if  (  !bMessengerIdValid(  &pMessengerInfo->idInfo  )  )  goto errLabel;
		   pRegInfo->addr.idInfo.ui64Id  =  pMessengerInfo->idInfo.ui64Id;
	 }
	 if  (  !idInfo2Str(  &pRegInfo->addr.idInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
	 
	 getCurTime(  pRegInfo->tLastModifiedTime  );


	 MACRO_setPtrs(  pFieldIdTable,  pRegInfo[0],  pRegInfo->fields  );
	 for  (  i  =  0;  i  <  CONST_qnmMaxRegFields;  i  ++  )  {
		  if  (  pRegInfo->fields[i].bufSize  )  pRegInfo->fields[i].ptr[pRegInfo->fields[i].bufSize  -  1]  =  0;
	 }

	 sqlStr  =  CString(  "select auditTime from qyImObjRegInfoTab where idStr='"  )  +  idStr  +  "'";
	 if  (  bQyGetRcdBySql(  pDb,  sqlStr.GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  {
		 ucbReged  =  TRUE;
		 index  =  0;
		 MACRO_sqlStr(  varVals[index],  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
		 if  (  lstrlen(  tBuf  )  ==  CONST_qyTimeLen  )  ucbAudited  =  TRUE;		 
	 }

	 memset(  &tmpEvent,  0,  sizeof(  tmpEvent  )  );

	 if  (  !ucbReged  )  {						//  未注册的情况
		 getCurTime(  pRegInfo->regTime  );
		 sqlStr  =  CString(  "insert into qyImObjRegInfoTab(misServName,idStr,regTime,auditTime,tLastModifiedTime,col0,col1,col2,col3,col4,col5,col6,col7,col8,col9,col10,col11,col12,col13,col14,col15,col16,col17,col18,col19,comment0)"  )  +
							  "values("  +  
							  getDbValStr(  iDbType,  CONST_iDataType_misServName,  pRegInfo->addr.misServName  )  +  ","  +
							  "'"  +  idStr  +  "',"  +
							  "'"  +  pRegInfo->regTime  +  "',"  +
							  "'"  +  pRegInfo->auditTime  +  "',"  +
							  "'"  +  pRegInfo->tLastModifiedTime  +  "',";
		 for  (  i  =  0;  i  <  20;  i  ++  )  {
			  sqlStr  =  sqlStr  +  getDbValStr(  iDbType,  pRegInfo->fields[i].iDataType,  pRegInfo->fields[i].ptr  )  +  ",";
		 }
		 sqlStr  =  sqlStr  +  "''"  +  ")";
		 if  (  !bQyExecSql(  pDb,  sqlStr.GetBuffer(  0  )  )  )  {
			 traceLogA(  "qnmRegUsrInfo: insert into qyPcRegInfoTab failed"  );
			 goto  errLabel;
		 }			 

		 if  (  pMessengerInfo  )  {

			 //  作操作日志	
			 tmpEvent.lEventType  =  CONST_qyEventType_nm_newReg;
		 	 tmpEvent.iCustomId  =  pRegInfo->iCustomId;
		 	 getCurTime(  tmpEvent.localEventTime  );
			 lstrcpyn(  tmpEvent.misServName,  pRegInfo->addr.misServName,  mycountof(  tmpEvent.misServName  )  );
			 tmpEvent.idInfo.ui64Id  =  pMessengerInfo->idInfo.ui64Id;			 
		 	 safeStrnCpy(  pMessengerInfo->ip,  tmpEvent.ip,  sizeof(  tmpEvent.ip  )  );
				
		 	 for  (  i  =  0;  gpRegEventRegColsTable[i].type  !=  -1;  i  ++  )  {
				  if  (  gpRegEventRegColsTable[i].type  ==  CONST_nullColId  )  continue;
			  	  MACRO_qyAssert(  gpRegEventRegColsTable[i].type  <  CONST_qnmMaxRegFields,  _T(  "qpRegEventRegColsTabl[n].type 太大, 不能超过CONST_qnmMaxRegFields"  )  );
			  	  MACRO_qyAssert(  i  <  CONST_qnmMaxEventRegFields,  _T(  "gpRegEventRegColsTable项数太多，不能超过CONST_qnmMaxEventRegFields"  )  );
			  	  lstrcpyn(  tmpEvent.cols[i],  (  TCHAR  *  )pRegInfo->u.cols[gpRegEventRegColsTable[i].type],  sizeof(  tmpEvent.cols[i]  )  /  sizeof(  TCHAR  )  );
		 	 }
			
			 logEvent_is(  pDb,  iDbType,  pMessengerInfo,  &tmpEvent  );

		 }

		 iErr  =  0;  goto  errLabel;
	
	 }

	 //  下面已注册
	 //

	 //  未审核，或pRegInfo属审核信息
	 if  (  !ucbAudited  ||  pRegInfo->auditTime[0]  )  {
		
		 sqlStr  =  CString(  "update qyImObjRegInfoTab set "  );
		 //  if  (  pRegInfo->auditTime[0]  )  sqlStr  +=  CString(  "auditTime='"  )  +  pRegInfo->auditTime  +  "',";
		 sqlStr  +=  CString(  "auditTime='"  )  +  (  pRegInfo->auditTime[0]  ?  pRegInfo->auditTime  :  ""  )  +  "',";
		 if  (  pRegInfo->regTime[0]  )  sqlStr  +=  CString(  "regTime='"  )  +  pRegInfo->regTime  +  "',";
		 sqlStr  +=  CString(  "tLastModifiedTime='"  )  +  pRegInfo->tLastModifiedTime  +  "',";
		 //		 
		 for  (  i  =  0;  i  <  20;  i  ++  )  {
			 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "col%d"  ),  i  );  
			 sqlStr  =  sqlStr  +  tBuf  +  "="  +  getDbValStr(  iDbType,  pRegInfo->fields[i].iDataType,  pRegInfo->fields[i].ptr  )  +  ",";
		 }
		 sqlStr  =  sqlStr  +  "comment0='' where idStr='"  +  idStr  +  "'";  
		 
	 	 if  (  !bQyExecSql(  pDb,  sqlStr.GetBuffer(  0  )  )  )  {
			 traceLogA(  "qnmRegUsrInfo: update qyPcRegInfoTab failed"  );
			 goto  errLabel;
		 }
		
		 sqlStr  =  CString(  ""  )  +  "delete from qyImObjRegInfoTab1 where idStr='"  +  idStr  +  "'";
		 if  (  !bQyExecSql(  pDb,  sqlStr.GetBuffer(  0  )  )  )  {
			 traceLogA(  "qnmRegUsrInfo: delete from qyPcRegInfoTab1 failed"  );
			 goto  errLabel;
		 }


		 if  (  bLogReRegEvent  )  {  //  2008/02/15
		 	 if  (  pMessengerInfo  )  {
		 
				 tmpEvent.lEventType  =  CONST_qyEventType_nm_reReg;
				 tmpEvent.iCustomId  =  pRegInfo->iCustomId;
				 getCurTime(  tmpEvent.localEventTime  );
				 lstrcpyn(   tmpEvent.misServName,  pRegInfo->addr.misServName,  mycountof(  tmpEvent.misServName  )  );
				 tmpEvent.idInfo.ui64Id  =  pMessengerInfo->idInfo.ui64Id;
				 safeStrnCpy(  pMessengerInfo->ip,  tmpEvent.ip,  sizeof(  tmpEvent.ip  )  );
					
				 for  (  i  =  0;  gpRegEventRegColsTable[i].type  !=  -1;  i  ++  )  {
					  if  (  gpRegEventRegColsTable[i].type  ==  CONST_nullColId  )  continue;
					  MACRO_qyAssert(  gpRegEventRegColsTable[i].type  <  CONST_qnmMaxRegFields,  _T(  "qpRegEventRegColsTabl[n].type 太大, 不能超过CONST_qnmMaxRegFields"  )  );
					  MACRO_qyAssert(  i  <  CONST_qnmMaxEventRegFields,  _T(  "gpRegEventRegColsTable项数太多，不能超过CONST_qnmMaxEventRegFields"  )  );
					  lstrcpyn(  tmpEvent.cols[i],  (  TCHAR  *  )pRegInfo->u.cols[gpRegEventRegColsTable[i].type],  sizeof(  tmpEvent.cols[i]  )  /  sizeof(  TCHAR  )  );
				 }

				 logEvent_is(  pDb,  iDbType,  pMessengerInfo,  &tmpEvent  );					
			 }
		 }
		 
		 iErr  =  0;  goto  errLabel;

	 }
	 
	 //  已审核，且pRegInfo属未审核信息，pRegInfo将更新入qyPcRegInfoTab1中
	 //
	 if  (  qisRegUsrInfoInTab(  pDb,  iDbType,  pFieldIdTable,  pMessengerInfo,  pRegInfo,  CONST_tabName_qyImObjRegInfoTab1  )  )  goto  errLabel;


	 iErr  =  0;

errLabel:

	 traceLogA(  "qisRegUsrInfo leaves"  );

	 return  iErr;

}
#endif
#if  0
 int  recoverMessengerPhoneInfo(  void  *  pDb,  int  iDbType,  MSGR_ADDR  *  pAddr,  void  *  p1  )
{
	int							iErr									=		-1;
	QY_MESSENGER_phoneInfo		rcd;
	TCHAR						sqlBuf[CONST_maxSqlBufLen  +  1]		=		_T(  ""  );
	char						timeBuf[CONST_qyTimeLen  +  1]			=		"";
	char						idStr[CONST_qyMessengerIdStrLen  +  1]	=		"";

    
	if  (  !pAddr  )  return  -1;

	if  (  !g_dbFuncs.pf_bGetMessengerPhoneInfoBySth(  pDb,  iDbType,  pAddr->misServName,  0,  0,  &pAddr->idInfo,  0,  &rcd  )  )  memset(  &rcd,  0,  sizeof(  rcd  )  );

	getCurTime(  timeBuf  );
	idInfo2Str(  &pAddr->idInfo,  idStr,  mycountof(  idStr  )  );

	if  (  !pAddr->uiDevType  )  {
		if  (  rcd.id  )  {
			_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s where id=%d"  ),  CONST_tabName_qyMessengerPhoneInfoTab,  rcd.id  );
			if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;
		}
		}
	else  {
		  if  (  pAddr->uiDevType  !=  rcd.uiDevType  ||  lstrcmpi(  pAddr->wDevIdStr,  rcd.wDevIdStr  )  )  {
	  		  if  (  !rcd.id  )  {
				  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into %s(misServName,uiDevType,wDevIdStr,idStr,iStatus,startTime,tLastModifiedTime) values(%s,%d,%s,'%s',%d,'%s','%s')"  ),  
					  CONST_tabName_qyMessengerPhoneInfoTab,  getDbValStr(  iDbType,  CONST_iDataType_misServName,  pAddr->misServName  ),  pAddr->uiDevType,  getDbValStr(  iDbType,  CONST_iDataType_wDevIdStr,  pAddr->wDevIdStr  ),  CString(  idStr  ),  0,  CString(  timeBuf  ),  CString(  timeBuf  )  );
				  if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;
				  }
			  else  {
				    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set uiDevType=%d,wDevIdStr=%s,tLastModifiedTime='%s' where id=%d"  ), 
							 CONST_tabName_qyMessengerPhoneInfoTab, pAddr->uiDevType,  getDbValStr(  iDbType,  CONST_iDataType_wDevIdStr,  pAddr->wDevIdStr  ),  CString(  timeBuf  ),  rcd.id  );
					if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;
			  }

		  }
	}


	iErr  =  0;
errLabel:

	if  (  iErr  )  {
		traceLogA(  "recoverMessengerPhoneInfo failed"  );
	}
	return  iErr;

}
#endif

 BOOL  bGetQyVDevComRcdBySth(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  WCHAR  *  wDevIdStr,  int  id,  QY_VDEVCOM_RCD  *  pRcd  )
{
	BOOL		bRet										=	FALSE;
	CString		sqlStr;
	char		idStr[CONST_qyMessengerIdStrLen  +  1]		=	"";
	TCHAR		whereClause[CONST_maxSqlClauseLen  +  1]	=	_T(  ""  );
	char		buf[128];
	CDBVariant	varVals[32];
	int			index;
	TCHAR		tBuf[255  +  1];
		
	sqlStr  =  CString(  ""  )  +  _T(  "select id,misServName,idStr,wDevIdStr,name,model,smsc,iStatus,startTime,endTime from "  )  +  CONST_tabName_qyVDevComTab;

	if  (  misServName  &&  bMessengerIdValid(  pIdInfo  )  &&  wDevIdStr  )  {
		idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  );
        sqlStr  =  sqlStr  +  " where misServName="  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )  +  " and idStr='"  +  idStr  +  "' and wDevIdStr="  +  getDbValStr(  iDbType,  CONST_iDataType_wDevIdStr,  wDevIdStr  );
		}
	else  {
		  sqlStr  =  sqlStr  +  " where id="  +  ltoa(  id,  buf,  10  );
	}

	if  (  !bQyGetRcdBySql(  pDb,  sqlStr.GetBuffer(  0  ),  mycountof(  varVals  ),  varVals  )  )  goto  errLabel;

	if  (  pRcd  )  {
		memset(  pRcd,  0,  sizeof(  pRcd[0]  )  );

		index  =  0;	MACRO_sqlLong(  varVals[index],  pRcd->id  );
		index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->misServName,  mycountof(  pRcd->misServName  )  );  
		index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo  );
		index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->wDevIdStr,  mycountof(  pRcd->wDevIdStr  )  );
		index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->name,  mycountof(  pRcd->name  )  );
		index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->model,  mycountof(  pRcd->model  )  );
		index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRcd->smsc,  mycountof(  pRcd->smsc  )  );
		index  ++  ;	MACRO_sqlLong(  varVals[index],  pRcd->iStatus  );
		index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRcd->startTime,  mycountof(  pRcd->startTime  )  );
		index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRcd->endTime,  mycountof(  pRcd->endTime  )  );
		index  ++  ;

	}

	bRet  =  TRUE;
errLabel:
	return  bRet;
}



 BOOL  bGetQySmContactRcdBySth(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  WCHAR  *  wDevIdStr,  unsigned  char  ucbDefaultSmServer,  int  id,  QY_SMCONTACT_RCD  *  pRcd  )
{
	BOOL		bRet										=	FALSE;
	CString		sqlStr;
	char		idStr[CONST_qyMessengerIdStrLen  +  1]		=	"";
	TCHAR		whereClause[CONST_maxSqlClauseLen  +  1]	=	_T(  ""  );
	char		buf[128];
	CDBVariant	varVals[32];
	int			index;
	TCHAR		tBuf[255  +  1];
		
	sqlStr  =  CString(  ""  )  +  _T(  "select id,misServName,idStr,wDevIdStr,ucbDefaultSmServer,cusName,ucbPublic,ucbDefault,idStr_contact,displayName,ucbImSwitchable,iStatus,startTime,endTime from "  )  +  CONST_tabName_qySmContactTab;

	if  (  misServName  &&  bMessengerIdValid(  pIdInfo  )  &&  wDevIdStr  )  {
		idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  );
		sqlStr  =  sqlStr  +  " where misServName="  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )  +  " and idStr='"  +  idStr  +  "' and wDevIdStr="  +  getDbValStr(  iDbType,  CONST_iDataType_wDevIdStr,  wDevIdStr  ) +  " and ucbDefaultSmServer='"  +  (  ucbDefaultSmServer  ?  "1"  :  ""  )  +  "'" ;
		}
	else  {
		  sqlStr  =  sqlStr  +  " where id="  +  ltoa(  id,  buf,  10  );
	}

	if  (  !bQyGetRcdBySql(  pDb,  sqlStr.GetBuffer(  0  ),  mycountof(  varVals  ),  varVals  )  )  goto  errLabel;

	if  (  pRcd  )  {
		memset(  pRcd,  0,  sizeof(  pRcd[0]  )  );

		index  =  0;	MACRO_sqlLong(  varVals[index],  pRcd->id  );
		index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->misServName,  mycountof(  pRcd->misServName  )  );  
		index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo  );
		index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->wDevIdStr,  mycountof(  pRcd->wDevIdStr  )  );
		index  ++  ;	MACRO_sqlUcb(  varVals[index],  pRcd->ucbDefaultSmServer  );
		index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->cusName,  mycountof(  pRcd->cusName  )  );
		index  ++  ;	MACRO_sqlUcb(  varVals[index],  pRcd->ucbPublic  );
		index  ++  ;	MACRO_sqlUcb(  varVals[index],  pRcd->ucbDefault  );
		index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo_contact  );
		index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->displayName,  mycountof(  pRcd->displayName  )  );
		index  ++  ;	MACRO_sqlUcb(  varVals[index],  pRcd->ucbImSwitchable  );		
		index  ++  ;	MACRO_sqlLong(  varVals[index],  pRcd->iStatus  );
		index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRcd->startTime,  mycountof(  pRcd->startTime  )  );
		index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRcd->endTime,  mycountof(  pRcd->endTime  )  );
		index  ++  ;

	}

	bRet  =  TRUE;
errLabel:
	return  bRet;
}


 BOOL  bGetQyDynBmpRuleRcdBySth(  void  *  pDb,  int  iDbType,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  QY_MESSENGER_ID  *  pIdInfo_visitor,  int  id,  QY_dynBmpRule_RCD  *  pRcd  )
{
	BOOL		bRet												=	FALSE;
	CString		sqlStr;
	char		idStr[CONST_qyMessengerIdStrLen  +  1]				=	"";
	char		idStr_visitor[CONST_qyMessengerIdStrLen  +  1]		=	"";
	TCHAR		whereClause[CONST_maxSqlClauseLen  +  1]			=	_T(  ""  );
	char		buf[128];
	CDBVariant	varVals[32];
	int			index;
	TCHAR		tBuf[255  +  1];
		
	sqlStr  =  CString(  ""  )  +  _T(  "select id,misServName,idStr,idStr_visitor,uiRuleCmd,iStatus,startTime,endTime from "  )  +  CONST_tabName_qyDynBmpRuleTab;

	if  (  misServName  &&  bMessengerIdValid(  pIdInfo  )  &&  bMessengerIdValid(  pIdInfo_visitor  )  )  {
		idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  );
		idInfo2Str(  pIdInfo_visitor,  idStr_visitor,  mycountof(  idStr_visitor  )  );

        sqlStr  =  sqlStr  +  " where misServName="  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )  +  " and idStr='"  +  idStr  +  "' and idStr_visitor='"  +  idStr_visitor  +  "'";
		}
	else  {
		  sqlStr  =  sqlStr  +  " where id="  +  ltoa(  id,  buf,  10  );
	}

	if  (  !bQyGetRcdBySql(  pDb,  sqlStr.GetBuffer(  0  ),  mycountof(  varVals  ),  varVals  )  )  goto  errLabel;

	if  (  pRcd  )  {
		memset(  pRcd,  0,  sizeof(  pRcd[0]  )  );

		index  =  0;	MACRO_sqlLong(  varVals[index],  pRcd->id  );
		index  ++  ;	MACRO_sqlStr(  varVals[index],  pRcd->misServName,  mycountof(  pRcd->misServName  )  );  
		index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo  );
		index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo_visitor  );
		index  ++  ;	MACRO_sqlLong(  varVals[index],  pRcd->uiRuleCmd  );
		index  ++  ;	MACRO_sqlLong(  varVals[index],  pRcd->iStatus  );
		index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRcd->startTime,  mycountof(  pRcd->startTime  )  );
		index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  pRcd->endTime,  mycountof(  pRcd->endTime  )  );
		index  ++  ;

	}

	bRet  =  TRUE;
errLabel:
	return  bRet;
}


 BOOL  bGetPhoneGuestRcdBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  unsigned  int  uiDevType,  LPCTSTR  wDevIdStr,  int  id,  PHONE_GUEST_RCD  *  pRcd  )
{
	 BOOL			bRet									=		FALSE;
	 TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1]		=		_T(  ""  );
	 CDBVariant		varVals[30];
	 int			index;
	 TCHAR			tBuf[256];
	 TCHAR			wherePart[CONST_maxSqlClauseLen  +  1]	=		_T(  ""  );
	 char			buf[255  +  1];

	 if  (  !pDbParam  )  return  FALSE;
		
	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select id,misServName,uiDevType,wDevIdStr,messengerPasswd,idStr_owner,iStatus,startTime,tLastModifiedTime from %s"  ),  CONST_tabName_qyPhoneGuestTab  );
     
	 if  (  misServName  &&  wDevIdStr  &&  wDevIdStr[0]  )  {
		 _sntprintf(  wherePart,  mycountof(  wherePart  ),  _T(  "misServName=%s and uiDevType=%d and wDevIdStr=%s"  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  uiDevType,  getDbValStr(  iDbType,  CONST_iDataType_wDevIdStr,  wDevIdStr  )  );
		 }
	 else  
		 _sntprintf(  wherePart,  mycountof(  wherePart  ),  _T(  "id=%d"  ),  id  ); 
	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s where %s"  ),  sqlBuf,  wherePart  );

	 traceLogA(  "sql is %S",  sqlBuf  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  CString(  sqlBuf  ).GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  goto  errLabel;

	 if  (  pRcd  )  {
	 	 memset(  pRcd,  0,  sizeof(  pRcd[0]  )  );

		 index  =  0;		MACRO_sqlLong(  varVals[index],  pRcd->id  );
		 index  ++	;		MACRO_sqlStr(  varVals[index],  pRcd->misServName,  mycountof(  pRcd->misServName  )  );
		 index  ++  ;		MACRO_sqlLong(  varVals[index],  pRcd->uiDevType  );
		 index  ++	;		MACRO_sqlStr(  varVals[index],  pRcd->wDevIdStr,  mycountof(  pRcd->wDevIdStr  )  );
		 index  ++	;		MACRO_sqlStr(  varVals[index],  pRcd->messengerPasswd,  mycountof(  pRcd->messengerPasswd  )  );
		 index  ++	;		MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo_owner  );
		 index  ++  ;		MACRO_sqlLong(  varVals[index],  pRcd->iStatus  );
		 index  ++	;		MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->startTime  =  gettTimeByStr(  buf  );
		 index  ++	;		MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tLastModifiedTime  =  gettTimeByStr(  buf  );
		 index  ++  ;

	 }

	 bRet  =  TRUE;
errLabel:
	 return  bRet;

}


#if  0  //  2013/02/02
 BOOL  bGetMessengerPhoneInfoBySth(  void  *  pDbParam,  int  iDbType,  LPCTSTR  misServName,  unsigned  int  uiDevType,  LPCTSTR  wDevIdStr,  QY_MESSENGER_ID  *  pIdInfo,  int  id,  QY_MESSENGER_phoneInfo  *  pRcd  )
{
	 BOOL			bRet									=		FALSE;
	 TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1]		=		_T(  ""  );
	 CDBVariant		varVals[30];
	 int			index;
	 TCHAR			tBuf[256];
	 TCHAR			wherePart[CONST_maxSqlClauseLen  +  1]	=		_T(  ""  );
	 char			buf[255  +  1];

	 if  (  !pDbParam  )  return  FALSE;
		
	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select id,misServName,uiDevType,wDevIdStr,messengerPasswd,idStr,iStatus,startTime,tLastModifiedTime from %s"  ),  CONST_tabName_qyMessengerPhoneInfoTab  );
     
	 if  (  misServName  &&  wDevIdStr  &&  wDevIdStr[0]  )  {
		 _sntprintf(  wherePart,  mycountof(  wherePart  ),  _T(  "misServName=%s and uiDevType=%d and wDevIdStr=%s"  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  uiDevType,  getDbValStr(  iDbType,  CONST_iDataType_wDevIdStr,  wDevIdStr  )  );
		 }
	 else  if  (  misServName  &&  pIdInfo  )  {
		       idInfo2Str(  pIdInfo,  buf,  mycountof(  buf  )  );
			   _sntprintf(  wherePart,  mycountof(  wherePart  ),  _T(  "misServName=%s and idStr='%s'"  ),  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  ),  CString(  buf  ).GetBuffer(  0  )  );
			   }
	 else  
		 _sntprintf(  wherePart,  mycountof(  wherePart  ),  _T(  "id=%d"  ),  id  ); 
	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s where %s"  ),  sqlBuf,  wherePart  );

	 traceLogA(  "sql is %S",  sqlBuf  );
	 if  (  !bQyGetRcdBySql(  pDbParam,  CString(  sqlBuf  ).GetBuffer(  0  ),  sizeof(  varVals  )  /  sizeof(  varVals[0]  ),  varVals  )  )  goto  errLabel;

	 if  (  pRcd  )  {
	 	 memset(  pRcd,  0,  sizeof(  pRcd[0]  )  );

		 index  =  0;		MACRO_sqlLong(  varVals[index],  pRcd->id  );
		 index  ++	;		MACRO_sqlStr(  varVals[index],  pRcd->misServName,  mycountof(  pRcd->misServName  )  );
		 index  ++  ;		MACRO_sqlLong(  varVals[index],  pRcd->uiDevType  );
		 index  ++	;		MACRO_sqlStr(  varVals[index],  pRcd->wDevIdStr,  mycountof(  pRcd->wDevIdStr  )  );
		 index  ++	;		MACRO_sqlStr(  varVals[index],  pRcd->messengerPasswd,  mycountof(  pRcd->messengerPasswd  )  );
		 index  ++	;		MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &pRcd->idInfo  );
		 index  ++  ;		MACRO_sqlLong(  varVals[index],  pRcd->iStatus  );
		 index  ++	;		MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->startTime  =  gettTimeByStr(  buf  );
		 index  ++	;		MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  pRcd->tLastModifiedTime  =  gettTimeByStr(  buf  );
		 index  ++  ;

	 }

	 bRet  =  TRUE;
errLabel:
	 return  bRet;

}
#endif
 int  qnmLogOpEvent_netMc(  void  *  pDbParam,  int  iDbType,  int  iEventType,  LPCTSTR  usr,  LPCTSTR  dsnName,  LPCTSTR  des  )
{
	QM_dbFuncs  *  pDbFuncs  =  QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;

	int							iErr			=	-1;
	CDatabase				*	pDb				=	(  CDatabase  *  )pDbParam;
	QNM_PC_EVENT				event;
	QNM_PC_EVENT			*	pEvent			=	&event;
	static  long				slHelpRand		=	0;

	memset(  &event,  0,  sizeof(  event  )  );

	pEvent->lHelpRand  =  slHelpRand;  slHelpRand  ++  ;	//  2005/10/01
	pEvent->lEventType  =  iEventType;
	pEvent->iCustomId  =  qyGetCustomId(  );
	safeStrnCpy(  CONST_qyNullMac,  pEvent->macs[0],  sizeof(  pEvent->macs[0]  )  );
	safeStrnCpy(  "127.0.0.1",  pEvent->ip,  sizeof(  pEvent->ip  )  );
	getCurTime(  pEvent->localEventTime  );
	if  (  usr  )  lstrcpyn(  pEvent->usrName,  usr,  sizeof(  pEvent->usrName  )  /  sizeof(  TCHAR  )  );
	if  (  dsnName  )  lstrcpyn(  pEvent->dsnName,  dsnName,  mycountof(  pEvent->dsnName  )  );
	if  (  des  )  lstrcpyn(  pEvent->deses[0],  des,  sizeof(  pEvent->deses[0]  )  );

	getCurTime(  pEvent->cntEventTime  );
	
    if  (  !g_dbFuncs.pf_bLogPcEventFunc(  pDb,  iDbType,  pEvent  )  )  goto  errLabel;

	iErr  =  0;

errLabel:

	 return  iErr;
}

 int  qnmLogOpEvent_is(  void  *  pDbParam,  int  iDbType,  int  iEventType,  LPCTSTR  usr,  LPCTSTR  dsnName,  LPCTSTR  des  )
{
	QM_dbFuncs  *  pDbFuncs  =  QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  return  -1;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;

	int							iErr			=	-1;
	CDatabase				*	pDb				=	(  CDatabase  *  )pDbParam;
	QIS_EVENT					event;
	QIS_EVENT				*	pEvent			=	&event;
	static  long				slHelpRand		=	0;

	memset(  &event,  0,  sizeof(  event  )  );

	pEvent->lHelpRand  =  slHelpRand;  slHelpRand  ++  ;	//  2005/10/01
	pEvent->lEventType  =  iEventType;
	pEvent->iCustomId  =  qyGetCustomId(  );
	safeStrnCpy(  "127.0.0.1",  pEvent->ip,  sizeof(  pEvent->ip  )  );
	getCurTime(  pEvent->localEventTime  );
	if  (  usr  )  lstrcpyn(  pEvent->usrName,  usr,  mycountof(  pEvent->usrName  )  );
	if  (  dsnName  )  lstrcpyn(  pEvent->dsnName,  dsnName,  mycountof(  pEvent->dsnName  )  );
	if  (  des  )  lstrcpyn(  pEvent->deses[0],  des,  mycountof(  pEvent->deses[0]  )  );

	getCurTime(  pEvent->cntEventTime  );
	
    if  (  !g_dbFuncs.pf_bLogEventFunc_is(  pDb,  iDbType,  pEvent  )  )  goto  errLabel;

	iErr  =  0;

errLabel:

	 return  iErr;
}



 int  qnmLogOpEvent(  int  iServiceId,  void  *  pDbParam,  int  iDbType,  int  iEventType,  LPCTSTR  usr,  LPCTSTR  dsnName,  LPCTSTR  des  )
{
	switch  (  iServiceId  )  {
			case  CONST_qyServiceId_netMc:
				  return  qnmLogOpEvent_netMc(  pDbParam,  iDbType,  iEventType,  usr,  dsnName,  des  );
				  break;
			case  CONST_qyServiceId_is:
				  return  qnmLogOpEvent_is(  pDbParam,  iDbType,  iEventType,  usr,  dsnName,  des  );
				  break;
			default:
				    break;
	}

	return  -1;

}

 int  qnmLogOpEvent(  int  iServiceId,  QY_OBJ_DB  *  pObjDb,  int  iEventType,  LPCTSTR  des  )		//  2007/01/02
{
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  -1;
	 if  (  !bObjDbAvail(  pObjDb->pLogObjDb  )  )  return  -1;
	 if  (  !pObjDb->pUsrInfo  )  return  -1;
	 return  qnmLogOpEvent(  iServiceId,  pObjDb->pLogObjDb->pDb,  pObjDb->pLogObjDb->cfg.iDbType,  iEventType,  CString(  pObjDb->pUsrInfo->name  ),  CString(  pObjDb->cfg.sysName  ),  des  );
}


 // 记录管理员操作事件
 int  qnmLogOpEvent(  int  iServiceId,  void  *  pDbParam,  int  iDbType,  int  iEventType,  LPCTSTR  usr,  LPCTSTR  des  )
{
	return  qnmLogOpEvent(  iServiceId,  pDbParam,  iDbType,  iEventType,  usr,  0,  des  );
}

 int  qyEnumModulesProc(  void  *  modulesParam,  LPCWSTR  funcName,  void  *  p1,  void  *  p2  )
{
	 QY_MODULES			*	pModules	=  (  QY_MODULES  *  )modulesParam;
	 PF_qyModuleProc		pf			=	NULL;
	 QY_DMITEM			*	pItem		=	NULL;
	 
	 for  (  unsigned  int  i  =  0;  i  <  pModules->uiCnt;  i  ++  )  {
		  pf  =  (  PF_qyModuleProc  )qyGetModuleProcByName(  &pModules->mems[i],  funcName  );
		  if  (  pf  )  (  *pf  )(  p1,  p2  );		  
	 }	 

	 return  0;
}


  int  auditNewMessenger(  void  *  pReserved,  QY_MESSENGER_ID  *  pLastIdInfo,  void  *  pLicenseCtx,  void  *  pDb,  int  iDbType,  POLICY_imAuthCond  *  pAuthCond,  QY_MESSENGERAUTHTMP_RCD  *  pNewMessenger  )
{
#if  !defined(  __isCli__  )  &&  !defined(  __APP_qyMc_touchscreen__  )
	 int				iErr										=  -1;
	 //  QMD_VAR_MIS	*	pVar										=	(  QMD_VAR_MIS  *  )pVarParam;
	 CString			sqlStr;
	 char				timeBuf[CONST_qyTimeLen  +  1];
	 char				nMacsBuf[32];
	 char				ip12Buf[12  +  1];
	 int				iDataType_pcName							=	SQL_WVARCHAR;
	 int				iDataType_osUsrName							=	SQL_WVARCHAR;
	 int				iDataType_domainName						=	SQL_WVARCHAR;
	 int				iDataType_messengerName						=	SQL_WVARCHAR;
	 char				idStr[CONST_qyMessengerIdStrLen  +  1];
	 TCHAR				misServName[32]								=	_T(  ""  );
	 char				imObjTypeBuf[32]							=	"";

	 if  (  pAuthCond  )  {
		 if  (  pAuthCond->ucbUseMac  )  {
			 //  处理一下是否在messenger中有相同的MAC，如果有，就要
			 //		if  (  !pAuthCond->ucbAutoAudited  )  弹出框问一下，是否这个Messenger要被删除。
			 //		esle  {  自动删除有相同MAC的Messenger, 并生成日志  }
		 }
		 if  (  pAuthCond->ucbUsePcName  )  {
			 //  处理一下是否在messenger中有相同的PCNAME。。。
			 //  要记住要根据pAuthCond->ucbUseDomainName区分pcName@domainName或只有pcName
		 }
		 if  (  pAuthCond->ucbUseOsUsrName  )  {
			 //  同上
		 }
	 }

	 //  把
 	 //  if  (  qnmGetnMessengers(  pDb  )  >=  qnmMaxMessengers(  (  QY_LICENSE_CTX  *  )pLicenseCtx  )  +  2  )  {
	 if  (  qnmGetnMessengers(  pDb  )  >=  qnmMaxMessengers1(  (  QY_LICENSE_CTX  *  )pLicenseCtx  )  +  0  )  {
		 iErr  =  CONST_qyRet_needMoreLicense;  goto  errLabel;
	 }

	 if  (  getNextMessengerId(  0,  pDb,  pLastIdInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;

	 getCurTime(  timeBuf  );
	 qyStdToIp12(  pNewMessenger->ip,  ip12Buf  ); 
	 ltoa(  pNewMessenger->uiType,  imObjTypeBuf,  10  );

	 sqlStr  =  CString(  ""  )  +  "insert into "  +  CONST_tabName_qyImObjAuthTab  +  "(misServName,idStr,uiType,mac0,mac1,mac2,nMacs,ip,pcName,osUsrName,domainName,messengerName,iStatus,startTime,tLastModifiedTime)"
									"Values("  +
									getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )  +  ","  +
									"'"  +  idStr  +  "',"  +
									imObjTypeBuf  +  ","  +
									"'"  +  pNewMessenger->macsInfo.macs[0]  +  "',"  +
									"'"  +  pNewMessenger->macsInfo.macs[1]  +  "',"  +
									"'"  +  pNewMessenger->macsInfo.macs[2]  +  "',"  +
									ltoa(  pNewMessenger->macsInfo.nMacs,  nMacsBuf,  10  )  +  ","  +
									"'"  +  ip12Buf  +  "',"  +
									getDbValStr(  iDbType,  iDataType_pcName,  pNewMessenger->pcName  )  +  ","  +
									getDbValStr(  iDbType,  iDataType_osUsrName,  pNewMessenger->osUsrName  )  +  ","  +
									getDbValStr(  iDbType,  iDataType_domainName,  pNewMessenger->domainName  )  +  ","  +
									getDbValStr(  iDbType,  iDataType_messengerName,  pNewMessenger->messengerName  )  +  ","  +
									"0,"  +
									"'"  +  timeBuf  +  "',"  +
									"'"  +  timeBuf  +  "')";
	 if  (  !bQyExecSql(  pDb,  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;

	 iErr  =  0;
errLabel:
	 return  iErr;
#else
	return  -1;
#endif
}


 int  auditNewImGrp(  void  *  pReserved,  QY_MESSENGER_ID  *  pLastIdInfo,  void  *  pLicenseCtx,  void  *  pDb,  int  iDbType,  unsigned  int  uiObjType,  IM_GRP_INFO  *  pGrpInfo  )
{
#if  !defined(  __isCli__  )  &&  !defined(  __APP_qyMc_touchscreen__  )
	 int				iErr										=  -1;
	 //  QMD_VAR_MIS	*	pVar										=	(  QMD_VAR_MIS  *  )pVarParam;
	 TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]			=	_T(  ""  );
	 char				idStr[CONST_qyMessengerIdStrLen  +  1];
	 char				timeBuf[CONST_qyTimeLen  +  1];
	 
	 if  (  !pGrpInfo  )  return  -1;

	 switch  (  uiObjType  )  {
			 case  CONST_objType_imGrp:
				   break;
			 default:
				    traceLogA(  "auditNewImGrp: uiType error"  );
					goto  errLabel;
	 }

	 //  把
 	 if  (  qnmGetnImGrps(  pDb  )  >=  qnmMaxImGrps(  (  QY_LICENSE_CTX  *  )pLicenseCtx  )  )  {
		 iErr  =  CONST_qyRet_needMoreLicense;  goto  errLabel;
	 }

	 if  (  getNextMessengerId(  0,  pDb,  pLastIdInfo,  idStr,  mycountof(  idStr  )  )  )  goto  errLabel;
	 
	 getCurTime(  timeBuf  );
	 
	 //  先在qyImObjAuthTab中登记
	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into %s (misServName,idStr,uiType,iStatus,startTime,tLastModifiedTime)"  )
									_T(  "Values(%s,'%s',%d,%d,'%s','%s')"  ),  
									CONST_tabName_qyImObjAuthTab,
									getDbValStr(  iDbType,  CONST_iDataType_misServName,  pGrpInfo->misServName  ),
									CString(  idStr  ),
									uiObjType,
									CONST_qyStatus_ok,
									CString(  timeBuf  ),
									CString(  timeBuf  )  );
	 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	 if  (  !idStr2Info(  idStr,  &pGrpInfo->idInfo  )  )  goto  errLabel;

	 if  (  recoverImGrp(  pDb,  iDbType,  CONST_fieldIdTable_en,  uiObjType,  pGrpInfo,  0  )  )  goto  errLabel;
	 
	 iErr  =  0;
errLabel:
	 return  iErr;
#else
	return  -1;
#endif
}


  int  postImMsg2Log_isMgr(  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo_send,  LPCTSTR  senderDesc,  time_t  tSendTime,  unsigned  int  uiTranNo,  QY_MESSENGER_ID  *  pIdInfo_recv,  LPCTSTR  receiverDesc,  unsigned  int  uiContentType,  LPCTSTR  content,  LPCTSTR  txtContent,  time_t  tRecvTime,  GENERIC_Q  *  pLogQ  ) 
{
	int						iErr			=	-1;
	MIS_MSG_imMsgRcd		msgImMsgRcd;

	if  (  !misServName  )  return  -1;
	if  (  isQFull(  pLogQ  )  )  return  -1;	//  队列如满，就不用再记录了（没法）
	
	memset(  &msgImMsgRcd,  0,  sizeof(  msgImMsgRcd  )  );
	msgImMsgRcd.uiType  =  CONST_misMsgType_imMsgRcd;
	lstrcpyn(  msgImMsgRcd.rcd.misServName,  misServName,  mycountof(  msgImMsgRcd.rcd.misServName  )  );
	msgImMsgRcd.rcd.idInfo_send.ui64Id  =  pIdInfo_send->ui64Id;
	if  (  senderDesc  )  lstrcpyn(  msgImMsgRcd.rcd.senderDesc,  senderDesc,  mycountof(  msgImMsgRcd.rcd.senderDesc  )  );
	msgImMsgRcd.rcd.tSendTime  =  tSendTime;
	msgImMsgRcd.rcd.uiTranNo  =  uiTranNo;
	//  uiSeqNo
	msgImMsgRcd.rcd.idInfo_recv.ui64Id  =  pIdInfo_recv->ui64Id;
	if  (  receiverDesc  )  lstrcpyn(  msgImMsgRcd.rcd.receiverDesc,  receiverDesc,  mycountof(  msgImMsgRcd.rcd.receiverDesc  )  );
	//
	msgImMsgRcd.rcd.uiType  =  uiContentType;
	if  (  content  )  lstrcpyn(  msgImMsgRcd.rcd.content,  content,  mycountof(  msgImMsgRcd.rcd.content  )  );
	if  (  txtContent  )  lstrcpyn(  msgImMsgRcd.rcd.txtContent,  txtContent,  mycountof(  msgImMsgRcd.rcd.txtContent  )  );
	msgImMsgRcd.rcd.tRecvTime  =  tRecvTime;
	mytime(  &msgImMsgRcd.rcd.firstTime  );
	mytime(  &msgImMsgRcd.rcd.lastTime  );
	mytime(  &msgImMsgRcd.rcd.tLastModifiedTime  );
	//
	if  (  qPostMsgAndTrigger(  &msgImMsgRcd,  sizeof(  msgImMsgRcd  ),  pLogQ  )  )  goto  errLabel;

	iErr  =  0;

errLabel:

	return  iErr;
			
}
