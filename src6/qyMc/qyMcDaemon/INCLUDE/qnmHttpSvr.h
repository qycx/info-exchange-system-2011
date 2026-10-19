

#ifndef  __QNMHTTPSVR_H__
#define	 __QNMHTTPSVR_H__	/*  {  */



#define		CONST_qyHttpCmd_get					1
#define		CONST_qyHttpCmd_post				2

extern  QY_DMITEM  CONST_qyHttpCmdTable[];


#define		CONST_qnmRegUrl						"/"
#define		CONST_qnmRegUsrInfoUrl				"/regUsrInfo.asp"


#define		CONST_qyHttpStr_contentLength		"Content-Length:"




int  showPostData(  char  *  inputBuffer  );


#ifdef  __cplusplus
  extern  "C"  {
#endif

void  urlDecode(  char  *  pEncoded  );
int  qnmGetHttpVarPair(  char  *  varVal,  QY_VAR_PAIR	*  pPair  );

#ifdef  __cplusplus
  }
#endif



#endif  /*  }  */



