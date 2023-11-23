#pragma once

class CrossFadeEffect : public Effect
{
public:
	std::wstring* other;
	float progress;

public:
	CrossFadeEffect();
	void SetOtherImage(std::wstring);
	void SetProgress(float);
};

