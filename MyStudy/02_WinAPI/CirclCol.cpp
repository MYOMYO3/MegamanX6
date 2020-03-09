#include "stdafx.h"
#include "CirclCol.h"
#include "Actor.h"
#include "RenderMgr.h"
#include "RectCol.h"
#include "PointCol.h"
#include <Debug.h>
#include <Windows.h>
#include <assert.h>

CircleCol::CircleCol()
{
	colType = CIRCLE;
}


CircleCol::~CircleCol()
{
}

void CircleCol::ColDataSetting()
{
	circle.pos	  = ActorPos();
	circle.radius = subRect.size.HalfX();
}

bool CircleCol::IsCol(Collision* _Other)
{
	COLTYPE CT = _Other->GetColType();

	switch (CT)
	{
	case Collision::RECT:
		return GeoMath::RectToCircle(((RectCol*)_Other)->GetColRect(), circle);
		
	case Collision::CIRCLE:		
		return GeoMath::CircleToCircle(circle, ((CircleCol*)_Other)->circle);
		
	case Collision::POINT:
		return GeoMath::CircleToPoint(circle, ((PointCol*)_Other)->GetColPos());
	case Collision::MAX:		


	default:
		assert(false);
		break;
	}

	return false;
}


void CircleCol::DebugRender()
{
	//int a = ActorPos().IX() - renderRect.size.HalfIX();
	//int b = ActorPos().IY() - renderRect.size.HalfIX();

	//if (Debug::Inst().GetActive() == true)
	//{
	//	Ellipse(RenderMgr::BACKDC(),
	//		ActorPos().IX() - renderRect.size.IX(),
	//		ActorPos().IY() - renderRect.size.IX(),
	//		ActorPos().IX() + (int)circle.radius,
	//		ActorPos().IY() + (int)circle.radius);
	//}


if (Debug::Inst().GetActive() == true)
{
	Ellipse(RenderMgr::BACKDC(),
	ActorPos().IX() - (int)circle.radius,
	ActorPos().IY() - (int)circle.radius,
	ActorPos().IX() + (int)circle.radius,
	ActorPos().IY() + (int)circle.radius );
}

}