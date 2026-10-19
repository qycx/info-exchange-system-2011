/*++
* NAME
*	fs_io 3
* SUMMARY
*	file system I/O routines
* SYNOPSIS
*	#include "fstools.h"
*
*	void	fs_read_block(fs, buf, len, addr, comment)
*	FS_INFO *fs;
*	FS_BUF	*buf;
*	int	len;
*	DADDR_T	addr;
*	const char *comment;
*
*	void	fs_read_random(fs, buf, len, offs, comment)
*	FS_INFO *fs;
*	char	*buf;
*	int	len;
*	OFF_T	offs;
*	const char *comment;
* DESCRIPTION
*	fs_read_block() reads a block of data from the named file system.
*
*	fs_read_random() reads from an arbitrary position.
*
*	Arguments:
* .IP fs
*	File system handle.
* .IP buf
*	Result buffer pointer.
* .IP len
*	Amount of bytes to be read.
* .IP addr
*	Block number.
* .IP fd
*	Open device file.
* .IP offs
*	Byte offset.
* .IP comment
*	Text logged with verbose logging.
* LICENSE
*	This software is distributed under the IBM Public License.
* AUTHOR(S)
*	Wietse Venema
*	IBM T.J. Watson Research
*	P.O. Box 704
*	Yorktown Heights, NY 10598, USA
--*/

#include "include\\fs_tools.h"
#include "include\\error.h"
#include "include\\fs_types.h"

/* fs_read_block - read a block from a file system */

__int64 myFileSeek (HANDLE hf, __int64 distance, DWORD MoveMethod)
{
   LARGE_INTEGER li;

   li.QuadPart = distance;

   li.LowPart = SetFilePointer (hf, li.LowPart, &li.HighPart, MoveMethod);

   if (li.LowPart == 0xFFFFFFFF && GetLastError() != NO_ERROR)
   {
      li.QuadPart = -1;
   }

   return li.QuadPart;
}



void    fs_read_block(FS_INFO *fs, FS_BUF *buf, int len, DADDR_T addr,
		              const char *comment)
{
    char   *myname = "fs_read_block";
    OFF_T   offs;
	DWORD					numberOfBytesRead;

    /*
     * Sanity checks.
     */

	if (len % fs->dev_bsize)  goto  errLabel;
		//error("%s: Block Read Request with length (%d) not a multiple of %d",  myname, len, fs->dev_bsize);

    if (len > buf->size)  goto  errLabel;
		//  error("%s: Buffer length is too short for read (%d > %d)",  myname, len, buf->size);

	if (addr > fs->last_block)  goto  errLabel;
		//  error("%s: Read Error (address is too large for image %lu)",  myname, (ULONG)addr);

    /*
     * Bummer: with the 32-bit file model, Solaris 7 read() won't go past 2GB
     * seek offsets, so we must use pread() instead of read(). When printing
     * disk offsets, convert to double in case they have huge file offset
     * types and the number does not fit in an unsigned long.
     */
    buf->addr = addr;
    offs = (OFF_T) addr *fs->block_size;

	// Move to nth(0~4177055) sector for something interesting to read.

    if (fs->seek_pos != offs)  myFileSeek(fs->fd, offs, FILE_BEGIN);	
	if (  !(  ReadFile(	fs->fd,  buf->data,  len,  &numberOfBytesRead,  NULL  )  )  )	{	
		 GetLastError(  );  goto  errLabel;  
	}
    
    fs->seek_pos = offs + len;
    buf->used = len;
	errLabel:
	return;
}

/* fs_read_random - random-access read */

void    fs_read_random(FS_INFO *fs, char *buf, int len, OFF_T offs,
		               const char *comment)
{
    char   *myname = "fs_read_random";
    //int     count;
	DWORD					numberOfBytesRead;


	/*
	if (fs->seek_pos != offs) {

		if  (  SetFilePointer(  fs->fd,  offs,  NULL,  FILE_BEGIN  )  ==  0xFFFFFFFF  )  goto  errLabel;

		if  (  S_lseeki64(  fs->fd, offs,  SEEK_SET  ) != offs  )  goto  errLabel;
	}
	*/
	if (fs->seek_pos != offs)  myFileSeek(fs->fd, offs, FILE_BEGIN);	
	if (  !(  ReadFile(	fs->fd,  buf,  len,  &numberOfBytesRead,  NULL  )  )  )	{	
		 GetLastError(  );  goto  errLabel;  
	}

    fs->seek_pos = offs + len;
	errLabel:
	return;
}
