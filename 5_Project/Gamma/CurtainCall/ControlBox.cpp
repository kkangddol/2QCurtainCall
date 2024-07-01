#include "GammaEngine.h"
#include "GRX.h"
#include "ControlBox.h"
#include "Information.h"
#include "SkyObject.h"
#include "Player.h"

ControlBox::ControlBox(GameObject* t) : Trigger(t)
{
	progress = 0.0f;

}

void ControlBox::ShowInfo()
{
	Information::DisableAll();
	if (index == 0)
	{
		Tween::Animate(L_shake->transform->position, PLAYBACK::ONCE_FORWARD, vector2(-100, -220), OUTBACK, 1, 0, [this]() {
			Tween::CancelAnimate(L_shake->transform->position.x);
			Tween::Animate(L_shake->transform->position.x, PLAYBACK::LOOP_PINGPONG, L_shake->transform->position.x + 5, INOUTELASTIC, 1);
			});
		
		L_shake->isEnabled = true;
		L_shake->transform->parent = transform;
		L_shake->transform->position = vector2();
		sun_moon_cloud->isEnabled = true;
	}
	else if (index == 1)
	{
		Tween::Animate(L_updown->transform->position, PLAYBACK::ONCE_FORWARD, vector2(-100, -220), OUTBACK, 1, 0, [this]() {
			Tween::CancelAnimate(L_updown->transform->position.y);
			Tween::Animate(L_updown->transform->position.y, PLAYBACK::LOOP_PINGPONG, L_shake->transform->position.y + 5, INOUTELASTIC, 1);
			});
		L_updown->isEnabled = true;
		L_updown->transform->parent = transform;
		L_updown->transform->position = vector2();
		actorA->isEnabled = true;
	}
	else if (index == 2)
	{
		Tween::Animate(L_updown->transform->position, PLAYBACK::ONCE_FORWARD, vector2(-100, -220), OUTBACK, 1, 0, [this]() {
			Tween::CancelAnimate(L_updown->transform->position.y);
			Tween::Animate(L_updown->transform->position.y, PLAYBACK::LOOP_PINGPONG, L_shake->transform->position.y + 5, INOUTELASTIC, 1);
		});
		L_updown->isEnabled = true;
		L_updown->transform->parent = transform;
		L_updown->transform->position = vector2();
		actorB->isEnabled = true;
	}
	Tween::Animate(popupbubble->transform->position, PLAYBACK::ONCE_FORWARD, vector2(150, -220), OUTBACK, 1);
	popupbubble->isEnabled = true;
	popupbubble->transform->parent = transform;
	popupbubble->transform->position = vector2(100, -170);
	
	lb->isEnabled = true;
	lb->transform->parent = transform;
	lb->transform->position = vector2();
	Tween::Animate(lb->transform->position, PLAYBACK::ONCE_FORWARD, vector2(150, -100), OUTBACK, 1);


	rb->isEnabled = true;
	rb->transform->parent = transform;
	rb->transform->position = vector2();
	Tween::Animate(rb->transform->position, PLAYBACK::ONCE_FORWARD, vector2(-150, -100), OUTBACK, 1);
}

