#include "GammaEngine.h"
#include "IInteractable.h"
#include "Player.h"
#include "Ladder.h"

Ladder::Ladder(GameObject* t):Component(t)
{

}

void Ladder::Start()
{
	BoxCollider* collider = GetComponent<BoxCollider>();
	bottom = transform->position.y + collider->GetBounds().y / 2 + offset;
	top = transform->position.y - collider->GetBounds().y / 2 - offset;

	
}

void Ladder::Update()
{
	Debug::DrawRectangle(vector2(100, 100), vector2(transform->position.x,top), 0, vector4(1, 0, 1, 1));
	Debug::DrawRectangle(vector2(100, 100), vector2(transform->position.x, bottom), 0, vector4(1, 0, 1, 1));
}

void Ladder::Use(Player* p)
{
	Tween::Animate(p->transform->position.x, PLAYBACK::ONCE_FORWARD, transform->position.x, EASING::LINEAR, 0.3);
	if (transform->position.y <= p->transform->position.y)
	{
		Tween::Animate(p->transform->position.y, PLAYBACK::ONCE_FORWARD, p->transform->position.y - offset, EASING::LINEAR, 0.3);
	}
	else
	{
		Tween::Animate(p->transform->position.y, PLAYBACK::ONCE_FORWARD, p->transform->position.y + offset, EASING::LINEAR, 0.3);
	}
		
}