#pragma once
#include "Collision.h"

class CircleCol : public Collision
{
private:
	Circle circle;

public:
	Circle& GetColCircle()
	{
		return circle;
	}

public:
	bool IsCol(Collision* _Other) override;
	void DebugRender() override;
	void ColDataSetting() override;

public:
	CircleCol();
	~CircleCol();
};

