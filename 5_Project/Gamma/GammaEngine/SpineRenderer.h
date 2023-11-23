#pragma once
#include "Type.h"
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif
namespace GammaEngine
{
	class Renderer;
	class Transform;
	class SpineModel;
	/// <summary>
	/// ºñÆ®¸Ê ·»´õ·¯ ÄÄÆ÷³ÍÆ®
	/// </summary>
	class GammaEngineAPI SpineRenderer : public Renderer
	{
	public:
		SpineRenderer();
		SpineRenderer(GameObject* t);
		~SpineRenderer();

	public:
		virtual void Render();
		virtual void Update();
		void LoadSpineModel(std::string,std::string,std::string);

	public:
		void SetFlipX(bool);
		void SetFlipY(bool);
		template<typename T>
		void AddEffect();
		void AddEffet(IEffect*);
		template<typename T>
		T* GetEffect();
		template<typename T>
		void RemoveEffect();

	public:
		bool flipX;
		bool flipY;
		SpineModel* model;
		std::vector<IEffect*>* appliedEffect;
	};

	template<typename T>
	void SpineRenderer::AddEffect()
	{
		T* newEffect = new T();
		appliedEffect->push_back(newEffect);
	}

	template<typename T>
	T* SpineRenderer::GetEffect()
	{
		for (auto iter = appliedEffect->begin(); iter < appliedEffect->end(); iter++)
		{
			if (strcmp(typeid(T).name(), typeid(**iter).name()) == 0)
				return (T*)*iter;
		}
	}

	template<typename T>
	void SpineRenderer::RemoveEffect()
	{
		appliedEffect->erase(remove_if(appliedEffect->begin(), appliedEffect->end(), [](IEffect* x) {
			if (strcmp(typeid(T).name(), typeid(*x).name()) == 0)
			{
				delete x;
				return true;
			}
			}), appliedEffect->end());
	}
}
