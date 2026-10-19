

#ifndef  __ASRWMONPRECOMP_H__	
#define  __ASRWMONPRECOMP_H__	/* { */


#ifdef  __DEBUG__

	//  #define			__TEST__							//  定义此项，为作测试程序用
	  #define			__BZAZ__							//  定义此项，使qwmSvr.exe的自安装功能失效
	#define			__NOTWATCHC__							//  定义此项，可以避免在DEBUG版本里因为记录err.log而导致不停的触发文件监视动作（过于频繁），2006/03/19
	#define			__WITHREG__								//  定义此项，使包含注册功能
	#define			__BXZAZ__								//  定义此项，使不限制安装	

	//  #define			__NOTHIDEQWM__								//  进程隐藏的开关两，有定义为不隐藏

#endif


//  #define			__NOTHIDEQWM__								//  进程隐藏的开关两，有定义为不隐藏


//  2003/12/01将下面的部分关闭，因为qnmProxy项目已被取消
//  #if		DEFAULT_qySystemId  ==  CONST_qySystemId_nms		//  由于已使用此开关量，不需要手工开关下面的开关量
//  															//  当使用管理代理程序时，应定义下面这项
//  	//  #define			__QNMPROXY__							//  定义此项，使下载代理.
//  #endif

#if	!defined(  __DEBUG__  )  ||  (  !defined(  __TEST__  )  &&  !defined(  __BZAZ__  )  )
	#define			HOOK_PROCESS
	#define			HIDE_COPY
#endif



//	#define			__FOR_ARMY__						//  定义此项，则全部为禁止



#endif /* } */


