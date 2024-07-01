#pragma once

struct Matrix3x3;

/// <summary>
/// ������ 2���� ���� Ŭ����
/// x,y �� ���� float���� ����� ũ�⸦ ��Ÿ����.
/// 
/// 22.12.19 ������ �����
/// </summary>
struct Vector2D
{
public:
	float x;
	float y;

	Vector2D();
	Vector2D(float _x, float _y);
	Vector2D(const Vector2D& vec);
	~Vector2D();

	void Normalize();
	float Magnitude() const;
	float DotProduct(const Vector2D& rhs) const;
	float CrossProduct(const Vector2D& rhs) const;	// ����� Vector3D���� 2������ ������ (0, 0, x1y2 - y1x2) �̹Ƿ�
														// ������ ����� ��ȯ�ϵ��� �ߴ�.

	Vector2D& operator=(const Vector2D& rhs);
	Vector2D operator+(const Vector2D& rhs) const;
	Vector2D operator-(const Vector2D& rhs) const;
	Vector2D operator-() const;
	Vector2D operator*(const Vector2D& rhs) const;
	Vector2D operator*(float rhs) const;
	Vector2D operator/(float rhs) const;
	Vector2D& operator/=(float rhs);
	Vector2D& operator+=(const Vector2D& rhs);
	Vector2D& operator-=(const Vector2D& rhs);
	bool operator==(const Vector2D& rhs) const;
	Vector2D operator*(const Matrix3x3& rhs) const;
};