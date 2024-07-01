#pragma once
#pragma comment(lib, "xinput.lib")
#include <Xinput.h>

/// <summary>
/// xBox 패드의 라이프 사이클 및 최대 4개의 패드 관리
/// </summary>
namespace GammaEngine {

	class Gamepad;
	class GammaEngineAPI GamepadManager
	{
	public:
		GamepadManager();
		static void AddPad(int id);
		static Gamepad* GetPad(int id);
		static void Frame();

	public:
		static Gamepad* mainController;

	private:
		static std::vector<Gamepad*>* pad;
	};
}