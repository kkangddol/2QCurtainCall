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
	/// winapi�� �⺻ ������ �����ϴ� class
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
		bool FullScreenMode = false;//��üȭ�� ���� ���� 
		void ShowTaskBar(bool show);
	};

	static WindowSystem* ApplicationHandler = 0;
}
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM);
