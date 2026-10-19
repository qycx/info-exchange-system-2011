

#ifndef  __AWMCHKCFG_H__
#define  __AWMCHKCFG_H__	/*  {  */

#define		DEFAULT_AWM_CHKED_METHOD			0

#define		MAX_DIGEST_LEN						256
#define		DEFAULT_DIGEST_LEN					16

#if  MAX_DIGEST_LEN  <  DEFAULT_DIGEST_LEN
 #error  MAX_DIGEST can't be less than DEFAULT_DIGEST_LEN
#endif


// #define AWM_NT_LOGON_SCRIPT_SIZE				12
// #define AWM_NT_LOGON_SCRIPT_DIGEST			{ ( unsigned char )0x44, ( unsigned char )0x22, ( unsigned char )0x7a, ( unsigned char )0x3a, ( unsigned char )0x33, ( unsigned char )0xbc, ( unsigned char )0xbe, ( unsigned char )0x0a, ( unsigned char )0x6f, ( unsigned char )0x9a, ( unsigned char )0x77, ( unsigned char )0x1e, ( unsigned char )0x7a, ( unsigned char )0x7e, ( unsigned char )0xa2, ( unsigned char )0xa6 }
//  #include "ntScriptChk.h"
#define		AWM_NT_LOGON_SCRIPT_SIZE			AWM_WIN2K_STARTUP_SCRIPT_SIZE
#define		AWM_NT_LOGON_SCRIPT_DIGEST			AWM_WIN2K_STARTUP_SCRIPT_DIGEST
#define		AWM_NT_LOGON_SCRIPT_NAME			CONST_qwmLogonScriptName

#define		AWM_NT_LOGON_BAT_NAME				"netCfg.bat"

// #define AWM_WIN2K_STARTUP_SCRIPT_SIZE		7
// #define AWM_WIN2K_STARTUP_SCRIPT_DIGEST		{ ( unsigned char )0xfc, ( unsigned char )0xea, ( unsigned char )0x92, ( unsigned char )0x0f, ( unsigned char )0x74, ( unsigned char )0x12, ( unsigned char )0xb5, ( unsigned char )0xda, ( unsigned char )0x7b, ( unsigned char )0xe0, ( unsigned char )0xcf, ( unsigned char )0x42, ( unsigned char )0xb8, ( unsigned char )0xc9, ( unsigned char )0x37, ( unsigned char )0x59 }
#include	"win2kScriptChk.h"
#define		AWM_WIN2K_STARTUP_SCRIPT_NAME		CONST_qwmStartupScriptName

#define		AWM_NT_LOGON_SCRIPT_INDEX			0
#define		AWM_NT_LOGON_BAT_INDEX				1
#define		AWM_WIN2K_STARTUP_SCRIPT_INDEX		2
#define		CONST_qwmBak_index					3
#define		CONST_qrtBak_index					4
#define		CONST_qyRegTool_index				5			//  for netMc2
#define		CONST_qrtForNms_index				6			//  for nms
#define		CONST_cPcJbForNms_index				7			//  for nms cpcjb
#define		CONST_qrtForSecChk_index			8			//  for secChk 快速检查
#define		CONST_qrtForSecChk1_index			9			//  for secChk 全面检查
#define		CONST_qyRegTool_x64_index			10			//  2010/05/16
#define		CONST_qnmCgi_index					11			//  qnm.cgi
#define		CONST_qrtForSecChkDj_index			12			//  for secChk 快速检查 单机版 
#define		CONST_qrtForSecChkDj1_index			13			//  for secChk 全面检查 单机 
#define		CONST_myCapture_index				14			//  for secChk 单机抓屏工具
#define		CONST_qyRegTool98_index				15			//  98版的注册工具
#define		CONST_qrtForNms98_index				16			//  98版的登记工具
#define		CONST_qyMessengerIni_index			17			//  2000的messenger.ini, 2007/06/16
#define		CONST_qyMessengerSplash_index		18			//  2009/07/29
#define		CONST_qyMessengerMsi_index			19
#define		CONST_qyMessengerSetup_index		20
//
#define		AWM_TOTAL_FILES						21


#ifdef  __DEBUG__
  #define	CONST_nInterval_awmChk				10000
#else
  #define	CONST_nInterval_awmChk				15000
#endif


#define		AWM_CHK_BAK_SUB_DIR					"bak"
#define		AWM_BAT_CHK_FILE					"chkFile.ext"
#ifdef  __DEBUG__
  #define	AWM_NT_LOGON_SCRIPT_CHK_FILE		"ntChkFile.ext"
  #define	AWM_WIN2K_STARTUP_SCRIPT_CHK_FILE	"win2kChkFile.ext"
#endif

//  #define		DEFAULT_AWM_NT_LOGON_SCRIPT_PATH	"netCfg.bat"
#define		DEFAULT_qwmNtLogonScriptPath		"netCfg.bat"

#endif  /*  }  */



