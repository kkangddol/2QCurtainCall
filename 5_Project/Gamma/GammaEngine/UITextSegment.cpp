#include "stdafx.h"
using namespace GammaEngine;
GammaEngine::UITextSegment::UITextSegment()
{
	text = new std::wstring();
	font = new std::wstring(L"Verdana");
	size = vector2(100, 100);
	material = new Material();
	position = vector2();
	rotation=0;
	scale = vector2();
}


GammaEngine::UITextSegment::~UITextSegment()
{

}

void GammaEngine::UITextSegment::Render(Matrix3x3 uiTransform)
{
	GraphicSystem::DrawTextBox(size, uiTransform*Matrix3x3::Scale(scale.x,scale.y)*Matrix3x3::Rotate(rotation)*Matrix3x3::Translation(position.x,position.y), *text, *font, material);
}