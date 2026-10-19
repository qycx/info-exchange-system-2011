

#include	"fs_tools.h"
#include	"error.h"
#include	"ntfs.h"
#include	"diskIO.h"

//#include	"fatfs.h"

/* Time skew of the system in seconds */
static int32_t sec_skew = 0;




FILE *logfp;

/*directory prefix for printing mactime output */
static char *macpre = NULL;	

static int localFlags;

/* Local Flags */
#define LCL_DOT		0x001
#define LCL_LONG	0x002
#define LCL_FILE	0x004
#define LCL_DIR		0x008
#define LCL_FULL	0x010
#define LCL_MAC		0x020


/* this is a wrapper type function that takes care of the runtime
 * flags
 * 
 * fs_data should be set to NULL for all NTFS file systems
 */
 int  printit(  FS_INFO  *  fs,  FS_DENT  *  fs_dent,  int  flags,  FS_DATA  *  fs_data  )
{
	int				iRet						=	CONST_qyRet_err;
	unsigned  int	i;

	if  (  !(  localFlags  &  LCL_FULL  )  )  {
		for  (  i  =  0;  i  <  fs_dent->pathdepth;  i  ++  )  traceLogA(  "+"  );
		if  (  fs_dent->pathdepth  )  traceLogA(  " "  );
	}

	if  (  localFlags  &  LCL_MAC  )  {
		if (sec_skew != 0) {
			fs_dent->fsi->mtime -= sec_skew;
			fs_dent->fsi->atime -= sec_skew;
			fs_dent->fsi->ctime -= sec_skew;
		}

		fs_dent_print_mac(stdout, fs_dent, flags, fs, fs_data, macpre);

		if (sec_skew != 0) {
			fs_dent->fsi->mtime += sec_skew;
			fs_dent->fsi->atime += sec_skew;
			fs_dent->fsi->ctime += sec_skew;
		}
		
		}
	else if (localFlags & LCL_LONG) {
		if (sec_skew != 0) {
			fs_dent->fsi->mtime -= sec_skew;
			fs_dent->fsi->atime -= sec_skew;
			fs_dent->fsi->ctime -= sec_skew;
		}

		if  (  LCL_FULL  &  localFlags  ) 
			iRet  =  fs_dent_print_long(stdout, fs_dent, flags, fs, fs_data);
		else  {
			  char *tmpptr = fs_dent->path;
			
			  fs_dent->path = NULL;
			  iRet  =  fs_dent_print_long(stdout, fs_dent, flags, fs, fs_data);
			  fs_dent->path = tmpptr;
		}

		if (sec_skew != 0) {
			fs_dent->fsi->mtime += sec_skew;
			fs_dent->fsi->atime += sec_skew;
			fs_dent->fsi->ctime += sec_skew;
		}
		}
	else {
		if (LCL_FULL & localFlags) 
			fs_dent_print(stdout, fs_dent, flags, fs, fs_data);
		else {
			char *tmpptr = fs_dent->path;
			fs_dent->path = NULL;
			fs_dent_print(stdout, fs_dent, flags, fs, fs_data);
			fs_dent->path = tmpptr;
			traceLogA(  "\t目录为：%s  ",  fs_dent->path  );
		}
		printf("\n");
	}
		
//  errLabel:

	return  iRet;

}



