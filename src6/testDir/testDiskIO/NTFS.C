/*
** ntfs
** The @stake Sleuth Kit (TASK)
**
** Content and meta data layer support for the NTFS file system
**
** Brian Carrier [carrier@atstake.com]
** Copyright (c) 2002 Brian Carrier, @stake Inc.  All rights reserved
**
*/
#include "fs_tools.h"
#include "fs_types.h"
#include "ntfs.h"

#include "mymalloc.h"
#include "error.h"

#include "fs_data.h"

#include <ctype.h>

/*
 * NOTES TO SELF:
 *
 * - multiple ".." entries may exist
 */
#define roundup(x, y)	\
	( ( ((x)+((y) - 1)) / (y)) * (y) )

extern FILE *logfp;


/* 
 * How are we to handle the META flag? Is the MFT $Data Attribute META?
 */


/* needs to be predefined for proc_attrseq */
static void
ntfs_proc_attrlist(NTFS_INFO *, FS_INODE *, FS_DATA *);



/* mini-design note:
 * The MFT has entries for every file and dir in the fs.
 * The first entry ($MFT) is for the MFT itself and it is used to find
 * the location of the entire table because it can become fragmented.
 * Therefore, the $Data attribute of $MFT is saved in the NTFS_INFO
 * structure for easy access.  We also use the size of the MFT as
 * a way to calculate the maximum MFT entry number (last_inum).
 *
 * Ok, that is simple, but getting the full $Data attribute can be tough
 * because $MFT may not fit into one MFT entry (i.e. an attribute list). 
 * We need to process the attribute list attribute to find out which
 * other entries to process.  But, the attribute list attribute comes
 * before any $Data attribute (so it could refer to an MFT that has not
 * yet been 'defined').  Although, the $Data attribute seems to always 
 * exist and define at least the run for the entry in the attribute list.
 *
 * So, the way this is solved is that generic mft_lookup is used to get
 * any MFT entry, even $MFT.  If $MFT is not cached then we calculate 
 * the address of where to read based on mutliplication and guessing.  
 * When we are loading the $MFT, we set 'loading_the_MFT' to 1 so
 * that we can update things as we go along.  When we read $MFT we
 * read all the attributes and save info about the $Data one.  If
 * there is an attribute list, we will have the location of the
 * additional MFT in the cached $Data location, which will be 
 * updated as we process the attribute list.  After each MFT
 * entry that we process while loading the MFT, the 'final_inum'
 * value is updated to reflect what we can currently load so 
 * that the sanity checks still work.
 */

// set to 1 when $MFT is itself being loaded
static u_int8_t loading_the_MFT = 0; 

/**********************************************************************
 *
 *  MISC FUNCS
 *
 **********************************************************************/

/* convert the NT Time (UTC hundred nanoseconds from 1/1/1601)
 * to UNIX (UTC seconds from 1/1/1970)
 *
 * The basic calculation is to remove the nanoseconds and then
 * subtract the number of seconds between 1601 and 1970
 * i.e. TIME - DELTA
 *
 */
u_int32_t
nt2unixtime(u_int64_t ntdate)
{
// (369*365 + 89) * 24 * 3600 * 10000000
#define	NSEC_BTWN_1601_1970	(u_int64_t)(116444736000000000)

	ntdate -= (u_int64_t)NSEC_BTWN_1601_1970;
	ntdate /= (u_int64_t)10000000;

	return (u_int32_t)ntdate;
}

/* 
 * Convert a UNICODE string to an ASCII string
 * 
 * both uni and asc must be defined and asc must be >= ulen / 2
 */
void 
uni2ascii(char *uni, int ulen, char *asc, int alen)
{
	int i, l;


	/* find the maximum that we can go
	 * we will break when we hit NULLs, but this is the
	 * absolute max 
	 */
	if ((ulen + 1) > alen)
		l = alen - 1;
	else
		l = ulen;

	for (i = 0; i < l; i++) {
		/* If this value is NULL, then stop */
		if (uni[i*2] == 0 && uni[i*2 + 1] == 0)
			break;

		if (isprint((int)uni[i*2]))
			asc[i] = uni[i*2];
		else
			asc[i] = '?';
	}
	/* NULL Terminate */
	asc[i] = '\0';
	return;
}


/**********************************************************************
 *
 * Lookup Functions
 *
 **********************************************************************/


/*
 * Lookup up a given MFT entry (mftnum) in the MFT and save it in its
 * raw format in *mft.
 *
 * NOTE: This will remove the update sequence integrity checks in the
 * structure
 */
static void
ntfs_mft_lookup(NTFS_INFO *ntfs, ntfs_mft *mft, u_int32_t mftnum)
{
	OFF_T mftaddr_b, mftaddr2_b, offset;
	int mftaddr_len = 0;
	int i;
	FS_INFO *fs = (FS_INFO *)&ntfs->fs_info;
	FS_DATA_RUN *data_run;
	ntfs_upd *upd;
	u_int16_t orig_seq;

	/* sanity checks */
	if (!mft)  goto  errLabel;
		//  error("mft_lookup: null mft buffer");

	if (mftnum < fs->first_inum)  goto  errLabel;
		//  error("inode number is too small (%lu)", (ULONG) mftnum);
	if (mftnum > fs->last_inum)  goto  errLabel;
		//  error("inode number is too large (%lu)", (ULONG) mftnum);

/*
	if (verbose)
		fprintf (logfp,
		  "ntfs_mft_lookup: Processing MFT %lu\n", (ULONG)mftnum);  */

	/* If mft_data (the cached $Data attribute of $MFT) is not there yet, 
	 * then we have not started to load $MFT yet.  In that case, we will
	 * 'cheat' and calculate where it goes.  This should only be for
	 * $MFT itself, in which case the calculation is easy
	 */
	if (!ntfs->mft_data) {

		/* This is just a random check with the assumption being that
		 * we don't want to just do a guess calculation for a very large
		 * MFT entry
		 */
		if (mftnum > NTFS_LAST_DEFAULT_INO)  goto  errLabel;
			//  error ("Error trying to load a high MFT entry when the MFT itself has not been loaded (%d)", mftnum);

		mftaddr_b = ntfs->root_mft_addr +  mftnum * ntfs->mft_rsize_b;
		mftaddr2_b = 0;
	}
	else {
		/* The MFT may not be in consecutive clusters, so we need to use its
		 * data attribute run list to find out what address to read
		 *
		 * This is why we cached it
		 */

		// will be set to the address of the MFT entry
		mftaddr_b = mftaddr2_b = 0;  

		/* The byte offset within the $Data stream */
		offset = mftnum * ntfs->mft_rsize_b;

		/* NOTE: data_run values are in clusters 
		 *
		 * cycle through the runs in $Data and identify which
		 * has the MFT entry that we want
		 */
		for (data_run = ntfs->mft_data->run; 
		  data_run != NULL; data_run = data_run->next) {

			/* The length of this specific run */
			OFF_T run_len = data_run->len * ntfs->csize_b;

			/* Is our MFT entry is in this run somewhere ? */
			if (offset < run_len) {

				/*
				if (verbose)
					fprintf (logfp,
					  "ntfs_mft_lookup: Found in offset: %llu  size: %llu at offset: %llu\n", 
					  (ULONGLONG)data_run->addr, (ULONGLONG)data_run->len, (ULONGLONG)offset);
					  */

				/* special case where the MFT entry crosses
				 * a run (only happens when cluster size is 512-bytes
				 * and there are an odd number of clusters in the run)
				 */
				if (run_len < offset + ntfs->mft_rsize_b) {

					/*
					if (verbose) 
						fprintf (logfp,
						  "ntfs_mft_lookup: Entry crosses run border\n");  */

					if (data_run->next == NULL) goto  errLabel;
						//  error("MFT entry crosses a cluster and there are no more clusters!");

					/* Assign address where the remainder of the entry is */
					mftaddr2_b= data_run->next->addr * ntfs->csize_b;	

					/* this should always be 512, but just in case */
					mftaddr_len = run_len - offset;
				}	

				/* Assign address of where the MFT entry starts */
				mftaddr_b = data_run->addr * ntfs->csize_b + offset;
				/*
				if (verbose)
					fprintf (logfp,	  "ntfs_mft_lookup: Entry address at: %llu\n",  (ULONGLONG)mftaddr_b);  */
				break;
			}

			/* decrement the offset we are looking for */
			offset -= run_len;
		}

		/* Did we find it? */
		if (!mftaddr_b)  goto  errLabel;
			//  error ("Error finding MFT entry %d in $MFT", mftnum);
	}


	/* can we do just one read or do we need multiple? */
	if (mftaddr2_b) {
		/* read the first part into mft */
		fs_read_random(&ntfs->fs_info, (char *)mft, 
		  mftaddr_len, mftaddr_b, "mft read");

		/* read the second part into mft */
		fs_read_random(&ntfs->fs_info, (char *)((int)mft + mftaddr_len), 
		  ntfs->mft_rsize_b - mftaddr_len, mftaddr2_b, "mft read");
	}
	else {	
		/* read the raw entry into mft */
		fs_read_random(&ntfs->fs_info, (char *)mft, 
		  ntfs->mft_rsize_b, mftaddr_b, "mft read");
	}

	/* if we are saving into the NTFS_INFO structure, assign mnum too */
	if ((int)mft == (int)ntfs->mft)
		ntfs->mnum = mftnum;

	/* Sanity Check */
	/* @@@ What else should we do with a BAAD entry ... */
	if ((getu32(fs, mft->magic) != NTFS_MFT_MAGIC) &&
	 (getu32(fs, mft->magic) != NTFS_MFT_MAGIC_BAAD))  goto  errLabel;
		//  error ("entry %d has an invalid MFT magic: %x", mftnum,  getu32(fs, mft->magic));

	/* The MFT entries have error and integrity checks in them
	 * called update sequences.  They must be checked and removed
	 * so that later functions can process the data as normal. 
	 * They are located in the last 2 bytes of each 512-byte sector
	 *
	 * We first verify that the the 2-byte value is a give value and
	 * then replace it with what should be there
	 */

	/* sanity check so we don't run over in the next loop */
	if ((getu16(fs, mft->upd_cnt) - 1) * ntfs->ssize_b > ntfs->mft_rsize_b)  goto  errLabel;
		//  error ("More Update Sequence Entries than MFT size");


	/* Apply the update sequence structure template */
	upd = (ntfs_upd *)((int)mft + getu16(fs, mft->upd_off));
	
	/* Get the sequence value that each 16-bit value should be */
	orig_seq = getu16(fs, upd->upd_val);

	/* cycle through each sector */
	for (i = 1; i < getu16(fs, mft->upd_cnt); i++) {
        /* The offset into the buffer of the value to analyze */
		int offset = i * ntfs->ssize_b - 2;
		u_int8_t *new, *old;

		/* get the current sequence value */
		u_int16_t cur_seq = getu16(fs, (int)mft + offset);

		if (cur_seq != orig_seq) {
			/* get the replacement value */
			u_int16_t cur_repl =  getu16(fs, &upd->upd_seq + (i-1) * 2);  
			goto  errLabel;
			//  error ("Incorrect update sequence value in index buffer\nUpdate Value: 0x%x Actual Value: 0x%x Replacement Value: 0x%x\nThis is typically because of a corrupted entry",  orig_seq, cur_seq, cur_repl);
		}

		new = &upd->upd_seq + (i-1) * 2;
		old = (u_int8_t *)(int)mft + offset;

		/*
		if (verbose)
			fprintf(logfp, 
			  "ntfs_mft_lookup: upd_seq %i   Replacing: %.4x   With: %.4x\n",
			  i, getu16(fs, old), getu16(fs, new));  */

		*old++ = *new++;
		*old = *new;
	}
errLabel:
	return;
}



