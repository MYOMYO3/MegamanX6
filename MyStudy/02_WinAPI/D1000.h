#pragma once
#include "Monster.h"

enum D1000STATE
{
	DIDLE, DDEF, DATTACK, DATTACK2 ,DDIE, DMAX
};

class AniRender;
class D1000 : public Monster
{
private:
	int SpecialAtt;
	D1000STATE state;

	float range; // 사정거리
	float attRange;
	float bulletTime;

	float defTime;
	float attTime;
	bool isParticle;
	bool isShoot;

public:
	void SetState(D1000STATE _STATE)
	{
		state = _STATE;
	}
public:
	bool Init() override;
	void Update() override;

public:
	void IDLE();
	void DEF();
	void ATTACK();
	void ATTACK2();
	void DIE();


	void ColEnter(Collision* _This, Collision* _Other);
	void ColStay(Collision* _This, Collision* _Other);
	void ColExit(Collision* _This, Collision* _Other);


public:
	D1000();
	~D1000();
};

