#include "stdafx.h"
#include "Monster.h"
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

Monster::Monster() : isEditor(false) ,deadSound(false)
{
}


Monster::~Monster()
{
}

bool Monster::MonsterDeath()
{
	return true;
}


void Monster::OutScreenMonster()
{
	if (SceneMgr::Inst().GetCurScene()->cameraPos.x - 300.0f > pos.x)
	{
		Die();
	}

	/*if (6700.0f > pos.x)
	{
		Die();
	}*/
}


//bool Monster::Init()
//{
//	aniRender = CreateRender<AniRender>();
//	//particleRender = CreateRender<AniRender>();
//
//	aniRender->RenderPosMode(PIVOT::CENTER);
//	//particleRender->RenderPosMode(PIVOT::B);
//
//	aniRender->CreateAnimation		(L"Idle",		L"Bat.bmp", 0, 3,	true, 0.1f);
//	aniRender->CreateAnimation		(L"Attack",		L"Bat.bmp", 5, 12,	true, 0.1f);	
//	//particleRender->CreateAnimation	(L"BombIdle", L"Bat.bmp", 12, 12, false, 0.1f); 
//	//particleRender->CreateAnimation	(L"BombAttack", L"Bat.bmp", 12, 14, true, 0.1f);
//
//	aniRender->PlayAnimation(L"Idle");
//	//particleRender->PlayAnimation(L"BombIdle");
//	aniRender->DebugOff();
//	//particleRender->DebugOff();
//
//	//RectCol* circleCol = CreateCol<RectCol>(L"MONSTER", { 220, 220 });
//
//	return true;
//}
//
//void Monster::Update()
//{
//
//
//}


