#include "stdafx.h"

using namespace GammaEngine;

GammaEngine::UIElement::UIElement(GameObject* t) :
	Component(t),
	size(vector2(100.0f, 100.0f)),
	material(new Material()),
	appliedEffects(new std::vector<IEffect*>()) {}

GammaEngine::UIElement::~UIElement()
{

}


void GammaEngine::UIElement::Render()
{
	
}

void GammaEngine::UIElement::Update()
{

}

bool GammaEngine::UIElement::InBound(vector2 v)
{
	return false;
}