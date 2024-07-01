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
	/// �簢�� ������
	/// </summary>
	class GammaEngineAPI RectangleRenderer : public Renderer
	{
	public:
		RectangleRenderer(GameObject* g);
		~RectangleRenderer();

	public:
		virtual void Render();
		void SetSize(vector2);
	};
}