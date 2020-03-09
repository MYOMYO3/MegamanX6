#include "stdafx.h"
#include "Worm.h"
#include <window.h>
#include <JTIME.h>
#include "GAMECORE.h"
#include "Bullet.h"
#include <JTIME.h>
#include <Input.h>
//#include "Render.h"
#include "ImageRender.h"
#include "TransRender.h"
#include "AniRender.h"
#include "CirclCol.h"
#include "RectCol.h"
#include "Player.h"

#include "WormBomb.h"


Worm::Worm() :state(WORMSTATE::WORMIDLE), attRange( 150.0f), bulletTime (5.0f)
{
	type = WORM;
	hp = 15;
}


Worm::~Worm()
{
}


bool Worm::Init()
{


	aniRender = CreateRender<AniRender>(15);
	//particleRender = CreateRender<AniRender>();

	aniRender->SubPivotMode(PIVOT::CENTER);
	//particleRender->RenderPosMode(PIVOT::B);

	aniRender->CreateAnimation(L"Idle", L"Worm.bmp", 0, 0, false, 0.1f);
	aniRender->CreateAnimation(L"Grow", L"Worm.bmp", 1, 9, false, 0.1f);
	aniRender->CreateAnimation(L"Attack", L"Worm.bmp", 10, 21, true, 0.1f);
	//aniRender->CreateAnimation(L"Die", L"Worm.bmp", 22, 24, false, 0.1f);
	aniRender->CreateAnimation(L"Die", L"Explosion.bmp", 0, 19, false, 0.03f);

	//aniRender->CreateAnimation(L"Attack", L"Worm.bmp", 5, 12, true, 0.1f);
	//particleRender->CreateAnimation	(L"BombIdle", L"Bat.bmp", 12, 12, false, 0.1f); 
	//particleRender->CreateAnimation	(L"BombAttack", L"Bat.bmp", 12, 14, true, 0.1f);

	aniRender->PlayAnimation(L"Idle");
	//particleRender->PlayAnimation(L"BombIdle");
	//aniRender->DebugOff();
	//particleRender->DebugOff();

	//RectCol* circleCol = CreateCol<RectCol>(L"MONSTER", { 220, 220 });

	RectCol* rectCol = CreateCol<RectCol>(L"MONSTER", { 30, 90 });
	rectCol->SubPivotMode(PIVOT::B);

	return true;
}

void Worm::Update()
{
	OutScreenMonster();
	if (true != isEditor)
	{
		range = sqrt(
			(pow((pos.x - Player::Inst()->GetPos().x), 2)
				+ pow((pos.y - Player::Inst()->GetPos().y), 2))
		);

		if (hp <= 0)
		{
			state = WORMDIE;
			if (deadSound == false)
			{
				Sound::SoundPlay(L"E_Explosion3.wav");
				deadSound = true;
			}
		}


		switch (state)
		{
		case WORMSTATE::WORMIDLE:
			IDLE();
			break;
		case WORMSTATE::WORMGROW:
			GROWUP();
			break;
		case WORMSTATE::WORMATTACK:
			ATTACK();
			break;
		case WORMSTATE::WORMDIE:
			DIE();
			break;
		case WORMSTATE::WORMMAX:
			break;
		}

	}
}

void Worm::IDLE()
{
	if (range < attRange)
	{
		state = WORMSTATE::WORMGROW;
	}
}
void Worm::GROWUP()
{
	aniRender->PlayAnimation(L"Grow");

	if (aniRender->GetCurAni()->aniEnd == true)
	{
		state = WORMSTATE::WORMATTACK;
	}
}
void Worm::ATTACK()
{
	aniRender->PlayAnimation(L"Attack");

	bulletTime -= Time::DeltaTime();

	if (range < 300.0f)
	{
		if (bulletTime < 0.0f)
		{
			/*WormBomb* myBomb = CreateActor<WormBomb>();
			myBomb->SetPos({ pos.x, pos.y - 50.0f });
			if (Player::Inst()->GetPos().x < pos.x)
			{
				myBomb->SetDir(0);
			}
			else
			{
				myBomb->SetDir(1);
			}*/

			bulletTime = 5.0f;
		}
	}



}
void Worm::DIE()
{
	aniRender->PlayAnimation(L"Die");

	if (aniRender->GetCurAni()->aniEnd == true)
	{
		Die();
	}
}