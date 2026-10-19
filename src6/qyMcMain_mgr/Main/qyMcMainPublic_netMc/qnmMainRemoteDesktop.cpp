
#include	"stdafx.h"
#include	<atlimage.h>
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyWmComm.h"

#include	"myresource.h"
#include	"dlgDesktopsMon_mgr.h"
#include	"qyCusResTemp.h"
#include	"qyPs.h"


//  注意：这里的定义应该和qwmRdCnt里统一起来，不要分开定义
#define		DAEMON_CLASS_NAME		_T(  "VNCviewer Daemon"  )
#define		CONST_appName_qwmRdCnt	(  "qwmRdCnt.exe"  )








 int  viewRemoteDesktop(  void  *  pDb,  void  *  p1,  char  *  mac0,  unsigned  char  ucbMonDesktop  )
{
	  
	 int						iRet						=		-1;
	 QY_MC					*	pQyMc						=		QY_GET_GBUF(  );
	 TCHAR						tmpExeName[MAX_PATH  +  1]	=		_T(  ""  );
	 STARTUPINFO				si;
	 PROCESS_INFORMATION		pi;
	 BOOL						bProcessCreated				=		FALSE;
	 TCHAR						sqlBuf[CONST_maxSqlBufLen  +  1];
	 char						timeBuf[CONST_qyTimeLen  +  1];
	 //
	 unsigned  char				ucMonDesktopIntervalInS		=		5;			//  假设是5秒一桢
	 	 
	 if  (  !bMacValid(  mac0  )  )  goto  errLabel;
	 
	 getCurTime(  timeBuf  );

	 if  (  pQyMc->cfg.ucbRemoteDesktopSupported  )  {
	 
		 if  (  !FindWindow(  DAEMON_CLASS_NAME,  NULL  )  )  {
			 traceLogA(  "qwmRcCnt不存在，将启动远程桌面管理器"  );

			 memset(  &si,  0,  sizeof(  si  )  );
			 memset(  &pi,  0,  sizeof(  pi  )  );
		 
			 traceLogA(  "Now start qwm "  );
			 memset(  &si,  0,  sizeof(  STARTUPINFO  )  );
	 		 si.cb  =  sizeof(  STARTUPINFO  );
	 		 si.dwFlags  =  STARTF_FORCEOFFFEEDBACK;
	 
			 _sntprintf(  tmpExeName,  mycountof(  tmpExeName  ),  _T(  "%sbin\\%s"  ),  pQyMc->cfg.installDir,  CString(  CONST_appName_qwmRdCnt  )  );
			 if  (  tQyQuoteFileName(  tmpExeName,  mycountof(  tmpExeName  )  )  )  goto  errLabel;
	 
			 if  (  !CreateProcess(  NULL,  CString(  tmpExeName  ).GetBuffer(  0  ),  NULL,  NULL,  0,  0,  NULL,  NULL,  &si,  &pi  )  )  goto  errLabel;
			 bProcessCreated  =  TRUE;
			 traceLogA(  "CreateProcess %S succeeded,  new processId is %d,  new threadId is %d.",  tmpExeName,  pi.dwProcessId,  pi.dwThreadId  );

		 }

	 }



	 //  设置操作标志位，qyPcStatusTab
	 if  (  setPcOpStatus(  pDb,  mac0,  TRUE  )  )  goto  errLabel;

	 //  添加查看远程桌面的指令
	 _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "insert into qyPcOpQTab (mac0,iCmd,iStatus,startTime) values('%s',%d,%d,'%s')"  ),  CString(  mac0  ),  ucbMonDesktop  ?  CONST_opCmd_monDesktop  :  CONST_opCmd_viewRemoteDesktop,  CONST_cmdStatus_start,  CString(  timeBuf  )  );
	 if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;

	 //  Sleep(  500  );

	 //  2006/12/10, 刷新管理队列
	 myREFRESHED_PCOPCMD	tmpPcOpCmd;
	 memset(  &tmpPcOpCmd,  0,  sizeof(  tmpPcOpCmd  )  );
	 safeStrnCpy(  mac0,  tmpPcOpCmd.mac,  sizeof(  tmpPcOpCmd.mac  )  );
	 tmpPcOpCmd.getOpCmd.ucbOped  =  TRUE;
	 tmpPcOpCmd.getOpCmd.ucbViewRemoteDesktop  =  !ucbMonDesktop;
	 tmpPcOpCmd.getOpCmd.ucbMonDesktop  =  ucbMonDesktop  ?  ucMonDesktopIntervalInS  :  0;		//  这个参数还起了携带屏幕间隔的作用。切记。2008/02/17

	 if  (  qnmTellPolicyChangedEx_netMc(  0,  &tmpPcOpCmd  )  )  goto  errLabel;

	 iRet  =  0;

