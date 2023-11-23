#include <cmath>
#include "Matrix.h"

const Matrix3x3 Matrix3x3::Identity = Matrix3x3(1, 0, 0, 0, 1, 0, 0, 0, 1);

Matrix2x2::Matrix2x2()
	: m11(0), m12(0), m21(0), m22(0)
{
}

Matrix2x2::Matrix2x2(float p11, float p12, float p21, float p22)
	: m11(p11), m12(p12), m21(p21), m22(p22)
{
}

float Matrix2x2::Determinant()
{
	return m11 * m22 - m12 * m21;
}

float Matrix2x2::Determinant(float p11, float p12, float p21, float p22)
{
	return p11 * p22 - p12 * p21;
}

Matrix1x3::Matrix1x3()
	: Matrix1x3(0, 0, 0)
{

}

Matrix1x3::Matrix1x3(float n11, float n12, float n13)
	:m11(n11), m12(n12), m13(n13)
{

}

Matrix1x3::~Matrix1x3()
{

}

Matrix1x3 Matrix1x3::operator*(const Matrix3x3& rhs)
{
	Matrix1x3 result;
	result.m11 = m11 * rhs.m11 + m12 * rhs.m21 + m13 * rhs.m31;
	result.m12 = m11 * rhs.m12 + m12 * rhs.m22 + m13 * rhs.m32;
	result.m13 = m11 * rhs.m13 + m12 * rhs.m23 + m13 * rhs.m33;

	return result;
}

// Matrix3x2 Matrix3x2::operator*(const Matrix3x2& rhs)
// {
// 	return Matrix3x2
// 	{
// 		m11 * rhs.m11 + m12 * rhs.m21, m11 * rhs.m12 + m12 * rhs.m22,
// 		m21 * rhs.m11 + m22 * rhs.m21, m21 * rhs.m12 + m22 * rhs.m22,
// 		m31 * rhs.m11 + m32 * rhs.m21 + rhs.m31, m31 * rhs.m12 + m32 * rhs.m22 + rhs.m32
// 	};
// }
// 
// Matrix3x2 Matrix3x2::operator*(const Matrix3x3& rhs)
// {
// 
// }

Matrix3x3::Matrix3x3()
	: m11(0), m12(0), m13(0),
	m21(0), m22(0), m23(0),
	m31(0), m32(0), m33(0)
{

}

Matrix3x3::Matrix3x3(
	float n11, float n12, float n13, 
	float n21, float n22, float n23,
	float n31, float n32, float n33
)
	: m11(n11), m12(n12), m13(n13),
	m21(n21), m22(n22), m23(n23),
	m31(n31), m32(n32), m33(n33)
{

}

Matrix3x3::~Matrix3x3()
{

}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& rhs)
{
	Matrix3x3 result;

	result.m11 = m11 * rhs.m11 + m12 * rhs.m21 + m13 * rhs.m31;
	result.m12 = m11 * rhs.m12 + m12 * rhs.m22 + m13 * rhs.m32;
	result.m13 = m11 * rhs.m13 + m12 * rhs.m23 + m13 * rhs.m33;

	result.m21 = m21 * rhs.m11 + m22 * rhs.m21 + m23 * rhs.m31;
	result.m22 = m21 * rhs.m12 + m22 * rhs.m22 + m23 * rhs.m32;
	result.m23 = m21 * rhs.m13 + m22 * rhs.m23 + m23 * rhs.m33;

	result.m31 = m31 * rhs.m11 + m32 * rhs.m21 + m33 * rhs.m31;
	result.m32 = m31 * rhs.m12 + m32 * rhs.m22 + m33 * rhs.m32;
	result.m33 = m31 * rhs.m13 + m32 * rhs.m23 + m33 * rhs.m33;

	return result;
}

Matrix3x3 Matrix3x3::operator*(float rhs)
{
	Matrix3x3 result;

	result.m11 = rhs * m11;
	result.m12 = rhs * m12;
	result.m13 = rhs * m13;

	result.m21 = rhs * m21;
	result.m22 = rhs * m22;
	result.m23 = rhs * m23;

	result.m31 = rhs * m31;
	result.m32 = rhs * m32;
	result.m33 = rhs * m33;

	return result;
}

Matrix3x3 Matrix3x3::Translation(float p_xPos, float p_yPos)
{
	Matrix3x3 result(
		1.f, 0.f, 0.f,
		0.f, 1.f, 0.f,
		p_xPos, p_yPos, 1.f
	);

	return result;
}

Matrix3x3 Matrix3x3::Rotate(double eulerAngle)
{
	double rad = eulerAngle * (3.141592 / 180);

	Matrix3x3 result(
		(float)cos(rad), (float)-sin(rad), 0.f,
		(float)sin(rad), (float)cos(rad), 0.f,
		0.f, 0.f, 1.f
	);

	return result;
}

Matrix3x3 Matrix3x3::Scale(float p_xRatio, float p_yRatio)
{
	Matrix3x3 result(
		p_xRatio, 0.f, 0.f,
		0.f, p_yRatio, 0.f,
		0.f, 0.f, 1.f
	);

	return result;
}

float Matrix3x3::Determinant()
{
	float det = m11 * (m22 * m33 - m23 * m32)
		- m12 * (m21 * m33 - m23 * m31)
		+ m13 * (m21 * m32 - m22 * m31);

	return det;
}

Matrix3x3 Matrix3x3::Transpose()
{
	Matrix3x3 result;

	result.m11 = m11;
	result.m12 = m21;
	result.m13 = m31;

	result.m21 = m12;
	result.m22 = m22;
	result.m23 = m32;

	result.m31 = m13;
	result.m32 = m23;
	result.m33 = m33;

	return result;
}

Matrix3x3 Matrix3x3::Inverse()
{
	if (Determinant() == 0)
	{
		return Matrix3x3();
	}

	Matrix3x3 result;

	result.m11 = Matrix2x2::Determinant(m22, m23, m32, m33);
	result.m12 = -Matrix2x2::Determinant(m21, m23, m31, m33);
	result.m13 = Matrix2x2::Determinant(m21, m22, m31, m32);

	result.m21 = -Matrix2x2::Determinant(m12, m13, m32, m33);
	result.m22 = Matrix2x2::Determinant(m11, m13, m31, m33);
	result.m23 = -Matrix2x2::Determinant(m11, m12, m31, m32);

	result.m31 = Matrix2x2::Determinant(m12, m13, m22, m23);
	result.m32 = -Matrix2x2::Determinant(m11, m13, m21, m23);
	result.m33 = Matrix2x2::Determinant(m11, m12, m21, m22);

	result = result.Transpose() * (1 / Determinant());

	return result;
}

