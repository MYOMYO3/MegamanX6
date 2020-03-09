#include "stdafx.h"
#include "Boss.h"
#include <window.h>
#include <JTIME.h>
#include "GAMECORE.h"
#include <JTIME.h>
#include <Input.h>
//#include "Render.h"
#include "TransRender.h"
#include "AniRender.h"

#include "CirclCol.h"
#include "RectCol.h"
#include "Player.h"
#include <math.h>

#include "Attack1.h"
#include "Attack4Bomb.h"
#include "Attack3Bomb.h"
#include "Attack2Bomb.h"


#include "FadeInOut.h"

Boss* Boss::boss = nullptr;

Boss::Boss() :state(BOSSSTATE::BOSSSTART), startTime(1.5f), dir(0)
{
	type = BOSS;

	range = 250.0f;

	attack4Time = 1.2f;
	
	isAttack4Bomb1 = false;
	isAttack4Bomb2 = false;
	isAttack4Bomb3 = false;
	isAttack4Bomb4 = false;
	stateAttack4Bomb = 1;


	playerDisX = 0.0f;
	playerDisY = 0.0f;

	moveCnt = 1;
	attack3Time = 0.5f;
	attack3Cnt = 0;

	attack3PosArr[0] = 10.0f;
	attack3PosArr[1] = 28.0f;

	hp = 400;

	idleTime = 2.0f;
	isMove = false;
}


Boss::~Boss()
{
}

bool Boss::Init()
{
	aniRender = CreateRender<AniRender>(15);
	aniRender->SubPivotMode(PIVOT::CENTER);
	///aniRender->BossDashOn();

	////////////////////////R_IMAGE
	aniRender->CreateAnimation(L"R_Start", L"Boss.bmp", 0, 14, false, 0.1f);
	
								 
	aniRender->CreateAnimation(L"R_Attack1", L"Boss.bmp", 21, 33, false, 0.08f);
	aniRender->CreateAnimation(L"R_Attack1Bomb", L"Boss.bmp", 34, 37, true, 0.1f);
								 
	aniRender->CreateAnimation(L"R_Attack2", L"Boss.bmp", 38, 43, false, 0.08f);
	aniRender->CreateAnimation(L"R_Attack2Bomb", L"Boss.bmp", 44, 44, true, 0.1f);
								 
	aniRender->CreateAnimation(L"R_Attack3", L"Boss.bmp", 45, 49, true, 0.08f);
	aniRender->CreateAnimation(L"R_Attack3Circle", L"Boss.bmp", 50, 52, true, 0.1f);
	aniRender->CreateAnimation(L"R_Attack3Particle", L"Boss.bmp", 53, 57, true, 0.1f);
	aniRender->CreateAnimation(L"R_Attack3Bomb", L"Boss.bmp", 58, 61, true, 0.1f);
								 
	aniRender->CreateAnimation(L"R_Attack4", L"Boss.bmp", 62, 77, false, 0.08f);
	aniRender->CreateAnimation(L"R_Attack4End", L"Boss.bmp", 69, 69, false, 0.08f);
	aniRender->CreateAnimation(L"R_Attack4Bomb", L"Boss.bmp", 78, 81, true, 0.1f);
	aniRender->CreateAnimation(L"R_Attack4Particle", L"Boss.bmp", 82, 86, true, 0.1f);
								 
	aniRender->CreateAnimation(L"R_Dash", L"Boss.bmp", 87, 93, false, 0.08f);
	aniRender->CreateAnimation(L"R_DashBooster", L"Boss.bmp", 94, 99, true, 0.1f);
								 
	aniRender->CreateAnimation(L"R_Idle", L"Boss.bmp", 100, 103, true, 0.08f);
	aniRender->CreateAnimation(L"R_Orora", L"Boss.bmp", 104, 107, true, 0.08f);
								 
	aniRender->CreateAnimation(L"R_Die", L"Boss.bmp", 109, 110, true, 0.1f);

	////////////////////////L_IMAGE
	aniRender->CreateAnimation(L"L_Start", L"LBoss.bmp", 0, 14, false, 0.1f);

	aniRender->CreateAnimation(L"L_Attack1", L"LBoss.bmp", 21, 33, false, 0.08f);
	aniRender->CreateAnimation(L"L_Attack1Bomb", L"LBoss.bmp", 34, 37, true, 0.1f);

	aniRender->CreateAnimation(L"L_Attack2", L"LBoss.bmp", 38, 43, false, 0.08f);
	aniRender->CreateAnimation(L"L_Attack2Bomb", L"LBoss.bmp", 44, 44, true, 0.1f);

	aniRender->CreateAnimation(L"L_Attack3", L"LBoss.bmp", 45, 49, true, 0.08f);
	aniRender->CreateAnimation(L"L_Attack3Circle", L"LBoss.bmp", 50, 52, true, 0.1f);
	aniRender->CreateAnimation(L"L_Attack3Particle", L"LBoss.bmp", 53, 57, true, 0.1f);
	aniRender->CreateAnimation(L"L_Attack3Bomb", L"LBoss.bmp", 58, 61, true, 0.1f);

	aniRender->CreateAnimation(L"L_Attack4", L"LBoss.bmp", 62, 77, false, 0.08f);
	aniRender->CreateAnimation(L"L_Attack4End", L"LBoss.bmp", 69, 69, false, 0.08f);
	aniRender->CreateAnimation(L"L_Attack4Bomb", L"LBoss.bmp", 78, 81, true, 0.1f);
	aniRender->CreateAnimation(L"L_Attack4Particle", L"LBoss.bmp", 82, 86, true, 0.1f);

	aniRender->CreateAnimation(L"L_Dash", L"LBoss.bmp", 87, 93, false, 0.08f);
	aniRender->CreateAnimation(L"L_DashBooster", L"LBoss.bmp", 94, 99, true, 0.1f);

	aniRender->CreateAnimation(L"L_Idle", L"LBoss.bmp", 100, 103, true, 0.08f);
	aniRender->CreateAnimation(L"L_Orora", L"LBoss.bmp", 104, 107, true, 0.08f);

	aniRender->CreateAnimation(L"L_Die", L"LBoss.bmp", 109, 110, true, 0.1f);

	//////////////////////////////



	////////////////////////

	aniRender->PlayAnimation(L"L_Start");

	backParticle = CreateRender<AniRender>(14);
	backParticle->SubPivotMode(PIVOT::CENTER);
	//backParticle->RenderPos({pos.x -3.0f, pos.y});
	backParticle->CreateAnimation(L"L_Orora", L"LBoss.bmp", 104, 107, true, 0.1f);
	backParticle->CreateAnimation(L"R_Orora", L"Boss.bmp", 104, 107, true, 0.1f);
	backParticle->CreateAnimation(L"None", L"LBoss.bmp", 111, 111, false, 0.1f);
	
	backParticle->PlayAnimation(L"None");

	RectCol* rectCol = CreateCol<RectCol>(L"MONSTER", { 50, 50 });
	rectCol->SubPivotMode(PIVOT::B);

	return true;
}

