
#include "stdafx.h"
#include	<stdlib.h>
#include	<tchar.h>

#include <d3dx9.h>


#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

#include	"qySyncCommProc.h"
#include	"qmcVideoCapture.h"


#include	"isCliD3dCommon.h"
#include	"dlgWallD3d.h"
#include	"qisWallsProc.h"


__declspec(  dllexport  )  void  *  qisWallsNew(  unsigned  short  usMaxCnt  )
{
	int				iErr	=	-1;
	QIS_walls  *	p		=  NULL;

	if  (  !usMaxCnt  )  return  NULL;
	int  size;

	size  =  sizeof(  QIS_walls  );
	p  =  (  QIS_walls  *  )malloc(  size  );
	if  (  !p  )  goto  errLabel;
	memset(  p,  0,  size  );
	
	p->usCnt  =  usMaxCnt;
	size  =  sizeof(  QIS_wallD3d_mem  )  *  p->usCnt;
	p->pMems  =  (  QIS_wallD3d_mem  *  )malloc(  size  );
	if  (  !p->pMems  )  goto  errLabel;
	memset(  p->pMems,  0,  size  );
	
	iErr  =  0;
errLabel:

	if  (  iErr  )  {
		qisWallsFree(  (  void  **  )&p  );
	}
	return  iErr  ?  NULL  :  p;
}



__declspec(  dllexport  )  void  qisWallsFree(  void  **  ppQIS_walls  )
{
	if  (  !ppQIS_walls  )  return;
	QIS_walls  *  p  =  *(  QIS_walls  **  )ppQIS_walls;
	if  (  !p  )  return;
	if  (  p->pMems  )  {
		MACRO_safeFree(  p->pMems  );  
	}
	MACRO_safeFree(  p  );
	*ppQIS_walls  =  NULL;
	return;
}


