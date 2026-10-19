
#include	"stdafx.h"
#include	"qyDropTarget.h"

void  DropData(  HWND  hwnd,  IDataObject  *  pDataObject  );

BEGIN_INTERFACE_MAP(CDropTarget, COleDropTarget)
	INTERFACE_PART(CDropTarget, IID_IDropTarget, DropTarget)
END_INTERFACE_MAP()

/*
BEGIN_INTERFACE_MAP(COleDropTarget, CCmdTarget)
	INTERFACE_PART(COleDropTarget, IID_IDropTarget, DropTarget)
END_INTERFACE_MAP()
*/

CDropTarget::CDropTarget(  )
{
}

CDropTarget::~CDropTarget(  )
{
	OutputDebugString(  _T(  "CDropTarget::~CDropTarget(  )\n"  )  );
}

void  PositionCursor(  HWND  hwndEdit,  POINTL  pt  )
{
	DWORD	curpos;

	ScreenToClient(  hwndEdit,  (  POINT  *  )&pt  );
	curpos  =  SendMessage(  hwndEdit,  EM_CHARFROMPOS,  0,  MAKELPARAM(  pt.x,  pt.y  )  );

	SendMessage(  hwndEdit,  EM_SETSEL,  LOWORD(  curpos  ),  LOWORD(  curpos  )  );

}

//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////


/*
		//  virtual DROPEFFECT OnDropEx(CWnd* pWnd, COleDataObject* pDataObject,	DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point);
		*/


DROPEFFECT CDropTarget::OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject,	DWORD dwKeyState, CPoint point)
{
	pWnd->ClientToScreen(  &point  );

	return  DROPEFFECT_NONE;

}

DROPEFFECT CDropTarget::OnDropEx(CWnd* pWnd, COleDataObject* pDataObject,	DROPEFFECT dropDefault, DROPEFFECT dropList, CPoint point)
{
	return  DROPEFFECT_NONE;
}
		


void CDropTarget::OnDragLeave(CWnd* pWnd)
{
	COleDropTarget::OnDragLeave(  pWnd  );
}


DROPEFFECT CDropTarget::OnDragOver(CWnd* pWnd, COleDataObject* pDataObject,	DWORD dwKeyState, CPoint point)
{

	return  DROPEFFECT_NONE;
}





 BOOL CDropTarget::OnDrop(CWnd* pWnd, COleDataObject* pDataObject,	DROPEFFECT dropEffect, CPoint point)
{

	return  TRUE;

}

 DROPEFFECT CDropTarget::OnDragScroll(CWnd* pWnd, DWORD dwKeyState,CPoint point)
 {
	 return  DROPEFFECT_NONE;
 }




 STDMETHODIMP_(ULONG) CDropTarget::XDropTarget::AddRef()
{
	METHOD_PROLOGUE_EX_(CDropTarget, DropTarget)
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CDropTarget::XDropTarget::Release()
{
	METHOD_PROLOGUE_EX_(CDropTarget, DropTarget)
	return pThis->ExternalRelease();
}

STDMETHODIMP CDropTarget::XDropTarget::QueryInterface(
		  REFIID iid, LPVOID far* ppvObj)     
{
	METHOD_PROLOGUE_EX_(CDropTarget, DropTarget)
	return pThis->ExternalQueryInterface(&iid, ppvObj);
}



STDMETHODIMP CDropTarget::XDropTarget::DragEnter(THIS_ LPDATAOBJECT lpDataObject,
	DWORD dwKeyState, POINTL pt, LPDWORD pdwEffect)
{
	METHOD_PROLOGUE_EX_(CDropTarget, DropTarget)


	return  E_NOTIMPL;
}

STDMETHODIMP CDropTarget::XDropTarget::DragOver(THIS_ DWORD dwKeyState,
	POINTL pt, LPDWORD pdwEffect)
{
	METHOD_PROLOGUE_EX(CDropTarget, DropTarget)
	ASSERT_VALID(pThis);

	return  E_NOTIMPL;
}


 STDMETHODIMP CDropTarget::XDropTarget::DragLeave(THIS)
{
	METHOD_PROLOGUE_EX(CDropTarget, DropTarget)
	ASSERT_VALID(pThis);

	return  E_NOTIMPL;
 }

 STDMETHODIMP CDropTarget::XDropTarget::Drop(THIS_ LPDATAOBJECT lpDataObject,
	DWORD dwKeyState, POINTL pt, LPDWORD pdwEffect)
{
	METHOD_PROLOGUE_EX(CDropTarget, DropTarget)
	ASSERT_VALID(pThis);

	return  E_NOTIMPL;
 }


 

/*
void  DropData(  HWND  hwnd,  IDataObject  *  pDataObject  )
{
	FORMATETC  fmtetc  =  {  CF_TEXT,  0,  DVASPECT_CONTENT,  -1,  TYMED_HGLOBAL  };
	STGMEDIUM  stgmed;

	if  (  pDataObject->QueryGetData(  &fmtetc  )  ==  S_OK  )
	{
		if  (  pDataObject->GetData(  &fmtetc,  &stgmed  )  ==  S_OK  )
		{
			PVOID  data  =  GlobalLock(  stgmed.hGlobal  );
			SetWindowText(  hwnd,  (  TCHAR  *  )data  );
			GlobalUnlock(  stgmed.hGlobal  );

			ReleaseStgMedium(  &stgmed  );
		}
	}

}
*/

