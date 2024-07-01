#include <math.h>
#include "matrix.h"
#include "vector2.h"

const Matrix3x3 Matrix3x3::Identity = Matrix3x3(1, 0, 0, 0, 1, 0, 0, 0, 1);


Matrix3x3 operator*(Matrix3x3 a, Matrix3x3 b)
{
	Matrix3x3 result;
	result[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0] + a[0][2] * b[2][0];
	result[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1] + a[0][2] * b[2][1];
	result[0][2] = a[0][0] * b[0][2] + a[0][1] * b[1][2] + a[0][2] * b[2][2];

	result[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0] + a[1][2] * b[2][0];
	result[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1] + a[1][2] * b[2][1];
	result[1][2] = a[1][0] * b[0][2] + a[1][1] * b[1][2] + a[1][2] * b[2][2];

	result[2][0] = a[2][0] * b[0][0] + a[2][1] * b[1][0] + a[2][2] * b[2][0];
	result[2][1] = a[2][0] * b[0][1] + a[2][1] * b[1][1] + a[2][2] * b[2][1];
	result[2][2] = a[2][0] * b[0][2] + a[2][1] * b[1][2] + a[2][2] * b[2][2];
	return result;
}

Matrix1x3 operator*(Matrix1x3 a, Matrix3x3 b)
{
	Matrix1x3 result;
	result[0] = a[0] * b[0][0] + a[1] * b[1][0] + a[2] * b[2][0];
	result[1] = a[0] * b[0][1] + a[1] * b[1][1] + a[2] * b[2][1];
	result[2] = a[0] * b[0][2] + a[1] * b[1][2] + a[2] * b[2][2];
	return result;
}

Matrix3x1 operator*(Matrix3x3 a, Matrix3x1 b)
{
	Matrix3x1 result;
	result[0] = a[0][0] * b[0] + a[0][1] * b[1] + a[0][2] * b[2];
	result[1] = a[1][0] * b[0] + a[1][1] * b[1] + a[1][2] * b[2];
	result[2] = a[2][0] * b[0] + a[2][1] * b[1] + a[2][2] * b[2];
	return result;
}

float Matrix3x3::Determinant()
{
	float det = value[0][0] * (value[1][1] * value[2][2] - value[1][2] * value[2][1])
		- value[0][1] * (value[1][0] * value[2][2] - value[1][2] * value[2][0])
		+ value[0][2] * (value[1][0] * value[2][1] - value[1][1] * value[2][0]);

	return det;
}

Matrix3x3 Matrix3x3::Transpose()
{
	Matrix3x3 result;

	result[0][0] = value[0][0];
	result[0][1] = value[1][0];
	result[0][2] = value[2][0];

	result[1][0] = value[0][1];
	result[1][1] = value[1][1];
	result[1][2] = value[2][1];

	result[2][0] = value[0][2];
	result[2][1] = value[1][2];
	result[2][2] = value[2][2];

	return result;
}

Matrix3x3 Matrix3x3::Inverse()
{
	if (Determinant() == 0)
	{
		return Matrix3x3();
	}

	Matrix3x3 result;

	result[0][0] = Matrix2x2::Determinant(value[1][1], value[1][2], value[2][1], value[2][2]);
	result[0][1] = -Matrix2x2::Determinant(value[1][0], value[1][2], value[2][0], value[2][2]);
	result[0][2] = Matrix2x2::Determinant(value[1][0], value[1][1], value[2][0], value[2][1]);

	result[1][0] = -Matrix2x2::Determinant(value[0][1], value[0][2], value[2][1], value[2][2]);
	result[1][1] = Matrix2x2::Determinant(value[0][0], value[0][2], value[2][0], value[2][2]);
	result[1][2] = -Matrix2x2::Determinant(value[0][0], value[0][1], value[2][0], value[2][1]);

	result[2][0] = Matrix2x2::Determinant(value[0][1], value[0][2], value[1][1], value[1][2]);
	result[2][1] = -Matrix2x2::Determinant(value[0][0], value[0][2], value[1][0], value[1][2]);
	result[2][2] = Matrix2x2::Determinant(value[0][0], value[0][1], value[1][0], value[1][1]);

	result = result.Transpose() * (1 / Determinant());

	return result;
}

vector2 Matrix3x3::tovector2()
{
	return vector2(value[0][0], value[1][1]);
}

vector2 Matrix1x3::tovector2()
{
	return vector2(value[0], value[1]);
}

vector2 Matrix3x1::tovector2()
{
	return vector2(value[0], value[1]);
}

float Matrix2x2::Determinant()
{
	return m11 * m22 - m12 * m21;
}

float Matrix2x2::Determinant(float p11, float p12, float p21, float p22)
{
	return p11 * p22 - p12 * p21;
}
