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
	/// 사각형 렌더러
	/// </summary>
	class GammaEngineAPI PolygonRenderer : public Renderer
	{
	public:
		PolygonRenderer(GameObject* g);
		~PolygonRenderer();

	public:
		virtual void Render();

	public:
		void SetPoints(std::vector<vector2>);
		void AddPoints(vector2);
		void MakePolygon(std::wstring name);

	public:
		std::vector<vector2>* points;
		std::wstring* name;
	};
}