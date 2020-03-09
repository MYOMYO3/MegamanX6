#include "stdafx.h"
#include "PlayerLittleBullet.h"
#include "AniRender.h"
#include "CirclCol.h"

#include "Collision.h"

#include <JTIME.h>
#include <Sound.h>


bool PlayerLittleBullet::Init()
{
	aniRender = CreateRender<AniRender>(20);
	aniRender->SubPivotMode(PIVOT::CENTER);

	aniRender->CreateAnimation(L"R_LittleBullet", L"PlayerLittleBullet.bmp", 0, 4, true, 0.05f);
	aniRender->CreateAnimation(L"L_LittleBullet", L"LPlayerLittleBullet.bmp", 0, 4, true, 0.05f);
	aniRender->CreateAnimation(L"R_ColEnter", L"CollideParticle.bmp", 0, 3, false, 0.03f);
	aniRender->CreateAnimation(L"L_ColEnter", L"LCollideParticle.bmp", 0, 3, false, 0.03f);
	//aniRender->CreateAnimation(L"Attack", L"Bat.bmp", 5, 12, true, 0.05f);

	aniRender->PlayAnimation(L"R_LittleBullet");
	aniRender->DebugOff();

	CircleCol* bulletCol = CreateCol<CircleCol>(L"PLAYERATTACK", { 12, 12 });


	return true;
}
void PlayerLittleBullet::Update()
{
	int a = 0;
	deathTime -= Time::DeltaTime();

	if (0 >= deathTime)
	{
		Die();
	}


	if (isCol == true)
	{
		if (dir == 1)
		{
			aniRender->PlayAnimation(L"R_ColEnter");

			if (aniRender->GetCurAni()->aniEnd == true)
			{
				Die();
			}
		}
		else
		{
			aniRender->PlayAnimation(L"L_ColEnter");

			if (aniRender->GetCurAni()->aniEnd == true)
			{
				Die();
			}
		}


		return;
	}

	if (dir == 1) //1 == RIGHT
	{
		aniRender->PlayAnimation(L"R_LittleBullet");
		pos.x += 300.0f * Time::DeltaTime();
	}
	else
	{
		aniRender->PlayAnimation(L"L_LittleBullet");
		pos.x -= 300.0f * Time::DeltaTime();
	}

	
}

void PlayerLittleBullet::ColEnter(Collision* _This, Collision* _Other)
{
	int a = 0;


	isCol = true;

	_Other->GetActor()->Damaged(att);

	Sound::SoundPlay(L"E_BusterHit.wav");
	
}
void PlayerLittleBullet::ColStay(Collision* _This, Collision* _Other)
{
	
	
}
void PlayerLittleBullet::ColExit(Collision* _This, Collision* _Other)
{
	int a = 0;
}

PlayerLittleBullet::PlayerLittleBullet() : deathTime(300.0f), isCol(false)
{
	att = 5;
}


PlayerLittleBullet::~PlayerLittleBullet()
{
}
