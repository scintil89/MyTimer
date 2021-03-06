// timer.cpp: 응용 프로그램의 진입점을 정의합니다.
//
// testwindow.cpp: 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include "timer.h"
#include "MyTimer.h"
#include <memory>


#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            //  기본 창 클래스 이름입니다.

int width;
int height;

MyTime* myt = nullptr;
												// 이 코드 모듈에 들어 있는 함수의 정방향 선언입니다.
ATOM                MyRegisterClass(HINSTANCE hInstance);
HWND                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void DrawWindow(HDC hdc);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 여기에 코드를 입력합니다.

	//타이머 생성
	myt = new MyTime();

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_TIMER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 응용 프로그램 초기화를 수행합니다.

	auto hWnd = InitInstance(hInstance, nCmdShow);

	if (!hWnd)
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TIMER));

	MSG msg;

	// 기본 메시지 루프입니다.
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				//myt release
				if (myt)
				{
					delete myt;
					myt = nullptr;
				}
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (myt->isRun == true)
			{
				myt->ProcessTime();

				auto dt = myt->GetElapsedTime(); 
				
				myt->Process(dt);

			}

			HDC		hdc = GetDC(hWnd);
			DrawWindow(hdc);
			ReleaseDC(hWnd, hdc);
		}
	}

	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  목적: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_TIMER));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_TIMER);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   목적: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   설명:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
HWND InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindowEx(WS_EX_APPWINDOW, szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, TIMER_W, TIMER_H, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	//get width, height
	RECT rect;
	if (GetClientRect(hWnd, &rect))
	{
		width = rect.right - rect.left;
		height = rect.bottom - rect.top;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  목적:  주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 응용 프로그램 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		//TODO : 다른곳으로 옮기기??
		CreateWindow(TEXT("button"), TEXT("H ↑"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, TIMER_W / 6 * 2, TIMER_H / 6, 50, 25, hWnd, (HMENU)BUTTON_HUP, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("H ↓"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, TIMER_W / 6 * 2, TIMER_H / 6 * 5, 50, 25, hWnd, (HMENU)BUTTON_HDOWN, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("M ↑"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, TIMER_W / 6 * 3, TIMER_H / 6, 50, 25, hWnd, (HMENU)BUTTON_MUP, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("M ↓"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, TIMER_W / 6 * 3, TIMER_H / 6 * 5, 50, 25, hWnd, (HMENU)BUTTON_MDOWN, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("S ↑"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, TIMER_W / 6 * 4, TIMER_H / 6, 50, 25, hWnd, (HMENU)BUTTON_SUP, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("S ↓"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, TIMER_W / 6 * 4, TIMER_H / 6 * 5, 50, 25, hWnd, (HMENU)BUTTON_SDOWN, hInst, NULL);
		
		CreateWindow(TEXT("button"), TEXT("RESET"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, TIMER_W / 6 * 1, TIMER_H / 6 * 3, 80, 40, hWnd, (HMENU)BUTTON_RESET, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("START"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, TIMER_W / 6 * 5, TIMER_H / 6 * 2, 80, 40, hWnd, (HMENU)BUTTON_START, hInst, NULL);
		CreateWindow(TEXT("button"), TEXT("STOP"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, TIMER_W / 6 * 5, TIMER_H / 6 * 4, 80, 40, hWnd, (HMENU)BUTTON_STOP, hInst, NULL);

		break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다.
		switch (wmId)
		{
		case BUTTON_HUP:
			{
				OutputDebugStringW(L"testestsetsettsets");
				myt->AddHr(1);
			}
			break;
		case BUTTON_HDOWN:
			{
				myt->MinusHr(1);
			}
			break;
		case BUTTON_MUP:
			{
				myt->AddMin(1);
			}
			break;
		case BUTTON_MDOWN:
			{
				myt->MinusMin(1);
			}
			break;
		case BUTTON_SUP:
			{
				myt->AddSec(1);
			}
			break;
		case BUTTON_SDOWN:
			{
				myt->MinusSec(1);
			}
			break;
		case BUTTON_START:
			{
				OutputDebugStringW(L"BUTTON_START dbg string\n");
				myt->Start();
			}
			break;
		case BUTTON_STOP:
			{
				OutputDebugStringW(L"BUTTON_START dbg string\n");
				myt->Stop();
			}
			break;
		case BUTTON_RESET:
			{
				myt->Reset();
			}
			break;

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
		HDC hdc = BeginPaint(hWnd, &ps);
		DrawWindow(hdc);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
	break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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

void DrawWindow(HDC hdc)
{
	SetTextAlign(hdc, TA_CENTER);

	HFONT myFont = CreateFont(70, 0, 0, 0, 10, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"궁서체");
	HFONT oldFont = (HFONT)SelectObject(hdc, myFont); //memoryDC?

	wchar_t time[255];
	wsprintf(time, L"%2d : %2d : %2d", myt->GetHr(), myt->GetMin(), myt->GetSec());

	TextOut(hdc, width / 2, height / 2, time, wcslen(time));

	SelectObject(hdc, oldFont);

	DeleteObject(myFont);
	DeleteObject(oldFont);
}
