#include "stdafx.h"
#include "Box2.h"
#include "Box2Script.h"
Box2::Box2()
{
	AddComponent<BoxCollider>();
	AddComponent<RectangleRenderer>();
	AddComponent<LineRenderer>();
	AddComponent<Box2Script>();
	GetComponent<BoxCollider>()->bounds = vector2(500,40);
	GetComponent<RectangleRenderer>()->size = vector2(500, 40);
	GetComponent<RectangleRenderer>()->order = -1;

	transform->position.x = 300;
	transform->position.y = 300;
	tag = string("box");
}

Box2::~Box2()
{

}