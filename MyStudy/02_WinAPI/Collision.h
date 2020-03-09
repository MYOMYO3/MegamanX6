#pragma once
#include "ObjBase.h"
#include <GEOMETRY.h>
#include "ActorSub.h"
#include <set>

class Actor;
class Collision : public ActorSub
{
public:
	enum COLTYPE
	{
		RECT, CIRCLE, POINT, MAX
	};

protected:
	std::wstring	groupName;
	COLTYPE		colType;

	std::set<Collision*>::iterator FindIter;
	std::set<Collision*> otherColSet;	//충돌상태를 체크하기위한 자료구조
	
public:
	COLTYPE GetColType()
	{
		return colType;
	}

	const wchar_t* GroupName()
	{
		return groupName.c_str();
	}

public:
	bool Init(const wchar_t* _GroupName, Actor* _Actor, Size _Size = { 10, 10 });

public:
	virtual void DebugRender() = 0;
			void PushColMgr();
			void ColCheck(Collision* _Other);

	virtual	void ColDataSetting() = 0;
	virtual bool IsCol(Collision* _Other) = 0;
	

public:
	Collision();
	virtual ~Collision();
};

