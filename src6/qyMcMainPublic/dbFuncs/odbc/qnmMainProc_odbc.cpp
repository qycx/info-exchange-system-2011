

#include	"stdafx.h"
#include	<stdio.h>
#include	"qyMcMainCommon.h"
#include	"myResource.h"
//#include	"QyRcdset.h"

#include	"qycusrescommon.h"

#include	"myDb.h"


  __declspec(  dllexport  )  int  delPcSth(  void  *  pDb,  LPCTSTR  hint,  LPCTSTR  tabName,  LPCTSTR  whereClause  )
{
	 int		iErr		=	-1;
	 TCHAR		sqlBuf[CONST_maxSqlBufLen  +  1];
	 //  char	*	hint		=	"ÊÇ·ñÉ¾³ý¸ÃPCµÄÏµÍ³ÈÕÖ¾?";

	 if  (  hint  &&  myMessageBox(  NULL,  hint,  _T(  ""  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  goto  errLabel;
	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s"  ),  CQyString(  tabName  )  );
	 if  (  whereClause  &&  whereClause[0]  )  {
		 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s where %s"  ),  sqlBuf,  whereClause  );
	 }
	 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;
	 iErr  =  0;

errLabel:
	 return  iErr;
}


 __declspec(  dllexport  )  int  delImObj(  void  *  pDb,  int  iDbType,  BOOL  bClient,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo  )
{
	int			iErr									=	-1;
	char		idStr[CONST_qyMessengerIdStrLen  +  1]	=	"";
	CQyString		whereClause;

	if  (  !idInfo2Str(  pIdInfo,  idStr,  mycountof(  idStr  )  )  )  return  -1;

	//  ÏÈÉ¾³ýimGrpMemTab
	whereClause  =  CQyString(  "misServName="  )  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )
		+  CQyString(  " and idStr_mem='"  )  +  CQyString(  idStr  )  +  CQyString(  "'"  );
	if  (  delPcSth(  pDb,  NULL,  _T(  "qyImGrpMemTab"  ),  whereClause  )  )  goto  errLabel;
	whereClause  =  CQyString(  "misServName="  )  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )
		+  CQyString(  " and idStr_grp='"  )  +  CQyString(  idStr  )  +  CQyString(  "'"  );
	if  (  delPcSth(  pDb,  NULL,  _T(  "qyImGrpMemTab"  ),  whereClause  )  )  goto  errLabel;

	//  2009/09/17
	if  (  !bClient  )  {
		whereClause  =  CQyString(  "misServName="  )  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )
			+  CQyString(  " and (idStr='"  )  +  CQyString(  idStr  )  +  CQyString(  "' or idStr_visitor='"  )  +  CQyString(  idStr  )  +  CQyString(  "')"  );
		if  (  delPcSth(  pDb,  NULL,  CONST_tabName_qyDynBmpRuleTab,  whereClause  )  )  goto  errLabel;
	}

	whereClause  =  CQyString(  "misServName="  )  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )
		+  CQyString(  " and (idStr='"  )  +  CQyString(  idStr  )  +  CQyString(  "')"  );
	if  (  delPcSth(  pDb,  NULL,  CONST_tabName_qyDynBmpTab,  whereClause  )  )  goto  errLabel;

	//
	whereClause  =  CQyString(  "misServName="  )  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )
		+  CQyString(  " and idStr='"  )  +  CQyString(  idStr  )  +  CQyString(  "'"  );
	
	if  (  delPcSth(  pDb,  NULL,  _T(  "qyImGrpInfoTab"  ),  whereClause  )  )  goto  errLabel;
	
	if  (  delPcSth(  pDb,  NULL,  _T(  "qyImObjRegInfoTab"  ),  whereClause  )  )  goto  errLabel;
	if  (  delPcSth(  pDb,  NULL,  _T(  "qyImObjRegInfoTab1"  ),  whereClause  )  )  goto  errLabel;
	if  (  delPcSth(  pDb,  NULL,  _T(  "qyImObjTab"  ),  whereClause  )  )  goto  errLabel;
	
	if  (  !bClient  )  {
		if  (  delPcSth(  pDb,  NULL,  CONST_tabName_qyWebContactTab,  whereClause  )  )  goto  errLabel;
	}
	if  (  delPcSth(  pDb,  NULL,  CONST_tabName_qyMessengerPhoneInfoTab,  whereClause  )  )  goto  errLabel;
	
	if  (  !bClient  )  {  //  2010/01/05
		if  (  delPcSth(  pDb,  NULL,  CONST_tabName_qyImAmTab,  whereClause  )  )  goto  errLabel;
	}

	if  (  !bClient  )  {
		whereClause  =  CQyString(  "misServName="  )  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )
			+  CQyString(  " and (idStr='"  )  +  CQyString(  idStr  )  +  CQyString(  "' or idStr_related='"  )  +  CQyString(  idStr  )  +  CQyString(  "')"  );
		//  2010/08/16
		if  (  delPcSth(  pDb,  NULL,  CONST_tabName_qyImObjRuleTab,  whereClause  )  )  goto  errLabel;
	}

	//
	whereClause  =  CQyString(  "misServName="  )  +  getDbValStr(  iDbType,  CONST_iDataType_misServName,  misServName  )
		+  CQyString(  " and idStr='"  )  +  CQyString(  idStr  )  +  CQyString(  "'"  );
	if  (  delPcSth(  pDb,  NULL,  _T(  "qyImObjAuthTab"  ),  whereClause  )  )  goto  errLabel;
	
	iErr  =  0;
