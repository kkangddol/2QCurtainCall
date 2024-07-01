#pragma once
#include "Component.h"
#include "Vector2D.h"
#include "Matrix.h"

class GameObject;

/// <summary>
/// �浹 ó���� ���� ��ӹ��� �ݶ��̴� �������̽�
/// �� �������̽��� ��ӹ޾Ƽ� ���� collider�� ���� �� (�ڽ�,��,�� ���)
/// 
/// 2022.12.13 ������ ��
/// </summary>
class Collider : public Component
{
public:
	enum class ColliderType
	{
		NOTHING,
		CIRCLE,
		RECTANGLE
	};

	Collider(GameObject* object, ColliderType type);
	virtual ~Collider();

	Vector2D SRT(float x, float y) const;
	Vector2D SRT(const Vector2D& vec) const;

	Matrix3x3 GetTransformMatrix() const;
	Matrix3x3 GetWorldTransformMatrix() const;
	
	ColliderType GetColliderType();

	/// �� 3�� ���� ���̾��Ű�� �ϰ� �Ǿ����� ����.
	/// ������Ʈ�� ���ý����ϸ� �����.
	/// ���� �ʿ�.
	/// 2023.01.19 ������ �����
	Vector2D GetWorldPosition() const;
	float GetWorldRotation() const;
	Vector2D GetWorldScale() const;

protected:
	ColliderType colliderType_;

	Vector2D position_;
	float rotation_;		// radian
	Vector2D scale_;
};

