// FirstD2D.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//
#include <windows.h>

#include "Core.h"
#include "InputSystem.h"
#include "RenderSystem.h"

#include "ClientCore.h"

#define CLASSNAME L"CurtainCallMapEditor"
#define WINDOWNAME L"CurtainCall MapEditor"

// 전역 변수:
HINSTANCE g_hInst;                                // 현재 인스턴스입니다.
//WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
//WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
HWND g_hWnd;
const int g_WindowWidth = 1920;                           // 윈도우 너비
const int g_WindowHeight = 1000;                           // 윈도우 높이

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

Core g_engine;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    MyRegisterClass(hInstance);

    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

	RECT rect;
	GetClientRect(g_hWnd, &rect);

    Core engine;
    engine.Initialize(g_hWnd , rect.right - rect.left, rect.bottom - rect.top);

    ClientCore client;
    client.Initialize(rect.right - rect.left, rect.bottom - rect.top);

    MSG msg;

    // 기본 메시지 루프입니다:
    while (1)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                break;
            }

            DispatchMessage(&msg);
        }
        else
        {
            engine.CycleOnce();
        }
    }

    //engine.Finalize();

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = NULL;
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL; // MAKEINTRESOURCEW(IDC_FIRSTD2D);
    wcex.lpszClassName  = CLASSNAME;
    wcex.hIconSm        = NULL;

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   g_hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   g_hWnd = CreateWindowW(CLASSNAME, WINDOWNAME, WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, CW_USEDEFAULT, g_WindowWidth, g_WindowHeight, nullptr, nullptr, hInstance, nullptr);

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    RenderSystem& renderSystem = RenderSystem::Instance();

    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
	case WM_SIZE:
        if (!renderSystem.GetGraphicModule())
        {
            break;
        }

		RECT rect;
		//GetWindowRect(g_hWnd, &rect);
		GetClientRect(g_hWnd, &rect);
        renderSystem.Resize(rect.right - rect.left, rect.bottom - rect.top);
		g_engine.Resize(rect.right - rect.left, rect.bottom - rect.top);
        break;
	case WM_MOUSEWHEEL:
		InputSystem::mouseScrollDelta = (SHORT)HIWORD(wParam);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

