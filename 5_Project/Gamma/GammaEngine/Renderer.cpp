#include "stdafx.h"

using namespace GammaEngine;
GammaEngine::Renderer::Renderer(GameObject* t) : Component(t)
{
	GraphicSystem* graphic = GraphicSystem::Instance();
	graphic->renderComponentList->push_back(this);
	size = vector2();
	offset = vector2();
	material = new Material();
}

GammaEngine::Renderer::~Renderer()
{
	GraphicSystem* graphic = GraphicSystem::Instance();
	graphic->renderComponentList->erase(remove_if(graphic->renderComponentList->begin(), graphic->renderComponentList->end(), [this](Component* x) { if (x == this) return true; else return false; }), graphic->renderComponentList->end());
}

void GammaEngine::Renderer::SetBrush(vector4 color)
{
	material->brush = color;
}

void GammaEngine::Renderer::SetPen(vector4 color)
{
	material->pen = color;
}


void GammaEngine::Renderer::Adjust(vector2& v)
{
	if (Camera::main)
	{
		vector2 center = vector2((float)Screen::width / 2, (float)Screen::height / 2) - Camera::main->transform->GetWorldPosition();

		v = v / Camera::main->orthoScale + center;
	}
	else
	{
		v = v + vector2((float)Screen::width / 2, (float)Screen::height / 2);
	}
}

void GammaEngine::Renderer::Adjust(vector2& pos,vector2& size)
{
	if (Camera::main)
	{
		vector2 center = vector2((float)Screen::width / 2, (float)Screen::height / 2) - Camera::main->transform->GetWorldPosition();
			
		pos = pos / Camera::main->orthoScale + center;
		

		size = size / Camera::main->orthoScale;
	}
	else
	{
		pos = pos + vector2((float)Screen::width / 2, (float)Screen::height / 2);
	}
}