#include "stdafx.h"
#include "SubBoss.h"
#include "AniRender.h"
#include "RectCol.h"
#include "Player.h"
#include <JTIME.h>
#include "Bat.h"
#include <Well512.h>
#include "SubBossBomb.h"
#include "Map.h"


SubBoss::SubBoss() : state(SUBSTART), moveTime(2.0f), isMove(false), batCnt(0), summonTime(0.2f), isBite(false), biteTime(0.8f)
{
	hp = 200;
	type = SUBBOSS;

	failedBite = false;
	attCnt = 0;

	isMoving = false;
}


SubBoss::~SubBoss()
{

}


bool SubBoss::Init()
{
	aniRender = CreateRender<AniRender>(15);
	aniRender->SubPivotMode(PIVOT::CENTER);
	backParticle = CreateRender<AniRender>(14);
	backParticle->SubPivotMode(PIVOT::CENTER);

	//PARTICLE
	backParticle->CreateAnimation(L"Orora", L"RSubBoss.bmp", 36, 39, true, 0.07f);
	backParticle->CreateAnimation(L"None", L"RSubBoss.bmp", 40, 40, false, 0.07f);

	//RIGHT
	
	
	aniRender->CreateAnimation(L"R_Idle", L"RSubBoss.bmp", 11, 16, true, 0.1f);
	aniRender->CreateAnimation(L"R_Idle2", L"RSubBoss.bmp", 17, 22, true, 0.1f);
	aniRender->CreateAnimation(L"R_BitePrev", L"LSubBoss.bmp", 23, 24, false, 0.1f);
	aniRender->CreateAnimation(L"R_Bite", L"LSubBoss.bmp", 25, 29, false, 0.1f);
	aniRender->CreateAnimation(L"R_Special", L"RSubBoss.bmp", 30, 34, false, 0.1f);

	aniRender->CreateAnimation(L"Die", L"Explosion.bmp", 0, 21, false, 0.03f);
	//LEFT
	aniRender->CreateAnimation(L"L_Start",	L"LSubBoss.bmp", 0, 0, false, 0.1f);
	aniRender->CreateAnimation(L"L_Turn",	L"LSubBoss.bmp", 1, 10, false, 0.1f);
	aniRender->CreateAnimation(L"L_Idle",	L"LSubBoss.bmp", 11, 16, true, 0.1f);
	aniRender->CreateAnimation(L"L_Idle2",	L"LSubBoss.bmp", 17, 22, true, 0.1f);
	aniRender->CreateAnimation(L"L_BitePrev", L"RSubBoss.bmp", 23, 24, false, 0.1f);
	aniRender->CreateAnimation(L"L_Bite",	L"RSubBoss.bmp", 25, 29, false, 0.1f);
	aniRender->CreateAnimation(L"L_Special",L"LSubBoss.bmp", 30, 34, false, 0.1f);

	aniRender->PlayAnimation(L"L_Start");
	backParticle->PlayAnimation(L"None");

	//RectCol* rectCol = CreateCol<RectCol>(L"SUBBOSS", { 50, 60 });
	//rectCol->SubPivotMode(PIVOT::B);


	RectCol* rectCol2 = CreateCol<RectCol>(L"MONSTER", { 50, 60 });
	rectCol2->SubPivotMode(PIVOT::B);
	

	return true;
}
void SubBoss::Update()
{

	if (hp < 0)
	{
		state = SUBDIE;
	}

	range = sqrt(
		(pow((pos.x - Player::Inst()->GetPos().x), 2)
			+ pow((pos.y - Player::Inst()->GetPos().y), 2))
	);


	if (Player::Inst()->GetPos().x < pos.x)
	{
		dir = LEFT;
	}
	else
	{
		dir = RIGHT;
	}

	//moveTime = 2.0f;
	switch (state)
	{
	case SUBSTART:
		Start();
		break;
	case SUBIDLE:
		Idle();
		break;
	case SUBMOVE:
		Move();
		break;
	case SUBATTACK1:
		Attack1();
		break;
	case SUBATTACK2:
		Attack2();
		break;
	case SUBATTACK3:
		Attack3();
		break;
	case SUBDIE:
		SubDie();
		break;
	}
}


///////////////////COLL

void SubBoss::ColEnter(Collision* _This, Collision* _Other)
{
	
}
void SubBoss::ColStay(Collision* _This, Collision* _Other)
{
	
}
void SubBoss::ColExit(Collision* _This, Collision* _Other)
{
	
}


/////////////////////////STATE
void SubBoss::ChangeState(SUBSTATE _State)
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

	changeAniName += SubAniName[_State];

	aniRender->PlayAnimation(changeAniName.c_str());

	state = _State;
}