/* 
 * call back action function for dent_walk
 */
 int  print_dent(  FS_INFO  *  fs,  FS_DENT  *  fs_dent,  int  flags,  char  *  ptr  ) 
{
	int					iRet		=  CONST_qyRet_err;
	FSENTRY_PROCINFO	procInfo;

	memset(  &procInfo,  0,  sizeof(  procInfo  )  );
	iRet  =  procFsEntry0(  NULL,  fs_dent,  &procInfo  );
	if  (  iRet  !=  CONST_qyRet_ok  )  
		return  iRet;

	/* only print dirs if LCL_DIR is set and only print everything
	** else if LCL_FILE is set (or we aren't sure what it is)
	*/
    if ( ((localFlags & LCL_DIR) &&
         ((fs_dent->fsi) &&
         ((fs_dent->fsi->mode & FS_INODE_FMT) == FS_INODE_DIR))) ||
        ((localFlags & LCL_FILE) &&
         (((fs_dent->fsi) &&
         ((fs_dent->fsi->mode & FS_INODE_FMT) != FS_INODE_DIR)) ||
         (!fs_dent->fsi)))) {


		/* Make a special case for NTFS so we can identify all of the
		 * alternate data streams!
		 */
		if (((fs->ftype & FSMASK) == NTFS_TYPE) && (fs_dent->fsi)) {

			FS_DATA *fs_data = fs_dent->fsi->attr;

			while ((fs_data) && (fs_data->flags & FS_DATA_INUSE)) {

				if (fs_data->type == NTFS_ATYPE_DATA) {
					mode_t mode = fs_dent->fsi->mode; 
					u_int8_t ent_type = fs_dent->ent_type;


					/* 
					 * A directory can have a Data stream, in which
					 * case it would be printed with modes of a
					 * directory, although it is really a file
					 * So, to avoid confusion we will set the modes
					 * to a file so it is printed that way.  The
					 * entry for the directory itself will still be
					 * printed as a directory
					 */

					if ((fs_dent->fsi->mode & FS_INODE_FMT) == FS_INODE_DIR) {
						
						/* we don't want to print the ..:blah stream if
						 * the -a flag was not given
						 */
						if ((fs_dent->name[0] == '.') && (fs_dent->name[1])
						  && (fs_dent->name[2] == '\0') && 
					      ((localFlags & LCL_DOT) == 0)) {
							fs_data = fs_data->next;
							continue;
						}

						fs_dent->fsi->mode &= ~FS_INODE_FMT;	
						fs_dent->fsi->mode |= FS_INODE_REG;	
						fs_dent->ent_type = FS_DENT_REG;
					}
					
					printit(fs, fs_dent, flags, fs_data);

					fs_dent->fsi->mode = mode; 
					fs_dent->ent_type = ent_type;
				}
				else if (fs_data->type == NTFS_ATYPE_IDXROOT) {

					/* If it is . or .. only print it if the flags say so,
					 * we continue with other streams though in case the 
					 * directory has a data stream 
					 */
					if  (  !  (  (  ISDOT(  fs_dent->name  )  ) &&  (  (  localFlags  &  LCL_DOT  )  ==  0  )  )  )
						printit(fs, fs_dent, flags, fs_data);
				}

				fs_data = fs_data->next;
			}

		}
		else  {
			  /* skip it if it is . or .. and we don't want them */
			  if  (  !(  (  ISDOT(  fs_dent->name  )  )  &&  (  (  localFlags  &  LCL_DOT  )  ==  0  )  )  )
				  printit(fs, fs_dent, flags, NULL);
		}
	}
	
	return  WALK_CONT;
}

 int					diskNum;								//  磁盘个数
 DISKDRV_INFO			diskDrv[CONST_numOfAbcTable+1];
 char					charTable[CONST_numOfAbcTable+1]	=  "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
 //	char  *  fstype		=  "fat16";			//  1/2暂时，等ntfs; fat16;fat32,
 // char  *  drvName	=  "\\\\.\\f:"		//  2/2  g:fat16,d/h/I:ntfs, c:fat32
 int  chkFsMain(  char  *  drvName,  char  *  fstype  ) 
{
	int			flags	=	FS_FLAG_ALLOC | FS_FLAG_UNALLOC  |  FS_FLAG_RECURSE;
	//   int			flags	=	FS_FLAG_ALLOC | FS_FLAG_UNALLOC;
	FS_INFO *	fs		=	NULL;
	BOOL		bFsOpen	=	FALSE;
	
	//  localFlags =  LCL_DIR | LCL_FILE;
	localFlags  =  LCL_DIR  |  LCL_FILE  |  LCL_FULL  |  LCL_LONG;

	/*
	
	/* Set the full flag to print the full path name if recursion is
	** set and we are only displaying files or deleted files
	
	if ((flags & FS_FLAG_RECURSE) && (
	  ((flags & FS_FLAG_UNALLOC) && (!(flags & FS_FLAG_ALLOC))) ||
	  ((localFlags & LCL_FILE) && (!(localFlags & LCL_DIR))) )) {

		localFlags |= LCL_FULL;
	}

	/* set flag to save full path for mactimes style printing 
	if (localFlags & LCL_MAC) {
		localFlags |= LCL_FULL;
	}
*/
	/* we need to append a / to the end of the directory if
	 * one does not already exist
	 */
	if (macpre) {
		int len = strlen (macpre);
		if (macpre[len - 1] != '/') {
			char *tmp = macpre;
			macpre = (char *)malloc(len + 2);
			strncpy (macpre, tmp, len + 1);
			strncat (macpre, "/", len + 2);
		}
	}

	
	/* open image */
	//  fs = fs_open("\\\\.\\f:", fstype);			//  2/2  g:fat16,d/h/I:ntfs, c:fat32
	fs = fs_open(  drvName, fstype  );			//  2/2  g:fat16,d/h/I:ntfs, c:fat32
	if  (  !fs ||  fs->fd  ==  (  HANDLE  )-1  )  {
		traceLogA(  "文件系统\"%s\"不能打开",  drvName  );  goto  errLabel;
	}
	bFsOpen  =  TRUE;

	/* begin walk */
	fs->dent_walk(fs, fs->root_inum, flags, print_dent, (char *)0); 
	traceLogA(  "文件处理完毕!!!"  );

errLabel:

	if  (  bFsOpen  )  fs->close(fs);
	return  0;

}


 //  区别：软盘、光盘、硬盘、可移动磁盘
 int  getDiskDrvInfo(  )
{
	 int				iRet				=  -1;
	 DWORD				tmpBit;				
	 DWORD				i					=  0;
	 DWORD				bitmask				=  CONST_bitmask_diskC;

	 char		rootPathName[256]			=  "";
	 char		lpVolumeNameBuffer[64]		=  "";											//  address of name of the volume 
     DWORD		nVolumeNameSize				=  sizeof(  lpVolumeNameBuffer  );				//  length of lpVolumeNameBuffer 
     DWORD		VolumeSerialNumber;														//  address of volume serial number 
     DWORD		MaximumComponentLength;													//  address of system's maximum filename length
     DWORD		FileSystemFlags;														//  address of file system flags 
     char		lpFileSystemNameBuffer[64]  =  "";										//  address of name of file system 
     DWORD		nFileSystemNameSize			=  sizeof(  lpFileSystemNameBuffer  );		//  length of lpFileSystemNameBuffer 
	 
	 strcat(  rootPathName,  "c:\\"  );
	 memset(  &diskDrv,  0,  sizeof(  diskDrv  )  );
	 if  (  !(  tmpBit  =  GetLogicalDrives(  )  )  )  goto  errLabel;
	 for (  i = 2;  i < CONST_numOfAbcTable;  i ++  )  {			//  抛开A:,B:两种情况
		 if  (  bitmask  &  tmpBit  )  {
			 strncpy(  rootPathName,  charTable  +  i,  1  );
			 if  (  GetVolumeInformation(	rootPathName,  
										lpVolumeNameBuffer,  
										nVolumeNameSize,
      			 						&VolumeSerialNumber,  
										&MaximumComponentLength,
			 							&FileSystemFlags,
	      								lpFileSystemNameBuffer,  
										nFileSystemNameSize  )  )  
			 {
				 if  (  !_strnicmp(  lpFileSystemNameBuffer,  "CDFS",  strlen(  lpFileSystemNameBuffer  )  )  )    continue;
				 memcpy(  diskDrv[diskNum].type,  lpFileSystemNameBuffer,  strlen(  lpFileSystemNameBuffer  )  );
	 			 memcpy(  &diskDrv[diskNum].vol,  charTable  +  i,  1  );
			 }
			 else  {  traceLogA(  " The file system has no found !"  );  goto  errLabel;  }
			 traceLogA(  "The  diskName  is  [%c],  the file system is [%s]  ",  diskDrv[diskNum].vol,  (  char  *  )&diskDrv[diskNum].type  );
			 diskNum  ++;
		 }
		 else  break;
		 bitmask  =  bitmask << 1; 
	 }

	 iRet   =  0;
errLabel:
	 return  iRet;
}

 void  usage(  char  *  progName  )
{
	 printf(  "Usage: %s drvName fstype\n",  progName  );
	 printf(  "		 drvName: 盘符\n"  );
	 printf(  "		 fstype:	fat16或fat32或ntfs\n"  );
	 printf(  "Example: 处理文件系统格式为fat16的f盘\n"  );
	 printf(  "		--\n"  );
	 printf(  "		%s f fat16",  progName  );
	 return;
}

 int  main(int argc, char **argv) 
{
	char		drvName[128]  =  "";
	int			i;

	if  (  argc  !=  3  )  {
		usage(  argv[0]  );  return  -1;
	}
	if  (  strcmp(  argv[2],  "fat16"  )
		&&  strcmp(  argv[2],  "fat32"  )
			&&  strcmp(  argv[2],  "ntfs"  )  )
	{
		usage(  argv[0]  );  return  -1;
	}
	//  _snprintf(  drvName,  sizeof(  drvName  ),  "\\\\.\\%s:",  argv[1]  );

	getDiskDrvInfo(  );

	for (  i = 0;  i <=  diskNum;  i ++  )  {

		_snprintf(  drvName,  sizeof(  drvName  ),  "\\\\.\\%c:",  diskDrv[i].vol  );


		chkFsMain(  drvName,  diskDrv[i].type  );
	}
	
	return  0; 
}


