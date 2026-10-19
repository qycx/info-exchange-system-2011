// qyMcHelp.cpp : Defines the entry point for the DLL application.
//

#include	"stdafx.h"
#include	"qyMcHelpProc.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

 QY_DMITEM  CONST_snTable[]  =
{
	{	0x6a,			(  TCHAR  *  )5,	(  TCHAR  *  )MAKELONG(  5,  5  ),	},		//  for test
	{	0x64,			(  TCHAR  *  )5,	(  TCHAR  *  )MAKELONG(  5,  5  ),	},		//  for test
	//
	{	0x72,			(  TCHAR  *  )200,	(  TCHAR  *  )MAKELONG(  200,  200  ),	},		//  for test
	//
	{	0x163,		(  TCHAR  *  )10,			},		//  20091107,bmj
	{	-1,				},
};



 extern  "C"  __declspec( dllexport )  int  getQyMcHelpDs(  void  *  p0,  void  *  p1,  void  *  p2  )
{
	 int					iLicenseCtxType			=	(  int  )p0;
	 unsigned  int			uiSn					=	(  unsigned  int  )p1;
	 int					iDsType					=	(  int  )p2;					//  0 for pItem->des, 1 for pItem->pData																						
	 //	 
	 static  unsigned  int	uiRealDs_0				=	0;
	 static  unsigned  int	uiRealDs_1				=	0;
	 
	 switch  (  iDsType  )  {
			 case  0:
				    if  (  uiRealDs_0  )  return  uiRealDs_0;
					break;
			 case  1:
				    if  (  uiRealDs_1  )  return  uiRealDs_1;
					break;
			 default:
					break;
	 }

	 if  (  iLicenseCtxType  )  {	//  
		 QY_DMITEM  *  pItem;
		 for  (  pItem  =  CONST_snTable;  pItem->type  !=  -1;  pItem  ++  )  {
			  if  (  pItem->type  ==  (  int  )uiSn  )  {
				  switch  (  iDsType  )  {
						  case  1:
							    uiRealDs_1  =  (  unsigned  int  )pItem->pData;
								break;
						  default:
							     uiRealDs_0  =  (  unsigned  int  )pItem->des;
								 break;
				  }
				  break;
			  }
		 }
	 }

	 switch  (  iDsType  )  {
			 case  1:
					 if  (  !uiRealDs_1  )  {
						 //  uiRealDs_1  =  MAKELONG(  4,  2  );		//  2011/11/19
						 //  uiRealDs_1  =  MAKELONG(  4,  4  );									 
						 uiRealDs_1  =  MAKELONG(  6,  6  );			//  2013/04/27
					 }
					 return  uiRealDs_1;
					 break;
			 default:
					if  (  !uiRealDs_0  )  uiRealDs_0  =  CONST_realDs;
					break;
		 
	 }

	 return  uiRealDs_0;
}


