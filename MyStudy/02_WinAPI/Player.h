#pragma once
#include "Actor.h"
#include <ColorRGB.h>

#include <Sound.h>
#pragma region PLAYER STATE ENUM
enum PlAYERSTATE
{
	START, IDLE, RUN, DASH, CHARGERUN, CHARGEDASH, JUMPING, LANDING, VASH, NOVASTRIKE, BIGSHOOT, LITTLESHOOT, JUMPVASH, SLIDEWALL, WALLJUMP, BEHIT , DEAD ,MAX,
};

enum PLAYEROPTION
{
	NONE, CHARGE
};

enum DIRECTION
{
	LEFT, RIGHT, TOP, BOTTOM
};
#pragma endregion

class NovaBomb;
class JRender;
class TransRender;
class AniRender;
class Map;
class Player : public Actor
{
public:
	static Player* m_Inst;
	static Player* Inst()
	{
		return m_Inst;
	}

private: 
	//RENDER
	TransRender*	render;
	AniRender*		aniRender;
	AniRender*		shootRender;	//총발사이펙트
	AniRender*		dashRender;	//총발사이펙트
	AniRender*		chargeRender;
	AniRender*		afterImageRender;
	AniRender*		dashBooster;
	AniRender*		wallDust;
	AniRender*		jumpSpark;

	AniRender*		hpUIRender;

	Pos		afterImageArr[4];
	float	imageDelayTime;

public:
	Pos GetPosArr(int _Index)
	{
		return afterImageArr[_Index];
	}

	AniRender* GetAniRender()
	{
		return aniRender;
	}

private:
	//STATE
	PlAYERSTATE		state;
	PLAYEROPTION	option;
	DIRECTION		dir;
	bool			isChangeDir;
	bool			groundCheck;
	
	bool			isWallSlide;
	Pos				prevWallJumpPos;


	bool isBgImageY;

	float vashTime;

	//STATE VARIABLE
	float			speed;
	float			gravityPwr;
	Pos				gravity;
	Pos				gravityAcc;
	bool			ultimateArmor;

	float			wallGravityPwr;
	Pos				wallGravity;
	Pos				wallGravityAcc;

	int soundCnt;
	bool isNova;

	bool isBgm1;
	bool isBgm2;

	NovaBomb* myNova;

#pragma region ANIMATION NAME STR
	const wchar_t DirStrArr[2][256] =
	{
		L"LEFT",
		L"RIGHT",
	};

	const wchar_t PlayerAniName[MAX][512] =
	{
		L"Start",
		L"Idle"	,
		L"Run"	,
		L"Dash"	,
		L"ChargeRun",
		L"ChargeDash",
		L"Jump",
		L"JumpEnd",
		L"AttackSword",
		L"NovaStrike",
		L"BigShoot",
		L"LittleShoot",
		L"JumpAttackSword",
		L"WallSlide",
		L"Jump",
		L"BeHit",

	};

	const wchar_t PlayerOption[MAX][512] =
	{
		L"None",
		L"Charging",
	};
#pragma endregion

#pragma region ANIMATION VARIABLE
private:	
	// START IDLE
	float	startTime;
	float	endTime;
	// DASH IDLE
	bool	isDash;
	float	dashTime;

	float wallJumpPWR;
	float resetWallJump;
	// JUMPING  LANDING IDLE
	float	jumpPower;
	float	resetJumpPWR;
	bool	isJumpKeyPress;
	bool	isJump;
	bool	isGround;
	bool	isLanding;
	//CHARGE IDLE
	float	chargeTime;

	bool IsBossRoom;
	bool inBossRoom;

	bool isHit;
	bool invincibility;
	float cycle; // 맞았을때 사인함수 사이클

	bool createBoss;


	int deadParticleCnt;
	bool fakeDead;
#pragma endregion

#pragma region INLINE FUNC
public:
	inline void ResetGravity()
	{
		gravity.y = gravityPwr;
	}

	inline void ResetWallGravity()
	{
		wallGravity.x = wallGravityPwr;
	}

