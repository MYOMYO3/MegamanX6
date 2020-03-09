#include "stdafx.h"
#include "RoomDoor.h"
#include "AniRender.h"
#include "RectCol.h"
#include "Player.h"
#include <JTIME.h>
#include "Warnning.h"
#include "SceneMgr.h"
#include <Sound.h>
#include "BGImage.h"


int RoomDoor::doorNumber = 0;
RoomDoor::RoomDoor() : state(0), playerMoveX(0.0f) 
{
	
}


RoomDoor::~RoomDoor()
{

}


bool RoomDoor::Init()
{
	aniRender = CreateRender<AniRender>();
	aniRender->SubPivotMode(PIVOT::CENTER);
	

	aniRender->CreateAnimation(L"Idle", L"bossdoor.bmp", 0, 0, false, 0.05f);
	aniRender->CreateAnimation(L"Open",  L"bossdoor.bmp", 0, 12, false, 0.03f);
	aniRender->CreateAnimation(L"Close", L"bossdoor.bmp", 13, 25, false, 0.05f);
	aniRender->PlayAnimation(L"Idle");
	

	RectCol* rectCol = CreateCol<RectCol>(L"BOSSDOOR", { 35, 75 });
	rectCol->SubPivotMode(PIVOT::B);

	return true;
}

void RoomDoor::Update()
{
	if (state == 0)
	{
		aniRender->PlayAnimation(L"Idle");

	}
	else if (state == 1)
	{
		aniRender->PlayAnimation(L"Open");

		
		playerMoveX += (100.0f * Time::DeltaTime());


		Player::Inst()->SetPos({ playerMoveX, playerMoveY });
	}
	else if (state == 2)
	{
		aniRender->PlayAnimation(L"Close");
	}
}

void RoomDoor::ColEnter(Collision* _This, Collision* _Other)
{
	Sound::SoundPlay(L"E_DoorOperated.wav");
	state = 1;

	if (RoomDoor::doorNumber == 1)
	{
		Player::Inst()->SetBossRoom(true);	

		Warnning::warnning->On();
		Warnning::warnning->SetPos({ 320.0f, 240.0f });
		
		Sound::AllSoundPlayerStop();
		Sound::SoundPlay(L"E_warning.wav", 6);
	}

	Player::Inst()->SetisBossRoom(true);
	RoomDoor::doorNumber += 1;




	playerMoveX = Player::Inst()->GetPos().x;
	playerMoveY = Player::Inst()->GetPos().y;
	Player::Inst()->OnSetPixelCheck();

	Player::Inst()->GetAniRender()->PauseOn();

	BGImage::Inst()->isBossRoom = true;
}

void RoomDoor::ColStay(Collision* _This, Collision* _Other)
{
	
}

void RoomDoor::ColExit(Collision* _This, Collision* _Other)
{
	Sound::SoundPlay(L"E_DoorUnlocked.wav");
	state = 2;

	Player::Inst()->OffSetPixelCheck();

	Player::Inst()->GetAniRender()->PauseOff();

	
}
