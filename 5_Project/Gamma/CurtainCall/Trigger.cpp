#include "GammaEngine.h"
#include "Player.h"
#include "Trigger.h"
#include "HighLighter.h"
#include "Information.h"


using namespace GammaEngine;

Trigger::Trigger(GameObject* t) : Component(t)
{
	progress = 0;
	AddComponent<HighLighter>();
}

Trigger::~Trigger()
{

}
void Trigger::Start()
{
	startSubject.OnNext(this);
}

void Trigger::Update()
{
	updateSubject.OnNext(this);
}

void Trigger::Reset()
{
	resetSubject.OnNext(this);
}

void Trigger::Hold()
{
	user->actionSubject.Where([](PlayerAction x) {
			return  x.buttonB == KeyState::released;
			}).First().Subscribe([this](PlayerAction x) {
				Information::DisableAll();
				user->info->isEnabled=true;
				user->info->transform->parent = transform;
				user->info->transform->position = vector2();
				Tween::Animate(user->info->transform->position, PLAYBACK::ONCE_FORWARD, vector2(100, -100), OUTBACK, 1);
				Tween::Animate(user->info->transform->scale, PLAYBACK::LOOP_PINGPONG, vector2(1.2, 1.2), INBOUNCE, 3);
				user->state = Player::IDLE;
				useDebug = false;
				user = nullptr;
			});
}

void Trigger::Toggle()
{
	user->actionSubject.Select<KeyState>([](PlayerAction x) {
		return x.buttonB;
		}).Where([](KeyState x) {
			return x == KeyState::pressed;
			}).First().Subscribe([this](KeyState x) {
				Information::DisableAll();
				user->info->transform->parent = transform;
				user->info->isEnabled = true;
				Tween::Animate(user->info->transform->position, PLAYBACK::ONCE_FORWARD, vector2(100, -100), OUTBACK, 1);
				Tween::Animate(user->info->transform->scale, PLAYBACK::LOOP_PINGPONG, vector2(1.2, 1.2), INBOUNCE, 3);
				user->state = Player::IDLE;
				useDebug = false;
				user = nullptr;
		});
}



void Trigger::OnCollisionEnter(CollisionResponse x)
{

}

void Trigger::OnCollisionStay(CollisionResponse x)
{

}

void Trigger::OnCollisionExit(CollisionResponse x)
{

}
void Trigger::RegistPlayer(Player* p)
{
	
	useDebug = true;
	user = p;
	p->actionSubject.Select<int>([](PlayerAction x) {
		return x.id;
		})
		.First()
			.Subscribe([this](int id) {
			padId = id;
				});
}