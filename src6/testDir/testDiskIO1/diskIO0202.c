#include "fs_tools.h"
#include "error.h"

#include "ntfs.h"
#include	"diskIO.h"

//#include	"fatfs.h"

/* Time skew of the system in seconds */
static int32_t sec_skew = 0;


void usage(char *myProg) {
	printf("usage: %s [-adDFlpruvV] [-f fstype] [-m dir/] [-z ZONE] [-s seconds] image [inode]\n", 
	  myProg);
    printf("\tIf [inode] is not given, the root directory is used\n");
	printf("\t-a: Display \".\" and \"..\" entries\n");
	printf("\t-d: Display deleted entries only\n");
	printf("\t-D: Display directory entries only\n");
	printf("\t-F: Display file entries only (NOTE: This was -f in TCTUTILs)\n");
	printf("\t-l: Display long version (like ls -l)\n");
	printf("\t-m: Display output in mactime input format with\n");
	printf("\t      dir/ as the actual mount point of the image\n");
	printf("\t-p: Display full path for each file\n");
	printf("\t-r: Recurse on directory entries\n");
	printf("\t-u: Display undeleted entries only\n");
	printf("\t-v: verbose output to stderr\n");
	printf("\t-V: Print version\n");
	printf("\t-z: Time zone of original machine (i.e. EST5EDT or GMT) (only useful with -l)\n");
	printf("\t-s seconds: Time skew of original machine (in seconds) (only useful with -l & -m)\n");
    printf("\t-f fstype: Image file system type\n");
	printf("Supported file system types:\n");
	fs_print_types();

	exit(1);
}


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
static void
printit (FS_INFO *fs, FS_DENT *fs_dent, int flags, FS_DATA *fs_data)
{
	unsigned int i;

	if (!(localFlags & LCL_FULL)) {
		for (i=0; i<fs_dent->pathdepth;i++) 
			//  fprintf(stdout, "+");
			traceLogA(  "+"  );

		if (fs_dent->pathdepth)
			//  fprintf(stdout, " ");
			traceLogA(  " "  );
	}


	if (localFlags & LCL_MAC) {
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

		if (LCL_FULL & localFlags) 
			fs_dent_print_long(stdout, fs_dent, flags, fs, fs_data);
		else {
			char *tmpptr = fs_dent->path;
			fs_dent->path = NULL;
			fs_dent_print_long(stdout, fs_dent, flags, fs, fs_data);
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
}



/* 
 * call back action function for dent_walk
 */
static u_int8_t
print_dent (FS_INFO *fs, FS_DENT *fs_dent, int flags, char *ptr) 
{

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
					if (!((ISDOT (fs_dent->name) ) && 
					  ((localFlags & LCL_DOT) == 0)))
						printit(fs, fs_dent, flags, fs_data);
				}

				fs_data = fs_data->next;
			}

		}
		else {
			/* skip it if it is . or .. and we don't want them */
			if (!((ISDOT (fs_dent->name) ) && ((localFlags & LCL_DOT) == 0)))
				printit(fs, fs_dent, flags, NULL);
		}
	}
	return WALK_CONT;
}



 int  main(int argc, char **argv) 
{
	char	*	fstype  =  "ntfs";			//  1/2暂时，等ntfs; fat16;fat32,
	//	int inode;
	int			flags	=	FS_FLAG_ALLOC | FS_FLAG_UNALLOC;
	//	char ch;
	FS_INFO *	fs		=	NULL;
	BOOL		bFsOpen	=	FALSE;
	//	extern int optind;

	progname = argv[0];

	localFlags =  LCL_DIR | LCL_FILE;

	/*
	while ((ch = getopt(argc, argv, "adDf:Fm:lprs:uvVz:")) > 0) {
		switch (ch) {
		case '?':
		default: 
			usage(argv[0]);
		case 'a':
			localFlags |= LCL_DOT;
			break;
		case 'd':
			flags &= ~FS_FLAG_ALLOC;
			break;
		case 'D':
			localFlags &= ~LCL_FILE;
			localFlags |= LCL_DIR;
			break;
        case 'f':
            fstype = optarg;
            break;
		case 'F':
			localFlags &= ~LCL_DIR;
			localFlags |= LCL_FILE;
			break;
		case 'l':
			localFlags |= LCL_LONG;
			break;
		case 'm':
			localFlags |= LCL_MAC;
			macpre = optarg;
			break;
		case 'p':
			localFlags |= LCL_FULL;
			break;
		case 'r':
			flags |= FS_FLAG_RECURSE;
			break;
		case 's':
			sec_skew = atoi(optarg);
			break;
		case 'u':
			flags &= ~FS_FLAG_UNALLOC;
			break;
		case 'v':
			verbose++;
			logfp = stderr;
			break;
		case 'V':
			print_version();
			exit(0);
		case 'z':
            {
            char envstr[32];
            snprintf(envstr, 32, "TZ=%s", optarg);
            if (0 != putenv(envstr)) {
                    error ("error setting environment");
            }

            /* we should be checking this somehow 
            tzset();
            }
            break;

		}
	}

	/* only the image and optional inode are left 
	if ((optind == argc) || ((optind+2) < argc))
		usage(argv[0]);


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
//	fs = fs_open(argv[optind++], fstype);
	fs = fs_open("\\\\.\\I:", fstype);			//  2/2  g:fat16,d/h/I:ntfs, c:fat32
	if  (  !fs ||  fs->fd  ==  (  HANDLE  )-1  )  {
		traceLogA(  "文件系统不能打开"  );  goto  errLabel;
	}
	bFsOpen  =  TRUE;

	/* was the inode given?  - we already did the bounds checks above /
	if (optind == argc)
		inode = fs->root_inum;
	else {
		if (strchr(argv[optind], '-') != NULL) 
			//  error ("Invalid inode (%s) type and id are not allowed", argv[optind]);  
			goto  errLabel;

		inode = atoi(argv[optind]);
	}
	*/


	/* begin walk */
//	fs->dent_walk(fs, inode, flags, print_dent, (char *)0); 
	fs->dent_walk(fs, fs->root_inum, flags, print_dent, (char *)0); 
	traceLogA(  "文件处理Exit!!!"  );

errLabel:

	if  (  bFsOpen  )  fs->close(fs);

	exit (0);
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