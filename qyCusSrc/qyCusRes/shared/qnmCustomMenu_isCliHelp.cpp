

#include	"stdafx.h"
#include	<tchar.h>

#include	"myresource_main_isCliHelp.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"

#include	"isCmdConst.h"

#include	"qnmCustomStr_common.h"
#include	"qnmCustomStr_is.h"

  extern  QY_DMITEM		CONST_popupMenuTable_isCliHelp[];


#if  0
 QY_DMITEM  CONST_menuTable_wenJian_isCli[]  =	//  2006/12/17
{
#if  0
	{	ID_qyMgrSystems,		},
	{	-2,						},
	{	ID_qyCfgSystems,		},
	{	-2,						},
#endif
	{	ID_qySearch,			},
	//  {	ID_qyStat,				},
	{	-2,						},
	//  {	ID_qyImport,			},
	//  {	ID_qyExport,			},
	{	ID_qyClearUp,			},
	{	-2,						},
	//  {	ID_FILE_PRINT_SETUP,	},
	//  {	ID_FILE_PRINT,			},
	//  {	-2,						},
	//  {	ID_APP_EXIT,		},	//  2007/09/14, 因为OnClose(  )在客户端用来提供最小化，所以，需要用另一个菜单来使退出。
	{	ID_qyQuitMainWnd,		},
	{		-1,				},
};


 QY_DMITEM  CONST_menuTable_lianXiRenGuanLi_isClient[]  =
{
#if  0
	{	ID_qyMessengerView,	},
	{	-2,					},
#endif
	{	ID_qyMessengerList,	},
	{	-2,					},
	//  {	-3,		(  TCHAR  *  )CONST_resId_menu_yongHuGuanLi,				(  TCHAR  *  )CONST_menuTable_yongHuGuanLi_netMc2,	},
	//  {	-2,					},
	//  {	ID_retrievAll,	},
	{		ID_qyPcUsrList,	},
	{	-1,		},
 };

  QY_DMITEM  CONST_menuTable_fenZuGuanLi_isClient[]  =
{
	//  {	ID_qyNewImGrp,				},
	{	ID_qyImGrpList,				},
	{	ID_qyImGrpMemList,			},
	{	-1,		},
};


#ifdef  __SUPPORT_sm__
 QY_DMITEM  CONST_menuTable_phoneGuestGuanLi_isClient[]  =
{
	{	ID_qyPhoneGuestList,		},
	{	-1,		},
};
#endif

 QY_DMITEM  CONST_menuTable_sharedResources_isClient[]  =
{
	{	ID_sharedDynBmpList,			},
	{	-1,		},
};

 QY_DMITEM  CONST_menuTable_share_misClient[]  =
{
	{	ID_shareDynBmps,				},
	{	-1,		},
};

 QY_DMITEM  CONST_menuTable_vWall_misClient[]  =
{
	{	ID_globalVWall,	},
	{	ID_globalGpsVWall,	},
	{	-2,		},
	{	ID_gpsVWall,	},
	{	ID_newVWall,	},
	//  {	ID_virtualWallList,	},
	{	-1,		},
};



#if  10  //  2013/02/06
 QY_DMITEM  CONST_menuTable_renWuChaKan_misClient[]  =
{
	{	ID_imTaskList_unproced,		},
#if  0
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
	{	ID_qList,					},
#endif
	{	-2,							},
	{	ID_imTaskList_cur,				},
	{	-2,		},
	{	ID_imTaskList_his,				},
	{	-1,		},
};
#endif

 QY_DMITEM  CONST_menuTable_xiaoXiChaKan_misClient[]  =
{
	{		ID_qyMsgToday,		0,		0,	},
	{		ID_qyMsgList,		0,		0,	},
	{		-1,				},
};

 QY_DMITEM  CONST_menuTable_shiJianChaKan_misClient[]  =
{
	{		ID_qyEventAll,		0,		0,	},
#if  0
	{		-2,									},
	{		ID_qyOpEventAll,	0,		0,	},
#endif
	{		-1,				NULL,			},
};



 QY_DMITEM  CONST_menuTable_modulesGuanLi_isClient[]  =
{
	{		ID_cliModule1,	},
	{		-1,				},
};

 QY_DMITEM  CONST_menuTable_subtitles_isCli[]  =
 {
	 //  {	ID_subtitle_conference,		},
	 {	ID_subtitle_screen,		},
	 {	ID_subtitle_webcam,		},
	 {	-1,	},
 };
