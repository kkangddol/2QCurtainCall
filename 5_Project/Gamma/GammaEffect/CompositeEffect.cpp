#include "Effect.h"
#include "CompositeEffect.h"

CompositeEffect::CompositeEffect()
{
	id = EffectId::CrossFadeEffect;
	mode = CompositMode::COMPOSITE_MODE_SOURCE_OVER;
	other = nullptr;
}
void CompositeEffect::SetOtherImage(std::wstring val)
{
	other = new std::wstring(val);
}

void CompositeEffect::SetCompositeMode(CompositMode val)
{
	mode = val;
}