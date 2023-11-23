#include "Prev.h"
#include "SoundManager.h"


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR	  lpCmdLine,
	_In_ int nCmdShow)
{
	HWND hWnd;
	MSG	msg = {};
	WNDCLASS wc;


	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"FMOD_Test";

	/// 윈도우 클래스 등록한다
	RegisterClass(&wc);

	/// 윈도우 생성한다
	hWnd = CreateWindow(L"FMOD_Test", L"FMOD_Test", WS_OVERLAPPEDWINDOW, 100, 100, 1200, 1000, NULL, NULL, hInstance, NULL);

	if (!hWnd) return FALSE;

	// 사운드 시스템 초기화
	SoundManager::Instance().SystemInitialize();
	// 사운드 생성
	SoundManager::Instance().CreateLoopSound("Maintheme_666.ogg", 0);
	SoundManager::Instance().CreateLoopReverbSound("singing.wav", 1);
	SoundManager::Instance().CreateReverb();
	SoundManager::Instance().SetProperties(1);
	SoundManager::Instance().SetReverbVector(0, 0, 0);
	
	// 사운드 재생
	//SoundManager::Instance().PlaySounds(0, 0);
	SoundManager::Instance().PlayReverbSounds(1, 1);


	/// 생성된 윈도우를 화면에 표시한다
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&msg);
		}
		else
		{
			// 리버브 생성
			SoundManager::Instance().KeyUpdate();
			SoundManager::Instance().system_->update();
			SoundManager::Instance().system2_->update();
		}
	}
	SoundManager::Instance().SystemFinalize();

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT ps;

	switch (message)
	{
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}