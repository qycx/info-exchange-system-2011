

#ifndef  __QMUIFUNC_H__
#define  __QMUIFUNC_H__	//  {



//  int  qyBrowseForFile(  BOOL bOpen,  LPCTSTR  lpszDefExt,  DWORD  dwFlags,  LPCTSTR  lpszFilter,  LPCTSTR  title,  LPCTSTR  initialFile,  CQyString  &  fileStr  );
//  int  qyBrowseForDir(  LPCTSTR  title,  LPCTSTR  initialDir,  CQyString  &  dirStr  );

__declspec(  dllexport  )  int  qyBrowseForFile(  HWND  hwndOwner,  BOOL bOpen,  LPCTSTR  lpszDefExt,  DWORD  dwFlags,  LPCTSTR  lpszFilter,  LPCTSTR  title,  LPCTSTR  initialFile,  CQyString  &  fileStr  );
int  qyBrowseForDir(  HWND  hwndOwner,  LPCTSTR  title,  LPCTSTR  initialDir,  CQyString  &  dirStr  );


#endif


