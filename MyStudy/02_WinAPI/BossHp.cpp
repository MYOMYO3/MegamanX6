#include "stdafx.h"
#include "BossHp.h"
#include "AniRender.h"
#include "Boss.h"

BossHp* BossHp::m_inst = nullptr;

BossHp::BossHp()
{
}


BossHp::~BossHp()
{
}

bool BossHp::Init()
{
	render = CreateRender<AniRender>(100);
	render->SubPivotMode(PIVOT::CENTER);
	render->CameraEffectOFF();
	render->CreateAnimation(L"1", L"Hud.bmp", 5, 5, false, 0.1f);
	render->CreateAnimation(L"2", L"Hud.bmp", 6, 6, false, 0.1f);
	render->CreateAnimation(L"3", L"Hud.bmp", 7, 7, false, 0.1f);
	render->CreateAnimation(L"4", L"Hud.bmp", 8, 8, false, 0.1f);
	render->CreateAnimation(L"5", L"Hud.bmp", 9, 9, false, 0.1f);


	render->PlayAnimation(L"1");


	render->DebugOff();

	render->RenderSize({ 350.0f, 350.0f });
	return true;

}

void BossHp::Update()
{
	bossHP = Boss::boss->GetHp();

	if (bossHP < 50)
	{
		render->PlayAnimation(L"5");

		return;
	}

	if (bossHP < 100)
	{
		render->PlayAnimation(L"4");

		return;
	}

	if (bossHP < 200)
	{
		render->PlayAnimation(L"3");

		return;
	}

	if (bossHP < 300)
	{
		render->PlayAnimation(L"2");

		return;
	}
}