#include "effect.h"
#include "BlendEffect.h"


BlendEffect::BlendEffect()
{
	id = EffectId::BlendEffect;
	blendMode = BlendMode::BLEND_MODE_MULTIPLY;
}

void BlendEffect::SetBlendMode(BlendMode val)
{
	blendMode = val;
}

void  BlendEffect::SetOtherImage(std::wstring val)
{
	other = new std::wstring(val);
}