#include "stdafx.h"
#include "Player.h"
#include "AniRender.h"
#include <JTIME.h>
#include <Input.h>
#include "Map.h"

#include "Sprite.h"
#include "TransRender.h"
#include "PlayerLittleBullet.h"
#include "PlayerBigBullet.h"

#include <Sound.h>

//Bullet* bullet = nullptr;

void Player::Star() // 스타트 상태
{
	//Sound::SoundPlay(L"V_ready.wav");

	if (soundCnt == 0)
	{
		Sound::SoundPlay(L"V_ready.wav");
		soundCnt++;
	}

	startTime -= Time::DeltaTime();

	if (startTime < 0.0f)
	{
		aniRender->PlayAnimation(L"R_StartEnd");
		endTime -= Time::DeltaTime();
		if (endTime < 0.0f)
		{
			ChangeState(IDLE);
			startTime = 3.0f;
			endTime = 1.0f;
		}
	}

	SceneMgr::Inst().GetCurScene()->cameraPos = (pos - Pos(645 * 0.5f, 480 * 0.75f));

}

#pragma region BASIC STATE
void Player::Idle()
{
	if (true == Input::Press(L"LEFT") || true == Input::Press(L"RIGHT"))
	{
		ChangeState(RUN);
	}

	if (true == Input::Down(L"DASH"))
	{
		isDash = true;
		ChangeDashParticle(L"Dash");
		ChangeState(DASH);

		RenderAfterImage(L"ULDash");
		//afterImageRender->PlayAnimation(L"R_ULDash");
	}

	if (isLanding == false)
	{
		if (isJumpKeyPress == false)
		{
			if (true == Input::Press(L"JUMP"))
			{
				isJumpKeyPress = true;
				isJump = true;
				isGround = false;
				ChangeState(JUMPING);

				isBgImageY = true;
			}
		}
	}



	if (true == Input::Up(L"FIRE"))
	{
		if (chargeTime < 0.0f)
		{
			ChangeState(BIGSHOOT);
		}
		else
		{
			ChangeState(LITTLESHOOT);
		}
	}

	//////////////////////////////////////
	CheckCharging();
}

void Player::Run()
{

	if (false == IsGroundColorCheck())
	{
		isGround = false;
		ChangeState(LANDING);
	}

	MoveCheck(speed);


	if (true == Input::Up(L"LEFT") || true == Input::Up(L"RIGHT"))
	{
		ChangeState(IDLE);
	}

	if (true == Input::Down(L"DASH"))
	{
		isDash = true;
		ChangeDashParticle(L"Dash");
		ChangeState(DASH);
		RenderAfterImage(L"ULDash");
		//afterImageRender->PlayAnimation(L"R_ULDash");
	}

	if (isJumpKeyPress == false)
	{
		if (true == Input::Press(L"JUMP"))
		{
			isJumpKeyPress = true;
			isJump = true;
			ChangeState(JUMPING);

			isBgImageY = true;
		}
	}



	if (true == Input::Up(L"FIRE"))
	{
		if (chargeTime < 0.0f)
		{
			ChangeState(BIGSHOOT);
		}
		else
		{
			ChangeState(LITTLESHOOT);
		}
	}
	//////////////////////////////////////
	CheckChargingRun();
}

void Player::Dash()
{

	MoveCheck(speed);


	if (isDash == true)
	{

		DashMoveCheck(300.0f);


	}

	if (isJumpKeyPress == false)
	{
		if (true == Input::Press(L"JUMP"))
		{
			isJumpKeyPress = true;
			isJump = true;
			//		jumpMax = pos.y - jumpPower;
			ChangeState(JUMPING);
			RenderAfterImage(L"ULJump");

			isBgImageY = true;
			//afterImageRender->PlayAnimation(L"R_ULJump");
		}
	}


	if (true == Input::Up(L"DASH"))
	{
		dashTime = 0.54f;
		isDash = false;
		ChangeState(IDLE);
	}
	else if (dashTime < 0.0f)
	{

		dashTime = 0.54f;
		//isDash		= false;
		ChangeState(IDLE);
	}

	if (true == Input::Up(L"FIRE"))
	{
		if (chargeTime < 0.0f)
		{
			ChangeState(BIGSHOOT);
		}
		else
		{
			ChangeState(LITTLESHOOT);
		}
	}
	//////////////////////////////////////
	CheckChargingDash();

	dashTime -= Time::DeltaTime();
}
#pragma endregion

#pragma region CHARGE STATE

