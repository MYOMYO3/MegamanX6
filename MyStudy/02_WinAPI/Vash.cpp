#include "stdafx.h"
#include "Vash.h"
#include "CirclCol.h"
#include "RectCol.h"
#include "AniRender.h"
#include <JTIME.h>

bool Vash::Init()
{
	aniRender = CreateRender<AniRender>(11);
	aniRender->SubPivotMode(PIVOT::CENTER);

	aniRender->CreateAnimation(L"R_IsCol", L"CollideParticle.bmp", 8, 12, false, 0.03f);
	aniRender->CreateAnimation(L"L_IsCol", L"LCollideParticle.bmp", 8, 12, false, 0.03f);
	aniRender->CreateAnimation(L"None", L"CollideParticle.bmp", 13, 13, false, 0.05f);

	aniRender->PlayAnimation(L"None");

	RectCol* rectCol = CreateCol<RectCol>(L"PLAYERATTACK", { 55, 65 });
	rectCol->SubPivotMode(PIVOT::LT);
	   


	return true;
}

void Vash::Update()
{
	if (isCol == true)
	{
		if (dir == 1)
		{
			aniRender->RenderPos({-45.0f, -30.0f});
 			aniRender->PlayAnimation(L"R_IsCol");
		}
		else
		{
			aniRender->RenderPos({ -40.0f, -30.0f});
			aniRender->PlayAnimation(L"L_IsCol");
		}
	}

	deathTime -= Time::DeltaTime();

	if (0 >= deathTime)
	{
		Die();
		//Off();
	}

	//pos.x += 100.0f * Time::DeltaTime();
}


void Vash::ColEnter(Collision* _This, Collision* _Other)
{
	int a = 0;
	_Other->GetActor()->Damaged(att);
}

void Vash::ColStay(Collision* _This, Collision* _Other)
{
	int a = 0;

	isCol = true;
}

void Vash::ColExit(Collision* _This, Collision* _Other)
{
	int a = 0;
}

Vash::Vash() : deathTime ( 0.20f), isCol(false)
{
	att = 15;
}


Vash::~Vash()
{
}
