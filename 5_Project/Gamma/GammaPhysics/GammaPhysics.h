#pragma once
#include <vector>
#include <utility>
#include "vector2.h"
#include "Matrix.h"

struct Face {
	vector2 normal;
	float distance;
};

class GammaPhysics
{
public:
	static std::vector<vector2> ComputePoints(vector2 bounds,Matrix3x3 matrix);
	static vector2 FarthestPoint(vector2 pos, float radius, vector2 v);
	static vector2 FarthestPoint(std::vector<vector2> points, vector2 bounds);
	static vector2 Support(std::vector<vector2> points1, std::vector<vector2> points2, vector2 bounds);
	static bool GJK(std::vector<vector2> points1, std::vector<vector2> points2);
	static float ProjectOntoAxis(const std::vector<vector2>& vertices, const vector2& axis);
	static float OverlapOnAxis(const std::vector<vector2>& vertices1, const std::vector<vector2>& vertices2, const vector2& axis);
	static std::pair<float, vector2> FindAxisLeastPenetration(const std::vector<vector2>& vertices1, const std::vector<vector2>& vertices2);
private:

};