errLabel:
	return  iErr;
}


 BOOL  bClearQnmTmpTab_netMc(  QY_MC  *  pQyMc  )
{
#ifdef  __NOTSUPPORT_DB__
	return  TRUE;
#else
	char		sqlBuf[256];
	 _snprintf(  sqlBuf,  sizeof(  sqlBuf  ),  "delete from qnmTmpTab where iType=%d",  pQyMc->cfg.iType_qnmTmpTab  );
	 bQyExecSql(  pQyMc->gui.pDb,  CQyString(  sqlBuf  ).GetBuffer(  0  )  );
	 return  TRUE;
#endif
}


 BOOL  bClearQnmTmpTab_mis(  QY_MC  *  pQyMc  )
{
	 return  TRUE;
}

 __declspec(  dllexport  )  BOOL  bClearQnmTmpTab(  QY_MC  *  pQyMc  )
{
	 BOOL	bRet	=	FALSE;

	 switch  (  qyGetServiceId(  pQyMc->iSystemId  )  )  {
			 case  CONST_qyServiceId_netMc:
				   bRet  =  bClearQnmTmpTab_netMc(  pQyMc  );
				   break;
			 case  CONST_qyServiceId_mis:
				   bRet  =  bClearQnmTmpTab_mis(  pQyMc  );
				   break;
			 default:
					break;
					
	 }


	 return  bRet;
}


 __declspec(  dllexport  )  BOOL  bClearupScannedIp_netMc(  QY_CLEARUPINFO  *  pClearupInfo  )
{
#ifdef  __NOTSUPPORT_DB__
	return  FALSE;
#else

	 QY_MC		*	pQyMc	=	QY_GET_GBUF(  );
	 CQyString		sqlStr;

	 sqlStr  =  CQyString(  "delete from qnmScannedIpTab"  );

	 return  bQyExecSql(  pQyMc->gui.pDb,  sqlStr.GetBuffer(  0  )  );
#endif
}
				  
 BOOL  bClearupEvent_netMc(  QY_CLEARUPINFO  *  pClearupInfo  )
{
#ifdef  __NOTSUPPORT_DB__
	return  FALSE;
#else

	 BOOL			bRet			=		FALSE;
	 QY_MC		*	pQyMc			=		QY_GET_GBUF(  );
	 CQyString		sqlStr;
	 TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1];

	 //  2006/03/08, ÕâÀïË³±ãÇåÀíÒ»ÏÂ²Ù×÷×´Ì¬±íµÄÐÅÏ¢£¬Ê¡µÃÌ«¶àÁË
	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from qyPcOpQTab where iStatus=%d or iStatus=%d"  ),  CONST_cmdStatus_end,  CONST_cmdStatus_err  );
	 bRet  =  bQyExecSql(  pQyMc->gui.pDb,  sqlBuf  );

	 // Ô­À´µÄÊÂ¼þÇåÀí¹¤×÷
	 sqlStr  =  CQyString(  "delete from qyPcEventTab"  )
				+  CQyString(  _T(  " where cntEventTime>'"  )  )  +  CQyString(  pClearupInfo->fromTimeBuf  )  +  CQyString(  _T(  "'"  )  )
				+  CQyString(  _T(  " and cntEventTime<'"  )  )  +  CQyString(  pClearupInfo->toTimeBuf  )  +  CQyString(  _T(  "'"  )  );
	 bRet  =  bQyExecSql(  pQyMc->gui.pDb,  sqlStr.GetBuffer(  0  )  );

	 sqlStr  =  CQyString(  "delete from offlineComputerLogTab"  )
				+  CQyString(  _T(  " where firstRecvdTime  >'"  )  )  +  CQyString(  pClearupInfo->fromTimeBuf  )  +  CQyString(  _T(  "'"  )  )
				+  CQyString(  _T(  " and firstRecvdTime  <'"  )  )  +  CQyString(  pClearupInfo->toTimeBuf  )  +  CQyString(  _T(  "'"  )  );
	 bRet  =  bQyExecSql(  pQyMc->gui.pDb,  sqlStr.GetBuffer(  0  )  );

	 if  (  bRet  )  {
		 char			logDes[128]			=	"";
		 char			startTimeBuf[32]	=	"";
		 char			endTimeBuf[32]		=	"";

		 _snprintf(  logDes,  sizeof(  logDes  ),  "%S : %s ~ %s",  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_deleteLogBetween  ),  qyDisplayTime(  pClearupInfo->fromTimeBuf,  startTimeBuf,  sizeof(  startTimeBuf  )  ),  qyDisplayTime(  pClearupInfo->toTimeBuf,  endTimeBuf,  sizeof(  endTimeBuf  )  )  );
		 qnmLogOpEvent(  pQyMc->iServiceId,  pQyMc->gui.pDb,  pQyMc->cfg.db.iDbType,  CONST_qyEventType_nm_clearupEvent,  CQyString(  pQyMc->curUsrInfo.name  ),  CQyString(  logDes  )  );
	 }

