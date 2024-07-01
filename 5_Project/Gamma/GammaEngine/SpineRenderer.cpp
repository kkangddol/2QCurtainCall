#include "stdafx.h"
#pragma comment (lib, "windowscodecs.lib")
using namespace GammaEngine;
GammaEngine::SpineRenderer::SpineRenderer(GameObject* t) :Renderer(t)
{
	material->pen = vector4(0, 0, 0, 0);
	material->brush = vector4(1, 1, 1, 1);
	flipX = false;
	flipY = false;
	appliedEffect = new std::vector<IEffect*>();
	AddEffect<TintEffect>();
	GetEffect<TintEffect>()->SetColor(material->brush);
}

GammaEngine::SpineRenderer::~SpineRenderer()
{

}

void GammaEngine::SpineRenderer::LoadSpineModel(std::string name, std::string atlasName, std::string jsonName)
{
	model = SpineModel::Create(name, atlasName, jsonName);
}

void GammaEngine::SpineRenderer::SetFlipX(bool val)
{
	flipX = val;
}

void GammaEngine::SpineRenderer::SetFlipY(bool val)
{
	flipY = val;
}

void GammaEngine::SpineRenderer::AddEffet(IEffect* effect)
{
	appliedEffect->push_back(effect);
}

void GammaEngine::SpineRenderer::Render()
{
	vector2 tmpSize;
	tmpSize.x = flipX ? -1 : 1;
	tmpSize.y = flipY ? -1 : 1;
	Matrix3x3 matrix = Matrix3x3::Scale(tmpSize.x, tmpSize.y) * Matrix3x3::Translation(offset.x, offset.y) * transform->GetWorldMatrix() * Camera::main->Projection();
	if (isEnabled && model)
	{
		model->Render(matrix, material, appliedEffect);
	}
}

void GammaEngine::SpineRenderer::Update()
{
 	if (model)
	{
		model->Update();
	}
}