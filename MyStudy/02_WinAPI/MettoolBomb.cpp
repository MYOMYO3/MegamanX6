#include "stdafx.h"
#include "MettoolBomb.h"
#include "AniRender.h"
#include "CirclCol.h"

#include "Collision.h"

#include "TransRender.h"
#include "CircleBomb.h"
#include "Map.h"
#include <JTIME.h>


MettoolBomb::MettoolBomb()
{
}


MettoolBomb::~MettoolBomb()
{
}



bool MettoolBomb::Init()
{
	aniRender = CreateRender<AniRender>(14);
	aniRender->SubPivotMode(PIVOT::CENTER);


	aniRender->CreateAnimation(L"L_Bomb", L"L_Mettool.bmp", 25, 28, false, 0.15f);
	aniRender->CreateAnimation(L"R_Bomb", L"R_Mettool.bmp", 25, 28, false, 0.15f);


	aniRender->PlayAnimation(L"L_Bomb");


	CircleCol* wormBombCol = CreateCol<CircleCol>(L"MONSTERBOMB", { 15, 15 });

	return  true;
}

void MettoolBomb::Update()
{
	OutScreenMonster();

	if (dir == 0)
	{
		pos.x -= 100.0f * Time::DeltaTime();
	}
	else
	{
		pos.x += 100.0f * Time::DeltaTime();
	}
}




void MettoolBomb::ColEnter(Collision* _This, Collision* _Other)
{

}

void MettoolBomb::ColStay(Collision* _This, Collision* _Other)
{

}

void MettoolBomb::ColExit(Collision* _This, Collision* _Other)
{

}