#endif

#if  0
 QY_DMITEM  CONST_menuTable_guanLi_misClient[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_lianXiRenGuanLi,				(  TCHAR  *  )CONST_menuTable_lianXiRenGuanLi_isClient,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_fenZuGuanLi,					(  TCHAR  *  )CONST_menuTable_fenZuGuanLi_isClient,	},
	{	ID_imObjRuleList,	},
	{	-2,			},
	{	ID_activeImObjList,	},
	{	-2,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_sharedResources,				(  TCHAR  *  )CONST_menuTable_sharedResources_isClient,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_vWall,						(  TCHAR  *  )CONST_menuTable_vWall_misClient,	},
	{	-2,		},
#ifdef  __SUPPORT_sm__
	{	-3,		(  TCHAR  *  )CONST_resId_menu_phoneGuest,					(  TCHAR  *  )CONST_menuTable_phoneGuestGuanLi_isClient,	},			
	{	ID_qyVerifiedPhoneList,		},
	{	-2,		},
#endif
	{	-3,		(  TCHAR  *  )CONST_resId_menu_modulesGuanLi_isClient,		(  TCHAR  *  )CONST_menuTable_modulesGuanLi_isClient,	},
	{	-2,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_subtitles,					(  TCHAR  *  )CONST_menuTable_subtitles_isCli,				},
	{	-2,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_setLocalSharing,				(  TCHAR  *  )CONST_menuTable_share_misClient,			},
	{	-2,		},
	{	ID_qyStartLocalVideo,			},
	{	ID_localPtzControl,				},
	{	-2,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_renWuChaKan,					(  TCHAR  *  )CONST_menuTable_renWuChaKan_misClient,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_xiaoXiChaKan,				(  TCHAR  *  )CONST_menuTable_xiaoXiChaKan_misClient,	},
	{	-2,		},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_shiJianChaKan,				(  TCHAR  *  )CONST_menuTable_shiJianChaKan_misClient,	},	
	{	-1,		NULL,			},

};

 QY_DMITEM	CONST_menuTable_peiZhi_misClient[]  =
{
	{	ID_cfgRasOptions,	(  TCHAR  *  )CONST_resId_policy_isClient,			},
	//  {	ID_cfgVideoConference,	},
	//  {	-2,							},
	//  {	ID_qyCfgCustom,				},
	//  {	-2,							},
	//  {	ID_cfgOptions				},
	//  {	ID_cfgAdvancedOptions		},
	{	-2,							},
	{	ID_setPasswd,				},
	//  {	ID_CFGUSR					},
	{	-1,		NULL,		},
};
	

 QY_DMITEM  CONST_menuTable_chaKan_misClient[]  =
{
	{	ID_VIEW_TOOLBAR,		},		//  MENUITEM "工具栏(&T)",                  
	{	ID_VIEW_STATUS_BAR,		},		//  MENUITEM "状态栏(&S)",                  
	{	-2,						},		//  MENUITEM SEPARATOR
	{	ID_viewQnmStaus,		},		//  MENUITEM "系统状态窗(&Z)",    
	{	-2,						},
	{	ID_notViewAudioStatus,	},
	{	ID_viewAudioStatus,		},
	{	ID_notViewVideoStatus,	},
	{	ID_viewVideoStatus,		},
	{	ID_notViewIoStatus,	},
	{	ID_viewIoStatus,		},
	{	-2,						},		//  MENUITEM SEPARATOR
	{	ID_notUseDirectX,		},
	{	ID_useDirectX,			},
	{	-2,						},
	{	ID_useDSound,			},
	{	ID_useAudioCap,			},
	{	-2,						},

	{	ID_notPrintAudioMediaType,	},
	{	ID_printAudioMediaType,		},
	{	-2,						},
#if  10
	{	ID_notShowVideoCapStatus,	},				//  2012/11/11
	{	ID_showVideoCapStatus,		},
	{	ID_notShowAudioCapStatus,	},
	{	ID_showAudioCapStatus,		},
	{	ID_notShowDrawStatus,		},
	{	ID_showDrawStatus,			},
	{	ID_notShowPlayAudioStatus,	},				//  2012/11/11
	{	ID_showPlayAudioStatus,		},
	{	-2,		},
	{	ID_notShowPktInputInfo,		},
	{	ID_showPktInputInfo,		},
	{	-2,		},
	{	ID_notUseDmo,		},
	{	ID_useDmo,		},
	{	-2,				},
	{	ID_notTestGps,	},
	{	ID_testGps,	},
#endif
	{	-2,						},
	{	ID_qyRefresh,			},		//  MENUITEM "刷新(&R)  F5",                
	{	-1,		NULL,			},
};


 QY_DMITEM  CONST_mainMenuTable_misClient[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_wenJian,		(  TCHAR  *  )CONST_menuTable_wenJian_isCli,			},	//  2006/12/17
	{	-3,		(  TCHAR  *  )CONST_resId_menu_guanLi,		(  TCHAR  *  )CONST_menuTable_guanLi_misClient,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_peiZhi,		(  TCHAR  *  )CONST_menuTable_peiZhi_misClient,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_chaKan,		(  TCHAR  *  )CONST_menuTable_chaKan_misClient,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_bangZhu,		(  TCHAR  *  )CONST_menuTable_bangZhu,	},	
	{	-1,		NULL,			},
 };

 
 QY_DMITEM  CONST_childFrmMenuTable_misClient[]  =
{
	{	-3,		(  TCHAR  *  )CONST_resId_menu_wenJian,		(  TCHAR  *  )CONST_menuTable_wenJian,			},	//  2006/12/17
	{	-3,		(  TCHAR  *  )CONST_resId_menu_guanLi,		(  TCHAR  *  )CONST_menuTable_guanLi_misClient,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_peiZhi,		(  TCHAR  *  )CONST_menuTable_peiZhi_misClient,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_chaKan,		(  TCHAR  *  )CONST_menuTable_chaKan_misClient,	},	
	{	-3,		(  TCHAR  *  )CONST_resId_menu_chuangKou,	(  TCHAR  *  )CONST_menuTable_chuangKou,	},
	{	-3,		(  TCHAR  *  )CONST_resId_menu_bangZhu,		(  TCHAR  *  )CONST_menuTable_bangZhu,	},	
	{	-1,		NULL,		},
};

