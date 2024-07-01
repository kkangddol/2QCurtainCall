#include "stdafx.h"
using namespace GammaEngine;
GammaEngine::PolygonRenderer::PolygonRenderer(GameObject* t) :Renderer(t)
{
	size = vector2(100, 100);
	points = new std::vector<vector2>();
	name = new wstring();
}

GammaEngine::PolygonRenderer::~PolygonRenderer()
{

}

void GammaEngine::PolygonRenderer::Render()
{
    Matrix3x3 matrix = transform->GetWorldMatrix() * Matrix3x3::Translation(offset.x, offset.y) * Camera::main->Projection();
	GraphicSystem::DrawPolygon(*name, matrix, material);
}

void GammaEngine::PolygonRenderer::SetPoints(std::vector<vector2> newPoints)
{
	(* points)=newPoints;
}

void GammaEngine::PolygonRenderer::AddPoints(vector2 point)
{
	points->push_back(point);
}

void GammaEngine::PolygonRenderer::MakePolygon(std::wstring n)
{
	(*name) = GraphicSystem::MakePolygon(n, *points);
}