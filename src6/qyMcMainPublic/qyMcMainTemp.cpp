

#include	"stdafx.h"
#include	"qyMcMainCommon.h"



 int  printQmObjQ_isClient(  void  *  p0,  void  *  p1,  void  *  pQmObjQ  )
{
	QY_MC	*	pQyMc	=	QY_GET_GBUF(  );
	QM_OBJQ	*	pQ		=	(  QM_OBJQ  *  )pQmObjQ;

#ifdef  __DEBUG__
		unsigned  int								i;
		char										buf[256];

		switch  (  pQ->iType  )  {
				case  CONST_objQType_misClient:
					  QMEM_MESSENGER_CLI	*	pQMem;
					  QY_DMITEM				*	pTable;
				  
					  pTable  =  getResTable(  0,  &pQyMc->cusRes,  CONST_resId_objTypeTable  );
					  for  (  i  =  0;  i  <  pQ->cnt;  i  ++  )  {
						   pQMem  =  (  QMEM_MESSENGER_CLI  *  )pQ->pMems[i].pQMemObj;
						   traceLogA(  "\t%d¸ %S, idInfo is %I64u",  i, qyGetDesByType1(  pTable,  pQMem->uiType  ),  pQMem->idInfo.ui64Id  );
					  }
					  break;

				default:
						break;
		}

#endif
	 return  0;
}


#ifdef __DEBUG__	//  __DEBUG__ must be defined to make all below valid!













#endif	//  __DEBUG__ must be defined to make all above valid!