errLabel:

	 if  (  bProcessCreated  )  {
		 if  (  pi.hThread  )  {  CloseHandle(  pi.hThread  );  pi.hThread  =  NULL;  }
		 if  (  pi.hProcess  )  {  CloseHandle(  pi.hProcess  );  pi.hProcess  =  NULL;	}
	 }


	  return  0;
}


 int  cancelRemoteDesktop(  void  *  pDb,  void  *  p1,  char  *  mac0,  unsigned  char  ucbMonDesktop  )
{
	 int		iErr		=		-1;

	 if  (  !bMacValid(  mac0  )  )  goto  errLabel;

	 setRemoteDesktopCanceled(  pDb,  p1,  mac0,  ucbMonDesktop  );

	 myREFRESHED_PCOPCMD	tmpPcOpCmd;
	 memset(  &tmpPcOpCmd,  0,  sizeof(  tmpPcOpCmd  )  );
	 safeStrnCpy(  mac0,  tmpPcOpCmd.mac,  sizeof(  tmpPcOpCmd.mac  )  );

	 //  2006/12/10, 刷新管理队列
	 if  (  qnmTellPolicyChangedEx_netMc(  0,  &tmpPcOpCmd  )  )  goto  errLabel;

	 iErr  =  0;
errLabel:
	 return  iErr;
}


 int  getMonPicsCfg(  unsigned  short  *  pusCnt_monPics_row,  unsigned  short  *  pusCnt_monPics_col  )
{
	char	*	pRegVal;
	char		buf[128];
	unsigned  long		usCnt_monPics_row	=  0;
	unsigned  long		usCnt_monPics_col	=  0;
	int					nTotal				=	0;

	pRegVal  =  CONST_regValName_monPics_row;
	if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  CString(  pRegVal  ),  buf,  sizeof(  buf  )  )  )  {
		trim(  buf  );
		usCnt_monPics_row  =  atol(  buf  );
	}
	pRegVal  =  CONST_regValName_monPics_col;
	if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  CString(  pRegVal  ),  buf,  sizeof(  buf  )  )  )  {
		trim(  buf  );
		usCnt_monPics_col  =  atol(  buf  );
	}

	nTotal  =  usCnt_monPics_row  *  usCnt_monPics_col;
	if  (  !nTotal  ||  nTotal  >  CONST_maxMonedDesktops  )  {
		usCnt_monPics_row	=	2;
		usCnt_monPics_col  =  2;
	}

	if  (  pusCnt_monPics_row  )  *  pusCnt_monPics_row  =  (  unsigned  short  )usCnt_monPics_row;
	if  (  pusCnt_monPics_col  )  *  pusCnt_monPics_col  =  (  unsigned  short  )usCnt_monPics_col;

	return  0;
}


 int  chkCapScreenDir(  )
{
	int						iErr		=		-1;
	QY_MC				*	pQyMc		=		QY_GET_GBUF(  );
	TCHAR				*	pRegVal;
	TCHAR					buf[1024]	=		_T(  ""  );
	CQyString				path;

	pRegVal  =  _T(  CONST_regValName_capScreenDir  );
	if  (  !qyGetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  pRegVal,  (  char  *  )buf,  sizeof(  buf  )  )  )  {
		tTrim(  buf  );
		//  _snprintf(  m_var.capScreenDir,  sizeof(  m_var.capScreenDir  ),  "%s",  buf  );
		if  (  bDir(  buf  )  )  {
			iErr  =  0;  goto  errLabel;
		}
	}

	qyBrowseForDir(  NULL,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_selectFolder  ),  buf,  path  );
	if  (  !path.GetLength(  )  )  goto  errLabel;
	
	qySetRegCfg(  _T(  CONST_qyRootKey_qnmScheduler  ),  pRegVal,  path.GetBuffer(  0  )  );

	iErr  =  0;