void ControlBox::Use(Player* p)
{

	Trigger::RegistPlayer(p);
	Trigger::Toggle();
	Tween::Animate(p->transform->position.x, PLAYBACK::ONCE_FORWARD, transform->position.x, EASING::LINEAR, 1);
	ShowInfo();
	p->actionSubject.Where([](PlayerAction x) {
		return x.LeftShoulder == KeyState::pressed;
		}).Subscribe([this](PlayerAction x) {
			index--;
			if (index == -1)
			{
				index = 2;
			}
			ShowInfo();
		});
		p->actionSubject.Where([](PlayerAction x) {
			return x.RightShoulder==KeyState::pressed;
			}).Subscribe([this](PlayerAction x) {
				index = (index + 1) % 3;
				ShowInfo();
			});

	p->actionSubject.Select<float>([](PlayerAction x) {
		return x.ThumbLX;
	}).Where([this](float x) {
		return  index == 0 &&(x < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || x > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
	}).Throttle(2.0f).Subscribe([this](float x) {
		currentSky->transform->position = center;
		currentSky->next->transform->position = rightPos;
		currentSky->previous->transform->position = leftPos;
		if (x < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			Tween::Animate(currentSky->transform->position, PLAYBACK::ONCE_FORWARD, leftPos, EASING::INBACK, 1);
			currentSky = currentSky->next;
			Tween::Animate(currentSky->transform->position, PLAYBACK::ONCE_FORWARD, center, EASING::INBACK, 1, 0.5);
		}
		else if (x > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			Tween::Animate(currentSky->transform->position, PLAYBACK::ONCE_FORWARD, rightPos, EASING::INBACK, 1);
			currentSky = currentSky->previous;
			Tween::Animate(currentSky->transform->position, PLAYBACK::ONCE_FORWARD, center, EASING::INBACK, 1,0.5);
		}
		
	});

	p->actionSubject.Select<float>([](PlayerAction x) {
		return x.ThumbLY;
		}).Where([this](float x) {
			return index > 0 &&(x < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || x > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		}).Subscribe([this](float y) {
			if (y < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				velocity.y = moveSpeed;
			}
			else if (y > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				velocity.y = -moveSpeed;
			}
	});
}

void ControlBox::SetActorNeutral()
{
	isActorDown_ = false;
	isActorUp_ = false;
}

void ControlBox::SetActorDown()
{
	isActorDown_ = true;
	isActorUp_ = false;
}

void ControlBox::SetActorUp()
{
	isActorDown_ = false;
	isActorUp_ = true;
}

void ControlBox::SetActressNeutral()
{
	isActressDown_ = false;
	isActressUp_ = false;
}

void ControlBox::SetActressDown()
{
	isActressDown_ = true;
	isActressUp_ = false;
}

void ControlBox::SetActressUp()
{
	isActressDown_ = false;
	isActressUp_ = true;
}

void ControlBox::Start()
{
	currentSky->transform->position = center;
	currentSky->next->transform->position = leftPos;
	currentSky->previous->transform->position = rightPos;

	lb = Information::Create(L"lb");
	rb = Information::Create(L"rb");
	L_shake = Information::Create(L"L_shake");
	popupbubble = Information::Create(L"popupbubble");
	sun_moon_cloud = Information::Create(L"sun_moon_cloud");
	actorA = Information::Create(L"actorA");
	actorB = Information::Create(L"actorB");
	L_updown = Information::Create(L"updown_L");
	sun_moon_cloud->transform->parent = popupbubble->transform;
	actorA->transform->parent = popupbubble->transform;
	actorB->transform->parent = popupbubble->transform;
	sun_moon_cloud->transform->scale = vector2(0.5, 0.5);
	actorA->transform->scale = vector2(0.2, 0.2);
	actorB->transform->scale = vector2(0.2, 0.2);


	Tween::Animate(lb->transform->scale, PLAYBACK::LOOP_PINGPONG, vector2(1.2, 1.2), INBOUNCE, 3);
	Tween::Animate(rb->transform->scale, PLAYBACK::LOOP_PINGPONG, vector2(1.2, 1.2), INBOUNCE, 3);
	Tween::Animate(L_shake->transform->scale, PLAYBACK::LOOP_PINGPONG, vector2(1.2, 1.2), INBOUNCE, 3);
	Tween::Animate(L_shake->transform->position.x, PLAYBACK::LOOP_PINGPONG, L_shake->transform->position.x + 5, INOUTELASTIC, 1);
	Tween::Animate(L_updown->transform->scale, PLAYBACK::LOOP_PINGPONG, vector2(1.2, 1.2), INBOUNCE, 3);
	Tween::Animate(L_updown->transform->position.y, PLAYBACK::LOOP_PINGPONG, L_updown->transform->position.y + 5, INOUTELASTIC, 1);
	Tween::Animate(popupbubble->transform->scale, PLAYBACK::LOOP_PINGPONG, vector2(1.2, 1.2), INSINE, 3);

}


void ControlBox::Update()
{
	Trigger::Update();
	Debug::DrawTextToWorld(vector2(100, 100), transform->position, std::to_wstring(index), std::wstring(L"Verdana"));
	velocity = vector2();
}

bool ControlBox::CheckStatus(int archIndex, int archDown, int archUp, int sound, int rainRatio, int skyIndex, int skyAppear, int actorDown, int actorUp, int actressDown, int actressUp)
{
	int temp = 1;

	if (skyIndex != -1)
	{
		temp *= (currentSky->index == skyIndex);
	}

	if (skyAppear != -1)
	{
		temp *= (currentSky->index == skyIndex);
	}

	if (actorDown != -1)
	{
		temp *= (!isActorUp_ == actorDown);
	}

	if (actorUp != -1)
	{
		temp *= (isActorUp_ == actorUp);
	}

	if (actressDown != -1)
	{
		temp *= (!isActressUp_ == actressDown);
	}

	if (actressUp != -1)
	{
		temp *= (isActressUp_ == actressUp);
	}

	return temp;
}
