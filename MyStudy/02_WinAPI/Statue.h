#pragma once
#include "Actor.h"


class AniRender;
class Statue : public Actor
{
protected:
	float deathTime;
	AniRender* aniRender;
	int selectAni;

public:
	void SetAniNum(const int _Data)
	{
		selectAni = _Data;
	}

public:
	bool Init() override;
	void Update() override;
	
public:
	Statue();
	~Statue();
};

