#pragma once
#include "GRX.h"
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
	class GammaEngineAPI BoxUIElement abstract: public UIElement
	{
	public:
		BoxUIElement(GameObject * t);
		~BoxUIElement();

	public:
		virtual void Update() final;
		virtual void Render() override;
		virtual bool InBound(vector2);
		virtual void OnExit();
		virtual void OnEnter();
		virtual void OnHover();
	public:
		bool isEntered;
		std::wstring* bitmap;
		Subject<void*> onEnterSubject;
		Subject<void*> onExitSubject;
		Subject<void*> onHoverSubject;
	};
}
