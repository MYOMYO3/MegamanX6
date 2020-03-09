#include "stdafx.h"
#include "GAMECORE.h"
#include <JTIME.h>
#include <Input.h>
#include <Sound.h>
#include <GEOMETRY.h>
#include "SceneMgr.h"
#include "TitleScene.h"
#include "TestScene.h"
#include "Stage01.h"
#include "Select.h"
#include "EndScene.h"
#include <Path.h>
#include "RenderMgr.h"

Window* GameCore::g_MainWindow = nullptr;

Window& GameCore::MainWindow()
{
	return (*g_MainWindow);
}

GameCore::GameCore()
{

}


GameCore::~GameCore()
{
		
}




void GameCore::Start()
{	
	Sound::Init();

#pragma region DIRECTORY
	Directory	dic = Path::GetRootDir();
	dic.ReplaceParentPath();
	dic.Move(L"_BIN");
#pragma endregion

#pragma region CREATE PATH
	Path::SetRootDir(dic);
	Path::CreatePath(L"DATA",		L"DATA");	
	Path::CreatePath(L"Sprite",		L"Sprite");
	Path::CreatePath(L"Sound",		L"Sound");
	Path::CreatePath(L"Select",		L"Sprite\\Select");
	Path::CreatePath(L"UI",			L"Sprite\\UI");
	Path::CreatePath(L"Title",		L"Sprite\\Title");	
	Path::CreatePath(L"Charcter",	L"Sprite\\charcter");
	Path::CreatePath(L"Monster",	L"Sprite\\Monster");
	Path::CreatePath(L"Map",		L"Sprite\\Map");
	Path::CreatePath(L"StageObject",L"Sprite\\StageObject");
#pragma endregion
	   
#pragma region CREATE WINDOW
	g_MainWindow = Window::CreateHWindow(L"MainWindow");
	//g_MainWindow->SetSize(1280, 800);//메가맨 이미지 파일 그대로사용하기위한 사이즈
	g_MainWindow->SetSize(645, 480);//메가맨 이미지 파일 그대로사용하기위한 사이즈
#pragma endregion
		   
#pragma region CREATE SCENE
	SceneMgr::Inst().CreateScene<TitleScene>(L"Title");
	SceneMgr::Inst().CreateScene<Select>(L"Select");
	SceneMgr::Inst().CreateScene<Stage01>(L"Stage01");
	SceneMgr::Inst().CreateScene<EndScene>(L"End");
	SceneMgr::Inst().CreateScene<TestScene>(L"TestScene");

	SceneMgr::Inst().ChangeScene(L"Title");
#pragma endregion		
}



MSG GameCore::Loop()
{
	Time::Reset();	
	RenderMgr::Inst().Init();
	MSG msg;
	// 기본 메시지 루프입니다:
	while (0 != Window::WindowCount())
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) //PeekMessage 윈도우 메세지변화가 없으면 FALSE를 반환해준다
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// 내 게임을 돌릴곳
			int a = 0;
			Run();
		}
	}

	 Sound::End();
	return msg;
}

void GameCore::Run()
{
	// 앞으로 클리어해 나가야하는 
	// 게임 프레임워크의 핵심요소
	// 1. 시간 (델타타임이라는 것을 구해낸다.)
	// 2. 외부입력
	// 3. 오브젝트(구조 게임에서 등장하는 요소들의 객체화 방법)
	// 4. 랜더링(애니메이션)
	// 5. 충돌(상호작용)
	// 6. 사운드
	Time ::Update();
	Input::Update();
	Window::AllWindowUpdate();
	 Sound::Update();
	
	SceneMgr::Inst().Progress();
}


void GameCore::End()
{
	
}