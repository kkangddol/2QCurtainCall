#include "stdafx.h"
using namespace GammaEngine;



GammaEngine::TextAnimationRenderer::TextAnimationRenderer(GameObject* t) :Renderer(t)
{
	material->pen = vector4(0, 0, 0, 1);
	material->brush = vector4(1, 1, 1, 1);
	order = 10;
	letter = new std::vector<Letter>();
	letterOffset = 30.0f;
	isScreen = false;
}

GammaEngine::TextAnimationRenderer::~TextAnimationRenderer()
{

}

void GammaEngine::TextAnimationRenderer::SetText(std::wstring str)
{
	text = new std::wstring(str);

	letter->clear();

	for (int i = 0; i < text->size(); i++)
	{
		Letter l_ = Letter((*text)[i]);
		l_.transform.position.x = letterOffset * i;
		letter->push_back(l_);
		
	}
}


void GammaEngine::TextAnimationRenderer::Render()
{
	Matrix3x3 matrix = transform->GetWorldMatrix() * Matrix3x3::Translation(offset.x, offset.y);

	for (auto seg : *letter)
	{
		Matrix3x3 localMatrix = matrix*seg.transform.GetLocalMatrix()* Camera::main->Projection();
		if (isScreen)
		{
			localMatrix = matrix * seg.transform.GetLocalMatrix();
		}

		wchar_t str[2];
		str[0]= seg.value;
		str[1] = '\0';

		GraphicSystem::DrawTextBox(vector2(5, 5), localMatrix, str, std::wstring(L"Ttangsbudaejjigae OTF"), &(seg.material));
	}
}


void GammaEngine::TextAnimationRenderer::Update()
{
	
}