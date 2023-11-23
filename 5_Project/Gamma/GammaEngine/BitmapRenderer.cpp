#include "stdafx.h"

using namespace GammaEngine;
GammaEngine::BitmapRenderer::BitmapRenderer(GameObject* t)
	: Renderer(t),
	isScreen(false)
{
	material->pen = vector4(0, 0, 0, 0);
	material->brush = vector4(1, 1, 1, 1);
	bitmap = new wstring();
	appliedEffect = new std::vector<IEffect*>();
	flipX=false;
	flipY=false;
	AddEffect<TintEffect>();
	GetEffect<TintEffect>()->SetColor(material->brush);
}

GammaEngine::BitmapRenderer::~BitmapRenderer()
{

}

void GammaEngine::BitmapRenderer::LoadBitmapImage(wstring filename)
{
	(* bitmap) = GraphicSystem::LoadBitmapImage(filename);
	size = GraphicSystem::GetBitmapSize(*bitmap);
}

void GammaEngine::BitmapRenderer::SetFlipX(bool val)
{
	flipX = val;
}

void GammaEngine::BitmapRenderer::SetFlipY(bool val)
{
	flipY = val;
}

void GammaEngine::BitmapRenderer::SetBrush(vector4 color)
{
	Renderer::SetBrush(color);
	GetEffect<TintEffect>()->SetColor(material->brush);
}

void GammaEngine::BitmapRenderer::AddEffect(IEffect* effect)
{
	appliedEffect->push_back(effect);
}

void GammaEngine::BitmapRenderer::RemoveEffect(IEffect* effect)
{
	appliedEffect->erase(remove(appliedEffect->begin(), appliedEffect->end(), effect), appliedEffect->end());
}

void GammaEngine::BitmapRenderer::Render()
{
	if (!isEnabled)
	{
		return;
	}

    Matrix3x3 matrix = Matrix3x3::Translation(offset.x, offset.y) * transform->GetWorldMatrix() *  Camera::main->Projection();
	if (isScreen)
	{
		matrix = Matrix3x3::Translation(offset.x, offset.y) * transform->GetWorldMatrix();
	}
	vector2 tmpSize;
	tmpSize.x = flipX ? -size.x : size.x;
	tmpSize.y = flipY ? -size.y : size.y;
	GraphicSystem::DrawBitmap(*bitmap, tmpSize, matrix, material, appliedEffect);
}