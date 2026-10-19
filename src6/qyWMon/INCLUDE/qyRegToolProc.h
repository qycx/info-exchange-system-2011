


#ifndef  __QYREGTOOLPROC_H__
#define	 __QYREGTOOLPROC_H__	/*  {  */




typedef  struct  __qrtCfg_t					{

				 QWM_DYN_CFG				dynCfg;							//  2006/07/01
				 //
				 QY_LOGICAL_SERVER			cnt;
				 //  QY_LOGICAL_SERVER			tmpCnt;
				 int						iSystemId_wanted;

				 unsigned  short			idrData;

				 SOCK_TIMEOUT				to;
				 unsigned  int				nInterval_chkIndexDatFile;		//  该参数主要用于在qwmSvr中为降低对系统的影响而设
				 unsigned  short			usTries_connect;				//  尝试连接的次数
				 unsigned  short			usTries_waitSndFinished;		//  等待发送数据完毕
				 
				 //  注意，因为要使用ANSI的共享库，故不能在这个结构中使用TCHAR，2005/11/16
				 unsigned  char				ucbReged;
				 //  char						cusHintBuf[CONST_maxQrtHintLen  *  2  +  1];			//  2005/07/27
				 TCHAR						cusHintBuf[CONST_maxQrtHintLen  +  1];			//  2005/07/27
				 TCHAR						hintBuf[64  +  1];
				 TCHAR						qyRegToolTitle[CONST_maxQrtTitleLen  +  1];		//  2003/09/19添加

				 //  2005/02/06
				 QNM_CUSTOM_COMM			custom;
				 QRT_LAYOUT_CFG				layout;
				 //
				 //
				 unsigned  char				ucbInstall;						//  是否安装，仅在qyRegTool中调用时才安装
				 unsigned  char				ucbSecChkQuickly;				//  是否快速安检
				 unsigned  char				ucbNoGui;						//  是否不显示界面
				 unsigned  char				ucbGetPcAsset;					//  是否进行资产管理
				 unsigned  char				ucbDj;							//  是否是单机版			2005/08/17
				 char						yMD[8  +  1];					//  单机版有效运行的日期，	2005/08/20
				 

}		 QRT_CFG;


typedef  struct  __qyRegTool_t				{

				 MACRO_qyAppCommonMems
				 
				 QY_ENV						env;

				 QRT_CFG					cfg;
				 QY_ENC_CTX					encCtx,  commEncCtx;	//  2004/01/03添加commEncCtx
				 
				 //  LANGID						usLangId;				//  操作系统语言类型，2005/01/17
				 unsigned  int				uiQwmType;				//  2004/05/14添加
				 BOOL						bQuit;					//  使注册线程终止

				 QNM_CUSRES_INFO			cusRes;

				 HANDLE						hRegThread;				//  注册线程
				 HANDLE						hSecChkThread;			//  检查线程
				 HANDLE						hSndThread;				//  发送线程
				 HWND						hWnd;					//  界面主窗口
				 //

				 QWM_MACS_INFO				macsInfo;
				 //  unsigned  long				ulIp;
				 char						pcName[MAX_COMPUTERNAME_LENGTH + 1];
				 QNM_REG_INFO				regInfo;
				 char						curUsrName[UNLEN + 1];

				 HANDLE						hDllRiched;
				 HFONT						hSt;					//  宋体
				 HFONT						hHt;					//  黑体

				 BOOL						bInProgress;			//  用作显示进程条
				 TCHAR						progressTxt[256],  progressTxt1[64];
				 int						iProgress;
				 char						errBuf[64];				//  用于错误提示,2003/12/15

				 QY_DMITEM				*	pSecChkTaskTable;		//  安检任务表
				 unsigned  int				uiSecChkCnt;					
				 
				 unsigned  char				ucbStartReg;			//  在qrtRegThreadProc里启动注册工作，在qrtRegThreadProc注册结束或不能进行时将ucbStartReg赋为FALSE,  2004/05/18

				 unsigned  char				ucbHotKeysAdded;		//  2005/08/27
				 unsigned  char				ucbSeriousErr;			//  严重的错误是否发生，2005/05/04, 当采用c++异常机制时的报警标志

				 unsigned  char				ucbRegFinished;			//  注册是否完成
				 unsigned  char				ucbSecChkFinished;		//  检查工作是否完成，2003/11/13
				 unsigned  char				ucbSndFinished;			//  发送是否完成
				 unsigned  char				ucbInSnd;				//  是否正在发送
				 
				 TCHAR						winDir[CONST_qyMaxPathLen  +  1];
				 TCHAR						usrsRootDir[CONST_qyMaxPathLen  +  1];
				 long						lEventTypeToDisplay;								//  选择显示的事件类型
				 char						djDatFileName[CONST_qyMaxPathLen  +  1];			//	单机版的数据文件名
				 
				 char				*		pSecChkEventCache;									//  准备一次性增加10000条事件的存放地
				 unsigned  int				uiMaxSecChkEventCnt;								//  最大多少条
				 unsigned  int				uiSecChkEventCnt;									//  当前多少条
				 unsigned  int				uiSecChkEventSentCnt;								//  已发送的事件计数
				 unsigned  int				uiHisSecChkEventSentCnt;							//  当缓冲区满时，就会将已发送的数据清空以存放更多的数据，这些清空的以发送的数据条数存在这里,  2005/05/04
				 BOOL						bGiveupAdjustCache;									//  当等待腾缓冲区时，超过2分钟，则将放弃这种努力,  2005/05/04

				 
}		 QY_REG_TOOL;





