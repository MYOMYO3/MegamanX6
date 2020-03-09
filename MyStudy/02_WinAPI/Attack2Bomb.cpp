#include "stdafx.h"
#include "Attack2Bomb.h"
#include "AniRender.h"
#include "RectCol.h"
#include "RectCol.h"
#include "Collision.h"

#include "CircleBomb.h"

#include <JTIME.h>

#define m_PI 3.1415926535

Attack2Bomb::Attack2Bomb() : deathTime(10.0f)
{
}


Attack2Bomb::~Attack2Bomb()
{
}



bool Attack2Bomb::Init()
{


	aniRender = CreateRender<AniRender>();
	aniRender->SubPivotMode(PIVOT::CENTER);
	aniRender->CreateAnimation(L"L_Bomb", L"LBoss.bmp", 44, 44, false, 0.03f);
	aniRender->CreateAnimation(L"R_Bomb", L"Boss.bmp", 44, 44, false, 0.03f);
	aniRender->PlayAnimation(L"R_Bomb");

	RectCol* batBombCol = CreateCol<RectCol>(L"MONSTERBOMB", { 25, 140 });
	batBombCol->SubPivotMode(PIVOT::B);

	return true;
}

void Attack2Bomb::Update()
{
	deathTime -= Time::DeltaTime();

	if (deathTime < 0.0f)
	{
		Die();
	}

	


	if (0 == dir)
	{
		//SetPos({-20.0f, 0.0f});

		aniRender->PlayAnimation(L"L_Bomb");
		pos.x -= 300.0f * Time::DeltaTime();
	}
	else if (1 == dir)
	{
		//SetPos({ 20.0f, 0.0f });

		aniRender->PlayAnimation(L"R_Bomb");
		pos.x += 300.0f * Time::DeltaTime();
	}

}

void Attack2Bomb::ColEnter(Collision* _This, Collision* _Other)
{
	int a = 0;
}
void Attack2Bomb::ColStay(Collision* _This, Collision* _Other)
{
	int a = 0;
}
void Attack2Bomb::ColExit(Collision* _This, Collision* _Other)
{
	int a = 0;
}