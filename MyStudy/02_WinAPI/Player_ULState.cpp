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
#include "Vash.h"
#include "JumpVash.h"
#include "NovaBomb.h"

#include <Sound.h>

#define m_PI 3.141592f

//NovaBomb* newbomb = nullptr;


//CreateActor<NovaBomb>();
//Bullet* bullet = nullptr;

void Player::ULStar() // 스타트 상태
{
	
	
	//Sound::SoundPlay(L"V_ready.wav");


	if (soundCnt == 0)
	{
		Sound::SoundPlay(L"V_ready.wav");
		
		Sound::SoundPlay(L"XE_Spawn.wav");
		soundCnt++;
	}

	startTime -= Time::DeltaTime();
	
	if (startTime < 0.0f)
	{
		aniRender->PlayAnimation(L"R_ULStartEnd");
		endTime	-= Time::DeltaTime();
		if (endTime < 0.0f)
		{
			ChangeULState(IDLE);
			startTime	= 3.0f;
			endTime		= 1.0f;
		}		
	}

	SceneMgr::Inst().GetCurScene()->cameraPos = (pos - Pos(645 * 0.5f, 480 * 0.75f));

}

#pragma region BASIC STATE
void Player::ULIdle()
{
	if (true == Input::Press(L"LEFT") || true == Input::Press(L"RIGHT"))
	{
		ChangeULState(RUN);
	}

	if (true == Input::Down(L"DASH"))
	{
		Sound::SoundPlay(L"XE_Dash.wav");
		isDash = true;
		ChangeDashParticle(L"Dash");
		ChangeULState(DASH);
		
		RenderAfterImage(L"ULDash");
		//afterImageRender->PlayAnimation(L"R_ULDash");
	}	

	if (isLanding == false)
	{
		if (isJumpKeyPress == false)
		{
			if (true == Input::Down(L"JUMP"))
			{
				Sound::SoundPlay(L"XE_Jump.wav");
				Sound::SoundPlay(L"XV_Jump.wav");
			}

			if (true == Input::Press(L"JUMP"))
			{
				isJumpKeyPress = true;
				isJump = true;
				isGround = false;
				ChangeULState(JUMPING);

				isBgImageY = true;
			}
		}
	}
	
	if (true == Input::Down(L"VASH"))
	{
		Sound::SoundPlay(L"ZE_Saber.wav");
		ChangeULState(VASH);
	}

	if (true == Input::Up(L"FIRE"))
	{
		if (chargeTime < 0.0f)
		{
			Sound::SoundPlay(L"XE_Buster1.wav");
			ChangeULState(BIGSHOOT);
		}
		else
		{
			Sound::SoundPlay(L"XE_Buster0.wav");
			ChangeULState(LITTLESHOOT);
		}
	}

	//////////////////////////////////////
	CheckCharging();

	if (invincibility == false)
	{
		if (true == isHit)
		{
			ChangeULState(BEHIT);
		}
	}
}

void Player::ULRun() 
{

	if (false == IsGroundColorCheck())
	{
		isGround = false;
		ChangeULState(LANDING);
	}

	MoveCheck(speed);


	if (true == Input::Up(L"LEFT") || true == Input::Up(L"RIGHT"))
	{
		ChangeULState(IDLE);
	}

	if (true == Input::Down(L"DASH"))
	{
		Sound::SoundPlay(L"XE_Dash.wav");
		isDash = true;
		ChangeDashParticle(L"Dash");
		ChangeULState(DASH);
		RenderAfterImage(L"ULDash");
		//afterImageRender->PlayAnimation(L"R_ULDash");
	}

	if (isJumpKeyPress == false)
	{
		if (true == Input::Down(L"JUMP"))
		{
			Sound::SoundPlay(L"XE_Jump.wav");
			Sound::SoundPlay(L"XV_Jump.wav");
		}
		if (true == Input::Press(L"JUMP"))
		{
			
			isJumpKeyPress = true;
			isJump = true;
			ChangeULState(JUMPING);

			isBgImageY = true;
		}
	}

	if (true == Input::Down(L"VASH"))
	{
		Sound::SoundPlay(L"ZE_Saber.wav");
		ChangeULState(VASH);
	}

	if (true == Input::Up(L"FIRE"))
	{
		if (chargeTime < 0.0f)
		{
			Sound::SoundPlay(L"XE_Buster1.wav");
			ChangeULState(BIGSHOOT);
		}
		else
		{
			Sound::SoundPlay(L"XE_Buster0.wav");
			ChangeULState(LITTLESHOOT);
		}
	}



	//////////////////////////////////////
	CheckChargingRun();

	if (invincibility == false)
	{
		if (true == isHit)
		{
			ChangeULState(BEHIT);
		}
	}
	
}

