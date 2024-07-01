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
/// ���Ϳ� ��İ��� ���� ������ Ư���� ���.
/// D2D1 �� Matrix3x2F�� �����Ͽ� ��������.
/// 3���� ���� ���� 0 0 1 �̹Ƿ� ������ �� �ֵ��� ����.
/// ���� �� ��ĳ��� ��İ��� �� �� ����. (������ ���� 0 0 1 �� �ִٰ� �����ϰ� ��� ����)
/// Vector2D�� ��İ��� ���� �� �ٷ� Vector2D�� ���� �� �ֵ��� ��.
/// </summary>
// struct Matrix3x2
// {
// 	float m11, m12;
// 	float m21, m22;
// 	float m31, m32;
// 
// 	// Ư���ϰ� �����.
// 	// �׳� 3x3���� �ұ�..?
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

	// ���Ͷ� ����̶� ���ϴ°� �ؾ���

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
