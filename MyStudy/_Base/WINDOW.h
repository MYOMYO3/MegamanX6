#pragma once
#include <map>
#include <string>
#include <Windows.h>
#include "GEOMETRY.h"

class Window
{
private:
	static HINSTANCE		hInstance; //���α׷��� �ν��Ͻ� �ڵ�
	static int				g_WindowCount; //������ ������ ����	

	static std::map<std::wstring, WNDCLASSEXW> g_WinClassMap;  //win32������Ŭ������ �����ϴ� �ڷᱸ��
	static std::map<std::wstring, Window*>	   g_WinMap;	   //win32������ Ŭ������ ���ؼ� ������� �����츦 �����ϴ� �ڷᱸ��

public:
	static int WindowCount()	//������ ������ �ٳ����ϴ� �Լ�
	{
		return g_WindowCount;
	}

public:
	static void    Init(const HINSTANCE _HInstance); // WINDOW Ŭ���� �ʱ�ȭ �Լ�
	static LRESULT CALLBACK DEFMSG(HWND _HWnd, UINT _Msg, WPARAM _WParam, LPARAM _LParam); //�޼��� ���� �Լ�

public:
	static bool CreateWindowClass(const WNDCLASSEXW& _wcex);  //win32������Ŭ������ ���� �ϴ� �Լ�
	static WNDCLASSEXW FindWindowClass(const wchar_t* _Name); //win32������Ŭ������ ã�� Ŭ���� g_WinClassMap�� ��ϵ� Ŭ������ ã���ش�

	static Window* CreateHWindow(const wchar_t* _TitleName, bool _IsShow = true);														 //
	static Window* CreateHWindow(const wchar_t* _WindowName, const wchar_t* _TitleName, bool _IsShow = true);							 //
	static Window* CreateHWindow(const wchar_t* _ClassName, const wchar_t* _WindowName, const wchar_t* _TitleName, bool _IsShow = true); //������ ��ü�� �����ϴ� Ŭ����

	static bool DestroyWindow(HWND hWnd); // ������ ��ü �ı�

	static void AllWindowUpdate();

private:
	HWND	hWnd; //������  �ڵ�
	HDC		hDc;  //DC(Device Context)�� ��� �ʿ��� ��� ������ ������ ������ ����ü�̸� GDI��⿡ ���� �����ȴ�.	
	int		style; //������ ��Ÿ�� 
	int		menu;  //������ �޴�
	Size	winSize; //d������ ������

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
	bool Create(const wchar_t* _ClassName, const wchar_t* _TitleName); //��ϵ� ������ Ŭ������ ����Ͽ� �޸𸮻� �����츦 ����� �Լ�

public:
	Size GetWindowSize();
	void SetSize(int _X, int _Y);
	void SetPos(int _X, int _Y);
	void SetSizePos( int _PosX, int _PosY, int _SizeX, int _SizeY); //������� �������� �����ϴ� �Լ�

	void Show(); //�����츦 �����ִ��Լ�
	void Hide(); 

	void Update();

	Pos MousePos();
	Pos MouseDir();

public:
	Window() : hWnd(nullptr) , hDc(nullptr) {};
	~Window() {};
};

