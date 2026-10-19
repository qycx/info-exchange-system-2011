


#include	<windows.h>
#include	<winsock.h>
#include	<ras.h>
#include	<raserror.h>
#include	<commctrl.h>
#include	<iphlpapi.H>
#include	<tchar.h>

#include	"asrWMon.h"
#include	"qwmRegistryFunc.h"


/*
 HANDLE				m_hToken;					// As Long		'Prozess-Token
 TOKEN_PRIVILEGES	m_TP;						// As 	'Prozessprivilegien-Struktur
 LUID				m_RestoreLuid;				// As LUID	'Restore-Privileg
 LUID				m_BackupLuid;				// As LUID	'Backup-Privileg
*/ 

 /*
 int  testRenameRegKey(  )
{
	 renameRegKey(  "c:\\tempbbb\\1.txt",  HKEY_LOCAL_MACHINE,  "SOFTWARE\\Qycx\\qwm",  "SOFTWARE\\Qycx\\qwm1"  );

	 return  0;
}
*/



/*
 //   '====================================================================================
 //   'Date:      2004-01-20
 //   'Function:  Backup- und Restore-Privilegien einrichten
 //   '====================================================================================
 int  setBackupAndRestorePriviliges()
{
	int		iErr		=	-1;
	long	nResult;
 
	//  'Prozess-Token ?ffnen
    nResult  =  pOpenProcessToken(  GetCurrentProcess(  ), TOKEN_ADJUST_PRIVILEGES  |  TOKEN_QUERY,  &m_hToken  );
	if  (  !nResult  )  goto  errLabel;
	//  'Restore-Struktur anfordern
    nResult  =  pLookupPrivilegeValue(  NULL,  SE_RESTORE_NAME,  &m_RestoreLuid  );
	if  (  !nResult  )  goto  errLabel;
	//  'BackUp-Struktur anfordern
    nResult  =  pLookupPrivilegeValue(  NULL,  SE_BACKUP_NAME,  &m_BackupLuid  );
	if  (  !nResult  )  goto  errLabel;
	//  'neue Privilegien einrichten
    m_TP.PrivilegeCount  =  2;
    m_TP.Privileges[0].Luid  =  m_RestoreLuid;
    m_TP.Privileges[0].Attributes  =  SE_PRIVILEGE_ENABLED;
    m_TP.Privileges[1].Luid  =  m_BackupLuid;
    m_TP.Privileges[1].Attributes  =  SE_PRIVILEGE_ENABLED;
	//  'ge?nderte Strukturen einstellen
    nResult  =  AdjustTokenPrivileges(  m_hToken,  FALSE,  &m_TP,  sizeof(  m_TP  ),  NULL,  NULL  );
	if  (  !nResult  )  goto  errLabel;
	iErr  =  0;
errLabel:

	 return  iErr;
}


 //  '====================================================================================
 //  'Date:      2004-01-20
 //  'Function:  Privilegien wieder zurücknehmen
 //  '====================================================================================
 int  resetBackupAndRestorePriviliges(  )
{
	int		iErr			=	-1;
	long	nResult;			//   As Long             'Rückgabe der Funktionen

    nResult  =  AdjustTokenPrivileges(  m_hToken,  TRUE,  &m_TP,  sizeof(  m_TP  ),  NULL,  NULL  );
	if  (  !nResult  )  goto  errLabel;
	iErr  =  0;
errLabel:
	 return  iErr;
}
*/

 //  '====================================================================================
 //  'Date:      2004-01-20
 //  'Function:  übergebenen Schlüssel umbenennen
 //  '------------------------------------------------------------------------------------
 //  'Argumente:
 //  '   nHKEY               KEY
 //  '   sKeySource          alter Schlüsselname
 //  '   sKeyDestination     neuer Schlüsselname
 //  '====================================================================================
 extern  "C"  int  bakRegKey(  QY_ENV  *  pEnv,  HKEY  nHKEY,  TCHAR  *  sKeySource,  TCHAR  *  sKeyDestination  )
{
	int							iErr						=	-1;
	HKEY						hKeySource					=	NULL;	BOOL  bKeySourceOpen		=  FALSE;
	HKEY						hKeyDestination				=	NULL;	BOOL  bKeyDestinationOpen	=	FALSE;
	long						nResult;
	HANDLE						m_hToken					=	NULL;		// As Long	'Prozess-Token
	BOOL						bTokenOpen					=	FALSE;
	TOKEN_PRIVILEGES			m_TP;										// As		'Prozessprivilegien-Struktur
	LUID						m_RestoreLuid;								// As LUID	'Restore-Privileg
	LUID						m_BackupLuid;								// As LUID	'Backup-Privileg
	BOOL						bRestorePrivAdjusted		=	FALSE;
	BOOL						bBackupPrivAdjusted			=	FALSE;
	TCHAR						tmpPath[MAX_PATH  +  1]		=	_T(  ""  );
	TCHAR						tmpFileName[MAX_PATH  +  1]	=	_T(  ""  );
	QWM_DYN_LIB				*	pDynLib						=	(  QWM_DYN_LIB  *  )pEnv->pDynLibs;

	if  (  !bShlwApiOk(  pDynLib  )  )  return  -1;
	if  (  !sKeySource  ||  !sKeyDestination  )  return  -1;
	
    //  if  (  setBackupAndRestorePriviliges(  )  )  goto  errLabel;
	if  (  !pDynLib->pOpenProcessToken(  GetCurrentProcess(  ), TOKEN_ADJUST_PRIVILEGES  |  TOKEN_QUERY,  &m_hToken  )  )  goto  errLabel;
	bTokenOpen  =  TRUE;
	//
    if  (  !pDynLib->pLookupPrivilegeValue(  NULL,  SE_RESTORE_NAME,  &m_RestoreLuid  )  )  goto  errLabel;
    if  (  !pDynLib->pLookupPrivilegeValue(  NULL,  SE_BACKUP_NAME,  &m_BackupLuid  )  )  goto  errLabel;
	//
    m_TP.PrivilegeCount  =  1;
    m_TP.Privileges[0].Luid  =  m_RestoreLuid;
    m_TP.Privileges[0].Attributes  =  SE_PRIVILEGE_ENABLED;
	nResult  =  pDynLib->pAdjustTokenPrivileges(  m_hToken,  FALSE,  &m_TP,  sizeof(  m_TP  ),  NULL,  NULL  );
	if  (  !nResult  )  {  qyDisplayLastError(  "pAdjustTokenPrivileges"  );  goto  errLabel;  }
	bRestorePrivAdjusted  =  TRUE;
	//
    m_TP.PrivilegeCount  =  1;
    m_TP.Privileges[0].Luid  =  m_BackupLuid;
    m_TP.Privileges[0].Attributes  =  SE_PRIVILEGE_ENABLED;
    nResult  =  pDynLib->pAdjustTokenPrivileges(  m_hToken,  FALSE,  &m_TP,  sizeof(  m_TP  ),  NULL,  NULL  );
	if  (  !nResult  )  {  qyDisplayLastError(  "pAdjustTokenPrivileges"  );  goto  errLabel;  }
	bBackupPrivAdjusted  =	TRUE;
	//
	

	if  (  !GetTempPath(  mycountof(  tmpPath  ),  tmpPath  )  )  goto  errLabel;
	if  (  !GetTempFileName(  tmpPath,  _T(  "wrd"  ),  0,  tmpFileName  )  )  goto  errLabel;
	DeleteFile(  tmpFileName  );

    if  (  RegOpenKeyEx(  nHKEY,  sKeySource,  0,  KEY_ALL_ACCESS,  &hKeySource  )  !=  ERROR_SUCCESS  )  goto  errLabel;
	bKeySourceOpen  =  TRUE;
	if  (  RegSaveKey(  hKeySource,  tmpFileName,  0  )  !=  ERROR_SUCCESS  )  {
		qyDisplayLastError(  "RegSaveKey failed"  );  goto  errLabel;
	}

	nResult  =  RegOpenKeyEx(  nHKEY,  sKeyDestination,  NULL,  KEY_ALL_ACCESS,  &hKeyDestination  );
	if  (  nResult  ==  ERROR_FILE_NOT_FOUND  )  {
    	nResult  =  RegCreateKeyEx(  nHKEY,  sKeyDestination,  NULL,  _T(  ""  ),  NULL,  KEY_ALL_ACCESS,  NULL,  &hKeyDestination,  NULL  );
	}
	if  (  nResult !=  ERROR_SUCCESS  )   goto  errLabel;
	bKeyDestinationOpen  =  TRUE;

    if  (  RegRestoreKey(  hKeyDestination,  tmpFileName,  0  )  !=  ERROR_SUCCESS  )  goto  errLabel;
		
	iErr  =  0;
		
errLabel:
    if  (  bKeyDestinationOpen  )  RegCloseKey(  hKeyDestination  );
	if  (  bKeySourceOpen  )  RegCloseKey(  hKeySource  );

	//  这里将临时文件删除
	if  (  tmpFileName[0]  )  DeleteFile(  tmpFileName  );

	//  resetBackupAndRestorePriviliges(  );
	if  (  bRestorePrivAdjusted  )  {
		m_TP.PrivilegeCount  =  1;
		m_TP.Privileges[0].Luid  =  m_RestoreLuid;
		m_TP.Privileges[0].Attributes  =  SE_PRIVILEGE_ENABLED;
		nResult  =  pDynLib->pAdjustTokenPrivileges(  m_hToken,  TRUE,  &m_TP,  sizeof(  m_TP  ),  NULL,  NULL  );
		if  (  !nResult  )  traceLogA(  "renameRegKey错误：restore权限调整不回来了"  );    
	}
	if  (  bBackupPrivAdjusted  )  {
		m_TP.PrivilegeCount  =  1;
		m_TP.Privileges[0].Luid  =  m_BackupLuid;
		m_TP.Privileges[0].Attributes  =  SE_PRIVILEGE_ENABLED;
		nResult  =  pDynLib->pAdjustTokenPrivileges(  m_hToken,  TRUE,  &m_TP,  sizeof(  m_TP  ),  NULL,  NULL  );
		if  (  !nResult  )  traceLogA(  "renameRegKey错误：backup权限调整不回来了"  );    
	}

	if  (  bTokenOpen  )  CloseHandle(  m_hToken  );

    return  iErr;
}


