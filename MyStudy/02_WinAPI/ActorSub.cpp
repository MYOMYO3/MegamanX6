#include "stdafx.h"
#include "ActorSub.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Actor.h"


ActorSub::ActorSub() : isCustomSize(false), isCameraEffect(true)
{
}


ActorSub::~ActorSub()
{
}

Pos ActorSub::ActorPos()
{
	if (false == isCameraEffect)
	{
		GetActor()->CalDebugPos(actor->GetPos());
		return actor->GetPos();
	} 
	else
	{
		Pos returnPos;
		
		Pos actorPos = actor->GetPos();
		Pos cameraPos = SceneMgr::Inst().GetCurScene()->cameraPos;

		returnPos = actorPos - cameraPos;

		GetActor()->CalDebugPos(returnPos);

		return returnPos;
	}
}

inline bool ActorSub::IsActive()
{
	bool tempA = ObjBase::IsActive();
	bool tempB = actor->IsActive();

	return tempA && tempB;
}

inline bool ActorSub::IsDeath()
{
	return ObjBase::IsDeath() || actor->IsDeath();
}

Pos ActorSub::CalPivotPos()
{
	Pos pivotSize = subRect.size * -0.5f;

	switch (pivot)
	{
	case LT:
		pivotSize.y -= pivotSize.y;
		pivotSize.x -= pivotSize.x;
		return ActorPos() + pivotSize;

	case T:
		pivotSize.y -= pivotSize.y;
		return ActorPos() + pivotSize;

	case RT:
		pivotSize.y -= pivotSize.y;
		pivotSize.x += pivotSize.x;
		return ActorPos() + pivotSize;

	case R:
		pivotSize.x += pivotSize.x;
		return ActorPos() + pivotSize;

	case RB:
		pivotSize.y += pivotSize.y;
		pivotSize.x += pivotSize.x;
		return ActorPos() + pivotSize;

	case B:
		pivotSize.y += pivotSize.y;
		return ActorPos() + pivotSize;

	case LB:
		pivotSize.y += pivotSize.y;
		pivotSize.x -= pivotSize.x;
		return ActorPos() + pivotSize;

	case L:
		pivotSize.x -= pivotSize.x;
		return ActorPos() + pivotSize;

	case CENTER:
		return ActorPos() + pivotSize;

	case CUSTOM:
		return ActorPos() + subRect.pos;

	default:
		assert(false);
		return Pos::ZERO;
	}

	assert(false);
	return Pos::ZERO;
}


