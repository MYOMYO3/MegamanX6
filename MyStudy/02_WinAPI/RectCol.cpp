#include "stdafx.h"
#include "RectCol.h"
#include "RenderMgr.h"
#include "Actor.h"
#include "CirclCol.h"
#include "PointCol.h"
#include <Debug.h>
#include <assert.h>


RectCol::RectCol() : rect(PIVOT::CENTER)
{
	colType = RECT;
}


RectCol::~RectCol()
{
}

void RectCol::ColDataSetting()
{
	rect.pivot	= pivot;
	rect.pos	= ActorPos() + subRect.pos;	
	rect.size	= subRect.size;	
}

bool RectCol::IsCol(Collision* _Other)
{
	COLTYPE CT = _Other->GetColType();

	switch (CT)
	{
	case Collision::RECT:
		return GeoMath::RectToRect(rect, ((RectCol*)_Other)->rect);
	case Collision::CIRCLE:
		return GeoMath::RectToCircle(rect, ((CircleCol*)_Other)->GetColCircle());
	case Collision::POINT:
		return GeoMath::RectToPoint(rect, ((PointCol*)_Other)->GetColPos());
	case Collision::MAX:	
	default:
		assert(false);
		break;
	}

	return false;
}

void RectCol::DebugRender()
{
	if (Debug::Inst().GetActive() == true)
	{
		//Rectangle(RenderMgr::BACKDC(),
		//	ActorPos().IX() - renderRect.size.HalfIX(),
		//	ActorPos().IY() - renderRect.size.IY(),
		//	ActorPos().IX() + renderRect.size.HalfIX(),
		//	ActorPos().IY()  );

		ColDataSetting();

		Rectangle(RenderMgr::BACKDC(),
			rect.ICalPosX(),
			rect.ICalPosY(),
			rect.ICalSizeX(),
			rect.ICalSizeY()
		);

		/*Rectangle(RenderMgr::BACKDC(),
			ActorPos().IX() - subRect.size.HalfIX(),
			ActorPos().IY() - subRect.size.HalfIY(),
			ActorPos().IX() + subRect.size.HalfIX(),
			ActorPos().IY() + subRect.size.HalfIY());*/
	}
}