
readMe.txt

2004-2-15、解决文件名为汉字的遍历问题。
	fs_dent.c  显示和计算目录项

	FS_DENT:什么意思

	fs_read_block:  基本读，将1个扇区数据读入缓存。
	
	fatfs_isdentry:  检验文件名的有效性。

	fatfs_dent_copy：

	print_dent:
	fs_dent_print:	 按格式(d/-d-)打印.

2004-2-24:  ntfs格式:$MFT;  from www.ntfs.com
MFT Record has pre-defined structure. It has a set of attributes defining any file of folder parameters. 

MFT Record begins with standard File Record Header (first bold section, offset 0x00):

"FILE" identifier (4 bytes) 
Offset to update sequence (2 bytes) 
Size of update sequence (2 bytes) 
$LogFile Sequence Number (LSN) (8 bytes) 
Sequence Number (2 bytes) 
Reference Count (2 bytes) 
Offset to Update Sequence Array (2 bytes) 
Flags (2 bytes) 
Real size of the FILE record (4 bytes) 
Allocated size of the FILE record (4 bytes) 
File reference to the base FILE record (8 bytes) 
Next Attribute Id (2 bytes) 
  
The most important information for us in this block is a file state: deleted or in-use. If Flags(in red color) field has bit 1 set, it means that file is in-use. In our example it is zero, i.e. file is deleted.

Starting from 0x48, we have Standard Information Attribute (second bold section):

File Creation Time (8 bytes) 
File Last Modification Time (8 bytes) 
File Last Modification Time for File Record (8 bytes) 
File Access Time for File Record (8 bytes) 
DOS File Permissions (4 bytes) 0x20 in our case Archive Attribute 
  
Following standard attribute header, we have File Name Attribute belonging to DOS name space, short file names, (third bold section, offset 0xA8) and again following standard attribute header, we have File Name Attribute belonging to Win32 name space, long file names, (third bold section, offset 0x120): 

File Reference to the Parent Directory (8 bytes) 
File Modification Times (32 bytes) 
Allocated Size of the File (8 bytes) 
Real Size of the File (8 bytes) 
Flags (8 bytes) 
Length of File Name (1 byte) 
File Name Space (1 byte) 
File Name (Length of File Name * 2 bytes) 
  
In our case from this section we can extract file name, "My Presentation.ppt", File Creation and Modification times, and Parent Directory Record number.

Starting from offset 0x188, there is a non-resident Data attribute (green section).

Attribute Type (4 bytes) (e.g. 0x80) 
Length including header (4 bytes) 
Non-resident flag (1 byte) 
Name length (1 byte) 
Offset to the Name (2 bytes) 
Flags (2 bytes) 
Attribute Id (2 bytes) 
Starting VCN (8 bytes) 
Last VCN (8 bytes) 
Offset to the Data Runs (2 bytes) 
Compression Unit Size (2 bytes) 
Padding (4 bytes) 
Allocated size of the attribute (8 bytes) 
Real size of the attribute (8 bytes) 
Initialized data size of the stream (8 bytes) 
Data Runs ... 
  
In this section we are interested in Compression Unit size (zero in our case means non-compressed), Allocated and Real size of attribute that is equal to our file size (0xDC00 = 56320 bytes), and Data Runs (see the next chapter).

 



