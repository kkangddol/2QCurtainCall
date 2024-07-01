#pragma once
#include <windows.h>
#include <unordered_map>

#include "Vector2D.h"

class Button;

/// 입력 상태를 나타내는 enum class
enum class InputStatus
{
	JUSTUP,
	JUSTDOWN,
	HOLD,
	UP
};

/// 입력을 저장하는 단위
/// keyID를 정수형으로 갖고있고
/// 이전상태 현재상태를 저장한다.
/// 
/// 22.12.18 강석원 집
struct InputUnit
{
	bool prevStatus = false;	// bit연산으로 바꾸고싶다
	bool nowStatus = false;
};

/// 입력의 상태를 바로 알 수 있도록 고안한 배열
/// 첫번째 인덱스로 이전 상태
/// 두번째 인덱스로 현재 상태를 넣으면
/// 해당 상태가 어떤 상태인지 알려준다.
/// 
/// 22.12.18 강석원 집
static InputStatus inputStatus[2][2] = {
	InputStatus::UP,
	InputStatus::JUSTDOWN,
	InputStatus::JUSTUP,
	InputStatus::HOLD,
};

/// 입력을 관리하는 클래스
/// 입력을 InputUnit이라는 단위로 map 자료구조로 관리
/// 
/// 22.12.18 강석원 집
class InputSystem final
{
public:
	~InputSystem();

	static InputSystem& Instance()
	{
		static InputSystem instance;
		return instance;
	}

/// <summary>
/// Core에서 사용할 함수들
/// </summary>
public:
	void Initialize(const HWND& hWnd);
	void Finalize();
	void AgingStatus();
	void CheckInput();
	void OnClickEvent();

/// <summary>
/// 사용자가 받을 키 상태
/// </summary>
public:
	static bool GetKeyUp(unsigned int keyCode);
	static bool GetKeyJustDown(unsigned int keyCode);
	static bool GetKeyJustUp(unsigned int keyCode);
	static bool GetKeyHold(unsigned int keyCode);

	static bool GetMouseButtonUP(int mouseBtn);
	static bool GetMouseButtonJustDown(int mouseBtn);
	static bool GetMouseButtonJustUp(int mouseBtn);
	static bool GetMouseButtonHold(int mouseBtn);
	static Vector2D GetMousePosition();

	static bool CompareOrder(Button* button);

public:
	static short mouseScrollDelta;		// 마우스 휠 스크롤 정보
	static Button* currentButton;		// 가장 위쪽에 있는 버튼
	static bool isButtonHold;			// 현재 버튼을 홀드중이면

private:
	InputSystem();

private:
	static HWND hWnd_;
	static std::unordered_map<unsigned int, InputUnit> inputMap_;
};