/*
 * given a cluster, return the cluster address containing the bitmap
 * for the given cluster
 */
static u_int64_t
ntfs_bmap_addr (NTFS_INFO *ntfs, u_int32_t cluster)
{
	int bit_p_cl = ntfs->fs_info.block_size * 8;
	int c;
	FS_DATA_RUN *run;

	if (cluster > ntfs->fs_info.last_block)  goto  errLabel;
		//  error ("ntfs_bmap_lookup: cluster too large");

	/* identify which cluster in the run we want */
	c = cluster / bit_p_cl;

	for (run = ntfs->bmap; run; run = run->next) {
		if (run->len <= c) {
			c -= run->len;
			continue;
		}
		return run->addr + c; 
	}

	//  error ("ntfs_bmap_lookup: cluster not found");
errLabel:
	return 1;
}



/**********************************************************************
 *
 *  FS_DATA functions
 *
 **********************************************************************/


/* 
 * turn a non-resident runlist into the generic fs_data_run
 * structure
 *
 * The return value is a list of FS_DATA_RUN entries of len
 * runlen (only set if non-NULL)
 */
static FS_DATA_RUN *
ntfs_make_data_run(NTFS_INFO *ntfs, ntfs_runlist *runlist, 
  u_int64_t *runlen)
{
	ntfs_runlist *run;
	FS_DATA_RUN *data_run, *data_run_head = NULL, *data_run_prev = NULL;
	int i, idx;
	int64_t prev_addr = 0;

	run = runlist;

	/* initialize of non-NULL */
	if (runlen)
		*runlen = 0;

	/* the ntfs runlist has dynamic size integers, specified by the
	 * len_size and off_size values
	 */
	while ((NTFS_RUNL_LENSZ(run) != 0) && (NTFS_RUNL_OFFSZ(run) != 0) ) {

		/* allocate a new data_run */
		data_run = fs_data_run_alloc();

		/* make the list, unless its the first pass & then we set the head */
		if (data_run_prev)
			data_run_prev->next = data_run;
		else
			data_run_head = data_run;
		data_run_prev = data_run;


		/* These fields are a variable number of bytes long
		 * these for loops are the equivalent of the getuX macros
		 */
		idx = 0;

		/* Get the length of this run */
		for (i = 0, data_run->len = 0; i < NTFS_RUNL_LENSZ(run); i++) { 
			data_run->len |= (run->buf[idx++] << (i * 8) );
			/*if (verbose)
				fprintf(logfp, 
				"ntfs_make_data_run: Len idx: %i cur: %i (%x) tot: %lu (%x)\n",
				i, run->buf[idx-1], run->buf[idx-1], (ULONG)data_run->len,
				(int)data_run->len );  */
		}

		/* Update the length if we were passed a value */
		if (runlen)
			*runlen += (data_run->len * ntfs->csize_b);


		/* Get the address of this run */
		for (i = 0, data_run->addr = 0; i < NTFS_RUNL_OFFSZ(run); i++) {
			data_run->addr |= (run->buf[idx++] << (i * 8));
			/*if (verbose)
				fprintf(logfp, 
				"ntfs_make_data_run: Off idx: %i cur: %i (%x) tot: %lu (%x)\n",
				i, run->buf[idx-1], run->buf[idx-1], (ULONG)data_run->addr,
				(int)data_run->addr);  */
		}

		/* offset value is signed so extend it to 64-bits */
		if ((int8_t)run->buf[idx - 1] < 0) {
			for ( ; i < sizeof(data_run->addr); i++) 
				data_run->addr |= (int64_t)((int64_t)0xff << (i * 8) );
		}

		/*
		if (verbose)
			fprintf(logfp, 
			  "ntfs_make_data_run: Signed offset: %lli Previous address: %li\n",
			  (ULONGLONG)data_run->addr, (long)prev_addr);  */


		/* The NT 4.0 version of NTFS uses an offset of -1 to represent
		 * a hole, so add the sparse flag and make it look like the 2K
		 * version with a offset of 0
		 */
		if ((data_run->addr == -1) && (ntfs->ver == NTFS_VINFO_NT)) {
			data_run->flags |= FS_DATA_SPARSE;
			data_run->addr = 0;
		}

		/* A Sparse file has a run with an offset of 0
		 * there is a special case though of the BOOT MFT entry which
		 * is the super block and has a legit offset of 0.
		 *
		 * The value given is a delta of the previous offset, so add 
		 * them for non-sparse files
		 *
		 * For sparse files the next run will have its offset relative 
		 * to the current "prev_addr" so skip that code
		 */
		else if ((data_run->addr) || (ntfs->mnum == NTFS_MFT_BOOT)) {
			data_run->addr += prev_addr;
			prev_addr = data_run->addr;
		}
		else {
			data_run->flags |= FS_DATA_SPARSE;
			/*if (verbose)
				fprintf(logfp, "ntfs_make_data_run: Sparse Run\n");  */
		}


		/* Advance run */
		run = (ntfs_runlist *) ((int)run + 
		   (1 + NTFS_RUNL_LENSZ(run) + NTFS_RUNL_OFFSZ(run) ) );

	}

	/* special case, only seen on the $BADCLUST mft entry, which 
	 * always has a weird size.
	 * Basically, we check if there is only one run entry and it
	 * is sparse, then get rid of it
	 */
	if ((data_run_head != NULL) && (data_run_head->next == NULL) && 
	  (data_run_head->flags & FS_DATA_SPARSE)) {
		free(data_run_head);
		data_run_head = NULL;
	}

	return data_run_head;
}



