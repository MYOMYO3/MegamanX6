#pragma once
#include "Monster.h"



class Map;
enum METSTATE
{
	METWAIT ,METIDLE, METMOVE, METATTACK, METDIE, METMAX
};



class AniRender;
class Mettool :	public Monster
{
private:
	float deathTime;
	METSTATE state;
	float range;
	int		dir;

	float distanceX;

	const wchar_t AniName[METSTATE::METMAX][128] =
	{
		L"Wait",  
		L"SitUp", 
		L"Run", 
		L"Jump", 
		
	};

private:
	Map* map;
	int posColor;

public:
	void SetMap(Map* _Map)
	{
		map = _Map;
	}

public:
	bool Init() override;
	void Update() override;
	bool MonsterDeath() override;

public:
	
	bool IsColorCheck(CHECKDIR _eDir, int _Color);
	void GroundCheck();
	void ChangeState(METSTATE _State);


	void WAIT();
	void IDLE();
	void MOVE();
	void ATTACK();
	void DIE();


public:
	Mettool();
	~Mettool();
};