errLabel:
	return  iErr;
}


 int  startDesktopMon(  void  *  p0,  char  *  mac0,  LPCTSTR  displayName  )
{
	int						iErr		=		-1;
	QY_MC				*	pQyMc		=		QY_GET_GBUF(  );
	QY_SERVICEGUI_INFO	*	pSci		=		getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_netMc  );
	if  (  !pSci  )  return  -1;
	MC_VAR_netMc		*	pVar		=		(  MC_VAR_netMc  *  )pSci->pVar;
	if  (  !pVar  )  return  -1;
	CDlgDesktopsMon		*	pDlg		=		NULL;
	RECT					rect;
	int						i;

	if  (  !bMacValid(  mac0  )  )  return  -1;

	//  2008/03/26, 检查屏幕拷贝存储目录，无则要求设置。
	if  (  chkCapScreenDir(  )  )  return  -1;

	for  (  i  =  0;  i  <  mycountof(  pVar->monedDesktops  );  i  ++  )  {	//  寻找，是否已经是被监控了
		 if  (  !pVar->monedDesktops[i].mac0[0]  )  continue;
		 if  (  !stricmp(  pVar->monedDesktops[i].mac0,  mac0  )  )  break;
	}
	if  (  i  ==  mycountof(  pVar->monedDesktops  )  )  {						//  如果没有找到。则找个空的位置
		for  (  i  =  0;  i  <  mycountof(  pVar->monedDesktops  );  i  ++  )  {
			if  (  !pVar->monedDesktops[i].mac0[0]  )  break;			
		}
		//
		if  (  i  ==  mycountof(  pVar->monedDesktops  )  )  {
			qyShowHint(  _T(  "%s is %d"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_monPics  ),  mycountof(  pVar->monedDesktops  )  );
			goto  errLabel;
		}
		//  新增监控
		safeStrnCpy(  mac0,  pVar->monedDesktops[i].mac0,  mycountof(  pVar->monedDesktops[i].mac0  )  );
		safeWcsnCpy(  displayName,  pVar->monedDesktops[i].displayName,  mycountof(  pVar->monedDesktops[i].displayName  )  );
		//
		pVar->usCnt_monPcs  ++  ;
		//
	}

	if  (  !pVar->hDlgDesktopsMon  ||  !IsWindow(  pVar->hDlgDesktopsMon  )  )  {
		unsigned  short		usCnt_monPics_row	=	0;
		unsigned  short		usCnt_monPics_col	=	0;
		//
		pDlg  =  new  CDlgDesktopsMon;
		if  (  !pDlg  )  goto  errLabel;
		getMonPicsCfg(  &usCnt_monPics_row,  &usCnt_monPics_col  );
		//  if  (  !pDlg->bSetDlgInfo(  0,  0,  usCnt_monPics_row,  usCnt_monPics_col,  0,  0  )  )  goto  errLabel;
		if  (  !pDlg->bSetDlgInfo(  0,  0,  0,  usCnt_monPics_row,  usCnt_monPics_col,  0,  0  )  )  goto  errLabel;
		if  (  !pDlg->Create(  rect  )  )  goto  errLabel;		
		//
		pDlg->ShowWindow(  SW_SHOW  );
		//
		pVar->hDlgDesktopsMon  =  pDlg->m_hWnd;	 pDlg  =  NULL;
	}

	iErr  =  0;

