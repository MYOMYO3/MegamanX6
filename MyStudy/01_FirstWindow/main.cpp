// 01_FirstWindow.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "01_FirstWindow.h"
#include <string.h>

#define MAX_LOADSTRING 100

INT WINDOWTYPE = 2;

HINSTANCE hInst;						//현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];			//제목표시줄 텍스트
WCHAR szWindowClass[MAX_LOADSTRING];	//기본 창 클래스 이름

WCHAR szTitle2[MAX_LOADSTRING];			//제목표시줄 텍스트
WCHAR szWindowClass2[MAX_LOADSTRING];	//기본 창 클래스 이름

//wcscpy_s(szTitle2, L"adfaf");
//wcscpy_s(szWindowClass2, L"adfaf");

HINSTANCE hInst2;


//함수 선언부
ATOM MyRegisterClass(HINSTANCE );	
BOOL InitInstance(HINSTANCE , int);
BOOL InitInstance2(HINSTANCE, int);

//2번째 윈도우
ATOM MyRegisterClass2(HINSTANCE);

	//CALLBACK = __stdcall
	//이 호출규약은 일반적으로 전역함수에 사용되며
	//그중에서 대표적인 예는 class내부 static멤버함수가 이 호출규약을 사용한다.
	//전역함수 포인터등을 만들때 void(*ptr)(int, int);
	//전역함수 포인터등을 만들때 void __stdcall (*ptr)(int, int);


//CALLBACK이 붙어있다면 이함수는 어떤 함수나 객체가 대신 실행해주는 용도이다.
LRESULT CALLBACK MYMSG(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);


LRESULT CALLBACK MYMSG2(HWND, UINT, WPARAM, LPARAM);
	//진입점을 변경했다.
	//main을 숨기는 방법과
	//컴파일러 옵션을 세팅해서
	//int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine,_in_ int nCmdShow)


	/// Handling의 원리
	//int* pData = new int();
	//int* Arr[100] = { pData ,};
	//void IntSetData(int _Handle, int Value) 
	//{
	//	(*Arr[_Handle]) = Value;
	//}

	//메인이 달라진다.
	//window 버전에 따라서 약간 뭔가 달리즌 ㄴ것으로 알고있는데
	//몇가지가 정의되어있다.


	// 핸들 방식이란.
	// 핸들 방식에 대해서 이해해보자.
	// HINSTANCE hInstance 
	// 윈도우에서 우리에게 지원하는 프로그램 그자체의 핸들.
	// 윈도우에 등록된 우리 프로그램의 등록증을 준다.

	// 사용하지 않는 변수에 대한 경고를 지워주는 매크로 
	// UNREFERENCED_PARAMETER 
	// UNREFERENCED_PARAMETER(hPrevInstance);
	// UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	// HINSTANCE hInstance 내 프로그램에서 다른 프로그램을 실행하거나
	// 하는 등의 동작을 할때.

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDS_APP_TITLE, szWindowClass, MAX_LOADSTRING);



	MyRegisterClass(hInstance);
	MyRegisterClass2(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	if (!InitInstance2(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY01FIRSTWINDOW));
	//액셀러레이터(Accelerator)는 아주 쉽게 말해서 단축키이다.아래 한글을 예로 든다면 Alt + L을 누르면 문자 꾸미기 기능, 
	//Ctrl + P를 누르면 프린터 설정 기능이 곧바로 실행되도록 하는 키보드 조합키를 말한다.그런데 왜 단축키라는 말을 쓰지 않고 어렵게시리 영어를 쓰는가 하면 
	//윈도우즈에서 단축키(ShortCut)라는 말은 다른 의미로 사용되고 있기 때문이다.
	//메뉴 이름에 &를 넣어 Alt키와 함께 사용하는 키를 단축키라고 하며 여기서 말하는 액셀러레이터와는 의미가 조금 다르다.
	//단축키는 반드시 Alt키와 함께 사용해야 하며 메뉴에 있는 항목을 키보드로 선택하는 빠른 방법이지만 
	//액셀러레이터는 메뉴와 상관없이 언제든지 사용할 수 있다는 점에 있어서 차이가 있다.
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

// 창 클래스를 등록하는 함수
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	// 윈도우의 형태를 정의해서 Window10 한테 넘긴다.
	// 나 이런 윈도우의 형태를 띄우고 싶은데 띄울수 있엉?
	// 띄울수 있다면 OK 싸인을 날려준다.

	// CreateCursor()

	// 넘겨줘야할 데이터 구조를 구조체로 넘겨준다.

	//넘겨줘야할 데이터 구조를 구조체를 넘겨준다.
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEXW);		//구조체의 크기를 저장하는 멤버
	wcex.style = CS_HREDRAW | CS_VREDRAW;	//윈도우의 스타일을 지정한다.
	wcex.lpfnWndProc = MYMSG;	//lpfnWndProc 멤버는 메세지 처리함수를 지정한다. 여기서 CALLBACK함수를 넘겨준다.
	wcex.cbClsExtra = 0;	//일종의 예약영역이다 윈도우즈가 내부적으로 사용하며 아주 특수한 목적에 사용되는
	wcex.cbWndExtra = 0;	//여유공간이다. 사용하지않을경우 0으로 지정한다.
	wcex.hInstance = hInstance;	//이 윈도우 클래스를 사용하는 프로그램의 번호이며 이 값은 WinMain의 인수로 전달된 hInstance값을 그대로 대입해주면 된다.
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ASTERISK)); //아이콘의 모양결정 0을넘으면 디폴트아이콘
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); //커서모양
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); //화면 백그라운드 
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY01FIRSTWINDOW); //이프로그램의 사용할 메뉴를 지정한다 메뉴는 프로그램코드에서 만드는것이 아니라 리소스 에디터에 의해 별도
															  //로 만들어진후 링크시에 같이 합쳐진다 메뉴를 사용하지않을경우 이 멤버에 NULL을 넣어준다.

	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ASTERISK));


	return RegisterClassExW(&wcex);
}

