
#include<windows.h>

static  char *GetCfgStr(char *cfgstr,char *key)
{
	char *str;
	
	str=cfgstr;

	// Skip past name of options list
	while(*str!='\0') str++;
	str++;
	// Walk through options
	while(*str!='\0') {
		int nLen;
		if(*str=='B') {
			nLen=1;
			str+=2;
			if(strncmp(str,key,strlen(key))==0) break;
		} else if(*str=='S') {
			str+=2;
			nLen=atoi(str);
			while(*str!=']') str++;
			str+=2;
			if(strncmp(str,key,strlen(key))==0) break;
		} else if(*str=='N') {
			str+=2;
			char *pb;
			pb=str;
			while(*str!=',') str++;
			nLen=(DWORD)str-(DWORD)pb;
			str++;
			pb=str;
			while(*str!=']') str++;
			int nLen2=(DWORD)str-(DWORD)pb;
			if(nLen2>nLen) nLen=nLen2;
			str+=2;
			if(strncmp(str,key,strlen(key))==0) break;
		}
		while(*str!='=') str++;
		str++;
		str+=(nLen+1);
	}
	if(*str!='\0') {
		while(*str!='=') str++;
		return str+1;
	}
	
	return NULL;
}

int GetCfgNum(char *cfgstr,char *key)
{
	char *str;
	str=GetCfgStr(cfgstr,key);
	return (str==NULL)?0:atoi(str);
}

int GetCfgBool(char *cfgstr,char *key)
{
	return GetCfgNum(cfgstr,key)?TRUE:FALSE;
}