errLabel:
	if  (  pDlg  )  delete  pDlg;
	return  iErr;
}


 int  stopDesktopMon(  void  *  p0,  char  *  mac0,  void  *  p2  )
{
	int						iErr		=		-1;
	QY_MC				*	pQyMc		=		QY_GET_GBUF(  );
	QY_SERVICEGUI_INFO	*	pSci		=		getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_netMc  );
	if  (  !pSci  )  return  -1;
	MC_VAR_netMc		*	pVar		=		(  MC_VAR_netMc  *  )pSci->pVar;
	if  (  !pVar  )  return  -1;
	CDlgDesktopsMon		*	pDlg		=		NULL;
	int						i;
	BOOL					bFound		=		FALSE;

	if  (  !bMacValid(  mac0  )  )  return  -1;

	for  (  i  =  0;  i  <  mycountof(  pVar->monedDesktops  );  i  ++  )  {	//  寻找，是否已经是被监控了
		 if  (  !pVar->monedDesktops[i].mac0[0]  )  continue;
		 if  (  !stricmp(  pVar->monedDesktops[i].mac0,  mac0  )  )  {			//  找到所有的MAC0都清空
			 memset(  &pVar->monedDesktops[i],  0,  sizeof(  pVar->monedDesktops[i]  )  );
			 bFound  =  TRUE;
		 }
	}
	//
	if  (  bFound  )  pVar->usCnt_monPcs  --  ;

	iErr  =  0;
//  errLabel:
	return  iErr;
}

#if  10  //  2013/01/17
 int  myGetImageInfo_netMc(	unsigned  char  ucbFixedSize,			//  固定大小
						int  iW_image,  int  iH_image,  
						int  iX,  int  iY,  unsigned  int  iW,  unsigned  int  iH,  
						int  *  piX_image,  int  *  piY_image,  unsigned  int  *  piW_image,  unsigned  int  *  piH_image  )
{
	double	f;

	if  (  !piX_image  ||  !piY_image  ||  !piW_image  ||  !piH_image  )  return  -1;
	if  (  !iW_image  ||  !iH_image  )  return  -1;

	if  (  ucbFixedSize  )  {					//  不能放大缩小
		if  (  iW_image  >  (  int  )iW  )  *piX_image  =  0;  
		else  *piX_image  =  iX  +  (  iW  -  iW_image  )  /  2;
		
		if  (  iH_image  >  (  int  )iH  )  *piY_image  =  0;  
		else  *  piY_image  =  iY  +  (  iH  -  iH_image  )  /  2;

		*piW_image  =  iW_image;
		*piH_image  =  iH_image;
		return  0;
	}

	f  =  iW_image  /  (  iH_image  *  1.  );
	if  (  f  *  iH  >  iW  )  {				//  太窄
		*piW_image  =  iW;
		*piH_image  =  (  int  )(  iW  /  f  );
		*piX_image  =  iX;
		*piY_image  =  (  int  )(  iY  +  (  iH  -  *piH_image  )  /  2.  );
		return  0;
	}

	//  太宽
	*piH_image  =  iH;
	*piW_image  =  (  int  )(  iH  *  f  );
	*piY_image  =  iY;
	*piX_image  =  (  int  )(  iX  +  (  iW  -  *piW_image  )  /  2.  );

	return  0;
}
#endif

