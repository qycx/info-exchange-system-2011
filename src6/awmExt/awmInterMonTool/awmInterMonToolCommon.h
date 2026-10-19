
#ifndef __AWMINTERMONTOOLCOMMON_H__
#define __AWMINTERMONTOOLCOMMON_H__	/* { */



typedef  struct  __awmInterMonToolCfg_t		{
				 char						dsnName[256];
				 int						interval;		// 一次性处理log的时间间隔
				 char						showWho[32];
}		 AWM_INTER_MON_TOOL_CFG;

typedef  struct  __awmInterMonTool_t		{
				 AWM_INTER_MON_TOOL_CFG		cfg;
				 CDatabase				*	pDb;
				 void					*	pLckFile;
}		 AWM_INTER_MON_TOOL;

int initAwmInterMonTool( AWM_INTER_MON_TOOL *p );
void exitAwmInterMonTool( AWM_INTER_MON_TOOL *pAIMT );
int awmInterMonToolRun( AWM_INTER_MON_TOOL *pAIMT );
int getTimeByInterval( char *oldTime, int interval, char *newTime );
int getAwmInterMonLogProcInfo( AWM_INTER_MON_TOOL *pAIMT, char *recvdTime, long *pIndex );
void getFirstAndLastTime( AWM_INTER_MON_TOOL *pAIMT, char *pComputerInfo, 
	 AWM_INTER_MON_LOG_PROC_INFO *pAIMLPI, char *newTime, char *pFirstTime, char *pLastTime );
void addRcdIntoOfflineComputerLogTab( AWM_INTER_MON_TOOL *pAIMT, OFFLINE_COMPUTER_LOG_TAB_RCD *pRcd );
void  removeRcdFromOnlineComputerTab(  AWM_INTER_MON_TOOL  *  pAIMT,  char  *  scannedIp  );
void storeAwmInterMonLogProcInfo( AWM_INTER_MON_TOOL *pAIMT, char *recvdTime, long index );
time_t getlTimeByBuf( char *timeBuf );
void removeOfflineLogFromOnlineTab( AWM_INTER_MON_TOOL *pAIMT, AWM_INTER_MON_LOG_PROC_INFO *pAIMLPI );
BOOL bIf2TimeNear( char *time1, char *time2, int interval );

int htJudgeDb( AWM_INTER_MON_TOOL *pAIMT, AWM_INTER_MON_LOG_PROC_INFO *pAIMLPI );
int htClearMaintainDbFlg( );
void htMaintainDb( );
extern "C" int asrSetRegCfg( char *rootKey, char *cfgName, char *cfgVal );


#endif /* } */

