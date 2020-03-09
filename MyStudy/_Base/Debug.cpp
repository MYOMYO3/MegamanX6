#include "Debug.h"





void Debug::LeakCheck()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

void Debug::Update()
{

}

void Debug::Render()
{

}

void Debug::PrintText(HDC _DC, int _X, int _Y, const std::wstring _Str)
{
	std::wstring str = _Str;
	TextOutW(_DC, _X, _Y, str.c_str(), (int)str.size() );
	//TextOut(GameCore::MainWindow().GetHDC(), 100, 80, Path::FindPathToString(L"Charcter").c_str(), (int)Path::FindPathToString(L"Charcter").size());
}
