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
	class GammaEngineAPI Light : public Component
	{
	public:
		Light(GameObject* t);
		~Light();
	public:
		float GetMagnitude();
		void SetMagnitude(float);
		vector3 GetColor();
		void SetColor(vector3);
		virtual void dummy() abstract;
	public:
		float magnitude;
		vector3 color;
	
	public:

	};

}
