#include "stdafx.h"
#include "SceneMgr.h"
#include "TitleScene.h"
#include <Windows.h>
#include "GAMECORE.h"
#include "Player.h"
#include <Path.h>
#include <Sound.h>
#include <Input.h>
#include "CollisionMgr.h"
#include "Asset.h"
#include "Map.h"


#include "Map.h"
#include "TitleIMG.h"
#include "Actor.h"
#include "Button.h"
#include <Debug.h>


spriteActor* titleImage = nullptr;
Button* startBtn = nullptr;
Button* optionBtn = nullptr;
Button* exitBtn = nullptr;

TitleScene::TitleScene() : armorCheatKey(0), selectMenu(1)
{
}


TitleScene::~TitleScene()
{
}


bool TitleScene::Loading()
{
#pragma region CREATEKEY
	Input::CreateKey(L"MLB",			VK_LBUTTON);
	Input::CreateKey(L"MRB",			VK_RBUTTON);
	Input::CreateKey(L"LEFT",			VK_LEFT);
	Input::CreateKey(L"RIGHT",			VK_RIGHT);
	Input::CreateKey(L"DOWN",			VK_DOWN);
	Input::CreateKey(L"UP",				VK_UP);
	Input::CreateKey(L"SAVE",			VK_F3);
	Input::CreateKey(L"LOAD",			VK_F4);
	Input::CreateKey(L"ENTER",			VK_RETURN);
	Input::CreateKey(L"POWER",			VK_F8);
	Input::CreateKey(L"FIRE",			'C');
	Input::CreateKey(L"JUMP",			'X');
	Input::CreateKey(L"DASH",			'Z');
	Input::CreateKey(L"VASH",			'V');
	Input::CreateKey(L"NOVASTRIKE",		'A');
	Input::CreateKey(L"JUMPUP",			'U');
	Input::CreateKey(L"JUMPDOWN",		'I');
	Input::CreateKey(L"GRAVITYUP",		'O');
	Input::CreateKey(L"GRAVITYDOWN",	'P');
	Input::CreateKey(L"ACCUP",			'9');
	Input::CreateKey(L"ACCDOWN",		'0');
	Input::CreateKey(L"MONTYPEUP",		'K');
	Input::CreateKey(L"MONTYPEDOWN",	'L');



#pragma endregion

#pragma region LOAD SOUND

	   
	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"Stage01Bgm.mp3").c_str());
	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"StartBgm.mp3").c_str());
	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"Button.wav").c_str());	
	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"SelectBtn.wav").c_str());


	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"E_BusterHit.wav").c_str());
	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"XE_Buster0.wav").c_str());
	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"XE_Buster1.wav").c_str());
	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"XE_Charging.wav").c_str());
	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"Charging.wav").c_str());
	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"XE_Dash.wav").c_str());
	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"XE_Jump.wav").c_str());
	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"XE_WallJump.wav").c_str());
	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"ZE_Saber.wav").c_str());
	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"V_ready.wav").c_str());
	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"E_DoorOperated.wav").c_str());
	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"E_DoorUnlocked.wav").c_str());
	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"E_warning.wav").c_str());
	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"CS04_RegeneratorComplete.mp3").c_str());
	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"XE_Spawn.wav").c_str());
	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"E_Explosion3.wav").c_str());
	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"E_BossClear.wav").c_str());

	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"CS02_CommandCenter.mp3").c_str());
	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"Stage01_CommanerYammark.mp3").c_str());

	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"VSBoss.mp3").c_str());

	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"XV_Dead.wav").c_str());
	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"XV_HitBig.wav").c_str());
	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"XV_Jump.wav").c_str());
	Sound::SoundLoad((Path::FindPathDir(L"Sound").FullPathString() + L"\\" + L"ZE_Dash.wav").c_str());

#pragma endregion

