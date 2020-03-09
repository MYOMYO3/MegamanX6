#include "WINDOW.h"



#include <assert.h>

int Window::g_WindowCount = 0;
HINSTANCE Window::hInstance;
std::map<std::wstring, WNDCLASSEXW> Window::g_WinClassMap;  //win32윈도우클래스를 관리하는 자료구조
std::map<std::wstring, Window*>	Window::g_WinMap;	//win32윈도우 클래스를 통해서 만들어진 윈도우를 관리하는 자료구조

#pragma region STATIC MGR FUNC

LRESULT CALLBACK Window::DEFMSG(HWND _HWnd, UINT _Msg, WPARAM _WParam, LPARAM _LParam)
{
	switch (_Msg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(_HWnd, &ps);
		// Run();
		// 이걸 한번 완료하지 않으면
		// 계속 그리라고 요청한다. OS가 나한테 요청한다.
		EndPaint(_HWnd, &ps);

		break;
	}
	case WM_DESTROY:
		// GetMessage함수에서 0을 리턴하게 하는 함수일 것이다.
		//PostQuitMessage(0);

		DestroyWindow(_HWnd);
		break;
	default:
		// 너희가 정의안한걸 우리가 기본적으로 만들어놓은 방식으로
		// 메세지를 처리해 줄께... 
		return DefWindowProc(_HWnd, _Msg, _WParam, _LParam);
	}
	return 0;
}

//윈도우 기반이 되는 클래스(구조체)를 정의한다
void Window::Init(const HINSTANCE _HInstance)
{
	hInstance = _HInstance;

	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = DEFMSG;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = 0;// LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;// MAKEINTRESOURCEW(IDC_AR22API);
	wcex.lpszClassName = L"Default"; // L"AR22API"
	wcex.hIconSm = 0;// LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ASTERISK));


	CreateWindowClass(wcex);
}

void Window::AllWindowUpdate()
{
	std::map<std::wstring, Window*>::iterator StartIter = g_WinMap.begin();
	std::map<std::wstring, Window*>::iterator EndIter = g_WinMap.end();

	for (; StartIter != EndIter; ++StartIter)
	{
		StartIter->second->Update();
	}


}

Window* Window::CreateHWindow(const wchar_t* _TitleName, bool _IsShow)
{
	return CreateHWindow(L"Default", _TitleName, _TitleName, _IsShow);
}
Window* Window::CreateHWindow(const wchar_t* _WindowName, const wchar_t* _TitleName, bool _IsShow)
{
	return CreateHWindow(L"Default", _WindowName, _TitleName, _IsShow);
}
Window* Window::CreateHWindow(const wchar_t* _ClassName, const wchar_t* _WindowName, const wchar_t* _TitleName, bool _IsShow)
{
	if (g_WinMap.end() != g_WinMap.find(_WindowName))	//만들어진 윈도우가 있다면 터트린다
	{
		assert(false);

		return nullptr;
	}

	Window* newWindow = new Window();	//윈도우 객체 생성

	if (false == newWindow->Create(_ClassName, _TitleName))
	{
		assert(false);
		delete newWindow;
		return nullptr;
	}

	g_WinMap.insert(std::map<std::wstring, Window*>::value_type(_WindowName, newWindow));

	if (true == _IsShow)
	{
		newWindow->Show();
	}

	++g_WindowCount;
	return newWindow;
}

bool Window::CreateWindowClass(const WNDCLASSEXW& _wcex)
{
	if (0 == RegisterClassExW(&_wcex))  // registerclass함수의 인수로 wndclass 구조체 번지를 넘겨주면 된다.
	{									// 윈도우 클래스를 등록한 후에는 등록한 윈도우클래스를 기본으로 윈도우를 
		assert(false);					// 실제로 생성해야한다.
		return false;
	}

	g_WinClassMap.insert(std::map<std::wstring, WNDCLASSEXW>::value_type(_wcex.lpszClassName, _wcex));

	return true;
}
WNDCLASSEXW Window::FindWindowClass(const wchar_t* _Name)
{
	std::map<std::wstring, WNDCLASSEXW>::iterator FindIter = g_WinClassMap.find(_Name);

	//std::map<std::wstring, WNDCLASSEXW>::iterator endIter = g_WinClassMap.end();

	if (g_WinClassMap.end() == FindIter)
	{
		WNDCLASSEXW w;
		w.hInstance = 0;
		return w;
	}

	return FindIter->second;
}

bool Window::DestroyWindow(HWND _hWnd)
{
	//////////////////////////////////////////
	std::map<std::wstring, Window*>::iterator Loop = g_WinMap.begin();
	std::map<std::wstring, Window*>::iterator End = g_WinMap.end();

	for (; Loop != End; ++Loop)
	{
		if (Loop->second->hWnd == _hWnd)
		{
			if (nullptr != Loop->second)
			{
				delete Loop->second;
				Loop->second = nullptr;
			}

			g_WinMap.erase(Loop);
			--g_WindowCount;

			return true;
		}
	}

	return true;
}
#pragma endregion
/////////////////////////////////////////////////////////////////////////////////////
#pragma region MEMBER

bool Window::Create(const wchar_t* _ClassName, const wchar_t* _TitleName)
{
	WNDCLASSEXW FindClass = FindWindowClass(_ClassName);
#pragma region FindClass Except
	if (0 == FindClass.hInstance)
	{
		assert(false);
	}
#pragma endregion	

	style = WS_OVERLAPPEDWINDOW;
	menu = TRUE;

	if (nullptr == FindClass.lpszMenuName)
	{
		menu = FALSE;
	}

	//메모리상에 윈도우를 만든다
	hWnd = CreateWindowW(_ClassName, _TitleName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	hDc = GetDC(hWnd); //hWnd의 hDc를 멤버변수 hDc에 받는다

#pragma region Except

	if (nullptr == hWnd)
	{
		assert(false);
		return false;
	}

	if (nullptr == hDc)
	{
		assert(false);
		return false;
	}

#pragma endregion	

	return true;
}

Size Window::GetWindowSize()
{
	return winSize;
}

void Window::SetSize(int _X, int _Y)
{
	winSize.x = (float)_X;
	winSize.y = (float)_Y;

	RECT rect = { 0, 0, _X, _Y };
	AdjustWindowRect(&rect, style, menu);
	SetWindowPos(hWnd, 0, 0, 0, (rect.right - rect.left), (rect.bottom - rect.top), SWP_NOMOVE | SWP_NOZORDER);

}

void Window::SetPos(int _X, int _Y)
{
	SetWindowPos(hWnd, 0, _X, _Y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

void Window::SetSizePos(int _PosX, int _PosY, int _SizeX, int _SizeY)
{
	SetPos(_PosX, _PosY);
	SetSize(_SizeX, _SizeY);
}

void Window::Show()
{
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
}
void Window::Hide()
{
	ShowWindow(hWnd, SW_HIDE);
	UpdateWindow(hWnd);
}

void Window::Update()
{
	prevMousePos = curMousePos;
	POINT MPOS;
	GetCursorPos(&MPOS);
	ScreenToClient(hWnd, &MPOS);
	curMousePos = { (float)MPOS.x, (float)MPOS.y };
}

Pos Window::MousePos()
{
	return curMousePos;
}

Pos Window::MouseDir()
{
	return (curMousePos - prevMousePos);
}
#pragma endregion

