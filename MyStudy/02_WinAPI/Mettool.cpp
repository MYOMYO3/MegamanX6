#include "stdafx.h"
#include "Mettool.h"
#include "AniRender.h"
#include "Player.h"
#include <math.h>
#include <JTIME.h>
#include "Map.h"
#include "TransRender.h"
#include "MettoolBomb.h"
#include "RectCol.h"
#include <Sound.h>

Mettool::Mettool() : state(METWAIT) , dir(0)
{
	type = METOOL;


	CHECKPOS[CHECKRIGHT] = { 20.0F,	-20.0F };
	CHECKPOS[CHECKLEFT] = { -20.0F, -20.0F };
	CHECKPOS[CHECKTOP] = { 0.0F,	-50.0F };
	CHECKPOS[CHECKBOTTOM] = { 0.0F,	  0.0F };
	CHECKPOS[CHECKUNDERGROUND] = { 0.0F,	 10.0F };


	//보이는거
	CHECKPOSSUB[CHECKRIGHT] = { 0.0F,	  0.0F };
	CHECKPOSSUB[CHECKLEFT] = { 0.0F,	  0.0F };
	CHECKPOSSUB[CHECKTOP] = { 0.0F,	  0.0F };
	CHECKPOSSUB[CHECKBOTTOM] = { 0.0F,	  0.0F };

	hp = 15;
}


Mettool::~Mettool()
{
}

bool Mettool::Init()
{
	map = Map::Inst();

	aniRender = CreateRender<AniRender>(15);
	
	aniRender->SubPivotMode(PIVOT::CENTER);
	//particleRender->RenderPosMode(PIVOT::B);
	

	///LEFT
	aniRender->CreateAnimation(L"L_Wait",  L"L_Mettool.bmp", 0, 1, true, 0.1f);
	aniRender->CreateAnimation(L"L_SitUp", L"L_Mettool.bmp", 2, 5, false, 0.1f);
	aniRender->CreateAnimation(L"L_Run", L"L_Mettool.bmp", 6, 13, true, 0.1f);
	aniRender->CreateAnimation(L"L_Jump", L"L_Mettool.bmp", 14, 20, false, 0.1f);
	//aniRender->CreateAnimation(L"L_Attack", L"L_Mettool.bmp", 21, 24, true, 0.1f);

	aniRender->CreateAnimation(L"Die", L"Explosion.bmp", 0, 19, false, 0.03f);
	
	///RIGHT
	aniRender->CreateAnimation(L"R_Wait", L"R_Mettool.bmp", 0, 1, true, 0.1f);
	aniRender->CreateAnimation(L"R_SitUp", L"R_Mettool.bmp", 2, 5, false, 0.1f);
	aniRender->CreateAnimation(L"R_Run", L"R_Mettool.bmp", 6, 13, true, 0.1f);
	aniRender->CreateAnimation(L"R_Jump", L"R_Mettool.bmp", 14, 20, false, 0.1f);
	//aniRender->CreateAnimation(L"R_Attack", L"R_Mettool.bmp", 21, 24, true, 0.1f);

	RectCol* rectCol = CreateCol<RectCol>(L"MONSTER", { 30, 50 });
	rectCol->SubPivotMode(PIVOT::B);

	aniRender->PlayAnimation(L"L_Wait");

	return true;
}

void Mettool::Update()
{
	OutScreenMonster();
	if (hp < 0)
	{
		state = METDIE;
		if (deadSound == false)
		{
			Sound::SoundPlay(L"E_Explosion3.wav");
			deadSound = true;
		}
	}

	distanceX = pos.x - Player::Inst()->GetPos().x;

	if (Player::Inst()->GetPos().x < pos.x)
	{
		dir = LEFT;
	}
	else
	{
		dir = RIGHT;
	}
	GroundCheck();

	switch (state)
	{
	case METWAIT:
		WAIT();
		break;

	case METIDLE:
		IDLE();
		break;

	case METMOVE:
		MOVE();
		break;

	case METATTACK:
		ATTACK();
		break;

	case METDIE:
		DIE();
		break;	
	}
}

