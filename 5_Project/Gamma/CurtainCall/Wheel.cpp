#include "GammaEngine.h"
#include "GRX.h"
#include "Wheel.h"
#include "Player.h"
#include "Information.h"

Wheel::Wheel(GameObject* t) : Trigger(t)
{
	progress = 0.0f;

	rd = new std::random_device();
	gen = new std::mt19937((*rd)());
	tick = new std::uniform_real_distribution<float>(0.05f, 0.1f);
}

void Wheel::Use(Player* p)
{
	
	Trigger::RegistPlayer(p);
	Trigger::Hold();

	rotateL->isEnabled = true;
	rotateL->transform->position = vector2();
	Tween::CancelAnimate(rotateL->transform->position.x);
	Tween::CancelAnimate(rotateL->transform->position.y);
	Tween::Animate(rotateL->transform->position.y, PLAYBACK::ONCE_FORWARD, -100, OUTBACK, 1, 0, [this]() {
		Tween::Animate(rotateL->transform->position.x, PLAYBACK::LOOP_PINGPONG, rotateL->transform->position.x + 10, LINEAR, 1);
		Tween::Animate(rotateL->transform->position.y, PLAYBACK::LOOP_FORWARD, rotateL->transform->position.y + 10, LINEAR, 1);
		});

	Tween::Animate(p->transform->position.x, PLAYBACK::ONCE_FORWARD, transform->position.x - 50, EASING::LINEAR, 1);
	p->actionSubject.Select<float>([](PlayerAction x){
			return x.ThumbLAngle;
		}).BufferCount(1,100)
		.Select<float>([](std::vector<float> x) {
			return x[0];
		}).BufferCount(2)
		.Where([this](auto x) {
			return abs(x[1] - x[0]) > 10;
		})
		.Subscribe([this](auto x) {
		float tick = x[1] - x[0] > 0 ? 0.01 : -0.01;
		progress += tick;
		progress = progress > 1.0f ? 1.0f : progress;
		progress = progress < 0.0f ? 0.0f : progress;
		GetComponent<AudioSource>()->PlayReverb(17);
		GetComponent<AudioSource>()->SetVolume(17, 0.4f);
		if (tick > 0 && progress !=1.0f)
		{
			GamepadManager::GetPad(padId)->Vibrate(3000,50000,0.2);
		}
		else if(progress != 0.0f)
		{
			GamepadManager::GetPad(padId)->Vibrate(50000, 3000,0.2);
		}
			
	});

}
void Wheel::Start()
{
	rotateL = Information::Create(L"L_rotation");
	rotateL->transform->parent=this->transform;
	rotateL->GetComponent<BitmapRenderer>()->offset=vector2(5, 0);
}


void Wheel::Update()
{
	if (!user && progress > 0.0f)
	{
		progress -= 0.005f;
	}
	wheel->rotation = -progress * 720;

	Trigger::Update();
	if (useDebug)
	{
		Debug::DrawTextToWorld(vector2(100, 100), transform->position + vector2::Up * 100, L"¹ÙÄû »ç¿ëÁß", L"Verdana");
		Debug::DrawTextToWorld(vector2(100, 100), transform->position, std::to_wstring(progress * 100), L"Verdana");
	}
	else
	{
		GetComponent<AudioSource>()->Stop(17);
		Debug::DrawTextToWorld(vector2(100, 100), transform->position + vector2::Up * 100, L"¹ÙÄû »ç¿ëÁß¾Æ´Ô", L"Verdana");
		Debug::DrawTextToWorld(vector2(100, 100), transform->position, std::to_wstring(progress * 100), L"Verdana");
	}
}