#include "Effect.h"
#include "TintEffect.h"


TintEffect::TintEffect()
{
	id = EffectId::TintEffect;
	color = vector4(1, 1, 1, 1);
	clampOutput = false;
}

void TintEffect::SetColor(vector4 val)
{
	color = val;
}

void TintEffect::SetClampOutput(bool val)
{
	clampOutput = val;
}