void Player::ULDash()
{

	MoveCheck(speed);


	if (isDash == true)
	{

		DashMoveCheck(300.0f);
		
		
	}
	
	if (isJumpKeyPress == false)
	{
		if (true == Input::Down(L"JUMP"))
		{
			Sound::SoundPlay(L"XE_Jump.wav");
			Sound::SoundPlay(L"XV_Jump.wav");
		}
		if (true == Input::Press(L"JUMP"))
		{
			isJumpKeyPress = true;
			isJump = true;
			//		jumpMax = pos.y - jumpPower;
			
			ChangeULState(JUMPING);
			RenderAfterImage(L"ULJump");

			isBgImageY = true;
			//afterImageRender->PlayAnimation(L"R_ULJump");
		}
	}


	if (true == Input::Up(L"DASH"))
	{
		dashTime = 0.54f;
		isDash = false;
		ChangeULState(IDLE);
	}
	else if (dashTime < 0.0f)
	{

		dashTime = 0.54f;
		//isDash		= false;
		ChangeULState(IDLE);
	}


	if (true == Input::Down(L"VASH"))
	{
		Sound::SoundPlay(L"ZE_Saber.wav");
		ChangeULState(VASH);
	}
	if (true == Input::Up(L"FIRE"))
	{
		if (chargeTime < 0.0f)
		{
			Sound::SoundPlay(L"XE_Buster1.wav");
			ChangeULState(BIGSHOOT);
		}
		else
		{
			Sound::SoundPlay(L"XE_Buster0.wav");
			ChangeULState(LITTLESHOOT);
		}
	}
	//////////////////////////////////////
	CheckChargingDash();

	dashTime -= Time::DeltaTime();

	if (invincibility == false)
	{
		if (true == isHit)
		{
			ChangeULState(BEHIT);
		}
	}
}
#pragma endregion

#pragma region CHARGE STATE

void Player::ULChargeRun()
{
	MoveCheck(speed);

	if (true == Input::Up(L"LEFT") || true == Input::Up(L"RIGHT"))
	{
		ChangeULState(IDLE);
	}

	if (true == Input::Down(L"DASH"))
	{
		Sound::SoundPlay(L"XE_Dash.wav");
		isDash = true;
		ChangeULState(DASH);
		ChangeDashParticle(L"Dash");
		RenderAfterImage(L"ULDash");
	}
	///점프
	if (isJumpKeyPress == false)
	{
		if (true == Input::Down(L"JUMP"))
		{
			Sound::SoundPlay(L"XE_Jump.wav");
			Sound::SoundPlay(L"XV_Jump.wav");
		}
		if (true == Input::Press(L"JUMP"))
		{
			isJumpKeyPress = true;
			isJump = true;
			////		jumpMax = pos.y - jumpPower;
			ChangeULState(JUMPING);
			RenderAfterImage(L"ULJump");

			isBgImageY = true;
		}
	}

	if (true == Input::Down(L"VASH"))
	{
		Sound::SoundPlay(L"ZE_Saber.wav");
		ChangeULState(VASH);
	}


	if (true == Input::Up(L"FIRE"))
	{
		if (chargeTime < 0.0f)
		{
			Sound::SoundPlay(L"XE_Buster1.wav");
			ChangeULState(BIGSHOOT);
		}
		else
		{
			Sound::SoundPlay(L"XE_Buster0.wav");
			ChangeULState(LITTLESHOOT);
		}
	}
	//////////////////////////////////////
	CheckCharging();

	if (invincibility == false)
	{
		if (true == isHit)
		{
			ChangeULState(BEHIT);
		}
	}
}