#pragma region LOAD IMAGE
	//TITLE SELECT SCENE
	Asset::LoadBitImage((Path::FindPathDir(L"Title").FullPathString()  + L"\\" + L"Title.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Select").FullPathString() + L"\\" + L"SelectBG.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Select").FullPathString() + L"\\" + L"SelectChr.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Select").FullPathString() + L"\\" + L"Playerselect.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"UI").FullPathString()     + L"\\" + L"StartBtn.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"UI").FullPathString()     + L"\\" + L"OptionBtn.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"UI").FullPathString()     + L"\\" + L"ExitBtn.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Charcter").FullPathString() + L"\\" + L"Zero.bmp").c_str());
	
	
	//X_BAISC IMAGE SPRITE
	Asset::LoadBitImage((Path::FindPathDir(L"Charcter").FullPathString() + L"\\" + L"X_Basic01.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Charcter").FullPathString() + L"\\" + L"LX_Basic01.bmp").c_str());

	//X_ULTIMATE IMAGE SPRITE
	Asset::LoadBitImage((Path::FindPathDir(L"Charcter").FullPathString() + L"\\" + L"Ultimate.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Charcter").FullPathString() + L"\\" + L"LUltimate.bmp").c_str());

	//CHARCTER PARTICLE
	Asset::LoadBitImage((Path::FindPathDir(L"Charcter").FullPathString() + L"\\" + L"Charging.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Charcter").FullPathString() + L"\\" + L"Empty.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Charcter").FullPathString() + L"\\" + L"R_XAttacks.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Charcter").FullPathString() + L"\\" + L"L_XAttacks.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Charcter").FullPathString() + L"\\" + L"R_Dash.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Charcter").FullPathString() + L"\\" + L"L_Dash.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Charcter").FullPathString() + L"\\" + L"UltimateAfter.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Charcter").FullPathString() + L"\\" + L"LUltimateAfter.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Charcter").FullPathString() + L"\\" + L"DashBooster.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Charcter").FullPathString() + L"\\" + L"LDashBooster.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Charcter").FullPathString() + L"\\" + L"WallEffect.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Charcter").FullPathString() + L"\\" + L"LWallEffect.bmp").c_str());

	//PARTICLE IMAGE
	Asset::LoadBitImage((Path::FindPathDir(L"Charcter").FullPathString() + L"\\" + L"PlayerLittleBullet.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Charcter").FullPathString() + L"\\" + L"LPlayerLittleBullet.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Charcter").FullPathString() + L"\\" + L"PlayerBigBullet.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Charcter").FullPathString() + L"\\" + L"LPlayerBigBullet.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Monster").FullPathString() + L"\\" + L"Explosion.bmp").c_str());

	Asset::LoadBitImage((Path::FindPathDir(L"Charcter").FullPathString() + L"\\" + L"CollideParticle.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Charcter").FullPathString() + L"\\" + L"LCollideParticle.bmp").c_str());

	//MONSTER IMAGE SPRITE
	Asset::LoadBitImage((Path::FindPathDir(L"Monster").FullPathString() + L"\\" + L"Bat.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Monster").FullPathString() + L"\\" + L"RBat.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Monster").FullPathString() + L"\\" + L"Worm.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Monster").FullPathString() + L"\\" + L"LBoss.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Monster").FullPathString() + L"\\" + L"Boss.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Monster").FullPathString() + L"\\" + L"L_Mettool.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Monster").FullPathString() + L"\\" + L"R_Mettool.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Monster").FullPathString() + L"\\" + L"SubBullet.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Monster").FullPathString() + L"\\" + L"D1000.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Monster").FullPathString() + L"\\" + L"LSubBoss.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Monster").FullPathString() + L"\\" + L"RSubBoss.bmp").c_str());

	//MAP IMAGE SPRITE
	Asset::LoadBitImage((Path::FindPathDir(L"Map").FullPathString() + L"\\" + L"Map.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Map").FullPathString() + L"\\" + L"BG_image.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"Map").FullPathString() + L"\\" + L"PixelMap.bmp").c_str());

	//OBJECT
	Asset::LoadBitImage((Path::FindPathDir(L"StageObject").FullPathString() + L"\\" + L"bossdoor.bmp").c_str());

	//UI
	Asset::LoadBitImage((Path::FindPathDir(L"UI").FullPathString() + L"\\" + L"Ready.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"UI").FullPathString() + L"\\" + L"warnning.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"UI").FullPathString() + L"\\" + L"Hud.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"UI").FullPathString() + L"\\" + L"DeadEffect.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"UI").FullPathString() + L"\\" + L"Ending.bmp").c_str());
	Asset::LoadBitImage((Path::FindPathDir(L"UI").FullPathString() + L"\\" + L"GameBackImage.bmp").c_str());

