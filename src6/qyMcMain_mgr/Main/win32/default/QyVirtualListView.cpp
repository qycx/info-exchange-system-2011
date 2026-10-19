// QyVirtualListView.cpp : implementation file
//

#include	"stdafx.h"
#include	<afxtempl.h>
#include	<windowsx.h>
#include	"qyMcMainCommon.h"
#include	"qyCommCommon.h"
#include	"myresource.h"
#include	"qyRcdset.h"
#include	"qyMcDoc.h"
#include	"QyVirtualListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQyVirtualListView

IMPLEMENT_DYNCREATE(CQyVirtualListView, CListView)

CQyVirtualListView::CQyVirtualListView()
{
	memset(  &var, 0, sizeof(  var  )  );
	var.m_nItemSelected  =  -1;
	var.m_nColSelected  =  -1;
}

CQyVirtualListView::~CQyVirtualListView()
{
}


BEGIN_MESSAGE_MAP(CQyVirtualListView, CListView)
	//{{AFX_MSG_MAP(CQyVirtualListView)
	ON_NOTIFY_REFLECT(LVN_GETDISPINFO, OnGetdispinfo)
	ON_COMMAND(IDC_BTN0, OnBtn0)
	ON_UPDATE_COMMAND_UI(IDC_BTN0, OnUpdateBtn0)
	ON_COMMAND(IDC_BTN1, OnBtn1)
	ON_UPDATE_COMMAND_UI(IDC_BTN1, OnUpdateBtn1)
	ON_COMMAND(IDC_BTN2, OnBtn2)
	ON_UPDATE_COMMAND_UI(IDC_BTN2, OnUpdateBtn2)
	ON_COMMAND(IDC_BTN3, OnBtn3)
	ON_UPDATE_COMMAND_UI(IDC_BTN3, OnUpdateBtn3)
	ON_COMMAND(IDC_BTN4, OnBtn4)
	ON_UPDATE_COMMAND_UI(IDC_BTN4, OnUpdateBtn4)
	ON_NOTIFY_REFLECT(LVN_ITEMCHANGED, OnItemchanged)
	ON_COMMAND(IDC_BTN5, OnBtn5)
	ON_UPDATE_COMMAND_UI(IDC_BTN5, OnUpdateBtn5)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	ON_NOTIFY_REFLECT(NM_DBLCLK, OnDblclk)
	//}}AFX_MSG_MAP
	ON_MESSAGE(  QY_WM_COMM,  OnQyComm  )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQyVirtualListView drawing

void CQyVirtualListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CQyVirtualListView diagnostics

#ifdef _DEBUG
void CQyVirtualListView::AssertValid() const
{
	CListView::AssertValid();
}

void CQyVirtualListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CQyVirtualListView message handlers

CQyMcDoc * CQyVirtualListView::GetDocument(  )
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CQyMcDoc)));
	return (CQyMcDoc*)m_pDocument;
}

