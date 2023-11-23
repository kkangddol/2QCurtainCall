#include "stdafx.h"

using namespace GammaEngine;

std::vector<Gamepad*>* GammaEngine::GamepadManager::pad;
GammaEngine::GamepadManager::GamepadManager()
{
	pad=new std::vector<Gamepad*>();
	AddPad(0);
	AddPad(1);
}

void GammaEngine::GamepadManager::Frame()
{
	for (auto iter = pad->begin(); iter < pad->end(); iter++)
	{
		(* iter)->Frame();
	}
}

void GammaEngine::GamepadManager::AddPad(int id)
{
	pad->push_back(new Gamepad(id));
}

Gamepad* GammaEngine::GamepadManager::GetPad(int id)
{
	return (*pad)[id];
}