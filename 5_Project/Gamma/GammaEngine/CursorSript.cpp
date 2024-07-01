#include "stdafx.h"
#include "CursorSript.h"
#include "Box.h"
#include "Circle.h"

CursorSript::CursorSript(GameObject* t):Component(t)
{

}

CursorSript::~CursorSript()
{
}
void CursorSript::Start()
{

}

void CursorSript::Update()
{
	vector2 mousePos = Camera::main->ScreenToWorldPoint(Input::GetMousePosition());
	transform->position = mousePos;

	if (!hover && Input::GetMouseButtonDown(0))
	{
		switch (mode)
		{
		case CreateMode::box :
		{
			GameObject* box = new Box();
			box->transform->position = mousePos;
			Instantiate(box);
			break;
		}
		case CreateMode::circle:
		{
			GameObject* circle = new Circle();
			circle->transform->position = mousePos;
			Instantiate(circle);
			break;
		}
		default:
			break;
		}
	}

	if (hover && Input::GetMouseButtonDown(0))
	{

	}
	if (hover && Input::GetMouseButtonDown(1))
	{
		if (hover == target)
		{
			target = NULL;
		}
		Destroy(hover);
		hover = NULL;
	}

	if (target)
	{
		if (Input::GetKey('W'))
			target->transform->position.y -= targetSpeed * Time::deltaTime;
		if (Input::GetKey('A'))
			target->transform->position.x -= targetSpeed * Time::deltaTime;
		if (Input::GetKey('S'))
			target->transform->position.y += targetSpeed * Time::deltaTime;
		if (Input::GetKey('D'))
			target->transform->position.x += targetSpeed * Time::deltaTime;
		if (Input::GetKey('Q'))
			target->transform->rotation -= targetRotateSpeed * Time::deltaTime;
		if (Input::GetKey('E'))
			target->transform->rotation += targetRotateSpeed * Time::deltaTime;
	}



	if (Input::GetKeyDown(VK_SPACE))
	{
		switch (mode)
		{
		case CreateMode::box:
			mode = CreateMode::circle;
			break;
		case CreateMode::circle:
			mode = CreateMode::box;
			break;
		default:
			break;
		}
	}
	hover = NULL;
}

void CursorSript::OnCollisionStay(CollisionResponse response)
{
	hover = response.other->gameObject;
}