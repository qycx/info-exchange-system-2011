// DlgCfgStandardName.cpp : implementation file
//

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qymc.h"
#include	"DlgCfgStandardName.h"
#include	"qyCusResTemp.h"
#include	"myDb.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgStandardName dialog


CDlgCfgStandardName::CDlgCfgStandardName(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCfgStandardName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCfgStandardName)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	memset(  &m_var,  0,  sizeof(  m_var  )  );
}

 QY_DMITEM  CONST_myRegInfoTable[]  =
{
	{	IDC_CHECK_zb,			(  TCHAR  *  )4,	},
	{	IDC_CHECK_bb,			(  TCHAR  *  )3,	},
	{	IDC_CHECK_dw,			(  TCHAR  *  )2,	},
	{	IDC_CHECK_bm,			(  TCHAR  *  )1,	},
	{	IDC_CHECK_syr,			(  TCHAR  *  )0,	},
	//
	{	IDC_EDIT_zb,			(  TCHAR  *  )4,	},
	{	IDC_EDIT_bb,			(  TCHAR  *  )3,	},
	{	IDC_EDIT_dw,			(  TCHAR  *  )2,	},
	{	IDC_EDIT_bm,			(  TCHAR  *  )1,	},
	{	IDC_EDIT_syr,			(  TCHAR  *  )0,	},
	//
	{	IDC_EDIT_zb_standard,	(  TCHAR  *  )4,	},
	{	IDC_EDIT_bb_standard,	(  TCHAR  *  )3,	},
	{	IDC_EDIT_dw_standard,	(  TCHAR  *  )2,	},
	{	IDC_EDIT_bm_standard,	(  TCHAR  *  )1,	},
	{	IDC_EDIT_syr_standard,	(  TCHAR  *  )0,	},
	//	
	{	-1,			},
};


 BOOL  CDlgCfgStandardName::bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  char  *  mac0,  int  id  )
{
	 QY_MC			*	pQyMc	=	QY_GET_GBUF(  );
	 QNM_REG_INFO		regInfo;
	 int				index;
	 int				i;


	 QM_dbFuncs  *  pDbFuncs  =  QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  return  FALSE;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	 if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;

	 m_var.pObjDb  =  pObjDb;	//  2007/01/02

	 if  (  bMacValid(  mac0  )  )  {

		 if  (  !g_dbFuncs.pf_bGetPcInfoByMac(  m_var.pObjDb->pDb,  mac0,  TRUE,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  0,  &regInfo  )  )  memset(  &regInfo,  0,  sizeof(  regInfo  )  );
	 
		 m_var.oldCusName.iType  =  CONST_cusNameType_pcRegInfo;

		 i  =  0;	index  =  getRegIndexByFieldId(  CONST_fieldId_zb  );
		 lstrcpyn(  m_var.oldCusName.objNames[i],  (  TCHAR  *  )regInfo.u.cols[index],  mycountof(  m_var.oldCusName.objNames[i]  )  );
		 i  ++  ;	index  =  getRegIndexByFieldId(  CONST_fieldId_bb  );
		 lstrcpyn(  m_var.oldCusName.objNames[i],  (  TCHAR  *  )regInfo.u.cols[index],  mycountof(  m_var.oldCusName.objNames[i]  )  );
		 i  ++  ;	index  =  getRegIndexByFieldId(  CONST_fieldId_dw  );
		 lstrcpyn(  m_var.oldCusName.objNames[i],  (  TCHAR  *  )regInfo.u.cols[index],  mycountof(  m_var.oldCusName.objNames[i]  )  );
		 i  ++  ;	index  =  getRegIndexByFieldId(  CONST_fieldId_bm  );
		 lstrcpyn(  m_var.oldCusName.objNames[i],  (  TCHAR  *  )regInfo.u.cols[index],  mycountof(  m_var.oldCusName.objNames[i]  )  );
		 i  ++  ;	index  =  getRegIndexByFieldId(  CONST_fieldId_syr  );
		 lstrcpyn(  m_var.oldCusName.objNames[i],  (  TCHAR  *  )regInfo.u.cols[index],  mycountof(  m_var.oldCusName.objNames[i]  )  );

		 bGetCusNameBySth(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  &m_var.oldCusName,  0,  &m_var.oldCusName  );

		}
	 else  {
		   m_var.id  =  id;
		   if  (  !bGetCusNameBySth(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  0,  id,  &m_var.oldCusName  )  )  memset(  &m_var.oldCusName,  0,  sizeof(  m_var.oldCusName  )  );
		   
	 }

	 return  TRUE;
}


 BOOL  CDlgCfgStandardName::bSetDlgInfo(  int  iDlgType,  QY_OBJ_DB  *  pObjDb,  LPCTSTR  misServName,  QY_MESSENGER_ID  *  pIdInfo,  int  id  )
{
	 QY_MC					*	pQyMc	=	QY_GET_GBUF(  );
	 QY_MESSENGER_REGINFO		regInfo;
	 int						index;
	 int						i;
	 
	 QM_dbFuncs  *  pDbFuncs  =  QY_GET_qmDbFuncs(  );
	if  (  !pDbFuncs  )  return  FALSE;
	QM_dbFuncs  &  g_dbFuncs  =  *pDbFuncs;


	 if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;

	 m_var.pObjDb  =  pObjDb;	//  2007/01/02

	 if  (  misServName  &&  pIdInfo  )  {

		 if  (  !g_dbFuncs.pf_bGetMessengerInfoBySth(  m_var.pObjDb->pDb,  pObjDb->cfg.iDbType,  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  misServName,  pIdInfo,  0,  NULL,  &regInfo,  0,  NULL  )  )  memset(  &regInfo,  0,  sizeof(  regInfo  )  );
	 
		 m_var.oldCusName.iType  =  CONST_cusNameType_pcRegInfo;

		 i  =  0;	index  =  getRegIndexByFieldId(  CONST_fieldId_zb  );
		 lstrcpyn(  m_var.oldCusName.objNames[i],  (  TCHAR  *  )regInfo.u.cols[index],  mycountof(  m_var.oldCusName.objNames[i]  )  );
		 i  ++  ;	index  =  getRegIndexByFieldId(  CONST_fieldId_bb  );
		 lstrcpyn(  m_var.oldCusName.objNames[i],  (  TCHAR  *  )regInfo.u.cols[index],  mycountof(  m_var.oldCusName.objNames[i]  )  );
		 i  ++  ;	index  =  getRegIndexByFieldId(  CONST_fieldId_dw  );
		 lstrcpyn(  m_var.oldCusName.objNames[i],  (  TCHAR  *  )regInfo.u.cols[index],  mycountof(  m_var.oldCusName.objNames[i]  )  );
		 i  ++  ;	index  =  getRegIndexByFieldId(  CONST_fieldId_bm  );
		 lstrcpyn(  m_var.oldCusName.objNames[i],  (  TCHAR  *  )regInfo.u.cols[index],  mycountof(  m_var.oldCusName.objNames[i]  )  );
		 i  ++  ;	index  =  getRegIndexByFieldId(  CONST_fieldId_syr  );
		 lstrcpyn(  m_var.oldCusName.objNames[i],  (  TCHAR  *  )regInfo.u.cols[index],  mycountof(  m_var.oldCusName.objNames[i]  )  );

		 bGetCusNameBySth(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  &m_var.oldCusName,  0,  &m_var.oldCusName  );

		}
	 else  {
		   m_var.id  =  id;
		   if  (  !bGetCusNameBySth(  m_var.pObjDb->pDb,  m_var.pObjDb->cfg.iDbType,  0,  id,  &m_var.oldCusName  )  )  memset(  &m_var.oldCusName,  0,  sizeof(  m_var.oldCusName  )  );
		   
	 }

	 return  TRUE;
}


