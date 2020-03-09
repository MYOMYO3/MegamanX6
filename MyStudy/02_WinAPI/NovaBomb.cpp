#include "stdafx.h"
#include "NovaBomb.h"
#include "RectCol.h"

NovaBomb::NovaBomb()
{
	att = 30;
}


NovaBomb::~NovaBomb()
{
}


bool NovaBomb::Init()
{
	RectCol* novaCol = CreateCol<RectCol>(L"PLAYERATTACK", { 90, 60 });
	novaCol->SubPivotMode(PIVOT::B);
	return true;
}

void NovaBomb::Update()
{

}


void NovaBomb::ColEnter(Collision* _This, Collision* _Other)
{
	_Other->GetActor()->Damaged(att);
}

void NovaBomb::ColStay(Collision* _This, Collision* _Other)
{

}

void NovaBomb::ColExit(Collision* _This, Collision* _Other)
{

}