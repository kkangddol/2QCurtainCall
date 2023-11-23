#include "GammaEngine.h"
#include "SkyObject.h"
#include "ControlBox.h"
using namespace GammaEngine;

SkyObject::SkyObject(GameObject* t) : Component(t)
{

}

SkyObject::~SkyObject()
{

}

void SkyObject::Start()
{
	transform->position = vector2(-600, -150);
}

void SkyObject::Update()
{
	if (GetComponent<BitmapRenderer>() && abs(transform->position.x) < boundary.x)
		GetComponent<BitmapRenderer>()->isEnabled = true;
	else if (GetComponent<BitmapRenderer>())
		GetComponent<BitmapRenderer>()->isEnabled = false;
}