extern  QY_DMITEM  CONST_monIdcTable[];

 int  tmpHandler_threadRefreshMonedDesktops(  MC_VAR_netMc  *  pVar,  LPCTSTR  cfgName,  LPCTSTR  cfgVal  )
{
	int			iErr						=	-1;
	TCHAR		tBuf[1024]					=	_T(  ""  );
	char		mac0[CONST_qyMacLen  +  1]	=	"";
	TCHAR		wUsrDomain[512  +  1]		=	_T(  ""  );
	char		timeBuf[128]				=	"";
	TCHAR	*	pT;
		
	safeWcsnCpy(  cfgName,  tBuf,  mycountof(  tBuf  )  );
	if  (  (  pT  =  _tcschr(  tBuf,  _T(  '-'  )  )  )  )  {
		*pT  =  0;  pT  ++  ;
		myTChar2Str(  tBuf,  mac0,  mycountof(  mac0  )  );
	}
	safeWcsnCpy(  pT,  wUsrDomain,  mycountof(  wUsrDomain  )  );
	if  (  (  pT  =  _tcsrchr(  wUsrDomain,  _T(  '-'  )  )  )  )  {
		*pT  =  0;  pT  ++  ;
		myTChar2Str(  pT,  timeBuf,  mycountof(  timeBuf  )  );
	}
	tTrim(  wUsrDomain  );
	//
	if  (  bMacValid(  mac0  )  &&  bQyTimeValid(  timeBuf  )  )  {
		CImage					img;
		HRESULT					hResult;
		int						idc_pic;
		int						idc_static;
		HWND					hCtrl		=	NULL;
		int						i;
		QY_DMITEM			*	pItem;
		RECT					rect;
		HDC						hDc_ctrl;
		char					buf[256]	=	"";
		//
		for  (  i  =  0;  i  <  mycountof(  pVar->monedDesktops  );  i  ++  )  {
			 if  (  !stricmp(  pVar->monedDesktops[i].mac0,  mac0  )  
				 &&  !_tcsicmp(  pVar->monedDesktops[i].wUsrDomain,  wUsrDomain  )  )  
			 {
				 break;
			 }
		}
		if  (  i  ==  mycountof(  pVar->monedDesktops  )  )  {	//  没找到正合适的．那么看有没有ＭＡＣ一样的
			for  (  i  =  0;  i  <  mycountof(  pVar->monedDesktops  );  i  ++  )  {
				 if  (  !stricmp(  pVar->monedDesktops[i].mac0,  mac0  )  )  break;
			}
			if  (  i  ==  mycountof(  pVar->monedDesktops  )  )  goto  errLabel;	//  没找到匹配的
			//
			safeWcsnCpy(  wUsrDomain,  pVar->monedDesktops[i].wUsrDomain,  mycountof(  pVar->monedDesktops[i].wUsrDomain  )  );
			//
		}
		//
		if  (  !(  pItem  =  qyGetDmItemByType(  CONST_monIdcTable,  i,  sizeof(  QY_DMITEM  )  )  )  )  goto  errLabel;
		idc_pic  =  (  int  )pItem->des;
		idc_static  =  (  int  )pItem->pData;
		//
		hResult  =  img.Load(  cfgVal  );
		if  (  FAILED(  hResult  )  )  goto  errLabel;
		if  (  !IsWindow(  pVar->hDlgDesktopsMon  )  )  goto  errLabel;
		if  (  !(  hCtrl  =  GetDlgItem(  pVar->hDlgDesktopsMon,  idc_pic  )  )  )  goto  errLabel;
		if  (  !GetClientRect(  hCtrl,  &rect  )  )  goto  errLabel;
		//		
		if  (  (  hDc_ctrl  =  GetDC(  hCtrl  )  )  )  {			//  注意一定要释放下面的dc
			int				iX_image  =  0;
			int				iY_image  =  0;
			unsigned  int	iW_image  =  0;
			unsigned  int	iH_image  =  0;
			//	int  myGetImageInfo(  int  iW_image,  int  iH_image,  int  iX,  int  iY,  unsigned  int  iW,  unsigned  int  iH,  int  *  piX_image,  int  *  piY_image,  unsigned  int  *  piW_image,  unsigned  int  *  piH_image  );
			myGetImageInfo_netMc(  0,  img.GetWidth(  ),  img.GetHeight(  ),  rect.left,  rect.top,  rect.right  -  rect.left,  rect.bottom  -  rect.top,  &iX_image,  &iY_image,  &iW_image,  &iH_image  );
			//
              //  SetStretchBltMode(  hDc_ctrl,  COLORONCOLOR  );
			POINT	loc_stp;
			GetDCOrgEx(  hDc_ctrl,  &loc_stp  );

			SetStretchBltMode(  hDc_ctrl,  HALFTONE  );

			SetBrushOrgEx(  hDc_ctrl,  loc_stp.x,  loc_stp.y,  NULL  );

			//  img.StretchBlt(  hDc_ctrl,  rect.left,  rect.top,  rect.right,  rect.bottom,  0,  0,  img.GetWidth(  ),  img.GetHeight(  ),  SRCCOPY  );
			//  img.StretchBlt(  hDc_ctrl,  iX_image,  iY_image,  iW_image,  iH_image,  0,  0,  img.GetWidth(  ),  img.GetHeight(  ),  SRCCOPY  );
			img.Draw(  hDc_ctrl,  iX_image,  iY_image,  iW_image,  iH_image  );			
			
			ReleaseDC(  hCtrl,  hDc_ctrl  );
		}
		time_t	t;
		t  =  gettTimeBylStr(  timeBuf  );	//  注册表里存的是localTime, qyDisplayTime用的是系统时间。所以，需要倒一下
		getTimeStr(  t,  timeBuf,  mycountof(  timeBuf  )  );
		qyDisplayTime(  timeBuf,  buf,  mycountof(  buf  )  );
		_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s, %s, %s"  ),  pVar->monedDesktops[i].displayName,  pVar->monedDesktops[i].wUsrDomain,  CString(  buf  )  );
		SetDlgItemText(  pVar->hDlgDesktopsMon,  idc_static,  tBuf  );

				
	}


	iErr  =  0;
errLabel:

	return  iErr;
}

