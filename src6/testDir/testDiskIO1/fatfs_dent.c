/*
** fatfs_dent
** The @stake Sleuth Kit (TASK)
**
** Human interface Layer support for the FAT file system
**
** Brian Carrier [carrier@atstake.com]
** Copyright (c) 2002 Brian Carrier, @stake Inc.  All rights reserved
**
*/

//  #include "fs_tools.h"
#include "fatfs.h"
#include "mymalloc.h"
#include "error.h"


/*
 * DESIGN NOTES
 *
 * the basic goal of this code is to parse directory entry structures for
 * file names.  The main function is fatfs_dent_walk, which takes an
 * inode value, reads in the contents of the directory into a buffer, 
 * and the processes the buffer.  
 *
 * The buffer is processed in directory entry size chunks and if the
 * entry meets tne flag requirements, an action function is called.
 *
 * One of the odd aspects of this code is that the 'inode' values are
 * the 'slot-address'.  Refer to the document on how FAT was implemented
 * for more details. This means that we need to search for the actual
 * 'inode' address for the '.' and '..' entries though!  The search
 * for '..' is quite painful if this code is called from a random 
 * location.  It does save what the parent is though, so the search
 * only has to be done once per session.
 */ 

/* Recursive path stuff */
static unsigned int depth = 0;  /* how deep in the directory tree are we */
#define MAX_DEPTH   64
static char *didx[MAX_DEPTH];  /* pointer in dirs string to where '/' is for
                        ** given depth */
#define DIR_STRSZ   2048
static char dirs[DIR_STRSZ];    /* The current directory name string */


/* as FAT does not use inode numbers, we are making them up.  This causes
 * minor problems with the . and .. entries.  These global variables help
 * us out with that
 */
static u_int32_t	p_inode = 0;	/* the . inode */
static u_int32_t	pp_inode = 0;	/* the .. inode */
static DADDR_T		pp_clust_tofind;		/* the first cluster that .. uses */

/* when set to 1, save data such as parent inodes and directory paths
 * in the global variables.  When set to 0 do not.  It is set to 0
 * when we have to do a search for the inode of '..' and we are doing
 * a dent_walk within a dent_walk.  
 *
 * Yes, I know this is a poor design 
 */
static u_int8_t		save_state = 1;		


/*
 * Copy the contents of the FAT specific directory entry into the generic
 * one.
 *
 * This gets interesting with the way that FAT handles long file names.
 * LFN are handled by proceeding the original 8.3 entry with special
 * structures that handle 13 UNICODE values.  These have a special 
 * attribute set.  The LFN structures are in reverse order and end with
 * an 8.3 entry with the short version of the name.
 *
 * We handle this by copying the LFN values into the FATFS_INFO structure
 * and then when we get the 8.3 entry the long name is copied in.  Therefore,
 * FATFS_INFO keeps state between calls to this function.
 *
 */
