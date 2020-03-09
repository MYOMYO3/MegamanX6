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
	// �̹��� ���þ��ϰ� �־�?????
	if (nullptr == image)
	{
		assert(false);
	}

	// �̳༮�� �����߿��� Ư��������
	// ���ٲ�!!!!
	// ũ��� ��������� �Ҽ� �ִ�.

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
