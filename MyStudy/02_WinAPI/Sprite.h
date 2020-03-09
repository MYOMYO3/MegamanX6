#pragma once

#include "Image.h"
#include <assert.h>

class Asset;
class Sprite
{
	friend Asset;

private:
	//어떤 이미지를 기반으로
	Image* image;
	std::vector<Rect> spriteRect;
	//Image* leftImage;

public:
	int PosToColor(Pos _Pos);

public:
	Image* GetImage()
	{
		return image;
	}

	bool IsMulti()
	{
		return 1 < spriteRect.size();
	}

	bool Count()
	{
		return spriteRect.size();
	}

	Rect GetRect(int _Count = 0)
	{
		if (0 >= spriteRect.size())
		{
			assert(false);
		}

		return spriteRect[_Count];
	}

public:
	Rect operator[](int _Index)
	{
		if (0 >= spriteRect.size())
		{
			assert(false);
		}

		return spriteRect[_Index];
	}

public:
	void Cut(int _X, int _Y, bool _Reverse = false);


private:
	Sprite(Image* _Image);
	~Sprite();
};

