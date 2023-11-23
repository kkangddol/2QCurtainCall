#include "stdafx.h"

using namespace GammaEngine;

GammaEngine::RectangleRenderer::RectangleRenderer(GameObject* t) :Renderer(t)
{
	size = vector2(100, 100);
}

GammaEngine::RectangleRenderer::~RectangleRenderer()
{

}

void GammaEngine::RectangleRenderer::Render()
{
	Matrix3x3 matrix = transform->GetWorldMatrix()  * Matrix3x3::Translation(offset.x, offset.y) *Camera::main->Projection();
	GraphicSystem::DrawRectangle(size, matrix, material);
}

void GammaEngine::RectangleRenderer::SetSize(vector2 val)
{
	size = val;
}