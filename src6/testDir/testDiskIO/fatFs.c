#include  "diskIO.h"
#include  "fatFs.h"
#include  "mymalloc.h"
#include  "error.h"

static int32_t	secwest;	/* Number of seconds west of UTC for time
							* conversions */


/*
 * Return the entry in the File Allocation Table (FAT) for the given 
 * cluster
 *
 * The appropriate entry size is then called
 *
 */
static u_int32_t 
getFAT(FATFS_INFO *fatfs, u_int32_t clust)
{
	u_int8_t *ptr;
	u_int16_t tmp16;
	u_int32_t retval = 0;
	FS_INFO *fs = (FS_INFO *) & fatfs->fs_info;
	DADDR_T	sect, offs;

	/* plus 1 because the first cluster starts at 2 */
	if (clust > fatfs->clustcnt + 1)
		return 0;

	switch (fatfs->fs_info.ftype) {
	  case MS12_FAT:
		if (clust & 0xf000)  goto  errLabel;
			//  error("getFAT: FAT12 Cluster too large ");

		/* id the sector in the FAT */
		sect = fatfs->firstfatsect + (clust + clust / 2) / fatfs->ssize;

		/* Load the FAT if we don't have it */
		if ((sect < fatfs->table->addr) || 
		  (sect >= (fatfs->table->addr + FAT_CACHE_S)) ||
		  (-1 == fatfs->table->addr) ) {
			fs_read_block (fs, fatfs->table, FAT_CACHE_B, sect, "");
		}

		/* get the offset into the cache */
		offs = (sect - fatfs->table->addr)*fatfs->ssize + 
		  (clust + clust / 2) % fatfs->ssize; 

		/* special case when the 12-bit value goes across the cache
		 * we load the cache to start at this sect.  The cache
		 * size must therefore be at least 2 sectors large 
		 */
		if (offs == (FAT_CACHE_B - 1) )  {
			fs_read_block (fs, fatfs->table, FAT_CACHE_B, sect, "");

			offs = (sect - fatfs->table->addr)*fatfs->ssize + 
			  (clust + clust / 2) % fatfs->ssize; 
		}

		/* get pointer to entry in current buffer */
		ptr = fatfs->table->data + offs;

		tmp16 = getu16(fs, ptr);

		/* slide it over if it is one of the odd clusters */
		if (clust & 1)
			tmp16 >>= 4;

		retval = tmp16 & FATFS_12_MASK;

		/* sanity check */
		if ((retval > (fatfs->clustcnt + 1)) &&
		  (retval < (0x0ffffff7 & FATFS_12_MASK)))  goto  errLabel;
			//  error ("getFAT: return FAT12 cluster too large");

		break;

	  case MS16_FAT:
		/* Get sector in FAT for cluster and load it if needed */
		sect = fatfs->firstfatsect + (clust * 2) / fatfs->ssize;
		if ((sect < fatfs->table->addr) || 
		  (sect >= (fatfs->table->addr + FAT_CACHE_S)) ||
		  (-1 == fatfs->table->addr) ) 
			fs_read_block (fs, fatfs->table, FAT_CACHE_B, sect, "");

		/* get pointer to entry in current buffer */
		ptr = fatfs->table->data +
		  (sect - fatfs->table->addr)*fatfs->ssize + 
		  (clust * 2) % fatfs->ssize; 

		retval = getu16(fs, ptr) & FATFS_16_MASK;

		/* sanity check */
		if ((retval > (fatfs->clustcnt + 1)) &&
		  (retval < (0x0ffffff7 & FATFS_16_MASK)))  goto  errLabel;
			//  error ("getFAT: return FAT16 cluster too large");

		break;

	  case MS32_FAT:
		/* Get sector in FAT for cluster and load if needed */
		sect = fatfs->firstfatsect + (clust * 4) / fatfs->ssize;
		if ((sect < fatfs->table->addr) || 
		  (sect >= (fatfs->table->addr + FAT_CACHE_S)) ||
		  (-1 == fatfs->table->addr) ) 
			fs_read_block (fs, fatfs->table, FAT_CACHE_B, sect, "");


		/* get pointer to entry in current buffer */
		ptr = fatfs->table->data +
		  (sect - fatfs->table->addr)*fatfs->ssize + 
		  (clust * 4) % fatfs->ssize; 

		retval = getu32(fs, ptr) & FATFS_32_MASK;

		/* sanity check */
		if ((retval > fatfs->clustcnt + 1) &&
		  (retval < (0x0ffffff7 & FATFS_32_MASK))) goto  errLabel;
			//error ("getFAT: return cluster too large");
		
		break;
	}
errLabel:
	return retval;
}

/*
 * Macro to identify if a cluster is allocated
 * returns 1 if it is allocated and 0 if not
 */
#define is_clustalloc(fs, c) \
	(getFAT((fs), (c)) != FATFS_UNALLOC)

/* 
 * Identifies if a sector is allocated
 *
 * If it is less than the data area, then it is allocated
 * else the FAT table is consulted
 *
 */
static u_int8_t
is_sectalloc(FATFS_INFO *fatfs, int sect) 
{
	/* If less than the first cluster sector, then it is allocated 
	 * otherwise check the FAT
	*/
	if (sect < fatfs->firstclustsect)
		return 1;

	/* 2 + is because clusters start at 2 */
	return is_clustalloc(fatfs, 
	  2 + ((sect - fatfs->firstclustsect) / fatfs->csize));
}

/* 
 * Identify if the dentry is a valid 8.3 name
 *
 * returns 1 if it is, 0 if it does not
 */
static u_int8_t
is_83_name(fatfs_dentry *de) 
{
	if (!de)
		return 0;

	/* The IS_NAME macro will fail if the value is 0x05, which is only
	 * valid in name[0], similarly with '.' */
	if ((de->name[0] != FATFS_SLOT_E5) && (de->name[0] != '.') && 
	  (de->name[0] != FATFS_SLOT_DELETED) && 
	  (FATFS_IS_83_NAME(de->name[0]) == 0))
			return 0;

	/* the second name field can only be . if the first one is a . */
	if (de->name[1] == '.') {
		if (de->name[0] != '.') 
			return 0;
	}
	else if (FATFS_IS_83_NAME(de->name[1]) == 0)
			return 0;

	if ( 
	  (FATFS_IS_83_NAME(de->name[2]) == 0) ||
	  (FATFS_IS_83_NAME(de->name[3]) == 0) || 
	  (FATFS_IS_83_NAME(de->name[4]) == 0) ||
	  (FATFS_IS_83_NAME(de->name[5]) == 0) ||
	  (FATFS_IS_83_NAME(de->name[6]) == 0) ||
	  (FATFS_IS_83_NAME(de->name[7]) == 0) ||
	  (FATFS_IS_83_NAME(de->ext[0]) == 0) || 
	  (FATFS_IS_83_NAME(de->ext[1]) == 0) || 
	  (FATFS_IS_83_NAME(de->ext[2]) == 0) )
		return 0;
	else
		return 1;
}

