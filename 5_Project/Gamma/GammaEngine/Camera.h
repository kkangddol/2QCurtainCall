#pragma once

#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

class Component;
class Transform;

/// <summary>
/// 카메라 컴포넌트 class
/// </summary>
namespace GammaEngine
{
	class GammaEngineAPI Camera : public Component
	{
	public:
		Camera(GameObject* t);
		virtual ~Camera();

	public:
		vector2 ScreenToWorldPoint(vector2);
		vector2 WorldToScreenPoint(vector2 p);
		vector2 ScreenToWorldScale(vector2 s);
		Matrix3x3 Projection();

	public:
		static Camera* main;
		float orthoScale = 1;
	private:

	};
}
