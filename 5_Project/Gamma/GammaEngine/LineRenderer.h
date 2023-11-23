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
	/// ∂Û¿Œ ∑ª¥ı∑Ø
	/// </summary>
	class GammaEngineAPI LineRenderer : public Renderer
	{
	public:
		LineRenderer(GameObject* t);
		~LineRenderer();

	public:
		virtual void Render();

	public:
		vector2 src;
		vector2 dst;
		float thickness = 0.5f;
	};
}