/*
 * Check if the given lfn entry has a valid long name
 * We are only looking at the ASCII equivalent of UNICODE
 *
 * The char set for lfn is larger than that of 8.3
 *
 * return 1 if valid name, 0 if not
 */
static u_int8_t
is_lfn_name(fatfs_dentry_lfn *de) 
{
	int i;
	if (!de)
		return 0;

	for (i=0; i < 10; i+=2) 
		if (FATFS_IS_LFN_NAME(de->part1[i]) == 0)
			return 0;
  	for (i=0; i < 12; i+=2) 
		if (FATFS_IS_LFN_NAME(de->part2[i]) == 0)
			return 0;
	for (i=0; i < 4; i+=2) 
		if (FATFS_IS_LFN_NAME(de->part3[i]) == 0)
			return 0;

	return 1;
}



/**************************************************************************
 *
 * BLOCK WALKING
 * 
 *************************************************************************/
/* 
** Walk the sectors of the partition. 
**
** NOTE: This is by SECTORS and not CLUSTERS
** _flags_ is only used for FS_FLAG_ALLOC / FS_FLAG_UNALLOC / FS_FLAG_META
**
*/
void
fatfs_block_walk(FS_INFO *fs, DADDR_T start, DADDR_T last, int flags,
          FS_BLOCK_WALK_FN action, char *ptr)
{
    char   		*myname = "fatfs_block_walk";
    FATFS_INFO 	*fatfs = (FATFS_INFO *) fs;
    FS_BUF 		*fs_buf = fs_buf_alloc(fs->block_size);
    DADDR_T 	addr;
    int     	myflags;

    /*
     * Sanity checks.
     */
    if (start < fs->start_block || start > fs->last_block)
        //  error("%s: invalid start block number: %lu", myname, (ULONG) start);
    if (last < fs->start_block || last > fs->last_block)
        //  error("%s: invalid last block number: %lu", myname, (ULONG) last);

	/* cycle through block addresses */
	for (addr = start; addr <= last; addr++) {

		/* Identify its allocation status */
		myflags = ((is_sectalloc(fatfs, addr)) ?
			FS_FLAG_ALLOC : FS_FLAG_UNALLOC);

		/* Anything less than the first data sector is either the FAT 
		 * tables or super block stuff - therefore meta
		 */
		if (addr < fatfs->firstdatasect)
			myflags |= FS_FLAG_META;

		if ((flags & myflags) == myflags) {
			fs_read_block(fs, fs_buf, fs->block_size, addr, "data block");
			if (WALK_STOP == action(fs, addr, fs_buf->data, myflags, ptr)) {
				fs_buf_free(fs_buf);
				return;
			}	
		}
	}

	fs_buf_free(fs_buf);
	return;
}

/*
** Convert the DOS time to the UNIX version
** 
** UNIX stores the time in seconds from 1970 in UTC
** FAT dates are the actual date with the year relative to 1980
** 
** Modified version from OpenBSD source in:
** src/sys/msdosfs/msdosfs_conv.c by Paul Popelka 
*/
static int
dos2unixtime(u_int16_t date, u_int16_t time)
{
    u_long seconds, lastseconds;
    u_long m, month;
    u_long y, year;
    u_long days;
    u_short *months;

	/* Days in each month in a regular year */
	u_short regyear[] = {
		31, 28, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31
	};
           
	/* Days in each month in a leap year */
	u_short leapyear[] = {  
		31, 29, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31
	};

    if (date == 0) 
        return 0;

	/* number of seconds in the last day */
    seconds = ((time & FATFS_SEC_MASK) >> FATFS_SEC_SHIFT) * 2
        + ((time & FATFS_MIN_MASK) >> FATFS_MIN_SHIFT) * 60
        + ((time & FATFS_HOUR_MASK) >> FATFS_HOUR_SHIFT) * 3600;

	/* Number of days, based on years */
	days = 0;
	year = (date & FATFS_YEAR_MASK) >> FATFS_YEAR_SHIFT;
	for (y = 0; y < year; y++)
		days += y & 0x03 ? 365 : 366;

	/* Is the current year a leap year? */
	months = year & 0x03 ? regyear : leapyear;

	/*
	 * Prevent going from 0 to 0xffffffff in the following
	 * loop.
	 */
	month = (date & FATFS_MON_MASK) >> FATFS_MON_SHIFT;
	if (month == 0) {
		printf("dos2unixtime(): month value out of range (%ld)\n",
			month);
		month = 1;
	}

	/* days based on number of months so far this year */
	for (m = 0; m < month - 1; m++)
		days += months[m];
	days += ((date & FATFS_DAY_MASK) >> FATFS_DAY_SHIFT) - 1;

#define SECONDSTO1980   (((8 * 365) + (2 * 366)) * (24 * 60 * 60))

	lastseconds = (days * 24 * 60 * 60) + SECONDSTO1980;

	/* add up everything
	 * we need the timezone data because FAT gives the exact time and
	 * has no notion of timezones.  So, we must manually figure it out
	 */
    return seconds + lastseconds + secwest;
         /* -+ daylight savings time correction */ ;

}

static void set_secwest(void)
{
    struct  tm *tmptr;
    time_t t;

    t = time(NULL);
    tmptr = localtime(&t);

	/*
#if HAVE_TIMEZONE
#if defined (CYGWIN)
    secwest = _timezone;
#else
    secwest = timezone;
#endif
	/* account for daylight savings *//*
    if (tmptr->tm_isdst)
        secwest -= 3600;
#else
    secwest = -1 * tmptr->tm_gmtoff;
#endif
	*/
}


