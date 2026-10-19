
#ifndef  __QYSTATUSTOOLCOMMON_H__
#define  __QYSTATUSTOOLCOMMON_H__	/*  {  */

#include	<vfw.h>

#include	"qmCommon.h"

#define		CONST_maxnItemsInListBox_main				12000		//  状态窗口的列表框的最大容纳记录数
#define		CONST_maxnItemsInListBox_client				4500		//  状态窗口的列表框的最大容纳记录数


extern  TCHAR		gStatusToolWndCls[256];


DWORD  WINAPI  qyStatusToolThreadProc(  LPVOID  lpParameter  );
DWORD  WINAPI  statusPipeServThreadProc(  LPVOID  lpParameter  );



#endif  /*  }  */

