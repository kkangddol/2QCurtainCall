#pragma once

class DirectionalBlurEffect : public Effect
{
public:
	enum PropOptimization 
	{
		DIRECTIONALBLUR_OPTIMIZATION_SPEED,
		DIRECTIONALBLUR_OPTIMIZATION_BALANCED,
		DIRECTIONALBLUR_OPTIMIZATION_QUALITY
	};
	enum BorderMode
	{
		BORDER_MODE_SOFT,
		BORDER_MODE_HARD
	};
public:
	float standardDeviation;
	float angle;
	PropOptimization optimization;
	BorderMode borderMode;
public:
	DirectionalBlurEffect();
	void SetStandardDeviation(float);
	void SetAngle(float);
	void SetOptimization(PropOptimization);
	void SetBorderMode(BorderMode);
};

