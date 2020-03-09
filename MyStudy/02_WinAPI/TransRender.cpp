// include 순서
// 기본 라이브러리(WIndows.h, std)
// 외부 라이브러리(자체 라이브러리 등)
// project 헤더
#include "stdafx.h"
#include "TransRender.h"
#include "Asset.h"
#include "GAMECORE.h"
#include "Actor.h"

#include "RenderMgr.h"

#include <assert.h>


// 윈도우에서 지원하는 API그래픽 라이브러리의
// 확장 라이브러리를 적용한다는 코드를 쳐야한다.
#pragma comment(lib, "msimg32.lib")



TransRender::TransRender()
{
}


TransRender::~TransRender()
{
}



void TransRender::Sprite(const wchar_t * _Name, int _Index)
{
	sprite = Asset::FIndSprite(_Name);
	index = _Index;

	if (nullptr == sprite)
	{
		assert(false);
	}

	if (false == isCustomSize)
	{
		SpriteSizeOn();
	}
}

void TransRender::SpriteSizeOn()
{
	subRect.size = (*sprite)[index].size;
}

void TransRender::Render()
{
	// 이미지 세팅안하고 왜씀?????
	if (nullptr == sprite)
	{
		assert(false);
	}

	// 이녀석의 색깔중에서 특정색깔을
	// 빼줄께!!!!
	// 크기는 내마음대로 할수 있다.

	transRender = ColorRGB();

	if (false == isCustomSize)
	{
		SpriteSizeOn();
	}

	//zz zzzz계산해서 넣어줘야 한다.
	Pos renderPos = CalPivotPos();

	//Rectangle(RenderMgr::BACKDC()
	//	, renderPos.IX()
	//	, renderPos.IY()
	//	, renderPos.IX() + renderRect.size.IX()
	//	, renderPos.IY() + renderRect.size.IY());


	// 가장 빠른건 그냥 이미지 크기 그대로 사용하는것,.
	// 되도록이면 이미지 크기의 배수이거나
	if (255 <= BF.SourceConstantAlpha)
	{
		TransparentBlt(
			RenderMgr::BACKDC(),
			renderPos.IX(),
			renderPos.IY(),
			subRect.size.IX(),
			subRect.size.IY(),
			sprite->GetImage()->GetDC(),
			(*sprite)[index].pos.IX(),
			(*sprite)[index].pos.IY(),
			(*sprite)[index].size.IX(),
			(*sprite)[index].size.IY(),
			transRender.m_Color
		);
	}
	else
	{
		AlphaBlend(
			RenderMgr::BACKDC(),
			renderPos.IX(),
			renderPos.IY(),
			subRect.size.IX(),
			subRect.size.IY(),
			sprite->GetImage()->GetDC(),
			(*sprite)[index].pos.IX(),
			(*sprite)[index].pos.IY(),
			(*sprite)[index].size.IX(),
			(*sprite)[index].size.IY(),
			BF
		);
	}




	//Rectangle(RenderMgr::BACKDC()
	//	, renderPos.IX() - 5
	//	, renderPos.IY() - 5
	//	, renderPos.IX() + 5
	//	, renderPos.IY() + 5);

	//Rectangle(RenderMgr::BACKDC()
	//	, actor->GetPos().IX() - 5
	//	, actor->GetPos().IY() - 5
	//	, actor->GetPos().IX() + 5
	//	, actor->GetPos().IY() + 5);
}
