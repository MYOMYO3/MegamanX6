#pragma once
#include "ObjBase.h"
#include "ActorSub.h"
#include <Windows.h>

class RenderMgr;
class Actor;
class JRender : public ActorSub
{
public:
	friend RenderMgr;
	friend Actor;

private:	
	int	 order;

protected:
	BLENDFUNCTION BF;

public:
	int GetAlpha()
	{
		return BF.SourceConstantAlpha;
	}

	void SetAlpha(int _Alpha)
	{
		BF.SourceConstantAlpha = _Alpha;
	}

public:
	inline int GetOrder() const
	{
		return order;
	}

	inline void SetOrder(int _Value)
	{
		order = _Value;
	}

private:
	void PushRenderMgr();
public:
	virtual void Init(int _Value, Actor* _Actor);
	virtual void Render() = 0;

public:
	JRender();
	~JRender();
};

