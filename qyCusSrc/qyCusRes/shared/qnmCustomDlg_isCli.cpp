
#include	"stdafx.h"
#include	<tchar.h>
//  #include	"qyCommon.h"
#include	"myresource_main_isCli.h"
#include	"afxres.h"

#include	"qyCusResCommon.h"
#include	"qyCusResTemp.h"

#include	"qnmCustomStr_common.h"
#include	"qnmCustomStr_netMc.h"

#ifndef  __WINCE__




 QY_DMITEM  CONST_dlg_cfgCustom_isCli[]  =
{
	{	IDC_STATIC_nDwLevels,				(  TCHAR  *  )CONST_resId_STATIC_nDwLevels,	},
	{	IDC_STATIC_nZcbhs,					(  TCHAR  *  )CONST_resId_STATIC_nZcbhs,		},
	{	IDC_STATIC_qrtTitle,				(  TCHAR  *  )CONST_resId_STATIC_qrtTitle,	},
	{	IDC_STATIC_hint,					(  TCHAR  *  )CONST_resId_STATIC_hint,		},
	{	IDOK,												},
	{	IDCANCEL,										},
	{	-1,			},
};

 
 QY_DMITEM  CONST_dlg_cfgStandardName_isCli[]  =
{
	{	IDC_STATIC_hint_cfgStandardName,		},
	{	IDC_STATIC_preStandardName,									},
	{	IDC_STATIC_standardName,									},
	{	IDC_CHECK_zb,										},
	{	IDC_CHECK_bb,											},
	{	IDC_CHECK_dw,											},
	{	IDC_CHECK_bm,											},
	{	IDC_CHECK_syr,									},
	{	IDOK,												},
	{	IDCANCEL,										},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_cfgStandardNames_isCli[]  =
{
	{	IDC_ADD,													},
	{	IDC_MODIFY,												},
	{	IDC_DEL,													},
	{	IDC_BUTTON_cfgStandardNames,									},
	{	-1,		},
};
 


#endif

#ifndef  __WINCE__

 QY_DMITEM  CONST_dlg_exportClients_isCli[] =
{
	{	IDC_RADIO_default,	},
	{	IDC_RADIO_ts_logon,	},
	{	IDC_RADIO_ts_dev,	},
	{	-1,			},

};
#endif

  QY_DMITEM  CONST_dlg_qnmCfgOptions_isCli[]  =
{
	{	IDC_STATIC_cntName,		},
	{	IDC_STATIC_centerAddr,				(  TCHAR  *  )CONST_resId_STATIC_centerIp,		},
	{	IDC_STATIC_cntAddr0,	},
	{	IDC_STATIC_cntAddr1,	},
	{	IDC_STATIC_cntAddr2,	},
	{	IDC_STATIC_cntPort,		},
	{	IDC_CHECK_useDb,		},
	{	IDC_ADD,				},
	{	IDC_MODIFY,				},
	{	IDC_DEL,				},
	{	IDOK,													},
	{	IDCANCEL,											},
	{	-1,			},
};



#ifndef  __WINCE__

 QY_DMITEM  CONST_dlg_qnmEditPcUsrInfo_isCli[]  =
{
	{	IDC_hint0,							(  TCHAR  *  )CONST_resId_hint0,				},
	{	IDC_hint1,							(  TCHAR  *  )CONST_resId_hint1,				},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_aboutBox_isCli[]  = 
{
	{	IDC_STATIC_ver,						(  TCHAR  *  )CONST_resId_ver,						},
	{	IDC_STATIC_qycxCopyRight,			(  TCHAR  *  )CONST_resId_qycxCopyRight,				},
	{	IDOK,														},
	{	-1,		},

};

 QY_DMITEM  CONST_dlg_cfgUsr_isCli[]  = 
{
	{	IDC_STATIC_name,					(  TCHAR  *  )CONST_resId_name,						},
	{	IDC_STATIC_passwd0,								},
	{	IDC_STATIC_passwd1,								},
	{	IDC_STATIC_scope,					},
	{	IDC_STATIC_zb,						},
	{	IDC_STATIC_bb,						},
	{	IDC_STATIC_dw,						},
	{	IDC_STATIC_bm,						},	
	{	IDOK,																					},
	{	IDCANCEL,												},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_cfgUsrs_isCli[]  = 
{
	{	IDC_STATIC_minPasswdLen,			},
	{	IDC_STATIC_maxInvalidLogonAttempts,			},
	{	IDC_HINT,							(  TCHAR  *  )CONST_resId_HINT,						},
	{	IDC_ADD,							(  TCHAR  *  )CONST_resId_ADD,						},
	{	IDC_MODIFY,							(  TCHAR  *  )CONST_resId_MODIFY,					},
	{	IDC_DEL,							(  TCHAR  *  )CONST_resId_DEL,						},
	{	IDOK,		},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_cfgWarn_isCli[]  = 
{
	{	IDC_WARNON,							(  TCHAR  *  )CONST_resId_WARNON,					},
	{	IDC_STATIC_cfgWarn,					(  TCHAR  *  )CONST_resId_STATIC_cfgWarn,			},
	{	IDC_WARNUNTILUSRSTOPIT,				(  TCHAR  *  )CONST_resId_WARNUNTILUSRSTOPIT,		},
	{	IDC_STATIC_maxWarnElapse,			(  TCHAR  *  )CONST_resId_STATIC_maxWarnElapse,		},
	{	IDC_CHECK_popupToWarn,				},
	{	IDC_STATIC_popupToWarnStartTime,	},
	{	IDC_STATIC_popupToWarnStartTimeVal,	},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_cleanupEventCond_isCli[]  = 
{
	{	IDC_STATIC_condition,							},
	{	IDC_STATIC_startTime,							},
	{	IDC_STATIC_endTime,								},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};



 QY_DMITEM  CONST_dlg_qnmCfgPcGrp_isCli[]  = 
{
	{	IDC_STATIC_qiShiIP,					(  TCHAR  *  )CONST_resId_STATIC_qiShiIP,		},
	{	IDC_STATIC_jieShuIP,				(  TCHAR  *  )CONST_resId_STATIC_jieShuIP,		},
	{	IDC_STATIC_danWei,					(  TCHAR  *  )CONST_resId_STATIC_danWei,		},
	{	IDC_STATIC_buMen,					(  TCHAR  *  )CONST_resId_STATIC_buMen,		},
	{	IDC_STATIC_scanedObj,				(  TCHAR  *  )CONST_resId_STATIC_scanedObj,		},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_pcProperties_isCli[]  =
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
	{	IDC_STATIC_usrInfoZone,				(  TCHAR  *  )CONST_resId_STATIC_usrInfoZone,		},
	{	IDC_STATIC_pcName,					(  TCHAR  *  )CONST_resId_STATIC_pcName,		},
	{	IDC_STATIC_ip,						(  TCHAR  *  )CONST_resId_STATIC_ip,		},
	{	IDC_STATIC_osName,					(  TCHAR  *  )CONST_resId_STATIC_osName,		},
	{	IDC_STATIC_servicePack,				(  TCHAR  *  )CONST_resId_STATIC_servicePack,		},
	{	IDC_STATIC_mac0,					(  TCHAR  *  )CONST_resId_STATIC_mac0,		},
	{	IDC_STATIC_mac1,					(  TCHAR  *  )CONST_resId_STATIC_mac1,		},
	{	IDC_STATIC_mac2,					(  TCHAR  *  )CONST_resId_STATIC_mac2,		},
	{	IDC_STATIC_ip0,						(  TCHAR  *  )CONST_resId_STATIC_ip0,		},
	{	IDC_STATIC_ip1,						(  TCHAR  *  )CONST_resId_STATIC_ip1,		},
	{	IDC_STATIC_ip2,						(  TCHAR  *  )CONST_resId_STATIC_ip2,		},
	//
	{	IDC_STATIC_qwmVer,					(  TCHAR  *  )CONST_resId_STATIC_qwmVer,		},
	{	IDC_STATIC_regTime,					(  TCHAR  *  )CONST_resId_STATIC_regTime,		},
	{	IDC_STATIC_auditTime,				(  TCHAR  *  )CONST_resId_STATIC_auditTime,		},
	{	IDC_STATIC_startTime,				(  TCHAR  *  )CONST_resId_STATIC_clientStartTime,		},
	{	IDC_STATIC_lastCommTime,			(  TCHAR  *  )CONST_resId_STATIC_lastCommTime,		},
	//
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};



 //  2007/07/30
 QY_DMITEM  CONST_dlg_messengerProperties_isCli[]  =
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

 
  QY_DMITEM  CONST_dlg_imGrpProperties_isCli[]  =
{
	{	IDC_STATIC_staticName,							},
	{	IDC_STATIC_staticMessengerId,							},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},

};


 QY_DMITEM  CONST_dlg_imGrp_isCli[]  =
{
	{	IDC_STATIC_staticName,							},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},

};

 QY_DMITEM  CONST_dlg_cfgCustomerService_isCli[]  =
{
	{	IDC_STATIC_lang,	},
	{	IDC_STATIC_category,	},
	{	IDC_STATIC_startIp,	},
	{	IDC_STATIC_endIp,	},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};

   #endif

 QY_DMITEM  CONST_dlg_policy_isCli[]  =
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

	{	IDC_STATIC_avCompressor_req,						},
	{	IDC_BUTTON_avCompressor_req,						},	
	{	IDC_STATIC_avCompressor_reply,						},
	{	IDC_BUTTON_avCompressor_reply,						},	
	{	IDC_STATIC_screenCompressor,						},
	{	IDC_BUTTON_screenCompressor,						},	
	{	IDC_STATIC_mediaFileCompressor,						},
	{	IDC_BUTTON_mediaFileCompressor,						},
	{	IDC_STATIC_mediaDeviceCompressor,					},
	{	IDC_BUTTON_mediaDeviceCompressor,					},
	{	IDC_STATIC_webcamCompressor,						},
	{	IDC_BUTTON_webcamCompressor,						},



	{	IDC_BUTTON_restoreDefaultSettings,						},
	{	IDOK,													},
	{	IDCANCEL,												},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_menu_isCli_wallsbar_isCli[]  =
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

 QY_DMITEM  CONST_dlg_bar_isCli[]  =
{
	{	IDC_BUTTON_menu,				},
	{	-1,								},
};


 QY_DMITEM  CONST_dlg_policyAv_isCli[]  =  
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

	//
	{	IDC_STATIC_avResolution,						},
	{	IDC_STATIC_webcamResolution,					},
	{	IDC_STATIC_iWidth_webcam,						},
	{	IDC_STATIC_iHeight_webcam,						},
	{	IDOK,													},
	{	IDCANCEL,												},
	{	-1,		},

};

 QY_DMITEM  CONST_dlg_videoCompressors_isCli[]  =
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

 QY_DMITEM  CONST_dlg_msgList_isCli[]  =
{
	{	IDC_BUTTON_export,		},
	{	IDC_BUTTON_clear,		},
	{	IDCANCEL,				},
	{	-1,						},

};

 QY_DMITEM  CONST_dlg_objs_isCli[]  =
{
	{	IDOK,					},
	{	IDCANCEL,				},
	{	-1,				},
};


 QY_DMITEM  CONST_dlg_test_isCli[]  =
 {
	 {	IDC_BUTTON_aDev,		},
	 {	IDC_BUTTON_vDev,		},
	 {  IDC_BUTTON_cfgCapturePin_v,  },
	 {	IDC_BUTTON_testAv,		},
	 {	IDCANCEL,				},
	 {	-1,						},
 };

#ifndef  __WINCE__

 QY_DMITEM  CONST_dlg_imTaskProperties_isCli[]  =
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

 QY_DMITEM  CONST_dlg_imMsgProperties_isCli[]  =
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



 QY_DMITEM  CONST_dlg_qyExport_isCli[]  = 
{
	{	IDC_RADIO_exportCurQuery,			(  TCHAR  *  )CONST_resId_RADIO_exportCurQuery,		},
	{	IDC_RADIO_exportBakData,			(  TCHAR  *  )CONST_resId_RADIO_exportBakData,		},
	{	IDC_RADIO_exportCfg,				(  TCHAR  *  )CONST_resId_RADIO_exportCfg,		},
	{	IDC_STATIC_hint,					(  TCHAR  *  )CONST_resId_STATIC_exportHint,		},
	{	IDC_RADIO_exportBhbCfg,				(  TCHAR  *  )CONST_resId_RADIO_exportBhbCfg,		},
	{	IDC_RADIO_exportRegInfo,			(  TCHAR  *  )CONST_resId_RADIO_exportRegInfo,		},
	{	IDC_RADIO_procDj,					(  TCHAR  *  )CONST_resId_RADIO_procDj,		},
	{	IDC_RADIO_procModuleKnowlege,		},
	{	IDC_RADIO_procRegistryKnowlege,		},
	{	IDC_RADIO_procIpKnowledge,			},
	{	IDC_RADIO_procPhoneGuest,			},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_qnmClearup_isCli[]  = 
{
	{	IDD_qnmClearup,					 	(  TCHAR  *  )CONST_resId_IDD_qnmClearup,		},
	{	IDC_STATIC_clearHint, 				(  TCHAR  *  )CONST_resId_STATIC_clearHint,		},
	{	IDC_RADIO_clearupScannedIp, 	 	(  TCHAR  *  )CONST_resId_RADIO_clearupScannedIp,		},
	{	IDC_RADIO_clearupEvent, 	 		(  TCHAR  *  )CONST_resId_RADIO_clearupEvent,		},
	{	IDC_RADIO_procModuleKnowlege,	},
	{	IDC_RADIO_procRegistryKnowlege,		},
	{	IDC_RADIO_procImMsg,				},
	{	IDC_RADIO_procImHisTask,				},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};



  QY_DMITEM  CONST_dlg_qnmSearch_isCli[]  = 
{
	{	IDC_STATIC_queryType,				(  TCHAR  *  )CONST_resId_STATIC_queryType,			},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};


  QY_DMITEM  CONST_dlg_qnmEventSearch_isCli[]  =
{
	{	IDC_STATIC_hint,			},	//  CONS"请输入查询条件:",
	{	IDC_STATIC_startTime,		},	//	"起始时间:"
	{	IDC_STATIC_endTime,			},	//  "截止时间:"
	{	IDC_STATIC_eventType,		},	//  "事件类型:"

	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},

};

 QY_DMITEM  CONST_dlg_qnmPcListSearch_isCli[]  =
{	
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_qnmCfgPcGrps_isCli[]  =
{	
	{	IDC_ADD,							(  TCHAR  *  )CONST_resId_qnmCfgPcGrps_ADD,		},
	{	IDC_MODIFY,							(  TCHAR  *  )CONST_resId_qnmCfgPcGrps_MODIFY,		},
	{	IDC_DEL,							(  TCHAR  *  )CONST_resId_qnmCfgPcGrps_DEL,		},
	{	IDC_CHECK_bNotAllAllowed,			},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_qnmCfgAdvancedOptions_isCli[]  =
{	
	{	IDC_STATIC_dbTypeName,				},
	{	IDC_STATIC_dbServIp,				},
	{	IDC_STATIC_dbName					},
	{	IDC_STATIC_uid,						},
	{	IDC_STATIC_pwd,						},
	{	IDC_CHECK_default,					},
	{	IDOK,														},
	{	IDCANCEL,												},
	{	-1,		},
};


#endif

 QY_DMITEM  CONST_dlg_selectDsn_isCli[]  =
{
	{	IDOK,							},
	{	IDCANCEL,						},
	{	-1,		},
};

#ifndef  __WINCE__
 QY_DMITEM  CONST_dlg_imMsgSearch_isCli[]  =
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

 QY_DMITEM  CONST_dlg_wwwQmContact_isCli[]  =
{
	{	IDC_STATIC_staticMessengerId,	},
	{	IDC_CHECK_ucbPublic,			},
	{	IDC_STATIC_grpDisplayName,		},
	{	IDC_EDIT_grpDisplayName,		},
	{	IDC_STATIC_displayName,		},
	{	IDC_EDIT_displayName,		},
	{	IDC_CHECK_ucbImSwitchable,		},
	{	IDC_STATIC_wAdvertisement,		},
	{	IDOK,							},
	{	IDCANCEL,						},
	{	-1,		},
};


  QY_DMITEM  CONST_dlg_cfgIpKnowledge_isCli[]  =
{
	{	IDC_STATIC_startIp,				},
	{	IDC_STATIC_endIp,				},
	{	IDC_STATIC_wLocation,			},
	{	IDC_STATIC_iWeight,				},
	{	IDOK,							},
	{	IDCANCEL,						},
	{	-1,		},
};


 QY_DMITEM  CONST_dlg_cfgPhoneMessenger_isCli[]  =
{
	{	IDC_STATIC_dw,					},
	{	IDC_STATIC_bm,					},
	{	IDC_STATIC_syr,					},
	{	IDC_STATIC_countryCode,			},
	{	IDC_STATIC_phoneNo,				},
	{	IDOK,							},
	{	IDCANCEL,						},
	{	-1,		},
};

 QY_DMITEM  CONST_dlg_cfgGsmModem_isCli[]  =
{
	{	IDC_CHECK_ucbPublic,			},
	{	IDC_STATIC_idStr_vDev,			},
	{	IDC_STATIC_wDevIdStr,			},
	{	IDC_CHECK_ucbDefaultSmServer,	},
	{	IDC_STATIC_name,				},
	{	IDC_STATIC_cusName,				},
	{	IDC_CHECK_ucbDefault,				(  TCHAR  *  )CONST_resId_ucbDefaultSmContact,			},
	{	IDC_STATIC_staticMessengerId,		(  TCHAR  *  )CONST_resId_smContactMsgrId,				},
	{	IDC_STATIC_displayName,			},
	{	IDOK,							},
	{	IDCANCEL,						},
	{	-1,		},
};


 QY_DMITEM  CONST_dlg_verifyPhoneList_isCli[]  =
{
	{	IDC_STATIC_hint,					(  TCHAR  *  )CONST_resId_verifyPhoneListHint,			},
	{	IDC_STATIC_status,				},
	{	IDOK,							},
	{	IDC_BUTTON_refresh,				},
	{	IDC_BUTTON_deny,				},
	{	IDCANCEL,						},
	{	-1,		},
};

#endif


 QY_DMITEM  CONST_dlg_talk_isCli[]  =
{
	{	IDC_STATIC_instantStatus,	},
	{	IDC_BUTTON_font,			},
	{	IDC_STATIC_peerName,		},
	{	IDC_STATIC_peerDesc,		},
	{	IDCANCEL,		},
	{	-1,		},
};


 QY_DMITEM  CONST_dlg_desktopsMon_isCli[]  =
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


 QY_DMITEM  CONST_dlg_cfgVideoConference_isCli[]  =
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

 QY_DMITEM  CONST_IDD_instantAssistant_isCli[]  =  
{
	{	IDC_BUTTON_msg,						},
	{	IDC_request,						},
	{	IDC_talkerList,						},
	{	IDC_COMBO_usLayoutType,				},
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

 QY_DMITEM  CONST_dlg_instantAssistant_vw_isCli[]  =  
{
	{	IDC_BUTTON_msg,						},
	{	IDC_request,						},
	{	IDC_talkerList,						},
	{	IDC_COMBO_usLayoutType,				},
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

 QY_DMITEM  CONST_dlg_selectAvDev_isCli[]  =  
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

#ifndef  __WINCE__

 QY_DMITEM  CONST_dlg_cfgWmv_isCli[]  =
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

 QY_DMITEM  CONST_dlg_mediaControl_isCli[]  =
 {
	 //  {	IDC_BUTTON_PLAY,	},
	 {	IDC_BUTTON_STOP,	},
	 {	IDC_BUTTON_FRAMESTEP,	},
	 {	IDC_CHECK_PLAYTHROUGH,							},
	 {	IDC_CHECK_LOOP,									},
	 {	IDC_CHECK_MUTE,									},

	 {	-1,				},
 };
 #endif


 QY_DMITEM  CONST_dlg_shareDynBmps_isCli[]  =
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


 QY_DMITEM  CONST_dlg_progress_isCli[]  =
{
	{	IDC_STATIC_progress,	},
	{	IDOK,					},
	{	IDCANCEL,				},
	{	-1,				},
};

 QY_DMITEM  CONST_dlg_mcClientLogon_isCli[]  =
{
	{	IDC_STATIC_logonServer,	},
	{	IDC_STATIC_usrName,		},
	{	IDC_STATIC_passwd,		},
	{	IDC_BUTTON_option,		},
	{	IDOK,					},
	{	IDCANCEL,				},
	{	-1,				},
};

#ifndef  __WINCE__
 QY_DMITEM	CONST_dlg_messenger_isCli[]	=
{
	{	IDC_STATIC_hint1,		 },
	{	IDC_STATIC_messengerName,},   //  IDC_STATIC_staticName
	{	IDC_STATIC_passwd0,		},
	{	IDC_STATIC_passwd1,		},
	{	IDOK,					 },
	{	IDCANCEL,				 },
	{	-1,				},
};

 QY_DMITEM	CONST_dlg_messengerIsClient_isCli[]	=
{
	{	IDC_STATIC_hint1,		 },
	{	IDC_STATIC_messengerName,},   //  IDC_STATIC_staticName
	{	IDC_STATIC_passwd0,		},
	{	IDC_STATIC_passwd1,		},
	{	IDOK,					 },
	{	IDCANCEL,				 },
	{	-1,				},
};

 QY_DMITEM  CONST_dlg_imObjRule_isCli[]  =
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

#endif

#ifdef  __WINCE__
 QY_DMITEM  CONST_dlg_qnmCfgOptions_isClient_ce[]  =
{
	{	IDC_BUTTON_contact,		},
	{	IDC_BUTTON_group,		},
	{	IDC_BUTTON_status,		},
	{	IDCANCEL,				 },
	{	-1,						},

};

#endif

QY_DMITEM  CONST_dlg_ptzControl[]  =
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

QY_DMITEM  CONST_dlg_ptzSettings[]  =
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

QY_DMITEM  CONST_dlg_videoSubtitlesCfg[]  =
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

QY_DMITEM  CONST_dlg_subtitleSelect[]  = 
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
 QY_DMITEM  CONST_dlgTable_isCli[]  =
{
#ifndef  __WINCE__
	//
		
	//	
#if  0		//  2012/07/16
	{	IDD_qyCfgSystem,					(  TCHAR  *  )CONST_dlg_qyCfgSystem,				},
	{	IDD_qyCfgSystems,					(  TCHAR  *  )CONST_dlg_qyCfgSystems,				},
	{	IDD_cfgSystemParams,				(  TCHAR  *  )CONST_dlg_cfgSystemParams,						},
	{	IDD_cfgSystemParams_is,				(  TCHAR  *  )CONST_dlg_cfgSystemParams_is,				},
	{	IDD_qnmCfgRasOptions,				(  TCHAR  *  )CONST_dlg_qnmCfgRasOptions,			(  TCHAR  *  )CONST_resId_IDD_qnmCfgRasOptions,			},
	{	IDD_pcNetworkOptions_sel,			(  TCHAR  *  )CONST_dlg_pcNetworkOptions_sel,		},

	{	IDD_qnmCfgPcNetworkOptions,			(  TCHAR  *  )CONST_dlg_qnmCfgPcNetworkOptions,	(  TCHAR  *  )CONST_resId_IDD_qnmCfgPcNetworkOptions,	},	
	{	IDD_qnmCfgPcMonOptions,				(  TCHAR  *  )CONST_dlg_qnmCfgPcMonOptions,		},	
	{	IDD_cfgFileMonFilter,				(  TCHAR  *  )CONST_dlg_cfgFileMonFilter,			},
	{	IDD_cfgPcRegistrys,					(  TCHAR  *  )CONST_dlg_cfgPcRegistrys,				},
	{	IDD_cfgPcRegistry,					(  TCHAR  *  )CONST_dlg_cfgPcRegistry,				},
	{	IDD_qnmCfgPcRule,					(  TCHAR  *  )CONST_dlg_qnmCfgPcRule,				(  TCHAR  *  )CONST_resId_IDD_qnmCfgPcRule,				},
	{	IDD_prop_pcProxyCfg,				(  TCHAR  *  )CONST_dlg_prop_pcProxyCfg,			},
	{	IDD_addFileMonRule,					(  TCHAR  *  )CONST_dlg_addFileMonRule,		},
	{	IDD_policy_imAuthCond,				(  TCHAR  *  )CONST_dlg_policyImAuthCond,			},
	{	IDD_passwdForStopMon,				(  TCHAR  *  )CONST_dlg_passwdForStopMon,			(  TCHAR  *  )CONST_resId_IDD_passwdForStopMon,			},
	{	IDD_cusPcSp,						(  TCHAR  *  )CONST_dlg_cusPcSp,					(  TCHAR  *  )CONST_resId_IDD_cusPcSp,					},
#endif

	{	IDD_cfgCustom,						(  TCHAR  *  )CONST_dlg_cfgCustom_isCli,									},
	{	IDD_cfgStandardName,				(  TCHAR  *  )CONST_dlg_cfgStandardName_isCli,	},
	{	IDD_cfgStandardNames,				(  TCHAR  *  )CONST_dlg_cfgStandardNames_isCli,	},
	{	IDD_exportClients,					(  TCHAR  *  )CONST_dlg_exportClients_isCli,		},				//  2011/03/28
#endif
	{	IDD_qnmCfgOptions_isClient,			(  TCHAR  *  )CONST_dlg_qnmCfgOptions_isCli,					},
#ifndef  __WINCE__
	{	IDD_qnmEditPcUsrInfo ,				(  TCHAR  *  )CONST_dlg_qnmEditPcUsrInfo_isCli,			(  TCHAR  *  )CONST_resId_IDD_qnmEditPcUsrInfo,			},
	//  2005/11/09
	{	IDD_ABOUTBOX,						(  TCHAR  *  )CONST_dlg_aboutBox_isCli,			(  TCHAR  *  )CONST_resId_IDD_ABOUTBOX,					},
	{	IDD_CFGUSR,							(  TCHAR  *  )CONST_dlg_cfgUsr_isCli,					(  TCHAR  *  )CONST_resId_IDD_CFGUSR,					},
	{	IDD_CFGUSRS,						(  TCHAR  *  )CONST_dlg_cfgUsrs_isCli,					(  TCHAR  *  )CONST_resId_IDD_CFGUSRS,					},
	{	IDD_CFGWARN,						(  TCHAR  *  )CONST_dlg_cfgWarn_isCli,					(  TCHAR  *  )CONST_resId_IDD_CFGWARN,					},
	{	IDD_clearupEventCond,				(  TCHAR  *  )CONST_dlg_cleanupEventCond_isCli,			(  TCHAR  *  )CONST_resId_IDD_clearupEventCond,			},
	{	IDD_qnmSearch,						(  TCHAR  *  )CONST_dlg_qnmSearch_isCli,					(  TCHAR  *  )CONST_resId_IDD_qnmSearch,				    },
	{	IDD_qnmCfgPcGrp,					(  TCHAR  *  )CONST_dlg_qnmCfgPcGrp_isCli,				(  TCHAR	 *  )CONST_resId_IDD_qnmCfgPcGrp,				},
	{	IDD_shhgPcProperties,				(  TCHAR  *  )CONST_dlg_pcProperties_isCli,				(  TCHAR  *  )CONST_resId_IDD_shhgPcProperties,			},

	{	IDD_prop_messenger,					(  TCHAR  *  )CONST_dlg_messengerProperties_isCli,		},
	{	IDD_prop_imGrp,						(  TCHAR  *  )CONST_dlg_imGrpProperties_isCli,			},
	{	IDD_imGrp,							(  TCHAR  *  )CONST_dlg_imGrp_isCli,				},
	{	IDD_cfgCustomerService,				(  TCHAR  *  )CONST_dlg_cfgCustomerService_isCli,	},
#endif
	{	IDD_policy_isClient,				(  TCHAR  *  )CONST_dlg_policy_isCli,	},
	{	IDD_menu_isCli_walls,				(  TCHAR  *  )CONST_dlg_menu_isCli_wallsbar_isCli,},
	{	IDD_qyBar,							(  TCHAR  *  )CONST_dlg_bar_isCli,				},
	{	IDD_policyAv,						(  TCHAR  *  )CONST_dlg_policyAv_isCli,			},
#ifndef  __WINCE__
	{	IDD_prop_imTask,					(  TCHAR  *  )CONST_dlg_imTaskProperties_isCli,	},
	{	IDD_prop_imMsg,						(  TCHAR  *  )CONST_dlg_imMsgProperties_isCli,	},
	{	IDD_qyExport,						(  TCHAR  *  )CONST_dlg_qyExport_isCli,					(  TCHAR  *  )CONST_resId_IDD_qyExport,					},
	{	IDD_qnmClearup,						(  TCHAR  *  )CONST_dlg_qnmClearup_isCli,					(  TCHAR  *  )CONST_resId_IDD_qnmClearup,				},
	{	IDD_qnmSearch,						(  TCHAR  *  )CONST_dlg_qnmSearch_isCli,					(  TCHAR  *  )CONST_resId_IDD_qnmSearch,				},
	{	IDD_qnmEventSearch,					(  TCHAR  *  )CONST_dlg_qnmEventSearch_isCli,			},
	{	IDD_qnmPcListSearch,				(  TCHAR  *  )CONST_dlg_qnmPcListSearch_isCli,			},
	{	IDD_qnmCfgPcGrps,					(  TCHAR  *  )CONST_dlg_qnmCfgPcGrps_isCli,				},
	{	IDD_qnmCfgAdvancedOptions,			(  TCHAR  *  )CONST_dlg_qnmCfgAdvancedOptions_isCli,		},
#if  0		//  2012/07/16
	{	IDD_prop_pcNetwork,					(  TCHAR  *  )CONST_dlg_prop_pcNetwork,			},
	{	IDD_qnmCfgPcNetworkRule,			(  TCHAR  *  )CONST_dlg_qnmCfgPcNetworkRule,		},
	{	IDD_qnmCfgPcProxyCfg,				(  TCHAR  *  )CONST_dlg_qnmCfgPcProxyCfg,			},
	{	IDD_prop_pcComputer,				(  TCHAR  *  )CONST_dlg_prop_pcComputer,			},
	{	IDD_qnmCfgPcComputer,				(  TCHAR  *  )CONST_dlg_qnmCfgPcComputer,		(  TCHAR  *  )CONST_resId_IDD_qnmCfgPcComputer,			},
	{	IDD_prop_windowsUpdatePolicy,		(  TCHAR  *  )CONST_dlg_prop_windowsUpdatePolicy,		},
	{	IDD_qnmCfgWindowsUpdatePolicy,		(  TCHAR  *  )CONST_dlg_qnmCfgWindowsUpdatePolicy,		},
	{	IDD_qnmCfgUnchk,					(  TCHAR  *  )CONST_dlg_qnmCfgUnchk,		},
	{	IDD_cfgPcProcessRule,				(  TCHAR  *  )CONST_dlg_cfgPcProcessRule,		},
	{	IDD_cfgSwitchPolicyGrps,			(  TCHAR  *  )CONST_dlg_cfgSwitchPolicyGrps,		},
	{	IDD_cfgSwitchPolicyGrp,				(  TCHAR  *  )CONST_dlg_cfgSwitchPolicyGrp,		},
	{	IDD_addSwitchToGrp,					(  TCHAR  *  )CONST_dlg_addSwitchToGrp,		},
	{	IDD_cfgSwitchDefaultPolicyGrp,		(  TCHAR  *  )CONST_dlg_cfgSwitchDefaultPolicyGrp,		},
	{	IDD_cfgModuleKnowlege,				(  TCHAR  *  )CONST_dlg_cfgModuleKnowlege,				},
	{	IDD_moduleKnowlegeOptions,			(  TCHAR  *  )CONST_dlg_moduleKnowlegeOptions,			},
	{	IDD_cfgPcRegistryKnowledge,			(  TCHAR  *  )CONST_dlg_cfgPcRegistryKnowledge,		},
	{	IDD_qnmCfgUnchkedIpGrp,				(  TCHAR  *  )CONST_dlg_qnmCfgUnchkedIpGrp,		},
	{	IDD_prop_moduleKnowlege,			(  TCHAR  *  )CONST_dlg_cfgModuleKnowlege,				},
	{	IDD_prop_pcRegistryKnowledge,		(  TCHAR  *  )CONST_dlg_cfgPcRegistryKnowledge,		},
	{	IDD_qnmEditMacInfo,					(  TCHAR  *  )CONST_dlg_qnmEditMacInfo,		},
	{	IDD_qnmSnmpObjProperties,			(  TCHAR  *  )CONST_dlg_qnmSnmpObjProperties,		},
	{	IDD_qnmSnmpObjPortProperties,		(  TCHAR  *  )CONST_dlg_qnmSnmpObjPortProperties,		},
	{	IDD_editSwitchInfo,					(  TCHAR  *  )CONST_dlg_editSwitchInfo,				},
	{	IDD_qnmCfgSnmpObjRule,				(  TCHAR  *  )CONST_dlg_qnmCfgSnmpObjRule,				},
	//
	{	IDD_qnmPcProcessModuleListSearch,	(  TCHAR  *  )CONST_dlg_qnmPcProcessModuleListSearch,	},
	{	IDD_qnmCfgIpScan,					(  TCHAR  *  )CONST_dlg_qnmCfgIpScan,			(  TCHAR  *  )CONST_resId_IDD_qnmCfgIpScan,				},
	{	IDD_qnmCfgIpGrp,					(  TCHAR  *  )CONST_dlg_qnmCfgIpGrp,				},
	{	IDD_cfgSkippedMacs,					(  TCHAR  *  )CONST_dlg_cfgSkippedMacs,	},
	{	IDD_qnmOtherMacInfo,				(  TCHAR  *  )CONST_dlg_qnmOtherMacInfo,		},
	{	IDD_phoneNum,						(  TCHAR  *  )CONST_dlg_phoneNum,				},	
	//  2005/12/11
	{	IDD_mgrSwitchPolicyGrps,			(  TCHAR  *  )CONST_dlg_mgrSwitchPolicyGrps,		},
	//

#endif
	//
	{	IDD_selectDsn,						(  TCHAR  *  )CONST_dlg_selectDsn_isCli,						},
	{	IDD_select_isCli,					(  TCHAR  *  )CONST_dlg_selectDsn_isCli,						},
	{	IDD_imMsgSearch,					(  TCHAR  *  )CONST_dlg_imMsgSearch_isCli,					},
	{	IDD_wwwQmCfg,						(  TCHAR  *  )CONST_dlg_wwwQmContact_isCli,					},
	{	IDD_cfgIpKnowledge,					(  TCHAR  *  )CONST_dlg_cfgIpKnowledge_isCli,				},
	{	IDD_prop_ipKnowledge,				(  TCHAR  *  )CONST_dlg_cfgIpKnowledge_isCli,				},
	{	IDD_cfgPhoneMessenger,				(  TCHAR  *  )CONST_dlg_cfgPhoneMessenger_isCli,				},
	{	IDD_cfgGsmModem,					(  TCHAR  *  )CONST_dlg_cfgGsmModem_isCli,						},
	{	IDD_verifyPhoneList,				(  TCHAR  *  )CONST_dlg_verifyPhoneList_isCli,			},
#endif
	{	IDD_talk,							(  TCHAR  *  )CONST_dlg_talk_isCli,					},
	{	IDD_desktopsMon,					(  TCHAR  *  )CONST_dlg_desktopsMon_isCli,			},
	{	IDD_cfgVideoConference,				(  TCHAR  *  )CONST_dlg_cfgVideoConference_isCli,	},
	{	IDD_videoCompressors,				(  TCHAR  *  )CONST_dlg_videoCompressors_isCli,		},
	{	IDD_msgList,						(  TCHAR  *  )CONST_dlg_msgList_isCli,				},
	{	IDD_objs,							(  TCHAR  *  )CONST_dlg_objs_isCli,					},
	{	IDD_test_isCli,						(  TCHAR  *  )CONST_dlg_test_isCli,					},
#ifndef  __WINCE__
	{	IDD_cfgWmv,							(  TCHAR  *  )CONST_dlg_cfgWmv_isCli,				},
	{	IDD_mediaControl,					(  TCHAR  *  )CONST_dlg_mediaControl_isCli,		},
#endif

	{	IDD_shareDynBmps,					(  TCHAR  *  )CONST_dlg_shareDynBmps_isCli,				},
	{	IDD_progress,						(  TCHAR  *  )CONST_dlg_progress_isCli,					},
	{	IDD_mcClient_logon,					(  TCHAR  *  )CONST_dlg_mcClientLogon_isCli,		},
#ifndef  __WINCE__
#if  0
	{	IDD_messenger,						(  TCHAR  *  )CONST_dlg_messenger_isCli,			},
#endif
	{	IDD_messenger_isClient,				(  TCHAR  *  )CONST_dlg_messengerIsClient_isCli,	},
	{	IDD_imObjRule,						(  TCHAR  *  )CONST_dlg_imObjRule_isCli,			},
#endif
	//
#ifdef  __WINCE__
	{	IDD_qnmCfgOptions_isClient_ce,		(  TCHAR  *  )CONST_dlg_qnmCfgOptions_isClient_ce,  },
#endif 

#if  1  //  __APP_qyMc_touchscreen__
	{	IDD_instantAssistant,				(  TCHAR  *  )CONST_IDD_instantAssistant_isCli,			},
	{	IDD_instantAssistant_vw,			(  TCHAR  *  )CONST_dlg_instantAssistant_vw_isCli,		},
	{	IDD_selectAvDev,					(  TCHAR  *  )CONST_dlg_selectAvDev_isCli,				},
#endif  
	{	IDD_ptzControl,						(  TCHAR  *  )CONST_dlg_ptzControl,						},
	{	IDD_ptzSettings,					(  TCHAR  *  )CONST_dlg_ptzSettings,					},
	{	IDD_videoTagCfg,					(  TCHAR  *  )CONST_dlg_videoSubtitlesCfg,				},
	{	IDD_subtitle_select,				(  TCHAR  *  )CONST_dlg_subtitleSelect,					},

	{	-1,		},
};