//  在一个后台线程里自动刷新
 int  threadRefreshMonedDesktops(  )
{
	int						iErr		=		-1;
	QY_MC				*	pQyMc		=		QY_GET_GBUF(  );
	QY_SERVICEGUI_INFO	*	pSci		=		getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_netMc  );
	if  (  !pSci  )  return  -1;
	MC_VAR_netMc		*	pVar		=		(  MC_VAR_netMc  *  )pSci->pVar;
	if  (  !pVar  )  return  -1;
	CDlgDesktopsMon		*	pDlg		=		NULL;
	 QY_REG					tmpReg;
	 HKEY					hKey			=		NULL;
	 BOOL					bKeyOpen		=		FALSE;
	 DWORD					j;   
	 DWORD					retValue;   
	 DWORD					dwcValueName;
	 TCHAR					cfgName[256];
	 TCHAR					cfgVal[2048];
	 DWORD					cbData;
	 //

	 if  (  !pVar->usCnt_monPcs  )  return  0;

#ifdef  __DEBUG__
		//  printRegLogs(  );
#endif
	 
	 memset(  &tmpReg,  0,  sizeof(  tmpReg  )  );
	 //
	 //	safeStrnCpy(  CONST_qyRootKey_monPics,  tmpReg.rootKey,  sizeof(  tmpReg.rootKey  )  );
	 lstrcpyn(  tmpReg.rootKey,  CString(  CONST_qyRootKey_monPics  ),  mycountof(  tmpReg.rootKey  )  );
 
	 if  (  ERROR_SUCCESS  !=  RegOpenKey(  HKEY_LOCAL_MACHINE,  CString(  tmpReg.rootKey  ),  &hKey  )  )  goto  errLabel;
	 bKeyOpen  =  TRUE;

	 //  注意这里，由dwcVals来控制循环次数，而j来指向将读取的记录
	 for  (  j  =  0;  ;  )  {
		  dwcValueName  =  mycountof(  cfgName  );        
		  cfgName[0] = '\0';
		  retValue  =  RegEnumValue(  hKey,  j,  cfgName,  
									  &dwcValueName,  
									  NULL,  
									  NULL,			//  &dwType,         
			  						  NULL,			//  data, 
									  NULL  );		//  &cbData  );    
		  if  (  retValue  !=  (  DWORD  )ERROR_SUCCESS  )  break;

		  cbData  =  sizeof(  cfgVal  );
		  cfgVal[0]  =  0;
		  if  (  qyGetRegCfgT(  HKEY_LOCAL_MACHINE,  CString(  tmpReg.rootKey  ),  cfgName,  (  char  *  )cfgVal,  cbData,  0  )  )  {
			  RegDeleteValue(  hKey,  cfgName  );
			  continue;
		  }

		  //
		  OutputDebugString(  CString(  "得到:"  )  +  cfgName  +  ":"  +  cfgVal  +  "\n"  );
		  //
		  tmpHandler_threadRefreshMonedDesktops(  pVar,  cfgName,  cfgVal  );  //  不能退出．因为接着需要delete

		  //  发完后，将日志清除
		  RegDeleteValue(  hKey,  cfgName  );		  


	 }


	 iErr  =  0;

