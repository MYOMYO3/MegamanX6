#include "stdafx.h"
#include "ImageRender.h"
#include "Asset.h"
#include "GAMECORE.h"
#include "Actor.h"
#include <assert.h>


ImageRender::ImageRender()
{
}


ImageRender::~ImageRender()
{
}

void ImageRender::Image(const wchar_t* _Name)
{
	image = Asset::FIndBitImage(_Name);

	if (nullptr == image)
	{
		assert(false);
	}
}

void ImageRender::Render()
{
	// 이미지 세팅안하고 왜씀?????
	if (nullptr == image)
	{
		assert(false);
	}

	// 이녀석의 색깔중에서 특정색깔을
	// 빼줄께!!!!
	// 크기는 내마음대로 할수 있다.

	BitBlt(GameCore::MainWindow().GetHDC(),
		actor->GetPos().IX(), actor->GetPos().IY(),
		45,
		57,
		image->GetDC(),
		79,
		123,
		SRCCOPY);


	//Rectangle(GameCore::MainWindow().GetHDC()
	//	, actor->GetPos().IX() - 5
	//	, actor->GetPos().IY() - 5
	//	, actor->GetPos().IX() + 5
	//	, actor->GetPos().IY() + 5);
}