BOOL CQyVirtualListView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.lpszName = WC_LISTVIEW;  
	cs.style &= ~LVS_TYPEMASK;
	cs.style |= LVS_REPORT;
	cs.style |= LVS_EDITLABELS;
	cs.style |= LVS_OWNERDATA;
	
	return CListView::PreCreateWindow(cs);
}

 void CQyVirtualListView::OnInitialUpdate() 
{
	QY_MC			*	pQyMc		=	(  QY_MC  *  )QY_GET_GBUF(  );
	QY_MC_DOCSTRUCT	*	pDocStruct	=	&GetDocument(  )->m_docStruct;
	QY_MC_QUERY		*	pQuery		=	NULL;
	CRecordset		*	pRs			=	(  CRecordset  *  )&GetDocument(  )->m_rs;
	int					iErr		=	-1;
	CListCtrl		&	ListCtrl	=	GetListCtrl();
	int					i;
	DWORD				dwStyle		=	0;

	traceLogA(  "CQyVirtualListView::OnInitialUpdate(  )."  );

	if  (  pDocStruct->iDocType  !=  CONST_qyDocType_mcQuery  )  goto  errLabel;				
	if  (  !GetDocument(  )->bDocAvail(  )  )  goto  errLabel;

	pQuery		=	&GetDocument(  )->m_docStruct.u.query;
	
	try  {

		 i  =  SendMessage(  TCM_GETUNICODEFORMAT,  0,  0  );

		//  由于记录集中的数据要经过处理，变换才能显示，不一定列数一致，故去掉这一项判断
		//  if  (  pRs->GetODBCFieldCount(  )  !=  pQuery->nFields  )  goto  errLabel;
		
		var.data2DisplayProc  =  pQuery->data2DisplayProc;
		var.display2DataProc  =  pQuery->display2DataProc;

		dwStyle  =  LVS_REPORT  |  LVS_SHOWSELALWAYS;
		if  (  !pQuery->ucbMultiSel  )  dwStyle  |=  LVS_SINGLESEL;		//  2007/08/24, 准备支持多选
		ModifyStyle(  LVS_TYPEMASK,  dwStyle  );						//  ModifyStyle( LVS_TYPEMASK, LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL );
		//
		ListCtrl.SetExtendedStyle( LVS_EX_FULLROWSELECT | LVS_EX_ONECLICKACTIVATE );
		
		m_LargeImageList.Create( IDB_LARGEICONS, 32, 1, RGB( 255, 255, 255 ) );
		m_SmallImageList.Create( IDB_SMALLICONS, 16, 1, RGB( 255, 255, 255 ) );
		ListCtrl.SetImageList( &m_LargeImageList, LVSIL_NORMAL );
		ListCtrl.SetImageList( &m_SmallImageList, LVSIL_SMALL );

		LV_COLUMN	lvcolumn;
		lvcolumn.mask	=	LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvcolumn.fmt	=	LVCFMT_LEFT;
		lvcolumn.cx		=	120;
		
		for  (  i  =  0;  i  <  pQuery->nFields; i  ++  )  {
					 
			 lvcolumn.fmt				=	pQuery->columns[i].fmt;
			 lvcolumn.cx				=	pQuery->columns[i].width;
			 lvcolumn.pszText			=	pQuery->columns[i].label;
			 
			 ListCtrl.InsertColumn(  i,  &lvcolumn  );		//  insert column
			 
		}

		CListView::OnInitialUpdate();

		}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CQyVirtualListView::OnInitialUpdate failed."  )  );
		   goto  errLabel;
	}


	iErr  =  0;

