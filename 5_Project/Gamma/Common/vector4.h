#pragma once
#include <xhash>

struct vector4
{
	float x;
	float y;
	float z;
	float w;

	vector4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	vector4(float a, float b, float c, float d)
	{
		x = a;
		y = b;
		z = c;
		w = d;
	}

	bool operator == (const vector4& other) const
	{
		if (x == other.x && y == other.y && z == other.z && w == other.w)
			return true;
		return false;
	}

	vector4 operator+(const vector4& rhs) const
	{
		return vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
	}

	vector4 operator-(const vector4& rhs) const
	{
		return vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
	}

	vector4 operator*(const float& rhs) const
	{
		return vector4(x * rhs, y * rhs, z * rhs, w * rhs);
	}
};

namespace std {
	template <>
	struct hash<vector4> {
		size_t operator()(const vector4& vec) const {
			hash<float> hash_func;
			return hash_func(vec.x + vec.y * 10 + vec.w * 100 + vec.z * 1000);
		}
	};
}