/*
 * Perform a walk on a given FS_DATA list.  The _action_ function is
 * called on each cluster of the run.  
 *
 * This gives us an interface to call an action on data and not care if
 * it is resident or not.
 *
 * used flag values: FS_FLAG_AONLY, FS_FLAG_SLACK
 * unused flag values: FS_FLAG_{UN}ALLOC, FS_FLAG_META, FS_FLAG_CONT, 
 */
static void
ntfs_data_walk(NTFS_INFO *ntfs, FS_DATA *fs_data, 
	int flags, FS_FILE_WALK_FN action, char *ptr)
{
	FS_INFO *fs = (FS_INFO *)&ntfs->fs_info;
	int myflags;

	/* Process the resident buffer 
	 *
	 * Resident has no concept of UNALLOCATED or SLACK
	 */
	if (fs_data->flags & FS_DATA_RES)  {
		char *buf = NULL;

		/* if it is resident, we only care about it if the content is
		 * wanted as there are no address or meta data about it
		 */
		if ((flags & FS_FLAG_CONT) == 0)
			return;

		if ((flags & FS_FLAG_AONLY) == 0) {
			buf = mymalloc(fs_data->size);
			memcpy(buf, fs_data->buf, fs_data->size);
		}

		myflags = FS_FLAG_CONT;
		action(fs, ntfs->root_mft_addr, buf, fs_data->size, myflags, ptr);
			
		if (buf)
			free(buf);
	}
	/* non-resident */
	else {
		int a, bufsize;
		DADDR_T	addr;
		FS_BUF *fs_buf = NULL;
		char *buf = NULL; 
		u_int64_t fsize;
		FS_DATA_RUN *fs_data_run;

		/* if we want the slack space too, then use the runlen  */
		if (flags & FS_FLAG_SLACK)
			fsize = fs_data->runlen;
		else 
			fsize = fs_data->size;

		if ((flags & FS_FLAG_AONLY) == 0)  {
			fs_buf = fs_buf_alloc(fs->block_size);	
			buf = fs_buf->data;
		}

		fs_data_run = fs_data->run;

		/* cycle through the number of runs we have */
		while (fs_data_run) {

			/* if this is just a filler entry, then skip it
			 * This should not happen, but may when dealing with deleted 
			 * entries 
			 */
			if (fs_data_run->flags & FS_DATA_FILLER)  goto  errLabel;
				//  error("Filler Entry exists in fs_data_run");

			addr = fs_data_run->addr;	

			/* cycle through each cluster in the run */
			for (a = 0; a < fs_data_run->len; a++) {

				/* If the address is too large then give an error unless
				 * the no abort flag is set */
				if (addr > fs->last_block) {
					if (flags & FS_FLAG_NOABORT)
						return;
					else  goto  errLabel;
						//  error ("Invalid address in run (too large): %lu", (ULONG)addr);
				}

				if ((flags & FS_FLAG_AONLY) == 0) {
					/* sparse files just get 0s */
					if (fs_data_run->flags & FS_DATA_SPARSE)
						memset (buf, 0, fs->block_size);
					else
						fs_read_block(fs, fs_buf, fs->block_size, 
						   addr, "data block");
				}

				/* Do we read a full block, or just the remainder? */
				if ((u_int64_t)fs->block_size < fsize)
					bufsize = fs->block_size;
				else
					bufsize = (int)fsize;

				myflags = FS_FLAG_CONT;
				if (WALK_STOP == action(fs, addr, buf, bufsize, myflags, ptr)) {
					if ((flags & FS_FLAG_AONLY) == 0)
						fs_buf_free(fs_buf);
					return;
				}

				
				if ((u_int64_t)fs->block_size >= fsize)
					break;

				fsize -= (u_int64_t)fs->block_size;

				/* If it is a sparse run, don't increment the addr so that
				 * it always reads 0
				 */
				if ((fs_data_run->flags & FS_DATA_SPARSE) == 0)
					addr++;
			}
			
			/* advance to the next run */ 
			fs_data_run = fs_data_run->next;
		}

		if ((flags & FS_FLAG_AONLY) == 0) 
			fs_buf_free(fs_buf);

	} /* end of non-res */
errLabel:
	return;
}



/* 
 * An attribute sequence is a linked list all of the attributes for a
 * MFT entry.
 * 
 * This function takes a pointer to the beginning of the sequence,
 * examines each attribute and adds the data to the appropriate fields
 * of fs_inode
 *
 * len is the length of the attrseq buffer
 *
 * This is called by copy_inode and proc_attrlist
 *
 */
