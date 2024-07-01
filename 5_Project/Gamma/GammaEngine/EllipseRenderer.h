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
	/// Ÿ�� ������
	/// </summary>
	class GammaEngineAPI EllipseRenderer : public Renderer
	{
	public:
		EllipseRenderer(GameObject* t);
		~EllipseRenderer();

	public:
		virtual void Render();
	};
}
