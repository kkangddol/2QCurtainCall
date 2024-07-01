#pragma once

class PointLightEffect : public Effect
{
public:
	enum ScaleMode
	{
		POINTSPECULAR_SCALE_MODE_NEAREST_NEIGHBOR,
		POINTSPECULAR_SCALE_MODE_LINEAR,
		POINTSPECULAR_SCALE_MODE_CUBIC,
		POINTSPECULAR_SCALE_MODE_MULTI_SAMPLE_LINEAR,
		POINTSPECULAR_SCALE_MODE_ANISOTROPIC,
		POINTSPECULAR_SCALE_MODE_HIGH_QUALITY_CUBIC
	};
public:
	vector3 lightPosition;
	float diffuseConstant;
	float specularExponent;
	float specularConstant;
	float surfaceScale;
	vector3 color;
	vector2 kernelUnitLength;
	ScaleMode scaleMode;
public:
	PointLightEffect();
	void SetLightPosition(vector3);
	void SetDiffuseConstant(float);
	void SetSpecularExponent(float);
	void SetSpecularConstant(float);
	void SetColor(vector3);
	void SetSurfaceScale(float);
	void SetKernelUnitLength(vector2);
	void SetScaleMode(ScaleMode);

};

