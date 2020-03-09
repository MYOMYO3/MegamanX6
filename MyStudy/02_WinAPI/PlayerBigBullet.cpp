#include "stdafx.h"
#include "PlayerBigBullet.h"



#include "AniRender.h"
#include "CirclCol.h"

#include "Collision.h"

#include "CircleBomb.h"

#include <JTIME.h>
#include <Sound.h>


bool PlayerBigBullet::Init()
{
	aniRender = CreateRender<AniRender>(11);
	aniRender->SubPivotMode(PIVOT::CENTER);

	aniRender->CreateAnimation(L"R_BigBulletAll", L"PlayerBigBullet.bmp", 0, 6, false, 0.05f);
	aniRender->CreateAnimation(L"R_BigBullet", L"PlayerBigBullet.bmp", 3, 6, true, 0.05f);
	
	
	//aniRender->CreateAnimation(L"R_BigBulletCircleAll", L"PlayerBigBullet.bmp", 7, 12, false, 0.05f);
	//aniRender->CreateAnimation(L"R_BigBulletCircle", L"PlayerBigBullet.bmp", 7, 10, true, 0.05f);

	aniRender->CreateAnimation(L"L_BigBulletAll", L"LPlayerBigBullet.bmp", 0, 4, false, 0.05f);
	aniRender->CreateAnimation(L"L_BigBullet", L"LPlayerBigBullet.bmp", 3, 4, true, 0.05f);
	
	aniRender->CreateAnimation(L"R_ColEnter", L"CollideParticle.bmp", 5, 8, false, 0.03f);
	aniRender->CreateAnimation(L"L_ColEnter", L"LCollideParticle.bmp", 5, 8, false, 0.03f);
	
	//aniRender->CreateAnimation(L"L_BigBulletCircleAll", L"LPlayerBigBullet.bmp", 7, 12, false, 0.05f);
	//aniRender->CreateAnimation(L"L_BigBulletCircle", L"LPlayerBigBullet.bmp", 7, 10, true, 0.05f);
	//aniRender->CreateAnimation(L"Attack", L"Bat.bmp", 5, 12, true, 0.05f);

	aniRender->PlayAnimation(L"R_BigBullet");
	//aniRender->DebugOff();

	CircleCol* bulletCol = CreateCol<CircleCol>(L"PLAYERATTACK", { 30, 30 });

	return true;
}
void PlayerBigBullet::Update()
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
				CircleBomb* bomb = CreateActor<CircleBomb>();
				if (dir == 1)
				{
					bomb->SetPos(pos + Pos{ 10.0f, 0.0f });
				}
				else
				{
					bomb->SetPos(pos + Pos{ -10.0f, 0.0f });
				}
			}
		}
		else
		{
			aniRender->PlayAnimation(L"L_ColEnter");

			if (aniRender->GetCurAni()->aniEnd == true)
			{
				Die();
				CircleBomb* bomb = CreateActor<CircleBomb>();
				if (dir == 1)
				{
					bomb->SetPos(pos + Pos{ 10.0f, 0.0f });
				}
				else
				{
					bomb->SetPos(pos + Pos{ -10.0f, 0.0f });
				}
			}
		}


		return;
	}





	if (dir == 1) //1 == RIGHT
	{

		if (isStartBullet == true)
		{
			aniRender->PlayAnimation(L"R_BigBulletAll");
		}
		else
		{
			aniRender->PlayAnimation(L"R_BigBullet");
		}

		if (aniRender->GetCurAni()->aniEnd == true && isStartBullet == true)
		{
			isStartBullet = false;
		}

		pos.x += 400.0f * Time::DeltaTime();
	}
	else
	{
		if (isStartBullet == true)
		{
			aniRender->PlayAnimation(L"L_BigBulletAll");
		}
		else
		{
			aniRender->PlayAnimation(L"L_BigBullet");
		}

		if (aniRender->GetCurAni()->aniEnd == true && isStartBullet == true)
		{
			isStartBullet = false;
		}

		pos.x -= 400.0f * Time::DeltaTime();
	}
}

void PlayerBigBullet::ColEnter(Collision* _This, Collision* _Other)
{
	int a = 0;

	isCol = true;
	//PlayerLittleBullet* littleBullet = CreateActor<PlayerLittleBullet>();
	_Other->GetActor()->Damaged(att);

	Sound::SoundPlay(L"E_BusterHit.wav");

}

void PlayerBigBullet::ColStay(Collision* _This, Collision* _Other)
{

}

void PlayerBigBullet::ColExit(Collision* _This, Collision* _Other)
{
	int a = 0;
}


PlayerBigBullet::PlayerBigBullet() : deathTime(300.0f), isStartBullet(true), isCol(false)
{
	att = 15;
}


PlayerBigBullet::~PlayerBigBullet() 
{
}
