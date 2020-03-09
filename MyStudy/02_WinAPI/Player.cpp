#include "stdafx.h"
#include "Player.h"
#include <WINDOW.h>
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

#include "Map.h"
#include "GAMECORE.h"
#include <WINDOW.h>
#include "RenderMgr.h"

#include "RectCol.h"

#include "Boss.h"
#include "BossHp.h"

#include "NovaBomb.h"

#include "DeadParticle.h"

Player* Player::m_Inst = nullptr;
//Player::m_Inst = Actor::CreateActor<Player>(L"Player", true);
int index = 0;


Player::Player() : startTime(1.5f), endTime(0.3f),state(START), dir(RIGHT),isDash(false), dashTime(0.54f), option(NONE)//dash 스프라이트 장수 * 시간
{
	isChangeDir		= true;
	groundCheck		= true;

	ultimateArmor	= false;
	speed			= 200.0f;	
	jumpPower		= 200.0f;


	wallJumpPWR = 500.0f;
	resetWallJump = 500.0f;

	isJump			= false;
	isGround		= false;
	isJump			= true;
	isLanding		= false;
	isJumpKeyPress	= false;
	isWallSlide = false;
	prevWallJumpPos = { 999999.0f, 0.0f };


	chargeTime		= 1.5f;

	resetJumpPWR	= 600.0f;
	gravityPwr		= 160.0f;
	gravity			= {	0.0f, gravityPwr };
	gravityAcc		= { 0.0f, 450.0f };

	wallGravityPwr = 160.0f;
	wallGravity = { wallGravityPwr, 0.0f };
	wallGravityAcc = { 450.0f, 0.0f };

	imageDelayTime = 0.07f;

	vashTime = 0.15f;

	//rPos = { _Pos.x + 20.0f, _Pos.y - 20.0f };
	//lPos = { _Pos.x - 20.0f, _Pos.y - 20.0f };
	//tPos = { _Pos.x ,		 _Pos.y - 50.0f };
	//
	CHECKPOS[CHECKRIGHT]		= {	15.0F,	-20.0F };
	CHECKPOS[CHECKLEFT]			= { -20.0F, -20.0F };
	CHECKPOS[CHECKTOP]			= { 0.0F,	-50.0F };
	CHECKPOS[CHECKBOTTOM]		= { 0.0F,	  0.0F };
	CHECKPOS[CHECKUNDERGROUND] =  {0.0F,	 10.0F };


	//보이는거
	CHECKPOSSUB[CHECKRIGHT]		= { 0.0F,	  0.0F };
	CHECKPOSSUB[CHECKLEFT]		= { 0.0F,	  0.0F };
	CHECKPOSSUB[CHECKTOP]		= { 0.0F,	  0.0F };
	CHECKPOSSUB[CHECKBOTTOM]	= { 0.0F,	  0.0F };
	//particleRender->GetCurAni()->isDebug = false;

	isPixelCheck = false;
	isCamerColRX = false;
	isCamerColY = false;

	
	isCameraColArr[0] = false;
	isCameraColArr[1] = false;
	isCameraColArr[2] = false;
	isCameraColArr[3] = false;

	prevCheckX = false;
	prevLPosX = 0.0f;
	prevTPosY = 0.0f;

	IsBossRoom = false;
	inBossRoom = false;
	isBgImageY = false;
	isHit = false;

	createBoss = false;

	soundCnt = 0;

	hp = 100;
	isNova = false;

	deadParticleCnt = 0;

	isBgm1 = false;
	isBgm2 = false;
}


Player::~Player()
{
}

