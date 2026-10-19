

#ifndef  __isCliD3dCommon_h__
#define  __isCliD3dCommon_h__	//  {



typedef  struct  __qisTextureInfo_t				{
				 LPDIRECT3DTEXTURE9				pTexture;
				 //
				 BOOL							bDataReady;			//  装载线程装完数据后,设置bReady为true
																	//  render线程使用bReady为true的texture进行绘制.
																	//  等另一个texture ready时,就将正使用的bReady设置为false, 然后. 切换标志位bFlag_toRend_mem1 

				 //
				 long							lCnt_used;			//  toFill在处理前时,要对此值+1,处理完-1
																	//

}		 QIS_textureInfo;

typedef  struct  __qisTextureInfo2_t			{
				 //
				 int							iW;
				 int							iH;

				 //
				 BOOL							bFlag_toRend_mem1;
				 QIS_textureInfo				mems[2];
				 //
				 BOOL							bQuit;				//  清理前,要先设置此标志位. 然后等待iCnt_used为0,就可以清理了
}		 QIS_textureInfo2;

//
typedef  struct  __ctxTxt_t						{
				 ID3DXMesh					*	g_pMesh;
}		 CTX_d3dTxt;


typedef  struct	 __d3dContext_t					{
				 LPDIRECT3D9					g_pD3D;				//  =  NULL;
				 LPDIRECT3DDEVICE9				g_pd3dDevice;		//  =  NULL;
				 
				 //
				 int							wnd_w,  wnd_h;
				 float							last_time;

				 //
				 ID3DXFont				*		g_pFont;

				 //
				 LPDIRECT3DVERTEXBUFFER9		g_pVB;				//  =  NULL;
				 //  LPDIRECT3DTEXTURE9				g_pTexture;			//  =  NULL;
				 QIS_textureInfo2				textureInfo2;

				 //
				 CTX_d3dTxt						ctx_txt;

}		 D3D_context;



//
struct  CUSTOMVERTEX  {
			float x, y, z;
			float u, v;
};

#define	D3DFVF_CUSTOMVERTEX  (D3DFVF_XYZ|D3DFVF_TEX1)		// 顶点格式



#include	"isCliD3dPublic.h"








//
extern  D3D_context	g_d3dContext;

//
QIS_textureInfo  *  getTextureInfo_toFill(  QIS_textureInfo2  *  p  );
QIS_textureInfo  *  getTextureInfo_toRend(  QIS_textureInfo2  *  p  );

//
int  init_txt(  LPDIRECT3DDEVICE9  g_pd3dDevice,  CTX_d3dTxt  *  pCtxTxt,  LPCTSTR  hint  );
int  exit_txt(  LPDIRECT3DDEVICE9  g_pd3dDevice,  CTX_d3dTxt  *  pCtxTxt  );
BOOL  bSetupMatrix_txt(  LPDIRECT3DDEVICE9  g_pd3dDevice,  int  wnd_w,  int  wnd_h  );
int   display_txt(  LPDIRECT3DDEVICE9  g_pd3dDevice, CTX_d3dTxt  *  pCtxTxt,  float  time_delta  );




#endif  //  }