#define  CONST_ProgramFiles					"Program Files"  
#define	 CONST_SystemVolumeInformation		"System Volume Information"
#define  CONST_dir_DocumentsandSettings		"Documents and Settings/"
#define  CONST_AllUsers						"All Users"
#define  CONST_DefaultUser					"Default User"
#define  CONST_Cookies						"Cookies"
 //  PF_commonHandler
 //  用于过滤一部分目录
 //
 //  返回	
 //			CONST_qyRet_ok			继续
 //			CONST_qyRet_skip		不处理子目录
 //			CONST_qyRet_err或其他	停止处理
 //				
 int  procFsEntry0(  LPVOID  p0,  LPVOID  p1,  LPVOID  p2  )
{
	 int			iRet		=	CONST_qyRet_err;
	 //  p0  用于全局环境变量
	 FS_DENT			*	fs_dent		=	p1;
	 FSENTRY_PROCINFO	*	pProcInfo	=	(  FSENTRY_PROCINFO  *  )p2;
	 FS_INODE			*	fs_inode	=	NULL;
	 BOOL					bFile		=	FALSE;
	 
	 if  (  !p1  )  goto  errLabel;
	 fs_inode  =  fs_dent->fsi;
	 if  (  fs_dent->name[0]  ==  '$'  ||  fs_dent->name[0]  ==  '.'  )  {
		 iRet  =  CONST_qyRet_skip;  goto  errLabel;
	 }
	 if  (  !fs_dent->path[0]  )  {		//  根目录下的过滤
		 if  (  !strcmpi(  fs_dent->name,  "WINNT"  )   //  暂时将winnt下的目录全部略去
			 ||  !strcmpi(  fs_dent->name,  "Inetpub"  )  
				||  !_strnicmp(  fs_dent->name,  CONST_ProgramFiles,  strlen(  CONST_ProgramFiles  )  )  
					||  !_strnicmp(  fs_dent->name,  CONST_SystemVolumeInformation,  strlen(  CONST_SystemVolumeInformation  )  )  )
		 {
			 iRet  =  CONST_qyRet_skip;  goto  errLabel;
		 }
	 }
	 if  (  !strcmpi(  fs_dent->path,  CONST_dir_DocumentsandSettings  )  )  {
		 if  (  !strcmpi(  fs_dent->name,  "All Users"  )  
			 ||  !strcmpi(  fs_dent->name,  "Default User"  )  )  
		 {
		 	 iRet  =  CONST_qyRet_skip;  goto  errLabel;
		 }
	 }
	 if  (  !strcmpi(  fs_dent->path,  "DOCUME~1/"  )  )  {
		 if  (  !_strnicmp(  fs_dent->name,  "Default User",  strlen(  "Default User"  )  )  
			 ||  !_strnicmp(  fs_dent->name,  "All Users",  strlen(  "All Users"  )  )  )
		 {
			 iRet  =  CONST_qyRet_skip;  goto  errLabel;
		 }
	 }
	 if  (  !strcmpi(  fs_dent->path,  "windows/"  )  )  {
		 if  (  _strnicmp(  fs_dent->name,  CONST_Cookies,  strlen(  CONST_Cookies  )  )  )  {		//  98下的cookie外的目录全部略去
			 iRet  =  CONST_qyRet_skip;  goto  errLabel;
		 }
	 }
	 	 	 
	 iRet  =  CONST_qyRet_ok;

errLabel:
	 
	 if  (  iRet  !=  CONST_qyRet_ok  )  traceLogA(  "序号%d: 路径为%s, 名字为%s, 返回%d",  gnDent,  fs_dent->path,  fs_dent->name,  iRet  );
	 if  (  gnDent  ==  15  )  {
		 iRet  =  iRet;
	 }
	 return  iRet;

}

 //  用于决定entry的打印等处理属性
 int  procFsEntry1(  LPVOID  p0,  LPVOID  p1,  LPVOID  p2  )
{
	 int			iRet		=	CONST_qyRet_err;
	 //  p0  用于全局环境变量
	 FS_DENT			*	fs_dent		=	p1;
	 FSENTRY_PROCINFO	*	pProcInfo	=	(  FSENTRY_PROCINFO  *  )p2;
	 FS_INODE			*	fs_inode	=	NULL;
	 BOOL					bFile		=	FALSE;
	 char				*	tmp0		=   NULL;
	 char				*   tmp1		=   NULL;	
	 int					len;
	 
	 if  (  !p1  )  goto  errLabel;
	 fs_inode  =  fs_dent->fsi;
	 
	 // type of file - based on dentry type 
	 if  (  (  fs_dent->ent_type  &  FS_DENT_MASK  )  <  FS_DENT_MAX_STR  )  {
		 //  traceLogA(  "\t基于dentry的类型 %s",  fs_dent_str[fs_dent->ent_type & FS_DENT_MASK]  );
		 if  (  fs_dent_str[fs_dent->ent_type & FS_DENT_MASK][0]  ==  'r'  )  bFile  =  TRUE;
		}
	 else
		 traceLogA(  "\t基于dentry的类型 (无)"  );

	 // type of file - based on inode type: we want letters though for
	 //  regular files so we use the dent_str though 
	 if  (  fs_inode  )  {
		 int typ = (fs_inode->mode & FS_INODE_FMT)>>FS_INODE_SHIFT;
		 if  (  (  typ  &  FS_INODE_MASK  )  <  FS_DENT_MAX_STR  )  {
			 //  traceLogA(  "\t基于inode的类型 %s", fs_dent_str[typ & FS_INODE_MASK]  );
			 if  (  fs_dent_str[typ & FS_INODE_MASK][0]  ==  'r'  )  bFile  =  TRUE;
			}
		 else
			 traceLogA(  "\t基于inode的类型 (无)"  );
		 }
	 else  traceLogA(  "\t无inode"  );

	 //	 需要获取的文件名后缀：ppt、doc、xls、eml、zip、txt、lnk、pdf、chm、mdb、log、htm、html
	 if  (  pProcInfo  &&  bFile  )  {
		 tmp0  =  fs_dent->name;
		 while  (  tmp0  )  {
			 if  (  !(tmp0  =  strchr(  tmp0,  '.'  )  )  )  break;
			 tmp1  =  tmp0  +  1;
			 tmp0  =  tmp1;
		 }  

		 len  =  strlen(  "ppt"  );

		 if  (  tmp1  )  {
			 if  (  !_strnicmp(  tmp1,  "ppt",  len  )  
				 ||  !_strnicmp(  tmp1,  "doc",  len  )
				   ||  !_strnicmp(  tmp1,  "xls",  len  ) 
				     ||  !_strnicmp(  tmp1,  "eml",  len  )  
				       ||  !_strnicmp(  tmp1,  "zip",  len  ) 
					     ||  !_strnicmp(  tmp1,  "txt",  len  )  
					       ||  !_strnicmp(  tmp1,  "pdf",  len  )  
						     ||  !_strnicmp(  tmp1,  "lnk",  len  )  
						       ||  !_strnicmp(  tmp1,  "chm",  len  )  
						         ||  !_strnicmp(  tmp1,  "log",  len  )  
								   ||  !_strnicmp(  tmp1,  "htm",  len  )  
							         ||  !_strnicmp(  tmp1,  "html",  len  )  )
			 pProcInfo->ucbPrint  =  TRUE;	 }
	 }

	 iRet  =  CONST_qyRet_ok;

errLabel:
	 
	 traceLogA(  "序号%d: 路径为%s, 名字为%s, 返回%d",  gnDent,  fs_dent->path,  fs_dent->name,  iRet  );
	 if  (  gnDent  ==  15  )  {
		 iRet  =  iRet;
	 }
	 return  iRet;

}


 //  2004-2-12 注释
 /*
void main( int argc, char *argv[], char *envp[] )
{
	fatfs_open(  "\\\\.\\G:",  MS16_FAT  );

//	fs->dent_walk(fs, inode, flags, print_dent, (char *)0); 

	return;
}



 //  2004-2-2 在testOld.c中建立备份
 /*
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
		  */
/*
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