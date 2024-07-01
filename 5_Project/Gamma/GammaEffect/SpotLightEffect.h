#pragma once

class SpotLightEffect : public Effect
{
public:
	enum ScaleMode
	{
		SPOTSPECULAR_SCALE_MODE_NEAREST_NEIGHBOR,
		SPOTSPECULAR_SCALE_MODE_LINEAR,
		SPOTSPECULAR_SCALE_MODE_CUBIC,
		SPOTSPECULAR_SCALE_MODE_MULTI_SAMPLE_LINEAR,
		SPOTSPECULAR_SCALE_MODE_ANISOTROPIC,
		SPOTSPECULAR_SCALE_MODE_HIGH_QUALITY_CUBIC
	};
public:
	vector3 lightPosition;
	vector3 pointsAt;
	float focus;
	float limitingConeAngle;
	float specularExponent;
	float diffuseConstant;
	float specularConstant;
	float surfaceScale;
	vector3 color;
	vector2 kernelUnitLength;
	ScaleMode scaleMode;
public:
	SpotLightEffect();
	void SetLightPosition(vector3);
	void SetSpecularConstant(float );
	void SetDiffuseConstant(float );
	void SetSpecularExponent(float );
	void SetColor(vector3);
	void SetSurfaceScale(float);
	void SetKernelUnitLength(vector2);
	void SetScaleMode(ScaleMode);
	void SetPointsAt(vector3);
	void SetFocus(float);
	void SetLimitingConeAngle(float);

};

