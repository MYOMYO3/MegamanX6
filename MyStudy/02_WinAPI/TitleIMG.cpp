#include "stdafx.h"
#include "TitleIMG.h"
#include <window.h>
#include <JTIME.h>
#include "GAMECORE.h"
#include "Bullet.h"
#include <JTIME.h>
#include <Input.h>
//#include "Render.h"
#include "ImageRender.h"
#include "TransRender.h"
#include "AniRender.h"


bool spriteActor::Init()
{
	//render = CreateRender<TransRender>();
	//render->SubPivotMode(PIVOT::LT);
	//render->Sprite(L"Title.bmp", 0);



	return true;
}

void spriteActor::InitTrRender(const wchar_t* _FileName)
{
	render = CreateRender<TransRender>();
	render->SubPivotMode(PIVOT::LT);
	render->Sprite(_FileName, 0);
}

void spriteActor::InitAniRender(/*const wchar_t* _FileName*/)
{
	aniRender1 = CreateRender<AniRender>();
	aniRender1->SubPivotMode(PIVOT::LT);
	aniRender1->RenderPos({210.0f, 35.0f});

	//
	aniRender1->CreateAnimation(L"None", L"Playerselect.bmp", 3, 3, false, 0.1f);
	aniRender1->CreateAnimation(L"Megaman", L"Playerselect.bmp", 0, 2, true, 0.1f);
	//aniRender->CreateAnimation(L"X", L"X4Playerselect.bmp", 4, 4, true, 0.1f);
	//aniRender->CreateAnimation(L"Zero", L"X4Playerselect.bmp", 5, 5, false, 0.1f);
	//aniRender->CreateAnimation(L"Zero", L"X4Playerselect.bmp", 5, 5, false, 0.1f);
	//aniRender->CreateAnimation(L"ZeroSelect", L"X4Playerselect.bmp", 6, 8, true, 0.1f);
	//aniRender->CreateAnimation(L"XSelect", L"X4Playerselect.bmp", 9, 11, true, 0.1f);



	aniRender1->PlayAnimation(L"None");

	aniRender2 = CreateRender<AniRender>();
	aniRender2->SubPivotMode(PIVOT::LT);
	aniRender2->RenderPos({ -33.0f, -10.0f });
	//
	aniRender2->CreateAnimation(L"None", L"Playerselect.bmp", 3, 3, false, 0.1f);
	aniRender2->CreateAnimation(L"Megaman", L"Playerselect.bmp", 4, 6, true, 0.1f);
	//aniRender->CreateAnimation(L"X", L"X4Playerselect.bmp", 4, 4, true, 0.1f);
	//aniRender->CreateAnimation(L"Zero", L"X4Playerselect.bmp", 5, 5, false, 0.1f);
	//aniRender->CreateAnimation(L"Zero", L"X4Playerselect.bmp", 5, 5, false, 0.1f);
	//aniRender->CreateAnimation(L"ZeroSelect", L"X4Playerselect.bmp", 6, 8, true, 0.1f);
	//aniRender->CreateAnimation(L"XSelect", L"X4Playerselect.bmp", 9, 11, true, 0.1f);



	aniRender2->PlayAnimation(L"Megaman");

}

void spriteActor::Update()
{

	if (aniRender1 != nullptr && aniRender2 != nullptr)
	{
		if (selectMegaman == 0)
		{
			aniRender1->PlayAnimation(L"Megaman");
			aniRender2->PlayAnimation(L"None");
		}
		else
		{
			aniRender2->PlayAnimation(L"Megaman");
			aniRender1->PlayAnimation(L"None");
		}
	}

}

spriteActor::spriteActor() : selectMegaman(1)
{
}


spriteActor::~spriteActor()
{
}
