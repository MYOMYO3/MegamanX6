#pragma once
#include <map>
#include <string>
#include <Windows.h>
#include "GEOMETRY.h"

class Window
{
private:
	static HINSTANCE		hInstance; //프로그램의 인스턴스 핸들
	static int				g_WindowCount; //생성된 윈도의 갯수	

	static std::map<std::wstring, WNDCLASSEXW> g_WinClassMap;  //win32윈도우클래스를 관리하는 자료구조
	static std::map<std::wstring, Window*>	   g_WinMap;	   //win32윈도우 클래스를 통해서 만들어진 윈도우를 관리하는 자료구조

public:
	static int WindowCount()	//윈도우 갯수를 바노한하는 함수
	{
		return g_WindowCount;
	}

public:
	static void    Init(const HINSTANCE _HInstance); // WINDOW 클래스 초기화 함수
	static LRESULT CALLBACK DEFMSG(HWND _HWnd, UINT _Msg, WPARAM _WParam, LPARAM _LParam); //메세지 정의 함수

public:
	static bool CreateWindowClass(const WNDCLASSEXW& _wcex);  //win32윈도우클래스를 생성 하는 함수
	static WNDCLASSEXW FindWindowClass(const wchar_t* _Name); //win32윈도우클래스를 찾는 클래스 g_WinClassMap에 등록된 클래스를 찾아준다

	static Window* CreateHWindow(const wchar_t* _TitleName, bool _IsShow = true);														 //
	static Window* CreateHWindow(const wchar_t* _WindowName, const wchar_t* _TitleName, bool _IsShow = true);							 //
	static Window* CreateHWindow(const wchar_t* _ClassName, const wchar_t* _WindowName, const wchar_t* _TitleName, bool _IsShow = true); //윈도우 객체를 생성하는 클래스

	static bool DestroyWindow(HWND hWnd); // 윈도우 객체 파괴

	static void AllWindowUpdate();

private:
	HWND	hWnd; //윈도우  핸들
	HDC		hDc;  //DC(Device Context)란 출력 필요한 모든 정보를 가지는 데이터 구조체이며 GDI모듈에 의해 관리된다.	
	int		style; //윈도우 스타일 
	int		menu;  //윈도우 메뉴
	Size	winSize; //d윈도우 사이즈

	Pos		curMousePos;
	Pos		prevMousePos;

public:
	HWND GetHWnd() const
	{
		return hWnd;
	}

	HDC GetHDC() const
	{
		return hDc;
	}

private:
	bool Create(const wchar_t* _ClassName, const wchar_t* _TitleName); //등록된 윈도우 클래스를 사용하여 메모리상에 윈도우를 만드는 함수

public:
	Size GetWindowSize();
	void SetSize(int _X, int _Y);
	void SetPos(int _X, int _Y);
	void SetSizePos( int _PosX, int _PosY, int _SizeX, int _SizeY); //사이즈와 포지션을 변경하는 함수

	void Show(); //윈도우를 보여주는함수
	void Hide(); 

	void Update();

	Pos MousePos();
	Pos MouseDir();

public:
	Window() : hWnd(nullptr) , hDc(nullptr) {};
	~Window() {};
};