//  static 
 void  fatfs_dent_copy(FATFS_INFO *fatfs, char *fatfs_dent, FS_DENT *fs_dent, 
   INUM_T inum) 
{
	FS_INFO *fs = &(fatfs->fs_info);
	int i;

	wchar_t  *  wBuf = L"\0";
	wchar_t  *  p1  =  NULL;		//  added by wqh
	wchar_t  *  p2  =  NULL;
	wchar_t		wNameBuf[sizeof(  WCHAR  )  *  FATFS_MAXNAMLEN]	=	L"";
	int			wNameBufLen;
	
	fatfs_dentry 		*dir = (fatfs_dentry *)fatfs_dent;
	fatfs_dentry_lfn 	*dirl = (fatfs_dentry_lfn *)fatfs_dent;

	fs_dent->inode = inum;
	fs_dent->reclen = fs_dent->nextLink = sizeof(fatfs_dentry);

	/* Name */
	if ((dir->attrib & FATFS_ATTR_LFN) == FATFS_ATTR_LFN) {
		/* Store the name in FATFS until we get the 8.3 name */

		/* Is this a new sequence?  The checksum is the same for all entries
		 * in the same sequence 
		 */
		if (dirl->chksum != fatfs->lfn_chk) { 
			fatfs->lfn_seq = dirl->seq;
			fatfs->lfn_chk = dirl->chksum;
			fatfs->lfn_len = 0;
		}

		if  (  gnDent  ==  2232  )  {
			traceLogA(  "here"  );
		}

		/* we are only going to support ASCII - not full UNICODE */	
		/*  2004/01/21, 修改lfn为存放Unicode,	以下修改by wqh  */
		p1  =  (  wchar_t  *  )dirl->part3;  
		p1 += 1;
		p2  =  (  wchar_t  *  )fatfs->lfn  +  fatfs->lfn_len; 
		for (i = 2; i >=0; i-=2) {
			if (  (*p1 != 0) && (  *p1 != 0xffff)) {
				if (fatfs->lfn_len < FATFS_MAXNAMLEN)  
					_snwprintf(  p2,  sizeof( char ),  p1  );
				fatfs->lfn_len ++;	p2  ++;
			}
			p1--;  
		}
		p1  =  (  wchar_t  *  )dirl->part2;  
		p1 += 5;
		for (i = 10; i >= 0 ; i-=2) {
			if ( (  *p1 != 0  ) && (  *p1 != 0xffff  ) ) {
				if (fatfs->lfn_len < FATFS_MAXNAMLEN)
					_snwprintf(  p2,  sizeof( char ),  p1  );
				//  traceLogA(  "%S, ",  (  wchar_t  *  )fatfs->lfn  );
				fatfs->lfn_len ++;	p2  ++;
			}
			p1--;  
		}

		p1  =  (  wchar_t  *  )dirl->part1;
		p1  += 4;
		for (i = 8; i >= 0; i-=2) {
			if ( ( *p1 != 0 ) && ( *p1 != 0xffff ) ) {
				if (fatfs->lfn_len < FATFS_MAXNAMLEN)
					_snwprintf(  p2,  sizeof(  char ),  p1  );
				//  traceLogA(  "%S,  ",  (  wchar_t  *  )fatfs->lfn  );
				fatfs->lfn_len ++;	p2  ++;
			}
			p1--;  
		}
	}

	else  { /* we have a short (8.3) entry 
			 * we may have the long name version already stored in the FATFS_INFO  */

		fs_dent->namlen = 0;

		if  (  gnDent  ==  2232  )  {
			traceLogA(  "here."  );
		}

		p1  =  (  wchar_t  *  )fs_dent->name;
		p2  =  (  wchar_t  *  )fatfs->lfn;  
		p2  +=  fatfs->lfn_len  - 1;
	
		/* if we have the lfn, copy it in.  Remember it is backwards */
		if (fatfs->lfn_len != 0) {
			for (i = 0; i < fatfs->lfn_len; i++) {
				_snwprintf(  p1,  sizeof(  char  ),  p2  );
				//  traceLogA(  "%S,  ",  (  wchar_t  *  )fs_dent->name  );
				fs_dent->namlen ++;
				p1 ++;   p2 --;	
			}
			_snwprintf(  p1,  sizeof(  wchar_t  ),  wBuf  );	
			//traceLogA(  "%S,  ",  (  wchar_t  *  )fs_dent->name  );
			
			//  将fs_dent->name中字符由Unicode编码改为mbcs编码
			memcpy(  (  char  *  )wNameBuf,  fs_dent->name,  sizeof(  wchar_t  ) * fs_dent->namlen  );
			wNameBuf[ fs_dent->namlen ]  =  0;
			wNameBufLen  =  WideCharToMultiByte(  CP_ACP,  0,  wNameBuf, -1, 0,  0,  NULL,  NULL  );
			if ( !WideCharToMultiByte(  CP_ACP,  0,  wNameBuf, -1, fs_dent->name, wNameBufLen,  NULL,  NULL  ) )  goto  errLabel;
			fs_dent->namlen  =  strlen(  fs_dent->name  );
						
			//  traceLogA(  "%S,  ",  wNameBuf  );
			//  traceLogA(  "%s,  ",  fs_dent->name  );
				
			p1 ++;

			/* we will have the short name appended as (xxxxxxx.xxx) */
			if (fs_dent->namlen + 2 < FATFS_MAXNAMLEN) {
				fs_dent->name[fs_dent->namlen++] = ' ';	
				fs_dent->name[fs_dent->namlen++] = '(';	
			}

		}

		if (fs_dent->namlen + 12 < FATFS_MAXNAMLEN) {
			/* copy in the short name, skipping spaces and putting in the . */
			for (i = 0 ; i < 8; i++) {
				if ((dir->name[i] != 0) && (dir->name[i] != 0xff) &&
				  (dir->name[i] != 0x20)) {

					if ((i == 0) && (dir->name[0] == FATFS_SLOT_DELETED))
						fs_dent->name[fs_dent->namlen++] = '_';
        			else if ((dir->lowercase & FATFS_CASE_LOWER_BASE) &&
				  	  (dir->name[i] >= 'A') && (dir->name[i] <= 'Z'))
						  fs_dent->name[fs_dent->namlen++] = dir->name[i] + 32;
					else
						fs_dent->name[fs_dent->namlen++] = dir->name[i];
				}

			}

			for (i = 0; i < 3; i++) {
				if ((dir->ext[i] != 0) && (dir->ext[i] != 0xff) &&
				  (dir->ext[i] != 0x20)) {
					if (i == 0)
						fs_dent->name[fs_dent->namlen++] = '.';
        			if ((dir->lowercase & FATFS_CASE_LOWER_EXT) &&
				  	  (dir->ext[i] >= 'A') && (dir->ext[i] <= 'Z'))
						  fs_dent->name[fs_dent->namlen++] = dir->ext[i] + 32;
					else
						fs_dent->name[fs_dent->namlen++] = dir->ext[i];
				}
			}
			fs_dent->name[fs_dent->namlen] = '\0';	
		}

		/* If we put the LFN and the short in () then add )*/
		if (fatfs->lfn_len != 0) {
			if (fs_dent->namlen + 1 < FATFS_MAXNAMLEN) 
				fs_dent->name[fs_dent->namlen++] = ')';	
			fs_dent->name[fs_dent->namlen] = '\0';	

			/* reset the stored length */
			fatfs->lfn_len = 0;
		}
	    
	}


	/* append the path data */
	fs_dent->path = dirs;
	fs_dent->pathdepth = depth;


	/* file type: FAT only knows DIR and FILE */
	if ((dir->attrib & FATFS_ATTR_DIRECTORY) == FATFS_ATTR_DIRECTORY)
		fs_dent->ent_type = FS_DENT_DIR;
	else
		fs_dent->ent_type = FS_DENT_REG;
errLabel:
	if (fs_dent->fsi) {
		free(fs_dent->fsi);
		fs_dent->fsi = NULL;
	}

	/* Get inode */
	if ((fs != NULL) && (inum))  
		fs_dent->fsi = fs->inode_lookup(fs, inum);

	return;
}