void Boss::Update()
{
	//playerDis = sqrt(
	//	(pow((pos.x - Player::Inst()->GetPos().x), 2)
	//		+ pow((pos.y - Player::Inst()->GetPos().y), 2))
	//);

	playerDisX = abs(Player::Inst()->GetPos().x - pos.x);
	playerDisY = abs(Player::Inst()->GetPos().y - pos.y);

	if (Player::Inst()->GetPos().x < pos.x)
	{
		dir = 0;
	}
	else
	{
		dir = 1;
	}

	if (hp < 0)
	{
		state = BOSSDIE;
	}

	switch (state)
	{
	case BOSSSTART:
		Start();
		break;
	case BOSSIDLE:
		Idle();
		break;
	case BOSSMOVE:
		Move();
		break;
	case BOSSATTACK1:
		Attack1();
		break;
	case BOSSATTACK2:
		Attack2();
		break;
	case BOSSATTACK3:
		Attack3();
		break;
	case BOSSATTACK4:
		Attack4();
		break;
	case BOSSDIE:
		BossDie();
		break;
	case BOSSMAX:
		break;	
	}
}

void Boss::ChangeState(BOSSSTATE	_State)
{
	std::wstring changeAniName = L"";

	switch (dir)
	{
	case LEFT:
		changeAniName += L"L_";
		break;
	case RIGHT:
		changeAniName += L"R_";
		break;
	default:
		break;
	}

	changeAniName += BossAniName[_State];

	aniRender->PlayAnimation(changeAniName.c_str());

	state = _State;
}


