// DlgSelect.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgSelect.h"
#include ".\dlgselect.h"
#include	"qyCusResTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSelect dialog


CDlgSelect::CDlgSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSelect)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );

}

 BOOL  CDlgSelect::bSetDlgInfo(  QY_OBJ_DB  *  pObjDb,  int  iSelectType,  int  iObjType,  LPCTSTR  hint,  void  *  p0,  void  *  p1  )
{
	BOOL	bRet	=	FALSE;

	if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;

	m_var.pObjDb  =  pObjDb;
	m_var.iSelectType  =  iSelectType;
	m_var.iObjType  =  iObjType;
	if  (  hint  )  lstrcpyn(  m_var.hint,  hint,  mycountof(  m_var.hint  )  );

	switch  (  iSelectType  )  {
			case  CONST_qyQueryType_sharedDynBmpList:
				  bRet  =  TRUE;  goto  errLabel;
				  break;
			case  CONST_qyQueryType_imGrpMemList:
				  if  (  p0  )  lstrcpyn(  m_var.u.selectMessenger.misServName,  (  LPCTSTR  )p0,  mycountof(  m_var.u.selectMessenger.misServName  )  );
				  if  (  !p1  )  goto  errLabel;
				  memcpy(  &m_var.inputU.selectImGrpMem.idInfo_grp,  p1,  sizeof(  m_var.inputU.selectImGrpMem.idInfo_grp  )  );
				  bRet  =  TRUE;  goto  errLabel;
				  break;
			default:
					break;
	}

	switch  (  iObjType  )  {
			case  CONST_objType_messenger:  {
				  if  (  p0  )  lstrcpyn(  m_var.u.selectMessenger.misServName,  (  LPCTSTR  )p0,  mycountof(  m_var.u.selectMessenger.misServName  )  );
				  }
				  break;
			case  CONST_objType_imGrp:
				  if  (  p0  )  lstrcpyn(  m_var.u.selectImGrp.misServName,  (  LPCTSTR  )p0,  mycountof(  m_var.u.selectImGrp.misServName  )  );
				  break;
			case  CONST_objType_toPath:  {
				  QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
				  QY_SERVICEGUI_INFO	*	pSci  =  getServiceGuiInfo(  pQyMc,  CONST_qyServiceId_is  );
				  if  (  !pSci  )  goto  errLabel;
				  //
				  if  (  p0  )  lstrcpyn(  m_var.u.selectToPath.misServName,  (  LPCTSTR  )p0,  mycountof(  m_var.u.selectToPath.misServName  )  );
				  m_var.u.selectToPath.bPhoneGuest  =  (  BOOL  )p1;
				  //
				  if  (  !(  m_var.u.selectToPath.pProcInfo  =  (  MC_VAR_isCli  *  )pSci->pVar  )  )  goto  errLabel;
				  if  (  !(  m_var.u.selectToPath.pMisCnt  =  getMisCntByName(  pQyMc,  NULL,  m_var.u.selectToPath.misServName  )  )  )  goto  errLabel;
				  }
				  break;
			default:
					break;
	}

	bRet  =  TRUE;
errLabel:
	return  bRet;
}

void CDlgSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSelect)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSelect, CDialog)
	//{{AFX_MSG_MAP(CDlgSelect)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSelect message handlers

 int  tmpHandler_displayVistor(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	HWND				hCombo				=  (  HWND  )p0;
	//  p1
	CDBVariant	*		varVals				=	(  CDBVariant  *  )p2;
	//
	int					index				=	0;
	int					uiType;
	TCHAR				tBuf[255  +  1]		=	_T(  ""  );
	TCHAR				dw[255  +  1]		=	_T(  ""  );
	TCHAR				bm[255  +  1]		=	_T(  ""  );
	TCHAR				syr[255  +  1]		=	_T(  ""  );
	TCHAR				grpName[255  +  1]	=	_T(  ""  );
	char				buf[255  +  1]		=	"";
	QY_MESSENGER_ID		idInfo;
	TCHAR				displayName[255  +  1]	=	_T(  ""  );

	index  =  0;	MACRO_sqlLong(  varVals[index],  uiType  );
	index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &idInfo  );
	index  ++  ;	MACRO_sqlStr(  varVals[index],  dw,  mycountof(  dw  )  );  
	index  ++  ;	MACRO_sqlStr(  varVals[index],  bm,  mycountof(  bm  )  );  
	index  ++  ;	MACRO_sqlStr(  varVals[index],  syr,  mycountof(  syr  )  );  
	index  ++  ;	MACRO_sqlStr(  varVals[index],  grpName,  mycountof(  grpName  )  );

	if  (  uiType  ==  CONST_objType_messenger  )  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%I64u - %s %s %s"  ),  idInfo.ui64Id,  dw,  bm,  syr  );
	else  if  (  uiType  ==  CONST_objType_imGrp  )  _sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%I64u - %s"  ),  idInfo.ui64Id,  grpName  );
	else  goto  errLabel;

	SendMessage(  hCombo,  CB_ADDSTRING,  0,  (  LPARAM  )displayName  );

