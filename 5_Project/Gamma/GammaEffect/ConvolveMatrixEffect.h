#pragma once


	class ConvolveMatrixEffect : public Effect
	{
	public:
		enum ScaleMode
		{
			SCALE_MODE_NEAREST_NEIGHBOR,
			SCALE_MODE_LINEAR,
			SCALE_MODE_CUBIC,
			SCALE_MODE_MULTI_SAMPLE_LINEAR,
			SCALE_MODE_ANISOTROPIC,
			SCALE_MODE_HIGH_QUALITY_CUBIC
		};

		enum BorderMode
		{
			BORDER_MODE_SOFT,
			BORDER_MODE_HARD
		};


	public:
		float kernelUnitLength;
		ScaleMode scaleMode;
		int kernelSizeX = 3;
		int kernelSizeY = 3;
		Matrix3x3 kernelMatrix;
		int divisor;
		float bias;
		vector2 kernelOffset;
		bool preserveAlpha;
		BorderMode borderMode;
		bool clampOutput;


	public:
		ConvolveMatrixEffect();
		void SetKernelUnitLength(float);
		void SetScaleMode(ScaleMode);
		void SetKernelSizeX(int);
		void SetKernelSizeY(int);
		void SetKernelMatrix(Matrix3x3);
		void SetDivisor(int);
		void SetBias(float);
		void SetKernelOffset(vector2);
		void SetPreserveAlpha(bool);
		void SetBorderMode(BorderMode);
		void SetClampOutput(bool);
	};