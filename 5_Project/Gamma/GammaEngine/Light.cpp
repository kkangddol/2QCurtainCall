#include "stdafx.h"

using namespace GammaEngine;
GammaEngine::Light::Light(GameObject* t) :Component(t)
{
	LightSystem::Add(this);
	color = vector3(1, 1, 1);
	magnitude = 1.0f;
}

GammaEngine::Light::~Light()
{
	LightSystem::Remove(this);
}

float GammaEngine::Light::GetMagnitude()
{
	return magnitude;
}

vector3 GammaEngine::Light::GetColor()
{
	return color;
}

void GammaEngine::Light::SetMagnitude(float val)
{
	magnitude = val;
}

void GammaEngine::Light::SetColor(vector3 val)
{
	color = val;
}
