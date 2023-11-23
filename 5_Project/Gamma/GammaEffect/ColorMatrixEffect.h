#pragma once

class ColorMatrixEffect : public Effect
{
public:
	enum class AlphaMode
	{
		PREMULTIPLIED,
		STRAIGHT
	};

public:
	Matrix5x5 matrix;
	AlphaMode alphaMode;
	bool clampOutput;

public:
	ColorMatrixEffect();
	void SetMatrix(Matrix5x5);
	void SetAlphaMode(AlphaMode);
	void SetClampOutput(bool);
};


