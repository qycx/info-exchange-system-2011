
#ifndef __INC_COMMNET_H
#define __INC_COMMNET_H

#include<windows.h>
//  #include<auth.h>


#define CMDFLAG_COMMAND 1
#define CMDFLAG_REPLY   2
	
void BreakDownCommand(BYTE *pInBuffer, int *cmdlen, int *command, int *comid, int *nArg1, char **svArg2, char **svArg3);
BYTE *BuildCommandRequest(int command, int comid, int nArg1, char *svArg2, char *svArg3, int *pnReqLen);
BYTE *BuildCommandReply(int comid, int nReplyCode, char *svReply, int *pnReqLen);
void FreeCommandMemory(BYTE *pCmd);

#endif