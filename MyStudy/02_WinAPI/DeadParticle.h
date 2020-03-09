#pragma once
#include "Bullet.h"


class AniRender;
class DeadParticle : public Bullet
{
private:
	AniRender* render;
	Pos dPos;
	float deathTime;

public:
	bool Init() override;
	void Update() override;

public:
	DeadParticle();
	~DeadParticle();
};

