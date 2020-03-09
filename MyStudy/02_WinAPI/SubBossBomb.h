#pragma once
#include "Actor.h"

class Map;
class AniRender;
class SubBossBomb : public Actor
{
private:
	float deathTime;
	AniRender* aniRender;
	AniRender* particleRender;

	float angle;
	
	Map* map;

	int state;

public:
	void CalAngle();
	

	void SetAngle(float _Angle)
	{
		angle = _Angle;
	}


	void SetMap(Map* _Map);
	


public:
	bool GroundCheck();

public:
	bool Init() override;
	void Update() override;

public:
	void ColEnter(Collision* _This, Collision* _Other) override;
	void ColStay(Collision* _This, Collision* _Other) override;
	void ColExit(Collision* _This, Collision* _Other) override;

	 
public:
	SubBossBomb();
	~SubBossBomb();
};

