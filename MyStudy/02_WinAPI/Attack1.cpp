#include "stdafx.h"
#include "Attack1.h"
#include "AniRender.h"
#include "RectCol.h"
#include "CirclCol.h"
#include "Collision.h"

#include "CircleBomb.h"

#include <JTIME.h>

#define m_PI 3.1415926535

Attack1Bomb::Attack1Bomb()
{
}


Attack1Bomb::~Attack1Bomb()
{
}



bool Attack1Bomb::Init()
{
	aniRender = CreateRender<AniRender>();
	aniRender->SubPivotMode(PIVOT::CENTER);
	aniRender->CreateAnimation(L"L_Bomb", L"LBoss.bmp", 34, 34, true, 0.03f);
	aniRender->CreateAnimation(L"R_Bomb", L"Boss.bmp", 34, 34, true, 0.03f);
	aniRender->PlayAnimation(L"R_Bomb");
	
	
	RectCol* batBombCol = CreateCol<RectCol>(L"MONSTERBOMB", { 20, 40 });
	batBombCol->SubPivotMode(PIVOT::B);

	return true;
}

void Attack1Bomb::Update()
{
	

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

void Attack1Bomb::ColEnter(Collision* _This, Collision* _Other)
{
	int a = 0;
}
void Attack1Bomb::ColStay(Collision* _This, Collision* _Other)
{
	int a = 0;			
}
void Attack1Bomb::ColExit(Collision* _This, Collision* _Other)
{
	int a = 0;
}