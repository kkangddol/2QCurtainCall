#include "GammaEngine.h"
#include "MainCamera.h"

using namespace GammaEngine;

MainCamera::MainCamera(GameObject* t) : Component(t)
{

}

MainCamera::~MainCamera()
{

}

void MainCamera::Start()
{

}

void MainCamera::Update()
{
	if (Input::mouseScrollDelta > 0)
	{
		Camera::main->orthoScale -= 0.1f;
	}
	if (Input::mouseScrollDelta < 0)
	{
		Camera::main->orthoScale += 0.1f;
	}

	if (Input::GetKey('W'))
	{
		Tween::Animate(transform->position.y, PLAYBACK::ONCE_FORWARD, transform->position.y - speed, EASING::INBACK, 0.01f);
	}	

	if (Input::GetKey('S'))
	{
		Tween::Animate(transform->position.y, PLAYBACK::ONCE_FORWARD, transform->position.y + speed, EASING::INBACK, 0.01f);
	}	

	if (Input::GetKey('A'))
	{
		Tween::Animate(transform->position.x, PLAYBACK::ONCE_FORWARD, transform->position.x - speed, EASING::INBACK, 0.01f);
	}	

	if (Input::GetKey('D'))
	{
		Tween::Animate(transform->position.x, PLAYBACK::ONCE_FORWARD, transform->position.x + speed, EASING::INBACK, 0.01f);
	}
}


