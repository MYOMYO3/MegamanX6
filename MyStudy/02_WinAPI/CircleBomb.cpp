#include "stdafx.h"
#include "CircleBomb.h"
#include "AniRender.h"
#include "CirclCol.h"

#include "Collision.h"

#include <JTIME.h>


CircleBomb::CircleBomb() : deathTime(1.0f)
{
	att = 10;
}


CircleBomb::~CircleBomb()
{
}


bool CircleBomb::Init()
{
	aniRender = CreateRender<AniRender>(16);
	aniRender->SubPivotMode(PIVOT::CENTER);

	aniRender->CreateAnimation(L"CircleBombAll", L"PlayerBigBullet.bmp", 7, 12, true, 0.05f);
	aniRender->CreateAnimation(L"CircleBomb", L"PlayerBigBullet.bmp", 7, 10, true, 0.05f);


	CircleCol* circleBomb = CreateCol<CircleCol>(L"PLAYERATTACK", { 30, 30 });
	

	return true;
}



void CircleBomb::Update()
{
	aniRender->PlayAnimation(L"CircleBombAll");

	deathTime -= Time::DeltaTime();
	if (0 >= deathTime)
	{
		Die();
	}
}

void CircleBomb::ColEnter(Collision* _This, Collision* _Other)
{
	_Other->GetActor()->Damaged(att);
}
void CircleBomb::ColStay(Collision* _This, Collision* _Other)
{
	
}
void CircleBomb::ColExit(Collision* _This, Collision* _Other)
{

}
