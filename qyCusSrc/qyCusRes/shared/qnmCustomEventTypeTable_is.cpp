
#include	"stdafx.h"
#include	<tchar.h>
//  #include	"qyCommon.h"
//  #include	"resource_main.h"
//  #include	"afxres.h"

#include	"qyCusResCommon.h"
//  #include	"qyCusResPublic.h" 

#include	"qnmCustomStr_common.h"
#include	"qnmCustomStr_is.h"

  //  事件类型总表
 QY_DMITEM  CONST_qnmEventTypeTable0_is[]  =  
{
	//
	{	CONST_qyEventType_nm_newReg,				CONST_str_nm_newReg,		},	//			_T(  "首次注册"  ),					},	
	{	CONST_qyEventType_nm_reReg,					CONST_str_nm_reReg,		},	//				_T(  "重新注册"  ),					},


	//  以下是应用系统操作日志			//									
	{	CONST_qyEventType_nm_logon,								CONST_str_nm_logon,		},	//				_T(  "登录"  ),					
	{	CONST_qyEventType_nm_logoff,							CONST_str_nm_logoff,		},	//			_T(  "离录"  ),						},
	{	CONST_qyEventType_nm_addUsr,							CONST_str_nm_addUsr,		},	//			_T(  "添加用户"  ),					},	
	{	CONST_qyEventType_nm_delUsr,							CONST_str_nm_delUsr,		},	//			_T(  "删除用户"  ),					},	
	{	CONST_qyEventType_nm_modifyUsr,							CONST_str_nm_modifyUsr,		},	//			_T(  "修改用户"  ),					},	
	{	CONST_qyEventType_nm_clearupEvent,						CONST_str_nm_clearupEvent,		},	//		_T(  "清空事件"  ),					},		
	{	CONST_qyEventType_nm_pzcz,								CONST_str_nm_pzcz,		},	//				_T(  "配置操作"  ),					},
	{	CONST_qyEventType_nm_sysWarn,							CONST_str_nm_sysWarn,		},	//			_T(  "系统告警"  ),					},	
	{	CONST_qyEventType_nm_logonFailed,						CONST_str_nm_logonFailed,			},		//  2006/02/25
	{	CONST_qyEventType_nm_export,							CONST_str_nm_export,		},				//  导出
	{	CONST_qyEventType_nm_bak,								CONST_str_nm_bak,			},				//  备份
	{	CONST_qyEventType_nm_import,							CONST_str_nm_import,		},				//  导入
	//
	{	CONST_qyEventType_nm_clearupImMsg,						CONST_str_nm_clearupImMsg,	},				//  清空消息
	{	CONST_qyEventType_nm_clearupImHisTask,					CONST_str_nm_clearupImHisTask,	},			//  清空历史任务

	//
	//
	{	CONST_qyEventType_is_newMessenger,			CONST_str_is_newMessenger,			},
	{	CONST_qyEventType_is_messengerLogon,		CONST_str_is_messengerLogon,			},
	{	CONST_qyEventType_is_messengerLogoff,		CONST_str_is_messengerLogoff,			},
	{	CONST_qyEventType_is_connErr,				CONST_str_is_connErr,					},
	{	CONST_qyEventType_is_memoryErr,				CONST_str_is_memoryErr,			},
	//
	{	-1,											NULL,						},
};


 QY_DMITEM  CONST_qnmEventTypeTable_op_is[]  =  
{
	{	CONST_qyEventType_nm_logon,								CONST_str_nm_logon,						},
	{	CONST_qyEventType_nm_logoff,							CONST_str_nm_logoff,					},
	{	CONST_qyEventType_nm_addUsr,							CONST_str_nm_addUsr,					},
	{	CONST_qyEventType_nm_delUsr,							CONST_str_nm_delUsr,					},
	{	CONST_qyEventType_nm_modifyUsr,							CONST_str_nm_modifyUsr,					},
	{	CONST_qyEventType_nm_clearupEvent,						CONST_str_nm_clearupEvent,				},
	//  {	CONST_qyEventType_nm_pzcz,								CONST_str_nm_pzcz,					},
	//  {	CONST_qyEventType_nm_sysWarn,							CONST_str_nm_sysWarn,				},
	{	CONST_qyEventType_nm_logonFailed,						CONST_str_nm_logonFailed,				},	//  2006/02/25
	{	CONST_qyEventType_nm_export,							CONST_str_nm_export,					},	//  导出
	{	CONST_qyEventType_nm_bak,								CONST_str_nm_bak,						},	//  备份
	{	CONST_qyEventType_nm_import,							CONST_str_nm_import,					},	//  导入
	//
	{	CONST_qyEventType_nm_clearupImMsg,						CONST_str_nm_clearupImMsg,				},				//  清空消息
	{	CONST_qyEventType_nm_clearupImHisTask,					CONST_str_nm_clearupImHisTask,			},			//  清空历史任务
	//
	{	-1,														NULL,									},
};



 QY_DMITEM  CONST_qnmEventTypeTable_misMgr[]  =  
{
	{	CONST_qyEventType_is_newMessenger,			CONST_str_is_newMessenger,			},
	{	CONST_qyEventType_is_messengerLogon,		CONST_str_is_messengerLogon,			},
	{	CONST_qyEventType_is_messengerLogoff,		CONST_str_is_messengerLogoff,			},
	{	CONST_qyEventType_is_connErr,				CONST_str_is_connErr,					},
	{	CONST_qyEventType_is_memoryErr,				CONST_str_is_memoryErr,			},
	{	-1,											NULL,					},
};



    //  2011/08/08
  QY_DMITEM  CONST_policyAvLevelTable_basic[]  =
{
	{	CONST_policyAvLevel_ld,					CONST_IDC_BUTTON_setLdSettings,		},
#if 0
	{	CONST_policyAvLevel_ld1,				CONST_IDC_BUTTON_setLd1Settings,	},
#endif
	{	CONST_policyAvLevel_sd,					CONST_IDC_BUTTON_setSdSettings,		},
	{	CONST_policyAvLevel_sd1,				CONST_IDC_BUTTON_setSd1Settings,	},
	{	-1,				NULL,				},
};


    //  2011/08/08
  QY_DMITEM  CONST_policyAvLevelTable_standard[]  =
{
	{	CONST_policyAvLevel_ld,						CONST_IDC_BUTTON_setLdSettings,		},
	{	CONST_policyAvLevel_sd,						CONST_IDC_BUTTON_setSdSettings,		},
	{	CONST_policyAvLevel_sd1,					CONST_IDC_BUTTON_setSd1Settings,	},
	{	CONST_policyAvLevel_sd2,					CONST_IDC_BUTTON_setSd2Settings,		},
	{	CONST_policyAvLevel_sd3,					CONST_IDC_BUTTON_setSd3Settings,		},
	{	CONST_policyAvLevel_hd,						CONST_IDC_BUTTON_setHdSettings,		},
	{	-1,				NULL,				},
};

    //  2011/08/08
  QY_DMITEM  CONST_policyAvLevelTable_high[]  =
{
	{	CONST_policyAvLevel_ld,						CONST_IDC_BUTTON_setLdSettings,		},
	{	CONST_policyAvLevel_sd,						CONST_IDC_BUTTON_setSdSettings,		},
	{	CONST_policyAvLevel_sd1,					CONST_IDC_BUTTON_setSd1Settings,	},
	{	CONST_policyAvLevel_sd2,					CONST_IDC_BUTTON_setSd2Settings,	},
	{	CONST_policyAvLevel_sd3,					CONST_IDC_BUTTON_setSd3Settings,	},
	{	CONST_policyAvLevel_hd,						CONST_IDC_BUTTON_setHdSettings,		},
	{	CONST_policyAvLevel_hd1,					CONST_IDC_BUTTON_setHd1Settings,	},
	{	CONST_policyAvLevel_hd2,					CONST_IDC_BUTTON_setHd2Settings,	},
	{	CONST_policyAvLevel_hd3,					CONST_IDC_BUTTON_setHd3Settings,	},
	{	CONST_policyAvLevel_fullHd,					CONST_IDC_BUTTON_setFullHdSettings,	},
	{	CONST_policyAvLevel_fullHd1,				CONST_IDC_BUTTON_setFullHd1Settings,},
	{	CONST_policyAvLevel_fullHd2,				CONST_IDC_BUTTON_setFullHd2Settings,},
	{	CONST_policyAvLevel_fullHd3,				CONST_IDC_BUTTON_setFullHd3Settings,},
	{	-1,				NULL,				},
};
  
  //  2012/02/16
  QY_DMITEM  CONST_policyAvLevelTable_webcam_basic[]  =
{
	{	CONST_policyAvLevel_ld,					CONST_IDC_BUTTON_setLdSettings,		},
	{	-1,				NULL,				},
};

  //  2012/02/16
  QY_DMITEM  CONST_policyAvLevelTable_webcam_standard[]  =
{
	{	CONST_policyAvLevel_ld,					CONST_IDC_BUTTON_setLdSettings,		},
	{	CONST_policyAvLevel_sd3,				CONST_IDC_BUTTON_setSd3Settings,	},
	{	-1,				NULL,				},
};

  QY_DMITEM  CONST_policyAvLevelTable_screen_basic[]  =
{
	{	CONST_policyAvLevel_dev_2fps,				CONST_IDC_BUTTON_setDev2fpsSettings,},
	{	-1,											NULL,								},
};
  QY_DMITEM  CONST_policyAvLevelTable_screen_standard[]  =
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
  QY_DMITEM  CONST_policyAvLevelTable_screen_high[]  =
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

 QY_DMITEM  CONST_policyAvLevelTable_mediaFile_basic[]  =
{
	{	CONST_policyAvLevel_dev_2fps,				CONST_IDC_BUTTON_setDev2fpsSettings,},
	{	CONST_policyAvLevel_dev_10fps,				CONST_IDC_BUTTON_setDev10fpsSettings,},
	{	-1,											NULL,								},
};

 QY_DMITEM  CONST_policyAvLevelTable_mediaFile_standard[]  =
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

 QY_DMITEM  CONST_policyAvLevelTable_mediaFile_high[]  =
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

 QY_DMITEM  CONST_policyAvLevelTable_mediaDevice_basic[]  =
{
	{	CONST_policyAvLevel_dev_2fps,				CONST_IDC_BUTTON_setDev2fpsSettings,},
	{	-1,											NULL,								},
};
 QY_DMITEM  CONST_policyAvLevelTable_mediaDevice_standard[]  =
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
 QY_DMITEM  CONST_policyAvLevelTable_mediaDevice_high[]  =
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

 QY_DMITEM  CONST_usLayoutTypeTable[]  =
{
	{		CONST_usLayoutType_null,							CONST_str_layout_auto,				},
	{		CONST_usLayoutType_dialog,							CONST_str_layout_dialog,			},
	{		CONST_usLayoutType_conference,						CONST_str_layout_conference,		},
	{		CONST_usLayoutType_training,						CONST_str_layout_training,			},
	{		CONST_usLayoutType_videoOnly,						CONST_str_layout_videoOnly,		},
	{		CONST_usLayoutType_resourceOnly,					CONST_str_layout_resourceOnly,		},
	{		-1,						},
};

 QY_DMITEM  CONST_usLayoutTypeTable_resource[]  =
{
	{		CONST_usLayoutType_null,							CONST_str_layout_auto,				},
	{		CONST_usLayoutType_dialog,							CONST_str_layout_dialog,			},
	{		CONST_usLayoutType_resourceOnly,					CONST_str_layout_resourceOnly,		},
	{		-1,						},
};

 QY_DMITEM	CONST_iTargetUsageTable[]  =
{
	{	CONST_iTargetUsage_bestQuality,				CONST_str_bestQuality,		},
	{	CONST_iTargetUsage_balanced,				CONST_str_balanced,			},
	{	CONST_iTargetUsage_bestSpeed,				CONST_str_bestSpeed,		},
	{	-1,				NULL,				},
};

 QY_DMITEM  CONST_iAvgBitrateTable[]  =  
{
	{		CONST_iAvgBitrate_1m,						_T(  "1Mbps/1080p-30p"  ),			},
	{		CONST_iAvgBitrate_2m,						_T(  "2Mbps/1080p-30p"  ),			},
	{		CONST_iAvgBitrate_3m,						_T(  "3Mbps/1080p-30p"  ),			},
	{		CONST_iAvgBitrate_4m,						_T(  "4Mbps/1080p-30p"  ),			},
	{		CONST_iAvgBitrate_5m,						_T(  "5Mbps/1080p-30p"  ),			},
	{		CONST_iAvgBitrate_6m,						_T(  "6Mbps/1080p-30p"  ),			},
	{		CONST_iAvgBitrate_7m,						_T(  "7Mbps/1080p-30p"  ),			},
	{		CONST_iAvgBitrate_8m,						_T(  "8Mbps/1080p-30p"  ),			},
	{		CONST_iAvgBitrate_9m,						_T(  "9Mbps/1080p-30p"  ),			},
	{		CONST_iAvgBitrate_10m,						_T(  "10Mbps/1080p-30p"  ),			},

	{	-1,											NULL,					},
};


//  
#if  0
 QY_DMITEM  CONST_qnmEventTypeTable_null[]  =  
{
	{	-1,											NULL,					},
};
#endif

