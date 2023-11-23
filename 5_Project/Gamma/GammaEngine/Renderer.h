#pragma once
#include <d2d1.h>
#include "Type.h"
#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

using namespace D2D1;

namespace GammaEngine
{
	class Transform;
	class Component;

	/// <summary>
	/// ·»´õ·¯ ÄÄÆ÷³ÍÆ®
	/// </summary>
	class GammaEngineAPI Renderer : public Component
	{
	public:
		Renderer(GameObject* g);
		~Renderer();

	public:
		virtual void Render() abstract;
		void Adjust(vector2& v);
		void Adjust(vector2& pos, vector2& size);

	public:
		virtual void SetBrush(vector4);
		virtual void SetPen(vector4);

	public:
		vector2 size;
		vector2 offset;
		Material* material;
		float order = 0;
	};
}