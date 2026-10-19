
#ifndef  __QYPRELICENSE_H__
#define  __QYPRELICENSE_H__	//  {


//  2007/11/18 


		   //  2007/11/18, qyMessenger, 
		   #define	__SystemId_Is__																		// 


		   //
		   //
		   ///////////////////
		   //
		   //


		      #define  __DEMO__																				//  
																											//  
			

#ifndef  __DEMO__

		 #define			CONST_qnmMaxPcs								1000								//  
																											//  
																											//  

		 #define			CONST_qnmMaxMessengers						220									//  55									//  

		 //  
		 //		#define		__LIMITED_VER__																	//  

		 #ifdef  __DEBUG__
				 #define		CONST_maxRegTimes						20000								//  总共注册次数
				 #define		CONST_qmdMaxConns_limitedVer_netMc		200									//  daemon的最大连接数，不得超过60。
				 #define		CONST_qmdMaxConns_limitedVer_is			(  CONST_qnmMaxMessengers  *  5  )	//  200  		//  daemon的最大连接数，不得超过60。
		 #else
				 #define		CONST_maxRegTimes						20000								//  总共注册次数
				 #define		CONST_qmdMaxConns_limitedVer_netMc		200									//  daemon的最大连接数，不得超过60。
				 #define		CONST_qmdMaxConns_limitedVer_is			(  CONST_qnmMaxMessengers  *  5  )	//  2048		//  daemon的最大连接数，不得超过60。
		 #endif

		 //  
		 //  #define		CONST_qnmDeadDate							"20100630"

#else	 //  

		 //  #define		CONST_qnmMaxPcs								2									
		 //  #define			CONST_qnmMaxPcs								4									//  2011/08/28
		 #define			CONST_qnmMaxPcs								6									//  2013/04/27
																											//  此宏仅在Daemon中使用
																											//  表明qyPcTab中能存储多少记录，即系统能管理多少终端
																											//  shhg内网管理系统购买了2048点

		 //  #define		CONST_qnmMaxMessengers						4									//  2007/06/19，用来表明在qyMessengerAuthTab中能存储多少个messenger
		 #define			CONST_qnmMaxMessengers						6									//  2013/04/27，用来表明在qyMessengerAuthTab中能存储多少个messenger

		 //  定义此宏为限制使用版								
		 #define		__LIMITED_VER__		

		 //  2009/09/23
		 //  #define		CONST_TEST_DOG_SN								0x6a
		 //  #define		CONST_TEST_DOG_SN1								0x64


		 #define		CONST_maxRegTimes								20480								//  总共注册次数
		 #define		CONST_qmdMaxConns_limitedVer_netMc				5									//  daemon的最大连接数，不得超过60。
		 #define		CONST_qmdMaxConns_limitedVer_is					(  CONST_qnmMaxMessengers  *  5  )	//  100			//  daemon的最大连接数，不得超过60。
		 //
		 #define		CONST_maxDateCounter							45+1								//  2010/03/21,timeout

		 //  
		 //  #define		CONST_qnmDeadDate							"20100630"


#endif


//  2012/12/21
#define				__NOTSUPPORT_superPro__										//  不再支持老狗. 2012/12/21

//  2007/02/23
//  define			DEFAULT_qyLicenseCtxType			CONST_qyLicenseCtxType_superPro		//  
#define			DEFAULT_qyLicenseCtxType				CONST_qyLicenseCtxType_sentinelKey	//  
//
//  #define		MACRO_bQnmWithoutChkDog(  pCtx  )  (  bQnmDemo(  )  &&  (  qnmMaxPcs(  pCtx  )  <=  3  )  &&  (  qnmMaxMessengers(  pCtx  )  <=  5  )  )
//  #define		MACRO_bQnmWithoutChkDog(  pCtx  )  (  bQnmDemo(  )  &&  (  qnmMaxPcs(  pCtx  )  <=  5  )  &&  (  qnmMaxMessengers2(  pCtx  )  <=  5  )  )
#define		MACRO_bQnmWithoutChkDog(  pCtx  )  (  bQnmDemo(  )  &&  (  qnmMaxPcs(  pCtx  )  <=  7  )  &&  (  qnmMaxMessengers2(  pCtx  )  <=  7  )  )


#endif  //  }


