
#include	"stdafx.h"
#include	<time.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<stdio.h>
#include	"qyCommon.h"
#include	"qyDbCommon.h"
#include	"awmExt.h"
#include	"awmInterMonToolCommon.h"

#define		AWM_EXT_MAINTAIN_DB_FLG_KEY		"maintainDbFlg"
#define		ASR_SET_VAL						1
#define		MAX_AWM_ORIGINAL_LOG_INDEX		1500000000

#ifdef  __DEBUG__
  #define   DEFAULT_MAX_DB_SIZE			50		//	2
#else
  #define	DEFAULT_MAX_DB_SIZE			50
#endif




 static  int  DeleteOriLog(  CDatabase  *  pDb,  long  id  )
{
	int		iErr			=	-1;
	char	sqlbuf[256]		=	"";
	
	_snprintf(  sqlbuf,  sizeof(  sqlbuf  ),  "delete from originalLogTab where index0<=%lu",  id  );

	TRY  {
		 pDb->ExecuteSQL( sqlbuf );
		}
	CATCH  (  CDBException,  e  )  {
		   debugLog( "DeleteOriLog( ) caught err is:%s", e->m_strError );
		   goto errLabel;
		}
	END_CATCH

	iErr  =  0;

errLabel:	 

	if  (  iErr  )  {
		traceLogA(  "严重警告：由于出了错，故将所有记录清除"  );
		_snprintf(  sqlbuf,  sizeof(  sqlbuf  ),  "delete from originalLogTab"  );
		bQyExecSql(  pDb,  sqlbuf  );
	}

	return  iErr;

}



// Notice: 清库标志位	software\\asr\\awm\\interMonTool\\maintainDbFlg
//			stopMon		software\\asr\\awm\\stopMon

// 将originalLogTab中的index0 < awmInterMonLogProcInfoTab
//		的procedIndex的记录删除
// 判断库大小，和awmInterMonLogProcInfoTab中的procedIndex
// 太大时，先设清库动作开始标志位( 设为 1 )，并设stopMon为1,
// return
 int htJudgeDb( AWM_INTER_MON_TOOL *pAIMT, AWM_INTER_MON_LOG_PROC_INFO *pAIMLPI )
{
	if  (  pAIMLPI->procedIndex  >  2  *  1023  *  1024  *  1024  ||  pAIMLPI->procedIndex  <  0  )  {		//  这里
		MessageBox(  NULL,  "Access数据库使用时间太久，需复位数据库。请在控制面板中停止服务，将日志导出，用模板库来替代数据库。",  "监视端提示",  MB_OK  );
	}
		 
	DeleteOriLog( pAIMT->pDb, pAIMLPI->procedIndex );
			
	return	0;

}




// 判断有清库标志位时，则先将stopMon设为0, 再将清库标志位清除（设为0）
 int htClearMaintainDbFlg( )
{
	char buf[128] = "0";

	if ( !asrGetRegCfg( ROOT_AWM_INTER_MON_TOOL_KEY, AWM_EXT_MAINTAIN_DB_FLG_KEY, buf, sizeof( buf ) ) ) {
		if ( atol( buf ) == ASR_SET_VAL ) {
			asrSetRegCfg( ROOT_AWM_KEY, ASR_RAS_STOP_MONITOR_KEY, "0" );
			asrSetRegCfg( ROOT_AWM_INTER_MON_TOOL_KEY, AWM_EXT_MAINTAIN_DB_FLG_KEY, "0" );
		}
	}
	return 0;
}

 //  将维持库的功能去除，2004/05/24
 void htMaintainDb( )
{
	CDatabase tmpDb;
	CDatabase *pDb = NULL;
	char buf[128];

	if ( asrGetRegCfg( ROOT_AWM_INTER_MON_TOOL_KEY, AWM_EXT_MAINTAIN_DB_FLG_KEY, buf, sizeof( buf ) ) 
		|| atol( buf ) != ASR_SET_VAL ) 
	{
		return;
	}

//  errLabel:	
	
	asrSetRegCfg( ROOT_AWM_KEY, ASR_RAS_STOP_MONITOR_KEY, "0" );
	asrSetRegCfg( ROOT_AWM_INTER_MON_TOOL_KEY, AWM_EXT_MAINTAIN_DB_FLG_KEY, "0" );	

	return;
}

