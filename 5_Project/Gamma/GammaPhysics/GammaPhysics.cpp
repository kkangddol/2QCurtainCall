#include "GammaPhysics.h"

std::vector<vector2> GammaPhysics::ComputePoints(vector2 bounds, Matrix3x3 matrix)
{
	std::vector<vector2> simplex;
	Matrix3x3 worldMatrix = matrix;
	vector2 leftUp = (vector2(-(bounds.x / 2), -(bounds.y / 2)).ToMatrix1x3() * worldMatrix).tovector2();
	vector2 rightUp = (vector2(bounds.x / 2, -(bounds.y / 2)).ToMatrix1x3() * worldMatrix).tovector2();
	vector2 rightDown = (vector2(bounds.x / 2, bounds.y / 2).ToMatrix1x3() * worldMatrix).tovector2();
	vector2 leftDown = (vector2(-(bounds.x / 2), bounds.y / 2).ToMatrix1x3() * worldMatrix).tovector2();

	simplex.push_back(leftUp);
	simplex.push_back(rightUp);
	simplex.push_back(rightDown);
	simplex.push_back(leftDown);
	return simplex;
}

vector2 GammaPhysics::FarthestPoint(vector2 pos, float radius, vector2 v)
{
	return pos + v.Normalize() * radius;
}

vector2 GammaPhysics::FarthestPoint(std::vector<vector2> points, vector2 v)
{
	vector2 result;
	auto iter = points.begin();
	result = *iter;
	iter++;
	for (; iter < points.end(); iter++)
	{
		if (vector2::Dot(v, result) < vector2::Dot(v, *iter))
		{
			result = *iter;
		}
	}
	return result;
}

vector2 GammaPhysics::Support(std::vector<vector2> points1, std::vector<vector2> points2, vector2 bounds)
{
	return FarthestPoint(points1, bounds) - FarthestPoint(points2, bounds);
}

bool GammaPhysics::GJK(std::vector<vector2> points1, std::vector<vector2> points2)
{
	vector2 direction = vector2(1, 1);
	vector2 a = Support(points1, points2, direction);

	vector2 v = -a;

	vector2 b = Support(points1, points2, v);

	if (vector2::Dot(b, v) < 0) return false;

	vector2 ab = b - a;
	v = vector2::TripleProduct(ab, -a, ab);

	for (;;) {
		vector2 c = Support(points1, points2, v);
		if (vector2::Dot(c, v) < 0) return false;

		vector2 c0 = -c;
		vector2 cb = b - c;
		vector2 ca = a - c;

		vector2 cbPerp = vector2::TripleProduct(ca, cb, cb);
		vector2 caPerp = vector2::TripleProduct(cb, ca, ca);

		if (vector2::Dot(caPerp, c0) > 0) {
			b = c;
			v = caPerp;
		}
		else if (vector2::Dot(cbPerp, c0) > 0) {
			a = c;
			v = cbPerp;
		}
		else
		{
			return true;
		}
	}


}

std::vector<Face> ComputeFaces(const std::vector<vector2>& vertices) {
	std::vector<Face> faces;
	for (int i = 0; i < vertices.size(); ++i) {
		int j = (i + 1) % vertices.size();
		vector2 edge = vertices[j] - vertices[i];
		vector2 normal = { -edge.y, edge.x };
		normal = vector2::Normalize(normal);
		float distance = vector2::Dot(normal, vertices[i]);
		faces.push_back({ normal, distance });
	}
	return faces;
}

float GammaPhysics::ProjectOntoAxis(const std::vector<vector2>& vertices, const vector2& axis)
{
	float min = vector2::Dot(vertices[0], axis);
	float max = min;
	for (int i = 1; i < vertices.size(); ++i) {
		float projection = vector2::Dot(vertices[i], axis);
		if (projection < min) {
			min = projection;
		}
		else if (projection > max) {
			max = projection;
		}
	}
	return max - min;
}

float GammaPhysics::OverlapOnAxis(const std::vector<vector2>& vertices1, const std::vector<vector2>& vertices2, const vector2& axis)
{
	float projection1 = ProjectOntoAxis(vertices1, axis);
	float projection2 = ProjectOntoAxis(vertices2, axis);
	float distance = vector2::Dot(axis, (vertices1[0] + vertices2[0])) * 0.5f;
	float overlap = projection1 + projection2 - std::abs(distance);
	return overlap;
}

std::pair<float, vector2> GammaPhysics::FindAxisLeastPenetration(const std::vector<vector2>& vertices1, const std::vector<vector2>& vertices2)
{
	float min_overlap = INFINITY;
	vector2 min_normal;
	std::vector<Face> faces1 = ComputeFaces(vertices1);
	std::vector<Face> faces2 = ComputeFaces(vertices2);
	for (const Face& face1 : faces1) {
		vector2 axis = face1.normal;
		float overlap = OverlapOnAxis(vertices1, vertices2, axis);
		if (overlap < 0) {
			return std::make_pair(0, vector2{ 0, 0 });
		}
		if (overlap < min_overlap) {
			min_overlap = overlap;
			min_normal = axis;
		}
	}
	for (const Face& face2 : faces2) {
		vector2 axis = -1 * face2.normal;
		float overlap = OverlapOnAxis(vertices1, vertices2, axis);
		if (overlap < 0) {
			return std::make_pair(0, vector2{ 0, 0 });
		}
		if (overlap < min_overlap) {
			min_overlap = overlap;
			min_normal = axis;
		}
	}
	return std::make_pair(min_overlap, min_normal);
}

