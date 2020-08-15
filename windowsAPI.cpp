#include "stdafx.h"
#include "playGround.h"

//API : Application Programming Interface

HINSTANCE _hInstance;
HWND	  _hWnd;
HDC		  _hdc;
LPCTSTR _lpszClass = TEXT("프레임워크 테스트");

POINT _ptMouse;

playGround _pg;


//함수 프로토타입 선언
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowsSize(int x, int y, int width, int height);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int cmdShow)
{
	MSG			message;	//윈도우 메시지를 담은 구조체
	WNDCLASS	wndClass;	//윈도우 클래스 구조체

	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = WINNAME;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);
	//_hWnd = CreateWindow(
	//	WINNAME,
	//	WINNAME,
	//	WS_OVERLAPPEDWINDOW,
	//	WINSTARTX,
	//	WINSTARTY,
	//	WINSIZEX,
	//	WINSIZEY,
	//	NULL,
	//	(HMENU)NULL,
	//	hInstance,
	//	NULL
	//);
	_hWnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		WINNAME,
		WINNAME,
		WS_POPUP,
		0,
		0,
		GetSystemMetrics(SM_CXSCREEN),
		GetSystemMetrics(SM_CYSCREEN),
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);

	setWindowsSize(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CXSCREEN));

	ShowWindow(_hWnd, cmdShow);

	//초기화 호출
	if (FAILED(_pg.init()))
	{
		return 0;
	}

	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{

			if (message.message == WM_QUIT) break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			//우선 60프레임으로 둔다
			TIMEMANAGER->update(60);
			_pg.update();
			_pg.render();
		}
	}


	_pg.release();

	return message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _pg.MainProc(hWnd, iMessage, wParam, lParam);
}

//클라이언트 영역 재조정
void setWindowsSize(int x, int y, int width, int height)
{
	RECT winRect;

	winRect.left = 0;
	winRect.top = 0;
	winRect.right = width;
	winRect.bottom = height;

	AdjustWindowRect(&winRect, WINSTYLE, false);

	//실질적으로 클라이언트 영역 크기 셋팅 해주는 함수
	SetWindowPos(_hWnd, NULL, x, y,
		(winRect.right - winRect.left),
		(winRect.bottom - winRect.top),
		SWP_NOZORDER | SWP_NOMOVE);
}