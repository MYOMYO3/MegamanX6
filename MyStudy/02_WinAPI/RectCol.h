#pragma once
#include "Collision.h"

class RectCol : public Collision
{
public:
	Rect rect;

public:
	const Rect& GetColRect()
	{
		return rect;
	}

	void SetRectPos(const Pos& _Pos)
	{
		rect.pos +=  _Pos;
	}


public:
	bool IsCol(Collision* _Other) override;
	void ColDataSetting() override;
	void DebugRender() override;

public:
	RectCol();
	~RectCol();
};

