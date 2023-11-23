#include "stdafx.h"
using namespace GammaEngine;

GammaEngine::Rigidbody::Rigidbody(GameObject* t) :Component(t),
mass(1), velocity(vector2()),
drag(0.08f), momentOfInertia(100.0f), restitution(0.0f),
angularDrag(0.05f), angularVelocity(0), torque(vector2()),
staticFriction(0.5f), dynamicFriction(1.0f),
useGravity(false), gravity(vector2::Down * 50), fixRotation(true),
frictionImpulse(vector2()), impulse(vector2())
{
	
}

GammaEngine::Rigidbody::~Rigidbody()
{

}
void GammaEngine::Rigidbody::SetIgnore(std::string name)
{
	ignoreList.insert(name);
}

void GammaEngine::Rigidbody::RemoveIgnore(std::string name)
{
	ignoreList.erase(name);
}


void GammaEngine::Rigidbody::Start()
{
	UpdateMomentOfInertia();
}

void GammaEngine::Rigidbody::UpdateMomentOfInertia()
{
	auto points = GetComponent<BoxCollider>()->ComputePoints();
	float sum = 0;
	for (int i = 0; i < points.size()-1; i++)
	{
		float step = (points[i].x * points[i + 1].y - points[i + 1].x * points[i].y) 
			* (points[i].x * points[i + 1].y + 2 * points[i].x * points[i].y + 2 * points[i + 1].x * points[i + 1].y + points[i + 1].x * points[i].y);
		sum += step;
	}
	sum /= 24;
	momentOfInertia = sum;
}

void GammaEngine::Rigidbody::Update()
{
	//Debug::DrawLine(transform->position, transform->position + velocity, vector4(1, 0, 0, 1));
	transform->position = transform->position + velocity * (float)Time::deltaTime;
	if (!fixRotation)
	{
		transform->rotation = transform->rotation + angularVelocity * (float)Time::deltaTime;
	}
	if (useGravity)
	{
		velocity = velocity + gravity;
	}

	velocity = velocity - velocity * drag;
	if (!fixRotation)
	{
		angularVelocity = angularVelocity;
	}
}

void GammaEngine::Rigidbody::LateUpdate()
{
	//impulse = vector2();
	//frictionImpulse = vector2();
}

void GammaEngine::Rigidbody::AddForce(vector2 force, ForceMode mode)
{
	switch (mode)
	{
	case GammaEngine::Rigidbody::Force:
		velocity = velocity + force / (mass > 0 ? mass : 1);
		break;
	case GammaEngine::Rigidbody::Impulse:
		velocity = velocity + force / (mass > 0 ? mass : 1) / (float)Time::deltaTime;
		break;
	case GammaEngine::Rigidbody::Acceleration:
		velocity = velocity + force;
		break;
	case GammaEngine::Rigidbody::VelocityChange:
		velocity = velocity + force / (float)Time::deltaTime;
		break;
	default:
		break;
	}
	
}

void GammaEngine::Rigidbody::OnCollisionEnter(CollisionResponse response)
{
	for (auto ignore : ignoreList)
	{
		if (response.other->CompareTag(ignore))
		{
			return;
		}
	}
	

	if (!response.isTrigger && mass > 0)
	{
		Rigidbody* otherRig = response.other->GetComponent<Rigidbody>();
		impulse = ResolveImpulse(this, otherRig, response);
		frictionImpulse = ResolveFrictionImpulse(this, otherRig, response);
		PositionalCorrection(this, otherRig, response);
	}
}

void GammaEngine::Rigidbody::OnCollisionStay(CollisionResponse response)
{
	for (auto ignore : ignoreList)
	{
		if (response.other->CompareTag(ignore))
		{
			return;
		}
	}

	if (!response.isTrigger && mass > 0)
	{
		Rigidbody* otherRig = response.other->GetComponent<Rigidbody>();
		impulse = ResolveImpulse(this, otherRig, response);
		frictionImpulse = ResolveFrictionImpulse(this, otherRig, response);
		PositionalCorrection(this, otherRig, response);
	}
}

void GammaEngine::Rigidbody::OnCollisionExit(CollisionResponse response)
{
	
}

