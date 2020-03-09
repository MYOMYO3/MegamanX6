#include "stdafx.h"
#include "CollisionMgr.h"

#include <assert.h>

CollisionMgr::CollisionMgr()
{
}


CollisionMgr::~CollisionMgr()
{
}



void CollisionMgr::AllColClear()
{
	colMapStart = collisionMap.begin();
	colMapEnd = collisionMap.end();

	for (; colMapStart != colMapEnd; ++colMapStart)
	{
		colMapStart->second.clear();
	}
}

void CollisionMgr::Release()
{
	colMapStart = collisionMap.begin();
	colMapEnd = collisionMap.end();

	for (; colMapStart != colMapEnd; ++colMapStart)
	{
		ColStart = colMapStart->second.begin();
		ColEnd = colMapStart->second.end();

		for (; ColStart != ColEnd;)
		{
			if (false == (*ColStart)->IsDeath())
			{
				++ColStart;
				continue;
			}
			ColStart = colMapStart->second.erase(ColStart);
		}
	}
}

void CollisionMgr::DebugRender()
{
	colMapStart = collisionMap.begin();
	colMapEnd = collisionMap.end();

	for (; colMapStart != colMapEnd; ++colMapStart)
	{
		ColStart = colMapStart->second.begin();
		ColEnd = colMapStart->second.end();

		for (; ColStart != ColEnd; ++ColStart)
		{
			if (false == (*ColStart)->IsActive())
			{
				//++ColStart;
				continue;
			}
			(*ColStart)->DebugRender();
		}
	}
}

bool CollisionMgr::IsLink(const wchar_t* _Left, const wchar_t* _Right)
{
	std::wstring left = _Left;
	std::wstring right= _Right;

	return (linkMap.end()) == linkMap.find(left + right)
		&& (linkMap.end()) == linkMap.find(right + left);

}

void CollisionMgr::Link(const wchar_t* _Left, const wchar_t* _Right)
{
	//if (false == IsLink(_Left, _Right))
	//{
	//	assert(false);
	//}

	std::map<std::wstring, std::list<Collision*>>::iterator ColGroupIter = collisionMap.find(_Left);
	if (ColGroupIter == collisionMap.end())
	{
		collisionMap.insert(std::map<std::wstring, std::list<Collision*>>::value_type(_Left, std::list<Collision*>()));
	}

	ColGroupIter = collisionMap.find(_Right);
	if (ColGroupIter == collisionMap.end())
	{
		collisionMap.insert(std::map<std::wstring, std::list<Collision*>>::value_type(_Right, std::list<Collision*>()));
	}


	LinkData data;
	data.leftName = _Left;
	data.rightName = _Right;
	linkMap.insert( std::map<std::wstring, LinkData>::value_type(data.leftName + data.rightName, data) );
	
}


void CollisionMgr::PushCol(Collision* _Col)
{
	std::map<std::wstring, std::list<Collision*>>::iterator ColGroupIter = collisionMap.find(_Col->GroupName());

	if (collisionMap.end() == ColGroupIter)
	{
		collisionMap.insert(std::map<std::wstring, std::list<Collision*>>::value_type(_Col->GroupName(), std::list<Collision*>()) );
		ColGroupIter = collisionMap.find(_Col->GroupName());
	}

	ColGroupIter->second.push_back(_Col);
}

void CollisionMgr::Coll()
{
	//그룹충돌에는 두가지 경우가 있는데
	// 1.같은 그룹내에서의 충돌
	// 2.다른 그룹

	LinkStart	= linkMap.begin();
	LinkEnd		= linkMap.end();

	for (; LinkStart != LinkEnd; ++LinkStart)
	{
		if (LinkStart->second.leftName != LinkStart->second.rightName)
		{
			GroupCol(LinkStart->second.leftName.c_str(), LinkStart->second.rightName.c_str());
		}
		else
		{

		}
	}
}

void CollisionMgr::GroupCol(const wchar_t* _Left, const wchar_t* _Right)
{
	LeftGroup	= collisionMap.find(_Left);
	RightGroup	= collisionMap.find(_Right);

	if (LeftGroup  == collisionMap.end() 
	 || RightGroup == collisionMap.end())
	{
		assert(false);
	}

	if	(0 >= LeftGroup ->second.size() 
	  || 0 >= RightGroup->second.size())
	{
		return;
	}

	LeftStart	= LeftGroup->second.begin();
	LeftEnd		= LeftGroup->second.end();

	for (; LeftStart != LeftEnd; ++LeftStart)
	{
		if (false == (*LeftStart)->IsActive())
		{
			continue;
		}
		(*LeftStart)->ColDataSetting();

		RightStart	= RightGroup->second.begin();
		RightEnd	= RightGroup->second.end();

		for (; RightStart != RightEnd; ++RightStart)
		{
			if (false == (*RightStart)->IsActive())
			{
				continue;
			}

			(*RightStart)->ColDataSetting();
			(*LeftStart) ->ColCheck((*RightStart));
		}
	}



}

void CollisionMgr::GroupCol(const wchar_t* _This)
{

}

