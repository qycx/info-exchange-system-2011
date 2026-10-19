

#include	"stdafx.h"
#include	"resource.h"
#include	"newawmChk.h"
#include	<tchar.h> 

#ifndef __DEBUG__
//#error "下面的数据须预定义, 不能从注册表里读!"
#endif

static unsigned char suNtLogonScriptMd5[DEFAULT_DIGEST_LEN] = AWM_NT_LOGON_SCRIPT_DIGEST;
static unsigned char suWin2kStartupScriptMd5[DEFAULT_DIGEST_LEN] = AWM_WIN2K_STARTUP_SCRIPT_DIGEST; 

 int getChkInfoFromFile( char *fileName, unsigned int *pSize, unsigned char *digest )
{
	int iErr = -1;
	FILE *fp = NULL;
	unsigned char buf[1024];
	int fileSize;
	unsigned char *ptr = ( unsigned char * )&fileSize;
	int i;

	fp = fopen( fileName, "rb" );
	if ( !fp ) goto errLabel;
	if ( fread( buf, 8, 1, fp ) != 1 ) goto errLabel;
	for ( i = 0; i < 4; i ++ )
		ptr[i] = buf[i * 2];
	if ( fread( buf, 2 * DEFAULT_DIGEST_LEN, 1, fp ) != 1 ) goto errLabel;
	for ( i = 0; i < DEFAULT_DIGEST_LEN; i ++ )
		digest[i] = buf[i * 2];
	fclose( fp ); fp = NULL;

#ifdef __DEBUG__ // {
	buf[0] = '\0';
	for ( i = 0; i < DEFAULT_DIGEST_LEN; i ++ )
		sprintf( ( char * )buf, "%s%02x", buf, digest[i] );
	debugLog( "digest of %s is [%s]", fileName, buf );
#endif // }

	*pSize = fileSize;

	iErr = 0;

errLabel:

	return iErr;

}


 // 这里增加了对操作系统的判断，以使脚本路径合乎要求。
 int  getScriptsDirAndOthers(  AWM_CHK  *  p,  int  index,  TCHAR  *  dirBuf,  unsigned  int  len,  int  *  piSystemId,  unsigned  char  *  pucbSecChkQuickly,  unsigned  char  *  pucbNoGui,  unsigned  char  *  pucbAssetMgr,  unsigned  char  *  pucbNetMc2,  unsigned  char  *  pucbSecChk,  unsigned  char  *  pucbDj  )
{
	 int				iErr				=	-1;
	 //  char				domainCtrlServerIpBuf[MAX_IP_ADDR_LEN + 1];	//  新加, 2002/12/28
	 int				iSystemId			=	0;
	 unsigned  char		ucbSecChkQuickly	=	FALSE;
	 unsigned  char		ucbNoGui			=	FALSE;
	 unsigned  char		ucbAssetMgr			=	FALSE;
	 unsigned  char		ucbNetMc2			=	FALSE;
	 unsigned  char		ucbSecChk			=	FALSE;
	 unsigned  char		ucbDj				=	FALSE;				//  2005/08/19

	 if  (  !dirBuf  ||  !len  )  goto  errLabel;

	 //  这里有一部分历史遗留问题，
	 /*
	 switch  (  index  )  {
			 case  AWM_NT_LOGON_SCRIPT_INDEX:
			 case  AWM_NT_LOGON_BAT_INDEX:
			 case  AWM_WIN2K_STARTUP_SCRIPT_INDEX:
				   
				   switch  (  p->iPlatformId  )  {
			 			   case  PLATFORM_NT:
							     if  (  getNetLogonLocalPath(  dirBuf  )  )  goto  errLabel;
				   				 break;
			 			   case  PLATFORM_WIN2K:
							     if  (  !getBatIp(  p,  domainCtrlServerIpBuf,  sizeof(  domainCtrlServerIpBuf  )  )  )  goto  errLabel;	//  added on 2002/12/28
				   				 _snprintf(  dirBuf,  len,  "\\\\%s\\netlogon\\",  domainCtrlServerIpBuf  );
				   				 break;
			 			   default:
								   goto  errLabel;					
	 			   }
				   break;
			 case  CONST_qwmBak_index:
			 case  CONST_qrtBak_index:
				   _snprintf(  dirBuf,  len,  "%s",  p->cfg.workDir  );
				   break;
			 default:
					 break;
	 }
	 */

	 _sntprintf(  dirBuf,  len,  _T(  "%s"  ),  p->cfg.regToolDir  );
					
	 switch  (  index  )  {
			 case  CONST_qyRegTool_index:
			 case  CONST_qyRegTool98_index:										//  2005/09/24
			 case  CONST_qyRegTool_x64_index:									//  2010/05/16
				   iSystemId  =  CONST_qySystemId_netMc2;
				   ucbAssetMgr  =  p->cfg.modulesInfo.ulbAssetMgrModuleLoaded;	//  2004/11/15
				   ucbNetMc2  =  p->cfg.modulesInfo.ulbNetMc2ModuleLoaded;		//  2004/11/15
				   break;
			 case  CONST_qrtForNms_index:
			 case  CONST_qrtForNms98_index:										//  2005/09/24
				   iSystemId  =  CONST_qySystemId_nms;
				   ucbAssetMgr  =  p->cfg.modulesInfo.ulbAssetMgrModuleLoaded;
				   break;
			 case  CONST_cPcJbForNms_index:
				   iSystemId  =  CONST_qySystemId_nms;
				   ucbNoGui  =  1;							//  2004/05/18加
				   ucbAssetMgr  =  p->cfg.modulesInfo.ulbAssetMgrModuleLoaded;
				   break;
			 case  CONST_qrtForSecChk_index:
				   iSystemId  =  CONST_qySystemId_secChk;
				   ucbSecChkQuickly  =  1;
				   break;
			 case  CONST_qrtForSecChk1_index:
				   iSystemId  =  CONST_qySystemId_secChk;
				   break;
			 //  case  CONST_qrtForNetMc4_index:
			 //	   iSystemId  =  CONST_qySystemId_netMc4;
			 //	   break;				   
			 case  CONST_qrtForSecChkDj_index:				//  2005/08/19
				   iSystemId  =  CONST_qySystemId_secChk;
				   ucbSecChkQuickly  =  1;
				   ucbDj  =  1;
				   break;
			 case  CONST_qrtForSecChkDj1_index:				//  2005/08/19
				   iSystemId  =  CONST_qySystemId_secChk;
				   ucbDj  =  1;
				   break;
			 case  CONST_qyMessengerIni_index:					//  2007/06/16
				   iSystemId  =  CONST_qySystemId_messenger;
				   break;
			 default:
				    break;
	 }

	 ucbSecChk  =  p->cfg.modulesInfo.ulbSecChkModuleLoaded;		//  2005/05/03
	
	 iErr  =  0;

errLabel:

	 if  (  !iErr  )  {
		 if  (  piSystemId  )  *piSystemId  =  iSystemId;
		 if  (  pucbSecChkQuickly  )  *pucbSecChkQuickly  =  ucbSecChkQuickly;
		 if  (  pucbNoGui  )  *pucbNoGui  =  ucbNoGui;
		 if  (  pucbAssetMgr  )  *pucbAssetMgr  =  ucbAssetMgr;
		 if  (  pucbNetMc2  )  *pucbNetMc2  =  ucbNetMc2;
		 if  (  pucbSecChk  )  *pucbSecChk  =  ucbSecChk;
		 if  (  pucbDj  )  *pucbDj  =  ucbDj;				//  2005/08/19

	 }

	 return  iErr;

}
 
 
/*
 char  gQyCfgs[CONST_qySize_cfgs  +  1]  =  CONST_qyCfgSym
										CONST_qyCfgName_cntIp			"="		DEFAULT_qwmServIp
										" "
										CONST_qyCfgName_cntPort			"="		"8766"
										"\0";
*/

 //  要注意，这个更新的数据区应把原有的数据区覆盖掉，避免由于原有的数据尾巴留存在后面造成数据错误
 //  比如：ip=1.1.1.1 port=808066	
 int  qnmGetUpdateData(  AWM_CHK  *  p,  AWM_CHKED_FILE  *  pScript,  char  *  data,  unsigned  int  size  )
{
	 _snprintf(  data,  size,  "%s=%s %s=%s %s=%s %s=%d %s=%s %s=%d %s=%s %s=%s %s=%s %s=%s %s=%s %s=%s %s=%s                               ",  
							   CONST_qyCfgName_cntIp,  p->cfg.cntCfg.ucbAutoCntIp  ?  p->cfg.cntCfg.cntIp  :  "",
							   CONST_qyCfgName_cntAddr1,  p->cfg.cntCfg.cntAddrs[0],
							   CONST_qyCfgName_cntAddr2,  p->cfg.cntCfg.cntAddrs[1],
							   //  CONST_qyCfgName_cntAddr3,  p->cfg.cntCfg.cntAddrs[2],
							   CONST_qyCfgName_cntPort,  p->cfg.cntCfg.usCntPort,
							   CONST_qyCfgName_qwmSeqNo,  p->cfg.seqNo,
							   CONST_qyCfgName_systemId,  pScript->iSystemId,
							   CONST_qyCfgName_bSecChkQuickly,  pScript->ucbSecChkQuickly  ?  "1"  :  "0",
							   CONST_qyCfgName_bNoGui,	pScript->ucbNoGui  ?  "1"  :  "0",
							   CONST_qyCfgName_bGetPcAsset,  pScript->ucbAssetMgr  ?  "1"  :  "0",
							   CONST_qyCfgName_bNetMc2,  pScript->ucbNetMc2  ?  "1"  :  "0",
							   CONST_qyCfgName_bSecChk,  pScript->ucbSecChk  ?  "1"  :  "0",
							   CONST_qyCfgName_bDj,  pScript->ucbDj  ?  "1"  :  "0",
							   CONST_qyCfgName_yMD,  p->cfg.yMD  );

	 return  0;
} 

 int  outputQwm(  AWM_CHK  *  p,  AWM_CHKED_FILE  *  pScript,  LPCTSTR  tmpFileName  )
{
	 int	iErr							=  -1;
	 char	data[CONST_qySize_cfgs  +  1];

	 if  (  tmpqyOutputResourceFile(  p->hInstResource,  pScript->idrData,  tmpFileName  )  )  goto  errLabel;

#ifndef  _DEBUG
// #error  "must check md5 of qwm"
#endif

	 if  (  qnmGetUpdateData(  p,  pScript,  data,  sizeof(  data  )  )  )  goto  errLabel;
	 if  (  !tmpbQyUpdateImageData(  tmpFileName,  CONST_qyCfgSym,  data,  strlen(  data  )  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:

	 return  iErr;

}


 int  outputQyRegTool(  AWM_CHK  *  p,  AWM_CHKED_FILE  *  pScript,  int  index,  LPCTSTR  tmpFileName  )
{
	 int	iErr							=  -1;
	 char	data[CONST_qySize_cfgs  +  1];

	 if  (  tmpqyOutputResourceFile(  p->hInstResource,  pScript->idrData,  tmpFileName  )  )  {
		 traceLogA(  "outputQyRegTool: 生成文件失败"  );  goto  errLabel;
	 }

#ifndef  _DEBUG
//  #error  "must check md5 of qyRegTool"
#endif

	 if  (  qnmGetUpdateData(  p,  pScript,  data,  sizeof(  data  )  )  )  goto  errLabel;	 
	 if  (  !tmpbQyUpdateImageData(  tmpFileName,  CONST_qyCfgSym_regTool,  data,  strlen(  data  )  )  )  goto  errLabel;
	 if  (  !tmpbQyUpdateImageData(  tmpFileName,  CONST_qyCfgSym,  data,  strlen(  data  )  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:

	 return  iErr;

}


 int  outputQyMessengerIni(  AWM_CHK  *  p,  AWM_CHKED_FILE  *  pScript,  LPCTSTR  tmpFileName  )
{
	int			iErr						=	-1;
	FILE	*	fp							=	NULL;

	fp  =  _tfopen(  tmpFileName,  _T(  "w"  )  );
	if  (  !fp  )  goto  errLabel;
	fclose(  fp  );  fp  =  NULL;

	TCHAR	iniFileName[MAX_PATH  +  1];
	_sntprintf(  iniFileName,  mycountof(  iniFileName  ),  _T(  "%S%S%S"  ),  p->cfg.installDir,  CONST_qyResSubDir,  "qyMessengerMgr.ini"  );				//  2003/09/19
	CopyFile(  iniFileName,  tmpFileName,  FALSE  );

	fp  =  _tfopen(  tmpFileName,  _T(  "a"  )  );
	if  (  !fp  )  goto  errLabel;

	fprintf(  fp,  "\n"  );
	fprintf(  fp,  "\n"  );
	fprintf(  fp,  "\n"  );

	fprintf(  fp,  "%s\t%s\n",	CONST_qyCfgName_cntIp,  p->cfg.cntCfg.ucbAutoCntIp  ?  p->cfg.cntCfg.cntIp  :  ""  );
	fprintf(  fp,  "%s\t%s\n",	CONST_qyCfgName_cntAddr1,  p->cfg.cntCfg.cntAddrs[0]  );
	fprintf(  fp,  "%s\t%s\n",	CONST_qyCfgName_cntAddr2,  p->cfg.cntCfg.cntAddrs[1]  );
	//  fprintf(  fp,  "%s\t%s\n",	CONST_qyCfgName_cntAddr3,  p->cfg.cntCfg.cntAddrs[2]  );
	fprintf(  fp,  "%s\t%d\n",  CONST_qyCfgName_cntPort,  p->cfg.cntCfg.usCntPort  );

	iErr  =  0;
errLabel:
	if  (  fp  )  fclose(  fp  );
	return  iErr;
}

 
 int  getQwmDigest(  AWM_CHK  *  p,  AWM_CHKED_FILE	 *  pScript  )
{
	 int	iErr							=  -1;
	 /*
	 char	tmpPath[MAX_PATH  +  1];
	 char	tmpFileName[MAX_PATH  +  1];
	 BOOL	bDel							=  FALSE;
	 
	 if  (  !GetTempPath(  sizeof(  tmpPath  ),  tmpPath  )  )  goto  errLabel;
	 if  (  !GetTempFileName(  tmpPath,  "wrd",  0,  tmpFileName  )  )  goto  errLabel;
	 bDel  =  TRUE;

	 if  (  outputQwm(  p,  pScript,  tmpFileName  )  )  goto  errLabel;

	 pScript->size  =  getFileLen(  tmpFileName  );
	 pScript->digestLen  =  sizeof(  pScript->digest  );
	 if  (  !bQyGetFileMd5(  tmpFileName,  pScript->digest,  &pScript->digestLen  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:

	 if  (  bDel  )  DeleteFile(  tmpFileName  );

  	 return  iErr;
*/

	 return  0;

}

 int  getQyRegToolDigest(  AWM_CHK  *  p,  AWM_CHKED_FILE	 *  pScript,  int  index  )
{
	 int	iErr							=  -1;
	/*
	 char	tmpPath[MAX_PATH  +  1];
	 char	tmpFileName[MAX_PATH  +  1];
	 BOOL	bDel							=  FALSE;
	 
	 if  (  !GetTempPath(  sizeof(  tmpPath  ),  tmpPath  )  )  goto  errLabel;
	 if  (  !GetTempFileName(  tmpPath,  "wrd",  0,  tmpFileName  )  )  goto  errLabel;
	 bDel  =  TRUE;

	 if  (  outputQyRegTool(  p,  pScript,  index,  tmpFileName  )  )  goto  errLabel;

	 pScript->size  =  getFileLen(  tmpFileName  );
	 pScript->digestLen  =  sizeof(  pScript->digest  );
	 if  (  !bQyGetFileMd5(  tmpFileName,  pScript->digest,  &pScript->digestLen  )  )  goto  errLabel;

	 iErr  =  0;

errLabel:

	 if  (  bDel  )  DeleteFile(  tmpFileName  );

  	 return  iErr;
*/

	 return  0;
}



 int  getNtScriptsCfg(  AWM_CHK  *  p  )
{
	int					iErr		=	-1;
	AWM_CHKED_FILE	*	pScript		=	NULL;
	int					index		=	AWM_NT_LOGON_SCRIPT_INDEX;

	traceLogA(  "getNtScriptsCfg( ) enters."  );

	if  (  !p  ||  !p->pScripts[index]  )  return  -1;

	pScript  =  p->pScripts[index];
	
	if  (  getScriptsDirAndOthers(  p,  index,  pScript->dir,  mycountof(  pScript->dir  ),  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL  )  )  goto  errLabel;			//  Modified on 2002/12/28 
	lstrcpyn(  pScript->fileName,  _T(  AWM_NT_LOGON_SCRIPT_NAME  ),  mycountof(  pScript->fileName  )  );
	if  (  !tmpqyGetFullPath(  pScript->dir,  pScript->fileName,  pScript->fullPathName,  mycountof(  pScript->fullPathName  )  )  )
		goto  errLabel;

	//  if  (  getQwmDigest(  p,  pScript  )  )  goto  errLabel;
	
	iErr  =  0;

errLabel:

	traceLogA( "getNtScriptsCfg( ) leaves." );
  
	return iErr;

}

 int  getBatContent(  char  *  ip,  char  *  batBuf  )
{
	sprintf( batBuf, "echo off\r\n" );
	sprintf( batBuf, "%s\\\\%s\\Netlogon\\%s\r\n", batBuf, ip,  CONST_qwmLogonScriptName  );
	return 0;
	
}

 char  *  getBatIp(  AWM_CHK  *  p,  char  *  ip,  unsigned  int  size  )
{
	 return  qnmBatIp(  ip,  size  );
}

 /*
 int  getNtBatCfg(  AWM_CHK  *  p  )
{
	int					iErr		=	-1;
	AWM_CHKED_FILE  *	pScript		=	NULL;
	char				domainCtrlServerIpBuf[MAX_IP_ADDR_LEN + 1];
	FILE			*	fp			=	NULL;
	int					index		=	AWM_NT_LOGON_BAT_INDEX;	

	if  (  !getBatIp(  p,  domainCtrlServerIpBuf,  sizeof(  domainCtrlServerIpBuf  )  )  )  goto  errLabel;

	pScript = p->pScripts[index];
	if ( getBatContent( domainCtrlServerIpBuf, pScript->digest ) ) goto errLabel;
	pScript->digestLen = strlen( pScript->digest );
	pScript->size = strlen( pScript->digest );

	if  (  getScriptsDirAndOthers(  p,  index,  pScript->dir,  sizeof(  pScript->dir  ),  NULL,  NULL,  NULL,  NULL,  NULL,  NULL,  NULL  )  )  goto  errLabel;
	strcpy( pScript->fileName, AWM_NT_LOGON_BAT_NAME );
	if ( !asrGetFullPath( pScript->dir, pScript->fileName, pScript->fullPathName, sizeof( pScript->fullPathName ) ) )
		goto errLabel;
	DeleteFile( pScript->fullPathName );
	fp = fopen( pScript->fullPathName, "wb" );
	if ( !fp ) goto errLabel;
	if ( 1 != fwrite( pScript->digest, pScript->size, 1, fp ) ) goto errLabel;
	fclose( fp ); fp = NULL;

	iErr = 0;

errLabel:

	if  (  fp  )  fclose(  fp  ); 

	return iErr;

}
*/

 QY_DMITEM		CONST_qwmScriptTable[]  =
{
	{		AWM_NT_LOGON_SCRIPT_INDEX,			_T(  ""  ),											},
	{		AWM_NT_LOGON_BAT_INDEX,				_T(  ""  ),											},
	{		AWM_WIN2K_STARTUP_SCRIPT_INDEX,		_T(  ""  ),											},
	{		CONST_qyRegTool_index,				_T(  "qyRegTool_win32.exe"  ),						},		//  for netMc2
	{		CONST_qwmBak_index,					_T(  ""  ),											},
	{		CONST_qrtBak_index,					_T(  ""  ),											},
	{		CONST_qrtForNms_index,				_T(  "dengJi.exe"  ),								},		//  for nms
	{		CONST_cPcJbForNms_index,			_T(  "cPcJb.exe"  ),								},		//  for nms 查PC脚本
	{		CONST_qrtForSecChk_index,			_T(  "jianCha.exe"  ),								},		//	for secChk
	{		CONST_qrtForSecChk1_index,			_T(  "jianCha1.exe"  ),								},		//	for secChk
	//
	{		CONST_qyRegTool_x64_index,			_T(  "qyRegTool_x64.exe"  ),						},
	//
	{		CONST_qnmCgi_index,					_T(  "qnm.cgi"  ),									},		//  2005/02/02
	{		CONST_qrtForSecChkDj_index,			_T(  CONST_finalName_qrtForSecChkDj  ),				},		//  2005/08/19
	{		CONST_qrtForSecChkDj1_index,		_T(  CONST_finalName_qrtForSecChkDj1  ),			},		//  2005/08/19
	{		CONST_myCapture_index,				_T(  "myCapture.exe"  ),							},
	{		CONST_qyRegTool98_index,			_T(  "qyRegTool98.exe"  ),							},		//  98版的注册工具
	{		CONST_qrtForNms98_index,			_T(  "dengJi98.exe"  ),								},		//  98版的登记工具
	//
	{		CONST_qyMessengerIni_index,			_T(  "qyMessenger.ini"  ),							},
	{		CONST_qyMessengerSplash_index,		_T(  "qyMessengerSplash.bmp"  ),				},
	{		CONST_qyMessengerMsi_index,			_T(  "qyMessenger.msi"  ),							},
	{		CONST_qyMessengerSetup_index,		_T(  "setup.exe"  ),							},

	{		-1,									NULL,										},
};


 int  getQyRegToolCfg(  AWM_CHK  *  p,  int  index  )
{
	int					iErr		=	-1;
	AWM_CHKED_FILE	*	pScript		=	NULL;
	
	if  (  !p  ||  !p->pScripts[index]  )  return  -1;

	pScript  =  p->pScripts[index];

	if  (  getScriptsDirAndOthers(  p,  index,  pScript->dir,  mycountof(  pScript->dir  ),  &pScript->iSystemId,  &pScript->ucbSecChkQuickly,  &pScript->ucbNoGui,  &pScript->ucbAssetMgr,  &pScript->ucbNetMc2,  &pScript->ucbSecChk,  &pScript->ucbDj  )  )  goto  errLabel;
	//  _snprintf(  pScript->fileName,  sizeof(  pScript->fileName  ),  "%s",  qyGetRegToolAppName(  )  );
	_sntprintf(  pScript->fileName,  mycountof(  pScript->fileName  ),  _T(  "%s"  ),  qyGetDesByType1(  CONST_qwmScriptTable,  index  )  );
	if  (  !tmpqyGetFullPath(  pScript->dir,  pScript->fileName,  pScript->fullPathName,  mycountof(  pScript->fullPathName  )  )  )  goto  errLabel;
	//  if  (  getQyRegToolDigest(  p,  pScript,  index  )  )  goto  errLabel;
		
	iErr  =  0;

errLabel:
	
	return  iErr;

}


 int  getQwmAgentCfg(  AWM_CHK  *  p,  int  index  )
{
	int					iErr		=	-1;
	AWM_CHKED_FILE	*	pScript		=	NULL;
	
	if  (  !p  ||  !p->pScripts[index]  )  return  -1;

	pScript  =  p->pScripts[index];

	if  (  getScriptsDirAndOthers(  p,  index,  pScript->dir,  mycountof(  pScript->dir  ),  &pScript->iSystemId,  NULL,  NULL,  &pScript->ucbAssetMgr,  &pScript->ucbNetMc2,  &pScript->ucbSecChk,  &pScript->ucbDj  )  )  goto  errLabel;
	//  strcpy(  pScript->fileName,  AWM_WIN2K_STARTUP_SCRIPT_NAME  );
	_sntprintf(  pScript->fileName,  mycountof(  pScript->fileName  ),  _T(  "%s"  ),  qyGetDesByType1(  CONST_qwmScriptTable,  index  )  );
	if  (  !tmpqyGetFullPath(  pScript->dir,  pScript->fileName,  pScript->fullPathName,  mycountof(  pScript->fullPathName  )  )  )  goto  errLabel;
	if  (  getQwmDigest(  p,  pScript  )  )  goto  errLabel;

	iErr = 0;

errLabel:
	
	return iErr;

}


 // 此函数提供计算hFile代表的文件的校验植
 // 须好好选用算法.

 int getChkedVal(  char  *  fileName, char  *  digest,  unsigned  int  *  pLen  )
{
	if  (  !bQyGetFileMd5(  fileName,  digest,  pLen  )  )  return  -1;
	return 0;
}


 int getNtBatBuf( char *fileName, char *batBuf, int *pSize )
{
	int iErr = -1;
	FILE *fp = NULL;
	char buf[1024];
	int len;

	fp = fopen( fileName, "r" );
	if ( !fp ) return -1;
	len = fread( buf, 1, sizeof( buf ), fp );
	if ( len == sizeof( buf ) ) goto errLabel;
	if ( *pSize > len ) *pSize = len;
	memcpy( batBuf, buf, *pSize );

	iErr = 0;

errLabel:
	if ( fp ) fclose( fp );
	return iErr;
	
}


