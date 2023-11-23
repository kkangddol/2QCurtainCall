#pragma once

#include "Collider.h"

class GameObject;

/// <summary>
/// ICollider 인터페이스를 상속받는 원형 콜라이더
/// 중심좌표와 반지름을 갖고 있다.
/// Circle Collision Detection을 이용해서 충돌을 체크한다.
/// 타원형에 대해서는 따로 만드는게 나으려나?
/// 
/// 22.12.19 강석원 인재원
/// </summary>
class CircleCollider2D : public Collider
{
public:
	CircleCollider2D(GameObject* object);
	virtual ~CircleCollider2D() {};

	float GetRadiusRelative() const;

	float GetRadius() const
	{
		return radius_;
	}

	void SetRadius(float radius)
	{
		radius_ = radius;
	}

private:
	float radius_;
};

