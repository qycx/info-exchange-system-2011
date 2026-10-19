
#ifndef  __SHOWPCPROCESS_H__
#define  __SHOWPCPROCESS_H__	//  {


typedef  struct  __mythreadinfo_t				{
				 DWORD							dwThreadID;
				 struct  __mythreadinfo_t  *	next;
}		 myTHREADINFO;

typedef  struct  __myprocinfo_t					{
				 DWORD							dwProcID;
				 myTHREADINFO				*	pThread;
				 TCHAR							svApp[MAX_PATH+1];
				 TCHAR							cmdLine[256];		//  2006/09/06
				 struct __myprocinfo_t		*	next;
}		 myPROCESSINFO;




int  getProcessNameById(  QY_ENV  *  pEnv,  DWORD  processID,  WCHAR  *  wzProcessName,  unsigned  int  processNameCnt,  WCHAR  *  wzCmdLine,  unsigned  int  cmdLineCnt  );


myPROCESSINFO  *  CreateProcListSnapshot(  QY_ENV  *  pEnv,  char  *  svName  );
void  DestroyProcListSnapshot(  QY_ENV  *  pEnv,  myPROCESSINFO  *  pSS  );

int  printProcessInfo(  myPROCESSINFO  *  ppi  );

#endif  //  }


