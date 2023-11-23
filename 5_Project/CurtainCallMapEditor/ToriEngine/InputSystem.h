#pragma once
#include <windows.h>
#include <unordered_map>

#include "Vector2D.h"

class Button;

/// �Է� ���¸� ��Ÿ���� enum class
enum class InputStatus
{
	JUSTUP,
	JUSTDOWN,
	HOLD,
	UP
};

/// �Է��� �����ϴ� ����
/// keyID�� ���������� �����ְ�
/// �������� ������¸� �����Ѵ�.
/// 
/// 22.12.18 ������ ��
struct InputUnit
{
	bool prevStatus = false;	// bit�������� �ٲٰ�ʹ�
	bool nowStatus = false;
};

/// �Է��� ���¸� �ٷ� �� �� �ֵ��� ����� �迭
/// ù��° �ε����� ���� ����
/// �ι�° �ε����� ���� ���¸� ������
/// �ش� ���°� � �������� �˷��ش�.
/// 
/// 22.12.18 ������ ��
static InputStatus inputStatus[2][2] = {
	InputStatus::UP,
	InputStatus::JUSTDOWN,
	InputStatus::JUSTUP,
	InputStatus::HOLD,
};

/// �Է��� �����ϴ� Ŭ����
/// �Է��� InputUnit�̶�� ������ map �ڷᱸ���� ����
/// 
/// 22.12.18 ������ ��
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
/// Core���� ����� �Լ���
/// </summary>
public:
	void Initialize(const HWND& hWnd);
	void Finalize();
	void AgingStatus();
	void CheckInput();
	void OnClickEvent();

/// <summary>
/// ����ڰ� ���� Ű ����
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
	static short mouseScrollDelta;		// ���콺 �� ��ũ�� ����
	static Button* currentButton;		// ���� ���ʿ� �ִ� ��ư
	static bool isButtonHold;			// ���� ��ư�� Ȧ�����̸�

private:
	InputSystem();

private:
	static HWND hWnd_;
	static std::unordered_map<unsigned int, InputUnit> inputMap_;
};