static void
ntfs_proc_attrseq (NTFS_INFO *ntfs, FS_INODE *fs_inode, ntfs_attr *attrseq,
  int len)
{
	ntfs_attr 	*attr = attrseq;
	FS_DATA		*fs_data_attrl = NULL, *fs_data;
	char		name[NTFS_MAXNAMLEN+1];
	u_int64_t	runlen;
	FS_INFO 	*fs = (FS_INFO *)&ntfs->fs_info;

	/*
	if (verbose)
		fprintf(logfp, "ntfs_proc_attrseq: Processing MFT %lu\n", 
		  (ULONG)ntfs->mnum);  */

	/* Cycle through the list of attributes */
	for ( ; ((int)attr >= (int)attrseq) && 
			((int)attr <= ((int)attrseq + len)) && 
			(getu32(fs, attr->len) > 0 &&
			(getu32(fs, attr->type) != 0xffffffff));
	        (int)attr += getu32(fs, attr->len)) 
	{
		/* Get the type of this attribute */
		u_int32_t	type = getu32(fs, attr->type);


		/* 
		 * For resident attributes, we will copy the buffer into
		 * a FS_DATA buffer, which is stored in the FS_INODE
		 * structure
		 */
		if (attr->res == NTFS_MFT_RES) {

			/* Copy the name into ASCII */
			if (attr->nlen)
				uni2ascii(&attr->c.r.name, attr->nlen, name, sizeof(name));
			/* Call the unnamed $Data attribute, $Data */
			else if (type == NTFS_ATYPE_DATA)
				strncpy(name, "$Data", NTFS_MAXNAMLEN+1);
			else
				strncpy(name, "N/A", NTFS_MAXNAMLEN+1);

			/*
			if (verbose)
				fprintf(logfp, 
				  "ntfs_proc_attrseq: Resident Attribute in %lu Type: %lu Id: %lu Name: %s\n", 
				  (ULONG)ntfs->mnum, (ULONG)type, (ULONG)getu16(fs, attr->id), name);
				  */


			/* Add this resident stream to the fs_inode->attr list */
			fs_inode->attr = fs_data_put_str(fs_inode->attr, name, 
			  type, getu16(fs, attr->id),
			  (DADDR_T *)((int)attr + getu16(fs, attr->c.r.soff)), 
			  getu32(fs, attr->c.r.ssize));

		}
		/* For non-resident attributes, we will copy the runlist
		 * to the generic form and then save it in the FS_INODE->attr
		 * list
		 */
		else {
			FS_DATA_RUN *fs_data_run;

			/* Copy the name */
			if (attr->nlen)
				uni2ascii(&attr->c.nr.name, attr->nlen, name, sizeof(name));
			else if (type == NTFS_ATYPE_DATA)
				strncpy(name, "$Data", NTFS_MAXNAMLEN+1);
			else
				strncpy(name, "N/A", NTFS_MAXNAMLEN+1);

			/*
			if (verbose)
				fprintf(logfp, 
				  "ntfs_proc_attrseq: Non-Resident Attribute in %lu Type: %lu Id: %lu Name: %s\n", 
				  (ULONG)ntfs->mnum, (ULONG)type, (ULONG)getu16(fs, attr->id), name); */

			/* convert the run to generic form */
			fs_data_run = ntfs_make_data_run(ntfs, 
			  (ntfs_runlist *) ((int)attr + getu16(fs, attr->c.nr.run_off)),
			  &runlen);

			/* Add the run to the list */
			fs_inode->attr = fs_data_put_run(fs_inode->attr, 
			  getu64(fs, attr->c.nr.start_vcn), runlen, fs_data_run,
			  name, type, getu16(fs, attr->id), 
			  getu64(fs, attr->c.nr.ssize));
		}


		/* 
		 * Special Cases, where we grab additional information
		 * regardless if they are resident or not
		 */

		/* Standard Information (is always resident) */
		if (type == NTFS_ATYPE_SI) {
			ntfs_attr_si *si;

			if (attr->res != NTFS_MFT_RES)  goto  errLabel;
				//  error ("Standard Information Attribute is not resident!");

			si = (ntfs_attr_si *) ((int)attr + getu16(fs, attr->c.r.soff));

			fs_inode->mtime = nt2unixtime(getu64(fs, si->mtime)); 
			fs_inode->atime = nt2unixtime(getu64(fs, si->atime)); 
			fs_inode->ctime = nt2unixtime(getu64(fs, si->ctime)); 
			fs_inode->crtime = nt2unixtime(getu64(fs, si->crtime)); 

			fs_inode->uid = getu32(fs, si->own_id);

			fs_inode->mode |= (MODE_IXUSR | MODE_IXGRP | MODE_IXOTH);

			if ((getu32(fs, si->dos) & NTFS_SI_RO) == 0)
				fs_inode->mode |= (MODE_IRUSR | MODE_IRGRP | MODE_IROTH);

			if ((getu32(fs, si->dos) & NTFS_SI_HID) == 0)
				fs_inode->mode |= (MODE_IWUSR | MODE_IWGRP | MODE_IWOTH);
		}

		/* File Name (always resident) */
		else if (type == NTFS_ATYPE_FNAME) {
			ntfs_attr_fname *fname;
			FS_NAME *fs_name;

			if (attr->res != NTFS_MFT_RES) goto  errLabel;
				//  error ("File Name Attribute is not resident!");

			fname = (ntfs_attr_fname *)((int)attr + getu16(fs, attr->c.r.soff));

			if (fname->nspace == NTFS_FNAME_DOS)
				continue;

			/* Seek to the end of the fs_name structures in FS_INODE */
			if (fs_inode->name) {
				for (fs_name = fs_inode->name; 
			  	  (fs_name) && (fs_name->next != NULL);
			      fs_name = fs_name->next) { }
		
				/* add to the end of the existing list */
				fs_name->next = (FS_NAME *)mymalloc(sizeof(FS_NAME));
				fs_name = fs_name->next;
				fs_name->next = NULL;
			}
			else {
				/* First name, so we start a list */
				fs_inode->name = fs_name = (FS_NAME *)mymalloc(sizeof(FS_NAME));
				fs_name->next = NULL;
			}

			uni2ascii(&fname->name, fname->nlen, fs_name->name, 256);
			fs_name->par_inode = getu48(fs, fname->par_ref);
			fs_name->par_seq = getu16(fs, fname->par_seq);
			
		}

		/* If this is an attribute list than we need to process
		 * it to get the list of other entries to read.  But, because
		 * of the wierd scenario of the $MFT having an attribute list
		 * and not knowing where the other MFT entires are yet, we wait 
		 * until the end of the attrseq to processes the list and then
		 * we should have the $Data attribute loaded
		 */
		else if (type == NTFS_ATYPE_ATTRLIST) {
			if (fs_data_attrl) {
				printf ("Multiple instances of attribute lists in the same MFT\n");
				goto  errLabel;
				//  error ("I didn't realize that could happen, contact the developers");
			}
			fs_data_attrl = fs_data_lookup (fs_inode->attr, 
			  NTFS_ATYPE_ATTRLIST, getu16(fs, attr->id));
		}

	} /* end of for loop */



	/* we recalc our size everytime through here.  It is not the most
	 * effecient, but easiest with all of the processing of attribute
	 * lists and such
	 */
	fs_inode->size = 0;
	for (fs_data = fs_inode->attr; 
	  fs_data != NULL;
	  fs_data = fs_data->next) {

		if ( (fs_data->flags & FS_DATA_INUSE) == 0)
			continue;

		/* we account for the size of $Data, and directory locations */
		if ( (fs_data->type == NTFS_ATYPE_DATA) ||
		  (fs_data->type == NTFS_ATYPE_IDXROOT) ||
		  (fs_data->type == NTFS_ATYPE_IDXALLOC) )
			fs_inode->size += fs_data->size;
	}

	/* Are we currently in the process of loading $MFT? */
	if (loading_the_MFT == 1) {

		/* If we don't even have a mini cached version, get it now 
		 * Even if we are not done because of attribute lists, then we
		 * should at least have the head of the list 
		 */
		if (!ntfs->mft_data)  {

			for (fs_data = fs_inode->attr; 
			  fs_data != NULL;
		  	  fs_data = fs_data->next) {

				if ( (fs_data->flags & FS_DATA_INUSE) &&
			 	  (fs_data->type == NTFS_ATYPE_DATA) &&
			 	  (strcmp (fs_data->name, "$Data") == 0) ) {
					ntfs->mft_data = fs_data;
					break;
				}
			}
		}

		/* Update the inode count based on the current size 
		 * IF $MFT has an attribute list, this value will increase each
		 * time
		 */
		fs->inum_count = ntfs->mft_data->size / ntfs->mft_rsize_b;
		fs->last_inum = fs->inum_count - 1;
	}

	/* If there was an attribute list, process it now, we wait because
	 * the list can contain MFT entries that are described in $Data
	 * of this MFT entry.  For example, part of the $DATA attribute
	 * could follow the ATTRLIST entry, so we read it first and then 
	 * process the attribute list
	 */
	if (fs_data_attrl) 
		ntfs_proc_attrlist(ntfs, fs_inode, fs_data_attrl);
errLabel:
	return;
}


/*
 * Print the UNIX mode value in the DOS mode format
 */
static void 
print_dosmode (FILE *hFile, int mode)
{
	fprintf(hFile, "DOS Mode: ");

    if (mode & FS_INODE_DIR)
        fprintf(hFile, "Directory");  
    else
        fprintf(hFile, "File");

    
    if ((mode & (MODE_IRUSR | MODE_IRGRP | MODE_IROTH)) == 0)
        fprintf(hFile, ", Read Only");
    
    if ((mode & (MODE_IWUSR | MODE_IWGRP | MODE_IWOTH)) == 0)
        fprintf(hFile, ", Hidden");
 
    fprintf(hFile, "\n");

    return;
}



/********   Attribute List Action and Function ***********/


/* Generic Action to fill a buffer with a file_walk 
 *
 * This is used if we need to analyze a data stream, we read it into
 * a buffer first and then analyze it
 */
static char *act_buf;
static int act_bufleft;

static u_int8_t
buffer_action(FS_INFO *fs, DADDR_T addr, char *buf, int size, 
  int flags, char *ptr)
{
    int len;

    if (!act_buf)  goto  errLabel;
        //  error("The Action Buffer is NULL (?)");

    len = ((size < act_bufleft) ? size : act_bufleft);

    memcpy(act_buf, buf, len);
    act_buf = (char *)((int)act_buf + (int)len);
    act_bufleft -= len;
errLabel:
    return ((act_bufleft > 0) ? WALK_CONT : WALK_STOP);
}


/*
 * Attribute lists are used when all of the attribute  headers can not
 * fit into one MFT entry.  This contains an entry for every attribute
 * and where they are located.  We process this to get the locations
 * and then call proc_attrseq on each of those, which adds the data
 * to the fs_inode structure.
 */
