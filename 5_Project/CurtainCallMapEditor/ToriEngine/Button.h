#pragma once
#include <string>
#include <functional>

#include "Component.h"
#include "Vector2D.h"

class GameObject;

class Button : public Component
{
public:
	Button(GameObject* obj);

	virtual void Update() override;

public:
	//void Check
	void SetOnLeftClickEvent(std::function<void()> onClickEvent);
	void SetOnRightClickEvent(std::function<void()> onClickEvent);
	void OnLeftClick();
	void OnRightClick();

public:
	bool operator<(const Button& rhs)
	{
		return order_ < rhs.order_;
	}

	bool operator>(const Button& rhs)
	{
		return order_ > rhs.order_;
	}

public:
	void SetOrder(int order);
	void SetButtonSize(float x, float y);
	bool IsLeft() const;
	bool IsRight() const;

private:
	int order_;
	Vector2D size_;
	std::wstring bitmap_;
	std::function<void()> onLeftClickEvent_;
	std::function<void()> onRightClickEvent_;
	bool isLeftHold_;
	bool isRightHold_;
	bool isLeft_;
	bool isRight_;
};

