

#include <stdio.h> 
#include <string.h>

#include	<windows.h>
#include	<tchar.h>

#include	"qyCommon.h"
#include	"qyEncCommon.h"
#include	"qyLicense.h"
#include	"qyCommProc.h"

extern  "C"  void  getQwmSortedMacs(  QY_ENV  *  pEnv,  QWM_MACS_INFO  *  pMacsInfo  );



#define		DFP_GET_VERSION				0x00074080 
#define		DFP_SEND_DRIVE_COMMAND		0x0007c084 
#define		DFP_RECEIVE_DRIVE_DATA		0x0007c088 

#pragma pack(1) 
typedef struct _GETVERSIONOUTPARAMS { 
 BYTE bVersion;  // Binary driver version. 
 BYTE bRevision;  // Binary driver revision. 
 BYTE bReserved;  // Not used. 
 BYTE bIDEDeviceMap; // Bit map of IDE devices. 
 DWORD fCapabilities; // Bit mask of driver capabilities. 
 DWORD dwReserved[4]; // For future use. 
} GETVERSIONOUTPARAMS, *PGETVERSIONOUTPARAMS, *LPGETVERSIONOUTPARAMS; 

#if _MSC_VER < 1500

typedef struct _IDEREGS { 
 BYTE bFeaturesReg;  // Used for specifying SMART "commands". 
 BYTE bSectorCountReg; // IDE sector count register 
 BYTE bSectorNumberReg; // IDE sector number register 
 BYTE bCylLowReg;   // IDE low order cylinder value 
 BYTE bCylHighReg;  // IDE high order cylinder value 
 BYTE bDriveHeadReg;  // IDE drive/head register 
 BYTE bCommandReg;  // Actual IDE command. 
 BYTE bReserved;   // reserved for future use.  Must be zero. 
} IDEREGS, *PIDEREGS, *LPIDEREGS; 

typedef struct _SENDCMDINPARAMS { 
 DWORD cBufferSize;  // Buffer size in bytes 
 IDEREGS irDriveRegs;  // Structure with drive register values. 
 BYTE bDriveNumber;  // Physical drive number to send 
        // command to (0,1,2,3). 
 BYTE bReserved[3];  // Reserved for future expansion. 
 DWORD dwReserved[4];  // For future use. 
 //BYTE  bBuffer[1];   // Input buffer. 
} SENDCMDINPARAMS, *PSENDCMDINPARAMS, *LPSENDCMDINPARAMS; 

typedef struct _DRIVERSTATUS { 
 BYTE bDriverError;  // Error code from driver, 
        // or 0 if no error. 
 BYTE bIDEStatus;   // Contents of IDE Error register. 
        // Only valid when bDriverError 
        // is SMART_IDE_ERROR. 
 BYTE bReserved[2];  // Reserved for future expansion. 
 DWORD dwReserved[2];  // Reserved for future expansion. 
} DRIVERSTATUS, *PDRIVERSTATUS, *LPDRIVERSTATUS; 

typedef struct _SENDCMDOUTPARAMS { 
 DWORD    cBufferSize;  // Size of bBuffer in bytes 
 DRIVERSTATUS DriverStatus;  // Driver status structure. 
 BYTE   bBuffer[512];   // Buffer of arbitrary length 
          // in which to store the data read from the drive. 
} SENDCMDOUTPARAMS, *PSENDCMDOUTPARAMS, *LPSENDCMDOUTPARAMS; 

#endif  

typedef struct _IDSECTOR { 
 USHORT wGenConfig; 
 USHORT wNumCyls; 
 USHORT wReserved; 
 USHORT wNumHeads; 
 USHORT wBytesPerTrack; 
 USHORT wBytesPerSector; 
 USHORT wSectorsPerTrack; 
 USHORT wVendorUnique[3]; 
 CHAR sSerialNumber[20]; 
 USHORT wBufferType; 
 USHORT wBufferSize; 
 USHORT wECCSize; 
 CHAR sFirmwareRev[8]; 
 CHAR sModelNumber[40]; 
 USHORT wMoreVendorUnique; 
 USHORT wDoubleWordIO; 
 USHORT wCapabilities; 
 USHORT wReserved1; 
 USHORT wPIOTiming; 
 USHORT wDMATiming; 
 USHORT wBS; 
 USHORT wNumCurrentCyls; 
 USHORT wNumCurrentHeads; 
 USHORT wNumCurrentSectorsPerTrack; 
 ULONG ulCurrentSectorCapacity; 
 USHORT wMultSectorStuff; 
 ULONG ulTotalAddressableSectors; 
 USHORT wSingleWordDMA; 
 USHORT wMultiWordDMA; 
 BYTE bReserved[128]; 
} IDSECTOR, *PIDSECTOR; 

