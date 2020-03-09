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
	//g_MainWindow->SetSize(1280, 800);//�ް��� �̹��� ���� �״�λ���ϱ����� ������
	g_MainWindow->SetSize(645, 480);//�ް��� �̹��� ���� �״�λ���ϱ����� ������
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
	// �⺻ �޽��� �����Դϴ�:
	while (0 != Window::WindowCount())
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) //PeekMessage ������ �޼�����ȭ�� ������ FALSE�� ��ȯ���ش�
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			// �� ������ ������
			int a = 0;
			Run();
		}
	}

	 Sound::End();
	return msg;
}

void GameCore::Run()
{
	// ������ Ŭ������ �������ϴ� 
	// ���� �����ӿ�ũ�� �ٽɿ��
	// 1. �ð� (��ŸŸ���̶�� ���� ���س���.)
	// 2. �ܺ��Է�
	// 3. ������Ʈ(���� ���ӿ��� �����ϴ� ��ҵ��� ��üȭ ���)
	// 4. ������(�ִϸ��̼�)
	// 5. �浹(��ȣ�ۿ�)
	// 6. ����
	Time ::Update();
	Input::Update();
	Window::AllWindowUpdate();
	 Sound::Update();
	
	SceneMgr::Inst().Progress();
}


void GameCore::End()
{
	
}