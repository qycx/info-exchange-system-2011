

#ifndef  __SNDEVENTLOG_H__
#define  __SNMEVENTLOG_H__	//  {



typedef  struct  __qwmEventLogProcInfo_t	{
				 TCHAR						sourceTypeName[32  +  1];
				 QY_PC_COMMU				pcCommU;
				 unsigned  char				ucbErr;
}		 QWM_EVENTLOG_PROCINFO;

typedef  struct  __qwmUsrProcInfo_t			{
				 QY_PC_COMMU				pcCommU;
				 unsigned  char				ucbErr;
}		 QWM_USR_PROCINFO;


#endif  //  }


