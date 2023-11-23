#include "stdafx.h"

using namespace GammaEngine;
GammaEngine::PointLight::PointLight(GameObject* t) : Light(t)
{
	z = 10;
}

GammaEngine::PointLight::~PointLight()
{

}


void GammaEngine::PointLight::SetZ(float val)
{
	z = val;
}

float GammaEngine::PointLight::GetZ()
{
	return z;
}

void  GammaEngine::PointLight::dummy()
{

}