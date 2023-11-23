#include "Effect.h"
#include "ArithmeticCompositeEffect.h"

ArithmeticCompositeEffect::ArithmeticCompositeEffect()
{
	id = EffectId::ArithmeticCompositeEffect;
}

void ArithmeticCompositeEffect::SetClampOutput(bool val)
{
	clampOutput = val;
}

void ArithmeticCompositeEffect::SetOtherImage(std::wstring val)
{
	other = new std::wstring(val);
}