	inline void ResetJumpPwr()
	{
		jumpPower = resetJumpPWR;
	}

	inline void ResetWallJumpPwr()
	{
		wallJumpPWR = resetWallJump;
	}

	void ArmorOn()
	{
		ultimateArmor = true;
	}

	bool GetGroundCheck()
	{
		return groundCheck;
	}

	void HitOn()
	{
		isHit = true;
	}

	void HitOff()
	{
		isHit = false;
	}

	void PowerOverOn()
	{
		invincibility = true;
	}

	void PowerOverOff()
	{
		invincibility = true;
	}

	int GetHp()
	{
		return hp;
	}

#pragma endregion

public:
	bool Init()		override;
	void Update()	override;

private:
	void CreateAni();

#pragma region FSM BASIC FUNC
public:
	void Star();
	void Idle();
	void Run();
	void Dash();

	//CHAE
	void ChargeRun();
	void ChargeDash();

	//JUMNG LANDING
	void Jumping();
	void Landing(); 

	//WALSLIDE
	void WallSlide();
	void WallJump();

	//ATTK SKILL

	void BigShoot();
	void LittleShoot();
	
#pragma endregion

#pragma region FSM ULTIMATE FUNC
public:
	//BASIC
	void ULStar();
	void ULIdle();
	void ULRun();
	void ULDash();
	
	//CHARGE
	void ULChargeRun();
	void ULChargeDash();

	//JUMPING LANDING
	void ULJumping();
	void ULLanding();
	
	//WALL SLIDE
	void ULWallSlide();
	void ULWallJump();

	//ATTACK SKILL
	void ULVash();
	void ULNova();
	void ULBigShoot();
	void ULLittleShoot();
	void ULJumpVash();


	void ULBeHit();

	void Dead();
#pragma endregion

#pragma region CHARGE FUNC
private:
	void DirCheck();
	void ULDirCheck();
	void MoveCheck(float			_Speed);
	void DashMoveCheck(float _Speed);
	void ChangeState(PlAYERSTATE	_State);
	void ChangeULState(PlAYERSTATE	_State);
	void ChangeShootParitcle(const std::wstring _Shoot);
	void ChangeDashParticle(const std::wstring _Shoot);
	void RenderAfterImage(const std::wstring _AfterImage);
	void ChangeOption(PLAYEROPTION	_Option);

public:
	void CheckCharging();
	void CheckChargingRun();
	void CheckChargingDash();
#pragma endregion

#pragma region CHECK DEBUG PROPERTY
public:
	void GroundCheck();

	bool IsColorCheck(CHECKDIR _eDir, int Color = ColorRGB::Magenta);
	bool IsGroundColorCheck();

	bool IsCameraCheckX(Pos _Pos);
	bool IsCameraCheckY(Pos _Pos);

	bool isCamerColRX;
	bool isCamerColY;

	bool isCameraColArr[4];

	bool prevCheckX;
	bool prevCheckY;
	float prevLPosX;
	float prevRPosX;

	float prevTPosY;
	float prevBPosY;

private:
	Map		*map;
	int		posColor;
	int		groundColor;

	bool    isPixelCheck;

public:
	void OnSetPixelCheck()
	{
		isPixelCheck = true;
	}

	void OffSetPixelCheck()
	{
		isPixelCheck = false;
	}

	void SetisBossRoom(const bool _Bool)
	{
		IsBossRoom = _Bool;
	}

	void SetBossRoom(const bool _Bool)
	{
		inBossRoom = _Bool;
	}

#pragma endregion


private:
	SoundPlayer* chargeSound;

#pragma region PLAYER OBJ FUNC
public:
	void	SetMap(Map* _Map);
	void	DebugRender() override;
#pragma endregion

public:
	void ColEnter(Collision* _This, Collision* _Other);
	void ColStay(Collision* _This, Collision* _Other);
	void ColExit(Collision* _This, Collision* _Other);

public:
	Player();
	~Player();
};

