#pragma once
#include <Directory.h>
#include <GEOMETRY.h>
#include <windows.h>


class Asset;
class Image
{
public:
	friend Asset;
	

private:
	Size				size;	

	HDC					image;
	HBITMAP				hBitMap;
	HBITMAP				hOldBitMap;

	BITMAPFILEHEADER	bitFIleHeader;
	BITMAPINFOHEADER	bitMapInfo;

public:
	int PosToColor(Pos _Pos);

public:
	Size GetSize() { return size; }
	HDC  GetDC() { return image; }


	//bool Create	(Size _Size);
	bool Load	(const wchar_t* _Path); 
	bool Create(Size _Size);
	void CalculateSize(const wchar_t* _Path);

public:
	Image();
	~Image();
};