errLabel:
	return  0;

}


int  tmpHandler_displayMessenger(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	HWND				hCombo				=  (  HWND  )p0;
	//  p1
	CDBVariant	*		varVals				=	(  CDBVariant  *  )p2;
	//
	int					index				=	0;
	TCHAR				tBuf[255  +  1]		=	_T(  ""  );
	TCHAR				dw[255  +  1]		=	_T(  ""  );
	TCHAR				bm[255  +  1]		=	_T(  ""  );
	TCHAR				syr[255  +  1]		=	_T(  ""  );
	char				buf[255  +  1]		=	"";
	QY_MESSENGER_ID		idInfo;
	TCHAR				displayName[255  +  1]	=	_T(  ""  );

	index  =  0;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &idInfo  );
	index  ++  ;	MACRO_sqlStr(  varVals[index],  dw,  mycountof(  dw  )  );  
	index  ++  ;	MACRO_sqlStr(  varVals[index],  bm,  mycountof(  bm  )  );  
	index  ++  ;	MACRO_sqlStr(  varVals[index],  syr,  mycountof(  syr  )  );  

	_sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%I64u - %s %s %s"  ),  idInfo.ui64Id,  dw,  bm,  syr  );
	SendMessage(  hCombo,  CB_ADDSTRING,  0,  (  LPARAM  )displayName  );

	return  0;

}


int  tmpHandler_displayImGrp(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	HWND				hCombo				=  (  HWND  )p0;
	//  p1
	CDBVariant	*		varVals				=	(  CDBVariant  *  )p2;
	//
	int					index				=	0;
	TCHAR				tBuf[255  +  1]		=	_T(  ""  );
	char				buf[255  +  1]		=	"";
	QY_MESSENGER_ID		idInfo;
	TCHAR				displayName[255  +  1]	=	_T(  ""  );

	index  =  0;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &idInfo  );
	index  ++  ;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  

	_sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%I64u - %s"  ),  idInfo.ui64Id,  tBuf  );
	SendMessage(  hCombo,  CB_ADDSTRING,  0,  (  LPARAM  )displayName  );

	return  0;

}

int  tmpHandler_displayDynBmp(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	HWND				hCombo				=  (  HWND  )p0;
	//  p1
	CDBVariant	*		varVals				=	(  CDBVariant  *  )p2;
	//
	QY_MC		*		pQyMc				=	QY_GET_GBUF(  );
	int					index				=	0;
	TCHAR				tBuf[255  +  1]		=	_T(  ""  );
	TCHAR				dw[255  +  1]		=	_T(  ""  );
	TCHAR				bm[255  +  1]		=	_T(  ""  );
	TCHAR				syr[255  +  1]		=	_T(  ""  );
	char				buf[255  +  1]		=	"";
	QY_MESSENGER_ID		idInfo;
	unsigned  int		uiObjType			=	0;
	unsigned  short		usIndex				=	0;
	TCHAR				displayName[255  +  1]	=	_T(  ""  );

	index  =  0;	MACRO_sqlStr(  varVals[index],  tBuf,  mycountof(  tBuf  )  );  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );  idStr2Info(  buf,  &idInfo  );
	index  ++  ;	MACRO_sqlLong(  varVals[index],  uiObjType  );
	index  ++  ;	MACRO_sqlLong(  varVals[index],  usIndex  );
	index  ++  ;	MACRO_sqlStr(  varVals[index],  dw,  mycountof(  dw  )  );  
	index  ++  ;	MACRO_sqlStr(  varVals[index],  bm,  mycountof(  bm  )  );  
	index  ++  ;	MACRO_sqlStr(  varVals[index],  syr,  mycountof(  syr  )  );  

	_sntprintf(  displayName,  mycountof(  displayName  ),  _T(  "%I64u - %s %s %s, %s, %d"  ),  idInfo.ui64Id,  dw,  bm,  syr,  qyGetDesByType1(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  ),  uiObjType  ),  usIndex  );
	SendMessage(  hCombo,  CB_ADDSTRING,  0,  (  LPARAM  )displayName  );

	return  0;

}



