#pragma once
#include "Bullet.h"

class AniRender;
class CircleBomb : public Bullet
{
private:
	float deathTime;
	AniRender* aniRender;


public:
	bool Init() override;
	void Update() override;

public:
	void ColEnter(Collision* _This, Collision* _Other) override;
	void ColStay(Collision* _This, Collision* _Other) override;
	void ColExit(Collision* _This, Collision* _Other) override;

public:
	CircleBomb();
	~CircleBomb();
};

