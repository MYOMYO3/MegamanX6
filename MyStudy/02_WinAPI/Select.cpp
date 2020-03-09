#include "stdafx.h"
#include "Select.h"
#include "GAMECORE.h"
#include "sceneMgr.h"
#include "RenderMgr.h"
#include "Render.h"
#include "TransRender.h"
#include "AniRender.h"
#include "TitleIMG.h"
#include "Asset.h"
#include <Path.h>
#include <Input.h>
#include <Sound.h>
#include <JTIME.h>

#include "Axe.h"
#include "Zero.h"


spriteActor* selectImg = nullptr;
spriteActor* character = nullptr;

Axe* axe = nullptr;
Zero* zero = nullptr;

Select::Select() : changeSceneTime (1.5f), isChangeScene(false)
{

}


Select::~Select()
{
}

bool Select::Loading()
{
	selectImg = Actor::CreateActor<spriteActor>(L"SelectBG");
	selectImg->InitTrRender(L"SelectBG.bmp");

	character = Actor::CreateActor<spriteActor>(L"Megaman");
	character->InitTrRender(L"SelectChr.bmp");
	character->InitAniRender();


	axe = Actor::CreateActor<Axe>(L"AxeStatue");
	axe->SetPos({ 100.0f, 400.0f });

	zero = Actor::CreateActor<Zero>(L"ZeroStatue");
	zero->SetPos({ 450.0f, 400.0f });


	return true;
}


void Select::SceneUpdate()
{


	if (Input::Down(L"RIGHT") == true)
	{
		character->SetMegaman(0);
		Sound::SoundPlay(L"Button.wav");
		zero->SetAniNum(1);
		axe->SetAniNum(0);
				
	}
	if (Input::Down(L"LEFT") == true)
	{
		character->SetMegaman(1);
		Sound::SoundPlay(L"Button.wav");

		zero->SetAniNum(0);
		axe->SetAniNum(1);
	}

	if (Input::Down(L"ENTER"))
	{
		zero->SetAniNum(2);
		axe->SetAniNum(2);
		isChangeScene = true;

		Sound::AllSoundPlayerStop();
		Sound::SoundPlay(L"Stage01Bgm.mp3", 10);
		Sound::SoundPlay(L"SelectBtn.wav");

		//SceneMgr::Inst().ChangeScene(L"Stage01");
	}
	
	if (isChangeScene == true)
	{
		changeSceneTime -= Time::DeltaTime();
	}
	

	if (changeSceneTime < 0.0f)
	{
		SceneMgr::Inst().ChangeScene(L"Stage01");
	}
	
}

void Select::DebugRender()
{

}
