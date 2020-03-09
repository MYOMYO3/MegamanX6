// include ����
// �⺻ ���̺귯��(WIndows.h, std)
// �ܺ� ���̺귯��(��ü ���̺귯�� ��)
// project ���
#include "stdafx.h"
#include "TransRender.h"
#include "Asset.h"
#include "GAMECORE.h"
#include "Actor.h"

#include "RenderMgr.h"

#include <assert.h>


// �����쿡�� �����ϴ� API�׷��� ���̺귯����
// Ȯ�� ���̺귯���� �����Ѵٴ� �ڵ带 �ľ��Ѵ�.
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
	// �̹��� ���þ��ϰ� �־�?????
	if (nullptr == sprite)
	{
		assert(false);
	}

	// �̳༮�� �����߿��� Ư��������
	// ���ٲ�!!!!
	// ũ��� ��������� �Ҽ� �ִ�.

	transRender = ColorRGB();

	if (false == isCustomSize)
	{
		SpriteSizeOn();
	}

	//zz zzzz����ؼ� �־���� �Ѵ�.
	Pos renderPos = CalPivotPos();

	//Rectangle(RenderMgr::BACKDC()
	//	, renderPos.IX()
	//	, renderPos.IY()
	//	, renderPos.IX() + renderRect.size.IX()
	//	, renderPos.IY() + renderRect.size.IY());


	// ���� ������ �׳� �̹��� ũ�� �״�� ����ϴ°�,.
	// �ǵ����̸� �̹��� ũ���� ����̰ų�
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
