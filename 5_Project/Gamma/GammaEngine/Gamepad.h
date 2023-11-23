#pragma once
#include <Xinput.h>
#include <map>
#pragma comment(lib, "xinput.lib")

/// <summary>
/// Xbox 컨트롤러 클래스
// 패드 조작키
//#define XINPUT_GAMEPAD_DPAD_UP          0x00000001
//#define XINPUT_GAMEPAD_DPAD_DOWN        0x00000002
//#define XINPUT_GAMEPAD_DPAD_LEFT        0x00000004
//#define XINPUT_GAMEPAD_DPAD_RIGHT       0x00000008
//#define XINPUT_GAMEPAD_START            0x00000010
//#define XINPUT_GAMEPAD_BACK             0x0020
//#define XINPUT_GAMEPAD_LEFT_THUMB       0x0040
//#define XINPUT_GAMEPAD_RIGHT_THUMB      0x0080
//#define XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100
//#define XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200
//#define XINPUT_GAMEPAD_A                0x1000
//#define XINPUT_GAMEPAD_B                0x2000
//#define XINPUT_GAMEPAD_X                0x4000
//#define XINPUT_GAMEPAD_Y                0x8000
/// </summary>

namespace GammaEngine {
	class GammaEngineAPI Gamepad
	{
	public:
		friend class GamepadManager;

	public:
		Gamepad(int x);	

	public:
		XINPUT_STATE GetState();
		bool GetWbuttonDown(WORD);
		bool GetWbutton(WORD);
		bool GetWbuttonUp(WORD);
		BYTE GetTriggerValue(int);
		SHORT GetStickValue(int);
		float GetStickRotation(int);
		bool IsConnected();
		void Vibrate(int leftVal, int rightVal);
		void Vibrate(int leftVal, int rightVal, float time);

	private:
		void Frame();
	
	public:
		std::map<WORD, KeyState>* wbuttonMap;
	
	private:
		XINPUT_STATE state_;
		int id;
	};
}
