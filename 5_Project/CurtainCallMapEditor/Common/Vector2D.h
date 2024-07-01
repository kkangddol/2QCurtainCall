#pragma once

struct Matrix3x3;

/// <summary>
/// 나만의 2차원 벡터 클래스
/// x,y 두 개의 float으로 방향과 크기를 나타낸다.
/// 
/// 22.12.19 강석원 인재원
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
	float CrossProduct(const Vector2D& rhs) const;	// 결과가 Vector3D지만 2차원의 외적은 (0, 0, x1y2 - y1x2) 이므로
														// 마지막 결과만 반환하도록 했다.

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