/*+++ 
Global vars 
---*/ 
GETVERSIONOUTPARAMS vers; 
SENDCMDINPARAMS in; 
SENDCMDOUTPARAMS out; 
HANDLE h; 
DWORD i; 
BYTE j; 


//  -------------------------by wqh.20040316
//void CopyRight(){ 
// cerr<<endl<<"HDD identifier v1.0 for WIN95/98/Me/NT/2000. written by Lu Lin"<<endl; 
// cerr<<"For more information, please visit Inside Programming: http://lu0.126.com"<<endl; 
// cerr<<"2000.11.3"<<endl<<endl; 
// } 
VOID ChangeByteOrder(PCHAR szString, USHORT uscStrSize) 
{ 

USHORT i; 
CHAR temp; 

 for (i = 0; i < uscStrSize; i+=2) 
 { 
  temp = szString[i]; 
  szString[i] = szString[i+1]; 
  szString[i+1] = temp; 
 } 
} 

void DetectIDE(BYTE bIDEDeviceMap){ 
 if (bIDEDeviceMap&1){ 
  if (bIDEDeviceMap&16){ 
   //  cout<<"ATAPI device is attached to primary controller, drive 0."<<endl; =---by wqh.
	  //AfxMessageBox(  "ATAPI  device is attached to primary controller,  drive 0."  );
  }else{ 
   //  cout<<"IDE device is attached to primary controller, drive 0."<<endl; 
	  //AfxMessageBox(  "IDE  device  is  attached  to primary controller,  drive  0."  );
  } 
 } 
 if (bIDEDeviceMap&2){ 
  if (bIDEDeviceMap&32){ 
   //  cout<<"ATAPI device is attached to primary controller, drive 1."<<endl; 
	  //AfxMessageBox(  "ATAPI  device  is  attached  to  primary controller,  drive 1."  );
  }else{ 
   //  cout<<"IDE device is attached to primary controller, drive 1."<<endl; 
	  //AfxMessageBox(  "IDE  device is attached  to primary controller, drive  1."  );
  } 
 } 
 if (bIDEDeviceMap&4){ 
  if (bIDEDeviceMap&64){ 
   //  cout<<"ATAPI device is attached to secondary controller, drive 0."<<endl; 
	  //AfxMessageBox(  "ATAPI  device is attached to secondary controller,  drive 0"  );
  }else{ 
   //  cout<<"IDE device is attached to secondary controller, drive 0."<<endl; 
	  //AfxMessageBox(  "IDE  device is attached  to secondary controller,  drive 0."  );
  } 
 } 
 if (bIDEDeviceMap&8){ 
  if (bIDEDeviceMap&128){ 
   //  cout<<"ATAPI device is attached to secondary controller, drive 1."<<endl; 
	  //AfxMessageBox(  "ATAPI  device  is  attached to secondary controller,  drive 1."  );
  }else{ 
   //  cout<<"IDE device is attached to secondary controller, drive 1."<<endl; 
	  //AfxMessageBox(  "IDE  device is attached  to secondary  controller,  drive 1."  );
  } 
 } 
} 