//  下面的step须逐渐增大	//  下面的step属于注册过程
#define		CONST_qrtStep_waitForQwm			70
#define		CONST_qrtStep_connected				74			//  服务器已连接
#define		CONST_qrtStep_canReg				75
#define		CONST_qrtStep_chkQwmVer				76			//  检查软件版本
#define		CONST_qrtStep_redirectOk			80
#define		CONST_qrtStep_readyToSndRegInfo		81			//  准备发送注册信息
#define		CONST_qrtStep_regOk					88			//  注册完成
#define		CONST_qrtStep_waitSndFinished		98			//  等待发送日志完成
#define		CONST_qrtStep_finished				100			//  注册对话流程结束

//  下面的step须逐渐增大，属于检查过程
#define		CONST_qrtStep_start					1			
#define		CONST_qrtStep_chkPcInfo				2			//  检查终端信息（如ServicePack）	7		ok
#define		CONST_qrtStep_chkRecent				5			//  检查曾使用文件					1		ok
#define		CONST_qrtStep_chkIe					8			//  检查上网痕迹					2		wait
#define		CONST_qrtStep_chkRas				20			//  检查拨号配置和痕迹				3		wait
#define		CONST_qrtStep_chkProxyCfg			21			//  检查代理设置					4		ok
#define		CONST_qrtStep_chkOsInfo				23			//  检查多操作系统情况
#define		CONST_qrtStep_chkShare				25			//  检查网络共享					6		wait
#define		CONST_qrtStep_chkSoftwareInstalled	29			//  检查安装的软件					8		
#define		CONST_qrtStep_chkRecycler			30			//  检查回收站
#define		CONST_qrtStep_chkRemovableStorage	31			//  检查曾使用移动存储				9		
#define		CONST_qrtStep_chkUsrInfo			32			//  检查用户信息					10		
#define		CONST_qrtStep_chkDiskDrvFile		43			//  检查遗失磁盘文件
#define		CONST_qrtStep_chkNormalDiskDrvFile	74			//  检查正常文件
#define		CONST_qrtStep_chkInternet			84			//  检查非法外联					5		ok
#define		CONST_qrtStep_waitSndFinished		98			//  等待发送日志完成
#define		CONST_qrtStep_finished				100



#define		CONST_winFile_desktopIni			"desktop.ini"
#define		CONST_winFile_indexDat				"index.dat"
#define		CONST_winFile_mm256Dat				"mm256.dat"
#define		CONST_winFile_mm2048Dat				"mm2048.dat"


//  2005/0923
#define		CONST_qnmSym_delSelf				_T(  "zhendelayidingyaoshandiaola"  )	//  自删除标志

int  procDelSelf(  TCHAR  *  fileToDelParam  );
int  delSelf(  );
int  doMyCapture(  void  *  p0,  void  *  p1,  void  *  p2  );
BOOL  bMyStream(  LPCTSTR  streamName  );
int  setStream(  LPCTSTR  path  );
int  setMySecChkCnt(  LPCTSTR,  unsigned  int  cnt  );
unsigned  int  getMySecChkCnt(  LPCTSTR  path  );

//



extern  BOOL  g_bIsWinNT;
extern  QY_REG_TOOL  gQyRegTool;
extern  HINSTANCE  ghDll_InetMib1;

int  qrtParseCfgs(  QY_REG_TOOL  *  pWMon  );
int  getHintFromServ(  QY_REG_TOOL  *  pQrt  );
int  qrtRegToServ(  QY_REG_TOOL  *  pQrt  );
DWORD  WINAPI  doRegProc(  LPVOID  lpParameter  );


void  GetOSVersion(  );
extern  "C"  int  getnTables(  QY_IDCITEM  *  pTables[]  );
extern  "C"  void  qrtSizeControls(  HWND  hDlg  );
int  getUsrKey(  char  *  szSid,  char  *  szSubKey,  char  *  szKey,  unsigned  int  size  );
//  int  addEventToCache(  QNM_SECCHK_EVENT  *  pEvent,  QY_REG_TOOL  *  pRegTool  );
int  addEventToCache(  void  *  pSubThreadInfoParam,  QNM_SECCHK_EVENT  *  pEvent,  QY_REG_TOOL  *  pRegTool  );	//  2005/05/04
int  sndCacheToSvr(  MT_SUBTHREADINFO  *  pSubThreadInfo,  QY_COMM_SESSION  *  pSession,  QY_SOCK  *  pSock  );
void  setProgressTxt(  QY_REG_TOOL  *  pQrt,  BOOL  bFailed  );
extern  "C"  BOOL  bSetQrtProgressTxt1(  TCHAR  *  txt  );

int  getQwmSpInfo(  int  iPlatformId,  QWM_INFO_EX  *  pSpInfo  );
int  getQwmAssetsHeadInfo(  void  *  pRegTool,  void  *  pAssetInfo  );
int  getQwmAssetsHardwareInfo(  void  *  pRegTool,  void  *  pAssetInfo  );
int  getQwmAssetsSoftwareInfo(  void  *  pRegTool,  void  *  pAssetInfo  );


extern  "C"  BOOL  bQrtNoGui(  );
extern  "C"  BOOL  bQrtQuit(  );


DWORD  WINAPI  qrtRegThreadProc(  LPVOID  lpParameter  );
DWORD  WINAPI  qrtSecChkThreadProc(  LPVOID  lpParameter  );
DWORD  WINAPI  qrtSndThreadProc(  LPVOID  lpParameter  );



#endif	/*  }  */