static void
ntfs_proc_attrlist(NTFS_INFO *ntfs, FS_INODE *fs_inode, 
  FS_DATA *fs_data_attrlist)
{
	ntfs_attrlist *list;
	char *buf;
	DADDR_T endaddr;
	FS_INFO *fs = (FS_INFO *)&ntfs->fs_info;
	ntfs_mft *mft = (ntfs_mft *)mymalloc (ntfs->mft_rsize_b);

	u_int32_t	hist[256];
	u_int16_t	histcnt = 0;

	/*
	if (verbose)
		fprintf(logfp, "ntfs_proc_attrlist: MFT %lu\n", 
		  (ULONG)ntfs->mnum);  */

	/* Clear the contents of the history buffer */
	memset (hist, 0, sizeof(hist));
	
	/* add ourselves to the history */
	hist[histcnt++] = ntfs->mnum;


	/* Get a copy of the attribute list stream using the above action*/
	act_bufleft = (int)fs_data_attrlist->size;
	act_buf = buf = mymalloc (act_bufleft);
	endaddr = (DADDR_T)buf + fs_data_attrlist->size;

	ntfs_data_walk(ntfs, fs_data_attrlist, (FS_FLAG_ALLOC | FS_FLAG_CONT), 
	   buffer_action, "attrlist");

	/* this value should be zero, if not then we didn't read all of the
	 * buffer
	 */
	if (act_bufleft > 0)  goto  errLabel;
		//  error ("proc_attrlist: listleft > 0");

	/* Process the list & and call ntfs_proc_attr */
	for (list = (ntfs_attrlist *)buf;
	  (list) && ((DADDR_T)list < endaddr);
	  list = (ntfs_attrlist *)((int)list + getu16(fs, list->len)) )
	{
		int mftnum;
		u_int32_t type;
		u_int16_t id, i;


		/* Which MFT is this attribute in? */
		mftnum = getu48(fs, list->file_ref);

		/* Check the history to see if we have already processed this
		 * one before (if we have then we can skip it as we grabbed all
		 * of them last time
		 */
		for (i = 0; i < histcnt; i++)  {
			if (hist[i] == mftnum) 
				break;
		}

		if (hist[i] == mftnum) 
			continue;
	
		/* This is a new one, add it to the history, and process it */
		if (histcnt < 256)
			hist[histcnt++] = mftnum;


		type = getu32(fs, list->type);
		id = getu16(fs, list->id);

		/*
		if (verbose)
			fprintf(logfp, "ntfs_proc_attrlist: mft: %lu type %lu id %lu\n", 
			  (ULONG)mftnum, (ULONG)type, (ULONG)id);  */

		/* 
		 * Read the MFT entry 
		 */

		/* Sanity check. */
		if (mftnum < ntfs->fs_info.first_inum || mftnum > ntfs->fs_info.last_inum)  goto  errLabel;
			//  error("Invalid MFT file reference (%lu) in the attribute list of MFT %lu", (ULONG) mftnum, ntfs->mnum);
		
		ntfs_mft_lookup(ntfs, mft, mftnum);

		/* verify that this entry refers to the original one */
		if (getu48(fs, mft->file_ref) != ntfs->mnum) {

			/* Before we raise alarms, check if the original was
			 * unallocated.  If so, then the list entry could 
			 * have been reallocated, so we will just ignore it
			 */
			if ((getu16(fs, ntfs->mft->flags) & NTFS_MFT_INUSE) == 0)
				continue;
			else  goto  errLabel;
				//  error ("Extension record %lu (file ref = %llu) is not for attribute list of %lu",  (ULONG)mftnum, (ULONGLONG)getu48(fs, mft->file_ref), (ULONG)ntfs->mnum);
		}	
		/* 
		 * Process the attribute seq for this MFT entry and add them
		 * to the FS_INODE structure
		 */

		ntfs_proc_attrseq (ntfs, fs_inode, 
		  (ntfs_attr *) ((int)mft + (int)getu16(fs, mft->attr_off)),
	  	  ntfs->mft_rsize_b - getu16(fs, mft->attr_off));
	}
errLabel:
	free(mft);
	free(buf);

	return;
}



/*
 * Copy the MFT entry saved in ntfs->mft into the generic structure 
 */
static void
ntfs_copy_inode(NTFS_INFO *ntfs, FS_INODE *fs_inode)
{
	ntfs_mft	*mft = ntfs->mft;
	ntfs_attr	*attr;
	FS_INFO		*fs = (FS_INFO *)&ntfs->fs_info;

	/* if the attributes list has been used previously, then make sure the 
	 * flags are cleared 
	 */
	if (fs_inode->attr)
		fs_data_clear_list(fs_inode->attr);

	/* If there are any name structures allocated, then free 'em */
	if (fs_inode->name) {
		FS_NAME *fs_name1, *fs_name2;
		fs_name1 = fs_inode->name;
		while (fs_name1) {
			fs_name2 = fs_name1->next;
			free(fs_name1);
			fs_name1 = fs_name2;
		}
		fs_inode->name = NULL;
	}

	/* Set the fs_inode values from mft */
	fs_inode->nlink = getu16(fs, mft->link);
	fs_inode->seq = getu16(fs, mft->seq);

	/* Set the mode for file or directory */
	if (getu16(fs, ntfs->mft->flags) & NTFS_MFT_DIR) 
		fs_inode->mode = FS_INODE_DIR;		
	else
		fs_inode->mode = FS_INODE_REG;


	/* the following will be changed once we find the correct attribute,
	 * but initialize them now just in case 
	 */
	fs_inode->uid = 0;
	fs_inode->gid = 0;
	fs_inode->size = 0;
	fs_inode->mtime = 0;
	fs_inode->atime = 0;
	fs_inode->ctime = 0;
	fs_inode->dtime = 0;
	fs_inode->crtime = 0;

	/* add the flags */
	fs_inode->flags = ((getu16(fs, ntfs->mft->flags) & NTFS_MFT_INUSE) ?
	  FS_FLAG_ALLOC : FS_FLAG_UNALLOC);

	fs_inode->flags |= (getu16(fs, ntfs->mft->link) ? 
	  FS_FLAG_LINK : FS_FLAG_UNLINK);

	/* MFT entries are only allocated when needed, so it has been used */
	fs_inode->flags |= FS_FLAG_USED;

	/* Process the attribute sequence to fill in the fs_inode->attr
	 * list and the other info such as size and times
	 */
	attr = (ntfs_attr *) ((int)mft + (int)getu16(fs, mft->attr_off));
	ntfs_proc_attrseq (ntfs, fs_inode, attr, 
	  ntfs->mft_rsize_b - getu16(fs, mft->attr_off));

	return;
}


/*
 * Read the mft entry and put it into the ntfs->mft structure
 * Also sets the ntfs->mnum value
 */
void
ntfs_dinode_lookup(NTFS_INFO *ntfs, INUM_T mftnum)
{
	/* mft_lookup does a sanity check, so we can skip it here */
	ntfs_mft_lookup(ntfs, ntfs->mft, mftnum);
	ntfs->mnum = mftnum;

	return;
}


/*
 * return the MFT entry in the generic FS_INODE format
 */
static FS_INODE *
ntfs_inode_lookup (FS_INFO *fs, INUM_T mftnum)
{
	NTFS_INFO *ntfs = (NTFS_INFO *) fs;
	FS_INODE *fs_inode = fs_inode_alloc(NTFS_NDADDR, NTFS_NIADDR);

	/* Lookup inode and store it in the ntfs structure */
    ntfs_dinode_lookup(ntfs, mftnum);

	/* Copy the structure in ntfs to generic fs_inode */
	ntfs_copy_inode(ntfs, fs_inode);
			  
	return (fs_inode);
}




/**********************************************************************
 *
 *  Load special MFT structures into the NTFS_INFO structure
 *
 **********************************************************************/

/* The attrdef structure defines the types of attributes and gives a 
 * name value to the type number.
 *
 * We currently do not use this during the analysis (Because it has not
 * historically changed, but we do display it in fsstat 
 */
static void
ntfs_load_attrdef (NTFS_INFO *ntfs)
{
	FS_INODE *fs_inode;
	FS_DATA *fs_data;
	FS_INFO *fs = &ntfs->fs_info;

	/* if already loaded, return now */
	if (ntfs->attrdef)
		return;

    fs_inode = ntfs_inode_lookup(fs, NTFS_MFT_ATTR);
    fs_data = fs_data_lookup(fs_inode->attr, NTFS_ATYPE_DATA, 0);
    if (!fs_data)  goto  errLabel;
        //  error ("Data attribute not found in $Attr");
 
    act_bufleft = fs_data->size; 
	act_buf = mymalloc(act_bufleft);
    ntfs->attrdef = (ntfs_attrdef *)act_buf;
    
    ntfs_data_walk(ntfs, fs_data,
      FS_FLAG_ALLOC | FS_FLAG_CONT, buffer_action, "");

    if (act_bufleft)  goto  errLabel;
        //  error ("space still left after walking $Attr data");
errLabel:
	fs_inode_free(fs_inode);
	return;
}


/* 
 * return the name of the attribute type.  If the attribute has not
 * been loaded yet, it will be.
 */
void
ntfs_attrname_lookup(FS_INFO *fs, u_int16_t type, char *name, int len)
{
	NTFS_INFO *ntfs = (NTFS_INFO *)fs;
	ntfs_attrdef *attrdef;

    if (!ntfs->attrdef)
        ntfs_load_attrdef(ntfs);
    
    attrdef = ntfs->attrdef;
    
    while (getu32(fs, attrdef->type)) {
		if (getu32(fs, attrdef->type) == type) {
        	uni2ascii(attrdef->label, 128, name, len);
			return;
		}
        attrdef++;
    }
	/* If we didn't find it, then call it '?' */
	_snprintf(name, len, "?");
}


