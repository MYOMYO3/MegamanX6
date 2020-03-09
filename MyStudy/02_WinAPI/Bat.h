#pragma once
#include "Monster.h"


class BatBomb;
enum BATSTATE
{
	BATIDLE , BATMOVE, BATATTACK, BATDIE, BOSSATT,BATMAX
};

class JRender;
class TransRender;
class AniRender;
class Bat : public Monster
{
private:
	float deathTime;

	BATSTATE state;
	float range;	//플레이어와의 거리
	float attRange;		//사정거리
	int i = 0;
	float cycle;
	float bombCycle;

	BatBomb* myBomb;

	int dir;

	int attCnt;
	int dieCnt;

	const wchar_t AniName[BATSTATE::BATMAX][128] =
	{

	};

public:
	void SetState(BATSTATE _STATE)
	{
		state = _STATE;
	}

public:
	bool Init() override;
	void Update() override;
	bool MonsterDeath() override;

public:

	void IDLE();
	void MOVE();
	void ATTACK();
	void DIE();
	void BOSSATT();
public:
	Bat();
	~Bat();
};

