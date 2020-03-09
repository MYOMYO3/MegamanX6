#pragma once
#include "Actor.h"


class AniRender;
class Vash : public Actor
{
private:
	AniRender* aniRender;

	float deathTime;
	int		dir;

	bool isStartBullet;

	bool isCol;

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
	Vash();
	~Vash();
};