void hdid9x(){ 
 ZeroMemory(&vers,sizeof(vers)); 
 //We start in 95/98/Me 
 h=CreateFile(  _T(  "\\\\.\\Smartvsd"  ),0,0,0,CREATE_NEW,0,0); 
 if (!h){ 
  //  cout<<"open smartvsd.vxd failed"<<endl;		--------by  wqh .20040316
	 //AfxMessageBox(  "open smartvsd.vxd  failed"  );
  exit(0); 
 } 

 if (!DeviceIoControl(h,DFP_GET_VERSION,0,0,&vers,sizeof(vers),&i,0)){ 
  //  cout<<"DeviceIoControl failed:DFP_GET_VERSION"<<endl; --------by wqh.
	 //AfxMessageBox(  "DeviceIoControl failed:DFP_GET_VERSION"  );
  CloseHandle(h); 
  return; 
 } 
 //If IDE identify command not supported, fails 
 if (!(vers.fCapabilities&1)){ 
  // cout<<"Error: IDE identify command not supported.";   --------by  wqh.
	 //AfxMessageBox(  "Error:  IDE  identify  command  not  supported "  );
  CloseHandle(h); 
  return; 
 } 
 //Display IDE drive number detected 
 DetectIDE(vers.bIDEDeviceMap); 
 //Identify the IDE drives 
 for (j=0;j<4;j++){ 
  PIDSECTOR phdinfo; 
  char s[41]; 

  ZeroMemory(&in,sizeof(in)); 
  ZeroMemory(&out,sizeof(out)); 
  if (j&1){ 
   in.irDriveRegs.bDriveHeadReg=0xb0; 
  }else{ 
   in.irDriveRegs.bDriveHeadReg=0xa0; 
  } 
  if (vers.fCapabilities&(16>>j)){ 
   //We don't detect a ATAPI device. 
   //  cout<<"Drive "<<(int)(j+1)<<" is a ATAPI device, we don't detect it"<<endl;   ------by wqh. 20040316
	 // AfxMessageBox(  "Drive"  );
   continue; 
  }else{ 
   in.irDriveRegs.bCommandReg=0xec; 
  } 
  in.bDriveNumber=j; 
  in.irDriveRegs.bSectorCountReg=1; 
  in.irDriveRegs.bSectorNumberReg=1; 
  in.cBufferSize=512; 
  if (!DeviceIoControl(h,DFP_RECEIVE_DRIVE_DATA,&in,sizeof(in),&out,sizeof(out),&i,0)){ 
   //  cout<<"DeviceIoControl failed:DFP_RECEIVE_DRIVE_DATA"<<endl; ----by wqh.20040316
	 // AfxMessageBox(  "DeviceIoControl failed:DFP_RECEIVE_DRIVE_DATA"  );
   CloseHandle(h); 
   return; 
  } 
  phdinfo=(PIDSECTOR)out.bBuffer; 
  memcpy(s,phdinfo->sModelNumber,40); 
  s[40]=0; 
  ChangeByteOrder(s,40); 
  //  cout<<endl<<"Module Number:"<<s<<endl;   ---by wqh.20040316.
  //AfxMessageBox(  "Module  Number:"  );
  memcpy(s,phdinfo->sFirmwareRev,8); 
  s[8]=0; 
  ChangeByteOrder(s,8); 
  //  cout<<"\tFirmware rev:"<<s<<endl; 
  //AfxMessageBox(  "Firmware rev:"  );
  memcpy(s,phdinfo->sSerialNumber,20); 
  s[20]=0; 
  ChangeByteOrder(s,20); 
  //  cout<<"\tSerial Number:"<<s<<endl; 
  //  cout<<"\tCapacity:"<<phdinfo->ulTotalAddressableSectors/2/1024<<"M"<<endl<<endl; 
  //AfxMessageBox(  "Serial Number:"  );
 } 

 //Close handle before quit 
 CloseHandle(h); 
 //  CopyRight();    ------------------------by wqh.20040316

} 

 void hdidnt(  unsigned  char  *  tmpBuf )
{
	 TCHAR hd[80]; 
	 PIDSECTOR phdinfo; 
	 char s[41]; 
	 int  j  =  0;

 
	 ZeroMemory(&vers,sizeof(vers)); 
	 //We start in NT/Win2000		//  切记：尚未考虑多硬盘问题
	 //  for (j=0;j<4;j++){ 
	 _sntprintf(hd,  sizeof(  hd  )  /  sizeof(  hd[0]  ),  _T(  "\\\\.\\PhysicalDrive%d"  ),j); 
	 h=CreateFile(hd,GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE,0,OPEN_EXISTING,0,0); 
	 if  (  !h  )  goto errLabel;
	 if (!DeviceIoControl(h,DFP_GET_VERSION,0,0,&vers,sizeof(vers),&i,0)){ 
		 CloseHandle(h); goto  errLabel; 
	 }
	 //If IDE identify command not supported, fails 
	 if (!(vers.fCapabilities&1)){ 
		 //  cout<<"Error: IDE identify command not supported."; ------by  wqh.
		 //	  AfxMessageBox(  "IDE  identify  command  not supported."  );
		 goto  errLabel;
	 } 
	 //Identify the IDE drives 
	 ZeroMemory(&in,sizeof(in)); 
	 ZeroMemory(&out,sizeof(out)); 
	 if (j&1){ 
		 in.irDriveRegs.bDriveHeadReg=0xb0; 
	 }
	 else{ 
		 in.irDriveRegs.bDriveHeadReg=0xa0; 
	 } 
	 if (vers.fCapabilities&(16>>j)){ 
		 //We don't detect a ATAPI device. 
		 //  cout<<"Drive "<<(int)(j+1)<<" is a ATAPI device, we don't detect it"<<endl; 
		 //	  AfxMessageBox(  "Drive"  );
		 goto  errLabel; 
	 }
	 else  { in.irDriveRegs.bCommandReg=0xec;  } 
	 in.bDriveNumber=j; 
	 in.irDriveRegs.bSectorCountReg=1; 
	 in.irDriveRegs.bSectorNumberReg=1; 
	 in.cBufferSize=512; 
	 if (!DeviceIoControl(h,DFP_RECEIVE_DRIVE_DATA,&in,sizeof(in),&out,sizeof(out),&i,0)){ 
		 //  cout<<"DeviceIoControl failed:DFP_RECEIVE_DRIVE_DATA"<<endl; 
		 //	  AfxMessageBox(  "DeviceIoControl failed:DFP_RECEIVE_DRIVE_DATA"  );
		 goto  errLabel;
	 } 
	 phdinfo=(PIDSECTOR)out.bBuffer; 
	 /*
		 memcpy(s,phdinfo->sModelNumber,40); 
		 //  memcpy(  tmpBuf,  phdinfo->sModelNumber,  sizeof(  tmpBuf  )  );
		 s[40]=0; 
		 ChangeByteOrder(s,40); 
		 //  cout<<endl<<"Module Number:"<<s<<endl; 
		 //AfxMessageBox(  "Module Number: "  );
		 memcpy(s,phdinfo->sFirmwareRev,8); 
		 s[8]=0; 
		 ChangeByteOrder(s,8); 
		 //  cout<<"\tFirmware rev:"<<s<<endl; 
		 //AfxMessageBox(  "\tFirmware rev:"  );
	 */
	 if  (  !phdinfo->sSerialNumber  )  goto  errLabel;
	 memcpy(s,phdinfo->sSerialNumber,20); 
	 s[20]=0; 
	 ChangeByteOrder(s,20); 
	 strcat(  (  char  *  )tmpBuf,  s  );  
	 //  cout<<"\tSerial Number:"<<s<<endl; 
	 //  cout<<"\tCapacity:"<<phdinfo->ulTotalAddressableSectors/2/1024<<"M"<<endl<<endl; 
	 //AfxMessageBox(  "\tSerial Number:"  );
	 // } 
	 //  CopyRight();  ------------------------by wqh .20040316
errLabel:
	 if  (  h  )  CloseHandle(  h  );
	 return;
}

 int  testCpuId( unsigned  char  *  cpuIdBuf ) 
{
	 unsigned long s1,s2;
	 unsigned char vendor_id[]="------------";
	 unsigned char buf[64] = "";
#if  0
//	 char sel;
//	 printf("Select the function:\n1-------Read CPU id.	\
//								 \n2-------Disable CPU id.\n");
//	 sel=getch();
//	 switch(sel)	 {
//	 case '1':
		 _asm {
			 xor eax,eax
			 cpuid
			 mov dword ptr vendor_id,ebx
			 mov dword ptr vendor_id[+4],edx
			 mov dword ptr vendor_id[+8],ecx
		 }
		 printf("%s-",vendor_id);
		 _asm {
			 mov eax,01h
			 xor edx,edx
			 cpuid
			 mov s1,edx
			 mov s2,eax
		 }
		 sprintf(  (  char  *  )cpuIdBuf, "%08X-%08X-",s1,s2);
		 _asm {
			 mov eax,03h
			 xor ecx,ecx
			 xor edx,edx
			 cpuid
			 mov s1,edx
			 mov s2,ecx
		 }
		 sprintf((  char *  )&buf, "%08X-%08X",s1,s2);
		 strcat(  (  char  *  )cpuIdBuf,  (  char  *  )&buf  );
//		 break;
//	 case '2':
//		 _asm{
//			 mov ecx,119h
//			 rdmsr
//			 or eax,00200000h
//			 wrmsr
//		 }
//		 printf("CPU id is disabled.\n");
//		 break;
//	 }
#endif
	 return 0;
}

 //  extern  "C"  void  getQwmSortedMacs(  QWM_MACS_INFO  *  pMacsInfo  );

 extern  "C"  int  testProductIdMain(  void  *  pEnvParam,  char  *  idBuf,  unsigned int * idBufSize  )
{
	 int					iErr			=  -1;
	 OSVERSIONINFO			VersionInfo; 

	 unsigned  char			buf[128]		=	"";
	 unsigned  char			tmpBuf[128]		=	"";
	 char					outputBuf[256]	=   "";
//	 unsigned  int			outputBufSize;
//	 unsigned  int			len;
//	 char				*	pMacs[ 10];
	 //  char				macs[CONST_qnmMaxMacs][CONST_qyMacLen  +  1];
//	 unsigned  int			pMaxMacs;
	 QWM_MACS_INFO			macsInfo;

#if  0

	 memset(  &macsInfo,  0,  sizeof(  macsInfo  )  );
	 getQwmSortedMacs(  (  QY_ENV  *  )pEnvParam,  &macsInfo    );
	 strcat(  idBuf,  (const char *  )&macsInfo.macs[0]  );			//  仅以第一块网卡为准
	 if  (  !*idBuf  )  goto  errLabel;
	 //  traceLogA(  "  网卡id :  %s,  ok!",  idBuf  );


	 testCpuId( (  unsigned  char  *  )&buf ); 
	 if  (  !*buf  )  goto  errLabel;
	 // traceLogA(  "  cpu Id :  %s,  ok!",  buf  );
	 strcat(  idBuf,  (  const char  *  )&buf  );
	 
	 ZeroMemory(&VersionInfo,sizeof(VersionInfo)); 
	 VersionInfo.dwOSVersionInfoSize=sizeof(VersionInfo); 
	 GetVersionEx(&VersionInfo); 
	 
	 switch (VersionInfo.dwPlatformId){ 
	 case VER_PLATFORM_WIN32s: 
		 // cout<<"Win32s is not supported by this programm."<<endl; ---by wqh.
		 MessageBox(  NULL,  _T(  "Win32s is not supported  by this program."  ),  _T(  ""  ),  MB_OK  );  goto  errLabel;
		 break; 
	 case VER_PLATFORM_WIN32_WINDOWS: 
		 MessageBox(  NULL,  _T(  "  系统只能安装在windows 2000以上操作系统上！"  ),  _T(  ""  ),  MB_OK  );  goto  errLabel;
		 hdid9x();			//  由于应用程序的安装环境将在windows 2000上，故本98系统没有进行处理。
		 break; 
	 case VER_PLATFORM_WIN32_NT: 
		 hdidnt(  tmpBuf  ); 
		 //  traceLogA(  "  hardware  Id  is : %s,  ok!",  tmpBuf  );
		 strcat(  idBuf,  (  char *  )&tmpBuf  );
		 qyTrim(  idBuf  );
		 //  traceLogA(  "  所有硬件参数：%s,  ok!",  idBuf  );
		 break; 
	 }
	 *idBufSize  =  strlen(  idBuf  );
#endif
	 
	 iErr  =  0;

errLabel:
	return    iErr;
} 
  
#define			CONST_HWHEAD			"I love you:"
#define			CONST_HWTAIL			"I love every people!"
 extern "C"  int  spoofHarewareId(  char  *  oldBuf,  unsigned int * oldBufSize )
{
	 int				iErr			=  -1;
	 char				tmpBuf[256]		=  "";
	 char				spoofBuf[256]	=  "";
	 unsigned  int		spoofBufSize;
	 unsigned  int		len;

	 memset( tmpBuf, 0, sizeof( tmpBuf ) );
	 memcpy( tmpBuf, CONST_HWHEAD,  sizeof(  CONST_HWHEAD  ) );
	 strcat( tmpBuf,  oldBuf  );
	 strcat( tmpBuf,  CONST_HWTAIL  );

	 len  =  strlen(  tmpBuf  );
	 if  (  testLicenseMain(  tmpBuf,  len,  spoofBuf,  &spoofBufSize  )  )  goto  errLabel;
	 
	 memset(  oldBuf, 0, CONST_hardwareId_len  );
	 strncpy(  oldBuf,  spoofBuf,  CONST_hardwareId_len  );
	 *oldBufSize  =  strlen(  oldBuf  );

	 iErr			=   0;
errLabel:
	 return				iErr;
}
