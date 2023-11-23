#include "stdafx.h"

using namespace GammaEngine;
GammaEngine::DistantLight::DistantLight(GameObject* t) : Light(t)
{
	azimuth = 0;
	elevation = 40;
}

GammaEngine::DistantLight::~DistantLight()
{

}
float GammaEngine::DistantLight::GetAzimuth()
{
	return azimuth;
}

void GammaEngine::DistantLight::SetAzimuth(float val)
{
	azimuth = val;
}

float GammaEngine::DistantLight::GetElvation()
{
	return elevation;
}

void GammaEngine::DistantLight::SetElvation(float val)
{
	elevation = val;
}

void  GammaEngine::DistantLight::dummy()
{

}