#include "GammaEngine.h"
#include "ControlBox.h"
#include "Gondola.h"

using namespace GammaEngine;
Gondola::Gondola(GameObject* t) : Component(t)
{

}

Gondola::~Gondola()
{

}

void Gondola::Start()
{
	if (trigger_)
	{
		trigger_->updateSubject.Where([this](Trigger* x) {
			auto y = dynamic_cast<ControlBox*>(x);
			controlBox_ = y;
			return y->index == index;
		}).Select<vector2>([](Trigger* x) {
			auto y = dynamic_cast<ControlBox*>(x);
			return y->velocity;
		}).Subscribe([this](vector2 v) {
			velocity = v;
		});
	}
}

void Gondola::Update()
{
	if (GetComponent<BitmapRenderer>() && abs(transform->position.y- centerHeight) <  boundary.y)
		GetComponent<BitmapRenderer>()->isEnabled = true;
	else if (GetComponent<BitmapRenderer>())
		GetComponent<BitmapRenderer>()->isEnabled = false;

	if (index == 1)
	{
		controlBox_->SetActorNeutral();
	}

	else if (index == 2)
	{
		controlBox_->SetActressNeutral();
	}

	if (transform->position.y >= centerHeight+boundary.y)
	{
		transform->position.y = centerHeight + boundary.y;

		if (index == 1)
		{
			controlBox_->SetActorDown();
		}

		else if (index == 2)
		{
			controlBox_->SetActressDown();
		}
	}
	if (transform->position.y <= centerHeight-boundary.y)
	{
		transform->position.y = centerHeight -boundary.y;

		if (index == 1)
		{
			controlBox_->SetActorUp();
		}

		else if (index == 2)
		{
			controlBox_->SetActressUp();
		}
	}

	transform->position += velocity * Time::deltaTime;
}
