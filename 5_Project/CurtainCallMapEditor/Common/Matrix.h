#pragma once

struct Matrix2x2;
struct Matrix1x3;
struct Matrix3x2;
struct Matrix3x3;

struct Matrix2x2
{
	float m11, m12;
	float m21, m22;

	Matrix2x2();
	Matrix2x2(float p11, float p12, float p21, float p22);

	float Determinant();
	static float Determinant(float p11, float p12, float p21, float p22);
};

struct Matrix1x3
{
	float m11, m12, m13;

	Matrix1x3();
	Matrix1x3(float n11, float n12, float n13);
	~Matrix1x3();

	Matrix1x3 operator*(const Matrix3x3& rhs);

};

/// <summary>
/// 벡터와 행렬곱을 위해 제작한 특별한 행렬.
/// D2D1 의 Matrix3x2F를 참고하여 제작했음.
/// 3열의 값이 각각 0 0 1 이므로 생략할 수 있도록 했음.
/// 따라서 이 행렬끼리 행렬곱을 할 수 있음. (마지막 열에 0 0 1 이 있다고 가정하고 계산 진행)
/// Vector2D와 행렬곱을 했을 때 바로 Vector2D가 나올 수 있도록 함.
/// </summary>
// struct Matrix3x2
// {
// 	float m11, m12;
// 	float m21, m22;
// 	float m31, m32;
// 
// 	// 특수하게 허용함.
// 	// 그냥 3x3으로 할까..?
// 	Matrix3x2 operator*(const Matrix3x2& rhs);
// 	Matrix3x2 operator*(const Matrix3x3& rhs);
// };

struct Matrix3x3
{
	float m11, m12, m13;
	float m21, m22, m23;
	float m31, m32, m33;

	Matrix3x3();
	Matrix3x3(float n11, float n12, float n13, float n21, float n22, float n23, float n31, float n32, float n33);
	~Matrix3x3();

	// 벡터랑 행렬이랑 곱하는거 해야함

	Matrix3x3 operator*(const Matrix3x3& rhs);
	Matrix3x3 operator*(float rhs);
	const static Matrix3x3 Identity;

	static Matrix3x3 Translation(float p_xPos, float p_yPos);
	static Matrix3x3 Rotate(double radian);
	static Matrix3x3 Scale(float p_xRatio, float p_yRatio);

	float Determinant();
	Matrix3x3 Transpose();
	Matrix3x3 Inverse();
};
