

#ifndef  __QYDROPTARGET_H__
#define  __QYDROPTARGET_H__  //  {

#include  "AFXOLE.h"

class  CDropTarget  :  public  COleDropTarget
{
public:
        CDropTarget(  );
		virtual ~CDropTarget(  );

		
		virtual DROPEFFECT OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject,	DWORD dwKeyState, CPoint point);
		virtual DROPEFFECT OnDragOver(CWnd* pWnd, COleDataObject* pDataObject,	DWORD dwKeyState, CPoint point);
		virtual BOOL OnDrop(CWnd* pWnd, COleDataObject* pDataObject,	DROPEFFECT dropEffect, CPoint point);
		virtual DROPEFFECT OnDropEx(CWnd* pWnd, COleDataObject* pDataObject,	DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point);
		virtual void OnDragLeave(CWnd* pWnd);
		virtual DROPEFFECT OnDragScroll(CWnd* pWnd, DWORD dwKeyState,CPoint point);
		

		// Interface Maps
public:
	BEGIN_INTERFACE_PART(DropTarget, IDropTarget)
		INIT_INTERFACE_PART(COleDropTarget, DropTarget)
		STDMETHOD(DragEnter)(LPDATAOBJECT, DWORD, POINTL, LPDWORD);
		STDMETHOD(DragOver)(DWORD, POINTL, LPDWORD);
		STDMETHOD(DragLeave)();
		STDMETHOD(Drop)(LPDATAOBJECT, DWORD, POINTL pt, LPDWORD);
	END_INTERFACE_PART(DropTarget)

	DECLARE_INTERFACE_MAP()

		/*

public:	
	    HWND  m_hWnd;

private:
		DWORD  DropEffect(  DWORD  grfKeyState,  POINTL  pt,  DWORD  dwAllowed  );
		BOOL  QueryDataObject(  IDataObject  *  pDataObject  );

		LONG  m_lRefCount;
		BOOL  m_fAllowDrop;

		IDataObject  *  m_pDataObject;
		*/

 };




#endif  //  }

