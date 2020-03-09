#pragma once
#include "Monster.h"
#include "WormBomb.h"

enum WORMSTATE
{
	WORMIDLE, WORMGROW, WORMATTACK, WORMDIE, WORMMAX
};

class JRender;
class TransRender;
class AniRender;
class Worm : public Monster
{
private:
	int SpecialAtt;
	WORMSTATE state;

	float range; // 사정거리
	float attRange;
	float bulletTime;
	
public:
	void SetState(WORMSTATE _STATE)
	{
		state = _STATE;
	}
public:
	bool Init() override;
	void Update() override;

public:
	void IDLE();
	void GROWUP();
	void ATTACK();
	void DIE();

public:
	Worm();
	~Worm();
};