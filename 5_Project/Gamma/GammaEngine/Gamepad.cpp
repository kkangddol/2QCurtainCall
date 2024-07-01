#include "stdafx.h"

using namespace GammaEngine;

GammaEngine::Gamepad::Gamepad(int x)
{
	id = x;
	ZeroMemory(&state_, sizeof(XINPUT_STATE));
    wbuttonMap = new std::map<WORD, KeyState>();
    wbuttonMap->insert(std::make_pair(XINPUT_GAMEPAD_DPAD_UP, KeyState::none));
    wbuttonMap->insert(std::make_pair(XINPUT_GAMEPAD_DPAD_DOWN, KeyState::none));
    wbuttonMap->insert(std::make_pair(XINPUT_GAMEPAD_DPAD_LEFT, KeyState::none));
    wbuttonMap->insert(std::make_pair(XINPUT_GAMEPAD_DPAD_RIGHT, KeyState::none));
    wbuttonMap->insert(std::make_pair(XINPUT_GAMEPAD_START, KeyState::none));
    wbuttonMap->insert(std::make_pair(XINPUT_GAMEPAD_BACK, KeyState::none));
    wbuttonMap->insert(std::make_pair(XINPUT_GAMEPAD_LEFT_THUMB, KeyState::none));
    wbuttonMap->insert(std::make_pair(XINPUT_GAMEPAD_RIGHT_THUMB, KeyState::none));
    wbuttonMap->insert(std::make_pair(XINPUT_GAMEPAD_LEFT_SHOULDER, KeyState::none));
    wbuttonMap->insert(std::make_pair(XINPUT_GAMEPAD_RIGHT_SHOULDER, KeyState::none));
    wbuttonMap->insert(std::make_pair(XINPUT_GAMEPAD_A, KeyState::none));
    wbuttonMap->insert(std::make_pair(XINPUT_GAMEPAD_B, KeyState::none));
    wbuttonMap->insert(std::make_pair(XINPUT_GAMEPAD_X, KeyState::none));
    wbuttonMap->insert(std::make_pair(XINPUT_GAMEPAD_Y, KeyState::none));
}

XINPUT_STATE GammaEngine::Gamepad::GetState()
{
  ZeroMemory(&state_, sizeof(XINPUT_STATE));
  XInputGetState(id, &state_);
  return state_;
  
	
}

void GammaEngine::Gamepad::Frame()
{
    for (auto iter = wbuttonMap->begin(); iter != wbuttonMap->end(); iter++)
    {
        if (GetState().Gamepad.wButtons & (*iter).first && (*iter).second == KeyState::none)
            (*iter).second = KeyState::pressed;
        else if (GetState().Gamepad.wButtons & (*iter).first && (*iter).second == KeyState::pressed)
            (*iter).second = KeyState::pressing;
        else if (!(GetState().Gamepad.wButtons & (*iter).first) && (*iter).second == KeyState::pressing)
            (*iter).second = KeyState::released;
        else if (!(GetState().Gamepad.wButtons & (*iter).first) && (*iter).second == KeyState::released)
            (*iter).second = KeyState::none;
    }
}

bool GammaEngine::Gamepad::GetWbuttonDown(WORD k)
{
    if ((*wbuttonMap)[k] == KeyState::pressed)
    {
        return true;
    }
    return false;
}
bool GammaEngine::Gamepad::GetWbutton(WORD k)
{
    if ((*wbuttonMap)[k] == KeyState::pressing)
    {
        return true;
    }
    return false;
}
bool GammaEngine::Gamepad::GetWbuttonUp(WORD k)
{
    if ((*wbuttonMap)[k] == KeyState::released)
    {
        return true;
    }
    return false;
}
BYTE GammaEngine::Gamepad::GetTriggerValue(int n)
{
    if (n == 0)
    {
        return GetState().Gamepad.bLeftTrigger;
    }
    else
    {
        return GetState().Gamepad.bRightTrigger;
    }
    
}

SHORT GammaEngine::Gamepad::GetStickValue(int n)
{
    if (n == 0)
    {
        if (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < GetState().Gamepad.sThumbLX || -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE > GetState().Gamepad.sThumbLX)
        {
            return GetState().Gamepad.sThumbLX;
        }
        else
        {
            return 0;
        }
        
    } 
    if (n == 1)
    {
        if (XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < GetState().Gamepad.sThumbLY || -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE > GetState().Gamepad.sThumbLY)
        {
            return GetState().Gamepad.sThumbLY;
        }
        else
        {
            return 0;
        }

    } 
    if (n == 2)
    {
        if (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE < GetState().Gamepad.sThumbRX || -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE > GetState().Gamepad.sThumbRX)
        {
            return GetState().Gamepad.sThumbRX;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if (XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE < GetState().Gamepad.sThumbRY || -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE > GetState().Gamepad.sThumbRY)
        {
            return GetState().Gamepad.sThumbRY;
        }
        else
        {
            return 0;
        }
    }
}

float GammaEngine::Gamepad::GetStickRotation(int n)
{
    if (n == 0)
    {
        float angle = atan2f(GetStickValue(0), GetStickValue(1));
        return angle * 180.0f / 3.1415926535f;
    }
    else
    {
        float angle = atan2f(GetStickValue(2), GetStickValue(3));
        return angle * 180.0f / 3.1415926535f;
    }
}

bool GammaEngine::Gamepad::IsConnected()
{
    if (XInputGetState(id, &state_) == ERROR_SUCCESS)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void GammaEngine::Gamepad::Vibrate(int leftVal, int rightVal)
{
    // Create a Vibraton State
    XINPUT_VIBRATION Vibration;

    // Zeroise the Vibration
    ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

    // Set the Vibration Values
    Vibration.wLeftMotorSpeed = leftVal;
    Vibration.wRightMotorSpeed = rightVal;

    // Vibrate the controller
    XInputSetState(id, &Vibration);
}

void GammaEngine::Gamepad::Vibrate(int leftVal, int rightVal,float time)
{
    // Create a Vibraton State
    XINPUT_VIBRATION Vibration;

    // Zeroise the Vibration
    ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

    // Set the Vibration Values
    Vibration.wLeftMotorSpeed = leftVal;
    Vibration.wRightMotorSpeed = rightVal;
    Timer::Delay(time, false, [this]() {
        XINPUT_VIBRATION Vibration;
        ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));
        Vibration.wLeftMotorSpeed = 0;
        Vibration.wRightMotorSpeed = 0;
        XInputSetState(id, &Vibration);
    });
    // Vibrate the controller
    XInputSetState(id, &Vibration);
}