
#include "stdafx.h"
#include "WzdBitmap.h"


 IMPLEMENT_DYNAMIC( CWzdBitmap, CBitmap )

 CWzdBitmap::CWzdBitmap()
{
	m_pPalette = NULL;
}

 CWzdBitmap::~CWzdBitmap()
{
	if ( m_pPalette ) {
		delete m_pPalette;
	}

}


 void CWzdBitmap::SaveBitmapEx( CString sFile )
{
	 int bmData;
	 HANDLE hDIB = CreateDIB( &bmData );

	 LPBYTE lpBitmap = ( LPBYTE )::GlobalLock( hDIB );
	 int bmSize = ::GlobalSize( hDIB );

	 CFile file;
	 file.Open( sFile, CFile::modeCreate | CFile::modeWrite );

	 BITMAPFILEHEADER bmfh;
	 bmfh.bfType = 'MB';
	 bmfh.bfSize = sizeof( BITMAPFILEHEADER ) + bmSize;
	 bmfh.bfReserved1 = 0;
	 bmfh.bfReserved2 = 0;
	 bmfh.bfOffBits = bmData;
	 file.Write( &bmfh, sizeof( BITMAPFILEHEADER ) );

	 file.Write( lpBitmap, bmSize );

	 file.Close();
	 ::GlobalUnlock( hDIB );
	 ::GlobalFree( hDIB );

}

 HANDLE CWzdBitmap::CreateDIB( int *pbmData )
{
	 BITMAPINFOHEADER bi;
	 memset( &bi, 0, sizeof( bi ) );
	 bi.biSize = sizeof( BITMAPINFOHEADER );
	 bi.biPlanes = 1;
	 bi.biCompression = BI_RGB;

	 BITMAP bm;
	 GetObject( sizeof( bm ), ( LPSTR )&bm );
	 bi.biWidth = bm.bmWidth;
	 bi.biHeight = bm.bmHeight;

	 int bits = bm.bmPlanes * bm.bmBitsPixel;
	 if ( bits <= 1 ) bi.biBitCount = 1;
	 else if ( bits <= 4 ) bi.biBitCount = 4;
	 else if ( bits <= 8 ) bi.biBitCount = 8;
	 else bi.biBitCount = 24;

	 int biColorSize = 0;

	 if ( bi.biBitCount != 24 ) biColorSize = ( 1 << bi.biBitCount );
	 biColorSize *= sizeof( RGBQUAD );

	 bi.biSizeImage = ( DWORD )bm.bmWidth * bi.biBitCount;
	 bi.biSizeImage = ( ( ( bi.biSizeImage ) + 31 ) / 32 ) * 4;

	 bi.biSizeImage *= bm.bmHeight;

	 if ( pbmData ) *pbmData = bi.biSize + biColorSize;

	 HANDLE hDIB = ::GlobalAlloc( GHND, bi.biSize + biColorSize + bi.biSizeImage );

	 LPBITMAPINFOHEADER lpbi = ( LPBITMAPINFOHEADER )::GlobalLock( hDIB );

	 *lpbi = bi;

	 CDC dc;
	 dc.Attach( ::GetDC( NULL ) );
	 CPalette *pPal = dc.SelectPalette( m_pPalette, FALSE );
	 dc.RealizePalette();

	 ::GetDIBits( dc.m_hDC, ( HBITMAP )m_hObject, 0, ( UINT )bi.biHeight,
		 ( LPSTR )lpbi + ( WORD )lpbi->biSize + biColorSize,
		 ( LPBITMAPINFO )lpbi, DIB_RGB_COLORS );


	 ::GlobalUnlock( hDIB );
	 dc.SelectPalette( pPal, FALSE );
	 dc.RealizePalette();

	 return hDIB;



}





 void CWzdBitmap::Capture( CRect &rect )
{
	 if ( m_pPalette ) {
		 DeleteObject();
		 delete m_pPalette;
	 }

	 m_nWidth = rect.Width();
	 m_nHeight = rect.Height();

	 CDC dcScreen;
	 dcScreen.CreateDC( "DISPLAY", NULL, NULL, NULL );

	 CDC dcMem;
	 dcMem.CreateCompatibleDC( &dcScreen );
	 CreateCompatibleBitmap( &dcScreen, m_nWidth, m_nHeight );
	 dcMem.SelectObject( this );

	 dcMem.BitBlt( 0, 0, m_nWidth, m_nHeight, &dcScreen, rect.left, rect.top, SRCCOPY );

	 int nColors = ( 1 << ( dcScreen.GetDeviceCaps( BITSPIXEL ) * dcScreen.GetDeviceCaps( PLANES ) ) );

	 LOGPALETTE *pLogPal = ( LOGPALETTE * )new BYTE[ sizeof( LOGPALETTE ) + ( nColors * sizeof( PALETTEENTRY ) ) ];

	 pLogPal->palVersion = 0x300;
	 pLogPal->palNumEntries = nColors;

	 ::GetSystemPaletteEntries( dcScreen.m_hDC, 0, nColors, ( LPPALETTEENTRY )( pLogPal->palPalEntry ) );

	 m_pPalette = new CPalette;
	 m_pPalette->CreatePalette( pLogPal );

	 delete []pLogPal;
	 dcMem.DeleteDC();
	 dcScreen.DeleteDC();




}

