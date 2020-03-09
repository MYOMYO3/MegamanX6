#pragma once

#include "Actor.h"



class AniRender;
class Attack2Bomb : public Actor
{
private:
	float deathTime;
	AniRender* aniRender;
	AniRender* particleRender;

	int dir;

	float cycle;

public:
	void SetDir(int _Dir)
	{
		dir = _Dir;
	}



public:
	bool Init() override;
	void Update() override;

public:
	void ColEnter(Collision* _This, Collision* _Other) override;
	void ColStay(Collision* _This, Collision* _Other) override;
	void ColExit(Collision* _This, Collision* _Other) override;

public:
	Attack2Bomb();
	~Attack2Bomb();
};

