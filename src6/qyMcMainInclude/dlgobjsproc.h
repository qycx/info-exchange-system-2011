
#ifndef  __DLGOBJSPROC_H__
#define  __DLGOBJSPROC_H__	//  {

typedef  struct  __param_layout_dlgObjs_t				{
}		 PARAM_layout_dlgObjs;

typedef  struct  __dlgObjsVar_t							{
				 void							*		pMisCnt;
				 unsigned short							usItemCount;

				 DLG_guiData_objs						guiData;


				 PARAM_layout_dlgObjs					layoutParam;

				 //
				 struct									{
					 union								{
						struct							{						 
							int							nColumns;
						}								selectRemoteVideo;

						//
						struct							{							//  2013/06/24
							int							nColumns;
						}								selectLayoutType;

					 }									u;
				 }										dataHead;

				 //
				 void							*		pData;
				 unsigned  int							uiSize_pData;


}		DLG_objs_var;




#endif  //  }



