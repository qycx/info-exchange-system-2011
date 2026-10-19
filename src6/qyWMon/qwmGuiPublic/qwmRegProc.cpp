


#include	<windows.h>
#include	<winsock.h>
#include	<ras.h>
#include	<raserror.h>
#include	<commctrl.h>
#include	<iphlpapi.h>
#include	<tchar.h>
#include	"resource.h"
#include	"asrWMon.h"
#include	"qyRegToolProc.h"
#include	"qwmAllHints.h"
#include	"qnmHotKeys.h"
#include	"qyTCharCommProc.h"
#include	"qyCusResPublic.h"

 extern  HMODULE					g_module;
 extern  BOOL						g_bIsWinNT;
 UINT								uiTimerId		=	0;

 
int  qrtGetHintFromServ(  QY_REG_TOOL  *  pQrt  );
int  setAllHints(  unsigned  short  usLangId  );
#ifdef  __DEBUG__
		int  testFunc(  void  *  pQyRegTool  );
#endif


HANDLE	ghMutex	 =	NULL;

 QYMC_HOTKEY	gHotKeys_qrt[] = 
{
	//  {  ID_HKF5, 0, VK_F5, 0  },
	//  {  ID_HKF6, 0, VK_F6, 0  },
	//  {  ID_HKF7, 0, VK_F7, 0  },
	{	ID_HKF8,	0,	VK_F8,	0,	},
	{	-1,					},
};


 //  BOOL  CALLBACK  qwmRegDlgProc(  HWND  hWnd,  UINT  msg,  WPARAM  wParam,  LPARAM  lParam  )
 INT_PTR CALLBACK  qwmRegDlgProc(  HWND  hWnd, UINT  msg, WPARAM  wParam, LPARAM  lParam  )
{
	 BOOL					bRet				=	FALSE;
	 HWND					hChild				=	NULL;
 	 QY_IDCITEM		*		pCurTable			=	NULL;
	 QY_IDCITEM		*		pItem				=	NULL;
	 TCHAR					wndTitle[128]		=	DEFAULT_qwmRegToolWndTitle;
	 RECT					rect;
	 //  DWORD					dwThreadId;
	 char					displayBuf[512]		=	"";
	 char					displayTimeBuf[32]	=	"";
	 unsigned		int		len					=	0;
	 int					iCxScreen			=	0;
	 int					iCyScreen			=	0;
	 int					iWidth				=	0;
	 int					iHeight				=	0;
	 long					lStyle				=	0;
	 TCHAR					tBuf[2048];

								 	 
	 switch  (  msg  )  {
			 case  WM_INITDIALOG:

				   lStyle  =  GetWindowLong(  hWnd,  GWL_STYLE  );	//  2005/08/27
				   if  (  gQyRegTool.iSystemId  !=  CONST_qySystemId_secChk  )  {
					   lStyle  &=  ~WS_MINIMIZEBOX;
					   lStyle  &=  ~WS_MAXIMIZEBOX;
					   SetWindowLong(  hWnd,  GWL_STYLE,  lStyle  );
						}
				   else  {		//  安全检查需要支持快键
					     if  (  bQnmAddHotKeys(  gHotKeys_qrt,  hWnd  )  )  gQyRegTool.ucbHotKeysAdded  =  TRUE;	//  2005/08/27
				   }
				 
				   //  这里先做一些为语言定制的工作  {
				#if  0
				   if  (  gQyRegTool.env.usLangId  !=  CONST_langId_PRC  )  {
					   lstrcpyn(  wndTitle,  _T(  "QYCX"  ),  mycountof(  wndTitle  )  );
					   lstrcpyn(  gQyRegTool.cfg.cusHintBuf,  gQyRegTool.cfg.ucbReged  ?  gAllHints.hint0_reged  :  gAllHints.hint0,  sizeof(  gQyRegTool.cfg.cusHintBuf  )  /  sizeof(  TCHAR  )  );
					   lstrcpyn(  gQyRegTool.cfg.qyRegToolTitle,  gAllHints.regToolTitle,  sizeof(  gQyRegTool.cfg.qyRegToolTitle  )  /  sizeof(  TCHAR  )  );
				   }
				#endif
				   tTrim(  gQyRegTool.cfg.cusHintBuf  );
				   if  (  !gQyRegTool.cfg.cusHintBuf[0]  ||  gQyRegTool.cfg.ucbReged  )  {
					   lstrcpyn(  gQyRegTool.cfg.cusHintBuf,  gQyRegTool.cfg.ucbReged  ?  gAllHints.hint0_reged  :  gAllHints.hint0,  sizeof(  gQyRegTool.cfg.cusHintBuf  )  /  sizeof(  TCHAR  )  );
				   }
				   if  (  !gQyRegTool.cfg.qyRegToolTitle[0]  ||  gQyRegTool.cfg.ucbReged  )  {
					   lstrcpyn(  gQyRegTool.cfg.qyRegToolTitle,  gAllHints.regToolTitle,  sizeof(  gQyRegTool.cfg.qyRegToolTitle  )  /  sizeof(  TCHAR  )  );
				   }
				   //
				   lstrcpyn(  gQyRegTool.cfg.hintBuf,  gAllHints.hint1,  sizeof(  gQyRegTool.cfg.hintBuf  )  /  sizeof(  TCHAR  )  );
				   lstrcpyn(  tBuf,  gAllHints.ok,  sizeof(  tBuf  )  /  sizeof(  TCHAR  )  );
				   SetDlgItemText(  hWnd,  IDOK,		tBuf  );
				   lstrcpyn(  tBuf,  gAllHints.cancel,  sizeof(  tBuf  )  /  sizeof(  TCHAR  )  );
				   SetDlgItemText(  hWnd,  IDCANCEL,	tBuf  );
				   //  }

				   iCxScreen  =  GetSystemMetrics(  SM_CXSCREEN  );		//  2005/08/19
				   iCyScreen  =  GetSystemMetrics(  SM_CYSCREEN  );		//  2005/08/19

				   GetWindowRect(  hWnd,  &rect  );
				   setDlgIdcParams(  &gQyRegTool.cfg.layout  );


				   if  (  gQyRegTool.iSystemId  ==  CONST_qySystemId_secChk  )  {
					    //  MoveWindow(  hWnd,  150,  100,  (  int  )(  292  *  1.55  ),  (  int  )(  229  *  1.64  ),  0  );		//  检查工具对话框。2003/11/12	
					   if  (  iCxScreen  <  700  &&  iCyScreen  <  550  )  {	//  主要为640  *  480的屏幕
						   iWidth  =  (  int  )(  400  *  1.55  );  iHeight  =  (  int  )(  256  *  1.64  );
						   gpTable0  =  CONST_secChkTable0_smallScreen;
							}
					   else  {		//  800  *  600以上的屏幕
						     iWidth  =  (  int  )(  495  *  1.55  );  iHeight  =  (  int  )(  283  *  1.64  );
						     gpTable0  =  CONST_secChkTable0;
					   }
					   MoveWindow(  hWnd,  (  iCxScreen  -  iWidth  )  /  2,  (  iCyScreen  -  iHeight  )  /  2,  iWidth,  iHeight,  0  );

					   SendMessage(  GetDlgItem(  hWnd,  IDC_LIST_secChk  ),  LB_SETHORIZONTALEXTENT,  512  *  12,  0  );  
						}
				   else if  (  gQyRegTool.cfg.ucbReged  )  {
							 MoveWindow(  hWnd,  100,  250,  rect.right  -  rect.left,  110,  0  );
					   		 gpTable0	 =	CONST_updateTable;				//  升级下载。2003/09/13
							 }
				   else  {
					     //  还是在这里直接计算了各控件的位置并设进gpTable0中, 2005/02/06  {  
				   	     setDlgIdcSize(  IDC_title,  IDC_hint0,  IDC_hint1,  IDC_PROGRESS_reg,  &gQyRegTool.cfg.custom,  &gQyRegTool.cfg.layout,  gpTable0  );
						
						 //  MoveWindow(  hWnd,  50,  50,  rect.right  -  rect.left,  rect.bottom  -  rect.top,  0  );
						 //  MoveWindow(  hWnd,  50,  50,  482,  369,  0  );		//  2005/01/18为了日文操作系统的界面，采用了这个固定的数字
						 int  i  =  MulDiv(  gQyRegTool.cfg.layout.ulDlgHeight,  CONST_multiplierOfDlgUnit,  CONST_divisorOfDlgUnit  );
						 //  MoveWindow(  hWnd,  100,  100,  482,  MulDiv(  gQyRegTool.cfg.layout.ulDlgHeight,  CONST_multiplierOfDlgUnit,  CONST_divisorOfDlgUnit  ),  0  );  
						 MoveWindow(  hWnd,  100,  100,  MulDiv(  gQyRegTool.cfg.layout.ulDlgWidth,  CONST_multiplierOfDlgUnit,  CONST_divisorOfDlgUnit  ),  MulDiv(  gQyRegTool.cfg.layout.ulDlgHeight,  CONST_multiplierOfDlgUnit,  CONST_divisorOfDlgUnit  ),  0  );  
				   }				  
				   
				   pCurTable  =  gpTable0;
				   qnmSizeRegToolControls(  &gQyRegTool.cusRes,  hWnd,  gpTable0,  pCurTable,  0  );

				   //  hChild  =  GetDlgItem(  hWnd,  IDC_EDIT0  );
				   //  if  (  hChild  )  {
				   //	   oldEditProc  =  SetWindowLong(  hChild,  GWL_WNDPROC,  (  LONG  )qyRestrictEditProc  );
				   //	   ShowWindow(  hChild,  SW_SHOWNORMAL  );
				   //  }
				   //  
				   
				   for  (  pItem  =  gpTable0;  pItem->idc  !=  -1;  pItem  ++  )  {
						if  (  pItem->idcType  ==  CONST_qyIdcType_edit  )  {
							hChild  =  GetDlgItem(  hWnd,  pItem->idc  );
							if  (  hChild  )  {
								gQyOldEditProc  =  SetWindowLong(  hChild,  GWLP_WNDPROC,  (  LONG  )qyRestrictEditProc  );
								SendMessage(  hChild,  EM_SETLIMITTEXT,  pItem->maxBytes,  0  );
							}
						}
				   }

				   MACRO_qyAssert(  qyCustomInfo.title[0],  _T(  "qyCustomInfo.title"  )  );

				   if  (  qyCustomInfo.wndTitle  )  safeTcsnCpy(  qyCustomInfo.wndTitle,  wndTitle,  mycountof(  wndTitle  )  );
				   if  (  !gQyRegTool.cfg.qyRegToolTitle[0]  )  safeTcsnCpy(  qyCustomInfo.title,  (  TCHAR  *  )gQyRegTool.cfg.qyRegToolTitle,  sizeof(  gQyRegTool.cfg.qyRegToolTitle  )  /  sizeof(  TCHAR  )  );

				   
				   //  注意：由于需要用窗口题头来判断窗口实例的唯一性，故原有的题头不能=DEFAULT_wndTitle
				   /*
				   if  (  FindWindow(  NULL,  wndTitle  )  )  {
					   traceLogA(  "对话框已存在"  );  
					   EndDialog(  hWnd,  -1  );
					   bRet  =  TRUE;  goto  errLabel;
				   }
				   */
                   ghMutex = CreateMutex(  NULL,  FALSE,  _T(  "QrtMutex"  )  );		//  2006/08/16,由于用title经常和目录名冲突,所以,换成mutex来保证唯一性
                   if  (  !ghMutex  ||  GetLastError(  )  ==  ERROR_ALREADY_EXISTS  )  {
					   traceLogA(  "对话框已存在"  );  
					   EndDialog(  hWnd,  -1  );
					   bRet  =  TRUE;  goto  errLabel;
				   }
				   
				   SetWindowText(  hWnd,  wndTitle  );				//  缺省：regTool
				   SetDlgItemText(  hWnd,  IDC_title,  (  TCHAR  *  )gQyRegTool.cfg.qyRegToolTitle  );	//  2003/09/19修改
				   SendMessage(  GetDlgItem(  hWnd,  IDC_title  ),  WM_SETFONT,  (  WPARAM  )gQyRegTool.hHt,  (  LPARAM  )myMAKELONG(  (  WORD  )TRUE,  0  )  );
				   SetDlgItemText(  hWnd,  IDC_hint0,  (  TCHAR  *  )gQyRegTool.cfg.cusHintBuf  );	//  2005/07/27增加了一个用户化的提示信息
				   SetDlgItemText(  hWnd,  IDC_hint1,  (  TCHAR  *  )gQyRegTool.cfg.hintBuf  );
				   tBuf[0]  =  0;	//  2006/05/13, 表现单机版的license信息
				   if  (  gQyRegTool.iSystemId  ==  CONST_qySystemId_secChk  &&  gQyRegTool.cfg.ucbDj  &&  g_bIsWinNT  )  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "尚可检查: %d次"  ),  CONST_maxSecChkDjCnt  -  gQyRegTool.uiSecChkCnt  );
				   SetDlgItemText(  hWnd,  IDC_STATIC_licenseHint,  tBuf  );
				   
				   SendMessage(  GetDlgItem(  hWnd,  IDC_PROGRESS_reg  ),  PBM_SETRANGE,  0,  myMAKELPARAM(  0,  CONST_qrtStep_finished  )  );
				   SendMessage(  GetDlgItem(  hWnd,  IDC_PROGRESS_reg  ),  PBM_SETSTEP,  1,  0  );

				   //  将本窗口句柄存在gQyRegTool中
				   gQyRegTool.hWnd  =  hWnd;
				   //
				   setProgressTxt(  &gQyRegTool,  0  );						
				   //				   
				   uiTimerId  =  SetTimer(  hWnd,  1,  1000,  NULL  );
				   
				   bRet  =  TRUE;  goto  errLabel;		   
				   break;
			 case  WM_SIZE:	  {  //  2005/08/27
				   int	x,  y,  nWidth,  nHeight;
				   //  traceLogA(  "这里需要调整安检窗口的大小"  );
				   GetWindowRect(  hWnd,  &rect  );
				   iWidth  =  rect.right  -  rect.left;  iHeight  =  rect.bottom  -  rect.top;
				   if  (  iWidth  <  10  ||  iHeight  <  10  )  {
					   bRet  =  TRUE;  goto  errLabel;
				   }
				   for  (  pItem  =  gpTable0;  pItem->idc  !=  -1;  pItem  ++  )  
					    if  (  pItem->idc  ==  IDC_LIST_secChk  )  break;
				   if  (  pItem->idc  ==  -1  )  {
					   traceLogA(  "secChkList没有找到：错误"  );  goto  errLabel;
				   }

				   x  =  pItem->x;
				   //  y  =  gQyRegTool.cfg.layout.tilteH  +  pItem->y;
				   y  =  gQyRegTool.cfg.layout.titleH  +  85;
				   nWidth  =  iWidth  -  2  *  gQyRegTool.cfg.layout.bj;
				   nHeight  =  iHeight  -  gQyRegTool.cfg.layout.titleH  -  y  -  gQyRegTool.cfg.layout.bbj;

				   MoveWindow(  GetDlgItem(  hWnd,  IDC_LIST_secChk  ),  x,  y,  nWidth,  nHeight,  TRUE  );

					}
				   bRet  =  TRUE;  goto  errLabel;
				   break;
			 case  WM_HOTKEY:  {
				   int	idHotKey		=		(  int  )wParam;				// identifier of hot key 
				   UINT	fuModifiers		=		(  UINT  )myLOWORD(  lParam  );	// key-modifier flags 
				   UINT	uVirtKey		=		(  UINT  )myHIWORD(  lParam  );   // virtual-key code 

				   switch  (  idHotKey  )  {
						   case  ID_HKF8:  
							     doMyCapture(  0,  0,  0  );
								 break;
						   default:
							       break;
				   }
					
					}
				   bRet  =  TRUE;  goto  errLabel;
				   break;
			 case  WM_TIMER:  {
	
				   //  DWORD				ulRet;
				   HWND					hProgress  =  GetDlgItem(  hWnd,  IDC_PROGRESS_reg  );

				   //  traceLogA(  "OnTimer"  );

				   if  (  gQyRegTool.ucbRegFinished  )  {
					   EndDialog(  hWnd,  0  );
					   bRet  =  TRUE;  goto  errLabel;
				   }
				   
				   if  (  gQyRegTool.bInProgress  )  {	//  注册期间进行进程显示
					   ShowWindow(  hProgress,  SW_SHOW  );
					   SendMessage(  hProgress,  PBM_SETPOS,  gQyRegTool.iProgress,  0  );							   
					   }
				   else  {
					     ShowWindow(  hProgress,  SW_HIDE  );							
					     /* if  (  gQyRegTool.hRegThread  )  {							 	 
							 ulRet  =  ::WaitForSingleObject(  gQyRegTool.hRegThread,  500  );  
							 if  (  ulRet  !=  WAIT_FAILED  &&  ulRet  !=  WAIT_TIMEOUT  )  {
								 CloseHandle(  gQyRegTool.hRegThread  );  gQyRegTool.hRegThread  =  NULL;
								 EnableWindow(  GetDlgItem(  hWnd,  IDOK  ),  TRUE  );
							 }
						 }
						 */
				   }

				   //  2004/05/18修改
				   EnableWindow(  GetDlgItem(  hWnd,  IDOK  ),  gQyRegTool.ucbStartReg  ?  FALSE  :  TRUE  );  

				   if  (  gQyRegTool.ucbSecChkFinished  &&  !gQyRegTool.ucbSndFinished  )  {		//  2004/06/23增加
			  		   _sntprintf(  (  TCHAR  *  )gQyRegTool.progressTxt,  sizeof(  gQyRegTool.progressTxt  )  /  sizeof(  TCHAR  ),  _T(  "检查将完成 %d%%"  ),  (  100  *  gQyRegTool.uiSecChkEventSentCnt  )  /  gQyRegTool.uiSecChkEventCnt  );
		  		   }

				   SetDlgItemText(  hWnd,  IDC_hint1,  (  TCHAR  *  )gQyRegTool.progressTxt  );
	
				  }
				   bRet  =  TRUE;  goto  errLabel;
				   break;
			 case  WM_COMMAND:
				   switch  (  myLOWORD(  wParam  )  )  {
						   case  IDCANCEL:
							     EndDialog(  hWnd,  -1  );
								 bRet  =  TRUE;  goto  errLabel;
						   case  IDOK:  {

								 QY_IDCITEM	*	pItem		=  NULL;
								 QY_IDCITEM	*	tmppItem	=  NULL;
								 //  char			buf[1024];
								 //  char			hint[1024];
								 //  int			index;

								 if  (  gQyRegTool.iSystemId  ==  CONST_qySystemId_secChk  )  {
									 if  (  !gQyRegTool.ucbSecChkFinished  ||  !gQyRegTool.ucbSndFinished  )  {
										 MessageBox(  NULL,  _T(  "工作未完成, 请选择取消以终止工作"  ),  _T(  ""  ),  MB_OK  );
										 bRet  =  TRUE;  goto  errLabel;
									 }
								 }
	
								 if  (  !bGetRegInfoFromDlg(  &gQyRegTool.cusRes,  hWnd,  gpTable0,  TRUE,  &gQyRegTool.regInfo  )  )  goto  errLabel;
								 //  2005/08/18
								 if  (  gQyRegTool.cfg.ucbDj  &&  gQyRegTool.iSystemId  ==  CONST_qySystemId_secChk  )  {
									 if  (  !bMacValid(  (  char  *  )gQyRegTool.macsInfo.macs[0]  )  )  {
										 int  i;
										 for  (  i  =  0;  i  <  sizeof(  gQyRegTool.regInfo.u.cols  )  /  sizeof(  gQyRegTool.regInfo.u.cols[0]  );  i  ++  )  {
											  if  (  gQyRegTool.regInfo.uiFieldIds[i]  ==  CONST_fieldId_syr  )  break;
									 	 }
										 if  (  i  ==  sizeof(  gQyRegTool.regInfo.u.cols  )  /  sizeof(  gQyRegTool.regInfo.u.cols[0]  )  )  goto  errLabel;
										 if  (  !gQyRegTool.regInfo.u.cols[i][0]  )  {
											 MessageBox(  NULL,  _T(  "工作未完成, 请输入使用人信息以标识本机"  ),  _T(  ""  ),  MB_OK  );
											 bRet  =  TRUE;  goto  errLabel;
										 }
									 }
								 }
								 /*
								 for  (  pItem  =  gpTable0;  pItem->idc  !=  -1;  pItem  ++  )  {
									  if  (  !(  pItem->flg  &  CONST_qyIdcFlgChkNotNull  )  )  continue;
		 							  if  (  pItem->idcType  !=  CONST_qyIdcType_edit  &&  pItem->idcType  !=  CONST_qyIdcType_combo  )  continue;
		 							  GetDlgItemText(  hWnd,  pItem->idc,  buf,  sizeof(  buf  )  );
		 							  trim(  buf  );
		 							  tmppItem  =  qyGetIdcItemByIdc(  gpTable0,  pItem->lIdc  );
		 							  MACRO_qyAssert(  tmppItem,  "表格中的lIdc错误，没有相关idc"  );
		 							  lstrcpyn(  hint,  tmppItem->des,  sizeof(  hint  )  );
									  lstrcpyn(  hint  +  lstrlen(  hint  ),  gAllHints.bt,  sizeof(  hint  )  -  lstrlen(  hint  )  );			 
		 							  //  MACRO_chkNotNull(  pItem->idc,  buf,  hint  );		//  被下面代码所替代	 
									  if  (  !buf[0]  )  {															
										  MessageBeep(  -1  );													
										  if  (  hint  &&  hint[0]  )  MessageBox(  NULL,  hint,  "",  MB_OK  );						
										  SetFocus(  GetDlgItem( hWnd,  pItem->idc )  );
										  bRet  =  TRUE;  goto  errLabel;
									  }								
								 }								 	
	
								 EnableWindow(  GetDlgItem(  hWnd,  IDOK  ),  FALSE  );

								 gQyRegTool.regInfo.iCustomId  =  gQyRegTool.iCustomId;
								 memset(  &gQyRegTool.regInfo.u,  0,  sizeof(  gQyRegTool.regInfo.u  )  );		 
								 for  (  pItem  =  gpTable0,  index  =  0;  pItem->idc  !=  -1;  pItem  ++  )  {
		 							  if  (  pItem->idcType  !=  CONST_qyIdcType_combo  &&  pItem->idcType  !=  CONST_qyIdcType_edit  )  continue;
		 							  if  (  pItem->flg  &  CONST_qyIdcFlgUnused  )  continue;
									  if  (  pItem->uiCommSeqNo  ==  -1  )  continue;		//  当传输顺序号为-1时，不作为注册信息传输到服务器上，2003/11/15
		 							  if  (  pItem->flg  &  CONST_qyIdcFlgNeeded  ||  !(  pItem->flg  &  CONST_qyIdcFlgHide  )  )  {
										  //  GetDlgItemText(  hWnd,  pItem->idc,  gQyRegTool.regInfo.u.cols[index],  min(  sizeof(  gQyRegTool.regInfo.u.cols[index]  ),  pItem->maxBytes  +  1  )  );		 
										  //  trim(  gQyRegTool.regInfo.u.cols[index]  );
										  MACRO_qyAssert(  pItem->uiCommSeqNo  <  CONST_qnmMaxRegFields,  "传输顺序号不能超过CONST_qnmMaxRegFields"  );
										  GetDlgItemText(  hWnd,  pItem->idc,  gQyRegTool.regInfo.u.cols[pItem->uiCommSeqNo],  min(  sizeof(  gQyRegTool.regInfo.u.cols[pItem->uiCommSeqNo]  ),  pItem->maxBytes  +  1  )  );		 
										  trim(  gQyRegTool.regInfo.u.cols[pItem->uiCommSeqNo]  );
										  if  (  pItem->idcType  ==  CONST_qyIdcType_combo  &&  pItem->pTable  )  {		//  2005/02/08将combo的数据由改为由类型来代表，为了使多语言能够使用
											  int	tmpiType  =  qyGetTypeByDes(  pItem->pTable,  gQyRegTool.regInfo.u.cols[pItem->uiCommSeqNo]  );
											  _snprintf(  gQyRegTool.regInfo.u.cols[pItem->uiCommSeqNo],  sizeof(  gQyRegTool.regInfo.u.cols[pItem->uiCommSeqNo]  ),  "%d",  tmpiType  );
										  }
										  gQyRegTool.regInfo.uiFieldIds[pItem->uiCommSeqNo]  =  pItem->uiFieldId;	//  2005/02/07
		 							  }
		 							  index  ++  ;
								 }
								 */
	
								 //  if  (  !gQyRegTool.hRegThread  )  gQyRegTool.hRegThread  =  CreateThread(  NULL,  0,  qrtRegThreadProc,  (  LPVOID  )&gQyRegTool,  0,  &dwThreadId  );
								 gQyRegTool.ucbStartReg  =  TRUE;
	
							   }
							     bRet  =  TRUE;  goto  errLabel;
						   case  IDC_COMBO0:
							     if  (  myHIWORD(  wParam  )  ==  CBN_SELCHANGE  )  {
									 QY_IDCITEM  **  ppTables  =  gpCb0Tables;

									 procCbSelChange(  0,  gpTable0,  ppTables,  hWnd,  myLOWORD(  wParam  ),  0  );									 
								 }
								 bRet  =  TRUE;  goto  errLabel;
						   case  IDC_COMBO1:
							     if  (  myHIWORD(  wParam  )  ==  CBN_SELCHANGE  )  {
									 QY_IDCITEM  **  ppTables  =  gpCb1Tables;

									 procCbSelChange(  0,  gpTable0,  ppTables,  hWnd,  myLOWORD(  wParam  ),  0  );									 
								 }
								 bRet  =  TRUE;  goto  errLabel;
						   case  IDC_COMBO2:
							     if  (  myHIWORD(  wParam  )  ==  CBN_SELCHANGE  )  {
									 QY_IDCITEM  **  ppTables  =  gpCb2Tables;

									 procCbSelChange(  0,  gpTable0,  ppTables,  hWnd,  myLOWORD(  wParam  ),  0  );									 
								 }
								 bRet  =  TRUE;  goto  errLabel;
						   case  IDC_COMBO3:
							     if  (  myHIWORD(  wParam  )  ==  CBN_SELCHANGE  )  {
									 QY_IDCITEM  **  ppTables  =  gpCb3Tables;

									 procCbSelChange(  0,  gpTable0,  ppTables,  hWnd,  myLOWORD(  wParam  ),  0  );									 
								 }
								 bRet  =  TRUE;  goto  errLabel;
						   case  IDC_COMBO4:
							     if  (  myHIWORD(  wParam  )  ==  CBN_SELCHANGE  )  {
									 QY_IDCITEM  **  ppTables  =  gpCb4Tables;

									 procCbSelChange(  0,  gpTable0,  ppTables,  hWnd,  myLOWORD(  wParam  ),  0  );									 
								 }
								 bRet  =  TRUE;  goto  errLabel;
						   case  IDC_COMBO_secChk:
							     if  (  myHIWORD(  wParam  )  ==  CBN_SELCHANGE  )  {
									 QY_WMBUF_COMMHEAD	wmBuf;

									 GetDlgItemText(  hWnd,  IDC_COMBO_secChk,  tBuf,  sizeof(  tBuf  )  /  sizeof(  TCHAR  )  );
									 gQyRegTool.lEventTypeToDisplay  =  qyGetTypeByDes(  getResTable(  0,  &gQyRegTool.cusRes,  CONST_resId_secChkEventTypeTable  ),  tBuf  );
									 wmBuf.uiType  =  CONST_qyWmParam_refreshData;
									 SendMessage(  hWnd,  CONST_qyWm_comm,  0,  (  LPARAM  )&wmBuf  );
								 }
								 bRet  =  TRUE;  goto  errLabel;
				  		   default:
								   break;
				   }
				   bRet  =  TRUE;  goto  errLabel;
				   break;
			 case  CONST_qyWm_comm:  {
				   QY_WMBUF_COMMHEAD	*	pCommHead	=	(  QY_WMBUF_COMMHEAD  *  )lParam;
				   int						iWmRet		=	-1;
				 
				   if  (  !pCommHead  )  goto  errLabel;

				   switch  (  pCommHead->uiType  )  {
						   case  CONST_qyWmParam_getIdcInfo:  {
							     QY_WMBUF_GETIDCINFO	*	pGetIdcInfo		=	(  QY_WMBUF_GETIDCINFO  *  )lParam;
					   			 QY_IDCITEM				*	pItem			=	gpTable0;
				 									   
								 for  (  pItem  =  gpTable0;  pItem->idc  !=  -1;  pItem  ++  )  {
						    		  if  (  GetDlgItem(  hWnd,  pItem->idc  )  ==  pGetIdcInfo->hCtrl  )  break;
					   			 }
					   
					   			 if  (  pItem->idc  !=  -1  )  {
									 pGetIdcInfo->flg  =  pItem->flg;
									 iWmRet  =  CONST_qyWmRc_ok;
								 }
								  }
								 break;
						   case  CONST_qyWmParam_showSecChkEvent:  {
							     QNM_WMBUF_SHOWSECCHKEVENT	*	pWmBuf  =  (  QNM_WMBUF_SHOWSECCHKEVENT  *  )lParam;
								 
								 if  (  gQyRegTool.lEventTypeToDisplay  >  0  &&  pWmBuf->event.lEventType  !=  gQyRegTool.lEventTypeToDisplay  )  {
									 iWmRet  =  CONST_qyWmRc_ok;  break;
								 }								 
									 
								 myTChar2Str(  qyGetDesByType1(  getResTable(  0,  &gQyRegTool.cusRes,  CONST_resId_qnmEventTypeTable0  ),  pWmBuf->event.lEventType  ),  displayBuf,  sizeof(  displayBuf  )  );
								 len  =  strlen(  displayBuf  );
								 safeStrnCpy(  "  ",  displayBuf  +  len,  sizeof(  displayBuf  )  -  len  );
								 len  +=  2;
								 safeStrnCpy(  pWmBuf->event.des0,  displayBuf  +  len,  sizeof(  displayBuf  )  -  len  );
								 //  2007/02/20, 加上用户信息
								 if  (  !qyDisplayTime(  pWmBuf->event.localEventTime,  displayTimeBuf,  sizeof(  displayTimeBuf  )  )  )  displayTimeBuf[0]  =  0;
								 _snprintf(  displayBuf,  sizeof(  displayBuf  ),  "%s   (%s)   %s",  displayBuf,  pWmBuf->event.usrName,  displayTimeBuf  );
								 //
								 SendMessage(  GetDlgItem(  hWnd,  IDC_LIST_secChk  ),  LB_ADDSTRING,  0,  (  LPARAM  )displayBuf  );
								 iWmRet  =  CONST_qyWmRc_ok;
								  }
							     break;
						   case  CONST_qyWmParam_refreshData:  {
							     QNM_SECCHK_EVENT	*	pEvent	=	NULL;
							     traceLogA(  "刷新数据"  );
								 SendMessage(  GetDlgItem(  hWnd,  IDC_LIST_secChk  ),  LB_RESETCONTENT,  0,  0  );
								 for  (  int  i  =  0;  i  <  (  int  )gQyRegTool.uiSecChkEventCnt;  i  ++  )  {
									  pEvent  =  (  QNM_SECCHK_EVENT  *  )&gQyRegTool.pSecChkEventCache[sizeof(  QNM_SECCHK_EVENT  )  *  i];
									  if  (  gQyRegTool.lEventTypeToDisplay  >  0  &&  pEvent->lEventType  !=  gQyRegTool.lEventTypeToDisplay  )  continue;
									  myTChar2Str(  qyGetDesByType1(  getResTable(  0,  &gQyRegTool.cusRes,  CONST_resId_qnmEventTypeTable0  ),  pEvent->lEventType  ),  displayBuf,  sizeof(  displayBuf  )  );
									  len  =  strlen(  displayBuf  );
									  safeStrnCpy(  "  ",  displayBuf  +  len,  sizeof(  displayBuf  )  -  len  );
									  len  +=  2;
									  safeStrnCpy(  pEvent->des0,  displayBuf  +  len,  sizeof(  displayBuf  )  -  len  );
									  //  2007/02/20, 加上用户信息
									  if  (  !qyDisplayTime(  pEvent->localEventTime,  displayTimeBuf,  sizeof(  displayTimeBuf  )  )  )  displayTimeBuf[0]  =  0;
									  _snprintf(  displayBuf,  sizeof(  displayBuf  ),  "%s   (%s)   %s",  displayBuf,  pEvent->usrName,  displayTimeBuf  );
									  //
									  SendMessage(  GetDlgItem(  hWnd,  IDC_LIST_secChk  ),  LB_ADDSTRING,  0,  (  LPARAM  )displayBuf  );								 
								}
								 iWmRet  =  CONST_qyWmRc_ok;
								  }
							     break;
						   default:
									break;
				   }

				   SetWindowLong(  hWnd,  DWLP_MSGRESULT,  iWmRet  );

					}	   
                
				   bRet  =  TRUE;  goto  errLabel;
			 case  WM_DESTROY:
				   //  Remove the subclassing
				   //  hChild  =  GetDlgItem(  hWnd,  IDC_EDIT0  );
				   //  if  (  hChild  )  {
				   //	   SetWindowLong(  hChild,  GWL_WNDPROC,  oldEditProc  );
				   //  }
				   
				   if  (  uiTimerId  )  {
					   KillTimer(  hWnd,  uiTimerId  );  uiTimerId  =  0;
				   }
				   
				   if  (  isHandleValid(  ghMutex  )  )  {		//  这里加入了Mutex的关闭,2006/08/16
					   CloseHandle(  ghMutex  );  ghMutex  =  NULL;
				   }

				   for  (  pItem  =  gpTable0;  pItem->idc  !=  -1;  pItem  ++  )  {
						if  (  pItem->idcType  ==  CONST_qyIdcType_edit  )  {
							hChild  =  GetDlgItem(  hWnd,  pItem->idc  );
							if  (  hChild  &&  gQyOldEditProc )  {
								SetWindowLong(  hChild,  GWLP_WNDPROC,  gQyOldEditProc  );								
							}
						}
				   }

				   //  2005/08/27
				   if  (  gQyRegTool.ucbHotKeysAdded  )  {  qnmRemoveHotKeys(  gHotKeys_qrt,  hWnd  );  gQyRegTool.ucbHotKeysAdded  =  FALSE;  }
		
				   bRet  =  TRUE;  goto  errLabel;
				   break;
			 default:
					 break;
	 }