/* 
 * convert the attribute list in FAT to a UNIX mode 
 */
static int
dos2unixmode(u_int16_t attr)
{
	int mode;

	/* every file is executable */
	mode = (MODE_IXUSR | MODE_IXGRP | MODE_IXOTH);

	/* file type */
	if (attr & FATFS_ATTR_DIRECTORY)
		mode |= FS_INODE_DIR;
	else
		mode |= FS_INODE_REG;

	if ((attr & FATFS_ATTR_READONLY) == 0)
		mode |= (MODE_IRUSR | MODE_IRGRP | MODE_IROTH);

	if ((attr & FATFS_ATTR_HIDDEN) == 0)
		mode |= (MODE_IWUSR | MODE_IWGRP | MODE_IWOTH);

	return mode;
}


static void
print_dosmode (FILE *hFile, int mode) 
{
    fprintf(hFile, "DOS Mode: ");

	if (mode & FS_INODE_DIR) 
		//  fprintf(hFile, "Directory");
		traceLogA(  "Directory"  );
	else
		//  fprintf(hFile, "File");
		traceLogA(  "File"  );


	if ((mode & (MODE_IRUSR | MODE_IRGRP | MODE_IROTH)) == 0)
		fprintf(hFile, ", Read Only");

	if ((mode & (MODE_IWUSR | MODE_IWGRP | MODE_IWOTH)) == 0)
		fprintf(hFile, ", Hidden");

	fprintf(hFile, "\n");

	return;
}



/*
 * Copy the contents of a dentry into a FS_INFO structure
 */
static void
fatfs_copy_inode(FATFS_INFO *fatfs, FS_INODE *fs_inode)
{
    fatfs_dentry    *in = fatfs->dep;
	int 		cnum, i;
	u_int32_t 	mask = 0, dcnt, clust;
	int32_t		size;
	FS_INFO *fs = (FS_INFO *)&fatfs->fs_info;

	fs_inode->mode = dos2unixmode(in->attrib);

	/* There is no notion of link in FAT, just deleted or not */
	fs_inode->nlink = (in->name[0] == FATFS_SLOT_DELETED)? 0 : 1;

    fs_inode->size = size = getu32(fs, in->size);

	/* No notion of UID, so set it to 0 */ 
    fs_inode->uid = 0;
    fs_inode->gid = 0;

	/* If these are valid dates, then convert to a unix date format */
	if (FATFS_ISDATE(getu16(fs, in->wdate)))
    	fs_inode->mtime = dos2unixtime(getu16(fs, in->wdate), 
		  getu16(fs, in->wtime));
	else
		fs_inode->mtime = 0;

	if (FATFS_ISDATE(getu16(fs, in->adate)))
    	fs_inode->atime = dos2unixtime(getu16(fs, in->adate), 0);
	else
		fs_inode->atime = 0;


	/* cdate is the creation date in FAT and there is no change,
	 * so we just put in into change and set create to 0.  The other
	 * front-end code knows how to handle it and display it
	 */
	if (FATFS_ISDATE(getu16(fs, in->cdate)))
    	fs_inode->ctime = 
		  dos2unixtime(getu16(fs, in->cdate), getu16(fs, in->ctime));
	else
		fs_inode->ctime = 0;

    fs_inode->crtime = 0;
    fs_inode->dtime = 0;

	fs_inode->seq = 0;

	/* 
	 * add the 8.3 file name 
	 */
	if (fs_inode->name == NULL) {
		fs_inode->name = (FS_NAME *)mymalloc(sizeof(FS_NAME));	
		fs_inode->name->next = NULL;
	}

	for (i = 0; (i < 8) && (in->name[i] != 0) && (in->name[i] != ' '); 
	  i++) {
		if ((i == 0) && (in->name[0] == FATFS_SLOT_DELETED))
			fs_inode->name->name[0] = '_';
		else if ((in->lowercase & FATFS_CASE_LOWER_BASE) && 
		  (in->name[i] >= 'A') && (in->name[i] <= 'Z'))
			fs_inode->name->name[i] = in->name[i] + 32;
		else
			fs_inode->name->name[i] = in->name[i];
	}

	if ((in->ext[0]) && (in->ext[0] != ' ')) {
		int a;
		fs_inode->name->name[i++] = '.';
		for (a = 0 ; (a < 3) && (in->ext[a] != 0) && (in->ext[a] != ' '); 
		  a++, i++) {
			if ((in->lowercase & FATFS_CASE_LOWER_EXT) && 
		  	  (in->ext[a] >= 'A') && (in->ext[a] <= 'Z'))
				fs_inode->name->name[i] = in->ext[a] + 32;
			else	
				fs_inode->name->name[i] = in->ext[a];
		}
	}
	fs_inode->name->name[i] = '\0';


	/* get the mask */
	if (fatfs->fs_info.ftype == MS16_FAT)
		mask = FATFS_16_MASK;
	else if (fatfs->fs_info.ftype == MS32_FAT)
		mask = FATFS_32_MASK;
	else if (fatfs->fs_info.ftype == MS12_FAT)
		mask = FATFS_12_MASK;


	/* get the starting cluster */
	fs_inode->direct_addr[0] = FATFS_DENTRY_CLUST(fs, in) & mask;

	/* wipe the remaining fields */
	for (dcnt = 1 ; dcnt < fs_inode->direct_count; dcnt++)
		fs_inode->direct_addr[dcnt] = 0;
	for (dcnt = 0 ; dcnt < fs_inode->indir_count; dcnt++)
		fs_inode->indir_addr[dcnt] = 0;

	/* FAT does not store a size for its directories so make one based
	 * on the number of allocated sectors 
	 */
	if (in->attrib & FATFS_ATTR_DIRECTORY) {

		/* count the total number of clusters in this file */
		clust = FATFS_DENTRY_CLUST(fs, in);
		cnum = 0;
		while ((clust) && (0 == FATFS_ISEOF(clust, mask))) {
			cnum++;
			clust = getFAT(fatfs, clust);
		}

		/* we are going to store the sectors, not clusters so calc
		 * that value 
		 */
		fs_inode->size = cnum * fatfs->csize * fatfs->ssize;

	}

	fs_inode->flags = ((in->name[0] == FATFS_SLOT_DELETED)?
	  FS_FLAG_UNALLOC : FS_FLAG_ALLOC);

	fs_inode->flags |= FS_FLAG_USED;

	return;
}

