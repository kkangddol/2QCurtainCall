#pragma once
struct  vector2;

struct Matrix3x1
{
	float value[3];
	float& operator[](int i)
	{
		return value[i];
	};
	Matrix3x1()
	{
		value[0] = 0;
		value[1] = 0;
		value[2] = 0;
	}
	Matrix3x1(float a0, float a1, float a2)
	{
		value[0] = a0;
		value[1] = a1;
		value[2] = a2;
	}
	vector2 tovector2();
};



struct Matrix1x3
{
	float value[3];
	float& operator[](int i)
	{
		return value[i];
	};
	Matrix1x3()
	{
		value[0] = 0;
		value[1] = 0;
		value[2] = 0;
	}
	Matrix1x3(float a0, float a1, float a2)
	{
		value[0] = a0;
		value[1] = a1;
		value[2] = a2;
	}
	vector2 tovector2();
};

struct Matrix2x2
{
	float m11, m12;
	float m21, m22;

	Matrix2x2()
	{
		m11 = 0;
		m12 = 0;
		m21 = 0;
		m22 = 0;
	}

	Matrix2x2(float p11, float p12, float p21, float p22)
	{
		m11 = p11;
		m12 = p12;
		m21 = p21;
		m22 = p22;
	}

	float Determinant();
	static float Determinant(float p11, float p12, float p21, float p22);
};

struct Matrix3x3
{
	Matrix3x1 value[3];
	Matrix3x3()
	{
		value[0][0] = 0;
		value[0][1] = 0;
		value[0][2] = 0;
		value[1][0] = 0;
		value[1][1] = 0;
		value[1][2] = 0;
		value[2][0] = 0;
		value[2][1] = 0;
		value[2][2] = 0;
	}

	Matrix3x3(float a0, float a1, float a2, float b0, float b1, float b2, float c0, float c1, float c2)
	{
		value[0][0] = a0;
		value[0][1] = a1;
		value[0][2] = a2;
		value[1][0] = b0;
		value[1][1] = b1;
		value[1][2] = b2;
		value[2][0] = c0;
		value[2][1] = c1;
		value[2][2] = c2;
	}

	Matrix3x1& operator[](int i)
	{
		return value[i];
	};

	Matrix3x3 operator*(float rhs)
	{
		Matrix3x3 result;

		result[0][0] = rhs * value[0][0];
		result[0][1] = rhs * value[0][1];
		result[0][2] = rhs * value[0][2];

		result[1][0] = rhs * value[1][0];
		result[1][1] = rhs * value[1][1];
		result[1][2] = rhs * value[1][2];

		result[2][0] = rhs * value[2][0];
		result[2][1] = rhs * value[2][1];
		result[2][2] = rhs * value[2][2];

		return result;
	}



	const static Matrix3x3 Identity;

	static Matrix3x3 Translation(float p_xPos, float p_yPos)
	{
		Matrix3x3 result(
			1.f, 0.f, 0.f,
			0.f, 1.f, 0.f,
			p_xPos, p_yPos, 1.f
		);

		return result;
	}

	static Matrix3x3 Rotate(double p_euler)
	{
		double rad = p_euler * (3.141592 / 180);

		Matrix3x3 result(
			(float)cos(rad), (float)-sin(rad), 0.f,
			(float)sin(rad), (float)cos(rad), 0.f,
			0.f, 0.f, 1.f
		);

		return result;
	}

	static Matrix3x3 Shear(float p_xRatio, float p_yRatio)
	{
		double radx = p_xRatio * (3.141592 / 180);
		double rady = p_yRatio * (3.141592 / 180);
		Matrix3x3 result(
			 1.f, (float)tan(rady), 0.f,
			(float)tan(radx), 1.f, 0.f,
			0.f, 0.f, 1.f
		);

		return result;
	}

	static Matrix3x3 Scale(float p_xRatio, float p_yRatio)
	{
		Matrix3x3 result(
			p_xRatio, 0.f, 0.f,
			0.f, p_yRatio, 0.f,
			0.f, 0.f, 1.f
		);

		return result;
	}

	vector2 tovector2();
	float Determinant();
	Matrix3x3 Transpose();
	Matrix3x3 Inverse();
};

struct Matrix5x1
{
	float value[5];
	Matrix5x1()
	{
		value[0] = 0;
		value[1] = 0;
		value[2] = 0;
		value[3] = 0;
		value[4] = 0;
	}
	float& operator[](int i)
	{
		return value[i];
	};
};

struct Matrix5x5
{
	Matrix5x1 value[5];
	Matrix5x5()
	{
		value[0] = Matrix5x1();
		value[1] = Matrix5x1();
		value[2] = Matrix5x1();
		value[3] = Matrix5x1();
		value[4] = Matrix5x1();
	}
	Matrix5x1& operator[](int i)
	{
		return value[i];
	};
};


Matrix3x3 operator*(Matrix3x3 a, Matrix3x3 b);

Matrix1x3 operator*(Matrix1x3 a, Matrix3x3 b);

Matrix3x1 operator*(Matrix3x3 a, Matrix3x1 b);
