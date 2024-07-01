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
	class GammaEngineAPI BitmapRenderer : public Renderer
	{
	public:
		BitmapRenderer();
		BitmapRenderer(GameObject* t);
		~BitmapRenderer();

	public:
		virtual void Render() override;
		virtual void SetBrush(vector4) override;

	public:
		void LoadBitmapImage(std::wstring filename);
		void SetFlipX(bool);
		void SetFlipY(bool);
		template<typename T>
		void AddEffect();
		void AddEffect(IEffect*);
		template<typename T>
		T* GetEffect();

		template<typename T>
		void RemoveEffect();
		void RemoveEffect(IEffect*);

	public:
		std::wstring* bitmap;
		std::vector<IEffect*>* appliedEffect;
		bool flipX;
		bool flipY;
		bool isScreen;
	};

	template<typename T>
	void BitmapRenderer::AddEffect()
	{
		T* newEffect = new T();
		appliedEffect->push_back(newEffect);
	}


	template<typename T>
	T* BitmapRenderer::GetEffect()
	{
		for (auto& iter : *appliedEffect)
		{
			T* result = dynamic_cast<T*>(iter);
			auto name1 = typeid(T*).name();
			auto name2 = typeid(result).name();
			if (result && strcmp(name1, name2) == 0)
			{
				return result;
			}
		}
		return nullptr;
	}

	template<typename T>
	void BitmapRenderer::RemoveEffect()
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