void Player::ULChargeDash()
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
		ChangeULState(IDLE);
	}
	else if (dashTime < 0.0f)
	{
		dashTime = 0.54f;
		//isDash		= false;
		ChangeULState(IDLE);
	}
	///점프
	if (isJumpKeyPress == false)
	{
		if (true == Input::Down(L"JUMP"))
		{
			Sound::SoundPlay(L"XE_Jump.wav");
			Sound::SoundPlay(L"XV_Jump.wav");
		}
		if (true == Input::Press(L"JUMP"))
		{
			isJumpKeyPress = true;
			isJump = true;
			//		jumpMax = pos.y - jumpPower;
			ChangeULState(JUMPING);

			isBgImageY = true;
		}
	}

	if (true == Input::Down(L"VASH"))
	{
		Sound::SoundPlay(L"ZE_Saber.wav");
		ChangeULState(VASH);
	}
	if (true == Input::Up(L"FIRE"))
	{
		//ChangeULState(DASH);
		if (chargeTime < 0.0f)
		{
			Sound::SoundPlay(L"XE_Buster1.wav");
			ChangeULState(BIGSHOOT);
		}
		else
		{
			Sound::SoundPlay(L"XE_Buster0.wav");
			ChangeULState(LITTLESHOOT);
		}
	}
	//////////////////////////////////////
	CheckCharging();

	dashTime -= Time::DeltaTime();
	if (invincibility == false)
	{
		if (true == isHit)
		{
			ChangeULState(BEHIT);
		}
	}

}
#pragma endregion

