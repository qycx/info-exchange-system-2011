/*
** ntfs_dent
** The @stake Sleuth Kit (TASK)
**
** name layer support for the NTFS file system
**
** Brian Carrier [carrier@atstake.com]
** Copyright (c) 2002 Brian Carrier, @stake Inc.  All rights reserved
**
*/
#include "fs_tools.h"
#include "fs_data.h"
#include "ntfs.h"

#include "mymalloc.h"
#include "error.h"


/* recursive path stuff */
static unsigned int depth = 0;  /* how deep in the directory tree are we */
#define MAX_DEPTH   64
static char *didx[MAX_DEPTH];  /* pointer in dirs string to where '/' is for
				** given depth */
#define DIR_STRSZ  2048 
static char dirs[DIR_STRSZ];    /* The current directory name string */


/* 
 * copy the index (directory) entry into the generic structure
 *
 * uses the global variables 'dirs' and 'depth'
 */
//static 
 void  ntfs_dent_copy(NTFS_INFO *ntfs, ntfs_idxentry *idxe, FS_DENT *fs_dent)
{

 	wchar_t  *  wBuf = L"\0";
	wchar_t		wNameBuf[sizeof(  WCHAR  )  *  NTFS_MAXNAMLEN]	=	L"";
	int			wNameBufLen;

	ntfs_attr_fname *fname = (ntfs_attr_fname *)&idxe->stream;
	FS_INFO *fs = (FS_INFO *)&ntfs->fs_info;

	fs_dent->inode = getu48(fs, idxe->file_ref);

	//  if  (  gnDent  ==  20  )  {
	//		traceLogA(  "here"  );
	//  }

	/* Copy the name */
	fs_dent->namlen = fname->nlen;
	
	/*traceLogA(  "%S",  ( wchar_t * )&fname->name  );
	_snwprintf(  (  wchar_t  * )fs_dent->name,  fname->nlen,  (  wchar_t  * )&fname->name  );
	//  uni2ascii((char *)&fname->name, fname->nlen, fs_dent->name, fs_dent->maxnamlen);
	//  (  (  wchar_t  *  )fs_dent->name  )[fs_dent->namlen]  =  0;
	(  (  wchar_t  *  )fs_dent->name  )[fname->nlen]  =  0;
	fs_dent->namlen  =  wcslen(  ( wchar_t * )fs_dent->name  );
	traceLogA(  " fs_dent->name  is  %S",  ( wchar_t  * )fs_dent->name  );
	*/
	//  将fs_dent->name中字符由Unicode编码改为mbcs编码
	memcpy(  (  char  *  )wNameBuf,  &fname->name,  sizeof(  wchar_t  ) * fname->nlen  );
	wNameBuf[ fname->nlen ]  =  0;
	wNameBufLen  =  WideCharToMultiByte(  CP_ACP,  0,  wNameBuf, -1, 0,  0,  NULL,  NULL  );
	WideCharToMultiByte(  CP_ACP,  0,  wNameBuf, -1, fs_dent->name, wNameBufLen,  NULL,  NULL  );
	fs_dent->namlen  =  strlen(  fs_dent->name  );
	//  traceLogA(  "%s",  fs_dent->name  );
	
	/* copy the path data */
	fs_dent->path = dirs;
	fs_dent->pathdepth = depth;

	/* Get the actual inode */
	if (fs_dent->fsi != NULL)
		fs_inode_free (fs_dent->fsi);

	fs_dent->fsi = fs->inode_lookup(fs, fs_dent->inode);

	if (getu64(fs, fname->flags) & NTFS_FNAME_FLAGS_DIR)
		fs_dent->ent_type = FS_DENT_DIR;
	else
		fs_dent->ent_type = FS_DENT_REG;

	return;
}



/* 
 * This loads the contents of idxalloc into the global variables
 * curbuf and bufleft
 *
 * This function can not be called recursively due to its usage of
 * global variables 
 *
 */

static char *curbuf;
static int bufleft;

