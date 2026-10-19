

#ifndef  __AEHELP_H__
#define  __AEHELP_H__	/*  {  */

#define		CONST_qyMagic_upnp					"StatusOk"
#define		CONST_qyBufSize_upnp				4096
#define		CONST_qyPort_upnp					1900 
#define		CONST_qyDataMaxLen					1024


extern  "C"  int  qyEnc(  void  *  pEncCtx,  char  *  input,  size_t  inputSize,  char  *  output,  size_t  *  pOutputSize  );
extern  "C"  int  qyDec(  void  *  pEncCtx,  char  *  input,  size_t  inputSize,  char  *  output,  size_t  *  pOutputSize  );


#endif  /*  }  */

