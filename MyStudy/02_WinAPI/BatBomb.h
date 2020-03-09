#pragma once
#include "Monster.h"


class Map;
class AniRender;
class BatBomb : public Monster
{
private:
	float deathTime;
	AniRender* aniRender;

	int state;

	float cycle;

	Map* map;

	bool deadSound;

public:
	void SetState(int _State)
	{
		state = _State;
	}

	void SetHP(int _Data)
	{
		hp = _Data;
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
	BatBomb();
	~BatBomb();
};

