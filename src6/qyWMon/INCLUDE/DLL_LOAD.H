
#ifndef __INC_DLL_LOAD_H
#define __INC_DLL_LOAD_H

#include<windows.h>

#define NTSIGNATURE(ptr) ((LPVOID)((BYTE *)(ptr) + ((PIMAGE_DOS_HEADER)(ptr))->e_lfanew))
#define SIZE_OF_NT_SIGNATURE (sizeof(DWORD))
#define PEFHDROFFSET(ptr) ((LPVOID)((BYTE *)(ptr)+((PIMAGE_DOS_HEADER)(ptr))->e_lfanew+SIZE_OF_NT_SIGNATURE))
#define OPTHDROFFSET(ptr) ((LPVOID)((BYTE *)(ptr)+((PIMAGE_DOS_HEADER)(ptr))->e_lfanew+SIZE_OF_NT_SIGNATURE+sizeof(IMAGE_FILE_HEADER)))
#define SECHDROFFSET(ptr) ((LPVOID)((BYTE *)(ptr)+((PIMAGE_DOS_HEADER)(ptr))->e_lfanew+SIZE_OF_NT_SIGNATURE+sizeof(IMAGE_FILE_HEADER)+sizeof(IMAGE_OPTIONAL_HEADER)))
#define RVATOVA(base,offset) ((LPVOID)((DWORD)(base)+(DWORD)(offset)))
#define VATORVA(base,offset) ((LPVOID)((DWORD)(offset)-(DWORD)(base)))

#define SIZE_OF_PARAMETER_BLOCK 4096
#define IMAGE_PARAMETER_MAGIC 0xCDC31337
#define MAX_DLL_PROCESSES 256
#define DLL_ATTACH 0
#define DLL_DETACH 1

// NEW FLAGS
#define REBIND_IMAGE_IMPORTS 0x00000100
#define RWX_PERMISSIONS 0x00000200
#define FORCE_LOAD_NEW_IMAGE 0x00000400

// Internal functions





#endif