#pragma once

#include "Collider.h"

class GameObject;

/// <summary>
/// ICollider �������̽��� ��ӹ޴� ���� �ݶ��̴�
/// �߽���ǥ�� �������� ���� �ִ�.
/// Circle Collision Detection�� �̿��ؼ� �浹�� üũ�Ѵ�.
/// Ÿ������ ���ؼ��� ���� ����°� ��������?
/// 
/// 22.12.19 ������ �����
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

