
#ifndef  __SECCHKFACTORYCOMMON_H__
#define  __SECCHKFACTORYCOMMON_H__	/*  {  */

#include	"qyCommon.h"
#include	"qyCommCommon.h"
#include	"qyWmComm.h"

#include	"qyPreCustom.h"
#include	"qyCustom.h"

#include	"qyCommProc.h"
#include	"qnmCommProc.h"


typedef  struct  __secChkFactory_t		{


				 QY_ENC_CTX				encCtx,  updateEncCtx,  quitEncCtx,  commEncCtx;	//  2004/01/03Ìí¼ÓcommEncCtx

				 struct					{
					 unsigned  long		ulbEncInited:1;
				 }						status;


}		 SECCHK_FACTORY;


extern SECCHK_FACTORY	gSecChkFactory;


#endif  /*  }  */


