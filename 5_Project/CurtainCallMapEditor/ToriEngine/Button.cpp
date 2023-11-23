#include "Button.h"

#include "InputSystem.h"
#include "GameObject.h"
#include "AABB.h"
#include "Debug.h"
#include "Camera.h"

Button::Button(GameObject* obj)
	: Component(obj),
	order_(0),
	size_(100, 100),
	bitmap_(),
	isLeftHold_(false), isRightHold_(false),
	isLeft_(false), isRight_(false)
{

}

void Button::Update()
{
	//Debug::DrawRectangleScreen(size_, object_->transform.GetLocalPosition(), object_->transform.GetLocalEulerAngle(), 1, 0, 1, 1);

	isLeft_ = false;
	isRight_ = false;

	if (InputSystem::GetMouseButtonJustDown(VK_LBUTTON))
	{
		Vector2D buttonPos = object_->transform.GetLocalPosition();
		Vector2D mouseScreenPos = InputSystem::GetMousePosition();
		if (DetectAABB(buttonPos.x - size_.x / 2, buttonPos.y - size_.y / 2, buttonPos.x + size_.x / 2, buttonPos.y + size_.y / 2,
			mouseScreenPos.x, mouseScreenPos.y, mouseScreenPos.x, mouseScreenPos.y))
		{
			if (InputSystem::CompareOrder(this))
			{
				isLeftHold_ = true;
				InputSystem::isButtonHold = true;
			}
		}
	}

	if (InputSystem::GetMouseButtonJustDown(VK_RBUTTON))
	{
		Vector2D buttonPos = object_->transform.GetLocalPosition();
		Vector2D mouseScreenPos = InputSystem::GetMousePosition();
		if (DetectAABB(buttonPos.x - size_.x / 2, buttonPos.y - size_.y / 2, buttonPos.x + size_.x / 2, buttonPos.y + size_.y / 2,
			mouseScreenPos.x, mouseScreenPos.y, mouseScreenPos.x, mouseScreenPos.y))
		{
			if (InputSystem::CompareOrder(this))
			{
				isRightHold_ = true;
				InputSystem::isButtonHold = true;
			}
		}
	}

	if (InputSystem::GetMouseButtonJustUp(VK_LBUTTON))
	{
		Vector2D buttonPos = object_->transform.GetLocalPosition();
		Vector2D mouseScreenPos = InputSystem::GetMousePosition();
		if (DetectAABB(buttonPos.x - size_.x / 2, buttonPos.y - size_.y / 2, buttonPos.x + size_.x / 2, buttonPos.y + size_.y / 2,
			mouseScreenPos.x, mouseScreenPos.y, mouseScreenPos.x, mouseScreenPos.y))
		{
			if (isLeftHold_)
			{
				isLeft_ = true;
			}
		}

		isLeftHold_ = false;
		InputSystem::isButtonHold = false;
	}

	if (InputSystem::GetMouseButtonJustUp(VK_RBUTTON))
	{
		Vector2D buttonPos = object_->transform.GetLocalPosition();
		Vector2D mouseScreenPos = InputSystem::GetMousePosition();
		if (DetectAABB(buttonPos.x - size_.x / 2, buttonPos.y - size_.y / 2, buttonPos.x + size_.x / 2, buttonPos.y + size_.y / 2,
			mouseScreenPos.x, mouseScreenPos.y, mouseScreenPos.x, mouseScreenPos.y))
		{
			if (isRightHold_)
			{
				isRight_ = true;
			}
		}

		isRightHold_ = false;
		InputSystem::isButtonHold = false;
	}
}

void Button::SetOnLeftClickEvent(std::function<void()> onClickEvent)
{
	onLeftClickEvent_.swap(onClickEvent);
}

void Button::SetOnRightClickEvent(std::function<void()> onClickEvent)
{
	onRightClickEvent_.swap(onClickEvent);
}

void Button::OnLeftClick()
{
	onLeftClickEvent_();
}

void Button::OnRightClick()
{
	onRightClickEvent_();
}

void Button::SetOrder(int order)
{
	order_ = order;
}

void Button::SetButtonSize(float x, float y)
{
	size_.x = x;
	size_.y = y;
}

bool Button::IsLeft() const
{
	return isLeft_;
}

bool Button::IsRight() const
{
	return isRight_;
}