BOOL CDlgSelect::OnInitDialog()
{
	CDialog::OnInitDialog();
	int			iErr								=	-1;
	QY_MC	*	pQyMc								=	QY_GET_GBUF(  );
	TCHAR		sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	TCHAR		tBuf[255  +  1]						=	_T(  ""  );
	CDBVariant	varVals[10];
	int			i;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	SetWindowText(  m_var.hint  );

	switch  (  m_var.iSelectType  )  {
			case  CONST_qyQueryType_sharedDynBmpList:
				  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyImObjAuthTab.uiType,qyImObjAuthTab.idStr,qyImObjRegInfoTab.col2,qyImObjRegInfoTab.col3,qyImObjRegInfoTab.col4,qyImGrpInfoTab.name from (qyImObjAuthTab left join qyImObjRegInfoTab on (qyImObjAuthTab.misServName=qyImObjRegInfoTab.misServName and qyImObjAuthTab.idStr=qyImObjRegInfoTab.idStr) ) left join qyImGrpInfoTab on (qyImObjAuthtab.misServName=qyImGrpInfoTab.misServName and qyImObjAuthTab.idStr=qyImGrpInfoTab.idStr ) where qyImObjAuthTab.misServName=%s and qyImObjAuthTab.uiType in (%d,%d) order by qyImObjAuthTab.idStr"  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_misServName,  m_var.u.selectImGrp.misServName  ),  CONST_objType_messenger,  CONST_objType_imGrp  );
				  if  (  enumSqlQuery(  m_var.pObjDb->pDb,  sqlBuf,  tmpHandler_displayVistor,  GetDlgItem(  IDC_COMBO_objList  )->m_hWnd,  0,  varVals,  mycountof(  varVals  ),  NULL  )  <  0  )  goto  errLabel;
				  iErr  =  0;  goto  errLabel;
				  break;
			case  CONST_qyQueryType_imGrpMemList:								  
				  char  idStr_grp[CONST_qyMessengerIdStrLen  +  1];
				  idInfo2Str(  &m_var.inputU.selectImGrpMem.idInfo_grp,  idStr_grp,  mycountof(  idStr_grp  )  );
				  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyImGrpMemTab.idStr_mem,qyImObjRegInfoTab.col2,qyImObjRegInfoTab.col3,qyImObjRegInfoTab.col4 from qyImGrpMemTab left join qyImObjRegInfoTab on( qyImGrpMemTab.misServName=qyImObjRegInfoTab.misServName and qyImGrpMemTab.idStr_mem=qyImObjRegInfoTab.idStr) where qyImGrpMemTab.misServName=%s and qyImGrpMemTab.idStr_grp='%s'"  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_misServName,  m_var.misServName  ),  CString(  idStr_grp  )  );
				  if  (  enumSqlQuery(  m_var.pObjDb->pDb,  sqlBuf,  tmpHandler_displayMessenger,  GetDlgItem(  IDC_COMBO_objList  )->m_hWnd,  0,  varVals,  mycountof(  varVals  ),  NULL  )  <  0  )  goto  errLabel;
				  iErr  =  0;  goto  errLabel;
				  break;
			default:
					break;
	}				  

	// TODO:  在此添加额外的初始化
	switch  (  m_var.iObjType  )  {
		    case  CONST_objType_messenger:
				  if  (  isIsMgr(  )  )  {
					  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyImObjAuthTab.idStr,qyImObjRegInfoTab.col2,qyImObjRegInfoTab.col3,qyImObjRegInfoTab.col4 from qyImObjAuthTab left join qyImObjRegInfoTab on (qyImObjAuthTab.misServName=qyImObjRegInfoTab.misServName and qyImObjAuthTab.idStr=qyImObjRegInfoTab.idStr) where qyImObjAuthTab.misServName=%s and qyImObjAuthTab.uiType in (%d) order by qyImObjAuthTab.idStr"  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_misServName,  m_var.u.selectImGrp.misServName  ),  CONST_objType_messenger  );
					  }
				  else  {
					    _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyImObjTab.idStr,qyImObjRegInfoTab.col2,qyImObjRegInfoTab.col3,qyImObjRegInfoTab.col4 from qyImObjTab left join qyImObjRegInfoTab on (qyImObjTab.misServName=qyImObjRegInfoTab.misServName and qyImObjTab.idStr=qyImObjRegInfoTab.idStr) where qyImObjTab.misServName=%s and qyImObjTab.uiType in (%d) order by qyImObjTab.idStr"  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_misServName,  m_var.u.selectImGrp.misServName  ),  CONST_objType_messenger  );					  
				  }
				  if  (  enumSqlQuery(  m_var.pObjDb->pDb,  sqlBuf,  tmpHandler_displayMessenger,  GetDlgItem(  IDC_COMBO_objList  )->m_hWnd,  0,  varVals,  mycountof(  varVals  ),  NULL  )  <  0  )  goto  errLabel;
				  break;
			case  CONST_objType_imGrp:
				  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyImObjAuthTab.idStr,qyImGrpInfoTab.name from qyImObjAuthTab left join qyImGrpInfoTab on (qyImObjAuthTab.misServName=qyImGrpInfoTab.misServName and qyImObjAuthTab.idStr=qyImGrpInfoTab.idStr) where qyImObjAuthTab.misServName=%s and qyImObjAuthTab.uiType in (%d) order by qyImObjAuthTab.idStr"  ),  getDbValStr(  pQyMc->cfg.db.iDbType,  CONST_iDataType_misServName,  m_var.u.selectImGrp.misServName  ),  CONST_objType_imGrp  );
				  if  (  enumSqlQuery(  m_var.pObjDb->pDb,  sqlBuf,  tmpHandler_displayImGrp,  GetDlgItem(  IDC_COMBO_objList  )->m_hWnd,  0,  varVals,  mycountof(  varVals  ),  NULL  )  <  0  )  goto  errLabel;
				  break;
			case  CONST_objType_toPath:  {
				  MIS_CNT	*	pMisCnt  =  m_var.u.selectToPath.pMisCnt;
				  if  (  !pMisCnt  )  goto  errLabel;

				  for  (  i  =  0;  i  <  pMisCnt->toPaths.usCnt;  i  ++  )  {
					   _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s://%s/%I64u/%s - %s"  ),  CONST_str_im,  m_var.u.selectToPath.misServName,  pMisCnt->toPaths.mems[i].idInfo_vDev.ui64Id,  pMisCnt->toPaths.mems[i].wDevIdStr,  pMisCnt->toPaths.mems[i].cusName  );
					  ::SendMessage(  GetDlgItem(  IDC_COMBO_objList  )->m_hWnd,  CB_ADDSTRING,  0,  (  LPARAM  )sqlBuf  );
				  }
				  //
				  if  (  m_var.u.selectToPath.pProcInfo->bPhoneModuleLoaded  &&  m_var.u.selectToPath.bPhoneGuest  )  {
					  _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_localToPaths  )  );
					  (  (  CComboBox  *  )GetDlgItem(  IDC_COMBO_objList  )  )->InsertString(  -1,  tBuf  );
				  }
				  //
				  }				  
				  break;
			case  CONST_objType_webcam:
			case  CONST_objType_screen:
				  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "select qyDynBmpTab.idStr,qyDynBmpTab.uiObjType,qyDynBmpTab.usIndex,qyImObjRegInfoTab.col2,qyImObjRegInfoTab.col3,qyImObjRegInfoTab.col4 "  )  );
				  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s from qyDynBmpTab left join qyImObjRegInfoTab on (qyDynBmpTab.misServName=qyImObjRegInfoTab.misServName and qyDynBmpTab.idStr=qyImObjRegInfoTab.idStr)"  ),  sqlBuf  );
				  _sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "%s order by qyImObjRegInfoTab.col0,qyDynBmpTab.idStr,qyDynBmpTab.usIndex"  ),  sqlBuf  );
				  if  (  enumSqlQuery(  m_var.pObjDb->pDb,  sqlBuf,  tmpHandler_displayDynBmp,  GetDlgItem(  IDC_COMBO_objList  )->m_hWnd,  0,  varVals,  mycountof(  varVals  ),  NULL  )  <  0  )  goto  errLabel;
				  break;
			default:
					break;
	}

	iErr  =  0;

