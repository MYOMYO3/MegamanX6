#pragma once
#include "Monster.h"


enum BOSSSTATE
{
	BOSSSTART ,BOSSIDLE, BOSSMOVE, BOSSATTACK1, BOSSATTACK2, BOSSATTACK3, BOSSATTACK4, BOSSDIE, BOSSMAX,
};

class AniRender;
class Boss : public Monster
{
public:
	static Boss* boss;

	Boss* Inst()
	{
		return boss;
	}

	int GetHp()
	{
		return hp;
	}

private:
	AniRender* aniRender;
	AniRender* backParticle;

	
	BOSSSTATE state;

	
	int		dir;
	float startTime;

	float playerDis;
	float playerDisX;
	float playerDisY;
	float range;

	float attack4Time;

	int moveCnt;
	bool isAttack4Bomb1;
	bool isAttack4Bomb2;
	bool isAttack4Bomb3;
	bool isAttack4Bomb4;

	float attack3PosArr[2];

	int stateAttack4Bomb;
	float attack3Time;
	int attack3Cnt;

	float idleTime;
	bool isMove;

	const wchar_t BossAniName[BOSSMAX][128] =
	{
		L"Start",
		L"Idle",
		L"Dash",
		L"Attack1",
		L"Attack2",
		L"Attack3",
		L"Attack4",
	};

public:
	bool Init() override;
	void Update() override;

public:
	void ColEnter(Collision* _This, Collision* _Other) override;
	void ColStay(Collision* _This, Collision* _Other) override;
	void ColExit(Collision* _This, Collision* _Other) override;

public:
	void ChangeState(BOSSSTATE	_State);

	void Start();
	void Idle();
	void Move();
	//void Move();
	void Attack1();
	void Attack2();
	void Attack3();
	void Attack4();

	void BossDie();
	

public:
	Boss();
	~Boss();
};

