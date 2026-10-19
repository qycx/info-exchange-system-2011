
#include  "qyCommon.h"

#ifndef  __QYLICENSE_H__
#define  __QYLICENSE_H__	/*  {  */



#define			CONST_regValName_chkNum					"position"
#define			CONST_hardwareId_len					256

#define			MACRO_check1				char			idBuf[256],  calcBuf[512],  chkNumBuf[256];																							\
											unsigned  int	idBufSize,  calcBufSize,  chkNumBufSize;																							\
											memset(  idBuf,  0,  sizeof(  idBuf  )  );	 memset(  calcBuf,  0,  sizeof(  calcBuf  )  );	 memset(  chkNumBuf,  0,  sizeof(  chkNumBuf  )  );		\
											if  (  testProductIdMain(  idBuf,  &idBufSize  )  )  return;																						\
	 										if  (  testLicenseMain(  idBuf,  strlen(  idBuf  ),  calcBuf,  &calcBufSize  )  )  return;															\
	 										if  (  !bGetChkNumOk(  chkNumBuf,  &chkNumBufSize  )  )  return;																					\
											if  (  !strcmp(  calcBuf,  chkNumBuf  )  )  return; 																								
														

typedef  struct  __spDynLib_t				{
				 HINSTANCE					hDll_sentinelKeyW;

				 void  *					pSFNTGetLicense;
				 void  *					pSFNTGetDeviceInfo;
				 void  *					pSFNTReleaseLicense;
				 void  *					pSFNTReadString;				 
}		 SP_DYN_LIB;

typedef  struct  __qyLicenseCtx_t			{
				 int						type;
				 BOOL						bRnbDogInited;
				 //
				 unsigned  int				uiSerialNo;						//  2007/02/28
				 //
				 BOOL						bSnTest;						//  2009/09/23
				 //
				 void					*	pApiPacket;
				 //
				 void					*	licHandle;						//  2007/02/23
				 BOOL						bSentinelKeyInited;

				 SP_DYN_LIB					spDynLib;

}		 QY_LICENSE_CTX;


#define		CONST_qyLicenseCtxType_superPro				0					//  2007/02/23
#define		CONST_qyLicenseCtxType_sentinelKey			1					//  2007/02/23



typedef  struct  __chkNumField_		{
				 int				type;
				 int				nField;
				 union  {
					unsigned int	fieldLen[5];
				 }		u;
}        CHKNUMFIELD;

