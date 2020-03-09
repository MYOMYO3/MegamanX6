#pragma once
#include "ObjBase.h"
#include <GEOMETRY.h>

class Actor;
class ActorSub : public ObjBase
{
public:
	bool isCameraEffect;
	
public:
	void CameraEffectOn()
	{
		isCameraEffect = true;
	}

	void CameraEffectOFF()
	{
		isCameraEffect = false;
	}


protected:
	Actor* actor;
	PIVOT  pivot;
	bool   isCustomSize;
	Rect   subRect;


public:
	inline bool IsActive() override;
	inline bool IsDeath() override;

public:
	Pos ActorPos();
	Actor* GetActor()
	{
		return actor;
	}

public:
	void RenderSize(const Size& _RenderSize)
	{
		subRect.size = _RenderSize;
		isCustomSize = true;
	}

	void RenderPos(const Pos& _RenderPos)
	{
		subRect.pos = _RenderPos;
		pivot = CUSTOM;
	}

	void SubPivotMode(PIVOT _Pivot)
	{
		pivot = _Pivot;
	}

	Pos CalPivotPos();



protected:
	ActorSub();
	virtual ~ActorSub() = 0;
};

