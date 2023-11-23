#pragma once
class ArithmeticCompositeEffect : public Effect
{
public:
	std::wstring* other;
	vector4 coefficient;
	bool clampOutput;
public:
	ArithmeticCompositeEffect();
	void SetClampOutput(bool);
	void SetOtherImage(std::wstring);
};
	

