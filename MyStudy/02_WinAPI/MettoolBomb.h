#pragma once
#include "Monster.h"

class AniRender;
class MettoolBomb : public Monster
{
private:
	float deathTime;
	AniRender* aniRender;

	int state;
	int dir;
	float cycle;

public:
	void SetState(int _State)
	{
		state = _State;
	}

	void SetDir(int _Dir)
	{
		dir = _Dir;
	}

public:
	bool Init() override;
	void Update() override;

	void GroundCheck();

public:
	void ColEnter(Collision* _This, Collision* _Other) override;
	void ColStay(Collision* _This, Collision* _Other) override;
	void ColExit(Collision* _This, Collision* _Other) override;

public:
	MettoolBomb();
	~MettoolBomb();
};