#ifdef  __cplusplus
  extern  "C"  {
#endif



 // 可惜没有清理的函数，因为软件狗没有
int  initRnbDog(  QY_LICENSE_CTX  *  pCtx  );
void  exitRnbDog(  QY_LICENSE_CTX  *  pCtx  );	//  2005/06/26
BOOL  bQyDogOk(  QY_LICENSE_CTX  *  pCtx,  LPCWSTR  moduleName  );

//


#define			qnmMaxMessengers1(  pCtx  )		GetDlgItemTxtW(  pCtx  )
#define			qnmMaxMessengers2(  pCtx  )		PgpSetAsign(  pCtx  )
#define			qnmMaxMessengers3(  pCtx  )		ODBCAttribut(  pCtx  )
#define			qnmMaxMessengers4(  pCtx  )		DesignTimeVisibl(  pCtx  )
#define			qnmMaxMessengers5(  pCtx  )		CreateParametr(  pCtx  )
#define			qnmMaxMessengers6(  pCtx  )		ExecuteRader(  pCtx  )
#define			qnmMaxMessengers7(  pCtx  )		ServiceTypFromHandle(  pCtx  )
#define			qnmMaxMessengers8(  pCtx  )		DockContrlBar(  pCtx  )
#define			qnmMaxMessengers9(  pCtx  )		IWMSOutgoingDistributionConnction(  pCtx  )
#define			qnmMaxMessengers0(  pCtx  )		IWMSOutgoingDistributonConnections(  pCtx  )
//
#define			qnmMaxImGrps(  pCtx  )			GetDlgContrl(  pCtx  )
//
#define			qnmAvUpperLimits(  pCtx  )		OpenClippboard(  pCtx  )


//
unsigned  int	qnmMaxPcs(  QY_LICENSE_CTX  *  pCtx  );
//
unsigned  int	qnmMaxMessengers1(  QY_LICENSE_CTX  *  pCtx  );		//  2007/04/03
unsigned  int	qnmMaxMessengers2(  QY_LICENSE_CTX  *  pCtx  );		//  2007/04/03
unsigned  int	qnmMaxMessengers3(  QY_LICENSE_CTX  *  pCtx  );		//  2007/04/03
unsigned  int	qnmMaxMessengers4(  QY_LICENSE_CTX  *  pCtx  );		//  2007/04/03
unsigned  int	qnmMaxMessengers5(  QY_LICENSE_CTX  *  pCtx  );		//  2007/04/03
unsigned  int	qnmMaxMessengers6(  QY_LICENSE_CTX  *  pCtx  );		//  2007/04/03
unsigned  int	qnmMaxMessengers7(  QY_LICENSE_CTX  *  pCtx  );		//  2007/04/03
unsigned  int	qnmMaxMessengers8(  QY_LICENSE_CTX  *  pCtx  );		//  2007/04/03
unsigned  int	qnmMaxMessengers9(  QY_LICENSE_CTX  *  pCtx  );		//  2007/04/03
unsigned  int	qnmMaxMessengers0(  QY_LICENSE_CTX  *  pCtx  );		//  2007/04/03
//
unsigned  int   qnmMaxImGrps(  QY_LICENSE_CTX  *  pCtx  );			//  2010/01/04
unsigned  int	qnmAvUpperLimits(  QY_LICENSE_CTX  *  pCtx  );		//  2009/11/03
unsigned  int	qnmMaxPhoneMessengers(  QY_LICENSE_CTX  *  pCtx  );	//  2008/01/29

//
int  getnMaxConns_netMc(  QY_LICENSE_CTX  *  pCtx  );
int  getnMaxConns_is(  QY_LICENSE_CTX  *  pCtx  );
BOOL  bQnmLicenseOk(  QY_LICENSE_CTX  *  pCtx,  unsigned  int  *  puiMaxRegTimes  );
int  useAQnmLicense(  QY_LICENSE_CTX  *  pCtx  );
int  getQnmLicenseInfo(  QY_LICENSE_CTX  *  pCtx,  char  *  buf,  unsigned  int  size  );

#define		bQnmLicenseTimeout_daemon(  pnDays_left,  infoBuf,  size  )		GetDlgItemTxt(  pnDays_left,  infoBuf,  size  )
#define		bQnmLicenseTimeout_gui(  pnDays_left,  infoBuf,  size  )		AfxMssageBox(  pnDays_left,  infoBuf,  size  )

BOOL  bQnmLicenseTimeout_daemon(  int  *  pnDays_left,  char  *  infoBuf,  unsigned  int  size    );
BOOL  bQnmLicenseTimeout_gui(  int  *  pnDays_left,  char  *  infoBuf,  unsigned  int  size    );


BOOL bQnmHardwareLicenseOk(  void  *  pEnvParam  );
BOOL  bQnmDemo(  );


#define		CONST_maxSeqNoLen								128							//  序列号最大长度，2005/06/24
#define		CONST_qwmSeqNoPrefix							"cz"						//  成长
//


int  getQwmSeqNo(  char  *  seqNo,  unsigned  int  size  );




int  testProductIdMain(  void  *  pEnvParam,  char  *  buf,  unsigned int * size  );
int  spoofHarewareId(  char  * oldBuf,  unsigned int * oldBufLen  );

BOOL  bGetHardwareIdOk(  void  *  pEnvParam,  LPCTSTR  fileName  );
BOOL  bCalcChkNumOk(  LPCTSTR  inputFileName,  LPCTSTR  outputFileName  );
BOOL  bSetChkNumOk(  LPCTSTR  fileName  );
BOOL  bGetChkNumOk(  char  *  buf,  unsigned int * size  );

int  qySetChkNum(  char  * input,  int inputLen,  CHKNUMFIELD  *  field  );
int  qyGetChkNum(  char  *  chkNumBuf,  unsigned int * pChkNumLen  );





 
#ifdef  __cplusplus
  }
#endif
 




#endif  /*  }  */


