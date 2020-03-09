#include "stdafx.h"
#include "MonsterMgr.h"
#include "Monster.h"


#include "Bat.h"
#include "Worm.h"
#include "Mettool.h"
#include "SubBoss.h"
#include "Boss.h"
#include "D1000.h"

#include <FILE.h>
#include <assert.h>

//std::list<Monster*> MonsterMgr::monsterList ;

MonsterMgr::MonsterMgr()
{
	
}


MonsterMgr::~MonsterMgr()
{
	
}


void MonsterMgr::PushMonster(Monster* _Monster)
{
	if (nullptr == _Monster)
	{
		assert(false);
	}

	monsterList.push_back(_Monster);
}

void MonsterMgr::PopMonster(Monster* _Monster)
{
	if (nullptr == _Monster)
	{
		assert(false);
	}

	Start = monsterList.begin();
	End = monsterList.end();


	for (; Start != End; ++Start)
	{
		if ((*Start) == _Monster)
		{
			(*Start)->Die();


			monsterList.erase(Start);


		}
	}
}

bool MonsterMgr::SaveData(const wchar_t* _Name)
{
	//MonsterClear();

	FileWBStream wb = FileWBStream(_Name);

	Start	= monsterList.begin();
	End		= monsterList.end();

	int monsterListSize = (int)monsterList.size();

	wb << monsterListSize;
	for (; Start != End; ++Start) 
	{
		wb << (*Start)->GetType();
		wb << (*Start)->GetPos();
	}

	return true;
}

bool MonsterMgr::LoadData(const wchar_t* _Name)
{
	MonsterClear();

	FileRBStream rb = FileRBStream(_Name);
	
	int loadListSize = 0;
	int loadType = 0;
	Pos loadPos = {0,0};


	rb >> loadListSize;
	for (int i = 0; i < loadListSize; ++i)
	{
		rb >> loadType;
		rb >> loadPos;

		CreateMonster(loadType, loadPos);
	}

	EditorAllOff();


	return true;
}

void MonsterMgr::MonsterClear()
{
	Start	= monsterList.begin();
	End		= monsterList.end();

	for (; Start != End; ++Start)
	{
		
		(*Start)->Die();
		//monsterList.erase(Start);
	}
	monsterList.clear();
}

void MonsterMgr::EditorAllOff()
{
	Start = monsterList.begin();
	End = monsterList.end();

	for (; Start != End; ++Start)
	{
		(*Start)->IsEditorOff();
	}
}


Monster* MonsterMgr::CreateMonster(int _Type, Pos _Pos)
{
	switch (_Type)
	{
		case BAT:
			{
				Bat* newMonster = Actor::CreateActor<Bat>(L"Bat", true);
				newMonster->SetPos(_Pos);
				newMonster->IsEditorOn();

				MonsterMgr::Inst().PushMonster(newMonster);
			}
			break;
		case WORM:
			{
				Worm* newMonster = Actor::CreateActor<Worm>(L"Worm", true);
				newMonster->SetPos(_Pos);
				newMonster->IsEditorOn();

				MonsterMgr::Inst().PushMonster(newMonster);
			}
			break;

		case METOOL:
			{
				Mettool* newMonster = Actor::CreateActor<Mettool>(L"Mettool", true);
				newMonster->SetPos(_Pos);
				newMonster->IsEditorOn();

				MonsterMgr::Inst().PushMonster(newMonster);
			}
			break;

		case ED1000:
		{
			D1000* newMonster = Actor::CreateActor<D1000>(L"D1000", true);
			newMonster->SetPos(_Pos);
			newMonster->IsEditorOn();

			MonsterMgr::Inst().PushMonster(newMonster);
		}
		break;

		case SUBBOSS:
		{
			SubBoss* newMonster = Actor::CreateActor<SubBoss>(L"SubBoss", true);
			newMonster->SetPos(_Pos);
			newMonster->IsEditorOn();

			MonsterMgr::Inst().PushMonster(newMonster);
		}
		break;

		case BOSS:
		{
			Boss* newMonster = Actor::CreateActor<Boss>(L"Boss", true);
			newMonster->SetPos(_Pos);
			newMonster->IsEditorOn();

			MonsterMgr::Inst().PushMonster(newMonster);
		}
		break;


	}

	

	return nullptr;
}