bool Player::Init()
{
	if (nullptr == m_Inst)
	{
		m_Inst = this;
	}

	RectCol* playerCol = CreateCol<RectCol>(L"PLAYER",{30, 40});
	playerCol->SubPivotMode(PIVOT::B);

	//vashCol->rect.pos = {30.0f, 30.0f};
	//vashCol->SubPivotMode(PIVOT::LB);

	//vashCol->SetRectPos({50.0f, 50.0f});
	//vashCol->Off();

	CreateAni();
	ultimateArmor = false;
	if (ultimateArmor == false)
	{
		aniRender->PlayAnimation(L"R_Start");
	}
	else
	{
		aniRender->PlayAnimation(L"R_Start");
	}
	
	chargeRender	->PlayAnimation(L"None");
	//particleRender->GetParitcleAni()->isDebug = false;
	shootRender->PlayAnimation(L"NoneShoot");
	dashRender->PlayAnimation(L"NoneDash");
	afterImageRender-> PlayAnimation(L"NoneImage");
	dashBooster->PlayAnimation(L"NoneDash");
	wallDust->PlayAnimation(L"NoneDust");
	jumpSpark->PlayAnimation(L"NoneSpark");
	//afterImageRender->PlayAnimation(L"R_ULDash");

	myNova = CreateActor<NovaBomb>();
	myNova->Off();
	//Sound::SoundPlay(L"V_ready.wav");

	//chargeSound = Sound::SoundPlayNoneReturn();



	return true;
}