static u_int8_t
idxalloc_action(FS_INFO *fs, DADDR_T addr, char *buf, int size, 
  int flags, char *ptr)
{
	int len;

	if (!curbuf)  goto  errLabel;
		//  error("curbuf is NULL");

	len = ((size < bufleft) ? size : bufleft);

	memcpy(curbuf, buf, len);
	curbuf = (char *)((int)curbuf + len);
	bufleft -= len;
errLabel:
	return ((bufleft > 0) ? WALK_CONT : WALK_STOP);
}


/* This is a sanity check to see if the time is valid
 * it is divided by 100 to keep it in a 32-bit integer 
 */

static u_int8_t
is_time(u_int64_t t)
{
#define SEC_BTWN_1601_1970_DIV100 ((369*365 + 89) * 24 * 36)
#define SEC_BTWN_1601_2010_DIV100 (SEC_BTWN_1601_1970_DIV100 + (40*356 + 6) * 24 * 36)

	t /= 1000000000;	/* put the time in seconds div by additional 100 */

	if (!t)
		return 0;

	if (t < SEC_BTWN_1601_1970_DIV100)
		return 0;

	if (t > SEC_BTWN_1601_2010_DIV100)
		return 0;

	return 1;
}

/* 
 * Process a list of directory entries, starting at idxe with a length
 * of _size_ bytes.  _len_ is the length that is reported in the 
 * idxbuf header.  in other words, everything after _len_ bytes is
 * considered unallocated area and therefore deleted content 
 *
 * The only flag that we care about is ALLOC (no UNALLOC entries exist
 * in the tree)
 */
 void  ntfs_dent_idxentry(  NTFS_INFO  *  ntfs,  ntfs_idxentry  *  idxe,
							int  size,  int  len,  int  flags,  FS_DENT_WALK_FN  action,  char  *  ptr  )
{
	DADDR_T		endaddr,  endaddr_alloc;
	int			myflags						=	0;
	int			iRet_procAction				=	CONST_qyRet_ok;

	
	FS_DENT *fs_dent = fs_dent_alloc( NTFS_MAXNAMLEN );
	FS_INFO *fs = (FS_INFO *)&ntfs->fs_info;

	/* where is the end of the buffer */
	endaddr = ((int)idxe + size);

	/* where is the end of the allocated data */
	endaddr_alloc = ((int)idxe + len);

	/* cycle through the index entries, based on provided size */
	while (((int)&(idxe->stream) + sizeof(ntfs_attr_fname)) < endaddr) {
		ntfs_attr_fname *fname = (ntfs_attr_fname *)&idxe->stream;

		/* perform some sanity checks & advance by 4-bytes if 
		 * this is not a valid entry
		 */
		if ((getu48(fs, idxe->file_ref) > fs->last_inum) || 
		   (getu48(fs, idxe->file_ref) < fs->first_inum) ||
		   (getu16(fs, idxe->idxlen) <= getu16(fs, idxe->strlen) ) ||
		   (getu16(fs, idxe->idxlen) % 4) || 
		   (getu16(fs, idxe->idxlen) > size) )
		{
			idxe = (ntfs_idxentry *)((int)idxe + 4);
			continue;
		}

		/* a deleted entry will have strlen of 0, so do some sanity
		 * checks first before we skip it.
		 */
		if  ( (getu16(fs, idxe->strlen) == 0) ||
		  (((int)idxe + getu16(fs, idxe->idxlen)) > endaddr_alloc)) {

			if (
			 ((fname->nspace != NTFS_FNAME_POSIX) &&
			  (fname->nspace != NTFS_FNAME_WIN32) &&
			  (fname->nspace != NTFS_FNAME_DOS) &&
			  (fname->nspace != NTFS_FNAME_WINDOS) ) ||  
		
			  ((int)getu64(fs, fname->alloc_fsize) < (int)getu64(fs, fname->real_fsize)) ||
			  (getu64(fs, fname->real_fsize) < fname->nlen) ||
			  (fname->nlen == 0) ||
			  (*(u_int8_t *)&fname->name == 0) ||
			  (is_time(getu64(fs, fname->crtime)) == 0) ||
			  (is_time(getu64(fs, fname->atime)) == 0) ||
			  (is_time(getu64(fs, fname->mtime)) == 0) ) {

				idxe = (ntfs_idxentry *)((int)idxe + 4);
				continue;
			}
		}
		
		/* For all fname entries, there will exist a DOS style 8.3 
		 * entry.  We don't process those because we already processed
		 * them before in their full version.  If the type is 
		 * full POSIX or WIN32 that does not satisfy DOS, then a 
		 * type NTFS_FNAME_DOS will exist.  If the name is WIN32,
		 * but already satisfies DOS, then a type NTFS_FNAME_WINDOS
		 * will exist */
		if  (  fname->nspace  ==  NTFS_FNAME_DOS  )  goto  incr_entry;
		

		/* Copy it into the generic form */
		ntfs_dent_copy(ntfs, idxe, fs_dent);

		/* 
		 * Check if this entry is deleted
		 *
		 * The final check is to see if the end of this entry is 
		 * within the space that the idxbuf claimed was valid
		 */
		if ((getu16(fs, idxe->strlen) == 0) || 
		  (((int)idxe + getu16(fs, idxe->idxlen)) > endaddr_alloc)) {

			/* we know entries with an inode of 0 are not legit because
			 * that is the MFT value.  Free it so it does not confuse
			 * people with invalid data
			 */
			if (fs_dent->inode == 0) {
				free(fs_dent->fsi);
				fs_dent->fsi = NULL;
			}
			myflags = FS_FLAG_UNALLOC;
		}
		else
			myflags = FS_FLAG_ALLOC;

		iRet_procAction  =  CONST_qyRet_ok;
		if  (  (  flags  &  myflags  )  ==  myflags  )  {
			iRet_procAction  =  action(  fs,  fs_dent,  myflags,  ""  );
			if  (  iRet_procAction  ==  CONST_qyRet_err  )  goto  errLabel;
		}
				
		/* Recurse if we need to */
		if  (  iRet_procAction  !=  CONST_qyRet_skip  
			&&  (  myflags  &  FS_FLAG_ALLOC  ) 
			&&  (  flags  &  FS_FLAG_RECURSE  ) 
			&&  (  !ISDOT(  fs_dent->name  )  ) 
			&&  (  (  fs_dent->fsi->mode  &  FS_INODE_FMT  )  ==  FS_INODE_DIR  ) 
			&&  (  fs_dent->inode  )  ) 
		{

            if (depth < MAX_DEPTH) {
                didx[depth] = &dirs[strlen(dirs)];
				strncpy(didx[depth], fs_dent->name, DIR_STRSZ - strlen(dirs));
                strncat(dirs, "/", DIR_STRSZ);
            }
            depth++;

			ntfs_dent_walk(&(ntfs->fs_info), fs_dent->inode, flags,
			  action, ptr);

            depth--;
            if (depth < MAX_DEPTH)
				*didx[depth] = '\0';

		} /* end of recurse */
		


		/* We could check for the NTFS_IDX_LAST flag here, but
		 * I think we may lose some deleted file entries by 
		 * doing that
		 */
incr_entry:


		/* the theory here is that deleted entries have strlen == 0 and
		 * have been found to have idxlen == 16
		 *
		 * if the strlen is 0, then guess how much the indexlen was
		 * before it was deleted
		 */

		/* 16: size of idxentry before stream
		 * 66: size of fname before name
		 * 2*nlen: size of name (in unicode)
		 */
		if (getu16(fs, idxe->strlen) == 0)
			idxe = (ntfs_idxentry *)((((int)idxe + 16 + 66 + 2*fname->nlen + 3)/4)*4);
		else
			idxe = (ntfs_idxentry *)((int)idxe + getu16(fs, idxe->idxlen));

	} /* end of loop of index entries */

errLabel:

	fs_dent_free(fs_dent);

	return;

}




