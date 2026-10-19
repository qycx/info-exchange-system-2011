
#include "stdafx.h"
#include <time.h>
#include "awmExt.h"
#include "awmInterMonToolCommon.h"


 int initAwmInterMonTool( AWM_INTER_MON_TOOL *pAIMT )
{
	int			iErr = -1;
	char		buf[1024];
	CString		lckCStr;
	CFile	*	pLckFile = NULL;
	
	setErrHintWndTitle(  CONST_qnmStatusWndTitle  );
	_snprintf(  pAIMT->cfg.showWho,  sizeof(  pAIMT->cfg.showWho  ),  "%s",  CONST_showWho_interMon  );
	
	if  (  asrGetRegCfg( ROOT_AWM_INTER_MON_TOOL_KEY, ASR_INSTALL_PATH_KEY, buf, sizeof( buf ) ) )  return -1;		 
	
	lckCStr = CString( buf ) + CString( "\\temp\\" ) + AWM_INTER_MON_TOOL_LCK_FILE;
	pLckFile = new CFile( );
	if ( !pLckFile ) goto errLabel;
	if ( !pLckFile->Open( lckCStr, CFile::modeCreate | CFile::shareExclusive ) )
		goto errLabel;
	pAIMT->pLckFile = pLckFile; pLckFile = NULL;

	while ( 1 ) {
		char buf[128] = "999";

		if ( !asrGetRegCfg( ROOT_AWM_INTER_MON_TOOL_KEY, ASR_QUIT_KEY, buf, sizeof( buf ) ) ) {
			debugLog( "initAwmInterMonTool( ) get quit key value is [%s]", buf );
			if ( atol( buf ) == ASR_QUIT_VAL ) goto errLabel;
		}
		
		asrShowRegStatus( ROOT_AWM_INTER_MON_TOOL_KEY, "stopMon" );

		if ( !asrGetRegCfg( ROOT_AWM_KEY, ASR_RAS_STOP_MONITOR_KEY, buf, sizeof( buf ) ) ) {
			debugLog( "initAwmInterMonTool( ) get stop key value is [%s]", buf );
			if ( atol( buf ) == ASR_STOP_VAL ) {
				Sleep( 3000 );
				continue;
			}
		}
		
		break;
	}

	asrShowRegStatus( ROOT_AWM_INTER_MON_TOOL_KEY, "tool starts..." );

	strcpy( pAIMT->cfg.dsnName, DEFAULT_AWM_EXT_DSN_NAME );
	pAIMT->cfg.interval = 900;	//  150;  // ywm将判断离线时间延长，2002/12/19
	TRY {
		if ( !pAIMT->pDb->Open( pAIMT->cfg.dsnName ) ) {
			asrShowRegErr( ROOT_AWM_INTER_MON_TOOL_KEY, "db.Open failed." );
			goto errLabel;
		}
		}
	CATCH ( CDBException, e ) {
		asrShowRegErr( ROOT_AWM_INTER_MON_TOOL_KEY, "db.Open failed." );
		goto errLabel;
		}
	END_CATCH

		
	// 校验此间隔，不允许 <= 0
	if ( pAIMT->cfg.interval <= 0 ) goto errLabel;

	iErr = 0;

errLabel:

	if  (  iErr  )  {


		/*
		if ( pLckFile ) {
			pLckFile->Close( );
			delete pLckFile;
		}
		*/
		
		if  (  pAIMT->pLckFile  )  {
			pLckFile = ( CFile * )pAIMT->pLckFile;  
			pLckFile->Close(  );
			pAIMT->pLckFile  =  NULL;
		}
		if  (  pLckFile  )  delete pLckFile;
		
		exitAwmInterMonTool( pAIMT );
	}
	
	return iErr;

}

 void exitAwmInterMonTool( AWM_INTER_MON_TOOL *pAIMT )
{
	CFile *pLckFile = NULL;
	if ( pAIMT->pDb->IsOpen( ) )
		pAIMT->pDb->Close( );
	
	if ( pAIMT->pLckFile ) pLckFile = ( CFile * )pAIMT->pLckFile;
	if ( pLckFile ) {
		pLckFile->Close( );
		delete pLckFile;
	}
	return;
	
}

 void awmInterMonToolMain( )
{
	AWM_INTER_MON_TOOL aIMT;
	CDatabase tmpDb;
	
	setDebugLogFileName( "errTool.log" );
	
	htClearMaintainDbFlg( );

	memset( &aIMT, 0, sizeof( aIMT ) );
	aIMT.pDb = &tmpDb;
	if ( initAwmInterMonTool( &aIMT ) ) return;

	awmInterMonToolRun( &aIMT );

	exitAwmInterMonTool( &aIMT );

	htMaintainDb( );
	debugLog( "awmInterMonToolMain( ) ends." );
	asrShowRegStatus( ROOT_AWM_INTER_MON_TOOL_KEY, "ends." );

	return;

}


