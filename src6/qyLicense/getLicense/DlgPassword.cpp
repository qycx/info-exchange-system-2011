// DlgPassword.cpp : implementation file
//

#include "stdafx.h"
#include "kk.h"
#include "DlgPassword.h"
#include "qyLicense.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPassword dialog


CDlgPassword::CDlgPassword(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPassword::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPassword)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgPassword::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPassword)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPassword, CDialog)
	//{{AFX_MSG_MAP(CDlgPassword)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPassword message handlers
#define			CONST_password				"zhenfanren != 123"

extern   int  flg;


 static  CString  qyBrowserForFile(  BOOL bOpen,  char  *  lpszDefExt,  DWORD  dwFlags,  char  *  lpszFilter,  char  *  title,  char  *  pFileName  )
{	 
	 CString		pathCStr;
	 CFileDialog	dlg(  bOpen,  lpszDefExt  ?  lpszDefExt  :  "html",  pFileName,  dwFlags  ?  dwFlags  :  OFN_CREATEPROMPT  |  OFN_OVERWRITEPROMPT,  lpszFilter  ?  lpszFilter  :  "Html 格式(*.html)|*.html|Excel 格式(*.xls)|*.xls||",  NULL  );

	 dlg.m_ofn.lpstrTitle  =  title  ?  title  :  "选择导出的数据文件名和格式";

	 if  (  IDOK  ==  dlg.DoModal(  )  )  {
		 pathCStr  =  dlg.GetPathName(  );
	 }
	
	 return  pathCStr;
}

void CDlgPassword::OnOK() 
{
	int					count					=  0;	
	char				buf[256]				=  "";
	char				fileNameBuf[256]		=  "";
	int					fileNameBufSize			=  0;
	char			*	p						=  NULL;
	char			*	p1						=  NULL;


	CString   inputPathCStr;
	CString	  outputPathCStr;
	CString	  hintCStr;

	//  当计算license时，三次输入密码无效，退出
	if  (  count		==  3  )  exit( 0 );
	if  (  !GetDlgItemText(  IDC_EDIT_password,  buf, sizeof(  buf  )  )  )  AfxMessageBox(  "error"  );
	if  (  strnicmp(  buf,  CONST_password,  sizeof(  CONST_password  )  )  ) {
		AfxMessageBox(  "输入密码不正确，请再输入一遍"  );  count ++;  goto  errLabel;
	}

	if  (  flg  ==  2  )  {
		AfxMessageBox(  "本命令用来计算并生成软件许可证！"  );
		//  第一步：选择导入种子文件

		inputPathCStr  =  qyBrowserForFile(  TRUE,  "sed",  OFN_FILEMUSTEXIST,  "License 格式(*.sed)|*.sed||",  "选择导入的数据文件名和格式",  fileNameBuf  );
		if  (  inputPathCStr  ==  ""  )  goto  errLabel;	

		memcpy(  fileNameBuf,  inputPathCStr.GetBuffer(  0  ),  sizeof(  fileNameBuf  )  );

		p  =  p1  =  fileNameBuf;
		fileNameBufSize		=  strlen(  fileNameBuf  );

		for  (  ;  ;  )  {
			if  (  !(  p  =  strchr(  p,  '\\'  )  )  )  {  p  =  NULL;  break;  }
			p1  =  p  + 1;
			if  (  p1  >=  (  fileNameBuf  +  fileNameBufSize  )  )  break;
			p   =  p1;
		}

		p  =  strchr(  p1,  '.'  );
		memset(  p,  0,  4  );
		strcpy(  fileNameBuf,  p1  );


		//  第二步：选择导出文件
		outputPathCStr  =  qyBrowserForFile(  FALSE,  "lcs",  0,  "License 格式(*.lcs)|*.lcs||",  NULL,  fileNameBuf  );
		if  (  outputPathCStr  ==  ""  )  goto  errLabel;	
		if  (  !bCalcChkNumOk(  inputPathCStr.GetBuffer(  0  ),  outputPathCStr.GetBuffer(  0  )  )  )   {  AfxMessageBox(  "    您的license.txt文件遭到了破坏，恢复后才能够正确使用该系统!  "  );  goto  errLabel;  }
		AfxMessageBox(  "已生成软件许可证 Ok!"  );
	}
	if  (  flg  ==  4  )  {
		if  (  !bQnmHardwareLicenseOk(  )  )  {  AfxMessageBox(  "   敬请注意：license不正确！"  );  goto  errLabel;  }
		AfxMessageBox(  "License  Ok!"  );
	}
errLabel:
	CDialog::OnOK();
}