/*
 * remove the update sequence values that are changed in the last two 
 * bytes of each sector 
 *
 */
static void
ntfs_fix_idxbuf(NTFS_INFO *ntfs, ntfs_idxbuf *idxbuf, u_int32_t len)
{
	int i;
	u_int16_t	orig_seq;
	FS_INFO		*fs = (FS_INFO *)&ntfs->fs_info;
	ntfs_upd	*upd;

    /* sanity check so we don't run over in the next loop */
    if ((getu16(fs, idxbuf->upd_cnt) - 1) * ntfs->ssize_b > len)  goto  errLabel;
        //  error ("More Update Sequence Entries than idx buf size");

    /* Apply the update sequence structure template */
    upd = (ntfs_upd *)((int)idxbuf + getu16(fs, idxbuf->upd_off));
   
    /* Get the sequence value that each 16-bit value should be */
    orig_seq = getu16(fs, upd->upd_val);

    /* cycle through each sector */
    for (i = 1; i < getu16(fs, idxbuf->upd_cnt); i++) {
        /* The offset into the buffer of the value to analyze */
	int offset = i * ntfs->ssize_b - 2;
	u_int8_t *new, *old;

        /* get the current sequence value */
	u_int16_t cur_seq = getu16(fs, (int)idxbuf + offset);

	if (cur_seq != orig_seq) {
		/* get the replacement value */
		u_int16_t cur_repl =
	  	getu16(fs, &upd->upd_seq + (i-1) * 2);  goto  errLabel;

            //  error ("Incorrect update sequence value in index buffer\nUpdate Value: 0x%x Actual Value: 0x%x Replacement Value: 0x%x\nThis is typically because of a corrupted entry", orig_seq, cur_seq, cur_repl);
        }

	new = &upd->upd_seq + (i-1) * 2;
	old = (u_int8_t *)(int)idxbuf + offset;

	*old++ = *new++;	
	*old = *new;	
    }
errLabel:
	return;
}