errLabel:

	if  (  iErr  )  {
		GetParentFrame(  )->PostMessage(  WM_CLOSE  );
	}
	
}


 //  采用SetAbsolutePosition(  ),  改为下面的方案
 /*
 void  CQyVirtualListView::OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	LV_DISPINFO		*	pDispInfo	=	(  LV_DISPINFO *  )pNMHDR;
	CQyRcdset		*	pRecordset  =	(  CQyRcdset  *  )&GetDocument(  )->m_docStruct.rs;
	char				szValue[QY_MAXPATHLEN + 1];
	CDBVariant			varVal;		
	long				index		=	pDispInfo->item.iItem + 1;
	long				iSubItem	= 	pDispInfo->item.iSubItem;

	if  (  pDispInfo->item.mask  &  LVIF_TEXT  )  {
		
		TRY		{
			pRecordset->SetAbsolutePosition(  index  );		//set the file to desired index
			}
		CATCH  (  CDBException,  e  )	{
			traceLogA(  e->m_strError.GetBuffer(  0  )  );
			return;		
			}
		END_CATCH
				
			//
			//  int							m_nDataType[QY_MAXCOLS];
	 		//  CArray	< void *, void * >	pRecordset->m_arrayValue;
			//  
		int	i	=	iSubItem;
		strcpy(  szValue,  ""  );
		switch  (  pRecordset->m_nDataType[i]  )  {
					
				case  SQL_BIT:
					if  (  *( ( BOOL * )pRecordset->m_arrayValue[i]  )  )	strcpy(  szValue, "TRUE"  );
				  	else	strcpy(  szValue, "FALSE"  );
					break;
				case  SQL_TINYINT:
					sprintf(  szValue, "%c",  *( ( BYTE * )pRecordset->m_arrayValue[i]  )  );
					break;
				case  SQL_SMALLINT:
					sprintf(  szValue,  "%d",  *( ( int * )pRecordset->m_arrayValue[i]  )  );
					break;
				case  SQL_INTEGER:
					sprintf(  szValue,  "%d",  *( ( long * )pRecordset->m_arrayValue[i]  )  );
					break;
				case  SQL_REAL:
					sprintf(  szValue,  "%f",  *( ( float * )pRecordset->m_arrayValue[i]  )  );
					break;
				case  SQL_FLOAT:
				case  SQL_DOUBLE:
					sprintf(  szValue,  "%f",  *( ( double * )pRecordset->m_arrayValue[i]  )  );
					break;
				case  SQL_DATE:
				case  SQL_TIME:
				case  SQL_TIMESTAMP:
					sprintf(  szValue,  "%s", ( ( CTime * )pRecordset->m_arrayValue[i]  )->Format( "%A, %B %d, %Y" )  );
					break;
				case  SQL_BINARY:
				case  SQL_VARBINARY:
					sprintf(  szValue,  "A binary or varBinary."  );
					break;
				case  SQL_DECIMAL:
				case  SQL_NUMERIC:
				case  SQL_CHAR:
				case  SQL_VARCHAR:
					sprintf(  szValue,  "%s",  *( ( CString * )pRecordset->m_arrayValue[i]  )  );
					break;
				case  SQL_LONGVARCHAR:
				case  SQL_LONGVARBINARY:
					sprintf(  szValue,  "A long varChar or longVarBinary."  );
					break;
				default:
					traceLogA(  "Serious error:  CQyVirutalListView::OnGetdispinfo(  ): dataType error."  );
					break;
		}
	
		if  (  var.data2DisplayProc  )  var.data2DisplayProc(  pQyMc,  iSubItem,  szValue,  pDispInfo->item.pszText,  pDispInfo->item.cchTextMax  );
		else  lstrcpyn(  pDispInfo->item.pszText,  szValue,  pDispInfo->item.cchTextMax  );	//  set item text

	}
	
	if  (  pDispInfo->item.mask  &  LVIF_IMAGE  )  pDispInfo->item.iImage  =  0;		//  set image to first in list

	*pResult = 0;

	return;

}
*/


 void  CQyVirtualListView::OnGetdispinfo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	QY_MC			*	pQyMc		=	QY_GET_GBUF(  );
	LV_DISPINFO		*	pDispInfo	=	(  LV_DISPINFO *  )pNMHDR;
	CQyRcdset		*	pRecordset  =	(  CQyRcdset  *  )&GetDocument(  )->m_rs;
	QY_MC_QUERY		*	pQuery		=	GetDocument(  )->getMcQuery(  );
	TCHAR				szValue[QY_MAXPATHLEN + 1];
	long				index		=	pDispInfo->item.iItem;
	long				iSubItem	= 	pDispInfo->item.iSubItem;
	CString				str;


	if  (  pDispInfo->item.mask  &  LVIF_TEXT  )  {
		
		try		{
			pRecordset->MoveFirst(  );
			pRecordset->Move(  index  );		//set the file to desired index

			//
			//  int							m_nDataType[QY_MAXCOLS];
	 		//  CArray	< void *, void * >	pRecordset->m_arrayValue;
		
			if  (  !pRecordset->IsEOF(  )  )  {
				int	i	=	iSubItem;
			
				lstrcpyn(  szValue,  _T(  ""  ),  sizeof(  szValue  )  /  sizeof(  szValue[0]  )  );
				switch  (  pRecordset->m_nDataType[i]  )  {
					
						case  SQL_BIT:
							  if  (  *( ( BOOL * )pRecordset->m_arrayValue[i]  )  )	lstrcpyn(  szValue, _T(  "TRUE"  ),  sizeof(  szValue  )  /  sizeof(  szValue[0]  )  );
				  			  else	lstrcpyn(  szValue, _T(  "FALSE"  ),  sizeof(  szValue  )  /  sizeof(  szValue[0]  )  );
							  break;
						case  SQL_TINYINT:
							  _sntprintf(  szValue,  sizeof(  szValue  )  /  sizeof(  szValue[0]  ),  _T(  "%c"  ),  *( ( BYTE * )pRecordset->m_arrayValue[i]  )  );
							  break;
						case  SQL_SMALLINT:
							  _sntprintf(  szValue,   sizeof(  szValue  )  /  sizeof(  szValue[0]  ),  _T(  "%d"  ),  *( ( int * )pRecordset->m_arrayValue[i]  )  );
							  break;
						case  SQL_INTEGER:
							  _sntprintf(  szValue,  sizeof(  szValue  )  /  sizeof(  szValue[0]  ),  _T(  "%d"  ),  *( ( long * )pRecordset->m_arrayValue[i]  )  );
							  break;
						case  SQL_REAL:
							  _sntprintf(  szValue,  sizeof(  szValue  )  /  sizeof(  szValue[0]  ),  _T(  "%f"  ),  *( ( float * )pRecordset->m_arrayValue[i]  )  );
							  break;
						case  SQL_FLOAT:
						case  SQL_DOUBLE:
							  _sntprintf(  szValue,  sizeof(  szValue  )  /  sizeof(  szValue[0]  ),  _T(  "%f"  ),  *( ( double * )pRecordset->m_arrayValue[i]  )  );
							  break;
						case  SQL_DATE:
						case  SQL_TIME:
						case  SQL_TIMESTAMP:
							  _sntprintf(  szValue,  sizeof(  szValue  )  /  sizeof(  szValue[0]  ),  _T(  "%s"  ), ( ( CTime * )pRecordset->m_arrayValue[i]  )->Format( "%A, %B %d, %Y" )  );
							  break;
						case  SQL_BINARY:
						case  SQL_VARBINARY:
							  _sntprintf(  szValue,  sizeof(  szValue  )  /  sizeof(  szValue[0]  ),  _T(  "A binary or varBinary."  )  );
							  break;
						case  SQL_DECIMAL:
						case  SQL_NUMERIC:
						case  SQL_CHAR:
						case  SQL_VARCHAR:
							  str  =  *( ( CString * )pRecordset->m_arrayValue[i]  );
							  _sntprintf(  szValue,  sizeof(  szValue  )  /  sizeof(  szValue[0]  ),  _T(  "%s"  ),  *( ( CString * )pRecordset->m_arrayValue[i]  )  );
							  break;
						case  SQL_LONGVARCHAR:
						case  SQL_LONGVARBINARY:
							  _sntprintf(  szValue,  sizeof(  szValue  )  /  sizeof(  szValue[0]  ),  _T(  "A long varChar or longVarBinary."  )  );
							  break;
						default:
								MACRO_qyAssert(  0,  _T(  "Serious error:  CQyVirutalListView::OnGetdispinfo(  ): dataType error"  )  );
								break;
				}
				
				if  (  var.data2DisplayProc  )  var.data2DisplayProc(  pQyMc,  pQuery,  pRecordset,  iSubItem,  pDispInfo->item.pszText,  pDispInfo->item.cchTextMax  );
				else  lstrcpyn(  pDispInfo->item.pszText,  CString(  szValue  ),  pDispInfo->item.cchTextMax  );	//  set item text

				if  (  pDispInfo->item.mask  &  LVIF_IMAGE  )  {
					//  设置显示图标
					if  (  pQuery->type  ==  CONST_qyQueryType_netMcEventList  ||  pQuery->type  ==  CONST_qyQueryType_netDevEventList  )  pDispInfo->item.iImage  =  0;		//  set image to first in list
					else  if  (  pQuery->type  ==  CONST_qyQueryType_netMcScannedIpList  )  pDispInfo->item.iImage  =  4;
					else  pDispInfo->item.iImage  =  2;
				}
			
			}

			}
	catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CQyVirtualListView::OnGetdispinfo failed."  )  );
		   goto  errLabel;
	}
	
	}
	
