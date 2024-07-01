#include "OBB.h"

float Abs(float value)
{
	if (value < 0)
	{
		value = -value;
	}

	return value;
}

bool DetectOBB(std::vector<Vector2D>& lhs, std::vector<Vector2D>& rhs)
{
	/// 각 도형의 중점을 잇는 벡터를 구한다.
	Vector2D ltemp;
	for (auto vec : lhs)
	{
		ltemp += vec;
	}
	ltemp /= lhs.size();

	Vector2D rtemp;
	for (auto vec : rhs)
	{
		rtemp += vec;
	}
	rtemp /= rhs.size();

	/// 각 도형의 중점을 잇는 벡터.
	Vector2D CtoC = rtemp - ltemp;

	for (int index = 0; index < lhs.size(); ++index)
	{
		Vector2D testVec = lhs[index] - lhs[(index + 1) % lhs.size()];
		testVec.Normalize();

		float CtoCLength = Abs(CtoC.DotProduct(testVec));
		float lhsLength = 0;
		float rhsLength = 0;

		for (int index = 0; index < lhs.size(); ++index)
		{
			Vector2D temp = lhs[index] - lhs[(index + 1) % lhs.size()];
			lhsLength += Abs(temp.DotProduct(testVec));
		}

		for (int index = 0; index < rhs.size(); ++index)
		{
			Vector2D temp = rhs[index] - rhs[(index + 1) % rhs.size()];
			rhsLength += Abs(temp.DotProduct(testVec));
		}

		lhsLength /= lhs.size();
		rhsLength /= rhs.size();

		if (CtoCLength > lhsLength + rhsLength)
		{
			return false;
		}
	}

	for (int index = 0; index < rhs.size(); ++index)
	{
		Vector2D testVec = rhs[index] - rhs[(index + 1) % rhs.size()];
		testVec.Normalize();

		float CtoCLength = Abs(CtoC.DotProduct(testVec));
		float lhsLength = 0;
		float rhsLength = 0;

		for (int index = 0; index < lhs.size(); ++index)
		{
			Vector2D temp = lhs[index] - lhs[(index + 1) % lhs.size()];
			lhsLength += Abs(temp.DotProduct(testVec));
		}

		for (int index = 0; index < rhs.size(); ++index)
		{
			Vector2D temp = rhs[index] - rhs[(index + 1) % rhs.size()];
			rhsLength += Abs(temp.DotProduct(testVec));
		}

		lhsLength /= lhs.size();
		rhsLength /= rhs.size();

		if (CtoCLength > lhsLength + rhsLength)
		{
			return false;
		}
	}

	return true;
}
