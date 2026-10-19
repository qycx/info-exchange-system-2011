// qyMcDoc.cpp : implementation of the CQyMcDoc class
//

#include	"stdafx.h"
#include	<afxtempl.h>
#include	"qyMcMainCommon.h"
#include	"qyOpenShellCommon.h"
#include	"qyMcMainWndProc.h"

#include	"qyMc.h"
#include	"qyRcdset.h"
//  #include	"qyBulkset.h"
#include	"qyMcDoc.h"
  #include	"mainClient.h"
//  #include	"qyDialogBar.h"
#include	"mainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


 static  BAR_CFG  sRootBarCfg  =	//  McRoot的配置
{
				  5,
				  {
					  {	"滚动日志",	1,	},
					  {	"告警信息",	1,	},
					  { "日志查询", 1,	},
					  {	"生成报表",	1,	},
					  {	"滚动定制",	1,	},					  
				  },
};



/////////////////////////////////////////////////////////////////////////////
// CQyMcDoc

IMPLEMENT_DYNCREATE(CQyMcDoc, CDocument)

BEGIN_MESSAGE_MAP(CQyMcDoc, CDocument)
	//{{AFX_MSG_MAP(CQyMcDoc)
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQyMcDoc construction/destruction

CQyMcDoc::CQyMcDoc()
{
	// TODO: add one-time construction code here
	memset( &this->m_docStruct, 0, sizeof( this->m_docStruct ) );

}