//  errLabel:
	 return  bRet;
#endif
}

 BOOL  bClearupEvent_is_odbc(  QY_CLEARUPINFO  *  pClearupInfo  )
{
#ifdef  __NOTSUPPORT_DB__
	return  FALSE;
#else

	 BOOL			bRet			=		FALSE;
	 QY_MC		*	pQyMc			=		QY_GET_GBUF(  );
	 CQyString		sqlStr;
	 //  TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1];

	 // Ô­À´µÄÊÂ¼þÇåÀí¹¤×÷
	 sqlStr  =  CQyString(  "delete from qyImEventTab"  )
				+  CQyString(  _T(  " where cntEventTime>'"  )  )  +  CQyString(  pClearupInfo->fromTimeBuf  )  +  CQyString(  _T(  "'"  )  )
				+  CQyString(  _T(  " and cntEventTime<'"  )  )  +  CQyString(  pClearupInfo->toTimeBuf  )  +  CQyString(  _T(  "'"  )  );
	 bRet  =  bQyExecSql(  pQyMc->gui.pDb,  sqlStr.GetBuffer(  0  )  );

	 if  (  bRet  )  {
		 char			logDes[128]			=	"";
		 char			startTimeBuf[32]	=	"";
		 char			endTimeBuf[32]		=	"";

		 _snprintf(  logDes,  sizeof(  logDes  ),  "%S : %s ~ %s",  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_deleteLogBetween  ),  qyDisplayTime(  pClearupInfo->fromTimeBuf,  startTimeBuf,  sizeof(  startTimeBuf  )  ),  qyDisplayTime(  pClearupInfo->toTimeBuf,  endTimeBuf,  sizeof(  endTimeBuf  )  )  );
		 qnmLogOpEvent(  pQyMc->iServiceId,  pQyMc->gui.pDb,  pQyMc->cfg.db.iDbType,  CONST_qyEventType_nm_clearupEvent,  CQyString(  pQyMc->curUsrInfo.name  ),  CQyString(  logDes  )  );
	 }

//  errLabel:
	 return  bRet;
