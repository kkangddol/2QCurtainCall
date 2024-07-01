#pragma once
#include <xhash>

struct vector3
{
	float x;
	float y;
	float z;

	vector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	vector3(float a, float b, float c)
	{
		x = a;
		y = b;
		z = c;
	}

	bool operator == (const vector3& other) const {
		if (x == other.x && y == other.y && z == other.z)
			return true;
		return false;
	}

	inline vector3 operator +(vector3 a) const
	{
		return vector3(x + a.x, y + a.y, z + a.z);
	}

	inline vector3 operator -(vector3 a) const
	{
		return vector3(x - a.x, y - a.y, z - a.z);
	}

	inline vector3 operator *(float a) const
	{
		return vector3(x * a, y * a, z * a);
	}

	inline vector3 operator /(float a) const
	{
		return vector3(x / a, y / a, z / a);
	}
};

namespace std {
	template <>
	struct hash<vector3> {
		size_t operator()(const vector3& vec) const {
			hash<float> hash_func;
			return hash_func(vec.x + vec.y * 10 + vec.z * 1000);
		}
	};
}