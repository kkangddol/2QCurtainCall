#include "GammaEngine.h"
#include "Elevator.h"

using namespace GammaEngine;

Elevator::Elevator(GameObject* t) : Component(t)
{
	
}

Elevator::~Elevator()
{

}

void Elevator::Start()
{
	initialHeight = transform->position.y;
	if (trigger_)
	{
		trigger_->updateSubject.Select<float>([](Trigger* x) {
			return x->progress;
		}).Where([this](float x) {
			return x >= 1 && movable;
		}).Subscribe([this](float y) {
			if (initialHeight - maxHeight < transform->position.y)
			{
				transform->position.y -= speed * Time::deltaTime;
			}
		});

		trigger_->updateSubject.Select<float>([](Trigger* x) {
			return x->progress;
		}).Where([this](float x) {
			return x <= 0 && movable;
		}).Subscribe([this](float y) {
			if(initialHeight> transform->position.y)
				transform->position.y += speed * Time::deltaTime;
		});

	}
}

void Elevator::Update()
{

}

void Elevator::OnCollisionEnter(CollisionResponse res)
{
	if (res.normal.y > 0.5 && res.other->CompareTag("player"))
	{
		movable=false;
	}
}

void Elevator::OnCollisionExit(CollisionResponse res)
{
	movable = true;
}