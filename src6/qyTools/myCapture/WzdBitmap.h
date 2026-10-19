
#ifndef __WZDBITMAP_H__
#define __WZDBITMAP_H__		/* { */

class CWzdBitmap : public CBitmap 
{
public:
	DECLARE_DYNAMIC( CWzdBitmap )

	CWzdBitmap();

	void SaveBitmapEx( CString sFile );
	HANDLE CreateDIB( int *pbmData = NULL );

	void Capture( CRect &rect );

	CPalette *GetPalette() { return m_pPalette; }

public:
	virtual ~CWzdBitmap();
	int m_nWidth;
	int m_nHeight;
private:
	CPalette *m_pPalette;


};




#endif	/* } __WZDBITMAP_H__ defined */
