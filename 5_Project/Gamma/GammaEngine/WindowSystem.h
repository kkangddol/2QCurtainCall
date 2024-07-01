#pragma once
#include <Windows.h>
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

namespace GammaEngine
{
	class Engine;
	class Time;
	/// <summary>
	/// winapi의 기본 구성을 포함하는 class
	/// </summary>
	class GammaEngineAPI WindowSystem : public Singleton<WindowSystem>
	{
	public:
		WindowSystem();
		~WindowSystem();

	public:
		LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
		void Initialize(int&, int&);
		void ShutDown();
		void Run(Engine* engine);

	public:
		static HWND hWnd;
		Time* time;

	private:
		LPCWSTR applicationName;
		HINSTANCE hInstance;
		bool FullScreenMode = false;//전체화면 조절 변수 
		void ShowTaskBar(bool show);
	};

	static WindowSystem* ApplicationHandler = 0;
}
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM);