/**************************************************************************
 *
 * find_parent
 *
 *************************************************************************/

/*
 * this is the call back for the dent walk when we need to find the 
 * parent directory
 *
 * save_state should be 0 when this is running
 */
static u_int8_t
find_parent_act(FS_INFO *fs, FS_DENT *fsd, int flags, char *ptr)
{
	/* we found the entry that points to the requested clustor */
	if (fsd->fsi->direct_addr[0] == pp_clust_tofind) {
		pp_inode = fsd->inode;
		return WALK_STOP;
	}
	return WALK_CONT;
}

/*
 * this function will find the parent inode of a given directory
 * as specified in fs_dent
 *
 * Set save_state to 0, so that no global variables are overwritten.  I do
 * not like the design of this, but this is much more efficient than
 * an inode walk
 *
 * return the inode
 */
static u_int32_t
find_parent (FATFS_INFO *fatfs, FS_DENT *fs_dent) 
{
	FS_INFO *fs = (FS_INFO *)&fatfs->fs_info;	

	if (save_state == 0)  goto  errLabel;
		//  error ("save_state is already 0, recursion?");

	pp_inode = 0;

	/* set the global value that the action function will use */
	pp_clust_tofind = fs_dent->fsi->direct_addr[0];

	/* is the root directory being called for? 
	 * we won't find it by searching as it does not exist
	 */
	if (fs->ftype == MS32_FAT) {
		OFF_T clust = 2 + (fatfs->rootsect - fatfs->firstclustsect) / 
		  fatfs->csize;	
		if ((clust == pp_clust_tofind) || (pp_clust_tofind == 0)) {
			pp_inode = fs->root_inum;
			return pp_inode;
		}
	}	
	else {
		if ((pp_clust_tofind == 1) || (pp_clust_tofind == 0)) {
			pp_inode = fs->root_inum;
			return pp_inode;
		}
	}

	if ((fs_dent->fsi->mode & FS_INODE_FMT) != FS_INODE_DIR) {
		//  remark ("find_parent called on a non-directory");
		return 2;
	}


	/* walk the inodes - looking for an inode that has allocated the
	 * same first sector 
	 */
	save_state = 0;
	fatfs_dent_walk(fs, fs->first_inum, FS_FLAG_ALLOC | FS_FLAG_RECURSE,
		find_parent_act, "find_parent");
	save_state = 1;

errLabel:
	/* if we didn't find anything then 0 will be returned */
	return pp_inode;
}

