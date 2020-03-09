#include "stdafx.h"
#include "Attack3Bomb.h"
#include "AniRender.h"
#include "RectCol.h"
#include "RectCol.h"
#include "Collision.h"

#include "CircleBomb.h"

#include <JTIME.h>

#define m_PI 3.1415926535

Attack3Bomb::Attack3Bomb() : deathTime(10.0f)
{
}


Attack3Bomb::~Attack3Bomb()
{
}



bool Attack3Bomb::Init()
{
	//aniRender->CreateAnimation(L"L_Attack4Bomb", L"LBoss.bmp", 78, 81, true, 0.1f);
	//aniRender->CreateAnimation(L"L_Attack4Particle", L"LBoss.bmp", 82, 86, true, 0.1f);

	aniRender = CreateRender<AniRender>();
	aniRender->SubPivotMode(PIVOT::CENTER);
	aniRender->CreateAnimation(L"L_Bomb", L"LBoss.bmp", 58, 61, true, 0.03f);
	aniRender->CreateAnimation(L"R_Bomb", L"Boss.bmp", 58, 61, true, 0.03f);
	aniRender->PlayAnimation(L"R_Bomb");


	/*particleRender = CreateRender<AniRender>();
	particleRender->SubPivotMode(PIVOT::CENTER);
	particleRender->CreateAnimation(L"BombParitlce", L"Boss.bmp", 82, 86, false, 0.05f);
	particleRender->CreateAnimation(L"None", L"LBoss.bmp", 111, 111, false, 0.1f);
	particleRender->PlayAnimation(L"None");
*/

	RectCol* attack3BombCol = CreateCol<RectCol>(L"MONSTERBOMB", { 40, 25 });
	attack3BombCol->SubPivotMode(PIVOT::B);

	return true;
}

void Attack3Bomb::Update()
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
		pos.x -= 200.0f * Time::DeltaTime();
	}
	else if (1 == dir)
	{
		//SetPos({ 20.0f, 0.0f });

		aniRender->PlayAnimation(L"R_Bomb");
		pos.x += 200.0f * Time::DeltaTime();
	}


}

void Attack3Bomb::ColEnter(Collision* _This, Collision* _Other)
{
	int a = 0;
}
void Attack3Bomb::ColStay(Collision* _This, Collision* _Other)
{
	int a = 0;
}
void Attack3Bomb::ColExit(Collision* _This, Collision* _Other)
{
	int a = 0;
}