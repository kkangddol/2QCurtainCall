#include "Dragable.h"
#include "InputSystem.h"
#include "EditorManager.h"
#include "Camera.h"
#include "GameObject.h"
#include "Debug.h"
#include "AABB.h"

Dragable::Dragable(GameObject* obj)
	: Component(obj),
	order_(0),
	size_(100,100),
	offSet_(),
	isDragging_(false)
{
	//EditorManager::AddToList(object_);
}

Dragable::~Dragable()
{
	EditorManager::RemoveFromList(object_);
}

void Dragable::Update()
{
	Debug::DrawRectangleWorld(size_, object_->transform.GetLocalPosition(), object_->transform.GetLocalEulerAngle(), 0, 0, 1, 1);

	if (isDragging_)
	{
		FollowMouse();
	}

	CheckDrag();
}

void Dragable::StartDrag()
{
	if (isDragging_)
	{
		return;
	}

	isDragging_ = true;
	EditorManager::SetDragObject(object_);
}

void Dragable::EndDrag()
{
	if (!isDragging_)
	{
		return;
	}

	isDragging_ = false;
	offSet_.x = 0;
	offSet_.y = 0;
	EditorManager::EndDrag();
}

void Dragable::FollowMouse()
{
	Vector2D mousePos(Camera::main->ScreenToWorldPoint(InputSystem::GetMousePosition()));
	object_->transform.SetLocalPosition(mousePos + offSet_);
}

void Dragable::CheckDrag()
{
	if (InputSystem::GetMouseButtonJustUp(VK_LBUTTON) && isDragging_)
	{
		EndDrag();
	}

	if (EditorManager::GetDragObject())
	{
		return;
	}

	if (InputSystem::GetMouseButtonHold(VK_LBUTTON) && !isDragging_)
	{
		Vector2D dragablePos = object_->transform.GetLocalPosition();
		Vector2D screenToWorld = Camera::main->ScreenToWorldPoint(InputSystem::GetMousePosition());
		if (DetectAABB(dragablePos.x - size_.x / 2, dragablePos.y - size_.y / 2, dragablePos.x + size_.x / 2, dragablePos.y + size_.y / 2,
			screenToWorld.x, screenToWorld.y, screenToWorld.x, screenToWorld.y))
		{
			offSet_ = object_->transform.GetLocalPosition() - screenToWorld;
			StartDrag();
		}
	}
}
