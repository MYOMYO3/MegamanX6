#pragma once
#include <list>
#include "Monster.h"


//class Monster;
class TransRender;
class MonsterMgr
{
private:
	TransRender* render;

public:
	static MonsterMgr& Inst()
	{
		static MonsterMgr m_Inst;
		return m_Inst;
	}

private:
	std::list<Monster*> monsterList;
	std::list<Monster*>::iterator Start;
	std::list<Monster*>::iterator End;

public:
	void PushMonster(Monster* _Monster);
	void EditorAllOff();
	void PopMonster(Monster* _Monster);

	bool SaveData(const wchar_t* _Name);
	bool LoadData(const wchar_t* _Name);
	void MonsterClear();	
	Monster* CreateMonster(int _Type, Pos _Pos);

public:
	MonsterMgr();
	~MonsterMgr();
};