// awmInterMonLogProcInfoTab
// offlineComputerTab( )
// onlineComputerTab( )

 // 待完成
 time_t getlTimeByBuf( char *timeBuf )
{
	char buf[5];
	struct tm tm;
	time_t t1 = 0;

	memset( &tm, 0, sizeof( struct tm ) );
	memcpy( buf, timeBuf, 4 );
	buf[4] = 0;
	tm.tm_year += atol( buf ) - 1900;
	memcpy( buf, timeBuf + 4, 2 );
	buf[2] = 0;
	tm.tm_mon += atol( buf ) - 1;
	memcpy( buf, timeBuf + 6, 2 );
	tm.tm_mday += atol( buf );
	memcpy( buf, timeBuf + 8, 2 );
	tm.tm_hour += atol( buf );
	memcpy( buf, timeBuf + 10, 2 );
	tm.tm_min += atol( buf );
	memcpy( buf, timeBuf + 12, 2 );
	tm.tm_sec += atol( buf );

	return mktime( &tm );

}

 int getTimeByInterval( char *oldTime, int interval, char *newTime )
{
	time_t t1;
	struct tm when;

	if ( !oldTime || !newTime ) return -1; 
	t1 = getlTimeByBuf( oldTime );
	if ( t1 == ( time_t )-1 ) t1 = 0;
	t1 += interval;
	if ( t1 < 0 ) t1 = 0;
	when = *localtime( &t1 );
	
	sprintf( newTime,"%04d%02d%02d%02d%02d%02d",when.tm_year+1900,
		 when.tm_mon+1,when.tm_mday,when.tm_hour,when.tm_min,
		 when.tm_sec );
	
	return 0;

}

  BOOL bIf2TimeNear( char *time1, char *time2, int interval )
{
	time_t t1, t2;

	t1 = getlTimeByBuf( time1 );
	t2 = getlTimeByBuf( time2 );
	if ( t1 == ( time_t )-1 || t2 == ( time_t )-1 ) return FALSE;
	if ( abs( t1 - t2 ) > abs( interval ) ) return FALSE;
	return TRUE;
}
						
 


 void removeOfflineLogFromOnlineTab( AWM_INTER_MON_TOOL *pAIMT, AWM_INTER_MON_LOG_PROC_INFO *pAIMLPI )
{
	char							curTime[14 + 1];
	char							newTime[14 + 1];
	CRecordset						rs( pAIMT->pDb );
	CString							sqlCStr;
	OFFLINE_COMPUTER_LOG_TAB_RCD	tmpRcd;
	CDBVariant						varValue;

	getCurTime(  curTime  );
	//  getTimeByInterval( curTime, -1 * 2 * pAIMT->cfg.interval, newTime );
	getTimeByInterval( curTime, -1 * 1 * pAIMT->cfg.interval, newTime );	// 由于interval改为较大值，故这里判断时间不能太长。Modified on 2002/1219
	sqlCStr = CString( "select officeName, subOfficeName, ip, mac,compName,usrName,is_server,firstRecvdTime, lastRecvdTime from onlineComputerTab where lastRecvdTime < " ) + "'" + newTime + "'";
	TRY  {
		 if  (  !rs.Open(  CRecordset::forwardOnly,  sqlCStr  )  )  goto  errLabel;
		 while  (  !rs.IsEOF( ) ) {
			    memset(  &tmpRcd,  0,  sizeof(  tmpRcd  )  );
				rs.GetFieldValue( ( short )0, varValue );
				if  (  varValue.m_dwType  ==  DBVT_STRING  )  _snprintf(  tmpRcd.officeName,  sizeof(  tmpRcd.officeName  ),  "%s",  varValue.m_pstring->GetBuffer(  0  )  );
				rs.GetFieldValue( ( short )1, varValue );
				if  (  varValue.m_dwType  ==  DBVT_STRING  )  _snprintf(  tmpRcd.subOfficeName,  sizeof(  tmpRcd.subOfficeName  ),  "%s",  varValue.m_pstring->GetBuffer( 0 )  );
				rs.GetFieldValue( ( short )2, varValue );
				if  (  varValue.m_dwType  ==  DBVT_STRING  )  _snprintf(  tmpRcd.ip,  sizeof(  tmpRcd.ip  ),  "%s",  varValue.m_pstring->GetBuffer( 0 )  );
				rs.GetFieldValue( ( short )3, varValue );
				if  (  varValue.m_dwType  ==  DBVT_STRING  )  _snprintf(  tmpRcd.mac,  sizeof(  tmpRcd.mac  ),  "%s",  varValue.m_pstring->GetBuffer( 0 )  );
				rs.GetFieldValue( ( short )4, varValue );
				if  (  varValue.m_dwType  ==  DBVT_STRING  )  _snprintf(  tmpRcd.compName,  sizeof(  tmpRcd.compName  ),  "%s",  varValue.m_pstring->GetBuffer(  0  )  );
				rs.GetFieldValue( ( short )5, varValue );
				if  (  varValue.m_dwType  ==  DBVT_STRING  )  _snprintf(  tmpRcd.usrName,  sizeof(  tmpRcd.usrName  ),  "%s",  varValue.m_pstring->GetBuffer(  0  )  );
				rs.GetFieldValue( ( short )6, varValue );
				if  (  varValue.m_dwType  ==  DBVT_STRING  )  tmpRcd.is_server  =  (  unsigned  char  )atol(  varValue.m_pstring->GetBuffer(  0  )  );
				rs.GetFieldValue( ( short )7, varValue );				
				if  (  varValue.m_dwType  ==  DBVT_STRING  )  _snprintf(  tmpRcd.firstRecvdTime,  sizeof(  tmpRcd.firstRecvdTime  ),  "%s",  varValue.m_pstring->GetBuffer( 0 )  );
				rs.GetFieldValue( ( short )8, varValue );
				if  (  varValue.m_dwType  ==  DBVT_STRING  )  _snprintf(  tmpRcd.lastRecvdTime,  sizeof(  tmpRcd.lastRecvdTime  ),  "%s",  varValue.m_pstring->GetBuffer( 0 ) );
					
				debugLog( "removeOfflineLogFromOnlineTab( ): officeName is [%s], subOfficeName is [%s], ip is [%s], firstRecvdTime is [%s], lastRecvdTime is [%s]", tmpRcd.officeName, tmpRcd.subOfficeName, tmpRcd.ip, tmpRcd.firstRecvdTime, tmpRcd.lastRecvdTime );
				addRcdIntoOfflineComputerLogTab( pAIMT, &tmpRcd );
				removeRcdFromOnlineComputerTab( pAIMT, tmpRcd.ip );
			
				rs.MoveNext(  );

		 }

		}
	CATCH ( CDBException, e ) {
		goto errLabel;
	}
	END_CATCH

errLabel:

	if  (  rs.IsOpen(  )  )  rs.Close(  );

	return;

}

