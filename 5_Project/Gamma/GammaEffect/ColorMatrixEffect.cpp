#include "Effect.h"
#include "ColorMatrixEffect.h"

ColorMatrixEffect::ColorMatrixEffect()
{
	id = EffectId::ColorMatrixEffect;
	matrix = Matrix5x5();
	matrix[0][0] = 1.0f;
	matrix[1][1] = 1.0f;
	matrix[2][2] = 1.0f;
	matrix[3][3] = 1.0f;
	matrix[4][4] = 1.0f;
	alphaMode = AlphaMode::PREMULTIPLIED;
	clampOutput = false;
}

void ColorMatrixEffect::SetMatrix(Matrix5x5 mat)
{
	matrix = mat;
}

void ColorMatrixEffect::SetAlphaMode(AlphaMode mode)
{
	alphaMode = mode;
}

void ColorMatrixEffect::SetClampOutput(bool val)
{
	clampOutput = val;
}