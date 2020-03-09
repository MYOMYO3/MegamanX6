#pragma once
#include "UI.h"

class AniRender;
class Ready : public UI
{
private:
	AniRender* render;

public:
	bool Init()		override;
	void Update()	override;

public:
	Ready();
	~Ready();
};

