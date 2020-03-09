#include "stdafx.h"
#include "Image.h"
#include <FILE.h>

#include "GAMECORE.h"
#include <WINDOW.h>
#include <assert.h>

Image::Image() : image(nullptr), size({ 0,0 }), hBitMap(nullptr), hOldBitMap(nullptr)
{
}


Image::~Image()
{
	DeleteObject(hOldBitMap);
	DeleteDC(image);
}

int Image::PosToColor(Pos _Pos)
{
	if (_Pos.IX() < 0)
	{
		return 0;
	}

	if (_Pos.IY() < 0)
	{
		return 0;
	}

	if (_Pos.IX() >= size.IX())
	{
		return 0;
	}

	if (_Pos.IY() >= size.IY())
	{
		return 0;
	}

	return GetPixel(image, _Pos.IX(), _Pos.IY());
}

bool Image::Load(const wchar_t* _Path)
{
	hBitMap = (HBITMAP)LoadImageW(nullptr, _Path, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (nullptr == hBitMap)
	{
		assert(false);
		return false;
	}

	image = CreateCompatibleDC(nullptr);
	hOldBitMap = (HBITMAP)SelectObject(image, hBitMap);

	if (nullptr == image)
	{
		assert(false);
	}

	CalculateSize(_Path);

	return true;
}

bool Image::Create(Size _Size)
{
	image = CreateCompatibleDC(nullptr);
	hBitMap = CreateCompatibleBitmap(GameCore::MainWindow().GetHDC(), _Size.IX(), _Size.IY());

	if (nullptr == image || nullptr == hBitMap)
	{
		assert(false);
	}

	hOldBitMap = (HBITMAP)SelectObject(image, hBitMap);

	if (nullptr == image)
	{
		assert(false);
	}

	size = _Size;

	return true;
}

void Image::CalculateSize(const wchar_t* _Path)
{
	FileRBStream stream = FileRBStream(_Path);
	stream >> bitFIleHeader;
	stream >> bitMapInfo;

	size.y = (float)bitMapInfo.biHeight;
	size.x = (float)bitMapInfo.biWidth;
}