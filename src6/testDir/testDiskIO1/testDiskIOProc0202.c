#include	"diskIO.h"

 int  readSectors(  HANDLE hDrive,  LONG lOffset,  unsigned long  numberOfBytes,  void	*  buf  )
{
	 int					iRet		=   -1;
	 BOOL					bResult;
	 DWORD					numberOfBytesRead;
	 LPBYTE					lpSector;


	 lpSector = VirtualAlloc(  NULL, numberOfBytes,  MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE  );

	 // Move to nth(0~4177055) sector for something interesting to read.
	 //  SetFilePointer(  hDrive, dgDisk.BytesPerSector * ( 511 + i*2 ),  NULL,  FILE_BEGIN  );
	 if  (  SetFilePointer(  hDrive, lOffset,  NULL,  FILE_BEGIN  )  ==  0xFFFFFFFF  )  goto  errLabel;

	 if (  !(  bResult  =  ReadFile(	hDrive,  lpSector,  numberOfBytes,  &numberOfBytesRead,  NULL  )  )  )
	 {	
		 GetLastError(  );  goto  errLabel;  
	 }
	 //  WriteFile(  hFile,  lpSector,  dwSize,  &NumberOfBytesRead,  NULL  );
	 //  需要测试
 	 if  (  !( *lpSector )  )  {
		 fileName.endFlg  =  1;
	 	 printf(  " 到尾部了 "  );
	 	 goto  errLabel;
	 }
	 memcpy(  buf,  lpSector,  numberOfBytes  );
	 iRet	=  0;
	 VirtualFree(  lpSector,  0,  MEM_RELEASE  );    lpSector  =  NULL;
errLabel:
	 if  (  lpSector  )  {  VirtualFree(  lpSector,  0,  MEM_RELEASE  );    lpSector  =  NULL;  }
	 return		iRet;
}

 int  getBootBPB(  HANDLE hDrive  )
{
	 int		iRet	=  -1;
	 unsigned	char		   buf[CONST_bytesPerSector  +  1]  =  "";
	 unsigned	char		*  p  =  NULL;

	 memset(  &boot,  0,  sizeof(  boot  )  );
	 if  (  readSectors(  hDrive,  0,  CONST_bytesPerSector,  buf  )  )  goto  errLabel;
	 p  =  buf  + 3;
	 memcpy(  boot.oemId,  p,  8  );									p  =  p  +  8;
	 memcpy(  &boot.bytesPerSector,  p,  sizeof(  short  )  );			p  =  p  +  2;
	 memcpy(  &boot.sectorsPerCluster,  p,  sizeof(  char  )  );		p ++;
	 memcpy(  &boot.reservedSectors,  p,  sizeof(  short  )  );			p  =  p  +  2;
	 memcpy(  &boot.numberOfFATs,  p,  sizeof(  char )  );				p++;
	 memcpy(  &boot.rootEntries,  p,  sizeof(  short  )  );				p =  p  +  2;
	 memcpy(  &boot.smallSectors,  p,  sizeof(  short  )  );			p  =  p  +  2;
	 memcpy(  &boot.mediaDescriptor,  p,  sizeof(  char  )  );			p  ++;  
	 memcpy(  &boot.sectorsPerFAT,  p,  sizeof(  short  )  );			p  =  p  +  2;
	 memcpy(  &boot.sectorsPerHead,  p,  sizeof(  short  )  );			p  =  p  +  2;
	 memcpy(  &boot.headsPerCylinder,  p,  sizeof(  short  )  );		p  =  p  +  2;
	 memcpy(  &boot.hiddenSectors,  p,  sizeof(  long  )  );			p  =  p  +  4;
	 memcpy(  &boot.largeSectors,  p,  sizeof(  long  )  );				p  =  p  +  4;
	 memcpy(  &boot.physicalDriveNumber,  p,  sizeof(  char  )  );		p  ++;
	 memcpy(  &boot.currentHead,  p,  sizeof(  char  )  );				p  ++;
	 memcpy(  &boot.signature,  p,  sizeof(  char  )  );				p  ++;
	 memcpy(  &boot.ID,  p,  sizeof(  long  )  );						p  =  p  +  4;
	 memcpy(  boot.volumeLabel,  p,  11  );								p  =  p  +  11;
	 memcpy(  boot.systemId,  p,  8  );									p  =  p  +  8;
 
	 iRet	=  0;
errLabel:
	 return		iRet;
}

 int  longOrShortEntry(  unsigned  char  *  input  )
{
	 int   iFlg		=  0;			//  iFlg  =  0:  短项
	 unsigned	char	*  p  =  NULL;

 	 p  =  input  +  0x0B;
	 if  (  p  =  strchr(  p ,  0x0F  )  ) iFlg  =  1;
	 return  iFlg;
}


 int  subDirProc(  HANDLE	hDrive,  ROOT_DIR_ENTRY  *  dir  )
{
	 int							iRet			=  -1;
	 LONG							lClusterBase,  offset;
	 unsigned	char				buf[CONST_bytesOfCluster  +  1];
	 unsigned	char			*	p;
	 unsigned	char				tmpBuf[CONST_bytesPerShortEntry  +  1] = "";
	 ROOT_DIR_ENTRY					shortName;

	 memset(  &shortName,  0,  sizeof(  shortName  )  );

	 lClusterBase	=  boot.bytesPerSector  *  (  boot.reservedSectors  +  boot.numberOfFATs * boot.sectorsPerFAT  +  CONST_sectorsForRootDir);
	 offset  =  (  dir->firstClusterNo  -  CONST_startClusterNo  )  *  boot.sectorsPerCluster  *  boot.bytesPerSector;

	 if (  readSectors(  hDrive,    lClusterBase  +  offset,  boot.sectorsPerCluster  *  boot.bytesPerSector,  buf  )  )  goto  errLabel;
	 p  =  buf  +  2  *  CONST_bytesPerShortEntry;
	 memcpy(  tmpBuf,  p,  CONST_bytesPerShortEntry  );
	 if (  longOrShortEntry(  p  )  ) printf ( "子目录中的长文件名"  );
	 else	{
		 printf(  "子目录中的短文件名"  );
		 getShortEntry(  hDrive,  tmpBuf,  &shortName  );
	 }

	 iRet	=  0;
errLabel:
	 return		iRet;
}

 int  getShortEntry(  HANDLE  hDrive,  unsigned  char  *  input,  ROOT_DIR_ENTRY  *  shortEntry )
{
	 int	iRet	=  -1;
	 unsigned  char		buf[CONST_bytesPerShortEntry  +  1]  =  "";
	 unsigned  char		*	p  =  NULL;
	 unsigned  char			tmpBuf[CONST_bytesPerShortEntry  +  1];

	 p  = input;
	 memcpy(  shortEntry,  (  ROOT_DIR_ENTRY  *  )p,  CONST_bytesPerShortEntry  );
	 if  (  !shortEntry->bytesOfFile  )  subDirProc(  hDrive,  shortEntry  );
	 printf(  "是文件!"  );
	 memcpy( tmpBuf,  p,  CONST_bytesPerShortEntry  );

	 iRet  =  0;
//  errLabel:
	 return  iRet;
}

 int  getRootEntry(  HANDLE  hDrive,  unsigned int  count )
{
	 int					iRet		=  -1;
	 unsigned  char			buf[CONST_bytesPerSector *  4  +  1]  =  "";
	 ROOT_LFN_ENTRY			longFile;
	 ROOT_DIR_ENTRY			shortName;
	 unsigned	char	*	p  =  NULL;
	 LONG					basic,  offset;
	 unsigned	char		tmpBuf[CONST_bytesPerShortEntry  +  1];

	 memset(  &longFile,  0,  sizeof(  longFile  )  );
	 memset(  &shortName,  0,  sizeof(  shortName  )  );
	 basic  =  boot.bytesPerSector  *  (  boot.reservedSectors + boot.sectorsPerFAT * boot.numberOfFATs  );
	 offset  =  count *  boot.bytesPerSector; 

	 if  (  readSectors(  hDrive,  basic + count,  boot.bytesPerSector * 4,  buf  )  )  goto  errLabel;
	 memcpy(  tmpBuf,  buf,  CONST_bytesPerShortEntry  );
	 if  (  longOrShortEntry(  tmpBuf  )  ) printf( "长文件名"  );
	 else	{
		 printf(  "短文件名"  );
		 getShortEntry(  hDrive,  tmpBuf,  &shortName );
	 }
		 


	 iRet	=  0;
errLabel:
	 return	 iRet;
}

