
#ifndef  __DLGQYMCWINCE_H__
#define  __DLGQYMCWINCE_H__	//  {

#include	"qyWnd.h"

class CDlg_qyMc_winCe : public CQyWnd
{
public:
	CDlg_qyMc_winCe(  );
	~CDlg_qyMc_winCe(  );

	QY_MC_mainWndVar			var;
#ifndef  __TEST__
	CCeMenuBar					m_menuBar;
#endif
	HICON m_hIcon;

	virtual  void  *  getGuiData(  )  {  return  &var.guiData;  }
	virtual  void  *  getVar(  )  {  return  &var;  }

	//  virtual BOOL OnInitDialog( );
	//  virtual void OnDestroy( );

	//  LONG  OnQyComm( UINT, LONG );

	//  void Onqyquitmainwnd();


};




#endif

