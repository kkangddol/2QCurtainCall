#pragma once
#pragma comment(lib, "xinput.lib")
#include <Xinput.h>

/// <summary>
/// xBox �е��� ������ ����Ŭ �� �ִ� 4���� �е� ����
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