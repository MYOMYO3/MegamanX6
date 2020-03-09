#pragma once
#include <WINDOW.h>


class GameCore
{
friend int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow);

private:
	static Window* g_MainWindow;

public:
	static Window& MainWindow();

private:	
	static void Run();


	//////////GAME  ///////
	static void Start();
	static  MSG Loop();
	static void End();

private:
	//Scene MGR

public:
	//title
	//Play
	//Ending

	//void ChangeScene(const wchar_t* _Name);

private:
	GameCore();
	~GameCore();
};