/*
 * Since FAT does not give an 'inode' or directory entry to the
 * root directory, this function makes one up for it 
 */
void
fatfs_make_root(FATFS_INFO *fatfs, FS_INODE *fs_inode)
{
	int 		snum, cnum, i;
	u_int32_t 	clust;

	fs_inode->mode = (FS_INODE_DIR);

	fs_inode->nlink =  1;

    fs_inode->uid = fs_inode->gid = 0;
	fs_inode->mtime = fs_inode->atime = fs_inode->ctime = fs_inode->dtime = 0;

	for (i = 1; i < fs_inode->direct_count; i++) 
		fs_inode->direct_addr[i] = 0;

	/* FAT12 and FAT16 don't use the FAT for root directory, so 
	 * we will have to fake it.
	 */
	if (fatfs->fs_info.ftype != MS32_FAT) {

		/* Other code will have to check this as a special condition 
		 */
		fs_inode->direct_addr[0] = 1;

		/* difference between end of FAT and start of clusters */
    	snum = fatfs->firstclustsect - fatfs->firstdatasect;

		/* number of bytes */
    	fs_inode->size = snum * fatfs->ssize; 

		return;
	}
	else {
		/* Get the number of allocated clusters */

		/* base cluster */
		clust = 2 + (fatfs->rootsect - fatfs->firstclustsect) / fatfs->csize;
		fs_inode->direct_addr[0] = clust;

		cnum = 0;
		while ((clust) && (0 == FATFS_ISEOF(clust, FATFS_32_MASK))) {
			cnum++;
			clust = getFAT(fatfs, clust);
		}

    	fs_inode->size = cnum * fatfs->csize * fatfs->ssize; 
	}
}



/* 
 * Is the pointed to buffer a directory entry buffer? 
 *
 * Returns 1 if it is, 0 if not
 */
u_int8_t
fatfs_isdentry(FATFS_INFO *fatfs, fatfs_dentry *de) 
{
	FS_INFO *fs = (FS_INFO *)&fatfs->fs_info;
	if (!de)
		return 0;

	/* volume labels will not have these values 
	 * same with LFN, but this check will take care of them too	
	*/
	if ((de->attrib & FATFS_ATTR_VOLUME) != FATFS_ATTR_VOLUME) {
		if (de->lowercase & ~(FATFS_CASE_LOWER_ALL))
			return 0;
		else if (de->attrib & ~(FATFS_ATTR_ALL))
			return 0;

		/* The ctime, cdate, and adate fields are optional and 
		 * therefore 0 is a valid value
		 */
		if ( (getu16(fs, de->ctime) != 0) && 
		  (FATFS_ISTIME(getu16(fs, de->ctime)) == 0) ) 
			return 0;
		else if (FATFS_ISTIME(getu16(fs, de->wtime)) == 0) 
			return 0;
		else if ( (getu16(fs, de->cdate) != 0) && 
		  (FATFS_ISDATE(getu16(fs, de->cdate)) == 0) ) 
			return 0;
		else if ( (getu16(fs, de->adate) != 0) && 
		  (FATFS_ISDATE(getu16(fs, de->adate)) == 0) ) 
			return 0;
		else if (FATFS_ISDATE(getu16(fs, de->wdate)) == 0) 
			return 0;
	}

	if ((de->attrib & FATFS_ATTR_LFN) == FATFS_ATTR_LFN)
		return is_lfn_name((fatfs_dentry_lfn *)de);
	else
		return is_83_name(de);
}



/**************************************************************************
 *
 * INODE WALKING
 * 
 *************************************************************************/
/*
 * walk the inodes
 *
 * Flags that are used: FS_FLAG_ALLOC FS_FLAG_UNALLOC FS_FLAG_USED
 * NOT: FS_FLAG_LINK (no link count)  
 *
 */