/////////////////////////////////////////////////////  2010/04/14, winCe

QY_DMITEM  CONST_menuTable_winCeMain[]  =
{
	//  {	ID_retrieveAll,	},
	{	IDCANCEL,	},
	{	-1,		},
};

  QY_DMITEM  CONST_winCeMenuTable_misClient[]  =
{
	{	CONST_resId_popup0,													0,		(  TCHAR  *  )CONST_popupMenuTable_0,			},									//  -0
	{	CONST_resId_menu_winCeMain,											0,		(  TCHAR  *  )CONST_menuTable_winCeMain,		},
	{	-1,														}
 };
#endif
///////////////////////////////////  }


 QY_DMITEM  CONST_cusMenusTable_misClientHelp[]  =
{
	//  {	CONST_resId_mainMenu,				(  TCHAR  *  )CONST_mainMenuTable_misClient,			},
	//  {	CONST_resId_childFrmMenu,			(  TCHAR  *  )CONST_childFrmMenuTable_misClient,		},
	{	CONST_resId_popupMenu,				(  TCHAR  *  )CONST_popupMenuTable_isCliHelp,			},
	//  {	CONST_resId_winceMenu,				(  TCHAR  *  )CONST_winCeMenuTable_misClient,			},			//  2010/04/13
	{	-1,		NULL,		},
};

  QY_DMITEM  CONST_queryTypeTable_isCliHelp[]  =
{
	{	CONST_qyQueryType_imMsgList,				CONST_str_imMsgChaXun,		},
#if 0
	{	CONST_qyQueryType_opEventList,				CONST_str_xiTongShiJianChaXun,			},		//  2006/02/25
#endif
	{	-1,											NULL,					},
};

  //  2008/12/29
 QY_DMITEM  CONST_imTaskTypeTable_isCliHelp[]  =
{
	{	CONST_imTaskType_sendFile,					CONST_str_sendFile,						},
	{	CONST_imTaskType_recvFile,					CONST_str_recvFile,						},
	//
	{	CONST_imTaskType_transferAvInfo,			CONST_str_av,							},
	{	CONST_imTaskType_shareScreen,				CONST_str_shareScreen,					},
	{	CONST_imTaskType_remoteAssist,				CONST_str_remoteAssist,					},
	{	CONST_imTaskType_shareMediaFile,			CONST_str_shareMediaFile,		},
	{	CONST_imTaskType_shareDynBmp,				CONST_str_shareDynBmp,			},
	{	CONST_imTaskType_viewDynBmp,				CONST_str_viewDynBmp,			},
	{	CONST_imTaskType_queryCustomerServiceOfficer,CONST_str_queryCustomerServiceOfficer,	},
	//
	{	CONST_imTaskType_shareGps,					CONST_str_shareGps,				},
	{	CONST_imTaskType_viewGps,					CONST_str_viewGps,				},

	//
	{	-1,											},
};

 //  2010/09/08
 QY_DMITEM	CONST_ruleCmdTable_autoAnswer_isCliHelp[]  =
{
	{	CONST_ruleCmd_null,									_T(  ""  ),	},
	{	CONST_ruleCmd_permit,								CONST_str_permit,	},
	{	CONST_ruleCmd_permitAndFullscreen,					CONST_str_permitAndFullscreen,	},
	{	-1,			},
};

 QY_DMITEM	CONST_remoteVideoTable_isCliHelp[]  =
{
	{	CONST_resId_selectScreen,	CONST_IDC_STATIC00,	},
	{	CONST_resId_selectWebcam0,	CONST_IDC_STATIC10,	},
	{	CONST_resId_selectWebcam1,	CONST_IDC_STATIC11,	},
	{	CONST_resId_selectWebcam2,	CONST_IDC_STATIC12,	},
	{	-1,			},
};

 //  2009/01/01
 QY_DMITEM  CONST_qyStatusTable_isCliHelp[]  =
{
	{	CONST_qyStatus_ok,										_T(  "OK"  ),						},
	//	
	{	CONST_qyStatus_del,										_T(  "Del"  ),						},
	{	CONST_qyStatus_update,									_T(  "Update"  ),					},
	//
	{	CONST_qyStatus_err,										_T(  "Error"  ),					},		//  这里是-1，所以Error显示不了了
	//
	{	CONST_imTaskStatus_req,									CONST_str_qingqiu,					},		//  2007/10/07
	{	CONST_imTaskStatus_resp,								CONST_str_xiangYing,				},
	//
	{	CONST_imTaskStatus_applyToSend,							CONST_str_reqToSend,				},
	{	CONST_imTaskStatus_waitToSend,							CONST_str_waitToSend,				},
	{	CONST_imTaskStatus_applyToRecv,							CONST_str_reqToRecv,				},
	{	CONST_imTaskStatus_waitToRecv,							CONST_str_waitToRecv,				},
    //
	{	CONST_imTaskStatus_sending,								CONST_str_sending,					},
	{	CONST_imTaskStatus_receiving,							CONST_str_receiving,				},
	//
	{	CONST_imTaskStatus_sendBreak,							CONST_str_sendBreak,				},
	{	CONST_imTaskStatus_recvBreak,							CONST_str_recvBreak,				},
	//
	{	CONST_imTaskStatus_recvFinished,						CONST_str_finished,					},
	{	CONST_imTaskStatus_sendFinished,						CONST_str_finished,					},
	//
	{	CONST_imTaskStatus_acceptedByReceiver,					CONST_str_acceptedByReceiver,		},
	{	CONST_imTaskStatus_dualByReceiver,						CONST_str_dualByReceiver,		},
	//
	{	CONST_imTaskStatus_err_missingOrgReq,					CONST_str_err_missingOrgReq,		},
    //
	{	CONST_imTaskStatus_canceledBySender,					CONST_str_canceledBySender,			},
	{	CONST_imTaskStatus_canceledByReceiver,					CONST_str_canceledByReceiver,		},
	{	CONST_imTaskStatus_deniedByReceiver,					CONST_str_deniedByReceiver,			},
	//
	//
	{	-1,																		},
};
 
  QY_DMITEM  CONST_policyAvLevelTable_screen_basic_isCliHelp[]  =
{
	{	CONST_policyAvLevel_dev_2fps,				CONST_IDC_BUTTON_setDev2fpsSettings,},
	{	-1,											NULL,								},
};
  QY_DMITEM  CONST_policyAvLevelTable_screen_standard_isCliHelp[]  =
{
	{	CONST_policyAvLevel_dev_2fps,				CONST_IDC_BUTTON_setDev2fpsSettings,},
	{	CONST_policyAvLevel_dev_5fps,				CONST_IDC_BUTTON_setDev5fpsSettings,},
	//  2012/10/29
	{	CONST_policyAvLevel_dev_5fps1,				CONST_IDC_BUTTON_setDev5fpsSettings1,},
	{	CONST_policyAvLevel_dev_5fps2,				CONST_IDC_BUTTON_setDev5fpsSettings2,},
	{	CONST_policyAvLevel_dev_5fps3,				CONST_IDC_BUTTON_setDev5fpsSettings3,},
	{	CONST_policyAvLevel_dev_5fps4,				CONST_IDC_BUTTON_setDev5fpsSettings4,},
	{	CONST_policyAvLevel_dev_5fps5,				CONST_IDC_BUTTON_setDev5fpsSettings5,},
	//
	{	-1,											NULL,								},
};
  QY_DMITEM  CONST_policyAvLevelTable_screen_high_isCliHelp[]  =
{
	{	CONST_policyAvLevel_dev_2fps,				CONST_IDC_BUTTON_setDev2fpsSettings,},
	{	CONST_policyAvLevel_dev_5fps,				CONST_IDC_BUTTON_setDev5fpsSettings,},
	//  2012/10/29
	{	CONST_policyAvLevel_dev_5fps1,				CONST_IDC_BUTTON_setDev5fpsSettings1,},
	{	CONST_policyAvLevel_dev_5fps2,				CONST_IDC_BUTTON_setDev5fpsSettings2,},
	{	CONST_policyAvLevel_dev_5fps3,				CONST_IDC_BUTTON_setDev5fpsSettings3,},
	{	CONST_policyAvLevel_dev_5fps4,				CONST_IDC_BUTTON_setDev5fpsSettings4,},
	{	CONST_policyAvLevel_dev_5fps5,				CONST_IDC_BUTTON_setDev5fpsSettings5,},
	//
	{	-1,											NULL,								},
};

 QY_DMITEM  CONST_policyAvLevelTable_mediaFile_basic_isCliHelp[]  =
{
	{	CONST_policyAvLevel_dev_2fps,				CONST_IDC_BUTTON_setDev2fpsSettings,},
	{	CONST_policyAvLevel_dev_10fps,				CONST_IDC_BUTTON_setDev10fpsSettings,},
	{	-1,											NULL,								},
};

 QY_DMITEM  CONST_policyAvLevelTable_mediaFile_standard_isCliHelp[]  =
{
	{	CONST_policyAvLevel_dev_2fps,				CONST_IDC_BUTTON_setDev2fpsSettings,},
	{	CONST_policyAvLevel_dev_5fps1,				CONST_IDC_BUTTON_setDev5fpsSettings1,},
	{	CONST_policyAvLevel_dev_5fps2,				CONST_IDC_BUTTON_setDev5fpsSettings2,},
	{	CONST_policyAvLevel_dev_5fps3,				CONST_IDC_BUTTON_setDev5fpsSettings3,},
	{	CONST_policyAvLevel_dev_sd24fps,			CONST_IDC_BUTTON_setDevSd24fpsSettings,},
	{	CONST_policyAvLevel_dev_sd25fps,			CONST_IDC_BUTTON_setDevSd25fpsSettings,},
	{	CONST_policyAvLevel_dev_sd30fps,			CONST_IDC_BUTTON_setDevSd30fpsSettings,},
	{	-1,											NULL,								},
};

 QY_DMITEM  CONST_policyAvLevelTable_mediaFile_high_isCliHelp[]  =
{
	{	CONST_policyAvLevel_dev_2fps,				CONST_IDC_BUTTON_setDev2fpsSettings,},
	{	CONST_policyAvLevel_dev_5fps1,				CONST_IDC_BUTTON_setDev5fpsSettings1,},
	{	CONST_policyAvLevel_dev_5fps2,				CONST_IDC_BUTTON_setDev5fpsSettings2,},
	{	CONST_policyAvLevel_dev_5fps3,				CONST_IDC_BUTTON_setDev5fpsSettings3,},
	{	CONST_policyAvLevel_dev_sd24fps,			CONST_IDC_BUTTON_setDevSd24fpsSettings,},
	{	CONST_policyAvLevel_dev_sd25fps,			CONST_IDC_BUTTON_setDevSd25fpsSettings,},
	{	CONST_policyAvLevel_dev_sd30fps,			CONST_IDC_BUTTON_setDevSd30fpsSettings,},
	{	CONST_policyAvLevel_dev_24fps,				CONST_IDC_BUTTON_setDev24fpsSettings,},
	{	CONST_policyAvLevel_dev_25fps,				CONST_IDC_BUTTON_setDev25fpsSettings,},
	{	CONST_policyAvLevel_dev_30fps,				CONST_IDC_BUTTON_setDev30fpsSettings,},
	{	-1,											NULL,								},
};

 QY_DMITEM  CONST_policyAvLevelTable_mediaDevice_basic_isCliHelp[]  =
{
	{	CONST_policyAvLevel_dev_2fps,				CONST_IDC_BUTTON_setDev2fpsSettings,},
	{	-1,											NULL,								},
};
 QY_DMITEM  CONST_policyAvLevelTable_mediaDevice_standard_isCliHelp[]  =
{
	{	CONST_policyAvLevel_dev_2fps,				CONST_IDC_BUTTON_setDev2fpsSettings,},
	{	CONST_policyAvLevel_dev_5fps1,				CONST_IDC_BUTTON_setDev5fpsSettings1,},
	{	CONST_policyAvLevel_dev_5fps2,				CONST_IDC_BUTTON_setDev5fpsSettings2,},
	{	CONST_policyAvLevel_dev_5fps3,				CONST_IDC_BUTTON_setDev5fpsSettings3,},
	{	CONST_policyAvLevel_dev_sd24fps,			CONST_IDC_BUTTON_setDevSd24fpsSettings,},
	{	CONST_policyAvLevel_dev_sd25fps,			CONST_IDC_BUTTON_setDevSd25fpsSettings,},
	{	CONST_policyAvLevel_dev_sd30fps,			CONST_IDC_BUTTON_setDevSd30fpsSettings,},
	{	-1,											NULL,								},
};
 QY_DMITEM  CONST_policyAvLevelTable_mediaDevice_high_isCliHelp[]  =
{
	{	CONST_policyAvLevel_dev_2fps,				CONST_IDC_BUTTON_setDev2fpsSettings,},
	{	CONST_policyAvLevel_dev_5fps1,				CONST_IDC_BUTTON_setDev5fpsSettings1,},
	{	CONST_policyAvLevel_dev_5fps2,				CONST_IDC_BUTTON_setDev5fpsSettings2,},
	{	CONST_policyAvLevel_dev_5fps3,				CONST_IDC_BUTTON_setDev5fpsSettings3,},
	{	CONST_policyAvLevel_dev_sd24fps,			CONST_IDC_BUTTON_setDevSd24fpsSettings,},
	{	CONST_policyAvLevel_dev_sd25fps,			CONST_IDC_BUTTON_setDevSd25fpsSettings,},
	{	CONST_policyAvLevel_dev_sd30fps,			CONST_IDC_BUTTON_setDevSd30fpsSettings,},
	{	CONST_policyAvLevel_dev_24fps,				CONST_IDC_BUTTON_setDev24fpsSettings,},
	{	CONST_policyAvLevel_dev_25fps,				CONST_IDC_BUTTON_setDev25fpsSettings,},
	{	CONST_policyAvLevel_dev_30fps,				CONST_IDC_BUTTON_setDev30fpsSettings,},
	{	-1,											NULL,								},
};

 QY_DMITEM  CONST_usLayoutTypeTable_isCliHelp[]  =
{
	{		CONST_usLayoutType_null,							CONST_str_layout_auto,				},
	{		CONST_usLayoutType_dialog,							CONST_str_layout_dialog,			},
	{		CONST_usLayoutType_conference,						CONST_str_layout_conference,		},
	{		CONST_usLayoutType_training,						CONST_str_layout_training,			},
	{		CONST_usLayoutType_videoOnly,						CONST_str_layout_videoOnly,		},
	{		CONST_usLayoutType_resourceOnly,					CONST_str_layout_resourceOnly,		},
	{		-1,						},
};
 QY_DMITEM  CONST_usLayoutTypeTable_resource_isCliHelp[]  =
{
	{		CONST_usLayoutType_null,							CONST_str_layout_auto,				},
	{		CONST_usLayoutType_dialog,							CONST_str_layout_dialog,			},
	{		CONST_usLayoutType_resourceOnly,					CONST_str_layout_resourceOnly,		},
	{		-1,						},
};


  QY_DMITEM  CONST_tableTable_misClientHelp[]  =
{
	{ 	CONST_resId_qnmEventTypeTable0,			(  TCHAR  *  )CONST_qnmEventTypeTable0_is,		},
	{	CONST_resId_qnmEventTypeTable_pc,		(  TCHAR  *  )CONST_qnmEventTypeTable_assetMgr,		},
	{	CONST_resId_qnmEventTypeTable_op,		(  TCHAR  *  )CONST_qnmEventTypeTable_op_is,		},
	{	CONST_resId_ipScanOfficeLevelTable,		(  TCHAR  *  )CONST_ipScanOfficeLevelTable,	},
	{	CONST_resId_zjgaYhlxTable,				(  TCHAR  *  )CONST_zjgaYhlxTable,			},
	{	CONST_resId_gYhGrpTable,				(  TCHAR  *  )gYhGrpTable,					},
	{	CONST_resId_gEventYhGrpTable,			(  TCHAR  *  )gEventYhGrpTable,				},
	//  {	CONST_resId_qnmEventTypeTable_secChk,	(  TCHAR  *  )CONST_qnmEventTypeTable_secChk,	},
	{	CONST_resId_qyNullTable,				(  TCHAR  *  )CONST_nullTable,				},
	{	CONST_resId_jqlxTable,					(  TCHAR  *  )CONST_jqlxTable,					},
	{	CONST_resId_qySystemIdTable,			(  TCHAR  *  )CONST_qySystemIdTable,				},
	{	CONST_resId_ucbDsnlessTable,			(  TCHAR  *  )CONST_ucbDsnlessTable,				},
	{	CONST_resId_myCONST_yhGrpTable_netMc,	(  TCHAR  *  )myCONST_yhGrpTable_netMc,				},
	{	CONST_resId_myCONST_eventYhGrpTable_netMc,(  TCHAR  *  )myCONST_eventYhGrpTable_netMc,		},
	{	CONST_resId_myCONST_yhGrpTable_is,		(  TCHAR  *  )myCONST_yhGrpTable_is,				},
	{	CONST_resId_myCONST_eventYhGrpTable_is,	(  TCHAR  *  )myCONST_eventYhGrpTable_is,			},
	//
	{	CONST_resId_objTypeTable,				(  TCHAR  *  )CONST_objTypeTable,					},
	//  {	CONST_resId_queryTypeTable,				(  TCHAR  *  )CONST_queryTypeTable_isClient,		},
	{	CONST_resId_fieldIdTable,				(  TCHAR  *  )CONST_fieldIdTable,					},
	//
	{	CONST_resId_imTaskTypeTable,			(  TCHAR  *  )CONST_imTaskTypeTable,				},
	{	CONST_resId_qyStatusTable,				(  TCHAR  *  )CONST_qyStatusTable,					},
	{	CONST_resId_imTaskStatusTable,				(  TCHAR  *  )CONST_imTaskStatusTable,				},
	//  2009/01/01
	{	CONST_resId_qyCommTypeTable,			(  TCHAR  *  )CONST_qyCommTypeTable,				},
	{	CONST_resId_pcCommTypeTable,			(  TCHAR  *  )CONST_pcCommTypeTable,				},
	{	CONST_resId_grpNameTable,				(  TCHAR  *  )CONST_grpNameTable,					},
	{	CONST_resId_usRunningStatusTable,		(  TCHAR  *  )CONST_usRunningStatusTable,			},

	//
	{	CONST_resId_ruleTypeTable,				(  TCHAR  *  )CONST_ruleTypeTable_is,				},
	{	CONST_resId_usLayoutTypeTable,			(  TCHAR  *  )CONST_usLayoutTypeTable,				},
	{	CONST_resId_usLayoutTypeTable_resource,	(  TCHAR  *  )CONST_usLayoutTypeTable_resource,		},
	{	CONST_resId_ruleCmdTable,				(  TCHAR  *  )CONST_ruleCmdTable,					},
	{	CONST_resId_ruleCmdTable_autoAnswer,	(  TCHAR  *  )CONST_ruleCmdTable_autoAnswer,		},

	{	CONST_resId_remoteVideoTable,			(  TCHAR  *  )CONST_remoteVideoTable,				},

	//
	//  {	CONST_resId_menu_conferenceWall,				(  TCHAR  *  )CONST_menuTable_conferenceWall,		},
	{	CONST_resId_menu_shareFullScreen,		(  TCHAR  *  )CONST_table_shareFullScreen,					},
	{	CONST_resId_menu_startShareMediaFile,	(  TCHAR  *  )CONST_table_startShareMediaFile,				},
	{	CONST_resId_menu_startShareMediaDevice,	(  TCHAR  *  )CONST_table_startShareMediaDevice,			},

	//
	{	CONST_resId_policyAvLevelTable_basic,				(  TCHAR  *  )CONST_policyAvLevelTable_basic,		},
	{	CONST_resId_policyAvLevelTable_standard,			(  TCHAR  *  )CONST_policyAvLevelTable_standard,	},
	{	CONST_resId_policyAvLevelTable_high,				(  TCHAR  *  )CONST_policyAvLevelTable_high,		},
	{	CONST_resId_policyAvLevelTable_screen_basic,		(  TCHAR  *  )CONST_policyAvLevelTable_screen_basic,		},
	{	CONST_resId_policyAvLevelTable_screen_standard,		(  TCHAR  *  )CONST_policyAvLevelTable_screen_standard,		},
	{	CONST_resId_policyAvLevelTable_screen_high,			(  TCHAR  *  )CONST_policyAvLevelTable_screen_high,		},
	{	CONST_resId_policyAvLevelTable_mediaFile_basic,		(  TCHAR  *  )CONST_policyAvLevelTable_mediaFile_basic,	},
	{	CONST_resId_policyAvLevelTable_mediaFile_standard,	(  TCHAR  *  )CONST_policyAvLevelTable_mediaFile_standard,	},
	{	CONST_resId_policyAvLevelTable_mediaFile_high,		(  TCHAR  *  )CONST_policyAvLevelTable_mediaFile_high,	},
	{	CONST_resId_policyAvLevelTable_mediaDevice_basic,	(  TCHAR  *  )CONST_policyAvLevelTable_mediaDevice_basic,  },
	{	CONST_resId_policyAvLevelTable_mediaDevice_standard,(  TCHAR  *  )CONST_policyAvLevelTable_mediaDevice_standard,  },
	{	CONST_resId_policyAvLevelTable_mediaDevice_high,	(  TCHAR  *  )CONST_policyAvLevelTable_mediaDevice_high,  },
	{	CONST_resId_policyAvLevelTable_webcam_basic,		(  TCHAR  *  )CONST_policyAvLevelTable_webcam_basic,		},
	{	CONST_resId_policyAvLevelTable_webcam_standard,		(  TCHAR  *  )CONST_policyAvLevelTable_webcam_standard,		},

	{	CONST_resId_iTargetUsageTable,						(  TCHAR  *  )CONST_iTargetUsageTable,				},
	{	CONST_resId_iAvgBitrateTable,						(  TCHAR  *  )CONST_iAvgBitrateTable,				},	

	{	-1,		NULL,		},
};

  extern  QY_DMITEM		CONST_strTable_isCliHelp[];
  //
  extern  QY_DMITEM		CONST_dlgTable_isCliHelp[];
  //
  //  extern  QY_DMITEM		CONST_searchTable_isCliHelp[];
  
 QY_DMITEM  CONST_cusResTable_isCliHelp[]  =
{
 	{	CONST_resType_str,						(  TCHAR  *  )CONST_strTable_isCliHelp,						},
	{	CONST_resType_table,					(  TCHAR  *  )CONST_tableTable_misClientHelp,			},
	{	CONST_resType_dlg,						(  TCHAR  *  )CONST_dlgTable_isCliHelp,						},
 	{	CONST_resType_menu,						(  TCHAR  *  )CONST_cusMenusTable_misClientHelp,				},
	  {	CONST_resType_query,					(  TCHAR  *  )CONST_queryTable_mis,						},
	  {	CONST_resType_search,					(  TCHAR  *  )CONST_searchTable,						},
	  {	CONST_resType_columnInfo,				(  TCHAR  *  )CONST_columnInfoTable,				},
	{	-1,		NULL,		},
};



