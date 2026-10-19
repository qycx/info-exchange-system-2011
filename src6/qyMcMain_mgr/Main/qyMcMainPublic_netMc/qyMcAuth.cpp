

#include "stdafx.h"
#include "qyMcMainCommon.h"



 extern  "C"  BOOL  bGetQyMcUsrRights( QY_MC * pQyMc, QYMC_USR * pUsr )
{
	 pUsr->right.canLogOn = TRUE;
	 return TRUE;
}