void
fatfs_inode_walk(FS_INFO *fs, INUM_T start, INUM_T last, int flags,
                      FS_INODE_WALK_FN action, char *ptr)
{
    char   	*myname = "fatfs_inode_walk";
    FATFS_INFO *fatfs = (FATFS_INFO *) fs;
    //INUM_T  	inum;
    FS_INODE *fs_inode = fs_inode_alloc(FATFS_NDADDR,FATFS_NIADDR);
	//u_int32_t	sect, ssect, lsect, sincr, myflags, i, didx;

    /*
     * Sanity checks.
     */
    if (start < fs->first_inum || start > fs->last_inum)  goto  errLabel;
        //error("%s: invalid start inode number: %lu", myname, (ULONG) start);
    if (last < fs->first_inum || last > fs->last_inum || last < start)  goto errLabel;
        //error("%s: invalid last inode number: %lu", myname, (ULONG) last);


	/* The root_inum is reserved for the root directory, which does
	 * not have a dentry in FAT, so we make one up
	 */
	if ((start == fs->root_inum) && 
	  ((FS_FLAG_ALLOC & flags) == FS_FLAG_ALLOC))
	{
		fatfs_make_root(fatfs, fs_inode);
		if (WALK_STOP == 
		   action(fs, start, fs_inode, FS_FLAG_ALLOC, ptr)) {
			fs_inode_free(fs_inode);
			return;
		}

		if (start == last) {
			fs_inode_free(fs_inode);
			return;
		}

	}


	/* advance it so that it is a valid starting point 
	if (start == fs->root_inum)
		start++;

	/* As FAT does not give numbers to the directory entries, we will make
	 * them up.  Start from one larger then the root inode number (which we
	 * made up) and number each entry in each cluster
	 

	/* start analyzing each sector
	 *
	 * Perform a test on the first 32 bytes of each sector to identify if
	 * the sector contains directory entries.  If it does, then continue
	 * to analyze it.  If not, then read the next sector 
	 */


	/* identify the sector numbers that the starting and ending inodes are 
	 * in
	 
	ssect = FATFS_INODE_2_SECT(fatfs, start);
	lsect = FATFS_INODE_2_SECT(fatfs, last);

	/* cycle through the sectors and increment by sincr
	 * we will increment by clusters when in the cluster section, but by
	 * sectors in FAT12 and FAT16 when we are in the root directory section
	 
	for (sect = ssect; sect <= lsect; sect+=sincr) {
		

        /* There are two scenarios for our current location:
         *
         * For FAT12 & FAT16 we could be between the start of the data area
         * and the start of the cluster area (i.e. the Root directory area)
         * We will only increment ahead 1 sector while in this area.
         *
         * For FAT32 the root directory is in the cluster area so we will
         * always skip ahead in the size of clusters
         */

		/* Skip by Clusters 
		if (sect >= fatfs->firstclustsect) 
		    sincr = fatfs->csize;

		/* Skip by sectors 
		else 
		    sincr = 1;

		/* if the sector is not allocated, then do not go into it if we 
		 * only want allocated/link entries
		 * If it is allocated, then go into it no matter what
		 
		if ((is_sectalloc(fatfs, sect) == 0) && 
		  ((flags & FS_FLAG_UNALLOC) == 0))
		  	continue;

		/* read it 
		fs_read_block(fs, fatfs->dinodes, fatfs->ssize, sect, 
		  "fatfs_inode_walk");

		/* if it is not a bunch of dentries, then skip it 
		if (0 == fatfs_isdentry(fatfs, (fatfs_dentry *)fatfs->dinodes->data)) 
			continue;

		inum = FATFS_SECT_2_INODE(fatfs, sect);

		/* cycle through the sectors, if we are in a cluster 
		for (i = 0; i < sincr; i++) {

			/* read the next sector, if needed 
			if (i != 0) 
				fs_read_block(fs, fatfs->dinodes, fatfs->ssize,
				  sect + i, "fatfs_inode_walk");

			fatfs->dep = (fatfs_dentry *)fatfs->dinodes->data;

			/* cycle through the directory entries 
			for (didx = 0; didx < fatfs->dentry_cnt_se; 
			   didx++, inum++, fatfs->dep++) {

				/* If less, then move on 
				if (inum < start) 
					continue;

				/* If we are done, then return 
				
				if (inum > last) {
					fs_inode_free(fs_inode);
					return;
				}


				/* if this is a long file name entry, then skip it and 
				 * wait for the short name 
				if ((fatfs->dep->attrib & FATFS_ATTR_LFN) == FATFS_ATTR_LFN)
					continue;

				/* Volume Label, skip it 
				if ((fatfs->dep->attrib & FATFS_ATTR_VOLUME) 
				   == FATFS_ATTR_VOLUME)
					continue;	

				/* we dont' care about . and .. entries because they
				 * are redundant of other 'inode' entries 
				if (((fatfs->dep->attrib & FATFS_ATTR_DIRECTORY) 
				   == FATFS_ATTR_DIRECTORY) && (fatfs->dep->name[0] == '.'))
					continue;


				/* Allocation status 
				myflags = ((fatfs->dep->name[0] == FATFS_SLOT_DELETED)? 
				  FS_FLAG_UNALLOC : FS_FLAG_ALLOC);

				if ((flags & myflags) != myflags)
					continue;

				/* Slot is not allocated yet 
				myflags |= ((fatfs->dep->name[0] == FATFS_SLOT_EMPTY) ?
				  FS_FLAG_UNUSED : FS_FLAG_USED);

				if ((flags & myflags) != myflags)
					continue;


				/* Do a final sanity check 
				if (0 == fatfs_isdentry(fatfs, fatfs->dep))
					continue;

				fatfs_copy_inode(fatfs, fs_inode);
				fs_inode->flags = myflags;

				if (WALK_STOP == action(fs, inum, fs_inode, myflags, ptr)) {
					fs_inode_free(fs_inode);
					return;
				}

			} /* dentries 

		} /* sectors 

	} /* clusters 

	fs_inode_free(fs_inode);

*/
errLabel:
	return;

} /* end of inode_walk */

/*
 * return the contents of a specific inode
 *
 * An error is called if the entry is not a valid inode
 *
 */
static FS_INODE *
fatfs_inode_lookup(FS_INFO *fs, INUM_T inum)
{
    FATFS_INFO *fatfs = (FATFS_INFO *) fs;
	FS_INODE *fs_inode = fs_inode_alloc(FATFS_NDADDR,FATFS_NIADDR);

    /* 
	 * Sanity check.
	 */
	if (inum < fs->first_inum || inum > fs->last_inum)  goto  errLabel;
		//  error("invalid inode number: %lu", (ULONG) inum);


	/* As there is no real root inode in FAT, use the made up one */
	if (inum == fs->root_inum) {
		fatfs_make_root(fatfs, fs_inode);
		fs_inode->flags = (FS_FLAG_USED | FS_FLAG_ALLOC);
	}
	else {
		u_int32_t sect, off;

		/* Get the sector that this inode would be in and its offset */
		sect = FATFS_INODE_2_SECT (fatfs, inum);
		off = FATFS_INODE_2_OFF (fatfs, inum);

		fs_read_block(fs, fatfs->dinodes, fatfs->ssize, sect, 
		  "fatfs_inode_lookup");

		fatfs->dep = (fatfs_dentry *) &fatfs->dinodes->data[off]; 
		if (fatfs_isdentry(fatfs, fatfs->dep)) {
			fatfs_copy_inode(fatfs, fs_inode);
		}
		else   goto  errLabel;
		/*{
			error ("%d is not an inode", inum);
		}*/
	}
errLabel:
	return fs_inode;

}


/**************************************************************************
 *
 * FILE WALKING
 * 
 *************************************************************************/

