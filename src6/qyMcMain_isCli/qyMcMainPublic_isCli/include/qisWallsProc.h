
#ifndef  __qisWallsProc_h__
#define  __qisWallsProc_h__


typedef  struct  __qisWallD3dMem_t			{
			     QY_MESSENGER_ID		idInfo;
				 //
				 TCHAR					wallFilePath[MAX_PATH];

}		 QIS_wallD3d_mem;


typedef  struct  __qisWalls_t			{
				 unsigned  short			usCnt;
				 QIS_wallD3d_mem		*	pMems;				 
}		 QIS_walls;


__declspec(  dllexport  )  void  *  qisWallsNew(  unsigned  short  usMaxCnt  );
__declspec(  dllexport  )  void  qisWallsFree(  void  **  ppQIS_walls  );


#endif

