#include "stdafx.h"
#include "Cursor.h"
#include "PointCol.h"
#include "CirclCol.h"
#include "MonsterMgr.h"
#include <Input.h>

Actor* Cursor::selectActor = nullptr;

Cursor::Cursor()
{
}


Cursor::~Cursor()
{
}


bool Cursor::Init()
{
	PointCol* pointCol = CreateCol<PointCol>(L"CURSOR");

	return true;
}

void Cursor::Update()
{
	if (nullptr == selectActor)
	{
		return;
	}
	



	if (true == Input::Press(L"MRB"))
	{


		//selectActor->Off();

		selectActor->Die();
		//MonsterMgr::Inst().PopMonster((Monster*)selectActor);

		selectActor = nullptr;
	}


}

void Cursor::ColEnter(Collision* _This, Collision* _Other)
{
	
	if (nullptr != selectActor)
	{
		return;
	}

	selectActor = _Other->GetActor();	

	int a = 0;
}

void Cursor::ColStay(Collision* _This, Collision* _Other)
{


	int a = 0;
}

void Cursor::ColExit(Collision* _This, Collision* _Other)
{
	selectActor = nullptr;

	int a = 0;
}