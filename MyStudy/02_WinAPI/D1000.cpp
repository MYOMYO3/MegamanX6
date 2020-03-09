#include "stdafx.h"
#include "D1000.h"
#include "AniRender.h"
#include "RectCol.h"
#include "Player.h"
#include "D1000Bomb.h"
#include <JTIME.h>

D1000::D1000() : state(D1000STATE::DIDLE)
{
	type = MONSTERTYPE::ED1000;
	hp = 50;

	defTime = 2.0f;
	attTime = 2.0f;

	isShoot = false;
	isParticle = false;
}


D1000::~D1000()
{
}


/////////////////////////
bool D1000::Init()
{

	aniRender = CreateRender<AniRender>(15);
	particleRender = CreateRender<AniRender>(14);

	aniRender->SubPivotMode(PIVOT::CENTER);
	particleRender->SubPivotMode(PIVOT::CENTER);

	aniRender->CreateAnimation(L"Idle", L"D1000.bmp",	18, 18,	 false, 0.1f);
	aniRender->CreateAnimation(L"Def", L"D1000.bmp",		19, 20,	 false, 0.1f);
	aniRender->CreateAnimation(L"Attack", L"D1000.bmp",	21, 24,  false, 0.1f);
	//aniRender->CreateAnimation(L"Die", L"Worm.bmp", 22, 24, false, 0.1f);
	aniRender->CreateAnimation(L"Attack2", L"D1000.bmp", 25, 28, false, 0.1f);
	
	aniRender->CreateAnimation(L"Die", L"Explosion.bmp", 0, 19,  false, 0.03f);

	//aniRender->CreateAnimation(L"Attack", L"Worm.bmp", 5, 12, true, 0.1f);
	//particleRender->CreateAnimation	(L"BombIdle", L"Bat.bmp", 12, 12, false, 0.1f); 
	particleRender->CreateAnimation	(L"AttackParticle", L"D1000.bmp", 0, 6, false, 0.1f);
	particleRender->CreateAnimation(L"None", L"D1000.bmp", 29, 29, true, 0.1f);

	aniRender->PlayAnimation(L"Idle");
	particleRender->PlayAnimation(L"None");
	//aniRender->DebugOff();
	//particleRender->DebugOff();

	//RectCol* circleCol = CreateCol<RectCol>(L"MONSTER", { 220, 220 });

	RectCol* rectCol = CreateCol<RectCol>(L"MONSTER", { 50, 90 });
	rectCol->SubPivotMode(PIVOT::B);

	return true;
}

void D1000::Update()
{
	OutScreenMonster();
	if (hp < 0)
	{
		if (deadSound == false)
		{
			Sound::SoundPlay(L"E_Explosion3.wav");
			deadSound = true;
		}
		state = D1000STATE::DDIE;
	}

	range = sqrt(
		(pow((pos.x - Player::Inst()->GetPos().x), 2)
			+ pow((pos.y - Player::Inst()->GetPos().y), 2))
	);

	switch (state)
	{
	case D1000STATE::DIDLE:
		IDLE();
		break;

	case D1000STATE::DDEF:
		if (Player::Inst()->GetPos().x < pos.x)
		{
			hp = 50;
			DEF();
		}
		break;

	case D1000STATE::DATTACK:
		ATTACK();
		break;

	case D1000STATE::DATTACK2:
		ATTACK2();
		break;

	case D1000STATE::DDIE:
		DIE();
		break;
	}
}
//////

void D1000::ColEnter(Collision* _This, Collision* _Other)
{
	state = D1000STATE::DDEF;

	//hp = 50;

}
void D1000::ColStay(Collision* _This, Collision* _Other)
{

}
void D1000::ColExit(Collision* _This, Collision* _Other)
{

}


/////////////////STATE
void D1000::IDLE()
{
	aniRender->PlayAnimation(L"Idle");

	attTime -= Time::DeltaTime();

	if (attTime < 0.0f)
	{
		if (range < 200.0f)
		{
			aniRender->PlayAnimation(L"Attack");
			attTime = 2.0f;
			state = D1000STATE::DATTACK;
			
		}
	}
}

void D1000::DEF()
{
	if (defTime < 0.0f)
	{
		state = D1000STATE::DIDLE;
		defTime = 2.0f;
	}

	aniRender->PlayAnimation(L"Def");

	defTime -= Time::DeltaTime();

}

void D1000::ATTACK()
{
		
	if (aniRender->GetCurAni()->aniEnd == true)
	{
		particleRender->PlayAnimation(L"AttackParticle");
		particleRender->RenderPos({ -183.0f, -148.0f });
		state = D1000STATE::DATTACK2;
	}
	//

}
void D1000::ATTACK2()
{
	if (particleRender->GetCurAni()->aniEnd == true)
	{
		particleRender->PlayAnimation(L"None");
		D1000Bomb* newBomb = Actor::CreateActor<D1000Bomb>(L"D1000Bomb");
		newBomb->SetPos({ pos.x - 50.0f, pos.y });
		state = D1000STATE::DIDLE;
	}

	

}

void D1000::DIE() 
{


	aniRender->PlayAnimation(L"Die");

	if (aniRender->GetCurAni()->aniEnd == true)
	{
		Die();
	}
}