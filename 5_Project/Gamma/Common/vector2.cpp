#include "vector2.h"
#include "Matrix.h"


const vector2 vector2::Zero = vector2(0, 0);
const vector2 vector2::Up = vector2(0, -1);
const vector2 vector2::Down = vector2(0, 1);
const vector2 vector2::Left = vector2(-1, 0);
const vector2 vector2::Right = vector2(1, 0);

Matrix3x1 vector2::ToMatrix3x1()
{
	Matrix3x1 result;
	result[0] = x;
	result[1] = y;
	result[2] = 1;
	return result;
}

Matrix1x3 vector2::ToMatrix1x3()
{
	Matrix1x3 result;
	result[0] = x;
	result[1] = y;
	result[2] = 1;
	return result;
}

Matrix3x3 vector2::ToMatrix3x3()
{
	Matrix3x3 result;
	result[0][0] = x;
	result[1][1] = y;
	result[2][2] = 1;
	return result;
}

vector2 operator *(float a, vector2 b)
{
	return vector2(a * b.x, a * b.y);
}