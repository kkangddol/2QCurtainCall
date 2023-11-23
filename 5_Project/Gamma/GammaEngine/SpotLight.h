#pragma once
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
	class GammaEngineAPI SpotLight : public Light
	{
	public:
		SpotLight(GameObject* t);
		~SpotLight();
		void SetZ(float);
		float GetZ();
		vector3 GetAt();
		void SetAt(vector3);
		float GetFocus();
		void SetFocus(float);	
		float GetConeAngle();
		void SetConeAngle(float);
		virtual void dummy();

	public:
		vector3 at;
		float focus;
		float ConeAngle;
		float z;
	};

}
