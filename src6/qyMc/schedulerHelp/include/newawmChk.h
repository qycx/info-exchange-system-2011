

#ifndef  __AWMCHECK_H__	 /*  {  */
#define  __AWMCHECK_H__

#include	"qyCommon.h"
#include	"qyPreCustom.h"
#include	"qyCustom.h"
#include	"qyWmComm.h"
#include	"qyCommCommon.h"
#include	"qyLicense.h"
#include	"qyCommProc.h"
#include	"qnmCommProc.h"
#include	"traceLog.h"

#include	"qnmCustom.h"
#include	"newawmChkCfg.h"
#include	"asrWMonCfg.h"



#define		AWM_CHK_FILE_STATE_UNKNOWN			-1
#define		AWM_CHK_FILE_NOT_EXISTS				-2
#define		AWM_CHK_FILE_INVALID				-3
#define		AWM_CHK_FILE_OK						1

#define		AWM_ACCESS_ALL						0x1f01ff
#define		AWM_ACCESS_RX						0x1200a9

#define		SZ_INDENT_BUF						80
#define		PERR(  api  )  printf(  "%s: Error %d from %s on line %d\n",  __FILE__,  GetLastError(  ),  api,  __LINE__  );

typedef  struct  __awm_chked_file_t		{
	
				 TCHAR					dir[CONST_qyMaxPathLen  +  1];
				 TCHAR					fileName[256];
				 TCHAR					fullPathName[CONST_qyMaxPathLen  +  1];
				 HFILE					hFile;
				 unsigned  int			size;
				 char					digest[MAX_DIGEST_LEN];
				 unsigned  int			digestLen;
				 int					chkedMethod;
				 unsigned  char			ucbNotChkSid;
				 unsigned  short		idrData;				//  资源号, 为0表非从资源数据产生
				 unsigned  char			ucbQwm;					//  是否qwm
				 unsigned  char			ucbNotModifyData;		//  孵化时简单的输出文件，不用更新里面的孵化参数, 2007/06/16
				 //
				 int					iSystemId;				//  
				 unsigned  char			ucbSecChkQuickly;		//	是否快速安检
				 unsigned  char			ucbNoGui;				//	是否有界面
				 unsigned  char			ucbAssetMgr;			//  是否有资产管理
				 unsigned  char			ucbNetMc2;				//  是否管理非法外联,  2004/11/15
				 unsigned  char			ucbSecChk;				//  是否安检， 2005/05/03
				 unsigned  char			ucbDj;					//  是否单机版， 2005/08/19

}		 AWM_CHKED_FILE;


typedef  struct  __awm_chk_t				{
			
				 MACRO_qyAppCommonMems

				 int						iPlatformId;

				 /*
				 struct  __gsids_t			{
						 PSID				psidDomainUserAdminSid;
						 PSID				psidDomainGroupAdminsSid;
						 PSID				psidDomainGroupUsersSid;
						 PSID				psidDomainAliasAdminsSid;
						 PSID				psidDomainAliasUsersSid;
						 PSID				psidLocalSystemSid;				// SECURITY_LOCAL_SYSTEM_RID
						 PSID				psidDomainAliasSystemOpsSid;	// DOMAIN_ALIAS_RID_SYSTEM_OPS
						 PSID				psidSecurityWorldSid;			// SECURITY_WORLD_RID
				 }							gSids;
				 */

				 BOOL						bShallQuit;
				 unsigned  char				ucbStopMon;
				 unsigned  char				ucbStopScripts;

				 unsigned  char				ucbDomainCtrl;					//  是否域控制器

				 AWM_CHKED_FILE			*	pScripts[AWM_TOTAL_FILES];
				 HANDLE						hThreadHint;
				 QY_ENC_CTX					encCtx;
				 
				 struct						{

					 QNM_SYSCFG_INFO	*	pSysCfg;

					 TCHAR					installDir[CONST_qyMaxPathLen  +  1];
					 char					workDir[CONST_qyMaxPathLen  +  1];
				 	 TCHAR					rootKey[CONST_qyMaxKeyLen  +  1];
					 
					 //  如下是配置数据文件			//  2005/08/27
					 TCHAR					cfgFullFileName[CONST_qyMaxPathLen  +  1];		//  配置文件绝对路径

					 //
				 	 //  QY_LOGICAL_SERVER		cnt;
					 QNM_CNT_CFG			cntCfg;								//  2006/06/30,将上面的cnt扩展为一个更多的地址选择
					 char					seqNo[CONST_maxSeqNoLen  +  1];		//  2005/06/24
					 TCHAR					regToolDir[MAX_PATH  +  1];
					 char					yMD[8  +  1];

					 //  MACRO_qnmModulesLoadedInfo	
					 QNM_MODULES_LOADEDINFO	modulesInfo;
					 
					 unsigned  int			nInterval_chk;
					 //
					 unsigned  char			ucbHaveDj;				//  2005/08/27, 是否有单机版

					 unsigned  char			ucbMakeClients;			//  2006/08/16

				 }							cfg;

				 HINSTANCE					hInstResource;

				 struct						{
					 struct					{
						unsigned  char  	ucbCnt;
						unsigned  char  	ucbRegToolDir;
						unsigned  char		ucbDomainCtrl;
						unsigned  char		ucbStopScripts;
						unsigned  char		ucbYMD;			//  2005/08/20

						//  MACRO_qnmModulesLoadedInfo
						QNM_MODULES_LOADEDINFO	modulesLoadedInfo;
						
					 }						changed;
					 unsigned  char			ucbEncInited;
				 }							status;

}		 AWM_CHK;