void Player::ChargeRun()
{
	MoveCheck(speed);

	if (true == Input::Up(L"LEFT") || true == Input::Up(L"RIGHT"))
	{
		ChangeState(IDLE);
	}

	if (true == Input::Down(L"DASH"))
	{
		isDash = true;
		ChangeState(DASH);
		ChangeDashParticle(L"Dash");
		RenderAfterImage(L"ULDash");
	}
	///점프
	if (isJumpKeyPress == false)
	{
		if (true == Input::Press(L"JUMP"))
		{
			isJumpKeyPress = true;
			isJump = true;
			////		jumpMax = pos.y - jumpPower;
			ChangeState(JUMPING);
			RenderAfterImage(L"ULJump");

			isBgImageY = true;
		}
	}




	if (true == Input::Up(L"FIRE"))
	{
		if (chargeTime < 0.0f)
		{
			ChangeState(BIGSHOOT);
		}
		else
		{
			ChangeState(LITTLESHOOT);
		}
	}
	//////////////////////////////////////
	CheckCharging();
}


void Player::ChargeDash()
{
	MoveCheck(speed);

	if (isDash == true)
	{
		if (dir == LEFT)
		{
			pos.x -= 300.0f * Time::DeltaTime();
		}
		else if (dir == RIGHT)
		{
			pos.x += 300.0f * Time::DeltaTime();
		}
	}


	if (true == Input::Up(L"DASH"))
	{
		dashTime = 0.54f;
		isDash = false;
		ChangeState(IDLE);
	}
	else if (dashTime < 0.0f)
	{
		dashTime = 0.54f;
		//isDash		= false;
		ChangeState(IDLE);
	}
	///점프
	if (isJumpKeyPress == false)
	{
		if (true == Input::Press(L"JUMP"))
		{
			isJumpKeyPress = true;
			isJump = true;
			//		jumpMax = pos.y - jumpPower;
			ChangeState(JUMPING);

			isBgImageY = true;
		}
	}


	if (true == Input::Up(L"FIRE"))
	{
		//ChangeULState(DASH);
		if (chargeTime < 0.0f)
		{
			ChangeState(BIGSHOOT);
		}
		else
		{
			ChangeState(LITTLESHOOT);
		}
	}
	//////////////////////////////////////
	CheckCharging();

	dashTime -= Time::DeltaTime();
}
#pragma endregion

#pragma region JUMPING LANDING
///점프 올라갈때
void Player::Jumping()
{
	if (true == Input::Press(DirStrArr[dir]))
	{
		if (false == IsColorCheck((Actor::CHECKDIR)dir, ColorRGB::Magenta))
		{
			isGround = false;
			isJump = false;
			ChangeState(SLIDEWALL);
		}
	}

	if (true == Input::Up(L"JUMP"))
	{
		isGround = false;
		isJump = false;
		//isLanding = true;
		ChangeState(LANDING);
	}

	if (true == IsColorCheck((Actor::CHECKDIR::CHECKBOTTOM), 0))
	{
		isGround = false;
		isJump = false;
		//isLanding = true;
		isDash = false;
		ChangeState(IDLE);

		isBgImageY = false;
	}


	if (true == Input::Press(L"LEFT") || true == Input::Press(L"RIGHT"))
	{
		if (isDash == true)
		{
			MoveCheck(speed * 2.0f);

		}
		else
		{
			MoveCheck(speed);
		}
	}



	if (true == IsColorCheck((Actor::CHECKDIR::CHECKTOP), 0))
	{
		isGround = false;
		isJump = false;
		//isLanding = true;
		ChangeState(LANDING);
	}
	if (true == Input::Press(L"JUMP"))
	{
		pos.y -= jumpPower * Time::DeltaTime();
		jumpPower -= gravityAcc.y * Time::DeltaTime();
	}




	if (true == Input::Up(L"FIRE"))
	{
		//shootRender->PlayAnimation(L"L_LittleShoot");		
		if (chargeTime < 0.0f)
		{
			chargeTime = 1.5f;
			ChangeShootParitcle(L"BigShoot");

			PlayerBigBullet* BigBullet = CreateActor<PlayerBigBullet>();
			BigBullet->SetPos({ pos.x + 10.0f, pos.y - 30.0f });

			if (dir == DIRECTION::RIGHT)
			{
				BigBullet->SetDir(DIRECTION::RIGHT);
			}
			else
			{
				BigBullet->SetDir(DIRECTION::LEFT);
			}
		}
		else
		{
			chargeTime = 1.5f;
			ChangeShootParitcle(L"LittleShoot");

			PlayerLittleBullet* littleBullet = CreateActor<PlayerLittleBullet>();
			littleBullet->SetPos({ pos.x + 10.0f, pos.y - 30.0f });

			if (dir == DIRECTION::RIGHT)
			{
				littleBullet->SetDir(DIRECTION::RIGHT);
			}
			else
			{
				littleBullet->SetDir(DIRECTION::LEFT);
			}
		}
	}

	//else
	//{
	//	shootRender->PlayAnimation(L"NoneShoot");
	//}
	

	//////////////////////////////////////
	CheckCharging();
}

