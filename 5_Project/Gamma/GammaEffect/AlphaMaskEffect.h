#pragma once

class AlphaMaskEffect : public Effect
{
public:
		std::wstring* maskImage;
public:
	AlphaMaskEffect();
	void SetMaskImage(std::wstring);
};

