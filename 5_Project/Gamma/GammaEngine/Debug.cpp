#include "stdafx.h"

using namespace GammaEngine;


std::vector<GammaEngine::DebugRect*>* GammaEngine::Debug::rect;
std::vector<GammaEngine::DebugEllipse*>* GammaEngine::Debug::ellipse;
std::vector<GammaEngine::DebugLine*>* GammaEngine::Debug::line;
std::vector<GammaEngine::DebugText*>* GammaEngine::Debug::textBox;


std::unordered_map<vector4,Material*>* GammaEngine::Debug::material;
bool GammaEngine::Debug::isDebugMode_ = false;

GammaEngine::Debug::Debug()
{
	rect = new std::vector<DebugRect*>();
	ellipse = new std::vector<DebugEllipse*>();
	line = new std::vector<DebugLine*>();
	textBox = new std::vector<DebugText*>();
	material = new std::unordered_map<vector4, Material*>();
}

GammaEngine::Debug::~Debug()
{

}

void GammaEngine::Debug::DrawRectangle(vector2 size, vector2 pos, float rotation, vector4 color)
{
	Matrix3x3 matrix = Matrix3x3::Scale(1, 1) * Matrix3x3::Rotate(rotation) * Matrix3x3::Translation(pos.x, pos.y) * Camera::main->Projection();
	DebugRect* debugShape = new DebugRect(size, matrix, GetMaterial(color));
	rect->push_back(debugShape);
}

void GammaEngine::Debug::DrawEllipse(vector2 size, vector2 pos, float rotation, vector4 color)
{
    Matrix3x3 matrix = Matrix3x3::Scale(1, 1) * Matrix3x3::Rotate(rotation) * Matrix3x3::Translation(pos.x, pos.y) * Matrix3x3::Scale(1, 1) * Camera::main->Projection();
	DebugEllipse* debugShape = new DebugEllipse(size, matrix, GetMaterial(color));
	ellipse->push_back(debugShape);
}

void GammaEngine::Debug::DrawLine(vector2 start, vector2 end,Matrix3x3 matrix, vector4 color)
{
	DebugLine* debugShape = new DebugLine(start, end, matrix * Camera::main->Projection(), GetMaterial(color));
	line->push_back(debugShape);
}

void GammaEngine::Debug::DrawTextToWorld(vector2 size, vector2 pos, std::wstring text, std::wstring fontFamily, vector4 color)
{
    Matrix3x3 matrix = Matrix3x3::Scale(1, 1) * Matrix3x3::Translation(pos.x, pos.y) * Camera::main->Projection();
	DebugText* debugShape = new DebugText(size, matrix, text, fontFamily, GetMaterial(color));
	textBox->push_back(debugShape);
}

void GammaEngine::Debug::DrawTextToScreen(vector2 size, vector2 pos, std::wstring text, std::wstring fontFamily, vector4 color)
{
	DebugText* debugShape = new DebugText(size, Matrix3x3::Translation(pos.x, pos.y), text, fontFamily, GetMaterial(color));
	textBox->push_back(debugShape);
}

Material* GammaEngine::Debug::GetMaterial(vector4 color)
{
	if ((*material)[color] == nullptr)
	{
		(*material)[color] = new Material(color);
	}
	return (*material)[color];
}

void GammaEngine::Debug::Render()
{
	if (isDebugMode_)
	{
		for (auto iter = rect->begin(); iter != rect->end(); iter++)
		{
			DebugRect* debugShape = *iter;
			GraphicSystem::DrawRectangle(debugShape->size, debugShape->matrix, debugShape->material);
		}

		for (auto iter = ellipse->begin(); iter != ellipse->end(); iter++)
		{
			DebugEllipse* debugShape = *iter;
			GraphicSystem::DrawEllipse(debugShape->size, debugShape->matrix, debugShape->material);
		}

		for (auto iter = line->begin(); iter != line->end(); iter++)
		{
			DebugLine* debugShape = *iter;
			GraphicSystem::DrawLine(debugShape->start, debugShape->end, debugShape->matrix, debugShape->material);
		}

		for (auto iter = textBox->begin(); iter != textBox->end(); iter++)
		{
			DebugText* debugShape = *iter;
			GraphicSystem::DrawTextBox(debugShape->size, debugShape->matrix, debugShape->text, debugShape->fontFamily, debugShape->material);
		}
	}

	for (auto iter = rect->begin(); iter != rect->end(); iter++)
	{
		delete* iter;
	}

	for (auto iter = ellipse->begin(); iter != ellipse->end(); iter++)
	{
		delete* iter;
	}

	for (auto iter = line->begin(); iter != line->end(); iter++)
	{
		delete* iter;
	}

	for (auto iter = textBox->begin(); iter != textBox->end(); iter++)
	{
		delete* iter;
	}

	rect->clear();
	ellipse->clear();
	line->clear();
	textBox->clear();

}

void Debug::SetDebugMode(bool mode)
{
	isDebugMode_ = mode;
}

void Debug::SetDebugMode()
{
	isDebugMode_ = !isDebugMode_;
}