/* 
 * This function looks up the inode and processes its tree
 *
 */
void
ntfs_dent_walk(FS_INFO *fs, INUM_T inum, int flags,
  FS_DENT_WALK_FN action, char *ptr)
{
	NTFS_INFO 		*ntfs = (NTFS_INFO *)fs;
	FS_INODE 		*fs_inode;
	FS_DATA 		*fs_data_root, *fs_data_alloc;
	char 			*idxalloc;
	ntfs_idxentry 	*idxe;
	ntfs_idxroot 	*idxroot;
	ntfs_idxbuf 	*idxbuf_p;
	int i, idxlen;;

	/* sanity check */
    if (inum < fs->first_inum || inum > fs->last_inum)  goto  errLabel;
		//  error("invalid inode value: %i\n", inum);


	/* Get the inode and verify it has attributes */
    fs_inode = fs->inode_lookup(fs, inum);
	if (!fs_inode->attr)  goto  errLabel;
		//  error("Error: Directory MFT has no attributes");


	/* 
	 * NTFS does not have "." and ".." entries in the index trees
	 * (except for a "." entry in the root directory)
	 * 
	 * So, we'll make 'em up by making a FS_DENT structure for
	 * a '.' and '..' entry and call the action
	 */
	if ((inum != fs->root_inum) && (flags & FS_FLAG_ALLOC)) {
		FS_DENT *fs_dent = fs_dent_alloc(16);
		FS_NAME *fs_name;
		int myflags = FS_FLAG_ALLOC;

		/* 
		 * "." 
		 */
		fs_dent->inode = inum; 
		fs_dent->namlen = 1;
		strcpy(fs_dent->name, ".");

		/* copy the path data */
		fs_dent->path = dirs;
		fs_dent->pathdepth = depth;

		/* this is probably a waste, but just in case the action mucks
		 * with it ...
		 */
		fs_dent->fsi = fs->inode_lookup(fs, fs_dent->inode);
		fs_dent->ent_type = FS_DENT_DIR;

		if (WALK_STOP == action (fs, fs_dent, myflags, "")) { 
			fs_dent_free(fs_dent);
			fs_inode_free(fs_inode);
			return;
		}



		/*
		 * ".."
		 */
		fs_dent->namlen = 2;
		strcpy(fs_dent->name, "..");
		fs_dent->ent_type = FS_DENT_DIR;

		/* The fs_name structure holds the parent inode value, so we 
		 * just cycle using those
		 */
		for (fs_name = fs_inode->name; fs_name != NULL; 
		  fs_name = fs_name->next) {
			if (fs_dent->fsi) {
				fs_inode_free(fs_dent->fsi);
				fs_dent->fsi = NULL;
			}
			
			fs_dent->inode = fs_name->par_inode;
			fs_dent->fsi = fs->inode_lookup(fs, fs_dent->inode);
			if (WALK_STOP == action (fs, fs_dent, myflags, "")) { 
				fs_dent_free(fs_dent);
				fs_inode_free (fs_inode);
				return;
			}
			
		}

		fs_dent_free(fs_dent);
		fs_dent = NULL;
	 }


	/* 
	 * Read & process the Index Root Attribute 
	 */
    fs_data_root = fs_data_lookup(fs_inode->attr, NTFS_ATYPE_IDXROOT, 0);
	if (!fs_data_root)  goto  errLabel;
		//  error ("$IDX_ROOT not found in MFT %d", inum);

	if (fs_data_root->flags & FS_DATA_NONRES)  goto  errLabel;
		//  error ("$IDX_ROOT is not resident - it should be");

	idxroot = (ntfs_idxroot *)fs_data_root->buf;
	idxe = (ntfs_idxentry *)&idxroot->stream;

	/* Get the type that is used to sort the tree */
	/* @@@ We should handle more things besides FNAME */
	if (getu32(fs, idxroot->type) == 0)
		return;
	else if (getu32(fs, idxroot->type) != NTFS_ATYPE_FNAME)  goto  errLabel;
		//  error ("ERROR: Directory index is sorted by type: %d.\nOnly $FNAME is currently supported", getu32(fs, idxroot->type));

	/* Process it */
	ntfs_dent_idxentry (ntfs, idxe, fs_data_root->buflen,
	  getu32(fs, idxroot->strlen), flags, action, ptr);


	/* 
	 * get the index allocation attribute if it exists (it doesn't for 
	 * small directories 
	 */
    fs_data_alloc = fs_data_lookup(fs_inode->attr, NTFS_ATYPE_IDXALLOC, 0);


	/* if we don't have an index alloc then return, we have processed
	 * all of the entries 
	 */
	if (!fs_data_alloc) {
		if (idxroot->flags & NTFS_IDX_LARGE)  goto  errLabel;
			//  error("Error: $IDX_ROOT says there should be an $IDX_ALLOC, but there isn't");

		return;
	}


	if (fs_data_alloc->flags & FS_DATA_RES)  goto  errLabel;
		//  error ("$IDX_ALLOC is Resident - it shouldn't be");

	/* 
	 * Copy the index allocation run into a big buffer
	 */
	bufleft = idxlen = (int)fs_data_alloc->runlen;
	curbuf = idxalloc = mymalloc (bufleft);

	fs->file_walk(fs, fs_inode, NTFS_ATYPE_IDXALLOC, 0, 
		FS_FLAG_CONT | FS_FLAG_SLACK,
		idxalloc_action, "index alloc");

	if (bufleft > 0)  goto  errLabel;
		//  error ("bufleft = %d", bufleft);


	/*
	 * The idxalloc is a big buffer that contains one or more
	 * idx buffer structures.  Each idxbuf is a sub-node in the B-Tree.  
	 * We do not process the tree as a tree because then we could
	 * not find the deleted file names.
	 *
	 * Therefore, we scan the big buffer looking for the idxbuf
	 * structures.  We save a pointer to the known beginning.
	 * Then we scan for the beginning of the next one and process
	 * everything in the middle as an idxbuf.  We can't use the
	 * size given because then we wouldn't see the deleted 
	 * names
	 */

	/* Set the previous pointer to NULL */
	idxbuf_p = NULL;

	/* Loop by cluster size */
	for (i = 0; i < idxlen; i += ntfs->csize_b) {
		ntfs_idxbuf *idxbuf = (ntfs_idxbuf *)&idxalloc[i];

		/* If we are not at the begining of an IDXBUF structure
		 * and not at the end of the buffer, then advance again
		 * until either the end of the buffer or the end of the 
		 * previous structure
		 */
		if ((getu32(fs, idxbuf->magic) != NTFS_IDXBUF_MAGIC) &&
		  (i != (idxlen - ntfs->csize_b))) 
				continue;


		/* idxbuf_p is only NULL for the first time that we set it
		 * (the first valid structure).  In that case, there is no
		 * previous valid structure
		 */
		if (idxbuf_p == NULL)
			idxbuf_p = idxbuf;

		/* this is the last structure in the buffer */
		if (i == (idxlen - ntfs->csize_b)) 
			idxbuf = (ntfs_idxbuf *)&idxalloc[idxlen];
	
		/* Process the previous structure if:
		 *  - it is the last one in the total buffer or
		 *  - idxbuf_p is the previous buffer and we are now pointing to
		 *    the second one
		 */
		if (idxbuf_p != idxbuf) {
			/* idxbuf points to the next idxbuf structure, idxbuf_p
			 * points to the one we are going to process
			 */
			int len;

			/* remove the update sequence */
			ntfs_fix_idxbuf(ntfs, idxbuf_p, (int)idxbuf - (int)idxbuf_p);

			/* I'm not sure why it is off by 0x18, but that is what the
			 * sourceforge docs say and it works 
			 */
			idxe = (ntfs_idxentry *)((int)idxbuf_p +
			  getu16(fs, idxbuf_p->begin_off) + 0x18);

			/* This is the length of the idx entries */
			len = (int)idxbuf - (int)idxe;

			/* process the list of index entries */
			ntfs_dent_idxentry (ntfs, idxe, len, 
			  getu32(fs, idxbuf_p->end_off) - getu16(fs, idxbuf_p->begin_off),
			  flags, action, ptr);

			/* reset the pointer */
			idxbuf_p = idxbuf;
		}
	}
errLabel:
	fs_inode_free (fs_inode);
	free(idxalloc);
	return;

} /* end of dent_walk */




