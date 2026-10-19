

#ifndef  __QYMTSOCK_H__
#define  __QYMTSOCK_H__	/*  {  */

#include	"qyCommon.h"

#ifdef  __cplusplus
  extern  "C"  {
#endif


#ifndef  __DEBUG__
	#define		MAX_CONNS							2560		//  2007/04/12, 将原来的256个改成2560个
#else
	#define		MAX_CONNS							2560
#endif


typedef  int  (  *PF_INITSERVWORK  )(  void  *  pSubThreadInfo,  void  *  reserved2  );
typedef  int  (  *PF_EXITSERVWORK  )(  void  *  pSubThreadInfo,  void  *  reserved2  );
//  typedef  int  (  *PF_DOSERVWORK  )(  int  sockFd,  void  *  aMRI  );



#define		CONST_mtSockType_null					0						//  2007/04/14
#define		CONST_mtSockType_general				1
#define		CONST_mtSockType_iocp					2


typedef  struct  __mtServWork_t						{
				 int								iType;					//  2007/04/14
				 int								iServiceId;				//  2007/03/12
				 PF_INITSERVWORK					pfInitServWork;
				 PF_commonHandler					pfDoServWork;
				 PF_EXITSERVWORK					pfExitServWork;
				 TCHAR								mutexName[32];
				 SOCK_TIMEOUT						sT;
				 unsigned  short					usMaxConns;				//  允许最大的并发连接数
				 unsigned  short					usMaxProcThreads;		//  启动的最大的处理线程数。因为在completionPort中，启动的线程数和cliSocket不是一样多的
				 unsigned  short					usMaxTalks;
				 //
				 unsigned  short					usSessionSize;			//  2007/04/20, 将此参数传入可以让perSocketContext分配内存以方便存放数据
				 unsigned  int						uiBufSize_msgInput;		//  一个大数据包的最大大小。2008/05/25

}		 MT_SERVWORK;

//  2007/07/04/14. 以后，mtSock有多种实现方式。用servWork的类型来区分。此servWork应放在第一位
#define		MACRO_mtSock_common						MT_SERVWORK			servWork;						\
													BOOL				bQuit;							\
													int					iWaitTimeout;					\
													char				servIp[MAX_IP_ADDR_LEN + 1];	\
													unsigned  short		port;							\
													void			*	pParentParam;					\
													HANDLE				hServThread;					\
													int					servSockFd;						\
													BOOL				bListenFailed;					\
													BOOL				bErr;							



typedef  struct  __mtSockCommont_					{						//  2007/08/14
				 MACRO_mtSock_common
}		 MT_SOCK_COMMON;


typedef  struct  __mt_sock_t						{

				 MACRO_mtSock_common

				 int								cliSockFds[MAX_CONNS];							 
				 BOOL								bUseds[MAX_CONNS];

				 HANDLE								hCliThreads[MAX_CONNS];
				 DWORD								dwThreadIds[MAX_CONNS];	//  2007/03/29

				 HANDLE								hEvents[MAX_CONNS];		//  多线程：事件的同步机制
				 
}		MT_SOCK;


typedef  struct  __mtSubThreadInfo_t				{
				 int								iServiceId;			//  2007/03/12
				 HANDLE								hMutex;
				 void					*			pDb;
				 unsigned  long						cnt;
				 SOCK_TIMEOUT			*			pTo;
				 void					*			pParentParam;		//  指向全局或生成此线程的父对象
				 void					*			pCfg;				//  指向线程的配置数据区
				 void					*			pThreadBuf;			//  指向线程的存储数据区
				 void					*			pTaskBuf;			//  指向一次任务的存储数据区
				 //  void					*			pLogHelp;
				 void					*			pLogCtx;
}		 MT_SUBTHREADINFO;

#define		MT_SOCK_SUBTHREADINFO	MT_SUBTHREADINFO

typedef  struct  __mtSockState_t					{
				 BOOL								bListenFailed;			//  2007/03/16
				 BOOL								bErr;					//  是否有错误
				 unsigned  int						nTotalCliThreads;		//  2007/04/15, 暂时不用
				 //  unsigned  int						nBusyCliThreads;
				 unsigned  int						nTotalConns;			//  
				 unsigned  int						nBusyConns;
}		 MT_SOCK_STATE;




//  int initQyMtSock( char *servIp, unsigned short port, MT_SERVWORK *pServWork, void * p );
int initQyMtSock( char *servIp, unsigned short port, MT_SERVWORK * pServWork, void * pParentParam,  void  **  ppMtSock  );
void exitQyMtSock(  void  *  pMtSockParam  );
int setSockTimeout( SOCK_TIMEOUT *p );
int  getQyMtSockState(  void  *  pMtSockparam,  MT_SOCK_STATE  *  pState  );
BOOL  bQyMtSockQuit(  void  *  pMtSockParam  );
//  MT_SERVWORK  *  getQyMtSockServWork(  );



#ifdef __cplusplus
  }
#endif



#endif	/*  }  */

