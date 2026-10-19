
#ifndef  __QYMCHELPPROC_H__
#define  __QYMCHELPPROC_H__		//  {

#ifndef  QY_DMITEM  //  {

typedef  struct  __qyDmItem_t			{
				 long					type;
				 TCHAR				*	des;
				 TCHAR				*	pData;
				 //  long				flg;
				 //  long				data;
}		 QY_DMITEM;

#endif  //  }

/*

#define		CONST_productLevel		0


#if  CONST_productLevel  ==  0
	 #define		CONST_minDs				0
	 #define		CONST_maxDs				300
#elif	CONST_productLevel	==	1
		#define		CONST_minDs				300
		#define		CONST_maxDs				600
#elif	CONST_productLevel	==	2			
		#define		CONST_minDs				600
		#define		CONST_maxDs				1000
#elif
		#define		CONST_minDs					//  给个最小的数
		#define		CONST_maxDs					//  给个最大的数
#endif

*/

//  注意，这里将给出精确的限制点数
#if  0
  	#define		CONST_realDs					2
#else
  	//  #define		CONST_realDs					4
	#define		CONST_realDs					6
#endif



#endif  //  }




