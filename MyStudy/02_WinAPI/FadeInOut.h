#pragma once
#include "Actor.h"
class TransRender;
class FadeInOut : public Actor
{
private:
	TransRender* m_FadeInOut;

public:
	bool Start;
	int m_Alpha;
	bool End;

public:
	bool Init() override;
	void Update() override;
public:
	FadeInOut();
	~FadeInOut() override;
};;

