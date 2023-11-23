#pragma once
#include "Type.h"
#include <map>
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif
namespace GammaEngine
{
	class Renderer;
	class Transform;
	class Letter;

	/// <summary>
	/// ºñÆ®¸Ê ·»´õ·¯ ÄÄÆ÷³ÍÆ®
	/// </summary>
	class GammaEngineAPI TextAnimationRenderer : public Renderer
	{
	public:
		TextAnimationRenderer(GameObject* t);
		~TextAnimationRenderer();

	public:
		virtual void Render();
		virtual void Update();
		std::vector<Letter>* letter;
		std::wstring* text;
		float letterOffset;

	public:
		void SetText(std::wstring);
	public:
		bool isScreen;

	};
}
