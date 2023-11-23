#include "InputSystem.h"
#include "Button.h"

short InputSystem::mouseScrollDelta = 0;
Button* InputSystem::currentButton = nullptr;
bool InputSystem::isButtonHold = false;
HWND InputSystem::hWnd_ = NULL;
std::unordered_map<unsigned int, InputUnit> InputSystem::inputMap_;

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

/// InputSystem에서 관리할 입력 키값을 map에 미리 등록한다.
/// 22.12.18 강석원 집
void InputSystem::Initialize(const HWND& hWnd)
{
	hWnd_ = hWnd;

	inputMap_[VK_F1];
	inputMap_[VK_LEFT];
	inputMap_[VK_UP];
	inputMap_[VK_RIGHT];
	inputMap_[VK_DOWN];
	inputMap_[VK_LBUTTON];
	inputMap_[VK_RBUTTON];
	inputMap_[VK_MBUTTON];
	inputMap_['Q'];
	inputMap_['E'];
	inputMap_['W'];
	inputMap_['S'];
	inputMap_['A'];
	inputMap_['D'];
	inputMap_['1'];
	inputMap_['2'];
	inputMap_['3'];
}

void InputSystem::Finalize()
{

}

/// 이전 프레임의 상태를 이전 상태로 옮긴다.
/// 22.12.18 강석원 집
void InputSystem::AgingStatus()
{
	if (!isButtonHold)
	{
		currentButton = nullptr;
	}

	for (auto& iter : inputMap_)
	{
		iter.second.prevStatus = iter.second.nowStatus;
		iter.second.nowStatus = false;
	}
}

/// Input을 입력받아서 상태를 저장한다.
/// 22.12.18 강석원 집
void InputSystem::CheckInput()
{
	for (auto& iter : inputMap_)
	{
		if (GetAsyncKeyState(iter.first) & 0x8001)
		{
			iter.second.nowStatus = true;
		}
	}
}

void InputSystem::OnClickEvent()
{
	if (currentButton == nullptr)
	{
		return;
	}

	if (currentButton->IsLeft())
	{
		currentButton->OnLeftClick();
	}
	
	if (currentButton->IsRight())
	{
		currentButton->OnRightClick();
	}
}

bool InputSystem::GetKeyUp(unsigned int keyCode)
{
	return InputStatus::UP == inputStatus[inputMap_[keyCode].prevStatus][inputMap_[keyCode].nowStatus];
}

bool InputSystem::GetKeyJustDown(unsigned int keyCode)
{
	return InputStatus::JUSTDOWN == inputStatus[inputMap_[keyCode].prevStatus][inputMap_[keyCode].nowStatus];
}

bool InputSystem::GetKeyJustUp(unsigned int keyCode)
{
	return InputStatus::JUSTUP == inputStatus[inputMap_[keyCode].prevStatus][inputMap_[keyCode].nowStatus];
}

bool InputSystem::GetKeyHold(unsigned int keyCode)
{
	return InputStatus::HOLD == inputStatus[inputMap_[keyCode].prevStatus][inputMap_[keyCode].nowStatus];
}

bool InputSystem::GetMouseButtonUP(int mouseBtn)
{
	return InputStatus::UP == inputStatus[inputMap_[mouseBtn].prevStatus][inputMap_[mouseBtn].nowStatus];
}

bool InputSystem::GetMouseButtonJustDown(int mouseBtn)
{
	return InputStatus::JUSTDOWN == inputStatus[inputMap_[mouseBtn].prevStatus][inputMap_[mouseBtn].nowStatus];
}

bool InputSystem::GetMouseButtonJustUp(int mouseBtn)
{
	return InputStatus::JUSTUP == inputStatus[inputMap_[mouseBtn].prevStatus][inputMap_[mouseBtn].nowStatus];
}

bool InputSystem::GetMouseButtonHold(int mouseBtn)
{
	return InputStatus::HOLD == inputStatus[inputMap_[mouseBtn].prevStatus][inputMap_[mouseBtn].nowStatus];
}

Vector2D InputSystem::GetMousePosition()
{
	POINT p;
	//GetWindowRect(hWnd_, &rc);
	GetCursorPos(&p);
	ScreenToClient(hWnd_, &p);
	return  Vector2D((float)(p.x), (float)(p.y));;
}

bool InputSystem::CompareOrder(Button* button)
{
	if (currentButton == nullptr)
	{
		currentButton = button;
		return true;
	}

	if (currentButton > button)
	{
		currentButton = button;
		return true;
	}

	return false;
}