errLabel:

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgSelect::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	QY_MC	*	pQyMc				=	QY_GET_GBUF(  );
	TCHAR		tBuf[255  +  1]		=	_T(  ""  );
	TCHAR	*	pT;
	TCHAR	*	pT1;
	char		buf[255  +  1]		=	"";

	GetDlgItemText(  IDC_COMBO_objList,  tBuf,  mycountof(  tBuf  )  );
	tTrim(  tBuf  );
	if  (  !tBuf[0]  )  {
		qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_needToSelect  )  );  return;
	}

	switch  (  m_var.iObjType  )  {
			case  CONST_objType_messenger:
				  if  (  !(  pT  =  _tcschr(  tBuf,  _T(  '-'  )  )  )  )  goto  errLabel;
				  *pT  =  0;
				  tTrim(  tBuf  );
				  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );
				  idStr2Info(  buf,  &m_var.u.selectMessenger.idInfo_selected  );				  				  
				  break;
			case  CONST_objType_imGrp:
				  if  (  !(  pT  =  _tcschr(  tBuf,  _T(  '-'  )  )  )  )  goto  errLabel;
				  *pT  =  0;
				  tTrim(  tBuf  );
				  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );
				  idStr2Info(  buf,  &m_var.u.selectImGrp.idInfo_selected  );				  
				  break;
			case  CONST_objType_toPath:
				  if  (  !_tcsicmp(  tBuf,  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_localToPaths  )  )  )  {
					  _sntprintf(  m_var.u.selectToPath.toPath,  mycountof(  m_var.u.selectToPath.toPath  ),  _T(  "%s:///0/"  ),  CONST_str_im  );
					  }
				  else  {
					    if  (  !(  pT  =  _tcschr(  tBuf,  _T(  '-'  )  )  )  )  goto  errLabel;
						*pT  =  0;
						tTrim(  tBuf  );
						//
						safeWcsnCpy(  tBuf,  m_var.u.selectToPath.toPath,  mycountof(  m_var.u.selectToPath.toPath  )  );
				  }
				  //
				  break;
			case  CONST_objType_webcam:
			case  CONST_objType_screen:
				  if  (  !(  pT  =  _tcschr(  tBuf,  _T(  '-'  )  )  )  )  goto  errLabel;
				  *pT  =  0;
				  tTrim(  tBuf  );
				  myTChar2Str(  tBuf,  buf,  mycountof(  buf  )  );
				  idStr2Info(  buf,  &m_var.u.selectDynBmp.idInfo  );				  
				  pT  ++  ;
				  if  (  !(  pT1  =  _tcsrchr(  pT,  _T(  ','  )  )  )  )  goto  errLabel;
				  *pT1  =  0;
				  pT1  ++  ;  tTrim(  pT1  );
				  m_var.u.selectDynBmp.usIndex  =  (  unsigned  short  )_ttol(  pT1  );
				  if  (  !(  pT1  =  _tcsrchr(  pT,  _T(  ','  )  )  )  )  goto  errLabel;
				  *pT1  =  0;
				  pT1  ++  ;  tTrim(  pT1  );
				  m_var.u.selectDynBmp.uiObjType  =  qyGetTypeByDes(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  ),  pT1  );
				  break;
			default:
					break;
	}



errLabel:
	CDialog::OnOK();
}

void CDlgSelect::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	OnOK();
}
