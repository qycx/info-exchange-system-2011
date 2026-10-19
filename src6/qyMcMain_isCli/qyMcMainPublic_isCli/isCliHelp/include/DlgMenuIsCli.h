#pragma once


typedef  struct  __dlgGuiDataMenuIsCli_t							{
				 BOOL												bInited;

				 int												iWndContentType;

				 int												iIDC_BUTTON_contact;
				 int												iIDC_BUTTON_group;
				 //
				 int												iIDC_BUTTON_fullScreen;
				 //
				 int												iIDC_BUTTON_testLocalAv;
				 int												iIDC_BUTTON_msg;
				 //
				 int												iIDC_BUTTON_policy;
				 int												iIDC_BUTTON_conferenceQuality;
				 //
				 int												iIDC_BUTTON_quit;
				 int												iIDC_BUTTON_about;
				 //
				 int												iIDC_STATIC_meDesc;
				 //
				 int												iIDCANCEL;
				 //
				 int												w_org,  h_org;
				 RECT												rcIDC_BUTTON_contact;	
				 RECT												rcIDC_BUTTON_group;
				 RECT												rcIDCANCEL;
				 //
				 RECT												rcIDC_BUTTON_fullScreen;
				 RECT												rcIDC_BUTTON_testLocalAv;
				 RECT												rcIDC_BUTTON_msg;
				 RECT												rcIDC_BUTTON_policy;
				 RECT												rcIDC_BUTTON_conferenceQuality;
				 RECT												rcIDC_BUTTON_quit;
				 RECT												rcIDC_BUTTON_about;
				 RECT												rcIDC_STATIC_meDesc;
				 //
			 
				 //  BOOL												m_bFullScreen_parent;
				 int												iWndContentType_hParent;		//  2013/07/12


}		 DLG_guiData_menuIsCli;

typedef  struct  __dlgMenuIsCliVar_t								{	
				 DLG_guiData_menuIsCli								guiData;

				 //  UINT_PTR											wTimerID;

}		 DLG_menuIsCli_var;

// CDlgMenuIsCli dialog
#if  0
class CDlgMenuIsCli : public CDialog
{
	DECLARE_DYNAMIC(CDlgMenuIsCli)

public:
	CDlgMenuIsCli(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgMenuIsCli();

// Dialog Data
	enum { IDD = IDD_menu_isCli };

	DLG_menuIsCli_var			m_var;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMoving(UINT fwSide, LPRECT pRect);
	afx_msg void OnBnClickedButtoncontact();
	afx_msg void OnBnClickedButtongroup();
};
#endif


#include	"qyWnd.h"

class CDlgMenuIsCli : public CQyWnd
{

public:
	CDlgMenuIsCli(  );   // standard constructor
	virtual ~CDlgMenuIsCli();

// Dialog Data
	//  enum { IDD = IDD_mcClient_logon };

	DLG_menuIsCli_var			m_var;


	virtual  void  *  getGuiData(  )  {  return  &m_var.guiData;  }
	virtual  void  *  getVar(  )  {  return  &m_var;	}

};