void Boss::Start()
{
	startTime -= Time::DeltaTime();

	if (dir == 0)
	{
		backParticle->PlayAnimation(L"L_Orora");
	}
	else
	{
		backParticle->PlayAnimation(L"R_Orora");
	}

	if (startTime < 0.0f)
	{

		idleTime = 2.0f;
		ChangeState(BOSSSTATE::BOSSIDLE);
	}
}

void Boss::Idle()
{
	idleTime -= Time::DeltaTime();

	if (idleTime > 0.0f)
	{
		return;
	}

	if (dir == 0)
	{
		backParticle->PlayAnimation(L"L_Orora");
	}
	else
	{
		backParticle->PlayAnimation(L"R_Orora");
	}

	if (moveCnt % 4 == 0) //attack4
	{
		ChangeState(BOSSATTACK3);

		return;
	}
	
	if (playerDisX > 100.0f) // move
	{
		//pos.x = Player::Inst()->GetPos().x;
		pos.x = Player::Inst()->GetPos().x;
		aniRender->BossDashOn();
		ChangeState(BOSSMOVE);

		backParticle->PlayAnimation(L"None");
		if (isMove == false)
		{
			Sound::SoundPlay(L"ZE_Dash.wav");
			isMove = true;
		}
		return;
	}



	if (playerDisY > 100.0f) //attack4
	{
		ChangeState(BOSSATTACK2);

		return;
	}
	



	if (playerDisX < 80.0f) //attack4
	{
		ChangeState(BOSSATTACK4);
		isAttack4Bomb1 = false;
		isAttack4Bomb2 = false;
		isAttack4Bomb3 = false;
		isAttack4Bomb4 = false;

		return;
	}






	ChangeState(BOSSIDLE);
}

void Boss::Move()
{
	isMove = false;
	
	

	aniRender->BossCloneDis -= (int)(7.0f * Time::DeltaTime());

	if (aniRender->GetCurAni()->aniEnd == true) // attafck1
	{
		++moveCnt;
		aniRender->BossCloneDis = 50;
		Sound::SoundPlay(L"ZE_Saber.wav");
		ChangeState(BOSSATTACK1);
		aniRender->BossDashOff();
	}
}

//void Move();
void Boss::Attack1()
{


	if (aniRender->GetCurAni()->aniEnd == true)
	{

		
		Attack1Bomb* Attack01Bomb = CreateActor<Attack1Bomb>();
		Attack01Bomb->SetDir(dir);
		//Attack01Bomb->SetPos(pos);

		if (0 == dir)
		{
			Attack01Bomb->SetPos({-40.0f + pos.x, 0.0f + pos.y});
		}
		else if (1 == dir)
		{
			Attack01Bomb->SetPos({ 40.0f + pos.x, 0.0f+ pos.y });
		}


		ChangeState(BOSSIDLE);
	}

	


	



	//WormBomb* myBomb = CreateActor<WormBomb>();




}

void Boss::Attack2()
{
	if (aniRender->GetCurAni()->aniEnd == true)
	{
		Attack2Bomb* Attack02Bomb = CreateActor<Attack2Bomb>();
		Attack02Bomb->SetDir(dir);
		//Attack01Bomb->SetPos(pos);

		if (0 == dir)
		{
			Attack02Bomb->SetPos({ -40.0f + pos.x, 0.0f + pos.y - 50.0f});
		}
		else if (1 == dir)
		{
			Attack02Bomb->SetPos({ 40.0f + pos.x, 0.0f + pos.y - 50.0f });
		}


		ChangeState(BOSSIDLE);
		idleTime = 2.0f;
	}
}

void Boss::Attack3()
{
	attack3Time -= Time::DeltaTime();

	if (attack3Time < 0.0f)
	{
		Sound::SoundPlay(L"XE_Buster0.wav");
		Attack3Bomb* Attack03Bomb = CreateActor<Attack3Bomb>();
		Attack03Bomb->SetDir(dir);
		++attack3Cnt;




		if (0 == dir)
		{
			Attack03Bomb->SetPos({ -40.0f + pos.x, 0.0f + pos.y - attack3PosArr[attack3Cnt % 2] });
		}
		else if (1 == dir)
		{
			Attack03Bomb->SetPos({ 40.0f + pos.x, 0.0f + pos.y  - attack3PosArr[attack3Cnt % 2] });
		}

		attack3Time = 0.5f;
	}



	if (attack3Cnt == 5)
	{
		attack3Cnt = 0;
		pos.x = Player::Inst()->GetPos().x;
		aniRender->BossDashOn();
		ChangeState(BOSSMOVE);
		Sound::SoundPlay(L"ZE_Dash.wav");

		backParticle->PlayAnimation(L"None");
	}
	
	

}