static void
fatfs_file_walk(FS_INFO *fs, FS_INODE *fs_inode, u_int32_t type, u_int16_t id,
    int flags, FS_FILE_WALK_FN action, char *ptr)
{
    FATFS_INFO 	*fatfs = (FATFS_INFO *) fs;
	int 		myflags = FS_FLAG_CONT | FS_FLAG_ALLOC, i;
	OFF_T		size, sbase, clust;
	u_int32_t	len, mask = 0;
	FS_BUF		*fs_buf;

	fs_buf = fs_buf_alloc(fatfs->ssize);
	if (flags & FS_FLAG_SLACK)
		size = roundup(fs_inode->size, fatfs->csize * fatfs->ssize);
	else
		size = fs_inode->size;

	/* get the mask */
	if (fs->ftype == MS16_FAT)
		mask = FATFS_16_MASK;
	else if (fs->ftype == MS32_FAT)
		mask = FATFS_32_MASK;
	else if (fs->ftype == MS12_FAT)
		mask = FATFS_12_MASK;

	clust = fs_inode->direct_addr[0];

	/* this is the root directory entry, special case: it is not in the FAT */
	if ((fs->ftype != MS32_FAT) && (clust == 1)) {
		int snum = fatfs->firstclustsect - fatfs->firstdatasect;
		for (i = 0; i < snum; i++) {

			if ((flags & FS_FLAG_AONLY) == 0)
				fs_read_block(fs, fs_buf, fatfs->ssize, 
				  fatfs->rootsect + i, "");

			action (fs, fatfs->rootsect + i, fs_buf->data, fatfs->ssize, 
			  myflags, ptr);
		}
	}
	else {

		while ((clust & mask) > 0 && size > 0 && 
		  (0 == FATFS_ISEOF(clust, mask)) )  {

			sbase = fatfs->firstclustsect + ((clust & mask) - 2) * fatfs->csize;

			if (sbase > fs->last_block) {
				fs_buf_free(fs_buf);
				if (flags & FS_FLAG_NOABORT)
					return;
				else  goto  errLabel;
					//  error ("Invalid sector address FAT (too large): %lu", (ULONG)sbase);
			}

			/* id the sectors */
			for (i = 0; i < fatfs->csize && size > 0; i++) {
				if (flags & FS_FLAG_SLACK)
					len = fatfs->ssize;
				else
					len = (size < fatfs->ssize) ? size : fatfs->ssize;

				if ((flags & FS_FLAG_AONLY) == 0)
					fs_read_block(fs, fs_buf, fatfs->ssize, sbase + i, "");

				action (fs, sbase + i, fs_buf->data, len, myflags, ptr);
				size -= len;
			}
			if (size > 0) 
				clust = getFAT(fatfs, clust);
		}
	}
errLabel:
	fs_buf_free(fs_buf);
}


static void
fatfs_fsstat(FS_INFO *fs, FILE *hFile)
{
	int i, mask = 0;
	u_int32_t	next, snext, sstart, send;
	FATFS_INFO *fatfs = (FATFS_INFO *)fs;
	fatfs_sb *sb = fatfs->sb;

	fprintf(hFile, "FILE SYSTEM INFORMATION\n");
	fprintf(hFile, "--------------------------------------------\n");

	fprintf(hFile, "File System Type: FAT\n");

	fprintf(hFile, "OEM: %c%c%c%c%c%c%c%c\n", sb->oemname[0], 
	  sb->oemname[1], sb->oemname[2], sb->oemname[3], sb->oemname[4],
	  sb->oemname[5], sb->oemname[6], sb->oemname[7]);
	

	if (fatfs->fs_info.ftype != MS32_FAT) {
		fprintf(hFile, "Volume ID: %lu\n", (ULONG)getu32(fs, sb->a.f16.vol_id));
		fprintf(hFile, "Volume Label: %c%c%c%c%c%c%c%c%c%c%c\n", 
		  sb->a.f16.vol_lab[0], sb->a.f16.vol_lab[1], sb->a.f16.vol_lab[2],
		  sb->a.f16.vol_lab[3], sb->a.f16.vol_lab[4], sb->a.f16.vol_lab[5],
		  sb->a.f16.vol_lab[6], sb->a.f16.vol_lab[7], sb->a.f16.vol_lab[8],
		  sb->a.f16.vol_lab[9], sb->a.f16.vol_lab[10]);

		fprintf(hFile, "File System Type (super block): %c%c%c%c%c%c%c%c\n", 
		  sb->a.f16.fs_type[0], sb->a.f16.fs_type[1], sb->a.f16.fs_type[2],
		  sb->a.f16.fs_type[3], sb->a.f16.fs_type[4], sb->a.f16.fs_type[5],
		  sb->a.f16.fs_type[6], sb->a.f16.fs_type[7]);
	}
	else {

		fprintf(hFile, "Volume ID: %lu\n", (ULONG)getu32(fs, sb->a.f32.vol_id));
		fprintf(hFile, "Volume Label: %c%c%c%c%c%c%c%c%c%c%c\n", 
		  sb->a.f32.vol_lab[0], sb->a.f32.vol_lab[1], sb->a.f32.vol_lab[2],
		  sb->a.f32.vol_lab[3], sb->a.f32.vol_lab[4], sb->a.f32.vol_lab[5],
		  sb->a.f32.vol_lab[6], sb->a.f32.vol_lab[7], sb->a.f32.vol_lab[8],
		  sb->a.f32.vol_lab[9], sb->a.f32.vol_lab[10]);

		fprintf(hFile, "File System Type: %c%c%c%c%c%c%c%c\n", 
		  sb->a.f32.fs_type[0], sb->a.f32.fs_type[1], sb->a.f32.fs_type[2],
		  sb->a.f32.fs_type[3], sb->a.f32.fs_type[4], sb->a.f32.fs_type[5],
		  sb->a.f32.fs_type[6], sb->a.f32.fs_type[7]);

	}

	fprintf(hFile, "\nMETA-DATA INFORMATION\n");
	fprintf(hFile, "--------------------------------------------\n");

	fprintf(hFile, "Range: %lu - %lu\n", (ULONG)fs->first_inum, 
	  (ULONG)fs->last_inum);
	fprintf(hFile, "Root Directory: %lu\n", (ULONG)fs->root_inum);


	fprintf(hFile, "\nCONTENT-DATA INFORMATION\n");
	fprintf(hFile, "--------------------------------------------\n");
	fprintf(hFile, "Sector Size: %d\n", fatfs->ssize);
	fprintf(hFile, "Cluster Size: %d\n", fatfs->csize * fatfs->ssize);
	fprintf(hFile, "Sector of First Cluster: %lu\n", (ULONG)fatfs->firstclustsect);

	fprintf(hFile, "Total Sector Range: %lu - %lu\n", (ULONG)fs->start_block, 
	  (ULONG)fs->last_block);

	for (i = 0; i < fatfs->numfat; i++) {
		u_int32_t base = fatfs->firstfatsect + i * (fatfs->sectperfat);

		fprintf(hFile, "FAT %d Range: %lu - %lu\n", i, (ULONG)base,
		   (ULONG)(base + fatfs->sectperfat - 1));
	}

	fprintf(hFile, "Data Area Sector Range: %lu - %lu\n", 
	  (ULONG)fatfs->firstdatasect, (ULONG)fs->last_block);

	/* Display the FAT Table */
	fprintf(hFile, "\nFAT CONTENTS (in sectors)\n");
	fprintf(hFile, "--------------------------------------------\n");

	if (fatfs->fs_info.ftype == MS16_FAT)
		mask = FATFS_16_MASK;
	else if (fatfs->fs_info.ftype == MS32_FAT)
		mask = FATFS_32_MASK;
	else if (fatfs->fs_info.ftype == MS12_FAT)
		mask = FATFS_12_MASK;

	/* 'sstart' marks the begining of the current run to print */
	sstart = fatfs->firstclustsect;

	/* cycle via cluster */
	for (i = 2; i < fatfs->clustcnt + 1; i++) {
		
		/* 'send' marks the end of the current run, which will extend
		 * when the current cluster continues to the next 
		 */
		send = fatfs->firstclustsect + (i - 1) * fatfs->csize - 1;

		/* get the next cluster */
		next = getFAT(fatfs, i);	
		snext = fatfs->firstclustsect + ((next & mask) - 2) * fatfs->csize;

		/* we are also using the next sector (clust) */
		if ((next & mask) == (i + 1)) {
			continue;
		}

		/* The next clust is either further away or the clust is available,
		 * print it if is further away 
		 */
		else if ((next & mask)) {
			if (FATFS_ISEOF(next, mask)) 
				fprintf (hFile, "%d-%d (%d) -> EOF\n", sstart, send, 
				  send - sstart + 1);
			else
				fprintf (hFile, "%d-%d (%d) -> %d\n", sstart, send, 
				  send - sstart + 1, snext);
		}

		/* reset the starting counter */
		sstart = fatfs->firstclustsect + (i - 1) * fatfs->csize;
	}

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

	fprintf(hFile, "%lu ", (unsigned long) addr);

	if (++printidx == WIDTH) {
		fprintf(hFile, "\n");
		printidx = 0;
    }

    return WALK_CONT;
}