errLabel:

	 return  bRet;

}




 extern  "C"  BOOL  bQrtNoGui(  )
{
	 return  gQyRegTool.cfg.ucbNoGui;
}


 extern  "C"  BOOL  bSetQrtProgressTxt1(  TCHAR  *  txt  )
{
	 safeTcsnCpy(  txt  ?  txt  :  _T(  ""  ),  gQyRegTool.progressTxt1,  mycountof(  gQyRegTool.progressTxt1  )  );
	 setProgressTxt(  &gQyRegTool,  FALSE  );

	 return  TRUE;
}

 
 extern  QY_DMITEM  CONST_cusResTable_qwm[];

 //  返回0表正确执行并点击OK
 extern  "C"  int  qwmRegProc(  void  *  pDynLib,  QWM_REG_STRUCT  *  pQwmRegStruct  )
{
	 int			iRet					=		-1;
	 //  int			iPlatformId;
	 DWORD			len;
	 unsigned  long ulbEncInited			=		FALSE;
	 DWORD			dwThreadId;
	 TCHAR			svLibName[CONST_qyMaxPathLen  +  1];
	 TCHAR			tBuf[2048];


	 setTraceLogOpen(  TRUE  );
	 traceLogA(  "qwmRegProc enters"  );

	 memset(  &gQyRegTool,  0,  sizeof(  gQyRegTool  )  );

	 gQyRegTool.hSt  =  CreateFont(  16,  0,  0,  0,  FW_NORMAL,  0,  0,  0,  ANSI_CHARSET,
									 OUT_DEFAULT_PRECIS,  CLIP_DEFAULT_PRECIS,
						 			 DEFAULT_QUALITY,  DEFAULT_PITCH  |  FF_DONTCARE,
						 			 _T(  "Tahoma"  )  );
	 gQyRegTool.hHt  =  CreateFont(  22,  0,  0,  0,  FW_SEMIBOLD,  0, 0, 0,  ANSI_CHARSET,
									 OUT_DEFAULT_PRECIS,  CLIP_DEFAULT_PRECIS,
						 			 DEFAULT_QUALITY,  DEFAULT_PITCH  |  FF_DONTCARE,
						 			 _T(  ""  )  //  "黑体"
									 );
	 if  (  !gQyRegTool.hSt  ||  !gQyRegTool.hHt  )  {
		 traceLogA(  "字体不支持"  );  goto  errLabel;
	 }
	 //  2005/09/23, 用richedit替代edit, 以支持多语言
	 GetSystemDirectory(  svLibName,  sizeof(  svLibName  )  );
	 tTrailDir(  svLibName,  sizeof(  svLibName  )  /  sizeof(  TCHAR  )  );
	 #ifndef  UNICODE
			  if  (  tQyStrCat(  svLibName,  _T(  "riched32.DLL"  ),  svLibName,  sizeof(  svLibName  )  /  sizeof(  TCHAR  )  )  )  goto  errLabel;
	 #else
			  if  (  tQyStrCat(  svLibName,  _T(  "riched20.DLL"  ),  svLibName,  sizeof(  svLibName  )  /  sizeof(  TCHAR  )  )  )  goto  errLabel;
	 #endif
	 if  (  !(  gQyRegTool.hDllRiched  =  LoadLibrary(  svLibName  )  )  )  goto  errLabel;

	 getQyEnv(  pDynLib,  &gQyRegTool.env  );
	 //  gQyRegTool.env.pDynLibs  =  pDynLib;

	 if  (  gQyRegTool.env.iPlatformId  ==  CONST_qyPlatform_win32  ||  gQyRegTool.env.iPlatformId  ==  CONST_qyPlatform_win95  )  goto  errLabel;

	 gQyRegTool.iSystemId  =  qyGetSystemId(  );
	 gQyRegTool.iCustomId  =  qyGetCustomId(  );
	 gQyRegTool.iServiceId  =  CONST_qyServiceId_qwm;
	 memcpy(  gQyRegTool.ver,  qnmVerStr(  gQyRegTool.iServiceId  ),  sizeof(  gQyRegTool.ver  )  -  1  );


	 //  这里初始化资源  {
	 gQyRegTool.cusRes.pSysResTable  =  CONST_cusResTable_qwm;
	 gQyRegTool.cusRes.pCusStrTable  =  (  QY_DMITEM  *  )qyGetDesByType(  gQyRegTool.cusRes.pSysResTable,  CONST_resType_str  );
	 //  }
	 setAllHints(  gQyRegTool.env.usLangId  );

	 if  (  initQnmEnc(  &gQyRegTool.encCtx,  NULL,  NULL,  &gQyRegTool.commEncCtx  )  )  goto  errLabel;
	 ulbEncInited  =  TRUE;


	 //  取得MAC地址
	 getQwmMacs(  &gQyRegTool.env,  &gQyRegTool.macsInfo  );	//  2004/05/20增加了取mac的补充手段
	 if  (  !gQyRegTool.macsInfo.nMacs  )  getQwmMacsByNetbios(  &gQyRegTool.env,  &gQyRegTool.macsInfo  );
	 if  (  qwmGetPcName(  gQyRegTool.pcName,  sizeof(  gQyRegTool.pcName  )  )  )  gQyRegTool.pcName[0]  =  0;
	 len  =  sizeof(  tBuf  )  /  sizeof(  TCHAR  );
	 GetUserName(  tBuf,  &len  );  myTChar2Str(  tBuf,  gQyRegTool.curUsrName,  sizeof(  gQyRegTool.curUsrName  )  );
	 
	 gQyRegTool.iSystemId						=  pQwmRegStruct->iSystemId_wanted;	//  2005/09/24
	 gQyRegTool.uiQwmType						=  pQwmRegStruct->uiQwmType;		//  2004/05/14添加
	 setSockTimeout(  &gQyRegTool.cfg.to  );
	 gQyRegTool.cfg.usTries_connect				=  3;
	 gQyRegTool.cfg.usTries_waitSndFinished		=  3;
	 memcpy(  &gQyRegTool.cfg.dynCfg,  &pQwmRegStruct->dynCfg,  sizeof(  gQyRegTool.cfg.dynCfg  )  );
	 gQyRegTool.cfg.idrData						=  pQwmRegStruct->idrData;
	 gQyRegTool.cfg.ucbInstall					=  pQwmRegStruct->ucbInstall;
	 gQyRegTool.cfg.ucbSecChkQuickly			=  pQwmRegStruct->ucbSecChkQuickly;
	 gQyRegTool.cfg.ucbNoGui					=  pQwmRegStruct->ucbNoGui;
	 gQyRegTool.cfg.ucbGetPcAsset				=  pQwmRegStruct->ucbGetPcAsset;
	 gQyRegTool.cfg.ucbDj						=  pQwmRegStruct->ucbDj;			//  2005/08/18
	 gQyRegTool.uiSecChkCnt						=  pQwmRegStruct->uiSecChkCnt;		//  2006/05/13
	 //  2005/02/06
	 gQyRegTool.cfg.custom.nDwLevels			=	3;		// 加使用人
	 gQyRegTool.cfg.custom.nZcbhs				=	1;

	 #ifdef  __DEBUG__		//  2004/07/26加
			 testFunc(  &gQyRegTool  );
	 #endif

	 if  (  !gQyRegTool.cfg.ucbDj  )  {
	 	 //  搜索管理端，2006/07/01 
	 	 if  (  getCorrectCnt(  &gQyRegTool.env,  &gQyRegTool.cfg.dynCfg,  bServConnected,  0,  gQyRegTool.iServiceId,  gQyRegTool.ver,  &gQyRegTool.commEncCtx,  &gQyRegTool.cfg.to,  &gQyRegTool.cfg.cnt  )  )  {
			 if  (  !bQrtNoGui(  )  )  MessageBox(  NULL,  gAllHints.ssfwqsb,  _T(  ""  ),  MB_OK  );  goto  errLabel;
		 }
	 }

	 if  (  qrtGetHintFromServ(  &gQyRegTool  )  )  {
		 if  (  !bQrtNoGui(  )  )  MessageBox(  NULL,  gAllHints.ljfwqsb,  _T(  ""  ),  MB_OK  );  goto  errLabel;
	 }
	 	 
	 if  (  initSecChk(  pQwmRegStruct->pSecChkTaskTable  )  )  {
		 if  (  !bQrtNoGui(  )  )  MessageBox(  NULL,  myStr2TChar1(  gQyRegTool.errBuf,  tBuf,  sizeof(  tBuf  )  /  sizeof(  TCHAR  )  ),  _T(  "注意"  ),  MB_OK  );  goto  errLabel;
	 }

	 if  (  bQrtNoGui(  )  )  doNoGuiChkPcInfo(  &gQyRegTool  );
	 else  {
		  
		   if  (  !gQyRegTool.hRegThread  )  gQyRegTool.hRegThread  =  CreateThread(  NULL,  0,  qrtRegThreadProc,  (  LPVOID  )&gQyRegTool,  0,  &dwThreadId  );
		   if  (  !gQyRegTool.hRegThread  )  {
			   traceLogA(  "启动注册线程失败"  );  goto  errLabel;
		   }
	 		
		   #ifndef  UNICODE
					if  (  DialogBox(  g_module,  MAKEINTRESOURCE(  IDD_qyRegFor98  ),  NULL,  qwmRegDlgProc  )  )  {
						qyDisplayLastError(  "DialogBox failed"  );  goto  errLabel;
					}
		   #else
					if  (  DialogBox(  g_module,  MAKEINTRESOURCE(  IDD_qyReg  ),  NULL,  qwmRegDlgProc  )  )  {
						qyDisplayLastError(  "DialogBox failed"  );  goto  errLabel;
					}
		   #endif
	
	 }

	 iRet  =  0;
	
errLabel:
	 
	 gQyRegTool.bQuit  =  TRUE;
	 traceLogA(  "准备退出注册程序"  );

	 if  (  gQyRegTool.hRegThread  )  {  MACRO_qyNullThread(  gQyRegTool.hRegThread  );  }

	 exitSecChk(  );	//  2003/12/15

	 if  (  ulbEncInited  )  exitQnmEnc(  &gQyRegTool.encCtx,  NULL,  NULL,  &gQyRegTool.commEncCtx  );

	 if  (  gQyRegTool.hDllRiched  )  {  FreeLibrary(  (  HINSTANCE  )gQyRegTool.hDllRiched  );  gQyRegTool.hDllRiched  =  NULL;  }  //  2005/09/23
	 if  (  gQyRegTool.hSt  )  {  DeleteObject(  gQyRegTool.hSt  );  gQyRegTool.hSt  =  NULL;  }
	 if  (  gQyRegTool.hHt  )  {  DeleteObject(  gQyRegTool.hHt  );  gQyRegTool.hHt  =  NULL;  }

	 traceLogA(  "qwmRegProc leaves"  );
	 setTraceLogOpen(  FALSE  );
	 
	 return  iRet;

}
 

 
 int  qrtGetHintFromServ(  QY_REG_TOOL  *  pQrt  )
{
	int						iErr		=		-1;
	ASR_SOCK				aS;
	int						i			=		0;
	char					ip[16]		=		"";
	QNM_COMM_AUTHINFO		authInfo;
	QY_COMM_SESSION			session;
	QY_COMM_RESP			tmpResp;
	char					cfgsBuf[8192];
	QWM_MACS_INFO			tmpMacsInfo;
	QWM_REG_HINT		*	pHint		=		NULL;

	traceLogA(  "getHintFromServ enters."  );

	//  2005/08/18, 加入对单机版的支持
	if  (  pQrt->cfg.ucbDj  )  {
		if  (  pQrt->iSystemId  ==  CONST_qySystemId_secChk  )  {
			traceLogA(  "这里是安检单机版"  );
			qwmOutputFileHead(  pQrt  );
		}
		iErr  =  0;  goto  errLabel;
	}

	//  取得MAC地址
	//  tmpMacsInfo.nMacs  =  0;	//  旧版 
	getQwmMacs(  &pQrt->env,  &tmpMacsInfo  );	//  新版
		
	clearQySock(  &aS  );
	memset(  &session,  0,  sizeof(  session  )  );
	
	//  safeStrnCpy(  "连接服务器",  pQrt->progressTxt,  mycountof(  pQrt->progressTxt  )  );	 
	lstrcpyn(  pQrt->progressTxt,  _T(  "连接服务器"  ),  mycountof(  pQrt->progressTxt  )  );	 
	traceLogA(  "连接服务器 %s : %d",  pQrt->cfg.cnt.ip,  pQrt->cfg.cnt.port  );
	for  (  i  =  0;  i  <  pQrt->cfg.usTries_connect;  i  ++  )  {
		 if  (  !qyConnect(  pQrt->cfg.cnt.ip,  pQrt->cfg.cnt.port,  &aS,  pQrt->cfg.to.iConnect  )  )  {
			 break;		
		 }
		 Sleep(  1000  );
		 pQrt->iProgress  ++  ;
	}
	if  (  i  ==  pQrt->cfg.usTries_connect  )  {
		//  safeStrnCpy(  "连接服务器失败，请重新进行",  pQrt->progressTxt,  sizeof(  pQrt->progressTxt  )  );
		lstrcpyn(  pQrt->progressTxt,  _T(  "连接服务器失败，请重新进行"  ),  mycountof(  pQrt->progressTxt  )  );
		traceLogA(  "连接服务器失败。"  );
		goto  errLabel;
	}
	
	if  (  getLocalIpBySocket(  aS.sockFd,  ip  )  )  goto  errLabel;
	memset(  &authInfo,  0,  sizeof(  authInfo  )  );
	if  (  makeQwmAuthInfo(  pQrt->ver,  &tmpMacsInfo,  &authInfo  )  )  goto  errLabel;
	memcpy(  authInfo.ip,  ip,  sizeof(  authInfo.ip  )  );
	authInfo.cmd  =  CONST_qnmAuthCmd_getHint;
	authInfo.uiQwmType  =  qyhtonl(  pQrt->uiQwmType  );
	
	session.encCtx.type  =  CONST_qyEncType_qnm;

	if  (  qyTellService(  pQrt->iServiceId,  pQrt->ver,  &pQrt->commEncCtx,  (  char  *  )&authInfo,  sizeof(  authInfo  ),  &aS,  &pQrt->cfg.to,  &session  )  )  goto  errLabel;
	traceLogA(  "qyTellService ok."  );
	if  (  qyRecvResp(  &session,  &aS,  &pQrt->cfg.to,  &tmpResp,  cfgsBuf,  sizeof(  cfgsBuf  )  )  )  goto  errLabel;
	traceLogA(  "get respCode %s",  qyGetDesByType1(  CONST_qyRcTable,  tmpResp.head.usCode  )  );

	if  (  isRcQuit(  tmpResp.head.usCode  )  )  {
		//  safeStrnCpy(  "受控端不再允许登记。",  pQrt->progressTxt,  sizeof(  pQrt->progressTxt  )  );
		lstrcpyn(  pQrt->progressTxt,  _T(  "受控端不再允许登记。"  ),  mycountof(  pQrt->progressTxt  )  );
		goto  errLabel;
	}
	if  (  isRcUpdate(  tmpResp.head.usCode  )  )  {
		//  safeStrnCpy(  "注册软件版本不符。请重新下载。",  pQrt->progressTxt,  sizeof(  pQrt->progressTxt  )  );		
		lstrcpyn(  pQrt->progressTxt,  _T(  "注册软件版本不符。请重新下载。"  ),  mycountof(  pQrt->progressTxt  )  );		
		goto  errLabel;
	}
	if  (  !isRcHint(  tmpResp.head.usCode  )  )   goto  errLabel;
	if  (  tmpResp.head.len  <  sizeof(  QWM_REG_HINT  )  )  goto  errLabel;	//  2005/02/10
	pHint  =  (  QWM_REG_HINT  *  )cfgsBuf;
	myUtf82TChar(  pHint->hintBuf,  pQrt->cfg.cusHintBuf,  sizeof(  pQrt->cfg.cusHintBuf  )  /  sizeof(  TCHAR  )  );
	myUtf82TChar(  pHint->qyRegToolTitle,  pQrt->cfg.qyRegToolTitle,  sizeof(  pQrt->cfg.qyRegToolTitle  )  /  sizeof(  TCHAR  )  );	//  2003/09/19加
	pQrt->cfg.ucbReged  =  pHint->ucbReged;
	lstrcpyn(  (  TCHAR  *  )pQrt->cfg.hintBuf,  _T(  "注：* 代表必选项"  ),  sizeof(  pQrt->cfg.hintBuf  )  /  sizeof(  TCHAR  )  );
	memcpy(  &pQrt->cfg.custom,  &pHint->custom,  sizeof(  pQrt->cfg.custom  )  );
		
	iErr  =  0;
	
errLabel:

	if  (  bQySockOpen(  &aS  )  )  qyDisconnect(  &aS  );
	
	traceLogA(  "getHintFromServ leaves."  );

	return  iErr;

}

 /*
 extern  "C"  int  qwmCreateRegProcess(  char  *  cmdLine  )
{
	 int						iRet						=		-1;
	 char						tmpExeName[MAX_PATH  +  1];
	 STARTUPINFO				si;
	 PROCESS_INFORMATION		pi;
	 BOOL						bProcessCreated				=		FALSE;

	 memset(  &si,  0,  sizeof(  si  )  );
	 memset(  &pi,  0,  sizeof(  pi  )  );
		 
	 traceLogA(  "Now start qwm "  );
	 memset(  &si,  0,  sizeof(  STARTUPINFO  )  );
 	 si.cb  =  sizeof(  STARTUPINFO  );
 	 si.dwFlags  =  STARTF_FORCEOFFFEEDBACK;
	 
	 if  (  !GetModuleFileName(  NULL,  tmpExeName,  sizeof(  tmpExeName  )  )  )  goto  errLabel;
	 if  (  qyQuoteFileName(  tmpExeName,  sizeof(  tmpExeName  )  )  )  goto  errLabel;
	 if  (  cmdLine  )  {
		 lstrcpyn(  tmpExeName  +  lstrlen(  tmpExeName  ),  " ",  sizeof(  tmpExeName  )  -  lstrlen(  tmpExeName  )  );
	 	 lstrcpyn(  tmpExeName  +  lstrlen(  tmpExeName  ),  cmdLine,  sizeof(  tmpExeName  )  -  lstrlen(  tmpExeName  )  );
	 }

	 if  (  !CreateProcess(  NULL,  tmpExeName,  NULL,  NULL,  0,  0,  NULL,  NULL,  &si,  &pi  )  )  goto  errLabel;
	 bProcessCreated  =  TRUE;
	 traceLogA(  "CreateProcess %s succeeded,  new processId is %d,  new threadId is %d.",  tmpExeName,  pi.dwProcessId,  pi.dwThreadId  );

	 iRet  =  0;

errLabel:

	 if  (  bProcessCreated  )  {
		 if  (  pi.hThread  )  {  CloseHandle(  pi.hThread  );  pi.hThread  =  NULL;  }
		 if  (  pi.hProcess  )  {  CloseHandle(  pi.hProcess  );  pi.hProcess  =  NULL;  }
	 }

	 return  iRet;
}
*/
 
 int  doNoGuiChkPcInfo(  LPVOID  lpParameter  )
{
	 int						iErr		=  -1;
	 QY_REG_TOOL	*			pRegTool	=  (  QY_REG_TOOL  *  )lpParameter;
	 MT_SUBTHREADINFO			subThreadInfo;							//  2004/05/14

	 memset(  &subThreadInfo,  0,  sizeof(  subThreadInfo  )  );		//  2004/05/14添加
	 subThreadInfo.pParentParam  =  pRegTool;
	 subThreadInfo.pTo  =  &pRegTool->cfg.to;
		
	 return  chkPcInfo(  &subThreadInfo,  NULL,  NULL  );

}

 

 DWORD  WINAPI  qrtRegThreadProc(  LPVOID  lpParameter  )
{
	 QY_REG_TOOL	*			pRegTool	=  (  QY_REG_TOOL  *  )lpParameter;

	 while  (  !pRegTool->ucbRegFinished  &&  !gQyRegTool.bQuit  )  {
			Sleep(  1100  );
			if  (  pRegTool->ucbStartReg  )  {
				doRegProc(  lpParameter  );  pRegTool->ucbStartReg  =  FALSE;
			}
	 }
	 return  0;
}