#pragma endregion

#pragma region CREATE SPRITE
	//TITLE SELECT SCENE
	Asset::CreateSprite(L"Title.bmp", 1, 1);
	Asset::CreateSprite(L"SelectBG.bmp", 1, 1);
	Asset::CreateSprite(L"SelectChr.bmp", 1, 1);
	Asset::CreateSprite(L"Playerselect.bmp", 4, 2);
	Asset::CreateSprite(L"StartBtn.bmp", 2, 1);
	Asset::CreateSprite(L"OptionBtn.bmp", 2, 1);
	Asset::CreateSprite(L"ExitBtn.bmp", 2, 1);
	Asset::CreateSprite(L"Zero.bmp", 5, 10);

	//PLAYER
	Asset::CreateSprite(L"X_Basic01.bmp", 5, 40);
	Asset::CreateSprite(L"LX_Basic01.bmp", 5, 40, true);

	//PLAYER SUB
	Asset::CreateSprite(L"Ultimate.bmp", 10, 30);
	Asset::CreateSprite(L"LUltimate.bmp", 10, 30, true);

	//PLAYER PARTICLE
	Asset::CreateSprite(L"Charging.bmp", 5, 2);
	Asset::CreateSprite(L"Empty.bmp", 1, 1);
	Asset::CreateSprite(L"R_XAttacks.bmp", 5, 3, true);
	Asset::CreateSprite(L"L_XAttacks.bmp", 5, 3);
	Asset::CreateSprite(L"UltimateAfter.bmp", 10, 30);
	Asset::CreateSprite(L"LUltimateAfter.bmp", 10, 30, true);

	Asset::CreateSprite(L"R_Dash.bmp", 8, 1);
	Asset::CreateSprite(L"L_Dash.bmp", 8, 1, true);

	Asset::CreateSprite(L"DashBooster.bmp", 7, 1);
	Asset::CreateSprite(L"LDashBooster.bmp", 7, 1, true);
	Asset::CreateSprite(L"WallEffect.bmp", 5, 3);
	Asset::CreateSprite(L"LWallEffect.bmp", 5, 3, true);

	//PARTICLE
	Asset::CreateSprite(L"Explosion.bmp", 10, 4);

	Asset::CreateSprite(L"CollideParticle.bmp", 5, 3);
	Asset::CreateSprite(L"LCollideParticle.bmp", 5, 3, true);

	//PLAYER BULLET
	Asset::CreateSprite(L"PlayerLittleBullet.bmp", 5, 2);
	Asset::CreateSprite(L"LPlayerLittleBullet.bmp", 5, 2, true);
	Asset::CreateSprite(L"PlayerBigBullet.bmp", 10, 2);
	Asset::CreateSprite(L"LPlayerBigBullet.bmp", 10, 2, true);

	//MONSTER
	Asset::CreateSprite(L"Bat.bmp", 5, 3);
	Asset::CreateSprite(L"RBat.bmp", 5, 3, true);
	Asset::CreateSprite(L"Worm.bmp", 5, 5);

	Asset::CreateSprite(L"LBoss.bmp", 10, 12);
	Asset::CreateSprite(L"Boss.bmp", 10, 12, true);

	Asset::CreateSprite(L"L_Mettool.bmp", 5, 6);
	Asset::CreateSprite(L"R_Mettool.bmp", 5, 6, true);

	Asset::CreateSprite(L"SubBullet.bmp", 5, 6);
	Asset::CreateSprite(L"D1000.bmp", 5, 6);

	Asset::CreateSprite(L"LSubBoss.bmp", 6, 7);
	Asset::CreateSprite(L"RSubBoss.bmp", 6, 7, true);

	//MAP
	Asset::CreateSprite(L"Map.bmp", 1, 1);
	Asset::CreateSprite(L"BG_image.bmp", 1, 1);
	Asset::CreateSprite(L"PixelMap.bmp", 1, 1);

	//Map Object
	Asset::CreateSprite(L"bossdoor.bmp", 5, 6);


	//UI
	Asset::CreateSprite(L"Ready.bmp", 10, 8);
	Asset::CreateSprite(L"warnning.bmp", 10, 9);
	Asset::CreateSprite(L"Hud.bmp", 5, 2);
	Asset::CreateSprite(L"DeadEffect.bmp", 12, 1);
	Asset::CreateSprite(L"Ending.bmp", 5, 22);
	Asset::CreateSprite(L"GameBackImage.bmp", 1, 1);

