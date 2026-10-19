
#include	"stdafx.h"
#include	"shlobj.h"
#ifndef  __WINCE__
		 #include	"myresource.h"
#endif
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"



 unsigned  short  qyGetAppAvLevel_qyMc(  )
{
#ifdef  __isCli__

	if  (  isIsCli(  )  )  {
		QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
		unsigned  short  usAppAvLevel  =  pQyMc->usAppAvLevel_default;	//  qyGetAppAvLevel_default(  );
		unsigned  short  usAppAvLevel_daemon  =  pQyMc->usAppAvLevel_daemon;
		if  (  usAppAvLevel_daemon  )  usAppAvLevel  =  min(  usAppAvLevel,  usAppAvLevel_daemon  );
		return  usAppAvLevel;
	}

	//  err
	return  0;

#else
	 return  qyGetAppAvLevel_default(  );
#endif

 }

 //  2012/06/17
 BOOL  bSupported_mediaSdk(  )
{
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );

	CUS_MODULE_U	*	pModule	=	NULL;

#ifdef  __DEBUG__
		//  return  TRUE;
#endif

	pModule  =  pQyMc->cusModules.pMediaSdk;
	if  (  pModule
		&&  pModule->common.hModule  
		&&  !pModule->compress.mgr.ucbNotSupported  )  return  TRUE;

	return  FALSE;

}

  QY_SERVICEGUI_INFO  *  getServiceGuiInfo(  QY_MC  *  pQyMc,  int  iServiceId  )
{
	 QY_SERVICEGUI_INFO	*	p		=	NULL;
	 int						index	=	0;

	 for  (  index  =  0;  index  <  mycountof(  pQyMc->serviceGuiInfos  );  index  ++  )  {
		  p  =  &pQyMc->serviceGuiInfos[index];
		  if  (  p->cfg.iServiceId  ==  iServiceId  )  return  p;
	 }
	 return  NULL;
}

 BOOL  isWinCe(  )
{
	BOOL	bRet	=	FALSE;

	switch  (  g_pQyMc->env.iPlatformId  )  {
			case  CONST_qyPlatform_winCe:
				  bRet  =  TRUE;
				  break;
			default:
					break;
	}
	return  bRet;
}

 BOOL  bSupported_vwRuleType_messenger(  )
{
	if  (  qyGetAppAvLevel_qyMc(  )  ==  CONST_qyAppAvLevel_basic  )  {
		return  FALSE;
	}

	return  TRUE;	
}
