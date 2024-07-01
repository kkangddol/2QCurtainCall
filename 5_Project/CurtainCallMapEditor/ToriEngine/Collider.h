#pragma once
#include "Component.h"
#include "Vector2D.h"
#include "Matrix.h"

class GameObject;

/// <summary>
/// 충돌 처리를 위해 상속받을 콜라이더 인터페이스
/// 이 인터페이스를 상속받아서 여러 collider를 만들 것 (박스,원,선 등등)
/// 
/// 2022.12.13 강석원 집
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

	/// 이 3개 아직 하이어라키컬 하게 되어있지 않음.
	/// 오브젝트의 로컬스케일만 갖고옴.
	/// 수정 필요.
	/// 2023.01.19 강석원 인재원
	Vector2D GetWorldPosition() const;
	float GetWorldRotation() const;
	Vector2D GetWorldScale() const;

protected:
	ColliderType colliderType_;

	Vector2D position_;
	float rotation_;		// radian
	Vector2D scale_;
};

