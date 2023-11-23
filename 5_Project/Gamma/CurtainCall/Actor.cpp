#include "GammaEngine.h"
#include "Actor.h"

using namespace GammaEngine;
Actor::Actor(GameObject* t) : Component(t)
{

}

Actor::~Actor()
{

}

void Actor::Update()
{
	if (GetComponent<SpineRenderer>() && abs(transform->parent->position.y - centerHeight) < boundary.y)
		GetComponent<SpineRenderer>()->isEnabled = true;
	else if (GetComponent<SpineRenderer>())
		GetComponent<SpineRenderer>()->isEnabled = false;
}