///떨어질때
void Player::Landing()
{
	if (true == Input::Press(DirStrArr[dir])
		&& false == IsColorCheck((Actor::CHECKDIR)dir, ColorRGB::Magenta))
	{
		isGround = false;
		isJump = false;
		ChangeState(SLIDEWALL);
	}


	if (true == Input::Press(L"LEFT") || true == Input::Press(L"RIGHT"))
	{
		if (isDash == true)
		{
			MoveCheck(speed * 2.0f);
		}
		else
		{
			MoveCheck(speed);
		}
	}
	///
	if (true == IsColorCheck((Actor::CHECKDIR::CHECKBOTTOM), 0))
	{
		isGround = false;
		isJump = false;
		isDash = false;
		//isLanding = true;
		ChangeState(IDLE);

		isBgImageY = false;
	}

	if (true == isGround)
	{
		isGround = false;
		isJump = false;
		//isLanding = true;
		ChangeState(IDLE);

		isBgImageY = false;
	}



	if (true == Input::Up(L"FIRE"))
	{
		//shootRender->PlayAnimation(L"L_LittleShoot");		
		if (chargeTime < 0.0f)
		{
			chargeTime = 1.5f;
			ChangeShootParitcle(L"BigShoot");

			PlayerBigBullet* BigBullet = CreateActor<PlayerBigBullet>();
			BigBullet->SetPos({ pos.x + 10.0f, pos.y - 30.0f });

			if (dir == DIRECTION::RIGHT)
			{
				BigBullet->SetDir(DIRECTION::RIGHT);
			}
			else
			{
				BigBullet->SetDir(DIRECTION::LEFT);
			}
		}
		else
		{
			chargeTime = 1.5f;
			ChangeShootParitcle(L"LittleShoot");

			PlayerLittleBullet* littleBullet = CreateActor<PlayerLittleBullet>();
			littleBullet->SetPos({ pos.x + 10.0f, pos.y - 30.0f });

			if (dir == DIRECTION::RIGHT)
			{
				littleBullet->SetDir(DIRECTION::RIGHT);
			}
			else
			{
				littleBullet->SetDir(DIRECTION::LEFT);
			}
		}
	}


	//////////////////////////////////////
	CheckCharging();
}
#pragma endregion

#pragma region WALL JUMP
void Player::WallSlide()
{
	groundCheck = false;
	Pos UpPos = { 0, -100.0f };
	pos -= UpPos * Time::DeltaTime();




	if (false == IsColorCheck((Actor::CHECKDIR)dir, ColorRGB::Magenta)) //좌우방향 체크
	{
		while (IsColorCheck((Actor::CHECKDIR)dir, 0))
		{
			if (dir == CHECKDIR::CHECKLEFT)
			{
				CalDebugPos(pos);
				pos += {1.0f, 0.0f};
			}
			else if (dir == CHECKDIR::CHECKRIGHT)
			{
				CalDebugPos(pos);
				pos -= {1.0f, 0.0f};
			}
		}


	}

	if (true == Input::Press(L"LEFT"))
	{
		wallDust->RenderPos({ -85.0f, -60.0f });
		wallDust->PlayAnimation(L"L_Dust");
	}
	else if (true == Input::Press(L"RIGHT"))
	{
		wallDust->RenderPos({ -55.0f, -60.0f });
		wallDust->PlayAnimation(L"R_Dust");
	}
	else
	{
		wallDust->PlayAnimation(L"NoneDust");
	}



	if (true != IsColorCheck(CHECKDIR::CHECKBOTTOM)) //바닥체크
	{
		wallDust->PlayAnimation(L"NoneDust");
		groundCheck = true;
		ChangeState(IDLE);
	}





	if (true == Input::Up(L"LEFT") || true == Input::Up(L"RIGHT"))
	{
		wallDust->PlayAnimation(L"NoneDust");




		groundCheck = true;
		ChangeState(LANDING);
	}





	//isWallSlide = false;
	if (true == Input::Down(L"JUMP"))
	{
		wallDust->PlayAnimation(L"NoneDust");

		if (dir == DIRECTION::LEFT)
		{
			jumpSpark->RenderPos({ -85.0f, -57.0f });
			jumpSpark->PlayAnimation(L"JumpSpark");
		}
		else if (dir == DIRECTION::RIGHT)
		{
			jumpSpark->RenderPos({ -55.0f, -57.0f });
			jumpSpark->PlayAnimation(L"JumpSpark");
		}


		isWallSlide = true;
		groundCheck = true;
		ChangeState(WALLJUMP);
	}




	//////////////////////////////////////
	CheckCharging();
}

