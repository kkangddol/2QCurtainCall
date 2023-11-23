#include "Effect.h"
#include "LinearTransferEffect.h"



void LinearTransferEffect::SetIntercept(vector4 val)
{
	intercept = val;
}

void LinearTransferEffect::SetSlope(vector4 val)
{
	slope = val;
}

void LinearTransferEffect::SetDisableRed(bool val)
{
	disableRed = val;
}

void LinearTransferEffect::SetDisableBlue(bool val)
{
	disableBlue = val;
}

void LinearTransferEffect::SetDisableGreen(bool val)
{
	disableGreen = val;
}

void LinearTransferEffect::SetDisableAlpha(bool val)
{
	disableAlpha = val;
}

void LinearTransferEffect::SetClampOutput(bool val)
{
	clampOutput = val;
}