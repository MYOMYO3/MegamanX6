#pragma once
#include "Bullet.h"
class NovaBomb : public Bullet
{
public:
public:
	bool Init() override;
	void Update() override;

public:
	void ColEnter(Collision* _This, Collision* _Other) override;
	void ColStay(Collision* _This, Collision* _Other) override;
	void ColExit(Collision* _This, Collision* _Other) override;

public:
	NovaBomb();
	~NovaBomb();
};