static void
fatfs_istat (FS_INFO *fs, FILE *hFile, INUM_T inum, int numblock,
  int32_t sec_skew)
{
    FS_INODE *fs_inode;
	FS_NAME *fs_name;
    int flags = (FS_FLAG_AONLY | FS_FLAG_CONT | FS_FLAG_META |
          FS_FLAG_ALLOC | FS_FLAG_UNALLOC | FS_FLAG_SLACK);

    fs_inode = fatfs_inode_lookup (fs, inum);
    fprintf(hFile, "Directory Entry: %lu\n", (ULONG) inum);
    fprintf(hFile, "%sAllocated\n",
      (fs_inode->flags&FS_FLAG_ALLOC)?"":"Not ");

	print_dosmode(hFile, fs_inode->mode);
	
    fprintf(hFile, "size: %lu\n", (ULONG) fs_inode->size);
	fprintf(hFile, "num of links: %lu\n", (ULONG) fs_inode->nlink);

	if (fs_inode->name) {
		fs_name = fs_inode->name;
		fprintf(hFile, "Name: %s\n", fs_name->name);
	}

    if (sec_skew != 0) {
        fprintf(hFile, "\nAdjusted Directory Entry Times:\n");                  
        fs_inode->mtime -= sec_skew;
        fs_inode->atime -= sec_skew;
        fs_inode->ctime -= sec_skew;
   
		fprintf(hFile, "Written:\t%s", ctime(&fs_inode->mtime));
		fprintf(hFile, "Accessed:\t%s", ctime(&fs_inode->atime));
		fprintf(hFile, "Created:\t%s", ctime(&fs_inode->ctime));

        fs_inode->mtime += sec_skew;
        fs_inode->atime += sec_skew;
        fs_inode->ctime += sec_skew;

        fprintf(hFile, "\nOriginal Directory Entry Times:\n");             
    }
    else
    	fprintf(hFile, "\nDirectory Entry Times:\n");

    fprintf(hFile, "Written:\t%s", ctime(&fs_inode->mtime));
    fprintf(hFile, "Accessed:\t%s", ctime(&fs_inode->atime));
    fprintf(hFile, "Created:\t%s", ctime(&fs_inode->ctime));

    fprintf (hFile, "\nSectors:\n");

    /* A bad hack to force a specified number of blocks */
    if (numblock > 0)
        fs_inode->size = numblock * fs->file_bsize;

    fs->file_walk(fs, fs_inode, 0, 0, flags, print_addr_act, (char *)hFile);

    if (printidx != 0)
        fprintf(hFile, "\n");

    return;
}


