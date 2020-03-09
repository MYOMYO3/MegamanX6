#include "stdafx.h"
#include "Player.h"
#include "AniRender.h"





void Player::CreateAni()
{
	aniRender = CreateRender<AniRender>(10);
	aniRender->SubPivotMode(PIVOT::CENTER);

	chargeRender = CreateRender<AniRender>(11);
	chargeRender->SubPivotMode(PIVOT::CENTER);
	
	shootRender = CreateRender<AniRender>(13);
	shootRender->SubPivotMode(PIVOT::CENTER);
	shootRender->RenderPos( { -85, -130 } );

	dashRender = CreateRender<AniRender>(12);
	dashRender->SubPivotMode(PIVOT::CENTER);
	dashRender->RenderPos({ -80, -80 });

	afterImageRender = CreateRender<AniRender>(9);
	afterImageRender->SubPivotMode(PIVOT::CENTER);
	afterImageRender->AfterImageOn();

	dashBooster = CreateRender<AniRender>(9);
	dashBooster->SubPivotMode(PIVOT::CENTER);
	//dashBooster->AfterImageOn();
	//dashBooster;

	
	wallDust = CreateRender<AniRender>(999);
	wallDust->SubPivotMode(PIVOT::CENTER);
	//wallDust->AfterImageOn();

	jumpSpark = CreateRender<AniRender>(1000);
	jumpSpark->SubPivotMode(PIVOT::CENTER);
	

	//hpUIRender = CreateRender<AniRender>(1000);
	//hpUIRender->SubPivotMode(PIVOT::CENTER);

	////hpUIRender->CameraEffectOFF();
	//hpUIRender->RenderPos({ -400.0f, -300.0f });

#pragma region BASIC
	//////////////////RIGHT
	aniRender->CreateAnimation(L"R_Start"				, L"X_Basic01.bmp", 0, 14, false,	0.1f);
	aniRender->CreateAnimation(L"R_StartEnd"			, L"X_Basic01.bmp", 15, 17, false,	0.05f);
	aniRender->CreateAnimation(L"R_Idle"				, L"X_Basic01.bmp", 18, 21, true,	0.05f);
	aniRender->CreateAnimation(L"R_Jump"				, L"X_Basic01.bmp", 22, 30, false,	0.06f);
	aniRender->CreateAnimation(L"R_JumpEnd"				, L"X_Basic01.bmp", 30, 30, false,	0.08f); //점프 마지막동작
	aniRender->CreateAnimation(L"R_Landing"				, L"X_Basic01.bmp", 31, 32, false,	0.05f); //31~32 점프 후 착지동작
	aniRender->CreateAnimation(L"R_LittleShoot"			, L"X_Basic01.bmp", 33, 40, false,	0.04f);
	aniRender->CreateAnimation(L"R_BigShoot"			, L"X_Basic01.bmp", 41, 49, false,	0.04f);
	aniRender->CreateAnimation(L"R_Run"					, L"X_Basic01.bmp", 51, 62, true,	0.04f);
	aniRender->CreateAnimation(L"R_Dash"				, L"X_Basic01.bmp", 63, 70, false,	0.06f);
	aniRender->CreateAnimation(L"R_ChargeJump"			, L"X_Basic01.bmp", 73, 94, false,	0.06f);
	aniRender->CreateAnimation(L"R_ChargeRun"			, L"X_Basic01.bmp", 99, 126, true,	0.05f);
	aniRender->CreateAnimation(L"R_ChargeDash"			, L"X_Basic01.bmp", 127, 142, false, 0.05f);
	aniRender->CreateAnimation(L"R_WallSlide"			, L"X_Basic01.bmp", 143, 146, true, 0.05f); // 무슨동작인지 모른다
	aniRender->CreateAnimation(L"R_DashJumptToSlipWall"	, L"X_Basic01.bmp", 147, 151, true, 0.05f);
	aniRender->CreateAnimation(L"R_ChargeSliding"		, L"X_Basic01.bmp", 152, 156, false, 0.1f);
	aniRender->CreateAnimation(L"R_Climb"				, L"X_Basic01.bmp", 160, 171, true, 0.1f);
	aniRender->CreateAnimation(L"R_Collide"				, L"X_Basic01.bmp", 175, 190, true, 0.1f); // 충돌애니메이션 죽는 애니메이션 모아둠
	aniRender->CreateAnimation(L"R_Gotohome"			, L"X_Basic01.bmp", 191, 199, true, 1.0f); //애니메이션 순서가 깨져있음 참고


	//////////////////LEFT
	aniRender->CreateAnimation(L"L_Start"				, L"LX_Basic01.bmp", 0, 14, false, 0.1f);
	aniRender->CreateAnimation(L"L_StartEnd"			, L"LX_Basic01.bmp", 15, 17, false, 0.05f);
	aniRender->CreateAnimation(L"L_Idle"				, L"LX_Basic01.bmp", 18, 21, true, 0.05f);
	aniRender->CreateAnimation(L"L_Jump"				, L"LX_Basic01.bmp", 22, 30, false, 0.06f);
	aniRender->CreateAnimation(L"L_JumpEnd"				, L"LX_Basic01.bmp", 30, 30, false, 0.08f); //점프 마지막동작
	aniRender->CreateAnimation(L"L_Landing"				, L"LX_Basic01.bmp", 31, 32, false, 0.05f);//31~32 점프 후 착지동작
	aniRender->CreateAnimation(L"L_LittleShoot"			, L"LX_Basic01.bmp", 33, 40, false, 0.04f);
	aniRender->CreateAnimation(L"L_BigShoot"			, L"LX_Basic01.bmp", 41, 49, false, 0.04f);
	aniRender->CreateAnimation(L"L_Run"					, L"LX_Basic01.bmp", 51, 62, true, 0.04f);
	aniRender->CreateAnimation(L"L_Dash"				, L"LX_Basic01.bmp", 63, 70, false, 0.06f);
	aniRender->CreateAnimation(L"L_ChargeJump"			, L"LX_Basic01.bmp", 73, 94, false, 0.06f);
	aniRender->CreateAnimation(L"L_ChargeRun"			, L"LX_Basic01.bmp", 99, 126, true, 0.05f);
	aniRender->CreateAnimation(L"L_ChargeDash"			, L"LX_Basic01.bmp", 127, 142, false, 0.05f);
	aniRender->CreateAnimation(L"L_WallSlide"			, L"LX_Basic01.bmp", 143, 146, true, 0.05f); // 무슨동작인지 모른다
	aniRender->CreateAnimation(L"L_DashJumptToSlipWall"	, L"LX_Basic01.bmp", 147, 151, true, 0.05f);
	aniRender->CreateAnimation(L"L_ChargeSliding"		, L"LX_Basic01.bmp", 152, 156, false, 0.1f);
	aniRender->CreateAnimation(L"L_Climb"				, L"LX_Basic01.bmp", 160, 171, true, 0.1f);
	aniRender->CreateAnimation(L"L_Collide"				, L"LX_Basic01.bmp", 175, 190, true, 0.1f);  // 충돌애니메이션 죽는 애니메이션 모아둠
	aniRender->CreateAnimation(L"L_Gotohome"			, L"LX_Basic01.bmp", 191, 199, true, 1.0f);  //애니메이션 순서가 깨져있음 참고

#pragma endregion


#pragma region ULTIMATE
	//////////////RIUGHT
	aniRender->CreateAnimation(L"R_ULStartEnd"				, L"Ultimate.bmp", 0, 2, false, 0.1f);
	aniRender->CreateAnimation(L"R_ULIdle"					, L"Ultimate.bmp", 3, 6, true, 0.2f);
	aniRender->CreateAnimation(L"R_ULJump"					, L"Ultimate.bmp", 7, 15, false, 0.05f); //16~17랜딩 0.06
	aniRender->CreateAnimation(L"R_ULJumpEnd"				, L"Ultimate.bmp", 15, 15, false, 0.06f);
	aniRender->CreateAnimation(L"R_ULLittleShoot"			, L"Ultimate.bmp", 18, 25, false, 0.02f);
	aniRender->CreateAnimation(L"R_ULBigShoot"				, L"Ultimate.bmp", 26, 33, false, 0.04f);
	aniRender->CreateAnimation(L"R_ULRun"					, L"Ultimate.bmp", 36, 49, true, 0.05f);
	aniRender->CreateAnimation(L"R_ULDash"					, L"Ultimate.bmp", 50, 57, false, 0.1f);
	aniRender->CreateAnimation(L"R_ULFlyLeft"				, L"Ultimate.bmp", 58, 63, true, 0.3f);
	aniRender->CreateAnimation(L"R_ULFly"					, L"Ultimate.bmp", 64, 66, true, 0.1f);
	aniRender->CreateAnimation(L"R_ULFlyRight"				, L"Ultimate.bmp", 67, 72, true, 0.3f);
	aniRender->CreateAnimation(L"R_ULChargeJump"			, L"Ultimate.bmp", 73, 94, true, 0.05f);
	aniRender->CreateAnimation(L"R_ULChargeRun"				, L"Ultimate.bmp", 99, 126, true, 0.05f);
	aniRender->CreateAnimation(L"R_ULChargeDash"			, L"Ultimate.bmp", 127, 142, true, 0.05f);
	aniRender->CreateAnimation(L"R_ULChargeFlyLeft"			, L"Ultimate.bmp", 143, 154, true, 0.05f); //거꾸로배열되어있다
	aniRender->CreateAnimation(L"R_ULChargeFly"				, L"Ultimate.bmp", 155, 160, true, 0.05f);
	aniRender->CreateAnimation(L"R_ULChargeFlyRight"		, L"Ultimate.bmp", 161, 172, true, 0.1f);
	aniRender->CreateAnimation(L"R_ULWallSlide"				, L"Ultimate.bmp", 173, 176, false, 0.05f);
	aniRender->CreateAnimation(L"R_ULWallSlideJump"			, L"Ultimate.bmp", 177, 178, false, 0.3f);
	aniRender->CreateAnimation(L"R_ULWallChargeSlide"		, L"Ultimate.bmp", 179, 186, true, 0.1f);
	aniRender->CreateAnimation(L"R_ULWallChargeSlideJump"	, L"Ultimate.bmp", 187, 190, true, 0.3f);
	aniRender->CreateAnimation(L"R_ULClimb"					, L"Ultimate.bmp", 191, 201, true, 0.3f);
	aniRender->CreateAnimation(L"R_ULNovaStrike"			, L"Ultimate.bmp", 205, 215, false, 0.06f);
	aniRender->CreateAnimation(L"R_ULBeHit"					, L"Ultimate.bmp", 214, 223, false, 0.1f);
	aniRender->CreateAnimation(L"R_ULHurt"					, L"Ultimate.bmp", 218, 223, true, 0.1f);
	aniRender->CreateAnimation(L"R_ULComplete"				, L"Ultimate.bmp", 224, 233, false, 1.1f); //거꾸로배열되어있다.
	aniRender->CreateAnimation(L"R_ULSitShoot"				, L"Ultimate.bmp", 234, 247, true, 0.1f);
	aniRender->CreateAnimation(L"R_ULRidePipe"				, L"Ultimate.bmp", 248, 256, true, 0.1f); //총쏘는모션 안쏘는 모션 합쳐져있음
	aniRender->CreateAnimation(L"R_ULDead"					, L"Ultimate.bmp"	, 257, 260, true, 0.1f);
	aniRender->CreateAnimation(L"R_ULAttackSword"			, L"LUltimate.bmp", 261, 275, false, 0.03f);
	aniRender->CreateAnimation(L"R_ULJumpAttackSword"		, L"Ultimate.bmp", 276, 282, false, 0.03f);
	aniRender->CreateAnimation(L"R_ULSlikeAttackSword"		, L"Ultimate.bmp", 283, 291, true, 0.1f);

	///////////LEFT
	aniRender->CreateAnimation(L"L_ULStartEnd"				, L"LUltimate.bmp", 0, 2, false, 0.1f);
	aniRender->CreateAnimation(L"L_ULIdle"					, L"LUltimate.bmp", 3, 6, true, 0.2f);
	aniRender->CreateAnimation(L"L_ULJump"					, L"LUltimate.bmp", 7, 15, false, 0.05f); //16~17 랜딩 0.06
	aniRender->CreateAnimation(L"L_ULJumpEnd"				, L"LUltimate.bmp", 15, 15, false, 0.06f);
	aniRender->CreateAnimation(L"L_ULLittleShoot"			, L"LUltimate.bmp", 18, 25, false, 0.02f);
	aniRender->CreateAnimation(L"L_ULBigShoot"				, L"LUltimate.bmp", 26, 33, false, 0.04f);
	aniRender->CreateAnimation(L"L_ULRun"					, L"LUltimate.bmp", 36, 49, true, 0.05f);
	aniRender->CreateAnimation(L"L_ULDash"					, L"LUltimate.bmp", 50, 57, false, 0.1f);
	aniRender->CreateAnimation(L"L_ULFlyLeft"				, L"LUltimate.bmp", 58, 63, true, 0.3f);
	aniRender->CreateAnimation(L"L_ULFly"					, L"LUltimate.bmp", 64, 66, true, 0.1f);
	aniRender->CreateAnimation(L"L_ULFlyRight"				, L"LUltimate.bmp", 67, 72, true, 0.3f);
	aniRender->CreateAnimation(L"L_ULChargeJump"			, L"LUltimate.bmp", 73, 94, true, 0.1f);
	aniRender->CreateAnimation(L"L_ULChargeRun"				, L"LUltimate.bmp", 99, 126, true, 0.05f);
	aniRender->CreateAnimation(L"L_ULChargeDash"			, L"LUltimate.bmp", 127, 142, true, 0.05f);
	aniRender->CreateAnimation(L"L_ULChargeFlyLeft"			, L"LUltimate.bmp", 143, 154, true, 0.05f); //거꾸로배열되어있다
	aniRender->CreateAnimation(L"L_ULChargeFly"				, L"LUltimate.bmp", 155, 160, true, 0.05f);
	aniRender->CreateAnimation(L"L_ULChargeFlyRight"		, L"LUltimate.bmp", 161, 172, true, 0.1f);
	aniRender->CreateAnimation(L"L_ULWallSlide"				, L"LUltimate.bmp", 173, 176, false, 0.05f);
	aniRender->CreateAnimation(L"L_ULWallSlideJump"			, L"LUltimate.bmp", 177, 178, false, 0.3f);
	aniRender->CreateAnimation(L"L_ULWallChargeSlide"		, L"LUltimate.bmp", 179, 186, true, 0.1f);
	aniRender->CreateAnimation(L"L_ULWallChargeSlideJump"	, L"LUltimate.bmp", 187, 190, true, 0.3f);
	aniRender->CreateAnimation(L"L_ULClimb"					, L"LUltimate.bmp", 191, 201, true, 0.3f);
	aniRender->CreateAnimation(L"L_ULNovaStrike"			, L"LUltimate.bmp", 205, 215, false, 0.06f);
	aniRender->CreateAnimation(L"L_ULBeHit"					, L"LUltimate.bmp", 214, 223, false, 0.1f);
	aniRender->CreateAnimation(L"L_ULHurt"					, L"LUltimate.bmp", 218, 223, true, 0.1f);
	aniRender->CreateAnimation(L"L_ULComplete"				, L"LUltimate.bmp", 224, 233, false, 1.1f); //거꾸로배열되어있다.
	aniRender->CreateAnimation(L"L_ULSitShoot"				, L"LUltimate.bmp", 234, 247, true, 0.1f);
	aniRender->CreateAnimation(L"L_ULRidePipe"				, L"LUltimate.bmp", 248, 256, true, 0.1f); //총쏘는모션 안쏘는 모션 합쳐져있음
	aniRender->CreateAnimation(L"L_ULDead"					, L"LUltimate.bmp", 257, 260, true, 0.1f);
	aniRender->CreateAnimation(L"L_ULAttackSword"			, L"Ultimate.bmp", 261, 275, false, 0.03f);
	aniRender->CreateAnimation(L"L_ULJumpAttackSword"		, L"LUltimate.bmp", 276, 282, false, 0.03f);
	aniRender->CreateAnimation(L"L_ULSlikeAttackSword"		, L"LUltimate.bmp", 283, 291, true, 0.1f);
#pragma endregion	

#pragma region PARTICLE
	chargeRender->CreateAnimation(L"None", L"Empty.bmp", 0, 0, false, 0.03f);
	chargeRender->CreateAnimation(L"Charging", L"Charging.bmp", 0, 9, true, 0.03f);

	shootRender->CreateAnimation(L"NoneShoot",		L"R_XAttacks.bmp", 5, 5, false, 0.1f);
	shootRender->CreateAnimation(L"R_BigShoot",		L"R_XAttacks.bmp", 6, 10, false, 0.05f);
	shootRender->CreateAnimation(L"R_LittleShoot",	L"R_XAttacks.bmp", 0, 4, false, 0.05f);

	shootRender->CreateAnimation(L"L_BigShoot",		L"L_XAttacks.bmp", 6, 10, false, 0.05f);
	shootRender->CreateAnimation(L"L_LittleShoot",	L"L_XAttacks.bmp", 0, 4, false, 0.05f);

	dashRender->CreateAnimation(L"NoneDash", L"R_XAttacks.bmp", 5, 5, false, 0.1f);
	dashRender->CreateAnimation(L"R_Dash", L"R_Dash.bmp",		0, 7, false, 0.04f);
	dashRender->CreateAnimation(L"L_Dash", L"L_Dash.bmp",		0, 7, false, 0.04f);

	dashBooster->CreateAnimation(L"NoneDash", L"R_XAttacks.bmp", 5, 5, false, 0.1f);
	dashBooster->CreateAnimation(L"R_Dash", L"DashBooster.bmp", 0, 6, false, 0.04f);
	dashBooster->CreateAnimation(L"L_Dash", L"LDashBooster.bmp", 0, 6, false, 0.04f);

	wallDust->CreateAnimation(L"NoneDust", L"R_XAttacks.bmp", 5, 5, false, 0.1f);
	wallDust->CreateAnimation(L"R_Dust", L"WallEffect.bmp", 0, 7, true, 0.04f);
	wallDust->CreateAnimation(L"L_Dust", L"LWallEffect.bmp", 0, 7, true, 0.04f);

	jumpSpark->CreateAnimation(L"NoneSpark", L"R_XAttacks.bmp", 5, 5, false, 0.1f);
	jumpSpark->CreateAnimation(L"JumpSpark", L"WallEffect.bmp", 9, 12, false , 0.04f);


	afterImageRender->CreateAnimation(L"NoneImage", L"R_XAttacks.bmp", 5, 5, false, 0.1f);
	afterImageRender->CreateAnimation(L"R_ULJump", L"UltimateAfter.bmp", 7, 15, false, 0.1f);
	afterImageRender->CreateAnimation(L"L_ULJump", L"LUltimateAfter.bmp", 7, 15, false, 0.1f);
	afterImageRender->CreateAnimation(L"R_ULDash", L"UltimateAfter.bmp", 50, 57, false, 0.1f);
	afterImageRender->CreateAnimation(L"L_ULDash", L"LUltimateAfter.bmp", 50, 57, false, 0.1f);




#pragma endregion

	chargeRender->DebugOff();
}