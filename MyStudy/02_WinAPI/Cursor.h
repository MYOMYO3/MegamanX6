#pragma once
#include "Actor.h"


class Collision;
class Cursor : public Actor
{
private:
	static Actor* selectActor;

public:
	bool Init()		override;
	void Update()	override;
	//void Render() override;

	void ColEnter	(Collision* _This, Collision* _Other) override;
	void ColStay	(Collision* _This, Collision* _Other) override;
	void ColExit	(Collision* _This, Collision* _Other) override;


public:
	Cursor();
	~Cursor();
};

