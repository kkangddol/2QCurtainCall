#pragma once

class DisplacementMapEffect : public Effect
{
public:
	enum ChannelSelector
	{
		CHANNEL_SELECTOR_R,
		CHANNEL_SELECTOR_G,
		CHANNEL_SELECTOR_B,
		CHANNEL_SELECTOR_A
	};
public:
	float scale;
	ChannelSelector xChannelSelect;
	ChannelSelector yChannelSelect;
public:
	DisplacementMapEffect();
	void SetXChannelSelect(ChannelSelector);
	void SetYChannelSelect(ChannelSelector);
};

