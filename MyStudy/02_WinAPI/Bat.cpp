#include "stdafx.h"
#include "Bat.h"
#include <window.h>
#include <JTIME.h>
#include "GAMECORE.h"
#include <JTIME.h>
#include <Input.h>
//#include "Render.h"
#include "ImageRender.h"
#include "TransRender.h"
#include "AniRender.h"
#include "CirclCol.h"
#include "RectCol.h"
#include "Player.h"
#include <math.h>

#include "BatBomb.h"
#include "Actor.h"


#define m_PI 3.1415926535

Bat::Bat() : state(BATSTATE::BATIDLE), range(0.0f), attRange(600.0f), cycle(0.0f), bombCycle(0.0f), deathTime(600.0f), dir(0)
{
	type = BAT;
	hp = 15;

	
	attCnt = 0;

	dieCnt = 0;
}


Bat::~Bat()
{
}


bool Bat::Init()
{
	aniRender = CreateRender<AniRender>(15);
	//particleRender = CreateRender<AniRender>();

	aniRender->SubPivotMode(PIVOT::CENTER);
	//particleRender->RenderPosMode(PIVOT::B);

	aniRender->CreateAnimation(L"L_Idle", L"Bat.bmp", 0, 3, true, 0.1f);
	aniRender->CreateAnimation(L"L_Attack", L"Bat.bmp", 4, 11, true, 0.1f);

	aniRender->CreateAnimation(L"R_Idle", L"RBat.bmp", 0, 3, true, 0.1f);
	aniRender->CreateAnimation(L"R_Attack", L"RBat.bmp", 4, 11, true, 0.1f);

	aniRender->CreateAnimation(L"Die", L"Explosion.bmp", 0, 21, false, 0.03f);
	//particleRender->CreateAnimation	(L"BombIdle", L"Bat.bmp", 12, 12, false, 0.1f); 
	//particleRender->CreateAnimation	(L"BombAttack", L"Bat.bmp", 12, 14, true, 0.1f);


	//particleRender->PlayAnimation(L"BombIdle");
	//aniRender->DebugOff();
	//particleRender->DebugOff();

	RectCol* rectCol = CreateCol<RectCol>(L"MONSTER", { 30, 50 });
	rectCol->SubPivotMode(PIVOT::B);

	
	aniRender->PlayAnimation(L"L_Idle");

	myBomb = Actor::CreateActor<BatBomb>();

	return true;
}

void Bat::Update()
{
	OutScreenMonster();
	deathTime -= Time::DeltaTime();

	if (deathTime < 0.0f)
	{
		//myBomb->SetState(4);

		Die();
	}

	if (hp <= 0)
	{
		state = BATDIE;
		if (deadSound == false)
		{
			Sound::SoundPlay(L"E_Explosion3.wav");
			deadSound = true;
		}
		if (dieCnt == 0)
		{
			myBomb->Die();
			++dieCnt;
		}
	}

	//myBomb->SetHP(hp);

	if (true != isEditor)
	{
		range = sqrt(
			(pow((pos.x - Player::Inst()->GetPos().x), 2)
				+ pow((pos.y - Player::Inst()->GetPos().y), 2))
		);



		switch (state)
		{
		case BATSTATE::BATIDLE:
			IDLE();
			break;
		case BATSTATE::BATMOVE:
			MOVE();
			break;
		case BATSTATE::BATATTACK:
			ATTACK();
			break;
		case BATSTATE::BATDIE:
			DIE();
			break;
		case BATSTATE::BOSSATT:
			BOSSATT();
			break;
		}
	}
}

bool Bat::MonsterDeath()
{
	return true;
}

/////////////////////////STATE FUNC
void Bat::IDLE()
{
	if (Player::Inst()->GetPos().x < pos.x)
	{
		dir = LEFT;
	}
	else
	{
		dir = RIGHT;
	}

	if (dir == LEFT)
	{
		if (range < attRange)
		{
			state = BATSTATE::BATMOVE;
			aniRender->PlayAnimation(L"L_Idle");
		}
		myBomb->SetPos({ pos.x - 3.0f , pos.y + 20.0f });
	}
	else
	{
		if (range < attRange)
		{
			state = BATSTATE::BATMOVE;
			aniRender->PlayAnimation(L"R_Idle");
		}
		myBomb->SetPos({ pos.x + 13.0f , pos.y + 20.0f });
	}
}

void Bat::MOVE()
{
	if (dir == LEFT)
	{
		if (Player::Inst()->GetPos().x >= pos.x)
		{
			state = BATSTATE::BATATTACK;
		}
		myBomb->SetPos({ pos.x - 3.0f , pos.y + 20.0f });

		cycle += 0.02f;
		pos.y += (sinf(cycle * m_PI) * 40.0f)  * Time::DeltaTime();
		pos.x -= 100.0f *Time::DeltaTime();
	}
	else
	{
		if (Player::Inst()->GetPos().x <= pos.x)
		{
			state = BATSTATE::BATATTACK;
		}
		myBomb->SetPos({ pos.x - 3.0f , pos.y + 20.0f });

		cycle += 0.02f;
		pos.y += (sinf(cycle * m_PI) * 40.0f)  * Time::DeltaTime();
		pos.x += 100.0f *Time::DeltaTime();
	}

	

	
}

void Bat::ATTACK()
{
	if (dir == LEFT)
	{
		aniRender->PlayAnimation(L"L_Attack");
		
		if (attCnt == 0)
		{
			myBomb->Die();
			++dieCnt;
			BatBomb* realBomb = Actor::CreateActor<BatBomb>();
			realBomb->SetPos({ pos.x - 3.0f , pos.y + 20.0f });
			realBomb->SetState(1);
			attCnt += 10;
		}
		cycle += 0.02f;
		pos.y += (sinf(cycle * m_PI) * 40.0f)  * Time::DeltaTime();
		pos.x -= 100.0f *Time::DeltaTime();

		
	}
	else
	{
		aniRender->PlayAnimation(L"R_Attack");
		//myBomb->SetState(1);
		if (attCnt == 0)
		{
			myBomb->Die();
			++dieCnt;
			BatBomb* realBomb = Actor::CreateActor<BatBomb>();
			realBomb->SetPos({ pos.x - 3.0f , pos.y + 20.0f });
			realBomb->SetState(1);
			attCnt += 10;
		}
		cycle += 0.02f;
		pos.y += (sinf(cycle * m_PI) * 40.0f)  * Time::DeltaTime();
		pos.x += 100.0f *Time::DeltaTime();

		
	}
	
}

void Bat::DIE()
{
	aniRender->PlayAnimation(L"Die");
	
	

	if (aniRender->GetCurAni()->aniEnd == true)
	{
		
		Die();
	}
}

void Bat::BOSSATT()
{

}