/* Load the block bitmap $Data run */
static void
ntfs_load_bmap(NTFS_INFO *ntfs)
{
	ntfs_attr *attr;
	FS_INFO *fs = &ntfs->fs_info;

	/* Get data on the bitmap */
	ntfs_dinode_lookup (ntfs, NTFS_MFT_BMAP);

    attr = (ntfs_attr *) ( (int)ntfs->mft + 
	  (int)getu16(fs, ntfs->mft->attr_off));

	/* cycle through them */
    while (((int)attr >= (int)ntfs->mft) &&
        ((int)attr <= ((int)ntfs->mft + (int)ntfs->mft_rsize_b)) &&
        (getu32(fs, attr->len) > 0 &&
        (getu32(fs, attr->type) != 0xffffffff) &&
        (getu32(fs, attr->type) != NTFS_ATYPE_DATA))) {
			attr = (ntfs_attr *)((int)attr + getu32(fs, attr->len));
    }

	/* did we get it? */
    if (getu32(fs, attr->type) != NTFS_ATYPE_DATA) goto  errLabel;
		//  error ("Error Finding Bitmap Data Attribute");

	/* convert to generic form */
	ntfs->bmap = ntfs_make_data_run(ntfs, 
	  (ntfs_runlist *) ((int)attr + getu16(fs, attr->c.nr.run_off)), NULL);
errLabel:
	return;
}


/*
 * Load the VOLUME MFT entry and the VINFO attribute so that we
 * can identify the volume version of this.  
 */
static void
ntfs_load_ver (NTFS_INFO *ntfs)
{
	FS_INFO *fs = (FS_INFO *)&ntfs->fs_info;
	FS_INODE *fs_inode;
	FS_DATA *fs_data;

	fs_inode = ntfs_inode_lookup(fs, NTFS_MFT_VOL);

	/* cache the data attribute */
	fs_data = fs_data_lookup(fs_inode->attr, NTFS_ATYPE_VINFO, 0);

	if (!fs_data)  goto  errLabel;
		//  error ("Volume Info attribute not found in $Volume");

	if ((fs_data->flags & FS_DATA_RES) && (fs_data->size)) {
		ntfs_attr_vinfo *vinfo = (ntfs_attr_vinfo *)fs_data->buf;	
		if ((vinfo->maj_ver == 1) && (vinfo->min_ver == 2))
			ntfs->ver = NTFS_VINFO_NT;
		else if ((vinfo->maj_ver == 3) && (vinfo->min_ver == 0))
			ntfs->ver = NTFS_VINFO_2K;
		else if ((vinfo->maj_ver == 3) && (vinfo->min_ver == 1))
			ntfs->ver = NTFS_VINFO_XP;
		else  goto  errLabel;
			//  error ("unknown version: %d.%d\n", vinfo->maj_ver,  vinfo->min_ver);
	}
	else  goto  errLabel;
		//  error ("VINFO is a non-resident attribute");
	
errLabel:
	fs_inode_free(fs_inode);
	return;
}


/**********************************************************************
 *
 *  Exported Walk Functions
 *
 **********************************************************************/

/*
 *
 * flag values: FS_FLAG_{UN}ALLOC, FS_FLAG_META, FS_FLAG_CONT, FS_FLAG_AONLY
 * FS_FLAG_SLACK
 *
 * a type of 0 will use $Data for files and IDXROOT for directories
 * an id of 0 will ignore the id and just find the first entry with the type
 */
void
ntfs_file_walk(FS_INFO *fs, FS_INODE *fs_inode, u_int32_t type, u_int16_t id,
	int flags, FS_FILE_WALK_FN action, char *ptr)
{
	FS_DATA *fs_data;
	NTFS_INFO *ntfs = (NTFS_INFO *)fs;

	/* no data */
	if (fs_inode->attr == NULL)
		return;

	/* there are no "meta" blocks here so return if they don't want
	 * content  
	 */
	if ((flags & FS_FLAG_CONT) == 0)
		return;

	/* if no type was given, then use DATA for files and IDXROOT for dirs */
	if (type == 0) {
		if ((fs_inode->mode & FS_INODE_FMT) == FS_INODE_DIR)
			type = NTFS_ATYPE_IDXROOT;
		else
			type = NTFS_ATYPE_DATA;
	}

	/* 
	 * Find the record with the correct type value 
	*/
	fs_data = fs_data_lookup(fs_inode->attr, type, id);
	if (!fs_data)  goto  errLabel;
		//  error ("type %i-%i not found in file", type, id);

	/* process the content */
	ntfs_data_walk(ntfs, fs_data, flags, action, ptr);
errLabel:
	return;
}





/*
 * flags: FS_FLAG_ALLOC and FS_FLAG_UNALLOC
 *
 * @@@ We should probably consider some data META, but it is tough with
 * the NTFS design ...
 */
void
ntfs_block_walk(FS_INFO *fs, DADDR_T start, DADDR_T last, int flags,
          FS_BLOCK_WALK_FN action, char *ptr)
{
	char *myname = "ntfs_block_walk";
	NTFS_INFO *ntfs = (NTFS_INFO *)fs;
	DADDR_T	addr, curaddr;
	FS_BUF *fs_buf = fs_buf_alloc(fs->block_size);	/* allocate a cluster */
	int myflags;
	int	bits_p_clust, base, curbase;
	FS_BUF *bmap = fs_buf_alloc(fs->block_size);

    /*
     * Sanity checks.
     */
	if (start < fs->start_block || start > fs->last_block)  goto  errLabel;
		//  error("%s: invalid start block number: %lu", myname, (ULONG) start);
	if (last < fs->start_block || last > fs->last_block)  goto  errLabel;
		//  error("%s: invalid last block number: %lu", myname, (ULONG) last);

	bits_p_clust = 8 * fs->block_size;

	/* identify the cluster of the bitmap for the starting location */
	curbase = start / bits_p_clust;
	curaddr = ntfs_bmap_addr (ntfs, start);
	fs_read_block(fs, bmap, fs->block_size, curaddr, "bmap");

	/* Cycle through the blocks */
	for (addr = start; addr <= last; addr++) {
		int b;
	
		/* identify the data for this address (bitmap cluster) */
		base = addr / bits_p_clust;

		/* is this the same as in the buffer? */
		if (base != curbase) {
			curbase = base;
			curaddr = ntfs_bmap_addr(ntfs, addr);
			fs_read_block(fs, bmap, fs->block_size, curaddr, "bmap");
		}

		/* identify if the cluster is allocated or not */
		b = addr % bits_p_clust;
		myflags = (((bmap->data[b/8]) & (0x1 << (b % 8)) ) ?
		  FS_FLAG_ALLOC : FS_FLAG_UNALLOC);

		if (flags & myflags) {
			fs_read_block(fs, fs_buf, fs->block_size, addr, "data block");

			if (WALK_STOP == action(fs, addr, fs_buf->data, myflags, ptr)) {
				fs_buf_free(fs_buf);
				fs_buf_free(bmap);
				return;
			}
		}
	}
errLabel:
	fs_buf_free(fs_buf);
	fs_buf_free(bmap);
	return;
}



/*
 * Unallocated inodes are determined using the INUSE flag and never
 * the link value because unused records have a link > 0
 *
 */
void
ntfs_inode_walk(FS_INFO *fs, INUM_T start, INUM_T last, int flags,
  FS_INODE_WALK_FN action, char *ptr)
{
	NTFS_INFO *ntfs = (NTFS_INFO *)fs;
	int 	myflags;
	INUM_T	mftnum;
	FS_INODE	*fs_inode = fs_inode_alloc(NTFS_NDADDR, NTFS_NIADDR);

    /*
     * Sanity checks.
     */
	if (start < fs->first_inum)  goto  errLabel;
		//  error("Starting inode number is too small (%lu)", (ULONG) start);
	if (start > fs->last_inum)  goto  errLabel;
		//  error("Starting inode number is too large (%lu)", (ULONG) start);

	if (last < fs->first_inum)  goto  errLabel;
		//  error("Ending inode number is too small (%lu)", (ULONG) last);
	if (last > fs->last_inum)  goto  errLabel;
		//  error("Ending inode number is too large (%lu)", (ULONG) last);


	for (mftnum = start; mftnum <= last; mftnum++) {

		/* read MFT entry in to NTFS_INFO */
		ntfs_dinode_lookup(ntfs, mftnum);

		/* we only want to look at base file records 
		 * (extended are because the base could not fit into one)
		 */
		if (getu48(fs, ntfs->mft->file_ref) != NTFS_MFT_BASE)
			continue;

		/* NOTE: We could add a sanity check here with the MFT bitmap
		 * to validate of the INUSE flag and bitmap are in agreement
		 */

		/* check flags */
		myflags = ((getu16(fs, ntfs->mft->flags) & NTFS_MFT_INUSE) ? 
		  FS_FLAG_ALLOC : FS_FLAG_UNALLOC);

		myflags |= (getu16(fs, ntfs->mft->link) ? 
		  FS_FLAG_LINK : FS_FLAG_UNLINK);

		/* MFT entries are only allocated when needed, so it must have 
		 * been used
		 */
		myflags |= FS_FLAG_USED;

		if ((flags & myflags) != myflags)
			continue;


		/* copy into generic format */
		ntfs_copy_inode(ntfs, fs_inode);

		/* call action */
		if (WALK_STOP == action(fs, mftnum, fs_inode, myflags, ptr)) {
			fs_inode_free(fs_inode);
			return;
		}
	}
errLabel:
	fs_inode_free(fs_inode);
	return;
}




