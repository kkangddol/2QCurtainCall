#include "stdafx.h"

std::map<std::wstring, PrintData>* TextAnimator::dataList;
GammaEngine::TextAnimator::TextAnimator(GameObject* t) :Component(t)
{
	renderer_ = GetComponent<TextAnimationRenderer>();
	dataList = new std::map<std::wstring, PrintData>();
}

GammaEngine::TextAnimator::~TextAnimator()
{

}

void GammaEngine::TextAnimator::AddAnimation(std::wstring tag, PrintData data)
{
	dataList->insert(std::make_pair(tag, data));
}


void GammaEngine::TextAnimator::Play()
{
	for (int i = 0; i < renderer_->letter->size(); i++)
	{
		Tween::Animate((*renderer_->letter)[i].material.pen.w, PLAYBACK::ONCE_FORWARD, 1, EASING::LINEAR, 0.2, 0.2 * i);
		Tween::Animate((*renderer_->letter)[i].transform.scale, PLAYBACK::ONCE_FORWARD, vector2(1,1), EASING::LINEAR, 0.2, 0.2 * i);
	}
}

void GammaEngine::TextAnimator::Render()
{

}