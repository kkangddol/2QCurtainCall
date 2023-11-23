#pragma once
#include "Collider.h"

class BoxCollider2D : public Collider
{
public:
	BoxCollider2D(GameObject* obj);

	void SetRect(float left, float top, float right, float bottom)
	{
		left_ = left;
		top_ = top;
		right_ = right;
		bottom_ = bottom;
	}

	float GetLocalLeft() const;
	float GetLocalTop() const;
	float GetLocalRight() const;
	float GetLocalBottom() const;

	float GetWorldLeft() const;
	float GetWorldTop() const;
	float GetWorldRight() const;
	float GetWorldBottom() const;

	Vector2D GetWorldLT() const;
	Vector2D GetWorldRT() const;
	Vector2D GetWorldRB() const;
	Vector2D GetWorldLB() const;

private:
	float left_;
	float top_;
	float right_;
	float bottom_;
};

