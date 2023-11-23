#pragma once
#include <cmath>
struct Matrix3x3;
struct Matrix3x1;
struct Matrix1x3;

/// <summary>
/// 2차원 벡터 자료형
/// </summary>
struct vector2
{
	float x;
	float y;
	const static vector2 Zero;
	const static vector2 Up;
	const static vector2 Down;
	const static vector2 Left;
	const static vector2 Right;

	vector2()
	{
		x = 0;
		y = 0;
	}

	vector2(float a, float b)
	{
		x = a;
		y = b;
	}

	inline friend bool operator ==(vector2 a, vector2 b)
	{
		return a.x == b.x && a.y == b.y;
	}

	inline friend bool operator !=(vector2& a, vector2& b)
	{
		return a.x != b.x || a.y != b.y;
	}

	inline vector2 operator -()
	{
		return vector2(-x, -y);
	}

	inline vector2 operator +(vector2 a) const
	{
		return vector2(x + a.x, y + a.y);
	}

	inline vector2 operator -(vector2 a) const
	{
		return vector2(x - a.x, y - a.y);
	}

	inline vector2 operator *(float a) const
	{
		return vector2(x * a, y * a);
	}

	inline vector2 operator /(float a) const
	{
		return vector2(x / a, y / a);
	}

	inline vector2& operator +=(vector2& a)
	{
		(*this) = (*this) + a;
		return *this;
	}

	inline vector2& operator +=(vector2 a)
	{
		(*this) = (*this) + a;
		return *this;
	}

	inline vector2& operator -=(vector2& a)
	{
		(*this) = (*this) - a;
		return *this;
	}

	inline vector2& operator -=(vector2 a)
	{
		(*this) = (*this) - a;
		return *this;
	}

	inline float operator *(const vector2& b)
	{
		return x * b.y - y * x;
	}

	inline static float Dot(vector2 v1, vector2 v2)
	{
		float result = v1.x * v2.x + v1.y * v2.y;
		return result;
	}

	inline static float Cross(vector2 v1, vector2 v2)
	{
		return (v1.x * v2.y) - (v1.y * v2.x);
	}

	inline static vector2 TripleProduct(vector2 a, vector2 b, vector2 c)
	{
		return -a * (vector2::Dot(b, c)) + b * (vector2::Dot(a, c));
	}

	inline float Length()
	{
		return sqrtf(x * x + y * y);
	}

	inline static float Length(vector2 v)
	{
		return sqrtf(v.x * v.x + v.y * v.y);
	}

	inline static float Distance(vector2 v1, vector2 v2)
	{
		float result = sqrtf((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
		return result;
	}

	inline vector2 Normalize()
	{
		if (Length() == 0)
		{
			return vector2();
		}
		vector2 result = vector2(x / this->Length(), y / this->Length());
		return result;
	}

	inline static vector2 Normalize(vector2 v)
	{
		if (Length(v) == 0)
		{
			return vector2();
		}
		vector2 result = vector2(v.x / Length(v), v.y / Length(v));
		return result;
	}

	inline static vector2 Reflect(vector2 v, vector2 normal)
	{
		return v - normal * vector2::Dot(v, normal) * 2;
	}

	Matrix3x1 ToMatrix3x1();
	Matrix1x3 ToMatrix1x3();
	Matrix3x3 ToMatrix3x3();
};

vector2 operator *(float a, vector2 b);