#include "stdafx.h"
#include "EndingVideo.h"
#include "AniRender.h"
#include <Sound.h>


EndingVideo::EndingVideo()
{

}


EndingVideo::~EndingVideo()
{

}




bool EndingVideo::Init()
{
	render = CreateRender<AniRender>(100);
	render->SubPivotMode(PIVOT::LT);
	//render->CameraEffectOFF();
	render->CreateAnimation(L"1", L"Ending.bmp", 0, 106, false, 0.08f);



	render->PlayAnimation(L"1");


	render->DebugOff();

	return true;
}

void EndingVideo::Update()
{
	if (render->GetCurAni()->curIndex == 1)
	{
		Sound::SoundPlay(L"XE_Dash.wav");
	}

	if (render->GetCurAni()->curIndex == 4)
	{
		Sound::SoundPlay(L"XE_Buster0.wav");
	}

	if (render->GetCurAni()->curIndex == 25)
	{
		//Sound::SoundPlay(L"XE_Buster0.wav");
	}

	if (render->GetCurAni()->curIndex == 29)
	{
		Sound::SoundPlay(L"ZE_Saber.wav");
		Sound::SoundPlay(L"XE_Buster0.wav");
	}

	if (render->GetCurAni()->curIndex == 55)
	{
		Sound::SoundPlay(L"XE_Buster0.wav");
	}

	if (render->GetCurAni()->curIndex == 80)
	{
		Sound::SoundPlay(L"XE_Dash.wav");
	}

}
