

#include	"stdafx.h"
#include	<tchar.h>

#include	"myresource_main_ts.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"

#include	"isCmdConst.h"


///////////////
   QY_DMITEM  CONST_menuTable_op_scrollBar_ts[]  =
 {
	{	ID_stopScrollBar,		},
	{	ID_startScrollBar,		},
	 {	-1,	},
 };



   /////////////////

  QY_DMITEM  CONST_popupMenuTable_trayNotify_ts[]  =
{
	{	ID_qyShowMainWnd,			},
	//  {	-2,							},
	//  {	ID_APP_ABOUT,				},
	//  {	-2,							},
	//  {	ID_qyQuitMainWnd,			},
	{	-1,				},
};



   //  2008/11/06
 QY_DMITEM  CONST_menuTable_dlgVideos_ts[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_op,				(  TCHAR  *  )CONST_menuTable_op_scrollBar_ts,	},
	{	ID_fullScreen,			},
	{	-1,							},	
};


  #if  10  //  2013/02/06

 QY_DMITEM  CONST_menuTable_runningStatus_ts[]  =
{
	{	ID_qyRealTimeTaskList,			},
	{	-2,								},
	{	ID_sharingObjectList,			},
	{	-2,								},
	{	ID_playerList,				},
	{	-2,								},
	{	ID_wallList,				},
	{	-2,							},
	{	ID_imNetStatList,				},
	{	-2,							},
	{	ID_talkerList,				},
	{	ID_messengerStatusList,		},
	{	-2,							},
	{	ID_qList,					},
	{	-2,	},
	{	ID_myDbStatus,			},
	{	-2,							},
	{	ID_imTaskList_unproced_test,	},
	{	ID_imTaskList_cur_test,			},
	{	-1,		},
};
#endif


 QY_DMITEM  CONST_menuTable_dlgTest_ts[]  =
 {
#if  0
	 {	-3,		(  TCHAR  *  )CONST_resId_menu_op,							(  TCHAR  *  )CONST_menuTable_op_scrollBar_ts,	},
	{	-2,			},
#endif
	{	-3,		(  TCHAR  *  )CONST_resId_menu_runningStatus,				(  TCHAR  *  )CONST_menuTable_runningStatus_ts,	},
	 {	-1,							},
 };


 QY_DMITEM  CONST_popupMenuTable_mis_ts[]  =
{

	//
	{	CONST_resId_popup_trayNotify,										0,		(  TCHAR  *  )CONST_popupMenuTable_trayNotify_ts,							},
	//
	{	CONST_resId_menu_dlgVideos,											0,		(  TCHAR  *  )CONST_menuTable_dlgVideos_ts,	},
	//
	{	CONST_resId_menu_dlgTest,											0,		(  TCHAR  *  )CONST_menuTable_dlgTest_ts,								},
	//
	{	-1,		NULL,		},
};