void Boss::Attack4()
{

	int a = 0;

	if (aniRender->GetCurAni()->aniEnd == false)
	{
		return;
	}

	aniRender->PlayAnimation(L"L_Attack4End");

	attack4Time -= Time::DeltaTime();


	


	if (0.9f < attack4Time)
	{

		if (isAttack4Bomb1 == false)
		{
			Sound::SoundPlay(L"XE_Buster1.wav");
			Attack4Bomb* RAttack04Bomb1 = CreateActor<Attack4Bomb>();
			RAttack04Bomb1->SetPos({ pos.x + 80.0f, pos.y });
			Attack4Bomb* lAttack04Bomb1 = CreateActor<Attack4Bomb>();
			lAttack04Bomb1->SetPos({ pos.x - 80.0f, pos.y });

			isAttack4Bomb1 = true;
			
		}
		//if (attack4Particle->GetCurAni()->aniEnd == true)
		//{
		//	attack4Particle->PlayAnimation(L"None");
		//}

	}
	else if (0.6f < attack4Time)
	{
		//isAttack4Bomb = false;

		if (isAttack4Bomb2 == false)
		{
			Sound::SoundPlay(L"XE_Buster1.wav");
			Attack4Bomb* rAttack04Bomb2 = CreateActor<Attack4Bomb>();
			rAttack04Bomb2->SetPos({ pos.x + 160.0f, pos.y });
			Attack4Bomb* lAttack04Bomb2 = CreateActor<Attack4Bomb>();
			lAttack04Bomb2->SetPos({ pos.x - 160.0f, pos.y });

			isAttack4Bomb2 = true;
			
		}
		//if (attack4Particle->GetCurAni()->aniEnd == true)
		//{
		//	attack4Particle->PlayAnimation(L"None");
		//}

	}
	else if (0.3f < attack4Time)
	{
		//isAttack4Bomb = false;

		if (isAttack4Bomb3 == false)
		{
			Sound::SoundPlay(L"XE_Buster1.wav");
			Attack4Bomb* rAttack04Bomb3 = CreateActor<Attack4Bomb>();
			rAttack04Bomb3->SetPos({ pos.x + 240.0f, pos.y });
			Attack4Bomb* lAttack04Bomb3 = CreateActor<Attack4Bomb>();
			lAttack04Bomb3->SetPos({ pos.x - 240.0f, pos.y });

			isAttack4Bomb3 = true;
		
		}
		//if (attack4Particle->GetCurAni()->aniEnd == true)
		//{
		//	attack4Particle->PlayAnimation(L"None");
		//}

	}
	else if (0.0f < attack4Time)
	{
		//isAttack4Bomb = false;
		if (isAttack4Bomb4 == false)
		{
			Sound::SoundPlay(L"XE_Buster1.wav");
			Attack4Bomb* rAttack04Bomb3 = CreateActor<Attack4Bomb>();
			rAttack04Bomb3->SetPos({ pos.x + 320.0f, pos.y });
			Attack4Bomb* lAttack04Bomb3 = CreateActor<Attack4Bomb>();
			lAttack04Bomb3->SetPos({ pos.x - 320.0f, pos.y });

			attack4Time = 1.2f;
			isAttack4Bomb4 = true;
		
			ChangeState(BOSSIDLE);	
			idleTime = 2.0f;
		}
		//if (attack4Particle->GetCurAni()->aniEnd == true)
		//{
		//	attack4Particle->PlayAnimation(L"None");
		//}


	}

}




void Boss::BossDie()
{
	//Die();
	FadeInOut* fade = CreateActor<FadeInOut>();
	
	


	
}

////////////////////////////////////////////////////////////////////////

void Boss::ColEnter(Collision* _This, Collision* _Other)
{

}

void Boss::ColStay(Collision* _This, Collision* _Other)
{

}

void Boss::ColExit(Collision* _This, Collision* _Other)
{

}
