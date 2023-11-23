#include "Effect.h"
#include "PointLightEffect.h"

PointLightEffect::PointLightEffect()
{
	id = EffectId::PointLightEffect;
	lightPosition = vector3();
	diffuseConstant = 1.0f;
	specularConstant = 1.0f;
	specularExponent = 1.0f;
	surfaceScale = 1.0f;
	color = vector3(1.0f, 1.0f, 1.0f);
	kernelUnitLength = vector2(1.0f, 1.0f);
	scaleMode = ScaleMode::POINTSPECULAR_SCALE_MODE_LINEAR;
}

void PointLightEffect::SetLightPosition(vector3 val)
{
	lightPosition = val;
}

void PointLightEffect::SetDiffuseConstant(float val)
{
	diffuseConstant = val;
}

void PointLightEffect::SetSpecularConstant(float val)
{
	specularConstant = val;
}

void PointLightEffect::SetSpecularExponent(float val)
{
	specularExponent = val;
}

void PointLightEffect::SetSurfaceScale(float val)
{
	surfaceScale = val;
}

void PointLightEffect::SetColor(vector3 val)
{
	color = val;
}

void PointLightEffect::SetKernelUnitLength(vector2 val)
{
	kernelUnitLength = val;
}

void PointLightEffect::SetScaleMode(ScaleMode val)
{
	scaleMode = val;
}
