#include "GammaEngine.h"
#include "GRX.h"
#include "Lever.h"
#include "Information.h"
#include "Player.h"

Lever::Lever(GameObject* t) : Trigger(t)
{
	std::random_device* rd = new std::random_device();
	gen = new std::mt19937((* rd)());
	tick = new std::uniform_real_distribution<float>(minTick, maxTick);
	dist = new std::uniform_real_distribution<float>(0.0f, 1.0f);
}

void Lever::Start()
{
	L_shake = Information::Create(L"L_shake");
	Tween::Animate(L_shake->transform->scale, PLAYBACK::LOOP_PINGPONG, vector2(1.2, 1.2), INBOUNCE, 3);
	Tween::Animate(L_shake->transform->position.x, PLAYBACK::LOOP_PINGPONG, L_shake->transform->position.x + 5, INOUTELASTIC, 1);

}

void Lever::Use(Player* p)
{
	L_shake->isEnabled = true;
	L_shake->transform->parent = transform;
	L_shake->transform->position = vector2();

	Tween::Animate(L_shake->transform->position, PLAYBACK::ONCE_FORWARD, vector2(0, -150), OUTBACK, 1, 0, [this]() {
		Tween::CancelAnimate(L_shake->transform->position.x);
		Tween::Animate(L_shake->transform->position.x, PLAYBACK::LOOP_PINGPONG, L_shake->transform->position.x + 5, INOUTELASTIC, 1);
	});
	Trigger::RegistPlayer(p);
	Trigger::Hold();
	if (_tween)
	{
		Tween::CancelAnimate(_tween);
		_tween = nullptr;
	}
	Tween::Animate(p->transform->position.x, PLAYBACK::ONCE_FORWARD, transform->position.x, EASING::LINEAR, 1);
	
	p->actionSubject.Where([](PlayerAction x) {
		return x.ThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	}).Throttle(0.1f)
	.Where([this](PlayerAction x) {
		return state!=SNAG;
	}).Subscribe([this](PlayerAction x) {

		GetComponent<AudioSource>()->PlayReverb(16);

		if ((*dist)(*gen) <= snagProbability)
		{
			//state == SNAG;
		}
		else if (progress > 0.0f)
		{
			progress -= (*tick)(*gen);
			
			GamepadManager::GetPad(padId)->Vibrate(30000, 3000, 0.2);
		}
		else if (progress <= 0.0f)
		{
			progress = 0.0f;
			initialProgress = 0.0f;
		}
		else if (progress >= 1.0f)
		{
			progress = 1.0f;
			initialProgress = 1.0f;
		}
		
	});

	p->actionSubject.Where([](PlayerAction x) {
		return x.ThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
	}).Throttle(0.1f)
	.Where([this](PlayerAction x) {
		return state!=SNAG;
	}).Subscribe([this](PlayerAction x) {
		GetComponent<AudioSource>()->PlayReverb(16);

		if ((*dist)(*gen) <= snagProbability)
		{
			//state == SNAG;
		}
		else if (progress < 1.0f)
		{
			progress += (*tick)(*gen);
			GamepadManager::GetPad(padId)->Vibrate(3000, 30000, 0.2);
		}
		else if (progress <= 0.0f)
		{
			progress = 0.0f;
			initialProgress = 0.0f;
		}
		else if (progress >= 1.0f)
		{
			progress = 1.0f;
			initialProgress = 1.0f;
		}
		
	});
}

void Lever::Update()
{
	Trigger::Update();
	if (!_tween && !user && progress != initialProgress)
	{
		_tween = Tween::Animate(progress, PLAYBACK::ONCE_FORWARD, initialProgress, EASING::OUTELASTIC, 0.2f);
	}
	if (stick)
	{
		stick->rotation = 60 - 120 * progress;
	}

	if (useDebug)
	{
		Debug::DrawTextToWorld(vector2(100, 100), transform->position + vector2::Up * 100, L"¹ÙÄû »ç¿ëÁß", L"Verdana");
		Debug::DrawTextToWorld(vector2(100, 100), transform->position, std::to_wstring(progress * 100), L"Verdana");
	}
	else
	{
		GetComponent<AudioSource>()->Stop(16);
		Debug::DrawTextToWorld(vector2(100, 100), transform->position + vector2::Up * 100, L"¹ÙÄû »ç¿ëÁß¾Æ´Ô", L"Verdana");
		Debug::DrawTextToWorld(vector2(100, 100), transform->position, std::to_wstring(progress * 100), L"Verdana");
	}

}