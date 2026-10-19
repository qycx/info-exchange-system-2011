#include	"diskIO.h"

VOID  GetSupportedGeometrys( HANDLE hDisk )
{
	DWORD ReturnedByteCount;
   
	if(  DeviceIoControl(  hDisk,  IOCTL_DISK_GET_DRIVE_GEOMETRY,  //IOCTL_DISK_GET_MEDIA_TYPES,
		               NULL,  0,  &dgDisk,  sizeof(  dgDisk  ),
					   &ReturnedByteCount,  NULL  )  )
     	 SupportedGeometryCount = ReturnedByteCount / sizeof(DISK_GEOMETRY);
	
	else SupportedGeometryCount = 0;
}

 VOID  PrintGeometry( PDISK_GEOMETRY lpGeometry )
{
	 LPSTR MediaType;

	 switch ( lpGeometry->MediaType ) {
         case F5_1Pt2_512:
            MediaType = "5.25, 1.2MB,  512 bytes/sector";
            break;
         case F3_1Pt44_512:
            MediaType = "3.5,  1.44MB, 512 bytes/sector";
            break;
         case F3_2Pt88_512:
            MediaType = "3.5,  2.88MB, 512 bytes/sector";
            break;
         case F3_20Pt8_512:
            MediaType = "3.5,  20.8MB, 512   bytes/sector";
            break;
         case F3_720_512:
            MediaType = "3.5,  720KB,  512 bytes/sector";
            break;
         case F5_360_512:
            MediaType = "5.25, 360KB,  512 bytes/sector";
            break;
         case F5_320_512:
            MediaType = "5.25, 320KB,  512 bytes/sector";
            break;
         case F5_320_1024:
            MediaType = "5.25, 320KB,  1024 bytes/sector";
            break;
         case F5_180_512:
            MediaType = "5.25, 180KB,  512 bytes/sector";
            break;
         case F5_160_512:
            MediaType = "5.25, 160KB,  512  bytes/sector";
            break;
         case RemovableMedia:
            MediaType = "Removable media other than floppy";
            break;
         case FixedMedia:
            MediaType = "Fixed hard disk media";
            break;
         default:
            MediaType = "Unknown";
            break;
	 }
	 printf("    Media Type %s\n", MediaType );
     printf("    Cylinders %d, Tracks/Cylinder %d, Sectors/Track %d\n",
             lpGeometry->Cylinders.LowPart, lpGeometry->TracksPerCylinder,
             lpGeometry->SectorsPerTrack
            );
}
 
 int  enumFileName(  )
{
	 int  iRet		=  -1;


	 iRet	=	0;
//  errLabel:
	 return  iRet;
}

 int  getLongFileNameFAT16(  FSFILENAME  *  fs,  unsigned  char  *  input  )
{
	 int					iRet  =  -1;
	 unsigned  char		*	p;
	 unsigned  char			buf[256]  =  "";
	 int					i  =  0;
	 unsigned  char			tmpChar[2]  =  "";

	 p  =  input;
	 fs->longFlg  =  1;							// noUse
	 p  =  p + 1;
	 for ( i = 0; i < 5; i++ ) {
		 if  (  *p ==  0xFF  ) goto  errLabel;
		 lstrcpy(  buf + i,  p  );
		 p  =  p + 2;
	 }
	 p  =  p + 3;
	 for ( i = 0; i < 6; i++ ) {
		 if  (  *p ==  0xFF  ) goto  errLabel;
		 lstrcpy(  buf + 5 + i,  p  );
		 p  =  p  +  2;
	 }
	 p  =  p  +  2;
	 for ( i = 0; i < 2; i++ ) {
		 if  (  *p  ==  0xFF  )  goto  errLabel;
		 lstrcpy(  buf + 11 + i,  p  );
		 p  =  p  +  2;
	 }

	 //  区分目录
	 p  =  buf  +  lstrlen(  buf  )  -  4;
	 if  (  !(  *p  ==  '.'  )  )  
		 strncat(  buf,  "\\",  1  );  
	 
 	 //  被删除文件名
 	 memset(  tmpChar,  0xE5,  1  );
	 if  (  !(  strnicmp(  input,  tmpChar,  1  )  &&  strnicmp(  input,  tmpChar,  1  )  )  ) {
		 fileName.delFlg	=  1;		//  noUse
		 //  memset(  buf,  '?',  1  );
		 printf(  " %s ,  已删除  \n",  buf  );
	 }
	 else    printf(  " %s  \n",  buf  );


	 iRet  =  0;
errLabel:
	 return  iRet;
}

 //  处理FAT16目录中的短项/被删除
 int  getRootDirEntryFAT16(  unsigned  char  *  input,  FSFILENAME  *  fs  )
{
	 int  iRet  =  -1;
	 unsigned  char  *  p;
	 unsigned  char		buf[256]  =  "";
	 unsigned  char	    tmBuf[10]  =  "";
	 unsigned  char		tmpChar[2]  =  "";

	 if  (  !( *input )  )  {
		 fs->endFlg  =  1;
		 printf(  " 到尾部了 "  );
		 goto  errLabel;
	 }

	 p  =  input  +  0x000B;
	 
	 //  长文件名:0F  
	 memset(  tmpChar,  0x0F,  1  );
	 if  (  !strnicmp(  p,  tmpChar,  1  )  )  {
		 getLongFileNameFAT16(  fs,  input  );
		 goto  errLabel;
	 }
	 //  短文件名
	 strncpy(  buf,  input,  8  );
	 strncpy(  tmBuf,  input  +  8,  3  );
	 //  文件项"."
	 if  (  (  strnicmp(  tmBuf, "!", 1 )  >=  0  )  
		 &&  (  strnicmp(  tmBuf, "~", 1 )  <=  0  )  )		 //  printf(  " 小于7B"  );
	 {
		 fileName.dirFlg  =  0;
		 if  (  p  =  strchr(  buf,  ' ' )  )  {
			 memset(  p,  '.',  1  );
			 p  =  p  + 1;
			 strncpy(  p,  input  +  8,  3  );
		 }
		 else  {
			 memset(  buf + 8,  '.',  1  );
			 strncpy(  buf + 9,  input + 8,  3  );
		 }

	 }
	 //  目录项"\"
	 else  {
		 fileName.dirFlg  =  1;
		 if  (  p  =  strchr(  buf,  ' '  )  ) {
			 strncpy(  p,  "\\",  1  );
		 }
		 else   strncpy(  buf  +  8,  "\\",  1  );
		 fileName.dirFlg  =  1;  
	 }
	 //  E5 : 被删除文件名
 	 memset(  tmpChar,  0xE5,  1  );
	 if  (  !(  strnicmp(  buf,  tmpChar,  1  )  &&  strnicmp(  buf,  tmpChar,  1  )  )  ) {
		 fileName.delFlg	=  1;		//  noUse
		 memset(  buf,  '?',  1  );
		 printf(  " %s ,  已删除  \n",  buf  );
	 }
	 else    printf(  " %s  \n",  buf  );

	 iRet  =   0;
errLabel:
	 return  iRet;
}


