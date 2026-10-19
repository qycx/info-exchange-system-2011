
#include	"stdafx.h"


 int  doMyCap(  void  *  p0,  TCHAR *svArg2, char *svArg3  )
{
	int		iErr	=	-1;
	// Create device context
	HDC hdc;
	hdc=CreateDC(_T(  "DISPLAY"  ), NULL, NULL, NULL);
	if(hdc==NULL)  goto  errLabel;
							
	// Get dimensions
	DWORD dwWidth, dwHeight, dwBPP, dwNumColors;

	dwWidth = GetDeviceCaps(hdc, HORZRES);
	dwHeight = GetDeviceCaps(hdc, VERTRES);
	dwBPP = GetDeviceCaps(hdc, BITSPIXEL);
	if(dwBPP<=8) {
		dwNumColors = GetDeviceCaps(hdc, NUMCOLORS);
		dwNumColors = 256;
	} else {
		dwNumColors = 0;
	}

	// Create compatible DC
	HDC hdc2;
	hdc2=CreateCompatibleDC(hdc);
	if(hdc2==NULL) {
		DeleteDC(hdc);
		goto  errLabel;
	}

	// Create bitmap
	HBITMAP bitmap;
	BITMAPINFO bmpinfo;
	LPVOID pBits;

	bmpinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpinfo.bmiHeader.biWidth = dwWidth;
	bmpinfo.bmiHeader.biHeight = dwHeight;
	bmpinfo.bmiHeader.biPlanes = 1;
	bmpinfo.bmiHeader.biBitCount = (WORD) dwBPP;
	bmpinfo.bmiHeader.biCompression = BI_RGB;
	bmpinfo.bmiHeader.biSizeImage = 0;
	bmpinfo.bmiHeader.biXPelsPerMeter = 0;
	bmpinfo.bmiHeader.biYPelsPerMeter = 0;
	bmpinfo.bmiHeader.biClrUsed = dwNumColors;
	bmpinfo.bmiHeader.biClrImportant = dwNumColors;
	
	bitmap = CreateDIBSection(hdc, &bmpinfo, DIB_PAL_COLORS, &pBits, NULL, 0);
	if(bitmap==NULL) {
		DeleteDC(hdc);
		DeleteDC(hdc2);
		goto  errLabel;
	}
	HGDIOBJ gdiobj;
	gdiobj = SelectObject(hdc2, (HGDIOBJ)bitmap);
	if((gdiobj==NULL) || (gdiobj==(void *)GDI_ERROR)) {
		DeleteDC(hdc);
		DeleteDC(hdc2);
		goto  errLabel;
	}
	if (!BitBlt(hdc2, 0,0, dwWidth, dwHeight, hdc, 0,0, SRCCOPY)) {
		DeleteDC(hdc);
		DeleteDC(hdc2);
		goto  errLabel;
	}
	
	RGBQUAD colors[256];
	if(dwNumColors!=0) {
		dwNumColors = GetDIBColorTable(hdc2, 0, dwNumColors, colors);
	}
	
	
	// Fill in bitmap structures
	BITMAPFILEHEADER bitmapfileheader;
	BITMAPINFOHEADER bitmapinfoheader;

	bitmapfileheader.bfType = 0x4D42;
	bitmapfileheader.bfSize = ((dwWidth * dwHeight * dwBPP)/8) + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (dwNumColors * sizeof(RGBQUAD));
	bitmapfileheader.bfReserved1 = 0;
	bitmapfileheader.bfReserved2 = 0;
	bitmapfileheader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + (dwNumColors * sizeof(RGBQUAD));  
	
	bitmapinfoheader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapinfoheader.biWidth = dwWidth;
	bitmapinfoheader.biHeight = dwHeight;
	bitmapinfoheader.biPlanes = 1;
	bitmapinfoheader.biBitCount = (WORD)dwBPP;
	bitmapinfoheader.biCompression = BI_RGB;
	bitmapinfoheader.biSizeImage = 0;
	bitmapinfoheader.biXPelsPerMeter = 0;
	bitmapinfoheader.biYPelsPerMeter = 0;
	bitmapinfoheader.biClrUsed = dwNumColors;
	bitmapinfoheader.biClrImportant = 0;
	
	// Write bitmap to disk
	HANDLE hfile;
	DWORD dwBytes;
	
	hfile=CreateFile(svArg2,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
	if(hfile==INVALID_HANDLE_VALUE) {
		DeleteObject(bitmap);
		DeleteDC(hdc2);
		DeleteDC(hdc);
		goto  errLabel;
	}
	WriteFile(hfile,&bitmapfileheader,sizeof(BITMAPFILEHEADER), &dwBytes, NULL);
	WriteFile(hfile,&bitmapinfoheader,sizeof(BITMAPINFOHEADER), &dwBytes, NULL);
	if(dwNumColors!=0)
		WriteFile(hfile,colors,sizeof(RGBQUAD)*dwNumColors,&dwBytes,NULL);
	WriteFile(hfile,pBits,(dwWidth*dwHeight*dwBPP)/8,&dwBytes,NULL);
	CloseHandle(hfile);
		
	//  IssueAuthCommandReply(cas_from,comid,0,"Bitmap captured to disk file.\n");
	
	// Clean up
		
	DeleteObject(bitmap);
	DeleteDC(hdc2);
	DeleteDC(hdc);

	iErr  =  0;

errLabel:

	return  iErr;
}

