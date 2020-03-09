#include "stdafx.h"
#include "SubBossBomb.h"
#include "AniRender.h"
#include "GAMECORE.h"
#include <GEOMETRY.h>
#include <JTIME.h>
#include "RenderMgr.h"
#include "TransRender.h"
#include "Map.h"

SubBossBomb::SubBossBomb() : state(0)
{
}


SubBossBomb::~SubBossBomb()
{

}


bool SubBossBomb::Init()
{
	aniRender = CreateRender<AniRender>(11);
	aniRender->SubPivotMode(PIVOT::CENTER);

	aniRender->CreateAnimation(L"Start",  L"SubBullet.bmp", 6, 9, true, 0.2f);
	
	aniRender->CreateAnimation(L"Moving", L"SubBullet.bmp", 10, 13, true, 0.1f);
	aniRender->CreateAnimation(L"Bomb",   L"SubBullet.bmp", 0, 5, false, 0.1f);
	aniRender->CreateAnimation(L"None", L"SubBullet.bmp", 29, 29, false, 0.1f);

	aniRender->PlayAnimation(L"Start");


	map = Map::Inst();

	return true;
}

void SubBossBomb::Update()
{
	GroundCheck();
	if ( 0 == state)
	{
		pos.y += 100.0f * Time::DeltaTime();
		pos.x += angle * 100.0f * Time::DeltaTime();

		if (aniRender->GetCurAni()->aniEnd == true)
		{
			state = 1;
		}
	}
	else if (state == 1)
	{
		pos.y += 100.0f * Time::DeltaTime();
		pos.x += angle * 100.0f * Time::DeltaTime();
		aniRender->PlayAnimation(L"Moving");
	}
	else if (state == 2)
	{
		aniRender->PlayAnimation(L"Bomb");

		if (aniRender->GetCurAni()->aniEnd == true)
		{
			//Off();
			Die();
		}
	}


}

void SubBossBomb::CalAngle()
{
	Pos Start = { pos };
	Pos End = GameCore::MainWindow().MousePos();
	Pos Pivot = Start - End;

	float value = GeoMath::PointDistacne({ 0,0 }, Pivot);
	Pivot = Pivot / value;
	value = GeoMath::PointDistacne({ 0,0 }, Pivot);
	
}

void SubBossBomb::SetMap(Map* _Map)
{
	map = _Map;
}

bool SubBossBomb::GroundCheck()
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
	int posColor = sprite->PosToColor(pos -map->GetPos());;

	if (checkColor == posColor)
	{
		state = 2;

		return true;
	}

	return false;	
}

/////////////////////COL

void SubBossBomb::ColEnter(Collision* _This, Collision* _Other)
{

}

void SubBossBomb::ColStay(Collision* _This, Collision* _Other)
{

}

void SubBossBomb::ColExit(Collision* _This, Collision* _Other)
{

}
