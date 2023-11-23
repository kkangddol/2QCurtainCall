#include "GammaEngine.h"
#include "IInteractable.h"
#include "Player.h"
#include "Box.h"

Box::Box(GameObject* t) :Component(t)
{

}



void Box::Update()
{


}

void Box::Use(Player* p)
{
	Tween::Animate(p->transform->position.x, PLAYBACK::ONCE_FORWARD, transform->position.x, EASING::LINEAR, 1);
}