typedef  struct  __awm_script_access_t  {			
				 BOOL					bAdminsAccessAll;
				 BOOL					bSystemAccessAll;
				 BOOL					bEveryoneAccessRX;
}		AWM_SCRIPT_ACCESS;


typedef  enum  _KINDS_OF_ACCESSMASKS_DECODED  {
    
			   FileAccessMask,
    		   ProcessAccessMask,
    		   WindowStationAccessMask,
    		   DesktopAccessMask,
    		   RegKeyAccessMask,
    		   ServiceAccessMask,
    		   DefaultDaclInAccessTokenAccessMask

}		 KINDS_OF_ACCESSMASKS_DECODED,  *  PKINDS_OF_ACCESSMASKS_DECODED;

// These hold the well-known SIDs


int bAwmChkFiles( AWM_CHK *p );
int  makeClients(  AWM_CHK  *  p  );
int awmChkMain( );
int initAwmChk( AWM_CHK *p );
void exitAwmChk( AWM_CHK *p );
#define		DisplayLastError(  szApi  )		qyDisplayLastError(  szApi  )
int  getAwmChkCfg(  AWM_CHK  *  p  );
int  getAwmChkInitialCfg(  AWM_CHK  *  p  );
int  getNtScriptsCfg(  AWM_CHK  *  p  );
int  getNtBatCfg(  AWM_CHK  *  p  );
int  getWin2kScriptsCfg(  AWM_CHK  *  p  );
int  getQyRegToolCfg(  AWM_CHK  *  p,  int  index  );
int  getQwmAgentCfg(  AWM_CHK  *  p,  int  index  );
int  getScriptsDirAndOthers(  AWM_CHK  *  p,  int  index,  TCHAR  *  dirBuf,  unsigned  int  len,  int  *  piSystemId,  unsigned  char  *  pucbSecChkQuickly,  unsigned  char  *  pucbNoGui,  unsigned  char  *  pucbAssetMgr,  unsigned  char  *  pucbNetMc2,  unsigned  char  *  pucbSecChk,  unsigned  char  *  pucbDj  );





int  warnAndProcess( AWM_CHKED_FILE *p );
void awmLockAndChkFile( AWM_CHK *pAC, AWM_CHKED_FILE *p, int chkedMethod, int *piState );
int  qshSetDigestKey(  AWM_CHK  *  pAc,  int  index  );
extern "C" int showHint( char *hint, char *caption, char type );
void awmUnlockFile( AWM_CHKED_FILE *p );
int  getChkedVal(  char  *  fileName,  char  *  digest,  unsigned  int  *  pLen  );
int  awmChkGetInstallPath(  AWM_CHK  *  p  );
int  awmRecoverFile(  AWM_CHK  *  pAC,  AWM_CHKED_FILE  *  p,  int  index,  int  chkedMethod,  int  *  piState  );
BOOL isAdminsAccessAllAce(  void  *  pAC1,  ACCESS_ALLOWED_ACE  *  paaAllowedAce  );
BOOL isEveryoneRXAce( void *pAC1, ACCESS_ALLOWED_ACE *paaAllowedAce );
BOOL isSystemAccessAllAce( void *pAC1, ACCESS_ALLOWED_ACE *paaAllowedAce );
// BOOL bAddAccessRights( CHAR *pFileName, BOOL bAdminsAccessAll, BOOL bSystemAccessAll, BOOL bEveryoneRX ) ;
BOOL bAddAccessRights( PSID pSid, DWORD accessMask, CHAR *pFileName ) ;
char  *  getBatIp(  AWM_CHK  *  p,  char  *  ip,  unsigned  int  size  );
int getBatContent( char *ip, char *batBuf );
int  outputQwm(  AWM_CHK  *  p,  AWM_CHKED_FILE  *  pScript,  LPCTSTR  tmpFileName  );
int  outputQyRegTool(  AWM_CHK  *  p,  AWM_CHKED_FILE  *  pScript,  int  index,  LPCTSTR  tmpFileName  );
int  outputQyMessengerIni(  AWM_CHK  *  p,  AWM_CHKED_FILE  *  pScript,  LPCTSTR  tmpFileName  );
//  void setAllUsrsScriptPath( const wchar_t *server, char *scriptName );
int setUsrScriptPath( WCHAR *wScriptPath, WCHAR *wUsrName );
BOOL bChkACEsAsAppropriate(PSECURITY_DESCRIPTOR psdFileSD, LPTSTR  lpszFullName, AWM_SCRIPT_ACCESS *pASA );
BOOL bAddACESAsNeeded( PSECURITY_DESCRIPTOR psdFileSD, LPTSTR lpszFullName, AWM_SCRIPT_ACCESS *pASA );


#include	"tmpLib.h"

//  #define		IDR_DATA_qrtForSecChk		IDR_DATA_qrt98		//  2007/02/20
#define		IDR_DATA_qrtForSecChk		IDR_DATA_qrt			//  2010/05/16


#endif /* } */


