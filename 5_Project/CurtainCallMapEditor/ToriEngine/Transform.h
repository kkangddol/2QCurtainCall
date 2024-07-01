#pragma once
#include "Component.h"
#include "Vector2D.h"
#include "Matrix.h"

class GameObject;

class Transform : public Component
{
public:
	Transform(GameObject* object);

	Vector2D SRT(float x, float y);
	Vector2D SRT(const Vector2D& vec);

	void Translate(float dX, float dY);		// deltaVector ��ŭ ���� (�̵�)
	void Rotate(float deltaRadian);			// deltaRadian ��ŭ ���� (ȸ��)
	void Scale(float dX, float dY);			// deltaScale ��ŭ ���� (Ȯ��,���)

	Matrix3x3 GetTransformMatrix() const;

	Vector2D GetLocalPosition() const;
	float GetLocalRotation() const;
	float GetLocalEulerAngle() const;
	Vector2D GetLocalScale() const;

	void SetLocalPosition(float posX, float posY);
	void SetLocalPosition(Vector2D);
	void SetLocalRotation(float rotation);
	void SetLocalScale(Vector2D scale);

private:
	Vector2D position_;		// ������Ʈ�� �߾� ��
	float rotation_;		// ������Ʈ�� ���� �� (-2*�� ~ 2*��)
	Vector2D scale_;		// ������Ʈ�� scale ��
};