bool Mettool::MonsterDeath()
{
	return true;
}


//////////////////////////////////

bool Mettool::IsColorCheck(CHECKDIR _eDir, int _Color)
{
#pragma region EXCEPT
	if (nullptr == map)
	{
		assert(false);
	}

	TransRender* render = map->GetPixelRender();

	if (nullptr == render)
	{
		assert(false);
	}

	Sprite* sprite = render->GetSprite();

	if (nullptr == sprite)
	{
		assert(false);
	}
#pragma endregion
	int checkColor = 0;

	CalDebugPos(pos);
	int CheckColor = sprite->PosToColor((GetCheckPos(_eDir) + CHECKPOSSUB[_eDir]) - map->GetPos());

	return _Color == CheckColor;
}

void Mettool::GroundCheck()
{
#pragma region EXCEPT
	if (nullptr == map)
	{
		assert(false);
	}

	TransRender* render = map->GetPixelRender();

	if (nullptr == render)
	{
		assert(false);
	}

	Sprite* sprite = render->GetSprite();

	if (nullptr == sprite)
	{
		assert(false);
	}
#pragma endregion
	int checkColor = 0; // 검정색

	/*char* p = (char*)&mouseColor;	//마우스 포지션 색체크
	mouseColor = sprite->PosToColor({ pos.x - 640.0f + GameCore::MainWindow().MousePos().x,
										pos.y - 400.0f + GameCore::MainWindow().MousePos().y });*/

	posColor = sprite->PosToColor(pos + Pos{ 0.0f, 1.0f } -map->GetPos());;
	//groundColor = sprite->PosToColor(pos + Pos{ 0.0f, 20.0f } -map->GetPos());;

	if (checkColor != posColor)
	{
		pos.y += 500.0f * Time::DeltaTime();
		
	}
	else
	{
		while (checkColor == sprite->PosToColor(pos - map->GetPos()))
		{
			CalDebugPos(pos);
			pos -= {0.0f, 1.0f};
		}		
	}
}

void Mettool::ChangeState(METSTATE _State)
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

	// 변신이 되어있다면
	// L_RIGHTANI

	changeAniName += AniName[_State];

	aniRender->PlayAnimation(changeAniName.c_str());

	state = _State;
}



void Mettool::WAIT()
{
	if (abs(distanceX) < 250.0f)
	{
		ChangeState(METSTATE::METIDLE);
		
		return;
	}


	ChangeState(METSTATE::METWAIT);
}

void Mettool::IDLE()
{
	if (aniRender->GetCurAni()->aniEnd == true)
	{
		ChangeState(METMOVE);
	}


	//ChangeState(METSTATE::METIDLE);
}

void Mettool::MOVE()
{
	if (false == IsColorCheck((Actor::CHECKDIR)dir, ColorRGB::Magenta)) //좌우방향 체크
	{
		return;
	}

	if (abs(distanceX) < 150.0f)
	{
		ChangeState(METATTACK);

		return;
	}

	if (dir == LEFT)
	{
		pos.x -= 100.0f * Time::DeltaTime();
	}
	else
	{
		pos.x += 100.0f * Time::DeltaTime();
	}

	ChangeState(METMOVE);
}

void Mettool::ATTACK()
{
	if (aniRender->GetCurAni()->aniEnd == true)
	{
		MettoolBomb* bomb = CreateActor< MettoolBomb>();
		bomb->SetDir(dir);
		if (dir == LEFT)
		{
			bomb->SetPos({pos.x -10.0f, pos.y - 10.0f});
		}
		else
		{
			bomb->SetPos({ pos.x + 10.0f, pos.y - 10.0f });
		}	
		
		ChangeState(METSTATE::METWAIT);
		return;

	}


	//aniRender->PlayAnimation(L"R_Attack");

	if (abs(distanceX) > 250.0f)
	{
		ChangeState(METSTATE::METWAIT);

		return;
	}

	ChangeState(METATTACK);

}

void Mettool::DIE()
{
	aniRender->PlayAnimation(L"Die");

	if (aniRender->GetCurAni()->aniEnd == true)
	{
		Die();
	}
}



