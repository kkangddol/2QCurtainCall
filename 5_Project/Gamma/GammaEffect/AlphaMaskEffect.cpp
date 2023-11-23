#include "Effect.h"
#include "AlphaMaskEffect.h"

AlphaMaskEffect::AlphaMaskEffect()
{
	id = EffectId::AlphaMaskEffect;
}

void AlphaMaskEffect::SetMaskImage(std::wstring str)
{
	maskImage = new std::wstring(str);
}