#pragma once



#include	"dlgObjsProc.h"

#include	"qyWnd.h"

class CDlgObjs : public CQyWnd
{

public:
	CDlgObjs(  HWND  hParent = NULL);   // standard constructor
	virtual ~CDlgObjs();

// Dialog Data
	//  enum { IDD = IDD_objs };

	DLG_objs_var			m_var;

#ifndef  __TEST__
	CCeMenuBar			m_menuBar;
#endif

	virtual  void  *  getGuiData(  )  {  return  &m_var.guiData;  }
	virtual  void  *  getVar(  )  {  return  &m_var;  }

	//  BOOL  bFillContent(  int  iObjType  );

	//  virtual BOOL OnInitDialog();

	//  virtual void OnOK();
};

