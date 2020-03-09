#include "stdafx.h"
#include "D1000Bomb.h"
#include "AniRender.h"
#include "RectCol.h"
#include <JTIME.h>

#include "Map.h"
#include "TransRender.h"


D1000Bomb::D1000Bomb(): deathTime(5.0f)
{
}


D1000Bomb::~D1000Bomb()
{
}

bool D1000Bomb::Init()
{
	aniRender = CreateRender<AniRender>(14);
	aniRender->SubPivotMode(PIVOT::CENTER);


	aniRender->CreateAnimation(L"L_Bomb", L"D1000.bmp", 7, 13, true, 0.15f);
	//aniRender->CreateAnimation(L"R_Bomb", L"D1000.bmp", 25, 28, false, 0.15f);


	aniRender->PlayAnimation(L"L_Bomb");


	RectCol* d1000Bomb = CreateCol<RectCol>(L"MONSTERBOMB", { 30, 30 });

	map = Map::Inst();

	return  true;
}

void D1000Bomb::Update()
{
	OutScreenMonster();


	deathTime -= Time::DeltaTime();

	if (0.0f > deathTime)
	{
		Die();
	}



	GroundCheck();

	pos.x -= 100.0f * Time::DeltaTime();
}

void D1000Bomb::GroundCheck()
{
#pragma region EXCEPT
	if (nullptr == map)
	{
		assert(false);
	}

	TransRender* render = map->GetPixelRender();

	if (nullptr == render)
	{
		assert(false);
	}

	Sprite* sprite = render->GetSprite();

	if (nullptr == sprite)
	{
		assert(false);
	}
#pragma endregion
	int checkColor = 0; // 검정색

	/*char* p = (char*)&mouseColor;	//마우스 포지션 색체크
	mouseColor = sprite->PosToColor({ pos.x - 640.0f + GameCore::MainWindow().MousePos().x,
										pos.y - 400.0f + GameCore::MainWindow().MousePos().y });*/
	int posColor = 0;
	posColor = sprite->PosToColor(pos + Pos{ 0.0f, 1.0f } -map->GetPos());;
	//groundColor = sprite->PosToColor(pos + Pos{ 0.0f, 20.0f } -map->GetPos());;

	if (checkColor != posColor)
	{
		pos.y += 500.0f * Time::DeltaTime();

	}
	else
	{
		while (checkColor == sprite->PosToColor(pos - map->GetPos()))
		{
			CalDebugPos(pos);
			pos -= {0.0f, 1.0f};
		}
	}
}

void D1000Bomb::ColEnter(Collision* _This, Collision* _Other)
{
	int a = 0;
}
void D1000Bomb::ColStay(Collision* _This, Collision* _Other)
{

}
void D1000Bomb::ColExit(Collision* _This, Collision* _Other)
{

}
