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

	/// <summary>
	/// direct2d 화면에 텍스트를 출력하는 컴포넌트
	/// </summary>
	class GammaEngineAPI TextRenderer : public Renderer
	{
	public:
		TextRenderer(GameObject* t);
		~TextRenderer();
		virtual void Render();

	public:
		void SetText(std::wstring str);

	public:
		std::wstring* text;
		//std::wstring* font;
		bool isScreen;

	private:

	};

}
