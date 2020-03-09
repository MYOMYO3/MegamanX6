#include "stdafx.h"
#include "Warnning.h"
#include "AniRender.h"
#include "Boss.h"
#include "BossHp.h"
#include <Sound.h>

Warnning* Warnning::warnning = nullptr;

Warnning::Warnning()
{
}


Warnning::~Warnning()
{
}


bool Warnning::Init()
{
	render = CreateRender<AniRender>(100);
	render->SubPivotMode(PIVOT::CENTER);
	render->CameraEffectOFF();
	render->CreateAnimation(L"Start", L"warnning.bmp", 0, 89, false, 0.09f);


	render->PlayAnimation(L"Start");

	render->DebugOff();

	return true;

}

void Warnning::Update()
{
	if (render->GetCurAni()->aniEnd == true)
	{
		Boss::boss->On();
		BossHp::m_inst->On();

		Die();

		//Sound::SoundPlay(L"CS04_RegeneratorComplete.mp3");
		Sound::SoundPlay(L"VSBoss.mp3");
		Sound::SoundPlay(L"XE_Spawn.wav");
	}
}