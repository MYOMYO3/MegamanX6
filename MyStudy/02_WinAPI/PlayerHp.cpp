#include "stdafx.h"
#include "PlayerHp.h"
#include "AniRender.h"

#include "Player.h"

PlayerHp::PlayerHp()
{
	//playerHP = Player::Inst()->GetHp();
}


PlayerHp::~PlayerHp()
{
}

bool PlayerHp::Init()
{
	render = CreateRender<AniRender>(100);
	render->SubPivotMode(PIVOT::CENTER);
	render->CameraEffectOFF();
	render->CreateAnimation(L"1", L"Hud.bmp", 0, 0, false, 0.1f);
	render->CreateAnimation(L"2", L"Hud.bmp", 1, 1, false, 0.1f);
	render->CreateAnimation(L"3", L"Hud.bmp", 2, 2, false, 0.1f);
	render->CreateAnimation(L"4", L"Hud.bmp", 3, 3, false, 0.1f);
	render->CreateAnimation(L"5", L"Hud.bmp", 4, 4, false, 0.1f);


	render->PlayAnimation(L"1");


	render->DebugOff();

	render->RenderSize({350.0f, 350.0f});
	return true;

}

void PlayerHp::Update()
{
	playerHP = Player::Inst()->GetHp();

	if (playerHP < 20)
	{
		render->PlayAnimation(L"5");

		return;
	}

	if (playerHP < 40)
	{
		render->PlayAnimation(L"4");

		return;
	}

	if (playerHP < 60)
	{
		render->PlayAnimation(L"3");

		return;
	}

	if (playerHP < 80)
	{
		render->PlayAnimation(L"2");

		return;
	}	
}
