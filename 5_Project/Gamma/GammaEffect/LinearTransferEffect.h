#pragma once


	class LinearTransferEffect : public Effect
	{
	public:
		vector4 intercept;
		vector4 slope;
		bool disableRed;
		bool disableBlue;
		bool disableGreen;
		bool disableAlpha;
		bool clampOutput;
	public:
		void SetIntercept(vector4);
		void SetSlope(vector4);
		void SetDisableRed(bool);
		void SetDisableBlue(bool);
		void SetDisableGreen(bool);
		void SetDisableAlpha(bool);
		void SetClampOutput(bool);
	};

