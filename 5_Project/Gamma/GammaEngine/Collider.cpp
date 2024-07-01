#include "stdafx.h"
using namespace GammaEngine;

void GammaEngine::Collider::DecideCollisionState(CollisionResponse& result, bool collided, bool check)
{
	if (!collided && check)
	{
		result.state = CollisionState::Enter;
	}
	else if (collided && check)
	{
		result.state = CollisionState::Stay;
	}
	else if (!collided && !check)
	{
		result.state = CollisionState::Not;
	}
	else if (collided && !check)
	{
		result.state = CollisionState::Exit;
	}

}

vector2 GammaEngine::Collider::Support(Collider* A, Collider* B, vector2 direction)
{
	vector2 fA = A->FarthestPoint(direction);
	vector2 fB = B->FarthestPoint(-direction);
	return fA - fB;
}

vector2 GammaEngine::Collider::Support(Collider* A, vector2 v, vector2 direction)
{
	vector2 fA = A->FarthestPoint(direction);
	return fA - v;
}

bool GammaEngine::Collider::GJK(Collider* A, Collider* B, std::vector<vector2>& result)
{
	vector2 direction = B->transform->position- A->transform->position;
	vector2 a = Support(A, B, direction);

	vector2 v = -a;

	vector2 b = Support(A, B, v);

	if (vector2::Dot(b, v) < 0) return false;

	vector2 ab = b-a;
	v = vector2::TripleProduct(ab, -a, ab);

	for (;;) {
		vector2 c = Support(A, B, v);
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
			result.push_back(a);
			result.push_back(b);
			result.push_back(c);
			return true;
		}
	}
}

bool GammaEngine::Collider::GJK(Collider* A, vector2 vv)
{
	vector2 direction = vector2(1, 1);
	vector2 a = Support(A, vv, direction);

	vector2 v = -a;

	vector2 b = Support(A, vv, v);

	if (vector2::Dot(b, v) <= 0) return false;

	vector2 ab = b - a;
	v = vector2::TripleProduct(ab, -a, ab);

	for (;;) {
		vector2 c = Support(A, vv, v);
		if (vector2::Dot(c, v) <= 0) return false;

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

void GammaEngine::Collider::EPA(Collider* A, Collider* B, std::vector<vector2>& polytope, vector2& normal, float& distance)
{
	int MAX_LOOP = 500;
	int minIndex = 0;
	int count=0;
	float minDistance=INFINITY;
	vector2 minNormal;
	while (minDistance == INFINITY) {
		for (int i = 0; i < polytope.size(); i++) {
			int j = (i + 1) % polytope.size();

			vector2 vertexI = polytope[i];
			vector2 vertexJ = polytope[j];

			vector2 ij = vertexJ - vertexI;
			vector2 n = vector2(ij.y, -ij.x);
			n = vector2::Normalize(n);
			float dist = vector2::Dot(n,vertexI);

			if (dist < 0) {
				dist *= -1;
				n = -n;
			}

			if (dist < minDistance) {
				minDistance = dist;
				minNormal = n;
				minIndex = j;
			}
		}
		vector2 support = Support(A, B, minNormal);
		float sDistance = vector2::Dot(minNormal,support);
		if (count >= MAX_LOOP)
		{
			break;
		}
		if (abs(sDistance - minDistance) > 0.001) {
			minDistance = INFINITY;
			auto iter = polytope.begin();
			polytope.insert(iter + minIndex, support);
		}
		
		count++;
	}

	normal = minNormal;
	distance = minDistance;
}

void GammaEngine::Collider::ComputeContactPoint(Collider* A, Collider* B,vector2& contactPoint)
{
	std::pair<float, vector2> result = GammaPhysics::FindAxisLeastPenetration(A->ComputePoints(), B->ComputePoints());
	float depth = result.first;
	vector2 normal = result.second;
	vector2 support1 = GammaPhysics::FarthestPoint(A->ComputePoints(), -normal);
	vector2 support2 = GammaPhysics::FarthestPoint(B->ComputePoints(), normal);
	contactPoint = (support1 + support2)/2 + normal * depth * 0.5f;
}


GammaEngine::Collider::Collider(GameObject* t) : Component(t)
{
	CollisionSystem::Instance()->Add(this);
	CollisionSystem::Instance()->collidedMap->insert(std::make_pair(this, new std::vector<Collider*>()));
}

GammaEngine::Collider::~Collider()
{
	CollisionSystem* coll = CollisionSystem::Instance();
	coll->Remove(this);
}

bool GammaEngine::Collider::CompareTag(std::string str)
{
	return this->gameObject->CompareTag(str);
}

bool GammaEngine::Collider::CompareTag(char* str)
{
	return this->gameObject->CompareTag(str);
}

bool GammaEngine::Collider::CompareTags(std::vector<std::string> strList)
{
	std::vector<std::string>::iterator iter;
	for (iter = strList.begin(); iter < strList.end(); iter++)
	{
		if (CompareTag((*iter)))
		{
			return true;
		}
	}
	return false;
}

bool GammaEngine::Collider::CompareTags(std::vector<char*> strList)
{
	std::vector<char*>::iterator iter;
	for (iter = strList.begin(); iter < strList.end(); iter++)
	{
		if (CompareTag((*iter)))
		{
			return true;
		}
	}
	return false;
}

std::vector<vector2> GammaEngine::Collider::ComputePoints()
{
	return std::vector<vector2>();
}

vector2 GammaEngine::Collider::GetBounds()
{
	return vector2();
}