/* 
**
** Read contents of directory sector (in buf) with length len and
** original address of addr.  
**
** The length read is returned or 0 if the action wanted to stop.  
**
** flags: FS_FLAG_ALLOC, FS_FLAG_RECURSE
*/
//  static 
 int  fatfs_dent_parse_block(FATFS_INFO *fatfs, char *buf, int len, DADDR_T addr, 
			int flags, FS_DENT_WALK_FN action, char *ptr) 
{
	int 		idx;
	u_int32_t 	inode, ibase;
	fatfs_dentry	*dep;
	FS_DENT 	*fs_dent;
	FS_INFO 	*fs = (FS_INFO *)&fatfs->fs_info;

	fs_dent = fs_dent_alloc( sizeof( WCHAR ) * FATFS_MAXNAMLEN );

	dep = (fatfs_dentry *)buf;

	/* Get the base inode for this sector */
	ibase = FATFS_SECT_2_INODE(fatfs, addr);
	if (ibase > fs->last_inum)  goto  errLabel;
		//  error("parse error: inode is too large");

	/* cycle through the entries */
	for (idx = 0; (  unsigned  int  )idx < fatfs->dentry_cnt_se; idx++, dep++)  {

			int myflags = 0;

			/* is it a valid dentry? */
			if (0 == fatfs_isdentry(fatfs, dep))
				continue;

			/* if a volume label, then skip it */
			if (((dep->attrib & FATFS_ATTR_VOLUME) == FATFS_ATTR_VOLUME) &&
			   ((dep->attrib & FATFS_ATTR_LFN) != FATFS_ATTR_LFN))
				continue;

			inode = ibase + idx;


			/* Copy the entry
			 * if this is LFN, then all that will happen is that it will
			 * be copied into FATFS_INFO 
			 */
			fatfs_dent_copy(fatfs, (char *)dep, fs_dent, inode);


			/* If it is a long file name, then keep on going until the
			 * final small name is reached */
			if ((dep->attrib & FATFS_ATTR_LFN) == FATFS_ATTR_LFN) 
				continue;

			/* Handle the . and .. entries specially
			 * The current inode 'address' they have is for the current
			 * slot in the cluster, but it needs to refer to the original
			 * slot 
			 */
			if (dep->name[0] == '.') {

				/* p_inode is always set and we can copy it in */
				if (dep->name[1] == ' ') 
					inode = fs_dent->inode = p_inode;

				/* pp_inode is not always set, so we may have to search */
				else if (dep->name[1] == '.') {
					/* save_state is set to 0 when we are already looking
					 * for a parent */
					if ((!pp_inode) && (save_state))
						pp_inode = find_parent(fatfs, fs_dent);

					inode = fs_dent->inode = pp_inode;

					/* If the parent is the root, the data is invalid
					 * so make it up
					 */
					if (inode == fs->root_inum) 
						fatfs_make_root(fatfs, fs_dent->fsi);
				}
			}

			
			/* Do we have a deleted entry? */
			myflags = (dep->name[0] == FATFS_SLOT_DELETED)?
			  FS_FLAG_UNALLOC : FS_FLAG_ALLOC;

			if ((flags & myflags) == myflags) {
				if (WALK_STOP == action(fs, fs_dent, myflags, ptr)) {
					fs_dent_free(fs_dent);
					return 0;
				}
			}


			/* if we have an allocated entry and we need to recurse,
			 * then do it 
			 */
            if ((myflags & FS_FLAG_ALLOC) &&
              (flags & FS_FLAG_RECURSE)  &&
              (!ISDOT(fs_dent->name)) &&
              ((fs_dent->fsi->mode & FS_INODE_FMT) == FS_INODE_DIR)) {

				u_int32_t back_p = 0;

				/* we are going to append only the short name */
                if ((save_state) && (depth < MAX_DEPTH)) {
					char tmpname[13];
					
					if ((strlen(fs_dent->name) > 12) || 
					  (strrchr(fs_dent->name, '('))) {
						int i;
						char *ptr;

						ptr = strrchr (fs_dent->name, '(');
						ptr++;

						for (i = 0; i < 12 && ptr[i] != ')'; i++) 
							tmpname[i] = ptr[i];
					
						tmpname[i] = '\0';

					}
					else {
						strncpy (tmpname, fs_dent->name, 13);
					}

                    didx[depth] = &dirs[strlen(dirs)];
					strncpy(didx[depth], tmpname, DIR_STRSZ - strlen(dirs));
					strncat(dirs, "/", DIR_STRSZ);
				}

				/* save the .. inode value */
				if (save_state) {
					back_p = pp_inode;
					pp_inode = p_inode;
					depth++;
				}

				fatfs_dent_walk(&(fatfs->fs_info), fs_dent->inode, 
				  flags, action, ptr);

				if (save_state) {
					depth--;
					p_inode = pp_inode;
					pp_inode = back_p; 
				}

				if ((save_state) && (depth < MAX_DEPTH))
					 *didx[depth] = '\0';

        	} /* end of recurse */

	} /* end for dentries */


errLabel:
	fs_dent_free(fs_dent);
	return len;

} /* end fatfs_dent_parse_block() */



