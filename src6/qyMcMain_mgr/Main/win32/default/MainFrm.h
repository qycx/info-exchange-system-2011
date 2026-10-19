// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__F21E10C9_D664_4E6F_9F30_50A42622943F__INCLUDED_)
#define AFX_MAINFRM_H__F21E10C9_D664_4E6F_9F30_50A42622943F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// #include "qyDialogBar.h"
 
class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
public:
	//  CQyDialogBar			m_dlgBar;				//  2005/11/06, 因为没用，并且。NET编译出错，故注释掉了
	CMainClient					m_wndClient;

	QY_MC_mainWndVar			var;

// Operations
public:
	BOOL	bSwitchToolbar(  );
	void	exportSth(  BOOL  bProcCurQueryOnly  );

	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
	virtual void GetMessageString(UINT nID, CString& rMessage) const;	//  2005/11/07

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewMcBar();
	afx_msg void OnUpdateViewMcBar(CCmdUI* pCmdUI);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnSysCommand(  UINT,  LPARAM  );
	afx_msg void OnqyMgrSystems();
	afx_msg void OnUpdateqyMgrSystems(CCmdUI* pCmdUI);
	afx_msg void OnqyCfgSystems();
	afx_msg void OnUpdateqyCfgSystems(CCmdUI* pCmdUI);
	afx_msg void OnqyPcView();
	afx_msg void OnUpdateqyPcView(CCmdUI* pCmdUI);
	afx_msg void OnqyPcList();
	afx_msg void OnUpdateqyPcList(CCmdUI* pCmdUI);
	afx_msg void OnIsCmd(  UINT nID  );
	afx_msg void OnUpdateIsCmd(CCmdUI *pCmdUI);
	afx_msg void Onqymessengerview();
	afx_msg void Onqynewmessenger();
	afx_msg void OnUpdateqynewmessenger(CCmdUI *pCmdUI);
	afx_msg void OnqyMessengerAuthList();
	afx_msg void OnqyMessengerAuthListneedAudited();
	afx_msg void Onqyimamlist();
	afx_msg void Onqyphonemessengerlist();
	afx_msg void Onqynewimgrp();
	afx_msg void OnUpdateqynewimgrp(CCmdUI *pCmdUI);
	afx_msg void Onqyimgrpauthlist();
#if  0
	afx_msg void Onqymessengerlist();
	afx_msg void Onqyimgrplist();
	afx_msg void Onqyimgrpmemlist();