#pragma region JUMPING LANDING
///점프 올라갈때
void Player::ULJumping()
{
	if (true == Input::Press(DirStrArr[dir]))
	{
		if (false == IsColorCheck((Actor::CHECKDIR)dir, ColorRGB::Magenta))
		{
			isGround = false;
			isJump = false;
			ChangeULState(SLIDEWALL);
		}
	}

	if (true == Input::Up(L"JUMP"))
	{
		isGround = false;
		isJump = false;
		//isLanding = true;
		ChangeULState(LANDING);
	}

	if (true == IsColorCheck((Actor::CHECKDIR::CHECKBOTTOM), 0))
	{
		isGround = false;
		isJump = false;
		//isLanding = true;
		isDash = false;
		ChangeULState(IDLE);

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
		ChangeULState(LANDING);
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
			Sound::SoundPlay(L"XE_Buster1.wav");
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
			Sound::SoundPlay(L"XE_Buster0.wav");
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

	if (true == Input::Down(L"NOVASTRIKE"))
	{
		Sound::SoundPlay(L"XE_Dash.wav");
		ChangeULState(NOVASTRIKE);
	}

	if (true == Input::Down(L"VASH"))
	{
		Sound::SoundPlay(L"ZE_Saber.wav");
		ChangeULState(JUMPVASH);
	}

	//////////////////////////////////////
	CheckCharging();

	if (invincibility == false)
	{
		if (true == isHit)
		{
			isGround = false;
			isJump = false;
			//isLanding = true;
			isDash = false;
			ChangeULState(BEHIT);
		}
	}
}

///떨어질때
void Player::ULLanding()
{
	if (true == Input::Press(DirStrArr[dir])
		&& false == IsColorCheck((Actor::CHECKDIR)dir, ColorRGB::Magenta))
	{
		isGround = false;
		isJump = false;
		ChangeULState(SLIDEWALL);
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
		ChangeULState(IDLE);

		isBgImageY = false;
	}

	if (true == isGround)
	{
		isGround = false;
		isJump = false;
		//isLanding = true;
		ChangeULState(IDLE);

		isBgImageY = false;
	}



	if (true == Input::Up(L"FIRE"))
	{
		//shootRender->PlayAnimation(L"L_LittleShoot");		
		if (chargeTime < 0.0f)
		{
			chargeTime = 1.5f;
			ChangeShootParitcle(L"BigShoot");
			Sound::SoundPlay(L"XE_Buster1.wav");
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
			Sound::SoundPlay(L"XE_Buster0.wav");
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

	if (true == Input::Down(L"NOVASTRIKE"))
	{
		Sound::SoundPlay(L"XE_Dash.wav");
		ChangeULState(NOVASTRIKE);
	}
	if (true == Input::Down(L"VASH"))
	{
		Sound::SoundPlay(L"ZE_Saber.wav");
		ChangeULState(JUMPVASH);
	}

	//////////////////////////////////////
	CheckCharging();

	if (invincibility == false)
	{
		if (true == isHit)
		{
			isGround = false;
			isJump = false;
			//isLanding = true;
			isDash = false;
			ChangeULState(BEHIT);
		}
	}
}
#pragma endregion

#pragma region WALL JUMP
void Player::ULWallSlide()
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
		ChangeULState(IDLE);
	}


	


	if (true == Input::Up(L"LEFT") || true == Input::Up(L"RIGHT"))
	{
		wallDust->PlayAnimation(L"NoneDust");


		

		groundCheck = true;
		ChangeULState(LANDING);
	}



	

	//isWallSlide = false;
	if (true == Input::Down(L"JUMP"))
	{
		Sound::SoundPlay(L"XE_WallJump.wav");
		wallDust->PlayAnimation(L"NoneDust");

		if (dir == DIRECTION::LEFT)
		{
			jumpSpark->RenderPos({-85.0f, -57.0f});
			jumpSpark->PlayAnimation(L"JumpSpark");
		}
		else if (dir == DIRECTION::RIGHT)
		{
			jumpSpark->RenderPos({-55.0f, -57.0f});
			jumpSpark->PlayAnimation(L"JumpSpark");
		}
		

		isWallSlide = true;
		groundCheck = true;
		ChangeULState(WALLJUMP);
	}




	//////////////////////////////////////
	CheckCharging();

	if (invincibility == false)
	{
		if (true == isHit)
		{
			isGround = false;
			isJump = false;
			//isLanding = true;
			isDash = false;
			ChangeULState(BEHIT);
		}
	}
}

///
void Player::ULWallJump()
{	
	if (true == IsColorCheck((Actor::CHECKDIR::CHECKTOP), 0))
	{
		isGround = false;
		isJump = false;
		//isLanding = true;
		ChangeULState(LANDING);
	}

	if (true != IsColorCheck(CHECKDIR::CHECKUNDERGROUND))
	{
		groundCheck = true;
		ChangeULState(IDLE);
	}

	
	if (false == IsColorCheck((Actor::CHECKDIR)dir, ColorRGB::Magenta))
	{
		isGround = false;
		isJump = false;
		isWallSlide = false;   
		ChangeULState(SLIDEWALL);
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

			pos.x		+= wallJumpPWR * Time::DeltaTime();
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
			Sound::SoundPlay(L"XE_Buster1.wav");
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
			Sound::SoundPlay(L"XE_Buster0.wav");
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

	if (true == Input::Down(L"NOVASTRIKE"))
	{
		//Sound::SoundPlay(L"ZE_Saber.wav");
		Sound::SoundPlay(L"XE_Dash.wav");
		ChangeULState(NOVASTRIKE);
	}

	if (true == Input::Down(L"VASH"))
	{
		Sound::SoundPlay(L"ZE_Saber.wav");
		ChangeULState(JUMPVASH);
	}

	//////////////////////////////////////
	CheckCharging();

	if (invincibility == false)
	{
		if (true == isHit)
		{
			isGround = false;
			isJump = false;
			//isLanding = true;
			isDash = false;
			ChangeULState(BEHIT);
		}
	}


}


#pragma endregion

#pragma region ATTACK SKILL

void Player::ULVash() //칼공격
{
	isChangeDir = false;

	vashTime -= Time::DeltaTime();

	if (vashTime < 0.0f)
	{
		vashTime = 0.15f;
		Vash* vash = CreateActor<Vash>();
		if (dir == DIRECTION::RIGHT)
		{
			vash->SetDir(dir);
			vash->SetPos(pos + Pos{ 20.0f, -60.0f });
		}
		else
		{
			vash->SetDir(dir);
			vash->SetPos(pos + Pos{ -75.0f, -60.0f });
		}
	}

	


	if (aniRender->GetCurAni()->aniEnd == true)
	{
		ChangeULState(IDLE);
	}

	if (invincibility == false)
	{
		if (true == isHit)
		{
			ChangeULState(BEHIT);
		}
	}
}

void Player::ULNova() // 필살기
{

	//if (isNova == false)
	//{
	//	//NovaBomb* bomb 
	//}

	myNova->On();
	myNova->SetPos(pos);

	groundCheck = false;
	isChangeDir = false;

	if (dir == LEFT)
	{
		if (true == IsColorCheck((Actor::CHECKDIR)dir, ColorRGB::Magenta)) //좌우방향 체크
		{
			pos.x -= 500.0f * Time::DeltaTime();
		}

		
	}
	else
	{
		if (true == IsColorCheck((Actor::CHECKDIR)dir, ColorRGB::Magenta)) //좌우방향 체크
		{
			pos.x += 500.0f * Time::DeltaTime();
		}
		
	}

	if (aniRender->GetCurAni()->aniEnd == true)
	{
		myNova->Off();
		groundCheck = true;
		ChangeULState(LANDING);
	}
}


void Player::ULBigShoot() //큰총발싸
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
		ChangeULState(IDLE);
	}
}

