

#include	"stdafx.h"
#include	<stdio.h>
#include	"qyMcMainCommon.h"
#include	"qyVDev.h"


#define		CONST_mutexName_syncGuiTalk_netMc		_T(  "syncNetMcGuiTalk"  )

 unsigned  int  getVarSize_netMc(  void  *  pQyMc  )
{
	 return  sizeof(  MC_VAR_netMc  );
}



 int  initVar_netMcGui(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int						iErr				=	-1;
	 QY_MC					*	pQyMc				=	(  QY_MC  *  )p0;
	 QY_SERVICEGUI_INFO		*	pSci				=	(  QY_SERVICEGUI_INFO  *  )p1;
	 //	 
	 if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_netMc  )  return  0;
	 //
	 MC_VAR_netMc			*	pProcInfo			=	(  MC_VAR_netMc  *  )pSci->pVar;
	 if  (  !pProcInfo  )  return  -1;

     _sntprintf(  pProcInfo->cfg.mutexName_syncGuiTalk,  mycountof(  pProcInfo->cfg.mutexName_syncGuiTalk  ),  _T(  "%s"  ),  CONST_mutexName_syncGuiTalk_netMc  );


	 return  0;
}

 int  exitVar_netMcGui(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int						iErr				=	-1;
	 QY_MC					*	pQyMc				=	(  QY_MC  *  )p0;
	 QY_SERVICEGUI_INFO		*	pSci				=	(  QY_SERVICEGUI_INFO  *  )p1;
	 //	 
	 if  (  pQyMc->iServiceId  !=  CONST_qyServiceId_netMc  )  return  0;
	 //
	 MC_VAR_netMc			*	pProcInfo			=	(  MC_VAR_netMc  *  )pSci->pVar;
	 if  (  !pProcInfo  )  return  -1;



	 return  0;
}


