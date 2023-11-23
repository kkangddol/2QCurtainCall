#include "stdafx.h"

using namespace GammaEngine;

GammaEngine::BoxUIElement::BoxUIElement(GameObject* t) : UIElement(t)
{
	bitmap = new std::wstring();
	isEntered = false;
}
	

GammaEngine::BoxUIElement::~BoxUIElement()
{

}

void GammaEngine::BoxUIElement::Update()
{
	if (InBound(Input::GetMousePosition())&& !isEntered)
	{
		OnEnter();
		isEntered = true;
	}
	if (InBound(Input::GetMousePosition()))
	{
		OnHover();
	}
	else if(isEntered)
	{
		OnExit();
		isEntered = false;
	}
}


bool GammaEngine::BoxUIElement::InBound(vector2 v)
{
	std::vector<vector2> V;
	V.push_back(v);
	return GammaPhysics::GJK(GammaPhysics::ComputePoints(size, transform->GetWorldMatrix()), V);
}

void GammaEngine::BoxUIElement::OnExit()
{
	onExitSubject.OnNext(nullptr);
}

void GammaEngine::BoxUIElement::OnEnter()
{
	onEnterSubject.OnNext(nullptr);
}

void GammaEngine::BoxUIElement::OnHover()
{
	onHoverSubject.OnNext(nullptr);
}

void GammaEngine::BoxUIElement::Render()
{
	Matrix3x3 matrix = transform->GetWorldMatrix();
	GraphicSystem::DrawBitmap(*bitmap, size, matrix, material, appliedEffects);
}