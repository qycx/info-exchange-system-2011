
#ifndef __INC_COMMANDLOOP_H
#define __INC_COMMANDLOOP_H

//  #include<auth.h>
//  #include<iohandler.h>
//  #include<encryption.h>

#define MAX_COMMAND_SOCKETS 64
#define MAX_COMMAND_CONNECTIONS 256


extern int g_nCommCount, g_nConnCount;
extern BOOL g_bBO2KFinished;
extern char g_szStartupOptions[];

void  commandHandlerLoop(void);
void  commandHandlerLoop_usrScript(  void  );




#endif