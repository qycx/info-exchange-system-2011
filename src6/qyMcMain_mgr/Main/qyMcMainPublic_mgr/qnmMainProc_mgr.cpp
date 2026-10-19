

#include	"stdafx.h"
#include	"qyMcMainCommon.h"
#include	"qyWmComm.h"
#include	"myresource.h"
#include	"qyRestrictEdit.h"
#include	"qyMc.h"

#ifndef  __isCli__
#include	"dlgCfgStandardName.h"
#endif
#include	"dlgQnmSendHint.h"
#if  10  //  ndef  __isCli__
#include	"dlgQnmEditPcUsrInfo.h"
#endif
#ifndef  __isCli__
#include	"dlgPropPcNetwork.h"
#endif
#include	"qyOpenShellCommon.h"
#if  defined  __isCli__  ||  defined  __APP_qyMc_touchscreen__
#include	"dlgTalk.h"
#endif
#include	"dlgPropMessenger.h"
#if  defined  __isCli__  ||  defined  __APP_qyMc_touchscreen__
#include	"dlgPropImTask.h"
#endif
#include	"dlgPropImMsg.h"
#include	"dlgPropImGrp.h"
#ifndef  __isCli__
#include	"dlgImGrp.h"
#endif
#include	"dlgSelect.h"
#include	"dlgNum.h"

#ifndef  __isCli__
#include	"dlgWwwQmContact.h"
#include	"dlgCfgIpKnowledge.h"
#include	"dlgPropIpKnowledge.h"

#include	"DlgMessenger.h"

#include	"dlgCfgPhoneMessenger.h"
#include	"dlgCfgGsmModem.h"
#endif

//  #include	"DlgImObjRule.h"

#ifndef  __isCli__
#include	"DlgCfgCustomerService.h"
#endif
//
#include	"qmcDynBmp.h"
//
#include	"qyCusResTemp.h"
#include	"tmpCeLib.h"

#include	"qyMcDoc.h"
#include	"myDb.h"


int  procTvEventFunc_netMc(  void  *  pQyMcParam,  void  *  pDocParamReserved,  void  *  pSelParam,  void  *  pEventInfoParam,  unsigned  int  uiCmd,  LPCTSTR  colName  );
int  procTvEventFunc_is(  void  *  pQyMcParam,  void  *  pDocParamReserved,  void  *  pSelParam,  void  *  pEventInfoParam,  unsigned  int  uiCmd,  LPCTSTR  colName  );


 int  mc_procTvEventFunc(  void  *  pQyMcParam,  void  *  pDocParamReserved,  void  *  pSelParam,  void  *  pEventInfoParam,  unsigned  int  uiCmd,  LPCTSTR  colName  )
{
	 QY_MC	*	pQyMc  =  (  QY_MC  *  )pQyMcParam;

	 switch  (  pQyMc->iServiceId  )  {
			 case  CONST_qyServiceId_netMc:
				   return  procTvEventFunc_netMc(  pQyMcParam,  pDocParamReserved,  pSelParam,  pEventInfoParam,  uiCmd,  colName  );
			 case  CONST_qyServiceId_mis:
				   return  procTvEventFunc_is(  pQyMcParam,  pDocParamReserved,  pSelParam,  pEventInfoParam,  uiCmd,  colName  );
			 default:
					break;					
	 }

	 return  -1;
}

 //
  //  该函数用于自动从数据库中提取数据填充ComboBox, 暂时不用
 BOOL  bQnmFillCol0(  QY_OBJ_DB  *  pObjDb,  LPCTSTR  sqlBuf,  HWND  hCombo,  BOOL  bFillAny  )
{
	 BOOL			bRet		=	FALSE;
	 QY_MC	*		pQyMc		=	QY_GET_GBUF(  );
	 if  (  !bObjDbAvail(  pObjDb  )  )  return  FALSE;
	 CRecordset		rs(  (  CDatabase  *  )pObjDb->pDb  );
	 int			index		=	0;
	 //  CString	sqlBuf;
	 CDBVariant		varVals[1];
	 int			cnt			=	1;
	 int			i;
	 TCHAR			tBuf[256];

	 SendMessage(  hCombo,  CB_RESETCONTENT,  0,  0  );
	 if  (  bFillAny  )  SendMessage(  hCombo,  CB_ADDSTRING,  0,  (  LPARAM  )CONST_qyAnyStr  );
	 
	 //  sqlBuf  =  CString(  "select distinct col0 from qyPcRegInfoTab order by col0"  );
	 try  {		
		  if  (  !rs.Open(  CRecordset::forwardOnly,  sqlBuf  )  )  goto  errLabel;
		  if  (  rs.GetODBCFieldCount(  )  !=  cnt  )  goto  errLabel;
		  for  (  i  =  0;  !rs.IsEOF(  );  i  ++  ,  rs.MoveNext(  )  )  {
			   for  (  index  =  0;  index  <  cnt;  index  ++  )  rs.GetFieldValue(  index,  varVals[index]  );
			   MACRO_sqlStr(  varVals[0],  tBuf,  mycountof(  tBuf  )  );
			   if  (  tBuf[0]  )  SendMessage(  hCombo,  CB_ADDSTRING,  0,  (  LPARAM  )tBuf  );
		  }
		  
		}
	 catch  (  CException  *  e  )  {
		   e->Delete(  );
		   qyShowInfo(  CONST_qyShowType_qwmComm,  0,  (  ""  ),  _T(  "IsClient"  ),  0,  _T(  ""  ),  _T(  ""  ),  _T(  "bQnmFillCol0 failed."  )  );
		   goto  errLabel;
	 }
	 bRet  =  TRUE;

errLabel:

	 if  (  rs.IsOpen(  )  )  rs.Close(  );

	 return  bRet;
}


  BOOL  bQnmFillCol0FromTable(  QY_DMITEM  *  pTable,  HWND  hCombo,  BOOL  bFillAny  )
{
	 BOOL			bRet		=	FALSE;
	 int			index		=	0;
	 //  CString	sqlBuf;
	 int			cnt			=	1;

	 SendMessage(  hCombo,  CB_RESETCONTENT,  0,  0  );
	 if  (  bFillAny  )  SendMessage(  hCombo,  CB_ADDSTRING,  0,  (  LPARAM  )CONST_qyAnyStr  );

	 for  (  pTable;  pTable->type  !=  -1;  pTable  ++  )  SendMessage(  hCombo,  CB_ADDSTRING,  0,  (  LPARAM  )CString(  pTable->des  ).GetBuffer(  0  )  );

	 bRet  =  TRUE;

//   errLabel:

	 return  bRet;
}




