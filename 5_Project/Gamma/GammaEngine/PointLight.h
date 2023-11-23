#pragma once
#include "Type.h"
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

class Effect;
namespace GammaEngine
{
	class Renderer;
	class Transform;

	/// <summary>
	/// ºñÆ®¸Ê ·»´õ·¯ ÄÄÆ÷³ÍÆ®
	/// </summary>
	class GammaEngineAPI PointLight : public Light
	{
	public:
		PointLight(GameObject* t);
		~PointLight();
		void SetZ(float);
		float GetZ();
		virtual void dummy();
	public:
		float z;
	};

}
