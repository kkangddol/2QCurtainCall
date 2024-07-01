#include "Transform.h"
#define _USE_MATH_DEFINES
#include <math.h>

Transform::Transform(GameObject* object)
	: Component(object), position_(Vector2D(0,0)), rotation_(0), scale_(Vector2D(1,1))
{

}

Vector2D Transform::SRT(float x, float y)
{
	return Vector2D(x, y) * GetTransformMatrix();
}

Vector2D Transform::SRT(const Vector2D& vec)
{
	return vec * GetTransformMatrix();
}

/// <summary>
/// 이동
/// 덧셈
/// 
/// 22.12.14 강석원 집
/// </summary>
/// <param name="deltaVector"></param>
void Transform::Translate(float dX, float dY)
{
	position_.x += dX;
	position_.y += dY;
}

/// <summary>
/// 회전(라디안)
/// 덧셈 
/// (-2*π ~ 2*π) 범위 유지하도록 함
/// 
/// 22.12.14 강석원 집
/// </summary>
/// <param name="deltaRadian"></param>
void Transform::Rotate(float deltaRadian)
{
	rotation_ += deltaRadian;

	while (rotation_ <= -(M_PI * 2) || M_PI * 2 <= rotation_)
	{
		if (rotation_ >= M_PI * 2)
		{
			rotation_ -= (float)(M_PI * 2);
		}
		else if (rotation_ <= -(M_PI * 2))
		{
			rotation_ += (float)(M_PI * 2);
		}
	}
}

/// <summary>
/// 확대 축소
/// 곱셈
/// 
/// 22.12.14 강석원 집
/// </summary>
/// <param name="deltaScale"></param>
void Transform::Scale(float dX, float dY)
{
	scale_.x += dX;
	scale_.y += dY;
}

Matrix3x3 Transform::GetTransformMatrix() const
{
	Matrix3x3 transformMatrix{
		scale_.x * (float)cos(rotation_), scale_.x * (float)sin(rotation_), 0,
		-scale_.y * (float)sin(rotation_), scale_.y * (float)cos(rotation_), 0,
		position_.x, position_.y, 1
	};

	return transformMatrix;
}

Vector2D Transform::GetLocalPosition() const
{
	return position_;
}

float Transform::GetLocalRotation() const
{
	return rotation_;
}

float Transform::GetLocalEulerAngle() const
{
	return rotation_ * 180.0f / M_PI;
}

Vector2D Transform::GetLocalScale() const
{
	return scale_;
}

void Transform::SetLocalPosition(float posX, float posY)
{
	position_.x = posX;
	position_.y = posY;
}

void Transform::SetLocalPosition(Vector2D position)
{
	position_.x = position.x;
	position_.y = position.y;
}

void Transform::SetLocalRotation(float rotation)
{
	rotation_ = rotation;

	while (rotation_ <= -(M_PI * 2) || M_PI * 2 <= rotation_)
	{
		if (rotation_ >= M_PI * 2)
		{
			rotation_ -= (float)(M_PI * 2);
		}
		else if (rotation_ <= -(M_PI * 2))
		{
			rotation_ += (float)(M_PI * 2);
		}
	}
}

void Transform::SetLocalScale(Vector2D scale)
{
	scale_ = scale;
}
