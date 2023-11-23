#define _USE_MATH_DEFINES
#include <math.h>

#include <list>

#include <string>

#include "ToriD2D.h"

#include "ObjectSystem.h"
#include "SceneSystem.h"
#include "RenderSystem.h"
#include "GameObject.h"

#include "CircleCollider2D.h"
#include "BoxCollider2D.h"
#include "Camera.h"

#include "Debug.h"

std::vector<DebugText*> Debug::textBoxes;
std::vector<DebugRect*> Debug::rects;

Debug::Debug()
{
	textBoxes.clear();
	rects.clear();
}

Debug::~Debug()
{
	for (auto debugText : textBoxes)
	{
		delete debugText;
	}

	for (auto rect : rects)
	{
		delete rect;
	}
}

/// <summary>
/// 콜라이더의 모양을 출력한다.		(O)
///	2023.01.21 강석원 집
/// 
/// fps, deltatime 을 출력한다.		(X)
/// 오브젝트의 좌표를 출력한다.		(X)
/// 콜라이더의 좌표를 출력한다.		(X)
/// 리지드바디의 속도를 출력한다.		(X)
/// </summary>
void Debug::BruteRender()
{
	if (!isDebugMode_)
	{
		return;
	}

	ObjectSystem& OS = ObjectSystem::Instance();
	SceneSystem& CS = SceneSystem::Instance();
	std::list<GameObject*>& objects = OS.GetCurrentSceneObjects(CS.GetCurrentScene());

	for (auto object : objects)
	{
		Collider* col = object->GetComponent<CircleCollider2D>();
		if (col != nullptr)
		{
			Vector2D pos = ((CircleCollider2D*)col)->GetWorldPosition();
			float radius = ((CircleCollider2D*)col)->GetRadiusRelative();

			ToriD2D::Instance().SetBrushColor(1, 0, 1, 1);
			ToriD2D::Instance().DrawCircle(pos.x, pos.y, radius);

			continue;
		}
		
		col = object->GetComponent<BoxCollider2D>();
		if (col != nullptr)
		{
			float left = ((BoxCollider2D*)col)->GetLocalLeft();
			float top = ((BoxCollider2D*)col)->GetLocalTop();
			float right = ((BoxCollider2D*)col)->GetLocalRight();
			float bottom = ((BoxCollider2D*)col)->GetLocalBottom();

			ToriD2D::Instance().SetBrushColor(1, 0, 1, 1);
			ToriD2D::Instance().DrawRectST(
				left, top, right, bottom,
				((BoxCollider2D*)col)->GetWorldPosition().x,
				((BoxCollider2D*)col)->GetWorldPosition().y,
				((BoxCollider2D*)col)->GetWorldRotation() * 180.0f / M_PI,
				((BoxCollider2D*)col)->GetWorldScale().x,
				((BoxCollider2D*)col)->GetWorldScale().y
				);

			continue;
		}
	}
}

void Debug::Render()
{
	for (auto& textBox : textBoxes)
	{
		RenderSystem::DrawText2D(textBox->text, textBox->size.x, textBox->size.y, textBox->matrix);
	}

	for (auto& rect : rects)
	{
		RenderSystem::SetBrushColor(rect->r, rect->g, rect->b, rect->a);
		RenderSystem::DrawRect(rect->size, rect->matrix);
	}

	textBoxes.clear();
	rects.clear();
}

void Debug::DrawTextToWorld(std::wstring text, Vector2D size, Vector2D pos)
{
	Matrix3x3 matrix = Matrix3x3::Scale(1, 1) * Matrix3x3::Translation(pos.x, pos.y) * Camera::main->Projection();
	DebugText* debugText = new DebugText(text, size, matrix);
	textBoxes.push_back(debugText);
}

void Debug::DrawTextToScreen(std::wstring text, Vector2D size, Vector2D pos)
{
	Matrix3x3 matrix = Matrix3x3::Scale(1, 1) * Matrix3x3::Translation(pos.x, pos.y);
	DebugText* debugText = new DebugText(text, size, matrix);
	textBoxes.push_back(debugText);
}

void Debug::DrawRectangleWorld(Vector2D size, Vector2D pos, float rotation, float r, float g, float b, float a)
{
	Matrix3x3 matrix = Matrix3x3::Scale(1, 1) * 
		Matrix3x3::Rotate(rotation) * 
		Matrix3x3::Translation(pos.x, pos.y) * Camera::main->Projection();
	DebugRect* debugRect = new DebugRect(size, matrix,r,g,b,a);
	rects.push_back(debugRect);
}

void Debug::DrawRectangleScreen(Vector2D size, Vector2D pos, float rotation, float r, float g, float b, float a)
{
	Matrix3x3 matrix = Matrix3x3::Scale(1, 1) *
		Matrix3x3::Rotate(rotation) *
		Matrix3x3::Translation(pos.x, pos.y);
	DebugRect* debugRect = new DebugRect(size, matrix, r, g, b, a);
	rects.push_back(debugRect);
}
