#include "stdafx.h"

using namespace GammaEngine;

GammaEngine::LineCollider::LineCollider(GameObject* t) :Collider(t)
{

}

GammaEngine::LineCollider::~LineCollider()
{

}

CollisionResponse GammaEngine::LineCollider::Collide(Collider* other, bool collided)
{
	CollisionResponse result;
	std::vector<vector2> polytope;

	bool detect = (endPoint-startPoint).Length()!=0 && GJK(this, other, polytope);
	result.other = other;
	result.isTrigger = isTrigger || other->isTrigger;
	if (detect)
	{
		EPA(this, other, polytope, result.normal, result.distance);
		ComputeContactPoint(this, other, result.contactPoint);
	}
	DecideCollisionState(result, collided, detect);
	return result;
}

vector2 GammaEngine::LineCollider::FarthestPoint(vector2 v)
{
	std::vector<vector2> simplex;
	simplex.push_back(startPoint);
	simplex.push_back(endPoint);
	return GammaPhysics::FarthestPoint(simplex, v);
}