#pragma endregion

	titleImage = Actor::CreateActor<spriteActor>(L"Title");
	titleImage->InitTrRender(L"Title.bmp");
	
	startBtn = Actor::CreateActor<Button>(L"StartBtn");
	startBtn->SetPos({320.0f, 330.0f});
	startBtn->SetButtonName(L"Start");
	startBtn->SetMenu(1);
	

	optionBtn = Actor::CreateActor<Button>(L"OptionBtn");
	optionBtn->SetPos({ 330.0f, 360.0f });
	optionBtn->SetButtonName(L"Option");
	startBtn->SetMenu(2);

	exitBtn = Actor::CreateActor<Button>(L"ExitBtn");
	exitBtn->SetPos({ 330.0f, 390.0f });
	exitBtn->SetButtonName(L"Exit");
	startBtn->SetMenu(3);

	Debug::Inst().Off();

	Sound::SoundPlay(L"StartBgm.mp3", 10);

	return true;
}

void TitleScene::SceneUpdate()
{
	if (0 != GetAsyncKeyState('1'))
	{
		SceneMgr::Inst().ChangeScene(L"TestScene");
	}

	if (true == Input::Down(L"UP"))
	{
		armorCheatKey += 7;

		if (selectMenu > 1)
		{
			--selectMenu;
			Sound::SoundPlay(L"Button.wav");
		}
	}

	if (true == Input::Down(L"DOWN"))
	{
		armorCheatKey += 4;

		if (selectMenu < 3)
		{
			++selectMenu;
			Sound::SoundPlay(L"Button.wav");
		}
	}

	if (armorCheatKey == 33)
	{
		Player::Inst()->ArmorOn();
		armorCheatKey++;
		Sound::SoundPlay(L"SelectBtn.wav");
	}


	switch (selectMenu)
	{
	case 1:
		optionBtn->OptionButtonOff();
		exitBtn->ExitButtonOff();

		startBtn->StartButtonOn();
		break;

	case 2:
		startBtn->StartButtonOff();
		exitBtn->ExitButtonOff();

		optionBtn->OptionButtonOn();
		break;

	case 3:
		optionBtn->OptionButtonOff();
		startBtn->StartButtonOff();

		exitBtn->ExitButtonOn();
		break;
	}

	//if (true == Input::Down(L"ENTER"))
	//{
	//	SceneMgr::Inst().ChangeScene(L"Stage01");

	//	Sound::AllSoundPlayerStop();
	//	Sound::SoundPlay(L"Stage01Bgm.mp3", 10);
	//	Sound::SoundPlay(L"SelectBtn.wav");
	//}
	if (true == Input::Down(L"ENTER"))
	{
		//Sound::AllSoundPlayerStop();
		SceneMgr::Inst().ChangeScene(L"Select");
	}

}

void TitleScene::DebugRender()
{
	//std::wstring Name = L"TitleScene";
	//TextOut(GameCore::MainWindow().GetHDC(), 0, 0, Name.c_str(), (int)Name.size());
	//TextOut(GameCore::MainWindow().GetHDC(), 100, 80, Path::FindPathToString(L"Charcter").c_str(), (int)Path::FindPathToString(L"Charcter").size());
}
