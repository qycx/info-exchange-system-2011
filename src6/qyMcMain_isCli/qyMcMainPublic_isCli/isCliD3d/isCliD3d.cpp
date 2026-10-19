// isCliD3d.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include	<stdlib.h>
#include	<tchar.h>

#include <d3dx9.h>

#include	"qyMcMainCommon.h"

#include	"isCliD3dCommon.h"



//
//
 QY_MC		*	g_pQyMc		=	NULL;

  __declspec(dllexport)  int   set_g_pQyMc_isCliD3d(  void  *  pQyMc  )
{
	g_pQyMc  =  (  QY_MC  *  )pQyMc;

#ifdef  __DEBUG__
		traceLog(  _T(  "set_g_pQyMc called"  )  );
#endif

	return  0;
}




//
D3D_context	g_d3dContext  =  {  NULL,  };


//
__declspec(  dllexport  )  void  *  GBuf_d3d_isCli_new(  )
{
	int					iErr	=	-1;
	GBuf_d3d_isCli  *	p  =  NULL;
	int					size;

	size  =  sizeof(  GBuf_d3d_isCli  );
	p  =  (  GBuf_d3d_isCli  *  )malloc(  size  );
	memset(  p,  0,  size  );

	iErr  =  0;
errLabel:
	if  (  iErr  )  {
		GBuf_d3d_isCli_free(  (  void  **  )&p  );
	}
	return  iErr  ?  NULL  :  p;
}


__declspec(  dllexport  )  void  GBuf_d3d_isCli_free(  void  **  ppGBuf_d3d_isCli  )
{
	if  (  !ppGBuf_d3d_isCli  )  return;
	GBuf_d3d_isCli  *  p  =  *(  GBuf_d3d_isCli  **  )ppGBuf_d3d_isCli;
	if  (  !p  )  return;

	free(  p  );
	*ppGBuf_d3d_isCli  =  NULL;
	return;
}

