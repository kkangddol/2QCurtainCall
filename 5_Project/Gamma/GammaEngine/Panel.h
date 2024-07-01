#pragma once

#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

/// <summary>
/// 카메라 컴포넌트 class
/// </summary>
namespace GammaEngine
{
	class GammaEngineAPI Panel : public UIElement
	{
	public:
		Panel(GameObject * t);
		~Panel();

	public:
		virtual void Update();

	public:
	};
}
