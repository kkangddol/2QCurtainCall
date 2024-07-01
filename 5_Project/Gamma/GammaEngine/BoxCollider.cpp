#include "stdafx.h"
using namespace GammaEngine;
GammaEngine::BoxCollider::BoxCollider(GameObject* t) :Collider(t)
{
	debug = new Material(vector4(0,1,0,1));
	simplex = nullptr;
}

GammaEngine::BoxCollider::~BoxCollider()
{

}

void GammaEngine::BoxCollider::SetBounds(vector2 v)
{
	bounds = v;
}
vector2 GammaEngine::BoxCollider::GetBounds()
{
	return bounds;
}

CollisionResponse GammaEngine::BoxCollider::Collide(Collider* other, bool collided)
{
	CollisionResponse result;
	std::vector<vector2> polytope;

	ResetPoints();
	bool detect = bounds.Length() != 0 && GJK(this, other, polytope);
	result.other = other;
	result.isTrigger = isTrigger || other->isTrigger;
	if (detect)
	{
 		EPA(this, other, polytope, result.normal, result.distance);
		ComputeContactPoint(this, other, result.contactPoint);
		//Debug::DrawRectangle(vector2(10, 10), result.contactPoint, 0, vector4(1, 0, 1, 1));
	}
	DecideCollisionState(result,collided, detect);
	return result;
}


std::vector<vector2> GammaEngine::BoxCollider::ComputePoints()
{
	if (!simplex)
	{
		simplex = new std::vector<vector2>(GammaPhysics::ComputePoints(bounds,transform->GetWorldMatrix()));
		return *simplex;
	}
	else
	{
		return *simplex;
	}
}

void GammaEngine::BoxCollider::ResetPoints()
{
	delete simplex;
	simplex = nullptr;
}

vector2 GammaEngine::BoxCollider::FarthestPoint(vector2 v)
{
	return GammaPhysics::FarthestPoint(ComputePoints(), v);
}

bool GammaEngine::BoxCollider::InBound(vector2 v)
{
	return GJK(this, v);
}
