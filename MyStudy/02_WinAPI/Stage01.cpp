#include "stdafx.h"
#include "Stage01.h"
#include "GAMECORE.h"
#include "sceneMgr.h"
#include "Player.h"
#include "Monster.h"
#include <Path.h>
#include "Map.h"
#include "RenderMgr.h"
#include "Asset.h"
#include "CollisionMgr.h"
#include "MonsterMgr.h"
#include <Sound.h>
#include "BGImage.h"
#include <Input.h>
#include <Debug.h>
#include <JTIME.h>
#include "RoomDoor.h"
#include "Boss.h"
#include "Ready.h"
#include "Warnning.h"
#include "PlayerHp.h"
#include "BossHp.h"


Map*		stageMap	= nullptr;
Player*		NewPlayer	= nullptr;
BGImage*	bgImage		= nullptr;

RoomDoor* leftDoor = nullptr;
RoomDoor* rightDoor = nullptr;

Ready* ready = nullptr;
Warnning* warnning = nullptr;

PlayerHp* playerHp = nullptr;



Stage01::Stage01()
{
}


Stage01::~Stage01()
{
}

bool Stage01::Loading()
{



#pragma region CREATE ACTOR
	//PLAYER
	Player::m_Inst = Actor::CreateActor<Player>(L"Player", true);
	Player::Inst()->PossibleOverScene(L"Stage01", L"Stage02", L"Ending");
	Player::Inst()->SetPos({500.0f, 800.0f });

	//MAP
	//stageMap = Actor::CreateActor<Map>(L"Map");
	//stageMap->PossibleOverScene(L"Stage01");
	Map::m_inst = Actor::CreateActor<Map>(L"Map");
	Map::m_inst->PossibleOverScene(L"Stage01");

	BGImage::m_inst = (BGImage*)Actor::CreateActor<BGImage>(L"BG_image");
	BGImage::Inst()->PossibleOverScene(L"Stage01");
	//bgImage->SetPos({ Player::Inst()->GetPos().x * 1.5f, Player::Inst()->GetPos().y * 0.8f });

	//ETC
	Player::Inst()->SetMap(Map::m_inst);

	leftDoor = Actor::CreateActor<RoomDoor>(L"LeftDoor", true);
	rightDoor = Actor::CreateActor<RoomDoor>(L"LeftDoor", true);
	leftDoor->SetPos({5724.0f, 710.0f});
	rightDoor->SetPos({ 6310.0f, 710.0f });

	

	Boss::boss = Actor::CreateActor<Boss>(L"Boss", true);
	Boss::boss->SetPos({ 6780.0f, 772.0f });
	Boss::boss->IsEditorOn();
	Boss::boss->Off();
		

	ready = Actor::CreateActor<Ready>(L"ready", true);
	ready->SetPos({ 320.0f, 240.0f });
	
	Warnning::warnning = Actor::CreateActor<Warnning>(L"warnning", true);
	//Warnning::warnning->SetPos({ 6414, 772.0f });

	Warnning::warnning->SetPos({ 320.0f, 240.0f });
	Warnning::warnning->Off();

	playerHp = Actor::CreateActor<PlayerHp>(L"PlayerHp", true);
	playerHp->SetPos({50.0f, 200.0f });

	BossHp::m_inst = Actor::CreateActor<BossHp>(L"BossHp", true);
	BossHp::m_inst->SetPos({ 600.0f, 200.0f });
	BossHp::m_inst->Off();


#pragma endregion

#pragma region LINK COLLISION
	CollisionMgr::Inst().Link(L"PLAYERATTACK",	L"MONSTER");
	CollisionMgr::Inst().Link(L"MONSTER", L"PLAYERATTACK");
	
	CollisionMgr::Inst().Link(L"PLAYER", L"MONSTER");
	CollisionMgr::Inst().Link(L"PLAYER", L"MONSTERBOMB");
	CollisionMgr::Inst().Link(L"MONSTERBOMB", L"PLAYER");
	CollisionMgr::Inst().Link(L"BOSSDOOR", L"PLAYER");

	CollisionMgr::Inst().Link(L"SUBBOSS", L"PLAYER");

	//MAP EDITOR
	CollisionMgr::Inst().Link(L"CURSOR"	, L"MONSTER");
#pragma endregion


#pragma region FILE IO
	

	//(YPATH::FindPathToDir(L"DATA").FullPathString() + L"\\" + L"Stage01.MAPDATA").c_str())
	if (true == IO::ExistFile((Path::FindPathDir(L"DATA").FullPathString() + L"\\" + L"Stage01.MAPDATA").c_str()))
	{
		MonsterMgr::Inst().LoadData((Path::FindPathDir(L"DATA").FullPathString() + L"\\" + L"Stage01.MAPDATA").c_str());
	}
	return true;
#pragma endregion	
}

