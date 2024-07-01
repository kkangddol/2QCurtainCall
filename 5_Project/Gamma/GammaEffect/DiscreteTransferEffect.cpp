#include "Effect.h"
#include "DiscreteTransferEffect.h"


DiscreteTransferEffect::DiscreteTransferEffect()
{
	id = EffectId::DiscreteTransferEffect;
	redTable[0] = 0.0f;
	redTable[1] = 0.0f;
	blueTable[0] = 0.0f;
	blueTable[1] = 0.0f;
	greenTable[0] = 0.0f;
	greenTable[1] = 0.0f;
	alphaTable[0] = 0.0f;
	alphaTable[1] = 0.0f;
	clampOutput = false;
}

void DiscreteTransferEffect::SetRedTable(float val0,float val1)
{
	redTable[0] = val0;
	redTable[1] = val1;
}

void DiscreteTransferEffect::SetBlueTable(float val0, float val1)
{
	blueTable[0] = val0;
	blueTable[1] = val1;
}

void DiscreteTransferEffect::SetGreenTable(float val0, float val1)
{
	greenTable[0] = val0;
	greenTable[1] = val1;
}

void DiscreteTransferEffect::SetAlphaTable(float val0, float val1)
{
	alphaTable[0] = val0;
	alphaTable[1] = val1;
}

void DiscreteTransferEffect::SetDisableRed(bool val)
{
	disableRed = val;
}

void DiscreteTransferEffect::SetDisableBlue(bool val)
{
	disableBlue = val;
}

void DiscreteTransferEffect::SetDisableGreen(bool val)
{
	disableGreen = val;
}

void DiscreteTransferEffect::SetDisableAlpha(bool val)
{
	disableAlpha= val;
}

void DiscreteTransferEffect::SetClampOutput(bool val)
{
	clampOutput = val;
}