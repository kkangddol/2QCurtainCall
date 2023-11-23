#include "Collider.h"
#include "GameObject.h"
#include "CollisionSystem.h"

Collider::Collider(GameObject* object, ColliderType type)
	: Component(object), colliderType_(type), position_(Vector2D(0,0)), rotation_(0), scale_(Vector2D(1,1))
{
	CollisionSystem::Instance().RegisterCollider(*this);
}

Collider::~Collider()
{
	CollisionSystem::Instance().RemoveCollider(*this);
}

Vector2D Collider::SRT(float x, float y) const
{
	return Vector2D(x, y) * GetWorldTransformMatrix();
}

Vector2D Collider::SRT(const Vector2D& vec) const
{
	return vec * GetWorldTransformMatrix();
}

Matrix3x3 Collider::GetTransformMatrix() const
{
	Matrix3x3 transformMatrix{
		scale_.x * cos(rotation_), scale_.x * sin(rotation_), 0,
		-scale_.y * sin(rotation_), scale_.y * cos(rotation_), 0,
		position_.x, position_.y, 1
	};

	return transformMatrix;
}

Matrix3x3 Collider::GetWorldTransformMatrix() const
{
	return GetTransformMatrix() * object_->transform.GetTransformMatrix();
}

Collider::ColliderType Collider::GetColliderType()
{
	return colliderType_;
}

/// <summary>
/// Object의 위치에 Collider의 로컬을 더해서 반환
/// 
/// 22.12.28 강석원 집
/// </summary>
/// <returns></returns>
Vector2D Collider::GetWorldPosition() const
{
	return SRT(position_);
}

float Collider::GetWorldRotation() const
{
	return rotation_ + object_->transform.GetLocalRotation();
}

Vector2D Collider::GetWorldScale() const
{
	return Vector2D(scale_ * object_->transform.GetLocalScale());
}