/*
 int  qrtCommWithGlCnt(  QY_REG_TOOL  *  pQrt  )
{
	 int					iErr				=		-1;
	 QWM_INFO				qwmInfo;
	 QY_SOCK				sock;
	 QWM_SESSION			session;
	 BOOL					bSessionOpen		=		FALSE;
	 QY_COMM_RESP			tmpResp;
	 int					len;

	 traceInfo(  &pQwm->logCtx,  "commWithGlCnt enters."  );

	 clearQySock(  &sock  );
	 memset(  &session,  0,  sizeof(  session  )  );

	 if  (  qwmOpenSession(  pQwm,  &session,  &sock  )  )  goto  errLabel;
	 bSessionOpen		=		TRUE;
	 if  (  !isRcOk(  session.comm.usLastRespCode  )  )  goto  errLabel;
	
	 //  通报本机信息
	 memset(  &qwmInfo,  0,  sizeof(  qwmInfo  )  );
	 qwmInfo.iPlatformId  =  pQrt->env.iPlatformId;
	 safeStrnCpy(  pQwm->pcName,  qwmInfo.pcName,  sizeof(  qwmInfo.pcName  )  );
	 safeStrnCpy(  pQwm->env.systemBuf,  qwmInfo.systemBuf,  sizeof(  qwmInfo.systemBuf  )  );
	 safeStrnCpy(  pQwm->env.servicePackBuf,  qwmInfo.servicePackBuf,  sizeof(  qwmInfo.servicePackBuf  )  );
	 //  safeStrnCpy(  pQwm->curUsrName,  qwmInfo.curUsrName,  sizeof(  qwmInfo.curUsrName  )  );
	 //  safeStrnCpy(  pQwm->proxyServer,  qwmInfo.proxyServer,  sizeof(  qwmInfo.proxyServer  )  );

	 len  =  qyhtonQwmInfo(  &qwmInfo  );
	 traceInfo(  &pQwm->logCtx,  "commWithGlCnt  pcName is [%s]",  pQwm->pcName  );
	 if  (  qySendReq(  &session.comm,  &sock,  &pQwm->cfg.to,  CONST_qyCmd_showQwmInfo,  (  char  *  )&qwmInfo,  len  )  )  goto  errLabel;
	 if  (  qyRecvResp(  &session.comm,  &sock,  &pQwm->cfg.to,  &tmpResp,  NULL,  0  )  )  goto  errLabel;

	 	 
	 iErr  =  0;

errLabel:

	 if  (  bSessionOpen  )  qwmCloseSession(  pQwm,  &session,  &sock  );

	 traceInfo(  &pQwm->logCtx,  "commWithGlCnt leaves %s",  iErr  ?  "失败"  :  "成功"  );

	 return  iErr;

}
*/


 void  setProgressTxt(  QY_REG_TOOL  *  pRegTool,  BOOL  bFailed  )
{
	 TCHAR			progressTxt[128]	=	_T(  ""  );
	 unsigned  int	nMaxBytes			=	min(  106,  mycountof(  progressTxt  )  -  1  );

	 lstrcpyn(  progressTxt,  (  TCHAR  *  )pRegTool->progressTxt,  mycountof(  progressTxt  )  );

	 if  (  pRegTool->ucbStartReg  )  {
		 if  (  pRegTool->iSystemId  !=  CONST_qySystemId_secChk  )  {
		 	 if  (  pRegTool->iProgress  <=  0  )  {
				 lstrcpyn(  progressTxt,  (  TCHAR  *  )gQyRegTool.cfg.hintBuf,  mycountof(  progressTxt  )  );
				 goto  errLabel;
			 }
			 if  (  pRegTool->iProgress  <  CONST_qrtStep_waitForQwm  )  {
				 if  (  !bFailed  )  lstrcpy(  progressTxt,  pRegTool->cfg.ucbReged  ?  gAllHints.zbgx  :  gAllHints.zbzc  );
				 else  lstrcpyn(  progressTxt,  pRegTool->cfg.ucbReged  ?  gAllHints.gxwwcqcxjx  :  gAllHints.wwczcqcxjx,  mycountof(  progressTxt  )  );			 
				 goto  errLabel;
			 }	
			 if  (  pRegTool->iProgress  <  CONST_qrtStep_connected  )  {
				 if  (  !bFailed  )  lstrcpyn(  progressTxt,  gAllHints.ljfwq,  mycountof(  progressTxt  )  );	 
				 else  	lstrcpyn(  progressTxt,  gAllHints.ljfwqsbqcxjx,  mycountof(  progressTxt  )  );
				 goto  errLabel;
			 }
			 if  (  pRegTool->iProgress  <  CONST_qrtStep_canReg  )  {
				 if  (  !bFailed  )  ;
				 else  lstrcpyn(  progressTxt,  gAllHints.khdbyxdjqlxwlgly,  mycountof(  progressTxt  )  );		
				 goto  errLabel;
			}
			if  (  pRegTool->iProgress  <  CONST_qrtStep_chkQwmVer  )  {
				if  (  !bFailed  )  ;
				else  lstrcpyn(  progressTxt,  gAllHints.zcrjbbbfqcxxz,  mycountof(  progressTxt  )  );		
				goto  errLabel;
			}
			if  (  pRegTool->iProgress  <  CONST_qrtStep_regOk  )  {
				if  (  !bFailed  )  lstrcpyn(  progressTxt,  gAllHints.zcjsjxx,  mycountof(  progressTxt  )  );
				else  lstrcpyn(  progressTxt,  gAllHints.khdbyxdjqlxwlgly,  mycountof(  progressTxt  )  );		
				goto  errLabel;		 
			}
			if  (  pRegTool->iProgress  <=  CONST_qrtStep_finished  )  {
				if  (  !bFailed  )  lstrcpyn(  progressTxt,  pRegTool->cfg.ucbReged  ?  gAllHints.wc  :  gAllHints.zcwb,  mycountof(  progressTxt  )  );
				else  lstrcpyn(  progressTxt,  gAllHints.wwcqcxjx,  mycountof(  progressTxt  )  );
				goto  errLabel;
			}
		 
			}
		else  {

			if  (  pRegTool->iProgress  <=  0  )  {
				lstrcpyn(  progressTxt,  _T(  ""  ),  sizeof(  gQyRegTool.progressTxt  )  );
				goto  errLabel;
			}		 
			if  (  pRegTool->iProgress  <=  CONST_qrtStep_regOk  )  {
				if  (  !bFailed  )  lstrcpyn(  progressTxt,  _T(  "准备退出"  ),  mycountof(  progressTxt  )  );
				else  lstrcpyn(  progressTxt,  _T(  "退出意外"  ),  mycountof(  progressTxt  )  );  
				goto  errLabel;
			}
			if  (  pRegTool->iProgress  <=  CONST_qrtStep_waitSndFinished  )  {
				if  (  !bFailed  )  ;
				else  lstrcpyn(  progressTxt,  _T(  "上传失败"  ),  mycountof(  progressTxt  )  );
				goto  errLabel;
			}
			if  (  pRegTool->iProgress  <=  CONST_qrtStep_finished  )  {
				if  (  !bFailed  )  lstrcpyn(  progressTxt,  _T(  "退出"  ),  mycountof(  progressTxt  )  );
				else  lstrcpyn(  progressTxt,  _T(  "退出错误"  ),  mycountof(  progressTxt  )  );
				goto  errLabel;
			}		 
		}
		
		}

	 else  {
		   if  (  pRegTool->iSystemId  !=  CONST_qySystemId_secChk  )  {
			   lstrcpyn(  progressTxt,  (  TCHAR  *  )gQyRegTool.cfg.hintBuf,  mycountof(  progressTxt  )  );
				}
		   else  {  //  检查过程

		 	   if  (  pRegTool->iProgress  <=  CONST_qrtStep_start  )  {
				   lstrcpyn(  progressTxt,  _T(  "开始检查"  ),  mycountof(  progressTxt  )  );
				   goto  errLabel;
			   }
			   if  (  pRegTool->iProgress  <=  CONST_qrtStep_chkPcInfo  )  {
				   lstrcpyn(  progressTxt,  _T(  "检查终端信息"  ),  mycountof(  progressTxt  )  );
				   goto  errLabel;
			   }		 
			   if  (  pRegTool->iProgress  <=  CONST_qrtStep_chkRecent  )  {
				   lstrcpyn(  progressTxt,  _T(  "检查曾使用文件"  ),  mycountof(  progressTxt  )  );
				   goto  errLabel;
			   }
			   if  (  pRegTool->iProgress  <=  CONST_qrtStep_chkIe  )  {
				   lstrcpyn(  progressTxt,  _T(  "检查上网情况"  ),  mycountof(  progressTxt  )  );
				   goto  errLabel;
			   }
			   if  (  pRegTool->iProgress  <=  CONST_qrtStep_chkRas  )  {
				   lstrcpyn(  progressTxt,  _T(  "检查拨号配置"  ),  mycountof(  progressTxt  )  );
				   goto  errLabel;
			   }
			   if  (  pRegTool->iProgress  <=  CONST_qrtStep_chkProxyCfg  )  {
				   lstrcpyn(  progressTxt,  _T(  "检查代理设置"  ),  mycountof(  progressTxt  )  );
				   goto  errLabel;
			   }
			   if  (  pRegTool->iProgress  <=  CONST_qrtStep_chkOsInfo  )  {
				   lstrcpyn(  progressTxt,  _T(  "检查多操作系统"  ),  mycountof(  progressTxt  )  );
				   goto  errLabel;
			   }		 
			   if  (  pRegTool->iProgress  <=  CONST_qrtStep_chkShare  )  {
				   lstrcpyn(  progressTxt,  _T(  "检查网络共享"  ),  mycountof(  progressTxt  )  );
				   goto  errLabel;
			   }
			   if  (  pRegTool->iProgress  <=  CONST_qrtStep_chkSoftwareInstalled  )  {
				   lstrcpyn(  progressTxt,  _T(  "检查安装的软件"  ),  mycountof(  progressTxt  )  );
				   goto  errLabel;
			   }
			   if  (  pRegTool->iProgress  <=  CONST_qrtStep_chkRecycler  )  {
				   lstrcpyn(  progressTxt,  _T(  "检查回收站"  ),  mycountof(  progressTxt  )  );
				   goto  errLabel;
			   }
			   if  (  pRegTool->iProgress  <=  CONST_qrtStep_chkRemovableStorage  )  {
				   lstrcpyn(  progressTxt,  _T(  "检查曾使用移动存储"  ),  mycountof(  progressTxt  )  );
				   goto  errLabel;
			   }
			   if  (  pRegTool->iProgress  <=  CONST_qrtStep_chkUsrInfo  )  {
				   lstrcpyn(  progressTxt,  _T(  "检查用户信息"  ),  mycountof(  progressTxt  )  );
				   goto  errLabel;
			   }
			   if  (  pRegTool->iProgress  <=  CONST_qrtStep_chkDiskDrvFile  )  {
				   lstrcpyn(  progressTxt,  _T(  "查删"  ),  nMaxBytes  );				   
				   //  myStr2TChar(  pRegTool->progressTxt1,  progressTxt  +  lstrlen(  progressTxt  ),  nMaxBytes  -  lstrlen(  progressTxt  )  );
				   lstrcpyn(  progressTxt  +  lstrlen(  progressTxt  ),  pRegTool->progressTxt1,  nMaxBytes  -  lstrlen(  progressTxt  )  );
				   if  (  (  unsigned  long  )lstrlen(  progressTxt  )  ==  nMaxBytes  -  1  )  {
					   progressTxt[lstrlen(  progressTxt  )  -  1]  =  '~';
				   }
				   goto  errLabel;
			   }
			   if  (  pRegTool->iProgress  <=  CONST_qrtStep_chkNormalDiskDrvFile  )  {	//  2005/05/10
				   lstrcpyn(  progressTxt,  _T(  "检查"  ),  nMaxBytes  );
				   //  myStr2TChar(  pRegTool->progressTxt1,  progressTxt  +  lstrlen(  progressTxt  ),  nMaxBytes  -  lstrlen(  progressTxt  )  );
				   lstrcpyn(  progressTxt  +  lstrlen(  progressTxt  ),  pRegTool->progressTxt1,  nMaxBytes  -  lstrlen(  progressTxt  )  );
				   if  (  (  unsigned  long  )lstrlen(  progressTxt  )  ==  nMaxBytes  -  1  )  {
					   progressTxt[lstrlen(  progressTxt  )  -  1]  =  '~';
				   }
				   goto  errLabel;
			   }
			   if  (  pRegTool->iProgress  <=  CONST_qrtStep_chkInternet  )  {
				   lstrcpyn(  progressTxt,  _T(  "检查非法外联"  ),  mycountof(  progressTxt  )  );
				   goto  errLabel;
			   }
			   if  (  pRegTool->iProgress  <=  CONST_qrtStep_waitSndFinished  )  {
				   lstrcpyn(  progressTxt,  _T(  "检查将完成"  ),  mycountof(  progressTxt  )  );
				   goto  errLabel;
			   }
			   if  (  pRegTool->iProgress  <=  CONST_qrtStep_finished  )  {
				   lstrcpyn(  progressTxt,  _T(  "检查完成，请输入单位名称，并按回车键退出"  ),  mycountof(  progressTxt  )  );
				   goto  errLabel;
			   }
		   }
	 }
	 
errLabel:
	
	 lstrcpyn(  (  TCHAR  *  )pRegTool->progressTxt,  progressTxt,  sizeof(  pRegTool->progressTxt  )  /  sizeof(  TCHAR  )  );
	 return;

}


 
 

