#pragma once

#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

/// <summary>
/// UI 최상위 추상화 계층
/// </summary>
namespace GammaEngine
{
	class GammaEngineAPI UIElement abstract : public Component
	{
	public:
		UIElement(GameObject* t);
		~UIElement();

	public:
		virtual void Render();
		virtual void Update();

	public:
		virtual bool InBound(vector2);

	public:
		vector2 size;
		Material* material;
		std::vector<IEffect*>* appliedEffects;
	};
}
