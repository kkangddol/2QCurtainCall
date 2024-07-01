#include <string>

#include "Component.h"
#include "MainCamera.h"

#include "Debug.h"
#include "GameObject.h"
#include "Vector2D.h"
#include "InputSystem.h"
#include "TimeSystem.h"
#include "Camera.h"

MainCamera::MainCamera(GameObject* obj)
	: Component(obj)
{

}

MainCamera::~MainCamera()
{

}

void MainCamera::Update()
{
	std::wstring debugText;
	debugText.append(L"x:");
	debugText.append(std::to_wstring(object_->transform.GetLocalPosition().x));
	debugText.append(L"\ny:");
	debugText.append(std::to_wstring(object_->transform.GetLocalPosition().y));
	Debug::DrawTextToScreen(debugText, Vector2D(200, 100), Vector2D(0,100));

	std::wstring deltaTime;
	deltaTime.append(L"deltaTime : ");
	deltaTime.append(std::to_wstring(TimeSystem::GetDeltaTime()));
	Debug::DrawTextToScreen(deltaTime, Vector2D(300, 100), Vector2D(0,200));

	std::wstring frame;
	frame.append(L"frame : ");
	frame.append(std::to_wstring(TimeSystem::GetFrameRate()));
	Debug::DrawTextToScreen(frame, Vector2D(300, 100), Vector2D(0, 250));

	std::wstring mousePos;
	mousePos.append(L"mouseX : ");
	mousePos.append(std::to_wstring(Camera::main->ScreenToWorldPoint(InputSystem::GetMousePosition()).x));
	mousePos.append(L"\n");
	mousePos.append(L"mouseY : ");
	mousePos.append(std::to_wstring(Camera::main->ScreenToWorldPoint(InputSystem::GetMousePosition()).y));
	Debug::DrawTextToScreen(mousePos, Vector2D(400, 200), Vector2D(0, 350));

	if (InputSystem::mouseScrollDelta > 0)
	{
		Camera::main->orthoScale -= 0.1f;
	}
	if (InputSystem::mouseScrollDelta < 0)
	{
		Camera::main->orthoScale += 0.1f;
	}

	if (InputSystem::GetKeyHold('A'))
	{
		object_->transform.Translate(-speed * TimeSystem::GetDeltaTime(), 0);
	}

	if (InputSystem::GetKeyHold('W'))
	{
		object_->transform.Translate(0, -speed * TimeSystem::GetDeltaTime());
	}

	if (InputSystem::GetKeyHold('D'))
	{
		object_->transform.Translate(speed * TimeSystem::GetDeltaTime(), 0);
	}

	if (InputSystem::GetKeyHold('S'))
	{
		object_->transform.Translate(0, speed * TimeSystem::GetDeltaTime());
	}


// 	if (maxPositionX < transform->position.x)
// 	{
// 		GetComponent<Camera>()->transform->position.x = maxPositionX;
// 	}
// 	else if (-maxPositionX > transform->position.x)
// 	{
// 		GetComponent<Camera>()->transform->position.x = -maxPositionX;
// 	}
// 
// 
// 	if (maxPositionY < transform->position.y)
// 	{
// 		GetComponent<Camera>()->transform->position.y = maxPositionY;
// 	}
// 	else if (-maxPositionY > transform->position.y)
// 	{
// 		GetComponent<Camera>()->transform->position.y = -maxPositionY;
// 	}


// 	if ((distance * coefficient) / GetComponent<Camera>()->orthoScale > fixBoundary + padding)
// 	{
// 		if (GetComponent<Camera>()->orthoScale < maxScale)
// 		{
// 			GetComponent<Camera>()->orthoScale += zoomStep;
// 		}
// 	}
// 	else if ((distance * coefficient) / GetComponent<Camera>()->orthoScale < fixBoundary - padding)
// 	{
// 		if (GetComponent<Camera>()->orthoScale > minScale)
// 		{
// 			GetComponent<Camera>()->orthoScale -= zoomStep;
// 		}
// 	}
}