#endif
}


 __declspec(  dllexport  )  BOOL  bClearupEvent(  QY_CLEARUPINFO  *  pClearupInfo  )
{
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	
	QM_dbFuncs  *  pDbFuncs  =  QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  return  FALSE;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	if  (  pQyMc->iServiceId  ==  CONST_qyServiceId_netMc  )  return  bClearupEvent_netMc(  pClearupInfo  );
	else  return  g_dbFuncs.pf_bClearupEvent_is(  pClearupInfo  );
}

 BOOL  bClearupImMsg_odbc(  QY_CLEARUPINFO  *  pClearupInfo  )
{
#ifdef  __NOTSUPPORT_DB__
	return  FALSE;
#else

	 BOOL			bRet			=		FALSE;
	 QY_MC		*	pQyMc			=		QY_GET_GBUF(  );
	 CQyString		sqlStr;
	 //  TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1];

	 // Ô­À´µÄÊÂ¼þÇåÀí¹¤×÷
	 sqlStr  =  CQyString(  "delete from qyImMsgTab"  )
				+  CQyString(  _T(  " where tLastModifiedTime>'"  )  )  +  CQyString(  pClearupInfo->fromTimeBuf  )  +  CQyString(  _T(  "'"  )  )
				+  CQyString(  _T(  " and tLastModifiedTime<'"  )  )  +  CQyString(  pClearupInfo->toTimeBuf  )  +  CQyString(  _T(  "'"  )  );
	 bRet  =  bQyExecSql(  pQyMc->gui.pDb,  sqlStr.GetBuffer(  0  )  );

	 if  (  bRet  )  {
		 char			logDes[128]			=	"";
		 char			startTimeBuf[32]	=	"";
		 char			endTimeBuf[32]		=	"";

		 _snprintf(  logDes,  sizeof(  logDes  ),  "%S : %s ~ %s",  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_deleteLogBetween  ),  qyDisplayTime(  pClearupInfo->fromTimeBuf,  startTimeBuf,  sizeof(  startTimeBuf  )  ),  qyDisplayTime(  pClearupInfo->toTimeBuf,  endTimeBuf,  sizeof(  endTimeBuf  )  )  );
		 qnmLogOpEvent(  pQyMc->iServiceId,  pQyMc->gui.pDb,  pQyMc->cfg.db.iDbType,  CONST_qyEventType_nm_clearupImMsg,  CQyString(  pQyMc->curUsrInfo.name  ),  CQyString(  logDes  )  );
	 }

//  errLabel:
	 return  bRet;
#endif
}
				  


 BOOL  bClearupImHisTask_odbc(  QY_CLEARUPINFO  *  pClearupInfo  )
{
#ifdef  __NOTSUPPORT_DB__
	return  FALSE;
#else

	 BOOL			bRet			=		FALSE;
	 QY_MC		*	pQyMc			=		QY_GET_GBUF(  );
	 CQyString		sqlStr;
	 //  TCHAR			sqlBuf[CONST_maxSqlBufLen  +  1];

	 // Ô­À´µÄÊÂ¼þÇåÀí¹¤×÷
	 sqlStr  =  CQyString(  "delete from qyImTaskHisTab"  )
				+  CQyString(  _T(  " where tSendTime>'"  )  )  +  CQyString(  pClearupInfo->fromTimeBuf  )  +  CQyString(  _T(  "'"  )  )
				+  CQyString(  _T(  " and tSendTime<'"  )  )  +  CQyString(  pClearupInfo->toTimeBuf  )  +  CQyString(  _T(  "'"  )  );
	 bRet  =  bQyExecSql(  pQyMc->gui.pDb,  sqlStr.GetBuffer(  0  )  );

	 if  (  bRet  )  {
		 char			logDes[128]			=	"";
		 char			startTimeBuf[32]	=	"";
		 char			endTimeBuf[32]		=	"";

		 _snprintf(  logDes,  sizeof(  logDes  ),  "%S : %s ~ %s",  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_deleteLogBetween  ),  qyDisplayTime(  pClearupInfo->fromTimeBuf,  startTimeBuf,  sizeof(  startTimeBuf  )  ),  qyDisplayTime(  pClearupInfo->toTimeBuf,  endTimeBuf,  sizeof(  endTimeBuf  )  )  );
		 qnmLogOpEvent(  pQyMc->iServiceId,  pQyMc->gui.pDb,  pQyMc->cfg.db.iDbType,  CONST_qyEventType_nm_clearupImHisTask,  CQyString(  pQyMc->curUsrInfo.name  ),  CQyString(  logDes  )  );
	 }

//  errLabel:
	 return  bRet;
#endif
}


//  2013/02/20
BOOL  bClearupImMsg_isCli_odbc(  void  *  pDb,  int  iDbType,  LPCTSTR  wherePart  )
{
	BOOL	bRet	=	FALSE;
	TCHAR	sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "delete from %s"  ),  CONST_tabName_qyImMsgTab  );
	if  (  wherePart  &&  wherePart[0]  )  {
		_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s where %s"  ),  sqlBuf,  wherePart  );
	}
	bQyExecSql(  pDb,  sqlBuf  );

	bRet  =  TRUE;
	return  bRet;
}