errLabel:

	*pResult = 0;

	return;

}


void CQyVirtualListView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	CListCtrl	&	ListCtrl	=	GetListCtrl(  );
	QY_MC_QUERY	*	pQuery	=	NULL;
	int				nItem	=	0;
	int				cnt;

	traceLogA(  "CQyVirtualListView::OnUpdate(  )."  );

	ListCtrl.DeleteAllItems(  );

	pQuery		=	&GetDocument(  )->m_docStruct.u.query;
	cnt			=	GetDocument(  )->m_rs.GetRecordCount(  );
	if  (  cnt  <  0  )  cnt  =  0;

	ListCtrl.SendMessage( LVM_SETITEMCOUNT, (WPARAM)cnt, (LPARAM)LVSICF_NOINVALIDATEALL );

	nItem  =  pQuery->curnItem;
	if  (  nItem  >=  cnt  )  nItem  =  cnt  -  1;				//  2003/9/5.
	if  (  nItem  >= 0  )  {
		ListView_EnsureVisible(  this->m_hWnd, nItem,  FALSE  );
		ListCtrl.SetItemState(  nItem,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING,  LVIS_SELECTED | LVIS_FOCUSED | LVIS_ACTIVATING );
		ListCtrl.Update(  nItem  );
	}
		
}

 static  int  sGetDisplayStr(  CArray  < void *, void * >  *	 pArrayValue,  int  i,  int  iDataType,  char  *  szValue,  unsigned  int  size  )
{
	 szValue[0]  =  0;
	 switch  (  iDataType  )  {
							
			 case  SQL_BIT:
				   if  (  *( ( BOOL * )(  *pArrayValue  )[i]  )  )	strcpy(  szValue, "TRUE"  );
				   else	 strcpy(  szValue, "FALSE"  );
				   break;
			 case  SQL_TINYINT:
				   sprintf(  szValue, "%c",  *( ( BYTE * )(  *pArrayValue  )[i]  )  );
				   break;
			 case  SQL_SMALLINT:
				   sprintf(  szValue,  "%d",  *( ( int * )(  *pArrayValue  )[i]  )  );
				   break;
			 case  SQL_INTEGER:
				   sprintf(  szValue,  "%d",  *( ( long * )(  *pArrayValue  )[i]  )  );
				   break;
			 case  SQL_REAL:
				   sprintf(  szValue,  "%f",  *( ( float * )(  *pArrayValue  )[i]  )  );
				   break;
			 case  SQL_FLOAT:
			 case  SQL_DOUBLE:
				   sprintf(  szValue,  "%f",  *( ( double * )(  *pArrayValue  )[i]  )  );
				   break;
			 case  SQL_DATE:
			 case  SQL_TIME:
			 case  SQL_TIMESTAMP:
				   sprintf(  szValue,  "%s", ( ( CTime * )(  *pArrayValue  )[i]  )->Format( "%A, %B %d, %Y" )  );
				   break;
			 case  SQL_BINARY:
			 case  SQL_VARBINARY:
				   sprintf(  szValue,  "A binary or varBinary."  );
				   break;
			 case  SQL_DECIMAL:
			 case  SQL_NUMERIC:
			 case  SQL_CHAR:
			 case  SQL_VARCHAR:
				   sprintf(  szValue,  "%s",  *( ( CString * )(  *pArrayValue  )[i]  )  );
				   break;
			 case  SQL_LONGVARCHAR:
			 case  SQL_LONGVARBINARY:
				   sprintf(  szValue,  "A long varChar or longVarBinary."  );
				   break;
			 default:
					 traceLogA(  "Serious error:  CQyVirutalListView::OnGetdispinfo(  ): dataType error."  );
					 break;
	 }
	
	 return  0;
}


 LRESULT CQyVirtualListView::OnQyComm(  WPARAM wParam,  LPARAM lParam  )
{
	long					lRet				=					-1;
	QY_WMBUF_COMM		*	pComm				=					( QY_WMBUF_COMM * )lParam;
	QY_MC_QUERY			*	pQuery				=					NULL;
	int						i;
	QY_MC				*	pQyMc				=					QY_GET_GBUF(  );

	if  (  !pComm  )  goto  errLabel;

	switch  (  pComm->uiType  )  {
			case  QY_WMPARAM_REFRESHDATA:
				  if  (  GetDocument(  )->m_docStruct.iDocType  ==  CONST_qyDocType_mcQuery  )  {
					  pQuery			=	&GetDocument(  )->m_docStruct.u.query;
					  pQuery->curnItem  =	pComm->u.refreshData.curnRow;
				  }														//  2003/9/5
				  GetDocument(  )->bRefreshData( TRUE  );
				  GetDocument(  )->UpdateAllViews(  NULL  );
				  break;
			case  CONST_qyWmParam_getnCol:
				  pQuery		=	&GetDocument(  )->m_docStruct.u.query;
				  for  (  i  =  0;  pQuery->columns[i].type  !=  -1;  i  ++  )  {
					   if  (  !lstrcmpi(  pQuery->columns[i].label,  CString(  pComm->u.getnCol.colName  )  )  )  break;
				  }
				  if  (  pQuery->columns[i].type  ==  -1  )  goto  errLabel;
				  pComm->u.getnCol.nCol  =  i;
				  break;
			case  CONST_qyWmParam_export:  {
				  CQyRcdset			*	pRecordset  =	(  CQyRcdset  *  )&GetDocument(  )->m_rs;
				  QY_MC_QUERY		*	pQuery		=	GetDocument(  )->getMcQuery(  );
				  QNM_WMBUF_EXPORT	*	pWmExport	=	(  QNM_WMBUF_EXPORT  *  )pComm;
				  char					szValue[QY_MAXPATHLEN + 1];
				  char					buf[1024];
				  int					j			=  0;
				  int					cnt			=  0;
				  CFile					file;
				  char					fileBuf[1024];
				  TCHAR					tBuf[1024];

				  //  取一下文档的标题
				  _sntprintf(  pWmExport->exportInfo.docTitle,  mycountof(  pWmExport->exportInfo.docTitle  ),  _T(  "%s"  ),  GetDocument(  )->GetTitle(  )  );	//  2006/02/25

				  if  (  !file.Open(  CString(  pWmExport->exportInfo.fileName  ),  CFile::modeCreate | CFile::modeWrite  )  )  goto  errLabel;

				  try		{
					  				  
					  cnt  =  pRecordset->GetRecordCount(  );
					  
					  //  写文件开头
					  switch  (  pWmExport->exportInfo.iFileType  )  {
							  case  CONST_qyFileType_excel:
								    buf[0]  =  (  char  )0xff;  buf[1]  =  (  char  )0xfe;
								    file.Write(  buf,  2  );
									//
								    for  (  j  =  0;  j  <  pQuery->nFields;  j  ++  )  {
										 //  myTChar2Str(  pQuery->columns[j].label,  buf,  sizeof(  buf  )  );
										 //  file.Write(  buf,  strlen(  buf  )  );
										 file.Write(  pQuery->columns[j].label, lstrlen(  pQuery->columns[j].label  )  *  sizeof(   TCHAR  )  ); 
										 file.Write(  _T(  "\t"  ),  1  *  sizeof(  TCHAR  )  );
					  				}
					  				file.Write(  _T(  "\r\n"  ),  2  *  sizeof(  TCHAR  )  );
									file.Write(  _T(  "\r\n"  ),  2  *  sizeof(  TCHAR  )  );
									break;
							  case  CONST_qyFileType_html:
								    _snprintf(  fileBuf,  sizeof(  fileBuf  ),  "<html>\r\n"  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
									_snprintf(  fileBuf,  sizeof(  fileBuf  ),  "<HEAD><META http-equiv=Content-Type content=\"text/html; charset=utf-8\"></HEAD>\r\n"  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
									_snprintf(  fileBuf,  sizeof(  fileBuf  ),  "<body>\r\n"  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
									_snprintf(  fileBuf,  sizeof(  fileBuf  ),  "<table border style='border-collapse:collapse'>\r\n"  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
									_snprintf(  fileBuf,  sizeof(  fileBuf  ),  "<tr><th colspan=%d><b>%s</b></th></tr>\r\n",  pQuery->nFields,  myTChar2Utf8(  CString(  GetDocument()->GetTitle( )  ).GetBuffer(  0  ),  buf,  sizeof(  buf  )  )  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
									_snprintf(  fileBuf,  sizeof(  fileBuf  ),  "<tr>"  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
									for  (  j  =  0;   j  <  pQuery->nFields;  j  ++  )  {
										 _snprintf(  fileBuf,  sizeof(  fileBuf  ),  "<th><b>%s</b></th>",  myTChar2Utf8(  pQuery->columns[j].label,  buf,  sizeof(  buf  )  )  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
									}
									_snprintf(  fileBuf,  sizeof(  fileBuf  ),  "</tr>\r\n"  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
									break;
							  default:
									  break;
					  }

					  //  文件体
					  for  (  i  =  0;  i  <  cnt;  i  ++  )  {
						   if  (  !i  )	 pRecordset->MoveFirst(  );
						   else  pRecordset->MoveNext(  );
						   if  (  pRecordset->IsEOF(  )  )  break;
						   
						   //  行头
						   switch  (  pWmExport->exportInfo.iFileType  )  {
								   case  CONST_qyFileType_html:
									     _snprintf(  fileBuf,  sizeof(  fileBuf  ),  "<tr>"  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
										 break;
								   default:
											break;
						   }

						   //  记录
						   for  (  j  =  0;  j  <  pQuery->nFields;  j  ++  )  {
							    sGetDisplayStr(  &pRecordset->m_arrayValue,  j,  pRecordset->m_nDataType[j],  szValue,  sizeof(  szValue  )  );
								if  (  var.data2DisplayProc  )  var.data2DisplayProc(  pQyMc,  pQuery,  pRecordset,  j,  tBuf,  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );
								else  lstrcpyn(  tBuf,  CString(  szValue  ),  sizeof(  tBuf  )  /  sizeof(  tBuf[0]  )  );	//  set item text
								switch  (  pWmExport->exportInfo.iFileType  )  {
										case  CONST_qyFileType_excel:
											  filterStr2Display(  tBuf,  -1  );
											  if  (  tBuf[0]  ==  _T(  '-'  )  )  {	//  2006/09/07, 在excel中-似乎是特殊字符，需要加个空格在前面
												  TCHAR	*	pT  =  _T(  " "  );
												  file.Write(  pT,  lstrlen(  pT  )  *  sizeof(  TCHAR  )  );
											  }
											  file.Write(  tBuf,  lstrlen(  tBuf  )  *  sizeof(  TCHAR  )  );
											  file.Write(  _T(  "\t"  ),  1  *  sizeof(  TCHAR  )  );											  
											  break;
										case  CONST_qyFileType_html:
											  myTChar2Utf8(  tBuf,  buf,  sizeof(  buf  )  );
											  _snprintf(  fileBuf,  sizeof(  buf  ),  "<td>%s</td>",  buf  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
											  break;											  
										default:
												traceLogA(  "rcd[%d][%d] is %s",  i,  j,  buf  );
												break;
								}
								
						   }
						   //  行尾
						   switch  (  pWmExport->exportInfo.iFileType  )  {
								   case  CONST_qyFileType_excel:
									     file.Write(  _T(  "\r\n"  ),  2  *  sizeof(  TCHAR  )  );
										 break;
								   case  CONST_qyFileType_html:
									     _snprintf(  fileBuf,  sizeof(  fileBuf  ),  "</tr>\r\n"  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
										 break;
								   default:
											break;
						   }						   
					  }
				  
					  //  文件尾
					  switch  (  pWmExport->exportInfo.iFileType  )  {
							  case  CONST_qyFileType_html:
								    _snprintf(  fileBuf,  sizeof(  fileBuf  ),  "</table>\r\n"  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
									_snprintf(  fileBuf,  sizeof(  fileBuf  ),  "</body>\r\n"  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
								    _snprintf(  fileBuf,  sizeof(  fileBuf  ),  "</html>\r\n"  );  file.Write(  fileBuf,  strlen(  fileBuf  )  );
									break;
							  default:
										break;
					  }


					}

					catch  (  CException  *  e  )  {
						e->Delete(  );
						qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CQyVirtualListView::OnQyComm failed."  )  );
						goto  errLabel;
					}
	
					file.Close(  );
				   }
				  break;
			default:
					goto  errLabel;
	}

	lRet	=	QY_RC_WMOK;

errLabel:

	return  lRet;

}


 int CQyVirtualListView::getItemContent(  int nItem,  QY_ITEMCONTENT  *  pItem  )
{
	int					iErr		=			-1;
	QY_MC			*	pQyMc		=			QY_GET_GBUF(  );
	CQyMcDoc		*	pDoc		=			GetDocument(  );
	CListCtrl		&	ListCtrl	=			GetListCtrl(  );
	CRecordset		*	pRs			=			(  CRecordset  *  )&GetDocument(  )->m_rs;
	int					nFields		=			pRs->GetODBCFieldCount(  );
	
	
	if  (  nItem  <  0  )  goto  errLabel;

	traceLogA(  "CQyVirtualListView::getItemContent not implemented"  );
	//  iErr		=			0;

errLabel:
	 return				iErr;
}


 int CQyVirtualListView::getSelectedItemContent(  QY_ITEMCONTENT  *  pItemContent  )
{
	 return  getItemContent(  var.m_nItemSelected,  pItemContent  );
}

 
 void CQyVirtualListView::OnItemchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CListCtrl		&	listCtrl	=	GetListCtrl(  );

	var.m_nItemSelected  =  pNMListView->iItem;

	traceLogA(  "OnItemChanged: m_nItemSelected is %d.",  var.m_nItemSelected  );

	*pResult = 0;
}



 void CQyVirtualListView::OnBtn0() 
{	
	
}

void CQyVirtualListView::OnUpdateBtn0(CCmdUI* pCmdUI) 
{
}

 void CQyVirtualListView::OnBtn1() 
{

	
}

void CQyVirtualListView::OnUpdateBtn1(CCmdUI* pCmdUI) 
{
	
}

 void CQyVirtualListView::OnBtn2() 
{
	
}

void CQyVirtualListView::OnUpdateBtn2(CCmdUI* pCmdUI) 
{
	
}

void CQyVirtualListView::OnBtn3() 
{
		
}

void CQyVirtualListView::OnUpdateBtn3(CCmdUI* pCmdUI) 
{
	BOOL		bStatus		=	FALSE;
	
	pCmdUI->Enable(  bStatus  );	
	
}

void CQyVirtualListView::OnBtn4() 
{
}

void CQyVirtualListView::OnUpdateBtn4(CCmdUI* pCmdUI) 
{
	BOOL		bStatus		=	FALSE;
	
	pCmdUI->Enable(  bStatus  );	
	
}


void CQyVirtualListView::OnBtn5() 
{
	
}

 void CQyVirtualListView::OnUpdateBtn5(CCmdUI* pCmdUI) 
{
 	BOOL			bStatus		=	FALSE;
	
	pCmdUI->Enable(  bStatus  );	
	
}


 void CQyVirtualListView::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW		*	pNMListView =	(NM_LISTVIEW*)pNMHDR;
	CQyMcDoc		*	pDoc		=	GetDocument(  );
	int					iSubItem	=	pNMListView->iSubItem;
	TCHAR				buf[1024];
	QY_MC_QUERY		*	pQuery		=	NULL;	
	// TODO: Add your control notification handler code here

	traceLogA(  "OnColumnclick: iItem is %d, iSubItem is %d",  pNMListView->iItem,  pNMListView->iSubItem  );

	if  (  pDoc->m_docStruct.iDocType  !=  QY_DOCTYPE_MCQUERY  )  goto  errLabel;
	pQuery  =  &pDoc->m_docStruct.u.query;
	if  (  pNMListView->iItem  !=  -1  )  goto  errLabel;
	if  (  pNMListView->iSubItem  >=  pDoc->m_docStruct.u.query.nSqlFields  )  goto  errLabel;

	//  没有数据库对应项，也不能排序
	if  (  !pDoc->m_docStruct.u.query.sqlColumns[iSubItem].label[0]  )  goto  errLabel;

	if  (  var.m_nColSelected  ==  iSubItem  )  var.bDesc  =  !var.bDesc;
	else  {
		var.m_nColSelected  =  iSubItem;
		var.bDesc  =  FALSE;
	}
	
	_sntprintf(  buf,  sizeof(  buf  )  /  sizeof(  buf[0]  ),  _T(  "%s %s"  ),  pQuery->sqlColumns[iSubItem].label,  var.bDesc  ?  _T(  "Desc"  )  :  _T(  "Asc"  )  );
	pDoc->bSortData(  buf  );
	pDoc->UpdateAllViews(  NULL  );

errLabel:

	*pResult = 0;

}



 void CQyVirtualListView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{	
	// TODO: Add your control notification handler code here
	QY_MC			*	pQyMc		=		QY_GET_GBUF(  );
	CListCtrl		&	listCtrl	=		GetListCtrl(  );
	CQyMcDoc		*	pDoc		=		GetDocument(  );
	int					iCurItem;
	QY_EVENTINFO		tmpEventInfo;
	
	DWORD  dwPos  =  GetMessagePos(  );

	// Convert the co-ords into a CPoint structure 
	CPoint  point(  GET_X_LPARAM(  dwPos  ),  GET_Y_LPARAM(  dwPos  )  ),  spt;
	spt  =  point;
	
	// Convert to screen co-ords for hittesting 
	listCtrl.ScreenToClient(  &spt  );

	UINT  test;
	iCurItem  =  listCtrl.HitTest(  spt,  &test  );

	memset(  &tmpEventInfo,  0,  sizeof(  tmpEventInfo  )  );
	tmpEventInfo.type  =  CONST_qyEventType_rClick;
	tmpEventInfo.hWnd  =  this->m_hWnd;
	tmpEventInfo.click.x  =  point.x;
	tmpEventInfo.click.y  =  point.y;

	// Did the click occur on an item 
	if  (  iCurItem  <  0  ||  !(  test  &  (  TVHT_ONITEM  |  TVHT_ONITEMRIGHT  )  )  )  {		//  2006/04/16, 修改，为使点击列表空白处时能弹出特殊的菜单
		tmpEventInfo.ucbNotSelected  =  TRUE;
		if  (  !pDoc->m_docStruct.u.query.nSubMenuPos_notSel  )  goto  errLabel;
	}	

	//  2007/08/24, 要考虑一下多选中的情况
	if  (  listCtrl.GetSelectedCount(  )  >  1  )  {
		tmpEventInfo.ucbMultiSelected  =  TRUE;	
		if  (  !pDoc->m_docStruct.u.query.nSubMenuPos_multiSel  )  goto  errLabel;
	}

	if  (  pDoc->m_docStruct.u.query.pfProcEvent  )  {
		pDoc->m_docStruct.u.query.pfProcEvent(  pQyMc,  pDoc,  &tmpEventInfo  );
	}
	
errLabel:	

	*pResult = 0;

}



 void CQyVirtualListView::OnDblclk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	QY_MC		*		pQyMc		=		QY_GET_GBUF(  );
	CListCtrl		&	listCtrl	=		GetListCtrl(  );
	CQyMcDoc		*	pDoc		=		GetDocument(  );
	int					iCurItem;
	QY_EVENTINFO		tmpEventInfo;

	DWORD dwPos = GetMessagePos();

	/* Convert the co-ords into a CPoint structure */
	CPoint point( GET_X_LPARAM( dwPos ), GET_Y_LPARAM( dwPos ) ), spt;
	spt = point;
	
	/* Convert to screen co-ords for hittesting */
	listCtrl.ScreenToClient( &spt );

	UINT test;
	iCurItem = listCtrl.HitTest( spt, &test );
	
	/* Did the click occur on an item */
	if ( iCurItem < 0 || !( test & ( TVHT_ONITEM | TVHT_ONITEMRIGHT ) ) )  goto errLabel;

	memset(  &tmpEventInfo,  0,  sizeof(  tmpEventInfo  )  );
	tmpEventInfo.type  =  CONST_qyEventType_dblClick;
	tmpEventInfo.hWnd  =  this->m_hWnd;
	tmpEventInfo.click.x  =  point.x;
	tmpEventInfo.click.y  =  point.y;
	tmpEventInfo.uiDefaultCmd  =  pDoc->m_docStruct.u.query.uiDefaultCmd;

	if  (  pDoc->m_docStruct.u.query.pfProcEvent  )  pDoc->m_docStruct.u.query.pfProcEvent(  pQyMc,  pDoc,  &tmpEventInfo  );
		
errLabel:	
		
	*pResult = 0;

}



