#include "Effect.h"
#include "ConvolveMatrixEffect.h"


ConvolveMatrixEffect::ConvolveMatrixEffect()
{
	id = EffectId::ConvolveMatrixEffect;
	kernelUnitLength = 1.0f;
	scaleMode = ScaleMode::SCALE_MODE_LINEAR;
	kernelSizeX = 3;
	kernelSizeY = 3;
	kernelMatrix = Matrix3x3();
	kernelMatrix[1][1] = 1.0f;
	divisor = 1;
	kernelOffset = vector2();
	preserveAlpha = false;
	borderMode = BorderMode::BORDER_MODE_SOFT;
	clampOutput = false;
}

void ConvolveMatrixEffect::SetKernelUnitLength(float val)
{
	kernelUnitLength = val;
}

void ConvolveMatrixEffect::SetScaleMode(ScaleMode val)
{
	scaleMode = val;
}

void ConvolveMatrixEffect::SetKernelSizeX(int val)
{
	kernelSizeX = val;
}

void ConvolveMatrixEffect::SetKernelSizeY(int val)
{
	kernelSizeY = val;
}

void ConvolveMatrixEffect::SetKernelMatrix(Matrix3x3 val)
{
	kernelMatrix = val;
}

void ConvolveMatrixEffect::SetDivisor(int val)
{
	divisor = val;
}

void ConvolveMatrixEffect::SetBias(float val)
{
	bias = val;
}

void ConvolveMatrixEffect::SetKernelOffset(vector2 val)
{
	kernelOffset = val;
}

void ConvolveMatrixEffect::SetPreserveAlpha(bool val)
{
	preserveAlpha = val;
}

void ConvolveMatrixEffect::SetBorderMode(BorderMode val)
{
	borderMode = val;
}

void ConvolveMatrixEffect::SetClampOutput(bool val)
{
	clampOutput = val;
}