static void
ntfs_fsstat(FS_INFO *fs, FILE *hFile)
{
	NTFS_INFO *ntfs = (NTFS_INFO *)fs;
	FS_INODE *fs_inode;
	FS_DATA *fs_data;
	char asc[128];
	ntfs_attrdef *attrdeftmp;

    fprintf(hFile, "FILE SYSTEM INFORMATION\n");
	fprintf(hFile, "--------------------------------------------\n");

	fprintf(hFile, "File System Type: NTFS\n");

	fprintf(hFile, "Volume Serial Number: %X%X\n", 
	  (u_int32_t)(getu64(fs, ntfs->fs->serial) & 0xffffffff00000000 >> 32),
	  (u_int32_t)getu64(fs, ntfs->fs->serial) & 0xffffffff);


	/*
	 * Volume 
	 */
	fs_inode = ntfs_inode_lookup(fs, NTFS_MFT_VOL);
	fs_data = fs_data_lookup(fs_inode->attr, NTFS_ATYPE_VNAME, 0);
	if (!fs_data)  goto  errLabel;
		//  error ("Volume Name attribute not found in $Volume");
	
	if ((fs_data->flags & FS_DATA_RES) && (fs_data->size)) {
		uni2ascii(fs_data->buf, fs_data->size, asc, 128);
		fprintf(hFile, "Volume Name: %s\n", asc);
	}

	fs_inode_free(fs_inode);
	fs_inode = NULL;
	fs_data = NULL;


	if (ntfs->ver == NTFS_VINFO_NT)
		fprintf(hFile, "Version: Windows NT\n");
	else if (ntfs->ver == NTFS_VINFO_2K)
		fprintf(hFile, "Version: Windows 2000\n");
	else if (ntfs->ver == NTFS_VINFO_XP)
		fprintf(hFile, "Version: Windows XP\n");


    fprintf(hFile, "\nMETA-DATA INFORMATION\n");
    fprintf(hFile, "--------------------------------------------\n");

    fprintf(hFile, "Range: %lu - %lu\n", (ULONG)fs->first_inum,
      (ULONG)fs->last_inum);
    fprintf(hFile, "Root Directory: %lu\n", (ULONG)fs->root_inum);


    fprintf(hFile, "\nCONTENT-DATA INFORMATION\n");
    fprintf(hFile, "--------------------------------------------\n");
    fprintf(hFile, "Sector Size: %d\n", ntfs->ssize_b);
    fprintf(hFile, "Cluster Size: %d\n", ntfs->csize_b);

    fprintf(hFile, "Total Cluster Range: %lu - %lu\n", 
	  (ULONG)fs->start_block,
      (ULONG)fs->last_block);

	
	/* 
	 * Attrdef Info 
	 */
	fprintf(hFile, "\nAttribute Defs (MFT Entry: %d)\n", NTFS_MFT_ATTR);

	if (!ntfs->attrdef)
		ntfs_load_attrdef(ntfs);

	attrdeftmp = ntfs->attrdef;

	while (getu32(fs, attrdeftmp->type)) {
		uni2ascii(attrdeftmp->label, 128, asc, 128);
		printf("%s: %d\n", asc, getu32(fs, attrdeftmp->type));

		attrdeftmp++;
	}
errLabel:
	return;
}


/************************* istat *******************************/
  
static int printidx = 0;
#define WIDTH   8
 
 
static u_int8_t
print_addr_act (FS_INFO *fs, DADDR_T addr, char *buf,
  int size, int flags, char *ptr) 
{
    FILE *hFile = (FILE *)ptr; 
 
    fprintf(hFile, "%lu ", (ULONG) addr);
 
    if (++printidx == WIDTH) { 
        fprintf(hFile, "\n");
        printidx = 0;
    }
   
    return WALK_CONT;
}


static void
ntfs_istat (FS_INFO *fs, FILE *hFile, INUM_T inum, int numblock, 
  int32_t sec_skew)
{
    FS_INODE *fs_inode;
	FS_DATA *fs_data;
    int flags = (FS_FLAG_CONT | FS_FLAG_AONLY | FS_FLAG_SLACK |
      FS_FLAG_ALLOC | FS_FLAG_UNALLOC);

    fs_inode = ntfs_inode_lookup (fs, inum);
    fprintf(hFile, "MFT Entry: %lu\n", (ULONG) inum);
	fprintf(hFile, "Sequence: %lu\n", (ULONG) fs_inode->seq);
    fprintf(hFile, "%sAllocated\n",
      (fs_inode->flags&FS_FLAG_ALLOC)?"":"Not ");

	fprintf(hFile, "UID: %d\n", (int)fs_inode->uid);

    print_dosmode(hFile, fs_inode->mode);
   
    fprintf(hFile, "Size: %lu\n", (ULONG) fs_inode->size);
    fprintf(hFile, "Links: %lu\n", (ULONG) fs_inode->nlink);

    if (fs_inode->name) {
        FS_NAME *fs_name = fs_inode->name;
        fprintf(hFile, "Name: ");
        while (fs_name) {
            fprintf(hFile, "%s", fs_name->name);
            fs_name = fs_name->next;
            if (fs_name)
                fprintf(hFile, ", ");
            else
                fprintf(hFile, "\n");
        }
    }

	/* Standard Info Times */
    if (sec_skew != 0) {
		fprintf(hFile, "\nAdjusted $STANDARD_INFORMATION Times:\n");
        fs_inode->mtime -= sec_skew;
        fs_inode->atime -= sec_skew;
        fs_inode->ctime -= sec_skew;
        fs_inode->crtime -= sec_skew;
   
    	fprintf(hFile, "Created:\t%s", ctime(&fs_inode->crtime));
    	fprintf(hFile, "File Modified:\t%s", ctime(&fs_inode->mtime));
    	fprintf(hFile, "MFT Modified:\t%s", ctime(&fs_inode->ctime));
    	fprintf(hFile, "Accessed:\t%s", ctime(&fs_inode->atime));

        fs_inode->mtime += sec_skew;
        fs_inode->atime += sec_skew;
        fs_inode->ctime += sec_skew;
        fs_inode->crtime += sec_skew;

		fprintf(hFile, "\nOriginal $STANDARD_INFORMATION Times:\n");
    }
    else
		fprintf(hFile, "\n$STANDARD_INFORMATION Times:\n");

    fprintf(hFile, "Created:\t%s", ctime(&fs_inode->crtime));
    fprintf(hFile, "File Modified:\t%s", ctime(&fs_inode->mtime));
    fprintf(hFile, "MFT Modified:\t%s", ctime(&fs_inode->ctime));
    fprintf(hFile, "Accessed:\t%s", ctime(&fs_inode->atime));

	/* fname Times */
	fs_data = fs_data_lookup(fs_inode->attr, NTFS_ATYPE_FNAME, 0);
	if(fs_data) {
        ntfs_attr_fname *fname = (ntfs_attr_fname *)fs_data->buf;
		time_t cr_time, m_time, c_time, a_time;


		cr_time = nt2unixtime(getu64(fs, fname->crtime));
        /* altered - modified */
		m_time = nt2unixtime(getu64(fs, fname->mtime));
        /* MFT modified */
		c_time = nt2unixtime(getu64(fs, fname->ctime));
        /* Access */
		a_time = nt2unixtime(getu64(fs, fname->atime));

    	if (sec_skew != 0) {
        	fprintf(hFile, "\nAdjusted $FILE_NAME Times:\n");
        	cr_time -= sec_skew;
        	m_time -= sec_skew;
        	a_time -= sec_skew;
        	c_time -= sec_skew;

			fprintf(hFile, "Created:\t%s", ctime(&cr_time));
			fprintf(hFile, "File Modified:\t%s", ctime(&m_time));
			fprintf(hFile, "MFT Modified:\t%s", ctime(&c_time));
			fprintf(hFile, "Accessed:\t%s", ctime(&a_time));

        	cr_time += sec_skew;
        	m_time += sec_skew;
        	a_time += sec_skew;
        	c_time += sec_skew;

        	fprintf(hFile, "\nOriginal $FILE_NAME Times:\n");
		}
		else
        	fprintf(hFile, "\n$FILE_NAME Times:\n");


    	fprintf(hFile, "Created:\t%s", ctime(&cr_time));
    	fprintf(hFile, "File Modified:\t%s", ctime(&m_time));
    	fprintf(hFile, "MFT Modified:\t%s", ctime(&c_time));
    	fprintf(hFile, "Accessed:\t%s", ctime(&a_time));

/*
        printf ("fsize: %lu  Alloc size: %lu\n",
		  getu64(fs, fname->real_fsize),
		  getu64(fs, fname->alloc_fsize));
*/

    }

    fs_data = fs_inode->attr;

    fprintf(hFile, "\nAttributes: \n");
    while ((fs_data) && (fs_data->flags & FS_DATA_INUSE)) {
        char type[256];
    
        ntfs_attrname_lookup(fs, fs_data->type, type, 256);

        printf("Type: %s (%i-%i)   Name: %s   %sResident   size: %d\n",
          type, fs_data->type, fs_data->id, fs_data->name,
          (fs_data->flags & FS_DATA_NONRES)?"Non-":"", (int)fs_data->size);
    
        if (fs_data->flags & FS_DATA_NONRES) {
            printidx = 0;

            fs->file_walk(fs, fs_inode, fs_data->type, fs_data->id, flags,
               print_addr_act, (char *)hFile);
            if (printidx != 0)
                printf("\n");
        }

        fs_data = fs_data->next;
    }

	fs_inode_free (fs_inode);

    return;
}

