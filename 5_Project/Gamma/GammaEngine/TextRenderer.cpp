#include "stdafx.h"
using namespace GammaEngine;

GammaEngine::TextRenderer::TextRenderer(GameObject* t)
	: Renderer(t),
	isScreen(false)
{
	size = vector2(100, 100);
	text = new wstring();
}

GammaEngine::TextRenderer::~TextRenderer()
{

}

void GammaEngine::TextRenderer::Render()
{
	if (text->length() > 0)
	{
		Matrix3x3 matrix = Matrix3x3::Translation(offset.x, offset.y) * transform->GetWorldMatrix() * Camera::main->Projection();
		if (isScreen)
		{
			matrix = Matrix3x3::Translation(offset.x, offset.y) * transform->GetWorldMatrix();
		}

		GraphicSystem::DrawTextBox(size,matrix, *text, std::wstring(L"Ttangsbudaejjigae OTF"), material);
	}
	
}

void TextRenderer::SetText(std::wstring str)
{
	*text = str;
}
