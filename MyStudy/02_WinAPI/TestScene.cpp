#include "stdafx.h"
#include "TestScene.h"
#include "GAMECORE.h"
#include "sceneMgr.h"
#include "Player.h"
#include "Bat.h"
#include <Path.h>
#include <JTIME.h>
#include "Map.h"
#include "RenderMgr.h"
#include "Asset.h"
#include "CollisionMgr.h"
#include "BGImage.h"
#include "MonsterMgr.h"
#include "TransRender.h"
#include "Actor.h"
#include "Cursor.h"

#include <commdlg.h>
#include <Directory.h>
#include <Input.h>
#include <Windows.h>
#include <WINDOW.h>
#include <IO.h>
#include <Debug.h>


Map*		editorMap = nullptr;
Cursor*		mouseCursor = nullptr;

TestScene::TestScene() : overSaveCheck(0)
{
}


TestScene::~TestScene()
{
}


bool TestScene::Loading()
{
	editorMap = Actor::CreateActor<Map>(L"Map");
	editorMap->PossibleOverScene(L"TestScene");
		   
	monsterSprite	= Asset::FIndSprite(L"Bat.bmp");
	mouseCursor		= Actor::CreateActor<Cursor>(L"Cursor");


	return true;
}

void TestScene::SceneUpdate()
{
	if (0 != GetAsyncKeyState('2'))
	{
		SceneMgr::Inst().ChangeScene(L"Title");
	}

#pragma region KEY
	if (true == Input::Press(L"UP"))
	{
		cameraPos.y -= 500.0f * Time::DeltaTime();
	}
	if (true == Input::Press(L"DOWN"))
	{
		cameraPos.y += 500.0f * Time::DeltaTime();
	}
	if (true == Input::Press(L"LEFT"))
	{
		cameraPos.x -= 500.0f * Time::DeltaTime();
	}
	if (true == Input::Press(L"RIGHT"))
	{
		cameraPos.x += 500.0f * Time::DeltaTime();
	}

	if (0 != GetAsyncKeyState(VK_F8))
	{
		Debug::Inst().On();
	}
	if (0 != GetAsyncKeyState(VK_F7))
	{
		Debug::Inst().Off();
	}

	if (true == Input::Down(L"MLB"))
	{
		MonsterMgr::Inst().CreateMonster(monsterType, GameCore::MainWindow().MousePos() + (cameraPos));
	}

	if (true == Input::Down(L"MONTYPEUP"))
	{
		if (monsterType < MONSTERTYPE::TYPEMAX - 1 && monsterType >= 0)
		{
			++monsterType;


			std::wstring name = monsterImgName[monsterType];
			monsterSprite = Asset::FIndSprite(name.c_str());
		}
	}
	if (true == Input::Down(L"MONTYPEDOWN"))
	{
		if (monsterType < MONSTERTYPE::TYPEMAX && monsterType > 0)
		{
			--monsterType;

			std::wstring name = monsterImgName[monsterType];
			monsterSprite = Asset::FIndSprite(name.c_str());
		}
	}

	mouseCursor->SetPos(GameCore::MainWindow().MousePos() + (cameraPos));
#pragma endregion
	

#pragma region FILEIO DIALLOG
	if (true == Input::Down(L"SAVE"))
	{
		if (overSaveCheck > 0)
		{
			//MonsterMgr::Inst().MonsterClear();
			overSaveCheck = 0;
		}
		++overSaveCheck;	

		OPENFILENAME ofn;
		TCHAR szFile[260] = { 0 };
		Directory directory = Path::FindPathDir(L"DATA");

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = GameCore::MainWindow().GetHWnd();
		ofn.lpstrInitialDir = directory.FullPath();
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = L"MAPDATA\0*.MAPDATA\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
		// ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (GetSaveFileName(&ofn) == TRUE)
		{
			std::wstring FilePath = ofn.lpstrFile;

			int a = (int)FilePath.find(L".MAPDATA");

			if (-1 == (int)FilePath.find(L".MAPDATA"))
			{
				FilePath += L".MAPDATA";
			}

			MonsterMgr::Inst().SaveData(ofn.lpstrFile);
			//editorMap->Save(FilePath.c_str());
		}
	}
	if (true == Input::Down(L"LOAD"))
	{
		OPENFILENAME ofn;       // common dialog box structure
		TCHAR szFile[260] = { 0 };       // if using TCHAR macros

		Directory directory = Path::FindPathDir(L"DATA");
		// Initialize OPENFILENAME
		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = GameCore::MainWindow().GetHWnd();
		ofn.lpstrInitialDir = directory.FullPath();
		ofn.lpstrFile = szFile;
		ofn.nMaxFile = sizeof(szFile);
		ofn.lpstrFilter = L"MAPDATA\0*.MAPDATA\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
		// ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		if (GetOpenFileName(&ofn) == TRUE)
		{
			MonsterMgr::Inst().LoadData(ofn.lpstrFile);
			//editorMap->Load(ofn.lpstrFile);
		}
	}
#pragma endregion
}


void TestScene::DebugRender()
{
		std::wstring key = L" 몬스터 종류변경 : K L";
		TextOut(RenderMgr::BACKDC(), 10, 10, key.c_str(), (int)key.size());

		std::wstring DebugText = L"EDITOR MAP";
		TextOut(RenderMgr::BACKDC(), 10, 30, DebugText.c_str(), (int)DebugText.size());

		wchar_t ArrText[256];
		swprintf_s(ArrText, L"Mouse Pos  x : %f y : %f", GameCore::MainWindow().MousePos().x, GameCore::MainWindow().MousePos().y);
		DebugText = ArrText;
		TextOut(RenderMgr::BACKDC(), 10, 50, DebugText.c_str(), (int)DebugText.size());

		swprintf_s(ArrText, L"Map Pos x : %f y : %f", cameraPos.x, cameraPos.y);
		DebugText = ArrText;
		TextOut(RenderMgr::BACKDC(), 10, 70, DebugText.c_str(), (int)DebugText.size());
		
		Rectangle(RenderMgr::BACKDC(), 
			550,
			10 ,
			640,
			110);

		if (monsterType == MONSTERTYPE::BOSS)
		{
			TransparentBlt(
				RenderMgr::BACKDC(),
				500,
				-20,
				200,
				200,
				monsterSprite->GetImage()->GetDC(),
				(*monsterSprite)[14].pos.IX(),
				(*monsterSprite)[14].pos.IY(),
				(*monsterSprite)[14].size.IX(),
				(*monsterSprite)[14].size.IY(),
				MAGENTA
			);

			return;
		}

		TransparentBlt(
			RenderMgr::BACKDC(),
			500	,
			-20 ,
			200 ,
			200 ,
			monsterSprite->GetImage()->GetDC(), 
			(*monsterSprite)[0].pos.IX(),
			(*monsterSprite)[0].pos.IY(),
			(*monsterSprite)[0].size.IX(),
			(*monsterSprite)[0].size.IY(),
			MAGENTA
		);	
}