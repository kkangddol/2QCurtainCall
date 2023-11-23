#include "stdafx.h"
#include "Box.h"
#include "BoxScript.h"

Box::Box()
{
	AddComponent<BoxCollider>();
	AddComponent<BoxScript>();
	GetComponent<BoxCollider>()->bounds = vector2(80,80);
	AddComponent<RectangleRenderer>();
	GetComponent<RectangleRenderer>()->size = vector2(80, 80);
	tag = string("box");
}