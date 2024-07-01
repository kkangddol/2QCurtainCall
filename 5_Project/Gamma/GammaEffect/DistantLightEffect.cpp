#include "Effect.h"
#include "DistantLightEffect.h"

DistantLightEffect::DistantLightEffect()
{
	id = EffectId::DistantLightEffect;
	azimuth = 0.0f;
	elevation = 0.0f;
	diffuseConstant = 1.0f;
	specularConstant = 1.0f;
	specularExponent = 1.0f;
	surfaceScale = 1.0f;
	color = vector3(1.0f, 1.0f, 1.0f);
	kernelUnitLength = vector2(1.0f, 1.0f);
	scaleMode = ScaleMode::DISTANTDIFFUSE_SCALE_MODE_LINEAR;
}

void DistantLightEffect::SetAzimuth(float val)
{
	azimuth = val;
}

void DistantLightEffect::SetElevation(float val)
{
	elevation = val;
}

void DistantLightEffect::SetDiffuseConstant(float val)
{
	diffuseConstant = val;
}
void DistantLightEffect::SetSpecularConstant(float val)
{
	specularConstant = val;
}

void DistantLightEffect::SetSpecularExponent(float val)
{
	specularExponent = val;
}

void DistantLightEffect::SetSurfaceScale(float val)
{
	surfaceScale = val;
}

void DistantLightEffect::SetColor(vector3 val)
{
	color = val;
}

void DistantLightEffect::SetKernelUnitLength(vector2 val)
{
	kernelUnitLength = val;
}

void DistantLightEffect::SetScaleMode(ScaleMode val)
{
	scaleMode = val;
}
