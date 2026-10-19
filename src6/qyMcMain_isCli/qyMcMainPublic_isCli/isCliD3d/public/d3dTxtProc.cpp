




#include "stdafx.h"
#include	<stdlib.h>
#include	<tchar.h>

#include <d3dx9.h>


#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"

//  #include	"qyCommProc.h"

#include	"isCliD3dCommon.h"


D3DLIGHT9  init_directional_light( D3DXVECTOR3 * direction,  D3DXCOLOR* color  )
{
	D3DLIGHT9  light;
	ZeroMemory(  &light,  sizeof(  light  ) );

	light.Type  =  D3DLIGHT_DIRECTIONAL;
	light.Ambient  =  *color *  0.6f;
	light.Diffuse  =  *color;
	light.Specular  =  *color * 0.6f;
	light.Direction  =  *direction;

	return light;
}

D3DMATERIAL9  init_material(  D3DXCOLOR  ambient,  D3DXCOLOR  diffuse,  D3DXCOLOR  specular,  D3DXCOLOR  emissive,  float  power  )
{
	D3DMATERIAL9  material;
	ZeroMemory(  &material,  sizeof(  material  )  );

	material.Ambient  =  ambient;
	material.Diffuse  =  diffuse;
	material.Specular  =  specular;
	material.Emissive  =  emissive;
	material.Power  =  power;

	return  material;
}

const  D3DXCOLOR  WHITE  =  D3DCOLOR_XRGB(  255,255,255  );
const  D3DXCOLOR  BLACK  =  D3DCOLOR_XRGB(  0,0,0  );
const  D3DMATERIAL9  WHITE_MATERIAL  =   init_material(  WHITE, WHITE, WHITE,  BLACK,  2.0f  );



int  init_txt(  LPDIRECT3DDEVICE9  g_pd3dDevice,  CTX_d3dTxt  *  pCtxTxt,  LPCTSTR  hint  )
{
	int		iErr	=	-1;

	if  (  !hint  )  return  -1;


	HDC  hDc  =  NULL;
	HFONT  font  =  NULL;
	HFONT  font_old  =  NULL;
	
	hDc  =  CreateCompatibleDC(  NULL  );
	if  (  !hDc  )  goto  errLabel;

	LOGFONT  lf;
	ZeroMemory(  &lf, sizeof(  LOGFONT  )  );

	lf.lfHeight  =  25;
	lf.lfWidth  =  12;
	lf.lfEscapement  =  0;
	lf.lfOrientation  =  0;
	lf.lfWeight  =  500;
	lf.lfItalic  =  FALSE;
	lf.lfUnderline  =  FALSE;
	lf.lfStrikeOut  =  FALSE;
	lf.lfCharSet  =  DEFAULT_CHARSET;
	lf.lfOutPrecision  =  0;
	lf.lfClipPrecision  =  0;
	lf.lfQuality  =  0;
	lf.lfPitchAndFamily  =  0;

	_tcscpy(  lf.lfFaceName,  _T(  "Times New Roman"  )  );

	font  =  CreateFontIndirect(  &lf  );
	if  (  !font  )  goto  errLabel;
	font_old  =  (HFONT )SelectObject(  hDc,  font  );

	if  (  FAILED(  D3DXCreateText(  g_pd3dDevice,  hDc,  hint,  0.001f,  0.4f,  &pCtxTxt->g_pMesh,  NULL,  NULL  )  )  )  goto  errLabel;

	//  restore  old font
	if  (  font_old  )  {
		SelectObject(  hDc,  font_old  );  font_old  =  NULL;
	}
	DeleteObject(  font  );  font  =  NULL;
	DeleteDC(  hDc  );  hDc  =  NULL;

	//  light
	D3DXVECTOR3  light_dir(  0.0f,  -0.5f,  1.0f  );
	D3DXCOLOR  color  =  D3DCOLOR_XRGB(  255,255, 255  );
	D3DLIGHT9  light  =  init_directional_light(  &light_dir,  &color  );

	g_pd3dDevice->SetLight(  0,  &light  );
	g_pd3dDevice->LightEnable(  0,  TRUE  );

	g_pd3dDevice->SetRenderState(  D3DRS_NORMALIZENORMALS,  TRUE  );
	g_pd3dDevice->SetRenderState(  D3DRS_SPECULARENABLE,  TRUE  );

	iErr  =  0;

errLabel:
	
	if  (  font_old  )  {
		SelectObject(  hDc,  font_old  );  font_old  =  NULL;
	}
	if  (  font  )  {
		DeleteObject(  font  );  font  =  NULL;
	}
	if  (  hDc  )  {
		DeleteDC(  hDc  );
	}

	if  (  iErr  )  {
		exit_txt(  g_pd3dDevice,  pCtxTxt  );
	}

	return  iErr;	
}

int  exit_txt(  LPDIRECT3DDEVICE9  g_pd3dDevice,  CTX_d3dTxt  *  pCtxTxt  )
{
	MACRO_safeRelease(  pCtxTxt->g_pMesh  );

	return  0;
	
}


BOOL  bSetupMatrix_txt(  LPDIRECT3DDEVICE9  g_pd3dDevice,  int  wnd_w,  int  wnd_h  )
{
	if  (  !wnd_w  ||  !wnd_h  )  return  FALSE;

		//  camera
	D3DXVECTOR3  pos(  0.0f,  1.5f,  -3.3f  );
	D3DXVECTOR3  target(  0.0f,  0.0f,  0.0f  );
	D3DXVECTOR3  up(  0.0f,  1.0f,  0.0f  );

#if  10
	//
	D3DXMATRIX  view_matrix;
	D3DXMatrixLookAtLH(  &view_matrix,  &pos,  &target,  &up  );
	g_pd3dDevice->SetTransform(  D3DTS_VIEW,  &view_matrix  );

	//
	D3DXMATRIX  proj;
	D3DXMatrixPerspectiveFovLH(  &proj,  D3DX_PI  *  0.25f,  (  float  )wnd_w/wnd_h,  0.01f,  1000.0f  );
	g_pd3dDevice->SetTransform(  D3DTS_PROJECTION,  &proj  );
#endif

	return  TRUE;
}


int  display_txt(  LPDIRECT3DDEVICE9  g_pd3dDevice, CTX_d3dTxt  *  pCtxTxt,  float  time_delta  )
{
	if  (  !pCtxTxt->g_pMesh  )  return  -1;

#if  10
	//  update:spin the  3D text
	D3DXMATRIX  Ry,  tran_mat;
	static  float  y =  0.0f;
	D3DXMatrixRotationY(  &Ry,  y );
	y  +=  time_delta;

	if  (  y  >=  6.28f  )  y  =  0.0f;

	D3DXMatrixTranslation(  &tran_mat,  -1.6f,  0.0f,  0.0f  );
	tran_mat  *=  Ry;

	g_pd3dDevice->SetTransform(  D3DTS_WORLD,  &tran_mat  );
#endif
	
	//
	g_pd3dDevice->SetMaterial(  &WHITE_MATERIAL  );		
	pCtxTxt->g_pMesh->DrawSubset(  0  );

	//  Render(  );

	return  0;
}
