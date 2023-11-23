#pragma once

class DistantLightEffect : public Effect
{
public:
	enum ScaleMode
	{
		DISTANTDIFFUSE_SCALE_MODE_NEAREST_NEIGHBOR,
		DISTANTDIFFUSE_SCALE_MODE_LINEAR,
		DISTANTDIFFUSE_SCALE_MODE_CUBIC,
		DISTANTDIFFUSE_SCALE_MODE_MULTI_SAMPLE_LINEAR,
		DISTANTDIFFUSE_SCALE_MODE_ANISOTROPIC,
		DISTANTDIFFUSE_SCALE_MODE_HIGH_QUALITY_CUBIC
	};
public:
	float azimuth;
	float elevation;
	float diffuseConstant;
	float specularExponent;
	float specularConstant;
	float surfaceScale;
	vector3 color;
	vector2 kernelUnitLength;
	ScaleMode scaleMode;
public:
	DistantLightEffect();
	void SetAzimuth(float);
	void SetElevation(float);
	void SetDiffuseConstant(float);
	void SetSpecularConstant(float);
	void SetSpecularExponent(float);
	void SetColor(vector3);
	void SetSurfaceScale(float);
	void SetKernelUnitLength(vector2);
	void SetScaleMode(ScaleMode);

};

