#pragma once
#include "Actor.h"

class AniRender;
class EndingVideo : public Actor
{
private:

	AniRender* render;

public:
	bool Init() override;
	void Update() override;

public:
	EndingVideo();
	~EndingVideo();
};