void SubBoss::Start()
{
	

	if (Player::Inst()->GetPos().y > pos.y && range < 300.0f)
	{
		aniRender->PlayAnimation(L"L_Turn");

		pos.y += 80.0f * Time::DeltaTime();

		if (aniRender->GetCurAni()->aniEnd == true)
		{
		
			Sound::AllSoundPlayerStop();
			Sound::SoundPlay(L"CS02_CommandCenter.mp3", 100);

			
			ChangeState(SUBIDLE);
		}
	}


}
void SubBoss::Idle()
{
	moveTime -= Time::DeltaTime();

	if (attCnt == 0)
	{
		if (moveTime < 0.0f)
		{
			moveTime = 2.0f;

			if (dir == RIGHT)
			{
				movingDir = RIGHT;
			}
			else
			{
				movingDir = LEFT;
			}

			moveTime = 2.0f;
			ChangeState(SUBMOVE);

			return;
		}
	}
	
	if(attCnt == 2)
	{
		if (moveTime < 0.0f)
		{
			moveTime = 2.0f;

			ChangeState(SUBATTACK2);

			return;
		}
	}

	if (attCnt == 3)
	{
		if (moveTime < 0.0f)
		{
			moveTime = 2.0f;

			ChangeState(SUBATTACK3);

			return;
		}
	}

	

	ChangeState(SUBIDLE);
}
void SubBoss::Move()
{	
	moveTime -= Time::DeltaTime();
		//moveTime = 2.0f;



	if (moveTime > 0.0f)
	{
		if (movingDir == LEFT)
		{
			pos.x -= 200.0f * Time::DeltaTime();
		}

		if(movingDir == RIGHT)
		{
			pos.x += 200.0f * Time::DeltaTime();
		}

		
	}
	else
	{
		moveTime = 2.0f;
		ChangeState(SUBATTACK1);
		attCnt += 1;

		return;
	}
	
	
	
	ChangeState(SUBMOVE);
}
//void Move();
void SubBoss::Attack1()
{
	backParticle->PlayAnimation(L"Orora");
	
	   	  	
	if (batCnt < 7)
	{
		Well512Random::Init();
		float x = Well512Random::GetFloatValue(0, 30);
		float y = Well512Random::GetFloatValue(0, 50);

		if (batCnt % 2 == 0)
		{
			x = -x;
		}


		Pos randPos = { x + pos.x, -y + pos.y };
		Bat* newBat = Actor::CreateActor<Bat>();
		newBat->SetPos(randPos);

		++batCnt;
	}
	else
	{
		backParticle->PlayAnimation(L"None");
		ChangeState(SUBIDLE);
		biteTime = 0.8f;
		attCnt += 1;

		batCnt = 0;
		return;
	}
	
	
	


	ChangeState(SUBATTACK1);
}
void SubBoss::Attack2() 
{
	biteTime -= Time::DeltaTime();

	if (biteTime > 0.0f)
	{
		if (dir == LEFT)
		{
			pos.y += 200.0f * Time::DeltaTime();
			pos.x -= 200.0f * Time::DeltaTime();
		}
		else
		{
			//if(Player::Inst()->GetPos())

			pos.y += 200.0f * Time::DeltaTime();
			pos.x += 200.0f * Time::DeltaTime();
		}
	}
	else
	{
		if (biteTime > -0.8f)
		{
			if (dir == LEFT)
			{
				pos.y -= 200.0f * Time::DeltaTime();
				pos.x -= 200.0f * Time::DeltaTime();
			}
			else
			{
				//if(Player::Inst()->GetPos())

				pos.y -= 200.0f * Time::DeltaTime();
				pos.x += 200.0f * Time::DeltaTime();
			}
		}
		else
		{
			moveTime = 2.0f;
			attCnt += 1;
			ChangeState(SUBIDLE);
		}
	}


}
void SubBoss::Attack3()
{
	if (aniRender->GetCurAni()->aniEnd == true)
	{
		SubBossBomb* newBomb = CreateActor<SubBossBomb>(L"SubBomb", true);
		newBomb->SetPos({ pos.x - 40.0f, pos.y + -15.0f });
		newBomb->SetAngle(-0.8f);


		SubBossBomb* newBomb1 = CreateActor<SubBossBomb>(L"SubBomb", true);
		newBomb1->SetPos({ pos.x - 20.0f, pos.y + 0.0f });
		newBomb1->SetAngle(-0.4f);

		SubBossBomb* newBomb2 = CreateActor<SubBossBomb>(L"SubBomb", true);
		newBomb2->SetPos({ pos.x    , pos.y + 20.0f });

		SubBossBomb* newBomb3 = CreateActor<SubBossBomb>(L"SubBomb", true);
		newBomb3->SetPos({ pos.x + 20.0f , pos.y + 0.0f });
		newBomb3->SetAngle(0.4f);

		SubBossBomb* newBomb4 = CreateActor<SubBossBomb>(L"SubBomb", true);
		newBomb4->SetPos({ pos.x + 40.0f, pos.y + -15.0f });
		newBomb4->SetAngle(0.8f);

		attCnt = 0;
		moveTime = 2.0f;
		ChangeState(SUBIDLE);

		return;
	}



}
void SubBoss::SubDie()
{
	aniRender->PlayAnimation(L"Die");

	if (aniRender->GetCurAni()->aniEnd == true)
	{
		Die();
	}
}