/**************************************************************************
 *
 * dent_walk
 *
 *************************************************************************/

/* values used to copy the directory contents into a buffer */
static char *curdirptr = NULL;
static int dirleft = 0;
static DADDR_T *curaddrbuf = NULL;
static int addralloc = 0;
static int addridx = 0;
#define DENT_ADDR_INC 512

static u_int8_t 
fatfs_dent_action(FS_INFO *fs, DADDR_T addr, char *buf, int size,
  int flags, char *ptr)
{       
	/* how much are we copying */
    int len = (dirleft < size) ? dirleft : size;
    memcpy (curdirptr, buf, len);
    curdirptr = (char *) ((int)curdirptr + len);
    dirleft -= len;

	/* fill in the stack of addresses of sectors 
	 *
	 * if we are at the end of our buffer, realloc more */
	if (addridx == addralloc) {
		addralloc += DENT_ADDR_INC;
		curaddrbuf = (DADDR_T *)myrealloc ((char *)curaddrbuf, 
		  addralloc * sizeof(DADDR_T));
	}

	curaddrbuf[addridx++] = addr;

    if (dirleft)
        return WALK_CONT;
    else   
        return WALK_STOP;
}


/* 
** The main function to do directory entry walking
**
** action is called for each entry with flags set to FS_FLAG_ALLOC for
** active entries
**
** Use the following flags: FS_FLAG_ALLOC, FS_FLAG_UNALLOC, FS_FLAG_RECURSE
*/
void fatfs_dent_walk(FS_INFO *fs, INUM_T inode, int flags, 
  FS_DENT_WALK_FN action, char *ptr) 
{
	OFF_T size;
	FS_INODE *fs_inode;
	FATFS_INFO	*fatfs = (FATFS_INFO *)fs;
	char *dirbuf, *dirptr;
	DADDR_T *addrbuf;
	int addrmax;
	int i;

	if ((inode < fs->first_inum) || (inode > fs->last_inum))  goto  errLabel;
		//  error("invalid inode value: %i\n", inode);

	fs_inode = fs->inode_lookup(fs, inode);
	if (!fs_inode)  goto  errLabel;
		//  error ("not an inode");
		
	size = fs_inode->size;

	/* If we are saving state, save the current inode value ('.') */
	if (save_state)
		p_inode = inode;

	/* Allocate a buffer for the lfn support */
	if (fatfs->lfn == NULL) {
		fatfs->lfn = mymalloc(  sizeof(  WCHAR  )  *  FATFS_MAXNAMLEN  );		//  2004/02/21，由于改为在里面存储Unicode，故*2
		fatfs->lfn_len = 0;
		fatfs->lfn_chk = 0;
		fatfs->lfn_seq = 0;
	}

    /* make a copy of the directory contents that we can process */
    if (curdirptr != NULL)  goto  errLabel;
        //  error ("fatfs_dent_walk: Curdirptr is set! recursive?");

    if (curaddrbuf != NULL)  goto  errLabel;
        //  error ("fatfs_dent_walk: Curaddrbuf is set! recursive?");

	/* make a buffer for the directory */
    curdirptr = dirbuf = mymalloc(size);
    dirleft = size;

	/* make a stack of addresses */
	addralloc = DENT_ADDR_INC;
    curaddrbuf = addrbuf = (DADDR_T *)mymalloc(addralloc * sizeof(DADDR_T));
	addridx = 0;
  
	/* save the directory contents into dirbuf */
    fs->file_walk(fs, fs_inode, 0, 0,
      FS_FLAG_CONT | FS_FLAG_ALLOC | FS_FLAG_SLACK, fatfs_dent_action, "");

	addrmax = addridx;
	/* the pointer could have moved due to a realloc */
	addrbuf = curaddrbuf;

    curdirptr = NULL;
 	curaddrbuf = NULL;
    dirptr = dirbuf;

	/* cycle through the directory and parse the contents */
	for (i = 0; size > 0; i++) {
        int len = (fatfs->ssize < size) ? fatfs->ssize : size;
		int retval;

		if (addrbuf[i] > fs->last_block)  goto  errLabel;
			//  error ("fatfs_dent_walk: block too large");

		retval = fatfs_dent_parse_block(fatfs, dirptr, len, addrbuf[i], flags,
          action, ptr);

		/* zero is returned when the action wanted to stop */
		if (retval)
			size -= retval;
		else
			break;

		if (len != retval)  goto  errLabel;
			//  error ("hmm, funky return");

        dirptr = (char *)((int)dirptr + len);
    }

errLabel:
	free (dirbuf);
	free(addrbuf);
}

