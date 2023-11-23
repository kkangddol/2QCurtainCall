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
	class GammaEngineAPI LightAdapter : public Component
	{
	public:
		LightAdapter(GameObject* t);
		virtual ~LightAdapter();
		virtual void Start();
		virtual void Update();
		void AddLight(Light*);

	public:
		std::unordered_map<Light*, IEffect*> effectList;
	};

}