ATOM MyRegisterClass2(HINSTANCE hInstance)
{	
	WNDCLASSEXW wcex;
	wcex.cbSize = sizeof(WNDCLASSEXW);		//구조체의 크기를 저장하는 멤버
	wcex.style = CS_HREDRAW | CS_VREDRAW;	//윈도우의 스타일을 지정한다.
	wcex.lpfnWndProc = MYMSG2;	//lpfnWndProc 멤버는 메세지 처리함수를 지정한다. 여기서 CALLBACK함수를 넘겨준다.
	wcex.cbClsExtra = 0;	//일종의 예약영역이다 윈도우즈가 내부적으로 사용하며 아주 특수한 목적에 사용되는
	wcex.cbWndExtra = 0;	//여유공간이다. 사용하지않을경우 0으로 지정한다.
	wcex.hInstance = hInstance;	//이 윈도우 클래스를 사용하는 프로그램의 번호이며 이 값은 WinMain의 인수로 전달된 hInstance값을 그대로 대입해주면 된다.
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY01FIRSTWINDOW)); //아이콘의 모양결정 0을넘으면 디폴트아이콘
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW); //커서모양
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); //화면 백그라운드 
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY01FIRSTWINDOW); //이프로그램의 사용할 메뉴를 지정한다 메뉴는 프로그램코드에서 만드는것이 아니라 리소스 에디터에 의해 별도
															  //로 만들어진후 링크시에 같이 합쳐진다 메뉴를 사용하지않을경우 이 멤버에 NULL을 넣어준다.

	wcex.lpszClassName = L"window2";//szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));


	return RegisterClassExW(&wcex);
}

//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//   이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//   주 프로그램 창을 만든 다음 표시합니다.
//

//HINSTANCE는 프로그램의 인스턴스 식별자(핸들)을 의미합니다.
//
//간단히 말씀드리자면 실행파일 형태로 껍데기에 불과한 프로그램이 메모리에 실제로
//
//구현된 실체를 뜻합니다.
//
//따라서 만약에 프로그램을 여러개 실행시켰을 때 이들의 각각을 프로그램 인스턴스라고
//
//하고 실행되는 프로그램마다 고유한 값을 갖고
//
//실행중인 프로그램들을 구분하기 위한 식별값으로 인스턴스 핸들을 이용합니다.
//
//
//
//HWND는 프로그램의 윈도우 식별자(핸들)를 의미하는데 해당 프로그램의 윈도우들을
//
//구분하기 위한 식별 값을 말합니다.여기서 윈도우와 프로그램과는 차이가 있습니다.
//
//윈도우 프로그래밍에서 하나의 프로그램에는 많은 윈도우들을 가질수 있기 때문입니다.
//
//프로그램의 윈도우 핸들 중에서 대표적인 것이 부모 윈도우의 핸들입니다.따라서 대부분의
//
//윈도우 프로그래밍의 작업과정중 대부분은 이들 HWND 값을 통해 얻은 윈도우 핸들을
//
//이용한다고 이해하시면 빠를꺼 같습니다.창뿐만 아니라 여러가지 수많은 컨트롤 등도 모두
//
//윈도우로 생성시에 핸들값을 소유하고 있는 존재이기 때문입니다.


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance;

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}
BOOL InitInstance2(HINSTANCE hInstance, int nCmdShow)
{
	hInst2 = hInstance;

	HWND hWnd = CreateWindowW(L"window2" , szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK MYMSG(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// 메뉴 선택을 구문 분석합니다:
			switch (wmId)
			{
			case IDM_ABOUT:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;

	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			// 그리기 위한 권한 핸들.
			HDC hdc = BeginPaint(hWnd, &ps);

			Rectangle(hdc, 0, 0, 100, 100);

			// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
			EndPaint(hWnd, &ps);
		}
		break;

	case WM_DESTROY:
		WINDOWTYPE--;
		if (WINDOWTYPE == 0)
		{
			PostQuitMessage(0);
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

LRESULT CALLBACK MYMSG2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst2, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:

			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		// 그리기 위한 권한 핸들.
		HDC hdc = BeginPaint(hWnd, &ps);

		//Rectangle(hdc, 0, 0, 100, 100);

		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		EndPaint(hWnd, &ps);
	}
	break;

	case WM_DESTROY:


		WINDOWTYPE--;
		if (WINDOWTYPE == 0)
		{
			PostQuitMessage(0);
		}		
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}