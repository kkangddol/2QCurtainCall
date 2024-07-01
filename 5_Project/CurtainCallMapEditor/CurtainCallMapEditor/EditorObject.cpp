#include "EditorObject.h"
#include "AABB.h"
#include "GameObject.h"
#include "InputSystem.h"
#include "Camera.h"
#include "Debug.h"
#include "EditorManager.h"

EditorObject::EditorObject(GameObject* obj)
	: Component(obj),
	objectID(),
	triggerID(-1),
	reactantID(-1),
	index(),
	linkedIndex(-1),
	linkedObject(nullptr),
	size_(100,100)
{

}

void EditorObject::Update()
{
	std::wstring infoText;
	infoText.append(L"index : ");
	infoText.append(std::to_wstring(index));
	infoText.append(L"\n");
	infoText.append(L"linkedIndex : ");
	if (linkedObject)
	{
		infoText.append(std::to_wstring(linkedObject->GetComponent<EditorObject>()->index));
	}
	infoText.append(L"\n");
	infoText.append(L"x : ");
	infoText.append(std::to_wstring(object_->transform.GetLocalPosition().x));
	infoText.append(L"\n");
	infoText.append(L"y : ");
	infoText.append(std::to_wstring(object_->transform.GetLocalPosition().y));
	infoText.append(L"\n");
	infoText.append(std::to_wstring(object_->GetComponentSize()));
	Debug::DrawTextToWorld(infoText, Vector2D(400, 200), object_->transform.GetLocalPosition() + Vector2D(-50, 50));



	Vector2D thisPos = object_->transform.GetLocalPosition();
	Vector2D screenToWorld = Camera::main->ScreenToWorldPoint(InputSystem::GetMousePosition());

	if (DetectAABB(thisPos.x - size_.x / 2, thisPos.y - size_.y / 2, thisPos.x + size_.x / 2, thisPos.y + size_.y / 2,
		screenToWorld.x, screenToWorld.y, screenToWorld.x, screenToWorld.y))
	{
		HighLight(true);
	}

	//CheckRightClick();
}

void EditorObject::CheckRightClick()
{
	if (InputSystem::GetMouseButtonJustDown(VK_RBUTTON))
	{
		Vector2D pos = object_->transform.GetLocalPosition();
		Vector2D screenToWorld = Camera::main->ScreenToWorldPoint(InputSystem::GetMousePosition());
		if (DetectAABB(pos.x - size_.x / 2, pos.y - size_.y / 2, pos.x + size_.x / 2, pos.y + size_.y / 2,
			screenToWorld.x, screenToWorld.y, screenToWorld.x, screenToWorld.y))
		{
			EditorManager::RightClick(object_);
		}
	}
}

EditorObject* EditorObject::GetLinkedComponent()
{
	if (!linkedObject)
	{
		return nullptr;
	}

	return linkedObject->GetComponent<EditorObject>();
}

void EditorObject::HighLight(bool callLinked)
{
	Debug::DrawRectangleWorld(size_+ Vector2D(10,10), object_->transform.GetLocalPosition(), 0, 1, 1, 0, 1);
	if (callLinked)
	{
		if (linkedObject)
		{
			linkedObject->GetComponent<EditorObject>()->HighLight(false);
		}
	}
}
