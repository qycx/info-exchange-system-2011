

#include	<windows.h>
#include	<winsock.h>
#include	<ras.h>
#include	<raserror.h>
#include	<commctrl.h>
#include	<iphlpapi.h>
#include	<tchar.h>
#include	"asrWMon.h"
#include	"qyRegToolProc.h"





 extern  "C"  int  qwmOutputFileHead(  void  *  pQrtParam  )
{
	 int				iErr		=		-1;
	 QY_REG_TOOL	*	pQrt		=		(  QY_REG_TOOL  *  )pQrtParam;
	 TCHAR				djDatFileName[CONST_qyMaxPathLen  +  1];
	 TCHAR				tmpFileName[CONST_qyMaxPathLen  +  1];
	 FILE			*	fp			=		NULL;
	 TCHAR				buf[CONST_maxDjValLen  +  32];

	 
	 //  数据目录
	 if  (  getModuleDirAndFinalName(  djDatFileName,  mycountof(  djDatFileName  ),  NULL,  0  )  )  goto  errLabel;
	 if  (  trailDir(  djDatFileName,  mycountof(  djDatFileName  )  )  )  goto  errLabel;
	 _sntprintf(  djDatFileName,  mycountof(  djDatFileName  ),  _T(  "%s%s"  ),  djDatFileName,  _T(  CONST_subDir_dat  )  );
	 if  (  trailDir(  djDatFileName,  mycountof(  djDatFileName  )  )  )  goto  errLabel;

	 //  建立数据目录
	 if  (  !CreateDirectory(  djDatFileName,  NULL  )  &&  GetLastError(  )  !=  ERROR_ALREADY_EXISTS  )  {
		 qyDisplayLastError(  ""  );  goto  errLabel;
	 }

	 //  选择文件名
	 GetTempFileName(  djDatFileName,  _T(  "dat"  ),  0,  tmpFileName  );
	 _sntprintf(  djDatFileName,  mycountof(  djDatFileName  ),  _T(  "%s"  ),  tmpFileName  );

	 //  输出文件头
	 if  (  !(  fp  =  _tfopen(  djDatFileName,  _T(  "a"  )  )  )  )  {
		 qyDisplayLastError(  ""  );  goto  errLabel;
	 }

	 fprintf(  fp,  "%s\n",  CONST_qyFileObj_djMagic  );
	 fprintf(  fp,  "%s=%s\n",  CONST_qyFileObj_djVer,  qnmVerStr(  pQrt->iServiceId  )  );
	 memset(  buf,  ' ',  sizeof(  buf  )  );  buf[sizeof(  buf  )  -  1]  =  0;
	 memcpy(  buf,  pQrt->macsInfo.macs[0],  strlen(  (  char  *  )pQrt->macsInfo.macs[0]  )  );
	 fprintf(  fp,  "%s=%s\n",  CONST_qyFileObj_djMac,  buf  );
	 //
	 memset(  buf,  ' ',  sizeof(  buf  )  );  buf[sizeof(  buf  )  -  1]  =  0;
	 fprintf(  fp,  "%s=%s\n",  CONST_qyFileObj_djDw,  buf  );
	 fprintf(  fp,  "%s=%s\n",  CONST_qyFileObj_djBm,  buf  );
	 fprintf(  fp,  "%s=%s\n",  CONST_qyFileObj_djSyr,  buf  );
	 //
	 fprintf(  fp,  "%s\n",  CONST_qyFileObj_djEnd  );

	 iErr  =  0;

errLabel:

	 if  (  fp  )  fclose(  fp  );
	 
	 if  (  !iErr  )  _snprintf(  pQrt->djDatFileName,  sizeof(  pQrt->djDatFileName  ),  "%s",  djDatFileName  );

	 return  iErr;
}

 int  qwmModifyFileObj(  char  *  fileName,  char  *  objName,  char  *  val  )
{
	 FILE			*	fp			=		NULL;
	 long				lPos;
	 int				objNameLen	=		strlen(  objName  );
	 char				buf[1024];
	 
	 if  (  !(  fp  =  fopen(  fileName,  "r+"  )  )  )  goto  errLabel;

	 for  (  ;  ;  )  {
		  lPos  =  ftell(  fp  );
		  if  (  !fgets(  buf,  sizeof(  buf  ),  fp  )  )  goto  errLabel;
		  if  (  !strcmpi(  buf,  CONST_qyFileObj_djEnd  )  )  break;
		  if  (  strnicmp(  buf,  objName,  objNameLen  )  )  continue;
		  fseek(  fp,  lPos,  SEEK_SET  );
		  fprintf(  fp,  "%s=%s",  objName,  val  );
		  break;
	 }
errLabel:
	 if  (  fp  )  fclose(  fp  );
	 return  0;
}

 extern  "C"  int  qwmModifyFile(  void  *  pQrtParam  )
{
	 QY_REG_TOOL	*	pQrt							=		(  QY_REG_TOOL  *  )pQrtParam;
	 TCHAR				dw[128]							=		_T(  ""  );
	 TCHAR				bm[128]							=		_T(  ""  );
	 TCHAR				syr[128]						=		_T(  ""  );
	 int				i;
	 char				fakedMac[CONST_qyMacLen  +  1]	=		"98";
	 char				buf[CONST_qyMaxPathLen  +  1];
	 char			*	p;

	 for  (  i  =  0;  i  <  sizeof(  gQyRegTool.regInfo.u.cols  )  /  sizeof(  gQyRegTool.regInfo.u.cols[0]  );  i  ++  )  {
		  if  (  gQyRegTool.regInfo.uiFieldIds[i]  ==  CONST_fieldId_dw  )  break;
	 }
	 if  (  i  ==  sizeof(  gQyRegTool.regInfo.u.cols  )  /  sizeof(  gQyRegTool.regInfo.u.cols[0]  )  )  goto  errLabel;
	 //	 safeStrnCpy(  gQyRegTool.regInfo.u.cols[i],  dw,  sizeof(  dw  )  );  //  2010/05/09
	 myStr2TChar(  gQyRegTool.regInfo.u.cols[i],  dw,  mycountof(  dw  )  );
	 //  myUtf82Str(  dw,  sizeof(  dw  )  );		  //  2010/05/09  //  2005/09/25
	 //  qwmModifyFileObj(  gQyRegTool.djDatFileName,  CONST_qyFileObj_djDw,  dw  );
	 qwmModifyFileObj(  gQyRegTool.djDatFileName,  CONST_qyFileObj_djDw,  gQyRegTool.regInfo.u.cols[i]  );
	 //
	 for  (  i  =  0;  i  <  sizeof(  gQyRegTool.regInfo.u.cols  )  /  sizeof(  gQyRegTool.regInfo.u.cols[0]  );  i  ++  )  {
		  if  (  gQyRegTool.regInfo.uiFieldIds[i]  ==  CONST_fieldId_bm  )  break;
	 }
	 if  (  i  ==  sizeof(  gQyRegTool.regInfo.u.cols  )  /  sizeof(  gQyRegTool.regInfo.u.cols[0]  )  )  goto  errLabel;
	 //  safeStrnCpy(  gQyRegTool.regInfo.u.cols[i],  bm,  sizeof(  bm  )  );  //  2010/05/09
	 myStr2TChar(  gQyRegTool.regInfo.u.cols[i],  bm,  mycountof(  bm  )  );
	 //  myUtf82Str(  bm,  sizeof(  bm  )  );		//  2010/05/09	//  2005/09/25
	 //  qwmModifyFileObj(  gQyRegTool.djDatFileName,  CONST_qyFileObj_djBm,  bm  );
	 qwmModifyFileObj(  gQyRegTool.djDatFileName,  CONST_qyFileObj_djBm,  gQyRegTool.regInfo.u.cols[i]  );
	 //
	 for  (  i  =  0;  i  <  sizeof(  gQyRegTool.regInfo.u.cols  )  /  sizeof(  gQyRegTool.regInfo.u.cols[0]  );  i  ++  )  {
		  if  (  gQyRegTool.regInfo.uiFieldIds[i]  ==  CONST_fieldId_syr  )  break;
	 }
	 if  (  i  ==  sizeof(  gQyRegTool.regInfo.u.cols  )  /  sizeof(  gQyRegTool.regInfo.u.cols[0]  )  )  goto  errLabel;
	 //  safeStrnCpy(  gQyRegTool.regInfo.u.cols[i],  syr,  sizeof(  syr  )  );  //  2010/05/09
	 myStr2TChar(  gQyRegTool.regInfo.u.cols[i],  syr,  mycountof(  syr  )  );
	 //	 myUtf82Str(  syr,  sizeof(  syr  )  );		  //  2010/05/09	//  2005/09/25
	 //  qwmModifyFileObj(  gQyRegTool.djDatFileName,  CONST_qyFileObj_djSyr,  syr  );
	 qwmModifyFileObj(  gQyRegTool.djDatFileName,  CONST_qyFileObj_djSyr,  gQyRegTool.regInfo.u.cols[i]  );

	 if  (  !syr[0]  )  goto  errLabel;

	 if  (  !bMacValid(  (  char  *  )gQyRegTool.macsInfo.macs[0]  )  )  {
		 memset(  buf,  0,  sizeof(  buf  )  );
		 //  if  (  strlen(  syr  )  >  5  )  safeStrnCpy(  syr  +  strlen(  syr  )  -  5,  buf,  6  );
		 if  (  lstrlen(  syr  )  >  5  )  myTChar2Str(  syr  +  lstrlen(  syr  )  -  5,  buf,  6  );
		 //  else  safeStrnCpy(  syr,  buf,  sizeof(  buf  )  );
		 else  myTChar2Str(  syr,  buf,  sizeof(  buf  )  );
		 qybuf2x(  buf,  5,  fakedMac  +  2  );
		 qwmModifyFileObj(  gQyRegTool.djDatFileName,  CONST_qyFileObj_djMac,  fakedMac  );
		}
	 else  fakedMac[0]  =  0;

	 safeStrnCpy(  gQyRegTool.djDatFileName,  buf,  sizeof(  buf  )  );
	 if  (  !(  p  =  strrchr(  buf,  '\\'  )  )  )  goto  errLabel;
	 p  ++  ;  p[0]  =  0;

	 TCHAR  tBuf[CONST_qyMaxPathLen  +  1];
	 myStr2TChar(  buf,  tBuf,  mycountof(  tBuf  )  );
	 TCHAR  tBuf2[CONST_qyMaxPathLen  + 1];
	 myStr2TChar(  (  fakedMac[0]  ?  ""  :  (  char  *  )gQyRegTool.macsInfo.macs[0]  ),  tBuf2,  mycountof(  tBuf2  )  );
	 _sntprintf(  tBuf,  mycountof(  tBuf  ),  _T(  "%s%s-%s-%s-%s"  ),  tBuf,  dw,  bm,  syr,  tBuf2  );
	 DeleteFile(  tBuf  );
	 myStr2TChar(  gQyRegTool.djDatFileName,  tBuf2,  mycountof(  tBuf2  )  );
	 if  (  !MoveFile(  tBuf2,  tBuf  )  )  {
		 qyDisplayLastError(  ""  );
	 }

errLabel:

	 return  0;
}