errLabel:

	 if  (  bKeyOpen  )  RegCloseKey(  hKey  );


	 return  0;

}




 //  原来的函数似乎已没用，但仍然保留一下，以减少代码的影响，2006。12/10
 //  2006/12/10, 在启停远程桌面时，立即告诉管理队列，要刷新队列中节点的策略信息，以方便立即启停远程桌面
 int  qnmTellPolicyChangedEx_netMc(  void  *  p0,  myREFRESHED_PCOPCMD  *  pPcOpCmd  )
{
	 int						iErr		=	-1;
	 //  QY_MC					*	pQyMc		=	QY_GET_GBUF(  );

	 QY_COMM_SESSION			session;
	 QY_SOCK					sock;
	 SOCK_TIMEOUT				to;
	 QY_COMM_RESP				resp;
	 char					*	ip		=	NULL;
	 unsigned  short			usPort	=	0;
	 unsigned  char				ucCmd;
	 QY_ENC_CTX					encCtx,  commEncCtx;
	 BOOL						bEncInited  =  FALSE;

	 
	 if  (  !pPcOpCmd  ||  !bMacValid(  pPcOpCmd->mac  )  )  goto  errLabel;

	 ip  =  "127.0.0.1";  usPort  =  DEFAULT_qyMcServPort;  ucCmd  =  CONST_qnmAuthCmd_guiTalk;
	
	 if  (  initQnmEnc(  &encCtx,  0,  0,  &commEncCtx  )  )  goto  errLabel;
	 bEncInited  =  TRUE;

	 memset(  &session,  0,  sizeof(  session  )  );
	 clearQySock(  &sock  );
	 setSockTimeout(  &to  );

	 if  (  !qnmOpenSession(  ip,  usPort,  NULL,  ucCmd,  CONST_qyServiceId_qwm,  qnmVerStr(  CONST_qyServiceId_qwm  ),  &commEncCtx,  &session,  &sock,  &to,  NULL,  NULL  )  )  {
		 if  (  !qySendReq(  &session,  &sock,  &to,  CONST_qyCmd_policyChanged,  (  char  *  )pPcOpCmd,  sizeof(  pPcOpCmd[0]  )  )  )  {
			 qyRecvResp(  &session,  &sock,  &to,  &resp,  NULL,  0  );
			 iErr  =  0;
		 }
		 qnmCloseSession(  &session,  &sock,  &to  );
	 }


errLabel:

	 if  (  bEncInited  )  exitQnmEnc(  &encCtx,  0,  0,  &commEncCtx  );

	 traceLogA(  "通知%s%s策略刷新%s",  "Daemon",  ip,  iErr  ?  "失败"  :  "成功"  );
	 return  0;

}








