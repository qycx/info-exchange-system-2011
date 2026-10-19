// isCliHelp.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "isCliHelp.h"

#include	"qyMcMainCommon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//



//
 QY_MC		*	g_pQyMc		=	NULL;

  __declspec(dllexport)  int   set_g_pQyMc_isCliHelp(  void  *  pQyMc  )
{
	g_pQyMc  =  (  QY_MC  *  )pQyMc;

#ifdef  __DEBUG__
		traceLog(  _T(  "set_g_pQyMc called"  )  );
#endif

	return  0;
}

   __declspec(dllexport)  int   set_g_dbPool_isCliHelp(  void  *  pPool,  int  cnt  )
{
	if  (  CQnmDb::useDbPool(  (  QNM_DB_MEM  *  )pPool,  cnt  )  )  return  -1;
	return  0;
 }



// CisCliHelpApp

BEGIN_MESSAGE_MAP(CisCliHelpApp, CWinApp)
END_MESSAGE_MAP()


// CisCliHelpApp construction

CisCliHelpApp::CisCliHelpApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CisCliHelpApp object

CisCliHelpApp theApp;


   __declspec(  dllexport  )  BOOL  dll_PreTranslateMessage_isCliHelp(  MSG  *  pMsg  )
  {

	   AFX_MANAGE_STATE(AfxGetStaticModuleState());

	   return  theApp.PreTranslateMessage(  pMsg  );
  }

//  2013/06/10
 HINSTANCE  get_my_hInst(  )
{
	return  theApp.m_hInstance;
}


 //
extern  IDispatch		*	gpDispOM;


// CisCliHelpApp initialization

BOOL CisCliHelpApp::InitInstance()
{
	CWinApp::InitInstance();

	//
	CCustomOccManager  *  pMgr  =  new  CCustomOccManager;
	gpDispOM  =  new  CImpIDispatch;

	//
	//  AfxEnableControlContainer();
	AfxEnableControlContainer(  pMgr  );

	//
	set_cur_iResId_sys(  CONST_resId_sys_isCliHelp  );

	//
	return TRUE;
}


int CisCliHelpApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	
	if  (  	gpDispOM  )  {
		delete  gpDispOM;  gpDispOM  =  NULL;
	}
	debugLog( "isCliHelp: ExitInstance( ) leaves." );


	return CWinApp::ExitInstance();
}
