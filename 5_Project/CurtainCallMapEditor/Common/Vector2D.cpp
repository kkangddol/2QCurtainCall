#include <cmath>
#include "Matrix.h"

#include "Vector2D.h"

Vector2D::Vector2D()
	:x(0), y(0)
{

}

Vector2D::Vector2D(float _x, float _y)
	:x(_x), y(_y)
{

}

Vector2D::Vector2D(const Vector2D& vec)
	:x(vec.x), y(vec.y)
{
}

Vector2D::~Vector2D()
{

}

void Vector2D::Normalize()
{
	float magnitude = this->Magnitude();

	if (magnitude <= 0)
	{
		return;
	}

	x /= magnitude;
	y /= magnitude;
}

float Vector2D::Magnitude() const
{
	return sqrt(pow(x, 2) + pow(y, 2));
}

float Vector2D::DotProduct(const Vector2D& rhs) const
{
	return (x * rhs.x) + (y * rhs.y);
}

/// <summary>
/// 2���� ������ ����
///	����� Vector3D���� 2������ ������ (0, 0, x1y2 - y1x2) �̹Ƿ�
/// ������ ����� float���� ��ȯ�ϵ��� ����
/// 
/// 22.12.19 ������ �����
/// </summary>
/// <param name="rhs"></param>
/// <returns></returns>
float Vector2D::CrossProduct(const Vector2D& rhs) const
{
	return (x * rhs.y) - (y * rhs.x);
}

Vector2D& Vector2D::operator=(const Vector2D& rhs)
{
	x = rhs.x;
	y = rhs.y;
	return *this;
}

Vector2D Vector2D::operator+(const Vector2D& rhs) const
{
	return Vector2D(x + rhs.x, y + rhs.y);
}

Vector2D Vector2D::operator-(const Vector2D& rhs) const
{
	return Vector2D(x - rhs.x, y - rhs.y);
}

Vector2D Vector2D::operator-() const
{
	return Vector2D(-x, -y);
}


Vector2D Vector2D::operator*(const Vector2D& rhs) const
{
	return Vector2D(x * rhs.x, y * rhs.y);
}

Vector2D Vector2D::operator*(float rhs) const
{
	return Vector2D(x * rhs, y * rhs);
}

Vector2D Vector2D::operator/(float rhs) const
{
	return rhs == 0 ? *this : Vector2D(x / rhs, y / rhs);
}

Vector2D& Vector2D::operator/=(float rhs)
{
	if (rhs == 0) return *this;

	x /= rhs;
	y /= rhs;
	return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D& rhs)
{
	(*this) = (*this) + rhs;
	return (*this);
}

Vector2D& Vector2D::operator-=(const Vector2D& rhs)
{
	(*this) = (*this) - rhs;
	return (*this);
}

bool Vector2D::operator==(const Vector2D& rhs) const
{
	return (x == rhs.x) && (y == rhs.y);
}

Vector2D Vector2D::operator*(const Matrix3x3& rhs) const
{
	return Vector2D(x * rhs.m11 + y * rhs.m21 + rhs.m31, x * rhs.m12 + y * rhs.m22 + rhs.m32);
}
