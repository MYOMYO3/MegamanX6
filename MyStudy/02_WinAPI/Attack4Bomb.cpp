#include "stdafx.h"
#include "Attack4Bomb.h"
#include "AniRender.h"
#include "RectCol.h"
#include "CirclCol.h"
#include "Collision.h"

#include "CircleBomb.h"
#include "RectCol.h"

#include <JTIME.h>

#define m_PI 3.1415926535

Attack4Bomb::Attack4Bomb() : deathTime( 10.0f)
{
}


Attack4Bomb::~Attack4Bomb()
{
}



bool Attack4Bomb::Init()
{
	//aniRender->CreateAnimation(L"L_Attack4Bomb", L"LBoss.bmp", 78, 81, true, 0.1f);
	//aniRender->CreateAnimation(L"L_Attack4Particle", L"LBoss.bmp", 82, 86, true, 0.1f);

	aniRender = CreateRender<AniRender>();
	aniRender->SubPivotMode(PIVOT::CENTER);
	aniRender->CreateAnimation(L"Bomb", L"LBoss.bmp", 78, 81, true, 0.01f);
	aniRender->PlayAnimation(L"Bomb");


	particleRender = CreateRender<AniRender>();
	particleRender->SubPivotMode(PIVOT::CENTER);
	particleRender->CreateAnimation(L"BombParitlce", L"Boss.bmp", 82, 86, false, 0.03f);
	particleRender->CreateAnimation(L"None", L"LBoss.bmp", 111, 111, false, 0.1f);
	particleRender->PlayAnimation(L"None");


	RectCol* batBombCol = CreateCol<RectCol>(L"MONSTERBOMB", { 25, 60 });
	batBombCol->SubPivotMode(PIVOT::B);

	return true;
}

void Attack4Bomb::Update()
{
	deathTime -= Time::DeltaTime();

	if (deathTime < 0.0f)
	{
		Die();
	}

	particleRender->PlayAnimation(L"BombParitlce");

	aniRender->PlayAnimation(L"Bomb");
	pos.y -= 200.0f * Time::DeltaTime();
	
	
}

void Attack4Bomb::ColEnter(Collision* _This, Collision* _Other)
{
	int a = 0;
}
void Attack4Bomb::ColStay(Collision* _This, Collision* _Other)
{
	int a = 0;
}
void Attack4Bomb::ColExit(Collision* _This, Collision* _Other)
{
	int a = 0;
}