/*   2004-2-2  备份
 void main( int argc, char *argv[], char *envp[] )
{
      //  HANDLE					hFile  =  NULL;
	  HANDLE					hDrive =  NULL;
	  //  DWORD						numberOfBytesRead;
	  LPBYTE					lpSector  =  NULL;
	  LONG						dwSize  =  0;   //  = 2 * dgDisk.BytesPerSector;  // 2 sectors
	  unsigned	char			recvBuf[4096]=  "";
	  int						i  =  0;
	  LONG						basic;

	  memset(  &fileName,  0,  sizeof(  fileName )  );
	  //  Disk file that will hold the disk sector data.
	  //  hFile = CreateFile (  "disk.dak",  GENERIC_WRITE,  0,  NULL,  CREATE_ALWAYS,  FILE_ATTRIBUTE_NORMAL, NULL  );
	  hDrive = CreateFile(	"\\\\.\\g:",
					   GENERIC_READ,   FILE_SHARE_READ | FILE_SHARE_WRITE,  NULL,  OPEN_EXISTING,
					   0,  NULL  );

	  /*  
	  if (  (  hDrive == INVALID_HANDLE_VALUE  )  
		  ||  (  hFile  ==  INVALID_HANDLE_VALUE  )  )  goto  errLabel;  //  ErrorOpeningFile();
		// 
	  if (  hDrive == INVALID_HANDLE_VALUE  )  goto  errLabel;  //  ErrorOpeningFile();

      //  GetSupportedGeometrys( hDrive );

      //  printf( "\nDrive supports the following disk geometries\n" );  printf("\n");
      //  PrintGeometry( &dgDisk );  printf("\n");

	  getBootBPB(  hDrive  );
	  getRootEntry(  hDrive,  0  );
	  basic  =  boot.bytesPerSector  *  (  boot.reservedSectors + boot.sectorsPerFAT * boot.numberOfFATs  );

	  //  读取RootDir
	  for  (  i = 0; i <= ( CONST_sectorsForRootDir/2 ); i++  )  {
		  readSectors(  hDrive,  basic + i*2,  boot.bytesPerSector*2,  recvBuf  );

		  lpSector  =  recvBuf;
		  dwSize = 2 * boot.bytesPerSector;  // 2 sectors
 		  printf(  "  第 %d 次  output  is : \n  ",  i  );

		  for  (  ; dwSize >=  32 ;  )  {
			  getRootDirEntryFAT16(  lpSector,  &fileName  );

			  if  (  fileName.endFlg  )  goto  errLabel;
			  if  (  fileName.longFlg  )  {
				  lpSector  =  lpSector  +  64;
				  dwSize  =  dwSize - 64;
				  fileName.longFlg  =  0;
			  }
			  else	{
				  lpSector  =  lpSector  +  32;
				  dwSize  =  dwSize - 32;
			  }
	  	  }
	  }

	  //  CloseHandle(  hFile  );	  hFile  =  NULL;
	  CloseHandle(  hDrive );	  hDrive  =  NULL;

errLabel:
	  //  if  (  hFile  )CloseHandle(  hFile  );
	  if  (  hDrive  )CloseHandle(  hDrive );
	  return;
}
*/