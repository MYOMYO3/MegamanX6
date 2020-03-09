#include "stdafx.h"
#include "FadeInOut.h"
#include "TransRender.h"
#include <JTIME.h>
#include "SceneMgr.h"
#include <Sound.h>

FadeInOut::FadeInOut() : Start(true), m_Alpha(0), End(false)
{
}
FadeInOut::~FadeInOut()
{

}
bool FadeInOut::Init()
{
	m_FadeInOut = CreateRender<TransRender>(100000);
	m_FadeInOut->Sprite(L"GameBackImage.bmp", 0);
	m_FadeInOut->CameraEffectOFF();
	return true;
}




void FadeInOut::Update()
{
	if (true == Start)
	{
		m_Alpha += Time::DeltaTime() * 200;
		if (255 <= m_Alpha)
		{
			m_Alpha = 255;
			Start = false;
			Die();
			//Sound::AllSoundPlayerStop();
			Sound::SoundPlay(L"E_BossClear.wav");
			SceneMgr::Inst().ChangeScene(L"End");
		}
	}
	//else
	//{
	//	m_Alpha -= Time::DeltaTime() * 200;
	//	if (0 >= m_Alpha)
	//	{
	//		m_Alpha = 0;
	//		End = true;
	//		Die();

	//		SceneMgr::Inst().ChangeScene(L"End");
	//	}
	//}

	m_FadeInOut->SetAlpha(m_Alpha);
}