CQyMcDoc::~CQyMcDoc()
{
	int	i = 0;

	switch  (  this->m_docStruct.iDocType  ) {
			case  QY_DOCTYPE_MCSITE:
			case  QY_DOCTYPE_MCWEB:
				  if  (  this->m_docStruct.m_pMcObj  )  {
					  delete  this->m_docStruct.m_pMcObj;	 this->m_docStruct.m_pMcObj = NULL;
				  }
				  break;				
			case  QY_DOCTYPE_MCQUERY:
				  if  (  this->m_rs.IsOpen(  )  )  {
					  this->m_rs.Close(  );
				  }
				  break;
			case  QY_DOCTYPE_MCROOT:
			case  QY_DOCTYPE_MC:
			default:
				break;
	}

	ASSERT(  !this->m_docStruct.m_pMcObj  );
	ASSERT(  !this->m_rs.IsOpen(  )  );
			
	return;

}

 BOOL  CQyMcDoc::bSetQyMcDoc(  QY_MC_SEL  *  pSel  )
{
	 BOOL			bRet	=	FALSE;
 	 QY_MC		*	pQyMc	=	QY_GET_GBUF(  );
	 CDBVariant		varVal[1];
	 BAR_CFG	*	pBarCfg	=	NULL;
	 CString		tmpCStr;
	 QY_OBJ_DB	*	pObj	=	NULL;

	 switch  (  pSel->type  )  {
			 
			 case  CONST_qySelType_mcQuery:

				   if  (  !pSel->u.query.nFields  )  goto  errLabel;

				   m_docStruct.iDocType  =  CONST_qyDocType_mcQuery;
				   memcpy(  &m_docStruct.u.query,  &pSel->u.query,  sizeof(  pSel->u.query  )  );

				   //  traceLog(  _T(  "bSetQyMcDoc(  ),  sqlStr is %s %s %s %s %s %s"  ),  pSel->u.query.selectPart,  pSel->u.query.fromPart,  pSel->u.query.wherePart[0]  ?  _T(  "where"  )  :  _T(  ""  ),  pSel->u.query.wherePart,  pSel->u.query.sortPart[0]  ?  _T(  "order by"  )  :  _T(  ""  ),  pSel->u.query.sortPart  );

				   if  (  1  )  {	//  2006/08/12, 增加了一点打印信息
					   OutputDebugString(  pSel->u.query.selectPart  );
					   OutputDebugString(  _T(  " "  )  );
					   OutputDebugString(  pSel->u.query.fromPart  );
					   OutputDebugString(  _T(  " "  )  );
					   OutputDebugString(  pSel->u.query.wherePart[0]  ?  _T(  "where"  )  :  _T(  ""  )  );
					   OutputDebugString(  _T(  " "  )  );
					   OutputDebugString(  pSel->u.query.wherePart  );
					   OutputDebugString(  _T(  " "  )  );
					   OutputDebugString(  pSel->u.query.sortPart[0]  ?  _T(  "order by"  )  :  _T(  ""  )  );
					   OutputDebugString(  _T(  " "  )  );
					   OutputDebugString(  pSel->u.query.sortPart  );
					   OutputDebugString(  _T(  "\n"  )  );
				   }

				   if  (  !(  pObj  =  getProcedObjDb(  0,  pSel->u.query.iDsnIndex  )  )  )  {
					   traceLogA(  "iDsnIndex error"  );  goto  errLabel;
				   }
				   if  (  !pObj->ucbLoaded  )  {
					   traceLogA(  "dsn is unloaded"  );  goto  errLabel;
				   }

				   try  {
					    if  (  this->m_rs.Initialize(  pObj->pDb,  CString(  pSel->u.query.selectPart  )  +  " "   +  pSel->u.query.fromPart,  pSel->u.query.wherePart,  pSel->u.query.sortPart,  pSel->u.query.nSqlFields,  pSel->u.query.sqlColumns  )  )  goto  errLabel;
					    m_rs.SetFilter(  pSel->u.query.wherePart  );
					   }
				   catch  (  CException  *  e  )  {
						  e->Delete(  );
		   				  qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CQyMcDoc::bSetQyMcDoc failed."  )  );
						  goto  errLabel;
				   }
					   
				   lstrcpyn(  m_docStruct.dsnName,  pObj->cfg.sysName,  mycountof(  m_docStruct.dsnName  )  );

				   if  (  pSel->u.query.type  ==  CONST_qyQueryType_general  )  lstrcpyn(  m_docStruct.postDocName,  _T(  "查询窗"  ),  sizeof(  m_docStruct.postDocName  )  /  sizeof(  TCHAR  )  );				   						
				   else  if  (  pSel->u.query.type  ==  CONST_qyQueryType_mcCfgUrlList  )  lstrcpyn(  m_docStruct.postDocName,  _T(  "网址列表配置窗"  ),  sizeof(  m_docStruct.postDocName  )  /  sizeof(  TCHAR  )  );					   		 
				   else  {
					     lstrcpyn(  m_docStruct.preDocName,  pSel->u.query.preDocName,  sizeof(  m_docStruct.preDocName  )  /  sizeof(  TCHAR  )  );	
						 lstrcpyn(  m_docStruct.docName,  pSel->u.query.docName,  sizeof(  m_docStruct.docName  )  /  sizeof(  TCHAR  )  );
						 lstrcpyn(  m_docStruct.postDocName,  pSel->u.query.postDocName,  sizeof(  m_docStruct.postDocName  )  /  sizeof(  TCHAR  )  );
				   }
				   this->qySetTitle(  CString(  pSel->u.query.docName  )  );
				   
				   break;

			 case  CONST_qySelType_mcRootTree:
				   m_docStruct.iDocType  =  CONST_qyDocType_mcRootTree;
				   memcpy(  &m_docStruct.u.treeList.tree,  &pSel->u.rootTree,  sizeof(  pSel->u.rootTree  )  );
				   break;
			 case  CONST_qySelType_mcView:
				   m_docStruct.iDocType  =  CONST_qyDocType_mcView;
				   memcpy(  &m_docStruct.u.mcView,  &pSel->u.mcView,  sizeof(  m_docStruct.u.mcView  )  );		//  2006/12/24

				   this->qySetTitle(  pSel->u.mcView.docName  );

				   break;
			 default:
					goto  errLabel;

	 }

	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}


 //  此函数已被废弃
 BOOL CQyMcDoc::bSetQyMcDoc(  QY_MC_DOCINFO * pDocInfo  )
{
	 BOOL			bRet	=	FALSE;
 	 QY_MC		*	pQyMc	=	QY_GET_GBUF(  );
	 CDBVariant		varVal[1];
	 BAR_CFG	*	pBarCfg	=	NULL;
	 CString		tmpCStr;

	 if  (  this->m_docStruct.m_pMcObj  )  {
		 qyDebugHint(  _T(  "CQyMcDoc::bSetQyMcDoc(  ) error: not empty!"  )  );
		 return  FALSE;
	 }
	 
	 try {
 		switch	 (  pDocInfo->iDocType  )  {
			 case  QY_DOCTYPE_MCROOT:
				   break;
			 case  QY_DOCTYPE_MC:
				   goto  errLabel;
			 case  QY_DOCTYPE_MCSITE:
				   this->m_docStruct.m_pMcObj  =  new  CQyMcObj(  1  );	
				   if  (  setQyBufData( & pDocInfo->u.site, sizeof( pDocInfo->u.site ), &this->m_docStruct.m_pMcObj->var.m_pBufs[0]  )  )
					   goto  errLabel;
				   lstrcpyn(  this->m_docStruct.postDocName,  _T(  "监视窗"  ),  sizeof(  this->m_docStruct.postDocName  )  /  sizeof(  TCHAR  )  );
				   this->qySetTitle(  CString(  pDocInfo->u.site.url  )  );
				   break;				
			 case  QY_DOCTYPE_MCWEB:
				   this->m_docStruct.m_pMcObj  =  new  CQyMcObj(  1  );
				   if  (  setQyBufData(  & pDocInfo->u.web,  sizeof(  pDocInfo->u.web ),  & this->m_docStruct.m_pMcObj->var.m_pBufs[0]  )  )
					   goto  errLabel;
				   lstrcpyn(  this->m_docStruct.preDocName,  _T(  "查看"  ),  sizeof(  this->m_docStruct.preDocName  )  /  sizeof(  TCHAR  )  );
			   	   this->qySetTitle(  CString(  pDocInfo->u.web.url  )  );
				   break;
			 case  QY_DOCTYPE_MCQUERY:
			 default:
				   goto  errLabel;
		}

		}
	 catch ( int iE ) {
		 switch  (  iE  )  {
			case QY_EXCEPTION_MALLOCFAILED:
				break;
			default:
				break;
		 }
		 qyDebugHint( _T(  "exception." )  );
		 goto  errLabel;
	 }

	 if  (  !(  pBarCfg  =  getBarCfg(  pDocInfo  )  )  )  goto  errLabel;

	 bRet  =  TRUE;

errLabel:

	 if  (  !bRet  )  {
		 if  (  m_rs.IsOpen(  )  )  m_rs.Close(  );
		 if  (  this->m_docStruct.m_pMcObj  )  {
			 delete  this->m_docStruct.m_pMcObj;  this->m_docStruct.m_pMcObj  =  NULL;
		 }
	 }
	 if  (  bRet  )  {
	 	 this->m_docStruct.iDocType		=	pDocInfo->iDocType;
		 this->m_docStruct.pBarCfg		=	pBarCfg;
	 }

	 return  bRet;

}

 void  CQyMcDoc::qySetTitle(  LPCTSTR  name  )
{
	 this->SetTitle(  CString(  m_docStruct.dsnName  )  +  (  m_docStruct.dsnName[0]  ?  " : "  :  ""  )  +  CString(  this->m_docStruct.preDocName  )  +  name  +  this->m_docStruct.postDocName  );
}


