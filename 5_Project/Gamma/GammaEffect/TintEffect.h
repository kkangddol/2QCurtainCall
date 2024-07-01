#pragma once
class TintEffect : public Effect
{
public:
	vector4 color;
	bool clampOutput;
public:
	TintEffect();
	void SetColor(vector4);
	void SetClampOutput(bool);
};

