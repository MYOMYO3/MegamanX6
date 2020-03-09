#pragma once
#include "Actor.h"
#include <iostream>

enum MONSTERTYPE
{
	BAT, WORM, METOOL, ED1000 ,SUBBOSS ,BOSS,TYPEMAX,
};

class JRender;
class TransRender;
class AniRender;
class Monster :	public Actor
{
protected:	
	bool isEditor;
	//int type;
	MONSTERTYPE		type;	
	AniRender*		aniRender;
	AniRender*		particleRender;

	bool deadSound;

public:
	int GetType()
	{
		return type;
	}

	void IsEditorOff()
	{
		isEditor = false;
	}

	void IsEditorOn()
	{
		isEditor = true;
	}

public:
	void OutScreenMonster();

	virtual bool MonsterDeath();

public:
	Monster();
	~Monster();
};