QY_MC_WEB	*	CQyMcDoc::getMcWeb(  )
{
	return	(  QY_MC_WEB  *  )this->m_docStruct.m_pMcObj->getQyBufData(  0  );
}

QY_MC_SITE	*	CQyMcDoc::getMcSite(  )
{
	return  (  QY_MC_SITE  *  )this->m_docStruct.m_pMcObj->getQyBufData(  0  );
}

QY_MC_QUERY *	CQyMcDoc::getMcQuery(  )
{
	return  (  QY_MC_QUERY  *  )&this->m_docStruct.u.query;
}


 int  CQyMcDoc::getQueryCnt(  QY_MC_QUERY  *  pQuery  )
{
	int			cnt			=	-1;
	QY_MC	*	pQyMc		=	QY_GET_GBUF(  );
	CDBVariant	varVal[1];

	if  (  !bQyGetRcdBySql(  pQyMc->gui.pDb,  getMcQueryCntStr( pQuery ).GetBuffer(  0  ),  1,  varVal  )  )  goto  errLabel;
	if  (  varVal[0].m_dwType  !=  DBVT_LONG  )  goto  errLabel;
	cnt		=		varVal[0].m_lVal;

errLabel:

	return  cnt;

}



 //  bRequeryOk 指是否重新查询，通常用在自动刷新上。若检索条件发生了变化，则取FALSE.
 BOOL  CQyMcDoc::bRefreshData(  BOOL bRequeryOk  )
{
	 BOOL		bRet	=	FALSE;
	 QY_MC	*	pQyMc	=	(  QY_MC  *  )QY_GET_GBUF(  );

	 if  (  m_docStruct.iDocType  !=  QY_DOCTYPE_MCQUERY  )  goto  errLabel;

	 try  {
		 m_rs.SetFilter(  m_rs.m_strFilter  );
		 }
	 catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CQyMcDoc::bRefreshData failed."  )  );
		   goto  errLabel;
	 }
		
	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}
	
 BOOL  CQyMcDoc::bSortData(  LPCTSTR  sortStr  )
{
	 BOOL		bRet	=	FALSE;
	 QY_MC	*	pQyMc	=	(  QY_MC  *  )QY_GET_GBUF(  );

	 if  (  m_docStruct.iDocType  !=  QY_DOCTYPE_MCQUERY  )  goto  errLabel;

	 try  {
		  m_rs.SetSort(  sortStr  );
		  _sntprintf(  this->m_docStruct.u.query.sortPart,  sizeof(  m_docStruct.u.query.sortPart  )  /  sizeof(  TCHAR  ),  _T(  "%s"  ),  CString(  sortStr  )  );
		 }
	 catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "CQyMcDoc::bSortData failed."  )  );
		   goto  errLabel;
	 }
		
	 bRet  =  TRUE;

