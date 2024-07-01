#include "BoxCollider2D.h"
#include "Vector2D.h"

BoxCollider2D::BoxCollider2D(GameObject* object)
	: Collider(object, ColliderType::RECTANGLE), left_(-5),top_(-5),right_(5),bottom_(5)
{

}

float BoxCollider2D::GetLocalLeft() const
{
	return left_;
}

float BoxCollider2D::GetLocalTop() const
{
	return top_;
}

float BoxCollider2D::GetLocalRight() const
{
	return right_;
}

float BoxCollider2D::GetLocalBottom() const
{
	return bottom_;
}

float BoxCollider2D::GetWorldLeft() const
{
	return left_ * GetWorldScale().x + GetWorldPosition().x;
}

float BoxCollider2D::GetWorldTop() const
{
	return top_ * GetWorldScale().y + GetWorldPosition().y;
}

float BoxCollider2D::GetWorldRight() const
{
	return right_ * GetWorldScale().x + GetWorldPosition().x;
}

float BoxCollider2D::GetWorldBottom() const
{
	return bottom_ * GetWorldScale().y + GetWorldPosition().y;
}

Vector2D BoxCollider2D::GetWorldLT() const
{
	return SRT(left_, top_);
}

Vector2D BoxCollider2D::GetWorldRT() const
{
	return SRT(right_, top_);
}

Vector2D BoxCollider2D::GetWorldRB() const
{
	return SRT(right_, bottom_);
}

Vector2D BoxCollider2D::GetWorldLB() const
{
	return SRT(left_, bottom_);
}
