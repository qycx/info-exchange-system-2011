

#ifndef  __dlgSelect_isCli_public_h__
#define  __dlgSelect_isCli_public_h__		//  {

typedef  union							{
			struct						{
				TCHAR					misServName[CONST_maxMisServNameLen  +  1];

				QY_MESSENGER_ID			idInfo_selected;
			}							selectMessenger;
			struct						{
				TCHAR					misServName[CONST_maxMisServNameLen  +  1];

				QY_MESSENGER_ID			idInfo_selected;
			}							selectImGrp;
			struct						{
				TCHAR					misServName[CONST_maxMisServNameLen  +  1];
				BOOL					bPhoneGuest;
				//
				MC_VAR_isCli			*	pProcInfo;
				MIS_CNT				*	pMisCnt;
				//
				TCHAR					toPath[256];
			}							selectToPath;
			QIS_DYN_BMP					selectDynBmp;
		
}			DlgSelect_isCli_o_U;


#endif  //  }




