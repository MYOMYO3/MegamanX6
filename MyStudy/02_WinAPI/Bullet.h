#pragma once
#include "Actor.h"
class Bullet : public Actor
{
private:
	//float deathTime;

public:
	bool Init() override;
	void Update() override;
	//void Render() override;

	void ColEnter(Collision* _This, Collision* _Other) override;
	void ColStay(Collision* _This, Collision* _Other) override;
	void ColExit(Collision* _This, Collision* _Other) override;

public:
	Bullet();
	~Bullet();
};

