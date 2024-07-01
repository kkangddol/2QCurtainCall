#include "CircleCollider2D.h"
#include "Vector2D.h"

#include "GameObject.h"

CircleCollider2D::CircleCollider2D(GameObject* object)
	: Collider(object, ColliderType::CIRCLE), radius_(0)
{

}

float CircleCollider2D::GetRadiusRelative() const
{
	return radius_ * GetWorldScale().y;
}
