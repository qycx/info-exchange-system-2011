========================================================================
       STATIC LIBRARY : qyLicense
========================================================================


AppWizard has created this qyLicense library for you.  

This file contains a summary of what you will find in each of the files that
make up your qyLicense application.

/////////////////////////////////////////////////////////////////////////////

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named qyLicense.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
The compiler and linker switches have been modified to support MFC. Using the
MFC ClassWizard with this project requires that you add several files to the 
project, including "resource.h", "qyLicense.rc" and a "qyLicense.h" that 
includes resource.h. If you add an rc file to a static library, you may 
experience difficulties due to the limitation that only one rc file may be 
present in a Dll or Exe. This problem may be overcome by including the 
library's .rc file into the parent project's .rc file.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" to indicate parts of the source code you
should add to or customize.


/////////////////////////////////////////////////////////////////////////////


2004/03/19

							关于校验方法
	原则:将在四个程序中实施校验.其中,qyMc.exe的校验方法是启动时校验;其它采用
服务启动时/配置刷新时校验;

						关于软件保护的技术设计
    
	为保护软件知识产权，对软件实施加密保护。目前采取的办法有：狗。目前
保护的文件：qyMc.exe;qyMcDaemon.exe;qnmScheduler.exe;qnmResponse.exe。离开狗，
程序将不能运行。

    为了加强保护力度，我们将进一步采取与硬件绑定的加密手段。具体为：
    1）提取一系列硬件参数：例如：硬盘序列号；cpu序列号和网卡序列号等。
    2）对硬件参数采取多种加密形成硬件校验值；
    3）存储校验值(chkNum)。
    4）在程序里自动提取硬件参数；分时、分点、分不同方法计算该参数，并与校验值
实时比对，一旦发现比对错误；程序停止运行立即退出。比对的过程需分布在不同的时间段中。


    下面将针对加密算法和校验函数进行设计：
    1、加密：在密钥进行加密存储的基础上，结合知名加密算法和自行研制算法，形成校验值。

    int  initLicenseEnc(  void  *  pEncCtx  )
    void  exitLicenseEnc(  void  *  pEncCtx  )
    int  licenseEnc(  void  *  pEncCtx,  char  *  input,  size_t  inputSize,  
				  char  *  output,  size_t  *  pOutputSize  )
    {
	     已加密密钥实时解密；
	     知名加密；
	     自行加密；
    }
    int  licenseDec(  void  *  pEncCtx,  char  *  input,  size_t  inputSize,  
				  char  *  output,  size_t  *  pOutputSize  )
   
    2、存储：分段、分点存储校验值。

    typedef  struct  __chkNumField_  {
		     int   type;
		     int   nField;
             union  {
		            char  fieldlen[nField];
		     }
	}        CHKNUMFIELD
    int  qySetChkNum( char  *  input,  int  inputLen,  void  *  fieldInfo )	//  分段分点存储校验值
    {
	     分段截取(1/4;3/4*1/4;13/16)，分别写注册表；
    }
    int  qyGetChkNum( char * srou, int srouLen, char * dest, int destLen, void * fieldInfo  )
	{
		  分段读取。
	}

    3、校验：分时校验、分点校验(多点调用)、分段校验

    int  qyCheckOnTime(  char  *  encNum,  int  encNumLen,  void  *  field,  Time  time  );			//  1月份……
    int  qyCheckOnField(  char  *  encNum,  int  encNumLen,  void  *  field,  int  nField,  
			              int  fieldLen   );

						关于软件保护的模块界面
    1、 硬件参数提取模块：有专门界面程序。提取一系列硬件参数：例如：硬盘序列号；
cpu序列号和网卡序列号等。
	    界面要求：	提取参数的开/关菜单。
					显示硬件参数的对话框。
	2、 校验值生成模块：有专门界面程序。对硬件参数采取多种加密形成硬件校验值。
	    界面要求：  输入参数对话框
					生成校验值的开/关菜单。
					显示校验值的对话框。
    3、 软件注册模块：有专门界面程序。存储校验值(chkNum)。
		界面要求：  输入校验值对话框
					注册开/关菜单。
					显示注册完毕的对话框。
    4、 程序内部的校验模块：不需要有专门界面程序。在程序内部的不同位置自动提取硬件参数；
分时、分点、分不同方法计算该参数，并与校验值实时比对，一旦发现比对错误；程序停止运行立即
退出。比对的过程需分布在不同的时间段中。


						关于加密的基本原则
    加密：密钥、算法、校验值
	1、密钥存储:加密存储.实时解密使用.
	2、算法土洋结合。
	3、多种校验类型（函数和宏）、多点校验、分时校验相结合。

	一、密钥存储
	二、算法
		混合算法：	结合国际知名算法和公司自行研制的算法，混合使用的结果是使破解无从下手。
	三、校验
		多种校验：	根据多个密钥，提供多个校验办法，可防止具有针对性的对"单一密钥"的破解。
		多点校验：	为防止破解中的“一点突破”情况，我们采用多点校验办法。在程序的不同执行位置，
调用不同的校验算法，铸就整体防御阵地。
		分时校验（分散校验）：	针对计算机时间可修改的特点：我们采用将校验分散到所有的月份和礼拜的校验办法，
避开通过调整时间来破解的行为。	同时，在分时校验中，校验时间必须精确定位到具体的时、分；这样，破解就根本
无法绕开具体时间。
		校验数据分多处存放：	提供校验的数据可以放在注册表中，但是需要分不同位置进行分段存放。可防止嗅探。
		不定长校验：	每次校验过程需将计算结果与校验数据进行比对；为防止嗅探，每次校验内容长度采用
不定长方法校验。

									关于生产过程：
		组件：	1）服务器(2台)
				2）id读取器
				3）license产生器
				4）license注册器

		生产要求：
			所有生产程序必须在通过验证的情况下，方可正常运行。
			服务器：为指定pc的mac绑定的程序，专门用于接收生产程序的验证。该程序不需成为服务；
		只是在需要生产的时候再启动。
			生产程序：除服务器之外的其他所有生产程序必须依赖服务器才能够运行。在离开服务器
		（找不到服务器）的时候，该程序将停止工作。

		测试：	将采用上述服务器控制模式工作。



									其它注意事项
		防止伪造mac
		防止内存泄漏：
		界面：读取数据参数；形成文件。

		
2004/03/19


2004/0423
	





