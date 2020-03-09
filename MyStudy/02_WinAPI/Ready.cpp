#include "stdafx.h"
#include "Ready.h"
#include "AniRender.h"


Ready::Ready()
{
}


Ready::~Ready()
{
}

bool Ready::Init()
{
	render = CreateRender<AniRender>(100);
	render->SubPivotMode(PIVOT::CENTER);
	render->CameraEffectOFF();
	render->CreateAnimation(L"Start", L"Ready.bmp", 0,79, false, 0.02f);


	render->PlayAnimation(L"Start");

	render->DebugOff();

	return true;

}

void Ready::Update()
{
	if (render->GetCurAni()->aniEnd == true)
	{
		Die();
	}
}
