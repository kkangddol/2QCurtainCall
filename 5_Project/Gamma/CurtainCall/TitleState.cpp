#include "GammaEngine.h"
#include "TitleState.h"

TitleState::TitleState(GameObject* t) : Component(t)
{
	if (current != this)
		gameObject->isEnabled = false;
}

void TitleState::Start()
{

}

void TitleState::Update()
{

}

void TitleState::OnEnter()
{
	State<TitleState>::OnEnter();
	gameObject->isEnabled = true;
}

void TitleState::OnExit()
{
	State<TitleState>::OnExit();
	gameObject->isEnabled = false;
}