// awmInterMonLogProcInfoTab

 int getAwmInterMonLogProcInfo( AWM_INTER_MON_TOOL *pAIMT, char *recvdTime, long *pIndex )
{
	int iErr = -1;
	CRecordset rs( pAIMT->pDb );
	CDBVariant varValue;

	TRY {
		if ( !rs.Open( CRecordset::forwardOnly, "select procedIndex, procedTime from awmInterMonLogProcInfoTab" ) ) 
			goto errLabel;
		rs.GetFieldValue( ( short )0, varValue );
		*pIndex = varValue.m_lVal;
		rs.GetFieldValue( ( short )1, varValue );
		strcpy( recvdTime, varValue.m_pstring->GetBuffer( 0 ) );
		}
	CATCH ( CDBException, e ) {
		goto errLabel;
		}
	END_CATCH

	iErr = 0;

errLabel:
	if ( !rs.IsOpen( ) ) rs.Close( );
	return iErr;

}

 void storeAwmInterMonLogProcInfo( AWM_INTER_MON_TOOL *pAIMT, char *recvdTime, long index )
{
	CString sqlCStr;
	char buf[128];

	sprintf( buf, "%d", index );
	sqlCStr = CString( "update awmInterMonLogProcInfoTab set procedIndex =" )
		+ buf + "," + "procedTime = " + "'" + recvdTime + "'";

	TRY {
		pAIMT->pDb->ExecuteSQL( sqlCStr );
		}
	CATCH ( CDBException, e ) {
		debugLog( "storeAwmInterMonLogProcInfo( ) error: [%s].", e->m_strError );
		}
	END_CATCH

	return;

}


 void addRcdIntoOfflineComputerLogTab( AWM_INTER_MON_TOOL *pAIMT, OFFLINE_COMPUTER_LOG_TAB_RCD *pRcd )
{
	CString sqlCStr;

	sqlCStr	 =  CString( "insert into offlineComputerLogTab( officeName, subOfficeName, ip, mac,compName,usrName,is_server,firstRecvdTime, lastRecvdTime ) " )
				+  " values( " 
				+  "'"  +  pRcd->officeName  +  "'" 
				+  ",'"  +  pRcd->subOfficeName  +  "'"
				+  ",'"  +  pRcd->ip  +  "'"
				+  ",'"  +  pRcd->mac  +  "'"
				+  ",'"  +  pRcd->compName  +  "'"
				+  ",'"  +  pRcd->usrName  +  "'"
				+  ",'"  +  (  pRcd->is_server  ?  "1"  :  ""  )  +  "'"    
				+  ",'"  +  pRcd->firstRecvdTime + "'"
				+  ",'"  +  pRcd->lastRecvdTime + "'"
				+  ")";
	TRY {
		pAIMT->pDb->ExecuteSQL( sqlCStr );
		}
	CATCH ( CDBException, e ) {
		debugLog( "addRcdInfoOfflineComputerLogTab( ) error: [%s]", e->m_strError );
	}
	END_CATCH

	return;
}



 void  removeRcdFromOnlineComputerTab(  AWM_INTER_MON_TOOL  *  pAIMT,  char  *  scannedIp  )
{
	CString  sqlCStr;

	sqlCStr  =  CString(  "delete from onlineComputerTab where "  )
				+  " ip = '" + scannedIp + "'";
	TRY  {
		 pAIMT->pDb->ExecuteSQL(  sqlCStr  );
		}
	CATCH  (  CDBException,  e  )  {
		   debugLog(  "removeIpOnlyRcdFromOnlineComputerTab( ) error: [%s]", e->m_strError );
	}
	END_CATCH

	return;

}


 void getFirstAndLastTime( AWM_INTER_MON_TOOL *pAIMT, char *pComputerInfo, 
	 AWM_INTER_MON_LOG_PROC_INFO *pAIMLPI, char *newTime, char *pFirstTime, char *pLastTime )
{
	CRecordset rs( pAIMT->pDb );
	char buf[128];

	memset( pFirstTime, '0', 14 );
	pFirstTime[14] = 0;
	memset( pLastTime, '0', 14 );
	pLastTime[14] = 0;
	sprintf( buf, "%d", pAIMLPI->procedIndex );

	CString csSql = CString( "select max( recvdTime ), min( recvdTime ) from originalLogTab " )
			+ " where "
			+ " computerInfo=" + "'" + pComputerInfo + "'" 
			+ " and recvdTime < " + "'" + newTime + "'"
			+ " and index0 > " + buf;

	TRY	{
		if ( rs.Open( CRecordset::forwardOnly, csSql ) ) {
			CDBVariant varValue;
			rs.GetFieldValue( ( short )0, varValue );
			strcpy( pLastTime,varValue.m_pstring->GetBuffer( 0 ) );
			
			rs.GetFieldValue( ( short )1, varValue );
			strcpy( pFirstTime,varValue.m_pstring->GetBuffer( 0 ) );
		}
		}
	CATCH ( CDBException, e ) {
		debugLog( "getFirstAndLastTime( ) error: [%s]", e->m_strError );
		}
	END_CATCH
	
	if ( rs.IsOpen( ) ) 
		rs.Close( );

	return;

}

