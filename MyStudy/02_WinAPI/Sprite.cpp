#include "stdafx.h"
#include "Sprite.h"


Sprite::Sprite(Image* _Image) : image(_Image)
{
}


Sprite::~Sprite()
{
}

int Sprite::PosToColor(Pos _Pos)
{
	return image->PosToColor(_Pos);
}

void Sprite::Cut(int _X, int _Y, bool _Reverse)
{
	Size size = { image->GetSize().x / _X, image->GetSize().y / _Y };
	

	Rect rect;

	if (false == _Reverse)
	{
		//정방향 스프라이트
		Pos pos = Pos::ZERO;
		for (int y = 0; y < _Y; ++y)
		{
			for (int x = 0; x < _X; ++x)
			{
				rect.pos = pos;
				rect.size = size;
				spriteRect.push_back(rect);
				pos.x += size.x;
			}
			pos.y += size.y;
			pos.x = 0;
		}
	}
	else
	{
		//리버스 스파리이트 포지션 
		Pos pos = { image->GetSize().x - image->GetSize().x / _X , 0.0f };
		for (int y = 0; y < _Y; ++y)
		{
			for (int x = 0; x < _X; ++x)
			{
				rect.pos = pos;
				rect.size = size;
				spriteRect.push_back(rect);
				pos.x -= size.x;
			}

			pos.y += size.y;
			pos.x = image->GetSize().x - image->GetSize().x / _X;
		}
	}



	


}