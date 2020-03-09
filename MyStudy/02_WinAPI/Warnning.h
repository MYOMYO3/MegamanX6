#pragma once
#include "UI.h"

class AniRender;
class Warnning : public UI
{
private:
	AniRender* render;

public:
	static Warnning* warnning;

public:
	bool Init()		override;
	void Update()	override;

public:
	Warnning();
	~Warnning();
};

