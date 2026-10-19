


#include "stdafx.h"
#include	<stdlib.h>
#include	<tchar.h>

#include <d3dx9.h>


#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"


#include	"isCliD3dCommon.h"


//  该函数只能在装载线程里调用
 QIS_textureInfo  *  getTextureInfo_toFill(  QIS_textureInfo2  *  p  )
{
	//  QIS_textureInfo  *  pTextureInfo_toRend  =  NULL;
	QIS_textureInfo  *  pTextureInfo_toFill  =  NULL;
	
	if  (  p->bFlag_toRend_mem1  )  {
		//  pTextureInfo_toRend  =  &p->mems[1];
		pTextureInfo_toFill  =  &p->mems[0];
	    }
	else  {
		  //  pTextureInfo_toRend  =  &p->mems[0];
		  pTextureInfo_toFill  =  &p->mems[1];
	}

	if  (  pTextureInfo_toFill->bDataReady  )  return  NULL;

	return  pTextureInfo_toFill;
}


//  该函书只能在render线程里调用
QIS_textureInfo  *  getTextureInfo_toRend(  QIS_textureInfo2  *  p  )
{
	QIS_textureInfo  *  pTextureInfo_toRend  =  NULL;
	QIS_textureInfo  *  pTextureInfo_toFill  =  NULL;
	
	if  (  p->bFlag_toRend_mem1  )  {
		pTextureInfo_toRend  =  &p->mems[1];
		pTextureInfo_toFill  =  &p->mems[0];
	    }
	else  {
		  pTextureInfo_toRend  =  &p->mems[0];
		  pTextureInfo_toFill  =  &p->mems[1];
	}

	if  (  pTextureInfo_toFill->bDataReady  )  {
		pTextureInfo_toRend->bDataReady  =  FALSE;
		p->bFlag_toRend_mem1  =  !p->bFlag_toRend_mem1;
		pTextureInfo_toRend  =  pTextureInfo_toFill;
		return  pTextureInfo_toRend;
	}

	if  (  !pTextureInfo_toRend->bDataReady  )  return  NULL;

	return  pTextureInfo_toRend;
}




