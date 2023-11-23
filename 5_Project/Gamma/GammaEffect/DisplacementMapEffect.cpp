#include "Effect.h"
#include "DisplacementMapEffect.h"


DisplacementMapEffect::DisplacementMapEffect()
{
	id = EffectId::DiscreteTransferEffect;
	xChannelSelect = ChannelSelector::CHANNEL_SELECTOR_A;
	yChannelSelect = ChannelSelector::CHANNEL_SELECTOR_A;
}

void DisplacementMapEffect::SetXChannelSelect(ChannelSelector val)
{
	xChannelSelect = val;
}

void DisplacementMapEffect::SetYChannelSelect(ChannelSelector val)
{
	yChannelSelect = val;
}