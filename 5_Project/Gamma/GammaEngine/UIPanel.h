#pragma once

#ifdef GammaEngineAPI_Exporting
#define GammaEngineAPI __declspec(dllexport)
#else
#define GammaEngineAPI __declspec(dllimport)
#endif

/// <summary>
/// �ڽ� ������ UI ���� ���� Ŭ����
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
