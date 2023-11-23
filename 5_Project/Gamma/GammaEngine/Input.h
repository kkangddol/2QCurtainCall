#pragma once

namespace GammaEngine
{
	/// <summary>
	/// 키의 상태를 표현하는 enum 타입
	/// </summary>
	enum class GammaEngineAPI KeyState {
		pressed,
		released,
		pressing,
		none
	};

	/// <summary>
	/// 키보드 및 마우스 입력을 담당하는 class
	/// </summary>
	class GammaEngineAPI Input : public Singleton<Input>
	{
	public:
		Input();
		~Input();

	public:
		void Initialize(HWND hwnd);
		void Frame();

	public:
		static bool GetKey(int key);//키가 눌려진 동안 true를 반환하는 함수
		static bool GetKeyDown(int key);//키가 눌렸을때 true를 반환하는 함수
		static bool GetKeyUp(int key);//키가 떼어졌을때 true를 반환하는 함수
		static bool GetMouseButton(int mouseBtn);//마우스가 눌려진 동안 true를 반환하는 함수
		static bool GetMouseButtonDown(int mouseBtn);//마우스가 눌렸을때 true를 반환하는 함수
		static bool GetMouseButtonUp(int mouseBtn);//마우스가 떼어졌을때 true를 반환하는 함수
		static vector2 GetMousePosition();//마우스의 좌표를 반환하는 함수
		
	public:
		static HWND hWnd;
		static KeyState key[256];//현재 키의 상태를 반환하는 변수
		static int mouse[3];
		static short mouseScrollDelta;
	};


}