void CDlgCfgStandardName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCfgStandardName)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCfgStandardName, CDialog)
	//{{AFX_MSG_MAP(CDlgCfgStandardName)
	ON_BN_CLICKED(IDC_CHECK_zb, OnCHECKzb)
	ON_BN_CLICKED(IDC_CHECK_bb, OnCHECKbb)
	ON_BN_CLICKED(IDC_CHECK_dw, OnCHECKdw)
	ON_BN_CLICKED(IDC_CHECK_bm, OnCHECKbm)
	ON_BN_CLICKED(IDC_CHECK_syr, OnCHECKsyr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCfgStandardName message handlers

#define		CONST_sym_unselected	_T(  "*"  )


BOOL CDlgCfgStandardName::OnInitDialog() 
{
	CDialog::OnInitDialog();
	QY_MC					*	pQyMc		=	QY_GET_GBUF(  );
	QY_DMITEM				*	pItem;
	int							idc;
	int							idcEdit;
	int							idcEdit_standard;
	int							i;

	cusDlgRes(  0,  &pQyMc->cusRes,  this->m_hWnd,  this->IDD  );

	i  =  0;	idc					=	IDC_CHECK_zb;
				idcEdit				=	IDC_EDIT_zb;
				idcEdit_standard	=	IDC_EDIT_zb_standard;
				SetDlgItemText(  idcEdit,  m_var.oldCusName.objNames[i]  );
				SetDlgItemText(  idcEdit_standard,  m_var.oldCusName.cusNames[i]  );
				pItem  =  qyGetDmItemByType(  CONST_myRegInfoTable,  idc,  0  );
				if  (  (  int  )pItem->des  <  pQyMc->cfg.custom.nDwLevels  &&  lstrcmpi(  m_var.oldCusName.objNames[i],  CONST_sym_unselected  )  )  GetDlgItem(  idc  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );
				else  {
					  GetDlgItem(  idcEdit  )->EnableWindow(  FALSE  );
					  GetDlgItem(  idcEdit_standard  )->EnableWindow(  FALSE  );
				}
	i  ++  ;	idc					=	IDC_CHECK_bb;
				idcEdit				=	IDC_EDIT_bb;
				idcEdit_standard	=	IDC_EDIT_bb_standard;
				SetDlgItemText(  idcEdit,  m_var.oldCusName.objNames[i]  );
				SetDlgItemText(  idcEdit_standard,  m_var.oldCusName.cusNames[i]  );
				pItem  =  qyGetDmItemByType(  CONST_myRegInfoTable,  idc,  0  );
				if  (  (  int  )pItem->des  <  pQyMc->cfg.custom.nDwLevels  &&  lstrcmpi(  m_var.oldCusName.objNames[i],  CONST_sym_unselected  )  )  GetDlgItem(  idc  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );
				else  {
					  GetDlgItem(  idcEdit  )->EnableWindow(  FALSE  );
					  GetDlgItem(  idcEdit_standard  )->EnableWindow(  FALSE  );
				}
	i  ++  ;	idc					=	IDC_CHECK_dw;
				idcEdit				=	IDC_EDIT_dw;
				idcEdit_standard	=	IDC_EDIT_dw_standard;
				SetDlgItemText(  idcEdit,  m_var.oldCusName.objNames[i]  );
				SetDlgItemText(  idcEdit_standard,  m_var.oldCusName.cusNames[i]  );
				pItem  =  qyGetDmItemByType(  CONST_myRegInfoTable,  idc,  0  );
				if  (  (  int  )pItem->des  <  pQyMc->cfg.custom.nDwLevels  &&  lstrcmpi(  m_var.oldCusName.objNames[i],  CONST_sym_unselected  )  )  GetDlgItem(  idc  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );
				else  {
					  GetDlgItem(  idcEdit  )->EnableWindow(  FALSE  );
					  GetDlgItem(  idcEdit_standard  )->EnableWindow(  FALSE  );
				}
	i  ++  ;	idc					=	IDC_CHECK_bm;
				idcEdit				=	IDC_EDIT_bm;
				idcEdit_standard	=	IDC_EDIT_bm_standard;
				SetDlgItemText(  idcEdit,  m_var.oldCusName.objNames[i]  );
				SetDlgItemText(  idcEdit_standard,  m_var.oldCusName.cusNames[i]  );
				pItem  =  qyGetDmItemByType(  CONST_myRegInfoTable,  idc,  0  );
				if  (  (  int  )pItem->des  <  pQyMc->cfg.custom.nDwLevels  &&  lstrcmpi(  m_var.oldCusName.objNames[i],  CONST_sym_unselected  )  )  GetDlgItem(  idc  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );
				else  {
					  GetDlgItem(  idcEdit  )->EnableWindow(  FALSE  );
					  GetDlgItem(  idcEdit_standard  )->EnableWindow(  FALSE  );
				}
	i  ++  ;	idc					=	IDC_CHECK_syr;
				idcEdit				=	IDC_EDIT_syr;
				idcEdit_standard	=	IDC_EDIT_syr_standard;
				SetDlgItemText(  idcEdit,  m_var.oldCusName.objNames[i]  );
				SetDlgItemText(  idcEdit_standard,  m_var.oldCusName.cusNames[i]  );
				pItem  =  qyGetDmItemByType(  CONST_myRegInfoTable,  idc,  0  );
				if  (  (  int  )pItem->des  <  pQyMc->cfg.custom.nDwLevels  &&  lstrcmpi(  m_var.oldCusName.objNames[i],  CONST_sym_unselected  )  )  GetDlgItem(  idc  )->SendMessage(  BM_SETCHECK,  BST_CHECKED,  0  );
				else  {
					  GetDlgItem(  idcEdit  )->EnableWindow(  FALSE  );
					  GetDlgItem(  idcEdit_standard  )->EnableWindow(  FALSE  );
				}

	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


//
#define  MACRO_setSth(  ucbSel  )  {	if  (  ucbSel  )  {																					\
											GetDlgItemText(  idcEdit,  cusName.objNames[index],  mycountof(  cusName.objNames[index]  )  );	\
											tTrim(  cusName.objNames[index]  );																\
											GetDlgItemText(  idcEdit_standard,  cusName.cusNames[index],  mycountof(  cusName.cusNames[index]  )  );	\
											tTrim(  cusName.cusNames[index]  );																			\
											}																											\
										else  {  lstrcpyn(  cusName.objNames[index],  CONST_sym_unselected,  mycountof(  cusName.objNames[index]  )  );		\
																lstrcpyn(  cusName.cusNames[index],  CONST_sym_unselected,  mycountof(  cusName.cusNames[index]  )  );  \
										}	\
									    if  (  !cusName.cusNames[index][0]  )  {	\
											_sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s %s %s"  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_afterStandard  ),  qyGetDesByType(  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_fieldIdTable  ),  fieldId  ),  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_cannotBeEmpty  )  );	\
											qyShowHint(  tBuf  );  \
											GetDlgItem(  idcEdit_standard  )->SetFocus(  );  return;  }  \
									}

											


 BOOL  bSetStandardRegInfo(  void  *  pDb,  int  iDbType,  QY_CUSNAME_RCD  *  pCusName  );


 void CDlgCfgStandardName::OnOK() 
{
	QY_MC			*	pQyMc								=	QY_GET_GBUF(  );
	int					iDbType								=	m_var.pObjDb->cfg.iDbType;
	unsigned  char		ucbZb								=	FALSE;
	unsigned  char		ucbBb								=	FALSE;
	unsigned  char		ucbDw								=	FALSE;
	unsigned  char		ucbBm								=	FALSE;
	unsigned  char		ucbSyr								=	FALSE;
	QY_DMITEM		*	pItem								=	NULL;
	int					fieldId;
	int					idcEdit;
	int					idcEdit_standard;
	int					index;
	QY_CUSNAME_RCD		cusName;
	TCHAR				tBuf[128];
	

	// TODO: Add extra validation here
	if  (  GetDlgItem(  IDC_CHECK_zb  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  ucbZb  =  TRUE;
	if  (  GetDlgItem(  IDC_CHECK_bb  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  ucbBb  =  TRUE;
	if  (  GetDlgItem(  IDC_CHECK_dw  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  ucbDw  =  TRUE;
	if  (  GetDlgItem(  IDC_CHECK_bm  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  ucbBm  =  TRUE;
	if  (  GetDlgItem(  IDC_CHECK_syr  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  ucbSyr  =  TRUE;

	memset(  &cusName,  0,  sizeof(  cusName  )  );
	cusName.iType  =  CONST_cusNameType_pcRegInfo;

	index  =  0;
	fieldId  =  CONST_fieldId_zb;
	idcEdit  =  IDC_EDIT_zb;
	idcEdit_standard  =  IDC_EDIT_zb_standard;
	MACRO_setSth(  ucbZb  );
	//
	index  ++  ;
	fieldId  =  CONST_fieldId_bb;
	idcEdit  =  IDC_EDIT_bb;
	idcEdit_standard  =  IDC_EDIT_bb_standard;
	MACRO_setSth(  ucbBb  );
	//
	index  ++  ;
	fieldId  =  CONST_fieldId_dw;
	idcEdit  =  IDC_EDIT_dw;
	idcEdit_standard  =  IDC_EDIT_dw_standard;
	MACRO_setSth(  ucbDw  );
	//
	index  ++  ;
	fieldId  =  CONST_fieldId_bm;
	idcEdit  =  IDC_EDIT_bm;
	idcEdit_standard  =  IDC_EDIT_bm_standard;
	MACRO_setSth(  ucbBm  );
	//
	index  ++  ;
	fieldId  =  CONST_fieldId_syr;
	idcEdit  =  IDC_EDIT_syr;
	idcEdit_standard  =  IDC_EDIT_syr_standard;
	MACRO_setSth(  ucbSyr  );


	if  (  !ucbZb  &&  !ucbBb  &&  !ucbDw  &&  !ucbBm  &&  !ucbSyr   )  {
		qyShowHint(  getResStr(  0, &pQyMc->cusRes,  CONST_resId_standardPolicyCannotBeEmpty  )  );  return;
	}
	
	if  (  AfxMessageBox(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_ifStandard  ),  MB_YESNO  |  MB_DEFBUTTON2  )  !=  IDYES  )  return;


	if  (  !bSetStandardRegInfo(  m_var.pObjDb->pDb,  iDbType,  &cusName  )  )  {
		qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_standardUsrInfoFailed  )  );  return;
	}

	//  这里再问是否存入规范库

	if  (  AfxMessageBox(  getResStr(  0, &pQyMc->cusRes,  CONST_resId_whetherToSaveStandardRule  ),  MB_YESNO  |  MB_DEFBUTTON1  )  ==  IDYES  )  {
		if  (  !bSetCusName(  m_var.pObjDb->pDb,  iDbType,  m_var.id,  &cusName,  0  )  )  {
			qyShowHint(  getResStr(  0,  &pQyMc->cusRes,  CONST_resId_saveStandardRuleFailed  )  );  return;
		}
		memcpy(  &m_var.cusName,  &cusName,  sizeof(  m_var.cusName  )  );
	}

	
//  errLabel:
	CDialog::OnOK();
}


#define		MACRO_setSql(  )  {	if  (  lstrcmpi(  pCusName->objNames[index],  CONST_sym_unselected  )  )  { 			\
									pItem  =  qyGetDmItemByType(  CONST_regInfo2DbTable,  fieldId,  0  );	\
									if  (  setPart[0]  )  _sntprintf(  setPart,  mycountof(  setPart  ),  _T(  "%s,"  ),  setPart  );	\
									_sntprintf(  setPart,  mycountof(  setPart  ),  _T(  "%scol%d=%s"  ),  setPart,  (  int  )pItem->des,  getDbValStr(  iDbType,  (  int  )pItem->pData,  pCusName->cusNames[index]  )  );	\
									if  (  wherePart[0]  )  _sntprintf(  wherePart,  mycountof(  wherePart  ),  _T(  "%s and"  ),  wherePart  );		\
									_sntprintf(  wherePart,  mycountof(  wherePart  ),  _T(  "%s col%d=%s"  ),  wherePart,  (  int  )pItem->des,  getDbValStr(  iDbType,  (  int  )pItem->pData,  pCusName->objNames[index]  )  );	\
								}  }
								

 BOOL  bSetStandardRegInfo(  void  *  pDb,  int  iDbType,  QY_CUSNAME_RCD  *  pCusName  )
{
	BOOL				bRet								=	FALSE;
	TCHAR				sqlBuf[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	TCHAR				setPart[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	TCHAR				wherePart[CONST_maxSqlBufLen  +  1]	=	_T(  ""  );
	QY_DMITEM		*	pItem								=	NULL;
	int					fieldId;
	int					index;
	QY_MC			*	pQyMc								=	QY_GET_GBUF(  );
	TCHAR			*	pTabName_regInfo					=	NULL;
	TCHAR			*	pTabName_regInfo1					=	NULL;

	if  (  pCusName->iType  !=  CONST_cusNameType_pcRegInfo  )  goto  errLabel;
	
	index  =  0;  fieldId  =  CONST_fieldId_zb;
	MACRO_setSql(  );
	index  ++;  fieldId  =  CONST_fieldId_bb;
	MACRO_setSql(  );
	index  ++;  fieldId  =  CONST_fieldId_dw;
	MACRO_setSql(  );
	index  ++;  fieldId  =  CONST_fieldId_bm;
	MACRO_setSql(  );
	index  ++;  fieldId  =  CONST_fieldId_syr;
	MACRO_setSql(  );

	switch  (  pQyMc->iServiceId  )  {
			case  CONST_qyServiceId_netMc:
				  pTabName_regInfo  =  CONST_tabName_qyPcRegInfoTab;
				  pTabName_regInfo1  =  CONST_tabName_qyPcRegInfoTab1;
				  break;
			case  CONST_qyServiceId_is:
				  pTabName_regInfo  =  CONST_tabName_qyImObjRegInfoTab;
				  pTabName_regInfo1  =  CONST_tabName_qyImObjRegInfoTab1;
				  break;
			default:
					goto  errLabel;
	}

	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set %s where %s"  ),  pTabName_regInfo,  setPart,  wherePart  );
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;
	_sntprintf(  sqlBuf,  mycountof(  sqlBuf  ),  _T(  "update %s set %s where %s"  ),  pTabName_regInfo1,  setPart,  wherePart  );
	if  (  !bQyExecSql(  pDb,  sqlBuf  )  )  goto  errLabel;
	
	bRet  =  TRUE;
errLabel:
	return  bRet;
}


 int  CDlgCfgStandardName::procCheck(  int  idcCheck,  int  idcEdit,  int  idcEdit_standard  )
{
	if  (  GetDlgItem(  idcCheck  )->SendMessage(  BM_GETCHECK,  0,  0  )  ==  BST_CHECKED  )  {
		SetDlgItemText(  idcEdit,  _T(  ""  )  );
		SetDlgItemText(  idcEdit_standard,  _T(  ""  )  );
		GetDlgItem(  idcEdit  )->EnableWindow(  TRUE  );
		GetDlgItem(  idcEdit_standard  )->EnableWindow(  TRUE  );
		}
	else  {
		  SetDlgItemText(  idcEdit,  CONST_sym_unselected  );
		  SetDlgItemText(  idcEdit_standard,  CONST_sym_unselected  );
		  GetDlgItem(  idcEdit  )->EnableWindow(  0  );
		  GetDlgItem(  idcEdit_standard  )->EnableWindow(  0  );

	}

	return  0;
}

 void CDlgCfgStandardName::OnCHECKzb() 
{
	// TODO: Add your control notification handler code here
	procCheck(  IDC_CHECK_zb,  IDC_EDIT_zb,  IDC_EDIT_zb_standard  );

}

void CDlgCfgStandardName::OnCHECKbb() 
{
	// TODO: Add your control notification handler code here
	procCheck(  IDC_CHECK_bb,  IDC_EDIT_bb,  IDC_EDIT_bb_standard  );
	
}

void CDlgCfgStandardName::OnCHECKdw() 
{
	// TODO: Add your control notification handler code here
	procCheck(  IDC_CHECK_dw,  IDC_EDIT_dw,  IDC_EDIT_dw_standard  );
	
}

void CDlgCfgStandardName::OnCHECKbm() 
{
	// TODO: Add your control notification handler code here
	procCheck(  IDC_CHECK_bm,  IDC_EDIT_bm,  IDC_EDIT_bm_standard  );
	
}

void CDlgCfgStandardName::OnCHECKsyr() 
{
	// TODO: Add your control notification handler code here
	procCheck(  IDC_CHECK_syr,  IDC_EDIT_syr,  IDC_EDIT_syr_standard  );
	
}
