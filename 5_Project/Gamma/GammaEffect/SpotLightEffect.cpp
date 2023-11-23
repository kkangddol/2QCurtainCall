#include "Effect.h"
#include "SpotLightEffect.h"

SpotLightEffect::SpotLightEffect()
{
	id = EffectId::SpotLightEffect;
	lightPosition = vector3(0.0f, 0.0f, 0.0f);
	pointsAt = vector3(0.0f, 0.0f, 0.0f);
	focus = 1.0f;
	limitingConeAngle = 90.0f;
	diffuseConstant = 1.0f;
	specularConstant = 1.0f;
	specularExponent = 1.0f;
	surfaceScale = 1.0f;
	color = vector3(1.0f, 1.0f, 1.0f);
	kernelUnitLength = vector2(1.0f, 1.0f);
	scaleMode = ScaleMode::SPOTSPECULAR_SCALE_MODE_LINEAR;
}


void SpotLightEffect::SetLightPosition(vector3 val)
{
	lightPosition = val;
}

void SpotLightEffect::SetDiffuseConstant(float val)
{
	diffuseConstant = val;
}

void SpotLightEffect::SetSpecularConstant(float val)
{
	specularConstant = val;
}

void SpotLightEffect::SetSpecularExponent(float val)
{
	specularExponent = val;
}


void SpotLightEffect::SetSurfaceScale(float val)
{
	surfaceScale = val;
}

void SpotLightEffect::SetColor(vector3 val)
{
	color = val;
}

void SpotLightEffect::SetKernelUnitLength(vector2 val)
{
	kernelUnitLength = val;
}

void SpotLightEffect::SetScaleMode(ScaleMode val)
{
	scaleMode = val;
}

void SpotLightEffect::SetPointsAt(vector3 val)
{
	pointsAt = val;
}

void SpotLightEffect::SetFocus(float val)
{
	focus = val;
}

void SpotLightEffect::SetLimitingConeAngle(float val)
{
	limitingConeAngle = val;
}

