#include "Effect.h"
#include "CrossFadeEffect.h"

CrossFadeEffect::CrossFadeEffect()
{
	id = EffectId::CrossFadeEffect;
	progress = 0.0f;
	other = nullptr;
}
void CrossFadeEffect::SetOtherImage(std::wstring val)
{
	other = new std::wstring(val);
}

void CrossFadeEffect::SetProgress(float val)
{
	progress = val;
}