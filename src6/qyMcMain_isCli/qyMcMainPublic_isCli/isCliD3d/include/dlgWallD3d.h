

#ifndef  __dlgWallD3d_h__
#define  __dlgWallD3d_h__

#include	"qywnd.h"
#include	"WallTalkers.h"


class CDlgWallD3d : public CQyWnd
{
// Construction
public:
	CDlgWallD3d();	// standard constructor
	virtual  ~CDlgWallD3d(  );

// Dialog Data

// Dialog Data
	
	struct						{
		DLG_wall_var			wall;


	}							m_var;
	//  CBrush						m_brush_fullScreen_dlg;


	//
	void  *  getGuiData(  )  {
				return  NULL;
	}
	void  *  getVar(  )  {
				return  &m_var;
	}
	
	//
	BOOL	Create(const RECT& rect);
	BOOL	bQuitDlg(  );
	
	//
	void			endFullScreen(  );

	//
	virtual BOOL OnInitDialog();

	//	
	virtual void OnCancel();
	void OnClose();
	void OnDestroy();	
	void OnSize(UINT nType, int cx, int cy);	
	void Onfullscreen();
	void OnMoving(UINT fwSide, LPRECT pRect);
	void OnMove(int x, int y);
	void myMouseMove(  WPARAM  wParam, LPARAM  lParam);

	//
	void OnTimer(UINT_PTR nIDEvent);		

	//
	void OnIsCmd(  UINT nID  );
	
	//
	virtual void PostNcDestroy();


};



#endif



