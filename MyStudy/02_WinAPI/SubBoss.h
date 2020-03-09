#pragma once
#include "Monster.h"



enum SUBSTATE
{
	SUBSTART, SUBIDLE, SUBMOVE, SUBATTACK1, SUBATTACK2, SUBATTACK3, SUBDIE, SUBMAX,
};

class AniRender;
class SubBoss :public Monster
{
	AniRender* aniRender;
	AniRender* backParticle;


	SUBSTATE state;

	float range;
	float moveTime;
	float summonTime;
	float biteTime;

	bool isMove;
	bool isMoving;

	int movingDir;
	int batCnt;

	int		dir;

	int attCnt;

	bool isBite;
	bool failedBite;
	bool isSummon;
	
	const wchar_t SubAniName[SUBMAX][128] =
	{
		L"Start",	
		L"Idle",
		L"Idle2",
		L"Idle2",
		L"BitePrev",
		L"Special",
	};

public:
	bool Init() override;
	void Update() override;

public:
	void ColEnter(Collision* _This, Collision* _Other) override;
	void ColStay(Collision* _This, Collision* _Other) override;
	void ColExit(Collision* _This, Collision* _Other) override;

public:
	void ChangeState(SUBSTATE	_State);
	void Start();
	void Idle();
	void Move();
	//void Move();
	void Attack1();
	void Attack2();
	void Attack3();
	

	void SubDie();
public:
	SubBoss();
	~SubBoss();
};

