#pragma once

#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

/// <summary>
/// 박스 형태의 UI 상위 계층 클래스
/// </summary>
namespace GammaEngine
{
	class GammaEngineAPI UIPanel : public BoxUIElement
	{
	public:
		UIPanel(GameObject* t);
		~UIPanel();
	};
}
