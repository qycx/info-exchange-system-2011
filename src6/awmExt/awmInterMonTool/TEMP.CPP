
#include	"stdafx.h"
#include	<time.h>
#include	"qyCommon.h"
#include	"qyDbCommon.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"awmExt.h"
#include	"awmInterMonToolCommon.h"

 int getOnlineComputerInfo( AWM_INTER_MON_TOOL *pAIMT, ONLINE_COMPUTER_TAB_RCD *pOCTR )
{
	int			iErr				=	-1;
	CRecordset	rs(  pAIMT->pDb  );
	CDBVariant	varValue;
	CString		sqlStr;
	//  char		officeNameBuf[sizeof(  pOCTR->officeName  )];

	
	TRY  {
		 sqlStr  =  CString(  "select firstRecvdTime, lastRecvdTime from onlineComputerTab " )
								   + " where ip = " + "'" + pOCTR->ip + "'";						
		 
		 traceLogA(  "getOnlineComputerInfo: sqlStr is [%s]",  sqlStr.GetBuffer(  0  )  );
		 if  (  !rs.Open( CRecordset::forwardOnly,  sqlStr.GetBuffer(  0  )  )  )  goto  errLabel;	
		 if  (  rs.IsEOF(  )  )  goto  errLabel;
		 rs.GetFieldValue(  (  short  )0, varValue );
		 _snprintf(  pOCTR->firstRecvdTime,  sizeof(  pOCTR->firstRecvdTime  ),  "%s",  varValue.m_pstring->GetBuffer(  0  )  );
		 rs.GetFieldValue(  (  short  )1, varValue );
		 _snprintf(  pOCTR->lastRecvdTime,  sizeof(  pOCTR->lastRecvdTime  ),  "%s",  varValue.m_pstring->GetBuffer(  0  )  );
		 
		}
	CATCH  (  CDBException,  e  )  {
		    goto  errLabel;
		}
	END_CATCH

	iErr  =  0;

errLabel:

	if  (  rs.IsOpen(  )  )  rs.Close(  );

	return  iErr;
	
}

 int awmInterMonToolRun( AWM_INTER_MON_TOOL *pAIMT )
{
	AWM_INTER_MON_LOG_PROC_INFO		aIMLPI;
	CString							sqlCStr;
	char							buf[128];
	BOOL							bOriginalLogExists	=	FALSE;
	long							loopCtrl			=	0;
	ORIGINAL_LOG_TAB_RCD			oLTR;
	ONLINE_COMPUTER_TAB_RCD			oCTR;
	//  char							officeNameBuf[sizeof(  oCTR.officeName  )];
	char						*	p;
	unsigned  int					fieldSize;
				
	memset(  &aIMLPI,  0,  sizeof(  aIMLPI  )  );

	//  从awmInterMonLogProcInfoTab中取出awmInterMonLogProcInfoTab
	if  (  getAwmInterMonLogProcInfo( pAIMT, ( char * )aIMLPI.procedTime, ( long * )&aIMLPI.procedIndex ) ) {
		debugLog( "getAwmInterMonLogProcInfo( ) failed." );
		goto  errLabel;
	}
	
	
	for  (  ;  ;  loopCtrl  ++  )  {
		
		 if  (  !asrGetRegCfg( ROOT_AWM_INTER_MON_TOOL_KEY, ASR_QUIT_KEY, buf, sizeof( buf ) ) ) {
			 debugLog( "awmInterMonToolRun( ) get quit key value is [%s]", buf );
			 if ( atol( buf ) == ASR_QUIT_VAL ) break;
		 }

		 if  (  !asrGetRegCfg( ROOT_AWM_KEY, ASR_RAS_STOP_MONITOR_KEY, buf, sizeof( buf ) ) ) {
			 debugLog( "awmInterMonRun( ) get stop key value is [%s]", buf );
			 if ( atol( buf ) == ASR_STOP_VAL ) break;
		 }
		
		 debugLog( "loopCtrl is %d", loopCtrl );

		 if  (  !( loopCtrl % 100 ) ) {
			 debugLog( "awmInterMonToolRun( ): before removeOfflineLogFromOnlineTab( )" );
			 removeOfflineLogFromOnlineTab( pAIMT, &aIMLPI );
			 htJudgeDb( pAIMT, &aIMLPI );	// added by asr, 0122.3,  包含清库中冗余信息的功能			
		 }
				
		 // 检索未处理的log,
		 memset(  &oLTR,  0,  sizeof(  oLTR  )  );
		
		 _snprintf(  buf,  sizeof(  buf  ),  "%d",  aIMLPI.procedIndex  );
		 sqlCStr  =  CString( "select index0, recvdTime, computerInfo " )
					 + " from originalLogTab where index0 > " + buf;
		 debugLog( "awmInterMonToolRun( ): [%s]", sqlCStr );
		 TRY  {

			  CRecordset						rs( pAIMT->pDb );

			  if  (  !rs.Open(  CRecordset::forwardOnly,  sqlCStr  )  )  continue;
			  
			  if  (  rs.IsEOF(  )  )  {
				  rs.Close(  );		//  没有记录
				  Sleep(  3000  );  continue;
			  }
			
			  for  (  ;  !rs.IsEOF(  );  rs.MoveNext(  )  )  {

				   CDBVariant  varValue;

				   memset(  &oLTR,  0,  sizeof(  oLTR  )  );
				   rs.GetFieldValue( ( short )0, varValue );
				   if  (  varValue.m_dwType  ==  DBVT_LONG  )  oLTR.index = varValue.m_lVal;
				   rs.GetFieldValue( ( short )1, varValue );
				   if  (  varValue.m_dwType  ==  DBVT_STRING  )  _snprintf(  oLTR.recvdTime,  sizeof(  oLTR.recvdTime  ),  "%s",  varValue.m_pstring->GetBuffer(  0  )  );
				   rs.GetFieldValue( ( short )2, varValue );
				   if  (  varValue.m_dwType  ==  DBVT_STRING  )  _snprintf(  oLTR.computerInfoBuf,  sizeof(  oLTR.computerInfoBuf  ),  "%s",  varValue.m_pstring->GetBuffer(  0  )  );

				   //  #define		CONST_aeComputerInfoBufLen		(  MAX_AWM_MON_OFFICE_NAME_LEN  +  MAX_AWM_MON_SUB_OFFICE_NAME_LEN  +  MAX_IP_ADDR_LEN  +  CONST_qyMacLen  +  CONST_maxAwmMonCompNameLen  +  CONST_maxAwmMonUsrNameLen	 +  CONST_maxAwmMonIsServerLen  )
			
				   memset(  &oCTR,  0,  sizeof(  oCTR  )  );
				   p  =  oLTR.computerInfoBuf;  fieldSize  =  MAX_AWM_MON_OFFICE_NAME_LEN;
				   _snprintf(  oCTR.officeName,  min(  fieldSize,  sizeof(  oCTR.officeName  )  ),  "%s",  p  );  trim(  oCTR.officeName  );
				   p  +=  fieldSize;  fieldSize  =  MAX_AWM_MON_SUB_OFFICE_NAME_LEN;
				   _snprintf(  oCTR.subOfficeName,  min(  fieldSize,  sizeof(  oCTR.subOfficeName  )  ),  "%s",  p  );  trim(  oCTR.subOfficeName  );
				   p  +=  fieldSize;  fieldSize  =  MAX_IP_ADDR_LEN;
				   _snprintf(  oCTR.ip,  min(  fieldSize,  sizeof(  oCTR.ip  )  ),  "%s",  p  );  trim(  oCTR.ip  );
				   p  +=  fieldSize;  fieldSize  =  CONST_qyMacLen;
				   _snprintf(  oCTR.mac,  min(  fieldSize,  sizeof(  oCTR.mac  )  ),  "%s",  p  );  trim(  oCTR.mac  );
				   p  +=  fieldSize;  fieldSize  =  CONST_maxAwmMonCompNameLen;
				   _snprintf(  oCTR.compName,  min( fieldSize,  sizeof(  oCTR.compName  )  ),  "%s",  p  );  trim(  oCTR.compName  );
				   p  +=  fieldSize;  fieldSize  =  CONST_maxAwmMonUsrNameLen;
				   _snprintf(  oCTR.usrName,  min(  fieldSize,  sizeof(  oCTR.usrName  )  ),  "%s",  p  );  trim(  oCTR.usrName  );
				   p  +=  fieldSize;  fieldSize  =  CONST_maxAwmMonUsrNameLen;
				   oCTR.is_server  =  (  unsigned  char  )atol(  p  );
				   p  +=  fieldSize;
			
				   /*
				   memcpy(  officeNameBuf,  oCTR.officeName,  sizeof(  officeNameBuf  )  );
				   trim(  officeNameBuf  );
				   if  (  !officeNameBuf[0]  )  {
					   memset(  oCTR.subOfficeName,  ' ',  sizeof(  oCTR.subOfficeName  )  );
					   oCTR.subOfficeName[sizeof(  oCTR.subOfficeName  )  -  1]  =  0;
					   oCTR.ucbIpOnly  =  TRUE;
				   }
				   */

				   if  (  !oCTR.officeName[0]  )  oCTR.ucbIpOnly  =  TRUE;

				   // 将取出的scannedIp在 onlineComputerTab中检索，
				   //		若有，则判断scannedIp的recvdTime的间隔，
				   //			若 < 5, 则update onlineComputerTab的lastRecvdTime
				   //			否则，将onlineComputerTab的记录放入offlineComputerTab中，
				   //					并且，生成新的记录放入onlineComputerTab
				   //		否则, 生成新的记录放入onlineComputerTab
		
				   if  (  getOnlineComputerInfo(  pAIMT,  &oCTR  )  )  {
					   setQnmWarnInfo(  NULL  );
					   qyShowInfo(  CONST_qyShowType_qnmChking,  "",  pAIMT->cfg.showWho,  "",  "",  "发现来自%s %s %s的外联",  oCTR.officeName,  oCTR.subOfficeName,  oCTR.ip  );
					   sqlCStr  =  CString(  "insert into onlineComputerTab "  )
										+  "(officename,subofficename,ip,mac,compName,usrName,is_server,firstrecvdtime,lastrecvdtime) "
										+  " values("
										+  "'"  +  oCTR.officeName  +  "'"
										+  ",'"  +  oCTR.subOfficeName  +  "'"
										+  ",'"  +  oCTR.ip  +  "'"
										+  ",'"  +  oCTR.mac  +  "'"
										+  ",'"  +  oCTR.compName  +  "'"
										+  ",'"  +  oCTR.usrName  +  "'"
										+  ",'"  +  (  oCTR.is_server  ?  "1"  :  ""  )  +  "'"
										+  ",'"  +  oLTR.recvdTime + "'"
										+  ",'"  +  oLTR.recvdTime + "')";
					   if  (  !bQyExecSql(  pAIMT->pDb,  sqlCStr.GetBuffer(  0  )  )  )  traceLogA(  "execSql failed, sql is %s",  sqlCStr.GetBuffer(  0  )  );				
					   continue;

				   }
			
				   if  (  bIf2TimeNear(  oCTR.lastRecvdTime,  oLTR.recvdTime,  pAIMT->cfg.interval  )  )  {
						
					   sqlCStr  =  CString(  "update onlineComputerTab"  )  
								   +  " set lastRecvdTime='"  +  oLTR.recvdTime  +  "'";
					   if  (  oCTR.officeName[0]  )  sqlCStr  =  sqlCStr   +  ",officeName='"  +  oCTR.officeName  +  "'"
																	+  ",subOfficeName='"  +  oCTR.subOfficeName  +  "'";
					   if  (  oCTR.mac[0]  )  sqlCStr  =  sqlCStr  +  ",mac='"  +  oCTR.mac  +  "'";
					   if  (  oCTR.compName[0]  )  sqlCStr  =  sqlCStr  +  ",compName='"  +  oCTR.compName  +  "'";
					   if  (  oCTR.usrName[0]  )  sqlCStr  =  sqlCStr  +  ",usrName='"  +  oCTR.usrName  +  "'";
					   sqlCStr  =  sqlCStr  +  ",is_server='"  +  (  oCTR.is_server  ?  "1"  :  ""  )  +  "'";
					   sqlCStr  =	sqlCStr  +  " where ip='"  +  oCTR.ip  +  "'";										

					   if  (  !bQyExecSql(  pAIMT->pDb,  sqlCStr.GetBuffer(  0  )  )  )  traceLogA(  "execSql failed, sql is %s",  sqlCStr.GetBuffer(  0  )  );				

					   continue;

				   }
				
				   //  lll
				   debugLog( "awmInterMonToolRun( ): before add and removeRcdFromOnlineComputerTab( )" );
				   OFFLINE_COMPUTER_LOG_TAB_RCD	tmpRcd;

				   memset(  &tmpRcd,  0,  sizeof(  tmpRcd  )  );
				   _snprintf(  tmpRcd.officeName,  sizeof(  tmpRcd.officeName  ),  "%s",  oCTR.officeName  );
				   _snprintf(  tmpRcd.subOfficeName,  sizeof(  tmpRcd.subOfficeName  ),  "%s",  oCTR.subOfficeName  );
				   _snprintf(  tmpRcd.ip,  sizeof(  tmpRcd.ip  ),  "%s",  oCTR.ip  );
				   _snprintf(  tmpRcd.mac,  sizeof(  tmpRcd.mac  ),  "%s",  oCTR.mac  );
				   _snprintf(  tmpRcd.compName,  sizeof(  tmpRcd.compName  ),  "%s",  oCTR.compName  );
				   _snprintf(  tmpRcd.usrName,  sizeof(  tmpRcd.usrName  ),  "%s",  oCTR.usrName  );
				   tmpRcd.is_server  =  oCTR.is_server;
				   _snprintf(  tmpRcd.firstRecvdTime,  sizeof(  tmpRcd.firstRecvdTime  ),  "%s",  oCTR.firstRecvdTime  );
				   _snprintf(  tmpRcd.lastRecvdTime,  sizeof(  tmpRcd.lastRecvdTime  ),  "%s",  oCTR.lastRecvdTime  );
				
				   debugLog( "awmInterMonToolRun( ): add and remove: officeName is [%s], subOfficeName is [%s], ip is [%s], firstRecvdTime is [%s], lastRecvdTime is [%s]",
					   tmpRcd.officeName, tmpRcd.subOfficeName, tmpRcd.ip, tmpRcd.firstRecvdTime, tmpRcd.lastRecvdTime );
				   addRcdIntoOfflineComputerLogTab( pAIMT, &tmpRcd );

				   //  注意：这里已确定为以ip为键值
				   removeRcdFromOnlineComputerTab(  pAIMT,  oCTR.ip  );
				   //  else  removeRcdFromOnlineComputerTab( pAIMT, oCTR.officeName, oCTR.subOfficeName, oCTR.ip  );

				   continue;		

				}

				if  (  rs.IsOpen(  )  )  rs.Close(  );	

				}
		CATCH  (  CDBException, e ) {			
			   debugLog( "awmInterMonToolRun( ): rs.Open( ) failed, [%s]", e->m_strError );
			   
			   // 将已处理过一遍的procedTime和index存入awmInterMonLogProcInfoTab中，以避免再次处理
			   if  (  oLTR.index  >  aIMLPI.procedIndex  )  {
				   aIMLPI.procedIndex  =  oLTR.index; 
				   _snprintf(  aIMLPI.procedTime,  sizeof(  aIMLPI.procedTime  ),  "%s",  oLTR.recvdTime  );
			   }
			   aIMLPI.procedIndex  ++  ;			//  饶过这一出错的记录
			   storeAwmInterMonLogProcInfo( pAIMT, aIMLPI.procedTime, aIMLPI.procedIndex );

			   goto  errLabel;			
			}
		END_CATCH

		
		debugLog( "awmInterMonToolRun( ): before storeAwmInterMonLogProcInfo( )" );
		// 更新aIMLPI.procedTime和index, 并存入awmInterMonLogProcInfoTab中
		//
		aIMLPI.procedIndex = oLTR.index;
		_snprintf(  aIMLPI.procedTime,  sizeof(  aIMLPI.procedTime  ),  "%s",  oLTR.recvdTime  );
		storeAwmInterMonLogProcInfo( pAIMT, aIMLPI.procedTime, aIMLPI.procedIndex );
		
	}

errLabel:

	return 0;

}


