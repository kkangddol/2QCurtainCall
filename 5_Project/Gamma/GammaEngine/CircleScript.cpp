#include "stdafx.h"
#include "CircleScript.h"

CircleScript::CircleScript(GameObject* t) :Component(t)
{
}

CircleScript::~CircleScript()
{
}

void CircleScript::Start()
{

}

void CircleScript::Update()
{
	transform->position += velocity * Time::deltaTime;
	//velocity += gravity;
	correction = vector2();
}

void CircleScript::OnCollisionEnter(CollisionResponse response)
{
	
}

void CircleScript::OnCollisionStay(CollisionResponse response)
{

}


void CircleScript::OnCollisionExit(CollisionResponse response)
{
	
}