#pragma once

#include "Component.h"
#include "Vector2D.h"
#include "Matrix.h"

class GameObject;
class Component;
class Transform;

/// <summary>
/// ī�޶� ������Ʈ class
/// 
/// ������ �ڵ�
/// 23.02.14 ������ �����
/// </summary>
class Camera : public Component
{
public:
	Camera(GameObject* obj);
	~Camera();

public:
	Vector2D ScreenToWorldPoint(Vector2D point);
	Vector2D WorldToScreenPoint(Vector2D point);
	Vector2D ScreenToWorldScale(Vector2D scale);
	Matrix3x3 Projection();

public:
	static Camera* main;
	float orthoScale = 1;
private:

};
