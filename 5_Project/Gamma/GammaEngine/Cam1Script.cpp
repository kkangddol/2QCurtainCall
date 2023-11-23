#include "stdafx.h"
#include "Cam1Script.h"

Cam1Script::Cam1Script(GameObject* t) :Component(t)
{
}

Cam1Script::~Cam1Script()
{
}

void Cam1Script::Update()
{
	if(Input::mouseScrollDelta > 0)
	{
		if (transform->GetComponent<Camera>()->orthoScale > 0)
		{
			transform->GetComponent<Camera>()->orthoScale -= 0.1;
		}
	}
	else if(Input::mouseScrollDelta < 0)
	{
		transform->GetComponent<Camera>()->orthoScale += 0.1;
	}

	if (Input::GetKey(VK_UP))
	{
		transform->position.y -= speed * Time::deltaTime;
	}
	if (Input::GetKey(VK_LEFT))
	{
		transform->position.x -= speed * Time::deltaTime;
	}
	if (Input::GetKey(VK_DOWN))
	{
		transform->position.y += speed * Time::deltaTime;
	}
	if (Input::GetKey(VK_RIGHT))
	{
		transform->position.x += speed * Time::deltaTime;
	}

}