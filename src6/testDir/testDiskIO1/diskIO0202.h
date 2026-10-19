#ifndef __DISKIO__
#define __DISKIO__

#include <windows.h>
#include <stdio.h>
#include <winioctl.h>
#include "qyCommon.h"

#define		u_int64_t						unsigned __int64
#define		u_int32_t						unsigned __int32
#define		u_int16_t						unsigned __int16
#define		u_int8_t						unsigned __int8
//#define		__s16						__int16
//#define		__s32						__int32
#define		int8_t							__int8
#define		int16_t							__int16
#define		int32_t							__int32
#define		int64_t							__int64

#define		OFF_T							__int64   //  _off_t ,  吃不准
#define		mode_t							__int16
#define		uid_t							__int32
#define		gid_t							__int32




#define		CONST_bytesPerSector				512			//  FAT16	
#define		CONST_sectorsForRootDir				32			//  FAT16
#define		CONST_startSectorForRootDir			511			//  FAT16
#define		CONST_bytesPerShortEntry			32			//  FAT16
#define		CONST_bytesPerBasicLongEntry		64			//  FAT16
#define		CONST_sectorsPerCluster				64			//  需要从BPB中读取
#define		CONST_startSectorForCluster			543			//  需要从BPB中读取并计算
#define		CONST_startClusterNo				0x0002		//  FAT16
#define		CONST_bytesOfCluster				512*64		//  FAT16

#ifdef  __cplusplus
		extern  "C"  {
#endif

typedef  struct  {
			int						longFlg;				//  1:长文件名
			int						delFlg;					//	1:被删除文件名
			int						endFlg;					//  1:到尾部了
			int						dirFlg;					//  1:目录项;  0:文件项
}		 FSFILENAME;

typedef	 struct  {
			unsigned	char		oemId[8  +  1];			//  8b
			unsigned	short		bytesPerSector;			//  2b
			unsigned	char		sectorsPerCluster;		//  1b
			unsigned	short		reservedSectors;		//  2b
			unsigned	char		numberOfFATs;			//  1b
			unsigned	short		rootEntries;			//  2b  only FAT16; FAT32 为 0
			unsigned	short		smallSectors;			//  2b  small disk
			unsigned	char		mediaDescriptor;		//  1b  F8:  hard disk
			unsigned	short		sectorsPerFAT;			//  2b	only FAT12/16; FAT32 为 0
			unsigned	short		sectorsPerHead;			//  2b
			unsigned	short		headsPerCylinder;		//  2b
			unsigned	long		hiddenSectors;			//  4b
			unsigned	long		largeSectors;			//  4b
			/*  followed only used for LargeSectors  */
			unsigned	char		physicalDriveNumber;	//  1b  
			unsigned	char		currentHead;			//  1b
			unsigned	char		signature;				//  1b
			unsigned	long		ID;						//  4b
			unsigned	char		volumeLabel[11  +  1];	//  11b
			unsigned	char		systemId[8  +  1];		//  8b
			/*  followed noUsed  */
			unsigned	long		bigSectorsPerFAT;		//  4b	only FAT32
			unsigned	short		extFlags;				//  2b
			unsigned	short		FSVersion;				//  2b
			unsigned	long		rootDirectoryStart;		//  4b
			unsigned	short		FSInfoSector;			//  2b
			unsigned	short		backupBootSector;		//  2b
			unsigned	char		reserved[12  +  1];		//  12b
}		BOOT_BPB;		//  BIOS  Parameter  Block

typedef  struct	{
			unsigned	char		name[8];			//  8b
			unsigned	char		extName[3];		//  3b
			unsigned	char		attribute;				//  1b
			unsigned	char		reserved;				//  1b
			unsigned	char		vFATCreateTime;			//  1b
			unsigned	char		createTime[2];			//  2b
			unsigned	char		createDate[2];			//  2b
			unsigned	char		accessTime[2];				//  2b
			unsigned	short		upperClusterNo;			//  2b
			unsigned	char		updataTime[2];				//  2b
			unsigned	char		updataData[2];				//  2b
			unsigned	short		firstClusterNo;			//  2b  lowerClusterNo
			unsigned	long		bytesOfFile;			//  4b  only file; dir 为 0
}		ROOT_DIR_ENTRY;				//  FAT16  short entry:  32bytes

typedef  struct	 {
			unsigned	char		no;						//	1b
			LPTSTR					firstPartUnicode;		//  10b
			unsigned	char		attribute;				//  1b  0F: 代表LFN
			unsigned	char		reserved;				//  1b
			unsigned	char		checkSum;				//  1b
			LPTSTR					secondPartUnicode;		//  12b
			unsigned	short		noUsed;					//  2b
			LPTSTR					thirdPartUnicode;		//  4b
}		ROOT_LFN_ENTRY;				//  long  file name:  32bytes


DISK_GEOMETRY			dgDisk;
DWORD					SupportedGeometryCount;
//  char				szFileBuf[2048];
BOOT_BPB				boot;
FSFILENAME				fileName;
FSFILENAME				subFileName;


/*  testDiskIOProc.c  */
int  readSectors(  HANDLE hDrive,  LONG lOffset,  unsigned long  numberOfBytes,  void	*  buf  );
int  getBootBPB(  HANDLE hDrive  );
int  longOrShortEntry(  unsigned  char  *  input  );
int  subDirProc(  HANDLE	hDrive,  ROOT_DIR_ENTRY  *  dir  );
int  getShortEntry(  HANDLE  hDrive,  unsigned  char  *  input,  ROOT_DIR_ENTRY  *  shortEntry );
int  getRootEntry(  HANDLE  hDrive,  unsigned int  count );


/*  testOld.c  */
VOID  GetSupportedGeometrys( HANDLE hDisk );
VOID  PrintGeometry( PDISK_GEOMETRY lpGeometry );
int  enumFileName(  );
int  getLongFileNameFAT16(  FSFILENAME  *  fs,  unsigned  char  *  input  );
int  getRootDirEntryFAT16(  unsigned  char  *  input,  FSFILENAME  *  fs  );






#ifdef  __cplusplus
		}
#endif

#endif