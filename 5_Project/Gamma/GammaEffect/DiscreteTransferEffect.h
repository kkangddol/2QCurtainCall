#pragma once

class DiscreteTransferEffect : public Effect
{
public:
	float redTable[2];
	float blueTable[2];
	float greenTable[2];
	float alphaTable[2];
	bool disableRed;
	bool disableBlue;
	bool disableGreen;
	bool disableAlpha;
	bool clampOutput;
public:
	DiscreteTransferEffect();
	void SetRedTable(float, float);
	void SetBlueTable(float, float);
	void SetGreenTable(float, float);
	void SetAlphaTable(float, float);
	void SetDisableRed(bool);
	void SetDisableBlue(bool);
	void SetDisableGreen(bool);
	void SetDisableAlpha(bool);
	void SetClampOutput(bool);
};