#endif
	afx_msg void Oncustomerservicelist();
	afx_msg void OnUpdatecustomerservicelist(CCmdUI *pCmdUI);
	afx_msg void Onwwwqmcfglist();
	afx_msg void OnUpdatewwwqmcfglist(CCmdUI *pCmdUI);
	afx_msg void Onipknowledgelist();
	afx_msg void OnUpdateipknowledgelist(CCmdUI *pCmdUI);
	afx_msg void Onqyphoneguestlist();
	afx_msg void OnUpdateqyphoneguestlist(CCmdUI *pCmdUI);
	afx_msg void Onqyverifiedphonelist();
	afx_msg void OnUpdateqyverifiedphonelist(CCmdUI *pCmdUI);
	afx_msg void Onqygsmmodemlist();
	afx_msg void Onqysmcontactlist();
	afx_msg void Onqystartlocalvideo();
	afx_msg void OnUpdateqystartlocalvideo(CCmdUI *pCmdUI);
	afx_msg void Onsharedynbmps();
	afx_msg void Onshareddynbmplist();
	afx_msg void Onshareddynbmprulelist();
	afx_msg void OnUpdateshareddynbmprulelist(CCmdUI *pCmdUI);
	afx_msg void OnqyMsgToday();
	afx_msg void OnUpdateqyMsgToday(CCmdUI* pCmdUI);
	afx_msg void Onqymsglist();
	afx_msg void OnqyPcSpList();
	afx_msg void OnqyPcUsrList();
	afx_msg void OnpcSecChkEventList();
	afx_msg void OnUpdatepcSecChkEventList(CCmdUI* pCmdUI);
	afx_msg void OnpcNetworkPropList();
	afx_msg void OnUpdatepcNetworkPropList(CCmdUI* pCmdUI);
	afx_msg void OnpcNetworkRuleList();
	afx_msg void OnUpdatepcNetworkRuleList(CCmdUI* pCmdUI);
	afx_msg void OnpcProxyCfgPropList();
	afx_msg void OnUpdatepcProxyCfgPropList(CCmdUI* pCmdUI);
	afx_msg void OnpcProxyCfgRuleList();
	afx_msg void OnUpdatepcProxyCfgRuleList(CCmdUI* pCmdUI);
	afx_msg void OnpcWindowsUpdatePolicyPropList();
	afx_msg void OnUpdatepcWindowsUpdatePolicyPropList(CCmdUI* pCmdUI);
	afx_msg void OnpcWindowsUpdatePolicyRuleList();
	afx_msg void OnUpdatepcWindowsUpdatePolicyRuleList(CCmdUI* pCmdUI);
	afx_msg void OnpcPrinterPropList();
	afx_msg void OnUpdatepcPrinterPropList(CCmdUI* pCmdUI);
	afx_msg void OnpcRegistryList();
	afx_msg void OnUpdatepcRegistryList(CCmdUI* pCmdUI);
	afx_msg void OnpcRegistryRuleStatusList();
	afx_msg void OnUpdatepcRegistryRuleStatusList(CCmdUI* pCmdUI);
	afx_msg void OnpcEventLogList();
	afx_msg void OnUpdatepcEventLogList(CCmdUI* pCmdUI);
	afx_msg void OnpcOsUsrList();
	afx_msg void OnUpdatepcOsUsrList(CCmdUI* pCmdUI);
	afx_msg void OnqyPcNetStatList();
	afx_msg void OnUpdateqyPcNetStatList(CCmdUI* pCmdUI);
	afx_msg void OnpcProcessPropList();
	afx_msg void OnUpdatepcProcessPropList(CCmdUI* pCmdUI);
	afx_msg void OnpcProcessModulePropList();
	afx_msg void OnUpdatepcProcessModulePropList(CCmdUI* pCmdUI);
	afx_msg void OnpcProcessRuleList();
	afx_msg void OnUpdatepcProcessRuleList(CCmdUI* pCmdUI);
	afx_msg void OnpcNetFlowPropList();
	afx_msg void OnUpdatepcNetFlowPropList(CCmdUI* pCmdUI);
	afx_msg void OnpcNetFlowPropListethernet();
	afx_msg void OnUpdatepcNetFlowPropListethernet(CCmdUI* pCmdUI);
	afx_msg void OnpcNetSharePropList();
	afx_msg void OnUpdatepcNetSharePropList(CCmdUI* pCmdUI);
	afx_msg void OnqyDevChanged();
	afx_msg void OnqyStartMon();
	afx_msg void OnqyStopMon();
	afx_msg void OnUpdateqyStartMon(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyStopMon(CCmdUI* pCmdUI);
	afx_msg void OnqyStartScripts();
	afx_msg void OnqyStopScripts();
	afx_msg void OnUpdateqyStartScripts(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyStopScripts(CCmdUI* pCmdUI);
	afx_msg void OnqyCfgIpScan();
	afx_msg void OnqyMgrPcGrp();
	afx_msg void OncfgRasOptions();
	afx_msg void OnUpdatecfgRasOptions(CCmdUI* pCmdUI);
	afx_msg void Oncfgvideoconference();
	afx_msg void OncfgPcNetworkOptions();
	afx_msg void OnUpdatecfgPcNetworkOptions(CCmdUI* pCmdUI);
	afx_msg void OncfgPcMonOptions();
	afx_msg void OnUpdatecfgPcMonOptions(CCmdUI* pCmdUI);
	afx_msg void OncfgImAuthCond();
	afx_msg void OnUpdatecfgImAuthCond(CCmdUI* pCmdUI);
	afx_msg void OnqyCfgModuleInfo();
	afx_msg void OnUpdateqyCfgModuleInfo(CCmdUI* pCmdUI);
	afx_msg void OnqyCfgPcRegistryKnowledge();
	afx_msg void OnUpdateqyCfgPcRegistryKnowledge(CCmdUI* pCmdUI);
	afx_msg void OnqyCfgCustom();
	afx_msg void OnUpdateqyCfgCustom(CCmdUI* pCmdUI);
	afx_msg void OnqyCfgStandardNames();
	afx_msg void OnUpdateqyCfgStandardNames(CCmdUI* pCmdUI);
	afx_msg void OnqyEventAll();
	afx_msg void OnqyRas();
	afx_msg void OncfgSystemParams();
	afx_msg void OnUpdatecfgSystemParams(CCmdUI* pCmdUI);
	afx_msg void OncfgOptions();
	afx_msg void OncfgAdvancedOptions();
	afx_msg void OnUpdatecfgAdvancedOptions(CCmdUI* pCmdUI);
	afx_msg void Onsetpasswd();
	afx_msg void OnUpdatesetpasswd(CCmdUI *pCmdUI);
	afx_msg void OnqyRefresh();
	afx_msg void OnqyStat();
	afx_msg void OnqyReportAssetsInfobyMac();
	afx_msg void OnqyReportAssetsInfobyOs();
	afx_msg void OnqyReportAssetsInfoenbyMac();
	afx_msg void OnqyReportAssetsInfoenbyOs();
	afx_msg void OnqyMakeClients();
	afx_msg void OnUpdateqyMakeClients(CCmdUI* pCmdUI);
	afx_msg void OnqySearch();
	afx_msg void OnqyStopAutoReg();
	afx_msg void OnqyStartAutoReg();
	afx_msg void OnUpdateqyStartAutoReg(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyStopAutoReg(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyStopIpScan(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyStartIpScan(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyStopRegScan(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyStopRespForUnreg(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyStartRespForUnreg(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyStartRegScan(CCmdUI* pCmdUI);
	afx_msg void OnqyStopIpScan();
	afx_msg void OnqyStartIpScan();
	afx_msg void OnqyStopRegScan();
	afx_msg void OnqyStartRegScan();
	afx_msg void OnqyStopRespForUnreg();
	afx_msg void OnqyStartRespForUnreg();
	afx_msg void OnqyStopDownPortIfMacChanged();
	afx_msg void OnUpdateqyStopDownPortIfMacChanged(CCmdUI* pCmdUI);
	afx_msg void OnqyStartDownPortIfMacChanged();
	afx_msg void OnUpdateqyStartDownPortIfMacChanged(CCmdUI* pCmdUI);
	afx_msg void OnqyStopDownPortIfWarnSpeed();
	afx_msg void OnUpdateqyStopDownPortIfWarnSpeed(CCmdUI* pCmdUI);
	afx_msg void OnqyStartDownPortIfWarnSpeed();
	afx_msg void OnUpdateqyStartDownPortIfWarnSpeed(CCmdUI* pCmdUI);
	afx_msg void OnqyScannedIpList();
	afx_msg void OnqyExport();
	afx_msg void OnqyClearUp();
	afx_msg void OnViewDebugStatus(  UINT nID  );
	afx_msg void OnUpdateViewDebugStatus(CCmdUI *pCmdUI);
	afx_msg void OnqyCfgUnchk();
	afx_msg void Onqycfgskippedmacs();
	afx_msg void OnUpdateqycfgskippedmacs(CCmdUI *pCmdUI);
	afx_msg void OnqyImport();
	afx_msg void OnqyIntraConn();
	afx_msg void OnqyQwmDel();
	afx_msg void OnHelp();
	afx_msg void OnqyOnInternet();
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnFilePrint();
	afx_msg void OnqyPcUsrInTab1List();
	afx_msg void OnCfgusr();
	afx_msg void OnUpdateCfgusr(CCmdUI* pCmdUI);
	afx_msg void OnUpdatecfgOptions(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyCfgIpScan(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyMgrPcGrp(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyCfgUnchk(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyPcUsrList(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyPcUsrInTab1List(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyImport(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyExport(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyClearUp(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyEventAll(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyRas(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyOnInternet(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyIntraConn(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyDevChanged(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyQwmDel(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqySearch(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyStat(CCmdUI* pCmdUI);
	afx_msg void OnCfgwarn();
	afx_msg void OnUpdateCfgwarn(CCmdUI* pCmdUI);
	afx_msg void OnqyProxyServer();
	afx_msg void OnstopFileMon();
	afx_msg void OnUpdatestopFileMon(CCmdUI* pCmdUI);
	afx_msg void OnstartFileMon();
	afx_msg void OnUpdatestartFileMon(CCmdUI* pCmdUI);
	afx_msg void OnstopModuleMon();
	afx_msg void OnUpdatestopModuleMon(CCmdUI* pCmdUI);
	afx_msg void OnstartModuleMon();
	afx_msg void OnUpdatestartModuleMon(CCmdUI* pCmdUI);
	afx_msg void OnstopPcRegistryMon();
	afx_msg void OnUpdatestopPcRegistryMon(CCmdUI* pCmdUI);
	afx_msg void OnstartPcRegistryMon();
	afx_msg void OnUpdatestartPcRegistryMon(CCmdUI* pCmdUI);
	afx_msg void OnqyStartUpdate();
	afx_msg void OnUpdateqyStartUpdate(CCmdUI* pCmdUI);
	afx_msg void OnqyStopUpdate();
	afx_msg void OnUpdateqyStopUpdate(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyProxyServer(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyScannedIpList(CCmdUI* pCmdUI);
	afx_msg void OnqyNetworkView();
	afx_msg void OnqyConnectionView();
	afx_msg void OnqyNetworkSpeedView();
	afx_msg void OnsnmpObjRuleList();
	afx_msg void OnUpdatesnmpobjrulelist(CCmdUI *pCmdUI);
	afx_msg void OnconflictConnList();
	afx_msg void OnUpdateconflictConnList(CCmdUI* pCmdUI);
	afx_msg void OndirectConnList();
	afx_msg void OnUpdatedirectconnlist(CCmdUI *pCmdUI);
	afx_msg void OnqyCfgSwitchPolicyGrps();
	afx_msg void OnqyMgrSwitchPolicyGrps();
	afx_msg void OnqyStopIntraMon();
	afx_msg void OnUpdateqyStopIntraMon(CCmdUI* pCmdUI);
	afx_msg void OnqyStartIntraMon();
	afx_msg void OnUpdateqyStartIntraMon(CCmdUI* pCmdUI);
	afx_msg void OncfgBhbSysOptions();
	afx_msg void OncfgBhbScannedNetSegs();
	afx_msg void OnUpdatecfgBhbSysOptions(CCmdUI* pCmdUI);
	afx_msg void OnUpdatecfgBhbScannedNetSegs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyCfgSwitchPolicyGrps(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyMgrSwitchPolicyGrps(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnqyNetDevEventAll();
	afx_msg void OnqyStopSnmpScan();
	afx_msg void OnUpdateqyStopSnmpScan(CCmdUI* pCmdUI);
	afx_msg void OnqyStartSnmpScan();
	afx_msg void OnUpdateqyStartSnmpScan(CCmdUI* pCmdUI);
	afx_msg void OnqySearchnetDevEvent();
	afx_msg void OnqySearchpcEvent();
	afx_msg void OnqySearchpcList();
	afx_msg void OnqySearchmac();
	afx_msg void OnqySearchip();
	afx_msg void OnqySearchunusedConn();
	afx_msg void OnqyStopMacScan();
	afx_msg void OnUpdateqyStopMacScan(CCmdUI* pCmdUI);
	afx_msg void OnqyStartMacScan();
	afx_msg void OnUpdateqyStartMacScan(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyNetworkView(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyConnectionView(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyNetworkSpeedView(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyNetDevEventAll(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqySearchnetDevEvent(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqySearchpcEvent(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqySearchpcList(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqySearchmac(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqySearchip(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqySearchunusedConn(CCmdUI* pCmdUI);
	afx_msg void OnqyOpEventAll();
	afx_msg void OnUpdateqyOpEventAll(CCmdUI* pCmdUI);
	afx_msg void OnqyStopWatchIp();
	afx_msg void OnUpdateqyStopWatchIp(CCmdUI* pCmdUI);
	afx_msg void OnqyStartWatchIp();
	afx_msg void OnUpdateqyStartWatchIp(CCmdUI* pCmdUI);
	afx_msg void OnqySearchpcSpList();
	afx_msg void OncfgInterMonIp();
	afx_msg void OnSysStart();
	afx_msg void OnUpdateSysStart(CCmdUI* pCmdUI);
	afx_msg void OnSysStop();
	afx_msg void OnUpdateSysStop(CCmdUI* pCmdUI);
	afx_msg void OnLogDisplay();
	afx_msg void OnLogDisplayOff();
	afx_msg void OnqyStartPermitNat();
	afx_msg void OnUpdateqyStartPermitNat(CCmdUI* pCmdUI);
	afx_msg void OnqyStopPermitNat();
	afx_msg void OnUpdateqyStopPermitNat(CCmdUI* pCmdUI);
	afx_msg void OnqyAssetsView();
	afx_msg void OnUpdateqyassetsview(CCmdUI *pCmdUI);
	afx_msg void OnUpdateqyPcSpList(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqySearchpcSpList(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyReportAssetsInfobyMac(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyReportAssetsInfobyOs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyReportAssetsInfoenbyMac(CCmdUI* pCmdUI);
	afx_msg void OnUpdateqyReportAssetsInfoenbyOs(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg  BOOL  OnToolTipText(  UINT  id,  NMHDR  *  pNMHDR,  LRESULT  *  pResult  );
	afx_msg  LRESULT  OnQyHotKey( WPARAM, LPARAM );
	afx_msg  LRESULT  OnQyComm( WPARAM, LPARAM );
	afx_msg  LRESULT  OnQyPostComm( WPARAM, LPARAM );
	afx_msg  LRESULT  OnQyTrayNotify( WPARAM, LPARAM );
	//  afx_msg  LRESULT  OnQyGraphNotify_mediaFile( WPARAM, LPARAM );
	//  afx_msg  LRESULT  OnQyGraphNotify_mediaDevice( WPARAM, LPARAM );
	DECLARE_MESSAGE_MAP()
public:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__F21E10C9_D664_4E6F_9F30_50A42622943F__INCLUDED_)