void Stage01::SceneUpdate()
{	
	
	//if ( true == Input::Press(L"RIGHT"))
	//{
	//	//float NUM = 100.0f;


	//	bgImage->SetPos({ Player::m_Inst->GetPos().x , Player::m_Inst->GetPos().y * 0.7f });
	//	//bgImage->SetPos(Player::m_Inst->GetPos());
	//}
	//if (true == Input::Press(L"LEFT"))
	//{

	//	bgImage->SetPos({ Player::m_Inst->GetPos().x, Player::m_Inst->GetPos().y * 0.7f });
	//	//bgImage->SetPos(Player::m_Inst->GetPos());
	//}

	if (Input::Down(L"POWER"))
	{
		Player::Inst()->PowerOverOn();
	}

	if (0 != GetAsyncKeyState(VK_F8))
	{
		Debug::Inst().On();		
	}
	if (0 != GetAsyncKeyState(VK_F7))
	{
		Debug::Inst().Off();
	}

	
}

void Stage01::DebugRender()
{
	if (Debug::Inst().GetActive() == true)
	{
		std::wstring KEY = L"방향키 : 이동 Z : 대쉬 X: 점프 C: 총쏘기 V: 칼공격 A: 필살기 F6 : 맵에디터";
		TextOut(RenderMgr::BACKDC(), 10, 10, KEY.c_str(), (int)KEY.size());
		std::wstring DebugText = L"Stage01";

		TextOut(RenderMgr::BACKDC(), 10, 30, DebugText.c_str(), (int)DebugText.size());

		wchar_t ArrText[256];
		swprintf_s(ArrText, L"Mouse Pos  x : %f y : %f", GameCore::MainWindow().MousePos().x, GameCore::MainWindow().MousePos().y);
		DebugText = ArrText;
		TextOut(RenderMgr::BACKDC(), 10, 50, DebugText.c_str(), (int)DebugText.size());

		swprintf_s(ArrText, L"Map Pos x : %f y : %f", Map::Inst()->GetPos().x, Map::Inst()->GetPos().y);
		DebugText = ArrText;
		TextOut(RenderMgr::BACKDC(), 10, 70, DebugText.c_str(), (int)DebugText.size());

		swprintf_s(ArrText, L"Player Pos x : %f y : %f", Player::m_Inst->GetPos().x, Player::m_Inst->GetPos().y);
		DebugText = ArrText;
		TextOut(RenderMgr::BACKDC(), 10, 90, DebugText.c_str(), (int)DebugText.size());

		swprintf_s(ArrText, L"Camera Pos x : %f y : %f", cameraPos.x, cameraPos.y);
		DebugText = ArrText;
		TextOut(RenderMgr::BACKDC(), 10, 110, DebugText.c_str(), (int)DebugText.size());

		swprintf_s(ArrText, L"FPS : %d", Time::getFPS());
		DebugText = ArrText;
		TextOut(RenderMgr::BACKDC(), 10, 130, DebugText.c_str(), (int)DebugText.size());
		
	}
}


