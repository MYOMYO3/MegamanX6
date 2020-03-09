#pragma once
#include "Actor.h"

class JRender;
class TransRender;
class AniRender;
class ImageRender;
class spriteActor : public Actor
{
private:
	TransRender* render;
	AniRender*	 aniRender1;
	AniRender*	 aniRender2;

	int selectMegaman;

public:
	void SetMegaman(int _Data)
	{
		selectMegaman = _Data;
	}

public:
	void InitTrRender(const wchar_t* _FileName);
	void InitAniRender(/*const wchar_t* _FileName*/);


	bool Init() override;
	void Update() override;

public:
	spriteActor();
	~spriteActor();
};