void Player::ULLittleShoot() //작은총
{
	isChangeDir = false;	

	if (aniRender->GetCurAni()->aniEnd == true)
	{
		//Bullet* bullet = CreateActor<Bullet>();
		//bullet->SetPos(pos);

		PlayerLittleBullet* littleBullet = CreateActor<PlayerLittleBullet>();
		littleBullet->SetPos({pos.x+ 10.0f, pos.y - 30.0f});
		
		if (dir == DIRECTION::RIGHT)
		{
			littleBullet->SetDir(DIRECTION::RIGHT);
		}
		else
		{
			littleBullet->SetDir(DIRECTION::LEFT);
		}
		

		chargeTime = 1.5f;
		ChangeULState(IDLE);
	}
}

void Player::ULJumpVash() //점프 칼공격
{
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

	vashTime -= Time::DeltaTime();

	if (vashTime < 0.0f)
	{
		vashTime = 0.15f;
		JumpVash* jumpVash = CreateActor<JumpVash>(L"JumpVash");
		if (dir == DIRECTION::RIGHT)
		{
			jumpVash->SetDir(dir);
			jumpVash->SetPos(pos + Pos{ 20.0f, -60.0f });
		}
		else
		{
			jumpVash->SetDir(dir);
			jumpVash->SetPos(pos + Pos{ -75.0f, -60.0f });
		}
	}

	if (aniRender->GetCurAni()->aniEnd == true)
	{
		if (true == isGround)
		{
			ChangeULState(IDLE);
		}
	}
}
#pragma endregion

////HIT AND DIE
void Player::ULBeHit()
{
	if (aniRender->GetCurAni()->aniEnd == true)
	{
		HitOff();
		hp -= 10;

		ChangeULState(IDLE);
	}
}