/****************************************************************************
 * FIND_FILE ROUTINES
 *
 */


/* 
 * Looks up the parent inode described in fs_name.  
 * myflags are the flags from the original inode lookup
 *
 * fs_dent was filled in by ntfs_find_file and will get the final path
 * added to it before action is called
 */
static void
ntfs_find_file_rec (FS_INFO *fs, FS_DENT *fs_dent, FS_NAME *fs_name, 
  int myflags, int flags, FS_DENT_WALK_FN action, char *ptr)
{
	FS_INODE *fs_inode_par;
	FS_NAME *fs_name_par;
	u_int8_t decrem = 0;
	int len = 0, i;
	char *begin = NULL;

    if (fs_name->par_inode < fs->first_inum || 
	  fs_name->par_inode > fs->last_inum)  goto  errLabel;
		//  error("invalid inode value: %i\n", fs_name->par_inode);

    fs_inode_par = fs->inode_lookup(fs, fs_name->par_inode);

	/* 
	 * Orphan File
	 * This occurs when the file is deleted and either:
	 * - The parent is no longer a directory 
	 * - The sequence number of the parent is no longer correct
	 */
	if (((fs_inode_par->mode & FS_INODE_FMT) != FS_INODE_DIR) ||
	  (fs_inode_par->seq != fs_name->par_seq)) {
		char *str = ORPHAN_STR; 
		len = strlen(str);

		/* @@@ There should be a sanity check here to verify that the 
		 * previous name was unallocated ... but how do I get it again?
		 */

		if ((((int)didx[depth-1] - len) >= (int)&dirs[0] ) &&
		  (depth < MAX_DEPTH)) {
			begin = didx[depth] = (char *)((int)didx[depth-1] - len);

			depth++;
			decrem = 1;

			for (i = 0; i < len; i++) 
				begin[i] = str[i];
		}

		fs_dent->path = begin;
		fs_dent->pathdepth = depth;
		action (fs, fs_dent, myflags, ptr);

		if (decrem)
			depth--;

		fs_inode_free(fs_inode_par);
		return;
	}

	for (fs_name_par = fs_inode_par->name; fs_name_par != NULL; 
	  fs_name_par = fs_name_par->next) {

		len = strlen (fs_name_par->name);	

		/* do some length checks on the dir structure 
		 * if we can't fit it then forget about it */
		if ((((int)didx[depth-1] - len - 1) >= (int)&dirs[0] ) &&
		  (depth < MAX_DEPTH)) {
			begin = didx[depth] = (char *)((int)didx[depth-1] - len - 1);

			depth++;
			decrem = 1;

			*begin = '/';
			for (i = 0; i < len; i++) 
				begin[i+1] = fs_name_par->name[i];
		}
		else {
			begin = didx[depth];
			decrem = 0;
		}

	
		/* if we are at the root, then fill out the rest of fs_dent with
		 * the full path and call the action 
		 */
		if (fs_name_par->par_inode == NTFS_ROOTINO) {
			/* increase the path by one so that we do not pass the '/'
			 * if we do then the printed result will have '//' at 
			 * the beginning
			 */
			fs_dent->path = (char *)(int)begin + 1;
			fs_dent->pathdepth = depth;
			action (fs, fs_dent, myflags, ptr);
		}

		/* otherwise, recurse some more */
		else {
			ntfs_find_file_rec(fs, fs_dent, fs_name_par, myflags, flags, 
			  action, ptr);
		}

		/* if we incremented before, then decrement the depth now */
		if (decrem)
			depth--;
	}
errLabel:
	fs_inode_free (fs_inode_par);
}