/* fatfs_close - close an fatfs file system */
static void
fatfs_close(FS_INFO *fs)
{
	FATFS_INFO *fatfs = (FATFS_INFO *)fs;
    close(fs->fd);
	fs_buf_free(fatfs->dinodes);
	fs_buf_free(fatfs->table);
	free(fatfs->sb);
    free(fs);
}


 FS_INFO  *  fatfs_open(  const  char  *  name,  unsigned  char  ftype  )
{
    char   			*	myname	=  "fatfs_open";
    FATFS_INFO 		*	fatfs	=  (FATFS_INFO *) mymalloc(sizeof(*fatfs));
    int     			len, datasectcnt;
    FS_INFO 		*	fs		=  NULL;		//  &(fatfs->fs_info);
	fatfs_sb		*	fatsb;
	HANDLE				hDrive	=  NULL;
	DWORD				numberOfBytesRead;
	BOOL				bRet	=  FALSE;

	if  (  !fatfs  )  goto  errLabel;
	fs  =  &fatfs->fs_info;

    if  (  (ftype  &  FSMASK  )  !=  FATFS_TYPE  )  {
        error ("%s: Invalid FS Type in fatfs_open", myname);  
		goto  errLabel;
	}
	
	fs->fd = CreateFile(	name,
							GENERIC_READ,   
							FILE_SHARE_READ | FILE_SHARE_WRITE,  
							NULL,  
							OPEN_EXISTING,
							0,  
							NULL  );
	if  (  fs->fd == INVALID_HANDLE_VALUE  )  goto  errLabel;
	fs->ftype = ftype;
    /*
     * Read the super block.
     */
    len = sizeof(fatfs_sb);
    fatsb = fatfs->sb = (fatfs_sb *)mymalloc (len);
	if  (  !fatsb  )  {
		traceLogA(  "fatfs_open mymalloc failed"  );  goto  errLabel;
	}
	if (  !(  ReadFile(	fs->fd,  fatsb,  len,  &numberOfBytesRead,  NULL  )  )  )
	{
		GetLastError(  );  goto  errLabel;  
	}

    //  if (read(fs->fd, (char *)fatsb, len) != len)
        //  error("%s: read superblock: %m", name);

	/* Check the magic value  and ID endian ordering */
	if (guessu16(fs, fatsb->magic, FATFS_FS_MAGIC)) goto  errLabel;

	fatfs->ssize = getu16(fs, fatsb->ssize);
	fatfs->csize = fatsb->csize;				/* cluster size */
	fatfs->numfat = fatsb->numfat;				/* number of tables */
	fatfs->numroot = getu16(fs, fatsb->numroot);	/* num of root entries */

	/* if sectors16 is 0, then the number of sectors is stored in sectors32 */
	if (0 == (fatfs->sectors = getu16(fs, fatsb->sectors16)))	
		fatfs->sectors = getu32(fs, fatsb->sectors32);


	/* for some reason, on my test images this number was always 1 too large */
	fatfs->sectors--;

	/* if secperfat16 is 0, then read sectperfat32 */
	if (0 == (fatfs->sectperfat = getu16(fs, fatsb->sectperfat16)))	
		fatfs->sectperfat = getu32(fs, fatsb->a.f32.sectperfat32);

	fatfs->firstfatsect = getu16(fs, fatsb->reserved); 	

	/* The data area starts after the FAT */
	fatfs->firstdatasect = fatfs->firstfatsect + 	
		fatfs->sectperfat * fatfs->numfat;

	/* The cluster area is the same as firstdatasect for FAT32, but is
	 * after the root directory entires for FAT12 and FAT16 
	 * NOTE: numroot for FAT32 will be 0 */
	fatfs->firstclustsect = fatfs->firstdatasect + 
	    ((fatfs->numroot * 32 + fatfs->ssize - 1) / fatfs->ssize);

	/* total number of clusters */
	fatfs->clustcnt = (fatfs->sectors - fatfs->firstdatasect) / 
			fatfs->csize;

	/* number of sectors in the data area, used for calculations here only */
	datasectcnt = (fatfs->sectors - fatfs->firstclustsect) / 
		fatfs->csize;

	/* identify the FAT type by the total number of data clusters
	 * this calculation is from the MS FAT Overview Doc
	 */
	if (ftype == MSAUTO_FAT) {

		/* Anything this size is going to be FAT12 */
		if (datasectcnt < 4085) {
			ftype = MS12_FAT;
		}
		/* by spec, we can determine FAT16 vs FAT32 by the number of
		 * sectors, but windows 2K can be forced to format small disks
		 * as FAT32, so we will check fields.  numroot is always 0 for 32
		 */
		else {
			if (getu16(fs, fatsb->numroot) == 0)
				ftype = MS32_FAT;
			else 
				ftype = MS16_FAT;
		}
		fatfs->fs_info.ftype = ftype;
	}

	/* Some sanity checks */
	else {
		if ((ftype == MS12_FAT) && (datasectcnt >= 4085)) 
		//	error ("Too many sectors for FAT12: try auto-detect mode");
		if ((ftype == MS32_FAT) && (fatfs->numroot != 0))  goto  errLabel;
		//  error ("Invalid FAT32 image (numroot != 0)");
		fatfs->fs_info.ftype = ftype;					//  added by wqh.2004/02/14

	}

	/* the root directories are always after the FAT for FAT12 and FAT16,
	 * but are dynamically located for FAT32
	 */
	if (ftype == MS32_FAT) 
		fatfs->rootsect = fatfs->firstclustsect + 
		  (getu32(fs, fatsb->a.f32.rootclust) - 2) * fatfs->csize;
	else 
		fatfs->rootsect = fatfs->firstdatasect;
	fatfs->table = fs_buf_alloc(FAT_CACHE_B);

	/* allocate a buffer for inodes */
    fatfs->dinodes = fs_buf_alloc(fatfs->ssize);


    /*
	 * block calculations : although there are no blocks in fat, we will
	 * use these fields for sector calculations
     */
    fs->start_block = 0;
    fs->block_count = fatfs->sectors;
    fs->last_block = fs->block_count - 1;
	fs->block_size = fatfs->ssize;
	fs->file_bsize = fatfs->ssize;
	fs->addr_bsize = 0;
	fs->block_frags = 1;
	fs->dev_bsize = FATFS_DEV_BSIZE;

	/*
	 * inode calculations
	 */

	/* maximum number of dentries in a sector & cluster */
	fatfs->dentry_cnt_se = fatfs->ssize / sizeof (fatfs_dentry);
	fatfs->dentry_cnt_cl = fatfs->dentry_cnt_se * fatfs->csize;


	/* can we handle this image (due to our meta data addressing scheme?)
	* 2^28 is because we have 2^32 for directory entry addresses and 
	* there are 2^4 entries per sector.  So, we can handle 2^28 sectors
	*/
	if (fatfs->sectors > (0x1 << 28)) goto  errLabel;
		//  error ("FAT Volume too large for analysis");

	fs->root_inum = FATFS_ROOTINO;
	fs->first_inum = FATFS_FIRSTINO;
	fs->inum_count = fatfs->dentry_cnt_cl * fatfs->clustcnt;
	fs->last_inum = fs->first_inum + fs->inum_count;
	fs->niaddr = FATFS_NIADDR;


	/* long file name support */
	fatfs->lfn = NULL;
	fatfs->lfn_len = 0;
	fatfs->lfn_chk = 0;


    /*
     * Other initialization: caches, callbacks.
     */
	fs->seek_pos = -1;
    fs->inode_walk = fatfs_inode_walk;
    fs->block_walk = fatfs_block_walk;
	fs->inode_lookup = fatfs_inode_lookup;
    fs->dent_walk = fatfs_dent_walk;
    fs->file_walk = fatfs_file_walk;
	fs->fsstat = fatfs_fsstat;
	fs->istat = fatfs_istat;
    fs->close = fatfs_close;

	/* Figure out timezone difference for time conversion */
	set_secwest();

	bRet  =  TRUE;
errLabel:

	return(  bRet  ?  fs  :  NULL  );
}
