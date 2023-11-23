#include "stdafx.h"
#include "Box2Script.h"
Box2Script::Box2Script(GameObject* t) :Component(t)
{
}

Box2Script::~Box2Script()
{
}

void Box2Script::Start()
{
	Tween::Animate(transform->rotation, PLAYBACK::LOOP_FORWARD, 360, EASING::LINEAR, 10);
	transform->rotation = 40;
	
}

void Box2Script::Update()
{
	transform->GetComponent<LineRenderer>()->src = vector2();
	transform->GetComponent<LineRenderer>()->dst = vector2();
	if (Input::GetKey('A'))
	{
		transform->position.x -= 300 * Time::deltaTime;
	}
	if (Input::GetKey('D'))
	{
		transform->position.x += 300 * Time::deltaTime;
	}

	if (Input::GetKey('W'))
	{
		transform->position.y -= 300 * Time::deltaTime;
	}
	if (Input::GetKey('S'))
	{
		transform->position.y += 300 * Time::deltaTime;
	}
}

void Box2Script::LateUpdate()
{
	
}

void Box2Script::OnCollisionEnter(CollisionResponse response)
{
	
}

void Box2Script::OnCollisionExit(CollisionResponse response)
{
	
}