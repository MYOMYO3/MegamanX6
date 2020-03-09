#include "stdafx.h"
#include "WormBomb.h"
#include "AniRender.h"
#include "CirclCol.h"

#include "Collision.h"

#include "CircleBomb.h"

#include <JTIME.h>

#define m_PI 3.1415926535


WormBomb::WormBomb() : deathTime(100.0f), state(0), dir(0)
{
}


WormBomb::~WormBomb()
{

}



bool WormBomb::Init()
{
	aniRender = CreateRender<AniRender>(14);
	aniRender->SubPivotMode(PIVOT::CENTER);


	aniRender->CreateAnimation(L"BombIdle", L"Worm.bmp", 24, 24, false, 0.05f);

	
	aniRender->PlayAnimation(L"BombIdle");


	CircleCol* wormBombCol = CreateCol<CircleCol>(L"MONSTERBOMB", { 30, 30 });

	return true;
}

void WormBomb::Update()
{
	
	if (dir == 0)
	{
		pos.x -= 100.0f * Time::DeltaTime();
	}
	else
	{
		pos.x += 100.0f * Time::DeltaTime();
	}

}

void WormBomb::ColEnter(Collision* _This, Collision* _Other)
{
	int a = 0;
}
void WormBomb::ColStay(Collision* _This, Collision* _Other)
{

}
void WormBomb::ColExit(Collision* _This, Collision* _Other)
{

}


