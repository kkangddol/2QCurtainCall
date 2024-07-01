#pragma once
#include "Type.h"
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

namespace GammaEngine
{
	/// <summary>
	/// ºñÆ®¸Ê ·»´õ·¯ ÄÄÆ÷³ÍÆ®
	/// </summary>
	class GammaEngineAPI DistantLight : public Light
	{
	public:
		DistantLight(GameObject* t);
		~DistantLight();
		float GetAzimuth();
		void SetAzimuth(float val);
		float GetElvation();
		void SetElvation(float val);
		virtual void dummy();
	public:
		float azimuth;
		float elevation;
	};

}