vector2 GammaEngine::Rigidbody::ResolveFrictionImpulse(Rigidbody* A, Rigidbody* B, CollisionResponse res)
{
	float InversMassA;
	if (A->mass == 0)
	{
		InversMassA = 0;
	}
	else
	{
		InversMassA = 1 / A->mass;
	}

	float InversMassB;
	if (!B || B->mass == 0)
	{
		InversMassB = 0;
	}
	else
	{
		InversMassB = 1 / B->mass;
	}
	vector2 rv = B ? B->velocity - A->velocity : -A->velocity;
	vector2 tangent = vector2::Normalize(rv - vector2::Dot(rv, res.normal) * res.normal);

	float velAlongNormal = vector2::Dot(rv, res.normal);

	if (velAlongNormal > 0)
		return vector2();

	float e = B ? A->restitution * B->restitution : 0;

	float j = -(1 + e) * velAlongNormal;

	j /= InversMassA + InversMassB;

	float jt = -vector2::Dot(rv, tangent);
	jt = jt / (InversMassA + InversMassB);

	float mu = B ? sqrt((float)pow(A->staticFriction, 2)+(float)pow(B->staticFriction, 2)) : A->staticFriction;
	vector2 frictionImpulse;
	float dynamicFriction;
	if (abs(jt) < j * mu)
		frictionImpulse = jt * tangent;
	else
	{
		dynamicFriction = B ? sqrt((float)pow(A->dynamicFriction, 2) + (float)pow(B->dynamicFriction, 2)):A->dynamicFriction;
		frictionImpulse = -j * tangent * dynamicFriction;
	}
	// Apply 
	A->velocity -= InversMassA * frictionImpulse;
	if(B)
		B->velocity += InversMassB * frictionImpulse;
	return frictionImpulse;
}

vector2 GammaEngine::Rigidbody::ResolveImpulse(Rigidbody* A, Rigidbody* B, CollisionResponse res)
{
	float InversMassA;
	if (A->mass==0)
	{
		InversMassA = 0;
	}
	else
	{
		InversMassA = 1 / A->mass;
	}

	float InversMassB;
	if (!B || B->mass == 0)
	{
		InversMassB = 0;
	}
	else
	{
		InversMassB = 1 / B->mass;
	}
	

	vector2 rv = B ? B->velocity - A->velocity : -A->velocity;
	
	float velAlongNormal = vector2::Dot(rv, res.normal);

	if (velAlongNormal > 0)
		return vector2();

	float e = B ? A->restitution * B->restitution : 0;

	float j = -(1 + e) * velAlongNormal;

	j /= InversMassA + InversMassB;
	

	vector2 impulse = j * res.normal;

// 	float mass_sum = A->mass + B->mass;
// 	float ratio = A->mass / mass_sum;
// 	A->velocity -= ratio * impulse;
// 
// 	ratio = B->mass / mass_sum;
// 	B->velocity += ratio * impulse;
	A->velocity -= InversMassA * impulse;
	if(B)
		B->velocity += InversMassB * impulse;
	if (!A->fixRotation)
	{
		A->angularVelocity -= 1.0f / A->momentOfInertia * vector2::Cross(res.contactPoint, impulse);
	}
	if(B && !B->fixRotation)
	{
		B->angularVelocity += 1.0f / B->momentOfInertia * vector2::Cross(res.contactPoint, impulse);
	}
	return impulse;
}

void GammaEngine::Rigidbody::PositionalCorrection(Rigidbody* A, Rigidbody* B, CollisionResponse res)
{
	float InversMassA;
	if (A->mass == 0)
	{
		InversMassA = 0;
	}
	else
	{
		InversMassA = 1 / A->mass;
	}

	float InversMassB;
	if (!B || B->mass == 0)
	{
		InversMassB = 0;
	}
	else
	{
		InversMassB = 1 / B->mass;
	}

	const float percent = 0.2f;
	const float slop = 0.01f;

	vector2 correction = (max(res.distance - slop, 0.1f) / (InversMassA + InversMassB)) * percent * res.normal;
	A->transform->position -= correction * InversMassA;
	if(B)
		B->transform->position += correction * InversMassB;
}