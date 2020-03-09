#include "stdafx.h"
#include "Player.h"
#include "AniRender.h"
#include <JTIME.h>
#include <Input.h>

#include <Sound.h>




//���� üũ
void Player::CheckCharging()
{
	//if (true == Input::Down(L"FIRE"))
	//{
	//	chargeSound = Sound::SoundPlayNoneReturn();
	//	chargeSound->Play(L"Charging.wav", 10000);
	//	//Sound::SoundPlay(L"V_ready.wav");
	//	
	//	//Sound::SoundPlay(L"XE_Charging.wav", 10000);
	//}
	//if (true == Input::Up(L"FIRE"))
	//{
	//	if (nullptr != chargeSound)
	//	{
	//		chargeSound->Stop();
	//	}
	//}

	chargeTime -= Time::DeltaTime();

	if (true == Input::Press(L"FIRE"))
	{
		//Sound::SoundPlay(L"XE_Charging.wav");
		ChangeOption(CHARGE);
	}
	else
	{
		ChangeOption(NONE);
	}

	if (shootRender->GetCurAni()->aniEnd == true)
	{
		shootRender->PlayAnimation(L"NoneShoot");
	}
	if (dashRender->GetCurAni()->aniEnd == true)
	{
		dashRender->PlayAnimation(L"NoneDash");
	}
	if (afterImageRender->GetCurAni()->aniEnd == true)
	{
		afterImageRender->PlayAnimation(L"NoneImage");
	}
	if (dashBooster->GetCurAni()->aniEnd == true)
	{
		dashBooster->PlayAnimation(L"NoneDash");
	}
	if (jumpSpark->GetCurAni()->aniEnd == true)
	{
		jumpSpark->PlayAnimation(L"NoneSpark");
	}
}


void Player::CheckChargingRun()
{
	if (true == Input::Press(L"FIRE"))
	{
		if (ultimateArmor != true)
		{
			ChangeState(CHARGERUN); //����Ű�� �����ִٸ� ���� �޸���� ����
			ChangeOption(CHARGE);
		}
		else
		{
			ChangeULState(CHARGERUN);
			ChangeOption(CHARGE);
		}
		
	}
	else
	{
		ChangeOption(NONE);
	}

	if (shootRender->GetCurAni()->aniEnd == true)
	{
		shootRender->PlayAnimation(L"NoneShoot");
	}
	if (dashRender->GetCurAni()->aniEnd == true)
	{
		dashRender->PlayAnimation(L"NoneDash");
	}
	if (afterImageRender->GetCurAni()->aniEnd == true)
	{
		afterImageRender->PlayAnimation(L"NoneImage");
	}
	if (dashBooster->GetCurAni()->aniEnd == true)
	{
		dashBooster->PlayAnimation(L"NoneDash");
	}
	if (jumpSpark->GetCurAni()->aniEnd == true)
	{
		jumpSpark->PlayAnimation(L"NoneSpark");
	}
}

void Player::CheckChargingDash()
{
	if (true == Input::Press(L"FIRE"))
	{
		if (ultimateArmor != true)
		{
			ChangeState(CHARGEDASH); //����Ű�� ���� �ִٸ� ���� ��÷� ����
			ChangeOption(CHARGE);
		}
		else
		{
			ChangeULState(CHARGEDASH);
			ChangeOption(CHARGE);
		}
	}
	else
	{
		ChangeOption(NONE);
	}

	if (shootRender->GetCurAni()->aniEnd == true)
	{
		shootRender->PlayAnimation(L"NoneShoot");
	}
	if (dashRender->GetCurAni()->aniEnd == true)
	{
		dashRender->PlayAnimation(L"NoneDash");
	}
	if (afterImageRender->GetCurAni()->aniEnd == true)
	{
		afterImageRender->PlayAnimation(L"NoneImage");
	}
	if (dashBooster->GetCurAni()->aniEnd == true)
	{
		dashBooster->PlayAnimation(L"NoneDash");
	}
	if (jumpSpark->GetCurAni()->aniEnd == true)
	{
		jumpSpark->PlayAnimation(L"NoneSpark");
	}
}


