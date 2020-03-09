#include "stdafx.h"
#include "Collision.h"
#include "CollisionMgr.h"
#include "Actor.h"

Collision::Collision()
{
}


Collision::~Collision()
{
}


void Collision::PushColMgr()
{
	CollisionMgr::Inst().PushCol(this);
}

bool Collision::Init(const wchar_t* _GroupName, Actor* _Actor, Size _Size)
{
	actor		= _Actor;
	groupName	= _GroupName;
	pivot = CENTER;
	subRect.size = _Size;
	PushColMgr();

	return true;
}

void Collision::ColCheck(Collision* _Other)
{

	if (this == _Other)
	{
		assert(false);
	}
	//처음 충돌인가
	//충돌중인가
	//충돌끝인가

	//여기까지 어떻게 들어오게 만들것인가?

	//도형끼리 충돌을 했을떄
	if (true == IsCol(_Other))
	{
		//처음충돌했다.
		//collEnter
		// 계속충돌중이다.
		//collstay

		FindIter = otherColSet.find(_Other);

		if (FindIter == otherColSet.end())
		{
			otherColSet.insert(_Other);
			actor->ColEnter(this, _Other);
		}
		else
		{
			actor->ColStay(this, _Other);
		}
	}
	else
	{
		//바로 이전프레임까지 충돌했다.
		//colExit
		//안했을때
		FindIter = otherColSet.find(_Other);
		//이녀석은 날와 전에 충돌한적이 없네????

		if (FindIter != otherColSet.end())
		{
			otherColSet.erase(_Other);
			actor->ColExit(this, _Other);
		}
	}
}