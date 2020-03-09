#include "stdafx.h"
#include "BatBomb.h"
#include "AniRender.h"
#include "RectCol.h"

#include "Collision.h"

#include "CircleBomb.h"
#include "Map.h"
#include "TransRender.h"
#include <JTIME.h>
#include <Sound.h>

#define m_PI 3.1415926535


BatBomb::BatBomb() : deathTime(100.0f), state(0)
{
	hp = 15;
	deadSound = false;
}


BatBomb::~BatBomb()
{

}



bool BatBomb::Init()
{
	aniRender = CreateRender<AniRender>(14);
	aniRender->SubPivotMode(PIVOT::CENTER);

	aniRender->CreateAnimation(L"BombIdle", L"Bat.bmp", 12, 12, false, 0.05f);

	aniRender->CreateAnimation(L"BombAttack", L"Bat.bmp", 12, 14, true, 0.05f);	
	aniRender->CreateAnimation(L"Die", L"Explosion.bmp", 0, 21, false, 0.03f);
	
	aniRender->PlayAnimation(L"BombIdle");
	

	RectCol* batBombCol = CreateCol<RectCol>(L"MONSTERBOMB", { 30, 30 });

	
	map = Map::Inst();
	return true;
}

void BatBomb::Update()
{
	OutScreenMonster();
	GroundCheck(); 
	if (hp <= 0 || state == 4)
	{
		if (deadSound == false)
		{
			Sound::SoundPlay(L"E_Explosion3.wav");
			deadSound = true;
		}

		aniRender->PlayAnimation(L"Die");
		if (aniRender->GetCurAni()->aniEnd == true)
		{
			Die();
		}
	}

	if (0 == state)
	{
		///noop
	}
	else if (1 == state)
	{
		aniRender->PlayAnimation(L"BombAttack");
		pos.y += 100.0f * Time::DeltaTime();
	}




}
void BatBomb::GroundCheck()
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
		//pos.y += 500.0f * Time::DeltaTime();

	}
	else
	{
		if(checkColor == sprite->PosToColor(pos - map->GetPos()))
		{
			hp = 0;		
			state = 3;
		}
	}
}

void BatBomb::ColEnter(Collision* _This, Collision* _Other)
{
	int a = 0;
}
void BatBomb::ColStay(Collision* _This, Collision* _Other)
{

}
void BatBomb::ColExit(Collision* _This, Collision* _Other)
{

}