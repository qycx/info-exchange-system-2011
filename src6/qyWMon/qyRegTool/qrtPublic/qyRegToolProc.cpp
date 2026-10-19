
#include	<windows.h>
#include	<lmcons.h>
#include	<iphlpapi.h>
#include	<tchar.h>
#include	"qyRegToolCommon.h"


char  gQyCfgs[CONST_qySize_cfgs  +  1]  =  CONST_qyCfgSym_regTool
										CONST_qyCfgName_cntIp			"="		DEFAULT_qwmServIp
										" "
										CONST_qyCfgName_cntAddr1		"="		"188.188.188.29"
										" "
										CONST_qyCfgName_cntAddr2		"="		"www.qycx.com"
										" "
										//  CONST_qyCfgName_cntAddr3		"="		"mail.qycx.com"
										//  " "
										CONST_qyCfgName_cntPort			"="		"8766"
										" "
										CONST_qyCfgName_systemId		"="		"7"
										" "
										CONST_qyCfgName_bSecChkQuickly	"="		"0"
										" "
										CONST_qyCfgName_bNoGui			"="		"0"				//  cpcjb
										" "
										CONST_qyCfgName_bGetPcAsset		"="		"1"				//  
										" "
										CONST_qyCfgName_bDj				"="		"0"				//  2005/08/17
										" "
										CONST_qyCfgName_yMD				"="		"20090406"		//  单机版可以运行的日期
										"\0";




char	gQwmDigest[CONST_qyMd5Len  +  1]  =  AWM_WIN2K_STARTUP_SCRIPT_DIGEST;






 //  size  ==  0  时，则不对pQyCfgs长度作出限制
 int  qrtParseCfgs(  QY_REG_TOOL  *  pWMon  )
{
	 int				iErr		=	-1;
	 char			*	p			=	NULL;
	 char				buf[1024];
	 char			*	pQyCfgs		=	gQyCfgs;
	 unsigned  int		size		=	sizeof(  gQyCfgs  );

	 traceLogA(  "qrtParseCfgs: pQyCfgs is [%s]",  pQyCfgs  );

	 if  (  size  )  {
		 if  (  strlen(  pQyCfgs  )  >=  (  int  )size   )  return  -1;
	 }

	 safeStrnCpy(  DEFAULT_qyCfgVal_cntIp,  pWMon->cfg.cnt.ip,  sizeof(  pWMon->cfg.cnt.ip  )  );
	 pWMon->cfg.cnt.port  =  DEFAULT_qyCfgVal_cntPort;
	 pWMon->cfg.iSystemId_wanted  =  qyGetSystemId(  );	//  2005/09/24

	 //  2006/07/01, 取管理端地址
	 if  (  parseQwmDynCfg(  pQyCfgs,  size,  &pWMon->cfg.dynCfg  )  )  goto  errLabel;
	 
	 //  2006/07/01注，在以后的版本中，将不再完全靠指定IP来进行，所以cnt.ip和cnt.port将利用dynCfg中的数据来调整
	 //  try to get cnt
	 /*
	 p  =  qwmGetCfg(  pQyCfgs,  CONST_qyCfgName_cntIp,  buf,  sizeof(  buf  )  );
	 if  (  p  )  {
		 if  (  inet_addr(  p  )  !=  INADDR_NONE  )  {
			 safeStrnCpy(  buf,  pWMon->cfg.cnt.ip,  sizeof(  pWMon->cfg.cnt.ip  )  );		 
		 }
	 }		 
	 p  =  qwmGetCfg(  pQyCfgs,  CONST_qyCfgName_cntPort,  buf,  sizeof(  buf  )  );
	 if  (  p  )  {
		 pWMon->cfg.cnt.port  =  (  unsigned  short  )atol(  buf  );
	 }
	 */
	 if  (  bIpValid(  pWMon->cfg.dynCfg.cnt.cntIp  )  )  safeStrnCpy(  pWMon->cfg.dynCfg.cnt.cntIp,  pWMon->cfg.cnt.ip,  sizeof(  pWMon->cfg.cnt.ip  )  );
	 pWMon->cfg.cnt.port  =  pWMon->cfg.dynCfg.cnt.usCntPort;
	 
	 //  2005/09/24
	 p  =  qwmGetCfg(  pQyCfgs,  CONST_qyCfgName_systemId,  buf,  sizeof(  buf  )  );
	 if  (  p  )  {
		 pWMon->cfg.iSystemId_wanted  =  (  unsigned  short  )atol(  buf  );
	 }

	 p  =  qwmGetCfg(  pQyCfgs,  CONST_qyCfgName_bSecChkQuickly,  buf,  sizeof(  buf  )  );
	 if  (  p  )  {
		 pWMon->cfg.ucbSecChkQuickly  =  (  unsigned  char  )atol(  buf  );
	 }

	 //  2004/05/14增加
	 p  =  qwmGetCfg(  pQyCfgs,  CONST_qyCfgName_bNoGui,  buf,  sizeof(  buf  )  );
	 if  (  p  )  {
		 pWMon->cfg.ucbNoGui  =  (  unsigned  char  )atol(  buf  );
	 }

	 //  2004/07/26
	 p  =  qwmGetCfg(  pQyCfgs,  CONST_qyCfgName_bGetPcAsset,  buf,  sizeof(  buf  )  );
	 if  (  p  )  {
		 pWMon->cfg.ucbGetPcAsset  =  (  unsigned  char  )atol(  buf  );
	 }

	 //  2005/08/17
	 p  =  qwmGetCfg(  pQyCfgs,  CONST_qyCfgName_bDj,  buf,  sizeof(  buf  )  );
	 if  (  p  )  {
		 pWMon->cfg.ucbDj  =  (  unsigned  char  )atol(  buf  );
	 }

	 //  2005/08/20
	 p  =  qwmGetCfg(  pQyCfgs,  CONST_qyCfgName_yMD,  buf,  sizeof(  buf  )  );
	 if  (  p  )  {
		 safeStrnCpy(  p,  pWMon->cfg.yMD,  sizeof(  pWMon->cfg.yMD  )  );  
	 }

	 iErr  =  0;	  

errLabel:

	 return  iErr;

 } 
  
 
 /*
 DWORD  WINAPI  qyProcessRegThreadProc(  LPVOID  lpParameter  )

 int  getHintFromServ(  QY_REG_TOOL  *  pQrt  )

 int  regToServ(  QY_REG_TOOL  *  pQrt  )


*/

