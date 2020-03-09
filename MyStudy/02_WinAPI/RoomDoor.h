#pragma once
#include "Actor.h"



class AniRender;
class RoomDoor : public Actor
{
private:
	AniRender* aniRender;

	int state;

	float playerMoveX;
	float playerMoveY;

	static int doorNumber;

public:
	bool Init() override;
	void Update() override;

public:
	void ColEnter(Collision* _This, Collision* _Other) override;
	void ColStay(Collision* _This, Collision* _Other) override;
	void ColExit(Collision* _This, Collision* _Other) override;

public:
	RoomDoor();
	~RoomDoor();
};

