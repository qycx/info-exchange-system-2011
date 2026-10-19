

#ifndef  __QMCFG_H__
#define  __QMCFG_H__	/*  {  */

#define		DEFAULT_QY_MC_DSNNAME							CONST_qyDsn_netMc

#define		DEFAULT_QY_MC_CHILD_FRM_TIMER_ID				1
#define		CONST_qyPsTimerId								2

#ifdef  __DEBUG__		//  2007/04/15
	#define		CONST_qmdMaxProcThreads						20
	#define		DEFAULT_usCnt_mgrThreads					10							//  2008/05/15, mtMgrThreadProc_mis
#else
	#define		CONST_qmdMaxProcThreads						20
	#define		DEFAULT_usCnt_mgrThreads					10							//  2008/05/15, mtMgrThreadProc_mis
#endif

#define		CONST_qmdMaxTalksASession						128							//  


//  #define		CONST_nRcdsPerBatch_forBar						99999
//  #define		CONST_nRcdsPerBatch								150
#define		CONST_QY_nQueryStopInterval						5000						//  
#define		CONST_QMD_nSenderInterval						10000						//  10
#define		CONST_QMD_nProcessingInterval					1000						//  1
#ifndef	 __DEBUG__
	#define		CONST_QMD_nSenderRequestInterval			(  10  *  60  *  1000  )	//  10				
	#define		CONST_QMD_nProcessQmObjQIntervalLoops		(  5  *  60  )				//  5, 2006/12/09
	#define		CONST_QMD_nRefreshQmObjQStatusInDbLoops		(  7  *  60  )				//  7
#else
	#define		CONST_QMD_nSenderRequestInterval			(  3  *  1  *  1000  )		//  10
	#define		CONST_QMD_nProcessQmObjQIntervalLoops		(  1  *  10  )				//  , 2006/12/09
	#define		CONST_QMD_nRefreshQmObjQStatusInDbLoops		(  1  *  60  )				//  1
#endif
#define			CONST_QMD_nGetDaemonStatusLoops				(  1  *  3  )				//  2010/01/10


#define		CONST_usIntervalAheadInS_refreshTime_forDb		1  *  60					//  1∑÷÷”£¨2007/08/05
																						//  
#define		CONST_usIntervalAheadInS_refreshTime_forMem		5							//  1 2007/08/05




#define		CONST_qmdMaxThreads								200							//  2007/04/20
			


#define		CONST_qnmMaxStatCols							CONST_qyMaxQueryCols

#define		DEFAULT_qrtTitle								_T(  "Computer registration"  )	//  2005/07/27
//  
#define		DEFAULT_qrtHint									_T(  "Fill in the following blanks before 2009-9-30"  )	//  	//  2005/05/02



#define		CONST_maxCnt_sema_mgrQ_is						10020					//  
#define		CONST_uiMaxQNodes_mgrQ_is						10000					//  
#define		CONST_mutexName_syncMisQ						_T(  "misQ_sync"  )
//

#define		DEFAULT_uiBufSize_misMsgGrpData					4  *  1024  *  1024		//  2008/05/27


#define		CONST_maxCnt_sema_webAuthQ_is					1000					//  2007/11/22
#define		CONST_mutexName_syncWebAuthQ					_T(  "webAuthQ_sync"  )	//  2007/11/22
//
#define		CONST_mutexname_syncGetNextMessengerId			_T(  "getNextMsgId"  )

#define		CONST_uiMaxQNodes_messengerProcessQ				1000
//
#define		CONST_uiMaxQNodes_messengerBtQ					300						//  2011/04/18
//
#define		CONST_uiMaxQNodes_messengerOutputQ				200						//  2007/05/29, messenger.outputQ
#define		CONST_uiMaxQNodes_messengerOutputQ_warning		150						//  messenger.outputQ
//
//
#define		CONST_uiMaxQNodes_messengerTalkingFriendQ		30						//  2007/09/01, messenger
//
#define		CONST_uiMaxQNodes_imGrpMems						1000					//  2007/09/01, imGrp
																					//  imGrptalkingFriendQ. 

//
#define		CONST_usMaxMsgrRecentFriends					230						//  2007/06/04, 2007/09/09



#endif  /*  }  */