///
void Player::WallJump()
{
	if (true == IsColorCheck((Actor::CHECKDIR::CHECKTOP), 0))
	{
		isGround = false;
		isJump = false;
		//isLanding = true;
		ChangeState(LANDING);
	}

	if (true != IsColorCheck(CHECKDIR::CHECKUNDERGROUND))
	{
		groundCheck = true;
		ChangeState(IDLE);
	}


	if (false == IsColorCheck((Actor::CHECKDIR)dir, ColorRGB::Magenta))
	{
		isGround = false;
		isJump = false;
		isWallSlide = false;
		ChangeState(SLIDEWALL);
		ResetGravity();

		ResetWallGravity();
		ResetWallJumpPwr();
	}


	MoveCheck(speed);

	if (dir == DIRECTION::LEFT)
	{
		if (true == Input::Press(L"JUMP"))
		{
			pos -= wallGravity * Time::DeltaTime();
			wallGravity += wallGravityAcc * Time::DeltaTime();

			pos.y -= (700.0f) * Time::DeltaTime();

			pos.x += wallJumpPWR * Time::DeltaTime();
			wallJumpPWR -= wallGravityAcc.x * Time::DeltaTime();
		}
	}
	else if (dir == DIRECTION::RIGHT)
	{
		if (true == Input::Press(L"JUMP"))
		{
			pos += wallGravity * Time::DeltaTime();
			wallGravity += wallGravityAcc * Time::DeltaTime();

			pos.y -= 700.0f * Time::DeltaTime();

			pos.x -= wallJumpPWR * Time::DeltaTime();
			wallJumpPWR -= wallGravityAcc.x * Time::DeltaTime();
		}
	}


	if (true == Input::Up(L"FIRE"))
	{
		//shootRender->PlayAnimation(L"L_LittleShoot");		
		if (chargeTime < 0.0f)
		{
			chargeTime = 1.5f;
			ChangeShootParitcle(L"BigShoot");
		}
		else
		{
			chargeTime = 1.5f;
			ChangeShootParitcle(L"LittleShoot");
		}
	}

	//else
	//{
	//	shootRender->PlayAnimation(L"NoneShoot");
	//}



	//////////////////////////////////////
	CheckCharging();


}


#pragma endregion

#pragma region ATTACK SKILL

void Player::BigShoot() //큰총발싸
{
	isChangeDir = false;

	if (aniRender->GetCurAni()->aniEnd == true)
	{
		PlayerBigBullet* BigBullet = CreateActor<PlayerBigBullet>();
		BigBullet->SetPos({ pos.x + 10.0f, pos.y - 30.0f });

		if (dir == DIRECTION::RIGHT)
		{
			BigBullet->SetDir(DIRECTION::RIGHT);
		}
		else
		{
			BigBullet->SetDir(DIRECTION::LEFT);
		}

		chargeTime = 1.5f;
		ChangeState(IDLE);
	}
}

void Player::LittleShoot() //작은총
{
	isChangeDir = false;

	if (aniRender->GetCurAni()->aniEnd == true)
	{
		//Bullet* bullet = CreateActor<Bullet>();
		//bullet->SetPos(pos);

		PlayerLittleBullet* littleBullet = CreateActor<PlayerLittleBullet>();
		littleBullet->SetPos({ pos.x + 10.0f, pos.y - 30.0f });

		if (dir == DIRECTION::RIGHT)
		{
			littleBullet->SetDir(DIRECTION::RIGHT);
		}
		else
		{
			littleBullet->SetDir(DIRECTION::LEFT);
		}


		chargeTime = 1.5f;
		ChangeState(IDLE);
	}
}


#pragma endregion




