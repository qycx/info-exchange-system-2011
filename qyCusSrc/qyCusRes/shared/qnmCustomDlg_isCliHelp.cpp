
#include	"stdafx.h"
#include	<tchar.h>
//  #include	"qyCommon.h"
#include	"myresource_main_isCliHelp.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"

#include	"qnmCustomStr_common.h"
#include	"qnmCustomStr_netMc.h"

 QY_DMITEM  CONST_dlg_aboutBox_isCliHelp[]  = 
{
	{	IDC_STATIC_ver,						(  TCHAR  *  )CONST_resId_ver,						},
	{	IDC_STATIC_qycxCopyRight,			(  TCHAR  *  )CONST_resId_qycxCopyRight,				},
	{	IDOK,														},
	{	-1,		},

};

 QY_DMITEM  CONST_dlg_cfgVideoConference_isCliHelp[]  =
{
	{	IDC_STATIC_conference_row,				},
	{	IDC_STATIC_conference_col,				},
	{	IDC_STATIC_usCntLimit_activeMems_from,	},
	{	IDC_STATIC_iWidth,						},
	{	IDC_STATIC_iHeight,						},
	{	IDC_CHECK_bUseAec,						},
	{	IDOK,									},
	{	IDCANCEL,								},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_cfgWmv_isCliHelp[]  =
 {
	 {	IDC_STATIC_encodingMode,	},
	 {	IDC_CBR,		},
	 {	IDC_QUALITY_VBR,	},
	 {	IDC_STATIC_VBRQUALITY,	},
	 {	IDC_STATIC_QUALITY,	},
	 {	IDC_STATIC_COMPLEXITY,	},
	 {	IDC_STATIC_PROFILES,		},
	 {	IDC_STATIC_FRAMERATE,		},
	 {	IDC_STATIC_BITRATE,			},
	 {	IDC_STATIC_BUFFERDELAY,		},
	 {	IDC_STATIC_MAXKEYDISTANCE,	},
	 {	IDOK,			},
	 {	IDCANCEL,		},
	 {	-1,				},
 };
 QY_DMITEM  CONST_dlg_cleanupEventCond_isCliHelp[]  = 
{
	{	IDC_STATIC_condition,							},
	{	IDC_STATIC_startTime,							},
	{	IDC_STATIC_endTime,								},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_desktopsMon_isCliHelp[]  =
{
	{	IDC_STATIC30,		},
	{	IDC_STATIC31,		},
	{	IDC_STATIC32,		},
	{	IDC_STATIC33,		},
	{	IDC_STATIC34,		},
	{	IDC_STATIC35,		},
	{	IDC_STATIC36,		},
	{	IDC_STATIC37,		},
	{	IDC_STATIC38,		},
	{	IDC_STATIC39,		},
	{	IDC_STATIC40,		},
	{	IDC_STATIC41,		},
	{	IDC_STATIC42,		},
	{	IDC_STATIC43,		},
	{	IDC_STATIC44,		},
	{	IDC_STATIC45,		},
	{	IDOK,		},
	{	IDCANCEL,		},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_imMsgSearch_isCliHelp[]  =
{
	{	IDC_STATIC_staticTalker,		},
	{	IDC_STATIC_staticId,			},
	{	IDC_STATIC_content,				},
	{	IDC_STATIC_startTime,			},
	{	IDC_STATIC_endTime,				},
	{	IDOK,							},
	{	IDCANCEL,						},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_imObjRule_isCliHelp[]  =
{
	{	IDC_STATIC_hint_imObjRule,					},
	{	IDC_CHECK_shareWebcamInConference,			},
	{	IDC_STATIC_conferenceId_shareWebcam,		},
	{	IDC_CHECK_noLocalVideoInThisConference,		},
	{	IDC_CHECK_distinguishSharedWebcams,			},

	{	IDC_STATIC_autoAnswer_av,					},
	{	IDC_STATIC_autoAnswer_screen,				},
	{	IDC_STATIC_autoAnswer_mediaFile,			},
	{	IDOK,										},
	{	IDCANCEL,									},
	{	-1,											},
};

 QY_DMITEM  CONST_IDD_instantAssistant_isCliHelp[]  =  
{
	{	IDC_BUTTON_msg,						},
	{	IDC_request,						},
	{	IDC_talkerList,						},
	//  {	IDC_COMBO_usLayoutType,				},
	{	IDC_BUTTON_layoutType,				},
	{	IDC_BUTTON_av,						},
	{	IDC_BUTTON_av_accept,				},
	{	IDC_BUTTON_av_deny,					},
	{	IDC_BUTTON_shareScreen,				},
	{	IDC_BUTTON_msgBox,					},
	{	IDC_BUTTON_fullScreen,				},			//  2013/02/12
	{	IDC_BUTTON_enlarge,					},
	{	IDC_BUTTON_close,					},
	{	IDC_BUTTON_more,					},
	{	IDC_BUTTON_rule,					},
	{	IDC_STATIC_status,					},
	{	IDC_BUTTON_nonexclusive,			},
	{	IDC_BUTTON_closeAndClean,			},
	{	IDC_BUTTON_subtitles,				},			//  2013/04/05
	{	IDC_BUTTON_remoteVideo,				},			//  2013/02/12
	{	IDC_BUTTON_ptzPanel,				},			//  2013/02/12
	{	-1,									},
};

 QY_DMITEM  CONST_dlg_instantAssistant_vw_isCliHelp[]  =  
{
	{	IDC_BUTTON_msg,						},
	{	IDC_request,						},
	{	IDC_talkerList,						},
	//  {	IDC_COMBO_usLayoutType,				},
	{	IDC_BUTTON_layoutType,				},
	{	IDC_BUTTON_av,						},
	{	IDC_BUTTON_av_accept,				},
	{	IDC_BUTTON_av_deny,					},
	{	IDC_BUTTON_shareScreen,				},
	{	IDC_BUTTON_msgBox,					},
	{	IDC_BUTTON_fullScreen,				},			//  2013/02/12
	{	IDC_BUTTON_enlarge,					},
	{	IDC_BUTTON_close,					},
	{	IDC_BUTTON_more,					},
	{	IDC_BUTTON_rule,					},
	{	IDC_STATIC_status,					},
	{	IDC_BUTTON_nonexclusive,			},
	{	IDC_BUTTON_closeAndClean,			},
	{	IDC_BUTTON_subtitles,				},			//  2013/04/05
	{	IDC_BUTTON_remoteVideo,				},			//  2013/02/12
	{	IDC_BUTTON_ptzPanel,				},			//  2013/02/12
	{	-1,									},
};

  QY_DMITEM  CONST_dlg_instantAssistant_start_ts_isCliHelp[]  =
{
	{	IDC_BUTTON_av,						},
	{	IDC_BUTTON_av_accept,				},
	{	IDC_BUTTON_av_deny,					},
	{	IDC_BUTTON_shareScreen,				},
	{	IDC_BUTTON_msgBox,					},
	{	IDC_BUTTON_enlarge,					},
	{	IDC_BUTTON_close,					},
	{	IDC_BUTTON_more,					},
	{	IDC_BUTTON_subtitles,				},		//  2013/04/05
	{	IDC_BUTTON_remoteVideo,				},		//  2013/02/15
	{	IDC_BUTTON_ptzPanel,				},		//  2013/02/15
	{	IDC_BUTTON_rule,					},
	{	IDC_BUTTON_msg,						},
	{	-1,									},
};

 QY_DMITEM	CONST_dlg_instantAssistant_av_ts_isCliHelp[]  =
{
	{	IDC_request,						},
	{	IDC_talkerList,						},
	//  {	IDC_COMBO_usLayoutType,				},
	{	IDC_BUTTON_layoutType,				},
	{	IDC_BUTTON_av,						},
	{	IDC_BUTTON_shareScreen,				},
	{	IDC_BUTTON_msgBox,					},
	{	IDC_BUTTON_enlarge,					},
	{	IDC_BUTTON_close,					},
	{	IDC_BUTTON_more,					},
	{	IDC_BUTTON_subtitles,				},		//  2013/04/05
	{	IDC_BUTTON_remoteVideo,				},
	{	IDC_BUTTON_ptzPanel,				},		//  2013/02/15
	{	IDC_BUTTON_rule,					},
	{	IDC_STATIC_status,					},
	{	IDC_BUTTON_msg,						},
	{	IDC_BUTTON_nonexclusive,			},
	{	IDC_BUTTON_shareMediaFile,			},
	{	-1,									},
};

 QY_DMITEM  CONST_dlg_mediaControl_isCliHelp[]  =
 {
	 //  {	IDC_BUTTON_PLAY,	},
	 {	IDC_BUTTON_STOP,	},
	 {	IDC_BUTTON_FRAMESTEP,	},
	 {	IDC_CHECK_PLAYTHROUGH,							},
	 {	IDC_CHECK_LOOP,									},
	 {	IDC_CHECK_MUTE,									},

	 {	-1,				},
 };

 QY_DMITEM  CONST_dlg_menu_isCli_wallsbar_isCliHelp[]  =
{
	{	IDC_BUTTON_contact,				},
	{	IDC_BUTTON_group,				},
	{	IDC_BUTTON_fullScreen,			},
	{	IDC_BUTTON_testLocalAv,			},
	{	IDC_BUTTON_msg,					},
	{	IDC_BUTTON_policy,				},
	{	IDC_BUTTON_conferenceQuality,	},
	{	IDC_BUTTON_quit,				},
	{	IDC_BUTTON_about,				},
	{	IDCANCEL,						},
	{	-1,								},
};

 QY_DMITEM  CONST_dlg_messageBox[]  =
{
	{	IDOK,					},
	{	IDC_BUTTON_no,			},
	{	IDCANCEL,				},
	{	-1,				},
};

 QY_DMITEM	CONST_dlg_messengerIsClient_isCliHelp[]	=
{
	{	IDC_STATIC_hint1,		 },
	{	IDC_STATIC_messengerName,},   //  IDC_STATIC_staticName
	{	IDC_STATIC_passwd0,		},
	{	IDC_STATIC_passwd1,		},
	{	IDOK,					 },
	{	IDCANCEL,				 },
	{	-1,				},
};


 QY_DMITEM  CONST_dlg_msgList_isCliHelp[]  =
{
	{	IDC_BUTTON_export,		},
	{	IDC_BUTTON_clear,		},
	{	IDCANCEL,				},
	{	-1,						},

};

 QY_DMITEM  CONST_dlg_objs_isCliHelp[]  =
{
	{	IDOK,					},
	{	IDCANCEL,				},
	{	-1,				},
};


 QY_DMITEM  CONST_dlg_policy_isCliHelp[]  =
{
	{	IDC_CHECK_ucbUseGlobalVWall,				},			//  2012/04/02
	//
	{	IDC_STATIC_staticRuleIfMsgArrive,			},
	{	IDC_STATIC_staticDirToSaveFile,				},
	{	IDC_BUTTON_browseDir,						},
#if  0
	{	IDC_CHECK_ucbOnlyNetSm,						},
	{	IDC_CHECK_ucbOnlyPhoneMsgr,					},
	{	IDC_STATIC_baud,							},
	{	IDC_CHECK_ucbPermitOtherSm,					},
#endif
	{	IDC_BUTTON_ptzSettings,						},
	//
	{	IDC_CHECK_showMsgBox,				},
	{	IDC_CHECK_showNotification,			},
	//
	{	IDC_CHECK_ucbPreferCuda,					},					//  2012/06/25
	{	IDC_CHECK_ucbLooping_mediaFile,				},					//  2012/11/06

	
	{	IDC_STATIC_usTimeoutInMsToSwitch,			},
	{	IDC_STATIC_usTimeoutInMsToSwitch_rt,		},
	{	IDC_STATIC_iTimeoutInMs_channelIdle,		},
	{	IDC_STATIC_usMax_nPlayers,					},			//  2012/03/30
	{	IDC_STATIC_usMax_nThreads_dec,				},			//  2012/03/30
	{	IDC_STATIC_uiMaxQNodes_vwRuleQ,				},			//  2012/03/30

#if  0
	{	IDC_CHECK_shareWebcamInConference,			},
	{	IDC_STATIC_conferenceId_shareWebcam,		},
	{	IDC_CHECK_noLocalVideoInConference,			},
	{	IDC_CHECK_distinguishSharedWebcams,			},
#endif

	{	IDC_CHECK_ucbManullyPermitToSpeakOnVideoConference,	},
	{	IDC_BUTTON_videoConferenceCfg,						},
	//
	{	IDC_CHECK_ucbScrollForEnlagedImg,					},

	{	IDC_BUTTON_avCompressor_req,						},	
	{	IDC_BUTTON_avCompressor_reply,						},	
	{	IDC_BUTTON_screenCompressor,						},	
	{	IDC_BUTTON_mediaFileCompressor,						},
	{	IDC_BUTTON_mediaDeviceCompressor,					},
	{	IDC_BUTTON_webcamCompressor,						},



	{	IDC_BUTTON_restoreDefaultSettings,						},
	{	IDOK,													},
	{	IDCANCEL,												},
	{	-1,		},
};


 QY_DMITEM  CONST_dlg_policyAv_isCliHelp[]  =  
{

	{	IDC_STATIC_req,											},
	{	IDC_STATIC_reply,										},

	{	IDC_BUTTON_setLdSettings,							},
	{	IDC_BUTTON_setLd1Settings,							},			//  2012/03/16
	{	IDC_BUTTON_setSdSettings,							},
	{	IDC_BUTTON_setSd1Settings,							},
	{	IDC_BUTTON_setSd2Settings,							},			//  2012/03/16
	{	IDC_BUTTON_setSd3Settings,							},			//  2012/03/16
	{	IDC_BUTTON_setHdSettings,							},
	{	IDC_BUTTON_setHd1Settings,							},
	{	IDC_BUTTON_setHd2Settings,							},
	{	IDC_BUTTON_setHd3Settings,							},
	{	IDC_BUTTON_setFullHdSettings,							},
	{	IDC_BUTTON_setFullHd1Settings,							},
	{	IDC_BUTTON_setFullHd2Settings,							},
	{	IDC_BUTTON_setFullHd3Settings,							},
	{	IDC_BUTTON_setDev2fpsSettings,							},
	{	IDC_BUTTON_setDev5fpsSettings,							},
	{	IDC_BUTTON_setDev5fpsSettings1,							},
	{	IDC_BUTTON_setDev5fpsSettings2,							},
	{	IDC_BUTTON_setDev5fpsSettings3,							},
	{	IDC_BUTTON_setDev5fpsSettings4,							},			//  2013/04/13
	{	IDC_BUTTON_setDev5fpsSettings5,							},
	{	IDC_BUTTON_setDev10fpsSettings,							},			//  2012/11/03
	{	IDC_BUTTON_setDevSd24fpsSettings,						},			//  2012/11/03
	{	IDC_BUTTON_setDevSd25fpsSettings,						},			//  2012/11/03
	{	IDC_BUTTON_setDevSd30fpsSettings,						},			//  2012/11/03
	{	IDC_BUTTON_setDev24fpsSettings,							},
	{	IDC_BUTTON_setDev25fpsSettings,							},
	{	IDC_BUTTON_setDev30fpsSettings,							},

	{	IDOK,													},
	{	IDCANCEL,												},
	{	-1,		},

};

 QY_DMITEM  CONST_dlg_progress_isCliHelp[]  =
{
	{	IDC_STATIC_progress,	},
	{	IDOK,					},
	{	IDCANCEL,				},
	{	-1,				},
};

  QY_DMITEM  CONST_dlg_imGrpProperties_isCliHelp[]  =
{
	{	IDC_STATIC_staticName,							},
	{	IDC_STATIC_staticMessengerId,							},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},

};

 QY_DMITEM  CONST_dlg_imMsgProperties_isCliHelp[]  =
{
	{	IDC_STATIC_staticType,								},
	{	IDC_STATIC_staticSender,	},
	{	IDC_STATIC_staticReceiver,	},
	{	IDC_STATIC_staticSendTime,	},
	{	IDC_STATIC_staticRecvTime,	},
	{	IDC_STATIC_staticContent,	},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_imTaskProperties_isCliHelp[]  =
{
	{	IDC_STATIC_staticType,								},
	{	IDC_STATIC_staticImTaskStatus,						},
	{	IDC_STATIC_staticSender,	},
	{	IDC_STATIC_staticReceiver,	},
	{	IDC_STATIC_staticSendTime,	},
	{	IDC_STATIC_staticRecvTime,	},
	{	IDC_STATIC_staticSubject,	},
	{	IDC_STATIC_staticContent,	},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};

 //  2007/07/30
 QY_DMITEM  CONST_dlg_messengerProperties_isCliHelp[]  =
{

	{	IDC_pc0_zongBu,		(  TCHAR  *  )CONST_resId_pc0_zongBu,		},
	{	IDC_pc2_benBu,		(  TCHAR  *  )CONST_resId_pc2_benBu,		},
	{	IDC_pc4_danWei,		(  TCHAR  *  )CONST_resId_pc4_danWei,		},
	{	IDC_pc6_qiTaDanWei,		(  TCHAR  *  )CONST_resId_pc6_qiTaDanWei,		},
	{	IDC_pc8_buMen,		(  TCHAR  *  )CONST_resId_pc8_buMen,		},
	{	IDC_pc10_shiYongRen,		(  TCHAR  *  )CONST_resId_pc10_shiYongRen,		},
	{	IDC_pc12_jiQiLeiXing,		(  TCHAR  *  )CONST_resId_pc12_jiQiLeiXing,		},
	{	IDC_pc14_ziChanBianHao,		(  TCHAR  *  )CONST_resId_pc14_ziChanBianHao,		},
	{	IDC_pc16_zhuYaoYongTu,		(  TCHAR  *  )CONST_resId_pc16_zhuYaoYongTu,		},
	{	IDC_pc18_lianXiDianHua,		(  TCHAR  *  )CONST_resId_pc18_lianXiDianHua,		},
	{	IDC_pc20_shiYongDiDian,		(  TCHAR  *  )CONST_resId_pc20_shiYongDiDian,		},
	{	IDC_pc22_shiYongDiDian,		(  TCHAR  *  )CONST_resId_pc22_shiYongDiDian,		},
	{	IDC_pc24_ziChanBianHao1,		(  TCHAR  *  )CONST_resId_pc24_ziChanBianHao1,		},
	{	IDC_pc26_ziChanShuoMing1,		(  TCHAR  *  )CONST_resId_pc26_ziChanShuoMing1,		},
	{	IDC_pc28_ziChanBianHao2,		(  TCHAR  *  )CONST_resId_pc28_ziChanBianHao2,		},
	{	IDC_pc30_ziChanShuoMing2,		(  TCHAR  *  )CONST_resId_pc30_ziChanShuoMing2,		},
	//	 
	{	IDC_STATIC_staticMessengerId,	},
	//  {	IDC_STATIC_usrInfoZone,				(  TCHAR  *  )CONST_resId_STATIC_usrInfoZone,		},
	//  {	IDC_STATIC_pcName,					(  TCHAR  *  )CONST_resId_STATIC_pcName,		},
	//  {	IDC_STATIC_ip,						(  TCHAR  *  )CONST_resId_STATIC_ip,		},
	//  {	IDC_STATIC_osName,					(  TCHAR  *  )CONST_resId_STATIC_osName,		},
	//  {	IDC_STATIC_servicePack,				(  TCHAR  *  )CONST_resId_STATIC_servicePack,		},
	//  {	IDC_STATIC_mac0,					(  TCHAR  *  )CONST_resId_STATIC_mac0,		},
	//  {	IDC_STATIC_mac1,					(  TCHAR  *  )CONST_resId_STATIC_mac1,		},
	//  {	IDC_STATIC_mac2,					(  TCHAR  *  )CONST_resId_STATIC_mac2,		},
	//  {	IDC_STATIC_ip0,						(  TCHAR  *  )CONST_resId_STATIC_ip0,		},
	//  {	IDC_STATIC_ip1,						(  TCHAR  *  )CONST_resId_STATIC_ip1,		},
	//  {	IDC_STATIC_ip2,						(  TCHAR  *  )CONST_resId_STATIC_ip2,		},
	//
	//  {	IDC_STATIC_qwmVer,					(  TCHAR  *  )CONST_resId_STATIC_qwmVer,		},
	//  {	IDC_STATIC_regTime,					(  TCHAR  *  )CONST_resId_STATIC_regTime,		},
	//  {	IDC_STATIC_auditTime,				(  TCHAR  *  )CONST_resId_STATIC_auditTime,		},
	//  {	IDC_STATIC_startTime,				(  TCHAR  *  )CONST_resId_STATIC_clientStartTime,		},
	//  {	IDC_STATIC_lastCommTime,			(  TCHAR  *  )CONST_resId_STATIC_lastCommTime,		},
	//
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};


QY_DMITEM  CONST_dlg_ptzControl_isCliHelp[]  =
{
	{	IDC_BUTTON_ptzSettings,	},
	{	IDC_STATIC_speed,		},

	{	IDC_BUTTON_UP,			},	
	{	IDC_BUTTON_DOWN,		},	
	{	IDC_BUTTON_LEFT,		},	
	{	IDC_BUTTON_RIGHT,		},	
	{	IDC_BUTTON_TOP_LEFT,	},	
	{	IDC_BUTTON_TOP_RIGHT,	},	
	{	IDC_BUTTON_BOTTOM_LEFT,	},	
	{	IDC_BUTTON_BOTTOM_RIGHT,},	
	{	IDC_BUTTON_noop,		},
	{	IDC_BUTTON_FOCUS_IN,	},	
	{	IDC_STATIC_focus,		},	
	{	IDC_BUTTON_FOCUS_OUT,	},	
	{	IDC_BUTTON_IRIS_IN,		},	
	{	IDC_STATIC_iris,		},	
	{	IDC_BUTTON_IRIS_OUT,	},	
	{	IDC_BUTTON_ZOOM_IN,		},	
	{	IDC_STATIC_zoom,		},	
	{	IDC_BUTTON_ZOOM_OUT,	},	

	{	IDC_STATIC_preset,		},
	{	IDC_BUTTON_PRE_GO,		},
	{	IDC_BUTTON_PRE_SET,		},
	{	IDC_BUTTON_PRE_CLEAR,	},
	{	IDCANCEL,				},

	{	-1,						},
};

QY_DMITEM  CONST_dlg_ptzSettings_isCliHelp[]  =
{
	{	IDC_STATIC_comPtz,		},
	{	IDC_STATIC_comName,		},
	{	IDC_STATIC_comBaud,		},
	{	IDC_STATIC_comParity,	},
	{	IDC_STATIC_comData,		},
	{	IDC_STATIC_comStopBit,	},
	{	IDC_STATIC_ptzProtocal,	},
	{	IDC_STATIC_ptzAddr,		},
	{	IDC_STATIC_remotePtz,	},
	{	IDC_STATIC_remoter,		},
	{	IDC_STATIC_memoAppending,	},
	{	IDC_EDIT_memoAppending,	},

	{	IDOK,					},
	{	IDCANCEL,				},

	{	-1,						},
};

 QY_DMITEM  CONST_dlg_qnmClearup_isCliHelp[]  = 
{
	{	IDC_STATIC_clearHint, 				(  TCHAR  *  )CONST_resId_STATIC_clearHint,		},
	{	IDC_RADIO_clearupEvent, 	 		(  TCHAR  *  )CONST_resId_RADIO_clearupEvent,		},
	{	IDC_RADIO_procModuleKnowlege,	},
	{	IDC_RADIO_procImMsg,				},
	{	IDC_RADIO_procImHisTask,				},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_qnmEditPcUsrInfo_isCliHelp[]  =
{
	{	IDC_hint0,							(  TCHAR  *  )CONST_resId_hint0,				},
	{	IDC_hint1,							(  TCHAR  *  )CONST_resId_hint1,				},
	{	-1,		},
};

  QY_DMITEM  CONST_dlg_qnmSearch_isCliHelp[]  = 
{
	{	IDC_STATIC_queryType,				(  TCHAR  *  )CONST_resId_STATIC_queryType,			},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};


 QY_DMITEM  CONST_dlg_bar_isCliHelp[]  =
{
	{	IDC_BUTTON_menu,				},
	{	-1,								},
};

 QY_DMITEM  CONST_dlg_selectDsn_isCliHelp[]  =
{
	{	IDOK,							},
	{	IDCANCEL,						},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_selectAvDev_isCliHelp[]  =  
 {
	 {  IDC_STATIC_aDev,  },
	 {  IDC_STATIC_vDev,  },
	 {  IDC_BUTTON_cfgCaptureFilter_v,  },
	 {  IDC_BUTTON_cfgCapturePin_v,  },
	 {	IDC_BUTTON_cfgCrossBar_v,  },				
	 {	IDOK,			},
	 {	IDCANCEL,		},
	 {	-1,				},
 };
 QY_DMITEM  CONST_dlg_shareDynBmps_isCliHelp[]  =
{
	{	IDC_STATIC00,	},
	{	IDC_STATIC01,	},
	{	IDC_STATIC02,	},
	{	IDC_STATIC_sharingScreen0,	},
	{	IDC_STATIC_sharingScreen1,	},
	{	IDC_STATIC_sharingScreen2,	},
	{	IDC_STATIC10,	},
	{	IDC_STATIC11,	},
	{	IDC_STATIC12,	},
	{	IDC_STATIC_webcam0,	},
	{	IDC_STATIC_webcam1,	},
	{	IDC_STATIC_webcam2,	},
	{	IDC_STATIC_pic0,	},
	//
	{	IDC_STATIC_gps,		},
	{	IDC_STATIC_gpsStatus,		},
	{	IDC_BUTTON_gps,		},
	//
	{	IDC_CHECK_shareBmp,	},
	//
	{	IDOK,			},
	{	IDCANCEL,		},
	{	-1,				},
};

QY_DMITEM  CONST_dlg_subtitle_select_isCliHelp[]  = 
{

	{	IDC_BUTTON_selectFont,					},
	{	IDC_CHECK_displayTime,					},
	{	IDC_CHECK_bottomUp,					},

	{	IDC_STATIC_staticMaskColor,				},	
	{	IDC_STATIC_xyStart,						},

	{	IDC_CHECK_3dShadow,					},
	{	IDC_STATIC_shadowOffset,			},

	{	IDOK,					},
	{	IDCANCEL,				},

	{	-1,						},

};

 QY_DMITEM  CONST_dlg_talk_isCliHelp[]  =
{
	{	IDC_STATIC_instantStatus,	},
	{	IDC_STATIC_peerDesc,		},
	{	IDCANCEL,		},
	{	-1,		},
};

  QY_DMITEM  CONST_dlg_test_isCliHelp[]  =
 {
	 {	IDC_BUTTON_aDev,		},
	 {	IDC_BUTTON_vDev,		},
	 {  IDC_BUTTON_cfgCapturePin_v,  },
	 {	IDC_BUTTON_testAv,	},
	 {	IDCANCEL,			},
	 {	-1,					},
 };


 QY_DMITEM  CONST_dlg_videoCompressors_isCliHelp[]  =
{

	{	IDC_STATIC_audio,									},
	{	IDC_STATIC_defaultFmt,								},
	{	IDC_STATIC_uiBytesRecorded_perBlockAlign,			},
	{	IDC_STATIC_audioCompressor,							},
	{	IDC_STATIC_audioOutputType,							},

	{	IDC_STATIC_audioPlayCfg,							},
	{	IDC_STATIC_uiMinTimeInMsOfAudioDataPlaying,			},				//  2009/06/14
	{	IDC_STATIC_uiAudioDataAddedToPlayEveryTime,			},				//  2009/06/14
	{	IDC_STATIC_uiNotifyIntervalInMs_needMoreAudioData,	},				//  2009/06/14. = CONST_notifyInterval
	{	IDC_STATIC_uiMinTimeInMsToPlay,						},				//  2012/01/27
	{	IDC_STATIC_uiMaxTimeInMsToPlay,						},
	{	IDC_STATIC_uiMaxTimeInMsToBeRemoved,				},

	{	IDC_STATIC_video,									},
	{	IDC_STATIC_videoCompressor,							},
	{	IDC_STATIC_videoOutputType,							},
	{	IDC_STATIC_videoEffect,								},				//  2012/02/08
	{	IDC_STATIC_avgBitrate,								},				//  2012/06/27

	{	IDC_STATIC_ucSeconds_perFrame,						},
	{	IDC_STATIC_usMaxFPS_toShareBmp,						},
	{	IDC_STATIC_usMinFps_toShareBmp,						},
	{	IDC_STATIC_iWidth,									},
	{	IDC_STATIC_iHeight,									},


	{	IDC_BUTTON_cfgWmv,							},

	{	IDOK,									},
	{	IDCANCEL,								},
	{	-1,			},
};

QY_DMITEM  CONST_dlg_videoSubtitlesCfg_isCliHelp[]  =
{

	{	IDC_CHECK_showVideoHint,				},
	{	IDC_CHECK_effectiveImmediately,			},

	{	IDC_BUTTON_useDefault,					},
	{	IDC_BUTTON_file,						},
	{	IDC_BUTTON_subtitlesSettings,			},

	{	IDC_STATIC_subtitle0,					},
	{	IDC_EDIT_subtitle0,						},

	{	IDC_EDIT_subtitle1,						},
	{	IDC_STATIC_subtitle1,					},

	{	IDC_EDIT_subtitle2,						},
	{	IDC_STATIC_subtitle2,					},

	{	IDC_EDIT_subtitle3,						},
	{	IDC_STATIC_subtitle3,					},

	{	IDC_EDIT_subtitle4,						},
	{	IDC_STATIC_subtitle4,					},

	{	IDC_EDIT_subtitle5,						},
	{	IDC_STATIC_subtitle5,					},

	{	IDC_EDIT_subtitle6,						},
	{	IDC_STATIC_subtitle6,					},

	{	IDC_EDIT_subtitle7,						},
	{	IDC_STATIC_subtitle7,					},

	{	IDC_EDIT_subtitle8,						},
	{	IDC_STATIC_subtitle8,					},
	
	{	IDC_EDIT_subtitle9,						},
	{	IDC_STATIC_subtitle9,					},
	
	{	IDC_EDIT_subtitle10,					},							
	{	IDC_STATIC_subtitle10,					},

	{	IDC_EDIT_subtitle11,					},
	{	IDC_STATIC_subtitle11,					},

	{	IDOK,									},
	{	IDC_BUTTON_emptyTxt,					},
	{	IDCANCEL,								},

	{	-1,						},
};




 QY_DMITEM  CONST_dlgTable_isCliHelp[]  =
{
	{	IDD_ABOUTBOX,						(  TCHAR  *  )CONST_dlg_aboutBox_isCliHelp,					(  TCHAR  *  )CONST_resId_IDD_ABOUTBOX,					},

	{	IDD_cfgVideoConference,				(  TCHAR  *  )CONST_dlg_cfgVideoConference_isCliHelp,				},
	{	IDD_cfgWmv,							(  TCHAR  *  )CONST_dlg_cfgWmv_isCliHelp,							},
	{	IDD_clearupEventCond,				(  TCHAR  *  )CONST_dlg_cleanupEventCond_isCliHelp,			(  TCHAR  *  )CONST_resId_IDD_clearupEventCond,			},
	{	IDD_desktopsMon,					(  TCHAR  *  )CONST_dlg_desktopsMon_isCliHelp,						},
	{	IDD_imMsgSearch,					(  TCHAR  *  )CONST_dlg_imMsgSearch_isCliHelp,					},
	{	IDD_imObjRule,						(  TCHAR  *  )CONST_dlg_imObjRule_isCliHelp,						},
	{	IDD_instantAssistant,				(  TCHAR  *  )CONST_IDD_instantAssistant_isCliHelp,					},
	{	IDD_instantAssistant_vw,			(  TCHAR  *  )CONST_dlg_instantAssistant_vw_isCliHelp,				},
	{	IDD_instantAssistant_av,			(  TCHAR  *  )CONST_dlg_instantAssistant_av_ts_isCliHelp,			},
	{	IDD_instantAssistant_av_min,		(  TCHAR  *  )CONST_dlg_instantAssistant_av_ts_isCliHelp,			},
	{	IDD_instantAssistant_start,			(  TCHAR  *  )CONST_dlg_instantAssistant_start_ts_isCliHelp,		},
	{	IDD_instantAssistant_start_min,		(  TCHAR  *  )CONST_dlg_instantAssistant_start_ts_isCliHelp,		},
	{	IDD_instantAssistant_start_wait,	(  TCHAR  *  )CONST_dlg_instantAssistant_start_ts_isCliHelp,		},
	{	IDD_instantAssistant_start_wait_min,(  TCHAR  *  )CONST_dlg_instantAssistant_start_ts_isCliHelp,		},

	{	IDD_mediaControl,					(  TCHAR  *  )CONST_dlg_mediaControl_isCliHelp,			},
	{	IDD_menu_isCli_walls,				(  TCHAR  *  )CONST_dlg_menu_isCli_wallsbar_isCliHelp,	},
	{	IDD_messageBox,						(  TCHAR  *  )CONST_dlg_messageBox,						},
	{	IDD_messenger_isClient,				(  TCHAR  *  )CONST_dlg_messengerIsClient_isCliHelp,	},
	{	IDD_msgList,						(  TCHAR  *  )CONST_dlg_msgList_isCliHelp,				},
	{	IDD_objs,							(  TCHAR  *  )CONST_dlg_objs_isCliHelp,					},
	{	IDD_policy_isClient,				(  TCHAR  *  )CONST_dlg_policy_isCliHelp,				},
	{	IDD_policyAv,						(  TCHAR  *  )CONST_dlg_policyAv_isCliHelp,				},
	{	IDD_progress,						(  TCHAR  *  )CONST_dlg_progress_isCliHelp,				},
	{	IDD_prop_imGrp,						(  TCHAR  *  )CONST_dlg_imGrpProperties_isCliHelp,		},
	{	IDD_prop_imMsg,						(  TCHAR  *  )CONST_dlg_imMsgProperties_isCliHelp,		},
	{	IDD_prop_imTask,					(  TCHAR  *  )CONST_dlg_imTaskProperties_isCliHelp,		},
	{	IDD_prop_messenger,					(  TCHAR  *  )CONST_dlg_messengerProperties_isCliHelp,	},
	{	IDD_ptzControl,						(  TCHAR  *  )CONST_dlg_ptzControl_isCliHelp,			},
	{	IDD_ptzSettings,					(  TCHAR  *  )CONST_dlg_ptzSettings_isCliHelp,			},
	{	IDD_qnmClearup,						(  TCHAR  *  )CONST_dlg_qnmClearup_isCliHelp,					(  TCHAR  *  )CONST_resId_IDD_qnmClearup,				},
	{	IDD_qnmEditPcUsrInfo ,				(  TCHAR  *  )CONST_dlg_qnmEditPcUsrInfo_isCliHelp,			(  TCHAR  *  )CONST_resId_IDD_qnmEditPcUsrInfo,			},
	{	IDD_qnmSearch,						(  TCHAR  *  )CONST_dlg_qnmSearch_isCliHelp,					(  TCHAR  *  )CONST_resId_IDD_qnmSearch,				    },
	{	IDD_qyBar,							(  TCHAR  *  )CONST_dlg_bar_isCliHelp,					},
	{	IDD_select_isCli,					(  TCHAR  *  )CONST_dlg_selectDsn_isCliHelp,			},
	{	IDD_selectAvDev,					(  TCHAR  *  )CONST_dlg_selectAvDev_isCliHelp,			},
	{	IDD_shareDynBmps,					(  TCHAR  *  )CONST_dlg_shareDynBmps_isCliHelp,			},
	{	IDD_subtitle_select,				(  TCHAR  *  )CONST_dlg_subtitle_select_isCliHelp,		},
	{	IDD_talk,							(  TCHAR  *  )CONST_dlg_talk_isCliHelp,					},
	{	IDD_test_isCli,						(  TCHAR  *  )CONST_dlg_test_isCliHelp,					},
	{	IDD_videoCompressors,				(  TCHAR  *  )CONST_dlg_videoCompressors_isCliHelp,		},
	{	IDD_videoTagCfg,					(  TCHAR  *  )CONST_dlg_videoSubtitlesCfg_isCliHelp,				},




	{	-1,		},
};

