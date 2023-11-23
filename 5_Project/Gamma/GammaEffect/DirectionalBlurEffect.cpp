#include "Effect.h"
#include "DirectionalBlurEffect.h"

DirectionalBlurEffect::DirectionalBlurEffect()
{
	id = EffectId::DirectionalBlurEffect;
	standardDeviation = 3.0f;
	angle = 0.0f;
	borderMode = BorderMode::BORDER_MODE_SOFT;
	optimization = PropOptimization::DIRECTIONALBLUR_OPTIMIZATION_BALANCED;
}

void DirectionalBlurEffect::SetStandardDeviation(float val)
{
	standardDeviation = val;
}

void DirectionalBlurEffect::SetAngle(float val)
{
	angle = val;
}

void DirectionalBlurEffect::SetOptimization(PropOptimization val)
{
	optimization = val;
}

void DirectionalBlurEffect::SetBorderMode(BorderMode val)
{
	borderMode = val;
}