/* 
 * this is a much faster way of doing it in NTFS 
 *
 * the inode that is passed in this case is the one to find the name
 * for
 *
 * This can not be called with dent_walk because the path
 * structure will get messed up!
 */

void
ntfs_find_file (FS_INFO *fs, INUM_T inode_toid, int flags,
  FS_DENT_WALK_FN action, char *ptr)
{

	FS_INODE *fs_inode;
	FS_NAME *fs_name;
	FS_DENT *fs_dent = fs_dent_alloc(NTFS_MAXNAMLEN);
	int myflags;
	NTFS_INFO *ntfs = (NTFS_INFO *)fs;

	/* sanity check */
    if (inode_toid < fs->first_inum || inode_toid > fs->last_inum)  goto  errLabel;
		//  error("invalid inode value: %i\n", inode_toid);

	/* in this function, we use the dirs array in the opposite order.
	 * we set the end of it to NULL and then prepend the
	 * directories to it
	 *
	 * didx[depth] will point to where the current level started their
	 * dir name
	 */
	dirs[DIR_STRSZ - 2] = '/';    
	dirs[DIR_STRSZ - 1] = '\0';    
	didx[0] = &dirs[DIR_STRSZ - 2];
	depth = 1;


	/* lookup the inode and get its allocation status */
	fs_dent->inode = inode_toid;
    fs_dent->fsi = fs_inode = fs->inode_lookup(fs, inode_toid);
	myflags = ((getu16(fs, ntfs->mft->flags) & NTFS_MFT_INUSE) ?
		  FS_FLAG_ALLOC : FS_FLAG_UNALLOC);

	/* loop through all the names it may have */
	for (fs_name = fs_inode->name; fs_name != NULL; fs_name = fs_name->next) {
		
		fs_dent->namlen = strlen (fs_name->name);
		strncpy(fs_dent->name, fs_name->name, fs_dent->maxnamlen);

		/* if this is in the root directory, then call back */
		if (fs_name->par_inode == NTFS_ROOTINO) {
			fs_dent->path = didx[0];
			fs_dent->pathdepth = depth;
			action (fs, fs_dent, myflags, ptr);
		}
		/* call the recursive function on the parent */
		else {
			ntfs_find_file_rec(fs, fs_dent, fs_name, myflags, flags, 
			  action, ptr);
		}

	} /* end of name loop */
errLabel:
	fs_dent_free(fs_dent);
	
	return;
}
