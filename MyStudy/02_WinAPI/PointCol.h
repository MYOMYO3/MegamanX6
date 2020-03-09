#pragma once
#include	 "Collision.h"

class PointCol : public Collision
{
private:
	Pos pos;

public:
	const Pos& GetColPos()
	{
		return pos;
	}

public:
	bool IsCol(Collision* _Other) override;
	void ColDataSetting() override;
	void DebugRender() override;

public:
	PointCol();
	~PointCol();
};