void Player::Update()
{
	if (Input::Down(L"ENTER"))
	{
		aniRender->On();
		pos = { 500.0f, 800.0f };
		hp = 100;
		state = IDLE;
		
	}


	//hpUIRender->RenderPos({ SceneMgr::Inst().GetCurScene()->cameraPos.x = 100.0f,  SceneMgr::Inst().GetCurScene()->cameraPos.y + 100.0f });
	GroundCheck();

	//dashRender->PlayAnimation(L"L_Dash");
	if (index == 3)
	{
		index = 0;
	}
	imageDelayTime -= Time::DeltaTime();
	if (imageDelayTime < 0.0f)
	{
		imageDelayTime = 0.04f;
		afterImageArr[index] = pos;
		++index;
	}
	

	

#pragma region DEBUGKEY
	//if (true == Input::Down(L"JUMPUP"))
//{
//	resetJumpPWR += 10.0F;
//}
//if (true == Input::Down(L"JUMPDOWN"))
//{
//	resetJumpPWR -= 10.0F;

//}
//if (true == Input::Down(L"GRAVITYUP"))
//{
//	gravityPwr += 10.0F;
//}
//if (true == Input::Down(L"GRAVITYDOWN"))
//{
//	gravityPwr -= 10.0F;
//}
//if (true == Input::Down(L"ACCUP"))
//{
//	gravityAcc.y += 10.0F;
//}
//if (true == Input::Down(L"ACCDOWN"))
//{
//	gravityAcc.y -= 10.0F;
//}
#pragma endregion
	if (false == ultimateArmor)
	{
		 //UL만들고 손보기

		if (hp <= 0)
		{
			state = DEAD;
		}
		else
		{
			DirCheck();
		}
		switch (state)
		{
		case START:
			Star();
			break;
		case IDLE:
			Idle();
			break;
		case RUN:
			Run();
			break;
		case DASH:
			Dash();
			break;
		case CHARGERUN:
			ChargeRun();
			break;
		case CHARGEDASH:
			ChargeDash();
			break;
		case JUMPING:
			Jumping();
			break;
		case LANDING:
			Landing();
			break;
		case BIGSHOOT:
			BigShoot();
			break;
		case LITTLESHOOT:
			LittleShoot();
			break;
		case SLIDEWALL:
			WallSlide();
			break;
		case WALLJUMP:
			WallJump();
			break;

		case DEAD:
			Dead();
			break;
		}
	}
	else
	{
		
		if (hp <= 0)
		{
			state = DEAD;
		}
		else
		{
			ULDirCheck();
		}
		switch (state)
		{			
		case START:
			ULStar();
			break;
		case IDLE:
			ULIdle();
			break;
		case RUN:
			ULRun();
			break;
		case DASH:
			ULDash();
			break;
		case CHARGERUN:
			ULChargeRun();
			break;
		case CHARGEDASH:
			ULChargeDash();
			break;
		case JUMPING:
			ULJumping();
			break;	
		case LANDING:
			ULLanding();
			break;
		case VASH:
			ULVash();
			break;
		case JUMPVASH:
			ULJumpVash();
			break;
		case NOVASTRIKE:
			ULNova();
			break;
		case BIGSHOOT:
			ULBigShoot();
			break;
		case LITTLESHOOT:
			ULLittleShoot();
			break;
		case SLIDEWALL:
			ULWallSlide();
			break;
		case WALLJUMP:
			ULWallJump();
			break;

		case BEHIT:
			ULBeHit();
			break;

		case DEAD:
			Dead();
			break;
		}		
	}

	if (true == Input::Up(L"JUMP"))
	{
		isJumpKeyPress = false;
	}

	//SceneMgr::Inst().GetCurScene()->cameraPos = (pos - Pos(1280 * 0.5f, 800 *0.5f));	

	//if (createBoss == false)
	//{
	//	if (pos.x > 6400.0f)
	//	{
	//		Boss::boss->On();
	//		BossHp::m_inst->On();

	//		createBoss = true;
	//	}
	//}


	if (IsBossRoom == true)
	{
		if (inBossRoom == true)
		{
			if (SceneMgr::Inst().GetCurScene()->cameraPos.x > 6266.0f )
			{
				SceneMgr::Inst().GetCurScene()->cameraPos = { 6267.0f, 449.0f };
			}
			else 
			{
				SceneMgr::Inst().GetCurScene()->cameraPos += {200.0f * Time::DeltaTime(), 0.0f * Time::DeltaTime() };
			}		
		}

		if (SceneMgr::Inst().GetCurScene()->cameraPos.x > 5700.0f && inBossRoom == false)
		{
			SceneMgr::Inst().GetCurScene()->cameraPos = { 5700.0f, 449.0f };
		}
		else if(SceneMgr::Inst().GetCurScene()->cameraPos.x < 5700.0f)
		{
			SceneMgr::Inst().GetCurScene()->cameraPos += {200.0f * Time::DeltaTime(), 0.0f * Time::DeltaTime() };
		}		

		return;
	}


	if (IsCameraCheckX(SceneMgr::Inst().GetCurScene()->cameraPos) == true)
	{
		if (pos.x > prevLPosX && prevLPosX != 0.0f)
		{
			prevLPosX = 0.0f;
			isCameraColArr[0] = false;
			prevCheckX = false;
		}

		if (pos.x < prevRPosX && prevRPosX != 0.0f)
		{
			prevRPosX = 0.0f;
			isCameraColArr[1] = false;
			prevCheckX = false;
		}
	}


	if (IsCameraCheckY(SceneMgr::Inst().GetCurScene()->cameraPos) == true)
	{
		if (pos.y > prevTPosY && prevTPosY != 0.0f)
		{
			prevTPosY = 0.0f;
			isCameraColArr[2] = false;
			prevCheckY = false;
		}
	}
	
	if (isCameraColArr[0] == true || isCameraColArr[1] == true)
	{		
		int a = 0;
	}
	else
	{
		SceneMgr::Inst().GetCurScene()->cameraPos.x = (pos.x - 645 * 0.5f);
	}

	
	if (isCameraColArr[2] == true )
	{
		int a = 0;
	}
	else
	{
		SceneMgr::Inst().GetCurScene()->cameraPos.y = (pos.y - 480 * 0.75f);
	}





	//sound

	if (isBgm1 == false)
	{
		if (pos.x > 4000.0f && pos.y > 250.0f)
		{
			Sound::AllSoundPlayerStop();
			Sound::SoundPlay(L"Stage01_CommanerYammark.mp3", 100);
			isBgm1 = true;
		}
	}



}


void Player::Dead()
{
	if (fakeDead == false)
	{
		fakeDead = true;
		aniRender->Off();

		Sound::SoundPlay(L"XV_Dead.wav");
		for (int i = 0; i < 50; ++i)
		{
			DeadParticle* newParticle = CreateActor<DeadParticle>();
			newParticle->SetPos(pos);
			deadParticleCnt++;
		}

	}

	hp = 100;
	ChangeULState(IDLE);	
}

void Player::ColEnter(Collision* _This, Collision* _Other)
{	
	HitOn();
}

void Player::ColStay(Collision* _This, Collision* _Other)
{

}

void Player::ColExit(Collision* _This, Collision* _Other)
{

}