errLabel:

	 return  bRet;

}
	

 BAR_CFG * CQyMcDoc::getBarCfg(  QY_MC_DOCINFO * pDocInfo  )
{
	 BAR_CFG	*	pBarCfg  =  NULL;
	 				   
	 pBarCfg	=  &sRootBarCfg;				 

	 return  pBarCfg;

}

 BOOL CQyMcDoc::bDocAvail(  )
{
	 BOOL  bRet  =  FALSE;
	 
	  switch  (  this->m_docStruct.iDocType  )  {
			  case  QY_DOCTYPE_MC:
				    goto  errLabel;
			  case  QY_DOCTYPE_MCSITE:
			  case  QY_DOCTYPE_MCWEB:
				    if  (  !this->m_docStruct.m_pMcObj  )  goto  errLabel;
				    break;
			  case  QY_DOCTYPE_MCQUERY:
				    if  (  !m_rs.IsOpen(  )  )  goto  errLabel;
				    break;
			  default:
				      break;		
	  }

	  bRet  =  TRUE;

errLabel:
		return  bRet;
}

BOOL CQyMcDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	memset(  &m_docStruct,  0,  sizeof(  m_docStruct  )  );
	this->m_docStruct.iDocType = QY_DOCTYPE_MC;

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CQyMcDoc serialization

void CQyMcDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
		qyDebugHint(  _T(  "output." )  );
	}
	else
	{
		// TODO: add loading code here
		qyDebugHint( _T(  "input." )  );
	}
}

/////////////////////////////////////////////////////////////////////////////
// CQyMcDoc diagnostics

#ifdef _DEBUG
void CQyMcDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CQyMcDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CQyMcDoc commands

void CQyMcDoc::OnBtn0() 
{
	// TODO: Add your command handler code here

}

void CQyMcDoc::OnUpdateBtn0(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(  this->m_docStruct.pBarCfg->btns[0].status  );

}

 void CQyMcDoc::OnBtn1() 
{	
	
}

void CQyMcDoc::OnUpdateBtn1(CCmdUI* pCmdUI) 
{
	
}



void CQyMcDoc::OnBtn2() 
{
	
}

void CQyMcDoc::OnUpdateBtn2(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	BOOL	bStatus	=	FALSE;

	switch  (  m_docStruct.iDocType  )  {
			case  QY_DOCTYPE_MCQUERY:
				  if  (  this->bDocAvail(  )  &&  this->m_docStruct.m_pMcObj->getMcQuery( )->curnItem >= 0  )
				  bStatus  =  TRUE;
				  break;
			default:
				bStatus  =  this->m_docStruct.pBarCfg->btns[1].status;
				break;
	}
	
	pCmdUI->Enable(  bStatus  );

}


void CQyMcDoc::OnBtn3() 
{
	
	
}

void CQyMcDoc::OnUpdateBtn3(CCmdUI* pCmdUI) 
{
	BOOL	bStatus	=	FALSE;

	pCmdUI->Enable(  bStatus  );
	
}

void CQyMcDoc::OnBtn4() 
{
	
}

void CQyMcDoc::OnUpdateBtn4(CCmdUI* pCmdUI) 
{
	BOOL	bStatus	=	FALSE;

	pCmdUI->Enable(  bStatus  );
	
}

