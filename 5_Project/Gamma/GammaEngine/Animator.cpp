#include "stdafx.h"
using namespace GammaEngine;

GammaEngine::Animator::Animator(GameObject* t) :Component(t),
bitmap(*(GetComponent<BitmapRenderer>()->bitmap))
//bitmap(bitmap = GetComponent<BitmapRenderer>()->bitmap || GetComponent<BoxUIElement>()->bitmap)
{
	animationList = new std::unordered_map<std::wstring, Animation*>();
	currentAnimation = new std::wstring();
}

GammaEngine::Animator::~Animator()
{

}

void GammaEngine::Animator::AddAnimation(wstring name, Animation* animation)
{
	(* animationList)[name] = animation;
}

wstring GammaEngine::Animator::GetCurrentAnimation()
{
	return *currentAnimation;
}

void GammaEngine::Animator::Play(wstring name, PLAYBACK playback)
{
	if (*currentAnimation != std::wstring(L""))
	{
		(*animationList)[*currentAnimation]->Pause();
	}

	if ((*animationList)[name])
	{
		*currentAnimation = name;
		(*animationList)[*currentAnimation]->Play(bitmap, playback);
	}
}
