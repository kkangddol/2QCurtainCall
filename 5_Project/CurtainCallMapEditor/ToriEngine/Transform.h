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

	void Translate(float dX, float dY);		// deltaVector 만큼 덧셈 (이동)
	void Rotate(float deltaRadian);			// deltaRadian 만큼 덧셈 (회전)
	void Scale(float dX, float dY);			// deltaScale 만큼 덧셈 (확대,축소)

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
	Vector2D position_;		// 오브젝트의 중앙 값
	float rotation_;		// 오브젝트의 라디안 값 (-2*π ~ 2*π)
	Vector2D scale_;		// 오브젝트의 scale 값
};

