#include "stdafx.h"
#include "PointCol.h"
#include "CirclCol.h"
#include "Actor.h"
#include "RenderMgr.h"
#include "RectCol.h"
#include "PointCol.h"
#include <Debug.h>
#include <Windows.h>
#include <assert.h>

PointCol::PointCol()
{
	colType = POINT;
}


PointCol::~PointCol()
{
}

bool PointCol::IsCol(Collision* _Other)
{
	COLTYPE CT = _Other->GetColType();

	switch (CT)
	{
	case Collision::RECT:
		return GeoMath::RectToPoint(((RectCol*)_Other)->GetColRect(), pos);
	case Collision::CIRCLE:
		return GeoMath::CircleToPoint(((CircleCol*)_Other)->GetColCircle(), pos);
	case Collision::POINT:
		return pos == ((PointCol*)_Other)->pos;
	case Collision::MAX:		
	default:
		assert(false);
		break;
	}

	return false;
}

void PointCol::ColDataSetting()
{
	pos = ActorPos();
}

void PointCol::DebugRender()
{
	//if (Debug::Inst().GetActive() == true)
	//{
	//	Ellipse(RenderMgr::BACKDC(),
	//		ActorPos().IX() - 3,
	//		ActorPos().IY() - 3,
	//		ActorPos().IX() + 3,
	//		ActorPos().IY() + 3);
	//}	
}