static void
ntfs_close(FS_INFO *fs)
{
    NTFS_INFO *ntfs = (NTFS_INFO *)fs;
    close(fs->fd);
	free((char *)ntfs->mft);
	free((char *)ntfs->fs);
	fs_data_run_free(ntfs->bmap);
	fs_inode_free(ntfs->mft_inode);
    free(fs);
}




 FS_INFO  *  ntfs_open(  const  char  *  name,  unsigned  char  ftype  )
{
	char		*		myname	=  "ntfs_open";
	NTFS_INFO	*		ntfs	=  (NTFS_INFO *)mymalloc(sizeof(*ntfs));
	FS_INFO		*		fs		=  NULL;	//  &(ntfs->fs_info);
	int					len;
	DWORD				numberOfBytesRead;
	BOOL				bRet	=  FALSE;

	if  (  !ntfs  )  goto  errLabel;
	fs  =  &ntfs->fs_info;

	loading_the_MFT = 0;

	if ((ftype & FSMASK) != NTFS_TYPE)  goto  errLabel;

    if  (  (  fs->fd  =  CreateFile(	name,  
										GENERIC_READ,   
										FILE_SHARE_READ | FILE_SHARE_WRITE,  
										NULL,  
										OPEN_EXISTING,  
										0,  
										NULL  )  )  
			==  INVALID_HANDLE_VALUE  )  
	{
		goto  errLabel;
	}

    fs->ftype = ftype;
    fs->flags = FS_HAVE_SEQ;

	len = roundup(sizeof(ntfs_sb), NTFS_DEV_BSIZE);
	ntfs->fs = (ntfs_sb *) mymalloc(len);

	if (  !(  ReadFile(	fs->fd,  ntfs->fs,  len,  &numberOfBytesRead,  NULL  )  )  )
	{
		GetLastError(  );  goto  errLabel;  
	}

//    if (read(fs->fd, (char *) ntfs->fs, len) != len)  goto  errLabel;
		//  error("%s: read superblock: %m", name);

	/* Check the magic value */
	if (guessu32(fs, ntfs->fs->magic, NTFS_FS_MAGIC))  goto  errLabel;
           //  error("Error: %s is not a NTFS file system", name);

	/*
     * block calculations : although there are no blocks in ntfs,
	 * we are using a cluster as a "block"
	 */
	
	ntfs->ssize_b = getu16(fs, ntfs->fs->ssize);
	ntfs->csize_b = ntfs->fs->csize * ntfs->ssize_b;
    fs->start_block = 0;

	/* This field is defined as 64-bits but according to the
	 * NTFS drivers in Linux, windows only uses 32-bits
	 */
    fs->block_count = (DADDR_T)getu32(fs, ntfs->fs->vol_size_s) / ntfs->fs->csize;
    fs->last_block = fs->block_count - 1;
    fs->block_size = ntfs->csize_b;
    fs->file_bsize = fs->block_size;
    fs->addr_bsize = 0;
    fs->block_frags = 1;
    fs->dev_bsize = NTFS_DEV_BSIZE;


	if (ntfs->fs->mft_rsize_c > 0)
		ntfs->mft_rsize_b = ntfs->fs->mft_rsize_c * ntfs->csize_b;
	else
		/* if the mft_rsize_c is not > 0, then it is -log2(rsize_b) */
		ntfs->mft_rsize_b = 1 << -ntfs->fs->mft_rsize_c;

	if (ntfs->fs->idx_rsize_c > 0)
		ntfs->idx_rsize_b = ntfs->fs->idx_rsize_c * ntfs->csize_b;
	else
		/* if the idx_rsize_c is not > 0, then it is -log2(rsize_b) */
		ntfs->idx_rsize_b = 1 << -ntfs->fs->idx_rsize_c;

	ntfs->root_mft_addr = getu64(fs, ntfs->fs->mft_clust) * ntfs->csize_b;

    /*
     * Other initialization: caches, callbacks.
     */
    fs->seek_pos = -1;
   
    fs->inode_walk = ntfs_inode_walk;
    fs->block_walk = ntfs_block_walk;
    fs->file_walk = ntfs_file_walk;
    fs->inode_lookup = ntfs_inode_lookup;
    fs->dent_walk = ntfs_dent_walk;
	fs->fsstat = ntfs_fsstat;
	fs->istat = ntfs_istat;
    fs->close = ntfs_close;


	/*
	 * inode
	 */

	/* allocate the buffer to hold mft entries */

	ntfs->mft = (ntfs_mft *) mymalloc(ntfs->mft_rsize_b);
	ntfs->mnum = 0;

	fs->root_inum = NTFS_ROOTINO;
	fs->first_inum = NTFS_FIRSTINO;
	fs->last_inum = NTFS_LAST_DEFAULT_INO;
	ntfs->mft_data = NULL;


	/* load the data run for the MFT table into ntfs->mft */
	loading_the_MFT = 1;
	ntfs_mft_lookup(ntfs, ntfs->mft, NTFS_MFT_MFT);

    ntfs->mft_inode = fs_inode_alloc(NTFS_NDADDR, NTFS_NIADDR);
    ntfs_copy_inode(ntfs, ntfs->mft_inode);

    /* cache the data attribute 
	 *
	 * This will likely be done already by proc_attrseq, but this
	 * should be quick
	 */
    ntfs->mft_data = fs_data_lookup(ntfs->mft_inode->attr, NTFS_ATYPE_DATA, 0);
    if (!ntfs->mft_data) goto  errLabel;
        //  error ("Data Attribute not found in $MFT");


	/* Get the inode count based on the table size */
	fs->inum_count = ntfs->mft_data->size / ntfs->mft_rsize_b;
	fs->last_inum = fs->inum_count - 1;

	/* reset the flag that we are no longer loading $MFT */
	loading_the_MFT = 0;

	/* load the version of the file system */
	ntfs_load_ver(ntfs);

	/* load the data block bitmap data run into ntfs_info */
	ntfs_load_bmap(ntfs);

	/* set this to NULL and it will be loaded if needed */
	ntfs->attrdef = NULL;
	
	if  (  verbose  )  {
		traceLogA(  "ssize: %d csize: %d serial: %x\n",
					getu16(fs, ntfs->fs->ssize), ntfs->fs->csize,
					(int)getu64(fs, ntfs->fs->serial));
		traceLogA(  "mft_rsize: %d idx_rsize: %d vol: %d mft: %d mft_mir: %d\n",
					ntfs->mft_rsize_b, 
					ntfs->idx_rsize_b, (int)fs->block_count,
					(int)getu64(fs, ntfs->fs->mft_clust), 
					(int)getu64(fs, ntfs->fs->mftm_clust));
	}
	
	bRet  =  TRUE;

errLabel:
	
	return  bRet  ?  fs  :  NULL;

}


