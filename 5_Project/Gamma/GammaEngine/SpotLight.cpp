#include "stdafx.h"

using namespace GammaEngine;
GammaEngine::SpotLight::SpotLight(GameObject* t) : Light(t)
{
	at = vector3();
	focus= 1.0f;
	ConeAngle=90;
	z = 100;
}

GammaEngine::SpotLight::~SpotLight()
{

}


void GammaEngine::SpotLight::SetZ(float val)
{
	z = val;
}

float GammaEngine::SpotLight::GetZ()
{
	return z;
}

vector3 GammaEngine::SpotLight::GetAt()
{
	return at;
}

void GammaEngine::SpotLight::SetAt(vector3 val)
{
	 at= val;
}

float GammaEngine::SpotLight::GetFocus()
{
	return focus;
}

void GammaEngine::SpotLight::SetFocus(float val)
{
	focus = val;
}

float GammaEngine::SpotLight::GetConeAngle()
{
	return ConeAngle;
}
void GammaEngine::SpotLight::SetConeAngle(float val)
{
	ConeAngle=val;
}

void  GammaEngine::SpotLight::dummy()
{

}